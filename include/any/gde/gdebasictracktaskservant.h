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
#ifndef __ANYGDE_RCF_TASK_BASICTRACK_SERVANT_H__
#define __ANYGDE_RCF_TASK_BASICTRACK_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"
#include "syntheticwaveletestimator.h"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeBasicTrackTask, "I_GdeBasicTrackTask")
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
	RCF_END(I_GdeBasicTrackTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeBasicTrackTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeBasicTrackTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeBasicTrackTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeBasicTrackTaskServant *m_parent;
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
		CGdeBasicTrackTaskServant();
		~CGdeBasicTrackTaskServant();

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
		*  BasicTrack
		**/
		void DoBasicTrack(MapKey *key, MapValue *value);
	public:
		void PetroVBPI(std::vector<double> &Seis_near, double start_time_near, double samp_num_near, double samp_int_near, \
			std::vector<double> &Imp_mod, double start_time_Imp, double samp_num_Imp, double samp_int_Imp, \
			std::vector<double> &wavelet_near, double start_time_wav_near, double samp_wav_near, double samp_int_wav_near, \
			int method, double sigma2, double sigma3, GdeBasicTrackSubParameter &option, int D_sample, \
			double lowpass, double lowcut, double Top_time, double Bot_time, int N_pad, std::vector<double> &Imp_output, std::vector<double> &Rc_output);
		void GetTracefromSeis(std::vector<double> &Seis, std::vector<double> &Seis_Inv, double start_time, double samp_int, double samp_num, double start_time_wav, double wav_samp,double Top_time,double Bot_time);
		void Extend_seis(std::vector<double> &Seis, std::vector<double> &Seis_pad, int N_pad);
		void GetTracefromModel(const std::vector<double> &Model, std::vector<double> &Model_Inv, double start_time,double Top_time,double Bot_time,double samp_int);
		void Wav_Seis_Uniformization(const std::vector<double> &wavelet, std::vector<double> &Seis_Inv, std::vector<double> &wavelet_uni);
		void GeneralizeWAVMAT3(const std::vector<double> &wavelet, int samp_wav, int N, std::vector<std::vector<double> > &W);
		void Inv_Output_PetroV_BP(double start_time, double samp_num, double samp_int, double top_time, double bot_time, const std::vector<double> &para_Inv, std::vector<double> &para_output, std::vector<double> &para_output2);
	public:
		void BP_Inv(std::vector<double> &d, std::vector<std::vector<double> > &W, std::vector<double> &Imp_Mod, int D_sample, double miu, double lamda, double lowpass, double lowcut, \
			double samp_int, int method_solve, GdeBasicTrackSubParameter &option, int N_pad, std::vector<double> &Imp_Inv);
		void HamingWinPetroV(int pad_numb, double lowpass, double lowcut, int dt, std::vector<double> &winlow, int &f1, int &f2);
		void Conv_Matr( double **Filter_Mat, std::vector<double> &Filter,int pad_numb, int N );
		void LowPassFilterMatrPetroV_New(double **Glow_cut, int N,double lowpass,double lowcut,int dt);
		void IntegalMatrPetroV_R(double **AA, double **A, int M, int N);
		void IntegalMatrPetroV_L(double **AA, double **A, int M, int N);
		void Rc_Decoupling_Mat(int N_sample,int D_sample,std::vector<std::vector<double> > &DD );
		void SoftConstrMatrForPost(int N,double lowpass,double lowcut,double dt,int N_pad,std::vector<std::vector<double> > &Gs);
		void LowPasFilterPetroV(const std::vector<double> &m, int dt, double lowpass, double lowcut, std::vector<double> &mp);
	public:
		void Primal_Dual_Log_Barrier_LP2( std::vector<std::vector<double> > &A,std::vector<double> &b,std::vector<double> &c,std::vector<double> &x0,std::vector<double> &y0,std::vector<double> &z0,GdeBasicTrackSubParameter &options, \
			std::vector<double> &x, std::vector<double> &y, std::vector<double> &z);
		void Cal_PDres1(std::vector<std::vector<double> > &A,std::vector<double> &b,std::vector<double> &c,double delta,double gamma,std::vector<double> &x,std::vector<double> &y,std::vector<double> &x1,std::vector<double> &z1,\
			std::vector<double> &r1,std::vector<double> &r2,std::vector<double> &rL,double &Pinf,double &Dinf );
		void Cal_PDres2( std::vector<double> &x1,std::vector<double> &z1,double mu,std::vector<double> &cL,double &Cinf0,double &Cinf,double &center);
		void GPSRforBP( std::vector<std::vector<double> > &A,std::vector<double> &b,double lamda_start,GdeBasicTrackSubParameter &option,std::vector<double> &x );
		void Cut_seis(std::vector<double> &Seis_pad, std::vector<double> &Seis, int N_pad);
		void findstep( std::vector<double> &x,std::vector<double> &dx,double &step );
		double norm(std::vector<double> &f);
		void Solve_Hermitian(std::vector<std::vector<double> > &A, std::vector<double> &b, int N, std::vector<double> &x);
		void Cholesky_Decomposition(std::vector<std::vector<double> > &A, int N, std::vector<std::vector<double> > &L);
		void Solve_Up_Trianglar(std::vector<std::vector<double> > &A, std::vector<double> &b, int N, std::vector<double> &x);
		void Solve_Down_Trianglar(std::vector<std::vector<double> > &A, std::vector<double> &b, int N, std::vector<double> &x);
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	public:
		std::vector<double> m_Seis_near;		//输入的地震数据
		std::vector<double> m_Imp_mod;			//输入的波阻抗低频模型
		std::vector<double> m_Imp_output;		//波阻抗的结果，空白处的值已经赋NaN
		std::vector<double> m_Rc_output;		//反射系数的结果，空白处的值已经赋NaN
	};
}

#endif
