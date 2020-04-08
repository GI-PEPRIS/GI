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
#ifndef __ANYGDE_ALPHAFILTER_H__
#define __ANYGDE_ALPHAFILTER_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include <stdlib.h>
#include <time.h>

#define RandCoef2053 2053	
#define RandCoef13849 13849
#define MODUL65536 65536

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAlphaFilter : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAlphaFilter();
		~CAlphaFilter();

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
	public:
		float m_fSampleInter;//单位s
		int m_nMaxBufferSize;
		int m_nOutSampNum;
		int m_nCompSpaceLen;
		int m_nOutputTimeInc;//单位ms

		bool m_isdomainfreq;
		double m_domainfreq;
		double m_alpha;
		double m_level;
		int m_linebinnum;
		int m_cdpbinnum;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;
	};
}
#endif
