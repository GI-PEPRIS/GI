/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYSDE_MAPREDUCE_TASK_BASIC_H__
#define __ANYSDE_MAPREDUCE_TASK_BASIC_H__

#include "any/base/anystl.h"
#include "any/base/anyport.h"
#include "any/base/hash/simple_hash.h"

#include <SF/vector.hpp>
#include <SF/string.hpp>
#include <SF/SerializeParent.hpp>
#include "any/gfs/anyservicebasic.h"

//
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

namespace AnySDE
{
	/*!
	*
	**/
	enum SdeParameterType
	{
		SPT_Unknown,
		SPT_Raster_Slice,
		SPT_Raster_MarchingCube,
		SPT_Max
	};
	/*!
	*
	**/
	struct SdePosition
	{
		short m_inline;
		short m_xline;
		double m_zvaluemin;
		double m_zvaluemax;

		SdePosition() : m_inline(0), m_xline(0), m_zvaluemin(0.0), m_zvaluemax(0.0)
		{
		}
		SdePosition(const SdePosition &other)
		{
			*this = other;
		}
		const SdePosition &operator=(const SdePosition &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_inline = other.m_inline;
			m_xline = other.m_xline;
			m_zvaluemin = other.m_zvaluemin;
			m_zvaluemax = other.m_zvaluemax;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_inline & m_xline & m_zvaluemin & m_zvaluemax;
		}
	};
	/*!
	*
	**/
	struct SdeTimeSlice
	{
		double m_timemin;
		double m_timemax;

		SdeTimeSlice() : m_timemin(0), m_timemax(0)
		{
		}
		SdeTimeSlice(const SdeTimeSlice &other)
		{
			*this = other;
		}
		const SdeTimeSlice &operator=(const SdeTimeSlice &other)
		{
			if(this != &other)
			{
				m_timemin = other.m_timemin;
				m_timemax = other.m_timemax;
			}

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_timemin & m_timemax;
		}
	};
	/*!
	*
	**/
	struct SdeHorizonSlice
	{
		std::vector<SdePosition> m_survey;

		SdeHorizonSlice()
		{
		}
		SdeHorizonSlice(const SdeHorizonSlice &other)
		{
			*this = other;
		}
		const SdeHorizonSlice &operator=(const SdeHorizonSlice &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_survey = other.m_survey;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_survey;
		}
	};

	/*!
	* 
	**/
	struct TaskCGeoPoint
	{
		double m_x;
		double m_y;
		double m_z;
		
		TaskCGeoPoint() : m_x(ANY_NAN), m_y(ANY_NAN), m_z(ANY_NAN)
		{
		}
		TaskCGeoPoint(const TaskCGeoPoint &other)
		{
			*this = other;
		}
		const TaskCGeoPoint &operator=(const TaskCGeoPoint &other)
		{
			m_x = other.m_x;
			m_y = other.m_y;
			m_z = other.m_z;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_x & m_y & m_z;
		}
	};
	struct TaskOctreeCube
	{
		// spatial planar: X-Y direction, from left-down, anti-clockwise
		TaskCGeoPoint m_pos1;
		TaskCGeoPoint m_pos2;
		TaskCGeoPoint m_pos3;
		TaskCGeoPoint m_pos4;
		// time window as Z direction
		double m_minTime;
		double m_maxTime;
		double m_interval;
		int m_octreeLevel;

		TaskOctreeCube() : m_minTime(ANY_NAN), m_maxTime(ANY_NAN), m_interval(ANY_NAN), m_octreeLevel(0)
		{
		}
		TaskOctreeCube(const TaskOctreeCube &other)
		{
			*this = other;
		}
		const TaskOctreeCube &operator=(const TaskOctreeCube &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_pos1 = other.m_pos1;
			m_pos2 = other.m_pos2;
			m_pos3 = other.m_pos3;
			m_pos4 = other.m_pos4;
			m_minTime = other.m_minTime;
			m_maxTime = other.m_maxTime;
			m_interval = other.m_interval;
			m_octreeLevel = other.m_octreeLevel;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_pos1 & m_pos2 & m_pos3 & m_pos4 & m_minTime & m_maxTime & m_interval & m_octreeLevel;
		}
	};

	/*!
	* 
	**/
	struct TaskOctreeTileDimension
	{
		int m_tileSizex;
		int m_tileSizey;
		int m_tileSizez;

		TaskOctreeTileDimension() : m_tileSizex(ANY_NAN), m_tileSizey(ANY_NAN), m_tileSizez(ANY_NAN)
		{
		}
		TaskOctreeTileDimension(const TaskOctreeTileDimension &other)
		{
			*this = other;
		}
		const TaskOctreeTileDimension &operator=(const TaskOctreeTileDimension &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_tileSizex = other.m_tileSizex;
			m_tileSizey = other.m_tileSizey;
			m_tileSizez = other.m_tileSizez;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_tileSizex & m_tileSizey & m_tileSizez;
		}
	};

	struct TaskSurveyInfo
	{
		int m_nLineNum;								// In Line数目
		int m_nCDPNum;								//Cross Line数目
		int m_nStartLine;								//In Line起始编号
		int m_nStartCDP;								//Cross Line起始编号
		short m_nLineIncrement;					//In Line编号间隔	
		short m_nCDPIncrement;					//Cross Line编号间隔

		TaskSurveyInfo() : m_nLineNum(0), m_nCDPNum(0), m_nStartLine(0), m_nStartCDP(0), m_nLineIncrement(0), m_nCDPIncrement(0)
		{
		}
		~TaskSurveyInfo()
		{
		}
		const TaskSurveyInfo &operator=(const TaskSurveyInfo &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_nLineNum = other.m_nLineNum;					// In Line数目
			m_nCDPNum = other.m_nCDPNum;					//Cross Line数目
			m_nStartLine = other.m_nStartLine;				//In Line起始编号
			m_nStartCDP = other.m_nStartCDP;				//Cross Line起始编号
			m_nLineIncrement = other.m_nLineIncrement;	//In Line编号间隔	
			m_nCDPIncrement = other.m_nCDPIncrement;	//Cross Line编号间隔
			return *this;
		}
		bool Sequence2Survey(long sequenceOrder, double &lineNo, double &cdpNo)
		{
			int lineOrder = sequenceOrder / m_nCDPNum;
			int CDPOrder = sequenceOrder % m_nCDPNum;
			lineNo = m_nStartLine + lineOrder * m_nLineIncrement;
			cdpNo = m_nStartCDP + CDPOrder * m_nCDPIncrement;
			return true;
		}
		bool Survey2Sequence(double LineNo, double CDPNo, long &sequenceOrder)
		{
			double tempCDP = CDPNo - m_nStartCDP;
			tempCDP = Dither(tempCDP, m_nCDPIncrement);
			int CDPOrder = (int)(tempCDP / m_nCDPIncrement);
			CDPOrder = abs(CDPOrder);

			if(m_nLineIncrement == 0)
			{
				sequenceOrder = CDPOrder;
				return true;
			}

			double tempLine = LineNo - m_nStartLine;
			tempLine = Dither(tempLine, m_nLineIncrement);
			int lineOrder = (int)(tempLine / m_nLineIncrement);
			lineOrder = abs(lineOrder);

			sequenceOrder = lineOrder * m_nCDPNum + CDPOrder;
			return true;
		}
		double Dither(double value,double dlt)
		{
			if(dlt <= 0)
				return value;
			if(value > 0)
				value += dlt / 2;
			else
				value -= dlt / 2;
			return value;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_nLineNum & m_nCDPNum & m_nStartLine & m_nStartCDP & m_nLineIncrement & m_nCDPIncrement;
		}
	};
	struct SdeMCParameter
	{
		string m_gfsname;
		string m_gfslocalpath;
		std::vector<int> m_tilecodetoload;
		int m_hisThreshold;
		int m_porosityx;
		int m_porosityy;
		int m_porosityz;
		int m_scanlineminwidth;
		int m_volumeminsize;
		int m_mergeowntimes;
		bool m_isCheckIntersect;
		int m_taskcount;
		int m_tilebuffer;
		SdeMCParameter()
		{
		}
		SdeMCParameter(const SdeMCParameter &other)
		{
			*this = other;
		}
		const SdeMCParameter &operator=(const SdeMCParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_gfsname = other.m_gfsname;
			m_gfslocalpath = other.m_gfslocalpath;
			m_tilecodetoload = other.m_tilecodetoload;
			m_hisThreshold = other.m_hisThreshold;
			m_porosityx = other.m_porosityx;
			m_porosityy = other.m_porosityy;
			m_porosityz = other.m_porosityz;
			m_scanlineminwidth = other.m_scanlineminwidth;
			m_volumeminsize = other.m_volumeminsize;
			m_mergeowntimes = other.m_mergeowntimes;
			m_isCheckIntersect = other.m_isCheckIntersect;
			m_taskcount = other.m_taskcount;
			m_tilebuffer = other.m_tilebuffer;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gfsname & m_gfslocalpath & m_tilecodetoload & m_hisThreshold & m_porosityx & m_porosityy & m_porosityz & m_scanlineminwidth &\
				m_volumeminsize & m_mergeowntimes & m_isCheckIntersect & m_taskcount & m_tilebuffer;
		}
	};

	struct SdeJobParameter : public SdeTimeSlice, SdeHorizonSlice, SdeMCParameter
	{
		short m_jobtype;
		short m_parametertype;
		std::vector<unsigned long long> m_chunkuuids;
		TaskOctreeCube m_cube;
		TaskOctreeTileDimension m_tileDimension;
		TaskSurveyInfo m_inputsurveyInfo;
		TaskSurveyInfo m_outputsurveyInfo;

		SdeJobParameter() : m_jobtype(AnyRCF::JET_Unknown), m_parametertype(SPT_Unknown)
		{
		}
		SdeJobParameter(const SdeJobParameter &other)
		{
			*this = other;
		}
		const SdeJobParameter &operator=(const SdeJobParameter &other)
		{	
			*((SdeTimeSlice*)this) = *((SdeTimeSlice*)&other);
			*((SdeHorizonSlice*)this) = *((SdeHorizonSlice*)&other);
			*((SdeMCParameter*)this) = *((SdeMCParameter*)&other);

			m_jobtype = other.m_jobtype;
			m_parametertype = other.m_parametertype;
			m_chunkuuids = other.m_chunkuuids;
			m_cube = other.m_cube;
			m_tileDimension = other.m_tileDimension;
			m_inputsurveyInfo = other.m_inputsurveyInfo;
			m_outputsurveyInfo = other.m_outputsurveyInfo;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			serializeParent( (SdeTimeSlice*) 0, ar, *this);
			serializeParent( (SdeHorizonSlice*) 0, ar, *this);
			serializeParent( (SdeMCParameter*) 0, ar, *this);
			ar & m_jobtype & m_parametertype & m_chunkuuids & m_cube & m_tileDimension & m_inputsurveyInfo & m_outputsurveyInfo;
		}
	};


	/*!
	*
	**/
	struct SdeMapKey
	{
		// inline extent
		long m_inlStart;
		long m_inlStep;
		long m_inlEnd;

		// cross line
		long m_crlStart;
		long m_crlStep;
		long m_crlEnd;

		// time or depth window
		double m_minZ;
		double m_maxZ;

		void serialize(SF::Archive &ar)
		{
			ar & m_inlStart & m_inlStep & m_inlEnd \
				& m_crlStart & m_crlStep & m_crlEnd \
				& m_minZ & m_maxZ;
		}

		unsigned int Hash()
		{
			char buf[1024] = {};
			::sprintf(buf, "%d,%d,%d,%d,%d,%d,%f,%f", m_inlStart, m_inlStep, m_inlEnd, m_crlStart, m_crlStep, m_crlEnd, m_minZ, m_maxZ);

			return JSHash(string(buf));
		}
	};
	typedef std::vector<SdeMapKey> SdeMapKeyVector;

	/*!
	*
	**/
	struct SdeMapValue
	{
		std::vector<std::vector<double> > m_traces;
		std::vector<SdePosition> m_slice;

		void serialize(SF::Archive &ar)
		{
			ar & m_traces & m_slice;
		}
	};

	/*!
	*
	**/
	struct SdeMapPair
	{
		unsigned long long m_chunkuuid;
		SdeMapKey m_key;
		SdeMapValue m_value;
		void serialize(SF::Archive &ar)
		{
			ar & m_chunkuuid & m_key & m_value;
		}
	};

};

#endif