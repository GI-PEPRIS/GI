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
#ifndef __ANYGDE_ROCKBRICK_INVERSION_H__
#define __ANYGDE_ROCKBRICK_INVERSION_H__

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
	class ANYGDE_CLASS CRockBrickInversion : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CRockBrickInversion();
		~CRockBrickInversion();

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
		void Pre_cond_BI(double start_time_near,double start_time_mid,double start_time_far,int samp_num_near,int samp_num_mid,int samp_num_far,double samp_int_near,double samp_int_mid,double samp_int_far,\
			double start_time_Imp,double start_time_Jmp,double start_time_dens,int samp_num_Imp,int samp_num_Jmp,int samp_num_dens,double samp_int_Imp,double samp_int_Jmp,double samp_int_dens,\
			double &start_time_mod,int &samp_num_mod,double &samp_int_mod);
		void BI_Inv_Trace(std::vector<double> &Rc_near,std::vector<double> &Rc_mid,std::vector<double> &Rc_far,double start_time_near,double start_time_mid,double start_time_far,\
			std::vector<double> &Imp_mod,std::vector<double> &Jmp_mod,std::vector<double> &dens_mod,double start_time_Imp,double start_time_Jmp,double start_time_dens,\
			double start_time_mod,int samp_num_mod,double samp_int_mod,double sigma2,double sigma3,double YM_min,double YM_max,double PR_min,double PR_max,\
			int N_Iter,double lowpass,double lowcut,double ag_near,double ag_mid,double ag_far,double Top_time,double Bot_time,\
			std::vector<double> &BI_output,std::vector<double> &vp_output,std::vector<double> &vs_output);
		void GetTracefromRc(std::vector<double> &Rc,double start_time,double samp_int,double Top_time,double Bot_time,std::vector<double> &Rc_Inv);
		void GetTracefromModel(const std::vector<double> &Model, std::vector<double> &Model_Inv, double start_time,double Top_time,double Bot_time,double samp_int);
		void GLIForBI_PetroV(std::vector<double> &Imp,std::vector<double> &Jmp,std::vector<double> &dens,double ag_near,double ag_mid,double ag_far,\
			std::vector<double> &Rc_near,std::vector<double> &Rc_mid,std::vector<double> &Rc_far,double sigma2,double sigma3,int N_Iter,double samp_int_mod,\
			double YM_min,double YM_max,double PR_min,double PR_max,double lowpass,double lowcut,std::vector<double> &BI_Inv,std::vector<double> &vp_Inv,std::vector<double> &vs_Inv);
		void Inv_Output_PetroV(double start_time, double samp_num, double samp_int, double top_time, double bot_time, const std::vector<double> &para_Inv, std::vector<double> &para_output);
		void Cal_BI_from_VpVsDens(std::vector<double> &vp,std::vector<double> &vs,std::vector<double> &dens,double YM_min,double YM_max,double PR_min,double PR_max,std::vector<double> &BI);
		void LowPasFilterPetroV(const std::vector<double> &m, int dt, double lowpass, double lowcut, std::vector<double> &mp);
		void HamingWinPetroV(int pad_numb, double lowpass, double lowcut, int dt, std::vector<double> &winlow, int &f1, int &f2);
		void DifMat2(int N,std::vector<std::vector<double> > &D);
		void SoftConstrMatrEI(int N,double lowpass,double lowcut,double dt,int N_pad,std::vector<std::vector<double> >&Gs);
		void LowPassFilterMatrPetroV_New(double **Glow_cut, int N,double lowpass,double lowcut,int dt);
		void Zoe_for_BIVpVs(double BI1,double BI2,double Vp1,double Vp2,double Vs1,double Vs2,std::vector<double> &sina,std::vector<double> &sina2,std::vector<double> &cosa,double YM_min,double YM_max,double PR_min,double PR_max,std::vector<double> &Rpp);
		void Cal_Dens_from_BIVpVs( double vp,double vs,double BI,double YM_min,double YM_max,double PR_min,double PR_max,double &dens );
		void Cal_Dul_Diag_Mat(std::vector<double> &diag_A, std::vector<double> &diag_B,std::vector<std::vector<double> > &C);
		void BuildWeightForTriCau2(std::vector<std::vector<double> >&D,std::vector<double>&m,double **fai,std::vector<std::vector<double> >&Q);
		void Conv_Matr( double **Filter_Mat, std::vector<double> &Filter,int pad_numb, int N );
	public:
		std::vector<double> m_Seis_1;//小角度反射系数
		std::vector<double> m_Seis_2;//中角度反射系数
		std::vector<double> m_Seis_3;//大角度反射系数
		std::vector<double> m_Seis_4;//P波阻抗低频模型
		std::vector<double> m_Seis_5;//S波阻抗低频模型
		std::vector<double> m_Seis_6;//密度低频模型
		std::vector<double> m_Seis_out_1;//脆性指数的反演结果
		std::vector<double> m_Seis_out_2;//P波速度的反演结果
		std::vector<double> m_Seis_out_3;//S波速度的反演结果
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

		double m_ag_near;//小角度角度，float型变量
		double m_ag_mid;//中角度角度，float型变量
		double m_ag_far;//大角度角度，float型变量
		double m_sigma2;//先验约束权重，参数放开给用户（default==0.01）
		double m_sigma3;//低频软约束项权重，参数放开给用户（default==1）
		double m_YM_min;//最小杨氏模量，double型变量，从界面获取
		double m_YM_max;//最大杨氏模量，double型变量，从界面获取
		double m_PR_min;//最小泊松比，double型变量，从界面获取
		double m_PR_max;//最大泊松比，double型变量，从界面获取
		int m_N_Iter;//反演迭代次数,参数放开给用户（default==2）
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
		CSyntheticWaveletEstimator::COMPLEX *m_LowPassFilterMatrPetroV_New_winlow_complex;
		int m_LowPassFilterMatrPetroV_New_winlow_complex_sub_count;
		double **m_LowPassFilterMatrPetroV_Glow;
		int m_LowPassFilterMatrPetroV_Glow_count;
		int m_LowPassFilterMatrPetroV_Glow_sub_count;
		double **m_SoftConstrMatrPetroV_Glow_cut;
		int m_SoftConstrMatrPetroV_Glow_cut_count;
	};
}

#endif
