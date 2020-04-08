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

#ifndef ANYWAY_RCF_DIMENSION_gfs_master_meta_load_H
#define ANYWAY_RCF_DIMENSION_gfs_master_meta_load_H

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
			struct deltasoft_gfs_master_load_meta
			{
				template <typename Servant, typename MetaConnection, typename Namespace, typename Strategy>
				static inline int apply(Servant const& servant, MetaConnection const& connection, Namespace &files, Strategy const&)
				{
					typedef typename rcf_serviceimpl<Servant>::type ServantImpl;
					ServantImpl *impl = servant.m_servant;
					assert(impl);

					//if(impl->IsRunning())
					{
						// short type, const std::string &srcname, const std::string &user, const std::string &pwd, const std::string &dbname
						//impl->InitDB(connection.m_type, connection.m_srcName, connection.m_user, connection.m_pwd, connection.m_dbName);
						impl->LoadMetaRecords(false);
						impl->GetMasterNamespace(files);

						return files.size();
					}
					return 0.;
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
				typename Servant,
				typename MetaConnection,
				typename Namespace,
				typename RcfSystem = rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type
			>
			struct gfs_master_meta_load : detail::calculate_null
			{
				template <typename Strategy>
				static inline int apply(Servant const& servant, MetaConnection const& connection, Namespace &files, Strategy const& strategy)
				{
					return calculate_null::apply<bool>(servant, connection, files, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Servant, typename MetaConnection, typename Namespace>
			struct gfs_master_meta_load<Servant, MetaConnection, Namespace, deltasoft_tag, gfsmaster_tag> : detail::deltasoft_gfs_master_load_meta
			{};
		}

		//
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Servant, typename MetaConnection, typename Namespace>
			struct gfs_master_meta_load
			{
				template <typename Strategy>
				static inline int apply(Servant const& servant, MetaConnection const &connection, Namespace &files, Strategy const& strategy)
				{
					return dispatch::gfs_master_meta_load<Servant, MetaConnection, Namespace>::apply(servant, connection, files, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename Servant, typename MetaConnection, typename Namespace, typename Strategy>
		inline typename int gfs_master_meta_load(Servant const& servant, MetaConnection const &connection, Namespace &files, Strategy const& strategy)
		{
			return resolve_variant::gfs_master_meta_load<Servant, MetaConnection, Namespace>::apply(servant, connection, files, strategy);
		}
	}
}

#endif