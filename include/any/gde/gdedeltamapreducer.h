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
#ifndef __ANYRCF_GDE_MAP_REDUCE_DEF_H__
#define __ANYRCF_GDE_MAP_REDUCE_DEF_H__

#include <winsock2.h>

// refer to EXPORT & IMPORT
#include "anygde.h"

//
#include "gdetaskbasic.h"
#include "gdemapreducerstub.h"
#ifdef COMPILE_Slice
#include "gdeslicetaskservant.h"
#endif
#ifdef COMPILE_Triangulate
#include "gdetrianglefiltertaskservant.h"
#endif
#ifdef COMPILE_Instant
#include "gdeinstantattributetaskservant.h"
#endif
#ifdef COMPILE_DipAzimuth
#include "gdedipazimuthtaskservant.h"
#endif
#ifdef COMPILE_AlphaFilter
#include "gdealphafiltertaskservant.h"
#endif
#ifdef COMPILE_Irregular
#include "gdeirregulartaskservant.h"
#endif
#ifdef COMPILE_Ellipse
#include "gdeellipsetaskservant.h"
#endif
#ifdef COMPILE_ThreeBayes
#include "gdethreebayestaskservant.h"
#endif
#ifdef COMPILE_BasicTrack
#include "gdebasictracktaskservant.h"
#endif
#ifdef COMPILE_RockPhysics
#include "gderockphysicstaskservant.h"
#endif
#ifdef COMPILE_Brick
#include "gdebricktaskservant.h"
#endif
#ifdef COMPILE_Conherency
#include "gdeconherencytaskservant.h"
#endif

// rcf package
#include "any/gfs/deltagfsreactor.h"
#include "any/gfs/anymapreducer.h"
#include "any/gfs/generic programming/model/jobtracker.h"
#include "any/gfs/generic programming/model/jobmapper.h"
#include "any/gfs/generic programming/model/jobreducer.h"
using namespace anyway::rcf;
using namespace anyway::rcf::model;

//
// delta soft solution
#include "any/gfs/anyservicebasic.h"
#include "any/gfs/eventstub.h"
#include "any/gfs/gfsjobstub.h"
#include "any/gfs/gfstaskstub.h"

//
namespace AnyGDE
{
	// kinds of traits
	typedef jobtracker<deltasoft_tag, AnyRCF::ServiceHandle, CGFSJobStub, CDeltaGfsReactor, AnyRCF::JobSpecification, GdeJobParameter> Gde_DeltaJobTracker;
#ifdef COMPILE_Slice
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeSliceTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_Slice_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeSliceTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_Slice_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_Slice_DeltaJobMapper, Gde_Slice_DeltaJobReducer> CGdeSliceDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_Slice_DeltaJobMapper, Gde_Slice_DeltaJobReducer>;
#endif
#ifdef COMPILE_Triangulate
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeTriangleFilterTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_TriangleFilter_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeTriangleFilterTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_TriangleFilter_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_TriangleFilter_DeltaJobMapper, Gde_TriangleFilter_DeltaJobReducer> CGdeTriangleFilterDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_TriangleFilter_DeltaJobMapper, Gde_TriangleFilter_DeltaJobReducer>;
#endif
#ifdef COMPILE_Instant
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeInstantAttributeTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_InstantAttribute_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeInstantAttributeTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_InstantAttribute_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_InstantAttribute_DeltaJobMapper, Gde_InstantAttribute_DeltaJobReducer> CGdeInstantAttributeDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_InstantAttribute_DeltaJobMapper, Gde_InstantAttribute_DeltaJobReducer>;
#endif
#ifdef COMPILE_DipAzimuth
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeDipAzimuthTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_DipAzimuth_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeDipAzimuthTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_DipAzimuth_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_DipAzimuth_DeltaJobMapper, Gde_DipAzimuth_DeltaJobReducer> CGdeDipAzimuthDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_DipAzimuth_DeltaJobMapper, Gde_DipAzimuth_DeltaJobReducer>;
#endif
#ifdef COMPILE_AlphaFilter
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeAlphaFilterTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_AlphaFilter_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeAlphaFilterTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_AlphaFilter_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_AlphaFilter_DeltaJobMapper, Gde_AlphaFilter_DeltaJobReducer> CGdeAlphaFilterDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_AlphaFilter_DeltaJobMapper, Gde_AlphaFilter_DeltaJobReducer>;
#endif
#ifdef COMPILE_Irregular
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeIrregularTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_Irregular_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeIrregularTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_Irregular_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_Irregular_DeltaJobMapper, Gde_Irregular_DeltaJobReducer> CGdeIrregularDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_Irregular_DeltaJobMapper, Gde_Irregular_DeltaJobReducer>;
#endif
#ifdef COMPILE_Ellipse
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeEllipseTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_Ellipse_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeEllipseTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_Ellipse_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_Ellipse_DeltaJobMapper, Gde_Ellipse_DeltaJobReducer> CGdeEllipseDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_Ellipse_DeltaJobMapper, Gde_Ellipse_DeltaJobReducer>;
#endif
#ifdef COMPILE_ThreeBayes
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeThreeBayesTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_ThreeBayes_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeThreeBayesTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_ThreeBayes_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_ThreeBayes_DeltaJobMapper, Gde_ThreeBayes_DeltaJobReducer> CGdeThreeBayesDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_ThreeBayes_DeltaJobMapper, Gde_ThreeBayes_DeltaJobReducer>;
#endif	
#ifdef COMPILE_BasicTrack
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeBasicTrackTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_BasicTrack_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeBasicTrackTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_BasicTrack_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_BasicTrack_DeltaJobMapper, Gde_BasicTrack_DeltaJobReducer> CGdeBasicTrackDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_BasicTrack_DeltaJobMapper, Gde_BasicTrack_DeltaJobReducer>;
#endif	
#ifdef COMPILE_RockPhysics
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeRockPhysicsTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_RockPhysics_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeRockPhysicsTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_RockPhysics_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_RockPhysics_DeltaJobMapper, Gde_RockPhysics_DeltaJobReducer> CGdeRockPhysicsDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_RockPhysics_DeltaJobMapper, Gde_RockPhysics_DeltaJobReducer>;
#endif	
#ifdef COMPILE_Brick
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeBrickTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_Brick_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeBrickTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_Brick_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_Brick_DeltaJobMapper, Gde_Brick_DeltaJobReducer> CGdeBrickDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_Brick_DeltaJobMapper, Gde_Brick_DeltaJobReducer>;
#endif	
#ifdef COMPILE_Conherency
	typedef jobmapper<deltasoft_tag, AnyRCF::ServiceHandle, CGdeConherencyTaskStub, JobTaskServer, GdeMapKey, GdeMapValue> Gde_Conherency_DeltaJobMapper;
	typedef jobreducer<deltasoft_tag, AnyRCF::ServiceHandle, CGdeConherencyTaskStub, JobTaskServer, GdeReduceKey, GdeReduceValue> Gde_Conherency_DeltaJobReducer;
	typedef CAnyMapReducer<Gde_DeltaJobTracker, Gde_Conherency_DeltaJobMapper, Gde_Conherency_DeltaJobReducer> CGdeConherencyDeltaMapReducer;
	template class ANYGDE_CLASS CAnyMapReducer<Gde_DeltaJobTracker, Gde_Conherency_DeltaJobMapper, Gde_Conherency_DeltaJobReducer>;
#endif
}
#endif