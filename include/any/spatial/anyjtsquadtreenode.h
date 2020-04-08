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
#ifndef __ANYINDEX_JTS_QUADTREENODE_H__
#define __ANYINDEX_JTS_QUADTREENODE_H__

// Refer to its parent
#include "anyjtsquadtreebase.h"
using namespace AnyIndex;

// Directly refer to definitions of outside classes
#include "anygeom\anycoordinate.h"
#include "anygeom\anyenvelope.h"
using namespace AnyGeometry;

// Spatial index package
namespace AnyIndex
{
	/*!
	 * \brief
	 * Represents a node of a Quadtree.
	 *
	 * Nodes contain items which have a spatial extent corresponding to
	 * the node's position in the quadtree.
	 *
	 */
	class CAnyJTSQuadTreeNode : public CAnyJTSQuadTreeBase 
	{
	public:
		//
		// Ctrs & dctr
		//
		/*!
        * \brief
		* Given a spaital extent to construct this quad node
		**/
		CAnyJTSQuadTreeNode(double minx, double maxx, double miny, double maxy, int level);

		/*!
        * \brief
		* Given a spaital extent to construct this quad node
		**/
        CAnyJTSQuadTreeNode(const CAnyEnvelope &curEnvelope, int level);

		/*!
		*
		**/
		virtual ~CAnyJTSQuadTreeNode();

	public:
		//
		// Access functions
		//
		/*!
		* \brief
        * Get the minimum spatial extent for this quad node
        *
        * \return return spatial extent for this quad node
		**/
        const CAnyEnvelope &GetEnvelope() const;

        //
        // Dynamics of this quad node
        //
        /*!
        * \brief
        * Returns the subquad containing the envelope. Creates the subquad if it does not already exist.
        */
        CAnyJTSQuadTreeNode *GetNode(const CAnyEnvelope &queryEnvelope);

        /*! 
        * \brief
        * Returns the smallest existing node containing the envelope
        *
        * Note:
        * This funcion plays almost the same role with GetNode() function 
        * except for not to create new inner node
        *
        * \param queryEnvelope, given spatial extent to find a node
        * \return the smallest existing node for given query envelope
        */
        CAnyJTSQuadTreeNode *FindNode(const CAnyEnvelope &queryEnvelope);

		/*!
		* \breif
        * Insert one quad node as its children even grandchildern of this quad tree
        *
        * \para subNode, one quad node may be inserted into current quad tree
		**/
		void InsertNode(CAnyJTSQuadTreeNode *subNode);

		//
		// Utility functions
		//
		/*!
		*
		**/
        static CAnyJTSQuadTreeNode *CreateNode(const CAnyEnvelope &envelope);

		/**
		*
		**/
        static CAnyJTSQuadTreeNode *CreateExpanded(const CAnyJTSQuadTreeNode *curNode, const CAnyEnvelope &expandedEnvelpoe);

	protected:
		//
		//
		//
		/*!
		*
		**/
        virtual bool IsMatched(const CAnyEnvelope &queryEnvelope);

	private:
		//
		//
		//
		/**
		*
		**/
		CAnyJTSQuadTreeNode *DoGetSubnode(int index);

		/**
		*
		**/
		CAnyJTSQuadTreeNode *DoCreateSubnode(int index);

	private:
		// Spatial extent of this quad node
        CAnyEnvelope m_envelope;
		// Spatial center of this quad node
        AnyGeometry::CAnyCoordinate m_center;
		// Depth of this quad node
		int m_level;
	};
}

#endif