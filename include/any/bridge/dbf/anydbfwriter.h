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
#ifndef __ANYBRIDGE_DBFWRITER_H__
#define __ANYBRIDGE_DBFWRITER_H__

// Refer to EXPORT & IMPORT
#include "anybridge.h"

// Refer to SHP basic definition
#include "anydbfbasic.h"

// Refer to portable string definitions
#include "any/base/anyport.h"
#include "any/base/anydirbasic.h"
#include "any/base/anyfilebasic.h"
using namespace AnyBase;

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  //  needs to have dll-interface
#pragma warning( disable: 4996 )  //  needs to have dll-interface

// Declare namespace
namespace AnyBridge
{
	/**
	*
	**/
	class ANYBRIDGE_CLASS CAnyDbfWriter
	{
	public:
		//
		//
		//
		/**
		*
		**/
		CAnyDbfWriter(const anystring &file);

		/**
		*
		**/
		~CAnyDbfWriter();

		//
		//
		//
		/**
		*
		**/
		bool Open();

		/**
		*
		**/
		void Close();

		//
		//
		//
		/**
		*
		**/
		int CAnyDbfWriter::AddFieldInfo(const char *fldName, short fldType, int width, int decimals);

		/**
		*
		**/
		bool WriteField(int recIdx, int fldIdx, int fldType, void *data);

	private:
		//
		//
		//
		/**
		*
		**/
		void WriteHeader();

		/**
		*
		**/
		bool FlushRecord();

	private:
		// File name
		anystring m_fileName;

		// File handle
		void *m_dataHandle;

		// DBF file information
		DbfDesc m_description;

		// Path basic functions
		const CAnyDirBasic &m_pathBasic;

		// File basic functions
		const CAnyFileBasic &m_fileBasic;
	};
}
#endif