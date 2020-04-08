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
#ifndef __ANYMATH_DIRECT_PARAMETER_STRATEGY_H__
#define __ANYMATH_DIRECT_PARAMETER_STRATEGY_H__

// refer to macro
#include "anymath.h"

// refer to distributionparameter
#include "anydistributionstrategy.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyDirectParameterStrategy
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyDirectParameterStrategy();

		/*!
		*
		**/
		~CAnyDirectParameterStrategy();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool DirectEstimate(const string &name, CAnyDistributionStrategy::DistributionParameters &parameter, double p90, double p10, double mean = 0., double min = 0., double max = 0.);
	};
}

#endif
