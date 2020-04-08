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
#ifndef __ANYGDE_LDM_DATA_OCTREE_GATE_H__
#define __ANYGDE_LDM_DATA_OCTREE_GATE_H__

// refer to EXPORT & IMPORT
#include "anygde.h"

// refer to its parent
#include "anygdedatagate.h"
#include "anygdedatasurvey.h"
#include "anygdedatalinesurvey.h"
#include "anygdedatagridsurvey.h"
#include "anygdedatapolysurvey.h"
#include "calculatorcubeiterator.h"

//
namespace AnyGDE
{
	// forward class
	class CAnyGdeDataOctree;
	class CAnyGdeDataTrace;

	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataOctreeGate : public CAnyGdeDataGate
	{
		/*!
		*
		**/
		class GetDataTraceTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetDataTraceTask(int taskcount, int index, CAnyGdeDataOctreeGate *parent, std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, CAnyGdeDataSurvey *survey, CAnyCPUScheduler *scheduler);
			~GetDataTraceTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyGdeDataOctreeGate *m_parent;
			std::vector<long> m_sequenceOrders;
			std::vector<double> m_minTimes;
			std::vector<double> m_maxTimes;
			CAnyGdeDataSurvey *m_survey;
			CAnyCPUScheduler *m_scheduler;
		};
		class GetDataTraceTask1 : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetDataTraceTask1(int taskcount, int index, CAnyGdeDataOctreeGate *parent, std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, std::vector<std::vector<float*> > &traces, CAnyGdeDataSurvey *survey, bool ispremode, std::vector<std::vector<int> > &gridpos_fileposes, CAnyCPUScheduler *scheduler);
			~GetDataTraceTask1();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyGdeDataOctreeGate *m_parent;
			std::vector<long> &m_sequenceOrders;
			std::vector<double> &m_minTimes;
			std::vector<double> &m_maxTimes;
			std::vector<std::vector<float*> > &m_traces;
			CAnyGdeDataSurvey *m_survey;
			bool m_ispremode;
			std::vector<std::vector<int> > &m_gridpos_fileposes;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class CommitTraceTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			CommitTraceTask(int taskcount, int index, CAnyGdeDataOctreeGate *parent, std::vector<CAnyGdeDataTrace*> &traces, CAnyGdeDataSurvey *survey, CAnyFunctor *progress, std::vector<std::vector<double> > &metas, CAnyCPUScheduler *scheduler);
			~CommitTraceTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyGdeDataOctreeGate *m_parent;
			std::vector<CAnyGdeDataTrace*> m_traces;
			CAnyGdeDataSurvey *m_survey;
			CAnyFunctor *m_progress;
			std::vector<std::vector<double> > m_metas;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		/*!
		*
		**/
		CAnyGdeDataOctreeGate(CAnyGdeDataOctree &octree);

		/*!
		*
		**/
		virtual ~CAnyGdeDataOctreeGate();

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
		bool UpdateTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyGdeDataSurvey &survey, CAnyFunctor *progress);

		/*!
		*
		**/
		bool CommitTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyGdeDataSurvey &survey, CAnyFunctor *progress, std::vector<std::vector<double> > metas);

		//
		//
		//
		/*!
		*
		**/
		long GetCalculatorCubeCount(CalculatorCube::DataCubeSize &cubesize, CAnyGeologicalCubeFeature::SampleVector &horizon);
		
		/*!
		*
		**/
		bool GetCalculatorCube(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CalculatorCube &cube, CAnyGdeDataSurvey &survey, bool cachemode);
									
		/*!
		*
		**/
		bool GetCalculatorCubeTraces(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs, \
			std::vector<CAnyGdeDataTrace*> &traces, CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CAnyGdeDataSurvey &survey);

		/*!
		*
		**/
		bool GetCalculatorCubeLineandCdps(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CAnyGdeDataSurvey &survey, std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs);
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
			std::vector<CAnyGdeDataTrace*> &supertraces, CAnyGdeDataSurvey &survey);

		/*!
		*
		**/
		bool GetSurrondingTracesCache(CalculatorCube &cube, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGdeDataSurvey &survey);

		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, CAnyGdeDataSurvey &survey);
		
		/*!
		*
		**/
		bool GetDataTrace_gfsfast(std::vector<long> &sequenceOrders, std::vector<std::vector<float*> > &traces, std::vector<std::vector<int> > &gridpos_fileposes, std::vector<int> &tileid_chunkoffset, \
			std::vector<string> &filenamesforchunk, std::vector<void*> &filehandlesforchunk, std::vector<int> &curpartforchunk, std::vector<long long> &curlengthforchunk, std::vector<long long> &alllengthforchunk);

		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, std::vector<std::vector<float*> > &traces, CAnyFunctor *progress, CAnyGdeDataSurvey &survey, bool ispremode, std::vector<std::vector<int> > &gridpos_fileposes);
		
		/*!
		*
		**/
		bool GetDataTraceSingle(long sequenceOrder, double minTime, double maxTime, std::vector<float*> &traces, CAnyGdeDataSurvey &survey, int threadoffset, bool ispremode, std::vector<std::vector<int> > &gridpos_fileposes, bool isdownload = true);
		
		/*!
		*
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, CAnyGdeDataSurvey &survey);
		
		/*!
		*
		**/
		bool GetMapReduceSlice(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, int meanorrms, std::vector<CGeoPoint<double> > &pts, CAnyFunctor *progress, CAnyGdeDataSurvey &survey, string outgfsname = "");
		
		/*!
		*
		**/
		bool GetMapReduceTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, std::vector<std::vector<double> > &traces, bool ispremode, CAnyFunctor *progress, CAnyGdeDataSurvey &survey);
					
		/*!
		*
		**/
		bool GetMapReduceTriangleFilter(void *jobparameter, string outgfsname = "");
		bool GetMapReduceInstantAttribute(void *jobparameter, string outgfsname = "");
		bool GetMapReduceDipAzimuth(void *jobparameter, string outgfsname = "");
		bool GetMapReduceAlphaFilter(void *jobparameter, string outgfsname = "");
		bool GetMapReduceIrregular(void *jobparameter, string outgfsname = "");
		bool GetMapReduceEllipse(void *jobparameter, string outgfsname = "");
		bool GetMapReduceThreeBayes(void *jobparameter, string outgfsname = "");
		bool GetMapReduceBasicTrack(void *jobparameter, string outgfsname = "");
		bool GetMapReduceRockPhysics(void *jobparameter, string outgfsname = "");
		bool GetMapReduceBrick(void *jobparameter, string outgfsname = "");
		bool GetMapReduceConherency(void *jobparameter, string outgfsname = "");

		/*!
		*
		**/
		bool InitJobClient(string gfspara, int jobtype);

		/*!
		*
		**/
		CAnyGdeDataTrace *GetDataTrace(long sequenceOrder, double minTime, double maxTime, CAnyGdeDataSurvey &survey, int threadoffset, bool ispremode = true);

		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataTrace *GetDataTrace(int tileCode, std::vector<int> &cmpcounts, int threadoffset);

		/*!
		*
		**/
		unsigned long Tile2File(unsigned long tileCode);
		
		/*!
		*
		**/
		bool InitGFSClient(CAnyGdeDataSet *dataset, string gxfilename, string gfspara, string gfsname);

		/*!
		*
		**/
		bool ClearCache(std::vector<long> &savedsequenceOrders);
		
		/*!
		*
		**/
		void SetFitCachelimit();
	private:
		/*!
		*
		**/
		CAnyGdeDataTrace *DoReadTraceData(unsigned long offset, std::vector<int> &cmpcounts, int threadoffset);

		/*!
		*
		**/
		static bool CompareTileCode(const CAnyGdeDataOctree::OctreeNode* first, const CAnyGdeDataOctree::OctreeNode* second)
		{
			return first->m_tileCode < second->m_tileCode;
		};

	private:
		//
		//
		//
		/*!
		*
		**/
		static bool CompareTraceSequenceOrder(const CAnyGdeDataTrace *first, const CAnyGdeDataTrace *second);

		/*!
		*
		**/
		static bool CompareTraceHitsUsage(const CAnyGdeDataTrace *first, const CAnyGdeDataTrace *second);

	public:
		// cache
		CAnyGdeDataOctree &m_octree;
		std::vector<CAnyGdeDataOctree::OctreeNode*> m_nodestocache;
		int m_nodestocachelimit;
		int m_nodestocacheallcount;
		std::vector<int> m_tileids;
		std::vector<int> m_fileids;

		// .gd files
		std::vector<wstring> m_gdfileNames;
		std::vector<std::vector<void *> > m_gdHandles;
		std::vector<int> m_gdtilecounts; // -1 for no limits

		//
		const CAnyFileBasic &m_fileBasic;
		int m_taskcount;

		// the first level cache in client side in futre
		// octree means the second level, be deployed in server side
		CAnyGdeDataTrace::TraceVector m_flyTraces;
		long m_flyLimits;
		// results for multiline class access
		CAnyGdeDataTrace::TraceVector m_tracesforMT;
		std::vector<int> m_tracetocacheforMT;
		// for distribute
		void* m_gfsclient;
		void* m_jobclient;
		void* m_mapreducer;
	};
}

#endif