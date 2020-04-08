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
#ifndef __ANYVIS_CONTOUR_SURFACE_STRATEGY_H__
#define __ANYVIS_CONTOUR_SURFACE_STRATEGY_H__

// refer to macro
#include "anyvis.h"
#include "anyaxises.h"

// refer to geo point
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to canvas
#include "any/map/anycanvas.h"
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//
namespace AnyVis
{
	// forward class
	class CAnyContour;

	/*!
	*
	**/
	class CAnyContourSurfaceStrategy : private CAnyAxises
	{
	public:
		/*!
		* light camera definition
		**/
		struct CameraMatrix
		{
			// camera position
			CGeoPoint<double> m_position;

			// projection matrix
			double m_matrix[16];

			/*!
			*
			**/
			CameraMatrix() : m_position(0., 0., 0.)
			{
				::memset(m_matrix, 0x00, 16 * sizeof(double));
			}

			/*!
			*
			**/
			void Reset()
			{
				double xy = ::sqrt(m_position.m_x*m_position.m_x + m_position.m_y*m_position.m_y);
				double xyz = ::sqrt(xy *xy + m_position.m_z*m_position.m_z);

				m_matrix[0] =  -m_position.m_x*m_position.m_z;
				m_matrix[1] =  -m_position.m_y*m_position.m_z;
				m_matrix[2] = xy*xy;
				m_matrix[3] = 0.;
				m_matrix[4] =  -m_position.m_y*xyz;
				m_matrix[5] = m_position.m_x*xyz;
				m_matrix[6] = 0.;
				m_matrix[7] = 0.;
				m_matrix[8] =  -m_position.m_x*xy;
				m_matrix[9] =  -m_position.m_y*xy;
				m_matrix[10] = m_position.m_z*xy;
				m_matrix[11] = 0.;
				m_matrix[12] = 0.;
				m_matrix[13] = 0.;
				m_matrix[14] = 0.;
				m_matrix[15] = xy*xyz;

				if(m_matrix[15] == 0.0)
				{
					m_matrix[1] = m_matrix[4] = m_matrix[10] = m_matrix[15] = m_position.m_z;
				}
				else
				{
					for (int i = 0; i < 16; i++)
					{
						m_matrix[i] /= m_matrix[15];
					}
				}
			}

			/*!
			*
			**/
			const CameraMatrix &operator=(const CameraMatrix &other)
			{
				if(this == &other)
				{
					return *this;
				}
				
				m_position = other.m_position;

				Reset();

				return *this;
			}

			/*!
			*
			**/
			void Transform(const CGeoPoint<double> &wPt, CGeoPoint<double> &cPt)
			{
				cPt.m_y = wPt.m_x*m_matrix[0] + wPt.m_y*m_matrix[1] + wPt.m_z*m_matrix[2] + m_matrix[3] ;				// Y
				cPt.m_x = -(wPt.m_x*m_matrix[4] + wPt.m_y*m_matrix[5] + wPt.m_z*m_matrix[6] + m_matrix[7]) ;			// X
				cPt.m_z = -(wPt.m_x*m_matrix[8] + wPt.m_y*m_matrix[9] + wPt.m_z*m_matrix[10] + m_matrix[11]);		// Z	
				double d = 100000. - cPt.m_z;
				cPt.m_y = cPt.m_y * 100000. / d;
				cPt.m_x = cPt.m_x * 100000. / d;
			}

			/*!
			*
			**/
			void Rotate(CGeoPoint<double> &axis, double angle)
			{
				// normalize surrounding axis
				double det = ::sqrt(axis.m_x * axis.m_x + axis.m_y * axis.m_y + axis.m_z * axis.m_z);
				axis.m_x /= det;
				axis.m_y /= det;
				axis.m_z /= det;

				//calculate parameters of the rotation matrix
				double c = ::cos(angle);
				double s = ::sin(angle);
				double t = 1 - c;
      
				//multiply v with rotation matrix
				CGeoPoint<double> middle;
				middle.m_x = (t * axis.m_x * axis.m_x + c) * m_position.m_x
					+ (t * axis.m_x * axis.m_y + s * axis.m_z) * m_position.m_y
					+ (t * axis.m_x * axis.m_z - s * axis.m_y) * m_position.m_z;
             
				middle.m_y = (t * axis.m_x * axis.m_y - s * axis.m_z) * m_position.m_x 
					+ (t * axis.m_y * axis.m_y +          c) * m_position.m_y 
					+ (t * axis.m_y * axis.m_z + s * axis.m_x) * m_position.m_z;
             
				middle.m_z = (t * axis.m_x * axis.m_z + s * axis.m_y) * m_position.m_x 
					+ (t * axis.m_y * axis.m_z - s * axis.m_x) * m_position.m_y 
					+ (t * axis.m_z * axis.m_z +          c) * m_position.m_z;
      
				det = ::sqrt(middle.m_x * middle.m_x + middle.m_y * middle.m_y + middle.m_z * middle.m_z);
				middle.m_x /= det;
				middle.m_y /= det;
				middle.m_z /= det;

				det = ::sqrt(m_position.m_x * m_position.m_x + m_position.m_y * m_position.m_y + m_position.m_z * m_position.m_z);
				m_position.m_x = middle.m_x * det;
				m_position.m_y = middle.m_y * det;
				m_position.m_z = middle.m_z * det;

				Reset();
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyContourSurfaceStrategy(CAnyContour *contour);

		/*!
		*
		**/
		virtual ~CAnyContourSurfaceStrategy();

	public:
		//
		//
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<short> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<short> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<short> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<short> &scrPoint);

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
		virtual void MakeSurface();

		/*!
		*
		**/
		void Release();

	protected:
		//
		//
		//
		/*!
		*
		**/
		void Map2Scr(CGeoPoint<double> &mapPt, CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		void Scr2Map(CGeoPoint<double> &scrPt, CGeoPoint<double> &mapPt);

		//
		//
		//
		/*!
		* control point in world space
		**/
		virtual bool DoGetControlPts();

		/*!
		* transformed by camera simple matrix
		**/
		virtual void DoGetCameraPts();

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderAxises(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderCurves(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderGradient(CAnyCanvas &canvas, const CGeoPoint<double> *const pts, int count);

		//
		//
		//
		/*!
		*
		**/
		void DoGetCurMatrix(CGeoPoint<double> curMatrix[][4], int currow, int curcol);

		/*!
		*
		**/
		CGeoPoint<double> DoSplineInterpolation(CGeoPoint<double> curMatrix[][4], double u, double v, bool isRow = true);

	protected:
		// host object
		CAnyContour *m_contour;

		// transform matrix
		int m_matrixrows;
		int m_matrixcols;

		// 2D and 3D data
		// orignal 3D data is directly from grid tracing
		// in tesslated units
		int m_ptrows;
		int m_ptcols;

		// control pts in world space
		CGeoPoint<double> **m_wPts;
		CGeoRect<double> m_wExtent;
		CGeoPoint<double> m_wCenter;

		// transformed pts and extent in view space
		CGeoPoint<double> **m_vPts;
		CGeoRect<double> m_vExtent;
		CGeoPoint<double> m_vCenter;

		// camera matrix
		CameraMatrix m_camera;
	public:
		//
		bool m_isInitialized;
	};

}
#endif