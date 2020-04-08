/*!
 * The AnyMap of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_LOG_TRACK_SECTION_H__
#define __ANYBRIDGE_LOG_TRACK_SECTION_H__

// refer to EXPORT & IMPORT
#include "anybridge.h"

// refer to WELL data model
#include "anybridgedatamodel.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to STL
#include "any/base/anystl.h"

//
namespace AnyBridge
{
	// forward class
	class CAnyLogTrackComponent;

	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyLogTrackSection : public CAnyViewHook
	{
	public:

		/*!
		*2016/9/27: Well pick relate profile
		**/
		struct WellPickProfile
		{
			PolyStyle m_polyStyle;//rendering style
			CGeoRect<double> m_positionMapPort;//map position in component
			AnyWellPick m_pick;//2019/8/9: add well pick property
		};
		typedef std::map<std::string,WellPickProfile> WellPickProfileMap;
		typedef std::map<std::string,WellPickProfile>::iterator wpp_itr;

		/*!
		*2018/5/22: well profile type
		**/
		enum CrossSectionType
		{
			CST_Normal = 0,
			CST_Stratigraphic,
			CST_Structural,
		};

		/*!
		*2018/6/6: cross section practice related
		**/
		struct CrossSectionPracticeRecord
		{
			long m_practiceIdx;
			std::string m_boreIds;
			
			//well profile type
			int m_well_profile_type;
			std::string m_stratigraphic_str;
			double m_structural_tvdss;

			//
			double m_whendo;
			std::string m_whodo;
			std::string m_remark;

			//2018/6/22: add class id
			long m_classid;

			/*!
			*
			**/
			CrossSectionPracticeRecord() 
				: m_practiceIdx(0), m_whendo(0.),m_remark(""),m_whodo(""),m_boreIds(""), m_classid(0)
			{
				m_well_profile_type = CST_Normal;
				m_stratigraphic_str = "";
				m_structural_tvdss = 0.;
			}

			/*!
			*
			**/
			const CrossSectionPracticeRecord &operator=(const CrossSectionPracticeRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				
				m_practiceIdx = other.m_practiceIdx;
				m_boreIds = other.m_boreIds;

				m_well_profile_type = other.m_well_profile_type;
				m_stratigraphic_str = other.m_stratigraphic_str;
				m_structural_tvdss = other.m_structural_tvdss;

				//
				m_whendo = other.m_whendo;
				m_whodo = other.m_whodo;
				m_remark = other.m_remark;
					
				m_classid = other.m_classid;

				//
				return *this;
			}
		};
		typedef std::vector<CrossSectionPracticeRecord> CrossSectionPracticeRecords;

		/*!
		*2018/6/22: log template practice related
		**/
		struct LogTemplatePracticeRecord
		{
			long m_practiceIdx;
			long m_classid;
			std::string m_boreIds;
			std::string m_boreid_desc;
			std::string m_curve_desc;
			double m_whendo;
			std::string m_whodo;
			std::string m_remark;

			/*!
			*
			**/
			LogTemplatePracticeRecord() 
				: m_practiceIdx(0), m_classid(0), m_boreIds(""), m_boreid_desc(""), m_curve_desc(""), m_whendo(0.), m_remark(""), m_whodo("")
			{
			}

			/*!
			*
			**/
			const LogTemplatePracticeRecord &operator=(const LogTemplatePracticeRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				
				m_practiceIdx = other.m_practiceIdx;
				m_classid = other.m_classid;
				m_boreIds = other.m_boreIds;
				m_boreid_desc = other.m_boreid_desc;
				m_curve_desc = other.m_curve_desc;				
				m_whendo = other.m_whendo;
				m_whodo = other.m_whodo;
				m_remark = other.m_remark;

				//
				return *this;
			}
		};
		typedef std::vector<LogTemplatePracticeRecord> LogTemplatePracticeRecords;


		/*!
		*
		**/
		struct LogTrack
		{
			// for coordinate, name etc basic information
			AnyWell m_basic;
			// track component
			CAnyLogTrackComponent *m_track;
			// position in map coord
			CGeoPoint<double> m_position;

			//2016/9/27: Well pick relate profile map
			WellPickProfileMap m_wppMap;

			//2018/5/22: well profile type
			int m_well_profile_type;
			std::string m_stratigraphic_str;
			double m_structural_tvdss;
			
			/*!
			*
			**/
			LogTrack() : m_track(0)
			{
				m_well_profile_type = CST_Normal;
				m_stratigraphic_str = "";
				m_structural_tvdss = 0.;
			}

			/*!
			*
			**/
			LogTrack(const LogTrack &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const LogTrack &operator=(const LogTrack &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_basic = other.m_basic;
				m_track = other.m_track;
				m_position = other.m_position;

				//
				m_wppMap = other.m_wppMap;

				//
				m_well_profile_type = other.m_well_profile_type;
				m_stratigraphic_str = other.m_stratigraphic_str;
				m_structural_tvdss = other.m_structural_tvdss;

				return *this;
			}
		};

		// kinds of vector
		typedef std::vector<LogTrack> TrackVector;
		typedef TrackVector::iterator track_itr;
		typedef TrackVector::const_iterator track_citr;

		/*!
		*2016/5/19: RenderTrack Multiple Thread
		**/
		class RenderTrackTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			RenderTrackTask(int taskcount, int index, CAnyCPUScheduler *scheduler, std::vector<CAnyLogTrackComponent*> &components, \
				CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
			~RenderTrackTask();
			
			void DoExecuteTask();
		private:
			int m_taskcount;
			int m_index;
			CAnyCPUScheduler *m_scheduler;
			
			//
			std::vector<CAnyLogTrackComponent*> m_components;
			CAnyCanvas &m_canvas;
			CAnyView &m_curView;
			const CGeoRect<double> m_validExtent;
			bool m_isDirect;
			int m_namesize;
			double m_labelscale;
			LabelStyle m_lablestyle;
		};

		//record the connected areas/missing parts
		struct BodyConnection
		{
			//
			long m_body_connect_id;		

			long m_from_interpretation_id;
			long m_to_interpretation_id;

			std::string m_formation;

			std::vector<CGeoPoint<double>> m_areas;

			//2019/9/5: record color
			int m_color;

			//
			BodyConnection() : m_body_connect_id(-1), m_from_interpretation_id(-1), m_to_interpretation_id(-1), m_formation(""), m_color(0)
			{
				m_areas.clear();
			}

			//
			~BodyConnection()
			{
			}

			//
			const BodyConnection &operator=(const BodyConnection &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_body_connect_id = other.m_body_connect_id;
				m_from_interpretation_id = other.m_from_interpretation_id;
				m_to_interpretation_id = other.m_to_interpretation_id;
				m_formation = other.m_formation;
				m_areas = other.m_areas;
				m_color = other.m_color;

				return *this;
			}
		};
		typedef std::vector<BodyConnection> BodyConnections;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyLogTrackSection(CAnyView &curView);

		/*!
		*
		**/
		~CAnyLogTrackSection();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool AddLogTrack(LogTrack &track, double min_depth = 0x7fffffff, double max_depth = -0x7fffffff, long boreid = -1);

		/*!
		*2019/7/9: insert log track
		**/
		bool InsertLogTrack(LogTrack &track, int index, double min_depth = 0x7fffffff, double max_depth = -0x7fffffff, long boreid = -1);

		/*!
		*
		**/
		void RemoveAll();

		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype)
		{

		}

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
		*2016/4/15: add para: bool &xFromRight, long &dataOrder
		**/
		bool GetCurCursor(const CGeoPoint<double> &scrPoint, CGeoPoint<double> &scrCursorPoint, CGeoPoint<double> &mapCursorPoint, string &cursorlinename, long &dataOrder);
				
		/*!
		*
		**/
		bool GetCurWellAndComponent(const CGeoPoint<double> &scrPoint, int &wellnum, int &componentnum, int &componenttype, bool &isincomponent);

		/*!
		*
		*/
		bool ZoomFull(const CGeoPoint<double> &scrPoint);
		bool ZoomFull(int wellnum);

		//
		// rendering function
		// 
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);
		
		/*!
		*
		**/
		void RefreshSettings(bool setmapport = true);
		
		/*!
		*
		**/
		void SetFitWidthScale();

		/*!
		*
		**/
		void SaveWellProperty();
				
		/*!
		*
		**/
		void LoadWellProperty();

		//
		//2018/12/12: well property with item_name
		//
		/*!
		*
		**/
		void SaveWellProperty(const std::string &item_name);
				
		/*!
		*
		**/
		void LoadWellProperty(const std::string &item_name);

		//
		//2018/6/6: cross section practice related
		//
		/*!
		*
		**/
		bool LoadCrossSection(long classid = -1); 

		/*!
		*
		**/
		void DoLoadPracticeRecord(CAnyAccessor &accessor, CrossSectionPracticeRecords &practices);

		/*!
		*
		**/
		static bool ComparePracticeIdx(const CrossSectionPracticeRecord &first, const CrossSectionPracticeRecord &second);		

		/*!
		*
		**/
		long CommitCrossSection(CrossSectionPracticeRecord &practiceRecord, CAnyLogTrackSection::WellPickProfileMap &wppMap);

		/*!
		*
		**/
		const CrossSectionPracticeRecord &GetPracticeRecord(int index);

		/*!
		*
		**/
		int GetPracticeCount();

		/*!
		*
		**/
		bool DeletePracticeRecord(long practiceIdx);

		/*!
		*
		**/
		bool LoadPracticeParameter(long practiceIdx, CAnyLogTrackSection::WellPickProfileMap &wppMap);

		/*!
		*
		**/
		bool UpdateRemarkPracticeRecord(long practiceIdx, const string &remark);

		//
		//2018/6/6: log template practice related
		//
		/*!
		*
		**/
		bool LoadLogTemplate(); 

		/*!
		*
		**/
		void DoLoadPracticeRecord_LogTemplate(CAnyAccessor &accessor, LogTemplatePracticeRecords &practices);

		/*!
		*
		**/
		static bool ComparePracticeIdx_LogTemplate(const LogTemplatePracticeRecord &first, const LogTemplatePracticeRecord &second);		

		/*!
		*
		**/
		long CommitLogTemplate(LogTemplatePracticeRecord &practiceRecord, AnyBridge::AnyWellLogTrace &trace);

		/*!
		*
		**/
		const LogTemplatePracticeRecord &GetPracticeRecord_LogTemplate(int index);

		/*!
		*
		**/
		int GetPracticeCount_LogTemplate();

		/*!
		*
		**/
		bool DeletePracticeRecord_LogTemplate(long practiceIdx);

		/*!
		*
		**/
		char *LoadPracticeParameter_LogTemplate(long practiceIdx, long &total_length);

		/*!
		*
		**/
		bool UpdateRemarkPracticeRecord_LogTemplate(long practiceIdx, const string &remark);

		//
		//2019/8/9: render sand body connection
		//
		/*!
		*
		**/
		void LoadBodyConnection();

		/*!
		*
		**/
		void SaveBodyConnection();

		/*!
		*adjust by db records
		**/
		void AdjustBodyConnection();

		
		//
		//2019/8/8: find sand body connection in (BodyConnections m_body_connect_areas)
		//
		/*!
		*
		**/
		int FindBodyConnection(const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		void RemoveBodyConnection(int idx);

		/*!
		*
		**/
		void DoRemoveBodyConnection(long body_connect_id, long from_interpretation_id, long &to_interpretation_id);

		/*!
		*
		**/
		int FindSandBody(const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		void ConnectSandBody(const std::vector<CGeoPoint<double> > &scrPts);

		//
		//2019/9/5: set body connection color (BodyConnections m_body_connect_areas_color)
		//
		/*!
		*
		**/
		void SetBodyConnectionColor(int idx, int color);

		/*!
		*
		**/
		int GetBodyConnectionColor(const BodyConnection &bc);

		/*!
		*adjust by db records
		**/
		void AdjustBodyConnectionColor();
	private:
		//
		//
		//
		/*!
		* deprecated, and well order shouldn't be distorbed
		**/
		static bool CompareWellIdx(const LogTrack &first, const LogTrack &second)
		{
			return first.m_basic.m_wellIdx < second.m_basic.m_wellIdx;
		}

		//
		//2019/8/8: render sand body connection
		//
		/*!
		*
		**/
		void DoRenderSandBodyConnection(CAnyCanvas &canvas);

	public:
		// 
		TrackVector m_tracks;
		LabelStyle m_lablestyle;
		LabelStyle m_tracelablestyle;
		double m_widthscale;
		double m_distancescale;
		bool m_issamedistance;
		double m_labelscale;
		double m_tracelabelscale;
		int m_namesize;
		int m_tracenamesize;
		std::vector<double> m_startdepths;
		std::vector<double> m_enddepths;
		std::vector<CGeoPoint<double> > m_shiftorstretchpts;
		CGeoPoint<double> m_titlePtRate;//2016/3/2: adjust title's position

		//2016/9/27: well profile, render well pick related profile
		bool m_isWellProfile;

		//2018/5/22: backup of the start/end depth
		std::vector<double> m_bk_startdepths;
		std::vector<double> m_bk_enddepths;

		//2019/7/10: stratigraphic compared well
		std::string m_stratigraphic_cmp_well;

		//2019/8/6: sand body connection?
		bool m_is_sand_body_connected;
		bool m_is_sand_body_connected_manually;

		//2019/8/12: well layer's item name/boreids
		std::string m_item_name;
		std::vector<long> m_boreids;

	private:
		//2018/6/6: practice related
		CrossSectionPracticeRecords m_practices;

		//2018/6/22: log template practice related
		LogTemplatePracticeRecords m_practices_log_template;

		//2019/8/8: sand body connection
		//interpretation results
		std::map<int,std::vector<AnyWellInterpretation> > m_interpretation_map;
		
		//wellorder - (current m_interpretation_id - next m_interpretation_id)
		std::map<int,std::map<long,long>> m_body_connect_map;
		std::map<int,std::map<long,long>> m_body_connect_map_loaded;

		//
		BodyConnections m_body_connect_areas;

		//2019/9/5: record color
		BodyConnections m_body_connect_areas_color;
		BodyConnections m_body_connect_areas_color_loaded;

		//2019/8/13: sand body itself
		BodyConnections m_sand_bodys;
	};
}
#endif