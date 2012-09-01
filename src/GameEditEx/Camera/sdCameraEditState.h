//*************************************************************************************************
// ����:	�༭״̬�����״̬(��ʱ���뷽ʽ��ͬ)
//---------------------------------------------------------
// ����:		
// ����:		2012-08-27
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _SD_GAMEEDITEX_EDITCAMERA_H__
#define _SD_GAMEEDITEX_EDITCAMERA_H__
#include "sdGameEditEx.h"
#include <sdCameraState.h>

namespace GameEditEx
{
	//*************************************************************************
	// �༭״̬�µ����
	class sdEditCameraState : public GameCore::sdCameraState
	{
	public:
	public:
		// �������ģʽ(�༭״̬)
		enum eEditCameraMode
		{
			E_EDIT_CAMERA_FREE = NUM_CAMERA_MODE + 1,	// �������ģʽ
			NUM_EDIT_CAMERA_MODE,
		};

	public:
		sdEditCameraState() {};
		virtual ~sdEditCameraState() {};

		// ������Ϣ
		// @{
		virtual void OnKeyDown(WPARAM wParam, LPARAM lParam){};
		virtual void OnKeyUp(WPARAM wParam, LPARAM lParam){};
		virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam){};
		virtual void OnMouseMove(WPARAM wParam, LPARAM lParam){};
		virtual void OnLeftButtonDown(WPARAM wParam, LPARAM lParam){};
		virtual void OnLeftButtonUp(WPARAM wParam, LPARAM lParam){};
		virtual void OnRightButtonDown(WPARAM wParam, LPARAM lParam){};
		virtual void OnRightButtonUp(WPARAM wParam, LPARAM lParam){};
		// @}
	};

	//*************************************************************************
	// �༭״̬�µ��������
	class sdEditFreeCameraState : public sdEditCameraState
	{
	public:
		sdEditFreeCameraState();

		// �麯���̳�
		virtual int Update();

		virtual void OnKeyDown(WPARAM wParam, LPARAM lParam);
		virtual void OnKeyUp(WPARAM wParam, LPARAM lParam);
		virtual void OnMouseMove(WPARAM wParam, LPARAM lParam);
		virtual void OnRightButtonDown(WPARAM wParam, LPARAM lParam);
		virtual void OnRightButtonUp(WPARAM wParam, LPARAM lParam);

	protected:
		bool m_bMoveForward;
		bool m_bMoveBack;
		bool m_bMoveLeft;
		bool m_bMoveRight;
		bool m_bRightButtonDown;
		int m_iX, m_iY, m_iLastX, m_iLastY;

		float m_fFreeCameraSpeed;
		float m_fFreeCameraRotate;
	};
}
#endif