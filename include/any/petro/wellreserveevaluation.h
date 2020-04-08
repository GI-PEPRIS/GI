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
#ifndef __ANYPETRO_WELL_EUR_EVALUATION_H__
#define __ANYPETRO_WELL_EUR_EVALUATION_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
//
#include "accumulationassessor.h"
#include "wellsingleeur.h"

#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CWellReserveEvaluation : public CAccumulationAssessor
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CWellReserveEvaluation(CAccumulationElement *curElement, int activityType = ST_Shale_Well_Reserve_Evaluation);
		~CWellReserveEvaluation();

	public:
		//
		//
		//
		/*!
		* 1, the first month, 2, the second month etc
		**/
		void GetSampleCorrelationPoints(short whichDate);//返回相关系数
		double GetSampleProductionQuantile(double probability);
		double GetSampleEURQuantile(double probability);
		unsigned int Commit(bool isDeleted = false);
		/*!
		* given correlation, to predicate new well's EUR
		**/
		double MakeNaturePredication(double production);
		void MakeNatureSimulation(int iterations, double pscale, int newwells);	// pscale = P10/P90
		double GetNatureEURQuantile(double probability);

		double CalculateCorrelation(std::vector<double> &xValues, std::vector<double> &yValues);

	private:
		/*!
		*
		**/
		static int CompareValue( const void *a , const void *b );
		double DoGetQuantile(const std::vector<double> &samples, double probability);
		double DoGetCDF(const std::vector<double> &samples, double value);

	public:
		//
		int m_seed;
		std::vector<CWellSingleEUR *> m_wells;
		std::vector<CGeoPoint<double> > m_corPts;	// x-production, y-eur

		std::vector<double> m_eurs;	// simulation results
	};
}
#endif
