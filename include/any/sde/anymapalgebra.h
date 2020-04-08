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
#ifndef __ANYSDE_SDE_MAP_ALGEBRA_H__
#define __ANYSDE_SDE_MAP_ALGEBRA_H__

// refer to EXPORT & IMPORT
#include "anyrasterspatialanalysis.h"

// namespace
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnyMapAlgebra : public CAnyRasterSpatialAnalysis
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyMapAlgebra();
		CAnyMapAlgebra(CAnyView &curView);//2015/7/30: paint cells
		CAnyMapAlgebra(CAnyViewHook *layer);
		CAnyMapAlgebra(int rows, int cols);
		~CAnyMapAlgebra();

		CAnyMapAlgebra(const CAnyMapAlgebra &other);
		const CAnyMapAlgebra &operator=(const CAnyMapAlgebra &other);
	public:
		//
		//
		//
		/*!
		*
		**/
		void SetLayerName(const string &name);
		string GetLayerName();
	
		//
		//
		//
		/*!
		*
		**/
		bool MakeRasterizations(const CGeoRect<double> &extent, const string &field, int rows, int cols);

		//
		// binary operations including basic operators such as arithmetic, relational, boolean, combinatorial, assignment etc
		//
		/*!
		*
		**/
		CAnyMapAlgebra operator+(const CAnyMapAlgebra &other);
		CAnyMapAlgebra operator-(const CAnyMapAlgebra &other);
		CAnyMapAlgebra operator*(const CAnyMapAlgebra &other);
		CAnyMapAlgebra operator/(const CAnyMapAlgebra &other);

		/*!
		*
		**/
		CAnyMapAlgebra operator+(double scalar);
		CAnyMapAlgebra operator-(double scalar);
		CAnyMapAlgebra operator*(double scalar);
		CAnyMapAlgebra operator/(double scalar);

		/*!
		*
		**/
		CAnyMapAlgebra operator+=(const CAnyMapAlgebra &other);
		CAnyMapAlgebra operator-=(const CAnyMapAlgebra &other);
		CAnyMapAlgebra operator*=(const CAnyMapAlgebra &other);
		CAnyMapAlgebra operator/=(const CAnyMapAlgebra &other);

		/*!
		*
		**/
		void pow(const CAnyMapAlgebra &other);
		void fabs();
		void sqrt();
		void sinh();
		void cosh();
		void tanh();
		void atan();
		void log();
		void log10();
		void exp();
		void sin();
		void cos();
		void cot();
		void tan();
		void asin();
		void acos();
		void integer();

		void Signl();
		void RAD();
		void DEG();
		void ArSinh();
		void ArCosh();
		void ArTanh();

		//
		bool MouseDown(const CGeoPoint<double> &scrPoint);
		bool MouseMove(const CGeoPoint<double> &scrPoint);
		bool MouseUp(const CGeoPoint<double> &scrPoint);
		bool DoubleClick(const CGeoPoint<double> &scrPoint);
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);

		/*!
		*2015/7/29
		**/
		void OperateCells(const std::string &operatorStr, double threshold);

	public:
		// as unique identification
		string m_name; 
	};
}

#endif
