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

#ifndef ANYWAY_RCF_DIMENSION_CHUNK_DATA_READ_H
#define ANYWAY_RCF_DIMENSION_CHUNK_DATA_READ_H

//
#include "any/base/hash/md5_hash.h"

//
#include "generic programming/core/tags.h"
#include "generic programming/dimension/strategy/chunk_data_read_asfile_logged.h"

namespace anyway
{
	namespace rcf
	{
		// detail
		namespace detail
		{
			//
			// Helper metafunction for default strategy retrieval
			template
			<
				typename MasterServant,
				typename ChunkServant,
				typename ChunkFile,
				typename RcfSystem = rcf_system<ChunkServant>::type,
				typename tag = typename tag<ChunkServant>::type
			>
			struct default_read_strategy
			{
			};

			/*!
			*
			**/
			template <typename MasterServant, typename ChunkServant, typename ChunkFile>
			struct default_read_strategy<MasterServant, ChunkServant, ChunkFile, deltasoft_tag, gfschunk_tag>
			{
				typedef typename strategy::chunk_data_read_asfile_logged type;
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
				typename MasterServant,
				typename ChunkServant,
				typename ChunkFile,
				typename Strategy,
				typename RcfSystem = typename rcf_system<ChunkServant>::type,
				typename tag = typename tag<ChunkServant>::type
			>
			struct gfs_chunk_data_read : detail::calculate_null
			{
				static inline std::vector<unsigned long long> apply(MasterServant const& masterservant, ChunkServant const& chunkservant, MasterFile const& masterfile, Strategy const& strategy)
				{
					return calculate_null::apply<std::vector<unsigned long long>>(masterservant, chunkservant, chunkfile, strategy);
				}
			};

			/*!
			*
			**/
			template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename Strategy>
			struct gfs_chunk_data_read<MasterServant, ChunkServant, ChunkFile, Strategy, deltasoft_tag, gfschunk_tag>
			{
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, Strategy const& strategy)
				{
					return strategy.apply(masterservant, chunkservant, chunkfile);
				}
			};
		}

		// resolve kinds of strategy
		namespace resolve_strategy
		{
			/*!
			*
			**/
			struct gfs_chunk_data_read
			{
				template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename Strategy>
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, Strategy const& strategy)
				{
					return dispatch::gfs_chunk_data_read<MasterServant, ChunkServant, ChunkFile, Strategy>::apply(masterservant, chunkservant, chunkfile, strategy);
				}

				template <typename MasterServant, typename ChunkServant, typename ChunkFile>
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, default_strategy)
				{
					typedef typename detail::default_read_strategy<MasterServant, ChunkServant, ChunkFile>::type strategy_type;
					return dispatch::gfs_chunk_data_read<MasterServant, ChunkServant, ChunkFile, strategy_type>::apply(masterservant, chunkservant, chunkfile, strategy_type());
				}
			};
		}

		// resolve kinds of object
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename MasterServant, typename ChunkServant, typename ChunkFile>
			struct gfs_chunk_data_read
			{
				template <typename Strategy>
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, Strategy const& strategy)
				{
					return resolve_strategy::gfs_chunk_data_read::apply(masterservant, chunkservant, chunkfile, strategy);
				}
			};

			// for other kinds of objects
			// ...
		}

		//
		/*!
		*
		**/
		template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename Strategy>
		inline typename bool gfs_chunk_data_read(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, Strategy const& strategy)
		{
			return resolve_variant::gfs_chunk_data_read<MasterServant, ChunkServant, ChunkFile>::apply(masterservant, chunkservant, chunkfile, strategy);
		}
	}
}

#endif