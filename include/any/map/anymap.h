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
#ifndef __ANYMAP_DEF_H__
#define __ANYMAP_DEF_H__

// Other DLL or EXE need define ANYMAP_IMPORT macro in order to 
// correctly and automatcially be linked to those symbols specified here
#ifdef ANYMAP_EXPORTS
	#define ANYMAP_CLASS __declspec(dllexport)
	#define ANYMAP_API extern "C" __declspec(dllexport)
#else
	#define ANYMAP_CLASS __declspec(dllimport)
	#define ANYMAP_API extern "C" __declspec(dllimport)

	// Resolving symbols
    #ifdef _DEBUG
	    #pragma comment(lib, "gi_mapd.lib")
	    #pragma message("Automatically linking with gi_mapd.dll")
    #else
	    #pragma comment(lib, "gi_map.lib")
	    #pragma message("Automatically linking with gi_map.dll")
    #endif
#endif 

// AGG's switches
#define AGG_BGR24
#define SYSTEM_BPP 24

// Erase compiling warning condition
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4996 )  // deprecated function
#endif