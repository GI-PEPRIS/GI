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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_GRAPH_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_GRAPH_H

//
#include "any/base/anystl.h"

//
#include "generic programming/core/tag.h"
#include "generic programming/core/tags.h"

#include "generic programming/dimension/gs_graph_create.h"
#include "generic programming/dimension/strategy/simulation_graph_into_nodes_by_topo_order.h"

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
				typename Node,
				typename Edge,
				typename NodeContainer,
				typename EdgeContainer,
				typename ParentGraph = SimulationJobGraph
				>
			class geo_simulation_graph : public ParentGraph // as the whole simulation parameter
			{
			public:
				//
				explicit inline geo_simulation_graph() {
					m_tortoise_job_idx = 0;
					m_rabbit_job_idx = 0;
				}
				~geo_simulation_graph() {
				}

			public:
				//
				bool create_simulation_graph(EdgeContainer const& job_edges) {
					//
					m_job_nodes_in_topo_order.clear();
					m_job_edges.clear();
					m_job_edges.assign(job_edges.begin(), job_edges.end());		

					SimulationJobEdge *firstedge = 0;
					for(int i = 0; i < m_job_edges.size(); i++)
					{
						SimulationJobNode *curnode = m_job_edges[i]->m_from_node;
						bool findparent = false;
						for(int j = 0; j < m_job_edges.size(); j++)
						{
							if(m_job_edges[j]->m_to_node == curnode)
							{
								findparent = true;
								break;
							}
						}
						if(!findparent)
						{
							firstedge = m_job_edges[i];
							break;
						}
					}
					if(firstedge)
					{
						m_job_nodes_in_topo_order.push_back(firstedge->m_from_node);
						m_job_nodes_in_topo_order.push_back(firstedge->m_to_node);
						while(true)
						{
							SimulationJobNode *curnode = m_job_nodes_in_topo_order[m_job_nodes_in_topo_order.size() - 1];
							bool findchild = false;
							for(int i = 0; i < m_job_edges.size(); i++)
							{
								if(m_job_edges[i]->m_from_node == curnode)
								{
									findchild = true;
									m_job_nodes_in_topo_order.push_back(m_job_edges[i]->m_to_node);
									break;
								}
							}
							if(!findchild)
								break;
						}
					}
					//gs_graph_create(this, detail::strategy::simulation_graph_into_nodes_by_topo_order());
					return m_job_nodes_in_topo_order.size()>0;
				}

				NodeContainer &get_nodes(){
					return m_job_nodes_in_topo_order;
				}

				Node *get_node(long job_node_idx){
					for(int i = 0; i < m_job_nodes_in_topo_order.size(); i++){
						if(m_job_nodes_in_topo_order[i]->m_job_node_idx == job_node_idx){
							return m_job_nodes_in_topo_order[i];
						}
					}

					return 0;
				}

				//
				bool is_master_done(){
					return m_rabbit_job_idx == m_job_nodes_in_topo_order.size() && \
						m_tortoise_job_idx == m_job_nodes_in_topo_order.size();
				}
				bool is_master_meetwith(){
					return m_tortoise_job_idx == m_rabbit_job_idx;
				}

				// for master's graph, update by worker
				bool is_master_tortoise_idx(long job_idx){
					return job_idx == m_tortoise_job_idx;
				}
				bool is_master_rabbit_idx(long job_idx){
					return job_idx == m_rabbit_job_idx;
				}
				void set_master_rabbit_idx(long job_idx_just_done) {
					m_rabbit_job_idx = job_idx_just_done;
				}
				void set_master_tortoise_idx(long job_idx_just_done) {
					m_tortoise_job_idx = job_idx_just_done;
				}			
				Node *get_master_rabbit_node(){
					if(m_rabbit_job_idx >= m_job_nodes_in_topo_order.size())
						return 0;
					return m_job_nodes_in_topo_order[m_rabbit_job_idx];
				}

				void reset_master_node_for_loop() {
					m_tortoise_job_idx = m_job_nodes_in_topo_order[m_rabbit_job_idx]->m_repeat_from_job_idx;
					for(int i = m_tortoise_job_idx; i <= m_rabbit_job_idx; i++)
					{
						m_job_nodes_in_topo_order[i]->m_job_state = AnyRCF::JS_Ready;
					}
					m_rabbit_job_idx = m_tortoise_job_idx;
				}

				// for worker's graph
				bool is_worker_done(){
					for(int i = 0; i < m_job_nodes_in_topo_order.size(); i++) {
						if(m_job_nodes_in_topo_order[i]->m_job_state != AnyRCF::JS_Done) {
							return false;
						}
					}
					return true;
				}
				Node *get_master_node_for_running() {
					//
					return m_job_nodes_in_topo_order[m_rabbit_job_idx];
				}
				Node *get_worker_node_for_running() {
					//
					for(int i = 0; i < m_job_nodes_in_topo_order.size(); i++) {
						if(m_job_nodes_in_topo_order[i]->m_job_state == AnyRCF::JS_Ready) {
							return m_job_nodes_in_topo_order[i];
						}
					}
					return 0;
				}
				// for worker's graph
				void reset_worker_node_after_running(bool needloop) {
					for(int i = 0; i < m_job_nodes_in_topo_order.size(); i++) {
						if(m_job_nodes_in_topo_order[i]->m_job_state == AnyRCF::JS_Ready)
						{
							m_job_nodes_in_topo_order[i]->m_job_state = AnyRCF::JS_Done;
							if(m_job_nodes_in_topo_order[i]->m_is_need_repeated)
							{
								if(needloop)
								{
									int repeatjobidx = m_job_nodes_in_topo_order[i]->m_repeat_from_job_idx;
									for(int j = 0; j < m_job_nodes_in_topo_order.size(); j++)
									{
										if(m_job_nodes_in_topo_order[j]->m_job_node_idx == repeatjobidx)
										{
											for(int k = j; k <= i; k++)
												m_job_nodes_in_topo_order[k]->m_job_state = AnyRCF::JS_Ready;
											break;
										}
									}
								}
								else if(i + 1 < m_job_nodes_in_topo_order.size())
									m_job_nodes_in_topo_order[i + 1]->m_job_state = AnyRCF::JS_Ready;
							}
							else
							{
								if(i + 1 < m_job_nodes_in_topo_order.size())
								{
									m_job_nodes_in_topo_order[i + 1]->m_job_state = AnyRCF::JS_Ready;
								}
							}
							break;
						}
					}				
			    }
				
				void reset_worker_node_after_master(long master_job_idx) {

					m_job_nodes_in_topo_order[master_job_idx]->m_job_state = AnyRCF::JS_Done;
					if(master_job_idx + 1 < m_job_nodes_in_topo_order.size()) {
						m_job_nodes_in_topo_order[master_job_idx + 1]->m_job_state = AnyRCF::JS_Ready;
					}
				}

			public:
				// graph itself
				EdgeContainer m_job_edges;
				NodeContainer m_job_nodes_in_topo_order;

				// against different graph executed in different workers
				long m_tortoise_job_idx; // the slowest
				long m_rabbit_job_idx;
			};
		}

		//
		namespace traits
		{
			template
				<
				typename Node,
				typename Edge,
				typename NodeContainer,
				typename EdgeContainer
				>
			struct tag<model::geo_simulation_graph<Node, Edge, NodeContainer, EdgeContainer> >
			{
				typedef simulation_graph_in_topo_order_tag type;
			};

			template
				<
				typename Node,
				typename Edge,
				typename NodeContainer,
				typename EdgeContainer
				>
			struct simulation_graph_node<model::geo_simulation_graph<Node, Edge, NodeContainer, EdgeContainer> >
			{
				typedef Node type;
			};

			template
				<
				typename Node,
				typename Edge,
				typename NodeContainer,
				typename EdgeContainer
				>
			struct simulation_graph_node_container<model::geo_simulation_graph<Node, Edge, NodeContainer, EdgeContainer> >
			{
				typedef NodeContainer type;
			};

			template
				<
				typename Node,
				typename Edge,
				typename NodeContainer,
				typename EdgeContainer
				>
			struct simulation_graph_edge<model::geo_simulation_graph<Node, Edge, NodeContainer, EdgeContainer> >
			{
				typedef Edge type;
			};

			template
				<
				typename Node,
				typename Edge,
				typename NodeContainer,
				typename EdgeContainer
				>
			struct simulation_graph_edge_container<model::geo_simulation_graph<Node, Edge, NodeContainer, EdgeContainer> >
			{
				typedef EdgeContainer type;
			};


		}
	}
}

#endif