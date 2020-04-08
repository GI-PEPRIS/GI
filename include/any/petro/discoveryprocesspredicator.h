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
#ifndef __ANYPETRO_DISCOVERY_PROCESS_PREDICATOR_H__
#define __ANYPETRO_DISCOVERY_PROCESS_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to ResourcePredication
#include "distributionresourcepredicator.h"

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// refer to geometry basic
#include "any/base/anygeom.h"
using namespace AnyBase;
#include "any/thread/jtc.h"

#include "boost/function.hpp"
// two kinds of implementations
// ...
#define FOR_POOL_SIZE_BY_RANK 1

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CDiscoveryProcessPredicator : public CAccumulationAssessor, public CAnyObservable
	{
	public:
		/*!
		*
		**/
		enum DiscoveryType
		{
			DT_Unknown = -1,
			DT_UnknownN,
			DT_KnownN,
			DT_Max
		};

		/*!
		*
		**/
		struct DiscoveryParameter
		{
			// distribution name
			string m_distributionName;

			// resource type
			short m_resourceType;
			// discovery type
			short m_discoveryType;
			// N type
			short m_functionType;
			// max N number
			int m_N;
			// max pool size
			double m_maxP;
			// min(economic) pool size
			double m_minP;
			//avgpool
			double m_avgP;
			// structure of pool
			int m_ranges;
			// is too many samples
			bool m_isRandom;
			// iteration for random
			long m_iterations;
			// exploration coefficient
			double m_beta;
			// distribution parameter
			double m_alpha;
			double m_lambda;

			// for inner calculation parameter
			double m_scalarN;
			int m_maxLoops;
			double m_errorlimit;
			bool m_isAbort;

			//resource class
			int m_resourceclass;
			//resourceclass type
			int m_resourcecategory;
			// maxP的方法
			int m_inferenceMaxP;
			//Q from predication
			double m_maxQ;
			double m_minQ;
			double m_avgQ;
			// swasonQ
			double m_swasonQ;

			std::vector<double> m_leftrangs;
			std::vector<double> m_rightrangs;
			/*!
			*
			**/
			DiscoveryParameter()
			{
				Prepare();
			}

			/*!
			*
			**/
			void Prepare()
			{
				m_distributionName = "geological pareto";
				m_resourceType = 0;
				m_discoveryType = DT_Unknown;
				m_functionType = 0;
				m_N = 0;
				m_maxP = 0.;
				m_minP = 0.;
				m_avgP=0.0;
				m_ranges = 10;
				m_isRandom = false;
				m_iterations = 1000;
				m_beta = 1.;
				m_alpha = 0.;
				m_lambda = 0.;
				m_resourceclass=0;
				m_resourcecategory=0;
				m_inferenceMaxP=0;
				m_maxQ=0.;
				m_minQ=0.;
				m_avgQ=0.;
				m_swasonQ=0;

				m_scalarN = 1.5;
				m_maxLoops = 5;
				m_errorlimit = 0.015;
				m_isAbort = false;

				m_leftrangs.clear();
				m_rightrangs.clear();
			}

			/*!
			*
			**/
			const DiscoveryParameter &operator=(const DiscoveryParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// distribution name
				m_distributionName = other.m_distributionName;

				// resource type
				m_resourceType = other.m_resourceType;
				// discovery type
				m_discoveryType = other.m_discoveryType;
				// N function type
				m_functionType = other.m_functionType;
				// N
				m_N = other.m_N;
				// max pool
				m_maxP = other.m_maxP;
				// min pool
				m_minP = other.m_minP;
				//avgpool
				m_avgP = other.m_avgP;
				// is too many samples
				m_isRandom = other.m_isRandom;
				// iteration for random
				m_iterations = other.m_iterations;
				// fractiles
				m_ranges = other.m_ranges;
				// exploration coefficient
				m_beta = other.m_beta;
				// distribution parameter
				m_alpha = other.m_alpha;
				m_lambda = other.m_lambda;

				m_resourceclass   = other.m_resourceclass;
				m_resourcecategory=other.m_resourcecategory;
				m_inferenceMaxP=other.m_inferenceMaxP;

				m_maxQ = other.m_maxQ;
				m_minQ = other.m_minQ;
				m_avgQ = other.m_avgQ;
				
				m_swasonQ = other.m_swasonQ;

				m_scalarN = other.m_scalarN;
				m_maxLoops = other.m_maxLoops;
				m_errorlimit = other.m_errorlimit;
				m_isAbort = other.m_isAbort;

				m_leftrangs.clear();
				m_rightrangs.clear();
				for(int i=0;i<other.m_leftrangs.size();i++)
				{
					m_leftrangs.push_back(other.m_leftrangs[i]);
				}
				for(int i=0;i<other.m_rightrangs.size();i++)
				{
					m_rightrangs.push_back(other.m_rightrangs[i]);
				}
	
				return *this;
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				char parameter[512] ="";
				::sprintf(parameter,  "%d#%d#%d#%d#%d#%d#%d#%.3f#%.3f#%.3f#%d#%d#%d#%.3f#%.3f#%.3f#%.3f#%.3f#%.3f#%.3f#%.3f#%d#", \
					m_resourceType, m_discoveryType, m_functionType, m_N, m_isRandom, m_iterations, m_ranges, m_beta, m_alpha, m_lambda,m_resourceclass,m_resourcecategory,m_inferenceMaxP,m_maxP,m_minP,m_swasonQ,m_avgP,m_maxQ,m_minQ,m_avgQ,m_errorlimit,m_maxLoops);
				string parameterx = parameter +m_distributionName;
				return parameterx;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("#","","");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				//assert(curCount == 13);
				if(curCount < 21)
					return;
				m_resourceType = ::atoi(curToken.GetAt(0));
				m_discoveryType = ::atoi(curToken.GetAt(1));
				m_functionType = ::atoi(curToken.GetAt(2));
				m_N = ::atoi(curToken.GetAt(3));
				m_isRandom = ::atoi(curToken.GetAt(4));
				m_iterations = ::atoi(curToken.GetAt(5));
				m_ranges = ::atoi(curToken.GetAt(6));
				m_beta = ::atof(curToken.GetAt(7));
				m_alpha = ::atof(curToken.GetAt(8));
				m_lambda = ::atof(curToken.GetAt(9));
				m_resourceclass = ::atoi(curToken.GetAt(10));
				m_resourcecategory = ::atoi(curToken.GetAt(11));
				m_inferenceMaxP = ::atoi(curToken.GetAt(12));
				m_maxP = ::atof(curToken.GetAt(13));
				m_minP = ::atof(curToken.GetAt(14));
				m_swasonQ = ::atof(curToken.GetAt(15));

				m_avgP = ::atof(curToken.GetAt(16));
				m_maxQ = ::atof(curToken.GetAt(17));
				m_minQ = ::atof(curToken.GetAt(18));
				m_avgQ = ::atof(curToken.GetAt(19));
				if(curCount==21)
				m_distributionName = curToken.GetAt(20);
				else if(curCount==23)
				{
					m_errorlimit = ::atof(curToken.GetAt(20));
					m_maxLoops = ::atoi(curToken.GetAt(21));
					m_distributionName = curToken.GetAt(22);
				}
				
			}
		};

		class DPTask: public CAnySignalTask<void()>,public JTCMonitor{
		public:
			DPTask( DiscoveryParameter& m_parameter,int taskcount,int m_index,CGeoPoint<double> *samples,int number,CDistributionResourcePredicator *predicator,CAnyFunctor *progress);
			~DPTask();
			void DoExecuteTask();
			//void Notify(short type=0);
			DiscoveryParameter* m_parameter;
			int m_index;
			int m_taskcount;
			CGeoPoint<double> *m_samples;
			int m_number;
			CDistributionResourcePredicator *m_predicator;
			CAnyFunctor *m_progress;
			static int m_notifycount;
		};


	public:
		//
		//
		//
		/*!
		*
		**/
		CDiscoveryProcessPredicator(CAccumulationElement *curElement);

		/*!
		*
		**/
		virtual ~CDiscoveryProcessPredicator();

	public:
		//
		//
		//
		/*!
		* whether is too many samples
		**/
		bool InitSamples(CGeoPoint<double> *samples, int number);

		/*!
		*
		**/
		const CGeoPoint<double> *GetSamples(int &number) const;

		/*!
		*
		**/
		bool MakePredication(DiscoveryParameter &parameter, bool isOnlyForBeta = false,bool useprogress=false);

		/*!
		*
		**/
		DiscoveryParameter &GetParameter()
		{
			return m_parameter;
		}

		/*!
		*
		**/
		CDistributionResourcePredicator::ResourcePredication &GetPredication()
		{
			assert(m_predicator);
			return m_predicator->GetPredication();
		}

		/*!
		* m_x sample value, m_y predication value
		**/
		void GetCreamingCurve(double beta, std::vector<CGeoPoint<double> > &curve);

		/*!
		*
		**/
		void GetCreamingCurve(double beta, int curveNumber, std::vector<std::vector<CGeoPoint<double> > > &curves);
		
		//
		// for thread version
		//
		/*!
		*
		**/
		bool MakePredicationMT(DiscoveryParameter &parameter, CAnyFunctor *progress, bool isOnlyForBeta = false);

		/*!
		* Let sub-class have its specified event types
		*/
		void Notify(short type);
		/*!
		*
		*/
		void Register(CAnyObserver *oneObserver);
		/*!
		*
		*/
		void Update();

		//
		// persistence interface
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
		void Release();


		void RestorePracticeVector (long practiceIdx);
		void RestorePracticeVector2(long practiceIdx);
		void RestorePracticeVector3(long practiceIdx);
		void RestorePracticeVector4(long practiceIdx);
		void RestorePracticeVector5(long practiceIdx);
		void RestorePracticeVector6(long practiceIdx);
		void RestorePracticeVector7(long practiceIdx);
		void RestorePracticeVector8(long practiceIdx);

		void DirectCalResource(string &disname,double min,double max,double alpha,double lambda,double N,double sampleq,CDistributionResourcePredicator::ResourcePredication &predication);

		void GetRangeByDataByDis(CAnyDistributionStrategy *dis,std::vector<double> &left,std::vector<double> &right,std::vector<double> &data) ;
		void GetCreamingCurveByParas(string &distributionName,std::vector<CGeoPoint<double>> &allsamples,
			double alpha, double lambda, int N, int discoveryType,double beta, int curveNumber, std::vector<std::vector<CGeoPoint<double> > > &curves);
	private:
		//
		//
		//
		/*!
		*
		**/
		bool IsLimitedToRandom();

		/*!
		*
		**/
		bool DoCalculateDistributionParameter(bool useprogress=false);

		/*!
		*
		**/
		void DoGetSampleMinMax(double &min, double &max);

		//
		// given unknown N
		//
		/*!
		*
		**/
		void EM_UnknownN_With_yB_Main(int n0, double *x0, double beta, double &miou, double &gama, int &N, int Ns);

		/*!
		*
		**/
		void EM_UnknownN_With_yB_2ManyData(int n0, double *x0, double beta, double &miou, double &gama, int &N, int Ns);
		
		/*!
		*
		**/
		void EM_UnknownN_With_yB_SuitableData(int n, double *x, double beta, double &miou, double &gama, double &delta);

		/*!
		*
		**/
		void Cal_SlSp(double beta, int n, int m, double **H, int t, double **B, double *b, double *Cl, double miou, double gama,  double delta, double &Sl, double &Sp);
		
		/*!
		*
		**/
		void Cal_PuSai(double beta, int n, int m, double **H, int t, double **B, double *b, double *Cl, double miou, double gama,  double delta, double &PuSai1, double &PuSai2);

#ifdef FOR_POOL_SIZE_BY_RANK
		/*!
		*
		**/
		void Cal_SlSpPuSai(double beta, int n, int m, double **H, int M, double *dGn, double miou, double gama,  double delta, double &Sl, double &Sp, double &PuSai1, double &PuSai2);
#else
		/*!
		*
		**/
		void Cal_SlSpPuSai(double beta, int n, int m, double **H, int t, double **B, double *b, double *Cl, double miou, double gama,  double delta, double &Sl, double &Sp, double &PuSai1, double &PuSai2);
#endif

		//
		// given known N
		//
		/*!
		*
		**/
		void EM_KnownN_With_yB_Main(int N, int n0, double *x0, double beta, double &miou, double &gama, int Ns);

		/*!
		*
		**/
		void EM_KnownN_With_yB_2ManyData(int n0, double *x0, double beta, double &miou, double &gama, int N0, int Ns);
		
		/*!
		*
		**/
		void EM_KnownN_With_yB_SuitableData(int N, int n, double *x, double beta, double &miou, double &gama);
		
		/*!
		*
		**/
		double Cal_A12a_yB(int n, int m, double **H, int t, double **B, double *Cl, double miou, double gama, double beta, double *b, int N);
		
		/*!
		*
		**/
		void Cal_omg_yB(int N, int n, int t, double **B, double *Cl, double miou, double gama, double beta, double *b, int m, double **H, double &omg1, double &omg2);

		//
		// common function as statistic functions
		//
		/*!
		*
		**/
		static void GetInterpolationPars(char name, double **V);
		
		/*!
		*
		**/
		static int Cal_dGn(int n, double *x, int M, double *dGn);

		/*!
		*
		**/
		static int ChangeStr2Datas(char *ss, double *fd, int nd);

		/*!
		*
		**/
		static double Cal_gama0(int n, double *lnx, double miou);
		
		/*!
		*
		**/
		static double Cal_Tl(int n, double *bi, int nl);
		
		/*!
		*
		**/
		static double Cal_A10b(int n, double *b, int l);
		
		/*!
		*
		**/
		static double Cal_A10a(int n, double *b, int l);
		
		/*!
		*
		**/
		static void Cal_bi_yB(int n, double *x, double beta, double *bi);
		
		/*!
		*
		**/
		static double Cal_Pf_yB(int m, double **H, double lmd, double miou, double gama, double beta);
		
		/*!
		*
		**/
		static double Cal_Pfdmiou_yB(int m, double **H, double lmd, double miou, double gama, double beta);
		
		/*!
		*
		**/
		static double Cal_Pfdgama_yB(int m, double **H, double lmd, double miou, double gama, double beta);
		
		/*!
		*
		**/
		static void Cal_Pfdmdo_yB(int m, double **H, double lmd, double miou, double gama, double beta, double &Pfdm, double &Pfdo);
		
		/*!
		*
		**/
		static double Cal_LogNormalDensity(double x, double lnx, double miou, double gama);
		
		/*!
		*
		**/
		static int GetPropertyN(int n0, double *x0, double beta, double &fSumCl);
		
		/*!
		*
		**/
		static void DataSortedFromLargerToLittle(int n, double *x);
		
		/*!
		*
		**/
		static void CreateRandomSampleNo(int n0, int n, int *sn);
		
		/*!
		*
		**/
		static double Cal_LogL(int n, double *x, double *lnx, double miou, double gama, double ss);

		/*!
		*
		**/
		static double Cal_SumCl(int n, double *x, double beta);

	private:
		// samples
		CGeoPoint<double> *m_samples;
		int m_number;

		// discovery parameter
		//DiscoveryParameter m_parameter;
		// distribution predicator
		
		CAnyObserver *m_observer;

		//huan for thread version
		int m_index;
		int m_stepsize;
		int m_max;
		int m_taskcount;
		int m_finishedtaskcount;
		CAnyFunctor* m_progress;

	public:
		bool m_isdirectuselandalpha;
		string m_remark;
		char *m_groupbitmap;
		int m_groupbitmaplength;
		char *m_distributionbitmap;
		int m_distributionbitmaplength;
		std::vector<std::vector<string>> m_datagroup;
		std::vector<std::vector<string>> m_customgroup;
		std::vector<std::vector<string>> m_resdisparas;
		CGeoPoint<double> m_resource_curve[500];
		std::vector<std::vector<string>> m_reslistdatas;
		std::vector<std::vector<string>> m_rescheckdatas;
		DiscoveryParameter m_parameter;
		CDistributionResourcePredicator *m_predicator;

		std::vector<std::vector<string>> m_parastr;

		std::vector<std::vector<double>>  m_para;//敏感分析结果
		std::vector<std::vector<string> > m_allcurves;//校验图版结果

		std::vector<std::vector<string>> m_modcheckparasgroup;//批量分析参数
		int m_seed;
	};
}

#endif
