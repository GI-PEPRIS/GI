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
#ifndef __ANYBRIDGE_SHPWRITER_H__
#define __ANYBRIDGE_SHPWRITER_H__

// Refer to EXPORT & IMPORT
#include "..\anybridge.h"

// Refer to SHP basic definitions
#include "anyshpbasic.h"

// Refer to portable type definition like anystring
// refer to anybase
#include "any/base/anyport.h"
#include "any/base/anyfilebasic.h"
#include "any/base/anydirbasic.h"
#include "any/base/anyplatinfo.h"
using namespace AnyBase;

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  //  needs to have dll-interface

// Declare namespace
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyShpWriter
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyShpWriter(short type, const anystring &file);

		/*!
		*
		**/
		~CAnyShpWriter();

	public:
		//
		// I/O functions
		//
		/*!
		*
		**/
		bool Open();

		/*!
		*
		**/
		void Close();

		//
		//
		//
		/*!
		* Encoding one SHP geometry
		**/
		ShpGeometry *CreateGeometry(int type, int idx, int vertices, double *xCoords, double *yCoords, 
			double *zCoords = 0, double *mCoords = 0, int parts = 1, int *partOffsets = 0, int *partTypes = 0);

		/*!
		*
		**/
		bool WriteGeometry(ShpGeometry *geometry, bool isNew = true);

	private:
		//
		//
		//
		/*!
		*
		**/
		void ComputeExtents(ShpGeometry *geometry);

		/*!
		*
		**/
		void SetBounds(char *buf, const ShpGeometry *geometry);

		/*!
		*
		**/
		void WritePolys(const ShpGeometry *geometry, char *buf, int &recordSize);

		/*!
		*
		**/
		void WritePoints(const ShpGeometry *geometry, char *buf, int &recordSize);

		/*!
		*
		**/
		void WritePoint(const ShpGeometry *geometry, char *buf, int &recordSize);

		/*!
		*
		**/
		void WriteHeader();

	public:
		// File name
		anystring m_fileName;

		// SHP description for header information
		ShpDesc m_description;

		// Little or Big endian
		bool m_isLittle;

		// Data handle
		void *m_dataHandle;

		// Index handle
		void *m_indexHandle;

		// Path basic functions
		const CAnyDirBasic &m_pathBasic;

		// File basic functions
		const CAnyFileBasic &m_fileBasic;

		// Platform-depedent utilities
		const CAnyPlatInfo &m_platInfo;
	};
}

#endif