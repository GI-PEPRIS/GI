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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_INVEST_STRATEGY_H__
#define __ANYPORTFOLIO_GENERIC_NPV_INVEST_STRATEGY_H__

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
	class ANYPORTFOLIO_CLASS CAnyGenericNPVInvestStrategy : public CAnyGenericNPVParameter
	{
	public:
		//
		enum SolutionType
		{
			ST_Default,
		};

		//
		enum InvestType
		{
			IT_Total			= 0xFFFFFFFF,
			IT_Well				= 1,
			IT_Facilities		= 1 << 1,
			IT_Others			= 1 << 2,
		};

		// invest kinds
		typedef std::map<string, std::vector<double> > InvestValue;
		typedef InvestValue::iterator invest_itr;
		typedef InvestValue::const_iterator invest_citr;

		// invest solution
		typedef std::map<string, InvestValue> InvestSolution;
		typedef InvestSolution::iterator solution_itr;
		typedef InvestSolution::const_iterator solution_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPVInvestStrategy(const ValuationDate &duration, CAnyGenericNPVParameter *depended, int mode);

		/*!
		*
		**/
		~CAnyGenericNPVInvestStrategy();

	public:
		//
		//
		//
		/*!
		* aginst kinds of price solution
		**/
		void RegisterSolution(const string &solutionIdx, InvestValue &invests);

		/*!
		*
		**/
		const std::vector<double> &GetSolutionValues(const string &solutionIdx, const string &resId);

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
		void ResetParameters(const string &category);

		/*!
		*
		**/
		void ClearSolution();

		/*!
		*
		**/
		const InvestSolution &GetSolutions();

		/*!
		*
		**/
		void SetSolutions(const InvestSolution &solutions);

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

	private:
		/*!
		*
		**/
		void ResetSolution();

	private:
		//
		InvestSolution m_solutions;

		//
		ParameterVector m_totalParameters;

	public:
		CAnyGenericNPVParameter *m_production;
	};
}
#endif