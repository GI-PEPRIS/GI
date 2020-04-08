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
#ifndef __ANYGDE_IRREGULAR_H__
#define __ANYGDE_IRREGULAR_H__

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
	class ANYGDE_CLASS CIrregular : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CIrregular();
		~CIrregular();

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
		void Getting_Scaling(std::vector<double> &TVD, std::vector<double> &AC, std::vector<double> &DENS, double Undef, int N_sample_well, \
			double start_depth_seis, int N_sample_seis, double dDepth_seis, std::vector<double> &Seis, int depth_shift, double &scale_factor);
		void FC_4order_Fit_Irregular(std::vector<double> &Rpp, std::vector<double> &fai_vec, double lamda, int Niter, double &r0, double &r2, double &r4, double &Polor);
		void Cal_Error_Weight(std::vector<std::vector<double> > &G, std::vector<double> &d, std::vector<double> &x, int N, std::vector<std::vector<double> > &W);
		void Cal_Error_Weight(std::vector<std::vector<double> > &G, std::vector<double> &d, std::vector<double> &x, int N, std::vector<double> &W);
		void IntpLine(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &t, int n, int m, std::vector<double> &z);
		void Getting_Rc(std::vector<double> &TVD, std::vector<double> &AC, std::vector<double> &Dens, double dDepth_seis, double Undef, int N_sample_well, double start_depth_seis, int depth_shift,\
			int N_sample_seis, std::vector<double> &Rc, double &start_depth_log, double &end_depth_log);
		void Cal_Scaling_Window(double start_depth_seis, int N_sample_seis, double dDepth_seis, double start_depth_log, double end_depth_log, double &Top_depth, double &Bot_depth, int &wav_sample);
		void Cal_Wav_Depth_Auto(double Top_depth, double Bot_depth, std::vector<double> &Seis, double start_depth_seis, double dDepth_seis, int wav_sample, std::vector<double> &Wav_auto, std::vector<double> &seis_cal);
		void Convolution(std::vector<double> &v1, std::vector<double> &v2, std::vector<double> &v3);
		double CrossCorlation(const std::vector<double> &x, const std::vector<double> &y);
		void Cor_Cor(std::vector<double> &x,std::vector<double> &y,std::vector<double> &cor );
		void Cal_Amp_Spe( CSyntheticWaveletEstimator::COMPLEX *Spe,int pad_num,std::vector<double>&Amp_Spe );
		void Highcut_Win( double high_pass,double high_cut,double DF,int pad_num,std::vector<double>&W );
		void Cal_cord_for_zero_ph( double wav_length,int wav_samp,int pad_num,double samp_int,std::vector<int>&cord_zero_ph );
		void Papoulis_Taper( int N_sample,std::vector<double> &Taper );
		void Calinverse(double **rhs, double **m, int stRank);
	public:
		double m_azimuthlow;
		double m_azimuthhigh;
		int m_azimuthgroup;
		double m_anglelow;
		double m_anglehigh;
		int m_Niter;
		double m_lamda;
		int m_depth_shift;
		int m_linebinnum;
		int m_cdpbinnum;
		double m_scalefactor;

		std::vector<double> m_r0_output;
		std::vector<double> m_r2_output;
		std::vector<double> m_r4_output;
		std::vector<double> m_polor_output;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}

#endif
