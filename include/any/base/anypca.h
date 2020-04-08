/**
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
#ifndef __ANYBASE_MATH_PCA_H__
#define __ANYBASE_MATH_PCA_H__

// Refer to EXPORT definition
#include "anybase.h"

//
namespace AnyBase
{
	/*!
	*
	**/
	class ANYBASE_CLASS CAnyPCA
	{
		//
		#define SIGN(a, b) ( (b) < 0 ? -::fabs(a) : ::fabs(a) )

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyPCA();

		/*!
		*
		**/
		~CAnyPCA();

	public:
		//
		//
		//
		/*!
		*
		**/
		double **AllocateMatrix(int n, int m);

		/*!
		*
		**/
		double *AllocateVector(int n);

		/*!
		*
		**/
		void FreeVector(double *v, int n);

		/*!
		*
		**/
		void FreeMatrix(double **mat, int n, int m);

		/*!
		*
		**/
		void AnalyzePCA(int type, double **data, double **symcols, int n, int m, int components = 3);

		//
		//
		//
		/*!
		*
		**/
		void GetCorrelation(double **data, int n, int m, double **symmat);

		/*!
		*
		**/
		void GetCovariance(double **data, int n, int m, double **symmat);

		/*!
		*
		**/
		void GetCrossProducts(double **data, int n, int m, double **symmat);

	private:
		//
		//
		//
		/*!
		*
		**/
		void Sym2Trid(double **a, int n, double *d, double *e);

		/*!
		*
		**/
		void Sym2Tqli(double *d, double *e, int n, double **z);
	};
}

#endif