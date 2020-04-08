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
#ifndef __ANYVIS_TERNARY_H__
#define __ANYVIS_TERNARY_H__

// refer to macro
#include "anyvis.h"

// refer to its parent
#include "anyrockphysicalternaryplot.h"

// refer to geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;



//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyTernaryPlot  : public CAnyRockPhysicalTernaryPlot
	{
	public:
		/*!
		*2017/3/31: ternary type
		**/
		enum TernaryType
		{
			TT_Normal = 0,
			TT_TOC,//only render 50%, 25%,10% line
		};
		
		/*!
		*2017/4/13: ternary point
		**/
		struct TernaryPoint
		{
			//name
			std::string m_name;

			//pt
			CGeoPoint<double> m_3dPt;
			CGeoPoint<double> m_2dPt;

			//property
			CAnyScatterMatrix::ScatterElement m_element;
		};
		typedef std::vector<TernaryPoint> TernaryPoints;

		/*!
		*
		**/
		struct ContourSetting
		{
			//color
			unsigned int m_minColor;
			unsigned int m_midColor;
			unsigned int m_maxColor;

			//z value
			double m_minZ;
			double m_maxZ;

			//< threshold, donnot paint
			double m_threshold;

			//flag of rendering contour grid/ line/ legend
			bool m_isRenderContourGrid;
			bool m_isRenderContourLegend;
			bool m_isRenderContourLine;
			
			//contour line related
			double m_interval;
			int m_lineColor;
			int m_lineStyle;
			double m_lineWidth;

			//2017/6/1: contour line's label size
			double m_labelSize;


			//flag of rendering cutoff line 
			bool m_isRenderCutoffLine;			

			//
			ContourSetting()
			{
				m_minColor = RGB(255,0,0);
				m_midColor = RGB(255,255,0);
				m_maxColor = RGB(0,255,0);

				m_minZ = 0x7fffffff;
				m_maxZ = -0x7fffffff;

				m_threshold = 0.;

				//
				m_isRenderContourGrid = true;
				m_isRenderContourLine = true;
				m_isRenderContourLegend = true;

				//
				m_interval = 5.;
				m_lineColor = RGB(0,0,0);
				m_lineStyle = 0;
				m_lineWidth = 1.;

				//
				m_isRenderCutoffLine = true;

				//
				m_labelSize = 11.;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyTernaryPlot(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyTernaryPlot();

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
		void SetTernaryName(const std::string &ternaryA = "A", const std::string &ternaryB = "B", const std::string &ternaryC = "C");
		
		//
		//2017/3/31
		//
		/*!
		*
		**/
		void SetTernaryType(int type);

		/*!
		*
		**/
		int GetTernaryType();

		//
		//2017/4/14: contour setting
		//
		/*!
		*
		**/
		void SetContourSetting(const ContourSetting &setting);

		/*!
		*
		**/
		const ContourSetting GetContourSetting();
	private:
		//
		//
		//
		/*!
		*
		**/
		void SetExtent();

		/*!
		*
		**/
		void GetInflectionPts();
		
		//
		//
		//
		/*!
		*
		**/
		void DoRenderBorder(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderTernaryLines(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderTernaryRegionLabel(CAnyCanvas &canvas, const std::vector<CGeoPoint<double>> &pts, const LabelStyle &labelStyle, const std::string &label, int color);

		/*!
		*
		**/
		void DoRenderTernaryPoints(CAnyCanvas &canvas);

		//
		//
		//
		/*!
		*
		**/
		void DoRenderContour(CAnyCanvas &canvas);

		/*!
		*
		**/
		void GetGridPts();

		/*!
		*
		**/
		void DoGetGridPts(const CGeoPoint<double> &scrPt, TernaryPercentage &tp, TernaryPoint &ternaryPt);

		/*!
		*
		**/
		void GetTernaryPtWeight(CGeoPoint<double> &tpt);
				
		/*!
		*
		**/
		void DoFillingGrid(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderContourLegend(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderContourLine(CAnyCanvas &canvas);

		/*!
		*2019/6/20: render legend: group name
		**/
		void DoRenderGroupLegend(CAnyCanvas &canvas);
	private:
		//
		//
		//
		std::string m_ternaryA;
		std::string m_ternaryB;
		std::string m_ternaryC;

		//2017/3/31: toc type related
		int m_ternaryType;

		//2017/4/13: samples
		TernaryPoints m_samplePts;
		
		//2017/4/13: grid pts
		TernaryPoints m_gridPts;
		std::vector<CGeoPoint<double>> m_grids;

		//2017/4/13: contour setting
		ContourSetting m_contour_setting;

		//2017/4/13: a triangle - 3 points
		std::vector<CGeoPoint<double>> m_borderScrPts;
		std::vector<CGeoPoint<double>> m_borderMapPts;

		//2019/6/20: get a map of 'group name - color'
		std::map<std::string, CAnyScatterMatrix::ScatterElement> m_groupname_color;
	};
}
#endif