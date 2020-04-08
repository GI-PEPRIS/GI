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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_COST_STRATEGY_H__
#define __ANYPORTFOLIO_GENERIC_NPV_COST_STRATEGY_H__

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
	template<typename PriceStrategy, typename ProductionStrategy, typename InvestStrategy>
	class ANYPORTFOLIO_CLASS CAnyGenericNPVCostStrategy : public CAnyGenericNPVParameter
	{
	public:
		//
		enum SolutionType
		{
			ST_Default,
		};

		//
		enum CostType
		{
			CT_Total				= 0xFFFFFFFF,
			CT_Lifting				= 1,
			CT_Distribution			= 1 << 1,
			CT_Production			= 1 << 2,
			CT_Abandonment			= 1 << 3,
			CT_Others				= 1 << 4,
		};

		// cost kinds
		typedef std::map<string, std::vector<double> > CostValue;
		typedef CostValue::iterator cost_itr;
		typedef CostValue::const_iterator cost_citr;

		// cost solution
		typedef std::map<string, CostValue> CostSolution;
		typedef CostSolution::iterator solution_itr;
		typedef CostSolution::const_iterator solution_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPVCostStrategy(PriceStrategy *price, ProductionStrategy *prodution, InvestStrategy *invest, const ValuationDate &duration, CAnyGenericNPVParameter *depended, int mode);

		/*!
		*
		**/
		~CAnyGenericNPVCostStrategy();

	public:
		//
		//
		//
		/*!
		*
		**/
		void RegisterSolution(int type, ParameterTreeNode *root);
				
		//
		//
		//
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
		static void ClearSolution(ParaSolution &solutions);
		
		//
		//
		//
		/*!
		*
		**/
		static void GetParameters(ParaSolution &solutions, ParameterVector &parameters);
		
		//
		//
		//
		/*!
		*
		**/
		static ParameterTreeNode * GetParameterTreeNode(ParaSolution &solutions, const string &key);

		/*!
		*
		**/
		static void DeleteParameterTreeNode(ParaSolution &solutions, const string &key);
		
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

		//
		//cost input related....
		//
		/*!
		*
		**/
		void RegisterSolution(const string &solutionIdx, CostValue &costs);

		/*!
		*
		**/
		const std::vector<double> &GetSolutionValues(const string &solutionIdx, const string &resId);

		/*!
		*
		**/
		void ClearInputs();

		/*!
		*
		**/
		const CostSolution &GetInputs();

		/*!
		*
		**/
		void SetInputs(const CostSolution &inputs);

		//
		//
		//
		/*!
		*
		**/
		std::string GetSolutionsStr();

		//
		//update solution
		//
		/*!
		*
		**/
		bool UpdateSolution(const string &newKey, const string &oldKey, const string &remark);

		/*!
		*
		**/
		bool DeleteSolution(const string &key);

		/*!
		*
		**/
		void UpdateSolutionInFormula(const ParameterVector &parameters);

		//
		//
		//
		/*!
		*
		**/
		bool DoResolveDepended(ParameterTreeNode *root, int year);

	private:
		/*!
		*
		**/
		void ResetSolution();

	private:
		//
		//
		//
		/*!
		*
		**/
		bool DoResolve(ParameterTreeNode *root, int level);
		
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

		ParameterVector m_totalParameters;

		//
		CostSolution m_inputs;
	};
}
#endif