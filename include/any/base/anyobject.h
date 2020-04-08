/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_OBJECT_H__
#define __ANYBASE_OBJECT_H__

// refer to EXPORT etc
#include "anybase.h"

// refer to type info
#include "anystl.h"

// 
namespace AnyBase
{
	/*!
	*
	**/
	class ANYBASE_CLASS CAnyObject
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyObject();

		/*!
		*
		**/
		virtual ~CAnyObject();

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual unsigned int Commit(bool isDeleted = false) = 0;

		//
		// 
		//
		/*!
		*
		**/
		virtual void SetIdx(unsigned long idx)
		{
			assert(idx > 0);
			m_idx = idx;
		}

		/*!
		*
		**/
		virtual unsigned long GetIdx() const
		{
			return m_idx;
		}

		/*!
		*
		**/
		virtual bool IsDirty()
		{
			return m_isDirty;
		}

		/*!
		*
		**/
		virtual void SetDirty(bool isDirty = true)
		{
			m_isDirty = isDirty;
		}

		/*!
		*
		**/
		virtual const string &GetName() const
		{
			return m_name;
		}

		/*!
		*
		**/
		virtual void SetName(const string &name)
		{
			assert(name.size());
			m_name = name;
		}

		/*!
		*
		**/
		virtual void SetType(unsigned long type)
		{
			m_type = type;
		}

		/*!
		*
		**/
		virtual unsigned long GetType() const
		{
			return m_type;
		}

		//
		//
		//
		/*!
		*
		**/
		virtual const char *GetTypeName() = 0;
		
		/*!
		*
		**/
		virtual bool IsSameType(const CAnyObject *other) = 0;

	protected:
		// unique idx
		unsigned long m_idx;

		// type
		unsigned long m_type;

		// name
		string m_name;

		// flag to status
		bool m_isDirty;
	};
}

#endif