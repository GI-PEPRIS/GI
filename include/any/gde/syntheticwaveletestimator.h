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
#ifndef __ANYGDE_SYNTHETIC_WAVELET_ESTIMATOR_H__
#define __ANYGDE_SYNTHETIC_WAVELET_ESTIMATOR_H__

// refer to export/import macro
#include "anygde.h"

#include "any/base/anystl.h"
#include "any/base/anyport.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

// 
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CSyntheticWaveletEstimator
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		enum TraceSampleType
		{
			TST_Unknown,
			TST_Log_AC_TVD,																// ����ʱ������ 
			TST_Log_AC_TVD_Backus,												// ����ʱ������, backus filter
			TST_Log_AC_Time,															// ����ʱ������
			TST_Log_SAC_TVD,															// �Შ����ʱ����������
			TST_Log_SAC_TVD_Backus,											// �Შ����ʱ����������, backus filter
			TST_Log_SAC_Time,															// �Შ����ʱ����������
			TST_Log_Density_TVD,														// �ܶ�����
			TST_Log_Density_TVD_Backus,										// �ܶ�����, backus filter
			TST_Log_Density_Time,														// �ܶ�����
			TST_Log_xshift_TVD,															// ��б��xshift 
			TST_Log_xshift_Time,															// ��б��xshift
			TST_Log_yshift_TVD,															// ��б��yshift 
			TST_Log_yshift_Time,															// ��б��yshift
			TST_Log_Time_TVD,											// �⾮���ߵ�ʱ������
			TST_Log_Time_TVD_Original,							// ����ѹ��ǰ��Ӧ��ʱ�����У�����򣩣�����
			TST_Log_TVD,														// �⾮�Ĵ�ֱ��ȣ������
			TST_Log_Depth,														// �⾮����ȣ������
			TST_Log_Time_Seismic,									// ʱ����⾮���߶�Ӧ��ʱ�����У����򵽵�����������- ʱ������ϵ������
			TST_Log_TVD_Seismic,									// ����궨������ʾ�Ĳ⾮��ֱ��� unused
			TST_show_Time,                                          // ����궨������ʾ��ʱ�� unused

			TST_Seismic_Post_Reflection,							// ������ϵ��
			TST_Seismic_P_Impedence,						     // P���迹
			TST_Seismic_P_Velocity,								// P���ٶ�����
			TST_Seismic_S_Velocity,				  				// S���ٶ�����
			TST_Seismic_Trace_Amplitude,						// ��ǰ���������
			TST_Seismic_Trace_Amplitude_Show,			      // ��������ʾ�ľ��Ե������
			TST_Seismic_Trace_Time,									// �������ʱ��
			TST_Seismic_Synthetic_Amplitude,					// �ϳɵ����¼
			TST_Seismic_Synthetic_Amplitude_Original,			// scaleǰ�ĺϳɵ����¼
			TST_Seismic_Synthetic_Time,							// �ϳɵ����¼��Ӧ��ʱ������
			TST_Seismic_Synthetic_Time_Original,			// ʱ���ϵ����ǰ�ĺϳɵ����¼��Ӧ��ʱ������
			TST_Seismic_Correlation_Value,						// �����ϵ��	unused,��TraceVectorVector correlations ����
			TST_Seismic_Correlation_Time,						// �����ϵ��ʱ������	
			TST_Seismic_PP_Reflection,							// P���Ƕȷ���ϵ��
			TST_Seismic_PP_Transmission,						// P���Ƕ�͸��ϵ��
			TST_Seismic_PS_Reflection,							// S���Ƕȷ���ϵ��
			TST_Seismic_PS_Transmission,		 				// S�Ƕ�͸��ϵ��

			TST_Wavelet_Trace,											// �Ӳ��������� 
			TST_Wavelet_Trace_Original,									// scaleǰ���Ӳ��������� 
			TST_Wavelet_Amplitude,									// �Ӳ������  
			TST_Wavelet_Amplitude_Show,							// ��ʾ���Ӳ������
			TST_Wavelet_Phase,											// �Ӳ�����λ��
			TST_Wavelet_Phase_Show,								// �Ӳ�����λ��
			TST_Wavelet_Frequency,									//  ����׺�����׶�Ӧx��Ƶ��
			TST_Wavelet_Frequency_Show,						//  ������x���Ӧ��Ƶ����ʾ
			TST_Wavelet_Time,												// �Ӳ�ʱ������

			TST_Horizon_Top,												// ��Ӧ��ʱ�����У���Ϊ�ز�͵�ʱ����
			TST_Horizon_Bottom,
			TST_Max
		};
		typedef std::vector<double> TraceSampleVector;
		typedef std::vector<TraceSampleVector > TraceVectorVector;
		typedef std::map<unsigned short, TraceSampleVector> TraceVectorMap;
		typedef TraceVectorMap::iterator trace_mitr;
		typedef TraceVectorMap::const_iterator trace_cmitr;

		typedef std::map<double, TraceVectorMap> TraceAngleMap;
		typedef TraceAngleMap::iterator trace_aitr;
		typedef TraceAngleMap::const_iterator trace_caitr;


		/*!
		*
		**/
		struct TraceSampleSpecification
		{
			// �����¼����ʼʱ�䣬�ӵ�ͷ���л�ȡ��int����λms��
			double m_starttime;
			// ���¼�Ĳ����������ӵ�ͷ���л�ȡ��int��
			int m_number;
			// �����¼�Ĳ����ʣ��ӵ�ͷ���л�ȡ��int����λms��
			double m_interval;
			// �Ӳ����У���ļ���ʱ����������Ϊ�ز���ʱ���֣���Ϊ�ز�����£�Ϊ��λ���뾮����ĵ�����ཻ���ʱ�䣨int����λms��
			double m_toptime;
			// �Ӳ����У���ļ���ʱ���ײ�����Ϊ�ز���ʱ���֣���Ϊ�ز�����£�Ϊ��λ���뾮��ĵ�����ཻ���ʱ�䣨int����λms��
			double m_bottomtime;

			TraceSampleSpecification() : m_starttime(ANY_NAN), m_number(0), m_interval(ANY_NAN), m_toptime(ANY_NAN), m_bottomtime(ANY_NAN)
			{

			}
			TraceSampleSpecification(const TraceSampleSpecification &other)
			{
				*this = other;
			}
			const TraceSampleSpecification &operator=(const TraceSampleSpecification &other)
			{
				if(this != &other)
				{
					m_starttime = other.m_starttime; 
					m_number = other.m_number; 
					m_interval = other.m_interval; 
					m_toptime = other.m_toptime; 
					m_bottomtime = other.m_bottomtime; 
				}
				return *this;
			}
		};

		/*!
		*
		**/
		struct WellSampleSpecification
		{
			int m_starttime;
			int m_samples;
			WellSampleSpecification(){}
			WellSampleSpecification(const WellSampleSpecification &other)
			{
				*this = other;
			}
			const WellSampleSpecification &operator=(const WellSampleSpecification &other)
			{
				if(this != &other)
				{
					m_starttime = other.m_starttime; 
					m_samples = other.m_samples; 
				}
				return *this;
			}
		};

		/*!
		*
		**/
		struct Wavelet
		{
			//
			double m_starttime; //�Ӳ�����ʼʱ�䣨default��-50ms��
			double m_phaseshift; //�Ӳ������ƶ�����default��0�ȣ�
			int m_wavelength; // �Ӳ��Ĳ��γ��ȣ�default��100ms��
			double m_sampleinterval; //�Ӳ���ʱ����������default��1ms��
			double m_domainfrequence; //�Ӳ�����Ƶ��default��30Hz��
			int m_number; //�Ӳ�������

			//
			double m_miu;	// ����λ�Ӳ��ȶ�ϵ�����ò����ſ������û�������д��default==1��
			double m_highcut; // ����Ƶ���ò����ſ������û�������д��default==80��

			//
			TraceVectorMap m_traces; // �Ӳ����С�����ס���λ�ס���Ƶ

			/*!
			*
			**/
			Wavelet() : m_starttime(-50), m_phaseshift(0), m_wavelength(100), m_sampleinterval(1), m_domainfrequence(30), m_miu(1.), m_highcut(80)
			{
				TraceSampleVector empty;
				for(int i = TST_Wavelet_Amplitude; i <= TST_Wavelet_Time; i++)
				{
					m_traces.insert(std::pair<unsigned short, TraceSampleVector>(i, empty));
				}
			}
			Wavelet(const Wavelet &other)
			{
				*this = other;
			}
			const Wavelet &operator=(const Wavelet &other)
			{
				if(this != &other)
				{
					m_starttime = other.m_starttime; //�Ӳ�����ʼʱ�䣨default��-50ms��
					m_phaseshift = other.m_phaseshift; //�Ӳ������ƶ�����default��0�ȣ�
					m_wavelength = other.m_wavelength; // �Ӳ��Ĳ��γ��ȣ�default��100ms��
					m_sampleinterval = other.m_sampleinterval; //�Ӳ���ʱ����������default��1ms��
					m_domainfrequence = other.m_domainfrequence; //�Ӳ�����Ƶ��default��30Hz)

					m_traces.clear();
					m_traces = other.m_traces;
				}
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
		CSyntheticWaveletEstimator();
		~CSyntheticWaveletEstimator();

	public:
		//
		// prepare
		//
		/*!
		*
		**/
		void Log_SAC2Backus(TraceVectorMap &traces, string &unit, double High_cut);
		void Log_AC2Backus(TraceVectorMap &traces, string &unit, double High_cut);
		void Log_Density2Backus(TraceVectorMap &traces, string &unit, double High_cut);

		//
		// for log curve
		//
		/*!
		* ��������ʱ�����ʱ���ϵ,CalTimeCurve
		* input: TST_Log_Ac, TST_Log_TVD; output: TST_Log_Time_TVD
		**/
		void Log_Depth2Time(TraceVectorMap &traces, const string &unit); // 
		/*!
		* ������ʱ��ת��
		* CurveDepth2Time
		* input: TST_Log_TVD, TST_Log_Time_TVD; output: TST_Log_Time_Seismic
		**/
		void Log_Time2Seismic(TraceVectorMap &traces, const TraceSampleSpecification &sample); // 
		/*!
		* �ھ���궨������ʾ�Ĳ⾮��ֱ���
		* TVD_show_in_Seis
		* input: TST_Log_Time_TVD, TST_Log_TVD. output: TST_Log_TVD_Seismic
		**/
		void Log_Depth2Seismic(TraceVectorMap &traces, const TraceSampleSpecification &sample); //

		//
		// for seismic
		//
		/*!
		* ���������ϵ��, CalZeroOffRc
		* input: TST_Log_Ac, TST_Log_Density; output: TST_Seismic_Post_Reflection, TST_Seismic_P_Impedence
		**/
		void Seismic_Trace2Reflection(TraceVectorMap &traces, const string &unit); // 
		/*!
		* �����ǰ�Ƕȷ���ϵ��, CalAVARc
		* input: TST_Log_Ac, TST_Log_Density, TST_Log_S_Ac; output: TST_Seismic_VP_Reflection
		**/
		void Seismic_Trace2Reflection(TraceVectorMap &traces, const string &unit, double angle); // prev
		/*!
		* �������ϳɵ����¼ CalZeroOffSyn
		* input: TST_Log_Time_Seismic, TST_Log_Time_TVD; output: TST_Seismic_Synthetic_Trace
		**/
		void Seismic_Reflection2Synthetic(TraceVectorMap &traces, Wavelet &wav); // post
		void Seismic_Reflection2Synthetic(TraceAngleMap &reflections, Wavelet &wav); // prev

		/*!
		* ���㾮�Ե��ͺϳɵ����¼�Ļ��������,CalSeisSynCrosCor
		* input: 
		**/
		void Seismic_Trace2Synthetic(TraceVectorMap &traces, const TraceVectorVector &seis, TraceVectorVector &correlations, const TraceSampleSpecification &sample, const Wavelet &wav); // CalSeisSynCrosCor

		//
		// for wavelet
		//
		/*!
		* ���ɲ��༭�׿��Ӳ� , EditRickerWavlet
		* 
		**/
		void Wavelet_Ricker(Wavelet &wav);
		/*!
		* �Ӳ�������ScalingWavelet
		* input: TST_Seismic_Synthetic_Trace, TST_Seismic_Trace; output: TST_Seismic_Synthetic_Trace
		**/
		void Wavelet_Scaling(TraceVectorMap &traces, Wavelet &wav, TraceSampleSpecification &sample, double &scale);
		/*!
		* �Ա��Ӳ��͵�����������,CompSeisWavSpe
		* 
		**/
		void Wavelet_Spectrum(TraceVectorMap &traces, TraceVectorVector &seis, Wavelet &wav, TraceSampleSpecification &sample);

		/*!
		*
		**/
		void Wavelet_Extraction(TraceVectorMap &traces, Wavelet &wav, TraceSampleSpecification &seissample, WellSampleSpecification &wellsample);

		/*!
		*
		**/
		void Wavelet_Averaging(std::vector<Wavelet *> &inputs, Wavelet &output);


		//
		// for estimator
		//
		/*!
		* ��ֱ�ƶ�ʱ���ϵ, ShiftTimeDepth
		* intput: TST_Log_Time_TVD
		**/
		void Estimator_Shift(TraceVectorMap &traces, double fromtime, double totime);
		/*!
		* ����ѹ��ʱ���ϵ, Stretch_SqueezeTimeDepth
		* intput: TST_Log_Time_TVD
		**/
		void Estimator_Stretch_Squeeze(TraceVectorMap &traces, std::vector<CGeoPoint<double> > &befores, std::vector<CGeoPoint<double> > &corrects);

		//
		//
		//
		struct  COMPLEX
		{
			double real;
			double imag;

			COMPLEX() : real(0.), imag(0.)
			{
			}
		};
		static void FFT(COMPLEX *x, int m);
		static void FFT(COMPLEX *x, int m, COMPLEX*w);
		static void IFFT(COMPLEX *x, int m);

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoZoeppritz(TraceVectorMap &traces, double angle);
		void DoConvolution(TraceSampleVector &v1, TraceSampleVector &v2, TraceSampleVector &v3);
		double DoGetUnitScale(const string &unit);
		void DoLinearInterpolation(TraceSampleVector &x, TraceSampleVector &y, TraceSampleVector &t, TraceSampleVector &z);
		double DoCrossCorrelation(const TraceSampleVector &x, const TraceSampleVector &y);
		void DoPopSort(TraceSampleVector &x, TraceSampleVector &y);
		void DoCorrelationCorrelation(TraceSampleVector &x, TraceSampleVector &y, TraceSampleVector &z);
		void DoPapoulisTaper(int samplenumber, TraceSampleVector &taper);
		void DoCalcAmplitudeSpectrum(COMPLEX *Spe, int pad_num, TraceSampleVector &Amp_Spe);
		void Cal_cord_for_zero_ph(int wav_length, int wav_samp,int pad_num,double samp_int, TraceSampleVector &cord_zero_ph);
		void GeneRcMatr(const TraceSampleVector &R, int M, double **Mr);
		void Circle_Cord( double start_time_wav, int wav_samp, double samp_int, TraceSampleVector &cord);
		void Cal_Phase_Angle(COMPLEX *spe, int pad_num, TraceSampleVector &phase_angle);
		void Highcut_Win(double high_pass, double high_cut, double DF, int pad_num, TraceSampleVector &w);
		double Seismic_Synthetic_cor(TraceVectorMap &traces, TraceSampleSpecification &seissample);

	};
}
#endif