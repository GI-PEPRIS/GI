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

#ifndef ANYWAY_RCF_DIMENSION_JOB_SCHEDULE_PARAMETER_H
#define ANYWAY_RCF_DIMENSION_JOB_SCHEDULE_PARAMETER_H

#include ".\generic programming\core\tags.h"

namespace anyway
{
	namespace rcf
	{
		// detail
		namespace detail
		{
			/*!
			* delta soft open source
			**/
			struct mr_schedule_parameter_delta
			{
				template <typename TaskServant, typename JobParameter>
				static inline void apply(TaskServant const& servant, JobParameter const& parameter)
				{
					typedef typename rcf_serviceimpl<TaskServant>::type ServantImpl;
					ServantImpl *impl = trackerservant.m_servant;
					assert(impl);

					impl->m_client->getClientStub().getTransport().setMaxIncomingMessageLength(128*1024*1024);//PENG
					impl->SetJobParameter(&parameter);
				}
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
				typename TaskServant,
				typename JobParameter,
				typename RcfSystem = typename rcf_system<TaskServant>::type,
				typename tag = typename tag<TaskServant>::type
			>
			struct mr_schedule_parameter : detail::calculate_null
			{
				static inline void apply(TaskServant const& trackerservant, JobParameter const& specification)
				{
					// never compiled here
					return calculate_null::apply<bool>(servant, filenode, strategy);
				}
			};

			/*!
			*
			**/
			template <typename TaskServant, typename JobParameter>
			struct mr_schedule_parameter<TaskServant, JobParameter, deltasoft_tag, job_tracker_tag> : detail::mr_schedule_parameter_delta
			{
			};
			template <typename TaskServant, typename JobParameter>
			struct mr_schedule_parameter<TaskServant, JobParameter, deltasoft_tag, job_mapper_tag> : detail::mr_schedule_parameter_delta
			{
			};
			template <typename TaskServant, typename JobParameter>
			struct mr_schedule_parameter<TaskServant, JobParameter, deltasoft_tag, job_reducer_tag> : detail::mr_schedule_parameter_delta
			{
			};
		}

		// resolve kinds of object
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename TaskServant, typename JobParameter>
			struct mr_schedule_parameter
			{
				static inline void apply(TaskServant const& servant, JobParameter const& parameter)
				{
					dispatch::mr_schedule_parameter<TaskServant, JobParameter>::apply(servant, parameter);
				}
			};

			// for other kinds of objects
			// ...
		}

		//
		/*!
		*
		**/
		template <typename TaskServant, typename JobParameter>
		inline typename void mr_schedule_parameter(TaskServant const& servant, JobParameter const& parameter)
		{
			resolve_variant::mr_schedule_parameter<TaskServant, JobParameter>::apply(servant, parameter);
		}
	}
}

#endif