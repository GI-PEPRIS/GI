#ifndef __ANYINDEX_INTNODE_H__
#define __ANYINDEX_INTNODE_H__

// Refer to STL definitions
#ifndef __ANYBASE_STL_H__
#include "anybase\anystl.h"
#endif

/**
*
**/
namespace AnyIndex
{
    /**
    *
    **/
    class CAnyIntNode
    {
    public:
        //
	    typedef std::vector<const CAnyIntNode *> NodeVector;

        //
        //
        //
        /**
        *
        **/
        CAnyIntNode();

        /**
        *
        **/
        CAnyIntNode(double min, double max);

        /**
        *
        **/
        virtual ~CAnyIntNode();

    public:
        //
        //
        //
        /**
        *
        **/
        double GetMin() const;
	
        /**
        *
        **/
        double GetMax() const; 

        /**
        *
        **/
        virtual void Query(double queryMin, double queryMax, void *visitor) const = 0;

        //
        // Class behaviors
        //
        /**
        *
        **/
		static bool Compare(const CAnyIntNode *first, const CAnyIntNode *second);

    protected:
        //
        //
        //
        /**
        *
        **/
        bool Intersects(double queryMin, double queryMax) const;

    protected:
        //
        double m_min;
        //
        double m_max;
    };
}

#endif