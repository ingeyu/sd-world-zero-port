#include "Stdafx.h"
#include "sdTerrainAtlasGeometryPass.h"
#include "sdRenderDevice_DX9.h"
#include "sdRenderSystem_DX9.h"
#include "sdResourceSystem.h"

using namespace ResourceSystem;

namespace RenderSystem
{

//-------------------------------------------------------------------------------------------------
sdTerrainAtlasGeometryPass::sdTerrainAtlasGeometryPass(sdRenderObjectAlloc* pkAlloc)
: sdRenderPass(pkAlloc)
, m_uiStencilRef(0)
, m_uiStencilMask(0)
{
	
}
//-------------------------------------------------------------------------------------------------
sdTerrainAtlasGeometryPass::~sdTerrainAtlasGeometryPass()
{
	if (m_bInitialized)
	{
		Destroy();
		m_bInitialized = false;
	}
}
//-------------------------------------------------------------------------------------------------
bool sdTerrainAtlasGeometryPass::Initialize(uint uiStencilRef, uint uiStencilMask, uint uiStencilFarTerrainBit, NiRenderedTexture* spDepthTexture)
{
	NIASSERT(uiStencilRef & uiStencilMask);
	NIASSERT(uiStencilFarTerrainBit);
	NIASSERT(spDepthTexture);

	if (m_bInitialized)
	{
		NIASSERT(0);
		return false;
	}

	//
	sdRenderDevice* pkRenderDevice = sdRenderDevice_DX9::InstancePtr();
	NIASSERT(pkRenderDevice);

	sdResourceSystem* pkResourceSystem = sdResourceSystem::InstancePtr();
	NIASSERT(pkResourceSystem);

	// 设置模版参数
	m_uiStencilRef = uiStencilRef;
	m_uiStencilMask = uiStencilMask;
	m_uiStencilFarTerrainBit = uiStencilFarTerrainBit;

	// 设置输入纹理
	m_spDepthTexture = spDepthTexture;

	m_spUVTableCubeMap = pkResourceSystem->LoadCubeTexture("dependence\\engine\\texture\\terrain\\terrainuvtable.dds");
	NIASSERT(m_spUVTableCubeMap);

	// 初始化材质
	m_spBaseNormalOnlyMaterial = pkRenderDevice->CreateMaterial("Terrain_AtlasGeometry_BaseNormal");
	NIASSERT(m_spBaseNormalOnlyMaterial);

	m_spNearNormalMapMaterial = pkRenderDevice->CreateMaterial("Terrain_AtlasGeometry_Near_BaseNormalAndNormalMap");
	NIASSERT(m_spNearNormalMapMaterial);

	m_spFarBaseNormalMaterial = pkRenderDevice->CreateMaterial("Terrain_AtlasGeometry_Far_BaseNormal");
	NIASSERT(m_spFarBaseNormalMaterial);

	// 初始化纹理属性
	m_spTexturingProp  = NiNew NiTexturingProperty;
	NIASSERT(m_spTexturingProp);
	m_spTexturingProp->SetShaderMap(0, NiNew NiTexturingProperty::ShaderMap(m_spUVTableCubeMap, 0));
	m_spTexturingProp->SetShaderMap(1, NiNew NiTexturingProperty::ShaderMap(spDepthTexture, 0));
	m_spTexturingProp->SetShaderMap(2, NiNew NiTexturingProperty::ShaderMap(0, 0));
	m_spTexturingProp->SetShaderMap(3, NiNew NiTexturingProperty::ShaderMap(0, 0));
	m_spTexturingProp->SetShaderMap(4, NiNew NiTexturingProperty::ShaderMap(0, 0));
	m_spTexturingProp->SetShaderMap(5, NiNew NiTexturingProperty::ShaderMap(0, 0));
	m_spTexturingProp->SetShaderMap(6, NiNew NiTexturingProperty::ShaderMap(0, 0));
	m_kPropertyList.AddTail((NiTexturingProperty*)m_spTexturingProp);

	return (m_bInitialized = true);
}
//-------------------------------------------------------------------------------------------------
void sdTerrainAtlasGeometryPass::Destroy()
{
	m_spTexturingProp = 0;

	m_spDepthTexture = 0;
	m_spUVTableCubeMap = 0;

	m_spBaseNormalOnlyMaterial = 0;
	m_spNearNormalMapMaterial = 0;
	m_spFarBaseNormalMaterial =0;

	m_uiStencilRef = 0;
	m_uiStencilMask = 0;

	m_bInitialized = false;
}
//-------------------------------------------------------------------------------------------------
void sdTerrainAtlasGeometryPass::SetTerrainParams(const sdTerrainParams& kTerrainParams)
{
	// 地表normalMap
	NiTexturingProperty::ShaderMap* spShaderMap = m_spTexturingProp->GetShaderMap(2);
	NIASSERT(spShaderMap);
	if (spShaderMap->GetTexture() != kTerrainParams.baseNormalMap)
	{
		spShaderMap->SetTexture(kTerrainParams.baseNormalMap);
	}

	// 地表TileMap
	spShaderMap = m_spTexturingProp->GetShaderMap(3);
	NIASSERT(spShaderMap);
	if (spShaderMap->GetTexture() != kTerrainParams.tileMap)
	{
		spShaderMap->SetTexture(kTerrainParams.tileMap);
	}

	// 地表BlendeMap
	spShaderMap = m_spTexturingProp->GetShaderMap(4);
	NIASSERT(spShaderMap);
	if (spShaderMap->GetTexture() != kTerrainParams.blendMap)
	{
		spShaderMap->SetTexture(kTerrainParams.blendMap);
	}

	// 地表NormalMap
	spShaderMap = m_spTexturingProp->GetShaderMap(5);
	NIASSERT(spShaderMap);
	if (spShaderMap->GetTexture() != kTerrainParams.normalAtlasTableMap)
	{
		spShaderMap->SetTexture(kTerrainParams.normalAtlasTableMap);
	}

	spShaderMap = m_spTexturingProp->GetShaderMap(6);
	NIASSERT(spShaderMap);
	if (spShaderMap->GetTexture() != kTerrainParams.normalAtlasMap)
	{
		spShaderMap->SetTexture(kTerrainParams.normalAtlasMap);
	}
}
//-------------------------------------------------------------------------------------------------
void sdTerrainAtlasGeometryPass::Draw()
{
	D3DPERF_BeginEvent(0xff000000, L"TerrainAtlasGeometryPass");

	sdRenderDevice* pkRenderDevice = sdRenderDevice_DX9::InstancePtr();
	NIASSERT(pkRenderDevice);

	sdRenderSystem* pkRenderSystem = sdRenderSystem_DX9::InstancePtr();
	NIASSERT(pkRenderSystem);

	NiRenderer* spRenderer = NiRenderer::GetRenderer();
	NIASSERT(spRenderer);

	// 清除数据绑定
	pkRenderDevice->ClearVertexBinding();
	//pkRenderDevice->ClearTextureBinding();

	// 根据当前地形渲染的NormalMap通道设置进行分别处理
	if (m_pkRenderParams->IsEnableChannel(sdRenderParams::E_TERRAIN, sdRenderParams::E_NORMALMAP))
	{
		// 地形允许使用NormalMap通道,从而可以使用NormalMap
		//
		// 设置渲染状态
		// @{
		// CullMode
		pkRenderDevice->SetRenderState(D3DRS_CULLMODE,			D3DCULL_NONE);

		// Alpha 
		//
		// WZ原文如下,不解(已修改)
		//pkRenderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,	true);
		//pkRenderDevice->SetRenderState(D3DRS_BLENDOP,				D3DBLENDOP_ADD);
		//pkRenderDevice->SetRenderState(D3DRS_SRCBLEND,			D3DBLEND_ONE);
		//pkRenderDevice->SetRenderState(D3DRS_DESTBLEND,			D3DBLEND_ONE);
		//
		pkRenderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,	false);
		pkRenderDevice->SetRenderState(D3DRS_ALPHATESTENABLE,	false);

		// Z
		pkRenderDevice->SetRenderState(D3DRS_ZENABLE,			false);
		pkRenderDevice->SetRenderState(D3DRS_ZWRITEENABLE,		false);

		// Stencil
		// (这里将所有Terrain像素替换为FraTerrain像素)
		pkRenderDevice->SetRenderState(D3DRS_STENCILENABLE,		true);
		pkRenderDevice->SetRenderState(D3DRS_STENCILFUNC,		D3DCMP_EQUAL);
		pkRenderDevice->SetRenderState(D3DRS_STENCILFAIL,		D3DSTENCILOP_KEEP);
		pkRenderDevice->SetRenderState(D3DRS_STENCILZFAIL,		D3DSTENCILOP_KEEP);
		pkRenderDevice->SetRenderState(D3DRS_STENCILPASS,		D3DSTENCILOP_REPLACE);
		pkRenderDevice->SetRenderState(D3DRS_STENCILREF,		m_uiStencilRef | (1 << m_uiStencilFarTerrainBit));
		pkRenderDevice->SetRenderState(D3DRS_STENCILMASK,		m_uiStencilMask);
		pkRenderDevice->SetRenderState(D3DRS_STENCILWRITEMASK,	1 << m_uiStencilFarTerrainBit);
		// @}

		// 绘制
		// @{
		NiMesh* spScreenMesh = pkRenderSystem->GetDefaultMesh(sdRenderSystem::E_SCREEN_QUAD);
		NIASSERT(spScreenMesh);

		NiPropertyState* spPropState = spScreenMesh->GetPropertyState();
		NIASSERT(spPropState);
		spPropState->SwapProperties(m_kPropertyList);

		// 绘制远处
		spScreenMesh->ApplyAndSetActiveMaterial(m_spFarBaseNormalMaterial);
		spScreenMesh->RenderImmediate(spRenderer);

		// 绘制近处
		pkRenderDevice->SetRenderState(D3DRS_STENCILREF,		m_uiStencilRef );
		pkRenderDevice->SetRenderState(D3DRS_STENCILMASK,		m_uiStencilMask | (1 << m_uiStencilFarTerrainBit));
		pkRenderDevice->SetRenderState(D3DRS_STENCILWRITEMASK,	1 << m_uiStencilFarTerrainBit);	

		spScreenMesh->ApplyAndSetActiveMaterial(m_spNearNormalMapMaterial);
		spScreenMesh->RenderImmediate(spRenderer);

		//
		spScreenMesh->SetActiveMaterial(NULL);
		spPropState->SwapProperties(m_kPropertyList);
		// @}
	}
	else
	{
		// 地形禁用NormalMap通道,从而只能使用基础法线
		//
		// 设置渲染状态
		// @{
		// CullMode
		pkRenderDevice->SetRenderState(D3DRS_CULLMODE,			D3DCULL_NONE);

		// Alpha 
		//
		// WZ原文如下,不解(已修改)
		//pkRenderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,	true);
		//pkRenderDevice->SetRenderState(D3DRS_BLENDOP,				D3DBLENDOP_ADD);
		//pkRenderDevice->SetRenderState(D3DRS_SRCBLEND,			D3DBLEND_ONE);
		//pkRenderDevice->SetRenderState(D3DRS_DESTBLEND,			D3DBLEND_ONE);
		//
		pkRenderDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,	false);
		pkRenderDevice->SetRenderState(D3DRS_ALPHATESTENABLE,	false);

		// Z
		pkRenderDevice->SetRenderState(D3DRS_ZENABLE,			false);
		pkRenderDevice->SetRenderState(D3DRS_ZWRITEENABLE,		false);

		// Stencil
		// (这里将所有Terrain像素替换为FraTerrain像素)
		pkRenderDevice->SetRenderState(D3DRS_STENCILENABLE,		true);
		pkRenderDevice->SetRenderState(D3DRS_STENCILFUNC,		D3DCMP_EQUAL);
		pkRenderDevice->SetRenderState(D3DRS_STENCILFAIL,		D3DSTENCILOP_KEEP);
		pkRenderDevice->SetRenderState(D3DRS_STENCILZFAIL,		D3DSTENCILOP_KEEP);
		pkRenderDevice->SetRenderState(D3DRS_STENCILPASS,		D3DSTENCILOP_REPLACE);
		pkRenderDevice->SetRenderState(D3DRS_STENCILREF,		m_uiStencilRef | (1 << m_uiStencilFarTerrainBit));
		pkRenderDevice->SetRenderState(D3DRS_STENCILMASK,		m_uiStencilMask);
		pkRenderDevice->SetRenderState(D3DRS_STENCILWRITEMASK,	1 << m_uiStencilFarTerrainBit);
		// @}

		// 绘制
		// @{
		NiMesh* spScreenMesh = pkRenderSystem->GetDefaultMesh(sdRenderSystem::E_SCREEN_QUAD);
		NIASSERT(spScreenMesh);

		NiPropertyState* spPropState = spScreenMesh->GetPropertyState();
		NIASSERT(spPropState);
		spPropState->SwapProperties(m_kPropertyList);
		spScreenMesh->ApplyAndSetActiveMaterial(m_spBaseNormalOnlyMaterial);

		spScreenMesh->RenderImmediate(spRenderer);

		spScreenMesh->SetActiveMaterial(NULL);
		spPropState->SwapProperties(m_kPropertyList);
		// @}
	}

	D3DPERF_EndEvent();
}
//-------------------------------------------------------------------------------------------------
}