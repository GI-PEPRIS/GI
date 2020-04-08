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

#ifndef ANYWAY_RCF_MODEL_RCF_SERVANT_H
#define ANYWAY_RCF_MODEL_RCF_SERVANT_H

// meta traits
#include "generic programming/core/rcf_system.h"
#include "generic programming/core/rcf_servicehandle.h"
#include "generic programming/core/rcf_serviceimpl.h"

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
				typename RcfServant	 // stub or skeleton 
			>
			class rcfservant
			{
			public:
				//
				explicit inline rcfservant() : m_servant(0), m_isrunning(true)
				{
				}

				//
				~rcfservant()
				{
					if(m_servant)
					{
						delete m_servant;
					}
				}

			public:
				// servant implementation
				RcfServant *m_servant;
				//
				RcfServiceHandle m_handle;
				//
				bool m_isrunning;
			};
		}

		//
		namespace traits
		{
			/*!
			* concept requirement 2: rcf system, namely open source adopted
			**/
			template
			<
				typename RcfSystem,
				typename RcfServiceHandle,
				typename RcfServant
			>
			struct rcf_system<model::rcfservant<RcfSystem, RcfServiceHandle, RcfServant> >
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
				typename RcfServant
			>
			struct rcf_servicehandle<model::rcfservant<RcfSystem, RcfServiceHandle, RcfServant> >
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
				typename RcfServant
			>
			struct rcf_serviceimpl<model::rcfservant<RcfSystem, RcfServiceHandle, RcfServant> >
			{
				typedef RcfServant type;
			};
		}
	}
}
#endif