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
#ifndef __ANYPETRO_NPV_EVALUATOR_H__
#define __ANYPETRO_NPV_EVALUATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to kinds of npv record
#include "npvparameterrecord.h"

#include "any/base/anyformulaparser.h"
using namespace AnyBase;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CNpvEvaluator : public CAccumulationAssessor
	{
		// relatives
		friend class CRovEvaluator;

	public:
		// record set
		typedef std::vector<NPV_BasicRecord *> RecordVector;
		typedef RecordVector::iterator rec_itr;
		typedef RecordVector::const_iterator rec_citr;

		//
		typedef std::vector<RecordVector> RecordVectors;
		typedef RecordVectors::iterator recs_itr;
		typedef RecordVectors::const_iterator recs_citr;

		// parameter map
		typedef std::map<short, RecordVector > ParameterMap;
		typedef ParameterMap::iterator para_itr;
		typedef ParameterMap::const_iterator para_citr;
		
		/*!
		*
		**/
		enum EvaluationType
		{
			ET_Unknown = -1,
			ET_Marginal,
			ET_Conditional,
			ET_UnConditional,
			ET_Dry,
			ET_Max,
		};

		/*!
		*
		**/
		struct ResourceEvaluation
		{
			// evaluation type
			unsigned short m_type;

			// start and npv date
			int m_start;
			int m_duration;

			// prices predicated from pre-exploration to disposal
			double *m_prices[NPV_RT_Max];
			double *m_reserves[NPV_RT_Max];
			int *m_wells[NPV_RT_Max];
			int *m_injections[NPV_RT_Max];

			double *m_incomes[NPV_RT_Max];
			double *m_expenditures; // exploration fee against different phases
			double *m_operations; // operation fee against different phases

			//2016/6/6: allowance in shale version
			double *m_allowances[NPV_RT_Max];
			double *m_allowanceIncomes[NPV_RT_Max];

			// results against determinisitic and non-determinisitc ways
			// ...
			// 1 means deterministic, > 1 non-deterministic
			int m_rounds;
			double **m_npvs;
			double **m_irrs;
			double *m_npv;

			//newly added
			double ***m_expend;
			double ***m_operat;
			double ***m_npvss;
			double ***m_npvssTax;
			double ***m_irrss;

			double ***m_incomess;
			double ***m_wellCost;
			double ***m_injectionCost;
			double ***m_facilityCost;
			double ***m_facilityTransCost;
			double ***m_investmentCost;

			double **m_npvNew;
			double **m_npvTaxNew;

			//
			double **m_emvTaxNew;
			double **m_wellExpCosts;

			//npv with tax
			double **m_npvsTax;
			double *m_npvTax;

			// firr
			double m_firr;
			double m_firrTax;

			//income tax related variables
			bool m_isYearDepreciation;
			long m_depreciationYear;
			double *m_depreciation;
			
			//
			double *m_investment;

			//
			double *m_profit;
			double *m_taxableProfit;
			double *m_loss;
			double *m_adjustmentTax;

			//economic measures
			double m_outFlow;
			double m_pc;
			double m_pe;
			double m_pcGas;
			double m_peGas;
			double m_peOilReserve;
			double m_pcOilReserve;
			double m_peGasReserve;
			double m_pcGasReserve;
			double m_emv;
			double m_emvTax;

			//for report 
			double m_avgOperCost;
			double m_wellExpCost;
			string m_productionCapacity;
			string m_avgPrices;
			double m_expCost;
			double m_devCost;

			//newly added,2014/6/27
			double m_avgManagementCost;
			double m_avgSpecialCost;
			double m_riskValue;

			//oil cost type:for tax calculation
			int m_costOilCalType;

			//for investment calculation method
			int m_investCalType;

			std::map<int,int> m_roundMap;

			/*!
			*
			**/
			ResourceEvaluation() : m_type(ET_Unknown), m_start(0), m_duration(0), m_rounds(1), m_firr(0.), m_firrTax(0.),\
				 m_expenditures(0), m_operations(0), m_npvs(0), m_irrs(0), m_npv(0),m_npvsTax(0),m_npvTax(0),\
				 m_depreciation(0),m_profit(0),m_taxableProfit(0),m_loss(0),m_adjustmentTax(0),m_isYearDepreciation(true),m_depreciationYear(10),\
				 m_outFlow(0.),m_pc(0.), m_pe(0.), m_pcGas(0.), m_peGas(0.),m_peOilReserve(0.), m_pcOilReserve(0.), m_emv(0.),m_emvTax(0.),\
				 m_peGasReserve(0.), m_pcGasReserve(0.),\
				 m_costOilCalType(NPV_COT_Key_Element),m_investment(0),m_investCalType(NPV_CBT_By_Year),\
				 m_wellExpCost(0.),m_avgOperCost(0.),m_productionCapacity(""),m_avgPrices(""),m_expCost(0.),m_devCost(0.),
				 m_expend(0),m_operat(0),m_npvss(0),m_npvssTax(0),m_irrss(0),m_npvNew(0),m_npvTaxNew(0),
				 m_incomess(0),m_wellCost(0), m_injectionCost(0),m_facilityCost(0),m_facilityTransCost(0),m_investmentCost(0),m_emvTaxNew(0),m_wellExpCosts(0),\
				 m_avgManagementCost(0.), m_avgSpecialCost(0.),m_riskValue(0.)
			{
				int i = NPV_RT_Unknown;
				for(; i < NPV_RT_Max; i++)
				{
					m_prices[i] = 0;					
					m_reserves[i] = 0;
					m_wells[i] = 0;
					m_injections[i] = 0;
					m_incomes[i] = 0;

					//2016/6/6
					m_allowances[i] = 0;
					m_allowanceIncomes[i] = 0;
				}
			}

			/*!
			*
			**/
			~ResourceEvaluation()
			{
				//Release();
			}

			/*!
			*
			**/
			ResourceEvaluation(const ResourceEvaluation &other) 
			{
				*this = other;
			}

			/*!
			*
			**/
			const ResourceEvaluation &operator=(const ResourceEvaluation &other)
			{
				if(this == &other)
				{
					return *this;
				}

				Release();
				m_type = other.m_type;
				m_start = other.m_start;
				m_duration = other.m_duration;
				m_rounds = other.m_rounds;
				m_firr = other.m_firr;
				m_firrTax = other.m_firrTax;
				m_isYearDepreciation = other.m_isYearDepreciation;
				m_depreciationYear = other.m_depreciationYear;
				m_outFlow = other.m_outFlow;
				m_pc = other.m_pc;
				m_pe = other.m_pe;
				m_pcGas = other.m_pcGas;
				m_peGas = other.m_peGas;
				m_peOilReserve = other.m_peOilReserve;
				m_pcOilReserve = other.m_pcOilReserve;
				m_peGasReserve = other.m_peGasReserve;
				m_pcGasReserve = other.m_pcGasReserve;
				m_emv = other.m_emv;
				m_emvTax = other.m_emvTax;
				m_avgOperCost = other.m_avgOperCost;
				m_wellExpCost = other.m_wellExpCost;
				m_productionCapacity = other.m_productionCapacity;
				m_avgPrices = other.m_avgPrices;
				m_expCost = other.m_expCost;
				m_devCost = other.m_devCost;
				m_costOilCalType = other.m_costOilCalType;
				m_investCalType = other.m_investCalType;
				
				//
				m_avgManagementCost = other.m_avgManagementCost;
				m_avgSpecialCost = other.m_avgSpecialCost;
				m_riskValue = other.m_riskValue;
				
				int i = NPV_RT_Unknown+1;
				for(; i < NPV_RT_Max; i++)
				{
					if(m_duration>0)
					{
						CopyRecord(m_prices[i],other.m_prices[i]);
						CopyRecord(m_reserves[i],other.m_reserves[i]);
						CopyRecord(m_incomes[i],other.m_incomes[i]);
						CopyRecord((double *&)m_wells[i],(double *)other.m_wells[i]);
						CopyRecord((double *&)m_injections[i],(double *)other.m_injections[i]);

						//2016/6/6
						CopyRecord(m_allowances[i],other.m_allowances[i]);
						CopyRecord(m_allowanceIncomes[i],other.m_allowanceIncomes[i]);
					}
				}

				//*
				CopyRecord(m_expenditures,other.m_expenditures);
				CopyRecord(m_operations,other.m_operations);
				CopyRecord(m_npv,other.m_npv);
				CopyRecord(m_npvTax,other.m_npvTax);
				CopyRecord(m_investment,other.m_investment);
				CopyRecord(m_depreciation,other.m_depreciation);
				CopyRecord(m_profit,other.m_profit);
				CopyRecord(m_taxableProfit,other.m_taxableProfit);
				CopyRecord(m_loss,other.m_loss);
				CopyRecord(m_adjustmentTax,other.m_adjustmentTax);

				//**
				CopyRecords(m_npvs,other.m_npvs,m_rounds);
				CopyRecords(m_npvsTax,other.m_npvsTax,m_rounds);
				CopyRecords(m_irrs,other.m_irrs,m_rounds);

				//newly added
				CopyRecords(m_npvNew,other.m_npvNew,ET_Max);
				CopyRecords(m_npvTaxNew,other.m_npvTaxNew,ET_Max);
				CopyRecords(m_emvTaxNew,other.m_emvTaxNew,ET_Max);
				CopyRecords(m_wellExpCosts,other.m_wellExpCosts,ET_Max);

				//***
				CopyRecordss(m_expend,other.m_expend);
				CopyRecordss(m_operat,other.m_operat);
				CopyRecordss(m_npvss,other.m_npvss);
				CopyRecordss(m_npvssTax,other.m_npvssTax);
				CopyRecordss(m_irrss,other.m_irrss);
				
				CopyRecordss(m_incomess,other.m_incomess);
				CopyRecordss(m_wellCost,other.m_wellCost);
				CopyRecordss(m_injectionCost,other.m_injectionCost);
				CopyRecordss(m_facilityCost,other.m_facilityCost);
				CopyRecordss(m_facilityTransCost,other.m_facilityTransCost);
				CopyRecordss(m_investmentCost,other.m_investmentCost);
				
				return *this;
			}

			/*!
			*
			**/
			void CopyRecordss(double *** &record, double *** otherRecord)
			{
				if(otherRecord)
				{
					record = (double ***)::malloc(ET_Max * sizeof(double **));
					for(int i = 0; i < ET_Max; i++)
					{
						CopyRecords(record[i],otherRecord[i],m_rounds);
					}
				}
			}

			/*!
			*
			**/
			void CopyRecords(double ** &record, double ** otherRecord, int num)
			{
				if(otherRecord)
				{
					record = (double **)::malloc(num * sizeof(double *));
					for(int i = 0; i < num; i++)
					{
						CopyRecord(record[i],otherRecord[i]);
					}
				}
			}

			/*!
			*
			**/
			void CopyRecord(double * &record, const double *otherRecord)
			{
				if (otherRecord)
				{
					record = (double *)::malloc(sizeof(double) * m_duration);
					for (int j = 0;j < m_duration; j++)
					{
						record[j] = otherRecord[j];
					}
				}
			}
			
			/*!
			*
			**/
			void Release()
			{
				//*
				Release(m_expenditures);
				Release(m_operations);
				Release(m_depreciation);
				Release(m_investment);
				Release(m_profit);
				Release(m_taxableProfit);
				Release(m_loss);
				Release(m_adjustmentTax);
				Release(m_npv);
				Release(m_npvTax);
				
				//resource type related
				int i = NPV_RT_Unknown + 1;
				for(; i < NPV_RT_Max; i++)
				{
					Release(m_prices[i]);
					Release(m_reserves[i]);
					Release(m_incomes[i]);
					Release((double*&)m_wells[i]);
					Release((double*&)m_injections[i]);

					//2016/6/6
					Release(m_allowances[i]);
					Release(m_allowanceIncomes[i]);
				}

				//**
				Release(m_npvs);
				Release(m_irrs);
				Release(m_npvsTax);

				//***
				ReleaseVariables();
			}

			/*!
			*
			**/
			void Release(double ** &record)
			{
				if (!record)
				{
					return;
				}

				int i = 0;
				for(; i < m_rounds; i++)
				{
					Release(record[i]);
				}

				::free(record);
				record = 0;
			}

			/*!
			*
			**/
			void Release(double * &record)
			{
				if(record)
				{
					::free(record);
				}
				record = 0;
			}

			/*!
			*
			**/
			void ReleaseVariables()
			{
				int i = ET_Unknown + 1;
				for(; i < ET_Max; i++)
				{
					int j = 0;
					for(; j < m_roundMap[i]; j++)
					{
						::free(m_npvss[i][j]);
						::free(m_npvssTax[i][j]);
						::free(m_expend[i][j]);
						::free(m_operat[i][j]);
						::free(m_irrss[i][j]);

						::free(m_incomess[i][j]);
						::free(m_wellCost[i][j]);
						::free(m_injectionCost[i][j]);
						::free(m_facilityCost[i][j]);
						::free(m_facilityTransCost[i][j]);
						::free(m_investmentCost[i][j]);
					}

					::free(m_npvss[i]);
					::free(m_npvssTax[i]);
					::free(m_expend[i]);
					::free(m_operat[i]);
					::free(m_irrss[i]);

					::free(m_incomess[i]);
					::free(m_wellCost[i]);
					::free(m_injectionCost[i]);
					::free(m_facilityCost[i]);
					::free(m_facilityTransCost[i]);
					::free(m_investmentCost[i]);
				}

				::free(m_npvss);
				::free(m_npvssTax);
				::free(m_expend);
				::free(m_operat);
				::free(m_irrss);

				::free(m_incomess);
				::free(m_wellCost);
				::free(m_injectionCost);
				::free(m_facilityCost);
				::free(m_facilityTransCost);
				::free(m_investmentCost);

				//
				i = ET_Unknown + 1;
				for(; i < ET_Max; i++)
				{
					::free(m_npvNew[i]);
					::free(m_npvTaxNew[i]);
					::free(m_emvTaxNew[i]);
					::free(m_wellExpCosts[i]);
				}
				::free(m_npvNew);
				::free(m_npvTaxNew);
				::free(m_emvTaxNew);
				::free(m_wellExpCosts);
			}
		};

		/*!
		*
		**/
		enum SensitivityParameter
		{
			SP_Unknown = -1,
			SP_Inflation,
			SP_Fixed_Cost,
			SP_Variable_Cost,
			SP_Production,
			SP_Drilling_Expense,
			SP_Decline_Rate,
			SP_Other_CAPEX,
			SP_Tax,
			SP_Price,
			SP_Max
		};

		/*!
		*
		**/
		enum SinopecSensitivityParameter
		{
			SSP_Unknown = -1,
			SSP_Output,
			SSP_Exploration_Investment,
			SSP_Development_Investment,
			SSP_Production_Cost,
			SSP_Commodity_Rate,
			SSP_Tax,
			SSP_Price,
			SSP_Max,
		};

		/*!
		*
		**/
		enum NpvCalculationType
		{
			NCT_General = 0,
			NCT_Sinopec,
			NCT_Prospect,
			NCT_Single_Well,//2015/6/24:well npv
			NCT_Shale_Oil,//2016/5/30: shale oil
			NCT_Abroad_Mine_Tax,
			NCT_Abroad_PSC,//2014/9/25: Production Sharing Contract
			NCT_Abroad_Service_Contract,//2014/9/25: Service Contract
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CNpvEvaluator(CAccumulationElement *curElement);

		/*!
		*
		**/
		~CNpvEvaluator();

	
		/*!
		*
		**/
		const CNpvEvaluator &operator=(const CNpvEvaluator &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_isExpInvestCount = other.m_isExpInvestCount;
			m_isCommitAsTemplate = other.m_isCommitAsTemplate;
			m_remark = other.m_remark;
			m_npvMode = other.m_npvMode;
			// resource evaluation
			m_evaluation=other.m_evaluation;

			// parameters
			para_itr itr = m_parameters.begin();
			for(; itr != m_parameters.end(); itr++)
			{
				int i = 0;
				for(; i < itr->second.size(); i++)
				{
					delete itr->second[i];
				}
				itr->second.clear();
			}
			m_parameters.clear();

			std::map<short, RecordVector>::const_iterator it;
			for(it=other.m_parameters.begin();it!=other.m_parameters.end();it++)
			{
				RecordVector tmpVec;
				RecordVector oldVec=(RecordVector)it->second;
				for(int i=0;i<oldVec.size();i++)
				{
					short type=it->first;
					NPV_BasicRecord* p;
					switch(type){
					case NPV_PRT_Policy:
						p=new NPV_PolicyRecord();
						*(NPV_PolicyRecord*)p=*(NPV_PolicyRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case NPV_PRT_Risk:
						p=new NPV_RiskRecord();
						*(NPV_RiskRecord*)p=*((NPV_RiskRecord*)oldVec[i]);
						tmpVec.push_back(p);
						break;
					case NPV_PRT_Resource:
						p=new NPV_ResourceRecord();
						*/*(NPV_ResourceRecord*)*/p=*(NPV_ResourceRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case  NPV_PRT_EDP_Basic:
						p=new NPV_EDP_BasicRecord();
						*(NPV_EDP_BasicRecord*)p=*(NPV_EDP_BasicRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case NPV_PRT_EDP_Schedule:
						p=new NPV_EDP_ScheduleRecord();
						*(NPV_EDP_ScheduleRecord*)p=*(NPV_EDP_ScheduleRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case NPV_PRT_Cost_Basic:
						p=new NPV_Cost_BasicRecord();
						*(NPV_Cost_BasicRecord*)p=*(NPV_Cost_BasicRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case  NPV_PRT_Cost_Detail:
						p=new NPV_Cost_DetailRecord();
						*(NPV_Cost_DetailRecord*)p=*(NPV_Cost_DetailRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case NPV_PRT_Cost_Oil:
						p=new NPV_Cost_OilRecord();
						*(NPV_Cost_OilRecord*)p=*(NPV_Cost_OilRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case NPV_PRT_Price:
						p=new NPV_PriceRecord();
						*(NPV_PriceRecord*)p=*(NPV_PriceRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case NPV_PRT_Tax:
						p=new NPV_TaxRecord();
						*(NPV_TaxRecord*)p=*(NPV_TaxRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					case NPV_PRT_Summary:
						p=new NPV_SummaryRecord();
						*(NPV_SummaryRecord*)p=*(NPV_SummaryRecord*)oldVec[i];
						tmpVec.push_back(p);
						break;
					default:
						break;
					}

				}
				m_parameters.insert(std::pair<short, RecordVector>(it->first,tmpVec));
			}
			//m_parameters=other.m_parameters;

			return *this;
		}
	public:
		//
		//
		//
		/*!
		*
		**/
		void InsertParameter(short type, RecordVector &recs);

		/*!
		*
		**/
		void UpdateParameter(short type, RecordVector &recs);

		/*!
		*
		**/
		void LoadParameters(unsigned long practiceIdx);

		/*!
		*
		**/
		const RecordVector &GetParameter(short type);

		/*!
		*
		**/
		bool IsExistParameter(short type);

		//
		//
		//
		/*!
		*
		**/
		bool PrepareDate();

		/*!
		*
		**/
		bool PrepareReserve();

		/*!
		*
		**/
		void SetReserves(RecordVectors &reserves);

		/*!
		*
		**/
		bool PrepareWell();

		/*!
		*
		**/
		bool PreparePrice();

		/*!
		*
		**/
		void SetReserves(std::vector<double> &reserves);

		/*!
		*
		**/
		void SetPrice(std::vector<double> &prices);

		//
		//
		//
		/*!
		*
		**/
		bool IsReady(bool isForRov = false);

		/*!
		*
		**/
		bool IsScheduleReady();

		/*!
		*
		**/
		double DoGetWellCost(int whichyear);

		/*!
		*
		**/
		double DoGetInjectionCost(int whichyear);

		/*!
		*
		**/
		double DoGetFacilityVariable(int whichyear);

		/*!
		*
		**/
		double DoGetFacilityTransVariable(int whichyear);

		//
		//
		//
		/*!
		*
		**/
		bool MakeEvaluation(unsigned long rounds = 1, unsigned short type = ET_Marginal, bool isForFirr = false, double quantile = -1.);

		/*!
		*
		**/
		void CalculateFIRR();

		/*!
		*
		**/
		void CalculateEcoMeasures();

		/*!
		* both support determinisitc and non-deterministic ways
		**/
		const ResourceEvaluation &GetEvaluation()
		{
			return m_evaluation;
		}

		/*!
		* against market, technique uncertainties
		**/
		double DirectEvaluation(short resourceType, double *prices, double *sensitivities);

		/*!
		* against market, technique uncertainties
		**/
		double DirectEvaluationForSinopec(short resourceType, double *prices, double *sensitivities);


		/*!
		*
		**/
		void GetSensitivityName(short type, string &name);

		/*!
		*
		**/
		void GetSensitivityNameForSinopec(short type, string &name);

		/*!
		*
		**/
		bool MakeSensitivity(short type, double *variables, double *npvs, int count, const std::string &resulttype = "npv", double screenChange = 50.);

		/*!
		*
		**/
		bool MakeSensitivityForSinopec(short type, double *variables, double *npvs, int count, const std::string &resulttype = "npv", double screenChange = 50.);

		//
		//
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);

		/*!
		*
		**/
		unsigned int CommitSummary(double npv, double riskValue, double irr, double expInvest, double devInvest, const string &remark = "Prospect ");

		/*!
		*
		**/
		bool DeleteNPVPracticeRecord(long practiceIdx);

		//
		//
		//
		/*!
		*
		**/
		double GetPolicyRate(int type, int whichYear);

		/*!
		*
		**/
		double GetInvestmentCost(int phase, int whichYear, int wellType = NPV_WT_Unknown);

		//
		//
		//
		/*!
		*
		**/
		static void GetFormula(CAnyFormulaParser &parser, std::string &formula, double reserve = 1.0, double prodRatio = 1.0, double scalar = 1.0, \
			double declineRate = 1.0, double declineIndex = 1.0);

		/*!
		*
		**/
		static void GetProspectFormula(CAnyFormulaParser &parser, std::string &formula, double proscale = 1.0, double declineRate = 1.0, double yearScalar = 1.0, double previousRes = 1.0);
	
		//
		//
		//
		/*!
		*
		**/
		double CalculateBreakEvenPrice(double invest, double fixedCost, double varCost, double commodityRate, double irr, bool isPreTax = true,\
			double vat = 0., double consTax = 0., double eduTax = 0., double rate = -0x7fffffff);

		/*!
		*
		**/
		double CalculateBreakEvenCost(double invest, double price, double commodityRate, double irr, bool isPreTax = true,\
			double vat = 0., double consTax = 0., double eduTax = 0., double rate = -0x7fffffff);

		/*!
		*
		**/
		double CalculateBreakEvenInvest(double price, double fixedCost, double varCost, double commodityRate, double irr, bool isPreTax = true,\
			double vat = 0., double consTax = 0., double eduTax = 0., double rate = -0x7fffffff);

				/*!
		*
		**/
		double CalculateBreakEvenYield(double invest, double price, double fixedCost, double varCost, double commodityRate, double irr, bool isPreTax = true,\
			double vat = 0., double consTax = 0., double eduTax = 0.);
	private:
		//
		//
		//
		/*!
		*
		**/
		void DoCalculateEcoMeasures(bool isNpvPostive,bool isPe, double quantile = -1.);
		
		/*!
		*
		**/
		void DoCalculatePcPeProbability();

		//
		//
		//
		/*!
		*
		**/
		void DoMakeSensitiveForInvestment(int phase,double *variables, double *npvs, int count, double bkNpv, double screenChange, const std::string &resulttype);
		
		//
		//
		//
		/*!
		*
		**/
		int DoGetWellNumber(int resourceType, int whichYear, bool isInjected = false);

		/*!
		*
		**/
		double DoGetOperationVariable(int whichyear);

		/*!
		*
		**/
		double DoGetTransVariable(int whichyear);

		/*!
		*
		**/
		double DoCalculateInflation(int whichyear);

		/*!
		*
		**/
		double DoGetRiskProbability();

		//
		// determinisitc and non-determinisitic against make evaluation
		//
		/*!
		*
		**/
		void DoMakePrepare(int rounds);

		/*!
		*
		**/
		void DoMakeIncome(double quantile, int rounds);

		/*!
		*
		**/
		void DoMakeExpenditure(double *basicQuantiles, double *detailQuantiles, short type, int rounds, int curRound, double quantiles = -1.);
		
		/*!
		*
		**/
		double GetReserveRate(int startYear, int curYear);

		/*!
		*
		**/
		void DoCalculateTaxCost(NPV_TaxRecord *taxRec, int resType, int whichYear);

		/*!
		*
		**/
		double GetVatTax(int resType, double income, int whichYear);

		/*!
		*
		**/
		double DoGetVatRatedCost(int whichYear, double rate);
		/*!
		*
		**/
		void DoCalculateOilCost(NPV_Cost_OilRecord *oilRec, int resType, int whichYear);

		/*!
		*
		**/
		double DoGetBasicCost(NPV_Cost_BasicRecord *costBasicRec, int phase, int costType = NPV_CT_Expenditure, int wellType = NPV_WT_Unknown);

		/*!
		*
		**/
		double DoGetDetailWellCost(NPV_Cost_DetailRecord *costRec, int phase, int wellType = NPV_WT_Drilling);

		/*!
		*
		**/
		double DoGetDetailVariableCost(NPV_Cost_DetailRecord *costRec,int variableType = NPV_VT_Facility);

		//
		//
		//
		/*!
		*
		**/
		void DoInsertPolicyRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertResourceRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertEDPBasicRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertEDPScheduleRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertCostBasicRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertCostDetailRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertCostOilRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		const string GetParametersToInsert(NPV_CustomizedRecords &records);

		/*!
		*
		**/
		const string GetOilParametersToInsert(NPV_Cost_OilRecord *costOilRec = 0, NPV_TaxRecord *taxTec = 0);

		/*!
		*
		**/
		void DoInsertBlobFieldRecord(CAnyAccessor &accessor, const string &tableName, long practiceId, const string &parameters, const string &fieldName = "data");

		/*!
		*
		**/
		void DoInsertPriceRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertTaxRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoInsertSummaryRecord(CAnyAccessor &accessor, long practiceIdx);

		//
		//
		//
		/*!
		*
		**/
		void DoLoadPolicyRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadEDPBasicRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadEDPScheduleRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadCostBasicRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadCostDetailRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadCostOilRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadPriceRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadTaxRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadSummaryRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoLoadResourceRecord(CAnyAccessor &accessor, RecordVector &recs);

		/*!
		*
		**/
		static void DoLoadResourceTypeRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		void DoLoadScenarioRecord(CAnyAccessor &accessor, RecordVector &recs, const string &sql);

		/*!
		*
		**/
		void DoInsertScenarioRecord(CAnyAccessor &accessor, long practiceIdx);

		/*!
		*
		**/
		void DoLoadBlobFieldRecord(CAnyAccessor &accessor, string &para, const string &fieldName = "data");

		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		void InitVariables();

		/*!
		*
		**/
		bool DoDeleteNPVPracticeRecord(CAnyAccessor &accessor, const string &tableName, long practiceIdx);

		//
		// common functions for sensitivity analysis
		//
		/*!
		*
		**/
		void DoCalculateNpvSensitivity(double *npvs, int order, double bkNpv, double screenChange, const std::string &resulttype);

		/*!
		*
		**/
		void DoChangeFixedCost(NPV_Cost_BasicRecord *costRec, NPV_Cost_BasicRecord &bkRec, double variation);

		/*!
		*
		**/
		void DoChangeVariableCost(NPV_Cost_DetailRecord *costRec, NPV_Cost_DetailRecord &bkRec, double variation);

		/*!
		*
		**/
		void DoChangeDrillingExpense(NPV_Cost_DetailRecord *costRec, NPV_Cost_DetailRecord &bkRec, double variation);

		/*!
		*
		**/
		void DoChangeOtherCapex(NPV_Cost_BasicRecord *costRec, NPV_Cost_BasicRecord &bkRec, double variation);

		/*!
		* for spider diagram, sensitive parameter
		**/
		void DoChangeBasicCost(int sensiType, NPV_Cost_BasicRecord *costRec, NPV_Cost_BasicRecord &bkRec, double variation);

		/*!
		* for for spider diagram, sensitive parameter
		**/
		void DoChangeDetailCost(int sensiType, NPV_Cost_DetailRecord *costRec, NPV_Cost_DetailRecord &bkRec, double variation);

		//
		//
		//
		/*!
		*
		**/
		static bool ComparePriceYear(NPV_BasicRecord *first, NPV_BasicRecord *second)
		{
			if (((NPV_PriceRecord *)first)->m_year < ((NPV_PriceRecord *)second)->m_year)
			{
				return true;
			}
			else if (((NPV_PriceRecord *)first)->m_year == ((NPV_PriceRecord *)second)->m_year)
			{
				return ((NPV_PriceRecord *)first)->m_type < ((NPV_PriceRecord *)second)->m_type;
			}
			else
			{
				return false;
			}
		}

		/*!
		*
		**/
		static bool ComparePriceResType(NPV_BasicRecord *first, NPV_BasicRecord *second)
		{
			return ((NPV_PriceRecord *)first)->m_type < ((NPV_PriceRecord *)second)->m_type;
		}

		/*!
		*
		**/
		static bool CompareScheduleResource(NPV_BasicRecord *first, NPV_BasicRecord *second)
		{
			return ((NPV_EDP_ScheduleRecord *)first)->m_type < ((NPV_EDP_ScheduleRecord *)second)->m_type;
		}

		/*!
		*
		**/
		static bool CompareCostDetailType(NPV_BasicRecord *first, NPV_BasicRecord *second)
		{
			return ((NPV_Cost_DetailRecord *)first)->m_type < ((NPV_Cost_DetailRecord *)second)->m_type;
		}

		/*!
		*
		**/
		double DoCalculateFIRR(NPV_PolicyRecord *policyRec, int rounds, double bkFirr, bool isForTax);

		/*!
		*
		**/
		int GetSeeds();

		/*!
		*
		**/
		const string GetWellStrToInsert(std::vector<NPV_WellCostRecord> &records);

		/*!
		*
		**/
		const string GetProspectFormulaStrToInsert(std::vector<string> &strs);
	protected:
		// resource evaluation
		ResourceEvaluation m_evaluation;

		// parameters
		ParameterMap m_parameters;

		// persistence tables
		static string m_policyTable;
		static string m_riskTable;
		static string m_resourceTable;
		static string m_edpBasicTable;
		static string m_edpScheduleTable;
		static string m_costBasicTable;
		static string m_costDetailTable;
		static string m_costMmbsTable;
		static string m_priceTable;
		static string m_taxTable;
		static string m_summaryTable;
		static string m_scenarioTable;

		//
		bool m_isExpInvestCount;

		CAnyFormulaParser m_parser;

		bool m_isForEcoMeasure;
		int m_bkRounds;

	public:
		//used in Commit()
		bool m_isCommitAsTemplate;

		bool m_isLoadAll;

		string m_remark;

		//
		int m_npvMode;
		bool m_isProspectMode;
		bool m_isAbroadMode;//mine tax

		bool m_isWellMode;//2015/6/24:well mode

		//2014/9/25
		bool m_isAbroadPSC;//Production Sharing Contract
		bool m_isAbroadSC;//Service Contract
		
		//
		std::vector<double> m_pcOilRes;
		std::vector<double> m_pcGasRes;
		std::vector<double> m_peOilRes;
		std::vector<double> m_peGasRes;

		std::vector<double> m_pcOil;
		std::vector<double> m_pcGas;
		std::vector<double> m_peOil;
		std::vector<double> m_peGas;

		//for scenario probability
		double m_scenarioProbability;

		//2015/11/3: for arps, lgm...
		DeclineFittingPara m_declinePara;

		//2016/5/30:record enum NpvCalculationType
		int m_npvSpecificMode;
	};
}

#endif