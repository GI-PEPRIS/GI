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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_MODEL_SOLUTION_BLOCK_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_MODEL_SOLUTION_BLOCK_H

//
#include "generic programming/core/tag.h"
#include "generic programming/core/tags.h"
#include "generic programming/core/simulation_block_container.h"

//
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

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
				typename ParentBlock = GeoSimulationBlock
				>
			class geo_simulation_block : public ParentBlock
			{
			public:
				//
				explicit inline geo_simulation_block()
				{
				}
				~geo_simulation_block()
				{
				}

			public:
				//
				void set_simulator(Simulator *model_simulator, Simulator* solution_simulator, Simulator *block_simulator){
					m_parent_model_simulator = model_simulator;
					m_parent_solution_block_simulator = solution_simulator;
					m_host_job_block_simulator = block_simulator;
				}

			public:
				// which block simulator
				Simulator *m_host_job_block_simulator;
				Simulator *m_parent_solution_block_simulator; // dumy
				Simulator *m_parent_model_simulator;
			};
		}

		// traits
		namespace traits
		{
			template
				<
				typename Simulator,
				typename Mesh,
				typename ParentBlock
				>
			struct simulation_block_container<model::geo_simulation_block<Simulator, Mesh, ParentBlock> >
			{
				typedef std::vector<ParentBlock*> type;
			};
		}
	}
}

#endif