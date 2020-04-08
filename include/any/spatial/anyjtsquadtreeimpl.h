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
#ifndef __ANYINDEX_JTS_QUADTREEIMPL_H__
#define __ANYINDEX_JTS_QUADTREEIMPL_H__

// Refer to STL definitions
#include "any/base/anystl.h"

// Refer to its parent interface
#include "anyquadtreeindeximpl.h"

// Refer to decalaration of item container such as a vector
#include "anyquadtreeindex.h"

// Spatial index package
namespace AnyIndex
{
    // Forward classes
    class CAnyJTSQuadTreeRoot;

	/*!
	*
	**/
    class CAnyJTSQuadTreeImpl : public CAnyQuadTreeIndexImpl
	{
	public:
		//
		// Ctrs & dctr
		//
		/*!
		*
		**/
		CAnyJTSQuadTreeImpl();

		/*!
		*
		**/
		~CAnyJTSQuadTreeImpl();

	private:
		//
		// Not to permitted to implicitly created
		//
		/*!
		*
		**/
		CAnyJTSQuadTreeImpl(const CAnyJTSQuadTreeImpl &other)
		{
		}

		/*!
		*
		**/
		const CAnyJTSQuadTreeImpl &operator=(const CAnyJTSQuadTreeImpl &other)
		{
		}

	public:
        //
        // Characteristic functions of this quad tree index
        //
		/*!
		* \return 
		* Returns the number of levels in the tree
		*/
		int GetDepth() const;

		/*!
		* \return 
		* Returns the number of items in the tree
		*/
		int GetItemSize() const;
	
        //
        // Dynamic functions of this quad spatial index
        //
		/*!
		*
		**/
        void Insert(const CAnyBoundable &bound, CAnyGeometry *item);

        /*!
        * \brief
        * Removes a single item from the tree.
        *
        * \param itemEnvelope the Envelope of the item to remove
        * \param item the item to remove
        * \return true if the item was found
        */
        bool Remove(const CAnyBoundable &bound, CAnyGeometry *item);

		//
		//
		//
		/*!
		*
		*/
        void Query(const CAnyBoundable &bound, CAnyQuadTreeIndex::ItemVector &items);

		/*!
		 * the items that are matched are the items in quads which
		 * overlap the search envelope
		 */
        void Query(const CAnyBoundable &bound, CAnyGeometryVisitor &visitor, CAnyQuadTreeIndex::ItemVector &items);

		/*!
        * \brief
		* Return a list of all items in the Quad tree index
		**/
        void Query(CAnyQuadTreeIndex::ItemVector &items);

	private:
		//
		//
		//
		/*!
		 *  \brief
		 * m_minExtent is the minimum envelope extent of all items
		 * inserted into the tree so far. It is used as a heuristic value
		 * to construct non-zero envelopes for features with zero X and/or
		 * Y extent.
		 * Start with a non-zero extent, in case the first feature inserted has
		 * a zero extent in both directions.  This value may be non-optimal, but
		 * only one feature will be inserted with this value.
		 */
        static void GetMinExtent(const CAnyEnvelope &curEnvelope);

		/**
		 * \brief
		 * Ensure that the envelope for the inserted item has non-zero extents.
		 *
		 * Use the current minExtent to pad the envelope, if necessary.
		 * Can return a new Envelope or the given one (casted to non-const).
		 */
        static void ValidateExtent(const CAnyEnvelope &itemEnv, CAnyEnvelope &ensuredEnvelope, double minExtent);

	private:
		// Container of spatial extent of those geometry objects
        //CAnyQuadTreeIndex::BoundableVector m_envelopes;

		// BRIDGE WAY: Every thing from the root of this tree index
		CAnyJTSQuadTreeRoot *m_root;

		// The spatial limit of one node of this quad tree
		static double m_minExtent;
	};
}
#endif
