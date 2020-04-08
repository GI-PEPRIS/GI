/*!
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
 * herman.sheng@gmail.com
 */
#ifndef __ANYBASE_MATH_BASIC_H__
#define __ANYBASE_MATH_BASIC_H__

// Refer to EXPORT & IMPORT macroes
#include "anybase.h"

// 
namespace AnyBase
{
	/*!
	* One suite of quick math algorithms better than general library.
	*/
	class ANYBASE_CLASS CAnyMathBasic
	{
		//
		static const int BITSPERLONG = 32;
		#define TOP2BITS(x) ((x & (3L << (BITSPERLONG-2))) >> (BITSPERLONG-2))
		struct int_sqrt
		{
			unsigned short	fract;
			unsigned short	sqrt;
		};

		// No any other automatically and implicitly creation
		CAnyMathBasic(const CAnyMathBasic &other);
		void operator=(const CAnyMathBasic &other);

		/*!
		*
		**/
		CAnyMathBasic()
		{
		}

		/*!
		*
		**/
		~CAnyMathBasic()
		{
		}

	public:
		//
		// Bit operations
		//
		/*!
		* One integer is expressed by at least how many bits.
		*
		*/
		short CLog2(long value) const;

		/*!
		*
		*/
		unsigned long GetMask(short shift, short bits) const;

		//
		// SQRT methods
		//
		/*!
		*
		**/
		unsigned long ISqrt(unsigned long x) const;

		/*!
		*
		**/
		unsigned long USqrt(unsigned long x) const;

		/*!
		* Base on assemble commands for X86 series and this function 
		* is shared by AGG writen by Maxim
		**/
		unsigned long ASqrt(unsigned long x) const;

		/*!
		*
		**/
		long HashCode(long x, long y) const;

		//
		// Quick type conversion
		//
		/*!
		*
		*/
		float AtoF(const char *c) const;

		//
		// Singleton
		//
		const static CAnyMathBasic &Get();

	private:
		// Singleton
		static CAnyMathBasic m_mathBasic;
	};
}
#endif