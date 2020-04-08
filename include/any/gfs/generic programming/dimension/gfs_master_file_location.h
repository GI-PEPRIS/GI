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

#ifndef ANYWAY_RCF_DIMENSION_GFS_MASTER_FILE_LOCATION_H
#define ANYWAY_RCF_DIMENSION_GFS_MASTER_FILE_LOCATION_H

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
			struct deltasoft_gfs_master_file_location
			{
				template <typename Servant,typename MasterFile, typename LocationVector, typename Strategy>
				static inline void apply(Servant const& servant, MasterFile const& masterfile, LocationVector &locations, Strategy const& strategy)
				{
					typedef typename rcf_serviceimpl<Servant>::type ServantImpl;
					ServantImpl *impl = servant.m_servant;
					assert(impl);

					//if(impl->IsRunning())
					{
						impl->GetChunkServers(masterfile.m_filename, locations);
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
				typename MasterFile,
				typename LocationVector,
				typename RcfSystem = rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type
			>
			struct gfs_master_file_location : detail::calculate_null
			{
				template <typename Strategy>
				static inline void apply(Servant const& servant, MasterFile const& masterfile, LocationVector &locations, Strategy const& strategy)
				{
					return calculate_null::apply<bool>(servant, filenode, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Servant, typename MasterFile, typename LocationVector>
			struct gfs_master_file_location<Servant, MasterFile, LocationVector, deltasoft_tag, gfsmaster_tag> : detail::deltasoft_gfs_master_file_location
			{};
		}

		// resolve 
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Servant, typename MasterFile, typename LocationVector>
			struct gfs_master_file_location
			{
				template <typename Strategy>
				static inline void apply(Servant const& servant, MasterFile const &masterfile, LocationVector &locations, Strategy const& strategy)
				{
					return dispatch::gfs_master_file_location<Servant, MasterFile, LocationVector>::apply(servant, masterfile, locations, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename Servant, typename MasterFile, typename LocationVector, typename Strategy>
		inline typename void gfs_master_file_location(Servant const& servant, MasterFile const& masterfile, LocationVector &locations, Strategy const& strategy)
		{
			return resolve_variant::gfs_master_file_location<Servant, MasterFile, LocationVector>::apply(servant, masterfile, locations, strategy);
		}
	}
}

#endif