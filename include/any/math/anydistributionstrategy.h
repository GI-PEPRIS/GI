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
#ifndef __ANYMATH_DISTRIBUTION_STRATEGY_H__
#define __ANYMATH_DISTRIBUTION_STRATEGY_H__

// refer to macro
#include "anymath.h"

// to calculate distribution parameter
#include "anymaximumparameterstrategy.h"

// refer to stl
#include "any/base/anyport.h"
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;

// refer to accessor
#include "any/db/anyaccessor.h"
using namespace AnyDB;
// refer to functor
#include "any/base/anymediator.h"
using namespace AnyBase;
// namespace
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyDistributionStrategy
	{
		// relatives
		friend class CAnySensitivityAnalysis;

	public:
		/*!
		*
		**/
		enum
		{
			DUPLICATE_ADD=0,
		};
		enum 
		{
			// along X direction
			SET_RANGE_MIN = 1,
			SET_RANGE_MAX = 1 << 1,

			// truncation
			SET_TRUNCTION_MIN = 1 << 2,
			SET_TRUNCTION_MAX = 1 << 3,

			// statistic setting
			SET_MEAN = 1 << 4,
			SET_SD = 1 << 5,
			SET_MODE = 1 << 6,

			// position and scale
			SET_ALPHA = 1 << 7,
			SET_LAMBDA = 1 << 8,
		};

		/*!
		*
		**/
		enum ExceedanceMode
		{
			EM_Unknown = -1,
			EM_Histogram,
			EM_Fractiles,
			EM_Midpoints,
			EM_Max,
		};

		/*!
		*
		**/
		struct ProbabilityRecord
		{
			long m_idx;
			string m_name;
			unsigned int m_paraType;
			string m_remark;

			/*!
			*
			**/
			ProbabilityRecord() : m_idx(0), m_name(""), m_paraType(0), m_remark("")
			{
			}

			/*!
			*
			**/
			const ProbabilityRecord &operator=(const ProbabilityRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx = other.m_idx;
				m_name = other.m_name;
				m_paraType = other.m_paraType;
				m_remark = other.m_remark;

				return *this;
			}
		};
		typedef std::vector<ProbabilityRecord> ProbabilityVector;
		typedef ProbabilityVector::iterator prob_itr;
		typedef ProbabilityVector::const_iterator prob_citr;

		/*!
		*
		**/
		struct DistributionStatistics
		{
			//
			double m_mean;
			double m_median;
			double m_mode;
			double m_sd;
			double m_variance;
			double m_skewness;

			/*!
			*
			**/
			DistributionStatistics() 
				: m_mean(ANY_NAN), m_median(ANY_NAN), m_mode(ANY_NAN), m_sd(ANY_NAN), m_variance(ANY_NAN), m_skewness(ANY_NAN)
			{
			}

			/*!
			*
			**/
			const DistributionStatistics &operator=(const DistributionStatistics &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_mean = other.m_mean;
				m_median = other.m_median;
				m_mode = other.m_mode;
				m_sd = other.m_sd;
				m_variance = other.m_variance;
				m_skewness = other.m_skewness;

				return *this;
			}
		};

		/*!
		*
		**/
		struct DistributionParameters
		{
			// statistic parameters
			// ...
			// normal distribution
			double m_mean;
			double m_sd;

			// parameters for corresponding x position
			// ...
			// uniform(lower, upper)
			// triangular(lower, mode, upper)
			// ...
			double m_min;
			double m_max;
			double m_mode;
			
			// parameters of shape and scale
			// weibull(shape = alpha > 0, scale = beta > 0)
			// gamma(shape = alpha > 0, scale = beta > 0)
			// rayleigh(sigma = alpha > 0)
			// pareto(scale = alpha > 0, beta = shape > 0)
			// non central beta(alpha, beta, lambda)
			// log normal(location = alpha, scale = beta)
			// logistic(location = alpha, scale = beta)
			// laplace(location = alpha, scale = beta)
			// extreme value(location = alpha, scale = beta)
			// beta(a = alpha, b = beta)
			double m_alpha;
			// exponential (lambda)
			double m_lambda;

			// trunction parameters
			double m_tMin;
			double m_tMax;

			// fractile number for generation of exceedance probability
			int m_fractiles;
			// whether in log axis
			bool m_isLogAxis;
			bool m_isNormalized;

			/*!
			*
			**/
			DistributionParameters() 
				: m_min(ANY_NAN), 
				m_max(ANY_NAN), 
				m_mode(ANY_NAN), 
				m_alpha(ANY_NAN), 
				m_lambda(ANY_NAN),
				m_mean(ANY_NAN),
				m_sd(ANY_NAN),
				m_tMin(ANY_NAN),
				m_tMax(ANY_NAN),
				m_fractiles(0),
				m_isLogAxis(false),
				m_isNormalized(false)
			{
			}

			/*!
			*
			**/
			DistributionParameters(const string &str)
			{
				assert(str.size());

				CAnyTokenString curToken;
				curToken.SetToken(":");
				int count = curToken.Trim((char *)str.c_str(), str.size());
				int order = 0;

				m_min = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_max = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_mode = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_alpha = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_lambda = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_mean = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_sd = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_tMin = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_tMax = order < count ? ::atof(curToken[order++]) : ANY_NAN;
				m_fractiles = order < count ? ::atoi(curToken[order++]) : ANY_NAN;
				m_isLogAxis = order < count ? ::atoi(curToken[order++]) : 0;
				m_isNormalized = order < count ? ::atoi(curToken[order++]) : 0;
			}

			/*!
			*
			**/
			const DistributionParameters &operator=(const DistributionParameters &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// ...
				m_min = other.m_min;
				m_max = other.m_max;
				m_mode = other.m_mode;
				m_alpha = other.m_alpha;
				m_lambda = other.m_lambda;
				m_mean = other.m_mean;
				m_sd = other.m_sd;
				m_tMin = other.m_tMin;
				m_tMax = other.m_tMax;
				m_fractiles = other.m_fractiles;
				m_isLogAxis = other.m_isLogAxis;
				m_isNormalized = other.m_isNormalized;

				//
				return *this;
			}

			/*!
			*
			**/
			void Reset()
			{
				m_min = ANY_NAN;
				m_max = ANY_NAN; 
				m_mode = ANY_NAN;
				m_alpha = ANY_NAN; 
				m_lambda = ANY_NAN;
				m_mean = ANY_NAN;
				m_sd = ANY_NAN;
				m_tMin = ANY_NAN;
				m_tMax = ANY_NAN;
				m_fractiles = 0;
				m_isLogAxis = false;
				m_isNormalized = false;
			}

			/*!
			*
			**/
			bool IsTruncated() const
			{
				if(ISNAN(m_tMax) ||
					ISNAN(m_tMin) || 
					m_tMax <= m_tMin ||
					(m_max <= m_tMax && m_min >= m_tMin))
				{
					return false;
				}

				return true;
			}

			/*!
			*
			**/
			void ToString(string &str) const
			{
				char value[512] = "";
				::sprintf(value, "%.5f:%.5f:%.5f:%.5f:%.5f:%.5f:%.5f:%.5f:%.5f:%.5f:%d:%d", \
					ISNAN(m_min) ? -1. : m_min,	
					ISNAN(m_max) ? -1. : m_max,	
					ISNAN(m_mode) ? -1. : m_mode, 
					ISNAN(m_alpha) ? -1. : m_alpha, 
					ISNAN(m_lambda) ? -1. : m_lambda, 
					ISNAN(m_mean) ? -1. : m_mean, 
					ISNAN(m_sd) ? -1. : m_sd, 
					ISNAN(m_tMin) ? -1. : m_tMin, 
					ISNAN(m_tMax) ? -1. : m_tMax, 
					ISNAN(m_fractiles) ? -1. : m_fractiles, 
					ISNAN(m_isLogAxis) ? -1 : m_isLogAxis, 
					ISNAN(m_isNormalized) ? -1 : m_isNormalized);

				str = value;
			}

			void FromString(const string &str) 
			{
				CAnyTokenString curToken(":","","");
				int curCount = curToken.Trim(str.c_str(), str.size());
				if(curCount != 12)
				{
					assert(false);
					return;
				}
				m_min = ::atof(curToken.GetAt(0));
				if(m_min ==-1) m_min = ANY_NAN;

				m_max = ::atof(curToken.GetAt(1));
				if(m_max ==-1) m_max = ANY_NAN;

				m_mode = ::atof(curToken.GetAt(2));
				if(m_mode ==-1) m_mode = ANY_NAN;

				m_alpha = ::atof(curToken.GetAt(3));
				if(m_alpha ==-1) m_alpha = ANY_NAN;

				m_lambda = ::atof(curToken.GetAt(4));
				if(m_lambda ==-1) m_lambda = ANY_NAN;

				m_mean = ::atof(curToken.GetAt(5));
				if(m_mean ==-1) m_mean = ANY_NAN;

				m_sd = ::atof(curToken.GetAt(6));
				if(m_sd ==-1) m_sd = ANY_NAN;

				m_tMin = ::atof(curToken.GetAt(7));
				if(m_tMin ==-1) m_tMin = ANY_NAN;

				m_tMax = ::atof(curToken.GetAt(8));
				if(m_tMax ==-1) m_tMax = ANY_NAN;

				m_fractiles = ::atof(curToken.GetAt(9));
				if(m_fractiles ==-1) m_fractiles = ANY_NAN;

				m_isLogAxis = ::atoi(curToken.GetAt(10));
				if(m_isLogAxis ==-1) m_isLogAxis = ANY_NAN;

				m_isNormalized = ::atoi(curToken.GetAt(11));
				if(m_isNormalized ==-1) m_isNormalized = ANY_NAN;		
			}

		};

		/*!
		*
		**/
		struct InterpolationIndice
		{
			int m_order;
			double m_value;

			/*!
			*
			**/
			InterpolationIndice() : m_order(0), m_value(0.)
			{
			}

			/*!
			*
			**/
			const InterpolationIndice &operator=(const InterpolationIndice &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_order = other.m_order;
				m_value = other.m_value;

				return *this;
			}
		};
		typedef std::vector<InterpolationIndice> InterIndices;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyDistributionStrategy();

		/*!
		*
		**/
		virtual ~CAnyDistributionStrategy();

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyDistributionStrategy *GetHistogramDistribution()
		{
			assert(m_histogram);
			return m_histogram;
		}

		/*!
		*
		**/
		CAnyDistributionStrategy *GetTruncatedDistribution()
		{
			assert(m_truncation);
			return m_truncation;
		}

		//
		//
		//
		/*!
		*
		**/
		unsigned int GetParaType()
		{
			return m_paraType;
		}

		/*!
		*
		**/
		const DistributionParameters &GetParameters()
		{
			return m_parameters;
		}

		/*!
		*
		**/
		const string &GetName() const
		{
			return m_name;
		}

		/*!
		*
		**/
		virtual void MakeInterpolations()
		{
			// Note:
			// this funcation is only for user definition
			// ...
		}

		/*!
		* interpolated points from above ctrl points
		**/
		void SetInterpolations(CGeoPoint<double> *interPts, int interNumber);

		//
		//
		//
		/*!
		*
		**/
		virtual bool InitSamples(const string &name, CGeoPoint<double> *samples, int number, const DistributionParameters &parameters);

		/*!
		*
		**/
		int GetSampleSize() const
		{
			return m_number;
		}

		/*!
		*
		**/
		CGeoPoint<double> *GetSamples() const
		{
			return m_samples;
		}
		
		/*!
		*
		**/
		virtual void GetRange(CGeoRect<double> &mapExtent) = 0;

		/*!
		*
		**/
		virtual const DistributionStatistics &GetStatistics() = 0;

		/*!
		*
		**/
		bool IsValid();

		//
		//
		//
		/*!
		*
		**/
		virtual double GetPDF(double &z, bool isForTruncation = false) = 0;

		/*!
		*
		**/
		virtual double GetCDF(double z, bool isComplement = false, bool isForTruncation = false) = 0;

		/*!
		*
		**/
		virtual double GetQuantile(double probability, bool isForTurncation = false) = 0;

		/*!
		*
		**/
		virtual double GetExceedance(double z, int mode);

		//
		// basic statistics
		//
		/*!
		*
		**/
		virtual double DoGetMean();

		/*!
		*
		**/
		virtual double DoGetSD();

		/*!
		*
		**/
		virtual double DoGetIQR();

		/*!
		*
		**/
		virtual double DoGetMin();

		/*!
		*
		**/
		virtual double DoGetMax();

		/*!
		*
		**/
		virtual double DoGetMode();

		/*!
		*
		**/
		virtual double DoGetMaxY(int divisions = 255);
		/*!
		*
		**/
		static bool RegisterFunctor(int type,CAnyFunctor *func);

		/*!
		*
		**/
		static bool RemoveFunctor(int type);

		//
		// persistence interface
		//
		/*!
		*
		**/
		static bool InitProbabilityRecords();

		/*!
		*
		**/
		static int GetDistributionCount();

		/*!
		*
		**/
		static const string &GetDistributionName(int order);

		/*!
		*
		**/
		static void UpdateProbabilityRecord(const ProbabilityRecord &record);

		/*!
		*
		**/
		static long GetDistributionRecordIdx(const string &name);

		/*!
		*
		**/
		static CAnyDistributionStrategy *GetDistribution(const string &name);

		/*!
		*
		**/
		static void ClearFunctor();

	private:
		//
		//
		//
		/*!
		*
		**/
		static bool DoAddProbabilityRecord(CAnyAccessor &accessor, const ProbabilityRecord &record);

		/*!
		*
		**/
		static void DoLoadRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		static void DoCommit();

		/*!
		*
		**/
		static bool CompareProbabilityIdx(const ProbabilityRecord &first, const ProbabilityRecord &second)
		{
			return first.m_idx < second.m_idx;
		}

		/*!
		*
		**/
		void DoGetExceedanceRange(double z, int &start, int &end);

	protected:
		//
		//
		//
		/*!
		*
		**/
		virtual int DoBSearch(double value, const InterIndices &indices);

		//
		//
		//
		/*!
		*
		**/
		static bool CompareInterIndice(const InterpolationIndice &first, const InterpolationIndice &second)
		{
			return first.m_value < second.m_value;
		}

	protected:
		// samples
		CGeoPoint<double> *m_samples;
		int m_number;

		// interpolated points for user defined or as indices
		CGeoPoint<double> *m_interPts;
		int m_interNumber;
		InterIndices m_xIndices;
		InterIndices m_yIndices;

		// distribution name 
		string m_name;

		// mean, mode, etc
		// ...
		// normal(mean, sd)
		DistributionStatistics m_stats;

		// setting status of parameters
		unsigned int m_paraType;

		// distribution parameters
		DistributionParameters m_parameters;

		// distribution before left-shift and right truncated
		CAnyDistributionStrategy *m_truncation;
		CAnyDistributionStrategy *m_histogram;
		CAnyDistributionStrategy *m_host;	// parent

		// generalizedly maximum liklihood estimation
		CAnyMaximumParameterStrategy m_mle;
		
		// persistence mechanism
		// ...
		static bool m_isDirty;
		static string m_probabilityTable;
		static ProbabilityVector m_probabilityRecords;
	public:
		// because Docommit() is static, so functormap should also be static.
		static std::map<int,CAnyFunctor*> m_functorMap;
		static int m_addCount;
	};
}

#endif