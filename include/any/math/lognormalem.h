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
#ifndef __ANYMATH_LOGNORMAL_EM__ALGORITHM_H__
#define __ANYMATH_LOGNORMAL_EM__ALGORITHM_H__

// refer to macro
#include "anymath.h"

// refer to parent
#include "anyexpectationmaximization.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CLognormalEM : public CAnyExpectationMaximization
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CLognormalEM();

		/*!
		*
		**/
		~CLognormalEM();

	public:
		//
		//
		//
		/*!
		*
		**/
		double *MakeEMKN(int& maxLoops, double error = errorlimit);
		double *MakeEMN(int numberScale, int& maxLoops, double error = errorlimit);

	private:
		double InitParameter(double sita[3]);
		double ObjectiveFunction(double sita[2]);
		void KInitParameter(double sita[2]);
		/*!
		* ¸ÅÂÊÃÜ¶Èº¯Êý
		**/
		double GetPDF(double x,double b,double s);
	};
}

#endif
