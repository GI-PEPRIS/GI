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
#ifndef __ANYGDE_SAMPLE_DATA_UTILITY_GENERIC_CALCULATOR__H__
#define __ANYGDE_SAMPLE_DATA_UTILITY_GENERIC_CALCULATOR__H__

// refer to EXPORT & IMPORT
#include "anygde.h"

#include "any/base/anytimebasic.h"
#include "any/base/anyplatinfo.h"
#include "any/base/anystl.h"
#include "any/base/anydbgmacro.h"
#include "any/base/anydbglogger.h"
using namespace AnyBase;

//
#include "boost\function.hpp"

//
namespace AnyGDE
{
	struct HandlerCallback
	{
		int m_totaltraces;
		int m_curtrace;
		string m_status;
		int m_starttime;
		int m_curtime;
	};

	template<typename Signature>
	struct GdeHandlerCallback : public HandlerCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};

	/*!
	*
	**/
	template<typename Handler, typename InputIterator, typename OutputIterator, typename ProgressMeter>
	class CAnyGdeDataGenericCalculator
	{
	public:
		// handler function
		//typedef boost::function<Signature> HandlerFunction;
		//typename optional_last_value<typename boost::function_traits<Signature>::result_type> FunctionType;

	private:
		//
		class DoWorkTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			DoWorkTask(int taskcount, int index, std::vector<CalculatorCube> &cubes, std::vector<std::vector<CalculatorCube> > &othercubes, std::vector<Handler*> &handlers, std::vector<InputIterator> &inputs, std::vector<OutputIterator> &outputs, \
				std::vector<std::vector<std::vector<CAnyGdeDataTrace*> > > &supertrace, std::vector<std::vector<CAnyGdeDataTrace*> > &tracestoupdate, std::map<int, std::vector<double> > &sequenceorder_meta, CAnyCPUScheduler *scheduler) : \
				m_cubes(cubes), m_othercubes(othercubes), m_handlers(handlers), m_inputs(inputs), m_outputs(outputs), m_supertrace(supertrace), m_tracestoupdate(tracestoupdate), m_sequenceorder_meta(sequenceorder_meta)
			{
				m_taskcount = taskcount;
				m_index = index;
				m_scheduler = scheduler;
			}
			~DoWorkTask(){}

			void DoExecuteTask()
			{
				int allcount = m_cubes.size();
				for(int i = m_index * allcount / m_taskcount; i < (m_index + 1) * allcount / m_taskcount; i++)
				{
					CalculatorCube &cube = m_cubes[i];
					int count = cube.GetTraceCount();
					for(int j = 0; j < count; j++)
					{
						CAnyGdeDataTrace *sampleTrace = cube.GetSampleTrace(j);
						if(!sampleTrace)
							continue;
						//获取其他inputs的cube中的道
						std::vector<CAnyGdeDataTrace*> othersampleTraces;
						for(int k = 0; k < m_othercubes.size(); k++)
						{
							CAnyGdeDataTrace *othersampleTrace = m_othercubes[k][i].GetSampleTrace(j);
							othersampleTraces.push_back(othersampleTrace);
						}
						std::vector<double> results;
						CAnyGdeDataHandler::HandlerStruct handlerstruct(sampleTrace, othersampleTraces, m_inputs[0].m_gate.m_surveyInfo, m_index, m_supertrace[i][j]);
						m_handlers[m_index]->DoHandle(handlerstruct);
						m_handlers[m_index]->DoGetTraceSample(results, sampleTrace->m_cmpcount);
						if(results.size() == 1)
						{
							m_outputs[0].UpdateSlice(sampleTrace, results[0]);
						}
						else
						{
							std::vector<CAnyGdeDataTrace*> sampleTraces;
							for(int offset = 0; offset < m_outputs.size(); offset++)
							{
								if(offset == 0)
									sampleTraces.push_back(sampleTrace);
								else
									sampleTraces.push_back(sampleTrace->Clone());
							}
							for(int offset = 0; offset < m_outputs.size(); offset++)
							{
								for(int k = 0; k < results.size() / m_outputs.size(); k++)
								{
									if(k < sampleTraces[offset]->m_samples.size())
										sampleTraces[offset]->m_samples[k] = results[offset * results.size() / m_outputs.size() + k];	
									else
										sampleTraces[offset]->m_samples.push_back(results[offset * results.size() / m_outputs.size() + k]);
								}
								JTCSyncT<JTCRecursiveMutex> guard(m_scheduler->m_internal);
								m_tracestoupdate[offset].push_back(sampleTraces[offset]);
							}
							std::vector<double> meta;
							m_handlers[m_index]->DoGetTraceHead(meta);
							if(meta.size() > 0)
							{
								JTCSyncT<JTCRecursiveMutex> guard(m_scheduler->m_internal);
								m_sequenceorder_meta.insert(pair<int, std::vector<double> >(sampleTrace->m_sequenceOrder, meta));
							}
						}
					}
				}
			}
			int m_taskcount;
			int m_index;
			std::vector<CalculatorCube> &m_cubes;
			std::vector<std::vector<CalculatorCube> > &m_othercubes;
			std::vector<Handler*> &m_handlers;
			std::vector<InputIterator> &m_inputs;
			std::vector<OutputIterator> &m_outputs;
			std::vector<std::vector<std::vector<CAnyGdeDataTrace*> > > m_supertrace;
			std::map<int, std::vector<double> > &m_sequenceorder_meta;
			std::vector<std::vector<CAnyGdeDataTrace*> > &m_tracestoupdate;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataGenericCalculator(std::vector<Handler*> &handlers, std::vector<InputIterator> &inputs, std::vector<OutputIterator> &outputs, ProgressMeter &meter) : \
			m_handlers(handlers), m_inputs(inputs), m_outputs(outputs), m_meter(meter), m_progresscb(0)
		{
			m_taskcount = CAnyPlatInfo::Get().GetNumberProcessors();
		}

		/*!
		*
		**/
		~CAnyGdeDataGenericCalculator()
		{
		}

	public:
		//
		// parallel interface
		//
		/*!
		*
		**/
		void DoExecute(int inputinlCount, int inputcrlCount, std::vector<double> inputtimewindows, int outputinlCount, int outputcrlCount, std::vector<double> outputtimewindows, std::vector<int> &sequenceorders)
		{
			std::vector<CalculatorCube::DataCubeSize> inputdatacubesizes;
			for(int i = 0; i < m_inputs.size(); i++)
			{
				CalculatorCube::DataCubeSize inputdatacubesize;
				inputdatacubesize.m_inlCount = inputinlCount;
				inputdatacubesize.m_crlCount = inputcrlCount;
				inputdatacubesize.m_windowZ = inputtimewindows[i];
				inputdatacubesizes.push_back(inputdatacubesize);
			}
			std::vector<CalculatorCube::DataCubeSize> outputdatacubesizes;
			for(int i = 0; i < m_outputs.size(); i++)
			{
				CalculatorCube::DataCubeSize outputdatacubesize;
				outputdatacubesize.m_inlCount = outputinlCount;
				outputdatacubesize.m_crlCount = outputcrlCount;
				outputdatacubesize.m_windowZ = outputtimewindows[i];
				outputdatacubesizes.push_back(outputdatacubesize);
			}
			for(int i = 0; i < m_inputs.size(); i++)
				m_inputs[i].m_cubeoffsets = sequenceorders;
			for(int i = 0; i < m_outputs.size(); i++)
				m_outputs[i].m_cubeoffsets = sequenceorders;
			for(int i = 0; i < m_inputs.size(); i++)
				m_inputs[i].SetCubeSize(inputdatacubesizes[i]);
			for(int i = 0; i < m_outputs.size(); i++)
				m_outputs[i].SetCubeSize(outputdatacubesizes[i]);
			for(int i = 0; i < m_inputs.size(); i++)
				m_inputs[i].SetFitCachelimit();
			for(int i = 0; i < m_outputs.size(); i++)
				m_outputs[i].SetFitCachelimit();
			for(int i = 0; i < m_outputs.size(); i++)
				m_outputs[i].Open(CAnyFileBasic::ANY_FILE_ALL);
			int cubecount = m_inputs[0].GetCubeCount();
			int outcubecount = m_outputs[0].GetCubeCount();
			int functorshowinterval = cubecount / 100;
			if(functorshowinterval == 0)
				functorshowinterval = 1;
			int lastindex = 0;
			CAnyTimeBasic::TimeReport report;
			CAnyTimeBasic timeBasic;
			if(m_progresscb)
			{
				timeBasic.GetNow(report);
				m_progresscb->m_starttime = report.m_hour * 10000 + report.m_minute * 100 + report.m_second;
			}
			double totalworktime = 0;
			double totalfinishtime = 0;
			int curvalidcube = 0;
			CAnyTimeBasic::TimeReport report1, report2, report3;
			for(int i = 0; i <= cubecount; i = i + m_taskcount)
			{
				timeBasic.GetNow(report1);
				int validcubecount = DoWorkMT(i, (i + m_taskcount > cubecount ? cubecount : i + m_taskcount));
				if(validcubecount == 0)
					continue;
				if(m_progresscb)
				{
					m_progresscb->m_curtrace = curvalidcube;
					m_progresscb->m_totaltraces = outcubecount;
					timeBasic.GetNow(report);
					m_progresscb->m_curtime = report.m_hour * 10000 + report.m_minute * 100 + report.m_second;
					((GdeHandlerCallback<void (const HandlerCallback&)> *)m_progresscb)->m_function(*m_progresscb);
				}
				if(i - lastindex >= functorshowinterval)
				{
					m_meter(true, 100, i / functorshowinterval);
					lastindex = i;
				}
				curvalidcube = curvalidcube + validcubecount;
				timeBasic.GetNow(report2);
				DoFinish(i, (i + m_taskcount > cubecount ? cubecount : i + m_taskcount));
				timeBasic.GetNow(report3);
				double worktime = (report2.m_day - report1.m_day) * (24 * 3600) + (report2.m_hour - report1.m_hour) * 3600 + (report2.m_minute - report1.m_minute) * 60 + (report2.m_second - report1.m_second);
				double finishtime = (report3.m_day - report2.m_day) * (24 * 3600) + (report3.m_hour - report2.m_hour) * 3600 + (report3.m_minute - report2.m_minute) * 60 + (report3.m_second - report2.m_second);
				totalworktime += worktime;
				totalfinishtime += finishtime;
				std::vector<long> savedsequenceOrders;
				for(int offset = 0; offset < m_inputs.size(); offset++)
					m_inputs[offset].ClearCache(savedsequenceOrders);
				for(int offset = 0; offset < m_outputs.size(); offset++)
					m_outputs[offset].ClearCache(savedsequenceOrders);
			}
			for(int i = 0; i < m_outputs.size(); i++)
				m_outputs[i].Open(CAnyFileBasic::ANY_FILE_READ);
			char info[1024] = {0, };
			TCHAR msg[1024] = {0, };
			::sprintf(info, "totalworktime:%f,totalcommittime:%f\r\n", totalworktime, totalfinishtime);
			CAnyStringBasic::Get().Ascii2Wcs(info, msg, 1024);
			RUNNING_HERE
			RUNNING_MSG(msg)
			if(m_progresscb)
			{
				delete m_progresscb;
				m_progresscb = 0;
			}
			m_meter(false, -1, -1);
		}

		/*!
		*
		**/
		int DoWorkMT(long start, long end)
		{
			std::vector<bool> isvalids;
			int validcubecount = 0;
			for(int i = start; i < end; i++)
			{
				std::vector<int> linenos, cdpnos;
				std::vector<double> minZs, maxZs;
				m_inputs[0].GetCubeLineandCdps(i, linenos, cdpnos, minZs, maxZs);
				bool isvalid = false;
				//判断当前cube线道号范围是否超出m_output范围，超出就不计算了
				for(int j = 0; j < m_outputs.size(); j++)
				{
					if(m_outputs[j].IsLineandCdpsvalid(linenos, cdpnos, minZs, maxZs))
					{
						isvalid = true;
						break;
					}
				}
				isvalids.push_back(isvalid);
				if(isvalid)
					validcubecount++;
			}
			if(validcubecount == 0)
				return 0;
			std::vector<CalculatorCube> cubes;//m_inputs[0]的cubes
			std::vector<std::vector<CalculatorCube> > othercubes;//其他m_inputs的cubes
			std::vector<std::vector<std::vector<CAnyGdeDataTrace*> > > supertrace;//m_inputs[0]的cubes的每道的周围道
			for(int i = 1; i < m_inputs.size(); i++)
			{
				std::vector<CalculatorCube> subothercubes;
				othercubes.push_back(subothercubes);
			}
			for(int i = start; i < end; i++)
			{
				if(!isvalids[i - start])
					continue;
				//获取m_inputs[0]的cube
				CalculatorCube cube;
				if(!m_inputs[0].GetCube(i, cube))
					continue;
				//获取其他m_inputs的cube
				{
					bool iscubeok = true;
					std::vector<CalculatorCube> tmpcubes;
					for(int j = 1; j < m_inputs.size(); j++)
					{
						CalculatorCube tmpcube;
						if(!m_inputs[j].GetCube(i, tmpcube) || tmpcube.GetTraceCount() < cube.GetTraceCount())
						{
							iscubeok = false;
							break;
						}
						tmpcubes.push_back(tmpcube);
					}
					if(iscubeok)
					{
						for(int j = 0; j < tmpcubes.size(); j++)
							othercubes[j].push_back(tmpcubes[j]);
						cubes.push_back(cube);
					}
					else
					{
						cube.Release();
						for(int j = 0; j < tmpcubes.size(); j++)
							tmpcubes[j].Release();
						continue;
					}
				}
				//获取m_inputs[0]的周围道
				std::vector<std::vector<CAnyGdeDataTrace*> > subsupertrace;
				int count = cube.GetTraceCount();
				for(int j = 0; j < count; j++)
				{
					std::vector<CAnyGdeDataTrace*> subsubsupertrace;
					if(m_inputs[0].GetCubeSize().m_inlCount > 1 || m_inputs[0].GetCubeSize().m_crlCount > 1)
					{
						CAnyGdeDataTrace *sampleTrace = cube.GetSampleTrace(j);
						m_inputs[0].GetSurrondingTraces(sampleTrace->m_sequenceOrder, subsubsupertrace);
					}
					subsupertrace.push_back(subsubsupertrace);
				}
				supertrace.push_back(subsupertrace);
			}
			for(int i = 0; i < m_outputs.size(); i++)
			{
				std::vector<CAnyGdeDataTrace*> subtracestoupdate;
				m_tracestoupdate.push_back(subtracestoupdate);
			}
			CAnyCPUScheduler* scheduler = CAnyCPUScheduler::GetInstance();
			for(int i = 0; i < m_taskcount; i++)
			{
				DoWorkTask* doworktask = new DoWorkTask(m_taskcount, i, cubes, othercubes, m_handlers, m_inputs, m_outputs, supertrace, m_tracestoupdate, m_sequenceorder_meta, scheduler);
				scheduler->AddTask(doworktask);
			}
			//同时缓冲下一批道
			for(int i = end; i < end + m_taskcount; i++)
			{
				std::vector<int> linenos, cdpnos;
				std::vector<double> minZs, maxZs;
				m_inputs[0].GetCubeLineandCdps(i, linenos, cdpnos, minZs, maxZs);
				bool isvalid = false;
				for(int j = 0; j < m_outputs.size(); j++)
				{
					if(m_outputs[j].IsLineandCdpsvalid(linenos, cdpnos, minZs, maxZs))
					{
						isvalid = true;
						break;
					}
				}
				if(!isvalid)
					continue;
				for(int j = 0; j < m_inputs.size(); j++)
				{
					CalculatorCube cube;
					m_inputs[j].GetCube(i, cube, true);
					if(j == 0 && (m_inputs[0].GetCubeSize().m_inlCount > 1 || m_inputs[0].GetCubeSize().m_crlCount > 1))
						m_inputs[0].GetSurrondingTracesCache(cube);
				}
			}
			scheduler->WaitPoolIdle();
			for(int i = 0; i < m_outputs.size(); i++)
			{
				for(int j = 0; j < m_tracestoupdate[i].size(); j++)
				{
					std::vector<CAnyGdeDataTrace*> subtracestoupdate;
					subtracestoupdate.push_back(m_tracestoupdate[i][j]);
					m_outputs[i].UpdateTrace(subtracestoupdate, &m_meter);
				}
			}
			// release memory
			for(int i = 1; i < m_tracestoupdate.size(); i++)
			{
				for(int j = 0; j < m_tracestoupdate[i].size(); j++)
				{
					if(m_tracestoupdate[i][j])
						delete m_tracestoupdate[i][j];
					m_tracestoupdate[i][j] = NULL;
				}
				m_tracestoupdate[i].clear();
			}
			m_tracestoupdate.clear();
			for(int i = 0; i < cubes.size(); i++)
			{
				cubes[i].Release();
			}
			cubes.clear();
			for(int i = 0; i < othercubes.size(); i++)
			{
				for(int j = 0; j < othercubes[i].size(); j++)
				{
					othercubes[i][j].Release();
				}
				othercubes[i].clear();
			}
			othercubes.clear();
			for(int i = 0; i < supertrace.size(); i++)
			{
				for(int j = 0; j < supertrace[i].size(); j++)
				{
					for(int k = 0; k < supertrace[i][j].size(); k++)
					{
						delete supertrace[i][j][k];
						supertrace[i][j][k] = NULL;
					}
					supertrace[i][j].clear();
				}
				supertrace[i].clear();
			}
			supertrace.clear();
			return validcubecount;
		}
		
		/*!
		*
		**/
		void DoFinish(long start, long end)
		{
			for(int offset = 0; offset < m_outputs.size(); offset++)
			{
				for(int i = start; i < end; i++)
				{
					std::vector<int> linenos, cdpnos;
					std::vector<double> minZs, maxZs;
					m_inputs[0].GetCubeLineandCdps(i, linenos, cdpnos, minZs, maxZs);
					if(!m_outputs[offset].IsLineandCdpsvalid(linenos, cdpnos, minZs, maxZs))
						continue;
					m_outputs[offset].GetTraces(linenos, cdpnos, minZs, maxZs, m_tracestocommit);
				}
				if(!m_tracestocommit.size())
					continue;
				std::vector<std::vector<double> > metas;
				for(int i = 0; i < m_tracestocommit.size(); i++)
				{
					if(m_sequenceorder_meta.find(m_inputs[0].GetSequenceFromSurvey(m_tracestocommit[i]->m_lineNo, m_tracestocommit[i]->m_cdpNo)) != m_sequenceorder_meta.end())
						metas.push_back(m_sequenceorder_meta[m_inputs[0].GetSequenceFromSurvey(m_tracestocommit[i]->m_lineNo, m_tracestocommit[i]->m_cdpNo)]);
					else
					{
						std::vector<double> meta;
						metas.push_back(meta);
					}
				}
				m_outputs[offset].CommitTrace(m_tracestocommit, &m_meter, metas);
				for(int i = 0; i < m_tracestocommit.size(); i++)
					delete m_tracestocommit[i];
				m_tracestocommit.clear();
			}
		}

		//
		//
		//
		/*!
		*
		**/
		void HandleData()
		{
			Execute(bind(&CAnyGdeDataGenericCalculator<Handler, InputIterator, OutputIterator, ProgressMeter>::Notify, this));
		}

		/*!
		*
		**/
		Handler *GetHandler()
		{
			return &m_handler;
		}

		/*!
		*
		**/
		void Notify()
		{
			m_meter(true, m_iterations/m_batches, m_current++);
		}

	public:
		HandlerCallback *m_progresscb;

	private:
		//
		long m_current;
		// handler or algorithm
		std::vector<Handler*> &m_handlers;
		// input data
		std::vector<InputIterator> &m_inputs;
		// progress meter
		ProgressMeter &m_meter;
		// output data
		std::vector<OutputIterator> &m_outputs;
		// configure parameters
		int m_taskcount;
		// trace meta data
		std::map<int, std::vector<double> > m_sequenceorder_meta;
		// trace to update
		std::vector<std::vector<CAnyGdeDataTrace*> > m_tracestoupdate;
		// trace to commit
		std::vector<CAnyGdeDataTrace*> m_tracestocommit;
	};
}
#endif