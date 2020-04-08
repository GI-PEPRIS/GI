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
#ifndef __ANYMATH_KRIG_BAYESIAN_SIMULATOR_H__
#define __ANYMATH_KRIG_BAYESIAN_SIMULATOR_H__

// refer to macro
#include "anymath.h"
#include "anykrigsimulator.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyBayesKrigSimulator : public CAnyKrigSimulator
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyBayesKrigSimulator(CAnyKrigSimulator *priorsimulator);
		~CAnyBayesKrigSimulator();

		//
		void GetSampleVariance(std::vector<CGeoPoint<double> >&variances, double tolerance = 1.);
		void BayesianKrigDirect(std::vector<CGeoPoint<double> > &locations, int rows = 0, int cols = 0);

	public:
		// prior simulator
		CAnyKrigSimulator *m_prior_simulator;

	};
}


#endif