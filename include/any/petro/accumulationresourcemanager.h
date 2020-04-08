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
#ifndef __ANYPETRO_ACCUMULATION_RESOURCE_MANAGER_H__
#define __ANYPETRO_ACCUMULATION_RESOURCE_MANAGER_H__

// for EXPORT & IMPORT
#include "anypetro.h"
#include "accumulationassessor.h"
// for stl
#include "any/base/anystl.h"

// for accessor
#include "any/db/anyaccessor.h"
using namespace AnyDB;
#include "any/map/anyviewhook.h"
using namespace AnyMap;
#include "any/math/anysequentialgausssimulator.h"
using namespace AnyMath;
//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CAccumulationResourceManager
	{
	public:
		
		enum ResourceCategory//资源性质
		{
			RC_Domestic,//国内
			RC_SPE,//SPE
			RC_Sinopec_Trap_Business, // 中石化 对应三参数定义
		};
		
		enum VolumeStatCommitPhase//三参数阶段定义
		{
			VSCP_Unknown = 0,
			VSCP_Already_Exist,//已有预测储量
			VSCP_After_Recognize,//重新认识后的预测储量
			VSCP_After_Prospect_Applied,//预计升级控制储量
		};
		
		/*!
		* 圈闭勘探阶段类型
		**/
		enum TrapExplorationPhaseType
		{
			//TET_Unknown = 0,
			TET_Resource_Applied ,//上报
			TET_Resource_Refreshed,//新增
			TET_Exploation_Initial ,//初始
		};
	

		
		
		/*!
		* TrapType
		**/
		enum TrapType
		{
			TT_Unknown = 0,			
			TT_Geological_Tect,
			TT_Geological_Litho,
			TT_Geological_stratigraphic,
			TT_Geological_combined,
			TT_Evaluation_Predication ,
			TT_Evaluation_Discovery  ,
			TT_Evalaution_Surronding ,

			//2016/12/6: 岩溶缝洞
			TT_Geological_karst_fracture,
		};

		enum TrapDevwellsolution
		{
			TDWS_uniform,
			TDWS_miduniform,
			TDWS_nouniformd,
		};

		/*!
		* default different kinds of resource
		**/
		enum VolumetricResourceType
		{
			VRT_Unknown = -1,
			VRT_Oil,		//0
			VRT_Gas,		//1
			VRT_ShaleGas,		//2
			VRT_ShaleOil,		//3
			VRT_OilSand,		//4
			VRT_MLR_Bitumen,//国土部沥青A 5
			VRT_MLR_Hindex , //国土部H index 6
			VRT_MLR_Cindex , //国土部C index 7 
			VRT_Common,//常规方法在此之前加，分隔符无实际意义8
			VRT_Rock_Pyrolysis_Oil,		//岩石热解(油) 9
			VRT_Rock_Pyrolysis_Gas,		//岩石热解(气) 10
			VRT_QSH_ShaleOil_05032013_Bitumen,	// 中石化，沥青A 11
			VRT_QSH_ShaleOil_05032013_Interlayer,	// 中石化，夹层体积 12
			VRT_QSH_ShaleGas_05032013,	// 中石化(含国土资源部，以及其可采资源量) 13
			VRT_DZT_ShaleGas_02542014,	// 国土资源部 14 
			VRT_LandFace_InterLayer,//陆相夹层 15
			VRT_User_Formulae,
			VRT_Max,
		};

		enum VolumetricResourceParasType
		{
			VRT_MLR_Bitumen_S			= VRT_MLR_Bitumen*100+1,
			VRT_MLR_Bitumen_H  			,
			VRT_MLR_Bitumen_A	 		,
			VRT_MLR_Bitumen_DEN			,
			VRT_MLR_Bitumen_Kj 			,
			VRT_MLR_Bitumen_rf			,
			VRT_MLR_Bitumen_Kp 			,
			VRT_MLR_Bitumen_GeoRes		,
			VRT_MLR_Bitumen_RecRes		,
			VRT_MLR_Bitumen_ValidAreas	,
			VRT_MLR_Bitumen_SinAreaNum	,
			VRT_MLR_Bitumen_SinArea		,
			VRT_MLR_Bitumen_SinAreaH	,
			VRT_MLR_Bitumen_SinAreaW	,
		
			VRT_MLR_Hindex_S			= VRT_MLR_Hindex*100+1,
			VRT_MLR_Hindex_H  			,
			VRT_MLR_Hindex_C  			,
			VRT_MLR_Hindex_DEN			,
			VRT_MLR_Hindex_To 			,
			VRT_MLR_Hindex_Tn 			,
			VRT_MLR_Hindex_K  			,
			VRT_MLR_Hindex_rf			,
			VRT_MLR_Hindex_GeoRes	   	,
			VRT_MLR_Hindex_RecRes	   	,
			VRT_MLR_Hindex_ValidAreas	,
			VRT_MLR_Hindex_SinAreaNum	,
			VRT_MLR_Hindex_SinArea   	,
			VRT_MLR_Hindex_SinAreaH  	,
			VRT_MLR_Hindex_SinAreaW  	,

			VRT_MLR_Cindex_S		   = VRT_MLR_Cindex*100+1,
			VRT_MLR_Cindex_H  		   ,
			VRT_MLR_Cindex_C  		   ,
			VRT_MLR_Cindex_DEN		   ,
			VRT_MLR_Cindex_Kc 		   ,
			VRT_MLR_Cindex_rf		   ,
			VRT_MLR_Cindex_GeoRes	   ,
			VRT_MLR_Cindex_RecRes	   ,
			VRT_MLR_Cindex_ValidAreas  ,
			VRT_MLR_Cindex_SinAreaNum  ,
			VRT_MLR_Cindex_SinArea     ,
			VRT_MLR_Cindex_SinAreaH    ,
			VRT_MLR_Cindex_SinAreaW    ,

			VRT_QSH_ShaleGas_05032013_S =  VRT_QSH_ShaleGas_05032013*100+1,
			VRT_QSH_ShaleGas_05032013_H	,
			VRT_QSH_ShaleGas_05032013_D,
			VRT_QSH_ShaleGas_05032013_G	,
			VRT_QSH_ShaleGas_05032013_K	,
			VRT_QSH_ShaleGas_05032013_GeoRes,
			VRT_QSH_ShaleGas_05032013_RecRes,
			VRT_QSH_ShaleGas_05032013_ValidAreas,
			VRT_QSH_ShaleGas_05032013_SinAreaNum,
			VRT_QSH_ShaleGas_05032013_SinArea,
			VRT_QSH_ShaleGas_05032013_SinAreaH,
			VRT_QSH_ShaleGas_05032013_SinAreaW,
			VRT_QSH_ShaleGas_05032013_Max,

			VRT_DZT_ShaleGas_02542014_A =   VRT_DZT_ShaleGas_02542014*100+1,
			VRT_DZT_ShaleGas_02542014_H	   ,
			VRT_DZT_ShaleGas_02542014_fai  ,
			VRT_DZT_ShaleGas_02542014_Sgi  ,
			VRT_DZT_ShaleGas_02542014_Den  ,
			VRT_DZT_ShaleGas_02542014_Bgi  ,
			VRT_DZT_ShaleGas_02542014_Cxi  ,
			VRT_DZT_ShaleGas_02542014_Zi   ,
			VRT_DZT_ShaleGas_02542014_cf   ,
			VRT_DZT_ShaleGas_02542014_rf   ,
			VRT_DZT_ShaleGas_02542014_GeoRes		,	
			VRT_DZT_ShaleGas_02542014_RecRes		,
			VRT_DZT_ShaleGas_02542014_ValidAreas	,
			VRT_DZT_ShaleGas_02542014_SinAreaNum	,
			VRT_DZT_ShaleGas_02542014_SinArea		,
			VRT_DZT_ShaleGas_02542014_SinAreaH		,
			VRT_DZT_ShaleGas_02542014_SinAreaW		,

			VRT_LandFace_InterLayer_A  =   VRT_LandFace_InterLayer*100+1,
			VRT_LandFace_InterLayer_Ca	,
			VRT_LandFace_InterLayer_Hfg	,
			VRT_LandFace_InterLayer_fai	,
			VRT_LandFace_InterLayer_Sw	,
			VRT_LandFace_InterLayer_Tsc	,
			VRT_LandFace_InterLayer_Psc	,
			VRT_LandFace_InterLayer_T	,
			VRT_LandFace_InterLayer_Pi 	,
			VRT_LandFace_InterLayer_Zi 	,
			VRT_LandFace_InterLayer_GeoRes,	
			VRT_LandFace_InterLayer_ValidAreas,
			VRT_LandFace_InterLayer_SinAreaNum,
			VRT_LandFace_InterLayer_SinArea,	
			VRT_LandFace_InterLayer_SinAreaH,	
			VRT_LandFace_InterLayer_SinAreaW,	

			VRT_QSH_ShaleOil_Bitumen_S  =  VRT_QSH_ShaleOil_05032013_Bitumen*100+1,
			VRT_QSH_ShaleOil_Bitumen_H				,
			VRT_QSH_ShaleOil_Bitumen_DEN 			,
			VRT_QSH_ShaleOil_Bitumen_A	  			,
			VRT_QSH_ShaleOil_Bitumen_Kaxi			,
			VRT_QSH_ShaleOil_Bitumen_TOC 			,
			VRT_QSH_ShaleOil_Bitumen_Ka  			,
			VRT_QSH_ShaleOil_Bitumen_rf  			,
			VRT_QSH_ShaleOil_Bitumen_GeoRes	 		,
			VRT_QSH_ShaleOil_Bitumen_AbsRes	 		,
			VRT_QSH_ShaleOil_Bitumen_FreRes	 		,
			VRT_QSH_ShaleOil_Bitumen_RecRes	 		,
			VRT_QSH_ShaleOil_Bitumen_ValidAreas		,
			VRT_QSH_ShaleOil_Bitumen_SinAreaNum		,
			VRT_QSH_ShaleOil_Bitumen_SinArea   		,
			VRT_QSH_ShaleOil_Bitumen_SinAreaH  		,
			VRT_QSH_ShaleOil_Bitumen_SinAreaW  		,

			VRT_QSH_ShaleOil_Interlayer_S   =  VRT_QSH_ShaleOil_05032013_Interlayer*100+1,
			VRT_QSH_ShaleOil_Interlayer_H			,
			VRT_QSH_ShaleOil_Interlayer_fai 		,
			VRT_QSH_ShaleOil_Interlayer_So	 		,
			VRT_QSH_ShaleOil_Interlayer_DEN 		,
			VRT_QSH_ShaleOil_Interlayer_Boi 		,
			VRT_QSH_ShaleOil_Interlayer_cf  		,
			VRT_QSH_ShaleOil_Interlayer_rf  		,
			VRT_QSH_ShaleOil_Interlayer_GeoRes		,
			VRT_QSH_ShaleOil_Interlayer_RecRes		,
			VRT_QSH_ShaleOil_Interlayer_ValidAreas	,
			VRT_QSH_ShaleOil_Interlayer_SinAreaNum	,
			VRT_QSH_ShaleOil_Interlayer_SinArea   	,
			VRT_QSH_ShaleOil_Interlayer_SinAreaH  	,
			VRT_QSH_ShaleOil_Interlayer_SinAreaW  	,
		};







		enum TrapEvalueStep
		{
			TES_Indenty=0,//白
			TES_Evalue,//橙
			TES_OptSelect,//黄
			TES_PreCheck,//灰
			TES_Storage,//蓝
			TES_Drill,//绿
			TES_Destory,//红
		};
		enum UnitKind
		{
			Unit_Domestic,
			Unit_Foreign,
		};
		enum Unitcontenttype
		{
			Unit_Domestic_oil,
			Unit_Domestic_gas,
			Unit_Domestic_ShaleGas,
			Unit_Domestic_ShaleOil,
			Unit_Domestic_OilSand,
			Unit_Domestic_MLRBitumen,
			Unit_Domestic_MLRHindex,
			Unit_Domestic_MLRCindex,
		};

		enum PlaySurveyExpLoreDegree
		{
			PSE_High,
			PSE_Mid,
			PSE_Low,
		};

	public:
		
		/*!
		*
		**/
		
		/*!
		*
		**/
		struct ResourceKindRecord
		{
			int m_idx;
			string m_name;	// for oil, gas, etc

			/*!
			*
			**/
			ResourceKindRecord() : m_idx(0), m_name("")
			{
			}
		};
		typedef std::vector<ResourceKindRecord> ResourceKindVector;



		/*!
		*
		**/
		struct ResourceClassRecord
		{
			int m_idx;
			string m_type; // 
			string m_class; //  

			/*!
			*
			**/
			ResourceClassRecord() : m_idx(0), m_type(""), m_class("")
			{
			}
		};
		typedef std::vector<ResourceClassRecord> ResourceClassVector;
////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////?????///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
		struct TinyVolctlgrid
		{
			int m_row;
			int m_col;
			double m_zvalue;
			std::vector<double> m_pointsZ;
			TinyVolctlgrid() : m_row(0), m_col(0), m_zvalue(0)
			{
				m_pointsZ.clear();
			}
			const TinyVolctlgrid &operator=(const TinyVolctlgrid &other)
			{
				if(this != &other)
				{
					m_row = other.m_row;
					m_col = other.m_col;
					m_zvalue=other.m_zvalue;
					m_pointsZ.clear();
					for(int i=0;i<other.m_pointsZ.size();i++)
					{
						m_pointsZ.push_back(other.m_pointsZ[i]);
					}
				}
				return *this;
			}
		};


		struct TinyVolResourcePredication
		{
			double m_oil;
			double m_freegas;
			double m_solutiongas;
			double m_absorbgas;

			double m_total;
			//页岩油
			double m_geooil;
			double m_absorboil;
			double m_Moil;//可动系数油,游离油
			double m_rfoil;
			TinyVolResourcePredication() : m_oil(0.), m_freegas(0.), m_solutiongas(0.), m_absorbgas(0.), m_total(0.),m_Moil(0),m_geooil(0),m_absorboil(0),m_rfoil(0)
			{
			}
			TinyVolResourcePredication(const TinyVolResourcePredication &other)
			{
				*this = other;
			}
			const TinyVolResourcePredication &operator=(const TinyVolResourcePredication &other)
			{
				if(this != &other)
				{
					m_oil = other.m_oil;
					m_freegas = other.m_freegas;
					m_solutiongas = other.m_solutiongas;
					m_absorbgas = other.m_absorbgas;
					m_total = other.m_total;
					m_Moil = other.m_Moil;
					m_geooil= other.m_geooil;
					m_absorboil= other.m_absorboil;
					m_rfoil=other.m_rfoil;
				}
				return *this;
			}
		};

		
		struct VolFuncParasRecord//参数
		{
			int    m_idx	;
			string m_name	;  
			string m_Des	;   
			string m_Unit	;
			
			
			CAnyDistributionStrategy *m_dis;
			//小面元体积法
			bool   m_isareapara;//是否是面积图层
			int	   m_caltype;//是否是定值 1:定值 0：图层
			string m_layername;//图层名称
			//小面元中间结果
			CAnyViewHook				   *m_hook						;
			std::vector<CGeoPoint<double>>	m_VariablePara				;
			CAnySequentialGaussSimulator   *m_SequentialGaussSimulator	;
			//小面元中间参数取值
			double m_fvalue;//取定值时的值
			std::vector<std::vector<double> > m_volSimdata;//小面元不确定性方法取值
			CGeoPoint<double> *m_volRasterizationdata;//小面元确定性方法取值

			/*!
			*
			**/
			VolFuncParasRecord() : m_idx(0), m_name(""), m_Des(""),m_Unit(""),m_fvalue(1.0),m_dis(0)
			{
				m_caltype  =1 ;
				m_layername="";
				m_isareapara=false;
				m_volRasterizationdata=0;
				m_volSimdata.clear();
				m_hook	=0;					
				m_VariablePara.clear();			
				m_SequentialGaussSimulator=0;	
			}
			~VolFuncParasRecord()
			{
				if(m_volRasterizationdata)
				{
					free(m_volRasterizationdata);
					m_volRasterizationdata=0;
				}
				if(m_SequentialGaussSimulator)
				{
					delete m_SequentialGaussSimulator;
					m_SequentialGaussSimulator=0;
				}
				if(m_dis)
				{
					delete m_dis;
					m_dis=0;
				}
			}
			const VolFuncParasRecord &operator=(const VolFuncParasRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_idx	=other.m_idx	;
				m_name	=other.m_name	;
				m_Des	=other.m_Des	;
				m_Unit	=other.m_Unit	;
				m_caltype  =other.m_caltype		;
				m_layername=other.m_layername	;
				m_fvalue=other.m_fvalue	;
				m_isareapara=other.m_isareapara	;

				m_volSimdata.clear();
				for(int i=0;i<other.m_volSimdata.size();i++)
				{
					std::vector<double> d;
					for(int j=0;j<other.m_volSimdata[i].size();j++)
					{
						d.push_back(other.m_volSimdata[i][j]);
					}
					m_volSimdata.push_back(d);
				}
				m_volRasterizationdata = other.m_volRasterizationdata;
				m_hook	=other.m_hook;					
				m_VariablePara.clear();
				for(int i=0;i<other.m_VariablePara.size();i++)
				{
					m_VariablePara.push_back(other.m_VariablePara[i]);
				}
				m_SequentialGaussSimulator=other.m_SequentialGaussSimulator;	

				m_dis = other.m_dis;
				return *this;
			}
			void Reset()
			{
				//m_idx		=		0		; 
				//m_name		=		""		; 
				//m_Des		=		""		;
				//m_Unit		=		""		;
				//m_caltype	=		1		;
				m_layername =		""		;
				m_fvalue	=		1		;
				//m_isareapara=		false	;
				if(m_volRasterizationdata)
				{
					free(m_volRasterizationdata);
					m_volRasterizationdata=0;
				}
				m_volSimdata.clear();
				m_hook	=0;					
				m_VariablePara.clear();			
				if(m_SequentialGaussSimulator)
				{
					delete m_SequentialGaussSimulator;
					m_SequentialGaussSimulator=0;
				}
				if(m_dis)
				{
					delete m_dis;
					m_dis=0;
				}	
			}
			void ResetLayer()
			{
				m_hook	=0;					
				m_VariablePara.clear();			
				if(m_SequentialGaussSimulator)
				{
					delete m_SequentialGaussSimulator;
					m_SequentialGaussSimulator=0;
				}
				if(m_volRasterizationdata)
				{
					free(m_volRasterizationdata);
					m_volRasterizationdata=0;
				}
				m_volSimdata.clear();
			}
			void ResetValue()
			{
				if( m_dis)
				{
					delete m_dis;
					m_dis = 0;
				}
				m_fvalue=1;
			}
		
		};

		struct VolFuncRecord // 方法
		{
			int    m_idx	;
			string m_name	;  
			string m_Des	;   
			string m_formula;
			
			std::vector<VolFuncParasRecord> m_calparas;
			std::vector<VolFuncParasRecord> m_resparas;

			////////////////////////////////////////////////////////
			//小面元体积法参数
			int m_tinycaltype;//0:确定  1：不确定
			string m_tinycalunit;//m/km
			int m_tinycalgridX;//网格数 
			int m_tinycalgridY;
			int m_tinycaliternum;//迭代数
			double m_tinycalvarate;//变差率
			double m_sucrate;//成功概率
			std::vector<TinyVolctlgrid> m_ctlgrid;//控制网格
			double m_minctlgridvalue;
			double m_maxctlgridvalue;


			//小面元体积法结果
			std::vector<TinyVolResourcePredication> m_resources;
			std::vector<TinyVolResourcePredication> m_resources_geological_probability;
			std::vector<CGeoPoint<double> > m_centersabudance;//总资源丰度
			int    m_valid_tiny_num		;//有效个数
			double m_alltinyarea		;//单一面积总面积
			double m_tinyarea			;//单一面积
			double m_areawidth			;//单一面积宽
			double m_areahight			;//单一面积高




			//////////////////////////////////////////////////////////////
			/*!
			*
			**/
			VolFuncRecord() : m_idx(0), m_name(""), m_Des(""),m_formula("")
			{
				m_calparas.clear();
				m_resparas.clear();
				m_tinycaltype=1;
				m_tinycalunit="m";
				m_tinycalgridX=10;
				m_tinycalgridY=10;
				m_tinycaliternum=100;
				m_tinycalvarate=50;
				m_sucrate=100;
				m_resources.clear();
				m_resources_geological_probability.clear();
				m_ctlgrid.clear();
				m_minctlgridvalue=0;
				m_maxctlgridvalue=0;
				m_centersabudance.clear();
				m_valid_tiny_num=0;		
				m_alltinyarea	=0;	
				m_tinyarea		=0;	
				m_areawidth		=0;
				m_areahight		=0;
				//m_TinyVolSimulationData.clear();
			}
			const VolFuncRecord &operator=(const VolFuncRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_idx	=other.m_idx	;
				m_name	=other.m_name	;
				m_Des	=other.m_Des	;
				m_formula = other.m_formula	;

				m_calparas.clear();
				for(int i=0;i<other.m_calparas.size();i++)
				{
					m_calparas.push_back(other.m_calparas[i]);
				}
				m_resparas.clear();
				for(int i=0;i<other.m_calparas.size();i++)
				{
					m_resparas.push_back(other.m_resparas[i]);
				}
				m_resources.clear();
				for(int i=0;i<other.m_resources.size();i++)
				{
					m_resources.push_back(other.m_resources[i]);
				}
				m_resources_geological_probability.clear();
				for(int i=0;i<other.m_resources_geological_probability.size();i++)
				{
					m_resources_geological_probability.push_back(other.m_resources_geological_probability[i]);
				}
				m_ctlgrid.clear();
				for(int i=0;i<other.m_ctlgrid.size();i++)
				{
					m_ctlgrid.push_back(other.m_ctlgrid[i]);
				}
				m_centersabudance.clear();
				for(int i=0;i<other.m_centersabudance.size();i++)
				{
					m_centersabudance.push_back(other.m_centersabudance[i]);
				}
				//m_TinyVolSimulationData.clear();
				//for(int i=0;i<other.m_TinyVolSimulationData.size();i++)
				//{
				//	m_TinyVolSimulationData.push_back(other.m_TinyVolSimulationData[i]);
				//}

				m_tinycaltype		=other.m_tinycaltype	;
				m_tinycalunit		=other.m_tinycalunit	;
				m_tinycalgridX		=other.m_tinycalgridX	;
				m_tinycalgridY		=other.m_tinycalgridY	;
				m_tinycaliternum	=other.m_tinycaliternum	;
				m_tinycalvarate		=other.m_tinycalvarate	;
				m_sucrate			=other.m_sucrate		;
				m_minctlgridvalue	=other.m_minctlgridvalue;
				m_maxctlgridvalue	=other.m_maxctlgridvalue;
				m_valid_tiny_num	=other.m_valid_tiny_num	;		
				m_alltinyarea		=other.m_alltinyarea	;	
				m_tinyarea			=other.m_tinyarea		;	
				m_areawidth			=other.m_areawidth		;
				m_areahight			=other.m_areahight		;						
				return *this;
			}
			void Reset()
			{
				m_idx		=		0		; 
				m_name		=		""		; 
				m_Des		=		""		;
				m_formula	=		""		;
				m_calparas.clear();
				m_resparas.clear();
				m_tinycaltype=1;
				m_tinycalunit="m";
				m_tinycalgridX=10;
				m_tinycalgridY=10;
				m_tinycaliternum=100;
				m_tinycalvarate=50;
				m_sucrate=100;
				m_resources.clear();
				m_resources_geological_probability.clear();
				m_ctlgrid.clear();
				m_minctlgridvalue=0;
				m_maxctlgridvalue=0;
				m_centersabudance.clear();
				m_valid_tiny_num=0;		
				m_alltinyarea	=0;	
				m_tinyarea		=0;	
				m_areawidth		=0;
				m_areahight		=0;
				//m_TinyVolSimulationData.clear();
			}

			int GetTinyVolAreaParaOrder()
			{
				int order2=0;
				for(int i=0;i<m_calparas.size();i++)
				{
					if(m_calparas[i].m_isareapara && m_calparas[i].m_caltype==0)
					{
						order2 = i;
						break;
					}
				}
				return order2;
			}
			int GetTinyVolParaOrder(int paratype)
			{
				int order=0;
				for(int i=0;i<m_calparas.size();i++)
				{
					if(m_calparas[i].m_idx == paratype)
					{
						order = i;
						break;
					}
				}
				return order;
			}

			void ClearCtlGrid()
			{
				m_ctlgrid.clear();
				m_minctlgridvalue=0;
				m_maxctlgridvalue=0;
			}
		};

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////



	
	
	public:
		
		
		CAccumulationResourceManager();
		
		
		~CAccumulationResourceManager();

		/*!
		*
		**/
		void InitVolFuncRecord();
		/*!
		*
		**/
		static int GetResourceKindCount();

		/*!
		*
		**/
		static ResourceKindRecord &GetResourceKind(int index);

		/*!
		*
		**/
		static int GetResourceClassCount();

		/*!
		*
		**/
		static ResourceClassRecord &GetResourceClass(int index);

		/*!
		*
		**/
		static void GetResourceClassType(std::vector<string> &types);

		/*!
		*
		**/
		static void GetResourceClasses(const string &type, std::vector<string> &classes);

		//
		//
		//
		/*!
		*
		**/
		static void InitResourceKindNames();

		/*!
		*
		**/
		static void InitResourceKindRecords();

		/*!
		*
		**/
		static void InitResourceClassRecords();

		static void InitUnitKindNames();
		static void InitTrapTypeNames();
		static void InitTrapExplorationPhaseType();
		static void InitResourceCategoryType();
		static void InitVolumeStatCommitPhaseType();
		static void InitPlaySurveyExpLoreDegree();
		static void InitTrapDevwellsolution();
		static void InitSeismicSchemeType();
		static void InitUnderstandingdegree();
		static void InitShaleUnitKindNames();
		/*!
		*
		**/
		static int GetTrapStepOrderByName(string &name);
		static void GetTrapStepNameByOrder(int order ,string &name);
		static int GetTrapStepNameCount();
		static void GetTrapStepColourByStepOrder(int order ,short &R,short &G,short &B);

		static int GetUnitContentType(int unittype,int resourcetype);
		static void GetUnitVectoeString(int unitcontenttype,int order,string &unitname);
		static void GetShaleUnitVectoeString(int unitcontenttype,int order,string &unitname);
		static void GetShaleUnitVectoeString2(int unitcontenttype,int order,string &unitname);

		static int GetTrapTypenum();
		static void GetTrapTypeNameByOrder(int order,string &name);

		static int GetTrapExplorationphaseTypenum();
		static void GetTrapExplorationphaseNameByOrder(int order,string &name);
		static int GetTrapExplorationphaseOrderByName(string &name);

		static int GetResourceCategoryTypenum();
		static void GetResourceCategoryNameByOrder(int order,string &name);

		static int GetVolumeStatCommitPhaseTypenum();
		static void GetVolumeStatCommitPhaseNameByOrder(int order,string &name);
		static int GetVolumeStatCommitPhaseOrderByName(string &name);

		static int  GetPlaySurveyExpLoreDegreeTypenum();
		static void GetPlaySurveyExpLoreDegreeNameByorder(int order,string &name);
		static int  GetPlaySurveyExpLoreDegreeOrderByName(string &name);

		static int  GetTrapDevwellsolutionnum();
		static void GetTrapDevwellsolutionNameByorder(int order,string &name);
		static int  GetTrapDevwellsolutionOrderByName(string &name);

		static int  GetSeismicSchemeTypenum();
		static void GetSeismicSchemeTypeNameByorder(int order,string &name);

		static int  GetUnderstandingdegreenum();
		static void GetUnderstandingdegreeNameByorder(int order,string &name);

		void GetVolFuncRecordbyBuildType(int buildtype,std::vector<VolFuncRecord> &VolFuncRecord);

	private:
		/*!
		*
		**/
		static void DoLoadResourceKindRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		static void DoLoadResourceClassRecord(CAnyAccessor &accessor);

		/*!
		*
		**/
		static bool CompareResourceClassRecord(const ResourceClassRecord &first, const ResourceClassRecord &second);

		/*!
		*
		**/
		static void AutoLoadTrapEvalueStepName();
    public:
		// resource kind
		static std::vector<string> m_resourceKindNames;
		static std::vector<string> m_unitdesc;
		static std::map<int,std::vector<std::string>> m_unitcontent;
		static std::map<int,std::vector<std::string>> m_shaleunitcontent;
		static std::map<int,string> m_TrapTypecontent;
		static std::map<int,string> m_trapexplorationphasetype;
		static std::map<int,string> m_ResourceCategorytype;
		static std::map<int,string> m_VolumeStatCommitPhasetype;
		static std::map<int,string> m_PlaySurveyExpLoreDegree;
		static std::map<int,string> m_TrapDevwellsolution;
		static std::map<int,string> m_seismicschemetype;
		static std::map<int,string> m_Understandingdegree;
		/*!
		通过restype name 获取对应的kindID
		**/
		static int GetResourceKindIDbyName(string &name);

		static int GetUnitKindnum();
		static void GetUnitNameByOrder(int order,string &name);
	
		
	private:
		// resource kinds
		static ResourceKindVector m_kinds;
		// resource classes
		static ResourceClassVector m_classes;

		// tables invovled
		static string m_kindTable;
		static string m_classTable;
		static std::vector<string> m_trapevaluestepname;



		std::vector<VolFuncRecord> m_VolFuncRecord;





		
	};
}
#endif