//*************************************************************************************************
// ����: ���ڶ���һЩ�궨������������Base��ı�������(���ļ���ȡ��Ogre/OgreConfig.h)
//---------------------------------------------------------
// ����:	
// ����:		2012-08-04
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _SD_BASE_CONFIG_H__
#define _SD_BASE_CONFIG_H__

namespace Base
{
	// �����Ƿ����profile
	//	0 - �ʷֺ궨��Ϊ��
	//	1 - �ʷֺ궨��Ϊ�������ʷִ���
	#define SD_PROFILING 0

	// ���Ʋ�׽assert�ķ�ʽ
	//	0 - DebugģʽΪAssert��Release����ʾ
	//	1 - DebugģʽΪAssert��ReleaseģʽΪException
	//	2 - DebugģʽΪException�� Releaseģʽ��ΪException
	#define SD_ASSERT_MODE 0

	// �����Ƿ��¼log
	#define SD_LOG 1

	// �����ڴ������ʹ��
	//#define SD_MEMORY_ALLOCATOR

	// �����ڴ�ʹ�ø���
	//#define SD_MEMORY_TRACKER
}
#endif