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
#ifndef __ANYGDE_DATA_GATE_H__
#define __ANYGDE_DATA_GATE_H__

#include<windows.h>
#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;

// refer to EXPORT & IMPORT
#include <stack>
#include <tchar.h>
#include "anygde.h"

#include "anygdedataoctree.h"
#include "anygdedatasurvey.h"
#include "calculatorcube.h"
#include "hugearray.h"

//
#include "any/base/anygeom.h"
#include "any/base/anyfilebasic.h"
#include "any/base/anylightlru.h"
#include "any/base/anymediator.h"
#include "any/base/anystringbasic.h"
using namespace AnyBase;

//
#include "any/bridge/anybridgedatamodel.h"
#include "any/bridge/anygeologicalcubefeature.h"
using namespace AnyBridge;

//
namespace AnyGDE
{
	// forward class
	class CAnyGdeDataTrace;
	class CAnySegyFile;
	class CAnyGdeDataOctreeGate;

	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataGate : public BaseVisitable<>
	{
	public:
		//
		LOKI_DEFINE_VISITABLE()

		enum GateType
		{
			POSTSTACK,
			PRESTACK,
			CMP,
			CRP,
			CAG,
			OVG,
			ANGLE360,
			ELLIPSE_AZIMUTH,//椭圆拟合方位角
			ELLIPSE_AMP,//椭圆拟合长短轴比
			AngleGroup,//角道集
			BIOT,//三角滤波
			VRMS,//均方根速度
			VINT,//层速度
			PROPERTY_POSTSTACK,//地震属性叠后
			PROPERTY_PRESTACK,//地震属性叠前
			TIME_DEPTH,//时深
			DEPTHDOMAIN,//深度域
		};

		/*!
		* 定义地震数据类型
		**/
		const static short	SEGY_SHORT = 3;
		const static short	SEGY_INT = 2;
		const static short	SEGY_IEEE = 5;
		const static short	SEGY_IBM = 1;

		/*!
		*
		**/
		struct HeadInfo
		{
			// head info
			long m_nTraceNum; // total trace number
			int m_nTraceLen; // trace lenth in bytes
			short m_nType; // segy type
			short m_nTracePt;		// sample number per trace
			long m_nInterval; // sample interval
			int m_lineNumber;	// in-line number
			int m_reelNumber; // CDP number

			/*!
			*
			**/
			HeadInfo() : m_nType(SEGY_IBM), m_nTraceLen(240), m_nTracePt(0), m_nTraceNum(1), m_nInterval(0), m_lineNumber(0), m_reelNumber(0)
			{
			}

			/*!
			*
			**/
			const HeadInfo &operator=(const HeadInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_nTraceNum = other.m_nTraceNum; // total trace number
				m_nTraceLen = other.m_nTraceLen; // trace lenth in bytes
				m_nType = other.m_nType; // segy type
				m_nTracePt = other.m_nTracePt;		// sample number per trace
				m_nInterval = other.m_nInterval; // sample interval
				m_lineNumber = other.m_lineNumber;	// in-line number
				m_reelNumber = other.m_reelNumber; // CDP number

				return *this;
			}
		};

		/*!
		* 定义地震道头结构
		**/
		struct TraceHead
		{
			int m_nOrder;						//道序号
			short m_nPts;						//每道采样点数
			short m_nInterval;					//采样间隔
			int m_nLineNo;						//线号
			int m_nCDPNo;						//道号
			int m_nSourceCrdX;				//大地坐标(source)
			int m_nSourceCrdY;				//大地坐标(source)
			int m_nDetectionCrdX;				//检波点坐标
			int m_nDetectionCrdY;				//检波点坐标
			int m_nCDPCrdX;					//cdp点坐标
			int m_nCDPCrdY;					//cdp点坐标
			int m_nCrdType;					// 坐标系统类型
			short m_nStartTime;				//采样起始时间
			short m_nEndTime;				//采样终止时间
			float m_azimuth;					//方位角
			float m_angle;						//入射角
			float m_distance;						//偏移距

			/*!
			*
			*/
			TraceHead() : m_nOrder(0), m_nPts(0), m_nInterval(0), m_nLineNo(0), m_nCDPNo(0), m_nSourceCrdX(0), m_nSourceCrdY(0), \
				m_nDetectionCrdX(0), m_nDetectionCrdY(0), m_nCDPCrdX(0), m_nCDPCrdY(0), m_nCrdType(1), m_nStartTime(0), m_nEndTime(0), m_azimuth(0), m_angle(0), m_distance(0)
			{
			}

			/*!
			*
			**/
			const TraceHead &operator=(const TraceHead &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_nOrder = other.m_nOrder;				//道序号
				m_nPts = other.m_nPts;						//每道采样点数
				m_nInterval = other.m_nInterval;		//采样间隔
				m_nLineNo = other.m_nLineNo;			//线号
				m_nCDPNo = other.m_nCDPNo;			//道号
				m_nSourceCrdX = other.m_nSourceCrdX;				//大地坐标
				m_nSourceCrdY = other.m_nSourceCrdY;				//大地坐标
				m_nDetectionCrdX = other.m_nDetectionCrdX;
				m_nDetectionCrdY = other.m_nDetectionCrdY;
				m_nCDPCrdX = other.m_nCDPCrdX;
				m_nCDPCrdY = other.m_nCDPCrdY;
				m_nCrdType = other.m_nCrdType;
				m_nStartTime = other.m_nStartTime;	//采样起始时间
				m_nEndTime = other.m_nEndTime;    // 采样结束时间
				m_azimuth = other.m_azimuth;
				m_angle = other.m_angle;
				m_distance = other.m_distance;

				return *this;
			}
		};
		
		/*!
		*
		**/
		struct TraceHeadOffset
		{
			int m_nOrderoffset;						//道序号
			int m_nLineNooffset;						//线号
			int m_nCDPNooffset;						//道号
			int m_nSourceCrdXoffset;				//大地坐标(source)
			int m_nSourceCrdYoffset;				//大地坐标(source)
			int m_nDetectionCrdXoffset;				//检波点坐标
			int m_nDetectionCrdYoffset;				//检波点坐标
			int m_nCDPCrdXoffset;				//cdp点坐标
			int m_nCDPCrdYoffset;				//cdp点坐标
			int m_nCrdTypeoffset;					// 坐标系统类型
			int m_nStartTimeoffset;				//采样起始时间
			int m_nEndTimeoffset;				//采样终止时间
			int m_nPtsoffset;						//每道采样点数
			int m_nIntervaloffset;					//采样间隔
			int m_azimuthoffset;					//方位角
			int m_angleoffset;					//入射角
			int m_distanceoffset;				//偏移距
			
			/*!
			*
			*/
			TraceHeadOffset() : m_nOrderoffset(0), m_nLineNooffset(8), m_nCDPNooffset(20), m_nSourceCrdXoffset(72), m_nSourceCrdYoffset(76), m_nDetectionCrdXoffset(80), m_nDetectionCrdYoffset(84), \
				m_nCDPCrdXoffset(-1), m_nCDPCrdYoffset(-1), m_nCrdTypeoffset(88), m_nStartTimeoffset(108), m_nEndTimeoffset(112), m_nPtsoffset(114), m_nIntervaloffset(116), m_azimuthoffset(232), \
				m_angleoffset(236), m_distanceoffset(36)
			{
			}

			/*!
			*
			**/
			const TraceHeadOffset &operator=(const TraceHeadOffset &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_nOrderoffset = other.m_nOrderoffset;				//道序号
				m_nLineNooffset = other.m_nLineNooffset;			//线号
				m_nCDPNooffset = other.m_nCDPNooffset;			//道号
				m_nSourceCrdXoffset = other.m_nSourceCrdXoffset;				//大地坐标
				m_nSourceCrdYoffset = other.m_nSourceCrdYoffset;				//大地坐标
				m_nDetectionCrdXoffset = other.m_nDetectionCrdXoffset;
				m_nDetectionCrdYoffset = other.m_nDetectionCrdYoffset;
				m_nCDPCrdXoffset = other.m_nCDPCrdXoffset;
				m_nCDPCrdYoffset = other.m_nCDPCrdYoffset;
				m_nCrdTypeoffset = other.m_nCrdTypeoffset;
				m_nStartTimeoffset = other.m_nStartTimeoffset;	//采样起始时间
				m_nEndTimeoffset = other.m_nEndTimeoffset;    // 采样结束时间
				m_nPtsoffset = other.m_nPtsoffset;						//每道采样点数
				m_nIntervaloffset = other.m_nIntervaloffset;		//采样间隔
				m_azimuthoffset = other.m_azimuthoffset;
				m_angleoffset = other.m_angleoffset;
				m_distanceoffset = other.m_distanceoffset;

				return *this;
			}
		};

		/*!
		*
		**/
		struct ProfileInfo
		{
			// default time/depth extent
			int m_defaultStart;
			int m_defaultEnd;

			// user's interesting extent
			int m_userStart;
			int m_userEnd;

			/*!
			*
			**/
			ProfileInfo() : m_defaultStart(0), m_defaultEnd(0), m_userStart(0), m_userEnd(0)
			{
			}

			/*!
			*
			**/
			const ProfileInfo &operator=(const ProfileInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_defaultStart = other.m_defaultStart;
				m_defaultEnd = other.m_defaultEnd;
				m_userStart = other.m_userStart;
				m_userEnd = other.m_userEnd;

				return *this;
			}

			/*!
			*
			**/
			bool IsValidExtent()
			{
				return !(m_userStart < m_defaultStart || m_userStart > m_defaultEnd ||
					m_userEnd < m_userStart || m_userEnd > m_defaultEnd);
			}
		};
		
		/*!
		*
		**/
		struct PosInfo
		{
			int m_gridpos;
			int m_filepos;

			PosInfo() : m_gridpos(-1), m_filepos(-1)
			{
			}
			PosInfo(const PosInfo &other)
			{
				*this = other;
			}
			const PosInfo &operator=(const PosInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}
				
				m_gridpos = other.m_gridpos;
				m_filepos = other.m_filepos;

				return *this;
			}
		};

		/*!
		*
		**/
		struct SurveyInfo
		{
			int m_nLineNum;								// In Line数目
			int m_nCDPNum;								//Cross Line数目
			int m_nStartLine;								//In Line起始编号
			int m_nStartCDP;								//Cross Line起始编号
			short m_nLineIncrement;					//In Line编号间隔	
			short m_nCDPIncrement;					//Cross Line编号间隔
			float m_fOrientation;							//In Line方向：向量a为inline从cdpno小号到大号的方向，向量b为x轴正方向,从b逆时针到a，范围0到2PI
			float m_fDirection;								//Cross Line方向：向量a为xline从lineno小号到大号的方向，向量b为x轴正方向,从b逆时针到a，范围0到2PI
			float m_fOrgX;									//大地起始坐标
			float m_fOrgY;									//大地起始坐标
			float m_fLineSpace;							//In Line大地间隔	
			float m_fCDPSpace;							//Cross Line大地间隔
			short m_crdType;								//大地坐标单位类型
			CGeoRect<double> m_extent;				// geographic extent

			int m_datatype;//0:normal,1:awe,2:ha
			int m_datacount;
			std::vector<bool> m_hasdatas;

			float* m_shotptxs;//炮点x坐标
			float* m_shotptys;//炮点y坐标
			float* m_detectionptxs;//检波点x坐标
			float* m_detectionptys;//检波点y坐标
			float* m_cdpptxs;//cdp点x坐标
			float* m_cdpptys;//cdp点y坐标
			float* m_azimuths;//方位角
			float* m_angles;//入射角
			float* m_distances;//偏移距
			PosInfo* m_gridandfilepos;//测网位置与文件位置对应关系

			int m_pagesize;//一个内存页的大小
			int m_windowpagenum;//一个窗口的内存页个数
			int m_curpage;//当前内存页
			ULONG_PTR *m_aPFNs;
			PVOID m_lpMemReserved;

			int m_ha_filesize;
			int m_ha_viewsize;
			HugeArray<float> m_shotptxs_ha;//炮点x坐标
			HugeArray<float> m_shotptys_ha;//炮点y坐标
			HugeArray<float> m_detectionptxs_ha;//检波点x坐标
			HugeArray<float> m_detectionptys_ha;//检波点y坐标
			HugeArray<float> m_cdpptxs_ha;//cdp点x坐标
			HugeArray<float> m_cdpptys_ha;//cdp点y坐标
			HugeArray<float> m_azimuths_ha;//方位角
			HugeArray<float> m_angles_ha;//入射角
			HugeArray<float> m_distances_ha;//偏移距
			HugeArray<PosInfo> m_gridandfilepos_ha;//测网位置与文件位置对应关系

			/*!
			*
			**/
			SurveyInfo() : m_nLineNum(0), m_nCDPNum(0), m_nStartLine(0), m_nStartCDP(0), m_nLineIncrement(0), m_nCDPIncrement(0), \
				m_fOrientation(0.), m_fDirection(0.), m_fOrgX(0.), m_fOrgY(0.), m_fLineSpace(0.), m_fCDPSpace(0.), m_crdType(1), m_datatype(0), m_datacount(0), \
				m_shotptxs(0), m_shotptys(0), m_detectionptxs(0), m_detectionptys(0), m_cdpptxs(0), m_cdpptys(0), \
				m_azimuths(0), m_angles(0), m_distances(0), m_gridandfilepos(0), m_ha_filesize(0), m_ha_viewsize(0), m_windowpagenum(256), m_curpage(-1), m_aPFNs(0), m_lpMemReserved(0)
			{
				SYSTEM_INFO sSysinfo;
				GetSystemInfo(&sSysinfo);
				m_pagesize = sSysinfo.dwPageSize;
				m_hasdatas.resize(9);
				for(int i = 0; i < 9; i++)
					m_hasdatas[i] = false;
			}
			
			/*!
			*
			**/
			~SurveyInfo()
			{
				Release();
			}

			/*!
			*
			**/
			void Release()
			{
				if(m_datatype == 0)
				{
					if(m_hasdatas[0] && m_shotptxs)
						::free(m_shotptxs);
					m_shotptxs = 0;
					if(m_hasdatas[1] && m_shotptys)
						::free(m_shotptys);
					m_shotptys = 0;
					if(m_hasdatas[2] && m_detectionptxs)
						::free(m_detectionptxs);
					m_detectionptxs = 0;
					if(m_hasdatas[3] && m_detectionptys)
						::free(m_detectionptys);
					m_detectionptys = 0;
					if(m_hasdatas[4] && m_cdpptxs)
						::free(m_cdpptxs);
					m_cdpptxs = 0;
					if(m_hasdatas[5] && m_cdpptys)
						::free(m_cdpptys);
					m_cdpptys = 0;
					if(m_hasdatas[6] && m_azimuths)
						::free(m_azimuths);
					m_azimuths = 0;
					if(m_hasdatas[7] && m_angles)
						::free(m_angles);
					m_angles = 0;
					if(m_hasdatas[8] && m_distances)
						::free(m_distances);
					m_distances = 0;
					if(m_gridandfilepos)
						::free(m_gridandfilepos);
					m_gridandfilepos = 0;
				}
				else if(m_datatype == 1)
				{
					ReleasePage();
					ULONG_PTR NumberOfPages = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9 + ((long long)(sizeof(PosInfo) * m_datacount / m_pagesize) + 1);
					FreeUserPhysicalPages(GetCurrentProcess(), &NumberOfPages, m_aPFNs);
					VirtualFree(m_lpMemReserved, 0, MEM_RELEASE);
					HeapFree(GetProcessHeap(), 0, m_aPFNs);
					m_curpage = -1;
					m_aPFNs = NULL;
					m_lpMemReserved = NULL;
				}
				else if(m_datatype == 2)
				{
					if(m_hasdatas[0])
						m_shotptxs_ha.DeAllocate();
					if(m_hasdatas[1])
						m_shotptys_ha.DeAllocate();
					if(m_hasdatas[2])
						m_detectionptxs_ha.DeAllocate();
					if(m_hasdatas[3])
						m_detectionptys_ha.DeAllocate();
					if(m_hasdatas[4])
						m_cdpptxs_ha.DeAllocate();
					if(m_hasdatas[5])
						m_cdpptys_ha.DeAllocate();
					if(m_hasdatas[6])
						m_azimuths_ha.DeAllocate();
					if(m_hasdatas[7])
						m_angles_ha.DeAllocate();
					if(m_hasdatas[8])
						m_distances_ha.DeAllocate();
					m_gridandfilepos_ha.DeAllocate();
				}
				m_hasdatas.resize(9);
				for(int i = 0; i < 9; i++)
					m_hasdatas[i] = false;
			}

			/*!
			*
			**/
			void ReleasePage()
			{
				if(m_curpage != -1)
				{
					if(m_curpage >= ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9;
						int NumberOfPagesend = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9 + ((long long)(sizeof(PosInfo) * m_datacount / m_pagesize) + 1);
						int windowoffset = (m_curpage - NumberOfPagesstart) / m_windowpagenum;
						if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
							MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), 0);
						else
							MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, 0);
					}
					else 
					{
						int offset = m_curpage / ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * offset;
						int NumberOfPagesend = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * offset + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = (m_curpage - NumberOfPagesstart) / m_windowpagenum;
						if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
							MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), 0);
						else
							MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, 0);
					}
				}
				m_curpage = -1;
			}

			/*!
			*
			**/
			const SurveyInfo &operator=(const SurveyInfo &other)
			{
				if(this == &other)
				{
					return *this;
				}

				Release();
				m_nLineNum = other.m_nLineNum;					// In Line数目
				m_nCDPNum = other.m_nCDPNum;					//Cross Line数目
				m_nStartLine = other.m_nStartLine;				//In Line起始编号
				m_nStartCDP = other.m_nStartCDP;				//Cross Line起始编号
				m_nLineIncrement = other.m_nLineIncrement;	//In Line编号间隔	
				m_nCDPIncrement = other.m_nCDPIncrement;	//Cross Line编号间隔
				m_fOrientation = other.m_fOrientation;			//In Line方位角，CDP小号到大号的方向，与x轴方向的夹角,0到PI
				m_fDirection = other.m_fDirection;					//Cross Line相对于In Line的顺时针方位角,-PI到PI
				m_fOrgX = other.m_fOrgX;								//大地起始坐标
				m_fOrgY = other.m_fOrgY;								//大地起始坐标
				m_fLineSpace = other.m_fLineSpace;				//In Line大地间隔	
				m_fCDPSpace = other.m_fCDPSpace;				//Cross Line大地间隔
				m_crdType = other.m_crdType;						//大地坐标单位标识
				m_extent = other.m_extent;

				m_datatype = other.m_datatype;
				m_datacount = other.m_datacount;
				m_hasdatas = other.m_hasdatas;
				
				if(other.m_datatype == 0)
				{
					if(other.m_hasdatas[0])
					{
						m_shotptxs = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_shotptxs, other.m_shotptxs, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[1])
					{
						m_shotptys = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_shotptys, other.m_shotptys, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[2])
					{
						m_detectionptxs = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_detectionptxs, other.m_detectionptxs, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[3])
					{
						m_detectionptys = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_detectionptys, other.m_detectionptys, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[4])
					{
						m_cdpptxs = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_cdpptxs, other.m_cdpptxs, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[5])
					{
						m_cdpptys = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_cdpptys, other.m_cdpptys, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[6])
					{
						m_azimuths = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_azimuths, other.m_azimuths, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[7])
					{
						m_angles = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_angles, other.m_angles, other.m_datacount * sizeof(float));
					}
					if(other.m_hasdatas[8])
					{
						m_distances = (float*)::malloc(other.m_datacount * sizeof(float));
						::memcpy(m_distances, other.m_distances, other.m_datacount * sizeof(float));
					}
					{
						m_gridandfilepos = (PosInfo*)::malloc(other.m_datacount * sizeof(PosInfo));
						::memcpy(m_gridandfilepos, other.m_gridandfilepos, other.m_datacount * sizeof(PosInfo));
					}
				}
				return *this;
			}

			/*!
			*
			**/
			void CopyOtherAWE(SurveyInfo &other)
			{
				if(other.m_datatype == 1)
				{
					// release
					{
						ReleasePage();
						ULONG_PTR NumberOfPages = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9 + ((long long)(sizeof(PosInfo) * m_datacount / m_pagesize) + 1);
						FreeUserPhysicalPages(GetCurrentProcess(), &NumberOfPages, m_aPFNs);
						VirtualFree(m_lpMemReserved, 0, MEM_RELEASE);
						HeapFree(GetProcessHeap(), 0, m_aPFNs);
						m_curpage = -1;
						m_aPFNs = NULL;
						m_lpMemReserved = NULL;
						other.ReleasePage();
					}
					m_pagesize = other.m_pagesize;
					m_windowpagenum = other.m_windowpagenum;
					m_curpage = -1;
					BOOL bResult;
					ULONG_PTR NumberOfPages = ((long long)(sizeof(float) * other.m_datacount / other.m_pagesize) + 1) * 9 + ((long long)(sizeof(PosInfo) * other.m_datacount / other.m_pagesize) + 1);
					m_aPFNs = (ULONG_PTR*)::HeapAlloc(GetProcessHeap(), 0, NumberOfPages * sizeof(ULONG_PTR));
					bResult = AWESetLockPagesPrivilege(GetCurrentProcess(), TRUE);
					bResult = AllocateUserPhysicalPages(GetCurrentProcess(), &NumberOfPages, m_aPFNs);
					m_lpMemReserved = VirtualAlloc(NULL, other.m_pagesize * other.m_windowpagenum, MEM_RESERVE | MEM_PHYSICAL, PAGE_READWRITE);
					for(int i = 0; i < NumberOfPages; i = i + m_windowpagenum)
					{
						if(i + m_windowpagenum >= NumberOfPages)
						{
							MapUserPhysicalPages(m_lpMemReserved, NumberOfPages - i, m_aPFNs + i);
							MapUserPhysicalPages(other.m_lpMemReserved, NumberOfPages - i, other.m_aPFNs + i);
							::memcpy(m_lpMemReserved, other.m_lpMemReserved, (NumberOfPages - i) * m_pagesize);
							MapUserPhysicalPages(m_lpMemReserved, NumberOfPages - i, 0);
							MapUserPhysicalPages(other.m_lpMemReserved, NumberOfPages - i, 0);
						}
						else
						{
							MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + i);
							MapUserPhysicalPages(other.m_lpMemReserved, m_windowpagenum, other.m_aPFNs + i);
							::memcpy(m_lpMemReserved, other.m_lpMemReserved, m_windowpagenum * m_pagesize);
							MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, 0);
							MapUserPhysicalPages(other.m_lpMemReserved, m_windowpagenum, 0);
						}
					}
				}
			}

			/*!
			*
			**/
			void SetAWEwindowpagenum(int windowpagenum)
			{
				if(m_datatype == 1 && m_windowpagenum != windowpagenum)
				{
					ReleasePage();
					VirtualFree(m_lpMemReserved, 0, MEM_RELEASE);
					m_windowpagenum = windowpagenum;
					m_lpMemReserved = VirtualAlloc(NULL, m_pagesize * m_windowpagenum, MEM_RESERVE | MEM_PHYSICAL, PAGE_READWRITE);
				}
			}

			/*!
			*
			**/
			void CopyOtherHugeArray(wstring myfilename, SurveyInfo &other)
			{
				if(m_datatype == 2)
				{
					m_ha_filesize = other.m_ha_filesize;
					m_ha_viewsize = other.m_ha_viewsize;
					other.m_shotptxs_ha.ClearContents();
					other.m_shotptys_ha.ClearContents();
					other.m_detectionptxs_ha.ClearContents();
					other.m_detectionptys_ha.ClearContents();
					other.m_cdpptxs_ha.ClearContents();
					other.m_cdpptys_ha.ClearContents();
					other.m_azimuths_ha.ClearContents();
					other.m_angles_ha.ClearContents();
					other.m_distances_ha.ClearContents();
					other.m_gridandfilepos_ha.ClearContents();
					string filepath = (char*)(_bstr_t)(myfilename.c_str());
					string filedir = filepath.substr(0, filepath.find_last_of("."));
					{
						filedir = filedir + "\\";
						TCHAR wbuf[1024] = {0, };
						CAnyStringBasic::Get().Ascii2Wcs((char *)filedir.c_str(), wbuf, 1024);
						wstring wfiledir = wbuf;
						if(!CAnyDirBasic::Get().IsDirExist(wfiledir))
							CAnyDirBasic::Get().CreateDir(wfiledir);
					}
					filepath = filedir;
					if(other.m_hasdatas[0])
					{
						string filedir = filepath + "shotptxs";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_shotptxs_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[0] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_shotptxs_ha.Allocate((long long)other.m_shotptxs_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_shotptxs_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_shotptxs_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_shotptxs_ha._GetAt(i), other.m_shotptxs_ha._GetAt(i), sizeof(float) * other.m_shotptxs_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_shotptxs_ha._GetAt(i), other.m_shotptxs_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[1])
					{
						string filedir = filepath + "shotptys";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_shotptys_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[1] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_shotptys_ha.Allocate((long long)other.m_shotptys_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_shotptys_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_shotptys_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_shotptys_ha._GetAt(i), other.m_shotptys_ha._GetAt(i), sizeof(float) * other.m_shotptys_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_shotptys_ha._GetAt(i), other.m_shotptys_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[2])
					{
						string filedir = filepath + "detectionptxs";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_detectionptxs_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[2] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_detectionptxs_ha.Allocate((long long)other.m_detectionptxs_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_detectionptxs_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_detectionptxs_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_detectionptxs_ha._GetAt(i), other.m_detectionptxs_ha._GetAt(i), sizeof(float) * other.m_detectionptxs_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_detectionptxs_ha._GetAt(i), other.m_detectionptxs_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[3])
					{
						string filedir = filepath + "detectionptys";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_detectionptys_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[3] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_detectionptys_ha.Allocate((long long)other.m_detectionptys_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_detectionptys_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_detectionptys_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_detectionptys_ha._GetAt(i), other.m_detectionptys_ha._GetAt(i), sizeof(float) * other.m_detectionptys_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_detectionptys_ha._GetAt(i), other.m_detectionptys_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[4])
					{
						string filedir = filepath + "cdpptxs";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_cdpptxs_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[4] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_cdpptxs_ha.Allocate((long long)other.m_cdpptxs_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_cdpptxs_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_cdpptxs_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_cdpptxs_ha._GetAt(i), other.m_cdpptxs_ha._GetAt(i), sizeof(float) * other.m_cdpptxs_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_cdpptxs_ha._GetAt(i), other.m_cdpptxs_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[5])
					{
						string filedir = filepath + "cdpptys";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_cdpptys_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[5] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_cdpptys_ha.Allocate((long long)other.m_cdpptys_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_cdpptys_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_cdpptys_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_cdpptys_ha._GetAt(i), other.m_cdpptys_ha._GetAt(i), sizeof(float) * other.m_cdpptys_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_cdpptys_ha._GetAt(i), other.m_cdpptys_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[6])
					{
						string filedir = filepath + "azimuths";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_azimuths_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[6] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_azimuths_ha.Allocate((long long)other.m_azimuths_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_azimuths_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_azimuths_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_azimuths_ha._GetAt(i), other.m_azimuths_ha._GetAt(i), sizeof(float) * other.m_azimuths_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_azimuths_ha._GetAt(i), other.m_azimuths_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[7])
					{
						string filedir = filepath + "angles";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_angles_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[7] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_angles_ha.Allocate((long long)other.m_angles_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_angles_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_angles_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_angles_ha._GetAt(i), other.m_angles_ha._GetAt(i), sizeof(float) * other.m_angles_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_angles_ha._GetAt(i), other.m_angles_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					if(other.m_hasdatas[8])
					{
						string filedir = filepath + "distances";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_distances_ha.m_lpszDirPath;
						if(CAnyDirBasic::Get().IsDirExist(otherfiledirw))
						{
							m_hasdatas[8] = true;
							string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
							m_distances_ha.Allocate((long long)other.m_distances_ha._AllocatedLen, filedirw.c_str());
							if(filedirw != otherfiledirw)
							{
								for(int i = 0; i < other.m_datacount; i = i + other.m_distances_ha.m_parameter._NoOfElemsPerView)
								{
									if(i + other.m_distances_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
										::memcpy(m_distances_ha._GetAt(i), other.m_distances_ha._GetAt(i), sizeof(float) * other.m_distances_ha.m_parameter._NoOfElemsPerView);
									else
										::memcpy(m_distances_ha._GetAt(i), other.m_distances_ha._GetAt(i), sizeof(float) * (other.m_datacount - i));
								}
							}
						}
					}
					{
						string filedir = filepath + "gridandfilepos";
						wstring filedirw = (wchar_t*)(_bstr_t)filedir.c_str();
						wstring otherfiledirw = other.m_gridandfilepos_ha.m_lpszDirPath;
						string otherfiledir = (char*)(_bstr_t)otherfiledirw.c_str();
						m_gridandfilepos_ha.Allocate((long long)other.m_gridandfilepos_ha._AllocatedLen, filedirw.c_str());
						if(filedirw != otherfiledirw)
						{
							for(int i = 0; i < other.m_datacount; i = i + other.m_gridandfilepos_ha.m_parameter._NoOfElemsPerView)
							{
								if(i + other.m_gridandfilepos_ha.m_parameter._NoOfElemsPerView < other.m_datacount)
									::memcpy(m_gridandfilepos_ha._GetAt(i), other.m_gridandfilepos_ha._GetAt(i), sizeof(PosInfo) * other.m_gridandfilepos_ha.m_parameter._NoOfElemsPerView);
								else
									::memcpy(m_gridandfilepos_ha._GetAt(i), other.m_gridandfilepos_ha._GetAt(i), sizeof(PosInfo) * (other.m_datacount - i));
							}
						}
					}
				}		
			}

			/*!
			*
			**/
			bool Sequence2Survey(long sequenceOrder, double &lineNo, double &cdpNo)
			{
				if(sequenceOrder < 0 || sequenceOrder >= m_nCDPNum * m_nLineNum)
					return false;
				int lineOrder = sequenceOrder / m_nCDPNum;
				int CDPOrder = sequenceOrder % m_nCDPNum;
				lineNo = m_nStartLine + lineOrder * m_nLineIncrement;
				cdpNo = m_nStartCDP + CDPOrder * m_nCDPIncrement;
				return true;
			}
						
			/*!
			*
			**/
			bool Survey2Sequence(double LineNo, double CDPNo, long &sequenceOrder)
			{
				double tempCDP = CDPNo - m_nStartCDP;
				tempCDP = Dither(tempCDP, m_nCDPIncrement);
				int CDPOrder = (int)(tempCDP / m_nCDPIncrement);
				if(CDPOrder < 0)
					return false;
				if(abs(CDPOrder) >= m_nCDPNum)
					return false;
				CDPOrder = abs(CDPOrder);

				if(m_nLineIncrement == 0)
				{
					sequenceOrder = CDPOrder;
					return true;
				}

				double tempLine = LineNo - m_nStartLine;
				tempLine = Dither(tempLine, m_nLineIncrement);
				int lineOrder = (int)(tempLine / m_nLineIncrement);
				if(lineOrder < 0)
					return false;
				if(abs(lineOrder) >= m_nLineNum)
					return false;
				lineOrder = abs(lineOrder);

				sequenceOrder = lineOrder * m_nCDPNum + CDPOrder;
				return true;
			}

			/*!
			*
			**/
			bool Survey2Coord(double lineNo, double cdpNo, CGeoPoint<double> &pt)
			{
				// 将线号道号转换为线和道两个方向上的偏移距离
				double tempCDP = cdpNo - m_nStartCDP;
				tempCDP = Dither(tempCDP, m_nCDPIncrement);
				tempCDP = (int)(tempCDP / m_nCDPIncrement) * m_fCDPSpace;//CDP间距方向，即测线方向
				double tempLine = lineNo - m_nStartLine;
				tempLine = Dither(tempLine, m_nLineIncrement);
				tempLine = (int)(tempLine / m_nLineIncrement) * m_fLineSpace;//Line间距方向，即CDP方向
				// 将线和道两个方向上的偏移距离转换为x,y上的偏移距离，并求出pt
				pt.m_x = m_fOrgX + tempCDP * cos(m_fOrientation) + tempLine * cos(m_fDirection);
				pt.m_y = m_fOrgY + tempCDP * sin(m_fOrientation) + tempLine * sin(m_fDirection);
				return true;
			}
			
			/*!
			*
			**/
			bool Coord2Survey(CGeoPoint<double> pt, double &lineNo, double &cdpNo)
			{
				// 求出pt在线和道两个方向上的偏移距离
				double tempCDP = (pt.m_x - m_fOrgX) * cos(m_fOrientation) + (pt.m_y - m_fOrgY) * sin(m_fOrientation);//CDP间距方向，即测线方向
				double tempLine = (pt.m_x - m_fOrgX) * cos(m_fDirection) + (pt.m_y - m_fOrgY) * sin(m_fDirection);//Line间距方向，即CDP方向
				tempCDP = Dither(tempCDP, m_fCDPSpace);
				tempLine = Dither(tempLine, m_fLineSpace);
				// 将偏移距离转换为线号和道号的偏移量
				int CDPIndex = (int)(tempCDP / m_fCDPSpace);
				int lineIndex = (int)(tempLine / m_fLineSpace);
				cdpNo = m_nStartCDP + CDPIndex * m_nCDPIncrement;
				lineNo = m_nStartLine + lineIndex * m_nLineIncrement;
				if(CDPIndex < 0)
					return false;
				if(abs(CDPIndex) >= m_nCDPNum)
					return false;
				if(lineIndex < 0)
					return false;
				if(abs(lineIndex) >= m_nLineNum)
					return false;
				// 求出真正的线号道号
				return true;
			}

			/*!
			*
			**/
			long GetTotalTraceNumber()
			{
				return m_nLineNum * m_nCDPNum;
			}

			/*!
			*
			**/
			bool Is3D() const
			{
				if(m_nLineNum <= 1 || m_nCDPNum <= 1)
				{
					return false;
				}

				return true;
			}

			/*!
			*
			**/
			bool IsEastDirection()
			{
				return m_fOrientation == 0.;
			}

			/*!
			*
			**/
			long GetLineOrder(long sequenceOrder) const
			{
				return ::floor(sequenceOrder * 1./m_nCDPNum);
			}

			/*!
			*
			**/
			long GetCDPOrder(long sequenceOrder) const
			{
				return sequenceOrder % m_nCDPNum;
			}

			/*!
			*
			**/
			bool IsValid()
			{
				if(m_nLineNum <= 0 || m_nCDPNum <= 0 || (m_fLineSpace <= 0. && m_fCDPSpace <= 0.) || 
					(m_extent.Width() <= 0. && m_extent.Height() <= 0.))
				{
					return false;
				}

				return true;
			}
			
			/*!
			*
			**/
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
			
			/*!
			*
			**/
			/*void QuickSortPosInfoUpOrder(int zz, int yy)
			{
				int z, y;
				if(zz < yy)
				{
					z = zz;
					y = yy;
					PosInfo k = GetData_Posinfo(z);
					do
					{
						while((z < y) && isGreater(GetData_Posinfo(y), k))
							y--;
						if(z < y)
						{
							GetData_Posinfo(z) = GetData_Posinfo(y);
							z = z + 1;
						}
						while((z < y) && isSmaller(GetData_Posinfo(z), k))
							z++;
						if(z < y)
						{
							GetData_Posinfo(y) = GetData_Posinfo(z);
						}
					} while(z != y);
					GetData_Posinfo(z) = k;
					QuickSortPosInfoUpOrder(zz, z - 1);
					QuickSortPosInfoUpOrder(z + 1, yy);
				}
			}
			void QuickSortPosInfoUpOrder2(int low, int high)
			{
				stack<int> st;
				if(low < high)
				{
					int mid = partition(low, high);
					if(low < mid - 1)
					{
						st.push(low);
						st.push(mid - 1);
					}
					if(mid + 1 < high)
					{
						st.push(mid + 1);
						st.push(high);
					}
					while(!st.empty())
					{
						int q = st.top();
						st.pop();
						int p = st.top();
						st.pop();
						mid = partition(p, q);
						if(p < mid - 1)
						{
							st.push(p);
							st.push(mid - 1);
						}
						if(mid + 1 < q)
						{
							st.push(mid + 1);
							st.push(q);
						}
					}
				}
			}
			int partition(int low, int high)
			{
				PosInfo pivot = GetData_Posinfo(low);
				while(low < high)
				{
					while(low < high && isGreater(GetData_Posinfo(high), pivot))
						high--;
					GetData_Posinfo(low) = GetData_Posinfo(high);
					while(low < high && isSmaller(GetData_Posinfo(low), pivot))
						low++;
					GetData_Posinfo(high) = GetData_Posinfo(low);
				}
				GetData_Posinfo(low) = pivot;
				return low;
			}
			bool isGreater(PosInfo &a, PosInfo &b)
			{
				if(a.m_gridpos > b.m_gridpos)
					return true;
				if(a.m_gridpos < b.m_gridpos)
					return false;
				if(a.m_filepos >= b.m_filepos)
					return true;
				return false;
			}
			bool isSmaller(PosInfo &a, PosInfo &b)
			{
				if(a.m_gridpos < b.m_gridpos)
					return true;
				if(a.m_gridpos > b.m_gridpos)
					return false;
				if(a.m_filepos <= b.m_filepos)
					return true;
				return false;
			}
			bool isGreaterTrue(PosInfo &a, PosInfo &b)
			{
				if(a.m_gridpos > b.m_gridpos)
					return true;
				if(a.m_gridpos < b.m_gridpos)
					return false;
				if(a.m_filepos > b.m_filepos)
					return true;
				return false;
			}
			bool isSmallerTrue(PosInfo &a, PosInfo &b)
			{
				if(a.m_gridpos < b.m_gridpos)
					return true;
				if(a.m_gridpos > b.m_gridpos)
					return false;
				if(a.m_filepos < b.m_filepos)
					return true;
				return false;
			}
			void HeapSortPosInfoUpOrder()
			{
				int n = m_datacount;
				if(n <= 1)
					return;
				int i, j, h, k;
				PosInfo t;
				for(i = n / 2 - 1; i >= 0; i--)
				{
					while(2 * i + 1 < n)
					{
						j = 2 * i + 1;
						if((j + 1) < n)
						{
							if(isSmallerTrue(GetData_Posinfo(j), GetData_Posinfo(j + 1)))
								j++;
						}
						if(isSmallerTrue(GetData_Posinfo(i), GetData_Posinfo(j)))
						{
							t = GetData_Posinfo(i);
							GetData_Posinfo(i) = GetData_Posinfo(j);
							GetData_Posinfo(j) = t;
							i = j;
						}
						else
						{
							break;
						}
					}
				}
				for(i = n - 1; i > 0; i--)
				{
					t = GetData_Posinfo(0);
					GetData_Posinfo(0) = GetData_Posinfo(i);
					GetData_Posinfo(i) = t;
					k = 0;
					while(2 * k + 1 < i)
					{
						j = 2 * k + 1;
						if((j + 1) < i)
						{
							if(isSmallerTrue(GetData_Posinfo(j), GetData_Posinfo(j + 1)))
							{
								j++;
							}
						}
						if(isSmallerTrue(GetData_Posinfo(k), GetData_Posinfo(j)))
						{
							t = GetData_Posinfo(k);
							GetData_Posinfo(k) = GetData_Posinfo(j);
							GetData_Posinfo(j) = t;
							k = j;
						}
						else
						{
							break;
						}
					}
				}
			}*/
			void QSortPosInfoUpOrder()
			{
				if(m_datatype == 0)
				{
					::qsort(m_gridandfilepos, m_datacount, sizeof(PosInfo), CompareValue);
				}
				else if(m_datatype == 1)
				{
					int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9;
					int NumberOfPagesend = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9 + ((long long)(sizeof(PosInfo) * m_datacount / m_pagesize) + 1);
					for(int i = NumberOfPagesstart; i < NumberOfPagesend; i = i + m_windowpagenum)
					{
						if(m_curpage != i)
						{
							ReleasePage();
							m_curpage = i;
						}
						if(i + m_windowpagenum >= NumberOfPagesend)
						{
							MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - i, m_aPFNs + i);
							if((NumberOfPagesend - NumberOfPagesstart) * m_pagesize >= m_datacount * sizeof(PosInfo))
								::qsort((PosInfo*)m_lpMemReserved, (m_datacount * sizeof(PosInfo) - (i - NumberOfPagesstart) * m_pagesize) / sizeof(PosInfo), sizeof(PosInfo), CompareValue);
							else
								::qsort((PosInfo*)m_lpMemReserved, (NumberOfPagesend - i) * m_pagesize / sizeof(PosInfo), sizeof(PosInfo), CompareValue);
						}
						else
						{
							MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + i);
							if((i - NumberOfPagesstart + m_windowpagenum) * m_pagesize >= m_datacount * sizeof(PosInfo))
								::qsort((PosInfo*)m_lpMemReserved, (m_datacount * sizeof(PosInfo) - (i - NumberOfPagesstart) * m_pagesize) / sizeof(PosInfo), sizeof(PosInfo), CompareValue);
							else
								::qsort((PosInfo*)m_lpMemReserved, m_windowpagenum * m_pagesize / sizeof(PosInfo), sizeof(PosInfo), CompareValue);
						}
					}
				}
				else if(m_datatype == 2)
				{
					for(int i = 0; i < m_datacount; i = i + m_gridandfilepos_ha.m_parameter._NoOfElemsPerView)
					{
						if(i + m_gridandfilepos_ha.m_parameter._NoOfElemsPerView < m_datacount)
							::qsort(m_gridandfilepos_ha._GetAt(i), m_gridandfilepos_ha.m_parameter._NoOfElemsPerView, sizeof(PosInfo), CompareValue);
						else
							::qsort(m_gridandfilepos_ha._GetAt(i), (m_datacount - i), sizeof(PosInfo), CompareValue);
					}
				}
			}
			static int CompareValue(const void *a, const void *b)
			{
				if(((PosInfo*)a)->m_gridpos > ((PosInfo*)b)->m_gridpos)
					return 1;
				if(((PosInfo*)a)->m_gridpos < ((PosInfo*)b)->m_gridpos)
					return -1;
				if(((PosInfo*)a)->m_filepos > ((PosInfo*)b)->m_filepos)
					return 1;
				if(((PosInfo*)a)->m_filepos < ((PosInfo*)b)->m_filepos)
					return -1;
				return 0;
			}

			/*!
			*
			**/
			/*int Gridpos2Filepos(int gridpos, int &count)
			{
				count = 0;
				bool find = false;
				int low = 0, high = m_datacount - 1, mid;
				while(low <= high)
				{
					mid = low + (high - low) / 2;
					if(GetData_Posinfo(mid).m_gridpos == gridpos)
					{
						find = true;
						break;
					}
					if(GetData_Posinfo(mid).m_gridpos > gridpos)
						high = mid - 1;
					else
						low = mid + 1;
				}
				if(!find)
					return -1;
				while(mid >= 0 && GetData_Posinfo(mid).m_gridpos == gridpos)
					mid--;
				if(mid == -1 || GetData_Posinfo(mid).m_gridpos != gridpos)
					mid++;
				int filepos = GetData_Posinfo(mid).m_filepos;
				while(mid < m_datacount && GetData_Posinfo(mid).m_gridpos == gridpos)
				{
					count++;
					mid++;
				}
				return filepos;
			}*/

			/*!
			*
			**/
			void Gridpos2Filepos(int gridpos, std::vector<int> &fileposes)
			{
				fileposes.clear();
				if(m_datatype == 0)
				{
					bool find = false;
					int low = 0, high = m_datacount - 1, mid;
					while(low <= high)
					{
						mid = low + (high - low) / 2;
						if(GetData_Posinfo(mid).m_gridpos == gridpos)
						{
							find = true;
							break;
						}
						if(GetData_Posinfo(mid).m_gridpos > gridpos)
							high = mid - 1;
						else
							low = mid + 1;
					}
					if(!find)
						return;
					while(mid >= 0 && GetData_Posinfo(mid).m_gridpos == gridpos)
						mid--;
					if(mid == -1 || GetData_Posinfo(mid).m_gridpos != gridpos)
						mid++;
					while(mid < m_datacount && GetData_Posinfo(mid).m_gridpos == gridpos)
					{
						fileposes.push_back(GetData_Posinfo(mid).m_filepos);
						mid++;
					}
				}
				else if(m_datatype == 1)
				{
					for(int i = 0; i < m_datacount; i = i + m_windowpagenum * m_pagesize / sizeof(PosInfo))
					{
						int lowbound = i;
						int highbound = (i + m_windowpagenum * m_pagesize / sizeof(PosInfo) < m_datacount) ? (i + m_windowpagenum * m_pagesize / sizeof(PosInfo)) : m_datacount;
						bool find = false;
						int low = lowbound;
						int high = highbound - 1;
						int mid;
						while(low <= high)
						{
							mid = low + (high - low) / 2;
							if(GetData_Posinfo(mid).m_gridpos == gridpos)
							{
								find = true;
								break;
							}
							if(GetData_Posinfo(mid).m_gridpos > gridpos)
								high = mid - 1;
							else
								low = mid + 1;
						}
						if(!find)
							continue;
						while(mid >= lowbound && GetData_Posinfo(mid).m_gridpos == gridpos)
							mid--;
						if(mid == lowbound - 1 || GetData_Posinfo(mid).m_gridpos != gridpos)
							mid++;
						while(mid < highbound && GetData_Posinfo(mid).m_gridpos == gridpos)
						{
							fileposes.push_back(GetData_Posinfo(mid).m_filepos);
							mid++;
						}
					}
				}
				else if(m_datatype == 2)
				{
					for(int i = 0; i < m_datacount; i = i + m_gridandfilepos_ha.m_parameter._NoOfElemsPerView)
					{
						int lowbound = i;
						int highbound = (i + m_gridandfilepos_ha.m_parameter._NoOfElemsPerView < m_datacount) ? (i + m_gridandfilepos_ha.m_parameter._NoOfElemsPerView) : m_datacount;
						bool find = false;
						int low = lowbound;
						int high = highbound - 1;
						int mid;
						while(low <= high)
						{
							mid = low + (high - low) / 2;
							if(GetData_Posinfo(mid).m_gridpos == gridpos)
							{
								find = true;
								break;
							}
							if(GetData_Posinfo(mid).m_gridpos > gridpos)
								high = mid - 1;
							else
								low = mid + 1;
						}
						if(!find)
							continue;
						while(mid >= lowbound && GetData_Posinfo(mid).m_gridpos == gridpos)
							mid--;
						if(mid == lowbound - 1 || GetData_Posinfo(mid).m_gridpos != gridpos)
							mid++;
						while(mid < highbound && GetData_Posinfo(mid).m_gridpos == gridpos)
						{
							fileposes.push_back(GetData_Posinfo(mid).m_filepos);
							mid++;
						}
					}
				}
			}

			/*!
			*
			**/
			PosInfo &GetData_Posinfo(int offset)
			{
				if(m_datatype == 0)
					return m_gridandfilepos[offset];
				else if(m_datatype == 1)
				{
					int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9;
					int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(PosInfo) * m_datacount / m_pagesize) + 1);
					int windowoffset = offset * sizeof(PosInfo) / (m_pagesize * m_windowpagenum);
					if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
					{
						ReleasePage();
						if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
							MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						else
							MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
					}
					int elementoffset = offset * sizeof(PosInfo) - windowoffset * m_pagesize * m_windowpagenum;
					return *((PosInfo*)((unsigned char*)m_lpMemReserved + elementoffset));
				}
				else if(m_datatype == 2)
					return m_gridandfilepos_ha[(long long)offset];
			}
			float &GetData_float(int datatype, int offset)
			{
				if(datatype == 0 && m_hasdatas[0])
				{
					if(m_datatype == 0)
						return m_shotptxs[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_shotptxs_ha[(long long)offset];
				}
				else if(datatype == 1 && m_hasdatas[1])
				{
					if(m_datatype == 0)
						return m_shotptys[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_shotptys_ha[(long long)offset];
				}
				else if(datatype == 2 && m_hasdatas[2])
				{
					if(m_datatype == 0)
						return m_detectionptxs[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_detectionptxs_ha[(long long)offset];
				}
				else if(datatype == 3 && m_hasdatas[3])
				{
					if(m_datatype == 0)
						return m_detectionptys[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_detectionptys_ha[(long long)offset];
				}
				else if(datatype == 4 && m_hasdatas[4])
				{
					if(m_datatype == 0)
						return m_cdpptxs[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_cdpptxs_ha[(long long)offset];
				}
				else if(datatype == 5 && m_hasdatas[5])
				{
					if(m_datatype == 0)
						return m_cdpptys[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_cdpptys_ha[(long long)offset];
				}
				else if(datatype == 6 && m_hasdatas[6])
				{
					if(m_datatype == 0)
						return m_azimuths[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_azimuths_ha[(long long)offset];
				}
				else if(datatype == 7 && m_hasdatas[7])
				{
					if(m_datatype == 0)
						return m_angles[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_angles_ha[(long long)offset];
				}
				else if(datatype == 8 && m_hasdatas[8])
				{
					if(m_datatype == 0)
						return m_distances[offset];
					else if(m_datatype == 1)
					{
						int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * datatype;
						int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
						int windowoffset = offset * sizeof(float) / (m_pagesize * m_windowpagenum);
						if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
						{
							ReleasePage();
							if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
								MapUserPhysicalPages(m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							else
								MapUserPhysicalPages(m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
							m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
						}
						int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
						return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
					}
					else if(m_datatype == 2)
						return m_distances_ha[(long long)offset];
				}
				else
				{
					float tmp = 0;
					return tmp;
				}
			}

			/*!
			*
			**/
			BOOL AWESetLockPagesPrivilege(HANDLE hProcess, BOOL Enable)
			{
				HANDLE Token = NULL;
				BOOL Result = FALSE;
				TOKEN_PRIVILEGES Info = {0};
				Result = OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &Token);
				if(!Result)
				{
					return FALSE;
				}
				Info.PrivilegeCount = 1;
				Info.Privileges[0].Attributes = Enable ? SE_PRIVILEGE_ENABLED : 0;
				Result = LookupPrivilegeValue(NULL, SE_LOCK_MEMORY_NAME, &(Info.Privileges[0].Luid));
				if(!Result)
				{
					CloseHandle(Token);
					return FALSE;
				}
				Result = AdjustTokenPrivileges(Token, FALSE, (PTOKEN_PRIVILEGES)&Info, 0, NULL, NULL);
				if(!(Result) || (GetLastError() != ERROR_SUCCESS))
				{
					CloseHandle(Token);
					return FALSE;
				}
				CloseHandle(Token);
				return TRUE;
			}
		};

		/*!
		*
		**/
		struct TraceRecord
		{
			long m_hcode;
			CGeoPoint<double> m_coord;
			long m_order;
			int m_cmpcount;
			// max and min amplitude against this trace
			double m_minA;
			double m_maxA;
			double m_minValue;
			double m_maxValue;
			// time window
			double m_minTime;
			double m_maxTime;
			double m_interval;
			// samples
			int m_number;	
			float *m_samples;
			float *m_times;		// time or depth
			long m_hits;

			/*!
			*
			**/
			TraceRecord() : m_hcode(0), m_order(0), m_cmpcount(1), m_minA(0x7FFFFFFF), m_maxA(-0x7FFFFFFF), m_minValue(0x7FFFFFFF), m_maxValue(-0x7FFFFFFF), \
				m_minTime(ANY_NAN), m_maxTime(ANY_NAN), m_interval(ANY_NAN), m_number(0), m_samples(0), m_times(0), m_hits(0)
			{
			}

			/*!
			*
			**/
			~TraceRecord()
			{
				Release();
			}

			/*!
			*
			**/
			void Delete()
			{
				delete this;
			}

			/*!
			*
			**/
			void Release()
			{
				if(m_samples)
				{
					::free(m_samples);
				}
				m_samples = 0;
				if(m_times)
				{
					::free(m_times);
				}
				m_times = 0;
				m_order = 0;
				m_cmpcount = 1;
				m_samples = 0;
				m_number = 0;
				m_minA = 0x7FFFFFFF;
				m_maxA = -0x7FFFFFFF;
				m_minValue = 0x7FFFFFFF;
				m_maxValue = -0x7FFFFFFF;
				m_minTime = ANY_NAN;
				m_maxTime = ANY_NAN;
				m_interval = ANY_NAN;
				m_hits = 0;
			}

			/*!
			*
			**/
			const TraceRecord &operator=(const TraceRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_hcode = other.m_hcode;
				m_coord = other.m_coord;
				m_order = other.m_order;
				m_cmpcount = other.m_cmpcount;
				m_minA = other.m_minA;
				m_maxA = other.m_maxA;
				m_minValue = other.m_minValue;
				m_maxValue = other.m_maxValue;
				m_minTime = other.m_minTime;
				m_maxTime = other.m_maxTime;
				m_interval = other.m_interval;
				m_number = other.m_number;
				m_hits = other.m_hits;
				if(m_samples)
					::free(m_samples);
				m_samples = (float *)::malloc(other.m_number * other.m_cmpcount * sizeof(float));
				if(m_times)
					::free(m_times);
				m_times = (float *)::malloc(other.m_number * other.m_cmpcount * sizeof(float));
				::memcpy(m_samples, other.m_samples, other.m_number * other.m_cmpcount * sizeof(float));
				::memcpy(m_times, other.m_times, other.m_number * other.m_cmpcount * sizeof(float));
				return *this;
			}

			/*!
			*
			**/
			TraceRecord *Clone()
			{
				TraceRecord *record = new TraceRecord;
				*record = *this;
				return record;
			}

			/*!
			*
			**/
			void GetMaxMin()
			{
				m_minA = 0x7FFFFFFF;
				m_maxA = -0x7FFFFFFF;
				m_minValue = 0x7FFFFFFF;
				m_maxValue = -0x7FFFFFFF;
				for(int cmpoffset = 0; cmpoffset < m_cmpcount; cmpoffset++)
				{
					for(int i = 0; i < m_number; i++)
					{
						m_maxA = ::fabs(m_samples[cmpoffset * m_number + i]) > m_maxA ? ::fabs(m_samples[cmpoffset * m_number + i]) : m_maxA;
						m_minA = ::fabs(m_samples[cmpoffset * m_number + i]) < m_minA ? ::fabs(m_samples[cmpoffset * m_number + i]) : m_minA;
						m_maxValue = m_samples[cmpoffset * m_number + i] > m_maxValue ? m_samples[cmpoffset * m_number + i] : m_maxValue;
						m_minValue = m_samples[cmpoffset * m_number + i] < m_minValue ? m_samples[cmpoffset * m_number + i] : m_minValue;
					}
				}
			}

			/*!
			*
			**/
			bool IsCover(const TraceRecord &other)
			{
				return IsCover(other.m_minTime, other.m_maxTime);
			}

			/*!
			*
			**/
			bool IsCover(double minTime, double maxTime)
			{
				return m_minTime <= minTime && m_maxTime >= maxTime;
			}

			/*!
			*
			**/
			bool IsIntersect(const TraceRecord &other)
			{
				return IsIntersect(other.m_minTime, other.m_maxTime);
			}

			/*!
			*
			**/
			bool IsIntersect(double minTime, double maxTime)
			{
				return !((m_minTime > maxTime) || (m_maxTime < minTime));
			}

			/*!
			*
			**/
			void Merge(TraceRecord *other, int mergetype)
			{
				if(m_cmpcount != other->m_cmpcount)
					return;
				if(!IsIntersect(other->m_minTime, other->m_maxTime))
				{
					*this = *other;
				}
				else
				{
					// merge samples
					std::vector<float> samples;
					std::vector<float> times;
					for(int cmpoffset = 0; cmpoffset < m_cmpcount; cmpoffset++)
					{
						int ownoffset = 0;
						int otheroffset = 0;
						if(mergetype == 0)
						{
							while(other->m_minTime + otheroffset * other->m_interval < m_minTime)
							{
								samples.push_back(other->m_samples[cmpoffset * other->m_number + otheroffset]);
								times.push_back(other->m_times[cmpoffset * other->m_number + otheroffset]);
								otheroffset++;
							}
							for(int i = 0; i < m_number; i++)
							{
								samples.push_back(m_samples[cmpoffset * m_number + i]);
								times.push_back(m_times[cmpoffset * m_number + i]);
							}
							while(other->m_minTime + otheroffset * other->m_interval < m_maxTime)
								otheroffset++;
							while(otheroffset < other->m_number)
							{
								samples.push_back(other->m_samples[cmpoffset * other->m_number + otheroffset]);
								times.push_back(other->m_times[cmpoffset * other->m_number + otheroffset]);
								otheroffset++;
							}
						}
						else
						{
							while(m_minTime + ownoffset * m_interval < other->m_minTime)
							{
								samples.push_back(m_samples[cmpoffset * m_number + ownoffset]);
								times.push_back(m_times[cmpoffset * m_number + ownoffset]);
								ownoffset++;
							}
							for(int i = 0; i < other->m_number; i++)
							{
								samples.push_back(other->m_samples[cmpoffset * other->m_number + i]);
								times.push_back(other->m_times[cmpoffset * other->m_number + i]);
							}
							while(m_minTime + ownoffset * m_interval < other->m_maxTime)
								ownoffset++;
							while(ownoffset < m_number)
							{
								samples.push_back(m_samples[cmpoffset * m_number + ownoffset]);
								times.push_back(m_times[cmpoffset * m_number + ownoffset]);
								ownoffset++;
							}
						}
					}
					m_number = samples.size() / m_cmpcount;
					if(m_samples)
						::free(m_samples);
					m_samples = (float *)::malloc(m_number * m_cmpcount * sizeof(float));
					if(m_times)
						::free(m_times);
					m_times = (float *)::malloc(m_number * m_cmpcount * sizeof(float));
					for(int i = 0; i < m_number * m_cmpcount; i++)
					{
						m_samples[i] = samples[i];
						m_times[i] = times[i];
					}
					m_minA = other->m_minA < m_minA ? other->m_minA : m_minA;
					m_maxA = other->m_maxA > m_maxA ? other->m_maxA : m_maxA;
					m_minValue = other->m_minValue < m_minValue ? other->m_minValue : m_minValue;
					m_maxValue = other->m_maxValue > m_maxValue ? other->m_maxValue : m_maxValue;
					m_minTime = other->m_minTime < m_minTime ? other->m_minTime : m_minTime;
					m_maxTime = other->m_maxTime > m_maxTime ? other->m_maxTime : m_maxTime;
				}
			}

		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataGate() : m_gatetype(0), m_traceheadtype(SEGY_INT)
		{
		}

		/*!
		*
		**/
		virtual ~CAnyGdeDataGate()
		{
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual bool Open(int type = CAnyFileBasic::ANY_FILE_READ, int bufsize = -1) = 0;
		virtual void Close() = 0;

		//
		//
		//
		/*!
		*
		**/
		virtual bool UpdateTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyGdeDataSurvey &survey, CAnyFunctor *progress)
		{
			return false;
		}
		virtual bool UpdateTrace(std::vector<CAnyGdeDataTrace*> &traces, SurveyInfo &survey, CAnyFunctor *progress)
		{
			return false;
		}
		/*!
		*
		**/
		virtual bool CommitTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyGdeDataSurvey &survey, CAnyFunctor *progress, std::vector<std::vector<double> > metas)
		{
			return false;
		}
		virtual bool CommitTrace(std::vector<CAnyGdeDataTrace*> &traces, SurveyInfo &survey, CAnyFunctor *progress, std::vector<std::vector<double> > metas)
		{
			return false;
		}

		//
		//
		//
		/*!
		*
		**/
		virtual long GetCalculatorCubeCount(CalculatorCube::DataCubeSize &cubesize,\
			CAnyGeologicalCubeFeature::SampleVector &horizon) = 0;
		
		/*!
		*
		**/
		virtual bool GetCalculatorCube(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CalculatorCube &cube, CAnyGdeDataSurvey &survey, bool cachemode)
		{
				return false;
		}
				
		/*!
		*
		**/
		virtual bool GetCalculatorCubeTraces(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs, \
			std::vector<CAnyGdeDataTrace*> &traces, CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CAnyGdeDataSurvey &survey)
		{
				return false;
		}

		/*!
		*
		**/
		virtual bool GetCalculatorCube(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CalculatorCube &cube, SurveyInfo &survey, bool cachemode)
		{
				return false;
		}

		/*!
		*
		**/
		virtual bool GetCalculatorCubeLineandCdps(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, CAnyGdeDataSurvey &survey, std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs)
		{
				return false;
		}
		
		/*!
		*
		**/
		virtual bool GetCalculatorCubeLineandCdps(long order, \
			CalculatorCube::DataCubeSize &cubesize, \
			CAnyGeologicalCubeFeature::SampleVector &horizon, SurveyInfo &survey, std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs)
		{
				return false;
		}
				
		/*!
		*
		**/
		virtual bool IsLineandCdpsvalid(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs)
		{
			return false;
		}
				
		/*!
		*
		**/
		virtual int GetCalculatorCubeSequenceFromSurvey(int lineno, int cdpno)
		{
			return -1;
		}

		//
		//
		//
		/*!
		*
		**/
		virtual bool GetDataTrace(std::vector<long> &sequenceOrders, double minTime, double maxTime, \
			CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, CAnyGdeDataSurvey &survey)
		{
			return false;
		}
		virtual bool GetDataTrace(std::vector<long> &sequenceOrders, double minTime, double maxTime, \
			CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, SurveyInfo &survey)
		{
			return false;
		}
		virtual bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, \
			std::vector<std::vector<float*> > &traces, CAnyFunctor *progress, CAnyGdeDataSurvey &survey, bool ispremode, std::vector<std::vector<int> > &gridpos_fileposes)
		{
			return false;
		}
		virtual bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, \
			CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, CAnyGdeDataSurvey &survey)
		{
			return false;
		}
		virtual bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, \
			CAnyGdeDataTrace::TraceVector &traces, CAnyFunctor *progress, SurveyInfo &survey)
		{
			return false;
		}

		virtual CAnyGdeDataTrace *GetDataTrace(long sequenceOrder, double minTime, double maxTime, CAnyGdeDataSurvey &survey)
		{
			return false;
		}

		/*!
		*
		**/
		virtual unsigned long Tile2File(unsigned long tileCode)
		{
			return -1;
		}
		virtual CAnyGdeDataTrace *GetDataTrace(int tileCode)
		{
			return 0;
		}

		/*!
		*
		**/
		virtual bool GetDataTrace(std::vector<long> &sequenceOrders, double minTime, double maxTime, std::vector<CAnyGdeDataGate::TraceRecord*> &records, \
			CAnyFunctor *progress, std::vector<CGeoPoint<double> > &coords) 
		{
			return false;
		}
		virtual bool GetDataTrace(std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, \
			std::vector<CAnyGdeDataGate::TraceRecord*> &records, CAnyFunctor *progress, std::vector<CGeoPoint<double> > &coords)
		{
			return false;
		}

		/*!
		*
		**/
		virtual wstring GetFileName()
		{
			wstring temp;
			return temp;
		}
		
		/*!
		*
		**/
		virtual bool ClearCache(std::vector<long> &savedsequenceOrders)
		{
			return false;
		}
		
		/*!
		*
		**/
		virtual void SetFitCachelimit()
		{
		}

	public:
		// for segy convert
		SurveyInfo m_surveyInfo;// survey info
		CGeoPoint<double> m_pos[4];// for AnySeismic3DGeometry, 0：线最小号，道最小号；1：线最大号，道最小号；2：线最大号，道最大号；3：线最小号，道最大号
		HeadInfo m_headInfo;// head info
		ProfileInfo m_profileInfo;// profile info
		TraceHeadOffset m_traceheadoffset;
		int m_gatetype; 
		int m_traceheadtype;//道头中方位角和入射角两项的数据格式
	};
}
#endif