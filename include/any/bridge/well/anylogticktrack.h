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
#ifndef __ANYBRIDGE_LOG_TICK_TRACK_H__
#define __ANYBRIDGE_LOG_TICK_TRACK_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to its parent
#include "anylogtrackcomponent.h"

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyLogTickTrack : public CAnyLogTrackComponent
	{
	public:
		/*!
		*
		**/
		enum TickType
		{
			TT_Scr,
			TT_Map,
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyLogTickTrack();

		/*!
		*
		**/
		~CAnyLogTickTrack();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		/*!
		*
		**/
		void DoRenderBaseTTMap(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		/*!
		*
		**/
		void DoRenderBaseTTScr(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		/*!
		*
		**/
		void DoRenderRelateTTMap(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		/*!
		*
		**/
		void DoRenderRelateTTScr(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
		
		/*!
		*
		**/
		double FromBaseToRelate(double basevalue);
				
		/*!
		*
		**/
		double FromRelateToBase(double relatevalue);

		//
		//2018/3/14: save/load
		//
		/*!
		*
		**/
		unsigned char *DoEncoding(long long &length);

		
		/*!
		*
		**/
		bool DoDecoding(unsigned char* parameter, const long &len = 0);

	public:
		int m_ticktype;//刻度间隔或像素间隔
		double m_mapinterval;//刻度间隔间距
		bool m_textonleft;//刻度文字居左
		bool m_isshowbasetickvalues;//是否显示基准刻度还是显示对应刻度
		std::vector<double> m_basetickvalues;//刻度对应关系，基准刻度
		std::vector<double> m_relatetickvalues;//刻度对应关系，对应刻度

		//2019/7/31: tick integer?
		bool m_is_integer;
	};
}
#endif