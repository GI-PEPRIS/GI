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
#ifndef __ANYVIS_ROCK_PHYSICAL_TERNARY_H__
#define __ANYVIS_ROCK_PHYSICAL_TERNARY_H__

// refer to its parent
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
	class ANYVIS_CLASS CAnyRockPhysicalTernaryPlot  : public CAnyScatterMatrix
	{
	public:

		enum TernaryOperaion
		{
			TO_Default = 0,
			TO_Create,
			TO_Reshape,
			TO_Drag,
		};

		enum PolygonOperaion
		{
			PO_Default = 0,
			PO_Create,
			PO_Reshape,
			PO_Drag,
		};

		//
		struct TernaryTriangular
		{
			//points
			CGeoPoint<double> m_pt1;
			CGeoPoint<double> m_pt2;
			CGeoPoint<double> m_pt3;

			//directions
			std::vector<CGeoPoint<double>> m_direction1;
			std::vector<CGeoPoint<double>> m_direction2;
			std::vector<CGeoPoint<double>> m_direction3;

			//names
			std::string m_name1;
			std::string m_name2;
			std::string m_name3;

			//property
			bool m_isShown;
			int m_color;
			double m_width;
			int m_style;
			bool m_isAlpha;

			//
			TernaryTriangular() : m_name1(""), m_name2(""), m_name3(""), m_isShown(true), m_color(RGB(0,0,0)), m_style(0), m_width(1.), m_isAlpha(false)
			{
			}

			//=
			const TernaryTriangular &operator=(const TernaryTriangular &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_pt1 = other.m_pt1;
				m_pt2 = other.m_pt2;
				m_pt3 = other.m_pt3;
				
				m_name1 = other.m_name1;
				m_name2 = other.m_name2;
				m_name3 = other.m_name3;

				m_direction1 = other.m_direction1;
				m_direction2 = other.m_direction2;
				m_direction3 = other.m_direction3;

				m_isShown = other.m_isShown;
				m_color = other.m_color;
				m_width = other.m_width;
				m_style = other.m_style;
				m_isAlpha = other.m_isAlpha;
			}
		};
		typedef std::vector<TernaryTriangular> TernaryTriangulars;

		//
		struct TernaryPercentage
		{
			std::string m_name1;
			std::string m_name2;
			std::string m_name3;

			double m_rate1;
			double m_rate2;
			double m_rate3;

			double m_depth;

			CGeoPoint<double> m_mapPt;
			CGeoPoint<double> m_scrPt;

			//
			TernaryPercentage()
			{
				InitData();
			}

			//
			void InitData()
			{
				m_name1 = "";
				m_name2 = "";
				m_name3 = "";

				m_rate1 = 0.;
				m_rate2 = 0.;
				m_rate3 = 0.;

				m_depth = 0.;

				m_mapPt.m_x = -1.;
				m_mapPt.m_y = -1.;

				m_scrPt.m_x = -1.;
				m_scrPt.m_y = -1.;
			}

			//
			bool IsLegal()
			{
				return m_mapPt.IsValid() && m_scrPt.IsValid() && m_name1.size() && m_name2.size() && m_name3.size();
			}
			
		};

		//for different polygon
		struct PolygonProperty
		{
			long m_idx;
			std::vector<CGeoPoint<double>> m_pts;
			std::string m_name;

			//property
			int m_color;
			double m_width;
			int m_style;
			bool m_isAlpha;
			
			//ellipse
			double m_a;
			double m_b;
			CGeoPoint<double> m_centerPt;
			double m_angle;

			//pdf curve
			ElementVector m_pdfxpts;
			ElementVector m_pdfypts;

			/*!
			*
			**/
			PolygonProperty() : m_name(""), m_color(RGB(0,0,0)), m_style(0), m_width(2.), m_isAlpha(false), m_idx(0)
			{
				InitEllipse();
			}
			
			/*!
			*
			**/
			void InitEllipse()
			{
				m_a = ANY_NAN;
				m_b = ANY_NAN;
				m_angle = ANY_NAN;
				m_centerPt.m_x = -1.;
				m_centerPt.m_y = -1.;
				m_centerPt.m_z = -1.;

				m_pdfxpts.clear();
				m_pdfypts.clear();
			}

			/*!
			*
			**/
			bool IsEllipseValid()
			{
				return !ISNAN(m_a) && !ISNAN(m_b) && !ISNAN(m_angle) && m_centerPt.IsValid();
			}
		};
		typedef std::vector<PolygonProperty> PolygonProperties;
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyRockPhysicalTernaryPlot(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyRockPhysicalTernaryPlot();

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
		*order means which point(0,1,2), return the order in m_ternarys
		**/
		int FindTernaryInflectionPoint(const CGeoPoint<double> &scrPt, int &order);

		/*!
		*return the order in m_ternarys
		**/
		int FindTernary(const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		bool GetTernaryPercentage(const CGeoPoint<double> &scrPt, TernaryPercentage &ternary);

		/*!
		*
		**/
		bool GetTernaryPercentages(TernaryTriangular &ternary, std::vector<TernaryPercentage> &ternaryPercentages);

		/*!
		*
		**/
		void ResetTernaryOperation();

		/*!
		*
		**/
		bool GetElementsInPolygon(int order, std::vector<ElementVector> &xelements, std::vector<ElementVector> &yelements);
	
		/*!
		*order in m_polygons
		**/
		int FindPolygon(CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		bool CreateEllipseAndPdfCurveViaElements(int order, std::vector<ElementVector> &xelements, std::vector<ElementVector> &yelements);

		/*!
		*
		**/
		static void CreateEllipseParameter(double A, double B, double C, double D, double E, double F, double &x, double &y, double &longAxis, double &shortAxis, double &seta);
	private:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTernary(CAnyCanvas &canvas, TernaryTriangular &ternary);

		/*!
		*
		**/
		void DoRenderTernaryInnerCutoffLine(CAnyCanvas &canvas, LineStyle &lineStyle, CGeoPoint<double> &mapPt1, CGeoPoint<double> &mapPt2, CGeoPoint<double> &mapPt3);

		/*!
		*2016/6/13: polygon related
		**/
		bool IsPolygonIntersect(const std::vector<CGeoPoint<double> > &polygon);
	public:
		TernaryTriangulars m_ternarys;//
		int m_ternaryOperation;

		PolygonProperties m_polygons;//
		int m_polygonOperation;

	protected:

		//2017/4/14: mouse pickup action's offset
		double m_offset;

	private:
		//ternary related
		TernaryTriangular m_tempternary;
		TernaryPercentage m_ternaryHint;
		bool m_isMouseDown;

		//for ternary drag,reshape
		CGeoPoint<double> m_prePos;
		int m_ternaryOrder;
		int m_ternaryPtOrder;

		//polygon related
		PolygonProperty m_tempPolygon;
		long m_polygonIdx;//2016/6/16: polygon's unique id
	};
}
#endif