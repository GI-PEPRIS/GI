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
#ifndef __ANYGDE_SAMPLE_DATASET_H__
#define __ANYGDE_SAMPLE_DATASET_H__

//
#include "anygde.h"

// refer to data gate
#include "anygdedatagate.h"

// refer to geopoint
#include "any/base/anygeom.h"
#include "any/base/anyfilebasic.h"
using namespace AnyBase;

//
namespace AnyGDE
{
	// forward classes
	class CAnyGdeDataOctreeGate;
	class CAnyGdeDataSurvey;
	class CAnyGdeDataTrace;

	/*!
	* against  EpiProject_Project and EpiSeismic_SeismicDataset persistence table
	**/
	class ANYGDE_CLASS CAnyGdeDataSet
	{
	public:
		/*!
		* AnySeismicDataSet's m_domainType
		**/
		enum TimeDepth
		{
			TD_Unknown,
			TD_Time,
			TD_Depth,
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataSet(CAnyGdeDataGate *gate, CAnyGdeDataSurvey *survey);

		/*!
		*
		**/
		~CAnyGdeDataSet();

	public:
		//
		// meta data for persistence
		//
		/*!
		*
		**/
		void SetProject(const AnySeismicProject &prj);

		/*!
		*
		**/
		const AnySeismicProject &GetProject()	const;

		/*!
		*
		**/
		void SetDataset(const AnySeismicDataSet &dataset);
	
		/*!
		*
		**/
		const AnySeismicDataSet &GetDataset() const;

		//
		// policies interface
		//
		/*!
		*
		**/
		void SetDataGate(CAnyGdeDataGate *gate);

		/*!
		*
		**/
		CAnyGdeDataGate *GetDataGate();

		/*!
		*
		**/
		void SetDataSurvey(CAnyGdeDataSurvey *survey);

		/*!
		*
		**/
		CAnyGdeDataSurvey *GetDataSurvey();
		
		/*!
		*
		**/
		bool WriteGDX(CAnyFunctor *progress, bool isuseroriginfurveyinfo, CAnyGdeDataGate::SurveyInfo &originsurveyInfo);

		/*!
		*
		**/
		bool LoadGDX(CAnyFunctor *progress);

		/*!
        * save survey head profile info
        */
        void SaveToDB(int datasetid, string linename = "", bool saveblobinDB = true);
				
        /*!
        * load survey head profile info
        */
        void LoadFromDB(int gateid);
		
		/*!
		*
		**/
		int LoadFileidFromGDX(int tilecode);
					
		/*!
		* return offset of tileid<->fileid in .gx file
		**/
		int GetIndexStartPos();

		/*!
		*
		**/
		void FormDataSurveyFromSegy(int type);

		//
		//
		//	
		/*!
		* given the current data survey, namely during running time ,data set can set its whole or partial survey
		**/
		long GetDataTraceCount();

		/*!
		* by sequence order. the encoding rule of order as whole or as partial
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress);

		/*!
		* by sequence order. the encoding rule of order as whole or as partial
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, std::vector<std::vector<float*> > &traces, CAnyFunctor *progress, bool ispremode, std::vector<std::vector<int> > &gridpos_fileposes);
		
		/*!
		* by sequence order. the encoding rule of order as whole or as partial
		**/
		bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress);

		/*!
		* min and max time = ANY_NAN, means to fetch the whole trace
		**/
		bool GetDataTrace(const CGeoPoint<double> &coord, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress);

		/*!
		* query in box 
		**/
		bool GetDataTrace(const CGeoRect<double> &extent, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress);

		/*!
		* query in polyline
		**/
		bool GetDataTrace(const std::vector<CGeoPoint<double> > &poly, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress);

		/*!
		*
		**/
		bool GetInLineDataTrace(double lineNo, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress);

		/*!
		*
		**/
		bool GetCrossLineDataTrace(double cdpNo, double minTime, double maxTime, CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress);

		//
		//
		//
		/*!
		*
		**/
		CGeoPoint<double> *GetTimeClip(double time, int rows, int cols);

		/*!
		*
		**/
		CGeoPoint<double> *GetLayerClip(const CAnyGeologicalCubeFeature &layer, int rows, int cols);
		
		/*!
		*
		**/
		CGeoRect<double> GetExtent(bool isgde);
				
		/*!
		*
		**/
		wstring GetName(bool isgde);
		
	public:
		// project meta data
		AnySeismicProject m_project;
		// dataset meta data
		AnySeismicDataSet m_dataset;

		// kinds of policies
		CAnyGdeDataGate *m_gate;
		// as trace iterator
		CAnyGdeDataSurvey *m_survey;

		// .gx file
		wstring m_gxfileName;
		void *m_gxHandle;
		const CAnyFileBasic &m_fileBasic;
	};
}
#endif