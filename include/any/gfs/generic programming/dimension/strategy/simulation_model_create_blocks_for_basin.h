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

#ifndef ANYWAY_RCF_DIMENSION_SIMULATION_MODEL_CREATE_BLOCKS_FOR_BASIN_H
#define ANYWAY_RCF_DIMENSION_SIMULATION_MODEL_CREATE_BLOCKS_FOR_BASIN_H

#include "default_strategy.h"
#include "../../core/tags.h"

namespace anyway
{
	namespace rcf
	{
		namespace detail
		{
			namespace strategy
			{
				//
				// services
				//
				struct simulation_model_create_blocks_for_basin : public default_strategy
				{
					//
					template
						<
						typename Model,
						typename Solution
						>
						static int apply(Model &model, Solution &solution)
						{
							typedef simulation_simulator<Model>::type Simulator;

							Simulator *host_simulator = model.m_host_model_simulator;
							host_simulator->create_model_blocks(&model, &solution);
							host_simulator->create_model_block_file(&model, &solution);
							host_simulator->create_model_block_memory(&model, &solution);
							
							return solution.get_block_number();
						}
				};
			}
		}
	}
}


#endif