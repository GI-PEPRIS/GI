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
#ifndef __ANYGEOP_SEGY_WELL_PROFILE_H__
#define __ANYGEOP_SEGY_WELL_PROFILE_H__

// refer to macro
#include "anygeop.h"

// refer to seis data gate and correlated algorithms
#include "anysegyprofile.h"
#include "any/bridge/anybridgedatamodel.h"

//
namespace AnyGeoP
{
	/*!
	*
	**/
	class ANYGEOP_CLASS CAnySegyWellProfile : public CAnySegyProfile
	{
	public:
		/*!
		*
		**/
		struct SegyWellSetting
		{
			string m_name;
			int m_project_method;//0 - md, 1 - vertical depth
			std::vector<std::string> m_well_names;
			std::vector<int> m_groupids;

			std::vector<std::vector<std::string>> m_left_curve_names;
			std::vector<std::vector<std::string>> m_right_curve_names;

			//std::vector<std::vector<AnyWellPick>> m_well_picks;//地质层位
			std::vector<std::vector<AnyWellPath>> m_well_paths;//井轨迹,xoffset,yoffset需有效

			int m_seis2dor3d;//0:2d,1:3d
			string m_sgydatasetname;
			int m_rendertype;
			int m_timeordepthdomain;
			double m_curvescale;
			string m_velocitydatasetname;
			std::vector<string> m_horizonnames;
			std::vector<LineStyle> m_horizonlinestyles;
			
			/*!
			*
			**/
			SegyWellSetting()
			{
				m_name = "";
				m_project_method = 0;
				m_seis2dor3d = 0;
				m_sgydatasetname = "";
				m_rendertype = CAnySegyProfile::PT_Gray;
				m_timeordepthdomain = 0;
				m_curvescale = 0.03;
				m_velocitydatasetname = "";
			}
			
			/*!
			*
			**/
			const SegyWellSetting &operator=(const SegyWellSetting &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_name = other.m_name;
				m_project_method = other.m_project_method;
				m_well_names = other.m_well_names;
				m_groupids = other.m_groupids;
				m_left_curve_names = other.m_left_curve_names;
				m_right_curve_names = other.m_right_curve_names;
				//m_well_picks = other.m_well_picks;
				m_well_paths = other.m_well_paths;
				m_seis2dor3d = other.m_seis2dor3d;
				m_sgydatasetname = other.m_sgydatasetname;
				m_rendertype = other.m_rendertype;
				m_timeordepthdomain = other.m_timeordepthdomain;
				m_curvescale = other.m_curvescale;
				m_velocitydatasetname = other.m_velocitydatasetname;
				m_horizonnames = other.m_horizonnames;
				m_horizonlinestyles = other.m_horizonlinestyles;
				return *this;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySegyWellProfile(CAnyView &curView, CAnyObservable *observable = 0);

		/*!
		*
		**/
		~CAnySegyWellProfile();

	public:
		//
		//
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

	public:
		SegyWellSetting m_segywellsetting;
	};
}
#endif