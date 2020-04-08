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
#ifndef __ANYGDE_GFS_TASK_SERVANT_H__
#define __ANYGDE_GFS_TASK_SERVANT_H__

#include"anygde.h"
#include "gdetaskbasic.h"

#include "any/gfs/gfschunkservant.h"
using namespace AnyRCF;

#include "boost\circular_buffer.hpp"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_AnyGdeTask, "I_AnyGdeTask")
		//here is soft control(rcf server start/stop) hard control is implemented in console app using psService.
		RCF_METHOD_R1(bool, Init, const ServiceHandle&)
		RCF_METHOD_V1(void, GetHandle, ServiceHandle&)
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
		// map reduce
		RCF_METHOD_V5(void, InitDB, short, const std::string&, const std::string&, const std::string&, const std::string&)
		RCF_METHOD_V1(void, SetMapTask, JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetMapTask)
		RCF_METHOD_V1(void, SetReduceTask, JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetReduceTask)
		RCF_METHOD_V2(void, SetTaskDone, bool, int)
		RCF_METHOD_R1(bool, GetTaskDone, int)
		//communicate e.g. heart beats
		RCF_METHOD_V3(void, BindTo, int, string&, int)
		RCF_METHOD_V0(void, SetResponseUserData)
		RCF_METHOD_V1(void, SetClientName, const std::string&)
		RCF_METHOD_V1(void, Callback, const std::string&)
		RCF_METHOD_V1(void, OnCallback, const std::string&)
		// mapreduce
		RCF_METHOD_V1(void, SetParameter, GdeJobParameter&)
		RCF_METHOD_V1(void, AddParameterSurvey, std::vector<GdePosition>&)
		RCF_METHOD_V1(void, SetEvent, const ServiceHandle&)
		RCF_METHOD_R0(int, MapWork)
		RCF_METHOD_V2(void, MapStart, unsigned long long, GdeMapKeyVector&)
		RCF_METHOD_V1(void, Map, std::vector<GdeMapPair>&)
		RCF_METHOD_V1(void, MapFlush, unsigned long long)
		RCF_METHOD_V0(void, MapChunk)
		RCF_METHOD_R0(int, ReduceWork)
		RCF_METHOD_V2(void, ReduceStart,unsigned long long, GdeMapKeyVector&)
		RCF_METHOD_V2(void, Reduce, unsigned long long, std::vector<GdeMapPair>&)
		RCF_METHOD_V0(void, ReduceFlush)
		RCF_METHOD_V0(void, ReduceChunk)
		RCF_METHOD_V1(void, GetReduceResult, std::vector<GdeMapPair>&)
		RCF_METHOD_V3(void, GetOneReduceResultPair, int, GdeMapPair&, std::vector<unsigned long long>&)
		//
		RCF_METHOD_V2(void, GetFileLength, std::string, long long&)
		RCF_METHOD_V4(void, ReadData, std::string, std::vector<char>&, int, long long)
		RCF_METHOD_V5(void, WriteData, std::string, std::vector<char>&, int&, long long, int)
		RCF_METHOD_V3(void, GetDir, int, bool, string&)
		RCF_METHOD_V2(void, AppendChunkuuid, int, unsigned long long)
		RCF_METHOD_V2(void, GetChunkuuidcount, int, int&)
		RCF_METHOD_R2(bool, IsChunkuuidBelongToThis, int, unsigned long long)
		//
		RCF_METHOD_V2(void, SetMapTaskStatus, std::string&, JobTaskStatus&)
		RCF_METHOD_V2(void, GetMapTaskStatus, std::string&, JobTaskStatus&)
		RCF_METHOD_V2(void, SetReduceTaskStatus, std::string&, JobTaskStatus&)
		RCF_METHOD_V2(void, GetReduceTaskStatus, std::string&, JobTaskStatus&)
	RCF_END(I_AnyGdeTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeTaskServant : public  CGFSChunkServant/*CRCFServiceImpl*/
	{
		// callback
		typedef RcfClient<I_AnyGdeTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CGdeTaskServant();
		~CGdeTaskServant();

	public:
		//
		// service interface
		//
		/*!
		*
		**/
		void Start(); 
		void DoScheduleEntries(std::deque<RequestEntry *> &entries);

		/*!
		*
		**/
		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);
		CAnyClientImpl *DoDirectBindTo(int type, string &ip, int port);
		void DoCollectServerStatus(ServiceHandle &handle, MasterChunkServer &chunkstatus, JobTaskServer &taskstatus);

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
		void DoQueueMapWork(long key);
		void DoDirectMapWork();
		void MapStart(unsigned long long chunkuuid, GdeMapKeyVector &keys);
		void DoQueueMapStart(long key);
		void DoDirectMapStart(unsigned long long chunkuuid, GdeMapKeyVector &keys);
		void Map(std::vector<GdeMapPair> &pairs);
		void DoQueueMap(long key);
		void DoDirectMap(std::vector<GdeMapPair> &pairs);
		void MapFlush(unsigned long long chunkuuid);
		void DoQueueMapFlush(long key);
		void DoDirectMapFlush(unsigned long long chunkuuid);
		void MapChunk();
		void DoQueueMapChunk(long key);
		void DoDirectMapChunk();

		/*!
		*
		**/
		int ReduceWork();
		void DoQueueReduceWork(long key);
		void DoDirectReduceWork();
		void DoDirectReduceCombine(std::vector<unsigned long long> &chunkuuids);
		void ReduceStart(unsigned long long chunkuuid, GdeMapKeyVector &keys);
		void DoQueueReduceStart(long key);
		void DoDirectReduceStart(unsigned long long chunkuuid, GdeMapKeyVector &keys);
		void Reduce(unsigned long long chunkuuid, std::vector<GdeMapPair> &pairs);
		void DoQueueReduce(long key);
		void DoDirectReduce(unsigned long long chunkuuid, std::vector<GdeMapPair> &pairs);
		void ReduceFlush();
		void DoQueueReduceFlush(long key);
		void DoDirectReduceFlush();
		void ReduceChunk();
		void DoQueueReduceChunk(long key);
		void DoDirectReduceChunk();
		void GetReduceResult(std::vector<GdeMapPair> &pairs);
		void DoQueueGetReduceResult(long key);
		void DoDirectGetReduceResult(std::vector<GdeMapPair> &pairs);
		void GetOneReduceResultPair(int pairoffset, GdeMapPair &pair, std::vector<unsigned long long> &pairsoffsets);
		void DoQueueGetOneReduceResultPair(long key);
		void DoDirectGetOneReduceResultPair(int pairoffset, GdeMapPair &pair, std::vector<unsigned long long> &pairsoffsets);
		
		/*!
		*
		**/
		void GetFileLength(std::string filepath, long long &filelength);
		void DoQueueGetFileLength(long key);
		void DoDirectGetFileLength(std::string filepath, long long &filelength);
		void ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset);
		void DoQueueReadData(long key);
		void DoDirectReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset);
		void WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype);
		void DoQueueWriteData(long key);
		void DoDirectWriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype);
		void GetDir(int dirtype, bool inputoroutput, string &dir);
		void AppendChunkuuid(int towhichtask, unsigned long long chunkuuid);
		void GetChunkuuidcount(int towhichtask, int &chunkuuidcount);
		bool IsChunkuuidBelongToThis(int towhichtask, unsigned long long chunkuuid);
	private:
		//
		//
		//
		/*!
		*
		**/
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);
		void DoExtractSlice(std::vector<GdeMapPair>& pairs, bool ispremode, int inlCount, int crlCount);
		void GetChunkData(unsigned long long chunkuuid, std::vector<int> &cmpcounts, long sequenceOrder, double minTime, double maxTime, std::vector<std::vector<double> > &samples, bool ispremode, void* &mapperinputfilehandle);
		void GetChunkCmpcounts(unsigned long long chunkuuid, std::vector<int> &cmpcounts);
		void GetRasterChunkData(unsigned long long chunkuuid, std::vector<std::vector<GdePosition> > &positions, std::vector<std::vector<unsigned int> > &colors);
		void GetGxSurvey();
		std::vector<std::string> GetVelocityFile();
		void GetVelocity(int lineno, int cdpno, std::vector<double> &vrms, std::vector<double> &vint);
		void DoCreateDir(string filepath);

		string DoGetMapInputDir(const string &gfsname);
		string DoGetMapOutputDir(const string &gfsname);
		string DoGetReduceInputDir(const string &gfsname);
		string DoGetReduceOutputDir(const string &gfsname);
		
		string DoGetMapInputFile(unsigned long long chunkuuid, bool ispartmode = false);
		string DoGetMapOutputFile(unsigned long long chunkuuid, bool isreplace = false);
		string DoGetReduceInputFile(unsigned long long chunkuuid);
		string DoGetReduceOutputFile(bool isreplace = false);

		void DoResponseToHeartbeat();
		void DoResponseToMapperAllDone();
		void DoResponseToReducerAllDone();

		/*!
		*
		**/
		bool Time2Positionz(double time, int &ZPosition);
		bool Positionz2Time(int ZPosition, double &time);
		bool PositionToPostile(CGeoPoint<int> Position, int fetchlevel, CGeoPoint<int> &postile);
		bool PostileToPosition(CGeoPoint<int> postile, int fetchlevel, CGeoPoint<int> &Position1, CGeoPoint<int> &Position2);
		bool Postile2Morton(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);
		bool Morton2Postile(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		bool Morton2Tileid(std::vector<int> morton, int &tileid);
		bool Tileid2Morton(int tileid, std::vector<int> &morton);

		/*!
		*  trianglefilter
		**/
		void DoTriangleFilter(GdeMapPair &pair);
		void DoDealWithSlope(std::vector<double> &samples, std::vector<std::vector<double> > &results);
		void DoDealWithCorrelation(std::vector<double> &samples, std::vector<std::vector<double> > &results);
		int GetFilterOrder(double frequency);

		/*!
		*  anglefractrue
		**/
		void DoAngleFracture(GdeMapPair &pair);
		void DoAngleFracture360(GdeMapPair &pair);
		void RayTracing(std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, std::vector<std::vector<double> > &seta);
		void ConvertCAG_weight(std::vector<std::vector<double> > &cmps, std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, std::vector<double> &angles, std::vector<std::vector<double> > &cag);
		void ConvertCAG_interpolation(std::vector<std::vector<double> > &cmps, std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, std::vector<double> &angles, std::vector<std::vector<double> > &cag);
		void PolarToOrt(double fai, double offset, double &x, double &y);
		bool DoEllipse_Xiaoye(std::vector<double> &azimuths, std::vector<double> &amps, double &a, double &b, double &seta, double &xc, double &yc, bool isforcetorigin = false);
	public:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
		// current gfs file to locate dir
		string m_gfsname;
		// job parameter
		GdeJobParameter m_parameter;
		TaskSurveyInfoData m_surveyinfodata;
		// buffer
		boost::circular_buffer<GdeMapPair> m_mappercircular;
		boost::circular_buffer<GdeMapPair> m_reducercircular;
		// tasks assigned
		JobTaskServer m_maptask;
		JobTaskServer m_reducetask;
		// chunks
		std::vector<ServiceHandle> m_chunkhandles;
		std::vector<CAnyClientImpl*> m_chunkstubs;
		std::vector<ServiceHandle> m_reducehandles;
		std::vector<CAnyClientImpl*> m_reducestubs;
		CAnyClientImpl *m_masterclient;
		CAnyClientImpl *m_jobclient;
		// chunk<->tileid
		std::map<unsigned long long, int> m_chunkuuid_tileid;
		bool m_ismapdone;
		bool m_isreducedone;

		//
		JobTaskStatusMap m_mapperstatus;
		JobTaskStatusMap m_reducerstatus;
	};
}

#endif