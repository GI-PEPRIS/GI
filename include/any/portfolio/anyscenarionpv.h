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
#ifndef __ANYPORTFOLIO_NPV_SCENARIO_TREE_H__
#define __ANYPORTFOLIO_NPV_SCENARIO_TREE_H__

// refer to EXPORT & IMPORT
#include "anyportfolio.h"

// refer to its parent
#include "any/petro/npvevaluator.h"
using namespace AnyPetro;

// refer to STL
#include "any/base/anystl.h"

// refer to histogram
#include "any/math/histogramdistribution.h"
using namespace AnyMath;

// refer to probability tree
#include "any/vis/anyprobabilitytree.h"
using namespace AnyVis;

// refer to 
#include "anygenericnpv.h"

// namespace
namespace AnyPortfolio
{
	/*!
	*
	**/
	class ANYPORTFOLIO_CLASS CAnyScenarioNPV
	{
	public:
		/*!
		*
		**/
		enum ScenarioNodeType
		{
			SNT_Unknown = -1,
			SNT_Price,
			SNT_Reserve,
			SNT_Geological_Risk,
			SNT_Investment,
			SNT_Cost,//2018/10/10: cost
			SNT_Basic,//2018/10/10: basic
			SNT_Max
		};

		/*!
		*
		**/
		enum ScenarioBranchType
		{
			SBT_Unknown = -1,
			SBT_Low,
			SBT_Mid,		// ignore
			SBT_High,
			SBT_Max
		};

		// sample value per year
		typedef std::vector<double> SampleVector;
		typedef SampleVector::iterator sample_itr;
		typedef SampleVector::const_iterator sample_citr;

		// 
		struct ScenarioBranch
		{
			double m_probability;
			SampleVector m_samples;

			/*!
			*
			**/
			ScenarioBranch():m_probability(0.)
			{

			}

			/*!
			*
			**/
			ScenarioBranch(const ScenarioBranch &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const ScenarioBranch &operator=(const ScenarioBranch &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_probability = other.m_probability;
				m_samples.clear();
				m_samples.assign(other.m_samples.begin(), other.m_samples.end());

				return *this;
			}
		};

		// sample value per scenario, here int == SBT_High, SBT_Mid, SBT_Low
		typedef std::map<int, ScenarioBranch> BranchMap;
		typedef BranchMap::iterator branch_itr;
		typedef BranchMap::const_iterator branch_citr;

		// sample value per variable, int  == SNT_Price, SNT_Reserve, SNT_Risk
		typedef std::map<int, BranchMap> NodeMap;
		typedef NodeMap::iterator node_itr;
		typedef NodeMap::const_iterator node_citr;

		//
		typedef AnyMath::CAnyDistributionStrategy::DistributionStatistics DistributionStatistics;

		//
		friend class CAnyScenarioSolutionGenerator;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyScenarioNPV(CAccumulationElement *curElement, int degree = 3);

		/*!
		*
		**/
		~CAnyScenarioNPV();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetName(const string &name);

		/*!
		*
		**/
		string GetName();

		//
		//
		//
		/*!
		*
		**/
		void SetItrNum(int num);

		//
		//
		//
		/*!
		*
		**/
		int GetScenarioNodeTypeCount();

		/*!
		*
		**/
		int GetScenarioNodeType(int order);

		/*!
		*
		**/
		string GetScenarioNodeTypeName(int order);

		//
		//
		//
		/*!
		*
		**/
		void SetScenarioNodeSample(short nodeType, short branchType, ScenarioBranch &samples);

		/*!
		*
		**/
		void GetScenarioNodeSample(short nodeType, short branchType, ScenarioBranch &samples);

		/*!
		*
		**/
		bool MakeScenarioTree(CAnyProbabilityTree *tree);

		/*!
		*
		**/
		void MakeScenarioSimulation(int iterations, AboardGenericNPV *abroadNpv = 0, const string &key = "");

		/*!
		*
		**/
		const SampleVector &GetNpvSamples(bool isresampled = true);

		/*!
		*
		**/
		void MakeStatistics();
		const DistributionStatistics &GetStats()
		{
			return m_stats;
		}

		CHistogramDistribution *GetHistogramDistribution()
		{
			return m_histogram;
		}


		//
		//
		//
		/*!
		*
		**/
		bool IsReady(bool &isProbabilityIssue);

		//
		//
		//
		/*!
		*
		**/
		bool GetRecordsFromScenarioSamples(NPV_CustomizedRecords &records);

		/*!
		*
		**/
		bool GetScenarioSamplesFromRecords(const NPV_CustomizedRecords &records);

		//
		//
		//
		/*!
		*
		**/
		bool GetRecordsFromNpvSamples(NPV_CustomizedRecords &records);

		/*!
		*
		**/
		bool GetNpvSamplesFromRecords(const NPV_CustomizedRecords &records);

	private:
		/*!
		*
		**/
		void LoadNpv();

		//
		//2018/10/10: init restriction
		//
		/*!
		*
		**/
		void InitRestriction(int degree);

	private:
		// probability tree
		CAnyProbabilityTree *m_tree;
		// scenario node names
		string m_nodeNames[SNT_Max];
		// scenario node samples
		NodeMap m_nodeSamples;
		// simulation number
		int m_iterations;
		// simulation result
		SampleVector m_npvSamples;
		AnyMath::CHistogramDistribution *m_histogram;
		DistributionStatistics m_stats;
		SampleVector m_triSamples;	// simulated

		//element related
		CNpvEvaluator *m_evaluator;
		CAccumulationElement *m_element;

		// indicator
		string m_name;

	public:
		// 
		double m_ratio;

		double m_expCost;
		double m_devCost;
		double m_oilRes;
		double m_gasRes;
		double m_npvTax;

		//
		string m_matureType;
		string m_depthType;
		string m_trapType;
		string m_resourceType;
		string m_fieldType;
		//
		typedef std::map<std::string,bool> RestrictMap;
		typedef RestrictMap::iterator rm_itr;
		typedef RestrictMap::const_iterator rm_citr;

		RestrictMap m_restriction; 

		//2018/10/10: degree
		int m_degree;

		//basic parameters for abroad mode
		std::vector<std::string> m_abroad_basic_keys;
	};
}
#endif