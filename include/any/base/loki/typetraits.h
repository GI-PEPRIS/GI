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
#ifndef __ANYBASE_LOKI_TYPETRAITS_H__
#define __ANYBASE_LOKI_TYPETRAITS_H__

// Refer to TypeList definition and its typical operations
#include "typelist.h"

// Anybase namespace
 namespace AnyBase
{
    // Loki namespace inside Anybase
    // None of the parameter types are defined inside of TypeTraits, e.g. PointeeType, ReferredType, etc...
    // ...
	// Note:
	// This include file is benefited from the ideas of "Modern C++" written by  by Andrei Alexandrescu
	namespace Loki
	{
		/*!
        * \brief
		* Offers a means to integrate nonstandard built-in unsigned integral types
		* (such as unsigned __int64 or unsigned long long int) with the TypeTraits class template defined below.
		* Invocation: IsCustomUnsignedInt<T> where T is any type
		* Defines 'value', an enum that is 1 iff T is a custom built-in unsigned integral type
		* Specialize this class template for nonstandard unsigned integral types and define value = 1 in those specializations
		**/
		template <typename T>
		struct IsCustomUnsignedInt
		{
			enum { value = 0 };
		};        

		/*!
        * \breif
		* Offers a means to integrate nonstandard built-in unsigned integral types
		* (such as unsigned __int64 or unsigned long long int) with the TypeTraits  class template defined below.
		* Invocation: IsCustomSignedInt<T> where T is any type
		* Defines 'value', an enum that is 1 iff T is a custom built-in signed integral type
		* Specialize this class template for nonstandard unsigned integral types and define value = 1 in those specializations
		**/
		template <typename T>
		struct IsCustomSignedInt
		{
			enum { value = 0 };
		};        

		/*!
        * \brief
		* Offers a means to integrate nonstandard floating point types with the TypeTraits class template defined below.
		* Invocation: IsCustomFloat<T> where T is any type
		* Defines 'value', an enum that is 1 iff T is a custom built-in floating point type
		* Specialize this class template for nonstandard unsigned integral types and define value = 1 in those specializations
		**/
		template <typename T>
		struct IsCustomFloat
		{
			enum { value = 0 };
		};        

		// Helper types for class template TypeTraits defined below
		typedef TYPELIST_4(unsigned char, unsigned short int, unsigned int, unsigned long int) StdUnsignedInts;
		typedef TYPELIST_4(signed char, short int, int, long int) StdSignedInts;
		typedef TYPELIST_3(bool, char, wchar_t) StdOtherInts;
		typedef TYPELIST_3(float, double, long double) StdFloats;

        template<typename T>
        class IsArray
        {
            template <typename> struct Type2Type2 {};
            typedef char (&yes)[1];
            typedef char (&no) [2];
        
            template<typename U, size_t N>
            static void vc7_need_this_for_is_array(Type2Type2<U(*)[N]>);
        
            template<typename U, size_t N>
            static yes is_array1(Type2Type2<U[N]>*);
            static no  is_array1(...);
        
            template<typename U>
            static yes is_array2(Type2Type2<U[]>*);
            static no  is_array2(...);
        
        public:
            enum { 
                value =
                    sizeof(is_array1((Type2Type2<T>*)0)) == sizeof(yes) ||
                    sizeof(is_array2((Type2Type2<T>*)0)) == sizeof(yes)
            };            
        };

		/**
		* Figures out various properties of any given type
		* Invocations (T is a type):
		* a) TypeTraits<T>::isPointer
		* returns (at compile time) true if T is a pointer type
		* b) TypeTraits<T>::PointeeType
		* returns the type to which T points is T is a pointer type, NullType otherwise
		* a) TypeTraits<T>::isReference
		* returns (at compile time) true if T is a reference type
		* b) TypeTraits<T>::ReferredType
		* returns the type to which T refers is T is a reference type, NullType
		* otherwise
		* c) TypeTraits<T>::isMemberPointer
		* returns (at compile time) true if T is a pointer to member type
		* d) TypeTraits<T>::isStdUnsignedInt
		* returns (at compile time) true if T is a standard unsigned integral type
		* e) TypeTraits<T>::isStdSignedInt
		* returns (at compile time) true if T is a standard signed integral type
		* f) TypeTraits<T>::isStdIntegral
		* returns (at compile time) true if T is a standard integral type
		* g) TypeTraits<T>::isStdFloat
		* returns (at compile time) true if T is a standard floating-point type
		* h) TypeTraits<T>::isStdArith
		* returns (at compile time) true if T is a standard arithmetic type
		* i) TypeTraits<T>::isStdFundamental
		* returns (at compile time) true if T is a standard fundamental type
		* j) TypeTraits<T>::isUnsignedInt
		* returns (at compile time) true if T is a unsigned integral type
		* k) TypeTraits<T>::isSignedInt
		* returns (at compile time) true if T is a signed integral type
		* l) TypeTraits<T>::isIntegral
		* returns (at compile time) true if T is a integral type
		* m) TypeTraits<T>::isFloat
		* returns (at compile time) true if T is a floating-point type
		* n) TypeTraits<T>::isArith
		* returns (at compile time) true if T is a arithmetic type
		* o) TypeTraits<T>::isFundamental
		* returns (at compile time) true if T is a fundamental type
		* p) TypeTraits<T>::ParameterType
		* returns the optimal type to be used as a parameter for functions that take Ts
		* q) TypeTraits<T>::isConst
		* returns (at compile time) true if T is a const-qualified type
		* r) TypeTraits<T>::NonConstType
		* removes the 'const' qualifier from T, if any
		* s) TypeTraits<T>::isVolatile
		* returns (at compile time) true if T is a volatile-qualified type
		* t) TypeTraits<T>::NonVolatileType
		* removes the 'volatile' qualifier from T, if any
		* u) TypeTraits<T>::UnqualifiedType
		* removes both the 'const' and 'volatile' qualifiers from T, if any
		**/
		template <typename T>
		class TypeTraits
		{
			typedef char (&yes)[1];
			typedef char (&no) [2];

			template<typename U>
			static yes is_reference(Type2Type<U&>);
			static no  is_reference(...);

			template<typename U>
			static yes is_pointer1(Type2Type<U*>);
			static no  is_pointer1(...);

			template<typename U>
			static yes is_pointer2(Type2Type<U const *>);
			static no  is_pointer2(...);

			template<typename U>
			static yes is_pointer3(Type2Type<U volatile *>);
			static no  is_pointer3(...);

			template<typename U>
			static yes is_pointer4(Type2Type<U const volatile *>);
			static no  is_pointer4(...);

			template<typename U, typename V>
			static yes is_pointer2member(Type2Type<U V::*>);
			static no  is_pointer2member(...);

			template<typename U>
			static yes is_const(Type2Type<const U>);
			static no  is_const(...);

			template<typename U>
			static yes is_volatile(Type2Type<volatile U>);
			static no  is_volatile(...);

		public:        
			// VC7 BUG - will not detect reference to function
			enum { 
				isReference = 
					sizeof(is_reference(Type2Type<T>())) == sizeof(yes) 
			};
	        
			// VC7 BUG - will not detect pointer to function
			enum { 
				isPointer = 
					sizeof(is_pointer1(Type2Type<T>())) == sizeof(yes) ||
					sizeof(is_pointer2(Type2Type<T>())) == sizeof(yes) ||
					sizeof(is_pointer3(Type2Type<T>())) == sizeof(yes) ||
					sizeof(is_pointer4(Type2Type<T>())) == sizeof(yes)
			};
	        
			enum { 
				isMemberPointer = 
					sizeof(is_pointer2member(Type2Type<T>())) == sizeof(yes)
			};
	    
			enum { 
				isArray = IsArray<T>::value
			};

			enum { 
				isVoid = 
					IsSameType<T, void>::value          ||
					IsSameType<T, const void>::value    ||
					IsSameType<T, volatile void>::value ||
					IsSameType<T, const volatile void>::value
			};

			enum { isStdUnsignedInt = 
				IndexOf<StdUnsignedInts, T>::value >= 0 };
			enum { isStdSignedInt = 
				IndexOf<StdSignedInts, T>::value >= 0 };
			enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt ||
				IndexOf<StdOtherInts, T>::value >= 0 };
			enum { isStdFloat = IndexOf<StdFloats, T>::value >= 0 };
			enum { isStdArith = isStdIntegral || isStdFloat };
			enum { isStdFundamental = isStdArith || isStdFloat || isVoid };
	            
			enum { isUnsignedInt = isStdUnsignedInt || IsCustomUnsignedInt<T>::value };
			enum { isSignedInt = isStdSignedInt || IsCustomSignedInt<T>::value };
			enum { isIntegral = isStdIntegral || isUnsignedInt || isSignedInt };
			enum { isFloat = isStdFloat || IsCustomFloat<T>::value };
			enum { isArith = isIntegral || isFloat };
			enum { isFundamental = isStdFundamental || isArith || isFloat };
	        
			enum { 
				isConst = 
					sizeof(is_const(Type2Type<T>())) == sizeof(yes)
			};

			enum { 
				isVolatile = 
					sizeof(is_volatile(Type2Type<T>())) == sizeof(yes)
			};

	        
		private:
			// is_scalar include functions types
			struct is_scalar
			{
			private:
				struct BoolConvert { BoolConvert(bool); };

				static yes check(BoolConvert);
				static no  check(...);

				struct NotScalar {};

				typedef typename SelectType
				<
					isVoid || isReference || isArray, 
					NotScalar, T
				>
				::Result RetType;
	            
				static RetType& get();

			public:
	//
	// Ignore forcing value to bool 'true' or 'false' (performance warning)
	//
	#ifdef _MSC_VER
	#pragma warning (disable: 4800)
	#endif

				enum { value = sizeof(check(get())) == sizeof(yes) };

	#ifdef _MSC_VER
	#pragma warning (default: 4800)
	#endif
			}; // is_scalar

	    
		private:
			template<bool IsRef>
			struct AdjReference
			{
				template<typename U>
				struct In { typedef U const & Result; };
			};

			template<>
			struct AdjReference<true>
			{
				template<typename U>
				struct In { typedef U Result; };
			};

			typedef typename AdjReference<isReference || isVoid>::
					template In<T>::Result AdjType;

		public:        
			enum { isScalar = is_scalar::value };

			typedef typename SelectType
			<
				isScalar || isArray, T, AdjType
			>
			::Result ParameterType;
	        
			//
			// We get is_class for free
			// BUG - fails with functions types (ICE) and unknown size array
			// (but works for other incomplete types)
			// (the boost one (Paul Mensonides) is better)
			//
			enum { isClass = 
					!isScalar    && 
					!isArray     && 
					!isReference &&
					!isVoid 
			};
		};
	}
}

#endif