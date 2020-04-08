 /* The AnyCGAL of PetroCOVERY solution is a collection of packages based on native C++ classes
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
#ifndef __ANYCGAL_GEOFRACTURE_SURFACE_FIT_H__
#define __ANYCGAL_GEOFRACTURE_SURFACE_FIT_H__

// macro
#include <vector>
using namespace std;

#include "anycgal.h"
#include "geovectordo.h"

//
namespace AnyCGAL
{
	class CGeoVectorDo;

	/*!
	*	SurfaceFit.cs;
	**/
	class ANYCGAL_CLASS CGeoSurfaceFit
	{
	public:
		CGeoSurfaceFit();
		~CGeoSurfaceFit();
		
		// 用最小二剩法拟合曲面方程
		// z   = b0*1 + b1*x + b2*y + b3*x2 + b4*xy + b5*y2  + b6*x3  + b7*x2y + b8*xy2 + b9*y3 +...
		// X'XB = X'Z 
		//     1  x[1]  y[1]  x[1]^2  x[1]y[1]  y[1]^2  x[1]^3  x[1]^2y[1]  x[1]y[1]^2  y[1]^3 ...
		//     1  x[2]  y[2]  x[2]^2  x[2]y[2]  y[2]^2  x[2]^3  x[2]^2y[2]  x[2]y[2]^2  y[2]^3 ...
		// X = 1  x[3]  y[3]  x[3]^2  x[3]y[3]  y[3]^2  x[3]^3  x[3]^2y[3]  x[3]y[3]^2  y[3]^3 ...
		//     .  .     .     .       .         .       .       .           .           .      ...
		//     1  x[n]  y[n]  x[n]^2  x[n]y[n]  y[n]^2  x[n]^3  x[n]^2y[n]  x[n]y[n]^2  y[n]^3 ...
		//
		// B' = [ b[0] b[1] b[2] b[3] b[4] b[5] b[6] b[7] b[8] b[9] ... ]
		//
		// Z' = [x[0] x[1] ... x[n] ]
		bool FitRootsetGauss(CGeoVectorDo::GeoPointVector &vertexes, int numCubic);
		bool FitRootsetMqr(CGeoVectorDo::GeoPointVector &vertexes, int numCubic);
		bool FitGauss(CGeoVectorDo::GeoPointVector &vertexes, int numCubic);

		//
		//
		//
		/*!
		*
		**/
		void SetData(int numCubic, double *bMatrix, int bMatrixNum);

		/*!
		*
		**/
		double GetDxyValueAt(double x, double y);
		double GetDx2ValueAt(double x, double y);
		double GetDy2ValueAt(double x, double y);
		double GetValueAt(double x, double y);

		/*!
		*
		**/
		void MainCurvature(CGeoVectorDo *v);
		void MainCurvature(double x, double y, double &r1, double &r2, double &azimuth);

		//
		//LinearEquations.cs method
		//
		/*!
		* 最小二乘法
		**/
		static bool RootSetGauss(double **XMatrix, int XMatrixNum, double *Z, int zNum, double * &result);

		/*!
		*全主元,消除前排主项
		**/
		static bool Gauss(double **matrix, double *mb, int mbNum);
		
	private:
		static int _CalcEquationItemNumber(int numCubic);
		static int _CalcCubicNumber(int numItem);
		void Release();

	public:
		// 方程次数
		int _NumCubic;
		// 方程系数
		double *_BMatrix;
		// dxdy 系数
		double *_BXYMatrix;
		// dx2 系数
		double *_BX2Matrix;
		// dy2 系数
		double *_BY2Matrix;

		//
		static double _MaxDifference;
	};
}
#endif
