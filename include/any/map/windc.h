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
#ifndef __ANYMAP_WINDC_H__
#define __ANYMAP_WINDC_H__

// refer to its parent
#include "anydc.h"

//
namespace AnyMap
{
	/*!
	*
	*/
    class CWinDC : public CAnyDC
    {
		// relatives
		friend class CWinViewImpl;

    public:
		//
		//
		//
		/*!
		*
		*/
		CWinDC(const CGeoRect<double> &layout, const CGeoPoint<double> &bufBase, unsigned int bkColor = RGB(255, 255, 255));

		/*!
		*
		*/
		virtual ~CWinDC();

    public:
		//
		//
		//
		/*!
		*
		*/
		void DrawBackGround(unsigned int bkColor);

		//
		//
		//
		/*!
		*
		**/
		void Release()
		{
		}

		/*!
		*
		*/
		void DrawClipped()
		{
		}

		/*!
		*
		*/
		bool MergedTo(void *otherDC, const CGeoPoint<double> &start, const CGeoPoint<double> &end);

		/*!
		*
		*/
		bool CopyTo(void *otherDC, const CGeoPoint<double> &start, const CGeoPoint<double> &end);

    protected:
		//
		//
		//
		/*!
		*
		*/
		void GetClipBox(const CGeoPoint<double> &start, const CGeoPoint<double> &end, RECT &srcRect, RECT &clipBox);

		/*!
		*
		*/
		bool CreateBitmap();
	};
}

#endif