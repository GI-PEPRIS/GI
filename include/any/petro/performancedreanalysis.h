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
#ifndef __ANYPETRO_PERFORMANCE_DRE_ANALYSIS_H__
#define __ANYPETRO_PERFORMANCE_DRE_ANALYSIS_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
#include "accumulationelement.h"
#include "accumulationassessor.h"
using namespace AnyPetro;

#include "any/base/anygeom.h"
using namespace AnyBase;

#include "any/math/anygeneticalgorithm.h"
using namespace AnyMath;

//
namespace AnyPetro
{
	//
	class GasMBRBase;



	/*!
	*
	**/
	class ANYPETRO_CLASS CPerformanceDREAnalysis : public CAccumulationAssessor
	{
	public:
		// 动态储量评价方法
		enum DREMethodType
		{
			DRE_Unknown = -1,
			DRE_Static,									// 静压，对应活动 ST_Performance_Static_Pressure
			DRE_Fluid,									// 流压，对应活动 ST_Performance_Flowing_Pressure
			DRE_Production,							// 地层压力，对应活动 ST_Performance_Production_Pressure
			DRE_Max
		};

//气体密度ρg = Mg*p / (Z*R*T)
//Mg :分子量，   kg/Kmol
//p  : 压力，MPa
//Z  :偏差因子
//T  : 温度，K
//R : 通用气体常数， R = 0.008314  (MPa. m3/ Kmol .K)

		// 对应"气藏基础地质参数配置表"，部分字段，后续跟进更新
		struct GeologicalParameter
		{
			long   m_wellid;							// 井id
			double m_pi;								// 初始地层压力
			double m_sgi;							// 初始含气饱和度
			double m_swi;							// 初始含水饱和度
			double m_phi;							// 孔隙度
			double m_cf;							// 岩石孔隙压缩系数
			double m_cw;							// 地层水压缩系数
			double m_pb;								// 储层密度
			double m_T;								// 地层温度，(273.15+ t0)   
			double m_Psc;							// 地表压力
			double m_Tsc;							// 地表标准温度
			double m_zsc;							// 地表标准压力
			double m_peff;							// 有效应力，需要根据围压来计算
			double m_vl;								// 等温吸附曲线兰氏体积
			double m_pl;								// 等温吸附曲线兰氏压力

			double m_mg;							// 分子量，   kg/Kmol
			double m_rg;							// 天然气相对密度
			double m_co2;							// CO2摩尔百分数
			double m_h2s;							// H2S摩尔百分数
			double m_n2 ;							// N2摩尔百分数

			short  m_zgmodel;						// 天然气偏差因子计算模型

			double m_h	;								//储层厚度
			double m_rw	;							//井眼半径
			double m_soi;							//初始含油饱和度
			double m_cti;							//综合压缩系数
			GeologicalParameter() : m_wellid(0), m_pi(0), m_sgi(0), m_swi(0), m_phi(0), m_cf(0), m_cw(0), m_pb(0), m_T(273.15), m_Psc(0.101), m_Tsc(293.15), m_zsc(1), m_peff(0), \
				m_vl(0), m_pl(0), m_zgmodel(0), m_mg(0.), m_rg(0.), m_co2(0.), m_h2s(0.), m_n2(0.),m_h(0), m_rw	(0),m_soi(0),m_cti(0)
			{
			}
			void Reset()
			{
				m_wellid=0;
				m_pi	=0;
				m_sgi	=0;
				m_swi	=0;
				m_phi	=0;
				m_cf	=0;
				m_cw	=0;
				m_pb	=0;
				m_T		=273.15;
				m_Psc  = 0.101;
				m_Tsc	= 293.15;
				m_zsc	=1;
				m_peff	=0;
				m_vl	=0;
				m_pl	=0;
				m_mg    = 0.;
				m_rg	=0;
				m_co2	=0;
				m_h2s	=0;
				m_n2	=0;
				m_h		=0;
				m_rw	=0;
				m_soi	=0;
				m_cti	=0;
			}
			const GeologicalParameter &operator=(const GeologicalParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_wellid=other.m_wellid;
				m_pi	=other.m_pi	   ;
				m_sgi	=other.m_sgi	;
				m_swi	=other.m_swi	;
				m_phi	=other.m_phi	;
				m_cf	=other.m_cf	   ;
				m_cw	=other.m_cw	   ;
				m_pb	=other.m_pb	   ;
				m_T		=other.m_T		;
				m_Psc	=other.m_Psc	;
				m_Tsc	=other.m_Tsc	;
				m_zsc	=other.m_zsc	;
				m_peff	=other.m_peff	;
				m_vl	=other.m_vl	   ;
				m_pl	=other.m_pl	   ;
				m_rg	=other.m_rg	   ;
				m_mg	=other.m_mg	   ;
				m_co2	=other.m_co2	;
				m_h2s	=other.m_h2s	;
				m_n2	=other.m_n2	   ;
				m_h		=other.m_h		;
				m_rw	=other.m_rw		   ;
				m_soi	=other.m_soi	 ;
				m_cti	=other.m_cti	;
				return *this;
			}


		};

		// 对应"实测压力数据管理表"，根据“状态标志”字段，判断当前记录是否可用，根据“测试产气量”是否为零，判断是流压（产量不为零）还是静压（产量为零）
		struct MeasuredPressure
		{
			long   m_wellid  ;							//
			double m_date	 ;							// 实测时间
			double m_md      ;							// 测试深度
			double m_tvd     ;							// 测试垂深
			double m_pressure;					
			double m_measuredgasproduction;				// 测试产气量, 根据“测试产气量”是否为零，判断是流压（产量不为零）还是静压（产量为零）
			long   m_order;
			// 非表中字段，中间计算结果
			double m_zg;								// 天然气偏差因子计算
			double m_isused;						//
			MeasuredPressure() : m_wellid(0), m_md(0), m_tvd(0), m_pressure(0),m_measuredgasproduction(0), m_isused(true),m_order(0)
			{
			}
			const MeasuredPressure &operator=(const MeasuredPressure &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_wellid  =other.m_wellid	;
				m_date	  =other.m_date	 	;
				m_md      =other.m_md      	;
				m_tvd     =other.m_tvd     	;
				m_pressure=other.m_pressure	;
				m_measuredgasproduction=other.m_measuredgasproduction;
				m_order = other.m_order;
				return *this;
			}
		};
		typedef std::vector<MeasuredPressure> PressureVector;

		// 对应“气井日生产数据表”，根据需要更新相关定义
		struct ProductionData
		{
			long   m_wellid			;
			double m_date			;
			double m_casingpressure	;//套压
			double m_tubingpressure	;//油压
			double m_gasproduction	;
			double m_waterproduction;
			double m_oilproduction	;
			double m_calculatedsandfacepressure;	// 计算的流压

			// 非表中字段，中间计算结果
			double m_gp;						// 到当前时间点的累计产气量

			/*!
			*
			**/
			ProductionData() : m_wellid(0), m_date(0), m_casingpressure(0.), m_tubingpressure(0.), m_gasproduction(0.), m_waterproduction(0.), m_oilproduction(0.), m_calculatedsandfacepressure(0.), m_gp(0.)
			{
			}
			const ProductionData &operator=(const ProductionData &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_wellid			=other. m_wellid			;
				m_date				=other. m_date				;
				m_casingpressure	=other. m_casingpressure	;
				m_tubingpressure	=other. m_tubingpressure	;
				m_gasproduction		=other. m_gasproduction		;
				m_waterproduction	=other. m_waterproduction	;
				m_oilproduction		=other. m_oilproduction		;
			    m_calculatedsandfacepressure = other.m_calculatedsandfacepressure;

				return *this;
			}
		};
		typedef std::vector<ProductionData> ProductionVector;

		// 对应“动态储量评价结果表”，根据需要更新成员变量定义
		struct EvaluationRecord
		{
			long   m_wellid;													// 井ID
			long   m_practiceid;											// 动态分析结果ID
			double m_balancetype;						// 物质平衡评价方法ID，int, not null。分物质平衡，流动物质平衡和动态物质平衡方法
			double m_isabsorption;						// 是否考虑吸附气解吸
			double m_ispressuresensitivity;			// 是否考虑应力敏感
			double m_intercept;											// 拟合直线截距
			double m_intercept_fluid;									// 基于流压，拟合直线截距
			double m_slope;												// 拟合直线斜率
			double m_gasproductionrate;							// 理论采气指数
			double m_reserve;											// 计算的总储量
			double m_freereserve;										// 计算的自由气储量
			double m_absorbreserve;								// 计算的吸附气储量
			double m_abandonpresssure;							// 废弃地层压力
			double m_eur;													// 预计EUR
			double m_eurrate;												// 预计采出程度
			double m_absorbscale;									// 吸附气比例

			double m_pi;
			double m_cf;
			string m_remark;
			double m_when;
			bool   m_isabsorb;
			
			const EvaluationRecord &operator=(const EvaluationRecord &other)
			{
				m_wellid				  =other.m_wellid;				
				m_practiceid			  =other.m_practiceid;			
				m_balancetype			  =other.m_balancetype;			
				m_isabsorption			  =other.m_isabsorption;			
				m_ispressuresensitivity	  =other.m_ispressuresensitivity;	
				m_intercept				  =other.m_intercept;				
				m_intercept_fluid		  =other.m_intercept_fluid;		
				m_slope					  =other.m_slope;					
				m_gasproductionrate		  =other.m_gasproductionrate;		
				m_reserve				  =other.m_reserve;				
				m_freereserve			  =other.m_freereserve;			
				m_absorbreserve			  =other.m_absorbreserve;			
				m_abandonpresssure		  =other.m_abandonpresssure;		
				m_eur					  =other.m_eur;					
				m_eurrate				  =other.m_eurrate;				
				m_absorbscale			  =other.m_absorbscale;			
				m_pi					  =other.m_pi;
				m_cf				      =other. m_cf;
				m_remark				  =other. m_remark;
				m_when					  =other. m_when;
				m_isabsorb				  =other. m_isabsorb;
												 
				return *this;
			}
			
			
			
			
			
			
			
			
			
			void reset()
			{
				m_wellid				=0;
				m_practiceid			=0;
				m_balancetype			=0;
				m_isabsorption			=0;
				m_ispressuresensitivity= 0;
				m_intercept				=0;
				m_intercept_fluid		=0;
				m_slope					=0;
				m_gasproductionrate		=0;
				m_reserve				=0;
				m_freereserve			=0;
				m_absorbreserve			=0;
				m_abandonpresssure		=0;
				m_eur					=0;
				m_eurrate				=0;
				m_absorbscale			=0;

				m_pi				   = 0;
				m_cf				   = 0;
				m_remark			   ="";
				m_when				   = 0;
				m_isabsorb			   =false;
			}
		};

		// 对应“动态储量评价中间数据表”
		struct RegressionVariable
		{
			long m_wellid;
			long m_practiceid;
			double m_gp;									// X轴
			double m_pz;									// Y轴（对静压和流压是左轴，对动态是右轴）
			double m_pi;									// 对动态，是Y轴，右侧（采气指数）
			double m_zgp;								// 动态法中间结果
			double m_gasproductionrate;
			double m_isused;
			int m_methodtype;
			long m_date;//取样日期
			double m_ptest;//实测压力
			long m_order;
		};
		typedef std::vector<RegressionVariable> RegressionVariableVector;

		/*!
		*2016/7/14,平衡产能预测相关的基础地质参数
		**/
		struct PredictRateParameter
		{
			double qs;				//稳产期产量
			double qL;				//经济极限废弃产量
			double A;				//产能方程系数
			double B;				//产能方程系数
			double p0;				//原始地层压力
			double pwL;				//最低井底流压
			double G1;				//区域1原始储量
			double G2;				//区域2原始储量
			double maxdt;			//最大时步大小
			double maxt;			//最大时间
			double xdmd;			//天然气相对密度
			double t0;				//气藏温度
			double A2;				//窜流系数
			double sw0;				//页岩初始含水饱和度sw0
			double VL;				//页岩等温吸附曲线参数
			double PL;				//页岩等温吸附曲线参数
			double phi;				//页岩孔隙度
			double density_rock;	//页岩密度
			bool adsorb_flag1 ;		//SRV区物质平衡模型是否考虑吸附气参数配置
			bool adsorb_flag2 ;		//SRV区外物质平衡模型是否考虑吸附气参数配置
			bool abnormal_flag;		//配置异常高压abnoarmal=0/1，否则为常规气藏
			
			//配置为异常高压气藏，给定岩石压缩系数与压力表:cf_tab = [ p, cf]，可以给常数
			int cf_tab_row;
			int cf_tab_col;
			double **cf_tab;

			double cw;//水的压缩系数cw，仅在异常高压时有用
			bool hist_match_flag;//加载历史标志hist_match_flag=0/1
			
			//历史日产气hist_tab=[t(d),qg(10^4m3/d)]
			int hist_tab_row;
			int hist_tab_col;
			double **hist_tab;	// production table
			
			//上一迭代步骤
			double Gp10;
			double Gp20;
			double qgw0;
			double qg20;

			double pv10;
			double pv20;
			double cur_dt;
			double cur_pv1;

			/*!
			*
			**/
			PredictRateParameter() 
			{
				Reset();
			}

			/*!
			*
			**/
			const PredictRateParameter &operator=(const PredictRateParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}
				
				Release();

				qs = other.qs;
				qL = other.qL;
				A = other.A;
				B = other.B;
				p0 = other.p0;
				pwL = other.pwL;
				G1 = other.G1;
				G2 = other.G2;
				maxdt = other.maxdt;
				maxt = other.maxt;
				xdmd = other.xdmd;
				t0 = other.t0;
				A2 = other.A2;
				sw0 = other.sw0;
				VL = other.VL;
				PL = other.PL;
				phi = other.phi;
				density_rock = other.density_rock;
				adsorb_flag1 = other.adsorb_flag1;
				adsorb_flag2 = other.adsorb_flag2;
				abnormal_flag = other.abnormal_flag;
				cw = other.cw;
				hist_match_flag = other.hist_match_flag;
				Gp10 = other.Gp10;
				Gp20 = other.Gp20;
				qgw0 = other.qgw0;
				qg20 = other.qg20;
				pv10 = other.pv10;
				pv20 = other.pv20;
				cur_dt = other.cur_dt;
				cur_pv1 = other.cur_pv1;

				//
				InitCf(other.cf_tab_row,other.cf_tab_col,other.cf_tab);
				InitHist(other.hist_tab_row,other.hist_tab_col,other.hist_tab);
				return *this;
			}

			/*!
			*
			**/
			void Reset()
			{
				qs = 8.0;//6.5
				qL = 0.;
				A = 21.107;
				B = 2.9494;
				p0 = 38.2;
				pwL = 7.5;
				G1 = 13000.;
				G2 = 7500.;
				maxdt = 1.;
				maxt = 10000.0;
				xdmd = 0.5656;
				t0 = 80.2;
				A2 = 0.0002;
				sw0 = 0.3;
				VL = 2.;
				PL = 6.;
				phi = 0.035;
				density_rock = 2.6;
				adsorb_flag1 = false;
				adsorb_flag2 = false;
				abnormal_flag = false;
				cw = 0.;
				hist_match_flag = true;				
				Gp10 = 0.;
				Gp20 = 0.;
				qgw0 = 0.;
				qg20 = 0.;
				pv10 = 0.;
				pv20 = 0.;
				cur_dt = 0.;
				cur_pv1 = 0.;

				//
				cf_tab_row = 0;
				cf_tab_col = 0;
				cf_tab = 0;

				//
				hist_tab_row = 0;
				hist_tab_col = 0;
				hist_tab = 0;
			}

			/*!
			*
			**/
			void Release()
			{
				ReleaseCf();
				ReleaseHist();
			}

			/*!
			*
			**/
			void ReleaseCf()
			{
				if (cf_tab)
				{
					int i = 0;
					for (; i < cf_tab_col; i++)
					{
						::free(cf_tab[i]);
						cf_tab[i] = 0;
					}

					::free(cf_tab);
				}

				cf_tab_row = 0;
				cf_tab_col = 0;
				cf_tab = 0;
			}

			/*!
			*
			**/
			void ReleaseHist()
			{
				if (hist_tab)
				{
					int i = 0;
					for (; i < hist_tab_col; i++)
					{
						::free(hist_tab[i]);
						hist_tab[i] = 0;
					}

					::free(hist_tab);
				}

				hist_tab_row = 0;
				hist_tab_col = 0;
				hist_tab = 0;
			}

			/*!
			*
			**/
			bool InitCf(int row, int col, double **copiedRecord)
			{
				if (row <= 0 || col <= 0)
				{
					return false;
				}

				cf_tab_row = row;
				cf_tab_col = col;

				cf_tab = (double**)::malloc(cf_tab_row * sizeof(double*));
				int i = 0;
				for(; i < cf_tab_row; i++)
				{
					cf_tab[i] = (double *)::malloc(sizeof(double) * cf_tab_col);

					//if (copiedRecord)
					{
						int j = 0;
						for (; j < cf_tab_col; j++)
						{
							cf_tab[i][j] = copiedRecord == 0 ? 0 : copiedRecord[i][j];
						}
					}
				}

				return true;
			}

			/*!
			*
			**/
			bool InitHist(int row, int col, double **copiedRecord)
			{
				if (row <= 0 || col <= 0)
				{
					return false;
				}

				hist_tab_row = row;
				hist_tab_col = col;

				hist_tab = (double**)::malloc(hist_tab_row * sizeof(double*));
				int i = 0;
				for(; i < hist_tab_row; i++)
				{
					hist_tab[i] = (double *)::malloc(sizeof(double) * hist_tab_col);	

					//if (copiedRecord)
					{
						int j = 0;
						for (; j < hist_tab_col; j++)
						{
							hist_tab[i][j] = copiedRecord == 0 ? 0. : copiedRecord[i][j];
						}
					}
				}

				return true;
			}

			/*!
			*
			**/
			bool check_param_struct()
			{
				int ret = 0;

				if (!hist_match_flag)
				{
					return false;
				}

				if (abnormal_flag)
				{
					if (!cf_tab || !cf_tab_row || !cf_tab_col)
					{
						return false;
					}
				}

				if (hist_match_flag)
				{
					if (!hist_tab || !hist_tab_row || !hist_tab_col)
					{
						return false;
					}
										
					//if (hist_tab_col > hist_tab_row && hist_tab_row < 2)
					//{
					//	return false;	//hist_tab没有输成列模式
					//}

					//if (hist_tab_col > 2)
					//{
					//	return false;	//hist_tab应该为[天数，产气量(104m3/d)]列向量
					//}
				}

				return true;
			} 
		};

		struct MBRPredictRateParameter
		{
			double m_xdmd  ;
			double m_t0    ;
			double m_p0    ;double m_p0max;double m_p0min;
			double m_phi   ;
			double m_Cf    ;
			double m_sw    ;
			double m_vl    ;
			double m_pl    ;
			double m_rockmd;
			
			double m_ipr_a   ;double m_ipr_amax;	double m_ipr_amin;
			double m_ipr_b   ;double m_ipr_bmax;	double m_ipr_bmin;
			double m_srv_ogip;double m_srv_ogipmax;	double m_srv_ogipmin;
			double m_out_ogip;double m_out_ogipmax; double m_out_ogipmin;
			double m_A2      ;double m_A2max;		double m_A2min;
			double m_pwfL	 ;	 

			bool m_isuseipr_a   ;
			bool m_isuseipr_b   ;
			bool m_isusesrv_ogip;
			bool m_isuseout_ogip;
			bool m_isuseA2      ;
			
			int    m_hist_match_flag;
			int    m_adsorp_flag   ;
			int    m_composite_flag;
			int    m_abnormal_flag ;
			
			std::vector<double> m_tpv	;
			std::vector<double> m_ctrlv	;
			std::vector<double> m_lmtv	;
			std::vector<int>    m_modev	;
			std::vector<int>    m_months;
			std::vector<int>    m_points;
			std::vector<int>    m_pntv;//这个工作制度预测点数。如果是历史数据，输1
		
			//std::vector<GasMBRBase::WellCtrlType>    m_wellctrltypemodev	;
			/*!
			*
			**/
			MBRPredictRateParameter() 
			{
				m_xdmd   = 0.5656;
				m_t0     = 82;
				m_p0     = 38.2;m_p0min = 0; m_p0max=38.2*2;
				m_phi    = 0.0392;
				m_Cf     = 1.82E-3;
				m_sw     = 0.27;
				m_vl     = 2;
				m_pl     = 6;
				m_rockmd  =2.6;
				m_ipr_a   = 21.107;  m_ipr_amax		=21.107*2;	m_ipr_amin		=0;
				m_ipr_b   = 2.949;	 m_ipr_bmax		=2.949*2;	m_ipr_bmin		=0;	
				m_srv_ogip= 2.3E4;	 m_srv_ogipmax	=2.3E4*2;	m_srv_ogipmin	=0;	
				m_out_ogip= 3.0E4;	 m_out_ogipmax	=3.0E4*2;	m_out_ogipmin	=0; 
				m_A2      = 1.0E-4;	 m_A2max		=1.0E-4*2;	m_A2min			=0;	

				m_isuseipr_a   =true;
				m_isuseipr_b   =true;
				m_isusesrv_ogip=true;
				m_isuseout_ogip=true;
				m_isuseA2      =true;

				m_hist_match_flag= 0;
				m_adsorp_flag    = 1;
				m_composite_flag = 1;
				m_abnormal_flag  = 0;
				m_pwfL           = 7.5;

				
				m_tpv.push_back(1080);
				//tpv.push_back(360*3);
				//tpv.push_back(360);

				m_ctrlv.push_back(10);
				//ctrlv.push_back(10);
				//ctrlv.push_back(5);

				m_lmtv.push_back(7.5);
				//lmtv.push_back(5);
				//lmtv.push_back(2.5);

				m_modev.push_back(0);
				//modev.push_back(WellCtrlType::constQg);
				//modev.push_back(WellCtrlType::constBhp);
				//
				m_months.push_back(36); 
				m_points.push_back(300); 

				m_pntv.push_back(1080);
				
			}

			/*!
			*
			**/
			const MBRPredictRateParameter &operator=(const MBRPredictRateParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}
				
				m_xdmd   = other.m_xdmd   ;
				m_t0     = other.m_t0     ;
				m_p0     = other.m_p0     ;
				m_phi    = other.m_phi    ;
				m_Cf     = other.m_Cf     ;
				m_sw     = other.m_sw     ;
				m_vl     = other.m_vl     ;
				m_pl     = other.m_pl     ;
				m_rockmd  =other.m_rockmd ; 
				m_ipr_a   =other.m_ipr_a  ; 
				m_ipr_b   =other.m_ipr_b  ; 
				m_srv_ogip=other.m_srv_ogip;
				m_out_ogip=other.m_out_ogip;
				m_A2      =other.m_A2      ;
				m_p0max = other.m_p0max;
				m_p0min = other.m_p0min;
				m_ipr_amax		=other.m_ipr_amax	;	
				m_ipr_bmax		=other.m_ipr_bmax	;	
				m_srv_ogipmax	=other.m_srv_ogipmax;	
				m_out_ogipmax	=other.m_out_ogipmax;	
				m_A2max			=other.m_A2max		;
				m_ipr_amin		=other.m_ipr_amin	;		
				m_ipr_bmin		=other.m_ipr_bmin	;		
				m_srv_ogipmin	=other.m_srv_ogipmin;		
				m_out_ogipmin	=other.m_out_ogipmin;		
				m_A2min			=other.m_A2min		;		
				
				m_isuseipr_a   =other.m_isuseipr_a   ;
				m_isuseipr_b   =other.m_isuseipr_b   ;
				m_isusesrv_ogip=other.m_isusesrv_ogip;
				m_isuseout_ogip=other.m_isuseout_ogip;
				m_isuseA2      =other.m_isuseA2      ;

				m_adsorp_flag    = other.m_adsorp_flag    ;
				m_composite_flag = other.m_composite_flag ;
				m_abnormal_flag  = other.m_abnormal_flag  ;
				m_pwfL           = other.m_pwfL           ;
				m_hist_match_flag= other.m_hist_match_flag;

				m_tpv	.clear();
				m_ctrlv	.clear();
				m_lmtv	.clear();
				m_modev	.clear();
				m_months.clear();
				m_points.clear();
				m_pntv.clear();

				m_tpv.assign(other.m_tpv.begin(),other.m_tpv.end());
				m_ctrlv.assign(other.m_ctrlv.begin(),other.m_ctrlv.end());
				m_lmtv.assign(other.m_lmtv.begin(),other.m_lmtv.end());
				m_modev.assign(other.m_modev.begin(),other.m_modev.end());
				m_months.assign(other.m_months.begin(),other.m_months.end());
				m_points.assign(other.m_points.begin(),other.m_points.end());
				m_pntv.assign(other.m_pntv.begin(),other.m_pntv.end());
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
		CPerformanceDREAnalysis(CAccumulationElement *curElement, int activityType=CAccumulationAssessor::ST_Performance_Static_Pressure);
		~CPerformanceDREAnalysis();

	public:
		//
		unsigned int Commit(bool isDeleted = false);
		bool CommitStatic();
		bool GetStaticPractice(long elementidx,long activityid,std::vector<EvaluationRecord> &evaluationrecords);
		/*!
		* ADD等同UPDATE
		**/
		void UpdateGeologicalParameter(const GeologicalParameter &parameter); // 直接更新m_geoparameter
		void CommitGeologicalParameter();									  // 更新表数据
		void GetGeologicalParameter(GeologicalParameter &parameter);		  // 获取m_geoparameter,供界面显示使用

		void UpdateMeasuredPressure(const MeasuredPressure &pressure);		  // 用时间字段去判断是更新还是增加
		void UpdateProductionData(const ProductionData &production);		  // 用时间字段去判断是更新还是增加

		bool DoGetPrepareProductionData(ProductionVector &productions);

		void CalculateTP(double &tccorrected, double &pccorrected);			  // 临界压力、临界温度计算
		void CalculateInitialParameter(double &z,double &Bgi,double &Cgi, double &ui,double &Pgi,double &pc,double &tc);// 初始地层压力条件下，计算各个压力结果，方便随时改变地质参数进行应用计算
	
		//
		// 图版定义：psudopressure, zg, bg, pg, cg, ug
		//
		/*!
		* 双坐标轴图版：X轴（m_x），压力；左侧Y轴（m_y）：Zg，右侧Y轴（m_z）：Pseudo Pressure
		**/
		void GetZFactor(std::vector<CGeoPoint<double> > &variables);
		CGeoPoint<double> GetZFactor_Horizon2Pseudo(double horizonpressure);
		double GetZFactor_Pseudo2Horizon(double pseudopressure);
		double GetZFactor_PZ2Horizon(double pz);
		double GetZFactor_Horizon2PZ(double horizonpressure);

		/*!
		*  双坐标轴图版：X轴（m_x），压力；左侧Y轴（m_y）：Bg；右侧Y轴，对数坐标（m_z）：Pg
		**/
		void GetGasFormationVolumeFactor(std::vector<CGeoPoint<double> > &variables);
		CGeoPoint<double> GetGasFormationVolumeFactor(double pressure);
		CGeoPoint<double> GetCgFactor_Horizon2Pseudo(double horizonpressure);
		/*!
		* 对数坐标图版：X轴（m_x），压力；Y轴（m_y）对数坐标，Cg
		**/
		void GetGasCompressibility(std::vector<CGeoPoint<double> > &variables);
		CGeoPoint<double> GetGasCompressibility(double pressure);

		/*!
		*普通图版：X轴（m_x），压力；Y轴（m_y）：Ug
		**/
		void GetVisosity(std::vector<CGeoPoint<double> > &variables);
		CGeoPoint<double> GetVisosity(double pressure);

		//
		//
		//
		/*!
		* 静压：X轴（m_x）：累计产气（GP），Y轴（m_z）：P/Z，m_z和m_w的返回值待定，用于区分交会图的点 
		**/
		long GetRegressionVariable(RegressionVariableVector &variables);
		long AdjustDynamicReserve(double reserve,RegressionVariableVector &variables);
		long AdjustDynamicPI(double pi,RegressionVariableVector &variables);
		long AdjustDynamicLine(double intercept, double slope,RegressionVariableVector &variables);

		void SetVariableNonValid(RegressionVariable &variable);
		bool MakeDirectRegression(long practiceidx, double abandonpressure, double &intercept, double &slope, std::vector<CGeoPoint<double> > &line,double &piz, bool isfit = true, bool isfixintercept = false);

		// 读表，假设已经有数据的情况
		bool DoPrepareData();
		bool DoPrepareGeoData();
		bool DoPreparePressureData();
		bool DoPrepareProductionData();
		bool DoPrepareGeoDataSing(GeologicalParameter &geoparameter);
				
		//
		double DoGetGP(double date);
		double DoGetDailyProduction(double date);
		void DoGetStaticPressures();
		void DoGetFluidPressures();
		void DoGetSandPressures();

		// 动态物质平衡
		double DoCalculatect(double p);
		double DoCalculateDynamicProductionIndex(double reserve);
		double DoCalculateDynamicPressureFactor(double pi, RegressionVariableVector& variablese);
		void DoCalculateFluidPZ(double pressure, double &zgp, double &pz);
		void DoCalculateStaticPZ(double pressure, double &zgp, double &pz);


		//
		//2016/7/14
		//
		/*!
		*output parameter(tv,qwv...p2v) needs to be released outside the method
		**/
		bool PredictRateNewCompsite(PredictRateParameter &param_struct,int &count, double * &tv, double * &qwv, double * &q1v, double * &q2v, double * &pwfv, double * &Qwv, double * &Q1v, double * &Q2v,double * &p1v, double * &p2v);
		bool PredictRateNewCompsiteWithSlip(PredictRateParameter &param_struct,int &count, double * &tv, double * &qwv, double * &q1v, double * &q2v, double * &pwfv, double * &Qwv, double * &Q1v, double * &Q2v,double * &p1v, double * &p2v);

		// based on MBRbase
		int PredicateNewCompositeWithMBR(PredictRateParameter &param_struct,int &count, 
			std::vector<double>& tv,std::vector<double>& calc_qgv,std::vector<double>& calc_pwfv,std::vector<double>& calc_qg12v,
			std::vector<double>& srv_pavgv,std::vector<double>& out_pavgv,int drawtype=1);

		// 线性回归
		void DoLinearRegression(double *x, double *y, int number, double &a, double &b);	
		void DoSlopeRegression(double *x, double *y, int number, double &slope, double intercept);


		void CalTmb(std::vector<CGeoPoint<double>> &tmbs);
		void CalRNP(std::vector<CGeoPoint<double>> &RNPS);
		double CalAmKm( double m3 ,double le,double h,double nf,double OGIP,double &k ,double &t,double &xf);
	private:
		
		//
		static bool DoComparePressureDate(const MeasuredPressure &first, const MeasuredPressure &second)
		{
			return first.m_date < second.m_date;
		}
		static bool DoCompareProductionDate(const ProductionData &first, const ProductionData &second)
		{
			return first.m_date < second.m_date;
		}

		//
		//
		//
		/*!
		*
		**/
		double SRV_mbe(double pv1, PredictRateParameter &param_struct);
		double Out_Srv_mbe(double pv2, PredictRateParameter &param_struct);

		//
		//
		//
		/*!
		*
		**/
		double get_Z(double rd, double t0, double p);
		double get_Bg(double rd, double t0, double p);
		void Newton_Raphson(const std::string &name,double x0,PredictRateParameter &param_struct,double allowed_rsd, double &x, double &f1);

		/*!
		*sub method of fcnchk
		**/
		double deriv(const std::string &name,double x, PredictRateParameter &param_struct);
		void Bi_Search(const std::string &name,double x1, double x2, double f1, double f2, PredictRateParameter &param_struct,double allowed_rsd, double &x0, double &f0);

		//
		//
		//
		void DoDynamicLoopAdjustment(RegressionVariableVector &variables, double intialreserve, double initialpi, long practiceidx);

		//
		//
		//
		double DoGeneticObjectFunction(int nP, double *P, std::vector<GA_UserData> &UserData);
		bool DoGeneticCheckFunction(int nx, double *x);
		double DoGeneticFitnessFunction(int nx, double *x, double ObjFunValue);
		int DoGeneticPrecisionFunction(int nx, double *x, double ObjFunValue, double Fitness, double &PrecisionValue);

	public:
		CAccumulationElement *m_element;
		
		// 计算方法
		short m_methodtype;	// 压力类型：静压、流压、开发压力
		short m_zgmethodtype;	// 偏差因子模型
		short m_ugmethodtype;	// 粘度模型
		short m_cgmethodtype;   // 压缩系数
		short m_pseudotype;		// 然气拟临界温度校正

		// 临界压力、临界温度计算（可以作为类成员变量，多次调用）
		double m_pccorrected;
		double m_tccorrected;

		// 是否考虑吸附气解析
		bool m_isadsorption;
		// 是否考虑岩石孔隙压缩系数随地层压力变化
		bool m_isnoncf;

		// 气藏基础地质参数
		GeologicalParameter m_geoparameter;

		// 从"实测压力数据管理表"中，分别提取流压数据和静压数据
		PressureVector m_pressures;
		PressureVector m_staticpressures;
		PressureVector m_fluidpressures;
		PressureVector m_sandpressures;

		// 日产数据
		ProductionVector m_productions;

		// 标示基础数据是新增或修改，需要提交数据库
		bool m_isdirty;

		// 预测结果
		EvaluationRecord m_evaluation;
		// 预测中间结果
		RegressionVariableVector m_regressionvariables;

		// 需要记录图版
		std::vector<CGeoPoint<double> > m_zfactors;
		std::vector<CGeoPoint<double> > m_formations;
		std::vector<CGeoPoint<double> > m_compressibilities;
		std::vector<CGeoPoint<double> > m_visosities;

		//平衡产能预测相关的基础地质参数
		PredictRateParameter m_predictrateparameter;
		MBRPredictRateParameter m_MBRpredictrateparameter;

		// 动态法初始储量
		double m_dynamicreserve;
		double m_dynamicpi;

		//
		GasMBRBase *m_mbrbase;

		double m_PressureUp;
	};
}

#endif