/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYSDE_SDE_RASTER_SPATIAL_ANALYSIS_H__
#define __ANYSDE_SDE_RASTER_SPATIAL_ANALYSIS_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to property vector
#include "anysdegeometrylayer.h"

// refer to STL
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "any/base/anyport.h"
using namespace AnyBase;

#include "any/math/anykriging.h"
using namespace AnyMath;

#include "any/vis/anycontour.h"
#include "any/vis/anygridtracing.h"
using namespace AnyVis;

//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnyRasterSpatialAnalysis : public CAnyViewHook
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyRasterSpatialAnalysis(CAnyView &curView);
		CAnyRasterSpatialAnalysis(CAnyView &curView, CAnyViewHook *layer);
		CAnyRasterSpatialAnalysis(CAnyView &curView, int rows, int cols);
		virtual ~CAnyRasterSpatialAnalysis();

	public:
		//
		// inherited from view hook
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);
		
		/*!
		*
		**/
		CGeoPoint<double> * MakeRasterization(CAnyViewHook *layer, const CGeoRect<double> &extent, const string &field, int rows, int cols);
		
		//
		// behaviors as a typical view hook
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);
		bool MouseDown(const CGeoPoint<double> &scrPoint);
		bool MouseMove(const CGeoPoint<double> &scrPoint);
		bool MouseUp(const CGeoPoint<double> &scrPoint);
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		//
		//
		//
		/*!
		*
		**/
		int GetRows();

		/*!
		*
		**/
		int GetCols();

		/*!
		*
		**/
		CGeoPoint<double> GetCell(int curRow, int curCol);

		/*!
		*
		**/
		void SetCell(int curRow, int curCol, double value);

		/*!
		* for contour output
		**/
		CGeoPoint<double> *Clone(int &number) const;

		/*!
		*
		**/
		void SetCell(double value);

		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		void IsInterploate(bool isInter);

		/*!
		*2015/7/23
		**/
		void SetRenderRaster(bool isRender);

	public:
		// raster extent
		CGeoRect<double> m_extent;
		// cells for contour output
		// order strictly follow ANYCONTOUR: i * rows + j, i  means cur col, j mean cur row
		CGeoPoint<double> *m_cells;	

		// host layer
		CAnyViewHook *m_layer;

		
	protected:
		int m_rows;
		int m_cols;

		//
		bool m_isInterpolation;
		bool m_isRenderRaster;//2015/7/23
	};
}
#endif