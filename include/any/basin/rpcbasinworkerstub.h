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
#ifndef ANYRCF_GEO_SIMULATION_WORKER_STUB_H
#define ANYRCF_GEO_SIMULATION_WORKER_STUB_H

//
#include "rpcbasinworkerservant.h"

//
#include "any/gfs/servicestub.h"
using namespace AnyRCF;

namespace AnyBasin
{
	namespace rpc
	{
		class ANYBASIN_CLASS CRpcBasinWorkerStub : public CRCFClientImpl
		{
			typedef RcfClient<I_RpcBasinWorkerServant> ServiceStub;
			typedef boost::shared_ptr<ServiceStub> ServiceStubPtr;

		public:
			CRpcBasinWorkerStub(void);
			~CRpcBasinWorkerStub(void);
		public:
			//
			// basic
			//
			void Init(const ServiceHandle &handle);
			void GetHandle(ServiceHandle &handle);
			void Start();
			void Listen(const std::string &multicastip, int multicastport);
			void Stop();
			void Suspend();
			void Resume(bool isstopheart = false, bool isstopbroadcast = false, bool isstoprequest = false);
			bool IsRunning();
			string GetResponseUserData(const string &data);
			void RegisterChildren(int type, const ServiceHandle &handle);
			void RemoveChildren(string &ip, int port);
			void GetChildren(int type, ServiceVector &handles);
			void BindTo(int type, string &ip, int port);
			void CollectHeartbeat(const ServiceHandle &handle, const MasterChunkServer &chunkstatus, const JobTaskServer &taskstatus);
			void SetClientName(const std::string &name);
			void Ping();
			void Callback(const std::string &topic);
		public:
			void UpdateTopoGraph(long graph_idx, SimulationJobNodeContainer &nodes);
			void ClearBlocks(long model_idx);
			int UploadBlockFile(long block_idx, std::string filepath, RCF::FileUpload &fileUpload);
			int UploadBlockStepFile(long block_idx, std::string filepath, RCF::FileUpload &fileUpload);
			int DownloadBlockFile(long block_idx, std::string filepath, RCF::FileDownload &fileDownload);
			int DownloadBlockFile_getfilelen(long block_idx, std::string filepath, long long &filelength);
			int DownloadBlockFile_readmode(long block_idx, std::string filepath, std::vector<char> &data, int readlength, long long offset);
			int UploadBlockData(long block_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			int DownloadBlockData(long block_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			int LoadBlockCurrentStepData(long block_idx);
			int SaveBlockCurrentStepData(long block_idx);
			void RunSimulation();
			void SuspendSimulation();
			void ResumeSimulation(long master_job_idx);
			int GetRunningNodeidx();
		public:
			ServiceStubPtr m_client;
		};

	}
}

#endif

