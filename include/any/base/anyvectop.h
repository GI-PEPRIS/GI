/*
 * The UrbanEye PND solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy one kind
 * of mobile or portable devices with competitive qualities being a leading one.
 *
 * Copyright (C) 2008 Xiujie Sheng
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
 * Graduate School
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYBASE_VECTOROP_H__
#define __ANYBASE_VECTOROP_H__

// Refer to EXPORT & IMPORT macroes
#include "anybase.h"

// Refer to CGeoPoint<> etc
#include "anygeom.h"

// Refer to special value setting
#include "anyport.h"

// Declare NavBase namespace
namespace AnyBase
{
    /*!
	* This class only encapsulates all useful vector operations in static way here
    */ 
    template<typename T>
    class CVectOP
    {
        // Not permit to directly declare this class as stack or heap variable
        ~CVectOP(void)
        {
        }

    public:
        // Data declaration for convenience
        typedef CGeoPoint<T> VectorPoint;

        // Static variables 
        static double m_minBuffWidth;
        static double m_maxBuffWidth;

        //
        // Basic vector's operations
        //
        /*!
        *
        */
        static void Add(const VectorPoint &start, const VectorPoint &end, VectorPoint &result);

        /*!
        *
        */
        static void Sub(const VectorPoint &start, const VectorPoint &end, VectorPoint &result);

        /*!
        *
        */
        static void Mul(const VectorPoint &point, T scale, VectorPoint &result);

        /*!
        *
        */
        static double Dot(const VectorPoint &first, const VectorPoint &second);

        /*!
        *
        */
        static double Cross(const VectorPoint &first, const VectorPoint &second);

        /*!
        *
        */
        static short Cross(const VectorPoint &first, const VectorPoint &second, const VectorPoint &third);

        /*!
        *
        */
        static double Mag(const VectorPoint &point);

        /*!
        *
        */
        static double Mag(const VectorPoint &start, const VectorPoint &end);

        /*!
        *
        */
        static double MagSquare(const VectorPoint &point);

        /*!
        *
        */
        static double MagSquare(const VectorPoint &start, const VectorPoint &end);

        /*!
        *
        */
        static double Unit(const VectorPoint &start, const VectorPoint &end, VectorPoint &result);

        //
        // Senior Vector operations
        //
        /*!
        * 
        */
        static double UnitAngle(const VectorPoint &point);

        /*!
        *
        */
        static double UnitAngle(const VectorPoint &first, const VectorPoint &second);

        /*!
        *
        */
        static double Angle(const VectorPoint &first, const VectorPoint &center, const VectorPoint &second);

        /*!
        *
        */
        static double Angle(const VectorPoint &first, const VectorPoint &second);

        /*!
        *
        */
        static void Rotate(const VectorPoint &point, double angle, VectorPoint &result);

        /*!
        *
        */
        static void Rotate(const VectorPoint &point, const VectorPoint &center, double angle, VectorPoint &result);

        /*!
        *
        */
        static void Rotate(double radius, double angle, const VectorPoint &center, VectorPoint &result);

        /*!
        *
        */
        static void Rotate(double radius, double angle, VectorPoint &result);

        //
        // Spatial analysis based on vector definition
        //
        /*!
        *
        */
        static short Direction(const VectorPoint &first, const VectorPoint &second, const VectorPoint &third);

        /*!
        *
        */
        static double Line2Point(const VectorPoint &start, const VectorPoint &end, const VectorPoint &point, double &factor, VectorPoint &result);

        /*!
        * Get the distance and projected point on one linear segment
        *
        * @start: the starting point of one linear segment
        * @end: the ending point of one linear segment
        * @point: the specified point which is needed to be projected
        * @result: the projected point
        * @return: the projecting distance. Note: zero means on "BOUNDARY"
        */
        static double Point2Line(const VectorPoint &start, const VectorPoint &end, const VectorPoint &point, double &factor, VectorPoint &result);

        /*!
        * Whether one point locate on boundary or in interior or exterior of one polygon
        *
        * @vertices: the pointer pointing to points of one polygon
        * @count: the count of points of one polygon
        * @point: the specified point needed to know its spatial relationship with above polygon
        * @base: the farest point define one ray starting from above specified point
        * @return: PP_Invalid, PP_On, PP_In, PP_Out
        */
        static short Point2Polygon(const VectorPoint *vertices, int count, const VectorPoint &point, const VectorPoint &base);

        /*!
        * Quick way to know whether specified point locates at inner or outside of one polygon
        * 
        * @vertices: the pointer pointing to polygon corner points
        * @count: the count of points making one polygon
        * @point: specified point
        * @return: -1 means exception occur, 1 means inside, zero means outside
        */
        static short Point2Polygon(const VectorPoint *vertices, int count, const VectorPoint &point);

        /*!
        * Get the spatial relationship of two lines
        *
        * @fist: the starting point of the first line segment
        * @second: the ending point of the first line segment
        * @third: the starting point of the second line segment
        * @fourth: the ending point of the second line segment
        * @factorOne: the scalar factor intercepted by crossed point on the first line segment
        * @factorTwo: the scalar factor intercepted by crossed point on the second line segment
        * @result: the intersected point
        * @Return: LL_Invalid, LL_Intersect, LL_Parallel
        */
        static short Line2Line(const VectorPoint &first, const VectorPoint &second, const VectorPoint & third, const VectorPoint &fourth, double &factorOne, double &factorTwo, VectorPoint &result, bool isQuick = 0);

        /*!
        * Get the relationship of one line and one circle 
        *
        * @center: the center point of one circle
        * @radius: the radius of one circle
        * @start: the starting point of one line segment
        * @end: the ending point of one line segment
        * @factorM: the scalar factor of line segment specified by "start" and "end" points
        * @factorK: the scalar factor of radius and above linear segment
        * @factorO: the scalar factor indicating relationship between projected length on above linear segment and radius
        * @return: LC_Invalid, LC_Bear, LC_Intersect, LC_Disperse
        */
        static short Line2Circle(const VectorPoint &center, double radius, const VectorPoint &start, const VectorPoint &end, double &factorM, double &factorK, double &factorO);

        /*!
        * At the inner or outside to generate points surrounding original points in specified way, namely, different CAP styles.
        * Note: this function is only to get half part of real buffer area surrounding this polyline
        *
        * @vertices: the pointer to original points around which new points are generated
        * @count: the count of original points
        * @bufferWidth: the width of buffer surrounding original points
        * @leftRight: the side in inner or outside: 1 means outside, -1 means inner side
        * @bufferVertices: the new points surrounding original points. Note: here let outside responsible for memory allocation 
        * @bufferCount: the count of new points
        * @return: -1 means failure, 1 means success
        */
        static short MakeBufferLine(const VectorPoint *vertices, int count, double bufferWidth, short leftRight, VectorPoint **bufferVertices, int &bufferCount);

        /*!
        * Get the order of one point which is the neast to specified point and the distance of specified point project on one segment
        * 
        * @vertices: the pointer pointing to a group of points 
        * @count: the count of above points
        * @cyclic: whether is a polygon
        * @point: the specified point to find one point which is the neast to it
        * @tolerance: the limited distance as standard
        * @result: the projected point on one segment of above points
        * @return: -1 means invalid or error, else indicates which point beginning with zero
        */
        static short GetInnerIdx(const VectorPoint *vertices, int count, const VectorPoint &point, double tolerance, VectorPoint &result, short cyclic = 0);

    };

    //////////////////////////////////////////////////////////////////////////////////
    // Class variables initialization
    //
    template<typename T>
    double CVectOP<T>::m_minBuffWidth = 5.0;

    template<typename T>
    double CVectOP<T>::m_maxBuffWidth = 16.0;

    //////////////////////////////////////////////////////////////////////////////////
    // Basic vector's operations
    //
    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline void CVectOP<T>::Add(const VectorPoint &start, const VectorPoint &end, VectorPoint &result)
    {
        result.m_x = end.m_x + start.m_x;
        result.m_y = end.m_y + start.m_y;
    }

    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline void CVectOP<T>::Sub(const VectorPoint &start, const VectorPoint &end, VectorPoint &result)
    {
        result.m_x = end.m_x - start.m_x;
        result.m_y = end.m_y - start.m_y;
    }

    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline void CVectOP<T>::Mul(const VectorPoint &point, T scale, VectorPoint &result)
    {
        // Note: when the vector point aren't double precision, automatically conversion behind different 
        // CPU architectures
        result.m_x = point.m_x * scale;
        result.m_y = point.m_y * scale;
    }

    /*!
    *
    */
    template<typename T>
    inline double CVectOP<T>::Dot(const VectorPoint &first, const VectorPoint &second)
    {
        return (first.m_x * second.m_x + first.m_y * second.m_y);
    }

    /*!
    * Right handed standard:
    */
    template<typename T>
    inline double CVectOP<T>::Cross(const VectorPoint &first, const VectorPoint &second)
    {
        return (first.m_x * second.m_y - first.m_y * second.m_x);
    }

    /*!
    *
    */
    template<typename T>
    inline short CVectOP<T>::Cross(const VectorPoint &first, const VectorPoint &second, const VectorPoint &third)
    {
        // Get two vectors
        VectorPoint dirOne;
        VectorPoint dirTwo;
        Unit(first, second, dirOne);
        Unit(first, third, dirTwo);

        // Apply right hand principle
        double indicator = Cross(dirOne, dirTwo);
        OrientDirection rd = OD_SameLine;

        if(indicator < -ANY_ZERO)
        {
            rd = OD_Clockwise;    // CW
        }
        else if(indicator > ANY_ZERO) 
        {
            rd = OD_CounterClockwise;     // CCW
        }

        return rd;
    }

    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline double CVectOP<T>::Mag(const VectorPoint &point)
    {
        return ::sqrt(static_cast<double>(point.m_x * point.m_x + point.m_y * point.m_y));
    }

    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline double CVectOP<T>::Mag(const VectorPoint &start, const VectorPoint &end)
    {
        return ::sqrt(static_cast<double>((end.m_x - start.m_x) * (end.m_x - start.m_x) + (end.m_y - start.m_y) * (end.m_y - start.m_y)));
    }

    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline double CVectOP<T>::MagSquare(const VectorPoint &point)
    {
        return (point.m_x * point.m_x + point.m_y * point.m_y);
    }

    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline double CVectOP<T>::MagSquare(const VectorPoint &start, const VectorPoint &end)
    {
        return ((end.m_x - start.m_x) * (end.m_x - start.m_x) + (end.m_y - start.m_y) * (end.m_y - start.m_y));
    }

    /*!
    * TODO: 
    * Not only limited to one plane
    */
    template<typename T>
    inline double CVectOP<T>::Unit(const VectorPoint &start, const VectorPoint &end, VectorPoint &result)
    {
        double magnitude = Mag(start, end);
	    if(magnitude <= ANY_ZERO && magnitude >= -ANY_ZERO)
        {
            // Note: Assume the repeated vectors as the full unit since ...
            magnitude = 0.0;
            result.m_x = result.m_y = static_cast<T>(1.0);
	    }
        else
        {
            // Note: Implicit type conversion when running spercial operators, e.g., division
            result.m_x = static_cast<T>((end.m_x - start.m_x)/magnitude);
            result.m_y = static_cast<T>((end.m_y - start.m_y)/magnitude);
        }

        return magnitude;
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Senior vector's operations
    //
    /*!
    * TODO: 
    * This function is only applied to XY plane and need define triangular function lookup table
    */
    template<typename T>
    inline double CVectOP<T>::UnitAngle(const VectorPoint &point)
    {
        return (point.m_y < 0.0) ? (TWOPI - ::acos(static_cast<double>(point.m_x))) : (::acos(static_cast<double>(point.m_x)));
    }

    /*!
    * TODO:
    * Triangular functions based on look up table
    */
    template<typename T>
    inline double CVectOP<T>::UnitAngle(const VectorPoint &first, const VectorPoint &second)
    {
        double dot = Dot(first, second);
        double cross = Cross(first, second);

        return (cross < 0.0) ? (TWOPI - ::acos(dot)) : (::acos(dot));
    }

    /*!
    *
    */
    template<typename T>
    inline double CVectOP<T>::Angle(const VectorPoint &first, const VectorPoint &center, const VectorPoint &second)
    {
        VectorPoint dirOne;
        Unit(center, first, dirOne);

        VectorPoint dirTwo;
        Unit(center, second, dirTwo);

        return UnitAngle(dirOne, dirTwo);
    }

    /*!
    *
    */
    template<typename T>
    inline double CVectOP<T>::Angle(const VectorPoint &first, const VectorPoint &second)
    {
        VectorPoint direction;
        Unit(first, second, direction);

        return UnitAngle(direction);
    }

    /*!
    * TODO:
    * Triangular functions based on look up table
    *
    */
    template<typename T>
    inline void CVectOP<T>::Rotate(const VectorPoint &point, double angle, VectorPoint &result)
    {
        // The same vector
        if(result == point)
        {
            // TODO:
            // Triangular function lookup table
            VectorPoint tmp = point;
            result.m_x = tmp.m_x * ::cos(angle) - tmp.m_y * ::sin(angle);
            result.m_y = tmp.m_x * ::sin(angle) + tmp.m_y * ::cos(angle);
        }
        else
        {
            // TODO:
            // Triangular function lookup table
            result.m_x = point.m_x * ::cos(angle) - point.m_y * ::sin(angle);
            result.m_y = point.m_x * ::sin(angle) + point.m_y * ::cos(angle);
        }
    }

    /*!
    * TODO:
    * Triangular functions based on look up table
    */
    template<typename T>
    inline void CVectOP<T>::Rotate(const VectorPoint &point, const VectorPoint &center, double angle, VectorPoint &result)
    {
        VectorPoint direction;
        VectorPoint difference;

        Sub(center, point, direction);
        Rotate(direction, angle, difference);
        Add(center, difference, result);
    }

    /*!
    * TODO:
    * Triangular functions based on look up table
    */
    template<typename T>
    inline void CVectOP<T>::Rotate(double radius, double angle, const VectorPoint &center, VectorPoint &result)
    {
        VectorPoint difference;
        difference.m_x = radius * ::cos(angle);
        difference.m_y = radius * ::sin(angle);

        Add(center, difference, result);
    }

    /*!
    * TODO:
    * Triangular functions based on look up table
    */
    template<typename T>
    inline void CVectOP<T>::Rotate(double radius, double angle, VectorPoint &result)
    {
        result.m_x = radius * ::cos(angle);
        result.m_y = radius * ::sin(angle);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Spatial analysis methods
    //
    /*!
    *
    */
    template<typename T>
    short CVectOP<T>::Direction(const VectorPoint &first, const VectorPoint &second, const VectorPoint &third)
    {
        short dir = Cross(first, second, third);
        if(dir == OD_SameLine)
        {
            CGeoPoint<double> dirOne, dirTwo;
            Sub(first, second, dirOne);
            Sub(first, third, dirTwo);

            return (dirOne.m_x * dirTwo.m_x < 0 || dirOne.m_y * dirTwo.m_y < 0) ? -1 :
                (MagSquare(dirOne) < MagSquare(dirTwo));
        }

        return dir;
    }

    /*!
    * The principle of one line segment to point: the value of factor would reflect which point on a line segment is nearest to specified point
    * > 0.5, < 0.5
    *
    */
    template<typename T>
    double CVectOP<T>::Line2Point(const VectorPoint &start, const VectorPoint &end, const VectorPoint &point, double &factor, VectorPoint &result)
    {
        // Exception check
        double lengthSquare = MagSquare(start, end);
        if(lengthSquare <= ANY_ZERO && lengthSquare >= -ANY_ZERO)
        {
            // Note:
            // Check the validity of invalid status which doesn't cause ambiguous
            result = start;
            factor = 0.0;
            return MagSquare(start, point);
        }

        // ...
        VectorPoint first;
        VectorPoint second;
        Sub(start, end, first);
        Sub(start, point, second);
        factor = Dot(first, second) / lengthSquare;

        // ...
        VectorPoint middle;
	    Mul(first, static_cast<T>(factor), middle);
	    Add(start, middle, result);

	    return  (MagSquare(start, point) - (factor * factor * lengthSquare)) ;
    }

    /*!
    * Use geometric sense of dot product
    *
    */
    template<typename T>
    double CVectOP<T>::Point2Line(const VectorPoint &start, const VectorPoint &end, const VectorPoint &point, double &factor, VectorPoint &result)
    {
        // Two linear directions
        VectorPoint first; 
        VectorPoint second;
        Sub(start, point, first);
        Sub(start, end, second);

        // Assure linear segment isn't one point
        double lengthSquare = MagSquare(start, end);
        if(lengthSquare <= ANY_ZERO && lengthSquare >= -ANY_ZERO)
        {
            factor = 0.0;
        }
        else
        {
            factor = Dot(first, second) / lengthSquare;
        }

        //
        if(factor < 0.0)
        {
            result = start;
        }
        else if(factor > 1.0)
        {
            result = end;
        }
        else
        {
            result.m_x = static_cast<T>(start.m_x + second.m_x * factor);
            result.m_y = static_cast<T>(start.m_y + second.m_y * factor);
        }

        // The projecting distance
        Sub(result, point, first);
        return Mag(first);
    }


    /*!
    * Use simple two algebra fucntion we can deduce whether lines intersect or directly use geometry sense represented by cross product 
    *
    */
    template<typename T>
    short CVectOP<T>::Line2Line(const VectorPoint &first, const VectorPoint &second, const VectorPoint & third, const VectorPoint &fourth, double &factorOne, double &factorTwo, VectorPoint &result, bool isQuick)
    {
        // Two linear directions
        VectorPoint dirOne, dirTwo;
        Sub(first, second, dirOne);
        Sub(third, fourth, dirTwo);
        
        // TODO:
        // Exception check if the magnitude of dirOne or dirTwo is zero
        // ...

        // The geometric sense of cross product
        LineLineRelationship rel = LL_Invalid;
        double denom = Cross(dirOne, dirTwo); 
        if(::fabs(denom) < ANY_ZERO)
        {
            // Note:
            // It also includes the stacked circumstance
            rel = LL_Parallel;
        }
        else
        {
            // Intersect 
            rel = LL_Intersect;

            if(!isQuick)
            {
                // Intersected scale position
                VectorPoint dirThree;
                Sub(first, third, dirThree);

                // Areas represented by different cross products then divide the same high or base, we should get 
                double denomOne = Cross(dirThree, dirTwo);
                double denomTwo = Cross(dirThree, dirOne);
                factorOne = denomOne / denom;
                factorTwo = denomTwo / denom;

                // Intersected point
                VectorPoint middle;
                Mul(dirOne, static_cast<T>(factorOne), middle);
                Add(first, middle, result);
            }
        }

        return rel;
    }

    /*!
    * Use dot product to get one point projected on linear segment made by "start" and "end" points then discuss 
    * different circumstances under above calculation
    * 
    */
    template<typename T>
    short CVectOP<T>::Line2Circle(const VectorPoint &center, double radius, const VectorPoint &start, const VectorPoint &end, double &factorM, double &factorK, double &factorO)
    {
        //
        VectorPoint middle;
        double distSquare = Line2Point(start, end, center, factorM, middle);
        
        LineCircleRelationship rel = LC_Invalid;
        factorO = ::sqrt(distSquare) / radius;
        if(::fabs(1.0 - factorO) < ANY_ZERO)
        {
            rel = LC_Bear;    
            factorK = 0.0;
            factorO = 1.0;
        }
        else if(factorO > 1.0)
        {
            rel = LC_Disperse;
            factorK = -1.0;
        }
        else
        {
            rel = LC_Intersect;
            double length = MagSquare(start, end);

            // Exclude exception
            factorK = (::fabs(length) < ANY_ZERO) ? 1.0 : ::sqrt((radius * radius - distSquare) / length);
        }

        return rel;
    }

    /*!
    * The distance of point is to one linear segment is zero means on boundary, ray theory would decide whether it is in exterior or interior
    *
    */
    template<typename T>
    short CVectOP<T>::Point2Polygon(const VectorPoint *vertices, int count, const VectorPoint &point, const VectorPoint &base)
    {
        // Exception check
        if(!vertices || count < 2)
        {
            return PP_Invalid;
        }

        // TODO:
        // Exception: base point should be not inside the specified polygon
        // ...

        // Note: here base point should be enough far 
        double rayDist = MagSquare(point, base);
        PointPolygonRelationship rel = PP_Invalid;
        int crossCount = 0;

        // Loop each two vertices ...
        int prev = 0;
        for(; prev < count; prev++)
        {
            // Get two valid vertices
            int next = (prev + 1) % count;
            if(MagSquare(vertices[prev], vertices[next]) < ANY_ZERO)
            {
                continue;
            }

            // Calculate lines relationship then deal with different circumstances
            double factorOne = 0.0;
            double factorTwo = 0.0;
            VectorPoint result;
            if(Line2Line(vertices[prev], vertices[next], point, base, factorOne, factorTwo, result) == LL_Intersect && 
                (factorOne > -ANY_ZERO && factorOne < ANY_FARONE) && 
                (factorTwo > -ANY_ZERO && factorTwo < ANY_FARONE))  // Intersect
            {
                if(factorTwo < ANY_ZERO || rayDist * factorTwo * factorTwo < ANY_ZERO)
                {
                    rel = PP_On;
                    break;
                }

                // TODO:
                // Here use factorOne < ZERO or NEARONE we can get different intersecting circumstances:
                // 1) Step over one vertex
                // 2) Intersect middle part of one line segment
                if(factorOne < ANY_ZERO && factorOne < ANY_NEARONE)
                {
                    crossCount++;
                }
            }
            else    // Parallel or Stacked
            {
                VectorPoint result;
                factorOne = Line2Point(vertices[prev], vertices[next], point, factorTwo, result);
                if(factorOne < ANY_ZERO && factorTwo > -ANY_ZERO && factorTwo < ANY_FARONE)
                {
                    rel = PP_On;
                    break;
                }
            }
        }

        // Ray thoery to get ...
        if(rel != PP_On)
        {
            rel = (crossCount % 2) ? PP_In : PP_Out;
        }

        return rel;
    }

    /*!
    * Use simple and quick way to decide whether one point pointing to one farest point cross one linear segment of polygon
    * 
    * TODO: 
    * Check whether the standards for testifying whether one point cross one linear segment
    */
    template<typename T>
    short CVectOP<T>::Point2Polygon(const VectorPoint *vertices, int count, const VectorPoint &point)
    {
        // Exception check
        if(!vertices || count < 2)
        {
            return PP_Invalid;
        }

        // Loop each two continuous points ...
        unsigned short indicator = 0;
        VectorPoint next = vertices[count - 1];
        int i = 0;
        for(; i < count; i++)
        {
            VectorPoint prev = next;
            next = vertices[i];

			if(point.m_y==prev.m_y && point.m_y== next.m_y)//horizontal
			{
				if((next.m_x <= point.m_x && point.m_x <= prev.m_x) || (prev.m_x <= point.m_x && point.m_x <= next.m_x))
				{
					indicator=1;
					break;
				}
			}
			if(point.m_x==prev.m_x && point.m_x== next.m_x)//vertical
			{
				if((next.m_y <= point.m_y && point.m_y <= prev.m_y) || (prev.m_y <= point.m_y && point.m_y <= next.m_y))
				{
					indicator=1;
					break;
				}
			}
            // Continue to find until Y direction has difference for performance issue
            if(prev.m_y == next.m_y)
            {
                continue;
            }

            // Simple and quick to decide whether one point cross one linear segment
            if(((next.m_y <= point.m_y && point.m_y < prev.m_y) || ((prev.m_y <= point.m_y && point.m_y < next.m_y))) && 
                (point.m_x < ((prev.m_x - next.m_x) * (point.m_y - next.m_y)/(prev.m_y - next.m_y) + next.m_x)))
            {
                indicator = (indicator + 1) % 2;
            }
        }

        // Ray theory
        return indicator;
    }

    /*!
    * Loop both linear segments and get two parallel lines for them then get new corner points under different spatial relationship between
    * new parallel lines
    *
    * TODO:
    * Add different exceptions
    */
    template<typename T>
    short CVectOP<T>::MakeBufferLine(const VectorPoint *vertices, int count, double bufferWidth, short leftRight, VectorPoint **bufferVertices, int &bufferCount)
    {
        // Exception check
        if(!vertices || count < 2)
        {
            return -1;
        }

        // New temporal storage space and condition preparation
        // The desired size of new stroage space is (count<<1 + 1)
        // TODO:
        // Five may ben't enough to storage new points, need to change below algorithm
        VectorPoint *tempVertices = new VectorPoint[count * 2 + 5];
        if(!tempVertices)
        {
            return -1;
        }

        // Buffer width limitation
        if(bufferWidth < m_minBuffWidth)
        {
            bufferWidth = m_minBuffWidth;
        }
        else if(bufferWidth > m_maxBuffWidth)
        {
            bufferWidth = m_maxBuffWidth;
        }
        
        // Loop two linear segments ...
        bufferCount = 0;
        CGeoPoint<double> result, resultOne, resultTwo, resultThree, resultFour;
        double leftRightAngle = leftRight * Deg2Rad(90.0);

		//
		int i = 1;
        double angle = Angle(vertices[i-1], vertices[i]);
        Rotate(bufferWidth, angle + leftRightAngle, vertices[i-1], resultOne);
        Rotate(bufferWidth, angle + leftRightAngle, vertices[i], resultTwo);
		tempVertices[bufferCount++] = resultOne;

        i++;
        for(; i < count; i++)
        {
            double angle = Angle(vertices[i-1], vertices[i]);
            Rotate(bufferWidth, angle + leftRightAngle, vertices[i-1], resultThree);
            Rotate(bufferWidth, angle + leftRightAngle, vertices[i], resultFour);

			if(MagSquare(resultTwo, resultThree) < 0.001)
			{
				result = tempVertices[bufferCount++] = resultThree;
				continue;
			}

            // TODO: ...
            // Performance issue caused here we only need to knoe line spatial relationship not full information
            double factorOne = 0.0;
            double factorTwo = 0.0;
            if(Line2Line(resultOne, resultTwo, resultThree, resultFour, factorOne, factorTwo, result) != LL_Intersect)
            {
				continue;
            }
			else
			{
				if(factorTwo > 0.9999999)
				{
					continue;
				}

				if(factorOne < 0.0000001)
				{
					resultTwo = resultFour;
					continue;
				}

				tempVertices[bufferCount++] = result;
				resultOne = result;
				resultTwo = resultFour;
			}
        }
        tempVertices[bufferCount++] = resultTwo;

        //
        if(*bufferVertices)
        {
            delete [](*bufferVertices);
        }

        *bufferVertices = new VectorPoint[bufferCount];
        if(!(*bufferVertices))
        {
            delete []tempVertices;
            return -1;
        }
        ::memcpy((*bufferVertices), tempVertices, sizeof(VectorPoint) * bufferCount);
        delete []tempVertices;

        return 1;
    }

    /*!
    * Use the principle of the distance of line to one point embodied by Line2Point(...) function
    * 
    * TODO: ...
    * Add corresponding exceptions
    */
    template<typename T>
    short CVectOP<T>::GetInnerIdx(const VectorPoint *vertices, int count, const VectorPoint &point, double tolerance, VectorPoint &result, short cyclic)
    {
        // Exception check
        if(!vertices || count <= 1)
        {
            return -1;
        }

        // Initialization of starting point under different circumstances: is polygon or not
        int innerIdx = 0;
        int order = 0;
        CGeoPoint<double> prev, next;
        if(cyclic)
        {
            innerIdx = count;
            prev.m_x = static_cast<double>(vertices[innerIdx - 1].m_x);
            prev.m_y = static_cast<double>(vertices[innerIdx - 1].m_y);
            order = 0;
        }
        else
        {
            innerIdx = 1;
            prev.m_x = static_cast<double>(vertices[0].m_x);
            prev.m_y = static_cast<double>(vertices[0].m_y);
            order = 1;
        }

        // Loop each line segment to find which ending points is nearst to specified point
        bool bFind = false;
        double minDist = ANY_MAXVALUE;
        for(; order < count; order++)
        {
            // Omit the same points
            next.m_x = static_cast<double>(vertices[order].m_x);
            next.m_y = static_cast<double>(vertices[order].m_y);
            if(next == prev)
            {
                continue;
            }

            // One linear segment to specified point
            double factor = 0.0;
            double dist = Line2Point(prev, next, point, factor, result);
            if(factor >= 0.0 && factor <= 1.0)
            {
                // There shouldn't only one chance to find which point is the neast to specified point,
                if(/*!bFind ||*/ dist < minDist)
                {
                    minDist = dist;
                    bFind = true;
                    innerIdx = (factor > 0.5) ? order : (order - 1);
                }
            }

            prev = next;
        }

        // The last chance
        if(bFind && minDist < tolerance)
        {
            return innerIdx;
        }

        return -1;
    }

}

#endif
