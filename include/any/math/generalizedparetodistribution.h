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
#ifndef __ANYMATH_GENERALIZED_PARETO_DISTRIBUTION_H__
#define __ANYMATH_GENERALIZED_PARETO_DISTRIBUTION_H__

// refer to parent
#include "anydistributionstrategy.h"

// namespace
namespace AnyMath
{
	/*!
	* generalized pareto 
	**/
	class CGeneralizedParetoDistribution : public CAnyDistributionStrategy
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CGeneralizedParetoDistribution();

		/*!
		*
		**/
		~CGeneralizedParetoDistribution();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool InitSamples(const string &name, CGeoPoint<double> *samples, int number, const DistributionParameters &parameters);
	
		/*!
		*
		**/
		void GetRange(CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		const DistributionStatistics &GetStatistics();

		/*!
		*
		**/
		double GetPDF(double &z, bool isForTruncation = false);

		/*!
		*
		**/
		double GetCDF(double z, bool isComplement = false, bool isForTruncation = false);

		/*!
		*
		**/
		double GetQuantile(double probability, bool isForTruncation = false);

	private:
		//
		// calculate the distribution parameters
		//
		/*!
		*
		**/
		double DoGetAlpha();

		/*!
		*
		**/
		double DoGetLambda();

		/*!
		*
		**/
		double DoCalculateSD(double q);

		/*!
		*
		**/
		void DoGetLikelihoodParameter();

	private:
		//
		//
		//
		/*!
		*
		**/
		double GetFormularPDF(double z, bool isForTruncation);

		/*!
		*
		**/
		double GetFormularCDF(double z, bool isForTruncation);

		/*!
		*
		**/
		double GetFormularQuantile(double probability, bool isForTruncation);

		/*!
		*
		**/
		bool IsFindNextQ(double probability, double nextQ, double prevQ, double &rtQ);

		//
		// maximum likelihood
		//
		/*!
		*
		**/
		void DoGetMaxLikeEquationValue(double curAlpha, double curLambda, double &aPrecision, double &lPrecision);

		/*!
		*
		**/
		void DoGetJacobiMatrix(double curAlpha, double curLambda, double &a11, double &a12, double &a21, double &a22);

		/*!
		*
		**/
		void DoGetInverseJacobiMatrix(double a11, double a12, double a21, double a22, double &b11, double &b12, double &b21, double &b22);

		/*!
		*
		**/
		int DoAdjustRelaxiationFactor(double curAlpha, double curLambda, double &nextAlpha, double &nextLambda, double aCurPrecision, double lCurPrecision, double aDiff, double lDiff);

		//
		//
		//
		/*!
		*
		**/
		double DoGetDenominator(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetFirstNumerator(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetSecondNumerator(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetDenominatorFirstDerivative(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetDenominatorSecondDerivative(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetFirstNumeratorFirstDerivative(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetFirstNumeratorSecondDerivative(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetSecondNumeratorFirstDerivative(double curQ, double minQ, double maxQ, double curLambda);

		/*!
		*
		**/
		double DoGetSecondNumeratorSecondDerivative(double curQ, double minQ, double maxQ, double curLambda);

	};
}

#endif