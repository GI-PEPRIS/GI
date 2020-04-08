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
#ifndef __ANYBASE_LOKI_GENERIC_H__
#define __ANYBASE_LOKI_GENERIC_H__

// Modern C++: 
// Below are trick structs, classes or maroes based on generic programming ideas, namely template techniques.
// It includes how to report compiling error or warning, partial template initialization etc.
namespace AnyBase
{
	// Note:
	// This includes file which is benefited from the ideas of "Modern C++" written 
	// by Andrei Alexandrescu
	namespace Loki
	{
		//
		// Asserts for "Non-Compliant" Application
		//
		/*!
        * \brief
        *
		* Helper structure for the COMPILING_CHECK macro, namely compiler will directly
		* report compile time error with this name when it can't find the implementation of 
		* CompileTimeError<false>, so it often substitutes "EXPR" part defined in COMPILING_CHECK
		* macro.
		*/
		template<bool CompileTimeAssertion>
		struct CompileTimeError;

        /*!
        * \brief
        * Partial template specialization let CompileTimerError has only TRUE implementation not WRONG
        **/
		template<> 
		struct CompileTimeError<true> 
		{
			typedef void type;
		};

		/*!
        * \brief
        *
		* where:
		* expr is a compile-time integral or pointer expression
		* id is a C++ identifier that does not need to be defined
		* If expr is zero, id will appear in a compile-time error message.
		*/
		#define LOKI_ASSERT_NONE(expr) CompileTimeError<(expr) != 0>()
		#define LOKI_ASSERT_MSG(expr, msg) typedef char ERROR_##msg[1][(expr)]

		//
		// "Generic" types
		//
		/*!
        * \brief
		* Used as a placeholder for "no type here" or said, "I am not an interesting type",
		* and generally be used as an end marker in typelists 
		*/
		class NullType 
		{
		public:
			/*!
			* Local class for TYPELIST as its heading type
			**/
			struct Head 
			{ 
			  private: 
				  Head(); 
			};

			/*!
			* Local class for a TYPELIST as its tail type
			**/
			struct Tail 
			{ 
			private: 
				Tail(); 
			};
		};

		/*!
        * \brief
		* Used as a class type that doesn't hold anything but it does be a sensful type
		* Useful as a strawman class
		*/
		class EmptyType 
		{
		};

		/*!
        * \brief
        * Being a typical traits this class converts each integral constant into a unique type
		* Invocation: Int2Type<v> where v is a compile-time constant integral
		* Defines 'value', an enum that evaluates to v
		*/
		template <int v>
		struct Int2Type
		{
			enum { value = v };
		};
    
		/*!
        * \brief
        * Being a typical traits this class converts each type into a unique, insipid type
		* Invocation Type2Type<T> where T is a type
		* Defines the type OriginalType which maps back to T
		*/
		template <typename T>
		struct Type2Type
		{  
			// Mapping between types
			typedef T OriginalType;

			/*!
			* In order to erase VC7 Compiler bug
			*/
			Type2Type()
			{
			} // VC7
		};

		/*!
        * \brief
        * Being a typical traits, this class selects one of two types based upon a boolean constant
		* Invocation: Select<flag, T, U>::Result
		* where:
		* flag is a compile-time boolean constant
		* T and U are types
		* Result evaluates to T if flag is true, and to U otherwise.
		*/
		template <bool flag, typename T, typename U>
		struct SelectType
		{
		private:
            // Define a template local class with is partial template specialization to hint
            // outside is to select which type, FALSE means U, otherwise means T
			/*!
			* TRUE means to select T type
			**/
			template<bool>
			struct In 
			{ typedef T Result; };

			/*!
			* FALSE means to select U type
			**/
			template<>
			struct In<false>
			{ typedef U Result; };

		public:
			typedef typename In<flag>::Result Result;
		};

		//
		// "Generic" operations
		//
		/*!
        * \brief
		* Return true if two given types are the same
		* Invocation: IsSameType<T, U>::value
		* where:
		* T and U are types
		* Result evaluates to true if U == T (types equal)
		*/
		template <typename T, typename U>
		struct IsSameType
		{
		private:
			/*!
            * \brief
			* Except for T type, all are false
			**/
			template<typename>
			struct In 
			{ enum { value = false }; };

			/*!
            * \brief
			* Only for T type, it is true with partial template specification
			**/
			template<>
			struct In<T>
			{ enum { value = true };  };

		public:
			enum { value = In<U>::value };
		};

		/*!
        * \brief
		* Whether those types are permitted types for given calling scene
		*/
        template<typename T>
        struct IsVoid
        {
            enum 
            { result = 
                IsSameType<T, void>::value          ||
                IsSameType<T, const void>::value    ||
                IsSameType<T, volatile void>::value ||
                IsSameType<T, const volatile void>::value
            };
        };

		/*!
        * \brief
		* Is one type convertable to another?
		*/
		template <class T, class U>
		class IsConvertible
		{
			// Tricks for definition of two overloads in order to 
			// differenciate return types using its size got by sizeof() function
			typedef char Small;
			class Big 
            { 
                char dummy[2]; 
            };

			// If T is the same as U type, they both select VoidReplace
			struct VoidReplace 
            {
            };

			/*!
            * brief
			* If T is one of valid types and is the same as VoidReplace
			**/
			typedef typename SelectType
			<
				IsVoid<T>::result,
				VoidReplace, T
			>::Result T1;

			/*!
            * \brief
			* If U is one of valid types and is the same as VoidReplace
			**/
			typedef typename SelectType
			<
				IsVoid<U>::result,
				VoidReplace, U
			>::Result U1;

			// Two overloads in order to differenciate kinds of types
			// This function nothing is only for compiling time not for running time
			// Namely, just its returned type will be evaluated when calling sizeof(...) function
			static Big Test(...); 
			static Small Test(U1);		// Small means what we want to compare

			// Just make definition it is TYPE u cared
            // In fact MakeT is only a dummy function with only share its return TYPE and
            // if T1 can be implicitly converted to U type, it DOES. Else, not convertibale
			static T1 MakeT();

		public:       
			enum { exists = (sizeof(Test(MakeT())) == sizeof(Small)) };
		};

		/*!
        * \brief
		* Figures out the conversion relationships between two types
		* Invocations (T and U are types):
		* a) Conversion<T, U>::exists
		* returns (at compile time) true if there is an implicit conversion from T
		* to U (example: Derived to Base)
		* b) Conversion<T, U>::exists2Way
		* returns (at compile time) true if there are both conversions from T
		* to U and from U to T (example: int to char and back)
		* c) Conversion<T, U>::sameType
		* returns (at compile time) true if T and U represent the same type
		* Caveat: might not work if T and U are in a private inheritance hierarchy.
		*/
		template <class T, class U>
		struct Conversion
		{
			enum { exists = (IsConvertible<T,U>::exists) };
			enum { exists2Way = (exists && IsConvertible<U, T>::exists) };
			enum { sameType = (IsSameType<T, U>::value) };
		};

		/*!
        * \brief
		* Invocation: SuperSubclass<B, D>::value where B and D are types. 
		* Returns true if B is a public base of D, or if B and D are aliases of the 
		* same type.
		* Caveat: might not work if T and U are in a private inheritance hierarchy.
		*/
		template <class T, class U>
		struct SuperSubclass
		{
		  enum { value = (Conversion<const volatile U*, const volatile T*>::exists &&
						  !Conversion<const volatile T*, const volatile void*>::sameType) };
		};
	    #define LOKI_ISSUBCLASS(T, U) SuperSubclass<T,U>::value

		/*!
        * \brief
		* Invocation: SuperSubclassStrict<B, D>::value where B and D are types. 
		* Returns true if B is a public base of D.
		* Caveat: might not work if T and U are in a private inheritance hierarchy.
		*/
		template<class T,class U>
		struct SuperSubclassStrict
		{
		  enum { value = (Conversion<const volatile U*, const volatile T*>::exists &&
						 !Conversion<const volatile T*, const volatile void*>::sameType &&
						 !Conversion<const volatile T*, const volatile U*>::sameType) };
		};
        #define LOKI_ISSTRICTSUBCLASS(T, U) SuperSubclassStrict<T,U>::value
	} // Loki
} // AnyBase

#endif