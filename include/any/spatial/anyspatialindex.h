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
#ifndef __ANYINDEX_SPATIALINDEX_H__
#define __ANYINDEX_SPATIALINDEX_H__

//
namespace AnyIndex
{
	/*!
	* \brief
	* This abstract class defines basic insertion and query operations supported by
	* classes implementing spatial index algorithms.
	* 
	* A spatial index typically provides a primary filter for range rectangle queries. A
	* secondary filter is required to test for exact intersection. Of course, this
	* secondary filter may consist of other tests besides intersection, such as
	* testing other kinds of spatial relationships.
	*/
	class CAnySpatialIndex 
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		virtual ~CAnySpatialIndex()
		{
		}

	public:
		/*!
		* \brief
		* Adds a spatial item with an extent specified by the given Envelope
		* to the index
		*/
		virtual void Insert(const CAnyBoundable &bound, CAnyGeometry *item) = 0;

		/*!
		* \brief
		* Queries the index for all items whose extents intersect the given search Envelope
		*
		* Note that some kinds of indexes may also return objects which do not in fact
		* intersect the query envelope.
		*
		* @param searchEnv the envelope to query for
		* @return a list of the items found by the query in a newly allocated vector
		*/
		virtual void Query(const CAnyBoundable &bound, CAnyQuadTreeIndex::ItemVector &items) = 0;

		/*!
		* \brief
		* Queries the index for all items whose extents intersect the given search Envelope
		* and applies an ItemVisitor to them.
		*
		* Note that some kinds of indexes may also return objects which do not in fact
		* intersect the query envelope.
		*
		* @param searchEnv the envelope to query for
		* @param visitor a visitor object to apply to the items found
		*/
		void Query(const CAnyBoundable &bound, CAnyGeometryVisitor &visitor, CAnyQuadTreeIndex::ItemVector &items) = 0;

		/*!
		* \brief
		* Removes a single item from the tree.
		*
		* @param itemEnv the Envelope of the item to remove
		* @param item the item to remove
		* @return <code>true</code> if the item was found
		*/
        virtual bool Remove(const CAnyBoundable &bound, CAnyGeometry *item) = 0;
	};
}

#endif