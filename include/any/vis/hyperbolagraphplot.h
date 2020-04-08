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
#ifndef __ANYVIS_HYPERBOLA_GRAPHPLOT_H__
#define __ANYVIS_HYPERBOLA_GRAPHPLOT_H__

// refer to export macroes
#include "anyvis.h"

// refer to parent
#include "anyscattermatrix.h"

// refer to geometry primitives
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyVis
{
	class ANYVIS_CLASS CHyperbolaGraphPlot : public CAnyScatterMatrix
	{

	public:
	/*!
	*
	**/
	enum HyperbolaOperation
	{
		HBO_Default					= 1,

		//picked operation status
		HBO_Picked_Horizontal				= 1 << 1,
		HBO_Picked_Vertical					= 1 << 2,
		HBO_Picked_Hyperbola				= 1 << 3,
		HBO_Picked_Hyperbola_Custom			= 1 << 4,
	};

	/*!
	*
	**/
	enum QuadrantOperation
	{
		QO_Default					= 1,
		QO_Picked_Top				= 1 << 1,
		QO_Picked_bottom			= 1 << 2,
		QO_Picked_Left				= 1 << 3,
		QO_Picked_Right				= 1 << 4,
	};

	public:
		/*!
		*
		**/
		struct HyperElement
		{
			long m_idx;
			long m_groupIdx;
			string m_name;
			CGeoPoint<double> m_coord;			// m_x, resource risk, up point
			double m_resource10;					// maximum value, right end-point
			double m_resource90;					// minimum value, left end-point
			double m_resource00;					 // resource-non risk, onto point
			bool m_isQuadPicked;
			bool m_isHyperbolaPicked;

			//color
			unsigned int m_color;
			unsigned int m_symbol;

			double m_txtSize;
			double m_symbolSize;

			//is value shown
			bool m_isValueShown;

			/*!
			*
			**/
			HyperElement() : m_idx(0), m_groupIdx(0), m_name(""), m_isQuadPicked(false),m_isHyperbolaPicked(false), m_resource10(0.), \
				m_resource90(0.), m_resource00(0.), m_color(0),m_symbol(0),m_txtSize(9.),m_symbolSize(3.),m_isValueShown(true)
			{
			}

			/*!
			*
			**/
			bool operator==(const string &strName)
			{
				if(this->m_name == strName)
				{
					return true;
				}
				return false;
			}
		};
		typedef std::vector<HyperElement> ElementVector;

		/*!
		*
		**/
		struct PickedRange
		{
			double m_xValue;
			double m_yValue;
			double m_hyperbola; // coefficient, namely x * y = hyperbola

			/*!
			*
			**/
			PickedRange() : m_xValue(0.), m_yValue(0.), m_hyperbola(0.)
			{
			}
		};

	public:
		CHyperbolaGraphPlot(CAnyView &curView, unsigned int mode);
		~CHyperbolaGraphPlot();

	public:
		//
		//
		//
		/*!
		*
		**/
		void AddElementVector(const ElementVector &elements, PickedRange &limits, const std::string &xName = "X", const std::string &yName = "Y");

		/*!
		*
		**/
		int GetElementCount();

		/*!
		*
		**/
		const HyperElement &GetElement(int order);

		/*!
		*
		**/
		double GetHyperbola();

		/*!
		*
		**/
		void SetHyperbola(double hyperbola);
		
		//
		//
		//
		const std::vector<double> &GetCustomHyperbolas();

		/*!
		*
		**/
		double GetCurrentCustomHyperbola();

		/*!
		*
		**/
		void SetCustomHyperbola(double hyperbola);

		/*!
		*
		**/
		void AddCustomHyperbola(double hyperbola);

		/*!
		*
		**/
		void RemoveCustomHyperbola();

		/*!
		*
		**/
		bool IsCustomHyperbolaSelected();

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
		bool MouseRDown(const CGeoPoint<double> &scrPoint);

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

		/*!
		* 
		**/
		void DoDeleteElements();

		//
		//quadrant related
		//
		/*!
		* 
		**/
		void SetQuadrantMode(bool isQuadrant);

		/*!
		* 2015/4/17
		**/
		bool IsQuadrantMode();

		/*!
		* 
		**/
		void SetQuadrantRowCol(int row = 3, int col = 3);

		/*!
		* 
		**/
		unsigned int GetQuadrantPointColor(CGeoPoint<double> &mapPt, string &quadrantName);

		//
		//build type
		//
		/*!
		* 
		**/
		void SetBuildType(int type);
	private:
		//
		//
		//
		/*!
		* when mouse up, call this function
		**/
		void DoPickElements();

		//
		//
		//
		/*!
		* render points out of PickedRange(m_limits)
		**/
		void DoRenderPoints(CAnyCanvas &canvas);

		/*!
		* render X and Y line
		**/
		void DoRenderEdgeLines(CAnyCanvas &canvas, unsigned int operation = HBO_Default);

		/*!
		* render hyperbola
		**/
		void DoRenderHyperbola(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderHyperbola(CAnyCanvas &canvas,double hyperbola,bool isSolid = true);

		/*!
		* render hint
		**/
		void DoRenderHint(CAnyCanvas &canvas);
		
		/*!
		* render quadrant
		**/
		void DoRenderQuadrant(CAnyCanvas &canvas);
		
		/*!
		* render quadrant edged lines
		**/
		void DoRenderQuadrantLines(CAnyCanvas &canvas, CGeoPoint<double> &pt1, CGeoPoint<double> &pt2, LineStyle &lineStyle, bool isVertcial = true);

		/*!
		* render quadrant name
		**/
		void DoRenderQuadrantName(CAnyCanvas &canvas);

		/*!
		*
		**/
		void ResetEdgedLinesLimit();

		/*!
		* 
		**/
		void InitQuadrantEdgedLines();

		//
		//
		//
		/*!
		* 
		**/
		void DoRenderPointName(CAnyCanvas &canvas, LabelStyle &txtstyle,const string &name, CGeoPoint<double> &scrPt);

		/*!
		* 
		**/
		void DoRenderPointValue(CAnyCanvas &canvas, LabelStyle &txtstyle,const string &label,CGeoPoint<double> &pos, CGeoPoint<double> &scrPt, bool isShown);

	private:
		// elements
		ElementVector m_elements;

		// X and Y direction pick lines
		CGeoPoint<double> m_xLine[2];
		CGeoPoint<double> m_yLine[2];

		//
		std::vector<double> m_hyperbolas;
		int m_selectedOrder;
		int m_deletedOrder;
		
		// point name and position for mouse move
		string m_ptName;
		CGeoPoint<double> m_hintPt;

		// picked setting
		PickedRange m_limits;

		//operation
		unsigned int m_operation;

		//flag of mouse down
		bool m_isMouseDown;

		//flag of mouse move
		bool m_isMouseMove;

		//rectangle positions for point name and value
		std::vector<CGeoRect <double>> m_nameRectPositions;
		std::vector<CGeoRect <double>> m_valueRectPositions;

		//quadrant
		bool m_isQuadrant;
		int m_quadrantRow;
		int m_quadrantCol;

		//pick lines in quadrant mode
		CGeoPoint<double> m_quadTopLine[2];
		CGeoPoint<double> m_quadBottomLine[2];

		CGeoPoint<double> m_quadLeftLine[2];
		CGeoPoint<double> m_quadRightLine[2];

		//operation
		unsigned int m_quadOperation;
		bool m_isInitial;

		//
		std::string m_xName;
		std::string m_yName;
	public:
		bool m_isRightDown;
	};
}
#endif