//*************************************************************************************************
// ����:		�ٽ���
//---------------------------------------------------------
// ����:		
// ����:		2012-07-16
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _CRITICAL_SECTION_H__
#define _CRITICAL_SECTION_H__

namespace Base
{
	// Win32�ٽ���(�ο���GB)
	class sdCriticalSection
	{
	public:
		sdCriticalSection()
		{
			::InitializeCriticalSection(&m_kCriticalSection);
		}

		~sdCriticalSection()
		{
			::DeleteCriticalSection(&m_kCriticalSection);
		}

		void Lock()
		{
			::EnterCriticalSection(&m_kCriticalSection);
		}

		void Unlock()
		{
			::LeaveCriticalSection(&m_kCriticalSection);
		}

	protected:
		CRITICAL_SECTION	m_kCriticalSection;
	};
}
#endif