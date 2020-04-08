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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_WORKER_SERVICE_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_WORKER_SERVICE_H

//
#include "any/base/anystl.h"

// refinement from
#include "generic programming\model\rcfservant.h"

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

// meta functions
#include "generic programming/dimension/gs_worker_clear_blocks.h"
#include "generic programming/dimension/gs_worker_update_block.h"
#include "generic programming/dimension/gs_worker_download_block.h"
#include "generic programming/dimension/gs_worker_update_graph.h"
#include "generic programming/dimension/gs_worker_run_simulation.h"
#include "generic programming/dimension/gs_worker_resume_simulation.h"
#include "generic programming/dimension/gs_worker_running_node_idx.h"

namespace anyway
{ 
	namespace rcf
	{
		//
		namespace model
		{
			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename Model,
				typename Graph,
				template<typename, typename, typename> class ParentServant = rcfservant
				>
			class geo_simulation_worker : public ParentServant<RcfSystem, RcfServiceHandle, RcfServant>
			{
				// traits related from model 
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

				// traits from worker services				
				typedef typename RcfServiceHandle WorkerServiceHandle;

			public:
				//
				explicit inline geo_simulation_worker()
				{
					m_servant = new RcfServant;
				}
				~geo_simulation_worker()
				{
				}

			public:
				//
				bool depoly_worker(WorkerServiceHandle &handle) {
					start_service(*this, handle, default_strategy());
					bool rt = service_isrunning(*this, default_strategy());
					assert(rt);
					return rt;
				}
				bool update_simulation_graph(Graph *graph){
					return gs_worker_update_graph(*this, *graph, detail::strategy::simulation_worker_update_graph_in_vector());	
				}
				void clear_model_blocks(Model *model){
					gs_worker_clear_blocks(*this, *model, detail::strategy::simulation_worker_clear_blocks_for_basin());
				}
				bool update_block(Model *model, HyperBlock *block){
					return gs_worker_update_block(*this, *model, *block, 0, detail::strategy::simulation_worker_update_block_by_file());
				}
				bool update_block(Model *model, HyperBlock *block, GraphNode *running_node){
					return gs_worker_update_block(*this, *model, *block, running_node, detail::strategy::simulation_worker_update_block_by_file());
				}
				bool download_block(Model *model, HyperBlock *block, GraphNode *running_node){
					return gs_worker_download_block(*this, *model, *block, running_node, detail::strategy::simulation_worker_download_block_by_file());					
				}
				long get_block_number(){
					return 0;
				}
				long get_running_node_idx()
				{
					return gs_worker_running_node_idx(*this);
				}

				//
				void run_simulation(){
					gs_worker_run_simulation(*this);
				}
				void resume_simulation(long job_idx){
					gs_worker_resume_simulation(*this, job_idx);
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
			struct tag<model::geo_simulation_worker<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
			{
				typedef simulation_service_worker_tag type;
			};

			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename Model,
				typename Graph
				>
			struct rcf_system<model::geo_simulation_worker<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
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
			struct rcf_servicehandle<model::geo_simulation_worker<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
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
			struct rcf_serviceimpl<model::geo_simulation_worker<RcfSystem, RcfServiceHandle, RcfServant, Model, Graph> >
			{
				typedef RcfServant type;
			};

		}
	}
}

#endif