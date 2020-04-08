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
#ifndef __ANYGDE_LDM_DATA_OCTREE_CACHE_H__
#define __ANYGDE_LDM_DATA_OCTREE_CACHE_H__

//
#include "anygde.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataOctreeCache
	{
		// relatives
		friend class CAnyGdeDataOctreeCacheIterator;
		friend class CAnyGdeDataOctree;
		
	public:
		/*!
		*
		**/
		struct CacheChunk
		{
			//
			int m_hits;
			int m_size;

			/*!
			*
			**/
			CacheChunk() : m_hits(0), m_size(0)
			{
			}

			/*!
			*
			**/
			~CacheChunk()
			{
			}
		};

		/*!
		*
		**/
		struct CacheNode
		{
			/*!
			* Node make sense unless it is limited to one valid memory block
			*/
			CacheNode(CacheChunk *dataChunk) : m_dataChunk(dataChunk), m_next(0), m_prev(0)
			{
				m_dataChunk->m_hits++;
			}

			/*!
			*
			**/
			~CacheNode()
			{
			}

			// Always keep this item refer to a valid mem address and also support mixed usage of different types of memory
			CacheChunk *m_dataChunk;   

			// Connecting indicators belonging the same coord firstly or sequence order
			CacheNode* m_next;
			CacheNode* m_prev;
		};
		typedef CacheNode* cursor;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataOctreeCache();

		/*!
		*
		**/
		~CAnyGdeDataOctreeCache();

	public:
		//
		//
		//
		/*!
		* 
		*/
		CacheNode *Begin();

		/*!
		* 
		*/
		CacheNode *End();

		/*!
		*
		*/
		long GetCacheSize();

		/*!
		*
		*/
		long GetChunkNumber();

		//
		//
		//
		/*!
		*
		*/
		void Add(CacheChunk *dataChunk);

		/*!
		*
		*/
		void Remove(CacheNode &node);

		/*!
		*
		*/
		void RemoveAll();

		//
		//
		//
		/*!
		*
		*/
		void MoveFront(CacheNode &node);

		/*!
		*
		*/
		void EraseLRU();

	protected:
		// cursor
		CacheNode *m_start;
		CacheNode *m_end;

		//
		long m_cacheSize;
		long m_chunks;
	};

	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataOctreeCacheIterator
	{
	public:
		/*!
		*
		**/
		CAnyGdeDataOctreeCacheIterator(CAnyGdeDataOctreeCache::CacheNode &node);

		/*!
		*
		**/
		virtual ~CAnyGdeDataOctreeCacheIterator();

	public:
		//
		//
		//
		/*!
		*
		*/
		void StartFrom(CAnyGdeDataOctreeCache::CacheNode &node);

		/*!
		*
		*/
		const CAnyGdeDataOctreeCache::CacheChunk *operator*();

		/*!
		*
		*/
		const CAnyGdeDataOctreeCache::CacheNode *GetNode();

	public:
		//
		//
		//
		void operator ++();
		void operator ++(int);
		void operator --();
		void operator --(int);
		bool IsAtEnd();
		bool IsAtFirst();

	private:
		//
		CAnyGdeDataOctreeCache::CacheNode *m_cursor;
	};

}
#endif