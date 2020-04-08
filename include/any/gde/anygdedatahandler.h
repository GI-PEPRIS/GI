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
#ifndef __ANYGDE_DATA_ALGORITHM_HANDLER_H__
#define __ANYGDE_DATA_ALGORITHM_HANDLER_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatagate.h"

// refer to vector
#include "any/base/anystl.h"

namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeDataHandler
	{
	public:
		//
		struct HandlerStruct
		{
			CAnyGdeDataTrace *m_trace;
			std::vector<CAnyGdeDataTrace*> m_othertraces;
			CAnyGdeDataGate::SurveyInfo &m_survey;
			int &m_threadoffset;
			std::vector<CAnyGdeDataTrace*> m_supertrace;

			/*!
			*
			**/
			HandlerStruct(CAnyGdeDataTrace *trace, CAnyGdeDataGate::SurveyInfo &survey, int &threadoffset) : \
				m_trace(trace), m_survey(survey), m_threadoffset(threadoffset)
			{
			}

			/*!
			*
			**/
			HandlerStruct(CAnyGdeDataTrace *trace, CAnyGdeDataGate::SurveyInfo &survey, int &threadoffset, std::vector<CAnyGdeDataTrace*> &supertrace) : \
				m_trace(trace), m_survey(survey), m_threadoffset(threadoffset), m_supertrace(supertrace)
			{
			}

			/*!
			*
			**/
			HandlerStruct(CAnyGdeDataTrace *trace, std::vector<CAnyGdeDataTrace*> othertraces, CAnyGdeDataGate::SurveyInfo &survey, int &threadoffset, std::vector<CAnyGdeDataTrace*> &supertrace) : \
				m_trace(trace), m_othertraces(othertraces), m_survey(survey), m_threadoffset(threadoffset), m_supertrace(supertrace)
			{
			}
		};

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataHandler()
		{
		}

		/*!
		*
		**/
		virtual ~CAnyGdeDataHandler()
		{
		}

	public:
		//
		//
		//
		/*!
		* HFT_Generic
		**/
		virtual void DoHandle(HandlerStruct &handlerstruct) = 0;

		/*!
		* calculation results
		**/
		virtual void DoGetTraceSample(std::vector<double> &results, int &cmpcount) = 0;

		/*!
		* calculation meta data for future explanation
		**/
		virtual void DoGetTraceHead(std::vector<double> &results) = 0;

	protected:
		// samples 
		std::vector<double> m_samples;
		// middle results
		std::vector<std::vector<double> > m_results;
	};

}
#endif