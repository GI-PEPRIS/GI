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
#ifndef __ANYGDE_THREE_TERM_BAYESIAN_INVERSION_H__
#define __ANYGDE_THREE_TERM_BAYESIAN_INVERSION_H__

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
	class ANYGDE_CLASS CThreeTermBayesianInversion : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CThreeTermBayesianInversion();
		~CThreeTermBayesianInversion();

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
		//
		void GetTracefromSeis(const std::vector<double> &Seis, std::vector<double> &Seis_Inv, double start_time, double samp_int, double samp_num, double start_time_wav, double wav_samp,double Top_time,double Bot_time);
		void GetTracefromModel(const std::vector<double> &Model, std::vector<double> &Model_Inv, double start_time,double Top_time,double Bot_time,double samp_int);
		void Wav_Seis_Uniformization(const std::vector<double> &wavelet, std::vector<double> &Seis_Inv, std::vector<double> &wavelet_uni);
		void GeneralizeWAVMAT3(double **waveletMATRIC, const std::vector<double> &wavelet, int samp_wav, int N);

		//
		void LowPasFilterPetroV(const std::vector<double> &m, int dt, double lowpass, double lowcut, std::vector<double> &mp);
		void HamingWinPetroV(int pad_numb, double lowpass, double lowcut, int dt, std::vector<double> &winlow, int &f1, int &f2);
		void Cal_Angle_Gama_PetroV(double **seta, const std::vector<double> &Ism, const std::vector<double> &Jsm, int Rc_len, const std::vector<double> &angle, std::vector<double> &gama);
		void Cal_Trend_PetroV(const std::vector<double> &Imp_Mod, const std::vector<double> &Jmp_Mod, const std::vector<double> &dens_Mod, int Mod_len, int Rc_len,int samp_int, double lowpass, double lowcut, std::vector<double> &EImp, std::vector<double> &EJmp, std::vector<double> &Ed);
		void Cal_Ref_PetroV(const std::vector<double> &Imp_Mod,const std::vector<double> &Jmp_Mod,const std::vector<double> &dens_Mod,int Rc_len, std::vector<double> &RImp, std::vector<double> &RJmp, std::vector<double> &Rd);
		void HermiteMatPetroV(double **A, int MM, int NN, double **AA);
		void Constr_Edge_Prot_PetroV(double **ProMatr, double **fai, int N, int samp_int, double sigma1);
		void GuasWinPetroV(int N, int samp_int, std::vector<double> &win);
		struct FAIParameter
		{
			double **fain;
			double **ProMatr;
		};
		void EstimatingFAIPetroV(FAIParameter &rt, const std::vector<double> &RImp, const std::vector<double> &RJmp, const std::vector<double> &Rd, int Rc_len, int samp_int, int NEM,double sigma1);
		void GetGPetroV(double **G, int trc_len_near, int trc_len_mid, int trc_len,int Rc_len,double **WM_near,double **WM_mid,double **WM_far,double**seta,std::vector<double> &gama);
		void SoftConstrMatrPetroV(double **Glow_In_cut, int N,double lowpass,double lowcut,int dt);
		void LowPassFilterMatrPetroV(double **Glow_cut, int N,double lowpass,double lowcut,int dt);
		void LowPassFilterMatrPetroV_New(double **Glow_cut, int N,double lowpass,double lowcut,int dt);
		void Conv_Matr( double **Filter_Mat, std::vector<double> &Filter,int pad_numb, int N );
		
		struct GdftParameter
		{
			double **Gdft_R;
			double **Gdft_I;
		};
		void DFTmatrPetroV(GdftParameter &rt, int pad_numb);
		void IntegalMatrPetroV_R(double **AA, double **A, int M, int N);
		void IntegalMatrPetroV_L(double **AA, double **A, int M, int N);
		
		double CalMuPetroV(double **G,double **m,double **d,double sigma2,int trc_len, int grows, int gcols);
		void BuildWeightForTriCauPetroV(double **Q, double **m, int mrows, double **fain,double sigma1, double samp_int, double mu);

		void Trc_IntegralPetroV(int Rc_len, double **m, double Imp_start, double Jmp_start, double dens_start, std::vector<double> &Imp_Inv, std::vector<double> &Jmp_Inv, std::vector<double> &dens_Inv);

		void LaMuRefInvForPetroV(const std::vector<double> &Imp_Mod, const std::vector<double> &Jmp_Mod, const std::vector<double> &dens_Mod, \
			const std::vector<double> &seis_near, const std::vector<double> &seis_mid, const std::vector<double> &seis_far, const std::vector<double> &angle, \
			double **WM_near, double **WM_mid, double **WM_far, \
			double sigma1, double sigma2, double sigma3,\
			int NEM, int NNN, int samp_int_mod, double lowpass, double lowcut, \
			std::vector<double> &Imp_Inv, std::vector<double> &Jmp_Inv, std::vector<double> &dens_Inv);

		//
		void Inv_Output_PetroV(double start_time, double samp_num, double samp_int, double top_time, double bot_time, const std::vector<double> &para_Inv, std::vector<double> &para_output);

		bool Pre_cond_PetroV(double samp_int_wav_near, double samp_int_wav_mid, double samp_int_wav_far, double samp_int_near, double samp_int_mid, double samp_int_far,double start_time_Imp, double start_time_Jmp, \
			double start_time_dens, double samp_num_Imp, double samp_num_Jmp, double samp_num_dens, double samp_int_Imp, double samp_int_Jmp, double samp_int_dens, \
			double &Top_time, double &Bot_time, double &start_time_mod, double &samp_num_mod, double &samp_int_mod);

		void PetroVPreInv(std::vector<double> &Seis_near, std::vector<double> &Seis_mid, std::vector<double> &Seis_far, double start_time_near, double start_time_mid, double start_time_far, \
			double samp_num_near, double samp_num_mid, double samp_num_far, double samp_int_near, double samp_int_mid, double samp_int_far, std::vector<double> &Imp_mod, std::vector<double> &Jmp_mod, std::vector<double> &dens_mod, \
			double start_time_Imp, double start_time_Jmp, double start_time_dens, double samp_num_Imp, double samp_num_Jmp, double samp_num_dens, \
			double samp_int_Imp, double samp_int_Jmp, double samp_int_dens, std::vector<double> &wavelet_near, std::vector<double> &wavelet_mid, std::vector<double> &wavelet_far, \
			double start_time_wav_near, double start_time_wav_mid, double start_time_wav_far, double samp_wav_near, double samp_wav_mid, double samp_wav_far, \
			double samp_int_wav_near, double samp_int_wav_mid, double samp_int_wav_far, std::vector<double> &angle, double sigma1, double sigma2, double sigma3, double NEM, double NNN, \
			double lowpass, double lowcut, double Top_time, double Bot_time, std::vector<double> &Imp_output, std::vector<double> &Jmp_output, std::vector<double> &dens_output, \
			double &start_time_mod, double &samp_num_mod, double &samp_int_mod);

		//
		// well QC
		//
		void FIND_DIF_TRAC(const std::vector<double> &inline_Vect, const std::vector<double> &xline_Vect, std::vector<double> &inline_QC, std::vector<double> &xline_QC);
		void CurveDepth2Time(const std::vector<double> &Cur_Depth,const std::vector<double> &Time, double simp_int, double start_time, std::vector<double> &Cur_Time, std::vector<double> &Time_well);
		void IntpLine(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &t, int n, int m, std::vector<double> &z);
		void Getting_QC_Traces(CAnyGdeDataGate::SurveyInfo &surveyinfo, double left_down_x_cord, double left_down_y_cord, double left_down_inline, double left_down_xline, \
			double right_down_x_cord, double right_down_y_cord, double right_down_inline, double right_down_xline, \
			double right_up_x_cord, double right_up_y_cord, double right_up_inline, double right_up_xline, \
			const std::vector<double> &Time, double simp_int, double start_time, \
			double well_x_loc, double well_y_loc,std::vector<double> &X_Dev,std::vector<double> &Y_Dev, \
			std::vector<double> &inline_QC,std::vector<double> &xline_QC,std::vector<double> &inline_Vect,std::vector<double> &xline_Vect,std::vector<double> &Time_well_QC);
		void Cord_To_Line(double left_down_x_cord, double left_down_y_cord, double left_down_inline, double left_down_xline, \
			double right_down_x_cord, double right_down_y_cord, double right_down_inline, double right_down_xline, \
			double right_up_x_cord, double right_up_y_cord, double right_up_inline, double right_up_xline, double **rotmat);
		void QC_well_curve_show(const std::vector<double> &AC, const std::vector<double> &S_AC, const std::vector<double> &Dens,const std::vector<double> &Time,\
			double start_time,double samp_int, string &unit,\
			std::vector<double> &TVD, std::vector<double> &Imp_well_show, std::vector<double> &Jmp_well_show, std::vector<double> &Dens_well_show, std::vector<double> &Gamma_well_show);
		void Run_Well_QC(std::vector<CAnyGdeDataSet*> datasets, std::vector<bool> isgdes, CAnyGdeDataGate::SurveyInfo &surveyinfo, double left_down_x_cord, double left_down_y_cord, double left_down_inline, double left_down_xline, \
			double right_down_x_cord, double right_down_y_cord, double right_down_inline, double right_down_xline, \
			double right_up_x_cord, double right_up_y_cord, double right_up_inline, double right_up_xline, \
			const std::vector<double> &Time, double well_x_loc, double well_y_loc,std::vector<double> &X_Dev,std::vector<double> &Y_Dev, \
			std::vector<double> &inline_QC,std::vector<double> &xline_QC,std::vector<double> &inline_Vect,std::vector<double> &xline_Vect,\
			std::vector<double> &AC, std::vector<double> &S_AC, std::vector<double> &Dens, string &unit, std::vector<double> &TVD, \
			std::vector<double> &Imp_Inv_QC_show, std::vector<double> &Jmp_Inv_QC_show, std::vector<double> &dens_Inv_QC_show, std::vector<double> &gamma_Inv_QC_show, \
			std::vector<double> &time_Inv_QC_show, std::vector<double> &Imp_well_show, std::vector<double> &Jmp_well_show,std::vector<double> &Dens_well_show, \
			std::vector<double> &Gamma_well_show, std::vector<double> &Time_well_QC);
	public:
		int m_nInlineFrom, m_nInlineTo, m_nXlineFrom, m_nXlineTo;
		//
		std::vector<double> m_Seis_near;	//输入的近道集地震数据
		std::vector<double> m_Seis_mid;	//输入的中道集地震数据
		std::vector<double> m_Seis_far;		//输入的远道集地震数据

		//
		double m_start_time_near;				//近道集起始时间
		double m_start_time_mid;					//中道集起始时间
		double m_start_time_far;					//远道集起始时间

		//
		int m_samp_num_near;						//近道集采样点数
		int m_samp_num_mid;						//中道集采样点数
		int m_samp_num_far;						//远道集采样点数

		//
		double m_samp_int_near;					//近道集采样间隔
		double m_samp_int_mid;					//中道集采样间隔
		double m_samp_int_far;					//远道集采样间隔

		//
		std::vector<double> m_Imp_mod;	//输入的P波阻抗低频模型
		std::vector<double> m_Jmp_mod;	//输入的S波阻抗低频模型
		std::vector<double> m_dens_mod;	//输入的密度低频模型

		//
		double m_start_time_Imp;					//P波阻抗低频模型起始时间
		double m_start_time_Jmp;				//S波阻抗低频模型起始时间
		double m_start_time_dens;				//密度低频模型起始时间

		//
		int m_samp_num_Imp;						//P波阻抗低频模型采样点数
		int m_samp_num_Jmp;						//S波阻抗低频模型采样点数
		int m_samp_num_dens;					//密度低频模型采样点数

		//
		double m_samp_int_Imp;					//P波阻抗低频模型采样间隔
		double m_samp_int_Jmp;					//S波阻抗低频模型采样间隔
		double m_samp_int_dens;					//密度低频模型采样间隔

		//
		std::vector<double> m_wavelet_near;		//输入的近角度子波（子波持久化文件中获取）
		std::vector<double> m_wavelet_mid;		//输入的中角度子波（子波持久化文件中获取）
		std::vector<double> m_wavelet_far;			//输入的远角度子波（子波持久化文件中获取）

		//
		double m_start_time_wav_near;				//近角度子波起始时间（子波持久化文件中获取）
		double m_start_time_wav_mid;				//中角度子波起始时间（子波持久化文件中获取）
		double m_start_time_wav_far;					//远角度子波起始时间（子波持久化文件中获取）

		//
		int m_samp_wav_near;								//近角度子波采样点数（子波持久化文件中获取）
		int m_samp_wav_mid;								//中角度子波采样点数（子波持久化文件中获取）
		int m_samp_wav_far;									//远角度子波采样点数（子波持久化文件中获取）

		//
		double m_samp_int_wav_near;				//近角度子波采样间隔（子波持久化文件中获取）
		double m_samp_int_wav_mid;					//中角度子波采样间隔（子波持久化文件中获取）
		double m_samp_int_wav_far;					//远角度子波采样间隔（子波持久化文件中获取）

		//
		std::vector<double> m_angle;											//入射角向量，用户界面填写，1×3的向量（例如[10,20,30]）
		double m_sigma1;										//高斯边界保护约束项权系数，参数放开给用户（default==0）
		double m_sigma2;										//反射系数稀疏约束项权系数，参数放开给用户（default==1）
		double m_sigma3;										//低频软约束项权系数，参数放开给用户（default==1）

		//
		double m_NEM;											//弹性参数尺度矩阵估计迭代次数,参数放开给用户（default==10）
		double m_NNN;											//反演迭代次数,参数放开给用户（default==2）
		double m_lowpass;									//低通滤波窗函数通过频率,参数放开给用户（default==5）
		double m_lowcut;										//低通滤波窗函数截至频率,参数放开给用户（default==15）

		double m_Top_time;									//反演时窗顶部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）
		double m_Bot_time;									//反演时窗底部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）
		
		std::vector<double> m_Top_times;									//反演时窗顶部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）
		std::vector<double> m_Bot_times;									//反演时窗底部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）

		std::vector<double> m_Imp_output;			//P波阻抗的反演结果，空白处的值已经赋NaN
		std::vector<double> m_Jmp_output;		//S波阻抗的反演结果，空白处的值已经赋NaN
		std::vector<double> m_dens_output;		//密度的反演结果，空白处的值已经赋NaN

		double m_start_time_mod;						//反演结果数据体起始时间（ms，存入反演结果数据体道头字，三维工区始终不变）
		double m_samp_num_mod;						//反演结果数据体采样点数（存入反演结果数据体道头字，三维工区始终不变）
		double m_samp_int_mod;							//反演结果数据体采样间隔（ms，存入反演结果数据体道头字，三维工区始终不变）

		// for malloc reuse
		bool m_isfirst;
		std::vector<double> m_PetroVPreInv_Seis_Inv_near;
		std::vector<double> m_PetroVPreInv_Seis_Inv_mid;
		std::vector<double> m_PetroVPreInv_Seis_Inv_far;
		std::vector<double> m_PetroVPreInv_Imp_mod_Inv;
		std::vector<double> m_PetroVPreInv_Jmp_mod_Inv;
		std::vector<double> m_PetroVPreInv_dens_mod_Inv;
		std::vector<double> m_PetroVPreInv_wavelet_near_uni;
		std::vector<double> m_PetroVPreInv_wavelet_mid_uni;
		std::vector<double> m_PetroVPreInv_wavelet_far_uni;
		double **m_PetroVPreInv_WM_near;
		int m_PetroVPreInv_WM_near_count;
		int m_PetroVPreInv_WM_near_sub_count;
		double **m_PetroVPreInv_WM_mid;
		int m_PetroVPreInv_WM_mid_count;
		int m_PetroVPreInv_WM_mid_sub_count;
		double **m_PetroVPreInv_WM_far;
		int m_PetroVPreInv_WM_far_count;
		int m_PetroVPreInv_WM_far_sub_count;
		std::vector<double> m_PetroVPreInv_Imp_Inv;
		std::vector<double> m_PetroVPreInv_Jmp_Inv;
		std::vector<double> m_PetroVPreInv_dens_Inv;	
		std::vector<double> m_LowPasFilterPetroV_winlow;
		CSyntheticWaveletEstimator::COMPLEX *m_LowPasFilterPetroV_mmsp;
		int m_LowPasFilterPetroV_mmsp_sub_count;
		std::vector<double> m_LowPasFilterPetroV_mm;
		double **m_LaMuRefInvForPetroV_seta;
		int m_LaMuRefInvForPetroV_seta_count;
		double **m_LaMuRefInvForPetroV_d;
		int m_LaMuRefInvForPetroV_d_count;
		double **m_LaMuRefInvForPetroV_transd;
		int m_LaMuRefInvForPetroV_transd_count;
		int m_LaMuRefInvForPetroV_transd_sub_count;
		double **m_LaMuRefInvForPetroV_crit;
		int m_LaMuRefInvForPetroV_crit_count;
		std::vector<double> m_Cal_Trend_PetroV_LImp;
		std::vector<double> m_Cal_Trend_PetroV_LJmp;
		std::vector<double> m_Cal_Trend_PetroV_Ldens;
		std::vector<double> m_Cal_Trend_PetroV_DImp;
		std::vector<double> m_Cal_Trend_PetroV_DJmp;
		std::vector<double> m_Cal_Trend_PetroV_Ddens;
		std::vector<double> m_LaMuRefInvForPetroV_Ism;
		std::vector<double> m_LaMuRefInvForPetroV_Jsm;
		std::vector<double> m_LaMuRefInvForPetroV_gama;
		std::vector<double> m_LaMuRefInvForPetroV_EImp;
		std::vector<double> m_LaMuRefInvForPetroV_EJmp;
		std::vector<double> m_LaMuRefInvForPetroV_Ed;
		std::vector<double> m_LaMuRefInvForPetroV_RImp;
		std::vector<double> m_LaMuRefInvForPetroV_RJmp;
		std::vector<double> m_LaMuRefInvForPetroV_Rd;
		FAIParameter m_LaMuRefInvForPetroV_fai;
		int m_LaMuRefInvForPetroV_fai_count1;
		int m_LaMuRefInvForPetroV_fai_count2;
		double **m_LaMuRefInvForPetroV_G;
		int m_LaMuRefInvForPetroV_G_count;
		int m_LaMuRefInvForPetroV_G_sub_count;
		double **m_LaMuRefInvForPetroV_GH;
		int m_LaMuRefInvForPetroV_GH_count;
		double **m_LaMuRefInvForPetroV_GlH;
		int m_LaMuRefInvForPetroV_GlH_count;
		double **m_LaMuRefInvForPetroV_GsH;
		int m_LaMuRefInvForPetroV_GsH_count;
		double **m_SoftConstrMatrPetroV_Glow_cut;
		int m_SoftConstrMatrPetroV_Glow_cut_count;
		double **m_SoftConstrMatrPetroV_Glow_In_cut;
		int m_SoftConstrMatrPetroV_Glow_In_cut_count;
		double **m_Trc_IntegralPetroV_I_tmp;
		int m_Trc_IntegralPetroV_I_tmp_count;
		double **m_Trc_IntegralPetroV_J_tmp;
		int m_Trc_IntegralPetroV_J_tmp_count;
		double **m_Trc_IntegralPetroV_d_tmp;
		int m_Trc_IntegralPetroV_d_tmp_count;
		double **m_Trc_IntegralPetroV_temp;
		int m_Trc_IntegralPetroV_temp_count;
		GdftParameter m_LowPassFilterMatrPetroV_gd;
		int m_LowPassFilterMatrPetroV_gd_count1;
		int m_LowPassFilterMatrPetroV_gd_count2;
		double **m_LowPassFilterMatrPetroV_Gidft_R;
		int m_LowPassFilterMatrPetroV_Gidft_R_count;
		int m_LowPassFilterMatrPetroV_Gidft_R_sub_count;
		double **m_LowPassFilterMatrPetroV_Gidft_I;
		int m_LowPassFilterMatrPetroV_Gidft_I_count;
		int m_LowPassFilterMatrPetroV_Gidft_I_sub_count;
		double **m_LowPassFilterMatrPetroV_Glow;
		int m_LowPassFilterMatrPetroV_Glow_count;
		int m_LowPassFilterMatrPetroV_Glow_sub_count;
		double **m_LaMuRefInvForPetroV_Q;
		int m_LaMuRefInvForPetroV_Q_count;
		double **m_LaMuRefInvForPetroV_transG;
		int m_LaMuRefInvForPetroV_transG_count;
		int m_LaMuRefInvForPetroV_transG_sub_count;
		double **m_LaMuRefInvForPetroV_transGl;
		int m_LaMuRefInvForPetroV_transGl_count;
		double **m_LaMuRefInvForPetroV_Gd;
		int m_LaMuRefInvForPetroV_Gd_count;
		double **m_LaMuRefInvForPetroV_GG1;
		int m_LaMuRefInvForPetroV_GG1_count;
		double **m_LaMuRefInvForPetroV_GG;
		int m_LaMuRefInvForPetroV_GG_count;
		double **m_LaMuRefInvForPetroV_invGG;
		int m_LaMuRefInvForPetroV_invGG_count;
		double **m_LaMuRefInvForPetroV_m;
		int m_LaMuRefInvForPetroV_m_count;
		std::vector<double> m_LaMuRefInvForPetroV_rtEImp;
		std::vector<double> m_LaMuRefInvForPetroV_rtEJmp;
		std::vector<double> m_LaMuRefInvForPetroV_rtEd;
		std::vector<double> m_LaMuRefInvForPetroV_rtmap;
		double **m_EstimatingFAIPetroV_Rmat;
		int m_EstimatingFAIPetroV_Rmat_count;
		double **m_CalMuPetroV_ds;
		int m_CalMuPetroV_ds_count;
		std::vector<double> m_BuildWeightForTriCauPetroV_win;
		double **m_Constr_Edge_Prot_PetroV_fain;
		int m_Constr_Edge_Prot_PetroV_fain_count;
		double **m_EstimatingFAIPetroV_fai;
		int m_EstimatingFAIPetroV_fai_count;
		double **m_EstimatingFAIPetroV_fai1;
		int m_EstimatingFAIPetroV_fai1_count;
		double **m_EstimatingFAIPetroV_invfai;
		int m_EstimatingFAIPetroV_invfai_count;
		double **m_EstimatingFAIPetroV_RR;
		int m_EstimatingFAIPetroV_RR_count;
		double **m_EstimatingFAIPetroV_transRR;
		int m_EstimatingFAIPetroV_transRR_count;
		double **m_EstimatingFAIPetroV_midRR;
		int m_EstimatingFAIPetroV_midRR_count;
		double **m_EstimatingFAIPetroV_ORRH;
		int m_EstimatingFAIPetroV_ORRH_count;
		double **m_EstimatingFAIPetroV_RRH;
		int m_EstimatingFAIPetroV_RRH_count;
		double **m_CalMuPetroV_dsH;
		int m_CalMuPetroV_dsH_count;
		double **m_BuildWeightForTriCauPetroV_fain_mu;
		int m_BuildWeightForTriCauPetroV_fain_mu_count;
		double **m_BuildWeightForTriCauPetroV_mm;
		int m_BuildWeightForTriCauPetroV_mm_count;
		double **m_BuildWeightForTriCauPetroV_transmm;
		int m_BuildWeightForTriCauPetroV_transmm_count;
		double **m_BuildWeightForTriCauPetroV_mid;
		int m_BuildWeightForTriCauPetroV_mid_count;
		double **m_BuildWeightForTriCauPetroV_QQ;
		int m_BuildWeightForTriCauPetroV_QQ_count;
		CSyntheticWaveletEstimator::COMPLEX *m_LowPassFilterMatrPetroV_New_winlow_complex;
		int m_LowPassFilterMatrPetroV_New_winlow_complex_sub_count;
	};
}

#endif
