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
#ifndef __ANYRCF_GFS_MASTER_STUB_H__
#define __ANYRCF_GFS_MASTER_STUB_H__

//
#include "anyrcf.h"
#include "servicestub.h"
#include "gfsmasterservant.h"

//
namespace AnyRCF
{
	/*!
	*
	**/
	class ANYRCF_CLASS CGFSMasterStub : public CServiceStub<I_AnyGFSMaster>
	{
	public:
		CGFSMasterStub();
		~CGFSMasterStub();

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitDB(short type, const string &srcname, const string &user, const string &pwd, const string &dbname)
		{
			try
			{
				m_client->InitDB(type, srcname, user, pwd, dbname);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetDB(MasterDBConnection &conn)
		{
			try
			{
				m_client->GetDB(conn);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		unsigned long Open(const std::string &gfsName, short type)
		{
			try
			{
				return m_client->Open(gfsName, type);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				return 0;
			}
		}
		unsigned long Open(const MasterNamespace &node)
		{
			try
			{
				return m_client->Open(node);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				return 0;
			}
		}

		unsigned long Delete(const std::string &gfsName, short type)
		{
			try
			{
				return m_client->Delete(gfsName, type);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				return 0;
			}
		}
		void GetGFSName(std::vector<std::string> &allfilenames)
		{
			try
			{
				m_client->GetGFSName( allfilenames);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetMasterNamespace(std::vector<MasterNamespace> &metanodes)
		{
			try
			{
				m_client->GetMasterNamespace(metanodes);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void UpdateReplicas(std::string &metaname, int replicas)
		{
			try
			{
				m_client->UpdateReplicas(metaname, replicas);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void LoadMetaRecords(bool isreload = false)
		{
			try
			{
				m_client->LoadMetaRecords(isreload);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void SaveMetaRecords()
		{
			try
			{
				m_client->SaveMetaRecords();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void RemoveMetaRecords()
		{
			try
			{
				m_client->RemoveMetaRecords();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void UpdateValiduuids(std::string filename, std::vector<unsigned long long> &validuuids)
		{
			try
			{
				m_client->UpdateValiduuids(filename, validuuids);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void AddMetaRecords(std::string filename)
		{
			try
			{
				m_client->AddMetaRecords(filename);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void DeleteMetaRecords(std::string filename)
		{
			try
			{
				m_client->DeleteMetaRecords(filename);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void RemoveChunkDir(std::string filename)
		{
			try
			{
				m_client->RemoveChunkDir(filename);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		std::vector<unsigned long long> GetChunk(const std::string &gfsName)
		{
			try
			{
				return m_client->GetChunk(gfsName);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);

				std::vector<unsigned long long> rt;
				return rt;
			}
		}	
		std::vector<std::string> GetAllFilenames()
		{
			try
			{
				return m_client->GetAllFilenames();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);

				std::vector<std::string> rt;
				return rt;
			}
		}	
		void GetAllChunkServers(MasterChunkServerVector &chunkservers)
		{
			try
			{
				m_client->GetAllChunkServers(chunkservers);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void GetChunkMissedTiles(std::string filename, MasterChunkServerVector &chunkservers, std::vector<std::vector<unsigned long long> > &misseduuids)
		{
			try
			{
				m_client->GetChunkMissedTiles(filename, chunkservers, misseduuids);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		std::vector<unsigned long long> AllocateChunk(const std::string &gfsName, unsigned long chunknumber)
		{
			try
			{
				return m_client->AllocateChunk(gfsName, chunknumber);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);

				std::vector<unsigned long long> rt;
				return rt;
			}
		}
		void AllocateGeoLocationChunk(const std::string &filename, std::vector<std::vector<char> > &geocodes, std::vector<std::vector<string> > &alluuidcodes, \
			std::vector<std::vector<unsigned long long> > &allpartlengths, std::vector<std::vector<std::vector<char> > > &allrowkeycodes, bool isfirst = true)
		{
			try
			{
				m_client->AllocateGeoLocationChunk(filename, geocodes, alluuidcodes, allpartlengths, allrowkeycodes, isfirst);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetGeoLocationRelatedFiles(std::vector<char> &geocode, std::vector<string> &uuidcodes, std::vector<std::vector<int> > &rowkeyoffsets)
		{
			try
			{
				m_client->GetGeoLocationRelatedFiles(geocode, uuidcodes, rowkeyoffsets);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetChunkServers(const std::string &gfsName, MasterChunkServerVector &chunkservers)
		{
			try
			{
				m_client->GetChunkServers(gfsName, chunkservers);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);

				std::vector<unsigned long long> rt;
			}
		}
		std::vector<unsigned long long> AppendChunk(const std::string &gfsName, unsigned long chunknumber)
		{
			try
			{
				return m_client->AppendChunk(gfsName, chunknumber);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		MasterRecordVector Lookup(const string &dir, short fileType)
		{
			try
			{
				return m_client->Lookup(dir, fileType);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);

				MasterRecordVector rt;
				return rt;
			}
		}
		unsigned long long Chunk4Read(const string &filename, long blockidx, MasterChunkServerVector &chunks)
		{
			try
			{
				return m_client->Chunk4Read(filename, blockidx, chunks);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				return 0;
			}
		}
		unsigned long long Chunk4Write(const string &filename, long blockidx, MasterChunkServerVector &chunks)
		{
			try
			{
				return m_client->Chunk4Write(filename, blockidx, chunks);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				return 0;
			}
		}
		void Chunk4Readuuid(const string &filename, unsigned long long chunkuuid, MasterChunkServerVector &chunks)
		{
			try
			{
				m_client->Chunk4Readuuid(filename, chunkuuid, chunks);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Chunk4Writeuuid(const string &filename, unsigned long long chunkuuid, MasterChunkServerVector &chunks)
		{
			try
			{
				m_client->Chunk4Writeuuid(filename, chunkuuid, chunks);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Ready4Job(const std::string &gfsname, std::vector<std::vector<unsigned long long> > &chunkuuids)
		{
			try
			{
				m_client->Ready4Job(gfsname, chunkuuids);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Chunk4Job(unsigned long long chunkuuid, MasterChunkServerVector &chunks)
		{
			try
			{
				m_client->Chunk4Job(chunkuuid, chunks);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetUploadStatus(const std::string& gfsname, GFSUploadStatus& uploadstatus)
		{
			try
			{
				m_client->SetUploadStatus(gfsname, uploadstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetUploadStatus(const std::string& gfsname, GFSUploadStatus& uploadstatus)
		{
			try
			{
				m_client->GetUploadStatus(gfsname, uploadstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetDownloadStatus(const std::string& gfsname, GFSDownloadStatus& downloadstatus)
		{
			try
			{
				m_client->SetDownloadStatus(gfsname, downloadstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetDownloadStatus(const std::string& gfsname, GFSDownloadStatus& downloadstatus)
		{
			try
			{
				m_client->GetDownloadStatus(gfsname, downloadstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetChunkStatus(const std::string& gfsname,const std::string& chunkip, long chunkport, GFSChunkStatus& chunkstatus)
		{
			try
			{
				m_client->GetChunkStatus(gfsname, chunkip, chunkport,chunkstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetChunkStatus(const std::string& gfsname,const std::string& chunkip, long chunkport, GFSChunkStatus& chunkstatus)
		{
			try
			{
				m_client->SetChunkStatus(gfsname, chunkip, chunkport,chunkstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
	};
	template class ANYRCF_CLASS CServiceStub<I_AnyGFSMaster>;
}

#endif