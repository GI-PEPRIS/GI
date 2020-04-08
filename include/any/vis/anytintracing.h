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
#ifndef __ANYVIS_CONTOUR_TIN_TRACING_H__
#define __ANYVIS_CONTOUR_TIN_TRACING_H__

// refer to macro
#include "anyvis.h"

// refer to parent
#include "anycontourtracingstrategy.h"

// refer to coordinate
#include "any/base/anygeom.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

#include "any/cgal/anydelunary.h"
using namespace AnyCGAL;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyTINTracing : public CAnyContourTracingStrategy
	{
		
	protected:
		/*!
		*
		**/
		struct TINEdge
		{
			CGeoPoint<double> m_v1;
			CGeoPoint<double> m_v2;
			std::vector<int> m_TINIndex;

			TINEdge()
			{
			}
			TINEdge(CGeoPoint<double> v1,CGeoPoint<double> v2)
			{
				m_v1=v1;
				m_v2=v2;
			}
			const TINEdge &operator=(const TINEdge &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_v1 = other.m_v1;
				m_v2 = other.m_v2;
				return *this;
			}
			bool Equals(const TINEdge &other)
			{
				if(m_v1.m_x == other.m_v1.m_x && m_v1.m_y == other.m_v1.m_y && (m_v1.m_z==other.m_v1.m_z || (ISNAN(m_v1.m_z) && ISNAN(other.m_v1.m_z))))
				{
					if(m_v2.m_x == other.m_v2.m_x && m_v2.m_y == other.m_v2.m_y && (m_v2.m_z==other.m_v2.m_z || (ISNAN(m_v2.m_z) && ISNAN(other.m_v2.m_z))))
					{
						return true;
					}				
				}
				else if(m_v1.m_x == other.m_v2.m_x && m_v1.m_y == other.m_v2.m_y && (m_v1.m_z==other.m_v2.m_z || (ISNAN(m_v1.m_z) && ISNAN(other.m_v2.m_z))))
				{
					if(m_v2.m_x == other.m_v1.m_x && m_v2.m_y == other.m_v1.m_y && (m_v2.m_z==other.m_v1.m_z || (ISNAN(m_v2.m_z) && ISNAN(other.m_v1.m_z))))
					{
						return true;
					}				
				}

				return false;
			}
		};
		struct Triangel
		{
			CGeoPoint<double> m_v1;
			CGeoPoint<double> m_v2;
			CGeoPoint<double> m_v3;

			std::vector<int> m_TINEdgeIndex;

			Triangel()
			{
			}
			Triangel(CGeoPoint<double> v1,CGeoPoint<double> v2,CGeoPoint<double> v3)
			{
				m_v1=v1;
				m_v2=v2;
				m_v3=v3;
			}
			const Triangel &operator=(const Triangel &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_v1 = other.m_v1;
				m_v2 = other.m_v2;
				m_v3 = other.m_v3;

				return *this;
			}

			bool Equals(const Triangel &other)
			{
				if(m_v1 == other.m_v1 && m_v2 == other.m_v2 && m_v3 == other.m_v3)
					return true;
				else if(m_v1 == other.m_v2 && m_v2 == other.m_v1&& m_v3 == other.m_v3)
					return true;
				else if(m_v1 == other.m_v1 && m_v2 == other.m_v3&& m_v3 == other.m_v2)
					return true;
				else if(m_v1 == other.m_v3 && m_v2 == other.m_v2&& m_v3 == other.m_v1)
					return true;

				return false;
			}

			double slope()
			{
				double dx=(m_v2.m_y-m_v1.m_y)*(m_v3.m_z-m_v2.m_z)-(m_v3.m_y-m_v2.m_y)*(m_v2.m_z-m_v1.m_z);
				double dy=(m_v3.m_x-m_v2.m_x)*(m_v2.m_z-m_v1.m_z)-(m_v2.m_x-m_v1.m_x)*(m_v3.m_z-m_v2.m_z);
				double cross=(m_v2.m_x-m_v1.m_x)*(m_v3.m_y-m_v2.m_y)-(m_v3.m_x-m_v2.m_x)*(m_v2.m_y-m_v1.m_y);
				if(cross==0)
					return 90;
				return atan(sqrt(dx*dx+dy*dy)/cross) * 180 / 3.1416;
			}

			double aspect()
			{
				double dx=(m_v2.m_y-m_v1.m_y)*(m_v3.m_z-m_v2.m_z)-(m_v3.m_y-m_v2.m_y)*(m_v2.m_z-m_v1.m_z);
				double dy=(m_v3.m_x-m_v2.m_x)*(m_v2.m_z-m_v1.m_z)-(m_v2.m_x-m_v1.m_x)*(m_v3.m_z-m_v2.m_z);
				if (dx == 0) 
				{
					if (dy == 0) //even land
					{
						return -1;
					}
					else if (dy > 0) 
					{
						return 0;
					}
					else 
					{
						return 180;
					}
				} else if (dx > 0) 
				{
					return atan(dy / dx) * 180 / 3.1416 + 270;
				}
				else
				{
					return atan(dy / dx) * 180 / 3.1416 + 90;
				}

				return -1;
			}

			double area()
			{
				double d1=sqrt((m_v2.m_x-m_v1.m_x)*(m_v2.m_x-m_v1.m_x)+(m_v2.m_y-m_v1.m_y)*(m_v2.m_y-m_v1.m_y)+(m_v2.m_z-m_v1.m_z)*(m_v2.m_z-m_v1.m_z));
				double d2=sqrt((m_v3.m_x-m_v2.m_x)*(m_v3.m_x-m_v2.m_x)+(m_v3.m_y-m_v2.m_y)*(m_v3.m_y-m_v2.m_y)+(m_v3.m_z-m_v2.m_z)*(m_v3.m_z-m_v2.m_z));
				double d3=sqrt((m_v1.m_x-m_v3.m_x)*(m_v1.m_x-m_v3.m_x)+(m_v1.m_y-m_v3.m_y)*(m_v1.m_y-m_v3.m_y)+(m_v1.m_z-m_v3.m_z)*(m_v1.m_z-m_v3.m_z));
				double p=(d1+d2+d3)/2;
				double s=sqrt(p*(p-d1)*(p-d2)*(p-d3));
				return s;
			}
		};
		struct EqualValuePoint
		{
			CGeoPoint<double> m_pos;
			bool m_used;
			int m_TINEdge;

			EqualValuePoint(CGeoPoint<double> position)
			{
				m_pos=position;
				m_used=false;
			}
			EqualValuePoint(double x, double y)
			{
				m_pos.m_x=x;
				m_pos.m_y=y;
				m_used=false;
			}
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyTINTracing(CAnyContour *contour);

		/*!
		*
		**/
		~CAnyTINTracing();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Tessellate(int rows, int cols, CGeoRect<double> &extent, const CGeoRect<double> &newExtent = CGeoRect<double>());


		void SetBlankAreaNANValue(std::vector<std::vector<CGeoPoint<double>> > &blanks, bool isTempBlank=true, bool isNAN=true, double customvalue=ANY_NAN);

		void SetCustomZValue();

		void TraceLine();
						
		//
		//
		//
		/*!
		*
		**/
		static double IsCounterClockWise(CGeoPoint<double> &pa, CGeoPoint<double> &pb, CGeoPoint<double> &pc);
		static double IsInTriangle(CGeoPoint<double> &pt, CGeoPoint<double> &trianglept1, CGeoPoint<double> &trianglept2, CGeoPoint<double> &trianglept3);

		//
		//
		/*!
		*
		**/
		void GetControlInfo(int &rows, int &cols);

		/*!
		*
		**/
		const CGeoPoint<double> &GetControlPoint(int row, int col);

		/*!
		*
		**/
		void GetControlGrid(const CGeoPoint<double> &pt, int &lbRow, int &lbCol);

		/*!
		* 
 		**/
		bool MoveFirst(CGeoPoint<double> *pts, bool &isbordergrid);

		/*!
		*
		**/
		bool MoveNext(CGeoPoint<double> *pts, bool &isbordergrid);

		/*!
		*
		**/
		CGeoPoint<double> GetValue(int row, int col);
				
		/*!
		*
		**/
		CGeoPoint<double> *MakeRasterization(const CGeoRect<double> &extent, const string &field, int rows, int cols);
	private:
		//
		//
		//
		/*!
		*
		**/
		void GetTINTracingParams(const CGeoPoint<double> *recs, int recNumber, CGeoRect<double> extent);

		void DoTraceOpenLine_TIN(std::vector<CGeoPoint<double> > &contourlinePts, EqualValuePoint &startPt, double curvalue, int k, int intin);

		void DoExtractContourLine_TIN(std::vector<CGeoPoint<double> > contourlinePts, double zvalue, int ptNumber, bool isOpen = true);
	public:

		//2016/11/7: delunary method
		CAnyDelunary m_delunary;
		//20190725 TIN tracing
		CAnyDelunary::MESH m_mesh;
		std::vector<TINEdge> m_TINEdges;
		std::vector<Triangel> m_Triangels;
		std::vector<std::vector<EqualValuePoint>> m_TINEqualValPts;

	};
}

#endif