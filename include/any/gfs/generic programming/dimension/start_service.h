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

#ifndef ANYWAY_RCF_DIMENSION_START_SERVICE_H
#define ANYWAY_RCF_DIMENSION_START_SERVICE_H

#include "..\dimension\calculate_null.h"
#include "..\core\tags.h"

namespace anyway
{
	namespace rcf
	{
		// dimesnion detail
		namespace detail
		{
			/*!
			* delta soft open source
			**/
			struct deltasoft_start_rcf_service
			{
				template <typename Servant, typename Configurator, typename Strategy>
				static inline bool apply(Servant const& servant, Configurator const& configurator, Strategy const&)
				{
					typedef typename rcf_serviceimpl<Servant>::type ServantImpl;

					ServantImpl *impl = servant.m_servant;
					impl->Init(configurator);
					if(!impl->IsRunning())
					{
						impl->Start();
						::Sleep(1000);
					}
					if(!impl->IsRunning())
					{
						return false;
					}

					return true;
				}
			};
		}

		// against rcf systems
		namespace dispatch
		{
			/*!
			*
			**/
			template
			<
				typename Servant,
				typename Configurator, 
				typename RcfSystem = rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type
			>
			struct start_service : detail::calculate_null
			{
				template <typename Strategy>
				static inline bool apply(Servant const& servant, Configurator const& configurator, Strategy const& strategy)
				{
					return calculate_null::apply<bool>(servant, configurator, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Servant, typename Configurator>
			struct start_service<Servant, Configurator, deltasoft_tag, gfsmaster_tag> : detail::deltasoft_start_rcf_service
			{};
			template <typename Servant, typename Configurator>
			struct start_service<Servant, Configurator, deltasoft_tag, gfschunk_tag> : detail::deltasoft_start_rcf_service
			{};
			template <typename Servant, typename Configurator>
			struct start_service<Servant, Configurator, deltasoft_tag, job_tracker_tag> : detail::deltasoft_start_rcf_service
			{};
			template <typename Servant, typename Configurator>
			struct start_service<Servant, Configurator, deltasoft_tag, job_mapper_tag> : detail::deltasoft_start_rcf_service
			{};
			template <typename Servant, typename Configurator>
			struct start_service<Servant, Configurator, deltasoft_tag, job_reducer_tag> : detail::deltasoft_start_rcf_service
			{};
			template <typename Servant, typename Configurator>
			struct start_service<Servant, Configurator, deltasoft_tag, simulation_service_master_tag> : detail::deltasoft_start_rcf_service
			{};
			template <typename Servant, typename Configurator>
			struct start_service<Servant, Configurator, deltasoft_tag, simulation_service_worker_tag> : detail::deltasoft_start_rcf_service
			{};
		}

		// 
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Servant, typename Configurator>
			struct start_service
			{
				template <typename Strategy>
				static inline bool apply(Servant const& servant, Configurator const& configurator, Strategy const& strategy)
				{
					return dispatch::start_service<Servant, Configurator>::apply(servant, configurator, strategy);
				}
			};
		}

		/*!
		*
		**/
		template <typename Servant, typename Configurator, typename Strategy>
		inline typename bool start_service(Servant const& servant, Configurator const& configurator, Strategy const& strategy)
		{
			return resolve_variant::start_service<Servant, Configurator>::apply(servant, configurator, strategy);
		}
	}
}

#endif