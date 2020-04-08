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
#ifndef ANYWAY_RCF_CORE_GEO_SIMULATION_MODEL_MATRIX_H
#define ANYWAY_RCF_CORE_GEO_SIMULATION_MODEL_MATRIX_H

#include <boost/mpl/assert.hpp>
#include "../util/bare_type.h"

namespace anyway
{
	namespace rcf
	{
		//
		namespace traits
		{
			template <typename Matrix, typename Enable = void>
			struct simulation_matrix
			{
				BOOST_MPL_ASSERT_MSG
					(
						false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Matrix>)
					);
			};
		}

		/*!
		*
		**/
		template <typename Matrix>
		struct simulation_matrix
		{
			typedef typename traits::simulation_matrix
				<
					typename rcf::util::bare_type<Matrix>::type
				>::type type;
		};
	}
}

#endif