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
#ifndef __ANYINDEX_QUADTREEINDEXIMPL_H__
#define __ANYINDEX_QUADTREEINDEXIMPL_H__

// Refer to item container of one tree node
#include "anyquadtreeindex.h"

// Spatial index  package
namespace AnyIndex
{
	// Forward class

    /*!
    * Being an interface class not never to be directly declared
    **/
    class CAnyQuadTreeIndexImpl
    {
        // Relatives
        friend class CAnyQuadTreeIndex;

    protected:
        //
        // Ctrs & dctr and only used by index frame work
        //
        /*!
        *
        **/
        virtual ~CAnyQuadTreeIndexImpl();

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

		//
		// Dynamic functions of this quad spatial index
		//
		/*!
		*
		**/
        virtual void Insert(const AnyGeometry::CAnyBoundable &bound, CAnyGeometry *item) = 0;

        /*!
        * \brief
        * Removes a single item from the tree.
        *
        * \param itemEnvelope the Envelope of the item to remove
        * \param item the item to remove
        * \return true if the item was found
        */
        virtual bool Remove(const AnyGeometry::CAnyBoundable &bound, CAnyGeometry *item) = 0;

		//
		// Query interface
		//
		/*!
		*
		*/
		virtual void Query(const AnyGeometry::CAnyBoundable &bound, CAnyQuadTreeIndex::ItemVector &items) = 0;

		/*!
		* the items that are matched are the items in quads which
		* overlap the search envelope
		*/
		virtual void Query(const AnyGeometry::CAnyBoundable &bound, CAnyGeometryVisitor &visitor, CAnyQuadTreeIndex::ItemVector &items) = 0;

		/*!
		* \brief
		* Return a list of all items in the Quad tree index
		**/
		virtual void Query(CAnyQuadTreeIndex::ItemVector &items) = 0;
    };
}
#endif
