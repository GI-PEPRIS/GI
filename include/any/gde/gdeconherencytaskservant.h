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
#ifndef __ANYGDE_RCF_TASK_CONHERENCY_SERVANT_H__
#define __ANYGDE_RCF_TASK_CONHERENCY_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"

#define SMALLVAL	1e-20
//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeConherencyTask, "I_GdeConherencyTask")
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
	RCF_END(I_GdeConherencyTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeConherencyTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeConherencyTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeConherencyTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeConherencyTaskServant *m_parent;
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
		CGdeConherencyTaskServant();
		~CGdeConherencyTaskServant();

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
		*  Conherency
		**/
		void DoConherency(MapKey *key, MapValue *value);
		std::vector<std::string> GetVelocityFile();
		void GetVelocity(int lineno, int cdpno, std::vector<double> &vrms, std::vector<double> &vint);
	public:
		/*!
		*
		**/
		int BufferCost(int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency);

		void DividFrequency(float *pInData, 
			int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency, 
			int nLevel, 
			float *pOutData, 
			float *pBuffer);
		void DividFrequencyRGB(float *pInData,  
			int nSamples,  
			int nSampleInterval, //us
			int nTop,
			int nBottom, 
			int nMaxFrequency, 
			int nLevel, 
			float *pOutData, 
			float *pBuffer);
		void RemoveNoise(float *pInData, 
			int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency, 
			int nLevel, 
			float *pOutData, 
			float *pBuffer);

		void DivFrequencyRemoveNoise(float *pInData, 
			int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency, 
			int nLevel, 
			int nRemoveNoise, 
			float *pOutData, 
			float *pBuffer);

		void getRSIParameter(int nMainFreq, 
			int nSamples, 
			int nSampInterval, 
			int& nMaxFreq, 
			int& nLevel, 
			int& nBufferSize);

		void RemoveNoise(float **pInData, 
			int nSamples, 
			int nSampleInterval, //ms
			int nTrace,
			float fScal, 
			float fLevel,
			float *pOutData);   //--- no use ---

		void kkwave(double *pr,double *pi,int n,int k,double *fr,double *fi,int l,int il);

		/*!
		*
		**/
		void correlation31(float***fAmpute,float*fCoeff,float*fDip,float*fAzimuth,int nX,int nY,int nX1,int nY1,
			int nTime,int nWin,int nBool,float dt,float dx,float dy,float*fVel);
		void correlation3(float***fAmpute,float*fCoeff,float*fDipx,float*fDipY,int nX,int nY,int nX1,int nY1,
			int nTime,int nWin);
		float MaxEigVal(float**C, int Row, int nIters, float tr);
		bool isValidTrace(float *pTrace, int nLen);
		float LinearInsert(float x1,float y1,float x2,float y2,float x);
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	public:
		// correlation
		float **m_C;
		int m_C_count;
		float **m_D;
		int m_D_count;
		int m_D_sub_count;
		float *m_fDipX;
		int m_fDipX_sub_count;
		float *m_fDipY;
		int m_fDipY_sub_count;
		// DoHandle
		float ***m_pSum;
		int m_pSum_sub_count;
		float ***m_pRSI;
		int m_pRSI_sub_count;
		float *m_pDip;
		int m_pDip_sub_count;
		float *m_pAzi;
		int m_pAzi_sub_count;
		float *m_pBuffer;
		int m_pBuffer_sub_count;
		float **m_fCoeff;
		float *m_pVelostar;
		float *m_pCoh;
		int m_pCoh_sub_count;
		// DividFrequency
		double *m_cof;
		int m_cof_sub_count;
		double *m_wave;
		int m_wave_sub_count;
	};
}

#endif
