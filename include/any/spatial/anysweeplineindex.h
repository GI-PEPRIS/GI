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
#ifndef __ANYINDEX_SWEEPLINEINDEX_H__
#define __ANYINDEX_SWEEPLINEINDEX_H__

// Refer to STL container definitions etc
#include "any/base/anystl.h"

// Forward class
namespace AnyGeom
{
	class CAnyGeometryVisitor;
}

// Spatial Index Package
namespace AnyIndex
{
    // Forward classes
    class CAnySweepLineEvent;
    class CAnyInterval;

    /*!
    *
    **/
    class CAnySweepLineIndex
    {
        // Alias name for event container
	    typedef std::vector<CAnySweepLineEvent*> EventVector;
        typedef EventVector::iterator event_itr;
        typedef EventVector::const_iterator event_citr;

    public:
        //
        // Ctrs & dctr
        //
        /*!
        *
        **/
        CAnySweepLineIndex();

        /*!
        *
        **/
        ~CAnySweepLineIndex();

    public:
        //
        // Index construction & application
        //
        /*!
        *
        **/
        void Insert(CAnyInterval &sweepInterval);

        /*!
        *
        **/
		void ComputeOverlaps(AnyGeom::CAnyGeometryVisitor *visitor);

    private:
        /*!
        * \brief
        * Because Delete Events have a link to their corresponding Insert event,
        * it is possible to compute exactly the range of events which must be
        * compared to a given Insert event object.
        */
        void BuildIndex();

        /*!
        *
        **/
		void DoComputeOverlaps(int start, int end, const CAnyInterval &curInterval, AnyGeom::CAnyGeometryVisitor *visitor);

    private:
	    // Make it a real vector rather then a pointer
	    EventVector m_events;

        // Status whether index is built
	    bool m_isBuilt;

	    // Statistics information
	    int m_overlaps;
    };
}

#endif