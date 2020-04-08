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

#ifndef ANYWAY_RCF_DIMENSION_GS_MASTER_SET_RABBIT_IDX_H
#define ANYWAY_RCF_DIMENSION_GS_MASTER_SET_RABBIT_IDX_H

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/calculate_null.h"

namespace anyway
{
	namespace rcf
	{
		//
		//
		namespace detail
		{
			struct default_master_set_rabbit_idx
			{
				template<typename Master>
				static void apply(Master &master, long job_idx)
				{
					try
					{
						typedef typename rcf_serviceimpl<Master>::type MasterServantImpl;
						MasterServantImpl *masterimpl = master.m_servant;
						assert(masterimpl);

						if(!masterimpl->IsRunning())
						{
							//masterimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
							return;
						}
						masterimpl->SetRabbitIdx(job_idx);
					}
					catch (...)
					{
					}
				}

			};
		}

		//
		//
		namespace dispatch
		{
			template
				<
				typename Master,
				typename Tag = typename rcf_system<Master>::type
				>
			struct gs_master_set_rabbit_idx :  detail::calculate_null
			{
				// not implemented
				static inline void apply(Master &master, long job_idx)
				{
					//return calculate_null::apply<int>(graph, strategy);
				}
			};

			//
			template <typename Master>
			struct gs_master_set_rabbit_idx<Master, deltasoft_tag> : public detail::default_master_set_rabbit_idx
			{
			};
		}

		//
		// against different algorithms how to iterate graph node
		namespace resolve_strategy
		{
		}

		//
		// against possibilities of different meta-function parameters
		namespace resolve_variant
		{
		}

		//
		//
		template<typename Master>
		void gs_master_set_rabbit_idx(Master &master, long job_idx)
		{
			return dispatch::gs_master_set_rabbit_idx
				<
				Master
				>::apply(master, job_idx);
		}
	}
}
#endif