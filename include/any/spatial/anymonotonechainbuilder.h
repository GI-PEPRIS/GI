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
#ifndef __ANYINDEX_MONOTONECHAINBUILDER_H__
#define __ANYINDEX_MONOTONECHAINBUILDER_H__

// Refer to STL container definitions
#include "anybase\anystl.h"

// Forward classes
namespace AnyGeometry
{
    class CAnyCoordinateSequence;
}

// Spatial index package
namespace AnyIndex
{
    // Forward classes
    class CAnyMonotoneChain;

    /*!
    * \brief
    * A CMonotoneChainBuilder implements functions to determine the monotone 
    * chains in a sequence of points.
    **/
    class CMonotoneChainBuilder
    {
    public:
        // Alias name for monotone chain container
        typedef std::vector<CAnyMonotoneChain *> ChainVector;
        typedef ChainVector::iterator chain_itr;
        typedef ChainVector::const_iterator chain_citr;

        typedef std::vector<int> IndexVector;
        typedef IndexVector::iterator index_itr;
        typedef IndexVector::const_iterator index_citr;

    protected:
        //
        // Ctrs & Dctr mean which is a UTILITY class since they are declared in private way
        //
        /*!
        *
        **/
        CMonotoneChainBuilder();

        /*!
        *
        **/
        ~CMonotoneChainBuilder();

    public:
        //
        // Class behaviors
        //
        /*!
         * \brief
         * Return a newly-allocated vector of newly-allocated CMonotoneChain objects for the 
         * given CoordinateSequence. 
         * Remember to deep-delete the result.
         */
        static ChainVector *GetChains(const AnyGeometry::CAnyCoordinateSequence &pts, void *context);

        /** 
         * \brief
         * Fill the provided vector with newly-allocated MonotoneChain objects
         * for the given CoordinateSequence.
         * Remember to delete vector elements!
         */
        static void GetChains(const AnyGeometry::CAnyCoordinateSequence &pts, void *context, ChainVector &mcList);

        /**
        *
        **/
        static ChainVector *GetChains(const AnyGeometry::CAnyCoordinateSequence &pts);

        /** 
         * \brief
         * Fill the given vector with start/end indexes of the monotone chains
         * for the given CoordinateSequence.
         * The last entry in the array points to the end point of the point array,
         * for use as a sentinel.
         */
        static void GetChainStartIndices(const AnyGeometry::CAnyCoordinateSequence &pts, IndexVector &startIndexList);

        /** 
         * \brief
         * Given whether consective points are in the same quadrant, if they are 
         * they make up a monotone chain
         * \param pts the points of one geometry such as a poly line
         * \param start from which order to find one monotone chain
         * \return the index of the last point in the monotone chain
         */
        static int FindChainEnd(const AnyGeometry::CAnyCoordinateSequence &pts, int start);
    };
}
#endif