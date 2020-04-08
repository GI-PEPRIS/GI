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
#ifndef __ANYBRIDGE_LOG_TRACK_COMPONENT_H__
#define __ANYBRIDGE_LOG_TRACK_COMPONENT_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to ANYRECT
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to ANYCANVAS
#include "any/map/anycanvas.h"
#include "any/map/anyviewhook.h"
using namespace AnyMap;
// namespace
namespace AnyBridge
{
	/*!
	* side layout
	**/
	enum Layout
	{
		Layout_Stack = 0,
		Layout_Left,
		Layout_Right,
	};
	
	/*!
	*
	**/
	enum componenttype
	{
		Log_Unknown = 0,
		Log_Curvetrack,
		Log_Lithtrack,
		Log_Picktrack,
		Log_Texttrack,
		Log_Ticktrack,
		Log_Seistrack,
		Log_Sedimentary_Cycle,//2016/1/28: CAnyLogSedimentaryCycle
		Log_Dlistrack,
		Log_Azimuthtrack,
		Log_Spectrumtrack,
	};

	/*!
	*2016/2/18: for all component
	**/
	enum ComponentOperation
	{
		CO_Default = 0,
		CO_Reshape,
		CO_Drag,
	};

	//2018/3/19: null value range
	struct NullValue
	{
		double m_left_null_value;
		double m_right_null_value;

		//
		NullValue()
		{
			m_left_null_value = ANY_NAN;
			m_right_null_value = ANY_NAN;
		}
	};
	typedef std::vector<NullValue> NullValues;

	/*!
	*2016/2/18: for curves in the component
	**/
	struct CurveProperty 
	{
		std::string m_name;
		std::string m_showname;
		std::string m_unit;
		ColorStyle m_color;
		bool m_islineshown;
		double m_linewidth;
		LineStyle m_linepattern;
		bool m_islinelog;
		bool m_islinegrid;
		double m_linenullvalue;

		//2016/12/20: left/right value of a curve
		double m_leftValue;
		double m_rightValue;

		//2017/5/19: tick number
		int m_tickNum;
		
		//2018/3/19: record multiple null value
		NullValues m_line_null_values;

		//2018/10/9: default line/square line/samples/horizontal stick
		int m_render_style;

		CurveProperty() : m_name(""), m_showname(""), m_unit(""), m_islineshown(true), m_linewidth(1.), m_islinelog(false), m_islinegrid(false), m_linenullvalue(ANY_NAN),\
			m_leftValue(ANY_NAN),m_rightValue(ANY_NAN),m_tickNum(2),m_render_style(0)
		{
			//2018/3/19: multiple null value
			m_line_null_values.clear();
		}
	};
	typedef std::vector<CurveProperty> CurveProperties;

	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyLogTrackComponent
	{
		// relatives
		friend class CAnyLogTrackSection;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyLogTrackComponent();

		/*!
		*
		**/
		virtual ~CAnyLogTrackComponent();

	public:
		//
		//
		//
		/*!
		* extent per log track in screen coords
		**/
		void SetTrackWidth(double width)
		{
			m_width = width;
		}

		/*!
		*
		**/
		double GetTrackWidth()
		{
			return m_width;
		}

		//
		// coordinate conversion
		//
		/*!
		*	minx, max means sample extent, miny, maxy means depth extent
		**/
		void SetAxisExtent(CGeoRect<double> &extent)
		{
			m_mapExtent = extent;
		}

		/*!
		*
		**/
		void Map2Scr(const CGeoPoint<double> &mapPt, CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		void Scr2Map(const CGeoPoint<double> &scrPt, CGeoPoint<double> &mapPt);

		//
		// decorator interface
		//
		/*!
		* explicit decorator
		**/
		void SetDecorator(CAnyLogTrackComponent *component, short side)
		{
			assert(component);
			m_component = component;
			m_side = side;
		}

		//
		//
		//
		/*!
		* the intention of parent is to calculate SCR EXTENT for each component, 2016/2/1: add parameter bool isDirect = OnPaint(...,isDirect)
		**/
		virtual void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		//
		//2016/2/18: common methods for all components
		//
		/*!
		*
		**/
		void SetComponentOperation(int operation);

		/*!
		*
		**/
		int GetComponentOperation();
		
		/*!
		*2017/9/14: render component border
		**/
		void DoRenderComponentBorder(CAnyCanvas &canvas, CAnyView &curView, double &shift_scale, int &shift_count, std::vector<double> &mds, std::vector<double> &total_shifts, double &min_shift, double &max_shift, bool isrender = true);

		/*!
		*
		**/
		double CalculateMaxAzimuth();
		
		/*!
		*
		**/
		void CalculateDatashift(double cur_depth, double &shift_scale, int &shift_count, std::vector<double> &mds, std::vector<double> &total_shifts, double &min_shift, double &max_shift, double scale, CGeoPoint<double> &mapCoord,bool is_offset_mode = false);
		void MoveScrCoordbywelladjust(CGeoPoint<double> &scrCoord, CAnyView &curView, double &shift_scale, int &shift_count, std::vector<double> &mds, std::vector<double> &total_shifts, double &min_shift, double &max_shift,double scale,bool is_offset_mode = false );
	
		/*!
		*
		**/
		double GetCurrentShift(double cur_depth, int &low, int &high);

		/*!
		*2019/6/26: render the label within the scrExtent
		**/
		static double DoRenderLabelWithinExtent(CAnyCanvas &canvas, LabelStyle &labelStyle, const CGeoPoint<double> &scrCoord, const CGeoRect<double> &scrExtent, std::string &label, bool is_reset_x = true);

	public:
		// layout position - left,top
		CGeoPoint<double> m_position;
		// layout width
		double m_width;
		// layout extent
		CGeoRect<double> m_scrExtent;
		// layout direction
		short m_side;
		// its direct neighbor
		CAnyLogTrackComponent *m_component;
		// axis (map) extent for this track
		CGeoRect<double> m_mapExtent;
		// component type
		short m_componenttype;
		// whether shown on screen
		bool m_isshown;
		// name of component
		string m_name;

		//2016/2/18: record map operation in the current component
		int m_mapOperation;

		//2016/2/26: label style could be different from that of others
		LabelStyle m_componentLabelStyle;
		double m_curWidthScale;//2016/5/3: component's width maybe different from that of others

		//2017/9/12: well adjust variables
		std::vector<double> m_mds;
		std::vector<double> m_shifts_total;
		
		std::vector<double> m_shifts_x;
		std::vector<double> m_shifts_y;
		double m_azimuth;

		std::vector<double> m_mds_rendered;
		std::vector<double> m_shifts_rendered;
		bool m_is_render_by_well_trajectory;

		//2017/9/19: record left/right screen border pts
		std::vector<CGeoPoint<double> > m_border_left_scr_pts;
		std::vector<CGeoPoint<double> > m_border_right_scr_pts;

		//2017/9/13: record current component id
		int m_component_id;

		//2018/3/14: min/max depth
		double m_min_depth;
		double m_max_depth;
	private:
		int m_componentOp;//2016/2/18:record ComponentOperation
	};
}
#endif

