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
#ifndef __ANYRCF_GFS_CHUNK_SERVANT_H__
#define __ANYRCF_GFS_CHUNK_SERVANT_H__

#include"anyrcf.h"
#include "rcfserviceimpl.h"

#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "rcf/FileUpload.hpp"
#include "rcf/FileDownload.hpp"

//
namespace AnyRCF
{
	// interface
	RCF_BEGIN(I_AnyGFSChunk, "I_AnyGFSChunk")
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
		//communicate  e.g. heart beats
		RCF_METHOD_V3(void, BindTo, int, string&, int)
		RCF_METHOD_V0(void, SetResponseUserData)
		RCF_METHOD_V1(void, SetClientName, const std::string&)
		RCF_METHOD_V1(void, Callback, const std::string&)
		RCF_METHOD_V1(void, OnCallback, const std::string&)

		// data transfer
		RCF_METHOD_V1(void, GetDataDir, std::string&)
		RCF_METHOD_R2(int, UploadFileByPath, std::string, RCF::FileUpload&)
		RCF_METHOD_R6(int, HandleChunkFile, std::string, int, int, int, std::vector<unsigned long long>&, std::vector<int>&)
		RCF_METHOD_R6(int, HandleChunkFileDistribute, std::string, std::vector<unsigned long long>&, std::vector<std::vector<int> >&, int, std::vector<ServiceHandle>&, std::vector<string>&)
		RCF_METHOD_R3(int, IsChunkFileExist, string, std::vector<unsigned long long>&, std::vector<bool>&)
		RCF_METHOD_R13(int, HandleChunkFile_Merge, string, int, std::vector<unsigned long long>&, std::vector<int>&, int, int, int, int, std::vector<int>&, int, int, int, int)
		RCF_METHOD_V2(void, MergeFile, string, string)
		RCF_METHOD_V4(void, MergeFileAdvanced, std::vector<string>&, std::vector<string>&, std::vector<long long>&, std::vector<long long>&)
		RCF_METHOD_R4(int, UploadFileByChain, std::string, RCF::FileUpload&, std::vector<ServiceHandle>&, std::vector<string>&)
		RCF_METHOD_R2(int, DownloadFileByPath, std::string, RCF::FileDownload&)
		RCF_METHOD_V2(void, GetFileLength, std::string, long long&)
		RCF_METHOD_R4(int, ReadData, std::string, std::vector<char>&, int, long long)
		RCF_METHOD_R5(int, WriteData, std::string, std::vector<char>&, int&, long long, int)
		RCF_METHOD_R7(int, WriteDataByChain, std::string, std::vector<char>&, int&, long long, int, std::vector<ServiceHandle>&, std::vector<string>&)
		RCF_METHOD_V3(void, GetChunkMissedTiles, std::string, std::vector<unsigned long long>&, std::vector<unsigned long long>&)
		RCF_METHOD_V1(void, RemoveDir, std::string)
		RCF_METHOD_V1(void, RemoveFile, std::string)
		/*RCF_METHOD_R7(bool, Opensgy, int, string, std::vector<string>&, int, string, string, string)
		RCF_METHOD_V0(void, Closesgy)
		RCF_METHOD_R13(bool, FormOneTile, std::vector<int>&, std::vector<std::vector<std::vector<int> > >&, std::vector<std::vector<int> >&, RCFpointInt, RCFpointInt, \
		RCFpointInt, RCFpointInt, std::vector<long long>&, std::vector<int>&, long, int, std::vector<ServiceHandle>&, std::vector<string>)*/
		// status
		RCF_METHOD_V2(void, SetTaskStatus, std::string&, JobTaskStatus&)
		RCF_METHOD_V2(void, GetTaskStatus, std::string&, JobTaskStatus&)
		RCF_METHOD_V3(void, SetChunkStatus, const std::string&, const std::string&, long);
	    RCF_METHOD_V4(void, GetChunkStatus, const std::string&, const std::string&, long, GFSChunkStatus&);
	RCF_END(I_AnyGFSChunk)

	/*!
	*
	**/
	class ANYRCF_CLASS CGFSChunkServant : public CRCFServiceImpl
	{
		// callback
		typedef RcfClient<I_AnyGFSChunk> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		//
		typedef std::map<unsigned long long, std::string> ChunkTable;
		typedef ChunkTable::iterator chunk_itr;
		typedef ChunkTable::const_iterator chunk_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CGFSChunkServant();
		~CGFSChunkServant();

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
		void DoCreateDir(string filepath);
		void DoCollectServerStatus(ServiceHandle &handle, MasterChunkServer &chunkstatus, JobTaskServer &taskstatus);

		//
		//
		//
		/*!
		*
		**/
		void GetDataDir(std::string &datadir);
		void DoQueueGetDataDir(long key);
		void DoDirectGetDataDir(std::string &datadir);

		void GetFileLength(std::string filepath, long long &filelength);
		void DoQueueGetFileLength(long key);
		void DoDirectGetFileLength(std::string filepath, long long &filelength);

		//
		//
		//
		/*!
		*
		**/
		int UploadFileByPath(std::string filepath, RCF::FileUpload &fileUpload);//filepath是服务端文件dir，fileUpload包含客户端文件path
		void DoQueueUploadFileByPath(long key);
		void DoDirectUploadFileByPath(std::string filepath, RCF::FileUpload &fileUpload);

		int HandleChunkFile(string filepath, int maxopenfilenum, int sgytype, int tilesizez, std::vector<unsigned long long> &tileid_uuid, std::vector<int> &tileid_gdtilecounts);
		int CGFSChunkServant::HandleChunkFileDistribute(string filepath, std::vector<unsigned long long> &tileid_uuid, std::vector<std::vector<int> > &tileid_chunkoffset, int curchunkoffset, \
			std::vector<ServiceHandle> &chunkhandles, std::vector<string> &uploadfiledirs);
		int IsChunkFileExist(string filepath, std::vector<unsigned long long> &tileid_uuid, std::vector<bool> &tileid_isexist);
		int HandleChunkFile_Merge(string filepath, int maxopenfilenum, std::vector<unsigned long long> &tileid_uuid, std::vector<int> &tileid_chunkoffset, int curchunkoffset, int linenum, int cdpnum, int samplenum, std::vector<int> &gridpos_cmpcount, \
			int tileSizex, int tileSizey, int tileSizez, int octreeLevel);
		void ReverseBytes(char *bytes, short nSize);
		void IBMtoIEEE(char *bytes);
		void MergeFile(string sourcefile, string targetfile);
		void MergeFileAdvanced(std::vector<string> &sourcefiles, std::vector<string> &targetfiles, std::vector<long long> &startfileposes, std::vector<long long> &readlengths);

		int DownloadFileByPath(std::string filepath, RCF::FileDownload &fileDownload);//filepath是服务端文件path，fileDownload包含客户端文件dir
		void DoQueueDownloadFileByPath(long key);
		void DoDirectDownloadFileByPath(std::string filepath, RCF::FileDownload &fileDownload);

		int UploadFileByChain(std::string filepath, RCF::FileUpload &fileUpload, std::vector<ServiceHandle> &others, std::vector<string> &dirs);
		void DoQueueUploadFileByChain(long key);
		void DoDirectUploadFileByChain(std::string filepath, RCF::FileUpload &fileUpload, std::vector<ServiceHandle> &others, std::vector<string> &dirs);

		/*bool Opensgy(int type, string sgyfileName, std::vector<string> &othersgyfileNames, int taskcount, string ip, string username, string password);
		void Closesgy();
		bool FormOneTile(std::vector<int> &cmpcounts, std::vector<std::vector<std::vector<int> > > &allfileposes, std::vector<std::vector<int> > &allsgyoffsets, RCFpointInt Position1, RCFpointInt Position2, \
			RCFpointInt tileSize, RCFpointInt surveydata, std::vector<long long> &allnTraceLens, std::vector<int> &allnTypes, \
			long allcmpcount, int threadoffset, std::vector<ServiceHandle> &others, std::vector<string> uploadpaths);
		float* ReadTraceData(int nOrder, int threadoffset, int start, int end, int interval, std::vector<std::vector<int> > &fileposes, std::vector<int> &sgyoffsets, int cdpNum, int lineNum, \
			int nTracePt, long long nTraceLen, std::vector<long long> &othernTraceLens, int nType, std::vector<int> &othernTypes);
		void ReverseBytes(char *bytes, short nSize);
		void IBMtoIEEE(char *bytes);*/

		//
		//
		//
		/*!
		*
		**/
		int ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset);
		void DoQueueReadData(long key);
		void DoDirectReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset);
		
		int WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype);
		void DoQueueWriteData(long key);
		void DoDirectWriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype);

		int WriteDataByChain(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype, std::vector<ServiceHandle> &others, std::vector<string> &paths);
		void DoQueueWriteDataByChain(long key);
		void DoDirectWriteDataByChain(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype, std::vector<ServiceHandle> &others, std::vector<string> &paths);

		void GetChunkMissedTiles(std::string filepath, std::vector<unsigned long long> &checkuuids, std::vector<unsigned long long> &misseduuids);
		void DoQueueGetChunkMissedTiles(long key);
		void DoDirectGetChunkMissedTiles(std::string filepath, std::vector<unsigned long long> &checkuuids, std::vector<unsigned long long> &misseduuids);

		void RemoveDir(std::string filedir);
		void DoQueueRemoveDir(long key);
		void DoDirectRemoveDir(std::string filedir);
		void RemoveFile(std::string filepath);

		//
		//
		//
		/*!
		*
		**/
		void SetTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus);
		void GetTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus);
		/*!
		*
		**/
		void SetChunkStatus(const std::string& gfsname, const std::string& chunkip, long chunkport);
		void GetChunkStatus(const std::string& gfsname,const std::string& chunkip, long chunkport, GFSChunkStatus& chunkstatus);


	private:
		//
		//
		//
		/*!
		*
		**/
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);
		void OnServerFileUpload(RCF::RcfSession & session, const RCF::FileUploadInfo & uploadInfo);
		void OnServerFileDownload(RCF::RcfSession & session, const RCF::FileDownloadInfo & uploadInfo);
		RCF::BandwidthQuotaPtr UploadBandwidthQuotaCb(RCF::RcfSession & session);
		RCF::BandwidthQuotaPtr DownBandwidthQuotaCb(RCF::RcfSession & session);

	private:
		// memory cache except directly up&dpwn load file
		// ...

		// server as report
		MasterChunkServer m_report;
		// chunk to file
		ChunkTable m_chunks;

		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;

		//
		RCF::Mutex m_taskstatusmutex;
		JobTaskStatusMap m_taskstatus;

		// chunk stubs
		std::vector<void *> m_chunkclients;
		std::vector<ServiceHandle> m_chunkhandles;

		// for formonetile
		int m_taskcount;
		wstring m_sgyfileName;
		std::vector<void *> m_sgyHandles;
		std::vector<wstring> m_othersgyfileNames;
		std::vector<std::vector<void *> > m_othersgyHandles;
		const CAnyFileBasic &m_fileBasic;

		RCF::Mutex m_chunkstatusMutex;
		GFSChunkStatusMap m_chunkstatusmap;
		GFSChunkStatus m_chunkstatus;
		double m_uploadedtilesize;
	};
}
#endif
