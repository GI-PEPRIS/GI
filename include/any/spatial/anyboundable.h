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
#ifndef __ANYSPATIALINDEX_BOUNDABLE_H__
#define __ANYSPATIALINDEX_BOUNDABLE_H__

// Refer to stl definitions
#include "anybase\anystl.h"

// Spatial index package
namespace AnySpatialIndex
{
    /*!
    * \class CAnyBoundable which is an envelope class for one geometry object
    *
    * \brief 
    * Returns a representation of space that encloses one boundable class, 
    * preferably not much bigger than this Boundable's boundary yet
    * fast to test for intersection with the bounds of other Boundables.
    *
    * As far, here are one style of boundable geometry, namely rectangle
    * and other geometries maybe as boundable object given one index algorithm
     */
    class CAnyBoundable
    {
    public:
        // Bounds container definition
        typedef std::vector<CAnyBoundable *> BoundVector;
        typedef BoundVector::iterator bound_itr;
        typedef BoundVector::const_iterator bound_citr;

        //
        // Ctrs & dctr
        //
        /*!
        * \brief
        * Not to permit implicitly type conversion from one geometry object to this boundable class
        **/
        explicit CAnyBoundable(void *item, const void *bound = 0);

        /*!
        * \brief
        * Nothing except for the correct declaration of its subclasses
        **/
        virtual ~CAnyBoundable();

    protected:
        //
        // Ctrs & dctr
        //
        /*!
        * \brief 
        * This bounable class must work together with its host class, namely a geometry object
        **/
        CAnyBoundable();

    private:
        // Not permit direct assignment between two boundable classes
        CAnyBoundable(const CAnyBoundable &other);
        const CAnyBoundable &operator=(const CAnyBoundable &other);

    public:
        //
        // Access interface 
        //
        /*!
        * \brief
        * \return non-type pointer to represent different spatial geometry types
        **/
        const void *GetBound() const;

        /*!
        * \brief 
        * Get host geometry object of this boundable class
        **/
        const void *GetItem() const;

    protected:
        //
        // Boundary functions
        //
        /*!
        * \brief
        * According to current host geometry object to compute its boundable geometry
        **/
        virtual void *DoComputeBound() const = 0;

    protected:
        // Bounds of current host spatial item
        // which is created by this class
        mutable const void *m_bound;

        // Host spatial item
        void *m_item;
    };
}
#endif