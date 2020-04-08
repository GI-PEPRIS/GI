/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGDE_SAMPLE_DATA_UTILITY_POLYGON_H__
#define __ANYGDE_SAMPLE_DATA_UTILITY_POLYGON_H__

// refer to EXPORT & IMPORT
#include "anygde.h"

// refer to geom
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataPolygon
	{
	public:
		//
		typedef std::vector<CGeoPoint<double> > CornerVector;
		typedef CornerVector::iterator cor_itr;
		typedef CornerVector::const_iterator cor_citr;

		/*!
		*
		**/
		struct IntersectPoint
		{
			//
			CGeoPoint<double> m_position;
			double m_distance;

			/*!
			*
			**/
			IntersectPoint() : m_distance(0)
			{
				m_position.m_x = 0.;
				m_position.m_y = 0.;
			}
		};
		typedef std::vector<IntersectPoint> IntersectPointVector;

		/*!
		*
		**/
		struct IntersectLine
		{
			CGeoPoint<double> m_first;
			CGeoPoint<double> m_second;

			/*!
			*
			**/
			IntersectLine()
			{
				m_first.m_x = m_first.m_y = 0.;
				m_second.m_x = m_second.m_y = 0.;
			}
		};
		typedef std::vector<IntersectLine> IntersectLineVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataPolygon(CornerVector &corners);

		/*!
		*
		**/
		CAnyGdeDataPolygon()
		{
		}

		/*!
		*
		**/
		~CAnyGdeDataPolygon();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetCorners(const CornerVector &corners);

		/*!
		*
		**/
		const CornerVector &GetCorners();

		/*!
		*
		**/
		void Clear()
		{
			m_corners.clear();
		}

		//
		//
		//
		/*!
		*
		**/
		bool IsPolygon() const;

		/*!
		*
		**/
		bool IsCoverPoint(double xa, double ya);

		//
		//
		//
		/*!
		*
		**/
		void IntersectWithLine(double xa,double ya,double xb,double yb, IntersectLineVector &lines);

	private:
		/*!
		* 计算两线段的交点
		**/
		static bool CalCross(const double x1[2],const double y1[2],const double x2[2],const double y2[2],double &x,double &y);

	private:
		//
		CornerVector m_corners;
	};
}
#endif