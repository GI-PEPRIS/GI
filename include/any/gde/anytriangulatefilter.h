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
#ifndef __ANYGDE_TRIANGULATE_FILTER_H__
#define __ANYGDE_TRIANGULATE_FILTER_H__

// refer to export/import macro
#include "anygde.h"

// refer to parent
#include "anygdedatahandler.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAnyTriangulateFilter : public CAnyGdeDataHandler
	{
	public:
		/*!
		*
		**/
		struct FilterParameter
		{
			// filter number
			int m_number;
			// filter width
			double m_width;
			// start frequency
			double m_start;
			// end frequency
			double m_end;

			// low and high frequence
			double m_lowFrom;
			double m_lowTo;
			double m_highFrom;
			double m_highTo;

			// main frequence against each filter
			std::vector<double> m_frequencies;

			// pre-process
			// slope
			bool m_isSloped;
			short m_slopePts;
			// correlation
			bool m_isAutoed;

			// sample interval
			double m_interval;

			/*!
			*
			**/
			FilterParameter() : m_number(100), m_width(10), m_start(0), m_end(120), m_isSloped(true), m_slopePts(5), m_isAutoed(true), m_interval(0.004), \
				m_lowFrom(m_start), m_lowTo(m_end), m_highFrom(m_start), m_highTo(m_end)
			{
			}

			/*!
			*
			**/
			FilterParameter(const FilterParameter &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const FilterParameter &operator=(const FilterParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// filter number
				m_number = other.m_number;
				// filter width
				m_width = other.m_width;
				// start frequency
				m_start = other.m_start;
				// end frequency
				m_end = other.m_end;

				// low and high frequence
				m_lowFrom = other.m_lowFrom;
				m_lowTo = other.m_lowTo;
				m_highFrom = other.m_highFrom;
				m_highTo = other.m_highTo;

				// pre-process
				// slope
				m_isSloped = other.m_isSloped;
				m_slopePts = other.m_slopePts;
				// correlation
				m_isAutoed = other.m_isAutoed;

				//
				m_frequencies.clear();
				m_frequencies.assign(other.m_frequencies.begin(), other.m_frequencies.end());

				// sample interval
				m_interval = other.m_interval;

				return *this;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyTriangulateFilter();

		/*!
		*
		**/
		~CAnyTriangulateFilter();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetParameter(const FilterParameter &parameter);

		/*!
		*
		**/
		const FilterParameter &GetParameter();

		/*!
		*
		**/
		int GetFilterOrder(double frequency);

		/*!
		*
		**/
		double GetFilterFrequency(int whichfilter)
		{
			assert(whichfilter >= 0 && whichfilter < m_parameter.m_frequencies.size());
			return m_parameter.m_frequencies[whichfilter];
		}

		//
		//
		//
		/*!
		*
		**/
		void DoHandle(CAnyGdeDataHandler::HandlerStruct &handlerstruct);

		/*!
		*
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		*
		**/
		void DoGetTraceHead(std::vector<double> &results);

		//
		//
		//
		/*!
		*
		**/
		void GetResults(int whichfilter, std::vector<double> &results);

		/*!
		*
		**/
		void MakeCompensate(double fStart, double fEnd, double hValue, double lValue, bool isLow);

		//
		//
		//
		/*!
		*
		**/
		double GetResultMax(int whichfilter);

		/*!
		*
		**/
		double GetResultMax();

		/*!
		*
		**/
		double GetResultAvg(int whichfilter);

		/*!
		*
		**/
		double GetResultAvg();

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoDealWithSlope();

		/*!
		*
		**/
		void DoDealWithCorrelation();

	public:
		//
		FilterParameter m_parameter;
		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;

		std::vector<float> m_fHf;
		std::vector<float> m_z;
	};
}
#endif