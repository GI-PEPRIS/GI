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
		* a.	���������㣬��������������˵�λ����
		* b.	�����˹���ֵ��Ȩ�أ�
		* c.	����ָ���ֲ����������ͨ��������Ĵ���õ�һ������Gamma�ֲ��������������Monte Carlo���֣�
		* d.	bt�����ǶԿ�̽Ч�ʸ�ֵ��
		* e.	Ȼ�󻹼����������Сֵ�����ڸ����ܶȺ����趨��
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
		* a.	����һЩ�м����������¼�������У�������sita�ı�ʱ����Щ�����ᷢ���仯��
		* b.	�����������δ֪����N�����˼��㡣
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
		* �����ܶȺ���
		**/
		virtual double GetPDF(double x,double b,double s) = 0;

		//
		//
		//
		/*!
		* EM������Ŀ�꺯��
		**/

		virtual double ObjectiveFunction(double sita[2])=0;
		/*!
		* ����Ŀ�꺯��
		**/
		double DirectionFunction(double t,double z0[2],double a[2]);

		/*!
		* һά��������
		* a.	�����ý��˷�������ֵ����
		* b.	���ûƽ�ָ�õ����Ž�
		**/
		double Minim(double es,double z0[2],double a[2]);

		/*!
		* ��ά���Ż���������������Ҫ����
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