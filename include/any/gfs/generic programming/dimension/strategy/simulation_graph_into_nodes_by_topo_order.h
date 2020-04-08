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

#ifndef ANYWAY_RCF_DIMENSION_SIMULATION_GRAPH_INTO_NODES_BY_TOPO_ORDER_H
#define ANYWAY_RCF_DIMENSION_SIMULATION_GRAPH_INTO_NODES_BY_TOPO_ORDER_H

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
				struct simulation_graph_into_nodes_by_topo_order : public default_strategy
				{
					//
					template
						<
						typename Graph
						>
						static int apply(Graph &graph)
						{
							try
							{
								
							}
							catch(...)
							{
							
							}
							return 0;
						}
				};
			}
		}
	}
}


#endif