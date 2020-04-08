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

#ifndef ANYWAY_RCF_DIMENSION_SCHEDULE_REDUCER_H
#define ANYWAY_RCF_DIMENSION_SCHEDULE_REDUCER_H

#include ".\generic programming\core\tags.h"
#include ".\generic programming\dimension\strategy\job_schedule_reducer_default.h"

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
				typename JobTracker,
				typename TaskServerVector,
				typename RcfSystem = rcf_system<JobTracker>::type,
				typename tag = typename tag<JobTracker>::type
			>
			struct default_mr_schedule_reducer
			{
			};

			/*!
			*
			**/
			template <typename JobTracker, typename TaskServerVector>
			struct default_mr_schedule_reducer<JobTracker, TaskServerVector, deltasoft_tag, job_tracker_tag>
			{
				typedef typename strategy::job_schedule_reducer_default type;
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
				typename JobTracker,
				typename TaskServerVector,
				typename Strategy,
				typename RcfSystem = typename rcf_system<JobTracker>::type,
				typename tag = typename tag<JobTracker>::type
			>
			struct mr_schedule_reducer : detail::calculate_null
			{
				static inline void apply(JobTracker const& masterservant, TaskServerVector &reducers, Strategy const& strategy)
				{
					return calculate_null::apply<std::vector<unsigned long long>>(masterservant, chunkservant, chunkfile, strategy);
				}
			};

			/*!
			*
			**/
			template <typename JobTracker, typename TaskServerVector, typename Strategy>
			struct mr_schedule_reducer<JobTracker, TaskServerVector, Strategy, deltasoft_tag, job_tracker_tag>
			{
				static inline void apply(JobTracker const& trackerservant, TaskServerVector &reducers, Strategy const& strategy)
				{
					strategy.apply(trackerservant, reducers);
				}
			};
		}

		// resolve kinds of strategy
		namespace resolve_strategy
		{
			/*!
			*
			**/
			struct mr_schedule_reducer
			{
				template <typename JobTracker, typename TaskServerVector, typename Strategy>
				static inline void apply(JobTracker const& trackerservant, TaskServerVector &reducers, Strategy &strategy)
				{
					return dispatch::mr_schedule_reducer<JobTracker, TaskServerVector, Strategy>::apply(trackerservant, reducers, strategy);
				}

				template <typename JobTracker, typename TaskServerVector>
				static inline void apply(JobTracker const& trackerservant, TaskServerVector &reducers, default_strategy)
				{
					typedef typename detail::default_mr_schedule_reducer<JobTracker,TaskServerVector>::type strategy_type;
					return dispatch::mr_schedule_reducer<JobTracker, TaskServerVector, strategy_type>::apply(trackerservant, reducers, strategy_type());
				}
			};
		}

		// resolve 
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename JobTracker, typename TaskServerVector>
			struct mr_schedule_reducer
			{
				template <typename Strategy>
				static inline void apply(JobTracker const& trackerservant, TaskServerVector &reducers, Strategy const& strategy)
				{
					resolve_strategy::mr_schedule_reducer::apply(trackerservant, reducers, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename JobTracker, typename TaskServerVector, typename Strategy>
		inline typename void mr_schedule_reducer(JobTracker const& trackerservant, TaskServerVector &reducers, Strategy const& strategy)
		{
			resolve_variant::mr_schedule_reducer<JobTracker, TaskServerVector>::apply(trackerservant, reducers, strategy);
		}
	}
}

#endif