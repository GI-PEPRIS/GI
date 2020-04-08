/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYRCF_JOB_TASK_RUNNER_H__
#define __ANYRCF_JOB_TASK_RUNNER_H__

//
#include "anyrcf.h"
#include "anyclientimpl.h"

//
namespace AnyRCF
{
	/*!
	*
	**/
	class ANYRCF_CLASS CAnyJobTaskRunner
	{
		//
		typedef std::vector<CAnyClientImpl *> MapReducerVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyJobTaskRunner();
		virtual ~CAnyJobTaskRunner();

	public:
		//
		//
		//

	protected:
		//
		//
		//
		/*!
		*
		**/
		std::vector<unsigned long long> &DoGetMapChunks(const ServiceHandle &handle);
		void DoStartJob();
		void DoEndJob();

		void GetFileLength(std::string filepath, long long &filelength);
		void ReadData(std::string filepath, std::vector<char> &data, int readlength, long long offset, void* &fileHandle);
		void WriteData(std::string filepath, std::vector<char> &data, int &datalength, long long offset, int filehandletype, void* &fileHandle);
		void DoCreateDir(string filepath);
	public:
		void SetJobStatus(const std::string& gfsname, JobStatus &jobstatus);
		void GetJobStatus(const std::string& gfsname, JobStatus &jobstatus);

	public:
		// schedule for current job upon one gfs name
		JobSpecification m_specification;
		// master stub
		CAnyClientImpl *m_masterclient;
		// job stub
		CAnyClientImpl *m_jobclient;
		// event stub
		CAnyClientImpl *m_eventclient;

		// tasks
		JobTaskServerVector m_maptasks;
		JobTaskServerVector m_reducetasks;
		// mapper task stubs
		MapReducerVector m_mapperclients;
		// reducer task stubs
		MapReducerVector m_reducerclients;
	};
}
#endif
