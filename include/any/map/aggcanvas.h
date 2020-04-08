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
#ifndef __ANYMAP_AGG_CANVAS_H__
#define __ANYMAP_AGG_CANVAS_H__

// refer to agg
#include "aggadaptors.h"

// refer to its parent
#include "anycanvas.h"

#include "any/thread/mutex.h"

//
namespace AnyMap
{
	// forward class
	class CAggDC;
	
	/*!
	*
	**/
	class CAggCanvas : public CAnyCanvas
	{
		//
		typedef agg::renderer_base<pixfmt> renderer_base;
		typedef agg::renderer_scanline_aa_solid<renderer_base> renderer_solid;
		typedef agg::renderer_scanline_bin_solid<renderer_base> renderer_bin;
		typedef agg::renderer_primitives<renderer_base> renderer_primitives;
		typedef agg::rasterizer_outline<renderer_primitives> outline_rasterizer;

		//
		typedef agg::pod_auto_array<color_type, 256> color_array_type;
		typedef agg::gradient_radial_d gradient_function;
		typedef agg::span_interpolator_linear<> interpolator_type;

		typedef agg::span_gradient<agg::rgba8, interpolator_type, gradient_polymorphic_wrapper_base, color_array_type> gradient_span_gen;
#ifdef AGG_2.1		
		typedef agg::span_allocator<agg::rgba8> gradient_span_alloc;
		typedef agg::renderer_scanline_aa<renderer_base, gradient_span_gen> renderer_gradient;
#endif
		typedef agg::span_allocator<gradient_span_gen::color_type> gradient_span_alloc;
		typedef agg::renderer_scanline_aa<renderer_base, gradient_span_alloc,gradient_span_gen> renderer_gradient;

		//
		#define AGG_LINESPACE 1.33

		//
		#define AGG_COLOR(c) agg::rgba8_pre(c.m_red, c.m_green, c.m_blue, c.m_alpha)
		#define AGG_MIN(a,b) (((a)<(b))?(a):(b))
		#define AGG_MAX(a,b) (((a)>(b))?(a):(b))
		#define AGG_ABS(a) (((a)<0) ? -(a) : (a))
		#define AGG_SGN(a) (((a)<0) ? -1 : 1)
		#define AGG_NINT(x) ((x) >= 0.0 ? ((long) ((x)+.5)) : ((long) ((x)-.5)))

	public:
		//
		//
		//
		/*!
		*
		**/
		CAggCanvas(CAggDC *curDC);
		~CAggCanvas();

	public:
		//
		//
		//
		/*!
		*
		**/
		void EraseBackGround(unsigned int bkColor);

	public:
		//
		//
		//
		/*!
		*
		**/
		void Prepare();
		void Release();

		//
		//
		//
		/*!
		*
		**/
		unsigned int GetBkColor();
		void SetPixel(int row, int col, unsigned int clr);
		unsigned int GetPixel(int row, int col);
		void BlendPixel(int row, int col, unsigned int clr, unsigned short alpha);
		void SetRenderModel(unsigned int model);
		unsigned int GetRenderModel();

		//
		//
		//
		/*!
		*
		**/
		void RenderLine(const CGeoPoint<double> *const pts, int number, const LineStyle &style);
		void RenderPolygon(const CGeoPoint<double> *const pts, int number, const PolyStyle &style);
		void RenderRectangle(const CGeoRect<double> &rect, const SymbolStyle &style);
		void RenderEllipse(const CGeoPoint<double> &pos, double a, double b, const SymbolStyle &style);
		CGeoPoint<double> RenderGlyphs(const CGeoPoint<double> &pos, const LabelStyle &style, const char *const text, CGeoPoint<double> *alongPts = 0, int number = 0);
		CGeoPoint<double> RenderGlyphs(const CGeoPoint<double> &pos, const LabelStyle &style, unsigned short txtcode, CGeoPoint<double> *alongPts = 0, int number = 0);
		void RenderBSpline(const CGeoPoint<double> *const pts, int number, const LineStyle &style);
		void RenderBezierArc(const CGeoPoint<double> &center, double rx, double ry, double startangle, double sweepangle, const PolyStyle &style);
		void RenderBezierArcLine(const CGeoPoint<double> &center, double rx, double ry, double startangle, double sweepangle, const LineStyle &style);
		void RenderRasterImage(void *image, const CGeoRect<double> &dev, const CGeoRect<double> &bmp, bool isBlend = false);

		//
		//
		//
		/*!
		*
		**/
		void RenderMapOperationTrack(const CGeoPoint<double> *const pts, int number, int mode);
		void LoadFont(const string &fontname);
		void GetDefaultCharacter(short size, unsigned from, unsigned to, std::vector<unsigned short> &characters);

		//
		//
		//
		/*!
		*
		**/
		static void GetInterpolations(const CGeoPoint<double> *const ctrlPts, int ctrlNumber, CGeoPoint<double> **interPts, int &interNumber, double interpolations = 20.);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderWithGradients(const GradientStyle &style, const agg::trans_affine &mtx);

		//
		//
		//
		/*!
		*
		**/
		template<class VertexSource>
		static void ApplyJoinCorner(VertexSource &stroke, int caps, int joins);

	private:
		//
		unsigned int m_bkColor;
		CAggDC *m_curDC;

		//
		pixfmt *m_pixFormat;
		renderer_base *m_renderBase;

		// For quick performance issue in draft rendering way
		renderer_solid *m_renderSolid;
		renderer_bin *m_renderBin;
		renderer_primitives *m_renderPrim;
		outline_rasterizer *m_renderOutline;
		renderer_gradient *m_renderGradient;

		// scan way
		agg::rasterizer_scanline_aa<> m_aRasterizer;
		agg::scanline_p8 m_pRasterizer;
		agg::scanline_bin m_bRasterizer;

		//
		static aggRendererCache m_fontcache;
		JTCMutex m_mutex;
	};
}

#endif