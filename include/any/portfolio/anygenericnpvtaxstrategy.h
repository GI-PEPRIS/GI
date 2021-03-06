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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_TAX_STRATEGY_H__
#define __ANYPORTFOLIO_GENERIC_NPV_TAX_STRATEGY_H__

// refer to EXPORT
#include "anyportfolio.h"

// refer to parameter record
#include "genericnpvbasic.h"

// refer to parent
#include "anygenericnpvparameter.h"

//
namespace AnyPortfolio
{
	/*!
	*
	**/
	template<typename PriceStrategy, typename ProductionStrategy, typename InvestStrategy, typename CostStrategy>
	class ANYPORTFOLIO_CLASS CAnyGenericNPVTaxStrategy : public CAnyGenericNPVParameter
	{
		//
		enum SolutionType
		{
			ST_Default,
		};

		//
		enum TaxType
		{
			CT_Total				= 0xFFFFFFFF,
			CT_Production			= 1,
			CT_CIT					= 1 << 1,
			CT_EPT					= 1 << 2,
		};

		//
// 		typedef typename std::map<int, ParameterTreeNode*> TaxSolution;
// 		typedef typename TaxSolution::iterator solution_itr;
// 		typedef typename TaxSolution::const_iterator solution_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPVTaxStrategy(PriceStrategy *price, ProductionStrategy *prodution, InvestStrategy *invest, \
			CostStrategy *cost, const ValuationDate &duration, CAnyGenericNPVParameter *depended, int mode) ;

		/*!
		*
		**/
		~CAnyGenericNPVTaxStrategy();

	public:
		//
		//
		//
		/*!
		*
		**/
		void RegisterSolution(int type, ParameterTreeNode *root);

		/*!
		*
		**/
		bool Resolve();

		//
		//
		//
		/*!
		*
		**/
		void ResetParameters(const string &category);
		
		/*!
		*
		**/
		const ParaSolution &GetSolutions();

		/*!
		*
		**/
		void SetSolutions(const ParaSolution &solutions);

		/*!
		*
		**/
		ParameterTreeNode * GetParameterTreeNode(const string &key);

		/*!
		*
		**/
		void DeleteParameterTreeNode(const string &key);

		/*!
		*
		**/
		void GetSolutionsFromParameterTreeNodes(const std::vector<ParameterTreeNode *> &nodes);

		/*!
		*2014/10/22: set psc/cost recover's parameters
		**/
		void SetAdditionalParameters(const ParameterVector &parameters);
	private:
		//
		//
		//
		/*!
		*2014/10/17
		**/
		bool DoResolve(ParameterTreeNode *root, int level, int year);

	private:
		//
		ParaSolution m_solutions;
		//
		PriceStrategy *m_price;
		//
		ProductionStrategy *m_production;

		//
		InvestStrategy *m_invest;
		//
		CostStrategy *m_cost;
		//
		ParameterVector m_totalParameters;

		//2014/10/22
		ParameterVector m_addedParameters;
	};
}
#endif