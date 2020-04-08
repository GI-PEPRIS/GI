/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_LOG_DATA_ACCESSOR_H__
#define __ANYBRIDGE_LOG_DATA_ACCESSOR_H__

// refer to EXPORT and IMPORT
#include "anybridge.h"

// refer to datamodel
#include "anybridgedatamodel.h"

#include "any/base/anystl.h"

//
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CLogDataAccessor
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CLogDataAccessor();
		
		/*!
		*
		**/
		~CLogDataAccessor();

	public:
		
		//
		//
		//
		/*!
		*
		**/
		void LoadLogTrace(const std::string &itemname, int boreid, bool is_load_db = true);

		/*!
		*
		**/
		bool DoLoadLogTrace(const std::string &itemname, AnyWellLogTrace &logtrace, int boreid);

		/*!
		*
		**/
		void DoLoadLogTrace_PlotSetting(CAnyAccessor &accessor, const std::string &itemname, AnyWellLogTrace &logtrace, int boreid);

		//
		//
		//
		/*!
		*
		**/
		bool DoSaveLogTrace(const std::string &itemname, AnyWellLogTrace &logtrace, int boreid, const std::vector<int> &lengths, \
			const std::vector<int> &lengths_traceids, std::map<long,bool> &exist_traceid_map);

		/*!
		*
		**/
		void DoSaveLogTrace_PlotSetting(CAnyAccessor &accessor, const std::string &itemname, AnyWellLogTrace &logtrace, int boreid, const std::vector<int> &lengths);


		/*!
		*
		**/
		void ReleaseLogTrace(long boreid = -1);

		/*!
		*
		**/
		void GetSamplesByTraceIds(const std::string &welltype, const std::string &itemname, long boreid, const std::vector<int> &traceids, std::vector<AnyTraceDescription> &alldescriptions, std::vector<AnyTraceSample> &allsamples);

		/*!
		*
		**/
		void LoadAllLogTraceNames(const std::string &itemname, std::vector<std::string> &tracenames, std::vector<std::string> &aliastracenames);
		void LoadAllLogTraceNames(const std::string &itemname, std::vector<std::string> &tracenames, std::vector<std::string> &aliastracenames, \
			std::vector<std::string> &units, bool is_tracename_first = true, const std::vector<long> &boreids = std::vector<long>());

		/*!
		*
		**/
		void UpdateLogTraceNames(const std::string &itemname, std::vector<std::string> &tracenames, std::vector<std::string> &aliastracenames, std::vector<std::string> &tracenames_new, \
			std::vector<std::string> &units_old, std::vector<std::string> &units_new);

	public:
		
		//table nick name
		std::string m_item_name;

		//map: bore id - log trace
		std::map<long, AnyWellLogTrace> m_boreid_logtrace_map;
	};
}

#endif
