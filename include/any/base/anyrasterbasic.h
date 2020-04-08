/*
 * The UrbanEye PND solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy one kind
 * of mobile or portable devices with competitive qualities being a leading one.
 *
 * Copyright (C) 2008 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Graduate School
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYBASE_IMAGE_RASTER_BASIC_H__
#define __ANYBASE_IMAGE_RASTER_BASIC_H__

// Refer to EXPORT & IMPORT definitions
#include "anybase.h"

// Refer to CGeoRect<> definition
#include "anygeom.h"

// UeBase namespace
namespace AnyBase
{
	/**
	* Encapsulate those general and useful functions for the general purpose of picture operation. This class is taken as 
	* a singleton since it is mainly be composited by those useful functions.
	*
	*/
	class ANYBASE_CLASS CAnyRasterBasic
	{
		// Disallow automatically and implicitly creation etc...
		CAnyRasterBasic(const CAnyRasterBasic &other);
		void operator=(const CAnyRasterBasic &other);

	public:
		/**
		*
		**/
		enum PictureType
		{
			PT_Unknown = -1,
			PT_BMP,
			PT_PNG,
			PT_Max
		};

		/**
		* Color schema, namely how many bytes or bits to represent different color channels
		*
		* Note:
		* Refer to AGG opensource to get more color expressions
		**/
		enum ColorType
		{
			CT_Unknown = 0,
			CT_RGB,
			CT_RGBA,
			CT_GRAY8,
			CT_GRAYA8,
			CT_RGB555,
			CT_RGBA555,
			CT_RGB565,
			CT_RGBA565,
			CT_RGBPAL,
			CT_BGR
		};

		/**
		* Different rendering way or styles.
		**/
		enum RenderingStyle
		{
			RS_Opaque = 0,
			RS_Transparent,
			RS_Semitrans,
			RS_Gray
		};

		/**
		* How to render one picture
		**/
		struct RenderingSpec
		{
			int m_resIdx;
			int m_cx;
			int m_cy;

			unsigned char m_style;
			unsigned int m_maskClr;

			/**
			*
			**/
			RenderingSpec() : m_resIdx(0), m_cx(0), m_cy(0), m_style(0), m_maskClr(0)
			{
			}

			/**
			*
			**/
			const RenderingSpec &operator = (const RenderingSpec &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_resIdx = other.m_resIdx;
				m_cx = other.m_cx;
				m_cy = other.m_cy;
				m_style = other.m_style;
				m_maskClr = other.m_maskClr;

				return *this;
			}
		};

		/**
		* Picture description to describle as more picture formats as possible.
		**/
		struct PictureBasic
		{
			// picture position
			CGeoRect<double> m_position;

			// Picture size
			int m_width;
			int m_height;

			// Picture basic attributes
			int m_bpp;	// Bit per pixel
			unsigned char m_clrType;
			unsigned char m_formatType;

			// BMP structure
			void *m_bmp;	// Here should be HBITMAP
			void *m_bmpInfo;	// Here should be BITMAPINFO
			unsigned char *m_bmpBase;	// BMP content memory

			// For PNG structure or new storing mechansim, for example, RGB555 etc
			// Namely, even if we directly load one bitmap, we can re-layout memory in m_rows for new
			// store mechansim
			unsigned char **m_rows;

			/**
			* Initialization
			*
			* Note:
			* Since it refer to memmediator.h, it carry the re-definition of CT_Unknown.
			**/
			PictureBasic() : m_width(0), m_height(0), m_bpp(0), m_formatType(PT_Unknown), m_clrType(CT_Unknown), 
				m_bmp(0), m_bmpInfo(0), m_bmpBase(0), m_rows(0)
			{
			}

			/**
			*
			**/
			bool IsValid()
			{
				return m_width > 0 && m_height > 0;
			}

			/**
			*
			**/
			const PictureBasic &operator =(const PictureBasic &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_position = other.m_position;
				m_width = other.m_width;
				m_height = other.m_height;
				m_bpp = other.m_bpp;
				m_clrType = other.m_clrType;
				m_formatType = other.m_formatType;
				m_bmp = other.m_bmp;
				m_bmpInfo = other.m_bmpInfo;
				m_bmpBase = other.m_bmpBase;
				m_rows = other.m_rows;

				return *this;
			}

			/**
			* Consider there maybe many objects sharing the same meory for one picture description, so it no need 
			* to release that memory unitl the loader know when and where is suitable to free those memories
			*/
			void Reset()
			{
				m_bmpBase = 0;
				m_bmpInfo = 0;
				m_bmp = 0;
				m_rows = 0;

				m_width = 0;
				m_height = 0;
				m_bpp = 0;
				m_clrType = -1;
				m_formatType = PT_Unknown;
			}
		};

	protected:
		// 
		// Constructors & deconstructor
		//
		/**
		*
		*/
		CAnyRasterBasic() : m_picFile(_T("")), m_idx(-1), m_picBuf(0)
		{
		}
		virtual ~CAnyRasterBasic()
		{
		}

	public:
		//
		// Singelton
		//
		/**
		*
		*/
		static const CAnyRasterBasic &Get();

		//
		//
		//
		//
		// Common utility functions for memory conversion in order to suppoet different storing mechansim
		// for one picture
		//
		/**
		*
		**/
		unsigned short rgb24_2_rgb555(int r, int g, int b) const;
		unsigned int rgb555_2_rgb24(int rgb555) const;
		void rgb555_2_bgr24(unsigned char *p, int rgb555) const;
		void blend_pix_555(unsigned short *p, unsigned cr, unsigned cg, unsigned cb, unsigned alpha) const;
		void blend_pix_bgr24(unsigned char *p, unsigned cr, unsigned cg, unsigned cb, unsigned alpha) const;
		void copy_image_info_rgb_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_rgb_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_bgr_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_bgr_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_rgba_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_rgba_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_rgb_pal_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_rgb_pal_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, void *maskClr = 0) const;
		void copy_image_info_rgb_pal_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;
		void copy_image_info_rgb_pal_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;
		void copy_image_info_rgb555_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_rgb555_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src) const;
		void copy_image_info_rgb555_2_555(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;
		void copy_image_info_rgb555_2_bgr24(unsigned char *bits, unsigned char **rows, const CGeoRect<int> &dest, const PictureBasic &onePic, const CGeoRect<int> &src, unsigned short maskClr) const;

	public:
		void Reset()
		{
			m_idx = 0;
			m_data.Reset();
			m_picFile = _T("");
			m_picBuf = 0;
		}
		static bool LoadPicture(char *buffer, int size, PictureBasic *onePicture);
		static bool ToBMP(char *_io_buffer, int _io_max, PictureBasic *_info);
		static bool ToPNG(char *_io_buffer, int _io_max, PictureBasic *_info);

		//
		long m_idx;
		// One plain file to get PNG/BMP format image
		anystring m_picFile;
		// A memory block storing PNG/BMP image
		// Note: The life time of below memory should be decided by outside since it is directly assigned by outside
		char *m_picBuf;
		PictureBasic m_data;
	};
}
#endif