//*************************************************************************************************
// ����:	������ɫ���Ĺ�������
//---------------------------------------------------------
// ����:		
// ����:		2012-08-04
// ����޸�:	2012-10-03
//*************************************************************************************************
#ifndef _TERRAIN_COMMON_H__
#define _TERRAIN_COMMON_H__

//
#include "../common.h"

//---------------------------------------------------------------------------------------
// ��ر���
//---------------------------------------------------------------------------------------
// ����Tile������Ϣ
float4	a_vTerrainQuadParam 	: ATTRIBUTE;
#define	a_vQuadOrigin			float2(a_vTerrainQuadParam[0], a_vTerrainQuadParam[1])
#define	a_fQuadScale			a_vTerrainQuadParam[2]
#define	a_fQuadMorphFactor		a_vTerrainQuadParam[3]

// ����һЩ��ͼ�ĳߴ�(���ڼ���UV)
float4	g_vTerrainMapSize		: GLOBAL;
#define g_fTerrainSize 			g_vTerrainMapSize.x
#define g_vTerrainSize 			g_vTerrainMapSize.xx
#define g_fBlendMapSize 		g_vTerrainMapSize.y
#define g_vBlendMapSize 		g_vTerrainMapSize.yy
#define g_fTileMapSize 			g_vTerrainMapSize.z
#define g_vTileMapSize 			g_vTerrainMapSize.zz

float4	g_vRecipTerrainMapSize	: GLOBAL;
#define g_fRecipTerrainSize 	g_vRecipTerrainMapSize.x
#define g_vRecipTerrainSize 	g_vRecipTerrainMapSize.xx
#define g_fRecipBlendMapSize 	g_vRecipTerrainMapSize.y
#define g_vRecipBlendMapSize 	g_vRecipTerrainMapSize.yy
#define g_fRecipTileMapSize 	g_vRecipTerrainMapSize.z
#define g_vRecipTileMapSize 	g_vRecipTerrainMapSize.zz

// ���ν���Զƽ��ķֽ���
float	g_fTerrainFarStart		: GLOBAL;

// Զ�����ش�С(���ڼ�������LOD)
float2 	g_vFarPixelSize			: GLOBAL;

// ���β�����Ϣ
float3 	g_vTerrainDiffuseMaterial	: GLOBAL;
float3 	g_vTerrainSpecularMaterial	: GLOBAL;
float	g_fTerrainShiness			: GLOBAL;

// Diffuse��ͼ����Ϣ
float4	g_vDiffuseAtlasTableParam	: GLOBAL;
#define g_fDiffuseAtlasIdScale		g_vDiffuseAtlasTableParam.x
#define g_fDiffuseAtlasIdOffset		g_vDiffuseAtlasTableParam.y
#define g_fDiffuseAtlasLevelScale	g_vDiffuseAtlasTableParam.z
#define g_fDiffuseAtlasLevelOffset	g_vDiffuseAtlasTableParam.w

// Normal��ͼ����Ϣ
float4	g_vNormalAtlasTableParam	: GLOBAL;
#define g_fNormalAtlasIdScale		g_vNormalAtlasTableParam.x
#define g_fNormalAtlasIdOffset		g_vNormalAtlasTableParam.y
#define g_fNormalAtlasLevelScale	g_vNormalAtlasTableParam.z
#define g_fNormalAtlasLevelOffset	g_vNormalAtlasTableParam.w

//
float3	g_vTerrainLODControl		: GLOBAL;
#define	g_fTerrainUseLightMap		g_vTerrainLODControl.x
#define	g_fTerrainUseSpecular		g_vTerrainLODControl.y

// ���Բ���
float2 	g_vTerrainDebugParams		: GLOBAL;
#define g_fTerrainShowInvisibleLayers	g_vTerrainDebugParams.x
#define g_fTerrainShowTileGrid			g_vTerrainDebugParams.y

//---------------------------------------------------------------------------------------
// ͼ������(����Diffuseͼ����Normalͼ��)
//---------------------------------------------------------------------------------------
float4 SamplerAtlasMap(sampler kAtlasMap, sampler kAtlasTable, float2 vTableUV, float2 vTerrainUV)
{
	// AtlasTable��������Ϣ:
	//	.x	LayerMap����ڵ��ε�����
	//	.y 	(�����)
	//	.zw	�ֱ���XY����LayerMap��PackedMap�����λ��(�Ѿ�����������ƫ��)
	//
	// ����ͼ�����ұ�
	float4 vTileInfo = tex2D(kAtlasTable, vTableUV);
	
	// ����ͼ����������
	float2 vAtlasTavleUV = frac(vTerrainUV * vTileInfo.x) * vTileInfo.y + vTileInfo.zw;
	
	// ������ͼ����ֵ
	return tex2D(kAtlasMap, vAtlasTavleUV);
}
//---------------------------------------------------------------------------------------
float4 SamplerAtlasMap_Planar(sampler kAtlasMap, sampler kAtlasTable, float2 vTableUV,
	float2 vTerrainUV_XY, float2 vTerrainUV_YZ,  float2 vTerrainUV_XZ, float3 vWeight)
{
	// ����ͼ�����ұ�
	float4 vTileInfo = tex2D(kAtlasTable, vTableUV);
	
	// ����ͼ����������
	float2 vAtlasTavleUV_XY = frac(vTerrainUV_XY * vTileInfo.x) * vTileInfo.y + vTileInfo.zw;
	float2 vAtlasTavleUV_YZ = frac(vTerrainUV_YZ * vTileInfo.x) * vTileInfo.y + vTileInfo.zw;
	float2 vAtlasTavleUV_XZ = frac(vTerrainUV_YZ * vTileInfo.x) * vTileInfo.y + vTileInfo.zw;
	
	// ������ͼ����ֵ
	return tex2D(kAtlasMap, vAtlasTavleUV_XY) * vWeight.z + 
		   tex2D(kAtlasMap, vAtlasTavleUV_YZ) * vWeight.x +
		   tex2D(kAtlasMap, vAtlasTavleUV_XZ) * vWeight.y;
}
//---------------------------------------------------------------------------------------
#endif