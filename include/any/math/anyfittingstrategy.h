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
		//目的: 给定一组观测数据(t, q), 计算出相对应的两组参数D、b
		//n: 数据点个数，n>=5;
		//t: 时间，为有n元素的一维数组
		//q: （与时间t对应的）产量数据，为有n元素的一维数组
		//D: n个元素的一维素组，用于返回参数D的计算结果
		//b: n个元素的一维素组，用于返回参数b的计算结果
		//要求: t须按由小到大的顺序排列
		//返回值：为对D进行修正时的修正量，在后续的PLE模型中需要用到
		//需要特别注意：由于计算的处理过程需要，结算结果对n、t、q的元素个数及顺序都做了修改
		//该程序返回时，数组t、q、D、b的元素个数都为重新修改后的n
		//该模块的计算步骤：
		//1、计算D值
		//2、对D整体向上平移deltaD，使D都为正数
		//3、对D按从小到大的顺序排列（t保持不变）
		//4、去掉D中的重复数据（同时也去掉与D相对应的t中的数据）
		//5、计算参数b
		//6、对b中的出现的极少数负值用加权平均的方法处理为正数
		**/
		void DbFitting(int &n, double *t, double *q, double *D, double *b);
		/*!
		* model analysis
		*目的: 根据公式: D=-d(lnq)/dt，计算D的值
		*n: 数据点个数，n>=3;
		*t: 时间，为有n元素的一维数组
		*q: （与时间t对应的）产量数据，为有n元素的一维数组
		*D: n个元素的一维素组，用于返回计算结果
		*要求: t须按由小到大的顺序排列
		**/
		void DeclineD(int n, double *t, double *q, double *D);
		/*!
		//目的: 根据公式: b=d(1/D)/dt，计算b的值
		//n: 数据点个数，n>=3;
		//t: 时间，为有n元素的一维数组
		//D: （与时间t对应的）D，为有n元素的一维数组
		//b: n个元素的一维素组，用于返回计算结果
		//要求: t须按由小到大的顺序排列
		**/
		void DeclineB(int n, double *t, double *D, double *b);

		/*!
		*
		**/
		void ArpsFitting(int Nxy, double *x, double *y, double Q0, double a0, double &n);
		double ArpsProduction(double t, double Q0, double a0, double n);
		double ArpsReserve(double t0, double t1, double Q0, double a0, double n);
		
		/*!
		*______数值积分______
		*目的: 计算被积函数为IFun在区间【a,b】内的积分值, 且被积函数IFun除自变量外，没有其它参数需要传入
		*适用于: 被积函数用解析式描述的情况
		*a,b: 积分的上、下限, a<b;
		*IFun:指向被积函数值计算的程序段指针;
		*IFunPs: 一维数组，传递IFun中所涉及的参数值;
		*IPs: 一维数组IFunPs的元素个数;
		*S: 积分计算结果
		*n: 进行数值积分计算时区间【a,b】的等分个数，n>=1（缺省值为50）, 一般来说，n越大，计算精度越高
		*注: 本段程序采用复合辛普生公式进行数值积分的计算
		**/
		double MakeNumericalIntegration(int n, double *x, double *f);
		double MakeNumericalIntegration(double a, double b, double (*IFun)(double x), int n);

		/*!
		* 求取Doung模型的所有4个参数: a、m、q0、q8
		* n: 数据点个数，n>2;
		* t: 时间，为有m元素的一维数组
		* q: （与时间t对应的）产量，为有n元素的一维数组
		* Q: （与时间t对应的）累积产量，为有n元素的一维数组
		**/
		void DoungFitting(int n, double *t, double *q, double *Q, double &aa, double &m, double &q0, double &q8);
		double DoungProduction(double t, double a, double m, double q0, double q8);
		double DoungReserve(double t0, double t1, double a, double m, double q0);

		/*!
		* 给定观测参数，计算PLE模型的4个参数
		* m: 数据点个数，m>2;
		* t: 时间，为有m元素的一维数组
		* q: （与时间t对应的）产量数据，为有m元素的一维数组
		* D: （与时间t对应的）递减率数据，为有m元素的一维数组
		* n、D1、D8、qi: 为所求的未知参数
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
		//m: 实测数据个数
		//t: 时间数据, t>0，m个元素的一维数组
		//G: (与时间对应的)累积产量数据, m个元素的一维数组
		//返回值：三个参数: K、a、n
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