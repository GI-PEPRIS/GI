#ifndef __ANYBASE_WINTIMER_H__
#define __ANYBASE_WINTIMER_H__

// Refer to its parent
#include "anytimer.h"

// Refer to Micro-specified data types
#ifndef _WINDOWS_
#include "windows.h"
#endif

// Refer STL basic definitions
#include "anystl.h"

/**
*
**/
namespace AnyBase
{
    /**
    * Note:
    *  Implementation is part of OGRE, and refactor its content according to own OO concepts
    **/
    class CAnyWinTimer : public CAnyTimer
    {
        //
        const static int FREQUENCY_RESAMPLE_RATE = 200;

    public:
        //
        //
        //
        /**
        *
        **/
        CAnyWinTimer();

        /**
        *
        **/
        explicit CAnyWinTimer(HANDLE curThread);

        /**
        *
        **/
        ~CAnyWinTimer();

    public:
        //
        //
        //
		/**
        * Resets timer and define the starting point
        */
		virtual void Reset();

        //
        // Statistic functions since Reset time
        //
		/** 
        * Returns milliseconds since initialisation or last reset 
        */
		virtual unsigned long GetMilliseconds();

		/** 
        * Returns microseconds since initialisation or last reset 
        */
		virtual unsigned long GetMicroseconds();

		/** 
        * Returns milliseconds since initialisation or last reset, only CPU time measured 
        */	
		virtual unsigned long GetMillisecondsCPU();

		/** 
        * Returns microseconds since initialisation or last reset, only CPU time measured 
        */	
		virtual unsigned long GetMicrosecondsCPU();

    private:
        //
		clock_t m_zeroClock;
        // 
        DWORD m_startTick;
        //
		 LONGLONG m_lastTime;
        //
        LARGE_INTEGER m_startTime;
        //
        LARGE_INTEGER m_frequency;
        //
        DWORD m_procMask;
        //
        DWORD m_sysMask;
        // Host object which is subject to get time info
        HANDLE m_thread;
        //
        DWORD m_queryCount;
    };
}
#endif