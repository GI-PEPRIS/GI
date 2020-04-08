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
#ifndef __ANYGDE_SAMPLE_DATA_SURVEY_ITERATOR_H__
#define __ANYGDE_SAMPLE_DATA_SURVEY_ITERATOR_H__

// refer to EXPORT & IMPORT
#include "anygde.h"

// refer to stl
#include "any/base/anystl.h"

//
namespace AnyGDE
{
	// forward class
	class CAnyGdeDataSurvey;

	/*!
	* in sequence order
	**/
	class ANYGDE_CLASS CAnyGdeDataIterator
	{
		//
		friend class CAnyGdeDataSurvey;
		friend class CAnyGdeDataLineSurvey;
		friend class CAnyGdeDataGridSurvey;
		friend class CAnyGdeDataPolySurvey;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataIterator(CAnyGdeDataSurvey *survey);

		/*!
		*
		**/
		~CAnyGdeDataIterator();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Prepare();

		/*!
		*
		**/
		void Prepare(const std::vector<long> &sequenceOrders);

		/*!
		*
		**/
		bool GetNextSurveyNo(double &xLine, double inLine);

		/*!
		*
		**/
		bool GetNextSequenceOrder(long &sequenceOrder);

	protected:
		// host CDP survey
		CAnyGdeDataSurvey *m_survey;

		// indices
		std::vector<long> m_sequenceOrders;
		long m_sequenceCursor;
	};
}
#endif