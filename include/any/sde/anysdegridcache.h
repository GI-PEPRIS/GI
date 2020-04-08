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
#ifndef __ANYSDE_SDE_GRID_CACHE_H__
#define __ANYSDE_SDE_GRID_CACHE_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anylightlru.h"
using namespace AnyBase;

// Refer to "test object"
#include "any/base/loki/singleton.h"
using namespace AnyBase::Loki;

// refer to index grid
#include "anysdeindexgrid.h"

//
namespace AnySDE
{
	/*!
	* this class should be as a singleton for cache management against all SDE layers
	**/
	class ANYSDE_CLASS CAnySdeGridCache
	{
		// Not permit copy & assign operations
		CAnySdeGridCache(const CAnySdeGridCache &other);
		const CAnySdeGridCache &operator=(const CAnySdeGridCache &other);
		
		// sinleton
		typedef SingletonHolder<CAnySdeGridCache, CreateUsingNew> Singleton;

	public:
        // Grid cache for rendering
		// One shape file should only have one grid cache for demands of different scale rendering
		// grids cached and those maybe discarded
		// ...
		typedef CAnyLightLru<CAnySdeIndexGrid> GridPointerCache;
		typedef std::map<string, GridPointerCache> LayerPointerCache;
		typedef LayerPointerCache::iterator pointer_cache_itr;
		typedef LayerPointerCache::const_iterator pointer_cache_citr;

		// backup geometries of one grid since they may be "seriously" lost
		// and here should store more info in order to quickly "POSITION" which geometry row or record ?
		// by default, is "ROWID"
		// ...
		typedef std::vector<std::vector<long> > GridIdxCache;
		typedef std::map<string, GridIdxCache> LayerIdxCache;
		typedef LayerIdxCache::iterator idx_cache_itr;
		typedef LayerIdxCache::const_iterator idx_cache_citr;

	public:
		//
		// as singleton
		//
		/*!
		*
		**/
		CAnySdeGridCache();

		/*!
		*
		**/
		~CAnySdeGridCache();

	public:
		//
		//
		//
		/*!
		*
		**/
		GridPointerCache &PreparePointerCache(const string &layerName);

		/*!
		*
		**/
		GridIdxCache &PrepareIdxCache(const string &layerName);

		/*!
		*
		**/
		void Clear(const string &layerName);

		/*!
		*
		**/
		void ClearAll();

	public:
		/*!
		*
		**/
		static bool CompareCacheIdx(long first, long second)
		{
			return first < second;
		}

		/*!
		*
		**/
		static CAnySdeGridCache &GetSingleton(short type);

	private:
		//
		LayerPointerCache m_ptCaches;
		LayerIdxCache m_idxCaches;
	};
}
#endif