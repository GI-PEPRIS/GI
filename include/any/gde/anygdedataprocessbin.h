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
#ifndef __ANYGDE_SAMPLE_DATA_UTILITY_PROCESS_BIN_H__
#define __ANYGDE_SAMPLE_DATA_UTILITY_PROCESS_BIN_H__

// refer to EXPORT & IMPORT
#include "anygde.h"

//
namespace AnyGDE
{
	/*!
	* 反演面元的辅助类。可向CDPSurvey对象请求一个CDP的面元，从CDPSurvey返回的面元总是正方形的。
	**/
	class ANYGDE_CLASS CAnyGdeDataProcessBin
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataProcessBin();

		/*!
		*
		**/
		~CAnyGdeDataProcessBin();

	public:
		//
		//
		//
		/*!
		* 设置面元的大小
		**/
		void SetBinSize(int lineCount,int CDPCount);

		/*!
		* 设置面元中的道信息
		**/
		void SetTraceOrder(int lineIndex,int CDPIndex, long traceOrder);

		/*!
		* 按线道索引获取道
		**/
		long GetTraceOrder(int lineIndex,int CDPIndex);

		/*!
		* 获取面元中心道的道序号
		**/
		long GetCenterTrace();

		/*!
		* 获取面元中测线的个数
		**/
		int GetLineCount();

		/*!
		* 获取面元中每条测线上的CDP个数
		**/
		int GetCDPCount();

		/*!
		* 获取面元中总的CDP个数
		**/
		int GetTotalCDPCount();

	private:
		//面元中的线个数
		int m_lineCount;
		//面元中的道个数
		int m_CDPCount;

		//面元的道信息
		long *m_sequenceOrders;
	};
}

#endif
