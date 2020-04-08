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

#ifndef ANYWAY_RCF_DIMENSION_REDUCER_START_H
#define ANYWAY_RCF_DIMENSION_REDUCER_START_H

#include ".\generic programming\core\tags.h"
#include ".\generic programming\dimension\strategy\job_reducer_start_default.h"

namespace anyway
{
	namespace rcf
	{
		// detail
		namespace detail
		{
			// Helper metafunction for default strategy retrieval
			template
			<
				typename JobReducer,
				typename JobParameter,
				typename RcfSystem = rcf_system<JobReducer>::type,
				typename tag = typename tag<JobReducer>::type
			>
			struct default_mr_reducer_start
			{
			};

			/*!
			*
			**/
			template <typename JobReducer, typename JobParameter>
			struct default_mr_reducer_start<JobReducer, JobParameter, deltasoft_tag, job_reducer_tag>
			{
				typedef typename strategy::job_reducer_start_default type;
			};
		}
		
		// dispatch
		namespace dispatch
		{
			/*!
			*
			**/
			template
			<
				typename JobReducer,
				typename JobParameter,
				typename Strategy,
				typename RcfSystem = typename rcf_system<JobReducer>::type,
				typename tag = typename tag<JobReducer>::type
			>
			struct mr_reducer_start : detail::calculate_null
			{
				static inline void apply(JobReducer const& servant, JobParameter &parameter, Strategy const& strategy)
				{
					// intend to error
					return calculate_null::apply<std::vector<unsigned long long>>(masterservant, chunkservant, chunkfile, strategy);
				}
			};

			/*!
			*
			**/
			template <typename JobReducer, typename JobParameter, typename Strategy>
			struct mr_reducer_start<JobReducer, JobParameter, Strategy, deltasoft_tag, job_reducer_tag>
			{
				static inline void apply(JobReducer const& servant, JobParameter &parameter, Strategy const& strategy)
				{
					strategy.apply(servant, parameter);
				}
			};
		}

		// resolve kinds of strategy
		namespace resolve_strategy
		{
			/*!
			*
			**/
			struct mr_reducer_start
			{
				template <typename JobReducer, typename JobParameter, typename Strategy>
				static inline void apply(JobReducer const& servant, JobParameter &parameter, Strategy const& strategy)
				{
					dispatch::mr_reducer_start<JobReducer, JobParameter, Strategy>::apply(servant, parameter, strategy);
				}

				template <typename JobReducer, typename JobParameter>
				static inline void apply(JobReducer const& servant, JobParameter &parameter, default_strategy)
				{
					typedef typename detail::default_mr_reducer_start<JobReducer, JobParameter>::type strategy_type;
					dispatch::mr_reducer_start<JobReducer, JobParameter, strategy_type>::apply(servant, parameter, strategy_type());
				}
			};
		}

		// resolve 
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename JobReducer, typename JobParameter>
			struct mr_reducer_start
			{
				template <typename Strategy>
				static inline void apply(JobReducer const&servant, JobParameter &parameter, Strategy const& strategy)
				{
					resolve_strategy::mr_reducer_start::apply(servant, parameter, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename JobReducer, typename JobParameter, typename Strategy>
		inline typename void mr_reducer_start(JobReducer const& servant, JobParameter &parameter, Strategy &strategy)
		{
			resolve_variant::mr_reducer_start<JobReducer, JobParameter>::apply(servant, parameter, strategy);
		}
	}
}

#endif