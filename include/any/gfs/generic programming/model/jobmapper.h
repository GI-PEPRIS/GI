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

#ifndef ANYWAY_RCF_MODEL_JOB_MAPPER_H
#define ANYWAY_RCF_MODEL_JOB_MAPPER_H

// refinement from
#include "generic programming/model/rcfservant.h"

//
#include "generic programming/core/tags.h"
#include "generic programming/core/tag.h"

// traits
#include "generic programming/core/job_mapkey.h"
#include "generic programming/core/job_mapvalue.h"
#include "generic programming/core/task_specification.h"

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
				typename TaskSpecification,
				typename MapKey,
				typename MapValue,
				template<typename, typename, typename> class ParentServant = rcfservant
			>
			class jobmapper : public ParentServant<RcfSystem, RcfServiceHandle, RcfServant>
			{
			public:
				//
				explicit inline jobmapper()
				{
				}

				//
				~jobmapper()
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
				typename TaskSpecification,
				typename MapKey,
				typename MapValue
			>
			struct tag<model::jobmapper<RcfSystem, RcfServiceHandle, RcfServant, TaskSpecification, MapKey, MapValue> >
			{
				typedef job_mapper_tag type;
			};

			/*!
			* concept requirement 2: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename TaskSpecification,
				typename MapKey,
				typename MapValue
			>
			struct rcf_system<model::jobmapper<RcfSystem, RcfServiceHandle, RcfServant, TaskSpecification, MapKey, MapValue> >
			{
				typedef RcfSystem type;
			};

			/*!
			* concept requirement 4: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename TaskSpecification,
				typename MapKey,
				typename MapValue
			>
			struct rcf_servicehandle<model::jobmapper<RcfSystem, RcfServiceHandle, RcfServant, TaskSpecification, MapKey, MapValue> >
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
				typename TaskSpecification,
				typename MapKey,
				typename MapValue
			>
			struct rcf_serviceimpl<model::jobmapper<RcfSystem, RcfServiceHandle, RcfServant, TaskSpecification, MapKey, MapValue> >
			{
				typedef RcfServant type;
			};

			/*!
			*
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename TaskSpecification,
				typename MapKey,
				typename MapValue
			>
			struct job_mapkey<model::jobmapper<RcfSystem, RcfServiceHandle, RcfServant, TaskSpecification, MapKey, MapValue> >
			{
				typedef MapKey type;
			};

			/*!
			*
			**/
			template
			<
			typename RcfSystem,
			typename RcfServiceHandle,
			typename RcfServant,
			typename TaskSpecification,
			typename MapKey,
			typename MapValue
			>
			struct job_mapvalue<model::jobmapper<RcfSystem, RcfServiceHandle, RcfServant, TaskSpecification, MapKey, MapValue> >
			{
				typedef MapValue type;
			};

			/*!
			*
			**/
			template
			<
			typename RcfSystem,
			typename RcfServiceHandle,
			typename RcfServant,
			typename TaskSpecification,
			typename MapKey,
			typename MapValue
			>
			struct task_specification<model::jobmapper<RcfSystem, RcfServiceHandle, RcfServant, TaskSpecification, MapKey, MapValue> >
			{
				typedef TaskSpecification type;
			};
		}
	}
}
#endif