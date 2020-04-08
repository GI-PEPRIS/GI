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
#ifndef ANYRCF_SIMULATION_MASTER_SERVANT_H
#define ANYRCF_SIMULATION_MASTER_SERVANT_H

#include"anyrcf.h"

#include "rcfserviceimpl.h"
#include "rcf\FileUpload.hpp"
#include "rcf\FileDownload.hpp"

//
namespace AnyRCF
{
	//
	template<typename SimulationGraph, typename JobNode, typename JobNodeContainer, typename SimulationModel, typename SimulationMatrix>
	class CSimulationMasterServant
	{

	public:
		CSimulationMasterServant(){m_model = 0;m_simulation_graph = 0;}
		virtual ~CSimulationMasterServant(){}

	public:
		// graph
		virtual void UpdateTopoGraph(long graph_idx, int nodecount, std::vector<unsigned long> jobstates, std::vector<char> &datachar)
		{
			m_simulation_graph = DoCreateSimulationGraph(nodecount, datachar);
			m_simulation_graph->m_job_graph_idx = graph_idx;
		}
		virtual void SetRabbitIdx(long rabbit_idx)
		{
			m_simulation_graph->set_master_rabbit_idx(rabbit_idx);	
		}
		virtual void SetTortoiseIdx(long tortoise_idx)
		{
			m_simulation_graph->set_master_tortoise_idx(tortoise_idx);
		}
		// model for simulator creation
		virtual int UploadModelFile(long model_idx, std::string filepath, RCF::FileUpload &fileUpload)
		{
			// given successfuly upload model file
			std::string model_file;
			{
				model_file = filepath;
			}

			// 
			if(m_model)
			{
				delete m_model;
			}
			m_model = DoCreateModel(model_file);
			return 0;
		}
		virtual int UploadModelStepFile(long model_idx, std::string filepath, RCF::FileUpload &fileUpload)
		{
			return 0;
		}
		virtual int DownloadModelFile(long model_idx, std::string filepath, RCF::FileDownload &fileDownload)
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
		virtual int DownloadModelFile_getfilelen(long model_idx, std::string filepath, long long &filelength)
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
		virtual int DownloadModelFile_readmode(long block_idx, std::string filepath, std::vector<char> &data, int readlength, long long offset)
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
		virtual int UploadModelData(long model_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber)
		{
			DoUploadModelData(m_model, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
			return 0;
		}
		virtual int DownloadModelData(long model_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber)
		{
			DoDownloadModelData(m_model, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
			return 0;
		}
		virtual int LoadModelCurrentStepData(long model_idx)
		{
			DoLoadModelCurrentStepData(m_model);
			return 0;
		}
		virtual int SaveModelCurrentStepData(long model_idx)
		{
			DoSaveModelCurrentStepData(m_model);
			return 0;
		}
		// only run sync node
		virtual bool RunSimulation(long job_node_idx)
		{
			JobNode *running_node = m_simulation_graph->get_master_node_for_running();
			if(job_node_idx != running_node->m_job_node_idx || !m_simulation_graph->is_master_meetwith())
			{
				// wait
				return false;
			}

			JobNode *master_node_runner = DoCreateModelRunner(m_model,running_node);
			bool needloop = master_node_runner->do_job();
			m_simulation_graph->reset_worker_node_after_running(needloop);

			delete master_node_runner;
			return needloop;
		}
	protected:
		//
		virtual SimulationGraph *DoCreateSimulationGraph(int nodecount, std::vector<char> &datachar) = 0;
		virtual SimulationModel *DoCreateModel(std::string &model_file) = 0;
		virtual JobNode *DoCreateModelRunner(SimulationModel *model, JobNode *running_node) = 0;
		virtual SimulationMatrix *DoCreateMatrix(SimulationModel *model, JobNode *job_node) = 0;
		virtual void DoUploadModelData(SimulationModel *model, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber) = 0;
		virtual void DoDownloadModelData(SimulationModel *model, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber) = 0;
		virtual void DoLoadModelCurrentStepData(SimulationModel *model) = 0;
		virtual void DoSaveModelCurrentStepData(SimulationModel *model) = 0;

	protected:
		// graph
		SimulationGraph *m_simulation_graph;
		// model, simulator, mesh etc
		SimulationModel *m_model;
	};
}

#endif

