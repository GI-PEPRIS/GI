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
#ifndef __ANYGDE_RCF_TASK_ROCKPHYSICS_SERVANT_H__
#define __ANYGDE_RCF_TASK_ROCKPHYSICS_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"
#include "syntheticwaveletestimator.h"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeRockPhysicsTask, "I_GdeRockPhysicsTask")
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
	RCF_END(I_GdeRockPhysicsTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeRockPhysicsTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeRockPhysicsTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeRockPhysicsTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeRockPhysicsTaskServant *m_parent;
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
		CGdeRockPhysicsTaskServant();
		~CGdeRockPhysicsTaskServant();

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
		*  RockPhysics
		**/
		void DoRockPhysics(MapKey *key, MapValue *value);
	public:
		void GetTracefromModel(const std::vector<double> &Model, std::vector<double> &Model_Inv, double start_time,double Top_time,double Bot_time,double samp_int);
		void LowPasFilterPetroV(const std::vector<double> &m, int dt, double lowpass, double lowcut, std::vector<double> &mp);
		void HamingWinPetroV(int pad_numb, double lowpass, double lowcut, int dt, std::vector<double> &winlow, int &f1, int &f2);
		void Estimate_Coeffient_Regression_3_Term(std::vector<double> &TOC,std::vector<double> &Porosity_Total,std::vector<double> &V_Bri,std::vector<double> &vp,std::vector<double> &vs,std::vector<double> &dens,\
			double Undef, int N_sample, int V_choice, std::vector<std::vector<double> > &G_Mat,std::vector<double> &Coef_Clay);
		void Getting_fai_from_las_3_Term(std::vector<double> &V_Bri,std::vector<double> &Toc,std::vector<double> &Porosity_Total,double undef,std::vector<std::vector<double> > &fai);
		void TOC_INV_Trace_3_Term(double start_time_Bri,double start_time_TOC,double start_time_Por,double samp_num_Bri,double samp_num_TOC,double samp_num_Por,double samp_int_Bri,double samp_int_TOC,double samp_int_Por,\
			double start_time_Imp,double start_time_Jmp,double start_time_dens,double samp_num_Imp,double samp_num_Jmp,double samp_num_dens,double samp_int_Imp,double samp_int_Jmp,double samp_int_dens,\
			double Top_time,double Bot_time,std::vector<double> &Imp,std::vector<double> &Jmp,std::vector<double> &dens,std::vector<double> &Bri_Mod,std::vector<double> &TOC_Mod,std::vector<double> &Por_Mod,\
			std::vector<std::vector<double> > &G_Mat,std::vector<std::vector<double> > &Cov,double lamda,double lowpass,double lowcut,std::vector<double> &Coef_Clay,int V_choice, \
			std::vector<double> &Bri_Inv,std::vector<double> &TOC_Inv,std::vector<double> &Por_Inv,double &start_time_mod,int &samp_num_mod,double &samp_int_mod);
		void Pre_cond_TOC_3_Term(double start_time_Bri,double start_time_TOC,double start_time_Por,int samp_num_Bri,int samp_num_TOC,int samp_num_Por,double samp_int_Bri,double samp_int_TOC,double samp_int_Por,\
			double start_time_Imp,double start_time_Jmp,double start_time_dens,int samp_num_Imp,int samp_num_Jmp,int samp_num_dens,double samp_int_Imp,double samp_int_Jmp,double samp_int_dens,\
			double &Top_time,double &Bot_time,double &start_time_mod,int &samp_num_mod,double &samp_int_mod);
		void Property_Inv_Regression_3_Term(std::vector<std::vector<double> > &G_Mat,std::vector<double> &mp,std::vector<std::vector<double> > &Cov,double lamda, \
			double Imp_sat,double Jmp_sat,double dens_sat,std::vector<double> &Coef_Clay,int V_choice, std::vector<double> &x);
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	public:
		std::vector<double> m_Seis_1;//P波阻抗
		std::vector<double> m_Seis_2;//S波阻抗
		std::vector<double> m_Seis_3;//密度
		std::vector<double> m_Seis_4;//脆性矿物体积分数
		std::vector<double> m_Seis_5;//干酪根体积分数
		std::vector<double> m_Seis_6;//总孔隙度
		std::vector<double> m_Seis_out_1;//脆性矿物体积分数输出
		std::vector<double> m_Seis_out_2;//干酪根体积分数输出
		std::vector<double> m_Seis_out_3;//总孔隙度输出
	public:
		// for malloc reuse
		std::vector<double> m_LowPasFilterPetroV_winlow;
		CSyntheticWaveletEstimator::COMPLEX *m_LowPasFilterPetroV_mmsp;
		int m_LowPasFilterPetroV_mmsp_sub_count;
		std::vector<double> m_LowPasFilterPetroV_mm;
	};
}

#endif
