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
#ifndef __ANYVIS_AXISES_H__
#define __ANYVIS_AXISES_H__

// refer to export macro
#include "anyvis.h"

// refer to canvas
#include "any/map/anyview.h"
#include "any/map/anycanvas.h"
using namespace AnyMap;

// namespace
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyAxises
	{
	public:

		/*!
		*2015/6/3
		**/
		enum AxisTickType
		{
			AT_DEFAULT = 0,
			AT_TIME,
			AT_STRING,
		};


		/*!
		*
		**/
		struct AxisInfo
		{
			//title
			std::string m_titleX;
			std::string m_titleY;
			
			//ticks
			int m_tickNumX;
			int m_tickNumY;
			
			//extent
			CGeoRect<double> m_mapExtent;
			
			//integer
			bool m_isXInteger;
			bool m_isYInteger;

			//log
			bool m_isXLog;
			bool m_isYLog;

			//zero start
			bool m_isXZeroStart;
			bool m_isYZeroStart;

			double m_tickSizeX;
			double m_tickSizeY;

			double m_TitleSizeX;
			double m_TitleSizeY;

			//2016/11/15: right y properties
			std::string m_titleY1;
			int m_tickNumY1;
			CGeoRect<double> m_mapExtent1;
			bool m_isYInteger1;
			bool m_isYLog1;
			bool m_isYZeroStart1;
			double m_tickSizeY1;
			double m_TitleSizeY1;
			
			/*!
			*
			**/
			AxisInfo()
			{		
				Init();
			}

			void Init()
			{
				m_titleX = "";
				m_titleY = "";
				m_tickNumY = -1;
				m_tickNumX = -1;
				m_isXInteger = false;
				m_isYInteger = false;
				m_isXLog = false;
				m_isYLog = false;

				m_isXZeroStart = false;
				m_isYZeroStart = false;

				//
				m_mapExtent.m_minX = ANY_INVALIDCOORD;
				m_mapExtent.m_maxX = ANY_INVALIDCOORD;
				m_mapExtent.m_minY = ANY_INVALIDCOORD;
				m_mapExtent.m_maxY = ANY_INVALIDCOORD;

				m_tickSizeX = 7.;
				m_tickSizeY = 7.;

				m_TitleSizeX = 8.;
				m_TitleSizeY = 8.;

				//2016/11/15: right y properties
				m_titleY1 = "";
				m_tickNumY1 = -1;
				m_mapExtent1.m_minX = ANY_INVALIDCOORD;
				m_mapExtent1.m_maxX = ANY_INVALIDCOORD;
				m_mapExtent1.m_minY = ANY_INVALIDCOORD;
				m_mapExtent1.m_maxY = ANY_INVALIDCOORD;
				m_isYInteger1 = false;
				m_isYLog1 = false;
				m_isYZeroStart1 = false;
				m_tickSizeY1 = 7.;
				m_TitleSizeY1 = 8.;
			}

			/*!
			*
			**/
			const AxisInfo &operator=(const AxisInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_titleX = other.m_titleX;
				m_titleY = other.m_titleY;

				m_tickNumX = other.m_tickNumX;
				m_tickNumY = other.m_tickNumY;

				m_mapExtent = other.m_mapExtent;

				m_isXInteger = other.m_isXInteger;
				m_isYInteger = other.m_isYInteger;

				m_isXLog = other.m_isXLog;
				m_isYLog = other.m_isYLog;

				m_isXZeroStart = other.m_isXZeroStart;
				m_isYZeroStart = other.m_isYZeroStart;

				m_tickSizeX = other.m_tickSizeX;
				m_tickSizeY = other.m_tickSizeY;

				m_TitleSizeX = other.m_TitleSizeX;
				m_TitleSizeY = other.m_TitleSizeY;

				//2016/11/15: right y properties
				m_titleY1 = other.m_titleY1;
				m_tickNumY1 = other.m_tickNumY1;
				m_mapExtent1 = other.m_mapExtent1;
				m_isYInteger1 = other.m_isYInteger1;
				m_isYLog1 = other.m_isYLog1;
				m_isYZeroStart1 = other.m_isYZeroStart1;
				m_tickSizeY1 = other.m_tickSizeY1;
				m_TitleSizeY1 = other.m_TitleSizeY1;

				return *this;
			}
		};

	protected:
		//
		enum AxisPosition
		{
			AP_Left		= 1,
			AP_Right	= 1 << 1,
			AP_Top		= 1 << 2,
			AP_Bottom	= 1 << 3,
			AP_Middle	= 1 << 4,
			AP_All		= 1 << 5,
		};
	protected:
		//
		//
		//
		/*!
		* = 0 means not to adopt view hook mechanism
		**/
		CAnyAxises(CAnyView *view = 0);

		/*!
		*
		**/
		virtual ~CAnyAxises();

	protected:
		//
		//
		//
		/*!
		*
		**/
		AnyMap::LineStyle SetAxisLineStyle(const AnyMap::LineStyle &lineStyle);

		/*!
		*
		**/
		AnyMap::LabelStyle SetAxisLabelStyle(const AnyMap::LabelStyle &labelStyle);

		/*!
		*
		**/
		void SetAxisExtent(const CGeoRect<double> &scrExtent, const CGeoRect<double> &mapExtent,
			bool isXLog = false, bool isYLog = false, bool isInitialized = false);

		/*!
		*
		**/
		bool IsExtentInitialized(const CGeoRect<double> &extent);

		/*!
		*
		**/
		static bool IsExtentLimitationSame(const CGeoRect<double> &extent);

		/*!
		*
		**/
		void SetAxisGap(short gap);

		//
		//
		//
		/*!
		*
		**/
		void RenderLinearAxis(CAnyCanvas &canvas, int ticks, unsigned short flag, const char *name, bool isLog = false, 
			bool arrowDirection = true, int order = 0, int pos = 0, bool isInteger = false, bool isDirectTick = false, bool isLogAxis = false);

		/*!
		*
		**/
		virtual void DoRenderAxisLine(CAnyCanvas &canvas, CGeoPoint<double> *pts, unsigned short flag, bool arrowDirection, short order);

		/*!
		*
		**/
		virtual void DoRenderAxisTicks(CAnyCanvas &canvas, CGeoPoint<double> *pts, int ticks, unsigned int flag, bool isLog, bool arrowDirection, bool isInteger, bool isDirectTick, bool isLogAxis);

		/*!
		*
		**/
		virtual void DoRenderAxisName(CAnyCanvas &canvas, CGeoPoint<double> *pts, unsigned int flag, const char *name, int position = 0);

		//
		//
		//
		/*!
		*
		**/
		virtual void Map2Scr(CGeoPoint<double> &mapPt, CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		virtual void Scr2Map(CGeoPoint<double> &scrPt, CGeoPoint<double> &mapPt);

	private:
		/*!
		*2015/5/25
		**/
		string GetTimeTick(bool isX, double val, bool isInterger);

		/*!
		*2015/6/4
		**/
		bool GetStringTicks(bool isX, int &ticks, bool &isDirectTick);

	public:
		//
		//
		//
		/*!
		*
		**/
		static string GetAxisName(const char *name, bool isForAxis = true);

		/*!
		*2015/6/9
		**/
		static int GetLogTickCount(double min, double max, std::string &minStr, std::string &maxStr);

		/*!
		*
		**/
		static int MakeExtentInteger(CGeoRect<double> &mapExtent, bool is_x);

		/*!
		*2019/6/13: adjust invalid extent
		**/
		static void AdjustExtent(CGeoRect<double> &extent);

		/*!
		*
		**/
		static int AdjsutTickDigitDecimal(char *tick, double val);

	protected:
		//
		AnyMap::LineStyle m_axisLineStyle;
		AnyMap::LabelStyle m_axisLabelStyle;

		//
		CGeoRect<double> m_scrExtent;
		CGeoRect<double> m_mapExtent;
		short m_axisGap;

		// pointer to current view for map2scr etc operations
		CAnyView *m_view;
		// since the units of X and Y coordinate aren't the same
		double m_xScale;
		double m_yScale;

		//
		bool m_isAutoMode;
		AxisInfo m_axisInfo;
		AxisInfo m_lastAxisInfo;

		//for AnyScatterLayer 
		CGeoRect<double> m_layerScrExtent;
		bool m_isLayerMode;

		//2014.8.29
		bool m_isArrowShown;
		bool m_isRight;

		//2015/6/3
		int m_xTickType;
		int m_yTickType;

		//2015/6/3
		std::vector<std::string> m_xTickStrs;
		std::vector<std::string> m_yTickStrs;

		//2015/10/8
		bool m_isReverseX;
		bool m_isReverseY;

		//2018/11/30: show ticks
		bool m_show_tick_x;
		bool m_show_tick_y;

	};
}

#endif