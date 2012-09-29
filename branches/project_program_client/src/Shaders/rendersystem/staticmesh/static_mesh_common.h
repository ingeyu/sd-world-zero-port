//*************************************************************************************************
// ����:	StaticMesh����ɫ�������еĹ��������뺯��
//---------------------------------------------------------
// ����:		
// ����:		2012-07-10
// ����޸�:
//*************************************************************************************************
#ifndef _STATICMESH_COMMON_H__
#define _STATICMESH_COMMON_H__

//
#include "../common.h"

// LightMap
float4	vLightMapChannel	: ATTRIBUTE	= float4(1.0f, 	0,	0,	0);
float4 	vLightMapTransform	: ATTRIBUTE	= float4(0, 	0,	1, 	1);

// DetailNormalMap�����������
float3	vDetailNormalScale			: ATTRIBUTE	= float3(1.0f, 1.0f, 1.0f);
float2	vDetailNormalUVTiling		: ATTRIBUTE = float2(5.0f, 5.0f);
float	fDetailNormalFadeDistance	: ATTRIBUTE = 30.0f;

// �ӳ���ɫ������������
SD_POINT_CLAMP_SAMPLE(0,	sdLightBufferSampler, 	sdTexLightBuffer, 	false);
SD_POINT_CLAMP_SAMPLE(1, 	sdGeomBufferSampler, 	sdTexGeomBuffer, 	false);
SD_POINT_CLAMP_SAMPLE(2, 	sdMatBufferSampler, 	sdTexMatBuffer, 	false);
SD_POINT_CLAMP_SAMPLE(2, 	sdMatBuffer0Sampler, 	sdTexMatBuffer0, 	false);
SD_POINT_CLAMP_SAMPLE(3, 	sdMatBuffer1Sampler, 	sdTexMatBuffer1, 	false);
SD_LINEAR_CLAMP_SAMPLE(3, 	curveFogBufferSampler, 	sdTexFogCurveMap, 	false);

#endif