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
#ifndef __ANYPORTFOLIO_GENERIC_NPV_PRODUCTION_STRATEGY_H__
#define __ANYPORTFOLIO_GENERIC_NPV_PRODUCTION_STRATEGY_H__

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
	class ANYPORTFOLIO_CLASS CAnyGenericNPVProductionStrategy : public CAnyGenericNPVParameter
	{
	public:
		//
		enum ProditionSolution
		{
			PS_Default = 0,
		};

		// price against specified resource type
		typedef std::map<string, std::vector<double> > ResourceProduction;
		typedef ResourceProduction::iterator production_itr;
		typedef ResourceProduction::const_iterator production_citr;

		// price solution
		typedef std::map<string, ResourceProduction> ProductionSolution;
		typedef ProductionSolution::iterator solution_itr;
		typedef ProductionSolution::const_iterator solution_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGenericNPVProductionStrategy(const ValuationDate &duration, CAnyGenericNPVParameter *depended, int mode);

		/*!
		*
		**/
		~CAnyGenericNPVProductionStrategy();

	public:
		//
		//
		//
		/*!
		* aginst kinds of production solution
		**/
		void RegisterSolution(const string &solutionIdx, ResourceProduction &productions);


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
		const ProductionSolution &GetSolutions();

		/*!
		*
		**/
		void SetSolutions(const ProductionSolution &solutions);

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
		ProductionSolution m_solutions;
	};
}
#endif