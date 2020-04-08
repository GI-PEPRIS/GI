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
#ifndef __ANYGDE_UTILITY_DATA_CONVERTER__H__
#define __ANYGDE_UTILITY_DATA_CONVERTER__H__

// refer to EXPORT & IMPORT
#include "anygde.h"

// refer to data gate
#include "anygdedatagate.h"

#include "any/base/anytimebasic.h"
using namespace AnyBase;
// 
namespace AnyGDE
{
	// 
	class CAnyGdeDataOctreeGate;
	class CAnyGdeDataSurvey;
	class CAnyGdeDataSet;

	struct ConverterProgressCallback
	{
		int m_cur;
		int m_total;
		string m_status;
	};

	template<typename Signature>
	struct DataConverterProgressCallback : public ConverterProgressCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};

	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataConverter
	{
		class ConvertFromSegyToOctreeTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			ConvertFromSegyToOctreeTask(int taskcount, int index, std::vector<float*> &totalsample, std::vector<int> &cmpcounts, std::vector<std::vector<std::vector<int> > > &allfileposes, \
				std::vector<std::vector<int> > &allsgyoffsets, CAnyGdeDataConverter *dataconverter, \
				CGeoPoint<int> &Position1, CGeoPoint<int> &Position2, CAnyCPUScheduler *scheduler);
			~ConvertFromSegyToOctreeTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			std::vector<float*> &m_totalsample;
			std::vector<int> &m_cmpcounts;
			std::vector<std::vector<std::vector<int> > > &m_allfileposes;
			std::vector<std::vector<int> > &m_allsgyoffsets;
			CAnyGdeDataConverter *m_dataconverter;
			CGeoPoint<int> m_position1;
			CGeoPoint<int> m_position2;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class ConvertFromSegyToOctreeShareTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			ConvertFromSegyToOctreeShareTask(int taskcount, int index, CAnyGdeDataConverter *dataconverter, std::vector<int> &tileidshare, std::vector<std::vector<int> > &cmpcountsshare, \
				std::vector<std::vector<std::vector<std::vector<int> > > > &allfileposesshare, std::vector<std::vector<std::vector<int> > > &allsgyoffsetsshare, \
				std::vector<CGeoPoint<int> > &Position1share, std::vector<CGeoPoint<int> > &Position2share, \
				std::vector<long long> &allnTraceLens, std::vector<int> &allnTypes, \
				std::vector<int> &allcmpcountshare, CAnyCPUScheduler *scheduler);
			~ConvertFromSegyToOctreeShareTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyGdeDataConverter *m_dataconverter;
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
		/*!
		*
		**/
		class GetTraceHeadTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetTraceHeadTask(int startoffset, int taskcount, int index, std::vector<CAnyGdeDataGate::TraceHead> &traceHeads, CAnyGdeDataConverter *dataconverter, CAnyCPUScheduler *scheduler);
			~GetTraceHeadTask();
			void DoExecuteTask();
			int m_startoffset;
			int m_taskcount;
			int m_index;
			std::vector<CAnyGdeDataGate::TraceHead> &m_traceHeads;
			CAnyGdeDataConverter *m_dataconverter;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class GetTraceHeadCharTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetTraceHeadCharTask(int taskcount, int index, int &fetchcount, std::vector<double> &starts, std::vector<double> &ends, std::vector<int> &datatypes, std::vector<std::vector<double> > &values, CAnyGdeDataConverter *dataconverter, CAnyCPUScheduler *scheduler);
			~GetTraceHeadCharTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			int m_fetchcount;
			std::vector<double> m_starts;
			std::vector<double> m_ends;
			std::vector<int> m_datatypes;
			std::vector<std::vector<double> > &m_values;
			CAnyGdeDataConverter *m_dataconverter;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class WriteFileTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			WriteFileTask(int taskcount, int index, CAnyGdeDataConverter *dataconverter, std::vector<float*> &totalsample, std::vector<int> &cmpcounts, int fileoffset, CAnyCPUScheduler *scheduler);
			~WriteFileTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyGdeDataConverter *m_dataconverter;
			std::vector<float*> &m_totalsample;
			std::vector<int> &m_cmpcounts;
			int m_fileoffset;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataConverter(CAnyGdeDataSet *dataset, CAnyGdeDataOctreeGate *octreeGate);

		/*!
		*
		**/
		~CAnyGdeDataConverter();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool Open(int type = CAnyFileBasic::ANY_FILE_READ);
		void Close();

		/*!
		* for segy convert, fill SurveyInfo, HeadInfo, ProfileInfo
		**/
		bool GetSegyInfo(CAnyFunctor *progress);
		
		/*!
		* for segy convert
		**/
		void Set2DSeismicGeometry(const AnySeismic2DGeometry &geometry);

		/*!
		* for segy convert
		**/
		void Set3DSeismicGeometry(const AnySeismic3DGeometry &geometry);

		/*!
		* for segy convert
		**/
		void ModifyLineandCdpByCDPpts();

		/*!
		* for segy convert
		**/
		bool ConvertFromSegyToOctree(CAnyFunctor *progress, bool iseachtileasonefile = false, string gfspara = "", string gfsdir = "", bool issharemode = false, \
			string ip = "", string username = "", string password = "");

		/*!
		* for segy convert
		**/
		void UploadGxfile();

		/*!
		*
		**/
		bool ConvertToSgy(wstring sgyfileName, double mintime, double maxtime, CAnyFunctor *progress, int CAGanglenum = 0, int startline = -1, int endline = -1, int startcdp = -1, int endcdp = -1, bool setnan = false, bool setzero = false);
		bool ConvertToSgy_gfsfast(wstring sgyfileName, CAnyFunctor *progress);

	public:
		/*!
		* for segy convert
		**/
		bool IsSEGYFile(CAnyFunctor *progress);
		void GetAllTraceHeads(std::vector<CAnyGdeDataGate::TraceHead> &traceHeads, int startoffset, int count);
		void GetTraceHeadChars(int fetchcount, std::vector<double> starts, std::vector<double> ends, std::vector<int> datatypes, std::vector<std::vector<double> > &values);
		void DoGetSurveyInfo(CAnyFunctor *progress, int headgetsize = 10000);
		float* ReadTraceData(int nOrder, int threadoffset, int start, int end, int interval, std::vector<std::vector<int> > &fileposes, std::vector<int> &sgyoffsets);
		void GetTraceHead(char *pBuf, CAnyGdeDataGate::TraceHead& traceHead);
		void ReverseBytes(char *bytes, short nSize);
		void IBMtoIEEE(char *bytes);

		// refector code
		void OpenSEGYFile(int &tileid, int &fileid, int &tilecount);
		void OpenOctreeGFS(bool iseachtileasonefile, const string &gfspara, const string &gfsdir, int tilecount);
		bool CreateOctreeGFS(const string &gfspara, const string &gfsdir, string &gdfilepath, string &gdfiledir, string &gdfilename, int tilecount, std::vector<void*> &tmphandles);
		void UpdateGFSStatus(int tilecount);
		long GetTileCMPCount(std::vector<int> &morton, 	std::vector<int> &cmpcounts, std::vector<std::vector<int> > &othergridpostoadd, std::vector<float*> &totalsample, \
			CGeoPoint<int> &Position1, CGeoPoint<int> &Position2, std::vector<std::vector<std::vector<int> > > &allfileposes, std::vector<std::vector<int> > &allsgyoffsets);
		int OpenTileFile(bool iseachtileasonefile, int &fileid, int tileid, int allcmpcount, std::vector<long long> &gdfileoffset, bool issharemode);
		void WriteTileFileWithTaskThread(std::vector<int> &cmpcounts, int fileoffset, std::vector<long long> &gdfileoffset, std::vector<float*> &totalsample, long allcmpcount);
		void UploadTileGFSWithLightThread(int tileid, int &uploadedfile, std::vector<int> &uploadfailedtileids);
		void UpdateOctreeGateSurvey(std::vector<std::vector<int> > &othergridpostoadd);
		void CloseOctreeGFS(bool iseachtileasonefile,std::vector<long long> &gdfileoffset);

	public:
		// data set
		CAnyGdeDataSet *m_dataset;

		// octree gate
		CAnyGdeDataOctreeGate *m_octreeGate;
		std::vector<CAnyGdeDataOctreeGate *> m_otheroctreeGates;//for convert whole sgylayer to one octree

		// configure parameters
		int m_taskcount;

		// .sgy file
		wstring m_sgyfileName;
		std::vector<void *> m_sgyHandles;
		std::vector<std::vector<void *> > m_sgyHandles_cutforbig;
		std::vector<long long> m_filesize_cutforbig;
		HugeArray<char> m_sgyha_cutforbig;
		std::vector<wstring> m_othersgyfileNames;//for convert whole sgylayer to one octree
		std::vector<std::vector<void *> > m_othersgyHandles;//for convert whole sgylayer to one octree
		const CAnyFileBasic &m_fileBasic;

		// for distribute
		void* m_gfsclient;
		// progress
		ConverterProgressCallback *m_progresscb;

		double m_seektime;
		double m_readtime;
		double m_writetime;
		double m_grid2filetime;
		CAnyTimeBasic::TimeReport m_timereportstart;
		CAnyTimeBasic::TimeReport m_timereportend;
		CAnyTimeBasic m_timeBasic;
		int m_cuttype;
		long long m_cutcachesize;
	};
}

#endif
