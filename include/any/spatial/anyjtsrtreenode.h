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
#ifndef __ANYINDEX_JTS_RTREENODE_H__
#define __ANYINDEX_JTS_RTREENODE_H__

// Refer to boundable container
#include "anyrtreeindex.h"

// Refer to its parent
#include "..\anygeom\anyboundable.h"
using namespace AnyGeometry;

// Namespace 
namespace AnyIndex
{
	/*!
	* A node of the STR tree. The children of this node are either more nodes
	* (CAnyJTSRTreeNodes) or real data (ItemBoundables). If this node contains real data
	* (rather than nodes), then we say that this node is a "leaf node".
	*/
	class CAnyJTSRTreeNode : public CAnyBoundable
	{
	public:
		//
		//
		//
		/*!
		* Constructs this object at the given level in the tree
		* @param level 0 if this node is a leaf, 1 if a parent of a leaf, and so on; the
		* root node will have the highest level
		*/
		CAnyJTSRTreeNode(int level, int capacity = 10);

		/*!
		*
		**/
		virtual ~CAnyJTSRTreeNode();

	public:
		//
		// Properties access
		//
		/*!
		* Returns a representation of space that encloses this Boundable,
		* preferably not much bigger than this Boundable's boundary yet fast to
		* test for intersection with the bounds of other Boundables.
		* The class of object returned depends on the subclass of CAnyJTSRTreeImpl.
		*/  
		const CAnyBoundable *GetBoundable() const;

		/*!
		* Returns 0 if this node is a leaf, 1 if a parent of a leaf, and so on; the
		* root node will have the highest level
		*/
		int GetLevel() const;

		//
		//
		//
		/*!
		* Returns either child AbstractNodes, or if this is a leaf node, real data (wrapped
		* in ItemBoundables).
		*/
		const CAnyRTreeIndex::BoundableVector &GetChildBoundables() const;

		/*!
		* Adds either an AbstractNode, or if this is a leaf node, a data object
		* (wrapped in an ItemBoundable)
		*/
		void AddChildBoundable(const CAnyBoundable *bound);

	protected:
		// All chidren boundaries
		CAnyRTreeIndex::BoundableVector m_childBoundables;

		// Which division level
		int m_level;

		// The boundary to cover all children boundaries
		mutable CAnyBoundable *m_boundable;
	};
}
#endif