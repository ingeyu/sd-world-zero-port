//*************************************************************************************************
// ����:	�ر���Դͼ��
//---------------------------------------------------------
// ����:		
// ����:		2012-08-11
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _TERRAIN_LAYER_MAP_H__
#define _TERRAIN_LAYER_MAP_H__
#include "sdEngine.h"
#include "sdMemoryTexture.h"

// ��ʾ�ر�һ����Դ��ͼ(�����ڱ༭��״̬��ʹ��,�൱��Cry��SSurfaceType)
class sdLayerMap : public NiRefObject
{
public:
	sdLayerMap(const std::string& szName, const std::string& szDiffuseMap, 
		const std::string& szNormalMap, float fRepeatSize = 1.0f, float fMipmapBias = 0.0f);
	~sdLayerMap();

	//
	const std::string&	GetName() const { return m_szName;}
	void				SetName(const std::string& szName) {m_szName = szName;}

	const std::string&	GetDiffuseMapPath() const { return m_szDiffuseMap;}
	void				SetDiffuseMapPath(const std::string& szName);

	const std::string&	GetNormalMapPath() const { return m_szNormalMap;}
	void				SetNormalMapPath(const std::string& szName);

	NiTexture*	GetDiffuseMap() { return m_pkDiffuseMap ? m_pkDiffuseMap->GetGBTexture() : NULL;}
	NiTexture*	GetNormalMap() { return m_pkNormalMap ? m_pkDiffuseMap->GetGBTexture() : NULL;}

	float	GetRepeatSize() const { return m_fRepeatSize;}
	void	SetRepeatSize(float fRepeatSize) { m_fRepeatSize = fRepeatSize; }

	float	GetMipmapBias() const { return m_fMipmapBias;};
	void	SetMipmapBias(float fMipmapBias) { m_fMipmapBias = fMipmapBias; }

protected:
	// �������ݵ�Texture
	RenderSystem::sdMemoryTexturePtr LoadPixelDataToD3DTexture(const char* szName);

protected:
	// ͼ����
	std::string		m_szName;			

	// ͼ������
	std::string		m_szDiffuseMap;	
	std::string		m_szNormalMap;
	RenderSystem::sdMemoryTexturePtr	m_pkDiffuseMap;
	RenderSystem::sdMemoryTexturePtr	m_pkNormalMap;

	// ͼ����Ϣ
	float	m_fRepeatSize;
	float	m_fMipmapBias;
};
NiSmartPointer(sdLayerMap);
#endif