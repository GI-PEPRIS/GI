#ifndef __ANYBASE_ALLOCATOR_H__ 
#define __ANYBASE_ALLOCATOR_H__

// Refer to EXPORT & IMPORT macroes
#ifndef __ANYBASE_DEF_H__
#include "anybase.h"
#endif

// UeBase namespace
namespace AnyBase
{
	/**
    * \brief
	* Set up segmental memory pooling mechansim in order to erase memory fragmentations based on one piece of virtual 
	* memory address space. Meanwhile, it also forcefully to declare one memory block when facing limitation.
	*
	* 1) Memory segment(POOL): one virtual memory address is divided into two kinds of segments: bucket and heap
	* 2) Bucket segment(SEGMENT/CHUNKS): one part of above VM address is divied into different spaces having the same size of blocks
	* 3) Heap segment(SEGMENT/CHUNKS): one part of above VM address is directly used as the same way to use malloc etc alloctors
	* 4) Bucket block(BLOCK): a single directional list recording all blocks belonging to one bucket
	* 5) Heap block(BLOCK): it can directly allocate un-fixed size of memory when bucket segment can't satisfy 
	* this kind of memory allocation
	*
	* Note: here two goals should be considered when u specify one dynamic allocator by yourself
	* 1) Memory Throughout: the average time for mallocing and freeing one memory block
	* 2) Memory Utilization: the larger memory size compared to current heap maximum size
	*/
    class ANYBASE_CLASS CAnyAllocator
    {
    private:
        /**
        * Blocks belonging to one bucket segment.
		**/
        struct BucketBlock
        {
			// Maximum number of buckets
			const static int MAXBUCKETNUM = 7;

            // Blocks defintion/description as a backward list
            // The pointer pointing to VM address is used to create block list
            unsigned char *m_nextBlock;		
            unsigned int m_size;
            unsigned int m_numBlocks;

			// Status of current blocks
            unsigned int m_numAllocated;
            unsigned int m_maxAllocated;
            unsigned int m_numRequested;

            // TODO:
            // Here should exist one thread synchronization object

            //
            BucketBlock() : m_nextBlock(0), m_size(0), m_numBlocks(0), m_numAllocated(0), 
				m_maxAllocated(0), m_numRequested(0)
            {
            }
        };

        /**
		* Index table for quickly positioning one block and locates which bucket and its position in this bucket
		* the maximum index size is the the number of buckets, default given 7 not specfied value 401.
		**/
        struct IndexTable
        {
			// 
			const static int MAXMAPPINGNUM = 401;

			//
            unsigned short m_bucketIdx;
            unsigned short m_numRequested;
            unsigned short m_numFailure;

            //
            IndexTable() : m_bucketIdx(-1), m_numRequested(0), m_numFailure(0)
            {
            }
        };

        /**
		* One kind of segments: a larger heap allocated for outside memory demands in un-fixed size.
		* Namely, the way is like u directly use malloc or other dynamic allocator except for it prepare one 
		* larger heap in advance.
		**/
        struct HeapBlock
        {
			//
            HeapBlock *m_nextBlock;
            unsigned int m_blockSize;

            //
            HeapBlock() : m_nextBlock(0), m_blockSize(0)
            {
            }
        };

        /**
		* Region information describing the segment layout information after initializing one heap block.
		**/
        struct BucketSegment
        {
			// Its parent segment, namely, MemoryPool
            void *m_parent;  

			// Its plain description
            unsigned char *m_start;
            unsigned int m_size;

            //
            BucketSegment() : m_parent(0), m_start(0), m_size(0)
            {
            }
        };

        /**
		* Block defintion belonging to one bucket.
		**/
        struct BucketSetting
        {
			//
            unsigned int m_blockSize;
            unsigned int m_numBlocks;

            //
            BucketSetting() : m_blockSize(0), m_numBlocks(0)
            {
            }
        };

        /**
		* Memory Region configure for heap allocation.
		**/
        struct HeapSegment
        {
			//
            HeapBlock *m_nextBlock;
            unsigned int m_avaliableSize;
            unsigned int m_minSize;

			//
            unsigned short m_numRequested;
            unsigned short m_numFailure;
            unsigned short m_lastRequestedSize;
            
            // TODO:
            // It had better add thread synchronization object
        };

        /**
		* Memory region block.
		**/
        struct MemoryPool
        {
			// It had better to set up connection between VM and PM. However, currently it is no any sense
			// and we delegate this task to OS
            char *m_physicalAddr;

			// Bucket segment description
            BucketSegment m_bucket;
            unsigned int m_bucketSize;
            unsigned int m_maxBlockSize;
            unsigned int m_numBuckets;

			// Rule how to specify the size of each bucket while easily using below mechansim easily to position
			// one block belonging to which bucket segment.
			// Here m_bucketQntSize means the basic memory allocation unit for each bucket, that is, the size of 
			// one block of one bucket is the power of 2 of this allocation unit.
			// E.g., m_bucketQntSize * 2^m_bucketQntPower is the size of one block belonging to one bucket. So,
			// according to the block size, we can easily to know this block locates which bucket segment
			//
            unsigned int m_bucketQntSize;
            unsigned int m_bucketQntPower;

			// Mapping between buckets and its index table
			IndexTable m_mapTbl[IndexTable::MAXMAPPINGNUM];
			BucketBlock m_bucketTbl[BucketBlock::MAXBUCKETNUM];

			// Heap segment
            bool m_heapFlag;
            unsigned int m_heapSize;
            HeapSegment m_heapSegment;

            //
            MemoryPool() : m_physicalAddr(0), m_bucketSize(0), m_bucketQntSize(0), m_bucketQntPower(0), 
                m_maxBlockSize(0), m_numBuckets(0), m_heapFlag(0), m_heapSize(0)
            {
            }
        };

        /**
		* Block defintion beloning to one heap beginning from m_virtualAddr, and we would divide it into many bucket blcoks
		* and heap blocks.
		**/
        struct SegmentSetting
        {
			//
            unsigned int m_size;
            unsigned char *m_virtualAddr;
            unsigned char *m_physicalAddr;

			// In order to clearly record which block is belonging to which bucket, define the unit size of memory block 
            // Default is 16
            unsigned int m_bucketQntSize;
            // Define what is the order of 2 given above size definition
            // Default is 4
            unsigned short m_numBuckets;
			BucketSetting m_buckets[BucketBlock::MAXBUCKETNUM];

            //
            SegmentSetting() : m_size(0), m_virtualAddr(0), m_physicalAddr(0), m_bucketQntSize(0), m_numBuckets(0)
            {
            }
        };

    public:
        //
        //
        //
        /**
        * Note: It can supply bucket and heap pool seperately.
		* 
		* @param heapSize the memory size for heap segment
		* @param bktCfg here u can change the default setting for each bucket
		* @param bktNum the total number of buckets.And it should be little than MAXBUCKETNUM = 7
        */
        CAnyAllocator(unsigned int heapSize, const BucketSetting *bktCfg = 0, unsigned short bktNum = 0);

        /**
        *
        */
        ~CAnyAllocator();

	private:
		// Never let this class be used in complex way ...
		CAnyAllocator(const CAnyAllocator &other);
		void operator =(const CAnyAllocator &other);

    public:
        //
        //
        //
        /**
        *
        */
        bool Alloc(unsigned int *size, unsigned char **ptr);

        /**
        *
        */
        bool Free(unsigned char *ptr, unsigned int size);

    protected:
        //
        //
        //
        /**
        *
        */
        bool Init(unsigned int heapSize, const BucketSetting *bktCfg = 0, unsigned short bktNum = 0);

        /**
        *
        */
        bool Release();

        /**
        *
        */
        bool InitSegments();

        /**
        *
        */
        void InitBucket(unsigned char **memAddr, unsigned short bktIdx, unsigned short *lstMapIdx);

        /**
        *
        */
        void InitHeap(unsigned char *memAddr);

        /**
        *
        */
        bool AllocHeap(unsigned char **ptr, unsigned int *size);

        /**
        *
        */
        bool FreeHeap(unsigned char *ptr, unsigned int size);

	private:
		//
		// 
		//
        /**
        * Memory alignment against bucket segment.
        */
        static unsigned int AllignBucketPtr(unsigned int ptr)
        {
            return (ptr % m_ptrStride) ? (ptr + (m_ptrStride - (ptr % m_ptrStride))) : ptr;
        }

        /**
        * Memory alignment against heap segment.
        */
        static unsigned int AllignHeapPtr(unsigned int ptr, unsigned int size)
        {
            return (ptr % size) ? (ptr + (size - (ptr % size))) : ptr;
        }

    protected:
        // Segment description
        MemoryPool *m_pool;
        SegmentSetting m_config;
        int m_heapSize;

        // Size of memory alignment
        const static short m_ptrStride;
        const static short m_minHeapSize;

		//
		static int m_bucketBlocks[BucketBlock::MAXBUCKETNUM];
		static int m_blockSize[BucketBlock::MAXBUCKETNUM];
    };
}

#endif