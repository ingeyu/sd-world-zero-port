//*************************************************************************************************
// 内容:	渲染系统的GB-D3D9实现
//---------------------------------------------------------
// 作者:		喻强
// 创建:		2012-06-30
// 最后修改:
//*************************************************************************************************
#pragma once
#ifndef _RENDER_SYSTEM_DX9_H__
#define _RENDER_SYSTEM_DX9_H__
#include <sdRenderSystem.h>

namespace RenderSystem
{
	// 前置声明
	class sdRenderDevice;
	class sdRenderPath;

	// 渲染系统的D3D9实现
	class sdRenderSystem_DX9 : public sdRenderSystem
	{
	public:
		sdRenderSystem_DX9();
		virtual ~sdRenderSystem_DX9();

		//*************************************************
		// 虚函数继承
		virtual bool Initialize();
		virtual void Destroy();

		virtual inline void SetMap(sdMap* pkMap);
		virtual inline sdMap* GetMap();

		virtual inline void SetCamera(NiCamera* spCamera);
		virtual inline NiCamera* GetCamera();

		virtual void UpdateFrame(float fAccumTime, float fFrameTime);
		virtual void RenderFrame();
		virtual void DisplayFrame();

	protected:
		//@{
		// 绘制
		void DrawOpaqueUI();
		void DrawTranslucentUI();
		void DrawScene();
		//@}

		//@{
		// 构建缺省Mesh
		

		//@}

	protected:
		// 待渲染的地图
		sdMap*			m_pkMap;

		// 主相机,以及相关裁剪变量
		NiCameraPtr		m_spCamera;

		// 最终渲染目标,默认是缺省渲染目标
		NiRenderTargetGroupPtr	m_spRenderTargetGroup;

		// 渲染设备
		sdRenderDevice*	m_pkRenderDevice;

		// 渲染路径
		sdRenderPath*	m_pkRenderPath;


		//@{
		// 常用缺省渲染Mesh
		//m_spScreenQuadMesh
		//m_spUnitCubeMesh
		//m_spUnitSphereMesh
		//m_spUnitConeMesh
		//m_spUnitPyramidMesh

		// 常用缺省材质
		NiMaterialPtr		m_kDefaultMaterials[NUM_DEFAULT_MATERIALS];

		// 常用缺省纹理
		NiSourceTexturePtr	m_kDefaultTextures[NUM_DEFAULT_TEXTURES];
		//@}
	};
	#include "sdRenderSystem_DX9.inl"
}
#endif