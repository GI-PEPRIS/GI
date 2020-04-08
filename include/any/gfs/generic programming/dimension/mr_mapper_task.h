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

#ifndef ANYWAY_RCF_DIMENSION_MR_MAPPER_TASK_H
#define ANYWAY_RCF_DIMENSION_MR_MAPPER_TASK_H

namespace anyway
{
	namespace rcf
	{
		//
		namespace detail
		{
			/*!
			* delta soft open source
			**/
			struct deltasoft_job_mapper_task
			{
				template <typename Mapper, typename MapTask, typename Strategy>
				static inline void apply(Mapper const& servant, MapTask const& task, Strategy const& strategy)
				{
					typedef typename rcf_serviceimpl<Mapper>::type ServantImpl;
					ServantImpl *impl = servant.m_servant;
					assert(impl);

					impl->SetMapTask(task);
				}
			};
		}

		//
		namespace dispatch
		{
			/*!
			*
			**/
			template
			<
				typename Mapper,
				typename MapTask,
				typename RcfSystem = rcf_system<Mapper>::type,
				typename tag = typename tag<Mapper>::type
			>
			struct mr_mapper_task : detail::calculate_null
			{
				template <typename Strategy>
				static inline void apply(Mapper const& servant, MapTask const& task, Strategy const& strategy)
				{
					return calculate_null::apply<bool>(servant, connection, files, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Mapper, typename MapTask>
			struct mr_mapper_task<Mapper, MapTask, deltasoft_tag, job_mapper_tag> : detail::deltasoft_job_mapper_task
			{
			};
		}

		//
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Mapper, typename MapTask>
			struct mr_mapper_task
			{
				template <typename Strategy>
				static inline void apply(Mapper const& servant, MapTask const& task, Strategy const& strategy)
				{
					dispatch::mr_mapper_task<Mapper, MapTask>::apply(servant, task, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename Mapper, typename MapTask, typename Strategy>
		inline typename void mr_mapper_task(Mapper const& servant, MapTask const& task, Strategy const& strategy)
		{
			return resolve_variant::mr_mapper_task<Mapper, MapTask>::apply(servant, task, strategy);
		}
	}
}

#endif