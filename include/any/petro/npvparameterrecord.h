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
#ifndef __ANYPETRO_ACCUMULATION_NPV_RECORD_H__
#define __ANYPETRO_ACCUMULATION_NPV_RECORD_H__

// refer to string 
#include "any/base/anystl.h"

// refer to distribution
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

//
namespace AnyPetro
{
	/*!
	* TODO: need to follow the definition in accumulation element
	**/
	enum NPV_ResourceType
	{
		NPV_RT_Unknown = -1,
		NPV_RT_Oil,
		NPV_RT_Gas,
		NPV_RT_2,
		NPV_RT_3,
		NPV_RT_4,
		NPV_RT_5,
		//NPV_RT_6,
		//NPV_RT_7,
		//NPV_RT_8,
		//NPV_RT_9,
		//NPV_RT_10,
		NPV_RT_Max
	};

	/*!
	*
	**/
	enum NPV_DurationType
	{
		NPV_DT_Unknown = -1,
		NPV_DT_Exploration_Previous,
		NPV_DT_Exploration,
		NPV_DT_Exploration_Apprasial,
		NPV_DT_Development_Appraisal,
		NPV_DT_Development,
		NPV_DT_Production_Buildup,
		NPV_DT_Production_Plateau,
		NPV_DT_Production_Decline,
		NPV_DT_Disposal,
		NPV_DT_Max
	};

	/*!
	*
	**/
	enum NPV_RecordType
	{
		NPV_PRT_Unknown,
		NPV_PRT_Policy,							// basic parameters
		NPV_PRT_Risk,								// risk 	
		NPV_PRT_Resource,						// resource result		
		NPV_PRT_EDP_Basic,						// the cost and table of exploration, development and production 
		NPV_PRT_EDP_Schedule,				// the cost and table of exploration, development and production 
		NPV_PRT_Cost_Basic,						// invest cost
		NPV_PRT_Cost_Detail,					// per well cost, against different resource types
		NPV_PRT_Cost_Oil,						//oil cost per ton
		NPV_PRT_Price,								// energy price
		NPV_PRT_Tax,								//  
		NPV_PRT_Summary,						//
		NPV_PRT_Scenario,
		NPV_PRT_Max
	};

	/*!
	* for NPV_CostBasicRecord
	**/
	enum NPV_CostType
	{
		NPV_CT_Unknown = -1,
		NPV_CT_Expenditure,
		NPV_CT_Operation,
		NPV_CT_Max
	};

	/*!
	* for NPV_CostBasicRecord and NPV_CostDetailRecord
	**/
	enum NPV_SensitvieType
	{
		NPV_ST_Unknown = -1,
		NPV_ST_Fixed_Cost,			//for cost basic
		NPV_ST_Other_Capex,		//for cost basic
		NPV_ST_Drilling_Expense,		//for cost detail
		NPV_ST_Variable_Cost,		//for cost detail
		NPV_ST_Max
	};

	/*!
	* for NPV_CostDetailRecord
	**/
	enum NPV_WellType
	{
		NPV_WT_Unknown = -1,
		NPV_WT_Drilling,			//drilling well
		NPV_WT_Injection,		//injection well
		NPV_WT_Max
	};

	/*!
	* for NPV_CostDetailRecord
	**/
	enum NPV_VariableType
	{
		NPV_VT_Unknown = -1,
		NPV_VT_Facility,			
		NPV_VT_Facility_Transportation,	
		NPV_VT_Operation,	
		NPV_VT_Transportation,	
		NPV_VT_Max
	};

	/*!
	* for NPV_CostOilRecord initialization
	**/
	enum NPV_CostOilType
	{
		NPV_COT_Default = -1,
		NPV_COT_Simple,			
		NPV_COT_Key_Element,	
		NPV_COT_Production_Procedure,	
	};

	/*!
	* for cost basic
	**/
	enum NPV_CostBasicType
	{
		NPV_CBT_By_Total = 0,			
		NPV_CBT_By_Year,		
	};

	/*!
	* for cost basic
	**/
	enum NPV_OilGasConversionType
	{
		NPV_Oil2Gas = 0,			
		NPV_Gas2Oil,		
	};

	/*!
	*
	**/
	enum NPV_EDPDeclineType
	{
		NPV_EDT_Exponent = 0,
		NPV_EDT_Hyperbola,
		NPV_EDT_Harmonic,

		//2015/11/3
		NPV_EDT_Arps,
		NPV_EDT_Duong,
		NPV_EDT_PLE,
		NPV_EDT_LGM,
		NPV_EDT_SEPD,

		NPV_EDT_Custom,
	};

	/*!
	*2015/11/3
	**/
	struct DeclineFittingPara
	{
		//arps
		double arps_Q0;
		double arps_a0;
		double arps_n;

		//duong
		double duong_a;
		double duong_m;
		double duong_q0;
		double duong_q8;

		//ple
		double ple_n;
		double ple_D1;
		double ple_D8;
		double ple_qi;
		
		//lgm
		double lgm_K;
		double lgm_a;
		double lgm_n;

		//sepd
		double sepd_q0;
		double sepd_n;
		double sepd_Tao;

		/*!
		*
		**/
		DeclineFittingPara()
		{
			//arps
			arps_Q0 = 0.;
			arps_a0 = 0.;
			arps_n = 0.;

			//duong
			duong_a = 0.;
			duong_m = 0.;
			duong_q0 = 0.;
			duong_q8 = 0.;

			//ple
			ple_n = 0.;
			ple_D1 = 0.;
			ple_D8 = 0.;
			ple_qi = 0.;

			//lgm
			lgm_K = 0.;
			lgm_a = 0.;
			lgm_n = 0.;

			//sepd
			sepd_q0 = 0.;
			sepd_n = 0.;
			sepd_Tao = 0.;
		}

		/*!
		*
		**/
		bool IsParaChanged(const DeclineFittingPara &other)
		{
			if (arps_Q0 != other.arps_Q0 || arps_a0 != other.arps_a0 || arps_n != other.arps_n ||\
				duong_a != other.duong_a || duong_m != other.duong_m || duong_q0 != other.duong_q0 || duong_q8 != other.duong_q8 ||\
				ple_n != other.ple_n || ple_D1 != other.ple_D1 || ple_D8 != other.ple_D8 || ple_qi != other.ple_qi ||\
				lgm_K != other.lgm_K || lgm_a != other.lgm_a || lgm_n != other.lgm_n ||\
				sepd_q0 != other.sepd_q0 || sepd_n != other.sepd_n || sepd_Tao != other.sepd_Tao)
			{
				return true;
			}

			return false;
		}

	};

	/*!
	*
	**/
	enum NPV_Cal_Type
	{
		NPV_CAL_General = 0,
		NPV_CAL_Sinopec,
		NPV_CAL_Prospect,
	};
	

	/*!
	* customized record and vector
	**/
	struct NPV_WellCostRecord
	{
		int m_wellNum;
		double m_wellDepth;
		double m_surfaceCost;
		double m_wellCost;

		/*!
		*
		**/
		NPV_WellCostRecord() 
		{
			Reset();
		}

		/*!
		*
		**/
		const NPV_WellCostRecord &operator=(const NPV_WellCostRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_wellNum = other.m_wellNum;
			m_wellDepth = other.m_wellDepth;
			m_surfaceCost = other.m_surfaceCost;
			m_wellCost = other.m_wellCost;

			return *this;
		}

		/*!
		*
		**/
		void Reset()
		{
			m_wellNum = 0;
			m_wellDepth = 0.;
			m_surfaceCost = 0.;
			m_wellCost = 0.;
		}

		/*!
		*
		**/
		void ResetExpWell()
		{
			m_wellNum = 4;
			m_wellDepth = 3000;
			m_surfaceCost = 0.;
			m_wellCost = 5100;
		}

		/*!
		*
		**/
		void ResetDevWell()
		{
			m_wellNum = 6;
			m_wellDepth = 3000;
			m_surfaceCost = 100.;
			m_wellCost = 5618;
		}
	};
	
	/*!
	* customized record and vector
	**/
	struct NPV_CustomizedRecord
	{
		std::string m_name;			//parameter name
		std::string m_unit;			//parameter unit
		double m_value;			//parameter total value 
		int m_phase;			//parameter phase : enum NPV_DurationType
		int m_costType;			//parameter cost type : enum NPV_CostType
		int m_sensiType;		//parameter sensitive type : enum NPV_SensitvieType
		int m_wellType;			//parameter well type : enum NPV_WellType
		int m_variableType;		//parameter variable type : enum NPV_VariableType
		bool m_isEconomic;		//parameter mode: economic
		bool m_isBusiness;		//parameter mode: business
		
		//for distribution parameter
		std::string m_disName;
		double m_min;
		double m_max;

		//value each year 
		std::vector <double> m_valueYear;

		//2015/12/1:distribution
		CAnyDistributionStrategy *m_distribution;

		//2015/12/9: for NPV_ActivityRecord
		std::string m_label;
		std::string m_phaseName;
		std::string m_target;
		double m_duration;//year: could be decimal
		double m_wells;
		double m_startDate;
		double m_endDate;
		std::string m_scheduling;
		std::string m_conditions;
		std::string m_stopCondition;
		std::string m_wellUsage;
		int m_wellRepeated;
		std::string m_hctype;
		
		double m_startDuration;
		double m_endDuration;
		std::string m_correlation;//2016/1/12

		/*!
		*
		**/
		NPV_CustomizedRecord() 
		{
			Reset();
		}

		/*!
		*2015/12/1:free distribution
		**/
		~NPV_CustomizedRecord() 
		{
			Release();
		}

		/*!
		*
		**/
		NPV_CustomizedRecord(const NPV_CustomizedRecord &other)
		{
			Reset();
			*this = other;
		}

		/*!
		*
		**/
		const NPV_CustomizedRecord &operator=(const NPV_CustomizedRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_name = other.m_name;
			m_unit = other.m_unit;
			m_value = other.m_value;
			m_phase = other.m_phase;
			m_costType = other.m_costType;
			m_sensiType = other.m_sensiType;
			m_wellType = other.m_wellType;
			m_variableType = other.m_variableType;
			m_isEconomic = other.m_isEconomic;
			m_isBusiness = other.m_isBusiness;

			//
			m_valueYear = other.m_valueYear;
			
			//
			m_disName = other.m_disName;
			m_min = other.m_min;
			m_max = other.m_max;

			//2015/12/1: distribution
			Release();
			if(other.m_distribution)
			{
				m_distribution = CAnyDistributionStrategy::GetDistribution(other.m_distribution->GetName());
				m_distribution->InitSamples(other.m_distribution->GetName(), 0, 0, other.m_distribution->GetParameters());
			}

			//2015/12/9: for NPV_ActivityRecord
			m_label = other.m_label;
			m_phaseName = other.m_phaseName;
			m_target = other.m_target;
			m_duration = other.m_duration;
			m_wells = other.m_wells;
			m_startDate = other.m_startDate;
			m_endDate = other.m_endDate;
			m_scheduling = other.m_scheduling;
			m_conditions = other.m_conditions;
			m_stopCondition = other.m_stopCondition;
			m_wellUsage = other.m_wellUsage;
			m_wellRepeated = other.m_wellRepeated;
			m_hctype = other.m_hctype;

			m_startDuration = other.m_startDuration;
			m_endDuration = other.m_endDuration;
			m_correlation = other.m_correlation;

			return *this;
		}

		//2015/12/1:free distribution
		void Release()
		{
			if (m_distribution)
			{
				delete m_distribution;
			}
			m_distribution = 0;
		}

		/*!
		*
		**/
		void Reset()
		{
			m_name = "";			
			m_unit = "";					
			m_value = 0.;					
			m_phase = NPV_DT_Unknown;					
			m_costType = NPV_CT_Unknown;			
			m_sensiType = NPV_ST_Unknown;		
			m_wellType = NPV_WT_Unknown;		
			m_variableType = NPV_VT_Unknown;	
			m_isEconomic = false;		
			m_isBusiness = false;
			m_disName = "";
			m_min = 0.;
			m_max = 0.;
			m_valueYear.clear();

			m_distribution = 0;

			m_label = "";
			m_phaseName = "";
			m_target = "";
			m_duration = -1.;
			m_wells = -1.;
			m_startDate = 0.;
			m_endDate = 0.;
			m_scheduling = "";
			m_conditions = "";
			m_stopCondition = "";
			m_wellUsage = "";
			m_wellRepeated = 1;
			m_hctype = "";

			m_startDuration = 0.;
			m_endDuration = 0.;
			m_correlation = "";
		}
	};
	typedef std::vector<NPV_CustomizedRecord> NPV_CustomizedRecords;
	typedef NPV_CustomizedRecords::iterator cr_itr;
	typedef NPV_CustomizedRecords::const_iterator cr_citr;

	/*!
	*
	**/
	static bool CompareCustomizedPhase(const NPV_CustomizedRecord &first, const NPV_CustomizedRecord &second)
	{
		return first.m_phase < second.m_phase;
	}

	/*!
	* oil unit record and vector
	**/
	struct NPV_CustomizedOilRecord
	{
		string m_name;			//name
		string m_unit;			//unit
		bool m_isTax;

		double m_value;			//value 
		std::vector <double> m_valueYear;//value each year 
		
		double *m_values;		//cost each year: income *  m_value(m_valueYear)
		int m_valsCount;		//values count	

		CAnyDistributionStrategy *m_distribution;	//distribution

		//added for vat calculation
		string m_parentName;
		double m_vatRate;
		bool m_isReadOnly;

		//
		bool m_isResTax;
		bool m_isCustom;

		/*!
		*
		**/
		NPV_CustomizedOilRecord() 
		{
			Reset();
		}

		/*!
		*
		**/
		NPV_CustomizedOilRecord(const NPV_CustomizedOilRecord &other) 
		{
			Reset();
			*this = other;
		}

		~NPV_CustomizedOilRecord() 
		{
			Release();
		}

		/*!
		*
		**/
		const NPV_CustomizedOilRecord &operator=(const NPV_CustomizedOilRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			Release();

			m_name = other.m_name;
			m_unit = other.m_unit;
			m_value = other.m_value;
			m_valueYear = other.m_valueYear;
			m_isTax = other.m_isTax;
			//m_valsCount = other.m_valsCount;
			
			//
			m_isResTax = other.m_isResTax;
			m_isCustom = other.m_isCustom;
			
			m_valsCount = m_valueYear.size();
			if (m_valsCount)
			{
				//copy values
				m_values =  (double *)::malloc(sizeof(double) * m_valsCount);

				if (other.m_values)
				{
					int i = 0;
					for (;i < m_valsCount; i++)
					{
						m_values[i] =  other.m_values[i];
					}
				}
			}else
			{
				m_values=0;
			}
			
			//
			m_parentName = other.m_parentName;
			m_vatRate = other.m_vatRate;
			m_isReadOnly = other.m_isReadOnly;

			//copy distribution
			if(other.m_distribution)
			{
				m_distribution = CAnyDistributionStrategy::GetDistribution(other.m_distribution->GetName());
				m_distribution->InitSamples(other.m_distribution->GetName(), 0, 0, other.m_distribution->GetParameters());
			}else
			{
				m_distribution=0;
			}

			return *this;
		}

		/*!
		*
		**/
		void Reset()
		{
			m_name = "";
			m_unit = "";

			m_value = 0.;
			m_valueYear.clear();
			
			m_isTax = false;

			m_values = 0; 
			m_valsCount = 0;

			m_distribution = 0;

			m_parentName = "";
			m_vatRate = 0.;
			m_isReadOnly = false;

			m_isResTax = true;
			m_isCustom = false;
		}
		
		/*!
		*
		**/
		void Release()
		{
			if (m_values)
			{
				::free(m_values);
			}
			m_values = 0;

			if (m_distribution)
			{
				delete m_distribution;
			}
			m_distribution = 0;
		}
	};
	typedef std::vector<NPV_CustomizedOilRecord> NPV_CustomizedOilRecords;
	typedef NPV_CustomizedOilRecords::iterator itr;
	typedef NPV_CustomizedOilRecords::const_iterator citr;

	/*!
	* common persistence attributes
	**/
	struct NPV_BasicRecord
	{
		// id, at default it is order when loaded from DB
		long m_practiceIdx;
		long m_elementIdx;

		// record status in memory
		bool m_isUpdated;
		bool m_isDeleted;
		bool m_isAdded;

		/*!
		*
		**/
		NPV_BasicRecord() 
			: m_practiceIdx(-1), m_elementIdx(-1), m_isUpdated(false), m_isDeleted(false), m_isAdded(false)
		{
		}

		/*!
		*
		**/
		virtual ~NPV_BasicRecord()
		{
		}

		//
		//
		//
		/*!
		*
		**/
		virtual int GetFldCount()
		{
			return 0;
		}

		/*!
		*
		**/
		virtual void GetFldValue(int order, string &value)
		{
		}

		/*!
		*
		**/
		virtual void GetFldDescription(int order, string &desc)
		{
		}

		/*!
		*
		**/
		virtual void SetFldValue(int order, string &value)
		{
		}
	};

	/*!
	*
	**/
	struct NPV_PolicyRecord : public NPV_BasicRecord
	{
		// evaluation type
		short m_calculationType; // certainty or uncertainty
		long m_rounds;

		// from this point, begin prev-exploration activities
		long m_startDate;
		// this should be equal the disposal time point
		long m_expirationDate; 

		// kinds of rates
		double m_pi;
		double m_irr;
		double m_discount;
		double m_inflation;
		
		//commodity rates
		double m_oilCommodityRate;
		double m_gasCommodityRate;
		double m_vatRate;

		//ratios
		double m_oil2gasRatio;
		double m_gas2oilRatio;

		//
		int m_oil2gasType;

		// kinds of 
		int m_productionType;
		int m_gasDisposalType;
		double m_screenReserve;
		
		//record rates
		NPV_CustomizedRecords m_records;
		string m_parameters;

		//scenario related
		bool m_isScenarioMode;
		int m_scenarioItrNum;

		//user seed related
		bool m_isUserSeedMode;
		int m_userSeedNum;

		//
		string m_abroadParaStr;

		/*!
		*
		**/
		NPV_PolicyRecord() 
			: m_calculationType(0), m_rounds(1), m_startDate(0), m_expirationDate(0), m_pi(0.), m_irr(0.), m_discount(0.), m_inflation(0.), \
			m_productionType(0), m_gasDisposalType(0), m_screenReserve(5.), m_oilCommodityRate(0.),m_gasCommodityRate(0.),m_vatRate(0.17),\
			m_oil2gasRatio(0.1225),m_gas2oilRatio(0.1225),m_oil2gasType(NPV_Gas2Oil),m_isScenarioMode(false),m_scenarioItrNum(5000),
			m_isUserSeedMode(false),m_userSeedNum(123),m_abroadParaStr(""),m_parameters("")
		{
		}

		/*!
		*
		**/
		void InitRates(int calType = NPV_CAL_Sinopec)
		{
			m_records.clear();

			NPV_CustomizedRecord record;

			if (calType == NPV_CAL_Sinopec)
			{
				record.m_phase = NPV_DT_Exploration;

				record.m_costType = NPV_CT_Expenditure;
				record.m_name = "VAT Rate [%/Yr]";
				record.m_value = 0.17;
				m_records.push_back(record);
			}

			//
			record.m_phase = NPV_DT_Development;

			record.m_costType = NPV_CT_Operation;
			record.m_name = "Oil Commodity Rate [%/Yr]";
			record.m_value = calType == NPV_CAL_Sinopec ? 0.96 : 0.967;
			m_records.push_back(record);

			record.m_costType = NPV_CT_Max;
			record.m_name = "Gas Commodity Rate [%/Yr]";
			record.m_value = calType == NPV_CAL_Sinopec ? 0.96 : 0.0;
			m_records.push_back(record);
		}

		/*!
		*
		**/
		void SetRates(const NPV_CustomizedRecords &records)
		{
			m_records = records;
		}

		/*!
		*
		**/
		const NPV_PolicyRecord &operator=(const NPV_PolicyRecord &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;
			
			// itself
			m_calculationType = other.m_calculationType;
			m_rounds = other.m_rounds;
			m_startDate = other.m_startDate;
			m_expirationDate = other.m_expirationDate;
			m_pi = other.m_pi;
			m_irr = other.m_irr;
			m_discount = other.m_discount;
			m_inflation = other.m_inflation;
			m_productionType = other.m_productionType;
			m_gasDisposalType = other.m_gasDisposalType;
			m_screenReserve = other.m_screenReserve;
			
			//
			m_oilCommodityRate = other.m_oilCommodityRate;
			m_gasCommodityRate = other.m_gasCommodityRate;
			m_vatRate = other.m_vatRate;
			
			//record rates each year
			m_records = other.m_records;
			m_parameters = other.m_parameters;

			//
			m_oil2gasRatio = other.m_oil2gasRatio;
			m_gas2oilRatio = other.m_gas2oilRatio;

			//
			m_isScenarioMode = other.m_isScenarioMode;
			m_scenarioItrNum = other.m_scenarioItrNum;

			m_isUserSeedMode = other.m_isUserSeedMode;
			m_userSeedNum = other.m_userSeedNum;

			//abroad related
			m_abroadParaStr = other.m_abroadParaStr;

			return *this;
		}

		//
		//
		//
		/*!
		*
		**/
		int GetFldCount()
		{
			//
			return 13;
		}

		/*!
		* TODO:
		* direct to position structure member
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_calculationType);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_rounds);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_startDate);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%d", m_expirationDate);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_pi);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_irr);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_discount);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_inflation);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%d", m_productionType);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%d", m_gasDisposalType);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_screenReserve);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_calculationType = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_rounds = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_startDate = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_pi = ::atoi(value.c_str());
			}
			if(order == 6)
			{
				m_expirationDate = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_irr = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_discount = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_inflation = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_productionType = ::atoi(value.c_str());
			}
			if(order == 11)
			{
				m_gasDisposalType = ::atoi(value.c_str());
			}
			if(order == 12)
			{
				m_expirationDate = ::atoi(value.c_str());
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &value)
		{
			if(order == 0)
			{
				value = "";
			}
			if(order == 1)
			{
				value = "";
			}
			if(order == 2)
			{
				value = "Calculation type";
			}
			if(order == 3)
			{
				value = "Iterations of uncertainty evaluation";
			}
			if(order == 4)
			{
				value = "Project start date";
			}
			if(order == 5)
			{
				value = "Probability index";
			}
			if(order == 6)
			{
				value = "Expiration date";
			}
			if(order == 7)
			{
				value = "Inner revenue rate";
			}
			if(order == 8)
			{
				value = "Discount rate";
			}
			if(order == 9)
			{
				value = "Inflate rate";
			}
			if(order == 10)
			{
				value = "HC production policy";
			}
			if(order == 11)
			{
				value = "Gas disposal";
			}
			if(order == 12)
			{
				value = "Screen reserve";
			}
		}
	};

	/*!
	*
	**/
	struct NPV_RiskRecord : public NPV_BasicRecord
	{
		double m_marginal;
		double m_conditional;
		double m_unconditional;
		double m_dryrisk;

		/*!
		*
		**/
		NPV_RiskRecord() : m_marginal(0.), m_conditional(0.), m_unconditional(0.), m_dryrisk(0.)
		{
		}

		/*!
		*
		**/
		const NPV_RiskRecord &operator=(const NPV_RiskRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			// itself
			m_marginal = other.m_marginal;
			m_conditional = other.m_conditional;
			m_unconditional = other.m_unconditional;
			m_dryrisk = other.m_dryrisk;

			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 6;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%f", m_marginal);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_conditional);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_unconditional);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_dryrisk);
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
			if(order == 0)
			{
				desc = "";
			}
			if(order == 1)
			{
				desc = "";
			}
			if(order == 2)
			{
				desc = "Marginal probability";
			}
			if(order == 3)
			{
				desc = "Conditional probability";
			}
			if(order == 4)
			{
				desc = "Un-conditional probability";
			}
			if(order == 5)
			{
				desc = "Dry hole risk";
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_marginal = ::atof(value.c_str());
			}
			if(order == 3)
			{
				m_conditional = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_unconditional = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_dryrisk = ::atof(value.c_str());
			}
		}
	};

	/*!
	*
	**/
	struct NPV_ResourceRecord : public NPV_BasicRecord
	{
		// resource type or id
		long m_type;
		double m_reserve;

		double m_gasReserve;

		// for undeterministice
		CAnyDistributionStrategy *m_oilDistribution;
		CAnyDistributionStrategy *m_gasDistribution;

		//zhihao:2013/8/8 variables for loading history
		long m_oilPracticeId;
		long m_gasPracticeId;

		short m_oilActivityType;
		short m_gasActivityType;

		/*!
		*
		**/
		NPV_ResourceRecord() : m_type(NPV_RT_Unknown),m_reserve(0.),m_gasReserve(0.),\
			m_oilDistribution(0),m_gasDistribution(0),\
			m_oilPracticeId(-1),m_gasPracticeId(-1),\
			m_oilActivityType(0),m_gasActivityType(0)	
		{
		}

		/*!
		*
		**/
		~NPV_ResourceRecord()
		{
			if(m_oilDistribution)
			{
				delete m_oilDistribution;
			}
			m_oilDistribution = 0;

			//
			if(m_gasDistribution)
			{
				delete m_gasDistribution;
			}
			m_gasDistribution = 0;
		}

		/*!
		*
		**/
		NPV_ResourceRecord &operator=(const NPV_ResourceRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			// itself
			m_type = other.m_type;
			m_reserve = other.m_reserve;

			//
			m_gasReserve = other.m_gasReserve;

			//
			m_oilPracticeId = other.m_oilPracticeId;
			m_gasPracticeId = other.m_gasPracticeId;

			m_oilActivityType = other.m_oilActivityType;
			m_gasActivityType = other.m_gasActivityType;
			
			if(m_oilDistribution)
			{
				delete m_oilDistribution;
			}
			m_oilDistribution = 0;
			if(other.m_oilDistribution)
			{
				m_oilDistribution = CAnyDistributionStrategy::GetDistribution(other.m_oilDistribution->GetName().c_str());
				m_oilDistribution->InitSamples(other.m_oilDistribution->GetName(), 0, 0, other.m_oilDistribution->GetParameters());
			}

			//
			if(m_gasDistribution)
			{
				delete m_gasDistribution;
			}
			m_gasDistribution = 0;
			if(other.m_gasDistribution)
			{
				m_gasDistribution = CAnyDistributionStrategy::GetDistribution(other.m_gasDistribution->GetName().c_str());
				m_gasDistribution->InitSamples(other.m_gasDistribution->GetName(), other.m_gasDistribution->GetSamples(), other.m_gasDistribution->GetSampleSize(), other.m_gasDistribution->GetParameters());
			}
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 4;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_type);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_reserve);
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
			if(order == 0)
			{
				desc = "";
			}
			if(order == 1)
			{
				desc = "";
			}
			if(order == 2)
			{
				desc = "Resource type";
			}
			if(order == 3)
			{
				desc = "Resource reserve";
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_type = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_reserve = ::atof(value.c_str());
			}
		}
	};

	/*!
	*
	**/
	struct NPV_EDP_BasicRecord : public NPV_BasicRecord
	{
		long m_expPrevDuration;
		long m_expPrevWellNumber;
		long m_expDuration;
		long m_expWellNumber;				// total number and not differenciate resource types
		long m_expAppDuration;
		long m_expAppWellNumber;		// total number
		long m_devAppDuration;
		long m_devAppWellNumber;
		long m_devDuration;
		long m_devWellNumber;				// total number
		long m_prodBuildup;
		long m_prodPlateau;
		long m_prodDecline;
		long m_prodDisposal;
		long m_prodWellNumber;			// total well number
		long m_prodInjectionNumber;     // total injection number
		double m_plateauProduceRatio;
		long m_declineType;
		double m_declineRate;
		double m_declineIndex;

		std::string m_declineCustomFormula;

		//for prospect version
		double m_oilProScale;
		double m_oilDecRate;
		double m_gasProScale;
		double m_gasDecRate;

		//
		std::vector<string> m_oilFormulas;
		std::vector<string> m_gasFormulas;
		string m_oilFormulaStr;
		string m_gasFormulaStr;

		//abroad
		string m_abroadParaStr;

		/*!
		*
		**/
		NPV_EDP_BasicRecord() : m_expPrevDuration(0), m_expPrevWellNumber(0), m_expDuration(0), m_expWellNumber(0), m_expAppDuration(0), m_expAppWellNumber(0), 
			m_devAppDuration(0), m_devAppWellNumber(0), m_devDuration(0), m_devWellNumber(0), 
			m_prodBuildup(0), m_prodPlateau(0), m_prodDecline(0), m_prodDisposal(0), m_prodWellNumber(0), m_prodInjectionNumber(0),
			m_plateauProduceRatio(0.), m_declineType(NPV_EDT_Exponent), m_declineRate(0),m_declineIndex(0.5),m_declineCustomFormula(""),\
			m_oilProScale(1.),m_oilDecRate(0.07), m_gasProScale(1.),m_gasDecRate(0.07),m_abroadParaStr(""),m_oilFormulaStr(""),m_gasFormulaStr("")
		{
		}

		/*!
		*
		**/
		const NPV_EDP_BasicRecord &operator=(const NPV_EDP_BasicRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			// itself
			m_expPrevDuration = other.m_expPrevDuration;
			m_expPrevWellNumber = other.m_expPrevWellNumber;
			m_expDuration = other.m_expDuration;
			m_expWellNumber = other.m_expWellNumber;
			m_expAppDuration = other.m_expAppDuration;
			m_expAppWellNumber = other.m_expAppWellNumber;
			m_devDuration = other.m_devDuration;
			m_devWellNumber = other.m_devWellNumber;
			m_prodBuildup = other.m_prodBuildup;
			m_prodPlateau = other.m_prodPlateau;
			m_prodDecline = other.m_prodDecline;
			m_prodDisposal = other.m_prodDisposal;
			m_prodWellNumber = other.m_prodWellNumber;
			m_prodInjectionNumber = other.m_prodInjectionNumber;
			m_plateauProduceRatio = other.m_plateauProduceRatio;
			m_declineType = other.m_declineType;
			m_declineRate = other.m_declineRate;
			m_declineIndex = other.m_declineIndex;

			m_declineCustomFormula = other.m_declineCustomFormula;

			m_oilProScale = other.m_oilProScale;
			m_oilDecRate = other.m_oilDecRate;
			m_gasProScale = other.m_gasProScale;
			m_gasDecRate = other.m_gasDecRate;

			//
			m_abroadParaStr = other.m_abroadParaStr;

			//
			m_oilFormulas = other.m_oilFormulas;
			m_gasFormulas = other.m_gasFormulas;
			m_oilFormulaStr = other.m_oilFormulaStr;
			m_gasFormulaStr = other.m_gasFormulaStr;

			//
			return *this;
		}

		/*!
		*
		**/
		void SetProspectFormulas(int duration)
		{
			m_oilFormulas.clear();
			m_gasFormulas.clear();

			//
			string formula = "production-scale / 2";
			m_oilFormulas.push_back(formula);
			m_gasFormulas.push_back(formula);

			formula = "production-scale";
			m_oilFormulas.push_back(formula);
			m_gasFormulas.push_back(formula);

			int j = 2;
			for (;j<duration;j++)
			{
				formula = "previous-reserve * (1-decline-rate)";
				m_oilFormulas.push_back(formula);
				m_gasFormulas.push_back(formula);
			}
		}

		/*!
		*
		**/
		int GetFldCount(bool isProspect = false)
		{
			if (!isProspect)
			{
				return 23;
			}

			return 23 + 4/*prodcution scale, decline rate*/;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_expPrevDuration);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_expPrevWellNumber);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_expDuration);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%d", m_expWellNumber);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%d", m_expAppDuration);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%d", m_expAppWellNumber);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%d", m_devAppDuration);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%d", m_devAppWellNumber);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%d", m_devDuration);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%d", m_devWellNumber);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%d", m_prodBuildup);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%d", m_prodPlateau);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%d", m_prodDecline);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%d", m_prodDisposal);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%d", m_prodWellNumber);
			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%d", m_prodInjectionNumber);
			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_plateauProduceRatio);
			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%d", m_declineType);
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_declineRate);
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_declineIndex);
			}
			if(order == 22)
			{
				value = m_declineCustomFormula;
			}
		}

		/*!
		*
		**/
		void GetFldDesc(int order, string &desc, bool isProspect = false)
		{
			if(order == 0)
			{
				desc = "";
			}
			if(order == 1)
			{
				desc = "";
			}
			if(order == 2)
			{
				desc = "Duration of pre-exploration activities";
			}
			if(order == 3)
			{
				desc = "Well number during pre-exploration";
			}
			if(order == 4)
			{
				desc = "Duration of exploration drilling";
			}
			if(order == 5)
			{
				desc = "Number of exploration wells";
			}
			if(order == 6)
			{
				desc = "Duration of appraisal drilling";
			}
			if(order == 7)
			{
				desc = "Number of appraisal wells";
			}
			if(order == 8)
			{
				desc = "Duration of development approval";
			}
			if(order == 9)
			{
				desc = "Well number during development approval";
			}
			if(order == 10)
			{
				desc = "Duration of development";
			}
			if(order == 11)
			{
				desc = "Well number during development";
			}
			if(order == 12)
			{
				desc = "Time for production buildup";
			}
			if(order == 13)
			{
				desc = "Time for production plateau";
			}
			if(order == 14)
			{
				desc = "Time for production decline";
			}
			if(order == 15)
			{
				desc = "Time for production disposal";
			}
			if(order == 16)
			{
				desc = "Well number during production";
			}
			if(order == 17)
			{
				desc = "Injection number during production";
			}
			if(order == 18)
			{
				desc = "Ratio between production and reserves in plateau";
			}
			if(order == 19)
			{
				desc = "Decline type of Production";
			}
			if(order == 20)
			{
				desc = "Decline fraction";
			}
			if(order == 21)
			{
				desc = "Decline Index";
			}
			if(order == 22)
			{
				desc = "Custom Decline Formula";
			}

			if (isProspect)
			{
				if(order == 23)
				{
					desc = "Construction Scale(Oil)";
				}
				if(order == 24)
				{
					desc = "Decline Rate(Oil)";
				}
				if(order == 25)
				{
					desc = "Construction Scale(Gas)";
				}
				if(order == 26)
				{
					desc = "Decline Rate(Gas)";
				}
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_expPrevDuration = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_expPrevWellNumber = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_expDuration = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_expWellNumber = ::atoi(value.c_str());
			}
			if(order == 6)
			{
				m_expAppDuration = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_expAppWellNumber = ::atoi(value.c_str());
			}
			if(order == 8)
			{
				m_devAppDuration = ::atoi(value.c_str());
			}
			if(order == 9)
			{
				m_devAppWellNumber = ::atoi(value.c_str());
			}
			if(order == 10)
			{
				m_devDuration = ::atoi(value.c_str());
			}
			if(order == 11)
			{
				m_devWellNumber = ::atoi(value.c_str());
			}
			if(order == 12)
			{
				m_prodBuildup = ::atoi(value.c_str());
			}
			if(order == 13)
			{
				m_prodPlateau = ::atoi(value.c_str());
			}
			if(order == 14)
			{
				m_prodDecline = ::atoi(value.c_str());
			}
			if(order == 15)
			{
				m_prodDisposal = ::atoi(value.c_str());
			}
			if(order == 16)
			{
				m_prodWellNumber = ::atoi(value.c_str());
			}
			if(order == 17)
			{
				m_prodInjectionNumber = ::atoi(value.c_str());
			}
			if(order == 18)
			{
				m_plateauProduceRatio = ::atof(value.c_str());
			}
			if(order == 19)
			{
				m_declineType = ::atoi(value.c_str());
			}
			if(order == 20)
			{
				m_declineRate = ::atof(value.c_str());
			}
			if(order == 21)
			{
				m_declineIndex = ::atof(value.c_str());
			}
			if(order == 22)
			{
				m_declineCustomFormula = value;
			}
		}
	};

	/*!
	*
	**/
	struct NPV_EDP_ScheduleRecord : public NPV_BasicRecord
	{
		// resource type
		int m_type;
		// which year
		long m_year;
		// reserve
		double m_reserve;
		// drilling number
		int m_drillingNumber;
		// injection rate
		int m_injectionNumber;

		//abroad
		string m_abroadParaStr;

		/*!
		*
		**/
		NPV_EDP_ScheduleRecord() : m_type(NPV_RT_Unknown), m_year(0), m_reserve(0.), m_drillingNumber(0), m_injectionNumber(0.),m_abroadParaStr("")
		{
		}

		/*!
		*
		**/
		const NPV_EDP_ScheduleRecord &operator=(NPV_EDP_ScheduleRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// resource type
			m_type = other.m_type;
			// which year
			m_year = other.m_year;
			// reserve
			m_reserve = other.m_reserve;
			// drilling number
			m_drillingNumber = other.m_drillingNumber;
			// injection number
			m_injectionNumber = other.m_injectionNumber;

			//
			m_abroadParaStr = other.m_abroadParaStr;

			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 7;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_type);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_year);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_reserve);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%d", m_drillingNumber);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%d", m_injectionNumber);
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
			if(order == 0)
			{
				desc = "";
			}
			if(order == 1)
			{
				desc = "";
			}
			if(order == 2)
			{
				desc = "Resource type";
			}
			if(order == 3)
			{
				desc = "Year";
			}
			if(order == 4)
			{
				desc = "Reserve";
			}
			if(order == 5)
			{
				desc = "Drilling number per year";
			}
			if(order == 6)
			{
				desc = "Injection number per year";
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_type = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_year = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_reserve = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_drillingNumber = ::atoi(value.c_str());
			}
			if(order == 6)
			{
				m_injectionNumber = ::atof(value.c_str());
			}
		}
	};
	
	/*!
	*
	**/
	struct NPV_Cost_BasicRecord : public NPV_BasicRecord
	{		
		NPV_CustomizedRecords m_records;

		//record parameters in m_records, and store them into db
		string m_parameters;

		CAnyDistributionStrategy **m_distributions;

		NPV_WellCostRecord m_expWellCost;
		NPV_WellCostRecord m_devWellCost;

		//
		std::vector<NPV_WellCostRecord> m_expWellCosts;
		std::vector<NPV_WellCostRecord> m_devWellCosts;
		string m_expWellCostStr;
		string m_devWellCostStr;

		//abroad
		string m_abroadParaStr;
		string m_abroadSolutionStr;
		
		/*!
		*
		**/
		NPV_Cost_BasicRecord(bool isInitRecords = false, bool isSinopec = true, bool isProspect = false) : m_parameters(""),\
			m_abroadParaStr(""),m_abroadSolutionStr(""),m_expWellCostStr(""),m_devWellCostStr("")
		{
			if (isInitRecords)
			{
				NPV_CustomizedRecord record;

				record.m_unit = "[10^4 RMB]";
				//record.m_unit = "[1e6 USD]";
				record.m_value = 0.;
				record.m_isEconomic = false;
				record.m_isBusiness = false;
				record.m_costType = NPV_CT_Expenditure;
				record.m_sensiType = NPV_ST_Fixed_Cost;

				if (isSinopec)
				{
					//exploration
					record.m_phase = NPV_DT_Exploration;

					if (!isProspect)
					{
						AddRecord(record,"Geological and geophysical cost of exploration",0.);

						//2015/3/19: well cost is not in Prospect mode
						record.m_wellType = NPV_WT_Drilling;
						AddRecord(record,"Well costs of Exploration",6120.);
						record.m_wellType = NPV_WT_Unknown;
					}					

					//zhihao: 2013/06/18 differentiate well exploration from others
					/*record.m_wellType = NPV_WT_Drilling;
					AddRecord(record,"Well costs of Exploration",6120.);
					record.m_wellType = NPV_WT_Unknown;*/

					AddRecord(record,"Investment costs of Exploration",!isProspect ? 1917.:6120.);

					//development
					record.m_phase = NPV_DT_Development;
					AddRecord(record,"Investment costs of Development",!isProspect ? 8070.:10712.4);
					
					if (!isProspect)
					{	
						//2015/6/24:Surface invest
						record.m_phase = NPV_DT_Development;
						AddRecord(record,"Surface Engineering Investment",0.);

						//disposal
						record.m_phase = NPV_DT_Disposal;
						AddRecord(record,"The recovery of Residue value of the fixed assets",0.);
						AddRecord(record,"The recovery of Current fund",0.);
					}	
				}
				else
				{
					//pre-exploration
					record.m_phase = NPV_DT_Exploration_Previous;
					AddRecord(record,"Rentals of pre-exploration activities",0./*0.2*/);
					AddRecord(record,"Other cost of pre-exploration activities",0./*0.1*/);
					
					///////////////////////////exploration/////////////////////////////////////
					record.m_phase = NPV_DT_Exploration;
					AddRecord(record,"Geological and geophysical cost of exploration",0./*2*/);
					
					//zhihao: 2014/03/05 differentiate well exploration from others
					record.m_wellType = NPV_WT_Drilling;
					AddRecord(record,"Well costs of Exploration",0./*50.*/);
					record.m_wellType = NPV_WT_Unknown;

					AddRecord(record,"Other cost of exploration",0./*1*/);
					///////////////////////////exploration/////////////////////////////////////					

					//exploration appraisal
					record.m_phase = NPV_DT_Exploration_Apprasial;
					AddRecord(record,"Geological and geophysical cost of exploration appraisal",0./*4*/);
					AddRecord(record,"Other cost of exploration appraisal",0./*2*/);

					//development appraisal
					record.m_phase = NPV_DT_Development_Appraisal;
					AddRecord(record,"Plan cost of development appraisal",0./*2*/);
					AddRecord(record,"Other cost of development appraisal",0./*1*/);
					
					//development
					record.m_phase = NPV_DT_Development;
					AddRecord(record,"Plan cost of development",0./*4*/);
					AddRecord(record,"Other cost of development",0./*2*/);
					AddRecord(record,"Construction scalar in development",0./*1*/);

					//production buildup
					record.m_phase = NPV_DT_Production_Buildup;
					AddRecord(record,"Construction scalar in buildup",0./*0.5*/);
					
					record.m_costType = NPV_CT_Expenditure;
					record.m_sensiType = NPV_ST_Fixed_Cost;
					AddRecord(record,"Facility fixed cost in buildup",0./*20*/);
					AddRecord(record,"Transportation facility fixed cost in buildup",0./*40*/);
									
					record.m_costType = NPV_CT_Operation;
					AddRecord(record,"Operating fixed cost in buildup",0./*5*/);
					AddRecord(record,"Fixed transportation cost in buildup",0./*10*/);
					
					//production plateau
					record.m_phase = NPV_DT_Production_Plateau;
					record.m_costType = NPV_CT_Expenditure;
					AddRecord(record,"Facility fixed cost in plateau",0./*30*/);
					AddRecord(record,"Transportation facility fixed cost in plateau",0./*20*/);

					record.m_costType = NPV_CT_Operation;
					AddRecord(record,"Operating fixed cost in plateau",0./*20*/);
					AddRecord(record,"Fixed transportation cost in plateau",0./*50*/);

					//production decline
					record.m_phase = NPV_DT_Production_Decline;
					record.m_costType = NPV_CT_Expenditure;
					AddRecord(record,"Facility fixed cost in decline",0./*10*/);
					AddRecord(record,"Transportation facility fixed cost in decline",0./*10*/);
					
					record.m_costType = NPV_CT_Operation;
					AddRecord(record,"Operating fixed cost in decline",0./*10*/);
					AddRecord(record,"Fixed transportation cost in decline",0./*50*/);

					//disposal
					record.m_sensiType = NPV_ST_Other_Capex;
					record.m_phase = NPV_DT_Disposal;
					AddRecord(record,"Decommission cost",0./*5*/);
				}
			}

			m_distributions = 0;
		}

		NPV_Cost_BasicRecord(const NPV_CustomizedRecords &records) : m_parameters(""),m_abroadParaStr(""),m_abroadSolutionStr(""),\
			m_expWellCostStr(""),m_devWellCostStr("")
		{
			m_records = records;
			
			m_distributions = (CAnyDistributionStrategy **)::malloc(GetFldCount() * sizeof(CAnyDistributionStrategy *));
			::memset(m_distributions, 0x00, GetFldCount() * sizeof(CAnyDistributionStrategy *));
		}

		/*!
		*
		**/
		~NPV_Cost_BasicRecord()
		{
			Release();
		}

		/*!
		*
		**/
		void Release()
		{
			if(m_distributions)
			{
				int i = 0;
				for(; i < GetFldCount(); i++)
				{
					if(m_distributions[i])
					{
						delete m_distributions[i];
					}
					m_distributions[i] = 0;
				}
				::free(m_distributions);
				m_distributions = 0;
			}
		}

		/*!
		*
		**/
		void PopulateDistribution(double *quantiles,double quantile = -1.)
		{
			int count = m_records.size();
			
			int i=0;
			for (;i<count;i++)
			{
				if (!m_distributions[i])
				{
					continue;
				}

				if (quantile == -1.)
				{
					m_records[i].m_value = m_distributions[i]->GetQuantile(quantiles[i]);
				}
				else
				{
					if (quantile == 0.5)
					{
						m_records[i].m_value = m_distributions[i]->GetStatistics().m_mode < m_distributions[i]->GetQuantile(0.9)?\
							m_distributions[i]->GetQuantile(0.5) : m_distributions[i]->GetStatistics().m_mode;
					}
					else
					{
						m_records[i].m_value = m_distributions[i]->GetQuantile(quantile);
					}
				}
			}
		}

		/*!
		*
		**/
		void AddRecord(NPV_CustomizedRecord &record, const string name, double val, int num = 0)
		{
			record.m_name = name;
			record.m_value = val;
			
			record.m_valueYear.clear();
			while (num)
			{
				record.m_valueYear.push_back(record.m_value);
				num--;
			}
			m_records.push_back(record);
		};

		/*!
		*
		**/
		const NPV_Cost_BasicRecord &operator=(const NPV_Cost_BasicRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// release current distributions
			Release();

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			//itself
			m_records = other.m_records;
			m_parameters = other.m_parameters;

			m_distributions = (CAnyDistributionStrategy **)::malloc(GetFldCount() * sizeof(CAnyDistributionStrategy *));
			::memset(m_distributions, 0x00, GetFldCount() * sizeof(CAnyDistributionStrategy *));
			int i = 0;
			for(; i < GetFldCount(); i++)
			{
				if(other.m_distributions[i])
				{
					m_distributions[i] = CAnyDistributionStrategy::GetDistribution(other.m_distributions[i]->GetName());
					m_distributions[i]->InitSamples(other.m_distributions[i]->GetName(), 0, 0, other.m_distributions[i]->GetParameters());
				}
			}

			//
			m_abroadParaStr = other.m_abroadParaStr;
			m_abroadSolutionStr = other.m_abroadSolutionStr;
			
			//
			m_expWellCost = other.m_expWellCost;
			m_devWellCost = other.m_devWellCost;

			//
			m_expWellCosts = other.m_expWellCosts;
			m_devWellCosts = other.m_devWellCosts;
			m_expWellCostStr = other.m_expWellCostStr;
			m_devWellCostStr = other.m_devWellCostStr;

			//
			return *this;
		}
		
		/*!
		*
		**/
		int GetFldCount()
		{
			//return 27;
			return m_records.size() + 2;			
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			//customized
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else //2 or plus
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					::sprintf((char*)value.c_str(),"%f",m_records[order].m_value);
				}
			}
		}

		/*!
		*
		*/
		void GetFldDescription(int order, string &desc)
		{
			//customized
			if(order == 0)
			{
				desc = "";
			}
			else if(order == 1)
			{
				desc = "";
			}
			else// 2 or plus 
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					desc = m_records[order].m_name;
				}
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			//customized
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else// 2 or plus 
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					m_records[order].m_value = ::atof(value.c_str());
				}
			}
		}
	};

	/*!
	*
	**/
	struct NPV_Cost_DetailRecord : public NPV_BasicRecord
	{
		NPV_CustomizedRecords m_records;

		//record parameters in m_records, and store them into db
		string m_parameters;

		// resource type
		int m_type;

		// kinds of distributions
		CAnyDistributionStrategy **m_distributions;

		/*!
		*
		**/
		NPV_Cost_DetailRecord(bool isInitRecords = false, bool isSinopec = true) : m_type(NPV_RT_Unknown),m_parameters("")
		{
			if (isInitRecords)
			{
				NPV_CustomizedRecord record;

				//record.m_unit = "[1e6 USD]";
				record.m_unit = "[10^4 RMB]";
				record.m_value = 0.;
				record.m_isEconomic = false;
				record.m_isBusiness = false;
				record.m_phase = NPV_DT_Unknown;

				//type
				record.m_phase = -1;
				record.m_name = "Resource type";
				record.m_value = NPV_RT_Unknown;
				m_records.push_back(record);

				//exploration
				record.m_wellType = NPV_WT_Drilling;
				record.m_sensiType = NPV_ST_Drilling_Expense;
				record.m_phase = NPV_DT_Exploration;
				record.m_name = "Per well cost of Exploration";
				record.m_value = 0/*10*/;
				
				if (!isSinopec)
				{
					record.m_value = 0/*10*/;
				}
				m_records.push_back(record);

				record.m_phase = NPV_DT_Exploration_Apprasial;
				record.m_name = "Per well cost of Appraisal";
				record.m_value = 0/*8*/;
				if (!isSinopec)
				{
					record.m_value = 0/*8*/;
				}
				m_records.push_back(record);

				//development
				record.m_phase = NPV_DT_Development;
				record.m_name = "Per well cost of Development";
				record.m_value = 0/*5*/;
				if (!isSinopec)
				{
					record.m_value = 0/*5*/;
				}
				m_records.push_back(record);

				record.m_name = "Per injection cost of Development";
				record.m_wellType = NPV_WT_Injection;
				record.m_value = 0/*2*/;
				if (!isSinopec)
				{
					record.m_value = 0/*2*/;
				}
				m_records.push_back(record);

				//production
				record.m_phase = NPV_DT_Production_Buildup;
				record.m_name = "Per well cost of Production";
				record.m_wellType = NPV_WT_Drilling;
				record.m_value = 0/*2*/;
				if (!isSinopec)
				{
					record.m_value = 0/*2*/;
				}
				m_records.push_back(record);

				record.m_name = "Per injection cost of Production";
				record.m_wellType = NPV_WT_Injection;
				record.m_value = 0/*1*/;
				if (!isSinopec)
				{
					record.m_value = 0/*1*/;
				}
				m_records.push_back(record);

				record.m_wellType = NPV_WT_Unknown;
				record.m_sensiType = NPV_ST_Variable_Cost;

				record.m_name = "Per facility cost of production plateau";
				record.m_variableType = NPV_VT_Facility;
				record.m_value = 0/*5*/;
				if (!isSinopec)
				{
					record.m_value = 0/*5*/;
				}
				m_records.push_back(record);

				record.m_name = "Per facility of transportation of production plateau";
				record.m_variableType = NPV_VT_Facility_Transportation;
				record.m_value = 0/*5*/;
				if (!isSinopec)
				{
					record.m_value = 0/*5*/;
				}
				m_records.push_back(record);

				record.m_name = "Per operation cost of production plateau";
				record.m_variableType = NPV_VT_Operation;
				record.m_value = 0/*5*/;
				if (!isSinopec)
				{
					record.m_value = 0/*5*/;
				}
				m_records.push_back(record);

				record.m_name = "Per transportation cost of production plateau";
				record.m_variableType = NPV_VT_Transportation;
				record.m_value = 0/*5*/;
				if (!isSinopec)
				{
					record.m_value = 0/*5*/;
				}
				m_records.push_back(record);
			}

			m_distributions = 0;
		}

		/*!
		*
		**/
		NPV_Cost_DetailRecord(const NPV_CustomizedRecords &records) : m_type(NPV_RT_Unknown), m_parameters("")
		{
			m_records = records;
			
			m_distributions = (CAnyDistributionStrategy **)::malloc(GetFldCount() * sizeof(CAnyDistributionStrategy *));
			::memset(m_distributions, 0x00, GetFldCount() * sizeof(CAnyDistributionStrategy *));
		}

		/*!
		*
		**/
		~NPV_Cost_DetailRecord()
		{
			Release();
		}

		/*!
		*
		**/
		const NPV_Cost_DetailRecord &operator=(const NPV_Cost_DetailRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			//
			Release();

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			//itself
			m_records = other.m_records;
			m_parameters = other.m_parameters;

			//
			m_type = other.m_type;
			
			m_distributions = (CAnyDistributionStrategy **)::malloc(GetFldCount() * sizeof(CAnyDistributionStrategy *));
			::memset(m_distributions, 0x00, GetFldCount() * sizeof(CAnyDistributionStrategy *));
			int i = 0;
			for(; i < GetFldCount(); i++)
			{
				if(other.m_distributions[i])
				{
					m_distributions[i] = CAnyDistributionStrategy::GetDistribution(other.m_distributions[i]->GetName());
					m_distributions[i]->InitSamples(other.m_distributions[i]->GetName(), 0, 0, other.m_distributions[i]->GetParameters());
				}
			}

			return *this;
		}

		/*!
		*
		**/
		void Release()
		{
			if(m_distributions)
			{
				int i = 0;
				for(; i < GetFldCount(); i++)
				{
					if(m_distributions[i])
					{
						delete m_distributions[i];
					}
					m_distributions[i] = 0;
				}
				::free(m_distributions);
				m_distributions = 0;
			}
		}

		/*!
		*
		**/
		void PopulateDistribution(double *quantiles, double quantile = -1.)
		{
			int count = m_records.size();

			int i=1;
			for (;i<count;i++)
			{
				//without 0:resource type
				if (!m_distributions[i-1])
				{
					continue;
				}

				if (quantile == -1.)
				{
					m_records[i].m_value = m_distributions[i-1]->GetQuantile(quantiles[i-1]);
				}
				else
				{
					if (quantile == 0.5)
					{
						m_records[i].m_value = m_distributions[i-1]->GetStatistics().m_mode < m_distributions[i-1]->GetQuantile(0.9)?\
							m_distributions[i-1]->GetQuantile(0.5) : m_distributions[i-1]->GetStatistics().m_mode;
					}
					else
					{
						m_records[i].m_value = m_distributions[i-1]->GetQuantile(quantile);
					}
				}
			}
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			//return 13;
			return m_records.size() + 2;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			//customized
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_type);
			}
			else//3 or plus
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					::sprintf((char*)value.c_str(),"%f",m_records[order].m_value);
				}
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
			//customized
			if(order == 0)
			{
				desc = "";
			}
			else if(order == 1)
			{
				desc = "";
			}
			else// 2 or plus 
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					desc = m_records[order].m_name;
				}
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			//customized
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_type = ::atoi(value.c_str());
			}
			else// 3 or plus 
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					m_records[order].m_value = ::atof(value.c_str());
				}
			}
		}
	};

	/*!
	*
	**/
	struct NPV_Cost_OilRecord : public NPV_BasicRecord
	{		
		NPV_CustomizedOilRecords m_records;

		//record parameters in m_records, and store them into db
		string m_parameters;

		//abroad
		string m_abroadParaStr;
		string m_abroadSolutionStr;

		//
		int m_type;

		/*!
		*
		**/
		NPV_Cost_OilRecord(int initType = NPV_COT_Default, int num = 0) : m_parameters(""),m_abroadParaStr(""),m_abroadSolutionStr(""),m_type(0)
		{
			Init(initType,num);
		}

		NPV_Cost_OilRecord(const NPV_CustomizedOilRecords &records) : m_parameters(""),m_abroadParaStr(""),m_abroadSolutionStr(""),m_type(0)
		{
			Init(records);
		}

		~NPV_Cost_OilRecord()
		{
			Release();
		}

		/*!
		*
		**/
		const NPV_Cost_OilRecord &operator=(const NPV_Cost_OilRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			//itself
			Release();
			m_records = other.m_records;
			m_parameters = other.m_parameters;			

			//
			m_abroadParaStr = other.m_abroadParaStr;
			m_abroadSolutionStr = other.m_abroadSolutionStr;
			m_type = other.m_type;

			//
			return *this;
		}

		/*!
		*
		**/
		void Init(int type, int num, bool isProspect = false)
		{
			if (type == NPV_COT_Default)
			{
				return;
			}

			NPV_CustomizedOilRecord record;
			record.m_unit = "[RMB/Ton]";
			record.m_isTax = false;
			
			//
			record.m_parentName = "";
			
			if (type == NPV_COT_Simple)
			{
				record.m_isReadOnly = false;
			}
			else
			{
				record.m_isReadOnly = true;
			}

			AddRecord(record, "Operation Cost", num, !isProspect?1500 : 750);
						
			//sub items for operation cost
			record.m_isReadOnly = false;
			if (type == NPV_COT_Key_Element)
			{
				record.m_parentName = record.m_name;
				
				//
				AddRecord(record, "Raw Material Cost", num, 200, 1);
				AddRecord(record, "Fuel Cost", num, 200, 1);
				AddRecord(record, "Power Cost", num, 100, 1);

				AddRecord(record, "Salary and Welfare Cost", num, 100, 0);

				//
				AddRecord(record, "Oil Extraction Cost", num, 100, 0.3);
				AddRecord(record, "Downhole Operation Cost", num, 100, 0.3);
				AddRecord(record, "Well Logging Cost", num, 100, 0.3);

				//
				AddRecord(record, "Maintenance Cost", num, 100, 0.5);
				AddRecord(record, "Heavy Oil Exploiting Cost", num, 100, 0.5);
				AddRecord(record, "Light Hydrocarbon Disposal Cost", num, 100, 0.5);

				//
				AddRecord(record, "Oil and Gas Disposal Cost", num, 100, 0.3);

				//
				AddRecord(record, "Transportation Cost", num, 100, 0);
				AddRecord(record, "Manufacturing Cost", num, 100, 0);
				AddRecord(record, "Other Direct Cost", num, 0, 0);
				AddRecord(record, "Production Safety Cost", num, 0, 0);
			}
			else if (type == NPV_COT_Production_Procedure)
			{
				record.m_parentName = record.m_name;

				AddRecord(record, "Oil and Gas Promotion Direct Cost", num, 300, 0);
				AddRecord(record, "Oil Extraction Direct Cost", num, 200, 0);
				AddRecord(record, "Downhole Operation Cost", num, 200, 0);
				AddRecord(record, "Well Logging Cost", num, 100, 0);
				AddRecord(record, "Light Hydrocarbon Disposal Direct Cost", num, 100, 0);
				AddRecord(record, "Heavy Oil Exploiting Direct Cost", num, 100, 0);
				AddRecord(record, "Oil and Gas Disposal Direct Cost", num, 100, 0);
				AddRecord(record, "Oil and Gas Transportation Cost", num, 100, 0);
				AddRecord(record, "Oil Region Maintenance Cost", num, 100, 0);
				AddRecord(record, "Manufacturing Cost", num, 100, 0);
				AddRecord(record, "Other Direct Cost", num, 100, 0);
			}

			//
			record.m_isReadOnly = false;
			record.m_parentName = "";

			AddRecord(record, "Management Cost", num, !isProspect?250 : 100);

			if (type == NPV_COT_Simple)
			{
				if (!isProspect)
				{
					AddRecord(record, "Other Cost", num, 50);
				}
			}
			else
			{
				//Financial Cost
				AddRecord(record,"Financial Cost",num,30,-1);
				AddRecord(record,"Sales Cost",num,20);
				AddRecord(record,"Exploration Cost",num, 0, -1);
			}
			
			//
			record.m_isTax = true;
			AddRecord(record, "Special Gain Levy", num, !isProspect? 180 : 82);
		}

		/*!
		*
		**/
		void AddRecord(NPV_CustomizedOilRecord &record, const string name, int num, double val, double vatRate = 0.)
		{
			record.m_name = name;
			record.m_value = val;
			record.m_vatRate = vatRate;

			record.m_valueYear.clear();
			while (num)
			{
				record.m_valueYear.push_back(record.m_value);
				num--;
			}
			m_records.push_back(record);
		};

		/*!
		*
		**/
		void Init(const NPV_CustomizedOilRecords &records)
		{
			Release();
			m_records = records;
		}

		/*!
		*
		**/
		void Release(bool isMallocMem = false, int num = 0)
		{
			int count = m_records.size();

			int i=0;
			for (;i<count;i++)
			{
				m_records[i].Release();

				if (isMallocMem)
				{
					m_records[i].m_values =  (double *)::malloc(sizeof(double) * num);
					::memset(m_records[i].m_values, 0x00, sizeof(double) * num);
				}
			}
			//m_records.clear();
		}

		/*!
		*
		**/
		void PopulateDistribution(double *quantiles)
		{
			int count = m_records.size();
			
			int i=0;
			for (;i<count;i++)
			{
				m_records[i].m_value = m_records[i].m_distribution->GetQuantile(quantiles[i]);
			}
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return m_records.size() + 2;			
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			//customized
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else //2 or plus
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					::sprintf((char*)value.c_str(),"%f",m_records[order].m_value);
				}
			}
		}

		/*!
		*
		*/
		void GetFldDescription(int order, string &desc)
		{
			//customized
			if(order == 0)
			{
				desc = "";
			}
			else if(order == 1)
			{
				desc = "";
			}
			else// 2 or plus 
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					desc = m_records[order].m_name;
				}
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			//customized
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else// 2 or plus 
			{
				order -= 2;
				if (order>=0 && order<m_records.size())
				{
					m_records[order].m_value = ::atof(value.c_str());
				}
			}
		}
	};

	/*!
	*
	**/
	struct NPV_PriceRecord : public NPV_BasicRecord
	{
		// which year
		long m_year;
		// resource type
		long m_type;
		//
		double m_price;
		double m_inflation;

		//2015/6/24:allowance for well mode
		double m_oilAllowance;
		double m_gasAllowance;

		//abroad
		string m_abroadParaStr;
		string m_abroadSolutionStr;

		/*!
		*
		**/
		NPV_PriceRecord() : m_year(0), m_type(0), m_price(0.), m_inflation(0.),m_abroadParaStr(""),m_abroadSolutionStr(""),\
			m_oilAllowance(0.),m_gasAllowance(0.)
		{
		}

		/*!
		*
		**/
		const NPV_PriceRecord &operator=(const NPV_PriceRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			
			// itself
			m_year = other.m_year;
			m_type = other.m_type;
			m_price = other.m_price;
			m_inflation = other.m_inflation;

			//
			m_abroadParaStr = other.m_abroadParaStr;
			m_abroadSolutionStr = other.m_abroadSolutionStr;

			//
			m_oilAllowance = other.m_oilAllowance;
			m_gasAllowance = other.m_gasAllowance;

			//
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 6;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_year);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_type);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_price);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_inflation);
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
			if(order == 0)
			{
				desc = "";
			}
			if(order == 1)
			{
				desc = "";
			}
			if(order == 2)
			{
				desc = "Year";
			}
			if(order == 3)
			{
				desc = "Resource type";
			}
			if(order == 4)
			{
				desc = "Price";
			}
			if(order == 5)
			{
				desc = "Inflation";
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_year = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_type = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_price = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_inflation = ::atof(value.c_str());
			}
		}
	};

	/*!
	*
	**/
	struct NPV_TaxRecord : public NPV_BasicRecord
	{
		//
		NPV_CustomizedOilRecords m_records;
		string m_parameters;
		
		// resource type
		int m_type;

		// which year
		int m_year;
		double m_incomeTax;
		double m_oilRevenueTax;
		double m_gasRevenueTax;

		//
		double m_resTax;
		double m_consEduTax;

		//abroad cost
		string m_abroadParaStr;
		//2014/10/16:save solutions of cost
		string m_abroadSolutionStr;

		/*!
		*
		**/
		NPV_TaxRecord(int num = 0, bool isProspect = false) : m_type(NPV_RT_Unknown), m_year(0), m_incomeTax(0.), m_oilRevenueTax(0.), m_gasRevenueTax(0.),\
			m_resTax(0.038),m_consEduTax(0.015),m_parameters(""),m_abroadParaStr("") ,m_abroadSolutionStr("")
		{
			Init(num, isProspect);
		}

		/*!
		*
		**/
		NPV_TaxRecord(const NPV_CustomizedOilRecords &records) : m_type(NPV_RT_Unknown), m_year(0), m_incomeTax(0.), m_oilRevenueTax(0.), m_gasRevenueTax(0.),\
			m_resTax(0.038),m_consEduTax(0.015),m_parameters(""),m_abroadParaStr("") ,m_abroadSolutionStr("")
		{
			Init(records);
		}

		~NPV_TaxRecord()
		{
			Release();
		}

		/*!
		*
		**/
		const NPV_TaxRecord &operator=(const NPV_TaxRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			// itself
			m_type = other.m_type;
			m_year = other.m_year;
			m_incomeTax = other.m_incomeTax;
			m_oilRevenueTax = other.m_oilRevenueTax;
			m_gasRevenueTax = other.m_gasRevenueTax;
			m_resTax = other.m_resTax;
			m_consEduTax = other.m_consEduTax;

			Release();
			m_records = other.m_records;
			m_parameters = other.m_parameters;	

			//
			m_abroadParaStr = other.m_abroadParaStr;
			m_abroadSolutionStr = other.m_abroadSolutionStr;
			//
			return *this;
		}

		/*!
		*
		**/
		void Init(int num, bool isProspect = false)
		{
			NPV_CustomizedOilRecord record;

			//for sales tax cost
			record.m_isCustom = false;
			record.m_unit = "%";
			record.m_isTax = false;

			//resource tax
			record.m_isResTax = true;
			AddRecord(record, "Resource Tax", num, !isProspect ? 0.038 : 0.04);
			
			//element method
			record.m_isReadOnly = false;
			record.m_isResTax = false;
			AddRecord(record, "City Construction Tax", num, 0.07/*0.15*/);
			
			//
			AddRecord(record, "Educational Surtax", num, 0.03);

			//parameter for simple method
			record.m_isReadOnly = true;
			AddRecord(record, "City Construction Tax and Educational Surtax", num, !isProspect ? 0.015 : 0.012);

			//for calculating after tax
			record.m_isTax = true;
			AddRecord(record, "Local Income Tax", num, 0.25);
		}

		/*!
		*
		**/
		void AddRecord(NPV_CustomizedOilRecord &record, const string name, int num, double val)
		{
			record.m_valueYear.clear();
			record.m_name = name;
			record.m_value = val;

			while (num)
			{
				record.m_valueYear.push_back(record.m_value);
				num--;
			}

			m_records.push_back(record);
		}

		/*!
		*
		**/
		void Init(const NPV_CustomizedOilRecords &records)
		{
			Release();
			m_records = records;
			//ReleaseOilRecords(records);
		}

		/*!
		*
		**/
		void Release(bool isMallocMem = false, int num = 0)
		{
			int count = m_records.size();

			int i=0;
			for (;i<count;i++)
			{
				m_records[i].Release();

				if (isMallocMem)
				{
					m_records[i].m_values =  (double *)::malloc(sizeof(double) * num);
					::memset(m_records[i].m_values, 0x00, sizeof(double) * num);
				}
			}
		}

		/*!
		*
		**/
		void PopulateDistribution(double *quantiles)
		{
			int count = m_records.size();
			
			int i=0;
			for (;i<count;i++)
			{
				m_records[i].m_value = m_records[i].m_distribution->GetQuantile(quantiles[i]);
			}
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 7;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_type);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_year);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_incomeTax);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilRevenueTax);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_gasRevenueTax);
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
			if(order == 0)
			{
				desc = "";
			}
			if(order == 1)
			{
				desc = "";
			}
			if(order == 2)
			{
				desc = "Resource type";
			}
			if(order == 3)
			{
				desc = "Year";
			}
			if(order == 4)
			{
				desc = "Income tax";
			}
			if(order == 5)
			{
				desc = "Oil revenue tax";
			}
			if(order == 6)
			{
				desc = "Gas revenue tax";
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_type = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_year = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_incomeTax = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_oilRevenueTax = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_gasRevenueTax = ::atof(value.c_str());
			}
		}
	};

	/*!
	*
	**/
	struct NPV_SummaryRecord : public NPV_BasicRecord
	{
		double m_discountRate;
		double m_npv;
		double m_irr;

		NPV_CustomizedRecords m_records;

		//abroad
		string m_abroadParaStr;
		string m_sipcParaStr;

		//2014/10/16
		string m_costRecoverParaStr;
		string m_pscParaStr;

		/*!
		*
		**/
		NPV_SummaryRecord(bool isInitialized = false, bool isProspect = false) : \
			m_discountRate(0.), m_npv(0.), m_irr(0.),m_abroadParaStr(""),m_sipcParaStr(""),m_costRecoverParaStr(""),m_pscParaStr("")
		{
			if (isInitialized)
			{
				NPV_CustomizedRecord record;

				if (!isProspect)
				{
					//cash inflow
					record.m_phase = 0;
					record.m_costType = 0;
					record.m_name = "Cash Inflow";
					m_records.push_back(record);

					record.m_costType = 1;
					record.m_name = "Sales Income";
					m_records.push_back(record);

					record.m_name = "The recovery of Residue value of the fixed assets";
					m_records.push_back(record);

					record.m_name = "The recovery of Current fund";
					m_records.push_back(record);

					//cash outflow
					record.m_phase = 1;
					record.m_costType = 0;
					record.m_name = "Cash Outflow";
					m_records.push_back(record);

					record.m_costType = 1;
					record.m_name = "Exploration Investment";
					m_records.push_back(record);

					record.m_name = "Development Investment";
					m_records.push_back(record);

					record.m_name = "Current Fund";
					m_records.push_back(record);

					record.m_name = "Operation Cost ";
					m_records.push_back(record);

					record.m_name = "Sales Tax and Plus";
					m_records.push_back(record);

					//pretax NPV
					record.m_phase = 2;
					record.m_costType = 0;
					record.m_name = "Pretax NPV/Year";
					m_records.push_back(record);

					record.m_name = "Pretax NPV/Accumulative Total";
					m_records.push_back(record);

					//after tax NPV
					record.m_phase = 3;
					record.m_costType = 0;

					record.m_name = "Tax Adjustment";
					m_records.push_back(record);

					record.m_name = "After Tax NPV/Year";
					m_records.push_back(record);

					record.m_name = "After Tax NPV/Accumulative Total";
					m_records.push_back(record);

					//measures
					record.m_phase = 4;
					record.m_costType = 0;

					record.m_name = "Pre Tax FIRR (%)";
					m_records.push_back(record);

					record.m_name = "After Tax FIRR (%)";
					m_records.push_back(record);

					record.m_name = "Pre Tax FNPV";
					m_records.push_back(record);

					record.m_name = "After Tax FNPV";
					m_records.push_back(record);

					//
					record.m_phase = 5;
					record.m_costType = 0;

					record.m_name = "Pc Reserve (Oil)";
					m_records.push_back(record);

					record.m_name = "Pe Reserve (Oil)";
					m_records.push_back(record);

					record.m_name = "Pc Reserve (Gas)";
					m_records.push_back(record);

					record.m_name = "Pe Reserve (Gas)";
					m_records.push_back(record);

					record.m_name = "Pc (Oil) (%)";
					m_records.push_back(record);

					record.m_name = "Pe (Oil) (%)";
					m_records.push_back(record);

					record.m_name = "Pc (Gas) (%)";
					m_records.push_back(record);

					record.m_name = "Pe (Gas) (%)";
					m_records.push_back(record);

					record.m_name = "EMV";
					m_records.push_back(record);

					//
					record.m_name = "Risk Value";
					m_records.push_back(record);
				}
				else
				{
					//cash inflow
					record.m_phase = 0;
					record.m_costType = 0;
					record.m_name = "Cash Inflow";
					m_records.push_back(record);

					record.m_costType = 1;
					record.m_name = "Sales Income";
					m_records.push_back(record);
					
					//cash outflow
					record.m_phase = 1;
					record.m_costType = 0;
					record.m_name = "Cash Outflow";
					m_records.push_back(record);

					record.m_costType = 1;
					record.m_name = "Exploration and Development Investment";
					m_records.push_back(record);

					//financial
					record.m_name = "Operation Cost ";
					m_records.push_back(record);

					record.m_name = "Full Cost";
					m_records.push_back(record);

					record.m_name = "Depreciation";
					m_records.push_back(record);

					//caozuo
					record.m_name = "Operation Cost";
					m_records.push_back(record);

					//
					record.m_name = "Period Expense";
					m_records.push_back(record);

					//
					record.m_name = "Sales Tax and Plus";
					m_records.push_back(record);

					record.m_name = "Resource Tax";
					m_records.push_back(record);

					record.m_name = "City Construction and Educational Expense";
					m_records.push_back(record);
					
					record.m_name = "Special Gain Levy";
					m_records.push_back(record);

					//pretax NPV
					record.m_phase = 2;
					record.m_costType = 0;
					record.m_name = "Pretax NPV/Year";
					m_records.push_back(record);

					//after tax NPV
					record.m_phase = 3;
					record.m_costType = 0;

					record.m_name = "Income Tax";
					m_records.push_back(record);

					record.m_name = "Taxable Income";
					m_records.push_back(record);

					record.m_name = "After Tax NPV/Year";
					m_records.push_back(record);
					
					//measures
					record.m_phase = 4;
					record.m_costType = 0;

					record.m_name = "Pre Tax FIRR (%)";
					m_records.push_back(record);

					record.m_name = "After Tax FIRR (%)";
					m_records.push_back(record);

					record.m_name = "Pre Tax FNPV";
					m_records.push_back(record);

					record.m_name = "After Tax FNPV";
					m_records.push_back(record);

					//
					record.m_phase = 5;
					record.m_costType = 0;

					record.m_name = "Pc Reserve (Oil)";
					m_records.push_back(record);

					record.m_name = "Pe Reserve (Oil)";
					m_records.push_back(record);

					record.m_name = "Pc Reserve (Gas)";
					m_records.push_back(record);

					record.m_name = "Pe Reserve (Gas)";
					m_records.push_back(record);

					record.m_name = "Pc (Oil) (%)";
					m_records.push_back(record);

					record.m_name = "Pe (Oil) (%)";
					m_records.push_back(record);

					record.m_name = "Pc (Gas) (%)";
					m_records.push_back(record);

					record.m_name = "Pe (Gas) (%)";
					m_records.push_back(record);

					record.m_name = "EMV";
					m_records.push_back(record);

					//
					record.m_name = "Risk Value";
					m_records.push_back(record);
				}				
			}
		}

		/*!
		*
		**/
		const NPV_SummaryRecord &operator=(const NPV_SummaryRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			// itself
			m_discountRate = other.m_discountRate;
			m_npv = other.m_npv;
			m_irr = other.m_irr;
			m_records = other.m_records;

			//
			m_abroadParaStr = other.m_abroadParaStr;
			m_sipcParaStr = other.m_sipcParaStr;

			//2014/10/16
			m_costRecoverParaStr = other.m_costRecoverParaStr;
			m_pscParaStr = other.m_pscParaStr;

			//
			return *this;
		}
		
		/*!
		*
		**/
		int GetFldCount()
		{
			return 5;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_practiceIdx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%f", m_discountRate);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_npv);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_irr);
			}
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
			if(order == 0)
			{
				desc = "";
			}
			if(order == 1)
			{
				desc = "";
			}
			if(order == 2)
			{
				desc = "Discount rate ";
			}
			if(order == 3)
			{
				desc = "NPV ";
			}
			if(order == 4)
			{
				desc = "IRRS";
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_practiceIdx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_discountRate = ::atof(value.c_str());
			}
			if(order == 3)
			{
				m_npv = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_irr = ::atof(value.c_str());
			}
		}
	};

	/*!
	*
	**/
	struct NPV_ScenarioRecord : public NPV_BasicRecord
	{
		//record parameters in m_records, and store them into db
		NPV_CustomizedRecords m_records;
		string m_parameters;

		NPV_CustomizedRecords m_resultRecords;
		string m_resultParameters;
		
		//
		double m_expCost;
		double m_devCost;
		double m_oilRes;
		double m_gasRes;
		double m_npvTax;

		/*!
		*
		**/
		NPV_ScenarioRecord() : m_parameters(""), m_resultParameters(""),\
			m_expCost(0.),m_devCost(0.),m_oilRes(0.),m_gasRes(0.),m_npvTax(0.)
		{
		}

		NPV_ScenarioRecord(const NPV_CustomizedRecords &records) : m_parameters(""), m_resultParameters(""),\
			m_expCost(0.),m_devCost(0.),m_oilRes(0.),m_gasRes(0.),m_npvTax(0.)
		{
			m_records = records;
		}

		~NPV_ScenarioRecord()
		{
			
		}

		/*!
		*
		**/
		const NPV_ScenarioRecord &operator=(const NPV_ScenarioRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			
			// itself
			m_parameters = other.m_parameters;
			m_records = other.m_records;

			//newly added
			m_resultParameters = other.m_resultParameters;
			m_resultRecords = other.m_resultRecords;

			//
			m_expCost = other.m_expCost;
			m_devCost = other.m_devCost;
			m_oilRes = other.m_oilRes;
			m_gasRes = other.m_gasRes;
			m_npvTax = other.m_npvTax;

			return *this;
		}

		/*!
		*
		**/
		void SetResultRecords(const NPV_CustomizedRecords &records)
		{
			m_resultRecords = records;
		}

		/*!
		*
		**/
		void Init(int num)
		{
			m_records.clear();

			NPV_CustomizedRecord record;
			
			//price
			AddRecord(record, 0, 0, 0.1, num, 2830.,1280.);
			AddRecord(record, 0, 1, 0.9, num, 3000.,1500.);

			//reserve
			AddRecord(record, 1, 0, 0.1, num, 10.,1.);
			AddRecord(record, 1, 1, 0.9, num, 15.,1.5);

			//risk
			AddRecord(record, 2, 0, 0.1, num, 0.75, 0.75);
			AddRecord(record, 2, 1, 0.9, num, 0.9, 0.9);
		}

		/*!
		*
		**/
		void AddRecord(NPV_CustomizedRecord &record, short nodeType, short branchType, double probability, int num, double val1,double val2)
		{
			record.m_costType = nodeType;//price\reserve\risk
			record.m_phase = branchType;//low
			record.m_value = probability;//probability

			record.m_valueYear.clear();
			
			int count = (val1 == val2)? num: 2*num;

			while (count)
			{
				if (count <= num)
				{
					record.m_valueYear.push_back(val2);
				}
				else
				{
					record.m_valueYear.push_back(val1);
				}
				count--;
			}

			m_records.push_back(record);
		}

		/*!
		*
		**/
		void AddRecord(NPV_CustomizedRecord &record, short nodeType, short branchType, double probability, std::vector<double> &vec)
		{
			record.m_costType = nodeType;//price\reserve\risk
			record.m_phase = branchType;//low
			record.m_value = probability;//probability

			record.m_valueYear.clear();
			record.m_valueYear = vec;
			m_records.push_back(record);
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 1;
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
		}

		/*!
		*
		**/
		void GetFldDescription(int order, string &desc)
		{
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
		}
	};

	/*!
	*2015/11/30
	**/
	struct NPV_ActivityRecord : public NPV_BasicRecord
	{		
		std::vector<NPV_CustomizedRecords> m_records;
		string m_parameters;//record parameters in m_records, and store them into db
		
		NPV_CustomizedRecords m_templateRecords;

		/*!
		*
		**/
		NPV_ActivityRecord() : m_parameters("")
		{
			NPV_CustomizedRecord record;
			record.m_wellType = NPV_WT_Unknown;
			record.m_sensiType = NPV_ST_Unknown;

			//pre-exploration
			record.m_phase = NPV_DT_Exploration_Previous;
			AddRecord(record,"Duration [Yr]",0.8);
			AddRecord(record,"Other cost [MM USD]",16.);
			AddRecord(record,"G&A cost [MM USD/Yr]",1.25);

			//2016/1/13: directly set correlation
			record.m_costType = NPV_CT_Expenditure;
			AddRecord(record,"Duration to cost correlation",0.);
			record.m_costType = NPV_CT_Unknown;

			///////////////////////////exploration/////////////////////////////////////
			record.m_phase = NPV_DT_Exploration;
			AddRecord(record,"Duration [Yr]",1.);
			AddRecord(record,"Number of wells",1.);
			AddRecord(record,"Drilling cost per well [MM USD]",11.);
			AddRecord(record,"Completion cost per well [MM USD]",9.);
			AddRecord(record,"Other cost [MM USD]",7.);
			AddRecord(record,"G&A cost [MM USD/Yr]",2.5);
			
			//2016/1/13: directly set correlation
			record.m_costType = NPV_CT_Expenditure;
			AddRecord(record,"Duration to cost correlation",0.);
			record.m_costType = NPV_CT_Unknown;

			///////////////////////////appraisal/////////////////////////////////////
			record.m_phase = NPV_DT_Exploration_Apprasial;
			AddRecord(record,"Duration [Yr]",1.);
			AddRecord(record,"Number of wells",1.);
			AddRecord(record,"Drilling cost per well [MM USD]",11.);
			AddRecord(record,"Completion cost per well [MM USD]",9.);
			AddRecord(record,"Other cost [MM USD]",3.5);
			AddRecord(record,"G&A cost [MM USD/Yr]",2.5);
			
			//2016/1/13: directly set correlation
			record.m_costType = NPV_CT_Expenditure;
			AddRecord(record,"Duration to cost correlation",0.);
			record.m_costType = NPV_CT_Unknown;

			///////////////////////////development/////////////////////////////////////		
			record.m_phase = NPV_DT_Development;
			AddRecord(record,"Duration [Yr]",3.);
			AddRecord(record,"Fixed development cost [MM USD]",750.);
			AddRecord(record,"Fixed operation cost [MM USD/Yr]",25.);
			AddRecord(record,"G&A cost [MM USD/Yr]",5.);
			AddRecord(record,"Repeated investments [MM USD]",0.);
			AddRecord(record,"Max capacity [K Sm3/Day]",0.);
			AddRecord(record,"Development cost per unit peak [USD/Sm3]",13.);
			AddRecord(record,"Variable operating cost [USD/Sm3]",12.);
			
			//2016/1/11: directly set parameter: CAPEX distribution
			record.m_costType = NPV_CT_Expenditure;
			AddRecord(record,"Use development CAPEX distribution across phases (with field-based production modeling)",0.);
			AddRecord(record,"Development",1.);
			AddRecord(record,"Production buildup",0.);
			AddRecord(record,"Plateau production",0.);
			AddRecord(record,"Use cost distribution for development",0.);
			AddRecord(record,"Duration to cost correlation",0.);//2016/1/13: directly set correlation
			record.m_costType = NPV_CT_Unknown;
			
			///////////////////////////field based production/////////////////////////////////////
			record.m_phase = NPV_DT_Production_Buildup;
			AddRecord(record,"Fraction HC produced yearly at plateau [decimal]",0.11);
			AddRecord(record,"Fraction remaining HC at EOP [decimal]",0.35);
			AddRecord(record,"Minimum joint well capacity main phase [Sm3/Day]",1000.);
			AddRecord(record,"Delay to first repeated investments [Yr]",0.);
			AddRecord(record,"Interval between repeated investments [Yr]",0.);

			//directly set parameter: general
			record.m_costType = NPV_CT_Expenditure;
			AddRecord(record,"Drilling policy",1.);
			AddRecord(record,"Associated gas usage",2.);
			AddRecord(record,"Fraction pre-drilled wells",0.15);
			AddRecord(record,"Hydrocarbon quality index",1.0);
			AddRecord(record,"Learning index",0.);
			
			//directly set parameter: rig
			AddRecord(record,"Cost of operating rig per year [MM USD/Yr]",0.0);
			AddRecord(record,"Numbers of rigs per year",1.);
			
			//directly set parameter: well decline type
			AddRecord(record,"Decline type",0.);

			//directly set parameter: well drilling sequence
			AddRecord(record,"Repeated sequence if need",1.);
			
			//2016/1/13: directly set correlation
			AddRecord(record,"Duration to cost correlation",0.);

			//directly set parameter: well types
			record.m_wellUsage = "Producer";
			AddRecord(record,"Default producer",0.);
						
			record.m_wellUsage = "Injector";
			AddRecord(record,"Default injector",0.);
						
			record.m_wellUsage = "";
			record.m_costType = NPV_CT_Unknown;

			//field based production - drilling well parameters
			record.m_wellType = NPV_WT_Drilling;
			AddRecord(record,"Drilling Duration [Yr]",0.5);
			AddRecord(record,"Unit cost [MM USD]",7.);
			AddRecord(record,"Operation cost [MM USD/Yr]",0.45);
			AddRecord(record,"Peak well rate [K Sm3/Day]",1.37);
			AddRecord(record,"Well plateau factor [decimal]",0.);
			
			//field based production - drilling well parameters - decline type
			record.m_sensiType = NPV_ST_Fixed_Cost;//exponential
			AddRecord(record,"Effective decline rate",0.181);

			record.m_sensiType = NPV_ST_Other_Capex;//hyperbolic
			AddRecord(record,"Hyperbolic exponent",0.);

			record.m_sensiType = NPV_ST_Drilling_Expense;//Linear WC
			AddRecord(record,"Fraction remaining at end production [decimal]",0.);
			AddRecord(record,"Fraction remaining hydrocarbon at start water production [decimal]",0.7);
			AddRecord(record,"Water Cut at end production [decimal]",0.9);
			AddRecord(record,"Water Cut at start water production [decimal]",0.);

			record.m_sensiType = NPV_ST_Variable_Cost;//Logarithmic WOR
			AddRecord(record,"Fraction remaining at end production [decimal]",0.);
			AddRecord(record,"Fraction remaining hydrocarbon at start water production [decimal]",0.7);
			AddRecord(record,"Water Oil Ratio at end production [decimal]",9.);
			AddRecord(record,"Water Oil Ratio at start water production [decimal]",0.05);

			record.m_sensiType = NPV_ST_Max;//custom
			AddRecord(record,"custom",0.2);

			//field based production - injection well parameters
			record.m_sensiType = NPV_ST_Unknown;
			record.m_wellType = NPV_WT_Injection;
			AddRecord(record,"Drilling Duration [Yr]",0.25);
			AddRecord(record,"Unit cost [MM USD]",0.35);
			AddRecord(record,"Operation cost [MM USD/Yr]",0.25);
			record.m_wellType = NPV_WT_Unknown;

			///////////////////////////well based production/////////////////////////////////////
			record.m_phase = NPV_DT_Production_Plateau;
			AddRecord(record,"Minimum joint well capacity main phase [Sm3/Day]",1000.);
			AddRecord(record,"Delay to first repeated investments [Yr]",0.);
			AddRecord(record,"Interval between repeated investments [Yr]",0.);
			
			//directly set parameter: general
			record.m_costType = NPV_CT_Expenditure;
			AddRecord(record,"Drilling policy",1.);
			AddRecord(record,"Associated gas usage",2.);
			AddRecord(record,"Fraction pre-drilled wells",0.15);
			AddRecord(record,"Hydrocarbon quality index",1.0);
			AddRecord(record,"Learning index",0.);

			//directly set parameter: rig
			AddRecord(record,"Cost of operating rig per year [MM USD/Yr]",0.0);
			AddRecord(record,"Numbers of rigs per year",1.);

			//directly set parameter: well decline type
			AddRecord(record,"Decline type",0.);

			//directly set parameter: well drilling sequence
			AddRecord(record,"Repeated sequence if need",1.);

			//2016/1/13: directly set correlation
			AddRecord(record,"Duration to cost correlation",0.);

			//directly set parameter: well types
			record.m_wellUsage = "Producer";
			AddRecord(record,"Default producer",0.);

			record.m_wellUsage = "Injector";
			AddRecord(record,"Default injector",0.);

			record.m_wellUsage = "";
			record.m_costType = NPV_CT_Unknown;

			//well based production - well parameters
			record.m_wellType = NPV_WT_Drilling;
			AddRecord(record,"Drilling Duration [Yr]",0.5);
			AddRecord(record,"Start production delay [Yr]",0.);
			AddRecord(record,"Unit cost [MM USD]",7.);
			AddRecord(record,"Operation cost [MM USD/Yr]",0.45);
			AddRecord(record,"Peak well rate [K Sm3/Day]",1.37);
			AddRecord(record,"Estimated Ultimate Recovery (EUR) per well [MM Sm3]",1.);
			AddRecord(record,"Well plateau factor [decimal]",0.);
			
			//well based production - well parameters - decline type
			record.m_sensiType = NPV_ST_Fixed_Cost;//exponential
			AddRecord(record,"Effective decline rate",0.181);

			record.m_sensiType = NPV_ST_Other_Capex;//hyperbolic
			AddRecord(record,"Abandonment well rate [K Sm3/Day]",0.);
			AddRecord(record,"Hyperbolic exponent",0.);
			
			record.m_sensiType = NPV_ST_Drilling_Expense;//Linear WC
			AddRecord(record,"Fraction remaining at end production [decimal]",0.);
			AddRecord(record,"Fraction remaining hydrocarbon at start water production [decimal]",0.7);
			AddRecord(record,"Water Cut at end production [decimal]",0.9);
			AddRecord(record,"Water Cut at start water production [decimal]",0.);

			record.m_sensiType = NPV_ST_Variable_Cost;//Logarithmic WOR
			AddRecord(record,"Fraction remaining at end production [decimal]",0.);
			AddRecord(record,"Fraction remaining hydrocarbon at start water production [decimal]",0.7);
			AddRecord(record,"Water Oil Ratio at end production [decimal]",9.);
			AddRecord(record,"Water Oil Ratio at start water production [decimal]",0.05);

			record.m_sensiType = NPV_ST_Max;//custom
			AddRecord(record,"custom",0.2);
			
			//well based production - injection well parameters
			record.m_sensiType = NPV_ST_Unknown;
			record.m_wellType = NPV_WT_Injection;
			AddRecord(record,"Drilling Duration [Yr]",0.25);
			AddRecord(record,"Unit cost [MM USD]",0.35);
			AddRecord(record,"Operation cost [MM USD/Yr]",0.25);
			record.m_wellType = NPV_WT_Unknown;
			
			///////////////////////////disposal/////////////////////////////////////
			record.m_phase = NPV_DT_Disposal;
			AddRecord(record,"Duration [Yr]",0.5);
			AddRecord(record,"Fraction abandonment cost [Decimal]",0.1);

			record.m_costType = NPV_CT_Expenditure;
			AddRecord(record,"Linked development activities",0.);//2016/1/11: directly set parameter: CAPEX distribution
			AddRecord(record,"Duration to cost correlation",0.);//2016/1/13: directly set correlation
			record.m_costType = NPV_CT_Unknown;
		}

		NPV_ActivityRecord(const NPV_CustomizedRecords &records) : m_parameters("")
		{
			m_templateRecords = records;
		}

		/*!
		*
		**/
		~NPV_ActivityRecord()
		{
			
		}

		/*!
		*
		**/
		void PopulateDistribution(double quantile)
		{
			int count = m_templateRecords.size();
			
			int i=0;
			for (;i<count;i++)
			{
				if (!m_templateRecords[i].m_distribution)
				{
					continue;
				}

				if (quantile == 0.5)
				{
					m_templateRecords[i].m_value = m_templateRecords[i].m_distribution->GetStatistics().m_mode < m_templateRecords[i].m_distribution->GetQuantile(0.9)?\
						m_templateRecords[i].m_distribution->GetQuantile(0.5) : m_templateRecords[i].m_distribution->GetStatistics().m_mode;
				}
				else
				{
					m_templateRecords[i].m_value = m_templateRecords[i].m_distribution->GetQuantile(quantile);
				}
			}
		}

		/*!
		*
		**/
		void AddRecord(NPV_CustomizedRecord &record, const string name, double val, int num = 0)
		{
			record.m_name = name;
			record.m_value = val;
			
			record.m_valueYear.clear();
			while (num)
			{
				record.m_valueYear.push_back(record.m_value);
				num--;
			}
			m_templateRecords.push_back(record);
		};

		/*!
		*
		**/
		const NPV_ActivityRecord &operator=(const NPV_ActivityRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_practiceIdx = other.m_practiceIdx;
			m_elementIdx = other.m_elementIdx;
			m_isAdded = other.m_isAdded;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;

			//itself
			m_templateRecords = other.m_templateRecords;
			m_parameters = other.m_parameters;

			//
			return *this;
		}
		
		/*!
		*
		**/
		int GetFldCount()
		{
			return m_templateRecords.size();			
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{			
		}

		/*!
		*
		*/
		void GetFldDescription(int order, string &desc)
		{			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{			
		}

		/*!
		*
		**/
		void GetParameters(NPV_CustomizedRecords &records, int phase, bool isDefaultData = true)
		{
			int count = m_templateRecords.size();

			int i = 0;
			for (; i < count; i++)
			{
				if (m_templateRecords[i].m_phase == phase)
				{
					records.push_back(m_templateRecords[i]);

					//set the value equals 0
					if (!isDefaultData)
					{
						records[records.size()-1].m_value = 0.;
					}
				}
			}
		}
	};
}
#endif