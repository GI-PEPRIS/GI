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
#ifndef __ANYBASE_LOKI_TYPELIST_H__
#define __ANYBASE_LOKI_TYPELIST_H__

// Refer to NullType etc basic generic definition
#include "generic.h"

// Anybase namespace
namespace AnyBase
{
    // Loki namespace 
	// Implementation of the ThreadingModel policy used by various classes
	// Implements a single-threaded model; no synchronization
    // ...
    //macros TYPELIST_1, TYPELIST_2, ... TYPELIST_50
    //Each takes a number of arguments equal to its numeric suffix
    //The arguments are type names. TYPELIST_NN generates a typelist containing all types passed as arguments, in that order.
    //Example: TYPELIST_2(char, int) generates a type containing char and int.
	namespace Loki
	{
        // Macroes for different type set, and its maximum size is 50
		#define TYPELIST_1(T1) Typelist<T1, NullType>
		#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) >
		#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
		#define TYPELIST_4(T1, T2, T3, T4) \
			Typelist<T1, TYPELIST_3(T2, T3, T4) >
		#define TYPELIST_5(T1, T2, T3, T4, T5) \
			Typelist<T1, TYPELIST_4(T2, T3, T4, T5) >
		#define TYPELIST_6(T1, T2, T3, T4, T5, T6) \
			Typelist<T1, TYPELIST_5(T2, T3, T4, T5, T6) >
		#define TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) \
			Typelist<T1, TYPELIST_6(T2, T3, T4, T5, T6, T7) >
		#define TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) \
			Typelist<T1, TYPELIST_7(T2, T3, T4, T5, T6, T7, T8) >
		#define TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
			Typelist<T1, TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9) >
		#define TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) \
			Typelist<T1, TYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10) >
		#define TYPELIST_11(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) \
			Typelist<T1, TYPELIST_10(T2, T3, T4, T5, T6, T7, T8, T9, T10, T11) >
		#define TYPELIST_12(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12) \
			Typelist<T1, TYPELIST_11(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12) >
		#define TYPELIST_13(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13) \
			Typelist<T1, TYPELIST_12(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13) >
		#define TYPELIST_14(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14) \
			Typelist<T1, TYPELIST_13(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14) >
		#define TYPELIST_15(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15) \
			Typelist<T1, TYPELIST_14(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15) >
		#define TYPELIST_16(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16) \
			Typelist<T1, TYPELIST_15(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16) >
		#define TYPELIST_17(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17) \
			Typelist<T1, TYPELIST_16(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17) >
		#define TYPELIST_18(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18) \
			Typelist<T1, TYPELIST_17(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18) >
		#define TYPELIST_19(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19) \
			Typelist<T1, TYPELIST_18(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19) >
		#define TYPELIST_20(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) \
			Typelist<T1, TYPELIST_19(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20) >
		#define TYPELIST_21(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) \
			Typelist<T1, TYPELIST_20(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21) >
		#define TYPELIST_22(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) \
			Typelist<T1, TYPELIST_21(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22) >
		#define TYPELIST_23(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) \
			Typelist<T1, TYPELIST_22(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23) >
		#define TYPELIST_24(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) \
			Typelist<T1, TYPELIST_23(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24) >
		#define TYPELIST_25(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25) \
			Typelist<T1, TYPELIST_24(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25) >
		#define TYPELIST_26(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26) \
			Typelist<T1, TYPELIST_25(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26) >
		#define TYPELIST_27(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27) \
			Typelist<T1, TYPELIST_26(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27) >
		#define TYPELIST_28(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28) \
			Typelist<T1, TYPELIST_27(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28) >
		#define TYPELIST_29(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29) \
			Typelist<T1, TYPELIST_28(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29) >
		#define TYPELIST_30(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) \
			Typelist<T1, TYPELIST_29(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30) >
		#define TYPELIST_31(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) \
			Typelist<T1, TYPELIST_30(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31) >
		#define TYPELIST_32(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) \
			Typelist<T1, TYPELIST_31(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32) >
		#define TYPELIST_33(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) \
			Typelist<T1, TYPELIST_32(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33) >
		#define TYPELIST_34(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) \
			Typelist<T1, TYPELIST_33(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, T34) >
		#define TYPELIST_35(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35) \
			Typelist<T1, TYPELIST_34(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35) >
		#define TYPELIST_36(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36) \
			Typelist<T1, TYPELIST_35(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36) >
		#define TYPELIST_37(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37) \
			Typelist<T1, TYPELIST_36(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37) >
		#define TYPELIST_38(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38) \
			Typelist<T1, TYPELIST_37(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38) >
		#define TYPELIST_39(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39) \
			Typelist<T1, TYPELIST_38(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39) >
		#define TYPELIST_40(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) \
			Typelist<T1, TYPELIST_39(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40) >
		#define TYPELIST_41(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) \
			Typelist<T1, TYPELIST_40(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41) >
		#define TYPELIST_42(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) \
			Typelist<T1, TYPELIST_41(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42) >
		#define TYPELIST_43(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) \
			Typelist<T1, TYPELIST_42(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43) >
		#define TYPELIST_44(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) \
			Typelist<T1, TYPELIST_43(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44) >
		#define TYPELIST_45(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45) \
			Typelist<T1, TYPELIST_44(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45) >
		#define TYPELIST_46(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46) \
			Typelist<T1, TYPELIST_45(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46) >
		#define TYPELIST_47(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47) \
			Typelist<T1, TYPELIST_46(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47) >
		#define TYPELIST_48(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47, T48) \
			Typelist<T1, TYPELIST_47(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47, T48) >
		#define TYPELIST_49(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47, T48, T49) \
			Typelist<T1, TYPELIST_48(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47, T48, T49) >
		#define TYPELIST_50(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) \
			Typelist<T1, TYPELIST_49(T2, T3, T4, T5, T6, T7, T8, T9, T10, \
				T11, T12, T13, T14, T15, T16, T17, T18, T19, T20, \
				T21, T22, T23, T24, T25, T26, T27, T28, T29, T30, \
				T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, \
				T41, T42, T43, T44, T45, T46, T47, T48, T49, T50) >

		/*!
        * \brief
		* The building block of typelists of any length
		* Use it through the TYPELIST_NN macros
		* Defines nested types:
		*     Head (first element, a non-typelist type by convention)
		*     Tail (second element, can be another typelist)
		**/
		template <class T, class U>
		struct Typelist
		{
		   typedef T Head;
		   typedef U Tail;
		};

		/*!
        * \brief
		* Takes a number of arguments equal to its numeric suffix
		* The arguments are type names.
		* MakeTypeList<T1, T2, ...>::Result
		* returns a typelist that is of T1, T2, ...
		*/
		template
		<
			typename T1  = NullType, typename T2  = NullType, typename T3  = NullType,
			typename T4  = NullType, typename T5  = NullType, typename T6  = NullType,
			typename T7  = NullType, typename T8  = NullType, typename T9  = NullType,
			typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
			typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
			typename T16 = NullType, typename T17 = NullType, typename T18 = NullType
		> 
		struct MakeTypeList
		{
		private:
			// Defint tail type set
			typedef typename MakeTypeList
			<
				T2 , T3 , T4 , 
				T5 , T6 , T7 , 
				T8 , T9 , T10, 
				T11, T12, T13,
				T14, T15, T16, 
				T17, T18
			>::Result TailResult;

		public:
			// Recursive definition for all types using above macroes
			typedef Typelist<T1, TailResult> Result;
		};

		/*!
		* \brief
		* Special implementation
		**/
		template<>
		struct MakeTypeList
		<
			NullType, NullType, NullType, 
			NullType, NullType, NullType, 
			NullType, NullType, NullType, 
			NullType, NullType, NullType,
			NullType, NullType, NullType,
			NullType, NullType, NullType
		>
		{
			typedef NullType Result;
		};
		
		/*!
		* \brief
		* Detects if type is Typelist (including Nulltype)
		* Invocation :
		* IsTypeList<T>::value
		* returns a compile-time boolean constant containing true if T is some Typelist<T1,T2>
		* IsTypeList<T>::type_id
		* returns a compile-time unsigned constant containing 
		* 1 if T == Typelist<T1,T2>, 2 if T == NullType and 3 otherwise
		**/
		struct Typelist_tag {};
		struct NullType_tag {};
		struct NoneList_tag {};

		template<typename T>
		struct IsTypeList
		{
		private:
			// Define different size of char array as return type of overloading functions, whose parameters
			// is ready to mention what its type is
			enum 
			{
				Typelist_ID = 1,
				NullType_ID = 2,
				NoneList_ID = 3
			};
			typedef char (&ye1)[Typelist_ID];
			typedef char (&ye2)[NullType_ID];
			typedef char (&no) [NoneList_ID];

			// Overloading functions using its different parameter types
			template<typename Head, typename Tail>
			static ye1 check(Type2Type< Typelist<Head, Tail> >);
			static ye2 check(Type2Type<NullType>);
			static no  check(...);

		public:
			// VC7 fail NPS_HierarchyGenerators.h if this one is enum
			static const unsigned int type_id = sizeof(check( Type2Type<T>() ));
			enum { value = type_id != sizeof(no) };

			// According its value to declare it reall type kinds: typelist, null type or nothing
			typedef typename SelectType
			<
				type_id == Typelist_ID, 
				Typelist_tag,
				typename SelectType<type_id == NullType_ID, NullType_tag, NoneList_tag>::Result
			> ::Result type_tag;
		};

		// this macro will cause compile time error if _type_ is not a Typelist or NullType
        // Note: 
        // The first marceo means always true and assure comipling process in higher process
		//#define ASSERT_TYPELIST(_type_)  typedef char _type_##_is_not_a_Typelist[true]
        #define ASSERT_TYPELIST(_type_) LOKI_ASSERT_MSG(IsTypeList<_type_>::value, TList_is_not_legal_Typelist)

		/*!
		* \brief
		* Computes the length of a typelist
		* Invocation (TList is a typelist):
		* Length<TList>::value
		* returns a compile-time constant containing the length of TList, not counting
		*     the end terminator (which by convention is NullType)
		*/
		template <class TList> struct Length;

		/*!
		* Ending condition
		**/
		template <> 
		struct Length<NullType>
		{
			enum { value = 0 };
		};

		/*!
		* Recursive deduction
		**/
        template <class T, class U>
        struct Length< Typelist<T, U> >
        {
            enum { value = 1 + Length<U>::value };
        };

		//template <class TList>
		//struct Length
		//{
		//private:
		//	ASSERT_TYPELIST(TList);
		//    
		//	typedef typename TList::Head Head;
		//	typedef typename TList::Tail Tail;

		//public:
		//	enum { value = 1 + Length<Tail>::value };
		//};

		/*!
		* \brief
		* Finds the type at a given index in a typelist
		* Invocation (TList is a typelist and index is a compile-time integral constant):
		* TypeAt<TList, index>::Result
		* returns the type in position 'index' in TList
		* If you pass an out-of-bounds index, the result is a compile-time error
		**/
		template <class TList, unsigned int index> 
		struct TypeAt
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<unsigned int i>
			struct In
			{
				typedef typename TypeAt<Tail, i - 1>::Result Result;
			};

			template<>
			struct In<0>
			{
				typedef Head Result;
			};

		public:
			typedef typename In<index>::Result Result;
		};
    
		/*!
		* \brief
		* Finds the type at a given index in a typelist
		* Invocations (TList is a typelist and index is a compile-time integral constant):
		* a) TypeAt<TList, index>::Result
		* returns the type in position 'index' in TList, or NullType if index is out-of-bounds
		* b) TypeAt<TList, index, D>::Result
		* returns the type in position 'index' in TList, or D if index is out-of-bounds
		**/
		template <class TList, unsigned int index, typename DefaultType = NullType> 
		struct TypeAtNonStrict
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1, unsigned int i>
			struct In
			{
				typedef typename TypeAtNonStrict
				<
					typename TList1::Tail, 
					i - 1,
					DefaultType
				>
				::Result Result;
			};

			template<>
			struct In<Typelist<Head, Tail>, 0>
			{
				typedef Head Result;
			};

			template<>
			struct In<NullType, index>
			{
				typedef DefaultType Result;
			};
		public:
			typedef typename In<TList, index>::Result Result;
		};

		/*!
		* \brief
		* Finds the index of a type in a typelist
		* Invocation (TList is a typelist and T is a type):
		* IndexOf<TList, T>::value
		* returns the position of T in TList, or NullType if T is not found in TList
		**/
		template <class TList, class T> 
		struct IndexOf
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1>
			struct In
			{
			private:
				typedef typename TList1::Tail Tail;

				enum { temp = (IndexOf<Tail, T>::value) };

			public:
				enum { value = temp == -1 ? -1 : 1 + temp  };
			};

			template<>
			struct In< Typelist<T, Tail> >
			{
				enum { value = 0 };
			};

			template<>
			struct In<NullType>
			{
				enum { value = -1 };
			};

		public:
			enum { value = In<TList>::value };
		};

		/*!
		* Appends a type or a typelist to another
		* Invocation (TList is a typelist and T is either a type or a typelist):
		* Append<TList, T>::Result
		* returns a typelist that is TList followed by T and NullType-terminated
		**/
		template <class TList, class T> 
		struct Append
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1>
			struct In
			{
				typedef typename TList1::Tail Tail;

				typedef Typelist
				<
					Head, 
					typename Append<Tail, T>::Result
				> 
				Result;
			};

			template<>
			struct In<NullType>
			{
				typedef typename SelectType
				<
					IsTypeList<T>::value, 
					T, TYPELIST_1(T) 
				>
				::Result Result;
			};

		public:
			typedef typename In<TList>::Result Result;
		};
    
		/*!
		* Erases the first occurence, if any, of a type in a typelist
		* Invocation (TList is a typelist and T is a type):
		* Erase<TList, T>::Result
		* returns a typelist that is TList without the first occurence of T
		**/
		template <class TList, class T> 
		struct Erase
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1>
			struct In
			{
				typedef typename TList1::Tail Tail;

				typedef Typelist
				<
					Head, 
					typename Erase<Tail, T>::Result
				>
				Result;
			};

			template<>
			struct In< Typelist<T, Tail> >
			{
				typedef Tail Result;
			};

			template<>
			struct In<NullType>
			{
				typedef NullType Result;
			};

		public:
			typedef typename In<TList>::Result Result;
		};

		/*!
		* Erases all first occurences, if any, of a type in a typelist
		* Invocation (TList is a typelist and T is a type):
		* EraseAll<TList, T>::Result
		* returns a typelist that is TList without any occurence of T
		**/
		template <class TList, class T> 
		struct EraseAll
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1>
			struct In
			{
			private:
				typedef typename TList1::Tail Tail;
				typedef typename EraseAll<Tail, T>::Result TailResult;
		    
			public:
				typedef typename SelectType
				<
					IsSameType<Head, T>::value,
					TailResult,
					Typelist<Head, TailResult>
				>
				::Result Result;
			};

			template<>
			struct In<NullType>
			{
				typedef NullType Result;
			};

		public:
			typedef typename In<TList>::Result Result;
		};

		/**
		* Removes all duplicate types in a typelist
		* Invocation (TList is a typelist):
		* NoDuplicates<TList, T>::Result
		**/
		template <class TList> 
		struct NoDuplicates
		{
		private:
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

			ASSERT_TYPELIST(TList);

			typedef typename NoDuplicates<Tail>::Result L1;
			typedef typename Erase<L1, Head>::Result    L2;

		public:
			typedef Typelist<Head, L2> Result;
		};

		template <> 
		struct NoDuplicates<NullType>
		{
			typedef NullType Result;
		};

		/**
		* Replaces the first occurence of a type in a typelist, with another type
		* Invocation (TList is a typelist, T, U are types):
		* Replace<TList, T, U>::Result
		* returns a typelist in which the first occurence of T is replaced with U
		**/
		template <class TList, class T, class U> 
		struct Replace
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1>
			struct In
			{
				typedef typename TList1::Tail Tail;

				typedef Typelist
				<
					Head, 
					typename Replace<Tail, T, U>::Result
				>
				Result;
			};

			template<>
			struct In< Typelist<T, Tail> >
			{
				typedef Typelist<U, Tail> Result;
			};

			template<>
			struct In<NullType>
			{
				typedef NullType Result;
			};

		public:
			typedef typename In<TList>::Result Result;
		};

		/**
		* Replaces all occurences of a type in a typelist, with another type
		* Invocation (TList is a typelist, T, U are types):
		* Replace<TList, T, U>::Result
		* returns a typelist in which all occurences of T is replaced with U
		**/
		template <class TList, class T, class U> 
		struct ReplaceAll
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1>
			struct In
			{
			private:
				typedef typename TList1::Tail Tail;
				typedef typename ReplaceAll<Tail, T, U>::Result TailResult;
		    
			public:
				typedef typename SelectType
				<
					IsSameType<Head, T>::value,
					Typelist<U,    TailResult>,
					Typelist<Head, TailResult>
				>
				::Result Result;
			};

			template<>
			struct In<NullType>
			{
				typedef NullType Result;
			};

		public:
			typedef typename In<TList>::Result Result;
		};

		/**
		* Reverses a typelist
		* Invocation (TList is a typelist):
		* Reverse<TList>::Result
		* returns a typelist that is TList reversed
		**/
		template <class TList> struct Reverse;

		template <>
		struct Reverse<NullType>
		{
			typedef NullType Result;
		};

		template <class TList> 
		struct Reverse
		{
		private:
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

			ASSERT_TYPELIST(TList);

		public:
			typedef typename Append<
				typename Reverse<Tail>::Result, Head>::Result Result;
		};


		/**
		* Finds the type in a typelist that is the most derived from a given type
		* Invocation (TList is a typelist, T is a type):
		* Replace<TList, T>::Result
		* returns the type in TList that's the most derived from T
		**/
		template <class TList, class T> 
		struct MostDerived
		{
			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

		private:
			ASSERT_TYPELIST(TList);

			template<class TList1>
			struct In
			{
			private:
				typedef typename TList1::Tail Tail;
				typedef typename TList1::Head Head;
				typedef typename MostDerived<Tail, T>::Result Candidate;
		    
			public:
				typedef typename SelectType
				<
					LOKI_ISSUBCLASS(Candidate, Head),
					Head, Candidate
				>
				::Result Result;
			};

			template<>
			struct In<NullType>
			{
				typedef T Result;
			};

		public:
			typedef typename In<TList>::Result Result;
		};
    
		/**
		* Arranges the types in a typelist so that the most derived types appear first
		* Invocation (TList is a typelist):
		* DerivedToFront<TList>::Result
		* returns the reordered TList 
		**/
		template <class TList> struct DerivedToFront;

		template <>
		struct DerivedToFront<NullType>
		{
			typedef NullType Result;
		};

		template <class TList>
		struct DerivedToFront
		{
		private:
			ASSERT_TYPELIST(TList);

			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

			typedef typename MostDerived<Tail, Head>::Result TheMostDerived;
			typedef typename Replace<Tail, TheMostDerived, Head>::Result Temp;
			typedef typename DerivedToFront<Temp>::Result L;

		public:
			typedef Typelist<TheMostDerived, L> Result;
		};
		        
		/*!
		* \brief
		* Arranges all the types in a typelist so that the most derived types appear first
		* Invocation (TList is a typelist):
		* DerivedToFront<TList>::Result
		* returns the reordered TList 
		**/
		template <class TList> struct DerivedToFrontAll;

		template <>
		struct DerivedToFrontAll<NullType>
		{
			typedef NullType Result;
		};

		template <class TList>
		struct DerivedToFrontAll
		{
		private:
			ASSERT_TYPELIST(TList);

			typedef typename TList::Head Head;
			typedef typename TList::Tail Tail;

			typedef typename MostDerived<Tail, Head>::Result TheMostDerived;
			typedef typename Replace<Tail, TheMostDerived, Head>::Result L;
		    
			typedef typename DerivedToFrontAll<L>::Result TailResult;

		public:
			typedef Typelist<TheMostDerived, TailResult> Result;
		};
	} // Loki
} // Anybase
#endif

