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
#ifndef __ANYMAP_DC_BASIC_H__
#define __ANYMAP_DC_BASIC_H__

// refer to export
#include "anymap.h"

// refer to basic structure
#include "anyviewbasic.h"

// namespace AnyMap
namespace AnyMap
{
	/*!
	*
	**/
	class ANYMAP_CLASS CAnyDC
	{
		// relatives
		friend class CAggDC;
		friend class CWinDC;
		friend class CWinViewImpl;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyDC();

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyDC(const CGeoRect<double> &layout, const CGeoPoint<double> &bufBase, unsigned int bkColor);
		virtual ~CAnyDC();

	private:
		//
		CAnyDC(const CAnyDC &other);
		const CAnyDC &operator=(const CAnyDC &other);

    public:
		//
		//
		//
		/*!
		*
		*/
		virtual void SetBase(const CGeoPoint<double> &portOrg);
		virtual const CGeoPoint<double> &GetBase() const;
		virtual const CGeoRect<double> &GetExtent() const;

		/*!
		*
		*/
		virtual void *GetDC() const;
		virtual void *GetBmp() const;
		virtual void *GetBmpBits() const;
		virtual unsigned int GetBkColor() const;
		virtual void SetBkColor(unsigned int clr);
		virtual void SetRenderModel(unsigned int model)
		{
			m_rendermodel = model;
		}
		unsigned int GetRenderModel()
		{
			return m_rendermodel;
		}

		//
		//
		//
		/*!
		*
		*/
		virtual void SetPixel(int row, int col, unsigned int clr);
		virtual unsigned int GetPixel(int row, int col);
		virtual void BlendPixel(int row, int col, unsigned int clr, unsigned short alpha);

		//
		//
		//
		/*!
		*
		**/
		virtual void Release() = 0; 
		virtual void DrawClipped() = 0;
		virtual bool MergedTo(void *otherDC, const CGeoPoint<double> &start, const CGeoPoint<double> &end) = 0;
		virtual bool CopyTo(void* otherDC, const CGeoPoint<double> &start, const CGeoPoint<double> &end) = 0;

	protected:
		// Saves HDC and scr setting passed in constructor
		void *m_memDC;

		// Buffer setting
		CGeoPoint<double> m_base;
		CGeoRect<double> m_extent;

		//
		CGeoRect<double> m_clipBox;
		CGeoPoint<double> m_offset;
		bool m_isRefresh;

		//
		unsigned int m_bkColor;

		// For 2.5D rendering better effects
		unsigned char *m_bitmapBits;
		int m_pixelCoff;

		// Bitmap setting for this memory dc
		void *m_bitmap;
		void *m_oldBitmap;

		//
		unsigned int m_rendermodel;
	};
}

#endif