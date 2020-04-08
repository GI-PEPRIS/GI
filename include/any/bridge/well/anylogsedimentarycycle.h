/*!
 * The AnyMap of PetroCOVERY Solution is a collection of native C++ classes that implement 
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
#ifndef __ANYBRIDGE_LOG_SEDIMENTARY_CYCLE_H__
#define __ANYBRIDGE_LOG_SEDIMENTARY_CYCLE_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to parent
#include "anylogtrackcomponent.h"

// 
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyLogSedimentaryCycle : public CAnyLogTrackComponent
	{
	public:
		//
		//set in main framework
		//
		struct CycleDescription
		{
			bool m_isPositive;
			PolyStyle m_style;
			CGeoRect<double> m_rect;
			double m_widthRate;
			int m_leanType;//2016/2/22: 0-center, 1-left, 2-right

			CycleDescription() : m_isPositive(true), m_widthRate(1.),m_leanType(0)
			{
			}
		};
		typedef std::vector<CAnyLogSedimentaryCycle::CycleDescription> CycleDescriptions;

		/*!
		*
		**/
		CAnyLogSedimentaryCycle();
		~CAnyLogSedimentaryCycle();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		/*!
		*
		**/
		bool AdjustRectExtent(CGeoRect<double> &extent, bool adjustParaExtent = true, int exceptionOrder = -1);

		/*!
		*
		**/
		int FindCycle(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		* return -1(not found) 0(top) 1(bottom)
		**/
		int FindCycleEdge(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		bool RemoveCycle(int order);

		//
		//2016/3/11: save/load
		//
		/*!
		*
		**/
		unsigned char *DoEncoding(long long &length);

		
		/*!
		*2018/2/28: add parameter const long &len = 0
		**/
		bool DoDecoding(unsigned char* parameter, const long &len = 0);
	private:
		/*!
		*
		**/
		void DoRenderSedimentaryCycle(CAnyCanvas &canvas, CAnyView &curView);

		/*!
		*
		**/
		void DoRenderTriangular(CAnyCanvas &canvas, CAnyView &curView, const CGeoRect<double>& rect, const PolyStyle &style, bool isPositive, double widthRate, int leanType);

		/*!
		*
		**/
		void DoRenderTempSedimentaryCycle(CAnyCanvas &canvas, CAnyView &curView);

	public:
		//
		CycleDescriptions m_cycles;
		int m_cycleOrder;
		CGeoRect<double> m_tempRect;//
	};
}
#endif