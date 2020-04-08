/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef ANYBASIN_RPC_BASIN_SIMULATOR_WORKER_SERVANT_H
#define ANYBASIN_RPC_BASIN_SIMULATOR_WORKER_SERVANT_H

//
#include "anybasin.h"
#include "rpcbasinsimulatoradapter.h"

#include "any/gfs/simulationworkerservant.h"
using namespace AnyRCF;

namespace AnyBasin
{
	namespace rpc
	{
		// interface
		RCF_BEGIN(I_RpcBasinWorkerServant, "I_RpcBasinWorkerServant")
			//here is soft control(rcf server start/stop) hard control is implemented in console app using psService.
			RCF_METHOD_R1(bool, Init, const ServiceHandle&)
			RCF_METHOD_V1(void, GetHandle, ServiceHandle&)
			RCF_METHOD_V1(void, SetEventHandle, const ServiceHandle&)
			RCF_METHOD_V0(void, Start)
			RCF_METHOD_V2(void, Listen, const std::string&, short)
			RCF_METHOD_V3(void, Notify, short, const std::string&, long)
			RCF_METHOD_V0(void, Stop)
			RCF_METHOD_V3(void, Resume, bool, bool, bool)
			RCF_METHOD_V0(void, Suspend)
			RCF_METHOD_R0(bool, IsRunning)
			RCF_METHOD_V2(void, NetworkBandwidthAsReceiver, int, int)
			RCF_METHOD_V4(void, NetworkBandwidthAsSender, string&, int, int, int)
			RCF_METHOD_R0(SessionObjectVector, QuerySessionObject)
			RCF_METHOD_V1(void, ClearSessionObject, const string&)

			//console operate on chilren of cms
			RCF_METHOD_V2(void, RegisterChildren, int, const ServiceHandle&)
			RCF_METHOD_V2(void, RemoveChildren, string&, int)
			RCF_METHOD_V2(void, GetChildren, int, ServiceVector&)
			RCF_METHOD_V3(void, CollectHeartbeat, const ServiceHandle&, const MasterChunkServer&, const JobTaskServer&)

			//communicate  e.g. heart beats
			RCF_METHOD_V3(void, BindTo, int, string&, int)
			RCF_METHOD_V0(void, SetResponseUserData)
			RCF_METHOD_V1(void, SetClientName, const std::string&)
			RCF_METHOD_V1(void, Callback, const std::string&)
			RCF_METHOD_V1(void, OnCallback, const std::string&)

			RCF_METHOD_V4(void, UpdateTopoGraph, long, int, std::vector<unsigned long> &, std::vector<char> &)
			RCF_METHOD_V1(void, ClearBlocks, long)
			RCF_METHOD_R3(int, UploadBlockFile, long, std::string, RCF::FileUpload&)
			RCF_METHOD_R3(int, UploadBlockStepFile, long, std::string, RCF::FileUpload&)
			RCF_METHOD_R3(int, DownloadBlockFile, long, std::string, RCF::FileDownload&)
			RCF_METHOD_R3(int, DownloadBlockFile_getfilelen, long, std::string, long long&)
			RCF_METHOD_R5(int, DownloadBlockFile_readmode, long, std::string, std::vector<char>&, int, long long)
			RCF_METHOD_R4(int, UploadBlockData, long, long&, int&, int&)
			RCF_METHOD_R4(int, DownloadBlockData, long, long&, int&, int&)
			RCF_METHOD_R1(int, LoadBlockCurrentStepData, long)
			RCF_METHOD_R1(int, SaveBlockCurrentStepData, long)
			RCF_METHOD_V0(void, RunSimulation)
			RCF_METHOD_V0(void, SuspendSimulation)
			RCF_METHOD_V1(void, ResumeSimulation, long)
			RCF_METHOD_R0(int, GetRunningNodeidx)

		RCF_END(I_RpcBasinWorkerServant)
		class ANYBASIN_CLASS CRpcBasinWorkerServant : public CRCFServiceImpl, public CSimulationWorkerServant<RpcSimulationGraph, SimulationJobNode, SimulationJobNodeContainer, RpcSolutionBlock, RpcSolutionBlockContainer>
		{
			// callback
			typedef RcfClient<I_RpcBasinWorkerServant> CbClient;
			typedef boost::shared_ptr<CbClient> CbClientPtr;

		public:
			CRpcBasinWorkerServant();
			~CRpcBasinWorkerServant();
		public:
			//
			// service interface
			//
			void Start(); 
			void Callback(const std::string &topic);
			void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);
			void DoScheduleEntries(std::deque<RequestEntry *> &entries);
			void OnCallback(const std::string &topic);
			void DoCollectServerStatus(ServiceHandle &handle, MasterChunkServer &chunkstatus, JobTaskServer &taskstatus);

			//
			//
		protected:
			//
			virtual RpcSimulationGraph *DoCreateSimulationGraph(int nodecount, std::vector<char> &datachar);
			virtual RpcSolutionBlock *DoCreateModelBlock(std::string &block_file);
			virtual SimulationJobNode *DoCreateBlockRunner(RpcSolutionBlock *model_block,SimulationJobNode *running_node);
		
			void DoUploadBlockData(RpcSolutionBlock *block, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			void DoDownloadBlockData(RpcSolutionBlock *block, long &whichsimulationstep, int &pressure_LoopNumber, int &heat_LoopNumber);
			void DoLoadBlockCurrentStepData(RpcSolutionBlock *block);
			void DoSaveBlockCurrentStepData(RpcSolutionBlock *block);

		private:
			RCF::BandwidthQuotaPtr UploadBandwidthQuotaCb(RCF::RcfSession & session);
			RCF::BandwidthQuotaPtr DownBandwidthQuotaCb(RCF::RcfSession & session);

		private:
			// callback connections
			std::map<std::string, CbClientPtr> m_cbClients;
		};

	}

};

#endif
