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
#ifndef __ANYINDEX_BINARYTREENODE_H__
#define __ANYINDEX_BINARYTREENODE_H__

// Refer to its parent which has common implementation for kinds of nodes
#include "anybinarytreebase.h"

// Refer to its corresponding index
#include "anyinterval.h"

//
namespace AnyIndex
{
    /*!
    * Inner and leaf nodes of current binary tree except root node
    **/
    class CAnyBinaryTreeNode : public CAnyBinaryTreeBase
    {
    public:
        //
        //
        //
        /*!
        *
        **/
        CAnyBinaryTreeNode(const CAnyInterval &curInterval, int level);

        /*!
        *
        **/
        virtual ~CAnyBinaryTreeNode();

	private:
        /*!
		* Not permitted
        **/
        CAnyBinaryTreeNode(const CAnyInterval &curInterval)
		{
		}

		/*!
		* Not permitted
		**/
		const CAnyBinaryTreeNode &operator = (const CAnyBinaryTreeNode &other)
		{
		}

    public:
        //
        // Basic interface for set and access methods
        //
        /*!
        *
        **/
        void Insert(const CAnyBinaryTreeNode *oneNode);

        /*!
        *
        **/
        const CAnyInterval &GetInterval() const;

		//
		// Query Inerface
		//
        /*!
        * Here will build a path until find the leaf node
        **/
        CAnyBinaryTreeBase *GetNode(const CAnyInterval &queryInterval);

        /*!
        * Here not do anything except for the suitable node
        **/
        CAnyBinaryTreeBase *Find(const CAnyInterval &queryInterval);

        //
        //
        //
        /*!
        *
        **/
        static CAnyBinaryTreeNode *CreateNode(const CAnyInterval &oneInterval);

        /*!
        *
        **/
        static CAnyBinaryTreeNode *CreateExpanded(CAnyBinaryTreeNode *node, const CAnyInterval &addInterval);

    protected:
        //
        //
        //
        /*!
        *
        **/
        bool IsSearchMatch(const CAnyInterval &curInterval);

    private:
        //
        //
        //
        /*!
        *
        **/
        CAnyBinaryTreeNode *GetSubnode(int index);

        /*!
        *
        **/
        CAnyBinaryTreeNode *CreateSubnode(int index);

    private:
        // Corresponding interval
	    CAnyInterval m_interval;

        //
	    double m_center;

        //
	    int m_level;
    };
}

#endif
