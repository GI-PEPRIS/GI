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

#ifndef ANYWAY_RCF_MODEL_GFS_CHUNK_H
#define ANYWAY_RCF_MODEL_GFS_CHUNK_H

// refinement from
#include "generic programming/model/rcfservant.h"

//
#include "generic programming/core/tags.h"
#include "generic programming/core/tag.h"
#include "generic programming/core/rcf_system.h"
#include "generic programming/core/rcf_servicehandle.h"
#include "generic programming/core/rcf_serviceimpl.h"
#include "generic programming/core/gfs_localchunk.h"
#include "generic programming/core/gfs_masterchunk.h"
#include "generic programming/core/gfs_chunkdata.h"
#include "generic programming/core/gfs_chunksize.h"


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
				typename MasterChunk,		// meta record
				typename LocalChunk,		// local chunk file
				typename ChunkLocation,		// chunk server and its status
				typename ChunkData,
				typename ChunkSize,
				template<typename, typename, typename> class ParentServant = rcfservant
			>
			class gfschunk : public ParentServant<RcfSystem, RcfServiceHandle, RcfServant>
			{
			public:
				//
				explicit inline gfschunk()
				{
				}

				//
				~gfschunk()
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
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
			>
			struct tag<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
			{
				typedef gfschunk_tag type;
			};

			/*!
			* concept requirement 2: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
			>
			struct rcf_system<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
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
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
			>
			struct gfs_masterchunk<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
			{
				typedef MasterChunk type;
			};

			/*!
			* concept requirement 3: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
			>
			struct gfs_chunklocation<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
			{
				typedef ChunkLocation type;
			};

			/*!
			* concept requirement 4: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
			>
			struct rcf_servicehandle<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
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
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
			>
			struct rcf_serviceimpl<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
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
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
			>
			struct gfs_localchunk<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
			{
				typedef LocalChunk type;
			};

			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
				>
			struct gfs_chunkdata<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
			{
				typedef ChunkData type;
			};

			template
				<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename MasterChunk,
				typename LocalChunk,
				typename ChunkLocation,
				typename ChunkData,
				typename ChunkSize
				>
			struct gfs_chunksize<model::gfschunk<RcfSystem, RcfServiceHandle, RcfServant, MasterChunk, LocalChunk, ChunkLocation, ChunkData, ChunkSize> >
			{
				typedef ChunkSize type;
			};
		}
	}
}
#endif