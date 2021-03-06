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

#ifndef ANYWAY_RCF_DIMENSION_GS_MASTER_SET_JOB_IDX_H
#define ANYWAY_RCF_DIMENSION_GS_MASTER_SET_JOB_IDX_H

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
		}

		//
		//
		namespace dispatch
		{
			template
				<
				typename Graph,
				typename Tag = typename tag<Graph>::type
				>
			struct gs_master_set_job_idx :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline int apply(Graph &graph, Strategy &strategy)
				{
					//return calculate_null::apply<int>(graph, strategy);
				}
			};

			//
			template <typename Graph>
			struct gs_master_set_job_idx<Graph, simulation_graph_in_topo_order_tag>
			{
				template<typename Strategy>
				static inline int apply(Graph &graph, Strategy &strategy)
				{
					return strategy.apply(graph);
				}
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
			struct gs_master_set_job_idx
			{
				template <typename Graph, typename Strategy>
				static inline int apply(Graph &graph, Strategy &strategy)
				{
					return dispatch::gs_master_set_job_idx<Graph>::apply(graph, strategy);
				}

				//
				template <typename Graph>
				static inline int apply(Graph &graph, default_strategy)
				{
					typedef detail::strategy::simulation_graph_into_nodes_by_topo_order topo_strategy_type;
					return dispatch::gs_master_set_job_idx<Graph>::apply(graph, topo_strategy_type());
				}
			};
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
			template <typename Graph>
			struct gs_master_set_job_idx
			{
				template <typename Strategy>
				static inline int apply(Graph &graph, Strategy &strategy)
				{
					return resolve_strategy::gs_master_set_job_idx::apply(graph, strategy);
				}
			};
		}

		//
		//
		template<typename Graph>
		int gs_master_set_job_idx(Graph &graph)
		{
			return resolve_variant::gs_master_set_job_idx
				<
				Graph
				>::apply(graph, default_strategy());
		}

		template<typename Graph, typename Strategy>
		int gs_master_set_job_idx(Graph &graph,Strategy &strategy)
		{
			return resolve_variant::gs_master_set_job_idx
				<
				Graph
				>::apply(graph, strategy);
		}
	}
}
#endif