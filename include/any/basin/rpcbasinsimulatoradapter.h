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
#ifndef ANYBASIN_RPC_BASIN_SIMULATOR_ADAPTER_H
#define ANYBASIN_RPC_BASIN_SIMULATOR_ADAPTER_H

//
#include "anybasin.h"
#include "anyhyperbasinsimulator.h"

//
#include "any/gfs/anyservicebasic.h"
using namespace AnyRCF;

#include "any/gfs/generic programming/core/simulation_graph.h"
#include "any/gfs/generic programming/core/simulation_graph_node.h"
#include "any/gfs/generic programming/core/simulation_graph_node_container.h"
#include "any/gfs/generic programming/core/simulation_graph_edge.h"
#include "any/gfs/generic programming/core/simulation_graph_edge_container.h"

#include "any/gfs/generic programming/model/geo_simulation_graph.h"
#include "any/gfs/generic programming/model/geo_simulation_graph_node.h"
#include "any/gfs/generic programming/model/geo_simulation_graph_edge.h"
#include "any/gfs/generic programming/model/geo_simulation_model.h"
#include "any/gfs/generic programming/model/geo_simulation_solution.h"
#include "any/gfs/generic programming/model/geo_simulation_block.h"
#include "any/gfs/generic programming/model/geo_simulation_matrix.h"
using namespace anyway::rcf::model;

//
namespace AnyBasin
{
	namespace rpc
	{
		//
		// burial history
		struct rpc_basin_burial_simple_simultion_tag{};
		struct rpc_basin_burial_overpressure_simulation_tag{};

		// thermal history 
		struct rpc_basin_thermal_dumy_soultion_tag{};
		struct rpc_basin_thermal_steady_soultion_tag{};
		struct rpc_basin_thermal_transit_simple_soultion_tag {};
		//
		// migration & trap 
		//
		struct rpc_basin_trap_dumy_simulation_tag {};
		struct rpc_basin_trap_darcy_blackmodel_simulation_tag{};
		struct rpc_basin_trap_darcy_components_simulation_tag {};
		struct rpc_basin_trap_flowpath_simulation_tag{};
		
		struct rpc_basin_trap_3d_percolation_simulation_tag{};

		// forward
		class CRpcBasinSimulatorAdapter;
		class CRpcBasinMatrixAdapter;

		// basic
		typedef geo_simulation_block<CRpcBasinSimulatorAdapter, CAnyHyperMesh> RpcSolutionBlock;
		typedef geo_simulation_solution<CRpcBasinSimulatorAdapter, CAnyHyperMesh, RpcSolutionBlock> RpcModelSolution;
		typedef geo_simulation_model<CRpcBasinSimulatorAdapter, CAnyHyperMesh, RpcModelSolution, RpcSolutionBlock> RpcSimulationModel;
		typedef RpcSimulationModel::MeshContainer RpcMeshContainer;
		typedef RpcSimulationModel::BlockContainer RpcSolutionBlockContainer;

		//
		typedef geo_simulation_graph<SimulationJobNode, SimulationJobEdge, SimulationJobNodeContainer, SimulationJobEdgeContainer> RpcSimulationGraph;
		typedef geo_simulation_matrix<RpcSimulationModel, CRpcBasinMatrixAdapter> RpcSimulationMatrix;

		//
		class ANYBASIN_CLASS CRpcBasinSimulatorAdapter : public GeoSimulationSimulator
		{
		public:
			//
			CRpcBasinSimulatorAdapter();
			~CRpcBasinSimulatorAdapter();

		public:
			//
			void set_impl(CAnyHyperMesh *init_mesh, RpcMeshContainer &refined_meshes);

			//
			void create_model_file(RpcSimulationModel *model);
			void create_model_solutions(RpcSimulationModel *model);
			void create_model_blocks(RpcSimulationModel *model, RpcModelSolution *solution);
			void create_model_block_file(RpcSimulationModel *model, RpcModelSolution *solution);
			void create_model_block_memory(RpcSimulationModel *model, RpcModelSolution *solution);
			void get_model_simulator_data_dir(RpcSimulationModel *model, string &dir);
			void get_block_simulator_data_dir(RpcSolutionBlock *block, string &dir);
			void get_model_step_data_filepath(RpcSimulationModel *model, std::vector<string> &filepaths);
			void get_block_step_data_filepath(RpcSolutionBlock *block, std::vector<string> &filepaths);
			void get_block_allstep_data_filepath(RpcSolutionBlock *block, std::vector<string> &filepaths);

			//
			template<typename BurialTag, typename ThermalTag, typename traptag>
			static void create_simulation_graph(SimulationJobEdgeContainer &job_edges);

			// TODO:
			// to remove below clumsy code with visually define job flow
			// ...
			// against simple burial
			template<>
			static void create_simulation_graph<rpc_basin_burial_simple_simultion_tag,rpc_basin_thermal_dumy_soultion_tag,rpc_basin_trap_dumy_simulation_tag>(SimulationJobEdgeContainer &job_edges);

			template<>
			static void create_simulation_graph<rpc_basin_burial_simple_simultion_tag,rpc_basin_thermal_steady_soultion_tag,rpc_basin_trap_flowpath_simulation_tag>(SimulationJobEdgeContainer &job_edges);
			template<>
			static void create_simulation_graph<rpc_basin_burial_simple_simultion_tag,rpc_basin_thermal_steady_soultion_tag,rpc_basin_trap_3d_percolation_simulation_tag>(SimulationJobEdgeContainer &job_edges);

			template<>
			static void create_simulation_graph<rpc_basin_burial_simple_simultion_tag,rpc_basin_thermal_transit_simple_soultion_tag,rpc_basin_trap_flowpath_simulation_tag>(SimulationJobEdgeContainer &job_edges);

			template<>
			static void create_simulation_graph<rpc_basin_burial_simple_simultion_tag,rpc_basin_thermal_transit_simple_soultion_tag,rpc_basin_trap_3d_percolation_simulation_tag>(SimulationJobEdgeContainer &job_edges);

			// against overpressure burial
			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_steady_soultion_tag,rpc_basin_trap_darcy_blackmodel_simulation_tag>(SimulationJobEdgeContainer &job_edges);
			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_steady_soultion_tag,rpc_basin_trap_darcy_components_simulation_tag>(SimulationJobEdgeContainer &job_edges);

			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_steady_soultion_tag,rpc_basin_trap_flowpath_simulation_tag>(SimulationJobEdgeContainer &job_edges);
			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_steady_soultion_tag,rpc_basin_trap_3d_percolation_simulation_tag>(SimulationJobEdgeContainer &job_edges);


			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_transit_simple_soultion_tag,rpc_basin_trap_dumy_simulation_tag>(SimulationJobEdgeContainer &job_edges);
			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_transit_simple_soultion_tag,rpc_basin_trap_darcy_blackmodel_simulation_tag>(SimulationJobEdgeContainer &job_edges);
			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_transit_simple_soultion_tag,rpc_basin_trap_darcy_components_simulation_tag>(SimulationJobEdgeContainer &job_edges);
			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_transit_simple_soultion_tag,rpc_basin_trap_flowpath_simulation_tag>(SimulationJobEdgeContainer &job_edges);
			template<>
			static void create_simulation_graph<rpc_basin_burial_overpressure_simulation_tag,rpc_basin_thermal_transit_simple_soultion_tag,rpc_basin_trap_3d_percolation_simulation_tag>(SimulationJobEdgeContainer &job_edges);

		public:
			//
			static RpcSimulationGraph*DoCreateSimulationGraph(int nodecount, std::vector<char> &datachar);
			static RpcSimulationModel*DoCreateModel(std::string &model_file);
			static RpcSolutionBlock*DoCreateModelBlock(std::string &block_file);
			static SimulationJobNode *DoCreateRunner(CAnyHyperBasinSimulator *simulator, SimulationJobNode *running_node);
			static SimulationJobNode *DoCreateModelRunner(RpcSimulationModel *model, SimulationJobNode *running_node);
			static SimulationJobNode *DoCreateBlockRunner(RpcSolutionBlock *block, SimulationJobNode *running_node);
			static RpcSimulationMatrix*DoCreateMatrix(RpcSimulationModel *model, SimulationJobNode *running_node);
			static void DoUploadModelData(RpcSimulationModel *model, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			static void DoDownloadModelData(RpcSimulationModel *model, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			static void DoLoadModelCurrentStepData(RpcSimulationModel *model);
			static void DoSaveModelCurrentStepData(RpcSimulationModel *model);
			static void DoUploadBlockData(RpcSolutionBlock *block, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			static void DoDownloadBlockData(RpcSolutionBlock *block, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			static void DoLoadBlockCurrentStepData(RpcSolutionBlock *block);
			static void DoSaveBlockCurrentStepData(RpcSolutionBlock *block);

		public:
			CAnyHyperBasinSimulator *m_simulator_impl;
		};
	}

}


#endif