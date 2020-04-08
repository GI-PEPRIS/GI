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
#ifndef __ANYBASIN_DISTRIBUTED_SIMULATION_SCHEDULER_H__
#define __ANYBASIN_DISTRIBUTED_SIMULATION_SCHEDULER_H__

//
#include "anybasin.h"
#include "distributedsimulationgeneric.h"
#include "distributedsimulationmodel.h"
#include "distributedsimulationsolution.h"
#include "distributedsimulationjob.h"
#include "distributedsimulationblock.h"
#include "hyperdebughelper.h"

#include "any/base/loki/generic.h"

//
namespace AnyBasin
{
	struct SchedulerProgressCallback
	{
		int m_cur;
		int m_total;
		string m_status;
	};
	template<typename Signature>
	struct DistributedSchedulerProgressCallback : public SchedulerProgressCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};
	/*!
	*
	**/
	class ANYBASIN_CLASS CDistributedSimulationScheduler
	{
	public:
		//
		struct ScheduleOption
		{
			
		};

	public:
		CDistributedSimulationScheduler();
		~CDistributedSimulationScheduler();

	public:
		//
		//
		//
		/*!
		*
		**/
		template<typename BurialTag, typename ThermalTag, typename traptag>
		void RunJob(CDistributedSimulationModel *model, ScheduleOption &scheduleoption)
		{	
			#define SCHEDULER_LOG CDistributedSimulationScheduler::GetLogger().Log<CDistributedSimulationScheduler>(__FILE__, __LINE__)	
			
			CAnyTimeBasic::TimeReport report;
			CAnyTimeBasic timeBasic;
			timeBasic.GetNow(report);
			SCHEDULER_LOG << "			This simulation begins at hour " << report.m_hour << ", minute " << report.m_minute;

			SCHEDULER_LOG << "			To generate job blocks ... ";
			assert(model);
			int total_blocks = 0;
			for(int i = 0; i < model->get_solution_number(); i++)
			{
				CDistributedSimulationSolution *solution = (CDistributedSimulationSolution*)(model->get_solution(i));
				solution->Solution2Job<BurialTag, ThermalTag, traptag>();
				total_blocks += solution->get_job_number();
				assert(solution->get_job_number());
			}
			SCHEDULER_LOG << "			Generate " << total_blocks << " job blocks ";

			SCHEDULER_LOG << "			To schedule all job blocks to calculate in fair way and get the first batch of job blocks";
			std::vector<CDistributedSimulationBlock*> blocks; 
			DoGetReadyJobBlocks(model, blocks);
			std::map<string, int> tag_times;
			while(blocks.size())
			{
				bool needloop = false;
				if(blocks.size())
				{
					if(m_progresscb)
					{
						m_progresscb->m_cur = 0;
						m_progresscb->m_total = 100;
						m_progresscb->m_status = blocks[0]->m_distributed_job_node_function_tag;
						if(tag_times.find(m_progresscb->m_status) != tag_times.end())
							tag_times[m_progresscb->m_status]++;
						else
							tag_times[m_progresscb->m_status] = 0;
						char buffer[256];
						::sprintf(buffer, ":time%d", tag_times[m_progresscb->m_status]);
						string bufferstr = buffer;
						m_progresscb->m_status = m_progresscb->m_status + bufferstr;
						((DistributedSchedulerProgressCallback<void (const SchedulerProgressCallback&)> *)m_progresscb)->m_function(*m_progresscb);
					}
					if(blocks[0]->m_distributed_job_node_run_tag == "job_model_sync_run_tag")
					{
						SCHEDULER_LOG << "			The " << blocks[0]->m_solution_idx \
							<< "th solution and the " << blocks[0]->m_block_idx \
							<< "the job block's function" << blocks[0]->m_distributed_job_node_function_tag << " is waiting for sync";

						bool rt = blocks[0]->do_job();
						if(rt)
							needloop = true;
					}
					else
					{
						#pragma omp parallel for schedule(static)
						for(int i = 0; i < blocks.size(); i++)
						{
							SCHEDULER_LOG << "			The " << blocks[i]->m_solution_idx \
								<< "th solution and the " << blocks[i]->m_block_idx \
								<< "the job block's function" << blocks[i]->m_distributed_job_node_function_tag << " is ready";

							bool rt = blocks[i]->do_job();
							if(rt)
								needloop = true;

							SCHEDULER_LOG << "			The " << blocks[i]->m_solution_idx \
								<< "th solution and the " << blocks[i]->m_block_idx \
								<< "the job block's function" << blocks[i]->m_distributed_job_node_function_tag << " is done";
						}
					}
				}

				SCHEDULER_LOG << "			To get the next batch of job blocks";
				for(int i = 0; i < model->get_solution_number(); i++)
				{
					CDistributedSimulationSolution *solution = (CDistributedSimulationSolution *)(model->get_solution(i));
					solution->reset_for_next_job(needloop);
				}
				DoGetReadyJobBlocks(model, blocks);
			}
			if(m_progresscb)
			{
				delete m_progresscb;
				m_progresscb = 0;
			}
			timeBasic.GetNow(report);
			SCHEDULER_LOG << "			This simulation ends at hour " << report.m_hour << ", minute " << report.m_minute;
		}

		//
		static CHyperDebugHelper &GetLogger();

	private:
		//
		//
		bool IsWait(CDistributedSimulationModel *model, CDistributedSimulationJob *job);
		void DoGetReadyJobBlocks(CDistributedSimulationModel *model, std::vector<CDistributedSimulationBlock*> &blocks);

	public:
		// jobs from job graph sorted by TOPO algorithm
		SchedulerProgressCallback *m_progresscb;
	};
}

#endif
