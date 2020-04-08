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

			// max�� min and base amplitude
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
		bool m_ispremode;//�Ƿ��ǰģʽ
		bool m_ispreattrimode;//�Ƿ��ǰ����ģʽ
		bool m_isshowanglecolor;//�Ƿ���ʾ�������ɫ
		std::vector<double> m_preattritimes;//��ǰ����ʱ��
		int m_cmpmode; //0:������1: ƫ�ƾ෽λ�Ƿ�����ӣ�2:�ǵ���, 3:������, 4:������ƫ�ƾ෽λ�Ƿ������,5:�ǵ�������Ƿ�λ�Ƿ������,6:�������ǵ�������Ƿ�λ�Ƿ������
		int m_presorttype;//��ǰ��������ʽ:��0�����ţ� 1����ƫ�ƾ࣬2������λ�ǣ�3���������
		bool m_isanglegroupgate;//�Ƿ�Ϊ�ǵ������͵�gate

		double m_cursorDepth;//��ǰ���λ�ö�Ӧ�����
		int m_cursorlinenum;//��ǰ���λ�ö�Ӧ���ߺ�
		int m_cursorcdpnum;//��ǰ���λ�ö�Ӧ�ĵ���
		int m_cursorcmpoffset;//��ǰ���λ�ö�Ӧ�ĵ�����ƫ��

		std::vector<std::vector<CGeoPoint<double> > > m_trackpts;//׷����

		std::vector<std::vector<CGeoPoint<double> > > m_supertraces;//ʵʱ����
		int m_superminorderoffset;//ʵʱ���Ӳ���
		int m_supermaxorderoffset;//ʵʱ���Ӳ���
		double m_supermintime;//ʵʱ���Ӳ���
		double m_supermaxtime;//ʵʱ���Ӳ���

		std::vector<CGeoPoint<double> > m_querypolygon;//��ǰ���Բ�ѯ
		std::vector<int> m_selectedsequenceorders;//��ǰ���Բ�ѯ
		std::vector<int> m_selectedcmpoffsets;//��ǰ���Բ�ѯ

		TraceVector m_traces;//����
		TraceVector m_supergrouptraces;//ƫ�ƾ෽λ�Ƿ������
		TraceVector m_anglegrouptraces;//�ǵ���
		TraceVector m_supercmptraces;//������
		TraceVector m_supercmpgrouptraces;//������ƫ�ƾ෽λ�Ƿ������
		TraceVector m_anglesupergrouptraces;//�ǵ�������Ƿ�λ�Ƿ������
		TraceVector m_anglesupercmpgrouptraces;//�������ǵ�������Ƿ�λ�Ƿ������
		std::vector<CAnyGdeDataTrace*> m_gdetraces;//����
		std::vector<CAnyGdeDataTrace*> m_gdesupergrouptraces;//ƫ�ƾ෽λ�Ƿ������
		std::vector<CAnyGdeDataTrace*> m_gdeanglegrouptraces;//�ǵ���
		std::vector<CAnyGdeDataTrace*> m_gdesupercmptraces;//������
		std::vector<CAnyGdeDataTrace*> m_gdesupercmpgrouptraces;//������ƫ�ƾ෽λ�Ƿ������
		std::vector<CAnyGdeDataTrace*> m_gdeanglesupergrouptraces;//�ǵ�������Ƿ�λ�Ƿ������
		std::vector<CAnyGdeDataTrace*> m_gdeanglesupercmpgrouptraces;//�������ǵ�������Ƿ�λ�Ƿ������
		std::vector<int> tracesequenceorders;

		//������Ӳ���
		double m_supergroupminoffset;
		double m_supergroupmaxoffset;
		int m_supergroupoffsetgroup;
		double m_supergroupmindirectionangle;
		double m_supergroupmaxdirectionangle;
		int m_supergroupanglegroup;
		double m_supergroupmininputangle;
		double m_supergroupmaxinputangle;
		int m_supergroupinputanglegroup;

		//�ǵ�������
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

		//����������
		std::vector<CGeoPoint<double> > m_supercmpshotpts;
		std::vector<CGeoPoint<double> > m_supercmpdetectpts;
		std::vector<double> m_supercmpangles;

		// profile record
		ProfileRecord m_profile;

		// observerable
		CAnyObservable *m_observable;

		// host dataset
		CAnyGdeDataSet *m_gdedataset;
		std::vector<CAnyGdeDataSet*> m_multigdedataset;//���ڶ��sgy��ʾ��һ������

		// kinds of strategies for promotion of current profile rendering
		CAnySegyStrategy m_strategy;

		double m_linelength; //�����Ӧ�Ĳ��ߵ��ܳ���

		string m_linename; //��������

		// for render welllayer
		std::vector<std::vector<AnyTraceSample> >m_samples; //��������
		std::vector<std::vector<double> > m_wellpicks; //���ķֲ�����
		std::vector<int> m_linecounts; // �������ߵĸ���
		std::vector<string> m_names; //��������
		std::vector<std::vector<string> > m_subnames; //�������ߵ�����
		std::vector<std::vector<double> > m_nullvalues; //�������ߵ���Чֵ
		std::vector<int> m_positions; // ����λ��
		std::vector<int> m_distances; // �����������̾���
		std::vector<LineStyle> m_wellstyles; // ���������ͣ���ɫ���߿�
		std::vector<std::vector<LineStyle> > m_subwellstyles; // ����ÿ���������ͣ���ɫ���߿�
		std::vector<std::vector<double> > m_subminA; // ����ÿ��������̶�
		std::vector<std::vector<double> > m_submaxA; // ����ÿ�������ҿ̶�
		std::vector<bool> m_iswellshowns; // �Ƿ���ʾ������
		std::vector<std::vector<bool> > m_subiswellshowns; // �Ƿ���ʾ������
		std::vector<bool> m_iswelladjusts; // �Ƿ�Ϊ���켣,���켣����ʾ��ֻ��������ͶӰ
		int m_distancetype; //��������,0:<=,1:>=
		double m_distancelen;//���볤��
		int m_projectiontype; // ͶӰ���ͣ�0:��ֱͶӰ��1�����켣ͶӰ
		double m_projectiondepth; // ��ֱͶӰ���

		// for render earthmodel
		std::vector<CAnyGeologicalCubeFeature::SampleVector> m_lines;
		std::vector<std::vector<int> > m_poses;
		std::vector<string> m_cubenames;
		std::vector<int> featurekinds; // ���ͳɹ�����(��λ/�ϲ�)
		std::vector<LineStyle> m_featurelinestyles; // ���ͳɹ����ͣ���ɫ���߿�
		std::vector<bool> m_isfeatureshowns;  // �Ƿ���ʾ���ͳɹ�
	};
}
#endif