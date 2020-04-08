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
#ifndef __ANYGDE_RCF_TASK_INSTANTATTRIBUTE_SERVANT_H__
#define __ANYGDE_RCF_TASK_INSTANTATTRIBUTE_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeInstantAttributeTask, "I_GdeInstantAttributeTask")
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
	RCF_END(I_GdeInstantAttributeTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeInstantAttributeTaskServant : public CGdeTaskServantCommon
	{
		struct REGRESSION
		{
			float m_la;
			float m_lb;
			REGRESSION() : m_la(0), m_lb(0)
			{
			}
			const REGRESSION &operator=(const REGRESSION &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_la = other.m_la;
				m_lb = other.m_lb;
				return *this;
			}
		};
		// callback
		typedef RcfClient<I_GdeInstantAttributeTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeInstantAttributeTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeInstantAttributeTaskServant *m_parent;
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
		CGdeInstantAttributeTaskServant();
		~CGdeInstantAttributeTaskServant();

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
		*  InstantAttribute
		**/
		void DoInstantAttribute(MapKey *key, MapValue *value);
		void InstantAttributes(float *pInData, 
			int nSamples, 
			float fSampleInterval, 
			int nDomF,
			float *pAmp, 
			float *pPha, 
			float *pFre);
		void InstantAttributes2(float *pInData, 
			int nSamples, 
			float fSampleInterval, 
			int nDomF,
			int nWindow,
			float *pAmp, 
			float *pPha, 
			float *pFre,
			float *pmFre, float *pbFre, float *pdFre);
		void ArcLengthOneTrace(float*fAmpute,float*fArcLength,int nTime,int nWin);
		void Model();
		void test();
		void PseudoEntropy(float*fAmpute,float*fPseudoEntropy,int nTime,int nWin);
		void Variance(float*fAmpute,float*fVariance,int nTime,int nWin);
		void Skew(float*fAmpute,float*fSkew,int nTime,int nWin);
		void Kurtosis(float*fAmpute,float*fKurtosis,int nTime,int nWin);
		float MeanCompute(float*fInput,int n);
		float VarianceCompute(float*fInput,float fMean,int n);
		float SkewCompute(float*fInput,float fMean,float fVariance,int n);
		float KurtosisCompute(float*fInput,float fMean,float fVariance,int n);
		void freqdiff(float*fFreq,float*fAmplitude,float*fFreqdiff,int nWin,int nTime);
		void RSEnergyHalfTimeOneTrace(float*fAmpute,float*fEnergyHalfTime,int nTime,int nWin);
	private:
		/*!
		*  Curvature
		**/
		void DoCurvature(MapKey *key, MapValue *value);
	private:
		/*!
		* Window
		**/
		void DoWindow(MapKey *key, MapValue *value);
		bool RegressionCalculate(float *lpDensity,float *lpVelocity,int nCount, REGRESSION *pReg);
		float VelocityFromImpedance(float lImpedancy, const REGRESSION &Reg);
		bool VpVsRegression(float *lpVs, float *lpVp, int nCount, REGRESSION *pReg);
		float VsFromVp(float Vp, const REGRESSION &Reg);
		float ArcLengthOneWin(float*fAmpute,int nWin);
		float VarianceOneWin(float*fAmpute,int nWin);
		float SkewOneWin(float*fAmpute,int nWin);
		float KurtosisOneWin(float*fAmpute,int nWin);
		float PseudoEntropy(float*fAmpute,int nWin);
		//float MeanCompute(float*fInput,int n);
		//float VarianceCompute(float*fInput,float fMean,int n);
		//float SkewCompute(float*fInput,float fMean,float fVariance,int n);
		//float KurtosisCompute(float*fInput,float fMean,float fVariance,int n);
		float EnergyHalfTimeOneWin(float*fAmpute,int nWin);
		bool getCurrentValue( int iMethod, int nCurrentTopTime, int nCurrentBottomTime, float fMinValue, float fMaxValue, float fImpA, float fImpB, float bImp, float * pTrace, float * pVeloTrace, int nSpaceLen, int nStartTime, int nSampNum, int nSampInc, float & fValue );
		float computeTimeWinAttr( int iMethod, float * pTrace, int iStartSamp, int iEndSamp, int nSampInc, float fMinValue, float fMaxValue );
		float statisticThick( float * pTrace, float * pVeloTrace, int iStartSamp, int iEndSamp, int nSampInc, int iMethod, float fMinValue, float fMaxValue, float fImpA, float fImpB, bool bImp );
		float atk( float * x, float * y, float xx, int n, int m );
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
		float* m_pInData;
		float* m_pOutTrace0;
		float* m_pOutTrace1;
		float* m_pOutTrace2;
		float* m_pOutTrace3;
		float* m_pOutTrace4;
		float* m_pOutTrace5;

		float* m_pVeloTrace;
		float* m_pTrace;
		int m_pVeloTracecount;
		int m_pTracecount;
	};
}

#endif
