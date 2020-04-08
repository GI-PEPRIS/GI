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
#ifndef __ANYBRIDGE_LOG_PICK_TRACK_H__
#define __ANYBRIDGE_LOG_PICK_TRACK_H__

// refer to EXPORT & IMPORT
#include "anybridge.h"

// refer to its parent
#include "anylogtrackcomponent.h"

#include "anybridgedatamodel.h"
#include "well/anyloglithtrack.h"

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyLogPickTrack : public CAnyLogTrackComponent
	{
	public:

		/*!
		*2017/5/18: differentiate from normal pick type to result data
		**/
		enum PickType
		{
			PT_Default = 0,
			PT_Result,
		};

		//
		//
		//
		/*!
		*
		**/
		struct WellPick
		{
			AnyWellPick m_pick;
			//CAnyLogLithTrack::VectorSymbol m_symbol;
			CAnyVectorSymbolPlot::VectorSymbol m_symbol;
		};
		typedef std::map<std::string,WellPick> WellPickMap;
		typedef std::map<std::string,WellPick>::iterator wpm_itr;
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyLogPickTrack();

		/*!
		*
		**/
		~CAnyLogPickTrack();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		//
		//
		//
		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		std::string FindWellPick(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		* return -1(not found) 0(top) 1(bottom)
		**/
		int FindWellPickEdge(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		bool RemoveWellPick(const std::string &name, bool isRelease = true);

		/*!
		*
		**/
		bool AdjustRectExtent(CGeoRect<double> &extent, bool adjustParaExtent = true, const std::string &exceptionName = "");

		//
		//
		//
		/*!
		*save/load
		**/
		unsigned char *DoEncoding(long long &length);

		
		/*!
		*2018/2/28: add parameter const long &len = 0
		**/
		bool DoDecoding(unsigned char* parameter, const long &len = 0);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderWellPick(CAnyCanvas &canvas, CAnyView &curView);

		/*!
		*
		**/
		void DoRenderWellPick(CAnyCanvas &canvas, CAnyView &curView, const CGeoRect<double> &theRect, WellPick &wellPick);

		
		/*!
		*
		**/
		void DoRenderTempWellPick(CAnyCanvas &canvas, CAnyView &curView);

	public:

		/*!
		*
		**/
		WellPickMap m_wellPickMap;
		std::string m_curWellPick;

		//for m_curView.Refresh(true)
		CGeoRect<double> m_tempRect;

		//2017/5/18: pick type
		int m_pickType;
	};
}
#endif