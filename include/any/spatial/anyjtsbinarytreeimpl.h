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
#ifndef __ANYINDEX_JTS_BINARYTREEIMPL_H__
#define __ANYINDEX_JTS_BINARYTREEIMPL_H__

// Refer to STL basics
#include "anybase\anystl.h"

// Refer to its parent
#include "anybinarytreeindeximpl.h"

// Refer to its "handler" implementation
#include "anyjtsbinarytreeroot.h"

//
namespace AnyIndex
{
	// Forward classes
	class CAnyInterval;
	class CAnyBinaryTreeRoot;

    /*!
    * The similar index mechanism as quadtree and expose common query interface of spatial index
    **/
	class CAnyJTSBinaryTreeImpl : public CAnyBinaryTreeIndexImpl
    {
    public:
        //
        //
        //
        /*!
        *
        **/
        CAnyJTSBinaryTreeImpl();

        /*!
        *
        **/
        ~CAnyJTSBinaryTreeImpl();

	private:
		/*!
		* Not permitted
		**/
		CAnyJTSBinaryTreeImpl(const CAnyJTSBinaryTreeImpl &other);

		/*!
		* Not permitted
		**/
		const CAnyJTSBinaryTreeImpl &operator = (const CAnyJTSBinaryTreeImpl &other);

    public:
        //
        // Characteristic methods as a classical tree
        //
        /*!
        *
        **/
        int GetDepth() const;
        
        /*!
        *
        **/
        int GetItemSize() const;
        
        /*!
        *
        **/
        int GetNodeSize() const;
        
		//
		//
		//
        /*!
        *
        **/
        void Insert(CAnyGeometry *item, const CAnyInterval &interval);

        /*!
        *
        **/
		void Query(double x, CAnyBinaryTreeIndex::ItemVector &collect);

        /*!
        *
        **/
        void Query(const CAnyInterval &interval, CAnyBinaryTreeIndex::ItemVector &collect);


    private:
        //
        //
        //
        /*!
		* \brief
        * Collect the min extent of all interval indices
        **/
        void GetMinExtent(const CAnyInterval &interval);

        /*!
        *
        **/
        void ValidateExtent(const CAnyInterval &itemInterval, CAnyInterval &rtInterval, double minExtent);

    private:
		// Indices
		std::vector<CAnyInterval> m_intervals;

		// Root node
		CAnyJTSBinaryTreeRoot m_root;

		// minExtent is the minimum extent of all items
		// inserted into the tree so far. It is used as a heuristic value
		// to construct non-zero extents for features with zero extent.
		// Start with a non-zero extent, in case the first feature inserted has
		// a zero extent in both directions.  This value may be non-optimal, but
		// only one feature will be inserted with this value.
		double m_minExtent;
    };
}
#endif