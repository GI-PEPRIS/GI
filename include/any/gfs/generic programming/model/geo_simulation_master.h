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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_MASTER_SERVICE_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_MASTER_SERVICE_H

#include "any/base/anystl.h"

// refinement from
#include "generic programming/model/rcfservant.h"

// traits
#include "generic programming/core/tags.h"
#include "generic programming/core/rcf_serviceimpl.h"
#include "generic programming/core/rcf_servicehandle.h"
#include "generic programming/core/simulation_mesh.h"
#include "generic programming/core/simulation_mesh_container.h"
#include "generic programming/core/simulation_solution.h"
#include "generic programming/core/simulation_solution_container.h"
#include "generic programming/core/simulation_block.h"
#include "generic programming/core/simulation_block_container.h"

#include  "generic programming/model/geo_simulation_worker.h"

// meta functions
#include "generic programming/dimension/strategy/default_strategy.h"
#include "generic programming/dimension/service_isrunning.h"
#include "generic programming/dimension/start_service.h"

#include "generic programming/dimension/gs_master_update_model.h"
#include "generic programming/dimension/gs_master_update_graph.h"
#include "generic programming/dimension/gs_master_set_rabbit_idx.h"
#include "generic programming/dimension/gs_master_set_tortoise_idx.h"
#include "generic programming/dimension/gs_master_download_model.h"
#include "generic programming/dimension/gs_master_run_simulation.h"

namespace anyway
{ 
	namespace rcf
	{
		namespace model
		{
			//
			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant, // master impl
				typename Model,
				typename Graph,
				template<typename, typename, typename> class ParentServant = rcfservant
				>
			class geo_simulation_master : public ParentServant<RcfSystem, RcfServiceHandle, RcfServant>
			{
				// traits related from model 
				typedef typename simulation_mesh<Model>::type HyperMesh;
				typedef typename simulation_mesh_container<Model>::type HyperMeshContainer;

				typedef typename simulation_solution<Model>::type HyperSolution;
				typedef typename simulation_solution_container<HyperSolution>::type HyperSolutionContainer;				

				typedef typename simulation_block<Model>::type HyperBlock;
				typedef typename simulation_block_container<HyperBlock>::type HyperBlockContainer;		

				// traits related from graph
				typedef typename simulation_graph_edge<Graph>::type GraphEdge;
				typedef typename simulation_graph_node<Graph>::type GraphNode;
				typedef typename simulation_graph_edge_container<Graph>::type GraphEdgeContainer;
				typedef typename simulation_graph_node_container<Graph>::type GraphNodeContainer;

				// traits from services
				typedef typename RcfServiceHandle MasterServiceHandle;
				typedef typename RcfServant MasterServiceImpl;

			public:
				//
				explicit inline geo_simulation_master()
				{
					m_servant = new RcfServant;
				}
				~geo_simulation_master()
				{
				}

			public:
				//
				bool depoly_master(MasterServiceHandle &handle) {
					start_service(*this, handle, default_strategy());
					bool rt = service_isrunning(*this, default_strategy());
					assert(rt);
					return rt;
				}

				// model 2 solutions, solution 2 blocks, blocks 2 workers
				void deploy_model(Model *model) {
								
					update_master_model(model,0);
				}

				// send graph to each worker
				void deploy_graph(Graph *graph) {
					//
					gs_master_update_graph(*this, *graph, detail::strategy::simulation_master_update_graph_in_vector());
				}

				//
				void update_master_graph(long rabbit_job_idx, long tortoise_job_idx) {
					gs_master_set_rabbit_idx(*this, rabbit_job_idx);
					gs_master_set_tortoise_idx(*this, tortoise_job_idx);
				}

				//
				void update_master_model(Model *model, GraphNode *running_node) {
					gs_master_update_model(*this, *model, running_node, detail::strategy::simulation_master_update_model_by_file());
				}
				void download_master_model(Model *model, GraphNode *running_node) {
					gs_master_download_model(*this, *model, running_node, detail::strategy::simulation_master_download_model_by_file());
				}

				//
				bool run_simulation(GraphNode *sync_node){
					return gs_master_run_simulation(*this, sync_node);
				}
			};
		}

		//
		namespace traits
		{
			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename Model,
				typename Graph
				>
			struct tag<model::geo_simulation_master<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
			{
				typedef simulation_service_master_tag type;
			};

			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename Model,
				typename Graph
				>
			struct rcf_system<model::geo_simulation_master<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
			{
				typedef RcfSystem type;
			};

			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename Model,
				typename Graph
				>
			struct rcf_servicehandle<model::geo_simulation_master<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
			{
				typedef RcfServiceHandle type;
			};

			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename Model,
				typename Graph
				>
			struct rcf_serviceimpl<model::geo_simulation_master<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
			{
				typedef RcfServant type;
			};

		}
	}
}

#endif