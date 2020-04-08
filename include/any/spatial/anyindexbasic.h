/*!
 * The AnyNet of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON NETWORK PROGRAMMING DEMANDS of other packages.
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
#ifndef __ANYINDEX_INDEXBASIC_H__
#define __ANYINDEX_INDEXBASIC_H__

// Refer to EXPORT & IMPORT
#include "anyindex.h"

// Refer to geometry basic definition
#include "any/base/anygeom.h"
using namespace AnyBase;

// Declare namespace
namespace AnyIndex
{
	/*!
	* The maximum tile number for each layer
	**/
	static const int MAXTILECOUNT = 256;

	/*!
	* Index types
	**/
	enum IndexType
	{
		IT_Unknown = -1,
		IT_RegularGrid,
		IT_GeneralGrid,
		IT_Sequence,
		IT_Gram,
		IT_Quard,
		IT_Max
	};

	/*!
	* Parcel expression in one tile
	*/
	struct GeoParcel
	{
		// Unique flag and its content
		unsigned long m_idx;
		CGeoRect<double> m_mbr;

		// Initialization
		GeoParcel() : m_idx(-1), m_mbr(0., 0., 0., 0.)
		{
		}
	};

	/*!
	* Titles expression in one layer
	*/
	struct GeoTile
	{
		// Unique flag and its extent
		unsigned int m_idx;
		CGeoRect<double> m_mbr;

		// Parcel definition for one tile
		int m_xCount;
		int m_yCount;

		// Its parcels in regular way, namely, the same width & the same height
		double m_xWidth;
		double m_yHeight;

		// Those tiles belonging to the same layer and its number should be xCount * yCount
		GeoParcel *m_parcels;

		// Initialization
		GeoTile() : m_idx(-1), m_mbr(0., 0., 0., 0.), m_xCount(0), m_yCount(0), m_parcels(0),
			m_xWidth(0.), m_yHeight(0.)
		{
		}

		// Relase
		~GeoTile()
		{
			if(m_parcels)
			{
				delete []m_parcels;
			}
			m_parcels = 0;
		}
	};

	/*!
	* Following network type, data in layers
	*/
	struct GeoLayer
	{
		// Unique flag and its extent
		unsigned short m_idx;
		CGeoRect<double> m_mbr;	

		// Tile definition for this layer
		int m_xCount;
		int m_yCount;

		// Tiles in regular way, namely, the same width & height
		double m_xWidth;
		double m_yHeight;

		// Those tiles belonging to the same layer and its number should be xCount * yCount
		GeoTile *m_tiles;

		/*!
		*
		**/
		GeoLayer() : m_idx(-1), m_mbr(0., 0., 0., 0.), m_xCount(0), m_yCount(0), m_tiles(0),
			m_xWidth(0.), m_yHeight(0.)
		{
		}

		/*!
		*
		**/
		~GeoLayer()
		{
			if(m_tiles)
			{
				delete []m_tiles;
			}
			m_tiles = 0;
		}
	};
	typedef std::map<string, GeoLayer> LayerMap;
}
#endif