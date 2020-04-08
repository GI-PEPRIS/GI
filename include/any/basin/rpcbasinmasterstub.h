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
#ifndef ANYRCF_GEO_SIMULATION_MASTER_STUB_H
#define ANYRCF_GEO_SIMULATION_MASTER_STUB_H

#include "anybasin.h"

//
#include "any/gfs/servicestub.h"
using namespace AnyRCF;

//
#include "rpcbasinmasterservant.h"

namespace AnyBasin
{
	namespace rpc
	{
		class ANYBASIN_CLASS CRpcBasinMasterStub : public CRCFClientImpl
		{
			typedef RcfClient<I_RpcBasinMasterServant> ServiceStub;
			typedef boost::shared_ptr<ServiceStub> ServiceStubPtr;
		public:
			CRpcBasinMasterStub(void);
			~CRpcBasinMasterStub(void);
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
			void SetRabbitIdx(long rabbit_idx);
			void SetTortoiseIdx(long tortoise_idx);
			int UploadModelFile(long model_idx, std::string filepath, RCF::FileUpload &fileUpload);
			int UploadModelStepFile(long model_idx, std::string filepath, RCF::FileUpload &fileUpload);
			int DownloadModelFile(long model_idx, std::string filepath, RCF::FileDownload &fileDownload);
			int DownloadModelFile_getfilelen(long model_idx, std::string filepath, long long &filelength);
			int DownloadModelFile_readmode(long model_idx, std::string filepath, std::vector<char> &data, int readlength, long long offset);
			int UploadModelData(long model_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			int DownloadModelData(long model_idx, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			int LoadModelCurrentStepData(long model_idx);
			int SaveModelCurrentStepData(long model_idx);
			bool RunSimulation(long job_node_idx);
		public:
			ServiceStubPtr m_client;
		};

	}
}

#endif

