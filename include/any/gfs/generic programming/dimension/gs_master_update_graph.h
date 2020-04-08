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

#ifndef ANYWAY_RCF_DIMENSION_GS_MASTER_UPDATE_GRAPH_H
#define ANYWAY_RCF_DIMENSION_GS_MASTER_UPDATE_GRAPH_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"
#include "generic programming/dimension/strategy/simulation_master_update_graph_in_vector.h"

namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_master_update_graph {
				template<typename Master, typename Graph>
				static bool apply(Master &master, Graph &graph){
					assert(false);
					return false;
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
				typename Graph,
				typename RcfTag = typename rcf_system<Master>::type,
				typename GraphTag = typename tag<Graph>::type
				>
			struct gs_master_update_graph :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline int apply(Master &master, Graph &graph, Strategy &strategy)
				{
					//return calculate_null::apply<int>(graph, strategy);
				}
			};

			//
			template <typename Master, typename Graph>
			struct gs_master_update_graph<Master, Graph, deltasoft_tag, simulation_graph_in_topo_order_tag>
			{
				template<typename Strategy>
				static inline int apply(Master &master, Graph &graph, Strategy &strategy)
				{
					return strategy.apply(master, graph);
				}
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
			struct gs_master_update_graph
			{
				template <typename Master, typename Graph, typename Strategy>
				static inline int apply(Master &master, Graph &graph, Strategy &strategy)
				{
					return dispatch::gs_master_update_graph<Graph>::apply(graph, strategy);
				}

				//
				template <typename Master, typename Graph>
				static inline int apply(Graph &graph, default_strategy)
				{
					return detail::default_master_update_graph::apply(master, graph);
				}

				template <typename Master, typename Graph>
				static inline int apply(Master &master, Graph &graph, detail::strategy::simulation_master_update_graph_in_vector &upate_graph)
				{
					return dispatch::gs_master_update_graph<Master, Graph>::apply(master, graph, upate_graph);
				}
			};
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
			template <typename Master, typename Graph>
			struct gs_master_update_graph
			{
				template <typename Strategy>
				static inline int apply(Master &master, Graph &graph, Strategy &strategy)
				{
					return resolve_strategy::gs_master_update_graph::apply(master, graph, strategy);
				}
			};
		}

		//
		//
		template<typename Master, typename Graph>
		int gs_master_update_graph(Master & master, Graph &graph)
		{
			return resolve_variant::gs_master_update_graph
				<
				Master,
				Graph
				>::apply(master, graph, default_strategy());
		}

		template<typename Master, typename Graph, typename Strategy>
		bool gs_master_update_graph(Master & master, Graph &graph, Strategy &strategy)
		{
			return resolve_variant::gs_master_update_graph
				<
				Master,
				Graph
				>::apply(master, graph, strategy);
		}
	}
}
#endif