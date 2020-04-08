/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYRCF_GFS_CHUNK_RUNNER_H__
#define __ANYRCF_GFS_CHUNK_RUNNER_H__

// refer to EXPORT & IMPORT
#include "anyrcf.h"
#include "anyclientimpl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;
//
namespace AnyRCF
{
	/*!
	* issues control (metadata) requests to master server
	* issues data requests directly to chunk servers
	* whether or not cache metadata
	**/
	class ANYRCF_CLASS CAnyGFSChunkRunner
	{
	public:
		/*!
		*
		**/
		struct LocalChunkFile
		{
			long m_tileidx;
			long m_chunkindex; // 
			unsigned long long m_chunkuuid;
			string m_chunkfile;
			short m_hits;
			bool m_isused;
			long m_curorder;		// 

			LocalChunkFile() : m_tileidx(0), m_chunkindex(0), m_chunkuuid(0), m_chunkfile(""), m_hits(0), m_isused(false), m_curorder(0)
			{
			}

			/*!
			*
			**/
			string GetChunkFile()
			{
				char buf[64] = {};
				::sprintf(buf, "%llu.afs", m_chunkuuid);
				m_chunkfile = buf;

				return m_chunkfile;
			}
		};
		typedef std::vector<LocalChunkFile *> LocalChunkFileVector;
		typedef std::vector<CAnyClientImpl *> ChunkClientVector;
		typedef std::map<unsigned long long, ChunkClientVector> ChunkClientMap;

		struct RunnerAdvancedSetting
		{
			bool m_isNamedPipe;
			bool m_isDasyChain;
			bool m_isFileBased;
			long m_bytesSentOnce;

			RunnerAdvancedSetting() : m_isNamedPipe(false), m_isDasyChain(false), m_isFileBased(true), m_bytesSentOnce(512 * 1024)
			{
			}
			RunnerAdvancedSetting(const RunnerAdvancedSetting &other)
			{
				*this = other;
			}
			const RunnerAdvancedSetting &operator=(const RunnerAdvancedSetting &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_isNamedPipe = other.m_isNamedPipe;
				m_isDasyChain = other.m_isDasyChain;
				m_isFileBased = other.m_isFileBased;
				m_bytesSentOnce = other.m_bytesSentOnce;

				return *this;
			}
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGFSChunkRunner();
		virtual ~CAnyGFSChunkRunner();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool InitNetwork(const ServiceHandle &maserhandle, const ServiceHandle &eventhandle);
		void Release();
		//
		//
		//
		/*!
		*
		**/
		void Lookup(const string &gfsdir, MasterRecordVector &records,short type = AnyRCF::FCT_Seismic);
		void Open(const string &filename, short type = AnyRCF::FCT_Seismic);
		bool Download(long tileidx, bool ispartmode = false);
		bool GetTileDataNoDownload(long tileidx, std::vector<long long> &seekoffsets, std::vector<int> &readlengths, std::vector<std::vector<char> > &datas);
		bool Upload(long tileidx, bool istoallchunk = false, int partcount = 1);
		bool UploadMulti(std::vector<int> &tileidxs, std::vector<long> &failedtileidxs, bool istoallchunk = false);
		bool Opensgy(int type, string sgyfileName, std::vector<string> &othersgyfileNames, int taskcount, string ip, string username, string password);
		void Closesgy();
		bool FormOneTile(long tileidx, bool istoallchunk, std::vector<int> &cmpcounts, std::vector<std::vector<std::vector<int> > > &allfileposes, std::vector<std::vector<int> > &allsgyoffsets, \
			RCFpointInt Position1, RCFpointInt Position2, RCFpointInt tileSize, RCFpointInt surveydata, std::vector<long long> &allnTraceLens, std::vector<int> &allnTypes, \
			long allcmpcount, int threadoffset);
		bool FormTiles(std::vector<int> &tileidshare, bool istoallchunk, std::vector<std::vector<int> > &cmpcountsshare, std::vector<std::vector<std::vector<std::vector<int> > > > &allfileposesshare, std::vector<std::vector<std::vector<int> > > &allsgyoffsetsshare, \
			std::vector<RCFpointInt> &Position1share, std::vector<RCFpointInt> &Position2share, RCFpointInt tileSize, RCFpointInt surveydata, std::vector<long long> &allnTraceLens, std::vector<int> &allnTypes, \
			std::vector<int> &allcmpcountshare, std::vector<int> &threadoffsets);
		bool UploadByPath(const string &filename);
		void UploadEnd();
		void Close(const string &filename);

		void Delete(const string &gfsName);
		void Snapshot(const string &gfsName); 
		void Append();

		void SetUploadStatus(const std::string& gfsname, GFSUploadStatus& uploadstatus);
		void GetUploadStatus(const std::string& gfsname, GFSUploadStatus& uploadstatus);
		void SetDownloadStatus(const std::string& gfsname, GFSDownloadStatus& downloadstatus);
		void GetDownloadStatus(const std::string& gfsname, GFSDownloadStatus& downloadstatus);

		//
		//
		//
		/*!
		*
		**/
		void AllocateGdeChunk(const string &filename, long chunknumber);
		bool GetGdeChunk(const string &filename);
		string GetGdeChunkFileName(long tileidx, long chunkorder);
		string GetGdeChunkFileName(long tileidx);
		void SwitchGdeChunkFile(std::vector<long> &tileidxes);
		void CleanGdeChunkFile(std::vector<int> &restoredtileids);
		std::vector<std::string> GetAllFilenames();
		void GetChunkMissedTiles(std::vector<std::string> &missedchunks, std::vector<std::vector<long> > &missedtileids);

	public:
		//
		//
		//
		/*!
		*
		**/
		void OnGdeCallback(const string &topic);
		bool FindLocalChunk(long tileidx, LocalChunkFile &chunk);
		bool IsChunkExist(const string &localchunk);
		void RemoveChunkFile(const string &localchunk);

		void GetFileLength(std::string filepath, long long &filelength);
		void ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset, void* &fileHandle);
		void WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype, void* &fileHandle);
		void DoCreateDir(string filepath);

		void DoDirectSend(const string &localchunk, std::vector<string> &uploadfilepaths, std::vector<string> &uploadfiledirs, std::vector<void*> &curs, int partcount = 1);
		void DoChainSend(const string &localchunk, std::vector<string> &uploadfilepaths, std::vector<string> &uploadfiledirs, std::vector<void*> &curs);

	public:
		static bool CompreChunkTileIdx(const LocalChunkFile *first, const LocalChunkFile *second)
		{
			return first->m_tileidx < second->m_tileidx;
		}
		static bool CompreChunkHits(const LocalChunkFile *first, const LocalChunkFile *second)
		{
			return first->m_hits < second->m_hits;
		}

	public:
		// distributed file name including dir
		string m_gfsLocalPath;
		string m_gfsName;
		long m_gfsHandle;

		// the global unique id for one data chunk
		std::vector<unsigned long long> m_chunkuuids;
		std::vector<unsigned long long> m_validchunkuuidsforfirstupload;
		// in frequency
		LocalChunkFileVector m_locals;
		// file number or total size
		long m_locallimits; 

		// master stub
		CAnyClientImpl *m_masterclient;

		// chunk stubs
		ChunkClientVector m_chunkclients;
		std::vector<std::vector<CAnyClientImpl *> > m_chunkclientsmultithread;
		std::vector<ServiceHandle> m_chunkhandles;
		std::vector<int> m_chunkhandlesinvalidtimes;

		// message channel
		CAnyClientImpl *m_eventclient;
		//
		RunnerAdvancedSetting m_setting;
	};
}
#endif
