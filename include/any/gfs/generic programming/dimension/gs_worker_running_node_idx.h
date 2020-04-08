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

#ifndef ANYWAY_RCF_DIMENSION_gs_worker_running_node_idx_H
#define ANYWAY_RCF_DIMENSION_gs_worker_running_node_idx_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"
#include "generic programming/dimension/strategy/simulation_graph_into_nodes_by_topo_order.h"

namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_worker_running_node_idx{
				template<typename Worker>
				static int apply(Worker &worker){

					try
					{
						typedef typename rcf_serviceimpl<Worker>::type WorkerServantImpl;
						WorkerServantImpl *workerimpl = worker.m_servant;
						assert(workerimpl);

						if(!workerimpl->IsRunning())
						{
							//masterimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
							return 0;
						}
						return workerimpl->GetRunningNodeidx();
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
			struct gs_worker_running_node_idx :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline int apply(Worker &worker, Strategy &strategy)
				{
					//return calculate_null::apply<int>(graph, strategy);
					return 0;
				}
			};

			//
			template <typename Worker>
			struct gs_worker_running_node_idx<Worker, deltasoft_tag>:public detail::default_worker_running_node_idx
			{
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
			struct gs_worker_running_node_idx
			{
				template <typename Worker, typename Strategy>
				static inline int apply(Worker &worker, Strategy &strategy)
				{
					return dispatch::gs_worker_running_node_idx<Worker, Strategy>::apply(worker, strategy);
				}


				template <typename Worker>
				static inline int apply(Worker &worker, default_strategy &default_strategy)
				{
					return dispatch::gs_worker_running_node_idx<Worker>::apply(worker);
				}
			};
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
			template <typename Worker>
			struct gs_worker_running_node_idx
			{
				template <typename Strategy>
				static inline int apply(Worker &worker, Strategy &strategy)
				{
					return resolve_strategy::gs_worker_running_node_idx::apply(worker, strategy);
				}
			};
		}

		//
		//
		template<typename Worker>
		int gs_worker_running_node_idx(Worker & worker)
		{
			return dispatch::gs_worker_running_node_idx
				<
				Worker
				>::apply(worker);
		}

		template<typename Worker, typename Strategy>
		int gs_worker_running_node_idx(Worker & worker, Strategy &strategy)
		{
			return resolve_variant::gs_worker_running_node_idx
				<
				Worker
				>::apply(worker, strategy);
		}
	}
}
#endif