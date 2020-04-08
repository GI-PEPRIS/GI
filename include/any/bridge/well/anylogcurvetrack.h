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
#ifndef __ANYBRIDGE_LOG_CURVE_TRACK_H__
#define __ANYBRIDGE_LOG_CURVE_TRACK_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to parent
#include "anylogtrackcomponent.h"

// refer to ANYTRACESAMPLE
#include "..\anybridgedatamodel.h"

// namespace
namespace AnyBridge
{
	/*!
	* also as a decorator
	**/
	class ANYBRIDGE_CLASS CAnyLogCurveTrack : public CAnyLogTrackComponent
	{
	public:
		/*!
		*2016/1/19
		**/
		struct FillingLineProperty
		{
			std::string m_name;
			double m_step;
			
			int m_type;
			int m_color;
			bool m_isAlpha;
			double m_width;
			
			std::string m_minCurveName;
			std::string m_maxCurveName;

			//2016/2/16: other line style
			int m_type1;
			int m_color1;
			bool m_isAlpha1;

			/*!
			*
			**/
			FillingLineProperty()
			{
				m_name = "";
				m_step = 1.;

				m_type = 0;
				m_color = 0;
				m_isAlpha = true;
				m_width = 1.;

				m_minCurveName = "";
				m_maxCurveName = "";

				//2016/2/16: other line style
				m_type1 = 0;
				m_color1 = 0;
				m_isAlpha1 = true;
			}

			/*!
			*
			**/
			bool IsValid()
			{
				if (m_name.size() && m_minCurveName.size() && m_maxCurveName.size() && m_minCurveName != m_maxCurveName && m_type >= 0 && m_color >= 0 && m_step > 0. && m_type1 >= 0 && m_color1 >= 0 )
				{
					return true;
				}

				return false;
			}
		};
		typedef std::vector<FillingLineProperty> FillingProperties;

		/*!
		*2016/2/16: 
		**/
		struct GridProperty
		{
			bool m_horizon_show;
			//int m_horizon_color;
			int m_horizon_big_cell;
			int m_horizon_small_cell;
			int m_horizon_thin_line;
			int m_horizon_mid_line;
			int m_horizon_thick_line;
			
			bool m_vertical_show;
			//int m_vertical_color;
			int m_vertical_big_cell;
			int m_vertical_small_cell;

			//2018/7/24: specific line settings
			int m_horizon_color;//big cell color
			int m_horizon_big_cell_line_style; 
			double m_horizon_big_cell_line_width; 
			int m_horizon_small_cell_line_color; 
			int m_horizon_small_cell_line_style; 
			double m_horizon_small_cell_line_width; 

			int m_vertical_color;//big cell color
			int m_vertical_big_cell_line_style; 
			double m_vertical_big_cell_line_width; 
			int m_vertical_small_cell_line_color; 
			int m_vertical_small_cell_line_style; 
			double m_vertical_small_cell_line_width; 

			//
			double m_horizon_map_interval;

			GridProperty()
			{
				m_horizon_show = true;
				m_horizon_color = 0;
				m_horizon_big_cell = 2;
				m_horizon_small_cell = 5;
				m_horizon_thin_line = 1;
				m_horizon_mid_line = 5;
				m_horizon_thick_line = 25;

				m_vertical_show = true;
				m_vertical_color = 0;
				m_vertical_big_cell = 2;
				m_vertical_small_cell = 5;

				//2018/7/24: specific line settings
				m_horizon_big_cell_line_style = 0; 
				m_horizon_big_cell_line_width = 2.; 
				m_horizon_small_cell_line_color = 0; 
				m_horizon_small_cell_line_style = 0; 
				m_horizon_small_cell_line_width = 1.; 

				m_vertical_big_cell_line_style = 0; 
				m_vertical_big_cell_line_width = 2.; 
				m_vertical_small_cell_line_color = 0; 
				m_vertical_small_cell_line_style = 0; 
				m_vertical_small_cell_line_width = 1.; 

				m_horizon_map_interval = 100.;
			}
		};
		typedef std::vector<GridProperty> GridProperties;

		/*!
		*2017/2/10: curve type for variable m_isSquareLineMode
		**/
		enum CurveType
		{
			CT_Normal = 0,
			CT_Square,
			CT_Sample_Point,

			//2018/10/9: new render style
			CT_Horizontal_Stick,
		};


	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyLogCurveTrack();

		/*!
		*
		**/
		~CAnyLogCurveTrack();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
	
		//
		//
		//
		/*!
		*2016/3/15: save/load; 2018/7/9: add para 'data_desc'
		**/
		unsigned char *DoEncoding(long long &length, std::string &data_desc = std::string());

		
		/*!
		*2018/2/28: add parameter const long &len = 0
		**/
		bool DoDecoding(unsigned char* parameter, const long &len = 0);

		//
		//2019/4/22: decoding/encoding methods
		//
		unsigned char *DoEncoding1(long long &length, std::string &data_desc = std::string());
		bool DoDecoding1(unsigned char* parameter, const long &len = 0);
		
		unsigned char *DoEncodingTraceIds(long long &length);
		bool DoDecodingTraceIds(unsigned char* parameter, const long &len = 0);


	private:
		/*!
		*
		**/
		void DoRenderFillingLines(CAnyCanvas &canvas, CAnyView &curView);

		/*!
		*
		**/
		void GetFillingLinePts(const std::string &name, std::vector<CGeoPoint<double>> &pts);

		/*!
		*
		**/
		void GetFillingLineMinMax(std::vector<CGeoPoint<double>> &pts, double &min, double &max, bool isX);

	public:
		//
		std::vector<AnyTraceSample> m_samples;
		std::vector<double> m_horizons;//≤„Œª
		std::vector<std::string> m_horizonnames;//≤„Œª√˚

		std::vector<double> m_lineminA;
		std::vector<double> m_linemaxA;

		//2016/2/26
		CurveProperties m_curves;
		int m_isSquareLineMode;//2016/4/27: vertical and horizontal line

		// for show cursor
		std::vector<std::vector<CGeoPoint<double> > > m_lines;
		std::vector<std::vector<AnyTraceSample> > m_datas;
		std::vector<std::vector<long>> m_dataOrders;//2016/4/15: record cursor shown order in m_samples

		//2016/1/19: filling line
		FillingLineProperty m_fillingLine;
		bool m_isRenderFilling;

		//2016/4/26: filling lines
		FillingProperties m_fillingLines;
		std::vector<bool> m_isRenderFillings;

		//2016/2/16: grid
		GridProperty m_gridProperty;

		//2019/4/22: m_samples could be fetched by trace ids
		std::vector<int> m_traceids;
	};
}

#endif