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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_GRAPH_NODE_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_GRAPH_NODE_H

//
#include "boost/function.hpp"

//
#include "any/base/anystl.h"
#include "any/base/loki/generic.h"
using namespace AnyBase;
using namespace AnyBase::Loki;

//
#include "generic programming/core/tag.h"
#include "generic programming/core/tags.h"
#include "generic programming/core/simulation_graph_node.h"
#include "generic programming/core/simulation_graph_node_function.h"
#include "generic programming/core/simulation_graph_node_container.h"


namespace anyway
{ 
	namespace rcf
	{
		namespace model
		{
			//
			template
				<
				typename Simulator, 
				typename Signature,
				typename TypeTag,
				typename RunTag,
				typename ParentNode = SimulationJobNode
				>
			class geo_simulation_graph_node : public ParentNode
			{
				

			public:
				//
				explicit inline geo_simulation_graph_node()
				{
					m_is_loop_node = IsSameType<TypeTag, simulation_graph_node_type_loop_tag>::value;
					m_is_async_node = IsSameType<RunTag, simulation_graph_node_run_async_tag>::value;
					m_is_sync_node = IsSameType<RunTag, simulation_graph_node_run_sync_tag>::value || IsSameType<RunTag, simulation_graph_node_run_sync_update_block_tag>::value || \
						IsSameType<RunTag, simulation_graph_node_run_sync_update_model_tag>::value || IsSameType<RunTag, simulation_graph_node_run_sync_solve_marix_tag>::value;
					m_is_need_update_model = IsSameType<RunTag, simulation_graph_node_run_sync_update_model_tag>::value;
					m_is_need_solve_model_matrix = IsSameType<RunTag, simulation_graph_node_run_sync_solve_marix_tag>::value;
					m_is_need_update_solution_block = IsSameType<RunTag, simulation_graph_node_run_sync_update_block_tag>::value;
				}
				~geo_simulation_graph_node()
				{
				}

				//
				bool do_job()
				{
					return m_block_function();
				}
				//
			public:	
				typedef boost::function<Signature> BlockFunction;
				BlockFunction m_block_function;				
			};
		}

		//
		namespace traits
		{
			template
				<
				typename Simulator, 
				typename Signature,
				typename TypeTag,
				typename RunTag,
				typename Node
				>
			struct simulation_graph_node<model::geo_simulation_graph_node<Simulator, Signature, TypeTag, RunTag, Node> >
			{
				typedef Node type;
			};

			template
				<
				typename Simulator, 
				typename Signature,
				typename TypeTag,
				typename RunTag,
				typename Node
				>
			struct simulation_graph_node_container<model::geo_simulation_graph_node<Simulator, Signature, TypeTag, RunTag, Node> >
			{
				typedef AnyRCF::SimulationJobNodeContainer type;
			};
		}
	}	
}

#endif