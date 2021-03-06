/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYPORTFOLIO_DEF_H__
#define __ANYPORTFOLIO_DEF_H__

// Other DLL or EXE need define ANYBASE_IMPORT macro in order to 
// correctly and automatcially be linked to those symbols specified here
#ifdef ANYPORTFOLIO_EXPORTS
	#define ANYPORTFOLIO_CLASS __declspec(dllexport)
	#define ANYPORTFOLIO_API extern "C" __declspec(dllexport)
#else
	#define ANYPORTFOLIO_CLASS __declspec(dllimport)
	#define ANYPORTFOLIO_API extern "C" __declspec(dllimport)

	// Resolving symbols
    #ifdef _DEBUG
	    #pragma comment(lib, "gi_portfoliod.lib")
	    #pragma message("Automatically linking with gi_portfoliod.dll")
    #else
	    #pragma comment(lib, "gi_portfolio.lib")
	    #pragma message("Automatically linking with gi_portfolio.dll")
    #endif
#endif 

// Erase compiling warning condition
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4996 )  

#endif