/*!
 * The AnyThread of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * thread definitions & operations required to satisfy KINDS OF THREAD CALLING of other packages.
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
#ifndef __ANYTHREAD_DEF_H__
#define __ANYTHREAD_DEF_H__

// Other DLL or EXE need define ANYTHREAD_IMPORTS macro in order to 
// correctly and automatcially be linked to those symbols specified here
#ifdef ANYTHREAD_EXPORTS
	#define ANYTHREAD_CLASS __declspec(dllexport)
	#define ANYTHREAD_API extern "C" __declspec(dllexport)
#else
	#define ANYTHREAD_CLASS __declspec(dllimport)
	#define ANYTHREAD_API extern "C" __declspec(dllimport)

	// Resolving symbols
    #ifdef _DEBUG
	    #pragma comment(lib, "gi_threadd.lib")
	    #pragma message("Automatically linking with gi_threadd.dll")
    #else
	    #pragma comment(lib, "gi_thread.lib")
	    #pragma message("Automatically linking with gi_thread.dll")
    #endif
#endif 

// Erase compiling warning condition
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

#endif