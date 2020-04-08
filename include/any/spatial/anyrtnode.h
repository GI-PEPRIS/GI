#ifndef __ANYINDEX_RTNODE_H__
#define __ANYINDEX_RTNODE_H__

// Refer to its parent
#ifndef __ANYINDEX_BOUNDABLE_H__
#include "anyboundable.h"
#endif

/**
*
**/
namespace AnyIndex
{
    /** 
     * \brief
     * A node of the STR tree.
     * The children of this node are either more nodes (CAnyRtNodes) or real data (CAnyBoundables).
     * If this node contains real data (rather than nodes), then we say that this node is a "leaf node".  
     */
    class CAnyRtNode : public CAnyBoundable
    {
    public:
        //
        //
        //
        /**
        *
        **/
        CAnyRtNode(int level, int capacity = 10);

        /**
        *
        **/
        virtual	~CAnyRtNode();

    public:
        //
        //
        //
        /**
        *
        **/
        BoundVector *GetChildBoundables();

        /**
        *
        **/
        const BoundVector *GetChildBoundables() const;

        /**
         * Returns a representation of space that encloses this Boundable,
         * preferably not much bigger than this Boundable's boundary yet fast to
         * test for intersection with the bounds of other Boundables.
         * The class of object returned depends on the subclass of
         * AbstractSTRtree.
         * 
         * @return an Envelope (for STRtrees), an Interval (for SIRtrees),
         *	or other object (for other subclasses of AbstractSTRtree)
         */  
        const void* GetBounds() const;

        /**
        *
        **/
        void *ComputeBounds() const;

        /**
        *
        **/
        int GetLevel();

        /**
        *
        **/
        void AddChildBoundable(CAnyBoundable *childBoundable);

     private:
        //
        BoundVector *m_childBounds;
        //
        int m_level;
    };
}
#endif