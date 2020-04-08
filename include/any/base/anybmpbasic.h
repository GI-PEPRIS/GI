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
#ifndef __ANYBASE_BMP_BASIC_H__
#define __ANYBASE_BMP_BASIC_H__

// Refer to EXPORT & IMPORT definitions
#include "anybase.h"

// Refer to stdio.h etc stand C headers
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
	//
    enum org_e
    {
        org_mono8   = 8,
        org_color16 = 16,
        org_color24 = 24,
        org_color32 = 32,
        org_color48 = 48,
        org_color64 = 64
    };

	/*!
	* This class is mainly responsible for BMP structure creation, data analyzation etc.
	*
	*/
    class ANYBASE_CLASS CAnyBmpBasic : public CAnyRasterBasic
    {
		// Disallow implicitly creation etc
        CAnyBmpBasic(const CAnyBmpBasic&);
        const CAnyBmpBasic& operator = (const CAnyBmpBasic&);

    public:
		//
		// Constructors & deconstructor
		//
		/*!
		*
		*/
        CAnyBmpBasic();
        ~CAnyBmpBasic();

    public:
		//
		// Methods for BMP/DIB creation & deletion
		//
		/*!
		*
		*/
        void Destroy();
        void Create(unsigned width, unsigned height, org_e org, unsigned clear_val = 256);
        void *CreateDIBSection(void *h_dc, unsigned width, unsigned height, org_e org, unsigned clear_val=256);
        void Clear(unsigned clear_val=256);
        void AttachToBmp(void *bmp);
        void* GetBitmapInfo() //pointer to the beginging of BMP
		{ 
			return m_bmp; 
		}
        bool LoadFromBmp(FILE *fd);
        bool SaveAsBmp(FILE *fd) const;
        bool LoadFromBmp(const anystring &fileName);
        bool SaveAsBmp(const anystring &fileName) const;

		//
		//
		//
		/*!
		*
		*/
        void Draw(void *h_dc, const CGeoRect<double> &device_rect, const CGeoRect<double> &bmp_rect) const;
        void Draw(void *h_dc, int x, int y, double scale=1.0) const;
		void GetPart(unsigned char *dest, unsigned width, unsigned height, const CGeoRect<double> &device_rect, const CGeoRect<double> &bmp_rect) const;
        void Blend(void *h_dc, const CGeoRect<double> &device_rect, const CGeoRect<double> &bmp_rect) const;
        void Blend(void *h_dc, int x, int y, double scale=1.0) const;

		//
		// Access methods
		//
		/*!
		*
		*/
        unsigned char* GetBuf();
        unsigned GetWidth() const;
        unsigned GetHeight() const;
        int GetStride() const;
		unsigned GetBpp() const { return m_bpp; }
		int GetImgSize()
		{
			return m_img_size;
		}

		//
        // Auxiliary static functions
		//
		/*!
		*
		*/
        static unsigned GetFullSize(void *bmp);
        static unsigned CalcHeaderSize(void *bmp);
        static unsigned GetPaletteSize(unsigned clr_used, unsigned bits_per_pixel);
        static unsigned CalcPaletteSize(void *bmp);
        static unsigned char *CalcImgPtr(void *bmp);
        static void *CreateBitmapInfo(unsigned width, unsigned height, unsigned bits_per_pixel);
        static void CreateGrayPalette(void *bmp);
        static unsigned GetStride(unsigned width, unsigned bits_per_pixel);        

    private:
		//
		//
		//
		/*!
		*
		*/
        void CreateFromBmp(void *bmp);
        void *CreateDIBFromArgs(void *h_dc, unsigned width, unsigned height, unsigned bits_per_pixel);

    private:
        void *m_bmp;	//BITMAPINFO
        unsigned char *m_buf;
        unsigned m_bpp;
        bool m_is_internal;
        unsigned m_full_size;
		unsigned m_img_size;
    };
}


#endif
