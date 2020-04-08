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
#ifndef __ANYPETRO_PROSPECT_INTEGRATED_ANALYZER_H__
#define __ANYPETRO_PROSPECT_INTEGRATED_ANALYZER_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to GetElementByIdx(...)
#include "accumulationelement.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to VOLUME parameter
#include "volumetricpredicator.h"

// refer to functor
#include "any/base/anymediator.h"
using namespace AnyBase;

// refer to distribution
#include "any/math/anydistributionstrategy.h"
#include "any/math/anyrandomgenerator.h"
using namespace AnyMath;

// refer to resourcegroup etc
#include "any/vis/anyresourcediagram.h"
using namespace AnyVis;

#include "any/thread/jtc.h"
#include "boost/function.hpp"

// namespace
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CProspectIntegratedAnalyzer : public CAccumulationAssessor, public CAnyObservable
	{
		// for recursive simulation
		typedef std::map<long, CProspectIntegratedAnalyzer*> AnalyzerMap;
		typedef AnalyzerMap::iterator analyzer_itr;
		typedef AnalyzerMap::const_iterator analyzer_citr;

	public:
		/*!
		* deprecated
		**/
		struct ConformableBedPair
		{
			CAccumulationElement *m_top;
			CAccumulationElement *m_bottom;

			double m_multiplierMax;
			double m_multiplierMin;

			/*!
			*
			**/
			ConformableBedPair() : m_top(0), m_bottom(0), m_multiplierMax(0.), m_multiplierMin(0.)
			{
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				string str;
				str.reserve(1024);
				char parameter[512] = "";
				::sprintf(parameter, "%d|%d|%.3f|%.3f#", m_top->GetIdx(), m_bottom->GetIdx(), m_multiplierMax, m_multiplierMin);
				str = parameter;
				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("|","","");
				//curToken.SetToken("#");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				
				long idxtop = ::atoi(curToken.GetAt(0));
				long idxbottom = ::atoi(curToken.GetAt(1));
				m_multiplierMax = ::atof(curToken.GetAt(2));
				m_multiplierMin = ::atof(curToken.GetAt(3));
				m_top = CAccumulationElement::GetElementByIdx(idxtop,CAccumulationElement::GetRootElement());
				m_bottom = CAccumulationElement::GetElementByIdx(idxbottom,CAccumulationElement::GetRootElement());
			
			}
		};

		/*!
		*
		**/
		enum RiskDependencyType
		{
			RDT_Unknown= -1,
			RDT_Max_Dependency,
			RDT_Partial_Dependency,
			RDT_No_Dependency,
			RDT_Max
		};

		/*!
		*
		**/
		enum RiskSceneGeology
		{
			RSG_Unknown = -1,
			RSG_Trap_Seal,
			RSG_Reservoir_Presence,	
			RSG_Reservoir_Quality,
			RSG_Source_Migration,
			RSG_Max
		};
		
		/*!
		*
		**/
		enum RiskSceneType
		{
			RST_None = 1,
			RST_Both = 1 << 1,
			RST_Depended = 1 << 2,
			RST_Dependable = 1 << 3
		};

		/*!
		*
		**/
		struct RiskSceneProbability
		{
			unsigned int m_type;
			double m_probability;

			/*!
			*
			**/
			RiskSceneProbability() : m_type(RST_None), m_probability(0.)
			{
			}

			/*!
			*
			**/
			const RiskSceneProbability &operator=(const RiskSceneProbability &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_type = other.m_type;
				m_probability = other.m_probability;
				return *this;
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				string str;
				str.reserve(1024);
				char parameter[512] = "";
				::sprintf(parameter, "%d|%.3f#", m_type, m_probability);
				str = parameter;
				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("|","","");
				//curToken.SetToken("#");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				
				m_type = ::atoi(curToken.GetAt(0));
				m_probability = ::atof(curToken.GetAt(1));	
			}
		};

		/*!
		*
		**/
		struct RiskDependencyPair
		{
			CAccumulationElement *m_depended;
			CAccumulationElement *m_dependable;

			int m_dependencyType;
			int m_dependencyScene;

			/*!
			*
			**/
			RiskDependencyPair() : m_depended(0), m_dependable(0), m_dependencyType(RDT_Unknown), m_dependencyScene(RDT_Unknown)
			{
			}

			/*!
			*
			**/
			const RiskDependencyPair &operator=(const RiskDependencyPair &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_depended = other.m_depended;
				m_dependable = other.m_dependable;
				m_dependencyType = other.m_dependencyType;
				m_dependencyScene = other.m_dependencyScene;

				return *this;
			}

			/*!
			* for RiskDependencyType
			**/
			static string GetTypeName(int type)
			{
				if(type == RDT_Max_Dependency)
				{
					return "Max Dependency";
				}
				else if(type == RDT_Partial_Dependency)
				{
					return "Conditional Dependency";
				}
				else if(type == RDT_No_Dependency)
				{
					return "Independency";
				}

				return "";
			}

			/*!
			*  for RiskDependencyScene
			**/
			static string GetSceneName(int type)
			{
				if(type == RSG_Trap_Seal)
				{
					return "Trap and Seal";
				}
				else if(type == RSG_Reservoir_Presence)
				{
					return "Reservoir Presence";
				}
				else if(type == RSG_Reservoir_Quality)
				{
					return "Reservoir Quality";
				}
				else if(type == RSG_Source_Migration)
				{
					return "Source and Migration";
				}

				return "";
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				string str;
				str.reserve(1024);
				char parameter[512] = "";
				::sprintf(parameter, "%d|%d|%d|%d#", m_depended->GetIdx(), m_dependable->GetIdx(), m_dependencyType, m_dependencyScene);
				str = parameter;
				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("|","","");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				
				long idxtop = ::atoi(curToken.GetAt(0));
				long idxbottom = ::atoi(curToken.GetAt(1));
				m_dependencyType = ::atoi(curToken.GetAt(2));
				m_dependencyScene = ::atoi(curToken.GetAt(3));
				m_depended = CAccumulationElement::GetElementByIdx(idxtop,CAccumulationElement::GetRootElement());
				m_dependable = CAccumulationElement::GetElementByIdx(idxbottom,CAccumulationElement::GetRootElement());
			
			}
		};

		/*!
		*
		**/
		struct FaultLeakPair
		{
			CAccumulationElement *m_from;
			CAccumulationElement *m_to;

			/*!
			*
			**/
			FaultLeakPair() : m_from(0), m_to(0)
			{
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				string str;
				str.reserve(1024);
				char parameter[512] = "";
				::sprintf(parameter, "%d|%d#", m_from->GetIdx(), m_to->GetIdx());
				str = parameter;
				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("|","","");
				//curToken.SetToken("#");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				
				long idxtop = ::atoi(curToken.GetAt(0));
				long idxbottom = ::atoi(curToken.GetAt(1));
				m_from = CAccumulationElement::GetElementByIdx(idxtop,CAccumulationElement::GetRootElement());
				m_to = CAccumulationElement::GetElementByIdx(idxbottom,CAccumulationElement::GetRootElement());
			
			}

		};

		typedef CVolumetricPredicator::ParameterCorrelationPair ParameterCorrelationPair;

		/*! 
		* by default, the upcoming bits for encoding element's ID
		**/
		enum SegmentStatusEncoding
		{
			// given risk dependency to decide
			SSE_Exist				= 1 << 31,
			// given risk dependence setting
			SSE_Risk				= 1 << 30,
			// given conformable setting
			SSE_Top				= 1 << 29,
			// given fault leaks
			SSE_Leak				= 1 << 28,
			// given parameter correlation
			SSE_Correlation		= 1 << 27,
			// whether be done
			SSE_Done				= 1 << 26,

			//
			SSE_ID_MASK = 0x00FFFFFF
		};

		//
		typedef CAnyResourceDiagram::ExceedenceProbability ExceedenceProbability;
		typedef CAnyResourceDiagram::ExceedenceResource ExceedenceResource;
		typedef CAnyResourceDiagram::ResourceGroup ResourceGroup;
		typedef CAnyResourceDiagram::ResourceVector ResourceVector;
		typedef CAnyResourceDiagram::SegmentProbability SegmentProbability;

		// put different kinds of resources together
		typedef std::map<int, ResourceVector > ResourceMap; 
		typedef ResourceMap::iterator rm_itr;
		typedef ResourceMap::const_iterator rm_citr;

		//
		typedef std::map<int, std::vector<ExceedenceResource> > ExceedenceMap;
		typedef ExceedenceMap::iterator ex_itr;
		typedef ExceedenceMap::const_iterator ex_citr;

		/*!
		*
		**/
		struct ResourceStatistics
		{
			double m_p90;
			double m_p10;
			double m_p50;
			double m_swason;

			/*!
			*
			**/
			ResourceStatistics() : m_p90(0.), m_p10(0.), m_p50(0.), m_swason(0.)
			{
			}

			/*!
			*
			**/
			void Reset()
			{
				m_p90 = 0.;
				m_p10 = 0.;
				m_p50 = 0.;
				m_swason = 0.;
			}
		};

		/*!
		* depredecated 
		**/
		class ProspectIntegratedTask: public CAnySignalTask<void()>,public JTCMonitor
		{
		public:
			ProspectIntegratedTask(CProspectIntegratedAnalyzer& parameter,int taskcount,int m_index,std::vector<CAnyRandomGenerator::RandomVector > maturities,
				std::vector<CAnyRandomGenerator::RandomVector > scenes,CAnyRandomGenerator::RandomVector multipliers,
				CAnyRandomGenerator::RandomVector leaks,CAnyRandomGenerator::RandomVector resources,std::map<long, CAnyRandomGenerator::RandomVector > quantiles, CAnyFunctor *progress);
			~ProspectIntegratedTask();
			void DoExecuteTask();
			void Notify(short type=0);
			CProspectIntegratedAnalyzer* m_parameter;
			std::vector<CAnyRandomGenerator::RandomVector > maturities;
			std::vector<CAnyRandomGenerator::RandomVector > scenes;
			CAnyRandomGenerator::RandomVector multipliers;
			CAnyRandomGenerator::RandomVector leaks;
			CAnyRandomGenerator::RandomVector resources;
			std::map<long, CAnyRandomGenerator::RandomVector > quantiles;
			int m_index;
			int m_taskcount;
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
		CProspectIntegratedAnalyzer(CAccumulationElement *curElement);

		/*!
		*
		**/
		~CProspectIntegratedAnalyzer();

	public:

		void Register(CAnyObserver *oneObserver);

		void Notify(short type);


		void Update();

		//
		// overriding functions
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
		//
		//
		/*!
		* those segments staying in memory
		**/
		void SetElements(std::vector<CAccumulationElement *> &elements);

		/*!
		*
		**/
		void SetConformableBedPair(std::vector<ConformableBedPair> &conforms);

		/*!
		*
		**/
		void SetRiskScenePair(std::vector<RiskDependencyPair> &scenes);

		/*!
		*
		**/
		void SetFaultLeakPair(std::vector<FaultLeakPair> &leaks);

		/*!
		*
		**/
		void SetParameterPair(std::vector<ParameterCorrelationPair> &parameters);

		/*!
		*
		**/
		bool IsVolumetricPredicatorReady(CAccumulationElement *element);

		/*!
		*
		**/
		bool IsBayesPredicatorReady(CAccumulationElement *element);

		/*!
		*
		**/
		void Prepare();

		/*!
		*
		**/
		bool MakeSimulation(int iterations, CAnyFunctor &progress);

		/*!
		*
		**/
		bool MakeSimulation(int iterations);

		/*!
		*
		**/
		bool MakeSimulationMT(int iterations, CAnyFunctor *progress);

		/*!
		*
		**/
		void DoCalculateScenarioProbabilities();

		/*!
		*
		**/
		void DoMakeStatistics();

		//
		// running results hidden
		//
		/*!
		*
		**/
		double GetMaturity()
		{
			return m_probabilities.m_maturity;
		}

		/*!
		*
		**/
		const ExceedenceProbability &GetProbabilities()
		{
			return m_probabilities;
		}

		/*!
		*
		**/
		double GetSceneProbability(std::vector<long> &idxes);

		/*!
		*
		**/
		bool GetSceneResources(std::vector<long> &idxes, std::vector<double> &resources,int resourcetype=0);

		/*!
		* parameter order
		**/
		double GetVariance(int order);

		/*!
		*
		**/
		void GetCorrelation(int order, std::vector<double> &samples, int pointcount = 40);

		/*!
		*
		**/
		bool ReadCommitString(string &parameter,string &retvalue);

private:
		/*!
		* order means which iteration
		**/
	    void DoSetRiskStatusWithProbabilityTree(std::vector<CAnyRandomGenerator::RandomVector > &sceneProbability, int whichIteration);

		/*!
		* deprecated functions since it only consider two limited elements
		**/
		void DoSetRiskStatus(double probability);

		/*!
		*
		**/
		void DoSetConformableStatus(double probability);

		/*!
		*
		**/
		void DoSetFaultLeakStatus(double probability);

		/*!
		*
		**/
		void DoChangeSegmentStatus(unsigned int idx, unsigned int status);

		/*!
		*
		**/
		unsigned int DoGetSegmentStatus(long idx);

		/*!
		*
		**/
		CAnyDistributionStrategy *DoGetDistributionByIdx(long idx, const string &desc);

		//
		// for recursive simulation
		//
		/*!
		*
		**/
		bool IsForRecursiveSimulation();

		/*!
		*
		**/
		bool DoRecursiveSimulation(int iterations, CAnyFunctor &progress);

		/*!
		*
		**/
		bool DoRecursiveSimulation(int iterations);

		/*!
		*
		**/
		void DoSetAnalyzerParameter(long parentIdx, CProspectIntegratedAnalyzer *analyzer);

		/*!
		*
		**/
		void DoSetAnalyzerParameter(std::vector<CAccumulationElement *> &elements, CProspectIntegratedAnalyzer *analyzer);

		/*!
		*
		**/
		bool IsExistElement(long idx, const std::vector<CAccumulationElement *> &elements);

		/*!
		*
		**/
		void ClearAnalyzers();

		/*!
		*
		**/
		void DoGetResourceQuantile(ExceedenceMap &onceMap/*std::vector<ExceedenceResource> &onceVector*/, double probability, bool isForGeological = false);

		/*!
		*
		**/
		static bool CompareResourceVector(ResourceGroup &first, ResourceGroup &second);

		//
		//
		//
		/*!
		*
		**/
		static bool CompareRiskSceneProbability(RiskSceneProbability &first, RiskSceneProbability &second);


		/*!
		获取当前对象体积参数保存的结果字符串
		**/
		string GetVolCommitString();

		/*!
		*
		**/
		string GetConformCommitString();

		/*!
		*
		**/
		string GetRiskCommitString();

		/*!
		*
		**/
		string GetleakCommitString();

		/*!
		*
		**/
		string GetcorrelationsCommitString();

		/*!
		*
		**/
		string GetIterationCommitString();
	
		/*!
		*
		**/
		string CorrelationPairToParameterString(ParameterCorrelationPair pair);
	
		/*!
		*
		**/
		void CorrelationPairFromParameterString(ParameterCorrelationPair &pair,const string &parameter);

	public:
		// Not 当前选中的对象
		CAccumulationElement *m_prospect;

		// segements selected
		std::vector<CAccumulationElement *> m_elements;
		// inner calculation status for differenciating whether one element already be done
		std::vector<unsigned int> m_statuses;
		std::vector<unsigned int> m_statusIdxes;

		// for recursive analyzers
		AnalyzerMap m_analyzers;

		// conformable bed group/pairs
		std::vector<ConformableBedPair> m_conforms;
		// risk dependency group/pairs
		std::vector<RiskDependencyPair> m_scenes;
		// fault leak group/pairs
		std::vector<FaultLeakPair> m_leaks;
		// parameter correlation group/pairs
		std::vector<ParameterCorrelationPair> m_correlations;

		// iterations
		int m_iterations;
		ResourceMap m_recResources;
		ResourceMap m_geoResources;
		int m_currentResourceKind;

		// risk from current monte-carlo
		ExceedenceProbability m_probabilities;

		//暂时用来存放结果资源量
		ResourceStatistics m_statistics[CAccumulationResourceManager::VRT_Max];
		string m_remark;

		// running parameter results
		int m_paraNumber;
		double ** m_paraValues;

		// thread-specific
		CAnyObserver *m_observer;
		int m_index;
		int m_stepsize;
		int m_max;
		int m_taskcount;
		int m_finishedtaskcount;
		CAnyFunctor* m_progress;

		//获取当前所选择对象
		std::vector<long> m_currentselectelements;


		//存放报告等数据
		std::vector<std::vector<string>> m_theelementsdata;
		std::vector<std::vector<string>> m_theelementsPropdata;
		std::vector<std::vector<string>> m_datatable;
		std::vector<std::vector<string>> m_restable;
		char *m_datagroupbitmap;//线图
		int m_datagroupbitmaplength;
		char *m_resgroupbitmap;//直方图
		int m_resgroupbitmaplength;
		char *m_disbitmap;//超概率图
		int m_disbitmaplength;

		//
		unsigned long m_userSeed;

		int m_resourcreclass;
		bool m_iscommitplate;
	};
}
#endif
