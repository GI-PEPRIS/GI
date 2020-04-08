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
#ifndef ANYRCF_SIMULATION_WORKER_SERVANT_H
#define ANYRCF_SIMULATION_WORKER_SERVANT_H

//
#include"anyrcf.h"
#include "rcfserviceimpl.h"
#include "rcf\FileUpload.hpp"
#include "rcf\FileDownload.hpp"

//
namespace AnyRCF
{

	template<typename SimulationGraph, typename JobNode, typename JobNodeContainer, typename SimulationBlock, typename SimulationBlockContainer>
	class CSimulationWorkerServant
	{
	public:
		CSimulationWorkerServant(){m_simulation_graph=0;}
		virtual ~CSimulationWorkerServant(){}

	public:
		// graph
		void UpdateTopoGraph(long graph_idx, int nodecount, std::vector<unsigned long> jobstates, std::vector<char> &datachar)
		{
			if(!m_simulation_graph)
			{
				m_simulation_graph = DoCreateSimulationGraph(nodecount, datachar);
				m_simulation_graph->m_job_graph_idx = graph_idx;
			}
			else
			{
				for(int i = 0; i < jobstates.size(); i++)
					m_simulation_graph->m_job_nodes_in_topo_order[i]->m_job_state = jobstates[i];
			}
		}
		// blocks
		void ClearBlocks(long model_idx)
		{
			for(int i = 0; i < m_blocks_as_simulator_prototypes.size(); i++)
			{
				delete m_blocks_as_simulator_prototypes[i];
			}
			m_blocks_as_simulator_prototypes.clear();
		}
		virtual int UploadBlockFile(long block_idx, std::string filepath, RCF::FileUpload &fileUpload)
		{
			SimulationBlock *block = DoCreateModelBlock(filepath);
			m_blocks_as_simulator_prototypes.push_back(block);
			return 0;
		}
		virtual int UploadBlockStepFile(long block_idx, std::string filepath, RCF::FileUpload &fileUpload)
		{
			return 0;
		}
		virtual int DownloadBlockFile(long block_idx, std::string filepath, RCF::FileDownload &fileDownload)
		{
			std::string fullpath = filepath;
			TCHAR wbuf[1024] = {0, };
			CAnyStringBasic::Get().Ascii2Wcs((char *)fullpath.c_str(), wbuf, 1024);
			if(CAnyDirBasic::Get().IsFileExist(wbuf)) 
			{
				fileDownload = RCF::FileDownload(fullpath);
			}
			return 0;
		}
		virtual int DownloadBlockFile_getfilelen(long model_idx, std::string filepath, long long &filelength)
		{
			TCHAR wbuf[1024] = {0, };
			CAnyStringBasic::Get().Ascii2Wcs((char *)filepath.c_str(), wbuf, 1024);
			wstring wchunkfile = wbuf;
			if(!CAnyDirBasic::Get().IsFileExist(wchunkfile))
				return 0;
			const CAnyFileBasic &fileBasic = CAnyFileBasic::Get();
			void *fileHandle = fileBasic.OpenFile(wchunkfile, CAnyFileBasic::ANY_FILE_READ);
			if(!fileHandle)
				return 0;
			fileBasic.SeekFile(fileHandle, 0, CAnyFileBasic::ANY_SEEK_END);
			filelength = fileBasic.TellFilePos(fileHandle);
			fileBasic.CloseFile(fileHandle);
			return 0;
		}
		virtual int DownloadBlockFile_readmode(long block_idx, std::string filepath, std::vector<char> &data, int readlength, long long offset)
		{
			string chunkfile = filepath;
			TCHAR wbuf[1024] = {0, };
			CAnyStringBasic::Get().Ascii2Wcs((char *)chunkfile.c_str(), wbuf, 1024);
			wstring wchunkfile = wbuf;
			if(!CAnyDirBasic::Get().IsFileExist(wchunkfile))
				return 0;
			const CAnyFileBasic &fileBasic = CAnyFileBasic::Get();
			void *fileHandle = fileBasic.OpenFile(wchunkfile, CAnyFileBasic::ANY_FILE_READ);
			fileBasic.SeekFile(fileHandle, offset, CAnyFileBasic::ANY_SEEK_BEGIN);
			if(data.size() < readlength)
				data.resize(readlength);
			char *datachar = data.data();
			int count = 1;
			fileBasic.ReadFile(fileHandle, (void **)&datachar, readlength, count);
			fileBasic.CloseFile(fileHandle);
			return 0;
		}
		virtual int UploadBlockData(long block_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber)
		{
			for(int i = 0; i < m_blocks_as_simulator_prototypes.size(); i++)
			{
				SimulationBlock *block = (SimulationBlock*)(m_blocks_as_simulator_prototypes[i]);
				DoUploadBlockData(block, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
			}
			return 0;
		}
		virtual int DownloadBlockData(long block_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber)
		{
			SimulationBlock *block = (SimulationBlock*)(m_blocks_as_simulator_prototypes[0]);
			DoDownloadBlockData(block, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
			return 0;
		}
		virtual int LoadBlockCurrentStepData(long block_idx)
		{
			for(int i = 0; i < m_blocks_as_simulator_prototypes.size(); i++)
			{
				SimulationBlock *block = (SimulationBlock*)(m_blocks_as_simulator_prototypes[i]);
				DoLoadBlockCurrentStepData(block);
			}
			return 0;
		}
		virtual int SaveBlockCurrentStepData(long block_idx)
		{
			for(int i = 0; i < m_blocks_as_simulator_prototypes.size(); i++)
			{
				SimulationBlock *block = (SimulationBlock*)(m_blocks_as_simulator_prototypes[i]);
				DoSaveBlockCurrentStepData(block);
			}
			return 0;
		}
		virtual void RunSimulation()
		{
			// running block simulators in one worker servant
			while(!m_simulation_graph->is_worker_done())
			{
				JobNode *running_node = m_simulation_graph->get_worker_node_for_running();
				m_running_job_node_idx = running_node->m_job_node_idx;
				if(running_node->m_is_sync_node)
				{
					//m_master->Run(m_running_job_node_idx);
					SuspendSimulation();

					break;
				}
				// bind current simulator function
				JobNodeContainer block_runners;
				for(int i = 0; i < m_blocks_as_simulator_prototypes.size(); i++)
				{
					// bind simulator function against current node specification
					block_runners.push_back(DoCreateBlockRunner((SimulationBlock*)m_blocks_as_simulator_prototypes[i],running_node));
				}
				bool needloop = false;
				{
					#pragma omp parallel for schedule(static)
					for(int i = 0; i < block_runners.size(); i++)
					{
						bool rt = block_runners[i]->do_job();
						if(rt)
							needloop = true;
					}
				}
				// release runner
				for(int i = 0; i < block_runners.size(); i++)
				{
					delete block_runners[i];
				}
				m_simulation_graph->reset_worker_node_after_running(needloop);
				//m_master->SetRabbitOrTortoiseIdx(m_running_job_node_idx);
			}
			if(m_simulation_graph->is_worker_done())
				m_running_job_node_idx = m_simulation_graph->m_job_nodes_in_topo_order.size();
		}
		virtual void SuspendSimulation()
		{

		}
		virtual void ResumeSimulation(long master_job_idx)
		{
			m_simulation_graph->reset_worker_node_after_master(master_job_idx);
			RunSimulation();
		}
		virtual int GetRunningNodeidx()
		{
			return m_running_job_node_idx;
		}

		// matrix
		//int UploadMatrixFile(std::string filepath, RCF::FileUpload &fileUpload);
		//int DownloadMatrixFile(std::string filepath, RCF::FileUpload &fileUpload);

	protected:
		//
		virtual SimulationGraph *DoCreateSimulationGraph(int nodecount, std::vector<char> &datachar) = 0;
		virtual SimulationBlock *DoCreateModelBlock(std::string &block_file) = 0 ;
		virtual JobNode *DoCreateBlockRunner(SimulationBlock *model_block, JobNode *running_node) = 0;

		virtual void DoUploadBlockData(SimulationBlock *block, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber) = 0;
		virtual void DoDownloadBlockData(SimulationBlock *block, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber) = 0;
		virtual void DoLoadBlockCurrentStepData(SimulationBlock *block) = 0;
		virtual void DoSaveBlockCurrentStepData(SimulationBlock *block) = 0;

	protected:
		//
		long m_running_job_node_idx;
		SimulationGraph *m_simulation_graph;
		SimulationBlockContainer m_blocks_as_simulator_prototypes;
	};

}

#endif
