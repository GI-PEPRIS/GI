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
#ifndef __ANYBRIDGE_LOG_LAYER_H__
#define __ANYBRIDGE_LOG_LAYER_H__

// refer to EXPORT & IMPORT macroes
#include "anybridge.h"
#include "anybridgedatamodel.h"

// refer to geom basic
#include "any/base/anygeom.h"
#include "any/base/anymediator.h"
#include "any/base/anystl.h"
using namespace AnyBase;

// refer to observer & mediator pattern
#include "any/base/anymediator.h"
#include "any/base/loki\visitor.h"
using namespace AnyBase;
using namespace AnyBase::Loki;

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;
#include "any/gfs/anyservicebasic.h"
using namespace AnyRCF;

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyLogLayer : public CAnyViewHook, public CAnyObservable, public CAnyMediator
	{

	public:
		
		//2018/10/22: cross section line
		struct CrossSectionLine 
		{
			bool m_isShown;
			long m_practiceIdx;
			std::vector<std::string> m_wellnames;
			std::vector<CGeoPoint<double> > m_points;
			std::string m_remark;//2019/1/24: remark
			/*!
			*
			**/
			CrossSectionLine() : m_isShown(false), m_practiceIdx(-1), m_remark("")
			{
				m_wellnames.clear();
				m_points.clear();
			}

			/*!
			*
			**/
			CrossSectionLine(const CrossSectionLine &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const CrossSectionLine &operator=(const CrossSectionLine &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_isShown = other.m_isShown;
				m_practiceIdx = other.m_practiceIdx;
				m_wellnames = other.m_wellnames;
				m_points = other.m_points;
				m_remark = other.m_remark;

				return *this;
			}
		};
		typedef std::map<long, CrossSectionLine> CrossSectionLineMap;

	public:
		/*!
		*
		**/
		CAnyLogLayer(CAnyView &curView);

		/*!
		*
		**/
		~CAnyLogLayer();

	public:
		//
		// OBSERVER and MEDIATOR interface
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
		void SetMediator(CAnyMediator *seismicLayer)
		{
			m_seismicLayer = seismicLayer;
		}

		/*!
		* return encoding block from CAnyLogLayer
		**/
		void PickLogTraceData(const CGeoPoint<double> &pos, void **data, int &number);
				
		/*!
		*
		**/
		void PickLogNames(const CGeoPoint<double> &pos, std::vector<string> &names, std::vector<double> &nullvalues, int &islasorlgcreport);
				
		/*!
		*
		**/
		void PickWellAdjustData(const CGeoPoint<double> &pos, std::vector<double> &times, std::vector<CGeoPoint<double> > &welladjusts);

		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype)
		{

		}

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

		/*!
		*
		**/
		bool Query(const CGeoRect<double> &rect, bool isCircle = false);

		/*!
		*
		**/
		bool Query(const std::vector<CGeoPoint<double> > &poly);
		
		/*!
		*
		**/
		bool QueryLine( const std::vector<CGeoPoint<double> > &line, bool is_well_pick_profile);
		bool IsIntersect( CGeoPoint<double> p1, CGeoPoint<double> p2, CGeoPoint<double> p3, CGeoPoint<double> p4 );
		double CrossProduct( CGeoPoint<double> pii, CGeoPoint<double> pj, CGeoPoint<double> pk );

		//
		//
		//
		/*!
		*
		**/
		void Load(long classid);

		/*!
		*
		**/
		static int SaveWellbasicandBore(AnyWell &well);
		static int SaveWellbasicandBore(AnyWell &well, CAnyAccessor &accessor);
		static int SaveWellbasicandBore(AnyWell &well, CAnyAccessor &accessor, int propertyid, int boreid);
		
		/*!
		*
		**/
		double FromBaseToRelate( double basevalue, std::vector<double> &basetickvalues, std::vector<double> &relatetickvalues );
				
		/*!
		*
		**/
		void GetCurvesDataByWellid(int wellid, std::vector<string> &curvenames, std::vector<std::vector<AnyBridge::AnyTraceSample> > &curvedatas);
		void FromLogTraceToCurvesData(AnyWellLogTrace &trace, int wellnum, std::vector<string> &curvenames, std::vector<std::vector<AnyBridge::AnyTraceSample> > &curvedatas);
		/*!
		*
		**/
		bool InitGFSClient(string gfspara);
		void UploadGFS(string localfilepath, string gfsname);
		void GetLogTraceGFS(AnyWellLogTrace &trace, int wellnum);

		static bool InitWellLogcurve(CAnyAccessor &accessor);

		//
		//2018/5/23:new methods
		//
		/*!
		*reset KBE/KB/GE/TVDSS
		**/
		static void CalculateWellDepths(AnyWell &well);

		/*!
		*reset m_x_coord_bottom_hole,m_y_coord_bottom_hole
		**/
		static void CalculateWellPos(CAnyAccessor &accessor, AnyWell &well, const std::string &item_name);

		/*!
		*update well basic information
		**/
		static bool UpdateWellbasic(std::vector<AnyWell> &wells);
		static bool UpdateWellbasic(AnyWell &well);
		static bool UpdateWellbasic(AnyWell &well, CAnyAccessor &accessor);

		//
		//2018/8/20: get well traces(paths)
		//
		/*!
		*
		**/
		void GetWellTraces(bool is_reset = false, int trace_order = -1);

		/*!
		*
		**/
		bool QueryByPoint(const CGeoPoint<double> &scrPoint, std::vector<int> &cur_pickedpoints);

	private:
		/*!
		*2018/11/1: render label, which includes handling intersect labels
		**/
		bool DoRenderLabel(CAnyCanvas &canvas, LabelStyle &labelStyle, const CGeoPoint<double> &pos, const std::string &label, CGeoPoint<double> *alongPts = 0, int num = 0);

		/*!
		*2019/3/22: load font/size
		**/
		void LoadFontAndSize(CAnyCanvas &canvas, LabelStyle &labelStyle);

	public:
		//
		CGeoRect<double> m_extent;
		std::vector<CGeoPoint<double> > m_points;
		std::vector<std::vector<CGeoPoint<double> > > m_traces;
		std::vector<bool> m_isshowwells;//显示井
		bool m_isshowtrace;// 显示井轨迹
		bool m_isshowwellbegin;//显示井口
		bool m_isshowwellend;//显示目的层位
		LineStyle m_tracestyle; // 井轨迹线型，颜色，线宽
		std::vector<AnyWell> m_basics;
		std::vector<int> pickedpoints;
		
		// for mediator calling and to get pointer of current seismic layer from existing hooks
		CAnyMediator *m_seismicLayer;
		void *m_masterclient;
		void *m_eventclient;
		std::vector<ServiceHandle> m_chunkhandles;
		std::vector<void*> m_chunkclients;
		string m_gfspara;
		string m_gfsname;
		string m_localfilepath;

		//2018/10/22: cross line map(practice id - CrossSectionLine)
		CrossSectionLineMap m_cross_line_map;

		//2018/10/31: highlighted wells
		std::map<int,int> m_hightlight_wells;

		//2018/12/6: record item name
		std::string m_item_name;

		//2019/2/28: well profile?
		bool m_is_well_profile_mode;
		std::vector<int> m_pickedpoints_well_profile;

		//2019/3/21: font and size... 
		LabelStyle m_lablestyle;

	private:
		//2018/11/1: rectangle positions for labels
		std::vector<CGeoRect <double>> m_labelRectPositions;

	};
}

#endif
