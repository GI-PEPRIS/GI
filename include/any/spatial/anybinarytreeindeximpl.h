/*!
 * The AnyIndex of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages, especially for those quick
 * spatial algorithms.
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
#ifndef __ANYINDEX_BINARYTREEINDEXIMPL_H__
#define __ANYINDEX_BINARYTREEINDEXIMPL_H__

// Refer to item container of one tree node
#include "anybinarytreeindex.h"

// Spatial index  package
namespace AnyIndex
{
	// Forward class

    /*!
    * Being an interface class not never to be directly declared
    **/
    class CAnyBinaryTreeIndexImpl
    {
        // Relatives
        friend class CAnyBinaryTreeIndex;

    protected:
        //
        // Ctrs & dctr and only used by index frame work
        //
        /*!
        *
        **/
        virtual ~CAnyBinaryTreeIndexImpl()
		{
		}

    public:
        //
        // Characters of this quad tree
        //
        /*!
        *
        **/
		virtual int GetDepth() const = 0;

		/*!
		* \return Returns the number of items in the tree
		*/
		virtual int GetItemSize() const = 0;


		/*!
		* \return Returns the number of items in the tree
		*/
		virtual int GetNodeSize() const = 0;

		//
		// Dynamic functions of this quad spatial index
		//
        /*!
        *
        **/
        virtual void Insert(CAnyGeometry *item, const CAnyInterval &interval) = 0;

        /*!
        *
        **/
		virtual void Query(double x, CAnyBinaryTreeIndex::ItemVector &collect) = 0;

        /*!
        *
        **/
		virtual void Query(const CAnyInterval &interval, CAnyBinaryTreeIndex::ItemVector &collect) = 0;

    };
}
#endif
