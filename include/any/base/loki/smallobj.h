#ifndef __ANYBASE_SMALLOBJECT_H__
#define __ANYBASE_SMALLOBJECT_H__

// Refer to imort & export definitions
#include "anybase.h"

// Refer to standard STL definitions
#include "anystl.h"

// Refer to singleton 
#include "singleton.h"

/**
* The design and that of implementation of a fast allocator for small objects.
*/
namespace AnyBase
{
	/**
	* Note:
	* This include file is benefited from the ideas of "Modern C++" written by  by Andrei Alexandrescu
	*/
	namespace Loki
	{
        // The specified memory for allocation of small object and it will be divided by given block size
        #ifndef DEFAULT_CHUNK_SIZE
        #define DEFAULT_CHUNK_SIZE  4096
        #endif

        // Which size is the small for below special allocation
        #ifndef MAX_SMALL_OBJECT_SIZE
        #define MAX_SMALL_OBJECT_SIZE  64
        #endif

		/**
		* Offers services for allocating fixed-sized objects
		* It knows how to allocate and deallocate blocks of a fixed size but is not limited to a chunk's size. Its capacity is
		* limited only by available memory.
		*/
		class FixedAllocator
		{
		public: 
			/**
			* A chunk of memory containing a fixed amount of blocks. At construction time, you configure the block size and the number of blocks.
			* A Chunk contains logic that allows you to allocate and deallocate memory blocks from that chunk of memory. When there are 
			* no more blocks available in the chunk, the allocation function returns zero.
			*/
			class Chunk
			{
				// VC7 access control BUG
				friend FixedAllocator;

				/**
				*
				*/
				void Init(std::size_t blockSize, unsigned char blocks);

				/**
				*
				*/
				void* Allocate(std::size_t blockSize);

				/**
				*
				**/
				void Deallocate(void* p, std::size_t blockSize);

				/**
				*
				**/
				void Reset(std::size_t blockSize, unsigned char blocks);

				/**
				*
				**/
				void Release();

				// Memory for allocation in groups, the unit size is block size
				unsigned char *m_data;
				// which unit is the first avaliable, namely, from it those chunks can be allocated
				unsigned char m_firstAvailableBlock;
				// which units is avaliable
				unsigned char m_blocksAvailable;
			};
			typedef std::vector<Chunk> Chunks;
		   
		public:
			/**
			* Create a FixedAllocator able to manage blocks of 'blockSize' size
			*/
			explicit FixedAllocator(std::size_t blockSize = 0);

			/**
			*
			**/
			FixedAllocator(const FixedAllocator&);

			/**
			*
			**/
			FixedAllocator& operator=(const FixedAllocator&);

			/**
			*
			**/
			~FixedAllocator();
		    
		public:
			/**
			*
			**/
			void Swap(FixedAllocator& rhs);
		    
			/**
			* Allocate a memory block
			*/
			void *Allocate();

			/**
			* Deallocate a memory block previously allocated with Allocate()
			* (if that's not the case, the behavior is undefined)
			*/
			void Deallocate(void* p);

			/**
			* Returns the block size with which the FixedAllocator was initialized
			*/
			std::size_t BlockSize() const
			{ return m_blockSize; }

			/**
			* Comparison operator for sorting 
             * Here the intention of this operator is to directly sort elements in one vector 
			 * but VC7 doesn't support this usage, give error C2784: 'bool std::operator <(const std::vector<_Ty,_Alloc> &,const std::vector<_Ty,_Alloc> &)' : 
			 * could not deduce template argument for 'const std::vector<_Ty,_Alloc> &' from 'const size_t'
			**/
			bool operator < (std::size_t rhs) const
			{ return BlockSize() < rhs; }

		private:
			/**
			*
			**/
			void DoDeallocate(void* p);

			/**
			*
			**/
			Chunk* VicinityFind(void* p);

		private:
			// Data 
			std::size_t m_blockSize;
			unsigned char m_numBlocks;

			// How many chunks compositing current fixed allocator
			Chunks m_chunks;
			Chunk *m_allocChunk;
			Chunk *m_deallocChunk;

			// For ensuring proper copy semantics
			mutable const FixedAllocator *m_prev;
			mutable const FixedAllocator *m_next;
		};

		/**
		* Offers services for allocating small-sized objects
		*/
		class ANYBASE_CLASS SmallObjAllocator
		{
			// Define memory pool containing different fixed allocators
			typedef std::vector<FixedAllocator> Pool;

		public:
			/**
			*
			**/
			SmallObjAllocator(std::size_t chunkSize, std::size_t maxObjectSize);

			/**
			*
			**/
			void* Allocate(std::size_t numBytes);

			/**
			*
			**/
			void Deallocate(void* p, std::size_t size);

		private:
			// Not permited to do type conversion implicitly
			SmallObjAllocator(const SmallObjAllocator&);
			SmallObjAllocator& operator=(const SmallObjAllocator&);

			/**
			*
			**/
			static bool CompareNumbytes(const FixedAllocator &first, const FixedAllocator &second);

		private:
			// Set of different fixed allocators specified to different small size
			Pool m_pool;

			// The address of first element of this memory pool
			FixedAllocator *m_lastAlloc;
			FixedAllocator *m_lastDealloc;

			// The basic chunk defintion and which small size is suitable
			std::size_t m_chunkSize;
			std::size_t m_maxObjectSize;
		};

		/**
		* class SmallObject
		* Base class for polymorphic small objects, offers fast allocations/deallocations
		*/
		template
		<
			template <class> class ThreadingModel = DEFAULT_THREADING,
			std::size_t chunkSize = DEFAULT_CHUNK_SIZE,
			std::size_t maxSmallObjectSize = MAX_SMALL_OBJECT_SIZE
		>
		class SmallObject : public ThreadingModel< SmallObject<ThreadingModel, chunkSize, maxSmallObjectSize> >
		{
			typedef ThreadingModel< SmallObject<ThreadingModel, chunkSize, maxSmallObjectSize> > MyThreadingModel;
			struct MySmallObjAllocator : public SmallObjAllocator
			{
				MySmallObjAllocator() : SmallObjAllocator(chunkSize, maxSmallObjectSize)
				{}
			};

			// The typedef below would make things much simpler, 
			//     but MWCW won't like it
			// typedef SingletonHolder<MySmallObjAllocator/*, CreateStatic, 
			//        DefaultLifetime, ThreadingModel*/> MyAllocator;
		public:
			/**
			*
			**/
			static  void* operator new(std::size_t size)
			{
#if (MAX_SMALL_OBJECT_SIZE != 0) && (DEFAULT_CHUNK_SIZE != 0)
				typename MyThreadingModel::Lock lock;
				(void)lock; // get rid of warning
	            
				return SingletonHolder<MySmallObjAllocator, CreateStatic, PhoenixSingleton>::Instance().Allocate(size);
#else
				return ::operator new(size);
#endif
			}

			/**
			*
			**/
			static  void operator delete(void* p, std::size_t size)
			{
#if (MAX_SMALL_OBJECT_SIZE != 0) && (DEFAULT_CHUNK_SIZE != 0)
				typename MyThreadingModel::Lock lock;
				(void)lock; // get rid of warning
	            
				SingletonHolder<MySmallObjAllocator, CreateStatic, PhoenixSingleton>::Instance().Deallocate(p, size);
#else
				::operator delete(p, size);
#endif
			}

			/**
			*
			**/
			virtual ~SmallObject() {}
		};
 	}
}
#endif