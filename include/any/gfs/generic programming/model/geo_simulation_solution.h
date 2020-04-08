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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_SOLUTION_SIMULATOR_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_SOLUTION_SIMULATOR_H

#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

#include "generic programming/core/tag.h"
#include "generic programming/core/tags.h"
#include "generic programming/core/simulation_solution_container.h"

namespace anyway
{ 
	namespace rcf
	{
		//
		namespace model
		{
			//
			//
			template
				<
				typename Simulator,
				typename Mesh,
				typename Block,
				typename ParentSolution = GeoSimulationSolution
				>
			class geo_simulation_solution : public ParentSolution
			{
				typedef typename simulation_block_container<Block>::type BlockContainer;

			public:
				//
				explicit inline geo_simulation_solution()
				{
				}
				~geo_simulation_solution()
				{
					if(m_host_solution_simulator) delete m_host_solution_simulator;
					clear_blocks();
				}

			public:
				int get_block_number(){
					return m_blocks.size();
				}
				void add_block(GeoSimulationBlock *block){
					m_blocks.push_back(block);
				}
				Block *get_block(long order){
					return (Block*)m_blocks[order];
				}
				void clear_blocks(){
					for(int i = 0; i < m_blocks.size(); i++){
						delete m_blocks[i];
					}
					m_blocks.clear();
				}

				//
				//
				void set_simulator(Simulator *model_simulator, Simulator *solution_simulator) {
					m_parent_model_simulator = model_simulator; 
					m_host_solution_simulator = solution_simulator;
				}
				Simulator *get_solution_simulator() {
					return m_host_solution_simulator;
				}
			public:
				// which block simulator
				Simulator *m_parent_model_simulator;
				Simulator *m_host_solution_simulator;

				//
				BlockContainer m_blocks;
			};
		}

		namespace traits
		{
			template
				<
				typename Simulator,
				typename Mesh,
				typename Block,
				typename ParentSolution
				>
			struct simulation_solution_container<model::geo_simulation_solution<Simulator, Mesh, Block, ParentSolution> >
			{
				typedef std::vector<ParentSolution*> type;
			};
		}
	} 
}

#endif