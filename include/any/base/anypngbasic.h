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
#ifndef __ANYBASE_PNG_BASIC_H__
#define __ANYBASE_PNG_BASIC_H__

// Refer to EXPORT & IMPORT definitions
#include "anybase.h"
#include "anyrasterbasic.h"

// Refer to PNG headers
#include "png/png.h"

// Refer to CHAR header files
#include "anyport.h"

// Refer to picture basic definitions
#include "anyrasterbasic.h"

// Refer to CGeoRect
#include "anygeom.h"

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4996 )  // Deprecated function calling

// UeBase namespace
namespace AnyBase
{
	// Forward classes
	class CAnyFileBasic;
	class CAnyDirBasic;

	/**
	* Utility functions encapsulated for PNG file.
	*/
	class ANYBASE_CLASS CAnyPngBasic : public CAnyRasterBasic
	{
		// Disallow implicitly usage ...
		CAnyPngBasic(const CAnyPngBasic &other);
		const CAnyPngBasic &operator=(const CAnyPngBasic &other);

	public:
		//
		// Constructors & deconstructor
		//
		/**
		*
		*/
		CAnyPngBasic();

		/**
		*
		*/
		~CAnyPngBasic();

		//
		// Methods as a PNG file reader
		//
		/**
		*
		*/
		bool Load(const anystring &fileName, bool isFlip = false);
		bool Save(const anystring &fileName); 
		bool GetPart(unsigned char *dest, const CGeoRect<int> &dev_rect, int width, int height, const CGeoRect<int> &png_rect);

		//
		//
		//
		/**
		*
		*/
		bool IsPNG(const anystring &file) const;
		bool IsPNG(char *buf) const;
		bool IsGood() const;
		int GetWidth() const;
		int GetHeight() const;
		unsigned char *GetBGRA() const;

	protected:
		//
		// returns true if the specified file is a png file
		//
		/**
		* converts the png bytes to BGRA
		*/
		bool ExtractData(png_structp& PngPtr, png_infop& InfoPtr);

		/**
		* gets the data from an 8-bit rgb image
		*/
		unsigned char* ToRGB8(png_structp& PngPtr, png_infop& InfoPtr) const;

		/**
		* gets the data from an 8-bit rgb image with alpha values
		*/
		unsigned char* ToRGBA8(png_structp& PngPtr, png_infop& InfoPtr) const;

		/**
		* gets the data from an 8-bit monochrome image
		*/
		unsigned char* ToGrey8(png_structp& PngPtr, png_infop& InfoPtr) const;

		/**
		* gets the data from an 8-bit monochrome image with alpha values
		*/
		unsigned char* ToGreyA8(png_structp& PngPtr, png_infop& InfoPtr) const;

		/**
		*
		*/
		bool DoFlip();

	public:
		static int g_io_offset;
		static int g_io_max;
		static inline void PNGAPI png_default_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
		static int GetStride(int width, int bitsPerPixel);

	private:
		//
		bool m_good;
		int m_width;
		int m_height;
		unsigned char *m_bgra;

		//
		const CAnyFileBasic &m_fileBasic;
		const CAnyDirBasic &m_pathBasic;
	};
}
#endif