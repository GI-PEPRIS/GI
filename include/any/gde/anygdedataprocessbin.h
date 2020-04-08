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
	* ������Ԫ�ĸ����ࡣ����CDPSurvey��������һ��CDP����Ԫ����CDPSurvey���ص���Ԫ���������εġ�
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
		* ������Ԫ�Ĵ�С
		**/
		void SetBinSize(int lineCount,int CDPCount);

		/*!
		* ������Ԫ�еĵ���Ϣ
		**/
		void SetTraceOrder(int lineIndex,int CDPIndex, long traceOrder);

		/*!
		* ���ߵ�������ȡ��
		**/
		long GetTraceOrder(int lineIndex,int CDPIndex);

		/*!
		* ��ȡ��Ԫ���ĵ��ĵ����
		**/
		long GetCenterTrace();

		/*!
		* ��ȡ��Ԫ�в��ߵĸ���
		**/
		int GetLineCount();

		/*!
		* ��ȡ��Ԫ��ÿ�������ϵ�CDP����
		**/
		int GetCDPCount();

		/*!
		* ��ȡ��Ԫ���ܵ�CDP����
		**/
		int GetTotalCDPCount();

	private:
		//��Ԫ�е��߸���
		int m_lineCount;
		//��Ԫ�еĵ�����
		int m_CDPCount;

		//��Ԫ�ĵ���Ϣ
		long *m_sequenceOrders;
	};
}

#endif
