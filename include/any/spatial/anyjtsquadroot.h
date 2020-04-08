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
#ifndef __ANYSPATIALINDEX_JTSQUADROOT_H__
#define __ANYSPATIALINDEX_JTSQUADROOT_H__

// Refer to its parent class
#include "anyjtsquadtree.h"

// Refer to definitions of basic geometries
#include "anygeom\anycoordinate.h"
#include "anygeom\anyenvelope.h"
using namespace AnyGeometry;

// Spatial index package
namespace AnySpatialIndex
{
    // Forward classes
    class CAnyJtsQuadNode;

	/*!
	 * \brief
	 * CAnyJtsQuadRoot is the root of a single Quadtree.  It is centred at the origin, and does not have a defined extent.
     *
	 */
	class CAnyJtsQuadRoot : public CAnyJtsQuadTree 
	{
	public:
		//
		// Ctrs & dctr
		//
		/*!
		*
		**/
		CAnyJtsQuadRoot();

		/*!
		*
		**/
		virtual ~CAnyJtsQuadRoot();

	public:
		//
		// Operations of this quad root
		//
		/**
		 * Insert an item into the quadtree this is the root of.
		 */
        void Insert(const AnyGeometry::CAnyEnvelope &itemEnvelope, void *item);

	private:
		/**
		 * insert an item which is known to be contained in the tree rooted at
		 * the given QuadNode root.  Lower levels of the tree will be created
		 * if necessary to hold the item.
		 */
        void InsertContained(CAnyJtsQuadNode *curNode, const AnyGeometry::CAnyEnvelope &itemEnvelope, void *item);

	private:
		// Center of the whole quad tree, given is (0., 0.)
		static CAnyCoordinate m_origin;
	};
}
#endif