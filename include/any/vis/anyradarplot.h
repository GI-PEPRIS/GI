/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYVIS_RADAR_H__
#define __ANYVIS_RADAR_H__

// refer to macro
#include "anyvis.h"

#include "anyscattermatrix.h"

// refer to geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyRadarPlot  : public CAnyScatterMatrix
	{
	public:
		/*!
		*max value for radar
		**/
		typedef std::map<std::string,double> MaxValueMap;
		typedef MaxValueMap::iterator nm_itr;

		//2015/7/2
		enum CanvasType
		{
			CT_Radar = 0,
			CT_Rose,
		};

		//2015/7/2
		typedef std::map<double,int> RoseStatMap;
		typedef RoseStatMap::iterator rsm_itr;
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyRadarPlot(CAnyView &curView, int canvasType = CT_Radar);

		/*!
		*
		**/
		virtual ~CAnyRadarPlot();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		//
 		//
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

		//
		//
		//
		/*!
		*
		**/
		bool IsDataLegal();

		/*!
		*
		**/
		void SetDimsMaxValue(const MaxValueMap &maxValMap);

		/*!
		*
		**/
		const ScatterElement &GetGridSetting();

		/*!
		*
		**/
		void SetGridSetting(const ScatterElement &setting);

		/*!
		*
		**/
		static void InitGridSetting(ScatterElement &setting);

	private:
		/*!
		*
		**/
		void GetDimsMaxValue(MaxValueMap &maxValMap, bool isAll = true);		

		/*!
		*
		**/
		void RenderCutoffAndBorderLine(CAnyCanvas &canvas, CGeoPoint<double> &baseMapPt, double mapRadius, double eachDegree);

		/*!
		*
		**/
		void RenderSampleLines(CAnyCanvas &canvas, CGeoPoint<double> &baseMapPt, double mapRadius, double eachDegree);

		/*!
		*
		**/
		void RenderLegend(CAnyCanvas &canvas);

	private:
		//
		MaxValueMap m_maxValMap;
		int m_groupCount;

		//
		MaxValueMap m_directMaxValMap;
		MaxValueMap m_shownMaxValMap;

		//2015/3/13:grid setting
		ScatterElement m_gridSetting;

		//2015/7/2
		int m_canvasType;
		RoseStatMap m_roseStatMap;
		RoseStatMap m_roseColorMap;
		double m_roseMaxStatValue;
	};
}
#endif