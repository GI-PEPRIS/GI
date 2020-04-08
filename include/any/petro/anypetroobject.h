/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYPETRO_PETRO_OBJECT_H__
#define __ANYPETRO_PETRO_OBJECT_H__

// Refer to EXPORT etc
#include "anypetro.h"

// refer to its parent
#include "any/base/anyobject.h"
using namespace AnyBase;

// refer to thread issue
#include "any/thread\jtc.h"

#include "any/db/anyaccessor.h"
using namespace AnyDB;
#include "any/base/anystl.h"

// namespace 
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CAnyPetroObject : public CAnyObject, public JTCMonitor
	{
		// composite container
		typedef std::vector<CAnyPetroObject *> ComponentVector;
		typedef ComponentVector::iterator cmp_itr;
		typedef ComponentVector::const_iterator cmp_citr;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyPetroObject();

		/*!
		*
		**/
		CAnyPetroObject(CAnyPetroObject *parent);

		/*!
		*
		**/
		virtual ~CAnyPetroObject();

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual bool IsDirty();

		/*!
		*
		**/
		virtual void SetDirty(bool isDirty);

		//
		//
		//
		/*!
		*
		**/
		short GetChildCount();

		/*!
		*
		**/
		CAnyPetroObject *GetChild(int index);

		/*!
		*
		**/
		void AddChild(CAnyPetroObject *child);

		/*!
		*
		**/
		template<class T>
		CAnyPetroObject *FindChild(long idx)
		{
			// current level
			CAnyPetroObject *cmp = new T;
			cmp->SetIdx(idx);
			cmp_itr itr = std::lower_bound(m_children.begin(), m_children.end(), cmp, CompareChildIdx);
			if(itr != m_children.end() && (*itr)->m_idx == idx)
			{
				delete cmp;
				return *itr;
			}
			delete cmp;

			// recursively loop next level
			int i = 0;
			int count = m_children.size();
			for(; i < count; i++)
			{
				return m_children[i]->FindChild<T>(idx);
			}

			return 0;
		}

		/*!
		*
		**/
		void RemoveChild(int index);

		/*!
		*
		**/
		bool RemoveChild(CAnyPetroObject *child);

		/*!
		*
		**/
		CAnyPetroObject *GetParent();

		/*!
		*
		**/
		CAnyPetroObject *GetPrevChild();

		/*!
		*
		**/
		CAnyPetroObject *GetNextChild();

	private:
		//
		//
		//
		/*!
		*
		**/
		bool IsChildrenDirty();

		/*!
		*
		**/
		static bool CompareChildIdx(const CAnyPetroObject *first, const CAnyPetroObject *second);

	public:
		// children
		ComponentVector m_children;
		std::set<int> m_childrenSet;
		// its parent
		CAnyPetroObject *m_parent;
		// sibling
		CAnyPetroObject *m_prev;
		CAnyPetroObject *m_next;
	};
}

#endif