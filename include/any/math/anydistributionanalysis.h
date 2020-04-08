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
#ifndef __ANYMATH_DISTRIBUTION_ANALYSIS_H__
#define __ANYMATH_DISTRIBUTION_ANALYSIS_H__

// refer to macro
#include "anymath.h"

// refer to its host distribution
#include "anydistributionstrategy.h"

// namespace
namespace AnyMath
{
	/*! 
	* mainly refer to students-t distribution, chi-squared distribution, f-distribution for the 
	* analysis of samples and results
	**/
	class ANYMATH_CLASS CAnySensitivityAnalysis
	{
	public:
		/*!
		*
		**/
		struct HypothesisComparison
		{
			bool m_isNoDifference;
			bool m_isDifference;
			bool m_isGreater;
			bool m_isLesser;

			/*!
			*
			**/
			HypothesisComparison() : m_isNoDifference(true), m_isDifference(true), m_isGreater(true), m_isLesser(true)
			{
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySensitivityAnalysis(CAnyDistributionStrategy *distribution);

		/*!
		*
		**/
		~CAnySensitivityAnalysis();

	public:
		//
		// related to students-t distribution
		//
		/*!
		*
		**/
		void GetMeanExtent(double alpha, double &lower, double &upper);

		/*!
		* false means not rejected, true means rejected
		**/
		void CompareMean(double alpha, double expected, HypothesisComparison &comparisons);

		/*!
		*
		**/
		void CompareMean(double alpha, CAnyDistributionStrategy *other, HypothesisComparison &comparisons);

		/*!
		*
		**/
		int GetMeanLimits(double alpha, double expected, bool isOneSide);

		//
		// related to chi-squared distribution
		//
		/*!
		*
		**/
		void GetSDExtent(double alpha, double &lower, double &upper);

		/*!
		* false means not rejected, true means rejected
		**/
		void CompareSD(double alpha, double expected, HypothesisComparison &comparisons);

		/*!
		*
		**/
		int GetSDLimits(double alpha, double diff, double expected, bool isLower);

		/*!
		* critical value
		**/
		double GetDesiredSquiredValue(double alpha, int freedoms);

		/*!
		*
		**/
		double GetEstimatedSquaredValue(std::vector<double> &samples, std::vector<double> &predications);

		//
		// related to F-distribution
		//
		/*!
		*
		**/
		void CompareSD(double alpha, CAnyDistributionStrategy *other, HypothesisComparison &comparisons);

		//
		// related to binomial distribution
		//
		/*!
		*
		**/
		void GetFrequenceLimits(double alpha, int trials, int successes, double &lower, double &upper, bool isJeffery = false);

		/*!
		*
		**/
		int GetMaxSampleSize(double alpha, double ratio, int successes);

		//
		// related to negative binomial distribution
		//
		/*!
		*
		**/
		void GetOccuranceLimits(double alpha, int trials, int successes, double &lower, double &upper);

		/*!
		*
		**/
		int GetMinSampleSize(double alpha, double ratio, double failures);

	private:
		//
		CAnyDistributionStrategy *m_distribution;
	};
}
#endif