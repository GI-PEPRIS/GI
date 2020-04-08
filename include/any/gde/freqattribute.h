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
#ifndef __ANYGDE_FREQATTRIBUTE_H__
#define __ANYGDE_FREQATTRIBUTE_H__

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
	class ANYGDE_CLASS CFreqAttribute : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CFreqAttribute();
		~CFreqAttribute();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle(HandlerStruct &handlerstruct);

		/*!
		*
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		*
		**/
		void DoGetTraceHead(std::vector<double> &results);
		
		/*!
		*
		**/
		void Short_Time_Fourier_Trasform_new(std::vector<double> &data, int Half_win, int pad_numb, int start_time, int N_sample, int samp_int, double Top_time, double Bot_time, \
			double start_freq, double end_freq, double first_freq, double second_freq, int fit_choice, int win_choice, \
			std::vector<double> &Peak_Amp, std::vector<double> &Peak_Freq, std::vector<double> &Highlight, std::vector<double> &Fluid_Mobility);
		void Short_Time_Fourier_Trasform_show_amp_spe_new(std::vector<double> &data, int pad_numb, int Ana_time, int start_time, int N_sample, int samp_int, int Half_win, int win_choice, \
			std::vector<double> &amp_spe, std::vector<double> &freq_vec);
		void Curve_Fit(std::vector<double> &x, std::vector<double> &y, int N, int fit_choice, double &a, double &b);
		void Freq_Attr(std::vector<double> &amp_spe, std::vector<double> &freq_vec, int valid_numb, double freq_int, double start_freq, double end_freq, double first_freq, double second_freq, int fit_choice, \
			double &Peak_Amp, double &Peak_Freq, double &Highlight, double &Fluid_Mobility);
	public:
		int m_Half_win;
		int m_pad_numb;
		double m_start_freq;
		double m_end_freq;
		double m_first_freq;
		double m_second_freq;
		int m_fit_choice;
		int m_win_choice;

		bool m_out_peakamp;
		bool m_out_peakfreq;
		bool m_out_highligth;
		bool m_out_fluidmobility;

		int m_Ana_time;

		// for malloc reuse
		CSyntheticWaveletEstimator::COMPLEX *m_Win_data_pad;
		double **m_G;
		double **m_G_inv;
		CSyntheticWaveletEstimator::COMPLEX *m_w;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}
#endif
