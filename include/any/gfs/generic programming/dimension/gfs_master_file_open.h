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

#ifndef ANYWAY_RCF_DIMENSION_GFS_MASTER_FILE_OPEN_H
#define ANYWAY_RCF_DIMENSION_GFS_MASTER_FILE_OPEN_H

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
			struct deltasoft_gfs_master_open_file
			{
				template <typename Servant,typename FileNode, typename Strategy>
				static inline bool apply(Servant const& servant, FileNode const& filenode, Strategy const& strategy)
				{
					typedef typename rcf_serviceimpl<Servant>::type ServantImpl;
					ServantImpl *impl = servant.m_servant;
					assert(impl);

					//if(impl->IsRunning())
					{
						impl->Open(filenode);
						return true;
					}

					return false;
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
				typename FileNode,
				typename RcfSystem = rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type
			>
			struct gfs_master_file_open : detail::calculate_null
			{
				template <typename Strategy>
				static inline bool apply(Servant const& servant, FileNode const& filenode, Strategy const& strategy)
				{
					return calculate_null::apply<bool>(servant, filenode, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Servant, typename FileNode>
			struct gfs_master_file_open<Servant, FileNode, deltasoft_tag, gfsmaster_tag> : detail::deltasoft_gfs_master_open_file
			{};
		}

		// resolve 
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Servant, typename FileNode>
			struct gfs_master_file_open
			{
				template <typename Strategy>
				static inline bool apply(Servant const& servant, FileNode const &filenode, Strategy const& strategy)
				{
					return dispatch::gfs_master_file_open<Servant, FileNode>::apply(servant, filenode, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename Servant, typename FileNode, typename Strategy>
		inline typename bool gfs_master_file_open(Servant const& servant, FileNode const& filenode, Strategy const& strategy)
		{
			return resolve_variant::gfs_master_file_open<Servant, FileNode>::apply(servant, filenode, strategy);
		}
	}
}

#endif