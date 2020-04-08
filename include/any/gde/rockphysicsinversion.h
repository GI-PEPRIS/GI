/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGDE_ROCKPHYSICS_INVERSION_H__
#define __ANYGDE_ROCKPHYSICS_INVERSION_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include "any/base/anystl.h"
#include "anygdedataset.h"
#include "syntheticwaveletestimator.h"
//
namespace AnyGDE
{
	/*!
	* contributed by ZHANG FENGQI
	**/
	class ANYGDE_CLASS CRockPhysicsInversion : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CRockPhysicsInversion();
		~CRockPhysicsInversion();

	public:
		/*!
		* HFT_Generic
		**/
		void DoHandle(HandlerStruct &handlerstruct);

		/*!
		* calculation results
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		* calculation meta data for future explanation
		**/
		void DoGetTraceHead(std::vector<double> &results);

	public:
		void GetTracefromModel(const std::vector<double> &Model, std::vector<double> &Model_Inv, double start_time,double Top_time,double Bot_time,double samp_int);
		void LowPasFilterPetroV(const std::vector<double> &m, int dt, double lowpass, double lowcut, std::vector<double> &mp);
		void HamingWinPetroV(int pad_numb, double lowpass, double lowcut, int dt, std::vector<double> &winlow, int &f1, int &f2);
		void Estimate_Coeffient_Regression_3_Term(std::vector<double> &TOC,std::vector<double> &Porosity_Total,std::vector<double> &V_Bri,std::vector<double> &vp,std::vector<double> &vs,std::vector<double> &dens,\
			double Undef, int N_sample, int V_choice, std::vector<std::vector<double> > &G_Mat,std::vector<double> &Coef_Clay);
		void Getting_fai_from_las_3_Term(std::vector<double> &V_Bri,std::vector<double> &Toc,std::vector<double> &Porosity_Total,double undef,std::vector<std::vector<double> > &fai);
		void TOC_INV_Trace_3_Term(double start_time_Bri,double start_time_TOC,double start_time_Por,double samp_num_Bri,double samp_num_TOC,double samp_num_Por,double samp_int_Bri,double samp_int_TOC,double samp_int_Por,\
			double start_time_Imp,double start_time_Jmp,double start_time_dens,double samp_num_Imp,double samp_num_Jmp,double samp_num_dens,double samp_int_Imp,double samp_int_Jmp,double samp_int_dens,\
			double Top_time,double Bot_time,std::vector<double> &Imp,std::vector<double> &Jmp,std::vector<double> &dens,std::vector<double> &Bri_Mod,std::vector<double> &TOC_Mod,std::vector<double> &Por_Mod,\
			std::vector<std::vector<double> > &G_Mat,std::vector<std::vector<double> > &Cov,double lamda,double lowpass,double lowcut,std::vector<double> &Coef_Clay,int V_choice, \
			std::vector<double> &Bri_Inv,std::vector<double> &TOC_Inv,std::vector<double> &Por_Inv,double &start_time_mod,int &samp_num_mod,double &samp_int_mod);
		void Pre_cond_TOC_3_Term(double start_time_Bri,double start_time_TOC,double start_time_Por,int samp_num_Bri,int samp_num_TOC,int samp_num_Por,double samp_int_Bri,double samp_int_TOC,double samp_int_Por,\
			double start_time_Imp,double start_time_Jmp,double start_time_dens,int samp_num_Imp,int samp_num_Jmp,int samp_num_dens,double samp_int_Imp,double samp_int_Jmp,double samp_int_dens,\
			double &Top_time,double &Bot_time,double &start_time_mod,int &samp_num_mod,double &samp_int_mod);
		void Property_Inv_Regression_3_Term(std::vector<std::vector<double> > &G_Mat,std::vector<double> &mp,std::vector<std::vector<double> > &Cov,double lamda, \
			double Imp_sat,double Jmp_sat,double dens_sat,std::vector<double> &Coef_Clay,int V_choice, std::vector<double> &x);
	public:
		std::vector<double> m_Seis_1;//P波阻抗
		std::vector<double> m_Seis_2;//S波阻抗
		std::vector<double> m_Seis_3;//密度
		std::vector<double> m_Seis_4;//脆性矿物体积分数
		std::vector<double> m_Seis_5;//干酪根体积分数
		std::vector<double> m_Seis_6;//总孔隙度
		std::vector<double> m_Seis_out_1;//脆性矿物体积分数输出
		std::vector<double> m_Seis_out_2;//干酪根体积分数输出
		std::vector<double> m_Seis_out_3;//总孔隙度输出
		double m_start_time_1;
		double m_start_time_2;
		double m_start_time_3;
		double m_start_time_4;
		double m_start_time_5;
		double m_start_time_6;
		double m_start_time_out;
		int m_samp_num_1;
		int m_samp_num_2;
		int m_samp_num_3;
		int m_samp_num_4;
		int m_samp_num_5;
		int m_samp_num_6;
		int m_samp_num_out;
		double m_samp_int_1;
		double m_samp_int_2;
		double m_samp_int_3;
		double m_samp_int_4;
		double m_samp_int_5;
		double m_samp_int_6;
		double m_samp_int_out;

		std::vector<std::vector<double> > m_fai;
		std::vector<std::vector<double> > m_G_Mat;
		std::vector<double> m_Coef_Clay;

		int m_v_choice;//总体积分数
		double m_lamda;//测井约束项权重
		double m_lowpass;//低通频
		double m_lowcut;//低截频

		int m_nInlineFrom, m_nInlineTo, m_nXlineFrom, m_nXlineTo;
		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;

		// for malloc reuse
		std::vector<double> m_LowPasFilterPetroV_winlow;
		CSyntheticWaveletEstimator::COMPLEX *m_LowPasFilterPetroV_mmsp;
		int m_LowPasFilterPetroV_mmsp_sub_count;
		std::vector<double> m_LowPasFilterPetroV_mm;
	};
}

#endif
