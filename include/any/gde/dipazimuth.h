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
#ifndef __ANYGDE_DIP_AZIMUTH_H__
#define __ANYGDE_DIP_AZIMUTH_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CDipAzimuth : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CDipAzimuth();
		~CDipAzimuth();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle(HandlerStruct &handlerstruct);

		/*!
		*
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		*
		**/
		void DoGetTraceHead(std::vector<double> &results);
		
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
			float *fCoeff,//镶边系数
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
	public:
		float m_fSampleInter;//单位s
		int m_nMaxBufferSize;
		int m_nOutSampNum;
		float* m_pVelo;
		int m_nCompSpaceLen;
		bool m_isfirst;

		int m_binnum;
		int *m_mainfreqs;
		int m_nOutputCubeNum;
		int m_nOutputTimeInc;//单位ms
		int *m_pWinLen;
		int m_nWinLen;
		float m_fCdpInterval;
		float m_fLineInterval;
		int m_nAngleX;
		int m_nAngleY;
		float m_fMinAngleX;
		float m_fMaxAngleX;
		float m_fMinAngleY;
		float m_fMaxAngleY;
		int m_enumMethod;
		int m_enumFitMode;
		int m_enumWinType;
		int m_enumCohMode;
		int m_iPrinFilter;
		int m_bHilbTrans;
		int m_enumSmoothMethod;
		bool m_isoutputdipazimtuh;
		bool m_isoutputlinecdpdip;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
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
