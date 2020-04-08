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
#ifndef __ANYBASE_IMAGE_RASTER_LOADER_H__
#define __ANYBASE_IMAGE_RASTER_LOADER_H__

// Refer to EXPORT & IMPORT definitions
#include "anybase.h"
#include "anyrasterbasic.h"
#include "anyport.h"

// Erase compile warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  // Deprecated function calling

// UeBase namespace
namespace AnyBase
{
	// Forward classes
	class CAnyFileBasic;
	class CAnyDirBasic;

	/**
	* Using one structure as more compatible as possible to describe as more picture formats as possible, 
	* for example, PNG/BMP etc. And With efficiently and directly storing these structures and as basic I/O analyzing 
	* different picture formats.
	*
	* File corresponding to this loader is mainly divided into two parts: STRING and PICTURE. STRING part would be
	* ordered in order to support binary predicate when finding one picture except for directly using one idx. 
	* For PICTURE part, different memory units can be taken as some pictures following the same picture specification 
	* or format. For example, one picture memory unit can be composited by hundreds of PNG data and we can use its 
	* CX and CY to get one of those PNG pictures, CAnyRasterBasic is responsible for analyze that memory unit and render 
	* it on specified frame buffer.
	*
	*/
	class ANYBASE_CLASS CAnyRasterLoader
	{
	public:
		/**
		* Different loader type corresponding to those pictures by specified categories.
		* Namely, those string or picture for POI rendering, for GUIDANCE rendering etc.
		*/
		enum LoaderType
		{
			LT_Unknown	= -1,
			LT_Log_Litho,
			LT_Max
		};

	protected:

		// Relatives
		friend class CAnyRasterBasic;

		// Alow how many CAnyRasterBasic objects are referencing to the same memory address
		const static int MAXREFCOUNT = 10;

		/**
		* Loader or storing specification.
		*
		* Different picture part would be stored as below specification.
		*/
		struct LoaderDef
		{
			// File positions for string and picture parts
			long m_strOffset;
			long m_picOffset;

			// Picture or image description
			short m_imgType;
			long m_picSize;
			CAnyRasterBasic::PictureBasic m_data;

			// Simple memory cache mechansim
			short m_refCount;
			LoaderDef *m_refObjects[MAXREFCOUNT];

			/**
			*
			**/
			LoaderDef() : m_strOffset(0), m_picOffset(0), m_imgType(0), m_picSize(0), m_refCount(0)
			{
				int i = 0;
				for(; i < MAXREFCOUNT; i++)
				{
					m_refObjects[i] = 0;
				}
			}
		};

		// Disallow the complex usage of this class
		CAnyRasterLoader(const CAnyRasterLoader &other);
		void operator=(const CAnyRasterLoader &other);

		//
		// Constructors & deconstructor
		//
		// As far, this class mainly be used as singletions: POI/Guidance/GUI/Default etc loaders
		/**
		*
		**/
		CAnyRasterLoader();
		virtual ~CAnyRasterLoader();

	public:
		//
		// Methods for open and close one kind of picture loader
		//
		/**
		*
		**/
		bool Open(const anystring &oneFile, bool isLazy = true);
		void Close();
		bool IsReady();

		//
		// Methods for string part
		//
		/**
		*
		**/
		char *GetString(int idx);
		int FindIdx(char *str);

		//
		// Methods for picture part
		//
		/**
		*
		**/
		int GetPictureCount();
		void AddPicture(LoaderDef *onePicture);
		LoaderDef *GetPicutre(int idx);

		int GetPictureSize(int idx);
		int GetPictureType(int idx);
		bool LoadPicture(int idx, LoaderDef *onePicture);
		void FreePicture(int idx, LoaderDef *onePicture, bool isForce = false);

		//
		// Methods for simple cache operations
		//
		/**
		*
		**/
		void IsCached(bool isCached);
		bool IsCached();
		void RemoveCache(int maxCount);

	private:
		//
		//
		//
		/**
		*
		**/
		void ReleasePicture(LoaderDef &onePic);
		bool Open();

	private:
		// Load identifications
		long m_saveDate;	// 20060313 means 2006/03/13
		long m_saveTime;	// 112244 means 11: 33 : 44

		// Image part
		int m_picNum;
		LoaderDef *m_pictures;

		// String part
		long m_strOffset;
		long m_strSize;
		char *m_strings;

		// Loader itself
		anystring m_loaderFile;
		void *m_loaderHandle;

		const CAnyFileBasic &m_fileBasic;
		const CAnyDirBasic &m_pathBasic;

		// Simple memory cache mechansim since one picture maybe frequently used
		int m_loadedCount;
		bool m_isCached;
	};
}

#endif