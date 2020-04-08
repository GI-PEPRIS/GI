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
#ifndef __ANYGDE_RCF_TASK_DIPAZIMUTH_SERVANT_H__
#define __ANYGDE_RCF_TASK_DIPAZIMUTH_SERVANT_H__

//
#include"anygde.h"
#include "gdetaskservantcommon.h"

//
namespace AnyGDE
{
	// interface
	RCF_BEGIN(I_GdeDipAzimuthTask, "I_GdeDipAzimuthTask")
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
	RCF_END(I_GdeDipAzimuthTask)

	/*!
	*
	**/
	class ANYGDE_CLASS CGdeDipAzimuthTaskServant : public CGdeTaskServantCommon
	{
		// callback
		typedef RcfClient<I_GdeDipAzimuthTask> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		class MapTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			MapTask(int taskcount, int index, CGdeDipAzimuthTaskServant *parent, MapKey *key, MapValue *value, \
				std::vector<long> &sequenceOrders, bool &ispremode, std::vector<int> &cmpcounts, CAnyCPUScheduler *scheduler);
			~MapTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CGdeDipAzimuthTaskServant *m_parent;
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
		CGdeDipAzimuthTaskServant();
		~CGdeDipAzimuthTaskServant();

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
		*  DipAzimuth
		**/
		void DoDipAzimuth(MapKey *key, MapValue *value);
	public:
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

		/*!
		*
		**/
		void BartlettWin(int n,float*fCoeff);
		void BlackmanWin(int n,float*fCoeff);
		void HammingWin(int n,float*fCoeff);
		void HanningWin(int n,float*fCoeff);
		void ChebyshevWin(int n,float*fCoeff);
		void KaiserWin(int n,float alpha,float*fCoeff);
		void TriangWin(int n,float*fCoeff);
		void BarthannWin(int n,float*fCoeff);
		void BlackmanharrisWin(int n,float*fCoeff);
		void BohmanWin(int n,float*fCoeff);
		void ParzenWin(int n,float*fCoeff);
		void TukeWin(int n,float*fCoeff);
		float Bessel_I_0(float x);

		float TrueDip(float xdiptan,float ydiptan);
		float Azimuth(float xdiptan,float ydiptan);
		float LinearInsert(float x1,float y1,float x2,float y2,float x);
		void HilbertTransform(float*fReal,float*fImage,int nReal,int nImage,int nLength);
		int aldle(float*a,int n,int m,float*c);

		float ReCoherent(float**re,int nWin,int nTrace);
		float ReCoherent(float**re,float*fCoeff,int nWin,int nTrace);
		float Coherent2(float**re,float**im,int nWin,int nTrace);
		float Coherent2(float**re,float**im,float*fCoeff,int nWin,int nTrace);

		float ReStdev(float**re,int nWin,int nTrace);
		float ReStdev(float**re,float*fCoeff,int nWin,int nTrace);
		float Stdev2(float**re,float**im,int nWin,int nTrace);
		float Stdev2(float**re,float**im,float*fCoeff,int nWin,int nTrace);

		float ReDiscrete(float**re,int nWin,int nTrace);
		float ReDiscrete(float**re,float*fCoeff,int nWin,int nTrace);
		float Discrete2(float**re,float**im,int nWin,int nTrace);
		float Discrete2(float**re,float**im,float*fCoeff,int nWin,int nTrace);

		float ReHOS(float**re,int nWin);
		float ReHOS(float**re,float*fCoeff,int nWin);
		float HOS2(float**re,float**im,int nWin);
		float HOS2(float**re,float**im,float*fCoeff,int nWin);

		void TwoCurve(float*x,float*y,float&a,float&b,float&c,int n);
		float SingleCurveDip(float*diptan,float*s,float&xdip,int nDip);
		float ReSingleCurveDip(float*diptan,float*s,float&xdip,int nDip);

		void PrincipalComponentFiltering2D(float**fData_in,float*p,int nX,int nTime,int nWin,int nP,float**fData_out);

		void PlaneCenterWin(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void PlaneMultiWin(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeCenterWin(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeMultiWin(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);

		void PlaneCenterWin_new(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void PlaneMultiWin_new(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeCenterWin_new(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeMultiWin_new(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,int nAngleY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,int iHilbTrans,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);


		void PlaneCenterWindow(float**fData,int nTraceLen,int nWinLen,float dx,float dt,int nAngle,float fMinAng,float fMaxAng,
			int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDip,float*fCoh);
		void PlaneCenterWindowHilb(float**fData,float**fData1,int nTraceLen,int nWinLen,float dx,float dt,int nAngle,float fMinAng,
			float fMaxAng,int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDip,float*fCoh);
		void PlaneMultiWindow(float**fData,int nTraceLen,int nWinLen,float dx,float dt,int nAngle,float fMinAng,float fMaxAng,
			int iFitMode,int iCohType,int iFiterMode,float*fVel,float*fCoeff,float*fDip,float*fCoh);
		void PlaneMultiWindowHilb(float**fData,float**fData1,int nTraceLen,int nWinLen,float dx,float dt,int nAngle,float fMinAng,
			float fMaxAng,int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDip,float*fCoh);

		void PlaneCenterWindow_new(float**re,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,float fMinAngX,float fMaxAngX,
			int nAngleY,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDipX,float*fDipY,float*fCoh);
		void PlaneCenterWindowHilb_new(float**re,float**im,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,float fMinAngX,
			float fMaxAngX,int nAngleY,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDipX,
			float*fDipY,float*fCoh);
		void PlaneMultiWindow_new(float***re,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,float fMinAngX,float fMaxAngX,
			int nAngleY,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDipX,float*fDipY,float*fCoh);
		void PlaneMultiWindowHilb_new(float***re,float***im,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngleX,float fMinAngX,float fMaxAngX,
			int nAngleY,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDipX,float*fDipY,float*fCoh);

		void CubeCenterWindow(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,int nAngY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,
			float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeCenterWindowHilb(float***fData,float***fData1,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,
			int nAngY,float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeMultiWindow(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,int nAngY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,
			float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeMultiWindowHilb(float***fData,float***fData1,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,
			int nAngY,float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,
			float*fVel,float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);

		void CubeCenterWindow_new(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,int nAngY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,
			float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeCenterWindowHilb_new(float***fData,float***fData1,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,int nAngY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,
			float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeMultiWindow_new(float***fData,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,int nAngY,float fMinAngX,
			float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,float*fCoeff,float*fDip,
			float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);
		void CubeMultiWindowHilb_new(float***fData,float***fData1,int nTraceLen,int nWinLen,float dx,float dy,float dt,int nAngX,int nAngY,
			float fMinAngX,float fMaxAngX,float fMinAngY,float fMaxAngY,int iFitMode,int iCohType,int iFilterMode,float*fVel,
			float*fCoeff,float*fDip,float*fAzimuth,float*fCoh,float*fDipX,float*fDipY);

		float CoherenceNoCoeff(float**fData,int nTrace,int nWin,int iCohType);
		float CoherenceWithCoeff(float**fData,int nTrace,int nWin,float*fCoeff,int iCohType);
		float CoherenceNoCoeffHilb(float**fData,float**fData1,int nTrace,int nWin,int iCohType);
		float CoherenceWithCoeffHilb(float**fData,float**fData1,int nTrace,int nWin,float*fCoeff,int iCohType);

		void CurveDip(float*xdiptan,float*ydiptan,float*s,float&xdip,float&ydip, float&s1,int nDip) ;
		void CurveDip1(float*xdiptan,float*ydiptan,float*s,float&xdip,float&ydip,float&ss, int nDipX,int nDipY);

		void radoncg(float **LLhreal,float *Lhdreal,float* weight,float *xn,int nq,float eps);
		void RDPmul(float **LLh,float *p,float *result,int nq);
	public:
		void DipAzimuth(float***fData,//5*5*nTraceLen,3*3*nTraceLen
			int nTraceLen,//trace length
			int nWinLen,//time window sample number
			float dx,//distance of xlines(m)
			float dy,//distance of inlines(m)
			float dt,//sample interval of trace(s)
			int nAngleX,//angle number of inline
			int nAngleY,//angle number of xline
			float fMinAngX,//min angle number of inline (sample number)
			float fMaxAngX,//max angle number of inline(sample number)
			float fMinAngY,//min angle number of xline(sample nummber)
			float fMaxAngY,//max angle number of xline(sample number)
			int iMethod,//0:2D,1:3D
			int iFitMode,//0:all,1:local
			int iWinType,//0:Center,1:Multi
			int iCohType,//0: Semblance; 1: Stdev 2: Discrete;3 HOS
			int iPrinFilter,   //--- 0: false; 1: true
			int iHilbTrans,   //--- 0: false; 1: true
			int iFilterMode,//0:false;1:true
			float *fVel,//Vel
			float *fCoeff,//Ïâ±ßÏµÊý
			float*fAzimuth,
			float*fDip,
			float*fCoh,
			float*fDipX,
			float*fDipY);
		void FilterCoefficient(int iMode,int n,float*fCoeff);
		//0: Rectangle;
		//1: Bartlett;
		//2: Blackman;
		//3: Chebyshev;
		//4: Hamming;
		//5: Hann;
		//6: Kaiser;
		//7: Triangle;
		//8: Barthann;
		//9: Blackmanharris;
		//10: Bohman;
		//11: Parzen;
		//12: Tuke;  
		bool isValidTrace(float *pTrace, int nLen);
	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	public:
		float **m_fCoeff;
		float *m_pBuffer;
		float ***m_pSum;
		float ***m_pRSI;
		int m_pSumRSIcount;
		float *m_pCoh;
		float *m_pDip;
		float *m_pAzi;
		float *m_pXDip;
		float *m_pYDip;
		int m_paracount;
	};
}

#endif
