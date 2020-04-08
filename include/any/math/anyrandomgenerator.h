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
#ifndef __ANYMATH_RANDOM_GENERATOR_H__
#define __ANYMATH_RANDOM_GENERATOR_H__

// refer to export/import macroes
#include "anymath.h"

// refer to std
#include "any/base/anystl.h"

// refer to boost
#include "boost/random/variate_generator.hpp"
#include "boost/random/mersenne_twister.hpp"
#include "boost/random/uniform_smallint.hpp"
#include "boost/random/uniform_int.hpp"
#include "boost/random/uniform_real.hpp"
#include "boost/random/bernoulli_distribution.hpp"
#include "boost/random/binomial_distribution.hpp"
#include "boost/random/geometric_distribution.hpp"
#include "boost/random/poisson_distribution.hpp"
#include "boost/random/exponential_distribution.hpp"
#include "boost/random/gamma_distribution.hpp"
#include "boost/random/normal_distribution.hpp"
#include "boost/random/lognormal_distribution.hpp"
#include "boost/random/cauchy_distribution.hpp"
#include "boost/random/triangle_distribution.hpp"
#include "boost/random/uniform_on_sphere.hpp"
using namespace boost::random;

#pragma warning(disable : 4244) 

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyRandomGenerator
	{
	public:
		//
		typedef std::vector<double> RandomVector;
		typedef std::vector<string> NameVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		~CAnyRandomGenerator()
		{
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual void GetRandoms(RandomVector &randoms) = 0;

		//
		//
		//
		/*!
		*
		**/
		static int GetGeneratorCount();

		/*!
		*
		**/
		static const string &GetGeneratorName(int order);

		/*!
		* factory method
		**/
		static CAnyRandomGenerator *GetGenerator(const string &name, double min, double mid, double max, unsigned int seed = 0);

	protected:
		//
		static NameVector m_names;
	};

	/*!
	*
	**/
	template<typename DistributionMode>
	class CBoostRandomGenerator : public CAnyRandomGenerator
	{
		// traits
		typedef DistributionMode type;

		// random collection
		typedef std::vector<typename DistributionMode::result_type> collection;

	public:
		//
		//
		//
		/*!
		* for kinds of means: alpha, sigma, lambda
		**/
		CBoostRandomGenerator(typename DistributionMode::input_type const &min, typename DistributionMode::input_type const &max, unsigned int seed = 0)
			: m_mode(min, max), m_seed(seed ? seed : std::time(0)), m_generator(m_seed, m_mode)
		{
		}

		/*!
		*  for binomal
		**/
		CBoostRandomGenerator(unsigned int t, double probability, unsigned int seed = 0)
			: m_mode(t, probability), m_seed(seed ? seed : std::time(0)), m_generator(m_seed, m_mode)
		{
		}

		/*!
		*  for discrete distributions
		**/
		CBoostRandomGenerator(double probability, unsigned int seed = 0)
			: m_mode(probability), m_seed(seed ? seed : std::time(0)), m_generator(m_seed, m_mode)
		{
		}

		/*!
		*  for triangle distribution
		**/
		CBoostRandomGenerator(double a, double b, double c, unsigned int seed = 0)
			: m_mode(a, b, c), m_seed(seed ? seed : std::time(0)), m_generator(m_seed, m_mode)
		{
		}

		/*!
		* for uniform
		**/
		CBoostRandomGenerator(unsigned int seed = 0)
			: m_seed(seed ? seed : std::time(0)), m_generator(m_seed, m_mode)
		{
		}

	public:
		//
		//
		//
		/*!
		* Retrieve one random number
		**/
		typename DistributionMode::result_type operator()() 
		{ 
			return m_generator();
		}

		/*!
		* Retrieves a vector of random numbers
		**/
		void GetRandoms(RandomVector &randoms)
		{
			assert(randoms.size());
			std::generate(randoms.begin(), randoms.end(), *this);
		}

	private:
		//
		boost::mt19937  m_seed;
		DistributionMode m_mode;
		boost::variate_generator<boost::mt19937, DistributionMode> m_generator;
	};

	// uniform related
	typedef CBoostRandomGenerator<boost::uniform_smallint<> > UniformSmallIntGenerator;
	typedef CBoostRandomGenerator<boost::uniform_01<> > Uniform01Generator;
	typedef CBoostRandomGenerator<boost::uniform_int<> > UniformIntGenerator;
	typedef CBoostRandomGenerator<boost::uniform_real<> > UniformRealGenerator;

	// bernoulli related
	typedef CBoostRandomGenerator<boost::bernoulli_distribution<> > BernoulliGenerator;
	typedef CBoostRandomGenerator<boost::binomial_distribution<> > BinomialGenerator;
	typedef CBoostRandomGenerator<boost::geometric_distribution<> > GeometricGenerator;

	// possian related
	typedef CBoostRandomGenerator<boost::poisson_distribution<> > PoissonGenerator;
	typedef CBoostRandomGenerator<boost::exponential_distribution<> > ExponentialGenerator;
	typedef CBoostRandomGenerator<boost::gamma_distribution<> > GammaGenerator;

	// normal related
	typedef CBoostRandomGenerator<boost::normal_distribution<> > NormalGenerator;
	typedef CBoostRandomGenerator<boost::lognormal_distribution<> > LognormalGenerator;
	typedef CBoostRandomGenerator<boost::cauchy_distribution<> > CauchyGenerator;

	// miscelleous related
	typedef CBoostRandomGenerator<boost::triangle_distribution<> > TriangleGenerator;
	typedef CBoostRandomGenerator<boost::uniform_on_sphere<> > SphereGenerator;
}

#endif