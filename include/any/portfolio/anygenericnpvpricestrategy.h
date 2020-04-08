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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_PRICE_STRATEGY_H__
#define __ANYPORTFOLIO_GENERIC_NPV_PRICE_STRATEGY_H__

// refer to EXPORT
#include "anyportfolio.h"

// refer to parameter record
#include "genericnpvbasic.h"

// refer to parent
#include "anygenericnpvparameter.h"

//
namespace AnyPortfolio
{
	// forward class
	class CAnyGenericNPVFormulae;

	/*!
	*
	**/
	class ANYPORTFOLIO_CLASS CAnyGenericNPVPriceStrategy : public CAnyGenericNPVParameter
	{
	public:
		//
		enum SolutionType
		{
			ST_Default = 0,
		};

		// price against specified resource type
		typedef std::map<string, std::vector<double> > ResourcePrice;
		typedef ResourcePrice::iterator price_itr;
		typedef ResourcePrice::const_iterator price_citr;

		// price solution
		typedef std::map<string, ResourcePrice> PriceSolution;
		typedef PriceSolution::iterator solution_itr;
		typedef PriceSolution::const_iterator solution_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPVPriceStrategy(const ValuationDate &duration, CAnyGenericNPVParameter *depended, int mode);

		/*!
		*
		**/
		~CAnyGenericNPVPriceStrategy();

	public:
		//
		//
		//
		/*!
		* aginst kinds of price solution
		**/
		void RegisterSolution(const string &solutionIdx, ResourcePrice &prices);

		/*!
		*
		**/
		static void RegisterSolution(const string &solutionIdx, ResourcePrice &prices, PriceSolution &solutions);

		/*!
		*
		**/
		static void RegisterResourceValues(ResourcePrice &resPrice, const string &resId, std::vector<double> &prices);

		/*!
		*
		**/
		const std::vector<double> &GetSolutionValues(const string &solutionIdx, const string &resId);

		//
		// TODO: to use tag-dispatching
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
		const PriceSolution &GetSolutions();

		/*!
		*
		**/
		void SetSolutions(const PriceSolution &solutions);

		/*!
		*
		**/
		static void UpdateSolutionParameterName(PriceSolution &solutions, ParameterVector &kinds, ParameterVector &parameters);

		//
		//
		//
		/*!
		*
		**/
		std::string GetSolutionsStr();

		/*!
		*
		**/
		static std::string DoGetSolutionsStr(PriceSolution &solutions,ParameterVector &kinds,const SolutionRemarkMap &map, const string &solutionString);

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
		static bool DoUpdateSolution(PriceSolution &solutions, const string &newKey, const string &oldKey, int duration, \
			ParameterVector &kinds, string &curSolution);

		/*!
		*
		**/
		bool DeleteSolution(const string &key);

		/*!
		*
		**/
		static bool DoDeleteSolution(PriceSolution &solutions, const string &key, string &curSolution);

		/*!
		* 2014/10/13: NPVSOLUTION(Solution:Cost:Operation) -> Operation
		**/
		static string GetSolutionKey(const string &key, const string &category, const string &subCategory);
	private:
		/*!
		*
		**/
		void ResetSolution();

		/*!
		*
		**/
		static bool IsNameExist(ParameterVector &parameters, const string &name);

	private:
		//
		PriceSolution m_solutions;
	};
}
#endif