#ifndef __ANYINDEX_RTSIR_H__
#define __ANYINDEX_RTSIR_H__

// Refer to parent class
#ifndef __ANYINDEX_RTTREE_H__
#include "anyrttree.h"
#endif

// Refer to parent class
#ifndef __ANYINDEX_RTNODE_H__
#include "anyrtnode.h"
#endif

/**
*
**/
namespace AnyIndex
{
    /** 
    * \brief
     * One-dimensional version of an STR-packed R-tree.
     *
     * SIR stands for "Sort-Interval-Recursive".
     *
     * STR-packed R-trees are described in:
     * P. Rigaux, Michel Scholl and Agnes Voisard. Spatial Databases With
     * Application To GIS. Morgan Kaufmann, San Francisco, 2002.
     *
     * @see STRtree
     */
    class CAnyRtSir : public CAnyRtBase
    {
        /**
        *
        **/
        class SIRAbstractNode : public CAnyRtNode 
        {
        public:
            //
            //
            //
            /**
            *
            **/
	        SIRAbstractNode(int level, int capacity);

            /**
            *
            **/
	        ~SIRAbstractNode();

        protected:
            //
            //
            //
            /**
            *
            **/
	        void* ComputeBounds() const;
        };

    protected:
        //
        //
        //
        /**
        *
        **/
        class SIRIntersectsOp:public CAnyRtBase::IntersectsOp 
        {
        public:
            /**
            *
            **/
            bool Intersects(const void *aBounds, const void *bBounds);
        };

    public:
        /** 
        * \brief
        * Constructs an SIRtree with the default node capacity.
        */
        CAnyRtSir();

        /** 
        * \brief
        * Constructs an SIRtree with the given maximum number of child nodes
        * that a node may have
        */
        CAnyRtSir(int nodeCapacity);

        /**
        *
        **/
        virtual ~CAnyRtSir();

    public:
        //
        //
        //
        /**
        *
        **/
        void Insert(double fx, double sx, void *item);

        /**
         * Returns items whose bounds intersect the given bounds.
         * @param x1 possibly equal to x2
         */
        std::vector<void*> *Query(double fx, double sx);

        /**
         * Returns items whose bounds intersect the given value.
         */
        std::vector<void*> *Query(double x);

    protected:
        /** 
        *\brief
        * Sorts the childBoundables then divides them into groups of size M, where
        * M is the node capacity.
        */
        std::auto_ptr<BoundVector> CreateParentBoundables(BoundVector *childBoundables, int level);

        /**
        *
        **/
        CAnyRtNode *CreateNode(int level);

        /**
        *
        **/
        IntersectsOp *GetIntersectsOp()
        {
            return m_intersectsOp;
        };

        /**
        *
        **/
        std::auto_ptr<BoundVector> SortBoundables(const BoundVector *input);

        /**
        *
        **/
        static bool CompareSIRBoundables(CAnyBoundable *a, CAnyBoundable *b);

    private:
        //
        IntersectsOp *m_intersectsOp;
    };
}

#endif