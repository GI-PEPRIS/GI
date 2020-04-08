/*!
 * The AnyGDE of PetroCOVERY Solution is a collection of native C++ classes that implement 
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
#ifndef __ANYGDE_DATA_SEGYFILE_H__
#define __ANYGDE_DATA_SEGYFILE_H__

// refer to export/import macro
#include "anygde.h"

// refer to its parent
#include "anygdedatagate.h"
#include "anygdedatatrace.h"
#include "anygdedatalinesurvey.h"
#include "anygdedatagridsurvey.h"
#include "anygdedatapolysurvey.h"
#include "calculatorcubeiterator.h"


// namespace, geophysics
namespace AnyGDE
{
	struct ProgressCallback
	{
		int m_cur;
		int m_total;
		string m_status;
	};

	template<typename Signature>
	struct SgyProgressCallback : public ProgressCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};

	/*!
	*
	**/
	class ANYGDE_CLASS CAnySegyFile : public CAnyGdeDataGate
	{
		/*!
		*
		**/
		class SetBigFileCutTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			SetBigFileCutTask(int index, CAnySegyFile *parent, CAnyCPUScheduler *scheduler);
			~SetBigFileCutTask();
			void DoExecuteTask();
			int m_index;
			CAnySegyFile *m_parent;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class GetTraceRecordTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetTraceRecordTask(int taskcount, int index, CAnySegyFile *parent, std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, std::vector<CGeoPoint<double> > &coords, CAnyCPUScheduler *scheduler);
			~GetTraceRecordTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySegyFile *m_parent;
			std::vector<long> m_sequenceOrders;
			std::vector<double> m_minTimes;
			std::vector<double> m_maxTimes;
			std::vector<CGeoPoint<double> > m_coords;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class GetTraceHeadTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetTraceHeadTask(int startoffset, int taskcount, int index, std::vector<TraceHead> &traceHeads, CAnySegyFile *parent, CAnyCPUScheduler *scheduler);
			~GetTraceHeadTask();
			void DoExecuteTask();
			int m_startoffset;
			int m_taskcount;
			int m_index;
			std::vector<TraceHead> &m_traceHeads;
			CAnySegyFile *m_parent;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class GetTraceHeadCharTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetTraceHeadCharTask(int taskcount, int index, int &fetchcount, std::vector<double> &starts, std::vector<double> &ends, std::vector<int> &datatypes, std::vector<std::vector<double> > &values, CAnySegyFile *parent, CAnyCPUScheduler *scheduler);
			~GetTraceHeadCharTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			int m_fetchcount;
			std::vector<double> m_starts;
			std::vector<double> m_ends;
			std::vector<int> m_datatypes;
			std::vector<std::vector<double> > &m_values;
			CAnySegyFile *m_parent;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class CommitTraceTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			CommitTraceTask(int taskcount, int index, CAnySegyFile *parent, std::vector<CAnyGdeDataTrace*> &traces, SurveyInfo &survey, CAnyFunctor *progress, std::vector<std::vector<double> > &metas, CAnyCPUScheduler *scheduler);
			~CommitTraceTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySegyFile *m_parent;
			std::vector<CAnyGdeDataTrace*> m_traces;
			SurveyInfo &m_survey;
			CAnyFunctor *m_progress;
			std::vector<std::vector<double> > m_metas;
			CAnyCPUScheduler *m_scheduler;
		};

		/*!
		*
		**/
		class FormNewSegyFileCAGTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			FormNewSegyFileCAGTask(int taskcount, int index, CAnySegyFile *parent, long long startgridposcount, wstring sgyFileName, double mintime, double maxtime, int CAGanglenum, int startline, int endline, int startcdp, int endcdp, bool setnan, CAnyCPUScheduler *scheduler);
			~FormNewSegyFileCAGTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnySegyFile *m_parent;
			long long m_startgridposcount;
			wstring m_sgyFileName;
			double m_mintime;
			double m_maxtime;
			int m_CAGanglenum;
			int m_startline;
			int m_endline;
			int m_startcdp;
			int m_endcdp;
			bool m_setnan;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySegyFile(const wstring &strFileName);
		
		/*!
		*
		**/
		~CAnySegyFile();

	public:
		//
		// generic interface
		//
		/*!
		*
		**/
		bool Open(int type = CAnyFileBasic::ANY_FILE_READ, int bufsize = -1);

		/*!
		*
		**/
		void Close();

		/*!
		*
		**/
		bool UpdateTrace(std::vector<CAnyGdeDataTrace*> &traces, SurveyInfo &survey, CAnyFunctor *progress);

		/*!
		*
		**/
		bool CommitTrace(std::vector<CAnyGdeDataTrace*> &traces, SurveyInfo &survey, CAnyFunctor *progress, std::vector<std::vector<double> > metas);

		/*!
		*
		**/
		long GetCalculatorCubeCount(CalculatorCube::DataCubeSize &cubesize, CAnyGeologicalCubeFeature::SampleVector &horizon);
		
		/*!
		*
		**/
		bool GetCalculatorCube(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CalculatorCube &cube, SurveyInfo &survey, bool cachemode);
								
		/*!
		*
		**/
		bool GetCalculatorCubeTraces(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs, \
			std::vector<CAnyGdeDataTrace*> &traces, CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, SurveyInfo &survey);

		/*!
		*
		**/
		bool GetCalculatorCubeLineandCdps(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, SurveyInfo &survey, std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs);

		/*!
		*
		**/
		bool IsLineandCdpsvalid(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs);
				
		/*!
		*
		**/
		int GetCalculatorCubeSequenceFromSurvey(int lineno, int cdpno);

		/*!
		*
		**/
		bool GetSurrondingTraces(long sequenceorder, \
			CalculatorCube::DataCubeSize &cubesize, \
			std::vector<CAnyGdeDataTrace*> &supertraces, SurveyInfo &survey);

		/*!
		*
		**/
		bool GetSurrondingTracesCache(CalculatorCube &cube, \
			CalculatorCube::DataCubeSize &cubesize, \
			SurveyInfo &survey);

		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, double minTime, double maxTime, std::vector<CAnyGdeDataGate::TraceRecord*> &records, CAnyFunctor *progress, std::vector<CGeoPoint<double> > &coords);
		
		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, std::vector<CAnyGdeDataGate::TraceRecord*> &records, CAnyFunctor *progress, std::vector<CGeoPoint<double> > &coords);

		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, SurveyInfo &survey);

		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, std::vector<std::vector<float*> > &traces, CAnyFunctor *progress, SurveyInfo &survey, bool ispremode, std::vector<std::vector<int> > &gridpos_fileposes);
		
		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, SurveyInfo &survey);

		//
		// reader, 存取地震数据接口 
		//
		/*!
		*
		**/
		bool IsSEGYFile(bool getsurveyinfo = true, CAnyFunctor *progress = NULL, int headgetsize = 10000, int bufsize = -1);
		
		/*!
		*
		**/
		void SetBigFileCut(long long bigfilecutsize = -1);
		
		/*!
		*
		**/
		void ClearBigFileCut();

		/*!
		*
		**/
		void GetAllTraceHeads(std::vector<TraceHead> &traceHeads, int startoffset, int count);

		/*!
		*
		**/
		void GetTraceHeadChars(int fetchcount, std::vector<double> starts, std::vector<double> ends, std::vector<int> datatypes, std::vector<std::vector<double> > &values);

		/*!
		*
		**/
		wstring GetFileName();

		/*!
		*
		**/
		const ProfileInfo &GetProfileInfo();

		/*!
		*
		**/
		void UpdateProfileInfo(const ProfileInfo &info);

		/*!
		*
		**/
		int GetTraceNum() const;

		/*!
		*
		**/
		int GetTracePoint() const;

		/*!
		*
		**/
		int GetType() const;

		/*!
		*
		**/
		float *ReadTraceData(int nOrder, int threadoffset, int start = -1, int end = -1, bool ispremode = true);
		
		/*!
		*
		**/
		bool DoReadTraceData(char *&traceData, int threadoffset, int start, int readnum, int filepose);

		/*!
		*
		**/
		bool ReadTraceMetaData(int nOrder, std::vector<double> &meta);

		/*!
		*
		**/
		double GetSampleInterval()
		{
			return m_headInfo.m_nInterval;
		}

		//
		// writer
		//
		/*!
		* 
		**/
		void SetFileName(wstring &strFileName);

		/*!
		*
		**/
		void SetTraceNum(int nTraceNum);
		
		/*!
		*
		**/
		void SetTracePoint(int nPts);
		
		/*!
		*
		**/
		void SetType(int nType);

		//
		// utility
		//
		/*!
		*
		**/
		int Time2Index(double time, double startTime, float interval);
				
        /*!
        *
        */
        void SaveToDB(int datasetid, string linename = "", bool saveblobinDB = true);
				
        /*!
        *
        */
        void LoadFromDB(int gateid);

		/*!
        *
        */
        void LoadTraceHeadFromDB(int gateid, int order, TraceHead& traceHead);
		
		/*!
        *
        */
		bool FormNewSegyFile(wstring sgyFileName, double mintime, double maxtime, CAnyFunctor *progress, int CAGanglenum = 0, int startline = -1, int endline = -1, int startcdp = -1, int endcdp = -1, bool setnan = true, bool setzero = false); 
		bool TBTest(wstring sgyFileName, int linecount, int cdpcount, int traceptcount);
	public:
		//
		//	存取地震道头数据
		//
		/*!
		*
		**/
		void GetTraceHead(char* pBuf, TraceHead& traceHead);

		//
		//数据类型转换
		//
		/*!
		*
		**/
		void IBMtoIEEE(char *bytes);

		/*!
		*
		**/
		void IEEEtoIBM(char *bytes);
		
		/*!
		*
		**/
		void ReverseBytes(char *bytes, short nSize);

		/*!
		*
		**/
		void DoGetSurveyInfo(CAnyFunctor *progress = NULL, int headgetsize = 10000);

		/*!
		*
		**/
		static bool CompareTraceSequenceOrder(const CAnyGdeDataGate::TraceRecord *first, const CAnyGdeDataGate::TraceRecord *second);
		
		/*!
		*
		**/
		static bool CompareTraceHitsUsage(const CAnyGdeDataGate::TraceRecord *first, const CAnyGdeDataGate::TraceRecord *second);
				
		/*!
		*
		**/
		bool ClearCache(std::vector<long> &savedsequenceOrders);
		
		/*!
		*
		**/
		void SetFitCachelimit();
		
		/*!
		*
		**/
		void TrackPtEliis(std::vector<std::vector<float> > &datas, std::vector<std::vector<CGeoPoint<int> > > &horizonlines, int cellsize, std::vector<std::vector<CGeoPoint<int> > > &tracklines);
		void DoSegmentHorizonlines(std::vector<std::vector<CGeoPoint<int> > > &horizonlines, std::vector<std::vector<CGeoPoint<int> > > &horizonlines_segment);
		void GetSegmentlines(std::vector<float> &curtrace, std::vector<float> &nexttrace, int cellsize, std::vector<CGeoPoint<int> > &trackline_segment, std::vector<CGeoPoint<int> > &lasttrackline_segment, std::vector<CGeoPoint<int> > &horizonline_segment);
		void CombineSegmentlines(std::vector<std::vector<CGeoPoint<int> > > &tracklines_segment, int datasize, int cellsize, std::vector<std::vector<CGeoPoint<int> > > &tracklines);
		double GetSQ(std::vector<std::vector<CGeoPoint<int> > > &tracklines, int cellsize);
		static bool ComparePointxy(const CGeoPoint<int> &a, const CGeoPoint<int> &b);
	public:
		// segy file
		wstring m_strFileName;
		std::vector<void *> m_fileHandles;
		std::vector<std::vector<void *> > m_sgyHandles_cutforbig;
		std::vector<long long> m_filesize_cutforbig;
		const CAnyFileBasic &m_fileBasic;
		int m_taskcount;
		int m_iolib_fortraceheadscan;

		// source is database
		bool m_isfromDB;

		// id of this gate
		int m_gateid;

		// trace cache
		std::vector<TraceRecord*> m_cache;
		long m_cachelimits;

		// results for multiline class access
		std::vector<CAnyGdeDataGate::TraceRecord*> m_recordsforMT;
		std::vector<int> m_tracetocacheforMT;

		// progress
		ProgressCallback *m_progresscb;
	};
}
#endif




