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
#ifndef __ANYBASE_LOKI_MULTIMETHODS_H__
#define __ANYBASE_LOKI_MULTIMETHODS_H__

// Loki-references
#include "typelist.h"
#include "typeInfo.h"
#include "functor.h"
#include "assocvector.h"

//
namespace AnyBase
{
	// Note:
	// The double dispatchers implemented below differ from the excerpts shown in
	// the book - they are simpler while respecting the same interface.
	namespace Loki
	{
		//
		// Static dispatcher
		//
		/*!
		* \brief
		* helper class template InvocationTraits (helper)
		* Helps implementing optional symmetry
		*/
		template <class SomeLhs, class SomeRhs, class Executor, typename ResultType>
		struct InvocationTraits
		{
			/*!
			* When encountering "false" condition, not swap parameters
			**/
			static ResultType DoDispatch(SomeLhs &lhs, SomeRhs &rhs, Executor &exec, Int2Type<false>)
			{
				return exec.Fire(lhs, rhs);
			}

			/*!
			* When encountering "true" condition, swap parameters
			**/
			static ResultType DoDispatch(SomeLhs &lhs, SomeRhs &rhs, Executor &exec, Int2Type<true>)
			{
				return exec.Fire(rhs, lhs);
			}
		};

		/*!
		* brief
		* class template StaticDispatcher
		* Implements an automatic static double dispatcher based on two typelists
		*/
		template
		<
			class Executor,
			class BaseLhs, 
			class TypesLhs,
			bool symmetric = true,
			class BaseRhs = BaseLhs,
			class TypesRhs = TypesLhs,
			typename ResultType = void
		>
		class StaticDispatcher
		{
			/*!
			* Exception
			**/
			template <class SomeLhs>
			static ResultType DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec, NullType)
			{ 
				return exec.OnError(lhs, rhs); 
			}
		    
			/*!
			*
			**/
			template <class Head, class Tail, class SomeLhs>
			static ResultType DispatchRhs(SomeLhs &lhs, BaseRhs &rhs, Executor exec, Typelist<Head, Tail>)
			{            
				// When right parameter can successfully be converted 
				// into the passed type ...
				if(Head *p2 = dynamic_cast<Head*>(&rhs))
				{
					// Whethr need to swap input class types for removing redundant functions
					Int2Type<(symmetric &&
							  int(IndexOf<TypesRhs, Head>::value) <
							  int(IndexOf<TypesLhs, SomeLhs>::value))> i2t;

					typedef InvocationTraits<SomeLhs, Head, Executor, ResultType> CallTraits;
					return CallTraits::DoDispatch(lhs, *p2, exec, i2t);
				}

				return DispatchRhs(lhs, rhs, exec, Tail());
			}
		    
			/*!
			* It doesn't permit NullType in both of left,right type series
			**/
			static ResultType DispatchLhs(BaseLhs &lhs, BaseRhs &rhs, Executor exec, NullType)
			{ 
				return exec.OnError(lhs, rhs); 
			}
		    
			/*!
			*
			**/
			template <class Head, class Tail>
			static ResultType DispatchLhs(BaseLhs &lhs, BaseRhs &rhs, Executor exec, Typelist<Head, Tail>)
			{           
				// When left parameter can successfully be converted 
				// into the first passed type ...
				if(Head *p1 = dynamic_cast<Head*>(&lhs))
				{
					// To iterate the right type series given the left class type
					return DispatchRhs(*p1, rhs, exec, TypesRhs());
				}

				// To find the next matched class type in left series
				return DispatchLhs(lhs, rhs, exec, Tail());
			}

		public:
			/*!
			* public interface executed by following the left type series
			**/
			static ResultType Go(BaseLhs& lhs, BaseRhs& rhs, Executor exec)
			{ 
				return DispatchLhs(lhs, rhs, exec, TypesLhs()); 
			}
		};
    
		//
		// Basic dispatcher given typeid map registration
		//
		/*!
		* \brief
		* class template BasicDispatcher
		* Implements a logarithmic double dispatcher for functors (or functions)
		* Doesn't offer automated casts or symmetry
		**/
		template
		<
			class BaseLhs,
			class BaseRhs = BaseLhs,
			typename ResultType = void,
			typename CallbackType = ResultType (*)(BaseLhs&, BaseRhs&)
		>
		class BasicDispatcher
		{
			// Left and right type id
			typedef std::pair<TypeInfo,TypeInfo> KeyType;
			// Above corresponding function
			typedef CallbackType MappedType;
			// Make a direct map for direct position
			typedef AssocVector<KeyType, MappedType> MapType;
			// Declare this callback map
			MapType m_callbackMap;
		    
			//
			// Basic operations for callback map
			//
			/*!
			*
			**/
			void DoAdd(TypeInfo lhs, TypeInfo rhs, CallbackType fun);

			/*!
			*
			**/
			bool DoRemove(TypeInfo lhs, TypeInfo rhs);
		    
		public:
			/*!
			* Template map operations
			**/
			template <class SomeLhs, class SomeRhs>
			void Add(CallbackType fun)
			{
				DoAdd(typeid(SomeLhs), typeid(SomeRhs), fun);
			}
		    
			/*!
			* Template map operations
			**/
			template <class SomeLhs, class SomeRhs>
			bool Remove()
			{
				return DoRemove(typeid(SomeLhs), typeid(SomeRhs));
			}
		    
			/*!
			*
			**/
			ResultType Go(BaseLhs &lhs, BaseRhs &rhs);
		};

		//
		// Implementatins of template methods removed from class body
		//
		/*!
		* Non-inline to reduce compile time overhead...
		**/
		template <class BaseLhs, class BaseRhs, typename ResultType, typename CallbackType>
		void BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>::DoAdd(TypeInfo lhs, TypeInfo rhs, CallbackType fun)
		{
			m_callbackMap[KeyType(lhs, rhs)] = fun;
		}
	    
		/*!
		*
		**/
		template <class BaseLhs, class BaseRhs, typename ResultType, typename CallbackType>
		bool BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>::DoRemove(TypeInfo lhs, TypeInfo rhs)
		{
			return m_callbackMap.erase(KeyType(lhs, rhs)) == 1;
		}

		/*!
		*
		**/
		template <class BaseLhs, class BaseRhs, typename ResultType, typename CallbackType>
		ResultType BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>::Go(BaseLhs &lhs, BaseRhs &rhs)
		{
			typename MapType::key_type k(typeid(lhs),typeid(rhs));
			typename MapType::iterator i = m_callbackMap.find(k);

			if(i == m_callbackMap.end())
			{
				throw std::runtime_error("Function not found");
			}

			return (i->second)(lhs, rhs);
		}


		//
		// Improvement of basic dispatch considering running time speed, namely 
		// the speed of "static_cast" is fast than "dynamic_cast", but the latter is more safe
		//
		/*!
		* class template StaticCaster
		* Implementation of the CastingPolicy used by FunctorDispatcher
		**/
		template <class To, class From>
		struct StaticCaster
		{
			static To &Cast(From &obj)
			{
				return static_cast<To&>(obj);
			}
		};

		/*!
		* class template DynamicCaster
		* Implementation of the CastingPolicy used by FunctorDispatcher
		**/
		template <class To, class From>
		struct DynamicCaster
		{
			static To &Cast(From &obj)
			{
				return dynamic_cast<To&>(obj);
			}
		};

		/*!
		* class template CastDispatcherHelper
		* Implements trampolines and argument swapping used by CastDispatcher
		**/
		template <class BaseLhs, class BaseRhs, class SomeLhs, class SomeRhs, typename ResultType, 
			class CastLhs, class CastRhs, ResultType (*Callback)(SomeLhs&, SomeRhs&)>
		struct CastDispatcherHelper
		{
			/*!
			* Have a chance to decide which type of cast
			**/
			static ResultType Trampoline(BaseLhs &lhs, BaseRhs &rhs)
			{
				return Callback(CastLhs::Cast(lhs), CastRhs::Cast(rhs));
			}

			/*!
			*
			**/
			static ResultType TrampolineR(BaseRhs &rhs, BaseLhs &lhs)
			{
				return Trampoline(lhs, rhs);
			}
		};

		/*!
		* \brief
		* class template CastDispatcher
		* Implements an automatic logarithmic double dispatcher for functions
		* Features automated conversions
		**/
		template <class BaseLhs, class BaseRhs = BaseLhs,
				  typename ResultType = void,
				  template <class, class> class CastingPolicy = DynamicCaster,
				  template <class, class, class, class>
				  class DispatcherBackend = BasicDispatcher>
		class CastDispatcher
		{
		public:
			/*!
			* Register callback function
			**/
			template <class SomeLhs, class SomeRhs>
			void Add(ResultType (*pFun)(BaseLhs&, BaseRhs&))
			{
				return m_backEnd.template Add<SomeLhs, SomeRhs>(pFun);
			}        
		    
			/*!
			* Make left and right type ids and their corresponding function
			**/
			template < class SomeLhs, class SomeRhs, ResultType (*callback)(SomeLhs&, SomeRhs&) >
			void Add()
			{
				// Here is a chance to select static_cast but dynamic for running time speed enhancement
				// using "trampoline" tricks
				typedef CastDispatcherHelper<
							BaseLhs, BaseRhs, 
							SomeLhs, SomeRhs,
							ResultType,
							CastingPolicy<SomeLhs, BaseLhs>, 
							CastingPolicy<SomeRhs, BaseRhs>, 
							callback> Local;

					Add<SomeLhs, SomeRhs>(&Local::Trampoline);
			}
		    
			/*!
			*
			**/
			template <class SomeLhs, class SomeRhs, ResultType (*callback)(SomeLhs&, SomeRhs&), bool symmetric>
			void Add(bool = true) // [gcc] dummy bool
			{
				typedef CastDispatcherHelper<
							BaseLhs, BaseRhs, 
							SomeLhs, SomeRhs,
							ResultType,
							CastingPolicy<SomeLhs,BaseLhs>, 
							CastingPolicy<SomeRhs,BaseRhs>, 
							callback> Local;

					Add<SomeLhs, SomeRhs>(&Local::Trampoline);
					if(symmetric)
					{
						Add<SomeRhs, SomeLhs>(&Local::TrampolineR);
					}
			}

			/*!
			*
			**/
			template <class SomeLhs, class SomeRhs>
			void Remove()
			{
				/*!
				*
				**/
				m_backEnd.template Remove<SomeLhs, SomeRhs>();
			}

			/*!
			* Forward function
			**/
			ResultType Go(BaseLhs &lhs, BaseRhs &rhs)
			{
				return m_backEnd.Go(lhs, rhs);
			}

		private:
			// Except for changing of cast conversion process, the left is the same as basic dispatcher
			DispatcherBackend<BaseLhs, BaseRhs, ResultType, ResultType (*)(BaseLhs&, BaseRhs&)> m_backEnd;
		};

		//
		// Functor dispatcher
		//
		/*!
		* \brief
		* class template FunctorDispatcherAdaptor
		* permits use of FunctorDispatcher under gcc.2.95.2/3
		**/
		template <class BaseLhs, class BaseRhs,
		  class SomeLhs, class SomeRhs,
		  typename ResultType,
		  class CastLhs, class CastRhs,
		  class Fun, bool SwapArgs>
		class FunctorDispatcherHelper 
		{
			/*!
			* To resolve symmetric issue of callback function
			**/
			Fun m_fun;

			/*!
			*
			**/
			ResultType Fire(BaseLhs &lhs, BaseRhs &rhs,Int2Type<false>)
			{
				return m_fun(CastLhs::Cast(lhs), CastRhs::Cast(rhs));
			}

			/*!
			*
			**/
			ResultType Fire(BaseLhs &rhs, BaseRhs &lhs,Int2Type<true>)
			{
				return m_fun(CastLhs::Cast(lhs), CastRhs::Cast(rhs));
			}

		public:
			/*!
			*
			**/
			FunctorDispatcherHelper(const Fun& fun) : m_fun(fun) 
			{
			}

			/*!
			*
			**/
			ResultType operator()(BaseLhs &lhs, BaseRhs &rhs)
			{
				return Fire(lhs, rhs, Int2Type<SwapArgs>());
			}
		};

		/*!
		* \brief
		* class template FunctorDispatcher
		* Implements a logarithmic double dispatcher for functors
		* Features automated casting
		**/
		template <class BaseLhs, class BaseRhs = BaseLhs,
				  typename ResultType = void,
				  template <class, class> class CastingPolicy = DynamicCaster, 
				  template <class, class, class, class>
				  class DispatcherBackend = BasicDispatcher>
		class FunctorDispatcher
		{
			typedef TYPELIST_2(BaseLhs&, BaseRhs&) ArgsList;
			typedef Functor<ResultType, ArgsList, LOKI_DEFAULT_THREADING> FunctorType;

			DispatcherBackend<BaseLhs, BaseRhs, ResultType, FunctorType> m_backEnd;

		public:
			/*!
			*
			**/
			template <class SomeLhs, class SomeRhs, class Fun>
			void Add(const Fun &fun)
			{
				typedef FunctorDispatcherHelper<
						BaseLhs, BaseRhs,
						SomeLhs, SomeRhs,
						ResultType,
						CastingPolicy<SomeLhs, BaseLhs>,
						CastingPolicy<SomeRhs, BaseRhs>,
						Fun, false> Adapter;

				m_backEnd.template Add<SomeLhs, SomeRhs>(FunctorType(Adapter(fun)));
			}

			/*!
			*
			**/
			template <class SomeLhs, class SomeRhs, bool symmetric, class Fun>
			void Add(const Fun& fun)
			{
				Add<SomeLhs, SomeRhs>(fun);

				if(symmetric)
				{
					// Note: symmetry only makes sense where BaseLhs==BaseRhs
					typedef FunctorDispatcherHelper<
						BaseLhs, BaseLhs,
						SomeLhs, SomeRhs,
						ResultType,
						CastingPolicy<SomeLhs, BaseLhs>,
						CastingPolicy<SomeRhs, BaseLhs>,
						Fun, true> AdapterR;

						m_backEnd.template Add<SomeRhs, SomeLhs>(FunctorType(AdapterR(fun)));
				}
			}
		    
			/*!
			*
			**/
			template <class SomeLhs, class SomeRhs>
			void Remove()
			{
				m_backEnd.template Remove<SomeLhs, SomeRhs>();
			}

			/*!
			*
			**/
			ResultType Go(BaseLhs &lhs, BaseRhs &rhs)
			{
				return m_backEnd.Go(lhs, rhs);
			}
		};

	} // namespace of loki
} // namespace of anybase

#endif