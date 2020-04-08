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
#ifndef __ANYPETRO_ACCUMULATION_PROPERTY_RECORD_H__
#define __ANYPETRO_ACCUMULATION_PROPERTY_RECORD_H__

// refer to reference type
#include "propertyreferencerecord.h"
#include "any/base/agm/reflection.hpp"
using namespace agm::reflection;



namespace AnyPetro
{
	/*!
	*
	**/
	enum PropertyRecordType
	{
		PRT_Unknown,//0
		PRT_Basic,//1
		PRT_Overall, //2
		PRT_Geology,//3
		PRT_Source,//4
		PRT_Reservoir,//5
		PRT_Cap,//6
		PRT_Preservation,//7
		PRT_Exploration,//8
		PRT_Segment,//9
		PRT_Trap,//10
		PRT_Trap_Exploration,//11
		PRT_Trap_Project,//12
		PRT_Trap_Repositpory,//13
		PRT_Pool,//14
		PRT_Volume,//15
		PRT_Volume_Para,//16
		PRT_WellVariable,//17
		PRT_Trap_Develop,//18
		PRT_Survey,//19
		PRT_Survey_Check,//20
		PRT_Seismic_Deploy,//21
		PRT_Seismic_Pic,//22
		PRT_Shale_WellBasic,//23
		PRT_Shale_WellProduction,//24
		PRT_Shale_Bore,//25
		PRT_Shale_Vol,//26
		PRT_Shale_WellVariable,//27
		PRT_Shale_PlayAnalogOverAll,//28
		PRT_Shale_TargetAnalogOverAll,//29
		PRT_Shale_WellAnalogOverAll,//30
		PRT_Block_Basinbasic,// 31
		PRT_Block_PrimarystructBasic,// 32
		PRT_Block_SecondStructBasic,// 33
		PRT_Block_ThirdStructBasic,// 34
		PRT_Block_BlockBasic,// 35
		PRT_Block_BlockExpDegree,// 36
		PRT_Block_Pics,//37
		PRT_Mlr_ResourceResults,//38
		PRT_Mlr_Calibrated,//39
		PRT_ELE_Resource,//40
		PRT_ELE_Resource_shale,//41

		PRT_Performance_WellBasic,
		PRT_Performance_Deployment,
		PRT_Performance_DeploymentCasing,
		PRT_Performance_DeploymentTubing,
		PRT_Performance_Deploymenttrajectory,
		PRT_Performance_GeologicalPara,
		PRT_Performance_Pressure,
		PRT_Performance_PressureGradient,
		PRT_Performance_Production,
		PRT_Performance_Practice,
		PRT_Performance_DreResult,
		PRT_Performance_DreMiddle,

		PRT_Shale_WellGeochemicalPara,

		//2016/7/20: trap related table
		PRT_Trap_Geology_Fault,
		PRT_Trap_Survey,
		PRT_Trap_Wildcat_Well,
		PRT_Trap_Post,
		PRT_Trap_Drill,

		PRT_OverSea_Project,

		PRT_Max//
	};

	// inner struct
	struct ProbabilityField
	{
		long m_idx;
		string m_parameter;

		/*!
		*
		**/
		ProbabilityField() : m_idx(0), m_parameter("")
		{
		}

		/*!
		*
		**/
		const ProbabilityField &operator=(const ProbabilityField &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_idx = other.m_idx;
			m_parameter = other.m_parameter;

			return *this;
		}
	};

	/*!
	* common persistence attributes
	**/
	struct PropertyRecord
	{
		// id, at default it is order when lodded from DB
		CLASS(PropertyRecord, agm::reflection::NullClass);
		//long m_idx;
		//long m_elementIdx;
		FIELD2(public,long, m_idx);
		FIELD2(public,long, m_elementIdx);
		// record status in memory
		bool m_isUpdated;
		bool m_isDeleted;
		bool m_isAdded;
		
		//
		bool IsDirty()
		{
			return false;
		}

		//
		std::vector<short> m_visibles;
		std::vector<short> m_writes;
		
		/*!
		*
		**/
		PropertyRecord() 
			: m_idx(-1), m_elementIdx(-1), m_isUpdated(false), m_isDeleted(false), m_isAdded(false)
		{
		}

		/*!
		*
		**/
		virtual ~PropertyRecord()
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
		virtual void GetFldDesc(int orde, string &desc)
		{
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
		virtual void SetFldValue(int order, string &value)
		{
		}

		/*!
		*
		**/
		virtual int GetReferenceType(int order)
		{
			return Ref_Unknown;
		}
	};

	/*!
	*
	**/
	struct ExplorationRecord : public PropertyRecord
	{
		//
		string m_groupName;
		string m_resourceName;
		long m_explorationDate; 
		double m_commercialWells;
		double m_commercialFootage;
		double m_wells;
		double m_evaluationWells;
		double m_evaluationFootage;
		double m_footage;
		double m_seismicLength;
		double m_seismicArea;
		double m_investment;
		double m_inplaceOil;
		double m_recoverableOil;
		double m_inplaceGas;
		double m_recoverableGas;

		/*!
		*
		**/
		ExplorationRecord() 
		{
			m_groupName = "";
			m_resourceName = "";
			m_explorationDate = 0; 
			m_commercialWells = 0.;
			m_commercialFootage = 0.;
			m_wells = 0.;
			m_evaluationWells = 0.;
			m_evaluationFootage = 0.;
			m_footage = 0.;
			m_seismicLength = 0.;
			m_seismicArea = 0.;
			m_investment = 0.;
			m_inplaceOil = 0.;
			m_recoverableOil = 0.;
			m_inplaceGas = 0.;
			m_recoverableGas = 0.;
		}

		/*!
		*
		**/
		const ExplorationRecord &operator=(const ExplorationRecord &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself info
			m_groupName = other.m_groupName;
			m_resourceName = other.m_resourceName;
			m_explorationDate = other.m_explorationDate; 
			m_commercialWells = other.m_commercialWells;
			m_commercialFootage = other.m_commercialFootage;
			m_wells = other.m_wells;
			m_evaluationWells = other.m_evaluationWells;
			m_evaluationFootage = other.m_evaluationFootage;
			m_footage = other.m_footage;
			m_seismicLength = other.m_seismicLength;
			m_seismicArea = other.m_seismicArea;
			m_investment = other.m_investment;
			m_inplaceOil = other.m_inplaceOil;
			m_recoverableOil = other.m_recoverableOil;
			m_inplaceGas = other.m_inplaceGas;
			m_recoverableGas = other.m_recoverableGas;

			//
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
			return 18;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "groupname";
				type=2;

			}
			if(order == 3)
			{
				value = "resourcename";
				type=2;

			}
			if(order == 4)
			{
				value = "explorationdate";
				type=0;

			}
			if(order == 5)
			{
				value = "commercialwells";
				type=1;

			}
			if(order == 6)
			{
				value = "commercialfootage";
				type=1;

			}
			if(order == 7)
			{
				value = "wells";
				type=1;

			}
			if(order == 8)
			{
				value = "evaluationwells";
				type=1;

			}
			if(order == 9)
			{
				value = "evaluationfootage";
				type=1;

			}
			if(order == 10)
			{
				value = "footage";
				type=1;

			}
			if(order == 11)
			{
				value = "seismiclength";
				type=1;

			}
			if(order == 12)
			{
				value = "seismicarea";
				type=1;

			}
			if(order == 13)
			{
				value = "investment";
				type=1;

			}
			if(order == 14)
			{
				value = "inplaceoil";
				type=1;

			}
			if(order == 15)
			{
				value = "recoverableoil";
				type=1;

			}
			if(order == 16)
			{
				value = "inplacegas";
				type=1;

			}
			if(order == 17)
			{
				value = "recoverablegas";
				type=1;

			}
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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value = m_groupName;
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%s", m_resourceName.c_str());
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_explorationDate);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_commercialWells);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_commercialFootage);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_wells);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_evaluationWells);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_evaluationFootage);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_footage);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_seismicLength);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_seismicArea);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_investment);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_inplaceOil);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoverableOil);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_inplaceGas);
			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoverableGas);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_groupName = value.c_str();
			}
			if(order == 3)
			{
				m_resourceName = value.c_str();
			}
			if(order == 4)
			{
				m_explorationDate = ::atol(value.c_str());
			}
			if(order == 5)
			{
				m_commercialWells = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_commercialFootage = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_wells = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_evaluationWells = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_evaluationFootage = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_footage = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_seismicLength = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_seismicArea = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_investment = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_inplaceOil = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_recoverableOil = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_inplaceGas = ::atof(value.c_str());
			}
			if(order == 17)
			{
				m_recoverableGas = ::atof(value.c_str());
			}
		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 3)
			{
				return Ref_ResourceName_Type;
			}
			return Ref_Unknown;
		}
	};

	/*!
	*
	**/
	struct PoolRecord : public PropertyRecord
	{
		//
		//string m_groupName;
		//string m_resourceName;
		//long m_trapIdx;
		//long m_appraisalWells;
		//long m_industryWells;
		//long m_drillWells;		
		//long m_foundDate;
		//double m_areaHeight;
		//double m_areaClosure;
		//double m_inplaceOil;
		//double m_recoverableOil;
		//double m_inplaceGas;
		//double m_recoverableGas;


		CLASS(PoolRecord,agm::reflection::NullClass);
		FIELD2(public,string, m_groupName);
		FIELD2(public,string, m_resourceName);		
		FIELD2(public,string, m_trapIdx);	
		FIELD2(public,long, m_appraisalWells);
		FIELD2(public,long, m_industryWells);
		FIELD2(public,long, m_drillWells);
		FIELD2(public,long, m_foundDate);
		FIELD2(public,double, m_areaHeight);	
		FIELD2(public,double, m_areaClosure);
		FIELD2(public,double, m_inplaceOil);		
		FIELD2(public,double, m_recoverableOil);		
		FIELD2(public,double, m_inplaceGas);
		FIELD2(public,double, m_recoverableGas);

		//2017/10/27: new variables
		FIELD2(public,double, m_usedreserves);
		FIELD2(public,double, m_recoverydegree);
		FIELD2(public,long, m_dataupdate);
		FIELD2(public,long, m_dataindate);
		FIELD2(public,double, m_effethickness);	
		FIELD2(public,double, m_avgverwellprod);
		FIELD2(public,double, m_avghorwellprod);		
		FIELD2(public,double, m_avgverwelleur);		
		FIELD2(public,double, m_avghorwelleur);
		FIELD2(public,double, m_recoveryfactor);
		FIELD2(public,double, m_reserveabundance);

		/*!
		*
		**/
		PoolRecord()
		{
			m_groupName = "";
			m_resourceName = "";
			m_trapIdx = "";
			m_appraisalWells = 0;
			m_industryWells = 0;
			m_drillWells = 0;		
			m_foundDate = 0;
			m_areaHeight = 0.;
			m_areaClosure = 0.;
			m_inplaceOil = 0.;
			m_recoverableOil = 0.;
			m_inplaceGas = 0.;
			m_recoverableGas = 0.;

			//
			m_usedreserves = 0.;
			m_recoverydegree = 0.;
			m_dataupdate = 0;
			m_dataindate = 0;
			m_effethickness = 0.;
			m_avgverwellprod = 0.;
			m_avghorwellprod = 0.;
			m_avgverwelleur = 0.;
			m_avghorwelleur = 0.;
			m_recoveryfactor = 0.;
			m_reserveabundance = 0.;
		}

		/*!
		*
		**/
		const PoolRecord &operator=(const PoolRecord &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			m_groupName = other.m_groupName;
			m_resourceName = other.m_resourceName;
			m_trapIdx = other.m_trapIdx;
			m_appraisalWells = other.m_appraisalWells;
			m_industryWells = other.m_industryWells;
			m_drillWells = other.m_drillWells;		
			m_foundDate = other.m_foundDate;
			m_areaHeight = other.m_areaHeight;
			m_areaClosure = other.m_areaClosure;
			m_inplaceOil = other.m_inplaceOil;
			m_recoverableOil = other.m_recoverableOil;
			m_inplaceGas = other.m_inplaceGas;
			m_recoverableGas = other.m_recoverableGas;

			//
			m_usedreserves = other.m_usedreserves;
			m_recoverydegree = other.m_recoverydegree;
			m_dataupdate = other.m_dataupdate;
			m_dataindate = other.m_dataindate;
			m_effethickness = other.m_effethickness;
			m_avgverwellprod = other.m_avgverwellprod;
			m_avghorwellprod = other.m_avghorwellprod;
			m_avgverwelleur = other.m_avgverwelleur;
			m_avghorwelleur = other.m_avghorwelleur;
			m_recoveryfactor = other.m_recoveryfactor;
			m_reserveabundance = other.m_reserveabundance;

			//
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
			return 15 + 11;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "groupname";
				type=2;

			}
			if(order == 3)
			{
				value = "resourcename";
				type=2;

			}
			if(order == 4)
			{
				value = "traptypeid";
				type=2;

			}
			if(order == 5)
			{
				value = "appraisalwells";
				type=0;

			}
			if(order == 6)
			{
				value = "industrywells";
				type=0;

			}
			if(order == 7)
			{
				value = "drillwells";
				type=0;

			}
			if(order == 8)
			{
				value = "founddate";
				type=0;

			}
			if(order == 9)
			{
				value = "areaheight";
				type=1;

			}
			if(order == 10)
			{
				value = "areaclosure";
				type=1;

			}
			if(order == 11)
			{
				value = "inplaceoil";
				type=1;

			}
			if(order == 12)
			{
				value = "recoverableoil";
				type=1;

			}
			if(order == 13)
			{
				value = "inplacegas";
				type=1;

			}
			if(order == 14)
			{
				value = "recoverablegas";
				type=1;

			}

			//
			if(order == 15){value = "usedreserves"			;type=1;}
			if(order == 16){value = "recoverydegree"		;type=1;}
			if(order == 17){value = "dataupdate"			;type=0;}
			if(order == 18){value = "dataindate"			;type=0;}
			if(order == 19){value = "effethickness"			;type=1;}
			if(order == 20){value = "avgverwellprod"		;type=1;}
			if(order == 21){value = "avghorwellprod"		;type=1;}
			if(order == 22){value = "avgverwelleur"			;type=1;}
			if(order == 23){value = "avghorwelleur"			;type=1;}
			if(order == 24){value = "recoveryfactor"		;type=1;}
			if(order == 25){value = "reserveabundance"		;type=1;}
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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value = m_groupName.c_str();
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%s", m_resourceName.c_str());
			}
			if(order == 4)
			{
				value = m_trapIdx.c_str();
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%d", m_appraisalWells);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%d", m_industryWells);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%d", m_drillWells);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%d", m_foundDate);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaHeight);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaClosure);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_inplaceOil);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoverableOil);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_inplaceGas);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoverableGas);
			}

			//
			if(order == 15){::sprintf((char *)value.c_str(), "%f", m_usedreserves);}
			if(order == 16){::sprintf((char *)value.c_str(), "%f", m_recoverydegree);}
			if(order == 17){::sprintf((char *)value.c_str(), "%d", m_dataupdate);}
			if(order == 18){::sprintf((char *)value.c_str(), "%d", m_dataindate);}
			if(order == 19){::sprintf((char *)value.c_str(), "%f", m_effethickness);}
			if(order == 20){::sprintf((char *)value.c_str(), "%f", m_avgverwellprod);}
			if(order == 21){::sprintf((char *)value.c_str(), "%f", m_avghorwellprod);}
			if(order == 22){::sprintf((char *)value.c_str(), "%f", m_avgverwelleur);}
			if(order == 23){::sprintf((char *)value.c_str(), "%f", m_avghorwelleur);}
			if(order == 24){::sprintf((char *)value.c_str(), "%f", m_recoveryfactor);}
			if(order == 25){::sprintf((char *)value.c_str(), "%f", m_reserveabundance);}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_groupName = value.c_str();
			}
			if(order == 3)
			{
				m_resourceName = value.c_str();
			}
			if(order == 4)
			{
				m_trapIdx = value.c_str();
			}
			if(order == 5)
			{
				m_appraisalWells = ::atoi(value.c_str());
			}
			if(order == 6)
			{
				m_industryWells = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_drillWells = ::atoi(value.c_str());
			}
			if(order == 8)
			{
				m_foundDate = ::atoi(value.c_str());
			}
			if(order == 9)
			{
				m_areaHeight = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_areaClosure = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_inplaceOil = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_recoverableOil = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_inplaceGas = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_recoverableGas = ::atof(value.c_str());
			}

			//
			if(order == 15){m_usedreserves = ::atof(value.c_str());}
			if(order == 16){m_recoverydegree = ::atof(value.c_str());}
			if(order == 17){m_dataupdate = ::atoi(value.c_str());}
			if(order == 18){m_dataindate = ::atoi(value.c_str());}
			if(order == 19){m_effethickness = ::atof(value.c_str());}
			if(order == 20){m_avgverwellprod = ::atof(value.c_str());}
			if(order == 21){m_avghorwellprod = ::atof(value.c_str());}
			if(order == 22){m_avgverwelleur = ::atof(value.c_str());}
			if(order == 23){m_avghorwelleur = ::atof(value.c_str());}
			if(order == 24){m_recoveryfactor = ::atof(value.c_str());}
			if(order == 25){m_reserveabundance = ::atof(value.c_str());}
		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 3)
			{
				return Ref_ResourceName_Type;
			}
			if(order == 4)
			{
				return Ref_Geology_Trap_Type;
			}
			return Ref_Unknown;
		}
	};

	/*!
	*
	**/
	struct VolumeRecord : public PropertyRecord
	{
		// coordinate
		//double m_xCoord;
		//double m_yCoord;

		// geo conditions
		double m_productArea;
		double m_grossThickness;
		double m_averagePorosity;
		double m_averageSaturation;
		double m_rockDensity;
		double m_oilDensity;
		double m_gasContent;

		// geo factors
		double m_geometricFactor;
		double m_nettogrossRatio;
		double m_formationVolumeFactor;
		double m_recoverableFactor;
		double m_recycleFactor;
		double m_conversionFactor;

		/*!
		*
		**/
		VolumeRecord() :  m_productArea(1.), m_grossThickness(1.), m_averagePorosity(1.), m_averageSaturation(1.), m_rockDensity(1.), m_oilDensity(1.), m_gasContent(1.),\
			m_geometricFactor(1.), m_nettogrossRatio(1.), m_formationVolumeFactor(1.), m_recoverableFactor(1.), m_conversionFactor(1.), m_recycleFactor(1.)
		{
		}

		/*!
		*
		**/
		const VolumeRecord &operator=(const VolumeRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			//m_xCoord = other.m_xCoord;
			//m_yCoord = other.m_yCoord;
			m_productArea = other.m_productArea;
			m_grossThickness = other.m_grossThickness;
			m_averagePorosity = other.m_averagePorosity;
			m_averageSaturation = other.m_averageSaturation;
			m_rockDensity = other.m_rockDensity;
			m_oilDensity = other.m_oilDensity;
			m_gasContent = other.m_gasContent;

			m_geometricFactor = other.m_geometricFactor;
			m_nettogrossRatio = other.m_nettogrossRatio;
			m_formationVolumeFactor = other.m_formationVolumeFactor;
			m_recoverableFactor = other.m_recoverableFactor;
			m_recycleFactor = other.m_recycleFactor;
			m_conversionFactor = other.m_conversionFactor;

			//
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
			return 15;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "productarea";
				type=1;

			}
			if(order == 3)
			{
				value = "grossthickness";
				type=1;

			}
			if(order == 4)
			{
				value = "averageporosity";
				type=1;

			}
			if(order == 5)
			{
				value = "averagehcsaturation";
				type=1;

			}
			if(order == 6)
			{
				value = "rockdensity";
				type=1;

			}
			if(order == 7)
			{
				value = "oildensity";
				type=1;

			}
			if(order == 8)
			{
				value = "gascontent";
				type=1;

			}
			if(order == 9)
			{
				value = "geometricfactor";
				type=1;

			}
			if(order == 10)
			{
				value = "nettogrossratio";
				type=1;

			}
			if(order == 11)
			{
				value = "formationvolumefactor";
				type=1;

			}
			if(order == 12)
			{
				value = "recoveryfactor";
				type=1;

			}
			if(order == 13)
			{
				value = "recyclefactor";
				type=1;

			}
			if(order == 14)
			{
				value = "conversionfacto";
				type=1;

			}

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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			/*if(order == 2)
			{
			::sprintf((char *)value.c_str(), "%f", m_xCoord);
			}
			if(order == 3)
			{
			::sprintf((char *)value.c_str(), "%f", m_yCoord);
			}*/
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%f", m_productArea);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_grossThickness);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_averagePorosity);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_averageSaturation);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockDensity);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilDensity);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_gasContent);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_geometricFactor);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_nettogrossRatio);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_formationVolumeFactor);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoverableFactor);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_recycleFactor);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_conversionFactor);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			/*		if(order == 2)
			{
			m_xCoord = ::atof(value.c_str());
			}
			if(order == 3)
			{
			m_yCoord = ::atof(value.c_str());
			}*/
			if(order == 2)
			{
				m_productArea = ::atof(value.c_str());
			}
			if(order == 3)
			{
				m_grossThickness = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_averagePorosity = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_averageSaturation = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_rockDensity = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_oilDensity = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_gasContent = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_geometricFactor = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_nettogrossRatio = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_formationVolumeFactor = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_recoverableFactor = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_recycleFactor = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_conversionFactor = ::atof(value.c_str());
			}
		}
	};

	/*!
	*
	**/
	struct VolumeParaRecord : public PropertyRecord
	{
		double m_minproductarea			;
		double m_modeproductarea			;
		double m_maxproductarea			;

		double m_mingrossthickness		;
		double m_modegrossthickness		;
		double m_maxgrossthickness		;

		double m_minaverageporosity		;
		double m_modeaverageporosity		;
		double m_maxaverageporosity		;

		double m_minaveragehcsaturation   ;
		double m_modeaveragehcsaturation  ;
		double m_maxaveragehcsaturation   ;

		double m_minrockdensity			;
		double m_moderockdensity			;
		double m_maxrockdensity			;

		double m_minoildensity			;
		double m_modeoildensity			;
		double m_maxoildensity			;

		double m_mingascontent			;
		double m_modegascontent			;
		double m_maxgascontent			;

		double m_mingeometricfactor		;
		double m_modegeometricfactor		;
		double m_maxgeometricfactor		;

		double m_minnettogrossratio		;
		double m_modenettogrossratio		;
		double m_maxnettogrossratio		;

		double m_minformationvolumefactor ;
		double m_modeformationvolumefactor;
		double m_maxformationvolumefactor ;

		double m_minrecoveryfactor		;
		double m_moderecoveryfactor		;
		double m_maxrecoveryfactor		;

		double m_minrecyclefactor			;
		double m_moderecyclefactor		;
		double m_maxrecyclefactor			;

		double m_minconversionfactor		;  	
		double m_modeconversionfactor		;  	
		double m_maxconversionfactor      ;

		long   m_commitphase   ;
		long   m_wellnumber    ;
		long   m_footage 	   ;
		long   m_istest 	   ;
		double m_geooil 	   ;
		double m_geogas 	   ;
		double m_recoveryrate  ;
		double m_recoveryoil   ;
		double m_recoverygas   ;

		long m_managementphase;

		/*!
		*
		**/
		VolumeParaRecord() : m_minproductarea			(0),
							 m_modeproductarea		(0),	
							 m_maxproductarea			(0),
							 m_mingrossthickness		(0),
							 m_modegrossthickness		(0),
							 m_maxgrossthickness		(0),
							 m_minaverageporosity		(0),
							 m_modeaverageporosity	(0),	
							 m_maxaverageporosity		(0),
							 m_minaveragehcsaturation (0),  
							 m_modeaveragehcsaturation(0),  
							 m_maxaveragehcsaturation (0),  
							 m_minrockdensity				(0),
							 m_moderockdensity			(0),
							 m_maxrockdensity				(0),
							 m_minoildensity				(0),
							 m_modeoildensity				(0),
							 m_maxoildensity				(0),
							 m_mingascontent				(0),
							 m_modegascontent				(0),
							 m_maxgascontent				(0),
							 m_mingeometricfactor			(0),
							 m_modegeometricfactor		(0),
							 m_maxgeometricfactor			(0),
							 m_minnettogrossratio			(0),
							 m_modenettogrossratio		(0),
							 m_maxnettogrossratio			(0),
							 m_minformationvolumefactor	(0),
							 m_modeformationvolumefactor	(0),
							 m_maxformationvolumefactor 	(0),
							 m_minrecoveryfactor			(0),
							 m_moderecoveryfactor			(0),
							 m_maxrecoveryfactor			(0),
							 m_minrecyclefactor			(0),
							 m_moderecyclefactor			(0),
							 m_maxrecyclefactor			(0),
							 m_minconversionfactor		(0),
							 m_modeconversionfactor		(0),
							 m_maxconversionfactor      	(0)
		{

			m_commitphase  =0 ;
			m_wellnumber   =0 ;
			m_footage 	   =0;
			m_istest 	   =0;
			m_geooil 	   =0.0;
			m_geogas 	   =0.0;
			m_recoveryrate =0.0 ;
			m_recoveryoil  =0.0 ;
			m_recoverygas  =0.0 ;

			m_managementphase = 0;

		}

		/*!
		*
		**/
		const VolumeParaRecord &operator=(const VolumeParaRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			
				m_minproductarea			  =other.m_minproductarea		;	
				m_modeproductarea			  =other.m_modeproductarea		;
				m_maxproductarea			  =other.m_maxproductarea			;	
				m_mingrossthickness		  =other.m_mingrossthickness		;
				m_modegrossthickness		  =other.m_modegrossthickness		;
				m_maxgrossthickness		  =other.m_maxgrossthickness		;
				m_minaverageporosity		  =other.m_minaverageporosity		;
				m_modeaverageporosity		  =other.m_modeaverageporosity	;
				m_maxaverageporosity		  =other.m_maxaverageporosity		;	
				m_minaveragehcsaturation    =other.m_minaveragehcsaturation ;
				m_modeaveragehcsaturation   =other.m_modeaveragehcsaturation;  
				m_maxaveragehcsaturation    =other.m_maxaveragehcsaturation ;  
				m_minrockdensity			  =other.m_minrockdensity			;  
				m_moderockdensity			  =other.m_moderockdensity		;
				m_maxrockdensity			  =other.m_maxrockdensity			;	
				m_minoildensity			  =other.m_minoildensity			;
				m_modeoildensity			  =other.m_modeoildensity			;
				m_maxoildensity			  =other.m_maxoildensity			;
				m_mingascontent			  =other.m_mingascontent			;
				m_modegascontent			  =other.m_modegascontent			;
				m_maxgascontent			  =other.m_maxgascontent			;
				m_mingeometricfactor		  =other.m_mingeometricfactor		;
				m_modegeometricfactor		  =other.m_modegeometricfactor	;
				m_maxgeometricfactor		  =other.m_maxgeometricfactor		;	
				m_minnettogrossratio		  =other.m_minnettogrossratio		;
				m_modenettogrossratio		  =other.m_modenettogrossratio	;
				m_maxnettogrossratio		  =other.m_maxnettogrossratio		;	
				m_minformationvolumefactor  =other.m_minformationvolumefactor ;
				m_modeformationvolumefactor =other.m_modeformationvolumefactor;
				m_maxformationvolumefactor  =other.m_maxformationvolumefactor ;
				m_minrecoveryfactor		  =other.m_minrecoveryfactor		;
				m_moderecoveryfactor		  =other.m_moderecoveryfactor		;
				m_maxrecoveryfactor		  =other.m_maxrecoveryfactor		;
				m_minrecyclefactor		  =other.m_minrecyclefactor		;	
				m_moderecyclefactor		  =other.m_moderecyclefactor		;
				m_maxrecyclefactor		  =other.m_maxrecyclefactor		;	
				m_minconversionfactor		  =other.m_minconversionfactor	;	
				m_modeconversionfactor	  =other.m_modeconversionfactor	;	
				m_maxconversionfactor       =other.m_maxconversionfactor    ; 
				m_commitphase				=other.m_commitphase ;
				m_wellnumber				=other.m_wellnumber  ;
				m_footage 					=other.m_footage 	  ;
				m_istest 					=other.m_istest 	  ;
				m_geooil 					=other.m_geooil 	  ;
				m_geogas 					=other.m_geogas 	  ;
				m_recoveryrate				=other.m_recoveryrate;
				m_recoveryoil				=other.m_recoveryoil ;
				m_recoverygas				=other.m_recoverygas ;

				m_managementphase = other.m_managementphase;
			//
			return *this;
		}


		/*!
		*
		**/
		int GetFldCount()
		{
			return 50;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "minproductare";
				type=1;

			}
			if(order == 3)
			{
				value = "modeproductarea";
				type=1;

			}
			if(order == 4)
			{
				value = "maxproductarea";
				type=1;

			}
			if(order == 5)
			{
				value = "mingrossthickness";
				type=1;

			}
			if(order == 6)
			{
				value = "modegrossthickness";
				type=1;

			}
			if(order == 7)
			{
				value = "maxgrossthickness";
				type=1;

			}
			if(order == 8)
			{
				value = "minaverageporosity";
				type=1;

			}
			if(order == 9)
			{
				value = "modeaverageporosity";
				type=1;

			}
			if(order == 10)
			{
				value = "maxaverageporosity";
				type=1;

			}
			if(order == 11)
			{
				value = "minaveragehcsaturation";
				type=1;

			}
			if(order == 12)
			{
				value = "modeaveragehcsaturation";
				type=1;

			}
			if(order == 13)
			{
				value = "maxaveragehcsaturation";
				type=1;

			}
			if(order == 14)
			{
				value = "minrockdensity";
				type=1;

			}
			if(order == 15)
			{
				value = "moderockdensity";
				type=1;

			}
			if(order == 16)
			{
				value = "maxrockdensity";
				type=1;

			}
			if(order == 17)
			{
				value = "minoildensity";
				type=1;

			}
			if(order == 18)
			{
				value = "modeoildensity";
				type=1;

			}
			if(order == 19)
			{
				value = "maxoildensity";
				type=1;

			}
			if(order == 20)
			{
				value = "mingascontent";
				type=1;

			}
			if(order == 21)
			{
				value = "modegascontent";
				type=1;

			}
			if(order == 22)
			{
				value = "maxgascontent";
				type=1;

			}
			if(order == 23)
			{
				value = "mingeometricfactor";
				type=1;

			}
			if(order == 24)
			{
				value = "modegeometricfactor";
				type=1;

			}
			if(order == 25)
			{
				value = "maxgeometricfactor";
				type=1;

			}
			if(order == 26)
			{
				value = "minnettogrossratio";
				type=1;

			}
			if(order == 27)
			{
				value = "modenettogrossratio";
				type=1;

			}
			if(order == 28)
			{
				value = "maxnettogrossratio";
				type=1;

			}
			if(order == 29)
			{
				value = "minformationvolumefactor";
				type=1;

			}
			if(order == 30)
			{
				value = "modeformationvolumefactor";
				type=1;

			}
			if(order == 31)
			{
				value = "maxformationvolumefactor";
				type=1;

			}
			if(order == 32)
			{
				value = "minrecoveryfactor";
				type=1;

			}
			if(order == 33)
			{
				value = "moderecoveryfactor";
				type=1;

			}
			if(order == 34)
			{
				value = "maxrecoveryfactor";
				type=1;

			}
			if(order == 35)
			{
				value = "minrecyclefactor";
				type=1;

			}
			if(order == 36)
			{
				value = "moderecyclefactor";
				type=1;

			}
			if(order == 37)
			{
				value = "maxrecyclefactor";
				type=1;

			}
			if(order == 38)
			{
				value = "minconversionfactor";
				type=1;

			}
			if(order == 39)
			{
				value = "modeconversionfactor";
				type=1;

			}
			if(order == 40)
			{
				value = "maxconversionfactor";
				type=1;

			}
			if(order == 41)
			{
				value = "commitphase";
				type=0;

			}
			if(order == 42)
			{
				value = "wellnumber";
				type=0;

			}
			if(order == 43)
			{
				value = "footage";
				type=0;

			}
			if(order == 44)
			{
				value = "istest";
				type=0;

			}
			if(order == 45)
			{
				value = "geooil";
				type=1;

			}
			if(order == 46)
			{
				value = "geogas";
				type=1;

			}
			if(order == 47)
			{
				value = "recoveryrate";
				type=1;

			}
			if(order == 48)
			{
				value = "recoveryoil";
				type=1;

			}
			if(order == 49)
			{
				value = "recoverygas";
				type=1;

			}
		}

		/*!
		*
		**/
		int GetRealFldCount()
		{
			return 13;
		}
		int GetRealotherFldCount()
		{
			return 9;
		}
	

		/*!
		*
		**/
		void GetRealFldName(int order,string &name)
		{
			if(order == 0)
			{
				name = "Product Area(a)";
			}
			if(order == 1)
			{
				name = "Gross Thickness(h)";
			}
			if(order == 2)
			{
				name = "Average Porosity(phi)";
			}
			if(order == 3)
			{
				name = "HC Saturation(shc)";
			}
			if(order == 4)
			{
				name = "Rock Density(pr)";
			}
			if(order == 5)
			{
				name = "Oil Density(po)";
			}
			if(order == 6)
			{
				name = "Gas Content(q)";
			}
			if(order == 7)
			{
				name = "Geometric Factor(gf)";
			}
			if(order == 8)
			{
				name = "Net2Gross(k)";
			}
			if(order == 9)
			{
				name = "FormationVolumeFactor(bhc)";
			}
			if(order == 10)
			{
				name = "Recovery Factor(rf)";
			}
			if(order == 11)
			{
				name = "Recycle Factor(r1)";
			}
			if(order == 12)
			{
				name = "Conversion Factor(cf)";
			}
		}

		void GetOtherRealFldName(int order,string &name)
		{
			if(order == 0)
			{
				name = "commitphase";
			}
			if(order == 1)
			{
				name = "wellnumber";
			}
			if(order == 2)
			{
				name = "footage";
			}
			if(order == 3)
			{
				name = "istest";
			}
			if(order == 4)
			{
				name = "geooil";
			}
			if(order == 5)
			{
				name = "geogas";
			}
			if(order == 6)
			{
				name = "recoveryrate";
			}
			if(order == 7)
			{
				name = "recoveryoil";
			}
			if(order == 8)
			{
				name = "recoverygas";
			}
		}
		int GetOtherRealFldType(int order)//0 文本  //1 int  //2 float
		{
			if(order == 0)
			{
				return 0;
			}
			if(order == 1)
			{
				return 1;
			}
			if(order == 2)
			{
				return 1;
			}
			if(order == 3)
			{
				return 1;
			}
			if(order == 4)
			{
				return 2;
			}
			if(order == 5)
			{
				return 2;
			}
			if(order == 6)
			{
				return 2;
			}
			if(order == 7)
			{
				return 2;
			}
			if(order == 8)
			{
				return 2;
			}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%f", m_minproductarea);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_modeproductarea);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxproductarea);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_mingrossthickness);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_modegrossthickness);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxgrossthickness);
			}

			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_minaverageporosity);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_modeaverageporosity);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxaverageporosity);
			}
			if(order ==11)
			{
				::sprintf((char *)value.c_str(), "%f", m_minaveragehcsaturation);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_modeaveragehcsaturation);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxaveragehcsaturation);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_minrockdensity);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_moderockdensity);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxrockdensity);
			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_minoildensity);
			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_modeoildensity);
			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxoildensity);
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_mingascontent);
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_modegascontent);
			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxgascontent);
			}
			if(order == 23)
			{
				::sprintf((char *)value.c_str(), "%f", m_mingeometricfactor);
			}
			if(order == 24)
			{
				::sprintf((char *)value.c_str(), "%f", m_modegeometricfactor);
			}
			if(order == 25)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxgeometricfactor);
			}
			if(order == 26)
			{
				::sprintf((char *)value.c_str(), "%f", m_minnettogrossratio);
			}
			if(order == 27)
			{
				::sprintf((char *)value.c_str(), "%f", m_modenettogrossratio);
			}
			if(order == 28)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxnettogrossratio);
			}
			if(order == 29)
			{
				::sprintf((char *)value.c_str(), "%f", m_minformationvolumefactor);
			}
			if(order == 30)
			{
				::sprintf((char *)value.c_str(), "%f", m_modeformationvolumefactor);
			}
			if(order == 31)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxformationvolumefactor);
			}
			if(order == 32)
			{
				::sprintf((char *)value.c_str(), "%f", m_minrecoveryfactor);
			}
			if(order == 33)
			{
				::sprintf((char *)value.c_str(), "%f", m_moderecoveryfactor);
			}
			if(order == 34)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxrecoveryfactor);
			}
			if(order == 35)
			{
				::sprintf((char *)value.c_str(), "%f", m_minrecyclefactor);
			}
			if(order == 36)
			{
				::sprintf((char *)value.c_str(), "%f", m_moderecyclefactor);
			}
			if(order == 37)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxrecyclefactor);
			}
			if(order == 38)
			{
				::sprintf((char *)value.c_str(), "%f", m_minconversionfactor);
			}
			if(order == 39)
			{
				::sprintf((char *)value.c_str(), "%f", m_modeconversionfactor);
			}
			if(order == 40)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxconversionfactor );
			}
			if(order == 41)
			{
				::sprintf((char *)value.c_str(), "%ld", m_commitphase);
			}
			if(order == 42)
			{
				::sprintf((char *)value.c_str(), "%ld", m_wellnumber);
			}
			if(order == 43)
			{
				::sprintf((char *)value.c_str(), "%ld", m_footage);
			}
			if(order == 44)
			{
				::sprintf((char *)value.c_str(), "%ld", m_istest);
			}
			if(order == 45)
			{
				::sprintf((char *)value.c_str(), "%f", m_geooil);
			}
			if(order == 46)
			{
				::sprintf((char *)value.c_str(), "%f", m_geogas);
			}
			if(order == 47)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoveryrate);
			}
			if(order == 48)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoveryoil);
			}
			if(order == 49)
			{
				::sprintf((char *)value.c_str(), "%f", m_recoverygas);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_minproductarea = ::atof(value.c_str());
			}
			if(order == 3)
			{
				m_modeproductarea = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_maxproductarea = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_mingrossthickness = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_modegrossthickness = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_maxgrossthickness = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_minaverageporosity = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_modeaverageporosity = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_maxaverageporosity = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_minaveragehcsaturation = ::atof(value.c_str());
			}
			if(order ==12)
			{
				m_modeaveragehcsaturation = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_maxaveragehcsaturation = ::atof(value.c_str());
			}
			if(order ==14)
			{
				m_minrockdensity = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_moderockdensity = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_maxrockdensity = ::atof(value.c_str());
			}
			if(order == 17)
			{
				m_minoildensity = ::atof(value.c_str());
			}
			if(order == 18)
			{
				m_modeoildensity = ::atof(value.c_str());
			}
			if(order == 19)
			{
				m_maxoildensity = ::atof(value.c_str());
			}
			if(order == 20)
			{
				m_mingascontent = ::atof(value.c_str());
			}
			if(order == 21)
			{
				m_modegascontent = ::atof(value.c_str());
			}
			if(order == 22)
			{
				m_maxgascontent = ::atof(value.c_str());
			}
			if(order == 23)
			{
				m_mingeometricfactor = ::atof(value.c_str());
			}
			if(order == 24)
			{
				m_modegeometricfactor = ::atof(value.c_str());
			}
			if(order == 25)
			{
				m_maxgeometricfactor = ::atof(value.c_str());
			}
			if(order == 26)
			{
				m_minnettogrossratio = ::atof(value.c_str());
			}
			if(order == 27)
			{
				m_modenettogrossratio = ::atof(value.c_str());
			}
			if(order == 28)
			{
				m_maxnettogrossratio = ::atof(value.c_str());
			}
			if(order == 29)
			{
				m_minformationvolumefactor = ::atof(value.c_str());
			}
			if(order == 30)
			{
				m_modeformationvolumefactor = ::atof(value.c_str());
			}
			if(order == 31)
			{
				m_maxformationvolumefactor = ::atof(value.c_str());
			}
			if(order == 32)
			{
				m_minrecoveryfactor = ::atof(value.c_str());
			}
			if(order == 33)
			{
				m_moderecoveryfactor = ::atof(value.c_str());
			}
			if(order == 34)
			{
				m_maxrecoveryfactor = ::atof(value.c_str());
			}
			if(order == 35)
			{
				m_minrecyclefactor = ::atof(value.c_str());
			}
			if(order == 36)
			{
				m_moderecyclefactor = ::atof(value.c_str());
			}
			if(order == 37)
			{
				m_maxrecyclefactor = ::atof(value.c_str());
			}
			if(order == 38)
			{
				m_minconversionfactor = ::atof(value.c_str());
			}
			if(order == 39)
			{
				m_modeconversionfactor = ::atof(value.c_str());
			}
			if(order == 40)
			{
				m_maxconversionfactor = ::atof(value.c_str());
			}
			if(order == 41)
			{
				 m_commitphase=::atoi(value.c_str());;
			}
			if(order == 42)
			{
				m_wellnumber=::atoi(value.c_str());;
			}
			if(order == 43)
			{
				m_footage=::atoi(value.c_str());;
			}
			if(order == 44)
			{
				m_istest=::atoi(value.c_str());
			}
			if(order == 45)
			{
				m_geooil=::atof(value.c_str());
			}
			if(order == 46)
			{
				m_geogas=::atof(value.c_str());
			}
			if(order == 47)
			{
				m_recoveryrate=::atof(value.c_str());
			}
			if(order == 48)
			{
				m_recoveryoil=::atof(value.c_str());
			}
			if(order == 49)
			{
				m_recoverygas=::atof(value.c_str());
			}
		}

	};




	/*!
	*
	**/
	struct OverallRecord : public PropertyRecord
	{
		// area of assessment unit[km2]
		ProbabilityField m_area;
		// number of mapped features
		ProbabilityField m_mapped;
		// number of postulated features
		ProbabilityField m_postulated;
		// conditional segment probability uncertainty
		ProbabilityField m_conditional;
		// discovered features
		ProbabilityField m_discovered;
		// yet-to-find threshold for effective as ...
		ProbabilityField m_ytf;
		// exploration efficiency
		ProbabilityField m_beta;

		/*!
		*
		**/
		const OverallRecord &operator=(const OverallRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// area of assessment unit[km2]
			m_area = other.m_area;
			// number of mapped features
			m_mapped = other.m_mapped;
			// number of postulated features
			m_postulated = other.m_postulated;
			// conditional segment probability uncertainty
			m_conditional = other.m_conditional;
			// discovered features
			m_discovered = other.m_discovered;
			// yet-to-find threshold for effective as ...
			m_ytf = other.m_ytf;
			// exploration efficiency
			m_beta = other.m_beta;

			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 7 * 2 + 2;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}
		/*!
		*
		**/
		void GetFldDesc(int order, string &desc)
		{
			order -= 2;
			if(order >= 0  && order <= 1)
			{
				desc = "Area of accumulation unit[km^2]";
			}
			if(order >= 2 && order <= 3)
			{
				desc = "Number of mapped features";
			}
			if(order >= 4 && order <= 5)
			{
				desc = "Number of postulated features";
			}
			if(order >= 6 && order <= 7)
			{
				desc = "Conditional segment probability uncertainty multiplier";
			}
			if(order >= 8 && order <= 9)
			{
				desc = "Discovered resources[1e6 sm^3 OE]";
			}
			if(order >= 10 && order <= 11)
			{
				desc = "YTF threshold for effective assessment unit[1e6 sm^3 OE]";
			}
			if(order >= 12 && order <= 13)
			{
				desc = "Exploration efficiency[decimal]";
			}
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_area.m_idx);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%s", m_area.m_parameter.c_str());
			}
			if(order == 4) 
			{
				::sprintf((char *)value.c_str(), "%d", m_mapped.m_idx);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%s", m_mapped.m_parameter.c_str());
			}
			if(order == 6) 
			{
				::sprintf((char *)value.c_str(), "%d", m_postulated.m_idx);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%s", m_postulated.m_parameter.c_str());
			}
			if(order == 8) 
			{
				::sprintf((char *)value.c_str(), "%d", m_conditional.m_idx);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%s", m_conditional.m_parameter.c_str());
			}
			if(order == 10) 
			{
				::sprintf((char *)value.c_str(), "%d", m_discovered.m_idx);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%s", m_discovered.m_parameter.c_str());
			}
			if(order == 12) 
			{
				::sprintf((char *)value.c_str(), "%d", m_ytf.m_idx);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%s", m_ytf.m_parameter.c_str());
			}
			if(order == 14) 
			{
				::sprintf((char *)value.c_str(), "%d", m_beta.m_idx);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%s", m_beta.m_parameter.c_str());
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0) 
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_area.m_idx = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_area.m_parameter = value;
			}
			if(order == 4) 
			{
				m_mapped.m_idx = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_mapped.m_parameter = value;
			}
			if(order == 6) 
			{
				m_postulated.m_idx = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_postulated.m_parameter = value;
			}
			if(order == 8) 
			{
				m_conditional.m_idx = ::atoi(value.c_str());
			}
			if(order == 9)
			{
				m_conditional.m_parameter = value;
			}
			if(order == 10) 
			{
				m_discovered.m_idx = ::atoi(value.c_str());
			}
			if(order == 11)
			{
				m_discovered.m_parameter = value;
			}
			if(order == 12) 
			{
				m_ytf.m_idx = ::atoi(value.c_str());
			}
			if(order == 13)
			{
				m_ytf.m_parameter = value;
			}
			if(order == 14) 
			{
				m_beta.m_idx = ::atoi(value.c_str());
			}
			if(order == 15)
			{
				m_beta.m_parameter = value;
			}
		}
	};




	/*!
	*
	**/
	struct OverallShalePlayRecord : public PropertyRecord
	{
		// area of assessment unit[km2]
		ProbabilityField m_a	;
		ProbabilityField m_h	;
		ProbabilityField m_toc	;
		ProbabilityField m_ro	;
		ProbabilityField m_phi	;
		ProbabilityField m_ra	;
		ProbabilityField m_hh	;
		ProbabilityField m_fmc	;
		ProbabilityField m_sg	;
		ProbabilityField m_q	;
		ProbabilityField m_s1	;
		ProbabilityField m_so	;
		ProbabilityField m_po	;
		ProbabilityField m_fvt	;

		/*!
		*
		**/
		const OverallShalePlayRecord &operator=(const OverallShalePlayRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_a		=other.m_a		;
			m_h		=other.m_h		;
			m_toc	=other.m_toc	;
			m_ro	=other.m_ro	;
			m_phi	=other.m_phi	;
			m_ra	=other.m_ra	;
			m_hh	=other.m_hh	;
			m_fmc	=other.m_fmc	;
			m_sg	=other.m_sg	;
			m_q	 	=other.m_q	;
			m_s1	=other.m_s1	;
			m_so	=other.m_so	;
			m_po	=other.m_po	;
			m_fvt	=other.m_fvt	;

			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 14 * 2 + 2;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}
		/*!
		*
		**/
		void GetFldDesc(int order, string &desc)
		{
			order -= 2;
			if(order >= 0  && order <= 1)
			{
				desc = "分布面积";
			}
			if(order >= 2 && order <= 3)
			{
				desc = "有效厚度";
			}
			if(order >= 4 && order <= 5)
			{
				desc = "TOC";
			}
			if(order >= 6 && order <= 7)
			{
				desc = "RO";
			}
			if(order >= 8 && order <= 9)
			{
				desc = "孔隙度";
			}
			if(order >= 10 && order <= 11)
			{
				desc = "储量丰度";
			}
			if(order >= 12 && order <= 13)
			{
				desc = "埋深";
			}
			if(order >= 14 && order <= 15)
			{
				desc = "脆性矿物含量";
			}
			if(order >= 16 && order <= 17)
			{
				desc = "含气饱和度";
			}
			if(order >= 18 && order <= 19)
			{
				desc = "含气量";
			}
			if(order >= 20 && order <= 21)
			{
				desc = "S1";
			}
			if(order >= 22 && order <= 23)
			{
				desc = "含油饱和度";
			}
			if(order >= 24 && order <= 25)
			{
				desc = "原油密度";
			}
			if(order >= 26 && order <= 27)
			{
				desc = "体积系数";
			}
	
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_a.m_idx);
			}
			if(order == 3)
			{
				value = m_a.m_parameter;
			}
			if(order == 4) 
			{
				::sprintf((char *)value.c_str(), "%d", m_h.m_idx);
			}
			if(order == 5)
			{
				value = m_h.m_parameter;
			}
			if(order == 6) 
			{
				::sprintf((char *)value.c_str(), "%d", m_toc.m_idx);
			}
			if(order == 7)
			{
				value = m_toc.m_parameter;
			}
			if(order == 8) 
			{
				::sprintf((char *)value.c_str(), "%d", m_ro.m_idx);
			}
			if(order == 9)
			{
				value = m_ro.m_parameter;
			}
			if(order == 10) 
			{
				::sprintf((char *)value.c_str(), "%d", m_phi.m_idx);
			}
			if(order == 11)
			{
				value = m_phi.m_parameter;
			}
			if(order == 12) 
			{
				::sprintf((char *)value.c_str(), "%d", m_ra.m_idx);
			}
			if(order == 13)
			{
				value = m_ra.m_parameter;
			}
			if(order == 14) 
			{
				::sprintf((char *)value.c_str(), "%d", m_hh.m_idx);
			}
			if(order == 15)
			{
				value = m_hh.m_parameter;
			}
			if(order == 16) 
			{
				::sprintf((char *)value.c_str(), "%d", m_fmc.m_idx);
			}
			if(order == 17)
			{
				value = m_fmc.m_parameter;
			}
			if(order == 18) 
			{
				::sprintf((char *)value.c_str(), "%d", m_sg.m_idx);
			}
			if(order == 19)
			{
				value = m_sg.m_parameter;
			}
			if(order == 20) 
			{
				::sprintf((char *)value.c_str(), "%d", m_q.m_idx);
			}
			if(order == 21)
			{
				value = m_q.m_parameter;
			}
			if(order == 22) 
			{
				::sprintf((char *)value.c_str(), "%d", m_s1.m_idx);
			}
			if(order == 23)
			{
				value = m_s1.m_parameter;
			}
			if(order == 24) 
			{
				::sprintf((char *)value.c_str(), "%d", m_so.m_idx);
			}
			if(order == 25)
			{
				value = m_so.m_parameter;
			}
			if(order == 26) 
			{
				::sprintf((char *)value.c_str(), "%d", m_po.m_idx);
			}
			if(order == 27)
			{
				value = m_po.m_parameter;
			}
			if(order == 28) 
			{
				::sprintf((char *)value.c_str(), "%d", m_fvt.m_idx);
			}
			if(order == 29)
			{
				value = m_fvt.m_parameter;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0) 
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_a.m_idx = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_a.m_parameter = value;
			}
			if(order == 4) 
			{
				m_h.m_idx = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_h.m_parameter = value;
			}
			if(order == 6) 
			{
				m_toc.m_idx = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_toc.m_parameter = value;
			}
			if(order == 8) 
			{
				m_ro.m_idx = ::atoi(value.c_str());
			}
			if(order == 9)
			{
				m_ro.m_parameter = value;
			}
			if(order == 10) 
			{
				m_phi.m_idx = ::atoi(value.c_str());
			}
			if(order == 11)
			{
				m_phi.m_parameter = value;
			}
			if(order == 12) 
			{
				m_ra.m_idx = ::atoi(value.c_str());
			}
			if(order == 13)
			{
				m_ra.m_parameter = value;
			}
			if(order == 14) 
			{
				m_hh.m_idx = ::atoi(value.c_str());
			}
			if(order == 15)
			{
				m_hh.m_parameter = value;
			}
			if(order == 16) 
			{
				m_fmc.m_idx = ::atoi(value.c_str());
			}
			if(order == 17)
			{
				m_fmc.m_parameter = value;
			}
			if(order == 18) 
			{
				m_sg.m_idx = ::atoi(value.c_str());
			}
			if(order == 19)
			{
				m_sg.m_parameter = value;
			}
			if(order == 20) 
			{
				m_q.m_idx = ::atoi(value.c_str());
			}
			if(order == 21)
			{
				m_q.m_parameter = value;
			}
			if(order == 22) 
			{
				m_s1.m_idx = ::atoi(value.c_str());
			}
			if(order == 23)
			{
				m_s1.m_parameter = value;
			}
			if(order == 24) 
			{
				m_so.m_idx = ::atoi(value.c_str());
			}
			if(order == 25)
			{
				m_so.m_parameter = value;
			}
			if(order == 26) 
			{
				m_po.m_idx = ::atoi(value.c_str());
			}
			if(order == 27)
			{
				m_po.m_parameter = value;
			}
			if(order == 28) 
			{
				m_fvt.m_idx = ::atoi(value.c_str());
			}
			if(order == 29)
			{
				m_fvt.m_parameter = value;
			}
		}
	};












		/*!
	*
	**/
	struct OverallShaleTargetRecord : public PropertyRecord
	{
		// area of assessment unit[km2]
		ProbabilityField m_a	 ;
		ProbabilityField m_h	 ;
		ProbabilityField m_toc	 ;
		ProbabilityField m_ro	 ;
		ProbabilityField m_phi	 ;
		ProbabilityField m_ra	 ;
		ProbabilityField m_eur	 ;
		ProbabilityField m_hh	 ;
		ProbabilityField m_fmc	 ;
		ProbabilityField m_q	 ;
		ProbabilityField m_qminus;
		ProbabilityField m_sg	 ;
		ProbabilityField m_qq	 ;
		ProbabilityField m_so	 ;
		ProbabilityField m_po	 ;
		ProbabilityField m_fvt	 ;

		/*!
		*
		**/
		const OverallShaleTargetRecord &operator=(const OverallShaleTargetRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_a		 =other.m_a		 ;
			m_h		 =other.m_h		 ;
			m_toc	 =other.m_toc	 ;
			m_ro	 =other.m_ro	 ;
			m_phi	 =other.m_phi	 ;
			m_ra	 =other.m_ra	 ;
			m_hh	 =other.m_hh	 ;
			m_fmc	 =other.m_fmc	 ;
			m_q		 =other.m_q		 ;
			m_qminus =other.m_qminus ;
			m_sg	 =other.m_sg	 ;
			m_qq	 =other.m_qq	 ;
			m_so	 =other.m_so	 ;
			m_po	 =other.m_po	 ;
			m_fvt	 =other.m_fvt	 ;
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 16 * 2 + 2;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}
		/*!
		*
		**/
		void GetFldDesc(int order, string &desc)
		{
			order -= 2;
			if(order >= 0  && order <= 1)
			{
				desc = "分布面积";
			}
			if(order >= 2 && order <= 3)
			{
				desc = "有效厚度";
			}
			if(order >= 4 && order <= 5)
			{
				desc = "TOC";
			}
			if(order >= 6 && order <= 7)
			{
				desc = "RO";
			}
			if(order >= 8 && order <= 9)
			{
				desc = "孔隙度";
			}
			if(order >= 10 && order <= 11)
			{
				desc = "储量丰度";
			}
			if(order >= 12 && order <= 13)
			{
				desc = "可采储量";
			}
			if(order >= 14 && order <= 15)
			{
				desc = "埋深";
			}
			if(order >= 16 && order <= 17)
			{
				desc = "脆性矿物含量";
			}
			if(order >= 18 && order <= 19)
			{
				desc = "累产";
			}
			if(order >= 20 && order <= 21)
			{
				desc = "单井平均累产";
			}
			if(order >= 22 && order <= 23)
			{
				desc = "含气饱和度";
			}
			if(order >= 24 && order <= 25)
			{
				desc = "含气量";
			}
			if(order >= 26 && order <= 27)
			{
				desc = "含油饱和度";
			}
			if(order >= 28 && order <= 29)
			{
				desc = "原油密度";
			}
			if(order >= 30 && order <= 31)
			{
				desc = "体积系数";
			}
	
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_a.m_idx);
			}
			if(order == 3)
			{
				value = m_a.m_parameter;
			}
			if(order == 4) 
			{
				::sprintf((char *)value.c_str(), "%d", m_h.m_idx);
			}
			if(order == 5)
			{
				value = m_h.m_parameter;
			}
			if(order == 6) 
			{
				::sprintf((char *)value.c_str(), "%d", m_toc.m_idx);
			}
			if(order == 7)
			{
				value = m_toc.m_parameter;
			}
			if(order == 8) 
			{
				::sprintf((char *)value.c_str(), "%d", m_ro.m_idx);
			}
			if(order == 9)
			{
				value = m_ro.m_parameter;
			}
			if(order == 10) 
			{
				::sprintf((char *)value.c_str(), "%d", m_phi.m_idx);
			}
			if(order == 11)
			{
				value = m_phi.m_parameter;
			}
			if(order == 12) 
			{
				::sprintf((char *)value.c_str(), "%d", m_ra.m_idx);
			}
			if(order == 13)
			{
				value = m_ra.m_parameter;
			}
			if(order == 14) 
			{
				::sprintf((char *)value.c_str(), "%d", m_eur.m_idx);
			}
			if(order == 15)
			{
				value = m_eur.m_parameter;
			}
			if(order == 16) 
			{
				::sprintf((char *)value.c_str(), "%d", m_hh.m_idx);
			}
			if(order == 17)
			{
				value = m_hh.m_parameter;
			}
			if(order == 18) 
			{
				::sprintf((char *)value.c_str(), "%d", m_fmc.m_idx);
			}
			if(order == 19)
			{
				value = m_fmc.m_parameter;
			}
			if(order == 20) 
			{
				::sprintf((char *)value.c_str(), "%d", m_q.m_idx);
			}
			if(order == 21)
			{
				value = m_q.m_parameter;
			}
			if(order == 22) 
			{
				::sprintf((char *)value.c_str(), "%d", m_qminus.m_idx);
			}
			if(order == 23)
			{
				value = m_qminus.m_parameter;
			}
			if(order == 24) 
			{
				::sprintf((char *)value.c_str(), "%d", m_sg.m_idx);
			}
			if(order == 25)
			{
				value = m_sg.m_parameter;
			}
			if(order == 26) 
			{
				::sprintf((char *)value.c_str(), "%d", m_qq.m_idx);
			}
			if(order == 27)
			{
				value = m_qq.m_parameter;
			}
			if(order == 28) 
			{
				::sprintf((char *)value.c_str(), "%d", m_so.m_idx);
			}
			if(order == 29)
			{
				value = m_so.m_parameter;
			}
			if(order == 30) 
			{
				::sprintf((char *)value.c_str(), "%d", m_po.m_idx);
			}
			if(order == 31)
			{
				value = m_po.m_parameter;
			}
			if(order == 32) 
			{
				::sprintf((char *)value.c_str(), "%d", m_fvt.m_idx);
			}
			if(order == 33)
			{
				value = m_fvt.m_parameter;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0) 
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_a.m_idx = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_a.m_parameter = value;
			}
			if(order == 4) 
			{
				m_h.m_idx = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_h.m_parameter = value;
			}
			if(order == 6) 
			{
				m_toc.m_idx = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_toc.m_parameter = value;
			}
			if(order == 8) 
			{
				m_ro.m_idx = ::atoi(value.c_str());
			}
			if(order == 9)
			{
				m_ro.m_parameter = value;
			}
			if(order == 10) 
			{
				m_phi.m_idx = ::atoi(value.c_str());
			}
			if(order == 11)
			{
				m_phi.m_parameter = value;
			}
			if(order == 12) 
			{
				m_ra.m_idx = ::atoi(value.c_str());
			}
			if(order == 13)
			{
				m_ra.m_parameter = value;
			}
			if(order == 14) 
			{
				m_eur.m_idx = ::atoi(value.c_str());
			}
			if(order == 15)
			{
				m_eur.m_parameter = value;
			}
			if(order == 16) 
			{
				m_hh.m_idx = ::atoi(value.c_str());
			}
			if(order == 17)
			{
				m_hh.m_parameter = value;
			}
			if(order == 18) 
			{
				m_fmc.m_idx = ::atoi(value.c_str());
			}
			if(order == 19)
			{
				m_fmc.m_parameter = value;
			}
			if(order == 20) 
			{
				m_q.m_idx = ::atoi(value.c_str());
			}
			if(order == 21)
			{
				m_q.m_parameter = value;
			}
			if(order == 22) 
			{
				m_qminus.m_idx = ::atoi(value.c_str());
			}
			if(order == 23)
			{
				m_qminus.m_parameter = value;
			}
			if(order == 24) 
			{
				m_sg.m_idx = ::atoi(value.c_str());
			}
			if(order == 25)
			{
				m_sg.m_parameter = value;
			}
			if(order == 26) 
			{
				m_qq.m_idx = ::atoi(value.c_str());
			}
			if(order == 27)
			{
				m_qq.m_parameter = value;
			}
			if(order == 28) 
			{
				m_so.m_idx = ::atoi(value.c_str());
			}
			if(order == 29)
			{
				m_so.m_parameter = value;
			}
			if(order == 30) 
			{
				m_po.m_idx = ::atoi(value.c_str());
			}
			if(order == 31)
			{
				m_po.m_parameter = value;
			}
			if(order == 32) 
			{
				m_fvt.m_idx = ::atoi(value.c_str());
			}
			if(order == 33)
			{
				m_fvt.m_parameter = value;
			}
		}
	};







		/*!
	*
	**/
	struct OverallShaleWellRecord : public PropertyRecord
	{
		// area of assessment unit[km2]
		ProbabilityField m_a	 ;
		ProbabilityField m_h	 ;
		ProbabilityField m_q	 ;
		ProbabilityField m_qminus;
		ProbabilityField m_eur	 ;
		ProbabilityField m_hh	 ;
		ProbabilityField m_po	 ;
		ProbabilityField m_fvt	 ;

		/*!
		*
		**/
		const OverallShaleWellRecord &operator=(const OverallShaleWellRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_a		 =other.m_a	 ;
			m_h		 =other.m_h	 ;
			m_q		 =other.m_q	 ;
			m_qminus =other.m_qminus;
			m_eur	 =other.m_eur	 ;
			m_hh	 =other.m_hh	 ;
			m_po	 =other.m_po	 ;
			m_fvt	 =other.m_fvt	 ;
			
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 8 * 2 + 2;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}
		/*!
		*
		**/
		void GetFldDesc(int order, string &desc)
		{
			order -= 2;
			if(order >= 0  && order <= 1)
			{
				desc = "单井泄油面积";
			}
			if(order >= 2 && order <= 3)
			{
				desc = "有效厚度";
			}
			if(order >= 4 && order <= 5)
			{
				desc = "单井累计产量";
			}
			if(order >= 6 && order <= 7)
			{
				desc = "单井平均日产";
			}
			if(order >= 8 && order <= 9)
			{
				desc = "单井可采储量";
			}
			if(order >= 10 && order <= 11)
			{
				desc = "埋深";
			}
			if(order >= 12 && order <= 13)
			{
				desc = "原油密度";
			}
			if(order >= 14 && order <= 15)
			{
				desc = "体积参数";
			}
			
	
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_a.m_idx);
			}
			if(order == 3)
			{
				value = m_a.m_parameter;
			}
			if(order == 4) 
			{
				::sprintf((char *)value.c_str(), "%d", m_h.m_idx);
			}
			if(order == 5)
			{
				value = m_h.m_parameter;
			}
			if(order == 6) 
			{
				::sprintf((char *)value.c_str(), "%d", m_q.m_idx);
			}
			if(order ==7)
			{
				value = m_q.m_parameter;
			}
			if(order == 8) 
			{
				::sprintf((char *)value.c_str(), "%d", m_qminus.m_idx);
			}
			if(order == 9)
			{
				value = m_qminus.m_parameter;
			}
			if(order == 10) 
			{
				::sprintf((char *)value.c_str(), "%d", m_eur.m_idx);
			}
			if(order == 11)
			{
				value = m_eur.m_parameter;
			}
			if(order == 12) 
			{
				::sprintf((char *)value.c_str(), "%d", m_hh.m_idx);
			}
			if(order == 13)
			{
				value = m_hh.m_parameter;
			}
			if(order == 14) 
			{
				::sprintf((char *)value.c_str(), "%d", m_po.m_idx);
			}
			if(order == 15)
			{
				value = m_po.m_parameter;
			}
			if(order == 16) 
			{
				::sprintf((char *)value.c_str(), "%d", m_fvt.m_idx);
			}
			if(order == 17)
			{
				value = m_fvt.m_parameter;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0) 
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_a.m_idx = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_a.m_parameter = value;
			}
			if(order == 4) 
			{
				m_h.m_idx = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_h.m_parameter = value;
			}
			if(order == 6) 
			{
				m_q.m_idx = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_q.m_parameter = value;
			}
			if(order == 8) 
			{
				m_qminus.m_idx = ::atoi(value.c_str());
			}
			if(order == 9)
			{
				m_qminus.m_parameter = value;
			}
			if(order == 10) 
			{
				m_eur.m_idx = ::atoi(value.c_str());
			}
			if(order == 11)
			{
				m_eur.m_parameter = value;
			}
			if(order == 12) 
			{
				m_hh.m_idx = ::atoi(value.c_str());
			}
			if(order == 13)
			{
				m_hh.m_parameter = value;
			}
			if(order == 14) 
			{
				m_po.m_idx = ::atoi(value.c_str());
			}
			if(order == 15)
			{
				m_po.m_parameter = value;
			}
			if(order == 16) 
			{
				m_fvt.m_idx = ::atoi(value.c_str());
			}
			if(order == 17)
			{
				m_fvt.m_parameter = value;
			}
		}
	};


	/*!
	*
	**/
	struct GeologyRecord : public PropertyRecord
	{
		// references
		string  m_basinTypeIdx;
		string  m_playTypeIdx;
		string  m_environmentIdx;
		string  m_formationIdx;
		string  m_beltTypeIdx;
		string  m_explorationDegreeIdx;
		string  m_thermalHistoryIdx;
		string  m_tectonicStrengthIdx;
		long  m_tectonicNumber;
		long  m_drillFootage;
		long  m_timeToFound;
		float m_maxArea;
		float m_maxBuryDepth;
		float m_rockMaxThickness;
		float m_rockAvgThickness;
		float m_rockMinThickness;
		float m_rockVolume;
		float m_rockMaxVelocity;
		float m_rockAvgVelocity;
		float m_rockMinVelocity;
		float m_rockMaxAge;
		float m_thermalSurface;
		float m_thermalGradient;
		float m_thermalHFU;

		string m_primarystructure	;
		string m_secstructure		;
		float  m_assarea			;
		float  m_arearatio			;
		float  m_successrate		;
		string m_geographyposition	;
		string m_tectonicposition	;
		string m_tectonictype		;
		string m_foundwell			;

		//2017/10/26: new variables
		std::string m_chronology;
		double m_wildcatwells;
		double m_seismiclength;
		double m_seismicarea;

		/*!
		*
		**/
		GeologyRecord() 
		{
			m_basinTypeIdx = "";
			m_playTypeIdx = "";
			m_environmentIdx = "";
			m_formationIdx = "";
			m_beltTypeIdx = "";
			m_explorationDegreeIdx = "";
			m_thermalHistoryIdx = "";
			m_tectonicStrengthIdx = "";

			m_tectonicNumber = 0;
			m_drillFootage = 0;
			m_timeToFound = 0;
			m_maxArea = 0.;
			m_maxBuryDepth = 0.;
			m_rockMaxThickness = 0.;
			m_rockAvgThickness = 0.;
			m_rockMinThickness = 0.;
			m_rockVolume = 0.;
			m_rockMaxVelocity = 0.;
			m_rockAvgVelocity = 0.;
			m_rockMinVelocity = 0.;
			m_rockMaxAge = 0.;
			m_thermalSurface = 0.;
			m_thermalGradient = 0.;
			m_thermalHFU = 0.;

			m_primarystructure	="";
			m_secstructure		="";
			m_assarea			=0;
			m_arearatio			=0;
			m_successrate		=0;
			m_geographyposition	="";
			m_tectonicposition	="";
			m_tectonictype		="";
			m_foundwell			="";

			//
			m_chronology = "";
			m_wildcatwells = 0.;
			m_seismiclength = 0.;
			m_seismicarea = 0.;

		}

		/*!
		*
		**/
		const GeologyRecord &operator=(const GeologyRecord &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			m_basinTypeIdx = other.m_basinTypeIdx;
			m_playTypeIdx = other.m_playTypeIdx;
			m_environmentIdx = other.m_environmentIdx;
			m_formationIdx = other.m_formationIdx;
			m_beltTypeIdx = other.m_beltTypeIdx;
			m_explorationDegreeIdx = other.m_explorationDegreeIdx;
			m_thermalHistoryIdx = other.m_thermalHistoryIdx;
			m_tectonicStrengthIdx = other.m_tectonicStrengthIdx;

			m_tectonicNumber = other.m_tectonicNumber;
			m_drillFootage = other.m_drillFootage;
			m_timeToFound = other.m_timeToFound;
			m_maxArea = other.m_maxArea;
			m_maxBuryDepth = other.m_maxBuryDepth;
			m_rockMaxThickness = other.m_rockMaxThickness;
			m_rockAvgThickness = other.m_rockAvgThickness;
			m_rockMinThickness = other.m_rockMinThickness;
			m_rockVolume = other.m_rockVolume;
			m_rockMaxVelocity = other.m_rockMaxVelocity;
			m_rockAvgVelocity = other.m_rockAvgVelocity;
			m_rockMinVelocity = other.m_rockMinVelocity;
			m_rockMaxAge = other.m_rockMaxAge;
			m_thermalSurface = other.m_thermalSurface;
			m_thermalGradient = other.m_thermalGradient;
			m_thermalHFU = other.m_thermalHFU;

			m_primarystructure	=other.m_primarystructure	;
			m_secstructure		=other.m_secstructure		;
			m_assarea			=other.m_assarea			;
			m_arearatio			=other.m_arearatio			;
			m_successrate		=other.m_successrate		;
			m_geographyposition	=other.m_geographyposition	;
			m_tectonicposition	=other.m_tectonicposition	;
			m_tectonictype		=other.m_tectonictype		;
			m_foundwell			=other.m_foundwell			;

			//
			m_chronology = other.m_chronology;
			m_wildcatwells = other.m_wildcatwells;
			m_seismiclength = other.m_seismiclength;
			m_seismicarea = other.m_seismicarea;

			//
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
			return 35 + 4;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid"				;type=0;}
			if(order == 1){value = "elementid"				;type=0;}
			if(order == 2){value = "basintypeid"			;type=2;}
			if(order == 3){value = "playtypeid"				;type=2;}
			if(order == 4){value = "environmentid"			;type=2;}
			if(order == 5){value = "formaitonid"			;type=2;}
			if(order == 6){value = "belttypeid"				;type=2;}
			if(order == 7){value = "explorationdegreeid" 	;type=2;}
			if(order == 8){value = "thermalhistoryid"		;type=2;}
			if(order == 9){value = "tectonicstrengthid"		;type=2;}
			if(order ==10){value = "tectonicnumber"			;type=0;}
			if(order ==11){value = "drillfootage"			;type=0;}
			if(order ==12){value = "timetofound"			;type=0;}
			if(order ==13){value = "maxarea"				;	type=1;}
			if(order ==14){value = "maxburydepth"			;	type=1;}
			if(order ==15){value = "rockmaxthickness"		;		type=1;}
			if(order ==16){value = "rockavgthickness"		;		type=1;}
			if(order ==17){value = "rockminthickness"		;	type=1;}
			if(order ==18){value = "rockvolume"				;type=1;}
			if(order ==19){value = "rockmaxvelocity"		;		type=1;}
			if(order ==20){value = "rockavgvelocity"		;		type=1;}
			if(order ==21){value = "rockminvelocity"		;		type=1;}
			if(order ==22){value = "rockmaxage"				;type=1;}
			if(order ==23){value = "thermalsurface"			;	type=1;}
			if(order ==24){value = "thermalgradient"		;type=1;}
			if(order ==25){value = "thermalhfu";		   ; type=1;}

			if(order ==26){value = "primarystructure";		   ; type=2;}
			if(order ==27){value = "secstructure";		   ; type=2;}
			if(order ==28){value = "assarea";		   ; type=1;}
			if(order ==29){value = "arearatio";		   ; type=1;}
			if(order ==30){value = "successrate";		   ; type=1;}
			if(order ==31){value = "geographyposition";		   ; type=2;}
			if(order ==32){value = "tectonicposition";		   ; type=2;}
			if(order ==33){value = "tectonictype";		   ; type=2;}
			if(order ==34){value = "foundwell";		   ; type=2;}

			//
			if(order ==35){value = "chronology";		   ; type=2;}
			if(order ==36){value = "wildcatwells";		   ; type=1;}
			if(order ==37){value = "seismiclength";		   ; type=1;}
			if(order ==38){value = "seismicarea";		   ; type=1;}

		}			  

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value= m_basinTypeIdx.c_str();
			}
			if(order == 3)
			{
				value= m_playTypeIdx.c_str();
			}
			if(order == 4)
			{
				value= m_environmentIdx.c_str();
			}
			if(order == 5)
			{
				value= m_formationIdx.c_str();
			}
			if(order == 6)
			{
				value= m_beltTypeIdx.c_str();
			}
			if(order == 7)
			{
				value= m_explorationDegreeIdx.c_str();
			}
			if(order == 8)
			{
				value= m_thermalHistoryIdx.c_str();
			}
			if(order == 9)
			{
				value= m_tectonicStrengthIdx.c_str();
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%d", m_tectonicNumber);;
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%d", m_drillFootage);;
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%d", m_timeToFound);;
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxArea);;
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxBuryDepth);;
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockMaxThickness);;
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockAvgThickness);;
			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockMinThickness);;
			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockVolume);;
			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockMaxVelocity);;
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockAvgVelocity);;
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockMinVelocity);;
			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockMaxAge);;
			}
			if(order == 23)
			{
				::sprintf((char *)value.c_str(), "%f", m_thermalSurface);;
			}
			if(order == 24)
			{
				::sprintf((char *)value.c_str(), "%f", m_thermalGradient);;
			}
			if(order == 25)
			{
				::sprintf((char *)value.c_str(), "%f", m_thermalHFU);;
			}


			if(order == 26)
			{
				value=m_primarystructure.c_str();
			}
			if(order == 27)
			{
				value=m_secstructure.c_str();
			}

			if(order == 28)
			{
				::sprintf((char *)value.c_str(), "%f", m_assarea);;
			}
			if(order == 29)
			{
				::sprintf((char *)value.c_str(), "%f", m_arearatio);;
			}
			if(order == 30)
			{
				::sprintf((char *)value.c_str(), "%f", m_successrate);;
			}

			if(order == 31)
			{
				value=m_geographyposition.c_str();
			}
			if(order == 32)
			{
				value=m_tectonicposition.c_str();
			}
			if(order == 33)
			{
				value=m_tectonictype.c_str();
			}
			if(order == 34)
			{
				value=m_foundwell.c_str();
			}

			//
			if(order == 35)
			{
				value = m_chronology.c_str();
			}
			if(order == 36)
			{
				::sprintf((char *)value.c_str(), "%f", m_wildcatwells);
			}
			if(order == 37)
			{
				::sprintf((char *)value.c_str(), "%f", m_seismiclength);
			}
			if(order == 38)
			{
				::sprintf((char *)value.c_str(), "%f", m_seismicarea);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_basinTypeIdx = value.c_str();
			}
			if(order == 3)
			{
				m_playTypeIdx = value.c_str();
			}
			if(order == 4)
			{
				m_environmentIdx = value.c_str();
			}
			if(order == 5)
			{
				m_formationIdx = value.c_str();
			}
			if(order == 6)
			{
				m_beltTypeIdx = value.c_str();
			}
			if(order == 7)
			{
				m_explorationDegreeIdx = value.c_str();
			}
			if(order == 8)
			{
				m_thermalHistoryIdx = value.c_str();
			}
			if(order == 9)
			{
				m_tectonicStrengthIdx = value.c_str();
			}
			if(order == 10)
			{
				m_tectonicNumber = ::atoi(value.c_str());
			}
			if(order == 11)
			{
				m_drillFootage = ::atoi(value.c_str());
			}
			if(order == 12)
			{
				m_timeToFound = ::atoi(value.c_str());
			}
			if(order == 13)
			{
				m_maxArea = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_maxBuryDepth = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_rockMaxThickness = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_rockAvgThickness = ::atof(value.c_str());
			}
			if(order == 17)
			{
				m_rockMinThickness = ::atof(value.c_str());
			}
			if(order == 18)
			{
				m_rockVolume = ::atof(value.c_str());
			}
			if(order == 19)
			{
				m_rockMaxVelocity = ::atof(value.c_str());
			}
			if(order == 20)
			{
				m_rockAvgVelocity = ::atof(value.c_str());
			}
			if(order == 21)
			{
				m_rockMinVelocity = ::atof(value.c_str());
			}
			if(order == 22)
			{
				m_rockMaxAge = ::atof(value.c_str());
			}
			if(order == 23)
			{
				m_thermalSurface = ::atof(value.c_str());
			}
			if(order == 24)
			{
				m_thermalGradient = ::atof(value.c_str());
			}
			if(order == 25)
			{
				m_thermalHFU = ::atof(value.c_str());
			}

			if(order == 26)
			{
				m_primarystructure=value.c_str();
			}
			if(order == 27)
			{
				m_secstructure=value.c_str();
			}

			if(order == 28)
			{
				m_assarea= ::atof(value.c_str());
			}
			if(order == 29)
			{
				m_arearatio= ::atof(value.c_str());
			}
			if(order == 30)
			{
				m_successrate= ::atof(value.c_str());
			}

			if(order == 31)
			{
				m_geographyposition=value.c_str();
			}
			if(order == 32)
			{
				m_tectonicposition=value.c_str();
			}
			if(order == 33)
			{
				m_tectonictype = value.c_str();
			}
			if(order == 34)
			{
				m_foundwell=value.c_str();
			}

			//
			if(order == 35)
			{
				m_chronology=value.c_str();
			}
			if(order == 36)
			{
				m_wildcatwells= ::atof(value.c_str());
			}
			if(order == 37)
			{
				m_seismiclength= ::atof(value.c_str());
			}
			if(order == 38)
			{
				m_seismicarea= ::atof(value.c_str());
			}

		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 2)
			{
				// m_basinTypeIdx;
				return Ref_Geology_Basin_Type;
			}
			if(order == 3)
			{
				// m_playTypeIdx;
				return Ref_Geology_Play_Type;
			}
			if(order == 4)
			{
				// m_environmentIdx = ::atoi(value.c_str());
				return Ref_Geology_Geographic_Environment;
			}
			if(order == 5)
			{
				// m_formationIdx
				return Ref_Geology_Formation_Type;
			}
			if(order == 6)
			{
				// m_beltTypeIdx
				return Ref_Geology_Structural_Belt;
			}
			if(order == 7)
			{
				// m_explorationDegreeIdx
				return Ref_Geology_Exploration_Degree;
			}
			if(order == 8)
			{
				// m_thermalHistoryIdx
				return Ref_Geology_Thermal_History;
			}
			if(order == 9)
			{
				// m_tectonicStrengthIdx
				return Ref_Geology_Tectonic_Strength;
			}

			return Ref_Unknown;
		}
	};

	/*!
	*
	**/
	struct SourceRecord : public PropertyRecord
	{
		string   m_horFromIdx;
		long   m_horToIdx;
		long   m_srcTypeIdx;
		string m_orgtype;
		string   m_pathwayIdx;
		string   m_supplywayIdx;
		double m_thermalGradient;
		double m_srcDensity;
		double m_roMax;
		double m_roAvg;
		double m_roMin;
		double m_sedCycle;
		double m_migDistance;
		double m_genVelocity;
		double m_genMax;
		double m_genAvg;
		double m_genMin;
		double m_genTime;
		double m_expulTime;
		double m_expulMax;
		double m_expulAvg;
		double m_expulMin;
		double m_remainedMax;
		double m_remainedAvg;
		double m_remainedMin;
		double m_srcMaxThick;
		double m_srcAvgThick;
		double m_srcMinThick;
		double m_srcMaxArea;
		double m_srcAvgArea;
		double m_srcMinArea;
		double m_srcMaxCoff;
		double m_srcAvgCoff;
		double m_srcMinCoff;
		double m_sandMaxPercent;
		double m_sandAvgPercent;
		double m_sandMinPercent;
		double m_srcMaxPercent;
		double m_srcAvgPercent;
		double m_srcMinPercent;
		double m_orgthickmax; 
		double m_orgthickmin; 
		double m_orgthickavg; 
		double m_orgcindex; 
		double m_orgyear; 
		double m_tocmax				;
		double m_tocavg				;
		double m_tocmin				;
		double m_hi					;
		string m_accumulationtime	;

		//2017/10/27: new variables
		double m_avgs1s2;
		double m_maxs1s2;
		double m_mins1s2;
		double m_avgs1;
		double m_maxs1;
		double m_mins1;
		double m_avgchloroa;
		double m_maxchloroa;
		double m_minchloroa;
		string m_organictype;
		double m_ks;
		double m_absorbedks;
		double m_ka;
		double m_absorbedka;
		double m_toc2srcmaxthick;
		double m_toc2srcavgthick;
		double m_toc2srcminthick;
		double m_toc2srcmaxarea;
		double m_toc2srcavgarea;
		double m_toc2srcminarea;

		/*!
		*
		**/
		SourceRecord()
		{
			m_horFromIdx = "";
			m_horToIdx = 0;
			m_srcTypeIdx = 0;
			m_orgtype = "";
			m_pathwayIdx = "";
			m_supplywayIdx = "";
		
			m_thermalGradient = 0.;
			m_srcDensity = 0.;
			m_roMax = 0.;
			m_roAvg = 0.;
			m_roMin = 0.;
			m_sedCycle = 0.;
			m_migDistance = 0.;
			m_genVelocity = 0.;
			m_genMax = 0.;
			m_genAvg = 0.;
			m_genMin = 0.;
			m_genTime = 0.;
			m_expulTime = 0.;
			m_expulMax = 0.;
			m_expulAvg = 0.;
			m_expulMin = 0.;
			m_remainedMax = 0.;
			m_remainedAvg = 0.;
			m_remainedMin = 0.;
			m_srcMaxThick = 0.;
			m_srcAvgThick = 0.;
			m_srcMinThick = 0.;
			m_srcMaxArea = 0.;
			m_srcAvgArea = 0.;
			m_srcMinArea = 0.;
			m_srcMaxCoff = 0.;
			m_srcAvgCoff = 0.;
			m_srcMinCoff = 0.;
			m_sandMaxPercent = 0.;
			m_sandAvgPercent = 0.;
			m_sandMinPercent = 0.;
			m_srcMaxPercent = 0.;
			m_srcAvgPercent = 0.;
			m_srcMinPercent = 0.;
			m_orgthickmax	=0.;
			m_orgthickmin	=0.;
			m_orgthickavg	=0.;
			m_orgcindex		=0.; 
			m_orgyear		=0.; 
			m_tocmax			=0;	
			m_tocavg			=0;	
			m_tocmin			=0;	
			m_hi				=0;	
			m_accumulationtime	="";

			//
			m_avgs1s2 = 0.;
			m_maxs1s2 = 0.;
			m_mins1s2 = 0.;
			m_avgs1 = 0.;
			m_maxs1 = 0.;
			m_mins1 = 0.;
			m_avgchloroa = 0.;
			m_maxchloroa = 0.;
			m_minchloroa = 0.;
			m_organictype = "";
			m_ks = 0.;
			m_absorbedks = 0.;
			m_ka = 0.;
			m_absorbedka = 0.;
			m_toc2srcmaxthick = 0.;
			m_toc2srcavgthick = 0.;
			m_toc2srcminthick = 0.;
			m_toc2srcmaxarea = 0.;
			m_toc2srcavgarea = 0.;
			m_toc2srcminarea = 0.;
		}

		/*!
		*
		**/
		const SourceRecord &operator=(const SourceRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			m_horFromIdx = other.m_horFromIdx;
			m_horToIdx = other.m_horToIdx;
			m_srcTypeIdx = other.m_srcTypeIdx;
			m_orgtype = other.m_orgtype;
			m_pathwayIdx = other.m_pathwayIdx;
			m_supplywayIdx = other.m_supplywayIdx;
		
			m_thermalGradient = other.m_thermalGradient;
			m_srcDensity = other.m_srcDensity;
			m_roMax = other.m_roMax;
			m_roAvg = other.m_roAvg;
			m_roMin = other.m_roMin;
			m_sedCycle = other.m_sedCycle;
			m_migDistance = other.m_migDistance;
			m_genVelocity = other.m_genVelocity;
			m_genMax = other.m_genMax;
			m_genAvg = other.m_genAvg;
			m_genMin = other.m_genMin;
			m_genTime = other.m_genTime;
			m_expulTime = other.m_expulTime;
			m_expulMax = other.m_expulMax;
			m_expulAvg = other.m_expulAvg;
			m_expulMin = other.m_expulMin;
			m_remainedMax = other.m_remainedMax;
			m_remainedAvg = other.m_remainedAvg;
			m_remainedMin = other.m_remainedMin;
			m_srcMaxThick = other.m_srcMaxThick;
			m_srcAvgThick = other.m_srcAvgThick;
			m_srcMinThick = other.m_srcMinThick;
			m_srcMaxArea = other.m_srcMaxArea;
			m_srcAvgArea = other.m_srcAvgArea;
			m_srcMinArea = other.m_srcMinArea;
			m_srcMaxCoff = other.m_srcMaxCoff;
			m_srcAvgCoff = other.m_srcAvgCoff;
			m_srcMinCoff = other.m_srcMinCoff;
			m_sandMaxPercent = other.m_sandMaxPercent;
			m_sandAvgPercent = other.m_sandAvgPercent;
			m_sandMinPercent = other.m_sandMinPercent;
			m_srcMaxPercent = other.m_srcMaxPercent;
			m_srcAvgPercent = other.m_srcAvgPercent;
			m_srcMinPercent = other.m_srcMinPercent;
			m_orgthickmax	=other.m_orgthickmax	;	
			m_orgthickmin	=other.m_orgthickmin	;
			m_orgthickavg	=other.m_orgthickavg	;
			m_orgcindex		=other.m_orgcindex		;
			m_orgyear		=other.m_orgyear		;

			m_tocmax			=other.m_tocmax				;	
			m_tocavg			=other.m_tocavg				;	
			m_tocmin			=other.m_tocmin				;	
			m_hi				=other.m_hi					;	
			m_accumulationtime	=other.m_accumulationtime	;

			//
			m_avgs1s2 = other.m_avgs1s2;
			m_maxs1s2 = other.m_maxs1s2;
			m_mins1s2 = other.m_mins1s2	;
			m_avgs1 = other.m_avgs1	;
			m_maxs1 = other.m_maxs1	;
			m_mins1 = other.m_mins1	;
			m_avgchloroa = other.m_avgchloroa	;
			m_maxchloroa = other.m_maxchloroa	;
			m_minchloroa = other.m_minchloroa	;
			m_organictype = other.m_organictype;
			m_ks = other.m_ks	;
			m_absorbedks = other.m_absorbedks	;
			m_ka = other.m_ka	;
			m_absorbedka = other.m_absorbedka	;
			m_toc2srcmaxthick = other.m_toc2srcmaxthick	;
			m_toc2srcavgthick = other.m_toc2srcavgthick	;
			m_toc2srcminthick = other.m_toc2srcminthick	;
			m_toc2srcmaxarea = other.m_toc2srcmaxarea	;
			m_toc2srcavgarea = other.m_toc2srcavgarea	;
			m_toc2srcminarea = other.m_toc2srcminarea	;

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
			return 52 + 20;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}


		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid"		;	type=0;}
			if(order == 1){value = "elementid"			;type=0;}
			if(order == 2){value = "horfromid"			;type=2;}
			if(order == 3){value = "hortoid"			;type=0;}
			if(order == 4){value = "srctypeid"			;type=0;}
			if(order == 5){value = "orgtype"			;type=2;}
			if(order == 6){value = "pathwayid"			;type=2;}
			if(order == 7){value = "supplywayid" 		;	type=2;}
			if(order == 8){value = "thermalgradient" 	;		type=1;}
			if(order == 9){value = "srcdensity"		;	type=1;}
			if(order ==10){value = "romax"				;type=1;}
			if(order ==11){value = "roavg"				;type=1;}
			if(order ==12){value = "romin"				;type=1;}
			if(order ==13){value = "sedcycle"			;type=1;}
			if(order ==14){value = "migdistance"		;	type=1;}
			if(order ==15){value = "genvelocity"		;	type=1;}
			if(order ==16){value = "genmax"			;type=1;}
			if(order ==17){value = "genavg"			;type=1;}
			if(order ==18){value = "genmin"			;type=1;}
			if(order ==19){value = "gentime"			;type=1;}
			if(order ==20){value = "expultime"			;type=1;}
			if(order ==21){value = "expulmax"			;type=1;}
			if(order ==22){value = "expulavg"			;type=1;}
			if(order ==23){value = "expulmin"			;type=1;}
			if(order ==24){value = "remainedmax"		;	type=1;}
			if(order ==25){value = "remainedavg"		;	type=1;}
			if(order ==26){value = "remainedmin"		;	type=1;}
			if(order ==27){value = "srcmaxthick"		;	type=1;}
			if(order ==28){value = "srcavgthick"		;	type=1;}
			if(order ==29){value = "srcminthick"		;	type=1;}
			if(order ==30){value = "srcmaxarea"		;	type=1;}
			if(order ==31){value = "srcavgarea"		;	type=1;}
			if(order ==32){value = "srcminarea"		;	type=1;}
			if(order ==33){value = "srcmaxcoff"		;	type=1;}
			if(order ==34){value = "srcavgcoff"		;	type=1;}
			if(order ==35){value = "srcmincoff"		;	type=1;}
			if(order ==36){value = "sandmaxpercent"	;		type=1;}
			if(order ==37){value = "sandavgpercent"	;		type=1;}
			if(order ==38){value = "sandminpercent"	;		type=1;}
			if(order ==39){value = "srcmaxpercent"		;	type=1;}
			if(order ==40){value = "srcavgpercent"		;	type=1;}
			if(order ==41){value = "srcminpercent"		;	type=1;}
			if(order ==42){value = "orgthickmax"		;	type=1;}
			if(order ==43){value = "orgthickmin"		;	type=1;}
			if(order ==44){value = "orgthickavg"		;	type=1;}
			if(order ==45){value = "orgcindex"		;	type=1;}
			if(order ==46){value = "orgyear"		;	type=1;}
			if(order ==47){value = "tocmax"					;	type=1;}
			if(order ==48){value = "tocavg"					;	type=1;}
			if(order ==49){value = "tocmin"					;	type=1;}
			if(order ==50){value = "hi"						;	type=1;}
			if(order ==51){value = "accumulationtime"		;	type=2;}

			//
			if(order ==52){value = "avgs1s2"		;	type=1;}
			if(order ==53){value = "maxs1s2"		;	type=1;}
			if(order ==54){value = "mins1s2"		;	type=1;}
			if(order ==55){value = "avgs1"		;	type=1;}
			if(order ==56){value = "maxs1"		;	type=1;}
			if(order ==57){value = "mins1"		;	type=1;}
			if(order ==58){value = "avgchloroa"					;	type=1;}
			if(order ==59){value = "maxchloroa"					;	type=1;}
			if(order ==60){value = "minchloroa"					;	type=1;}
			if(order ==61){value = "organictype"						;	type=2;}
			if(order ==62){value = "ks"		;	type=1;}
			if(order ==63){value = "absorbedks"		;	type=1;}
			if(order ==64){value = "ka"		;	type=1;}
			if(order ==65){value = "absorbedka"		;	type=1;}
			if(order ==66){value = "toc2srcmaxthick"		;	type=1;}
			if(order ==67){value = "toc2srcavgthick"		;	type=1;}
			if(order ==68){value = "toc2srcminthick"					;	type=1;}
			if(order ==69){value = "toc2srcmaxarea"					;	type=1;}
			if(order ==70){value = "toc2srcavgarea"					;	type=1;}
			if(order ==71){value = "toc2srcminarea"						;	type=1;}

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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value  = m_horFromIdx.c_str();
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_horToIdx);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_srcTypeIdx);
			}
			if(order == 5)
			{
				value  = m_orgtype.c_str();
			}
			if(order == 6)
			{
				value  = m_pathwayIdx.c_str();
			}
			if(order == 7)
			{
				value  = m_supplywayIdx.c_str();
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_thermalGradient);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcDensity);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_roMax);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_roAvg);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_roMin);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_sedCycle);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_migDistance);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_genVelocity);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_genMax);
			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_genAvg);
			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_genMin);
			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%f", m_genTime);
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_expulTime);
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_expulMax);
			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%f", m_expulAvg);
			}
			if(order == 23)
			{
				::sprintf((char *)value.c_str(), "%f", m_expulMin);
			}
			if(order == 24)
			{
				::sprintf((char *)value.c_str(), "%f", m_remainedMax);
			}
			if(order == 25)
			{
				::sprintf((char *)value.c_str(), "%f", m_remainedAvg);
			}
			if(order == 26)
			{
				::sprintf((char *)value.c_str(), "%f", m_remainedMin);
			}
			if(order == 27)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMaxThick);
			}
			if(order == 28)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcAvgThick);
			}
			if(order == 29)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMinThick);
			}
			if(order == 30)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMaxArea);
			}
			if(order == 31)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcAvgArea);
			}
			if(order == 32)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMinArea);
			}
			if(order == 33)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMaxCoff);
			}
			if(order == 34)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcAvgCoff);
			}
			if(order == 35)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMinCoff);
			}
			if(order == 36)
			{
				::sprintf((char *)value.c_str(), "%f", m_sandMaxPercent);
			}
			if(order == 37)
			{
				::sprintf((char *)value.c_str(), "%f", m_sandAvgPercent);
			}
			if(order == 38)
			{
				::sprintf((char *)value.c_str(), "%f", m_sandMinPercent);
			}
			if(order == 39)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMaxPercent);
			}
			if(order == 40)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcAvgPercent);
			}
			if(order == 41)
			{
				::sprintf((char *)value.c_str(), "%f", m_srcMinPercent);
			}
			if(order == 42)
			{
				::sprintf((char *)value.c_str(), "%f", m_orgthickmax);
			}
			if(order == 43)
			{
				::sprintf((char *)value.c_str(), "%f", m_orgthickmin);
			}
			if(order == 44)
			{
				::sprintf((char *)value.c_str(), "%f", m_orgthickavg);
			}
			if(order == 45)
			{
				::sprintf((char *)value.c_str(), "%f", m_orgcindex);
			}
			if(order == 46)
			{
				::sprintf((char *)value.c_str(), "%f", m_orgyear);
			}

			if(order == 47)
			{
				::sprintf((char *)value.c_str(), "%f", m_tocmax);
			}

			if(order == 48)
			{
				::sprintf((char *)value.c_str(), "%f", m_tocavg);
			}

			if(order == 49)
			{
				::sprintf((char *)value.c_str(), "%f", m_tocmin);
			}

			if(order == 50)
			{
				::sprintf((char *)value.c_str(), "%f", m_hi);
			}

			if(order == 51)
			{
				value = m_accumulationtime.c_str();
			}
			
			//
			if(order ==52){::sprintf((char *)value.c_str(), "%f", m_avgs1s2);}
			if(order ==53){::sprintf((char *)value.c_str(), "%f", m_maxs1s2);}
			if(order ==54){::sprintf((char *)value.c_str(), "%f", m_mins1s2);}
			if(order ==55){::sprintf((char *)value.c_str(), "%f", m_avgs1);}
			if(order ==56){::sprintf((char *)value.c_str(), "%f", m_maxs1);}
			if(order ==57){::sprintf((char *)value.c_str(), "%f", m_mins1);}
			if(order ==58){::sprintf((char *)value.c_str(), "%f", m_avgchloroa);}
			if(order ==59){::sprintf((char *)value.c_str(), "%f", m_maxchloroa);}
			if(order ==60){::sprintf((char *)value.c_str(), "%f", m_minchloroa);}
			if(order ==61){value = m_organictype.c_str();}
			if(order ==62){::sprintf((char *)value.c_str(), "%f", m_ks);}
			if(order ==63){::sprintf((char *)value.c_str(), "%f", m_absorbedks);}
			if(order ==64){::sprintf((char *)value.c_str(), "%f", m_ka);}
			if(order ==65){::sprintf((char *)value.c_str(), "%f", m_absorbedka);}
			if(order ==66){::sprintf((char *)value.c_str(), "%f", m_toc2srcmaxthick);}
			if(order ==67){::sprintf((char *)value.c_str(), "%f", m_toc2srcavgthick);}
			if(order ==68){::sprintf((char *)value.c_str(), "%f", m_toc2srcminthick);}
			if(order ==69){::sprintf((char *)value.c_str(), "%f", m_toc2srcmaxarea);}
			if(order ==70){::sprintf((char *)value.c_str(), "%f", m_toc2srcavgarea);}
			if(order ==71){::sprintf((char *)value.c_str(), "%f", m_toc2srcminarea);}

		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_horFromIdx = value.c_str();
			}
			if(order == 3)
			{
				m_horToIdx = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_srcTypeIdx = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_orgtype = value.c_str();
			}
			if(order == 6)
			{
				m_pathwayIdx = value.c_str();
			}
			if(order == 7)
			{
				m_supplywayIdx = value.c_str();
			}
			if(order == 8)
			{
				m_thermalGradient = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_srcDensity = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_roMax = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_roAvg = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_roMin = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_sedCycle = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_migDistance = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_genVelocity = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_genMax = ::atof(value.c_str());
			}
			if(order == 17)
			{
				m_genAvg = ::atof(value.c_str());
			}
			if(order == 18)
			{
				m_genMin = ::atof(value.c_str());
			}
			if(order == 19)
			{
				m_genTime = ::atof(value.c_str());
			}
			if(order == 20)
			{
				m_expulTime = ::atof(value.c_str());
			}
			if(order == 21)
			{
				m_expulMax = ::atof(value.c_str());
			}
			if(order == 22)
			{
				m_expulAvg = ::atof(value.c_str());
			}
			if(order == 23)
			{
				m_expulMin = ::atof(value.c_str());
			}
			if(order == 24)
			{
				m_remainedMax = ::atof(value.c_str());
			}
			if(order == 25)
			{
				m_remainedAvg = ::atof(value.c_str());
			}
			if(order == 26)
			{
				m_remainedMin = ::atof(value.c_str());
			}
			if(order == 27)
			{
				m_srcMaxThick = ::atof(value.c_str());
			}
			if(order == 28)
			{
				m_srcAvgThick = ::atof(value.c_str());
			}
			if(order == 29)
			{
				m_srcMinThick = ::atof(value.c_str());
			}
			if(order == 30)
			{
				m_srcMaxArea = ::atof(value.c_str());
			}
			if(order == 31)
			{
				m_srcAvgArea = ::atof(value.c_str());
			}
			if(order == 32)
			{
				m_srcMinArea = ::atof(value.c_str());
			}
			if(order == 33)
			{
				m_srcMaxCoff = ::atof(value.c_str());
			}
			if(order == 34)
			{
				m_srcAvgCoff = ::atof(value.c_str());
			}
			if(order == 35)
			{
				m_srcMinCoff = ::atof(value.c_str());
			}
			if(order == 36)
			{
				m_sandMaxPercent = ::atof(value.c_str());
			}
			if(order == 37)
			{
				m_sandAvgPercent = ::atof(value.c_str());
			}
			if(order == 38)
			{
				m_sandMinPercent = ::atof(value.c_str());
			}
			if(order == 39)
			{
				m_srcMaxPercent = ::atof(value.c_str());
			}
			if(order == 40)
			{
				m_srcAvgPercent = ::atof(value.c_str());
			}
			if(order == 41)
			{
				m_srcMinPercent = ::atof(value.c_str());
			}
			if(order == 42)
			{
				m_orgthickmax = ::atof(value.c_str());
			}
			if(order == 43)
			{
				m_orgthickmin = ::atof(value.c_str());
			}
			if(order == 44)
			{
				m_orgthickavg = ::atof(value.c_str());
			}
			if(order == 45)
			{
				m_orgcindex = ::atof(value.c_str());
			}
			if(order == 46)
			{
				m_orgyear = ::atof(value.c_str());
			}
			if(order == 47)
			{
				m_tocmax=::atof(value.c_str());
			}

			if(order == 48)
			{
				m_tocavg=::atof(value.c_str());
			}

			if(order == 49)
			{
				m_tocmin=::atof(value.c_str());
			}

			if(order == 50)
			{
				m_hi=::atof(value.c_str());
			}

			if(order == 51)
			{
				m_accumulationtime=value.c_str();
			}

			//
			if(order ==52){ m_avgs1s2=::atof(value.c_str());}
			if(order ==53){ m_maxs1s2=::atof(value.c_str());}
			if(order ==54){ m_mins1s2=::atof(value.c_str());}
			if(order ==55){ m_avgs1=::atof(value.c_str());}
			if(order ==56){ m_maxs1=::atof(value.c_str());}
			if(order ==57){ m_mins1=::atof(value.c_str());}
			if(order ==58){ m_avgchloroa=::atof(value.c_str());}
			if(order ==59){ m_maxchloroa=::atof(value.c_str());}
			if(order ==60){ m_minchloroa=::atof(value.c_str());}
			if(order ==61){ m_organictype = value.c_str();}
			if(order ==62){ m_ks=::atof(value.c_str());}
			if(order ==63){ m_absorbedks=::atof(value.c_str());}
			if(order ==64){ m_ka=::atof(value.c_str());}
			if(order ==65){ m_absorbedka=::atof(value.c_str());}
			if(order ==66){ m_toc2srcmaxthick=::atof(value.c_str());}
			if(order ==67){ m_toc2srcavgthick=::atof(value.c_str());}
			if(order ==68){ m_toc2srcminthick=::atof(value.c_str());}
			if(order ==69){ m_toc2srcmaxarea=::atof(value.c_str());}
			if(order ==70){ m_toc2srcavgarea=::atof(value.c_str());}
			if(order ==71){ m_toc2srcminarea=::atof(value.c_str());}
		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 2)
			{
				// m_horFromIdx
				return Ref_Unknown;
			}
			if(order == 3)
			{
				// m_horToIdx
				return Ref_Unknown;
			}
			if(order == 4)
			{
				// m_srcTypeIdx
				return Ref_Source_Rock_Type;
			}
			if(order == 5)
			{
				// m_orgTypeIdx
				return Ref_Source_Organic_Type;
			}
			if(order == 6)
			{
				// m_pathwayIdx
				return Ref_Source_Pathway_Type;
			}
			if(order == 7)
			{
				// m_supplywayIdx
				return Ref_Source_Supplyway_Type;
			}

			return Ref_Unknown;
		}
	};

	/*!
	*
	**/
	struct ReservoirRecord : public PropertyRecord
	{
		//
		std::string   m_horFromIdx;
		long   m_horToIdx;
		std::string   m_reservorTypeIdx;
		std::string   m_poretypeIdx;
		string m_face;
		
		double m_avgThickness;
		
		double m_maxDepth;
		double m_avgDepth;
		double m_minDepth;
		double m_maxPore;
		double m_avgPore;
		double m_minPore;
		double m_maxPerme;
		double m_avgPerme;
		double m_minPerme;
		
		double m_maxSand;
		double m_avgSand;
		double m_minSand;
		
		double m_maxThrout;
		double m_avgThrout;
		double m_minThrout;						
		string  m_sedcycle;
		string  m_subfacies;
		string  m_poretype;
		double  m_cements;
		double  m_claymineral;
		
		//2017/10/26: new variables
		double m_avgthickness;
		double m_minthickness;
		double m_maxthickness;
		string m_genrockphase;
		string m_oilcomposition;
		double m_oildensity;
		double m_reserviortempoil;
		string m_gascomposition;
		double m_reserviortempgas;
		double m_reservoirpres;
		double m_pressurecoef;
		double m_volumetricfactoroil;
		double m_oilcontent;
		double m_absorbedoil;
		double m_oilsaturation;
		double m_volumetricfactorgas;
		double m_gascontent;
		double m_absorbedgas;
		double m_gassaturation;
		string m_microfacies;
		string m_lithology;
		double m_brittlecontent;
		double m_elasticmodulus;
		double m_poissonratio;
		double m_rockdensity;
		double m_totalporosity;
		string m_microfracturedegree;
		

		/*!
		*
		**/
		ReservoirRecord()
		{
			m_horFromIdx = "";
			m_horToIdx = 0;
			m_reservorTypeIdx = "";
			m_poretypeIdx = "";
			m_face = "";
			m_avgThickness = 0.;
			m_maxDepth = 0.;
			m_avgDepth = 0.;
			m_minDepth = 0.;
			m_maxPore = 0.;
			m_avgPore = 0.;
			m_minPore = 0.;
			m_maxPerme = 0.;
			m_avgPerme = 0.;
			m_minPerme = 0.;
			m_maxSand = 0.;
			m_avgSand = 0.;
			m_minSand = 0.;
			m_maxThrout = 0.;
			m_avgThrout = 0.;
			m_minThrout = 0.;
			m_genrockphase="";

			m_sedcycle		="";	
			m_subfacies		="";	
			m_poretype		="";	
			m_cements		=0;	
			m_claymineral	=0;	

			//
			m_avgthickness = 0.;
			m_minthickness = 0.;
			m_maxthickness = 0.;
			m_genrockphase = "";
			m_oilcomposition = "";
			m_oildensity = 0.;
			m_reserviortempoil = 0.;
			m_gascomposition = "";
			m_reserviortempgas = 0.;
			m_reservoirpres = 0.;
			m_pressurecoef = 0.;
			m_volumetricfactoroil = 0.;
			m_oilcontent = 0.;
			m_absorbedoil = 0.;
			m_oilsaturation = 0.;
			m_volumetricfactorgas = 0.;
			m_gascontent = 0.;
			m_absorbedgas = 0.;
			m_gassaturation = 0.;
			m_microfacies = "";
			m_lithology = "";
			m_brittlecontent = 0.;
			m_elasticmodulus = 0.;
			m_poissonratio = 0.;
			m_rockdensity = 0.;
			m_totalporosity = 0.;
			m_microfracturedegree = "";
		}

		/*!
		*
		**/
		const ReservoirRecord &operator=(const ReservoirRecord &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			m_horFromIdx = other.m_horFromIdx;
			m_horToIdx = other.m_horToIdx;
			m_reservorTypeIdx = other.m_reservorTypeIdx;
			m_poretypeIdx = other.m_poretypeIdx;
			m_face= other.m_face;
			m_avgThickness = other.m_avgThickness;
			m_maxDepth = other.m_maxDepth;
			m_avgDepth = other.m_avgDepth;
			m_minDepth = other.m_minDepth;
			m_maxPore = other.m_maxPore;
			m_avgPore = other.m_avgPore;
			m_minPore = other.m_minPore;
			m_maxPerme = other.m_maxPerme;
			m_avgPerme = other.m_avgPerme;
			m_minPerme = other.m_minPerme;
			m_maxSand = other.m_maxSand;
			m_avgSand = other.m_avgSand;
			m_minSand = other.m_minSand;
			m_maxThrout = other.m_maxThrout;
			m_avgThrout = other.m_avgThrout;
			m_minThrout = other.m_minThrout;
			m_genrockphase = other.m_genrockphase;

			m_sedcycle			=other.m_sedcycle			;
			m_subfacies			=other.m_subfacies			;
			m_poretype			=other.m_poretype			;
			m_cements			=other.m_cements			;
			m_claymineral		=other.m_claymineral		;

			//
			m_avgthickness = other.m_avgthickness;
			m_minthickness = other.m_minthickness;
			m_maxthickness = other.m_maxthickness;
			m_genrockphase = other.m_genrockphase;
			m_oilcomposition = other.m_oilcomposition;
			m_oildensity = other.m_oildensity;
			m_reserviortempoil = other.m_reserviortempoil;
			m_gascomposition = other.m_gascomposition;
			m_reserviortempgas = other.m_reserviortempgas;
			m_reservoirpres = other.m_reservoirpres;
			m_pressurecoef = other.m_pressurecoef;
			m_volumetricfactoroil = other.m_volumetricfactoroil;
			m_oilcontent = other.m_oilcontent;
			m_absorbedoil = other.m_absorbedoil;
			m_oilsaturation = other.m_oilsaturation;
			m_volumetricfactorgas = other.m_volumetricfactorgas;
			m_gascontent = other.m_gascontent;
			m_absorbedgas = other.m_absorbedgas;
			m_gassaturation = other.m_gassaturation;
			m_microfacies = other.m_microfacies;
			m_lithology = other.m_lithology;
			m_brittlecontent = other.m_brittlecontent;
			m_elasticmodulus = other.m_elasticmodulus;
			m_poissonratio = other.m_poissonratio;
			m_rockdensity = other.m_rockdensity;
			m_totalporosity = other.m_totalporosity;
			m_microfracturedegree = other.m_microfracturedegree;

			//
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
			return 2 + 53;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid"			;type=0;}
			if(order == 1){value = "elementid"			;type=0;}
			if(order == 2){value = "horfromid"			;type=2;}
			if(order == 3){value = "hortoid"			;type=0;}
			if(order == 4){value = "reservortypeid"		;type=2;}
			if(order == 5){value = "poretypeid"			;type=2;}
			if(order == 6){value = "face"				;type=2;}
			if(order == 7){value = "thickness" 			;type=1;}
			if(order == 8){value = "maxdepth"			;type=1;}
			if(order == 9){value = "avgdepth"			;type=1;}
			if(order ==10){value = "mindepth"			;type=1;}
			if(order ==11){value = "maxpore"			;type=1;}
			if(order ==12){value = "avgpore"			;type=1;}
			if(order ==13){value = "minpore"			;type=1;}
			if(order ==14){value = "maxperme"			;type=1;}
			if(order ==15){value = "avgperme"			;type=1;}
			if(order ==16){value = "minperme"			;type=1;}
			if(order ==17){value = "maxsand"			;type=1;}
			if(order ==18){value = "avgsand"			;type=1;}
			if(order ==19){value = "minsand"			;type=1;}
			if(order ==20){value = "maxthrout"			;type=1;}
			if(order ==21){value = "avgthrout"			;type=1;}
			if(order ==22){value = "minthrout"			;type=1;}
			if(order ==23){value = "sedcycle"			;type=2;}
			if(order ==24){value = "subfacies"			;type=2;}
			if(order ==25){value = "poretype"			;type=2;}
			if(order ==26){value = "cements"			;type=1;}
			if(order ==27){value = "claymineral"		;type=1;}

			//
			if(order ==28){value = "avgthickness"			;type=1;}
			if(order ==29){value = "minthickness"			;type=1;}
			if(order ==30){value = "maxthickness"		;type=1;}
			if(order ==31){value = "diageneticstage"		;type=2;}//"genrockphase"
			if(order ==32){value = "oilcomposition"			;type=2;}
			if(order ==33){value = "oildensity"			;type=1;}
			if(order ==34){value = "reserviortempoil"		;type=1;}
			if(order ==35){value = "gascomposition"		;type=2;}
			if(order ==36){value = "reserviortempgas" ;type=1;}
			if(order ==37){value = "reservoirpres"			;type=1;}
			if(order ==38){value = "pressurecoef"		;type=1;}
			if(order ==39){value = "volumetricfactoroil"		;type=1;}
			if(order ==40){value = "oilcontent"		;type=1;}
			if(order ==41){value = "absorbedoil" ;type=1;}
			if(order ==42){value = "oilsaturation"			;type=1;}
			if(order ==43){value = "volumetricfactorgas"		;type=1;}
			if(order ==44){value = "gascontent"		;type=1;}
			if(order ==45){value = "absorbedgas"		;type=1;}
			if(order ==46){value = "gassaturation" ;type=1;}
			if(order ==47){value = "microfacies"			;type=2;}
			if(order ==48){value = "lithology"		;type=2;}
			if(order ==49){value = "brittlecontent"		;type=1;}
			if(order ==50){value = "elasticmodulus"		;type=1;}
			if(order ==51){value = "poissonratio"			;type=1;}
			if(order ==52){value = "rockdensity"			;type=1;}
			if(order ==53){value = "totalporosity"			;type=1;}
			if(order ==54){value = "microfracturedegree"	;type=2;}

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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value=m_horFromIdx.c_str();
				//::sprintf((char *)value.c_str(), "%d", m_horFromIdx);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_horToIdx);
			}
			if(order == 4)
			{
				value=m_reservorTypeIdx.c_str();
				//::sprintf((char *)value.c_str(), "%d", m_reservorTypeIdx);
			}
			if(order == 5)
			{
				value=m_poretypeIdx.c_str();
				//::sprintf((char *)value.c_str(), "%d", m_poretypeIdx);
			}
			if(order == 6)
			{
				value=m_face.c_str();
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgThickness);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxDepth);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgDepth);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_minDepth);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxPore);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgPore);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_minPore);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxPerme);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgPerme);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_minPerme);
			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxSand);
			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgSand);
			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%f", m_minSand);
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxThrout);
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgThrout);
			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%f", m_minThrout);
			}


			if(order == 23)
			{
				value=m_sedcycle.c_str();
			}

			if(order == 24)
			{
				value=m_subfacies.c_str();
			}

			if(order == 25)
			{
				value=m_poretype.c_str();
			}

			if(order == 26)
			{
				::sprintf((char *)value.c_str(), "%f", m_cements);
			}

			if(order == 27)
			{
				::sprintf((char *)value.c_str(), "%f", m_claymineral);
			}
			
			//2017/10/26: new variables
			if(order ==28)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgthickness);
			}
			if(order ==29)
			{
				::sprintf((char *)value.c_str(), "%f", m_minthickness);
			}
			if(order ==30)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxthickness);
			}
			if(order == 31)
			{
				value = m_genrockphase.c_str();
			}
			if(order == 32)
			{
				value = m_oilcomposition.c_str();
			}
			if(order == 33)
			{
				::sprintf((char *)value.c_str(), "%f", m_oildensity);
			}
			if(order == 34)
			{
				::sprintf((char *)value.c_str(), "%f", m_reserviortempoil);
			}
			if(order == 35)
			{
				value = m_gascomposition.c_str();
			}
			if(order == 36)
			{
				::sprintf((char *)value.c_str(), "%f", m_reserviortempgas);
			}
			if(order == 37)
			{
				::sprintf((char *)value.c_str(), "%f", m_reservoirpres);
			}
			if(order == 38)
			{
				::sprintf((char *)value.c_str(), "%f", m_pressurecoef);
			}
			if(order == 39)
			{
				::sprintf((char *)value.c_str(), "%f", m_volumetricfactoroil);
			}
			if(order == 40)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilcontent);
			}
			if(order == 41)
			{
				::sprintf((char *)value.c_str(), "%f", m_absorbedoil);
			}			
			if(order == 42)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilsaturation);
			}
			if(order == 43)
			{
				::sprintf((char *)value.c_str(), "%f", m_volumetricfactorgas);
			}
			if(order == 44)
			{
				::sprintf((char *)value.c_str(), "%f", m_gascontent);
			}
			if(order == 45)
			{
				::sprintf((char *)value.c_str(), "%f", m_absorbedgas);
			}
			if(order == 46)
			{
				::sprintf((char *)value.c_str(), "%f", m_gassaturation);
			}
			if(order == 47)
			{
				value = m_microfacies.c_str();
			}
			if(order == 48)
			{
				value = m_lithology.c_str();
			}
			if(order == 49)
			{
				::sprintf((char *)value.c_str(), "%f", m_brittlecontent);
			}
			if(order == 50)
			{
				::sprintf((char *)value.c_str(), "%f", m_elasticmodulus);
			}
			if(order == 51)
			{
				::sprintf((char *)value.c_str(), "%f", m_poissonratio);
			}
			if(order == 52)
			{
				::sprintf((char *)value.c_str(), "%f", m_rockdensity);
			}
			if(order == 53)
			{
				::sprintf((char *)value.c_str(), "%f", m_totalporosity);
			}
			if(order == 54)
			{
				value=m_microfracturedegree.c_str();
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_horFromIdx = value.c_str();
				//m_horFromIdx = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_horToIdx = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_reservorTypeIdx = value.c_str();
				//m_reservorTypeIdx = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_poretypeIdx = value.c_str();
				//m_poretypeIdx = ::atoi(value.c_str());
			}
			if(order == 6)
			{
				m_face = value.c_str();
			}
			if(order == 7)
			{
				m_avgThickness = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_maxDepth = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_avgDepth = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_minDepth = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_maxPore = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_avgPore = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_minPore = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_maxPerme = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_avgPerme = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_minPerme = ::atof(value.c_str());
			}
			if(order == 17)
			{
				m_maxSand = ::atof(value.c_str());
			}
			if(order == 18)
			{
				m_avgSand = ::atof(value.c_str());
			}
			if(order == 19)
			{
				m_minSand = ::atof(value.c_str());
			}
			if(order == 20)
			{
				m_maxThrout = ::atof(value.c_str());
			}
			if(order == 21)
			{
				m_avgThrout = ::atof(value.c_str());
			}
			if(order == 22)
			{
				m_minThrout = ::atof(value.c_str());
			}


			if(order == 23)
			{
				m_sedcycle = value.c_str();
			}

			if(order == 24)
			{
				m_subfacies = value.c_str();
			}

			if(order == 25)
			{
				m_poretype = value.c_str();
			}

			if(order == 26)
			{
				m_cements = ::atof(value.c_str());
			}

			if(order == 27)
			{
				m_claymineral = ::atof(value.c_str());
			}

			//2017/10/26: new variables
			if(order ==28)
			{
				m_avgthickness = ::atof(value.c_str());
			}
			if(order ==29)
			{
				m_minthickness = ::atof(value.c_str());
			}
			if(order ==30)
			{
				m_maxthickness = ::atof(value.c_str());
			}
			if(order == 31)
			{
				m_genrockphase = value.c_str();
			}
			if(order == 32)
			{
				m_oilcomposition = value.c_str();
			}
			if(order == 33)
			{
				m_oildensity = ::atof(value.c_str());
			}
			if(order == 34)
			{
				m_reserviortempoil = ::atof(value.c_str());
			}
			if(order == 35)
			{
				m_gascomposition = value.c_str();
			}
			if(order == 36)
			{
				m_reserviortempgas = ::atof(value.c_str());
			}
			if(order == 37)
			{
				m_reservoirpres = ::atof(value.c_str());
			}
			if(order == 38)
			{
				m_pressurecoef = ::atof(value.c_str());
			}
			if(order == 39)
			{
				m_volumetricfactoroil = ::atof(value.c_str());
			}
			if(order == 40)
			{
				m_oilcontent = ::atof(value.c_str());
			}
			if(order == 41)
			{
				m_absorbedoil = ::atof(value.c_str());
			}			
			if(order == 42)
			{
				m_oilsaturation = ::atof(value.c_str());
			}
			if(order == 43)
			{
				m_volumetricfactorgas = ::atof(value.c_str());
			}
			if(order == 44)
			{
				m_gascontent = ::atof(value.c_str());
			}
			if(order == 45)
			{
				m_absorbedgas = ::atof(value.c_str());
			}
			if(order == 46)
			{
				m_gassaturation = ::atof(value.c_str());
			}
			if(order == 47)
			{
				m_microfacies = value.c_str();
			}
			if(order == 48)
			{
				m_lithology = value.c_str();
			}
			if(order == 49)
			{
				m_brittlecontent = ::atof(value.c_str());
			}
			if(order == 50)
			{
				m_elasticmodulus = ::atof(value.c_str());
			}
			if(order == 51)
			{
				m_poissonratio = ::atof(value.c_str());
			}
			if(order == 52)
			{
				m_rockdensity = ::atof(value.c_str());
			}
			if(order == 53)
			{
				m_totalporosity = ::atof(value.c_str());
			}
			if(order == 54)
			{
				m_microfracturedegree = value.c_str();
			}
		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 2)
			{
				 // m_horFromIdx
				return Ref_Unknown;
			}
			if(order == 3)
			{
				// m_horToIdx
				return Ref_Unknown;
			}
			if(order == 4)
			{
				// m_reservorTypeIdx
				return Ref_Reservoir_Rock_Type;
			}
			if(order == 5)
			{
				// m_poretypeIdx
				return Ref_Reservoir_Pore_Type;
			}
			if(order == 6)
			{
				// m_faceIdx
				return Ref_Source_Face_Type;
			}

			return Ref_Unknown;
		}
	};

	/*!
	*
	*/
	struct CapRecord : public PropertyRecord
	{
		//
		long   m_horizonFromIdx;
		long   m_horizonToIdx;
		string   m_captype;
		double m_displacement;
		double m_maxPermiability;
		double m_avgPermiability;
		double m_minPermiability;
		double m_maxThickness;
		double m_avgThickness;
		double m_minThickness;
		double m_area;
		double m_areaCoff;
		double m_maxDepth;
		double m_avgDepth;
		double m_minDepth;	
		string m_capdestroydegree			;
		long   m_strumovenum				;
		string m_oilyeartotraprelation	;

		string m_caplithology ;
		double m_avgcaparea   ;
		double m_mincaparea   ;
		double m_maxcaparea   ;
		/*!
		*
		**/
		CapRecord()
		{
			m_horizonFromIdx = 0;
			m_horizonToIdx = 0;
			m_captype = "";
			m_displacement = 0.;
			m_maxPermiability = 0.;
			m_avgPermiability = 0.;
			m_minPermiability = 0.;
			m_maxThickness = 0.;
			m_avgThickness = 0.;
			m_minThickness = 0.;
			m_area = 0.;
			m_areaCoff = 0.;
			m_maxDepth = 0.;
			m_avgDepth = 0.;
			m_minDepth = 0.;
			m_capdestroydegree		="";	
			m_strumovenum			=0;		
			m_oilyeartotraprelation	="";

			m_caplithology ="";
			m_avgcaparea   =0;
			m_mincaparea   =0;
			m_maxcaparea   =0;
		}

		/*!
		*
		**/
		const CapRecord &operator=(const CapRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			m_horizonFromIdx = other.m_horizonFromIdx;
			m_horizonToIdx = other.m_horizonToIdx;
			m_captype = other.m_captype;
			m_displacement = other.m_displacement;
			m_maxPermiability = other.m_maxPermiability;
			m_avgPermiability = other.m_avgPermiability;
			m_minPermiability = other.m_minPermiability;
			m_maxThickness = other.m_maxThickness;
			m_avgThickness = other.m_avgThickness;
			m_minThickness = other.m_minThickness;
			m_area = other.m_area;
			m_areaCoff = other.m_areaCoff;
			m_maxDepth = other.m_maxDepth;
			m_avgDepth = other.m_avgDepth;
			m_minDepth = other.m_minDepth;	
			m_capdestroydegree		 =other.m_capdestroydegree		 ;
			m_strumovenum			 =other.m_strumovenum			 ;
			m_oilyeartotraprelation	 =other.m_oilyeartotraprelation	 ;

			m_caplithology =other.m_caplithology ;
			m_avgcaparea   =other.m_avgcaparea   ;
			m_mincaparea   =other.m_mincaparea   ;
			m_maxcaparea   =other.m_maxcaparea   ;

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
			return 24;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid"			;type=0;}
			if(order == 1){value = "elementid"			;type=0;}
			if(order == 2){value = "horizonfromidx"		;type=0;}
			if(order == 3){value = "horizontoidx"		;type=0;}
			if(order == 4){value = "captype"			;type=2;}
			if(order == 5){value = "displacement"		;type=1;}
			if(order == 6){value = "maxpermiability"	;type=1;}
			if(order == 7){value = "avgpermiability" 	;type=1;}
			if(order == 8){value = "minpermiability"	;type=1;}
			if(order == 9){value = "maxthickness"		;type=1;}
			if(order ==10){value = "avgthickness"		;type=1;}
			if(order ==11){value = "minthickness"		;type=1;}
			if(order ==12){value = "area"				;type=1;}
			if(order ==13){value = "areacoff"			;type=1;}
			if(order ==14){value = "maxdepth"			;type=1;}
			if(order ==15){value = "avgdepth"			;type=1;}
			if(order ==16){value = "mindepth"			;type=1;}
			if(order ==17){value = "capdestroydegree"			;type=2;}
			if(order ==18){value = "strumovenum"			;type=0;}
			if(order ==19){value = "oilyeartotraprelation"			;type=2;}

			if(order ==20){value = "caplithology"		;type=2;}
			if(order ==21){value = "avgcaparea"			;type=1;}
			if(order ==22){value = "mincaparea"			;type=1;}
			if(order ==23){value = "maxcaparea"			;type=1;}


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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_horizonFromIdx);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_horizonToIdx);
			}
			if(order == 4)
			{
				value=m_captype.c_str();
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_displacement);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxPermiability);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgPermiability);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_minPermiability);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxThickness);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgThickness);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_minThickness);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_area);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaCoff);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxDepth);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgDepth);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_minDepth);
			}
			if(order == 17)
			{
				value=m_capdestroydegree.c_str();
			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%d", m_strumovenum );
			}
			if(order == 19)
			{
				value=m_oilyeartotraprelation.c_str();
			}


			if(order == 20)
			{
				value=m_caplithology.c_str();
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgcaparea);
			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%f", m_mincaparea);
			}
			if(order == 23)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxcaparea);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_horizonFromIdx = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_horizonToIdx = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_captype = value.c_str();
			}
			if(order == 5)
			{
				m_displacement = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_maxPermiability = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_avgPermiability = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_minPermiability = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_maxThickness = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_avgThickness = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_minThickness = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_area = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_areaCoff = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_maxDepth = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_avgDepth = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_minDepth = ::atof(value.c_str());
			}
			if(order == 17)
			{
				m_capdestroydegree  = value.c_str();
			}
			if(order == 18)
			{
				m_strumovenum  = ::atoi(value.c_str());
			}
			if(order == 19)
			{
				m_oilyeartotraprelation  = value.c_str();
			}

			if(order == 20)
			{
				m_caplithology=value.c_str();
			}
			if(order == 21)
			{
				m_avgcaparea=::atof(value.c_str());
			}
			if(order == 22)
			{
				m_mincaparea=::atof(value.c_str());
			}
			if(order == 23)
			{
				m_maxcaparea=::atof(value.c_str());
			}
		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 2)
			{
				// m_horizonFromIdx
				return Ref_Unknown;
			}
			if(order == 3)
			{
				// m_horizonToIdx
				return Ref_Unknown;
			}
			if(order == 4)
			{
				// m_horizonToIdx
				return Ref_Cap_Rock_Type;
			}

			return Ref_Unknown;
		}
	};

	/*!
	*
	**/
	struct PreservationRecord : public PropertyRecord
	{
		//
		string   m_faultTypeIdx;
		long   m_faultNumber;
		string   m_waterTypeIdx;
		string   m_migrationRelationIdx;
		string   m_migrationWayIdx;
		long   m_compositionIdx;
		double m_maxErosionThick;
		double m_avgErosionThick;
		double m_minErosionThick;
		double m_maxErosionArea;
		double m_avgErosionArea;
		double m_minErosionArea;
		double m_waterPPM;
		double m_compositionNumber;
		double m_accumulationPeriod;

		string m_faultstrength;
		string m_tectonicactivity;

		//2017/10/27: new variables
		string m_overlyinglithology;
		string 	m_tectonicperiod;
		string 	m_fracturedegree;
		string 	m_hydrocondition;
		string 	m_sealtype;
		double	m_avgsealarea;
		double	m_maxsealarea;
		double	m_minsealarea;
		double	m_avgsealthickness;
		double	m_maxsealthickness;
		double	m_minsealthickness;
		long	m_prsdataupdate;
		long	m_prsdataindate;
		string 	m_systerm;
		string 	m_formation;
		string 	m_section;

		/*!
		*
		**/
		PreservationRecord()
		{
			m_faultTypeIdx = "";
			m_faultNumber = 0;
			m_waterTypeIdx = "";
			m_migrationRelationIdx = "";
			m_migrationWayIdx = "";
			m_compositionIdx = 0;

			m_maxErosionThick = 0.;
			m_avgErosionThick = 0.;
			m_minErosionThick = 0.;
			m_maxErosionArea = 0.;
			m_avgErosionArea = 0.;
			m_minErosionArea = 0.;
			m_waterPPM = 0.;
			m_compositionNumber = 0.;
			m_accumulationPeriod = 0.;

			m_faultstrength		="";
			m_tectonicactivity 	="";

			//
			m_overlyinglithology ="";
			m_tectonicperiod ="";
			m_fracturedegree ="";
			m_hydrocondition ="";
			m_sealtype ="";
			m_avgsealarea = 0.;
			m_maxsealarea = 0.;
			m_minsealarea = 0.;
			m_avgsealthickness = 0.;
			m_maxsealthickness = 0.;
			m_minsealthickness = 0.;
			m_prsdataupdate = 0;
			m_prsdataindate = 0;
			m_systerm ="";
			m_formation ="";
			m_section ="";
		}

		/*!
		*
		**/
		const PreservationRecord &operator=(const PreservationRecord &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			// itself
			m_faultTypeIdx = other.m_faultTypeIdx;
			m_faultNumber = other.m_faultNumber;
			m_waterTypeIdx = other.m_waterTypeIdx;
			m_migrationRelationIdx = other.m_migrationRelationIdx;
			m_migrationWayIdx = other.m_migrationWayIdx;
			m_compositionIdx = other.m_compositionIdx;

			m_maxErosionThick = other.m_maxErosionThick;
			m_avgErosionThick = other.m_avgErosionThick;
			m_minErosionThick = other.m_minErosionThick;
			m_maxErosionArea = other.m_maxErosionArea;
			m_avgErosionArea = other.m_avgErosionArea;
			m_minErosionArea = other.m_minErosionArea;
			m_waterPPM = other.m_waterPPM;
			m_compositionNumber = other.m_compositionNumber;
			m_accumulationPeriod = other.m_accumulationPeriod;

			m_faultstrength		=other.m_faultstrength		;
			m_tectonicactivity 	=other.m_tectonicactivity 	;

			//
			m_overlyinglithology = other.m_overlyinglithology;
			m_tectonicperiod = other.m_tectonicperiod;
			m_fracturedegree = other.m_fracturedegree;
			m_hydrocondition = other.m_hydrocondition;
			m_sealtype = other.m_sealtype;
			m_avgsealarea = other.m_avgsealarea;
			m_maxsealarea = other.m_maxsealarea;
			m_minsealarea = other.m_minsealarea;
			m_avgsealthickness = other.m_avgsealthickness;
			m_maxsealthickness = other.m_maxsealthickness;
			m_minsealthickness = other.m_minsealthickness;
			m_prsdataupdate = other.m_prsdataupdate;
			m_prsdataindate = other.m_prsdataindate;
			m_systerm = other.m_systerm;
			m_formation = other.m_formation;
			m_section = other.m_section;

			//
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
			return 19 + 16;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid"				;type=0;}
			if(order == 1){value = "elementid"				;type=0;}
			if(order == 2){value = "faulttypeidx"			;type=2;}
			if(order == 3){value = "faultnumber"			;type=0;}
			if(order == 4){value = "watertypeidx"			;type=2;}
			if(order == 5){value = "migrationrelationidx"	;type=2;}
			if(order == 6){value = "migrationwayidx"		;type=2;}
			if(order == 7){value = "compositionidx" 		;type=0;}
			if(order == 8){value = "maxerosionthick"		;type=1;}
			if(order == 9){value = "avgerosionthick"		;type=1;}
			if(order ==10){value = "minerosionthick"		;type=1;}
			if(order ==11){value = "maxerosionarea"			;type=1;}
			if(order ==12){value = "avgerosionarea"			;type=1;}
			if(order ==13){value = "minerosionarea"			;type=1;}
			if(order ==14){value = "waterppm"				;type=1;}
			if(order ==15){value = "compositionNumber"		;type=1;}
			if(order ==16){value = "accumulationPeriod"		;type=1;}

			if(order ==17){value = "faultstrength"		;type=2;}
			if(order ==18){value = "tectonicactivity"		;type=2;}
			
			//
			if(order == 19){value = "overlyinglithology"			;type=2;}
			if(order == 20){value = "tectonicperiod"				;type=2;}
			if(order == 21){value = "fracturedegree"			;type=2;}
			if(order == 22){value = "hydrocondition"			;type=2;}
			if(order == 23){value = "sealtype"			;type=2;}
			if(order == 24){value = "avgsealarea"		;type=1;}
			if(order == 25){value = "maxsealarea"		;type=1;}
			if(order == 26){value = "minsealarea" 		;type=1;}
			if(order == 27){value = "avgsealthickness"		;type=1;}
			if(order == 28){value = "maxsealthickness"		;type=1;}
			if(order == 29){value = "minsealthickness"		;type=1;}
			if(order == 30){value = "prsdataupdate"			;type=0;}
			if(order == 31){value = "prsdataindate"			;type=0;}
			if(order == 32){value = "system"			;type=2;}
			if(order == 33){value = "formation"				;type=2;}
			if(order == 34){value = "section"		;type=2;}
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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value = m_faultTypeIdx.c_str();
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_faultNumber);
			}
			if(order == 4)
			{
				value = m_waterTypeIdx.c_str();
			}
			if(order == 5)
			{
				value = m_migrationRelationIdx.c_str();
			}
			if(order == 6)
			{
				value = m_migrationWayIdx.c_str();
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%d", m_compositionIdx);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxErosionThick);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgErosionThick);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_minErosionThick);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_maxErosionArea);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_avgErosionArea);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_minErosionArea);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_waterPPM);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_compositionNumber);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_accumulationPeriod);
			}

			if(order == 17)
			{
				value=m_faultstrength.c_str();
			}

			if(order == 18)
			{
				value=m_tectonicactivity .c_str();
			}

			//
			if(order == 19){value = m_overlyinglithology .c_str();}
			if(order == 20){value = m_tectonicperiod .c_str();}
			if(order == 21){value = m_fracturedegree .c_str();}
			if(order == 22){value = m_hydrocondition.c_str();}
			if(order == 23){value = m_sealtype.c_str();}
			if(order == 24){::sprintf((char *)value.c_str(), "%f", m_avgsealarea);}
			if(order == 25){::sprintf((char *)value.c_str(), "%f", m_maxsealarea);}
			if(order == 26){::sprintf((char *)value.c_str(), "%f", m_minsealarea);}
			if(order == 27){::sprintf((char *)value.c_str(), "%f", m_avgsealthickness);}
			if(order == 28){::sprintf((char *)value.c_str(), "%f", m_maxsealthickness);}
			if(order == 29){::sprintf((char *)value.c_str(), "%f", m_minsealthickness);}
			if(order == 30){::sprintf((char *)value.c_str(), "%d", m_prsdataupdate);}
			if(order == 31){::sprintf((char *)value.c_str(), "%d", m_prsdataindate);}
			if(order == 32){value = m_systerm.c_str();}
			if(order == 33){value = m_formation.c_str();}
			if(order == 34){value = m_section.c_str();}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_faultTypeIdx = value.c_str();
			}
			if(order == 3)
			{
				m_faultNumber = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_waterTypeIdx = value.c_str();
			}
			if(order == 5)
			{
				m_migrationRelationIdx = value.c_str();
			}
			if(order == 6)
			{
				m_migrationWayIdx = value.c_str();
			}
			if(order == 7)
			{
				m_compositionIdx = ::atoi(value.c_str());
			}
			if(order == 8)
			{
				m_maxErosionThick = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_avgErosionThick = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_minErosionThick = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_maxErosionArea = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_avgErosionArea = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_minErosionArea = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_waterPPM = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_compositionNumber = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_accumulationPeriod = ::atof(value.c_str());
			}

			if(order == 17)
			{
				m_faultstrength=value.c_str();
			}

			if(order == 18)
			{
				m_tectonicactivity=value.c_str();
			}

			//
			if(order == 19){m_overlyinglithology = value .c_str();}
			if(order == 20){m_tectonicperiod = value .c_str();}
			if(order == 21){m_fracturedegree = value .c_str();}
			if(order == 22){m_hydrocondition = value.c_str();}
			if(order == 23){m_sealtype = value.c_str();}
			if(order == 24){m_avgsealarea = ::atof(value.c_str());}
			if(order == 25){m_maxsealarea = ::atof(value.c_str());}
			if(order == 26){m_minsealarea = ::atof(value.c_str());}
			if(order == 27){m_avgsealthickness = ::atof(value.c_str());}
			if(order == 28){m_maxsealthickness = ::atof(value.c_str());}
			if(order == 29){m_minsealthickness = ::atof(value.c_str());}
			if(order == 30){m_prsdataupdate = ::atoi(value.c_str());}
			if(order == 31){m_prsdataindate = ::atoi(value.c_str());}
			if(order == 32){m_systerm = value.c_str();}
			if(order == 33){m_formation = value.c_str();}
			if(order == 34){m_section = value.c_str();}
		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 2)
			{
				// m_faultTypeIdx
				return Ref_Preservation_Fault_Strength;
			}
			if(order == 4)
			{
				// m_waterTypeIdx
				return Ref_Preservation_Water_Type;
			}
			if(order == 5)
			{
				// m_migrationRelationIdx
				return Ref_Preservation_Migration_Relation;
			}
			if(order == 6)
			{
				// m_migrationWayIdx
				return Ref_Preservation_Migration_Way;
			}
			if(order == 7)
			{
				// m_compositionIdx
				return Ref_Preservation_Composition_Type;
			}

			return Ref_Unknown;
		}
	};

	/*!
	*
	**/
	struct TrapRecord : public PropertyRecord
	{
		long m_managementphase;//m_projectid
		long m_horizonFromIdx;
		long m_horizonToIdx;
		long m_trapTypeIdx;
		double m_rangeMaxHeight;
		double m_rangeAvgHeight;
		double m_areaClosure;
		double m_areaOilClosure;
		double m_areaGasClosure;
		double m_areaMaxCoff;
		double m_areaAvgCoff;
		double m_areaMinCoff;
		string m_formationTime;
		double m_knownArea;
		double m_predicationArea;
		double m_knownNumber;
		double m_predicationNumber;
		double m_reliability;
		double m_drillsuccess;
		string m_traptype;
		string m_seishorizon;
		string m_geohorizon;
		long   m_isrestoretrap;
		string m_trapsphasetype;

		//
		long m_isinuse;
		double m_highpointdepth;
		double m_highpointelevation;
		long m_trapfield;
		long m_childrennumber;
		long m_resourcetype;
		std::string	m_remark;

		/*!
		*
		**/
		TrapRecord()
		{
			m_managementphase = 0;

			m_horizonFromIdx = 0;
			m_horizonToIdx = 0;
			m_trapTypeIdx = 0;
			m_rangeMaxHeight = 0.;
			m_rangeAvgHeight = 0.;
			m_areaClosure = 0.;
			m_areaOilClosure = 0.;
			m_areaGasClosure = 0.;
			m_areaMaxCoff = 0.;
			m_areaAvgCoff = 0.;
			m_areaMinCoff = 0.;
			m_formationTime = "";
			m_knownArea = 0.;
			m_predicationArea = 0.;
			m_knownNumber = 0.;
			m_predicationNumber = 0.;
			m_reliability = 0.;
			m_drillsuccess = 0.;
			m_traptype = "";
			m_seishorizon = "";
			m_geohorizon = "";
			m_isrestoretrap=0;
			m_trapsphasetype="";

			//
			m_isinuse = false;
			m_highpointdepth = 0.;
			m_highpointelevation = 0.;
			m_trapfield = 0;
			m_childrennumber = 0;
			m_resourcetype = 0;
			m_remark ="";
		}

		/*!
		*
		**/
		const TrapRecord &operator=(const TrapRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			//2016/7/28:parent's items
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isAdded = other.m_isAdded;
			m_isDeleted = other.m_isDeleted;

			m_managementphase = other.m_managementphase;
			m_horizonFromIdx = other.m_horizonFromIdx;
			m_horizonToIdx = other.m_horizonToIdx;
			m_trapTypeIdx = other.m_trapTypeIdx;
			m_rangeMaxHeight = other.m_rangeMaxHeight;
			m_rangeAvgHeight = other.m_rangeAvgHeight;
			m_areaClosure = other.m_areaClosure;
			m_areaOilClosure = other.m_areaOilClosure;
			m_areaGasClosure = other.m_areaGasClosure;
			m_areaMaxCoff = other.m_areaMaxCoff;
			m_areaAvgCoff = other.m_areaAvgCoff;
			m_areaMinCoff = other.m_areaMinCoff;
			m_formationTime = other.m_formationTime;
			m_knownArea = other.m_knownArea;
			m_predicationArea = other.m_predicationArea;
			m_knownNumber = other.m_knownNumber;
			m_predicationNumber = other.m_predicationNumber;
			m_reliability = other.m_reliability;
			m_drillsuccess = other.m_drillsuccess;
			m_traptype = other.m_traptype;
			m_seishorizon = other.m_seishorizon;
			m_geohorizon = other.m_geohorizon;
			m_isrestoretrap =other.m_isrestoretrap;
			m_trapsphasetype=other.m_trapsphasetype;

			//
			m_isinuse = other.m_isinuse;
			
			m_highpointdepth = other.m_highpointdepth;
			m_highpointelevation = other.m_highpointelevation;
			m_trapfield = other.m_trapfield;
			m_childrennumber = other.m_childrennumber;
			m_resourcetype = other.m_resourcetype;
			m_remark  = other.m_remark;

			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 26 + 6;//
		}

		/*!
		*
		**/
		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			else if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			else if(order == 2)
			{
				value = "management phase";
				type=0;
			}
			else if(order == 3)
			{
				value = "horizonfromid";
				type=0;
			}
			else if(order == 4)
			{
				value = "horizontoid";
				type=0;
			}
			else if(order == 5)
			{
				value = "traptypeid";
				type=0;
			}
			else if(order == 6)
			{
				value = "rangemaxheight";
				type=1;
			}
			else if(order == 7)
			{
				value = "rangeavgheight";
				type=1;
			}
			else if(order == 8)
			{
				value = "areaclosure";
				type=1;
			}
			else if(order == 9)
			{
				value = "areaoilclosure";
				type=1;
			}
			else if(order == 10)
			{
				value = "areagasclosure";
				type=1;
			}
			else if(order ==11)
			{
				value = "areamaxcoff";
				type=1;
			}
			else if(order == 12)
			{
				value = "areaavgcoff";
				type=1;
			}
			else if(order == 13)
			{
				value = "areamincoff";
				type=1;
			}
			else if(order == 14)
			{
				value = "formationtime";
				type=2;
			}
			else if(order == 15)
			{
				value = "knownarea";
				type=1;
			}
			else if(order == 16)
			{
				value = "predicationarea";
				type=1;
			}
			else if(order == 17)
			{
				value = "knownnumber";
				type=1;
			}
			else if(order == 18)
			{
				value = "predicationnumber";
				type=1;
			}
			else if(order == 19)
			{
				value = "reliability";
				type=0;
			}
			else if(order == 20)
			{
				value = "drillsuccess";
				type=1;
			}
			else if(order == 21)
			{
				value = "traptype";
				type=2;
			}
			else if(order == 22)
			{
				value = "seismic horizon";
				type=2;
			}
			else if(order == 23)
			{
				value = "geology horizon";
				type=2;
			}
			else if(order == 24)
			{
				value = "isrestoretrap";
				type=0;
			}
			else if(order == 25)
			{
				value = "trapsphasetype";
				type=2;
			}
			//added fields
			else if (order == 26)
			{
				value = "high point depth";
				type=1;
			}
			else if (order == 27)
			{
				value = "high point elevation";
				type=1;
			}
			else if (order == 28)
			{
				value = "trap field";
				type=0;
			}
			else if (order == 29)
			{
				value = "children number";
				type=0;
			}
			else if (order == 30)
			{
				value = "resource type";
				type=0;
			}
			else if (order == 31)
			{
				value = "remark";
				type=2;
			}
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
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			else if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_horizonFromIdx);
			}
			else if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_horizonToIdx);
			}
			else if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%d", m_trapTypeIdx);
			}
			else if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_rangeMaxHeight);
			}
			else if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_rangeAvgHeight);
			}
			else if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaClosure);
			}
			else if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaOilClosure);
			}
			else if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaGasClosure);
			}
			else if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaMaxCoff);
			}
			else if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaAvgCoff);
			}
			else if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_areaMinCoff);
			}
			else if(order == 14)
			{
				value = m_formationTime;
			}
			else if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_knownArea);
			}
			else if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_predicationArea);
			}
			else if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_knownNumber);
			}
			else if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_predicationNumber);
			}
			else if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%f", m_reliability);
			}
			else if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_drillsuccess);
			}
			else if(order == 21)
			{
				//::sprintf((char *)value.c_str(), "%s", m_traptype);
				value = m_traptype;
			}
			else if(order == 22)
			{
				//::sprintf((char *)value.c_str(), "%s", m_seishorizon);
				value = m_seishorizon;
			}
			else if(order == 23)
			{
				//::sprintf((char *)value.c_str(), "%s", m_geohorizon);
				value = m_geohorizon;
			}
			//m_isrestoretrap;
			//m_trapsphasetype;
			else if(order == 24)
			{
				::sprintf((char *)value.c_str(), "%d", m_isrestoretrap);
			}
			else if(order == 25)
			{
				//::sprintf((char *)value.c_str(), "%s", m_geohorizon);
				value = m_trapsphasetype;
			}
			//added fields
			else if (order == 26)
			{
				::sprintf((char *)value.c_str(), "%f", m_highpointdepth);
			}
			else if (order == 27)
			{
				::sprintf((char *)value.c_str(), "%f", m_highpointelevation);
			}
			else if (order == 28)
			{
				::sprintf((char *)value.c_str(), "%d", m_trapfield);
			}
			else if (order == 29)
			{
				::sprintf((char *)value.c_str(), "%d", m_childrennumber);
			}
			else if (order == 30)
			{
				::sprintf((char *)value.c_str(), "%d", m_resourcetype);
			}
			else if (order == 31)
			{
				value = m_remark;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}
			else if(order == 3)
			{
				m_horizonFromIdx = ::atoi(value.c_str());
			}
			else if(order == 4)
			{
				m_horizonToIdx = ::atoi(value.c_str());
			}
			else if(order == 5)
			{
				m_trapTypeIdx = ::atoi(value.c_str());
			}
			else if(order == 6)
			{
				m_rangeMaxHeight = ::atof(value.c_str());
			}
			else if(order == 7)
			{
				m_rangeAvgHeight = ::atof(value.c_str());
			}
			else if(order == 8)
			{
				m_areaClosure = ::atof(value.c_str());
			}
			else if(order == 9)
			{
				m_areaOilClosure = ::atof(value.c_str());
			}
			else if(order == 10)
			{
				m_areaGasClosure = ::atof(value.c_str());
			}
			else if(order == 11)
			{
				m_areaMaxCoff = ::atof(value.c_str());
			}
			else if(order == 12)
			{
				m_areaAvgCoff = ::atof(value.c_str());
			}
			else if(order == 13)
			{
				m_areaMinCoff = ::atof(value.c_str());
			}
			else if(order == 14)
			{
				m_formationTime = value.c_str();
			}
			else if(order == 15)
			{
				m_knownArea = ::atof(value.c_str());
			}
			else if(order == 16)
			{
				m_predicationArea = ::atof(value.c_str());
			}
			else if(order == 17)
			{
				m_knownNumber = ::atof(value.c_str());
			}
			else if(order == 18)
			{
				m_predicationNumber = ::atof(value.c_str());
			}
			else if(order == 19)
			{
				m_reliability = ::atof(value.c_str());
			}
			else if(order == 20)
			{
				m_drillsuccess = ::atof(value.c_str());
			}
			else if(order == 21)
			{
				m_traptype = value.c_str();
			}
			else if(order == 22)
			{
				m_seishorizon = value.c_str();
			}
			else if(order == 23)
			{
				m_geohorizon = value.c_str();
			}
			//m_isrestoretrap;
			//m_trapsphasetype;
			else if(order == 24)
			{
				m_isrestoretrap = ::atoi(value.c_str());
			}
			else if(order == 25)
			{
				m_trapsphasetype = value.c_str();
			}
			//added fields
			else if (order == 26)
			{
				m_highpointdepth = ::atof(value.c_str());
			}
			else if (order == 27)
			{
				m_highpointelevation = ::atof(value.c_str());
			}
			else if (order == 28)
			{
				m_trapfield = ::atoi(value.c_str());
			}
			else if (order == 29)
			{
				m_childrennumber = ::atoi(value.c_str());
			}
			else if (order == 30)
			{
				m_resourcetype = ::atoi(value.c_str());
			}
			else if (order == 31)
			{
				m_remark = value;
			}
			
		}

		/*!
		*
		**/
		int GetReferenceType(int order)
		{
			if(order == 3)
			{
				// m_horizonFromIdx
				return Ref_Unknown;
			}
			if(order == 4)
			{
				// m_horizonToIdx
				return Ref_Unknown;
			}
			if(order == 5)
			{
				// m_trapTypeIdx
				return Ref_Geology_Trap_Type;
			}

			return Ref_Unknown;
		}
	};

	
	
	/*!
	*
	**/
	struct TrapExplorationRecord :public PropertyRecord
	{
		//0
		//1
		long   m_managementphase;
		double m_statdate;
		string m_drillstatus;
		string m_drillresult;
		string m_drillevaluation;
		string m_drillconclusion;
		double m_drilldate;
		string m_discoveryid;
		double m_discoverydate;
		long   m_drilled;//10
		long   m_drilling;
		double m_footage;
		long   m_tested;
		long   m_testing;
		long   m_successes;
		double m_oilresource;
		double m_gasresource;
		string m_remark;
		long   m_phasetype 	    ;
		string m_oilfieldname   ;//20
		string m_resourcekind   ;
		string m_seismiclength  ;
		string m_seismicarea 	;
		long   m_wells 		    ;
		long   m_lowwells 	    ;
		long   m_untested 	    ;
		long   m_untestedlogs   ;
		long   m_failedwell		;//28

		float  m_seic2ddiscovrate;//29
		float  m_newtraparea 	 ;//30
		float  m_yearnewseiclong ;//31
		float  m_seic3dprofit 	 ;//32
		float  m_newoilgasarea 	 ;//33
		float  m_seic3dworkarea  ;//34


		/*!
		*
		**/
		TrapExplorationRecord()
		{
			//m_trapIdx =0;
			m_managementphase=0;
			m_statdate =0.;
			m_drillstatus="";
			m_drillresult="";
			m_drillevaluation="";
			m_drillconclusion="";
			m_drilldate=0.;
			m_discoveryid="";
			m_discoverydate=0.;
			m_drilled=0;
			m_drilling=0;
			m_footage=0.;
			m_tested=0;
			m_testing=0;
			m_successes=0;
			m_oilresource=0.;
			m_gasresource=0.;
			m_remark="";
			m_phasetype 	=0    ;
			m_oilfieldname  ="" ;
			m_resourcekind  ="" ;
			m_seismiclength ="" ;
			m_seismicarea 	="";
			m_wells 		=0    ;
			m_lowwells 	    =0;
			m_untested 	    =0;
			m_untestedlogs  =0 ;
			m_failedwell    =0 ;
			m_seic2ddiscovrate =0;
			m_newtraparea 	   =0;
			m_yearnewseiclong  =0;
			m_seic3dprofit 	   =0;
			m_newoilgasarea    =0;
			m_seic3dworkarea   =0;
			
		}	
		
				/*!
		*
		**/
		const TrapExplorationRecord &operator=(const TrapExplorationRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
				m_managementphase	 =other.m_managementphase	;
			    m_statdate           =other.m_statdate          ;
				m_drillstatus		 =other.m_drillstatus		;
				m_drillresult		 =other.m_drillresult		;
				m_drillevaluation    =other.m_drillevaluation   ;
				m_drillconclusion	 =other.m_drillconclusion	;
				m_drilldate			 =other.m_drilldate			;
				m_discoveryid		 =other.m_discoveryid		;
				m_discoverydate		 =other.m_discoverydate		;
				m_drilled			 =other.m_drilled			;
				m_drilling			 =other.m_drilling			;
				m_footage			 =other.m_footage			;
				m_tested			 =other.m_tested			;
				m_testing			 =other.m_testing			;
				m_successes			 =other.m_successes			;
				m_oilresource		 =other.m_oilresource		;
				m_gasresource		 =other.m_gasresource		;
				m_remark			 =other.m_remark			;
				m_phasetype 	 	 =other.m_phasetype 	 	;
				m_oilfieldname   	 =other.m_oilfieldname   	;
				m_resourcekind   	 =other.m_resourcekind   	;
				m_seismiclength  	 =other.m_seismiclength  	;
				m_seismicarea 		 =other.m_seismicarea 		;
				m_wells 		 	 =other.m_wells 		 	;
				m_lowwells 	    	 =other.m_lowwells 	    	;
				m_untested 	    	 =other.m_untested 	    	;
				m_untestedlogs   	 =other.m_untestedlogs   	;
				m_failedwell		 =other.m_failedwell		;
				m_seic2ddiscovrate =other.m_seic2ddiscovrate	;
				m_newtraparea 	   =other.m_newtraparea 		;
				m_yearnewseiclong  =other.m_yearnewseiclong		;
				m_seic3dprofit 	   =other.m_seic3dprofit 		;
				m_newoilgasarea    =other.m_newoilgasarea		;
				m_seic3dworkarea   =other.m_seic3dworkarea		;
				
				return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 36;//36: contains m_managementphase
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 )
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;
				
			}
			if(order == 2)
			{
				value = "managementphase";
				type=0;

			}
			if(order == 3)
			{
				value = "statdate";
				type=1;
				
			}
			if(order == 4)
			{
				value = "drillstatus";
				type=2;
				
			}
			if(order == 5)
			{
				value = "drillresult";
				type=2;
				
			}
			if(order == 6)
			{
				value = "drillevaluation";
				type=2;
				
			}
			if(order == 7)
			{
				value = "drillconclusion";
				type=2;
				
			}
			if(order == 8)
			{
				value = "drilldate";
				type=1;
				
			}
			if(order == 9)
			{
				value = "discoveryid";
				type=2;
				
			}
			if(order == 10)
			{
				value = "discoverydate";
				type=1;
				
			}
			if(order == 11)
			{
				value = "drilled";
				type=0;
				
			}
			if(order == 12)
			{
				value = "drilling";
				type=0;
				
			}
			if(order == 13)
			{
				value = "footage";
				type=1;
				
			}
			if(order == 14)
			{
				value = "tested";
				type=0;
				
			}
			if(order == 15)
			{
				value = "testing";
				type=0;
				
			}
			if(order == 16)
			{
				value = "successes";
				type=0;
				
			}
			if(order == 17)
			{
				value = "oilresource";
				type=1;
				
			}
			if(order == 18)
			{
				value = "gasresource";
				type=1;
				
			}
			if(order == 19)
			{
				value = "remark";
				type=2;
				
			}
			if(order == 20)
			{
				value = "phasetype";
				type=0;
				
			}
			if(order == 21)
			{
				value = "oilfieldname";
				type=2;
				
			}
			if(order == 22)
			{
				value = "resourcekind";
				type=2;
				
			}
			if(order == 23)
			{
				value = "seismiclength";
				type=2;
				
			}
			if(order == 24)
			{
				value = "seismicarea";
				type=2;
				
			}
			if(order == 25)
			{
				value = "wells";
				type=0;
				
			}
			if(order == 26)
			{
				value = "lowwells";
				type=0;
				
			}
			if(order == 27)
			{
				value = "untested";
				type=0;
				
			}
			if(order == 28)
			{
				value = "untestedlogs";
				type=0;
				
			}
			if(order == 29)
			{
				value = "failedwell";
				type=0;
			}
			/*m_seic2ddiscovrate
			m_newtraparea 	  
			m_yearnewseiclong 
			m_seic3dprofit 	  
			m_newoilgasarea   
			m_seic3dworkarea  
			m_optimyear		  
			m_optimnum		  */
			if(order == 30)
			{
				value = "seic2ddiscovrate";
				type=1;
			}
			if(order == 31)
			{
				value = "newtraparea";
				type=1;
			}
			if(order == 32)
			{
				value = "yearnewseiclong";
				type=1;
			}
			if(order == 33)
			{
				value = "seic3dprofit";
				type=1;
			}
			if(order == 34)
			{
				value = "newoilgasarea";
				type=1;
			}
			if(order == 35)
			{
				value = "seic3dworkarea";
				type=1;
			}
			
		}
	

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}

			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_statdate);
			}
			if(order == 4)
			{
				value = m_drillstatus;
			}
			if(order ==5)
			{
				value = m_drillresult;
			}
			if(order == 6)
			{
				value = m_drillevaluation;
			}
			if(order == 7)
			{
				value = m_drillconclusion;
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_drilldate);
			}
			if(order == 9)
			{
				value = m_discoveryid;
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_discoverydate);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%d", m_drilled);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%d", m_drilling);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_footage);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%d", m_tested);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%d", m_testing);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%d", m_successes);
			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilresource);
			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_gasresource);
			}
			if(order == 19)
			{
				value =  m_remark;
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%ld", m_phasetype);
			}
			if(order == 21)
			{
				value = m_oilfieldname;
			}
			if(order == 22)
			{
				value = m_resourcekind;
			}
			if(order == 23)
			{
				value = m_seismiclength;
			}
			if(order == 24)
			{
				value = m_seismicarea;
			}
			if(order == 25)
			{
				::sprintf((char *)value.c_str(), "%ld", m_wells);
			}
			if(order == 26)
			{
				::sprintf((char *)value.c_str(), "%ld", m_lowwells);
			}
			if(order == 27)
			{
				::sprintf((char *)value.c_str(), "%ld", m_untested);
			}
			if(order == 28)
			{
				::sprintf((char *)value.c_str(), "%ld", m_untestedlogs );
			}
			if(order == 29)
			{
				::sprintf((char *)value.c_str(), "%ld", m_failedwell );
			}
			/*m_seic2ddiscovrate
			m_newtraparea 	  
			m_yearnewseiclong 
			m_seic3dprofit 	  
			m_newoilgasarea   
			m_seic3dworkarea  
			m_optimyear		  
			m_optimnum		  */
			if(order == 30)
			{
				::sprintf((char *)value.c_str(), "%f", m_seic2ddiscovrate);
			}
			if(order == 31)
			{
				::sprintf((char *)value.c_str(), "%f", m_newtraparea);
			}
			if(order == 32)
			{
				::sprintf((char *)value.c_str(), "%f", m_yearnewseiclong);
			}
			if(order == 33)
			{
				::sprintf((char *)value.c_str(), "%f", m_seic3dprofit);
			}
			if(order == 34)
			{
				::sprintf((char *)value.c_str(), "%f", m_newoilgasarea);
			}
			if(order == 35)
			{
				::sprintf((char *)value.c_str(), "%f", m_seic3dworkarea);
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}

			if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}

			if(order == 3)
			{
				m_statdate = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_drillstatus = value;
			}
			if(order == 5)
			{
				m_drillresult = value;
			}
			if(order == 6)
			{
				m_drillevaluation = value;
			}
			if(order == 7)
			{
				m_drillconclusion = value;
			}
			if(order == 8)
			{
				m_drilldate = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_discoveryid = value;
			}
			if(order == 10)
			{
				m_discoverydate = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_drilled = ::atoi(value.c_str());
			}
			if(order == 12)
			{
				m_drilling = ::atoi(value.c_str());
			}
			if(order == 13)
			{
				m_footage = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_tested = ::atoi(value.c_str());
			}
			if(order == 15)
			{
				m_testing = ::atoi(value.c_str());
			}
			if(order == 16)
			{
				m_successes = ::atoi(value.c_str());
			}
			if(order == 17)
			{
				m_oilresource = ::atof(value.c_str());
			}
			if(order == 18)
			{
				m_gasresource = ::atof(value.c_str());
			}
			if(order == 19)
			{
				m_remark = value;
			}
			if(order == 20)
			{
				m_phasetype = ::atoi(value.c_str());
			}
			if(order == 21)
			{
				 m_oilfieldname = value;
			}
			if(order == 22)
			{
				  m_resourcekind=value;
			}
			if(order == 23)
			{
				m_seismiclength=value;
			}
			if(order == 24)
			{
				m_seismicarea=value;
			}
			if(order == 25)
			{
				m_wells = ::atoi(value.c_str());
			}
			if(order == 26)
			{
				m_lowwells = ::atoi(value.c_str());;
			}
			if(order == 27)
			{
				m_untested= ::atoi(value.c_str());
			}
			if(order == 28)
			{
				m_untestedlogs = ::atoi(value.c_str());
			}
			if(order == 29)
			{
				m_failedwell = ::atoi(value.c_str());
			}
			/*m_seic2ddiscovrate
			m_newtraparea 	  
			m_yearnewseiclong 
			m_seic3dprofit 	  
			m_newoilgasarea   
			m_seic3dworkarea  
			m_optimyear		  
			m_optimnum		  */
			if(order == 30)
			{
				m_seic2ddiscovrate = ::atof(value.c_str());
			}
			if(order == 31)
			{
				m_newtraparea = ::atof(value.c_str());
			}
			if(order == 32)
			{
				m_yearnewseiclong = ::atof(value.c_str());
			}
			if(order == 33)
			{
				m_seic3dprofit = ::atof(value.c_str());
			}
			if(order == 34)
			{
				m_newoilgasarea = ::atof(value.c_str());
			}
			if(order == 35)
			{
				m_seic3dworkarea = ::atof(value.c_str());
			}
			
		}
	};		
	
	/*!
	*PRT_Trap_Project
	**/
	struct TrapProjectRecord : public PropertyRecord
	{
		long m_managementphase;
		double m_fromdate;
		double m_todate;
		double m_discoverdate;
		double m_recheckdate;
		double m_descdate;
		string m_discoverydepartment;
		string m_auditdepartment;
		string m_submitdepartment;
		string m_personicharge;
		double m_submitdate;
		string m_reviewcomments;
		string m_reviewersign;
		double m_reviewdate;
		string m_reviewdepartment;
		string m_exploreproject;
		string m_subexplorproject;
		string m_discoverymethod;
		string m_trapoldname;
		long m_recogtimes;
		string m_remark;
		
		//
		string m_organization;
		string m_conductor 	 ;
		string m_auditor 	 ;
		string m_auditstatus ;
		string m_trapstatus  ;
		string m_reliability ;
		
		/*!
		*
		**/
		TrapProjectRecord()
		{
			m_managementphase = 0;
			
			m_fromdate 	  =0.;
			m_todate 	  =0.;
			
			//
			m_discoverdate = 0.;
			m_recheckdate = 0.;
			m_descdate = 0.;
			m_discoverydepartment ="";
			m_auditdepartment ="";
			m_submitdepartment ="";
			m_personicharge ="";
			m_submitdate = 0.;
			m_reviewcomments ="";
			m_reviewersign ="";
			m_reviewdate =0.;
			m_reviewdepartment ="";
			m_exploreproject ="";
			m_subexplorproject ="";
			m_discoverymethod ="";
			m_trapoldname ="";
			m_recogtimes =0;
			m_remark ="";

			/*!
			*
			**/
			m_organization="";
			m_conductor   ="";
			m_auditor 	  ="";
			m_auditstatus ="";
			m_trapstatus  ="";
			m_reliability ="";
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 2 + 21/* + 6*/;
		}

		/*!
		*
		**/
		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			else if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			else if(order == 2)
			{
				value = "management phase";
				type=0;
			}
			else if(order == 3)
			{
				value = "fromdate";
				type=0;
			}
			else if(order == 4)
			{
				value = "todate";
				type=0;
			}
			else if(order == 5)
			{
				value = "discover date";
				type=0;
			}
			else if(order == 6)
			{
				value = "recheck date";
				type=0;
			}
			else if(order == 7)
			{
				value = "desc date";
				type=0;
			}
			else if(order == 8)
			{
				value = "discovery department";
				type=2;
			}
			else if(order == 9)
			{
				value = "audit department";
				type=2;
			}
			else if(order == 10)
			{
				value = "submit department";
				type=2;
			}
			else if(order == 11)
			{
				value = "person in charge";
				type=2;
			}
			else if(order == 12)
			{
				value = "submit date";
				type=0;
			}
			else if(order == 13)
			{
				value = "review comments";
				type=2;
			}
			else if(order == 14)
			{
				value = "reviewer signature";
				type=2;
			}
			else if(order == 15)
			{
				value = "review date";
				type=0;
			}
			else if(order == 16)
			{
				value = "review department";
				type=2;
			}

			//
			else if (order == 17)
			{
				value = "explore project";
				type=2;
			}
			else if (order == 18)
			{
				value = "sub explore project";
				type=2;
			}
			else if (order == 19)
			{
				value = "trap discovery condition";
				type=2;
			}
			else if (order == 20)
			{
				value = "trap old name";
				type=2;
			}
			else if (order == 21)
			{
				value = "recognized times";
				type=0;
			}
			else if(order == 22)
			{
				value = "remark";
				type=2;

			}
			
			//
			else if(order == 23)
			{
				value = "organization";
				type=2;

			}
			else if(order == 24)
			{
				value = "conductor";
				type=2;

			}
			else if(order == 25)
			{
				value = "auditor";
				type=2;

			}
			else if(order == 26)
			{
				value = "auditstatus";
				type=2;

			}
			else if(order == 27)
			{
				value = "trapstatus";
				type=2;

			}
			else if(order == 28)
			{
				value = "reliability";
				type=2;
			}			
		}
		
		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			else if(order == 1) 
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			else if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_fromdate);
			}
			else if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_todate);
			}
			else if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_discoverdate);
			}
			else if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_recheckdate);
			}
			else if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_descdate);
			}
			else if(order == 8)
			{
				value = m_discoverydepartment;
			}
			else if(order == 9)
			{
				value = m_auditdepartment;
			}
			else if(order == 10)
			{
				value = m_submitdepartment;
			}
			else if(order == 11)
			{
				value = m_personicharge;
			}
			else if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_submitdate);
			}
			else if(order == 13)
			{
				value = m_reviewcomments;
			}
			else if(order == 14)
			{
				value = m_reviewersign;
			}
			else if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_reviewdate);
			}
			else if(order == 16)
			{
				value = m_reviewdepartment;
			}

			//
			else if (order == 17)
			{
				value = m_exploreproject;
			}
			else if (order == 18)
			{
				value = m_subexplorproject;
			}
			else if (order == 19)
			{
				value = m_discoverymethod;
			}
			else if (order == 20)
			{
				value = m_trapoldname;
			}
			else if (order == 21)
			{
				::sprintf((char *)value.c_str(), "%d", m_recogtimes);
			}
			else if(order == 22)
			{
				value = m_remark;
			}

			//
			else if(order == 23)
			{
				value = m_organization;
			}
			else if(order == 24)
			{
				value = m_conductor;
			}
			else if(order == 25)
			{
				value = m_auditor;
			}
			else if(order == 26)
			{
				value = m_auditstatus;
			}
			else if(order == 27)
			{
				value = m_trapstatus;
			}
			else if(order == 28)
			{
				value = m_reliability;
			}			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}
			else if(order == 3)
			{
				m_fromdate = ::atof(value.c_str());
			}
			else if(order == 4)
			{
				m_todate = ::atof(value.c_str());
			}
			else if(order == 5)
			{
				m_discoverdate = ::atof(value.c_str());
			}
			else if(order == 6)
			{
				m_recheckdate = ::atof(value.c_str());
			}
			else if(order == 7)
			{
				m_descdate = ::atof(value.c_str());
			}
			else if(order == 8)
			{
				m_discoverydepartment = value;
			}
			else if(order == 9)
			{
				m_auditdepartment = value;
			}
			else if(order == 10)
			{
				m_submitdepartment = value;
			}
			else if(order == 11)
			{
				m_personicharge = value;
			}
			else if(order == 12)
			{
				m_submitdate = ::atof(value.c_str());
			}
			else if(order == 13)
			{
				m_reviewcomments = value;
			}
			else if(order == 14)
			{
				m_reviewersign = value;
			}
			else if(order == 15)
			{
				m_reviewdate = ::atof(value.c_str());
			}
			else if(order == 16)
			{
				m_reviewdepartment = value;
			}

			//
			else if (order == 17)
			{
				m_exploreproject = value;
			}
			else if (order == 18)
			{
				m_subexplorproject = value;
			}
			else if (order == 19)
			{
				m_discoverymethod = value;
			}
			else if (order == 20)
			{
				m_trapoldname = value;
			}
			else if (order == 21)
			{
				m_recogtimes = ::atoi(value.c_str());
			}
			else if(order == 22)
			{
				m_remark = value;
			}

			//
			else if(order == 23)
			{
				m_organization = value;
			}
			else if(order == 24)
			{
				m_conductor = value;
			}
			else if(order == 25)
			{
				m_auditor = value;
			}
			else if(order == 26)
			{
				m_auditstatus = value;
			}
			else if(order == 27)
			{
				m_trapstatus = value;
			}
			else if(order == 28)
			{
				m_reliability = value;
			}		
		}

	};
	
	/*!
	*
	**/
	struct TrapRepositoryRecord :public PropertyRecord
	{

		string m_remark;

		TrapRepositoryRecord()
		{

			m_remark = "";
		}

		int GetFldCount()
		{
			return 3;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value = m_remark;
			}
		}

		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_remark = value;
			}
		}

	};

	/*!
	*PRT_Trap_Survey
	**/
	struct TrapSurveyRecord :public PropertyRecord
	{
		long m_managementphase;
		
		std::string m_basin;
		std::string m_1unit;
		std::string m_2unit;
		std::string m_geographydesc;
		std::string m_surfacecondition;
		double m_surfaceelevation;
		std::string m_seisworkprocess;
		std::string m_discoverreason;
		std::string m_mainseisline; 
		
		//2016/8/29
		double m_coordx;
		double m_coordy;

		//image
		char *m_geographymap;
		long m_geographymaplength;
		char *m_seislineprofile; 
		long m_seislineprofilelength;

		std::string m_projectsys; 
		std::string m_coordsys; 

		/*!
		*
		**/
		TrapSurveyRecord()
		{
			Reset();
		}	
		
		/*!
		*
		**/
		TrapSurveyRecord(const TrapSurveyRecord &other)
		{
			Reset();
			*this = other;
		}

		/*!
		*
		**/
		const TrapSurveyRecord &operator=(const TrapSurveyRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;

			//2016/7/28:parent's items
			m_isUpdated = other.m_isUpdated;
			m_isAdded = other.m_isAdded;
			m_isDeleted = other.m_isDeleted;

			m_managementphase = other.m_managementphase;

			m_basin = other.m_basin;
			m_1unit = other.m_1unit;
			m_2unit = other.m_2unit;
			m_geographydesc = other.m_geographydesc;
			m_surfacecondition = other.m_surfacecondition;
			m_surfaceelevation = other.m_surfaceelevation;
			m_seisworkprocess = other.m_seisworkprocess;
			m_discoverreason= other.m_discoverreason;
			m_mainseisline= other.m_mainseisline;

			//
			m_coordx = other.m_coordx;
			m_coordy = other.m_coordy;

			m_projectsys =other.m_projectsys;
			m_coordsys = other.m_coordsys;

			//image
			Release();
			
			m_geographymaplength = other.m_geographymaplength;
			if (m_geographymaplength > 0)
			{
				m_geographymap = (char *)::malloc(m_geographymaplength);
				::memcpy(m_geographymap,other.m_geographymap,m_geographymaplength);
			}
			
			m_seislineprofilelength = other.m_seislineprofilelength;
			if (m_seislineprofilelength > 0)
			{
				m_seislineprofile = (char *)::malloc(m_seislineprofilelength);
				::memcpy(m_seislineprofile,other.m_seislineprofile,m_seislineprofilelength);
			}

			return *this;
		}
		
		/*!
		*
		**/
		void Release()
		{
			if (m_geographymap)
			{
				::free(m_geographymap);
			}
			m_geographymap = 0;
			m_geographymaplength = 0;

			if (m_seislineprofile)
			{
				::free(m_seislineprofile);
			}
			m_seislineprofile = 0;
			m_seislineprofilelength = 0;

		}

		/*!
		*
		**/
		void Reset()
		{
			m_managementphase = 0;
			m_basin = "";
			m_1unit = "";
			m_2unit = "";
			m_geographydesc = "";
			m_surfacecondition = "";
			m_surfaceelevation = 0.;
			m_seisworkprocess = "";
			m_discoverreason= "";
			m_mainseisline= "";

			//
			m_coordx = 0.;
			m_coordy = 0.;

			m_geographymap = 0; 
			m_geographymaplength = 0;
			m_seislineprofile = 0; 
			m_seislineprofilelength = 0;

			m_projectsys ="";
			m_coordsys = "";
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 2 + 10 + 2 + 2/*coord*/;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order == 2 || order == 8 || order == 13)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			else if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			else if(order == 2)
			{
				value = "management phase";
				type=0;
			}
			else if(order == 3)
			{
				value = "basin";
				type=2;
			}
			else if(order == 4)
			{
				value = "first unit";
				type=2;
			}
			else if(order == 5)
			{
				value = "second unit";
				type=2;
			}
			else if(order == 6)
			{
				value = "coordinate x";
				type=1;
			}
			else if(order == 7)
			{
				value = "coordinate y";
				type=1;
			}
			else if(order == 8)
			{
				value = "geological position";
				type=2;
			}
			else if(order == 9)
			{
				value = "surface condition";
				type=2;
			}
			else if(order == 10)
			{
				value = "surface elevation";
				type=1;
			}
			else if(order == 11)
			{
				value = "seismic work process";
				type=2;
			}
			else if(order == 12)
			{
				value = "discover reason";
				type=2;
			}
			else if(order == 13)
			{
				value = "main seismic lines";
				type=2;
			}
			else if(order == 14)
			{
				value = "projectsys";
				type=2;
			}
			else if(order == 15)
			{
				value = "coordsys";
				type=2;
			}
		}
	
		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			else if(order == 3)
			{
				value = m_basin;
			}
			else if(order == 4)
			{
				value = m_1unit;
			}
			else if(order == 5)
			{
				value = m_2unit;
			}
			else if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_coordx);
			}
			else if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_coordy);
			}
			else if(order == 8)
			{
				value = m_geographydesc;
			}
			else if(order == 9)
			{
				value = m_surfacecondition;
			}
			else if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_surfaceelevation);
			}
			else if(order == 11)
			{
				value = m_seisworkprocess;
			}
			else if(order == 12)
			{
				value = m_discoverreason;
			}
			else if(order == 13)
			{
				value = m_mainseisline;
			}
			else if(order == 14)
			{
				value = m_projectsys;
			}
			else if(order == 15)
			{
				value = m_coordsys;
			}

		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}
			else if(order == 3)
			{
				m_basin = value;
			}
			else if(order == 4)
			{
				m_1unit = value;
			}
			else if(order == 5)
			{
				m_2unit = value;
			}
			else if(order == 6)
			{
				m_coordx = ::atof(value.c_str());
			}
			else if(order == 7)
			{
				m_coordy = ::atof(value.c_str());
			}
			else if(order == 8)
			{
				m_geographydesc = value;
			}
			else if(order == 9)
			{
				m_surfacecondition = value;
			}
			else if(order == 10)
			{
				m_surfaceelevation = ::atof(value.c_str());
			}
			else if(order == 11)
			{
				 m_seisworkprocess = value;
			}
			else if(order == 12)
			{
				m_discoverreason = value;
			}
			else if(order == 13)
			{
				m_mainseisline = value;
			}
			else if(order == 14)
			{
				m_projectsys = value;
			}
			else if(order == 15)
			{
				m_coordsys = value;
			}
		}
	};		

	/*!
	*PRT_Trap_Geology_Fault
	**/
	struct TrapGeologyFaultRecord :public PropertyRecord
	{
		long m_managementphase;
		
		std::string m_faultname;
		std::string m_brokenseishorizon;
		std::string m_brokengeohorizon;
		std::string m_faultproperty;
		double m_faultdip;
		double m_faultdipangle;
		double m_faultheave;
		double m_faultextension;
		
		/*!
		*
		**/
		TrapGeologyFaultRecord()
		{
			m_managementphase = 0;
			m_faultname = "";
			m_brokenseishorizon = "";
			m_brokengeohorizon = "";
			m_faultproperty = "";
			m_faultdip = 0;
			m_faultdipangle = 0;
			m_faultheave = 0;
			m_faultextension = 0;
		}	
		
		/*!
		*
		**/
		const TrapGeologyFaultRecord &operator=(const TrapGeologyFaultRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;

			m_managementphase = other.m_managementphase;

			m_faultname = other.m_faultname;
			m_brokenseishorizon = other.m_brokenseishorizon;
			m_brokengeohorizon = other.m_brokengeohorizon;
			m_faultproperty = other.m_faultproperty;
			m_faultdip = other.m_faultdip;
			m_faultdipangle = other.m_faultdipangle;
			m_faultheave = other.m_faultheave;
			m_faultextension = other.m_faultextension;
			
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 2 + 9;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order == 2)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			else if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			else if(order == 2)
			{
				value = "management phase";
				type=0;
			}
			else if(order == 3)
			{
				value = "fault name";
				type=2;
			}
			else if(order == 4)
			{
				value = "broken seismic horizon";
				type=2;
			}
			else if(order == 5)
			{
				value = "broken geology horizon";
				type=2;
			}
			else if(order == 6)
			{
				value = "fault property";
				type=2;
			}
			else if(order == 7)
			{
				value = "fault dip";
				type=1;
			}
			else if(order == 8)
			{
				value = "fault dip angle";
				type=1;
			}
			else if(order == 9)
			{
				value = "fault heave";
				type=1;
			}
			else if(order == 10)
			{
				value = "fault extension";
				type=1;
			}
		}
	
		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			else if(order == 3)
			{
				value = m_faultname;
			}
			else if(order == 4)
			{
				value = m_brokenseishorizon;
			}
			else if(order == 5)
			{
				value = m_brokengeohorizon;
			}
			else if(order == 6)
			{
				value = m_faultproperty;
			}
			else if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_faultdip);
			}
			else if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_faultdipangle);
			}
			else if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_faultheave);
			}
			else if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_faultextension);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}
			else if(order == 3)
			{
				m_faultname = value;
			}
			else if(order == 4)
			{
				m_brokenseishorizon = value;
			}
			else if(order == 5)
			{
				m_brokengeohorizon = value;
			}
			else if(order == 6)
			{
				m_faultproperty = value;
			}
			else if(order == 7)
			{
				m_faultdip = ::atof(value.c_str());
			}
			else if(order == 8)
			{
				m_faultdipangle = ::atof(value.c_str());
			}
			else if(order == 9)
			{
				m_faultheave = ::atof(value.c_str());
			}
			else if(order == 10)
			{
				m_faultextension = ::atof(value.c_str());
			}
		}
	};	

	/*!
	*PRT_Trap_Wildcat_Well
	**/
	struct TrapWildcatWellRecord :public PropertyRecord
	{
		long m_managementphase;
		
		std::string m_wildcatwell;
		std::string m_teststatus;
		std::string m_indication;
		std::string m_failedreason;
		double m_designeddepth;
		double m_expwellcost;
		double m_startdate;
		double m_finishdate;
		std::string m_drillstatus;
		std::string m_updowngrade;
		std::string m_approvalstatus;
		std::string m_gradingreason; 
		std::string m_remark; 
		
		/*!
		*
		**/
		TrapWildcatWellRecord()
		{
			m_managementphase = 0;
			m_wildcatwell = "";
			m_teststatus = "";
			m_indication = "";
			m_failedreason = "";
			m_designeddepth = 0.;
			m_expwellcost = 0.;
			m_startdate = 0.;
			m_finishdate = 0.;
			m_drillstatus = "";
			m_updowngrade = "";
			m_approvalstatus= "";
			m_gradingreason= "";;
			m_remark = "";
		}	
		
		/*!
		*
		**/
		const TrapWildcatWellRecord &operator=(const TrapWildcatWellRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;

			m_managementphase = other.m_managementphase;

			m_wildcatwell = other.m_wildcatwell;
			m_teststatus = other.m_teststatus;
			m_indication = other.m_indication;
			m_failedreason = other.m_failedreason;
			m_designeddepth = other.m_designeddepth;
			m_expwellcost = other.m_expwellcost;
			m_startdate = other.m_startdate;
			m_finishdate = other.m_finishdate;

			m_drillstatus = other.m_drillstatus;
			m_updowngrade = other.m_updowngrade;
			m_approvalstatus= other.m_approvalstatus;
			m_gradingreason= other.m_gradingreason;
			m_remark = other.m_remark;
			
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 2 + 14;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order == 2)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			else if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			else if(order == 2)
			{
				value = "management phase";
				type=0;
			}
			else if(order == 3)
			{
				value = "wildcat well";
				type=2;
			}
			else if(order == 4)
			{
				value = "test status";
				type=2;
			}
			else if(order == 5)
			{
				value = "indication";
				type=2;
			}
			else if(order == 6)
			{
				value = "failed reason";
				type=2;
			}
			else if(order == 7)
			{
				value = "designed depth";
				type=1;
			}
			else if(order == 8)
			{
				value = "explore well cost";
				type=1;
			}
			else if(order == 9)
			{
				value = "start date";
				type=0;
			}
			else if(order == 10)
			{
				value = "finish date";
				type=0;
			}
			else if(order == 11)
			{
				value = "drill status";
				type=2;
			}
			else if(order == 12)
			{
				value = "up down grade";
				type=2;
			}
			else if(order == 13)
			{
				value = "approval status";
				type=2;
			}
			else if(order == 14)
			{
				value = "grading reason";
				type=2;
			}
			else if(order == 15)
			{
				value = "remark";
				type=2;
			}
		}
	
		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			else if(order == 3)
			{
				value = m_wildcatwell;
			}
			else if(order == 4)
			{
				value = m_teststatus;
			}
			else if(order == 5)
			{
				value = m_indication;
			}
			else if(order == 6)
			{
				value = m_failedreason;
			}
			else if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_designeddepth);
			}
			else if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_expwellcost);
			}
			else if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_startdate);
			}
			else if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_finishdate);
			}
			else if(order == 11)
			{
				value = m_drillstatus;
			}
			else if(order == 12)
			{
				value = m_updowngrade;
			}
			else if(order == 13)
			{
				value = m_approvalstatus;
			}
			else if(order == 14)
			{
				value = m_gradingreason;
			}
			else if(order == 15)
			{
				value = m_remark;
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}
			else if(order == 3)
			{
				m_wildcatwell = value;
			}
			else if(order == 4)
			{
				m_teststatus = value;
			}
			else if(order == 5)
			{
				m_indication = value;
			}
			else if(order == 6)
			{
				m_failedreason = value;
			}
			else if(order == 7)
			{
				m_designeddepth = ::atof(value.c_str());				
			}
			else if(order == 8)
			{
				m_expwellcost = ::atof(value.c_str());		
			}
			else if(order == 9)
			{
				m_startdate = ::atof(value.c_str());		
			}
			else if(order == 10)
			{
				m_finishdate = ::atof(value.c_str());		
			}
			else if(order == 11)
			{
				m_drillstatus = value;
			}
			else if(order == 12)
			{
				m_updowngrade = value;
			}
			else if(order == 13)
			{
				m_approvalstatus = value;
			}
			else if(order == 14)
			{
				m_gradingreason = value;
			}
			else if(order == 15)
			{
				m_remark = value;
			}
		}
	};		

	/*!
	*PRT_Trap_Post
	**/
	struct TrapPostRecord :public PropertyRecord
	{
		long m_managementphase;
		
		double m_trapcondition;
		double m_fillingcondition;
		double m_reservoircondition;
		double m_reservecondition;
		
		std::string	m_failedreason;
		std::string	m_drillconclusion;
		std::string	m_advice;
		std::string	m_formation;
		
		double m_oilrate;
		double m_gasrate;
		
		std::string	m_maintarget;
		double m_postdrillarea;
		double m_postdrillthick;
		double m_postdrillURF;
		double m_postdrillreserve;
		
		/*!
		*
		**/
		TrapPostRecord()
		{
			m_managementphase = 0;
			m_trapcondition = 0;
			m_fillingcondition = 0;
			m_reservoircondition = 0;
			m_reservecondition = 0;
			
			m_failedreason = "";
			m_drillconclusion = "";
			m_advice = "";
			m_formation = "";
			
			m_oilrate = 0;
			m_gasrate = 0;
			
			m_maintarget = "";
			
			m_postdrillarea = 0;
			m_postdrillthick = 0;
			m_postdrillURF = 0;
			m_postdrillreserve = 0;
		}	
		
		/*!
		*
		**/
		const TrapPostRecord &operator=(const TrapPostRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;

			m_managementphase = other.m_managementphase;

			m_trapcondition = other.m_trapcondition;
			m_fillingcondition = other.m_fillingcondition;
			m_reservoircondition = other.m_reservoircondition;
			m_reservecondition = other.m_reservecondition;

			m_failedreason = other.m_failedreason;
			m_drillconclusion = other.m_drillconclusion;
			m_advice = other.m_advice;
			m_formation = other.m_formation;

			m_oilrate = other.m_oilrate;
			m_gasrate = other.m_gasrate;
			m_maintarget = other.m_maintarget;
			m_postdrillarea = other.m_postdrillarea;
			m_postdrillthick = other.m_postdrillthick;
			m_postdrillURF = other.m_postdrillURF;
			m_postdrillreserve = other.m_postdrillreserve;
			
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 2 + 16;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order == 2)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			else if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			else if(order == 2)
			{
				value = "management phase";
				type=0;
			}
			else if(order == 3)
			{
				value = "trap condition";
				type=1;
			}
			else if(order == 4)
			{
				value = "filling condition";
				type=1;
			}
			else if(order == 5)
			{
				value = "reservoir condition";
				type=1;
			}
			else if(order == 6)
			{
				value = "reserve condition";
				type=1;
			}
			else if(order == 7)
			{
				value = "failed reason and new recognizes";
				type=2;
			}
			else if(order == 8)
			{
				value = "drilled conclusion";
				type=2;
			}
			else if(order == 9)
			{
				value = "work advice of next step";
				type=2;
			}
			else if(order == 10)
			{
				value = "formation";
				type=2;
			}
			else if(order == 11)
			{
				value = "oil rate";
				type=1;
			}
			else if(order == 12)
			{
				value = "gas rate";
				type=1;
			}
			else if(order == 13)
			{
				value = "main target formation";
				type=2;
			}
			else if(order == 14)
			{
				value = "post drill area";
				type=1;
			}
			else if(order == 15)
			{
				value = "post drill thickness";
				type=1;
			}
			else if(order == 16)
			{
				value = "post drill URF";
				type=1;
			}
			else if(order == 17)
			{
				value = "post drill reserve";
				type=1;
			}
		}
	
		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			else if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_trapcondition);
			}
			else if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_fillingcondition);
			}
			else if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_reservoircondition);
			}
			else if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_reservecondition);
			}
			else if(order == 7)
			{
				value = m_failedreason;
			}
			else if(order == 8)
			{
				value = m_drillconclusion;
			}
			else if(order == 9)
			{
				value = m_advice;
			}
			else if(order == 10)
			{
				value = m_formation;
			}
			else if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilrate);
			}
			else if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_gasrate);
			}
			else if(order == 13)
			{
				value = m_maintarget;
			}
			else if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_postdrillarea);
			}
			else if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_postdrillthick);
			}
			else if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_postdrillURF);
			}
			else if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%f", m_postdrillreserve);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}
			else if(order == 3)
			{
				m_trapcondition = ::atof(value.c_str());
			}
			else if(order == 4)
			{
				m_fillingcondition = ::atof(value.c_str());
			}
			else if(order == 5)
			{
				m_reservoircondition = ::atof(value.c_str());
			}
			else if(order == 6)
			{
				m_reservecondition = ::atof(value.c_str());
			}
			else if(order == 7)
			{
				m_failedreason = value;				
			}
			else if(order == 8)
			{
				m_drillconclusion = value;
			}
			else if(order == 9)
			{
				m_advice = value;	
			}
			else if(order == 10)
			{
				m_formation = value;			
			}
			else if(order == 11)
			{
				m_oilrate = ::atof(value.c_str());
			}
			else if(order == 12)
			{
				m_gasrate = ::atof(value.c_str());
			}
			else if(order == 13)
			{
				m_maintarget = value;
			}
			else if(order == 14)
			{
				m_postdrillarea = ::atof(value.c_str());
			}
			else if(order == 15)
			{
				m_postdrillthick = ::atof(value.c_str());
			}
			else if(order == 16)
			{
				m_postdrillURF = ::atof(value.c_str());
			}
			else if(order == 17)
			{
				m_postdrillreserve = ::atof(value.c_str());
			}
		}
	};		

	/*!
	*PRT_Trap_Drill
	**/
	struct TrapDrillRecord :public PropertyRecord
	{
		long m_managementphase;
		
		std::string m_constrprogress;
		std::string m_wellfunctions;
		std::string m_targetformation;
		double	m_currentdepth;
		double	m_remainfootage;
		std::string m_currentformation;
		double	m_currentfootage;
		std::string m_resourceindication;
		std::string m_projectstatus;
		double	m_drillingdensity;
		double	m_reportdate;
		double	m_drillingdays;
		double	m_planedyear;
		std::string m_totalindication;
		std::string m_conclution;
		
		/*!
		*
		**/
		TrapDrillRecord()
		{
			m_managementphase = 0;
			
			m_constrprogress = "";
			m_wellfunctions = "";
			m_targetformation = "";
			m_currentdepth = 0.;
			m_remainfootage = 0.;
			m_currentformation = "";
			m_currentfootage = 0.;
			m_resourceindication = "";
			m_projectstatus = "";
			m_drillingdensity = 0.;
			m_reportdate = 0.;
			m_drillingdays = 0.;
			m_planedyear = 0.;
			m_totalindication = "";
			m_conclution = "";
		}	
		
		/*!
		*
		**/
		const TrapDrillRecord &operator=(const TrapDrillRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;

			m_managementphase = other.m_managementphase;

			m_constrprogress = other.m_constrprogress;
			m_wellfunctions = other.m_wellfunctions;
			m_targetformation = other.m_targetformation;
			m_currentdepth = other.m_currentdepth;
			m_remainfootage = other.m_remainfootage;
			m_currentformation = other.m_currentformation;
			m_currentfootage = other.m_currentfootage;
			m_resourceindication = other.m_resourceindication;
			m_projectstatus = other.m_projectstatus;
			m_drillingdensity = other.m_drillingdensity;
			m_reportdate = other.m_reportdate;
			m_drillingdays = other.m_drillingdays;
			m_planedyear = other.m_planedyear;
			m_totalindication = other.m_totalindication;
			m_conclution = other.m_conclution;
			
			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 2 + 16;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order == 2)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			else if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			else if(order == 2)
			{
				value = "management phase";
				type=0;
			}
			else if(order == 3)
			{
				value = "construct progress";
				type=2;
			}
			else if(order == 4)
			{
				value = "well functions";
				type=2;
			}
			else if(order == 5)
			{
				value = "main target formation";
				type=2;
			}
			else if(order == 6)
			{
				value = "depth in the current day";
				type=1;
			}
			else if(order == 7)
			{
				value = "remaining footage";
				type=1;
			}
			else if(order == 8)
			{
				value = "current formation";
				type=2;
			}
			else if(order == 9)
			{
				value = "current footage";
				type=1;
			}
			else if(order == 10)
			{
				value = "resource indication";
				type=2;
			}
			else if(order == 11)
			{
				value = "project status";
				type=2;
			}
			else if(order == 12)
			{
				value = "drilling density";
				type=1;
			}
			else if(order == 13)
			{
				value = "report date";
				type=0;
			}
			else if(order == 14)
			{
				value = "drilling days";
				type=1;
			}
			else if(order == 15)
			{
				value = "planned year";
				type=1;
			}
			else if(order == 16)
			{
				value = "total indication";
				type=2;
			}
			else if(order == 17)
			{
				value = "conclution";
				type=2;
			}
		}
	
		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			else if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			else if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			else if(order == 3)
			{
				value = m_constrprogress;
			}
			else if(order == 4)
			{
				value = m_wellfunctions;
			}
			else if(order == 5)
			{
				value = m_targetformation;
			}
			else if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_currentdepth);
			}
			else if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_remainfootage);
			}
			else if(order == 8)
			{
				value = m_currentformation;
			}
			else if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_currentfootage);
			}
			else if(order == 10)
			{
				value = m_resourceindication;
			}
			else if(order == 11)
			{
				value = m_projectstatus;
			}
			else if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_drillingdensity);
			}
			else if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_reportdate);
			}
			else if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_drillingdays);
			}
			else if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_planedyear);
			}
			else if(order == 16)
			{
				value = m_totalindication;
			}
			else if(order == 17)
			{
				value = m_conclution;
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			else if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			else if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}
			else if(order == 3)
			{
				m_constrprogress = value;
			}
			else if(order == 4)
			{
				m_wellfunctions = value;
			}
			else if(order == 5)
			{
				m_targetformation = value;
			}
			else if(order == 6)
			{
				m_currentdepth = ::atof(value.c_str());
			}
			else if(order == 7)
			{
				m_remainfootage = ::atof(value.c_str());
			}
			else if(order == 8)
			{
				m_currentformation = value;
			}
			else if(order == 9)
			{
				m_currentfootage = ::atof(value.c_str());
			}
			else if(order == 10)
			{
				m_resourceindication = value;
			}
			else if(order == 11)
			{
				m_projectstatus = value;
			}
			else if(order == 12)
			{
				m_drillingdensity = ::atof(value.c_str());
			}
			else if(order == 13)
			{
				m_reportdate = ::atof(value.c_str());
			}
			else if(order == 14)
			{
				m_drillingdays = ::atof(value.c_str());
			}
			else if(order == 15)
			{
				m_planedyear = ::atof(value.c_str());
			}
			else if(order == 16)
			{
				m_totalindication = value;
			}
			else if(order == 17)
			{
				m_conclution = value;
			}
		}
	};		
	
	/*!
	*
	**/
	struct TrapDevelopmentRecord : public PropertyRecord
	{
		long	m_managementphase;
		int     m_isdiscovery	 ;
		double	m_stdproduction  ;
		double	m_maxproduction  ;
		double	m_avgproduction  ;
		string  m_wellsolution 	 ;
		double	m_testmax 		 ;
		double	m_testavg 		 ;
		string	m_decision 		 ;
		string	m_remark 		 ;
		string	m_discoverytype  ;
		string	m_result 		 ;
		string  m_wellnum		 ;
		/*!
		*
		**/
		TrapDevelopmentRecord()
		{
			m_managementphase=0;
			m_isdiscovery	 =0;
			m_stdproduction  =0.0;
			m_maxproduction  =0.0;
			m_avgproduction  =0.0;
			m_wellsolution 	 ="";
			m_testmax 		 =0.0;
			m_testavg 		 =0.0;
			m_decision 		 ="";
			m_remark 		 ="";
			m_discoverytype  ="";
			m_result 		 ="";
			m_wellnum		 ="";
		}
		/*!
		*
		**/
		const TrapDevelopmentRecord &operator=(const TrapDevelopmentRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_managementphase	=other.m_managementphase;
			m_isdiscovery	 =other.m_isdiscovery	;
			m_stdproduction  =other.m_stdproduction ;
			m_maxproduction  =other.m_maxproduction ;
			m_avgproduction  =other.m_avgproduction ;
			m_wellsolution 	 =other.m_wellsolution 	;
			m_testmax 		 =other.m_testmax 		;
			m_testavg 		 =other.m_testavg 		;
			m_decision 		 =other.m_decision 		;
			m_remark 		 =other.m_remark 		;
			m_discoverytype  =other.m_discoverytype ;
			m_result 		 =other.m_result 		;
			m_wellnum		 =other.m_wellnum		;
			return *this;
		}

		int GetFldCount()
		{
			return 15;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text 
		{
			if(order == 0) 
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			if(order == 2) 
			{
				value = "managementphase";
				type=0;
			}
			if(order == 3) 
			{
				value = "isdiscovery";
				type=0;
			}
			if(order == 4) 
			{
				value = "stdproduction";
				type=1;
			}
			if(order == 5) 
			{
				value = "maxproduction";
				type=1;
			}
			if(order == 6) 
			{
				value = "avgproduction";
				type=1;
			}
			if(order == 7) 
			{
				value = "wellsolution";
				type=2;
			}
			if(order == 8) 
			{
				value = "testmax";
				type=1;
			}
			if(order == 9) 
			{
				value = "testavg";
				type=1;
			}
			if(order == 10)
			{
				value = "decision";
				type=2;
			}
			if(order == 11)
			{
				value = "remark";
				type=2;
			}
			if(order == 12)
			{
				value = "discoverytype";
				type=2;
			}
			if(order == 13)
			{
				value = "result";
				type=2;
			}
			if(order == 14)
			{
				value = "wellnum";
				type=2;
			}
		}


		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_managementphase);
			}
			if(order == 3) 
			{
				::sprintf((char *)value.c_str(), "%d", m_isdiscovery);
			}
			if(order == 4) 
			{
				::sprintf((char *)value.c_str(), "%.3f", m_stdproduction);
			}
			if(order == 5) 
			{
				::sprintf((char *)value.c_str(), "%.3f", m_maxproduction);
			}
			if(order ==6) 
			{
				::sprintf((char *)value.c_str(), "%.3f", m_avgproduction);
			}
			if(order == 7) 
			{
				value = m_wellsolution;
			}
			if(order == 8) 
			{
				::sprintf((char *)value.c_str(), "%.3f", m_testmax);
			}
			if(order == 9) 
			{
				::sprintf((char *)value.c_str(), "%.3f", m_testavg);
			}
			if(order == 10)
			{
				value = m_decision;
			}
			if(order == 11)
			{
				value = m_remark;
			}
			if(order == 12)
			{
				value = m_discoverytype;
			}
			if(order == 13)
			{
				value = m_result;
			}
			if(order == 14)
			{
				value = m_wellnum;
			}

		}

		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}

			if(order == 2)
			{
				m_managementphase = ::atoi(value.c_str());
			}

			if(order == 3)
			{
				m_isdiscovery = ::atoi(value.c_str());
			}
			if(order ==4)
			{
				m_stdproduction = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_maxproduction = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_avgproduction = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_wellsolution = value;
			}
			if(order == 8)
			{
				m_testmax = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_testavg = ::atof(value.c_str());
			}

			if(order == 10)
			{
				m_decision = value;
			}
			if(order == 11)
			{
				m_remark = value;
			}
			if(order == 12)
			{
				m_discoverytype = value;
			}
			if(order == 13)
			{
				m_result = value;
			}
			if(order == 14)
			{
				m_wellnum = value;
			}
		}



	};

	struct SurveyElementRecord : public PropertyRecord
	{
		string  m_parentregion					;
		string  m_parentplay					;
		string	m_exphorizon					;
		float	m_explorarea 					;
		float   m_seismiclength2d 				;
		string  m_surdensity 					;
		float	m_seismicarea3d 				;
		float	m_coverage3d 					;
		long	m_wells 						;
		float	m_wellarea 						;
		long	m_oilwells 						;
		long	m_gaswells 						;
		float	m_oilresource 					;
		float	m_gasresource 					;
		float	m_oilprovreserves 				;
		float	m_gasprovreserves 				;
		float	m_oilcontroreserves 			;
		float	m_gascontroreserves 			;
		float	m_oilforereserves 				;
		float	m_gasforereserves 				;
		float	m_oilprosresources 				;
		float	m_gasprosresources 				;
		float	m_reserverate					;
		string  m_understandingdegree			;
		string  m_explorationdegree				;
		string  m_caliname						;
		float   m_caliabundance					;
		float   m_caliabundancenormal			;
		float   m_calisuccess					;
		float   m_seisstrategyvalue				;
		float	m_oilgasequivresource			;
		float	m_workablerate					;
		float	m_expindex						;

		SurveyElementRecord()
		{
			m_parentregion="";
			m_parentplay					="";
			m_exphorizon					="";
			m_explorarea 					=0.0;
			m_seismiclength2d 				=0.0;
			m_surdensity 					="";
			m_seismicarea3d 				=0.0;
			m_coverage3d 					=0.0;
			m_wells 						=0;
			m_wellarea 						=0.0;
			m_oilwells 						=0;
			m_gaswells 						=0;
			m_oilresource 					=0.0;
			m_gasresource 					=0.0;
			m_oilprovreserves 				=0.0;
			m_gasprovreserves 				=0.0;
			m_oilcontroreserves 			=0.0;
			m_gascontroreserves 			=0.0;
			m_oilforereserves 				=0.0;
			m_gasforereserves 				=0.0;
			m_oilprosresources 				=0.0;
			m_gasprosresources 				=0.0;
			m_reserverate					=0.0;
			m_understandingdegree			="";
			m_explorationdegree				="";
			m_caliname						="";
			m_caliabundance					=0.0;
			m_calisuccess					=0.0;
			m_seisstrategyvalue				=0.0;
			m_caliabundancenormal=0.0;
			m_oilgasequivresource			=0.0;	
			m_workablerate					=0.0;
			m_expindex						=0.0;
		}
		/*!
		*
		**/
		const SurveyElementRecord &operator=(const SurveyElementRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_parentregion					=other.m_parentregion		;
			m_parentplay					=other.m_parentplay		;
			m_exphorizon					=other.m_exphorizon		;
			m_explorarea 					=other.m_explorarea 		;
			m_seismiclength2d 				=other.m_seismiclength2d 	;
			m_surdensity 					=other.m_surdensity 		;
			m_seismicarea3d 				=other.m_seismicarea3d 	;
			m_coverage3d 					=other.m_coverage3d 		;
			m_wells 						=other.m_wells 			;
			m_wellarea 						=other.m_wellarea 			;
			m_oilwells 						=other.m_oilwells 			;
			m_gaswells 						=other.m_gaswells 			;
			m_oilresource 					=other.m_oilresource 		;
			m_gasresource 					=other.m_gasresource 		;
			m_oilprovreserves 				=other.m_oilprovreserves 	;
			m_gasprovreserves 				=other.m_gasprovreserves 	;
			m_oilcontroreserves 			=other.m_oilcontroreserves ;
			m_gascontroreserves 			=other.m_gascontroreserves ;
			m_oilforereserves 				=other.m_oilforereserves 	;
			m_gasforereserves 				=other.m_gasforereserves 	;
			m_oilprosresources 				=other.m_oilprosresources 	;
			m_gasprosresources 				=other.m_gasprosresources 	;
			m_reserverate					=other.m_reserverate		;
			m_explorationdegree				=other.m_explorationdegree	;
			m_understandingdegree 			=other.m_understandingdegree;
			m_caliname						=other.m_caliname;
			m_caliabundance					=other.m_caliabundance;
			m_calisuccess					=other.m_calisuccess;
			m_seisstrategyvalue				=other.m_seisstrategyvalue;
			m_caliabundancenormal			=other.m_caliabundancenormal;
			m_oilgasequivresource			=other.m_oilgasequivresource;			
			m_workablerate					=other.m_workablerate		;			
			m_expindex						=other.m_expindex			;			



			return *this;
		}

		int GetFldCount()
		{
			return 35;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text 
		{
			if(order == 0) 
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			if(order == 2)
			{
				value = "parentregion";
				type=2;
			}
			if(order == 3)
			{
				value = "parentplay";
				type=2;
			}
			if(order == 4)
			{
				value = "exphorizon";
				type=2;
			}
			if(order == 5)
			{
				value = "explorarea";
				type=1;
			}
			
			if(order == 6)
			{
				value = "seismiclength2d";
				type=1;
			}
			if(order == 7)
			{
				value = "surdensity";
				type=2;
			}
			if(order == 8)
			{
				value = "seismicarea3d";
				type=1;
			}
			if(order ==9)
			{
				value = "coverage3d";
				type=1;
			}
			if(order == 10)
			{
				value = "wells";
				type=0;
			}
			if(order == 11)
			{
				value = "wellarea";
				type=1;
			}
			if(order == 12)
			{
				value = "oilwells";
				type=0;
			}
			if(order == 13)
			{
				value = "gaswells";
				type=0;
			}
			if(order == 14)
			{
				value = "oilresource";
				type=1;
			}
			if(order == 15)
			{
				value = "gasresource";
				type=1;
			}
			if(order == 16)
			{
				value = "oilprovreserves";
				type=1;
			}
			if(order == 17)
			{
				value = "gasprovreserves";
				type=1;
			}
			if(order == 18)
			{
				value = "oilcontroreserves";
				type=1;
			}
			if(order == 19)
			{
				value = "gascontroreserves";
				type=1;
			}
			if(order == 20)
			{
				value = "oilforereserves";
				type=1;
			}
			if(order == 21)
			{
				value = "gasforereserves";
				type=1;
			}
			if(order == 22)
			{
				value = "oilprosresources";
				type=1;
			}
			if(order == 23)
			{
				value = "gasprosresources";
				type=1;
			}
			if(order == 24)
			{
				value = "reserverate";
				type=1;
			}
			if(order == 25)
			{
				value = "understandingdegree";
				type=2;
			}
			if(order == 26)
			{
				value = "explorationdegree";
				type=2;
			}
			if(order == 27)
			{
				value = "caliname";
				type=2;
			}
			if(order == 28)
			{
				value = "caliabundance";
				type=1;
			}
			if(order == 29)
			{
				value = "caliabundancenormal";
				type=1;
			}
			if(order == 30)
			{
				value = "calisuccess";
				type=1;
			}
			if(order == 31)
			{
				value = "seisstrategyvalue";
				type=1;
			}		
			if(order == 32)
			{
				value = "oilgasequivresource";
				type=1;
			}
			if(order == 33)
			{
				value = "workablerate";
				type=1;
			}
			if(order == 34)
			{
				value = "expindex";
				type=1;
			}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value = m_parentregion;
			}
			if(order == 3)
			{
				value = m_parentplay;
			}
			if(order == 4)
			{
				value = m_exphorizon;
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_explorarea);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_seismiclength2d);
			}
			if(order == 7)
			{
				value = m_surdensity;
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_seismicarea3d);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_coverage3d);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%d", m_wells);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_wellarea);

			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%d", m_oilwells);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%d", m_gaswells);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_oilresource);

			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gasresource);

			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_oilprovreserves);

			}
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gasprovreserves);

			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_oilcontroreserves);

			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gascontroreserves);

			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_oilforereserves);

			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gasforereserves);

			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_oilprosresources);

			}
			if(order == 23)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gasprosresources);

			}
			if(order == 24)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_reserverate);

			}
			if(order == 25)
			{
				value = m_understandingdegree;

			}
			if(order == 26)
			{
				value = m_explorationdegree;

			}
			if(order == 27)
			{
				value = m_caliname;

			}
			if(order == 28)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_caliabundance);

			}
			if(order == 29)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_caliabundancenormal);

			}
			if(order == 30)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_calisuccess);

			}
			if(order == 31)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_seisstrategyvalue);

			}			
			if(order == 32)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_oilgasequivresource);

			}
			if(order == 33)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_workablerate);

			}
			if(order == 34)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_expindex);

			}
		}
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_parentregion=value;
			}
			if(order == 3)
			{
				m_parentplay=value;
			}
			
			if(order == 4)
			{
				  m_exphorizon=value;
			}
			if(order == 5)
			{
				m_explorarea = ::atof(value.c_str());
			}

			if(order ==6)
			{
				m_seismiclength2d = ::atof(value.c_str());
			}
			if(order == 7)
			{
				  m_surdensity=value;
			}
			if(order == 8)
			{
				m_seismicarea3d=::atof(value.c_str());
				
			}
			if(order == 9)
			{
				m_coverage3d=::atof(value.c_str());
				
			}
			if(order == 10)
			{
				m_wells=::atoi(value.c_str());
				
			}
			if(order == 11)
			{
				m_wellarea=::atof(value.c_str());
				

			}
			if(order == 12)
			{
				m_oilwells=::atoi(value.c_str());
				
			}
			if(order == 13)
			{
				m_gaswells=::atoi(value.c_str());
				
			}
			if(order == 14)
			{
				m_oilresource=::atof(value.c_str());
				

			}
			if(order == 15)
			{
				m_gasresource=::atof(value.c_str());
				

			}
			if(order == 16)
			{
				m_oilprovreserves=::atof(value.c_str());
				

			}
			if(order == 17)
			{
				m_gasprovreserves=::atof(value.c_str());
				

			}
			if(order == 18)
			{
				m_oilcontroreserves=::atof(value.c_str());
				

			}
			if(order == 19)
			{
				m_gascontroreserves=::atof(value.c_str());
				

			}
			if(order == 20)
			{
				m_oilforereserves=::atof(value.c_str());
				

			}
			if(order == 21)
			{
				m_gasforereserves=::atof(value.c_str());
				

			}
			if(order == 22)
			{
				m_oilprosresources=::atof(value.c_str());
				

			}
			if(order == 23)
			{
				m_gasprosresources=::atof(value.c_str());
				

			}
			if(order == 24)
			{
				m_reserverate=::atof(value.c_str());
				

			}
			if(order == 25)
			{
				m_understandingdegree=value;

			}
			if(order == 26)
			{
				m_explorationdegree=value;

			}
			if(order == 27)
			{
				m_caliname=value;

			}
			if(order == 28)
			{
				m_caliabundance=::atof(value.c_str());

			}
			if(order == 29)
			{
				m_caliabundancenormal=::atof(value.c_str());

			}
			if(order == 30)
			{
				m_calisuccess=::atof(value.c_str());

			}
			if(order == 31)
			{
				m_seisstrategyvalue=::atof(value.c_str());

			}
			if(order == 32)
			{
				m_oilgasequivresource=::atof(value.c_str());
			}
			if(order == 33)
			{
				m_workablerate=::atof(value.c_str());
			}
			if(order == 34)
			{
				m_expindex=::atof(value.c_str());
			}
		}

	};

	struct SeismicDeployRecord : public PropertyRecord
	{
		//double m_deploydate             ;
		//string m_parentplay             ;
		string m_schemetype				;
		string m_pooltype               ;
		double m_hfrequence             ;
		double m_hvelocity              ;
		double m_hdepth                 ;
		double m_hsnr                   ;
		double m_linelength             ;
		double m_linecost               ;
		double m_lineinvestment         ;
		double m_gridarea               ;
		double m_gridcost               ;
		double m_gridinvestment         ;
		string m_geowork                ;
		string m_geocommit              ;
		long   m_trapnum				;	
		string m_observesystemtype		;
		double m_potential;
		SeismicDeployRecord()
		{
		
		m_schemetype       ="" ;
		m_pooltype         ="" ;
		m_hfrequence       =0.0;
		m_hvelocity        =0.0;
		m_hdepth           =0.0;
		m_hsnr             =0.0;
		m_linelength       =0.0;
		m_linecost         =0.0;
		m_lineinvestment   =0.0;
		m_gridarea         =0.0;
		m_gridcost         =0.0;
		m_gridinvestment   =0.0;
		m_geowork          ="" ;
		m_geocommit        ="" ;
		m_trapnum		   =0;			
		m_observesystemtype	="" ;	
		m_potential         =0.0;
		}
		/*!
		*
		**/
		const SeismicDeployRecord &operator=(const SeismicDeployRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

				m_schemetype				=other.m_schemetype			 ;	
				m_pooltype      			=other.m_pooltype      		 ;
				m_hfrequence    			=other.m_hfrequence    		 ;
				m_hvelocity     			=other.m_hvelocity     		 ;
				m_hdepth        			=other.m_hdepth        		 ;
				m_hsnr          			=other.m_hsnr          		 ;
				m_linelength    			=other.m_linelength    		 ;
				m_linecost      			=other.m_linecost      		 ;
				m_lineinvestment			=other.m_lineinvestment		 ;
				m_gridarea      			=other.m_gridarea      		 ;
				m_gridcost      			=other.m_gridcost      		 ;
				m_gridinvestment			=other.m_gridinvestment		 ;
				m_geowork       			=other.m_geowork       		 ;
				m_geocommit     			=other.m_geocommit     		 ;
				m_trapnum					=other.m_trapnum             ;			
				m_observesystemtype			=other.m_observesystemtype   ;	
				m_potential                 =other.m_potential           ;	
			return *this;
		}

		int GetFldCount()
		{
			return 19;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text ,3 blob ,
		{
			if(order == 0) 
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			if(order == 2)
			{
				value = "schemetype";
				type=2;
			}
			
			if(order == 3)
			{
				value = "pooltype";
				type=2;
			}
	/*		if(order == 4)
			{
				value = "caliabundance";
				type=1;
			}
			if(order == 5)
			{
				value = "calisuccess";
				type=1;
			}*/
			if(order == 4)
			{
				value = "hfrequence";
				type=1;
			}
			if(order == 5)
			{
				value = "hvelocity";
				type=1;
			}
			if(order == 6)
			{
				value = "hdepth";
				type=1;
			}
			if(order == 7)
			{
				value = "hsnr";
				type=1;
			}
			if(order == 8)
			{
				value = "linelength";
				type=1;
			}
			if(order == 9)
			{
				value = "linecost";
				type=1;
			}
			if(order == 10)
			{
				value = "lineinvestment";
				type=1;
			}
			if(order == 11)
			{
				value = "gridarea";
				type=1;
			}
			if(order == 12)
			{
				value = "gridcost";
				type=1;
			}
			if(order == 13)
			{
				value = "gridinvestment";
				type=1;
			}
			if(order == 14)
			{
				value = "geowork";
				type=2;
			}
			if(order == 15)
			{
				value = "geocommit";
				type=2;
			}
			if(order == 16)
			{
				value = "trapnum";
				type=0;
			}
			if(order == 17)
			{
				value = "observesystemtype";
				type=2;
			}
			if(order == 18)
			{
				value = "potential";
				type=1;
			}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}

			if(order == 2)
			{
				value = m_schemetype;
			}
			if(order == 3)
			{
				value = m_pooltype;
				
			}
			
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_hfrequence);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_hvelocity );
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_hdepth );
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_hsnr );
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_linelength );
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_linecost );

			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_lineinvestment );
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gridarea );
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gridcost);

			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_gridinvestment );

			}
			if(order == 14)
			{
				value=m_geowork;

			}
			if(order == 15)
			{
				value=m_geocommit ;

			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%d", m_trapnum );

			}
			if(order == 17)
			{
				value=m_observesystemtype ;

			}
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_potential );

			}
		}
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
		
			if(order == 2)
			{
				m_schemetype=value;
			}
			if(order == 3)
			{
				 m_pooltype=value;

			}
			
			if(order == 4)
			{
				m_hfrequence  = ::atof(value.c_str());
			}
			if(order == 5)
			{
				 m_hvelocity =::atof(value.c_str());
			}
			if(order == 6)
			{
				m_hdepth =::atof(value.c_str());
				
			}
			if(order == 7)
			{
				m_hsnr =::atof(value.c_str());
				
			}
			if(order == 8)
			{
				m_linelength=::atof(value.c_str());
				
			}
			if(order == 9)
			{
				m_linecost =::atof(value.c_str());
				

			}
			if(order == 10)
			{
				m_lineinvestment =::atof(value.c_str());
				
			}
			if(order == 11)
			{
				m_gridarea =::atof(value.c_str());
				
			}
			if(order == 12)
			{
				m_gridcost =::atof(value.c_str());
				

			}
			if(order == 13)
			{
				m_gridinvestment =::atof(value.c_str());
				

			}
			if(order == 14)
			{
				m_geowork=value;
				

			}
			if(order == 15)
			{
				m_geocommit=value;
				

			}
			if(order == 15)
			{
				m_trapnum =::atol(value.c_str());


			}
			if(order == 17)
			{
				m_observesystemtype=value;


			}
			if(order == 18)
			{
				m_potential  = ::atof(value.c_str());
			}
		}

	};
	struct SurveyCheckRecord : public PropertyRecord
	{
		float		m_maxresabundance  ;
		float		m_minresabundance  ;
		float		m_maxp10divp90 	 ;
		float		m_minp10divp90 	 ;
		float		m_maxsuccessrate 	 ;
		float		m_minsuccessrate 	 ;
		float		m_maxscore ;
		float		m_minscore ;

		SurveyCheckRecord()
		{

			m_maxresabundance  = 0.0;
			m_minresabundance  = 0.0;
			m_maxp10divp90 	   = 0.0;
			m_minp10divp90 	   = 0.0;
			m_maxsuccessrate   = 0.0;
			m_minsuccessrate   = 0.0;
			m_maxscore		   = 0.0;
			m_minscore		   = 0.0;


		}
		const SurveyCheckRecord &operator=(const SurveyCheckRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_maxresabundance  =other.m_maxresabundance ;
			m_minresabundance  =other.m_minresabundance ;
			m_maxp10divp90 	   =other.m_maxp10divp90 	;
			m_minp10divp90 	   =other.m_minp10divp90 	;
			m_maxsuccessrate   =other.m_maxsuccessrate 	;
			m_minsuccessrate   =other.m_minsuccessrate 	;
			m_maxscore		   =other.m_maxscore 		;
			m_minscore		   =other.m_minscore 		;
			return *this;
		}
		int GetFldCount()
		{
			return 10;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text 
		{
			if(order == 0) 
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			if(order == 2)
			{
				value = "maxresabundance";
				type=1;
			}
			if(order == 3)
			{
				value = "minresabundance";
				type=1;
			}
			if(order == 4)
			{
				value = "maxp10divp90";
				type=1;
			}
			if(order == 5)
			{
				value = "minp10divp90";
				type=1;
			}
			if(order == 6)
			{
				value = "maxsuccessrate";
				type=1;
			}
			if(order == 7)
			{
				value = "minsuccessrate";
				type=1;
			}
			if(order == 8)
			{
				value = "maxscore";
				type=1;
			}
			if(order == 9)
			{
				value = "minscore";
				type=1;
			}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}

			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_maxresabundance);

			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_minresabundance);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_maxp10divp90);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_minp10divp90);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_maxsuccessrate);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_minsuccessrate);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_maxscore);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%.3f", m_minscore);
			}
		}

		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_maxresabundance= ::atof(value.c_str());

			}
			if(order == 3)
			{
				m_minresabundance= ::atof(value.c_str());
				
			}
			if(order == 4)
			{
				m_maxp10divp90= ::atof(value.c_str());
				
			}
			if(order == 5)
			{
				m_minp10divp90= ::atof(value.c_str());
				
			}
			if(order == 6)
			{
				m_maxsuccessrate= ::atof(value.c_str());
				
			}
			if(order == 7)
			{
				m_minsuccessrate= ::atof(value.c_str());
				
			}
			if(order == 8)
			{
				m_maxscore= ::atof(value.c_str());

			}
			if(order == 9)
			{
				m_minscore = ::atof(value.c_str());

			}
		}



	};

	struct SurveyPic : public PropertyRecord
	{
		string		m_seissurvey  ;
		string		m_seisquality  ;
		string		m_seisprofile 	 ;
		string		m_seisfrequency 	 ;
		string		m_seislandscape 	 ;

		char 		*m_charseissurvey  ;
		char 		*m_charseisquality  ;
		char 		*m_charseisprofile 	 ;
		char 		*m_charseisfrequency 	 ;
		char		*m_charseislandscape 	 ;

		long		m_lengthseissurvey    ;
		long		m_lengthseisquality   ;
		long		m_lengthseisprofile 	;
		long		m_lengthseisfrequency ;
		long        m_lengthseislandscape 	 ;			






		SurveyPic()
		{

			m_seissurvey    ="";
			m_seisquality  	="";
			m_seisprofile 	="";
			m_seisfrequency	="";
			m_seislandscape="";

			m_charseissurvey         =NULL;
			m_charseisquality        =NULL;
			m_charseisprofile 	     =NULL;
			m_charseisfrequency 	 =NULL;
			m_charseislandscape      =NULL;

			m_lengthseissurvey         =0;
			m_lengthseisquality        =0;
			m_lengthseisprofile 	   =0;
			m_lengthseisfrequency 	   =0;
			m_lengthseislandscape      =0;


		}
		const SurveyPic &operator=(const SurveyPic &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_seissurvey      =other.m_seissurvey    ;
			m_seisquality  	  =other.m_seisquality   ;
			m_seisprofile 	  =other.m_seisprofile 	 ;
			m_seisfrequency	  =other.m_seisfrequency ;
			m_seislandscape   =other.m_seislandscape ;
			return *this;
		}
		int GetFldCount()
		{
			return 7;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text 
		{
			if(order == 0) 
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			if(order == 2)
			{
				value = "seissurvey";
				type=3;
			}
			if(order == 3)
			{
				value = "seisquality";
				type=3;
			}
			if(order == 4)
			{
				value = "seisprofile";
				type=3;
			}
			if(order == 5)
			{
				value = "seisfrequency";
				type=3;
			}
			if(order == 6)
			{
				value = "seislandscape";
				type=3;
			}
			
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}

			if(order == 2)
			{
				value = "";

			}
			if(order == 3)
			{
				value = "";
			}
			if(order == 4)
			{
				value = "";
			}
			if(order == 5)
			{
				value = "";
			}
			
		}

		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				

			}
			if(order == 3)
			{
				

			}
			if(order == 4)
			{
				

			}
			if(order == 5)
			{
				

			}
			if(order == 6)
			{


			}
			
		}
	};
	/*!
	*
	**/
	struct SegmentRecord : public PropertyRecord
	{
		// oil/gas contact[m]
		ProbabilityField m_oilgas;
		// hc water contact
		ProbabilityField m_hcwater;
		// spill depth
		ProbabilityField m_spilldepth;
		// thickness multiplier
		ProbabilityField m_thick;

		/*!
		*
		**/
		const SegmentRecord &operator=(const SegmentRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_oilgas = other.m_oilgas;
			m_hcwater = other.m_hcwater;
			m_spilldepth = other.m_spilldepth;
			m_thick = other.m_thick;

			return *this;
		}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 4 * 2 + 2;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		/*!
		*
		**/
		void GetFldDesc(int order, string &desc)
		{
			order -= 2;
			if(order >= 0  && order <= 1)
			{
				desc = "Oil/Gas contact[m]";
			}
			if(order >= 2 && order <= 3)
			{
				desc = "HC/Water contact[m]";
			}
			if(order >= 4 && order <= 5)
			{
				desc = "Spill depth[m]";
			}
			if(order >= 6 && order <= 7)
			{
				desc = "Thickness multiplier[m]";
			}
		}

		/*!
		*
		**/
		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_oilgas.m_idx);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%s", m_oilgas.m_parameter.c_str());
			}
			if(order == 4) 
			{
				::sprintf((char *)value.c_str(), "%d", m_hcwater.m_idx);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%s", m_hcwater.m_parameter.c_str());
			}
			if(order == 6) 
			{
				::sprintf((char *)value.c_str(), "%d", m_spilldepth.m_idx);
			}
			if(order == 7) 
			{
				::sprintf((char *)value.c_str(), "%d", m_spilldepth.m_idx);
			}
			if(order == 8) 
			{
				::sprintf((char *)value.c_str(), "%d", m_thick.m_idx);
			}
			if(order == 9) 
			{
				::sprintf((char *)value.c_str(), "%d", m_thick.m_idx);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0) 
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_oilgas.m_idx = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_oilgas.m_parameter = value;
			}
			if(order == 4) 
			{
				m_hcwater.m_idx = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_hcwater.m_parameter = value;
			}
			if(order == 6) 
			{
				m_spilldepth.m_idx = ::atoi(value.c_str());
			}
			if(order == 7)
			{
				m_spilldepth.m_parameter = value;
			}
			if(order == 8) 
			{
				m_thick.m_idx = ::atoi(value.c_str());
			}
			if(order == 9)
			{
				m_thick.m_parameter = value;
			}
		}
	};

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*!
	用于外部Excel数据导入
	**/
	struct ImportExcelHistroy
	{
		string m_name;
		ExplorationRecord m_historyRecord;
	};

	struct ImportExcelPool
	{
		string m_name;
		PoolRecord m_poolRecord;
	};

	struct ImportExcelVol
	{
		string m_name;
		VolumeRecord m_VolRecord;
	};

	struct ShaleWellBasic : public PropertyRecord
	{
		long	m_wellid				;
		long	m_classid				;
		long	m_geometryid			;
		long	m_adminid				;
		string  m_name				;
		float	m_longitude			;
		float	m_latitude			;
		float	m_xcoord				;
		float	m_ycoord				;
		float	m_groundevaluation	;
		float	m_totaldepth			;
		string	m_groupnumber			;
		string	m_wellnumber			;
		string	m_wellstatus			;
		string	m_welltype			;
		string	m_boretype			;
		string	m_fluidtype			;
		float	m_nullvalue			;
		float	m_wellkb				;
		float	m_welleurs				;
		float	m_welldrainage				;

		ShaleWellBasic()
		{
			m_wellid			=0;
			m_classid			=0;
			m_geometryid		=0;
			m_adminid			=0;
			m_name				="";
			m_longitude			=0;
			m_latitude			=0;
			m_xcoord			=0;
			m_ycoord			=0;
			m_groundevaluation	=0;
			m_totaldepth		=0;
			m_groupnumber		="";
			m_wellnumber		="";
			m_wellstatus		="";
			m_welltype			="";
			m_boretype			="";
			m_fluidtype			="";
			m_nullvalue			=0;
			m_wellkb			=0;
			m_welleurs			=0;
			m_welldrainage		=0;

		}
		const ShaleWellBasic &operator=(const ShaleWellBasic &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_wellid			=other.m_wellid					;
			m_classid			=other.m_classid				;
			m_geometryid		=other.m_geometryid				;
			m_adminid			=other.m_adminid				;
			m_name				=other.m_name					;
			m_longitude			=other.m_longitude				;
			m_latitude			=other.m_latitude				;
			m_xcoord			=other.m_xcoord					;
			m_ycoord			=other.m_ycoord					;
			m_groundevaluation	=other.m_groundevaluation		;
			m_totaldepth		=other.m_totaldepth				;
			m_groupnumber		=other.m_groupnumber			;
			m_wellnumber		=other.m_wellnumber				;
			m_wellstatus		=other.m_wellstatus				;
			m_welltype			=other.m_welltype				;
			m_boretype			=other.m_boretype				;
			m_fluidtype			=other.m_fluidtype				;
			m_nullvalue			=other.m_nullvalue				;
			m_wellkb			=other.m_wellkb					;
			m_welleurs			=other.m_welleurs					;
			m_welldrainage		=other.m_welldrainage					;
			return *this;
		}
		int GetFldCount()
		{
			return 23;
		}


		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order ==2 || order==3 || order==4 || order==5)
			{
				return true;
			}
			return false;
		}


		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text 
		{
			
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}		if(order == 1)
			
			if(order == 1)
			{
				value = "elementid";
				type=0;
			}
			if(order == 2) 
			{
				value = "wellid";
				type=0;
			}
	
			if(order == 3)
			{
				value = "classid";
				type=0;
			}
			if(order == 4)
			{
				value = "geometryid";
				type=0;
			}
			if(order == 5)
			{
				value = "adminid";
				type=0;
			}
			if(order == 6)
			{
				value = "name";
				type=2;
			}
			if(order == 7)
			{
				value = "longitude";
				type=1;
			}
			if(order == 8)
			{
				value = "latitude";
				type=1;
			}
			if(order == 9)
			{
				value = "xcoord";
				type=1;
			}
			if(order == 10)
			{
				value = "ycoord";
				type=1;
			}
			if(order == 11)
			{
				value = "groundevaluation";
				type=1;
			}
			if(order == 12)
			{
				value = "totaldepth";
				type=1;
			}
			if(order == 13)
			{
				value = "groupnumber";
				type=2;
			}
			if(order == 14)
			{
				value = "wellnumber";
				type=2;
			}
			if(order == 15)
			{
				value = "wellstatus";
				type=2;
			}
			if(order == 16)
			{
				value = "welltype";
				type=2;
			}
			if(order == 17)
			{
				value = "boretype";
				type=2;
			}
			if(order == 18)
			{
				value = "fluidtype";
				type=2;
			}
			if(order == 19)
			{
				value = "nullvalue";
				type=1;
			}
			if(order == 20)
			{
				value = "wellkb";
				type=1;
			}
			if(order == 21)
			{
				value = "welleurs";
				type=1;
			}
			if(order == 22)
			{
				value = "welldrainage";
				type=1;
			}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			
			
			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			
			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_wellid);
			}
		
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_classid);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_geometryid);

			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%d",m_adminid);
			}
			
			if(order == 6)
			{
				//::sprintf((char *)value.c_str(), "%s", m_name.c_str());
				value=m_name;
			}
			
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_longitude);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_latitude);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_xcoord);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_ycoord);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_groundevaluation);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_totaldepth);
			}
			if(order == 13)
			{
				//::sprintf((char *)value.c_str(), "%s", m_groupnumber.c_str());
				value=m_groupnumber;
			}
			if(order == 14)
			{
				//::sprintf((char *)value.c_str(), "%s", m_wellnumber.c_str());
				value=m_wellnumber;
			}
			if(order == 15)
			{
				//::sprintf((char *)value.c_str(), "%s", m_wellstatus.c_str());
				value=m_wellstatus;
			}
			if(order == 16)
			{
				//::sprintf((char *)value.c_str(), "%s", m_welltype.c_str());
				value=m_welltype;
			}
			if(order == 17)
			{
				//::sprintf((char *)value.c_str(), "%s", m_boretype.c_str());
				value=m_boretype;
			}
			if(order == 18)
			{
				//::sprintf((char *)value.c_str(), "%s", m_fluidtype.c_str());
				value=m_fluidtype;
			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%f", m_nullvalue);
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_wellkb);
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_welleurs);
			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%f", m_welldrainage);
			}
		}



		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_wellid = ::atoi(value.c_str());
			}
		
			if(order == 3)
			{
				m_classid = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_geometryid = ::atoi(value.c_str());

			}
			if(order == 5)
			{
				m_adminid = ::atoi(value.c_str());

			}
			if(order == 6)
			{
				m_name = value.c_str();
			}

			if(order == 7)
			{
				m_longitude = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_latitude = ::atof(value.c_str());
				
			}
			if(order == 9)
			{
				m_xcoord = ::atof(value.c_str());
				
			}
			if(order == 10)
			{
				m_ycoord = ::atof(value.c_str());
				
			}
			if(order == 11)
			{
				m_groundevaluation = ::atof(value.c_str());
				
			}
			if(order == 12)
			{
				m_totaldepth = ::atof(value.c_str());
				
			}
			if(order == 13)
			{
				m_groupnumber = value.c_str();
				
			}
			if(order == 14)
			{
				m_wellnumber = value.c_str();
				
			}
			if(order == 15)
			{
				m_wellstatus = value.c_str();
				
			}
			if(order == 16)
			{
				m_welltype = value.c_str();
				
			}
			if(order == 17)
			{
				m_boretype = value.c_str();
				
			}
			if(order == 18)
			{
				m_fluidtype = value.c_str();
				
			}
			if(order == 19)
			{
				m_nullvalue = ::atof(value.c_str());
				
			}
			if(order == 20)
			{
				m_wellkb = ::atof(value.c_str());
				
			}
			if(order == 21)
			{
				m_welleurs = ::atof(value.c_str());

			}
			if(order == 22)
			{
				m_welldrainage = ::atof(value.c_str());

			}
		}
	};



	struct ShaleWellProduction : public PropertyRecord
	{
		long	m_boreid					;
		long	m_productiondate			;
		float	m_productionstart			;
		float	m_productionprediction		;
		float	m_productionactual			;
		float	m_declinestart				;
		float	m_declineprediction			;
		float	m_declineactual				;
		string	m_declineformular			;
		float	m_productiondays			;
		float	m_watercut					;
		double  m_date						;
		double	m_practicalProduction		;
		double	m_practicaldecline			;

		ShaleWellProduction()
		{
			m_boreid				=0;
			m_productiondate		=0;
			m_productionstart		=0;
			m_productionprediction	=0;
			m_productionactual		=0;
			m_declinestart			=0;
			m_declineprediction		=0;
			m_declineactual			=0;
			m_declineformular		="";
			m_productiondays		=0;
			m_watercut				=0;
			m_date					=0;
			m_practicalProduction	=0;
			m_practicaldecline		=0;

		}
		const ShaleWellProduction &operator=(const ShaleWellProduction &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_boreid				=other.m_boreid				;
			m_productiondate		=other.m_productiondate		;
			m_productionstart		=other.m_productionstart		;
			m_productionprediction	=other.m_productionprediction	;
			m_productionactual		=other.m_productionactual		;
			m_declinestart			=other.m_declinestart			;
			m_declineprediction		=other.m_declineprediction		;
			m_declineactual			=other.m_declineactual			;
			m_declineformular		=other.m_declineformular		;
			m_productiondays		=other.m_productiondays			;
			m_watercut				=other.m_watercut				;
			m_date					=other.m_date					;
			m_practicalProduction	=other.m_practicalProduction	;
			m_practicaldecline		=other.m_practicaldecline		;
			return *this;
		}
		int GetFldCount()
		{
			return 13;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text 
		{

			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}		if(order == 1)

				if(order == 1)
				{
					value = "elementid";
					type=0;
				}
				if(order == 2) 
				{
					value = "boreid";
					type=0;
				}

				if(order == 3)
				{
					value = "productiondate";
					type=0;
				}
				if(order == 4)
				{
					value = "productionstart";
					type=1;
				}
				if(order == 5)
				{
					value = "productionprediction";
					type=1;
				}
				if(order == 6)
				{
					value = "productionactual";
					type=1;
				}
				if(order == 7)
				{
					value = "declinestart";
					type=1;
				}
				if(order == 8)
				{
					value = "declineprediction";
					type=1;
				}
				if(order == 9)
				{
					value = "declineactual";
					type=1;
				}
				if(order == 10)
				{
					value = "declineformular";
					type=2;
				}
				if(order == 11)
				{
					value = "productiondays";
					type=1;
				}
				if(order == 12)
				{
					value = "watercut";
					type=1;
				}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";


			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}

			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}

			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_boreid);
			}

			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_productiondate);
			}

			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_productionstart);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_productionprediction);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_productionactual);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_declinestart);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_declineprediction);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_declineactual);
			}
			if(order == 10)
			{
				//::sprintf((char *)value.c_str(), "%s", m_declineformular.c_str());
				value=m_declineformular;
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_productiondays);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_watercut);
			}
		}



		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}

			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_boreid = ::atoi(value.c_str());
			}

			if(order == 3)
			{
				m_productiondate = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_productionstart = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_productionprediction = ::atof(value.c_str());

			}
			if(order == 6)
			{
				m_productionactual = ::atof(value.c_str());

			}
			if(order == 7)
			{
				m_declinestart = ::atof(value.c_str());

			}
			if(order == 8)
			{
				m_declineprediction = ::atof(value.c_str());

			}
			if(order == 9)
			{
				m_declineactual = ::atof(value.c_str());

			}
			if(order == 10)
			{
				m_declineformular = value.c_str();

			}
			
			if(order == 11)
			{
				m_productiondays = ::atof(value.c_str());

			}
			if(order ==12)
			{
				m_watercut = ::atof(value.c_str());

			}

		}
	};

	struct ShaleWellBore : public PropertyRecord
	{
		long	m_boreid					;
		long	m_wellid					;
		string	m_name						;
		string	m_targettstrata				;
		float	m_perforationnumber			;
		float	m_perforationlength			;
		float	m_horizontallength			;
	

		ShaleWellBore()
		{
			m_boreid			=0;
			m_wellid			=0;
			m_name				="";
			m_targettstrata		="";
			m_perforationnumber	=0;
			m_perforationlength	=0;
			m_horizontallength	=0;
	
		}
		const ShaleWellBore &operator=(const ShaleWellBore &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_boreid			=other.m_boreid			;
			m_wellid			=other.m_wellid			;	
			m_name				=other.m_name				;
			m_targettstrata		=other.m_targettstrata		;
			m_perforationnumber	=other.m_perforationnumber	;
			m_perforationlength	=other.m_perforationlength	;
			m_horizontallength	=other.m_horizontallength	;
	
		}
		int GetFldCount()
		{
			return 7;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text 
		{

			if(order == 0)
			{
				value = "boreid";
				type=0;
			}		if(order == 1)

				if(order == 1)
				{
					value = "wellid";
					type=0;
				}
				if(order == 2) 
				{
					value = "name";
					type=0;
				}

				if(order == 3)
				{
					value = "targettstrata";
					type=0;
				}
				if(order == 4)
				{
					value = "perforationnumber";
					type=1;
				}
				if(order == 5)
				{
					value = "perforationlength";
					type=1;
				}
				if(order == 6)
				{
					value = "horizontallength";
					type=1;
				}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";


			if(order == 0)
			{
				::sprintf((char *)value.c_str(), "%d", m_boreid);
			}

			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_wellid);
			}

			if(order == 2) 
			{
				::sprintf((char *)value.c_str(), "%d", m_boreid);
			}
			if(order == 3)
			{
				//::sprintf((char *)value.c_str(), "%s", m_name.c_str());
				value=m_name;
			}
			if(order == 4)
			{
				//::sprintf((char *)value.c_str(), "%s", m_targettstrata.c_str());
				value=m_targettstrata;
			}
			
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_perforationnumber);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_perforationlength);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_horizontallength);
			}
			
		}



		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_boreid = ::atoi(value.c_str());
			}

			if(order == 1)
			{
				m_wellid = ::atoi(value.c_str());
			}
			if(order == 2) 
			{
				m_boreid = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_name = value.c_str();

			}
			if(order == 4)
			{
				m_targettstrata = value.c_str();

			}

			if(order == 5)
			{
				m_perforationnumber = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_perforationlength = ::atof(value.c_str());

			}
			if(order == 7)
			{
				m_horizontallength = ::atof(value.c_str());

			}

		}
	};

	struct ShaleVolumeRecord : public PropertyRecord
	{
		double m_productArea	;
		double m_grossThickness	;
		double m_R				;
		double m_TOC			;
		double m_psh			;
		double m_po				;
		double m_S1				;
		double m_C				;
		double m_S20			;
		double m_bhc			;
		double m_rf				;
		double m_tr				;
		double m_cf				;

		/*!
		*
		**/
		ShaleVolumeRecord() :  m_productArea(1.), m_grossThickness(1.), m_R(1.), m_TOC(1.), m_psh(1.), m_po(1.), m_S1(1.),\
			m_C(1.), m_S20(1.), m_bhc(1.), m_rf(1.), m_tr(1.), m_cf(1.)
		{
		}

		/*!
		*
		**/
		const ShaleVolumeRecord &operator=(const ShaleVolumeRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent info
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_isUpdated = other.m_isUpdated;
			m_isDeleted = other.m_isDeleted;
			m_isAdded = other.m_isAdded;

			m_productArea	= other.m_productArea	;
			m_grossThickness	= other.m_grossThickness;	
			m_R				= other.m_R				;
			m_TOC			= other.m_TOC			;
			m_psh			= other.m_psh			;
			m_po				= other.m_po			;	
			m_S1				= other.m_S1			;	
			m_C				= other.m_C				;
			m_S20			= other.m_S20			;
			m_bhc			= other.m_bhc			;
			m_rf				= other.m_rf			;	
			m_tr				= other.m_tr			;	
			m_cf				= other.m_cf			;	

			//
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
			return 15;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "productarea";
				type=1;

			}
			if(order == 3)
			{
				value = "grossthickness";
				type=1;

			}
			if(order == 4)
			{
				value = "wvsr";
				type=1;

			}
			if(order == 5)
			{
				value = "wvstoc";
				type=1;

			}
			if(order == 6)
			{
				value = "wvspsh";
				type=1;

			}
			if(order == 7)
			{
				value = "wvspo";
				type=1;

			}
			if(order == 8)
			{
				value = "wvssone";
				type=1;

			}
			if(order == 9)
			{
				value = "wvsc";
				type=1;

			}
			if(order == 10)
			{
				value = "wvsstwenty";
				type=1;

			}
			if(order == 11)
			{
				value = "wvsbhc";
				type=1;

			}
			if(order == 12)
			{
				value = "wvsrf";
				type=1;

			}
			if(order == 13)
			{
				value = "wvstr";
				type=1;

			}
			if(order == 14)
			{
				value = "wvscf";
				type=1;

			}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%f", m_productArea);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_grossThickness);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_R);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_TOC);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_psh);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_po);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_S1);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_C);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_S20);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_bhc);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_rf);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_tr);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_cf);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_productArea = ::atof(value.c_str());
			}
			if(order == 3)
			{
				m_grossThickness = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_R = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_TOC = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_psh = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_po = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_S1 = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_C = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_S20 = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_bhc = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_rf = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_tr = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_cf = ::atof(value.c_str());
			}
		}
	};

	struct ShaleWellVariableRecord : public PropertyRecord
	{
			long  m_wellid ;
		    string m_name;
			long  m_ishc ;
			float m_xcoord ;
			float m_ycoord ;
			float m_grossthickness ;
			float m_netthickness ;
			float m_porosity ;
			float m_saturation ;
			float m_netgross ;
			float m_capthickness ;
			float m_estimateduplift ;
			float m_presuregradient ;
			float m_salinitygradient ;
			float m_structure ;
			float m_structureresiduals ;
			float m_md ;
			float m_risk ;
			float m_mresource ;
			float m_predication ;
			float m_sourcerockthickness ;
			float m_toccontent ;
			float m_romaturity ;
			float m_absortedgas ;
			float m_dailyproduction ;
		   string m_organictype;
			float m_wellrecovery ;
			float m_wellreserve ;
			float m_resourceabundance ;
			float m_mineralcomponent; 
			float m_forg;

		/*!
		*
		**/
		ShaleWellVariableRecord()
		{
			m_wellid =0;
			m_name="";
			m_ishc =0;
			m_xcoord =0;
			m_ycoord =0;
			m_grossthickness =0;
			m_netthickness =0;
			m_porosity =0;
			m_saturation =0;
			m_netgross =0;
			m_capthickness =0;
			m_estimateduplift =0;
			m_presuregradient =0;
			m_salinitygradient =0;
			m_structure =0;
			m_structureresiduals =0;
			m_md =0;
			m_risk =0;
			m_mresource =0;
			m_predication =0;
			m_sourcerockthickness =0;
			m_toccontent =0;
			m_romaturity =0;
			m_absortedgas =0;
			m_dailyproduction =0;
			m_organictype="";
			m_wellrecovery =0;
			m_wellreserve =0;
			m_resourceabundance =0;
			m_mineralcomponent=0; 
			m_forg=0;
		}

		/*!
		*
		**/
		const ShaleWellVariableRecord &operator=(const ShaleWellVariableRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_wellid 				=other.m_wellid					;
			m_name					=other.m_name					;
			m_ishc 					=other.m_ishc 					;
			m_xcoord 				=other.m_xcoord 				;
			m_ycoord 				=other.m_ycoord 				;
			m_grossthickness 		=other.m_grossthickness 		;
			m_netthickness 			=other.m_netthickness 			;
			m_porosity 				=other.m_porosity 				;
			m_saturation 			=other.m_saturation 			;
			m_netgross 				=other.m_netgross 				;//9
			m_capthickness 			=other.m_capthickness 			;
			m_estimateduplift 		=other.m_estimateduplift 		;
			m_presuregradient 		=other.m_presuregradient 		;
			m_salinitygradient 		=other.m_salinitygradient 		;
			m_structure 			=other.m_structure 				;
			m_structureresiduals 	=other.m_structureresiduals 	;
			m_md 					=other.m_md 					;
			m_risk 					=other.m_risk 					;
			m_mresource 			=other.m_mresource 				;
			m_predication 			=other.m_predication 			;//19
			m_sourcerockthickness 	=other.m_sourcerockthickness	;//20
			m_toccontent 			=other.m_toccontent 			;
			m_romaturity 			=other.m_romaturity 			;
			m_absortedgas 			=other.m_absortedgas 			;
			m_dailyproduction 		=other.m_dailyproduction 		;
			m_organictype			=other.m_organictype			;
			m_wellrecovery 			=other.m_wellrecovery 			;
			m_wellreserve 			=other.m_wellreserve 			;
			m_resourceabundance 	=other.m_resourceabundance 		;
			m_mineralcomponent 		=other.m_mineralcomponent 		;//29
			m_forg					=other.m_forg;
			//
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
			return 33;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "wellid";
				type=0;

			}
			if(order == 3)
			{
				value = "name";
				type=2;

			}
			if(order == 4)
			{
				value = "ishc";
				type=0;

			}
			if(order == 5)
			{
				value = "xcoord";
				type=1;

			}
			if(order == 6)
			{
				value = "ycoord";
				type=1;

			}
			if(order == 7)
			{
				value = "grossthickness";
				type=1;

			}
			if(order == 8)
			{
				value = "netthickness";
				type=1;

			}
			if(order == 9)
			{
				value = "porosity";
				type=1;

			}
			if(order == 10)
			{
				value = "saturation";
				type=1;

			}
			if(order == 11)
			{
				value = "netgross";
				type=1;

			}
			if(order == 12)
			{
				value = "capthickness";
				type=1;

			}
			if(order == 13)
			{
				value = "estimateduplift";
				type=1;

			}
			if(order == 14)
			{
				value = "presuregradient";
				type=1;

			}
			if(order == 15)
			{
				value = "salinitygradient";
				type=1;

			}
			if(order == 16)
			{
				value = "structure";
				type=1;
			}
			if(order == 17)
			{
				value = "structureresiduals";
				type=1;

			}
			if(order == 18)
			{
				value = "md";
				type=1;

			}
			if(order == 19)
			{
				value = "risk";
				type=1;

			}
			if(order == 20)
			{
				value = "mresource";
				type=1;

			}
			if(order == 21)
			{
				value = "predication";
				type=1;

			}
			if(order == 22)
			{
				value = "sourcerockthickness";
				type=1;

			}
			if(order == 23)
			{
				value = "toccontent";
				type=1;

			}
			if(order == 24)
			{
				value = "romaturity";
				type=1;

			}
			if(order == 25)
			{
				value = "absortedgas";
				type=1;

			}
			if(order == 26)
			{
				value = "dailyproduction";
				type=1;

			}
			if(order == 27)
			{
				value = "organictype";
				type=2;

			}
			if(order == 28)
			{
				value = "wellrecovery";
				type=1;

			}
			if(order == 29)
			{
				value = "wellreserve";
				type=1;

			}
			if(order == 30)
			{
				value = "resourceabundance";
				type=1;

			}
			if(order == 31)
			{
				value = "mineralcomponent";
				type=1;

			}
			if(order == 32)
			{
				value = "forg";
				type=1;

			}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_wellid);
			}
			if(order == 3)
			{
				value=m_name;
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_ishc);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_xcoord);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_ycoord);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_grossthickness);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_netthickness);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_porosity);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_saturation);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_netgross);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_capthickness);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%f", m_estimateduplift);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_presuregradient);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%f", m_salinitygradient);
			}
			if(order == 16)
			{
				::sprintf((char *)value.c_str(), "%f", m_structure);
			}
			if(order ==17)
			{
				::sprintf((char *)value.c_str(), "%f", m_structureresiduals);
			}	
			if(order == 18)
			{
				::sprintf((char *)value.c_str(), "%f", m_md);
			}
			if(order == 19)
			{
				::sprintf((char *)value.c_str(), "%f", m_risk);
			}
			if(order == 20)
			{
				::sprintf((char *)value.c_str(), "%f", m_mresource);
			}
			if(order == 21)
			{
				::sprintf((char *)value.c_str(), "%f", m_predication);
			}
			if(order == 22)
			{
				::sprintf((char *)value.c_str(), "%f", m_sourcerockthickness);
			}
			if(order == 23)
			{
				::sprintf((char *)value.c_str(), "%f", m_toccontent);
			}
			if(order == 24)
			{
				::sprintf((char *)value.c_str(), "%f", m_romaturity);
			}
			if(order == 25)
			{
				::sprintf((char *)value.c_str(), "%f", m_absortedgas);
			}
			if(order == 26)
			{
				::sprintf((char *)value.c_str(), "%f", m_dailyproduction);
			}
			if(order == 27)
			{
				value=m_organictype;
			}
			if(order == 28)
			{
				::sprintf((char *)value.c_str(), "%f", m_wellrecovery);
			}
			if(order == 29)
			{
				::sprintf((char *)value.c_str(), "%f", m_wellreserve);
			}
			if(order == 30)
			{
				::sprintf((char *)value.c_str(), "%f", m_resourceabundance);
			}
			if(order == 31)
			{
				::sprintf((char *)value.c_str(), "%f", m_mineralcomponent);
			}
			if(order == 32)
			{
				::sprintf((char *)value.c_str(), "%f", m_forg);
			}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_wellid = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_name = value.c_str();
			}
			if(order == 4)
			{
				m_ishc= ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_xcoord = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_ycoord = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_grossthickness = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_netthickness = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_porosity = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_saturation = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_netgross = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_capthickness = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_estimateduplift = ::atof(value.c_str());
			}
			if(order == 14)
			{
				m_presuregradient = ::atof(value.c_str());
			}
			if(order == 15)
			{
				m_salinitygradient = ::atof(value.c_str());
			}
			if(order == 16)
			{
				m_structure = ::atof(value.c_str());
			}
			if(order == 17)
			{
				m_structureresiduals = ::atof(value.c_str());
			}
			if(order == 18)
			{
				m_md = ::atof(value.c_str());
			}
			if(order == 19)
			{
				m_risk = ::atof(value.c_str());
			}
			if(order == 20)
			{
				m_mresource = ::atof(value.c_str());
			}
			if(order == 21)
			{
				m_predication = ::atof(value.c_str());
			}
			if(order == 22)
			{
				m_sourcerockthickness = ::atof(value.c_str());
			}
			if(order == 23)
			{
				m_toccontent = ::atof(value.c_str());
			}
			if(order == 24)
			{
				m_romaturity = ::atof(value.c_str());
			}
			if(order == 25)
			{
				m_absortedgas = ::atof(value.c_str());
			}
			if(order == 26)
			{
				m_dailyproduction = ::atof(value.c_str());
			}
			if(order == 27)
			{
				m_organictype = value;
			}
			if(order == 28)
			{
				m_wellrecovery = ::atof(value.c_str());
			}
			if(order == 29)
			{
				m_wellreserve = ::atof(value.c_str());
			}
			if(order == 30)
			{
				m_resourceabundance = ::atof(value.c_str());
			}
			if(order == 31)
			{
				m_mineralcomponent = ::atof(value.c_str());
			}
			if(order == 32)
			{
				m_forg = ::atof(value.c_str());
			}
			
		}
	};


	struct BlockBasinRecord : public PropertyRecord
	{
		string	m_basinname			;
		float	m_oilresource		;
		float	m_gasresource		;	
		float	m_oilprovedreserves	;		
		float	m_gasprovedreserves	;			
		float	m_area				;
		string	m_type				;
		string	m_location			;
		string	m_remark			;
	

		/*!
		*
		**/
		BlockBasinRecord() 
		{
			m_basinname			="" ;
			m_oilresource		=0.0;
			m_gasresource		=0.0;
			m_oilprovedreserves	=0.0;
			m_gasprovedreserves	=0.0;
			m_area				=0.0;
			m_type				="" ;
			m_location			="" ;
			m_remark			="" ;
		}

		/*!
		*
		**/
		const BlockBasinRecord &operator=(const BlockBasinRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_basinname			=other.	m_basinname			;
			m_oilresource		=other.	m_oilresource		;
			m_gasresource		=other.	m_gasresource		;
			m_oilprovedreserves	=other.	m_oilprovedreserves	;
			m_gasprovedreserves	=other.	m_gasprovedreserves	;
			m_area				=other.	m_area				;
			m_type				=other.	m_type				;
			m_location			=other.	m_location			;
			m_remark			=other.	m_remark			;

			//
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
			return 11;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "basinname";
				type=2;

			}
			if(order == 3)
			{
				value = "oilresource";
				type=1;

			}
			if(order == 4)
			{
				value = "gasresource";
				type=1;

			}
			if(order == 5)
			{
				value = "oilprovedreserves";
				type=1;

			}
			if(order == 6)
			{
				value = "gasprovedreserves";
				type=1;

			}
			if(order == 7)
			{
				value = "area";
				type=1;

			}
			if(order == 8)
			{
				value = "type";
				type=2;

			}
			if(order == 9)
			{
				value = "location";
				type=2;

			}
			if(order == 10)
			{
				value = "remark";
				type=2;

			}
			
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value=m_basinname;
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilresource);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%f", m_gasresource);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilprovedreserves);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_gasprovedreserves);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_area);
			}
			if(order == 8)
			{
				value=m_type;
			}
			if(order == 9)
			{
				value=m_location;
			}
			if(order == 10)
			{
				value=m_remark;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_basinname = value;
			}
			if(order == 3)
			{
				m_oilresource = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_gasresource = ::atof(value.c_str());
			}
			if(order == 5)
			{
				m_oilprovedreserves = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_gasprovedreserves = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_area = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_type = value;
			}
			if(order == 9)
			{
				m_location = value;
			}
			if(order == 10)
			{
				m_remark = value;
			}
			
		}
	};


	struct BlockPrimaryStructuralrecord : public PropertyRecord
	{
		string	m_primarystructuralname			;	
		float	m_area							;
		string	m_type							;
		string	m_remark						;
	

		/*!
		*
		**/
		BlockPrimaryStructuralrecord() 
		{
			m_primarystructuralname			="" ;
			m_area							=0.0;
			m_type							="" ;
			m_remark						="" ;
		}

		/*!
		*
		**/
		const BlockPrimaryStructuralrecord &operator=(const BlockPrimaryStructuralrecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_primarystructuralname			=other.	m_primarystructuralname			;
			m_area							=other.	m_area				;
			m_type							=other.	m_type				;
			m_remark						=other.	m_remark			;

			//
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
			return 6;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "primarystructuralname";
				type=2;

			}
			if(order == 3)
			{
				value = "area";
				type=1;

			}
			if(order == 4)
			{
				value = "type";
				type=2;

			}
			if(order == 5)
			{
				value = "remark";
				type=2;

			}
			
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value=m_primarystructuralname;
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_area);
			}
			if(order == 4)
			{
				value=m_type;
			}
			if(order == 5)
			{
				value=m_remark;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_primarystructuralname = value;
			}
			if(order == 3)
			{
				m_area = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_type = value;
			}
			if(order == 5)
			{
				m_remark = value;
			}
			
		}
	};



	struct BlockSecondaryStructuralrecord : public PropertyRecord
	{
		string	m_blocksecondarystructuralname	;	
		float	m_area							;
		string	m_type							;
		string	m_remark						;
	

		/*!
		*
		**/
		BlockSecondaryStructuralrecord() 
		{
			m_blocksecondarystructuralname	="" ;
			m_area							=0.0;
			m_type							="" ;
			m_remark						="" ;
		}

		/*!
		*
		**/
		const BlockSecondaryStructuralrecord &operator=(const BlockSecondaryStructuralrecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_blocksecondarystructuralname	=other.	m_blocksecondarystructuralname			;
			m_area							=other.	m_area				;
			m_type							=other.	m_type				;
			m_remark						=other.	m_remark			;

			//
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
			return 6;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "blocksecondarystructuralname";
				type=2;

			}
			if(order == 3)
			{
				value = "area";
				type=1;

			}
			if(order == 4)
			{
				value = "type";
				type=2;

			}
			if(order == 5)
			{
				value = "remark";
				type=2;

			}
			
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value=m_blocksecondarystructuralname;
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_area);
			}
			if(order == 4)
			{
				value=m_type;
			}
			if(order == 5)
			{
				value=m_remark;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_blocksecondarystructuralname = value;
			}
			if(order == 3)
			{
				m_area = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_type = value;
			}
			if(order == 5)
			{
				m_remark = value;
			}
			
		}
	};

	struct BlockThirdStructuralrecord : public PropertyRecord
	{
		string	m_blockthirdstructuralname		;	
		float	m_area							;
		string	m_type							;
		string	m_remark						;
	

		/*!
		*
		**/
		BlockThirdStructuralrecord() 
		{
			m_blockthirdstructuralname		="" ;
			m_area							=0.0;
			m_type							="" ;
			m_remark						="" ;
		}

		/*!
		*
		**/
		const BlockThirdStructuralrecord &operator=(const BlockThirdStructuralrecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_blockthirdstructuralname		=other.	m_blockthirdstructuralname			;
			m_area							=other.	m_area				;
			m_type							=other.	m_type				;
			m_remark						=other.	m_remark			;

			//
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
			return 6;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "blockthirdstructuralname";
				type=2;

			}
			if(order == 3)
			{
				value = "area";
				type=1;

			}
			if(order == 4)
			{
				value = "type";
				type=2;

			}
			if(order == 5)
			{
				value = "remark";
				type=2;

			}
			
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value=m_blockthirdstructuralname;
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_area);
			}
			if(order == 4)
			{
				value=m_type;
			}
			if(order == 5)
			{
				value=m_remark;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_blockthirdstructuralname = value;
			}
			if(order == 3)
			{
				m_area = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_type = value;
			}
			if(order == 5)
			{
				m_remark = value;
			}
			
		}
	};


struct BlockPicsrecord : public PropertyRecord
	{
		string	m_kuangquanqukuainame		;	
		string	m_youqikantanchengduname	;
		string	m_youqikantanchengguoname	;
		string	m_youqukantanbushuname		;
	

		/*!
		*
		**/
		BlockPicsrecord() 
		{
			m_kuangquanqukuainame		="" ;
			m_youqikantanchengduname	="" ;
			m_youqikantanchengguoname	="" ;
			m_youqukantanbushuname		="" ;
		}

		/*!
		*
		**/
		const BlockPicsrecord &operator=(const BlockPicsrecord &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_kuangquanqukuainame		=other.	m_kuangquanqukuainame		;
			m_youqikantanchengduname	=other.	m_youqikantanchengduname	;
			m_youqikantanchengguoname	=other.	m_youqikantanchengguoname	;
			m_youqukantanbushuname		=other.	m_youqukantanbushuname		;

			//
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
			return 4;
		}

		bool IsColReadOnly(int order)
		{
		
			return true;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "矿权区块图";
				type=2;
			}
			if(order == 1)
			{
				value = "油气勘探程度图";
				type=2;

			}
			if(order == 2)
			{
				value = "油气勘探成果图";
				type=2;

			}
			if(order == 3)
			{
				value = "油气勘探部署图";
				type=2;

			}
		}

		void GetFldValue(int order, string &value)
		{
		/*	value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value=m_blockthirdstructuralname;
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_area);
			}
			*/
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			/*if(order == 0)
			{
			m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
			m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
			m_blockthirdstructuralname = value;
			}
			if(order == 3)
			{
			m_area = ::atof(value.c_str());
			}*/
	
		}
	};
	





















struct BlockBlockRecord : public PropertyRecord
	{
		long	m_licenseid			;
		string	m_blockname			;
		string	m_explorationlayer	;
		string	m_evaluationunit	;	
		string	m_explorationunit	;		
		string	m_belongoilfield	;	
		string	m_belongfirststru	;
		string	m_belongsecondstru	;
		string	m_belongunit		;
		float	m_basinarea			;
		float	m_area				;
		long	m_startdate			;
		long	m_dateline			;
		long	m_firsttime			;
		string	m_belongprjname		;
		long	m_isevaluate		;
		string	m_remark			;
	

		/*!
		*
		**/
		BlockBlockRecord() 
		{
			m_licenseid			=0;
			m_blockname			="";
			m_explorationlayer	="";
			m_evaluationunit	="";
			m_explorationunit	="";
			m_belongoilfield	="";
			m_belongfirststru	="";
			m_belongsecondstru	="";
			m_belongunit		="";
			m_basinarea			=0 ;
			m_area				=0 ;
			m_startdate			=0 ;
			m_dateline			=0 ;
			m_firsttime			=0 ;
			m_belongprjname		="";
			m_isevaluate		=0;
			m_remark			="";
			
		}

		/*!
		*
		**/
		const BlockBlockRecord &operator=(const BlockBlockRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_licenseid			=other.m_licenseid			;
			m_blockname			=other.m_blockname			;
			m_explorationlayer	=other.m_explorationlayer	;
			m_evaluationunit	=other.m_evaluationunit		;
			m_explorationunit	=other.m_explorationunit	;
			m_belongoilfield	=other.m_belongoilfield		;
			m_belongfirststru	=other.m_belongfirststru	;
			m_belongsecondstru	=other.m_belongsecondstru	;
			m_belongunit		=other.m_belongunit			;
			m_basinarea			=other.m_basinarea			;
			m_area				=other.m_area				;
			m_startdate			=other.m_startdate			;
			m_dateline			=other.m_dateline			;
			m_firsttime			=other.m_firsttime			;
			m_belongprjname		=other.m_belongprjname		;
			m_isevaluate		=other.m_isevaluate			;
			m_remark			=other.m_remark				;
															;
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
			return 19;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "licenseid";
				type=0;

			}
			if(order == 3)
			{
				value = "blockname";
				type=2;

			}
			if(order == 4)
			{
				value = "explorationlayer";
				type=2;

			}
			if(order == 5)
			{
				value = "evaluationunit";
				type=2;

			}
			if(order == 6)
			{
				value = "explorationunit";
				type=2;

			}
			if(order == 7)
			{
				value = "belongoilfield";
				type=2;

			}
			if(order == 8)
			{
				value = "belongfirststru";
				type=2;

			}
			if(order == 9)
			{
				value = "belongsecondstru";
				type=2;

			}
			if(order == 10)
			{
				value = "belongunit";
				type=2;

			}
			if(order == 11)
			{
				value = "basinarea";
				type=1;

			}
	
			if(order == 12)
			{
				value = "area";
				type=1;

			}
			if(order == 13)
			{
				value = "startdate";
				type=0;

			}
			if(order == 14)
			{
				value = "dateline";
				type=0;

			}
			if(order == 15)
			{
				value = "firsttime";
				type=0;

			}
			if(order == 16)
			{
				value = "belongprjname";
				type=2;

			}

			if(order == 17)
			{
				value = "isevaluate";
				type=0;

			}
			if(order == 18)
			{
				value = "remark";
				type=2;

			}
		}

		void GetFldValue(int order, string &value)
		{

			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_licenseid);
			}
			if(order == 3)
			{
				value=m_blockname;
			}
			if(order == 4)
			{
				value=m_explorationlayer;
			}
			if(order == 5)
			{
				value=m_evaluationunit;
			}
			if(order == 6)
			{
				value=m_explorationunit;
			}
			if(order == 7)
			{
				value=m_belongoilfield;
			}
			if(order == 8)
			{
				value=m_belongfirststru;
			}
			if(order == 9)
			{
				value=m_belongsecondstru;
			}
			if(order == 10)
			{
				value=m_belongunit;
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_basinarea);
			}

			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_area);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%d", m_startdate);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%d", m_dateline);
			}
			if(order == 15)
			{
				::sprintf((char *)value.c_str(), "%d", m_firsttime);
			}
			if(order == 16)
			{
				value=m_belongprjname;
			}
			
			if(order == 17)
			{
				::sprintf((char *)value.c_str(), "%d", m_isevaluate);
			}
			if(order == 18)
			{
				value=m_remark;
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_licenseid = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_blockname = value;
			}
			if(order == 4)
			{
				m_explorationlayer = value;
			}
			if(order == 5)
			{
				m_evaluationunit = value;
			}
			if(order == 6)
			{
				m_explorationunit = value;
			}
			if(order == 7)
			{
				m_belongoilfield = value;
			}

			if(order == 8)
			{
				m_belongfirststru=value;
			}
			if(order == 9)
			{
				m_belongsecondstru=value;
			}
			if(order == 10)
			{
				m_belongunit=value;
			}
			if(order == 11)
			{
				m_basinarea = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_area = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_startdate = ::atoi(value.c_str());
			}
			if(order == 14)
			{
				m_dateline = ::atoi(value.c_str());
			}
			if(order == 15)
			{
				m_firsttime = ::atoi(value.c_str());
			}
			if(order == 16)
			{
				m_belongprjname=value;
			}
			if(order == 17)
			{
				m_isevaluate = ::atoi(value.c_str());
			}
			if(order == 18)
			{
				m_remark = value;
			}
			
		}
	};

	struct BlockExplorationDegreeRecord : public PropertyRecord
	{
		float	m_earthquake2d		;
		float	m_earthquake3d		;
		int		m_wellnum			;
		float	m_provedreserves	;
		float	m_controledreserves	;
		float	m_forecastreserves	;
		float	m_potentialreserves	;
		float	m_oilresource		;
		float	m_gasresource		;
		string	m_explorationdgree	;
		string	m_explorationdomain	;					
		string	m_remark			;
	

		/*!
		*
		**/
		BlockExplorationDegreeRecord() 
		{
			m_earthquake2d		=0.0	;
			m_earthquake3d		=0.0	;
			m_wellnum			=0.0	;
			m_provedreserves	=0.0	;
			m_controledreserves	=0.0	;
			m_forecastreserves	=0.0	;
			m_potentialreserves	=0.0	;
			m_oilresource		=0.0	;
			m_gasresource		=0.0	;
			m_explorationdgree	=""		;
			m_explorationdomain	=""		;
			m_remark			=""		;		
		}

		/*!
		*
		**/
		const BlockExplorationDegreeRecord &operator=(const BlockExplorationDegreeRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_earthquake2d		=other.m_earthquake2d		;	
			m_earthquake3d		=other.m_earthquake3d		;
			m_wellnum			=other.m_wellnum			;
			m_provedreserves	=other.m_provedreserves		;
			m_controledreserves	=other.m_controledreserves	;
			m_forecastreserves	=other.m_forecastreserves	;
			m_potentialreserves	=other.m_potentialreserves	;
			m_oilresource		=other.m_oilresource		;
			m_gasresource		=other.m_gasresource		;
			m_explorationdgree	=other.m_explorationdgree	;
			m_explorationdomain	=other.m_explorationdomain	;
			m_remark			=other.m_remark				;
		
			//
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
			return 14;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{

			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "earthquake2d";
				type=1;

			}
			if(order == 3)
			{
				value = "earthquake3d";
				type=1;

			}
			if(order == 4)
			{
				value = "wellnum";
				type=0;

			}
			if(order == 5)
			{
				value = "provedreserves";
				type=1;

			}
			if(order == 6)
			{
				value = "controledreserves";
				type=1;

			}
			if(order == 7)
			{
				value = "forecastreserves";
				type=1;

			}
			if(order == 8)
			{
				value = "potentialreserves";
				type=1;

			}
			if(order == 9)
			{
				value = "oilresource";
				type=1;

			}
			if(order == 10)
			{
				value = "gasresource";
				type=1;

			}
			if(order == 11)
			{
				value = "explorationdgree";
				type=2;

			}
			if(order == 12)
			{
				value = "explorationdomain";
				type=2;

			}
			if(order == 13)
			{
				value = "remark";
				type=2;

			}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%f", m_earthquake2d);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%f", m_earthquake3d);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_wellnum);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_provedreserves);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_controledreserves);
			}
			if(order == 7)
			{
				::sprintf((char *)value.c_str(), "%f", m_forecastreserves);
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_potentialreserves);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_oilresource);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_gasresource);
			}
			if(order == 11)
			{
				value=m_explorationdgree;
			}
			if(order == 12)
			{
				value=m_explorationdomain;
			}
			if(order == 13)
			{
				value=m_remark;
			}
			
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_earthquake2d = ::atof(value.c_str());
			}
			if(order == 3)
			{
				m_earthquake3d = ::atof(value.c_str());
			}
			if(order == 4)
			{
				m_wellnum = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_provedreserves = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_controledreserves = ::atof(value.c_str());
			}
			if(order == 7)
			{
				m_forecastreserves = ::atof(value.c_str());
			}
			if(order == 8)
			{
				m_potentialreserves = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_oilresource = ::atof(value.c_str());
			}
			if(order == 10)
			{
				m_gasresource = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_explorationdgree = value;
			}
			if(order == 12)
			{
				m_explorationdomain = value;
			}
			if(order == 13)
			{
				m_remark = value;
			}
			
		}
	};

///////////////////////////

struct PerformanceWellBasicRecord : public PropertyRecord
{
			string	m_WeLLName		;
			int		m_WellStatus	;
			int		m_WellType		;
			double	m_CoordinateX	;
			double	m_CoordinateY	;

		/*!
		*
		**/
		PerformanceWellBasicRecord() 
		{
			m_WeLLName		=""		;
			m_WellStatus	=0		;
			m_WellType		=0		;
			m_CoordinateX	=0.0	;
			m_CoordinateY	=0.0	;
				
		}

		/*!
		*
		**/
		const PerformanceWellBasicRecord &operator=(const PerformanceWellBasicRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_WeLLName		=other.m_WeLLName	;	
			m_WellStatus	=other.m_WellStatus	;
			m_WellType		=other.m_WellType	;
			m_CoordinateX	=other.m_CoordinateX;
			m_CoordinateY	=other.m_CoordinateY;
			;
		
			//
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
			return 7;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{

			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "WeLLName";
				type=2;

			}
			if(order == 3)
			{
				value = "WellStatus";
				type=0;

			}
			if(order == 4)
			{
				value = "WellType";
				type=0;

			}
			if(order == 5)
			{
				value = "CoordinateX";
				type=1;

			}
			if(order == 6)
			{
				value = "CoordinateY";
				type=1;

			}
			
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				value = m_WeLLName;
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_WellStatus);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_WellType);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%f", m_CoordinateX);
			}
			if(order == 6)
			{
				::sprintf((char *)value.c_str(), "%f", m_CoordinateY);
			}
			
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_WeLLName = value;
			}
			if(order == 3)
			{
				m_WellStatus = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_WellType = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_CoordinateX = ::atof(value.c_str());
			}
			if(order == 6)
			{
				m_CoordinateY = ::atof(value.c_str());
			}
			
		}
	};
//////////////////////

struct PerformanceDeploymentRecord : public PropertyRecord
{
		int		m_CasingdeploymentID			;
		int		m_TubingdeploymentID			;
		int		m_welltrajectorydeploymentID	;
		int		m_deploymentdate				;
		string	m_deploymentname				;
		string	m_wellpipemode					;
		float	m_PerforationTopdepth			;
		float	m_Perforationbottomdepth		;
		float	m_completionmiddledepth 		;
		float	m_Wellheadtemperature			;
		float	m_Reservoirtemperature			;
		int		m_Flowpressurecalculationmodel	;
		float	m_additionalpressuredrop		;

		/*!
		*
		**/
		PerformanceDeploymentRecord() 
		{	
			m_CasingdeploymentID			=0;
			m_TubingdeploymentID			=0;
			m_welltrajectorydeploymentID	=0;
			m_deploymentdate				=0;
			m_deploymentname				="";
			m_wellpipemode					="";
			m_PerforationTopdepth			=0;
			m_Perforationbottomdepth		=0;
			m_completionmiddledepth 		=0;
			m_Wellheadtemperature			=0;
			m_Reservoirtemperature			=0;
			m_Flowpressurecalculationmodel	=0;
			m_additionalpressuredrop		=0;


		}

		/*!
		*
		**/
		const PerformanceDeploymentRecord &operator=(const PerformanceDeploymentRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_CasingdeploymentID			=other.m_CasingdeploymentID				;
			m_TubingdeploymentID			=other.m_TubingdeploymentID			   ;
			m_welltrajectorydeploymentID	=other.m_welltrajectorydeploymentID	   ;
			m_deploymentdate				=other.m_deploymentdate				   ;
			m_deploymentname				=other.m_deploymentname				   ;
			m_wellpipemode					=other.m_wellpipemode					;
			m_PerforationTopdepth			=other.m_PerforationTopdepth			;
			m_Perforationbottomdepth		=other.m_Perforationbottomdepth		   ;
			m_completionmiddledepth 		=other.m_completionmiddledepth 		   ;
			m_Wellheadtemperature			=other.m_Wellheadtemperature			;
			m_Reservoirtemperature			=other.m_Reservoirtemperature			;
			m_Flowpressurecalculationmodel	=other.m_Flowpressurecalculationmodel	;
			m_additionalpressuredrop		=other.m_additionalpressuredrop		   ;


			//
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
			return 15;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2 || order==3 || order==4)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{

			if(order == 0)
			{
				value = "propertyid";
				type=0;
			}
			if(order == 1)
			{
				value = "elementid";
				type=0;

			}
			if(order == 2)
			{
				value = "CasingdeploymentID";
				type=0;

			}
			if(order == 3)
			{
				value = "TubingdeploymentID";
				type=0;

			}
			if(order == 4)
			{
				value = "welltrajectorydeploymentID";
				type=0;

			}
			if(order == 5)
			{
				value = "deploymentdate";
				type=0;

			}
			if(order == 6)
			{
				value = "deploymentname";
				type=2;

			}
			if(order == 7)
			{
				value = "wellpipemode";
				type=2;

			}
			if(order == 8)
			{
				value = "PerforationTopdepth";
				type=1;

			}
			if(order == 9)
			{
				value = "Perforationbottomdepth";
				type=1;

			}
			if(order == 10)
			{
				value = "completionmiddledepth";
				type=1;

			}
			if(order == 11)
			{
				value = "Wellheadtemperature";
				type=1;

			}
			if(order == 12)
			{
				value = "Reservoirtemperature";
				type=1;

			}
			if(order == 13)
			{
				value = "Flowpressurecalculationmodel";
				type=0;

			}
			if(order == 14)
			{
				value = "additionalpressuredrop";
				type=1;

			}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) 
			{
				::sprintf((char *)value.c_str(), "%d", m_idx);
			}
			if(order == 1)
			{
				::sprintf((char *)value.c_str(), "%d", m_elementIdx);
			}
			if(order == 2)
			{
				::sprintf((char *)value.c_str(), "%d", m_CasingdeploymentID);
			}
			if(order == 3)
			{
				::sprintf((char *)value.c_str(), "%d", m_TubingdeploymentID);
			}
			if(order == 4)
			{
				::sprintf((char *)value.c_str(), "%d", m_welltrajectorydeploymentID);
			}
			if(order == 5)
			{
				::sprintf((char *)value.c_str(), "%d", m_deploymentdate);
			}
			if(order == 6)
			{
				value= m_deploymentname;
			}
			if(order == 7) 
			{
				value=m_wellpipemode;
			}
			if(order == 8)
			{
				::sprintf((char *)value.c_str(), "%f", m_PerforationTopdepth);
			}
			if(order == 9)
			{
				::sprintf((char *)value.c_str(), "%f", m_Perforationbottomdepth);
			}
			if(order == 10)
			{
				::sprintf((char *)value.c_str(), "%f", m_completionmiddledepth);
			}
			if(order == 11)
			{
				::sprintf((char *)value.c_str(), "%f", m_Wellheadtemperature);
			}
			if(order == 12)
			{
				::sprintf((char *)value.c_str(), "%f", m_Reservoirtemperature);
			}
			if(order == 13)
			{
				::sprintf((char *)value.c_str(), "%d", m_Flowpressurecalculationmodel);
			}
			if(order == 14)
			{
				::sprintf((char *)value.c_str(), "%f", m_additionalpressuredrop);
			}
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0)
			{
				m_idx = ::atoi(value.c_str());
			}
			if(order == 1)
			{
				m_elementIdx = ::atoi(value.c_str());
			}
			if(order == 2)
			{
				m_CasingdeploymentID = ::atoi(value.c_str());
			}
			if(order == 3)
			{
				m_TubingdeploymentID = ::atoi(value.c_str());
			}
			if(order == 4)
			{
				m_welltrajectorydeploymentID = ::atoi(value.c_str());
			}
			if(order == 5)
			{
				m_deploymentdate = ::atoi(value.c_str());
			}
			if(order == 6)
			{
				m_deploymentname =value;
			}
			if(order == 7)
			{
				m_wellpipemode = value;
			}
			if(order == 8)
			{
				m_PerforationTopdepth = ::atof(value.c_str());
			}
			if(order == 9)
			{
				m_Perforationbottomdepth = ::atof(value.c_str());;
			}
			if(order == 10)
			{
				m_completionmiddledepth = ::atof(value.c_str());
			}
			if(order == 11)
			{
				m_Wellheadtemperature = ::atof(value.c_str());
			}
			if(order == 12)
			{
				m_Reservoirtemperature = ::atof(value.c_str());
			}
			if(order == 13)
			{
				m_Flowpressurecalculationmodel = ::atoi(value.c_str());
			}
			if(order == 14)
			{
				m_additionalpressuredrop = ::atof(value.c_str());
			}
		
		}
	};

//////////////////////////////////////

struct PerformanceDeploymentCasingRecord : public PropertyRecord
{
	int		m_CasingdeploymentID		;
	string	m_deploymentname			;
	int		m_Casingcompletionmethod	;
	float	m_CasingBottomDepth			;
	float	m_Casingdiameter			;
	float	m_Casingwallroughness		;

		/*!
		*
		**/
		PerformanceDeploymentCasingRecord() 
		{
			m_CasingdeploymentID		=0;
			m_deploymentname			="";
			m_Casingcompletionmethod	=0;
			m_CasingBottomDepth			=0;
			m_Casingdiameter			=0;
			m_Casingwallroughness		=0;
		}

		/*!
		*
		**/
		const PerformanceDeploymentCasingRecord &operator=(const PerformanceDeploymentCasingRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_CasingdeploymentID		=other.m_CasingdeploymentID		;
			m_deploymentname			=other.m_deploymentname			;
			m_Casingcompletionmethod	=other.m_Casingcompletionmethod	;
			m_CasingBottomDepth			=other.m_CasingBottomDepth		;	
			m_Casingdiameter			=other.m_Casingdiameter			;
			m_Casingwallroughness		=other.m_Casingwallroughness	;	
		
			//
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
			return 8;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";					type=0;}
			if(order == 1){value = "elementid";						type=0;}
			if(order == 2){value = "casingdeploymentid";			type=0;}
			if(order == 3){value = "deploymentname";				type=2;}
			if(order == 4){value = "casingcompletionmethod";		type=0;}
			if(order == 5){value = "casingbottomdepth";				type=1;}
			if(order == 6){value = "casingdiameter";				type=1;}
			if(order == 7){value = "casingwallroughness";			type=1;}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_CasingdeploymentID);}
			if(order == 3) {value=m_deploymentname;}
			if(order == 4) {::sprintf((char *)value.c_str(), "%d", m_Casingcompletionmethod);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_CasingBottomDepth);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_Casingdiameter);}
			if(order == 7) {::sprintf((char *)value.c_str(), "%f", m_Casingwallroughness);}
				
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_CasingdeploymentID	 = ::atoi(value.c_str());}
			if(order == 3){m_deploymentname=value;}
			if(order == 4){m_Casingcompletionmethod = ::atoi(value.c_str());}
			if(order == 5){m_CasingBottomDepth		 = ::atof(value.c_str());}
			if(order == 6){m_Casingdiameter		 = ::atof(value.c_str());}
			if(order == 7){m_Casingwallroughness	 = ::atof(value.c_str());}
		}
	};

//////////////////////////////////

	
struct PerformanceDeploymentTubingRecord : public PropertyRecord
{

	int		m_TubingdeploymentID	;		
	string	m_deploymentname		;		
	float	m_TubingBottomDepth		;	
	float	m_Tubingdiameter		;		
	float	m_Tubingwallroughness	;		
		/*!
		*
		**/
		PerformanceDeploymentTubingRecord() 
		{
			m_TubingdeploymentID	=0;
			m_deploymentname		="";
			m_TubingBottomDepth		=0;
			m_Tubingdiameter		=0;
			m_Tubingwallroughness	=0;
		}

		/*!
		*
		**/
		const PerformanceDeploymentTubingRecord &operator=(const PerformanceDeploymentTubingRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_TubingdeploymentID	=other.m_TubingdeploymentID		;
			m_deploymentname		=other.m_deploymentname			;
			m_TubingBottomDepth		=other.m_TubingBottomDepth		;
			m_Tubingdiameter		=other.m_Tubingdiameter			;
			m_Tubingwallroughness	=other.m_Tubingwallroughness	;
		
			//
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
			return 7;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";					type=0;}
			if(order == 1){value = "elementid";						type=0;}
			if(order == 2){value = "TubingdeploymentID";			type=0;}
			if(order == 3){value = "deploymentname";				type=2;}
			if(order == 4){value = "TubingBottomDepth";				type=1;}
			if(order == 5){value = "Tubingdiameter";				type=1;}
			if(order == 6){value = "Tubingwallroughness";			type=1;}
			

		}

		void GetFldValue(int order, string &value)
		{
			value =  "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_TubingdeploymentID	);}
			if(order == 3) {value=m_deploymentname;}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_TubingBottomDepth		);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_Tubingdiameter		);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_Tubingwallroughness	);}
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_TubingdeploymentID	= ::atoi(value.c_str());}
			if(order == 3){m_deploymentname	=	value;}
			if(order == 4){m_TubingBottomDepth	= ::atof(value.c_str());}
			if(order == 5){m_Tubingdiameter		= ::atof(value.c_str());}
			if(order == 6){m_Tubingwallroughness= ::atof(value.c_str());}
		}
	};

///////////////////////////////

struct PerformanceDeploymenttrajectoryRecord : public PropertyRecord
{
		int		m_welltrajectorydeploymentID	;
		string	m_deploymentname				;
		float	m_MeasuredDepth					;
		float	m_TVD							;
		float	m_Azimuthangle					;
		/*!
		*
		**/
		PerformanceDeploymenttrajectoryRecord() 
		{
			m_welltrajectorydeploymentID	=0;	
			m_deploymentname				="";
			m_MeasuredDepth					=0;
			m_TVD							=0;
			m_Azimuthangle					=0;
			
			
			
			
		}

		/*!
		*
		**/
		const PerformanceDeploymenttrajectoryRecord &operator=(const PerformanceDeploymenttrajectoryRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_welltrajectorydeploymentID	=other.m_welltrajectorydeploymentID	;
			m_deploymentname				=other.m_deploymentname				;
			m_MeasuredDepth					=other.m_MeasuredDepth				;	
			m_TVD							=other.m_TVD						;	
			m_Azimuthangle					=other.m_Azimuthangle				;	
																				
			
			
			
		
			//
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
			return 7;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";					type=0;}
			if(order == 1){value = "elementid";						type=0;}
			if(order == 2){value = "welltrajectorydeploymentID";			type=0;}
			if(order == 3){value = "deploymentname";						type=2;}
			if(order == 4){value = "MeasuredDepth";							type=1;}
			if(order == 5){value = "TVD";									type=1;}
			if(order == 6){value = "Azimuthangle";							type=1;}
			

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_welltrajectorydeploymentID	);}
			if(order == 3) {value=m_deploymentname;}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_MeasuredDepth		);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_TVD		);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_Azimuthangle	);}
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_welltrajectorydeploymentID	= ::atoi(value.c_str());}
			if(order == 3){m_deploymentname	=	value;}
			if(order == 4){m_MeasuredDepth	= ::atof(value.c_str());}
			if(order == 5){m_TVD		= ::atof(value.c_str());}
			if(order == 6){m_Azimuthangle= ::atof(value.c_str());}
		}
	};

//////////////////
struct PerformanceGeologicalParaRecord : public PropertyRecord
{
	float m_initialstratapressure		;
	float m_stratatemperature			;
	float m_reservoirthickness			;
	float m_porosity					;
	float m_initialgassaturation		;
	float m_Porecompressioncoefficient	;
	float m_gasRelativedensity			;
	float m_CO2Molepercentage			;
	float m_H2SMolepercentage			;
	float m_N2Molepercentage			;
	float m_LangeMuirvolume				;
	float m_LangeMuirpressure			;
	float m_shaledensity				;
	float m_stratumwaterdensity			;
	float m_initialcompression			;
	float m_initialvolume				;
	float m_stratumwaterviscosity		;
	int	  m_gasdeviationfactor			;
	int   m_gasviscosity				;
	float m_rw							;			
	float m_soi							;
	float m_swi							;
	float m_cti							;
	float m_mg							;
		/*!
		*
		**/
		PerformanceGeologicalParaRecord() 
		{
			m_initialstratapressure		=0;
			m_stratatemperature			=0;
			m_reservoirthickness		=0;
			m_porosity					=0;
			m_initialgassaturation		=0;
			m_Porecompressioncoefficient=0;
			m_gasRelativedensity		=0;
			m_CO2Molepercentage			=0;
			m_H2SMolepercentage			=0;
			m_N2Molepercentage			=0;
			m_LangeMuirvolume			=0;
			m_LangeMuirpressure			=0;
			m_shaledensity				=0;
			m_stratumwaterdensity		=0;
			m_initialcompression		=0;
			m_initialvolume				=0;
			m_stratumwaterviscosity		=0;
			m_gasdeviationfactor		=0;
			m_gasviscosity				=0;
			m_rw						=0;	
			m_soi						=0;	
			m_swi						=0;	
			m_cti						=0;	
			m_mg						=0;
			
		}

		void SetDefaultValue()
		{
			m_initialstratapressure		=38.2;
			m_stratatemperature			=355.15;
			m_reservoirthickness		=45;
			m_porosity					=0.0392;
			m_initialgassaturation		=0.7285;
			m_Porecompressioncoefficient=0.00182;
			m_gasRelativedensity		=0.566;
			m_CO2Molepercentage			=0;
			m_H2SMolepercentage			=0;
			m_N2Molepercentage			=0;
			m_LangeMuirvolume			=3;
			m_LangeMuirpressure			=6;
			m_shaledensity				=2.6;
			m_stratumwaterdensity		=0;
			m_initialcompression		=0.0004;
			m_initialvolume				=1;
			m_stratumwaterviscosity		=1;
			m_gasdeviationfactor		=0;
			m_gasviscosity				=0;
			m_rw						=0.06;	
			m_soi						=0;	
			m_swi						=0.2715;	
			m_cti						=0.013799;	
			m_mg						=0;
		}

		int CheckDataValid()
		{
			if(m_initialstratapressure			<=0){return  2;}
			//if(m_stratatemperature				<=0){return  3;}
			if(m_reservoirthickness				<=0){return  4;}
			if(m_porosity						<=0 || m_porosity>1){return  5;}
			if(m_initialgassaturation			< 0){return  6;}
			if(m_Porecompressioncoefficient		<=0){return  7;}
			if(m_gasRelativedensity				<=0){return  8;}
			if(m_CO2Molepercentage				< 0){return  9;}
			if(m_H2SMolepercentage				< 0){return 10;}
			if(m_N2Molepercentage				< 0){return 11;}
			if(m_LangeMuirvolume				<=0){return 12;}
			if(m_LangeMuirpressure				<=0){return 13;}
			if(m_shaledensity					<=0){return 14;}
			if(m_stratumwaterdensity			< 0){return 15;}
			if(m_initialcompression				<=0){return 16;}
			if(m_initialvolume					< 0){return 17;}
			if(m_stratumwaterviscosity			< 0){return 18;}
			if(m_gasdeviationfactor				< 0){return 19;}
			if(m_gasviscosity					< 0){return 20;}
			if(m_rw								<=0){return 21;}
			if(m_soi							< 0){return 22;}
			if(m_swi							< 0){return 23;}
			//if(m_cti							<=0){return 24;}
			//if(m_mg							<=0){return 25;}
			
			return -1;
		}

		bool CheckSgiSwiSoi()
		{
			if((abs(m_initialgassaturation+m_soi+m_swi - 1))>0.0001)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		bool CheckGasComposition()
		{
			if((m_CO2Molepercentage+m_H2SMolepercentage+m_N2Molepercentage-1)>=0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		/*!
		*
		**/
		const PerformanceGeologicalParaRecord &operator=(const PerformanceGeologicalParaRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_initialstratapressure			=other.m_initialstratapressure			;
			m_stratatemperature				=other.m_stratatemperature				;
			m_reservoirthickness			=other.m_reservoirthickness				;
			m_porosity						=other.m_porosity						;
			m_initialgassaturation			=other.m_initialgassaturation			;
			m_Porecompressioncoefficient	=other.m_Porecompressioncoefficient		;
			m_gasRelativedensity			=other.m_gasRelativedensity				;
			m_CO2Molepercentage				=other.m_CO2Molepercentage				;
			m_H2SMolepercentage				=other.m_H2SMolepercentage				;
			m_N2Molepercentage				=other.m_N2Molepercentage				;
			m_LangeMuirvolume				=other.m_LangeMuirvolume				;
			m_LangeMuirpressure				=other.m_LangeMuirpressure				;
			m_shaledensity					=other.m_shaledensity					;
			m_stratumwaterdensity			=other.m_stratumwaterdensity			;
			m_initialcompression			=other.m_initialcompression				;
			m_initialvolume					=other.m_initialvolume					;
			m_stratumwaterviscosity			=other.m_stratumwaterviscosity			;
			m_gasdeviationfactor			=other.m_gasdeviationfactor				;
			m_gasviscosity					=other.m_gasviscosity					;
			m_rw							=other.m_rw								;					
			m_soi							=other.m_soi							;
			m_swi							=other.m_swi							;
			m_cti							=other.m_cti							;																	
			m_mg							=other.m_mg								;
			
			
		
			//
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
			return 26;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";							type=0;}
			if(order == 1){value = "elementid";								type=0;}
			if(order == 2){value = "initialstratapressure";				type=1;}
			if(order == 3){value = "stratatemperature";					type=1;}
			if(order == 4){value = "reservoirthickness";				type=1;}
			if(order == 5){value = "porosity";							type=1;}
			if(order == 6){value = "initialgassaturation";				type=1;}
			if(order == 7){value = "Porecompressioncoefficient";		type=1;}
			if(order == 8){value = "gasRelativedensity";				type=1;}
			if(order == 9){value = "CO2Molepercentage";					type=1;}
			if(order ==10){value = "H2SMolepercentage";					type=1;}
			if(order ==11){value = "N2Molepercentage";					type=1;}
			if(order ==12){value = "LangeMuirvolume";					type=1;}
			if(order ==13){value = "LangeMuirpressure";					type=1;}
			if(order ==14){value = "shaledensity";						type=1;}
			if(order ==15){value = "stratumwaterdensity";				type=1;}
			if(order ==16){value = "initialcompression";				type=1;}
			if(order ==17){value = "initialvolume";						type=1;}
			if(order ==18){value = "stratumwaterviscosity";				type=1;}
			if(order ==19){value = "gasdeviationfactor";				type=0;}
			if(order ==20){value = "gasviscosity";						type=0;}
			if(order ==21){value = "rw";								type=1;}
			if(order ==22){value = "soi";								type=1;}
			if(order ==23){value = "swi";								type=1;}
			if(order ==24){value = "cti";								type=1;}
			if(order ==25){value = "mg";								type=1;}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%f", m_initialstratapressure				);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%f", m_stratatemperature					);}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_reservoirthickness				);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_porosity							);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_initialgassaturation				);}
			if(order == 7) {::sprintf((char *)value.c_str(), "%f", m_Porecompressioncoefficient		);}
			if(order == 8) {::sprintf((char *)value.c_str(), "%f", m_gasRelativedensity				);}
			if(order == 9) {::sprintf((char *)value.c_str(), "%f", m_CO2Molepercentage					);}
			if(order ==10) {::sprintf((char *)value.c_str(), "%f", m_H2SMolepercentage					);}
			if(order ==11) {::sprintf((char *)value.c_str(), "%f", m_N2Molepercentage					);}
			if(order ==12) {::sprintf((char *)value.c_str(), "%f", m_LangeMuirvolume					);}
			if(order ==13) {::sprintf((char *)value.c_str(), "%f", m_LangeMuirpressure					);}
			if(order ==14) {::sprintf((char *)value.c_str(), "%f", m_shaledensity						);}
			if(order ==15) {::sprintf((char *)value.c_str(), "%f", m_stratumwaterdensity				);}
			if(order ==16) {::sprintf((char *)value.c_str(), "%f", m_initialcompression				);}
			if(order ==17) {::sprintf((char *)value.c_str(), "%f", m_initialvolume						);}
			if(order ==18) {::sprintf((char *)value.c_str(), "%f", m_stratumwaterviscosity				);}
			if(order ==19) {::sprintf((char *)value.c_str(), "%d", m_gasdeviationfactor				);}
			if(order ==20) {::sprintf((char *)value.c_str(), "%d", m_gasviscosity						);}
			if(order ==21) {::sprintf((char *)value.c_str(), "%f", m_rw									);}
			if(order ==22) {::sprintf((char *)value.c_str(), "%f", m_soi								);}
			if(order ==23) {::sprintf((char *)value.c_str(), "%f", m_swi								);}
			if(order ==24) {::sprintf((char *)value.c_str(), "%f", m_cti								);}
			if(order ==25) {::sprintf((char *)value.c_str(), "%f", m_mg									);}
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_initialstratapressure				= ::atof(value.c_str());}
			if(order == 3){m_stratatemperature					= ::atof(value.c_str());}
			if(order == 4){m_reservoirthickness					= ::atof(value.c_str());}
			if(order == 5){m_porosity							= ::atof(value.c_str());}
			if(order == 6){m_initialgassaturation				= ::atof(value.c_str());}
			if(order == 7){m_Porecompressioncoefficient			= ::atof(value.c_str());}
			if(order == 8){m_gasRelativedensity					= ::atof(value.c_str());}
			if(order == 9){m_CO2Molepercentage					= ::atof(value.c_str());}
			if(order ==10){m_H2SMolepercentage					= ::atof(value.c_str());}
			if(order ==11){m_N2Molepercentage					= ::atof(value.c_str());}
			if(order ==12){m_LangeMuirvolume					= ::atof(value.c_str());}
			if(order ==13){m_LangeMuirpressure					= ::atof(value.c_str());}
			if(order ==14){m_shaledensity						= ::atof(value.c_str());}
			if(order ==15){m_stratumwaterdensity				= ::atof(value.c_str());}
			if(order ==16){m_initialcompression					= ::atof(value.c_str());}
			if(order ==17){m_initialvolume						= ::atof(value.c_str());}
			if(order ==18){m_stratumwaterviscosity				= ::atof(value.c_str());}
			if(order ==19){m_gasdeviationfactor					= ::atoi(value.c_str());}
			if(order ==20){m_gasviscosity						= ::atoi(value.c_str());}
			if(order ==21){m_rw									= ::atof(value.c_str());}
			if(order ==22){m_soi								= ::atof(value.c_str());}
			if(order ==23){m_swi								= ::atof(value.c_str());}
			if(order ==24){m_cti								= ::atof(value.c_str());}
			if(order ==25){m_mg									= ::atof(value.c_str());}
		}
	};








/////////////////	
struct PerformancePressureRecord : public PropertyRecord
{
		int		m_measureddate				;
		float	m_measureddepth				;
		float	m_measuredTVD				;
		float	m_measuredgasproduction		;
		float	m_measuredpressure			;
		int		m_statussign				;
		string	m_remarks					;
		/*!
		*
		**/
		PerformancePressureRecord() 
		{
			m_measureddate				=0;
			m_measureddepth				=0;
			m_measuredTVD				=0;
			m_measuredgasproduction		=0;
			m_measuredpressure			=0;
			m_statussign				=0;
			m_remarks					="";
			
			
		}

		/*!
		*
		**/
		const PerformancePressureRecord &operator=(const PerformancePressureRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_measureddate				=other.m_measureddate				;
			m_measureddepth				=other.m_measureddepth				;																
			m_measuredTVD				=other.m_measuredTVD				;
			m_measuredgasproduction		=other.m_measuredgasproduction		;
			m_measuredpressure			=other.m_measuredpressure			;
			m_statussign				=other.m_statussign					;
			m_remarks					=other.m_remarks					;
			
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
			return 9;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==3 ||order==4 ||order==5 ||order==8)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";							type=0;}
			if(order == 1){value = "elementid";								type=0;}
			if(order == 2){value = "measureddate";						type=0;}
			if(order == 3){value = "measureddepth";						type=1;}
			if(order == 4){value = "measuredTVD";						type=1;}
			if(order == 5){value = "measuredgasproduction";				type=1;}
			if(order == 6){value = "measuredpressure";					type=1;}
			if(order == 7){value = "statussign";						type=0;}
			if(order == 8){value = "remarks";							type=2;}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_measureddate					);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%f", m_measureddepth					);}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_measuredTVD					);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_measuredgasproduction			);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_measuredpressure				);}
			if(order == 7) {::sprintf((char *)value.c_str(), "%d", m_statussign					);}
			if(order == 8) {value=m_remarks	;}
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_measureddate				= ::atoi(value.c_str());}
			if(order == 3){m_measureddepth				= ::atof(value.c_str());}
			if(order == 4){m_measuredTVD				= ::atof(value.c_str());}
			if(order == 5){m_measuredgasproduction		= ::atof(value.c_str());}
			if(order == 6){m_measuredpressure			= ::atof(value.c_str());}
			if(order == 7){m_statussign					= ::atoi(value.c_str());}
			if(order == 8){m_remarks=value;}
		}
	};


/////////////////


struct PerformancePressureGradientRecord : public PropertyRecord
{
		int		m_measureddate			;	
		float	m_measureddepth			;
		float	m_measuredpressure		;
		float	m_Measuredtemperature	;
		/*!
		*
		**/
		PerformancePressureGradientRecord() 
		{
			m_measureddate			=0;
			m_measureddepth			=0;
			m_measuredpressure		=0;
			m_Measuredtemperature	=0;
			
		}

		/*!
		*
		**/
		const PerformancePressureGradientRecord &operator=(const PerformancePressureGradientRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			m_measureddate			=other.m_measureddate				;
			m_measureddepth			=other.m_measureddepth				;	
			m_measuredpressure		=other.m_measuredpressure			;
			m_Measuredtemperature	=other.m_Measuredtemperature		;	

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
			return 6;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";						type=0;}
			if(order == 1){value = "elementid";							type=0;}
			if(order == 2){value = "measureddate";						type=0;}
			if(order == 3){value = "measureddepth";						type=1;}
			if(order == 4){value = "measuredpressure";					type=1;}
			if(order == 5){value = "Measuredtemperature";				type=1;}
		

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_measureddate					);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%f", m_measureddepth					);}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_measuredpressure				);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_Measuredtemperature			);}
		
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_measureddate				= ::atoi(value.c_str());}
			if(order == 3){m_measureddepth				= ::atof(value.c_str());}
			if(order == 4){m_measuredpressure			= ::atof(value.c_str());}
			if(order == 5){m_Measuredtemperature		= ::atof(value.c_str());}
			
		}
	};
///////////////////////////////////

struct PerformanceProductionRecord : public PropertyRecord
{
		int		m_productiondate				;
		float	m_productionhours				;
		float	m_Casingpressure				;
		float	m_tubingpressure				;
		float	m_gasproductionrate				;
		float	m_waterproductionrate			;
		float	m_oilproductionrate				;
		float	m_calculatedsandfacepressure	;
		string		m_calculatingpressure		;
		/*!
		*
		**/
		PerformanceProductionRecord() 
		{
			m_productiondate				=0;
			m_productionhours				=0;
			m_Casingpressure				=0;
			m_tubingpressure				=0;
			m_gasproductionrate				=0;
			m_waterproductionrate			=0;
			m_oilproductionrate				=0;
			m_calculatedsandfacepressure	=0;
			m_calculatingpressure			="";
			
			
		}

		/*!
		*
		**/
		const PerformanceProductionRecord &operator=(const PerformanceProductionRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_productiondate				=other.m_productiondate					;	
			m_productionhours				=other.m_productionhours				;
			m_Casingpressure				=other.m_Casingpressure					;
			m_tubingpressure				=other.m_tubingpressure					;
			m_gasproductionrate				=other.m_gasproductionrate				;
			m_waterproductionrate			=other.m_waterproductionrate			;
			m_oilproductionrate				=other.m_oilproductionrate				;
			m_calculatedsandfacepressure	=other.m_calculatedsandfacepressure		;
			m_calculatingpressure			=other.m_calculatingpressure			;

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
			return 11;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";						type=0;}
			if(order == 1){value = "elementid";							type=0;}
			if(order == 2){value = "productiondate";						type=0;}
			if(order == 3){value = "productionhours";						type=1;}
			if(order == 4){value = "Casingpressure";						type=1;}
			if(order == 5){value = "tubingpressure";						type=1;}
			if(order == 6){value = "gasproductionrate";						type=1;}
			if(order == 7){value = "waterproductionrate";					type=1;}
			if(order == 8){value = "oilproductionrate";						type=1;}
			if(order == 9){value = "calculatedsandfacepressure";			type=1;}
			if(order ==10){value = "calculatingpressure";					type=2;}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_productiondate					);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%f", m_productionhours				);}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_Casingpressure					);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_tubingpressure					);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_gasproductionrate				);}
			if(order == 7) {::sprintf((char *)value.c_str(), "%f", m_waterproductionrate			);}
			if(order == 8) {::sprintf((char *)value.c_str(), "%f", m_oilproductionrate				);}
			if(order == 9) {::sprintf((char *)value.c_str(), "%f", m_calculatedsandfacepressure		);}
			if(order ==10) {value = m_calculatingpressure;}
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_productiondate					= ::atoi(value.c_str());}
			if(order == 3){m_productionhours				= ::atof(value.c_str());}
			if(order == 4){m_Casingpressure					= ::atof(value.c_str());}
			if(order == 5){m_tubingpressure					= ::atof(value.c_str());}
			if(order == 6){m_gasproductionrate				= ::atof(value.c_str());}
			if(order == 7){m_waterproductionrate			= ::atof(value.c_str());}
			if(order == 8){m_oilproductionrate				= ::atof(value.c_str());}
			if(order == 9){m_calculatedsandfacepressure		= ::atof(value.c_str());}
			if(order ==10){m_calculatingpressure			= value;}
			
		}
	};


/////////////////////////////
//PRT_Performance_Practice

struct PerformancePracticeRecord : public PropertyRecord
{
		int    m_practiceid		;	
		int    m_activityid		;
		string m_name			;
		string m_remark			;
		/*!
		*
		**/
		PerformancePracticeRecord() 
		{
			m_practiceid		=0;
			m_activityid		=0;
			m_name				="";
			m_remark			="";
		
			
			
		}

		/*!
		*
		**/
		const PerformancePracticeRecord &operator=(const PerformancePracticeRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_practiceid		=other.m_practiceid						;	
			m_activityid		=other.m_activityid						;
			m_name				=other.m_name							;
			m_remark			=other.m_remark							;
		
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
			return 6;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";						type=0;}
			if(order == 1){value = "elementid";							type=0;}
			if(order == 2){value = "practiceid";							type=0;}
			if(order == 3){value = "activityid";							type=0;}
			if(order == 4){value = "name";									type=2;}
			if(order == 5){value = "remark";								type=2;}
			
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_practiceid		);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%d", m_activityid		);}
			if(order == 4) {value=m_name				;}
			if(order == 5) {value=m_remark				;}
		
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_practiceid	= ::atoi(value.c_str());}
			if(order == 3){m_activityid	= ::atoi(value.c_str());}
			if(order == 4){m_name		= value;}
			if(order == 5){m_remark		= value;}
		
			
		}
	};



/////////////////////////////
//	PRT_Performance_DreResult

struct PerformanceDreResultRecord : public PropertyRecord
{
		int		m_practiceid						;
		int		m_materialbalancemethod				;
		int		m_adsorbedgasdesorption				;
		int		m_stresssensitivity					;
		float	m_slopem							;
		float	m_interceptb						;
		float	m_theoreticalproductionindex		;
		float	m_calculatedtotalreserves			;
		float	m_calculatedfreegasreserves			;
		float	m_calculatedabsorbedgasreserves		;
		float	m_abandonstratapressure				;
		float	m_predictedeur						;
		float	m_predictedrecoverypercent			;
		string	m_remark							;
		/*!
		*
		**/
		PerformanceDreResultRecord() 
		{
			m_practiceid						=0;
			m_materialbalancemethod				=0;
			m_adsorbedgasdesorption				=0;
			m_stresssensitivity					=0;
			m_slopem							=0;
			m_interceptb						=0;
			m_theoreticalproductionindex		=0;
			m_calculatedtotalreserves			=0;
			m_calculatedfreegasreserves			=0;
			m_calculatedabsorbedgasreserves		=0;
			m_abandonstratapressure				=0;
			m_predictedeur						=0;
			m_predictedrecoverypercent			=0;
			m_remark							="";
			
	
		}

		/*!
		*
		**/
		const PerformanceDreResultRecord &operator=(const PerformanceDreResultRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_practiceid						=other.m_practiceid						;
			m_materialbalancemethod				=other.m_materialbalancemethod			;	
			m_adsorbedgasdesorption				=other.m_adsorbedgasdesorption			;	
			m_stresssensitivity					=other.m_stresssensitivity				;	
			m_slopem							=other.m_slopem							;
			m_interceptb						=other.m_interceptb						;
			m_theoreticalproductionindex		=other.m_theoreticalproductionindex		;
			m_calculatedtotalreserves			=other.m_calculatedtotalreserves		;	
			m_calculatedfreegasreserves			=other.m_calculatedfreegasreserves		;	
			m_calculatedabsorbedgasreserves		=other.m_calculatedabsorbedgasreserves	;	
			m_abandonstratapressure				=other.m_abandonstratapressure			;	
			m_predictedeur						=other.m_predictedeur					;	
			m_predictedrecoverypercent			=other.m_predictedrecoverypercent		;	
			m_remark							=other.m_remark							;

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
			return 16;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";							type=0;}
			if(order == 1){value = "elementid";								type=0;}
			if(order == 2){value = "practiceid";						type=0;}
			if(order == 3){value = "materialbalancemethod";				type=0;}
			if(order == 4){value = "adsorbedgasdesorption";				type=0;}
			if(order == 5){value = "stresssensitivity";					type=0;}
			if(order == 6){value = "slopem";							type=1;}
			if(order == 7){value = "interceptb";						type=1;}
			if(order == 8){value = "theoreticalproductionindex";		type=1;}
			if(order == 9){value = "calculatedtotalreserves";			type=1;}
			if(order ==10){value = "calculatedfreegasreserves";			type=1;}
			if(order ==11){value = "calculatedabsorbedgasreserves";		type=1;}
			if(order ==12){value = "abandonstratapressure";				type=1;}
			if(order ==13){value = "predictedeur";						type=1;}
			if(order ==14){value = "predictedrecoverypercent";			type=1;}
			if(order ==15){value = "remark";							type=2;}
		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_practiceid						);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%d", m_materialbalancemethod				);}
			if(order == 4) {::sprintf((char *)value.c_str(), "%d", m_adsorbedgasdesorption				);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%d", m_stresssensitivity					);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_slopem							);}
			if(order == 7) {::sprintf((char *)value.c_str(), "%f", m_interceptb						);}
			if(order == 8) {::sprintf((char *)value.c_str(), "%f", m_theoreticalproductionindex		);}
			if(order == 9) {::sprintf((char *)value.c_str(), "%f", m_calculatedtotalreserves			);}
			if(order ==10) {::sprintf((char *)value.c_str(), "%f", m_calculatedfreegasreserves			);}
			if(order ==11) {::sprintf((char *)value.c_str(), "%f", m_calculatedabsorbedgasreserves		);}
			if(order ==12) {::sprintf((char *)value.c_str(), "%f", m_abandonstratapressure				);}
			if(order ==13) {::sprintf((char *)value.c_str(), "%f", m_predictedeur						);}
			if(order ==14) {::sprintf((char *)value.c_str(), "%f", m_predictedrecoverypercent			);}
			if(order ==15) {value=m_remark							;}
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_practiceid							= ::atoi(value.c_str());}
			if(order == 3){m_materialbalancemethod				= ::atoi(value.c_str());}
			if(order == 4){m_adsorbedgasdesorption				= ::atoi(value.c_str());}
			if(order == 5){m_stresssensitivity					= ::atoi(value.c_str());}
			if(order == 6){m_slopem								= ::atof(value.c_str());}
			if(order == 7){m_interceptb							= ::atof(value.c_str());}
			if(order == 8){m_theoreticalproductionindex			= ::atof(value.c_str());}
			if(order == 9){m_calculatedtotalreserves			= ::atof(value.c_str());}
			if(order ==10){m_calculatedfreegasreserves			= ::atof(value.c_str());}
			if(order ==11){m_calculatedabsorbedgasreserves		= ::atof(value.c_str());}
			if(order ==12){m_abandonstratapressure				= ::atof(value.c_str());}
			if(order ==13){m_predictedeur						= ::atof(value.c_str());}
			if(order ==14){m_predictedrecoverypercent			= ::atof(value.c_str());}
			if(order ==15){m_remark	= value;}
			
			
		}
	};


/////////////////////////////
//PRT_Performance_DreMiddle
struct PerformanceDreMiddleRecord : public PropertyRecord
{
		int   m_practiceid					;
		float m_cumulativegasproduction		;
		float m_pz							;
		float m_gasproductivityindex		;
		int   m_pzdatastatus				;
		/*!
		*
		**/
		PerformanceDreMiddleRecord() 
		{
			m_practiceid					=0;
			m_cumulativegasproduction		=0;
			m_pz							=0;
			m_gasproductivityindex			=0;
			m_pzdatastatus					=0;


		}

		/*!
		*
		**/
		const PerformanceDreMiddleRecord &operator=(const PerformanceDreMiddleRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_practiceid					=other.m_practiceid					;	
			m_cumulativegasproduction		=other.m_cumulativegasproduction	;
			m_pz							=other.m_pz							;
			m_gasproductivityindex			=other.m_gasproductivityindex		;
			m_pzdatastatus					=other.m_pzdatastatus				;
			

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
			return 7;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 || order==2)
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";							type=0;}
			if(order == 1){value = "elementid";								type=0;}
			if(order == 2){value = "practiceid";							type=0;}
			if(order == 3){value = "cumulativegasproduction";				type=1;}
			if(order == 4){value = "pz";									type=1;}
			if(order == 5){value = "gasproductivityindex";					type=1;}
			if(order == 6){value = "pzdatastatus";							type=0;}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%d", m_practiceid					);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%f", m_cumulativegasproduction	);}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_pz							);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_gasproductivityindex		);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%d", m_pzdatastatus				);}
		
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_practiceid						= ::atoi(value.c_str());}
			if(order == 3){m_cumulativegasproduction		= ::atof(value.c_str());}
			if(order == 4){m_pz								= ::atof(value.c_str());}
			if(order == 5){m_gasproductivityindex			= ::atof(value.c_str());}
			if(order == 6){m_pzdatastatus					= ::atoi(value.c_str());}
			
			
		}
};

struct MlrResourceResultRecord : public PropertyRecord
{
		
		float	m_provedgeoreserves			;
		float	m_controlgeoreserves		;
		float	m_possiblegeoreserves		;
		float	m_provedtecreserves			;
		float	m_controltecreserves		;
		float	m_possibletecreserves		;
		float	m_provedecoreserves			;
		float	m_controlecoreserves		;
		float	m_possibleecoreserves		;
		float	m_potentialgeoreserves		;
		float	m_potentialtecreserves		;
		float	m_potentialecoreserves		;
		float	m_speculativegeoreserves	;
		float	m_speculativetecreserves	;
		float	m_speculativeecoreserves	;
		string	m_remark					;
		/*!
		*
		**/
		MlrResourceResultRecord() 
		{
			m_provedgeoreserves			=0;
			m_controlgeoreserves		=0;
			m_possiblegeoreserves		=0;
			m_provedtecreserves			=0;
			m_controltecreserves		=0;
			m_possibletecreserves		=0;
			m_provedecoreserves			=0;
			m_controlecoreserves		=0;
			m_possibleecoreserves		=0;
			m_potentialgeoreserves		=0;
			m_potentialtecreserves		=0;
			m_potentialecoreserves		=0;
			m_speculativegeoreserves	=0;
			m_speculativetecreserves	=0;
			m_speculativeecoreserves	=0;
			m_remark					="";
										
		}

		/*!
		*
		**/
		const MlrResourceResultRecord &operator=(const MlrResourceResultRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_provedgeoreserves			=other.m_provedgeoreserves			;	
			m_controlgeoreserves		=other.m_controlgeoreserves			;
			m_possiblegeoreserves		=other.m_possiblegeoreserves		;
			m_provedtecreserves			=other.m_provedtecreserves			;
			m_controltecreserves		=other.m_controltecreserves			;
			m_possibletecreserves		=other.m_possibletecreserves		;
			m_provedecoreserves			=other.m_provedecoreserves			;
			m_controlecoreserves		=other.m_controlecoreserves			;
			m_possibleecoreserves		=other.m_possibleecoreserves		;
			m_potentialgeoreserves		=other.m_potentialgeoreserves		;
			m_potentialtecreserves		=other.m_potentialtecreserves		;
			m_potentialecoreserves		=other.m_potentialecoreserves		;
			m_speculativegeoreserves	=other.m_speculativegeoreserves		;
			m_speculativetecreserves	=other.m_speculativetecreserves		;
			m_speculativeecoreserves	=other.m_speculativeecoreserves		;
			m_remark					=other.m_remark						;

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
			return 18;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 )
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";			type=0;}
			if(order == 1){value = "elementid";				type=0;}
			if(order == 2){value = "provedgeoreserves";		type=1;}
			if(order == 3){value = "controlgeoreserves";	type=1;}
			if(order == 4){value = "possiblegeoreserves";	type=1;}
			if(order == 5){value = "provedtecreserves";		type=1;}
			if(order == 6){value = "controltecreserves";	type=1;}
			if(order == 7){value = "possibletecreserves";	type=1;}
			if(order == 8){value = "provedecoreserves";		type=1;}
			if(order == 9){value = "controlecoreserves";	type=1;}
			if(order ==10){value = "possibleecoreserves";	type=1;}
			if(order ==11){value = "potentialgeoreserves";	type=1;}
			if(order ==12){value = "potentialtecreserves";	type=1;}
			if(order ==13){value = "potentialecoreserves";	type=1;}
			if(order ==14){value = "speculativegeoreserves";type=1;}
			if(order ==15){value = "speculativetecreserves";type=1;}
			if(order ==16){value = "speculativeecoreserves";type=1;}
			if(order ==17){value = "remark";				type=2;}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx						);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx					);}
			if(order == 2) {::sprintf((char *)value.c_str(), "%f", m_provedgeoreserves			);}
			if(order == 3) {::sprintf((char *)value.c_str(), "%f", m_controlgeoreserves			);}
			if(order == 4) {::sprintf((char *)value.c_str(), "%f", m_possiblegeoreserves		);}
			if(order == 5) {::sprintf((char *)value.c_str(), "%f", m_provedtecreserves			);}
			if(order == 6) {::sprintf((char *)value.c_str(), "%f", m_controltecreserves			);}
			if(order == 7) {::sprintf((char *)value.c_str(), "%f", m_possibletecreserves		);}
			if(order == 8) {::sprintf((char *)value.c_str(), "%f", m_provedecoreserves			);}
			if(order == 9) {::sprintf((char *)value.c_str(), "%f", m_controlecoreserves			);}
			if(order ==10) {::sprintf((char *)value.c_str(), "%f", m_possibleecoreserves		);}
			if(order ==11) {::sprintf((char *)value.c_str(), "%f", m_potentialgeoreserves		);}
			if(order ==12) {::sprintf((char *)value.c_str(), "%f", m_potentialtecreserves		);}
			if(order ==13) {::sprintf((char *)value.c_str(), "%f", m_potentialecoreserves		);}
			if(order ==14) {::sprintf((char *)value.c_str(), "%f", m_speculativegeoreserves		);}
			if(order ==15) {::sprintf((char *)value.c_str(), "%f", m_speculativetecreserves		);}
			if(order ==16) {::sprintf((char *)value.c_str(), "%f", m_speculativeecoreserves		);}
			if(order ==17) {value=m_remark	;}					   				
			
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_provedgeoreserves			= ::atof(value.c_str());}
			if(order == 3){m_controlgeoreserves			= ::atof(value.c_str());}
			if(order == 4){m_possiblegeoreserves		= ::atof(value.c_str());}
			if(order == 5){m_provedtecreserves			= ::atof(value.c_str());}
			if(order == 6){m_controltecreserves			= ::atof(value.c_str());}
			if(order == 7){m_possibletecreserves		= ::atof(value.c_str());}
			if(order == 8){m_provedecoreserves			= ::atof(value.c_str());}
			if(order == 9){m_controlecoreserves			= ::atof(value.c_str());}
			if(order ==10){m_possibleecoreserves		= ::atof(value.c_str());}
			if(order ==11){m_potentialgeoreserves		= ::atof(value.c_str());}
			if(order ==12){m_potentialtecreserves		= ::atof(value.c_str());}
			if(order ==13){m_potentialecoreserves		= ::atof(value.c_str());}
			if(order ==14){m_speculativegeoreserves		= ::atof(value.c_str());}
			if(order ==15){m_speculativetecreserves		= ::atof(value.c_str());}
			if(order ==16){m_speculativeecoreserves		= ::atof(value.c_str());}
			if(order ==17){m_remark = value	;}
			
		}
};


struct MlrcalibratedRecord : public PropertyRecord
{
	string m_calibratedname					;
	string m_calibratedlv					;
	string m_calibratedrestype				;
	string m_calibratedtype					;
	float  m_calibratedarea					;
	float  m_calibratedavgthick				;
	float  m_calibratedrockvol				;
	string m_calibratedbasintype			;
	string m_calibratedbasinname			;
	string m_calibrateddepressionname		;
	string m_calibratedhothis				;
	string m_calibratedcarryoutunit			;
	float  m_calibratedhcgen				;
	float  m_calibratedhcexp				;
	float  m_calibratedknowgeores			;
	float  m_calibratedctlgeores			;
	float  m_calibratedpregeores			;
	float  m_calibratedpottrapres			;
	float  m_calibratedgeores				;
	float  m_calibratedrecoveres			;
	float  m_calibratedgeoareaaboundance	;
	float  m_calibratedgeovolaboundance		;
	float  m_calibratedrecoveareaaboundance	;
	float  m_calibratedrecovevolaboundance	;
	float  m_calibratedcoefficient			;
	float  m_calibratedcf					;
	float  m_calibratedtrapdens				;
	float  m_calibratedareaindex			;
	float  m_calibratedsucindex				;
	float  m_calibratedminoilfield 			;


	MlrcalibratedRecord() 
	{
		m_calibratedname						="";		
		m_calibratedlv							="";
		m_calibratedrestype						="";
		m_calibratedtype						="";
		m_calibratedarea						=0;
		m_calibratedavgthick					=0;
		m_calibratedrockvol						=0;
		m_calibratedbasintype					="";
		m_calibratedbasinname					="";
		m_calibrateddepressionname				="";
		m_calibratedhothis						="";
		m_calibratedcarryoutunit				="";
		m_calibratedhcgen						=0;
		m_calibratedhcexp						=0;
		m_calibratedknowgeores					=0;
		m_calibratedctlgeores					=0;
		m_calibratedpregeores					=0;
		m_calibratedpottrapres					=0;
		m_calibratedgeores						=0;
		m_calibratedrecoveres					=0;
		m_calibratedgeoareaaboundance			=0;
		m_calibratedgeovolaboundance			=0;
		m_calibratedrecoveareaaboundance		=0;
		m_calibratedrecovevolaboundance			=0;
		m_calibratedcoefficient					=0;
		m_calibratedcf							=0;
		m_calibratedtrapdens					=0;
		m_calibratedareaindex					=0;
		m_calibratedsucindex					=0;
		m_calibratedminoilfield 				=0;
	}

	const MlrcalibratedRecord &operator=(const MlrcalibratedRecord &other)
	{
		if(this == &other)
		{
			return *this;
		}
		
		m_calibratedname						=other.m_calibratedname						;
		m_calibratedlv							=other.m_calibratedlv						;	
		m_calibratedrestype						=other.m_calibratedrestype					;	
		m_calibratedtype						=other.m_calibratedtype						;
		m_calibratedarea						=other.m_calibratedarea						;
		m_calibratedavgthick					=other.m_calibratedavgthick					;
		m_calibratedrockvol						=other.m_calibratedrockvol					;	
		m_calibratedbasintype					=other.m_calibratedbasintype				;	
		m_calibratedbasinname					=other.m_calibratedbasinname				;	
		m_calibrateddepressionname				=other.m_calibrateddepressionname			;	
		m_calibratedhothis						=other.m_calibratedhothis					;	
		m_calibratedcarryoutunit				=other.m_calibratedcarryoutunit				;
		m_calibratedhcgen						=other.m_calibratedhcgen					;	
		m_calibratedhcexp						=other.m_calibratedhcexp					;	
		m_calibratedknowgeores					=other.m_calibratedknowgeores				;	
		m_calibratedctlgeores					=other.m_calibratedctlgeores				;	
		m_calibratedpregeores					=other.m_calibratedpregeores				;	
		m_calibratedpottrapres					=other.m_calibratedpottrapres				;	
		m_calibratedgeores						=other.m_calibratedgeores					;	
		m_calibratedrecoveres					=other.m_calibratedrecoveres				;	
		m_calibratedgeoareaaboundance			=other.m_calibratedgeoareaaboundance		;	
		m_calibratedgeovolaboundance			=other.m_calibratedgeovolaboundance			;
		m_calibratedrecoveareaaboundance		=other.m_calibratedrecoveareaaboundance		;
		m_calibratedrecovevolaboundance			=other.m_calibratedrecovevolaboundance		;	
		m_calibratedcoefficient					=other.m_calibratedcoefficient				;	
		m_calibratedcf							=other.m_calibratedcf						;	
		m_calibratedtrapdens					=other.m_calibratedtrapdens					;
		m_calibratedareaindex					=other.m_calibratedareaindex				;	
		m_calibratedsucindex					=other.m_calibratedsucindex					;
		m_calibratedminoilfield 				=other.m_calibratedminoilfield 				;
		return *this;
	}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 32;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 )
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value ="propertyid";											type=0;}
			if(order == 1){value ="elementid";											type=0;}
			if(order == 2){value = "calibratedname";									type=3;}
			if(order == 3){value = "calibratedlv";									type=3;}
			if(order == 4){value = "calibratedrestype";								type=3;}
			if(order == 5){value = "calibratedtype";									type=3;}
			if(order == 6){value = "calibratedarea";									type=1;}
			if(order == 7){value = "calibratedavgthick";								type=1;}
			if(order == 8){value = "calibratedrockvol";								type=1;}
			if(order == 9){value = "calibratedbasintype";								type=3;}
			if(order ==10){value = "calibratedbasinname";								type=3;}
			if(order ==11){value = "calibrateddepressionname";						type=3;}
			if(order ==12){value = "calibratedhothis";								type=3;}
			if(order ==13){value = "calibratedcarryoutunit";							type=3;}
			if(order ==14){value = "calibratedhcgen";									type=1;}
			if(order ==15){value = "calibratedhcexp";									type=1;}
			if(order ==16){value = "calibratedknowgeores";							type=1;}
			if(order ==17){value = "calibratedctlgeores";								type=1;}
			if(order ==18){value = "calibratedpregeores";								type=1;}
			if(order ==19){value = "calibratedpottrapres";							type=1;}
			if(order ==20){value = "calibratedgeores";								type=1;}
			if(order ==21){value = "calibratedrecoveres";								type=1;}
			if(order ==22){value = "calibratedgeoareaaboundance";						type=1;}
			if(order ==23){value = "calibratedgeovolaboundance";						type=1;}
			if(order ==24){value = "calibratedrecoveareaaboundance";					type=1;}
			if(order ==25){value = "calibratedrecovevolaboundance";					type=1;}
			if(order ==26){value = "calibratedcoefficient";							type=1;}
			if(order ==27){value = "calibratedcf";									type=1;}
			if(order ==28){value = "calibratedtrapdens";								type=1;}
			if(order ==29){value = "calibratedareaindex";								type=1;}
			if(order ==30){value = "calibratedsucindex";								type=1;}
			if(order ==31){value = "calibratedminoilfield";							type=1;}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0){::sprintf((char *)value.c_str(), "%d", m_idx							);}
			if(order == 1){::sprintf((char *)value.c_str(), "%d", m_elementIdx					);}
			if(order == 2){value=m_calibratedname		;}
			if(order == 3){value=m_calibratedlv			;}
			if(order == 4){value=m_calibratedrestype	;}
			if(order == 5){value=m_calibratedtype		;}
			if(order == 6){::sprintf((char *)value.c_str(), "%f", m_calibratedarea				);}
			if(order == 7){::sprintf((char *)value.c_str(), "%f", m_calibratedavgthick			);}
			if(order == 8){::sprintf((char *)value.c_str(), "%f", m_calibratedrockvol			);}
			if(order == 9){value=m_calibratedbasintype		;}
			if(order ==10){value=m_calibratedbasinname		;}
			if(order ==11){value=m_calibrateddepressionname	;}
			if(order ==12){value=m_calibratedhothis			;}
			if(order ==13){value=m_calibratedcarryoutunit	;}
			if(order ==14){::sprintf((char *)value.c_str(), "%f", m_calibratedhcgen					);}
			if(order ==15){::sprintf((char *)value.c_str(), "%f", m_calibratedhcexp					);}
			if(order ==16){::sprintf((char *)value.c_str(), "%f", m_calibratedknowgeores			);}
			if(order ==17){::sprintf((char *)value.c_str(), "%f", m_calibratedctlgeores				);}
			if(order ==18){::sprintf((char *)value.c_str(), "%f", m_calibratedpregeores				);}
			if(order ==19){::sprintf((char *)value.c_str(), "%f", m_calibratedpottrapres			);}
			if(order ==20){::sprintf((char *)value.c_str(), "%f", m_calibratedgeores				);}
			if(order ==21){::sprintf((char *)value.c_str(), "%f", m_calibratedrecoveres				);}
			if(order ==22){::sprintf((char *)value.c_str(), "%f", m_calibratedgeoareaaboundance		);}
			if(order ==23){::sprintf((char *)value.c_str(), "%f", m_calibratedgeovolaboundance		);}
			if(order ==24){::sprintf((char *)value.c_str(), "%f", m_calibratedrecoveareaaboundance	);}
			if(order ==25){::sprintf((char *)value.c_str(), "%f", m_calibratedrecovevolaboundance	);}
			if(order ==26){::sprintf((char *)value.c_str(), "%f", m_calibratedcoefficient			);}
			if(order ==27){::sprintf((char *)value.c_str(), "%f", m_calibratedcf					);}
			if(order ==28){::sprintf((char *)value.c_str(), "%f", m_calibratedtrapdens				);}
			if(order ==29){::sprintf((char *)value.c_str(), "%f", m_calibratedareaindex				);}
			if(order ==30){::sprintf((char *)value.c_str(), "%f", m_calibratedsucindex				);}
			if(order ==31){::sprintf((char *)value.c_str(), "%f", m_calibratedminoilfield 			);}
		}
		////////////////////////////////////////////////////////////////////////////////
		void GetOilGasType(string &restypename)
		{
			restypename = m_calibratedrestype;
			if(m_calibratedrestype=="")
			{
				restypename="油";
			}
		}
		double GetGeoAreaAboundance()
		{
			return m_calibratedgeoareaaboundance;
		}
		double GetGeovolAboundance()
		{
			return m_calibratedgeovolaboundance;
		}
		double GetArea()
		{
			return m_calibratedarea;
		}
		double GetTrapNumber()
		{	
			return m_calibratedtrapdens*m_calibratedarea;
		}
		double GetVol()
		{	
			return m_calibratedrockvol;
		}
		/////////////////////////////////////////////////////////////////////////////////
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_calibratedname		    = value	;}
			if(order == 3){m_calibratedlv			= value	;}
			if(order == 4){m_calibratedrestype	    = value	;}
			if(order == 5){m_calibratedtype		    = value	;}
			if(order == 6){m_calibratedarea		= ::atof(value.c_str());}
			if(order == 7){m_calibratedavgthick	= ::atof(value.c_str());}
			if(order == 8){m_calibratedrockvol	= ::atof(value.c_str());}
			if(order == 9){m_calibratedbasintype		= value	;}
			if(order ==10){m_calibratedbasinname		= value	;}
			if(order ==11){m_calibrateddepressionname	= value	;}
			if(order ==12){m_calibratedhothis			= value	;}
			if(order ==13){m_calibratedcarryoutunit		= value	;}
			if(order ==14){m_calibratedhcgen				= ::atof(value.c_str());}
			if(order ==15){m_calibratedhcexp				= ::atof(value.c_str());}
			if(order ==16){m_calibratedknowgeores			= ::atof(value.c_str());}
			if(order ==17){m_calibratedctlgeores			= ::atof(value.c_str());}
			if(order ==18){m_calibratedpregeores			= ::atof(value.c_str());}
			if(order ==19){m_calibratedpottrapres			= ::atof(value.c_str());}
			if(order ==20){m_calibratedgeores				= ::atof(value.c_str());}
			if(order ==21){m_calibratedrecoveres			= ::atof(value.c_str());}
			if(order ==22){m_calibratedgeoareaaboundance	= ::atof(value.c_str());}
			if(order ==23){m_calibratedgeovolaboundance		= ::atof(value.c_str());}
			if(order ==24){m_calibratedrecoveareaaboundance	= ::atof(value.c_str());}
			if(order ==25){m_calibratedrecovevolaboundance	= ::atof(value.c_str());}
			if(order ==26){m_calibratedcoefficient			= ::atof(value.c_str());}
			if(order ==27){m_calibratedcf					= ::atof(value.c_str());}
			if(order ==28){m_calibratedtrapdens				= ::atof(value.c_str());}
			if(order ==29){m_calibratedareaindex			= ::atof(value.c_str());}
			if(order ==30){m_calibratedsucindex				= ::atof(value.c_str());}
			if(order ==31){m_calibratedminoilfield 			= ::atof(value.c_str());}
		}

};





struct ElementResourceRecord : public PropertyRecord
{
		long  m_calibrationtype								;
		float m_meanarea 									;
		float m_minarea 									;
		float m_maxarea 									;
		float m_meanrockvolume 								;
		float m_minrockvolume 								;
		float m_maxrockvolume 								;
		float m_oilgenerating								;
		float m_oildischarge 								;
		float m_oilprovreserves 							;
		float m_oilprovrecoverreserves 						;
		float m_oilcontrolreserves 							;
		float m_oilcontrolrecoverreserves 					;
		float m_oilpredreserves 							;
		float m_oilpredrecoverreserves 						;
		float m_oilpotentialresources 						;
		float m_oilnodiscovresources 						;
		float m_oilnodiscovrecoverresources 				;
		float m_oilresourcemean 							;
		float m_oilresourcemin 								;
		float m_oilresourcemax 								;
		float m_oilrecoverresourcemean 						;
		float m_oilrecoverresourcemin 						;
		float m_oilrecoverresourcemax 						;
		float m_gasgenerating 								;
		float m_gasdischarge 								;
		float m_gasprovreserves 							;
		float m_gasprovrecoverreserves 						;
		float m_gascontrolreserves 							;
		float m_gascontrolrecoverreserves 					;
		float m_gaspredreserves 							;
		float m_gaspredrecoverreserves 						;
		float m_gaspotentialresources 						;
		float m_gasnodiscovresources 						;
		float m_gasnodiscovrecoverresources 				;
		float m_gasresourcemean 							;
		float m_gasresourcemin 								;
		float m_gasresourcemax 								;
		float m_gasrecoverresourcemean 						;
		float m_gasrecoverresourcemin 						;
		float m_gasrecoverresourcemax 						;
		float m_condensateoilprovreserves 					;
		float m_condensateoilprovrecoverreserves 			;
		float m_condensateoilcontrolreserves 				;
		float m_condensateoilcontrolrecoverreserves 		;
		float m_condensateoilpredreserves 					;
		float m_condensateoilpredrecoverreserves 			;
		float m_condensateoilnodiscovresources 				;
		float m_condensateoilnodiscovrecoverresources 		;
		float m_condensateoilresourcemean 					;
		float m_condensateoilresourcemin 					;
		float m_condensateoilresourcemax 					;
		float m_condensateoilrecoverresourcemean 			;
		float m_condensateoilrecoverresourcemin 			;
		float m_condensateoilrecoverresourcemax 			;

	ElementResourceRecord() 
	{
			m_calibrationtype								=0;
			m_meanarea 										=0;
			m_minarea 										=0;
			m_maxarea 										=0;
			m_meanrockvolume 								=0;
			m_minrockvolume 								=0;
			m_maxrockvolume 								=0;
			m_oilgenerating								=0;						
			m_oildischarge 								=0;
			m_oilprovreserves 							=0;
			m_oilprovrecoverreserves 						=0;
			m_oilcontrolreserves 							=0;
			m_oilcontrolrecoverreserves 					=0;
			m_oilpredreserves 							=0;
			m_oilpredrecoverreserves 						=0;
			m_oilpotentialresources 						=0;
			m_oilnodiscovresources 						=0;
			m_oilnodiscovrecoverresources 				=0;
			m_oilresourcemean 							=0;
			m_oilresourcemin 								=0;
			m_oilresourcemax 								=0;
			m_oilrecoverresourcemean 						=0;
			m_oilrecoverresourcemin 						=0;
			m_oilrecoverresourcemax 						=0;
			m_gasgenerating 								=0;
			m_gasdischarge 								=0;
			m_gasprovreserves 							=0;
			m_gasprovrecoverreserves 						=0;
			m_gascontrolreserves 							=0;
			m_gascontrolrecoverreserves 					=0;
			m_gaspredreserves 							=0;
			m_gaspredrecoverreserves 						=0;
			m_gaspotentialresources 						=0;
			m_gasnodiscovresources 						=0;
			m_gasnodiscovrecoverresources 				=0;
			m_gasresourcemean 							=0;
			m_gasresourcemin 								=0;
			m_gasresourcemax 								=0;
			m_gasrecoverresourcemean 						=0;
			m_gasrecoverresourcemin 						=0;
			m_gasrecoverresourcemax 						=0;
			m_condensateoilprovreserves 					=0;
			m_condensateoilprovrecoverreserves 			=0;
			m_condensateoilcontrolreserves 				=0;
			m_condensateoilcontrolrecoverreserves 		=0;
			m_condensateoilpredreserves 					=0;
			m_condensateoilpredrecoverreserves 			=0;
			m_condensateoilnodiscovresources 				=0;
			m_condensateoilnodiscovrecoverresources 		=0;
			m_condensateoilresourcemean 					=0;
			m_condensateoilresourcemin 					=0;
			m_condensateoilresourcemax 					=0;
			m_condensateoilrecoverresourcemean 			=0;
			m_condensateoilrecoverresourcemin 			=0;
			m_condensateoilrecoverresourcemax 			=0;
	}

	const ElementResourceRecord &operator=(const ElementResourceRecord &other)
	{
		if(this == &other)
		{
			return *this;
		}
		
		m_calibrationtype							=other.m_calibrationtype								;										
		m_meanarea 									=other.m_meanarea 										;
		m_minarea 									=other.m_minarea 										;
		m_maxarea 									=other.m_maxarea 										;
		m_meanrockvolume 							=other.m_meanrockvolume 								;
		m_minrockvolume 							=other.m_minrockvolume 									;
		m_maxrockvolume 							=other.m_maxrockvolume 									;
		m_oilgenerating								=other.m_oilgenerating								;				
		m_oildischarge 								=other.m_oildischarge 								;
		m_oilprovreserves 							=other.m_oilprovreserves 							;
		m_oilprovrecoverreserves 					=other.m_oilprovrecoverreserves 						;
		m_oilcontrolreserves 						=other.m_oilcontrolreserves 							;
		m_oilcontrolrecoverreserves 				=other.m_oilcontrolrecoverreserves 					;
		m_oilpredreserves 							=other.m_oilpredreserves 							;
		m_oilpredrecoverreserves 					=other.m_oilpredrecoverreserves 						;
		m_oilpotentialresources 					=other.m_oilpotentialresources 						;
		m_oilnodiscovresources 						=other.m_oilnodiscovresources 						;
		m_oilnodiscovrecoverresources 				=other.m_oilnodiscovrecoverresources 				;
		m_oilresourcemean 							=other.m_oilresourcemean 							;
		m_oilresourcemin 							=other.m_oilresourcemin 								;
		m_oilresourcemax 							=other.m_oilresourcemax 								;
		m_oilrecoverresourcemean 					=other.m_oilrecoverresourcemean 						;
		m_oilrecoverresourcemin 					=other.m_oilrecoverresourcemin 						;
		m_oilrecoverresourcemax 					=other.m_oilrecoverresourcemax 						;
		m_gasgenerating 							=other.m_gasgenerating 								;
		m_gasdischarge 								=other.m_gasdischarge 								;
		m_gasprovreserves 							=other.m_gasprovreserves 							;
		m_gasprovrecoverreserves 					=other.m_gasprovrecoverreserves 						;
		m_gascontrolreserves 						=other.m_gascontrolreserves 							;
		m_gascontrolrecoverreserves 				=other.m_gascontrolrecoverreserves 					;
		m_gaspredreserves 							=other.m_gaspredreserves 							;
		m_gaspredrecoverreserves 					=other.m_gaspredrecoverreserves 						;
		m_gaspotentialresources 					=other.m_gaspotentialresources 						;
		m_gasnodiscovresources 						=other.m_gasnodiscovresources 						;
		m_gasnodiscovrecoverresources 				=other.m_gasnodiscovrecoverresources 				;
		m_gasresourcemean 							=other.m_gasresourcemean 							;
		m_gasresourcemin 							=other.m_gasresourcemin 								;
		m_gasresourcemax 							=other.m_gasresourcemax 								;
		m_gasrecoverresourcemean 					=other.m_gasrecoverresourcemean 						;
		m_gasrecoverresourcemin 					=other.m_gasrecoverresourcemin 						;
		m_gasrecoverresourcemax 					=other.m_gasrecoverresourcemax 						;
		m_condensateoilprovreserves 				=other.m_condensateoilprovreserves 					;
		m_condensateoilprovrecoverreserves 			=other.m_condensateoilprovrecoverreserves 			;
		m_condensateoilcontrolreserves 				=other.m_condensateoilcontrolreserves 				;
		m_condensateoilcontrolrecoverreserves 		=other.m_condensateoilcontrolrecoverreserves 		;
		m_condensateoilpredreserves 				=other.m_condensateoilpredreserves 					;
		m_condensateoilpredrecoverreserves 			=other.m_condensateoilpredrecoverreserves 			;
		m_condensateoilnodiscovresources 			=other.m_condensateoilnodiscovresources 				;
		m_condensateoilnodiscovrecoverresources 	=other.m_condensateoilnodiscovrecoverresources 		;
		m_condensateoilresourcemean 				=other.m_condensateoilresourcemean 					;
		m_condensateoilresourcemin 					=other.m_condensateoilresourcemin 					;
		m_condensateoilresourcemax 					=other.m_condensateoilresourcemax 					;
		m_condensateoilrecoverresourcemean 			=other.m_condensateoilrecoverresourcemean 			;
		m_condensateoilrecoverresourcemin 			=other.m_condensateoilrecoverresourcemin 			;
		m_condensateoilrecoverresourcemax 			=other.m_condensateoilrecoverresourcemax 			;
	
		return *this;
	}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 57;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 )
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";										type=0;}
			if(order == 1){value = "elementid";											type=0;}
			if(order == 2){value = "calibrationtype";									type=0;}
			if(order == 3){value = "meanarea";											type=1;}
			if(order == 4){value = "minarea";											type=1;}
			if(order == 5){value = "maxarea";											type=1;}
			if(order == 6){value = "meanrockvolume";									type=1;}
			if(order == 7){value = "minrockvolume";										type=1;}
			if(order == 8){value = "maxrockvolume";										type=1;}
			if(order == 9){value = "oilgenerating";type=1;}
			if(order ==10){value = "oildischarge";type=1;}
			if(order ==11){value = "oilprovreserves";type=1;}
			if(order ==12){value = "oilprovrecoverreserves";type=1;}
			if(order ==13){value = "oilcontrolreserves";type=1;}
			if(order ==14){value = "oilcontrolrecoverreserves";type=1;}
			if(order ==15){value = "oilpredreserves";type=1;}
			if(order ==16){value = "oilpredrecoverreserves";type=1;}
			if(order ==17){value = "oilpotentialresources";type=1;}
			if(order ==18){value = "oilnodiscovresources";type=1;}
			if(order ==19){value = "oilnodiscovrecoverresources";type=1;}
			if(order ==20){value = "oilresourcemean";type=1;}
			if(order ==21){value = "oilresourcemin";type=1;}
			if(order ==22){value = "oilresourcemax";type=1;}
			if(order ==23){value = "oilrecoverresourcemean";type=1;}
			if(order ==24){value = "oilrecoverresourcemin";type=1;}
			if(order ==25){value = "oilrecoverresourcemax";type=1;}
			if(order ==26){value = "gasgenerating";type=1;}
			if(order ==27){value = "gasdischarge";type=1;}
			if(order ==28){value = "gasprovreserves";type=1;}
			if(order ==29){value = "gasprovrecoverreserves";type=1;}
			if(order ==30){value = "gascontrolreserves";type=1;}
			if(order ==31){value = "gascontrolrecoverreserves";type=1;}
			if(order ==32){value = "gaspredreserves";type=1;}
			if(order ==33){value = "gaspredrecoverreserves";type=1;}
			if(order ==34){value = "gaspotentialresources";type=1;}
			if(order ==35){value = "gasnodiscovresources";type=1;}
			if(order ==36){value = "gasnodiscovrecoverresources";type=1;}
			if(order ==37){value = "gasresourcemean";type=1;}
			if(order ==38){value = "gasresourcemin";type=1;}
			if(order ==39){value = "gasresourcemax";type=1;}
			if(order ==40){value = "gasrecoverresourcemean";type=1;}
			if(order ==41){value = "gasrecoverresourcemin";type=1;}
			if(order ==42){value = "gasrecoverresourcemax";type=1;}
			if(order ==43){value = "condensateoilprovreserves";type=1;}
			if(order ==44){value = "condensateoilprovrecoverreserves";type=1;}
			if(order ==45){value = "condensateoilcontrolreserves";type=1;}
			if(order ==46){value = "condensateoilcontrolrecoverreserves";type=1;}
			if(order ==47){value = "condensateoilpredreserves";type=1;}
			if(order ==48){value = "condensateoilpredrecoverreserves";type=1;}
			if(order ==49){value = "condensateoilnodiscovresources";type=1;}
			if(order ==50){value = "condensateoilnodiscovrecoverresources";type=1;}
			if(order ==51){value = "condensateoilresourcemean";type=1;}
			if(order ==52){value = "condensateoilresourcemin";type=1;}
			if(order ==53){value = "condensateoilresourcemax";type=1;}
			if(order ==54){value = "condensateoilrecoverresourcemean";type=1;}
			if(order ==55){value = "condensateoilrecoverresourcemin";type=1;}
			if(order ==56){value = "condensateoilrecoverresourcemax";type=1;}

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0){::sprintf((char *)value.c_str(), "%d", m_idx											);}
			if(order == 1){::sprintf((char *)value.c_str(), "%d", m_elementIdx									);}
			if(order == 2){::sprintf((char *)value.c_str(), "%f", m_calibrationtype								);}
			if(order == 3){::sprintf((char *)value.c_str(), "%f", m_meanarea 									);}
			if(order == 4){::sprintf((char *)value.c_str(), "%f", m_minarea 									);}
			if(order == 5){::sprintf((char *)value.c_str(), "%f", m_maxarea 									);}
			if(order == 6){::sprintf((char *)value.c_str(), "%f", m_meanrockvolume 								);}
			if(order == 7){::sprintf((char *)value.c_str(), "%f", m_minrockvolume 								);}
			if(order == 8){::sprintf((char *)value.c_str(), "%f", m_maxrockvolume 								);}
			if(order == 9){::sprintf((char *)value.c_str(), "%f", m_oilgenerating								);}
			if(order ==10){::sprintf((char *)value.c_str(), "%f", m_oildischarge 								);}
			if(order ==11){::sprintf((char *)value.c_str(), "%f", m_oilprovreserves 								);}
			if(order ==12){::sprintf((char *)value.c_str(), "%f", m_oilprovrecoverreserves 						);}
			if(order ==13){::sprintf((char *)value.c_str(), "%f", m_oilcontrolreserves 							);}
			if(order ==14){::sprintf((char *)value.c_str(), "%f", m_oilcontrolrecoverreserves 						);}
			if(order ==15){::sprintf((char *)value.c_str(), "%f", m_oilpredreserves 									);}
			if(order ==16){::sprintf((char *)value.c_str(), "%f", m_oilpredrecoverreserves 						);}
			if(order ==17){::sprintf((char *)value.c_str(), "%f", m_oilpotentialresources 						);}
			if(order ==18){::sprintf((char *)value.c_str(), "%f", m_oilnodiscovresources 							);}
			if(order ==19){::sprintf((char *)value.c_str(), "%f", m_oilnodiscovrecoverresources 						);}
			if(order ==20){::sprintf((char *)value.c_str(), "%f", m_oilresourcemean 								);}
			if(order ==21){::sprintf((char *)value.c_str(), "%f", m_oilresourcemin 									);}
			if(order ==22){::sprintf((char *)value.c_str(), "%f", m_oilresourcemax 								);}
			if(order ==23){::sprintf((char *)value.c_str(), "%f", m_oilrecoverresourcemean 							);}
			if(order ==24){::sprintf((char *)value.c_str(), "%f", m_oilrecoverresourcemin 						);}
			if(order ==25){::sprintf((char *)value.c_str(), "%f", m_oilrecoverresourcemax 							);}
			if(order ==26){::sprintf((char *)value.c_str(), "%f", m_gasgenerating 									);}
			if(order ==27){::sprintf((char *)value.c_str(), "%f", m_gasdischarge 										);}
			if(order ==28){::sprintf((char *)value.c_str(), "%f", m_gasprovreserves 								);}
			if(order ==29){::sprintf((char *)value.c_str(), "%f", m_gasprovrecoverreserves 						);}
			if(order ==30){::sprintf((char *)value.c_str(), "%f", m_gascontrolreserves 							);}
			if(order ==31){::sprintf((char *)value.c_str(), "%f", m_gascontrolrecoverreserves 						);}
			if(order ==32){::sprintf((char *)value.c_str(), "%f", m_gaspredreserves 									);}
			if(order ==33){::sprintf((char *)value.c_str(), "%f", m_gaspredrecoverreserves 						);}
			if(order ==34){::sprintf((char *)value.c_str(), "%f", m_gaspotentialresources 						);}
			if(order ==35){::sprintf((char *)value.c_str(), "%f", m_gasnodiscovresources 							);}
			if(order ==36){::sprintf((char *)value.c_str(), "%f", m_gasnodiscovrecoverresources 						);}
			if(order ==37){::sprintf((char *)value.c_str(), "%f", m_gasresourcemean 								);}
			if(order ==38){::sprintf((char *)value.c_str(), "%f", m_gasresourcemin 									);}
			if(order ==39){::sprintf((char *)value.c_str(), "%f", m_gasresourcemax 								);}
			if(order ==40){::sprintf((char *)value.c_str(), "%f", m_gasrecoverresourcemean 							);}
			if(order ==41){::sprintf((char *)value.c_str(), "%f", m_gasrecoverresourcemin 						);}
			if(order ==42){::sprintf((char *)value.c_str(), "%f", m_gasrecoverresourcemax 							);}
			if(order ==43){::sprintf((char *)value.c_str(), "%f", m_condensateoilprovreserves 						);}
			if(order ==44){::sprintf((char *)value.c_str(), "%f", m_condensateoilprovrecoverreserves 					);}
			if(order ==45){::sprintf((char *)value.c_str(), "%f", m_condensateoilcontrolreserves 						);}
			if(order ==46){::sprintf((char *)value.c_str(), "%f", m_condensateoilcontrolrecoverreserves 			);}
			if(order ==47){::sprintf((char *)value.c_str(), "%f", m_condensateoilpredreserves 					);}
			if(order ==48){::sprintf((char *)value.c_str(), "%f", m_condensateoilpredrecoverreserves 					);}
			if(order ==49){::sprintf((char *)value.c_str(), "%f", m_condensateoilnodiscovresources 				);}
			if(order ==50){::sprintf((char *)value.c_str(), "%f", m_condensateoilnodiscovrecoverresources 			);}
			if(order ==51){::sprintf((char *)value.c_str(), "%f", m_condensateoilresourcemean 						);}
			if(order ==52){::sprintf((char *)value.c_str(), "%f", m_condensateoilresourcemin 						);}
			if(order ==53){::sprintf((char *)value.c_str(), "%f", m_condensateoilresourcemax 							);}
			if(order ==54){::sprintf((char *)value.c_str(), "%f", m_condensateoilrecoverresourcemean 				);}
			if(order ==55){::sprintf((char *)value.c_str(), "%f", m_condensateoilrecoverresourcemin 					);}
			if(order ==56){::sprintf((char *)value.c_str(), "%f", m_condensateoilrecoverresourcemax 				);}
			
		}
		////////////////////////////////////////////////////////////////////////////////
	
		/////////////////////////////////////////////////////////////////////////////////
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_calibrationtype									= ::atoi(value.c_str());}
			if(order == 3){m_meanarea 											= ::atof(value.c_str());}
			if(order == 4){m_minarea 											= ::atof(value.c_str());}
			if(order == 5){m_maxarea 											= ::atof(value.c_str());}
			if(order == 6){m_meanrockvolume 									= ::atof(value.c_str());}
			if(order == 7){m_minrockvolume 										= ::atof(value.c_str());}
			if(order == 8){m_maxrockvolume 										= ::atof(value.c_str());}
			if(order == 9){m_oilgenerating										= ::atof(value.c_str());}
			if(order ==10){m_oildischarge 										= ::atof(value.c_str());}
			if(order ==11){m_oilprovreserves 									= ::atof(value.c_str());}
			if(order ==12){m_oilprovrecoverreserves 							= ::atof(value.c_str());}
			if(order ==13){m_oilcontrolreserves 								= ::atof(value.c_str());}
			if(order ==14){m_oilcontrolrecoverreserves 						= ::atof(value.c_str());}
			if(order ==15){m_oilpredreserves 									= ::atof(value.c_str());}
			if(order ==16){m_oilpredrecoverreserves 							= ::atof(value.c_str());}
			if(order ==17){m_oilpotentialresources 						= ::atof(value.c_str());}
			if(order ==18){m_oilnodiscovresources 							= ::atof(value.c_str());}
			if(order ==19){m_oilnodiscovrecoverresources 						= ::atof(value.c_str());}
			if(order ==20){m_oilresourcemean 									= ::atof(value.c_str());}
			if(order ==21){m_oilresourcemin 										= ::atof(value.c_str());}
			if(order ==22){m_oilresourcemax 										= ::atof(value.c_str());}
			if(order ==23){m_oilrecoverresourcemean 								= ::atof(value.c_str());}
			if(order ==24){m_oilrecoverresourcemin 						= ::atof(value.c_str());}
			if(order ==25){m_oilrecoverresourcemax 							= ::atof(value.c_str());}
			if(order ==26){m_gasgenerating 									= ::atof(value.c_str());}
			if(order ==27){m_gasdischarge 										= ::atof(value.c_str());}
			if(order ==28){m_gasprovreserves 									= ::atof(value.c_str());}
			if(order ==29){m_gasprovrecoverreserves 							= ::atof(value.c_str());}
			if(order ==30){m_gascontrolreserves 								= ::atof(value.c_str());}
			if(order ==31){m_gascontrolrecoverreserves 						= ::atof(value.c_str());}
			if(order ==32){m_gaspredreserves 									= ::atof(value.c_str());}
			if(order ==33){m_gaspredrecoverreserves 							= ::atof(value.c_str());}
			if(order ==34){m_gaspotentialresources 						= ::atof(value.c_str());}
			if(order ==35){m_gasnodiscovresources 							= ::atof(value.c_str());}
			if(order ==36){m_gasnodiscovrecoverresources 						= ::atof(value.c_str());}
			if(order ==37){m_gasresourcemean 									= ::atof(value.c_str());}
			if(order ==38){m_gasresourcemin 										= ::atof(value.c_str());}
			if(order ==39){m_gasresourcemax 										= ::atof(value.c_str());}
			if(order ==40){m_gasrecoverresourcemean 								= ::atof(value.c_str());}
			if(order ==41){m_gasrecoverresourcemin 						= ::atof(value.c_str());}
			if(order ==42){m_gasrecoverresourcemax 							= ::atof(value.c_str());}
			if(order ==43){m_condensateoilprovreserves 						= ::atof(value.c_str());}
			if(order ==44){m_condensateoilprovrecoverreserves 					= ::atof(value.c_str());}
			if(order ==45){m_condensateoilcontrolreserves 						= ::atof(value.c_str());}
			if(order ==46){m_condensateoilcontrolrecoverreserves 				= ::atof(value.c_str());}
			if(order ==47){m_condensateoilpredreserves 					= ::atof(value.c_str());}
			if(order ==48){m_condensateoilpredrecoverreserves 					= ::atof(value.c_str());}
			if(order ==49){m_condensateoilnodiscovresources 					= ::atof(value.c_str());}
			if(order ==50){m_condensateoilnodiscovrecoverresources 			= ::atof(value.c_str());}
			if(order ==51){m_condensateoilresourcemean 						= ::atof(value.c_str());}
			if(order ==52){m_condensateoilresourcemin 						= ::atof(value.c_str());}
			if(order ==53){m_condensateoilresourcemax 							= ::atof(value.c_str());}
			if(order ==54){m_condensateoilrecoverresourcemean 					= ::atof(value.c_str());}
			if(order ==55){m_condensateoilrecoverresourcemin 					= ::atof(value.c_str());}
			if(order ==56){m_condensateoilrecoverresourcemax 					= ::atof(value.c_str());}
		}

};


struct ElementResourceShaleRecord : public PropertyRecord
{
		long  m_calibrationtype					;
		float m_meanarea 						;
		float m_minarea 						;
		float m_maxarea 						;
		float m_meanrockvolume 					;
		float m_minrockvolume 					;
		float m_maxrockvolume 					;
		float m_meanthickness 					;
		float m_minthickness 					;
		float m_maxthickness 					;
		float m_meanrecoverresource 			;
		float m_minrecoverresource 				;
		float m_maxrecoverresource 				;
		float m_meanrecoverreserve 				;
		float m_minrecoverreserve 				;
		float m_maxrecoverreserve 				;
		float m_meanrecoverresourceabundance 	;
		float m_minrecoverresourceabundance 	;
		float m_maxrecoverresourceabundance 	;
		float m_meanrecoverreserveabundance 	;
		float m_minrecoverreserveabundance 		;
		float m_maxrecoverreserveabundance 		;
		float m_meanresource					;
		float m_minresource 					;
		float m_maxresource 					;
		float m_meanreserve 					;
		float m_minreserve 						;
		float m_maxreserve 						;
		float m_meanresourceabundance 			;
		float m_minresourceabundance 			;
		float m_maxresourceabundance 			;
		float m_meanreserveabundance 			;
		float m_minreserveabundance 			;
		float m_maxreserveabundance 			;
		float m_recoverablecoeffiecient 		;
		string m_exploretype					;

	ElementResourceShaleRecord() 
	{
		m_calibrationtype					=0;
		m_meanarea 							=0;
		m_minarea 							=0;
		m_maxarea 							=0;
		m_meanrockvolume 					=0;
		m_minrockvolume 					=0;
		m_maxrockvolume 					=0;
		m_meanthickness 					=0;
		m_minthickness 						=0;
		m_maxthickness 						=0;
		m_meanrecoverresource 				=0;
		m_minrecoverresource 				=0;
		m_maxrecoverresource 				=0;
		m_meanrecoverreserve 				=0;
		m_minrecoverreserve 				=0;
		m_maxrecoverreserve 				=0;
		m_meanrecoverresourceabundance		=0;
		m_minrecoverresourceabundance 		=0;
		m_maxrecoverresourceabundance 		=0;
		m_meanrecoverreserveabundance 		=0;
		m_minrecoverreserveabundance 		=0;
		m_maxrecoverreserveabundance 		=0;
		m_meanresource						=0;
		m_minresource 						=0;
		m_maxresource 						=0;
		m_meanreserve 						=0;
		m_minreserve 						=0;
		m_maxreserve 						=0;
		m_meanresourceabundance 			=0;
		m_minresourceabundance 				=0;
		m_maxresourceabundance 				=0;
		m_meanreserveabundance 				=0;
		m_minreserveabundance 				=0;
		m_maxreserveabundance 				=0;
		m_recoverablecoeffiecient 			=0;
		m_exploretype						="";
	}

	const ElementResourceShaleRecord &operator=(const ElementResourceShaleRecord &other)
	{
		if(this == &other)
		{
			return *this;
		}
		
		m_calibrationtype				=other.m_calibrationtype				;	
		m_meanarea 						=other.m_meanarea 						;
		m_minarea 						=other.m_minarea 						;
		m_maxarea 						=other.m_maxarea 						;
		m_meanrockvolume 				=other.m_meanrockvolume 				;
		m_minrockvolume 				=other.m_minrockvolume 					;
		m_maxrockvolume 				=other.m_maxrockvolume 					;
		m_meanthickness 				=other.m_meanthickness 					;
		m_minthickness 					=other.m_minthickness 					;
		m_maxthickness 					=other.m_maxthickness 					;
		m_meanrecoverresource 			=other.m_meanrecoverresource 			;
		m_minrecoverresource 			=other.m_minrecoverresource 			;
		m_maxrecoverresource 			=other.m_maxrecoverresource 			;
		m_meanrecoverreserve 			=other.m_meanrecoverreserve 			;
		m_minrecoverreserve 			=other.m_minrecoverreserve 				;
		m_maxrecoverreserve 			=other.m_maxrecoverreserve 				;
		m_meanrecoverresourceabundance	=other.m_meanrecoverresourceabundance	;
		m_minrecoverresourceabundance 	=other.m_minrecoverresourceabundance 	;
		m_maxrecoverresourceabundance 	=other.m_maxrecoverresourceabundance 	;
		m_meanrecoverreserveabundance 	=other.m_meanrecoverreserveabundance 	;
		m_minrecoverreserveabundance 	=other.m_minrecoverreserveabundance 	;
		m_maxrecoverreserveabundance 	=other.m_maxrecoverreserveabundance 	;
		m_meanresource					=other.m_meanresource					;		
		m_minresource 					=other.m_minresource 					;		
		m_maxresource 					=other.m_maxresource 					;		
		m_meanreserve 					=other.m_meanreserve 					;		
		m_minreserve 					=other.m_minreserve 					;		
		m_maxreserve 					=other.m_maxreserve 					;		
		m_meanresourceabundance 		=other.m_meanresourceabundance 			;	
		m_minresourceabundance 			=other.m_minresourceabundance 			;		
		m_maxresourceabundance 			=other.m_maxresourceabundance 			;		
		m_meanreserveabundance 			=other.m_meanreserveabundance 			;		
		m_minreserveabundance 			=other.m_minreserveabundance 			;		
		m_maxreserveabundance 			=other.m_maxreserveabundance 			;		
		m_recoverablecoeffiecient 		=other.m_recoverablecoeffiecient 		;		
		m_exploretype					=other.m_exploretype					;		
		return *this;
	}

		/*!
		*
		**/
		int GetFldCount()
		{
			return 38;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 )
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value ="propertyid";											type=0;}
			if(order == 1){value ="elementid";											type=0;}
			if(order == 2){value = "calibrationtype";					type=0;}
			if(order == 3){value = "meanarea"; 						type=1;}
			if(order == 4){value = "minarea"; 						type=1;}
			if(order == 5){value = "maxarea"; 							type=1;}
			if(order == 6){value = "meanrockvolume"; 					type=1;}
			if(order == 7){value = "minrockvolume"; 					type=1;}
			if(order == 8){value = "maxrockvolume"; 				type=1;}
			if(order == 9){value = "meanthickness"; 					type=1;}
			if(order ==10){value = "minthickness"; 						type=1;}
			if(order ==11){value = "maxthickness"; 					type=1;}
			if(order ==12){value = "meanrecoverresource"; 			type=1;}
			if(order ==13){value = "minrecoverresource"; 				type=1;}
			if(order ==14){value = "maxrecoverresource"; 				type=1;}
			if(order ==15){value = "meanrecoverreserve"; 				type=1;}
			if(order ==16){value = "minrecoverreserve"; 			type=1;}
			if(order ==17){value = "maxrecoverreserve"; 				type=1;}
			if(order ==18){value = "meanrecoverresourceabundance";		type=1;}
			if(order ==19){value = "minrecoverresourceabundance"; 	type=1;}
			if(order ==20){value = "maxrecoverresourceabundance"; 	type=1;}
			if(order ==21){value = "meanrecoverreserveabundance"; 		type=1;}
			if(order ==22){value = "minrecoverreserveabundance"; 		type=1;}
			if(order ==23){value = "maxrecoverreserveabundance"; 		type=1;}
			if(order ==24){value = "meanresource"; 		type=1;}
			if(order ==25){value = "minresource"; 		type=1;}
			if(order ==26){value = "maxresource"; 		type=1;}
			if(order ==27){value = "meanreserve"; 		type=1;}
			if(order ==28){value = "minreserve"; 		type=1;}
			if(order ==29){value = "maxreserve"; 		type=1;}
			if(order ==30){value = "meanresourceabundance"; 		type=1;}
			if(order ==31){value = "minresourceabundance"; 		type=1;}
			if(order ==32){value = "maxresourceabundance"; 		type=1;}
			if(order ==33){value = "meanreserveabundance"; 		type=1;}
			if(order ==34){value = "minreserveabundance"; 		type=1;}
			if(order ==35){value = "maxreserveabundance"; 		type=1;}
			if(order ==36){value = "recoverablecoeffiecient"; 		type=1;}
			if(order ==37){value = "exploretype"; 		type=2;}
			

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0){::sprintf((char *)value.c_str(), "%d", m_idx								);}
			if(order == 1){::sprintf((char *)value.c_str(), "%d", m_elementIdx						);}
			if(order == 2){::sprintf((char *)value.c_str(), "%d", m_calibrationtype					);}
			if(order == 3){::sprintf((char *)value.c_str(), "%f", m_meanarea 							);}
			if(order == 4){::sprintf((char *)value.c_str(), "%f", m_minarea 							);}
			if(order == 5){::sprintf((char *)value.c_str(), "%f", m_maxarea 							);}
			if(order == 6){::sprintf((char *)value.c_str(), "%f", m_meanrockvolume 					);}
			if(order == 7){::sprintf((char *)value.c_str(), "%f", m_minrockvolume 					);}
			if(order == 8){::sprintf((char *)value.c_str(), "%f", m_maxrockvolume 					);}
			if(order == 9){::sprintf((char *)value.c_str(), "%f", m_meanthickness 					);}
			if(order ==10){::sprintf((char *)value.c_str(), "%f", m_minthickness 						);}
			if(order ==11){::sprintf((char *)value.c_str(), "%f", m_maxthickness 						);}
			if(order ==12){::sprintf((char *)value.c_str(), "%f", m_meanrecoverresource 				);}
			if(order ==13){::sprintf((char *)value.c_str(), "%f", m_minrecoverresource 				);}
			if(order ==14){::sprintf((char *)value.c_str(), "%f", m_maxrecoverresource 				);}
			if(order ==15){::sprintf((char *)value.c_str(), "%f", m_meanrecoverreserve 				);}
			if(order ==16){::sprintf((char *)value.c_str(), "%f", m_minrecoverreserve 				);}
			if(order ==17){::sprintf((char *)value.c_str(), "%f", m_maxrecoverreserve 				);}
			if(order ==18){::sprintf((char *)value.c_str(), "%f", m_meanrecoverresourceabundance		);}
			if(order ==19){::sprintf((char *)value.c_str(), "%f", m_minrecoverresourceabundance 		);}
			if(order ==20){::sprintf((char *)value.c_str(), "%f", m_maxrecoverresourceabundance 		);}
			if(order ==21){::sprintf((char *)value.c_str(), "%f", m_meanrecoverreserveabundance 		);}
			if(order ==22){::sprintf((char *)value.c_str(), "%f", m_minrecoverreserveabundance 		);}
			if(order ==23){::sprintf((char *)value.c_str(), "%f", m_maxrecoverreserveabundance 		);}
			if(order ==24){::sprintf((char *)value.c_str(), "%f", m_meanresource					);}
			if(order ==25){::sprintf((char *)value.c_str(), "%f", m_minresource 					);}
			if(order ==26){::sprintf((char *)value.c_str(), "%f", m_maxresource 					);}
			if(order ==27){::sprintf((char *)value.c_str(), "%f", m_meanreserve 					);}
			if(order ==28){::sprintf((char *)value.c_str(), "%f", m_minreserve 					);}
			if(order ==29){::sprintf((char *)value.c_str(), "%f", m_maxreserve 					);}
			if(order ==30){::sprintf((char *)value.c_str(), "%f", m_meanresourceabundance 		);}
			if(order ==31){::sprintf((char *)value.c_str(), "%f", m_minresourceabundance 			);}
			if(order ==32){::sprintf((char *)value.c_str(), "%f", m_maxresourceabundance 			);}
			if(order ==33){::sprintf((char *)value.c_str(), "%f", m_meanreserveabundance 			);}
			if(order ==34){::sprintf((char *)value.c_str(), "%f", m_minreserveabundance 			);}
			if(order ==35){::sprintf((char *)value.c_str(), "%f", m_maxreserveabundance 			);}
			if(order ==36){::sprintf((char *)value.c_str(), "%f", m_recoverablecoeffiecient 		);}
			if(order ==37){value=m_exploretype.c_str()					;}
			
		
		}
		////////////////////////////////////////////////////////////////////////////////
	
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_calibrationtype					= ::atoi(value.c_str());}
			if(order == 3){m_meanarea 							= ::atof(value.c_str());}
			if(order == 4){m_minarea 							= ::atof(value.c_str());}
			if(order == 5){m_maxarea 							= ::atof(value.c_str());}
			if(order == 6){m_meanrockvolume 					= ::atof(value.c_str());}
			if(order == 7){m_minrockvolume 					= ::atof(value.c_str());}
			if(order == 8){m_maxrockvolume 					= ::atof(value.c_str());}
			if(order == 9){m_meanthickness 					= ::atof(value.c_str());}
			if(order ==10){m_minthickness 						= ::atof(value.c_str());}
			if(order ==11){m_maxthickness 						= ::atof(value.c_str());}
			if(order ==12){m_meanrecoverresource 				= ::atof(value.c_str());}
			if(order ==13){m_minrecoverresource 				= ::atof(value.c_str());}
			if(order ==14){m_maxrecoverresource 					= ::atof(value.c_str());}
			if(order ==15){m_meanrecoverreserve 					= ::atof(value.c_str());}
			if(order ==16){m_minrecoverreserve 				= ::atof(value.c_str());}
			if(order ==17){m_maxrecoverreserve 					= ::atof(value.c_str());}
			if(order ==18){m_meanrecoverresourceabundance			= ::atof(value.c_str());}
			if(order ==19){m_minrecoverresourceabundance 		= ::atof(value.c_str());}
			if(order ==20){m_maxrecoverresourceabundance 		= ::atof(value.c_str());}
			if(order ==21){m_meanrecoverreserveabundance 			= ::atof(value.c_str());}
			if(order ==22){m_minrecoverreserveabundance 			= ::atof(value.c_str());}
			if(order ==23){m_maxrecoverreserveabundance 		= ::atof(value.c_str());}
			if(order ==24){m_meanresource			 		= ::atof(value.c_str());}
			if(order ==25){m_minresource 			 		= ::atof(value.c_str());}
			if(order ==26){m_maxresource 			 		= ::atof(value.c_str());}
			if(order ==27){m_meanreserve 			 		= ::atof(value.c_str());}
			if(order ==28){m_minreserve 				 		= ::atof(value.c_str());}
			if(order ==29){m_maxreserve 				 		= ::atof(value.c_str());}
			if(order ==30){m_meanresourceabundance 	 		= ::atof(value.c_str());}
			if(order ==31){m_minresourceabundance 	 		= ::atof(value.c_str());}
			if(order ==32){m_maxresourceabundance 	 		= ::atof(value.c_str());}
			if(order ==33){m_meanreserveabundance 	 		= ::atof(value.c_str());}
			if(order ==34){m_minreserveabundance 	 		= ::atof(value.c_str());}
			if(order ==35){m_maxreserveabundance 	 		= ::atof(value.c_str());}
			if(order ==36){m_recoverablecoeffiecient  		= ::atof(value.c_str());}
			if(order ==37){m_exploretype				 	= value.c_str();}
		}

};


struct OverSeaPrjRecord : public PropertyRecord
{
		
		string	m_prjname					;
		string	m_Prjcountry				;
		string	m_PrjBasin					;
		string	m_PrjFieldName				;
		string	m_PrjCondition				;
		long	m_PrjStartTime				;
		long	m_PrjStartProduceTime		;
		float	m_PrjRemainReserve			;
		float	m_PrjReserve				;
		string	m_PrjContraType				;
		string	m_remark					;
		/*!
		*
		**/
		OverSeaPrjRecord() 
		{
			m_prjname					="";
			m_Prjcountry				="";
			m_PrjBasin					="";
			m_PrjFieldName				="";
			m_PrjCondition				="";
			m_PrjStartTime				=0;
			m_PrjStartProduceTime		=0;
			m_PrjRemainReserve			=0;
			m_PrjReserve				=0;
			m_PrjContraType				="";
			m_remark					="";
			
			
			
			
			
										
		}

		/*!
		*
		**/
		const OverSeaPrjRecord &operator=(const OverSeaPrjRecord &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_prjname					=other.m_prjname					;	
			m_Prjcountry				=other.m_Prjcountry					;
			m_PrjBasin					=other.m_PrjBasin					;
			m_PrjFieldName				=other.m_PrjFieldName				;
			m_PrjCondition				=other.m_PrjCondition				;
			m_PrjStartTime				=other.m_PrjStartTime				;
			m_PrjStartProduceTime		=other.m_PrjStartProduceTime		;
			m_PrjRemainReserve			=other.m_PrjRemainReserve			;
			m_PrjReserve				=other.m_PrjReserve					;
			m_PrjContraType				=other.m_PrjContraType				;
			m_remark					=other.m_remark						;
		

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
			return 13;
		}

		bool IsColReadOnly(int order)
		{
			if(order==0 || order==1 )
			{
				return true;
			}
			return false;
		}

		void GetFldName(int order, string &value,int &type)//0 int ,1 float ,2 text
		{
			if(order == 0){value = "propertyid";			 type=0;}
			if(order == 1){value = "elementid";				 type=0;}
			if(order == 2){value = "prjname"				;type=2;}
			if(order == 3){value = "prjcountry"				;type=2;}
			if(order == 4){value = "prjbasin"				;type=2;}
			if(order == 5){value = "prjfieldname"			;type=2;}
			if(order == 6){value = "prjcondition"			;type=2;}
			if(order == 7){value = "prjstarttime"			;type=0;}
			if(order == 8){value = "prjstartproducetime"	;type=0;}
			if(order == 9){value = "prjremainreserve"		;type=1;}
			if(order ==10){value = "prjreserve"				;type=1;}
			if(order ==11){value = "prjcontratype"			;type=2;}
			if(order ==12){value = "remark"					;type=2;}
		

		}

		void GetFldValue(int order, string &value)
		{
			value = "";
			if(order == 0) {::sprintf((char *)value.c_str(), "%d", m_idx						);}
			if(order == 1) {::sprintf((char *)value.c_str(), "%d", m_elementIdx					);}
			if(order == 2) {value=m_prjname			;}
			if(order == 3) {value=m_Prjcountry		;}
			if(order == 4) {value=m_PrjBasin		;}
			if(order == 5) {value=m_PrjFieldName	;}
			if(order == 6) {value=m_PrjCondition	;}
			if(order == 7) {::sprintf((char *)value.c_str(), "%d", m_PrjStartTime				);}
			if(order == 8) {::sprintf((char *)value.c_str(), "%d", m_PrjStartProduceTime		);}
			if(order == 9) {::sprintf((char *)value.c_str(), "%f", m_PrjRemainReserve			);}
			if(order ==10) {::sprintf((char *)value.c_str(), "%f", m_PrjReserve					);}
			if(order ==11) {value=m_PrjContraType	;}
			if(order ==12) {value=m_remark			;}					   				
			
			
	
		}

		/*!
		*
		**/
		void SetFldValue(int order, string &value)
		{
			if(order == 0){m_idx = ::atoi(value.c_str());}
			if(order == 1){m_elementIdx = ::atoi(value.c_str());}
			if(order == 2){m_prjname		 = value	;}
			if(order == 3){m_Prjcountry		 = value	;}
			if(order == 4){m_PrjBasin		 = value	;}
			if(order == 5){m_PrjFieldName	 = value	;}
			if(order == 6){m_PrjCondition	 = value	;}
			if(order == 7){m_PrjStartTime		= ::atoi(value.c_str());}
			if(order == 8){m_PrjStartProduceTime= ::atoi(value.c_str());}
			if(order == 9){m_PrjRemainReserve	= ::atof(value.c_str());}
			if(order ==10){m_PrjReserve			= ::atof(value.c_str());}
			if(order ==11){m_PrjContraType = value	;}
			if(order ==12){m_remark = value	;}
			
			
			
		}
};


}
#endif

