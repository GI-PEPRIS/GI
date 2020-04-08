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

#ifndef ANYWAY_RCF_DIMENSION_GS_MASTER_RUN_SIMULATION_H
#define ANYWAY_RCF_DIMENSION_GS_MASTER_RUN_SIMULATION_H

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
			struct default_master_run_simulation{

				template<typename Master, typename GraphNode>
				static bool apply(Master &master, GraphNode *job_node){

					try{
						typedef typename rcf_serviceimpl<Master>::type MasterServantImpl;
						MasterServantImpl *masterimpl = master.m_servant;
						assert(masterimpl);

						if(!masterimpl->IsRunning())
						{
							//masterimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
							return false;
						}
						return masterimpl->RunSimulation(job_node->m_job_node_idx);
					}
					catch(...){

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
				typename Master,
				typename GraphNode,
				typename RcfTag = typename rcf_system<Master>::type
				>
			struct gs_master_run_simulation :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline bool apply(Master &master, GraphNode *job_node, Strategy &strategy)
				{
					return false;
					//return calculate_null::apply<int>(graph, strategy);
				}
			};

			//
			template <typename Master, typename GraphNode>
			struct gs_master_run_simulation<Master, GraphNode, deltasoft_tag> : public detail::default_master_run_simulation
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
		template<typename Master, typename GraphNode>
		bool gs_master_run_simulation(Master &master, GraphNode *job_node)
		{
			return dispatch::gs_master_run_simulation
				<
				Master,
				GraphNode
				>::apply(master, job_node);
		}

	}
}
#endif