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
#ifndef __ANYPETRO_WELL_DECLINE_PRODUCITON_H__
#define __ANYPETRO_WELL_DECLINE_PRODUCITON_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
//
#include "accumulationassessor.h"
#include "accumulationelement.h"
#include "accumulationpropertyrecord.h"
#include "accumulationpropertyset.h"
using namespace AnyPetro;
//
#include "any/base/agm/reflection.hpp"
using namespace agm::reflection;

#include "any/base/anyformulaparser.h"


namespace AnyPetro
{
	class ANYPETRO_CLASS CWellDeclineProductionCurve : public CAccumulationAssessor
	{
	public:
		/*!
		*d_well_production
		**/
		//struct ProductionRecord
		//{
		//	CLASS(ProductionRecord, agm::reflection::NullClass);		
		//	FIELD2(public,long, m_idx);
		//	FIELD2(public,double,m_date);
		//	FIELD2(public,double,m_practicalProduction);
		//	FIELD2(public,string,m_formulae);

		//	// TODO:
		//	// ...
		//};
		typedef std::vector<ShaleWellProduction> RecordVector;

		enum DeclineType
		{
			DT_Unknown = -1,
			DT_Arps,
			DT_Hyperbola_Modified,
			DT_Duong,
			DT_PLE,
			DT_Custom_Formulae,
			//add new here
			DT_LGM,


			DT_SEPD,
			DT_Max
		};
		typedef std::map<int, string> DeclineTypes;

	public:
		/*!
		*
		**/
		CWellDeclineProductionCurve(CAccumulationElement *curElement, int activityType = ST_Shale_Well_Single_Curve);
		~CWellDeclineProductionCurve();

	public:
		//
		// interface for get decline types
		//
		/*!
		*
		**/
		static int GetDeclineTypeCount();
		static string GetDeclineType(int order);

		//
		//
		//
		/*!
		*
		**/
		void MakeDeclineCurve(int type, const string &formulae, double fromDate, double toDate);
		double ProductionPredication(double t);
		double ReservePredication(double t0,double t1);

		//void GetWellDataByElement(	CAccumulationElement *element,
		//							long   &eleid,
		//							long   &wellid,
		//							string &wellname,
		//							std::vector<ShaleWellProduction> &ShaleWellProductions);

		unsigned int Commit(bool isDeleted = false);
		long CommitResult(string &commitstring);
		void UpdateFormula(long elementid,string &formula);
		void LoadRecord();

		double DoHyperbolaPredication(double t);
		double DoEXPPredication(double t);
		double DoHyperbolaPredicationByData(double t,double initialProduction,double initialRate,double n);
		double DoEXPPredicationBydata(double t,double initialProduction,double initialRate);
		void DoGetDoungSampleData(double **x, double **y,double **z, int &n);
		void DoGetPLESampleData(double **x, double **y,double **z, int &n);
		void DoGetLGMSampleData(double **x, double **y, int &n);

		void GetDeclineDSamples(std::vector<CGeoPoint<double>> &tq,std::vector<double> &Dsamples);
		void GetBeclineDSamples(std::vector<CGeoPoint<double>> &tD,std::vector<double> &Bsamples);
		void GetDBFitSamples(std::vector<double> &t,std::vector<double> &q,std::vector<double> &D,std::vector<double> &b);

		int GetWellTypeByElement(CAccumulationElement *element);

		void GetCommitString(std::vector<string> &paras,string &parastring);
		void NonMinusDeclinRecord();//在不检查初始递减率情况下读取数据
	private:
		//
		//
		//
		/*!
		*
		**/
		void DoGetSampleData(double **x, double **y, int &n);

	public:
		//
		double m_initialProduction;
		double m_initialRate;
		double m_declineRate; 
		short  m_declineType;
		double m_fromDate;
		double m_toDate;
		string m_formulae;
		// for hyper modify
		double m_tlimted;//Hyperbola_modify时记录分割线的时间
		double m_productionlimted;//Hyperbola_modify时记录分割线的产量
		// for hyper extended
		double m_minRate;		// predicated min decline rate
		double m_minDate;		// predicated time
		double m_minProduction; // predicated production
		


		//for arps
		double m_arpsqi;
		double m_arpsDi;
		double m_arpsb;

		//for doung模型
		double m_Dounga;
		double m_Doungm;
		double m_Doungq0;
		double m_Doungq8;
		//for PLE模型
		double m_PLEn;
		double m_PLED1;
		double m_PLED8;
		double m_PLEqi;
		//for sepd
		double m_sepdn;
		double m_sepdtao;
		double m_sepdq0;
		double m_sepdr1;
		double m_sepdr2;
		//for lGM
		double m_LGMK;
		double m_LGMa;
		double m_LGMn;
		//for 泄油
		double m_xe;
		double m_xf;
		double m_xef;// xe/xf
		double m_r1;
		double m_r2;
		double m_A1;
		double m_A2;
		double m_L;
		bool m_isshow;//是否绘制
		//
		RecordVector m_records;

		RecordVector m_beforerecords;

		long m_elementidx;
		int m_wellltype;

		string m_remark;
	};
}
#endif
