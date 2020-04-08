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
#ifndef __ANYRCF_GFS_TASK_SERVANT_H__
#define __ANYRCF_GFS_TASK_SERVANT_H__

#include"anyrcf.h"
#include "anyservicebasic.h"
#include "gfschunkservant.h"

//
#include "boost\circular_buffer.hpp"

//
namespace AnyRCF
{
	// interface
	RCF_BEGIN(I_AnyGFSTask, "I_AnyGFSTask")
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
		RCF_METHOD_V1(void, SetMapTask, const JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetMapTask)
		RCF_METHOD_V1(void, MapStart, JobParameter*)
		RCF_METHOD_V2(void, Map, MapKey*, MapValue*)
		RCF_METHOD_V0(void, Map)	// in a batch
		RCF_METHOD_V1(void, MapFlush, unsigned long long)
		RCF_METHOD_V0(void, MapCombine)
		RCF_METHOD_V0(void, MapShard)	// transport chunk
		RCF_METHOD_R1(bool, IsMapDone, const string&)

		RCF_METHOD_V1(void, SetReduceTask, const JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetReduceTask)
		RCF_METHOD_V0(void, ReduceStart)
		RCF_METHOD_V2(void, Reduce, unsigned long long, ReducePairVector&)
		RCF_METHOD_V0(void, Reduce)	// in a batch
		RCF_METHOD_V0(void, ReduceFlush)
		RCF_METHOD_R1(bool, IsReduceDone, const string&)

		// output
		RCF_METHOD_V4(void, ReadData, std::string, std::vector<char>&, int, long long)
		RCF_METHOD_V5(void, WriteData, std::string, std::vector<char>&, int&, long long, int)
		RCF_METHOD_V3(void, GetDataDirectory, int, bool, string&)
		RCF_METHOD_V2(void, GetFileLength, std::string, long long&)
	RCF_END(I_AnyGFSTask)

	/*!
	*
	**/
	class ANYRCF_CLASS CGFSTaskServant : public CGFSChunkServant
	{
		// callback
		typedef RcfClient<I_AnyGFSTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CGFSTaskServant();
		~CGFSTaskServant();

	public:
		//
		// service interface
		//
		void Start(); 
		void DoScheduleEntries(std::deque<RequestEntry *> &entries);
		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);

		//
		//
		//

		//
		//
		//
		void SetMapTask(JobTaskServer &task);
		JobTaskServer GetMapTask();
		virtual int MapStart(JobParameter*){return 0;}
		virtual void Map(MapKey *key, MapValue *value){}
		int Map(); // in a batch
		virtual void MapFlush(unsigned long long chunkuuid){}
		virtual void MapCombine(){}
		virtual void MapShard(){}
		bool IsMapDone(const string& gfsfile);

		//
		//
		//
		void SetReduceTask(JobTaskServer &task);
		JobTaskServer GetReduceTask();
		virtual int ReduceStart(){return 0;};	// shuffle
		virtual void Reduce(unsigned long long chunkuuid, ReducePairVector &reducepairs){}
		int Reduce();	// in a batch
		virtual void ReduceFlush(){}
		bool IsReduceDone(const string& gfsfile);

		//
		//
		//
		void ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset);
		void WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype);
		void ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset, void* &fileHandle);
		void WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype, void* &fileHandle);
		void GetDataDirectory(int dirtype, bool inputoroutput, string &dir);
		void GetFileLength(std::string filepath, long long &filelength);
		void DoDirectSend(const string &localchunk, std::vector<string> &uploadfilepaths, std::vector<string> &uploadfiledirs, std::vector<void*> &curs, int partcount);
	protected:

		//
		//
		//
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);

		//
		//
		//
		virtual string DoGetReduceInputFile(unsigned long long chunkuuid);
		virtual string DoGetReduceOutputFile(bool isreplace = false);
		virtual string DoGetMapInputFile(unsigned long long chunkuuid, bool ispartmode = false);
		virtual string DoGetMapOutputFile(unsigned long long chunkuuid, bool isreplace = false);
		virtual void DoGetMapPairVector(unsigned long long chunkuuid, MapPairVector &pairs){};
		virtual void DoGetReducePairVector(unsigned long long chunkuuid, ReducePairVector &pairs){};

		//
		//
		//
		string DoGetMapInputDir(const string &gfsname);
		string DoGetMapOutputDir(const string &gfsname);
		string DoGetReduceInputDir(const string &gfsname);
		string DoGetReduceOutputDir(const string &gfsname);
		void DoCreateDir(string filepath);

	protected:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;

		//
		JobParameter *m_parameter;
		unsigned long long m_cur_chunkuuid;

		// tasks assigned
		JobTaskServer m_maptask;
		JobTaskServer m_reducetask;

		//
		JobTaskStatusMap m_mapperstatus;
		JobTaskStatusMap m_reducerstatus;

		//
		// buffer
		boost::circular_buffer<MapPair> m_mappercircular;
		boost::circular_buffer<ReducePair> m_reducercircular;

		//
		std::vector<ServiceHandle> m_reducehandles;
		std::vector<CAnyClientImpl*> m_reducestubs;

		//
		// chunks
		CAnyClientImpl *m_masterclient;
		std::vector<ServiceHandle> m_chunkhandles;
		std::vector<CAnyClientImpl*> m_chunkstubs;
	};
}

#endif
