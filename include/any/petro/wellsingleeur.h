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
#ifndef __ANYPETRO_WELL_SINGLE_EUR_H__
#define __ANYPETRO_WELL_SINGLE_EUR_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
//
#include "welldeclineproductioncurve.h"
#include "any/base/anyformulaparser.h"
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;
//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CWellSingleEUR : public CWellDeclineProductionCurve
	{
	public:
		/*!
		*
		**/

		struct ShaleWellEURParaRecord
		{
			string	m_paraname;
			double	m_paramax ;
			double	m_paramin ;
			double	m_paraavg ;
			string	m_disname;
			CAnyDistributionStrategy *m_paradis;

			ShaleWellEURParaRecord()
			{
				m_paraname="";
				m_paramax =0;
				m_paramin =0;
				m_paraavg =0;
				m_disname="";
				m_paradis=0;
			}
		};


		struct VariableDistribution
		{
			string m_name;
			CAnyDistributionStrategy *m_distribution;
		};
		typedef std::vector<VariableDistribution *> VariableVector;


		struct EURResult
		{
			//
			double m_drainage;		//泄油半径
			double m_reserve;
			
			// decline parameter
			double m_b;
			double m_Qi;
			double m_Di;
			short  m_declineType;

			// date
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
			//
			std::vector<string> m_customparas;
			std::vector<double> m_customparasvalues;

			CAnyDistributionStrategy *m_distribution;
			long					  m_elementidx;
			double m_min;
			double m_avg;
			double m_max;

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
			//for LGM模型
			double m_LGMK;
			double m_LGMa;
			double m_LGMn;
		

			EURResult()
			{
				m_reserve			=0;
				m_b					=0;
				m_Qi				=0;
				m_Di				=0;
				m_declineType		=0;
				m_fromDate			=0;
				m_toDate			=0;
				m_formulae			="";
				m_tlimted			=0;
				m_productionlimted	=0;
				m_minRate			=0;		
				m_minDate			=0;		
				m_minProduction		=0; 
				m_distribution		=0;
				m_elementidx		=0;

				
				m_Dounga			=0;
				m_Doungm			=0;
				m_Doungq0			=0;
				m_Doungq8			=0;

				m_PLEn				=0;
				m_PLED1				=0;
				m_PLED8				=0;
				m_PLEqi				=0;

				m_LGMK				=0;
				m_LGMa				=0;
				m_LGMn				=0;
			}
			const EURResult &operator=(const EURResult &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_drainage          = other.m_drainage;
				m_reserve			=other.m_reserve			;
				m_b					=other.m_b					;
				m_Qi				=other.m_Qi					;
				m_Di				=other.m_Di					;
				m_declineType		=other.m_declineType		;
				m_fromDate			=other.m_fromDate			;
				m_toDate			=other.m_toDate				;
				m_formulae			=other.m_formulae			;
				m_tlimted			=other.m_tlimted			;
				m_productionlimted	=other.m_productionlimted	;
				m_minRate			=other.m_minRate			;	
				m_minDate			=other.m_minDate			;	
				m_minProduction		=other.m_minProduction		; 
				m_distribution		=other.m_distribution		;
				m_elementidx		=other.m_elementidx			;
				m_Dounga			=other.m_Dounga				;
				m_Doungm			=other.m_Doungm				;
				m_Doungq0			=other.m_Doungq0			;
				m_Doungq8			=other.m_Doungq8			;
		
				m_PLEn				=other.m_PLEn				;
				m_PLED1				=other.m_PLED1				;
				m_PLED8				=other.m_PLED8				;
				m_PLEqi				=other.m_PLEqi				;

				m_LGMK				=other.m_LGMK				;
				m_LGMa				=other.m_LGMa				;
				m_LGMn				=other.m_LGMn				;
				return *this;		 
			}
		};
		

	public:
		//
		//
		//
		/*!
		*
		**/
		CWellSingleEUR(CAccumulationElement *curElement, int activityType = ST_Shale_Well_EUR);
		~CWellSingleEUR();

	public:
		//
		//
		//
		/*!
		* given current m_formulae
		**/
		void RegisterVariable(VariableDistribution *variable);
		void MakeSimulation(int iterations);
		double GetQuantile(double probability);

		void SetResultEUR(EURResult &eurres,double reserve,double qi,double Di,double b,std::vector<double> &customparavalues);

		long Commit(string &parastring);

		void GettoCommitParasstring(string &parastring,
									std::vector<ShaleWellEURParaRecord> &paras,
									string &startdate,string &enddate,string &todate,
									string &modename,string &endpro,string &limtdecline,string &itenum);

		void FromCommitParasstring(string &parastrings,
								   std::vector<ShaleWellEURParaRecord> &paras,
								   long &startdate,long &enddate,double &todate,
								   string &modename,double &endpro,double &limtdecline,int &itenum);
	public:
		//
		int m_seed;
		double m_Npi;//已生产累计产量
		//
		VariableVector m_variables;
		//
		std::vector<EURResult> m_eur;
		
		//for commit
		string m_remark;
		double m_P90EUR;
		double m_P50EUR;
		double m_P10EUR;
		double m_max;
		double m_min;
		CAnyDistributionStrategy *m_resdis;

	};

}
#endif
