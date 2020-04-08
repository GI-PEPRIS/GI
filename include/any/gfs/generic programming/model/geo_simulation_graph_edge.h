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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_GRAPH_EDGE_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_GRAPH_EDGE_H

//
#include "boost/function.hpp"

//
#include "any/base/anystl.h"
#include "any/base/loki/generic.h"
using namespace AnyBase;
using namespace AnyBase::Loki;

//
#include "generic programming/core/tag.h"
#include "generic programming/core/tags.h"
#include "generic programming/core/simulation_graph_edge.h"
#include "generic programming/core/simulation_graph_edge_container.h"


namespace anyway
{ 
	namespace rcf
	{
		namespace model
		{
			//
			//
			template
				<
				typename FromNode,
				typename ToNode,
				typename TypeTag = simulation_graph_edge_type_tag,
				typename ParentEdge = SimulationJobEdge
				>
			class geo_simulation_graph_edge : public ParentEdge
			{
			public:
				//
				explicit inline geo_simulation_graph_edge()
				{

				}
				~geo_simulation_graph_edge()
				{
				}

			public:
				//
				bool is_data_edge(){
					return IsSameType<TypeTag, simulation_graph_edge_type_data_tag>::value;
				}
				bool is_control_edge(){
					return IsSameType<TypeTag, simulation_graph_edge_type_control_tag>::value;
				}
			};
		}

		//
		namespace traits
		{
			template
				<
				typename Node,
				typename TypeTag,
				typename Edge
				>
			struct simulation_graph_edge<model::geo_simulation_graph_edge<Node, TypeTag, Edge> >
			{
				typedef Edge type;
			};

			template
				<
				typename Node,
				typename TypeTag,
				typename Edge
				>
			struct simulation_graph_edge_container<model::geo_simulation_graph_edge<Node, TypeTag, Edge> >
			{
				typedef std::vector<Edge > type;
			};
		}
	}
		
}

#endif