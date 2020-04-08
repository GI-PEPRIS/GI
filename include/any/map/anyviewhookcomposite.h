/*!
 * The AnyMap of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYMAP_VIEW_HOOK_COMPOSITE_H__
#define __ANYMAP_VIEW_HOOK_COMPOSITE_H__

// refer to export macro
#include "anymap.h"

// refer to parent component
#include "anyviewhook.h"

//
namespace AnyMap
{
	/*!
	*
	**/
	class ANYMAP_CLASS CAnyViewHookComposite : public CAnyViewHook
	{
		//
		typedef std::map<long, CAnyViewHook *> ChildMap;
		typedef ChildMap::iterator child_itr;
		typedef ChildMap::const_iterator child_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyViewHookComposite(CAnyView &curView);
		~CAnyViewHookComposite();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype)
		{

		}

		//
		// composite interface
		//
		/*!
		*
		**/
		void Add(CAnyViewHook *layer);
		void Remove(const long layerIdx);
		CAnyViewHook *GetFirst();
		CAnyViewHook *GetNext();

		//
		//
		//
		/*!
		*
		**/
		bool Query(const CGeoPoint<double> &pt, std::vector<unsigned long> &idxes);
		bool Query(const CGeoRect<double> &rect, std::vector<unsigned long> &idxes, bool isCircle = false);
		bool Query(const std::vector<CGeoPoint<double> > &poly, std::vector<unsigned long> &idxes);

		//
		//
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);

		//
		//
		//
		/*!
		*
		*/
		virtual bool MouseDown(const CGeoPoint<double> &scrPoint);
		virtual bool MouseMove(const CGeoPoint<double> &scrPoint);
		virtual bool MouseUp(const CGeoPoint<double> &scrPoint);
		virtual bool DoubleClick(const CGeoPoint<double> &scrPoint);

	private:
		//
		ChildMap m_children;
		child_itr m_cursor;
	};
}
#endif

