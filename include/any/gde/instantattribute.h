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
#ifndef __ANYGDE_INSTANTATTRIBUTE_H__
#define __ANYGDE_INSTANTATTRIBUTE_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CInstantAttribute : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CInstantAttribute();
		~CInstantAttribute();

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

		/*!
		*
		**/
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

		/*!
		*
		**/
		void freqdiff(float*fFreq,float*fAmplitude,float*fFreqdiff,int nWin,int nTime);

		/*!
		*
		**/
		void RSEnergyHalfTimeOneTrace(float*fAmpute,float*fEnergyHalfTime,int nTime,int nWin);
	public:
		int m_nOutSampNum;

		bool m_bOutputAmp;
		bool m_bOutputFreq;
		bool m_bOutputPhase;
		bool m_bOutputWeighted;
		bool m_bOutputBand;
		bool m_bOutputDomain;
		bool m_bOutputArc;
		bool m_bOutputThin;
		bool m_bOutputEHT;
		bool m_bOutputEntropy;
		bool m_bOutputVariance;
		bool m_bOutputSkew;
		bool m_bOutputKurtosis;
		std::vector<double> m_para1s;
		std::vector<double> m_para2s;
		std::vector<double> m_para3s;

		float* m_pInData;
		float* m_pOutTrace0;
		float* m_pOutTrace1;
		float* m_pOutTrace2;
		float* m_pOutTrace3;
		float* m_pOutTrace4;
		float* m_pOutTrace5;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}
#endif
