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
#ifndef __ANYPETRO_ROV_EVALUATOR_H__
#define __ANYPETRO_ROV_EVALUATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to functor
#include "any/base/anymediator.h"
using namespace AnyBase;

// adapt decision tree
#include "any/vis/anydecisiontree.h"
using namespace AnyVis;
#include "any/thread/jtc.h"
#include "any/thread/mutex.h"
// namespace
namespace AnyPetro
{
	// forward class
	class CNpvEvaluator;

	/*!
	* Real option valuation
	**/
	class ANYPETRO_CLASS CRovEvaluator : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		enum OptionType
		{
			OT_Appraisal			= 1,
			OT_Price				= 1 << 1,
			OT_Expand			= 1 << 2,
			OT_Abandon			= 1 << 3,
		};

		/*!
		* mean-reversion model
		**/
		struct PriceParameter
		{
			double m_start;
			double m_mean;
			double m_speed;
			double m_volatility;
			double m_random;

			/*!
			*
			**/
			PriceParameter() : m_start(0.), m_mean(0.), m_speed(0.17), m_volatility(0.2), m_random(0.5)
			{
			}

			/*!
			*
			**/
			const PriceParameter &operator=(const PriceParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_start = other.m_start;
				m_mean = other.m_mean;
				m_speed = other.m_speed;
				m_volatility = other.m_volatility;
				m_random = other.m_random;

				return *this;
			}
		};

		class DecisionTreeTask: public CAnySignalTask<void()>,public JTCMonitor{
		public:
			DecisionTreeTask(int taskcount,int index,int totalcount,int uncertainty,std::vector<CAnyDecisionTree::TreeNode *>& onodes,CNpvEvaluator *npv );
			~DecisionTreeTask();
			void DoExecuteTask();
			void Notify(short type=0);
			int m_index;
			int m_taskcount;
			int m_totalcount;
			std::vector<CAnyDecisionTree::TreeNode *> outcomeNodes;
			CNpvEvaluator *m_npv;
			int m_uncertainties;
			static int m_notifycount;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CRovEvaluator(CAccumulationElement *element);

		/*!
		*
		**/
		~CRovEvaluator();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Update();

		/*!
		*
		**/
		bool Prepare(CAnyDecisionTree *tree);

		/*!
		*
		**/
		void SetTechnique(short type, int index, double quantile, double variation);

		/*!
		*
		**/
		bool IsTechniqueUncertainty(short type);

		/*!
		* corresponding to the start date
		**/
		void SetPrice(PriceParameter &parameter);

		/*!
		*
		**/
		void OptionToAppraisal();

		/*!
		*
		**/
		void OptionToPrice();

		/*!
		*
		**/
		void OptionToExpand(unsigned long from, unsigned long to, double *expandCost);

		/*!
		*
		**/
		void OptionToAbandon(unsigned long whichYear, double abandonCost);

		//
		//
		//
		/*!
		*
		**/
		bool IsReady();

		/*!
		*
		**/
		bool MakeDecisionTree(CAnyFunctor &progress);

		/*!
		*
		**/
		void SolvingDecisionTree(CAnyFunctor &progress);
		
		/*!
		*
		**/
		void BACKUPSolvingDecisionTree(CAnyFunctor &progress);

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

		/*!
		*
		**/
		void Release();

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoInsertTechniqueNode(CAnyDecisionTree::TreeNode *parent, int order);

		/*!
		*
		**/
		CAnyDecisionTree::TreeNode *DoInsertAbandonNode(CAnyDecisionTree::TreeNode *parent, int order);

		/*!
		*
		**/
		CAnyDecisionTree::TreeNode *DoInsertExpandNode(CAnyDecisionTree::TreeNode *parent, int order);

		/*!
		*
		**/
		CAnyDecisionTree::TreeNode *DoInsertPriceNode(CAnyDecisionTree::TreeNode *parent, int order);

		/*!
		* the order from m_npv->m_evaluation->m_start
		**/
		double DoPredicatePrice(CAnyDecisionTree::TreeNode *curNode, long whichYear, bool isUp = true);

		/*!
		*
		**/
		double DoPredicatePriceQuantile(CAnyDecisionTree::TreeNode *curNode, long whichYear, bool isUp = true);

		/*!
		*
		**/
		double DoGetParentPrice(CAnyDecisionTree::TreeNode *curNode);

		/*!
		*
		**/
		double DoGetAbandonCost();

		/*!
		*
		**/
		double DoGetExpandCost(int order);

	private:
		// options
		unsigned int m_options;
		unsigned long m_expandFrom;
		unsigned long m_expandTo;
		unsigned long m_abandonYear;

		// kinds of option cost
		double *m_expandCost;
		double m_abandonCost;

		// technique uncertainties
		int m_degree;
		int m_uncertainties;
		double **m_quantiles;
		double **m_variations;

		// prices
		PriceParameter m_priceParameter;
		double *m_prices;

		// to find techiniqucal uncertainty from net price valuator
		CNpvEvaluator *m_npv;
		// decision tree
		CAnyDecisionTree *m_tree;

		int m_index;
		int m_max;
		int m_taskcount;
		int m_finishedtaskcount;

		bool m_finish;
		JTCCond m_thread_finish_event;
		JTCRecursiveMutex m_internal;
	};
}

#endif
