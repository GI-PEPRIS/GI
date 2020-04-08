#ifndef __ANYINDEX_INTLEAF_H__
#define __ANYINDEX_INTLEAF_H__

// Refer to its parent
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
    class CAnyIntLeaf : public CAnyIntNode
    {
    public:
        //
        //
        //
        /**
        *
        **/
        CAnyIntLeaf(double min, double max, void *item);

        /**
        *
        **/
        ~CAnyIntLeaf();

    public:
        //
        //
        //
        /**
        *
        **/
        void Query( double queryMin, double queryMax, void *visitor) const;

    private:
        //
        void *m_item;
    };
}
#endif