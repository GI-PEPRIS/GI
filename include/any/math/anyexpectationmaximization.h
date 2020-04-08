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
#ifndef __ANYMATH_EXPECTATION_MAXIMIZATION_ALGORITHM_H__
#define __ANYMATH_EXPECTATION_MAXIMIZATION_ALGORITHM_H__

// refer to macro
#include "anymath.h"

const static int GUASSPOINTNUM=30;
const static int EXPONENTPOINTNUM=2000;
const static double errorlimit=0.015;

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyExpectationMaximization
	{
		//
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyExpectationMaximization();

		/*!
		*
		**/
		virtual ~CAnyExpectationMaximization();

	public:
		//
		// 
		//
		/*!
		* a.	输入样本点，并对样本点进行了单位处理；
		* b.	输入高斯积分点和权重；
		* c.	输入指数分布随机数，再通过样本点的处理得到一个广义Gamma分布的随机数来进行Monte Carlo积分；
		* d.	bt参数是对勘探效率赋值；
		* e.	然后还计算了最大，最小值，用于概率密度函数设定。
		**/
		void SetSamples(double *samples, int number, double beta, double N = 1, double minq = 0x7FFFFF, double maxq = 0);

		//
		// given unknown N
		//
		/*!
		*
		**/
		virtual double *MakeEMN(int numberScale, int &maxLoops, double error = errorlimit);

		//
		// given known N
		//
		/*!
		*
		**/
		virtual double *MakeEMKN(int &maxLoops, double error = errorlimit);

	protected:
		/*!
		* a.	计算一些中间参量，并记录到对象中，当参数sita改变时，这些参数会发生变化；
		* b.	而且在这里对未知参量N进行了计算。
		**/
		virtual double InitParameter(double sita[3])=0;

		/*!
		*
		**/
		virtual void KInitParameter(double sita[2])=0;

	private:
		//
		//
		//
		/*!
		* 概率密度函数
		**/
		virtual double GetPDF(double x,double b,double s) = 0;

		//
		//
		//
		/*!
		* EM迭代的目标函数
		**/

		virtual double ObjectiveFunction(double sita[2])=0;
		/*!
		* 方向目标函数
		**/
		double DirectionFunction(double t,double z0[2],double a[2]);

		/*!
		* 一维最优搜索
		* a.	首先用进退法搜索极值区间
		* b.	再用黄金分割得到最优解
		**/
		double Minim(double es,double z0[2],double a[2]);

		/*!
		* 二维最优化方向搜索，不需要导数
		**/
		double *Powell(double es);

		//
		//
		//
		/*!
		*
		**/
		bool DoLoadGaussTable();

		/*!
		*
		**/
		bool DoLoadGammaTable(double sum);

	public:
		double *m_samples;
		int m_number;
		double m_N;
		double *m_Gauss;
		double *m_Gaussw;
		double *m_rnGamma;
		double m_qmax;
		double m_qmin;
		double m_beta;	
		double m_Srou;
		double m_S1;
		double *m_sita0;
		double **m_r1;
		double **m_r2;
		double *m_bs;
		double *m_st;
		double m_shift;
	};
}
#endif