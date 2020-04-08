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
#ifndef __ANYBASE_LOKI_FACTORY_H__
#define __ANYBASE_LOKI_FACTORY_H__

#include "typeinfo.h"
#include "assocvector.h"

//
namespace AnyBase
{
    //
    namespace Loki
    {
		/*!
		* Manages the "Unknown Type" error in an object factory
		**/
		template <typename IdentifierType, class AbstractProduct>
		struct DefaultFactoryError
		{
			/*!
			*
			**/
			struct Exception : public std::exception
			{
				const char *what() const throw() { return "Unknown Type"; }
			};

			/*!
			*
			**/
			static AbstractProduct *OnUnknownType(IdentifierType)
			{
				throw Exception();
			}
		};

		/*!
		* Implements a generic object factory
		**/
		template
		<
			class AbstractProduct, 
			typename IdentifierType,
			typename ProductCreator = AbstractProduct* (*)(),
			template<typename, class> class FactoryErrorPolicy = DefaultFactoryError
		>
		class Factory : public FactoryErrorPolicy<IdentifierType, AbstractProduct>
		{
		public:
			/*!
			*
			**/
			bool Register(const IdentifierType &id, ProductCreator creator)
			{
				 return m_associations.insert(IdToProductMap::value_type(id, creator)).second;
			}
		    
			/*!
			*
			**/
			bool Unregister(const IdentifierType &id)
			{
				 return m_associations.erase(id) == 1;
			}
		    
			/*!
			*
			**/
			AbstractProduct *CreateObject(const IdentifierType& id)
			{
				 typename IdToProductMap::iterator i = m_associations.find(id);
				 if(i != m_associations.end())
				 {
					 return (i->second)();
				 }
				 return OnUnknownType(id);
			}
		    
		private:
			// Object type and its corresponding creator
			typedef AssocVector<IdentifierType, ProductCreator> IdToProductMap;
			IdToProductMap m_associations;
		};

		/*!
		* Implements a generic cloning factory
		**/
		template
		<
			class AbstractProduct, 
			class ProductCreator = AbstractProduct* (*)(const AbstractProduct*),
			template<typename, class> class FactoryErrorPolicy = DefaultFactoryError
		>
		class CloneFactory : public FactoryErrorPolicy<TypeInfo, AbstractProduct>
		{
		public:
			/*!
			*
			**/
			bool Register(const TypeInfo &ti, ProductCreator creator)
			{
				 return m_associations.insert(IdToProductMap::value_type(ti, creator)).second;
			}
		    
			/*!
			*
			**/
			bool Unregister(const TypeInfo &id)
			{
				 return m_associations.erase(id) == 1;
			}
		    
			/*!
			*
			**/
			AbstractProduct* CreateObject(const AbstractProduct* model)
			{
				 if(model == 0) 
				 {
					 return 0;
				 }
		        
				 typename IdToProductMap::iterator i = m_associations.find(typeid(*model));
				 if(i != m_associations.end())
				 {
					 return (i->second)(model);
				 }
				 return OnUnknownType(typeid(*model));
			}
		    
		private:
			//
			typedef AssocVector<TypeInfo, ProductCreator> IdToProductMap;
			IdToProductMap m_associations;
		};
    } 
}
#endif
