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

#ifndef ANYWAY_RCF_DIMENSION_GS_MODEL_INITIALIZE_H
#define ANYWAY_RCF_DIMENSION_GS_MODEL_INITIALIZE_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"

//
#include "generic programming/dimension/calculate_null.h"
#include "generic programming/dimension/strategy/simulation_model_initialize_for_basin.h"

//
namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_model_intialize
			{
				template <typename Model, typename Mesh, typename MeshContainer>
				bool apply(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes)
				{
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
				typename Model,
				typename Mesh,
				typename MeshContainer,
				typename Tag = tag<Model>::type
				>
			struct gs_model_initialize :  detail::calculate_null
			{
				// not implemented
				template<typename Strategy>
				static inline bool apply(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes, Strategy &strategy)
				{
					check_false // should be never compiled
					return calculate_null::apply<bool>(graph, strategy);
				}
			};

			//
			template <typename Model, typename Mesh, typename MeshContainer>
			struct gs_model_initialize<Model, Mesh, MeshContainer, simulation_model_simulator_basin_tag>
			{
				template<typename Strategy>
				static inline bool apply(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes, Strategy &strategy)
				{
					return strategy.apply(model, init_mesh, refined_meshes);
				}
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
			struct gs_model_initialize
			{
				template<typename Model, typename Mesh, typename MeshContainer, typename Strategy>
				static inline bool apply(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes, Strategy &strategy)
				{
					return dispatch::gs_model_initialize<Model, Mesh, Strategy>::apply(graph, strategy);
				}

				//
				template<typename Model, typename Mesh, typename MeshContainer>
				static inline bool apply(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes, default_strategy)
				{
					return detail::default_model_intialize<Model, Mesh, MeshContainer>::apply(model, init_mesh, refined_meshes);
				}

				template<typename Model, typename Mesh, typename MeshContainer>
				static inline bool apply(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes, detail::strategy::simulation_model_initialize_for_basin &model_strategy_type)
				{
					return dispatch::gs_model_initialize<Model, Mesh, MeshContainer>::apply(model, init_mesh, refined_meshes, model_strategy_type);
				}
			};
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
			template<typename Model, typename Mesh, typename MeshContainer>
			struct gs_model_initialize
			{
				template <typename Strategy>
				static inline bool apply(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes, Strategy &strategy)
				{
					return resolve_strategy::gs_model_initialize::apply(model, init_mesh, refined_meshes, strategy);
				}
			};
		}

		//
		//
		template<typename Model, typename Mesh, typename MeshContainer &refined_meshes>
		bool gs_model_initialize(Model &model, Mesh *init_mesh)
		{
			return resolve_variant::gs_model_initialize
				<
				Model,
				Mesh,
				MeshContainer
				>::apply(model, init_mesh, refined_meshes, default_strategy());
		}

		template<typename Model, typename Mesh, typename MeshContainer, typename Strategy>
		bool gs_model_initialize(Model &model, Mesh *init_mesh, MeshContainer &refined_meshes, Strategy &strategy)
		{
			return resolve_variant::gs_model_initialize
				<
				Model,
				Mesh,
				MeshContainer
				>::apply(model, init_mesh, refined_meshes, strategy);
		}
	}
}
#endif