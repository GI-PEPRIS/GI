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
#ifndef __ANYGDE_RCF_TASK_IRREGULAR_SERVANT_H__
#define __ANYGDE_RCF_TASK_IRREGULAR_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"
#include "syntheticwaveletestimator.h"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeIrregularTask, "I_GdeIrregularTask")
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
	RCF_END(I_GdeIrregularTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeIrregularTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeIrregularTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeIrregularTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeIrregularTaskServant *m_parent;
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
		CGdeIrregularTaskServant();
		~CGdeIrregularTaskServant();

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
		*  Irregular
		**/
		void DoIrregular(MapKey *key, MapValue *value);
	public:
		void Getting_Scaling(std::vector<double> &TVD, std::vector<double> &AC, std::vector<double> &DENS, double Undef, int N_sample_well, \
			double start_depth_seis, int N_sample_seis, double dDepth_seis, std::vector<double> &Seis, int depth_shift, double &scale_factor);
		void FC_4order_Fit_Irregular(std::vector<double> &Rpp, std::vector<double> &fai_vec, double lamda, int Niter, double &r0, double &r2, double &r4, double &Polor);
		void Cal_Error_Weight(std::vector<std::vector<double> > &G, std::vector<double> &d, std::vector<double> &x, int N, std::vector<std::vector<double> > &W);
		void Cal_Error_Weight(std::vector<std::vector<double> > &G, std::vector<double> &d, std::vector<double> &x, int N, std::vector<double> &W);
		void IntpLine(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &t, int n, int m, std::vector<double> &z);
		void Getting_Rc(std::vector<double> &TVD, std::vector<double> &AC, std::vector<double> &Dens, double dDepth_seis, double Undef, int N_sample_well, double start_depth_seis, int depth_shift,\
			int N_sample_seis, std::vector<double> &Rc, double &start_depth_log, double &end_depth_log);
		void Cal_Scaling_Window(double start_depth_seis, int N_sample_seis, double dDepth_seis, double start_depth_log, double end_depth_log, double &Top_depth, double &Bot_depth, int &wav_sample);
		void Cal_Wav_Depth_Auto(double Top_depth, double Bot_depth, std::vector<double> &Seis, double start_depth_seis, double dDepth_seis, int wav_sample, std::vector<double> &Wav_auto, std::vector<double> &seis_cal);
		void Convolution(std::vector<double> &v1, std::vector<double> &v2, std::vector<double> &v3);
		double CrossCorlation(const std::vector<double> &x, const std::vector<double> &y);
		void Cor_Cor(std::vector<double> &x,std::vector<double> &y,std::vector<double> &cor );
		void Cal_Amp_Spe( CSyntheticWaveletEstimator::COMPLEX *Spe,int pad_num,std::vector<double>&Amp_Spe );
		void Highcut_Win( double high_pass,double high_cut,double DF,int pad_num,std::vector<double>&W );
		void Cal_cord_for_zero_ph( double wav_length,int wav_samp,int pad_num,double samp_int,std::vector<int>&cord_zero_ph );
		void Papoulis_Taper( int N_sample,std::vector<double> &Taper );
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	};
}

#endif
