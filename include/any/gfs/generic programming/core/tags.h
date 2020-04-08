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
#ifndef ANYWAY_RCF_CORE_TAGS_H
#define ANYWAY_RCF_CORE_TAGS_H


namespace anyway
{ 
	namespace rcf
	{
		/// open source
		struct deltasoft_tag{};

		//
		struct single_node_tag{};
		struct multi_node_tag{};
		
		///
		struct gfs_name_node_tag{};
		struct gfs_task_node_tag{};
		struct gfs_data_node_tag{};

		/// gfs: master node
		struct gfsmaster_tag : single_node_tag, gfs_name_node_tag{};
		struct gfschunk_tag : multi_node_tag, gfs_task_node_tag, gfs_data_node_tag{};

		/// job: mapper & reducer
		struct job_mapper_tag : multi_node_tag, gfs_task_node_tag{};
		struct job_reducer_tag : multi_node_tag, gfs_task_node_tag{};
		struct job_tracker_tag : multi_node_tag, gfs_task_node_tag{};

		/// gfs strategies
		struct strategy_tag_master_file_allocate_robin{};
		struct strategy_tag_master_file_allocate_concensus{};
		struct strategy_tag_master_file_allocate_geolocation{};

		//
		struct strategy_tag_chunk_data_read_asfile{};	// rw: read/write
		struct strategy_tag_chunk_data_read_asfile_logged : strategy_tag_chunk_data_read_asfile{};	
		struct strategy_tag_chunk_data_read_asbyte{};

		///
		struct strategy_tag_chunk_data_write_asfile{};	// rw: read/write
		struct strategy_tag_chunk_data_write_asfile_logged : strategy_tag_chunk_data_write_asfile{};
		struct strategy_tag_chunk_data_write_asbyte{};

		// simulation tags
		struct simulation_mesh_tag{};
		struct simulation_mesh_hexa_tag : simulation_mesh_tag{};
		struct simulation_mesh_octa_tag : simulation_mesh_tag{};
		struct simulation_mesh_hexa_tetra_tag : simulation_mesh_hexa_tag{};

		struct simulation_matrix_solver_tag{};
		struct simulation_matrix_solver_supperlu_standalone_tag : simulation_matrix_solver_tag{};
		struct simulation_matrix_solver_supperlu_mpi_tag : simulation_matrix_solver_tag{};

		struct simulation_model_simulator_tag{};
		struct simulation_model_simulator_basin_tag : simulation_model_simulator_tag{};
		struct simulation_model_simulator_reservoir_tag : simulation_model_simulator_tag{};

		struct simulation_model_block_tag{};
		struct simulation_model_block_generic_tag : simulation_model_block_tag{};
		struct simulation_model_block_refined_tag : simulation_model_block_tag{};

		struct simulation_service_tag{};
		struct simulation_service_master_tag : simulation_service_tag{};
		struct simulation_service_worker_tag : simulation_service_tag{}; 

		struct simulation_graph_tag{};
		struct simulation_graph_in_topo_order_tag : public simulation_graph_tag{};

		struct simulation_graph_edge_type_tag{};
		struct simulation_graph_edge_type_data_tag : simulation_graph_edge_type_tag{};
		struct simulation_graph_edge_type_control_tag : simulation_graph_edge_type_tag{};

		struct simulation_graph_node_type_tag{};
		struct simulation_graph_node_type_loop_tag : simulation_graph_node_type_tag{};

		struct simulation_graph_node_run_tag{};
		struct simulation_graph_node_run_async_tag : simulation_graph_node_run_tag{};
		struct simulation_graph_node_run_sync_tag : simulation_graph_node_run_tag{};

		struct simulation_graph_node_run_sync_update_block_tag : simulation_graph_node_run_sync_tag{};
		struct simulation_graph_node_run_sync_update_model_tag : simulation_graph_node_run_sync_tag{};
		struct simulation_graph_node_run_sync_solve_marix_tag : simulation_graph_node_run_sync_tag{};

		struct simulation_matrix_tag{};
		struct simulation_matrix_finite_element_tag : simulation_matrix_tag{}; // finite element
	}
}

#endif