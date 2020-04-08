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
#ifndef __ANYRCF_GFS_JOB_STUB_H__
#define __ANYRCF_GFS_JOB_STUB_H__

//
#include "anyrcf.h"
#include "servicestub.h"
#include "gfsjobservant.h"

//
namespace AnyRCF
{
	class ANYRCF_CLASS CGFSJobStub : public CServiceStub<I_AnyGFSJob>
	{
	public:
		CGFSJobStub();
		~CGFSJobStub();

	public:
		void SetJobSpecification(const JobSpecification &specification)
		{
			try
			{
				m_client->SetJobSpecification(specification);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Job4Mapper(JobTaskServerVector &mapreducers)
		{
			try
			{
				m_client->Job4Mapper(mapreducers);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Job4Reducer(JobTaskServerVector &mapreducers)
		{
			try
			{
				m_client->Job4Reducer(mapreducers);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		unsigned long long FirstSplit()
		{
			try
			{
				return m_client->FirstSplit();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);

				return 0;
			}
		}
		unsigned long long NextSplit()
		{
			try
			{
				return m_client->NextSplit();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);

				return 0;
			}
		}
		void SetJobStatus(const std::string& gfsname, JobStatus &jobstatus)
		{
			try
			{
				m_client->SetJobStatus(gfsname, jobstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetJobStatus(const std::string& gfsname, JobStatus &jobstatus)
		{
			try
			{
				m_client->GetJobStatus(gfsname, jobstatus);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
	};
	template class ANYRCF_CLASS CServiceStub<I_AnyGFSJob>;
}
#endif

