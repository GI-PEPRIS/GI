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

#ifndef ANYWAY_RCF_DIMENSION_gfs_MASTER_META_LOOKUP_H
#define ANYWAY_RCF_DIMENSION_gfs_MASTER_META_LOOKUP_H

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
			struct deltasoft_gfs_master_meta_lookup
			{
				template <typename Servant, typename MetaNode, typename ChildrenNode, typename Strategy>
				static inline int apply(Servant const& servant, MetaNode const& metanode, ChildrenNode &children, Strategy const&)
				{
					typedef typename rcf_serviceimpl<Servant>::type ServantImpl;
					ServantImpl *impl = servant.m_servant;
					assert(impl);

					//if(!impl->IsRunning())
					{
						children = impl->Lookup(metanode.m_name, metanode.m_type);
						return children.size();
					}

					return 0;
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
				typename MetaNode,
				typename ChildrenNode,
				typename RcfSystem = rcf_system<Servant>::type,
				typename tag = typename tag<Servant>::type
			>
			struct gfs_master_meta_lookup : detail::calculate_null
			{
				template <typename Strategy>
				static inline int apply(Servant const& servant, MetaNode const& MetaNode, ChildrenNode &children, Strategy const& strategy)
				{
					return calculate_null::apply<bool>(servant, metanode, children, strategy);
				}
			};

			/*!
			*
			**/
			template <typename Servant, typename MetaNode, typename ChildrenNode>
			struct gfs_master_meta_lookup<Servant, MetaNode, ChildrenNode, deltasoft_tag, gfsmaster_tag> : detail::deltasoft_gfs_master_meta_lookup
			{};
		}

		//
		namespace resolve_variant
		{
			/*!
			*
			**/
			template <typename Servant, typename MetaNode, typename ChildrenNode>
			struct gfs_master_meta_lookup
			{
				template <typename Strategy>
				static inline int apply(Servant const& servant, MetaNode const &metanode, ChildrenNode &children, Strategy const& strategy)
				{
					return dispatch::gfs_master_meta_lookup<Servant, MetaNode, ChildrenNode>::apply(servant, metanode, children, strategy);
				}
			};
		}

		//
		/*!
		*
		**/
		template <typename Servant, typename MetaNode, typename ChildrenNode, typename Strategy>
		inline typename int gfs_master_meta_lookup(Servant const& servant, MetaNode const &metanode, ChildrenNode &children, Strategy const& strategy)
		{
			return resolve_variant::gfs_master_meta_lookup<Servant, MetaNode, ChildrenNode>::apply(servant, metanode, children, strategy);
		}
	}
}

#endif