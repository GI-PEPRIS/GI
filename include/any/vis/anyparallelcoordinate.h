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
#ifndef __ANYVIS_PARALLEL_COORDINATE_H__
#define __ANYVIS_PARALLEL_COORDINATE_H__

// refer to macro
#include "anyvis.h"

// refer to view hook
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to axis parent
#include "anyaxises.h"

// refer to geometry basic
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyVis
{
	// forward class
	class CParallelCoordinateCluster;

	/*!
	*
	**/
	class ANYVIS_CLASS CAnyParallelCoordinate : public CAnyViewHook, private CAnyAxises
	{
	public:
		/*!
		*
		**/
		enum MapOperation
		{
			MO_Normal  = 1,
			MO_ZoomIn  = 1 << 1,
			MO_ZoomOut = 1 << 2,
			MO_Pan     = 1 << 3,
		};

		/*!
		*
		**/
		struct PolyLine
		{
			// dimension definitions
			CGeoPoint<double> *m_pts;
			int m_ptNumber;
			// which cluster numbering from zero
			short m_cluster; 
			// the name of polyline
			char m_name[512];
			// whether hide
			bool m_isHiden;

			/*!
			*
			**/
			PolyLine() : m_pts(0), m_ptNumber(0), m_isHiden(false)
			{
				::memset(m_name, 0x00, 512);
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyParallelCoordinate(CAnyView &curView);

		/*!
		*
		**/
		~CAnyParallelCoordinate();

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
		**/
		void Reset(PolyLine *begin, int lineNumber, double **limits, char **names);

		/*!
		*
		**/
		void Refresh()
		{
			m_curView.Refresh();
		}

		/*!
		*
		**/
		int GetAxisOrder();

		//
		//
		//
		/*!
		*
		**/
		void MakeClusters(int clusters, int iterations);

		/*!
		*
		**/
		int GetCount();

		/*!
		*
		**/
		CAnyParallelCoordinate::PolyLine *GetPolyLine(int index);

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
		virtual void DoRenderAxisLine(CAnyCanvas &canvas, CGeoPoint<double> *pts, unsigned short flag, bool arrowDirection, short order);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderHints(CAnyCanvas &canvas);

		/*!
		*
		**/
		void Map2Scr(PolyLine *curLine, CGeoPoint<double> *scrPts);

		/*!
		*
		**/
		int GetNextOrder(int curOrder);

		//
		//
		//
		/*!
		*
		**/
		static int CompareCluster(const void *first, const void *second);

	private:
		// map operation
		unsigned int m_opType;

		//
		PolyLine *m_lines;
		int m_lineNumber;

		//
		const static int MAXNAMELENGTH = 64;
		int m_axises;
		char **m_names;
		double **m_limits;

		// position for hints
		CGeoPoint<double> m_hintPt;

		//
		CParallelCoordinateCluster *m_cluster;
	};
}
#endif