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
#ifndef __ANYMATH_FITTING_STRATEGY_H__
#define __ANYMATH_FITTING_STRATEGY_H__

// refer to macro
#include "anymath.h"

// refer to geo
#include "any/base/anygeom.h"
using namespace AnyBase;

// namespace
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyFittingStrategy
	{
	public:
		/*!
		*
		**/
		enum FittingType
		{
			FT_Unknown = -1,
			FT_Linear,
			FT_Power,
			FT_Exponential,
			FT_Log,
			FT_InverseExponential,
			FT_S,
			FT_Z,
			FT_Quadratic,
			FT_Cubic,
			FT_Lifecycle,
			FT_Max,
		};

		/*!
		* formula definition for kinds of fitting curves
		**/
		struct FittingLine
		{
			// steps
			int m_steps;

			// type
			short m_type;

			// x-axis variables
			double m_start;
			double m_end;
			int m_lifeNumber;
			double m_mode; // for lifecycle
			double m_extreme; // the predicated

			// coffs
			double m_a;
			double m_b;
			double m_c;
			double m_d;
			double m_e; // for lifecycle
			double m_f; // for lifecycle

			/*!
			*
			**/
			FittingLine() : m_steps(255), m_type(FT_Unknown), m_start(0.), m_end(0.), m_lifeNumber(3), m_mode(0.), m_extreme(0.), m_a(0.), m_b(0.), m_c(0.), m_d(0.), m_f(0.)
			{
			}

			/*!
			* 
			**/
			const FittingLine &operator=(const FittingLine &other)
			{
				if(&other == this)
				{
					return *this;
				}

				// steps
				m_steps = other.m_steps;
				m_type = other.m_type;
				m_start = other.m_start;
				m_end = other.m_end;
				m_lifeNumber = other.m_lifeNumber;
				m_mode = other.m_mode; // for lifecycle
				m_extreme = other.m_extreme; // the predicated
				m_a = other.m_a;
				m_b = other.m_b;
				m_c = other.m_c;
				m_d = other.m_d;
				m_e = other.m_e; // for lifecycle
				m_f =other.m_f; // for lifecycle

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
		CAnyFittingStrategy();

		/*!
		*
		**/
		virtual ~CAnyFittingStrategy();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetSamples(const CGeoPoint<double> *const samples, int number);

		/*!
		*
		**/
		const CGeoPoint<double> *GetSamples(int &number) const;
		
		/*!
		*
		**/
		void Release();

		//
		//
		//
		/*!
		*
		**/
		void MakeFitting(FittingLine &parameter, bool isForPredication = false);
		void GetInterpolations(const CGeoPoint<double> *const ctrlPts, int ctrlNumber, CGeoPoint<double> **interPts, int &interNumber, int interpolations);
		void GetFittingTypeName(int type,string& name);

		//
		//
		//
		/*!
		//Ŀ��: ����һ��۲�����(t, q), ��������Ӧ���������D��b
		//n: ���ݵ������n>=5;
		//t: ʱ�䣬Ϊ��nԪ�ص�һά����
		//q: ����ʱ��t��Ӧ�ģ��������ݣ�Ϊ��nԪ�ص�һά����
		//D: n��Ԫ�ص�һά���飬���ڷ��ز���D�ļ�����
		//b: n��Ԫ�ص�һά���飬���ڷ��ز���b�ļ�����
		//Ҫ��: t�밴��С�����˳������
		//����ֵ��Ϊ��D��������ʱ�����������ں�����PLEģ������Ҫ�õ�
		//��Ҫ�ر�ע�⣺���ڼ���Ĵ��������Ҫ����������n��t��q��Ԫ�ظ�����˳�������޸�
		//�ó��򷵻�ʱ������t��q��D��b��Ԫ�ظ�����Ϊ�����޸ĺ��n
		//��ģ��ļ��㲽�裺
		//1������Dֵ
		//2����D��������ƽ��deltaD��ʹD��Ϊ����
		//3����D����С�����˳�����У�t���ֲ��䣩
		//4��ȥ��D�е��ظ����ݣ�ͬʱҲȥ����D���Ӧ��t�е����ݣ�
		//5���������b
		//6����b�еĳ��ֵļ�������ֵ�ü�Ȩƽ���ķ�������Ϊ����
		**/
		void DbFitting(int &n, double *t, double *q, double *D, double *b);
		/*!
		* model analysis
		*Ŀ��: ���ݹ�ʽ: D=-d(lnq)/dt������D��ֵ
		*n: ���ݵ������n>=3;
		*t: ʱ�䣬Ϊ��nԪ�ص�һά����
		*q: ����ʱ��t��Ӧ�ģ��������ݣ�Ϊ��nԪ�ص�һά����
		*D: n��Ԫ�ص�һά���飬���ڷ��ؼ�����
		*Ҫ��: t�밴��С�����˳������
		**/
		void DeclineD(int n, double *t, double *q, double *D);
		/*!
		//Ŀ��: ���ݹ�ʽ: b=d(1/D)/dt������b��ֵ
		//n: ���ݵ������n>=3;
		//t: ʱ�䣬Ϊ��nԪ�ص�һά����
		//D: ����ʱ��t��Ӧ�ģ�D��Ϊ��nԪ�ص�һά����
		//b: n��Ԫ�ص�һά���飬���ڷ��ؼ�����
		//Ҫ��: t�밴��С�����˳������
		**/
		void DeclineB(int n, double *t, double *D, double *b);

		/*!
		*
		**/
		void ArpsFitting(int Nxy, double *x, double *y, double Q0, double a0, double &n);
		double ArpsProduction(double t, double Q0, double a0, double n);
		double ArpsReserve(double t0, double t1, double Q0, double a0, double n);
		
		/*!
		*______��ֵ����______
		*Ŀ��: ���㱻������ΪIFun�����䡾a,b���ڵĻ���ֵ, �ұ�������IFun���Ա����⣬û������������Ҫ����
		*������: ���������ý���ʽ���������
		*a,b: ���ֵ��ϡ�����, a<b;
		*IFun:ָ�򱻻�����ֵ����ĳ����ָ��;
		*IFunPs: һά���飬����IFun�����漰�Ĳ���ֵ;
		*IPs: һά����IFunPs��Ԫ�ظ���;
		*S: ���ּ�����
		*n: ������ֵ���ּ���ʱ���䡾a,b���ĵȷָ�����n>=1��ȱʡֵΪ50��, һ����˵��nԽ�󣬼��㾫��Խ��
		*ע: ���γ�����ø�����������ʽ������ֵ���ֵļ���
		**/
		double MakeNumericalIntegration(int n, double *x, double *f);
		double MakeNumericalIntegration(double a, double b, double (*IFun)(double x), int n);

		/*!
		* ��ȡDoungģ�͵�����4������: a��m��q0��q8
		* n: ���ݵ������n>2;
		* t: ʱ�䣬Ϊ��mԪ�ص�һά����
		* q: ����ʱ��t��Ӧ�ģ�������Ϊ��nԪ�ص�һά����
		* Q: ����ʱ��t��Ӧ�ģ��ۻ�������Ϊ��nԪ�ص�һά����
		**/
		void DoungFitting(int n, double *t, double *q, double *Q, double &aa, double &m, double &q0, double &q8);
		double DoungProduction(double t, double a, double m, double q0, double q8);
		double DoungReserve(double t0, double t1, double a, double m, double q0);

		/*!
		* �����۲����������PLEģ�͵�4������
		* m: ���ݵ������m>2;
		* t: ʱ�䣬Ϊ��mԪ�ص�һά����
		* q: ����ʱ��t��Ӧ�ģ��������ݣ�Ϊ��mԪ�ص�һά����
		* D: ����ʱ��t��Ӧ�ģ��ݼ������ݣ�Ϊ��mԪ�ص�һά����
		* n��D1��D8��qi: Ϊ�����δ֪����
		**/
		void PLEFitting(int m, double *t, double *q, double &n, double &D1, double &D8, double &qi);
		double PLEProduction(double t, double n, double D1, double D8, double qi);
		double PLEReserve(double t0, double t1, double n, double D1, double D8, double qi);

		/*!
		*
		**/
		void SEPDFitting(double C1, double C2, double r1, double C3, double C4, double r2, double &n, double &Tao);
		double SEPDProduction(double t, double q0, double n, double Tao);
		double SEPDReserve(double t0, double t1, double q0, double n, double Tao);

		/*!
		//m: ʵ�����ݸ���
		//t: ʱ������, t>0��m��Ԫ�ص�һά����
		//G: (��ʱ���Ӧ��)�ۻ���������, m��Ԫ�ص�һά����
		//����ֵ����������: K��a��n
		**/
		void LGMFitting(int m, double *t, double *G, double &K, double &a, double &n);
		double LGMProduction(double t, double K, double a, double n);
		double LGMReserve(double t0, double t1, double K, double a, double n);

		//
		//
		//
		/*!
		*
		**/
		bool TrendSurfaceAnalysis(double *x, double *y, double *z, int n, double *P, short type = 0);
		int DegreePolynomialFitting(double *x, double *y, int m, int n, double *a, double *OParam);

	private:
		//
		//
		//
		/*!
		*
		**/
		void GetFittingSequence(double **x, double **y, short type, const CGeoPoint<double> *const samples, int number, bool isForPredication);

		/*!
		*
		**/
		void DoCalcFittingParameter(FittingLine &parameter, double a, double b);

		/*!
		*
		**/
		void DoMakePolynomialPredication(FittingLine &predication, double *x, double *y, int number);

		/*!
		* deprecated function
		**/
		void DoMakeLifecyclePredication(FittingLine &predication, double *x, double *y, int number);

		/*!
		* deprecated function
		**/
		double DoGetLifecylePredication(FittingLine &predication, double trendValue);
		void DoMakeWengLifecyclePredication(FittingLine &predication, double *x, double *y, int number);
		
		bool Bi_TrendSurfaceAnalysis(double *x, double *y, double *z, int n, double *P);
		bool Tri_TrendSurfaceAnalysis(double *x, double *y, double *z, int n, double *P);

	public:
		//
		//
		//
		/*!
		*
		**/
		static void DoLinearRegression(double *x, double *y, int number, double &a);

		/*!
		*
		**/
		static void DoLinearRegression(double *x, double *y, int number, double &a, double &b);

		/*!
		*
		**/
		static bool DoGeneralPolynomialFitting(double *x, double *y, int m, int n, double *a);

		/*!
		*
		**/
		static bool DoMultivariateFitting(double **x, double *y, int m, int n, double *a);

		/*!
		*
		**/
		static int DoWithGassJordan(double **rhs, double **m, int stRank);

		/*!
		*
		**/
		static void DoMakeMatrixProduct(double **rhs, double *m, int nRow, int nCol, double *R);

	private:
		// samples & number
		CGeoPoint<double> *m_samples;
		int m_number;
	};
}

#endif