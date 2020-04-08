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
#ifndef __ANYMAP_CANVAS_BASIC_H__
#define __ANYMAP_CANVAS_BASIC_H__

//
namespace AnyMap
{
	/*!
	*
	**/
	enum GradientType
	{
		GT_Unknown = -1,
		GT_Circle,
		GT_X,
		GT_Y,
		GT_XY,
		GT_Diamond,
		GT_SQRT_XY,
		GT_Conic,
	};

	/*!
	* style of join corner
	**/
	enum JointCornerType
	{
		JCT_NONE, 
		JCT_BEVEL, 
		JCT_BUTT, 
		JCT_MITER, 
		JCT_ROUND, 
		JCT_SQUARE, 
		JCT_TRIANGLE
	}; 

	static char FontName[9][127] = { \
		"google",
		"arial",
		"solo5",
		"korean",
		"dfhei5a",
		"bluehigh",
		"bluecond",
		 "bluebold",
		"simsun",
	};

	/*!
	*
	**/
	struct ColorStyle
	{
		int m_red;
		int m_green;
		int m_blue;
		int m_alpha;

		/*!
		*
		**/
		ColorStyle() : m_red(0), m_green(0), m_blue(0), m_alpha(255)
		{
		}

		/*!
		*
		**/
		ColorStyle(const ColorStyle &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const ColorStyle &operator=(const ColorStyle &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_red = other.m_red;
			m_green = other.m_green;
			m_blue = other.m_blue;
			m_alpha = other.m_alpha;

			return *this;
		}
	};

	/*!
	*
	**/
	struct GradientStyle
	{
		short m_type;
		double m_firstx;	// gradient extent
		double m_lastx;	// gradient extent
		ColorStyle m_begin;
		ColorStyle m_middle;
		ColorStyle m_end;

		/*!
		*
		**/
		GradientStyle() : m_type(GT_Unknown), m_firstx(1.), m_lastx(1.)
		{
		}

		/*!
		*
		**/
		GradientStyle(const GradientStyle &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const GradientStyle &operator=(const GradientStyle &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_type = other.m_type;
			m_begin = other.m_begin;
			m_middle = other.m_middle;
			m_end = other.m_end;
			m_firstx = other.m_firstx;
			m_lastx = other.m_lastx;

			return *this;
		}
	};

	/*!
	*
	**/
	struct ArrowStyle
	{
		double m_first;
		double m_second;
		double m_third;
		double m_fourth;

		/*!
		*
		**/
		ArrowStyle() : m_first(0.), m_second(0.), m_third(0.), m_fourth(0.)
		{
		}

		/*!
		*
		**/
		ArrowStyle(const ArrowStyle &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const ArrowStyle &operator=(const ArrowStyle &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_first = other.m_first;
			m_second = other.m_second;
			m_third = other.m_third;
			m_fourth = other.m_fourth;

			return *this;
		}

		/*!
		*
		**/
		bool IsWithArraw() const
		{
			return !(m_second == m_third);
		}
	};

	/*!
	*
	**/
	enum GeometryStyleType
	{
		GST_Unknown = -1,
		GST_Line,
		GST_Polygon,
		GST_Symbol,
		GST_Label,
		GST_Max
	};

	/*!
	* dummy parent
	**/
	struct GeometryStyle
	{
		GeometryStyleType m_styleType;
	};

	/*!
	*
	**/
	struct LineStyle : public GeometryStyle
	{
		//
		static const int MS_MAXPATTERNLENGTH = 10;

		// line width in pixels
		double m_width;

		// line pattern, e.g. dots, dashes, etc..
		int m_patternlength;
		double m_pattern[MS_MAXPATTERNLENGTH];

		// must be a valid color if not NULL
		// color.alpha must be used if supported by the renderer */
		ColorStyle m_color;
		GradientStyle m_gradient;
		ArrowStyle m_arrow;

		// MS_CJC_TRIANGLE, MS_CJC_SQUARE, MS_CJC_ROUND, MS_CJC_BUTT
		// MS_CJC_BEVEL MS_CJC_ROUND MS_CJC_MITER
		int m_linecap;
		int m_linejoin;
		double m_linejoinmaxsize;

		/*!
		*
		**/
		LineStyle() 
			: m_width(1.), m_patternlength(0.), m_linecap(0), m_linejoin(0), m_linejoinmaxsize(0.)
		{
			::memset(m_pattern, 0x00, sizeof(double) * MS_MAXPATTERNLENGTH);
			m_styleType = GST_Line;
		}

		/*!
		*
		**/
		LineStyle(const LineStyle &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const LineStyle &operator=(const LineStyle &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_styleType = other.m_styleType;

			//
			m_width = other.m_width;
			m_patternlength = other.m_patternlength;
			m_color = other.m_color;
			m_gradient = other.m_gradient;
			m_arrow = other.m_arrow;

			m_linecap = other.m_linecap;
			m_linejoin = other.m_linejoin;
			m_linejoinmaxsize = other.m_linejoinmaxsize;

			int i = 0;
			for(; i < MS_MAXPATTERNLENGTH; i++)
			{
				m_pattern[i] = other.m_pattern[i];
			}

			return *this;
		}
	};

	/*!
	*
	**/
	struct PolyStyle : public GeometryStyle
	{
		//
		static const int MS_MAXPATTERNLENGTH = 10;

		// line pattern, e.g. dots, dashes, etc..
		int m_patternlength;
		double m_pattern[MS_MAXPATTERNLENGTH];

		// must be a valid color if not NULL
		// color.alpha must be used if supported by the renderer */
		ColorStyle m_color;
		GradientStyle m_gradient;

		// line width in pixels
		double m_linewidth;
		ColorStyle m_linecolor;
		int m_linecap;
		int m_linejoin;

		/*!
		*
		**/
		PolyStyle() : m_linewidth(1.), m_patternlength(0.)
		{
			::memset(m_pattern, 0x00, sizeof(double) * MS_MAXPATTERNLENGTH);
			m_styleType = GST_Polygon;
		}

		/*!
		*
		**/
		PolyStyle(const PolyStyle &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const PolyStyle &operator=(const PolyStyle &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_styleType = other.m_styleType;

			//
			m_patternlength = other.m_patternlength;
			m_color = other.m_color;
			m_gradient = other.m_gradient;
			m_linewidth = other.m_linewidth;
			m_linecolor = other.m_linecolor;
			m_linecap = other.m_linecap;
			m_linejoin = other.m_linejoin;

			int i = 0;
			for(; i < MS_MAXPATTERNLENGTH; i++)
			{
				m_pattern[i] = other.m_pattern[i];
			}

			return *this;
		}
	};

	/*!
	*
	**/
	struct LabelStyle : public GeometryStyle
	{
		// whether to label THIS fld
		string m_fldName;
		unsigned long m_fldIdx;

		// full path to truetype font file
		char m_font[1024];
		double m_size;
		double m_rotation;
		ColorStyle m_color;
		double m_outlinewidth;
		ColorStyle m_outlinecolor;

		/*!
		*
		**/
		LabelStyle() : m_fldName(""), m_fldIdx(0), m_size(10), m_rotation(0.), m_outlinewidth(0.)
		{
			::strcpy(m_font, "google");
			m_styleType = GST_Label;
		}

		/*!
		*
		**/
		LabelStyle(const LabelStyle &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const LabelStyle &operator=(const LabelStyle &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_styleType = other.m_styleType;
			m_fldName = other.m_fldName;
			m_fldIdx = other.m_fldIdx;

			//
			::strcpy(m_font, other.m_font);
			m_size = other.m_size;
			m_rotation = other.m_rotation;
			m_color = other.m_color;
			m_outlinewidth = other.m_outlinewidth;
			m_outlinecolor = other.m_outlinecolor;

			return *this;
		}
	};

	/*!
	*
	**/
	struct SymbolStyle : public GeometryStyle
	{
		// must be valid colors if not NULL
		// color.alpha must be used if supported by the renderer
		ColorStyle m_color;
		ColorStyle m_backgroundcolor;

		// gradient-related
		GradientStyle m_gradient;
		double m_outlinewidth;
		ColorStyle m_outlinecolor;
		// scalefactor to be applied on the tile or symbol
		double m_scale;
		//rotation to apply on the symbol (and the tile?) in radians
		double m_rotation;
		// the gap to space symbols appart when used as a polygon tile
		double m_gap;
		double m_radius;

		/*!
		*
		**/
		SymbolStyle() : m_radius(2.), m_rotation(0.), m_scale(1.), m_outlinewidth(0.), m_gap(0.)
		{
			m_styleType = GST_Symbol;
		}

		/*!
		*
		**/
		SymbolStyle(const SymbolStyle &other)
		{
			*this = other;
		}

		/*!
		*
		**/
		const SymbolStyle &operator=(const SymbolStyle &other)
		{
			if(this == &other)
			{
				return *this;
			}

			// parent
			m_styleType = other.m_styleType;

			//
			m_color = other.m_color;
			m_backgroundcolor = other.m_backgroundcolor;

			m_gradient = other.m_gradient;
			m_outlinewidth = other.m_outlinewidth;
			m_outlinecolor = other.m_outlinecolor;
			m_scale = other.m_scale;
			m_rotation = other.m_rotation;
			m_gap = other.m_gap;
			m_radius = other.m_radius;

			return *this;
		}
	};
}

#endif