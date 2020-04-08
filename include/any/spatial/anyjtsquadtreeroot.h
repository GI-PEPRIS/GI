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
#ifndef __ANYINDEX_JTS_QUADTREEROOT_H__
#define __ANYINDEX_JTS_QUADTREEROOT_H__

// Refer to its parent class
#include "anyjtsquadtreebase.h"

// Refer to definitions of basic geometries
#include "anygeom\anycoordinate.h"
#include "anygeom\anyenvelope.h"
using namespace AnyGeometry;

// Spatial index package
namespace AnyIndex
{
    // Forward classes
    class CAnyJTSQuadTreeNode;

	/*!
	 * \brief
	 * CAnyJTSQuadTreeRoot is the root of a single Quadtree.  It is centred at the origin, 
	 * and does not have a defined extent.
     *
	 */
	class CAnyJTSQuadTreeRoot : public CAnyJTSQuadTreeBase 
	{
	public:
		//
		// Ctrs & dctr
		//
		/*!
		*
		**/
		CAnyJTSQuadTreeRoot();

		/*!
		*
		**/
		virtual ~CAnyJTSQuadTreeRoot();

	public:
		//
		// Operations of this quad root
		//
		/*!
		* Insert an item into the quadtree this is the root of.
		*/
		void Insert(const CAnyEnvelope &itemEnvelope, CAnyGeometry *item);

	private:
		/*!
		* \brief
		* insert an item which is known to be contained in the tree rooted at
		* the given QuadNode root.  Lower levels of the tree will be created
		* if necessary to hold the item.
		*/
		void InsertContained(CAnyJTSQuadTreeNode *curNode, const CAnyEnvelope &itemEnvelope, CAnyGeometry *item);

	private:
		// Center of the whole quad tree, given is (0., 0.)
		static CAnyCoordinate m_origin;
	};
}
#endif