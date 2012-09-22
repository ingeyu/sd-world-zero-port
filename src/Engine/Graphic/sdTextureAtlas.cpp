#include "Stdafx.h"
#include "sdTextureAtlas.h"
#include "NiDX9TextureData.h"
#include "sdMath.h"

//
#include "NiDX9Direct3DTexture.h"
#include "NiDX9Direct3DTextureData.h"

namespace RenderSystem
{

uint sdTextureAtlas::ms_uiMaxTextureSize = 4096;
//-------------------------------------------------------------------------------------------------
// LevelInfo����������
bool sdTextureAtlas::LevelGreater(stLevelInfo* lhs, stLevelInfo* rhs)
{
	NIASSERT(lhs && rhs && lhs != rhs);

	// ���ȱȽϳߴ�(�ߴ�������)
	if (lhs->uiSize != rhs->uiSize)
		return lhs->uiSize > rhs->uiSize;

	// ��αȽ�Mipmap����(Mipmap�������)
	if (lhs->pkTexInfo->uiTotalPixels != rhs->pkTexInfo->uiTotalPixels)
		return lhs->pkTexInfo->uiTotalPixels > rhs->pkTexInfo->uiTotalPixels;

	// ���Ƚϵ�ַ
	return lhs->pkTexInfo->spTexture > rhs->pkTexInfo->spTexture;
}
//-------------------------------------------------------------------------------------------------
void sdTextureAtlas::GetCoordinate(uint uiNumAllAllocatedPixels, uint& uiX, uint& uiY)
{
	// ������һ��Z����
	static const uchar uiODDBits[256]	= {
		#define	OB1(n, m)	(n + m)
		#define OB2(n, m)	OB1(0, m),			OB1(1, m)
		#define OB3(n, m)	OB2(0, m + (n<<1)), OB2(1, m + (n<<1))
		#define OB4(n, m)	OB3(0, m),			OB3(1, m)
		#define OB5(n, m)	OB4(0, m + (n<<2)), OB4(1, m + (n<<2))
		#define OB6(n, m)	OB5(0, m),			OB5(1, m)
		#define OB7(n)		OB6(0, (n<<3)),		OB6(1, (n<<3))
		#define OB8(n)		OB7(0),				OB7(1)
		
		OB8(0), OB8(1),
	};

	static const uchar uiEvenBits[256]	= {
		#define EB1(n, m)	(m)
		#define EB2(n, m)	EB1(0, n + m),		EB1(1, n+m)
		#define EB3(n, m)	EB2(0, m),			EB2(1, m)
		#define EB4(n, m)	EB3(0, m + (n<<1)),	EB3(1, m + (n<<1))
		#define EB5(n, m)	EB4(0, m),			EB4(1, m)
		#define EB6(n, m)	EB5(0, m + (n<<2)),	EB5(1, m + (n<<2))
		#define EB7(n, m)	EB6(0, m),			EB6(1, m)
		#define EB8(n)		EB7(0, (n<<3)),		EB7(1, (n<<3))
				
		EB8(0), EB8(1),
	};

	uchar* ucPtr =  (uchar*)&uiNumAllAllocatedPixels;
	uiY = uiEvenBits[ucPtr[0]] + (uiEvenBits[ucPtr[1]] << 4) + (uiEvenBits[ucPtr[2]] << 8) + (uiEvenBits[ucPtr[3]] << 12);
	uiX = uiODDBits[ucPtr[0]] + (uiODDBits[ucPtr[1]] << 4) + (uiODDBits[ucPtr[2]] << 8) + (uiODDBits[ucPtr[3]] << 12);
}
//-------------------------------------------------------------------------------------------------
sdTextureAtlas::sdTextureAtlas(D3DFORMAT eFormat)
: m_eFormat(eFormat)
, m_uiAtlasSize(0)
, m_uiTotalPixels(0)
{
	// ��ȡ��Ⱦ�豸
	m_spRenderer = NiDX9Renderer::GetRenderer();
	NIASSERT(m_spRenderer);

	m_spD3DDevice = m_spRenderer->GetD3DDevice();

	// ����AtlasTexture��AtlasTable��GB����
	m_spAtlasTexture = NiDX9Direct3DTexture::Create(m_spRenderer);
	m_spAtlasTable	 = NiDX9Direct3DTexture::Create(m_spRenderer);

	m_spD3DAtlasTexture = NULL;
	m_spD3DAtlasTable = NULL;

	m_bAtlasDirty = false;
	m_bAtlasTextureDirty = false;
	m_bAtlasTableDirty = false;
	m_bAtlasTableTextureDirty = false;

}
//-------------------------------------------------------------------------------------------------
sdTextureAtlas::~sdTextureAtlas()
{

}
//-------------------------------------------------------------------------------------------------
uint sdTextureAtlas::AddTexture(NiTexture *spTexture, float fUVRepeat, float fMipmapBias,  uint uiNumLevel)
{
	return InsertTexture(m_kTextureInfoVec.size(), spTexture, fUVRepeat, fMipmapBias, uiNumLevel);
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::RemoveTexture()
{
	return RemoveTexture(m_kTextureInfoVec.size() - 1);
}
//-------------------------------------------------------------------------------------------------
uint sdTextureAtlas::InsertTexture(uint uiIndex, NiTexture *spTexture, float fUVRepeat, float fMipmapBias,  uint uiNumLevel)
{
	// ����������
	// @{
	if (uiIndex > m_kTextureInfoVec.size())	return -1;	
	if (NULL == spTexture)	return -1;
	if (fUVRepeat <= 0.0f)	return -1;

	// �����ͼ�Ƿ��Ѿ�����
	bool bExist = false;
	TextureInfoVecItr itr_tex = m_kTextureInfoVec.begin();
	TextureInfoVecItr itr_tex_end = m_kTextureInfoVec.end();
	for (; itr_tex != itr_tex_end; ++itr_tex)
	{
		if ((*itr_tex)->spTexture == spTexture)
		{
			bExist = true;
			break;
		}
	}

	// ��ȡD3D����,��������Ƿ�����Ҫ��
	//	1.��һ��D3D����
	//	2.��������һ���ڴ�����
	//	3.��������ʽ����ͼ����ͬ
	//	4.��������һ�ŷ�������
	//	5.�������ߴ�ΪPower(2,n)
	NiDX9TextureData* spDX9TextureData = (NiDX9TextureData*)spTexture->GetRendererData();
	IDirect3DTexture9* spD3DTexture = (IDirect3DTexture9*)spDX9TextureData->GetD3DTexture();
	
	if (NULL == spD3DTexture)	return -1;
	if (D3DRTYPE_TEXTURE != spD3DTexture->GetType())	return -1;

	D3DSURFACE_DESC kDesc;
	spD3DTexture->GetLevelDesc(0, &kDesc);
	if (kDesc.Format != m_eFormat)			return -1;
	if (D3DPOOL_SYSTEMMEM != kDesc.Pool)	return -1;
	if ((kDesc.Width != kDesc.Height) || !NiIsPowerOf2(kDesc.Width))	return -1;
	// @}

	// �½�����ҳ
	// @{
	// ����LOD����
	uint uiTexNumLevel = spD3DTexture->GetLevelCount();
	if (0 != uiNumLevel)
		uiNumLevel = min(uiNumLevel, uiTexNumLevel);
	else
		uiNumLevel = uiTexNumLevel;

	// �������Texture
	stTextureInfo* pkTexPageInfo = new stTextureInfo;
	NIASSERT(pkTexPageInfo);
	pkTexPageInfo->spTexture		= spTexture;

	pkTexPageInfo->spD3DTexture		= spD3DTexture;
	spD3DTexture->AddRef();

	pkTexPageInfo->fUVRepeat		= fUVRepeat;
	pkTexPageInfo->fMipmapBias		= fMipmapBias;

	for (uint i = 0; i < uiNumLevel; ++i)
	{
		IDirect3DSurface9* spD3DSurface;
		HRESULT hr = spD3DTexture->GetSurfaceLevel(i, &spD3DSurface);
		NIASSERT(SUCCEEDED(hr));

		D3DSURFACE_DESC kSurfaceDesc;
		hr = spD3DSurface->GetDesc(&kSurfaceDesc);
		NIASSERT(SUCCEEDED(hr));

		NIASSERT(kSurfaceDesc.Width >= 4);
		NIASSERT(NiIsPowerOf2(kSurfaceDesc.Width));
		NIASSERT(kSurfaceDesc.Width == kSurfaceDesc.Height);

		stLevelInfo kLevelInfo;
		kLevelInfo.uiSize		= kSurfaceDesc.Width;
		kLevelInfo.spD3DSurface = spD3DSurface;
		spD3DSurface->AddRef();
		kLevelInfo.pkTexInfo	= pkTexPageInfo;

		pkTexPageInfo->kLevelInfoVec.push_back(kLevelInfo);
		pkTexPageInfo->uiTotalPixels += kSurfaceDesc.Width * kSurfaceDesc.Height;
	}

	// ��������ܴ�С
	if (!bExist && m_uiTotalPixels + pkTexPageInfo->uiTotalPixels > ms_uiMaxTextureSize * ms_uiMaxTextureSize)
	{
		LevelInfoVecItr itr = pkTexPageInfo->kLevelInfoVec.begin();
		LevelInfoVecItr itr_end = pkTexPageInfo->kLevelInfoVec.end();
		for (; itr!=itr_end; ++itr)
		{
			itr->spD3DSurface->Release();
			itr->spD3DSurface = NULL;
		}

		pkTexPageInfo->spD3DTexture->Release();
		pkTexPageInfo->spD3DTexture = NULL;

		delete pkTexPageInfo;
		pkTexPageInfo = NULL;

		return -1;
	}

	m_uiTotalPixels += pkTexPageInfo->uiTotalPixels;
	// @}

	// ��������ҳ���б�
	// @{
	if (uiIndex == m_kTextureInfoVec.size())
	{
		m_kTextureInfoVec.push_back(pkTexPageInfo);
	}
	else
	{
		m_kTextureInfoVec.insert(m_kTextureInfoVec.begin() + uiIndex, pkTexPageInfo);
	}
	// @}

	//
	m_bAtlasDirty = true;
	m_bAtlasTableDirty = true;

	return uiIndex;
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::RemoveTexture(uint uiIndex)
{
	// ����������
	if (uiIndex >= m_kTextureInfoVec.size())	return false;	

	// �������������Ƿ������ͬ����������
	// @{
	bool bExistSame = false;
	for (uint i = 0; i < uiIndex; ++i)
	{
		if (m_kTextureInfoVec[i]->spTexture == m_kTextureInfoVec[uiIndex]->spTexture)
		{
			bExistSame = true;
			break;
		}
	}

	if (!bExistSame)
	{
		for (uint i = uiIndex+1; i < m_kTextureInfoVec.size(); ++i)
		{
			if (m_kTextureInfoVec[i]->spTexture == m_kTextureInfoVec[uiIndex]->spTexture)
			{
				bExistSame = true;
				break;
			}
		}
	}
	// @}

	// �Ƴ�����������ҳ
	// @{
	stTextureInfo* spTextureInfo = m_kTextureInfoVec[uiIndex];
	LevelInfoVecItr itr = spTextureInfo->kLevelInfoVec.begin();
	LevelInfoVecItr itr_end = spTextureInfo->kLevelInfoVec.end();
	for (; itr!=itr_end; ++itr)
	{
		itr->spD3DSurface->Release();
		itr->spD3DSurface = NULL;
	}

	spTextureInfo->spD3DTexture->Release();
	spTextureInfo->spD3DTexture = NULL;

	if (!bExistSame)
		m_uiTotalPixels -= spTextureInfo->uiTotalPixels;

	delete spTextureInfo;
	m_kTextureInfoVec.erase(m_kTextureInfoVec.begin() + uiIndex);

	// @}

	//
	m_bAtlasDirty = true;
	m_bAtlasTableDirty = true;

	return true;
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::Update()
{
	// �������AltasTexture,������AtlasTexture�б䶯,�����֮
	if (!UpdateAtlasAndTable())
		return false;

	// ������AtlasTexture��AtlasTableTexture��Ҫ���������֮
	if (!UpdateRenderTexture())
		return false;

	return true;
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::UpdateAtlasAndTable()
{
	// ��ǰ����Ϊ��
	if (0 == m_uiTotalPixels || m_kTextureInfoVec.empty())
		return true;

	// �����ǰ����AtlasTexture��������, ���²�������Mipmap��SurfaceAtlas
	if (m_bAtlasDirty)
	{
		// �������֮��Ӧ��ʹ�õ������ߴ�
		// (���˾��ü��㲻׼ȷ,Ӧ���ڳ��ȺͿ��������湲ͬ����,����Ӧ��������Page�Ĵ�С��������)
		uint uiAtlasSize = Base::Math::sdMath::Power2_Ceil((uint)ceilf(sqrt((float)m_uiTotalPixels)));
		NIASSERT(uiAtlasSize > 2 && uiAtlasSize <= ms_uiMaxTextureSize);

		m_uiAtlasSize = uiAtlasSize;

		// ��鵱ǰAtlasSurface�ߴ�,��ƥ�����������´���֮
		if (m_pkSurfaceAtlas && uiAtlasSize != m_pkSurfaceAtlas->GetWidth())
		{
			DestroyAtlasTexture();
			m_pkSurfaceAtlas = 0;
		}

		if (!m_pkSurfaceAtlas)
		{
			m_pkSurfaceAtlas =  NiNew RenderSystem::sdSurfaceAtlas(uiAtlasSize, uiAtlasSize, m_eFormat);
			NIASSERT(m_pkSurfaceAtlas);
		}

		// ����AtlasSurface����Tile
		m_pkSurfaceAtlas->DeallocAllTiles();

		// ���ҳ��ظ���Texture
		std::map<uint, uint> kRedirect;
		TextureInfoVecItr itr_tex = m_kTextureInfoVec.begin();
		TextureInfoVecItr itr_tex_begin = m_kTextureInfoVec.begin();
		TextureInfoVecItr itr_tex_end = m_kTextureInfoVec.end();
		for (; itr_tex != itr_tex_end; ++itr_tex)
		{
			stTextureInfo* spTexInfo = *itr_tex;

			TextureInfoVecItr itr_tex_inner = m_kTextureInfoVec.begin();
			for (; itr_tex_inner!= itr_tex; ++itr_tex_inner)
			{
				if ((*itr_tex_inner)->spTexture == spTexInfo->spTexture)
				{
					kRedirect.insert(std::make_pair(itr_tex - itr_tex_begin, itr_tex_inner - itr_tex_begin));
				}
			}
		}

		// ��ȡ��AtlasTexture������Mipmap(��ͬ��Texture������)
		typedef std::vector<stLevelInfo*> LevelInfoPtrVec;
		typedef std::vector<stLevelInfo*>::iterator LevelInfoPtrVecItr;
		LevelInfoPtrVec kAllLevelInfoPtrVec;
		itr_tex = m_kTextureInfoVec.begin();
		for (; itr_tex != itr_tex_end; ++itr_tex)
		{
			// ���ٴ����ظ���Texture
			if (kRedirect.find(itr_tex - itr_tex_begin) != kRedirect.end())
				continue;

			//
			stTextureInfo* pkTexInfo = *itr_tex;
			NIASSERT(pkTexInfo);
			NIASSERT(!pkTexInfo->kLevelInfoVec.empty());

			LevelInfoVecItr itr_level = pkTexInfo->kLevelInfoVec.begin();
			LevelInfoVecItr itr_level_end = pkTexInfo->kLevelInfoVec.end();
			for (; itr_level != itr_level_end; ++itr_level)
				kAllLevelInfoPtrVec.push_back(&(*itr_level));
		}

		// ����Mipmap
		sort(kAllLevelInfoPtrVec.begin(), kAllLevelInfoPtrVec.end(), sdTextureAtlas::LevelGreater);

		// ������Mipmap����SurfaceAtlas
		uint uiCurTotalAllocatedPixels = 0;
		LevelInfoPtrVecItr itr_level_ptr = kAllLevelInfoPtrVec.begin();
		LevelInfoPtrVecItr itr_level_ptr_end = kAllLevelInfoPtrVec.end();
		for (; itr_level_ptr != itr_level_ptr_end; ++itr_level_ptr)
		{
			stLevelInfo* spLevelInfo = *itr_level_ptr;
			NIASSERT(spLevelInfo);

			// ��������
			uint uiX, uiY;
			GetCoordinate(uiCurTotalAllocatedPixels, uiX, uiY);
		
			// ����,���ҵߵ�
			uint uiLeft = m_uiAtlasSize - uiX - spLevelInfo->uiSize;
			uint uiTop = m_uiAtlasSize - uiY - spLevelInfo->uiSize;

			// ���뵽SurfaceAtlas����
			spLevelInfo->uiLeft = uiLeft;
			spLevelInfo->uiTop	= uiTop;
			spLevelInfo->uiTileIndex = m_pkSurfaceAtlas->AllocTile(uiLeft, uiTop, spLevelInfo->uiSize, spLevelInfo->uiSize);
			m_pkSurfaceAtlas->BindSourceSurfaceToTile(spLevelInfo->uiTileIndex, spLevelInfo->spD3DSurface, 0, 0);
		}

		// Ϊ�ظ���Texture������Level���Index
		std::map<uint, uint>::iterator itr_map_ui2ui;
		for (itr_map_ui2ui = kRedirect.begin(); itr_map_ui2ui != kRedirect.end(); ++itr_map_ui2ui)
		{
			stTextureInfo* pkDstTexInfo = m_kTextureInfoVec[itr_map_ui2ui->first];
			LevelInfoVec& kDstLevelInfo = pkDstTexInfo->kLevelInfoVec;

			stTextureInfo* pkSrcTexInfo = m_kTextureInfoVec[itr_map_ui2ui->second];
			LevelInfoVec& kSrcLevelInfo = pkSrcTexInfo->kLevelInfoVec;
	
			for (uint i = 0; i < kSrcLevelInfo.size(); ++i)
			{
				kDstLevelInfo[i].uiTileIndex = kSrcLevelInfo[i].uiTileIndex;
				kDstLevelInfo[i].uiLeft = kSrcLevelInfo[i].uiLeft;
				kDstLevelInfo[i].uiTop = kSrcLevelInfo[i].uiTop;
			}
		}

		//
		m_bAtlasDirty = false;
		m_bAtlasTextureDirty = true;
	}	

	// �������AtlasTable��������
	if (m_bAtlasTableDirty)
	{
		int iMinLodOffset = 1000;
		int iMaxLodOffset = -1000;
		TextureInfoVecItr itr_tex = m_kTextureInfoVec.begin();
		TextureInfoVecItr itr_tex_end = m_kTextureInfoVec.end();
		for (; itr_tex != itr_tex_end; ++itr_tex)
		{
			stTextureInfo* pkTexInfo = *itr_tex;
			stLevelInfo* pkLevelInfo = &pkTexInfo->kLevelInfoVec[0];

			int iLodOffset = (int)(log(pkLevelInfo->uiSize / pkTexInfo->fUVRepeat) / log(2.0f) + pkTexInfo->fMipmapBias);
			
			iMinLodOffset = min(iMinLodOffset, iLodOffset);
			iMaxLodOffset = max(iMaxLodOffset, iLodOffset);
		}

		// 
		int iMaxMipmapLod = 6;
		int iMinLodFactor = 0;
		int iMaxLodFactor = iMaxMipmapLod;

		iMinLodFactor = 0 - iMaxLodFactor;
		iMaxLodFactor = iMaxMipmapLod - iMinLodFactor;

		//
		m_kTableInfo.uiTextureCount = m_kTextureInfoVec.size();
		m_kTableInfo.uiLevelCount = iMaxMipmapLod;
	
		// ����AtlasTable�����ߴ�,��鵱ǰAtlasTable�ߴ�,��ƥ�����������´���֮
		uint uiWidth = Base::Math::sdMath::Power2_Ceil(m_kTableInfo.uiTextureCount);
		uint uiHeight = Base::Math::sdMath::Power2_Ceil(iMaxLodFactor - iMinLodFactor + 1) * 4;
		if (uiWidth != m_kTableInfo.uiWidth || uiHeight != m_kTableInfo.uiHeight)
		{
			DestroyAtlasTableTexture();
			
			m_kTableInfo.uiWidth = uiWidth;
			m_kTableInfo.uiHeight = uiHeight;
		}

		// (����Shader����ʱʹ��)
		m_kTableInfo.vTexId2U[0] = 1.0f / uiWidth;
		m_kTableInfo.vTexId2U[1] = 0.5f / uiWidth;
		m_kTableInfo.vLevel2V[0] = 1.0f / uiHeight;
		m_kTableInfo.vLevel2V[1] = -iMinLodFactor / (float)uiHeight;

		//
		m_bAtlasTableDirty = false;
		m_bAtlasTableTextureDirty = true;
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::UpdateRenderTexture()
{
	// �豸��ʧ��ֱ�ӷ���
	if (m_spRenderer->IsDeviceLost())
		return true;

	// AtlasTexture����
	// @{
	// ���������б�Ϊ����ֱ�ӷ���
	if (0 == m_uiTotalPixels || m_kTextureInfoVec.empty())
		return true;

	// ���AtlasTexture��D3D������Ϊ��,�ҷ���״ֱ̬�ӷ���
	if (!m_bAtlasTextureDirty && NULL != m_spD3DAtlasTexture)
		return true;

	// ���AtlasTexture��D3D�����������򴴽�֮
	if (NULL == m_spD3DAtlasTexture)
	{
		if (!CreateAtlasTexture())
			return false;
	}

	// ����ƴ�Ӵ��������AtlasTexture
	m_pkSurfaceAtlas->UpdateTargetSurface();
	// @}

	// AtlasTable����
	// @{
	// ���AtlasTable��D3D������Ϊ��,�ҷ���״ֱ̬�ӷ���
	if (!m_bAtlasTableTextureDirty && NULL != m_spD3DAtlasTable)
		return true;

	// ���AtlasTable��D3D�����������򴴽�֮
	if (NULL == m_spD3DAtlasTable)
	{
		if (!CreateAtlasTableTexture())
			return false;
	} 

	// ����������AtlasTable
	D3DLOCKED_RECT kLockedRect;
	HRESULT hr = m_spD3DAtlasTable->LockRect(0, &kLockedRect, 0, D3DLOCK_DISCARD);
	NIASSERT(SUCCEEDED(hr));

	float* pfDataLine = (float*)kLockedRect.pBits;
	for (uint y = 0; y < m_kTableInfo.uiHeight; ++y)
	{
		float* pfDataPixel = pfDataLine;
		for (uint x = 0; x < m_kTableInfo.uiWidth; ++x)
		{
			// ��ȡ��ǰ����(Ϊ��power(2,n)��������ĳ�������ʹ�����һҳ)
			stTextureInfo* pkTexInfo = m_kTextureInfoVec[min(x, m_kTableInfo.uiTextureCount -1)];

			// ���㵱ǰLOD
			float fLodOffset = log(pkTexInfo->kLevelInfoVec[0].uiSize / pkTexInfo->fUVRepeat) / log(2.0f);
			float fLodFactor = (((float)y) / m_kTableInfo.uiHeight - m_kTableInfo.vLevel2V[1]) / m_kTableInfo.vLevel2V[0];
			int iLevel = (int)(fLodFactor + fLodOffset + pkTexInfo->fMipmapBias);
			uint uiLevel = NiClamp(iLevel, 0, pkTexInfo->kLevelInfoVec.size());

			// ��ȡTile����Ϣ������
			stLevelInfo* pkLevel = &pkTexInfo->kLevelInfoVec[uiLevel];
			NIASSERT(-1 == pkLevel->uiTileIndex);

			pfDataPixel[0] = 1.0f / pkTexInfo->fUVRepeat;
			pfDataPixel[1] = ((float)pkLevel->uiSize - 1.0f) / (float)m_pkSurfaceAtlas->GetWidth();
			pfDataPixel[2] = ((float)pkLevel->uiLeft + 0.5f) / (float)m_pkSurfaceAtlas->GetWidth();
			pfDataPixel[3] = ((float)pkLevel->uiTop +  0.5f) / (float)m_pkSurfaceAtlas->GetHeight();

			// ��һ������
			pfDataPixel += 4;
		}

		// ��һ��
		pfDataLine += kLockedRect.Pitch;
	}

	m_spD3DAtlasTable->UnlockRect(0);
	m_bAtlasTableTextureDirty = false;
	// @}

	return true;
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::CreateAtlasTexture()
{
	if (!m_spD3DAtlasTexture)
		return false;

	// ����AtlasTexture��D3D,�����
	HRESULT hr = m_spD3DDevice->CreateTexture(m_uiAtlasSize, m_uiAtlasSize, 1, D3DUSAGE_DYNAMIC, m_eFormat, D3DPOOL_DEFAULT, &m_spD3DAtlasTexture, 0);
	if (FAILED(hr))
		return false;

	D3DLOCKED_RECT kLockedRect;
	m_spD3DAtlasTexture->LockRect(0, &kLockedRect, NULL, 0);
	ZeroMemory(kLockedRect.pBits, m_uiAtlasSize * m_uiAtlasSize);
	m_spD3DAtlasTexture->UnlockRect(0);

	// �󶨵�AtlasTexture
	NiDX9Direct3DTextureData::Create((NiDX9Direct3DTexture*)(NiTexture*)m_spAtlasTexture, m_spRenderer, m_spD3DAtlasTexture);

	// �󶨵�AtlasSurface
	IDirect3DSurface9* spD3DAtlasSurface;
	m_spD3DAtlasTexture->GetSurfaceLevel(0, &spD3DAtlasSurface);
	if (!m_pkSurfaceAtlas->BindTargetSurface(spD3DAtlasSurface))
		return false;

	return true;
}
//-------------------------------------------------------------------------------------------------
void sdTextureAtlas::DestroyAtlasTexture()
{
	if (m_spD3DAtlasTexture)
	{
		// ��AtlasSurface���
		m_pkSurfaceAtlas->UnbindTargetSurface();

		// ��AtlasTexture���
		NiDX9TextureData* spDX9TextureData = (NiDX9TextureData*)m_spAtlasTexture->GetRendererData();
		if (spDX9TextureData)
		{
			m_spAtlasTexture->SetRendererData(NULL);
			NiDelete spDX9TextureData;
		}

		// ����AtlasTexture��D3D����
		m_spD3DAtlasTexture->Release();
		m_spAtlasTexture = NULL;
	}
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::CreateAtlasTableTexture()
{
	if (!m_spD3DAtlasTable)
		return false;

	// ����AtlasTable��D3D
	HRESULT hr = m_spD3DDevice->CreateTexture(m_kTableInfo.uiWidth, m_kTableInfo.uiHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &m_spD3DAtlasTable, 0);
	if (FAILED(hr))
		return false;

	// �󶨵�AtlasTable
	NiDX9Direct3DTextureData::Create((NiDX9Direct3DTexture*)(NiTexture*)m_spAtlasTable, m_spRenderer, m_spD3DAtlasTable);

	return true; 
}
//-------------------------------------------------------------------------------------------------
void sdTextureAtlas::DestroyAtlasTableTexture()
{
	if (m_spD3DAtlasTable)
	{
		// ��AtlasTable���
		NiDX9TextureData* spDX9TextureData = (NiDX9TextureData*)m_spAtlasTable->GetRendererData();
		if (spDX9TextureData)
		{
			m_spAtlasTable->SetRendererData(NULL);
			NiDelete spDX9TextureData;
		}

		// ����AtlasTable��D3D����
		m_spD3DAtlasTable->Release();
		m_spD3DAtlasTable = NULL;
	}
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::OnDeviceLost()
{
	DestroyAtlasTexture();
	DestroyAtlasTableTexture();
	return true;
}
//-------------------------------------------------------------------------------------------------
bool sdTextureAtlas::OnDeviceReset(bool bBefore)
{
	if (bBefore)
	{
		// �豸����ǰ
		DestroyAtlasTexture();
		DestroyAtlasTableTexture();
		return true;
	}
	else
	{
		// �豸�Ѿ�����
		UpdateRenderTexture();
		return true;
	}
}
//-------------------------------------------------------------------------------------------------
}