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
#ifndef __ANYMATH_TRUNCATED_LOGNORMAL_DISTRIBUTION_H__
#define __ANYMATH_TRUNCATED_LOGNORMAL_DISTRIBUTION_H__

// refer to parent
#include "anydistributionstrategy.h"

// namespace
namespace AnyMath
{
	/*!
	* also called histogram distribution
	**/
	class CTruncatedLognormalDistribution : public CAnyDistributionStrategy
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CTruncatedLognormalDistribution();

		/*!
		*
		**/
		~CTruncatedLognormalDistribution();

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

		//
		//
		//
		/*!
		*
		**/
		double GetPDF(double z);

		/*!
		*
		**/
		double GetCDF(double z, bool isComplement = false);

		/*!
		*
		**/
		double GetQuantile(double probability, bool isOneSided = false);
	};
}

#endif