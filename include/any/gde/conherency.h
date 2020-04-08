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
#ifndef __ANYGDE_CONHERENCY_H__
#define __ANYGDE_CONHERENCY_H__

#define SMALLVAL	1e-20

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include "anygdedataset.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CConherency : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CConherency();
		~CConherency();

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
		void correlation31(float***fAmpute,float*fCoeff,float*fDip,float*fAzimuth,int nX,int nY,int nX1,int nY1,
			int nTime,int nWin,int nBool,float dt,float dx,float dy,float*fVel);
		void correlation3(float***fAmpute,float*fCoeff,float*fDipx,float*fDipY,int nX,int nY,int nX1,int nY1,
			int nTime,int nWin);
		float MaxEigVal(float**C, int Row, int nIters, float tr);
		bool isValidTrace(float *pTrace, int nLen);
		float LinearInsert(float x1,float y1,float x2,float y2,float x);
	public:
		float m_fSampleInter;//单位s
		int m_nMaxBufferSize;
		int m_nOutSampNum;
		std::vector<CAnyGdeDataSet*> m_datasets;//0:dip,1:azimuth
		std::vector<bool> m_isgdes;
		std::vector<float> m_pVelo;
		int m_nCompSpaceLen;

		int m_binnum;
		std::vector<int> m_mainfreqs;
		int m_nOutputCubeNum;
		int m_nOutputTimeInc;//单位ms
		std::vector<int> m_pWinLen;
		float m_fCdpInterval;
		float m_fLineInterval;
		int m_enumCoherentMethod;//0:normal,1:dip
		int m_enumDipUnit;//0:角度,1弧度
		int m_enumAziUnit;//0:角度,1弧度

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;

		// correlation
		float **m_C;
		int m_C_count;
		float **m_D;
		int m_D_count;
		int m_D_sub_count;
		float *m_fDipX;
		int m_fDipX_sub_count;
		float *m_fDipY;
		int m_fDipY_sub_count;
		// DoHandle
		float ***m_pSum;
		int m_pSum_sub_count;
		float ***m_pRSI;
		int m_pRSI_sub_count;
		float *m_pDip;
		int m_pDip_sub_count;
		float *m_pAzi;
		int m_pAzi_sub_count;
		float *m_pBuffer;
		int m_pBuffer_sub_count;
		float **m_fCoeff;
		float *m_pVelostar;
		float *m_pCoh;
		int m_pCoh_sub_count;
		// DividFrequency
		double *m_cof;
		int m_cof_sub_count;
		double *m_wave;
		int m_wave_sub_count;
	};
}
#endif
