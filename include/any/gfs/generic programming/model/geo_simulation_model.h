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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_MODEL_SIMULATOR_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_MODEL_SIMULATOR_H

#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

// traits
#include "generic programming/core/tag.h"
#include "generic programming/core/tags.h"

#include "generic programming/core/simulation_simulator.h"
#include "generic programming/core/simulation_mesh.h"
#include "generic programming/core/simulation_mesh_container.h"
#include "generic programming/core/simulation_solution.h"
#include "generic programming/core/simulation_solution_container.h"
#include "generic programming/core/simulation_block.h"
#include "generic programming/core/simulation_block_container.h"

// model
#include "generic programming/model/geo_simulation_solution.h"
#include "generic programming/model/geo_simulation_block.h"

// meta functions
#include "generic programming/dimension/gs_model_initialize.h"
#include "generic programming/dimension/gs_model_create_solutions.h"
#include "generic programming/dimension/gs_model_create_blocks.h"

#include "generic programming/dimension/strategy/simulation_model_initialize_for_basin.h"
#include "generic programming/dimension/strategy/simulation_model_create_solutions_for_basin.h"
#include "generic programming/dimension/strategy/simulation_model_create_blocks_for_basin.h"


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
				typename Solution,
				typename Block,
				typename ParentModel = GeoSimulationModel
				>
			class geo_simulation_model : public ParentModel
			{
			public:
				//
				typedef typename simulation_solution_container<Solution>::type SolutionContainer;
				typedef typename simulation_block_container<Block>::type BlockContainer;

				typedef typename std::vector<Mesh *> MeshContainer;

			public:
				//
				explicit inline geo_simulation_model() : m_host_model_simulator(0)
				{
					m_host_model_simulator = new Simulator;
				}
				~geo_simulation_model()
				{
					delete m_host_model_simulator;
				}

			public:
				//
				void create_model(Mesh *whole_mesh, MeshContainer &refined_meshes) {
					// define simulator and create model file
					gs_model_initialize(*this, whole_mesh, refined_meshes, detail::strategy::simulation_model_initialize_for_basin());

					//
					for(int i = 0; i < m_solutions.size(); i++)
					{
						delete m_solutions[i];
					}
					m_solutions.clear();
					gs_model_create_solutons(*this, detail::strategy::simulation_model_create_solutions_for_basin());

					//
					for(int i = 0; i < m_solutions.size(); i++)
					{
						gs_model_create_blocks(*this, *((Solution*)m_solutions[i]), detail::strategy::simulation_model_create_blocks_for_basin());
					}
				}		

				bool update_block(Block &oneblock){
					return false;
				}

				int get_solution_number(){return m_solutions.size();}
				Solution *get_solution(int order){return (Solution *)m_solutions[order];}

				//
				void add_solution(Solution *one){m_solutions.push_back(one);}
				Simulator *get_simulator(){ return m_host_model_simulator;}

				//
			public:
				// simulator = initial mesh & refined mesh
				Simulator *m_host_model_simulator; 

				//
				SolutionContainer m_solutions;
			};
		}

		//
		namespace traits
		{
			template
				<
				typename Simulator,
				typename Mesh,
				typename Solution,
				typename Block
				>
			struct tag<model::geo_simulation_model<Simulator, Mesh, Solution, Block> >
			{
				typedef simulation_model_simulator_basin_tag type;
			};

			template
				<
				typename Simulator,
				typename Mesh,
				typename Solution,
				typename Block
				>
			struct simulation_mesh<model::geo_simulation_model<Simulator, Mesh, Solution, Block> >
			{
				typedef Mesh type;
			};

			template
				<
				typename Simulator,
				typename Mesh,
				typename Solution,
				typename Block
				>
			struct simulation_mesh_container<model::geo_simulation_model<Simulator, Mesh, Solution, Block> >
			{
				typedef std::vector<Mesh*> type;
			};

			template
				<
				typename Simulator,
				typename Mesh,
				typename Solution,
				typename Block
				>
			struct simulation_solution<model::geo_simulation_model<Simulator, Mesh, Solution, Block> >
			{
				typedef Solution type;
			};

			template
				<
				typename Simulator,
				typename Mesh,
				typename Solution,
				typename Block
				>
			struct simulation_block<model::geo_simulation_model<Simulator, Mesh, Solution, Block> >
			{
				typedef Block type;
			};

			template
				<
				typename Simulator,
				typename Mesh,
				typename Solution,
				typename Block
				>
			struct simulation_simulator<model::geo_simulation_model<Simulator, Mesh, Solution, Block> >
			{
				typedef Simulator type;
			};
		}
	}
}

#endif