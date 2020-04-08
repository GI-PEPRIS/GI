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
#ifndef __ANYRCF_GFS_TASK_STUB_H__
#define __ANYRCF_GFS_TASK_STUB_H__

//
#include "anyrcf.h"
#include "servicestub.h"
#include "gfstaskservant.h"

//
namespace AnyRCF
{
	class CGFSTaskStub : public CServiceStub<I_AnyGFSTask>
	{
	public:
		CGFSTaskStub()
		{
		}
		virtual ~CGFSTaskStub()
		{
		}
	public:
		//
		//
		//

		//
		//
		//
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
		void MapStart(JobParameter *parameter)
		{
			try
			{
				m_client->MapStart(parameter);
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
		void Map()
		{
			try
			{
				m_client->Map();
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
		void ReduceStart()
		{
			try
			{
				m_client->ReduceStart();
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
		void Reduce()
		{
			try
			{
				m_client->getClientStub().setDefaultCallingSemantics(RCF::Oneway);
				m_client->Reduce();
				m_client->getClientStub().setDefaultCallingSemantics(RCF::Twoway);
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
	};
}
#endif