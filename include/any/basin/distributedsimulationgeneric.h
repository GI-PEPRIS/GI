/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYBASIN_DISTRIBUTED_SIMULATION_GENERIC_H__
#define __ANYBASIN_DISTRIBUTED_SIMULATION_GENERIC_H__

//
#include "boost\function.hpp"
using namespace boost;

//
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "any/base/loki/generic.h"
using namespace AnyBase;

//
namespace AnyBasin
{
		// concepts & traits & tags, to implement those concepts by generic programming 
		//
		//
		/*!
		* simulation concepts & traits
		**/
		template<class>
		struct simulation_model{};
		//template<class>
		//struct simulation_solution{};
		template<class>
		struct simulation_soluiton_block{};
		template<class>
		struct simulation_job{};
		template<class>
		struct simulation_job_block{};
		template<class>
		struct simulation_stage{};

		/*!
		* execution concepts
		**/
		template<class> // job scheduler/ job block schedluer etc
		struct simulation_scheduler{};
		template<class> // for one machine
		struct simulation_worker{};
		template<class>	// for one process
		struct simulation_executor{};
		template<class>	// for one thread
		struct simulation_task{};

		// for the usage of anybase\loki\generic etc meta calling, such as IsSameType, SuperSubclass etc
		//
		
		// traits related to geological model to be simulated
		/*!
		* distributed meshes against different solutions against kinds of geological histories 
		**/
		struct hyper_model_mesh_tag
		{
			std::string m_model_mesh_tag; 
			hyper_model_mesh_tag(){	m_model_mesh_tag = "unknown";}
		};
		struct hexa_tetra_hyper_model_mesh_tag : public hyper_model_mesh_tag
		{
			hexa_tetra_hyper_model_mesh_tag(){ m_model_mesh_tag = "hexa_tetra_hyper_model_mesh_tag";	}
		};

		// traits related to simulation schema - solution
		//
		/*!
		*
		**/
		struct solution_block_tag
		{
			std::string m_solution_block_tag;
			solution_block_tag(){m_solution_block_tag = "unknown";}
		};
		struct solution_generic_block_tag : public solution_block_tag
		{
			solution_generic_block_tag(){m_solution_block_tag="solution_generic_block_tag";}
		};
		struct solution_refined_block_tag : public solution_block_tag
		{
			solution_refined_block_tag(){m_solution_block_tag="solution_refined_block_tag";}
		};

		/*!
		*
		**/
		struct model_simulation_tag
		{
			std::string m_simulation_task_tag;
			model_simulation_tag(){m_simulation_task_tag = "unknown";}
		};
		
		//
		//
		// ...

		// burial history
		struct basin_burial_simple_simultion_tag : public model_simulation_tag
		{
			basin_burial_simple_simultion_tag(){m_simulation_task_tag = "basin_burial_simple_simultion_tag";}
		};
		struct basin_burial_overpressure_simulation_tag : public model_simulation_tag
		{
			basin_burial_overpressure_simulation_tag(){m_simulation_task_tag = "basin_overpressure_3d_onephase_simulation_tag";}
		};

		// thermal history 
		struct basin_thermal_dumy_soultion_tag : public model_simulation_tag
		{
			basin_thermal_dumy_soultion_tag(){m_simulation_task_tag = "basin_thermal_dumy_soultion_tag";}
		};
		struct basin_thermal_steady_soultion_tag : public model_simulation_tag
		{
			basin_thermal_steady_soultion_tag(){m_simulation_task_tag = "basin_thermal_steady_soultion_tag";}
		};
		struct basin_thermal_transit_simple_soultion_tag : public model_simulation_tag
		{
			basin_thermal_transit_simple_soultion_tag(){m_simulation_task_tag = "basin_thermal_transit_simple_soultion_tag";}
		};

		//
		// migration & trap 
		//
		struct basin_trap_dumy_simulation_tag : public model_simulation_tag
		{
			basin_trap_dumy_simulation_tag(){m_simulation_task_tag = "basin_trap_dumy_simulation_tag";}
		};
		struct basin_trap_darcy_blackmodel_simulation_tag : public model_simulation_tag
		{
			basin_trap_darcy_blackmodel_simulation_tag(){m_simulation_task_tag = "basin_trap_darcy_blackmodel_simulation_tag";}
		};
		struct basin_trap_darcy_components_simulation_tag : public model_simulation_tag
		{
			basin_trap_darcy_components_simulation_tag(){m_simulation_task_tag = "basin_trap_darcy_components_simulation_tag";}
		};
		struct basin_trap_flowpath_simulation_tag : public model_simulation_tag
		{
			basin_trap_flowpath_simulation_tag(){m_simulation_task_tag = "basin_trap_flowpath_simulation_tag";}
		};
		struct basin_trap_3d_percolation_simulation_tag : public model_simulation_tag
		{
			basin_trap_3d_percolation_simulation_tag(){m_simulation_task_tag = "basin_trap_3d_percolation_simulation_tag";}
		};

		//
		//由生烃动力学参数决定黑油、多组分模型
		//

		///////////////////////////////////////////////////////////////////////////
		// traits related to job and its running block
		/*!
		* key points against one concrete solution
		**/
		struct job_node_function_tag
		{
			std::string m_job_node_function_tag;
			job_node_function_tag(){m_job_node_function_tag = "unknown";}
		};

		// job function: recover max depth
		struct job_node_recover_max_depth_tag : public job_node_function_tag
		{
			job_node_recover_max_depth_tag(){m_job_node_function_tag = "job_node_recover_max_depth_tag";}
		};

		// job functions: before simulation
		struct job_node_simulation_before_prepare_tag : public job_node_function_tag
		{
			job_node_simulation_before_prepare_tag(){m_job_node_function_tag = "job_node_simulation_before_prepare_tag";}
		};
		struct job_node_simulation_before_prepare1_tag : public job_node_function_tag
		{
			job_node_simulation_before_prepare1_tag(){m_job_node_function_tag = "job_node_simulation_before_prepare1_tag";}
		};
		struct job_node_simulation_before_prepare2_tag : public job_node_function_tag
		{
			job_node_simulation_before_prepare2_tag(){m_job_node_function_tag = "job_node_simulation_before_prepare2_tag";}
		};
		struct job_node_simulation_before_prepare3_tag : public job_node_function_tag
		{
			job_node_simulation_before_prepare3_tag(){m_job_node_function_tag = "job_node_simulation_before_prepare3_tag";}
		};
		struct job_node_simulation_before_prepare4_tag : public job_node_function_tag
		{
			job_node_simulation_before_prepare4_tag(){m_job_node_function_tag = "job_node_simulation_before_prepare4_tag";}
		};
		struct job_node_simulation_before_prepare5_tag : public job_node_function_tag
		{
			job_node_simulation_before_prepare5_tag(){m_job_node_function_tag = "job_node_simulation_before_prepare5_tag";}
		};
		struct job_node_simulation_before_prepare6_tag : public job_node_function_tag
		{
			job_node_simulation_before_prepare6_tag(){m_job_node_function_tag = "job_node_simulation_before_prepare6_tag";}
		};

		// job functions: for one step simulation
		struct job_node_simulation_begin_tag : public job_node_function_tag
		{
			job_node_simulation_begin_tag(){m_job_node_function_tag = "job_node_simulation_begin_tag";}
		};
		struct job_node_simulation_exchange_block2model_tag : public job_node_function_tag
		{
			job_node_simulation_exchange_block2model_tag(){m_job_node_function_tag = "job_node_simulation_exchange_block2model_tag";}
		};
		struct job_node_simulation_exchange_model2block_tag : public job_node_function_tag
		{
			job_node_simulation_exchange_model2block_tag(){m_job_node_function_tag = "job_node_simulation_exchange_model2block_tag";}
		};
		struct job_node_simulation_isover_tag : public job_node_function_tag
		{
			job_node_simulation_isover_tag(){m_job_node_function_tag = "job_node_simulation_isover_tag";}
		};
		struct job_node_simulation_sourcerock_tag : public job_node_function_tag
		{
			job_node_simulation_sourcerock_tag(){m_job_node_function_tag = "job_node_simulation_sourcerock_tag";}
		};
		struct job_node_simulation_percolation_tag : public job_node_function_tag
		{
			job_node_simulation_percolation_tag(){m_job_node_function_tag = "job_node_simulation_percolation_tag";}
		};

		//
		struct job_node_simulation_onestep_prepare_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_prepare_tag(){m_job_node_function_tag = "job_node_simulation_onestep_prepare_tag";}
		};
		struct job_node_simulation_onestep_end_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_end_tag(){m_job_node_function_tag = "job_node_simulation_onestep_end_tag";}
		};
		struct job_node_simulation_onestep_isover_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_isover_tag(){m_job_node_function_tag = "job_node_simulation_onestep_isover_tag";}
		};

		// burial against overpressure
		struct job_node_simulation_onestep_burial_overpressure_prepare_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_prepare_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_prepare_tag";}
		};
		struct job_node_simulation_onestep_burial_overpressure_fe_prepare_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_fe_prepare_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_fe_prepare_tag";}
		};
		struct job_node_simulation_onestep_burial_overpressure_fe_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_fe_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_fe_tag";}
		};
		struct job_node_simulation_onestep_burial_overpressure_threephase_fe_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_threephase_fe_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_threephase_fe_tag";}
		};
		struct job_node_simulation_onestep_burial_overpressure_saturationwater_fe_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_saturationwater_fe_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_saturationwater_fe_tag";}
		};
		struct job_node_simulation_onestep_burial_overpressure_saturationoil_fe_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_saturationoil_fe_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_saturationoil_fe_tag";}
		};
		struct job_node_simulation_onestep_burial_overpressure_fe_isover_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_fe_isover_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_fe_isover_tag";}
		};
		struct job_node_simulation_onestep_burial_overpressure_done_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_burial_overpressure_done_tag(){m_job_node_function_tag = "job_node_simulation_onestep_burial_overpressure_done_tag";}
		};

		// thermal against transit
		struct job_node_simulation_onestep_thermal_transit_prepare_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_thermal_transit_prepare_tag(){m_job_node_function_tag = "job_node_simulation_onestep_thermal_transit_prepare_tag";}
		};
		struct job_node_simulation_onestep_thermal_transit_fe_prepare_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_thermal_transit_fe_prepare_tag(){m_job_node_function_tag = "job_node_simulation_onestep_thermal_transit_fe_prepare_tag";}
		};
		struct job_node_simulation_onestep_thermal_transit_fe_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_thermal_transit_fe_tag(){m_job_node_function_tag = "job_node_simulation_onestep_thermal_transit_fe_tag";}
		};
		struct job_node_simulation_onestep_thermal_transit_fe_isover_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_thermal_transit_fe_isover_tag(){m_job_node_function_tag = "job_node_simulation_onestep_thermal_transit_fe_isover_tag";}
		};
		struct job_node_simulation_onestep_thermal_transit_done_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_thermal_transit_done_tag(){m_job_node_function_tag = "job_node_simulation_onestep_thermal_transit_done_tag";}
		};
		struct job_node_simulation_onestep_pressure_thermal_fe_isover_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_pressure_thermal_fe_isover_tag(){m_job_node_function_tag = "job_node_simulation_onestep_pressure_thermal_fe_isover_tag";}
		};

		// thermal against steady mode
		struct job_node_simulation_onestep_thermal_steady_tag : public job_node_function_tag
		{
			job_node_simulation_onestep_thermal_steady_tag(){m_job_node_function_tag = "job_node_simulation_onestep_thermal_steady_tag";}
		};


		/*!
		* differentiate above functions belong to which kind of simulator
		**/
		struct job_node_run_tag
		{
			std::string m_job_node_run_tag;
			job_node_run_tag(){m_job_node_run_tag = "unknown";}
		};
		// job block
		struct job_block_async_run_tag : public job_node_run_tag	
		{
			job_block_async_run_tag(){m_job_node_run_tag = "block_async_run_tag";}
		};
		struct job_block_sync_run_tag : public job_node_run_tag 
		{
			job_block_sync_run_tag(){m_job_node_run_tag = "job_block_sync_run_tag";}
		};
		
		// solution block
		struct job_solution_async_run_tag : public job_node_run_tag 
		{
			job_solution_async_run_tag(){m_job_node_run_tag = "job_solution_async_run_tag";}
		};
		struct job_solution_sync_run_tag : public job_node_run_tag 
		{
			job_solution_sync_run_tag(){m_job_node_run_tag = "job_solution_sync_run_tag";}
		};

		// model block
		struct job_model_sync_run_tag : public job_node_run_tag 
		{
			job_model_sync_run_tag(){m_job_node_run_tag = "job_model_sync_run_tag";}
		};
		struct job_model_async_run_tag : public job_node_run_tag 
		{
			job_model_async_run_tag(){m_job_node_run_tag = "job_model_async_run_tag";}
		};

		//
		// traits related matrix and its calculation
		/*!
		*
		**/
		struct matrix_storage_tag
		{
			std::string m_maxtrix_storage_tag;
			matrix_storage_tag(){m_maxtrix_storage_tag = "unknown";}
		};
		struct matrix_csr_local_storage_tag :public matrix_storage_tag
		{
			matrix_csr_local_storage_tag(){m_maxtrix_storage_tag = "matrix_csr_local_storage_tag";}
		};
		struct matrix_csr_distributed_storage_tag :public matrix_storage_tag
		{
			matrix_csr_distributed_storage_tag(){m_maxtrix_storage_tag = "matrix_csr_distributed_storage_tag";}
		};

		/*!
		*
		**/
		struct matrix_solution_tag
		{
			std::string m_matrix_solution_tag;
			matrix_solution_tag(){m_matrix_solution_tag = "unknown";}
		};
		struct thermal_finite_element_matrix_tag : public matrix_solution_tag
		{
			thermal_finite_element_matrix_tag(){m_matrix_solution_tag = "thermal_finite_element_matrix_tag";}
		};
		struct overpressure_finite_element_matrix_tag : public matrix_solution_tag
		{
			overpressure_finite_element_matrix_tag(){m_matrix_solution_tag = "overpressure_finite_element_matrix_tag";}
		};
		struct property_finite_element_matrix_tag : public matrix_solution_tag
		{
			property_finite_element_matrix_tag(){m_matrix_solution_tag = "property_finite_element_matrix_tag";}
		};

		/*!
		*
		**/
		struct matrix_resolve_tag
		{
			std::string m_matrix_resolve_tag;
			matrix_resolve_tag(){m_matrix_resolve_tag = "unknown";}
		};
		struct supper_lu_standalone_resolve_tag : public matrix_resolve_tag
		{
			supper_lu_standalone_resolve_tag(){m_matrix_resolve_tag = "thermal_finite_element_matrix_tag";}
		};
		struct supper_lu_threads_resolve_tag : public matrix_resolve_tag
		{
			supper_lu_threads_resolve_tag(){m_matrix_resolve_tag = "supper_lu_threads_resolve_tag";}
		};
		struct supper_lu_shared_memory_resolve_tag : public matrix_resolve_tag
		{
			supper_lu_shared_memory_resolve_tag(){m_matrix_resolve_tag = "supper_lu_shared_memory_resolve_tag";}
		};

	//
	//against one or more machines, namely, distributed environment
	//
	/*! 
	* geological model
	**/
	struct DistributedModel : public CGeoRect<double>
	{
		// tedra etc
		std::string m_distributed_model_mesh_tag;

		// MPI machine id
		long m_rank_id;
		long m_model_idx;

		// model data 
		// 一个区域的模拟方案（SOLUTION）对应一个及以上MESH CHUNKS
		// MESH CHUNK的组织，区域下的HORIZONS？
		// 缺省本地单机版对应一个CHUNK FILE
		//
		std::string m_mesh_distributed_info_file;	// xxxx.mesh.info
		std::vector<std::string> m_mesh_distributed_chunk_files; // xxxx.mesh.chunk // in future, to follow *.afs specification specified by ANYRCF

		// matrix data
		// 按行组织的稀疏矩阵，事先计算需要的中间计算结果？
		// 分模拟阶段
		std::string m_matrix_distributed_info_file; //xxxx.matrix.info
		std::vector<std::string> m_matrix_distributed_chunk_files; // xxxx(stage(x)).matrix.chunk

		// simulation data 
		// 与MODEL DATA对应，但是对应不同的模拟地质年代
		// ...
		std::string m_simulation_distributed_info_file; //xxxx.simulation.info
		std::vector<std::string> m_simulation_distributed_chunk_files; // xxxx(stage(x)).simulation.chunk
	};

	// against the initial hyerp mesh or simulator of current basin simulation
	template<typename HyperMesh, typename Simulator, typename MeshTag>
	struct HyperModel : public DistributedModel, public MeshTag
	{
		// which distributed mesh
		Simulator *m_host_model_simulator; // == hyper mesh
		std::vector<HyperMesh*> m_model_refined_hyper_meshes;

		//
		HyperModel() : m_host_model_simulator(0)
		{
			MeshTag meshtag;
			m_distributed_model_mesh_tag = meshtag.m_model_mesh_tag;
		}
	};

	/*!
	* one distributed mesh against one kind of solution
	**/
	struct DistributedSolution : public CGeoRect<double>
	{
		// generic, refined etc
		std::string m_distributed_soluiton_block_tag;

		// MPI machine id
		long m_rank_id;
		long m_solution_idx;
	};

	//对应MODEL建模时的分块
	template<typename Simulator, typename SolutionBlockTag>
	struct ModelSolution : public DistributedSolution, private SolutionBlockTag
	{	
		// which block simulator
		Simulator *m_parent_model_simulator;
		Simulator *m_host_solution_simulator;

		//
		ModelSolution()
		{
			SolutionBlockTag blocktag;
			m_distributed_soluiton_block_tag = blocktag.m_solution_block_tag;
		}
	};
	typedef std::vector<DistributedSolution *> ModelSolutionContainer;
	
	/*!
	*
	**/
	struct DistributedBlock : public CGeoRect<double>
	{
		// generic, refined etc
		std::string m_distributed_job_block_tag;
		std::string m_distributed_job_node_function_tag;
		std::string m_distributed_job_node_run_tag;

		// MPI machine id
		long m_rank_id;

		//
		long m_solution_idx;
		long m_block_idx;

		virtual bool do_job(){return false;}
	};

	template<typename Simulator>
	struct SolutionBlock : public DistributedBlock
	{
		// which block simulator
		Simulator *m_host_job_block_simulator;
		Simulator *m_parent_solution_block_simulator; // dumy
		Simulator *m_parent_model_simulator;
	};

	// block object & idx vector
	typedef std::vector<DistributedBlock*> SolutionBlockContainer;

	/*!
	*
	**/
	enum JobState
	{
		JS_Ready	= 0,
		JS_Run		= 1,
		JS_Wait		= 1 << 1,
		JS_Done		= 1 << 2, // also as mark bits
	};
	struct DistributedJob
	{
		std::string m_distributed_job_node_function_tag;
		std::string m_distributed_job_node_run_tag;

		// MPI machine id
		long m_rank_id;

		// job graph
		long m_solution_idx;
		long m_job_idx;

		// job state 
		unsigned long m_job_state;

		// this job node repeated until the job meets condition
		int m_is_need_repeated;
		long m_repeat_from_job_idx;

		//
		DistributedJob()
		{
			m_is_need_repeated = false;
			m_repeat_from_job_idx = -1;
			m_job_state = JS_Ready;
		}
	};
	template<typename JobFunctionTag,typename JobRunTag>
	struct SolutionJob : public DistributedJob, private JobFunctionTag, private JobRunTag
	{
		//
		SolutionJob()
		{
			JobFunctionTag functiontag;
			m_distributed_job_node_function_tag = functiontag.m_job_node_function_tag;

			JobRunTag runtag;
			m_distributed_job_node_run_tag = runtag.m_job_node_run_tag;
		}
	};
	typedef std::vector<DistributedJob*> SolutionJobContainer;
	typedef std::vector<std::pair<DistributedJob*,DistributedJob*> > SolutionJobGraph; // not only local memory, but also as distributed shared memory to update graph's state

	template<typename Simulator, typename Signature, typename JobFunctionTag, typename JobRunTag>
	struct JobBlock : public DistributedBlock, private JobFunctionTag, private JobRunTag
	{
		// which block simulator
		Simulator *m_host_block_simulator;

		//
		long m_job_idx;

		//
		typedef boost::function<Signature> BlockFunction;
		BlockFunction m_block_function;

		//
		JobBlock() : m_host_block_simulator(0), m_block_function(0)
		{
			JobFunctionTag functiontag;
			m_distributed_job_node_function_tag = functiontag.m_job_node_function_tag;

			JobRunTag runtag;
			m_distributed_job_node_run_tag = runtag.m_job_node_run_tag;
		}

		bool do_job()
		{
			return m_block_function();
		}
	};
	// block object & idx vector
	typedef std::vector<DistributedBlock*> JobBlockContainer;

	/*!
	* only local not distributed for stage
	*/
	struct DistributedStage
	{
		// meta
		std::string m_job_node_function_tag;
		std::string m_job_node_run_tag;

		// MPI machine id
		long m_rank_id;

		// thread id
		long m_task_idx;
		long m_block_idx;
	};
	template<typename Simulator, typename Signature, typename JobFunctionTag, typename JobRunTag>
	struct BlockStage : public DistributedStage, private JobFunctionTag, private JobRunTag
	{
		typedef boost::function<Signature> StageFunction;

		// which block simulator
		Simulator *m_block_simulator;
		// which function
		StageFunction m_stage_function;

		// which layer or geological event
		int m_which_layer;
		// which layer
		int m_which_horizon;

		BlockStage() : m_block_simulator(0), m_stage_function(0)
		{
			JobFunctionTag functiontag;
			m_job_node_function_tag = functiontag.m_job_node_function_tag;

			JobRunTag runtag;
			m_job_node_run_tag = runtag.m_job_node_run_tag;
		}
	};
	typedef std::vector<DistributedStage *> BlockStageContainer;

	//
	// against one executor deployed a machine
	//
}
#endif