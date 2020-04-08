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
#ifndef __ANYGDE_RCF_TASK_BRICK_SERVANT_H__
#define __ANYGDE_RCF_TASK_BRICK_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"
#include "syntheticwaveletestimator.h"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeBrickTask, "I_GdeBrickTask")
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
	RCF_END(I_GdeBrickTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeBrickTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeBrickTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeBrickTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeBrickTaskServant *m_parent;
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
		CGdeBrickTaskServant();
		~CGdeBrickTaskServant();

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
		*  Brick
		**/
		void DoBrick(MapKey *key, MapValue *value);
	public:
		void Pre_cond_BI(double start_time_near,double start_time_mid,double start_time_far,int samp_num_near,int samp_num_mid,int samp_num_far,double samp_int_near,double samp_int_mid,double samp_int_far,\
			double start_time_Imp,double start_time_Jmp,double start_time_dens,int samp_num_Imp,int samp_num_Jmp,int samp_num_dens,double samp_int_Imp,double samp_int_Jmp,double samp_int_dens,\
			double &start_time_mod,int &samp_num_mod,double &samp_int_mod);
		void BI_Inv_Trace(std::vector<double> &Rc_near,std::vector<double> &Rc_mid,std::vector<double> &Rc_far,double start_time_near,double start_time_mid,double start_time_far,\
			std::vector<double> &Imp_mod,std::vector<double> &Jmp_mod,std::vector<double> &dens_mod,double start_time_Imp,double start_time_Jmp,double start_time_dens,\
			double start_time_mod,int samp_num_mod,double samp_int_mod,double sigma2,double sigma3,double YM_min,double YM_max,double PR_min,double PR_max,\
			int N_Iter,double lowpass,double lowcut,double ag_near,double ag_mid,double ag_far,double Top_time,double Bot_time,\
			std::vector<double> &BI_output,std::vector<double> &vp_output,std::vector<double> &vs_output);
		void GetTracefromRc(std::vector<double> &Rc,double start_time,double samp_int,double Top_time,double Bot_time,std::vector<double> &Rc_Inv);
		void GetTracefromModel(const std::vector<double> &Model, std::vector<double> &Model_Inv, double start_time,double Top_time,double Bot_time,double samp_int);
		void GLIForBI_PetroV(std::vector<double> &Imp,std::vector<double> &Jmp,std::vector<double> &dens,double ag_near,double ag_mid,double ag_far,\
			std::vector<double> &Rc_near,std::vector<double> &Rc_mid,std::vector<double> &Rc_far,double sigma2,double sigma3,int N_Iter,double samp_int_mod,\
			double YM_min,double YM_max,double PR_min,double PR_max,double lowpass,double lowcut,std::vector<double> &BI_Inv,std::vector<double> &vp_Inv,std::vector<double> &vs_Inv);
		void Inv_Output_PetroV(double start_time, double samp_num, double samp_int, double top_time, double bot_time, const std::vector<double> &para_Inv, std::vector<double> &para_output);
		void Cal_BI_from_VpVsDens(std::vector<double> &vp,std::vector<double> &vs,std::vector<double> &dens,double YM_min,double YM_max,double PR_min,double PR_max,std::vector<double> &BI);
		void LowPasFilterPetroV(const std::vector<double> &m, int dt, double lowpass, double lowcut, std::vector<double> &mp);
		void HamingWinPetroV(int pad_numb, double lowpass, double lowcut, int dt, std::vector<double> &winlow, int &f1, int &f2);
		void DifMat2(int N,std::vector<std::vector<double> > &D);
		void SoftConstrMatrEI(int N,double lowpass,double lowcut,double dt,int N_pad,std::vector<std::vector<double> >&Gs);
		void LowPassFilterMatrPetroV_New(double **Glow_cut, int N,double lowpass,double lowcut,int dt);
		void Zoe_for_BIVpVs(double BI1,double BI2,double Vp1,double Vp2,double Vs1,double Vs2,std::vector<double> &sina,std::vector<double> &sina2,std::vector<double> &cosa,double YM_min,double YM_max,double PR_min,double PR_max,std::vector<double> &Rpp);
		void Cal_Dens_from_BIVpVs( double vp,double vs,double BI,double YM_min,double YM_max,double PR_min,double PR_max,double &dens );
		void Cal_Dul_Diag_Mat(std::vector<double> &diag_A, std::vector<double> &diag_B,std::vector<std::vector<double> > &C);
		void BuildWeightForTriCau2(std::vector<std::vector<double> >&D,std::vector<double>&m,double **fai,std::vector<std::vector<double> >&Q);
		void Conv_Matr( double **Filter_Mat, std::vector<double> &Filter,int pad_numb, int N );
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	public:
		std::vector<double> m_Seis_1;//小角度反射系数
		std::vector<double> m_Seis_2;//中角度反射系数
		std::vector<double> m_Seis_3;//大角度反射系数
		std::vector<double> m_Seis_4;//P波阻抗低频模型
		std::vector<double> m_Seis_5;//S波阻抗低频模型
		std::vector<double> m_Seis_6;//密度低频模型
		std::vector<double> m_Seis_out_1;//脆性指数的反演结果
		std::vector<double> m_Seis_out_2;//P波速度的反演结果
		std::vector<double> m_Seis_out_3;//S波速度的反演结果
	public:
		// for malloc reuse
		std::vector<double> m_LowPasFilterPetroV_winlow;
		CSyntheticWaveletEstimator::COMPLEX *m_LowPasFilterPetroV_mmsp;
		int m_LowPasFilterPetroV_mmsp_sub_count;
		std::vector<double> m_LowPasFilterPetroV_mm;
		CSyntheticWaveletEstimator::COMPLEX *m_LowPassFilterMatrPetroV_New_winlow_complex;
		int m_LowPassFilterMatrPetroV_New_winlow_complex_sub_count;
		double **m_LowPassFilterMatrPetroV_Glow;
		int m_LowPassFilterMatrPetroV_Glow_count;
		int m_LowPassFilterMatrPetroV_Glow_sub_count;
		double **m_SoftConstrMatrPetroV_Glow_cut;
		int m_SoftConstrMatrPetroV_Glow_cut_count;
	};
}

#endif
