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

#ifndef ANYWAY_RCF_DIMENSION_SIMULATION_WORKER_UPDATE_GRAPH_IN_VECTOR_H
#define ANYWAY_RCF_DIMENSION_SIMULATION_WORKER_UPDATE_GRAPH_IN_VECTOR_H

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
				struct simulation_worker_update_graph_in_vector : public default_strategy
				{
					//
					template
						<
						typename Worker,
						typename Graph
						>
					static bool apply(Worker &worker, Graph &graph)
					{
						bool isuploaded = true;
						try
						{
							typedef typename rcf_serviceimpl<Worker>::type WorkerServantImpl;
							WorkerServantImpl *workerimpl = worker.m_servant;
							assert(workerimpl);

							if(!workerimpl->IsRunning())
							{
								//workerimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
								return 0;
							}
							workerimpl->UpdateTopoGraph(graph.m_job_graph_idx, graph.m_job_nodes_in_topo_order);

						}
						catch (...)
						{
						}

						return isuploaded;
					}
				};
			}
		}
	}
}


#endif