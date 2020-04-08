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
#ifndef __ANYINDEX_SWEEPLINEEVENT_H__
#define __ANYINDEX_SWEEPLINEEVENT_H__

// Refer to boundable definition for this index
#include "anyinterval.h"

// Spatial index package
namespace AnyIndex
{
    // Forward classes
    class CAnyInterval;

    /*!
    *
    **/
    class CAnySweepLineEvent
    {
    public:
        /*!
        * \enum sweep event type
        * \brief Here are two events when sweeping from left to right or top to down
        **/
	    enum EventType
        {
		    EVENT_INSERT = 1,
		    EVENT_DELETE
	    };

        /*!
        * \struct comparasion function
        * \brief order function for an event container
        **/
        struct LessThen 
        {
	        bool operator()(const CAnySweepLineEvent *first, const CAnySweepLineEvent *second) const;
        };

    public:
        //
        // Ctrs & dctr
        //
        /*!
        *
        **/
        CAnySweepLineEvent(double xValue, CAnySweepLineEvent *insertEvent, CAnyInterval &sweepInterval);

        /*!
        *
        **/
        ~CAnySweepLineEvent();

	private:
		//
		CAnySweepLineEvent(const CAnySweepLineEvent &other);

		//
		const CAnySweepLineEvent &operator=(const CAnySweepLineEvent &other);

    public:
        //
        // Decision & basic access functions
        //
        /*!
        *
        **/
        bool IsInsert() const;

        /*!
        *
        **/
        bool IsDelete() const;

        /*!
        *
        **/
        const CAnySweepLineEvent *GetInsertEvent() const;

		//
		//
		//
        /*!
        *
        **/
        int GetDeleteEventIndex() const;

        /*!
        *
        **/
        void SetDeleteEventIndex(int deleteEventIndex);

        //
        // Comparasion functions for an event container
        //
        /*!
        *
        **/
        const CAnyInterval &GetInterval() const;

        /*!
        * \brief
        * Those events are ordered first by their x-value, and then by their eventType.
        * It is important that Insert events are sorted before Delete events, so that
        * items whose Insert and Delete events occur at the same x-value will be
        * correctly handled.
        */
        int CompareTo(const CAnySweepLineEvent *other) const;

    private:
        // Whether is INSERT or DELETE
	    int m_eventType;

	    // Relation bewteen a DELETE event and an INSERT event, 
        // null if this is an INSERT_EVENT event
	    CAnySweepLineEvent *m_insertEvent;

        // Direct indicator of DELETE event in order to quick position which insert event
	    int m_deleteEventIndex;

        // Comparasion value in one coordinate direction
	    double m_xValue;

        // Comparasion interval bewteen an INSERT event & DELETE event
	    CAnyInterval m_sweepInterval;
    };
}
#endif