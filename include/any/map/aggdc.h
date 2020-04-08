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
#ifndef __ANYMAP_AGGDC_H__
#define __ANYMAP_AGGDC_H__

// refer to its parent
#include "anydc.h"

// refer to buffer definition
#include "agg\include\agg_rendering_buffer.h"
using namespace agg;

// Delcare namespace
namespace AnyMap
{
	/*!
	*
	*/
	class CAggDC : public CAnyDC
	{
		// relatives
		friend class CAggCanvas;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAggDC();

		/*!
		*
		*/
		CAggDC(CAnyDC *winDC, bool isDirect = false);

		/*!
		*
		**/
		virtual ~CAggDC();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Release();
		void DrawClipped();

		//
		//
		//
		/*!
		*
		*/
		bool MergedTo(void *otherDC, const CGeoPoint<double> &start, const CGeoPoint<double> &end);
		bool CopyTo(void *otherDC, const CGeoPoint<double> &start, const CGeoPoint<double> &end);

	protected:
		//
		//
		//
		/*!
		*
		**/
		agg::rendering_buffer &GetRenderingBuf()
		{
			return m_curBuf;
		}

		/*!
		*
		*/
		bool CreateBitmap(CAnyDC *oneDC);

		/*!
		*
		**/
		static int GetStride(int width, int bitsPerPixel);

	private:
		// the host DC which be decorated by agg
		CAnyDC *m_winDC;

		// how many bytes skipped when using differnt BPP
		int m_stride;

		// rendering buffer
		bool m_isDirect;
		unsigned char **m_rowBits;
		agg::rendering_buffer m_curBuf;
	};
}
#endif