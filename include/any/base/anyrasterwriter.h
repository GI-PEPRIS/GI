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
#ifndef __ANYBASE_IMAGE_RASTER_WRITER_H__
#define __ANYBASE_IMAGE_RASTER_WRITER_H__

// Refer to EXPORT & IMPORT definitions
#include "anybase.h"
#include "anystl.h"
#include "anyfilebasic.h"
#include "anydirbasic.h"
#include "anygeom.h"

//
namespace AnyBase
{
	/**
	*
	*/
	class ANYBASE_CLASS CAnyRasterWriter
	{
		/**
		*
		*/
		struct ResInfo
		{
			// Name in order to write XML file and XML file only record those resources has name
			char m_name[64];
			// String idx for binart search inner side
			char m_idx[128];
			// Resource source
			char m_fName[512];
			// Image data offset in UePicture file
			int m_offset;
			// Resouces size
			int m_size;
			// Image data
			unsigned char *m_data;

			/**
			*
			*/
			ResInfo() : m_offset(-1), m_size(0), m_data(0)
			{
				m_name[0] = 0;
				m_idx[0] = 0;
				m_fName[0] = 0;
			}

			/**
			*
			*/
			int GetImageType() const
			{
				char tmp[200] = {0, };
				::strcpy(tmp, m_fName);
				::strlwr(tmp);
				if(::strstr(tmp, ".bmp"))	
				{
					return 0;
				}

				if(::strstr(tmp, ".png"))	
				{
					return 1;
				}

				return 0;
			}
		};

		//
		typedef std::vector<ResInfo> ResVector;
		typedef ResVector::iterator res_itr;
		typedef ResVector::const_iterator res_citr;

		// Header + date + time + number + string offset + string size
		const static int IMAGEOFFSET = 8 + 4 + 4 + 4 + 4 + 4;
		const static int RECORDWITHSTR = 4 + 4 + 4 + 4;
		const static int RECORDWITHOUTSTR = 4 + 4 + 4;
	public:
		//
		//
		//
		/**
		*
		*/
		CAnyRasterWriter();
		~CAnyRasterWriter();

	public:
		//
		//
		//
		/**
		*
		*/
		void MakeUePictures(const ResVector &images, const anystring &fileName, bool isHasStrPart);

		/**
		*
		*/
		void ExtractUePictures(ResVector &images, const anystring &fileName, const anystring &path);

	private:
		//
		const CAnyFileBasic &m_fileBasic;
		const CAnyDirBasic &m_pathBasic;
	};
}
#endif
