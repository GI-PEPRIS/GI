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
#ifndef __ANYBASE_LOKI_VISITOR_H__
#define __ANYBASE_LOKI_VISITOR_H__

//
#include "typelist.h"
#include "hierarchygenerators.h"

//
namespace AnyBase
{
    namespace Loki
    {
        /*!
        * \brief
        * The base class of any Acyclic Visitor
        */
        class BaseVisitor
        {
        public:
            //
            // Constructors & deconstructor
            //
            /**
            * \fn virtual ~BaseVisitor() 
            * \brief
            * 1) for the correct usage of dynamic_cast
            * 2) for the correct bahavior of deconstructor when deleting vid base pointer
            **/
            virtual ~BaseVisitor() 
            {
            }
        };
        
		// Forward decleration
		// Here is difference for const & non-const visitor objects
		template <class T, typename R = void, bool ConstVisit = false>
		class Visitor;

		/*!
		* FALSE means visitor visits the non-const object represented by T
		**/
		template <class T, typename R>
		class Visitor<T, R, false>
		{
		public:
			// Alias names
			typedef R ReturnType;
			typedef T ParamType;

			//
			//
			//
			/*!
			*
			**/
			virtual ~Visitor() 
			{
			}

			/*!
			*
			**/
			virtual ReturnType Visit(ParamType&) = 0;
		};

		/*!
		* TRUE means visitor visits the const object represented by T
		**/
		template <class T, typename R>
		class Visitor<T, R, true>
		{
		public:
			// Alias names
			typedef R ReturnType;
			typedef const T ParamType;

			//
			//
			//
			/*!
			*
			**/
			virtual ~Visitor() 
			{
			}

			/*!
			*
			**/
			virtual ReturnType Visit(ParamType&) = 0;
		};

		/*!
		* class template Visitor (specialization)
		* It makes it easier to define Visitors for multiple types in a shot by using a typelist. 
		* Example:
		* class SomeVisitor : 
		*     public BaseVisitor // required
		*     public Visitor<LOKI_TYPELIST_2(RasterBitmap, Paragraph)>
		* {
		* public:
		*     void Visit(RasterBitmap&); // visit a RasterBitmap
		*     void Visit(Paragraph &);   // visit a Paragraph
		* };
		**/
		template <class Head, class Tail, typename R>
		class Visitor<Typelist<Head, Tail>, R, false> : public Visitor<Head, R, false>, public Visitor<Tail, R, false>
		{
		public:
			typedef R ReturnType;

		   // using Visitor<Head, R>::Visit;
		   // using Visitor<Tail, R>::Visit;
		};

		/*!
		* When unfolding the last pair
		**/
		template <class Head, typename R>
		class Visitor<Typelist<Head, NullType>, R, false> : public Visitor<Head, R, false>
		{
		public:
			typedef R ReturnType;
			using Visitor<Head, R, false>::Visit;
		};

		/*!
		*
		**/
		template <class Head, class Tail, typename R>
		class Visitor<Typelist<Head, Tail>, R, true> : public Visitor<Head, R, true>, public Visitor<Tail, R, true>
		{
		public:
			typedef R ReturnType;

		   // using Visitor<Head, R>::Visit;
		   // using Visitor<Tail, R>::Visit;
		};

		/*!
		* When unfolding the last pair
		**/
		template <class Head, typename R>
		class Visitor<Typelist<Head, NullType>, R, true> : public Visitor<Head, R, true>
		{
		public:
			typedef R ReturnType;
			using Visitor<Head, R, true>::Visit;
		};


		/*!
		* \brief class template BaseVisitorImpl
		* Implements non-strict visitation (you can implement only part of the Visit functions)
		**/
	    template <class TList, typename R = void> class BaseVisitorImpl;

		/*!
		*
		**/
		template <class Head, class Tail, typename R>
		class BaseVisitorImpl<Typelist<Head, Tail>, R> : public Visitor<Head, R>, public BaseVisitorImpl<Tail, R>
		{
		public:
			// using BaseVisitorImpl<Tail, R>::Visit;

			/*!
			*
			**/
			virtual R Visit(Head&)
			{ 
				return R(); 
			}
		};

		/*!
		* When unfolding the last one
		**/
		template <class Head, typename R>
		class BaseVisitorImpl<Typelist<Head, NullType>, R> : public Visitor<Head, R>
		{
		public:
			/*!
			*
			**/
			virtual R Visit(Head&)
			{ 
				return R(); 
			}
		};


		/*!
		* class template BaseVisitable
		**/
		template <typename R, typename Visited>
		struct DefaultCatchAll
		{
			/*!
			* Here one concrete shouldn't visit the un-predicated concrete vistable classes,
			* else it should go here!
			**/
			static R OnUnknownVisitor(Visited&, BaseVisitor&)
			{ 
				return R(); 
			}
		};

		// Forward class
		template 
		<
			typename R = void, 
			template <typename, class> class CatchAll = DefaultCatchAll,
			bool ConstVisitable = false
		>
		class BaseVisitable;

		/*!
		* For non-const vistable object
		**/
		template<typename R,template <typename, class> class CatchAll>
		class BaseVisitable<R, CatchAll, false>
		{
		public:
			typedef R ReturnType;

			//
			//
			//
			/*!
			*
			**/
			virtual ~BaseVisitable() 
			{
			}

			//
			//
			//
			/*!
			* Bouncing back function when visitable class be visited by its corresponding visitor class
			**/
			virtual ReturnType Accept(BaseVisitor&) = 0;
		    
		protected:
			//
			//
			//
			/*!
			* Give access only to the whole vistable class hierarchy
			**/
			template <class T>
			static ReturnType AcceptImpl(T& visited, BaseVisitor& guest)
			{
				// Apply the Acyclic Visitor
				if(Visitor<T,R> *p = dynamic_cast<Visitor<T,R>*>(&guest))
				{
					return p->Visit(visited);
				}

				// Here is no direct correspondence between given vistable and visitor classes
				return CatchAll<R, T>::OnUnknownVisitor(visited, guest);
			}
		};

		/*!
		* For const object
		**/
		template<typename R,template <typename, class> class CatchAll>
		class BaseVisitable<R, CatchAll, true>
		{
		public:
			//
			typedef R ReturnType;

			//
			//
			//
			/*!
			*
			**/
			virtual ~BaseVisitable() 
			{
			}

			/*!
			*
			**/
			virtual ReturnType Accept(BaseVisitor&) const = 0;
		    
		protected: 
			// 
			//
			//
			/*!
			* Give access only to the hierarchy
			**/
			template <class T>
			static ReturnType AcceptImpl(const T& visited, BaseVisitor& guest)
			{
				// Apply the Acyclic Visitor
				if(Visitor<T,R,true> *p = dynamic_cast<Visitor<T,R,true>*>(&guest))
				{
					return p->Visit(visited);
				}

				// Here is no direct correspondence between given vistable and visitor classes
				return CatchAll<R, T>::OnUnknownVisitor(const_cast<T&>(visited), guest);
			}
		};

		// Define acyclic vistor & visitable hierarchy

		// \def LOKI_DEFINE_VISITABLE()
		// \ingroup VisitorGroup
		// Put it in every class that you want to make visitable 
		// (in addition to deriving it from BaseVisitable<R>)
		#define LOKI_DEFINE_VISITABLE() \
			virtual ReturnType Accept(BaseVisitor &guest) \
			{ return AcceptImpl(*this, guest); }

		// \def LOKI_DEFINE_CONST_VISITABLE()
		// \ingroup VisitorGroup
		// Put it in every class that you want to make visitable by const member 
		// functions (in addition to deriving it from BaseVisitable<R>)
		#define LOKI_DEFINE_CONST_VISITABLE() \
			virtual ReturnType Accept(BaseVisitor& guest) const \
			{ return AcceptImpl(*this, guest); }

		/*!
		* \class CyclicVisitor
		*
		* \ingroup VisitorGroup
		* Put it in every class that you want to make visitable (in addition to 
		* deriving it from BaseVisitable<R>
		**/
		template <typename R, class TList>
		class CyclicVisitor : public Visitor<TList, R>
		{
		public:
			typedef R ReturnType;
			// using Visitor<TList, R>::Visit;
	        
			template <class Visited>
			ReturnType GenericVisit(Visited &host)
			{
				Visitor<Visited, ReturnType> &subObj = *this;
				return subObj.Visit(host);
			}
		};

		// \def LOKI_DEFINE_CYCLIC_VISITABLE(SomeVisitor)
		// \ingroup VisitorGroup
		// Put it in every class that you want to make visitable by a cyclic visitor
		#define LOKI_DEFINE_CYCLIC_VISITABLE(SomeVisitor) \
			virtual SomeVisitor::ReturnType Accept(SomeVisitor &guest) \
			{ return guest.GenericVisit(*this); }
    }
}
#endif
