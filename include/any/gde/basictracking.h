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
#ifndef __ANYGDE_BASIC_TRACKING_H__
#define __ANYGDE_BASIC_TRACKING_H__

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
	class ANYGDE_CLASS CBasicTracking : public CAnyGdeDataHandler
	{
	public:
		struct BasicTrackingParameter
		{
			int MaxIter;
			double FeaTol;
			double OptTol;
			double StepTol;
			double x0min;
			double z0min;
			double mu0;
			double gamma;
			double delta;

			int Maxitns;
			int Minitns;
			double tol;
			double cont_steps;
			double mu;
			double beta;
			
			/*!
			*
			**/
			BasicTrackingParameter() : MaxIter(100), FeaTol(0.000000001), OptTol(0.000000001), StepTol(0.99), x0min(0.1), z0min(1), mu0(1000), gamma(0.0001), delta(1), \
				Maxitns(50000), Minitns(500), tol(0.01), cont_steps(1), mu(0.1), beta(0.5)
			{
			}

			/*!
			*
			**/
			BasicTrackingParameter(const BasicTrackingParameter &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const BasicTrackingParameter &operator=(const BasicTrackingParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}
				MaxIter = other.MaxIter;
				FeaTol = other.FeaTol;
				OptTol = other.OptTol;
				StepTol = other.StepTol;
				x0min = other.x0min;
				z0min = other.z0min;
				mu0 = other.mu0;
				gamma = other.gamma;
				delta = other.delta;
				Maxitns = other.Maxitns;
				Minitns = other.Minitns;
				tol = other.tol;
				cont_steps = other.cont_steps;
				mu = other.mu;
				beta = other.beta;
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
		CBasicTracking();
		~CBasicTracking();

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
		void PetroVBPI(std::vector<double> &Seis_near, double start_time_near, double samp_num_near, double samp_int_near, \
			std::vector<double> &Imp_mod, double start_time_Imp, double samp_num_Imp, double samp_int_Imp, \
			std::vector<double> &wavelet_near, double start_time_wav_near, double samp_wav_near, double samp_int_wav_near, \
			int method, double sigma2, double sigma3, BasicTrackingParameter &option, int D_sample, \
			double lowpass, double lowcut, double Top_time, double Bot_time, int N_pad, std::vector<double> &Imp_output, std::vector<double> &Rc_output);
		void GetTracefromSeis(std::vector<double> &Seis, std::vector<double> &Seis_Inv, double start_time, double samp_int, double samp_num, double start_time_wav, double wav_samp,double Top_time,double Bot_time);
		void Extend_seis(std::vector<double> &Seis, std::vector<double> &Seis_pad, int N_pad);
		void GetTracefromModel(const std::vector<double> &Model, std::vector<double> &Model_Inv, double start_time,double Top_time,double Bot_time,double samp_int);
		void Wav_Seis_Uniformization(const std::vector<double> &wavelet, std::vector<double> &Seis_Inv, std::vector<double> &wavelet_uni);
		void GeneralizeWAVMAT3(const std::vector<double> &wavelet, int samp_wav, int N, std::vector<std::vector<double> > &W);
		void Inv_Output_PetroV_BP(double start_time, double samp_num, double samp_int, double top_time, double bot_time, const std::vector<double> &para_Inv, std::vector<double> &para_output, std::vector<double> &para_output2);
public:
		void BP_Inv(std::vector<double> &d, std::vector<std::vector<double> > &W, std::vector<double> &Imp_Mod, int D_sample, double miu, double lamda, double lowpass, double lowcut, \
		double samp_int, int method_solve, BasicTrackingParameter &option, int N_pad, std::vector<double> &Imp_Inv);
		void HamingWinPetroV(int pad_numb, double lowpass, double lowcut, int dt, std::vector<double> &winlow, int &f1, int &f2);
		void Conv_Matr( double **Filter_Mat, std::vector<double> &Filter,int pad_numb, int N );
		void LowPassFilterMatrPetroV_New(double **Glow_cut, int N,double lowpass,double lowcut,int dt);
		void IntegalMatrPetroV_R(double **AA, double **A, int M, int N);
		void IntegalMatrPetroV_L(double **AA, double **A, int M, int N);
		void Rc_Decoupling_Mat(int N_sample,int D_sample,std::vector<std::vector<double> > &DD );
		void SoftConstrMatrForPost(int N,double lowpass,double lowcut,double dt,int N_pad,std::vector<std::vector<double> > &Gs);
		void LowPasFilterPetroV(const std::vector<double> &m, int dt, double lowpass, double lowcut, std::vector<double> &mp);
public:
	void Primal_Dual_Log_Barrier_LP2( std::vector<std::vector<double> > &A,std::vector<double> &b,std::vector<double> &c,std::vector<double> &x0,std::vector<double> &y0,std::vector<double> &z0,BasicTrackingParameter &options, \
		std::vector<double> &x, std::vector<double> &y, std::vector<double> &z);
	void Cal_PDres1(std::vector<std::vector<double> > &A,std::vector<double> &b,std::vector<double> &c,double delta,double gamma,std::vector<double> &x,std::vector<double> &y,std::vector<double> &x1,std::vector<double> &z1,\
		std::vector<double> &r1,std::vector<double> &r2,std::vector<double> &rL,double &Pinf,double &Dinf );
	void Cal_PDres2( std::vector<double> &x1,std::vector<double> &z1,double mu,std::vector<double> &cL,double &Cinf0,double &Cinf,double &center);
	void GPSRforBP( std::vector<std::vector<double> > &A,std::vector<double> &b,double lamda_start,BasicTrackingParameter &option,std::vector<double> &x );
	void Cut_seis(std::vector<double> &Seis_pad, std::vector<double> &Seis, int N_pad);
	void findstep( std::vector<double> &x,std::vector<double> &dx,double &step );
	double norm(std::vector<double> &f);
	void Solve_Hermitian(std::vector<std::vector<double> > &A, std::vector<double> &b, int N, std::vector<double> &x);
	void Cholesky_Decomposition(std::vector<std::vector<double> > &A, int N, std::vector<std::vector<double> > &L);
	void Solve_Up_Trianglar(std::vector<std::vector<double> > &A, std::vector<double> &b, int N, std::vector<double> &x);
	void Solve_Down_Trianglar(std::vector<std::vector<double> > &A, std::vector<double> &b, int N, std::vector<double> &x);
public:
		int m_nInlineFrom;
		int m_nInlineTo;
		int m_nXlineFrom;
		int m_nXlineTo;
		std::vector<double> m_Seis_near;		//����ĵ�������
		double m_start_time_near;				//����������ʼʱ��
		int m_samp_num_near;					//�������ݲ�������
		double m_samp_int_near;					//�������ݲ������
		std::vector<double> m_Imp_mod;			//����Ĳ��迹��Ƶģ��
		double m_start_time_Imp;				//���迹��Ƶģ����ʼʱ��
		int m_samp_num_Imp;						//���迹��Ƶģ�Ͳ�������
		double m_samp_int_Imp;					//���迹��Ƶģ�Ͳ������
		std::vector<double> m_wavelet_near;		//������Ӳ����Ӳ��־û��ļ��л�ȡ��
		double m_start_time_wav_near;			//�Ӳ���ʼʱ�䣨�Ӳ��־û��ļ��л�ȡ��
		int m_samp_wav_near;					//�Ӳ������������Ӳ��־û��ļ��л�ȡ��
		double m_samp_int_wav_near;				//�Ӳ�����������Ӳ��־û��ļ��л�ȡ��
		int m_method;							//��׷�ٷֽⷽ��
		double m_sigma2;						//ϡ��Լ��
		double m_sigma3;						//��Ƶ��Լ��
		BasicTrackingParameter m_option;		//ODLP��GPSR�߼����ò���
		int m_D_sample;							//���������
		double m_lowpass;						//��ͨƵ
		double m_lowcut;						//�ͽ�Ƶ
		int m_N_pad;							//�߽�����
		bool m_setzero;
		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
		std::vector<double> m_Imp_output;		//���迹�Ľ�����հ״���ֵ�Ѿ���NaN
		std::vector<double> m_Rc_output;		//����ϵ���Ľ�����հ״���ֵ�Ѿ���NaN
	};
}

#endif
