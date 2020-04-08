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
#ifndef __ANYVIS_CONTOUR_COMPOSITOR_H__
#define __ANYVIS_CONTOUR_COMPOSITOR_H__

// refer to parent
#include "anycontour.h"

// refer to macro
#include "anyvis.h"

// refer to parent
#include "anyaxises.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//2015/5/27
#include "any/thread/jtc.h"

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyContourCompositor  : public CAnyContour
	{

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyContourCompositor(CAnyView &curView,int subContourNumber);

		/*!
		*
		**/
		virtual ~CAnyContourCompositor();

	public:

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
		//void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);
			
	public:		
		/*!
		*
		*/
		void SetSubBorders(std::vector<std::vector<CGeoPoint<double>> > subborders);

		/*!
		*
		*/
		void SetSubExtents(std::vector<CGeoRect<double>> subMBRs);

		/*!
		*
		*/
		void SetSubSamples();
				
		/*!
		*
		*/
		void SetSubSamples(std::vector<std::vector<CGeoPoint<double>>> subsamples);

		/*!
		*
		*/
		void SetSubContours(std::vector<CAnyContour::KrigingPara> krigparams);

		/*!
		*
		*/
		void SetGridValuesFromSubContours();

	protected:

		CGeoPoint<double> *m_gridvalue;

		int m_subContourNumber;
		//sub contours
		std::vector<CAnyContour*> m_subcontours;
		//extent of sub contours
		std::vector<CGeoRect<double>> m_subextents;
		//borders of sub contours
		std::vector<std::vector<CGeoPoint<double>> > m_subborders;
		//samples of sub contours
		std::vector<std::vector<CGeoPoint<double>>> m_subsamples;
		//grid value of sub contours
		std::vector<CGeoPoint<double> *> m_subgridvalue;
		
	};
}
#endif