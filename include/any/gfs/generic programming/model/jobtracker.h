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

#ifndef ANYWAY_RCF_MODEL_JOB_TRACKER_H
#define ANYWAY_RCF_MODEL_JOB_TRACKER_H

// refinement from
#include "generic programming/model/rcfservant.h"

//
#include "generic programming/core/tags.h"
#include "generic programming/core/tag.h"
#include "generic programming/core/job_gfsfile.h"
#include "generic programming/core/job_specification.h"

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
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter,
				template<typename, typename, typename> class ParentServant = rcfservant
			>
			class jobtracker : public ParentServant<RcfSystem, RcfServiceHandle, RcfServant>
			{
			public:
				//
				explicit inline jobtracker()
				{
				}

				//
				~jobtracker()
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
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter
			>
			struct tag<model::jobtracker<RcfSystem, RcfServiceHandle, RcfServant, JobGFS, JobSpecification, JobParameter> >
			{
				typedef job_tracker_tag type;
			};

			/*!
			* concept requirement 2: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter
			>
			struct rcf_system<model::jobtracker<RcfSystem, RcfServiceHandle, RcfServant, JobGFS, JobSpecification, JobParameter> >
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
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter
			>
			struct rcf_servicehandle<model::jobtracker<RcfSystem, RcfServiceHandle, RcfServant, JobGFS, JobSpecification, JobParameter> >
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
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter
			>
			struct rcf_serviceimpl<model::jobtracker<RcfSystem, RcfServiceHandle, RcfServant, JobGFS, JobSpecification, JobParameter> >
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
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter
			>
			struct job_gfsfile<model::jobtracker<RcfSystem, RcfServiceHandle, RcfServant, JobGFS, JobSpecification, JobParameter> >
			{
				typedef JobGFS type;
			};

			/*!
			*
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter
			>
			struct job_specification<model::jobtracker<RcfSystem, RcfServiceHandle, RcfServant, JobGFS, JobSpecification, JobParameter> >
			{
				typedef JobSpecification type;
			};

			/*!
			*
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant,
				typename JobGFS,
				typename JobSpecification,
				typename JobParameter
			>
			struct job_parameter<model::jobtracker<RcfSystem, RcfServiceHandle, RcfServant, JobGFS, JobSpecification, JobParameter> >
			{
				typedef JobParameter type;
			};
		}
	}
}
#endif