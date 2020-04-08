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
#ifndef __ANYGDE_LDM_DATA_OCTREE_H__
#define __ANYGDE_LDM_DATA_OCTREE_H__

//
#include "anygde.h"

// refer to cache chunk
#include "anygdedataoctreecache.h"

// refer to geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to boost share_ptr
#include "boost\smart_ptr.hpp"
using namespace boost;

//
namespace AnyGDE
{
	// forward class
	class CAnyGdeDataTrace;
	class CAnyGdeDataIterator;

	/*!
	* linear octree
	**/
	class ANYGDE_CLASS CAnyGdeDataOctree
	{
		//
		friend class CAnyGdeDataOctreeGate;

	public:
		/*!
		* the whole tree extent
		**/
		struct OctreeCube
		{
			// spatial planar: X-Y direction, from left-down, anti-clockwise
			CGeoPoint<double> m_pos1;
			CGeoPoint<double> m_pos2;
			CGeoPoint<double> m_pos3;
			CGeoPoint<double> m_pos4;
			// line/cdp num, not x/y cubenode num 
			int m_xcount; 
			int m_ycount;
			// time window as Z direction
			double m_minTime;
			double m_maxTime;
			double m_interval;
			int m_octreeLevel;

			/*!
			*
			**/
			OctreeCube() : m_xcount(0), m_ycount(0), m_minTime(ANY_NAN), m_maxTime(ANY_NAN), m_interval(ANY_NAN), m_octreeLevel(0)
			{
			}

			/*!
			*
			**/
			OctreeCube(const OctreeCube &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const OctreeCube &operator=(const OctreeCube &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_pos1 = other.m_pos1;
				m_pos2 = other.m_pos2;
				m_pos3 = other.m_pos3;
				m_pos4 = other.m_pos4;
				m_xcount = other.m_xcount;
				m_ycount = other.m_ycount;
				m_minTime = other.m_minTime;
				m_maxTime = other.m_maxTime;
				m_interval = other.m_interval;
				m_octreeLevel = other.m_octreeLevel;

				return *this;
			}
		};

		/*!
		* cell extent in physical definition
		**/
		struct OctreeTileDimension
		{
			// tile size
			int m_tileSizex;
			int m_tileSizey;
			int m_tileSizez;

			// the size
			double m_xDimension;
			double m_yDimension;
			double m_zDimension;

			// the overlaps
			double m_xOverlaps;
			double m_yOverlaps;
			double m_zOverlaps;

			/*!
			*
			**/
			OctreeTileDimension() : m_tileSizex(ANY_NAN), m_tileSizey(ANY_NAN), m_tileSizez(ANY_NAN), \
				m_xDimension(ANY_NAN), m_yDimension(ANY_NAN), m_zDimension(ANY_NAN), \
				m_xOverlaps(ANY_NAN), m_yOverlaps(ANY_NAN), m_zOverlaps(ANY_NAN)
			{
			}

			/*!
			*
			**/
			OctreeTileDimension(const OctreeTileDimension &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const OctreeTileDimension &operator=(const OctreeTileDimension &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_tileSizex = other.m_tileSizex;
				m_tileSizey = other.m_tileSizey;
				m_tileSizez = other.m_tileSizez;

				m_xDimension = other.m_xDimension;
				m_yDimension = other.m_yDimension;
				m_zDimension = other.m_zDimension;

				m_xOverlaps = other.m_xOverlaps;
				m_yOverlaps = other.m_yOverlaps;
				m_zOverlaps = other.m_zOverlaps;

				return *this;
			}
		};

		/*!
		* limits to leaf code only
		**/
		struct OctreeNode : public CAnyGdeDataOctreeCache::CacheChunk
		{
			// morton code
			std::vector<int> m_mortonCode;
			// cell position
			unsigned long m_tileCode;
			// spatial position
			CGeoPoint<double> m_center;
			
			// for non-leaf node directly composites its leaf children
			// smarter means not directly erse child node when ancestors still existing
			// ...
			std::vector<boost::shared_ptr<OctreeNode> > m_children; 
			// for leaf node
			unsigned char *m_traces;
			// per trace data size
			long m_traceSize;

			/*!
			*
			**/
			OctreeNode() : m_tileCode(ANY_NAN), m_traces(0), m_traceSize(ANY_NAN)
			{
			}
		
			/*!
			*
			**/
			~OctreeNode()
			{
				if(m_traces)
				{
					delete m_traces;
				}
			}

		private:
			//
			OctreeNode(const OctreeNode &other);
			const OctreeNode &operator=(const OctreeNode &other);
		};

		/*!
		* index for cache nodes
		**/
		struct OctreeNodeIndex
		{
			unsigned long m_tileCode;
			CAnyGdeDataOctreeCache::cursor m_cursor;
		};
		typedef std::vector<OctreeNodeIndex> IndexVector;
		typedef IndexVector::iterator idx_itr;
		typedef IndexVector::const_iterator idx_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataOctree();

		/*!
		*
		*/
		~CAnyGdeDataOctree();

	public:
		//
		// cube specification
		//
		/*!
		*
		**/
		void SetOctreeCube(const OctreeCube &cube);

		/*!
		*
		**/
		const OctreeCube &GetOctreeCube();

		/*!
		*
		**/
		void SetOctreeTile(const OctreeTileDimension &tileDimension);

		/*!
		*
		**/
		const OctreeTileDimension &GetOctreeTile();

		//
		// kinds of code conversion
		//
		/*!
		*
		**/
		bool Cubecoord2Position(CGeoPoint<double> &cubecoord, CGeoPoint<int> &Position);

		/*!
		*
		**/
		bool Position2Cubecoord(CGeoPoint<int> &Position, CGeoPoint<double> &cubecoord);

		/*!
		*
		**/
		bool Time2Positionz(double time, int &ZPosition);
		
		/*!
		*
		**/
		bool Positionz2Time(int ZPosition, double &time);
				
		/*!
		*
		**/
		bool PositionToPostile(CGeoPoint<int> Position, int fetchlevel, CGeoPoint<int> &postile);
						
		/*!
		*
		**/
		bool PostileToPosition(CGeoPoint<int> postile, int fetchlevel, CGeoPoint<int> &Position1, CGeoPoint<int> &Position2);

		/*!
		*
		**/
		bool Postile2Morton(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);

		/*!
		*
		**/
		bool Morton2Postile(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		
		/*!
		*
		**/
		bool Morton2Tileid(std::vector<int> morton, int &tileid);
		
		/*!
		*
		**/
		bool Tileid2Morton(int tileid, std::vector<int> &morton);

		//
		// simple topological relationships
		//
		/*!
		*
		**/
		void GetLeafChildren(unsigned long tileCode, std::vector<unsigned long> &leafs);

		/*!
		*
		**/
		void GetAncestors(unsigned long tileCode, std::vector<unsigned long> &ancestors);

		//
		// get sample trace under the help of cache, and may merge traces fetched from different tile
		//
		/*!
		* from cache
		**/
		CAnyGdeDataTrace *GetDataTrace(int tileCode);
		
		/*!
		*
		**/
		CAnyGdeDataTrace *FromNodeToTrace(OctreeNode *node);	
				
		/*!
		*
		**/
		OctreeNode *GetOctreeNode(unsigned long tileCode);

	public:
		/*!
		*
		**/
		bool CreateCacheNodes(std::vector<OctreeNode*> nodes);

		/*!
		*
		**/
		static bool CompareOctreeIndex(const OctreeNodeIndex &first, const OctreeNodeIndex &second)
		{
			return first.m_tileCode < second.m_tileCode;
		};

	protected:
		/*!
		*
		**/
		CAnyGdeDataTrace *DoDirectFromCache(unsigned long tileCode);

	public:
		// specification
		OctreeCube m_cube;
		// volume data cube
		OctreeTileDimension m_tileDimension;
		// rendering cube
		short m_tilePixel;	

		// nodes in cache
		IndexVector m_indices; // sort by tilecode
		CAnyGdeDataOctreeCache m_cache; // sort by used order, not by hits
		long m_cacheLimits; // in memory size not number
	};
}

#endif
