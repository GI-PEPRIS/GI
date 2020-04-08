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
			TST_Log_AC_TVD,																// 声波时差曲线 
			TST_Log_AC_TVD_Backus,												// 声波时差曲线, backus filter
			TST_Log_AC_Time,															// 声波时差曲线
			TST_Log_SAC_TVD,															// 横波声波时差曲线序列
			TST_Log_SAC_TVD_Backus,											// 横波声波时差曲线序列, backus filter
			TST_Log_SAC_Time,															// 横波声波时差曲线序列
			TST_Log_Density_TVD,														// 密度序列
			TST_Log_Density_TVD_Backus,										// 密度序列, backus filter
			TST_Log_Density_Time,														// 密度序列
			TST_Log_xshift_TVD,															// 井斜：xshift 
			TST_Log_xshift_Time,															// 井斜：xshift
			TST_Log_yshift_TVD,															// 井斜：yshift 
			TST_Log_yshift_Time,															// 井斜：yshift
			TST_Log_Time_TVD,											// 测井曲线的时间序列
			TST_Log_Time_TVD_Original,							// 拉伸压缩前对应的时间序列（深度域）？？？
			TST_Log_TVD,														// 测井的垂直深度（深度域）
			TST_Log_Depth,														// 测井的深度（深度域）
			TST_Log_Time_Seismic,									// 时间域测井曲线对应的时间序列（规则到地震采样间隔）- 时间域反射系数序列
			TST_Log_TVD_Seismic,									// 井震标定窗口显示的测井垂直深度 unused
			TST_show_Time,                                          // 井震标定窗口显示的时间 unused

			TST_Seismic_Post_Reflection,							// 叠后反射系数
			TST_Seismic_P_Impedence,						     // P波阻抗
			TST_Seismic_P_Velocity,								// P波速度序列
			TST_Seismic_S_Velocity,				  				// S波速度序列
			TST_Seismic_Trace_Amplitude,						// 叠前或叠后地震道
			TST_Seismic_Trace_Amplitude_Show,			      // 界面中显示的井旁道振幅谱
			TST_Seismic_Trace_Time,									// 地震采样时间
			TST_Seismic_Synthetic_Amplitude,					// 合成地震记录
			TST_Seismic_Synthetic_Amplitude_Original,			// scale前的合成地震记录
			TST_Seismic_Synthetic_Time,							// 合成地震记录对应的时间序列
			TST_Seismic_Synthetic_Time_Original,			// 时深关系调整前的合成地震记录对应的时间序列
			TST_Seismic_Correlation_Value,						// 互相关系数	unused,由TraceVectorVector correlations 代替
			TST_Seismic_Correlation_Time,						// 互相关系数时间序列	
			TST_Seismic_PP_Reflection,							// P波角度反射系数
			TST_Seismic_PP_Transmission,						// P波角度透射系数
			TST_Seismic_PS_Reflection,							// S波角度反射系数
			TST_Seismic_PS_Transmission,		 				// S角度透射系数

			TST_Wavelet_Trace,											// 子波数据序列 
			TST_Wavelet_Trace_Original,									// scale前的子波数据序列 
			TST_Wavelet_Amplitude,									// 子波振幅谱  
			TST_Wavelet_Amplitude_Show,							// 显示的子波振幅谱
			TST_Wavelet_Phase,											// 子波的相位谱
			TST_Wavelet_Phase_Show,								// 子波的相位谱
			TST_Wavelet_Frequency,									//  振幅谱和相对谱对应x轴频率
			TST_Wavelet_Frequency_Show,						//  界面中x轴对应的频率显示
			TST_Wavelet_Time,												// 子波时间序列

			TST_Horizon_Top,												// 对应的时间序列，分为沿层和等时两种
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
			// 地震记录的起始时间，从道头字中获取（int，单位ms）
			double m_starttime;
			// 震记录的采样点数，从道头字中获取（int）
			int m_number;
			// 地震记录的采样率，从道头字中获取（int，单位ms）
			double m_interval;
			// 子波振幅校正的计算时窗顶部，分为沿层或等时两种，当为沿层情况下，为层位与离井最近的地震道相交汇的时间（int，单位ms）
			double m_toptime;
			// 子波振幅校正的计算时窗底部，分为沿层或等时两种，当为沿层情况下，为层位与离井最精的地震道相交汇的时间（int，单位ms）
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
			double m_starttime; //子波的起始时间（default：-50ms）
			double m_phaseshift; //子波的相移度数（default：0度）
			int m_wavelength; // 子波的波形长度（default：100ms）
			double m_sampleinterval; //子波的时间采样间隔（default：1ms）
			double m_domainfrequence; //子波的主频（default：30Hz）
			int m_number; //子波样点数

			//
			double m_miu;	// 常相位子波稳定系数（该参数放开，供用户自行填写，default==1）
			double m_highcut; // 高切频（该参数放开，供用户自行填写，default==80）

			//
			TraceVectorMap m_traces; // 子波序列、振幅谱、相位谱、主频

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
					m_starttime = other.m_starttime; //子波的起始时间（default：-50ms）
					m_phaseshift = other.m_phaseshift; //子波的相移度数（default：0度）
					m_wavelength = other.m_wavelength; // 子波的波形长度（default：100ms）
					m_sampleinterval = other.m_sampleinterval; //子波的时间采样间隔（default：1ms）
					m_domainfrequence = other.m_domainfrequence; //子波的主频（default：30Hz)

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
		* 根据声波时差计算时深关系,CalTimeCurve
		* input: TST_Log_Ac, TST_Log_TVD; output: TST_Log_Time_TVD
		**/
		void Log_Depth2Time(TraceVectorMap &traces, const string &unit); // 
		/*!
		* 井曲线时深转换
		* CurveDepth2Time
		* input: TST_Log_TVD, TST_Log_Time_TVD; output: TST_Log_Time_Seismic
		**/
		void Log_Time2Seismic(TraceVectorMap &traces, const TraceSampleSpecification &sample); // 
		/*!
		* 在井震标定窗口显示的测井垂直深度
		* TVD_show_in_Seis
		* input: TST_Log_Time_TVD, TST_Log_TVD. output: TST_Log_TVD_Seismic
		**/
		void Log_Depth2Seismic(TraceVectorMap &traces, const TraceSampleSpecification &sample); //

		//
		// for seismic
		//
		/*!
		* 计算叠后反射系数, CalZeroOffRc
		* input: TST_Log_Ac, TST_Log_Density; output: TST_Seismic_Post_Reflection, TST_Seismic_P_Impedence
		**/
		void Seismic_Trace2Reflection(TraceVectorMap &traces, const string &unit); // 
		/*!
		* 计算叠前角度反射系数, CalAVARc
		* input: TST_Log_Ac, TST_Log_Density, TST_Log_S_Ac; output: TST_Seismic_VP_Reflection
		**/
		void Seismic_Trace2Reflection(TraceVectorMap &traces, const string &unit, double angle); // prev
		/*!
		* 计算叠后合成地震记录 CalZeroOffSyn
		* input: TST_Log_Time_Seismic, TST_Log_Time_TVD; output: TST_Seismic_Synthetic_Trace
		**/
		void Seismic_Reflection2Synthetic(TraceVectorMap &traces, Wavelet &wav); // post
		void Seismic_Reflection2Synthetic(TraceAngleMap &reflections, Wavelet &wav); // prev

		/*!
		* 计算井旁道和合成地震记录的互相关剖面,CalSeisSynCrosCor
		* input: 
		**/
		void Seismic_Trace2Synthetic(TraceVectorMap &traces, const TraceVectorVector &seis, TraceVectorVector &correlations, const TraceSampleSpecification &sample, const Wavelet &wav); // CalSeisSynCrosCor

		//
		// for wavelet
		//
		/*!
		* 生成并编辑雷克子波 , EditRickerWavlet
		* 
		**/
		void Wavelet_Ricker(Wavelet &wav);
		/*!
		* 子波比例，ScalingWavelet
		* input: TST_Seismic_Synthetic_Trace, TST_Seismic_Trace; output: TST_Seismic_Synthetic_Trace
		**/
		void Wavelet_Scaling(TraceVectorMap &traces, Wavelet &wav, TraceSampleSpecification &sample, double &scale);
		/*!
		* 对比子波和地震道的振幅谱,CompSeisWavSpe
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
		* 垂直移动时深关系, ShiftTimeDepth
		* intput: TST_Log_Time_TVD
		**/
		void Estimator_Shift(TraceVectorMap &traces, double fromtime, double totime);
		/*!
		* 拉伸压缩时深关系, Stretch_SqueezeTimeDepth
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