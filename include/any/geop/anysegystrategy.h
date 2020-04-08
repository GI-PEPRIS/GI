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
#ifndef __ANYGEOP_SEGY_STRATEGY_H__
#define __ANYGEOP_SEGY_STRATEGY_H__

// refer to macro
#include "anygeop.h"

// refer to TraceRecord & SurveyPoint
#include "anysegylayer.h"

#include "any/gde/anygdedatagate.h"
using namespace AnyGDE;
// geographic namespace
namespace AnyGeoP
{
	/*!
	*
	**/
	class ANYGEOP_CLASS CAnySegyStrategy
	{
		// relatives
		friend class CAnySegyProfile;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySegyStrategy();

		/*!
		*
		**/
		~CAnySegyStrategy();

	protected:
		//
		//
		//
		/*!
		*
		**/
		void SetGate(CAnySegyFile *gate)
		{
			m_gate = gate;
		}

		//
		//
		//
		/*!
		*
		**/
		void MakeAutoGain(const CAnySegyLayer::SurveyPoint &traceOrder, CAnyGdeDataGate::TraceRecord* traceRecord);

		/*!
		*
		**/
		void MakeExpGain(const CAnySegyLayer::SurveyPoint &traceOrder, CAnyGdeDataGate::TraceRecord* traceRecord);

		/*!
		*
		**/
		void MakeScaleGain(CAnyGdeDataGate::TraceRecord* traceRecord, double scale);

		//
		//
		//
		/*!
		*
		**/
		void MakeMedianFilter(const CAnySegyLayer::SurveyPoint &traceOrder, CAnyGdeDataGate::TraceRecord* traceRecord);

		/*!
		*
		**/
		void MakeFFTFilter(const CAnySegyLayer::SurveyPoint &traceOrder, CAnyGdeDataGate::TraceRecord* traceRecord);

	private:
		// dataset
		CAnySegyFile *m_gate;
		// current trace order
		CAnySegyLayer::SurveyPoint m_traceOrder;
	};
}

#endif