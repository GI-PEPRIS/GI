/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_DLISHELP_H__
#define __ANYBRIDGE_DLISHELP_H__

// refer to EXPORT and IMPORT
#include "..\anybridge.h"
#include "dlisread.h"

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CDlisHelp
	{		
	public:
		struct Curve
		{
			string m_Name;// ��������
			float m_StartIndex;// ��ʼ����
			float m_EndIndex;// ��������
			float m_DeltaIndex;// �������
			int m_Samples;// ÿ������������ݸ���
			int m_NumLev;// ����������
			std::vector<int> m_Elements;// ÿ��ά�ȵ�Ԫ�ظ���
			string m_Unit;// ���ߵ�λ
			string m_IndexUnit;// ������λ
			Curve()
			{
			}
			const Curve &operator=(const Curve &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_Name = other.m_Name;
				m_StartIndex = other.m_StartIndex;
				m_EndIndex = other.m_EndIndex;
				m_DeltaIndex = other.m_DeltaIndex;
				m_Samples = other.m_Samples;
				m_NumLev = other.m_NumLev;
				m_Elements = other.m_Elements;
				m_Unit = other.m_Unit;
				m_IndexUnit = other.m_IndexUnit;
				return *this;								
			}
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CDlisHelp();

		/*!
		*
		**/
		~CDlisHelp();
	public:
		
		/*!
		*
		**/
		void SetFile(string fileName);
		int GetFileNumbers();
		void SetFileNum(int num);
		std::vector<CDlisHelp::Curve> GetCurveList();
		float* GetCurveValue(int i);
		CDlisHelp::Curve CreatCurve(int index);

	public:
		CDlisRead *m_dlisRead;
	};
}

#endif
