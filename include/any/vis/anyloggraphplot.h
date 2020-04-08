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
#ifndef __ANYVIS_LOG_GRAPH_PLOT_H__
#define __ANYVIS_LOG_GRAPH_PLOT_H__

// refer to macro
#include "anyscattermatrix.h"
using namespace AnyVis;


namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyLogGraphPlot : public CAnyScatterMatrix
	{
	public:
		enum CanvasType
		{
			CT_POST_DRILL = 0,
			CT_REAL_TIME,

			//2019/3/26 CM graph
			CT_CM_GRAPH,
		};

	public:
		//
		//
		//
		/*!
		*
		*/
		CAnyLogGraphPlot(CAnyView &curView, int canvasType = CT_POST_DRILL);

		/*!
		*
		*/
		~CAnyLogGraphPlot();

	public:
		
		//
		//
		//
		/*!
		*
		*/
		void Clone(const CAnyViewHook *prototype);

		//
		//
		//
		/*!
		*
		*/
		void SetShownAxisName(const std::string & actualStr, const std::string & predictedStr);

		//
		//
		//
		/*!
		*
		*/
		void SetAxisNames(const std::string &top, const std::string &bottom, const std::string &left, const std::string &right);

		/*!
		*2016/7/18
		*/
		void GetAxisNames(std::string &top, std::string &bottom, std::string &left, std::string &right, std::string & actualStr, std::string & predictedStr);

		/*!
		*2016/11/14
		*/
		void SetXAxisFormat(bool isInteger = false);
	private:
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

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderBorders(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderGridLineAndTick(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderLines(CAnyCanvas &canvas);

		/*!
		*
		**/
		std::string GetTickString(const char* str);
				
		/*!
		*
		**/
		void SetAxisExtent();

		/*!
		*
		**/
		void DoRenderPoints(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderRealTimePoints(CAnyCanvas &canvas, int num, ScatterElement * xelement, ScatterElement * yelement);

		/*!
		*
		**/
		void DoRenderRealTimeLegend(CAnyCanvas &canvas);

		//
		//2016/12/30: pick points in polygon
		//
		/*!
		*
		**/
		void DoPickPoints(const std::vector<CGeoPoint<double> > &polygon);

	private:
		//variables
		std::string m_predictedStr;
		std::string m_actualStr;

		std::vector<CGeoRect <double>> m_nameRectPositions;

		//2015/6/8
		int m_canvasType;

		//four axis names
		std::string m_topStr;
		std::string m_bottomStr;
		std::string m_leftStr;
		std::string m_rightStr;

		//2016/11/14
		bool m_isInteger;
	};
}
#endif