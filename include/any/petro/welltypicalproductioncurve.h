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
#ifndef __ANYPETRO_WELL_TYPICAL_CURVE_H__
#define __ANYPETRO_WELL_TYPICAL_CURVE_H__

// refer to EXPORT etc macroes
#include "anypetro.h"

#include "welldeclineproductioncurve.h"
#include "accumulationassessor.h"
#include "accumulationelement.h"
#include "accumulationpropertyrecord.h"
#include "accumulationpropertyset.h"
using namespace AnyPetro;
//
namespace AnyPetro
{
	// forward class
	//class CWellDeclineProductionCurve;

	/*!
	*
	**/
	class ANYPETRO_CLASS CWellTypicalProductionCurve : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		enum TypicalCurveType
		{
			TCT_Unknown,
			TCT_Quantile,
			TCT_Exponent_Extended,
			TCT_Max
		};

		/*!
		*
		**/
		typedef std::vector<CWellDeclineProductionCurve *> WellVector;
		typedef std::vector<CGeoPoint<double> > ProductionCurve;
		struct DeclineCurve
		{
			long m_id;
			ProductionCurve m_curve;
		};
		typedef std::vector<DeclineCurve> CurveSet;

		struct MonthGroup
		{

		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CWellTypicalProductionCurve(CAccumulationElement *curElement, int activityType = ST_Shale_Well_Typical_Curve);
		~CWellTypicalProductionCurve();

	public:
		//
		//
		//
		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);
	
		//
		// general typical
		//
		/*!
		* align all curves in non-absolutely coords
		返回最小组数
		**/
		int Normalize(double &maxproduction);

		/*!
		*
		**/
		void GetMean(std::vector<CGeoPoint<double> > &samples);

		/*!
		*
		**/
		void GetQuantile(double probability, std::vector<CGeoPoint<double> > &samples);

		//
		// SPED typical
		//
		/*!
		* welltype maybe all, vertical, horizon etc
		**/
		int GetMonthGroupNumber(int wellType, double fromdate);

		/*!
		* the wells deployed int the same month, in general order
		**/
		void GetOneMonthGroup(double whichdate, std::vector<CGeoPoint<double> > &samples, int years = 3);

		int GetAddnumberByyear(int whichdate,int years);
		void GetYearandMonthFromNumber( int number ,int &year,int &month);

		void RestoreXymjVector(long practiceIdx);
		double GetAFromOnstring(std::vector<string> &onestring);
	private:
		/*!
		*
		**/
		double DoGetQuantile(const std::vector<double> &samples, double probability);
		
		/*!
		*
		**/
		static int CompareValue( const void *a , const void *b ) 
		 { 
			return (*(double*)b-*(double*)a > 0) ? 1 : -1;
		 }

	public:
		// to select the corresponding well curve
		WellVector m_wells;
		// all production curves normalized
		CurveSet m_curves;

		std::vector<double> m_sepdtimes;

		long m_elementidx;

		int m_needwelltype;//需要进行统计的井类型；0 vertical 1 horizon

		std::vector<std::vector<string>> m_xymjdatagroup;
		string m_remark;
	};

}
#endif
