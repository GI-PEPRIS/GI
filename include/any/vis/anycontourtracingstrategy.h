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
#ifndef __ANYVIS_CONTOUR_TRACING_STRATEGY_H__
#define __ANYVIS_CONTOUR_TRACING_STRATEGY_H__

// refer to macro
#include "anyvis.h"

// refer to geo point
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyVis
{
	// forward class
	class CAnyContour;

	/*!
	*
	**/
	class ANYVIS_CLASS CAnyContourTracingStrategy
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyContourTracingStrategy(CAnyContour *contour);

		/*!
		*
		**/
		virtual ~CAnyContourTracingStrategy();

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual void Tessellate(int rows, int cols, CGeoRect<double> &extent, const CGeoRect<double> &newExtent = CGeoRect<double>()) = 0;

		/*!
		*
		**/
		virtual void TraceLine() = 0;
		//
		//
		//
		/*!
		*
		**/
		virtual void GetControlInfo(int &rows, int &cols) = 0;

		/*!
		*
		**/
		virtual const CGeoPoint<double> &GetControlPoint(int row, int col) = 0;

		/*!
		*
		**/
		virtual void GetControlGrid(const CGeoPoint<double> &pt, int &lbRow, int &lbCol) = 0;
		
		//
		//
		//
		/*!
		* fetch tesslellated unit
 		**/
		virtual bool MoveFirst(CGeoPoint<double> *pts, bool &isbordergrid) = 0;

		/*!
		*
		**/
		virtual bool MoveNext(CGeoPoint<double> *pts, bool &isbordergrid) = 0;

		/*!
		*
		**/
		virtual CGeoPoint<double> GetValue(int row, int col) = 0;

		//
		//
		//
		/*!
		*
		**/
		virtual CGeoPoint<double> *MakeRasterization(const CGeoRect<double> &extent, const string &field, int rows, int cols) = 0;

		/*!
		*
		**/
		virtual void SetBlankAreaNANValue(std::vector<std::vector<CGeoPoint<double>> > &blanks, bool isTempBlank=true, bool isNAN=true, double customvalue=ANY_NAN) = 0;
				
		/*!
		*
		**/
		virtual void SetCustomZValue() = 0;

	protected:
		// host object
		CAnyContour *m_contour;
	};

}
#endif