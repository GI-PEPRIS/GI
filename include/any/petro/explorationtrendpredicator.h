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
#ifndef __ANYPETRO_EXPLORATION_PREDICATOR_H__
#define __ANYPETRO_EXPLORATION_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to stl
#include "any/base/anystl.h"

// refer to geopoint
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;

// refer to FT_XXX
#include "any/math/anyfittingstrategy.h"
using namespace AnyMath;

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CExplorationTrendPredicator : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		enum ExplotrationTrendType
		{
			ETT_Unknown = -1,
			ETT_Year,
			ETT_Wells,
			ETT_Footage,
			ETT_Investment,
			ETT_Max
		};

		/*!
		* to use definition of anymath package
		**/
		//enum FittingType
		//{
		//	FT_Unknown = -1,
		//	FT_Linear,
		//	FT_Power,
		//	FT_Exponential,
		//	FT_Log,
		//	FT_InverseExponential,
		//	FT_S,
		//	FT_Z,
		//	FT_Quadratic,
		//	FT_Cubic,
		//	FT_Lifecycle,
		//	FT_Max,
		//};

		/*!
		*
		**/
		struct TrendSample
		{
			// which statistic type
			short m_trendType;
			// which fitting mode
			short m_fittingType;
			// weight for current statistic type
			double m_weight;
			// trend limited value
			double m_extremeTrend;
			// trend groups
			int m_extremeGroups;
			// for lifecycle mode
			// the mode value
			double m_lifeMode;
			int m_lifeNumber;

			// sample number
			int m_number;
			// samples
			CGeoPoint<double> *m_samples;

			// predicated value
			double m_Q;
			double m_avgQ;
			double m_maxQ;
			double m_minQ;
			double m_variance; // average in square
			double m_swasonQ;

			double m_a;
			double m_b;
			double m_c;
			double m_d;

			/*!
			*
			**/
			TrendSample() : m_trendType(ETT_Unknown), m_fittingType(CAnyFittingStrategy::FT_Unknown), m_weight(0.), m_extremeTrend(0.), m_extremeGroups(5), m_lifeMode(0.), m_lifeNumber(5), m_number(0), m_samples(0), m_Q(0.), 
				m_avgQ(0.),m_minQ(0.),m_maxQ(0.),m_variance(0.),m_swasonQ(0),m_a(0),m_b(0),m_c(0),m_d(0)
			{
			}

			TrendSample(const TrendSample &other)
			{
				m_samples=0;
				*this = other;
			}
			~TrendSample()
			{
				Release();
			}
			/*!
			*
			**/
			const TrendSample &operator=(const TrendSample &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_trendType = other.m_trendType;
				m_fittingType = other.m_fittingType;
				m_weight = other.m_weight;
				// trend limited value
				m_extremeTrend = other.m_extremeTrend;
				m_extremeGroups = other.m_extremeGroups;
				// for lifecycle mode
				// the mode value
				m_lifeMode = other.m_lifeMode;
				m_lifeNumber = other.m_lifeNumber;

				// predicated value
				m_Q = other.m_Q;
				m_avgQ = other.m_avgQ;
				m_minQ = other.m_minQ;
				m_maxQ= other.m_maxQ;
				m_swasonQ = other.m_swasonQ;

				m_a = other.m_a;
				m_b = other.m_b;
				m_c = other.m_c;
				m_d = other.m_d;


				m_variance = other.m_variance; // average in square

				if(m_samples)
				{
					::free(m_samples);
				}
				m_number = other.m_number;
				m_samples = (CGeoPoint<double> *)::malloc(m_number * sizeof(CGeoPoint<double>));
				::memcpy(m_samples, other.m_samples, m_number * sizeof(CGeoPoint<double>));

				return *this;
			}

			/*!
			*
			**/
			void Release()
			{
				if(m_samples)
				{
					::free(m_samples);
				}
				m_samples = 0;
				m_number = 0;
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				char parameter[512] = "";
				::sprintf(parameter, "%d|%d|%.3f|%.3f|%.3f|%d|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f|%.3f", m_trendType, m_fittingType, m_weight, m_extremeTrend, m_lifeMode, m_lifeNumber, m_avgQ,m_minQ,m_maxQ, m_variance,
					                  m_swasonQ,m_a,m_b,m_c,m_d);

				return parameter;
			}

			/*!
			*
			**/
			void FromParameterString(string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("|");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				//assert(curCount == 10);

				m_trendType = ::atoi(curToken.GetAt(0));
				m_fittingType = ::atoi(curToken.GetAt(1));
				m_weight = ::atof(curToken.GetAt(2));
				m_extremeTrend = ::atof(curToken.GetAt(3));
				m_lifeMode = ::atof(curToken.GetAt(4));
				m_lifeNumber = ::atoi(curToken.GetAt(5));
				m_avgQ = ::atof(curToken.GetAt(6));
				m_minQ = ::atof(curToken.GetAt(7));
				m_maxQ = ::atof(curToken.GetAt(8));
				m_variance = ::atof(curToken.GetAt(9));
				m_swasonQ = ::atof(curToken.GetAt(10));
				m_a = ::atof(curToken.GetAt(11));
				m_b = ::atof(curToken.GetAt(12));
				m_c = ::atof(curToken.GetAt(13));
				m_d = ::atof(curToken.GetAt(14));
				m_samples=0;
				m_number=0;
			}
		};
		typedef std::map<short, TrendSample> TrendMap;
		typedef TrendMap::const_iterator trend_citr;
		typedef TrendMap::iterator trend_itr;

		/*!
		*
		**/
		struct ResourcePredication
		{
			// resource type
			int m_resourceType;

			// middle coefficients
			double m_a;
			double m_b;
			double m_c;
			double m_d;
			double m_e; // for lifecycle
			double m_f; // for lifecycle

			// sum distribution
			// min Q
			double m_minQ;
			// avg Q
			double m_avgQ;
			// max Q
			double m_maxQ;

			double m_swasonQ;

			// samples
			TrendMap m_trends;

			//resource type
			int m_resourcecategory;
			//resource class
			int m_resourceclass;

			int m_curtrend;
			short m_curfittingType;
			/*!
			*
			**/
			ResourcePredication() : m_curfittingType(0),m_resourceType(0), m_resourcecategory(0),m_resourceclass(0),m_a(0.), m_b(0.), m_c(0.), m_d(0.), m_e(0.), m_f(0.), m_minQ(0.), m_avgQ(0.), m_maxQ(0.),m_curtrend(0),m_swasonQ(0.0)
			{
			}

			ResourcePredication(const ResourcePredication &other)
			{
				m_trends.clear();
				*this = other;
			}

			~ResourcePredication()
			{
				Release();
			}
			
			void Reset()
			{
				m_trends.clear();
				m_resourceType=0; 
				m_resourcecategory=0;
				m_resourceclass=0;
				m_a=0; 
				m_b=0;
				m_c=0;
				m_d=0;
				m_e=0; 
				m_f=0;
				m_minQ=0;
				m_avgQ=0;
				m_maxQ=0;
				m_curtrend=0;
				m_swasonQ=0;
				m_curfittingType=0;

			}
			/*!
			*
			**/
			const ResourcePredication &operator=(const ResourcePredication &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// samples related
				Release();
				/*TrendSample sample;
				sample.m_trendType = ETT_Year;
				m_trends.insert(TrendMap::value_type(ETT_Year, sample));
				sample.m_trendType = ETT_Wells;
				m_trends.insert(TrendMap::value_type(ETT_Wells, sample));
				sample.m_trendType = ETT_Footage;
				m_trends.insert(TrendMap::value_type(ETT_Footage, sample));*/

				// resource type
				m_resourceType = other.m_resourceType;
				
				// calculation parameter
				m_a = other.m_a;
				m_b = other.m_b;
				m_c = other.m_c;
				m_d = other.m_d;
				m_e = other.m_e;
				m_f  = other.m_f;

				// samples
				int count=0;
				trend_citr itr = other.m_trends.begin();
				for(; itr != other.m_trends.end(); itr++)
				{
					/*if(itr->second.m_trendType==ETT_Year)
					{
						TrendSample sample;
						sample.m_trendType = ETT_Year;
						m_trends.insert(TrendMap::value_type(ETT_Year, sample));
						m_trends[count] = itr->second;
						count++;
						continue;
					}
					if(itr->second.m_trendType==ETT_Wells)
					{
						TrendSample sample;
						sample.m_trendType = ETT_Wells;
						m_trends.insert(TrendMap::value_type(ETT_Wells, sample));
						m_trends[count] = itr->second;
						count++;
						continue;
					}
					if(itr->second.m_trendType==ETT_Footage)
					{
						TrendSample sample;
						sample.m_trendType = ETT_Footage;
						m_trends.insert(TrendMap::value_type(ETT_Footage, sample));
						m_trends[count] = itr->second;
						count++;
						continue;
					}*/
					m_trends.insert(TrendMap::value_type(itr->second.m_trendType, itr->second));

				}

				// total result
				m_minQ = other.m_minQ;
				m_avgQ = other.m_avgQ;
				m_maxQ = other.m_maxQ;
				m_swasonQ = other.m_swasonQ;

				m_resourcecategory = other.m_resourcecategory;
				m_resourceclass= other.m_resourceclass;
				m_curtrend = other.m_curtrend;
				m_curfittingType = other.m_curfittingType;
				return *this;
			}

			/*!
			*
			**/
			bool IsValid() const
			{
				return m_minQ < m_avgQ && m_avgQ < m_maxQ;
			}

			/*!
			*
			**/
			void Release()
			{
	/*			trend_itr itr = m_trends.begin();
				for(; itr != m_trends.end(); itr++)
				{
					itr->second.Release();
				}*/
				m_trends.clear();
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				char parameter[512] = "";
				::sprintf(parameter, "%d#%.3f#%.3f#%.3f#%.3f#%.3f#%.3f#%.3f#%.3f#%.3f#%d#%d#%d#%.3f#%d", m_resourceType, \
					m_a, m_b, m_c, m_d, m_e, m_f, m_minQ, m_avgQ, m_maxQ,m_resourcecategory,m_resourceclass,m_curtrend,m_swasonQ,m_curfittingType);

				string str = parameter;
				trend_itr itr = m_trends.begin();
				for(; itr != m_trends.end(); itr++)
				{
					str += "#";
					str += itr->second.ToParameterString();
				}

				assert(str.size() < 255);
				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");
				int count = curToken.Trim(parameter.c_str(), parameter.size());

				m_resourceType = ::atoi(curToken.GetAt(0));
				m_a = ::atof(curToken.GetAt(1));
				m_b = ::atof(curToken.GetAt(2));
				m_c = ::atof(curToken.GetAt(3));
				m_d = ::atof(curToken.GetAt(4));
				m_e = ::atof(curToken.GetAt(5));
				m_f = ::atof(curToken.GetAt(6));
				m_minQ = ::atof(curToken.GetAt(7));
				m_avgQ = ::atof(curToken.GetAt(8));
				m_maxQ = ::atof(curToken.GetAt(9));
				m_resourcecategory = ::atof(curToken.GetAt(10));
				m_resourceclass = ::atof(curToken.GetAt(11));
				m_curtrend = ::atof(curToken.GetAt(12));
				m_swasonQ = ::atof(curToken.GetAt(13));
				m_curfittingType = ::atoi(curToken.GetAt(14));
				int i = 15;
				for(; i < count; i++)
				{
					string str = curToken.GetAt(i);
					TrendSample sample;
					sample.FromParameterString(str);
					m_trends.insert(TrendMap::value_type(sample.m_trendType, sample));
					if(m_trends[i-15].m_samples)
					{
						::free(m_trends[i-15].m_samples);
						m_trends[i-15].m_samples=0;
					}
				}
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CExplorationTrendPredicator(CAccumulationElement *curElement);

		/*!
		*
		**/
		virtual ~CExplorationTrendPredicator();

	public:
		//
		//
		//
		/*!
		*
		**/
		int GetValidTrendsSize();

		/*!
		*
		**/
		bool AddTrendSample(const TrendSample &sample);

		/*!
		*
		**/
		bool IsExistTrend(short type);

		/*!
		*
		**/
		TrendSample &GetTrendSample(short type);

		/*!
		*
		**/
		const TrendSample &GetTrendSample(short type) const;

		//
		//
		//
		/*!
		*
		**/
		bool MakePredication(short trendType, bool isForFitting = false, bool isDirect = false);

		/*!
		*
		**/
		void MakeTriangulateDistribution();

		/*!
		*
		**/
		ResourcePredication &GetPredication() 
		{
			return m_predication;
		}

		/*!
		*
		**/
		void Release()
		{
			m_predication.Release();
		}

		/*!
		* deprecated: from 0 - m_extremegroups
		**/
		bool GetRangeDesc(int trendType, int whichgroup, double &left, double &right, double &efficiency, double &min, double &avg, double &max);

		//
		//
		//
		/*!
		*
		**/
		void SetFittingType(short trendType, short fittingType)
		{
			assert(trendType > ETT_Unknown && trendType < ETT_Max);
			assert(fittingType > CAnyFittingStrategy::FT_Unknown && fittingType < CAnyFittingStrategy::FT_Max);
			if(m_predication.m_trends.find(trendType) != m_predication.m_trends.end())
			{
				m_predication.m_trends[trendType].m_fittingType = fittingType;
			}
		}

		/*!
		*
		**/
		void GetFittingSequence(double **x, double **y, short type, const CGeoPoint<double> *const samples, int number);

		//
		//
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);

		//
		// for fitting models
		//
		/*!
		*
		**/
		static int GetFittingCount();

		/*!
		获取公式名称
		**/
		static const string &GetFittingName(int order);

		/*!
		isonlyforavgQ 为true 表示只带入公式计算当前预测值 不与minQ累加
		**/
		double DoCalcTrend(short trendType, ResourcePredication &predication, double trendValue, const CGeoPoint<double> *const samples, int number,bool isonlyforavgQ=false);

		/*!
		获取趋势类型名称
		**/
		static void GetTrendName(int trendtype,string &trendname)
		{
			if(trendtype<0 ||trendtype>2)
			{
				trendname="";
			}
			else if(trendtype==0)
			{
				trendname="date";
			}
			else if(trendtype==1)
			{
				trendname="wells";
			}
			else if(trendtype==2)
			{
				trendname="footage";
			}
		}
	private:
		//
		//
		//

		/*!
		*
		**/
		void DoCalcFittingParameter(short trendType, ResourcePredication &predication, double a, double b);

	
		/*!
		*
		**/
		double DoCalcVariance(short trendType, ResourcePredication &predication, const CGeoPoint<double> *const samples, int number);

		/*!
		*
		**/
		void DoMakePolynomialPredication(short trendType, ResourcePredication &predication, double *x, double *y, int number);

		/*!
		* deprecated function
		**/
		void DoMakeLifecyclePredication(short trendType, ResourcePredication &predication, double *x, double *y, int number);

		/*!
		* 
		**/
		void DoMakeWengLifecyclePredication(short trendType, ResourcePredication &predication, double *x, double *y, int number);

		/*!
		*
		**/
		double DoGetLifecylePredication(ResourcePredication &predication, double trendValue);

	private:
		// parameters
		ResourcePredication m_predication;

		// delegate to mathematic functions
		// TODO:
		// here stil not replace key functions with those in CAnyFittingStrategy
		// ...
		CAnyFittingStrategy m_fitting;

		// fitting models
		static std::vector<std::string> m_fittingNames;
	public:
		string m_remark;

		char *m_groupbitmap;
		int m_groupbitmaplength;
		char *m_distributionbitmap;
		int m_distributionbitmaplength;

		std::vector<std::vector<string>> m_datagroup;
		std::vector<std::vector<string>> m_resgroup;

		std::vector<std::vector<string>> m_scattergroup;
		std::vector<std::vector<string>> m_totalgroup;
	};
}

#endif