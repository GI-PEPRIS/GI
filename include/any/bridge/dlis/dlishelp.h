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
			string m_Name;// 曲线名称
			float m_StartIndex;// 起始索引
			float m_EndIndex;// 结束索引
			float m_DeltaIndex;// 索引间隔
			int m_Samples;// 每个索引点的数据个数
			int m_NumLev;// 索引采样数
			std::vector<int> m_Elements;// 每个维度的元素个数
			string m_Unit;// 曲线单位
			string m_IndexUnit;// 索引单位
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
