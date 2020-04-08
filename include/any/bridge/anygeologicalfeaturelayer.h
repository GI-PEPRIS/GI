/*!
 * The ANYBRIDGE of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYBRIDGE_em_GEOLOGICAL_FEATURE_LAYER_H__
#define __ANYBRIDGE_em_GEOLOGICAL_FEATURE_LAYER_H__

// refer to EXPORT & IMPORT
#include "anybridge.h"
#include "anytokenizer.h"

// refer to parent class
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// namespace
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyGeologicalFeatureLayer : public CAnyViewHook, public CAnyTokenizer
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGeologicalFeatureLayer(long layerIdx, CAnyView &view, const string &fileName, const string &featureTable, \
			const string &geometryTable, const string &indexTable, const string &configureTable, long elementIdx = 0);

		/*!
		*
		**/
		~CAnyGeologicalFeatureLayer();

	public:
		//
		// from TOKENIZER
		//
		/*!
		*
		**/
		int Extract(long elementid, long classid, int num = 0, int startline = 0, int endline = -1);

		//
		// inherited interface from VIEWHOOK
		//

	public:
		// geological feature type
		short m_featureType;	// CFK_Horizon or CFK_Fault or CFK_Interval
	};
}

#endif
