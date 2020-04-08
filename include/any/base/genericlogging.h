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
#ifndef __ANYBASE_GENERIC_LOGGING_H__
#define __ANYBASE_GENERIC_LOGGING_H__

#include "anybase.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

namespace AnyBase
{
	class ANYBASE_CLASS GenericDateLogger 
	{
	public:
		GenericDateLogger() 
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

	class ANYBASE_CLASS ConsoleLogMessage 
	{
	public:
		ConsoleLogMessage(const char* file, int line);
		~ConsoleLogMessage() { log_stream_ << '\n'; }
		std::ostream& stream() { return log_stream_; }

	protected:
		std::ostream& log_stream_;

	private:
		GenericDateLogger pretty_date_;
		ConsoleLogMessage(const ConsoleLogMessage&);
		void operator=(const ConsoleLogMessage&);
	};

	class ANYBASE_CLASS FileLogMessage 
	{
	public:
		FileLogMessage(std::ofstream &stream, const char* file, int line);
		~FileLogMessage() { log_stream_ << '\n'; }
		std::ofstream& stream() { return log_stream_; }

	protected:
		std::ofstream &log_stream_;

	private:
		GenericDateLogger pretty_date_;
		FileLogMessage(const FileLogMessage&);
		void operator=(const FileLogMessage&);
	};
}
#endif

