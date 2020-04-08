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
#ifndef __ANYBASIN_DISTRIBUTED_SIMULATION_SOLUTION_H__
#define __ANYBASIN_DISTRIBUTED_SIMULATION_SOLUTION_H__

//
#include "anybasin.h"
#include "distributedsimulationgeneric.h"
#include "anyhyperbasinbasic.h"

//
namespace AnyBasin
{
	// forward class
	class CAnyHyperBasinSimulator;
	/*!
	* 
	**/
	class ANYBASIN_CLASS CDistributedSimulationSolution : public DistributedSolution
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CDistributedSimulationSolution(){m_host_simulation_solution_impl=0;m_jobblockrows=-1;m_jobblockcols=-1;}
		~CDistributedSimulationSolution(){}

	public:
		//
		//
		//
		/*!
		* divided int block distributed files and 
		**/
		template<typename Simulator>
		void DeployBlock(int jobblockrows, int jobblockcols);
		template<>
		void DeployBlock<CAnyHyperBasinSimulator>(int jobblockrows, int jobblockcols);

		/*!
		* 
		**/
		template<typename Simulator>
		void DeployResultBlock(int jobblockrows, int jobblockcols);
		template<>
		void DeployResultBlock<CAnyHyperBasinSimulator>(int jobblockrows, int jobblockcols);

		/*!
		* update divided block date to origin
		**/
		template<typename Simulator>
		void UpdateBlockToSimulator();
		template<>
		void UpdateBlockToSimulator<CAnyHyperBasinSimulator>();

		/*!
		* 
		**/
		template<typename Simulator>
		void GetBlockVertexesSimulated(int offseti, int offsetj, int offsetk, std::vector<Vertex3D*> &vertexs, int bottomortop, int colorsource);
		template<>
		void GetBlockVertexesSimulated<CAnyHyperBasinSimulator>(int offseti, int offsetj, int offsetk, std::vector<Vertex3D*> &vertexs, int bottomortop, int colorsource);
		
		//
		//
		//
		/*!
		*
		**/
		template<typename BurialTag, typename ThermalTag, typename TrapTag>
		void Solution2Job();

		// against simple burial
		template<>
		void Solution2Job<basin_burial_simple_simultion_tag,basin_thermal_dumy_soultion_tag,basin_trap_dumy_simulation_tag>();

		template<>
		void Solution2Job<basin_burial_simple_simultion_tag,basin_thermal_steady_soultion_tag,basin_trap_flowpath_simulation_tag>();
		template<>
		void Solution2Job<basin_burial_simple_simultion_tag,basin_thermal_steady_soultion_tag,basin_trap_3d_percolation_simulation_tag>();

		template<>
		void Solution2Job<basin_burial_simple_simultion_tag,basin_thermal_transit_simple_soultion_tag,basin_trap_flowpath_simulation_tag>();

		template<>
		void Solution2Job<basin_burial_simple_simultion_tag,basin_thermal_transit_simple_soultion_tag,basin_trap_3d_percolation_simulation_tag>();

		// against overpressure burial
		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_steady_soultion_tag,basin_trap_darcy_blackmodel_simulation_tag>();
		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_steady_soultion_tag,basin_trap_darcy_components_simulation_tag>();

		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_steady_soultion_tag,basin_trap_flowpath_simulation_tag>();
		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_steady_soultion_tag,basin_trap_3d_percolation_simulation_tag>();


		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_transit_simple_soultion_tag,basin_trap_dumy_simulation_tag>();
		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_transit_simple_soultion_tag,basin_trap_darcy_blackmodel_simulation_tag>();
		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_transit_simple_soultion_tag,basin_trap_darcy_components_simulation_tag>();
		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_transit_simple_soultion_tag,basin_trap_flowpath_simulation_tag>();
		template<>
		void Solution2Job<basin_burial_overpressure_simulation_tag,basin_thermal_transit_simple_soultion_tag,basin_trap_3d_percolation_simulation_tag>();

		//
	    // rpc interfaces
		//
		int get_job_number()
		{
			return m_job_blocks_in_topo_order.size();
		}
		DistributedJob *get_job(int order)
		{
			return m_job_blocks_in_topo_order[order];
		}
		DistributedJob *get_ready_for_running_job();
		void reset_for_next_job(bool needloop);

		//
		//
		//
		/*!
		*
		**/
		bool SaveSimulationData(CAnyHyperBasinSimulator *curhypermesh);
		bool LoadSimulationData(CAnyHyperBasinSimulator *curhypermesh);
		void CreateDir(string filepath);

	public:
		// host simulator etc
		DistributedSolution *m_host_simulation_solution_impl;
		// blocks and their simulators
		SolutionBlockContainer m_solution_job_block_prototypes;
		// job schema for run
		SolutionJobGraph m_prototypes_in_job_graph;
		// jobs in topo order
		SolutionJobContainer m_job_blocks_in_topo_order;

		int m_jobblockrows;
		int m_jobblockcols;
	};
}


#endif