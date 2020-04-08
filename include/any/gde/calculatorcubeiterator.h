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
#ifndef __ANYGDE_SAMPLE_DATA_CALCULATOR_CUBE__ITERATOR_H__
#define __ANYGDE_SAMPLE_DATA_CALCULATOR_CUBE__ITERATOR_H__

// refer to EXPORT & IMPORT
#include "anygde.h"

// refer to cursor cube
#include "calculatorcube.h"

// refer to horizon sample vector
#include "any/bridge/anygeologicalcubefeature.h"
using namespace AnyBridge;

//
namespace AnyGDE
{
	// forward classes
	class CAnyGdeDataGridSurvey;
	class CalculatorCube;

	/*!
	*
	**/
	template<typename CubeGate, typename CubeSurvey, typename Horizon = CAnyGeologicalCubeFeature::SampleVector>
	class CalculatorCubeIterator
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CalculatorCubeIterator(CubeGate &gate, CubeSurvey &survey, Horizon &horizon) : \
			m_gate(gate), m_survey(survey), m_horizon(horizon) // the kind of size, 0 means loop all cubes; 1 means along T cubes; else, along horizon cubes
		{
		}

		/*!
		*
		**/
		~CalculatorCubeIterator()
		{
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetCubeSize(const CalculatorCube::DataCubeSize &size)
		{
			m_size = size;
		}

		/*!
		*
		**/
		const CalculatorCube::DataCubeSize &GetCubeSize()
		{
			return m_size;
		}

		//
		//
		//
		/*!
		*
		**/
		long GetCubeCount()
		{
			if(m_cubeoffsets.size() == 0)
				return m_gate.GetCalculatorCubeCount(m_size, m_horizon);
			return m_cubeoffsets.size();
		}

		/*!
		*
		**/
		bool GetCube(long order, CalculatorCube &cube, bool cachemode = false)
		{
			bool rt;
			if(m_cubeoffsets.size() == 0)
				rt = m_gate.GetCalculatorCube(order, m_size, m_horizon, cube, m_survey, cachemode);
			else
				rt = m_gate.GetCalculatorCube(m_cubeoffsets[order], m_size, m_horizon, cube, m_survey, cachemode);
			if(rt)
				m_cursor = order;
			return rt;
		}
		
		/*!
		*
		**/
		bool GetTraces(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs, std::vector<CAnyGdeDataTrace*> &traces)
		{
			return m_gate.GetCalculatorCubeTraces(linenos, cdpnos, minZs, maxZs, traces, m_size, m_horizon, m_survey);
		}

		/*!
		*
		**/
		bool GetCubeLineandCdps(long order, std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs)
		{
			if(m_cubeoffsets.size() == 0)
				return m_gate.GetCalculatorCubeLineandCdps(order, m_size, m_horizon, m_survey, linenos, cdpnos, minZs, maxZs);
			else
				return m_gate.GetCalculatorCubeLineandCdps(m_cubeoffsets[order], m_size, m_horizon, m_survey, linenos, cdpnos, minZs, maxZs);
			return true;
		}
				
		/*!
		*
		**/
		bool IsLineandCdpsvalid(std::vector<int> &linenos, std::vector<int> &cdpnos, std::vector<double> &minZs, std::vector<double> &maxZs)
		{
			return m_gate.IsLineandCdpsvalid(linenos, cdpnos, minZs, maxZs);
		}
						
		/*!
		*
		**/
		int GetSequenceFromSurvey(int lineno, int cdpno)
		{
			return m_gate.GetCalculatorCubeSequenceFromSurvey(lineno, cdpno);
		}

		/*!
		*
		**/
		bool FirstCube(CalculatorCube &cube)
		{
			if(m_cubeoffsets.size() == 0)
				return GetCube(0, cube);
			return GetCube(m_cubeoffsets[0], cube);
		}

		/*!
		*
		**/
		bool NextCube(CalculatorCube &cube)
		{
			if(m_cubeoffsets.size() == 0)
				return GetCube(m_cursor + 1, cube);
			else if(m_cursor + 1 < m_cubeoffsets.size())
				return GetCube(m_cubeoffsets[m_cursor + 1], cube);
			return GetCube(m_cubeoffsets[m_cursor], cube);
		}
		
		/*!
		*
		**/
		bool GetSurrondingTraces(long sequenceorder, std::vector<CAnyGdeDataTrace*> &supertraces)
		{
			return m_gate.GetSurrondingTraces(sequenceorder, m_size, supertraces, m_survey);
		}
		
		/*!
		*
		**/
		bool GetSurrondingTracesCache(CalculatorCube &cube)
		{
			return m_gate.GetSurrondingTracesCache(cube, m_size, m_survey);
		}
		//
		//
		//
		/*!
		*
		**/
		bool UpdateTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyFunctor *progress)
		{
			return m_gate.UpdateTrace(traces, m_survey, progress);
		}

		/*!
		*
		**/
		bool UpdateSlice(CAnyGdeDataTrace *sampleTrace, double value)
		{
			if(!m_slice.size())
			{
				m_slice.reserve(m_survey.GetTotalTraceNumber());
			}

			long sequenceOrder;
			m_survey.Survey2Sequence((double)sampleTrace->m_lineNo, (double)sampleTrace->m_cdpNo, sequenceOrder);
			m_slice[sequenceOrder].m_point = sampleTrace->m_coord;
			m_slice[sequenceOrder].m_point.m_z = value;
			m_slice[sequenceOrder].m_inLineOrder = sampleTrace->m_lineNo;
			m_slice[sequenceOrder].m_xLineOrder = sampleTrace->m_cdpNo;

			return true;
		}

		/*!
		*
		**/
		void CommitTrace(std::vector<CAnyGdeDataTrace*> &traces, CAnyFunctor *progress, std::vector<std::vector<double> > metas)
		{
			m_gate.CommitTrace(traces, m_survey, progress, metas);
		}

		/*!
		*
		**/
		const Horizon &GetSliceData()
		{
			return m_slice;
		}
		
		/*!
		*
		**/
		bool ClearCache(std::vector<long> &savedsequenceOrders)
		{
			return m_gate.ClearCache(savedsequenceOrders);
		}
		
		/*!
		*
		**/
		void SetFitCachelimit()
		{
			return m_gate.SetFitCachelimit();
		}
		
		/*!
		*
		**/
		bool Open(int type)
		{
			return m_gate.Open(type);
		}
	public:
		// data 
		CubeGate &m_gate;
		// survey
		CubeSurvey &m_survey;
		// horizon 
		Horizon &m_horizon;

		// cube specification
		CalculatorCube::DataCubeSize m_size;
		// current cube as cursor
		int m_cursor;
		// as slice result
		Horizon m_slice;
		// for random sequenceorders
		std::vector<int> m_cubeoffsets;
	};
}
#endif
