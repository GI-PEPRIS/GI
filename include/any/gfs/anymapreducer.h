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
#ifndef __ANYRCF_META_PROGRAMMING_MAP_REDUCER_H__
#define __ANYRCF_META_PROGRAMMING_MAP_REDUCER_H__

// refer to EXPORT & IMPORT
#include "anyrcf.h"
#include "any/base/anystl.h"

//
#include "generic programming\core\rcf_servicehandle.h"
#include "generic programming\core\rcf_serviceimpl.h"
#include "generic programming\core\job_specification.h"
#include "generic programming\core\job_parameter.h"
#include "generic programming\core\task_specification.h"
#include "generic programming\core\job_gfsfile.h"
#include "generic programming\core\job_mapkey.h"
#include "generic programming\core\job_mapvalue.h"
#include "generic programming\core\job_reducekey.h"
#include "generic programming\core\job_reducevalue.h"

#include "generic programming\dimension\start_service.h"

#include "generic programming\dimension\strategy\default_strategy.h"
#include "generic programming\dimension\mr_schedule_specification.h"
#include "generic programming\dimension\mr_schedule_mapper.h"
#include "generic programming\dimension\mr_schedule_reducer.h"
#include "generic programming\dimension\mr_mapper_task.h"
#include "generic programming\dimension\mr_reducer_task.h"
#include "generic programming\dimension\mr_mapper_start.h"
#include "generic programming\dimension\mr_reducer_start.h"
#include "generic programming\dimension\mr_reducer_reduce.h"
#include "generic programming\dimension\mr_mapper_map.h"
#include "generic programming\dimension\register_children.h"
#include "generic programming\dimension\mr_mapper_is_done.h"
#include "generic programming\dimension\mr_reducer_is_done.h"
using namespace anyway::rcf;

//
namespace AnyRCF
{
	/*!
	*
	**/
	template
	<
		typename JobTracker,
		typename JobMapper,
		typename JobReducer
	>
	class ANYRCF_CLASS CAnyMapReducer
	{
	public:
		// traits related to general service
		typedef typename rcf_servicehandle<JobTracker>::type JobServiceHandle;
		typedef typename rcf_serviceimpl<JobTracker>::type JobServiceImpl;
		typedef typename rcf_serviceimpl<JobMapper>::type JobMapperImpl;
		typedef typename rcf_serviceimpl<JobReducer>::type JobReducerImpl;

		// traits related to job tracker
		typedef typename job_specification<JobTracker>::type JobSpecification;
		typedef typename job_parameter<JobTracker>::type JobParameter;
		typedef typename job_gfsfile<JobTracker>::type JobGFSFile;
		
		// traits related to mapper
		typedef typename task_specification<JobMapper>::type MapperTaskSpecification;
		typedef std::vector<MapperTaskSpecification> MapTaskVector;

		typedef typename job_mapkey<JobMapper>::type MapKey;
		typedef typename job_mapvalue<JobMapper>::type MapValue;

		// traits related to reducer
		typedef typename task_specification<JobReducer>::type ReducerTaskSpecification;
		typedef std::vector<ReducerTaskSpecification> ReduceTaskVector;

		typedef typename job_reducekey<JobReducer>::type ReduceKey;
		typedef typename job_reducevalue<JobReducer>::type ReduceValue;

	public:
		//
		//
		//
		CAnyMapReducer(JobGFSFile *gfsfile);
		CAnyMapReducer()
		{ 
			m_tracker = 0; m_gfsfile = 0;};
		~CAnyMapReducer();

	public:
		//
		// configure map-reduce framework
		//
		void RegisterHandler(JobServiceHandle &handle)
		{
			// register master
			if(handle.m_servicetype & ST_GFS_Job)
			{
				//
				if(m_tracker)
				{
					delete m_tracker;
				}
				m_tracker = new JobTracker;
				m_tracker->m_servant = new JobServiceImpl;

				// start service
				bool rt = start_service<JobTracker, JobServiceHandle, default_strategy>(*m_tracker, handle, default_strategy());
				assert(rt);
			}
		}
		void RemoveHandler(JobServiceHandle &handle)
		{
			if(handle.m_servicetype & ST_GFS_Job)
			{
				if(m_tracker)
				{
					delete m_tracker;
				}
				m_tracker = 0;
			}		
		}

		//
		//
		//
		/*!
		*
		**/
		void Initialize(JobSpecification &specification, JobParameter &parameter)
		{
			//
			m_parameter = parameter;
			m_specification = specification;
			if(m_tracker)
			{
				mr_schedule_specification(*m_tracker, specification);
			}

			//
			m_maptasks.clear();
			m_mappers.clear();
			mr_schedule_mapper(*m_tracker, m_maptasks, default_strategy());
			for(int i = 0; i < m_maptasks.size(); i++)
			{
				ServiceHandle handle;
				handle.m_rackid = m_maptasks[i].m_rackid;
				handle.m_ip = m_maptasks[i].m_ip;
				handle.m_port = m_maptasks[i].m_port;
				handle.m_servicetype = ST_GFS_Mapper;
				JobMapper *mapper = new JobMapper;
				mapper->m_servant = new JobMapperImpl;
				start_service(*mapper, handle, default_strategy());
				mr_mapper_task(*mapper, m_maptasks[i], default_strategy());
				m_mappers.push_back(mapper);
			}

			//
			m_reducetasks.clear();
			m_reducers.clear();
			mr_schedule_reducer(*m_tracker, m_reducetasks, default_strategy());
			for(int i = 0; i < m_reducetasks.size();i++)
			{
				ServiceHandle handle;
				handle.m_rackid = m_reducetasks[i].m_rackid;
				handle.m_ip = m_reducetasks[i].m_ip;
				handle.m_port = m_reducetasks[i].m_port;
				handle.m_servicetype = ST_GFS_Reducer;
				JobReducer *reducer = new JobReducer;
				reducer->m_servant = new JobReducerImpl;
				start_service(*reducer, handle, default_strategy());
				mr_reducer_task(*reducer, m_reducetasks[i], default_strategy());
				m_reducers.push_back(reducer);
			}
			// m_output_gfsname open and allocate

		}
		/*!
		*
		**/
		void Run() // in sequential
		{
			// declare mapper nodes
			for(int i = 0; i < m_maptasks.size(); i++)
			{
				ServiceHandle handle;
				handle.m_rackid = m_maptasks[i].m_rackid;
				handle.m_ip = m_maptasks[i].m_ip;
				handle.m_port = m_maptasks[i].m_port;

				JobMapper *mapper = m_mappers[i];
				mr_mapper_task(*mapper, m_maptasks[i], default_strategy());

				unsigned long long groupid = m_maptasks[i].m_groupid;
				for(int j = 0; j < m_reducetasks.size(); j++)
				{
					if(groupid == m_reducetasks[j].m_groupid)
					{
						ServiceHandle handle;
						handle.m_rackid = m_reducetasks[j].m_rackid;
						handle.m_ip = m_reducetasks[j].m_ip;
						handle.m_port = m_reducetasks[j].m_port;

						register_children(*mapper, ST_GFS_Reducer, handle);
					}
				}
			}

			// map
			for(int i = 0; i < m_mappers.size(); i++)
			{
				mr_mapper_start(*m_mappers[i], m_parameter, default_strategy());
				mr_mapper_map(*m_mappers[i], m_specification, m_parameter, default_strategy());
			}

			// block ...
			while(true)
			{
				bool isalldone = true;
				for(int i = 0; i < m_mappers.size(); i++)
				{
					if(!mr_mapper_is_done(*m_mappers[i], m_maptasks[i], default_strategy()))
					{
						isalldone = false;
						break;
					}
				}
				if(isalldone)
					break;
				::Sleep(1000);
			}

			//

			// reduce
			for(int i = 0; i < m_reducers.size(); i++)
			{
				mr_reducer_task(*m_reducers[i], m_reducetasks[i], default_strategy());
				mr_reducer_start(*m_reducers[i], m_parameter, default_strategy());
				mr_reducer_reduce(*m_reducers[i], m_specification, m_parameter, default_strategy());
			}

			//
			while(true)
			{
				bool isalldone = true;
				for(int i = 0; i < m_reducers.size(); i++)
				{
					if(!mr_reducer_is_done(*m_reducers[i], m_reducetasks[i], default_strategy()))
					{
						isalldone = false;
						break;
					}
				}
				if(isalldone)
					break;
				::Sleep(1000);
			}
		}

		/*!
		*
		**/
		void Finalize()
		{

		}

	public:
		// gfs reactor
		JobGFSFile *m_gfsfile;

		// Tracker or Scheduler
		JobTracker *m_tracker;

		// JOB specification
		JobSpecification m_specification;
		JobParameter m_parameter;

		// TASK specification
		MapTaskVector m_maptasks;
		ReduceTaskVector m_reducetasks;
		std::vector<JobMapper*> m_mappers;
		std::vector<JobReducer*> m_reducers;
	};
}

#endif