/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYSDE_SDE_INDEX_GRID_H__
#define __ANYSDE_SDE_INDEX_GRID_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to kinds of sde geometries
#include "anysdegeometry.h"

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to boost share_ptr
#include "boost/smart_ptr.hpp"
using namespace boost;

#include "any/thread/monitor.h"

//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnySdeIndexGrid : public JTCMonitor
	{
		// Not permit copy & assign operations
		CAnySdeIndexGrid(const CAnySdeIndexGrid &other);
		const CAnySdeIndexGrid &operator=(const CAnySdeIndexGrid &other);

	public:
		//
		struct BorderGeometryIndex
		{
			long m_grididx;
			long m_geometryidx;
		};
		typedef std::vector<BorderGeometryIndex> BorderGeometryVector;

		// Pointers set for current SHP layer in this grid
		typedef std::vector<boost::shared_ptr<CAnySdeGeometry> > GeometryVector;
		typedef GeometryVector::iterator geom_itr;
		typedef GeometryVector::const_iterator geom_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeIndexGrid();
		~CAnySdeIndexGrid();

	public:
        /*!
        *
        */
        void Delete();
		int GetIdx() const
		{
			return m_id;
		}
		void GetGeometry(boost::shared_ptr<CAnySdeGeometry> &geometry, long geometryidx)
		{
			int low = 0, high = m_geometries.size() - 1, mid;
			while(low <= high)
			{
				mid = low + (high - low) / 2;
				if(m_geometries[mid]->m_idx == geometryidx)
				{
					geometry = m_geometries[mid];
					break;
				}
				else if(m_geometries[mid]->m_idx > geometryidx)
					high = mid - 1;
				else
					low = mid + 1;
			}
		}
		void SetGeometry(boost::shared_ptr<CAnySdeGeometry> &geometry, long geometryidx)
		{
			int low = 0, high = m_geometries.size() - 1, mid;
			while(low <= high)
			{
				mid = low + (high - low) / 2;
				if(m_geometries[mid]->m_idx == geometryidx)
				{
					m_geometries[mid] = geometry ;
					break;
				}
				else if(m_geometries[mid]->m_idx > geometryidx)
					high = mid - 1;
				else
					low = mid + 1;
			}
		}

		/*!
		*
		**/
		static bool CompareGeometryIdx(const boost::shared_ptr<CAnySdeGeometry> first, const boost::shared_ptr<CAnySdeGeometry> second)
		{
			return first->m_idx < second->m_idx;
		}
		static bool CompareBorderGeometryIdx(const BorderGeometryIndex &first, const BorderGeometryIndex &second)
		{
			return first.m_geometryidx < second.m_geometryidx;
		}

    public:
        // grid idx
        unsigned int m_id;

		// belong to which layer
		short m_layerIdx;

		// bounding envolope
		CGeoRect<double> m_extent;

		// geometries covered 
		GeometryVector m_geometries;
		BorderGeometryVector m_borders;
	};
}
#endif