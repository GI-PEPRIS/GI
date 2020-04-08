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

#ifndef ANYWAY_RCF_DIMENSION_ALLOCATE_CHUNK_H
#define ANYWAY_RCF_DIMENSION_ALLOCATE_CHUNK_H

#include ".\generic programming\dimension\strategy\chunk_allocate_by_concensus.h"
#include ".\generic programming\dimension\strategy\chunk_allocate_by_geolocation.h"

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
				typename Servant,
				typename MasterFile,
				typename RcfSystem = rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type
			>
			struct default_allocate_strategy
			{
			};

			/*!
			*
			**/
			template <typename Servant, typename MasterFile>
			struct default_allocate_strategy<Servant, MasterFile, deltasoft_tag, gfsmaster_tag>
			{
				typedef typename strategy::chunk_allocate_by_concensus type;
				//typedef typename strategy::chunk_allocate_by_geolocation geolocationtype;
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
				typename Servant,
				typename MasterFile,
				typename Strategy,
				typename RcfSystem = typename rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type,
				typename strategyTag = typename Strategy::type
			>
			struct gfs_master_file_allocate : detail::calculate_null
			{
				static inline std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile, Strategy const& strategy)
				{
					return calculate_null::apply<std::vector<unsigned long long>>(servant, masterfile, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Servant, typename MasterFile, typename Strategy>
			struct gfs_master_file_allocate<Servant, MasterFile, Strategy, deltasoft_tag, gfsmaster_tag, strategy_tag_master_file_allocate_concensus>
			{
				static inline std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile, Strategy const& strategy)
				{
					return strategy.apply(servant, masterfile);
				}
			};
			template <typename Servant, typename MasterFile, typename Strategy>
			struct gfs_master_file_allocate<Servant, MasterFile, Strategy, deltasoft_tag, gfsmaster_tag, strategy_tag_master_file_allocate_geolocation>
			{
				static inline std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile, Strategy const& strategy)
				{
					return strategy.apply(servant, masterfile);
				}
			};
		}

		// resolve kinds of strategy
		namespace resolve_strategy
		{
			/*!
			*
			**/
			struct gfs_master_file_allocate
			{
				template <typename Servant, typename MasterFile, typename Strategy>
				static inline std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile, Strategy const& strategy)
				{
					return dispatch::gfs_master_file_allocate<Servant, MasterFile, Strategy>::apply(servant, masterfile, strategy);
				}

				template <typename Servant, typename MasterFile>
				static inline typename std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile, default_strategy)
				{
					typedef typename detail::default_allocate_strategy<Servant, MasterFile>::type strategy_type;
					return dispatch::gfs_master_file_allocate<Servant, MasterFile, strategy_type>::apply(servant, masterfile, strategy_type());
				}

				template <typename Servant, typename MasterFile>
				static inline typename std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile, chunk_allocate_by_geolocation)
				{
					typedef typename chunk_allocate_by_geolocation strategy_type;
					return dispatch::gfs_master_file_allocate<Servant, MasterFile, strategy_type>::apply(servant, masterfile, chunk_allocate_by_geolocation());
				}
			};
		}

		// resolve kinds of object
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Servant, typename MasterFile>
			struct gfs_master_file_allocate
			{
				template <typename Strategy>
				static inline std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile, Strategy const& strategy)
				{
					return resolve_strategy::gfs_master_file_allocate::apply(servant, masterfile, strategy);
				}
			};

			// for other kinds of objects
			// ...
		}

		//
		/*!
		*
		**/
		template <typename Servant, typename MasterFile, typename Strategy>
		inline typename std::vector<unsigned long long> gfs_master_file_allocate(Servant const& servant, MasterFile &masterfile, Strategy const& strategy)
		{
			return resolve_variant::gfs_master_file_allocate<Servant, MasterFile>::apply(servant, masterfile, strategy);
		}
	}
}

#endif