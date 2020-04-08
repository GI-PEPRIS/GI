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
 * herman.sheng@gmail.com
 */
#ifndef __ANYBASE_PORT_H__
#define __ANYBASE_PORT_H__

// Refer to string definition etc
#include "anystl.h"

// ANSI C headers
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h> 
#include <string.h>
#include <locale.h>
#include <float.h>
#include <tchar.h>

//
#if (_WIN32)
#include <windows.h>
#endif

// stand C declaration
// Note: 
// this macro can't be put above windows.h since it is a strange one as expected
#define __STDC__ 1
//#define _POSIX_ 1

/*!
* String definitions beared to UNICODE or SMBS environment
* Note: below are abridged from <tchar.h> defined by MS and they would carry warning information 
* when being compiled for MS OS
*/
#ifdef  _UNICODE
	typedef wchar_t TCHAR;
	#define anystring std::wstring

    #ifndef _INC_TCHAR     // Exclude the defintion corruption in "tchar.h" 
		#define _T(x) L ## x
    #endif
#else
	typedef char TCHAR;
	#define anystring std::string

    #ifndef _INC_TCHAR     // Exclude the defintion corruption in "tchar.h" 
		#define _T(x) L ## x
    #endif
#endif

// Defines NaN for intel platforms and don't forget to define infinities
#define DoubleNotANumber 1.7e-308
#define DoublePosInfinity 1.7e+308
#define DoubleNegInfinity -1.7e+308
#define ISNAN(x) ::_isnan(x)
#define FINITE(x) _finite(static_cast<double>(x))   

// Useful CPU-dependent mathematical macros
const static double ANY_ZERO = 0.0000001;
const static double ANY_FARONE = 1.0000001;
const static double ANY_NEARONE = 0.99999999;
const static double ANY_MAXVALUE = 0x7FFFFFFF;
const static double ANY_MINVALUE = 0x10000000; 
const static long	ANY_NANSPEC[2] = {0xFFFFFFFF, 0x7FFFFFFF};
const static double ANY_NAN = *(double *)(ANY_NANSPEC);
const static double ANY_INVALIDCOORD = -1.;

 // type against long OS
 typedef long long int int64;

 // kinds of max and mimum
 #define INT_MIN32       (~0x7FFFFFFFL)
#define INT_MAX32       0x7FFFFFFFL
#define UINT_MAX32      0xFFFFFFFFL
#define INT_MIN24       (~0x007FFFFF)
#define INT_MAX24       0x007FFFFF
#define UINT_MAX24      0x00FFFFFF
#define INT_MIN16       (~0x7FFF)
#define INT_MAX16       0x7FFF
#define UINT_MAX16      0xFFFF
#define INT_MIN8        (~0x7F)
#define INT_MAX8        0x7F
#define UINT_MAX8       0xFF

//From limits.h instead
#ifndef DBL_MIN
#define DBL_MIN		4.94065645841246544e-324
#define FLT_MIN		((float)1.40129846432481707e-45)
#endif
#ifndef DBL_MAX
#define DBL_MAX		1.79769313486231470e+308
#define FLT_MAX		((float)3.40282346638528860e+38)
#endif
#ifndef SSIZE_MAX
#define SSIZE_MAX ((~((size_t) 0)) / 2)
#endif

//Define missing math constants.
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.7182818284590452354
#endif
#ifndef M_LN2
#define M_LN2 0.69314718055994530942
#endif

//  Max size that must be added to a so that we know Size to make
//  adressable obj.
#define MY_ALIGN(A,L)	(((A) + (L) - 1) & ~((L) - 1))
#define ALIGN_SIZE(A)	MY_ALIGN((A),sizeof(double))
// Size to make adressable obj.
#define ALIGN_PTR(A, t) ((t*) MY_ALIGN((A),sizeof(t)))
// Offset of field f in structure t
#define OFFSET(t, f)	((size_t)(char *)&((t *)0)->f)
#define ADD_TO_PTR(ptr,size,type) (type) ((byte*) (ptr)+size)
#define PTR_BYTE_DIFF(A,B) (my_ptrdiff_t) ((byte*) (A) - (byte*) (B))

//
//  ATTENTION !
//   
// Please, note, uint3korr reads 4 bytes (not 3) !
// It means, that you have to provide enough allocated space !
#define uint3korr(A)	(long) (*((unsigned int *) (A)) & 0xFFFFFF)
#define uint4korr(A)	(*((unsigned long *) (A)))
#define uint5korr(A)	((ulonglong)(((uint32) ((uchar) (A)[0])) +\
				    (((uint32) ((uchar) (A)[1])) << 8) +\
				    (((uint32) ((uchar) (A)[2])) << 16) +\
				    (((uint32) ((uchar) (A)[3])) << 24)) +\
				    (((ulonglong) ((uchar) (A)[4])) << 32))
#define uint8korr(A)	(*((ulonglong *) (A)))
#define sint8korr(A)	(*((longlong *) (A)))
#define int2store(T,A)	*((uint16*) (T))= (uint16) (A)
#define int3store(T,A)		{ *(T)=  (uchar) ((A));\
				  *(T+1)=(uchar) (((uint) (A) >> 8));\
				  *(T+2)=(uchar) (((A) >> 16)); }
#define int4store(T,A)	*((long *) (T))= (long) (A)
#define int5store(T,A)	{ *(T)= (uchar)((A));\
			  *((T)+1)=(uchar) (((A) >> 8));\
			  *((T)+2)=(uchar) (((A) >> 16));\
			  *((T)+3)=(uchar) (((A) >> 24)); \
			  *((T)+4)=(uchar) (((A) >> 32)); }
#define int8store(T,A)	*((ulonglong *) (T))= (ulonglong) (A)

#define doubleget(V,M)	do { *((long *) &V) = *((long*) M); \
			    *(((long *) &V)+1) = *(((long*) M)+1); } while(0)
#define doublestore(T,V) do { *((long *) T) = *((long*) &V); \
			      *(((long *) T)+1) = *(((long*) &V)+1); } while(0)
#define float4get(V,M) { *((long *) &(V)) = *((long*) (M)); }
#define floatstore(T,V) memcpy((byte*)(T), (byte*)(&V), sizeof(float))
#define floatget(V,M)   memcpy((byte*)(&V), (byte*)(M), sizeof(float))
#define float8get(V,M) doubleget((V),(M))
#define float4store(V,M) memcpy((byte*) V,(byte*) (&M),sizeof(float))
#define float8store(V,M) doublestore((V),(M))

// last
#endif