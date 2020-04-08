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
#ifndef __ANYMATH_BOOST_DISTRIBUTION_H__
#define __ANYMATH_BOOST_DISTRIBUTION_H__

// refer to its parent
#include "anydistributionstrategy.h"

// refer to lognormal truncation
#include "shifttruncatedlognormaldistribution.h"
// refer to replacement of general truncation
#include "userdistribution.h"

// refer to type2type
#include "any/base/loki/generic.h"
using namespace AnyBase::Loki;

// refer to kinds of distributoins
#include "boost/math/distributions.hpp"
using namespace boost::math;

//
#pragma warning( push )
#pragma warning( disable: 4715 ) 

//
namespace AnyMath
{
	/*!
	*
	**/
	template<class T, class B>
	class CBoostDistribution : public B
	{
		// traits
		typedef T DistributionType;

	public:
		//
		//
		//
		/*!
		*
		**/
		CBoostDistribution() : m_distribution(0)
		{
			//
			m_pi = 3.14159265358979323846264338327950288419716939937510;
			m_euler = 0.57721566490153286060651209008240243104215933593992;
		}

		/*!
		*
		**/
		virtual ~CBoostDistribution()
		{
			if(m_distribution)
			{
				delete m_distribution;
			}
			m_distribution = 0;
		}

	public:
		//
		// statistic variables
		//
		/*!
		*
		**/
		bool InitSamples(const string &name, CGeoPoint<double> *samples, int number, const CAnyDistributionStrategy::DistributionParameters &parameters)
		{
			//
			bool rt = CAnyDistributionStrategy::InitSamples(name, samples, number, parameters);
			if(rt)
			{
				rt = DoCreate(Type2Type<T>());
				if(rt)
				{
					/*if(m_name != "lognormal" && m_parameters.IsTruncated())
					{
						assert(!m_truncation);
						m_truncation = new CUserDistribution(this);
						m_truncation->InitSamples("user", m_samples, m_number, parameters);
						m_truncation->MakeInterpolations();
					}*/
					//without user distribution
					//if(m_parameters.IsTruncated())
					//{
					//	//assert(!m_truncation);
					//	//m_truncatedDistribution=new CBoostDistribution();
					//	//m_truncatedDistribution->SetDistribution(this);
					//}
				}
			}

			return rt;
		}

		/*!
		*
		**/
		const CAnyDistributionStrategy::DistributionStatistics &GetStatistics()
		{
			//
			if(m_parameters.IsTruncated())
			{
				//if(m_truncation)
				//{
				//	m_stats = m_truncation->GetStatistics();

				//	//m_stats.m_mean = m_truncation->DoGetMean();
				//	//m_stats.m_median = m_truncation->GetQuantile(0.5, true);
				//	//m_stats.m_mode = m_truncation->DoGetMode();
				//	//m_stats.m_sd = m_truncation->DoGetSD();
				//}
				//else
				//{
				//	m_stats.m_mean = ANY_NAN;
				//	m_stats.m_median = ANY_NAN;
				//	m_stats.m_mode = ANY_NAN;
				//	m_stats.m_sd = ANY_NAN;
				//}

				m_interNumber = 80000;
				if(m_interPts)
				{
					::free(m_interPts);
				}
				m_interPts=(CGeoPoint<double> *)::malloc(m_interNumber * sizeof(CGeoPoint<double>));
				double step = (m_parameters.m_tMax-m_parameters.m_tMin)/m_interNumber;
				for(int i=0;i<m_interNumber;i++)
				{
					m_interPts[i].m_x=m_parameters.m_tMin+i*step;
					m_interPts[i].m_y=GetPDF(m_interPts[i].m_x,true);
				}

				//mean
				double sum=0,weight=0;
				for(int i=0;i<m_interNumber-1;i++)
				{
					sum+=(m_interPts[i+1].m_x+m_interPts[i].m_x)/2*m_interPts[i].m_y*(m_interPts[i+1].m_x-m_interPts[i].m_x);
					//weight+=m_interPts[i].m_y;
				}
				m_stats.m_mean=sum/*/weight*/;

				if(m_parameters.m_isNormalized)
				{
					m_stats.m_mean = m_parameters.m_tMin + (m_parameters.m_tMax - m_parameters.m_tMin) * m_stats.m_mean;
				}


				//sd
				sum=0,weight=0;
				for(int i=0;i<m_interNumber;i++)
				{
					sum+=(m_interPts[i].m_x-m_stats.m_mean)*(m_interPts[i].m_x-m_stats.m_mean)*m_interPts[i].m_y;
					weight+=m_interPts[i].m_y;
				}
				m_stats.m_sd=sqrt(sum/weight);

				//mode
				double maxY=0;
				m_stats.m_mode=m_parameters.m_tMin;
				for(int i=0;i<m_interNumber;i++)
				{
					
					if(maxY<m_interPts[i].m_y)
					{
						m_stats.m_mode=m_interPts[i].m_x;
						maxY=m_interPts[i].m_y;
					}
				}
				if(m_parameters.m_isNormalized)
				{
					m_stats.m_mode = m_parameters.m_tMin + (m_parameters.m_tMax - m_parameters.m_tMin) * m_stats.m_mode;
				}
				//median
				m_stats.m_median = GetQuantile(0.5,true);
				return m_stats;
			}

			//
			try
			{
				m_stats.m_mean = mean(*m_distribution);
				if(m_parameters.m_isNormalized)
				{
					m_stats.m_mean = m_parameters.m_min + (m_parameters.m_max - m_parameters.m_min) * m_stats.m_mean;
				}
			}
			catch(...)
			{
				m_stats.m_mean = ANY_NAN;
			}

			try
			{
				m_stats.m_median = median(*m_distribution);
				if(m_parameters.m_isNormalized)
				{
					m_stats.m_median = m_parameters.m_min + (m_parameters.m_max - m_parameters.m_min) * m_stats.m_median;
				}
			}
			catch(...)
			{
				m_stats.m_median = ANY_NAN;
			}

			try
			{
				m_stats.m_mode = mode(*m_distribution);
				m_stats.m_mode = m_stats.m_mode == 0. ? ANY_NAN : m_stats.m_mode;
				if(m_parameters.m_isNormalized)
				{
					m_stats.m_mode = m_parameters.m_min + (m_parameters.m_max - m_parameters.m_min) * m_stats.m_mode;
				}
			}
			catch(...)
			{
				m_stats.m_mode = ANY_NAN;
			}

			try
			{
				m_stats.m_sd = standard_deviation(*m_distribution);
				if(m_parameters.m_isNormalized)
				{
					m_stats.m_sd = m_stats.m_sd * DoGetMax();
				}
			}
			catch(...)
			{
				m_stats.m_sd = ANY_NAN;
			}

			try
			{
				m_stats.m_variance = variance(*m_distribution);
				if(m_parameters.m_isNormalized)
				{
					m_stats.m_variance = m_stats.m_variance *  DoGetMax();
				}
			}
			catch(...)
			{
				m_stats.m_variance = ANY_NAN;
			}

			return m_stats;
		}

		/*!
		*
		**/
		void GetRange(CGeoRect<double> &mapExtent)
		{
			double min=(m_parameters.m_isLogAxis) ? ::log(m_parameters.m_min) : m_parameters.m_min;
			double max=(m_parameters.m_isLogAxis) ? ::log(m_parameters.m_max) : m_parameters.m_max;
			double tmin=(m_parameters.m_isLogAxis) ? ::log(m_parameters.m_tMin) : m_parameters.m_tMin;
			double tmax=(m_parameters.m_isLogAxis) ? ::log(m_parameters.m_tMax) : m_parameters.m_tMax;
			if(m_parameters.IsTruncated())
			{
				//if(m_truncation)
				//{
				//	mapExtent.m_minX = m_truncation->GetParameters().m_tMin;
				//	mapExtent.m_maxX = m_truncation->GetParameters().m_tMax;

				//	// pdf should be normalization
				//	mapExtent.m_minY = 0.;
				//	mapExtent.m_maxY = 1.;
				//	return ;
				//}
				mapExtent.m_minX = tmin;
				mapExtent.m_maxX = tmax;

				// pdf should be normalization
				mapExtent.m_minY = 0.;
				mapExtent.m_maxY = 1.;
				return ;
			}

			try
			{
				mapExtent.m_minX = (ISNAN(min)) ? range(*m_distribution).first : min;
				mapExtent.m_maxX = (ISNAN(max)) ? range(*m_distribution).second :max;
				
				// pdf should be normalization
				mapExtent.m_minY = 0.;
				mapExtent.m_maxY = 1.;
			}
			catch(...)
			{
				// if meet with exception, use default value
				mapExtent.m_minX = min;
				mapExtent.m_maxX = max;
				mapExtent.m_minY = 0.;
				mapExtent.m_maxY = 1.;
			}
		}

		//
		// 
		//
		/*!
		*
		**/
		double GetPDF(double &z, bool isForTruncation = false)
		{
			try
			{
				double value=0.0;

			
			
				// whether truncated
				if(isForTruncation && m_parameters.IsTruncated())
				{
					// Note:
					// only log normal distribution has real truncated distribution
					/*if(m_truncation && m_name == "lognormal")
					{
						return m_truncation->GetPDF(z);
					}

					if(z < m_parameters.m_tMin || z > m_parameters.m_tMax)
					{
						value = ANY_NAN;
					}
					else
					{
						value = value / (cdf(*m_distribution, m_parameters.m_tMax) - cdf(*m_distribution, m_parameters.m_tMin));
					}*/

					// for beta and non-central beta
					if(m_parameters.m_isNormalized)
					{
						if(z >= m_parameters.m_tMax)
						{
							z = 1.;
						}
						else if(z <= m_parameters.m_tMin)
						{
							z = 0.;
						}
						else
						{
							z = (z - m_parameters.m_tMin) / (m_parameters.m_tMax - m_parameters.m_tMin);
						}
					}

					// default pdf value
					value = pdf(*m_distribution, z);
					double b=GetB();
					value = value / b;
				}
				else
				{
					// for beta and non-central beta
					if(m_parameters.m_isNormalized)
					{
						if(z >= m_parameters.m_max)
						{
							z = 1.;
						}
						else if(z <= m_parameters.m_min)
						{
							z = 0.;
						}
						else
						{
							z = (z - m_parameters.m_min) / (m_parameters.m_max - m_parameters.m_min);
						}
					}

					// default pdf value
					value = pdf(*m_distribution, z);
				}

				return value;
			}
			catch(...)
			{
				return 0.;
			}
		}

		/*!
		*
		**/
		double GetCDF(double z, bool isComplement = false, bool isForTruncation = false)
		{
			try
			{
				//
				if(m_parameters.m_isNormalized)
				{
					if(z >= m_parameters.m_max)
					{
						z = 1.;
					}
					else if(z <= m_parameters.m_min)
					{
						z = 0.;
					}
					else
					{
						z = (z - m_parameters.m_min) / (m_parameters.m_max - m_parameters.m_min);
					}
				}

				if(isForTruncation&&m_parameters.IsTruncated())
				{
					/*if(m_truncation && m_name == "lognormal")
					{
						return m_truncation->GetCDF(z, isComplement);
					}

					if(z < m_parameters.m_tMin || z > m_parameters.m_tMax)
					{
						return ANY_NAN;
					}

					double value = (cdf(*m_distribution, z) - cdf(*m_distribution, m_parameters.m_tMin)) / (cdf(*m_distribution, m_parameters.m_tMax) - cdf(*m_distribution, m_parameters.m_tMin));
					return isComplement ? 1 - value : value;*/

					//without user distribution
					if(m_parameters.m_isNormalized)
					{
						if(z < 0.0|| z > 1.)
						{
							return ANY_NAN;
						}
					}
					else
					{
						if(z < m_parameters.m_tMin || z > m_parameters.m_tMax)
						{
							return ANY_NAN;
						}
					}
					double b= GetB();
					double value = (cdf(*m_distribution, z) - cdf(*m_distribution, m_parameters.m_tMin)) / b;
					return isComplement ? 1 - value : value;
				}

				return isComplement ? cdf(complement(*m_distribution, z)) : cdf(*m_distribution, z);
			}
			catch(...)
			{
				return 0.;
			}
		}

		/*!
		*
		**/
		double GetQuantile(double probability, bool isForTruncation = false)
		{
			try
			{
				// Note:
				// given isonesdie for calling from user distribution when making interpolations
				if(isForTruncation && m_parameters.IsTruncated())
				{
					/*if(m_truncation)
					{
					return m_truncation->GetQuantile(probability, isForTruncation);
					}
					else
					{
					return ANY_NAN;
					}*/
					//without user distribution
					double b= GetB();
					double value=0.0;
					if(m_parameters.m_isNormalized)
					{
						//double tmp= (1-probability)*b+cdf(*m_distribution,0.0);
						//double value = quantile(*m_distribution, (1-probability)*b+cdf(*m_distribution,0.0));
						value = quantile(complement(*m_distribution, probability));
						value = m_parameters.m_tMin + (m_parameters.m_tMax - m_parameters.m_tMin) * value;
					}
					else
					{
						value = quantile(*m_distribution, (1-probability)*b+cdf(*m_distribution,  m_parameters.m_tMin));
					}
					return value;
				}

				double value = quantile(complement(*m_distribution, probability));
				if(m_parameters.m_isNormalized)
				{
					value = m_parameters.m_min + (m_parameters.m_max - m_parameters.m_min) * value;
				}
				return value;
			}
			catch(...)
			{
				return 0.;
			}
		}

		double GetB()
		{
			double b=0.0;
			if(m_parameters.m_isNormalized)
			{
				b=cdf(*m_distribution, (m_parameters.m_tMax - m_parameters.m_min) / (m_parameters.m_max - m_parameters.m_min)) - cdf(*m_distribution, (m_parameters.m_tMin - m_parameters.m_min) / (m_parameters.m_max - m_parameters.m_min));
			}
			else
			{
				b=cdf(*m_distribution, m_parameters.m_tMax) - cdf(*m_distribution, m_parameters.m_tMin);
			}
			return b;
		}
	private:
		//
		//
		//
		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::normal_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				//
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? -2. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 2. : m_parameters.m_max;
				m_parameters.m_mean = (ISNAN(m_parameters.m_mean)) ? 0. : m_parameters.m_mean;
				m_parameters.m_sd = (ISNAN(m_parameters.m_sd)) ? 1. : m_parameters.m_sd;
			}
			else
			{
				//
				m_parameters.m_mean =  (ISNAN(m_parameters.m_mean)) ? DoGetMean() : m_parameters.m_mean;
				m_parameters.m_sd = (ISNAN(m_parameters.m_sd)) ? DoGetSD() : m_parameters.m_sd;
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;
			}
			m_paraType |= SET_MEAN;
			m_paraType |= SET_SD;

			try
			{
				m_distribution = new normal(m_parameters.m_mean, m_parameters.m_sd);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}
			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::beta_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				//
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? 0. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 1. : m_parameters.m_max;

				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 1. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				// given the latest min and max definition to normalize
				assert(m_parameters.m_isNormalized);
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				//
				// maximum liklihood estimation
				if(ISNAN(m_parameters.m_alpha) || ISNAN(m_parameters.m_lambda)||m_parameters.IsTruncated())
				{
					double parameters[2];
					m_mle.Zangwill(parameters);
					m_parameters.m_lambda = parameters[1];
					m_parameters.m_alpha = parameters[0];
				}

				//double mean = DoGetMean();
				//double variance = DoGetSD();
				//variance *= variance;
				//m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? beta_distribution<>::find_alpha(mean, variance) : m_parameters.m_alpha;
				//m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? beta_distribution<>::find_beta(mean, variance) : m_parameters.m_lambda;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new beta_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::exponential_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? 0 : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 10. : m_parameters.m_max;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1./DoGetMean() : m_parameters.m_lambda;
			}
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::exponential_distribution<>(m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::extreme_value_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? -5. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 5. : m_parameters.m_max;

				// location
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 0. : m_parameters.m_alpha;
				// scale
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				// maximum liklihood estimation
				if(ISNAN(m_parameters.m_alpha) || ISNAN(m_parameters.m_lambda)||m_parameters.IsTruncated())
				{
					double parameters[2];
					m_mle.Zangwill(parameters);
					m_parameters.m_alpha = parameters[0];
					m_parameters.m_lambda = parameters[1];
				}

				// scale
				//double sd = DoGetSD();
				//double mean = DoGetMean();
				//m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? (sd * ::sqrt(6.) / m_pi) : m_parameters.m_lambda;
				//m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? (mean - m_euler * m_parameters.m_lambda) : m_parameters.m_alpha;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::extreme_value_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::gamma_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? 0. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 10. : m_parameters.m_max;

				// location
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 2. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				m_parameters.m_min =  (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max =  (ISNAN(m_parameters.m_max)) ?DoGetMax() : m_parameters.m_max;

				// maximum liklihood estimation
				if(ISNAN(m_parameters.m_alpha) || ISNAN(m_parameters.m_lambda) ||m_parameters.IsTruncated())
				{
					double parameters[2];
					m_mle.Zangwill(parameters);
					m_parameters.m_lambda = 1. / parameters[1];
					m_parameters.m_alpha = parameters[0];
				}

				//
				//double mean = DoGetMean();
				//double sd = DoGetSD();
				//double variance = sd * sd;
				//m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ?  ((variance) ? mean * mean /variance : 1.) : m_parameters.m_lambda;
				//m_parameters.m_alpha =  (ISNAN(m_parameters.m_alpha)) ? ((mean) ? variance / mean : 1.) : m_parameters.m_alpha;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::gamma_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::inverse_gamma_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				//
				m_parameters.m_min = (m_parameters.m_min== ANY_NAN) ? 0 : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ?10. : m_parameters.m_max;

				// location
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 2. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				// maximum liklihood estimation
				if(ISNAN(m_parameters.m_alpha) || ISNAN(m_parameters.m_lambda)||m_parameters.IsTruncated())
				{
					double parameters[2];
					m_mle.Zangwill(parameters);
					m_parameters.m_lambda = parameters[1];
					m_parameters.m_alpha = parameters[0];
				}

				//
				//double mean = DoGetMean();
				//double variance = DoGetSD()  * DoGetSD();
				//m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? (mean * mean/variance + 2.) : m_parameters.m_alpha;
				//m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? (mean * mean/variance + 1.) * mean : m_parameters.m_lambda;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::inverse_gamma_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::laplace_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? -5. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 5. : m_parameters.m_max;

				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 0. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				double mean = DoGetMean();
				double variance = DoGetSD() * DoGetSD();

				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? mean : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? (::sqrt(variance/2.)) : m_parameters.m_lambda;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::laplace_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::logistic_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? -5. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 5. : m_parameters.m_max;

				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 0. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min; 
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				// maximum liklihood estimation
				if(ISNAN(m_parameters.m_alpha) || ISNAN(m_parameters.m_lambda)||m_parameters.IsTruncated())
				{
					double parameters[2];
					m_mle.Zangwill(parameters);
					m_parameters.m_lambda = parameters[0];
					m_parameters.m_alpha = parameters[1];
				}

				//
				//double mean = DoGetMean();
				//double sd = DoGetSD();
				//double variance = sd * sd;
				//m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? mean : m_parameters.m_alpha;
				//m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? (::sqrt(variance * 3)/m_pi) : m_parameters.m_lambda;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::logistic_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::lognormal_distribution<> >)
		{
			//
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? 0. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 10. : m_parameters.m_max;
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 0. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				// range
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				// scale
				double mean = 0.;
				double sd = 0.;
				int i = 0;
				for(; i < m_number; i++)
				{
					mean += ::log(m_samples[i].m_y);
				}
				mean /= m_number;

				i = 0;
				for(; i < m_number; i++)
				{
					sd += (::log(m_samples[i].m_y) - mean) * (::log(m_samples[i].m_y) - mean);
				}
				sd = ::sqrt(sd/m_number);
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? mean : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? sd : m_parameters.m_lambda;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				//lognormal's scale parameter cannot be zero
				if(m_parameters.m_lambda==0.0)
				{
					m_parameters.m_lambda=0.00001;
				}
				m_distribution = new boost::math::lognormal_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			//
			if(m_parameters.IsTruncated())
			{
				m_truncation = new CShiftTruncatedLognormalDistribution(this);
				m_truncation->InitSamples("shift-truncated lognormal", m_samples, m_number, m_parameters);
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::non_central_beta_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				//
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? 0.1 : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 1. : m_parameters.m_max;
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 10. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 40. : m_parameters.m_lambda;
			}
			else
			{
				double mean = DoGetMean();
				double variance = DoGetSD();
				variance *= variance;

				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ?  mean * (( (mean * (1 - mean)) / variance)- 1) : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? (1 - mean) * (((mean * (1 - mean)) /variance)-1) : m_parameters.m_lambda;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new non_central_beta_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda, 1.);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::pareto_distribution<> >)
		{
			//
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? 0.1 : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 10. : m_parameters.m_max;

				// location
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 1. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				//
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				double sd = DoGetSD();
				double mean = DoGetMean();
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. + ::sqrt(1. + (mean * mean) / (sd * sd)) : m_parameters.m_lambda;
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? (1. - 1. / (1. + ::sqrt(1. + (mean * mean) / (sd * sd)))) * mean : m_parameters.m_alpha;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::pareto_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::rayleigh_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? 0.1 : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 30. : m_parameters.m_max;
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 1. : m_parameters.m_alpha;
			}
			else
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				double mean = DoGetMean();
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? (mean / (::sqrt(m_pi/2.))) : m_parameters.m_alpha;
			}
			m_paraType |= SET_ALPHA;

			try
			{
				m_distribution = new boost::math::rayleigh_distribution<>(m_parameters.m_alpha);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::triangular_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? -1. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 1. : m_parameters.m_max;
				m_parameters.m_mode = (ISNAN(m_parameters.m_mode)) ? 0. : m_parameters.m_mode;
				if(m_parameters.m_mode<m_parameters.m_min)
				{
					m_parameters.m_mode=m_parameters.m_min;
				}
				if(m_parameters.m_mode>m_parameters.m_max)
				{
					m_parameters.m_mode=m_parameters.m_max;
				}
			}
			else
			{
				// rough calculation
				m_parameters.m_mode = ISNAN(m_parameters.m_mode) ? DoGetMode() : m_parameters.m_mode;

				double mean = DoGetMean();
				double variance = DoGetSD() * DoGetSD();
				double a = 3. * mean - m_parameters.m_mode;
				double b = 6. * mean * m_parameters.m_mode + 24. * variance - 3. * m_parameters.m_mode * m_parameters.m_mode - 3. * mean * mean;
				m_parameters.m_min =  (ISNAN(m_parameters.m_min)) ? (a - b) / 2. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? (a+b) / 2. : m_parameters.m_max;
			}
			m_paraType |= SET_MODE;

			try
			{
				m_distribution = new boost::math::triangular_distribution<>(m_parameters.m_min, m_parameters.m_mode, m_parameters.m_max);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::uniform_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? -1. : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 1. : m_parameters.m_max;
				m_parameters.m_mode = (ISNAN(m_parameters.m_mode)) ? 0. : m_parameters.m_mode;
			}
			else
			{
				double mean = DoGetMean();
				double sd = DoGetSD();
				m_parameters.m_min =  (ISNAN(m_parameters.m_min)) ? mean - ::sqrt(12.* sd * sd)/2. : m_parameters.m_min;
				m_parameters.m_max =  (ISNAN(m_parameters.m_max)) ? mean + ::sqrt(12. * sd * sd)/2. : m_parameters.m_max;
				m_parameters.m_mode =  (ISNAN(m_parameters.m_mode)) ? m_parameters.m_min + (m_parameters.m_max - m_parameters.m_min)/2. : m_parameters.m_mode;
			}

			try
			{
				m_distribution = new boost::math::uniform_distribution<>(m_parameters.m_min, m_parameters.m_max);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

		/*!
		*
		**/
		bool DoCreate(Type2Type<boost::math::weibull_distribution<> >)
		{
			if(!m_samples || !m_number)
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? .1 : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? 3. : m_parameters.m_max;
				m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? 1. : m_parameters.m_alpha;
				m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 1. : m_parameters.m_lambda;
			}
			else
			{
				m_parameters.m_min = (ISNAN(m_parameters.m_min)) ? DoGetMin() : m_parameters.m_min;
				m_parameters.m_max = (ISNAN(m_parameters.m_max)) ? DoGetMax() : m_parameters.m_max;

				// maximum liklihood estimation
				if(ISNAN(m_parameters.m_alpha) || ISNAN(m_parameters.m_lambda)||m_parameters.IsTruncated())
				{
					double parameters[2];
					m_mle.Zangwill(parameters);
					m_parameters.m_lambda = parameters[1];
					m_parameters.m_alpha = parameters[0];
				}

				//m_parameters.m_alpha = (ISNAN(m_parameters.m_alpha)) ? .75 : m_parameters.m_alpha;
				//m_parameters.m_lambda = (ISNAN(m_parameters.m_lambda)) ? 25. : m_parameters.m_lambda;
			}
			m_paraType |= SET_ALPHA;
			m_paraType |= SET_LAMBDA;

			try
			{
				m_distribution = new boost::math::weibull_distribution<>(m_parameters.m_alpha, m_parameters.m_lambda);
			}
			catch(...)
			{
				m_distribution = 0;
				return false;
			}

			return true;
		}

	private:
		// which distribution
		T *m_distribution;
		CBoostDistribution *m_truncatedDistribution;
		//
		double m_pi;
		double m_euler;
	};

	// kinds of strategies
	typedef CBoostDistribution<boost::math::normal_distribution<>, CAnyDistributionStrategy> BoostNormal;
	typedef CBoostDistribution<boost::math::beta_distribution<>, CAnyDistributionStrategy> BoostBeta;
	typedef CBoostDistribution<boost::math::exponential_distribution<>, CAnyDistributionStrategy> BoostExponential;
	typedef CBoostDistribution<boost::math::extreme_value_distribution<>, CAnyDistributionStrategy> BoostExtremeValue;
	typedef CBoostDistribution<boost::math::gamma_distribution<>, CAnyDistributionStrategy> BoostGamma;
	typedef CBoostDistribution<boost::math::inverse_gamma_distribution<>, CAnyDistributionStrategy> BoostInverseGamma;
	typedef CBoostDistribution<boost::math::laplace_distribution<>, CAnyDistributionStrategy> BoostLaplace;
	typedef CBoostDistribution<boost::math::logistic_distribution<>, CAnyDistributionStrategy> BoostLogistic;
	typedef CBoostDistribution<boost::math::lognormal_distribution<>, CAnyDistributionStrategy> BoostLognormal;
	typedef CBoostDistribution<boost::math::non_central_beta_distribution<>, CAnyDistributionStrategy> BoostNonCentralBeta;
	typedef CBoostDistribution<boost::math::pareto_distribution<>, CAnyDistributionStrategy> BoostPareto;
	typedef CBoostDistribution<boost::math::rayleigh_distribution<>, CAnyDistributionStrategy> BoostRayleigh;
	typedef CBoostDistribution<boost::math::triangular_distribution<>, CAnyDistributionStrategy> BoostTriangular;
	typedef CBoostDistribution<boost::math::uniform_distribution<>, CAnyDistributionStrategy> BoostUniform;
	typedef CBoostDistribution<boost::math::weibull_distribution<>, CAnyDistributionStrategy> BoostWeibull;
}
//
#pragma warning( pop )

#endif