/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYCGAL_DELUNARY_H__
#define __ANYCGAL_DELUNARY_H__

// Refer to EXPORT & IMPORT macroes
#include "anycgal.h"

// refer to CGeoPoint
#include "any/base/anygeom.h"
using namespace AnyBase;

// namespace 
namespace AnyCGAL
{
	/*!
	*
	**/
	class ANYCGAL_CLASS CAnyDelunary
	{
	public:
		// TYPES
		struct VERTEX2D
		{
			double m_x;
			double m_y;
			double m_value;
			VERTEX2D() : m_x(0), m_y(0), m_value(0)
			{
			}
			VERTEX2D(const double &x, const double &y, const double &value) : m_x(x), m_y(y), m_value(value)
			{
			}
			const VERTEX2D &operator=(const VERTEX2D &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_x = other.m_x;
				m_y = other.m_y;
				m_value = other.m_value;
				return *this;
			}
		};

		/*!
		*
		**/
		struct EDGE
		{
			VERTEX2D m_v1;
			VERTEX2D m_v2;
			EDGE()
			{
			}
			const EDGE &operator=(const EDGE &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_v1 = other.m_v1;
				m_v2 = other.m_v2;
				return *this;
			}
		};

		/*!
		*
		**/
		struct EDGEINDEX
		{
			int m_i1;
			int m_i2;
			EDGEINDEX()
			{
			}
			const EDGEINDEX &operator=(const EDGEINDEX &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_i1 = other.m_i1;
				m_i2 = other.m_i2;
				return *this;
			}
			static bool CompareStart(const EDGEINDEX &a, const EDGEINDEX &b)
			{
				return a.m_i1 < b.m_i1;
			}
			static bool CompareEnd(const EDGEINDEX &a, const EDGEINDEX &b)
			{
				return a.m_i2 < b.m_i2;
			}
		};

		/*!
		*
		**/
		struct VERTEX_EDGE
		{
			int m_i1;
			int m_edgecount;
			VERTEX_EDGE()
			{
			}
			const VERTEX_EDGE &operator=(const VERTEX_EDGE &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_i1 = other.m_i1;
				m_edgecount = other.m_edgecount;
				return *this;
			}
			static bool CompareEdgecount(const VERTEX_EDGE &a, const VERTEX_EDGE &b)
			{
				return a.m_edgecount > b.m_edgecount;
			}
		};

		/*!
		*
		**/
		struct TRIANGLE
		{
			int m_i1; // vertex index
			int m_i2; 
			int m_i3; 

			TRIANGLE *m_pNext;
			TRIANGLE *m_pPrev;

			VERTEX2D m_circlecenter;
			double m_circleR;

			TRIANGLE() : m_pNext(0), m_pPrev(0), m_i1(-1), m_i2(-1), m_i3(-1), m_circleR(0)
			{
			}
			const TRIANGLE &operator=(const TRIANGLE &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_i1 = other.m_i1;
				m_i2 = other.m_i2;
				m_i3 = other.m_i3;
				m_pNext = other.m_pNext;
				m_pPrev = other.m_pPrev;
				m_circlecenter = other.m_circlecenter;
				m_circleR = other.m_circleR;
				return *this;
			}
		};

		/*!
		*
		**/
		struct MESH
		{
			int vertex_num;
			int triangle_num;

			VERTEX2D *m_pVerArr; // point to outer vertices arrary
			TRIANGLE  *m_pTriArr; // point to outer triangles arrary

			/*!
			*
			**/
			MESH() : vertex_num(0), triangle_num(0), m_pVerArr(0), m_pTriArr(0)
			{
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyDelunary();
		~CAnyDelunary();

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitMesh(CGeoPoint<double> *samples, int number);
		void InitMesh(const std::vector<CGeoPoint<double> > &samples);
		void DirectMesh(CGeoPoint<double> *samples, int row, int col);
		void IncrementalDelaunay();
		void IncrementalVoronoi(std::vector<std::vector<CGeoPoint<double> > > &polygons, std::vector<CGeoPoint<double> > &voronoi_boudary);
		void GetConcave(double R, std::vector<CGeoPoint<double> > &outpolygons);
		void GetConcave_RemoveOneTriangle(std::map<int, std::map<int, std::vector<int> > > &edgepair_triangleoffsets, std::vector<int> &triangletoremove, double R, int triangleoffset, std::vector<TRIANGLE> &triangles);
		void ReleaseMesh();

		//
		//
		//
		/*!
		*
		**/
		const MESH &GetMesh() const
		{
			return m_mesh;
		}
		double IsInTriangle(VERTEX2D* pVer, TRIANGLE* pTri);
		double IsInTriangle(CGeoPoint<double> &pt, CGeoPoint<double> &trianglept1, CGeoPoint<double> &trianglept2, CGeoPoint<double> &trianglept3);
		void DoContourDelunary(const CGeoPoint<double> *samples, int samplenum, int cols, int rows, CGeoRect<double> &extent, CGeoPoint<double> *resultsamples);
		void DoHexagon(int cols, int rows, std::vector<CGeoPoint<double> > &samples, std::vector<std::vector<CGeoPoint<double> > > &polygons);

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoAddBoundingBox();
		TRIANGLE *DoAddTriangleNode(TRIANGLE *pPrevTri, int i1, int i2, int i3);
		double IsCounterClockWise(VERTEX2D *pa, VERTEX2D *pb, VERTEX2D *pc);
		double IsCounterClockWise(CGeoPoint<double> &pa, CGeoPoint<double> &pb, CGeoPoint<double> &pc);
		void DoInsertSample(int ver_index);
		void DoFindNeighborInCircleTriangle(TRIANGLE* curtriangle, std::vector<TRIANGLE*> &neighbortriangles, int ver_index);
		void DoInsertOnEdge(TRIANGLE* pTargetTri, int ver_index);
		bool DoFlipTest(TRIANGLE* pTestTri);
		double IsInCircle(VERTEX2D* pa, VERTEX2D* pb, VERTEX2D* pp, VERTEX2D*  pd);
		void DoRemoveTriangleNode(TRIANGLE* pTri);
		void DoInsertInTriangle(TRIANGLE* pTargetTri, int ver_index);
		void DoRemoveBoundingBox();
		bool DoGranhamScanning(std::vector<int> &outptoffsets, double crossval = 0);
		static bool CompareGraham(const CGeoPoint<double> &a, const CGeoPoint<double> &b);
		static double cross(const CGeoPoint<double> &a, const CGeoPoint<double> &b, const CGeoPoint<double> &c);
		static bool Getdistance(const CGeoPoint<double> &a, const CGeoPoint<double> &b);
		/*!
		*
		**/
		CGeoPoint<double> VectorConstruct(CGeoPoint<double> &A, CGeoPoint<double> &B);
		double CrossProduct(CGeoPoint<double> &a, CGeoPoint<double> &b);
		CGeoRect<double> MbrConstruct(CGeoPoint<double> &A, CGeoPoint<double> &B);
		int MbrOverlap(CGeoRect<double> &m1, CGeoRect<double> &m2);
		int SegmentIntersection(CGeoPoint<double> &A, CGeoPoint<double> &B, CGeoPoint<double> &C, CGeoPoint<double> &D);
		void ModifyTrianglesByCutedge(std::vector<CGeoPoint<double> > &cutedgestarts, std::vector<CGeoPoint<double> > &cutedgeends);
	public:
		// 
		MESH m_mesh;
		int m_algorithmtype;
		static CGeoPoint<double> m_theleftpt;// min start pt
	};
}

#endif