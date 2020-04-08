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
#ifndef __ANYMAP_VIEW_WINIMPL_H__
#define __ANYMAP_VIEW_WINIMPL_H__

// refer to its parent
#include "anyviewimpl.h"

//
namespace AnyMap
{
	// forward class
	class CAnyDC;

	/*!
	*
	**/
	class CWinViewImpl : public CAnyViewImpl
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CWinViewImpl();

		/*!
		*
		**/
		~CWinViewImpl();

	protected:
		//
		//
		//
		/*!
		*
		**/
		bool Attach(void *curWnd, const ScreenPort &scrPort);
		void Detach();
		void *GetBMP();
		void *GetDC();

		//
		//
		//
		/*!
		*
		**/
		void Refresh(bool isDirect = false);
		void OnPaint(bool isDirect = false);
		void RefreshHook(int idx);

	protected:
		//
		//
		//
		/*!
		*
		*/
		void UpFlash(const CGeoPoint<double> &start, const CGeoPoint<double> &end);

		/*!
		*
		*/
		void PanFlash(const CGeoPoint<double> &start, const CGeoPoint<double> &end);

	private:
		//
		//
		//
		/*!
		*
		**/
		CAnyDC *DoCreateDC();

	private:
		// host window
		void *m_curWnd;
		//
		CAnyDC *m_curDC;
	};
}
#endif
