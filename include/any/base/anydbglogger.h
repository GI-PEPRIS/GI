/*!
 * The AnyBase package of PetroCOVERY Solution is a collection of native C++ classes that 
 * implement the fundamental algorithms & operations required to 
 * satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASE_DBG_TRACER_H__
#define __ANYBASE_DBG_TRACER_H__

// Refer to EXPORT & IMPORT definitions
#include "anybase.h"

// Refer to anystring etc
#include "anyport.h"

//
#include "any/thread/jtc.h"

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4996 )  // Deprecated function calling
#pragma warning( disable: 4251 )  //  needs to have dll-interface

// UeBase namespace
namespace AnyBase
{
	// Forward classes
	class CAnyFileBasic;
	class CAnyDirBasic;
	class CAnyStringBasic;
	class CAnyOutputter;

	/*!
	*
	**/
	class ANYBASE_CLASS CAnyDateLogger 
	{
	public:
		CAnyDateLogger() 
		{
#if defined(_MSC_VER)
			_tzset();
#endif
		}
		const char* HumanDate() 
		{
#if defined(_MSC_VER)
			_strtime_s(buffer_, sizeof(buffer_));
#else
			time_t time_value = time(NULL);
			struct tm *pnow;
#if !defined(_WIN32)
			struct tm now;
			pnow = localtime_r(&time_value, &now);
#else
			pnow = localtime(&time_value);  // NOLINT(*)
#endif
			snprintf(buffer_, sizeof(buffer_), "%02d:%02d:%02d",
				pnow->tm_hour, pnow->tm_min, pnow->tm_sec);
#endif
			return buffer_;
		}

	private:
		char buffer_[9];
	};

	/**
	* Auxiliary class for checking memory usage, time elapse etc.
	*
	*/
    class ANYBASE_CLASS CAnyDbgLogger
    {
		// Disallow the automatically or implicitly creation of this object
		CAnyDbgLogger(const CAnyDbgLogger &other);
		void operator=(const CAnyDbgLogger &other);

	protected:
		// Only be called by sub-classes as common initialization place
		/*!
        * Note:
		* Here fileName is the file being checked or logged
        */
        CAnyDbgLogger(const anystring &fileName, int line);

	public:
		/*!
		* This class can be used for one specified class then log interesting thing
		*
		* Note:
		* Here fileName is the file to record the log information
		*/
        CAnyDbgLogger(const anystring &fileName);

		/*!
		*
		*/
		virtual ~CAnyDbgLogger();

    public:
        //
        //
        //
		/*!
		*
		**/
		virtual void Log(const TCHAR *format, ...);

		/*!
		*
		*/
		const anystring &GetLogFile()
		{
			return m_logFile;
		}

		/*!
		*
		**/
		void *GetLogHandle()
		{
			return m_logHandle;
		}

		//
		//
		//
		/*!
		*
		**/
		static void RegisterOutputter(CAnyOutputter *outputter)
		{
			m_outputter = outputter;
		}

    protected:
        // Which file is being monitored and which line occur
        anystring m_fileName;
        int m_line;

		// For print of variant variables 
		TCHAR m_printBuf[1024];

        // Initial status and ending status
        int m_start;
        int m_end;

		// Log file handle
		anystring m_logFile;
		void *m_logHandle;

		// Auxiliary classes for file operations
		const CAnyFileBasic &m_fileBasic;
		const CAnyDirBasic &m_pathBasic;
		const CAnyStringBasic &m_stringBasic;

		//
		JTCMutex m_mutex;

		//
		static CAnyOutputter *m_outputter;
    };

	/**
	* Get time elapsing report happened to one function or one scope in function, so this class should always stack variable.
	* 
	* Note:
	* There should only one file for the whole project to collecting those time statistic results.
	*/
    class ANYBASE_CLASS CAnyTimeLogger : public CAnyDbgLogger
    {
		// Disallow the automatically or implicitly creation of this object
		CAnyTimeLogger(const CAnyTimeLogger &other);
		void operator=(const CAnyTimeLogger &other);

		// Constant variable for getting time elapse statistic result
		static const int TIMETHRESHOLD = 1; // Unit: S

    public:
        //
        //
        //
		/*!
		*
		*/
        CAnyTimeLogger(const anystring &fileName, int line);

		/*!
		*
		*/
        ~CAnyTimeLogger();

    public:
        //
        //
        //
		/*!
		*
		**/
		void Log(const TCHAR *format, ...);

		/*!
		*
		*/
		static const anystring &GetLogFile()
		{
			return m_timeFile;
		}

	private:
		// The only file for recoding time info
		static anystring m_timeFile;
		static void *m_timeHandle;

		//
		JTCMutex m_mutex;
    };

	/*!
	* Get memory consuming report happened to one function or one scope in function, , so this class should always stack variable.
	*
	* Note:
	* There should only one file for the whole project to collecting those memory consuming statistic results.
	*
	*/
    class ANYBASE_CLASS CAnyMemoryLogger : public CAnyDbgLogger
    {
		// Disallow the automatically or implicitly creation of this object
		CAnyMemoryLogger(const CAnyMemoryLogger &other);
		void operator=(const CAnyMemoryLogger &other);

		// Constant variable for getting time elapse statistic result
		static const int MEMTHRESHOLD = 50; // Unit: KB

    public:
        //
        //
        //
		/*!
		*
		*/
		CAnyMemoryLogger(const anystring &fileName, int line);

		/*!
		*
		*/
		~CAnyMemoryLogger();

    public:
        //
        //
        //
		/*!
		*
		**/
		void Log(const TCHAR *format, ...);

		/*!
		*
		*/
		static anystring GetLogFile()
		{
			return m_memFile;
		}

	private:
		// The only file for recoding time info
		static anystring m_memFile;
		static void *m_memHandle;

		//
		JTCMutex m_mutex;
    };

	/*!
	* Get memory consuming report happened to one function or one scope in function, , so this class should always stack variable.
	*
	* Note:
	* There should only one file for the whole project to collecting those memory consuming statistic results.
	*
	*/
    class ANYBASE_CLASS CAnyRunningLogger : public CAnyDbgLogger
    {
		// Disallow the automatically or implicitly creation of this object
		CAnyRunningLogger(const CAnyRunningLogger &other);
		void operator=(const CAnyRunningLogger &other);

		// Constant variable for getting time elapse statistic result
		static const int MEMTHRESHOLD = 50; // Unit: KB

    public:
        //
        //
        //
		/*!
		*
		*/
		CAnyRunningLogger(const anystring &fileName, int line);

		/*!
		*
		*/
		~CAnyRunningLogger();

    public:
        //
        //
        //
		/*!
		*
		**/
		void Log(const TCHAR *format, ...);

		/**
		*
		*/
		static const anystring &GetLogFile()
		{
			return m_runFile;
		}

	private:
		// The only file for recoding time info
		static anystring m_runFile;
		static void *m_runHandle;
    };

	/*!
	* Decide whether memory have leaks.
	*
	* Note:
	* There should only one file for the whole project to collecting those time statistic results.
	*/
    class ANYBASE_CLASS CAnyMemoryChecker : public CAnyDbgLogger
    {
		// Disallow the automatically or implicitly creation of this object
		CAnyMemoryChecker(const CAnyMemoryChecker &other);
		void operator=(const CAnyMemoryChecker &other);

    protected:
		/*!
		* Link of files being checked
		*/
		struct CheckedFile
		{
			// Current file and its follower in one link list
			TCHAR *m_name;
			CheckedFile *m_next;

			/**
			*
			*/
			CheckedFile() : m_name(0), m_next(0)
			{
			}
		};

		/*!
		* Link of memory blocks being checked
		*/
		struct CheckedMemory 
		{
			// Belonging to which file and where, namely which line of this file
			CheckedFile *m_file;
			int m_line;

			// Description of current block checked 
			unsigned int m_length;
			void *m_addr;
			CheckedMemory *m_next;
		    
			//
			CheckedMemory() : m_file(0), m_line(0), m_length(0), m_addr(0), m_next(0)
			{
			}
		};

	public:
		//
		// This class would be as a singleton
		//
		/*!
		*
		*/
		CAnyMemoryChecker(const anystring &fileName, int line);

		/*!
		*
		*/
		~CAnyMemoryChecker();

    public:
        //
        //
        //
		/*!
		*
		**/
		void Log(const TCHAR *format, ...);

		//
		//
		//
		/*!
		*
		*/
		void Collect();

		/*!
		*
		*/
		void Register(void *mem, unsigned int s, const anystring &fileName, int line);

		/*!
		*
		*/
		void UnRegister(void *mem);

		//
		//
		//
		/*!
		*
		*/
		static CAnyMemoryChecker &Get(const anystring &fileName = _T(""), int line = 0);

		/*!
		*
		*/
		static const anystring &GetLogFile()
		{
			return m_checkFile;
		}

    protected:
        // Links for those files checked and memory blocks
        CheckedMemory *m_memList;
        CheckedFile *m_fileList;

		// Iterative variables
        unsigned long m_maxMem;
        unsigned long m_curMem;

		// Only one file to record check info
		// It had better for the first position to initialize this static variable in order to 
		// monitor other's static objects
		static anystring m_checkFile;
		static void *m_checkHandle;

		//
		JTCMutex m_mutex;

		//
		static CAnyMemoryChecker m_checker;
    };
}
#endif
