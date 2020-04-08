/*!
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
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
#ifndef __ANYCGAL_PLANAR_GRAPH_COLORING3D_H__
#define __ANYCGAL_PLANAR_GRAPH_COLORING3D_H__

// macro
#include "anycgal.h"

// georect etc
#include "any/base/anygeom.h"
#include "any/base/anystl.h"
using namespace AnyBase;

// histogram
#include "any/math/histogramdistribution.h"
#include "any/math/anyconditionalsimulator.h"
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
	class ANYCGAL_CLASS CAnyPlanarGraphColoring3D
	{
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

		struct AreaCentroid
		{
			CGeoPoint<double> m_point;
			int m_offset;
			static bool ComparePosition(const AreaCentroid &a, const AreaCentroid &b)
			{
				if(a.m_point.m_x < b.m_point.m_x)
					return true;
				if(a.m_point.m_x > b.m_point.m_x)
					return false;
				if(a.m_point.m_y < b.m_point.m_y)
					return true;
				if(a.m_point.m_y > b.m_point.m_y)
					return false;
				if(a.m_point.m_z < b.m_point.m_z)
					return true;
				return false;
			}
			static bool ComparePointyz(const CGeoPoint<int> &a, const CGeoPoint<int> &b)
			{
				if(a.m_y < b.m_y)
					return true;
				if(a.m_y > b.m_y)
					return false;
				if(a.m_z < b.m_z)
					return true;
				return false;
			}
		};

		/*!
		*
		**/
		struct RasterData
		{
			long m_idx; // tileid
			unsigned char m_type;
			CGeoRect<int> m_extent; // the position against the whole image
			int m_zmin;
			int m_zmax;
			unsigned char *m_data; // in minx->maxx and miny->maxy order

			RasterData() : m_idx(0), m_type(IT_Unknown), m_zmin(0), m_zmax(0), m_data(0)
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
				m_zmin = other.m_zmin;
				m_zmax = other.m_zmax;
				return *this;
			}
		};

		/*!
		*
		**/
		struct ScanLine
		{
			long m_depth;
			long m_row; // which as Y direction for ordering
			long m_start; // along horizon
			long m_end; // along horizon

			ScanLine() : m_depth(-1), m_row(-1), m_start(-1), m_end(-1)
			{
			}
			ScanLine *Clone()
			{
				ScanLine *other = new ScanLine;
				other->m_depth = m_depth;
				other->m_start = m_start;
				other->m_end = m_end;
				other->m_row = m_row;
				return other;
			}
			bool IsIntersect(const ScanLine *other)
			{
				if(::fabs((double)(m_depth - other->m_depth)) > 1. || ::fabs((double)(m_row - other->m_row)) > 1. || m_end < other->m_start || m_start > other->m_end)
				{
					return false;
				}
				return true;
			}
			static bool CompareDepthandRow(const ScanLine *a, const ScanLine *b)
			{
				if(a->m_depth < b->m_depth)
					return true;
				if(a->m_depth > b->m_depth)
					return false;
				if(a->m_row < b->m_row)
					return true;
				return false;
			}
			static bool CompareRow(const ScanLine *a, const ScanLine *b)
			{
				if(a->m_row < b->m_row)
					return true;
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
			int m_zmin;
			int m_zmax;
			CGeoPoint<double> m_centroid; // centroid point

			ScanArea() : m_areaIdx(-1), m_clrIdx(-1), m_zmin(0), m_zmax(0)
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
			}
			void Inflate(ScanLine *line)
			{
				m_envelope.m_minX = m_envelope.m_minX > line->m_start ? line->m_start : m_envelope.m_minX;
				m_envelope.m_maxX = m_envelope.m_maxX < line->m_end ? line->m_end : m_envelope.m_maxX;
				m_envelope.m_minY = m_envelope.m_minY > line->m_row ? line->m_row : m_envelope.m_minY;
				m_envelope.m_maxY = m_envelope.m_maxY < line->m_row + 1 ? line->m_row + 1 : m_envelope.m_maxY;
				m_zmin = m_zmin > line->m_depth ? line->m_depth : m_zmin;
				m_zmax = m_zmax < line->m_depth + 1 ? line->m_depth + 1 : m_zmax;
			}
			bool IsIntersect(ScanArea *other)
			{
				if(m_zmin > other->m_zmax || m_zmax < other->m_zmin)
					return false;
				return m_envelope.IsIntersect(other->m_envelope);
			}
			bool IsOverlap(ScanArea *other)
			{
				int linesize = m_lines.size();
				int otherlinesize = other->m_lines.size();
				if(linesize == 0 || otherlinesize == 0)
					return false;
				int curdepth = m_lines[0]->m_depth > other->m_lines[0]->m_depth ? m_lines[0]->m_depth : other->m_lines[0]->m_depth;
				int offset = 0;
				int otheroffset = 0;
				while(true)
				{
					while(offset < linesize && m_lines[offset]->m_depth < curdepth - 1)
						offset++;
					while(otheroffset < otherlinesize && other->m_lines[otheroffset]->m_depth < curdepth - 1)
						otheroffset++;
					if(offset >= linesize || otheroffset >= otherlinesize)
						break;
					if(m_lines[offset]->m_depth > curdepth + 1 || other->m_lines[otheroffset]->m_depth > curdepth + 1)
					{
						curdepth++;
						continue;
					}
					int offsetend = offset;
					int otheroffsetend = otheroffset;
					while(offsetend < linesize && m_lines[offsetend]->m_depth <= curdepth + 1)
						offsetend++;
					while(otheroffsetend < otherlinesize && other->m_lines[otheroffsetend]->m_depth <= curdepth + 1)
						otheroffsetend++;
					std::sort(m_lines.begin() + offset, m_lines.begin() + offsetend, ScanLine::CompareRow);
					std::sort(other->m_lines.begin() + otheroffset, other->m_lines.begin() + otheroffsetend, ScanLine::CompareRow);
					int currow = m_lines[offset]->m_row > other->m_lines[otheroffset]->m_row ? m_lines[offset]->m_row : other->m_lines[otheroffset]->m_row;
					int suboffset = offset;
					int subotheroffset = otheroffset;
					while(true)
					{
						while(suboffset < offsetend && m_lines[suboffset]->m_row < currow - 1)
							suboffset++;
						while(subotheroffset < otheroffsetend && other->m_lines[subotheroffset]->m_row < currow - 1)
							subotheroffset++;
						if(suboffset >= offsetend || subotheroffset >= otheroffsetend)
						{
							std::sort(m_lines.begin() + offset, m_lines.begin() + offsetend, ScanLine::CompareDepthandRow);
							std::sort(other->m_lines.begin() + otheroffset, other->m_lines.begin() + otheroffsetend, ScanLine::CompareDepthandRow);
							break;
						}
						if(m_lines[suboffset]->m_row > currow + 1 || other->m_lines[subotheroffset]->m_row > currow + 1)
						{
							currow++;
							continue;
						}
						int suboffsetend = suboffset;
						int subotheroffsetend = subotheroffset;
						while(suboffsetend < offsetend && m_lines[suboffsetend]->m_row <= currow + 1)
							suboffsetend++;
						while(subotheroffsetend < otheroffsetend && other->m_lines[subotheroffsetend]->m_row <= currow + 1)
							subotheroffsetend++;
						for(int i = suboffset; i < suboffsetend; i ++)
						{
							for(int j = subotheroffset; j < subotheroffsetend; j++)
							{
								if(m_lines[i]->IsIntersect(other->m_lines[j]))
								{
									std::sort(m_lines.begin() + offset, m_lines.begin() + offsetend, ScanLine::CompareDepthandRow);
									std::sort(other->m_lines.begin() + otheroffset, other->m_lines.begin() + otheroffsetend, ScanLine::CompareDepthandRow);
									return true;
								}
							}
						}
						currow++;
					}
					curdepth++;
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
						m_zmin = m_lines[i]->m_depth;
						m_zmax = m_lines[i]->m_depth + 1;
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
						if(m_zmin > m_lines[i]->m_depth)
							m_zmin = m_lines[i]->m_depth;
						if(m_zmax < m_lines[i]->m_depth + 1)
							m_zmax = m_lines[i]->m_depth + 1;
					}
				}
			}
			int CalculateVolume()
			{
				int volume = 0;
				for(int i = 0; i < m_lines.size(); i++)
				{
					volume += (m_lines[i]->m_end - m_lines[i]->m_start);
				}
				return volume;
			}
			void CalculateCentroid()
			{
				m_centroid.m_x = m_envelope.m_minX + m_envelope.Width() / 2.;
				m_centroid.m_y = m_envelope.m_minY + m_envelope.Height() / 2.;
				m_centroid.m_z = (m_zmin + m_zmax) / 2.;
			}
		};
		typedef std::vector<ScanArea*> ScanAreaList;
		typedef ScanAreaList::iterator area_itr;
		typedef ScanAreaList::const_iterator area_citr;


		//
		typedef std::vector<CAnyPlanarGraphColoring3D *> ChildrenVector;
		typedef ChildrenVector::iterator child_itr;
		typedef ChildrenVector::const_iterator child_citr;
	public:
		class WriteScanlineFileTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			WriteScanlineFileTask(int taskcount, int index, string scanlinefilepath, int scanlinefileheight, int scanlinefilewidth, int scanlinefiledepth, CAnyPlanarGraphColoring3D *parent, CAnyCPUScheduler *scheduler);
			~WriteScanlineFileTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			string m_scanlinefilepath;
			int m_scanlinefileheight;
			int m_scanlinefilewidth;
			int m_scanlinefiledepth;
			CAnyPlanarGraphColoring3D *m_parent;
			CAnyCPUScheduler *m_scheduler;
		};
		class MarchingCubeTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MarchingCubeTask(int taskcount, int index, int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, string meshfilepath, bool istoscreen, bool ismultifile, \
				double widthmappixelrate, double heightmappixelrate, double depthmappixelrate, double layerxmin, double layerymin, double layerzmin, \
				AnyCGAL::CAnyPlanarGraphColoring3D::ScanLineVector &scanlines, CAnyPlanarGraphColoring3D *parent, CAnyCPUScheduler *scheduler);
			~MarchingCubeTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			int m_xmin;
			int m_xmax;
			int m_ymin;
			int m_ymax;
			int m_zmin;
			int m_zmax;
			string m_meshfilepath;
			bool m_istoscreen;
			bool m_ismultifile;
			double m_widthmappixelrate;
			double m_heightmappixelrate;
			double m_depthmappixelrate;
			double m_layerxmin;
			double m_layerymin;
			double m_layerzmin;
			AnyCGAL::CAnyPlanarGraphColoring3D::ScanLineVector m_scanlines;
			CAnyPlanarGraphColoring3D *m_parent;
			CAnyCPUScheduler *m_scheduler;
		};
		class MarchingMagicCubeTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MarchingMagicCubeTask(int taskcount, int index, std::vector<int> &nHs, ExperimentalVariogram_Structure*** Ori3dEvs, std::vector<double> &validvaluemins, std::vector<double> &validvaluemaxs, CAnyPlanarGraphColoring3D *parent, CAnyCPUScheduler *scheduler);
			~MarchingMagicCubeTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			std::vector<int> m_nHs;
			ExperimentalVariogram_Structure*** m_Ori3dEvs;
			std::vector<double> m_validvaluemins;
			std::vector<double> m_validvaluemaxs;
			CAnyPlanarGraphColoring3D *m_parent;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyPlanarGraphColoring3D(RasterData *const data);
		~CAnyPlanarGraphColoring3D();

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
		// Scan Connected Area
		//
		/*!
		*
		**/
		void ScanConnectedArea(int cur = 0);
		void DoScanConnectedArea(int dummy);
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
		bool AddChildren(CAnyPlanarGraphColoring3D *children);
		void RemoveChildren();
		bool RemoveChildren(int gridCode);
		void FindNeighbors(CAnyPlanarGraphColoring3D *parent, ChildrenVector &neighbors);
		bool Postile2Morton(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);
		bool Morton2Postile(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		bool Morton2Tileid(std::vector<int> morton, int &tileid);
		bool Tileid2Morton(int tileid, std::vector<int> &morton);

		//
		// Delunary
		//
		/*!
		*
		**/
		void Make3DDelumary(std::vector<int> &edgestarts, std::vector<int> &edgeends);
		void MakeSkinSurface(std::vector<CGeoPoint<double> > &inpts, double shrinkfactor, std::vector<CGeoPoint<double> > &outpts, std::vector<int> &outfaces);
		void Make3DSolidMesh(std::vector<CGeoPoint<double> > &inpts, std::vector<int> &infaces, std::vector<CGeoPoint<double> > &outpts, std::vector<int> &outfaces);
		void Make3DSurfaceMesh(std::vector<CGeoPoint<double> > &inpts, std::vector<CGeoPoint<double> > &outpts, std::vector<int> &outfaces);

		void FilterPtsByCubeExtent(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, std::vector<CGeoPoint<int> > &pts, std::vector<int> &colors);
		void MarchingCube(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, std::vector<CGeoPoint<double> > &pts, std::vector<int> &faces, string meshfilepath, bool istoscreen, bool ismultifile, \
			double widthmappixelrate, double heightmappixelrate, double depthmappixelrate, double layerxmin, double layerymin, double layerzmin, int taskcount);
		void MarchingMagicCube(std::vector<int> &nHs, ExperimentalVariogram_Structure*** Ori3dEvs, std::vector<double> &validvaluemins, std::vector<double> &validvaluemaxs, std::vector<CGeoPoint<double> > &pts, std::vector<int> &faces, int taskcount);
		void FormOneMarchingLayer(int xmin, int xmax, int ymin, int ymax, int depth, std::vector<std::vector<bool> > &flags, ScanLineVector &scanlines);
		static void FormOneCubeMesh(std::vector<bool> &cube, std::vector<CGeoPoint<double> > &cubepts, std::vector<CGeoPoint<double> > &pts, std::vector<int> &faces, int truecount);
		static void FormOneCubeMesh_1pt(std::vector<bool> &cube, string &code);
		static void FormOneCubeMesh_2pt(std::vector<bool> &cube, string &code);
		static void FormOneCubeMesh_3pt(std::vector<bool> &cube, string &code);
		static void FormOneCubeMesh_4pt(std::vector<bool> &cube, string &code);
		static void FormOneCubeMesh_5pt(std::vector<bool> &cube, string &code);
		static void FormOneCubeMesh_6pt(std::vector<bool> &cube, string &code);
		static void FormOneCubeMesh_7pt(std::vector<bool> &cube, string &code);
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
		void CreateScanlineFile(string scanlinefilepath, int scanlinefileheight, int scanlinefilewidth, int scanlinefiledepth);
	public:
		int m_rasterid;
		RasterData *m_raster;
		double m_hisThreshold;
		double m_rbgraterange;
		int m_porosityx;
		int m_porosityy;
		int m_porosityz;
		int m_scanlineminwidth;
		int m_volumeminsize;
		int m_mergeowntimes;
		bool m_isCheckIntersect;
		ScanAreaList m_areas;
		ChildrenVector m_children;
		int m_taskCount;
		std::vector<std::vector<CGeoPoint<double> > > m_ptsforMT;
		std::vector<std::vector<int> > m_facesforMT;
	};
}
#endif