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
#ifndef __ANYBASE_DELUNARY_H__
#define __ANYBASE_DELUNARY_H__

// Refer to EXPORT & IMPORT macroes
#include "anybase.h"

// refer to CGeoPoint
#include "anygeom.h"

// namespace 
namespace AnyBase
{
	/*!
	*
	**/
	class ANYBASE_CLASS CAnyDelunary
	{
	public:
		// TYPES
		struct VERTEX2D
		{
			double m_x;
			double m_y;

		};

		/*!
		*
		**/
		struct EDGE
		{
			VERTEX2D m_v1;
			VERTEX2D m_v2;

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

		/*!
		*
		**/
		~CAnyDelunary();

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitMesh(const std::vector<CGeoPoint<double> > &samples);

		/*!
		*
		**/
		void IncrementalDelaunay();

		/*!
		*
		**/
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

		/*!
		*
		**/
		double IsInTriangle(VERTEX2D* pVer, TRIANGLE* pTri);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoAddBoundingBox();

		/*!
		*
		**/
		TRIANGLE *DoAddTriangleNode(TRIANGLE *pPrevTri, int i1, int i2, int i3);

		/*!
		*
		**/
		double IsCounterClockWise(VERTEX2D *pa, VERTEX2D *pb, VERTEX2D *pc);

		/*!
		*
		**/
		void DoInsertSample(int ver_index);

		/*!
		*
		**/
		void DoInsertOnEdge(TRIANGLE* pTargetTri, int ver_index);

		/*!
		*
		**/
		bool DoFlipTest(TRIANGLE* pTestTri);

		/*!
		*
		**/
		double IsInCircle(VERTEX2D* pa, VERTEX2D* pb, VERTEX2D* pp, VERTEX2D*  pd);

		/*!
		*
		**/
		void DoRemoveTriangleNode(TRIANGLE* pTri);

		/*!
		*
		**/
		void DoInsertInTriangle(TRIANGLE* pTargetTri, int ver_index);

		/*!
		*
		**/
		void DoRemoveBoundingBox();

	private:
		// 
		MESH m_mesh;
	};
}

#endif