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
#ifndef __ANYRCF_GDE_TASK_MAP_REDUCE_STUB_H__
#define __ANYRCF_GDE_TASK_MAP_REDUCE_STUB_H__

#define COMPILE_Slice
//#define COMPILE_Triangulate
#define COMPILE_Instant
//#define COMPILE_DipAzimuth
//#define COMPILE_AlphaFilter
//#define COMPILE_Irregular
//#define COMPILE_Ellipse
//#define COMPILE_ThreeBayes
#define COMPILE_BasicTrack
//#define COMPILE_RockPhysics
//#define COMPILE_Brick
//#define COMPILE_Conherency

//
#include "anygde.h"
#ifdef COMPILE_Slice
#include "gdeslicetaskservant.h"
#endif
#ifdef COMPILE_Triangulate
#include "gdetrianglefiltertaskservant.h"
#endif
#ifdef COMPILE_Instant
#include "gdeinstantattributetaskservant.h"
#endif
#ifdef COMPILE_DipAzimuth
#include "gdedipazimuthtaskservant.h"
#endif
#ifdef COMPILE_AlphaFilter
#include "gdealphafiltertaskservant.h"
#endif
#ifdef COMPILE_Irregular
#include "gdeirregulartaskservant.h"
#endif
#ifdef COMPILE_Ellipse
#include "gdeellipsetaskservant.h"
#endif
#ifdef COMPILE_ThreeBayes
#include "gdethreebayestaskservant.h"
#endif
#ifdef COMPILE_BasicTrack
#include "gdebasictracktaskservant.h"
#endif
#ifdef COMPILE_RockPhysics
#include "gderockphysicstaskservant.h"
#endif
#ifdef COMPILE_Brick
#include "gdebricktaskservant.h"
#endif
#ifdef COMPILE_Conherency
#include "gdeconherencytaskservant.h"
#endif

//
#include "any/gfs/servicestub.h"
using namespace AnyRCF;

//
namespace AnyGDE
{
	template<typename GdeInterface>
	class CGdeTaskCommonStub : public CRCFClientImpl
	{
		typedef RcfClient<GdeInterface> ServiceStub;
		typedef boost::shared_ptr<ServiceStub> ServiceStubPtr;

	public:
		CGdeTaskCommonStub()
		{
		}
		~CGdeTaskCommonStub()
		{
			if(m_client)
				m_client.reset();
			m_client = 0;
		}
	public:
		//
		//
		//
		/*!
		*
		**/
		void Init(const ServiceHandle &handle)
		{
			try
			{
				m_handle = handle;
				RCF::TcpEndpoint point(m_handle.m_ip,m_handle.m_port);				

				ServiceStubPtr clientPtr(new ServiceStub(point));
				m_client = clientPtr;
				m_client->getClientStub().setConnectTimeoutMs(m_handle.m_contimeout);
				m_client->getClientStub().setRemoteCallTimeoutMs(m_handle.m_calltimeout);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void GetHandle(ServiceHandle &handle)
		{
			try
			{
				m_client->GetHandle(handle);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void SetEventHandle(const ServiceHandle &handle)
		{
			try
			{
				m_client->SetEventHandle(handle);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		//
		// RPC
		//
		/*!
		*
		**/
		void Start()
		{
			try
			{
				m_client->Start();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Listen(const std::string &multicastip, int multicastport)
		{
			try
			{
				m_client->Listen(multicastip, multicastport);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Notify(short topic, const std::string &multicastip, long multicastport)
		{
			try
			{
				m_client->Notify(topic, multicastip, multicastport);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Stop()
		{
			try
			{
				m_client->Stop();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}			
		}
		void Suspend()
		{
			try
			{
				m_client->Suspend();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Resume(bool isstopheart = false, bool isstopbroadcast = false, bool isstoprequest = false)
		{
			try
			{
				m_client->Resume(isstopheart, isstopbroadcast, isstoprequest);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		bool IsRunning()
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				int previousConnectTimeoutMs = m_client->getClientStub().getConnectTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(10000);
				m_client->getClientStub().setConnectTimeoutMs(10000);

				bool isRunning = m_client->IsRunning();

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
				m_client->getClientStub().setConnectTimeoutMs(previousTimeoutMs);
				return isRunning;
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);

				return false;
			}
		}
		string GetResponseUserData(const string &data)
		{
			try
			{
				m_client->getClientStub().setRequestUserData(data);
				m_client->SetResponseUserData();
				return m_client->getClientStub().getResponseUserData();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);

				return "";
			}
		}

		//
		//
		//
		/*!
		*
		**/
		void RegisterChildren(int type, const ServiceHandle &handle)
		{
			try
			{
				m_client->RegisterChildren(type, handle);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void RemoveChildren(string &ip, int port)
		{
			try
			{
				m_client->RemoveChildren(ip, port);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetChildren(int type, ServiceVector &handles)
		{
			try
			{
				m_client->GetChildren(type, handles);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void BindTo(int type, string &ip, int port)
		{
			try
			{
				m_client->BindTo(type, ip, port);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void CollectHeartbeat(const ServiceHandle &handle, const MasterChunkServer &chunkstatus, const JobTaskServer &taskstatus)
		{
			try
			{
				m_client->CollectHeartbeat(handle, chunkstatus, taskstatus);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetClientName(const std::string &name)
		{
			try
			{
				m_client->SetClientName(name);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		/*!
		* local not remote call, if connection is dropped, throw an exception
		**/
		void Ping()
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(1000);

				// Ping.
				m_client->getClientStub().ping();

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void NetworkBandwidthAsSender(std::string &ip, int ports, int calls, int buflen)
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(10000000);

				m_client->NetworkBandwidthAsSender(ip, ports, calls, buflen);

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void NetworkBandwidthAsReceiver(int calls, int buflen)
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(10000000);

				m_client->NetworkBandwidthAsReceiver(calls, buflen);

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
				
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		SessionObjectVector QuerySessionObject()
		{
			try
			{
				return m_client->QuerySessionObject();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void ClearSessionObject(const string &clientAddr)
		{
			try
			{
				m_client->ClearSessionObject(clientAddr);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		/*!
		*
		**/
		void Callback(const std::string &topic)
		{
			try
			{
				m_client->Callback(topic);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		//
		//
		//
		void SetParameter(GdeJobParameter &parameter)
		{
			try
			{
				m_client->SetParameter(parameter);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void AddParameterSurvey(std::vector<GdePosition> &survey)
		{
			try
			{
				m_client->AddParameterSurvey(survey);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetEvent(const ServiceHandle &eventhandle)
		{
			try
			{
				m_client->SetEvent(eventhandle);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetMapTask(JobTaskServer const& task)
		{
			try
			{
				m_client->SetMapTask(task);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		JobTaskServer GetMapTask()
		{
			try
			{
				return m_client->GetMapTask();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		int MapStart(JobParameter *parameter)
		{
			try
			{
				return m_client->MapStart(parameter);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Map(MapKey *key, MapValue *value)
		{
			try
			{
				m_client->getClientStub().setDefaultCallingSemantics(RCF::Oneway);
				m_client->Map(key,value);
				m_client->getClientStub().setDefaultCallingSemantics(RCF::Twoway);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		int Map()
		{
			try
			{
				return m_client->Map();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void MapFlush(unsigned long long chunkuuid)
		{
			try
			{
				m_client->MapFlush(chunkuuid);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void MapCombine()
		{
			try
			{
				m_client->MapCombine();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void MapShard()
		{
			try
			{
				m_client->MapShard();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		bool IsMapDone(const string& gfsfile)
		{
			try
			{
				return m_client->IsMapDone(gfsfile);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		//
		//
		//
		void SetReduceTask(JobTaskServer const& task)
		{
			try
			{
				m_client->SetReduceTask(task);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		JobTaskServer GetReduceTask()
		{
			try
			{
				return m_client->GetReduceTask();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}	
		}
		int ReduceStart()
		{
			try
			{
				return m_client->ReduceStart();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}	
		}
		void Reduce(unsigned long long chunkuuid, ReducePairVector &reducepairs)
		{
			try
			{
				m_client->Reduce(chunkuuid, reducepairs);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}	
		}
		int Reduce()
		{
			try
			{
				m_client->getClientStub().setDefaultCallingSemantics(RCF::Oneway);
				int fRet = m_client->Reduce();
				m_client->getClientStub().setDefaultCallingSemantics(RCF::Twoway);
				return fRet;
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void ReduceFlush()
		{
			try
			{
				m_client->ReduceFlush();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		bool IsReduceDone(const string& gfsfile)
		{
			try
			{
				return m_client->IsReduceDone(gfsfile);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		//
		//
		//
		long GetChunkUUIDCount(int tasktype)
		{
			try
			{
				JobTaskServer task;
				if(tasktype == ST_GFS_Mapper)
				{
					task = m_client->GetMapTask();
				}
				else if(tasktype == ST_GFS_Reducer)
				{
					task = m_client->GetReduceTask();
				}
				return task.m_chunkuuids.size();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		
		void AppendChunkUUID(int tasktype, unsigned long long chunkuuid)
		{
			try
			{
				JobTaskServer task;
				if(tasktype == ST_GFS_Mapper)
				{
					task = m_client->GetMapTask();
				}
				else if(tasktype == ST_GFS_Reducer)
				{
					task = m_client->GetReduceTask();
				}
				task.m_chunkuuids.push_back(chunkuuid);
				tasktype == ST_GFS_Mapper ? m_client->SetMapTask(task) : m_client->SetReduceTask(task);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		bool IsChunkAlreadySet(int tasktype, unsigned long long chunkuuid)
		{
			try
			{
				JobTaskServer task;
				if(tasktype == ST_GFS_Mapper)
				{
					task = m_client->GetMapTask();
				}
				else if(tasktype == ST_GFS_Reducer)
				{
					task = m_client->GetReduceTask();
				}

				for(int i = 0; i < task.m_chunkuuids.size(); i++)
				{
					if(task.m_chunkuuids[i] == chunkuuid)
						return true;
				}
				return false;
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset)
		{
			try
			{
				m_client->ReadData(filepath, data, readlength, offset);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype)
		{
			try
			{
				m_client->WriteData(filepath, data, datalength, offset, filehandletype);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void GetDataDirectory(int dirtype, bool inputoroutput, string &dir)
		{
			try
			{
				m_client->GetDataDirectory(dirtype, inputoroutput, dir);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void GetFileLength(std::string filepath, long long &filelength)
		{
			try
			{
				m_client->GetFileLength(filepath, filelength);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
	public:
		ServiceStubPtr m_client;
	};
#ifdef COMPILE_Slice
	typedef CGdeTaskCommonStub<I_GdeSliceTask> CGdeSliceTaskStub;
#endif
#ifdef COMPILE_Triangulate
	typedef CGdeTaskCommonStub<I_GdeTriangleFilterTask> CGdeTriangleFilterTaskStub;
#endif
#ifdef COMPILE_Instant
	typedef CGdeTaskCommonStub<I_GdeInstantAttributeTask> CGdeInstantAttributeTaskStub;
#endif
#ifdef COMPILE_DipAzimuth
	typedef CGdeTaskCommonStub<I_GdeDipAzimuthTask> CGdeDipAzimuthTaskStub;
#endif
#ifdef COMPILE_AlphaFilter
	typedef CGdeTaskCommonStub<I_GdeAlphaFilterTask> CGdeAlphaFilterTaskStub;
#endif
#ifdef COMPILE_Irregular
	typedef CGdeTaskCommonStub<I_GdeIrregularTask> CGdeIrregularTaskStub;
#endif
#ifdef COMPILE_Ellipse
	typedef CGdeTaskCommonStub<I_GdeEllipseTask> CGdeEllipseTaskStub;
#endif
#ifdef COMPILE_ThreeBayes
	typedef CGdeTaskCommonStub<I_GdeThreeBayesTask> CGdeThreeBayesTaskStub;
#endif
#ifdef COMPILE_BasicTrack
	typedef CGdeTaskCommonStub<I_GdeBasicTrackTask> CGdeBasicTrackTaskStub;
#endif
#ifdef COMPILE_RockPhysics
	typedef CGdeTaskCommonStub<I_GdeRockPhysicsTask> CGdeRockPhysicsTaskStub;
#endif
#ifdef COMPILE_Brick
	typedef CGdeTaskCommonStub<I_GdeBrickTask> CGdeBrickTaskStub;
#endif
#ifdef COMPILE_Conherency
	typedef CGdeTaskCommonStub<I_GdeConherencyTask> CGdeConherencyTaskStub;
#endif
}
#endif