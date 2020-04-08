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
#ifndef __ANYGEOP_SEGY_PROFILE_H__
#define __ANYGEOP_SEGY_PROFILE_H__

// refer to macro
#include "anygeop.h"

// refer to seis data gate and correlated algorithms
#include "anysegystrategy.h"
#include "anysegylayer.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to geopoint
#include "any/base/anygeom.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

#include "any/gde/anygde.h"
#include "any/gde/anygdedataset.h"
#include "any/gde/anygdedatatrace.h"
#include "any/gde/anygdedatagate.h"
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
using namespace AnyGDE;

#include "any/bridge/anygeologicalcubefeature.h"

// visitor pattern
#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;

//
namespace AnyGeoP
{
	/*!
	*
	**/
	class ANYGEOP_CLASS CAnySegyProfile : public CAnyViewHook, public CAnyObserver
	{
	public:
		//
		LOKI_DEFINE_VISITABLE()

		/*!
		* profile type
		**/
		enum ProfileType
		{
			PT_Unknown					= 0,
			PT_Curve						= 1,
			PT_Curve_Filling				= 1 << 1,
			PT_Gray						= 1 << 2,
			PT_Color						= 1 << 3,
			PT_RGB						= 1 << 4,
			PT_Max
		};

		/*!
		* statisitcs of current profile
		**/
		struct ProfileRecord
		{
			// geographic coords
			CGeoPoint<double> m_start;
			CGeoPoint<double> m_end;

			// profile extent
			// m_x mean the maximum direct distance
			// m_y means maximum time or depth
			// ... ...
			CGeoRect<double> m_extent;

			// max、 min and base amplitude
			double m_minA;
			double m_maxA;
			double m_maxValue;
			double m_minValue;
			double m_baseA; // scalar for sharp
			double m_scale;

			double m_grayAlow;//values in [m_grayAlow, m_grayAup] will be handle by ToGray instead of ToPseudoColor
			double m_grayAup;

			// min/start in-line / cross-line 
			long m_minOrder;

			// profile rendering type
			short m_renderingType;

			// whether to mix color
			bool m_isBlended;

			// whether to color complemented
			bool m_isComplemented;

			// whether show grid on layer
			bool m_isShowGrid;

			// whether show interval line on layer
			bool m_isshowintervalline;

			//whether show cursor line on layer
			bool m_isshowcursorline;

			// Pseudo color settings
			std::vector<double> m_colorcodevals;
			std::vector<int> m_colorcodecolors;
			
			// tick settings
			int m_xtrap;
			int m_ytrap;

			/*!
			*
			**/
			ProfileRecord()
			{
				Reset();
			}

			/*!
			*
			**/
			void Reset()
			{
				m_extent.Empty();
				m_extent.m_minX = m_extent.m_minY = m_minOrder = m_start.m_x = m_start.m_y = m_minValue = 0x7FFFFFFF;
				m_extent.m_maxX = m_extent.m_maxY = m_end.m_x = m_end.m_y = m_maxA = m_maxValue = -0x7FFFFFFF;
				m_scale = 1.;
				m_minA = m_baseA = m_grayAlow = m_grayAup = 0.;

				m_renderingType = PT_Gray;
				m_isBlended = false;
				m_isComplemented = false; 
				m_isShowGrid = false;
				m_isshowintervalline = false;
				m_isshowcursorline = true;
				m_colorcodevals.clear();
				m_colorcodecolors.clear();
				m_xtrap = 10;
				m_ytrap = 50;
			}

			/*!
			*
			**/
			const ProfileRecord &operator=(const ProfileRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_start = other.m_start;
				m_end = other.m_end;
				m_extent = other.m_extent;
				m_minA = other.m_minA;
				m_maxA = other.m_maxA;
				m_minValue = other.m_minValue;
				m_maxValue = other.m_maxValue;
				m_baseA = other.m_baseA;
				m_scale = other.m_scale;
				m_grayAlow = other.m_grayAlow;
				m_grayAup = other.m_grayAup;
				m_minOrder = other.m_minOrder;

				m_renderingType = other.m_renderingType;
				m_isBlended = other.m_isBlended;
				m_isComplemented = other.m_isComplemented; 
				m_isShowGrid = other.m_isShowGrid; 
				m_isshowintervalline = other.m_isshowintervalline;
				m_isshowcursorline = other.m_isshowcursorline;

				m_colorcodevals = other.m_colorcodevals;
				m_colorcodecolors = other.m_colorcodecolors;
				m_xtrap = other.m_xtrap;
				m_ytrap = other.m_ytrap;

				return *this;
			}

			void Setproperty(const ProfileRecord &other)
			{
				m_renderingType = other.m_renderingType;
				m_isBlended = other.m_isBlended;
				m_isComplemented = other.m_isComplemented; 
				m_isShowGrid = other.m_isShowGrid; 
				m_isshowintervalline = other.m_isshowintervalline;
				m_isshowcursorline = other.m_isshowcursorline;

				m_colorcodevals = other.m_colorcodevals;
				m_colorcodecolors = other.m_colorcodecolors;
				m_xtrap = other.m_xtrap;
				m_ytrap = other.m_ytrap;
			}
		};

		typedef std::vector<CAnyGdeDataGate::TraceRecord*> TraceVector;
		typedef TraceVector::iterator trace_itr;
		typedef TraceVector::const_iterator trace_citr;

		struct TraceHeadoffset
		{
			CGeoPoint<double> m_shotpt;
			CGeoPoint<double> m_detectionpt;
			double m_angle;
			int m_offset;
			/*!
			*
			**/
			TraceHeadoffset() : m_offset(0), m_angle(0)
			{
			}

			/*!
			*
			**/
			const TraceHeadoffset &operator=(const TraceHeadoffset &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_shotpt = other.m_shotpt;
				m_detectionpt = other.m_detectionpt;
				m_angle = other.m_angle;
				m_offset = other.m_offset;
				return *this;
			}
			static bool CompareDistance(const TraceHeadoffset &a, const TraceHeadoffset &b)
			{
				double distancea = sqrt((a.m_shotpt.m_x - a.m_detectionpt.m_x) * (a.m_shotpt.m_x - a.m_detectionpt.m_x) + (a.m_shotpt.m_y - a.m_detectionpt.m_y) * (a.m_shotpt.m_y - a.m_detectionpt.m_y));
				double distanceb = sqrt((b.m_shotpt.m_x - b.m_detectionpt.m_x) * (b.m_shotpt.m_x - b.m_detectionpt.m_x) + (b.m_shotpt.m_y - b.m_detectionpt.m_y) * (b.m_shotpt.m_y - b.m_detectionpt.m_y));
				if(distancea < distanceb)
					return true;
				return false;
			}
			static bool CompareAzimuth(const TraceHeadoffset &a, const TraceHeadoffset &b)
			{
				double distancea = sqrt((a.m_shotpt.m_x - a.m_detectionpt.m_x) * (a.m_shotpt.m_x - a.m_detectionpt.m_x) + (a.m_shotpt.m_y - a.m_detectionpt.m_y) * (a.m_shotpt.m_y - a.m_detectionpt.m_y));
				double distanceb = sqrt((b.m_shotpt.m_x - b.m_detectionpt.m_x) * (b.m_shotpt.m_x - b.m_detectionpt.m_x) + (b.m_shotpt.m_y - b.m_detectionpt.m_y) * (b.m_shotpt.m_y - b.m_detectionpt.m_y));
				double anglea = acos((a.m_detectionpt.m_x - a.m_shotpt.m_x) / distancea);
				double angleb = acos((b.m_detectionpt.m_x - b.m_shotpt.m_x) / distanceb);
				if(a.m_detectionpt.m_y < a.m_shotpt.m_y)
					anglea = 2 * PI - anglea;
				anglea = 2.5 * PI - anglea;
				if(anglea >= 2 * PI)
					anglea -= 2 * PI;
				if(b.m_detectionpt.m_y < b.m_shotpt.m_y)
					angleb = 2 * PI - angleb;
				angleb = 2.5 * PI - angleb;
				if(angleb >= 2 * PI)
					angleb -= 2 * PI;
				if(anglea < angleb)
					return true;
				return false;
			}
			static bool CompareAngle(const TraceHeadoffset &a, const TraceHeadoffset &b)
			{
				if(a.m_angle < b.m_angle)
					return true;
				return false;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySegyProfile(CAnyView &curView, CAnyObservable *observable = 0);

		/*!
		*
		**/
		~CAnySegyProfile();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		//
		//
		//
		/*!
		*
		**/
		bool AddTraceRecord(const CAnyGdeDataGate::TraceRecord *record, bool isReset = false);
		bool AddTraceRecordGDE(CAnyGdeDataTrace *record, bool isReset = false);

		/*!
		* erase all trace records loaded 
		**/
		void RemoveAll();
		void ClearSuperGroupData();
		void ClearAngleGroupData();
		void ClearSuperCmpData();
		void ClearSuperCmpGroupData();
		void ClearAngleSuperGroupData();
		void ClearAngleSuperCmpGroupData();

		/*!
		*
		**/
		void SetSegyGate(CAnySegyFile *gate)
		{
			if(!m_gdedataset)
			{
				CAnyGdeDataGridSurvey::GridSurvey gridsurvey;
				CAnyGdeDataSurvey *survey = new CAnyGdeDataGridSurvey(gridsurvey);
				m_gdedataset = new CAnyGdeDataSet(gate, survey);
			}
			else
				m_gdedataset->m_gate = gate;
		}
		void SetGDEdataset(CAnyGdeDataSet *&dataset)
		{
			m_gdedataset = dataset;
		}

		/*!
		*
		**/
		CAnySegyFile *GetSegyGate()
		{
			assert(m_gdedataset->m_gate);
			return (CAnySegyFile*)m_gdedataset->m_gate;
		}
		CAnyGdeDataSet *GetGDEdataset()
		{
			assert(m_gdedataset);
			return m_gdedataset;
		}

		/*!
		*
		**/
		ProfileRecord &GetProfileRecord();

		/*!
		*
		**/
		void UpdateProfileRecord(const ProfileRecord &record);

		//
 		//
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
		bool GetCurCursor(const CGeoPoint<double> &scrPoint, string &linename, int &linenum, int &cdpnum, int &cmpoffset, double &depth, double &dis, double &amp, CGeoPoint<double> &shotpt, CGeoPoint<double> &detecpt);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);
		
		/*!
		*
		**/
		bool Query(const std::vector<CGeoPoint<double> > &poly);

		
		/*!
		*
		**/
		bool Query(const CGeoRect<double> &rect, double &minorderrate, double &maxorderrate, double &mintime, double &maxtime);

		//
		//
		//
		/*!
        *
        */
        void Update(short type = 0, void *para = 0);

		/*!
        *
        */
		void Trackpts(double mintime, double maxtime, double starttimemin, double starttimemax, double timewindow, double timewindowoffset, double timewindowadjust, \
			int startoffset, int endoffset, std::vector<CGeoPoint<double> > &trackpts);
		
		/*!
        *
        */
		void GetSuperpositionTraces(CAnySegyLayer *Superpositionlayer, int datasetoffset, double minorderrate, double maxorderrate, double mintime, double maxtime, \
			double minoffsetdisrate, double maxoffsetdisrate, double mindirectionanglerate, double maxdirectionanglerate, CAnyFunctor *progress);

		/*!
        *
        */
		void GetAmpSpeTraces(double minorderrate, double maxorderrate, double mintime, double maxtime, std::vector<std::vector<double> > &results, CAnyFunctor *progress);
		void DoAmpSpe(std::vector<std::vector<double> > &Seis, double sample_int, std::vector<double> &Amp_spe, std::vector<double> &freq);
		
		/*!
        *
        */
		void GetSuperpositionGroupTraces(double minoffset, double maxoffset, int offsetgroup, double mindirectionangle, double maxdirectionangle, int anglegroup, CAnyFunctor *progress);
		
		/*!
        *
        */
		void GetVrmsAndVint(CAnySegyLayer *vrmslayer, int vrmsdatasetoffset, CAnySegyLayer *vintlayer, int vintdatasetoffset, CAnyFunctor *progress);
													
		/*!
        *
        */
		void GetAngleGroupTraces(int prestackconvertertype, CAnySegyLayer *hostlayer, int datasetoffset, CAnyFunctor *progress);

		/*!
        *
        */
		void GetSuperCmpTraces(CAnyFunctor *progress);
						
		/*!
        *
        */
		void GetSuperCmpGroupTraces(double minoffset, double maxoffset, int offsetgroup, double mindirectionangle, double maxdirectionangle, int anglegroup, CAnyFunctor *progress);

		/*!
        *
        */
		void GetAngleSuperpositionGroupTraces(int prestackconvertertype, CAnySegyLayer *hostlayer, int datasetoffset, double mindirectionangle, double maxdirectionangle, int directionanglegroup, double mininputangle, double maxinputangle, int inputanglegroup, CAnyFunctor *progress);						

		/*!
        *
        */
		void GetSuperAngleSuperpositionGroupTraces(int prestackconvertertype, CAnySegyLayer *hostlayer, int datasetoffset, double mindirectionangle, double maxdirectionangle, int directionanglegroup, double mininputangle, double maxinputangle, int inputanglegroup, CAnyFunctor *progress);

		/*!
        *
        */
		void GetMaxMinDistanceAndAngle(double &mindistance, double &maxdistance, double &minangle, double &maxangle);

		//
		//
		//
		/*!
		*
		**/
		unsigned int ToGray(double value);

		/*!
		*
		**/
		unsigned int Merge2RGB(double value);

		/*!
		*
		**/
		unsigned int ToPseudoColor(double value);

		/*!
		*
		**/
		unsigned int ToRealColor(double value);

		//
		//
		//
		/*!
		*
		**/
		void DoStatisticProfile(const CAnyGdeDataGate::TraceRecord *record);
		void DoStatisticProfileGDE(CAnyGdeDataTrace *record);

		/*!
		*
		**/
		void DoPrepareProfile();
		
		/*!
		*
		**/
		void SetPixelInterval(double pixeltrace, double pixelms);
				
		/*!
		*
		**/
		void GetPixelInterval(double &pixeltrace, double &pixelms);

		//
		// rendering functions
		//
		/*!
		*
		**/
		void DoRenderCurve(CAnyCanvas &canvas, const CGeoRect<double> &clipBox);
		void DoRenderCurveSuper(CAnyCanvas &canvas, const CGeoRect<double> &clipBox);

		/*!
		*
		**/
		void DoRenderColor(CAnyCanvas &canvas, const CGeoRect<double> &clipBox);
		void DoRenderColorSuper(CAnyCanvas &canvas, const CGeoRect<double> &clipBox);
		
		/*!
		*
		**/
		void DoRenderAttri(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, int &maxcmpcount);

		/*!
		*
		**/
		void DoRenderCAGColor(CAnyCanvas &canvas, const CGeoRect<double> &clipBox);

		/*!
		*
		**/
		void DoRenderGrayBlock(CAnyCanvas &canvas, const CGeoRect<double> &block, double f1, double f2, double f3, double f4, bool issupermode = false);

		/*!
		*
		**/
		void DoRenderColorBlock(CAnyCanvas &canvas, const CGeoRect<double> &block, double f1, double f2, double f3, double f4);

		/*!
		*
		**/
		long CAnySegyProfile::DoGetTraceOrder(long which);

		/*!
		*
		**/
		void DoCalculateInerpolation(const CGeoRect<double> &tMapExtent, const CGeoPoint<double> &prevMapPt, const CGeoPoint<double> &curMapPt, CGeoPoint<double> &interPt);

		//
		//
		//
		/*!
		*
		**/
		static bool CompareTraceHashCode(const CAnyGdeDataGate::TraceRecord *first, const CAnyGdeDataGate::TraceRecord *second);

		/*!
		*
		**/
		static bool CompareTraceOrder(const CAnyGdeDataGate::TraceRecord *first, const CAnyGdeDataGate::TraceRecord *second);
		
		/*!
		*
		**/
		double Time2MapY(double time);
				
		/*!
		*
		**/
		double MapY2Time(double y);

		/*!
		*
		**/
		double Welladjustshift(double curdepth, string curwellname);	

		/*!
		*
		**/
		void RayTracing(std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, std::vector<std::vector<double> > &seta);

		/*!
		*
		**/
		bool UpdateTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyGdeDataGate::SurveyInfo &survey, CAnyFunctor *progress);

		/*!
		*
		**/
		bool CommitTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyGdeDataGate::SurveyInfo &survey, CAnyFunctor *progress, std::vector<std::vector<double> > metas);

		/*!
		*
		**/
		long GetCalculatorCubeCount(CalculatorCube::DataCubeSize &cubesize, CAnyGeologicalCubeFeature::SampleVector &horizon);
		
		/*!
		*
		**/
		bool GetCalculatorCube(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CalculatorCube &cube, CAnyGdeDataGate::SurveyInfo &survey, bool cachemode);
					
		/*!
		*
		**/
		bool GetCalculatorCubeTraces(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs, \
			std::vector<CAnyGdeDataTrace*> &traces, CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CAnyGdeDataGate::SurveyInfo &survey);

		/*!
		*
		**/
		bool GetCalculatorCubeLineandCdps(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CAnyGdeDataGate::SurveyInfo &survey, std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs);

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
			std::vector<CAnyGdeDataTrace*> &supertraces, CAnyGdeDataGate::SurveyInfo &survey);

		/*!
		*
		**/
		bool GetSurrondingTracesCache(CalculatorCube &cube, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGdeDataGate::SurveyInfo &survey);

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
		bool Open(int type = CAnyFileBasic::ANY_FILE_READ, int bufsize = -1);

		/*!
		*
		**/
		void ConvertCAG_weight(std::vector<std::vector<double> > &cmps, std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, \
			std::vector<double> &angles, std::vector<std::vector<double> > &cag);
									
		/*!
		*
		**/
		void ConvertCAG_interpolation(std::vector<std::vector<double> > &cmps, std::vector<double> &distances, std::vector<double> &times, std::vector<double> &vrms, std::vector<double> &vint, \
			std::vector<double> &angles, std::vector<std::vector<double> > &cag);
	public:
		bool m_isgde;
		bool m_ispremode;//是否叠前模式
		bool m_ispreattrimode;//是否叠前属性模式
		bool m_isshowanglecolor;//是否显示入射角颜色
		std::vector<double> m_preattritimes;//叠前属性时间
		int m_cmpmode; //0:正常，1: 偏移距方位角分组叠加，2:角道集, 3:超道集, 4:超道集偏移距方位角分组叠加,5:角道集入射角方位角分组叠加,6:超道集角道集入射角方位角分组叠加
		int m_presorttype;//叠前数据排序方式:，0：不排， 1：按偏移距，2：按方位角，3：按入射角
		bool m_isanglegroupgate;//是否为角道集类型的gate

		double m_cursorDepth;//当前鼠标位置对应的深度
		int m_cursorlinenum;//当前鼠标位置对应的线号
		int m_cursorcdpnum;//当前鼠标位置对应的道号
		int m_cursorcmpoffset;//当前鼠标位置对应的道集内偏移

		std::vector<std::vector<CGeoPoint<double> > > m_trackpts;//追踪线

		std::vector<std::vector<CGeoPoint<double> > > m_supertraces;//实时叠加
		int m_superminorderoffset;//实时叠加参数
		int m_supermaxorderoffset;//实时叠加参数
		double m_supermintime;//实时叠加参数
		double m_supermaxtime;//实时叠加参数

		std::vector<CGeoPoint<double> > m_querypolygon;//叠前属性查询
		std::vector<int> m_selectedsequenceorders;//叠前属性查询
		std::vector<int> m_selectedcmpoffsets;//叠前属性查询

		TraceVector m_traces;//正常
		TraceVector m_supergrouptraces;//偏移距方位角分组叠加
		TraceVector m_anglegrouptraces;//角道集
		TraceVector m_supercmptraces;//超道集
		TraceVector m_supercmpgrouptraces;//超道集偏移距方位角分组叠加
		TraceVector m_anglesupergrouptraces;//角道集入射角方位角分组叠加
		TraceVector m_anglesupercmpgrouptraces;//超道集角道集入射角方位角分组叠加
		std::vector<CAnyGdeDataTrace*> m_gdetraces;//正常
		std::vector<CAnyGdeDataTrace*> m_gdesupergrouptraces;//偏移距方位角分组叠加
		std::vector<CAnyGdeDataTrace*> m_gdeanglegrouptraces;//角道集
		std::vector<CAnyGdeDataTrace*> m_gdesupercmptraces;//超道集
		std::vector<CAnyGdeDataTrace*> m_gdesupercmpgrouptraces;//超道集偏移距方位角分组叠加
		std::vector<CAnyGdeDataTrace*> m_gdeanglesupergrouptraces;//角道集入射角方位角分组叠加
		std::vector<CAnyGdeDataTrace*> m_gdeanglesupercmpgrouptraces;//超道集角道集入射角方位角分组叠加
		std::vector<int> tracesequenceorders;

		//分组叠加参数
		double m_supergroupminoffset;
		double m_supergroupmaxoffset;
		int m_supergroupoffsetgroup;
		double m_supergroupmindirectionangle;
		double m_supergroupmaxdirectionangle;
		int m_supergroupanglegroup;
		double m_supergroupmininputangle;
		double m_supergroupmaxinputangle;
		int m_supergroupinputanglegroup;

		//角道集参数
		std::vector<std::vector<double> > m_vrms;
		std::vector<std::vector<double> > m_vint;
		std::vector<double> m_angles;
		double m_azimuthlow;
		double m_azimuthhigh;
		int m_azimuthgroup;
		CAnySegyLayer *m_vrmslayer;
		CAnySegyLayer *m_vintlayer;
		int m_vrmsdataoffset;
		int m_vintdataoffset;

		//超道集参数
		std::vector<CGeoPoint<double> > m_supercmpshotpts;
		std::vector<CGeoPoint<double> > m_supercmpdetectpts;
		std::vector<double> m_supercmpangles;

		// profile record
		ProfileRecord m_profile;

		// observerable
		CAnyObservable *m_observable;

		// host dataset
		CAnyGdeDataSet *m_gdedataset;
		std::vector<CAnyGdeDataSet*> m_multigdedataset;//用于多个sgy显示在一个剖面

		// kinds of strategies for promotion of current profile rendering
		CAnySegyStrategy m_strategy;

		double m_linelength; //剖面对应的测线的总长度

		string m_linename; //测线名称

		// for render welllayer
		std::vector<std::vector<AnyTraceSample> >m_samples; //井的数据
		std::vector<std::vector<double> > m_wellpicks; //井的分层数据
		std::vector<int> m_linecounts; // 井中曲线的个数
		std::vector<string> m_names; //井的名称
		std::vector<std::vector<string> > m_subnames; //井中曲线的名称
		std::vector<std::vector<double> > m_nullvalues; //井中曲线的无效值
		std::vector<int> m_positions; // 井的位置
		std::vector<int> m_distances; // 井与剖面的最短距离
		std::vector<LineStyle> m_wellstyles; // 井曲线线型，颜色，线宽
		std::vector<std::vector<LineStyle> > m_subwellstyles; // 井中每个曲线线型，颜色，线宽
		std::vector<std::vector<double> > m_subminA; // 井中每个曲线左刻度
		std::vector<std::vector<double> > m_submaxA; // 井中每个曲线右刻度
		std::vector<bool> m_iswellshowns; // 是否显示井曲线
		std::vector<std::vector<bool> > m_subiswellshowns; // 是否显示井曲线
		std::vector<bool> m_iswelladjusts; // 是否为井轨迹,井轨迹不显示，只用来辅助投影
		int m_distancetype; //距离类型,0:<=,1:>=
		double m_distancelen;//距离长度
		int m_projectiontype; // 投影类型，0:垂直投影，1：井轨迹投影
		double m_projectiondepth; // 垂直投影深度

		// for render earthmodel
		std::vector<CAnyGeologicalCubeFeature::SampleVector> m_lines;
		std::vector<std::vector<int> > m_poses;
		std::vector<string> m_cubenames;
		std::vector<int> featurekinds; // 解释成果类型(层位/断层)
		std::vector<LineStyle> m_featurelinestyles; // 解释成果线型，颜色，线宽
		std::vector<bool> m_isfeatureshowns;  // 是否显示解释成果
	};
}
#endif