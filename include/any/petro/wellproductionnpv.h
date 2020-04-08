#ifndef __ANYPETRO_WELL_NPV_H__
#define __ANYPETRO_WELL_NPV_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
//
#include "accumulationassessor.h"
#include "welldeclineproductioncurve.h"
#include "accumulationelement.h"
#include "accumulationpropertyrecord.h"
#include "accumulationpropertyset.h"
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CWellProductionNPV : public CWellDeclineProductionCurve
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CWellProductionNPV(CAccumulationElement *curElement, int activityType = ST_Shale_Well_NPV);
		~CWellProductionNPV();

	public:
		//
		//
		//
		/*!
		todate: 0---todate
		**/
		void MakeNpvSimulation(int declinetype, double todate,double minProduction,double limitedrate,string &formula);
		unsigned int Commit(bool isDeleted = false);
		void InitSamples();
		void ClearSimSamples();
		double GetMinDateFromMinProduction(int declinetype,double minProduction,double limitedrate,string &formula);
		double GetLimtedDataByLimtedDecline(double limteddecline,double b);

		void RestorePracticeVector(long practiceIdx);
	public:
		std::vector<CGeoPoint<double> > m_wellproductions;
		long	m_startdate;
		long	m_todate;
		double	m_minproduction;
		double	m_mindate;
		double	m_limteddecline;
		double	m_limtedproduction;
		double	m_limteddate;//相对于预测开始时间（m_preinitproduction，m_preinitdeclinerate，0）的极限递减率对应时间
		double	m_b;
		double	m_preinitproduction;
		double	m_preinitdeclinerate;
		double	m_sampletodata;//最后一个样本点的时间
		int		m_npvdeclinetype;
		
		CAccumulationElement *m_element;
		string  m_remark;
		double  m_allnpv;
		std::vector<std::vector<string>> m_resdatagroup;
		std::vector<std::vector<string>> m_datadatagroup;
	};
}
#endif