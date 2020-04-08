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
#ifndef __ANYGDE_RCF_GFS_CLIENT_H__
#define __ANYGDE_RCF_GFS_CLIENT_H__

// refer to EXPORT & IMPORT
#include "anygde.h"
#include "anygdedataconverter.h"

#include "any/gfs/anygfschunkrunner.h"
using namespace AnyRCF;

//
namespace AnyGDE
{
	/*!
	* issues control (metadata) requests to master server
	* issues data requests directly to chunk servers
	* whether or not cache metadata
	**/
	class ANYGDE_CLASS CAnyGdeGFSClient : public CAnyGFSChunkRunner, public CAnyGdeDataConverter
	{
		//
		class UploadGFSThread : public JTCThread
		{
		public:
			UploadGFSThread(CAnyGdeGFSClient *parent, const char* name) : m_parent(parent), m_isfinished(false), JTCThread(name)
			{
			}
			void run();

		public:
			CAnyGdeGFSClient *m_parent;
			std::map<int, bool> m_tileid_upload;
			bool m_isfinished;
		};

	protected:
		//
		struct OctreeTileSurvey
		{
			long m_tileidx;
			std::vector<int> m_mortoncodes;
			std::vector<int> m_cmpcounts;
			CGeoPoint<int> m_position1;
			CGeoPoint<int> m_position2;
			std::vector<float*> m_totalsample;
			std::vector<std::vector<std::vector<int> > > m_allfileposes;
			std::vector<std::vector<int> > m_allsgyoffsets;

		};
		typedef std::vector<OctreeTileSurvey*> TileSurveyVector;

		//
		struct SEGYReadThreadParameter
		{
			int m_fromindex;
			OctreeTileSurvey *m_tilesurvey;

			SEGYReadThreadParameter(int fromindex, OctreeTileSurvey *survey) : \
				m_fromindex(fromindex), m_tilesurvey(survey)
			{
			}
		};

		//
		struct TileWriteThreadParameter
		{
			int m_fromindex;
			int m_fileoffset;
			const OctreeTileSurvey *m_tilesurvey;

			TileWriteThreadParameter(int fromindex, int fileoffset, const OctreeTileSurvey *tilesurvey) : m_fromindex(fromindex), m_fileoffset(fileoffset), m_tilesurvey(tilesurvey)
			{
			}
		};

		/*!
		*
		**/
		class ConvertFromSegyToOctreeRemoteTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			ConvertFromSegyToOctreeRemoteTask(int taskcount, int index, CAnyGdeGFSClient *gfsclient, std::vector<int> &tileidshare, std::vector<std::vector<int> > &cmpcountsshare, \
				std::vector<std::vector<std::vector<std::vector<int> > > > &allfileposesshare, std::vector<std::vector<std::vector<int> > > &allsgyoffsetsshare, \
				std::vector<CGeoPoint<int> > &Position1share, std::vector<CGeoPoint<int> > &Position2share, \
				std::vector<long long> &allnTraceLens, std::vector<int> &allnTypes, \
				std::vector<int> &allcmpcountshare, CAnyCPUScheduler *scheduler);
			~ConvertFromSegyToOctreeRemoteTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyGdeGFSClient *m_gfsclient;
			std::vector<long long> &m_allnTraceLens;
			std::vector<int> &m_allnTypes;
			std::vector<int> &m_tileidshare;
			std::vector<std::vector<int> > &m_cmpcountsshare;
			std::vector<std::vector<std::vector<std::vector<int> > > > &m_allfileposesshare;
			std::vector<std::vector<std::vector<int> > > &m_allsgyoffsetsshare;
			std::vector<CGeoPoint<int> > &m_Position1share;
			std::vector<CGeoPoint<int> > &m_Position2share;
			std::vector<int> &m_allcmpcountshare;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeGFSClient(CAnyGdeDataSet *dataset, CAnyGdeDataOctreeGate *octreeGate);
		~CAnyGdeGFSClient();

	public:
		//
		//
		//
		void UploadGxfile();
		void UploadGFSSlice(const string &gfspara, const string &gfsdir, std::vector<long> &sequenceOrders, std::vector<double> &midTimes, std::vector<CGeoPoint<double> > &pts);
		short UploadGFSDirect(CAnyFunctor *progress, bool isuploadforgfs, const string &gfspara, const string &gfsdir, bool isuseoriginsurveyinfo, CAnyGdeDataGate::SurveyInfo &originsurveyInfo, \
			int chunksperbatch, int tilescutlimit, bool iswritefile, int bufsize, long long bigfilecutsize, bool isHA, int cuttype, long long cutcachesize, int chunkreplicas); // one by one
		short UploadGFSBatch(CAnyFunctor *progress, bool isuploadforgfs, const string &gfspara, const string &gfsdir, bool isuseoriginsurveyinfo, CAnyGdeDataGate::SurveyInfo &originsurveyInfo); // in batch
		short UploadGFSRemote(CAnyFunctor *progress, bool isuploadforgfs, const string &gfspara, const string &gfsdir, bool isuseoriginsurveyinfo, CAnyGdeDataGate::SurveyInfo &originsurveyInfo, string ip = "", string username = "", string password = ""); // remote
		void rcfreactorfunction(int from, int to, std::vector<std::vector<void*> > &datas, std::vector<std::vector<int> > &datasizes, bool iswritefile);
		void HandleChunkFile_Merge(std::vector<string> &filenamesforchunk, std::vector<int> &tileid_chunkoffset);
		void UploadFileByPath(string localfilepath);
		void DownloadFileByPath(string localfilepath);
		void CollectGFSRunningStatus(const string &msg);
	public:
		// local preparation
		bool DoInitNetwork(const string &gfspara, const string &gfsdir);
		bool DoPrepareOctreeTileBasic(int &tilefromidx, int &tilecount);
		bool DoOpenSEGYStdFile(unsigned int mode = CAnyFileBasic::ANY_FILE_READ, int bufsize = -1, long long bigfilecutsize = -1, bool isHA = false);

		// remote preparation
		void DoResetOctreeGate(std::vector<void*> &tilehandles, string &gdfiledir, string &gdfilename);
		void DoOpenOctreeTileLocalFile(int tilecount, const std::vector<void*> &tilehandles, const string gdfiledir);
		bool DoOpenOctreeTileGFSFile(int tilecount, const std::vector<void*> &tilehandles, const string &gfsdir, const string &gdfiledir, const string &gdfilename, int chunkreplicas = 1);

		//
		void DoCollectGFSInitialStatus();
		void DoCollectGFSRunningStatus(const string &msg);
		void DoCollectGFSStopStatus();

		//
		long DoGetOctreeTileSurvey(OctreeTileSurvey *tilesurvey, bool isuseoriginsurveyinfo, CAnyGdeDataGate::SurveyInfo &originsurveyInfo);
		void DoPrepareSetup(int tileidx, int tilecount);

		// thread(s)
		void DoReadSEGYThread(const SEGYReadThreadParameter &parameter);
		int DoCreateOctreeTileFile(bool isremote, bool iswritefile = true);
		void DoWriteOctreeTileFile(int fileoffset, const OctreeTileSurvey *tilesurvey, bool iswritefile = true);		
		void DoWriteOctreeTileFileThread(const TileWriteThreadParameter &parameter);

		//
		void DoUploadOctreeTileGFS(int tileidx);
		void DoUploadOctreeTileGFSBatch(std::vector<int> &validtileidxs);
		void DoUploadOctreeTileGFSFailed();
		void DoUpdateOctreeGateSurvey();
		void DoUpdateOctreeGateData();
		
	public:
		//
		int m_fileidx;
		int m_tileidx;
		int m_tilecount;
		long m_tilecmpcount;
		bool m_iseachtileasonefile;
		bool m_isuploadforgfs;

		//
		int m_functorshowinterval;
		int m_lasttileidx;
		std::vector<std::vector<int> > m_othergridpostoadd;
		std::vector<long long> m_gdfileoffset;

		//
		int m_uploadedfile;
		std::vector<int> m_uploadfailedtileids;
		std::vector<int> m_validtileidxsforbatch;
		bool m_isbatchmainfuncfinished;
		bool m_isbatchthreadfinished;
	};
}
#endif
