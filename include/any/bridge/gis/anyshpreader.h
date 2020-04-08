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
#ifndef __ANYBRIDGE_SHPREADER_H__
#define __ANYBRIDGE_SHPREADER_H__

// Refer to EXPORT & IMPORT
#include "..\anybridge.h"

// Refer to SHP basic definitions
#include "anyshpbasic.h"

// Refer to portable definitions
#include "any/base/anyport.h"
#include "any/base/anyfilebasic.h"
#include "any/base/anydirbasic.h"
#include "any/base/anyplatinfo.h"
using namespace AnyBase;

#include "boost/shared_ptr.hpp"
using namespace boost;
// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  //  needs to have dll-interface

// Declare namespace 
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyShpReader
	{
		// Callback function in order to check whether one geometry is suitable to be removed from current
		// cache
		typedef bool (*IsUsed)(const string &layerName, boost::shared_ptr<ShpGeometry> oneGeometry);

		// Simple memory cache
		typedef std::deque<boost::shared_ptr<ShpGeometry> > GeometryCache;
		typedef GeometryCache::iterator cache_itr;
		typedef GeometryCache::const_iterator cache_citr;

		// Maximum of this cache
		static const int MAXCACHESIZE = 1000;

	public:
		//
		//
		//
		/*!
		* Note:
		* This file name shouldn't include suffix since we need two file with respect to 
		* .shp & .idx two files according to this name definition
		**/
		CAnyShpReader(const anystring &fileName, bool isCached = true);

		/*!
		*
		**/
		~CAnyShpReader();

	public:
		//
		// I/O functions
		//
		/*!
		*
		**/
		bool Open(bool isForData = false);

		/*!
		*
		**/
		void LoadFileCache();
		char* GetFileCache();
		void SetFileCache(char* filecache);
		void ReleaseFileCache();

		/*!
		*
		**/
		void Close();

		/*!
		*
		*/
		unsigned short GetShpType();

		//
		// Read operations
		//
		/*!
		*
		**/
		int GetCount();

		/*!
		*
		**/
		boost::shared_ptr<ShpGeometry> GetGeometry(int idx);

		/*!
		*
		**/
		const ShpDesc &GetDescription();

		//
		// Deal with some object adhering to some specifications. E.g., for polygons, the first ring should be
		// outer ring and others should be inner rings
		//
		/*!
		*
		**/
		bool Rewind(boost::shared_ptr<ShpGeometry> geometry);

		//
		// Callback function
		//
		/*!
		*
		**/
		void SetCallback(IsUsed oneFunc);

		/*!
		*
		**/
		const anystring &GetFileName();

	private:
		//
		//
		//
		/*!
		*
		**/
		boost::shared_ptr<ShpGeometry> GetPolys(int idx, int shpType);

		/*!
		*
		**/
		boost::shared_ptr<ShpGeometry> GetPoints(int idx, int shpType);

		/*!
		*
		**/
		boost::shared_ptr<ShpGeometry> GetPoint(int idx, int shpType);

	public:
		// Simple geometry cache in order to ecrease the numnber of I/O access
		GeometryCache m_cache;

	private:
		// File name
		anystring m_fileName;

		// SHP description
		ShpDesc m_description;

		// Little or Big endian
		bool m_isLittle;

		// Handle for .shp file
		void *m_dataHandle;
		long long m_datafilelength;

		// Handle for .idx file
		void *m_idxHandle;

		// Whether geometries are cached
		bool m_isCache;

		// File basic functions
		const CAnyFileBasic &m_fileBasic;

		// Path basic functions
		const CAnyDirBasic &m_pathBasic;

		// Platform basic functions
		const CAnyPlatInfo &m_platInfo;

		// Callback function
		IsUsed m_check;

		// The worst circustances where no any geometry will may be removed from memory cache
		// and we only change below variable in order to enlarge the grid size
		int m_cacheSize;

		// Memory prepared satifying with different object demands in order to avoid frequently 
		// allocate memory
		int m_bufSize;
		unsigned char *m_buf;

		char *m_filedatacache;//load whole file into cache
	};
}
#endif