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

#ifndef ANYWAY_RCF_MODEL_GFS_MASTER_H
#define ANYWAY_RCF_MODEL_GFS_MASTER_H

// refinement from
#include "generic programming/model/rcfservant.h"

//
#include "generic programming/core/tags.h"
#include "generic programming/core/tag.h"
#include "generic programming/core/rcf_system.h"
#include "generic programming/core/gfs_metastorage.h"
#include "generic programming/core/rcf_servicehandle.h"
#include "generic programming/core/gfs_metanode.h"
#include "generic programming/core/gfs_metarecord.h"
#include "generic programming/core/rcf_serviceimpl.h"
#include "generic programming/core/gfs_masterfile.h"

namespace anyway
{ 
	namespace rcf
	{
		//
		namespace model
		{
			/*!
			*
			*/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile,
				template<typename, typename, typename> class ParentServant = rcfservant
			>
			class gfsmaster : public ParentServant<RcfSystem, RcfServiceHandle, RcfServant>
			{
			public:
				//
				explicit inline gfsmaster()
				{
				}

				//
				~gfsmaster()
				{
				}
			};
		}

		//
		namespace traits
		{
			/*!
			* concept requirement 1: tag, namely type of gfs node
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct tag<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef gfsmaster_tag type;
			};

			/*!
			* concept requirement 2: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct rcf_system<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef RcfSystem type;
			};

			/*!
			* concept requirement 3: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct gfs_metastorage<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef MetaStorage type;
			};

			/*!
			* concept requirement 4: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct rcf_servicehandle<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef RcfServiceHandle type;
			};

			/*!
			* concept requirement 4: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct gfs_metanode<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef MetaNode type;
			};

			/*!
			* concept requirement 4: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct gfs_metarecord<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef MetaRecord type;
			};

			/*!
			* concept requirement 4: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct rcf_serviceimpl<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef RcfServant type;
			};

			/*!
			* concept requirement 4: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MetaStorage,
				typename MetaNode,
				typename MetaRecord,
				typename MasterFile
			>
			struct gfs_masterfile<model::gfsmaster<RcfSystem, RcfServiceHandle, RcfServant, MetaStorage, MetaNode, MetaRecord, MasterFile> >
			{
				typedef MasterFile type;
			};
		}
	}
}
#endif