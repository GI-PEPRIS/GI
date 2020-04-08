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
#ifndef __ANYPETRO_DISTRIBUTION_RESOURCE_PREDICATOR_H__
#define __ANYPETRO_DISTRIBUTION_RESOURCE_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to stl
#include "any/base/anystl.h"

// refer to cgeopoint
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// refer to distribution 
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CDistributionResourcePredicator : public CAccumulationAssessor
	{
		// relatives
		friend class CDiscoveryProcessPredicator;

	public:
		/*!
		* the way to infer pool number
		**/
		enum InferenceN
		{
			NT_Unknown = -1,
			NT_Linear,					// sequence in order
			NT_NonParameter,		// GSC non-parameter
			NT_Discovery,			// pool-size-by-rank
			NT_Max,
		};

		/*!
		* the way to infer max pool
		**/
		enum InferenceP
		{
			PT_Unknown = -1,
			PT_Sample,				// directly from max sample
			PT_Linear,					// seqence in order
			PT_Distribution,			// current size-distribution
			PT_Discovery,			// pool-size-by-rank
			PT_Max,
		};

		/*!
		*
		**/
		enum IterationType
		{
			IT_Unknown = -1,
			IT_Trapezodial,
			IT_Simpson,
			IT_Max,
		};
//////////////////////////////////////////////////////////
		struct AdvancedSamples
		{
			long   m_founddate;
			int    m_foundN;
			int	   m_allfoundN;
			double m_foundP;
			double m_reserve;
			double m_alpha;
			double m_lamda;
			int    m_N;

			AdvancedSamples() 
			{
				m_founddate =-1;
				m_foundN	=-1;
				m_reserve	=-1;
				m_alpha		=-1;
				m_lamda		=-1;
				m_allfoundN =-1;
				m_foundP    =-1;
				m_N			=-1;
			}

			const AdvancedSamples &operator=(const AdvancedSamples &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_founddate = other.m_founddate ;
				m_foundN	= other.m_foundN	  ;
				m_reserve	= other.m_reserve	  ;
				m_alpha		= other.m_alpha	  ;
				m_lamda		= other.m_lamda	  ;
				m_allfoundN = other.m_allfoundN ;
				m_foundP    = other.m_foundP    ;
				m_N			= other.m_N;
				return *this;
			}
		};
/////////////////////////////////////////////////////////////
		struct AdvancedPara
		{
			double m_Fractiles;
			int m_NUntestedProspects;

			AdvancedPara()
			{
				m_Fractiles = -1;
				m_NUntestedProspects=-1;
			}

			const AdvancedPara &operator=(const AdvancedPara &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_Fractiles = other.m_Fractiles ;
				m_NUntestedProspects	= other.m_NUntestedProspects	  ;
				return *this;
			}
		};
///////////////////////////////////////////////////////////////////
		struct AdvanceResourcePredication
		{
			int m_N;
			double m_P;
			double m_lamda;
			double m_alpha;
			double m_orilamda;
			double m_orialpha;

			AdvanceResourcePredication() 
			{
				m_alpha		=-1;
				m_lamda		=-1;
				m_N         =-1;
				m_P			=-1;
				m_orilamda	=-1;
				m_orialpha	=-1;
			}
			const AdvanceResourcePredication &operator=(const AdvanceResourcePredication &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_alpha		=other.m_alpha		;
				m_lamda		=other.m_lamda		;
				m_N         =other.m_N         	;
				m_P			=other.m_P			;
				m_orilamda	=other.m_orilamda	;
				m_orialpha	=other.m_orialpha	;
				return *this;
			}

		};
/////////////////////////////////////////////////////////////////////////
		/*!
		*
		**/
		struct ResourcePredication
		{
			// which samples
			// 0 means the all samples except those abnormal samples represented by < 0
			// > 0 means different sample groups
			string m_groupName;
			short m_resType;

			// given prior distribution
			// and its lifetime be maintained by outside
			CAnyDistributionStrategy *m_distribution;

			// below should be set in outside
			// ...
			// inference N type
			short m_inferenceN;
			// inference Q type
			short m_inferenceP;

			// the position(order) for getting maxQ
			short m_maxOrder;
			// min Q
			double m_minP;

			// iteration number
			short m_iterNumber;
			// calculation type
			short m_iterType;

			// freqence or range number
			double m_ranges;

			// different ranges
			double *m_rangeL;
			double *m_rangeR;

			// below should be predicated
			// ...
			// slope and interception for maxQ and maxN
			double m_slope;
			double m_interception;

			// pool distribution predication
			//double m_minPool;	// P95
			//double m_maxPool; // P5
			//double m_avgPool; // P50

			// given maximum pool size 
			double m_maxP;
			// averange resource
			double m_avgP; // pool mean value

			// sample N as min 
			double m_sampleN;
			// average N as mean value
			double m_avgN;
			// given maximum number
			double m_maxN;

			// total Q as median Q
			double m_avgQ;	// Q average
			// sample Q as min Q
			double m_sampleQ;
			// Sum Q as max Q
			double m_maxQ;
			// exceedence resource curve points
			CGeoPoint<double> m_resource_curve[500];
			std::vector<double> m_montcarlorangQ;

			// total Q for one range
			double *m_rangeQ;
			// pool number for one range in theory
			double *m_rangeN;
			// average pool for one range
			double *m_rangeP;
			// pool number for one range in practical way
			double *m_factN;
			
			//resource class
			int m_resourceclass;
			//resource type
			int m_resourcecategory;
			
			// swasonQ
			double m_swasonQ;

			double m_successrate;
			double m_NumFractiles;
			double m_hasdiscoveredN;
			std::vector<AdvanceResourcePredication> m_AdvanceResourcePredication;
			std::vector<AdvancedPara> m_AdvancedPara;
			std::vector<AdvancedSamples> m_AdvancedSamples;
			std::vector<std::vector<AdvancedSamples>> m_NPAdvancedSamples;
			int m_starcheckgroupNum;

			std::vector<CGeoPoint<double> > m_NPoints;//对应N累计分布曲线
			/*!
			*
			**/

			void ReleaseRangeQNP()
			{
				if(m_rangeQ) {::free(m_rangeQ);m_rangeQ=0;}
				if(m_rangeN) {::free(m_rangeN);m_rangeN=0;}
				if(m_rangeP) {::free(m_rangeP);m_rangeP=0;}
				if(m_factN) {::free(m_factN);m_factN=0;}
			}

			ResourcePredication() 
			{
				Reset();
			}

			~ResourcePredication() 
			{
				Release();
				Reset();
			}

			ResourcePredication(const ResourcePredication &other)
			{
				Reset();
				Release();
				*this = other;
			}
			/*!
			*
			**/
			void Release()
			{
				if(m_rangeL)
				{
					::free(m_rangeL);
				}
				m_rangeL = 0;

				if(m_rangeR)
				{
					::free(m_rangeR);
				}
				m_rangeR = 0;

				if(m_rangeQ)
				{
					::free(m_rangeQ);
				}
				m_rangeQ = 0;

				if(m_rangeN)
				{
					::free(m_rangeN);
				}
				m_rangeN = 0;
				
				if(m_rangeP)
				{
					::free(m_rangeP);
				}
				m_rangeP = 0;

				if(m_factN)
				{
					::free(m_factN);
				}
				m_factN = 0;

				if(m_distribution)
				{
					delete m_distribution;
				}
				m_distribution = 0;

			
				m_AdvanceResourcePredication.clear();
				m_AdvancedPara.clear();
				m_AdvancedSamples.clear();
				m_NPAdvancedSamples.clear();
				m_NPoints.clear();

				for(int i=0;i<500;i++)
				{
					m_resource_curve[i].m_x = 0;
					m_resource_curve[i].m_y = 0;
				}
			}

			/*!
			*
			**/
			void Reset()
			{
				m_groupName = "";
				m_resType = 0;
				m_distribution = 0;
				m_inferenceN = NT_Linear;
				m_inferenceP = PT_Linear;
				m_maxOrder = 5;
				m_minP = 0.;
				m_iterNumber = 10;
				m_iterType = IT_Simpson;
				m_ranges = 10;
				m_rangeL = 0;
				m_rangeR = 0;
				m_slope = 1.;
				m_interception = 0.;
				m_maxP = m_minP;
				m_maxN = 0.;
				//m_minPool = 0.;
				//m_maxPool = 0.;
				//m_avgPool = 0.;
				m_avgP = 0.;
				m_avgQ = 0.;
				m_sampleQ = 0.;
				m_maxQ = 0.;
				m_sampleN = 0.;
				m_avgN = 0.;
				m_rangeQ = 0;
				m_rangeN = 0;
				m_factN = 0;
				m_rangeP = 0;
				m_resourceclass=0;
				m_resourcecategory=0;
				m_swasonQ=0;
				m_successrate=0.5;
				m_NumFractiles=7;
				m_hasdiscoveredN=0;
				m_starcheckgroupNum=3;
				m_AdvanceResourcePredication.clear();
				m_AdvancedPara.clear();
				m_AdvancedSamples.clear();
				m_NPAdvancedSamples.clear();
				m_NPoints.clear();
				for(int i=0;i<500;i++)
				{
					m_resource_curve[i].m_x = 0;
					m_resource_curve[i].m_y = 0;
				}
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
				Release();
				Reset();
				m_groupName = other.m_groupName;
				m_resType = other.m_resType;
				m_inferenceN = other.m_inferenceN;
				m_inferenceP = other.m_inferenceP;
				m_maxOrder = other.m_maxOrder;
				m_minP = other.m_minP;
				m_iterNumber = other.m_iterNumber;
				m_iterType = other.m_iterType;
				m_ranges = other.m_ranges;
				m_swasonQ = other.m_swasonQ;
				
				if(other.m_rangeL && m_ranges>0)
				{
					m_rangeL = (double *)::malloc(m_ranges * sizeof(double));
					::memcpy(m_rangeL, other.m_rangeL, m_ranges * sizeof(double));
				}
				if(other.m_rangeR && m_ranges>0)
				{
					m_rangeR = (double *)::malloc(m_ranges * sizeof(double));
					::memcpy(m_rangeR, other.m_rangeR, m_ranges * sizeof(double));
				}

				if(other.m_rangeQ && m_ranges>0)
				{
					m_rangeQ = (double *)::malloc(m_ranges * sizeof(double));
					::memcpy(m_rangeQ, other.m_rangeQ, m_ranges * sizeof(double));
				}

				if(other.m_rangeN && m_ranges>0)
				{
					m_rangeN = (double *)::malloc(m_ranges * sizeof(double));
					::memcpy(m_rangeN, other.m_rangeN, m_ranges * sizeof(double));
				}

				if(other.m_rangeP && m_ranges>0)
				{
					m_rangeP = (double *)::malloc(m_ranges * sizeof(double));
					::memcpy(m_rangeP, other.m_rangeP, m_ranges * sizeof(double));
				}

				if(other.m_factN && m_ranges>0)
				{
					m_factN = (double *)::malloc(m_ranges * sizeof(double));
					::memcpy(m_factN, other.m_factN, m_ranges * sizeof(double));
				}

				

				m_slope = other.m_slope;
				m_interception = other.m_interception;
				m_maxP = other.m_maxP;
				m_maxN = other.m_maxN;
				//m_minPool = other.m_minPool;
				//m_maxPool = other.m_maxPool;
				//m_avgPool = other.m_avgPool;
				m_avgP = other.m_avgP;
				m_avgQ = other.m_avgQ;
				m_maxQ = other.m_maxQ;
				m_sampleQ = other.m_sampleQ;
				m_avgN = other.m_avgN;
				m_sampleN = other.m_sampleN;
				m_resourceclass=other.m_resourceclass;
				m_resourcecategory=other.m_resourcecategory;
				m_successrate		=other.m_successrate	;	
				m_NumFractiles		=other.m_NumFractiles	;	
				m_hasdiscoveredN 	=other.m_hasdiscoveredN ;	
				m_starcheckgroupNum = other.m_starcheckgroupNum;

				CAnyDistributionStrategy *distribution = (CAnyDistributionStrategy *)other.m_distribution;
				assert(distribution);
				if(distribution)
				{
					m_distribution = CAnyDistributionStrategy::GetDistribution(distribution->GetName());
					m_distribution->InitSamples(distribution->GetName(), distribution->GetSamples(), distribution->GetSampleSize(), distribution->GetParameters());
				}
				m_AdvanceResourcePredication.clear();
				for(int i=0;i<other.m_AdvanceResourcePredication.size();i++)
				{
					m_AdvanceResourcePredication.push_back(other.m_AdvanceResourcePredication[i]);
				}
				m_AdvancedPara.clear();
				for(int i=0;i<other.m_AdvancedPara.size();i++)
				{
					m_AdvancedPara.push_back(other.m_AdvancedPara[i]);
				}	
				m_AdvancedSamples.clear();
				for(int i=0;i<other.m_AdvancedSamples.size();i++)
				{
					m_AdvancedSamples.push_back(other.m_AdvancedSamples[i]);
				}
				m_NPoints.clear();
				for(int i=0;i<other.m_NPoints.size();i++)
				{
					m_NPoints.push_back(other.m_NPoints[i]);
				}

				m_NPAdvancedSamples.clear();
				for(int i=0;i<other.m_NPAdvancedSamples.size();i++)
				{
					std::vector<AdvancedSamples> oneAdvancedSamples;
					for(int j=0;j<other.m_NPAdvancedSamples[i].size();j++)
					{
						oneAdvancedSamples.push_back(other.m_NPAdvancedSamples[i][j]);
					}
					if(oneAdvancedSamples.size()>0)
					{
						m_NPAdvancedSamples.push_back(oneAdvancedSamples);
					}
				}

				CGeoPoint<double> m_resource_curve[500];
				for(int i=0;i<500;i++)
				{
					m_resource_curve[i] = other.m_resource_curve[i];
				}

				return *this;
			}

			/*!
			*
			**/
			bool IsReady() const
			{
				return /*m_minPool > 0. && */
					m_maxN && 
					m_maxP && 
					m_avgQ && 
					m_rangeN && 
					m_factN && 
					m_rangeL && 
					m_rangeR;
			}

			/*!
			*
			**/
			bool IsValid()
			{
				return (m_maxN > m_sampleN) && 
					(m_avgQ > m_sampleQ)/* &&
					(m_maxQ > m_avgQ)*/;
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				assert(m_distribution);

				char parameter[1024] ="\0";
				string para;//.size() ? m_groupName.c_str() : "all", 
				m_distribution->GetParameters().ToString(para);
				::sprintf(parameter,  "%s#%d#%d#%.3f#%d#%.3f#%.3f#%d#%d#%.3f#%s#%s#%d#%d#%.3f#", 
m_groupName.c_str(),m_resType, m_inferenceN,m_maxN,m_inferenceP,m_maxP, m_minP, m_iterNumber, m_iterType, m_ranges, m_distribution->GetName().c_str(), para.c_str(),m_resourcecategory,m_resourceclass,m_swasonQ);
				//保存分组
				string Lranges="";
				string Rranges="";
				for(int i=0;i<m_ranges;i++)
				{
					char ldata[30]="\0";
					char rdata[30]="\0";
					::sprintf(ldata,"%0.2f",m_rangeL[i]);
					::sprintf(rdata,"%0.2f",m_rangeR[i]);
					Lranges= Lranges + ldata;
					Rranges= Rranges + rdata;
					if(i!=m_ranges-1)
					{
						Lranges = Lranges+"|";
						Rranges = Rranges+"|";
					}
					
				}
				string savepara = parameter + Lranges +"#" +Rranges;

				return savepara;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("#","","");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				//assert(curCount == 11);
				if(curCount < 17)
					return;
				m_groupName = curToken.GetAt(0);
				m_resType = ::atoi(curToken.GetAt(1));
			
				
				m_inferenceN = ::atoi(curToken.GetAt(2));
				m_maxN = ::atoi(curToken.GetAt(3));
				m_inferenceP = ::atoi(curToken.GetAt(4));
				m_maxP = ::atof(curToken.GetAt(5));

				m_minP = ::atof(curToken.GetAt(6));
				m_iterNumber = ::atoi(curToken.GetAt(7));
				m_iterType = ::atoi(curToken.GetAt(8));
				m_ranges = ::atof(curToken.GetAt(9));
				
				string name = curToken.GetAt(10);
				string para = curToken.GetAt(11);

				m_resourcecategory = ::atoi(curToken.GetAt(12));
				m_resourceclass = ::atoi(curToken.GetAt(13));
				m_swasonQ = ::atof(curToken.GetAt(14));
				string Lranges = curToken.GetAt(15);
				string Rranges = curToken.GetAt(16);

				CAnyDistributionStrategy::DistributionParameters parameters(para);
				assert(!m_distribution);
				if(m_distribution)
				{
					delete m_distribution;
					m_distribution=0;
				}
				m_distribution = CAnyDistributionStrategy::GetDistribution(name);
				m_distribution->InitSamples(name, 0, 0, parameters);

				CAnyTokenString curTokenL("|","","");
				int curCountL = curTokenL.Trim(Lranges.c_str(), Lranges.size());
				if(m_rangeL)
				{
					::free(m_rangeL);
				}
				m_rangeL = 0;
				if(m_ranges>0)
				{
					m_rangeL = (double *)::malloc(m_ranges * sizeof(double));
				}
				for(int i=0;i<m_ranges;i++)
				{
					double dleft = ::atof(curTokenL.GetAt(i));
					m_rangeL[i]=dleft;
				}
				if(m_rangeR)
				{
					::free(m_rangeR);
				}
				m_rangeR = 0;
				CAnyTokenString curTokenR("|","","");
				int curCountR = curTokenR.Trim(Rranges.c_str(), Rranges.size());
				if(m_ranges>0)
				{
					m_rangeR = (double *)::malloc(m_ranges * sizeof(double));
				}
				for(int i=0;i<m_ranges;i++)
				{
					double dright = ::atof(curTokenR.GetAt(i));
					m_rangeR[i]=dright;
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
		CDistributionResourcePredicator(CAccumulationElement *curElement, CAnyDistributionStrategy *strategy);

		/*!
		*
		**/
		virtual ~CDistributionResourcePredicator();

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitSamples(CGeoPoint<double> *samples, int number, CAnyDistributionStrategy *strategy = 0);

		/*!
		*
		**/
		const CGeoPoint<double> *GetSamples(int &number) const;

		/*!
		*
		**/
		bool MakePredication(ResourcePredication &predication,bool isuseMulProcess=false);

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
			if(m_samples)
			{
				::free(m_samples);
			}
			m_samples = 0;
			m_number = 0;

			m_predication.Release();
		}

		/*!
		*
		**/
		bool GetRangeDesc(int order, double &sample, double &predication, double &diff, bool isForNumber = true);

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
		unsigned int Commit(bool isActivity = true);

		/*!
		*
		**/
		void RoundingOffByOrder(double *value, int number, int upperLimits);

		
	protected:
		//
		//
		//
		/*!
		*
		**/
		bool DoMakePredication(ResourcePredication &predication);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoGetLinearMaxN(ResourcePredication &predication);

		/*!
		*
		**/
		void DoGetLinearMaxQ(ResourcePredication &predication);

		/*!
		*
		**/
		void DoGetSampleSumQ(ResourcePredication &predication);

		/*!
		*
		**/
		void DoGetSampleMaxQ(ResourcePredication &predication);

		/*!
		*
		**/
		void DoGetNonLinearMaxN(ResourcePredication &predication);

		/*!
		*
		**/
		void DoGetLinearSequence(double **x, double **y);

		/*!
		利用梯形法求积分
		n：平均油藏个数
		a：平均油藏大小
		q：总的油藏大小 （n x a）
		**/
		void DoTrapezodialCalculation(ResourcePredication &predication, double start, double end, double &n, double &a, double &q);

		/*!
		利用辛普森法求积分
		n：平均油藏个数
		a：平均油藏大小
		q：总的油藏大小 （n x a）
		**/
		void DoSimpsonCalculation(ResourcePredication &predication, double start, double end, double &n, double &a, double &q);

		//
		//
		//
		/*!
		*
		**/
		double DoGetQuantile(const std::vector<double> &pools, double probability);

		/*!
		*
		**/
		static int CompareResourceValue( const void *a , const void *b ) 
		{ 
			return (*(double*)b-*(double*)a > 0) ? 1 : -1;
		}

	private:
		// samples
		CGeoPoint<double> *m_samples;
		int m_number;

		// parameters
		ResourcePredication m_predication;
	public:
		string m_remark;
		char *m_groupbitmap;
		int m_groupbitmaplength;
		char *m_distributionbitmap;
		int m_distributionbitmaplength;
		std::vector<std::vector<string>> m_datagroup;

	public:
		int m_iternumber;
		
		//产生0-1间的随机数
		double GetRand0_1() ;
		//线性插值函数
		double LinerInterpolate(double t,double t0,double p0,double t1,double p1);
		//获得未测试目标数
		int PickNumberOfUntestedProspects (int NumFractiles,double *Fractiles,int *NUntestedProspects);
		//根据勘探目标数和成功率获得油藏数
		int PickNumberOfPools(int NumberOfUntestedProspects,double SuccessRatio);
		//给定未测试目标数量、对应分位数、成功率情况下的油藏数PoolNumber及对应概率PoolNumberProb
		void GetPoolNumberProb(int MaxNumber, double * PoolNumberProb,int NumFractiles,double *Fractiles,int *NUntestedProspects,double SuccessRatio );
		
		void FitLineModel(const std::vector<CGeoPoint<double> > &samples, double &slope, double &intercept);
		void DoLinearRegression(double *x, double *y, int number, double &a, double &b);

		bool MakeAdvancedPredication(ResourcePredication &parameter,double &reallamda,double &realalpha,long &realN);
		double MakeAdvancedPredicationCal(ResourcePredication &parameter);

		void GetSamplesandoutput(std::vector<std::vector<double>> &outdatas);
	};
}

#endif