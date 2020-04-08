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
#ifndef ANYWAY_RCF_CORE_GEO_SIMULATION_MODEL_SOLUTION_H
#define ANYWAY_RCF_CORE_GEO_SIMULATION_MODEL_SOLUTION_H

#include <boost/mpl/assert.hpp>
#include "../util/bare_type.h"

namespace anyway
{
	namespace rcf
	{
		//
		namespace traits
		{
			template <typename Model, typename Enable = void>
			struct simulation_solution
			{
				BOOST_MPL_ASSERT_MSG
					(
						false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Model>)
					);
			};
		}

		/*!
		*
		**/
		template <typename Model>
		struct simulation_solution
		{
			typedef typename traits::simulation_solution
				<
					typename rcf::util::bare_type<Model>::type
				>::type type;
		};
	}
}

#endif