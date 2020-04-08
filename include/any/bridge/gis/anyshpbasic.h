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
#ifndef __ANYBRIDGE_SHPBASIC_H__
#define __ANYBRIDGE_SHPBASIC_H__

// Refer to geometry basic definition
#include "any/base/anygeom.h"
using namespace AnyBase;

// Declare namespace
namespace AnyBridge
{
	/*!
	* Types of SHP geometries
	**/
	enum ShpType
	{
		ST_Null			= 0,
		ST_Point		= 1,
		ST_PolyLine		= 3,
		ST_Polygon		= 5,
		ST_MultiPoint	= 8,
		ST_PointZ		= 11,
		ST_PolyLineZ	= 13,
		ST_PolygonZ		= 15,
		ST_MultiPointZ	= 18,
		ST_PointM		= 21,
		ST_PolyLineM	= 23,
		ST_PolygonM		= 25,
		ST_MultiPointM	= 28,
		ST_MultiPatch	= 31,
		ST_MAX
	};

	/*!
	* A multipatch object including different parts interpreted as below
	* 0: Triangle Strip, A linked strip of triangles, where every vertex (after the first two) completes a new 
	*    triangle. A new triangle is always formed by connecting the new vertex with its two immediate predecessors.
	* 1: Triangle Fan: A linked fan of triangles, where every vertex (after the first two) completes a new triangle. 
	*	 A new triangle is always formed by connecting the new vertex with its immediate predecessor and the 
	*    first vertex of the part.
	* 2: Outer Ring: The outer ring of a polygon
	* 3: Inner Ring: A hole of a polygon
	* 4: Ring: A ring of a polygon of an unspecified type
	**/
	enum PatchPartType
	{
		PPT_TriStrip	= 0, 
		PPT_TriFan		= 1,
		PPT_OuterRing	= 2,
		PPT_InnerRing	= 3,
		PPT_FirstRing	= 4,
		PPT_Ring		= 5
	};

	/*!
	* Shp basic description
	**/
	struct ShpDesc
	{
		// The whole file size: Read from SHP header
		int m_fileSize;

		// Extent: Read from SHP header
		double m_xMin;
		double m_xMax;
		double m_yMin;
		double m_yMax;
		double m_zMin;
		double m_zMax;
		double m_mMin;
		double m_mMax;

		// Shape type: Read from SHX header
		int m_shpType;

		// The total number of records: Read from SHX header
		int m_records;

		// When inserting geometry object, max records means memory already allocated
		int m_maxRecords;

		// Directly store offset addresses: Read from SHX header
		int *m_offsets;

		// Directly store record sizes: Read from SHX header
		int *m_sizes;

		/*!
		*
		**/
		ShpDesc() : m_fileSize(0), m_shpType(0), m_records(0), m_maxRecords(0), m_offsets(0), m_sizes(0),
			m_xMin(0.), m_xMax(0.), m_yMin(0.), m_yMax(0.), m_zMin(0.), m_zMax(0.), m_mMin(0.), m_mMax(0.)
		{
		}

		/*!
		*
		**/
		~ShpDesc()
		{
			if(m_offsets)
			{
				::free(m_offsets);
			}
			m_offsets = 0;

			if(m_sizes)
			{
				::free(m_sizes);
			}
			m_sizes = 0;
		}
    };

	/*!
	*
	**/
	struct ShpCoord
	{
		// coordinate info
		double m_xCoord;
		double m_yCoord;
		double m_zCoord;
		double m_mCoord;
	};

	/*!
	*
	**/
	struct ShpGeometry
	{
		// SHP type
		int m_shpType;

		// Idx: -1 is unknown or unassigned
		unsigned long m_idx;

		// maximum part number
		const static int MAXPARTS = 512;
		// real part number
		int m_parts;
		// Offsets for different parts(not physical offset, only points' count)
		int m_partOffsets[MAXPARTS];
		// Types for different parts
		int m_partTypes[MAXPARTS];

		// Altitude & Measure extent
		double m_xMin;
		double m_xMax;
		double m_yMin;
		double m_yMax;
		double m_zMin;
		double m_zMax;
		double m_mMin;
		double m_mMax;

		// Vert number
		// coords or address
		int m_vertices;
		ShpCoord m_coords[1];

		/*!
		*
		**/
		ShpGeometry() : m_shpType(0), m_idx(-1), m_parts(0), /*m_partOffsets(0), m_partTypes(0), */m_vertices(0),/* m_xCoords(0),
			m_yCoords(0), m_zCoords(0), m_mCoords(0),*/ m_xMin(0), m_xMax(0), m_yMin(0), m_yMax(0), 
			m_zMin(0), m_zMax(0), m_mMin(0), m_mMax(0)
		{
		}

		/*!
		*
		**/
		~ShpGeometry()
		{
		}

		/*!
		* 
		**/
		bool CalcExtent(CGeoRect<double> &extent)
		{
			if(m_vertices)
			{
				extent.m_minX = extent.m_maxX = m_coords[0].m_xCoord;
				extent.m_minY = extent.m_maxY = m_coords[0].m_yCoord;

				int part = 0;
				for(; part < m_parts; part++)
				{
					int vertStart = m_partOffsets[part];
					int vertCount = 0;
					if(part == m_parts-1)
					{
						vertCount = m_vertices - m_partOffsets[part];
					}
					else
					{
						vertCount = m_partOffsets[part+1] - m_partOffsets[part];
					}

					int vert = vertStart;
					int count = vertStart + vertCount - 1;
					for(; vert < count; vert++)
					{
						extent.m_minX = (extent.m_minX < m_coords[vert].m_xCoord) ? extent.m_minX : m_coords[vert].m_xCoord;
						extent.m_minY = (extent.m_minY < m_coords[vert].m_yCoord) ? extent.m_minY : m_coords[vert].m_yCoord;
						extent.m_maxX = (extent.m_maxX > m_coords[vert].m_xCoord) ? extent.m_maxX : m_coords[vert].m_xCoord;
						extent.m_maxY = (extent.m_maxY > m_coords[vert].m_yCoord) ? extent.m_maxY : m_coords[vert].m_yCoord;
					}
				}

				return true;
			}

			return false;
		}

		/*!
		*
		**/
		bool GetExtent(CGeoRect<double> &extent)
		{
			if(m_vertices)
			{
				extent.m_minX = m_xMin;
				extent.m_maxX = m_xMax;
				extent.m_minY = m_yMin;
				extent.m_maxY = m_yMax;

				return true;
			}

			return false;
		}
	};
}

#endif