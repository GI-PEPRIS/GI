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
#ifndef __ANYINDEX_JTS_RTREE_TILEIMPL_H__
#define __ANYINDEX_JTS_RTREE_TILEIMPL_H__

// Refer to its parent
#include "anyjtsrtreeimpl.h"

// Namespace
namespace AnyIndex
{
	/*!
	* \brief
	* A query-only R-tree created using the Sort-Tile-Recursive (STR) algorithm. 
	* For two-dimensional spatial data. 
	*
	* The STR packed R-tree is simple to implement and maximizes space
	* utilization; that is, as many leaves as possible are filled to capacity.
	* Overlap between nodes is far less than in a basic R-tree. However, once the
	* tree has been built (explicitly or on the first call to #query), items may
	* not be added or removed. 
	* 
	* Described in: P. Rigaux, Michel Scholl and Agnes Voisard. Spatial
	* Databases With Application To GIS. Morgan Kaufmann, San Francisco, 2002. 
	*
	*/
	class CAnyJTSRTreeTileImpl : public CAnyJTSRTreeImpl
	{
		/*!
		* Given boundary gemoetry to decide spatial intersect algorithm
		*/
		class STRIntersectsOp: public CAnyJTSRTreeImpl::IntersectsOp 
		{
		public:
			/*!
			*
			**/
			bool Intersects(const void* aBounds, const void* bBounds);
		};

	public:
		//
		//
		//
		/*!
		 * Constructs an CAnyJTSRTreeTileImpl with the given maximum number of child nodes that
		 * a node may have
		 */
		CAnyJTSRTreeTileImpl(int nodeCapacity = 10);

		/*!
		*
		**/
		~CAnyJTSRTreeTileImpl();

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyJTSRTreeNode *CreateNode(int level);

		/*!
		*
		**/
		STRIntersectsOp *GetIntersectsOp() 
		{
			return &m_intersectsOp;
		};

	private:
		/*!
		* Creates the parent level for the given child level. First, orders the items
		* by the x-values of the midpoints, and groups them into vertical slices.
		* For each slice, orders the items by the y-values of the midpoints, and
		* group them into runs of size M (the node capacity). For each run, creates
		* a new (parent) node.
		*/
		virtual void CreateParentBoundables(CAnyRTreeIndex::BoundableVector &children, int newLevel, CAnyRTreeIndex::BoundableVector &parents);

		/*!
		* @param childBoundables Must be sorted by the x-value of
		*        the envelope midpoints
		* @return
		*/
		void VerticalSlices(CAnyRTreeIndex::BoundableVector &childBoundables, int sliceCount, CAnyRTreeIndex::BoundableVectorVector &verticalSlices);

		/*!
		*
		**/
		void CreateParentBoundablesFromVerticalSlices(CAnyRTreeIndex::BoundableVectorVector &verticalSlices, int newLevel, CAnyRTreeIndex::BoundableVector &parents);

		/*!
		*
		**/
		void CreateParentBoundablesFromVerticalSlice(CAnyRTreeIndex::BoundableVector &childBoundables, int newLevel, CAnyRTreeIndex::BoundableVector &parents);

		/*!
		*
		**/
		virtual void SortBoundables(const CAnyRTreeIndex::BoundableVector &input, CAnyRTreeIndex::BoundableVector &output, bool xDirection = true);

		//
		//
		//
		/*!
		*
		**/
		static double Avg(double a, double b);

		/*!
		*
		**/
		static double CentreY(const AnyGeometry::CAnyEnvelope &envelope);
		
		/*!
		*
		**/
		static double CentreX(const AnyGeometry::CAnyEnvelope &envelope);

		/*!
		*
		**/
		static bool yComparator(CAnyBoundable *a, CAnyBoundable *b);

		/*!
		*
		**/
		static bool xComparator(CAnyBoundable *a, CAnyBoundable *b);

	private:
		// 
		STRIntersectsOp m_intersectsOp;
	};
}

#endif