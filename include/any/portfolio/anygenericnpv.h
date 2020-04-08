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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_H__
#define __ANYPORTFOLIO_GENERIC_NPV_H__

// refer to EXPORT & IMPORT
#include "anyportfolio.h"

//
#include "genericnpvbasic.h"
#include "anygenericnpvparameter.h"
#include "anygenericnpvpricestrategy.h"
#include "anygenericnpvproductionstrategy.h"
#include "anygenericnpvinveststrategy.h"
#include "anygenericnpvcoststrategy.h"
#include "anygenericnpvtaxstrategy.h"
#include "anygenericnpvformulae.h"
//
namespace AnyPortfolio
{
	/*!
	*
	**/
	template<typename CommonParameter, typename PriceStrategy, typename ProductionStrategy, typename InvestStrategy, typename CostStrategy, typename TaxStrategy>
	class ANYPORTFOLIO_CLASS CAnyGenericNPV
	{
	public:
		/*!
		*
		**/
		enum SensitivityParameter
		{
			SP_Unknown = -1,
			SP_Production,
			SP_Investment,
			SP_Price,
			SP_Cost,
			SP_Max,
		};

		//
		typedef std::map<string,std::vector<ParameterTreeNode *>> TreeMap;
		typedef TreeMap::iterator tmsolution_itr;
		typedef TreeMap::const_iterator tmsolution_citr;

	public:	
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPV(const ValuationDate &duration, int mode = AMT_Mine_Tax) : m_common(0), m_price(0), m_production(0), m_invest(0), m_cost(0), m_tax(0),m_resolvedName("")
		{
			m_mode = mode;
			m_duration = duration;

			m_common = new CommonParameter(m_duration, 0, mode);
			m_price = new PriceStrategy(m_duration, m_common, mode);
			m_production = new ProductionStrategy(m_duration, m_common, mode);
			m_invest = new InvestStrategy(m_duration, m_common, mode);
			
			//
			m_invest->m_production = m_production;

			m_cost = new CostStrategy(m_price, m_production, m_invest, m_duration, m_common, mode);
			m_tax = new TaxStrategy(m_price, m_production, m_invest, m_cost, m_duration, m_common, mode);

			m_total = new CAnyGenericNPVParameter(m_duration,m_common, mode);
		}

		/*!
		*
		**/
		~CAnyGenericNPV()
		{
			ClearTree();
			if(m_common)
			{
				delete m_common;
			}
			if(m_price)
			{
				delete m_price;
			}
			if(m_production)
			{
				delete m_production;
			}
			if(m_invest)
			{
				delete m_invest;
			}
			if(m_cost)
			{
				delete m_cost;
			}
			if(m_tax)
			{
				delete m_tax;
			}
			if (m_total)
			{
				delete m_total;
			}
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetPriceSolution(int solution, int type)
		{
			assert(m_price);
			m_price->SetSolution(solution, type);
		}
		void SetProductionSolution(int solution, int type)
		{
			assert(m_production);
			m_production->SetSolution(solution, type);
		}
		void SetInvestSolution(int solution, int type)
		{
			assert(m_invest);
			m_invest->SetSolution(solution, type);
		}
		void SetCostSolution(int solution, int type)
		{
			assert(m_cost);
			m_cost->SetSolution(solution, type);
		}
		void SetTaxSolution(int solution, int type)
		{
			assert(m_tax);
			m_tax->SetSolution(solution, type);
		}

		//
		//
		//
		/*!
		* to add and delete parameter
		**/
		CommonParameter *GetCommonParameter()
		{
			assert(m_common);
			return m_common;
		}
		PriceStrategy *GetPriceStrategy()
		{
			assert(m_price);
			return m_price;
		}
		ProductionStrategy *GetProductionStrategy()
		{
			assert(m_production);
			return m_production;
		}
		InvestStrategy *GetInvestStrategy()
		{
			assert(m_invest);
			return m_invest;
		}
		CostStrategy *GetCostStrategy()
		{
			assert(m_cost);
			return m_cost;
		}
		TaxStrategy *GetTaxStrategy()
		{
			assert(m_tax);
			return m_tax;
		}

		//
		//
		//
		/*!
		*
		**/
		void SetDuration(const ValuationDate &duration)
		{
			m_duration = duration;
			m_common->SetDuration(duration);
			m_price->SetDuration(duration);
			m_production->SetDuration(duration);
			m_invest->SetDuration(duration);
			m_cost->SetDuration(duration);
			m_tax->SetDuration(duration);
			m_total->SetDuration(duration);
		}

		/*!
		*
		**/
		const ValuationDate &GetDuration()
		{
			return m_duration;
		}

		//
		//
		//
		/*!
		*
		**/
		bool InsertTree(const string &type, std::vector<ParameterTreeNode *> &trees);

		/*!
		*
		**/
		bool DoInsertTree(std::vector<ParameterTreeNode *> &trees, ParameterTreeNode *node);

		/*!
		*
		**/
		void GetParameterTreeNodes(const string &type, std::vector<ParameterTreeNode *> &trees);

		/*!
		*
		**/
		void ClearTree(const string &name = "");

		/*!
		*
		**/
		bool Resolve(const string &name = "");

		//
		//
		//
		/*!
		*
		**/
		void ResetParameters(const string &name);

		/*!
		*
		**/
		void SetReslovedParameterName(const string &name);
		
		/*!
		*
		**/
		void DeleteParameterTreeNode(const string &key);

		/*!
		*
		**/
		ParameterTreeNode *GetParameterTreeNode(const string &key);

		/*!
		*
		**/
		void GetParameters(ParameterVector &parameters, const string &key = "");

		//
		//
		//
		/*!
		*
		**/
		string GetSensitivityName(short type);

		/*!
		*
		**/
		bool MakeSensitivity(short type, double *variables, double *npvs, int count, const string &key);

		/*!
		*
		**/
		bool ResolveAll(double variable = -100.);

		/*!
		*
		**/
		double GetParameterTotalValue(const string &key);

		//
		//
		//
		/*!
		* itself
		**/
		void UpdateFormula(const string &oldKey, const string &newKey);

		/*!
		* itself
		**/
		void UpdateAllFormula(const string &oldKey, const string &newKey, bool isParameterRecord = false);

		//
		//
		//
		/*!
		*
		**/
		void GetTreesFromParameterTreeNodes(const string &name, std::vector<ParameterTreeNode *> &nodes);

		
		/*!
		*2016/7/7
		**/
		double ReverseCalculateParameter(const string &reverseKey, const string &resultKey, double resultVal);

	private:
		/*!
		*
		**/
		void DoClearTree(std::vector<ParameterTreeNode *> &trees);
		
		//
		//
		//
		/*!
		*2014/10/17
		**/
		bool DoResolve(ParameterTreeNode *root, int level, int year);

		/*!
		*
		**/
		bool DoResolve(ParameterTreeNode *root, int level);
	private:
		//
		ValuationDate m_duration;

		// input
		// get below variable given specified time/year
		// ...
		CommonParameter *m_common;
		PriceStrategy *m_price;
		ProductionStrategy *m_production;
		InvestStrategy *m_invest;
		CostStrategy *m_cost;
		TaxStrategy *m_tax;

		// output
		//
		std::vector<ParameterTreeNode *> m_trees;
				
		TreeMap m_treeMap;
		//
		CAnyGenericNPVParameter *m_total;
		ParameterVector m_totalParameters;
		ParameterVector m_parameters;

		//
		ParameterVector m_profitParameters;
		ParameterVector m_npvParameters;
		ParameterVector m_npvSipcParameters;

		//2014/10/15:add psc and cost recover paras
		ParameterVector m_pscParameters;
		ParameterVector m_costRcParameters;		

		string m_resolvedName;

		//solutions
		ParameterVector m_kinds;

		//2014/10/8: mode
		int m_mode;
	};

	//
	typedef CAnyGenericNPV<CAnyGenericNPVParameter, CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy, \
	CAnyGenericNPVCostStrategy<CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy>,  \
	CAnyGenericNPVTaxStrategy<CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy, CAnyGenericNPVCostStrategy<CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy>> > AboardGenericNPV;

	template class ANYPORTFOLIO_CLASS CAnyGenericNPV<CAnyGenericNPVParameter, CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy, \
	CAnyGenericNPVCostStrategy<CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy>,  \
	CAnyGenericNPVTaxStrategy<CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy, CAnyGenericNPVCostStrategy<CAnyGenericNPVPriceStrategy, CAnyGenericNPVProductionStrategy, CAnyGenericNPVInvestStrategy>> >;
}
#endif
