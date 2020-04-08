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
#ifndef __ANYGEOP_WELL_LAYER_H__
#define __ANYGEOP_WELL_LAYER_H__

// refer to EXPORT & IMPORT macroes
#include "anygeop.h"

// refer to geom basic
#include "any/base/anygeom.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// for seismic survey 
#include "any/bridge/anybridgedatamodel.h"
using namespace AnyBridge;

//
namespace AnyGeoP
{
	/*!
	*
	**/
	class ANYGEOP_CLASS CAnyWellLayer : public CAnyViewHook
	{
	public:
		/*!
		*
		**/
		CAnyWellLayer(CAnyView &curView);

		/*!
		*
		**/
		~CAnyWellLayer();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype)
		{

		}
		//
 		// layer's functions
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

	public:
		CGeoRect<double> m_extent;
		vector<CGeoPoint<double> > m_points;
		vector<string> m_filenames;
		int curpickpoint;
	};
}

#endif
