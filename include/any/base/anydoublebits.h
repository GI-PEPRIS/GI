/*!
 * The AnyBase package of PetroCOVERY Solution is a collection of native C++ classes that 
 * implement the fundamental algorithms & operations required to 
 * satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_DOUBLE_BITS_H__
#define __ANYBASE_DOUBLE_BITS_H__

// Export and import macro def
#include "anybase.h"

// refer to unsigned long long
#include "anyport.h"

// namespace AnyBase
namespace AnyBase
{
	/*!
	*
	**/
	class ANYBASE_CLASS CAnyDoubleBits
	{
		//
		static const int EXPONENT_BIAS = 1023;

	public:
		/*!
		*
		**/
		CAnyDoubleBits(double value);

		/*!
		*
		**/
		~CAnyDoubleBits();

		/**
		* Copy constructor & operator =.
		*
		* No any secenes to let this class occur except for the initialization of static variable.
		*/
		CAnyDoubleBits(const CAnyDoubleBits &other);
		const CAnyDoubleBits &operator=(const CAnyDoubleBits &other);

	public:
		//
		//
		//
		/*!
		*
		**/
		double GetDouble();

		/*!
		*
		**/
		int64 BiasedExponent();

		/*!
		*
		**/
		int64 GetExponent();

		/*!
		*
		**/
		void ZeroLowerBits(int nBits);

		/*!
		*
		**/
		int GetBit(int order) const;

		/*!
		*
		**/
		int NumCommonMantissaBits(const CAnyDoubleBits &db);

		/*!
		*
		**/
		string ToString();

	public:
		//
		// class's behaviors
		// 
		/*!
		*
		**/
		static double PowerOf2(int exp);

		/*!
		*
		**/
		static int Exponent(double d);

		/*!
		*
		**/
		static double TruncateToPowerOfTwo(double d);

		/*!
		*
		**/
		static string ToBinaryString(double d);

		/*!
		*
		**/
		static double MaximumCommonMantissa(double d1, double d2);

	private:
		double m_x;
		int64 m_xBits;
	};
}

#endif

