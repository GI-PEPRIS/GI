#ifndef __ANYBASE_LOKI_TYPEINFO_H__
#define __ANYBASE_LOKI_TYPEINFO_H__

// Refer to STL defintions
#include "any/base/anystl.h"

//
namespace AnyBase
{
    //
    namespace Loki
    {
		/*!
		* Offer a first-class, comparable wrapper over std::type_info
		**/
        class TypeInfo
        {
        public:
			//
			// Constructors
			//
			/*!
			* Default constructor needed for containers
			**/
			TypeInfo(); 

			/*!
			* Non-explicit
			**/
			TypeInfo(const std::type_info&);

			//
			//
			//
			/*!
			* Access for the wrapped std::type_info
			**/
			const std::type_info &Get() const;

			/*!
			* Compatibility functions
			**/
			bool before(const TypeInfo &rhs) const;

			/*!
			*
			**/
			const char *name() const;

        private:
            const std::type_info *m_info;
        };

		//
		// Comparison operators
		//
		/*!
		*
		**/
		inline bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
		{ 
			return (lhs.Get() == rhs.Get()) != 0; 
		}

		/*!
		*
		**/
		inline bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
		{ 
			return lhs.before(rhs); 
		}

		/*!
		*
		**/
		inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
		{ 
			return !(lhs == rhs); 
		}    

		/*!
		*
		**/
		inline bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
		{ 
			return rhs < lhs; 
		}

		/*!
		*
		**/
		inline bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
		{ 
			return !(lhs > rhs); 
		}

		/*!
		*
		**/
		inline bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
		{ 
			return !(lhs < rhs); 
		}

    }
}
#endif
