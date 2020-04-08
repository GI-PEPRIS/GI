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
#ifndef __ANYSPATIALINDEX_DOUBLEBITS_H__
#define __ANYSPATIALINDEX_DOUBLEBITS_H__

// Spatial index package
namespace AnyIndex
{
    /*! 
    * \brief
    * DoubleBits manipulates Double numbers
    * by using bit manipulation and bit-field extraction.
    *
    * For some operations (such as determining the exponent)
    * this is more accurate than using mathematical operations
    * (which suffer from round-off error).
    * 
    * The algorithms and constants in this class
    * apply only to IEEE-754 double-precision floating point format.
    *
    */
	class CAnyDoubleBits 
	{
		// Exponent base in IEEE standard for double
		static const int EXPONENT_BIAS = 1023;

	public:
		//
		// Ctrs & dctr
		//
		/*!
		*
		**/
		CAnyDoubleBits(double number);

	public:
		//
		//
		//
		/*!
		*
		**/
		double GetDouble() const;

		/*!
		* Determines the exponent for the number
		**/
		__int64 BiasedExponent() const;

		/*!
		* Determines the exponent for the number
		**/
		int GetExponent() const;

		/*!
		*
		**/
		void ZeroLowerBits(int nBits);

		/*!
		*
		**/
		int GetBit(int i) const;

		/*!
		* \brief
		* This computes the number of common most-significant bits in
		* the mantissa.
		*
		* It does not count the hidden bit, which is always 1.
		* It does not determine whether the numbers have the same exponent;
		* if they do not, the value computed by this function is meaningless.
		*
		* @param db
		*
		* @return the number of common most-significant mantissa bits
		*/
		int NumCommonMantissaBits(const CAnyDoubleBits& oneNumber) const;

		//
		// Class behaviors : Utility functions
		//
		/*!
		*
		**/
		static double PowerOfTwo(int exp);

		/*!
		*
		**/
		static int Exponent(double d);

		/*!
		*
		**/
		static double TruncateToPowerOfTwo(double d);


		/**
		*
		**/
		static double MaximumCommonMantissa(double firstNumber, double secondNumber);

	private:
		// Current double value, generally represent the width or height of current envelope
		double m_xNumber;

		// Its correspondence bits on behalf of above double value
		__int64 m_xBits;
	};
} 
#endif