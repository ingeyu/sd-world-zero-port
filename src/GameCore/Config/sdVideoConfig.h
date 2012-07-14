//*************************************************************************************************
// 内容:	游戏显示配置管理
//---------------------------------------------------------
// 作者:		
// 创建:		2012-07-09
// 最后修改:
//*************************************************************************************************
#pragma once
#ifndef _VIDEO_CONFIG_H__
#define _VIDEO_CONFIG_H__
#include <NiMemObject.h>

// 读取游戏配置ini,获取当前的配置信息
class sdVideoConfig : public NiMemObject
{
public:
	sdVideoConfig();
	~sdVideoConfig();

	// 将当前配置初始化为对应类型配置
	//void InitLow();
	//void InitMid();
	//void InitHeight();
	//void InitBest();
	
public:
	unsigned int	m_uiWidth;
	unsigned int	m_uiHeight;
	bool			m_bVSync;
	bool			m_bFullScreen;

	// 
	unsigned int	m_uiMipmapSkipLevel;
};

#endif