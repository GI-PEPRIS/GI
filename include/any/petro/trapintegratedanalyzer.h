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
#ifndef __ANYPETRO_TRAP_INTEGRATED_ANALYZER_H__
#define __ANYPETRO_TRAP_INTEGRATED_ANALYZER_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// 
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CTrapIntegratedAnalyzer : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		enum AnalysisFactor
		{
			// data quality or reliability
			AF_Reliability		= 1,
			// geological evaluation
			AF_Risk				= 1 << 1,
			// in-place resouce
			AF_Resource		= 1 << 2,
			// npv
			AF_NPV				= 1 << 3,
			// exploration
			AF_Exploation	= 1 << 4,
			// economic integrated
			AF_Economic		= 1 << 5,
			// engineering integrated
			AF_Engineering	= 1 << 6,
		};
		const static int MAX_FACTOR = 7;

		/*!
		*
		**/
		enum AnalysisWay
		{
			AW_Unknown = -1,
			AW_Cross_Plot,
			AW_Parallel_Weight,
			AW_Parallel_Coefficient,
			AW_Max
		};

	public:
		CTrapIntegratedAnalyzer();
		~CTrapIntegratedAnalyzer();

	public:
		//
		// overiding functions
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
		// analysis functions
		//
		/*!
		*
		**/
		void SetElements(std::vector<CAccumulationElement *> &elements);

		/*!
		*
		**/
		void SetParameter(unsigned int factor, short analysisType, double *weights = 0, int number = MAX_FACTOR);

		/*!
		*
		**/
		bool MakeAnalysis();

		/*!
		*
		**/
		const std::vector<CAccumulationElement *> &GetResult(unsigned int orderby);

	private:
		/*!
		*
		**/
		static bool OrderById(const CAccumulationElement *first, const CAccumulationElement *second);
		/*!
		*
		**/
		static bool OrderByName(const CAccumulationElement *first, const CAccumulationElement *second);
		/*!
		*
		**/
		static bool OrderByReliability(const CAccumulationElement *first, const CAccumulationElement *second);

		/*!
		*
		**/
		static bool OrderByRisk(const CAccumulationElement *first, const CAccumulationElement *second);

		/*!
		*
		**/
		static bool OrderByResource(const CAccumulationElement *first, const CAccumulationElement *second);

		/*!
		*
		**/
		static bool OrderByNPV(const CAccumulationElement *first, const CAccumulationElement *second);

		/*!
		*
		**/
		static bool OrderByExploation(const CAccumulationElement *first, const CAccumulationElement *second);

		/*!
		*
		**/
		static bool OrderByEconomic(const CAccumulationElement *first, const CAccumulationElement *second);

		/*!
		*
		**/
		static bool OrderByEngineering(const CAccumulationElement *first, const CAccumulationElement *second);

	private:
		// factor type
		unsigned int m_factor;
		double m_weights[MAX_FACTOR]; 

		// analysis way
		short m_analysisType;

		// traps selected
		std::vector<CAccumulationElement *> m_elements;
	};
}
#endif