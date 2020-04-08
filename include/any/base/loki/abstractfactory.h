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
#ifndef __ANYBASE_LOKI_ABSTRACTFACTORY_H__
#define __ANYBASE_LOKI_ABSTRACTFACTORY_H__

// Refer to CRITICAL_SECTION definition
#include <cassert>

//
#include "typelist.h"
#include "hierarchygenerators.h"

/**
 * \defgroup	FactoriesGroup Factories
 * \defgroup	AbstractFactoryGroup Abstract Factory
 * \ingroup		FactoriesGroup
 * \brief		Implements an abstract object factory.
 */
 
/*!
 * \class		AbstractFactory
 * \ingroup		AbstractFactoryGroup
 * \brief		Implements an abstract object factory.
 */
// Namespace
namespace AnyBase
{
	//
	namespace Loki
	{
		/*!
		* \brief
		* class template AbstractFactoryUnit
		* The building block of an Abstract Factory
		**/
		template <class T>
		class AbstractFactoryUnit
		{
		public:
			//
			//
			//
			/*!
			* Overloading tricks
			**/
			virtual T* DoCreate(Type2Type<T>) = 0;

			/*!
			*
			**/
			virtual ~AbstractFactoryUnit() 
			{
			}
		};

		/*!
		* class template AbstractFactory
		* Defines an Abstract Factory interface starting from a typelist
		**/
		template
		<
			class TList,
			template <class> class Unit = AbstractFactoryUnit
		>
		class AbstractFactory : public GenScatterHierarchy<TList, Unit>
		{
		public:
			// Classes to be created
			typedef TList ProductList;
		    
			/*!
			* Loop to create each class
			**/
			template <class T> T* Create()
			{
				Unit<T>& unit = *this;
				return unit.DoCreate(Type2Type<T>());
			}
		};
    
		/*!
		* \brief
		* class template OpNewFactoryUnit
		* Creates an object by invoking the new operator
		**/
		template <class ConcreteProduct, class Base>
		class OpNewFactoryUnit : public Base
		{
			// Classes to be created
			typedef typename Base::ProductList BaseProductList;

		protected:
			// The left classes to be created
			typedef typename BaseProductList::Tail ProductList;

		public:
			// The current class is being created with NEW allocation
			typedef typename BaseProductList::Head AbstractProduct;

			/*!
			* Only some type calculations for figuring out which abstract product to
			* implement
			**/
			ConcreteProduct* DoCreate(Type2Type<AbstractProduct>)
			{
				return new ConcreteProduct;
			}
		};

		/*!
		* \brief
		* this class creates an object by cloning a prototype.
		* GetPrototype and SetPrototype use the helper friend functions DoGetPrototype and DoSetPrototype. 
		* The friend functions avoid name hiding issues. Plus, GetPrototype takes a reference to pointer 
		* instead of returning the pointer by value.
		**/
		template <class ConcreteProduct, class Base>
		class PrototypeFactoryUnit : public Base
		{
			// Classes to be created
			typedef typename Base::ProductList BaseProductList;

		protected:
			// The left classes to be created
			typedef typename BaseProductList::Tail ProductList;

		public:
			// The current class is being created in prototype way
			typedef typename BaseProductList::Head AbstractProduct;

			/*!
			*
			**/
			PrototypeFactoryUnit(AbstractProduct *p = 0)
				: m_prototype(p)
			{
			}

			/*!
			*
			**/
			template <class CP, class Base1>
			friend void DoGetPrototype(const PrototypeFactoryUnit<CP, Base1> &me, typename Base1::ProductList::Head *&pPrototype);

			/*!
			*
			**/
			template <class CP, class Base1>
			friend void DoSetPrototype(PrototypeFactoryUnit<CP, Base1> &me, typename Base1::ProductList::Head *pObj);

			/*!
			*
			**/
			template <class U>
			void GetPrototype(U *&p)
			{ 
				return DoGetPrototype(*this, p); 
			}
		    
			/*!
			*
			**/
			template <class U>
			void SetPrototype(U *pObj)
			{ 
				DoSetPrototype(*this, pObj); 
			}
		    
			/*!
			*
			**/
			AbstractProduct* DoCreate(Type2Type<AbstractProduct>)
			{
				assert(m_prototype);
				return m_prototype->Clone();
			}
		    
		private:
			// The prototype
			AbstractProduct *m_prototype;
		};

		// 
		// Helper template functions 
		//
		/*!
		*
		**/
		template <class CP, class Base>
		inline void DoGetPrototype(const PrototypeFactoryUnit<CP, Base> &me, typename Base::ProductList::Head *&pPrototype)
		{ 
			pPrototype = me.m_prototype; 
		}

		/*!
		*
		**/
		template <class CP, class Base>
		inline void DoSetPrototype(PrototypeFactoryUnit<CP, Base> &me, typename Base::ProductList::Head *pObj)
		{ 
			me.m_prototype = pObj; 
		}


		/*!
		* \brief
		* class template ConcreteFactory
		* Implements an AbstractFactory interface
		**/
		template
		<
			class AbstractFact,
			template <class, class> class Creator = OpNewFactoryUnit,
			class TList = typename AbstractFact::ProductList
		>
		class ConcreteFactory : public GenLinearHierarchy<typename Reverse<TList>::Result, Creator, AbstractFact>
		{
		public:
			// Abstract classes
			typedef typename AbstractFact::ProductList ProductList;

			// Inheritted classes from above abstract classes
			typedef TList ConcreteProductList;
		};

	} // namespace Loki
}

#endif

