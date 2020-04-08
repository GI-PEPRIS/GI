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
#ifndef __ANYGDE_GFS_TASK_STUB_H__
#define __ANYGDE_GFS_TASK_STUB_H__

#include "anygde.h"
#include "gdetaskservant.h"

#include "any/gfs/rcfclientimpl.h"
#include "any/gfs/gfschunkstub.h"
using namespace AnyRCF;

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CGdeTaskStub : public CGFSChunkStub
	{
		typedef RcfClient<I_AnyGdeTask> ServiceStub;
		typedef boost::shared_ptr<ServiceStub> ServiceStubPtr;

	public:
		CGdeTaskStub();
		~CGdeTaskStub();

	public:
		//
		// basic
		//
		void Init(const ServiceHandle &handle);
		void GetHandle(ServiceHandle &handle);
		void Start();
		void Listen(const std::string &multicastip, int multicastport);
		void Stop();
		void Suspend();
		void Resume(bool isstopheart = false, bool isstopbroadcast = false, bool isstoprequest = false);
		bool IsRunning();
		string GetResponseUserData(const string &data);
		void RegisterChildren(int type, const ServiceHandle &handle);
		void RemoveChildren(string &ip, int port);
		void GetChildren(int type, ServiceVector &handles);
		void BindTo(int type, string &ip, int port);
		void SetClientName(const std::string &name);
		void Ping();
		void Callback(const std::string &topic);

		//
		//
		//
		/*!
		*
		**/
		void SetMapTask(JobTaskServer &task);
		void SetReduceTask(JobTaskServer &task);
		JobTaskServer GetMapTask();
		JobTaskServer GetReduceTask();
		void SetParameter(GdeJobParameter &parameter);
		void AddParameterSurvey(std::vector<GdePosition> &survey);
		void SetEvent(const ServiceHandle &eventhandle);
		void SetTaskDone(bool isdone, int type);
		bool GetTaskDone(int type);
		void SetMapTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus);
		void GetMapTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus);
		void SetReduceTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus);
		void GetReduceTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus);
		
		/*!
		*
		**/
		int MapWork();
		void MapStart(unsigned long long chunkuuid, GdeMapKeyVector &keys);
		void Map(std::vector<GdeMapPair> &pairs);
		void MapFlush(unsigned long long chunkuuid);
		void MapChunk();

		/*!
		*
		**/
		int ReduceWork();
		void ReduceStart(unsigned long long chunkuuid, GdeMapKeyVector &keys);
		void Reduce(unsigned long long chunkuuid, std::vector<GdeMapPair> &pairs);
		void ReduceFlush();
		void ReduceChunk();
		void GetReduceResult(std::vector<GdeMapPair> &pairs);
		void GetOneReduceResultPair(int pairoffset, GdeMapPair &pair, std::vector<unsigned long long> &pairsoffsets);
				
		/*!
		*
		**/
		void GetFileLength(std::string filepath, long long &filelength);
		void ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset);
		void WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype);
		void GetDir(int dirtype, bool inputoroutput, string &dir);
		void AppendChunkuuid(int towhichtask, unsigned long long chunkuuid);
		void GetChunkuuidcount(int towhichtask, int &chunkuuidcount);
		bool IsChunkuuidBelongToThis(int towhichtask, unsigned long long chunkuuid);

	public:
		ServiceStubPtr m_client;
	};

}
#endif