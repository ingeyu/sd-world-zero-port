//*************************************************************************************************
// ����:	�ر��߶�ͼ
//---------------------------------------------------------
// ����:		
// ����:		2012-08-01
// ����޸�:
//*************************************************************************************************
#pragma once
#ifndef _TERRAIN_HEIGHT_MAP_H__
#define _TERRAIN_HEIGHT_MAP_H__
#include "sdTypes.h"

// �ر��߶�ͼ,������������,��С������pow(2,n)����λ
//
// ����ϵ:	GBĬ����������ϵ,����ΪX,��ǰΪY,����ΪZ
//
// Ĭ�ϸ߶�ͼ��(0,0,0)�㿪ʼ��XY����������
//
class sdHeightMap : public NiRefObject
{
public:
	sdHeightMap(uint uiSize);
	~sdHeightMap();


	// ���Է���
	uint	GetSize() const { return m_uiSize;};

	// �߶�(�߶�ͼ��������,ԭʼ�߶�)
	void	SetRawHeight(uint uiX, uint uiY, float fHeight);
	float	GetRawHeight(uint uiX, uint uiY);

	// ����(�߶�ͼ��������,��ֵ����)
	void	GetNormal(uint uiX, uint uiY, float& fNX, float& fNY, float& fNZ);

	// �߶�(��ֵ)/����/�¶�
	//float		GetHeight(float fX, float fY);
	//NiPoint3	GetGradients(float fX, float fY);

	// ��ȡLOD�μ��ֲ�������LOD��ϸ��������ָ�����괦���ֵ(���һ��)
	// (Ϊ�����Ч��,����û�м���������)
	//
	//	uiX,uiY		�߶�ͼ��������
	//	uiSpacing	��ϸ������������С,Ӧ������power(2,n)
	float	GetMorphDelta(uint uiX, uint uiY, uint uiSpacing);

protected:
	//NiPoint3	m_kOrigin;			// �߶�ͼ��ʼλ��������(������ʾЧ��)
	//float		m_fScale;
	//float		m_fHorizontalScale;	// ˮƽ����
	//float		m_fVerticalScale;	// ��ֱ����,���߱�(��ʾʱ�߶ȿ��ű���)
	//int		m_iSpacing;			// �߶�ͼ������(Cry�д˲���)
	//float		m_fBaseHeight;		// �߶�ͼ��׼�߶�

	// �߶�ͼ����(���Ǿ�ȷ��ʽ,���Կ���ѹ��Ϊunsigned short)
	float	*m_pfHeight;

	// �߶�ͼ�߳���С
	uint	m_uiSize;		// pow(2,n)
	uint	m_uiAllocSize;	// pow(2,n) + 1

	// �������С�߶�,ѹ������ʱʹ��
	float	m_fMinHeight;
	float	m_fMaxHeight;

	// �߶ȶ��뵥λֵ
	// (��ʱ��Ⱦ��������Ҫѹ���������ݶ�ʹ�ö��㸡����)
	float	m_fAlignedHeight;
};
NiSmartPointer(sdHeightMap);

#endif