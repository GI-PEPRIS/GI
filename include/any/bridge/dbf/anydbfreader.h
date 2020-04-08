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
#ifndef __ANYBRIDGE_DBFREADER_H__
#define __ANYBRIDGE_DBFREADER_H__

// Refer to EXPORT & IMPORT 
#include "anybridge.h"

// Refer to portable type definitions
#include "any/base/anyport.h"

// refer to dir and file basic
#include "any/base/anydirbasic.h"
#include "any/base/anyfilebasic.h"
using namespace AnyBase;

// Refer to DBF basic definitions
#include "anydbfbasic.h"

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  //  needs to have dll-interface
#pragma warning( disable: 4996 )  //  needs to have dll-interface

// Declare namespace
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyDbfReader
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyDbfReader(const anystring &file, bool isCached = true);

		/*!
		*
		**/
		~CAnyDbfReader();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool Open();

		/*!
		*
		**/
		void LoadFileCache();
		char* GetFileCache();
		void SetFileCache(char* filecache);
		void ReleaseFileCache();

		/*!
		*
		**/
		void Close();

		//
		//
		//
		/*!
		*
		**/
		int GetRecordCount();

		/*!
		*
		**/
		int GetFieldCount();

		/*!
		*
		**/
		short GetFieldInfo(int fldIdx, char *fldName, int &width, int &decimals);

		/*!
		*
		**/
		void *GetField(int recIdx, int fldIdx, short fldType);

		/*!
		*
		**/
		bool IsNullField(int recIdx, int fldIdx);

		/*!
		*
		**/
		void SearchRecord(const string &fldName, const string &querystr, std::vector<int> &resultRecIdxs);

		/*!
		*
		**/
		const anystring &GetFileName();
	private:
		// File name
		anystring m_fileName;

		// File handle
		void *m_fileHandle;

		// File description
		DbfDesc m_description;

		// Whether geometries are cached
		bool m_isCache;

		// Path basic functions
		const CAnyDirBasic &m_pathBasic;

		// File basic functions
		const CAnyFileBasic &m_fileBasic;

		// Memory buf for getting data value
		int m_dataSize;
		unsigned char *m_dataBuf;

		// For numerica data conversion
		double m_numericValue;

		char *m_filedatacache;//load whole file into cache
	};
}
#endif
