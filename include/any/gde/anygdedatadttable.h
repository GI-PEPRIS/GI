/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
 *
 * Copyright (C) 2015 XIUJIE SHENG
 *
 * This library isn't a free software, so you cann't take the source code without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will not harm your computer or ongoing 
 * business if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Resource Faculty
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYGDE_SAMPLE_DATA_UTILITY_DT_TABLE__H__
#define __ANYGDE_SAMPLE_DATA_UTILITY_DT_TABLE__H__

// refer to EXPORT & IMPORT
#include "anygde.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataDTTable
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataDTTable(double base, double interval, double *samples, int sampleCount);

		/*!
		*
		**/
		~CAnyGdeDataDTTable();

	public:
		//
		//
		//
		/*!
		* ��ѯָ��ʱ���Ӧ����ȣ����ظ�ֵ��ʾ����ȷ����ʱ���Ӧ�����
		**/
		double TimeToDepth(float time);

		/*!
		* ��ѯָ����ȶ�Ӧ��ʱ�䣬���ظ�ֵ��ʾ����ȷ������ȶ�Ӧ��ʱ��
		**/
		float DepthToTime(double depth);

	private:
		/*!
		* �������������Ӧ���
		**/
		double ConvertIndexToDepth(int index);

		/*!
		* ��������Ӧ��������,����ֵ-1��ʾ�����С������������ȣ�-2��ʾ����ȴ��������������
		**/
		int ConvertDepthToIndex(double depth);

		/*!
		* ��������Ӧ��������,�����������Ƿ���Ч
		**/
		int ConvertDepthToIndexNoLimit(double depth);

		/*!
		*
		**/
		double Dither(double value,double dlt);
	private:
		//���ߵ�һ������̶ȣ�ʱ�����ȣ�
		double m_sampleBase;
		//�������
		double m_sampleInterval;
		// just reference
		double *m_samples;
		//
		int m_sampleCount;
	};
}

#endif
