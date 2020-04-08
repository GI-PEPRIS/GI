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
#ifndef __ANYINDEX_RTREEINDEX_H__
#define __ANYINDEX_RTREEINDEX_H__

// Refer to STL basic definitions
#include "anybase\anystl.h"

// Refer to the definition of geometry item & its boundable
#include "..\anygeom\anygeometry.h"
#include "..\anygeom\anyboundable.h"
using namespace AnyGeometry;

// Forward classes in other namespace
namespace AnyGeometry
{
    class CAnyCoordinate;
	class CAnyGeometryVisitor;
}

// Spatial index  package
namespace AnyIndex
{
    // Forward classes
    class CAnyRTreeIndexImpl;

    /*!
    * Being an envelope class to brige algorithm varities of spatial quad tree
    **/
    class CAnyRTreeIndex
    {
    public:
        // Container definition for geometry items
        typedef std::vector<CAnyGeometry *> ItemVector;
        typedef ItemVector::iterator item_itr;
        typedef ItemVector::const_iterator item_citr;

		//
        typedef std::vector<CAnyBoundable *> BoundableVector;
        typedef BoundableVector::iterator bound_itr;
        typedef BoundableVector::const_iterator bound_citr;

		//
		typedef std::vector<BoundableVector> BoundableVectorVector;
		typedef BoundableVectorVector::iterator bounds_itr;
		typedef BoundableVectorVector::const_iterator bounds_citr;

    protected:
        //
        // Ctrs & dctr and not directly be used except for as a singleton
        //
        /*!
        *
        **/
        CAnyRTreeIndex(CAnyRTreeIndexImpl *oneImpl);

        /*!
        *
        **/
        ~CAnyRTreeIndex();

	private:
		/*!
		* Not to permitted
		**/
		CAnyRTreeIndex(const CAnyRTreeIndex &other)
		{
		}

		/*!
		* Not to permitted
		**/
		const CAnyRTreeIndex &operator=(const CAnyRTreeIndex &other)
		{
		}

    public:
        //
        // Characters of this quad tree
        //
		/*!
		* \return the tree depth
		**/
		int GetDepth() const;

		/*!
		* \return return the number of items in this tree
		*/
		int GetItemSize() const;

        //
        // Dynamic functions of this quad spatial index
        //
		/*!
		* Insert a primitive geometry with its suitable approximations
		**/
		void Insert(const CAnyBoundable *bound, CAnyGeometry *item);

        /*!
        * \brief
        * Removes a single item from the tree.
        *
        * \param itemEnvelope the Envelope of the item to remove
        * \param item the item to remove
        * \return true if the item was found
        */
        bool Remove(const CAnyBoundable *bound, CAnyGeometry *item);

		//
		// Query methods
		//
		/*!
		* \brief
		* The items that are matched are the items in this tree which
		* overlap the search envelope
		*/
		void Query(const CAnyBoundable *bound, CAnyRTreeIndex::ItemVector &matches);

		/*!
		* as above query with filtering rules specified by outside
		*/
		void Query(const CAnyBoundable *bound, CAnyGeometryVisitor &visitor, CAnyRTreeIndex::ItemVector &matches);

    protected:
        //
        // Singleton declaration
        //
        /*!
        *
        **/
        static CAnyRTreeIndex *GetIndex(short type);

        /*!
        *
        **/
        static void DeleteIndex();

    private:
        // One kind of implementation of quad index
        CAnyRTreeIndexImpl *m_impl;
	
		// Singleton
		static CAnyRTreeIndex *m_singleton;
	};
}
#endif
