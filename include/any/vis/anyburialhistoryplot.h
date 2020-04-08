/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYVIS_BASIN_MODEL_BURIAL_HISTORY_H__
#define __ANYVIS_BASIN_MODEL_BURIAL_HISTORY_H__

// refer to macro
#include "anyscattermatrix.h"
using namespace AnyVis;
//
//#include "anymath/anyburialhistorysimulator.h"
//using namespace AnyMath;

#include "anyburialhistorysimulator.h"

//
#include "any/db/anyaccessor.h"
using namespace AnyDB;

namespace AnyVis
{
	class ANYVIS_CLASS CAnyBurialHistoryPlot : public CAnyScatterMatrix, public CAnyBurialHistorySimulator
	{
	public:
		// trait
		typedef CAnyBurialHistorySimulator::GeologicalTimeScale GeologicalTimeScale;
		typedef CAnyBurialHistorySimulator::TimeScaleVector TimeScaleVector;

		// trait
		typedef CAnyBurialHistorySimulator::GeologicalLine GeologicalLine;
		typedef CAnyBurialHistorySimulator::GeologicalLines GeologicalLines;
		typedef CAnyBurialHistorySimulator::GeologicalLayerMap GeologicalLayerMap;

		//2017/3/1: same temperature/RO line
		typedef std::map<double,GeologicalLine> ContourLineMap;

		typedef CAnyBurialHistorySimulator::GeologicalLayer GeologicalLayer;
		typedef CAnyBurialHistorySimulator::GeologicalLayerVector GeologicalLayerVector;

		/*!
		*2017/8/29: practice related
		**/
		struct BurialHistoryPracticeRecord
		{
			long m_boreIdx;
			long m_practiceIdx;
			double m_whendo;
			string m_remark;

			/*!
			*
			**/
			BurialHistoryPracticeRecord() 
				: m_boreIdx(-1), m_practiceIdx(0), m_whendo(0.),m_remark("")
			{
			}

			/*!
			*
			**/
			const BurialHistoryPracticeRecord &operator=(const BurialHistoryPracticeRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				
				m_boreIdx = other.m_boreIdx;
				m_practiceIdx = other.m_practiceIdx;
				m_whendo = other.m_whendo;
				m_remark = other.m_remark;
								
				//
				return *this;
			}
		};
		typedef std::vector<BurialHistoryPracticeRecord> BurialHistoryPracticeRecords;
		
		/*!
		*2017/5/25: lithology
		**/
		struct GeologicalLithology
		{
			//category
			std::string m_category;

			//sub category
			std::string m_sub_category;

			//name
			std::string m_name;

			//porosity (%)
			double m_deposition_porosity;
			
			//Athy K (1/km)
			double m_athy_k_km;

			//Athy K (1/Mpa)
			double m_athy_k_mpa;

			//compress y max (1e-7/kPa)
			double m_compress_y_max;

			//compress y min (1e-7/kPa)
			double m_compress_y_min;

			//Schneider factor, ka (1/Mpa)
			double m_schneider_factor_ka;

			//Schneider factor, kb (1/Mpa)
			double m_schneider_factor_kb;

			//Schneider factor, φ (digit)
			double m_schneider_factor_fai;

			//reciprocal compaction factor (1/km)
			double m_reciprocal_compaction_factor;

			//Vert. Cond. (W/mK)
			double m_vert_cond;

			//Anisotr. ()
			double m_anisotr;

			//Sp. Heat Cap.(J/(KgK))
			double m_sp_heat_cap;

			//Th. Sort. Fac. (f)
			double m_th_sort_fac;

			//Den. (kg/m3)
			double m_den;

			//U (ppm)
			double m_u;

			//Th (ppm)
			double m_th;

			//K (%)
			double m_k;

			//radioactive heat (uW/m3)
			double m_radioactive_heat;

			//perm. Anisotr. ()
			double m_perm_anisotr;

			//porosity at point 1 (%)
			double m_porosity_pt_1;

			//porosity at point 2 (%)
			double m_porosity_pt_2;

			//porosity at point 3 (%)
			double m_porosity_pt_3;

			//permeability at point 1 (log mD)
			double m_permeability_pt_1;

			//permeability at point 2 (log mD)
			double m_permeability_pt_2;

			//permeability at point 3 (log mD)
			double m_permeability_pt_3;

			//2018/8/16: entry pressure related
			//entry pressure at porosity 1%
			double m_entrypr_porosity_1;
			
			//entry pressure at porosity 25%
			double m_entrypr_porosity_25;

			//a to entry pressure
			double m_a_to_entrypr;

			//b to entry pressure
			double m_b_to_entrypr;


			//formula
			std::vector<std::string> m_formulas;

			//2018/4/23: new variables
			long m_idx;
			std::vector<std::string> m_lith_names;
			std::vector<double> m_lith_ratios;
			
			//
			GeologicalLithology()
			{
				m_category = "";
				m_sub_category = "";

				m_name = "";

				m_deposition_porosity = ANY_NAN;
				
				m_athy_k_km = ANY_NAN;
				m_athy_k_mpa = ANY_NAN;
				
				m_compress_y_max = ANY_NAN;
				m_compress_y_min = ANY_NAN;
				
				m_schneider_factor_ka = ANY_NAN;
				m_schneider_factor_kb = ANY_NAN;
				m_schneider_factor_fai = ANY_NAN;

				m_reciprocal_compaction_factor = ANY_NAN;
				m_vert_cond = ANY_NAN;
				m_anisotr = ANY_NAN;
				m_sp_heat_cap = ANY_NAN;
				m_th_sort_fac = ANY_NAN;
				m_den = ANY_NAN;
				m_u = ANY_NAN;
				m_th = ANY_NAN;
				m_k = ANY_NAN;
				m_radioactive_heat = ANY_NAN;

				m_perm_anisotr = ANY_NAN;
				
				m_porosity_pt_1 = ANY_NAN;
				m_porosity_pt_2 = ANY_NAN;
				m_porosity_pt_3 = ANY_NAN;

				m_permeability_pt_1 = ANY_NAN;
				m_permeability_pt_2 = ANY_NAN;
				m_permeability_pt_3 = ANY_NAN;

				//2018/8/16: entry pressure related
				m_entrypr_porosity_1 = ANY_NAN;
				m_entrypr_porosity_25 = ANY_NAN;
				m_a_to_entrypr = ANY_NAN;
				m_b_to_entrypr = ANY_NAN;

				//
				m_formulas.push_back("1-(φ0 *EXP(-C*depth))");
				m_formulas.push_back("1-(1/(1/φ0 + C*depth))");
				//m_formulas.push_back("EXP(LOG(depth/6.02)/6.35)");

				//new variables
				m_idx = 0;
				m_lith_names.clear();
				m_lith_ratios.clear();
			}

			//overload *
			const GeologicalLithology &operator*(double scalar)
			{
				if (scalar >= 1. || scalar < 0.)
				{
					return *this;
				}

				//
				m_deposition_porosity = !ISNAN(m_deposition_porosity) ? m_deposition_porosity * scalar : m_deposition_porosity;
				m_athy_k_km = !ISNAN(m_athy_k_km) ? m_athy_k_km * scalar : m_athy_k_km;
				m_athy_k_mpa = !ISNAN(m_athy_k_mpa) ? m_athy_k_mpa * scalar : m_athy_k_mpa;

				m_compress_y_max = !ISNAN(m_compress_y_max) ? m_compress_y_max * scalar : m_compress_y_max;
				m_compress_y_min = !ISNAN(m_compress_y_min) ? m_compress_y_min * scalar : m_compress_y_min;

				m_schneider_factor_ka = !ISNAN(m_schneider_factor_ka) ? m_schneider_factor_ka * scalar : m_schneider_factor_ka;
				m_schneider_factor_kb = !ISNAN(m_schneider_factor_kb) ? m_schneider_factor_kb * scalar : m_schneider_factor_kb;
				m_schneider_factor_fai = !ISNAN(m_schneider_factor_fai) ? m_schneider_factor_fai * scalar : m_schneider_factor_fai;

				m_reciprocal_compaction_factor = !ISNAN(m_reciprocal_compaction_factor) ? m_reciprocal_compaction_factor * scalar : m_reciprocal_compaction_factor;
				m_vert_cond = !ISNAN(m_vert_cond) ? m_vert_cond * scalar : m_vert_cond;
				m_anisotr = !ISNAN(m_anisotr) ? m_anisotr * scalar : m_anisotr;
				m_sp_heat_cap = !ISNAN(m_sp_heat_cap) ? m_sp_heat_cap * scalar : m_sp_heat_cap;
				m_th_sort_fac = !ISNAN(m_th_sort_fac) ? m_th_sort_fac * scalar : m_th_sort_fac;
				m_den = !ISNAN(m_den) ? m_den * scalar : m_den;
				m_u = !ISNAN(m_u) ? m_u * scalar : m_u;
				m_th = !ISNAN(m_th) ? m_th * scalar : m_th;
				m_k = !ISNAN(m_k) ? m_k * scalar : m_k;
				m_radioactive_heat = !ISNAN(m_radioactive_heat) ? m_radioactive_heat * scalar : m_radioactive_heat;

				m_perm_anisotr = !ISNAN(m_perm_anisotr) ? m_perm_anisotr * scalar : m_perm_anisotr;

				m_porosity_pt_1 = !ISNAN(m_porosity_pt_1) ? m_porosity_pt_1 * scalar : m_porosity_pt_1;
				m_porosity_pt_2 = !ISNAN(m_porosity_pt_2) ? m_porosity_pt_2 * scalar : m_porosity_pt_2;
				m_porosity_pt_3 = !ISNAN(m_porosity_pt_3) ? m_porosity_pt_3 * scalar : m_porosity_pt_3;

				m_permeability_pt_1 = !ISNAN(m_permeability_pt_1) ? m_permeability_pt_1 * scalar : m_permeability_pt_1;
				m_permeability_pt_2 = !ISNAN(m_permeability_pt_2) ? m_permeability_pt_2 * scalar : m_permeability_pt_2;
				m_permeability_pt_3 = !ISNAN(m_permeability_pt_3) ? m_permeability_pt_3 * scalar : m_permeability_pt_3;

				//2018/8/16: entry pressure related
				m_entrypr_porosity_1 = !ISNAN(m_entrypr_porosity_1) ? m_entrypr_porosity_1 * scalar : m_entrypr_porosity_1;
				m_entrypr_porosity_25 = !ISNAN(m_entrypr_porosity_25) ? m_entrypr_porosity_25 * scalar : m_entrypr_porosity_25;
				m_a_to_entrypr = !ISNAN(m_a_to_entrypr) ? m_a_to_entrypr * scalar : m_a_to_entrypr;
				m_b_to_entrypr = !ISNAN(m_b_to_entrypr) ? m_b_to_entrypr * scalar : m_b_to_entrypr;

				//
				return *this;
			}

			//overload +=
			const GeologicalLithology &operator += (const GeologicalLithology &other)
			{
				m_deposition_porosity = !ISNAN(m_deposition_porosity) && !ISNAN(other.m_deposition_porosity) ? m_deposition_porosity + other.m_deposition_porosity : m_deposition_porosity;
				m_athy_k_km = !ISNAN(m_athy_k_km) && !ISNAN(other.m_athy_k_km) ? m_athy_k_km + other.m_athy_k_km : m_athy_k_km;
				m_athy_k_mpa = !ISNAN(m_athy_k_mpa) && !ISNAN(other.m_athy_k_mpa) ? m_athy_k_mpa + other.m_athy_k_mpa : m_athy_k_mpa;

				m_compress_y_max = !ISNAN(m_compress_y_max) && !ISNAN(other.m_compress_y_max) ? m_compress_y_max + other.m_compress_y_max : m_compress_y_max;
				m_compress_y_min = !ISNAN(m_compress_y_min) && !ISNAN(other.m_compress_y_min) ? m_compress_y_min + other.m_compress_y_min : m_compress_y_min;

				m_schneider_factor_ka = !ISNAN(m_schneider_factor_ka) && !ISNAN(other.m_schneider_factor_ka) ? m_schneider_factor_ka + other.m_schneider_factor_ka : m_schneider_factor_ka;
				m_schneider_factor_kb = !ISNAN(m_schneider_factor_kb) && !ISNAN(other.m_schneider_factor_kb) ? m_schneider_factor_kb + other.m_schneider_factor_kb : m_schneider_factor_kb;
				m_schneider_factor_fai = !ISNAN(m_schneider_factor_fai) && !ISNAN(other.m_schneider_factor_fai) ? m_schneider_factor_fai + other.m_schneider_factor_fai : m_schneider_factor_fai;

				m_reciprocal_compaction_factor = !ISNAN(m_reciprocal_compaction_factor) && !ISNAN(other.m_reciprocal_compaction_factor) ? m_reciprocal_compaction_factor + other.m_reciprocal_compaction_factor : m_reciprocal_compaction_factor;
				m_vert_cond = !ISNAN(m_vert_cond) && !ISNAN(other.m_vert_cond) ? m_vert_cond + other.m_vert_cond : m_vert_cond;
				m_anisotr = !ISNAN(m_anisotr) && !ISNAN(other.m_anisotr) ? m_anisotr + other.m_anisotr : m_anisotr;
				m_sp_heat_cap = !ISNAN(m_sp_heat_cap) && !ISNAN(other.m_sp_heat_cap) ? m_sp_heat_cap + other.m_sp_heat_cap : m_sp_heat_cap;
				m_th_sort_fac = !ISNAN(m_th_sort_fac) && !ISNAN(other.m_th_sort_fac) ? m_th_sort_fac + other.m_th_sort_fac : m_th_sort_fac;
				m_den = !ISNAN(m_den) && !ISNAN(other.m_den) ? m_den + other.m_den : m_den;
				m_u = !ISNAN(m_u) && !ISNAN(other.m_u) ? m_u + other.m_u : m_u;
				m_th = !ISNAN(m_th) && !ISNAN(other.m_th) ? m_th + other.m_th : m_th;
				m_k = !ISNAN(m_k) && !ISNAN(other.m_k) ? m_k + other.m_k : m_k;
				m_radioactive_heat = !ISNAN(m_radioactive_heat) && !ISNAN(other.m_radioactive_heat) ? m_radioactive_heat + other.m_radioactive_heat : m_radioactive_heat;

				m_perm_anisotr = !ISNAN(m_perm_anisotr) && !ISNAN(other.m_perm_anisotr) ? m_perm_anisotr + other.m_perm_anisotr : m_perm_anisotr;

				m_porosity_pt_1 = !ISNAN(m_porosity_pt_1) && !ISNAN(other.m_porosity_pt_1) ? m_porosity_pt_1 + other.m_porosity_pt_1 : m_porosity_pt_1;
				m_porosity_pt_2 = !ISNAN(m_porosity_pt_2) && !ISNAN(other.m_porosity_pt_2) ? m_porosity_pt_2 + other.m_porosity_pt_2 : m_porosity_pt_2;
				m_porosity_pt_3 = !ISNAN(m_porosity_pt_3) && !ISNAN(other.m_porosity_pt_3) ? m_porosity_pt_3 + other.m_porosity_pt_3 : m_porosity_pt_3;

				m_permeability_pt_1 = !ISNAN(m_permeability_pt_1) && !ISNAN(other.m_permeability_pt_1) ? m_permeability_pt_1 + other.m_permeability_pt_1 : m_permeability_pt_1;
				m_permeability_pt_2 = !ISNAN(m_permeability_pt_2) && !ISNAN(other.m_permeability_pt_2) ? m_permeability_pt_2 + other.m_permeability_pt_2 : m_permeability_pt_2;
				m_permeability_pt_3 = !ISNAN(m_permeability_pt_3) && !ISNAN(other.m_permeability_pt_3) ? m_permeability_pt_3 + other.m_permeability_pt_3 : m_permeability_pt_3;

				//2018/8/16: new variables
				m_entrypr_porosity_1 = !ISNAN(m_entrypr_porosity_1) && !ISNAN(other.m_entrypr_porosity_1) ? m_entrypr_porosity_1 + other.m_entrypr_porosity_1 : m_entrypr_porosity_1;
				m_entrypr_porosity_25 = !ISNAN(m_entrypr_porosity_25) && !ISNAN(other.m_entrypr_porosity_25) ? m_entrypr_porosity_25 + other.m_entrypr_porosity_25 : m_entrypr_porosity_25;
				m_a_to_entrypr = !ISNAN(m_a_to_entrypr) && !ISNAN(other.m_a_to_entrypr) ? m_a_to_entrypr + other.m_a_to_entrypr : m_a_to_entrypr;
				m_b_to_entrypr = !ISNAN(m_b_to_entrypr) && !ISNAN(other.m_b_to_entrypr) ? m_b_to_entrypr + other.m_b_to_entrypr : m_b_to_entrypr;
			
				//
				return *this;
			}
		};
		typedef std::vector<GeologicalLithology> GeologicalLithologies;
		typedef std::map<std::string, GeologicalLithologies> GeologicalLithologyMap;
		
		//
		/*!
		*2017/6/8: 干酪根降解率结构体 ，用于干酪根降解率与Ro关系
		**/
		struct DegradationRate
		{ 
			/////////////////////////////////////////input////////////////////////////////
			int NKerogen; //干酪根类型数
			std::vector<double> Ratio; //各种干酪根所占的比例
			
			int NI; //对应于I型干酪根降解率数值的个数
			std::vector<double> DRI;  //DegradationRate Of Type I Kerogen
			std::vector<double> RoI;  //对应于DegradationRate Of Type I Kerogen的Ro
			
			int NIIA; //对应于IIA型干酪根降解率数值的个数
			std::vector<double> DRIIA;  //DegradationRate Of Type IIA Kerogen
			std::vector<double> RoIIA;  //对应于DegradationRate Of Type IIA Kerogen的Ro
			
			int NIIB; //对应于IIB型干酪根降解率数值的个数
			std::vector<double> DRIIB;  //DegradationRate Of Type IIB Kerogen
			std::vector<double> RoIIB;  //对应于DegradationRate Of Type IIB Kerogen的Ro
			
			int NIII; //对应于III型干酪根降解率数值的个数
			std::vector<double> DRIII;  //DegradationRate Of Type III Kerogen
			std::vector<double> RoIII;  //对应于DegradationRate Of Type III Kerogen的Ro
			
			int NGDR; //对应于气降解含量的数值的个数
			std::vector<double> GDR; //气降解含量
			std::vector<double> RoGDR; //气降解含量对应的Ro%值
			
			double COG;//为油气转化率，一般取值0.96m3/kg ，暂时没用这个转化率，气量也用kg表示
			
			/////////////////////////////////////////output////////////////////////////////
			//四种不同类型的干酪根单位质量（kg)有机碳降解量
			double HCFromDRI;
			double HCFromDRIIA;
			double HCFromDRIIB;
			double HCFromDRIII; 
			
			//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
			double InitTOCI;
			double InitTOCIIA;
			double InitTOCIIB;
			double InitTOCIII; 
			
			//各组分的原始有机碳在地层段的原始有机碳质量kg
			double MassInitTOCI;
			double MassInitTOCIIA;
			double MassInitTOCIIB;
			double MassInitTOCIII; 
			
			//天然气比率,相当于文档中的Pg
			double GasRatio; 

			//每单位（kg）原始有机碳质量的生烃量
			double HCGIPerUnitInitTOC_I;
			double HCGIPerUnitInitTOC_IIA;
			double HCGIPerUnitInitTOC_IIB;
			double HCGIPerUnitInitTOC_III; 

			//每单位（kg）原始有机碳质量的生油量
			double OGIPerUnitInitTOC_I;
			double OGIPerUnitInitTOC_IIA;
			double OGIPerUnitInitTOC_IIB;
			double OGIPerUnitInitTOC_III; 

			//每单位（kg）原始有机碳质量的生气量
			double GGIPerUnitInitTOC_I;
			double GGIPerUnitInitTOC_IIA;
			double GGIPerUnitInitTOC_IIB;
			double GGIPerUnitInitTOC_III; 

			//2017/6/27: pointer of another DegradationRate
			DegradationRate *m_other;

			/*!
			*
			**/
			DegradationRate()
			{
				Init();
			}

			/*!
			*
			**/
			void Init()
			{
				NKerogen = 0; //干酪根类型数
				Ratio.clear(); //各种干酪根所占的比例

				NI = 0; //对应于I型干酪根降解率数值的个数
				NIIA = 0; //对应于IIA型干酪根降解率数值的个数
				NIIB = 0; //对应于IIB型干酪根降解率数值的个数
				NIII = 0; //对应于III型干酪根降解率数值的个数
				NGDR = 0; //对应于气降解含量的数值的个数

				DRI.clear();  //DegradationRate Of Type I Kerogen
				RoI.clear();  //对应于DegradationRate Of Type I Kerogen的Ro

				DRIIA.clear();  //DegradationRate Of Type IIA Kerogen
				RoIIA.clear();  //对应于DegradationRate Of Type IIA Kerogen的Ro

				DRIIB.clear();  //DegradationRate Of Type IIB Kerogen
				RoIIB.clear();  //对应于DegradationRate Of Type IIB Kerogen的Ro

				DRIII.clear();  //DegradationRate Of Type III Kerogen
				RoIII.clear();  //对应于DegradationRate Of Type III Kerogen的Ro

				GDR.clear(); //气降解含量
				RoGDR.clear(); //气降解含量对应的Ro%值

				COG = 0; //为油气转化率，一般取值0.96m3/kg ，暂时没用这个转化率，气量也用kg表示

				/////////////////////////////////////////output////////////////////////////////
				//四种不同类型的干酪根单位质量（kg)有机碳降解量
				HCFromDRI = 0;
				HCFromDRIIA = 0;
				HCFromDRIIB = 0;
				HCFromDRIII = 0; 

				//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
				InitTOCI = 0;
				InitTOCIIA = 0;
				InitTOCIIB = 0;
				InitTOCIII = 0; 

				//各组分的原始有机碳在地层段的原始有机碳质量kg
				MassInitTOCI = 0;
				MassInitTOCIIA = 0;
				MassInitTOCIIB = 0;
				MassInitTOCIII = 0; 

				//天然气比率,相当于文档中的Pg
				GasRatio = 0;

				//每单位（kg）原始有机碳质量的生烃量
				HCGIPerUnitInitTOC_I = 0;
				HCGIPerUnitInitTOC_IIA = 0;
				HCGIPerUnitInitTOC_IIB = 0;
				HCGIPerUnitInitTOC_III = 0; 

				//每单位（kg）原始有机碳质量的生油量
				OGIPerUnitInitTOC_I = 0;
				OGIPerUnitInitTOC_IIA = 0;
				OGIPerUnitInitTOC_IIB = 0;
				OGIPerUnitInitTOC_III = 0; 

				//每单位（kg）原始有机碳质量的生气量
				GGIPerUnitInitTOC_I = 0;
				GGIPerUnitInitTOC_IIA = 0;
				GGIPerUnitInitTOC_IIB = 0;
				GGIPerUnitInitTOC_III = 0; 

				//
				m_other = 0;
			}

			/*!
			*
			**/
			void Release()
			{
				Ratio.clear();
				
				DRI.clear();
				RoI.clear();
				
				DRIIA.clear();
				RoIIA.clear();

				DRIIB.clear();
				RoIIB.clear();

				DRIII.clear();
				RoIII.clear();

				GDR.clear();
				RoGDR.clear();
			}

			/*!
			*
			**/
			void InitWithRecords()
			{
				Release();
				Init();

				NKerogen=4; //干酪根类型数
				Ratio.resize(NKerogen);//各种干酪根所占的比例
				Ratio[0]=0.2; Ratio[1]=0.3;  Ratio[2]=0.3;  Ratio[3]=0.2;//用户输入，但要保证四者之和为1
				
				//对应于I型干酪根降解率数值的个数
				NI=25; 
				DRI.resize(NI);  //DegradationRate Of Type I Kerogen
				RoI.resize(NI);  //对应于DegradationRate Of Type I Kerogen的Ro
				
				RoI[0]=0.2; RoI[1]=0.311; RoI[2]=0.351;RoI[3]=0.390;RoI[4]=0.455;RoI[5]=0.503;RoI[6]=0.552;RoI[7]=0.617;RoI[8]=0.657;RoI[9]=0.705;RoI[10]=0.754;RoI[11]=0.809;RoI[12]=0.849;
				RoI[13]=0.895;  RoI[14]=0.948;RoI[15]=0.993;RoI[16]=1.034;RoI[17]=1.092;RoI[18]=1.161;RoI[19]=1.224 ;RoI[20]=1.279;RoI[21]=1.351;RoI[22]=1.481;RoI[23]=1.620;RoI[24]=1.783;
				
				DRI[0]=0; DRI[1]=0.31;DRI[2]=1.27;DRI[3]=2.06;DRI[4]=3.47;DRI[5]=4.71;DRI[6]=6.31;DRI[7]=8.82;DRI[8]=10.98;DRI[9]=13.95;DRI[10]=17.64;DRI[11]=22.51;DRI[12]=26.67;
				DRI[13]=31.72;DRI[14]=37.14; DRI[15]=41.75;DRI[16]=45.63;DRI[17]=50.78;DRI[18]=56.47;DRI[19]=60.08;DRI[20]=61.97;DRI[21]=63.67;DRI[22]=65.46;DRI[23]=66.25;DRI[24]=66.41;
				
				//对应于IIA型干酪根降解率数值的个数
				NIIA=26; 
				DRIIA.resize(NIIA);  //DegradationRate Of Type IIA Kerogen
				RoIIA.resize(NIIA);  //对应于DegradationRate Of Type IIA Kerogen的Ro
				
				RoIIA[0]=0.2;RoIIA[1]=0.358;RoIIA[2]=0.406;RoIIA[3]=0.429;RoIIA[4]=0.466;RoIIA[5]=0.515;RoIIA[6]=0.575;RoIIA[7]=0.626;RoIIA[8]=0.683;
				RoIIA[9]=0.730;RoIIA[10]=0.802;RoIIA[11]=0.856;RoIIA[12]=0.901;RoIIA[13]=0.958;RoIIA[14]=1.014;RoIIA[15]=1.051;RoIIA[16]=1.089;RoIIA[17]=1.146;
				RoIIA[18]=1.223;RoIIA[19]=1.286;RoIIA[20]=1.358;RoIIA[21]=1.445;RoIIA[22]=1.565;RoIIA[23]=1.765;RoIIA[24]=2.030;RoIIA[25]=2.448;
				
				DRIIA[0]=0;DRIIA[1]=0.63;DRIIA[2]=1.41;DRIIA[3]=1.85;DRIIA[4]=2.46;DRIIA[5]=3.61;DRIIA[6]=5.49;DRIIA[7]=7.28;DRIIA[8]=9.61;
				DRIIA[9]=11.49;DRIIA[10]=14.82;DRIIA[11]=17.79;DRIIA[12]=20.76;DRIIA[13]=24.73;DRIIA[14]=28.97;DRIIA[15]=31.77;DRIIA[16]=34.39;DRIIA[17]=37.91;
				DRIIA[18]=41.88;DRIIA[19]=43.76;DRIIA[20]=45.20;DRIIA[21]=46.09;DRIIA[22]=46.61;DRIIA[23]=47.03;DRIIA[24]=47.18;DRIIA[25]=47.22;
				
				//对应于IIB型干酪根降解率数值的个数
				NIIB=22; 
				DRIIB.resize(NIIB);  //DegradationRate Of Type IIB Kerogen
				RoIIB.resize(NIIB);  //对应于DegradationRate Of Type IIB Kerogen的Ro
				
				RoIIB[0]=0.2;RoIIB[1]=0.374;RoIIB[2]=0.429;RoIIB[3]=0.477;RoIIB[4]=0.520;RoIIB[5]=0.567;RoIIB[6]=0.619;RoIIB[7]=0.671;RoIIB[8]=0.724;RoIIB[9]=0.792;RoIIB[10]=0.838;
				RoIIB[11]=0.896;RoIIB[12]=0.958;RoIIB[13]=1.038;RoIIB[14]=1.124;RoIIB[15]=1.201;RoIIB[16]=1.261;RoIIB[17]=1.356;RoIIB[18]=1.435;RoIIB[19]=1.595;RoIIB[20]=1.861;RoIIB[21]=2.355;
				
				DRIIB[0]=0;DRIIB[1]=0.62;DRIIB[2]=1.13;DRIIB[3]=1.91;DRIIB[4]=2.71;DRIIB[5]=3.68;DRIIB[6]=5.20;DRIIB[7]=7.17;DRIIB[8]=9.23;DRIIB[9]=11.83;DRIIB[10]=13.63;
				DRIIB[11]=15.79;DRIIB[12]=17.76;DRIIB[13]=20.37;DRIIB[14]=22.97;DRIIB[15]=25.22;DRIIB[16]=26.47;DRIIB[17]=27.45;DRIIB[18]=27.80;DRIIB[19]=28.22;DRIIB[20]=28.36;DRIIB[21]=28.57;
				
				//对应于III型干酪根降解率数值的个数
				NIII=16; 
				DRIII.resize(NIII);  //DegradationRate Of Type III Kerogen
				RoIII.resize(NIII);  //对应于DegradationRate Of Type III Kerogen的Ro
				
				RoIII[0]=0.2;RoIII[1]=0.418;RoIII[2]=0.462;RoIII[3]=0.510;RoIII[4]=0.568;RoIII[5]=0.641;RoIII[6]=0.720;RoIII[7]=0.823;
				RoIII[8]=0.906;RoIII[9]=1.006;RoIII[10]=1.130;RoIII[11]=1.239;RoIII[12]=1.361;RoIII[13]=1.510;RoIII[14]=1.665;RoIII[15]=1.887;
				
				DRIII[0]=0;DRIII[1]=0.228;DRIII[2]=0.745;DRIII[3]=1.444;DRIII[4]=2.502;DRIII[5]=3.738;DRIII[6]=5.066;DRIII[7]=6.390;
				DRIII[8]=7.361;DRIII[9]=8.239;DRIII[10]=9.114;DRIII[11]=9.724;DRIII[12]=10.243;DRIII[13]=10.759;DRIII[14]=11.005;DRIII[15]=11.244;
				
				//对应于气降解含量的数值的个数
				NGDR=21; 
				GDR.resize(NGDR); //气降解含量
				RoGDR.resize(NGDR); //气降解含量对应的Ro%值
				
				RoGDR[0]=0.200;RoGDR[1]=0.221;RoGDR[2]=0.435;RoGDR[3]=0.642;RoGDR[4]=0.823;RoGDR[5]=0.965;RoGDR[6]=1.172;RoGDR[7]=1.340;RoGDR[8]=1.527;RoGDR[9]=1.662;
				RoGDR[10]=1.785;RoGDR[11]=1.913;RoGDR[12]=2.042;RoGDR[13]=2.190;RoGDR[14]=2.337;RoGDR[15]=2.498;RoGDR[16]=2.620;RoGDR[17]=2.736;RoGDR[18]=2.897;RoGDR[19]=3.039;RoGDR[20]=3.201;
				
				GDR[0]=0.0000;GDR[1]=0.0055;GDR[2]=0.0273;GDR[3]=0.0573;GDR[4]=0.0914;GDR[5]=0.1228;GDR[6]=0.1760;GDR[7]=0.2251;GDR[8]=0.2865;GDR[9]=0.3397;
				GDR[10]=0.3874;GDR[11]=0.4461;GDR[12]=0.5075;GDR[13]=0.5894;GDR[14]=0.6780;GDR[15]=0.7667;GDR[16]=0.8349;GDR[17]=0.8868;GDR[18]=0.9482;GDR[19]=0.9850;GDR[20]=1.0000;
				
				//为油气转化率，一般取值0.96m3/kg
				COG=0.96;
			}

			/*!
			*
			**/
			void Construct(int aNKerogen,double *aRatio,int aNI, int aNIIA, int aNIIB,int aNIII, int aNGDR, double *aDRI,double *aRoI,double *aDRIIA, double *aRoIIA,double *aDRIIB, double *aRoIIB,double *aDRIII,double *aRoIII,double *aGDR, double *aRoGDR,double aCOG)
			{
				//
				Release();
				Init();

				//
				NKerogen = aNKerogen;
				if (NKerogen > 0)
				{
					Ratio.resize(NKerogen); 
					for(int i=0;i<NKerogen;i++) 
					{
						Ratio[i]=aRatio[i];
					}
				}
				
				//four kinds of oil Degradation Rate
				NI=aNI;
				if (NI > 0)
				{
					DRI.resize(NI);
					RoI.resize(NI);
					for(int i=0;i<NI;i++)
					{
						DRI[i]=aDRI[i];
						RoI[i]=aRoI[i];
					}
				}
				
				//
				NIIA=aNIIA;
				if (NIIA > 0)
				{
					DRIIA.resize(NIIA);
					RoIIA.resize(NIIA);
					for(int i=0;i<NIIA;i++)
					{
						DRIIA[i]=aDRIIA[i];
						RoIIA[i]=aRoIIA[i];
					}
				}
								
				//
				NIIB=aNIIB;
				if (NIIB > 0)
				{
					DRIIB.resize(NIIB); 
					RoIIB.resize(NIIB); 
					for(int i=0;i<NIIB;i++)
					{
						DRIIB[i]=aDRIIB[i];
						RoIIB[i]=aRoIIB[i];
					}
				}			

				//
				NIII=aNIII;
				if (NIII > 0)
				{
					DRIII.resize(NIII); 
					RoIII.resize(NIII);
					for(int i=0;i<NIII;i++) 
					{
						DRIII[i]=aDRIII[i];
						RoIII[i]=aRoIII[i];
					}
				}
				
				//gas Degradation Rate
				NGDR=aNGDR;
				if (NGDR > 0)
				{
					GDR.resize(NGDR);
					RoGDR.resize(NGDR);
					for(int i=0;i<NGDR;i++) 
					{
						GDR[i]=aGDR[i];
						RoGDR[i]=aRoGDR[i];
					}
				}
												
				//
				COG=aCOG;
			}

			/*!
			*
			**/
			void CopyFrom(DegradationRate *aaDR)
			{
				if (!aaDR)
				{
					return;
				}

				////2017/6/27: another object
				//if (!aaDR->m_other)
				//{
				//	m_other = aaDR;
				//}
				//else
				//{
				//	m_other = aaDR->m_other;
				//}

				//return;

				Release();
				Init();

				NKerogen=aaDR->NKerogen;
				if (NKerogen > 0)
				{
					Ratio.resize(NKerogen);
					for(int i=0;i<NKerogen;i++) 
					{
						Ratio[i] = aaDR->Ratio[i];
					}
				}

				//four kinds of oil Degradation Rate
				NI=aaDR->NI;
				if (NI > 0)
				{
					DRI.resize(NI);
					RoI.resize(NI);
					for(int i=0;i<NI;i++)
					{
						DRI[i]=aaDR->DRI[i];
						RoI[i]=aaDR->RoI[i];
					}
				}

				//
				NIIA=aaDR->NIIA;
				if (NIIA > 0)
				{
					DRIIA.resize(NIIA);
					RoIIA.resize(NIIA);
					for(int i=0;i<NIIA;i++)
					{
						DRIIA[i]=aaDR->DRIIA[i];
						RoIIA[i]=aaDR->RoIIA[i];
					}
				}

				//
				NIIB=aaDR->NIIB;
				if (NIIB > 0)
				{
					DRIIB.resize(NIIB);
					RoIIB.resize(NIIB);
					for(int i=0;i<NIIB;i++)
					{
						DRIIB[i]=aaDR->DRIIB[i];
						RoIIB[i]=aaDR->RoIIB[i];
					}
				}			

				//
				NIII=aaDR->NIII;
				if (NIII > 0)
				{
					DRIII.resize(NIII);
					RoIII.resize(NIII);
					for(int i=0;i<NIII;i++) 
					{
						DRIII[i]=aaDR->DRIII[i];
						RoIII[i]=aaDR->RoIII[i];
					}
				}

				//gas Degradation Rate
				NGDR=aaDR->NGDR;
				if (NGDR > 0)
				{
					GDR.resize(NGDR);
					RoGDR.resize(NGDR);
					for(int i=0;i<NGDR;i++) 
					{
						GDR[i]=aaDR->GDR[i];
						RoGDR[i]=aaDR->RoGDR[i];
					}
				}

				//
				COG=aaDR->COG;
			}

			/*!
			*
			**/
			bool IsRecordChanged(DegradationRate *aaDR)
			{
				if (!aaDR)
				{
					return false;
				}

				//Kerogen ratio
				if (NKerogen != aaDR->NKerogen)
				{
					return true;
				}

				//
				for(int i=0;i<NKerogen;i++) 
				{
					if (Ratio[i] != aaDR->Ratio[i])
					{
						return true;
					}
				}

				//four kinds of oil Degradation Rate
				if (NI != aaDR->NI)
				{
					return true;
				}

				for(int i=0;i<NI;i++)
				{
					if (DRI[i] != aaDR->DRI[i])
					{
						return true;
					}

					if (RoI[i] != aaDR->RoI[i])
					{
						return true;
					}
				}

				//
				if (NIIA != aaDR->NIIA)
				{
					return true;
				}

				for(int i=0;i<NIIA;i++)
				{
					if (DRIIA[i] != aaDR->DRIIA[i])
					{
						return true;
					}

					if (RoIIA[i] != aaDR->RoIIA[i])
					{
						return true;
					}
				}
			
				//
				if (NIIB != aaDR->NIIB)
				{
					return true;
				}

				for(int i=0;i<NIIB;i++)
				{
					if (DRIIB[i] != aaDR->DRIIB[i])
					{
						return true;
					}

					if (RoIIB[i] != aaDR->RoIIB[i])
					{
						return true;
					}
				}
					
				//
				if (NIII != aaDR->NIII)
				{
					return true;
				}

				for(int i=0;i<NIII;i++)
				{
					if (DRIII[i] != aaDR->DRIII[i])
					{
						return true;
					}

					if (RoIII[i] != aaDR->RoIII[i])
					{
						return true;
					}
				}

				//
				if (NGDR != aaDR->NGDR)
				{
					return true;
				}

				for(int i=0;i<NGDR;i++)
				{
					if (GDR[i] != aaDR->GDR[i])
					{
						return true;
					}

					if (RoGDR[i] != aaDR->RoGDR[i])
					{
						return true;
					}
				}


				//
				return COG != aaDR->COG;
			}

			/*!
			*线性插值函数
			**/
			double LinerInterpolate(double t,double t0,double p0,double t1,double p1)
			{
				return p1-(p1-p0)*(t1-t)/(t1-t0);
			}

			/*!
			*get result
			**/
			void GetHCFromDR(double Ro)
			{
				if (!m_other)
				{
					//
					if(Ro<=RoI[0]) HCFromDRI=DRI[0];
					else if(Ro>= RoI[ NI-1])HCFromDRI= DRI[ NI-1];
					else {for(int i=0;i< NI-1;i++) if(Ro> RoI[i]&&Ro<= RoI[i+1]) HCFromDRI=LinerInterpolate(Ro, RoI[i], DRI[i], RoI[i+1], DRI[i+1]);}

					//
					if(Ro<= RoIIA[0]) HCFromDRIIA= DRIIA[0];
					else if(Ro>= RoIIA[ NIIA-1])HCFromDRIIA= DRIIA[ NIIA-1];
					else {for(int i=0;i< NIIA-1;i++) if(Ro> RoIIA[i]&&Ro<= RoIIA[i+1]) HCFromDRIIA=LinerInterpolate(Ro, RoIIA[i], DRIIA[i], RoIIA[i+1], DRIIA[i+1]);}

					//
					if(Ro<= RoIIB[0]) HCFromDRIIB= DRIIB[0];
					else if(Ro>= RoIIB[ NIIB-1])HCFromDRIIB= DRIIB[ NIIB-1];
					else {for(int i=0;i< NIIB-1;i++) if(Ro> RoIIB[i]&&Ro<= RoIIB[i+1]) HCFromDRIIB=LinerInterpolate(Ro, RoIIB[i], DRIIB[i], RoIIB[i+1], DRIIB[i+1]);}

					//
					if(Ro<= RoIII[0]) HCFromDRIIB= DRIII[0];
					else if(Ro>= RoIII[ NIII-1])HCFromDRIII= DRIII[ NIII-1];
					else {for(int i=0;i< NIII-1;i++) if(Ro> RoIII[i]&&Ro<= RoIII[i+1]) HCFromDRIII=LinerInterpolate(Ro, RoIII[i], DRIII[i], RoIII[i+1], DRIII[i+1]);}

					//
					if(Ro<= RoGDR[0]) GasRatio= DRIII[0];
					else if(Ro>= RoGDR[ NGDR-1])GasRatio= GDR[ NGDR-1];
					else {for(int i=0;i< NGDR-1;i++) if(Ro> RoGDR[i]&&Ro<= RoGDR[i+1]) GasRatio=LinerInterpolate(Ro, RoGDR[i], GDR[i], RoGDR[i+1], GDR[i+1]);}
				}
				else
				{
					//
					if(Ro<=m_other->RoI[0]) HCFromDRI = m_other->DRI[0];
					else if(Ro>= m_other->RoI[ m_other->NI-1]) HCFromDRI= m_other->DRI[ m_other->NI-1];
					else {for(int i=0;i< m_other->NI-1;i++) if(Ro> m_other->RoI[i]&&Ro<= m_other->RoI[i+1]) HCFromDRI=LinerInterpolate(Ro, m_other->RoI[i], m_other->DRI[i], m_other->RoI[i+1], m_other->DRI[i+1]);}

					//
					if(Ro<= m_other->RoIIA[0]) HCFromDRIIA= m_other->DRIIA[0];
					else if(Ro>= m_other->RoIIA[ m_other->NIIA-1]) HCFromDRIIA= m_other->DRIIA[ m_other->NIIA-1];
					else {for(int i=0;i< m_other->NIIA-1;i++) if(Ro> m_other->RoIIA[i]&&Ro<= m_other->RoIIA[i+1]) HCFromDRIIA=LinerInterpolate(Ro, m_other->RoIIA[i], m_other->DRIIA[i], m_other->RoIIA[i+1], m_other->DRIIA[i+1]);}

					//
					if(Ro<= m_other->RoIIB[0]) HCFromDRIIB= m_other->DRIIB[0];
					else if(Ro>= m_other->RoIIB[ m_other->NIIB-1])HCFromDRIIB= m_other->DRIIB[ m_other->NIIB-1];
					else {for(int i=0;i< m_other->NIIB-1;i++) if(Ro> m_other->RoIIB[i]&&Ro<= m_other->RoIIB[i+1]) HCFromDRIIB=LinerInterpolate(Ro, m_other->RoIIB[i], m_other->DRIIB[i], m_other->RoIIB[i+1], m_other->DRIIB[i+1]);}

					//
					if(Ro<= m_other->RoIII[0]) HCFromDRIIB= m_other->DRIII[0];
					else if(Ro>= m_other->RoIII[ m_other->NIII-1]) HCFromDRIII= m_other->DRIII[ m_other->NIII-1];
					else {for(int i=0;i< m_other->NIII-1;i++) if(Ro> m_other->RoIII[i]&&Ro<= m_other->RoIII[i+1]) HCFromDRIII=LinerInterpolate(Ro, m_other->RoIII[i], m_other->DRIII[i], m_other->RoIII[i+1], m_other->DRIII[i+1]);}

					//
					if(Ro<= m_other->RoGDR[0]) GasRatio= m_other->DRIII[0];
					else if(Ro>= m_other->RoGDR[ m_other->NGDR-1]) GasRatio= m_other->GDR[ m_other->NGDR-1];
					else {for(int i=0;i< m_other->NGDR-1;i++) if(Ro> m_other->RoGDR[i]&&Ro<= m_other->RoGDR[i+1]) GasRatio=LinerInterpolate(Ro, m_other->RoGDR[i], m_other->GDR[i], m_other->RoGDR[i+1], m_other->GDR[i+1]);}
				}
								
				//
				HCGIPerUnitInitTOC_I=HCFromDRI/100./0.84;  
				HCGIPerUnitInitTOC_IIA=HCFromDRIIA/100./0.84;
				HCGIPerUnitInitTOC_IIB=HCFromDRIIB/100./0.84; 
				HCGIPerUnitInitTOC_III=HCFromDRIII/100./0.84;
				
				//
				OGIPerUnitInitTOC_I=HCGIPerUnitInitTOC_I*(1.0-GasRatio);
				OGIPerUnitInitTOC_IIA=HCGIPerUnitInitTOC_IIA*(1.0-GasRatio);
				OGIPerUnitInitTOC_IIB=HCGIPerUnitInitTOC_IIB*(1.0-GasRatio);
				OGIPerUnitInitTOC_III=HCGIPerUnitInitTOC_III*(1.0-GasRatio);

				//这里的气量也用kg表示，不再乘以COG转化为立方米
				GGIPerUnitInitTOC_I=HCGIPerUnitInitTOC_I*GasRatio;
				GGIPerUnitInitTOC_IIA=HCGIPerUnitInitTOC_IIA*GasRatio;    
				GGIPerUnitInitTOC_IIB=HCGIPerUnitInitTOC_IIB*GasRatio;
				GGIPerUnitInitTOC_III=HCGIPerUnitInitTOC_III*GasRatio;
			}

			/*!
			*2017/6/27: method of getting init toc
			**/
			void GetInitTOC(double TOC, double Thickness,double MatrixDensity, double Poro)  
			{
				if (!m_other)
				{
					InitTOCI = TOC*Ratio[0]/(1.0-HCFromDRI/100.);
					InitTOCIIA = TOC*Ratio[1]/(1.0-HCFromDRIIA/100.);
					InitTOCIIB = TOC*Ratio[2]/(1.0-HCFromDRIIB/100.);
					InitTOCIII = TOC*Ratio[3]/(1.0-HCFromDRIII/100.);
					MassInitTOCI = Thickness*MatrixDensity*(1.0-Poro)*InitTOCI/100.;
					MassInitTOCIIA = Thickness*MatrixDensity*(1.0-Poro)*InitTOCIIA/100.;
					MassInitTOCIIB = Thickness*MatrixDensity*(1.0-Poro)*InitTOCIIB/100.;
					MassInitTOCIII = Thickness*MatrixDensity*(1.0-Poro)*InitTOCIII/100.;
				}
				else
				{  
					InitTOCI = TOC*m_other->Ratio[0]/(1.0-HCFromDRI/100.);
					InitTOCIIA = TOC*m_other->Ratio[1]/(1.0-HCFromDRIIA/100.);
					InitTOCIIB = TOC*m_other->Ratio[2]/(1.0-HCFromDRIIB/100.);
					InitTOCIII = TOC*m_other->Ratio[3]/(1.0-HCFromDRIII/100.);
					MassInitTOCI = Thickness*MatrixDensity*(1.0-Poro)*InitTOCI/100.;
					MassInitTOCIIA = Thickness*MatrixDensity*(1.0-Poro)*InitTOCIIA/100.;
					MassInitTOCIIB = Thickness*MatrixDensity*(1.0-Poro)*InitTOCIIB/100.;
					MassInitTOCIII = Thickness*MatrixDensity*(1.0-Poro)*InitTOCIII/100.;
				}
			}

		};

		/*!
		*2017/6/19: Lawrence Livermore National Laboratories parameter
		**/
		struct KerogenParaLLNL
		{
			/////////////////////////////////////////input//////////////////
			//以下为Lawrence Livermore National Laboratories (LLNL)干酪根反映动力学参数
			int NKerogenType;   //干酪根类型数
			std::vector<double> RatioKerogenType; // 干酪根比例
			std::vector<double> InitTOC;//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
			std::vector<double> MassOfInitTOC; //每种干酪根的原始TOC质量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
			
			//以下为I型干酪根的动力学参数
			double HI_LLNL_I; //I型干酪根的氢指数
			double KSF_LLNL_I;//   Kerogen Start Fraction  LLNL的I型干酪根 反应物干酪根初始量
			double KToOilF_LLNL_I;// 干酪根生成油的比率
			double KToGasF_LLNL_I; //  干酪根生成气的比率
			double OSF_LLNL_I;  // Oil Strat Fraction 反应物（生成物）起始含量
			double OToGasF_LLNL_I; //油生成气的比例
			double OToResidueF_LLNL_I; //油生成残余物的比例

			int N_LLNL_I_KToOil;//LLNL的I型干酪根生油的平行反应活化能数
			std::vector<double> fLLNL_I_KToOil;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> ELLNL_I_KToOil;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_I_KToOil; //Frequency factor  ，即A

			int N_LLNL_I_KToGas;//LLNL的I型干酪根生气的平行反应活化能数
			std::vector<double> fLLNL_I_KToGas;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> ELLNL_I_KToGas;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_I_KToGas; //Frequency factor,频率因子

			int N_LLNL_I_OilToGas;//LLNL的I型干酪根油生成气的反应活化能数
			std::vector<double> fLLNL_I_OilToGas;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> fLLNL_I_OilToGasBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			std::vector<double> ELLNL_I_OilToGas;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_I_OilToGas; //Frequency factor

			int N_LLNL_I_OilToResidue;//LLNL的I型干酪根油生成残余物的反应活化能数
			std::vector<double> fLLNL_I_OilToResidue;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> fLLNL_I_OilToResidueBak;  //备份的计量系数，永远纪录最初始的化学计量系数值
			std::vector<double> ELLNL_I_OilToResidue;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_I_OilToResidue; //Frequency factor
			
			//以下为LLNL II型干酪根参数
			double HI_LLNL_II; //II型干酪根的氢指数
			double KSF_LLNL_II;//   Kerogen Start Fraction  LLNL的II型干酪根 反应物干酪根初始量
			double KToOilF_LLNL_II;// 干酪根生成油的比率
			double KToGasF_LLNL_II; //  干酪根生成气的比率
			double OSF_LLNL_II;  // Oil Strat Fraction 反应物（生成物）起始含量
			double OToGasF_LLNL_II; //油生成气的比例
			double OToResidueF_LLNL_II; //油生成残余物的比例

			int N_LLNL_II_KToOil;//LLNL的II型干酪根生油的平行反应活化能数
			std::vector<double> fLLNL_II_KToOil;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> ELLNL_II_KToOil;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_II_KToOil; //Frequency factor

			int N_LLNL_II_KToGas;//LLNL的II型干酪根生气的平行反应活化能数
			std::vector<double> fLLNL_II_KToGas;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> ELLNL_II_KToGas;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_II_KToGas; //Frequency factor

			int N_LLNL_II_OilToGas;//LLNL的II型干酪根油生成气的反应活化能数
			std::vector<double> fLLNL_II_OilToGas;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> fLLNL_II_OilToGasBak;   //备份的计量系数，永远纪录最初始的化学计量系数值
			std::vector<double> ELLNL_II_OilToGas;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_II_OilToGas; //Frequency factor

			int N_LLNL_II_OilToResidue;//LLNL的II型干酪根油生成残余物的反应活化能数
			std::vector<double> fLLNL_II_OilToResidue;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> fLLNL_II_OilToResidueBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			std::vector<double> ELLNL_II_OilToResidue;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_II_OilToResidue; //Frequency factor

			//以下为LLNL III型干酪根参数
			double HI_LLNL_III; //III型干酪根的氢指数
			double KSF_LLNL_III;//   Kerogen Start Fraction  LLNL的III型干酪根 反应物干酪根初始量
			double KToOilF_LLNL_III;// 干酪根生成油的比率
			double KToGasF_LLNL_III; //  干酪根生成气的比率
			double OSF_LLNL_III;  // Oil Strat Fraction 反应物（生成物）起始含量
			double OToGasF_LLNL_III; //油生成气的比例
			double OToResidueF_LLNL_III; //油生成残余物的比例

			int N_LLNL_III_KToOil;//LLNL的III型干酪根生油的平行反应活化能数
			std::vector<double> fLLNL_III_KToOil;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> ELLNL_III_KToOil;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_III_KToOil; //Frequency factor

			int N_LLNL_III_KToGas;//LLNL的III型干酪根生气的平行反应活化能数
			std::vector<double> fLLNL_III_KToGas;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> ELLNL_III_KToGas;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_III_KToGas; //Frequency factor

			int N_LLNL_III_OilToGas;//LLNL的III型干酪根油生成气的反应活化能数
			std::vector<double> fLLNL_III_OilToGas;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> fLLNL_III_OilToGasBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			std::vector<double> ELLNL_III_OilToGas;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_III_OilToGas; //Frequency factor

			int N_LLNL_III_OilToResidue;//LLNL的III型干酪根油生成残余物的反应活化能数
			std::vector<double> fLLNL_III_OilToResidue;//是化学计量系数（Stoichiometric Factor）
			std::vector<double> fLLNL_III_OilToResidueBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			std::vector<double> ELLNL_III_OilToResidue;//活化能（Activation Energy）（Kcal/mole）
			std::vector<double> FFLLNL_III_OilToResidue; //Frequency factor

			/////////////////////////////////////////output//////////////////
			double wBIw0_I_KToOil,  wBIw0_II_KToOil,  wBIw0_III_KToOil;//分别是I、II、III型干酪根由于生油而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
			double wBIw0_I_KToGas,  wBIw0_II_KToGas,  wBIw0_III_KToGas;//分别是I、II、III型干酪根由于生气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
			double wBIw0_I_OilToGas,  wBIw0_II_OilToGas,  wBIw0_III_OilToGas; //分别是I、II、III型干酪根相关油裂解成气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
			double wBIw0_I_OilToResidue,  wBIw0_II_OilToResidue,  wBIw0_III_OilToResidue; //分别是I、II、III型干酪根相关油裂解成残余物而导致的总的剩余化学计量系数，原始的总的化学计量系数为1

			double wBIw0_I_K,wBIw0_II_K, wBIw0_III_K; //分别是I、II、III型干酪根 总的剩余化学计量系数，原始为1。通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到。
			double OilPerInitTOC_I, OilPerInitTOC_II, OilPerInitTOC_III; //分别是I、II、III型InitTOC在这一时间段的生油量
			double GasPerInitTOC_I, GasPerInitTOC_II, GasPerInitTOC_III; //分别是I、II、III型InitTOC在这一时间段的生气量
			double TOCRemained_I, TOCRemained_II, TOCRemained_III; //每种类型干酪根有机碳剩余量
			double OilCracked_I,OilCracked_II,OilCracked_III; //每种干酪根相关的油在这一时间段的裂解量
			double GasCracked_I,GasCracked_II,GasCracked_III; //每种干酪根相关的油在这一时间段的裂解成气量
			double ResidueCracked_I,ResidueCracked_II,ResidueCracked_III; //每种干酪根相关的油在这一时间段的裂解成残余物量
			double OilExisted_I, OilExisted_II, OilExisted_III;   //每种单位质量原始干酪根生油以及油裂解为气后存在的油
			double GasExisted_I, GasExisted_II, GasExisted_III;   //每种单位质量原始干酪根生气以及油裂解的气
			double ResidueExisted_I, ResidueExisted_II, ResidueExisted_III;   //每种单位质量原始干酪根相关的残余物量
			
			//2017/6/27: another object of ParaLLNL
			KerogenParaLLNL *m_other;

			/*!
			*
			**/
			KerogenParaLLNL()
			{
				Init();
			}

			/*!
			*
			**/
			void Init()
			{
				NKerogenType = 0;   //干酪根类型数
				RatioKerogenType.clear(); // 干酪根比例
				InitTOC.clear();//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
				MassOfInitTOC.clear(); //每种干酪根的原始TOC质量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值

				//以下为I型干酪根的动力学参数
				HI_LLNL_I = 0.; //I型干酪根的氢指数
				KSF_LLNL_I = 0.;//   Kerogen Start Fraction  LLNL的I型干酪根 反应物干酪根初始量
				KToOilF_LLNL_I = 0.;// 干酪根生成油的比率
				KToGasF_LLNL_I = 0.; //  干酪根生成气的比率
				OSF_LLNL_I = 0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				OToGasF_LLNL_I = 0.; //油生成气的比例
				OToResidueF_LLNL_I = 0.; //油生成残余物的比例

				N_LLNL_I_KToOil = 0;//LLNL的I型干酪根生油的平行反应活化能数
				fLLNL_I_KToOil.clear();//是化学计量系数（Stoichiometric Factor）
				ELLNL_I_KToOil.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_I_KToOil.clear(); //Frequency factor  ，即A

				N_LLNL_I_KToGas = 0;//LLNL的I型干酪根生气的平行反应活化能数
				fLLNL_I_KToGas.clear();//是化学计量系数（Stoichiometric Factor）
				ELLNL_I_KToGas.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_I_KToGas.clear(); //Frequency factor,频率因子

				N_LLNL_I_OilToGas = 0;//LLNL的I型干酪根油生成气的反应活化能数
				fLLNL_I_OilToGas.clear();//是化学计量系数（Stoichiometric Factor）
				fLLNL_I_OilToGasBak.clear(); //备份的计量系数，永远纪录最初始的化学计量系数值
				ELLNL_I_OilToGas.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_I_OilToGas.clear(); //Frequency factor

				N_LLNL_I_OilToResidue = 0;//LLNL的I型干酪根油生成残余物的反应活化能数
				fLLNL_I_OilToResidue.clear();//是化学计量系数（Stoichiometric Factor）
				fLLNL_I_OilToResidueBak.clear();  //备份的计量系数，永远纪录最初始的化学计量系数值
				ELLNL_I_OilToResidue.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_I_OilToResidue.clear(); //Frequency factor

				//以下为LLNL II型干酪根参数
				HI_LLNL_II = 0.; //II型干酪根的氢指数
				KSF_LLNL_II = 0.;//   Kerogen Start Fraction  LLNL的II型干酪根 反应物干酪根初始量
				KToOilF_LLNL_II = 0.;// 干酪根生成油的比率
				KToGasF_LLNL_II = 0.; //  干酪根生成气的比率
				OSF_LLNL_II = 0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				OToGasF_LLNL_II = 0.; //油生成气的比例
				OToResidueF_LLNL_II = 0.; //油生成残余物的比例

				N_LLNL_II_KToOil = 0;//LLNL的II型干酪根生油的平行反应活化能数
				fLLNL_II_KToOil.clear();//是化学计量系数（Stoichiometric Factor）
				ELLNL_II_KToOil.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_II_KToOil.clear(); //Frequency factor

				N_LLNL_II_KToGas = 0;//LLNL的II型干酪根生气的平行反应活化能数
				fLLNL_II_KToGas.clear();//是化学计量系数（Stoichiometric Factor）
				ELLNL_II_KToGas.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_II_KToGas.clear(); //Frequency factor

				N_LLNL_II_OilToGas = 0;//LLNL的II型干酪根油生成气的反应活化能数
				fLLNL_II_OilToGas.clear();//是化学计量系数（Stoichiometric Factor）
				fLLNL_II_OilToGasBak.clear();   //备份的计量系数，永远纪录最初始的化学计量系数值
				ELLNL_II_OilToGas.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_II_OilToGas.clear(); //Frequency factor

				N_LLNL_II_OilToResidue = 0;//LLNL的II型干酪根油生成残余物的反应活化能数
				fLLNL_II_OilToResidue.clear();//是化学计量系数（Stoichiometric Factor）
				fLLNL_II_OilToResidueBak.clear(); //备份的计量系数，永远纪录最初始的化学计量系数值
				ELLNL_II_OilToResidue.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_II_OilToResidue.clear(); //Frequency factor

				//以下为LLNL III型干酪根参数
				HI_LLNL_III = 0.; //III型干酪根的氢指数
				KSF_LLNL_III = 0.;//   Kerogen Start Fraction  LLNL的III型干酪根 反应物干酪根初始量
				KToOilF_LLNL_III = 0.;// 干酪根生成油的比率
				KToGasF_LLNL_III = 0.; //  干酪根生成气的比率
				OSF_LLNL_III = 0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				OToGasF_LLNL_III = 0.; //油生成气的比例
				OToResidueF_LLNL_III = 0.; //油生成残余物的比例

				N_LLNL_III_KToOil = 0;//LLNL的III型干酪根生油的平行反应活化能数
				fLLNL_III_KToOil.clear();//是化学计量系数（Stoichiometric Factor）
				ELLNL_III_KToOil.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_III_KToOil.clear(); //Frequency factor

				N_LLNL_III_KToGas = 0;//LLNL的III型干酪根生气的平行反应活化能数
				fLLNL_III_KToGas.clear();//是化学计量系数（Stoichiometric Factor）
				ELLNL_III_KToGas.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_III_KToGas.clear(); //Frequency factor

				N_LLNL_III_OilToGas = 0;//LLNL的III型干酪根油生成气的反应活化能数
				fLLNL_III_OilToGas.clear();//是化学计量系数（Stoichiometric Factor）
				fLLNL_III_OilToGasBak.clear(); //备份的计量系数，永远纪录最初始的化学计量系数值
				ELLNL_III_OilToGas.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_III_OilToGas.clear(); //Frequency factor

				N_LLNL_III_OilToResidue = 0;//LLNL的III型干酪根油生成残余物的反应活化能数
				fLLNL_III_OilToResidue.clear();//是化学计量系数（Stoichiometric Factor）
				fLLNL_III_OilToResidueBak.clear(); //备份的计量系数，永远纪录最初始的化学计量系数值
				ELLNL_III_OilToResidue.clear();//活化能（Activation Energy）（Kcal/mole）
				FFLLNL_III_OilToResidue.clear(); //Frequency factor

				//分别是I、II、III型干酪根由于生油而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				wBIw0_I_KToOil = 0.;
				wBIw0_II_KToOil = 0.;
				wBIw0_III_KToOil = 0.;

				//分别是I、II、III型干酪根由于生气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				wBIw0_I_KToGas = 0.;
				wBIw0_II_KToGas = 0.;
				wBIw0_III_KToGas = 0.;

				//分别是I、II、III型干酪根相关油裂解成气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				wBIw0_I_OilToGas = 0.;
				wBIw0_II_OilToGas = 0.;
				wBIw0_III_OilToGas = 0.; 

				//分别是I、II、III型干酪根相关油裂解成残余物而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				wBIw0_I_OilToResidue = 0.;
				wBIw0_II_OilToResidue = 0.;
				wBIw0_III_OilToResidue = 0.; 

				//分别是I、II、III型干酪根 总的剩余化学计量系数，原始为1。通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到。
				wBIw0_I_K = 0.;
				wBIw0_II_K = 0.;
				wBIw0_III_K = 0.; 

				//分别是I、II、III型InitTOC在这一时间段的生油量
				OilPerInitTOC_I = 0.;
				OilPerInitTOC_II = 0.;
				OilPerInitTOC_III = 0.; 

				//分别是I、II、III型InitTOC在这一时间段的生气量
				GasPerInitTOC_I = 0.;
				GasPerInitTOC_II = 0.;
				GasPerInitTOC_III = 0.;; 

				//每种类型干酪根有机碳剩余量
				TOCRemained_I = 0.;
				TOCRemained_II = 0.;
				TOCRemained_III = 0.;

				//每种干酪根相关的油在这一时间段的裂解量
				OilCracked_I = 0.;
				OilCracked_II = 0.;
				OilCracked_III = 0.; 

				//每种干酪根相关的油在这一时间段的裂解成气量
				GasCracked_I = 0.;
				GasCracked_II = 0.;
				GasCracked_III = 0.;
				
				//每种干酪根相关的油在这一时间段的裂解成残余物量
				ResidueCracked_I = 0.;
				ResidueCracked_II = 0.;
				ResidueCracked_III = 0.; 
				
				//每种单位质量原始干酪根生油以及油裂解为气后存在的油
				OilExisted_I = 0.;
				OilExisted_II = 0.;
				OilExisted_III = 0.;   
				
				//每种单位质量原始干酪根生气以及油裂解的气
				GasExisted_I = 0.;
				GasExisted_II = 0.;
				GasExisted_III = 0.;  
				
				//每种单位质量原始干酪根相关的残余物量
				ResidueExisted_I = 0.;
				ResidueExisted_II = 0.;
				ResidueExisted_III = 0.;  

				//
				m_other = 0;
			}

			/*!
			*
			**/
			void Release()
			{
				Init();
			}

			/*!
			*
			**/
			void InitWithRecords()
			{
				Init();

				NKerogenType=3;   //干酪根类型数
				RatioKerogenType.resize(NKerogenType); // 干酪根比例
				RatioKerogenType[0]=0.2, RatioKerogenType[1]=0.6, RatioKerogenType[2]=0.2;  //这些比例是用户输入的，但要保证三个之和是1
				
				//以下为I型干酪根的动力学参数
				HI_LLNL_I=0.85; //I型干酪根的氢指数
				KSF_LLNL_I=1.0;//   Kerogen Start Fraction  LLNL的I型干酪根 反应物干酪根初始量 
				KToOilF_LLNL_I=0.9;// 干酪根生成油的比率
				KToGasF_LLNL_I=0.1; //  干酪根生成气的比率
				OSF_LLNL_I=0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				OToGasF_LLNL_I=0.5; //油生成气的比例
				OToResidueF_LLNL_I=0.5; //油生成残余物的比例

				//LLNL的I型干酪根生油的平行反应活化能数
				N_LLNL_I_KToOil=3;
				
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_I_KToOil.resize(N_LLNL_I_KToOil);
				fLLNL_I_KToOil[0]=0.07, fLLNL_I_KToOil[1]=0.9, fLLNL_I_KToOil[2]=0.03;
				
				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_I_KToOil.resize(N_LLNL_I_KToOil);
				ELLNL_I_KToOil[0]=49, ELLNL_I_KToOil[1]=53, ELLNL_I_KToOil[2]=54;
				
				FFLLNL_I_KToOil.resize(N_LLNL_I_KToOil); //Frequency factor
				FFLLNL_I_KToOil[0]=5.07e13,FFLLNL_I_KToOil[1]=5.07e13, FFLLNL_I_KToOil[2]=5.07e13;

				N_LLNL_I_KToGas=3;//LLNL的I型干酪根生气的平行反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_I_KToGas.resize(N_LLNL_I_KToGas);
				fLLNL_I_KToGas[0]=0.07, fLLNL_I_KToGas[1]=0.9, fLLNL_I_KToGas[2]=0.03;
				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_I_KToGas.resize(N_LLNL_I_KToGas);
				ELLNL_I_KToGas[0]=49, ELLNL_I_KToGas[1]=53, ELLNL_I_KToGas[2]=54;
				FFLLNL_I_KToGas.resize(N_LLNL_I_KToGas); //Frequency factor,频率因子
				FFLLNL_I_KToGas[0]=5.07e13,FFLLNL_I_KToGas[1]=5.07e13, FFLLNL_I_KToGas[2]=5.07e13;

				N_LLNL_I_OilToGas=1;//LLNL的I型干酪根油生成气的反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_I_OilToGas.resize(N_LLNL_I_OilToGas);
				fLLNL_I_OilToGas[0]=1;
				fLLNL_I_OilToGasBak = fLLNL_I_OilToGas;


				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_I_OilToGas.resize(N_LLNL_I_OilToGas);
				ELLNL_I_OilToGas[0]=54;
				FFLLNL_I_OilToGas.resize(N_LLNL_I_OilToGas); //Frequency factor
				FFLLNL_I_OilToGas[0]=1.014e12;

				N_LLNL_I_OilToResidue=1;//LLNL的I型干酪根油生成残余物的反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue);
				fLLNL_I_OilToResidue[0]=1;
				fLLNL_I_OilToResidueBak = fLLNL_I_OilToResidue;

				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue);
				ELLNL_I_OilToResidue[0]=54;
				FFLLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue); //Frequency factor
				FFLLNL_I_OilToResidue[0]=1.014e12;
				//以下为LLNL II型干酪根参数
				HI_LLNL_II=0.65; //II型干酪根的氢指数
				KSF_LLNL_II=1.0;//   Kerogen Start Fraction  LLNL的II型干酪根 反应物干酪根初始量
				KToOilF_LLNL_II=0.84;// 干酪根生成油的比率
				KToGasF_LLNL_II=0.16; //  干酪根生成气的比率
				OSF_LLNL_II=0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				OToGasF_LLNL_II=0.5; //油生成气的比例
				OToResidueF_LLNL_II=0.5; //油生成残余物的比例

				N_LLNL_II_KToOil=5;//LLNL的II型干酪根生油的平行反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_II_KToOil.resize(N_LLNL_II_KToOil);
				fLLNL_II_KToOil[0]=0.05, fLLNL_II_KToOil[1]=0.2, fLLNL_II_KToOil[2]=0.5, fLLNL_II_KToOil[3]=0.2, fLLNL_II_KToOil[4]=0.05;

				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_II_KToOil.resize(N_LLNL_II_KToOil);
				ELLNL_II_KToOil[0]=49, ELLNL_II_KToOil[1]=50, ELLNL_II_KToOil[2]=51, ELLNL_II_KToOil[3]=52, ELLNL_II_KToOil[4]=53;
				FFLLNL_II_KToOil.resize(N_LLNL_II_KToOil); //Frequency factor
				FFLLNL_II_KToOil[0]=3.01e13,FFLLNL_II_KToOil[1]=3.01e13, FFLLNL_II_KToOil[2]=3.01e13,FFLLNL_II_KToOil[3]=3.01e13,FFLLNL_II_KToOil[4]=3.01e13;

				N_LLNL_II_KToGas=5;//LLNL的II型干酪根生气的平行反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_II_KToGas.resize(N_LLNL_II_KToGas);
				fLLNL_II_KToGas[0]=0.05, fLLNL_II_KToGas[1]=0.2, fLLNL_II_KToGas[2]=0.5, fLLNL_II_KToGas[3]=0.2, fLLNL_II_KToGas[4]=0.05;
				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_II_KToGas.resize(N_LLNL_II_KToGas);
				ELLNL_II_KToGas[0]=49, ELLNL_II_KToGas[1]=50, ELLNL_II_KToGas[2]=51, ELLNL_II_KToGas[3]=52, ELLNL_II_KToGas[4]=53;
				FFLLNL_II_KToGas.resize(N_LLNL_II_KToGas); //Frequency factor
				FFLLNL_II_KToGas[0]=3.01e13,FFLLNL_II_KToGas[1]=3.01e13, FFLLNL_II_KToGas[2]=3.01e13,FFLLNL_II_KToGas[3]=3.01e13,FFLLNL_II_KToGas[4]=3.01e13;

				N_LLNL_II_OilToGas=1;//LLNL的II型干酪根油生成气的反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);
				fLLNL_II_OilToGas[0]=1;
				fLLNL_II_OilToGasBak = fLLNL_II_OilToGas;

				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);
				ELLNL_II_OilToGas[0]=54;
				FFLLNL_II_OilToGas.resize(N_LLNL_II_OilToGas); //Frequency factor
				FFLLNL_II_OilToGas[0]=1.014e12;

				N_LLNL_II_OilToResidue=1;//LLNL的II型干酪根油生成残余物的反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue);
				fLLNL_II_OilToResidue[0]=1;
				fLLNL_II_OilToResidueBak = fLLNL_II_OilToResidue;

				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue);
				ELLNL_II_OilToResidue[0]=54;
				FFLLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue); //Frequency factor
				FFLLNL_II_OilToResidue[0]=1.014e12;

				//以下为LLNL III型干酪根参数
				HI_LLNL_III=0.25; //III型干酪根的氢指数
				KSF_LLNL_III=1.0;//   Kerogen Start Fraction  LLNL的III型干酪根 反应物干酪根初始量
				KToOilF_LLNL_III=0.31;// 干酪根生成油的比率
				KToGasF_LLNL_III=0.69; //  干酪根生成气的比率
				OSF_LLNL_III=0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				OToGasF_LLNL_III=0.5; //油生成气的比例
				OToResidueF_LLNL_III=0.5; //油生成残余物的比例

				N_LLNL_III_KToOil=8;//LLNL的III型干酪根生油的平行反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_III_KToOil.resize(N_LLNL_III_KToOil);
				fLLNL_III_KToOil[0]=0.04, fLLNL_III_KToOil[1]=0.14, fLLNL_III_KToOil[2]=0.32, fLLNL_III_KToOil[3]=0.17, fLLNL_III_KToOil[4]=0.13, fLLNL_III_KToOil[5]=0.1, fLLNL_III_KToOil[6]=0.07, fLLNL_III_KToOil[7]=0.03;
				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_III_KToOil.resize(N_LLNL_III_KToOil);
				ELLNL_III_KToOil[0]=48, ELLNL_III_KToOil[1]=50, ELLNL_III_KToOil[2]=52, ELLNL_III_KToOil[3]=54, ELLNL_III_KToOil[4]=56, ELLNL_III_KToOil[5]=60, ELLNL_III_KToOil[6]=64, ELLNL_III_KToOil[7]=68;
				FFLLNL_III_KToOil.resize(N_LLNL_III_KToOil); //Frequency factor
				FFLLNL_III_KToOil[0]=1.616e13,FFLLNL_III_KToOil[1]=1.616e13, FFLLNL_III_KToOil[2]=1.616e13,FFLLNL_III_KToOil[3]=1.616e13,FFLLNL_III_KToOil[4]=1.616e13, FFLLNL_III_KToOil[5]=1.616e13,FFLLNL_III_KToOil[6]=1.616e13,FFLLNL_III_KToOil[7]=1.616e13;

				N_LLNL_III_KToGas=8;//LLNL的III型干酪根生气的平行反应活化能数
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_III_KToGas.resize(N_LLNL_III_KToGas);
				fLLNL_III_KToGas[0]=0.04, fLLNL_III_KToGas[1]=0.14, fLLNL_III_KToGas[2]=0.32, fLLNL_III_KToGas[3]=0.17, fLLNL_III_KToGas[4]=0.13, fLLNL_III_KToGas[5]=0.1, fLLNL_III_KToGas[6]=0.07, fLLNL_III_KToGas[7]=0.03;
				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_III_KToGas.resize(N_LLNL_III_KToGas);
				ELLNL_III_KToGas[0]=48, ELLNL_III_KToGas[1]=50, ELLNL_III_KToGas[2]=52, ELLNL_III_KToGas[3]=54, ELLNL_III_KToGas[4]=56, ELLNL_III_KToGas[5]=60, ELLNL_III_KToGas[6]=64, ELLNL_III_KToGas[7]=68;
				FFLLNL_III_KToGas.resize(N_LLNL_III_KToGas); //Frequency factor
				FFLLNL_III_KToGas[0]=1.616e13,FFLLNL_III_KToGas[1]=1.616e13, FFLLNL_III_KToGas[2]=1.616e13,FFLLNL_III_KToGas[3]=1.616e13,FFLLNL_III_KToGas[4]=1.616e13, FFLLNL_III_KToGas[5]=1.616e13,FFLLNL_III_KToGas[6]=1.616e13,FFLLNL_III_KToGas[7]=1.616e13;

				//LLNL的III型干酪根油生成气的反应活化能数
				N_LLNL_III_OilToGas=1;
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);
				fLLNL_III_OilToGas[0]=1;
				fLLNL_III_OilToGasBak = fLLNL_III_OilToGas;

				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);
				ELLNL_III_OilToGas[0]=54;
				FFLLNL_III_OilToGas.resize(N_LLNL_III_OilToGas); //Frequency factor
				FFLLNL_III_OilToGas[0]=1.014e12;

				//LLNL的III型干酪根油生成残余物的反应活化能数
				N_LLNL_III_OilToResidue=1;
				//是化学计量系数（Stoichiometric Factor）
				fLLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue);
				fLLNL_III_OilToResidue[0]=1;
				fLLNL_III_OilToResidueBak = fLLNL_III_OilToResidue;

				//活化能（Activation Energy）（Kcal/mole）
				ELLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue);
				ELLNL_III_OilToResidue[0]=54;
				FFLLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue); //Frequency factor
				FFLLNL_III_OilToResidue[0]=1.014e12;
			}

			/*!
			*
			**/
			bool IsRecordChanged(KerogenParaLLNL *aParaLLNL)
			{
				if (!aParaLLNL)
				{
					return false;
				}

				//
				if (NKerogenType != aParaLLNL->NKerogenType)
				{
					return true;
				}

				for (int i = 0; i < NKerogenType; i++)
				{
					if (RatioKerogenType[i] != aParaLLNL->RatioKerogenType[i])
					{
						return true;
					}
				}

				//
				if (HI_LLNL_I != aParaLLNL->HI_LLNL_I || KSF_LLNL_I != aParaLLNL->KSF_LLNL_I || KToOilF_LLNL_I != aParaLLNL->KToOilF_LLNL_I || KToGasF_LLNL_I != aParaLLNL->KToGasF_LLNL_I\
					 || OSF_LLNL_I != aParaLLNL->OSF_LLNL_I || OToGasF_LLNL_I != aParaLLNL->OToGasF_LLNL_I || OToResidueF_LLNL_I != aParaLLNL->OToResidueF_LLNL_I)
				{
					return true;
				}

				//
				if (N_LLNL_I_KToOil != aParaLLNL->N_LLNL_I_KToOil)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_I_KToOil; i++)
				{
					if (fLLNL_I_KToOil[i] != aParaLLNL->fLLNL_I_KToOil[i])
					{
						return true;
					}

					if (ELLNL_I_KToOil[i] != aParaLLNL->ELLNL_I_KToOil[i])
					{
						return true;
					}

					if (FFLLNL_I_KToOil[i] != aParaLLNL->FFLLNL_I_KToOil[i])
					{
						return true;
					}
				}

				//
				if (N_LLNL_I_KToGas != aParaLLNL->N_LLNL_I_KToGas)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_I_KToGas; i++)
				{
					if (fLLNL_I_KToGas[i] != aParaLLNL->fLLNL_I_KToGas[i])
					{
						return true;
					}

					if (ELLNL_I_KToGas[i] != aParaLLNL->ELLNL_I_KToGas[i])
					{
						return true;
					}

					if (FFLLNL_I_KToGas[i] != aParaLLNL->FFLLNL_I_KToGas[i])
					{
						return true;
					}
				}

				//
				if (N_LLNL_I_OilToGas != aParaLLNL->N_LLNL_I_OilToGas)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_I_OilToGas; i++)
				{
					if (fLLNL_I_OilToGas[i] != aParaLLNL->fLLNL_I_OilToGas[i])
					{
						return true;
					}

					if (fLLNL_I_OilToGasBak[i] != aParaLLNL->fLLNL_I_OilToGasBak[i])
					{
						return true;
					}

					if (ELLNL_I_OilToGas[i] != aParaLLNL->ELLNL_I_OilToGas[i])
					{
						return true;
					}

					if (FFLLNL_I_OilToGas[i] != aParaLLNL->FFLLNL_I_OilToGas[i])
					{
						return true;
					}
				}

				//
				if (N_LLNL_I_OilToResidue != aParaLLNL->N_LLNL_I_OilToResidue)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_I_OilToResidue; i++)
				{
					if (fLLNL_I_OilToResidue[i] != aParaLLNL->fLLNL_I_OilToResidue[i])
					{
						return true;
					}

					if (fLLNL_I_OilToResidueBak[i] != aParaLLNL->fLLNL_I_OilToResidueBak[i])
					{
						return true;
					}

					if (ELLNL_I_OilToResidue[i] != aParaLLNL->ELLNL_I_OilToResidue[i])
					{
						return true;
					}

					if (FFLLNL_I_OilToResidue[i] != aParaLLNL->FFLLNL_I_OilToResidue[i])
					{
						return true;
					}
				}
				
				//
				if (HI_LLNL_II != aParaLLNL->HI_LLNL_II || KSF_LLNL_II != aParaLLNL->KSF_LLNL_II || KToOilF_LLNL_II != aParaLLNL->KToOilF_LLNL_II || KToGasF_LLNL_II != aParaLLNL->KToGasF_LLNL_II\
					|| OSF_LLNL_II != aParaLLNL->OSF_LLNL_II || OToGasF_LLNL_II != aParaLLNL->OToGasF_LLNL_II || OToResidueF_LLNL_II != aParaLLNL->OToResidueF_LLNL_II)
				{
					return true;
				}

				//
				if (N_LLNL_II_KToOil != aParaLLNL->N_LLNL_II_KToOil)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_II_KToOil; i++)
				{
					if (fLLNL_II_KToOil[i] != aParaLLNL->fLLNL_II_KToOil[i])
					{
						return true;
					}

					if (ELLNL_II_KToOil[i] != aParaLLNL->ELLNL_II_KToOil[i])
					{
						return true;
					}

					if (FFLLNL_II_KToOil[i] != aParaLLNL->FFLLNL_II_KToOil[i])
					{
						return true;
					}
				}

				//
				if (N_LLNL_II_KToGas != aParaLLNL->N_LLNL_II_KToGas)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_II_KToGas; i++)
				{
					if (fLLNL_II_KToGas[i] != aParaLLNL->fLLNL_II_KToGas[i])
					{
						return true;
					}

					if (ELLNL_II_KToGas[i] != aParaLLNL->ELLNL_II_KToGas[i])
					{
						return true;
					}

					if (FFLLNL_II_KToGas[i] != aParaLLNL->FFLLNL_II_KToGas[i])
					{
						return true;
					}
				}

				//
				if (N_LLNL_II_OilToGas != aParaLLNL->N_LLNL_II_OilToGas)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_II_OilToGas; i++)
				{
					if (fLLNL_II_OilToGas[i] != aParaLLNL->fLLNL_II_OilToGas[i])
					{
						return true;
					}

					if (fLLNL_II_OilToGasBak[i] != aParaLLNL->fLLNL_II_OilToGasBak[i])
					{
						return true;
					}

					if (ELLNL_II_OilToGas[i] != aParaLLNL->ELLNL_II_OilToGas[i])
					{
						return true;
					}

					if (FFLLNL_II_OilToGas[i] != aParaLLNL->FFLLNL_II_OilToGas[i])
					{
						return true;
					}
				}

				//
				if (N_LLNL_II_OilToResidue != aParaLLNL->N_LLNL_II_OilToResidue)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_II_OilToResidue; i++)
				{
					if (fLLNL_II_OilToResidue[i] != aParaLLNL->fLLNL_II_OilToResidue[i])
					{
						return true;
					}

					if (fLLNL_II_OilToResidueBak[i] != aParaLLNL->fLLNL_II_OilToResidueBak[i])
					{
						return true;
					}

					if (ELLNL_II_OilToResidue[i] != aParaLLNL->ELLNL_II_OilToResidue[i])
					{
						return true;
					}

					if (FFLLNL_II_OilToResidue[i] != aParaLLNL->FFLLNL_II_OilToResidue[i])
					{
						return true;
					}
				}

				//
				if (HI_LLNL_III != aParaLLNL->HI_LLNL_III || KSF_LLNL_III != aParaLLNL->KSF_LLNL_III || KToOilF_LLNL_III != aParaLLNL->KToOilF_LLNL_III || KToGasF_LLNL_III != aParaLLNL->KToGasF_LLNL_III\
					|| OSF_LLNL_III != aParaLLNL->OSF_LLNL_III || OToGasF_LLNL_III != aParaLLNL->OToGasF_LLNL_III || OToResidueF_LLNL_III != aParaLLNL->OToResidueF_LLNL_III)
				{
					return true;
				}

				//
				if (N_LLNL_III_KToOil != aParaLLNL->N_LLNL_III_KToOil)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_III_KToOil; i++)
				{
					if (fLLNL_III_KToOil[i] != aParaLLNL->fLLNL_III_KToOil[i])
					{
						return true;
					}

					if (ELLNL_III_KToOil[i] != aParaLLNL->ELLNL_III_KToOil[i])
					{
						return true;
					}

					if (FFLLNL_III_KToOil[i] != aParaLLNL->FFLLNL_III_KToOil[i])
					{
						return true;
					}
				}
				
				//
				if (N_LLNL_III_KToGas != aParaLLNL->N_LLNL_III_KToGas)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_III_KToGas; i++)
				{
					if (fLLNL_III_KToGas[i] != aParaLLNL->fLLNL_III_KToGas[i])
					{
						return true;
					}

					if (ELLNL_III_KToGas[i] != aParaLLNL->ELLNL_III_KToGas[i])
					{
						return true;
					}

					if (FFLLNL_III_KToGas[i] != aParaLLNL->FFLLNL_III_KToGas[i])
					{
						return true;
					}
				}
				
				//
				if (N_LLNL_III_OilToGas != aParaLLNL->N_LLNL_III_OilToGas)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_III_OilToGas; i++)
				{
					if (fLLNL_III_OilToGas[i] != aParaLLNL->fLLNL_III_OilToGas[i])
					{
						return true;
					}

					if (fLLNL_III_OilToGasBak[i] != aParaLLNL->fLLNL_III_OilToGasBak[i])
					{
						return true;
					}

					if (ELLNL_III_OilToGas[i] != aParaLLNL->ELLNL_III_OilToGas[i])
					{
						return true;
					}

					if (FFLLNL_III_OilToGas[i] != aParaLLNL->FFLLNL_III_OilToGas[i])
					{
						return true;
					}
				}

				//
				if (N_LLNL_III_OilToResidue != aParaLLNL->N_LLNL_III_OilToResidue)
				{
					return true;
				}

				for (int i = 0; i < N_LLNL_III_OilToResidue; i++)
				{
					if (fLLNL_III_OilToResidue[i] != aParaLLNL->fLLNL_III_OilToResidue[i])
					{
						return true;
					}

					if (fLLNL_III_OilToResidueBak[i] != aParaLLNL->fLLNL_III_OilToResidueBak[i])
					{
						return true;
					}

					if (ELLNL_III_OilToResidue[i] != aParaLLNL->ELLNL_III_OilToResidue[i])
					{
						return true;
					}

					if (FFLLNL_III_OilToResidue[i] != aParaLLNL->FFLLNL_III_OilToResidue[i])
					{
						return true;
					}
				}

				return false;
			}

			/*!
			*
			**/
			void Construct(int aNKerogenType,double *aRatioKerogenType,double aHI_LLNL_I,double aKSF_LLNL_I,double aKToOilF_LLNL_I,double aKToGasF_LLNL_I,double aOSF_LLNL_I,double aOToGasF_LLNL_I,double aOToResidueF_LLNL_I,
				int aN_LLNL_I_KToOil,double *afLLNL_I_KToOil,double *aELLNL_I_KToOil,double *aFFLLNL_I_KToOil,int aN_LLNL_I_KToGas,double *afLLNL_I_KToGas,double *aELLNL_I_KToGas,double *aFFLLNL_I_KToGas,
				int aN_LLNL_I_OilToGas,double *afLLNL_I_OilToGas,double *aELLNL_I_OilToGas,double *aFFLLNL_I_OilToGas,int aN_LLNL_I_OilToResidue,double *afLLNL_I_OilToResidue,double *aELLNL_I_OilToResidue,double *aFFLLNL_I_OilToResidue,
				double aHI_LLNL_II,double aKSF_LLNL_II,double aKToOilF_LLNL_II,double aKToGasF_LLNL_II,double aOSF_LLNL_II,double aOToGasF_LLNL_II,double aOToResidueF_LLNL_II,
				int aN_LLNL_II_KToOil,double *afLLNL_II_KToOil,double *aELLNL_II_KToOil,double *aFFLLNL_II_KToOil,int aN_LLNL_II_KToGas,double *afLLNL_II_KToGas,double *aELLNL_II_KToGas,double *aFFLLNL_II_KToGas,
				int aN_LLNL_II_OilToGas,double *afLLNL_II_OilToGas,double *aELLNL_II_OilToGas,double *aFFLLNL_II_OilToGas,int aN_LLNL_II_OilToResidue,double *afLLNL_II_OilToResidue,double *aELLNL_II_OilToResidue,double *aFFLLNL_II_OilToResidue,
				double aHI_LLNL_III,double aKSF_LLNL_III,double aKToOilF_LLNL_III,double aKToGasF_LLNL_III,double aOSF_LLNL_III,double aOToGasF_LLNL_III,double aOToResidueF_LLNL_III,
				int aN_LLNL_III_KToOil,double *afLLNL_III_KToOil,double *aELLNL_III_KToOil,double *aFFLLNL_III_KToOil,int aN_LLNL_III_KToGas,double *afLLNL_III_KToGas,double *aELLNL_III_KToGas,double *aFFLLNL_III_KToGas,
				int aN_LLNL_III_OilToGas,double *afLLNL_III_OilToGas,double *aELLNL_III_OilToGas,double *aFFLLNL_III_OilToGas,int aN_LLNL_III_OilToResidue,double *afLLNL_III_OilToResidue,double *aELLNL_III_OilToResidue,double *aFFLLNL_III_OilToResidue )
			{
				Init();

				//
				NKerogenType=aNKerogenType;
				RatioKerogenType.resize(NKerogenType);
				for(int i=0;i<NKerogenType;i++)
				{
					RatioKerogenType[i]=aRatioKerogenType[i];
				}

				//
				HI_LLNL_I=aHI_LLNL_I;KSF_LLNL_I=aKSF_LLNL_I;KToOilF_LLNL_I=aKToOilF_LLNL_I;KToGasF_LLNL_I=aKToGasF_LLNL_I;OSF_LLNL_I=aOSF_LLNL_I;OToGasF_LLNL_I=aOToGasF_LLNL_I;OToResidueF_LLNL_I=aOToResidueF_LLNL_I;
				N_LLNL_I_KToOil=aN_LLNL_I_KToOil; fLLNL_I_KToOil.resize(N_LLNL_I_KToOil); ELLNL_I_KToOil.resize(N_LLNL_I_KToOil);FFLLNL_I_KToOil.resize(N_LLNL_I_KToOil);
				for(int i=0;i< N_LLNL_I_KToOil;i++) {fLLNL_I_KToOil[i]=afLLNL_I_KToOil[i];ELLNL_I_KToOil[i]=aELLNL_I_KToOil[i];FFLLNL_I_KToOil[i]=aFFLLNL_I_KToOil[i];}
				N_LLNL_I_KToGas=aN_LLNL_I_KToGas; fLLNL_I_KToGas.resize(N_LLNL_I_KToGas); ELLNL_I_KToGas.resize(N_LLNL_I_KToGas);FFLLNL_I_KToGas.resize(N_LLNL_I_KToGas);
				for(int i=0;i< N_LLNL_I_KToGas;i++) {fLLNL_I_KToGas[i]=afLLNL_I_KToGas[i];ELLNL_I_KToGas[i]=aELLNL_I_KToGas[i];FFLLNL_I_KToGas[i]=aFFLLNL_I_KToGas[i];}
				N_LLNL_I_OilToGas=aN_LLNL_I_OilToGas;fLLNL_I_OilToGas.resize(N_LLNL_I_OilToGas); fLLNL_I_OilToGasBak.resize(N_LLNL_I_OilToGas);ELLNL_I_OilToGas.resize(N_LLNL_I_OilToGas);FFLLNL_I_OilToGas.resize(N_LLNL_I_OilToGas);
				for(int i=0;i<N_LLNL_I_OilToGas;i++) {fLLNL_I_OilToGas[i]=afLLNL_I_OilToGas[i];fLLNL_I_OilToGasBak[i]=afLLNL_I_OilToGas[i];ELLNL_I_OilToGas[i]=aELLNL_I_OilToGas[i];FFLLNL_I_OilToGas[i]=aFFLLNL_I_OilToGas[i];}
				N_LLNL_I_OilToResidue=aN_LLNL_I_OilToResidue;fLLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue);fLLNL_I_OilToResidueBak.resize(N_LLNL_I_OilToResidue); ELLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue); FFLLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue);
				for(int i=0;i<N_LLNL_I_OilToResidue;i++) {fLLNL_I_OilToResidue[i]=afLLNL_I_OilToResidue[i];fLLNL_I_OilToResidueBak[i]=afLLNL_I_OilToResidue[i];ELLNL_I_OilToResidue[i]=aELLNL_I_OilToResidue[i];FFLLNL_I_OilToResidue[i]=aFFLLNL_I_OilToResidue[i];}

				//
				HI_LLNL_II=aHI_LLNL_II;KSF_LLNL_II=aKSF_LLNL_II;KToOilF_LLNL_II=aKToOilF_LLNL_II;KToGasF_LLNL_II=aKToGasF_LLNL_II;OSF_LLNL_II=aOSF_LLNL_II;OToGasF_LLNL_II=aOToGasF_LLNL_II;OToResidueF_LLNL_II=aOToResidueF_LLNL_II;
				N_LLNL_II_KToOil=aN_LLNL_II_KToOil; fLLNL_II_KToOil.resize(N_LLNL_II_KToOil); ELLNL_II_KToOil.resize(N_LLNL_II_KToOil);FFLLNL_II_KToOil.resize(N_LLNL_II_KToOil);
				for(int i=0;i< N_LLNL_II_KToOil;i++) {fLLNL_II_KToOil[i]=afLLNL_II_KToOil[i];ELLNL_II_KToOil[i]=aELLNL_II_KToOil[i];FFLLNL_II_KToOil[i]=aFFLLNL_II_KToOil[i];}
				N_LLNL_II_KToGas=aN_LLNL_II_KToGas; fLLNL_II_KToGas.resize(N_LLNL_II_KToGas); ELLNL_II_KToGas.resize(N_LLNL_II_KToGas);FFLLNL_II_KToGas.resize(N_LLNL_II_KToGas);
				for(int i=0;i< N_LLNL_II_KToGas;i++) {fLLNL_II_KToGas[i]=afLLNL_II_KToGas[i];ELLNL_II_KToGas[i]=aELLNL_II_KToGas[i];FFLLNL_II_KToGas[i]=aFFLLNL_II_KToGas[i];}
				N_LLNL_II_OilToGas=aN_LLNL_II_OilToGas;fLLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);fLLNL_II_OilToGasBak.resize(N_LLNL_II_OilToGas); ELLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);FFLLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);
				for(int i=0;i<N_LLNL_II_OilToGas;i++) {fLLNL_II_OilToGas[i]=afLLNL_II_OilToGas[i];fLLNL_II_OilToGasBak[i]=afLLNL_II_OilToGas[i];ELLNL_II_OilToGas[i]=aELLNL_II_OilToGas[i];FFLLNL_II_OilToGas[i]=aFFLLNL_II_OilToGas[i];}
				N_LLNL_II_OilToResidue=aN_LLNL_II_OilToResidue;fLLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue);fLLNL_II_OilToResidueBak.resize(N_LLNL_II_OilToResidue); ELLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue); FFLLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue);
				for(int i=0;i<N_LLNL_II_OilToResidue;i++) {fLLNL_II_OilToResidue[i]=afLLNL_II_OilToResidue[i];fLLNL_II_OilToResidueBak[i]=afLLNL_II_OilToResidue[i];ELLNL_II_OilToResidue[i]=aELLNL_II_OilToResidue[i];FFLLNL_II_OilToResidue[i]=aFFLLNL_II_OilToResidue[i];}

				//
				HI_LLNL_III=aHI_LLNL_III;KSF_LLNL_III=aKSF_LLNL_III;KToOilF_LLNL_III=aKToOilF_LLNL_III;KToGasF_LLNL_III=aKToGasF_LLNL_III;OSF_LLNL_III=aOSF_LLNL_III;OToGasF_LLNL_III=aOToGasF_LLNL_III;OToResidueF_LLNL_III=aOToResidueF_LLNL_III;
				N_LLNL_III_KToOil=aN_LLNL_III_KToOil; fLLNL_III_KToOil.resize(N_LLNL_III_KToOil); ELLNL_III_KToOil.resize(N_LLNL_III_KToOil);FFLLNL_III_KToOil.resize(N_LLNL_III_KToOil);
				for(int i=0;i< N_LLNL_III_KToOil;i++) {fLLNL_III_KToOil[i]=afLLNL_III_KToOil[i];ELLNL_III_KToOil[i]=aELLNL_III_KToOil[i];FFLLNL_III_KToOil[i]=aFFLLNL_III_KToOil[i];}
				N_LLNL_III_KToGas=aN_LLNL_III_KToGas; fLLNL_III_KToGas.resize(N_LLNL_III_KToGas); ELLNL_III_KToGas.resize(N_LLNL_III_KToGas);FFLLNL_III_KToGas.resize(N_LLNL_III_KToGas);
				for(int i=0;i< N_LLNL_III_KToGas;i++) {fLLNL_III_KToGas[i]=afLLNL_III_KToGas[i];ELLNL_III_KToGas[i]=aELLNL_III_KToGas[i];FFLLNL_III_KToGas[i]=aFFLLNL_III_KToGas[i];}
				N_LLNL_III_OilToGas=aN_LLNL_III_OilToGas;fLLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);fLLNL_III_OilToGasBak.resize(N_LLNL_III_OilToGas);  ELLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);FFLLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);
				for(int i=0;i<N_LLNL_III_OilToGas;i++) {fLLNL_III_OilToGas[i]=afLLNL_III_OilToGas[i];fLLNL_III_OilToGasBak[i]=afLLNL_III_OilToGas[i];ELLNL_III_OilToGas[i]=aELLNL_III_OilToGas[i];FFLLNL_III_OilToGas[i]=aFFLLNL_III_OilToGas[i];}
				N_LLNL_III_OilToResidue=aN_LLNL_III_OilToResidue;fLLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue);fLLNL_III_OilToResidueBak.resize(N_LLNL_III_OilToResidue); ELLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue); FFLLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue);
				for(int i=0;i<N_LLNL_III_OilToResidue;i++) {fLLNL_III_OilToResidue[i]=afLLNL_III_OilToResidue[i];fLLNL_III_OilToResidueBak[i]=afLLNL_III_OilToResidue[i];ELLNL_III_OilToResidue[i]=aELLNL_III_OilToResidue[i];FFLLNL_III_OilToResidue[i]=aFFLLNL_III_OilToResidue[i];}

			}

			/*!
			*
			**/
			void CopyFrom(KerogenParaLLNL *aParaLLNL, bool is_copy_input = false)
			{   
				if (!aParaLLNL)
				{
					return;
				}

				//2017/6/27: another object
				//if (!aParaLLNL->m_other)
				//{
				//	m_other = aParaLLNL;
				//}
				//else
				//{
				//	m_other = aParaLLNL->m_other;
				//}

				////copy input parameter
				////if (is_copy_input)
				//{
				//	CopyInputPara(aParaLLNL);
				//}

				//return;

				//
				Init();

				//从另一个结构中拷贝一份参数
				NKerogenType=aParaLLNL->NKerogenType;
				RatioKerogenType.resize(NKerogenType);
				for(int i=0;i<NKerogenType;i++) RatioKerogenType[i]=aParaLLNL->RatioKerogenType[i];

				HI_LLNL_I=aParaLLNL->HI_LLNL_I;KSF_LLNL_I=aParaLLNL->KSF_LLNL_I;KToOilF_LLNL_I=aParaLLNL->KToOilF_LLNL_I;KToGasF_LLNL_I=aParaLLNL->KToGasF_LLNL_I;OSF_LLNL_I=aParaLLNL->OSF_LLNL_I;OToGasF_LLNL_I=aParaLLNL->OToGasF_LLNL_I;OToResidueF_LLNL_I=aParaLLNL->OToResidueF_LLNL_I;
				N_LLNL_I_KToOil=aParaLLNL->N_LLNL_I_KToOil; fLLNL_I_KToOil.resize(N_LLNL_I_KToOil); ELLNL_I_KToOil.resize(N_LLNL_I_KToOil);FFLLNL_I_KToOil.resize(N_LLNL_I_KToOil);
				for(int i=0;i< N_LLNL_I_KToOil;i++) {fLLNL_I_KToOil[i]=aParaLLNL->fLLNL_I_KToOil[i];ELLNL_I_KToOil[i]=aParaLLNL->ELLNL_I_KToOil[i];FFLLNL_I_KToOil[i]=aParaLLNL->FFLLNL_I_KToOil[i];}
				N_LLNL_I_KToGas=aParaLLNL->N_LLNL_I_KToGas; fLLNL_I_KToGas.resize(N_LLNL_I_KToGas); ELLNL_I_KToGas.resize(N_LLNL_I_KToGas);FFLLNL_I_KToGas.resize(N_LLNL_I_KToGas);
				for(int i=0;i< N_LLNL_I_KToGas;i++) {fLLNL_I_KToGas[i]=aParaLLNL->fLLNL_I_KToGas[i];ELLNL_I_KToGas[i]=aParaLLNL->ELLNL_I_KToGas[i];FFLLNL_I_KToGas[i]=aParaLLNL->FFLLNL_I_KToGas[i];}
				N_LLNL_I_OilToGas=aParaLLNL->N_LLNL_I_OilToGas;fLLNL_I_OilToGas.resize(N_LLNL_I_OilToGas);fLLNL_I_OilToGasBak.resize(N_LLNL_I_OilToGas); ELLNL_I_OilToGas.resize(N_LLNL_I_OilToGas);FFLLNL_I_OilToGas.resize(N_LLNL_I_OilToGas);
				for(int i=0;i<N_LLNL_I_OilToGas;i++) {fLLNL_I_OilToGas[i]=aParaLLNL->fLLNL_I_OilToGas[i];fLLNL_I_OilToGasBak[i]=aParaLLNL->fLLNL_I_OilToGasBak[i];ELLNL_I_OilToGas[i]=aParaLLNL->ELLNL_I_OilToGas[i];FFLLNL_I_OilToGas[i]=aParaLLNL->FFLLNL_I_OilToGas[i];}
				N_LLNL_I_OilToResidue=aParaLLNL->N_LLNL_I_OilToResidue;fLLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue);fLLNL_I_OilToResidueBak.resize(N_LLNL_I_OilToResidue); ELLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue); FFLLNL_I_OilToResidue.resize(N_LLNL_I_OilToResidue);
				for(int i=0;i<N_LLNL_I_OilToResidue;i++) {fLLNL_I_OilToResidue[i]=aParaLLNL->fLLNL_I_OilToResidue[i];fLLNL_I_OilToResidueBak[i]=aParaLLNL->fLLNL_I_OilToResidueBak[i];ELLNL_I_OilToResidue[i]=aParaLLNL->ELLNL_I_OilToResidue[i];FFLLNL_I_OilToResidue[i]=aParaLLNL->FFLLNL_I_OilToResidue[i];}

				HI_LLNL_II=aParaLLNL->HI_LLNL_II;KSF_LLNL_II=aParaLLNL->KSF_LLNL_II;KToOilF_LLNL_II=aParaLLNL->KToOilF_LLNL_II;KToGasF_LLNL_II=aParaLLNL->KToGasF_LLNL_II;OSF_LLNL_II=aParaLLNL->OSF_LLNL_II;OToGasF_LLNL_II=aParaLLNL->OToGasF_LLNL_II;OToResidueF_LLNL_II=aParaLLNL->OToResidueF_LLNL_II;
				N_LLNL_II_KToOil=aParaLLNL->N_LLNL_II_KToOil; fLLNL_II_KToOil.resize(N_LLNL_II_KToOil); ELLNL_II_KToOil.resize(N_LLNL_II_KToOil);FFLLNL_II_KToOil.resize(N_LLNL_II_KToOil);
				for(int i=0;i< N_LLNL_II_KToOil;i++) {fLLNL_II_KToOil[i]=aParaLLNL->fLLNL_II_KToOil[i];ELLNL_II_KToOil[i]=aParaLLNL->ELLNL_II_KToOil[i];FFLLNL_II_KToOil[i]=aParaLLNL->FFLLNL_II_KToOil[i];}
				N_LLNL_II_KToGas=aParaLLNL->N_LLNL_II_KToGas; fLLNL_II_KToGas.resize(N_LLNL_II_KToGas); ELLNL_II_KToGas.resize(N_LLNL_II_KToGas);FFLLNL_II_KToGas.resize(N_LLNL_II_KToGas);
				for(int i=0;i< N_LLNL_II_KToGas;i++) {fLLNL_II_KToGas[i]=aParaLLNL->fLLNL_II_KToGas[i];ELLNL_II_KToGas[i]=aParaLLNL->ELLNL_II_KToGas[i];FFLLNL_II_KToGas[i]=aParaLLNL->FFLLNL_II_KToGas[i];}
				N_LLNL_II_OilToGas=aParaLLNL->N_LLNL_II_OilToGas;fLLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);fLLNL_II_OilToGasBak.resize(N_LLNL_II_OilToGas);  ELLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);FFLLNL_II_OilToGas.resize(N_LLNL_II_OilToGas);
				for(int i=0;i<N_LLNL_II_OilToGas;i++) {fLLNL_II_OilToGas[i]=aParaLLNL->fLLNL_II_OilToGas[i];fLLNL_II_OilToGasBak[i]=aParaLLNL->fLLNL_II_OilToGasBak[i];ELLNL_II_OilToGas[i]=aParaLLNL->ELLNL_II_OilToGas[i];FFLLNL_II_OilToGas[i]=aParaLLNL->FFLLNL_II_OilToGas[i];}
				N_LLNL_II_OilToResidue=aParaLLNL->N_LLNL_II_OilToResidue;fLLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue);fLLNL_II_OilToResidueBak.resize(N_LLNL_II_OilToResidue);  ELLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue); FFLLNL_II_OilToResidue.resize(N_LLNL_II_OilToResidue);
				for(int i=0;i<N_LLNL_II_OilToResidue;i++) {fLLNL_II_OilToResidue[i]=aParaLLNL->fLLNL_II_OilToResidue[i];fLLNL_II_OilToResidueBak[i]=aParaLLNL->fLLNL_II_OilToResidueBak[i];ELLNL_II_OilToResidue[i]=aParaLLNL->ELLNL_II_OilToResidue[i];FFLLNL_II_OilToResidue[i]=aParaLLNL->FFLLNL_II_OilToResidue[i];}

				HI_LLNL_III=aParaLLNL->HI_LLNL_III;KSF_LLNL_III=aParaLLNL->KSF_LLNL_III;KToOilF_LLNL_III=aParaLLNL->KToOilF_LLNL_III;KToGasF_LLNL_III=aParaLLNL->KToGasF_LLNL_III;OSF_LLNL_III=aParaLLNL->OSF_LLNL_III;OToGasF_LLNL_III=aParaLLNL->OToGasF_LLNL_III;OToResidueF_LLNL_III=aParaLLNL->OToResidueF_LLNL_III;
				N_LLNL_III_KToOil=aParaLLNL->N_LLNL_III_KToOil; fLLNL_III_KToOil.resize(N_LLNL_III_KToOil); ELLNL_III_KToOil.resize(N_LLNL_III_KToOil);FFLLNL_III_KToOil.resize(N_LLNL_III_KToOil);
				for(int i=0;i< N_LLNL_III_KToOil;i++) {fLLNL_III_KToOil[i]=aParaLLNL->fLLNL_III_KToOil[i];ELLNL_III_KToOil[i]=aParaLLNL->ELLNL_III_KToOil[i];FFLLNL_III_KToOil[i]=aParaLLNL->FFLLNL_III_KToOil[i];}
				N_LLNL_III_KToGas=aParaLLNL->N_LLNL_III_KToGas; fLLNL_III_KToGas.resize(N_LLNL_III_KToGas); ELLNL_III_KToGas.resize(N_LLNL_III_KToGas);FFLLNL_III_KToGas.resize(N_LLNL_III_KToGas);
				for(int i=0;i< N_LLNL_III_KToGas;i++) {fLLNL_III_KToGas[i]=aParaLLNL->fLLNL_III_KToGas[i];ELLNL_III_KToGas[i]=aParaLLNL->ELLNL_III_KToGas[i];FFLLNL_III_KToGas[i]=aParaLLNL->FFLLNL_III_KToGas[i];}
				N_LLNL_III_OilToGas=aParaLLNL->N_LLNL_III_OilToGas;fLLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);fLLNL_III_OilToGasBak.resize(N_LLNL_III_OilToGas); ELLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);FFLLNL_III_OilToGas.resize(N_LLNL_III_OilToGas);
				for(int i=0;i<N_LLNL_III_OilToGas;i++) {fLLNL_III_OilToGas[i]=aParaLLNL->fLLNL_III_OilToGas[i];fLLNL_III_OilToGasBak[i]=aParaLLNL->fLLNL_III_OilToGasBak[i];ELLNL_III_OilToGas[i]=aParaLLNL->ELLNL_III_OilToGas[i];FFLLNL_III_OilToGas[i]=aParaLLNL->FFLLNL_III_OilToGas[i];}
				N_LLNL_III_OilToResidue=aParaLLNL->N_LLNL_III_OilToResidue;fLLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue);fLLNL_III_OilToResidueBak.resize(N_LLNL_III_OilToResidue); ELLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue); FFLLNL_III_OilToResidue.resize(N_LLNL_III_OilToResidue);
				for(int i=0;i<N_LLNL_III_OilToResidue;i++) {fLLNL_III_OilToResidue[i]=aParaLLNL->fLLNL_III_OilToResidue[i];fLLNL_III_OilToResidueBak[i]=aParaLLNL->fLLNL_III_OilToResidueBak[i];ELLNL_III_OilToResidue[i]=aParaLLNL->ELLNL_III_OilToResidue[i];FFLLNL_III_OilToResidue[i]=aParaLLNL->FFLLNL_III_OilToResidue[i];}
			}

			/*!
			*
			**/
			void CopyInputPara(KerogenParaLLNL *aParaLLNL)
			{
				if (!aParaLLNL)
				{
					return;
				}
						
				//Stoichiometric Factor
				//I
				N_LLNL_I_KToOil = aParaLLNL->N_LLNL_I_KToOil;
				fLLNL_I_KToOil = aParaLLNL->fLLNL_I_KToOil;

				N_LLNL_I_KToGas = aParaLLNL->N_LLNL_I_KToGas;
				fLLNL_I_KToGas = aParaLLNL->fLLNL_I_KToGas;

				N_LLNL_I_OilToGas = aParaLLNL->N_LLNL_I_OilToGas;
				fLLNL_I_OilToGas = aParaLLNL->fLLNL_I_OilToGas;
				//fLLNL_I_OilToGasBak = aParaLLNL->fLLNL_III_OilToGasBak;

				N_LLNL_I_OilToResidue = aParaLLNL->N_LLNL_I_OilToResidue;
				fLLNL_I_OilToResidue = aParaLLNL->fLLNL_I_OilToResidue;
				//fLLNL_I_OilToResidueBak = aParaLLNL->fLLNL_III_OilToResidueBak;

				//II
				N_LLNL_II_KToOil = aParaLLNL->N_LLNL_II_KToOil;
				fLLNL_II_KToOil = aParaLLNL->fLLNL_II_KToOil;

				N_LLNL_II_KToGas = aParaLLNL->N_LLNL_II_KToGas;
				fLLNL_II_KToGas = aParaLLNL->fLLNL_II_KToGas;

				N_LLNL_II_OilToGas = aParaLLNL->N_LLNL_II_OilToGas;
				fLLNL_II_OilToGas = aParaLLNL->fLLNL_II_OilToGas;
				//fLLNL_II_OilToGasBak = aParaLLNL->fLLNL_III_OilToGasBak;

				N_LLNL_II_OilToResidue = aParaLLNL->N_LLNL_II_OilToResidue;
				fLLNL_II_OilToResidue = aParaLLNL->fLLNL_II_OilToResidue;
				//fLLNL_II_OilToResidueBak = aParaLLNL->fLLNL_III_OilToResidueBak;

				//III
				N_LLNL_III_KToOil = aParaLLNL->N_LLNL_III_KToOil;
				fLLNL_III_KToOil = aParaLLNL->fLLNL_III_KToOil;

				N_LLNL_III_KToGas = aParaLLNL->N_LLNL_III_KToGas;
				fLLNL_III_KToGas = aParaLLNL->fLLNL_III_KToGas;

				N_LLNL_III_OilToGas = aParaLLNL->N_LLNL_III_OilToGas;
				fLLNL_III_OilToGas = aParaLLNL->fLLNL_III_OilToGas;
				//fLLNL_III_OilToGasBak = aParaLLNL->fLLNL_III_OilToGasBak;

				N_LLNL_III_OilToResidue = aParaLLNL->N_LLNL_III_OilToResidue;
				fLLNL_III_OilToResidue = aParaLLNL->fLLNL_III_OilToResidue;
				//fLLNL_III_OilToResidueBak = aParaLLNL->fLLNL_III_OilToResidueBak;

				//last results as new input
				////I
				//wBIw0_I_KToOil = aParaLLNL->wBIw0_I_KToOil;
				//wBIw0_I_KToGas = aParaLLNL->wBIw0_I_KToGas;
				//OilExisted_I = aParaLLNL->OilExisted_I;
				//GasExisted_I = aParaLLNL->GasExisted_I;
				//ResidueExisted_I = aParaLLNL->ResidueExisted_I;
				//TOCRemained_I = aParaLLNL->TOCRemained_I;
				//wBIw0_I_OilToGas = aParaLLNL->wBIw0_I_OilToGas;
				//wBIw0_I_OilToResidue = aParaLLNL->wBIw0_I_OilToResidue;
				//
				////II
				//wBIw0_II_KToOil = aParaLLNL->wBIw0_II_KToOil;
				//wBIw0_II_KToGas = aParaLLNL->wBIw0_II_KToGas;
				//OilExisted_II = aParaLLNL->OilExisted_II;
				//GasExisted_II = aParaLLNL->GasExisted_II;
				//ResidueExisted_II = aParaLLNL->ResidueExisted_II;
				//TOCRemained_II = aParaLLNL->TOCRemained_II;
				//wBIw0_II_OilToGas = aParaLLNL->wBIw0_II_OilToGas;
				//wBIw0_II_OilToResidue = aParaLLNL->wBIw0_II_OilToResidue;

				////III
				//wBIw0_III_KToOil = aParaLLNL->wBIw0_III_KToOil;
				//wBIw0_III_KToGas = aParaLLNL->wBIw0_III_KToGas;
				//OilExisted_III = aParaLLNL->OilExisted_III;
				//GasExisted_III = aParaLLNL->GasExisted_III;
				//ResidueExisted_III = aParaLLNL->ResidueExisted_III;
				//TOCRemained_III = aParaLLNL->TOCRemained_II;
				//wBIw0_III_OilToGas = aParaLLNL->wBIw0_III_OilToGas;
				//wBIw0_III_OilToResidue = aParaLLNL->wBIw0_III_OilToResidue;
			}

			/*!
			*
			**/
			void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,double *fLLNL,double *FFLLNL, double *ELLNL,double &wBIw0)
			{  //分别是上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma），
				// 平行反应个数N_LLNL，化学计量系数fLLNL,频率因子FFLLNL，活化能ELLNL,总的剩余化学计量系数wBIw0
				wBIw0=0;
				double R=0.001986;//气体常数 ，单位 Kcal/(mol*K)
				//假设在t和tLast间温度T与t呈线性关系，即在T和TLast间线性变化：T=a*tt+b   ,tt是在t和tLast间变化的时间
				double a,b; // 线性变化的系数
				a=(T-TLast)/(t-tLast);b=T-a*t;
				//对于tLast和t之间采用数值积分方法，将期间等分为N个等分，因此Δt=(t-tLast)/N
				int N=int(fabs(T-TLast)/0.5+1); //这样计算是保证在每个计算步下温度变化不超过0.5℃，后面加1是保证至少有1步来执行。
				double Delta_t=(t-tLast)/double(N); //Delta_t在这里是有正负概念的
				double tt1=tLast,tt2,ttM; // 分别是时间段的下端点值、上端点值和中间值,初始的tt1值设在最底端
				double temp=0;
				
				//wi/w0i ,含义见EasyRo推导中的公式（8）
				std::vector<double> wiBIw0i;
				wiBIw0i.resize(N_LLNL);
				
				for(int i=0;i<N_LLNL;i++)
				{
					for(int j=0;j<N;j++)
					{
						tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
						temp+=(-FFLLNL[i]*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
						tt1=tt2;
					}
					wiBIw0i[i]=exp(temp);
					fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //计算这一时间段的化学计量系数
					wBIw0+=fLLNL[i];  // wBIw0为总的化学计量系数剩余值
					tt1=tLast; // 算下一个对应的活化能的wiBIw0i[i]需要将初始时间重置
					temp=0;    //temp重新归零
				}
			}

			/*!
			*
			**/
			void Reactions(double TLast, double tLast, double T, double t,KerogenParaLLNL *aParaLLNL)
			{  // 各干酪根组分、油、气量的变化
				// 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				//aParaLLNL 为上一个时间段的参数结构
				//都是基于单位质量（kg）原始有机碳计算的
				// 计算原理来自PetroMod；参数来源于BasinMod

				if (!aParaLLNL)
				{
					Reactions(TLast,tLast,T,t);
					return;
				}

				TLast+=273;T+=273;   //转化为开氏温度
				tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				t=t*1000000*365*24*3600; //百万年转化为秒

				if (!m_other)
				{
					//以下为I型干酪根热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil.data(),FFLLNL_I_KToOil.data(),ELLNL_I_KToOil.data(),wBIw0_I_KToOil);  // I型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas.data(),FFLLNL_I_KToGas.data(),ELLNL_I_KToGas.data(),wBIw0_I_KToGas);  // I型干酪根成气热解
					wBIw0_I_K=wBIw0_I_KToOil*KSF_LLNL_I*KToOilF_LLNL_I +  wBIw0_I_KToGas*KSF_LLNL_I*KToGasF_LLNL_I;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_I=HI_LLNL_I*(aParaLLNL->wBIw0_I_KToOil-wBIw0_I_KToOil)*KSF_LLNL_I*KToOilF_LLNL_I;
					GasPerInitTOC_I=HI_LLNL_I*(aParaLLNL->wBIw0_I_KToGas-wBIw0_I_KToGas)*KSF_LLNL_I*KToGasF_LLNL_I;
					OilExisted_I=aParaLLNL->OilExisted_I+OilPerInitTOC_I; //
					GasExisted_I=aParaLLNL->GasExisted_I+GasPerInitTOC_I; //
					TOCRemained_I=aParaLLNL->TOCRemained_I-OilPerInitTOC_I-GasPerInitTOC_I;
					//以下为II型干酪根热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil.data(),FFLLNL_II_KToOil.data(),ELLNL_II_KToOil.data(),wBIw0_II_KToOil);  // II型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas.data(),FFLLNL_II_KToGas.data(),ELLNL_II_KToGas.data(),wBIw0_II_KToGas);  // II型干酪根成气热解
					wBIw0_II_K=wBIw0_II_KToOil*KSF_LLNL_II*KToOilF_LLNL_II +  wBIw0_II_KToGas*KSF_LLNL_II*KToGasF_LLNL_II;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到
					OilPerInitTOC_II=HI_LLNL_II*(aParaLLNL->wBIw0_II_KToOil-wBIw0_II_KToOil)*KSF_LLNL_II*KToOilF_LLNL_II;
					GasPerInitTOC_II=HI_LLNL_II*(aParaLLNL->wBIw0_II_KToGas-wBIw0_II_KToGas)*KSF_LLNL_II*KToGasF_LLNL_II;
					OilExisted_II=aParaLLNL->OilExisted_II+OilPerInitTOC_II; //
					GasExisted_II=aParaLLNL->GasExisted_II+GasPerInitTOC_II; //
					TOCRemained_II=aParaLLNL->TOCRemained_II-OilPerInitTOC_II-GasPerInitTOC_II;
					//以下为III型干酪根热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil.data(),FFLLNL_III_KToOil.data(),ELLNL_III_KToOil.data(),wBIw0_III_KToOil);  // III型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas.data(),FFLLNL_III_KToGas.data(),ELLNL_III_KToGas.data(),wBIw0_III_KToGas);  // III型干酪根成气热解
					wBIw0_III_K=wBIw0_III_KToOil*KSF_LLNL_III*KToOilF_LLNL_III +  wBIw0_III_KToGas*KSF_LLNL_III*KToGasF_LLNL_III;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到
					OilPerInitTOC_III=HI_LLNL_III*(aParaLLNL->wBIw0_III_KToOil-wBIw0_III_KToOil)*KSF_LLNL_III*KToOilF_LLNL_III;
					GasPerInitTOC_III=HI_LLNL_III*(aParaLLNL->wBIw0_III_KToGas-wBIw0_III_KToGas)*KSF_LLNL_III*KToGasF_LLNL_III;
					OilExisted_III=aParaLLNL->OilExisted_III+OilPerInitTOC_III; //
					GasExisted_III=aParaLLNL->GasExisted_III+GasPerInitTOC_III; //
					TOCRemained_III=aParaLLNL->TOCRemained_III-OilPerInitTOC_III-GasPerInitTOC_III;
					
					//以下为I型干酪根相关油裂解为气和残余物
					for(int i=0;i<N_LLNL_I_OilToGas;i++) fLLNL_I_OilToGas[i]=fLLNL_I_OilToGasBak[i];  //由于油每次裂解都有来自干酪根生成油的补充，因此化学计量系数都赋为初始值
					for(int i=0;i<N_LLNL_I_OilToResidue;i++) fLLNL_I_OilToResidue[i]=fLLNL_I_OilToResidueBak[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas.data(),FFLLNL_I_OilToGas.data(),ELLNL_I_OilToGas.data(),wBIw0_I_OilToGas);  // I型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue.data(),FFLLNL_I_OilToResidue.data(),ELLNL_I_OilToResidue.data(),wBIw0_I_OilToResidue);  // I型干酪根相关油裂解为残余物
					GasCracked_I=aParaLLNL->OilExisted_I*OToGasF_LLNL_I*(aParaLLNL->wBIw0_I_OilToGas-wBIw0_I_OilToGas);
					ResidueCracked_I=aParaLLNL->OilExisted_I*OToResidueF_LLNL_I*(aParaLLNL->wBIw0_I_OilToResidue-wBIw0_I_OilToResidue);
					OilCracked_I=GasCracked_I+ResidueCracked_I;
					OilExisted_I=OilExisted_I-OilCracked_I;
					GasExisted_I=GasExisted_I+GasCracked_I;
					ResidueExisted_I=aParaLLNL->ResidueExisted_I+ResidueCracked_I;
					wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
					for(int i=0;i<N_LLNL_I_OilToGas;i++)  wBIw0_I_OilToGas+=fLLNL_I_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_I_OilToResidue;i++) wBIw0_I_OilToResidue+=fLLNL_I_OilToResidueBak[i]; //每次计算完要将该值归为起始值

					//以下为II型干酪根相关油裂解为气和残余物
					for(int i=0;i<N_LLNL_II_OilToGas;i++) fLLNL_II_OilToGas[i]=fLLNL_II_OilToGasBak[i];  //由于油每次裂解都有来自干酪根生成油的补充，因此化学计量系数都赋为初始值
					for(int i=0;i<N_LLNL_II_OilToResidue;i++) fLLNL_II_OilToResidue[i]=fLLNL_II_OilToResidueBak[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToGas,fLLNL_II_OilToGas.data(),FFLLNL_II_OilToGas.data(),ELLNL_II_OilToGas.data(),wBIw0_II_OilToGas);  // II型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToResidue,fLLNL_II_OilToResidue.data(),FFLLNL_II_OilToResidue.data(),ELLNL_II_OilToResidue.data(),wBIw0_II_OilToResidue);  // II型干酪根相关油裂解为残余物
					GasCracked_II=aParaLLNL->OilExisted_II*OToGasF_LLNL_II*(aParaLLNL->wBIw0_II_OilToGas-wBIw0_II_OilToGas);
					ResidueCracked_II=aParaLLNL->OilExisted_II*OToResidueF_LLNL_II*(aParaLLNL->wBIw0_II_OilToResidue-wBIw0_II_OilToResidue);
					OilCracked_II=GasCracked_II+ResidueCracked_II;
					OilExisted_II=OilExisted_II-OilCracked_II;
					GasExisted_II=GasExisted_II+GasCracked_II;
					ResidueExisted_II=aParaLLNL->ResidueExisted_II+ResidueCracked_II;
					wBIw0_II_OilToGas=0,wBIw0_II_OilToResidue=0;
					for(int i=0;i<N_LLNL_II_OilToGas;i++)  wBIw0_II_OilToGas+=fLLNL_II_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_II_OilToResidue;i++) wBIw0_II_OilToResidue+=fLLNL_II_OilToResidueBak[i]; //每次计算完要将该值归为起始值

					//以下为III型干酪根相关油裂解为气和残余物
					for(int i=0;i<N_LLNL_III_OilToGas;i++) fLLNL_III_OilToGas[i]=fLLNL_III_OilToGasBak[i];  //由于油每次裂解都有来自干酪根生成油的补充，因此化学计量系数都赋为初始值
					for(int i=0;i<N_LLNL_III_OilToResidue;i++) fLLNL_III_OilToResidue[i]=fLLNL_III_OilToResidueBak[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToGas,fLLNL_III_OilToGas.data(),FFLLNL_III_OilToGas.data(),ELLNL_III_OilToGas.data(),wBIw0_III_OilToGas);  // III型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToResidue,fLLNL_III_OilToResidue.data(),FFLLNL_III_OilToResidue.data(),ELLNL_III_OilToResidue.data(),wBIw0_III_OilToResidue);  // III型干酪根相关油裂解为残余物
					GasCracked_III=aParaLLNL->OilExisted_III*OToGasF_LLNL_III*(aParaLLNL->wBIw0_III_OilToGas-wBIw0_III_OilToGas);
					ResidueCracked_III=aParaLLNL->OilExisted_III*OToResidueF_LLNL_III*(aParaLLNL->wBIw0_III_OilToResidue-wBIw0_III_OilToResidue);
					OilCracked_III=GasCracked_III+ResidueCracked_III;
					OilExisted_III=OilExisted_III-OilCracked_III;
					GasExisted_III=GasExisted_III+GasCracked_III;
					ResidueExisted_III=aParaLLNL->ResidueExisted_III+ResidueCracked_III;
					wBIw0_III_OilToGas=0,wBIw0_III_OilToResidue=0;
					for(int i=0;i<N_LLNL_III_OilToGas;i++)  wBIw0_III_OilToGas+=fLLNL_III_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_III_OilToResidue;i++) wBIw0_III_OilToResidue+=fLLNL_III_OilToResidueBak[i]; //每次计算完要将该值归为起始值
				}
				else
				{
					//以下为I型干酪根热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil.data(),m_other->FFLLNL_I_KToOil.data(),m_other->ELLNL_I_KToOil.data(),wBIw0_I_KToOil);  // I型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas.data(),m_other->FFLLNL_I_KToGas.data(),m_other->ELLNL_I_KToGas.data(),wBIw0_I_KToGas);  // I型干酪根成气热解
					
					wBIw0_I_K=wBIw0_I_KToOil*m_other->KSF_LLNL_I*m_other->KToOilF_LLNL_I +  wBIw0_I_KToGas*m_other->KSF_LLNL_I*m_other->KToGasF_LLNL_I;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_I=m_other->HI_LLNL_I*(aParaLLNL->wBIw0_I_KToOil-wBIw0_I_KToOil)*m_other->KSF_LLNL_I*m_other->KToOilF_LLNL_I;
					GasPerInitTOC_I=m_other->HI_LLNL_I*(aParaLLNL->wBIw0_I_KToGas-wBIw0_I_KToGas)*m_other->KSF_LLNL_I*m_other->KToGasF_LLNL_I;
					OilExisted_I=aParaLLNL->OilExisted_I+OilPerInitTOC_I; //
					GasExisted_I=aParaLLNL->GasExisted_I+GasPerInitTOC_I; //
					TOCRemained_I=aParaLLNL->TOCRemained_I-OilPerInitTOC_I-GasPerInitTOC_I;
					
					//以下为II型干酪根热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil.data(),m_other->FFLLNL_II_KToOil.data(),m_other->ELLNL_II_KToOil.data(),wBIw0_II_KToOil);  // II型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas.data(),m_other->FFLLNL_II_KToGas.data(),m_other->ELLNL_II_KToGas.data(),wBIw0_II_KToGas);  // II型干酪根成气热解
					
					wBIw0_II_K=wBIw0_II_KToOil*m_other->KSF_LLNL_II*m_other->KToOilF_LLNL_II +  wBIw0_II_KToGas*m_other->KSF_LLNL_II*m_other->KToGasF_LLNL_II;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到
					OilPerInitTOC_II=m_other->HI_LLNL_II*(aParaLLNL->wBIw0_II_KToOil-wBIw0_II_KToOil)*m_other->KSF_LLNL_II*m_other->KToOilF_LLNL_II;
					GasPerInitTOC_II=m_other->HI_LLNL_II*(aParaLLNL->wBIw0_II_KToGas-wBIw0_II_KToGas)*m_other->KSF_LLNL_II*m_other->KToGasF_LLNL_II;
					OilExisted_II=aParaLLNL->OilExisted_II+OilPerInitTOC_II; //
					GasExisted_II=aParaLLNL->GasExisted_II+GasPerInitTOC_II; //
					TOCRemained_II=aParaLLNL->TOCRemained_II-OilPerInitTOC_II-GasPerInitTOC_II;
					
					//以下为III型干酪根热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil.data(),m_other->FFLLNL_III_KToOil.data(),m_other->ELLNL_III_KToOil.data(),wBIw0_III_KToOil);  // III型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas.data(),m_other->FFLLNL_III_KToGas.data(),m_other->ELLNL_III_KToGas.data(),wBIw0_III_KToGas);  // III型干酪根成气热解
					
					wBIw0_III_K=wBIw0_III_KToOil*m_other->KSF_LLNL_III*m_other->KToOilF_LLNL_III +  wBIw0_III_KToGas*m_other->KSF_LLNL_III*m_other->KToGasF_LLNL_III;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到
					OilPerInitTOC_III=m_other->HI_LLNL_III*(aParaLLNL->wBIw0_III_KToOil-wBIw0_III_KToOil)*m_other->KSF_LLNL_III*m_other->KToOilF_LLNL_III;
					GasPerInitTOC_III=m_other->HI_LLNL_III*(aParaLLNL->wBIw0_III_KToGas-wBIw0_III_KToGas)*m_other->KSF_LLNL_III*m_other->KToGasF_LLNL_III;
					OilExisted_III=aParaLLNL->OilExisted_III+OilPerInitTOC_III; //
					GasExisted_III=aParaLLNL->GasExisted_III+GasPerInitTOC_III; //
					TOCRemained_III=aParaLLNL->TOCRemained_III-OilPerInitTOC_III-GasPerInitTOC_III;

					//以下为I型干酪根相关油裂解为气和残余物
					for(int i=0;i<N_LLNL_I_OilToGas;i++) 
						fLLNL_I_OilToGas[i]=m_other->fLLNL_I_OilToGasBak[i];  //由于油每次裂解都有来自干酪根生成油的补充，因此化学计量系数都赋为初始值
					for(int i=0;i<N_LLNL_I_OilToResidue;i++) 
						fLLNL_I_OilToResidue[i]=m_other->fLLNL_I_OilToResidueBak[i];

					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas.data(),m_other->FFLLNL_I_OilToGas.data(),m_other->ELLNL_I_OilToGas.data(),wBIw0_I_OilToGas);  // I型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue.data(),m_other->FFLLNL_I_OilToResidue.data(),m_other->ELLNL_I_OilToResidue.data(),wBIw0_I_OilToResidue);  // I型干酪根相关油裂解为残余物
					GasCracked_I=aParaLLNL->OilExisted_I*m_other->OToGasF_LLNL_I*(aParaLLNL->wBIw0_I_OilToGas-wBIw0_I_OilToGas);
					ResidueCracked_I=aParaLLNL->OilExisted_I*m_other->OToResidueF_LLNL_I*(aParaLLNL->wBIw0_I_OilToResidue-wBIw0_I_OilToResidue);
					OilCracked_I=GasCracked_I+ResidueCracked_I;
					OilExisted_I=OilExisted_I-OilCracked_I;
					GasExisted_I=GasExisted_I+GasCracked_I;
					ResidueExisted_I=aParaLLNL->ResidueExisted_I+ResidueCracked_I;

					wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
					for(int i=0;i<N_LLNL_I_OilToGas;i++)  
						wBIw0_I_OilToGas+=m_other->fLLNL_I_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_I_OilToResidue;i++) 
						wBIw0_I_OilToResidue+=m_other->fLLNL_I_OilToResidueBak[i]; //每次计算完要将该值归为起始值

					//以下为II型干酪根相关油裂解为气和残余物
					for(int i=0;i<N_LLNL_II_OilToGas;i++) 
						fLLNL_II_OilToGas[i]=m_other->fLLNL_II_OilToGasBak[i];  //由于油每次裂解都有来自干酪根生成油的补充，因此化学计量系数都赋为初始值
					for(int i=0;i<N_LLNL_II_OilToResidue;i++) 
						fLLNL_II_OilToResidue[i]=m_other->fLLNL_II_OilToResidueBak[i];

					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToGas,fLLNL_II_OilToGas.data(),m_other->FFLLNL_II_OilToGas.data(),m_other->ELLNL_II_OilToGas.data(),wBIw0_II_OilToGas);  // II型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToResidue,fLLNL_II_OilToResidue.data(),m_other->FFLLNL_II_OilToResidue.data(),m_other->ELLNL_II_OilToResidue.data(),wBIw0_II_OilToResidue);  // II型干酪根相关油裂解为残余物
					GasCracked_II=aParaLLNL->OilExisted_II*m_other->OToGasF_LLNL_II*(aParaLLNL->wBIw0_II_OilToGas-wBIw0_II_OilToGas);
					ResidueCracked_II=aParaLLNL->OilExisted_II*m_other->OToResidueF_LLNL_II*(aParaLLNL->wBIw0_II_OilToResidue-wBIw0_II_OilToResidue);
					OilCracked_II=GasCracked_II+ResidueCracked_II;
					OilExisted_II=OilExisted_II-OilCracked_II;
					GasExisted_II=GasExisted_II+GasCracked_II;
					ResidueExisted_II=aParaLLNL->ResidueExisted_II+ResidueCracked_II;
					
					wBIw0_II_OilToGas=0,wBIw0_II_OilToResidue=0;
					for(int i=0;i<N_LLNL_II_OilToGas;i++)  
						wBIw0_II_OilToGas+=m_other->fLLNL_II_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_II_OilToResidue;i++) 
						wBIw0_II_OilToResidue+=m_other->fLLNL_II_OilToResidueBak[i]; //每次计算完要将该值归为起始值

					//以下为III型干酪根相关油裂解为气和残余物
					for(int i=0;i<N_LLNL_III_OilToGas;i++) 
						fLLNL_III_OilToGas[i]=m_other->fLLNL_III_OilToGasBak[i];  //由于油每次裂解都有来自干酪根生成油的补充，因此化学计量系数都赋为初始值
					for(int i=0;i<N_LLNL_III_OilToResidue;i++) 
						fLLNL_III_OilToResidue[i]=m_other->fLLNL_III_OilToResidueBak[i];

					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToGas,fLLNL_III_OilToGas.data(),m_other->FFLLNL_III_OilToGas.data(),m_other->ELLNL_III_OilToGas.data(),wBIw0_III_OilToGas);  // III型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToResidue,fLLNL_III_OilToResidue.data(),m_other->FFLLNL_III_OilToResidue.data(),m_other->ELLNL_III_OilToResidue.data(),wBIw0_III_OilToResidue);  // III型干酪根相关油裂解为残余物
					GasCracked_III=aParaLLNL->OilExisted_III*m_other->OToGasF_LLNL_III*(aParaLLNL->wBIw0_III_OilToGas-wBIw0_III_OilToGas);
					ResidueCracked_III=aParaLLNL->OilExisted_III*m_other->OToResidueF_LLNL_III*(aParaLLNL->wBIw0_III_OilToResidue-wBIw0_III_OilToResidue);
					OilCracked_III=GasCracked_III+ResidueCracked_III;
					OilExisted_III=OilExisted_III-OilCracked_III;
					GasExisted_III=GasExisted_III+GasCracked_III;
					ResidueExisted_III=aParaLLNL->ResidueExisted_III+ResidueCracked_III;
					wBIw0_III_OilToGas=0,wBIw0_III_OilToResidue=0;
					for(int i=0;i<N_LLNL_III_OilToGas;i++)  
						wBIw0_III_OilToGas+=m_other->fLLNL_III_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_III_OilToResidue;i++) 
						wBIw0_III_OilToResidue+=m_other->fLLNL_III_OilToResidueBak[i]; //每次计算完要将该值归为起始值
				}
			}

			/*!
			*
			**/
			void Reactions(double TLast, double tLast, double T, double t)
			{  //针对时间上第一个地层段
				// 各干酪根组分、油、气量的变化
				// 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				//aParaLLNL 为上一个时间段的参数结构
				//都是基于单位质量（kg）原始有机碳计算的
				// 计算原理来自PetroMod；参数来源于BasinMod
				TLast+=273;T+=273;   //转化为开氏温度
				tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				t=t*1000000*365*24*3600; //百万年转化为秒
				
				if (!m_other)
				{
					//以下为I型干酪根热解
					double InitwBIw0_I_KToOil=0,InitwBIw0_I_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
					for(int i=0;i<N_LLNL_I_KToOil;i++)InitwBIw0_I_KToOil+=fLLNL_I_KToOil[i]; for(int i=0;i<N_LLNL_I_KToGas;i++)InitwBIw0_I_KToGas+=fLLNL_I_KToGas[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil.data(),FFLLNL_I_KToOil.data(),ELLNL_I_KToOil.data(),wBIw0_I_KToOil);  // I型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas.data(),FFLLNL_I_KToGas.data(),ELLNL_I_KToGas.data(),wBIw0_I_KToGas);  // I型干酪根成气热解
					wBIw0_I_K=wBIw0_I_KToOil*KSF_LLNL_I*KToOilF_LLNL_I +  wBIw0_I_KToGas*KSF_LLNL_I*KToGasF_LLNL_I;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_I=HI_LLNL_I*(InitwBIw0_I_KToOil-wBIw0_I_KToOil)*KSF_LLNL_I*KToOilF_LLNL_I;
					GasPerInitTOC_I=HI_LLNL_I*(InitwBIw0_I_KToGas-wBIw0_I_KToGas)*KSF_LLNL_I*KToGasF_LLNL_I;
					OilExisted_I=OSF_LLNL_I+OilPerInitTOC_I; //
					GasExisted_I=GasPerInitTOC_I; //
					TOCRemained_I=1.-OilPerInitTOC_I-GasPerInitTOC_I;   //初始时刻原始有机碳为1
					//以下为II型干酪根热解
					double InitwBIw0_II_KToOil=0,InitwBIw0_II_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
					for(int i=0;i<N_LLNL_II_KToOil;i++)InitwBIw0_II_KToOil+=fLLNL_II_KToOil[i]; for(int i=0;i<N_LLNL_II_KToGas;i++)InitwBIw0_II_KToGas+=fLLNL_II_KToGas[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil.data(),FFLLNL_II_KToOil.data(),ELLNL_II_KToOil.data(),wBIw0_II_KToOil);  // II型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas.data(),FFLLNL_II_KToGas.data(),ELLNL_II_KToGas.data(),wBIw0_II_KToGas);  // II型干酪根成气热解
					wBIw0_II_K=wBIw0_II_KToOil*KSF_LLNL_II*KToOilF_LLNL_II +  wBIw0_II_KToGas*KSF_LLNL_II*KToGasF_LLNL_II;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_II=HI_LLNL_II*(InitwBIw0_II_KToOil-wBIw0_II_KToOil)*KSF_LLNL_II*KToOilF_LLNL_II;
					GasPerInitTOC_II=HI_LLNL_II*(InitwBIw0_II_KToGas-wBIw0_II_KToGas)*KSF_LLNL_II*KToGasF_LLNL_II;
					OilExisted_II=OSF_LLNL_II+OilPerInitTOC_II; //
					GasExisted_II=GasPerInitTOC_II; //
					TOCRemained_II=1.-OilPerInitTOC_II-GasPerInitTOC_II;   //初始时刻原始有机碳为1
					//以下为III型干酪根热解
					double InitwBIw0_III_KToOil=0,InitwBIw0_III_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
					for(int i=0;i<N_LLNL_III_KToOil;i++)InitwBIw0_III_KToOil+=fLLNL_III_KToOil[i]; for(int i=0;i<N_LLNL_III_KToGas;i++)InitwBIw0_III_KToGas+=fLLNL_III_KToGas[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil.data(),FFLLNL_III_KToOil.data(),ELLNL_III_KToOil.data(),wBIw0_III_KToOil);  // III型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas.data(),FFLLNL_III_KToGas.data(),ELLNL_III_KToGas.data(),wBIw0_III_KToGas);  // III型干酪根成气热解
					wBIw0_III_K=wBIw0_III_KToOil*KSF_LLNL_III*KToOilF_LLNL_III +  wBIw0_III_KToGas*KSF_LLNL_III*KToGasF_LLNL_III;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_III=HI_LLNL_III*(InitwBIw0_III_KToOil-wBIw0_III_KToOil)*KSF_LLNL_III*KToOilF_LLNL_III;
					GasPerInitTOC_III=HI_LLNL_III*(InitwBIw0_III_KToGas-wBIw0_III_KToGas)*KSF_LLNL_III*KToGasF_LLNL_III;
					OilExisted_III=OSF_LLNL_III+OilPerInitTOC_III; // OSF_LLNL_III=0
					GasExisted_III=GasPerInitTOC_III; //
					TOCRemained_III=1.-OilPerInitTOC_III-GasPerInitTOC_III;   //初始时刻原始有机碳为1
					//以下为I型干酪根相关油裂解为气和残余物
					double InitwBIw0_I_OilToGas=0,InitwBIw0_I_OilToResidue=0;  //初始时刻的各油裂解（化学计量系数）之和
					for(int i=0;i<N_LLNL_I_OilToGas;i++)InitwBIw0_I_OilToGas+=fLLNL_I_OilToGas[i]; for(int i=0;i<N_LLNL_I_OilToResidue;i++)InitwBIw0_I_OilToResidue+=fLLNL_I_OilToResidue[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas.data(),FFLLNL_I_OilToGas.data(),ELLNL_I_OilToGas.data(),wBIw0_I_OilToGas);  // I型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue.data(),FFLLNL_I_OilToResidue.data(),ELLNL_I_OilToResidue.data(),wBIw0_I_OilToResidue);  // I型干酪根相关油裂解为残余物
					GasCracked_I=OSF_LLNL_I*OToGasF_LLNL_I*(InitwBIw0_I_OilToGas-wBIw0_I_OilToGas);
					ResidueCracked_I=OSF_LLNL_I*OToResidueF_LLNL_I*(InitwBIw0_I_OilToResidue-wBIw0_I_OilToResidue);
					OilCracked_I=GasCracked_I+ResidueCracked_I;
					OilExisted_I=OSF_LLNL_I-OilCracked_I; //// 这里的Oil Strat Fraction 反应物（生成物）起始含量OSF_LLNL_I =0 ，如果起始含量不为0，就有反应了
					GasExisted_I=0.+GasCracked_I;    //气的起始量为0
					ResidueExisted_I=0.+ResidueCracked_I;//残余物的起始量为0
					wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
					for(int i=0;i<N_LLNL_I_OilToGas;i++)  wBIw0_I_OilToGas+=fLLNL_I_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_I_OilToResidue;i++) wBIw0_I_OilToResidue+=fLLNL_I_OilToResidueBak[i]; //每次计算完要将该值归为起始值
					//以下为II型干酪根相关油裂解为气和残余物
					double InitwBIw0_II_OilToGas=0,InitwBIw0_II_OilToResidue=0;  //初始时刻的各油裂解（化学计量系数）之和
					for(int i=0;i<N_LLNL_II_OilToGas;i++)InitwBIw0_II_OilToGas+=fLLNL_II_OilToGas[i]; for(int i=0;i<N_LLNL_II_OilToResidue;i++)InitwBIw0_II_OilToResidue+=fLLNL_II_OilToResidue[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToGas,fLLNL_II_OilToGas.data(),FFLLNL_II_OilToGas.data(),ELLNL_II_OilToGas.data(),wBIw0_II_OilToGas);  // II型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToResidue,fLLNL_II_OilToResidue.data(),FFLLNL_II_OilToResidue.data(),ELLNL_II_OilToResidue.data(),wBIw0_II_OilToResidue);  // II型干酪根相关油裂解为残余物
					GasCracked_II=OSF_LLNL_II*OToGasF_LLNL_II*(InitwBIw0_II_OilToGas-wBIw0_II_OilToGas);
					ResidueCracked_II=OSF_LLNL_II*OToResidueF_LLNL_II*(InitwBIw0_II_OilToResidue-wBIw0_II_OilToResidue);
					OilCracked_II=GasCracked_II+ResidueCracked_II;
					OilExisted_II=OSF_LLNL_II-OilCracked_II; //// 这里的Oil Strat Fraction 反应物（生成物）起始含量OSF_LLNL_II =0 ，如果起始含量不为0，就有反应了
					GasExisted_II=0.+GasCracked_II;    //气的起始量为0
					ResidueExisted_II=0.+ResidueCracked_II;//残余物的起始量为0
					wBIw0_II_OilToGas=0,wBIw0_II_OilToResidue=0;
					for(int i=0;i<N_LLNL_II_OilToGas;i++)  wBIw0_II_OilToGas+=fLLNL_II_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_II_OilToResidue;i++) wBIw0_II_OilToResidue+=fLLNL_II_OilToResidueBak[i]; //每次计算完要将该值归为起始值
					//以下为III型干酪根相关油裂解为气和残余物
					double InitwBIw0_III_OilToGas=0,InitwBIw0_III_OilToResidue=0;  //初始时刻的各油裂解（化学计量系数）之和
					for(int i=0;i<N_LLNL_III_OilToGas;i++)InitwBIw0_III_OilToGas+=fLLNL_III_OilToGas[i]; for(int i=0;i<N_LLNL_III_OilToResidue;i++)InitwBIw0_III_OilToResidue+=fLLNL_III_OilToResidue[i];
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToGas,fLLNL_III_OilToGas.data(),FFLLNL_III_OilToGas.data(),ELLNL_III_OilToGas.data(),wBIw0_III_OilToGas);  // III型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToResidue,fLLNL_III_OilToResidue.data(),FFLLNL_III_OilToResidue.data(),ELLNL_III_OilToResidue.data(),wBIw0_III_OilToResidue);  // III型干酪根相关油裂解为残余物
					GasCracked_III=OSF_LLNL_III*OToGasF_LLNL_III*(InitwBIw0_III_OilToGas-wBIw0_III_OilToGas);
					ResidueCracked_III=OSF_LLNL_III*OToResidueF_LLNL_III*(InitwBIw0_III_OilToResidue-wBIw0_III_OilToResidue);
					OilCracked_III=GasCracked_III+ResidueCracked_III;
					OilExisted_III=OSF_LLNL_II-OilCracked_III; //// 这里的Oil Strat Fraction 反应物（生成物）起始含量OSF_LLNL_III =0 ，如果起始含量不为0，就有反应了
					GasExisted_III=0.+GasCracked_III;    //气的起始量为0
					ResidueExisted_III=0.+ResidueCracked_III;//残余物的起始量为0
					wBIw0_III_OilToGas=0,wBIw0_III_OilToResidue=0;
					for(int i=0;i<N_LLNL_III_OilToGas;i++)  wBIw0_III_OilToGas+=fLLNL_III_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_III_OilToResidue;i++) wBIw0_III_OilToResidue+=fLLNL_III_OilToResidueBak[i]; //每次计算完要将该值归为起始值
				}
				else
				{
					//以下为I型干酪根热解
					double InitwBIw0_I_KToOil=0,InitwBIw0_I_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
					for(int i=0;i<N_LLNL_I_KToOil;i++)
						InitwBIw0_I_KToOil+=fLLNL_I_KToOil[i]; 
					for(int i=0;i<N_LLNL_I_KToGas;i++)
						InitwBIw0_I_KToGas+=fLLNL_I_KToGas[i];
					
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil.data(),m_other->FFLLNL_I_KToOil.data(),m_other->ELLNL_I_KToOil.data(),wBIw0_I_KToOil);  // I型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas.data(),m_other->FFLLNL_I_KToGas.data(),m_other->ELLNL_I_KToGas.data(),wBIw0_I_KToGas);  // I型干酪根成气热解
					
					wBIw0_I_K=wBIw0_I_KToOil*m_other->KSF_LLNL_I*m_other->KToOilF_LLNL_I +  wBIw0_I_KToGas*m_other->KSF_LLNL_I*m_other->KToGasF_LLNL_I;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_I=m_other->HI_LLNL_I*(InitwBIw0_I_KToOil-wBIw0_I_KToOil)*m_other->KSF_LLNL_I*m_other->KToOilF_LLNL_I;
					GasPerInitTOC_I=m_other->HI_LLNL_I*(InitwBIw0_I_KToGas-wBIw0_I_KToGas)*m_other->KSF_LLNL_I*m_other->KToGasF_LLNL_I;
					OilExisted_I=m_other->OSF_LLNL_I+OilPerInitTOC_I; //
					GasExisted_I=GasPerInitTOC_I; //
					TOCRemained_I=1.-OilPerInitTOC_I-GasPerInitTOC_I;   //初始时刻原始有机碳为1
					
					//以下为II型干酪根热解
					double InitwBIw0_II_KToOil=0,InitwBIw0_II_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
					for(int i=0;i<N_LLNL_II_KToOil;i++)
						InitwBIw0_II_KToOil+=fLLNL_II_KToOil[i]; 
					for(int i=0;i<N_LLNL_II_KToGas;i++)
						InitwBIw0_II_KToGas+=fLLNL_II_KToGas[i];
					
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil.data(),m_other->FFLLNL_II_KToOil.data(),m_other->ELLNL_II_KToOil.data(),wBIw0_II_KToOil);  // II型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas.data(),m_other->FFLLNL_II_KToGas.data(),m_other->ELLNL_II_KToGas.data(),wBIw0_II_KToGas);  // II型干酪根成气热解
					
					wBIw0_II_K=wBIw0_II_KToOil*m_other->KSF_LLNL_II*m_other->KToOilF_LLNL_II +  wBIw0_II_KToGas*m_other->KSF_LLNL_II*m_other->KToGasF_LLNL_II;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_II=m_other->HI_LLNL_II*(InitwBIw0_II_KToOil-wBIw0_II_KToOil)*m_other->KSF_LLNL_II*m_other->KToOilF_LLNL_II;
					GasPerInitTOC_II=m_other->HI_LLNL_II*(InitwBIw0_II_KToGas-wBIw0_II_KToGas)*m_other->KSF_LLNL_II*m_other->KToGasF_LLNL_II;
					OilExisted_II=m_other->OSF_LLNL_II+OilPerInitTOC_II; //
					GasExisted_II=GasPerInitTOC_II; //
					TOCRemained_II=1.-OilPerInitTOC_II-GasPerInitTOC_II;   //初始时刻原始有机碳为1
					
					//以下为III型干酪根热解
					double InitwBIw0_III_KToOil=0,InitwBIw0_III_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
					for(int i=0;i<N_LLNL_III_KToOil;i++)
						InitwBIw0_III_KToOil+=fLLNL_III_KToOil[i]; 
					for(int i=0;i<N_LLNL_III_KToGas;i++)
						InitwBIw0_III_KToGas+=fLLNL_III_KToGas[i];

					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil.data(),m_other->FFLLNL_III_KToOil.data(),m_other->ELLNL_III_KToOil.data(),wBIw0_III_KToOil);  // III型干酪根成油热解
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas.data(),m_other->FFLLNL_III_KToGas.data(),m_other->ELLNL_III_KToGas.data(),wBIw0_III_KToGas);  // III型干酪根成气热解
					
					wBIw0_III_K=wBIw0_III_KToOil*m_other->KSF_LLNL_III*m_other->KToOilF_LLNL_III +  wBIw0_III_KToGas*m_other->KSF_LLNL_III*m_other->KToGasF_LLNL_III;  //通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到,,暂时没有用处
					OilPerInitTOC_III=m_other->HI_LLNL_III*(InitwBIw0_III_KToOil-wBIw0_III_KToOil)*m_other->KSF_LLNL_III*m_other->KToOilF_LLNL_III;
					GasPerInitTOC_III=m_other->HI_LLNL_III*(InitwBIw0_III_KToGas-wBIw0_III_KToGas)*m_other->KSF_LLNL_III*m_other->KToGasF_LLNL_III;
					OilExisted_III=m_other->OSF_LLNL_III+OilPerInitTOC_III; // OSF_LLNL_III=0
					GasExisted_III=GasPerInitTOC_III; //
					TOCRemained_III=1.-OilPerInitTOC_III-GasPerInitTOC_III;   //初始时刻原始有机碳为1

					//以下为I型干酪根相关油裂解为气和残余物
					double InitwBIw0_I_OilToGas=0,InitwBIw0_I_OilToResidue=0;  //初始时刻的各油裂解（化学计量系数）之和
					for(int i=0;i<N_LLNL_I_OilToGas;i++)
						InitwBIw0_I_OilToGas+=fLLNL_I_OilToGas[i]; 
					for(int i=0;i<N_LLNL_I_OilToResidue;i++)
						InitwBIw0_I_OilToResidue+=fLLNL_I_OilToResidue[i];

					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas.data(),m_other->FFLLNL_I_OilToGas.data(),m_other->ELLNL_I_OilToGas.data(),wBIw0_I_OilToGas);  // I型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue.data(),m_other->FFLLNL_I_OilToResidue.data(),m_other->ELLNL_I_OilToResidue.data(),wBIw0_I_OilToResidue);  // I型干酪根相关油裂解为残余物
					GasCracked_I=m_other->OSF_LLNL_I*m_other->OToGasF_LLNL_I*(InitwBIw0_I_OilToGas-wBIw0_I_OilToGas);
					ResidueCracked_I=m_other->OSF_LLNL_I*m_other->OToResidueF_LLNL_I*(InitwBIw0_I_OilToResidue-wBIw0_I_OilToResidue);
					OilCracked_I=GasCracked_I+ResidueCracked_I;
					OilExisted_I=m_other->OSF_LLNL_I-OilCracked_I; //// 这里的Oil Strat Fraction 反应物（生成物）起始含量OSF_LLNL_I =0 ，如果起始含量不为0，就有反应了
					GasExisted_I=0.+GasCracked_I;    //气的起始量为0
					ResidueExisted_I=0.+ResidueCracked_I;//残余物的起始量为0
					
					wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
					for(int i=0;i<N_LLNL_I_OilToGas;i++)  
						wBIw0_I_OilToGas+=m_other->fLLNL_I_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_I_OilToResidue;i++) 
						wBIw0_I_OilToResidue+=m_other->fLLNL_I_OilToResidueBak[i]; //每次计算完要将该值归为起始值
					
					//以下为II型干酪根相关油裂解为气和残余物
					double InitwBIw0_II_OilToGas=0,InitwBIw0_II_OilToResidue=0;  //初始时刻的各油裂解（化学计量系数）之和
					for(int i=0;i<N_LLNL_II_OilToGas;i++)
						InitwBIw0_II_OilToGas+=fLLNL_II_OilToGas[i]; 
					for(int i=0;i<N_LLNL_II_OilToResidue;i++)
						InitwBIw0_II_OilToResidue+=fLLNL_II_OilToResidue[i];
					
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToGas,fLLNL_II_OilToGas.data(),m_other->FFLLNL_II_OilToGas.data(),m_other->ELLNL_II_OilToGas.data(),wBIw0_II_OilToGas);  // II型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_OilToResidue,fLLNL_II_OilToResidue.data(),m_other->FFLLNL_II_OilToResidue.data(),m_other->ELLNL_II_OilToResidue.data(),wBIw0_II_OilToResidue);  // II型干酪根相关油裂解为残余物
					GasCracked_II=m_other->OSF_LLNL_II*m_other->OToGasF_LLNL_II*(InitwBIw0_II_OilToGas-wBIw0_II_OilToGas);
					ResidueCracked_II=m_other->OSF_LLNL_II*m_other->OToResidueF_LLNL_II*(InitwBIw0_II_OilToResidue-wBIw0_II_OilToResidue);
					OilCracked_II=GasCracked_II+ResidueCracked_II;
					OilExisted_II=m_other->OSF_LLNL_II-OilCracked_II; //// 这里的Oil Strat Fraction 反应物（生成物）起始含量OSF_LLNL_II =0 ，如果起始含量不为0，就有反应了
					GasExisted_II=0.+GasCracked_II;    //气的起始量为0
					ResidueExisted_II=0.+ResidueCracked_II;//残余物的起始量为0
					
					wBIw0_II_OilToGas=0,wBIw0_II_OilToResidue=0;
					for(int i=0;i<N_LLNL_II_OilToGas;i++) 
						wBIw0_II_OilToGas+=m_other->fLLNL_II_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_II_OilToResidue;i++) 
						wBIw0_II_OilToResidue+=m_other->fLLNL_II_OilToResidueBak[i]; //每次计算完要将该值归为起始值
					
					//以下为III型干酪根相关油裂解为气和残余物
					double InitwBIw0_III_OilToGas=0,InitwBIw0_III_OilToResidue=0;  //初始时刻的各油裂解（化学计量系数）之和
					for(int i=0;i<N_LLNL_III_OilToGas;i++)
						InitwBIw0_III_OilToGas+=fLLNL_III_OilToGas[i]; 
					for(int i=0;i<N_LLNL_III_OilToResidue;i++)
						InitwBIw0_III_OilToResidue+=fLLNL_III_OilToResidue[i];

					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToGas,fLLNL_III_OilToGas.data(),m_other->FFLLNL_III_OilToGas.data(),m_other->ELLNL_III_OilToGas.data(),wBIw0_III_OilToGas);  // III型干酪根相关油裂解为气
					FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_OilToResidue,fLLNL_III_OilToResidue.data(),m_other->FFLLNL_III_OilToResidue.data(),m_other->ELLNL_III_OilToResidue.data(),wBIw0_III_OilToResidue);  // III型干酪根相关油裂解为残余物
					GasCracked_III=m_other->OSF_LLNL_III*m_other->OToGasF_LLNL_III*(InitwBIw0_III_OilToGas-wBIw0_III_OilToGas);
					ResidueCracked_III=m_other->OSF_LLNL_III*m_other->OToResidueF_LLNL_III*(InitwBIw0_III_OilToResidue-wBIw0_III_OilToResidue);
					OilCracked_III=GasCracked_III+ResidueCracked_III;
					OilExisted_III=m_other->OSF_LLNL_II-OilCracked_III; //// 这里的Oil Strat Fraction 反应物（生成物）起始含量OSF_LLNL_III =0 ，如果起始含量不为0，就有反应了
					GasExisted_III=0.+GasCracked_III;    //气的起始量为0
					ResidueExisted_III=0.+ResidueCracked_III;//残余物的起始量为0
					
					wBIw0_III_OilToGas=0,wBIw0_III_OilToResidue=0;
					for(int i=0;i<N_LLNL_III_OilToGas;i++)  
						wBIw0_III_OilToGas+=m_other->fLLNL_III_OilToGasBak[i];      //每次计算完要将该值归为起始值
					for(int i=0;i<N_LLNL_III_OilToResidue;i++) 
						wBIw0_III_OilToResidue+=m_other->fLLNL_III_OilToResidueBak[i]; //每次计算完要将该值归为起始值
				}
				
			}

			
			/*!
			*2017/6/27: gain init toc
			**/
			void GainInitTOC(double TOC, double Thickness,double MatrixDensity, double Poro)  
			{
				if (!m_other)
				{
					InitTOC.resize(NKerogenType);
					InitTOC[0]=RatioKerogenType[0]*TOC/TOCRemained_I;
					InitTOC[1]=RatioKerogenType[1]*TOC/TOCRemained_II;
					InitTOC[2]=RatioKerogenType[2]*TOC/TOCRemained_III;

					MassOfInitTOC.resize(NKerogenType);
					MassOfInitTOC[0]=Thickness*MatrixDensity*(1.0-Poro)*InitTOC[0]/100.;
					MassOfInitTOC[1]=Thickness*MatrixDensity*(1.0-Poro)*InitTOC[1]/100.;
					MassOfInitTOC[2]=Thickness*MatrixDensity*(1.0-Poro)*InitTOC[2]/100.;
				}
				else
				{
					InitTOC.resize(m_other->NKerogenType);
					InitTOC[0]=m_other->RatioKerogenType[0]*TOC/TOCRemained_I;
					InitTOC[1]=m_other->RatioKerogenType[1]*TOC/TOCRemained_II;
					InitTOC[2]=m_other->RatioKerogenType[2]*TOC/TOCRemained_III;

					MassOfInitTOC.resize(m_other->NKerogenType);
					MassOfInitTOC[0]=Thickness*MatrixDensity*(1.0-Poro)*InitTOC[0]/100.;
					MassOfInitTOC[1]=Thickness*MatrixDensity*(1.0-Poro)*InitTOC[1]/100.;
					MassOfInitTOC[2]=Thickness*MatrixDensity*(1.0-Poro)*InitTOC[2]/100.;
				}
			}
		};

		/*!
		*2017/6/28: Multiple Thread for Calculating CGI
		**/
		class CalculateHCGITask: public CAnySignalTask<void()>,public JTCMonitor
		{
			public:
				CalculateHCGITask(int taskcount,int index, CAnyCPUScheduler *scheduler, CAnyBurialHistoryPlot *hook, const std::string &key);
				~CalculateHCGITask();
				void DoExecuteTask();
			private:
				int m_index;
				int m_taskcount;
				std::string m_key;
				CAnyCPUScheduler *m_scheduler;
				CAnyBurialHistoryPlot *m_hook;
		};
		friend class CalculateHCGITask;

		/*!
		*2017/6/12: source rock record in each grid
		**/
		struct SourceRockRecord
		{
			bool m_isSourceRock;//flag
			CGeoPoint<double> m_pt;//position
			double m_curAge;
			double m_toAge;//the end age of the whole process
			double m_ro;

			double TOC; //残余有机碳含量
			double InitTOC; //原始有机碳含量 ,是在现在的地层条件下的原始有机碳含量，即现今的岩石密度条件 。该数值只有最后一个时间的地层段存在
			double MassOfInitTOC;//该地层段单位面积（m^2）上原始有机碳的总质量 。 该数值只有最后一个时间的地层段存在

			double Thickness;
			double MatrixDensity;
			double Poro;

			//
			DegradationRate aDR;  //定义一个干酪根降解结构体
			double HCGI; //  生烃强度 kg/m^2
			double OGI; //oil generating intensity ,生油强度 kg/m^2
			double GGI; //gas generating intensity ,生气强度 kg/m^2
			
			//
			KerogenParaLLNL aParaLLNL;//(LLNL)干酪根反映动力学参数
			double OGI_LLNL;   //oil generating intensity ,生油强度 kg/m^2  ,用于化学反应动力学生烃模拟
			double GGI_LLNL;   //gas generating intensity ,生气强度 kg/m^2（也用质量单位）  ,用于化学反应动力学生烃模拟

			double TLast;//last temperature
			double tLast;//last age
			double T;//current temperature
			double t;//current age

			/*!
			*
			**/
			SourceRockRecord()
			{
				Init();
			}

			/*!
			*
			**/
			~SourceRockRecord()
			{
				//Release();
			}

			/*!
			*
			**/
			SourceRockRecord(const SourceRockRecord& other)
			{
				Init();
				*this = other;
			}

			/*!
			*
			**/
			const SourceRockRecord&operator=(const SourceRockRecord& other)
			{
				if(this == &other)
				{
					return *this;
				}

				//
				m_isSourceRock = other.m_isSourceRock;
				m_pt = other.m_pt;
				m_curAge = other.m_curAge;
				m_toAge = other.m_toAge;
				m_ro = other.m_ro;

				//
				TOC = other.TOC;
				InitTOC = other.InitTOC;
				MassOfInitTOC = other.MassOfInitTOC;

				//
				Thickness = other.Thickness;
				MatrixDensity = other.MatrixDensity;
				Poro = other.Poro;

				//DegradationRate
				Release();
				aDR.CopyFrom(&(const_cast<SourceRockRecord&>(other).aDR));
				
				//
				HCGI = other.HCGI;
				OGI = other.OGI;
				GGI = other.GGI;

				//ParaLLNL
				aParaLLNL.CopyFrom(&(const_cast<SourceRockRecord&>(other).aParaLLNL));
				OGI_LLNL = other.OGI_LLNL;
				GGI_LLNL = other.GGI_LLNL;

				TLast = other.TLast;//last temperature
				tLast = other.tLast;//last age
				T = other.T;//current temperature
				t = other.t;//current age
			}
			/*!
			*
			**/
			void Init()
			{
				//
				m_isSourceRock = false;
				m_pt.m_x = -1;
				m_pt.m_y = -1;
				
				//
				m_curAge = 0.;
				m_toAge = 0.;
				m_ro = 0.;

				//
				TOC = 0.; 
				InitTOC = 0.;
				MassOfInitTOC = 0.;

				//
				Thickness = 0.;
				MatrixDensity = 0.;
				Poro = 0.;

				//
				Release();
				
				//
				HCGI = 0.;
				OGI = 0.;
				GGI = 0.;

				//
				aParaLLNL.Release();
				OGI_LLNL = 0.;
				GGI_LLNL = 0.;
			}

			/*!
			*
			**/
			void Release()
			{
				aDR.Release();
				aDR.Init();
			}

			/*!
			*获得单位质量原始有机碳的生烃量、生油量和生气量 ,通过有机碳降解率与Ro关系曲线获得；如果一开始就对所有网格的在每一时刻的状态都赋值了，则可以忽略该函数
			**/
			void GetHCGIPerUnitInitTOC(SourceRockRecord *other = 0)
			{   
				//
				if (other)
				{
					aDR.CopyFrom(&other->aDR);
				}

				//
				aDR.GetHCFromDR(m_ro);
			}

			/*!
			*获得原始有机碳含量和质量，用于降解率-Ro方法；在执行操作前，要确保TOC已经赋值
			**/
			void GetInitTOC()  
			{
				//当达到了地层段模拟的最后一个时间点时执行计算
				//if(m_curAge == m_toAge)
				{  
					aDR.GetInitTOC(TOC,Thickness,MatrixDensity,Poro);
				}
			}

			//
			//ParaLLNL
			//
			/*!
			*获得单位质量原始有机碳的生烃量、生油量和生气量 ,通过有机碳降解率与Ro关系曲线获得；如果一开始就对所有网格的在每一时刻的状态都赋值了，则可以忽略该函数
			**/
			void GainHCGIPerUnitInitTOC(SourceRockRecord *other = 0)
			{   
				//
				if (other)
				{
					aParaLLNL.CopyFrom(&other->aParaLLNL,true);
					aParaLLNL.Reactions(other->T, other->t, T, t, &other->aParaLLNL);
				}
				else
				{
					//
					aParaLLNL.Reactions(TLast, tLast, T, t);
				}
			}

			/*!
			*获得原始有机碳含量和质量，用于降解率-Ro方法；在执行操作前，要确保TOC已经赋值
			**/
			void GainInitTOC()  
			{
				//当达到了地层段模拟的最后一个时间点时执行计算
				//if(m_curAge == m_toAge)
				{  
					aParaLLNL.GainInitTOC(TOC,Thickness,MatrixDensity,Poro);
				}
			}
		};
		typedef std::vector<SourceRockRecord> SourceRockRecords;

		/*!
		*2017/3/22: ro type
		**/
		enum RoType
		{
			RO_TTI = 0,
			RO_Simple,
			RO_Easy,
			RO_Basin,
		};

		/*!
		*2017/4/6: parameter for ro setting
		**/
		struct RoPara
		{
			int m_type;

			double f0;//化学计量系数之和
			std::vector<double> f;//化学计量系数（Stoichiometric Factor）
			
			std::vector<double> E;//活化能（Activation Energy）（Kcal/mole）
			
			double A;//频率因子 S^-1
			double Roo;//地表初始时刻的Ro值  Roo=exp(-1.6);
					
			//
			RoPara()
			{				
			}
		};
		typedef std::map<int,RoPara> RoParaMap;

		/*!
		*
		**/
		enum GeologicalVariableType
		{
			GV_Unknown					= 1,
			GV_Temperature				= 1 << 1,
			GV_Temperature_Contour      = 1 << 2,
			GV_RO						= 1 << 3,
			GV_RO_Contour				= 1 << 4,
			
			//2018/2/1: porosity related
			GV_Porosity					= 1 << 5,
			GV_Porosity_Contour			= 1 << 6,
			
			GV_Lithology				= 1 << 7,

			//2017/4/11: show temperature and ro in the mean time
			GV_Ro_TemperatureContour	= 1 << 8,
			GV_Temperature_RoContour	= 1 << 9,
			
		};

		/*!
		*
		**/
		struct GeologicalVariableSliceColor
		{
			unsigned int m_minColor;
			unsigned int m_midColor;
			unsigned int m_maxColor;

			GeologicalVariableSliceColor()
			{
				m_minColor = RGB(0,0,255);
				m_midColor = RGB(255,255,0);
				m_maxColor = RGB(255,0,0);
			}
		};

		/*!
		*
		**/
		enum GeologicalVariableState
		{
			GVS_Unknown = -1,
			GVS_Depositing,
			GVS_Eroded,
			GVS_Max
		};

		/*!
		*
		**/
		struct GeologicalLayerCursor
		{
			GeologicalLayer m_layer;

			//
			std::string m_name;
			double m_top;
			double m_base;
			double m_max_depth;
			CGeoPoint<double> m_pt;

			/*!
			*
			**/
			GeologicalLayerCursor()
			{
				m_name = "";
				m_top = -1.;
				m_base = -1.;
				m_max_depth = -1.;
			}
		};

		/*!
		*
		**/
		struct GeologicalVariableSlice
		{
			// to scan geological variable
			GeologicalVariableType m_type;	
			
			//
			typedef boost::function<double (double,double)> ColorFunction;
			ColorFunction m_function;
		
			// description of this scan line
			GeologicalVariableState m_state;	// current state, depositing or eroded
			double m_age;
			double m_depth_from;
			double m_depth_to;

			//
			double m_minValue;
			double m_maxValue;

			// current layers met with this scan line
			std::vector<GeologicalLayerCursor> m_layers;

			// scan results
			std::map<std::string, std::vector<CGeoPoint<double>>> m_results;

			/*!
			*
			**/
			GeologicalVariableSlice()
			{
				//m_type = GV_Temperature;
				//m_function = boost::bind(&GeologicalVariableSlice::GetColor,this,_1,_2);

				m_age = 0.;
				m_state = GVS_Unknown;
				m_depth_from = 0.;
				m_depth_to = 0.;

				//
				m_minValue = 0x7fffffff;
				m_maxValue = -0x7fffffff;
			}

			/*!
			*
			**/
			GeologicalVariableSlice(const GeologicalVariableSlice& other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const GeologicalVariableSlice&operator=(const GeologicalVariableSlice& other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_type = other.m_type;
				m_function = other.m_function;

				// description of this scan line
				m_age = other.m_age;
				m_state = other.m_state;	// current state, depositing or eroded
				m_depth_from = other.m_depth_from;
				m_depth_to = other.m_depth_to;

				// current layers met with this scan line
				m_layers = other.m_layers;

				// scan results
				m_results = other.m_results;

				//
				m_minValue = other.m_minValue;
				m_maxValue = other.m_maxValue;

				return *this;
			}

			/*!
			*
			**/
			const GeologicalVariableSlice&UpCopyFrom(const GeologicalVariableSlice& anchor)
			{
				// loop each layer, directly copy
				for(int i = 0; i < anchor.m_layers.size(); i++)
				{
					//copy value
					std::string name = anchor.m_layers[i].m_name;

					/////////////////////////////////copy max depth/////////////////////////////////
					int j = 0;
					for (; j < m_layers.size(); j++)
					{
						if (name == m_layers[j].m_name)
						{
							m_layers[j].m_max_depth = anchor.m_layers[i].m_max_depth;
							break;
						}
					}
									
					/////////////////////////////////copy value/////////////////////////////////
					//match name
					std::map<std::string, std::vector<CGeoPoint<double>>>::iterator itr = m_results.find(name);

					//not found
					if (itr == m_results.end())
					{
						continue;
					}

					//anchor result
					std::map<std::string, std::vector<CGeoPoint<double>>>::const_iterator anchoritr = anchor.m_results.find(name);
					if (anchoritr == anchor.m_results.end())
					{
						continue;
					}
					
					int anchorCount = anchoritr->second.size();
					int order = 0;
					
					//from last to first
					j = itr->second.size() - 1;
					for (; j >= 0; j--)
					{
						//from last to first
						int anchorIdx = anchorCount - 1 - order;

						//exception
						if (anchorIdx < 0)
						{
							break;
						}

						//copy value
						itr->second[j].m_z = anchoritr->second[anchorIdx].m_z; 

						//
						order++;
					}
				}

				return *this;
			}

			/*!
			*
			**/
			const GeologicalVariableSlice&DownCopyFrom(const GeologicalVariableSlice& anchor)
			{
				// loop each layer, compare max depth
				// if one layer over current max depth, partially copy end()+shift
				for(int i = 0; i < anchor.m_layers.size(); i++)
				{
					std::string name = anchor.m_layers[i].m_name;

					//match name
					std::map<std::string, std::vector<CGeoPoint<double>>>::iterator itr = m_results.find(name);

					//not found
					if (itr == m_results.end())
					{
						continue;
					}

					//anchor result
					std::map<std::string, std::vector<CGeoPoint<double>>>::const_iterator anchoritr = anchor.m_results.find(name);
					if (anchoritr == anchor.m_results.end())
					{
						continue;
					}
					int notchangeCount = 0;
					int anchorCount = anchoritr->second.size();

					//from first to last
					int j = 0;
					for (; j < itr->second.size(); j++)
					{
						//from first to last
						int anchorIdx = j;

						//exception
						if (anchorIdx >= anchorCount)
						{
							break;
						}

						//copy value
						if (itr->second[j].m_y <= anchor.m_layers[i].m_max_depth)
						{
							itr->second[j].m_z = anchoritr->second[anchorIdx].m_z; 
						}
						else
						{
							notchangeCount++;
						}
					}
				}

				return *this;
			}
		};

		//
		//
		//
		/*!
		*
		**/
		enum GeologicalVariableSliceType
		{
			GVS_Type_Fai = 0,
			GVS_Type_Temperature,
			GVS_Type_TTI,

			GVS_Type_RO_TTI,
			GVS_Type_RO_Simple,
			GVS_Type_RO_Easy,
			GVS_Type_RO_Basin,

			//2018/1/31: add porosity
			GVS_Type_Porosity,

			GVS_Type_Max,
		};

		struct ContourRecord
		{
			double m_cmpVal;
			int m_lessId;
			int m_equalId;
			int m_greatId;

			//2017/8/10: backup of compare value
			double m_bkCmpVal;
		};
		typedef std::vector<ContourRecord> ContourRecords;

		/*!
		*2017/8/23: shown variable type
		**/
		enum GeologicalVariableResultType
		{
			GVR_Type_PCOEm = 0,//压力系数
			
			GVR_Type_vWater,//地层水流速
			GVR_Type_Porom,//中部孔隙度 ，小数
			GVR_Type_Perm,//渗透率，需要除以0.98692e-15
			
			GVR_Type_WaterViscosity,//水粘度
			GVR_Type_WaterDensity, //地层水密度
			
			GVR_Type_TotalThermalCond,//总的热导率  （包括基质和孔隙流体）
			GVR_Type_TMatrixThermalCond, //总的基质热导率
			GVR_Type_WaterThermalCond, //地层水热导率
			
			GVR_Type_TotalHeatCapacity, //总的比热容 （包括基质和孔隙流体）
			GVR_Type_TMatrixHeatCapacity, //总的基质比热容
			GVR_Type_WaterHeatCapacity, //地层水比热容
			
			GVR_Type_Qr, // 总的辐射热
			GVR_Type_Tm, //中部温度
			GVR_Type_TTI, //地层的TTI值
						
			GVR_Type_RO_Simple,//ro%
			GVR_Type_RO_Easy,//ro%
			GVR_Type_RO_Basin,//ro%
			
			GVR_Type_Pm,//流体压力
			GVR_Type_Um,//流体超压
			GVR_Type_StaticPm, //静流体压力
			GVR_Type_Plm, //静岩压力
			GVR_Type_Ulm, //静岩势能
			GVR_Type_EffectiveStressm,//有效应力

			//2017/9/4:反应动力学生烃强度
			GVR_Type_HI_LLNL_Oil,
			GVR_Type_HI_LLNL_Gas,

			//2017/9/4: 降解率生烃强度
			GVR_Type_HI_DR_Oil_Simple_Ro,
			GVR_Type_HI_DR_Oil_Easy_Ro,
			GVR_Type_HI_DR_Oil_Basin_Ro,
			
			GVR_Type_HI_DR_Gas_Simple_Ro,
			GVR_Type_HI_DR_Gas_Easy_Ro,
			GVR_Type_HI_DR_Gas_Basin_Ro,

			GVR_Type_HI_DR_Total_Simple_Ro,
			GVR_Type_HI_DR_Total_Easy_Ro,
			GVR_Type_HI_DR_Total_Basin_Ro,

			//2017/10/16:排烃对应变量,这些变量单位都是kg
			GVR_Type_MKer, //源岩中干酪根质量，以有机碳形式给出，单位：kg
			GVR_Type_MKerReac, //源岩中可反应的干酪根量，以有机碳形式给出，单位：kg
			GVR_Type_MKerInert, //源岩中无效干酪根量 ，以有机碳形式给出，单位：kg
			GVR_Type_MAdxOil, //源岩中油的吸附量，单位：kg
			GVR_Type_MAdxGas, //源岩中气的吸附量，单位：kg
			GVR_Type_MExpOilAdded, //源岩累积排油量，单位：kg
			GVR_Type_MExpGasAdded, //源岩累积排气量，单位：kg
			GVR_Type_MResidualOil,  //源岩残余油量，是指吸附量加上无机质孔隙中的油量，单位：kg ，
			GVR_Type_MResidualGas,  //源岩残余气量，是指吸附量加上无机质孔隙中的气量，单位：kg ，
			GVR_Type_OilInSourceRockPoros,//源岩孔隙中的油量,单位：kg 
			GVR_Type_GasInSourceRockPoros, //源岩孔隙中的气量,单位：kg 
			GVR_Type_OilOutOfSourceRock,//运移到源岩外的累计的油量,单位：kg 
			GVR_Type_GasOutOfSourceRock, //运移到源岩外的累计的气量，单位：kg 
			GVR_Type_OGIFromKerogen,//源岩干酪根累积生油量，单位：kg 
			GVR_Type_GGIFromKerogen, //源岩干酪根累积生气量 ，单位：kg 
			GVR_Type_OilCrackedAdded, //源岩中累积的油裂解量，单位：kg
			GVR_Type_GasCrackedAdded, //源岩中累积的气裂解量，单位：kg 
			GVR_Type_CokeAdded,//源岩中油裂解产生的焦炭量，单位：kg
			GVR_Type_TR, //源岩的油气转化率
			
			//
			GVR_Type_RO_TTI,//ro%
		};

		/*!
		*2017/9/8: layer scale in each age
		**/
		struct LayerScaleDepth
		{
			std::string m_name;
			double m_min_depth;
			double m_max_depth;

			LayerScaleDepth()
			{
				m_name = "";
				m_min_depth = 0x7fffffff;
				m_max_depth = -0x7fffffff;
			}
		};
		typedef std::vector<LayerScaleDepth> LayerScaleDepths;
		typedef std::map<double,LayerScaleDepths> LayerScaleDepthMap;

		/*!
		*
		**/
		struct GeologicalVariableSliceResult
		{
			double m_minValue;
			double m_maxValue;
			
			//store records by age, from old age to now
			std::vector<GeologicalVariableSlice> m_slices;

			//store records by line
			std::map<std::string, std::vector<std::vector<CGeoPoint<double>>>> m_simulationPts;

			//contour line related
			int m_contourLineNum;
			ContourRecords m_contourRecs;
			ContourLineMap m_allVarMap;
			ContourLineMap m_contourLineMap;

			//2017/6/12: store HCGI/OCGI/GGI
			std::map<std::string, std::vector<SourceRockRecords>> m_hcgiPts;
			std::map<std::string, std::map<double,CGeoPoint<double>>> m_hcgiVarMap;
			std::map<std::string, std::map<double,CGeoPoint<double>>> m_hcgi_LLNL_VarMap;

			//2017/7/24: rendered map
			ContourLineMap m_renderedMap;

			//2017/8/9: pressure coefficient points
			//2017/8/23: change std::map<std::string, std::vector<std::vector<CGeoPoint<double>>>> to std::map<int,std::map<std::string, std::vector<std::vector<CGeoPoint<double>>>>>
			//in order to store different kinds of variables
			std::map<int,std::map<std::string, std::vector<std::vector<CGeoPoint<double>>>>> m_pressurePts;
			std::map<int,ContourLineMap> m_pressureVarMap;

			//2018/3/15: layer scale in each age, with variable type
			std::map<int,LayerScaleDepthMap> m_layer_scale_depth_map_with_type;

			/*!
			*
			**/
			GeologicalVariableSliceResult()
			{
				Reset();
			}

			/*!
			*
			**/
			GeologicalVariableSliceResult(const GeologicalVariableSliceResult& other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const GeologicalVariableSliceResult&operator=(const GeologicalVariableSliceResult& other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_slices = other.m_slices;
				m_simulationPts = other.m_simulationPts;

				m_minValue = other.m_minValue;
				m_maxValue = other.m_maxValue;
				
				//
				m_contourLineNum = other.m_contourLineNum;
				m_contourRecs = other.m_contourRecs;
				m_allVarMap = other.m_allVarMap;
				m_contourLineMap = other.m_contourLineMap;

				//2017/6/12: copy HCGI/OCGI/GGI
				m_hcgiPts = other.m_hcgiPts;
				//CopyHCGI(other.m_hcgiPts);
				m_hcgiVarMap = other.m_hcgiVarMap;

				//
				m_hcgi_LLNL_VarMap = other.m_hcgi_LLNL_VarMap;

				//
				m_renderedMap = other.m_renderedMap;

				//
				m_pressurePts = other.m_pressurePts;
				m_pressureVarMap = other.m_pressureVarMap;

				//
				m_layer_scale_depth_map_with_type = other.m_layer_scale_depth_map_with_type;

				//
				return *this;
			}

			/*!
			*
			**/
			void ResetMinMax()
			{
				m_minValue = 0x7fffffff;
				m_maxValue = -0x7fffffff;
			}

			/*!
			*
			**/
			void Reset()
			{
				m_minValue = 0x7fffffff;
				m_maxValue = -0x7fffffff;

				m_slices.clear();
				m_simulationPts.clear();

				m_contourLineNum = 10;
				m_contourLineMap.clear();
				m_contourRecs.clear();
				m_allVarMap.clear();

				//
				//ReleaseHCGI();
				m_hcgiPts.clear();
				m_hcgiVarMap.clear();

				//
				m_hcgi_LLNL_VarMap.clear();

				//
				m_renderedMap.clear();

				//
				m_pressurePts.clear();
				m_pressureVarMap.clear();

				//
				m_layer_scale_depth_map_with_type.clear();
			}

			/*!
			*
			**/
			void CopyHCGI(const std::map<std::string, std::vector<SourceRockRecords>> &hcgiPts)
			{
				ReleaseHCGI();

				//
				std::map<std::string, std::vector<SourceRockRecords>>::const_iterator itr = hcgiPts.begin();
				for (; itr != hcgiPts.end(); itr++)
				{
					std::vector<SourceRockRecords> recordss;

					int i = 0;
					for ( ; i < itr->second.size(); i++)
					{
						SourceRockRecords records;

						int j = 0;
						for (; j < itr->second[i].size(); j++)
						{
							SourceRockRecord record = itr->second[i][j];
							records.push_back(record);
						}

						if (records.size())
						{
							recordss.push_back(records);
						}
					}

					if (recordss.size())
					{
						m_hcgiPts[itr->first] = recordss;
					}
				}
			}

			/*!
			*
			**/
			void ReleaseHCGI()
			{
				//
				std::map<std::string, std::vector<SourceRockRecords>>::iterator itr = m_hcgiPts.begin();
				for (; itr != m_hcgiPts.end(); itr++)
				{
					int i = 0;
					for ( ; i < itr->second.size(); i++)
					{
						int j = 0;
						for (; j < itr->second[i].size(); j++)
						{
							itr->second[i][j].Release();
						}
					}
				}

				//
				m_hcgiPts.clear();
			}
		};
		typedef std::map<GeologicalVariableSliceType,GeologicalVariableSliceResult> GeologicalVariableSliceResultMap;//

		/*!
		*
		**/
		class RenderGeologicalVariableSliceTask: public CAnySignalTask<void()>,public JTCMonitor
		{
			public:
				RenderGeologicalVariableSliceTask(int taskcount,int index, CAnyCanvas &canvas,const CGeoRect<double> &scrExtent, CAnyCPUScheduler *scheduler, CAnyBurialHistoryPlot *hook,\
					GeologicalVariableSlice &varSlice,GeologicalLine &scrLastLine, double minValue, double maxValue, const std::vector<double> &contourValues);
				~RenderGeologicalVariableSliceTask();
				void DoExecuteTask();
			private:
				int m_index;
				int m_taskcount;
				CAnyCanvas &m_canvas;
				CGeoRect<double> m_scrExtent;
				CAnyCPUScheduler *m_scheduler;
				CAnyBurialHistoryPlot *m_hook;
				GeologicalVariableSlice &m_varSlice;
				GeologicalLine m_scrLastLine;
				double m_minValue;
				double m_maxValue;
				std::vector<double> m_contourValues;
		};
		friend class RenderGeologicalVariableSliceTask;


		/*!
		*2017/2/22: reality check mode
		**/
		enum RealityCheck
		{
			RC_Unknown = -1,
			RC_Temperature,
			RC_RO,
			
			//2017/6/15: hydrocarbon-generating intensity
			RC_Hydrocarbon_Generating_Intensity,

			//2017/8/9: pressure coefficient
			RC_Pressure_Coefficient,
		};

		/*!
		*2017/6/22: Hydrocarbon Intensity Canvas Type
		**/
		enum HydrocarbonIntensityCanvasType
		{
			HICT_Degradation_Rate     = 1,
			HICT_LLNL                 = 1 << 2,

			//2017/10/16: 排烃相关
			HICT_MKer                 = 1 << 3,
			HICT_MKerReac             = 1 << 4,
			HICT_MKerInert            = 1 << 5,
			HICT_MAdxOil              = 1 << 6,
			HICT_MAdxGas              = 1 << 7,
			HICT_MExpOilAdded         = 1 << 8,
			HICT_MExpGasAdded         = 1 << 9,
			HICT_MResidualOil         = 1 << 10,
			HICT_MResidualGas         = 1 << 11,
			HICT_OilInSourceRockPoros = 1 << 12,
			HICT_GasInSourceRockPoros = 1 << 13,
			HICT_OilOutOfSourceRock   = 1 << 14,
			HICT_GasOutOfSourceRock   = 1 << 15,
			HICT_OGIFromKerogen       = 1 << 16,
			HICT_GGIFromKerogen       = 1 << 17,
			HICT_OilCrackedAdded      = 1 << 18,
			HICT_GasCrackedAdded      = 1 << 19,
			HICT_CokeAdded            = 1 << 20,
		};

		/*!
		*2017/8/9: pressure coefficient canvas type
		**/
		enum PressureCoefficientCanvasType
		{
			PCCT_Age_Pressure = 0,
			PCCT_Depth_Pressure,
		};

		/*!
		*2017/3/14: mc kenzie struct
		**/
		struct FsMcKenzieRecord
		{
			bool m_isFsMcKenzie;
			double m_fromage;
			double m_toage;

			double m_Beita;//'拉张系数'
			double m_yL;//'岩石圈厚度'
			double m_Tm;//'软流圈温度'
			double m_k;//'导热系数'
			double m_Kappa;//'热扩散系数'

			FsMcKenzieRecord()
			{
				m_isFsMcKenzie = true;
				m_fromage = 0.;
				m_toage = 0.;

				m_Beita = 2.;
				m_yL = 125.; 
				m_Tm = 1333.; 
				m_k = 0.0075;
				m_Kappa = 0.00804;
			}
		};
		typedef std::vector<FsMcKenzieRecord> FsMcKenzieRecords;

	public:
		CAnyBurialHistoryPlot(CAnyView &curView);
		~CAnyBurialHistoryPlot();

	public:
		// 
		// hook
		//
		/*!
		*
		*/
		void Clone(const CAnyViewHook *prototype);

		/*!
		*
		*/
		void InitAllTimeScales(TimeScaleVector &timescales);

		//
		// data preparation, layer
		//
		/*!
		*
		*/
		void SetGeologicalLayerVector(GeologicalLayerVector &layers);
		
		/*!
		*
		*/
		const GeologicalLayerVector &GetGeologicalLayerVector();

		/*!
		*
		*/
		void SetSeaHorizonLine(GeologicalLine &seahorizon, const std::string &name);
		
		/*!
		*
		*/
		const GeologicalLine &GetSeaHorizonLine(const std::string &name);

		//
		// geological slice...
		//
		/*!
		*type
		*/
		void SetGeologicalVariableSliceType(int type);

		/*!
		*
		*/
		int GetGeologicalVariableSliceType();

		/*!
		*color
		*/
		void SetGeologicalVariableSliceColor(int type, const GeologicalVariableSliceColor &sliceColor);
		
		/*!
		*
		*/
		GeologicalVariableSliceColor &GetGeologicalVariableSliceColor(int type);

		//
		// simulation
		//
		/*!
		*boost::bind
		**/
		double CompressionFunction(double depth, const string& formulae);

		/*!
		*
		*/
		bool Simulation();	

		//
		// reality mode 
		//
		/*!
		*
		*/
		void SetRealityCheckMode(int mode);

		/*!
		*
		*/
		int GetRealityCheckMode();

		//
		//results
		//
		/*!
		*
		*/
		const GeologicalLines &GetBurialHistoryLines();

		/*!
		*
		*/
		const std::vector<std::string> &GetBurialHistoryLineNames();

		//
		//2017/3/14: parameters for FsMcKenzie records
		//
		/*!
		*
		**/
		void SetFsMcKenzieRecords(const FsMcKenzieRecords &FsMcKenzies);
		
		/*!
		*
		**/
		const FsMcKenzieRecords &GetFsMcKenzieRecords();

		//
		//2017/3/22: ro type
		//
		/*!
		*
		**/
		void SetRoType(int type);
		
		/*!
		*
		**/
		int GetRoType();

		//
		//2017/4/12: get heat flow by McKenzie
		//
		/*!
		*
		**/
		double GetHeatFlowByMcKenzie(double age, const FsMcKenzieRecords &FsMcKenzies, double toage);

		//
		//2017/4/17: save/load
		//
		/*!
		*
		**/
		void SetBordId(long idx);

		/*!
		*
		**/
		long GetBordId();


		/*!
		*
		**/
		bool Load(bool is_commit_result = true); 

		/*!
		*
		**/
		long Commit(bool is_commit_result = true);

		/*!
		*
		**/
		double GetGeologicalSliceValue(const std::string &layername, double age, int gvs_type, int calculate_type);

		//
		//2017/5/17: transit model
		//
		/*!
		*
		**/
		void SetTransitHeatFlowModel(bool isTransit);
		
		/*!
		*
		**/
		bool IsTransitHeatFlowModel();


		//
		//2017/6/5: lithology
		//
		/*!
		*
		**/
		void SetGeologicalLithology(const GeologicalLithologyMap &lithmap);
		
		/*!
		*
		**/
		void SetDefaultGeologicalLithology(GeologicalLithologyMap &lithmap);

		/*!
		*
		**/
		GeologicalLithologyMap &GetGeologicalLithology();

		/*!
		*
		**/
		bool SetLithologyFormula(std::vector<std::string> &lithnames, std::vector<double> &ratios, GeologicalLayer &curlayer, int formulaId = 0, const std::string &new_lithname = ""); 

		/*!
		*
		**/
		bool IsLithnameOk(const std::string &category, const std::string &subcategory, const std::string &lithname);

		//
		//2017/6/16: Degradation Rate
		//		
		/*!
		*
		**/
		const DegradationRate &GetDegradationRate();
		
		/*!
		*
		**/
		void SetDegradationRate(DegradationRate &rate);

		//
		//2017/6/21: LLNL parameter
		//		
		/*!
		*
		**/
		const KerogenParaLLNL &GetLLNL();
		
		/*!
		*
		**/
		void SetLLNL(KerogenParaLLNL &para);

		//
		//2017/6/22: HydrocarbonIntensityCanvasType
		//
		/*!
		*
		**/
		int GetHydrocarbonIntensityCanvasType();

		/*!
		*
		**/
		void SetHydrocarbonIntensityCanvasType(int type);
		
		/*!
		*
		**/
		const std::vector<std::string> &GetHydrocarbonLayers();

		/*!
		*
		**/
		void SetHydrocarbonLayers(const std::vector<std::string> &layernames);
	
		//
		//2017/7/7: step for x/y
		//
		/*!
		*
		**/
		inline double GetThicknessStep();

		/*!
		*
		**/
		inline void SetThicknessStep(double step);
		
		/*!
		*
		**/
		inline double GetAgeStep();

		/*!
		*
		**/
		inline void SetAgeStep(double step);
		
		/*!
		*
		**/
		inline bool IsOverPressure();

		/*!
		*
		**/
		inline void SetOverPressure(bool is_over_pressure);

		//
		//2017/8/9: pressure coefficient
		//
		/*!
		*
		**/
		int GetPressureCoefficientCanvasType();

		/*!
		*
		**/
		void SetPressureCoefficientCanvasType(int type);
		
		/*!
		*
		**/
		const std::vector<std::string> &GetPressureCoefficientLayers();

		/*!
		*
		**/
		void SetPressureCoefficientLayers(const std::vector<std::string> &layernames);

		/*!
		*
		**/
		int GetPressureCoefficientGridIdx();

		/*!
		*
		**/
		void SetPressureCoefficientGridIdx(int idx);

		/*!
		*2017/8/9: return the slice result
		**/
		GeologicalVariableSliceResultMap &GetGeologicalVariableSliceResultMap();

		/*!
		*
		**/
		double GetPressureCoefficientAge();

		/*!
		*
		**/
		void SetPressureCoefficientAge(double age);

		/*!
		*
		**/
		int GetPressureCoefficientVariableType();

		/*!
		*
		**/
		void SetPressureCoefficientVariableType(int type);

		/*!
		*
		**/
		std::string GetVariableNameByType(int type, bool is_unit = false);

		//
		//2017/8/29: practice related
		//
		/*!
		*
		**/
		const BurialHistoryPracticeRecord &GetPracticeRecord(int index);

		/*!
		*
		**/
		int GetPracticeCount();

		/*!
		*
		**/
		bool DeletePracticeRecord(long practiceIdx);

		/*!
		*
		**/
		bool LoadPracticeParameter(long practiceIdx, bool is_load_result = false);

		/*!
		*
		**/
		bool UpdateRemarkPracticeRecord(long practiceIdx, const string &remark);

		//
		//2017/9/4: whether to calculate water depth
		//
		/*!
		*
		**/
		bool IsCalculateWaterDepth();

		/*!
		*
		**/
		void SetCalculateWaterDepth(bool is_calculate);

	protected:
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

		/*!
		*
		**/
		void DoSetAxisExtent();

		/*!
		*
		**/
		void DoRenderTimeScales(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderGeologicalVariableSlice(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderAxises(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderLayerScale(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderGeologicalLines(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderGeologicalScanLines(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderGeologicalScanLines(CAnyCanvas &canvas,const std::vector<CGeoPoint<double>> &leftLinePts, const std::vector<CGeoPoint<double>> &rightLinePts,\
			const CGeoPoint<double> &temp_first, const CGeoPoint<double> &temp_second, int &lineOrder, int order, int lithoColor, int lithoStyle);//2017/3/13: add color, style for lithology

		/*!
		*
		**/
		void DoRenderSeaHorizon(CAnyCanvas &canvas);

		//
		// topo, sea horizon & layers, layer &layer
		//
		/*!
		*
		**/
		void TopoRelationship();

		//
		// simulation
		//
		/*!
		*
		**/
		double TemperatureFunction(double age, double depth);
		
		/*!
		*2017/2/22: render reality check line/points
		**/
		void DoRenderRealityCheckLines(CAnyCanvas &canvas);

		/*!
		*2017/3/7: calculate the value of a formulae
		**/
		double CalculateByFormula(const string& formulae, double depth, double c, double fai0);

		//
		//
		//
		/*!
		*
		**/
		double RoFunction(double age, double depth);
		
		/*!
		*
		**/
		void CalculateRoRatio();

		/*!
		*2017/3/24: easy ro function
		**/
		double EasyRo(double TLast, double tLast, double T, double t,int NN,double *f,double *E,double A,double Roo,double f0 );

		/*!
		*2017/3/24: simple ro function
		**/
		double SimpleRo(double TLast, double tLast, double T, double t,double &f,double aerf,double beita,double A,double Roo, double f0);

		/*!
		*2017/4/10: tti function
		**/
		double TTIF(double TLast, double tLast, double T, double t,double &TMax,double TTILast);
		
		/*!
		*2017/4/10: tti function
		**/
		double GetRoByTTI(double tti);

		/*!
		*2017/4/6: ro parameters
		**/
		void InitRoParameter();

		//
		//2017/3/14: calculate heat flow by FsMcKenzie
		//
		/*!
		*
		**/
		double FsMcKenzie(double t, double Beita = 2.,double yL = 125., double Tm = 1333., double k = 0.0075, double Kappa = 0.00804);

		//
		//2017/3/23: get burial lines
		//
		/*!
		*
		**/
		void DoSimulation(GeologicalLayerVector &layers);

		/*!
		*2017/3/28: get layer batch by batch
		**/
		int DoGetLayerBatch(int curlayerIdx, std::vector<GeologicalLayer> &curbatch, std::vector<GeologicalLayer> &prevbatch);

		/*!
		*2017/3/31: sub method of DoGetLayerBatch, connect from/to age between the two layers
		**/
		void ConnectLayerAge(const GeologicalLayer &lastLayer, GeologicalLayer &curLayer);

		/*!
		*2017/3/29: merge layer's burial lines batch by batch
		**/
		void DoMergeBurialLines(std::vector<std::vector<GeologicalLayer> > &layerbatches);

		//
		//
		//
		/*!
		*get surface temperature and heat flow
		**/
		void DoGetT0Q0(double age, double &t0, double &Q);

		//
		//2017/4/7: new Geological Variable methods
		//
		/*!
		*
		**/
		void DoRenderGeologicalSlice(CAnyCanvas &canvas);
		
		/*!
		*
		**/
		void GetGeologicalVariable();

		/*!
		*
		**/
		void ScanGeologicalVariable(double start_age = ANY_NAN, double end_age = ANY_NAN, double xMapStep = ANY_NAN, double yMapStep = ANY_NAN);

		/*!
		*
		**/
		void CalculateGeologicalVariable();

		/*!
		*
		**/
		void TraceGeologicalVariableContour();

		/*!
		*
		**/
		void DoTraceGeologicalVariableContour(const GeologicalVariableSliceType &renderType);

		/*!
		*
		**/
		void DoRenderSliceByContour(const GeologicalVariableSliceType &renderType, int slicetype, int color = -1);

		/*!
		*
		**/
		void DoRenderSliceByPixel(CAnyCanvas &canvas, const GeologicalVariableSliceType &renderType, int slicetype, double lessValue = -1.);

		/*!
		*
		**/
		void DoRenderSlice(CAnyCanvas &canvas);

		/*!
		*2018/3/16: render ro/temperature/porosity
		**/
		void DoRenderSliceHints(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderSliceLegend(CAnyCanvas &canvas, int slicetype);
		
		/*!
		*
		**/
		static bool CompareGeologicalSliceAge(const GeologicalVariableSlice &slice1, const GeologicalVariableSlice &slice2);

		/*!
		*
		**/
		bool AddGeologicalVariableSlice(double curage, GeologicalVariableSlice &anchorStart, GeologicalVariableSlice &anchorEnd, std::vector<GeologicalVariableSlice> &slices,\
			const std::string type = "direct", double yMapStep = ANY_NAN);

		/*!
		*
		**/
		void DoGetGeologicalVariableAnchors(double start_age, double end_age, double xMapStep);
		void DoCalculateGeologicalVariableSlice(double age, GeologicalVariableSlice &slice, double yMapStep);
		bool IsErodedBegin(double &curAge, double preAge);
		bool IsErodedEnd(double &curAge, double preAge);
		bool IsAddNewLayer(double &curAge, double preAge);

		//
		//check whether the variables changed
		//
		/*!
		*2017/4/7: if layers changed, then call function Simulation()
		**/
		bool IsGeologicalLayerRecordModified(GeologicalLayerVector &layers);
		
		/*!
		*2017/4/10: if McKenzieRecord changed, then re-calculate temperature...
		**/
		bool IsMcKenzieRecordModified(const FsMcKenzieRecords &FsMcKenzies);

		/*!
		*2017/4/10: if temperature/heat flow changed, then re-calculate temperature...
		**/
		bool IsTemperatureRecordModified(const GeologicalLine &oldRecords, const GeologicalLine &reccords);

		/*!
		*2017/4/11: compare CGeoPoint x
		**/
		static bool CompareGeoPointX(const CGeoPoint<double> &x1, const CGeoPoint<double> &x2);

		//
		//2017/4/17: save/load functions
		//
		/*!
		*
		**/
		void DoCommitGeologicalLayers(long practiceIdx);

		/*!
		*
		**/
		void DoLoadGeologicalLayers(char* data, int& len);

		/*!
		*
		**/
		void DoCommitResults(long practiceIdx);

		/*!
		*
		**/
		void DoLoadResults(char* data, int& len);

		
		//
		//2017/8/28: save/load settings
		//
		/*!
		*
		**/
		void DoCommitSettings(long practiceIdx);

		/*!
		*
		**/
		void DoLoadSettings(char* data, int& len);

		/*!
		*
		**/
		void DoLoadPracticeRecord(CAnyAccessor &accessor, BurialHistoryPracticeRecords &practices);

		/*!
		*
		**/
		static bool ComparePracticeIdx(const BurialHistoryPracticeRecord &first, const BurialHistoryPracticeRecord &second)
		{
			return first.m_practiceIdx > second.m_practiceIdx;
		}

		//
		//2017/5/11: transit heat flow
		//
		/*!
		*
		**/
		bool TransitHeatFlowModel_For1Time(int L, double *Z, double *T0, double *K, double *V, double *c1, double *p1, double *c2, double *p2, double q,double Ts, double dt, double *T1);
		
		/*!
		*
		**/
		void TransitHeatFlowModel_BuildMatrix(int L, double *Z, double *T0, double *K, double *V, double *c1, double *p1, double *c2, double *p2, double q,double Ts, double dt, double **M, double *W);
		
		/*!
		*
		**/
		bool TridagonalmatrixFuction(int n, double **A, double *B, double *X);

		/*!
		*2017/6/23: new transit heat flow
		**/
		bool TransitHeatFlowModel_For1Time(int L, double *Z, double *T0, double *K, double *v,double *Q,  double *c1, double *p1, double *c2, double *p2, double q,double Ts, double dt, double *T1);
		void TransitHeatFlowModel_BuildMatrix(int L, double *Z, double *T0, double *K, double *V, double *Q, double *c1, double *p1, double *c2, double *p2, double q,double Ts, double dt, double **M, double *W);

		//
		//hcgi related
		//
		/*!
		*2017/6/13: get hcgi
		**/
		void DoGetGeologicalVariableHcgi(const GeologicalVariableSliceType &renderType);

		//
		//get water depth according to 'age'
		//
		/*!
		*2017/6/21: get water depth
		**/
		double GetWaterDepth(double age, double cur_depth);

		/*!
		*2017/6/28: the method of calculating hcgi
		**/
		void CalculateHCGI();
				
		/*!
		*2017/6/28: the method of calculating ro
		**/
		void CalculateRo();

		/*!
		*2017/6/28: the method of calculating tti
		**/
		void CalculateTTI();

		/*!
		*2017/6/28: the method of calculating Temperature
		**/
		bool CalculateTemperature();

		/*!
		*2017/7/3: the method of OverpressureEquation
		**/
		bool OverpressureEquation_For1Time_12(int L, double *Z, double *u0, double *a, double *b, double *c, double dt, double *u1);
		void OverpressureEquation_BuildMatrix_12(int L, double *Z, double *u0, double *a, double *b, double *c, double dt, double **M, double *W);

		/*!
		*2017/7/3: the method of StretchHeatFlowMode
		**/
		bool Model_B_For1Time_11(int L, double *Z, double *T0, double *K, double *V, double *Q, double *c1, double *p1, double *c2, double *p2,double dt, double *T1);
		void Model_B_BuildMatrix_11(int L, double *Z, double *T0, double *K, double *V,double *Q, double *c1, double *p1, double *c2, double *p2, double dt, double **M, double *W);

		/*!
		*2017/8/11: get pressure coefficient by age-depth
		**/
		void DoGetPressureCoefficientByAge(const GeologicalVariableSliceType &renderType);

		/*!
		*2017/9/8: compare by depth
		**/
		static bool CompareLayerScaleDepth(const LayerScaleDepth &x1, const LayerScaleDepth &x2);

	public:

		//2018/1/29: whether to paint without simulation inside the class
		//direct mode?
		bool m_is_direct_paint_mode;
		
		//depth must be added by ascending order( min -> max)
		GeologicalLines m_burial_layer_vector;
		std::vector<std::string> m_burial_layer_names;

		//2019/8/22: make those variables as public 
		//slice colors: int is GeologicalVariable
		std::map<int,GeologicalVariableSliceColor> m_sliceColors;
		GeologicalVariableSliceResultMap m_geological_slice_map;
		GeologicalVariableType m_sliceType;

		//2019/9/10: whether to paint time scale
		bool m_is_paint_time_scale;
	protected:
		// x axis
		double m_fromage;
		double m_toage;

		// y axis
		double m_fromdepth;
		double m_todepth;

		// input geological layer
		//GeologicalLayerVector m_layers;

		// extract from ref_geological_timescale
		TimeScaleVector m_timescales;
		TimeScaleVector m_alltimescales;

		// sea horizon
		GeologicalLine m_seahorizon;

		// history, 
		GeologicalLayerMap m_burial_layer_map;

		//depth must be added by ascending order( min -> max)
		/*GeologicalLines m_burial_layer_vector;
		std::vector<std::string> m_burial_layer_names;*/

		//simulator
		CAnyBurialHistorySimulator m_simulator;

		//2017/2/7: slice type
		//GeologicalVariableType m_sliceType;

		//swi temperature
		GeologicalLine m_temperatures;

		//heat flow
		GeologicalLine m_heatFlows;

		//slice colors: int is GeologicalVariable
		//std::map<int,GeologicalVariableSliceColor> m_sliceColors;

		//2017/2/21: temperature calibration data
		int m_realityCheckMode;
		GeologicalLine m_calibrationDataTemperture;
		GeologicalLine m_simulationDataTemperture;	

		//2017/3/7: ro calibration data
		GeologicalLine m_calibrationDataRO;
		GeologicalLine m_simulationDataRO;	

		//2017/3/1: contour line map
		int m_contourLineNum;
		ContourLineMap m_contourLineMap;

		//2017/3/14: FsMcKenzie functions
		FsMcKenzieRecords m_FsMcKenzies;

		//2017/3/22: ro type
		int m_roType;
		GeologicalLine m_ttiRoVec;

		//2017/4/1: for geological variable scan
		std::vector<GeologicalVariableSlice> m_geological_anchors;
		
		//2017/4/7
		//GeologicalVariableSliceResultMap m_geological_slice_map;

		//2017/4/1
		GeologicalVariableSlice m_varSlice;

		//2017/4/6: ro para map
		RoParaMap m_roMap;

		//2017/4/7: flag of record modification, get value from 'bool IsGeologicalLayerRecordModified()'
		bool m_isLayerSimulationRecordModified;
		bool m_isLayerTemperatureRecordModified;

		//2017/4/17: for save parameters/results
		long m_boreIdx;

		//2017/5/17:transit model
		bool m_isTransitHeatFlow;

		//2017/5/31: lithology map
		GeologicalLithologyMap m_lithologyMap;

		//2017/6/7: real screen extent for zoom
		CGeoRect<double> m_realScrExtent;

		//2017/6/13: Degradation Rate para
		DegradationRate m_degradation_rate;

		//2017/6/19: LLNL para
		KerogenParaLLNL m_paraLLNL;

		//2017/6/22: HydrocarbonIntensityCanvasType
		int m_hydrocarbon_canvas_type;
		std::vector<std::string> m_hydrocarbon_layers;

		//2017/7/6: step for x/y
		double m_step_thickness;
		double m_step_age;

		//2017/7/6: use over pressure mode?
		bool m_is_over_pressure;

		//2017/7/24: whether the screen extent changed?
		bool m_is_screen_extent_changed;

		//2017/8/9: pressure coefficient canvas type
		int m_pressure_canvas_type;
		std::vector<std::string> m_pressure_layers;
		int m_pressure_grid_idx;
		double m_pressure_age;

		//2017/8/23: shown variable type
		int m_pressure_variable_type;

		//2017/8/29: practice related
		BurialHistoryPracticeRecords m_practices;
		bool is_load_practice;

		//2017/9/4: whether to calculate water depth
		bool m_is_calculate_water_depth;
	public:
		//2017/8/30:practice remark
		std::string m_remark;
		
	};
}
#endif