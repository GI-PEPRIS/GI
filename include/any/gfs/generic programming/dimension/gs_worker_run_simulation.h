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

#ifndef ANYWAY_RCF_DIMENSION_GS_WORKER_RUN_SIMULATION_H
#define ANYWAY_RCF_DIMENSION_GS_WORKER_RUN_SIMULATION_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"


namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_worker_run_simulation{
				template<typename Worker>
				static void apply(Worker &worker){

					try
					{
						typedef typename rcf_serviceimpl<Worker>::type WorkerServantImpl;
						WorkerServantImpl *workerimpl = worker.m_servant;
						assert(workerimpl);

						if(!workerimpl->IsRunning())
						{
							//masterimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
							return;
						}
						workerimpl->RunSimulation();
					}
					catch (...)
					{
						
					}

				}
			};
		}

		//
		//
		namespace dispatch
		{
			template
				<
				typename Worker,
				typename Tag = typename rcf_system<Worker>::type
				>
			struct gs_worker_run_simulation :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline int apply(Worker &worker, Strategy &strategy)
				{
					check_false
					//return calculate_null::apply<int>(graph, strategy);
				}
			};

			//
			template <typename Worker>
			struct gs_worker_run_simulation<Worker, deltasoft_tag> : public detail::default_worker_run_simulation
			{
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{

		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{

		}

		//
		//
		template<typename Worker>
		void gs_worker_run_simulation(Worker const& worker)
		{
			return dispatch::gs_worker_run_simulation
				<
				Worker
				>::apply(worker);
		}

	}
}
#endif