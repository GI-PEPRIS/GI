/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef ANYRCF_RPC_GEO_SIMULATION_SCHEDULER_H
#define ANYRCF_RPC_GEO_SIMULATION_SCHEDULER_H

// refer to EXPORT & IMPORT
#include "anyrcf.h"

//
#include "any/base/anystl.h"

// traits
#include "generic programming/core/tags.h"
#include "generic programming/core/rcf_serviceimpl.h"
#include "generic programming/core/rcf_servicehandle.h"

#include "generic programming/core/simulation_simulator.h"
#include "generic programming/core/simulation_mesh.h"
#include "generic programming/core/simulation_mesh_container.h"
#include "generic programming/core/simulation_solution.h"
#include "generic programming/core/simulation_solution_container.h"
#include "generic programming/core/simulation_block.h"
#include "generic programming/core/simulation_block_container.h"

#include "generic programming/core/simulation_matrix.h"

#include "generic programming/core/simulation_graph.h"
#include "generic programming/core/simulation_graph_node.h"
#include "generic programming/core/simulation_graph_node_container.h"
#include "generic programming/core/simulation_graph_edge.h"
#include "generic programming/core/simulation_graph_edge_container.h"

#include "generic programming/dimension/start_service.h"

using namespace anyway::rcf;

//
namespace AnyRCF
{
	template
		<
		typename Model,
		typename Graph,
		typename Matrix,
		typename Master,
		typename Worker
		>
	class ANYRCF_CLASS CGeoSimulationScheduler
	{
		// model
		typedef typename simulation_simulator<Model>::type ModelSimulator;

		typedef typename simulation_mesh<Model>::type ModelMesh;
		typedef typename simulation_mesh_container<Model>::type ModelMeshContainer;

		typedef typename simulation_solution<Model>::type ModelSolution;
		typedef typename simulation_block<Model>::type ModelBlock;

		typedef typename simulation_matrix<Matrix>::type ModelMatrix;
		//typedef typename simulation_matrix_solver<Matrix>::type ModelMatrixSolver;

		// service
		typedef typename rcf_servicehandle<Master>::type MasterServiceHandle;
		typedef typename rcf_servicehandle<Worker>::type WorkerServiceHandle;
		typedef std::vector<Worker*> WorkerContainer;

		// graph
		typedef typename simulation_graph_node<Graph>::type GraphNode;
		typedef typename simulation_graph_edge<Graph>::type GraphEdge;
		typedef typename simulation_graph_node_container<Graph>::type GraphNodeContainer;
		typedef typename simulation_graph_edge_container<Graph>::type GraphEdgeContainer;


	public:
		//
		CGeoSimulationScheduler(){

			// concept/traits check
			//ModelSimulator *simulator = new ModelSimulator;
			//ModelMesh *mesh = new ModelMesh;
			//ModelMeshContainer meshes;
			//meshes.push_back(mesh);

			//ModelSolution *solution = new ModelSolution;
			//ModelBlock *block = new ModelBlock;

			//ModelMatrix *matrix = new ModelMatrix;
			//MasterServiceHandle service_handle;
			//WorkerServiceHandle worker_handle;

			//GraphNode *node = new geo_simulation_graph_node<ModelSimulator, bool(), simulation_graph_node_type_loop_tag, simulation_graph_node_run_sync_solve_marix_tag>;
			//GraphEdge *edge = new geo_simulation_graph_edge<GraphNode,GraphNode>;

			//GraphNodeContainer nodes;
			//nodes.push_back(node);

			//GraphEdgeContainer edges;
			//edges.push_back(edge);
			m_master = 0;
			m_model = 0;
			m_graph = 0;
		}
		~CGeoSimulationScheduler()
		{
			if(m_master){
				delete m_master;
			}
			for(int i = 0; i < m_workers.size(); i++) {
				delete m_workers[i];
			}
		}

		
	public:
		// deploy services
		bool register_master(MasterServiceHandle &service_handle){
			if(!(service_handle.m_servicetype & ST_Simulation_Master)){
				return false;
			}

			if(m_master){
				delete m_master;
			}
			m_master = new Master;
			return m_master->depoly_master(service_handle);
		}
		void register_workers(std::vector<WorkerServiceHandle> &worker_handles){
			
			// start service consider start failure
			for(int i = 0; i < worker_handles.size(); i++) {
				Worker *one_worker = new Worker;
				one_worker->depoly_worker(worker_handles[i]);
				m_workers.push_back(one_worker);
			}
		}

		// deploy geo/data model
		void deploy_model(ModelMesh *whole_mesh, ModelMeshContainer &refined_meshes){
			if(m_model){
				delete m_model;
			}

			m_model = new Model;
			m_model->create_model(whole_mesh, refined_meshes);

			// pass to master
			assert(m_master);
			m_master->deploy_model(m_model);

			// pass to worker
			// firstly, to clear existed
			for(int i = 0; i < m_workers.size(); i++){
				m_workers[i]->clear_model_blocks(m_model);							
			}		
			// secondly, assign blocks in robin way
			update_worker_blocks(0);
		}

		// create simulation graph
		void deploy_graph(GraphEdgeContainer &job_edges)
		{
			if(m_graph){
				delete m_graph;
			}
			m_graph = new Graph;
			m_graph->create_simulation_graph(job_edges);

			assert(m_master);
			m_master->deploy_graph(m_graph);

			//
			for(int i = 0; i < m_workers.size(); i++){
				m_workers[i]->update_simulation_graph(m_graph);							
			}
		}

		//
		// simply schedule those workers driven by graph status
		void run_simulation_in_fairway() {

			// start all workers and during worker simulation, each worker callback/notify its latest job node idx
			start_workers();

			// until each worker has done
			while(!m_graph->is_master_done()) {
				// which is the latest rabbit and the slowest tortoise
				//
				long tortoise_job_idx = 0x7FFFFFFF;
				long rabbit_job_idx = -0x7FFFFFFF;
				for(int i = 0; i < m_workers.size(); i++) {
					long job_idx = m_workers[i]->get_running_node_idx(); // running or just done?
					rabbit_job_idx = rabbit_job_idx < job_idx ? job_idx : rabbit_job_idx;
					tortoise_job_idx = tortoise_job_idx > job_idx ? job_idx : tortoise_job_idx;
				}

				m_master->update_master_graph(rabbit_job_idx, tortoise_job_idx);
				m_graph->set_master_rabbit_idx(rabbit_job_idx);
				m_graph->set_master_tortoise_idx(tortoise_job_idx);

				// position to running node
				GraphNode *rabbit_node = m_graph->get_master_rabbit_node();
				if(!rabbit_node)
					continue;
				//
				if(rabbit_node->m_is_sync_node)
				{
					// rabbits wait tortoises
					if(!m_graph->is_master_meetwith())
						continue;
					// blocked here until all reach the same node
					if(rabbit_node->m_is_need_update_model) 
					{
						// firstly update local/scheduler model
						download_worker_blocks(rabbit_node);
						// also down load blocks locally, namely, update m_model???
						m_master->update_master_model(m_model, rabbit_node);
					}
					// here, should be blocked until master has done, mainly solve matrix as whole
					bool needloop = m_master->run_simulation(rabbit_node);
					if(rabbit_node->m_is_need_update_solution_block) 
					{
						m_master->download_master_model(m_model, rabbit_node);
						update_worker_blocks(rabbit_node);
					}
					if(rabbit_node->m_is_loop_node && needloop)
					{
						m_graph->reset_master_node_for_loop();
						for(int i = 0; i < m_workers.size(); i++) 
							m_workers[i]->update_simulation_graph(m_graph);			
					}
					else
						resume_workers(rabbit_node);
				}
			}	
			download_worker_blocks(0);	
		}

		void update_worker_blocks(GraphNode *running_node) {

			// in robin way to assign blocks to each worker service
			int solution_number = m_model->get_solution_number();
			int totalblockcount = 0;
			for(int i = 0; i < solution_number; i++)
			{
				ModelSolution *solution = m_model->get_solution(i);
				int block_number = solution->get_block_number();
				totalblockcount += block_number;
			}
			if(totalblockcount < m_workers.size())
				m_workers.resize(totalblockcount);
			int whichworker = 0;
			for(int i = 0; i < solution_number; i++) {

				ModelSolution *solution = m_model->get_solution(i);
				int block_number = solution->get_block_number();
				for(int j = 0; j < block_number; j++) {
					whichworker = (whichworker + 1) % m_workers.size();
					m_workers[whichworker]->update_block(m_model, solution->get_block(j), running_node);
				}
			}
		}

		void download_worker_blocks(GraphNode *running_node) {

			// in robin way to assign blocks to each worker service
			int solution_number = m_model->get_solution_number();
			int whichworker = 0;
			for(int i = 0; i < solution_number; i++) {

				ModelSolution *solution = m_model->get_solution(i);
				int block_number = solution->get_block_number();
				for(int j = 0; j < block_number; j++) {
					whichworker = (whichworker + 1) % m_workers.size();
					m_workers[whichworker]->download_block(m_model, solution->get_block(j), running_node);
				}
			}
		}

		void start_workers(){
			for(int i = 0; i < m_workers.size(); i++) {
				m_workers[i]->run_simulation();
			}				
		}

		void resume_workers(GraphNode* sync_node){
			for(int i = 0; i < m_workers.size(); i++) {
				m_workers[i]->resume_simulation(sync_node->m_job_node_idx);
			}	
		}

	public:
		//
		Master *m_master;
		WorkerContainer m_workers;
		
		// for data preparation
		Model *m_model;
		// for running
		Graph *m_graph;
	};

}

#endif