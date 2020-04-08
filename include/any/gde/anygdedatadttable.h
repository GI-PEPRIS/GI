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
		* 查询指定时间对应的深度，返回负值表示不能确定该时间对应的深度
		**/
		double TimeToDepth(float time);

		/*!
		* 查询指定深度对应的时间，返回负值表示不能确定该深度对应的时间
		**/
		float DepthToTime(double depth);

	private:
		/*!
		* 由样点索引求对应深度
		**/
		double ConvertIndexToDepth(int index);

		/*!
		* 由深度求对应样点索引,返回值-1表示该深度小于所有样点深度，-2表示该深度大于所有样点深度
		**/
		int ConvertDepthToIndex(double depth);

		/*!
		* 由深度求对应样点索引,不考虑索引是否有效
		**/
		int ConvertDepthToIndexNoLimit(double depth);

		/*!
		*
		**/
		double Dither(double value,double dlt);
	private:
		//曲线第一个样点刻度（时间或深度）
		double m_sampleBase;
		//采样间隔
		double m_sampleInterval;
		// just reference
		double *m_samples;
		//
		int m_sampleCount;
	};
}

#endif
