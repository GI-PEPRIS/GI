/*!
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYCGAL_MAP_MORPHOMETRIC_ANALYSIS_H__
#define __ANYCGAL_MAP_MORPHOMETRIC_ANALYSIS_H__

// macro
#include "anycgal.h"

//
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyCGAL
{
	/*!
	*
	**/
	class ANYCGAL_CLASS CAnyMapMorphometricAnalysis
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyMapMorphometricAnalysis();
		~CAnyMapMorphometricAnalysis();

	public:
		//
		// geomorphometric parameterization
		//
		/*!
		*
		**/
		struct GeomorphometricParameter
		{
			CGeoPoint<double> m_pos;
			double m_slope;
			double m_aspect;
			double m_profc;		// profile convexity, rate of change in gradient, reflect the change gradient of slope, 
			double m_planc;		// plan convexity, convexity of contours, reflect the change gradient of aspect
			double m_longc;		// longitudinal curvature
			double m_crosc;		// cross-sectional curvature
			double m_maxic;		 // maximum curvature
			double m_minic;		// minimum curvature
			double m_meanc;		// mean curvature
		};

		//
		// vector field analysis
		//
		/*!
		*
		**/
		struct StreamLine
		{
			CGeoPoint<double> *m_pts;
			int m_number;

			StreamLine() : m_pts(0), m_number(0)
			{
			}
		};
		/*!
		* CGeoPoint as a vector: from(x,y) to(z,w) means direction, the length means magnitude
		**/
		void PlacementofStreamlines(CGeoPoint<double> *pts, int rows, int cols, StreamLine **lines, int &linenumber); // 2D streamline placement from a vector field defined on a regular grid
		void PlacementofStreamlines(CGeoPoint<double> *pts, int number, StreamLine **lines, int &linenumber); // on a triangular grid.
	};
}
#endif