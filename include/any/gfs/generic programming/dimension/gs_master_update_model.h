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

#ifndef ANYWAY_RCF_DIMENSION_GS_MASTER_UPDATE_MODEL_H
#define ANYWAY_RCF_DIMENSION_GS_MASTER_UPDATE_MODEL_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"


#include "generic programming/core/rcf_system.h"
#include "generic programming/dimension/strategy/simulation_master_update_model_by_file.h"

namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_master_update_model
			{
				template<typename Master, typename Model, typename GraphNode>
				static bool apply(Master &master, Model &model, GraphNode *running_node)
				{
					assert(false);
					return 0;
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
				typename Model,
				typename GraphNode,
				typename RpcTag = typename rcf_system<Master>::type,
				typename SimulatorTag = typename tag<Model>::type
				>
			struct gs_master_update_model : detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline bool apply(Master &master, Model &model, GraphNode *running_node, Strategy &strategy)
				{
					return calculate_null::apply<int>(worker, model, strategy);
				}
			};

			//
			template <typename Master, typename Model, typename GraphNode>
			struct gs_master_update_model<Master, Model, GraphNode, deltasoft_tag, simulation_model_simulator_basin_tag>
			{
				template<typename Strategy>
				static inline bool apply(Master &master, Model &model, GraphNode *running_node, Strategy &strategy)
				{
					return strategy.apply(master, model, running_node);
				}
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
			struct gs_master_update_model
			{
				template<typename Master, typename Model, typename GraphNode, typename Strategy>
				static inline bool apply(Master &master, Model &model, GraphNode *running_node, Strategy &strategy)
				{
					return dispatch::gs_master_update_model<Master, Model, GraphNode>::apply(master, model, running_node, strategy);
				}

				//
				template<typename Master, typename Model, typename GraphNode>
				static inline bool apply(Master &master, Model &model, GraphNode *running_node, default_strategy &default_strategy)
				{
					return detail::default_master_update_model::apply(master, model, running_node);
				}

				template<typename Master, typename Model, typename GraphNode>
				static inline bool apply(Master &master, Model &model, GraphNode *running_node, detail::strategy::simulation_master_update_model_by_file &file_strategy)
				{
					return dispatch::gs_master_update_model<Master, Model, GraphNode>::apply(master, model, running_node, file_strategy);
				}
			};
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
			template<typename Master, typename Model, typename GraphNode>
			struct gs_master_update_model
			{
				template <typename Strategy>
				static inline bool apply(Master &master, Model &model, GraphNode *running_node, Strategy &strategy)
				{
					return resolve_strategy::gs_master_update_model::apply(master, model, running_node, strategy);
				}
			};
		}

		//
		//
		template<typename Master, typename Model, typename GraphNode>
		bool gs_master_update_model(Master &master, Model &model, GraphNode *running_node)
		{
			return resolve_variant::gs_master_update_model
				<
				Master,
				Model,
				GraphNode
				>::apply(master, model, running_node, default_strategy());
		}

		template<typename Master, typename Model, typename GraphNode, typename Strategy>
		bool gs_master_update_model(Master &master, Model &model, GraphNode *running_node, Strategy &strategy)
		{
			return resolve_variant::gs_master_update_model
				<
				Master,
				Model,
				GraphNode
				>::apply(master, model, running_node, strategy);
		}
	}
}
#endif