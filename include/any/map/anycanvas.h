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
#ifndef __ANYMAP_CANVAS_H__
#define __ANYMAP_CANVAS_H__

// refer to EXPORT & IMPORT
#include "anymap.h"

// refer to coordinate
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to basic definitions
#include "anycanvasbasic.h"

//
namespace AnyMap
{
	#define ANY_SRCCOPY             (unsigned long)0x00CC0020 /* dest = source                   */
	#define ANY_SRCPAINT            (unsigned long)0x00EE0086 /* dest = source OR dest           */
	#define ANY_SRCAND              (unsigned long)0x008800C6 /* dest = source AND dest          */
	#define ANY_SRCINVERT           (unsigned long)0x00660046 /* dest = source XOR dest          */
	#define ANY_SRCERASE            (unsigned long)0x00440328 /* dest = source AND (NOT dest )   */
	#define ANY_NOTSRCCOPY          (unsigned long)0x00330008 /* dest = (NOT source)             */
	#define ANY_NOTSRCERASE         (unsigned long)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
	#define ANY_MERGECOPY           (unsigned long)0x00C000CA /* dest = (source AND pattern)     */
	#define ANY_MERGEPAINT          (unsigned long)0x00BB0226 /* dest = (NOT source) OR dest     */
	#define ANY_PATCOPY             (unsigned long)0x00F00021 /* dest = pattern                  */
	#define ANY_PATPAINT            (unsigned long)0x00FB0A09 /* dest = DPSnoo                   */
	#define ANY_PATINVERT           (unsigned long)0x005A0049 /* dest = pattern XOR dest         */
	#define ANY_DSTINVERT           (unsigned long)0x00550009 /* dest = (NOT dest)               */
	#define ANY_BLACKNESS          (unsigned long)0x00000042 /* dest = BLACK                    */
	#define ANY_WHITENESS           (unsigned long)0x00FF0062 /* dest = WHITE                    */

	/*!
	*
	**/
	class ANYMAP_CLASS CAnyCanvas
	{
	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyCanvas();
		virtual ~CAnyCanvas();

	public:
		//
		// pixel operations
		//
		/*!
		*
		**/
		virtual unsigned int GetBkColor() = 0;
		virtual void SetPixel(int row, int col, unsigned int clr) = 0;
		virtual unsigned int GetPixel(int row, int col) = 0;
		virtual void BlendPixel(int row, int col, unsigned int clr, unsigned short alpha) = 0;
		virtual void SetRenderModel(unsigned int model) = 0;
		virtual unsigned int GetRenderModel() = 0;
		void SetHighQuality(bool isHighQuality)
		{
			m_isHighQuality = isHighQuality;
		}

		//
		// basic primitives
		//
		/*!
		*
		**/
		virtual void RenderLine(const CGeoPoint<double> *const pts, int number, const LineStyle &style) = 0;
		virtual void RenderPolygon(const CGeoPoint<double> *const pts, int number, const PolyStyle &style) = 0;
		virtual void RenderEllipse(const CGeoPoint<double> &pos, double a, double b, const SymbolStyle &style) = 0;
		virtual void RenderRectangle(const CGeoRect<double> &rect, const SymbolStyle &style) = 0;
		virtual CGeoPoint<double> RenderGlyphs(const CGeoPoint<double> &pos, const LabelStyle &style, const char *const text, CGeoPoint<double> *alongPts = 0, int number = 0) = 0;
		virtual CGeoPoint<double> RenderGlyphs(const CGeoPoint<double> &pos, const LabelStyle &style, unsigned short txtcode, CGeoPoint<double> *alongPts = 0, int number = 0) = 0;
		virtual void RenderBSpline(const CGeoPoint<double> *const pts, int number, const LineStyle &style) = 0;
		virtual void RenderBezierArc(const CGeoPoint<double> &center, double rx, double ry, double startangle, double sweepangle, const PolyStyle &style) = 0;
		virtual void RenderBezierArcLine(const CGeoPoint<double> &center, double rx, double ry, double startangle, double sweepangle, const LineStyle &style) = 0;
		virtual void RenderRasterImage(void *image, const CGeoRect<double> &dev, const CGeoRect<double> &bmp, bool isBlend = false) = 0;

		//
		// TODO: senior operations
		//
		/*!
		*
		**/
		static void GetInterpolations(const CGeoPoint<double> *const ctrlPts, int ctrlNumber, CGeoPoint<double> **interPts, int &interNumber, double interpolations = 20.);
		virtual void EraseBackGround(unsigned int bkColor) = 0;
		virtual void LoadFont(const string &fontname) = 0;
		virtual void GetDefaultCharacter(short size, unsigned from, unsigned to, std::vector<unsigned short> &characters) = 0;

	protected:
		//
		bool m_isHighQuality;
	public:
		//
		string m_curfontname;
	};
}

#endif