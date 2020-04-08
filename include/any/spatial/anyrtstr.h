#ifndef __ANYINDEX_RTSTR_H__
#define __ANYINDEX_RTSTR_H__

// Refer to its parent class
#ifndef __ANYINDEX_GEOINDEX_H__
#include "anygeoindex.h"
#endif

// Refer to its parent class
#ifndef __ANYINDEX_RTBASE_H__
#include "anyrtbase.h"
#endif

// Refer to inner class's parent
#ifndef __ANYINDEX_RTNODE_H__
#include "anyrtnode.h"
#endif

/**
*
**/
namespace AnyIndex
{
    // Forward classes
    class CAnyEnvelope;

    /**
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
    **/
    class CAnyRtStr : public CAnyRtBase, public CAnyGeoIndex
    {
        /**
        *
        **/
        class STRIntersectsOp: public CAnyRtBase::IntersectsOp 
        {
	        public:
		        bool Intersects(const void* aBounds, const void* bBounds);
        };

        /**
        *
        **/
        class STRAbstractNode : public CAnyRtNode
        {
        public:
            //
            //
            //
            /**
            *
            **/
	        STRAbstractNode(int level, int capacity);

            /**
            *
            **/
	        ~STRAbstractNode();

        protected:
            //
            //
            //
            /**
            *
            **/
	        void* ComputeBounds() const;
        };

    public:
        //
        //
        //
        /**
         * Constructs an STRtree with the given maximum number of child nodes that
         * a node may have
         */
        CAnyRtStr(int nodeCapacity = 10);

        /**
        *
        **/
        ~CAnyRtStr();

    public:
        //
        //
        //
        /**
        *
        **/
        void Insert(const CAnyEnvelope *itemEnv, void* item);

        /**
        *
        **/
        void Query(const CAnyEnvelope *searchEnv, std::vector<void*> &matches);

        /**
        *
        **/
        void Query(const CAnyEnvelope *searchEnv, void *visitor);

        /**
        *
        **/
        bool Remove(const CAnyEnvelope *itemEnv, void *item);

    public:
        //
        //
        //
        /**
        *
        **/
        static double Avg(double a, double b);

        /**
        *
        **/
        static double CenterY(const CAnyEnvelope *e);

    protected:
        //
        //
        //
        /**
        *
        **/
        CAnyRtNode *CreateNode(int level);

        /**
        *
        **/
        IntersectsOp *GetIntersectsOp() 
        {
            return &m_intersectsOp;
        };

    private:
        /**
         * Creates the parent level for the given child level. First, orders the items
         * by the x-values of the midpoints, and groups them into vertical slices.
         * For each slice, orders the items by the y-values of the midpoints, and
         * group them into runs of size M (the node capacity). For each run, creates
         * a new (parent) node.
         */
        std::auto_ptr<BoundVector> CreateParentBoundables(BoundVector *childBoundables, int level);

        /**
        *
        **/
        std::auto_ptr<BoundVector> CreateParentBoundablesFromVerticalSlices(std::vector<BoundVector*> *verticalSlices, int level);

        /**
        *
        **/
        std::auto_ptr<BoundVector> SortBoundables(const BoundVector *input);

        /**
        *
        **/
        std::auto_ptr<BoundVector> CreateParentBoundablesFromVerticalSlice(BoundVector *childBoundables, int level);

        /**
         * @param childBoundables Must be sorted by the x-value of
         *        the envelope midpoints
         * @return
         */
        std::vector<BoundVector*> *VerticalSlices(BoundVector *childBoundables, int sliceCount);

        /**
        *
        **/
        static bool CompareY(CAnyBoundable *a, CAnyBoundable *b);

    private:
        // Bound intersection operation
        STRIntersectsOp m_intersectsOp;

    };
}
#endif