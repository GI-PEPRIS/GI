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

#ifndef ANYWAY_RCF_MODEL_GEO_SIMULATION_MATRIX_H
#define ANYWAY_RCF_MODEL_GEO_SIMULATION_MATRIX_H

#include "any/base/anystl.h"

#include "generic programming/core/tags.h"
#include "generic programming/core/simulation_matrix.h"
#include "generic programming/core/simulation_matrix_solver.h"

//
namespace anyway
{ 
	namespace rcf
	{
		//
		namespace model
		{
			template
				<
				typename Model,
				typename ParentMatrix
				>
			class geo_simulation_matrix : public ParentMatrix
			{
			public:
				//
				explicit inline geo_simulation_matrix()
				{
				}
				~geo_simulation_matrix()
				{
				}

			public:

			private:
				//
				Model *m_model;
			};
		}

		//
		namespace traits
		{
			template
				<
				typename Model,
				typename ParentMatrix
				>
			struct tag<model::geo_simulation_matrix<Model, ParentMatrix> >
			{
				typedef simulation_matrix_finite_element_tag type;
			};

			template
				<
				typename Model,
				typename ParentMatrix
				>
			struct simulation_matrix<model::geo_simulation_matrix<Model, ParentMatrix> >
			{
				typedef ParentMatrix type;
			};
		}
	}
}

#endif