#ifndef __ANYBASE_TIMER_H__
#define __ANYBASE_TIMER_H__

/**
*
**/
namespace AnyBase
{
	/*!
	*
	**/
    class CAnyTimer
    {
    public:
        //
        //
        //
		/*!
		*
		**/
		CAnyTimer()
		{
		}

		/*!
		*
		**/
		virtual ~CAnyTimer()
		{
		}

    public:
        //
        //
        //
		/**
        * Resets timer and define the starting point
        */
		virtual void Reset() = 0;

        //
        // Statistic functions since Reset time
        //
		/** 
        * Returns milliseconds since initialisation or last reset 
        */
		virtual unsigned long GetMilliseconds() = 0;

		/** 
        * Returns microseconds since initialisation or last reset 
        */
		virtual unsigned long GetMicroseconds() = 0;

		/** 
        * Returns milliseconds since initialisation or last reset, only CPU time measured 
        */	
		virtual unsigned long GetMillisecondsCPU() = 0;

		/** 
        * Returns microseconds since initialisation or last reset, only CPU time measured 
        */	
		virtual unsigned long GetMicrosecondsCPU() = 0;
    };
}

#endif