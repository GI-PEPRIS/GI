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
#ifndef __ANYRCF_GFS_JOB_SERVANT_H__
#define __ANYRCF_GFS_JOB_SERVANT_H__

#include"anyrcf.h"
#include "rcfserviceimpl.h"
#include "anyclientimpl.h"

//
namespace AnyRCF
{
	// interface
	RCF_BEGIN(I_AnyGFSJob, "I_AnyGFSJob")
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
		// map reduce
		RCF_METHOD_V1(void, SetJobSpecification, const JobSpecification&)
		RCF_METHOD_V5(void, InitDB, short, const std::string&, const std::string&, const std::string&, const std::string&)
		RCF_METHOD_V1(void, SetMapTask, const JobTaskServer&)
		RCF_METHOD_V1(void, SetReduceTask, const JobTaskServer&)
		//communicate e.g. heart beats
		RCF_METHOD_V3(void, BindTo, int, string&, int)
		RCF_METHOD_V0(void, SetResponseUserData)
		RCF_METHOD_V1(void, SetClientName, const std::string&)
		RCF_METHOD_V1(void, Callback, const std::string&)
		RCF_METHOD_V1(void, OnCallback, const std::string&)
		// job schedule
		RCF_METHOD_V1(void, Job4Mapper, JobTaskServerVector&)
		RCF_METHOD_V1(void, Job4Reducer, JobTaskServerVector&)
		RCF_METHOD_R0(unsigned long long, FirstSplit)
		RCF_METHOD_R0(unsigned long long, NextSplit)
		// status
		RCF_METHOD_V2(void, SetJobStatus, const std::string&, JobStatus&)
		RCF_METHOD_V2(void, GetJobStatus, const std::string&, JobStatus&)

		// mapreduce
		RCF_END(I_AnyGFSJob)

	/*!
	*
	**/
	class ANYRCF_CLASS CGFSJobServant : public CRCFServiceImpl
	{
		// callback
		typedef RcfClient<I_AnyGFSJob> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CGFSJobServant();
		~CGFSJobServant();

	public:
		//
		// service interface
		//
		/*!
		*
		**/
		void Start(); 
		void DoScheduleEntries(std::deque<RequestEntry *> &entries);

		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);
		void DoCollectServerStatus(ServiceHandle &handle, MasterChunkServer &chunkstatus, JobTaskServer &taskstatus);

		/*!
		* aync 
		**/
		void SetJobSpecification(const JobSpecification &specification);
		void Job4Mapper(JobTaskServerVector &mapreducers);
		void Job4Reducer(JobTaskServerVector &mapreducers);
		unsigned long long FirstSplit();
		unsigned long long NextSplit();


		//
		//
		//
		void SetJobStatus(const std::string& gfsname, JobStatus &jobstatus);
		void GetJobStatus(const std::string& gfsname, JobStatus &jobstatus);

	private:
		//
		//
		//
		/*!
		*
		**/
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);
		void GetMasterClient();

		void DoResponseToHeartbeat();
		void DoResponseToMapperDone();
		void DoResponseToReducerDone();
		bool IsAllTaskDone(std::vector<ServiceHandle> &servants, short childrentype);

	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;

		// job specification
		JobSpecification m_specification;

		// chunk files
		RCF::Mutex m_chunkmutex;
		std::vector<unsigned long long>  m_chunkuuids;
		int m_chunkcursor;

		// master stub
		CAnyClientImpl *m_masterclient;

		//
		RCF::Mutex m_jobstatusmutex;
		JobStatusMap m_jobstatus;
	};
}

#endif
