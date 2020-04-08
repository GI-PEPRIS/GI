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
#ifndef __ANYRCF_GFS_MASTER_SERVANT_H__
#define __ANYRCF_GFS_MASTER_SERVANT_H__

#include"anyrcf.h"
#include "rcfserviceimpl.h"
#include "eventstub.h"

#include "libconhash\conhash.h"

//
namespace AnyRCF
{
	// interface
	RCF_BEGIN(I_AnyGFSMaster, "I_AnyGFSMaster")
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
		RCF_METHOD_V1(void, GetDB, MasterDBConnection&)
		RCF_METHOD_V1(void, SetMapTask, const JobTaskServer&)
		RCF_METHOD_V1(void, SetReduceTask, const JobTaskServer&)
		//communicate e.g. heart beats
		RCF_METHOD_V3(void, BindTo, int, string&, int)
		RCF_METHOD_V0(void, SetResponseUserData)
		RCF_METHOD_V1(void, SetClientName, const std::string&)
		RCF_METHOD_V1(void, Callback, const std::string&)
		RCF_METHOD_V1(void, OnCallback, const std::string&)
		// db
		RCF_METHOD_V1(void, LoadMetaRecords, bool)
		RCF_METHOD_V1(void, GetMasterNamespace, std::vector<MasterNamespace>&)
		RCF_METHOD_V1(void, GetGFSName, std::vector<std::string>&)
		RCF_METHOD_V2(void, UpdateReplicas, std::string&, int)
		RCF_METHOD_V2(void, UpdateValiduuids, std::string, std::vector<unsigned long long>&)
		RCF_METHOD_V1(void, AddMetaRecords, std::string)
		RCF_METHOD_V1(void, DeleteMetaRecords, std::string)
		RCF_METHOD_V1(void, RemoveChunkDir, std::string)
		RCF_METHOD_V0(void, SaveMetaRecords)
		RCF_METHOD_V0(void, RemoveMetaRecords)
		// chunk info
		RCF_METHOD_R2(MasterRecordVector, Lookup, const string&, short);
		RCF_METHOD_R2(unsigned long, Open, const string&, short);
		RCF_METHOD_R1(unsigned long, Open, const MasterNamespace&);
		RCF_METHOD_R2(unsigned long, Delete, const string&, short);
		RCF_METHOD_R2(std::vector<unsigned long long>, AllocateChunk, const string&, long);
		RCF_METHOD_V6(void, AllocateGeoLocationChunk, const std::string&, std::vector<std::vector<char> >&, std::vector<std::vector<string> >&, std::vector<std::vector<unsigned long long> >&, std::vector<std::vector<std::vector<char> > >&, bool)
		RCF_METHOD_V3(void, GetGeoLocationRelatedFiles, std::vector<char>&, std::vector<string>&, std::vector<std::vector<int> >&)
		RCF_METHOD_R2(std::vector<unsigned long long>, AppendChunk, const string&, long);
		RCF_METHOD_R1(std::vector<unsigned long long>, GetChunk, const string&);
		RCF_METHOD_R0(std::vector<std::string>, GetAllFilenames);
		RCF_METHOD_V1(void, GetAllChunkServers, MasterChunkServerVector&)
		RCF_METHOD_V2(void, GetChunkServers, const string&, MasterChunkServerVector&)
		RCF_METHOD_V3(void, GetChunkMissedTiles, std::string, MasterChunkServerVector&, std::vector<std::vector<unsigned long long> > &)
		RCF_METHOD_R3(unsigned long long, Chunk4Read, const std::string&, long, MasterChunkServerVector&);
		RCF_METHOD_R3(unsigned long long, Chunk4Write,  const std::string&, long, MasterChunkServerVector&);
		RCF_METHOD_V3(void, Chunk4Readuuid, const std::string&, unsigned long long, MasterChunkServerVector&);
		RCF_METHOD_V3(void, Chunk4Writeuuid, const std::string&, unsigned long long, MasterChunkServerVector&);
		// job
		RCF_METHOD_V2(void, Ready4Job, const std::string&, std::vector<std::vector<unsigned long long> >&)
		RCF_METHOD_V2(void, Chunk4Job, unsigned long long, MasterChunkServerVector&)
		// status
		RCF_METHOD_V2(void, SetUploadStatus, const std::string&, GFSUploadStatus&)
		RCF_METHOD_V2(void, GetUploadStatus, const std::string&, GFSUploadStatus&)
		RCF_METHOD_V2(void, SetDownloadStatus, const std::string&, GFSDownloadStatus&)
		RCF_METHOD_V2(void, GetDownloadStatus, const std::string&, GFSDownloadStatus&)
		RCF_METHOD_V4(void, GetChunkStatus, const std::string&, const std::string& , long,GFSChunkStatus&)
		RCF_METHOD_V4(void, SetChunkStatus, const std::string&, const std::string& , long,GFSChunkStatus&)
	RCF_END(I_AnyGFSMaster)

	/*!
	* missing heatbeats:
	* to decrements count of replicas for all chunks on dead chunserver;
	* re-replicates in background;
	* reboots£º
	* replays log: recover namespace, file-to-chunkId;
	* ask chunk servers which chunks they hold, to recover chunk-id-to-chunkserver mapping
	* if chunk server has older chunk, its stale; if chunkserver has newer chunk, adopt version number
	**/
	class ANYRCF_CLASS CGFSMasterServant : public CRCFServiceImpl
	{
	public:
		// callback
		typedef RcfClient<I_AnyGFSMaster> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		// current path to self and its children dir or file
		typedef std::map<string, MasterRecordVector > MetaRecordTable;
		typedef MetaRecordTable::iterator meta_itr;
		typedef MetaRecordTable::const_iterator meta_citr;

		// file to chunk or block(uuid) mapping
		typedef std::map<string, std::vector<unsigned long long> > FileTable;
		typedef FileTable::iterator uuid_itr;
		typedef FileTable::const_iterator uuid_citr;

		// chunk uuid to chunk location mapping
		typedef std::map<unsigned long long, std::vector<unsigned long long> > ChunkLocationTable;
		typedef ChunkLocationTable::iterator loc_itr;
		typedef ChunkLocationTable::const_iterator loc_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CGFSMasterServant();
		~CGFSMasterServant();

	public:
		//
		// service interface
		//
		/*!
		*
		**/
		void Start(); 
		void DoScheduleEntries(std::deque<RequestEntry *> &entries)
		{
		}
		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);
		void DoCollectServerStatus(ServiceHandle &handle, MasterChunkServer &chunkstatus, JobTaskServer &taskstatus);

		//
		// 
		//
		/*!
		* sync functions
		**/
		void InitDB(short type, const std::string &srcname, const std::string &user, const std::string &pwd, const std::string &dbname);
		void GetDB(MasterDBConnection &conn);
		MasterRecordVector Lookup(const string &dir, short fileType);
		void DoLookup(long key);

		void UpdateReplicas(std::string &metaname, int &replicas);
		void DoQueueUpdateReplicas(long key);
		void DoDirectUpdateReplicas(std::string &metaname, int &replicas);
		void LoadMetaRecords(bool isreload);
		void GetMasterNamespace(std::vector<MasterNamespace> &metanodes);
		void DoQueueLoadMetaRecords(long key);
		void GetGFSName(std::vector<std::string> &allfilenames);
		void DoQueueGetGFSName(long key);
		void SaveMetaRecords();
		void DoQueueSaveMetaRecords(long key);
		void UpdateValiduuids(std::string filename, std::vector<unsigned long long> &validuuids);
		void DoQueueUpdateValiduuids(long key);
		void AddMetaRecords(std::string filename);
		void DoQueueAddMetaRecords(long key);
		void DeleteMetaRecords(std::string filename);
		void DoQueueDeleteMetaRecords(long key);
		void RemoveChunkDir(std::string filename);
		void DoQueueRemoveChunkDir(long key);
		void RemoveMetaRecords();
		void DoQueueRemoveMetaRecords(long key);
		std::vector<std::string> GetAllFilenames();

		/*!
		*
		**/
		unsigned long Open(const string &name, short type);
		unsigned long Open(const MasterNamespace &metanode);
		unsigned long Delete(const string &name, short type);
		std::vector<unsigned long long> AllocateChunk(const std::string &filename, long chunknumber);
		std::vector<unsigned long long> AppendChunk(const std::string &filename, long chunknumber);	
		void AllocateGeoLocationChunk(const std::string &filename, std::vector<std::vector<char> > &geocodes, std::vector<std::vector<string> > &alluuidcodes, \
			std::vector<std::vector<unsigned long long> > &allpartlengths, std::vector<std::vector<std::vector<char> > > &allrowkeycodes, bool isfirst = true);
		void GetGeoLocationRelatedFiles(std::vector<char> &geocode, std::vector<string> &uuidcodes, std::vector<std::vector<int> > &rowkeyoffsets);
		void DoResetCandidateChildren(std::vector<unsigned long long> &machinelocations);
		std::vector<unsigned long long> GetChunk(const std::string &filename);
		void GetAllChunkServers(MasterChunkServerVector &chunkservers);
		void GetChunkServers(const std::string &filename, MasterChunkServerVector &chunkservers);
		void GetChunkMissedTiles(std::string filename, MasterChunkServerVector &chunkservers, std::vector<std::vector<unsigned long long> > &misseduuids);

		/*!
		*
		**/
		unsigned long long Chunk4Read(const std::string &filename, long chunkindex, MasterChunkServerVector &chunks);
		void DoQueueChunk4Read(long key);
		unsigned long long DoDirectChunk4Read(const std::string &filename, long chunkindex, MasterChunkServerVector &chunks);
		void Chunk4Readuuid(const std::string &filename, unsigned long long chunkuuid, MasterChunkServerVector &chunks);
		unsigned long long Chunk4Write(const std::string &filename, long chunkindex, MasterChunkServerVector &chunks);
		void DoQueueChunk4Write(long key);
		unsigned long long DoDirectChunk4Write(const std::string &filename, long chunkindex, MasterChunkServerVector &chunks);
		void Chunk4Writeuuid(const std::string &filename, unsigned long long chunkuuid, MasterChunkServerVector &chunks);

		//
		//
		//
		/*!
		* per chunk server 
		**/
		void Ready4Job(const std::string &gfsname, std::vector<std::vector<unsigned long long> > &chunkuuids);
		void Chunk4Job(unsigned long long chunkuuid, MasterChunkServerVector &chunks);

		//
		//
		//
		/*!
		*
		**/
		void SetUploadStatus(const std::string& gfsname, GFSUploadStatus& uploadstatus);
		void GetUploadStatus(const std::string& gfsname, GFSUploadStatus& uploadstatus);
		void SetDownloadStatus(const std::string& gfsname, GFSDownloadStatus& downloadstatus);
		void GetDownloadStatus(const std::string& gfsname, GFSDownloadStatus& downloadstatus);
		void SetChunkStatus(const std::string& gfsname,const std::string& chunkip, long chunkport, GFSChunkStatus& chunkstatus);
		void GetChunkStatus(const std::string& gfsname,const std::string& chunkip, long chunkport, GFSChunkStatus& chunkstatus);
		//
		//
		//
		static unsigned long long DoCalculateConcensusHash(const char *instr);

	private:
		/*!
		*
		**/
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);

		void DoDirectLoadMetaRecords(bool isreload);
		void DoDirectGetGFSName(std::vector<std::string>& allfilenames);
		void DoDirectUpdateValiduuids(std::string filename, std::vector<unsigned long long> &validuuids);
		void DoDirectAddMetaRecords(std::string filename);
		void DoDirectDeleteMetaRecords(std::string filename);
		void DoDirectRemoveChunkDir(std::string filename);
		void DoDirectSaveMetaRecords();
		void DoDirectRemoveMetaRecords();

		void DoAllocateWithRrobin(const std::string &filename, long chunknumber);
		void DoAllocateWithConcensus(const std::string &filename, long chunknumber);
		void DoGetDirectChunkServer(unsigned long long chunkuuid, MasterChunkServerVector &chunkserver);
		void DoGetHashChunkServer(unsigned long long chunkuuid, MasterChunkServerVector &chunkserver);
		void DoAllocateWithLocationConcensus(const std::string &filename, std::vector<unsigned long long> &uuids);

		/*!
		*
		**/
		static bool CompareMaterRecordHandle(const MasterRecord &first, const MasterRecord &second)
		{
			return first.m_filehandle < second.m_filehandle;
		}
		static unsigned long long MakeConsistentHash(const ServiceHandle &handle);

	public:
		// meta records
		RCF::Mutex m_metaMutex;
		// map each path to its children records
		MetaRecordTable m_metas;	
		// file to uuids
		FileTable m_chunkuuids;	
		// whether chunkfile exist
		std::map<string, std::vector<bool> > m_chunkuuidexists;
		// uuid 2 chunk location
		ChunkLocationTable m_chunklocations;	

		// current chunk server number
		long m_chunkservernumber;
		// maximum chunk server number
		long m_chunkservermaxnumber;
		// robin, here not consisten hash
		long m_chunkserverrobin;

		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;

		// database
		MasterDBConnection m_srcDesc;

		// concensus hash
		struct conhash_s *m_conhash;
		struct node_s m_nodes[1024];

		//
		RCF::Mutex m_uploadstatusMutex;
		GFSUploadStatusMap m_uploadstatus;
		RCF::Mutex m_downloadstatusMutex;
		GFSDownloadStatusMap m_downloadstatus;
		RCF::Mutex m_chunkstatusMutex;
		GFSChunkStatusMap m_chunkstatus;
	};
}

#endif
