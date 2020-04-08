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

#ifndef ANYWAY_RCF_DIMENSION_GS_MODEL_CREATE_SOLUTIONS_H
#define ANYWAY_RCF_DIMENSION_GS_MODEL_CREATE_SOLUTIONS_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"

#include "generic programming/dimension/strategy/simulation_model_create_solutions_for_basin.h"

namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_model_create_solutions
			{
				template
					<
					typename Model
					>
				static int apply(Model &model)
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
				typename Model,
				typename Tag = typename tag<Model>::type
				>
			struct gs_model_create_solutons :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline int apply(Model &model, Strategy &strategy)
				{
					//return calculate_null::apply<int>(graph, strategy);
				}
			};

			//
			template <typename Model>
			struct gs_model_create_solutons<Model, simulation_model_simulator_basin_tag>
			{
				template<typename Strategy>
				static inline int apply(Model &model, Strategy &strategy)
				{
					return strategy.apply(model);
				}
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
			struct gs_model_create_solutons
			{
				template <typename Model, typename Strategy>
				static inline int apply(Model &model, Strategy &strategy)
				{
					return dispatch::gs_model_create_solutons<Model, SolutionContainer>::apply(model, strategy);
				}

				//
				template <typename Model>
				static inline int apply(Model &model, default_strategy)
				{
					return detail::default_model_create_solutions<Model>::apply(model);
				}

				template <typename Model>
				static inline int apply(Model &model, detail::strategy::simulation_model_create_solutions_for_basin &basin_strategy_type)
				{
					return dispatch::gs_model_create_solutons<Model>::apply(model, basin_strategy_type);
				}
			};
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
			template <typename Model>
			struct gs_model_create_solutons
			{
				template <typename Strategy>
				static inline int apply(Model &model, Strategy &strategy)
				{
					return resolve_strategy::gs_model_create_solutons::apply(model, strategy);
				}
			};
		}

		//
		//
		template<typename Model>
		int gs_model_create_solutons(Model &model)
		{
			return resolve_variant::gs_model_create_solutons
				<
				Model
				>::apply(model, default_strategy());
		}

		template<typename Model,typename Strategy>
		int gs_model_create_solutons(Model &model, Strategy &strategy)
		{
			return resolve_variant::gs_model_create_solutons
				<
				Model
				>::apply(model, strategy);
		}
	}
}
#endif