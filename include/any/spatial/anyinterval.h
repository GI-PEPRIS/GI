/*!
 * The AnyIndex of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages, especially for those quick
 * spatial algorithms.
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
#ifndef __ANYINDEX_INTERVAL_H__
#define __ANYINDEX_INTERVAL_H__
 
// namespace
namespace AnyIndex
{
	/*!
    * \class CAnyInterval
    *
    * \brief
    * Provides a test for whether an interval is
    * so small it should be considered as zero for the purposes of
    * inserting it into a binary tree.
    *
    * The reason this check is necessary is that round-off error can
    * cause the algorithm used to subdivide an interval to fail, by
    * computing a midpoint value which does not lie strictly between the
    * endpoints.
	 */
    class CAnyInterval
	{
        // The definition of min width
		static const int MIN_BINARY_EXPONENT = -50;

    public:
        //
        // Ctrs & dctr
        //
		/*!
		*
		**/
		CAnyInterval();

        /*!
        * Copy constructor
        *
        * \para other, another interval object
        **/
        CAnyInterval(const CAnyInterval &other);

        /*!
        * Default constructor with two parameter
        * 
        * \para min, the minimum of a given coordinate
        * \para max, the maximum of a given coordinate
        **/
        CAnyInterval(double min, double max);

        /*!
        * \brief
        * Declaration for its sub classes if it has
        **/
        virtual ~CAnyInterval();

		/*!
		* Object assignment 
		**/
		const CAnyInterval &operator=(const CAnyInterval &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_min = other.m_min;
			m_max = other.m_max;

			return *this;
		}

    public:
        //
        // Basic set and access functions
        //
		/*!
		*
		**/
		void Init(double min, double max)
		{
			m_min = min;
			m_max = max;
		}

        /*!
        *
        **/
        double GetMin() const
        {
            return m_min;
        }

        /*!
        *
        **/
        double GetMax() const
        {
            return m_max;
        }

		/*!
		*
		**/
		double GetWidth() const
		{
			return m_max - m_min;
		}

        //
        // Interval calculation functions 
        //		
        /*!
        * \return the "middle" value of this interval object
        **/
        virtual double GetCenter() const;

        /*!
        * \brief
        * Merge two interval objects
        *
        * \para other, another interval object
        * \return the latest spatial definition of this interval object
        **/
        const CAnyInterval &ExpandToInclude(const CAnyInterval &other);

        //
        // Interval logic operations
        //
        /*!
        * \brief
        * Whether two interval objects intersect
        *
        * \para other, another interval object
        **/
        virtual bool IsIntersect(const CAnyInterval &other) const;

        /*!
        * \brief
        * Whether two interval objects is the same object or
        * has the same spatial definition
        *
        * \para other, another interval object
        **/
        virtual bool IsEqual(const CAnyInterval &other) const;


        /*!
        * \brief
        * Whether two interval objects is the same object or
        * has the same spatial definition
        *
        * \para other, another interval object
        **/
        virtual bool IsContain(const CAnyInterval &other) const;

	public:
		//
		// Overloading methods 
		//
		/*!
		*
		**/
		bool operator != (const CAnyInterval &other)
		{
			double limited = (2 >> MIN_BINARY_EXPONENT);
			return (((m_min - other.m_min) > limited) || ((m_max - other.m_max) > limited));
		}

		/*!
		*
		**/
		bool operator == (const CAnyInterval &other)
		{
			return !(*this != other);
		}

        //
        // Class behaviors
        //
		 /*!
         * \brief
         * This value is chosen to be a few powers of 2 less than the
		 * number of bits available in the double representation (i.e. 53).
		 * This should allow enough extra precision for simple computations
		 * to be correct, at least for comparison purposes.
         */
		static bool IsZeroWidth(double min, double max);

    private:
        // The minimum value of a given coordinate
        double m_min;
        // The maximum value of a given coordinate
        double m_max;
	};
}
#endif