/**
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
 * smartpoint@sohu.com
 */
#ifndef __ANYSPATIALINDEX_JTSQUADTREE_H__
#define __ANYSPATIALINDEX_JTSQUADTREE_H__

// Refer to STL definitions like vector etc
#include "anybase\anystl.h"

// Refer to item vector
#include "anyjtsquadimpl.h"

// Forward classes in outside package
namespace AnyGeometry
{
    class CAnyCoordinate;
    class CAnyEnvelope;
}

//Spatial index package
namespace AnySpatialIndex
{
 	/*!
	 * \brief
	 * The base class for nodes in a quad tree.
	 */
	class CAnyJtsQuadTree 
	{
	protected:
		//
		// Ctrs & Dctr functions
		//
		/*!
		*
		**/
		CAnyJtsQuadTree();

		/*!
		*
		**/
		virtual ~CAnyJtsQuadTree();

	public:
        //
        // Dynamics of this quad tree
        //
		/*!
		* \brief
        * Add one item into current item vector of this quad tree node
        * \param item, one geometry object 
		**/
		virtual void Add(void* item);

		/*!
		 * \brief
         * Removes a single item from this subtree.
		 *
		 * \param itemEnvelope the envelope containing the item
		 * \param item the item to remove
		 * \return true if the item was found and removed
		 */
        virtual bool Remove(const AnyGeometry::CAnyEnvelope &itemEnvelope, void *item);

        //
        // Usages of this quad tree
        //
		/*!
		* \brief
        * Recursively scan the whole nodes from current node to get geometry items
        * \param results, given item vector receiving items scanned
		**/
        virtual void Query(CAnyQuadIndex::ItemVector &results) const;

		/*!
        * \brief
		* Get all items with overlapping function (as condition) not simply scan node items
        * 
        * \param queryEnvelope, given query envelope with which those node items intersect
        * \param results, given an outside container for receiving those qualified geometry items
		**/
        virtual void Query(const AnyGeometry::CAnyEnvelope &queryEnvelope, CAnyQuadIndex::ItemVector &results)  const;

		/*!
		* \brief
        * Get all items covered by given query envelope and outside spatial decision
        *
        * \param queryEnvelope, suppose rectangular spatial extent to find those items intersect it
        * \param visitor, one undefined outside object for collecting those items accordting to its specification
		**/
        virtual void Query(const AnyGeometry::CAnyEnvelope &queryEnvelope, void *visitor);

        //
        // Access methods of this quard tree
        //
		/*!
		*
		**/
        virtual const CAnyQuadIndex::ItemVector &GetItems() const;

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
		virtual int GetSize() const;

		/*!
		*
		**/
		virtual int GetNodeCount() const;

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
        static int GetSubnodeIndex(const AnyGeometry::CAnyEnvelope &curEnvelope, const AnyGeometry::CAnyCoordinate &centerPt);

	private:
        //
        // Characters of current quad tree
        //
		/*!
		*
		**/
        virtual bool IsMatched(const AnyGeometry::CAnyEnvelope &itemEnvelope)  const;

		/*!
		*
		**/
		bool IsPrunable() const;

		/*!
		*
		**/
		bool IsHasItems() const;

		/*!
		*
		**/
		bool IsHasChildren() const;

        //
        //
        //
		/*!
		*
		**/
        virtual void DoVisitItems(const AnyGeometry::CAnyEnvelope &queryEnvelope, void *visitor = 0);

	protected:
		// Geometry objects which overlaps current exterior given current node
        CAnyQuadIndex::ItemVector m_items;

		 // subquads are numbered as follows:
 		 //  2 | 3
		 //  --+--
		 //  0 | 1
		CAnyJtsQuadTree *m_subnodes[4];
	};
}
#endif