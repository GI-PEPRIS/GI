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
#ifndef __ANYMAP_AGG_ADAPTORS_H__
#define __ANYMAP_AGG_ADAPTORS_H__

// refer to basic
#include "anyviewbasic.h"

// refer to geometry
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to 
#include "agg\include\agg_basics.h"
#include "agg\include\pixel_formats.h"
#include "agg\include\agg_renderer_primitives.h"
#include "agg\include\agg_renderer_scanline.h"
#include "agg\include\agg_rasterizer_outline.h"
#include "agg\include\agg_rasterizer_scanline_aa.h"
#include "agg\include\agg_scanline_p.h"
#include "agg\include\agg_scanline_bin.h"
#include "agg\include\agg_conv_stroke.h"
#include "agg\include\agg_conv_marker.h"
#include "agg\include\agg_conv_concat.h"
#include "agg\include\agg_conv_dash.h"
#include "agg\include\agg_conv_transform.h"
#include "agg\include\agg_conv_contour.h"
#include "agg\include\agg_conv_segmentator.h"
#include "agg\include\agg_conv_transform.h"
#include "agg\include\agg_conv_marker.h"
#include "agg\include\agg_path_storage.h"
#include "agg\include\agg_ellipse.h"
#include "agg\include\agg_font_freetype.h"
#include "agg\include\agg_font_cache_manager.h"
#include "agg\include\agg_trans_single_path.h"
#include "agg\include\agg_span_gradient.h"
#include "agg\include\agg_span_interpolator_linear.h"
#include "agg\include\agg_arrowhead.h"
#include "agg\include\agg_vcgen_markers_term.h"
#include "agg\include\agg_rounded_rect.h"
#include "agg\include\agg_color_rgba.h"
#include "agg\include\agg_conv_bspline.h"
#include "agg\include\agg_bezier_arc.h"
#include "agg\include\agg_span_allocator.h"
using namespace agg;

//
namespace AnyMap
{
	/*!
	*
	**/
	class aggRendererCache 
	{
	public:
		typedef agg::font_engine_freetype_int16 font_engine_type;
		typedef agg::font_cache_manager<font_engine_type> font_manager_type;
		typedef agg::conv_curve<font_manager_type::path_adaptor_type> font_curve_type;
		typedef agg::conv_segmentator<font_curve_type> conv_font_segm_type;
		typedef agg::conv_transform<conv_font_segm_type, agg::trans_single_path> conv_font_trans_type;

	public:
		font_engine_type m_feng;
		font_manager_type m_fman;
		aggRendererCache() : m_fman(m_feng){}
	};

	/*!
	*
	**/
	class my_line_adaptor 
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		my_line_adaptor(const CGeoPoint<double> *const ptsHead, int count);
	    
		/*!
		*
		**/
		virtual ~my_line_adaptor();
	    
	public:
		//
		//
		//
		/*!
		*
		**/
		void rewind(unsigned);
	    
		/*!
		*
		**/
		virtual unsigned vertex(double* x, double* y);

	private:
		//
		short m_cur;
		short m_ptsCount;
		const CGeoPoint<double> *m_ptsHead;
	};

	/*!
	*
	**/
	class polygon_adaptor 
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		polygon_adaptor(const CGeoPoint<double> *const ptsHead, int count);
	    
		/*!
		* a class with virtual functions should also provide a virtual destructor 
		*/
		virtual ~polygon_adaptor();
	    
	public:
		//
		//
		//
		/*!
		*
		**/
		void rewind(unsigned);

		/*!
		*
		**/
		virtual unsigned vertex(double* x, double* y);

	private:
		// 
		short m_cur;
		// 
		short m_ptsCount;
		// 
		const CGeoPoint<double> *m_ptsHead;
		// should next call return stop command
		bool m_stop;
	};

	/*!
	*
	**/
	class gradient_polymorphic_wrapper_base
	{
	public:
		virtual int calculate(int x, int y, int) const = 0;
	};

	/*!
	*
	**/
	template<class GradientF> 
	class gradient_polymorphic_wrapper : public gradient_polymorphic_wrapper_base
	{
	public:
		gradient_polymorphic_wrapper() : m_adaptor(m_gradient) {}
		
		virtual int calculate(int x, int y, int d) const
		{
			return m_adaptor.calculate(x, y, d);
		}
		GradientF m_gradient;
		agg::gradient_reflect_adaptor<GradientF> m_adaptor;
	};

	/*!
	*
	**/
	struct color_function_profile
	{
		color_function_profile() {}
		color_function_profile(const color_type* colors, const agg::int8u* profile) :
		m_colors(colors), m_profile(profile) {}
		
		static unsigned size() { return 256; }
		const color_type& operator [] (unsigned v) const
		{ 
			return m_colors[m_profile[v]]; 
		}
		
		const color_type* m_colors;
		const agg::int8u* m_profile;
	};

	/*!
	*
	**/
	class color_interpolator_rgba8
	{
	public:
		color_interpolator_rgba8(agg::rgba8 c1, agg::rgba8 c2, unsigned len) :
			 m_r(c1.r, c2.r, len),
			 m_g(c1.g, c2.g, len),
			 m_b(c1.b, c2.b, len),
			 m_a(c1.a, c2.a, len)
		{
		}

		void operator ++ ()
		{
			 ++m_r; ++m_g; ++m_b; ++m_a;
		}

		rgba8 color() const
		{
			 return rgba8(m_r.y(), m_g.y(), m_b.y(), m_a.y());
		}

	private:
		dda_line_interpolator<16> m_r;
		dda_line_interpolator<16> m_g;
		dda_line_interpolator<16> m_b;
		dda_line_interpolator<16> m_a;
	};

	/*!
	*
	**/
	template<class Renderer>
	void color_square_rgba8(Renderer& r, int x, int y, int size, rgba8 c1, rgba8 c2, rgba8 c3, rgba8 c4)
	{
		int i, j;
		color_interpolator_rgba8 cy1(c1, c4, size);
		color_interpolator_rgba8 cy2(c2, c3, size);
		for(i = 0; i < size; ++i)
		{
			 color_interpolator_rgba8 cx(cy1.color(), cy2.color(), size);
			 for(j = 0; j < size; ++j)
			 {
				 r.copy_pixel(x + j, y + i, cx.color());
				 ++cx;
			 }
			 ++cy1;
			 ++cy2;
		}
	}

	/*!
	* A simple function to form the gradient color array consisting of 3 colors, "begin", "middle", "end"
	**/
	template<class Array>
	void fill_color_array(Array& array, 
							agg::rgba8 begin, 
							agg::rgba8 middle, 
							agg::rgba8 end)
	{
		unsigned i;
		unsigned half_size = array.size() / 2;
		for(i = 0; i < half_size; ++i)
		{
			 array[i] = begin.gradient(middle, i / double(half_size));
		}
		for(; i < array.size(); ++i)
		{
			 array[i] = middle.gradient(end, (i - half_size) / double(half_size));
		}
	}

	/*!
	*
	**/
	template<class Source> struct stroke_fine_arrow
	{
		typedef agg::conv_stroke<Source, agg::vcgen_markers_term>                   stroke_type;
		typedef agg::conv_marker<typename stroke_type::marker_type, agg::arrowhead> marker_type;
		typedef agg::conv_concat<stroke_type, marker_type>                          concat_type;

		stroke_type    s;
		agg::arrowhead ah;
		marker_type    m;
		concat_type    c;

		stroke_fine_arrow(Source& src, double w) : 
			 s(src),
			 ah(),
			 m(s.markers(), ah),
			 c(s, m)
		{
			 s.width(w); 
			 ah.head(0, 10, 5, 0);
			 s.shorten(w * 2.0);
		}

		void rewind(unsigned path_id) { c.rewind(path_id); }
		unsigned vertex(double* x, double* y) { return c.vertex(x, y); }
	};

	/*!
	*
	**/
	template<class Source> 
	struct dash_stroke_fine_arrow
	{
		typedef agg::conv_dash<Source, agg::vcgen_markers_term>                   dash_type;
		typedef agg::conv_stroke<dash_type>                                       stroke_type;
		typedef agg::conv_marker<typename dash_type::marker_type, agg::arrowhead> marker_type;
		typedef agg::conv_concat<stroke_type, marker_type>                        concat_type;

		dash_type      d;
		stroke_type    s;
		agg::arrowhead ah;
		marker_type    m;
		concat_type    c;

		dash_stroke_fine_arrow(Source& src, 
							   double dash_len, double gap_len, double w, short scaleLevel) : 
			d(src),
			s(d),
			ah(),
			m(d.markers(), ah),
			c(s, m)
		{
			d.add_dash(dash_len, gap_len);
			d.dash_start(0.);
			s.width(w);

			double various = (5-scaleLevel) > 0. ? (5-scaleLevel) : 1;
			ah.head(5*various, 1*various, 4*various, 2*various);
			d.shorten(w * 2.0);
		}

		void rewind(unsigned path_id) { c.rewind(path_id); }
		unsigned vertex(double* x, double* y) { return c.vertex(x, y); }
	};
}

#endif