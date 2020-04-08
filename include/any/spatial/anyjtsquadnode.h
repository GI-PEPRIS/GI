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
#ifndef __ANYSPATIALINDEX_JTSQUADNODE_H__
#define __ANYSPATIALINDEX_JTSQUADNODE_H__

// Refer to its parent
#include "anyjtsquadtree.h"

// Directly refer to definitions of outside classes
#include "anygeom\anyenvelope.h"
#include "anygeom\anycoordinate.h"
using namespace AnyGeometry;

// Spatial index package
namespace AnySpatialIndex
{
	/*!
	 * \brief
	 * Represents a node of a Quadtree.
	 *
	 * Nodes contain items which have a spatial extent corresponding to
	 * the node's position in the quadtree.
	 *
	 */
	class CAnyJtsQuadNode : public CAnyJtsQuadTree 
	{
	public:
		//
		// Ctrs & dctr
		//
		/*!
        * \brief
		* Given a spaital extent to construct this quad node
		**/
		CAnyJtsQuadNode(double minx, double maxx, double miny, double maxy, int level);

		/*!
        * \brief
		* Given a spaital extent to construct this quad node
		**/
        CAnyJtsQuadNode(const AnyGeometry::CAnyEnvelope &curEnvelope, int level);

		/*!
		*
		**/
		virtual ~CAnyJtsQuadNode();

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
        const AnyGeometry::CAnyEnvelope &GetEnvelope() const;

        //
        // Dynamics of this quad node
        //
        /*!
        * \brief
        * Returns the subquad containing the envelope. Creates the subquad if it does not already exist.
        */
        CAnyJtsQuadNode *GetNode(const AnyGeometry::CAnyEnvelope &queryEnvelope);

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
        CAnyJtsQuadNode *FindNode(const AnyGeometry::CAnyEnvelope &queryEnvelope);

		/*!
		* \breif
        * Insert one quad node as its children even grandchildern of this quad tree
        *
        * \para subNode, one quad node may be inserted into current quad tree
		**/
		void InsertNode(CAnyJtsQuadNode *subNode);

		//
		// Utility functions
		//
		/*!
		*
		**/
        static CAnyJtsQuadNode *CreateNode(const AnyGeometry::CAnyEnvelope &envelope);

		/**
		*
		**/
        static CAnyJtsQuadNode *CreateExpanded(const CAnyJtsQuadNode *curNode, const AnyGeometry::CAnyEnvelope &expandedEnvelpoe);

	protected:
		//
		//
		//
		/*!
		*
		**/
        virtual bool IsMatched(const AnyGeometry::CAnyEnvelope &queryEnvelope);

	private:
		//
		//
		//
		/**
		*
		**/
		CAnyJtsQuadNode *DoGetSubnode(int index);

		/**
		*
		**/
		CAnyJtsQuadNode *DoCreateSubnode(int index);

	private:
		// Spatial extent of this quad node
        AnyGeometry::CAnyEnvelope m_envelope;
		// Spatial center of this quad node
        AnyGeometry::CAnyCoordinate m_center;
		// Depth of this quad node
		int m_level;
	};
}

#endif