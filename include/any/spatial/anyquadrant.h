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
#ifndef __ANYSPATIALINDEX_QUADRANT_H__
#define __ANYSPATIALINDEX_QUADRANT_H__

// Forward classes outside below namespace
namespace AnyGeometry
{
    class CAnyCoordinate;
}

// Spatial index package
namespace AnyIndex
{
    /*!
    * \brief
    * Utility functions for working with quadrants, which are numbered as follows:
    *
    * 1 | 0
    * --+--
    * 2 | 3
    *
    **/
    class CAnyQuadrant
    {
    public:
        /*!
        * \enum
        * Quadrant enumeration
        */
        enum QuadrantDef
        {
            Quadrant_Unknown = -1,
            Quadrant_First,
            Quadrant_Second,
            Quadrant_Third,
            Quadrant_Fourth,
        };

    protected:
        //
        // Ctrs & Dctr mean which is a UTILITY class since they are declared in private way
        //
        /*!
        *
        **/
        CAnyQuadrant();

        /*!
        *
        **/
        ~CAnyQuadrant();

    public:
        //
        // Quadrant creation
        //
        /*!
        * \brief
        * Returns the quadrant of a directed line segment (specified as x and y displacements, 
        * which cannot both be 0)
        **/
        static int Quadrant(double dx, double dy);

        /*!
        * \brief
        * Returns the quadrant of a directed line segment from first coordinate to second coordinate
        **/
        static int Quadrant(const AnyGeometry::CAnyCoordinate &firstCoord, const AnyGeometry::CAnyCoordinate &secondCoord);

        //
        // Typical operations based on quadrants
        //
        /*!
        * brief
        * Returns true if the quadrants are 1 and 3, or 2 and 4
        **/
        static bool IsOpposite(int firstQuadrant, int secondQuadrant);

        /*!
        * Returns the right-hand quadrant of the halfplane defined by the two quadrants,
        * or -1 if the quadrants are opposite, or the quadrant if they are identical.
        **/
        static int CommonHalfPlane(int firstQuadrant, int secondQuadrant);

        /*!
        * \brief
        * Returns whether the given quadrant lies within the given halfplane (specified
        * by its right-hand quadrant).
        **/
        static bool IsInHalfPlane(int quadrant, int halfPlane);

        /*!
        * Returns true if the given quadrant is 0 or 1.
        **/
        static bool IsNorthern(int quadrant);
    };
}

#endif