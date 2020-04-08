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
#ifndef __ANYGDE_MAPREDUCE_TASK_BASIC_H__
#define __ANYGDE_MAPREDUCE_TASK_BASIC_H__

//
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include<windows.h>
#include<memoryapi.h>

#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;
//
#include "any/base/anystl.h"
#include <SF/vector.hpp>
#include <SF/string.hpp>
#include <SF/SerializeParent.hpp>
#include "calculatorcube.h"
#include "any/base/hash/simple_hash.h"
#include "any/gfs/anyservicebasic.h"
using namespace AnyRCF;
#include <tchar.h>
#include "hugearray.h"

//
namespace AnyGDE
{
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
	
	/*!
	*
	**/
	struct TaskPosInfo
	{
		int m_gridpos;
		int m_filepos;

		TaskPosInfo() : m_gridpos(-1), m_filepos(-1)
		{
		}
		TaskPosInfo(const TaskPosInfo &other)
		{
			*this = other;
		}
		const TaskPosInfo &operator=(const TaskPosInfo &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_gridpos = other.m_gridpos;
			m_filepos = other.m_filepos;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gridpos & m_filepos;
		}
	};
		
	/*!
	*
	**/
	struct TaskSurveyInfoData
	{
		int m_datatype;//0:normal,1:awe,2:ha
		int m_datacount;
		std::vector<bool> m_hasdatas;

		float* m_shotptxs;//炮点x坐标
		float* m_shotptys;//炮点y坐标
		float* m_detectionptxs;//检波点x坐标
		float* m_detectionptys;//检波点y坐标
		float* m_azimuths;//方位角
		float* m_angles;//入射角
		TaskPosInfo* m_gridandfilepos;//测网位置与文件位置对应关系

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
		HugeArray<float> m_azimuths_ha;//方位角
		HugeArray<float> m_angles_ha;//入射角
		HugeArray<TaskPosInfo> m_gridandfilepos_ha;//测网位置与文件位置对应关系

		TaskSurveyInfoData() : m_datatype(0), m_datacount(0), m_shotptxs(0), m_shotptys(0), m_detectionptxs(0), m_detectionptys(0), m_gridandfilepos(0), m_ha_filesize(0), m_ha_viewsize(0), \
			m_windowpagenum(256), m_curpage(-1), m_aPFNs(0), m_lpMemReserved(0)
		{
			SYSTEM_INFO sSysinfo;
			GetSystemInfo(&sSysinfo);
			m_pagesize = sSysinfo.dwPageSize;
			m_hasdatas.resize(9);
			for(int i = 0; i < 9; i++)
				m_hasdatas[i] = false;
		}
		~TaskSurveyInfoData()
		{
			Release();
		}
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
				if(m_hasdatas[6] && m_azimuths)
					::free(m_azimuths);
				m_azimuths = 0;
				if(m_hasdatas[7] && m_angles)
					::free(m_angles);
				m_angles = 0;
				if(m_gridandfilepos)
					::free(m_gridandfilepos);
				m_gridandfilepos = 0;
			}
			else if(m_datatype == 1)
			{
				ULONG_PTR NumberOfPages = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9 + ((long long)(sizeof(TaskPosInfo) * m_datacount / m_pagesize) + 1);
				//FreeUserPhysicalPages(GetCurrentProcess(), &NumberOfPages, m_aPFNs);
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
				if(m_hasdatas[6])
					m_azimuths_ha.DeAllocate();
				if(m_hasdatas[7])
					m_angles_ha.DeAllocate();
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
					int NumberOfPagesend = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9 + ((long long)(sizeof(TaskPosInfo) * m_datacount / m_pagesize) + 1);
					int windowoffset = (m_curpage - NumberOfPagesstart) / m_windowpagenum;
					if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
						MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), 0);
					else
						MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, 0);
				}
				else 
				{
					int offset = m_curpage / ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
					int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * offset;
					int NumberOfPagesend = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * offset + ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1);
					int windowoffset = (m_curpage - NumberOfPagesstart) / m_windowpagenum;
					if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
						MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), 0);
					else
						MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, 0);
				}
			}
			m_curpage = -1;
		}

		const TaskSurveyInfoData &operator=(const TaskSurveyInfoData &other)
		{
			if(this == &other)
			{
				return *this;
			}

			Release();
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
				{
					m_gridandfilepos = (TaskPosInfo*)::malloc(other.m_datacount * sizeof(TaskPosInfo));
					::memcpy(m_gridandfilepos, other.m_gridandfilepos, other.m_datacount * sizeof(TaskPosInfo));
				}
			}
			return *this;
		}
		
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
				for(int i = 0; i < m_datacount; i = i + m_windowpagenum * m_pagesize / sizeof(TaskPosInfo))
				{
					int lowbound = i;
					int highbound = (i + m_windowpagenum * m_pagesize / sizeof(TaskPosInfo) < m_datacount) ? (i + m_windowpagenum * m_pagesize / sizeof(TaskPosInfo)) : m_datacount;
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
		TaskPosInfo &GetData_Posinfo(int offset)
		{
			if(m_datatype == 0)
				return m_gridandfilepos[offset];
			else if(m_datatype == 1)
			{
				int NumberOfPagesstart = ((long long)(sizeof(float) * m_datacount / m_pagesize) + 1) * 9;
				int NumberOfPagesend = NumberOfPagesstart + ((long long)(sizeof(TaskPosInfo) * m_datacount / m_pagesize) + 1);
				int windowoffset = offset * sizeof(TaskPosInfo) / (m_pagesize * m_windowpagenum);
				if(m_curpage != NumberOfPagesstart + windowoffset * m_windowpagenum)
				{
					ReleasePage();
					if(NumberOfPagesstart + windowoffset * m_windowpagenum + m_windowpagenum >= NumberOfPagesend)
						MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
					else
						MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
					m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
				}
				int elementoffset = offset * sizeof(TaskPosInfo) - windowoffset * m_pagesize * m_windowpagenum;
				return *((TaskPosInfo*)((unsigned char*)m_lpMemReserved + elementoffset));
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
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						else
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
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
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						else
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
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
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						else
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
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
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						else
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
					}
					int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
					return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
				}
				else if(m_datatype == 2)
					return m_detectionptys_ha[(long long)offset];
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
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						else
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
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
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, NumberOfPagesend - (NumberOfPagesstart + windowoffset * m_windowpagenum), m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						else
							MapUserPhysicalPagesScatter((LPVOID *)&m_lpMemReserved, m_windowpagenum, m_aPFNs + NumberOfPagesstart + windowoffset * m_windowpagenum);
						m_curpage = NumberOfPagesstart + windowoffset * m_windowpagenum;
					}
					int elementoffset = offset * sizeof(float) - windowoffset * m_pagesize * m_windowpagenum;
					return *(float*)((unsigned char*)m_lpMemReserved + elementoffset);
				}
				else if(m_datatype == 2)
					return m_angles_ha[(long long)offset];
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
	struct TaskSurveyInfo
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

		TaskSurveyInfo() : m_nLineNum(0), m_nCDPNum(0), m_nStartLine(0), m_nStartCDP(0), m_nLineIncrement(0), m_nCDPIncrement(0), m_fOrientation(0.), m_fDirection(0.), m_fOrgX(0.), m_fOrgY(0.), m_fLineSpace(0.), m_fCDPSpace(0.)
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
			m_fOrientation = other.m_fOrientation;			//In Line方位角，CDP小号到大号的方向，与x轴方向的夹角,0到PI
			m_fDirection = other.m_fDirection;					//Cross Line相对于In Line的顺时针方位角,-PI到PI
			m_fOrgX = other.m_fOrgX;								//大地起始坐标
			m_fOrgY = other.m_fOrgY;								//大地起始坐标
			m_fLineSpace = other.m_fLineSpace;				//In Line大地间隔	
			m_fCDPSpace = other.m_fCDPSpace;				//Cross Line大地间隔
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
			ar & m_nLineNum & m_nCDPNum & m_nStartLine & m_nStartCDP & m_nLineIncrement & m_nCDPIncrement & m_fOrientation & m_fDirection & m_fOrgX & m_fOrgY & m_fLineSpace & m_fCDPSpace;
		}
	};

	/*!
	* 
	**/
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
						
	/*!
	*
	**/
	struct TaskDataCubeSize
	{
		int m_inlCount;
		int m_crlCount;
		double m_windowZ;

		TaskDataCubeSize() : m_inlCount(0), m_crlCount(0), m_windowZ(0.)
		{
		}
		TaskDataCubeSize(const TaskDataCubeSize &other)
		{
			*this = other;
		}
		const TaskDataCubeSize &operator=(const TaskDataCubeSize &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_inlCount = other.m_inlCount;
			m_crlCount = other.m_crlCount;
			m_windowZ = other.m_windowZ;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_inlCount & m_crlCount & m_windowZ;
		}
	};	

	/*!
	*
	**/
	struct GdeCubeParameter
	{
		TaskOctreeCube m_cube;
		TaskOctreeTileDimension m_tileDimension;
		TaskSurveyInfo m_inputsurveyInfo;
		TaskSurveyInfo m_outputsurveyInfo;
		TaskDataCubeSize m_datacubesize;

		GdeCubeParameter()
		{
		}
		GdeCubeParameter(const GdeCubeParameter &other)
		{
			*this = other;
		}
		const GdeCubeParameter &operator=(const GdeCubeParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_cube = other.m_cube;
			m_tileDimension = other.m_tileDimension;
			m_inputsurveyInfo = other.m_inputsurveyInfo;
			m_outputsurveyInfo = other.m_outputsurveyInfo;
			m_datacubesize = other.m_datacubesize;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_cube & m_tileDimension & m_inputsurveyInfo & m_outputsurveyInfo & m_datacubesize;
		}
	};

	/*!
	*
	**/
	struct GdeFilterParameter
	{
		int m_number;
		double m_width;
		double m_start;
		double m_end;
		double m_lowFrom;
		double m_lowTo;
		double m_highFrom;
		double m_highTo;
		std::vector<double> m_frequencies;
		bool m_isSloped;
		short m_slopePts;
		bool m_isAutoed;
		double m_interval;

		GdeFilterParameter() : m_number(100), m_width(10), m_start(0), m_end(120), m_lowFrom(m_start), m_lowTo(m_end), m_highFrom(m_start), m_highTo(m_end), \
			m_isSloped(true), m_slopePts(5), m_isAutoed(true), m_interval(0.004)
		{
		}
		GdeFilterParameter(const GdeFilterParameter &other)
		{
			*this = other;
		}
		const GdeFilterParameter &operator=(const GdeFilterParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_number = other.m_number;
			m_width = other.m_width;
			m_start = other.m_start;
			m_end = other.m_end;
			m_lowFrom = other.m_lowFrom;
			m_lowTo = other.m_lowTo;
			m_highFrom = other.m_highFrom;
			m_highTo = other.m_highTo;
			m_frequencies = other.m_frequencies;
			m_isSloped = other.m_isSloped;
			m_slopePts = other.m_slopePts;
			m_isAutoed = other.m_isAutoed;
			m_interval = other.m_interval;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_number & m_width & m_start & m_end & m_lowFrom & m_lowTo & m_highFrom & m_highTo & m_frequencies & m_isSloped & m_slopePts & m_isAutoed & m_interval;
		}
	};
		
	/*!
	*
	**/
	struct GdeInstantAttributeParameter
	{
		int m_nOutSampNum;
		bool m_bOutputAmp;
		bool m_bOutputFreq;
		bool m_bOutputPhase;
		bool m_bOutputWeighted;
		bool m_bOutputBand;
		bool m_bOutputDomain;
		bool m_bOutputArc;
		bool m_bOutputThin;
		bool m_bOutputEHT;
		bool m_bOutputEntropy;
		bool m_bOutputVariance;
		bool m_bOutputSkew;
		bool m_bOutputKurtosis;
		std::vector<double> m_para1s;
		std::vector<double> m_para2s;
		std::vector<double> m_para3s;

		GdeInstantAttributeParameter() : m_nOutSampNum(0), m_bOutputAmp(false), m_bOutputFreq(false), m_bOutputPhase(false), m_bOutputWeighted(false), m_bOutputBand(false), m_bOutputDomain(false), m_bOutputArc(false), \
			m_bOutputThin(false), m_bOutputEHT(false), m_bOutputEntropy(false), m_bOutputVariance(false), m_bOutputSkew(false), m_bOutputKurtosis(false)
		{
		}
		GdeInstantAttributeParameter(const GdeInstantAttributeParameter &other)
		{
			*this = other;
		}
		const GdeInstantAttributeParameter &operator=(const GdeInstantAttributeParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_nOutSampNum = other.m_nOutSampNum;
			m_bOutputAmp = other.m_bOutputAmp;
			m_bOutputFreq = other.m_bOutputFreq;
			m_bOutputPhase = other.m_bOutputPhase;
			m_bOutputWeighted = other.m_bOutputWeighted;
			m_bOutputBand = other.m_bOutputBand;
			m_bOutputDomain = other.m_bOutputDomain;
			m_bOutputArc = other.m_bOutputArc;
			m_bOutputThin = other.m_bOutputThin;
			m_bOutputEHT = other.m_bOutputEHT;
			m_bOutputEntropy = other.m_bOutputEntropy;
			m_bOutputVariance = other.m_bOutputVariance;
			m_bOutputSkew = other.m_bOutputSkew;
			m_bOutputKurtosis = other.m_bOutputKurtosis;
			m_para1s = other.m_para1s;
			m_para2s = other.m_para2s;
			m_para3s = other.m_para3s;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_nOutSampNum & m_bOutputAmp & m_bOutputFreq & m_bOutputPhase & m_bOutputWeighted & m_bOutputBand & m_bOutputDomain & m_bOutputArc & m_bOutputThin & m_bOutputEHT & \
				m_bOutputEntropy & m_bOutputVariance & m_bOutputSkew & m_bOutputKurtosis & m_para1s & m_para2s & m_para3s;
		}
	};

	struct GdeDipAzimuthParameter
	{
		float m_dipazimuth_fSampleInter;//单位s
		int m_dipazimuth_nMaxBufferSize;
		int m_dipazimuth_nOutSampNum;
		std::vector<float> m_dipazimuth_pVelo;
		int m_dipazimuth_nCompSpaceLen;
		bool m_dipazimuth_isfirst;

		int m_dipazimuth_binnum;
		std::vector<int> m_dipazimuth_mainfreqs;
		int m_dipazimuth_nOutputCubeNum;
		int m_dipazimuth_nOutputTimeInc;//单位ms
		std::vector<int> m_dipazimuth_pWinLen;
		int m_dipazimuth_nWinLen;
		float m_dipazimuth_fCdpInterval;
		float m_dipazimuth_fLineInterval;
		int m_dipazimuth_nAngleX;
		int m_dipazimuth_nAngleY;
		float m_dipazimuth_fMinAngleX;
		float m_dipazimuth_fMaxAngleX;
		float m_dipazimuth_fMinAngleY;
		float m_dipazimuth_fMaxAngleY;
		int m_dipazimuth_enumMethod;
		int m_dipazimuth_enumFitMode;
		int m_dipazimuth_enumWinType;
		int m_dipazimuth_enumCohMode;
		int m_dipazimuth_iPrinFilter;
		int m_dipazimuth_bHilbTrans;
		int m_dipazimuth_enumSmoothMethod;
		bool m_dipazimuth_isoutputdipazimtuh;
		bool m_dipazimuth_isoutputlinecdpdip;

		GdeDipAzimuthParameter()
		{
			m_dipazimuth_binnum = 0;
			m_dipazimuth_nOutputCubeNum = 0;
			m_dipazimuth_isfirst = true;
		}
		GdeDipAzimuthParameter(const GdeDipAzimuthParameter &other)
		{
			*this = other;
		}
		const GdeDipAzimuthParameter &operator=(const GdeDipAzimuthParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_dipazimuth_fSampleInter = other.m_dipazimuth_fSampleInter;
			m_dipazimuth_nMaxBufferSize = other.m_dipazimuth_nMaxBufferSize;
			m_dipazimuth_nOutSampNum = other.m_dipazimuth_nOutSampNum;
			m_dipazimuth_pVelo = other.m_dipazimuth_pVelo;
			m_dipazimuth_nCompSpaceLen = other.m_dipazimuth_nCompSpaceLen;
			m_dipazimuth_isfirst = other.m_dipazimuth_isfirst;

			m_dipazimuth_binnum = other.m_dipazimuth_binnum;
			m_dipazimuth_mainfreqs = other.m_dipazimuth_mainfreqs;
			m_dipazimuth_nOutputCubeNum = other.m_dipazimuth_nOutputCubeNum;
			m_dipazimuth_nOutputTimeInc = other.m_dipazimuth_nOutputTimeInc;
			m_dipazimuth_pWinLen = other.m_dipazimuth_pWinLen;
			m_dipazimuth_nWinLen = other.m_dipazimuth_nWinLen;
			m_dipazimuth_fCdpInterval = other.m_dipazimuth_fCdpInterval;
			m_dipazimuth_fLineInterval = other.m_dipazimuth_fLineInterval;
			m_dipazimuth_nAngleX = other.m_dipazimuth_nAngleX;
			m_dipazimuth_nAngleY = other.m_dipazimuth_nAngleY;
			m_dipazimuth_fMinAngleX = other.m_dipazimuth_fMinAngleX;
			m_dipazimuth_fMaxAngleX = other.m_dipazimuth_fMaxAngleX;
			m_dipazimuth_fMinAngleY = other.m_dipazimuth_fMinAngleY;
			m_dipazimuth_fMaxAngleY = other.m_dipazimuth_fMaxAngleY;
			m_dipazimuth_enumMethod = other.m_dipazimuth_enumMethod;
			m_dipazimuth_enumFitMode = other.m_dipazimuth_enumFitMode;
			m_dipazimuth_enumWinType = other.m_dipazimuth_enumWinType;
			m_dipazimuth_enumCohMode = other.m_dipazimuth_enumCohMode;
			m_dipazimuth_iPrinFilter = other.m_dipazimuth_iPrinFilter;
			m_dipazimuth_bHilbTrans = other.m_dipazimuth_bHilbTrans;
			m_dipazimuth_enumSmoothMethod = other.m_dipazimuth_enumSmoothMethod;
			m_dipazimuth_isoutputdipazimtuh = other.m_dipazimuth_isoutputdipazimtuh;
			m_dipazimuth_isoutputlinecdpdip = other.m_dipazimuth_isoutputlinecdpdip;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_dipazimuth_fSampleInter & m_dipazimuth_nMaxBufferSize & m_dipazimuth_nOutSampNum & m_dipazimuth_pVelo & m_dipazimuth_nCompSpaceLen & m_dipazimuth_isfirst & \
				m_dipazimuth_binnum & m_dipazimuth_mainfreqs & m_dipazimuth_nOutputCubeNum & m_dipazimuth_nOutputTimeInc & m_dipazimuth_pWinLen & m_dipazimuth_nWinLen & \
				m_dipazimuth_fCdpInterval & m_dipazimuth_fLineInterval & m_dipazimuth_nAngleX & m_dipazimuth_nAngleY & m_dipazimuth_fMinAngleX & m_dipazimuth_fMaxAngleX & \
				m_dipazimuth_fMinAngleY & m_dipazimuth_fMaxAngleY & m_dipazimuth_enumMethod & m_dipazimuth_enumFitMode & m_dipazimuth_enumWinType & m_dipazimuth_enumCohMode & \
				m_dipazimuth_iPrinFilter & m_dipazimuth_bHilbTrans & m_dipazimuth_enumSmoothMethod & m_dipazimuth_isoutputdipazimtuh & m_dipazimuth_isoutputlinecdpdip;
		}
	};

	struct GdeAlphaFilterParameter
	{
		float m_alphafilter_fSampleInter;//单位s
		int m_alphafilter_nMaxBufferSize;
		int m_alphafilter_nOutSampNum;
		int m_alphafilter_nCompSpaceLen;
		int m_alphafilter_nOutputTimeInc;//单位ms

		bool m_alphafilter_isdomainfreq;
		double m_alphafilter_domainfreq;
		double m_alphafilter_alpha;
		double m_alphafilter_level;
		int m_alphafilter_linebinnum;
		int m_alphafilter_cdpbinnum;

		GdeAlphaFilterParameter()
		{
		}
		GdeAlphaFilterParameter(const GdeAlphaFilterParameter &other)
		{
			*this = other;
		}
		const GdeAlphaFilterParameter &operator=(const GdeAlphaFilterParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_alphafilter_fSampleInter = other.m_alphafilter_fSampleInter;
			m_alphafilter_nMaxBufferSize = other.m_alphafilter_nMaxBufferSize;
			m_alphafilter_nOutSampNum = other.m_alphafilter_nOutSampNum;
			m_alphafilter_nCompSpaceLen = other.m_alphafilter_nCompSpaceLen;
			m_alphafilter_nOutputTimeInc = other.m_alphafilter_nOutputTimeInc;
			m_alphafilter_isdomainfreq = other.m_alphafilter_isdomainfreq;
			m_alphafilter_domainfreq = other.m_alphafilter_domainfreq;
			m_alphafilter_alpha = other.m_alphafilter_alpha;
			m_alphafilter_level = other.m_alphafilter_level;
			m_alphafilter_linebinnum = other.m_alphafilter_linebinnum;
			m_alphafilter_cdpbinnum = other.m_alphafilter_cdpbinnum;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_alphafilter_fSampleInter & m_alphafilter_nMaxBufferSize & m_alphafilter_nOutSampNum & m_alphafilter_nCompSpaceLen & m_alphafilter_nOutputTimeInc & \
				m_alphafilter_isdomainfreq & m_alphafilter_domainfreq & m_alphafilter_alpha & m_alphafilter_level & m_alphafilter_linebinnum & m_alphafilter_cdpbinnum;
		}
	};
	struct GdeIrregularParameter
	{
		double m_irregular_azimuthlow;
		double m_irregular_azimuthhigh;
		int m_irregular_azimuthgroup;
		double m_irregular_anglelow;
		double m_irregular_anglehigh;
		int m_irregular_Niter;
		double m_irregular_lamda;
		int m_irregular_depth_shift;
		int m_irregular_linebinnum;
		int m_irregular_cdpbinnum;
		double m_irregular_scalefactor;

		GdeIrregularParameter()
		{
		}
		GdeIrregularParameter(const GdeIrregularParameter &other)
		{
			*this = other;
		}
		const GdeIrregularParameter &operator=(const GdeIrregularParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_irregular_azimuthlow = other.m_irregular_azimuthlow;
			m_irregular_azimuthhigh = other.m_irregular_azimuthhigh;
			m_irregular_azimuthgroup = other.m_irregular_azimuthgroup;
			m_irregular_anglelow = other.m_irregular_anglelow;
			m_irregular_anglehigh = other.m_irregular_anglehigh;
			m_irregular_Niter = other.m_irregular_Niter;
			m_irregular_lamda = other.m_irregular_lamda;
			m_irregular_depth_shift = other.m_irregular_depth_shift;
			m_irregular_linebinnum = other.m_irregular_linebinnum;
			m_irregular_cdpbinnum = other.m_irregular_cdpbinnum;
			m_irregular_scalefactor = other.m_irregular_scalefactor;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_irregular_azimuthlow & m_irregular_azimuthhigh & m_irregular_azimuthgroup & m_irregular_anglelow & m_irregular_anglehigh & \
				m_irregular_Niter & m_irregular_lamda & m_irregular_depth_shift & m_irregular_linebinnum & m_irregular_cdpbinnum & m_irregular_scalefactor;
		}
	};
	/*!
	*
	**/
	struct GdeAngleFractureParameter
	{
		std::vector<double> m_angles;
		std::vector<int> m_linenos;
		std::vector<int> m_cdpnos;
		std::string m_vrmsname;
		std::string m_vintname;
		bool m_isvrmsgde;
		bool m_isvintgde;
		int m_converttype;
		double m_azimuthlow;
		double m_azimuthhigh;
		int m_azimuthgroup;
		double m_timeinterval;

		GdeAngleFractureParameter() : m_vrmsname(""), m_vintname(""), m_isvrmsgde(false), m_isvintgde(false), m_converttype(0), m_azimuthlow(0), m_azimuthhigh(360), m_azimuthgroup(12), m_timeinterval(10)
		{
		}
		GdeAngleFractureParameter(const GdeAngleFractureParameter &other)
		{
			*this = other;
		}
		const GdeAngleFractureParameter &operator=(const GdeAngleFractureParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_angles = other.m_angles;
			m_linenos = other.m_linenos;
			m_cdpnos = other.m_cdpnos;
			m_vrmsname = other.m_vrmsname;
			m_vintname = other.m_vintname;
			m_isvrmsgde = other.m_isvrmsgde;
			m_isvintgde = other.m_isvintgde;
			m_converttype = other.m_converttype;
			m_azimuthlow = other.m_azimuthlow;
			m_azimuthhigh = other.m_azimuthhigh;
			m_azimuthgroup = other.m_azimuthgroup;
			m_timeinterval = other.m_timeinterval;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_angles & m_linenos & m_cdpnos & m_vrmsname & m_vintname & m_isvrmsgde & m_isvintgde & m_converttype & m_azimuthlow & m_azimuthhigh & m_azimuthgroup & m_timeinterval;
		}
	};				
	struct GdeThreeBayesParameter
	{
		std::vector<string> m_threebayes_inputnames;
		int m_threebayes_nInlineFrom, m_threebayes_nInlineTo, m_threebayes_nXlineFrom, m_threebayes_nXlineTo;
		
		//
		double m_threebayes_start_time_near;				//近道集起始时间
		double m_threebayes_start_time_mid;					//中道集起始时间
		double m_threebayes_start_time_far;					//远道集起始时间

		//
		int m_threebayes_samp_num_near;						//近道集采样点数
		int m_threebayes_samp_num_mid;						//中道集采样点数
		int m_threebayes_samp_num_far;						//远道集采样点数

		//
		double m_threebayes_samp_int_near;					//近道集采样间隔
		double m_threebayes_samp_int_mid;					//中道集采样间隔
		double m_threebayes_samp_int_far;					//远道集采样间隔

		//
		double m_threebayes_start_time_Imp;					//P波阻抗低频模型起始时间
		double m_threebayes_start_time_Jmp;				//S波阻抗低频模型起始时间
		double m_threebayes_start_time_dens;				//密度低频模型起始时间

		//
		int m_threebayes_samp_num_Imp;						//P波阻抗低频模型采样点数
		int m_threebayes_samp_num_Jmp;						//S波阻抗低频模型采样点数
		int m_threebayes_samp_num_dens;					//密度低频模型采样点数

		//
		double m_threebayes_samp_int_Imp;					//P波阻抗低频模型采样间隔
		double m_threebayes_samp_int_Jmp;					//S波阻抗低频模型采样间隔
		double m_threebayes_samp_int_dens;					//密度低频模型采样间隔

		//
		std::vector<double> m_threebayes_wavelet_near;		//输入的近角度子波（子波持久化文件中获取）
		std::vector<double> m_threebayes_wavelet_mid;		//输入的中角度子波（子波持久化文件中获取）
		std::vector<double> m_threebayes_wavelet_far;			//输入的远角度子波（子波持久化文件中获取）

		//
		double m_threebayes_start_time_wav_near;				//近角度子波起始时间（子波持久化文件中获取）
		double m_threebayes_start_time_wav_mid;				//中角度子波起始时间（子波持久化文件中获取）
		double m_threebayes_start_time_wav_far;					//远角度子波起始时间（子波持久化文件中获取）

		//
		int m_threebayes_samp_wav_near;								//近角度子波采样点数（子波持久化文件中获取）
		int m_threebayes_samp_wav_mid;								//中角度子波采样点数（子波持久化文件中获取）
		int m_threebayes_samp_wav_far;									//远角度子波采样点数（子波持久化文件中获取）

		//
		double m_threebayes_samp_int_wav_near;				//近角度子波采样间隔（子波持久化文件中获取）
		double m_threebayes_samp_int_wav_mid;					//中角度子波采样间隔（子波持久化文件中获取）
		double m_threebayes_samp_int_wav_far;					//远角度子波采样间隔（子波持久化文件中获取）

		//
		std::vector<double> m_threebayes_angle;											//入射角向量，用户界面填写，1×3的向量（例如[10,20,30]）
		double m_threebayes_sigma1;										//高斯边界保护约束项权系数，参数放开给用户（default==0）
		double m_threebayes_sigma2;										//反射系数稀疏约束项权系数，参数放开给用户（default==1）
		double m_threebayes_sigma3;										//低频软约束项权系数，参数放开给用户（default==1）

		//
		double m_threebayes_NEM;											//弹性参数尺度矩阵估计迭代次数,参数放开给用户（default==10）
		double m_threebayes_NNN;											//反演迭代次数,参数放开给用户（default==2）
		double m_threebayes_lowpass;									//低通滤波窗函数通过频率,参数放开给用户（default==5）
		double m_threebayes_lowcut;										//低通滤波窗函数截至频率,参数放开给用户（default==15）

		double m_threebayes_Top_time;									//反演时窗顶部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）
		double m_threebayes_Bot_time;									//反演时窗底部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）

		std::vector<double> m_threebayes_Top_times;									//反演时窗顶部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）
		std::vector<double> m_threebayes_Bot_times;									//反演时窗底部时间（ms）（沿层或者等时模式，沿层时用层位和当前道相交的时间，TimeGate中获取）

		double m_threebayes_start_time_mod;						//反演结果数据体起始时间（ms，存入反演结果数据体道头字，三维工区始终不变）
		double m_threebayes_samp_num_mod;						//反演结果数据体采样点数（存入反演结果数据体道头字，三维工区始终不变）
		double m_threebayes_samp_int_mod;							//反演结果数据体采样间隔（ms，存入反演结果数据体道头字，三维工区始终不变）

		GdeThreeBayesParameter()
		{
		}
		GdeThreeBayesParameter(const GdeThreeBayesParameter &other)
		{
			*this = other;
		}
		const GdeThreeBayesParameter &operator=(const GdeThreeBayesParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_threebayes_inputnames = other.m_threebayes_inputnames;
			m_threebayes_nInlineFrom = other.m_threebayes_nInlineFrom;
			m_threebayes_nInlineTo = other.m_threebayes_nInlineTo;
			m_threebayes_nXlineFrom = other.m_threebayes_nXlineFrom;
			m_threebayes_nXlineTo = other.m_threebayes_nXlineTo;

			//
			m_threebayes_start_time_near = other.m_threebayes_start_time_near;
			m_threebayes_start_time_mid = other.m_threebayes_start_time_mid;
			m_threebayes_start_time_far = other.m_threebayes_start_time_far;

			//
			m_threebayes_samp_num_near = other.m_threebayes_samp_num_near;
			m_threebayes_samp_num_mid = other.m_threebayes_samp_num_mid;
			m_threebayes_samp_num_far = other.m_threebayes_samp_num_far;

			//
			m_threebayes_samp_int_near = other.m_threebayes_samp_int_near;
			m_threebayes_samp_int_mid = other.m_threebayes_samp_int_mid;
			m_threebayes_samp_int_far = other.m_threebayes_samp_int_far;

			//
			m_threebayes_start_time_Imp = other.m_threebayes_start_time_Imp;
			m_threebayes_start_time_Jmp = other.m_threebayes_start_time_Jmp;
			m_threebayes_start_time_dens = other.m_threebayes_start_time_dens;

			//
			m_threebayes_samp_num_Imp = other.m_threebayes_samp_num_Imp;
			m_threebayes_samp_num_Jmp = other.m_threebayes_samp_num_Jmp;
			m_threebayes_samp_num_dens = other.m_threebayes_samp_num_dens;

			//
			m_threebayes_samp_int_Imp = other.m_threebayes_samp_int_Imp;
			m_threebayes_samp_int_Jmp = other.m_threebayes_samp_int_Jmp;
			m_threebayes_samp_int_dens = other.m_threebayes_samp_int_dens;

			//
			m_threebayes_wavelet_near = other.m_threebayes_wavelet_near;
			m_threebayes_wavelet_mid = other.m_threebayes_wavelet_mid;
			m_threebayes_wavelet_far = other.m_threebayes_wavelet_far;

			//
			m_threebayes_start_time_wav_near = other.m_threebayes_start_time_wav_near;
			m_threebayes_start_time_wav_mid = other.m_threebayes_start_time_wav_mid;
			m_threebayes_start_time_wav_far = other.m_threebayes_start_time_wav_far;

			//
			m_threebayes_samp_wav_near = other.m_threebayes_samp_wav_near;
			m_threebayes_samp_wav_mid = other.m_threebayes_samp_wav_mid;
			m_threebayes_samp_wav_far = other.m_threebayes_samp_wav_far;

			//
			m_threebayes_samp_int_wav_near = other.m_threebayes_samp_int_wav_near;
			m_threebayes_samp_int_wav_mid = other.m_threebayes_samp_int_wav_mid;
			m_threebayes_samp_int_wav_far = other.m_threebayes_samp_int_wav_far;

			//
			m_threebayes_angle = other.m_threebayes_angle;
			m_threebayes_sigma1 = other.m_threebayes_sigma1;
			m_threebayes_sigma2 = other.m_threebayes_sigma2;
			m_threebayes_sigma3 = other.m_threebayes_sigma3;

			//
			m_threebayes_NEM = other.m_threebayes_NEM;
			m_threebayes_NNN = other.m_threebayes_NNN;
			m_threebayes_lowpass = other.m_threebayes_lowpass;
			m_threebayes_lowcut = other.m_threebayes_lowcut;

			m_threebayes_Top_time = other.m_threebayes_Top_time;
			m_threebayes_Bot_time = other.m_threebayes_Bot_time;

			m_threebayes_Top_times = other.m_threebayes_Top_times;
			m_threebayes_Bot_times = other.m_threebayes_Bot_times;

			m_threebayes_start_time_mod = other.m_threebayes_start_time_mod;
			m_threebayes_samp_num_mod = other.m_threebayes_samp_num_mod;
			m_threebayes_samp_int_mod = other.m_threebayes_samp_int_mod;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_threebayes_inputnames & m_threebayes_nInlineFrom & m_threebayes_nInlineTo & m_threebayes_nXlineFrom & m_threebayes_nXlineTo\
				& m_threebayes_start_time_near & m_threebayes_start_time_mid & m_threebayes_start_time_far & m_threebayes_samp_num_near & m_threebayes_samp_num_mid & m_threebayes_samp_num_far\
				& m_threebayes_samp_int_near & m_threebayes_samp_int_mid & m_threebayes_samp_int_far & m_threebayes_start_time_Imp\
				& m_threebayes_start_time_Jmp & m_threebayes_start_time_dens & m_threebayes_samp_num_Imp & m_threebayes_samp_num_Jmp & m_threebayes_samp_num_dens & m_threebayes_samp_int_Imp & m_threebayes_samp_int_Jmp\
				& m_threebayes_samp_int_dens & m_threebayes_wavelet_near & m_threebayes_wavelet_mid & m_threebayes_wavelet_far & m_threebayes_start_time_wav_near & m_threebayes_start_time_wav_mid & m_threebayes_start_time_wav_far\
				& m_threebayes_samp_wav_near & m_threebayes_samp_wav_mid & m_threebayes_samp_wav_far & m_threebayes_samp_int_wav_near & m_threebayes_samp_int_wav_mid & m_threebayes_samp_int_wav_far\
				& m_threebayes_angle & m_threebayes_sigma1 & m_threebayes_sigma2 & m_threebayes_sigma3 & m_threebayes_NEM & m_threebayes_NNN & m_threebayes_lowpass & m_threebayes_lowcut & m_threebayes_Top_time\
				& m_threebayes_Bot_time & m_threebayes_Top_times & m_threebayes_Bot_times & m_threebayes_start_time_mod\
				& m_threebayes_samp_num_mod & m_threebayes_samp_int_mod;
		}
	};
	struct GdeBasicTrackSubParameter
	{
		int MaxIter;
		double FeaTol;
		double OptTol;
		double StepTol;
		double x0min;
		double z0min;
		double mu0;
		double gamma;
		double delta;

		int Maxitns;
		int Minitns;
		double tol;
		double cont_steps;
		double mu;
		double beta;
			
		/*!
		*
		**/
		GdeBasicTrackSubParameter() : MaxIter(100), FeaTol(0.000000001), OptTol(0.000000001), StepTol(0.99), x0min(0.1), z0min(1), mu0(1000), gamma(0.0001), delta(1), \
			Maxitns(50000), Minitns(500), tol(0.01), cont_steps(1), mu(0.1), beta(0.5)
		{
		}

		/*!
		*
		**/
		GdeBasicTrackSubParameter(const GdeBasicTrackSubParameter &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const GdeBasicTrackSubParameter &operator=(const GdeBasicTrackSubParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			MaxIter = other.MaxIter;
			FeaTol = other.FeaTol;
			OptTol = other.OptTol;
			StepTol = other.StepTol;
			x0min = other.x0min;
			z0min = other.z0min;
			mu0 = other.mu0;
			gamma = other.gamma;
			delta = other.delta;
			Maxitns = other.Maxitns;
			Minitns = other.Minitns;
			tol = other.tol;
			cont_steps = other.cont_steps;
			mu = other.mu;
			beta = other.beta;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & MaxIter & FeaTol & OptTol & StepTol & x0min\
				& z0min & mu0 & gamma & delta & Maxitns & Minitns\
				& tol & cont_steps & mu & beta;
		}
	};
	struct GdeBasicTrackParameter
	{
		std::vector<string> m_basictrack_inputnames;
		int m_basictrack_nInlineFrom;
		int m_basictrack_nInlineTo;
		int m_basictrack_nXlineFrom;
		int m_basictrack_nXlineTo;
		double m_basictrack_start_time_near;				//地震数据起始时间
		int m_basictrack_samp_num_near;					//地震数据采样点数
		double m_basictrack_samp_int_near;					//地震数据采样间隔
		double m_basictrack_start_time_Imp;				//波阻抗低频模型起始时间
		int m_basictrack_samp_num_Imp;						//波阻抗低频模型采样点数
		double m_basictrack_samp_int_Imp;					//波阻抗低频模型采样间隔
		std::vector<double> m_basictrack_wavelet_near;		//输入的子波（子波持久化文件中获取）
		double m_basictrack_start_time_wav_near;			//子波起始时间（子波持久化文件中获取）
		int m_basictrack_samp_wav_near;					//子波采样点数（子波持久化文件中获取）
		double m_basictrack_samp_int_wav_near;				//子波采样间隔（子波持久化文件中获取）
		int m_basictrack_method;							//基追踪分解方法
		double m_basictrack_sigma2;						//稀疏约束
		double m_basictrack_sigma3;						//低频软约束
		GdeBasicTrackSubParameter m_basictrack_option;		//ODLP和GPSR高级配置参数
		int m_basictrack_D_sample;							//薄层最大厚度
		double m_basictrack_lowpass;						//低通频
		double m_basictrack_lowcut;						//低截频
		int m_basictrack_N_pad;							//边界外延
		
		GdeBasicTrackParameter()
		{
		}
		GdeBasicTrackParameter(const GdeBasicTrackParameter &other)
		{
			*this = other;
		}
		const GdeBasicTrackParameter &operator=(const GdeBasicTrackParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_basictrack_inputnames = other.m_basictrack_inputnames;
			m_basictrack_nInlineFrom = other.m_basictrack_nInlineFrom;
			m_basictrack_nInlineTo = other.m_basictrack_nInlineTo;
			m_basictrack_nXlineFrom = other.m_basictrack_nXlineFrom;
			m_basictrack_nXlineTo = other.m_basictrack_nXlineTo;
			m_basictrack_start_time_near = other.m_basictrack_start_time_near;
			m_basictrack_samp_num_near = other.m_basictrack_samp_num_near;
			m_basictrack_samp_int_near = other.m_basictrack_samp_int_near;
			m_basictrack_start_time_Imp = other.m_basictrack_start_time_Imp;
			m_basictrack_samp_num_Imp = other.m_basictrack_samp_num_Imp;
			m_basictrack_samp_int_Imp = other.m_basictrack_samp_int_Imp;
			m_basictrack_wavelet_near = other.m_basictrack_wavelet_near;
			m_basictrack_start_time_wav_near = other.m_basictrack_start_time_wav_near;
			m_basictrack_samp_wav_near = other.m_basictrack_samp_wav_near;
			m_basictrack_samp_int_wav_near = other.m_basictrack_samp_int_wav_near;
			m_basictrack_method = other.m_basictrack_method;
			m_basictrack_sigma2 = other.m_basictrack_sigma2;
			m_basictrack_sigma3 = other.m_basictrack_sigma3;
			m_basictrack_option = other.m_basictrack_option;
			m_basictrack_D_sample = other.m_basictrack_D_sample;
			m_basictrack_lowpass = other.m_basictrack_lowpass;
			m_basictrack_lowcut = other.m_basictrack_lowcut;
			m_basictrack_N_pad = other.m_basictrack_N_pad;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_basictrack_inputnames & m_basictrack_nInlineFrom & m_basictrack_nInlineTo & m_basictrack_nXlineFrom & m_basictrack_nXlineTo & m_basictrack_start_time_near & m_basictrack_samp_num_near & m_basictrack_samp_int_near\
				& m_basictrack_start_time_Imp & m_basictrack_samp_num_Imp & m_basictrack_samp_int_Imp & m_basictrack_wavelet_near & m_basictrack_start_time_wav_near & m_basictrack_samp_wav_near & m_basictrack_samp_int_wav_near\
				& m_basictrack_method & m_basictrack_sigma2 & m_basictrack_sigma3 & m_basictrack_option & m_basictrack_D_sample & m_basictrack_lowpass & m_basictrack_lowcut & m_basictrack_N_pad;
		}
	};
	struct GdeRockPhysicsParameter
	{
		std::vector<string> m_rockphysics_inputnames;
		double m_rockphysics_start_time_1;
		double m_rockphysics_start_time_2;
		double m_rockphysics_start_time_3;
		double m_rockphysics_start_time_4;
		double m_rockphysics_start_time_5;
		double m_rockphysics_start_time_6;
		double m_rockphysics_start_time_out;
		int m_rockphysics_samp_num_1;
		int m_rockphysics_samp_num_2;
		int m_rockphysics_samp_num_3;
		int m_rockphysics_samp_num_4;
		int m_rockphysics_samp_num_5;
		int m_rockphysics_samp_num_6;
		int m_rockphysics_samp_num_out;
		double m_rockphysics_samp_int_1;
		double m_rockphysics_samp_int_2;
		double m_rockphysics_samp_int_3;
		double m_rockphysics_samp_int_4;
		double m_rockphysics_samp_int_5;
		double m_rockphysics_samp_int_6;
		double m_rockphysics_samp_int_out;

		std::vector<std::vector<double> > m_rockphysics_fai;
		std::vector<std::vector<double> > m_rockphysics_G_Mat;
		std::vector<double> m_rockphysics_Coef_Clay;

		int m_rockphysics_v_choice;//总体积分数
		double m_rockphysics_lamda;//测井约束项权重
		double m_rockphysics_lowpass;//低通频
		double m_rockphysics_lowcut;//低截频

		int m_rockphysics_nInlineFrom, m_rockphysics_nInlineTo, m_rockphysics_nXlineFrom, m_rockphysics_nXlineTo;

		GdeRockPhysicsParameter()
		{
		}
		GdeRockPhysicsParameter(const GdeRockPhysicsParameter &other)
		{
			*this = other;
		}
		const GdeRockPhysicsParameter &operator=(const GdeRockPhysicsParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_rockphysics_inputnames = other.m_rockphysics_inputnames;
			m_rockphysics_start_time_1 = other.m_rockphysics_start_time_1;
			m_rockphysics_start_time_2 = other.m_rockphysics_start_time_2;
			m_rockphysics_start_time_3 = other.m_rockphysics_start_time_3;
			m_rockphysics_start_time_4 = other.m_rockphysics_start_time_4;
			m_rockphysics_start_time_5 = other.m_rockphysics_start_time_5;
			m_rockphysics_start_time_6 = other.m_rockphysics_start_time_6;
			m_rockphysics_start_time_out = other.m_rockphysics_start_time_out;
			m_rockphysics_samp_num_1 = other.m_rockphysics_samp_num_1;
			m_rockphysics_samp_num_2 = other.m_rockphysics_samp_num_2;
			m_rockphysics_samp_num_3 = other.m_rockphysics_samp_num_3;
			m_rockphysics_samp_num_4 = other.m_rockphysics_samp_num_4;
			m_rockphysics_samp_num_5 = other.m_rockphysics_samp_num_5;
			m_rockphysics_samp_num_6 = other.m_rockphysics_samp_num_6;
			m_rockphysics_samp_num_out = other.m_rockphysics_samp_num_out;
			m_rockphysics_samp_int_1 = other.m_rockphysics_samp_int_1;
			m_rockphysics_samp_int_2 = other.m_rockphysics_samp_int_2;
			m_rockphysics_samp_int_3 = other.m_rockphysics_samp_int_3;
			m_rockphysics_samp_int_4 = other.m_rockphysics_samp_int_4;
			m_rockphysics_samp_int_5 = other.m_rockphysics_samp_int_5;
			m_rockphysics_samp_int_6 = other.m_rockphysics_samp_int_6;
			m_rockphysics_samp_int_out = other.m_rockphysics_samp_int_out;

			m_rockphysics_fai = other.m_rockphysics_fai;
			m_rockphysics_G_Mat = other.m_rockphysics_G_Mat;
			m_rockphysics_Coef_Clay = other.m_rockphysics_Coef_Clay;

			m_rockphysics_v_choice = other.m_rockphysics_v_choice;
			m_rockphysics_lamda = other.m_rockphysics_lamda;
			m_rockphysics_lowpass = other.m_rockphysics_lowpass;
			m_rockphysics_lowcut = other.m_rockphysics_lowcut;

			m_rockphysics_nInlineFrom = other.m_rockphysics_nInlineFrom;
			m_rockphysics_nInlineTo = other.m_rockphysics_nInlineTo;
			m_rockphysics_nXlineFrom = other.m_rockphysics_nXlineFrom;
			m_rockphysics_nXlineTo = other.m_rockphysics_nXlineTo;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_rockphysics_inputnames & m_rockphysics_start_time_1 & m_rockphysics_start_time_2 & m_rockphysics_start_time_3 & m_rockphysics_start_time_4 & m_rockphysics_start_time_5 & m_rockphysics_start_time_6 & m_rockphysics_start_time_out\
				& m_rockphysics_samp_num_1 & m_rockphysics_samp_num_2 & m_rockphysics_samp_num_3 & m_rockphysics_samp_num_4 & m_rockphysics_samp_num_5 & m_rockphysics_samp_num_6 & m_rockphysics_samp_num_out\
				& m_rockphysics_samp_int_1 & m_rockphysics_samp_int_2 & m_rockphysics_samp_int_3 & m_rockphysics_samp_int_4 & m_rockphysics_samp_int_5 & m_rockphysics_samp_int_6 & m_rockphysics_samp_int_out\
				& m_rockphysics_fai & m_rockphysics_G_Mat & m_rockphysics_Coef_Clay & m_rockphysics_v_choice & m_rockphysics_lamda & m_rockphysics_lowpass & m_rockphysics_lowcut & m_rockphysics_nInlineFrom\
				& m_rockphysics_nInlineTo & m_rockphysics_nXlineFrom & m_rockphysics_nXlineTo;
		}
	};
	struct GdeBrickParameter
	{
		std::vector<string> m_brick_inputnames;
		double m_brick_start_time_1;
		double m_brick_start_time_2;
		double m_brick_start_time_3;
		double m_brick_start_time_4;
		double m_brick_start_time_5;
		double m_brick_start_time_6;
		double m_brick_start_time_out;
		int m_brick_samp_num_1;
		int m_brick_samp_num_2;
		int m_brick_samp_num_3;
		int m_brick_samp_num_4;
		int m_brick_samp_num_5;
		int m_brick_samp_num_6;
		int m_brick_samp_num_out;
		double m_brick_samp_int_1;
		double m_brick_samp_int_2;
		double m_brick_samp_int_3;
		double m_brick_samp_int_4;
		double m_brick_samp_int_5;
		double m_brick_samp_int_6;
		double m_brick_samp_int_out;

		double m_brick_ag_near;//小角度角度，float型变量
		double m_brick_ag_mid;//中角度角度，float型变量
		double m_brick_ag_far;//大角度角度，float型变量
		double m_brick_sigma2;//先验约束权重，参数放开给用户（default==0.01）
		double m_brick_sigma3;//低频软约束项权重，参数放开给用户（default==1）
		double m_brick_YM_min;//最小杨氏模量，double型变量，从界面获取
		double m_brick_YM_max;//最大杨氏模量，double型变量，从界面获取
		double m_brick_PR_min;//最小泊松比，double型变量，从界面获取
		double m_brick_PR_max;//最大泊松比，double型变量，从界面获取
		int m_brick_N_Iter;//反演迭代次数,参数放开给用户（default==2）
		double m_brick_lowpass;//低通频
		double m_brick_lowcut;//低截频

		int m_brick_nInlineFrom, m_brick_nInlineTo, m_brick_nXlineFrom, m_brick_nXlineTo;

		GdeBrickParameter()
		{
		}
		GdeBrickParameter(const GdeBrickParameter &other)
		{
			*this = other;
		}
		const GdeBrickParameter &operator=(const GdeBrickParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_brick_inputnames = other.m_brick_inputnames;
			m_brick_start_time_1 = other.m_brick_start_time_1;
			m_brick_start_time_2 = other.m_brick_start_time_2;
			m_brick_start_time_3 = other.m_brick_start_time_3;
			m_brick_start_time_4 = other.m_brick_start_time_4;
			m_brick_start_time_5 = other.m_brick_start_time_5;
			m_brick_start_time_6 = other.m_brick_start_time_6;
			m_brick_start_time_out = other.m_brick_start_time_out;
			m_brick_samp_num_1 = other.m_brick_samp_num_1;
			m_brick_samp_num_2 = other.m_brick_samp_num_2;
			m_brick_samp_num_3 = other.m_brick_samp_num_3;
			m_brick_samp_num_4 = other.m_brick_samp_num_4;
			m_brick_samp_num_5 = other.m_brick_samp_num_5;
			m_brick_samp_num_6 = other.m_brick_samp_num_6;
			m_brick_samp_num_out = other.m_brick_samp_num_out;
			m_brick_samp_int_1 = other.m_brick_samp_int_1;
			m_brick_samp_int_2 = other.m_brick_samp_int_2;
			m_brick_samp_int_3 = other.m_brick_samp_int_3;
			m_brick_samp_int_4 = other.m_brick_samp_int_4;
			m_brick_samp_int_5 = other.m_brick_samp_int_5;
			m_brick_samp_int_6 = other.m_brick_samp_int_6;
			m_brick_samp_int_out = other.m_brick_samp_int_out;

			m_brick_ag_near = other.m_brick_ag_near; 
			m_brick_ag_mid = other.m_brick_ag_mid;
			m_brick_ag_far = other.m_brick_ag_far;
			m_brick_sigma2 = other.m_brick_sigma2;
			m_brick_sigma3 = other.m_brick_sigma3;
			m_brick_YM_min = other.m_brick_YM_min;
			m_brick_YM_max = other.m_brick_YM_max;
			m_brick_PR_min = other.m_brick_PR_min;
			m_brick_PR_max = other.m_brick_PR_max;
			m_brick_N_Iter = other.m_brick_N_Iter;

			m_brick_lowpass = other.m_brick_lowpass;
			m_brick_lowcut = other.m_brick_lowcut;
			  
			m_brick_nInlineFrom = other.m_brick_nInlineFrom;
			m_brick_nInlineTo = other.m_brick_nInlineTo;
			m_brick_nXlineFrom = other.m_brick_nXlineFrom;
			m_brick_nXlineTo = other.m_brick_nXlineTo;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_brick_inputnames & m_brick_start_time_1 & m_brick_start_time_2 & m_brick_start_time_3 & m_brick_start_time_4 & m_brick_start_time_5 & m_brick_start_time_6 & m_brick_start_time_out\
				& m_brick_samp_num_1 & m_brick_samp_num_2 & m_brick_samp_num_3 & m_brick_samp_num_4 & m_brick_samp_num_5 & m_brick_samp_num_6 & m_brick_samp_num_out\
				& m_brick_samp_int_1 & m_brick_samp_int_2 & m_brick_samp_int_3 & m_brick_samp_int_4 & m_brick_samp_int_5 & m_brick_samp_int_6 & m_brick_samp_int_out\
				& m_brick_ag_near & m_brick_ag_mid & m_brick_ag_far & m_brick_sigma2 & m_brick_sigma3 & m_brick_YM_min & m_brick_YM_max & m_brick_PR_min & m_brick_PR_max & m_brick_N_Iter\
				& m_brick_lowpass & m_brick_lowcut & m_brick_nInlineFrom & m_brick_nInlineTo & m_brick_nXlineFrom & m_brick_nXlineTo;
		}
	};
	struct GdeConherencyParameter
	{
		float m_conherency_fSampleInter;//单位s
		int m_conherency_nMaxBufferSize;
		int m_conherency_nOutSampNum;
		std::vector<int> m_conherency_linenos;
		std::vector<int> m_conherency_cdpnos;
		std::string m_conherency_vrmsname;
		std::string m_conherency_vintname;
		bool m_conherency_isvrmsgde;
		bool m_conherency_isvintgde;
		std::vector<float> m_conherency_pVelo;
		int m_conherency_nCompSpaceLen;

		int m_conherency_binnum;
		std::vector<int> m_conherency_mainfreqs;
		int m_conherency_nOutputCubeNum;
		int m_conherency_nOutputTimeInc;//单位ms
		std::vector<int> m_conherency_pWinLen;
		float m_conherency_fCdpInterval;
		float m_conherency_fLineInterval;
		int m_conherency_enumCoherentMethod;//0:normal,1:dip
		int m_conherency_enumDipUnit;//0:角度,1弧度
		int m_conherency_enumAziUnit;//0:角度,1弧度

		GdeConherencyParameter()
		{
		}
		GdeConherencyParameter(const GdeConherencyParameter &other)
		{
			*this = other;
		}
		const GdeConherencyParameter &operator=(const GdeConherencyParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_conherency_fSampleInter = other.m_conherency_fSampleInter;
			m_conherency_nMaxBufferSize = other.m_conherency_nMaxBufferSize;
			m_conherency_nOutSampNum = other.m_conherency_nOutSampNum;
			m_conherency_linenos = other.m_conherency_linenos;
			m_conherency_cdpnos = other.m_conherency_cdpnos;
			m_conherency_vrmsname = other.m_conherency_vrmsname;
			m_conherency_vintname = other.m_conherency_vintname;
			m_conherency_isvrmsgde = other.m_conherency_isvrmsgde;
			m_conherency_isvintgde = other.m_conherency_isvintgde;
			m_conherency_pVelo = other.m_conherency_pVelo;
			m_conherency_nCompSpaceLen = other.m_conherency_nCompSpaceLen;

			m_conherency_binnum = other.m_conherency_binnum;
			m_conherency_mainfreqs = other.m_conherency_mainfreqs;
			m_conherency_nOutputCubeNum = other.m_conherency_nOutputCubeNum;
			m_conherency_nOutputTimeInc = other.m_conherency_nOutputTimeInc;
			m_conherency_pWinLen = other.m_conherency_pWinLen;
			m_conherency_fCdpInterval = other.m_conherency_fCdpInterval;
			m_conherency_fLineInterval = other.m_conherency_fLineInterval;
			m_conherency_enumCoherentMethod = other.m_conherency_enumCoherentMethod;
			m_conherency_enumDipUnit = other.m_conherency_enumDipUnit;
			m_conherency_enumAziUnit = other.m_conherency_enumAziUnit;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_conherency_fSampleInter & m_conherency_nMaxBufferSize & m_conherency_nOutSampNum & m_conherency_linenos & m_conherency_cdpnos & \
				m_conherency_vrmsname & m_conherency_vintname & m_conherency_isvrmsgde & m_conherency_isvintgde & m_conherency_pVelo & m_conherency_nCompSpaceLen & \
				m_conherency_binnum & m_conherency_mainfreqs & m_conherency_nOutputCubeNum & m_conherency_nOutputTimeInc & m_conherency_pWinLen & \
				m_conherency_fCdpInterval & m_conherency_fLineInterval & m_conherency_enumCoherentMethod & m_conherency_enumDipUnit & m_conherency_enumAziUnit;
		}
	};
	struct GdeCurvatureParameter
	{
		std::vector<string> m_curvature_inputnames;
		bool m_curvature_bUseAziDip;
		int m_curvature_enumUnits0;
		int m_curvature_enumUnits1;
		int m_curvature_nOutSampNum;
		float m_curvature_fCdpInterval;
		float m_curvature_fLineInterval;
		int m_curvature_enumDevMethod;
		float m_curvature_fVelocity;
		bool m_curvature_bOutputMean;
		bool m_curvature_bOutputGaussian;
		bool m_curvature_bOutputMaximun;
		bool m_curvature_bOutputMinimun;
		bool m_curvature_bOutputMostPositive;
		bool m_curvature_bOutputMostNegative;
		bool m_curvature_bOutputDip;
		bool m_curvature_bOutputStrike;
		bool m_curvature_bOutputCurvature;
		bool m_curvature_bOutputShapeIndex;

		GdeCurvatureParameter()
		{
		}
		GdeCurvatureParameter(const GdeCurvatureParameter &other)
		{
			*this = other;
		}
		const GdeCurvatureParameter &operator=(const GdeCurvatureParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_curvature_inputnames = other.m_curvature_inputnames;
			m_curvature_bUseAziDip = other.m_curvature_bUseAziDip;
			m_curvature_enumUnits0 = other.m_curvature_enumUnits0;
			m_curvature_enumUnits1 = other.m_curvature_enumUnits1;
			m_curvature_nOutSampNum = other.m_curvature_nOutSampNum;
			m_curvature_fCdpInterval = other.m_curvature_fCdpInterval;
			m_curvature_fLineInterval = other.m_curvature_fLineInterval;
			m_curvature_enumDevMethod = other.m_curvature_enumDevMethod;
			m_curvature_fVelocity = other.m_curvature_fVelocity;
			m_curvature_bOutputMean = other.m_curvature_bOutputMean;
			m_curvature_bOutputGaussian = other.m_curvature_bOutputGaussian;
			m_curvature_bOutputMaximun = other.m_curvature_bOutputMaximun;
			m_curvature_bOutputMinimun = other.m_curvature_bOutputMinimun;
			m_curvature_bOutputMostPositive = other.m_curvature_bOutputMostPositive;
			m_curvature_bOutputMostNegative = other.m_curvature_bOutputMostNegative;
			m_curvature_bOutputDip = other.m_curvature_bOutputDip;
			m_curvature_bOutputStrike = other.m_curvature_bOutputStrike;
			m_curvature_bOutputCurvature = other.m_curvature_bOutputCurvature;
			m_curvature_bOutputShapeIndex = other.m_curvature_bOutputShapeIndex;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_curvature_inputnames & m_curvature_bUseAziDip & m_curvature_enumUnits0 & m_curvature_enumUnits1 & m_curvature_nOutSampNum\
				& m_curvature_fCdpInterval & m_curvature_fLineInterval & m_curvature_enumDevMethod & m_curvature_fVelocity & m_curvature_bOutputMean & m_curvature_bOutputGaussian\
				& m_curvature_bOutputMaximun & m_curvature_bOutputMinimun & m_curvature_bOutputMostPositive & m_curvature_bOutputMostNegative\
				& m_curvature_bOutputDip & m_curvature_bOutputStrike & m_curvature_bOutputCurvature & m_curvature_bOutputShapeIndex;
		}
	};
	struct GdeCagParameter
	{
		std::vector<double> m_cag_angles;
		std::vector<int> m_cag_linenos;
		std::vector<int> m_cag_cdpnos;
		std::string m_cag_vrmsname;
		std::string m_cag_vintname;
		bool m_cag_isvrmsgde;
		bool m_cag_isvintgde;
		int m_cag_converttype;
		double m_cag_azimuthlow;
		double m_cag_azimuthhigh;
		int m_cag_azimuthgroup;

		GdeCagParameter() : m_cag_vrmsname(""), m_cag_vintname(""), m_cag_isvrmsgde(false), m_cag_isvintgde(false), m_cag_converttype(0), m_cag_azimuthlow(0), m_cag_azimuthhigh(360), m_cag_azimuthgroup(12)
		{
		}
		GdeCagParameter(const GdeCagParameter &other)
		{
			*this = other;
		}
		const GdeCagParameter &operator=(const GdeCagParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_cag_angles = other.m_cag_angles;
			m_cag_linenos = other.m_cag_linenos;
			m_cag_cdpnos = other.m_cag_cdpnos;
			m_cag_vrmsname = other.m_cag_vrmsname;
			m_cag_vintname = other.m_cag_vintname;
			m_cag_isvrmsgde = other.m_cag_isvrmsgde;
			m_cag_isvintgde = other.m_cag_isvintgde;
			m_cag_converttype = other.m_cag_converttype;
			m_cag_azimuthlow = other.m_cag_azimuthlow;
			m_cag_azimuthhigh = other.m_cag_azimuthhigh;
			m_cag_azimuthgroup = other.m_cag_azimuthgroup;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_cag_angles & m_cag_linenos & m_cag_cdpnos & m_cag_vrmsname & m_cag_vintname & m_cag_isvrmsgde & m_cag_isvintgde & m_cag_converttype & m_cag_azimuthlow & m_cag_azimuthhigh & m_cag_azimuthgroup;
		}
	};
	struct GdeWindowParameter
	{
		std::vector<string> m_window_inputnames;
		int m_window_nOutSampNum;
		bool m_window_OutPutTimeThick;
		bool m_window_OutPutStatisticThick;
		bool m_window_OutPutStatisticThickPercent;
		bool m_window_OutPutRMS;
		bool m_window_OutPutMean;
		bool m_window_OutPutMeanAbsolute;
		bool m_window_OutPutSum;
		bool m_window_OutPutSumAbsolute;
		bool m_window_OutPutMin;
		bool m_window_OutPutMax;
		bool m_window_OutPutMaxAbsolute;
		bool m_window_OutPutArc;
		bool m_window_OutPutEnergyHalfTime;
		bool m_window_OutPutNumberofCrossZero;
		bool m_window_OutPutPseudoEntropy;
		bool m_window_OutPutVariance;
		bool m_window_OutPutSkew;
		bool m_window_OutPutKurtosis;
		bool m_window_OutPutRatio;
		std::vector<double> m_window_minvalues;
		std::vector<double> m_window_maxvalues;
		bool m_window_bImp;
		double m_window_fImpA;
		double m_window_fImpB;
		GdeWindowParameter()
		{
		}
		GdeWindowParameter(const GdeWindowParameter &other)
		{
			*this = other;
		}
		const GdeWindowParameter &operator=(const GdeWindowParameter &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_window_inputnames = other.m_window_inputnames;
			m_window_nOutSampNum = other.m_window_nOutSampNum;
			m_window_OutPutTimeThick = other.m_window_OutPutTimeThick;
			m_window_OutPutStatisticThick = other.m_window_OutPutStatisticThick;
			m_window_OutPutStatisticThickPercent = other.m_window_OutPutStatisticThickPercent;
			m_window_OutPutRMS = other.m_window_OutPutRMS;
			m_window_OutPutMean = other.m_window_OutPutMean;
			m_window_OutPutMeanAbsolute = other.m_window_OutPutMeanAbsolute;
			m_window_OutPutSum = other.m_window_OutPutSum;
			m_window_OutPutSumAbsolute = other.m_window_OutPutSumAbsolute;
			m_window_OutPutMin = other.m_window_OutPutMin;
			m_window_OutPutMax = other.m_window_OutPutMax;
			m_window_OutPutMaxAbsolute = other.m_window_OutPutMaxAbsolute;
			m_window_OutPutArc = other.m_window_OutPutArc;
			m_window_OutPutEnergyHalfTime = other.m_window_OutPutEnergyHalfTime;
			m_window_OutPutNumberofCrossZero = other.m_window_OutPutNumberofCrossZero;
			m_window_OutPutPseudoEntropy = other.m_window_OutPutPseudoEntropy;
			m_window_OutPutVariance = other.m_window_OutPutVariance;
			m_window_OutPutSkew = other.m_window_OutPutSkew;
			m_window_OutPutKurtosis = other.m_window_OutPutKurtosis;
			m_window_OutPutRatio = other.m_window_OutPutRatio;
			m_window_minvalues = other.m_window_minvalues;
			m_window_maxvalues = other.m_window_maxvalues;
			m_window_bImp = other.m_window_bImp;
			m_window_fImpA = other.m_window_fImpA;
			m_window_fImpB = other.m_window_fImpB;
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_window_inputnames & m_window_nOutSampNum & m_window_OutPutTimeThick & m_window_OutPutStatisticThick & m_window_OutPutStatisticThickPercent & m_window_OutPutRMS &\
				m_window_OutPutMean & m_window_OutPutMeanAbsolute & m_window_OutPutSum & m_window_OutPutSumAbsolute & m_window_OutPutMin & m_window_OutPutMax & m_window_OutPutMaxAbsolute &\
				m_window_OutPutArc & m_window_OutPutEnergyHalfTime & m_window_OutPutNumberofCrossZero & m_window_OutPutPseudoEntropy & m_window_OutPutVariance & m_window_OutPutSkew &\
				m_window_OutPutKurtosis & m_window_OutPutRatio & m_window_minvalues & m_window_maxvalues & m_window_bImp & m_window_fImpA & m_window_fImpB;
		}
	};
	/*!
	*
	**/
	struct TaskTraceHeadoffset
	{
		TaskCGeoPoint m_shotpt;
		TaskCGeoPoint m_detectionpt;
		int m_offset;

		TaskTraceHeadoffset() : m_offset(0)
		{
		}
		const TaskTraceHeadoffset &operator=(const TaskTraceHeadoffset &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_shotpt = other.m_shotpt;
			m_detectionpt = other.m_detectionpt;
			m_offset = other.m_offset;
			return *this;
		}
		static bool CompareDistance(const TaskTraceHeadoffset &a, const TaskTraceHeadoffset &b)
		{
			double distancea = sqrt((a.m_shotpt.m_x - a.m_detectionpt.m_x) * (a.m_shotpt.m_x - a.m_detectionpt.m_x) + (a.m_shotpt.m_y - a.m_detectionpt.m_y) * (a.m_shotpt.m_y - a.m_detectionpt.m_y));
			double distanceb = sqrt((b.m_shotpt.m_x - b.m_detectionpt.m_x) * (b.m_shotpt.m_x - b.m_detectionpt.m_x) + (b.m_shotpt.m_y - b.m_detectionpt.m_y) * (b.m_shotpt.m_y - b.m_detectionpt.m_y));
			if(::abs(distancea) < ::abs(distanceb))
				return true;
			return false;
		}
		static bool CompareAngle(const TaskTraceHeadoffset &a, const TaskTraceHeadoffset &b)
		{
			double distancea = sqrt((a.m_shotpt.m_x - a.m_detectionpt.m_x) * (a.m_shotpt.m_x - a.m_detectionpt.m_x) + (a.m_shotpt.m_y - a.m_detectionpt.m_y) * (a.m_shotpt.m_y - a.m_detectionpt.m_y));
			double distanceb = sqrt((b.m_shotpt.m_x - b.m_detectionpt.m_x) * (b.m_shotpt.m_x - b.m_detectionpt.m_x) + (b.m_shotpt.m_y - b.m_detectionpt.m_y) * (b.m_shotpt.m_y - b.m_detectionpt.m_y));
			double anglea = acos((a.m_detectionpt.m_x - a.m_shotpt.m_x) / distancea);
			double angleb = acos((b.m_detectionpt.m_x - b.m_shotpt.m_x) / distanceb);
			if(a.m_detectionpt.m_y < a.m_shotpt.m_y)
				anglea = 2 * PI - anglea;
			anglea = 2.5 * PI - anglea;
			if(anglea >= 2 * PI)
				anglea -= 2 * PI;
			if(b.m_detectionpt.m_y < b.m_shotpt.m_y)
				angleb = 2 * PI - angleb;
			angleb = 2.5 * PI - angleb;
			if(angleb >= 2 * PI)
				angleb -= 2 * PI;
			if(anglea < angleb)
				return true;
			return false;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_shotpt & m_detectionpt & m_offset;
		}
	};

	/*!
	*
	**/
	struct GdePosition
	{
		short m_inline;
		short m_xline;
		double m_zvaluemin;
		double m_zvaluemax;

		GdePosition() : m_inline(0), m_xline(0), m_zvaluemin(0.0), m_zvaluemax(0.0)
		{
		}
		GdePosition(const GdePosition &other)
		{
			*this = other;
		}
		const GdePosition &operator=(const GdePosition &other)
		{
			if(this != &other)
			{
				m_inline = other.m_inline;
				m_xline = other.m_xline;
				m_zvaluemin = other.m_zvaluemin;
				m_zvaluemax = other.m_zvaluemax;
			}

			return *this;
		}
		static bool ComparePosition(const GdePosition &a, const GdePosition &b)
		{
			if(a.m_inline < b.m_inline)
				return true;
			if(a.m_inline > b.m_inline)
				return false;
			if(a.m_xline < b.m_xline)
				return true;
			if(a.m_xline > b.m_xline)
				return false;
			return false;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_inline & m_xline & m_zvaluemin & m_zvaluemax;
		}
	};

	/*!
	*
	**/
	struct GdeTimeSlice
	{
		double m_timemin;
		double m_timemax;

		GdeTimeSlice() : m_timemin(0), m_timemax(0)
		{
		}
		GdeTimeSlice(const GdeTimeSlice &other)
		{
			*this = other;
		}
		const GdeTimeSlice &operator=(const GdeTimeSlice &other)
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
	struct GdeHorizonSlice
	{
		std::vector<GdePosition> m_survey;

		GdeHorizonSlice()
		{
		}
		GdeHorizonSlice(const GdeHorizonSlice &other)
		{
			*this = other;
		}
		const GdeHorizonSlice &operator=(const GdeHorizonSlice &other)
		{
			if(this != &other)
			{
				m_survey.clear();
				m_survey.assign(other.m_survey.begin(), other.m_survey.end());
			}
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
	enum GdeParameterType
	{
		GPT_Unknown,
		GPT_Slice_Time,
		GPT_Slice_Horizon,
		GPT_Slice_3D_Post,
		GPT_Slice_3D_Prestack,
		GPT_Attribute_Triangulate,
		GPT_Attribute_Instant,
		GPT_Attribute_DipAzimuth,
		GPT_Attribute_AlphaFilter,
		GPT_Attribute_Irregular,
		GPT_Attribute_Ellipse,
		GPT_Attribute_ThreeBayes,
		GPT_Attribute_BasicTrack,
		GPT_Attribute_RockPhysics,
		GPT_Attribute_Brick,
		GPT_Attribute_Conherency,
		GPT_Attribute_Curvature,
		GPT_Attribute_Cag,
		GPT_Attribute_Window,
		GPT_Raster_Slice,
		GPT_Marching_Cube,
		GPT_Max
	};

	/*!
	*
	**/
	struct GdeJobParameter : public JobParameter, public GdeTimeSlice, public GdeHorizonSlice, public GdeCubeParameter, public GdeFilterParameter, \
		public GdeAngleFractureParameter, public GdeInstantAttributeParameter, public GdeDipAzimuthParameter, public GdeAlphaFilterParameter, \
		public GdeIrregularParameter, public GdeThreeBayesParameter, public GdeBasicTrackParameter, public GdeRockPhysicsParameter, \
		public GdeBrickParameter, public GdeConherencyParameter, public GdeCurvatureParameter, public GdeCagParameter, public GdeWindowParameter
	{
		short m_jobtype;
		short m_parametertype;
		std::vector<unsigned long long> m_chunkuuids;
		int m_mroffset;

		GdeJobParameter() : m_jobtype(AnyRCF::JET_Unknown), m_parametertype(GPT_Unknown), m_mroffset(0)
		{
		}
		GdeJobParameter(const GdeJobParameter &other)
		{
			*this = other;
		}
		const GdeJobParameter &operator=(const GdeJobParameter &other)
		{
			*((JobParameter*)this) = *((JobParameter*)&other);
			*((GdeTimeSlice*)this) = *((GdeTimeSlice*)&other);
			*((GdeHorizonSlice*)this) = *((GdeHorizonSlice*)&other);
			*((GdeCubeParameter*)this) = *((GdeCubeParameter*)&other);
			*((GdeFilterParameter*)this) = *((GdeFilterParameter*)&other);
			*((GdeAngleFractureParameter*)this) = *((GdeAngleFractureParameter*)&other);
			*((GdeInstantAttributeParameter*)this) = *((GdeInstantAttributeParameter*)&other);
			*((GdeDipAzimuthParameter*)this) = *((GdeDipAzimuthParameter*)&other);
			*((GdeAlphaFilterParameter*)this) = *((GdeAlphaFilterParameter*)&other);
			*((GdeIrregularParameter*)this) = *((GdeIrregularParameter*)&other);
			*((GdeThreeBayesParameter*)this) = *((GdeThreeBayesParameter*)&other);
			*((GdeBasicTrackParameter*)this) = *((GdeBasicTrackParameter*)&other);
			*((GdeRockPhysicsParameter*)this) = *((GdeRockPhysicsParameter*)&other);
			*((GdeBrickParameter*)this) = *((GdeBrickParameter*)&other);
			*((GdeConherencyParameter*)this) = *((GdeConherencyParameter*)&other);
			*((GdeCurvatureParameter*)this) = *((GdeCurvatureParameter*)&other);
			*((GdeCagParameter*)this) = *((GdeCagParameter*)&other);
			*((GdeWindowParameter*)this) = *((GdeWindowParameter*)&other);
			
			m_jobtype = other.m_jobtype;
			m_parametertype = other.m_parametertype;
			m_chunkuuids = other.m_chunkuuids;
			m_mroffset = other.m_mroffset;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			serializeParent( (JobParameter*) 0, ar, *this);
			serializeParent( (GdeTimeSlice*) 0, ar, *this);
			serializeParent( (GdeHorizonSlice*) 0, ar, *this);
			serializeParent( (GdeCubeParameter*) 0, ar, *this);
			serializeParent( (GdeFilterParameter*) 0, ar, *this);
			serializeParent( (GdeAngleFractureParameter*) 0, ar, *this);
			serializeParent( (GdeInstantAttributeParameter*) 0, ar, *this);
			serializeParent( (GdeDipAzimuthParameter*) 0, ar, *this);
			serializeParent( (GdeAlphaFilterParameter*) 0, ar, *this);
			serializeParent( (GdeIrregularParameter*) 0, ar, *this);
			serializeParent( (GdeThreeBayesParameter*) 0, ar, *this);
			serializeParent( (GdeBasicTrackParameter*) 0, ar, *this);
			serializeParent( (GdeRockPhysicsParameter*) 0, ar, *this);
			serializeParent( (GdeBrickParameter*) 0, ar, *this);
			serializeParent( (GdeConherencyParameter*) 0, ar, *this);
			serializeParent( (GdeCurvatureParameter*) 0, ar, *this);
			serializeParent( (GdeCagParameter*) 0, ar, *this);
			serializeParent( (GdeWindowParameter*) 0, ar, *this);

			ar & m_jobtype & m_parametertype & m_chunkuuids & m_mroffset;
		}
	};

	/*!
	*
	**/
	struct GdeMapKey : public MapKey, public CalculatorCube::CubeExtent
	{
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
	struct GdeReduceKey : public ReduceKey, public GdeMapKey
	{

	};
	typedef std::vector<GdeMapKey> GdeMapKeyVector;

	/*!
	*
	**/
	struct GdeMapValue : public ReduceValue, public MapValue
	{
		std::vector<std::vector<double> > m_traces;
		std::vector<GdePosition> m_slice;

		void serialize(SF::Archive &ar)
		{
			ar & m_traces & m_slice;
		}
	};
	struct GdeReduceValue : public GdeMapValue
	{

	};

	/*!
	*
	**/
	struct GdeMapPair : public MapPair
	{
		unsigned long long m_chunkuuid;

		GdeMapKey m_key;
		GdeMapValue m_value;
		void serialize(SF::Archive &ar)
		{
			ar & m_chunkuuid & m_key & m_value;
		}
	};
}
#endif