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
#ifndef __ANYVIEW_BASIC_DEF_H__
#define __ANYVIEW_BASIC_DEF_H__

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

// namespace
namespace AnyMap
{
	// pixel format against rendering buffer
	#define AGG_BGR24
	#define SYSTEM_BPP 24

	/*!
	*
	**/
	enum CommandType
	{
		CT_Invalid = -1,
		CT_Select,
		CT_Pan,
		CT_Timer
	};

	/*!
	*
	**/
	enum MapOperation
	{
		MO_Default					= 0,
		MO_Edit							= 1 << 1,
		MO_Pan							= 1 << 2,
		MO_Zoom_In					= 1 << 3,
		MO_Zoom_Out				= 1 << 4,
		MO_Zoom_Extent			= 1 << 5,
		MO_Zoom_Full				= 1 << 6,
		MO_Pick_By_Point		= 1 << 7,
		MO_Pick_By_Rect		= 1 << 8,
		MO_Pick_By_Poly		= 1 << 9,
		MO_Pick_By_Line		= 1 << 10,
		MO_Pick_By_Circle     = 1 << 11,
	};

	/*!
	*
	*/
	enum MouseFlag
	{
		MF_Left = 0,
		MF_Right,
		MF_Middle
	};

	/*!
	*
	**/
	enum ViewType
	{
		VT_Unknown,
		VT_Win,
		VT_Max,
	};

	/*!
	*
	**/
	struct ScreenPort
	{
		// Base point for mapping 
		// between view state's extent and map extent
		CGeoPoint<double> m_base;
		// DC base
		CGeoPoint<double> m_bufBase;
		// Extent of current view state 
		// corresponding to the whole screen's extent
		CGeoRect<double> m_extent;

		/*!
		*
		**/
		ScreenPort()
		{
		}

		/*!
		*
		**/
		const ScreenPort &operator = (const ScreenPort &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			//
			m_base = other.m_base;
			m_bufBase = other.m_bufBase;
			m_extent = other.m_extent;

			//
			return *this;
		}
	};

    /*!
	*
	**/
    struct MapPort
    {
		//
        CGeoPoint<double> m_base;
        CGeoRect<double> m_extent;

		//
        double m_scale;
        double m_angle;
		
		//
		MapPort() : m_scale(0), m_angle(0)
		{

		}

		//
		const MapPort &operator = (const MapPort &other)
		{
			//
			if(this == &other)
			{
				return *this;
			}

			//
			m_base = other.m_base;
			m_extent = other.m_extent;
			m_scale = other.m_scale;
			m_angle = other.m_angle;

			//
			return *this;
		}
    };
}
#endif