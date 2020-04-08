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
#ifndef __ANYINDEX_JTS_RTREEINDEXIMPL_H__
#define __ANYINDEX_JTS_RTREEINDEXIMPL_H__

// Refer to item container of one tree node
#include "anyrtreeindex.h"

// Refer to its parent
#include "anyrtreeindeximpl.h"

// Spatial index  package
namespace AnyIndex
{
	// Forward class
	class CAnyJTSRTreeNode;

    /*!
    * Being an interface class not never to be directly declared
    **/
	class CAnyJTSRTreeImpl : public CAnyRTreeIndexImpl
    {
		// Subject to which objects to create 
		friend class CAnyRTreeIndex;

		// Nodes of current r-tree
		typedef std::vector<CAnyJTSRTreeNode *> NodeVector;

    protected:
		/*!
		* \brief
		 * A test for intersection between two bounds, necessary because
		 * subclasses of AbstractSTRtree have different implementations of
		 * bounds. 
		 */
		class IntersectsOp 
		{
			public:
				/*!
				* For STRtrees, the bounds will be Envelopes; for
				* SIRtrees, Intervals; for other subclasses of
				* AbstractSTRtree, some other class.
				* @param aBounds the bounds of one spatial object
				* @param bBounds the bounds of another spatial object
				* @return whether the two bounds intersect
				*/
				virtual bool Intersects(const void* aBounds, const void* bBounds) = 0;

				/*!
				*
				**/
				virtual ~IntersectsOp() 
				{
				}
		};

	protected:
        //
        // Ctrs & dctr and only used by index frame work
        //
		/*!
		* Constructs an AbstractSTRtree with the specified maximum number of child
		* nodes that a node may have
		*/
		CAnyJTSRTreeImpl(short newNodeCapacity);

        /*!
        *
        **/
        virtual ~CAnyJTSRTreeImpl();

    public:
        //
        // Characters of this quad tree
        //
        /*!
        *
        **/
		virtual int GetDepth();

		/*!
		* \return Returns the number of items in the tree
		*/
		virtual int GetItemSize();

		/*!
		*
		**/
		virtual int GetNodeCapacity();

		//
		// Dynamic functions of this quad spatial index
		//
		/*!
		*
		**/
		virtual void Insert(const AnyGeometry::CAnyBoundable *bound, CAnyGeometry *item);

       /*!
        * \brief
        * Removes a single item from the tree.
        *
        * \param itemEnvelope the Envelope of the item to remove
        * \param item the item to remove
        * \return true if the item was found
        */
        virtual bool Remove(const AnyGeometry::CAnyBoundable *bound, CAnyGeometry *item);

		/*!
		*
		*/
		virtual void Query(const AnyGeometry::CAnyBoundable *bound, CAnyRTreeIndex::ItemVector &matches);

		/*!
		* the items that are matched are the items in quads which
		* overlap the search envelope
		*/
		virtual void Query(const AnyGeometry::CAnyBoundable *bound, CAnyGeometryVisitor &visitor, CAnyRTreeIndex::ItemVector &matches);

		//
		//
		//
		/*!
		*
		**/
		virtual CAnyJTSRTreeNode *GetRoot() 
		{
			return m_root;
		}

		//
		//
		//
		/*!
		* @return a test for intersection between two bounds,
		* necessary because subclasses
		* of AbstractSTRtree have different implementations of bounds.
		* @see IntersectsOp
		*/
		virtual IntersectsOp *GetIntersectsOp() = 0;

		//
		//
		//
		/*!
		*
		**/
		static bool CompareDoubles(double a, double b) 
		{
			return a < b;
		}

	protected:
		//
		// 
		//
		/*!
		*
		**/
		virtual void Build();

		/*!
		* Ownership to caller (TODO: return by auto_ptr)
		**/
		virtual CAnyJTSRTreeNode *CreateNode(int level) = 0;

		/*!
		* Creates the levels higher than the given level
		* 
		* @param boundablesOfALevel the level to build on
		* @param level the level of the Boundables, or -1 if the boundables are item
		*            boundables (that is, below level 0)
		* @return the root, which may be a ParentNode or a LeafNode
		*/
		virtual CAnyJTSRTreeNode *CreateHigherLevels(CAnyRTreeIndex::BoundableVector &boundablesOfALevel, int level);

		/*!
		* Sorts the childBoundables then divides them into groups of size M, where
		* M is the node capacity.
		*/
		virtual void CreateParentBoundables(CAnyRTreeIndex::BoundableVector &children, int newLevel, CAnyRTreeIndex::BoundableVector &parents);

		/*!
		*
		**/
		virtual void SortBoundables(const CAnyRTreeIndex::BoundableVector &input, CAnyRTreeIndex::BoundableVector &output, bool xDirection = true) = 0;

		/*!
		*
		**/
		virtual CAnyJTSRTreeNode *LastNode(CAnyRTreeIndex::BoundableVector &nodes);

	private:
		//
		//
		//
		/*!
		*
		**/
		int GetDepth(CAnyJTSRTreeNode *node);

		/*!
		*
		**/
		int GetItemSize(CAnyJTSRTreeNode *node);

		//
		//
		//
		/*!
		*
		**/
		bool Remove(const CAnyBoundable *bound, CAnyJTSRTreeNode *node, CAnyGeometry *item);

		/*!
		*
		**/
		bool RemoveItem(CAnyJTSRTreeNode *node, CAnyGeometry *item);

		/*!
		*
		**/
		void ItemsTree(CAnyJTSRTreeNode *node, CAnyRTreeIndex::ItemVector &vector);

		/*!
		*
		**/
		void Query(const CAnyBoundable *bound, const CAnyJTSRTreeNode *node, CAnyRTreeIndex::ItemVector &matches);

		/*!
		*
		**/
		void Query(const CAnyBoundable *bound, const CAnyJTSRTreeNode *node, CAnyGeometryVisitor &visitor, CAnyRTreeIndex::ItemVector &matches);


	protected:
		// Is built for indexing
		bool m_isBuilt;

		// Boundables of items
		CAnyRTreeIndex::BoundableVector m_itemBoundables;

		// Delegation point
		CAnyJTSRTreeNode *m_root;

		// All nodes of current r-tree
		NodeVector m_nodes;

		// Should be size_t, probably
		short m_nodeCapacity;
    };
}
#endif
