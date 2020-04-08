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
#ifndef __ANYINDEX_JTS_QUADTREEBASE_H__
#define __ANYINDEX_JTS_QUADTREEBASE_H__

// Refer to STL definitions like vector etc
#include "anybase\anystl.h"

// Refer to item vector
#include "anyjtsquadtreeimpl.h"

// Forward classes in outside package
namespace AnyGeometry
{
    class CAnyCoordinate;
}

//Spatial index package
namespace AnyIndex
{
 	/*!
	 * \brief
	 * The base class for nodes in a quad tree.
	 */
	class CAnyJTSQuadTreeBase 
	{
	protected:
		//
		// Ctrs & Dctr functions
		//
		/*!
		*
		**/
		CAnyJTSQuadTreeBase();

		/*!
		*
		**/
		virtual ~CAnyJTSQuadTreeBase();

	private:
		//
		//
		//
		/*!
		*
		**/
		CAnyJTSQuadTreeBase(const CAnyJTSQuadTreeBase &other)
		{
		}

		/*!
		*
		**/
		CAnyJTSQuadTreeBase &operator=(const CAnyJTSQuadTreeBase &other)
		{
		}

	public:
        //
        // Dynamics of this quad tree
        //
		/*!
		* \brief
        * Add one item into current item vector of this quad tree node
        * \param item, one geometry object 
		**/
		virtual void Add(CAnyGeometry *item);

		/*!
		 * \brief
         * Removes a single item from this subtree as a template method.
		 *
		 * \param itemEnvelope the envelope containing the item
		 * \param item the item to remove
		 * \return true if the item was found and removed
		 */
        virtual bool Remove(const CAnyEnvelope &itemEnvelope, CAnyGeometry *item);

        //
        // Usages of this quad tree as series of template methods
        //
		/*!
		* \brief
        * Recursively scan the whole nodes from current node to get geometry items
        * \param results, given item vector receiving items scanned
		**/
        virtual void Query(CAnyQuadTreeIndex::ItemVector &results) const;

		/*!
        * \brief
		* Get all items with overlapping function (as condition) not simply scan node items
        * 
        * \param queryEnvelope, given query envelope with which those node items intersect
        * \param results, given an outside container for receiving those qualified geometry items
		**/
        virtual void Query(const CAnyEnvelope &queryEnvelope, CAnyQuadTreeIndex::ItemVector &results)  const;

		/*!
		* \brief
        * Get all items covered by given query envelope and outside spatial decision
        *
        * \param queryEnvelope, suppose rectangular spatial extent to find those items intersect it
        * \param visitor, one undefined outside object for collecting those items accordting to its specification
		**/
        virtual void Query(const CAnyEnvelope &queryEnvelope, CAnyGeometryVisitor &visitor, CAnyQuadTreeIndex::ItemVector &items);

        //
        // Access or characteristic methods of this quard tree
        //
		/*!
		*
		**/
        virtual const CAnyQuadTreeIndex::ItemVector &GetItems() const;

		/*!
		* \brief
        * Get the level of this quad tree
        * \return the tree depth (+1)
		**/
		virtual int GetDepth() const;

		/*!
		* \brief
        * Get all items indexed by this quad tree
        *
        * \return the count of items
		**/
		virtual int GetItemSize() const;

		/*!
		*
		**/
		virtual int GetNodeSize() const;

        //
        // Utility functions
        //
        /*!
        * \brief
        * Given one coordinate as origin point, to decide one rectangle locates which quadrant specified 
        * by this quad tree. 
        *
        * \param curEnvelope, the spatial extent
        * \param centerPt, given this coordinate as origin point
        * \return which quadrant arround current origin point. 
        *  Note:
        * if this input envelope crosses x- or y- axis defined by this origin point, it returns -1
        **/
        static int GetSubnodeIndex(const CAnyEnvelope &curEnvelope, const CAnyCoordinate &centerPt);

	protected:
        //
        // Template methods of this quad tree
        //
		/*!
		*
		**/
        virtual bool IsMatched(const CAnyEnvelope &itemEnvelope)  const;

		/*!
		*
		**/
		virtual bool IsPrunable() const;

		/*!
		*
		**/
		virtual bool IsHasItems() const;

		/*!
		*
		**/
		virtual bool IsHasChildren() const;

        //
        //
        //
		/*!
		*
		**/
        virtual void DoPick(const CAnyEnvelope &queryEnvelope, CAnyGeometryVisitor &visitor, CAnyQuadTreeIndex::ItemVector &items);

	protected:
		// Geometry objects which overlaps current exterior given current node
        CAnyQuadTreeIndex::ItemVector m_items;

		 // subquads are numbered as follows:
 		 //  2 | 3
		 //  --+--
		 //  0 | 1
		CAnyJTSQuadTreeBase *m_subnodes[4];
	};
}
#endif