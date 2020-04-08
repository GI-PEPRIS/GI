/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
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
#ifndef __ANYBRIDGE_EXCHANGE_UTIL_H__
#define __ANYBRIDGE_EXCHANGE_UTIL_H__

// refer to EXPORT and IMPORT
#include "anybridge.h"

#include "any/base/anystl.h"
#include "any/base/anyfilebasic.h"
#include "any/base/anydirbasic.h"
#include "any/base/anystringbasic.h"
using namespace AnyBase;

namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CExchangeUtil
	{									
	public:
		//
		//
		//
		/*!
		*
		**/
		CExchangeUtil();

		/*!
		*
		**/
		~CExchangeUtil();
	public:
		
		/*!
		*
		**/
		static float ReadSunFSHORT(unsigned char* BytesIn, int IP, int &LenBytes);
		static float ReadSunFSINGL(unsigned char* BytesIn, int IP, int &LenBytes);
		static float* ReadSunFSING1(unsigned char* BytesIn, int IP, int &LenBytes);
		static float* ReadSunFSING2(unsigned char* BytesIn, int IP, int &LenBytes);
		static float ReadSunISINGL(unsigned char* BytesIn, int IP, int &LenBytes);
		static float ReadSunVSINGL(unsigned char* BytesIn, int IP, int &LenBytes);
		static double ReadSunFDOUBL(unsigned char* BytesIn, int IP, int &LenBytes);
		static double* ReadSunFDOUB1(unsigned char* BytesIn, int IP, int &LenBytes);
		static double* ReadSunFDOUB2(unsigned char* BytesIn, int IP, int &LenBytes);
		static float* ReadSunCSINGL(unsigned char* BytesIn, int IP, int &LenBytes);
		static double* ReadSunCDOUB2(unsigned char* BytesIn, int IP, int &LenBytes);
		static int ReadSunSSHORT(unsigned char* BytesIn, int IP, int &LenBytes);
		static int ReadSunSNORM(unsigned char* BytesIn, int IP, int &LenBytes);
		static int ReadSunSLONG(unsigned char* BytesIn, int IP, int &LenBytes);
		static int ReadSunUSHORT(unsigned char* BytesIn, int IP, int &LenBytes);
		static int ReadSunUNORM(unsigned char* BytesIn, int IP, int &LenBytes);
		static long ReadSunULONG(unsigned char* BytesIn, int IP, int &LenBytes);
		static int ReadSunUVARI(unsigned char* BytesIn, int IP, int &LenBytes);
		static string ReadSunIDENT(unsigned char* BytesIn, int IP, int &LenBytes);
		static string ReadSunASCII(unsigned char* BytesIn, int IP, int &LenBytes);
		static string ReadSunDTIME(unsigned char* BytesIn, int IP, int &LenBytes);
		static string ReadSunOBNAME(unsigned char* BytesIn, int IP, int &LenBytes, int &OriginRef, int &CopyNo);
		static string ReadSunOBJREF(unsigned char* BytesIn, int IP, int &LenBytes, int &OriginRef, int &CopyNo);
		static string ReadSunATTREF(unsigned char* BytesIn, int IP, int &LenBytes, int &OriginRef, int &CopyNo);
		static int ReadSunSTATUS(unsigned char* BytesIn, int IP, int &LenBytes);
		static string ReadSunUNITS(unsigned char* BytesIn, int IP, int &LenBytes);
		static int BytesOfDlisCode(int RepCode);
		static double MeterUnitFactor(string units);
		static double msTimeUnitFactor(string units);
		static double STimeUnitFactor(string units);
		static unsigned char* GetSunSingleBytes(float Value);
		static unsigned char* GetSunDoubleBytes(double DValue);
		static unsigned char* GetSunInt16Bytes(short Vint16);
		static unsigned char* GetSunInt32Bytes(int Vint32);
		static unsigned char* GetSunUshortBytes(int Vint32);
		static unsigned char* GetSunUint16Bytes(int Vint32);
		static unsigned char* GetSunUint32Bytes(long Vint64);
		static unsigned char* GetSunUVARIBytes(int Vint32);
		static unsigned char* GetSunIdentBytes(string IdentStr);
		static unsigned char* GetSunAsciiBytes(string AsciiStr);
		static unsigned char* GetSunDateBytes();                                                                                                      
		static unsigned char* GetDlisObjectNameBytes(string ObjNameStr, int NoOrigin, int NoCopy);
		// For Version 2
		static int DLIS_RNORM(unsigned char* buf, double &numerator, double &denominator);
		static int DLIS_RLONG(unsigned char* buf, double &numerator, double &denominator);
		static int DLIS_ISNORM(unsigned char* buf, int &nbyte);
		static int DLIS_ISLONG(unsigned char* buf, int &nbyte);
		static int DLIS_IUNORM(unsigned char* buf, int &nbyte);
		static unsigned int DLIS_IULONG(unsigned char* buf, int &nbyte);
		static int DLIS_IRNORM(unsigned char* buf, double &numerator, double &denominator);
		static int DLIS_IRLONG(unsigned char* buf, double &numerator, double &denominator);
		static int DLIS_LOGICL(unsigned char* buf, int nbyte);
		static int DLIS_BINARY(unsigned char* buf, int &nbyte);
		static int DLIS_FRATIO(unsigned char* buf, double &numerator, double &denominator);
		static int DLIS_DRATIO(unsigned char* buf, double &numerator, double &denominator);
	};
}

#endif
