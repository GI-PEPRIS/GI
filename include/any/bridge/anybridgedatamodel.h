/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
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
#ifndef __ANYBRIDGE_DATAMODEL_H__
#define __ANYBRIDGE_DATAMODEL_H__

// refer to stl, geometry primitives etc
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;

//
#include "any/base/agm/reflection.hpp"
using namespace agm::reflection;

// refer to TypeList
#include "any/base/loki/typelist.h"
using namespace AnyBase::Loki;

// refer to persistence
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// namespace
namespace AnyBridge
{
	//
	// kinds of well data
	//
	/*!
	*
	**/
	enum WellType
	{
		WT_Unknown,
		WT_On_Shore,
		WT_Off_Shore,
		WT_Off_Shore_Subsea,
	};

	/*!
	*
	**/
	struct AnyWell
	{
		CLASS(AnyWell, agm::reflection::NullClass);	

		// unique idx
		FIELD2(public, unsigned long, m_wellIdx);
		// foreign keys
		FIELD2(public, unsigned long, m_elementIdx);
		FIELD2(public, unsigned long, m_classIdx);
		FIELD2(public, unsigned long, m_geometryIdx);
		FIELD2(public, unsigned long, m_adminIdx);
		// Name of the entity
		FIELD2(public, string, m_name);//well name
		// earth coordinate
		FIELD2(public, double, m_longitude);
		FIELD2(public, double, m_latitude);
		// mapped or UTM coordinate
		FIELD2(public, double, m_xCoord);
		FIELD2(public, double, m_yCoord);
		// The elevation of the ground where this well is located. 
		FIELD2(public, double, m_groundEvaluation);//GE
		// total depth
		FIELD2(public, double, m_totalDepth);//TVD
		// The number of the well
		FIELD2(public, string, m_wellNumber);
		// The name or code that describes this well's current status
		FIELD2(public, string, m_wellStatus);
		//  code that describes the nature of the location of this well
		FIELD2(public, string, m_wellType);
		// null value
		FIELD2(public, double, m_nullvalue);

		//2018/5/22: new fields
		//alias name
		FIELD2(public, string, m_alias_name);

		//KB
		FIELD2(public, double, m_kb);

		//KBE = GE+KB
		FIELD2(public, double, m_kbe);

		//TVDSS = -(TVD - KBE), +/-
		FIELD2(public, double, m_tvdss);
		
		//2018/11/6
		//well type
		FIELD2(public, string, m_well_type);
		//well area
		FIELD2(public, string, m_well_area);
		//drilling_type
		FIELD2(public, string, m_drilling_type);
		//completion_date
		FIELD2(public, string, m_completion_date);
		//drill_finishing_date
		FIELD2(public, string, m_drill_finishing_date);
		//completion_depth
		FIELD2(public, double, m_completion_depth);
		//vertical_depth
		FIELD2(public, double, m_vertical_depth);
		//completion_formation
		FIELD2(public, string, m_completion_formation);
		//completion_method
		FIELD2(public, string, m_completion_method);
		//ai_bottom_depth
		FIELD2(public, double, m_ai_bottom_depth);
	
		//2019/3/5: petromod variables
		FIELD2(public, double, m_x_coord_bottom_hole);
		FIELD2(public, double, m_y_coord_bottom_hole);
		FIELD2(public, double, m_total_drill_depth);
		FIELD2(public, double, m_pm_start_elevation);
		FIELD2(public, double, m_pm_total_drill_depth);
		FIELD2(public, double, m_pm_true_vertical_depth);
		FIELD2(public, std::string, m_symbol_style);
		FIELD2(public, double, m_symbol_size);
		FIELD2(public, std::string, m_remark);

		//2019/4/2: group name
		FIELD2(public, std::string, m_groupname);

		// persistence table
		STATIC_FIELD(public, string, m_table);

		//
		/*!
		*
		**/
		AnyWell() : m_wellIdx(0), m_elementIdx(0), m_classIdx(0), m_geometryIdx(0), m_adminIdx(0), m_name(""), m_longitude(0.), m_latitude(0.), \
			m_xCoord(0.), m_yCoord(0.), m_groundEvaluation(0.), m_totalDepth(0.), m_wellNumber(""), m_wellStatus(""), m_wellType(""), m_nullvalue(ANY_NAN),\
			m_alias_name(""), m_kb(0.), m_kbe(0.), m_tvdss(0.), m_well_type(""), m_well_area(""),m_drilling_type(""), m_completion_date(""),m_drill_finishing_date(""), \
			m_completion_depth(0.),m_vertical_depth(0.),m_completion_formation(""),m_completion_method(""),m_ai_bottom_depth(0.),\
			m_x_coord_bottom_hole(0.), m_y_coord_bottom_hole(0.), m_total_drill_depth(0.), m_pm_start_elevation(0.), m_pm_total_drill_depth(0.), m_pm_true_vertical_depth(0.), \
			m_symbol_style(""),m_symbol_size(0.), m_remark(""), m_groupname("")
		{
		}

		/*!
		*
		**/
		AnyWell(const AnyWell &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWell &operator=(const AnyWell &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_wellIdx = other.m_wellIdx;
			m_elementIdx = other.m_elementIdx;
			m_classIdx = other.m_classIdx;
			m_geometryIdx = other.m_geometryIdx;
			m_adminIdx = other.m_adminIdx;
			m_name = other.m_name;
			m_longitude = other.m_longitude;
			m_latitude = other.m_latitude;
			m_xCoord = other.m_xCoord;
			m_yCoord = other.m_yCoord;
			m_groundEvaluation = other.m_groundEvaluation;
			m_totalDepth = other.m_totalDepth;
			m_wellNumber = other.m_wellNumber;
			m_wellStatus = other.m_wellStatus;
			m_wellType = other.m_wellType;
			m_nullvalue = other.m_nullvalue;

			//
			m_alias_name = other.m_alias_name;
			m_kb = other.m_kb;
			m_kbe = other.m_kbe;
			m_tvdss = other.m_tvdss;

			//
			m_well_type = other.m_well_type;
			m_well_area = other.m_well_area;
			m_drilling_type = other.m_drilling_type;
			m_completion_date = other.m_completion_date;
			m_drill_finishing_date = other.m_drill_finishing_date;
			m_completion_depth = other.m_completion_depth;
			m_vertical_depth = other.m_vertical_depth;
			m_completion_formation = other.m_completion_formation;
			m_completion_method = other.m_completion_method;
			m_ai_bottom_depth = other.m_ai_bottom_depth;

			//
			m_x_coord_bottom_hole = other.m_x_coord_bottom_hole;
			m_y_coord_bottom_hole = other.m_y_coord_bottom_hole;
			m_total_drill_depth = other.m_total_drill_depth;
			m_pm_start_elevation = other.m_pm_start_elevation;
			m_pm_total_drill_depth = other.m_pm_total_drill_depth;
			m_pm_true_vertical_depth = other.m_pm_true_vertical_depth;
			m_symbol_style = other.m_symbol_style;
			m_symbol_size = other.m_symbol_size;
			m_remark = other.m_remark;

			//
			m_groupname = other.m_groupname;

			return *this;
		}
	};

	/*!
	*
	**/
	struct AnyWellBore
	{
		CLASS(AnyWellBore, agm::reflection::NullClass);

		// 
		FIELD2(public, unsigned long, m_boreIdx);
		//
		FIELD2(public, unsigned long, m_wellIdx);
		//
		FIELD2(public, string, m_name);

		// persistence table
		STATIC_FIELD(public, string, m_table);

		//
		//
		//
		/*!
		*
		**/
		AnyWellBore() : m_boreIdx(0), m_wellIdx(0), m_name("")
		{
		}

		/*!
		*
		**/
		AnyWellBore(const AnyWellBore &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellBore &operator=(const AnyWellBore &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_boreIdx = other.m_boreIdx;
			m_wellIdx = other.m_wellIdx;
			m_name = other.m_name;
			return *this;
		}
	};

	/*!
	*
	**/
	struct AnyTraceDescription
	{
		// trace
		char m_name[12];
		// unit
		char m_unit[12];
		// invalid sample value
		double m_invalid;
		// unsigned long as address or bytes offset from begining
		unsigned long m_offset;
		// sample number
		long m_number;
	};

	/*!
	*
	**/
	enum TraceIndexKind
	{
		TIK_Unknown,
		TIK_MD,
		TIK_OWT,
		TIK_TVD,
		TIK_TVDSS,
		TIK_TWT,
	};

	/*!
	* well path: d_well_path
	**/
	struct AnyWellPath
	{
		//2018/5/22: new variables
		long m_boreIdx;

		// measure depth
		double m_md;
		// tvd depth
		double m_tvd;

		//
		double m_inclination;

		// dip azimuth
		double m_dipAzimuth;

		// coordinate
		double m_xOffset;//deltax
		double m_yOffset;//deltay

		double m_easting;
		double m_northing;

		// tvdss depth
		double m_tvdss;
		// dip angle
		double m_dipAngle;
		
		/*!
		*
		**/
		AnyWellPath() : m_md(0.), m_tvd(0.), m_tvdss(0.), m_dipAngle(0.), m_dipAzimuth(0.), m_xOffset(0.), m_yOffset(0.),\
			m_boreIdx(0), m_inclination(0.),m_easting(0.), m_northing(0.)
		{
		}

			/*!
		*
		**/
		AnyWellPath(const AnyWellPath &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellPath &operator=(const AnyWellPath &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			//
			m_boreIdx = other.m_boreIdx;
			m_md = other.m_md;
			m_tvd = other.m_tvd;
			m_inclination = other.m_inclination;
			m_dipAzimuth = other.m_dipAzimuth;
			m_xOffset = other.m_xOffset;
			m_yOffset = other.m_yOffset;
			m_easting = other.m_easting;
			m_northing = other.m_northing;
			m_tvdss = other.m_tvdss;
			m_dipAngle = other.m_dipAngle;

			return *this;
		}
	};

	/*!
	* 2018/5/22: well fault: d_well_fault
	**/
	struct AnyWellFault
	{
		//
		long m_boreIdx;

		//fault id
		std::string m_faultname;
		
		//vertical sep
		double m_verticalsep;

		//slip type
		std::string m_sliptype;

		// dip angle
		double m_dipAngle;

		// dip azimuth
		double m_dipAzimuth;
				
		/*!
		*
		**/
		AnyWellFault() :m_boreIdx(0), m_faultname(""),m_verticalsep(0.), m_sliptype(""),\
			m_dipAngle(0.), m_dipAzimuth(0.)
		{
		}

		/*!
		*
		**/
		AnyWellFault(const AnyWellFault &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellFault &operator=(const AnyWellFault &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			//
			m_boreIdx = other.m_boreIdx;
			m_faultname = other.m_faultname;
			m_verticalsep = other.m_verticalsep;
			m_sliptype = other.m_sliptype;
			m_dipAngle = other.m_dipAngle;
			m_dipAzimuth = other.m_dipAzimuth;

			return *this;
		}

	};

	/*!
	* 2018/7/18: well interpretation: d_well_interpretation
	**/
	struct AnyWellInterpretation
	{
		//
		long m_boreIdx;

		//interpretation id
		long m_interpretation_id;
		
		//top depth
		double m_top_depth;

		//bottom depth
		double m_bottom_depth;

		//thickness
		double m_thickness;

		//single layer
		std::string m_single_layer;
			
		//interpretation result
		std::string m_interpretation_result;
		
		//net thickness
		double m_net_thickness;

		//interpretation porosity
		double m_interpretation_porosity;

		//interpretation perm
		double	m_interpretation_perm;

		//vsh
		double m_vsh;

		//saturation
		double m_saturation;

		//2018/10/8: formation position/sandset
		std::string m_formation_position;
		
		//sandset
		std::string m_sandset;

		/*!
		*
		**/
		AnyWellInterpretation() :m_boreIdx(0), m_interpretation_id(0),m_top_depth(0.), m_bottom_depth(0.), m_thickness(0.), m_single_layer(""),\
			m_interpretation_result(""), m_net_thickness(0.), m_interpretation_porosity(0.), m_interpretation_perm(0.), m_vsh(0.), m_saturation(0.),\
			m_formation_position(""),m_sandset("")
		{
		}

		/*!
		*
		**/
		AnyWellInterpretation(const AnyWellInterpretation &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellInterpretation &operator=(const AnyWellInterpretation &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			//
			m_boreIdx = other.m_boreIdx;
			m_interpretation_id = other.m_interpretation_id;
			m_top_depth = other.m_top_depth;
			m_bottom_depth = other.m_bottom_depth;
			m_thickness = other.m_thickness;
			m_single_layer = other.m_single_layer;
			m_interpretation_result = other.m_interpretation_result;
			m_net_thickness = other.m_net_thickness;
			m_interpretation_porosity = other.m_interpretation_porosity;
			m_interpretation_perm = other.m_interpretation_perm;
			m_vsh = other.m_vsh;
			m_saturation = other.m_saturation;
			m_formation_position = other.m_formation_position;
			m_sandset = other.m_sandset;

			//
			return *this;
		}

	};

	/*!
	* 2018/10/15: well logging data(d_well_interpretation)
	**/
	struct AnyWellLogging
	{
		//
		long m_boreIdx;

		//logging unit
		std::string m_loggingunit;
		
		//bottom depth
		double m_bottomdepth;

		//thickness
		double m_thickness;

		//color code
		long m_colorcode;
		std::string m_color;

		//oil bearing grade
		long m_oilbearinggradecode;
		std::string m_oilbearinggrade;
		
		//lithology
		std::string m_lithologycode;
		std::string m_lithologyname;

		//description
		std::string m_desctype;
		std::string m_sampletype;
		double m_desctopdepth;
		double m_desctoplength;
		
		//recorder
		std::string m_recorddate;
		std::string m_recorder;
		std::string m_auditor;
		std::string m_reviewer;
				
		/*!
		*
		**/
		AnyWellLogging() :m_boreIdx(0), m_loggingunit(""),m_bottomdepth(0.), m_thickness(0.), m_colorcode(0), m_color(""),\
			m_oilbearinggradecode(0),m_oilbearinggrade(""),m_lithologycode(""),m_lithologyname(""),m_desctype(""),m_sampletype(""),\
			m_desctopdepth(0.), m_desctoplength(0.),m_recorddate(""),m_recorder(""),m_auditor(""),m_reviewer("")
		{
		}

		/*!
		*
		**/
		AnyWellLogging(const AnyWellLogging &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellLogging &operator=(const AnyWellLogging &other)
		{
			if(this == &other)
			{
				return *this;
			}
			
			//
			m_boreIdx = other.m_boreIdx;
			m_loggingunit = other.m_loggingunit;
			m_bottomdepth = other.m_bottomdepth;
			m_thickness = other.m_thickness;
			m_colorcode = other.m_colorcode;
			m_color = other.m_color;
			m_oilbearinggradecode = other.m_oilbearinggradecode;
			m_oilbearinggrade = other.m_oilbearinggrade;
			m_lithologycode = other.m_lithologycode;
			m_lithologyname = other.m_lithologyname;
			m_desctype = other.m_desctype;
			m_sampletype = other.m_sampletype;
			m_desctopdepth = other.m_desctopdepth;
			m_desctoplength = other.m_desctoplength;
			m_recorddate = other.m_recorddate;
			m_recorder = other.m_recorder;
			m_auditor = other.m_auditor;
			m_reviewer = other.m_reviewer;

			return *this;
		}

	};

	/*!
	* for serialize the m_log, m_synthetic, m_timedepth etc below struct
	**/
	struct AnyTraceSample
	{
		double m_depth;
		double m_sample;
	};

	/*!
	*
	**/
	struct AnyTraceHead
	{
		double m_name;
		double m_maxTraceValue;
		double m_minTraceValue;
	};

	/*!
	*
	**/
	enum LogTraceDatatype
	{
		LTD_Unknown = -1,
		LTD_Log = 0,
		LTD_Path = 1000,
		LTD_Synthetic = 2000,
		LTD_Timedepth = 3000,
		LTD_Welladjust = 4000,
		LTD_Raster = 5000,
		LTD_Sedimentary = 6000,
		LTD_Depth = 7000,//2016/4/14: common depth component
		LTD_Pick = 8000,//2016/9/23: well pick component

		//2017/12/25: text component
		LTD_Text = 9000,
	};

	/*!
	*
	**/
	struct AnyWellLogTrace
	{
		CLASS(AnyWellLogTrace, agm::reflection::NullClass);

		//
		FIELD2(public, unsigned long, m_boreIdx);
		//
		FIELD2(public, std::vector<int>, m_datatypes);
		//
		FIELD2(public, std::vector<int>, m_traceids);
		//
		FIELD2(public, std::vector<string>, m_datatypenames);
		//
		FIELD2(public, std::vector<string>, m_tracenames);
		//
		FIELD2(public, std::vector<string>, m_tracealiasnames);
		//
		FIELD2(public, std::vector<string>, m_data_descs);
		//
		FIELD2(public, std::vector<unsigned char*>, m_tracedatas);
		//
		FIELD2(public, std::vector<long>, m_tracedatalengths);
		//
		FIELD2(public, std::vector<unsigned char*>, m_tracedatas_traceids);
		//
		FIELD2(public, std::vector<long>, m_tracedatalengths_traceids);

		// persistence table
		STATIC_FIELD(public, string, m_table);

		//
		//
		//
		/*!
		*
		**/
		AnyWellLogTrace() : m_boreIdx(0)
		{
		}

		/*!
		*
		**/
		AnyWellLogTrace(const AnyWellLogTrace &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellLogTrace &operator=(const AnyWellLogTrace &other)
		{
			// TODO:
			m_boreIdx = other.m_boreIdx;
			m_datatypes = other.m_datatypes;
			m_traceids = other.m_traceids;
			m_datatypenames = other.m_datatypenames;
			m_tracenames = other.m_tracenames;
			m_tracealiasnames = other.m_tracealiasnames;
			m_data_descs = other.m_data_descs;
			m_tracedatas = other.m_tracedatas;
			m_tracedatalengths = other.m_tracedatalengths;
			m_tracedatas_traceids = other.m_tracedatas_traceids;
			m_tracedatalengths_traceids = other.m_tracedatalengths_traceids;

			return *this;
		}
		
		/*!
		*
		**/
		unsigned char* GetWellTraceData(int datatype, long &len)
		{
			len = 0;
			for(int i = 0; i < m_datatypes.size(); i++)
			{
				if(m_datatypes[i] == datatype)
				{
					if (i < m_tracedatalengths.size())
					{
						len = m_tracedatalengths[i];
					}
					return m_tracedatas[i];
				}
			}
			return 0;
		}
		unsigned char* GetWellTraceData(int datatype, int traceid, long &len)
		{
			len = 0;
			for(int i = 0; i < m_datatypes.size(); i++)
			{
				if(m_datatypes[i] == datatype && m_traceids[i] == traceid)
				{
					if (i < m_tracedatalengths.size())
					{
						len = m_tracedatalengths[i];
					}
					return m_tracedatas[i];
				}
			}
			return 0;
		}

		unsigned char* GetWellTraceData_PlotSetting(int datatype, int traceid, long &len)
		{
			len = 0;
			for(int i = 0; i < m_datatypes.size(); i++)
			{
				if(m_datatypes[i] == datatype && m_traceids[i] == traceid)
				{
					if (i < m_tracedatalengths_traceids.size())
					{
						len = m_tracedatalengths_traceids[i];
					}

					if (i < m_tracedatas_traceids.size())
					{
						return m_tracedatas_traceids[i];
					}
					break;
				}
			}
			return 0;
		}


		void GetCountByDataType(int datatype, std::vector<int> &datatypes)
		{
			for(int i = 0; i < m_datatypes.size(); i++)
			{
				if(m_datatypes[i] >= datatype && m_datatypes[i] < datatype + 1000)
					datatypes.push_back(m_datatypes[i]);
			}
			if(datatypes.size() >= 2)
			{
				for(int j = 0; j < datatypes.size() - 1; j++)
				{
					for(int i = 0; i < datatypes.size() - 1 - j; i++)
					{
						if(datatypes[i] > datatypes[i + 1])
						{
							int temp = datatypes[i];
							datatypes[i] = datatypes[i + 1];
							datatypes[i + 1] = temp;
						}
					}
				}
			}
		}
		void GetCountByDataType(int datatype, std::vector<int> &datatypes, std::vector<int> &traceids)
		{
			for(int i = 0; i < m_datatypes.size(); i++)
			{
				if(m_datatypes[i] >= datatype && m_datatypes[i] < datatype + 1000)
				{
					datatypes.push_back(m_datatypes[i]);
					traceids.push_back(m_traceids[i]);
				}
			}
			if(datatypes.size() >= 2)
			{
				for(int j = 0; j < datatypes.size() - 1; j++)
				{
					for(int i = 0; i < datatypes.size() - 1 - j; i++)
					{
						if(datatypes[i] > datatypes[i + 1])
						{
							int temp = datatypes[i];
							datatypes[i] = datatypes[i + 1];
							datatypes[i + 1] = temp;
							int temp1 = traceids[i];
							traceids[i] = traceids[i + 1];
							traceids[i + 1] = temp1;
						}
					}
				}
			}
		}
		std::string GetWellTraceDataDesc(int datatype)
		{
			if(!m_data_descs.size())
			{
				return "";
			}
			for(int i = 0; i < m_datatypes.size(); i++)
			{
				if(m_datatypes[i] == datatype)
				{
					if(i < m_data_descs.size())
					{
						return m_data_descs[i];
					}
				}
			}
			return "";
		}
		std::string GetWellTraceDataDesc(int datatype, int traceid)
		{
			if(!m_data_descs.size())
			{
				return "";
			}
			for(int i = 0; i < m_datatypes.size(); i++)
			{
				if(m_datatypes[i] == datatype && m_traceids[i] == traceid)
				{
					if(i < m_data_descs.size())
					{
						return m_data_descs[i];
					}
				}
			}
			return "";
		}
		std::string FromTypeToName(int datatype)
		{
			if(datatype >= LTD_Log && datatype < LTD_Log + 1000)
				return "Log";
			if(datatype >= LTD_Path && datatype < LTD_Path + 1000)
				return "Path";
			if(datatype >= LTD_Synthetic && datatype < LTD_Synthetic + 1000)
				return "Synthetic";
			if(datatype >= LTD_Timedepth && datatype < LTD_Timedepth + 1000)
				return "Timedepth";
			if(datatype >= LTD_Welladjust && datatype < LTD_Welladjust + 1000)
				return "Welladjust";
			if(datatype >= LTD_Raster && datatype < LTD_Raster + 1000)
				return "Raster";
			if(datatype >= LTD_Sedimentary && datatype < LTD_Sedimentary + 1000)
				return "Sedimentary";
			if(datatype >= LTD_Depth && datatype < LTD_Depth + 1000)//2016/4/14
				return "Depth";
			if(datatype >= LTD_Pick && datatype < LTD_Pick + 1000)//2016/9/23
				return "Wellpick";
			if(datatype >= LTD_Text && datatype < LTD_Text + 1000)
				return "Text";
			return "";
		}
		int GetNextTraceid(int datatype)
		{
			int maxtraceid = -1;
			for(int i = 0; i < m_traceids.size(); i++)
			{
				if(m_datatypes[i] == datatype && maxtraceid < m_traceids[i])
				{
					maxtraceid = m_traceids[i];
				}
			}
			maxtraceid++;
			return maxtraceid;
		}
	};

	/*!
	*
	**/
	struct AnyWellPick
	{
		CLASS(AnyWellPick, agm::reflection::NullClass);

		//
		FIELD2(public, unsigned long, m_boreIdx);
		FIELD2(public, unsigned long, m_zoneIdx);
		FIELD2(public, string, m_pickby);
		FIELD2(public, string, m_pickName);

		//
		FIELD2(public, double, m_coordx);
		FIELD2(public, double, m_coordy);
		FIELD2(public, double, m_dipAngle);
		FIELD2(public, double, m_dipAzimuth);

		//
		FIELD2(public, double, m_topmd);
		FIELD2(public, double, m_toptvd);
		FIELD2(public, double, m_toptvdss);
		FIELD2(public, double, m_time);
		FIELD2(public, double, m_thick);

		//
		FIELD2(public, long, m_lithosymbolidx);
		FIELD2(public, double, m_faultHeave);
		FIELD2(public, string, m_faultName);
		FIELD2(public, string, m_faultType);
		FIELD2(public, unsigned long, m_color);

		//2018/5/22: new variables
		FIELD2(public, string, m_lithname);
		FIELD2(public, string, m_aliasname);
		FIELD2(public, string, m_source);
		FIELD2(public, double, m_northing);
		FIELD2(public, double, m_easting);
		FIELD2(public, double, m_basemd);
		FIELD2(public, double, m_basetvd);
		FIELD2(public, double, m_basetvdss);
		FIELD2(public, double, m_grossthickness);
		FIELD2(public, double, m_tvt);
		FIELD2(public, double, m_tst);
		FIELD2(public, double, m_gapthickness);
		FIELD2(public, double, m_boreazimuth);
		FIELD2(public, double, m_boreangle);
		
		//2018/7/12: fault related
		FIELD2(public, double, m_faultdepth);
		FIELD2(public, double, m_faultseparation);
		FIELD2(public, string, m_faultcomparedwell);

		// persistence table
		STATIC_FIELD(public, string, m_table);

		//
		//
		//
		/*!
		*
		**/
		AnyWellPick() : m_boreIdx(0), m_zoneIdx(0), m_pickby(""), m_pickName(""), m_coordx(ANY_NAN), m_coordy(ANY_NAN), m_dipAngle(0.), m_dipAzimuth(0.), \
			m_topmd(0.), m_toptvd(0.), m_toptvdss(0.), m_time(0.), m_thick(0.), m_lithosymbolidx(0), m_faultHeave(0.), m_faultName(""), m_faultType(""), m_color(0),\
			m_lithname(""), m_aliasname(""), m_source(""), m_northing(0.), m_easting(0.), m_basemd(0.), m_basetvd(0.), m_basetvdss(0.), m_grossthickness(0.), m_tvt(0.),\
			m_tst(0.), m_gapthickness(0.), m_boreazimuth(0.), m_boreangle(0.),m_faultdepth(0.),m_faultseparation(0.),m_faultcomparedwell("")
		{
		}

		/*!
		*
		**/
		AnyWellPick(const AnyWellPick &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellPick &operator=(const AnyWellPick &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_boreIdx = other.m_boreIdx;
			m_zoneIdx = other.m_zoneIdx;
			m_pickby = other.m_pickby;
			m_pickName = other.m_pickName;
			m_coordx = other.m_coordx;
			m_coordy = other.m_coordy;
			m_dipAngle = other.m_dipAngle;
			m_dipAzimuth = other.m_dipAzimuth;
			m_topmd = other.m_topmd;
			m_toptvd = other.m_toptvd;
			m_toptvdss = other.m_toptvdss;
			m_time = other.m_time;
			m_thick = other.m_thick;
			m_lithosymbolidx = other.m_lithosymbolidx;
			m_faultHeave = other.m_faultHeave;
			m_faultName = other.m_faultName;
			m_faultType = other.m_faultType;
			m_color = other.m_color;

			//2018/5/22: new variables
			m_lithname = other.m_lithname;
			m_aliasname = other.m_aliasname;
			m_source = other.m_source;
			m_northing = other.m_northing;
			m_easting = other.m_easting;
			m_basemd = other.m_basemd;
			m_basetvd = other.m_basetvd;
			m_basetvdss = other.m_basetvdss;
			m_grossthickness = other.m_grossthickness;
			m_tvt = other.m_tvt;
			m_tst = other.m_tst;
			m_gapthickness = other.m_gapthickness;
			m_boreazimuth = other.m_boreazimuth;
			m_boreangle = other.m_boreangle;

			//2018/7/12: fault related
			m_faultdepth = other.m_faultdepth;
			m_faultseparation = other.m_faultseparation;
			m_faultcomparedwell = other.m_faultcomparedwell;

			return *this;
		}
	};

	/*!
	*
	**/
	struct AnyWellZone
	{
		CLASS(AnyWellZone, agm::reflection::NullClass);

		//
		FIELD2(public, unsigned long, m_boreIdx);
		//
		FIELD2(public, string, m_wellZone);

		// persistence table
		STATIC_FIELD(public, string, m_table);

		//
		//
		//
		/*!
		*
		**/
		AnyWellZone() : m_boreIdx(0), m_wellZone("")
		{
		}

		/*!
		*
		**/
		AnyWellZone(const AnyWellZone &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnyWellZone &operator=(const AnyWellZone &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_boreIdx = other.m_boreIdx;
			m_wellZone = other.m_wellZone;
			return *this;
		}
	};

	/*!
	*
	**/
	struct AnyWellGeometry
	{
		CLASS(AnyWellGeometry, agm::reflection::NullClass);

		//
		FIELD2(public, unsigned long, m_geometryIdx);
		//
		FIELD2(public, double, m_xmin);
		//
		FIELD2(public, double, m_xmax);
		//
		FIELD2(public, double, m_ymin);
		//
		FIELD2(public, double, m_ymax);

		// persistence table
		STATIC_FIELD(public, string, m_table);
	};

	// make types for kinds of well data
	typedef MakeTypeList<AnyWell, AnyWellBore, AnyWellLogTrace, AnyWellPick, AnyWellZone>::Result WellDataTypes;

	//
	// kinds of seismic data
	//
	/*!
	* EpiProject_Project
	**/
	struct AnySeismicProject
	{
		// primary key
		long m_idx;
		// belong to which element
		long m_elementIdx;
		// A string-encoded representation of the coordinate system in which the project extent is specified. 
		string m_coordinateSystemType;
		// A string-encoded representation of the default depth-based coordinate system for the project. 
		string m_depthCoordinateSystem;
		// Name of the project.
		string m_name;
		// A textual description of the project's intended use, user, location, or associated tables.
		string m_description;
		// The spatial bounding box that represents the limits/boundaries of this project. 
		CGeoRect<double> m_extent;
		// The list of project interpreters available to the user. 
		string m_interpreters;

		/*!
		*
		**/
		AnySeismicProject() : m_idx(0), m_elementIdx(0), m_coordinateSystemType(""), m_depthCoordinateSystem(""), m_name(""), m_description(""), \
			m_extent(0., 0., 0., 0.), m_interpreters("")
		{
		}

		/*!
		*
		**/
		AnySeismicProject(const AnySeismicProject &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnySeismicProject &operator=(const AnySeismicProject &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_idx = other.m_idx;
			m_elementIdx = other.m_elementIdx;
			m_coordinateSystemType = other.m_coordinateSystemType;
			m_depthCoordinateSystem = other.m_depthCoordinateSystem;
			m_name = other.m_name;
			m_description = other.m_description;
			m_extent = other.m_extent;
			m_interpreters = other.m_interpreters;
			return *this;
		}
	};

	/*!
	* EpiSeismic_SeismicDataset 
	**/
	struct AnySeismicDataSet
	{
		// primary key
		long m_idx;
		// from which data set
		long m_fromIdx;
		// belong to which project
		long m_projectIdx;
		// belong to which geometry survey
		long m_geometryIdx;
		// Name of the entity. 
		string m_name;
		// Text containing user remarks about this seismic data set. 
		string m_comment;
		// The data store installation name. 
		string m_datasource;
		// A factor that represents the extent to which the data in this seismic data set is compressed while stored on disk. 
		double m_compressionFactor;
		// The Z axis sampling rate for the traces in the dataset. 
		double m_deltaZ;
		// Indicates if the seismic data is sampled in time or depth.
		unsigned char m_domainType; // TIME or DEPTH
		// The seismic dataset's spatial bounding box. 
		CGeoRect<double> m_extent;
		// time stamp, The date the data represented in the entity last changed in the data store. 
		double m_timestamp;
		// The maximum Z (time/depth) value across all the traces in this dataset. 
		double m_maxZ;
		// The minimum Z (time/depth) value across all the traces in this dataset. 
		double m_minZ;
		// The number of samples per trace for this data set. 
		long m_numTraces;
		// The type of sample data.  For example, "SEISMIC AMPLITUDE". 
		unsigned char m_sampleKind;
		// The maximum sample value in this seismic data set. 
		double m_sampleMax;
		// The minimum sample value in this seismic data set. 
		double m_sampleMin;
		// The unit of measure in which the sample data is returned. 
		unsigned char m_sampleUnit;
		// 

		/*!
		*
		**/
		AnySeismicDataSet() : m_idx(0), m_fromIdx(0), m_projectIdx(0), m_geometryIdx(0), m_name(""), m_comment(""), m_datasource(""), m_compressionFactor(0), \
			m_deltaZ(0), m_domainType(0), m_extent(0., 0., 0., 0.), m_timestamp(0), m_maxZ(0), m_minZ(0), m_numTraces(0), m_sampleKind(0), \
			m_sampleMax(0), m_sampleMin(0), m_sampleUnit(0)
		{
		}

		/*!
		*
		**/
		AnySeismicDataSet(const AnySeismicDataSet &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnySeismicDataSet &operator=(const AnySeismicDataSet &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_idx = other.m_idx;
			m_fromIdx = other.m_fromIdx;
			m_projectIdx = other.m_projectIdx;
			m_geometryIdx = other.m_geometryIdx;
			m_name = other.m_name;
			m_comment = other.m_comment;
			m_datasource = other.m_datasource;
			m_compressionFactor = other.m_compressionFactor;
			m_deltaZ = other.m_deltaZ;
			m_domainType = other.m_domainType;
			m_extent = other.m_extent;
			m_timestamp = other.m_timestamp;
			m_maxZ = other.m_maxZ;
			m_minZ = other.m_minZ;
			m_numTraces = other.m_numTraces;
			m_sampleKind = other.m_sampleKind;
			m_sampleMax = other.m_sampleMax;
			m_sampleMin = other.m_sampleMin;
			m_sampleUnit = other.m_sampleUnit;
			return *this;
		}
	};

	/*!
	* EpiSeismic_SeismicDataset 
	**/
	struct AnySeismicWavelet
	{
		// wavelet idx
		long m_idx;
		// from which dataset
		long m_fromDataset;
		// name
		string m_name;
		// sample
		double m_starttime;
		double m_samplenumber;
		double m_sampleinterval;
		// data
		std::vector<double> m_trace;
	};

	/*!
	* A seismic line that has 2D geometry
	**/
	struct AnySeismic2DGeometry
	{
		// unique idx
		long m_idx;

		// The name of this 2D line
		string m_name;

		// The data store installation name, namely, path
		string m_datasource;

		// The total number of points that constitute the geometry of the 2D line 
		// and preserves the relationship between trace, shotpoint, and CDP numbers. 
		int m_numControlPoints;

		// The maximum number of seismic traces that can exist for this 2D line. 
		int m_numTraces;

		// A list of numbers that identify the shotpoint associated with each 2D line control point. 
		std::vector<double> m_shotpoints;

		// A list of numbers that identify the trace number associated with each 2D line control point.
		std::vector<long> m_traces;

		// A list of XY coordinates that identify the location associated with each 2D line control point. 
		std::vector<CGeoPoint<double> > m_pts;

		/*!
		*
		**/
		AnySeismic2DGeometry() : m_idx(0), m_name(""), m_datasource(""), m_numControlPoints(0), m_numTraces(0)
		{
		}

		/*!
		*
		**/
		AnySeismic2DGeometry(const AnySeismic2DGeometry &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnySeismic2DGeometry &operator=(const AnySeismic2DGeometry &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_idx = other.m_idx;
			m_name = other.m_name;
			m_datasource = other.m_datasource;
			m_numControlPoints = other.m_numControlPoints;
			m_numTraces = other.m_numTraces;
			m_shotpoints.clear();
			for(int i = 0; i < other.m_shotpoints.size(); i++)
				m_shotpoints.push_back(other.m_shotpoints[i]);
			m_traces.clear();
			for(int i = 0; i < other.m_traces.size(); i++)
				m_traces.push_back(other.m_traces[i]);
			m_pts.clear();
			for(int i = 0; i < other.m_pts.size(); i++)
				m_pts.push_back(other.m_pts[i]);
			return *this;
		}
	};

	/*!
	* A seismic survey that has 3D geometry. 
	**/
	struct AnySeismic3DGeometry
	{
		// unique idx
		long m_idx;

		// The data store installation name, namely, path
		string m_datasource;

		// The extent in the form of an array of points (total 4). Clients should always set the coordinate system when 
		// retrieving this column; otherwise, the points will be returned in the default coordinate system and each vendor store might have a different default. 
		// The first point in the sequence identifies the survey's origin. All other points are in relation to this origin. 
		// The points are returned in the following order: (InlineStart, XlineStart) - survey origin, (InlineEnd, XlineStart), (InlineEnd, XlineEnd), (InlineStart, XlineEnd). 
		// This does not imply the SeismicBinGrid coordinate system (e.g. Inline/Xline axis) is the default coordinate system. 
		// You can specify a Map coordinate system but the first point returned will correspond to the (InlineStart, XlineStart) corner. 
		// Since the SeismicGeometry3d represents a two-dimensional "surface" mapping the third coordinate for each point will be zero since this coordinate represents the Z axis. 
		// The SeismicGeometry3d extents have no knowledge of the Z axis. 
		// It is very important the points are ordered correctly when doing INSERTS; otherwise, the inline/xline corner points will not be associated to the proper Map XY corner points. 
		CGeoPoint<double> m_extent[4];
		double m_inline[4];
		double m_xline[4];

		// for persistence above

		// The total number of inline grid coordinates in the survey. 
		double m_numInlines;

		// A number that represents the survey's inline increment. 
		double m_inlineDelta;

		// A number that represents the survey's last inline. 
		double m_inlineEnd;

		// A number that represents the survey's first inline. 
		double m_inlineStart;

		// The total number of crossline grid coordinates in the survey. 
		double m_numXlines;

		// A number that represents the survey's crossline increment. 
		double m_xlineDelta;

		// A number that represents the survey's last crossline. 
		double m_xlineEnd;

		// A number that represents the survey's first crossline. 
		double m_xlineStart;

		// Spacing between inlines.
		double m_inlineSpacing;

		// Spacing between crosslines.
		double m_xlineSpacing;

		/*!
		*
		**/
		AnySeismic3DGeometry() : m_idx(0), m_datasource(""), m_numInlines(0), m_inlineDelta(0),
			m_inlineEnd(0), m_inlineStart(0), m_numXlines(0), m_xlineDelta(0), m_xlineEnd(0),
			m_xlineStart(0), m_inlineSpacing(0), m_xlineSpacing(0)
		{
		}

		/*!
		*
		**/
		AnySeismic3DGeometry(const AnySeismic3DGeometry &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const AnySeismic3DGeometry &operator=(const AnySeismic3DGeometry &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_idx = other.m_idx;
			m_datasource = other.m_datasource;
			m_extent[0] = other.m_extent[0];
			m_extent[1] = other.m_extent[1];
			m_extent[2] = other.m_extent[2];
			m_extent[3] = other.m_extent[3];
			m_inline[0] = other.m_inline[0];
			m_inline[1] = other.m_inline[1];
			m_inline[2] = other.m_inline[2];
			m_inline[3] = other.m_inline[3];
			m_xline[0] = other.m_xline[0];
			m_xline[1] = other.m_xline[1];
			m_xline[2] = other.m_xline[2];
			m_xline[3] = other.m_xline[3];
			m_numInlines = other.m_numInlines;
			m_inlineDelta = other.m_inlineDelta;
			m_inlineEnd = other.m_inlineEnd;
			m_inlineStart = other.m_inlineStart;
			m_numXlines = other.m_numXlines;
			m_xlineDelta = other.m_xlineDelta;
			m_xlineEnd = other.m_xlineEnd;
			m_xlineStart = other.m_xlineStart;
			m_inlineSpacing = other.m_inlineSpacing;
			m_xlineSpacing = other.m_xlineSpacing;
			return *this;
		}
	};

	// 
	// kinds of interpretation data: feature-geometry-property
	//
	/*!
	* The primary domain of this earth model
	**/
	enum InterpretationDomainType
	{
		IDT_Time,
		IDT_Depth,
	};

	/*!
	* The type of feature
	**/
	enum InterpretationFeatureType
	{
		IFT_Fault,
		IFT_Horizon,
		IFT_Interval,
	};

	/*!
	* A list of OpenSpirit shape property types that are supported by the native datastore of this feature representation
	**/
	enum InterpretationShapeType
	{
		IST_Grid1D,
		IST_Grid2D,
		IST_GridQuadMesh,
		IST_PointSet,
		IST_PolylineSet,
	};

	/*!
	* Property type, such as time, depth, amplitude, thickness, etc. 
	**/
	enum InterpretationPropertyType
	{
		IPT_Unknown,
		IPT_Amplitude,
		IPT_Depth,
		IPT_Isochron,
		IPT_Isolith,
		IPT_Isopatch,
		IPT_Time,
		IPT_Velocity,
	};

	/*!
	* fault feature as GIS layer
	* Epiipt_FaultProperty, Epiipt_FaultPointSet 
	**/
	struct AnyInterpretationFaultFeature
	{
		// feature idx
		unsigned long m_idx;
		// from which seimic project
		unsigned long m_projectIdx;
		// locates 2D or 3D seismic geometry
		unsigned long m_surveyIdx;
		// Name of the entity
		string m_name;
		// The date the data represented in the entity last changed in the data store
		double m_lastModifiedDate;

		// shape type
		short m_shapeType;
		// property type
		short m_propertyType;
		// The property's maximum value representation
		double m_maxValue;
		// The property's minimum value representation as it exists in the vendor store
		double m_minValue;
		// The property's null value representati
		double m_nullValue;
	};

	/*!
	* Epiipt_FaultPointSet as GIS layer
	* 
	* A representation of a geologic fault structure as a set of x,y,z points. If any z values are non-zero, this fault is viewable in a 3d viewer. 
	* If all z values are zero, this fault representation is viewable only in 2d. A FaultPointSet may optionally have associated attribute properties sampled at these points. 
	**/
	struct AnyInterpretationFaultGeometry
	{
		// geometry idx
		unsigned long m_idx;
		// which feature
		unsigned long m_featureIdx;
		// The spatial bounding box represented by four points containing all the non-null and null data
		CGeoRect<double> m_extent;
		// coord and property
		std::vector<CGeoPoint<double> > m_coords;
	};

	/*!
	* Epiipt_HorizonProperty as GIS layer
	* 
	* A geologic boundary representing the interface between two strata or an unconformity
	**/
	struct AnyInterpretationHorizonFeature
	{
		// feature idx
		unsigned long m_idx;
		// from which seimic project
		unsigned long m_projectIdx;
		// locates 2D or 3D seismic geometry
		unsigned long m_surveyIdx;
		// Name of the entity
		string m_name;
		// The date the data represented in the entity last changed in the data store
		double m_lastModifiedDate;

		// shape type
		short m_shapeType;
		// property type
		short m_propertyType;
		// The property's maximum value representation
		double m_maxValue;
		// The property's minimum value representation as it exists in the vendor store
		double m_minValue;
		// The property's null value representati
		double m_nullValue;

		// strata
		unsigned long m_strataIdx;
		string m_strataColumnName;

		// The name of the category or classification of this horizon. Example values are:
		// 'Conformable', 'Downlap', 'Fluid Contact', 'Onlap', 'Nonconformity', etc. 
		string m_classification;
		// The age of this horizon
		double m_geologicalAge;
	};

	/*!
	* as GIS layer
	**/
	struct AnyIntrepretationHorizonGeometry
	{
		// geometry idx
		unsigned long m_idx;
		// which feature
		unsigned long m_featureIdx;
		
		// The spatial bounding box represented by four points containing all the non-null and null data
		CGeoRect<double> m_extent;
		// The total number of column coordinates in the 2D grid. 
		long m_numColumns;
		// The total number of row coordinates in the 2D grid. 
		long m_numRows;
		
		// The grid decimation factor
		long m_traceDelta;
		// TraceEnd identifies the seismic trace number where the last non-null horizon property value occurs
		long m_traceEnd;
		// TraceStart identifies the seismic trace number where the first non-null horizon property value occurs
		long m_traceStart;

		// coord and property
		std::vector<CGeoPoint<double> > m_coords;
	};
};

#endif