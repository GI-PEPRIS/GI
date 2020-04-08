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

#ifndef ANYWAY_RCF_DIMENSION_JOB_REDUCER_START_DEFAULT_H
#define ANYWAY_RCF_DIMENSION_JOB_REDUCER_START_DEFAULT_H

#include "default_strategy.h"

namespace anyway
{
	namespace rcf
	{
		namespace detail
		{
			namespace strategy
			{
				//
				// services
				//
				struct job_reducer_start_default : public default_strategy
				{
					//
					template
					<
						typename JobReducer,
						typename JobParameter
					>
					static inline bool apply(JobReducer const& servant, JobParameter &parameter)
					{
						try
						{
							//
							typedef typename rcf_serviceimpl<JobReducer>::type TrackerServantImpl;
							TrackerServantImpl *reducer = servant.m_servant;
							assert(reducer);		

							reducer->ReduceStart();							
						}
						catch(...)
						{
							return false;
						}

						return true;
					}
				};
			}
		}
	}
}


#endif