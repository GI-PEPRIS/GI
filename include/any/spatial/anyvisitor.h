#ifndef __ANYINDEX_VISITOR_H__
#define __ANYINDEX_VISITOR_H__

/**
*
**/
namespace AnyIndex
{
    /**
    *
    **/
    class CAnyVisitor
    {
    protected:
        //
        //
        //
        /**
        *
        **/
        CAnyVisitor();

        /**
        *
        **/
        virtual ~CAnyVisitor();

    public:
        //
        //
        //
        /**
        *
        **/
        virtual bool VisitItem(void *item) = 0;
    };
}

#endif