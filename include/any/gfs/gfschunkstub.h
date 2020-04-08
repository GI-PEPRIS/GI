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
#ifndef __ANYRCF_GFS_CHUNK_STUB_H__
#define __ANYRCF_GFS_CHUNK_STUB_H__

//
#include "anyrcf.h"
#include "gfschunkservant.h"
#include "servicestub.h"

//
namespace AnyRCF
{
	/*!
	*
	**/
	class ANYRCF_CLASS CGFSChunkStub : public CServiceStub<I_AnyGFSChunk>
	{
	public:
		/*!
		*
		**/
		CGFSChunkStub();
		~CGFSChunkStub();

	public:
		//
		//
		//
		/*!
		*
		**/
		void GetDataDir(std::string &datadir)
		{
			try
			{
				m_client->GetDataDir(datadir);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		int UploadFileByPath(std::string filepath, RCF::FileUpload &fileUpload)
		{
			try
			{
				string filepathtmp = filepath.substr(0, filepath.find_last_of("\\"));
				fileUpload.setUploadToPath(filepathtmp);
				return m_client->UploadFileByPath(filepath, fileUpload);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				throw e;
			}
		}
		int HandleChunkFile(string filepath, int maxopenfilenum, int sgytype, int tilesizez, std::vector<unsigned long long> &tileid_uuid, std::vector<int> &tileid_gdtilecounts)
		{
			try
			{
				return m_client->HandleChunkFile(filepath, maxopenfilenum, sgytype, tilesizez, tileid_uuid, tileid_gdtilecounts);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				throw e;
			}
		}
		int HandleChunkFileDistribute(string filepath, std::vector<unsigned long long> &tileid_uuid, std::vector<std::vector<int> > &tileid_chunkoffset, int curchunkoffset, \
			std::vector<ServiceHandle> &chunkhandles, std::vector<string> &uploadfiledirs)
		{
			try
			{
				return m_client->HandleChunkFileDistribute(filepath, tileid_uuid, tileid_chunkoffset, curchunkoffset, chunkhandles, uploadfiledirs);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				throw e;
			}
		}
		int IsChunkFileExist(string filepath, std::vector<unsigned long long> &tileid_uuid, std::vector<bool> &tileid_isexist)
		{
			try
			{
				return m_client->IsChunkFileExist(filepath, tileid_uuid, tileid_isexist);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				throw e;
			}
		}
		int HandleChunkFile_Merge(string filepath, int maxopenfilenum, std::vector<unsigned long long> &tileid_uuid, std::vector<int> &tileid_chunkoffset, int curchunkoffset, int linenum, int cdpnum, int samplenum, std::vector<int> &gridpos_cmpcount, \
			int tileSizex, int tileSizey, int tileSizez, int octreeLevel)
		{
			try
			{
				return m_client->HandleChunkFile_Merge(filepath, maxopenfilenum, tileid_uuid, tileid_chunkoffset, curchunkoffset, linenum, cdpnum, samplenum, gridpos_cmpcount, \
					tileSizex, tileSizey, tileSizez, octreeLevel);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				throw e;
			}
		}
		void MergeFile( string sourcefile, string targetfile )
		{
			try
			{
				m_client->MergeFile(sourcefile, targetfile);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void MergeFileAdvanced(std::vector<string> &sourcefiles, std::vector<string> &targetfiles, std::vector<long long> &startfileposes, std::vector<long long> &readlengths)
		{
			try
			{
				m_client->MergeFileAdvanced(sourcefiles, targetfiles, startfileposes, readlengths);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		int UploadFileByChain(std::string filepath, RCF::FileUpload &fileUpload, std::vector<ServiceHandle> &lefts, std::vector<string> &dirs)
		{
			try
			{
				return m_client->UploadFileByChain(filepath, fileUpload, lefts, dirs);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		int DownloadFileByPath(std::string filepath, RCF::FileDownload &fileDownload)
		{
			try
			{
				return m_client->DownloadFileByPath(filepath, fileDownload);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
				throw e;
			}
		}
		/*!
		*
		**/
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
		int ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset)
		{
			try
			{
				return m_client->ReadData(filepath, data, readlength, offset);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		int WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype)
		{
			try
			{
				return m_client->WriteData(filepath, data, datalength, offset, filehandletype);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		int WriteDataByChain(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype, std::vector<ServiceHandle> &lefts,std::vector<string> &paths)
		{
			try
			{
				return m_client->WriteDataByChain(filepath, data, datalength, offset, filehandletype, lefts, paths);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetChunkMissedTiles(std::string filepath, std::vector<unsigned long long> &checkuuids, std::vector<unsigned long long> &misseduuids)
		{
			try
			{
				m_client->GetChunkMissedTiles(filepath, checkuuids, misseduuids);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void RemoveDir(std::string filedir)
		{
			try
			{
				m_client->RemoveDir(filedir);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void RemoveFile(std::string filepath)
		{
			try
			{
				m_client->RemoveFile(filepath);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		/*!
		*
		**/
		void SetFileProgressCallback(RCF::FileProgressCb cb)
		{
			try
			{
				m_client->getClientStub().setFileProgressCallback(cb);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		/*!
		*
		**/
		void SetTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus)
		{
			try
			{
				m_client->SetTaskStatus(gfsname, taskstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetTaskStatus(std::string& gfsname, JobTaskStatus& taskstatus)
		{
			try
			{
				m_client->GetTaskStatus(gfsname, taskstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetChunkStatus(const std::string& gfsname,const std::string& chunkip, long chunkport)
		{
			try
			{
				m_client->SetChunkStatus(gfsname, chunkip, chunkport);
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
				m_client->GetChunkStatus(gfsname, chunkip, chunkport, chunkstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		/*bool Opensgy(int type, string sgyfileName, std::vector<string> &othersgyfileNames, int taskcount, string ip, string username, string password)
		{
			try
			{
				return m_client->Opensgy(type, sgyfileName, othersgyfileNames, taskcount, ip, username, password);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Closesgy()
		{
			try
			{
				m_client->Closesgy();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		bool FormOneTile(std::vector<int> &cmpcounts, std::vector<std::vector<std::vector<int> > > &allfileposes, std::vector<std::vector<int> > &allsgyoffsets, RCFpointInt Position1, RCFpointInt Position2, \
			RCFpointInt tileSize, RCFpointInt surveydata, std::vector<long long> &allnTraceLens, std::vector<int> &allnTypes, \
			long allcmpcount, int threadoffset, std::vector<ServiceHandle> &others, std::vector<string> uploadpaths)
		{
			try
			{
				return m_client->FormOneTile(cmpcounts, allfileposes, allsgyoffsets, Position1, Position2, \
					tileSize, surveydata, allnTraceLens, allnTypes, \
					allcmpcount, threadoffset, others, uploadpaths);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}*/
	};
	template class ANYRCF_CLASS CServiceStub<I_AnyGFSChunk>;
}

#endif