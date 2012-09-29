//*************************************************************************************************
// ����:	������ͼ
//---------------------------------------------------------
// ����:		
// ����:		2012-06-29
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _SD_ENGINE_MAP_H__
#define _SD_ENGINE_MAP_H__
#include "sdGameObject.h"
#include "sdTerrain.h"
#include "sdLight.h"

// ��Ⱦϵͳ
#include "sdRenderSystem.h"


// ������ͼ
class sdMap : public sdGameObject
{
public:
	sdMap();
	~sdMap();


	// 
	bool	CreateScene();
	//void	DestroyScene();
	//bool	LoadScene();
	//bool	SaveScene(const std::string& szSceneFullPath);
	//bool	HasScene() { return m_bInitialized;};

	//*********************
	NiAVObjectPtr	m_pkRoot;
	//**********************

	// Entity����
	bool	AddEntity(sdEntity* pkEntity);
	bool	RemoveEntity(sdEntity* pkEntity);

	// ���Է���
	// @{
	// 
	sdTerrain*	GetTerrain() { return &m_kTerrain;};

	//
	NiNode*	GetDebugNode() const { return m_spDebugNode;}

	// �ƹ�
	sdLight* GetAmbientLight() const;
	sdLight* GetMainLight() const;
	sdLight* GetAssistantLight() const;

	// ��Ⱦ����
	const RenderSystem::sdRenderParams& GetRenderParams() const { return m_kRenderParams;};
	const RenderSystem::sdEnvironmentParams& GetEnvironmentParams() const { return m_kEnvironmentParams;};
	const RenderSystem::sdPostProcessParams& GetPostProcessParams() const { return m_kPostProcessParams;};
	// @}

protected:

protected:
	

	// ����ϵͳ
	sdTerrain	m_kTerrain;

	// �����ƹ�
	sdLightPtr	m_pkAmbientLight;
	sdLightPtr	m_pkMainLight;
	sdLightPtr	m_pkAssistantLight;


	// ���Ը��ڵ�
	NiNodePtr	m_spDebugNode;

	// �������Ʋ���(�����ṩ����Ⱦϵͳʹ��,�ڲ���Ӧ�ñ������ڴ�ͱ�����Դ)
	RenderSystem::sdRenderParams		m_kRenderParams;
	RenderSystem::sdEnvironmentParams	m_kEnvironmentParams;
	RenderSystem::sdPostProcessParams	m_kPostProcessParams;
};
NiSmartPointer(sdMap);
#include "sdMap.inl"
#endif