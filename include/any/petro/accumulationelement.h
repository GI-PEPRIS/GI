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
#ifndef __ANYPETRO_ACCUMULATION_ELEMENT_H__
#define __ANYPETRO_ACCUMULATION_ELEMENT_H__

// refer to export etx
#include "anypetro.h"

// refer to its parent
#include "anypetroinfo.h"

// refer to accumulationassessor
#include "accumulationassessor.h"

#include "assessmentusermanager.h"
#include "anytrapmanagement.h"

#include "accumulationfactor.h"
// refer to anydb
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// refer to anymath
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

// namespace
namespace AnyPetro
{
	// Forward class
	class CAccumulationFactor;
	class CAccumulationPropertySet;

	/*!
	*
	**/
	class ANYPETRO_CLASS CAccumulationElement : public CAnyPetroInfo
	{
	public:
		/*!
		* deprecated enum, directly use resource kind specified by ref_assessment_resource_kind table
		**/
		enum ElementResourceType
		{
			ERT_Unknown	= -1,
			ERT_Oil,
			ERT_Gas,
			ERT_Total,
			ERT_Max,
		};

		/*!
		*
		**/
		enum ElementType
		{
			ET_Unknown = -1,
			ET_Region = 0,//区域
			ET_Basin = 1,//盆地
			ET_Accumulation_System = 2,//成藏体系
			ET_Accumulation_Play = 3,//亚成藏体系
			ET_Petroleum_System = 4,//含油气系统
			ET_Petroleum_Play = 5,//区带
			ET_Tectonic_Second = 6,//二级构造带
			ET_Tectonic_Play = 7,//三级构造带
			ET_Trap_Segment = 8,//层圈闭
			ET_Trap = 9,//圈闭
			ET_Play_Segment = 10,//区块
			ET_Prospect = 11,//评价项目
			ET_Prospect_Segment = 12,//评价单元
			ET_Field = 13,//油田
			ET_Pool = 14,//油气藏
			ET_Well = 15,//井
			ET_Play_Survey = 16,//工区
			ET_Shale_Basin = 17,//非常规盆地
			ET_Shale_FavZone = 18,//非常规有利区
			ET_Shale_Play = 19,//非常规区块
			ET_Shale_Target = 20,//非常规目标区
			ET_Shale_Well = 21,//非常规井
			ET_Block_Basin = 22,//区块 盆地
			ET_Block_FirstTectonic = 23,//区块  一级单元
			ET_Block_SecondTectonic = 24,//区块 二级单元
			ET_Block_ThirdTectonic = 25,//区块  三级单元
			ET_Block_Block = 26,//区块 区块
			ET_Block_Play = 27,//区块 区块
			ET_Block_Unit = 28,//区块 区块
			ET_Performance_Block = 29,//动态分析 区块
			ET_Performance_WellGroup = 30,//动态分析 井组
			ET_Performance_Well = 31,//动态分析 井
			ET_OverSea_Project = 32,//海外项目
			ET_Max = 33,
		};

		/*!
		*
		**/
		enum ElementActivityType
		{
			EAT_Unknown,
			EAT_Maturity,
			EAT_Maturity_Prospect,
			EAT_Fuzzy,
			EAT_Bayes,
			EAT_Predicator_Distribution,
			EAT_Predicator_Linear,
			EAT_Predicator_ExplorationTrend,
			EAT_Predicator_Volumetric,
			EAT_Predicator_NonParameter,
			EAT_Predicator_PoolRank,
			EAT_Predicator_Discovery,
			EAT_Predicator_MonteCarlo,
			EAT_Predicator_Analogue,
			EAT_Predicator_Spatial_Stochastic,
			EAT_Value_Prospect,
			EAT_NPV,
			EAT_ROV,
			EAT_Value_Trap,
			EAT_Well_EUR,//2015/8/18

			EAT_Max=200,
		};
		typedef std::map<unsigned short, CAccumulationAssessor*> ActivityMap;
		typedef ActivityMap::iterator act_itr;
		typedef ActivityMap::const_iterator act_citr;

		/*!
		*
		**/
		enum OperationMode
		{
			OM_Nothing = 0,
			OM_Delete = 1,
			OM_Add = 2,
			OM_Update = 4,
		};

		struct OverseaRiskResRecord
		{
			long   m_when		;
			double m_p10		;
			double m_p90		;
			double m_p50		;
			double m_pmean		;
			long m_num;
			long m_type;		//在经济结果m_ecoparas中对应资源类型
			CAnyDistributionStrategy *m_dis;

			OverseaRiskResRecord() 
			{
				m_when	=0;	
				m_p10	=0;	
				m_p90	=0;	
				m_p50	=0;	
				m_pmean	=0;
				m_dis	=0;
				m_num=0;
				m_type=0;
			}

			const OverseaRiskResRecord &operator=(const OverseaRiskResRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_when	=other.m_when	;
				m_p10	=other.m_p10	;
				m_p90	=other.m_p90	;
				m_p50	=other.m_p50	;
				m_pmean	=other.m_pmean	;
				m_num=other.m_num;
				m_type=other.m_type;
				if(m_dis)
				{
					delete m_dis;
					m_dis=0;
					m_dis	=other.m_dis	;
				}

				return *this;
			}
			void Reset()
			{
				m_when	=0;	
				m_p10	=0;	
				m_p90	=0;	
				m_p50	=0;	
				m_pmean	=0;
				m_num=0;
				m_type=0;
				if(m_dis)
				{
					delete m_dis;
					m_dis=0;
				}

			}

			string ValueToTheString()
			{
				char parameter[512] = "";
				::sprintf(parameter, "%d#%d#%d#%.3f#%.3f#%.3f#%.3f", m_when, m_num,m_type,m_p10, m_p50, m_p90,m_pmean);
				string str = parameter;
				return str;
			}

			void StringToTheValue(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");
				int count = curToken.Trim(parameter.c_str(), parameter.size());

				m_when = ::atoi(curToken.GetAt(0));
				m_num = ::atoi(curToken.GetAt(1));
				m_type = ::atoi(curToken.GetAt(2));
				m_p10 = ::atof(curToken.GetAt(3));
				m_p50 = ::atof(curToken.GetAt(4));
				m_p90 = ::atof(curToken.GetAt(5));
				m_pmean = ::atof(curToken.GetAt(6));
			}

		};

		struct OverseaDrillResRecord
		{
			int    m_when		;
			string m_welltype	;
			string m_wellkind	;
			int	   m_num		;
			double m_p10		;
			double m_p90		;
			double m_p50		;
			double m_Sesmic2D	;
			double m_Sesmic3D	;

			OverseaDrillResRecord() 
			{
				m_when		=0;
				m_welltype	="";	
				m_wellkind	="";	
				m_num		=0;	
				m_p10		=0;	
				m_p90		=0;
				m_p50		=0;
				m_Sesmic2D	=0;
				m_Sesmic3D	=0;
			}

			const OverseaDrillResRecord &operator=(const OverseaDrillResRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_when		=other.m_when				;
				m_welltype	=other.m_welltype	;
				m_wellkind	=other.m_wellkind	;
				m_num		=other.m_num		;
				m_p10		=other.m_p10		;
				m_p90		=other.m_p90		;
				m_p50		=other.m_p50		;
				m_Sesmic2D	=other.m_Sesmic2D	;
				m_Sesmic3D	=other.m_Sesmic3D	;
				return *this;
			}
			void Reset()
			{
				m_when		=0;
				m_welltype	="";
				m_wellkind	="";
				m_num		=0;	
				m_p10		=0;	
				m_p90		=0;
				m_p50		=0;
				m_Sesmic2D	=0;
				m_Sesmic3D	=0;
			}

			string ValueToTheString()
			{
				char parameter[512] = "";
				::sprintf(parameter, "%d#%.3f#%.3f#%.3f#%d#%.3f#%.3f#", m_when, m_p10, m_p50, m_p90,m_num,m_Sesmic2D,m_Sesmic3D);
				string str = parameter;
				if(m_welltype=="") m_welltype="采油井";
				if(m_wellkind=="") m_welltype="直井";
				str = str + m_welltype +"#"+m_wellkind;
				return str;
			}

			void StringToTheValue(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");
				int count = curToken.Trim(parameter.c_str(), parameter.size());

				m_when = ::atoi(curToken.GetAt(0));
				m_p10 = ::atof(curToken.GetAt(1));
				m_p50 = ::atof(curToken.GetAt(2));
				m_p90 = ::atof(curToken.GetAt(3));
				m_num = ::atoi(curToken.GetAt(4));
				m_Sesmic2D = ::atoi(curToken.GetAt(5));
				m_Sesmic3D = ::atoi(curToken.GetAt(6));
				m_welltype = curToken.GetAt(7);
				m_wellkind = curToken.GetAt(8);
			}


		};

		struct OverSeaDirectWellNums
		{
			int m_when		;
			int m_allnum	;
			int m_caiyounum	;
			int m_zushuinum	;

			OverSeaDirectWellNums()
			{
				m_when		=0;
				m_allnum	=0;
				m_caiyounum	=0;
				m_zushuinum	=0;
			}

			const OverSeaDirectWellNums &operator=(const OverSeaDirectWellNums &other)
			{
				m_when		=other.m_when		;
				m_allnum	=other.m_allnum		;
				m_caiyounum	=other.m_caiyounum	;
				m_zushuinum	=other.m_zushuinum	;
				return *this;
			}

			string ValueToTheString()
			{
				char parameter[512] = "";
				::sprintf(parameter, "%d#%d#%d#%d", m_when, m_allnum, m_caiyounum, m_zushuinum);
				string str = parameter;
				return str;
			}

			void StringToTheValue(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");
				int count = curToken.Trim(parameter.c_str(), parameter.size());

				m_when = ::atoi(curToken.GetAt(0));
				m_allnum = ::atof(curToken.GetAt(1));
				m_caiyounum = ::atof(curToken.GetAt(2));
				m_zushuinum = ::atof(curToken.GetAt(3));
			}

		};

		struct OverseaRiskRecord
		{
			int m_restype;//0 oil 1 gas 
			OverseaRiskResRecord m_geores;//地质定量结果

			double m_welleur;//井位模拟EUR
			double m_zcb;//注采比
			std::vector<std::vector<int>> m_allwellnums;//钻井工作量 p10 p50 p90 pmean
			std::vector<std::vector<OverseaRiskResRecord>> m_oildevproductions; // 油p10 p50 p90 pmean
			std::vector<std::vector<OverseaRiskResRecord>> m_gasdevproductions; // 气p10 p50 p90 pmean
			std::vector<std::vector<OverSeaDirectWellNums>> m_wellnums;//记录直接定义的井型
			std::vector<std::vector<OverseaDrillResRecord>> m_Geowells;//记录地质井型

			std::vector<std::vector<OverseaRiskResRecord>>  m_landinvest ;//陆地投资
			std::vector<std::vector<OverseaRiskResRecord>>  m_marinvest  ; //海工
			std::vector<std::vector<OverseaDrillResRecord>> m_drillinvest;//钻井投资

			std::vector<std::vector<OverseaRiskResRecord>> m_ecoparas;//经济财税 成本等经济评价相关

			OverseaRiskRecord() 
			{
				m_restype=0;
				m_geores.Reset();
				m_allwellnums.clear();
				m_oildevproductions.clear();
				m_gasdevproductions.clear();
				m_welleur=0;
				m_landinvest .clear();
				m_marinvest  .clear();
				m_drillinvest.clear();
				m_zcb=0;
				m_ecoparas.clear();
				m_Geowells.clear();
			}

			const OverseaRiskRecord &operator=(const OverseaRiskRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_geores = other.m_geores;
				m_welleur= other.m_welleur;
				m_restype= other.m_restype;
				m_zcb	 = other.m_zcb;

				m_allwellnums.clear();
				for(int i=0;i<other.m_allwellnums.size();i++)
				{
					std::vector<int> onewellnum;
					for(int j=0;j<other.m_allwellnums[i].size();j++)
					{
						onewellnum.push_back(other.m_allwellnums[i][j]);
					}
					m_allwellnums.push_back(onewellnum);
				}

				m_oildevproductions.clear();
				for(int i=0;i<other.m_oildevproductions.size();i++)
				{
					std::vector<OverseaRiskResRecord> oneoildevproductions;
					for(int j=0;j<other.m_oildevproductions[i].size();j++)
					{
						oneoildevproductions.push_back(other.m_oildevproductions[i][j]);
					}
					m_oildevproductions.push_back(oneoildevproductions);
				}

				m_gasdevproductions.clear();
				for(int i=0;i<other.m_gasdevproductions.size();i++)
				{
					std::vector<OverseaRiskResRecord> onegasdevproductions;
					for(int j=0;j<other.m_gasdevproductions[i].size();j++)
					{
						onegasdevproductions.push_back(other.m_gasdevproductions[i][j]);
					}
					m_gasdevproductions.push_back(onegasdevproductions);
				}
				//
				m_landinvest.clear();
				for(int i=0;i<other.m_landinvest.size();i++)
				{
					std::vector<OverseaRiskResRecord> onelandinvest;
					for(int j=0;j<other.m_landinvest[i].size();j++)
					{
						onelandinvest.push_back(other.m_landinvest[i][j]);
					}
					m_landinvest.push_back(onelandinvest);
				}

				m_landinvest.clear();
				for(int i=0;i<other.m_landinvest.size();i++)
				{
					std::vector<OverseaRiskResRecord> onelandinvest;
					for(int j=0;j<other.m_landinvest[i].size();j++)
					{
						onelandinvest.push_back(other.m_landinvest[i][j]);
					}
					m_landinvest.push_back(onelandinvest);
				}

				m_marinvest.clear();
				for(int i=0;i<other.m_marinvest.size();i++)
				{
					std::vector<OverseaRiskResRecord> onemarinvest;
					for(int j=0;j<other.m_marinvest[i].size();j++)
					{
						onemarinvest.push_back(other.m_marinvest[i][j]);
					}
					m_marinvest.push_back(onemarinvest);
				}

				m_drillinvest.clear();
				int numdrillinvest = other.m_drillinvest.size();
				for(int i=0;i<numdrillinvest;i++)
				{
					std::vector<OverseaDrillResRecord> onedrillinvest1;
					m_drillinvest.push_back(onedrillinvest1);
				}
				for(int i=0;i<other.m_drillinvest.size();i++)
				{
					for(int j=0;j<other.m_drillinvest[i].size();j++)
					{
						m_drillinvest[i].push_back(other.m_drillinvest[i][j]);
					}
				}
				
				m_ecoparas.clear();
				for(int i=0;i<other.m_ecoparas.size();i++)
				{
					std::vector<OverseaRiskResRecord> oneeco;
					for(int j=0;j<other.m_ecoparas[i].size();j++)
					{
						oneeco.push_back(other.m_ecoparas[i][j]);
					}
					m_ecoparas.push_back(oneeco);
				}

				m_wellnums.clear();
				for(int i=0;i<other.m_wellnums.size();i++)
				{
					std::vector<OverSeaDirectWellNums> oneeco;
					for(int j=0;j<other.m_wellnums[i].size();j++)
					{
						oneeco.push_back(other.m_wellnums[i][j]);
					}
					m_wellnums.push_back(oneeco);
				}

				m_Geowells.clear();
				for(int i=0;i<other.m_Geowells.size();i++)
				{
					std::vector<OverseaDrillResRecord> oneeco;
					for(int j=0;j<other.m_Geowells[i].size();j++)
					{
						oneeco.push_back(other.m_Geowells[i][j]);
					}
					m_Geowells.push_back(oneeco);
				}

				return *this;
			}
			void ResetAll()
			{
				m_geores.Reset();
				m_allwellnums.clear();
				m_oildevproductions.clear();
				m_gasdevproductions.clear();
				m_welleur=0;
				m_restype=0;
				m_landinvest .clear();
				m_marinvest  .clear();
				m_drillinvest.clear();
				m_zcb=0;
				m_ecoparas.clear();
				m_wellnums.clear();
				m_Geowells.clear();
			}
			void ResetGeoRes()
			{
				m_geores.Reset();

			}
			void Resetwellnums()
			{
				m_allwellnums.clear();

			}
			void Resetwelleur()
			{
				m_welleur=0;

			}
			void Resetdevproductions()
			{
				m_allwellnums.clear();
				m_oildevproductions.clear();
				m_gasdevproductions.clear();
			}
			void ResetPriInvest()
			{
				m_landinvest .clear();
				m_marinvest  .clear();
				m_drillinvest.clear();
			}
			void ResetEco()
			{
				m_ecoparas.clear();
			}

			void CopyFromOtherDrillRecords(std::vector<std::vector<OverseaDrillResRecord>> &drillinvest)
			{
				m_drillinvest.clear();
				int num = drillinvest.size();
				for(int i=0;i<num;i++)
				{
					std::vector<OverseaDrillResRecord> onedrillinvest1;
					m_drillinvest.push_back(onedrillinvest1);
				}
				for(int i=0;i<drillinvest.size();i++)
				{
					for(int j=0;j<drillinvest[i].size();j++)
					{
						m_drillinvest[i].push_back(drillinvest[i][j]);
					}
				}
			}
			void CopyToOtherDrillRecords(std::vector<std::vector<OverseaDrillResRecord>> &drillinvest)
			{
				drillinvest.clear();
				int num = m_drillinvest.size();
				for(int i=0;i<num;i++)
				{
					std::vector<OverseaDrillResRecord> onedrillinvest1;
					drillinvest.push_back(onedrillinvest1);
				}
				for(int i=0;i<m_drillinvest.size();i++)
				{
					for(int j=0;j<m_drillinvest[i].size();j++)
					{
						drillinvest[i].push_back(m_drillinvest[i][j]);
					}
				}
			}

			void CopyFromOtherEcoParasRecords(std::vector<std::vector<OverseaRiskResRecord>> &ecoparas)
			{
				m_ecoparas.clear();
				for(int i=0;i<ecoparas.size();i++)
				{
					std::vector<OverseaRiskResRecord> oneeco;
					for(int j=0;j<ecoparas[i].size();j++)
					{
						oneeco.push_back(ecoparas[i][j]);
					}
					m_ecoparas.push_back(oneeco);
				}
			}

			void CaldrillinvestbyYear(int sel ,int year,int &num,double &p10,double &p50,double &p90)//sel 0: p10 1:p50 2: p90
			{
				p10=0;p90=0;p50=0;num=0;
				if(m_drillinvest.size()<(sel+1))
				{
					return;
				}
				std::vector<OverseaDrillResRecord> &DrillResRecords = m_drillinvest[sel];
				for(int i=0;i<DrillResRecords.size();i++)
				{
					if(DrillResRecords[i].m_when==year )
					{
						num = num + DrillResRecords[i].m_num ;
						p10 = p10 + DrillResRecords[i].m_p10 ;
						p50 = p50 + DrillResRecords[i].m_p50 ;
						p90 = p90 + DrillResRecords[i].m_p90 ;
					}
				}
			}
			int GetJCfromInvest(std::vector<OverseaRiskResRecord> &invest)
			{
				std::vector<long> whens;
				for(int i=0;i<invest.size();i++)
				{
					whens.push_back(invest[i].m_when);
				}
				int jc=0;
				for(int i=0;i<whens.size();i++)
				{
					if(whens[i]<jc)
					{
						jc=whens[i];
					}
				}
				jc = jc*-1+1;
				return jc;
			}

			int GetGeoWellYearsfromDrills(std::vector<OverseaDrillResRecord> &geowell)
			{
				std::vector<int> days;
				for(int i=0;i<geowell.size();i++)
				{
					int day = geowell[i].m_when;
					bool isexist=false;
					for(int j=0;j<days.size();j++)
					{
						if(days[j]==day)
						{
							isexist=true;
						}
					}
					if(!isexist)
					{
						days.push_back(day);
					}
				}
				return days.size();
			}

			int GetValidInvestNum(std::vector<OverseaRiskResRecord> &invest)
			{
				int g=0;
				for(int i=0;i<invest.size();i++)
				{
					if(invest[i].m_p90<=0 && invest[i].m_p50<=0 && invest[i].m_p10<=0)
					{
						continue;
					}
					g++;
				}
				
				return g;
			}
			//std::vector<std::vector<int>> m_allwellnums;//钻井工作量 p10 p50 p90 pmean
			//std::vector<std::vector<OverseaRiskResRecord>> m_oildevproductions; // 油p10 p50 p90 pmean
			void AddMultiwellnums(std::vector<std::vector<int> > &oneallwellnums,std::vector<std::vector<std::vector<int> > >&allallwellnums)
			{
				oneallwellnums.clear();
				std::vector<int> p10,p90,p50,pmean;
				for(int i=0;i<allallwellnums.size();i++)
				{
					std::vector<std::vector<int>> &allwellnums = allallwellnums[i];
					std::vector<int> &tp10=allwellnums[0];
					std::vector<int> &tp50=allwellnums[1];
					std::vector<int> &tp90=allwellnums[2];
					std::vector<int> &tpmean=allwellnums[3];
					//p10
					for(int j=0;j<tp10.size();j++)
					{
						if(p10.size()<=j)
						{
							p10.push_back(tp10[j]);
						}
						else
						{
							p10[j] = p10[j]+tp10[j];
						}
					}
					//p50
					for(int j=0;j<tp50.size();j++)
					{
						if(p50.size()<=j)
						{
							p50.push_back(tp50[j]);
						}
						else
						{
							p50[j] = p50[j]+tp50[j];
						}
					}
					//p90
					for(int j=0;j<tp90.size();j++)
					{
						if(p90.size()<=j)
						{
							p90.push_back(tp90[j]);
						}
						else
						{
							p90[j] = p90[j]+tp90[j];
						}
					}
					//pmean
					for(int j=0;j<tpmean.size();j++)
					{
						if(pmean.size()<=j)
						{
							pmean.push_back(tpmean[j]);
						}
						else
						{
							pmean[j] = pmean[j]+tpmean[j];
						}
					}
				}
				if(p10.size()){oneallwellnums.push_back(p10);}else{oneallwellnums.clear();return;}
				if(p90.size()){oneallwellnums.push_back(p50);}else{oneallwellnums.clear();return;}
				if(p50.size()){oneallwellnums.push_back(p90);}else{oneallwellnums.clear();return;}
				if(pmean.size()){oneallwellnums.push_back(pmean);}else{oneallwellnums.clear();return;}

			}
			void AddMultiproductions(std::vector<std::vector<OverseaRiskResRecord>> &onedevproductions,std::vector<std::vector<std::vector<OverseaRiskResRecord>>> &allalldevproductions)
			{
				onedevproductions.clear();
				std::vector<OverseaRiskResRecord> p10,p90,p50,pmean;
				for(int i=0;i<allalldevproductions.size();i++)
				{
					std::vector<std::vector<OverseaRiskResRecord>> &alldevproductions = allalldevproductions[i];
					std::vector<OverseaRiskResRecord> &tp10=alldevproductions[0];
					std::vector<OverseaRiskResRecord> &tp50=alldevproductions[1];
					std::vector<OverseaRiskResRecord> &tp90=alldevproductions[2];
					std::vector<OverseaRiskResRecord> &tpmean=alldevproductions[3];
					//p10
					for(int j=0;j<tp10.size();j++)
					{
						if(p10.size()<=j)
						{
							p10.push_back(tp10[j]);
						}
						else
						{
							p10[j].m_when	=tp10[j].m_when	;
							p10[j].m_p10	=tp10[j].m_p10	+p10[j].m_p10	;
							p10[j].m_p90	=tp10[j].m_p90	+p10[j].m_p90	;
							p10[j].m_p50	=tp10[j].m_p50	+p10[j].m_p50	;
							p10[j].m_pmean	=tp10[j].m_pmean+p10[j].m_pmean	;
							p10[j].m_num    =tp10[j].m_num  +p10[j].m_num	;
							p10[j].m_type   =tp10[j].m_type ;
						}
					}
					//p50
					for(int j=0;j<tp50.size();j++)
					{
						if(p50.size()<=j)
						{
							p50.push_back(tp50[j]);
						}
						else
						{
							p50[j].m_when	=tp50[j].m_when	;
							p50[j].m_p10	=tp50[j].m_p10	+p50[j].m_p10	;
							p50[j].m_p90	=tp50[j].m_p90	+p50[j].m_p90	;
							p50[j].m_p50	=tp50[j].m_p50	+p50[j].m_p50	;
							p50[j].m_pmean	=tp50[j].m_pmean+p50[j].m_pmean	;
							p50[j].m_num    =tp50[j].m_num  +p50[j].m_num	;
							p50[j].m_type   =tp50[j].m_type ;
						}
					}
					//p90
					for(int j=0;j<tp90.size();j++)
					{
						if(p90.size()<=j)
						{
							p90.push_back(tp90[j]);
						}
						else
						{
							p90[j].m_when	=tp90[j].m_when	;
							p90[j].m_p10	=tp90[j].m_p10	+p90[j].m_p10	;
							p90[j].m_p90	=tp90[j].m_p90	+p90[j].m_p90	;
							p90[j].m_p50	=tp90[j].m_p50	+p90[j].m_p50	;
							p90[j].m_pmean	=tp90[j].m_pmean+p90[j].m_pmean	;
							p90[j].m_num    =tp90[j].m_num  +p90[j].m_num	;
							p90[j].m_type   =tp90[j].m_type ;
						}
					}
					//pmean
					for(int j=0;j<tpmean.size();j++)
					{
						if(pmean.size()<=j)
						{
							pmean.push_back(tpmean[j]);
						}
						else
						{
							pmean[j].m_when	=tpmean[j].m_when	;
							pmean[j].m_p10	=tpmean[j].m_p10	+pmean[j].m_p10	;
							pmean[j].m_p90	=tpmean[j].m_p90	+pmean[j].m_p90	;
							pmean[j].m_p50	=tpmean[j].m_p50	+pmean[j].m_p50	;
							pmean[j].m_pmean=tpmean[j].m_pmean  +pmean[j].m_pmean	;
							pmean[j].m_num  =tpmean[j].m_num    +pmean[j].m_num	;
							pmean[j].m_type =tpmean[j].m_type ;
						}
					}
				}
				if(p10.size()){onedevproductions.push_back(p10);}else{onedevproductions.clear();return;}
				if(p90.size()){onedevproductions.push_back(p50);}else{onedevproductions.clear();return;}
				if(p50.size()){onedevproductions.push_back(p90);}else{onedevproductions.clear();return;}
				if(pmean.size()){onedevproductions.push_back(pmean);}else{onedevproductions.clear();return;}
			}
		};

		/*!
		* Note:
		* Correspondence with the declaration of its table
		**/
		struct ElementRecord
		{
			// basic info
			long m_idx;
			string m_whodo;
			long m_managementphase;
			long m_parentidx;
			string m_name;
			unsigned long m_type;
			long m_found;
			// whether as a calibration area
			bool m_calibration;
			float m_weight;
			// kinds of pool size
			double m_resourceMin;		// resource base minimum: smallest accumulation of eventual interest
			double m_largeMax;			// large field maximum: size for which no future discoveries larger than this max are expected in the target area
			double m_largeMin;			// large filed minimum: size for which no future discoveries larger than this min are expected in calibration area
			double m_screening;			// economic minimum: economic Hydrocarbons

			// calibration and target analogue
			// ...
			// accumulation type
			string m_resourceName;
			double m_resource;	// resource calculation result
			double m_resource10;
			double m_resource90;
			double m_resource00;
			double m_ppolitic;
			double m_recovery;								// recoverable factor

			// kinds of probability
			double m_pmaturity;								// margin risk
			double m_pshare;									// shared/conditional risk
			double m_pbusiness;
			double m_peconomic;
			double m_pengineering;							// as final evalution factor or as engineering factor

			double m_irr;											// economic standard
			double m_npv;										// economic standard	
			double m_emv;										 //
			double m_economic;								 // as final evaluation factor 
			double m_strategy;
			bool m_isTrapCandidate;
			bool m_isWellCandidate;
			double m_trapR;
			double m_wellR;
			long m_traprank;
			long m_wellrank;
			string m_oilfieldname;
			double m_npv10;
			double m_npv90;
			double m_npv00;
			double m_explrinvest;
			double m_devlpinvest;
			long m_riskid;
			long m_resourceid;
			long m_economicid;
			long m_selectionid;
			double m_p2dseismic;//block 版用来记录勘探程度取值                 海外版借用
			double m_p3dseismic;//block 版用来记录勘探程度						海外版借用
			double m_projectarea;///block 版 借用该字段存放区块价值评价模板结果 海外版借用
			double m_costpertone;
			long m_discovertype;
			long m_optimyear;
			long m_optimnum;
			double m_pmaturityenv;
			double m_pmaturityeco;

			//海外项目评价
			OverseaRiskRecord m_overseariskrecord;//存放海外评价版相关的评价数据和结果
			long m_startdate;//项目开始日期
			long m_enddata  ;//项目结束日期
			/*!
			*
			**/
			ElementRecord() : m_idx(0), m_whodo(""), m_managementphase(CAnyTrapManagement::TEP_Preliminary | CAnyTrapManagement::TRA_Preliminary_Found), m_parentidx(0), m_name(""), m_found(0), m_type(0), m_weight(0.0), m_calibration(0), m_resourceName(""), \
				m_resourceMin(0.), m_largeMax(0.), m_largeMin(0.), m_screening(0.), \
				m_resource(0.), m_resource10(0.), m_resource90(0.), m_resource00(0.), m_ppolitic (0.), m_recovery(0.), m_pmaturity(0.), m_pshare(1.), m_pbusiness(0.), m_peconomic(0.), m_pengineering(0.), \
				m_irr(0.), m_npv(0.), m_emv(0.), m_economic(0.), m_strategy(0.), m_isTrapCandidate(0), m_isWellCandidate(0), \
				m_trapR(0.), m_wellR(0.), m_traprank(0), m_wellrank(0), m_oilfieldname(""), m_npv10(0.), m_npv90(0.), m_npv00(0.), \
				m_explrinvest(0.), m_devlpinvest(0.), m_riskid(0), m_resourceid(0), m_economicid(0), m_selectionid(0), m_p2dseismic(0.), \
				m_p3dseismic(0.), m_projectarea(0.), m_costpertone(0.), m_discovertype(0),m_optimyear(0),m_optimnum(0),m_pmaturityenv(0),m_pmaturityeco(0),m_startdate(0),m_enddata(0)
			{
				m_overseariskrecord.ResetAll();
			}

			/*!
			*
			**/
			const ElementRecord &operator=(const ElementRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx = other.m_idx;
				m_whodo = other.m_whodo;
				m_managementphase = other.m_managementphase;
				m_parentidx = other.m_parentidx;
				m_name = other.m_name;
				m_type = other.m_type;
				m_found = other.m_found;
				m_weight = other.m_weight;
				m_calibration = other.m_calibration;

				// kinds of pool size
				m_resourceMin = other.m_resourceMin;	
				m_largeMax = other.m_largeMax;
				m_largeMin = other.m_largeMin;	
				m_screening = other.m_screening;	

				// calibration and target analogue
				// ...
				// accumulation type
				m_resourceName = other.m_resourceName;
				m_resource = other.m_resource;								// resource calculation result
				m_resource10 = other.m_resource10;
				m_resource90 = other.m_resource90;
				m_resource00 = other.m_resource00;
				m_ppolitic = other.m_ppolitic;
				m_recovery = other.m_recovery;								// recoverable factor

				// kinds of probability
				m_pmaturity = other.m_pmaturity;								// margin risk
				m_pshare = other.m_pshare;									// shared/conditional risk
				m_pbusiness = other.m_pbusiness;
				m_peconomic = other.m_peconomic;
				m_pengineering = other.m_pengineering;							// as final evalution factor or as engineering factor

				m_irr = other.m_irr;											// economic standard
				m_npv = other.m_npv;										// economic standard	
				m_emv = other.m_emv;										 //
				m_economic = other.m_economic;								 // as final evaluation factor 
				m_strategy = other.m_strategy;
				m_isTrapCandidate = other.m_isTrapCandidate;
				m_isWellCandidate = other.m_isWellCandidate;
				m_trapR = other.m_trapR;
				m_wellR = other.m_wellR;
				m_traprank = other.m_traprank;
				m_wellrank = other.m_wellrank;
				m_oilfieldname = other.m_oilfieldname;
				m_npv10 = other.m_npv10;
				m_npv90 = other.m_npv90;
				m_npv00 = other.m_npv00;
				m_explrinvest = other.m_explrinvest;
				m_devlpinvest = other.m_devlpinvest;
				m_riskid = other.m_riskid;
				m_resourceid = other.m_resourceid;
				m_economicid = other.m_economicid;
				m_selectionid = other.m_selectionid;
				m_p2dseismic = other.m_p2dseismic;
				m_p3dseismic = other.m_p3dseismic;
				m_projectarea = other.m_projectarea;
				m_costpertone = other.m_costpertone;
				m_discovertype = other.m_discovertype;
				m_optimyear = other.m_optimyear;
				m_optimnum = other.m_optimnum;
				m_pmaturityenv = other.m_pmaturityenv;
				m_pmaturityeco = other.m_pmaturityeco;

				m_overseariskrecord = other.m_overseariskrecord;
				return *this;
			}
			static bool CompareElementIdx(const ElementRecord &a, const ElementRecord &b)
			{
				return a.m_idx < b.m_idx;
			}
		};

		// To construct vector feature space
		typedef std::vector<CAccumulationFactor *> FactorVector;
		typedef FactorVector::iterator factor_itr;
		typedef FactorVector::const_iterator factor_citr;

		// property map
		typedef std::map<int, CAccumulationPropertySet*> PropertyMap;
		typedef PropertyMap::iterator prop_itr;
		typedef PropertyMap::const_iterator prop_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAccumulationElement(CAccumulationElement *parent);

		/*!
		*
		**/
		~CAccumulationElement();

	public:
		//
		// inheritance interface
		//
		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);

		/*!
		*
		**/
		void SetType(unsigned long type)
		{
			m_record.m_type = m_type = type;
		}

		/*!
		*
		**/
		const string &GetName() const
		{
			return m_name;
		}

		/*!
		*
		**/
		void SetName(const string &name)
		{
			m_name = m_record.m_name = name;
		}

		/*!
		*
		**/
		void SetMaturity(double maturity)
		{
			m_record.m_pmaturity = maturity;
		}

		/*pc*/
		/*!
		*
		**/
		void SetEngineering(double engineering)
		{
			m_record.m_pengineering = engineering;
		}
		/*pc-end*/

		/*!
		*
		**/
		long GetParentidx()
		{
			return m_record.m_parentidx;
		}
		
		/*!
		*
		**/
		const ElementRecord &GetRecord() const
		{
			return m_record;
		}

		/*!
		*
		**/
		void SetRecord(const ElementRecord &other)
		{
			m_record = other;
		}

		/*!
		*
		**/
		void SetIdx(unsigned long idx)
		{
			CAnyObject::SetIdx(idx);
			m_record.m_idx = idx;
		}

		//
		// property-related interface
		//
		/*!
		*
		**/
		CAccumulationPropertySet *GetPropertySet(unsigned int type);


		/*!
		通过类型删除属性集合中的某个属性集
		**/
		void DelPropertySetByType(unsigned int type);

		void DelAllPropertySet();
		//
		// factor-related interface
		//
		/*!
		* Only add primitve factor not consider composite factor
		**/
		void AddFactor(CAccumulationFactor *factor);

		/*!
		*
		**/
		int GetFactorCount() const;

		/*!
		*
		**/
		const CAccumulationFactor *GetFactor(int index);
		
	

		/*!
		*
		**/
		void GetSiblingFactors(CAccumulationElement::FactorVector &factors, int level,int templateid=-1) const;

		/*!
		* let outside has a chance to change
		**/
		CAccumulationFactor *FindFactor(long idx);

		/*!
		*
		**/
		void DeleteFactors(long templateIdx, bool isCommited = false);

		/*!
		*
		**/
		void DeleteProperties(bool isCommited = false);

		//
		// activity interface
		//
		/*!
		*
		**/
		CAccumulationAssessor *GetActivity(unsigned short type);

		/*!
		* to decouple DLL dependence between this package and anothre
		**/
		CAccumulationAssessor *SetActivity(unsigned short type, CAccumulationAssessor *activity);

		/*!
		*
		**/
		unsigned int CommitActivity(unsigned short type);

		/*!
		*
		**/
		unsigned int CommitActivity(CAccumulationAssessor::ActivityPracticeRecord &practice);

		/*!
		*
		**/
		unsigned int CommitActivity(CAccumulationAssessor::ActivityRiskRecord &risk);

		/*!
		*
		**/
		void DeleteActivities(bool isCommited = false);

		/*!
		* deprecated function: which should be encasulated by an activity class
		**/
		float GetMaturityRisk(long templateid);

		/*!
		*
		**/
		float GetMariginalRisk(long templateid);

		/*!
		*
		**/
		void GetPractices(CAccumulationAssessor::PracticeVector &practices);
		/*!
		*
		**/
		void DeleteDummyChildren();
		//
		// persistence issue
		//
		/*!
		*
		**/
		static CAccumulationElement *Load(long idx = 0);

		/*!
		*
		**/
		static bool CommitElementRecord(ElementRecord* elementrecord);

		/*!
		*2015/11/16: define CAnyAccessor outside the method 
		**/
		static bool CommitElementRecord(CAnyAccessor &accessor, ElementRecord* elementrecord);

		/*!
		*
		**/
		static double GetWellDelphiScore(int elementIdx, std::string field);

		/*!
		*
		**/
		void DeleteAllElementActivities(CAnyAccessor &accessor, string whodo = "");

		/*!
		*
		**/
		void DeleteAllElementActivitiesPractice(CAnyAccessor &accessor, string whodo = "");

		/*!
		*
		**/
		void DeleteAllElementInfoXXData(CAnyAccessor &accessor);
		
		/*!
		*
		**/
		static void DeleteOldPractice(CAnyAccessor &accessor, int deletetype, int elementid, int activityid, std::vector<string> whodos);

		/*!
		*
		**/
		bool HasRelatedData();
		
		/*!
		*
		**/
		static void GetInfoXXTableNames(std::vector<string> &infoxxnames);

		/*!
		*
		**/
		static void GetActivityXXTableNames(std::vector<string> &activityxxnames);
		
		/*!
		*
		**/
		static void GetNoCopyXXTableNames(std::vector<string> &nocopyxxnames);

		/*!
		*
		**/
		static void GetFactors(CAccumulationElement *curElement);
		
		/*!
		*
		**/
		static void GetFactorsNODB(CAccumulationElement *curElement,std::map<int,CAccumulationFactor::FactorVector>& factorMap);
		
		/*!
		*
		**/
		static CAccumulationElement*  GetRootElement();

		/*!
		*
		**/
		static CAccumulationElement* GetElementByIdx(long idx,CAccumulationElement *root);

		/*!
		*
		**/
		static void GetAllElements(std::vector<CAccumulationElement *> &elements,CAccumulationElement *root);

		/*!
		*
		**/
		static CAccumulationElement* GetElementByName(string name,CAccumulationElement *root);
		

		static CAccumulationElement* GetElementByNameAndParentName(string &name,string &parentname,CAccumulationElement *root);
		/*!
		*
		**/
		static  void GetElementByType(std::vector<CAccumulationElement *> &elements,CAccumulationElement *root,int type);

		/*!
		*
		**/
		static  void GetChildElementByParent(std::vector<CAccumulationElement *> &elements,CAccumulationElement *parent);

		/*!
		*
		**/
		static void GetAllChildElementByParent(std::vector<CAccumulationElement *> &elements,CAccumulationElement *element);

		/*!
		*
		**/
		static void SetTrapElementsStep( long idx,string &name );

		/*!
		*
		**/
		static void GetTrapElementsStep( long idx,string &name );

		/*!
		*
		**/
		static void SetTrapElementsStepByNum( long idx,int num );

		/*!
		*
		**/
		static int GetTrapElementsStep( long idx);

		/*!
		*
		**/
		static CAccumulationElement* GetRandomElement();

		/*!
		*
		**/
		static int GetTableTypeByTableName(string &name);
		
		
		
		/*!
		*
		**/
		static void GetRelatedLayers(int elementid, std::vector<string> &names, std::vector<string> &sources, std::vector<int> &types, \
			std::vector<std::vector<int> > &versions, std::vector<std::vector<string> > &whodos, std::vector<std::vector<string> > &whendos, \
			std::vector<std::vector<bool> > &iscurvers);
		
		/*!
		*
		**/
		static void GetCurRecord(CAnyAccessor &accessor, CAccumulationElement *element, CAccumulationElement *parent);
				
		/*!
		*
		**/
		static std::string GetTypeName(int type);


		static void GetInfoXXTableNamesByType(int type, std::vector<string> &infoxxnames );

		static void GetTableDispNameByTableName( string &name ,string &dispname);

		static bool IsSingElementTypeRecord(string &name,int type=-1);

		static void GetCreatenewTypeName( int type ,int version,std::vector<long> &newtype);
		static void GetTableTypeByElementType( int type ,std::vector<long> &newtype);

		void EraserExistActivity(int type);

		char* SerializeVec( int &len,std::vector<std::vector<string> >& vecdata );
		void SaveStringVectortoBlobData( std::vector<std::vector<string> > &vecdata ,long nID );
		long QuickSavePractice( long elementid ,long activitytype);
		long QuickLoadPracticeBlobData( long elementid ,long activitytype,std::vector<std::vector<string> > &vecdata);
		void RestoreVec(char* data,std::vector<std::vector<string> >& vecdata );
	private:
		//
		//
		//
		/*!
		*
		**/
		bool DoCommitComponents(bool isDelete);

		/*!
		*
		**/
		void DoGetFactors(CAccumulationFactor *curFactor, CAccumulationElement::FactorVector &factors, int level,int templateid=-1) const;

		//
		//
		//
		/*!
		*
		**/
		static CAccumulationElement *DoLoad(CAnyAccessor &accessor, CAccumulationElement *parent = 0);

		/*!
		*
		**/
		static void DoLoadFromCache(std::map<int,std::vector<ElementRecord>> &map, CAccumulationElement *parent = 0);

		/*!
		*
		**/
		static void DoLoadFromCacheWithElelmentVector(std::map<int,std::vector<ElementRecord>> &map, CAccumulationElement *parent ,std::vector<CAccumulationElement*>& eleVec);

		
		/*!
		*
		**/
		static void GetAllElementRecords(std::vector<ElementRecord> &elements);

		/*!
		*
		**/
		static void GetChildrenRecord(CAccumulationElement *parent);

		/*!
		*
		**/
		static bool CompareFactorIdx(const CAccumulationFactor *first, const CAccumulationFactor *second);



		/*!
		*
		**/
		static void LoadElementAndFactor(CAccumulationElement *dummy);
	private:
		// Factors
		FactorVector m_factors;
		std::set<int> m_factorSet;

		// its weight
		ElementRecord m_record;

		// property map
		PropertyMap m_properties;

		// activity map
		ActivityMap m_activities;

	public:
		// persistence table
		static string m_elementTable;
		static string m_elementTableEvaluation;
		static string m_elementTableView;

		// dummy object
		static CAccumulationElement *m_rootobject;
		static int m_practicelimits;
	};
}

#endif
