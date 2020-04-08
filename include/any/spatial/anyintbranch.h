#ifndef __ANYINDEX_INTBRANCH_H__
#define __ANYINDEX_INTBRANCH_H__

// Refer to parent class
#ifndef __ANYINDEX_INTNODE_H__
#include "anyintnode.h"
#endif

namespace AnyIndex
{
    /**
    *
    **/
    class CAnyIntBranch : public CAnyIntNode
    {
    public:
        //
        //
        //
        /**
        *
        **/
        CAnyIntBranch(const CAnyIntNode *first, const CAnyIntNode *second);

        /**
        *
        **/
        ~CAnyIntBranch();

    public:
        //
        //
        //
        /**
        *
        **/
        void Query(double queryMin, double queryMax, void *visitor) const;

    private:
        //
        const CAnyIntNode *m_firstNode;
        //
        const CAnyIntNode *m_secondNode;
    };
}
#endif