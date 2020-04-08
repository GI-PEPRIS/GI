/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYRCF_META_PROGRAMMING_DELTA_JOB_MAP_REDUCER_H__
#define __ANYRCF_META_PROGRAMMING_DELTA_JOB_MAP_REDUCER_H__

// refer to EXPORT & IMPORT
#include "anyrcf.h"

//
#include "anymapreducer.h"
#include "deltagfsreactor.h"
#include "gfstaskstub.h"

//
#include ".\generic programming\model\jobtracker.h"
#include ".\generic programming\model\jobmapper.h"
#include ".\generic programming\model\jobreducer.h"
using namespace anyway::rcf;
using namespace anyway::rcf::model;

//
// delta soft solution
#include "anyservicebasic.h"
#include "eventstub.h"
#include "gfsjobstub.h"
#include "gfschunkstub.h"

//
namespace AnyRCF
{
	// kinds of traits
	typedef jobtracker<deltasoft_tag, ServiceHandle, CGFSJobStub, CDeltaGfsReactor, JobSpecification, JobParameter> DeltaJobTracker;
	typedef jobmapper<deltasoft_tag, ServiceHandle, CGFSTaskStub, JobTaskServer, MapKey, MapValue> DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, ServiceHandle, CGFSTaskStub, JobTaskServer, ReduceKey, ReduceValue> DeltaJobReducer;
	typedef CAnyMapReducer<DeltaJobTracker, DeltaJobMapper, DeltaJobReducer> CDeltaMapReducer;

	//
	template class ANYRCF_CLASS CAnyMapReducer<DeltaJobTracker, DeltaJobMapper, DeltaJobReducer>;

}
#endif
