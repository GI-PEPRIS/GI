/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYRCF_RCF_SERVICE_BASIC_H__
#define __ANYRCF_RCF_SERVICE_BASIC_H__

//
#include "anyrcf.h"
#include "any/base/anystl.h"

//
#include "rcf/RCF.hpp"
#include "rcf/RcfClient.hpp"
#include "rcf/util/Log.hpp"

//
//
#include "any/base/anydbgmacro.h"
#include "any/base/anystringbasic.h"
#include "any/base/anydirbasic.h"
#include "any/base/anyfilebasic.h"
using namespace AnyBase;

//
namespace AnyRCF
{	
	class ANYRCF_CLASS CRCFServiceBasic
	{
	protected:
		CRCFServiceBasic()
		{
			m_init = RCF::RcfInitDeinit();
		}
		~CRCFServiceBasic()
		{
		}

	protected:
		/*!
		*
		**/
		std::string ToString(RCF::Exception &e)
		{
			std::ostringstream os;

			int err = e.getErrorId();
			std::string errMsg = RCF::getErrorString(err);
			
			{
				 HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
				 SetConsoleTextAttribute(hStdout,FOREGROUND_RED|FOREGROUND_INTENSITY);

				std::cout << std::endl;
				std::cout << "Error: %s" << e.getErrorString() << std::endl;

				SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);//±ä»Ø°×É«
			}

			os << "[RCF:" << err << "] " << errMsg << std::endl;
			if (e.getSubSystem() == RCF::RcfSubsystem_Os)
			{
				err = e.getSubSystemError();
				errMsg = Platform::OS::GetErrorString(err);
				os << "[OS:" << err << "] " << errMsg << std::endl;
			}
			os << "[What] " << e.what() << std::endl;
			os << "[Context] " << e.getContext() << std::endl;
			os << "[Exception type] " << typeid(e).name() << std::endl;

			return os.str();
		}

		/*!
		*
		**/
		void ToLog(RCF::Exception &e)
		{
			RCF::Lock lock(m_ioStreamMutex);
			RUNNING_HERE

			string what = ToString(e);
			char info[1024] = {0, };
			TCHAR msg[1024] = {0, };
			::sprintf(info, "[%s]:%s\r\n", CAnyDateLogger().HumanDate(),what.c_str());
			CAnyStringBasic::Get().Ascii2Wcs(info, msg, 1024);

			RUNNING_MSG(msg);

			//throw e;
		}

		/*!
		*
		**/
		void ToLog(const std::exception &e)
		{
			RCF::Lock lock(m_ioStreamMutex);
			RUNNING_HERE

			char info[1024] = {0, };
			TCHAR msg[1024] = {0, };
			::sprintf(info, "[%s]:%s\r\n", CAnyDateLogger().HumanDate(),e.what());
			CAnyStringBasic::Get().Ascii2Wcs(info, msg, 1024);
			
			RUNNING_MSG(msg);

			//throw e;
		}

		template<typename Functor>
		void WrapInTryCatch(Functor functor)
		{
			try
			{
				Functor()
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
			catch(const std::exception &e)
			{
				ToLog(e);
			}
		}

	public:
		/*!
		*
		**/
		static void StartLogger()
		{
			RCF::LogManager::instance().deactivateAllLoggers();

			static RCF::LoggerPtr loggerPtr;
			if(!loggerPtr.get())
			{
				std::string fileLogFormat = "%C\t[Thread %D]\t%X";
				TCHAR wPath[CAnyDirBasic::MAXPATHLENGTH] = {0, };
				CAnyDirBasic::Get().GetModulePath(wPath, CAnyDirBasic::MAXPATHLENGTH);
				anystring wFile = wPath;
				wFile += _T("\\");
				wFile += _T("rcf.log");

				//
				char logfile[CAnyDirBasic::MAXPATHLENGTH] = {0, };
				CAnyStringBasic::Get().Wcs2Ascii((TCHAR *)wFile.c_str(), logfile, CAnyDirBasic::MAXPATHLENGTH);
				loggerPtr = RCF::LoggerPtr(new RCF::Logger(RCF::LogNameRcf, RCF::LogLevel_3, RCF::LogToFile(logfile), fileLogFormat));
			}
			loggerPtr->activate();
		}
	protected:
		//
		RCF::RcfInitDeinit m_init;
		// logout
		RCF::Mutex m_ioStreamMutex;
	};
}

#endif