/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASIN_DISTRIBUTED_SIMULATION_SOLUTION_JOB_H__
#define __ANYBASIN_DISTRIBUTED_SIMULATION_SOLUTION_JOB_H__

//
#include "anybasin.h"
#include "distributedsimulationgeneric.h"

//
namespace AnyBasin
{
	/*!
	*
	**/
	class ANYBASIN_CLASS CDistributedSimulationJob : public DistributedJob
	{
	public:
		CDistributedSimulationJob();
		~CDistributedSimulationJob();

	public:
		//
		//
		//
		/*!
		*
		**/
		template<typename Simulator, typename signature, typename JobNodeFunctionTag, typename JobNodeRunTag>
		void Job2Block(JobBlockContainer &blockprototypes);

		//
		// rpc interfaces
		// 
		string get_run_tag()
		{
			return m_host_simulation_job_impl->m_distributed_job_node_run_tag;
		}
		string get_function_tag()
		{
			return m_host_simulation_job_impl->m_distributed_job_node_function_tag;
		}
		int get_block_number()
		{
			return m_job_ready_blocks.size();
		}
		DistributedBlock *get_block(int order)
		{
			return m_job_ready_blocks[order];
		}
		// state chain
		void job_set_state(unsigned long state){m_job_state = state;};
		unsigned long job_get_state(){return m_job_state;};

	public:
		// host job
		DistributedJob *m_host_simulation_job_impl;
		// job blocks in ready queue
		JobBlockContainer m_job_ready_blocks;
	};

}

#endif
