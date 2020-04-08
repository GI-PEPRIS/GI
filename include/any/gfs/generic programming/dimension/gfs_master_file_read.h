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

#ifndef ANYWAY_RCF_DIMENSION_MASTER_FILE_READ_H
#define ANYWAY_RCF_DIMENSION_MASTER_FILE_READ_H

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
			struct deltasoft_gfs_master_file_read
			{
				template <typename Servant, typename ChunkFile, typename ChunkVector, typename Strategy>
				static inline unsigned long long apply(Servant const& servant, ChunkFile const& chunkfile, ChunkVector &chunklocations, Strategy const& strategy)
				{
					typedef typename rcf_serviceimpl<Servant>::type ServantImpl;
					ServantImpl *impl = servant.m_servant;
					assert(impl);
					//if(!impl->IsRunning())
					{
						return impl->Chunk4Read(chunkfile.m_gfsfile, chunkfile.m_chunkindex, chunklocations);
					}
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
				typename Servant,
				typename ChunkFile,
				typename ChunkVector,
				typename RcfSystem = rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type
			>
			struct gfs_master_file_read : detail::calculate_null
			{
				template <typename Strategy>
				static inline unsigned long long apply(Servant const& servant, ChunkFile const& chunkfile, ChunkVector &chunklocations, Strategy const& strategy)
				{
					return calculate_null::apply<bool>(servant, chunkfile, chunklocations, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Servant, typename ChunkFile, typename ChunkVector>
			struct gfs_master_file_read<Servant, ChunkFile, ChunkVector, deltasoft_tag, gfsmaster_tag> : detail::deltasoft_gfs_master_file_read
			{};
		}

		// resolve 
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Servant, typename ChunkFile, typename ChunkVector>
			struct gfs_master_file_read
			{
				template <typename Strategy>
				static inline unsigned long long apply(Servant const& servant, ChunkFile const& chunkfile, ChunkVector &chunklocations, Strategy const& strategy)
				{
					return dispatch::gfs_master_file_read<Servant, ChunkFile, ChunkVector>::apply(servant, chunkfile, chunklocations, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename Servant, typename ChunkFile, typename ChunkVector, typename Strategy>
		inline typename unsigned long long gfs_master_file_read(Servant const& servant, ChunkFile const& chunkfile, ChunkVector &chunklocations, Strategy const& strategy)
		{
			return resolve_variant::gfs_master_file_read<Servant, ChunkFile, ChunkVector>::apply(servant, chunkfile, chunklocations, strategy);
		}
	}
}

#endif