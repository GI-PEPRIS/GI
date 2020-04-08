#ifndef __ANYTHREAD_DEF_H__
#define __ANYTHREAD_DEF_H__

// Other DLL or EXE need define NAVBASE_IMPORT macro in order to 
// correctly and automatcially be linked to those symbols specified here
#ifdef ANYTHREAD_EXPORTS
	#define ANYTHREAD_CLASS __declspec(dllexport)
	#define ANYTHREAD_API extern "C" __declspec(dllexport)
#else
	#define ANYTHREAD_CLASS __declspec(dllimport)
	#define ANYTHREAD_API extern "C" __declspec(dllimport)

	// Resolving symbols
    #ifdef _DEBUG
	    #pragma comment(lib, "anythreadd.lib")
	    #pragma message("Automatically linking with anythreadd.dll")
    #else
	    #pragma comment(lib, "anythread.lib")
	    #pragma message("Automatically linking with anythread.dll")
    #endif
#endif 

#endif