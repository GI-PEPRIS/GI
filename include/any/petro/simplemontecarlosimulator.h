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
#ifndef __ANYPETRO_SIMPLE_MONTECARLO_SIMULATOR_H__
#define __ANYPETRO_SIMPLE_MONTECARLO_SIMULATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

//
#include "any/base/anystl.h"

// refer to distribution
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CSimpleMonteCarloSimulator
	{
	public:
		/*!
		*
		**/
		enum SimulationType
		{
			ST_Unknown,
			ST_Sum,
			ST_Analog,
			ST_MAX
		};

		/*!
		*
		**/
		struct DistributionSimulated
		{
			CAnyDistributionStrategy *m_distribution;
			double m_success_probability;
			double m_ratio;

			DistributionSimulated(): m_distribution(0), m_success_probability(1.), m_ratio(1.)
			{

			}
		};
		typedef std::vector<DistributionSimulated> DistributionVector;
		typedef std::vector<DistributionVector > DistributionVectorVector;

	public:
		CSimpleMonteCarloSimulator(void);
		~CSimpleMonteCarloSimulator(void);

	public:
		// simple sum
		void MakeSimulation(const DistributionVector &distributions, int simulations, short simulationtype);
		// analog
		void MakeSimulation(const DistributionVectorVector &distributions, int simulations, short simulationtype);

		// results
		double GetQuantile(double probability, bool isabundance = false);

	private:
		//
		static int CompareSampleValue( const void *a , const void *b ) 
		{ 
			return (*(double*)b-*(double*)a > 0) ? 1 : -1;
		}

	private:
		double m_seed;
		std::vector<double> m_samples_simulated;
		std::vector<double> m_samples_simulated_abundance;
		short m_simulaiton_type;
	};
}

#endif