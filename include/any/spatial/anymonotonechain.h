/*!
 * The AnyIndex of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages, especially for those quick
 spatial algorithms.
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
#ifndef __ANYINDEX_MONOTONECHAIN_H__
#define __ANYINDEX_MONOTONECHAIN_H__

// Refer to basic geometry definition
#include  "..\anygeom\anyenvelope.h"
using namespace AnyGeometry;

// Forward classes outside below namespace
namespace AnyGeometry
{
    class CAnyCoordinateSequence;
    class CAnyLineSegment;
}

// Spatial index package
namespace AnyIndex
{
    /*! 
    * \brief
    * CMonotoneChain is a way of partitioning the segments of a linestring to
    * allow for fast searching of intersections.
    *
    * They have the following properties:
    * 
    * - the segments within a monotone chain will never intersect each other
    * - the envelope of any contiguous subset of the segments in a monotone chain
    *   is equal to the envelope of the endpoints of the subset.
    * 
    * Property 1 means that there is no need to test pairs of segments from within
    * the same monotone chain for intersection.
    * Property 2 allows
    * binary search to be used to find the intersection points of two monotone chains.
    * For many types of real-world data, these properties eliminate a large number of
    * segment comparisons, producing substantial speed gains.
    *
    * One of the goals of this implementation of MonotoneChains is to be
    * as space and time efficient as possible. One design choice that aids this
    * is that a MonotoneChain is based on a subarray of a list of points.
    * This means that new arrays of points (potentially very large) do not
    * have to be allocated.
    *
    * MonotoneChains support the following kinds of queries:
    * 
    * - Envelope select: determine all the segments in the chain which
    *   intersect a given envelope
    * - Overlap: determine all the pairs of segments in two chains whose
    *   envelopes overlap
    *
    * This implementation of MonotoneChains uses the concept of internal iterators
    * to return the resultsets for the above queries.
    * This has time and space advantages, since it
    * is not necessary to build lists of instantiated objects to represent the segments
    * returned by the query.
    * However, it does mean that the queries are not thread-safe.
    */
    class CAnyMonotoneChain
    {
    public:
        //
        //
        //
        /*!
        *
        **/
        CAnyMonotoneChain(const AnyGeometry::CAnyCoordinateSequence &pts, int start, int end, void *context);

        /*!
        *
        **/
        ~CAnyMonotoneChain();

    public:
        //
        // Access functions
        //
        /*!
        *
        **/
        const AnyGeometry::CAnyEnvelope &GetEnvelope();

        /*!
        *
        **/
        const AnyGeometry::CAnyEnvelope &GetEnvelope() const;

        /*!
        *
        **/
    	int GetStartIndex() const;

        /*!
        *
        **/
    	int GetEndIndex() const;

        /*!
        *
        **/
        void GetLineSegment(int index, AnyGeometry::CAnyLineSegment &lineSegment) const;

        /*!
        * \brief
        * Return the subsequence of coordinates forming this chain.
        * Allocates a new CoordinateSequence to hold the Coordinates
        */
        const AnyGeometry::CAnyCoordinateSequence &GetCoordinates() const;

        /*!
        *
        **/
        void SetId(int idx);

        /*!
        *
        **/
        int GetId() const;

        /*!
        *
        **/
        void *GetContext() const;

        //
        // Application functions based on montone chain index
        //
        /*!
        * \brief
        * Determine all the line segments in the chain whose envelopes overlap
        * the querying envelope, and process them. Namely, it can quickly decide those line segments are
        * overlaping the queryin envelope.
        *
        * \param queryEnvelope, given querying envelope to select which line segments of one poly line
        * \param visitor, it may convey highlight spatial calculation algorithm
        */
        void ComputeSelect(const AnyGeometry::CAnyEnvelope &queryEnvelope, void *visitor = 0);

        /*!
        * \brief
        * Quickly calculate whether there are two polyline intersected at one point using their monotone chain. 
        * Namely, each of two poly lines may represented by one or more monotone chain, then loop them to 
        * quickly decide whether there exist two line segment overlap.
        * \param other, one chain of monotone chains for one poly line
        * \param visitor, it may convey overlap algorithm
        **/
        void ComputeOverlaps(CAnyMonotoneChain &other, void *visitor = 0);

    private:
        //
        //
        //
        /*!
        *
        **/
        void DoComputeSelect(const AnyGeometry::CAnyEnvelope &queryEnvelope, unsigned int start, unsigned int end,  void *visitor = 0);

        /*!
        * 
        **/
        void DoComputeOverlaps(int fStart, int fEnd,CAnyMonotoneChain &other, int sStart,  int sEnd, void *visitor = 0);

    private:
        // Characters referred to its host geometry object
        // and the order ranger for this monotone chain
        const AnyGeometry::CAnyCoordinateSequence &m_pts;
        int m_start;
        int m_end;

        // Envelope constructed for this chain
        AnyGeometry::CAnyEnvelope m_envelope;

        // User-defined information
        void *m_context;

        // Inner idx, useful for optimizing chain comparisons
        int m_id;
    };
}
#endif