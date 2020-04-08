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
#ifndef __ANYPETRO_ACCUMULATION_BAYES_INFERENCE_H__
#define __ANYPETRO_ACCUMULATION_BAYES_INFERENCE_H__

// refer to EXPORT etc macroes
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to factor record
#include "accumulationfactor.h"

// 
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CBayesConditionInference : public CAccumulationAssessor
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CBayesConditionInference(CAccumulationElement *curElement);

		/*!
		*
		**/
		~CBayesConditionInference();

	public:
		//
		// individual and common factors
		//
		/*!
		*
		**/
		void Prepare();

		/*!
		*
		**/
		void SetDirectEvaluation(double probability);

		/*!
		*
		**/
		bool AddIndividualFactor(const CAccumulationFactor::FactorRecord &factor);

		/*!
		*
		**/
		bool AddCommonFactor(const CAccumulationFactor::FactorRecord &factor);

		/*!
		*
		**/
		bool AddInterdependedElement(CAccumulationElement *const element);

		/*!
		*
		**/
		long GetInterdependentElementCount();

		/*!
		*
		**/
		const CAccumulationElement *GetInterdependentElement(int order);

		//
		// bayes risk analysis
		//
		/*!
		*
		**/
		double GetConditionalProbability();

		/*!
		*
		**/
		double GetCommonProbability();

		/*!
		*
		**/
		double GetUnconditionalProbability();

		/*!
		* given hypotheis: this element has oil/gas, those probabilities of interdependent elements
		**/
		double GivenDiscoveryProbability(long elementIdx, bool isConformable = false);

		/*!
		* given hypothesis: this element is dry, those probabilities of interdependent elements
		**/
		double GivenDryProbability(long elementIdx, bool isConformable = false);

		//
		// acitivity persistence issues
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isActivity = true);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoFindElement(long elementIdx, CAccumulationElement **element, CBayesConditionInference **bayes);

		//
		// compare functions
		//
		/*!
		*
		**/
		static bool CompareFactorIdx(const CAccumulationFactor::FactorRecord &first, const CAccumulationFactor::FactorRecord &second);

		/*!
		*
		**/
		static bool CompareElementIdx(const CAccumulationElement *const first, const CAccumulationElement *const second);

	private:
		// condition factors
		CAccumulationFactor::FactorVector m_individuals;

		// common or shared factors
		CAccumulationFactor::FactorVector m_commons;

		// interdependent elements
		std::vector<CAccumulationElement */*const*/> m_elements;

		// may directly specify probability
		double m_probability;
	};
}
#endif