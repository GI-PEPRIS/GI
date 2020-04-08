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
#ifndef __ANYGDE_RCF_TASK_ALPHAFILTER_SERVANT_H__
#define __ANYGDE_RCF_TASK_ALPHAFILTER_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"
#include <stdlib.h>
#include <time.h>
#define RandCoef2053 2053	
#define RandCoef13849 13849
#define MODUL65536 65536
//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeAlphaFilterTask, "I_GdeAlphaFilterTask")
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

		// map reduce
		RCF_METHOD_V1(void, SetParameter, GdeJobParameter&)
		RCF_METHOD_V1(void, AddParameterSurvey, std::vector<GdePosition>&)
		RCF_METHOD_V1(void, SetEvent, const ServiceHandle&)
		RCF_METHOD_V1(void, SetMapTask, const JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetMapTask)
		RCF_METHOD_R1(int, MapStart, JobParameter*)
		RCF_METHOD_V2(void, Map, MapKey*, MapValue*)
		RCF_METHOD_R0(int, Map)	// in a batch
		RCF_METHOD_V1(void, MapFlush, unsigned long long)
		RCF_METHOD_V0(void, MapCombine)
		RCF_METHOD_V0(void, MapShard)	// transport chunk
		RCF_METHOD_R1(bool, IsMapDone, const string&)

		RCF_METHOD_V1(void, SetReduceTask, const JobTaskServer&)
		RCF_METHOD_R0(JobTaskServer, GetReduceTask)
		RCF_METHOD_R0(int, ReduceStart)
		RCF_METHOD_V2(void, Reduce, unsigned long long, ReducePairVector&)
		RCF_METHOD_R0(int, Reduce)	// in a batch
		RCF_METHOD_V0(void, ReduceFlush)
		RCF_METHOD_R1(bool, IsReduceDone, const string&)

		// output
		RCF_METHOD_V4(void, ReadData, std::string, std::vector<char>&, int, long long)
		RCF_METHOD_V5(void, WriteData, std::string, std::vector<char>&, int&, long long, int)
		RCF_METHOD_V3(void, GetDataDirectory, int, bool, string&)
		RCF_METHOD_V2(void, GetFileLength, std::string, long long&)
	RCF_END(I_GdeAlphaFilterTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeAlphaFilterTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeAlphaFilterTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeAlphaFilterTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeAlphaFilterTaskServant *m_parent;
			MapKey *m_key;
			MapValue *m_value;
			std::vector<long> &m_sequenceOrders;
			bool &m_ispremode;
			std::vector<int> &m_cmpcounts;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CGdeAlphaFilterTaskServant();
		~CGdeAlphaFilterTaskServant();

	public:
		//
		// service interface
		//
		void Start(); 
		void DoScheduleEntries(std::deque<RequestEntry *> &entries);
		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);

		/*!
		*
		**/
		void SetParameter(GdeJobParameter &parameter);
		void AddParameterSurvey(std::vector<GdePosition> &survey);
		void SetEvent(const ServiceHandle &eventhandle);

		//
		//
		//
		int MapStart(JobParameter*);
		void Map(MapKey *key, MapValue *value);
		int Map();
		void MapFlush(unsigned long long chunkuuid);
		void MapCombine();
		void MapShard();

		//
		//
		//
		int ReduceStart();	// reduce shuffle
		void Reduce(unsigned long long chunkuuid, ReducePairVector &reducepairs);
		int Reduce();
		void ReduceFlush();

	protected:

		//
		//
		//
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);

		//
		//
		//
		void DoGetMapPairVector(unsigned long long chunkuuid, MapPairVector &mappairs);
		void DoGetReducePairVector(unsigned long long chunkuuid, ReducePairVector &reducepairs);
	private:

		/*!
		*  AlphaFilter
		**/
		void DoAlphaFilter(MapKey *key, MapValue *value);
	public:
		/*!
		*
		**/
		void sortData( float * lpData, int nNum );
		float oneSampleAlphaFilter( float * lpData, int nNum, float lAlpha );
		bool isValidTrace( float * pTrace, int nLen );
		void alphaFilter( float * * * pSumTrace, int nLineWidth, int nCDPWidth, int nSampNum, float fAlpha, float * pOutTrace );
		void combineTraceData( float * pOutTrace, float * pOrgTrace, float * pRSITrace, int nSampNum, float fDomainFreq, float fLevel );
				
		/*!
		*
		**/
		double *alloc1d(int);	//开辟一个一维double数组
		double **alloc2d(int, int); //开辟一个二维double数组
		// 开辟一个二维double数组, 其中每一列的长度都不同,用于为隐层单元m_hiddenUnits分配内存空间
		double **alloc2d(int, int*); 
		int **alloc2d_int(int, int);
		// 开辟一个三维变长double数组, 用于为隐层单元m_hiddenWeights分配内存空间
		double ***alloc3d(int, int *); 
		double ***alloc3d(int, int, int);
		float  ***alloc3d_float(int, int, int);
		void free1d(double *); //释放一维double
		void free2d(double **, int); //释放二维int数组
		void free2d(int **, int); //释放二维double数组
		void free3d(double ***, int, int*); //与alloc3d(int, int*)对应的free3d
		void free3d(double ***, int, int);	// free3d for alloc3d(int, int, int)
		void free3d_float(float ***, int, int);	// free3d for alloc3d(int, int, int)
		void randperm(int*, int, unsigned int seed);  // 返回1-n的整数的随机排列
		// 以下3个函数与神经网络无关
		double** convert(double*, int, int);
		void convert(double**, double*, int, int);
		double** convertAll(double**, int, int, int);
		// 生成高斯分布的随机数, 均值为mu, 方差为ro, seed为种子数
		double randn(double mu, double ro, double& seed);
		int rand2(int n);
		// normalize data
		// method == 1: (mean,var)
		// method == 0: (min,max) 
		// change == true: change data
		// change == false: only compute params for data distribution, do not change data
		// (mean,var) and no change by default 
		void normalizeData(double* x, int num, double& p1,double& p2, int method = 1, bool change=false) ;
		// generate random weights and etas between layers
		// input->1st hidden, last hidden-> output layer, 
		// etaflag == true, for weights; false, for etas
		void randWeights(double **w, int m, int n, double& seed, bool etaflag = false);
		// between hidden layers
		void randWeights3d(double ***w, int l, int* m, double &seed, bool etaflag = false);
				
		/*!
		*
		**/
		int BufferCost(int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency);

		void DividFrequency(float *pInData, 
			int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency, 
			int nLevel, 
			float *pOutData, 
			float *pBuffer);
		void DividFrequencyRGB(float *pInData,  
			int nSamples,  
			int nSampleInterval, //us
			int nTop,
			int nBottom, 
			int nMaxFrequency, 
			int nLevel, 
			float *pOutData, 
			float *pBuffer);
		void RemoveNoise(float *pInData, 
			int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency, 
			int nLevel, 
			float *pOutData, 
			float *pBuffer);

		void DivFrequencyRemoveNoise(float *pInData, 
			int nSamples, 
			int nSampleInterval, //us
			int nMaxFrequency, 
			int nLevel, 
			int nRemoveNoise, 
			float *pOutData, 
			float *pBuffer);

		void getRSIParameter(int nMainFreq, 
			int nSamples, 
			int nSampInterval, 
			int& nMaxFreq, 
			int& nLevel, 
			int& nBufferSize);

		void RemoveNoise(float **pInData, 
			int nSamples, 
			int nSampleInterval, //ms
			int nTrace,
			float fScal, 
			float fLevel,
			float *pOutData);   //--- no use ---

		void kkwave(double *pr,double *pi,int n,int k,double *fr,double *fi,int l,int il);
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	};
}

#endif
