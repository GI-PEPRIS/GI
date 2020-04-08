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

#ifndef ANYWAY_RCF_DIMENSION_CHUNK_DATA_WRITE_H
#define ANYWAY_RCF_DIMENSION_CHUNK_DATA_WRITE_H

//
#include "any/base/hash/md5_hash.h"
#include "generic programming/core/tags.h"
#include "generic programming/dimension/strategy/chunk_data_write_asfile_logged.h"
#include "generic programming/dimension/strategy/chunk_data_write_asbyte.h"

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
			    bool asbyte,
				typename MasterServant,
				typename ChunkServant,
				typename ChunkFile,
				typename ChunkData,
				typename ChunkSize,
				typename RcfSystem = rcf_system<ChunkServant>::type,
				typename tag = typename tag<ChunkServant>::type
			>
			struct default_write_strategy
			{
			};

			/*!
			*
			**/
			template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename ChunkData, typename ChunkSize>
			struct default_write_strategy<false, MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize, deltasoft_tag, gfschunk_tag>
			{
				typedef typename strategy::chunk_data_write_asfile_logged type;
			};
			/*!
			*
			**/
			template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename ChunkData, typename ChunkSize>
			struct default_write_strategy<true, MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize, deltasoft_tag, gfschunk_tag>
			{
				typedef typename strategy::chunk_data_write_asbyte type;
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
				typename ChunkData,
				typename ChunkSize,
				typename Strategy,
				typename RcfSystem = typename rcf_system<ChunkServant>::type,
				typename tag = typename tag<ChunkServant>::type
			>
			struct gfs_chunk_data_write : detail::calculate_null
			{
				static inline std::vector<unsigned long long> apply(MasterServant const& masterservant, ChunkServant const& chunkservant, MasterFile const& masterfile, Strategy const& strategy)
				{
					return calculate_null::apply<std::vector<unsigned long long>>(masterservant, chunkservant, chunkfile, strategy);
				}
			};

			/*!
			*
			**/
			template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename ChunkData, typename ChunkSize, typename Strategy>
			struct gfs_chunk_data_write<MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize, Strategy, deltasoft_tag, gfschunk_tag>
			{
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, \
					ChunkData const& chunkdata, ChunkSize const& chunksize, Strategy const& strategy)
				{
					return strategy.apply(masterservant, chunkservant, chunkfile,chunkdata, chunksize);
				}
			};
		}

		// resolve kinds of strategy
		namespace resolve_strategy
		{
			/*!
			*
			**/
			struct gfs_chunk_data_write
			{
				template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename ChunkData, typename ChunkSize, typename Strategy>
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, \
					ChunkData const& chunkdata, ChunkSize const& chunksize,Strategy const& strategy)
				{
					return dispatch::gfs_chunk_data_write<MasterServant, ChunkServant, ChunkFile, Strategy>::apply(masterservant, chunkservant, chunkfile, chunkdata, chunksize, strategy);
				}

				template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename ChunkData, typename ChunkSize>
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, \
					ChunkData const& chunkdata, ChunkSize const& chunksize, default_strategy)
				{
					if(chunkdata.size())
					{
						typedef typename detail::default_write_strategy<true, MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize>::type strategy_type;
						return dispatch::gfs_chunk_data_write<MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize, strategy_type>::\
							apply(masterservant, chunkservant, chunkfile, chunkdata, chunksize, strategy_type());
					}
					else
					{
						typedef typename detail::default_write_strategy<false, MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize>::type strategy_type;
						return dispatch::gfs_chunk_data_write<MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize, strategy_type>::\
							apply(masterservant, chunkservant, chunkfile, chunkdata, chunksize, strategy_type());

					}
				}
			};
		}

		// resolve kinds of object
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename ChunkData, typename ChunkSize>
			struct gfs_chunk_data_write
			{
				template <typename Strategy>
				static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, \
					ChunkData const& chunkdata, ChunkSize const& chunksize, Strategy const& strategy)
				{
					return resolve_strategy::gfs_chunk_data_write::apply(masterservant, chunkservant, chunkfile, chunkdata, chunksize, strategy);
				}
			};

			// for other kinds of objects
			// ...
		}

		//
		/*!
		*
		**/
		template <typename MasterServant, typename ChunkServant, typename ChunkFile, typename ChunkData, typename ChunkSize, typename Strategy>
		inline typename bool gfs_chunk_data_write(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, \
			ChunkData const& chunkdata, ChunkSize const& chunksize, Strategy const& strategy)
		{
			return resolve_variant::gfs_chunk_data_write<MasterServant, ChunkServant, ChunkFile, ChunkData, ChunkSize>::apply(masterservant, chunkservant, chunkfile, chunkdata, chunksize, strategy);
		}
	}
}

#endif