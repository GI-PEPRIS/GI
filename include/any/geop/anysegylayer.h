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
#ifndef __ANYGEOP_SEGY_LAYER_H__
#define __ANYGEOP_SEGY_LAYER_H__

// refer to EXPORT & IMPORT macroes
#include "anygeop.h"

// refer to geom basic
#include "any/base/anygeom.h"
#include "any/base/anylightlru.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// for seismic survey 
#include "any/bridge/anybridgedatamodel.h"
#include "any/bridge/anyearthmodel.h"
#include "any/bridge/anygeologicalcubefeature.h"
#include "any/bridge/anygeologicalfeaturelayer.h"
using namespace AnyBridge;

#include "any/gde/anygde.h"
#include "any/gde/anygdedataset.h"
#include "any/gde/anygdedatatrace.h"
#include "any/gde/anygdedataoctreegate.h"
#include "any/gde/anygdedataoctree.h"
#include "any/gde/anygdedataoctreecache.h"
#include "any/gde/anygdedatasurvey.h"
#include "any/gde/anygdedatalinesurvey.h"
#include "any/gde/anygdedatagridsurvey.h"
#include "any/gde/anygdedatapolysurvey.h"
#include "any/gde/anygdedataiterator.h"
#include "any/gde/anygdedatapolygon.h"
#include "any/gde/anygdedatadttable.h"
#include "any/gde/anygdedataprocessbin.h"
#include "any/gde/anysegyfile.h"
using namespace AnyGDE;

// visitor pattern
#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;

//
namespace AnyGeoP
{
	// forward class
	class CAnySegyProfile;

	/*!
	*
	**/
	class ANYGEOP_CLASS CAnySegyLayer : public CAnyViewHook, public CAnyObservable, public CAnyMediator
	{
	public:
		//
		LOKI_DEFINE_VISITABLE()

		/*!
		* gates
		*/
		typedef std::vector<CAnySegyFile *> GateVector;
		typedef GateVector::iterator gate_itr;
		typedef GateVector::const_iterator gate_citr;

		/*!
		*
		**/
		struct SurveyPoint
		{
			// in-line sequence order
			int m_lineOrder;
			// CDP sequence order
			int m_cdpOrder;

			// coordinate
			CGeoPoint<double> m_coord;
			CGeoPoint<double> m_pickcoord;//user pick position

			/*!
			*
			**/
			SurveyPoint() : m_lineOrder(0), m_cdpOrder(0)
			{
				m_pickcoord.m_x = ANY_NAN;m_pickcoord.m_y = ANY_NAN;
			}
		};

		// survey line
		typedef std::vector<SurveyPoint> SurveyLine;
		typedef SurveyLine::iterator pt_itr;
		typedef SurveyLine::const_iterator pt_citr;

		// the set of survey line
		typedef std::vector<SurveyLine > SurveyLineSet;
		typedef SurveyLineSet::iterator line_ptr;
		typedef SurveyLineSet::const_iterator line_citr;

		// survey map contains different segy gates
		typedef std::map<int, SurveyLineSet> SurveyMap;
		typedef SurveyMap::iterator survey_itr;
		typedef SurveyMap::const_iterator survey_citr;

		/*!
		* when double click to fetch the below informatoin
		**/
		struct SurveyCursor
		{
			CAnyGdeDataSet *m_gdedataset;
			SurveyLine m_line;
			bool m_isInline;

			/*!
			*
			**/
			SurveyCursor() : m_gdedataset(0), m_isInline(true)
			{
			}

			/*!
			*
			**/
			void Reset()
			{
				m_gdedataset = 0;
				m_isInline = true;
				m_line.clear();
			}

			/*!
			*
			**/
			bool IsValid()
			{
				return m_gdedataset && m_line.size();
			}
		};

		/*!
		*
		**/
		struct RenderThreadParameter
		{
			int m_start;
			int m_end;
			int m_mincmpcount;
			int m_maxcmpcount;
			CGeoRect<double> m_scrsurveylineextent;
			int m_datasetoffset;
			CAnyCanvas &m_canvas;
			
			RenderThreadParameter(int start, int end, int mincmpcount, int maxcmpcount, \
				CGeoRect<double> scrsurveylineextent, int datasetoffset, CAnyCanvas &canvas) : m_start(start), m_end(end), \
				m_mincmpcount(mincmpcount), m_maxcmpcount(maxcmpcount), m_scrsurveylineextent(scrsurveylineextent), m_datasetoffset(datasetoffset), m_canvas(canvas)
			{
			}
		};
		
	public:
		/*!
		*
		**/
		CAnySegyLayer(CAnyView &curView);

		/*!
		*
		**/
		~CAnySegyLayer();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		/*!
		*
		**/
		void Set2DSeismicGeometry(CAnySegyFile *gate, const AnySeismic2DGeometry &geometry);
		void FormSurveymapBy2DSeismicGeometry(CAnySegyFile *gate, CAnyGdeDataSet* dataset, const AnySeismic2DGeometry &geometry);

		/*!
		*
		**/
		void Set3DSeismicGeometry(CAnySegyFile *gate, const AnySeismic3DGeometry &geometry);
		void ModifyLineandCdpByCDPpts(CAnySegyFile *gate);

		//
		// data gates
		//
		/*!
		*
		**/
		bool AddSegyGate(const CAnySegyFile *gate, bool isaddsurveyline = true);
		bool AddGDEDataset(CAnyGdeDataSet *dataset, bool isaddsurveyline = true);

		/*!
		*
		**/
		void RemoveSegyGate(const CAnySegyFile *gate);
		void RemoveGDEDataset(CAnyGdeDataSet *gate);

		/*!
		*
		**/
		int GetSegyGateCount()
		{
			return m_datasets.size();
		}
		int GetGDEDatasetCount()
		{
			return m_datasets.size();
		}

		/*!
		*
		**/
		CAnySegyFile *GetSegyGate(int order)
		{
			assert(order >= 0 && order < m_datasets.size());
			return (CAnySegyFile*)m_datasets[order]->m_gate;
		}
		CAnyGdeDataSet *GetGDEDataset(int order)
		{
			assert(order >= 0 && order < m_datasets.size());
			return m_datasets[order];
		}

		/*!
		*
		**/
		CAnySegyFile *GetSegyGate(const anystring &name);
		CAnyGdeDataSet *GetGDEDataset(const anystring &name);

		/*!
		*
		**/
		int GetSegyGateorGDEDatasetIdx(const anystring &name);

		//
		// geographic definition
		//
		/*!
		*
		**/
		bool UpdateSurveyMap(const anystring &name);

		/*!
		* directly set spatial extent
		**/
		void SetSurveyExtent(const CGeoRect<double> &extent);

		/*!
		* 
		**/
		const CGeoRect<double> &GetSurveyExtent();

		/*!
		*
		**/
		void RemoveSurveyLine(long gateIdx);
		void RemoveSurveyLineGDE(long datasetIdx);


		/*!
		*
		**/
		void AddSurveyLine(long gateIdx, const CAnySegyFile::SurveyInfo &surveyInfo, CGeoPoint<double> &pos0, CGeoPoint<double> &pos1, CGeoPoint<double> &pos2, CGeoPoint<double> &pos3);
		void AddSurveyLineGDE(long datasetIdx, CAnyGdeDataSet *dataset);

		/*!
		* when picking one line, return infomation 
		**/
		const SurveyCursor &GetSurveyCursor()
		{
			return m_cursor;
		}

		/*!
		* for user-defined traces to be rendered
		**/
		bool LoadSeismicProfilebyLine(CAnySegyProfile *profile, const anystring &whichGate, SurveyLine &userLine, CAnyFunctor *progress = 0, int operationMode = MO_Default, int gateid = -1);
		bool LoadSeismicProfilebyLineGDE(CAnySegyProfile *profile, const anystring &whichDataset, SurveyLine &userLine, CAnyFunctor *progress = 0, int operationMode = MO_Default);
		void GetSequenceOrdersByLine(const anystring &whichGate, std::vector<long> &sequenceOrders, SurveyLine &userLine, int operationMode);
		//
 		// layer's functions
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);
		void RenderCmpcountsThread(const RenderThreadParameter &parameter);
		void RenderDataptsThread(const RenderThreadParameter &parameter);

		//
		// observer design pattern
		//
        /*!
        * Let sub-class have its specified event types
        */
        void Notify(short type);

        /*!
        *
        */
        void Register(CAnyObserver *oneObserver);

		/*!
		*
		**/
		void SetMediator(CAnyMediator *logLayer)
		{
			m_logLayer = logLayer;
		}

		/*!
		* return TraceRecord data from CAnySegyLayer
		**/
		void PickSeismicTraceData(const CGeoPoint<double> &pos, void **data, int &number, int datasetoffset = -1);
		void GetPickSeismicTraceDataSequenceOrders(const CGeoPoint<double> &pos, int &datasetoffset, std::vector<long> &sequenceOrders);
		void PickSeismicTraceDatabyLine(SurveyLine &userLine, int operationMode, void **data, int &number, int datasetoffset = -1);
		void PickSeismicTraceDatabySequenceOrders(std::vector<long> &sequenceOrders, void **data, int &number, int datasetoffset);
		
        /*!
        *
        */
        int SaveToDB(int classid, int elementid, int type, string remark = "", int newgatenum = 0, bool saveblobinDB = true);
				
        /*!
        *
        */
        void LoadFromDB(int classid, int type, CAnyFunctor *progress);
						
        /*!
        *
        */
        static void RemoveFromDB(int classid, int type);
						
        /*!
        *
        */
        void RemoveOneDatasetFromDB(int datasetoffset);
								
        /*!
        *
        */
        static void SaveProjectAttributeToDB(AnySeismicProject &project);
										
        /*!
        *
        */
        static void LoadProjectAttributeFromDB(AnySeismicProject &project, int projectid);
										
        /*!
        *
        */
        static void SaveDatasetAttributeToDB(AnySeismicDataSet &dataset);
										
        /*!
        *
        */
        static void LoadDatasetAttributeFromDB(AnySeismicDataSet &dataset, int datasetid);
												
        /*!
        *
        */
		void FilterPointsOnline(SurveyLine &line, std::vector<CGeoPoint<double> > &inmappts, std::vector<string> &innames, std::vector<CGeoPoint<double> > &outscrpts, std::vector<string> &outnames, std::vector<int> &outpositions, std::vector<double> &outdistance, int operationMode = MO_Default);
		
		/*!
		*
		**/
		bool Coord2Survey(int offset, const CGeoPoint<double> &pt, double &lineNo, double &cdpNo);

		/*!
		*
		**/
		bool Survey2Coord(int offset, double lineNo, double cdpNo, CGeoPoint<double> &pt);

		/*!
		*
		**/
		bool Survey2Sequence(int offset, double lineNo, double cdpNo, long &sequenceOrder);

		/*!
		*
		**/
		bool Sequence2Survey(int offset, long sequenceOrder, double &lineNo, double &cdpNo);

	public:
		//
		//
		//
		/*!
		*
		**/
		bool CAnySegyLayer::DoGetTraceRecord(long gateIdx, CAnySegyFile *gate, std::vector<long> &sequenceOrders, std::vector<CAnyGdeDataGate::TraceRecord*> &records, CAnyFunctor *progress, double minTime = ANY_NAN, double maxTime = ANY_NAN);

		/*!
		*
		**/
		bool DoPickSurveyLine(const CGeoPoint<double> &scrPt, int lineorcdp = 0);
		
		/*!
		*
		**/
		bool DoPickSurveyPoint(const CGeoPoint<double> &scrPt);
		
		/*!
		*
		**/
		bool Query(const CGeoRect<double> &rect, std::vector<unsigned long> &idxes, bool isCircle = false);
		
		/*!
		*
		**/
		bool Query(const std::vector<CGeoPoint<double> > &poly, std::vector<unsigned long> &idxes);

		/*!
		*
		**/
		unsigned char* DoEncoding(SurveyMap &map, int &length);

		/*!
		*
		**/
		bool DoDecoding(unsigned char* &parameter, SurveyMap &map, int length);

		/*!
		*
		**/
		bool IsIntersect( CGeoPoint<double> p1, CGeoPoint<double> p2, CGeoPoint<double> p3, CGeoPoint<double> p4 );

		/*!
		*
		**/
		double CrossProduct( CGeoPoint<double> pii, CGeoPoint<double> pj, CGeoPoint<double> pk );
		
		/*!
		* GDE,SGY融合相关
		**/
		void GetRange(int &inlinestart, int &inlineend, int &xlinestart, int &xlineend, double &mintime, double &maxtime);
		double GetTimeInterval(int offset = 0);

		/*!
		*
		*/	
		ColorStyle GetRandomColor(int n);
	public:

		/*!
		*  求取解释成果与切片的交线的相关函数
		**/
		static void CalculateIntersectionLines(CAnyGeologicalCubeFeature* cubefeature, CAnySegyLayer *sgyLayer, int &gateoffset, std::vector<double> &lineOrders, std::vector<double> &traceOrders, std::vector<double> &times, std::vector<std::vector<CGeoPoint<double> > > &intersectionlines);
		static void CalculateIntersectionPoints(CAnyGeologicalCubeFeature* cubefeature, CAnySegyLayer *sgyLayer, int &gateoffset, std::vector<double> &lineOrders, std::vector<double> &traceOrders, std::vector<double> &times, std::vector<CGeoPoint<double> > &intersectionpoints);
		static void ConnectPointsToLines(double &mincheckdis, std::vector<CGeoPoint<double> > &intersectionpoints, std::vector<std::vector<CGeoPoint<double> > > &intersectionlines);
		static bool CalculateVector(CGeoPoint<double> &a, CGeoPoint<double> &b, CGeoPoint<double> &c, double &ratea, double &rateb);
		static bool IsSampleOutsidArea(CAnyGeologicalCubeFeature::FeatureSample &sample, std::vector<double> &lineOrders, std::vector<double> &traceOrders, std::vector<double> &times);
		static bool IsPointOutsidArea(CGeoPoint<double> point, std::vector<CGeoPoint<double> > &planepoints);
		static bool CalculateVerticalVector(CGeoPoint<double> &vectora, CGeoPoint<double> &vectorb, CGeoPoint<double> &vectorresult);
		static bool CalculateCrossPoint(CGeoPoint<double> &m, CGeoPoint<double> &VL, CGeoPoint<double> &n, CGeoPoint<double> &VP, CGeoPoint<double> &result, double &t);

	public:
		std::vector<bool> m_isgdes;
		SurveyCursor m_cursor;

		int m_cursorlinenum;//联动剖面中鼠标位置对应的线号
		int m_cursorcdpnum;//联动剖面中鼠标位置对应的道号
		std::vector<int> m_selectedsequenceorders;//联动剖面中查询多边形查到的结果
		bool m_isshowcursorcross;//显示十字光标
		CAnyGdeDataSet* m_cursordataset;

		// segy gates
		std::vector<CAnyGdeDataSet*> m_datasets;
		std::vector<string> m_2dlinenames;
		std::vector<bool> m_datasetpickvalids;//哪些dataset可以被拾取
		bool m_ispickmultisgy;//是否拾取多个sgy文件同时展示到一个剖面上

		// geographic extent
		// its dummy vector order maybe as id of cache unit
		// ...
		CGeoRect<double> m_extent;
		
		// layer content
		SurveyMap m_map;
		bool m_isdrawcmpcount;
		int m_drawwhichcmpcount;
		bool m_isdrawcmppts;
		std::vector<int> m_isdrawcmpptsparameter;
		bool m_isdrawdatapts;

		// observer & mediator
		CAnyObserver *m_observer;

		CAnyMediator *m_logLayer;

		// related earthmodel
		CAnyEarthModel *m_earthmodel;

		// grid show settings
		int m_inlinetrap;
		int m_xlinetrap;
		double m_inlinestart;
		double m_xlinestart;
		double m_inlineend;
		double m_xlineend;
		LabelStyle m_inlinelablestyle; // 线号字体，颜色
		LabelStyle m_xlinelablestyle; // 道号字体，颜色
		LineStyle m_inlinestyle; // 测网线线型，颜色，线宽
		LineStyle m_xlinestyle; // 测网道线型，颜色，线宽
		LineStyle m_selectlinestyle; // 选中线线型，颜色，线宽
		bool m_inlinehandleoverwrite;//测网线压盖处理
		bool m_xlinehandleoverwrite;//测网道压盖处理

		LineStyle m_horizonlinestyle; // 层位线型，颜色，线宽
		LineStyle m_faultlinestyle; // 断层线型，颜色，线宽
		bool m_ishorizonshown; // 显示层位
		bool m_isfaultshown; // 显示断层
		LineStyle m_wellstyle; // 井轨迹线型，颜色，线宽
		bool m_iswellshown; // 显示井轨迹

		std::vector<std::vector<CGeoPoint<double> > > m_slicecachepts;
	};
}

#endif
