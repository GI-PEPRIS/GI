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

#ifndef ANYWAY_RCF_DIMENSION_GS_WORKER_CLEAR_BLOCKS_H
#define ANYWAY_RCF_DIMENSION_GS_WORKER_CLEAR_BLOCKS_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"
#include "generic programming/dimension/strategy/simulation_worker_clear_blocks_for_basin.h"

namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_worker_clear_blocks{
				template<typename Worker, typename Model>
				static void apply(Worker &worker, Model &model) {
					//
					assert(false);
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
				typename Model,
				typename RcfTag = typename rcf_system<Worker>::type,
				typename ModelTag = typename tag<Model>::type
				>
			struct gs_worker_clear_blocks :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline void apply(Worker &worker, Model &model, Strategy &strategy)
				{
					//return calculate_null::apply<int>(graph, strategy);
				}
			};

			//
			template <typename Worker, typename Model>
			struct gs_worker_clear_blocks<Worker, Model, deltasoft_tag, simulation_model_simulator_basin_tag>
			{
				template<typename Strategy>
				static inline void apply(Worker &worker, Model &model, Strategy &strategy)
				{
					return strategy.apply(worker, model);
				}
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
			struct gs_worker_clear_blocks
			{
				template <typename Worker, typename Model, typename Strategy>
				static inline void apply(Worker &worker, Strategy &strategy)
				{
					return dispatch::gs_worker_clear_blocks<Graph>::apply(graph, strategy);
				}

				//
				template <typename Worker, typename Model>
				static inline void apply(Worker &worker, Model &model, default_strategy &default_strategy)
				{
				}

				//
				template <typename Worker, typename Model>
				static inline void apply(Worker &worker, Model &model, detail::strategy::simulation_worker_clear_blocks_for_basin &basin_strategy)
				{
					return dispatch::gs_worker_clear_blocks<Worker, Model>::apply(worker, model, basin_strategy);
				}
			};
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
			template <typename Worker, typename Model>
			struct gs_worker_clear_blocks
			{
				template <typename Strategy>
				static inline void apply(Worker &worker, Model &model, Strategy &strategy)
				{
					return resolve_strategy::gs_worker_clear_blocks::apply(worker, model, strategy);
				}
			};
		}

		//
		//
		template<typename Worker, typename Model>
		void gs_worker_clear_blocks(Worker &worker, Model &model)
		{
			return resolve_variant::gs_worker_clear_blocks
				<
				Worker,
				Model
				>::apply(worker, model, default_strategy());
		}

		template<typename Worker, typename Model, typename Strategy>
		void gs_worker_clear_blocks(Worker &worker, Model &model, Strategy &strategy)
		{
			return resolve_variant::gs_worker_clear_blocks
				<
				Worker,
				Model
				>::apply(worker, model, strategy);
		}
	}
}
#endif