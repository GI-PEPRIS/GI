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
#ifndef __ANYGDE_GEOSTATISTICS_INVERSION_H__
#define __ANYGDE_GEOSTATISTICS_INVERSION_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include "syntheticwaveletestimator.h"


//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CGeostatisticsInversion
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CGeostatisticsInversion();
		~CGeostatisticsInversion();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle();
	public:
		//参数分析
		void Get_Miu0_C0(int N_well, string impedancecurvename, string timecurvename, std::vector<int> &selectedwelloffsets, \
			std::vector<CGeoPoint<double> > &wellpoints, std::vector<std::vector<string> > &curvenames,std::vector<std::vector<std::vector<double> > > &curvedatas, \
			double undef, std::vector<std::vector<std::vector<double> > > &Top_interface_buff, std::vector<std::vector<std::vector<double> > > &Bot_interface_buff, \
			int I_Layer, double Sample_statisc, double x_max_inline_min_xline, double y_max_inline_min_xline, double x_min_inline_min_xline, double y_min_inline_min_xline, \
			double x_min_inline_max_xline, double y_min_inline_max_xline, int min_inline, int min_xline, int max_inline, int max_xline, double &miu0, double &c0);
		void Cord_To_Line(double left_down_x_cord, double left_down_y_cord, int left_down_inline, int left_down_xline, \
			double right_down_x_cord, double right_down_y_cord, int right_down_inline, int right_down_xline, \
			double right_up_x_cord, double right_up_y_cord, int right_up_inline, int right_up_xline, std::vector<std::vector<double> > &rot_mat);
		void Get_Well_In_SM(std::vector<double> &Imp, std::vector<double> &time, double Top_Slope, double Bot_Slope, int N_microlayer, double Sample_microlayer, \
			int N_sample_well, double undef, std::vector<double> &Imp_SM);
		bool Cal_Exp_Var_2D_Discrete(std::vector<CGeoPoint<double> > &discretepts, int sectioncountx, int sectioncounty, \
			std::vector<std::vector<double> > &Var_2D, std::vector<std::vector<double> > &fold_2D, double &c0_hor, \
			double Ratio_Crit, std::vector<std::vector<double> > &Var_2D_show, std::vector<double> &x_axis_show, std::vector<double> &y_axis_show);
		void Cal_Exp_Var_2D(std::vector<std::vector<double> > &slice, int N_inline, int N_xline, std::vector<std::vector<double> > &Var_2D, std::vector<std::vector<double> > &fold_2D, double &c0_hor);
		void Show_Exp_Var_2D(std::vector<std::vector<double> > &Var_2D, std::vector<std::vector<double> > &fold_2D, int N_inline, int N_xline, double Ratio_Crit, double c0_hor, \
			std::vector<std::vector<double> > &Var_2D_show, std::vector<double> &x_axis_show, std::vector<double> &y_axis_show);
		void Cal_Seta(double x1, double y1, double x2, double y2, double bin_inline, double bin_xline, double &seta);
		void Cal_Exp_Var_Vertical(int N_well, string impedancecurvename, string timecurvename, std::vector<int> &selectedwelloffsets, \
			std::vector<CGeoPoint<double> > &wellpoints, std::vector<std::vector<string> > &curvenames,std::vector<std::vector<std::vector<double> > > &curvedatas, \
			double undef, std::vector<std::vector<std::vector<double> > > &Top_interface_buff, std::vector<std::vector<std::vector<double> > > &Bot_interface_buff, \
			int I_Layer, double lag_ver, double Max_lag_ver, double x_max_inline_min_xline, double y_max_inline_min_xline, double x_min_inline_min_xline, double y_min_inline_min_xline, \
			double x_min_inline_max_xline, double y_min_inline_max_xline, int min_inline, int min_xline, int max_inline, int max_xline, double c0, \
			std::vector<double> &Var_Exp_Ver, std::vector<double> &N_Pair_Ver, std::vector<double> &x_axis_Ver);
		void Show_Exp_Var_Hor(std::vector<std::vector<double> > &Var_2D, std::vector<std::vector<double> > &fold_2D, int N_inline, int N_xline, double bin_inline, double bin_xline, \
			double seta, double angle_tol, double Bandwidth, double Max_lag_hor, double lag_hor, double c0_hor, \
			std::vector<double> &Var_Exp_Hor1, std::vector<double> &N_Pair_Hor1, std::vector<double> &Var_Exp_Hor2, std::vector<double> &N_Pair_Hor2, std::vector<double> &x_axis_Hor);
		void Cal_ATAN(double y, double x, double &fai);
		void Cal_Theory_Var_Ver(double Weight_Exp, double Weight_Guass, double Weight_Nug, double lag_ver, double Max_lag_ver, double Ver_Range, std::vector<double> &Var_Theory_Ver, std::vector<double> &h_Ver);
		void Cal_Theory_Var_Hor_1(double Weight_Exp, double Weight_Guass, double Weight_Nug, double lag_hor, double Max_lag_hor, double Hor_Range_1, std::vector<double> &Var_Theory_Hor1, std::vector<double> &h_Hor1);
		void Cal_Theory_Var_Hor_2(double Weight_Exp, double Weight_Guass, double Weight_Nug, double lag_hor, double Max_lag_hor, double Hor_Range_2, std::vector<double> &Var_Theory_Hor2, std::vector<double> &h_Hor2);
		//反演
		void Geostatistical_Inversion_3D(string stratigraphy_grid_file, std::vector<CAnyGdeDataSet*> &datasets, std::vector<bool> &isgdes, int inputdataoffset, CSyntheticWaveletEstimator::Wavelet &wav, string Inv_file, \
			int N_well, string impedancecurvename, string timecurvename, std::vector<int> &selectedwelloffsets, \
			std::vector<CGeoPoint<double> > &wellpoints, std::vector<std::vector<string> > &curvenames, std::vector<std::vector<std::vector<double> > > &curvedatas, \
			double undef, int N_Layer, std::vector<int> &N_microlayer_buff, \
			std::vector<std::vector<std::vector<double> > > &Top_slope_buff, std::vector<std::vector<std::vector<double> > > &Bot_slope_buff, \
			std::vector<std::vector<std::vector<double> > > &Top_interface_buff, std::vector<std::vector<std::vector<double> > > &Bot_interface_buff, \
			std::vector<int> &stratigraphy_choice, double Top_offset, double Bot_offset, std::vector<double> &survey_info, std::vector<double> &Inver_Para, std::vector<std::vector<double> > &Geostatistic_Para, \
			int start_inline, int end_inline, int start_xline, int end_xline, double start_time, int N_sample, double Int_sample, double start_time_wave, int N_wave, int Fm);
		void Get_Geostatistic_Para(std::vector<std::vector<double> > &Geostatistic_Para, int N_Search, int N_layer, double bin_inline, std::vector<double> &miu0, std::vector<double> &c0, \
			std::vector<double> &Hor_ratio, std::vector<double> &Ver_Range, std::vector<double> &Ver_ratio, std::vector<double> &seta, std::vector<double> &cos_seta, std::vector<double> &sin_seta, \
			std::vector<double> &Weight_Guass, std::vector<double> &Weight_Expon, std::vector<double> &Weight_Nugget, std::vector<double> &a_G, std::vector<double> &a_E, std::vector<double> &aa, std::vector<double> &bb);
		void Get_Oblique_Ellipse_Region(double aa, double bb, double seta, double bin_inline, double bin_xline, std::vector<double> &x_Region, std::vector<double> &y_Region, int &Numb_point);
		void Initial_stratigraphy_grid(string stratigraphy_grid_file, int max_inline, int min_inline, int max_xline, int min_xline, \
			double x_min_inline_min_xline, double y_min_inline_min_xline, double x_max_inline_min_xline, double y_max_inline_min_xline, double x_min_inline_max_xline, double y_min_inline_max_xline, \
			int N_well, string impedancecurvename, string timecurvename, std::vector<int> &selectedwelloffsets, \
			std::vector<CGeoPoint<double> > &wellpoints, std::vector<std::vector<string> > &curvenames, std::vector<std::vector<std::vector<double> > > &curvedatas, \
			double undef, int N_Layer, std::vector<int> &N_microlayer_buff, std::vector<std::vector<std::vector<double> > > &Top_slope_buff, std::vector<std::vector<std::vector<double> > > &Bot_slope_buff, \
			int start_inline, int end_inline, int start_xline, int end_xline, std::vector<int> &inline_well_buff, std::vector<int> &xline_well_buff, int &N_well_new);
		void Cal_Valid(std::vector<int> &head, int N_layer, int &Valid);
		void CGeostatisticsInversion::Read_Grid_File_CDP(void *fid, int Inline, int xline, int N_xline, int trace_byte, int min_inline, int min_xline, int N_Layer, int N_microlayer_total, \
			std::vector<int> &head, std::vector<float> &grid_data);
		void CGeostatisticsInversion::Get_Grid_File_Offset(int Inline, int xline, int N_xline, int trace_byte, int min_inline, int min_xline, long long &offset, int &Cur_trace);
		void CGeostatisticsInversion::Read_Seis_CDP(std::vector<CAnyGdeDataSet*> &datasets, std::vector<bool> &isgdes, int inputdataoffset, int N_sample, int Inline, int xline, int min_inline, int min_xline, int N_xline, int Fm, std::vector<float> &Seis);
		void CGeostatisticsInversion::Get_Wave_Re(std::vector<double> &wave, double start_time_wav, int N_wave, double Int_sample, double Sample_microlayer, std::vector<double> &wave_re, int &N_wave_re);
		void CGeostatisticsInversion::Get_Seis_Re(std::vector<float> &Seis, double start_time, int N_sample, double Int_sample, double Top_Slope, int N_microlayer, double Sample_microlayer, \
			double start_time_wave, int N_wave_re, double scale, std::vector<float> &Seis_re);
		void interp_line(std::vector<double> &T1, std::vector<float> &V1, std::vector<double> &T2, std::vector<float> &V2);
		void interp_line(std::vector<double> &T1, std::vector<double> &V1, std::vector<double> &T2, std::vector<double> &V2);
		void Cal_Condition_Miu_C_from_Reigon_3D_Well(int Cur_Inline, int Cur_Xline, std::vector<int> &Buff_Condition_Inline, std::vector<int> &Buff_Condition_Xline, \
			std::vector<std::vector<double> > &Buff_Condition_Value, int N_Condition_Traces, double N_Condition_Sample_Half, double Sample_microlayer, int N_microlayer, \
			double bin_inline, double bin_xline, double miu0, double c0, double Hor_ratio, double Ver_ratio, double cos_seta, double sin_seta, double Weight_Guass, \
			double Weight_Expon, double Weight_Nugget, double a_G, double a_E, std::vector<double> &Buff_Miu_Pre, std::vector<double> &Buff_C_Condition, \
			std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord);
		void Cal_Cov_3D(double dx, double dy, double dz, double Hor_ratio, double Ver_ratio, double cos_seta, double sin_seta, \
			double Weight_Guass, double Weight_Expon, double Weight_Nugget, double a_G, double a_E, double &cov);
		void Cal_Region_Cord(int Seed, double Range, int start_cord, int end_cord, std::vector<int> &Region_cord, int &N_Region);
		void Get_C_Mat_Seed(std::vector<std::vector<double> > &C_Mat, std::vector<double> &Y_Mat, int N_Region, std::vector<int> &Region_cord, int N_Condition_Traces, \
			std::vector<int> &Buff_Condition_Inline, std::vector<int> &Buff_Condition_Xline, int Cur_Inline, int Cur_Xline, double bin_inline, double bin_xline, double Sample_microlayer, \
			double Hor_ratio, double Ver_ratio, double cos_seta, double sin_seta, double Weight_Guass, double Weight_Expon, double Weight_Nugget, double a_G, double a_E, int Seed_Ver);
		void Get_Para_Buff_1(std::vector<double> &lamda, std::vector<double> &Y_Mat_New, std::vector<std::vector<double> > &Buff_Condition_Value, std::vector<double> &Buff_Miu_Pre, \
			std::vector<double> &Buff_C_Condition, std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord, \
			int N_Condition_Traces, int N_Region, std::vector<int> &Region_cord, double miu0, double c0, int Seed_Ver);
		void Get_Para_Buff_2(std::vector<double> &lamda, std::vector<double> &Y_Mat_New, std::vector<double> &Buff_Miu_Pre, \
			std::vector<double> &Buff_C_Condition, std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord, \
			int N_Region, std::vector<int> &Region_cord, double miu0, double c0, int Seed_Ver);
		void MCMC_Sequense_Gibbs_Sampling_LN_Well(std::vector<float> &Seis_Re, std::vector<double> &wave_Re, double miu0, std::vector<std::vector<double> > &Buff_lamda_Cur, \
			std::vector<double> &Buff_Miu_Pre, std::vector<double> &Buff_C_Condition, int N_Iter, double S2N_max, int N_microlayer, int N_Iter_Pre, std::vector<int> &Buff_N_Condition_Sample, \
			std::vector<std::vector<double> > &Buff_Coord, double S2N_W_max, std::vector<float> &Imp_Well, std::vector<double> &Realization, std::vector<double> &Res);
		void randperm(int N, std::vector<int> &randvec);
		static bool ComparePositionX(const CGeoPoint<double> &a, const CGeoPoint<double> &b);
		void LN_Sampling(double miu, double c, double &Realization);
		double GaussRand(double mean, double std_dev);
		void Cal_Energy_Overall_Std(std::vector<float> &Seis_Re, std::vector<double> &wave_Re, std::vector<double> &Realization, int N_microlayer, int E_cord_1, int E_cord_2, double S2N, \
			double &E_Noise, std::vector<double> &error_Vec_S, double &sigma_S);
		void DoConvolution(std::vector<double> &v1, std::vector<double> &v2, std::vector<double> &v3);
		void Cal_Energy_Overall_Well(std::vector<float> &Imp_Well, int N_microlayer, std::vector<double> &Realization, double S2N_W, \
			double &E_Noise_W, std::vector<double> &error_Vec_W, double &sigma_W);
		void Cal_Energy_Seed_Std(std::vector<double> &wave_Re, std::vector<double> &Realization, double Realization_Seed, int Seed, std::vector<double> &error_Vec_S, int lw, int lr, int N_microlayer, \
			int E_cord_1, int E_cord_2, double &E_change_S, std::vector<double> &error_Vec_S_Seed, std::vector<int> &Seed_cord);
		void Cal_Energy_Seed_Well(double Realization_Seed, int Seed, std::vector<double> &error_Vec_W, std::vector<float> &Imp_Well, double &E_change_W, double &error_Vec_W_Seed);
		void Replace_Ele_To_Vec(std::vector<double> &realization_old, std::vector<double> &realization_Seed, std::vector<int> &Seed_cord);
		void Replace_Ele_To_Vec(std::vector<double> &realization_old, double &realization_Seed, int &Seed_cord);
		void Cal_S2N_Std(std::vector<double> &realization, std::vector<double> &wave_Re, double E_Noise_S, int N_microlayer, int E_cord_1, int E_cord_2, double &S2N);
		void Cal_S2N_Well(std::vector<double> &Realization, double E_Noise_W, double &S2N_W);
		void Cal_Condition_Miu_C_from_Reigon_3D_New(int Cur_Inline, int Cur_Xline, std::vector<int> &Buff_Condition_Inline, std::vector<int> &Buff_Condition_Xline, \
			std::vector<std::vector<double> > &Buff_Condition_Value, int N_Condition_Traces, double N_Condition_Sample_Half, double Sample_microlayer, int N_microlayer, \
			double bin_inline, double bin_xline, double miu0, double c0, double Hor_ratio, double Ver_ratio, double cos_seta, double sin_seta, double Weight_Guass, \
			double Weight_Expon, double Weight_Nugget, double a_G, double a_E, std::vector<double> &Buff_Miu_Pre, std::vector<double> &Buff_C_Condition, \
			std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord);
		void Get_Para_Buff_1_Mid(std::vector<double> &lamda, double C_condition_Mid, std::vector<std::vector<double> > &Buff_Condition_Value, std::vector<double> &Buff_Miu_Pre, \
			std::vector<double> &Buff_C_Condition, std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord, \
			int N_Condition_Traces, int N_Region, std::vector<int> &Region_cord, double miu0, int Seed_Ver);
		void Get_Para_Buff_1_Mirror(std::vector<double> &lamda, std::vector<std::vector<double> > &Buff_Condition_Value, std::vector<double> &Buff_Miu_Pre, \
			std::vector<double> &Buff_C_Condition, std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord, \
			int N_Condition_Traces, int N_Region, std::vector<int> &Region_cord, double miu0, int Seed_Ver, int Mirror);
		void Get_Para_Buff_2_Mid(std::vector<double> &lamda, double C_condition_Mid, std::vector<double> &Buff_Miu_Pre, \
			std::vector<double> &Buff_C_Condition, std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord, \
			int N_Region, std::vector<int> &Region_cord, double miu0, int Seed_Ver);
		void Get_Para_Buff_2_Mirror(std::vector<double> &lamda, std::vector<double> &Buff_Miu_Pre, \
			std::vector<double> &Buff_C_Condition, std::vector<std::vector<double> > &Buff_lamda_Cur, std::vector<int> &Buff_N_Condition_Sample, std::vector<std::vector<double> > &Buff_Coord, \
			int N_Region, std::vector<int> &Region_cord, double miu0, int Seed_Ver, int Mirror);
		void Get_New_C_Mat(std::vector<std::vector<double> > &C_Mat, int N_Total, int M);
		void Get_New_Y_Mat(std::vector<double> &Y_Mat, int N_Total, int M);
		void Generate_Inv_Data(std::vector<CAnyGdeDataSet*> &datasets, std::vector<bool> &isgdes, int inputdataoffset, void *fid_grid, string Inv_file, std::vector<std::vector<std::vector<double> > > &Top_slope_buff, std::vector<std::vector<std::vector<double> > > &Bot_slope_buff, \
			std::vector<std::vector<std::vector<double> > > &Top_interface_buff, std::vector<std::vector<std::vector<double> > > &Bot_interface_buff, \
			std::vector<int> &N_microlayer_buff, std::vector<int> &stratigraphy_choice, int N_Layer, \
			double Top_offset, double Bot_offset, int N_inline, int N_xline, int N_inline_Inv, int N_xline_Inv, double start_time, int Int_Sample_Inv, int min_inline, int min_xline, int start_inline, int start_xline);
		void Cal_Numb_Sample_Inv(std::vector<std::vector<std::vector<double> > > &Top_interface_buff, std::vector<std::vector<std::vector<double> > > &Bot_interface_buff, \
			int N_layer, int Int_Sample_Inv, double Top_offset, double Bot_offset, int N_inline, int N_xline, double start_time, double &start_time_Inv, int &N_sample_Inv);
		void HorTime_Map_To_SeisTime(double Top_time, double Bot_time, double start_time, int Int_Sample, double &Top_time_Seis, double &Bot_time_Seis, int &Top_cord, int &Bot_cord);
		void Truncated_Stratigraphy_Grid(std::vector<float> &grid_data, std::vector<int> &head, int N_layer, std::vector<double> &Top_slope, std::vector<double> &Bot_slope, \
			std::vector<double> &Top_interface, std::vector<double> &Bot_interface, std::vector<int> &N_microlayer_buff, std::vector<int> &stratigraphy_choice);
		void Convert_Stratigraphy_Grid_To_SGY(std::vector<float> &grid_data, std::vector<int> &head, int N_layer, std::vector<double> &Top_slope, std::vector<double> &Bot_slope, \
			std::vector<double> &Top_interface, std::vector<double> &Bot_interface, std::vector<int> &N_microlayer_buff, 
			double start_time_Inv, int N_sample_Inv, int Sample_Int_Inv, double Top_offset, double Bot_offset, std::vector<float> &data_Inv);
	};
}
#endif
