 /* The AnyCGAL of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYCGAL_PLANAR_GRAPH_COLORING_H__
#define __ANYCGAL_PLANAR_GRAPH_COLORING_H__

// macro
#include "anycgal.h"

// georect etc
#include "any/base/anygeom.h"
#include "any/base/anystl.h"
using namespace AnyBase;

// histogram
#include "any/math/histogramdistribution.h"
using namespace AnyMath;

// refer to smart pointer
#include "boost/smart_ptr.hpp"
using namespace boost;

//
namespace AnyCGAL
{
	/*!
	* composite pattern against largest image data for mapping and reducing
	**/
	class ANYCGAL_CLASS CAnyPlanarGraphColoring
	{
		class WriteScanlineFileTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			WriteScanlineFileTask(int taskcount, int index, string scanlinefilepath, int scanlinefileheight, int scanlinefilewidth, CAnyPlanarGraphColoring *parent, CAnyCPUScheduler *scheduler);
			~WriteScanlineFileTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			string m_scanlinefilepath;
			int m_scanlinefileheight;
			int m_scanlinefilewidth;
			CAnyPlanarGraphColoring *m_parent;
			CAnyCPUScheduler *m_scheduler;
		};

	public:

		/*!
		*
		**/
		enum RasterType
		{
			IT_Unknown = 0,
			IT_Gray = 1,
			IT_RGB = 3,
			IT_RGB_True = 4,
		};
		
		/*!
		*
		**/
		struct RasterData
		{
			long m_idx; // tileid
			unsigned char m_type;
			CGeoRect<int> m_extent; // the position against the whole image
			unsigned char *m_data; // in minx->maxx and miny->maxy order

			RasterData() : m_idx(0), m_type(IT_Unknown), m_data(0)
			{
			}
			RasterData(const RasterData &other)
			{
				*this = other;
			}
			~RasterData()
			{
				if(m_data)
				{
					::free(m_data);
					m_data = NULL;
				}
			}
			const RasterData &operator=(const RasterData &other)
			{
				if(this == &other)
					return *this;
				m_type = other.m_type;
				m_data = other.m_data;
				m_extent = other.m_extent;
				return *this;
			}
		};

		/*!
		*
		**/
		struct ScanLine
		{
			long m_row; // which as Y direction for ordering
			long m_start; // along horizon
			long m_end; // along horizon

			ScanLine() : m_row(-1), m_start(-1), m_end(-1)
			{
			}
			ScanLine *Clone()
			{
				ScanLine *other = new ScanLine;
				other->m_start = m_start;
				other->m_end = m_end;
				other->m_row = m_row;
				return other;
			}
			bool IsIntersect(const ScanLine *other)
			{
				if(::fabs((double)(m_row - other->m_row)) > 1. || m_end < other->m_start || m_start > other->m_end)
				{
					return false;
				}
				return true;
			}
			static bool CompareRow(const ScanLine *a, const ScanLine *b)
			{
				if(a->m_row < b->m_row)
					return true;
				return false;
			}
			static bool CompareRowAndStart(const ScanLine *a, const ScanLine *b)
			{
				if(a->m_row < b->m_row)
					return true;
				if(a->m_row > b->m_row)
					return false;
				if(a->m_start < b->m_start)
					return true;
				if(a->m_start > b->m_start)
					return false;
				return false;
			}
		};
		typedef std::vector<ScanLine*> ScanLineVector;
		typedef ScanLineVector::iterator line_itr;
		typedef ScanLineVector::const_iterator line_citr;
		typedef std::vector<ScanLineVector> ScanLineMatrix;
		typedef std::stack<ScanLine*> ScanLineStack;
		
		/*!
		*
		**/
		struct ScanArea
		{
			long m_areaIdx; // idx
			int m_clrIdx; // color idx
			ScanLineVector m_lines; // scan lines in order
			CGeoRect<int> m_envelope; // index
			CGeoPoint<double> m_centroid; // centroid point
			static CGeoPoint<double> m_theleftpt;// min start pt
			int m_ptNumber; // polygon
			CGeoPoint<double> *m_pts; // polygon points

			ScanArea() : m_areaIdx(-1), m_clrIdx(-1), m_ptNumber(0), m_pts(0)
			{
			}
			~ScanArea()
			{
				for(int i = 0; i < m_lines.size(); i++)
				{
					delete m_lines[i];
					m_lines[i] = NULL;
				}
				m_lines.clear();
				if(m_pts)
				{
					::free(m_pts);
					m_pts = NULL;
				}
			}
			void Inflate(ScanLine *line)
			{
				m_envelope.m_minX = m_envelope.m_minX > line->m_start ? line->m_start : m_envelope.m_minX;
				m_envelope.m_maxX = m_envelope.m_maxX < line->m_end ? line->m_end : m_envelope.m_maxX;
				m_envelope.m_minY = m_envelope.m_minY > line->m_row ? line->m_row : m_envelope.m_minY;
				m_envelope.m_maxY = m_envelope.m_maxY < line->m_row + 1 ? line->m_row + 1 : m_envelope.m_maxY;
			}
			bool IsIntersect(ScanArea *other)
			{
				return m_envelope.IsIntersect(other->m_envelope);
			}
			bool IsOverlap(ScanArea *other)
			{
				int linesize = m_lines.size();
				int otherlinesize = other->m_lines.size();
				if(linesize == 0 || otherlinesize == 0)
					return false;
				int currow = m_lines[0]->m_row > other->m_lines[0]->m_row ? m_lines[0]->m_row : other->m_lines[0]->m_row;
				int offset = 0;
				int otheroffset = 0;
				while(true)
				{
					while(offset < linesize && m_lines[offset]->m_row < currow - 1)
						offset++;
					while(otheroffset < otherlinesize && other->m_lines[otheroffset]->m_row < currow - 1)
						otheroffset++;
					if(offset >= linesize || otheroffset >= otherlinesize)
						break;
					if(m_lines[offset]->m_row > currow + 1 || other->m_lines[otheroffset]->m_row > currow + 1)
					{
						currow++;
						continue;
					}
					int offsetend = offset;
					int otheroffsetend = otheroffset;
					while(offsetend < linesize && m_lines[offsetend]->m_row <= currow + 1)
						offsetend++;
					while(otheroffsetend < otherlinesize && other->m_lines[otheroffsetend]->m_row <= currow + 1)
						otheroffsetend++;
					for(int i = offset; i < offsetend; i ++)
					{
						for(int j = otheroffset; j < otheroffsetend; j++)
						{
							if(m_lines[i]->IsIntersect(other->m_lines[j]))
							{
								return true;
							}
						}
					}
					currow++;
				}
				return false;
			}
			void CalculateEnvelope()
			{
				for(int i = 0; i < m_lines.size(); i++)
				{
					if(i == 0)
					{
						m_envelope.m_minX = m_lines[i]->m_start;
						m_envelope.m_maxX = m_lines[i]->m_end;
						m_envelope.m_minY = m_lines[i]->m_row;
						m_envelope.m_maxY = m_lines[i]->m_row + 1;
					}
					else
					{
						if(m_envelope.m_minX > m_lines[i]->m_start)
							m_envelope.m_minX = m_lines[i]->m_start;
						if(m_envelope.m_maxX < m_lines[i]->m_end)
							m_envelope.m_maxX = m_lines[i]->m_end;
						if(m_envelope.m_minY > m_lines[i]->m_row)
							m_envelope.m_minY = m_lines[i]->m_row;
						if(m_envelope.m_maxY < m_lines[i]->m_row + 1)
							m_envelope.m_maxY = m_lines[i]->m_row + 1;
					}
				}
			}
			int CalculateArea()
			{
				int area = 0;
				for(int i = 0; i < m_lines.size(); i++)
				{
					area += (m_lines[i]->m_end - m_lines[i]->m_start);
				}
				return area;
			}
			void CalculateCentroid()
			{
				m_centroid.m_x = m_envelope.m_minX + m_envelope.Width() / 2.;
				m_centroid.m_y = m_envelope.m_minY + m_envelope.Height() / 2.;
			}
			void CalculateVectorLine(std::vector<ScanLineVector> &vectorlines)
			{
				if(m_lines.size() == 0)
					return;
				std::sort(m_lines.begin(), m_lines.begin(), ScanLine::CompareRowAndStart);
				// get row_offset, isadded
				std::map<int, int> row_offset;
				std::vector<bool> isadded;
				int currow = m_lines[0]->m_row;
				row_offset[currow - 1] = 0;
				row_offset[currow] = 0;
				for(int i = 0; i < m_lines.size(); i++)
				{
					isadded.push_back(false);
					if(m_lines[i]->m_row != currow)
					{
						currow = m_lines[i]->m_row;
						row_offset[currow] = i;
					}
				}
				row_offset[currow + 1] = m_lines.size();
				row_offset[currow + 2] = m_lines.size();
				// get vectorlines
				int lastaddfalsepos = 0;
				while(true)
				{
					// find firstline
					ScanLine* firstline = NULL;
					int firstlineoffset;
					for(int i = lastaddfalsepos; i < m_lines.size(); i++)
					{
						if(!isadded[i])
						{
							firstline = m_lines[i];
							isadded[i] = true;
							firstlineoffset = i;
							lastaddfalsepos = i;
							break;
						}
					}
					if(!firstline)
						break;
					// fill vectorline
					ScanLineVector subvectorlines;
					std::vector<int> subvectorlineoffsets;
					subvectorlines.push_back(firstline);
					subvectorlineoffsets.push_back(firstlineoffset);
					ScanLine* curline = firstline;
					int curlineoffset = firstlineoffset;
					std::vector<int> tomakefalse;
					int curdirection = 0;//0:up,1:down
					bool lastdirectionfind = true;
					//向上寻找与当前线相邻的线，找不到换方向找，两次都没找到则跳出
					while(true)
					{
						if(curdirection == 0)//向上找相邻线
						{
							int intersectcount = 0;//相邻线的个数,大于1表示是分叉节点
							int interoffset = -1;//上方的第一个相邻线
							for(int i = row_offset[curline->m_row]; i < row_offset[curline->m_row + 2]; i++)
							{
								if(m_lines[i]->IsIntersect(curline) && !isadded[i] && i != curlineoffset)
								{
									if(intersectcount == 0)
										interoffset = i;
									intersectcount++;
									if(intersectcount > 1)
										break;
								}
							}
							if(intersectcount == 0)//不相邻，换方向找或者跳出
							{
								if(lastdirectionfind)
								{
									curdirection = 1;
									lastdirectionfind = false;
									continue;
								}
								else
									break;
							}
							lastdirectionfind = true;
							if(intersectcount == 1)//上方只有1个相邻，再看下方有几个相邻，加起来大于1是分叉节点
							{
								for(int i = row_offset[curline->m_row - 1]; i < row_offset[curline->m_row]; i++)
								{
									if(m_lines[i]->IsIntersect(curline) && !isadded[i] && i != curlineoffset)
									{
										intersectcount++;
										break;
									}
								}
							}
							if(intersectcount > 1)
								tomakefalse.push_back(curlineoffset);
							curline = m_lines[interoffset];
							curlineoffset = interoffset;
							subvectorlines.push_back(curline);
							subvectorlineoffsets.push_back(curlineoffset);
							isadded[curlineoffset] = true;
						}
						else if(curdirection == 1)
						{
							int intersectcount = 0;
							int interoffset = -1;
							for(int i = row_offset[curline->m_row - 1]; i < row_offset[curline->m_row + 1]; i++)
							{
								if(m_lines[i]->IsIntersect(curline) && !isadded[i] && i != curlineoffset)
								{
									if(intersectcount == 0)
										interoffset = i;
									intersectcount++;
									if(intersectcount > 1)
										break;
								}
							}
							if(intersectcount == 0)
							{
								if(lastdirectionfind)
								{
									curdirection = 0;
									lastdirectionfind = false;
									continue;
								}
								else
									break;
							}
							lastdirectionfind = true;
							if(intersectcount == 1)
							{
								for(int i = row_offset[curline->m_row + 1]; i < row_offset[curline->m_row + 2]; i++)
								{
									if(m_lines[i]->IsIntersect(curline) && !isadded[i] && i != curlineoffset)
									{
										intersectcount++;
										break;
									}
								}
							}
							if(intersectcount > 1)
								tomakefalse.push_back(curlineoffset);
							curline = m_lines[interoffset];
							curlineoffset = interoffset;
							subvectorlines.push_back(curline);
							subvectorlineoffsets.push_back(curlineoffset);
							isadded[curlineoffset] = true;
						}
					}
					// do thin
					if(subvectorlines.size() > 6)
					{
						bool hasheadbranchpos = false;
						for(int i = 1; i < 3; i++)
						{
							if(hasheadbranchpos)
								break;
							for(int j = 0; j < tomakefalse.size(); j++)
							{
								if(subvectorlineoffsets[i] == tomakefalse[j])
								{
									hasheadbranchpos = true;
									for(int k = 0; k < i; k++)
										subvectorlines.erase(subvectorlines.begin());
									break;
								}
							}
						}
						bool hastailbranchpos = false;
						for(int i = subvectorlineoffsets.size() - 2; i > subvectorlineoffsets.size() - 4; i--)
						{
							if(hastailbranchpos)
								break;
							for(int j = 0; j < tomakefalse.size(); j++)
							{
								if(subvectorlineoffsets[i] == tomakefalse[j])
								{
									hastailbranchpos = true;
									for(int k = subvectorlineoffsets.size() - 1; k > i; k--)
										subvectorlines.erase(subvectorlines.end() - 1);
									break;
								}
							}
						}
					}
					// recycle lines which has multi branch
					for(int i = 0; i < tomakefalse.size(); i++)
						isadded[tomakefalse[i]] = false;
					// has circle
					if(subvectorlines.size() > 2 && subvectorlines[subvectorlines.size() - 1]->IsIntersect(subvectorlines[0]))
						subvectorlines.push_back(subvectorlines[0]);
					if(subvectorlines.size() >= 2)
						vectorlines.push_back(subvectorlines);
				}
			}
			bool DoFreemanAllpoints()
			{
				if(m_lines.size() < 2)
				{
					for(int i = 0; i < m_lines.size(); i++)
					{
						delete m_lines[i];
						m_lines[i] = NULL;
					}
					m_lines.clear();
					return false;
				}
				std::vector<CGeoPoint<int> > points;
				std::vector<int> pointsadded;
				for(int i = 0; i < m_lines.size(); i++)
				{
					for(int j = m_lines[i]->m_start; j < m_lines[i]->m_end; j++)
					{
						points.push_back(CGeoPoint<int>(j, m_lines[i]->m_row));
						pointsadded.push_back(0);
					}
				}
				std::sort(points.begin(), points.end(), CompareXY);
				std::vector<CGeoPoint<int> > outpoints;
				CGeoPoint<int> lastpoint;
				CGeoPoint<int> curpoint;
				bool first = true;
				while(true)
				{
					if(first)
					{
						first = false;
						lastpoint = curpoint = points[0];
						outpoints.push_back(curpoint);
						pointsadded[0]++;
					}
					else
					{
						std::vector<CGeoPoint<int> > ninepts;
						std::vector<int> ptoffsets;
						for(int i = -1; i <= 1; i++)
						{
							for(int j = -1; j <= 1; j++)
							{
								CGeoPoint<int> cmp;
								cmp.m_x = curpoint.m_x + i;
								cmp.m_y = curpoint.m_y + j;
								ninepts.push_back(cmp);
								std::vector<CGeoPoint<int> >::iterator lower = std::lower_bound(points.begin(), points.end(), cmp, CompareXY);
								if(lower != points.end() && lower->m_x == cmp.m_x && lower->m_y == cmp.m_y)
									ptoffsets.push_back(lower - points.begin());
								else
									ptoffsets.push_back(-1);
							}
						}
						std::vector<int> pttypes; // -1:notexist or edged or iscurpoint, 0:normal, 1:added, 2:added && islastpoint
						for(int i = 0; i < 9; i++)
						{
							if(ptoffsets[i] == -1 || i == 4)
							{
								pttypes.push_back(-1);
								continue;
							}
							if((i == 0 && (ptoffsets[1] == -1 || ptoffsets[3] == -1)) || \
								(i == 1 && (ptoffsets[0] == -1 || ptoffsets[2] == -1)) || \
								(i == 2 && (ptoffsets[1] == -1 || ptoffsets[5] == -1)) || \
								(i == 3 && (ptoffsets[0] == -1 || ptoffsets[6] == -1)) || \
								(i == 5 && (ptoffsets[2] == -1 || ptoffsets[8] == -1)) || \
								(i == 6 && (ptoffsets[3] == -1 || ptoffsets[7] == -1)) || \
								(i == 7 && (ptoffsets[6] == -1 || ptoffsets[8] == -1)) || \
								(i == 8 && (ptoffsets[5] == -1 || ptoffsets[7] == -1)))
							{
								if(ninepts[i].m_x == lastpoint.m_x && ninepts[i].m_y == lastpoint.m_y)
									pttypes.push_back(2);
								else if(pointsadded[ptoffsets[i]] > 0)
									pttypes.push_back(1);
								else
									pttypes.push_back(0);
								continue;
							}
							else
							{
								pttypes.push_back(-1);
								continue;
							}
						}
						bool added = false;
						int typetoselect = 0;
						while(true)
						{
							if(added || typetoselect > 2)
								break;
							if(typetoselect == 1)
							{
								bool find = false;
								int mintimes;
								int minoffset;
								for(int i = 0; i < ninepts.size(); i++)
								{
									if(pttypes[i] == typetoselect)
									{
										if(!find)
										{
											find = true;
											mintimes = pointsadded[ptoffsets[i]];
											minoffset = i;
										}
										else
										{
											if(mintimes > pointsadded[ptoffsets[i]])
											{
												mintimes = pointsadded[ptoffsets[i]];
												minoffset = i;
											}
										}
									}
								}
								if(find)
								{
									lastpoint = curpoint;
									curpoint = ninepts[minoffset];
									outpoints.push_back(curpoint);
									pointsadded[ptoffsets[minoffset]]++;
									added = true;
									break;
								}
							}
							else
							{
								for(int i = 0; i < ninepts.size(); i++)
								{
									if(pttypes[i] == typetoselect)
									{
										lastpoint = curpoint;
										curpoint = ninepts[i];
										outpoints.push_back(curpoint);
										pointsadded[ptoffsets[i]]++;
										added = true;
										break;
									}
								}
							}
							typetoselect++;
						}
						if(!added || (curpoint == outpoints[0] && pointsadded[0] > 5))
							break;
					}
				}
				if(m_pts)
				{
					::free(m_pts);
					m_pts = NULL;
				}
				m_ptNumber = outpoints.size();
				m_pts = (CGeoPoint<double>*)(::malloc(sizeof(CGeoPoint<double>) * m_ptNumber));
				for(int i = 0; i < outpoints.size(); i++)
				{
					m_pts[i].m_x = outpoints[i].m_x;
					m_pts[i].m_y = outpoints[i].m_y;
				}
				for(int i = 0; i < m_lines.size(); i++)
				{
					delete m_lines[i];
					m_lines[i] = NULL;
				}
				m_lines.clear();
				return true;
			}
			bool DoFreeman()
			{
				if(m_lines.size() < 2)
				{
					for(int i = 0; i < m_lines.size(); i++)
					{
						delete m_lines[i];
						m_lines[i] = NULL;
					}
					m_lines.clear();
					return false;
				}
				std::vector<CGeoPoint<int> > points;
				std::vector<bool> pointsadded;
				for(int i = 0; i < m_lines.size(); i++)
				{
					points.push_back(CGeoPoint<int>(m_lines[i]->m_start, m_lines[i]->m_row));
					points.push_back(CGeoPoint<int>(m_lines[i]->m_end - 1, m_lines[i]->m_row));
					pointsadded.push_back(false);
					pointsadded.push_back(false);
				}
				std::sort(points.begin(), points.end(), CompareXY);
				std::vector<CGeoPoint<int> > outpoints;
				while(true)
				{
					if(points.size() == 0)
						break;
					CGeoPoint<int> lastpoint;
					CGeoPoint<int> curpoint;
					bool first = true;
					while(true)
					{
						if(first)
						{
							first = false;
							if(outpoints.size() > 0)
							{
								CGeoPoint<int> cmp = outpoints[outpoints.size() - 1];
								std::vector<CGeoPoint<int> >::iterator lower = std::lower_bound(points.begin(), points.end(), cmp, CompareXY);
								if(lower == points.end())
								{
									lastpoint = curpoint = points[points.size() - 1];
									pointsadded[points.size() - 1] = true;
								}
								else
								{
									lastpoint = curpoint = *lower;
									pointsadded[lower - points.begin()] = true;
								}
								outpoints.push_back(curpoint);
							}
							else
							{
								lastpoint = curpoint = points[0];
								outpoints.push_back(curpoint);
								pointsadded[0] = true;
							}
						}
						else
						{
							bool find = false;
							for(int i = -1; i <= 1; i++)
							{
								if(find)
									break;
								for(int j = -1; j <= 1; j++)
								{
									if(find)
										break;
									if(i == 0 && j == 0)
										continue;
									CGeoPoint<int> cmp;
									cmp.m_x = curpoint.m_x + i;
									cmp.m_y = curpoint.m_y + j;
									if(cmp.m_x == lastpoint.m_x && cmp.m_y == lastpoint.m_y)
										continue;
									std::vector<CGeoPoint<int> >::iterator lower = std::lower_bound(points.begin(), points.end(), cmp, CompareXY);
									if(lower != points.end() && lower->m_x == cmp.m_x && lower->m_y == cmp.m_y && pointsadded[lower - points.begin()] == false)
									{
										find = true;
										lastpoint = curpoint;
										curpoint = *lower;
										outpoints.push_back(curpoint);
										pointsadded[lower - points.begin()] = true;
										break;
									}
									else
										continue;
								}
							}
							if(!find)
								break;
						}
					}
					std::vector<CGeoPoint<int> >::iterator itr = points.begin();
					std::vector<CGeoPoint<int> >::iterator last = points.end();
					std::vector<bool>::iterator itr1 = pointsadded.begin();
					std::vector<bool>::iterator last1 = pointsadded.end();
					while(itr != last)
					{
						if(*itr1 == true)
						{
							itr = points.erase(itr);
							last = points.end();
							itr1 = pointsadded.erase(itr1);
							last1 = pointsadded.end();
							continue;
						}
						itr++;
						itr1++;
					}
				}
				if(m_pts)
				{
					::free(m_pts);
					m_pts = NULL;
				}
				m_ptNumber = outpoints.size();
				m_pts = (CGeoPoint<double>*)(::malloc(sizeof(CGeoPoint<double>) * m_ptNumber));
				for(int i = 0; i < outpoints.size(); i++)
				{
					m_pts[i].m_x = outpoints[i].m_x;
					m_pts[i].m_y = outpoints[i].m_y;
				}
				for(int i = 0; i < m_lines.size(); i++)
				{
					delete m_lines[i];
					m_lines[i] = NULL;
				}
				m_lines.clear();
				return true;
			}
			static bool CompareXY(const CGeoPoint<int> &a, const CGeoPoint<int> &b)
			{
				if(a.m_y < b.m_y)
					return true;
				else if(a.m_y > b.m_y)
					return false;
				else if(a.m_x < b.m_x)
					return true;
				return false;
			}
			bool DoGranhamScanning(double crossval = 0)
			{
				if(m_lines.size() < 2)
				{
					for(int i = 0; i < m_lines.size(); i++)
					{
						delete m_lines[i];
						m_lines[i] = NULL;
					}
					m_lines.clear();
					return false;
				}
				std::vector<CGeoPoint<double> > points;
				int index = 0;
				for(int i = 0; i < m_lines.size(); i++)
				{
					points.push_back(CGeoPoint<double>(m_lines[i]->m_start, m_lines[i]->m_row));
					points.push_back(CGeoPoint<double>(m_lines[i]->m_end, m_lines[i]->m_row));
					if(i == 0 || m_theleftpt.m_x > m_lines[i]->m_start || (m_theleftpt.m_x == m_lines[i]->m_start && m_theleftpt.m_y > m_lines[i]->m_row))
					{
						m_theleftpt = CGeoPoint<double>(m_lines[i]->m_start, m_lines[i]->m_row);
						index = i * 2;
					}
				}
				CGeoPoint<double> temp = points[0];
				points[0] = points[index];
				points[index] = temp;
				std::vector<CGeoPoint<double> >::iterator iter = points.begin();
				iter++;
				std::sort(iter, points.end(), CompareGraham);
				std::vector<CGeoPoint<double> > outpoints;
				outpoints.push_back(points[0]);
				outpoints.push_back(points[1]);
				outpoints.push_back(points[2]);
				for(int i = 3; i < points.size(); i++)
				{
					while(outpoints.size() >= 2 && cross(outpoints[outpoints.size() - 1], outpoints[outpoints.size() - 2], points[i]) >= crossval)
					{
						outpoints.pop_back();
					}
					outpoints.push_back(points[i]);
				}
				if(m_pts)
				{
					::free(m_pts);
					m_pts = NULL;
				}
				m_ptNumber = outpoints.size();
				m_pts = (CGeoPoint<double>*)(::malloc(sizeof(CGeoPoint<double>) * m_ptNumber));
				for(int i = 0; i < outpoints.size(); i++)
					m_pts[i] = outpoints[i];
				for(int i = 0; i < m_lines.size(); i++)
				{
					delete m_lines[i];
					m_lines[i] = NULL;
				}
				m_lines.clear();
				return true;
			}
			static bool CompareGraham(const CGeoPoint<double> &a, const CGeoPoint<double> &b)
			{
				double result = cross(m_theleftpt, a, b);
				if(result > 0)
					return true;
				else if(result < 0)
					return false;
				else if(Getdistance(m_theleftpt, a) < Getdistance(m_theleftpt, b))
					return true;
				return false;
			}
			static double cross(const CGeoPoint<double> &a, const CGeoPoint<double> &b, const CGeoPoint<double> &c)
			{
				CGeoPoint<double> u, v;
				u.m_x = b.m_x - a.m_x;
				u.m_y = b.m_y - a.m_y;
				v.m_x = c.m_x - a.m_x;
				v.m_y = c.m_y - a.m_y;
				return u.m_x * v.m_y - v.m_x * u.m_y;
			}
			static bool Getdistance(const CGeoPoint<double> &a, const CGeoPoint<double> &b)
			{
				return (b.m_x - a.m_x) * (b.m_x - a.m_x) + (b.m_y - a.m_y) * (b.m_y - a.m_y);
			}
		};
		typedef std::vector<ScanArea*> ScanAreaList;
		typedef ScanAreaList::iterator area_itr;
		typedef ScanAreaList::const_iterator area_citr;

		/*!
		*
		**/
		struct HistogramParameter
		{
			double m_min;
			double m_max;
			int m_fractiles;	// groups

			HistogramParameter() : m_min(ANY_NAN), m_max(ANY_NAN), m_fractiles(0)
			{
			}
		};

		//
		typedef std::vector<CAnyPlanarGraphColoring *> ChildrenVector;
		typedef ChildrenVector::iterator child_itr;
		typedef ChildrenVector::const_iterator child_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyPlanarGraphColoring(RasterData *const data, const HistogramParameter &parameter);
		~CAnyPlanarGraphColoring();

	public:
		//
		// data 
		//
		/*!
		*
		**/
		void SetRasterData(RasterData *raster)
		{
			m_raster = raster;
		}
		const RasterData *GetRasterData()
		{
			return m_raster;
		}
		void SetTaskCount(int taskCount)
		{
			m_taskCount = taskCount;
		}
		
		//
		// histogram
		//
		/*!
		*
		**/
		void SetHistogram(const HistogramParameter &parameter)
		{
			m_hisParameter = parameter;
		}
		const CHistogramDistribution *GetHistogram()
		{
			return m_hisDistribution;
		}
		void MakeOwnHistogram();
		void MakeHistogram(int cur = 0);
		void DoMakeHistogram(int dummy = 0);	// thread function

		//
		// Scan Connected Area
		//
		/*!
		*
		**/
		void ScanConnectedArea(int cur = 0);
		void DoScanConnectedArea(int dummy = 0);
		void DoFindIntersected(ScanLine *line, ScanLineVector &lines, ScanLineStack &stack);
		int MergeOwnArea();
		int MergeArea();
		void DoMergeArea(ScanArea *area, ScanAreaList &otherAreas);

		//
		// composite
		//
		/*!
		*
		**/
		bool AddChildren(CAnyPlanarGraphColoring *children);
		void RemoveChildren();
		bool RemoveChildren(int gridCode);
		void FindNeighbors(CAnyPlanarGraphColoring *parent, ChildrenVector &neighbors);
		bool Postile2Morton(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);
		bool Morton2Postile(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		bool Morton2Tileid(std::vector<int> morton, int &tileid);
		bool Tileid2Morton(int tileid, std::vector<int> &morton);

		//
		// Graph Coloring
		//
		/*!
		*
		**/
		void DoGraphColoring(std::vector<int> &edgestarts, std::vector<int> &edgeends);
		static int GetColor(int colorid, int maxcolorid);
		int GetMaxColorid();
		
		//
		// Create Scanline file
		//
		/*!
		*
		**/
		void CreateScanlineFile(string scanlinefilepath, int scanlinefileheight, int scanlinefilewidth);
	public:
		int m_rasterid;
		RasterData *m_raster;
		HistogramParameter m_hisParameter;
		CHistogramDistribution *m_hisDistribution;
		CHistogramDistribution *m_hisDistributionr;
		CHistogramDistribution *m_hisDistributiong;
		CHistogramDistribution *m_hisDistributionb;
		double m_hisThreshold;
		int m_rgbscantype;
		double m_hisThresholdrlow;
		double m_hisThresholdglow;
		double m_hisThresholdblow;
		double m_hisThresholdrup;
		double m_hisThresholdgup;
		double m_hisThresholdbup;
		double m_rbgraterange;
		int m_porosityx;
		int m_porosityy;
		int m_scanlineminwidth;
		int m_areaminsize;
		int m_mergeowntimes;
		bool m_isCheckIntersect;
		ScanAreaList m_areas;
		ChildrenVector m_children;
		int m_taskCount;
	};
}
#endif