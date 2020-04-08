#ifndef __ANYINDEX_INTINDEX_H__
#define __ANYINDEX_INTINDEX_H__

// Refer to node vector definition
#ifndef __ANYINDEX_INTNODE_H__
#include "anyintnode.h"
#endif

/**
*
**/
namespace AnyIndex
{
    /**
    *
    **/
    class CAnyIntIndex
    {
    public:
        //
        //
        //
        /**
        *
        **/
        CAnyIntIndex();

        /**
        *
        **/
        ~CAnyIntIndex();

    public:
        /**
         * Adds an item to the index which is associated with the given interval
         * 
         * @param min the lower bound of the item interval
         * @param max the upper bound of the item interval
         * @param item the item to insert
         * 
         * @throw IllegalStateException if the index has already been queried
         */
        void Insert(double min, double max, void * item);

        /**
         * Search for intervals in the index which intersect the given closed interval
         * and apply the visitor to them.
         * 
         * @param min the lower bound of the query interval
         * @param max the upper bound of the query interval
         * @param visitor the visitor to pass any matched items to
         */
        void Query(double min, double max, void *visitor);

    private:
        //
        //
        //
        /**
        *
        **/
        void Init();

        /**
        *
        **/
        void BuildLevel(CAnyIntNode::NodeVector *src, CAnyIntNode::NodeVector *dest);

        /**
        *
        **/
        const CAnyIntNode *BuildTree();

    private:
        //
        CAnyIntNode::NodeVector *m_leaves;
        //
        const CAnyIntNode *m_root;
        //
        int m_level;
    };
}

#endif