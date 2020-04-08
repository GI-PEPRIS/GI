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
#ifndef __ANYGDE_TIMEWINATTRIBUTE_H__
#define __ANYGDE_TIMEWINATTRIBUTE_H__

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
	class ANYGDE_CLASS CTimewinAttribute : public CAnyGdeDataHandler
	{
	public:
		struct REGRESSION
		{
			double m_la;
			double m_lb;
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
	public:
		//
		//
		//
		/*!
		*
		**/
		CTimewinAttribute();
		~CTimewinAttribute();

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
		bool RegressionCalculate(float *lpDensity,float *lpVelocity,int nCount, REGRESSION *pReg);
		double VelocityFromImpedance(double lImpedancy, const REGRESSION &Reg);
		bool VpVsRegression(float *lpVs, float *lpVp, int nCount, REGRESSION *pReg);
		double VsFromVp(double Vp, const REGRESSION &Reg);
				
		/*!
		*
		**/
		double ArcLengthOneWin(float*fAmpute,int nWin);
		double VarianceOneWin(float*fAmpute,int nWin);
		double SkewOneWin(float*fAmpute,int nWin);
		double KurtosisOneWin(float*fAmpute,int nWin);
		double PseudoEntropy(float*fAmpute,int nWin);
		double MeanCompute(float*fInput,int n);
		double VarianceCompute(float*fInput,double fMean,int n);
		double SkewCompute(float*fInput,double fMean,double fVariance,int n);
		double KurtosisCompute(float*fInput,double fMean,double fVariance,int n);
						
		/*!
		*
		**/
		double EnergyHalfTimeOneWin(float*fAmpute,int nWin);
								
		/*!
		*
		**/
		bool getCurrentValue( int iMethod, int nCurrentTopTime, int nCurrentBottomTime, double fMinValue, double fMaxValue, double fImpA, double fImpB, double bImp, float * pTrace, float * pVeloTrace, int nSpaceLen, int nStartTime, int nSampNum, int nSampInc, double & fValue );
		double computeTimeWinAttr( int iMethod, float * pTrace, int iStartSamp, int iEndSamp, int nSampInc, double fMinValue, double fMaxValue );
		double statisticThick( float * pTrace, float * pVeloTrace, int iStartSamp, int iEndSamp, int nSampInc, int iMethod, double fMinValue, double fMaxValue, double fImpA, double fImpB, bool bImp );
		double atk( float * x, float * y, double xx, int n, int m );
	public:
		CAnyGdeDataSet *m_dataset;
		bool m_isgde;
		CAnyGdeDataSet *m_VeloIMPdataset;
		bool m_isVeloIMPgde;
		int m_nOutSampNum;

		bool m_OutPutTimeThick;
		bool m_OutPutStatisticThick;
		bool m_OutPutStatisticThickPercent;
		bool m_OutPutRMS;
		bool m_OutPutMean;
		bool m_OutPutMeanAbsolute;
		bool m_OutPutSum;
		bool m_OutPutSumAbsolute;
		bool m_OutPutMin;
		bool m_OutPutMax;
		bool m_OutPutMaxAbsolute;
		bool m_OutPutArc;
		bool m_OutPutEnergyHalfTime;
		bool m_OutPutNumberofCrossZero;
		bool m_OutPutPseudoEntropy;
		bool m_OutPutVariance;
		bool m_OutPutSkew;
		bool m_OutPutKurtosis;
		bool m_OutPutRatio;
		std::vector<double> m_minvalues;
		std::vector<double> m_maxvalues;
		bool m_bImp;
		double m_fImpA;
		double m_fImpB;

		float* m_pVeloTrace;
		float* m_pTrace;
		int m_pVeloTracecount;
		int m_pTracecount;
		
		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}
#endif
