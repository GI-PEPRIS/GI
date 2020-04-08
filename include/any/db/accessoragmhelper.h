/*!
 * The AnyDB of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the persistence-related architectural patterns such as MAPPER etc.
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
#ifndef __ANYDB_ACCESSOR_AGM_HELPER_H__
#define __ANYDB_ACCESSOR_AGM_HELPER_H__

// Refer to EXPORT etc
#include "anydb.h"

#include "any/base/agm/reflection.hpp" // compile conflict with RCF
#include "anyaccessor.h"

//
namespace AnyDB
{
	/*!
	*
	**/
	class ANYDB_CLASS CAccessorAgmHelper
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAccessorAgmHelper(CAnyAccessor &accessor);

		/*!
		*
		**/
		~CAccessorAgmHelper();

	public:

		/*!
		*  Fill Data
		**/
		template<typename T>
		bool GetData(T* object,const agm::reflection::Field2 &field,int& index )
		{

			string type=field.getType();
			string name=field.getName();
			if(type=="long" ||type=="unsigned long")
			{
				long val;
				field.get(val,object);
				m_accessor.m_impl->BindLong(index++,val);
			}
			else if(type=="int" ||type=="unsigned int"|| type=="short" ||type=="unsigned short")
			{
				int val;
				field.get(val,object);
				m_accessor.m_impl->BindInt(index++,val);
			}
			else if(type=="string")
			{
				string val;
				field.get(val,object);
				((CAnyAccessorImpl *)m_accessor.m_impl)->BindString(index++,val);
			}
			else if(type=="bool" ||type=="boolean")
			{
				bool val;
				field.get(val,object);
				m_accessor.m_impl->BindBool(index++,val);
			}
			else if(type=="char" ||type=="unsigned char")
			{
				char val;
				field.get(val,object);
				m_accessor.m_impl->BindChar(index++,val);
			}
			else if(type=="float"||type=="unsigned float")
			{
				float val;
				field.get(val,object);
				m_accessor.m_impl->BindFloat(index++,val);
			}
			else if(type=="double"||type=="unsigned double")
			{
				double val;
				field.get(val,object);
				m_accessor.m_impl->BindDouble(index++,val);
			}
			else
			{
				return false;
			}
			return true;
		}

		/*!
		*  bind all data in object to the generated sql statement
		**/
		template<typename T>
		bool DirectBind(T* object,std::vector<int> FilterFields=std::vector<int>())
		{
			//const Class &myClass=object->getClass();
			const Class * cls = Class::forType(typeid(T));
			const Class &myClass=*cls;
			int index=0;//index of ?
			int structIndex=0;

			if(myClass.hasSuper())
			{
				const Class &superClass=myClass.getSuper();

				for(agm::reflection::Class::FieldList::const_iterator itField = superClass.getFields().begin();
					itField != superClass.getFields().end();
					++itField)
				{
					const agm::reflection::Field2 &field = **itField;
					std::vector<int>::iterator it=find(FilterFields.begin(),FilterFields.end(),structIndex++);
					if(it!=FilterFields.end())
					{
						continue;
					}
					const Class * cls = Class::forType(typeid(T));
					if(!GetData(object,field,index))
					{
						return false;
					}
				}
			}

			for(agm::reflection::Class::FieldList::const_iterator itField = myClass.getFields().begin();
				itField != myClass.getFields().end();
				++itField)
			{
				const agm::reflection::Field2 &field = **itField;
				std::vector<int>::iterator it=find(FilterFields.begin(),FilterFields.end(),structIndex++);
				if(it!=FilterFields.end())
				{
					continue;
				}
				const Class * cls = Class::forType(typeid(T));
				if(!GetData(object,field,index))
				{
					return false;
				}
			}
			return true;
		}

		/*!
		*  Fill Data
		**/
		template<typename T>
		bool FillData(T* object,const agm::reflection::Field2 &field,int& index )
		{
			string type=field.getType();
			string name=field.getName();
			string value;
			if(type=="long" ||type=="unsigned long")
			{
				m_accessor.m_impl->FetchField(index++, value);
				long val=::atoi(value.c_str());
				field.set(object,val);
			}
			else if(type=="int" ||type=="unsigned int"|| type=="short" ||type=="unsigned short")
			{
				m_accessor.m_impl->FetchField(index++, value);
				int val=::atoi(value.c_str());
				field.set(object,val);
			}
			else if(type=="string")
			{
				m_accessor.m_impl->FetchField(index++, value);
				field.set(object,value);
			}
			else if(type=="bool" ||type=="boolean")
			{
				m_accessor.m_impl->FetchField(index++, value);
				bool val=::atoi(value.c_str());
				field.set(object,val);
			}
			else if(type=="char" ||type=="unsigned char")
			{
				m_accessor.m_impl->FetchField(index++, value);
				char val=value.c_str()[0];
				field.set(object,val);
			}
			else if(type=="float"||type=="unsigned float")
			{
				m_accessor.m_impl->FetchField(index++, value);
				float val=::atof(value.c_str());
				field.set(object,val);
			}
			else if(type=="double"||type=="unsigned double")
			{
				m_accessor.m_impl->FetchField(index++, value);
				double val=::atof(value.c_str());
				field.set(object,val);
			}
			else
			{
				return false;
			}
			return true;
		}

		/*!
		*  load data from accessor(FetchField()) to the object.
		* given the order of fields of current structure strictly corresponds to DB schema
		**/
		template<typename T>
		bool DirectLoad(T* object)
		{
			const Class &myClass=object->getClass();
			int index=0;//index of ?
			if(myClass.hasSuper())
			{
				const Class &superClass=myClass.getSuper();

				for(agm::reflection::Class::FieldList::const_iterator itField = superClass.getFields().begin();
					itField != superClass.getFields().end();
					++itField)
				{
					const agm::reflection::Field2 &field = **itField;
					if(!FillData(object,field,index))
					{
						return false;
					}
				}
			}
			
			for(agm::reflection::Class::FieldList::const_iterator itField = myClass.getFields().begin();
				itField != myClass.getFields().end();
				++itField)
			{
				const agm::reflection::Field2 &field = **itField;
				if(!FillData(object,field,index))
				{
					return false;
				}
				
			}
			return true;
		}

	private:
		CAnyAccessor &m_accessor;
	};
}

#endif