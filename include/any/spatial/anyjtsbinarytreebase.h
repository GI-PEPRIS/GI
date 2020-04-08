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
#ifndef __ANYINDEX_JTS_BINARYTREEBASE_H__
#define __ANYINDEX_JTS_BINARYTREEBASE_H__

// Refer to STL basics
#include "anybase\anystl.h"

// Refer to item collector
#include "anybinarytreeindex.h"

// Forward class
namespace AnyGeometry
{
	class CAnyGeometry;
}

// Spatial Index Package
namespace AnyIndex
{
	// Forward classes
	class CAnyInterval;

    /*!
    * \breif
	* Common behaviors belonging to root and other nodes of a binary tree
    **/
    class CAnyJTSBinaryTreeBase
    {
    public:
        //
        //
        //
        /*!
        *
        **/
        CAnyJTSBinaryTreeBase();

        /*!
        *
        **/
        virtual ~CAnyJTSBinaryTreeBase();

	private:
		//
		//
		//
		/*!
		* Not permitted
		**/
		CAnyJTSBinaryTreeBase(const CAnyJTSBinaryTreeBase &other)
		{
		}

		/*!
		* Not permitted
		**/
		const CAnyJTSBinaryTreeBase &operator = (const CAnyJTSBinaryTreeBase &other)
		{
		}

    public:
        //
        //
        //
        /*!
        *
        **/
        virtual void Add(CAnyGeometry* item);

		//
		// Characteristic methods
		//
        /*!
        * Items belonging to current node
        **/
		virtual const CAnyBinaryTreeIndex::ItemVector &GetCurrentItems() const;

        /*!
        *
        **/
        virtual void GetAllItems(CAnyBinaryTreeIndex::ItemVector &collect);

        /*!
        *
        **/
		virtual void GetAllItems(const CAnyInterval &interval, CAnyBinaryTreeIndex::ItemVector &collect);

		//
		//
		//
        /*!
        * The number of descedent nodes
        **/
        virtual int GetDepth() const;

        /*!
        * Get the item number belonging to this node and its descedent nodes
        **/
        virtual int GetItemSize() const;

        /*!
        *
        **/
        virtual int GetNodeSize() const;


    protected:
        //
        //
        //
        /*!
        *
        **/
        virtual bool IsSearchMatch(const CAnyInterval &interval) = 0;

		//
		// Common methods for its descedents
		//
		/*!
		*
		**/
        static int GetSubnodeIndex(const CAnyInterval &curInterval, double center);

    protected:
        // Tree container and not restrict its pointer types for future broad usages
		CAnyBinaryTreeIndex::ItemVector m_items;

        // Subnodes are numbered as follows:
        //  0 | 1
        CAnyJTSBinaryTreeBase *m_subNodes[2];
    };
}
#endif