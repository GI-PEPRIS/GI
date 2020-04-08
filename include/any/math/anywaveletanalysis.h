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
#ifndef __ANYMATH_WAVELET_ANALYSIS_H__
#define __ANYMATH_WAVELET_ANALYSIS_H__

// refer to macro
#include "anymath.h"

#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

#include "any/thread/monitor.h"

namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyWaveletAnalysis : public JTCMonitor
	{
	public:
		//
		typedef struct Filter {
			double const * const (filter[4]);
			unsigned int const len_filter;
		} Filter;

	public:
		//
		enum WaveletType
		{
			WT_Unknown = -1,
			WT_Morlet,
			WT_Paul,
			WT_Meyer,
			WT_Max,
		};

		struct SimpleTaskParameter
		{
			long m_from;
			long m_to;

			SimpleTaskParameter() : m_from(0), m_to(0)
			{
			}
		};

		//////
		//
		enum GeologicalAge
		{
			GA_Unknown = -1,
			GA_Holocene,
			GA_K2,
			GA_P1,
			GA_C3,
			GA_D2,
			GA_S1,
			GA_Max
		};

		enum MilanGeoAge
		{
			MGA_Unknown = -1,
			MGA_40,
			MGA_10,
			MGA_4,
			MGA_2,
			MGA_Max
		};
		struct MilanCycleFrequencyRatio
		{
			double m_A;
			double m_AA;
			double m_B;
			double m_C;
			double m_D;
			double m_E;
			double m_F;
		};
		typedef std::map<short, MilanCycleFrequencyRatio> MilanIndicatorMap;
		typedef std::vector<MilanIndicatorMap> MilanIndicatorMapVector;

		struct MilanIndicator
		{
			int m_order;
			double m_cycleratio;
			double m_frequenceratio;
		};
		typedef std::vector<MilanIndicator> IndicatorVector;

		//
		//
		enum LithologicalFormationType
		{
			LFT_Unknown,
			LFT_Mud,
			LFT_Sand,
			LFT_Max
		};
		struct CompactingFactor
		{
			double m_a;
			double m_b;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyWaveletAnalysis(double samplerate = 1000., double minfreq = .1, double maxfreq = 500., double bandsperoctave = 8.);
		~CAnyWaveletAnalysis();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetSample(const std::vector<CGeoPoint<double> > &samples);
		void GetSamples(std::vector<CGeoPoint<double> > &samples);
		void EraseWildValue(double min, double max, double invalid);
		void HighPassFilter(double frequency);
		void HighPassFilter(double cutoff, int order,double rippleLevel);

		//
		//
		//
		/*!
		*
		**/
		void MakeCWT(CAnyFunctor &progress, bool isThreaded = false);
		void MakeCWT(bool isThreaded = false);

		void MakeSWT(const std::vector<CGeoPoint<double> > &samples, int mode = 0, int order = 2, int level = 1);
		void MakeDWT(const std::vector<CGeoPoint<double> > &samples, int mode = 0, int order = 2, int level = 1);

		//
		//
		//
		int GetScaleNumber();
		double GetScaleFrequency(int i);
		void GetScalePower(int order, std::vector<CGeoPoint<double> > &tracesamples);
		void GetScaleCurve(int order, std::vector<CGeoPoint<double> > &curvesamples);
		void GetScaleModel(std::vector<CGeoPoint<double> > &modelsamples);
		void GetScaleCycle(std::vector<CGeoPoint<double> > &cyclesamples);

		//
		//
		//
		void SetMilankovitchCylceIndicator(int whichage, const MilanCycleFrequencyRatio &standard);
		void SetMilankovitchFrequencyIndicator(int whichage, const MilanCycleFrequencyRatio &standard);
		void ScanFrequencyMilanIndicator(int order, IndicatorVector &indicators, short whichage = MGA_10);
		void ScanCycleMilanIndicator(int order, IndicatorVector &indicators, short whichage = MGA_10);

		//
		//
		//
		void CalculateGeologicalTimingCurve(int order, double fromage, double cycleage, double deltaage);
		
	private:
		//
		void DoWithSimpleTaskThread(const SimpleTaskParameter &parameter);
		static bool CompareScaleCurveSample(const CGeoPoint<double> &first, const CGeoPoint<double> &second)
		{
			return first.m_x < second.m_x;
		}
		void DoFindExtreme(int n, double *v, double *vDiff, int *E);
		void DoFindCycle(int n, double *v, int *E, double *angle);
		void DoFindCycleInHalfPi(int n, double *v, int *E, double *angle);
		void DoFindCycleInPi(int n, double *v, int *E, double *angle);
		int SIGN(double v);
		int SIGN(double v, double mean);
		bool IsMilankovitchFrequency(double ratio, short geoage = MGA_10);
		bool IsMilankovitchCycle(double ratio, short geoage = MGA_10);
		double DoCalculatePhase(double real, double imag);
		double DoEraseCompactEffect(double from, double to);

		void DoMakeSWT(float *input, int input_len, double fromdepth, double todepth, std::vector<CGeoPoint<double> > &acurve, std::vector<CGeoPoint<double> > &dcurve, int level = 1);
		void DoMakeDWT(float *input, int input_len, double fromdepth, double todepth, std::vector<CGeoPoint<double> > &acurve, std::vector<CGeoPoint<double> > &dcurve, int level = 1);

		//
		int DoDwt(float *sourceData, int dataLen, Filter db, float *cA, float *cD);
		void DoIdwt(float *cA, float *cD,  int cALength, Filter db, float *recData);

	public:
		//
		std::vector<CGeoPoint<double> > m_samples;
		int m_scalenumber;
		std::vector<double> m_scalevalues;
		std::vector<double> m_scalefrequencies;
		std::vector<double> m_scalecycles;

		std::vector<std::vector<CGeoPoint<double> > > m_scalecurves;
		std::vector<std::vector<CGeoPoint<double> > > m_scalephases;
		std::vector<CGeoPoint<double> > m_sedimentarycurve;

		//
		double m_samplerate;
		double m_minfreq;
		double m_maxfreq;
		double m_bandsperoctave;

		//
		double m_ratiolimit;
		int m_geologicalage;
		MilanIndicatorMapVector m_milancycleratioes;
		MilanIndicatorMapVector m_milanfrequencyratioes;

		// lithological explaination
		double m_mudpercent;
		string m_lithoformula;
		std::vector<CGeoPoint<double> > m_lithocurve;
		CompactingFactor m_mudfactor;
		CompactingFactor m_sandfactor;

		//
		short m_timingphaseway;
		double m_timingdepthlimit;
		
		// discrete wavelet transformation
		int m_swtmode;
		int m_swtlevel;
		std::vector<std::vector<CGeoPoint<double> > > m_swtacurves;
		std::vector<std::vector<CGeoPoint<double> > > m_swtdcurves;
	};
}

#endif
