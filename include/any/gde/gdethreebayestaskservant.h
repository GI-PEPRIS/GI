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
#ifndef __ANYGDE_RCF_TASK_THREEBAYES_SERVANT_H__
#define __ANYGDE_RCF_TASK_THREEBAYES_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"
#include "syntheticwaveletestimator.h"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeThreeBayesTask, "I_GdeThreeBayesTask")
		//here is soft control(rcf server start/stop) hard control is implemented in console app using psService.
		RCF_METHOD_R1(bool, Init, const ServiceHandle&)
		RCF_METHOD_V1(void, GetHandle, ServiceHandle&)
		RCF_METHOD_V1(void, SetEventHandle, const ServiceHandle&)
		RCF_METHOD_V0(void, Start)
		RCF_METHOD_V2(void, Listen, const std::string&, short)
		RCF_METHOD_V3(void, Notify, short, const std::string&, long)
		RCF_METHOD_V0(void, Stop)
		RCF_METHOD_V3(void, Resume, bool, bool, bool)
		RCF_METHOD_V0(void, Suspend)
		RCF_METHOD_R0(bool, IsRunning)
		RCF_METHOD_V2(void, NetworkBandwidthAsReceiver, int, int)
		RCF_METHOD_V4(void, NetworkBandwidthAsSender, string&, int, int, int)
		RCF_METHOD_R0(SessionObjectVector, QuerySessionObject)
		RCF_METHOD_V1(void, ClearSessionObject, const string&)

		//console operate on chilren of cms
		RCF_METHOD_V2(void, RegisterChildren, int, const ServiceHandle&)
		RCF_METHOD_V2(void, RemoveChildren, string&, int)
		RCF_METHOD_V2(void, GetChildren, int, ServiceVector&)
		RCF_METHOD_V3(void, CollectHeartbeat, const ServiceHandle&, const MasterChunkServer&, const JobTaskServer&)

		//communicate  e.g. heart beats
		RCF_METHOD_V3(void, BindTo, int, string&, int)
		RCF_METHOD_V0(void, SetResponseUserData)
		RCF_METHOD_V1(void, SetClientName, const std::string&)
		RCF_METHOD_V1(void, Callback, const std::string&)
		RCF_METHOD_V1(void, OnCallback, const std::string&)

		// map reduce
		RCF_METHOD_V1(void, SetParameter, GdeJobParameter&)
		RCF_METHOD_V1(void, AddParameterSurvey, std::vector<GdePosition>&)
		RCF_METHOD_V1(void, SetEvent, const ServiceHandle&)
		RCF_METHOD_V1(void, SetMapTask, const JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetMapTask)
		RCF_METHOD_R1(int, MapStart, JobParameter*)
		RCF_METHOD_V2(void, Map, MapKey*, MapValue*)
		RCF_METHOD_R0(int, Map)	// in a batch
		RCF_METHOD_V1(void, MapFlush, unsigned long long)
		RCF_METHOD_V0(void, MapCombine)
		RCF_METHOD_V0(void, MapShard)	// transport chunk
		RCF_METHOD_R1(bool, IsMapDone, const string&)

		RCF_METHOD_V1(void, SetReduceTask, const JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetReduceTask)
		RCF_METHOD_R0(int, ReduceStart)
		RCF_METHOD_V2(void, Reduce, unsigned long long, ReducePairVector&)
		RCF_METHOD_R0(int, Reduce)	// in a batch
		RCF_METHOD_V0(void, ReduceFlush)
		RCF_METHOD_R1(bool, IsReduceDone, const string&)

		// output
		RCF_METHOD_V4(void, ReadData, std::string, std::vector<char>&, int, long long)
		RCF_METHOD_V5(void, WriteData, std::string, std::vector<char>&, int&, long long, int)
		RCF_METHOD_V3(void, GetDataDirectory, int, bool, string&)
		RCF_METHOD_V2(void, GetFileLength, std::string, long long&)
	RCF_END(I_GdeThreeBayesTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeThreeBayesTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeThreeBayesTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeThreeBayesTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeThreeBayesTaskServant *m_parent;
			MapKey *m_key;
			MapValue *m_value;
			std::vector<long> &m_sequenceOrders;
			bool &m_ispremode;
			std::vector<int> &m_cmpcounts;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CGdeThreeBayesTaskServant();
		~CGdeThreeBayesTaskServant();

	public:
		//
		// service interface
		//
		void Start(); 
		void DoScheduleEntries(std::deque<RequestEntry *> &entries);
		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);

		/*!
		*
		**/
		void SetParameter(GdeJobParameter &parameter);
		void AddParameterSurvey(std::vector<GdePosition> &survey);
		void SetEvent(const ServiceHandle &eventhandle);

		//
		//
		//
		int MapStart(JobParameter*);
		void Map(MapKey *key, MapValue *value);
		int Map();
		void MapFlush(unsigned long long chunkuuid);
		void MapCombine();
		void MapShard();

		//
		//
		//
		int ReduceStart();	// reduce shuffle
		void Reduce(unsigned long long chunkuuid, ReducePairVector &reducepairs);
		int Reduce();
		void ReduceFlush();

	protected:

		//
		//
		//
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);

		//
		//
		//
		void DoGetMapPairVector(unsigned long long chunkuuid, MapPairVector &mappairs);
		void DoGetReducePairVector(unsigned long long chunkuuid, ReducePairVector &reducepairs);
	private:

		/*!
		*  ThreeBayes
		**/
		void DoThreeBayes(MapKey *key, MapValue *value);
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
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	public:
		std::vector<double> m_Seis_near;	//输入的近道集地震数据
		std::vector<double> m_Seis_mid;	//输入的中道集地震数据
		std::vector<double> m_Seis_far;		//输入的远道集地震数据
		std::vector<double> m_Imp_mod;	//输入的P波阻抗低频模型
		std::vector<double> m_Jmp_mod;	//输入的S波阻抗低频模型
		std::vector<double> m_dens_mod;	//输入的密度低频模型
		std::vector<double> m_Imp_output;			//P波阻抗的反演结果，空白处的值已经赋NaN
		std::vector<double> m_Jmp_output;		//S波阻抗的反演结果，空白处的值已经赋NaN
		std::vector<double> m_dens_output;		//密度的反演结果，空白处的值已经赋NaN
	public:
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
