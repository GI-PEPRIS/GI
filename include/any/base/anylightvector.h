/*!
 * The AnyBase package of PetroCOVERY Solution is a collection of native C++ classes that 
 * implement the fundamental algorithms & operations required to 
 * satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_LIGHT_VECTOR_H__
#define __ANYBASE_LIGHT_VECTOR_H__

// export & import macroes
#include "anybase.h"

// Declare UeBase namespace
namespace AnyBase
{

	/*!
	* Self-defined implemenation of one arrary which is based on one continuous memory block.
	*
	*/
    class ANYBASE_CLASS CAnyLightVector
    {
    public:
        //
        // Default constructor and deconstructor
        // 
        /*!
        * Note: here smart pointer maybe reasonable when need to decide when to release memory
        */
	    CAnyLightVector(int blockSize, int increment = 100, bool isReleased = true);

        /*!
        *
        */
        CAnyLightVector(const CAnyLightVector &other, bool isRelease = true);

        /*!
        *
        */
	    virtual ~CAnyLightVector();

    public:
        //
        // Methods about vector generation
        //
        /*!
        * Not only does it can initialize relative variables when firstly used, but also it clean the 
        * the old memory up for the following usage.
        *
        * @param blockSize the size of one block in continuous memory
        * @param increment the incremented size when reallocating this continuous memory
        */
        void Init(int blockSize, int increment = 100);

        /*!
        *
        */
        void *Add(void *oneBlock);

        /*!
        *
        */
        void *Add(const void *oneBlock, long pos);

        /*!
        *
        */
        short Remove(long pos);

        /*!
        *
        */
        short Remove(long startPos, long endPos);

        /*!
        *
        */
        void RemoveAll(bool isReleae = true);
        
        /*!
        *
        */

        //
        // Access or senior visiting interfaces
        //
        /*!
        *
        */
        long GetCount() const;

        /*!
        *
        */
        void *GetData(long curBlock) const;

        /*!
        *
        */
        void *GetHead() const;

        /*!
        *
        */
        int GetBlockSize() const;

        /*!
        *
        */
	    void QuickSort(int (* SortFunc)(const void *firstBlock, const void *secondBlock)); 

        /*!
        *
        */
    	void *BinaryFind(const void *key, int (__cdecl *CompareFunc)(const void *firstBlock, const void *secondBlock));

        //
        // Overloading operators
        //
        /*!
        * Deprecated function
        */
        const CAnyLightVector& operator = (const CAnyLightVector &other);

        /*!
        * Deprecated function since we directly use suffix to position one element after getting one 
        * continuous memory
        */
        void *operator[](long pos) const;

		//
		//
		//
		/*!
		*
		**/
		static bool MakeBufferLine(double bufferWidth, short leftRight, const CAnyLightVector &lineCoords, CAnyLightVector &bufCoords);

    private:
        /*!
        *
        */
        void *Alloc();

    private:
        // Whether automatically to release memory
        bool m_isRelease;
        // The size of one continuous memory unit
        int m_blockSize;
        // The number of units in continuous way
        long m_blocks;
        // The position indicating which unit
        long m_lastBlock;
        // The size of units needed to be allocated
        int m_increment;
        // The heading address
        void *m_head;
    };
}

#endif