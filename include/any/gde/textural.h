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
#ifndef __ANYGDE_TEXTURAL_H__
#define __ANYGDE_TEXTURAL_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CTextural : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CTextural();
		~CTextural();

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
		void Gal_Seis_Textural(int Nx, int Ny, int Nz, int Ng, int d, double Amp_max, double Amp_min, \
			double &Energy_inline, double &Energy_xline, double &Energy_time, double &Energy_mean, double &Entropy_inline, double &Entropy_xline, double &Entropy_time, double &Entropy_mean, \
			double &Contrast_inline, double &Contrast_xline, double &Contrast_time, double &Contrast_mean, double &Homogeneity_inline, double &Homogeneity_xline, double &Homogeneity_time, double &Homogeneity_mean);
		void Data2Gray(int Nx, int Ny, int Nz, int Ng, double Amp_max, double Amp_min);
		void Galculating_GLCM(int Nx, int Ny, int Nz, int Ng, int d);
		void Textural_Attribute(int Ng, double &Energy_inline, double &Energy_xline, double &Energy_time, double &Energy_mean, double &Entropy_inline, double &Entropy_xline, double &Entropy_time, double &Entropy_mean, \
			double &Contrast_inline, double &Contrast_xline, double &Contrast_time, double &Contrast_mean, double &Homogeneity_inline, double &Homogeneity_xline, double &Homogeneity_time, double &Homogeneity_mean);
	public:
		bool m_outEnergy;
		bool m_outEntropy;
		bool m_outContrast;
		bool m_outHomogeneity;
		bool m_outinline;
		bool m_outxline;
		bool m_outtime;
		bool m_outmean;
		int m_linebinnum;
		int m_cdpbinnum;
		int m_timebinnum;
		int m_graylev;
		int m_distance;
		double m_ampmax;
		double m_ampmin;

		// for reuse
		std::vector<std::vector<std::vector<double> > > m_data;
		std::vector<std::vector<std::vector<int> > > m_data_gray;
		std::vector<std::vector<double> > m_GLCM_inline;
		std::vector<std::vector<double> > m_GLCM_xline;
		std::vector<std::vector<double> > m_GLCM_time;
		bool m_isfirst;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}
#endif
