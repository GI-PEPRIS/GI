#ifndef __ANYMATH_GENETIC_H__
#define __ANYMATH_GENETIC_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>
#include "boost\function.hpp";
using namespace std;
// refer to functor
#include "any/base/anymediator.h"
using namespace AnyBase;
#include "anymath.h"
#include "any/base/anymediator.h"

#define RandCoef2053 2053
#define RandCoef13849 13849
#define MODUL65536 65536
//#define PUNISHFACTOR DBL_MAX  //惩罚函数的惩罚因子
const double PUNISHFACTOR=9e16;

typedef void (*SubjectToFunction)(int m, int n, double **A, double *X, double *V);
//SubjectToFunction: 条件方程组(各不等式左端计算式的值)的通用接口
//                   m: 方程组个数
//                   n: 规划变量个数
//                   A: 条件方程组系数矩阵，m行、n列
//                   X: 目标方程变量向量，有n个元素
//                   V: 计算结果：各不等式左端计算式的值，有m个元素
typedef double (*ObjectFunction)(int n, double *C, double *X);
//OubjectFunction: 目标函数的通用接口
//                 n: 规划变量个数
//                 C: 目标方程系数向量，有n个元素
//                 X: 目标方程变量向量，有n个元素
//

typedef double (*FitnessFunction)(double OV, int nSV, double *SV,int m);
//FitnessFunction: 计算适应度函数的通用接口
//                 OV: 目标方程值
//                 nSV: 条件方程个数
//                 SV: 条件方程不等式左端计算值向量，有nSV个元素
//
typedef bool (*GeneralConstraintFunction)(double *scales, int number);
//

//SubjectToFunction: 条件方程组(各不等式左端计算式的值)的通用接口
void CalculateSubjectFunctionValue(int m, int n, double **A, double *X, double *V);
//OubjectFunction: 目标函数的通用接口
double CalculateObjectFunctionValue(int n, double *C, double *X, int nOther, double *Others);
//FitnessFunction: 计算适应度函数的通用接口
double CalculateFitness(double OV, int nSV, double *SV, double *b,int m);

namespace AnyMath
{
	class ANYMATH_CLASS GENE
	{
	public:
		//
		struct GENEResult
		{
			int m_idx;

			std::vector<int> m_resultIndex;
			std::vector<double> m_resultValue;
			double m_objValue;
			double m_NPV;
			GENEResult():m_objValue(0),m_NPV(0), m_idx(0)
			{}

			const GENEResult &operator=(const GENEResult &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_NPV=other.m_NPV;
				m_objValue=other.m_objValue;
				m_resultValue=other.m_resultValue;
				m_resultIndex=other.m_resultIndex;
				m_idx = other.m_idx;

				return *this;
			}
			GENEResult(const GENEResult &other)
			{
				*this=other;
			}
		}; 

		typedef class ParDescribeInfo   //规划变量信息描述结构
		{
		public:
			//        double x;         //变量的十进制值
			double Min,Max;   //变量值的变化范围
			int DecimalNum;   //保留的小数位数，DecimalNum≥0
			int CodingLength; //（单个）变量的二进制编码长度，CodingLength>0
		}ParDescribeInfo; //变量描述信息

		typedef class  Populations_Class_GENOCOP   //种群结构
		{
		public:
			double *x;               //种群变量的十进制值
			double ObjFunValue;      //种群个体的目标函数值
			double Fitness;          //种群个体的适应度值
			int dim;
			Populations_Class_GENOCOP(){
				x = NULL;
				dim=0;
			}
			~Populations_Class_GENOCOP(){
				if(x != NULL){
					delete [] x;
					x = NULL;
				}
			}
			void AllocatX(int n){
				x = new double[n];
				dim=n;
			}
			const Populations_Class_GENOCOP &operator=(const Populations_Class_GENOCOP &other)
			{
				if(this == &other)
				{
					return *this;
				}
				dim = other.dim;
				ObjFunValue = other.ObjFunValue;
				Fitness = other.Fitness;
				if(other.x!=NULL)
				{
					if(x!=NULL && dim!=0)
					{
						delete[] x;
					}
					x=NULL;
					AllocatX(dim);
					for(int i=0;i<dim;i++)
					{
						x[i]=other.x[i];
					}
				}
				return *this;
			}
			Populations_Class_GENOCOP(const Populations_Class_GENOCOP &other)
			{
				*this=other;
			}
			bool operator <(const Populations_Class_GENOCOP &other)const
			{
				return ObjFunValue<other.ObjFunValue;
			}
		}Populations_Class_GENOCOP; //变量描述信息


		GENE():m_a(0),m_b(0),m_c(0),m_x(0),m_c2(0),m_curc(0),m_fillPoint(false),m_npvPos(-1),m_x2(0),\
			m_nOther(0),m_EqualCol(-1),m_Others(0),m_Others2(0),m_plow(0),m_plow2(0),m_phigh(0),\
			m_phigh2(0),m_nxP0(2000),m_iterationtimes(500),m_numSubOptimal(5),m_a2(0), m_callback(0)
		{

		}
		~GENE()
		{
			ReleaseAll();
		}

		// general random tool
		double rand_01_One(void);
		int rand_ab_One(int a, int b);

		// binary search to accelerate RollGambling
		int binarysearch(double rd,double**p,int l,int r);

		//随机产生初始种群的随机数生成器 需要限制条件进行进一步筛选
		void CreateRandomXValue(int n, double *X);
		//随机产生初始种群的随机数生成器 需要限制条件进行进一步筛选
		bool CreateRandomXValueLowHigh(int n, double *X,double* pLow, double* pHigh);
		//随机产生初始种群的随机数生成器 需要限制条件进行进一步筛选
		bool CreateRandomXValueLowHighEqual(int n, double *X,double* pLow, double* pHigh,double equalVal,double* equalCoef);
		//产生初始种群
		bool CreateInitialPopulations(int n0, int m0, double **a0, double *b0, double *c0,
			int &nxP0,  double*pLow,double* pHigh,Populations_Class_GENOCOP *Populations,
			int nOther, double *Others,
			void (*SubjectToFunction)(int , int , double **, double *, double *),
			double (*ObjectFunction)(int , double *, double *, int, double *),
			double (*FitnessFunction)(double, int, double *, double *,int),
			std::vector<double>& lastBestPopulationVec);


		////使用轮盘赌选法进行种群选择
		int Population_Select_RollGambling(int nxP0, double *P);

		//每次迭代都进行选择，使用二分轮盘赌的方法
		void Population_Select(int nx, int nP, Populations_Class_GENOCOP *Populations, int nPSelect, int *SelectNo);

		//内点法进行交叉
		void Population_Crossor(int father1, int father2, double *Child1, double *Child2, int nx, Populations_Class_GENOCOP *Populations);
	
		//选择交叉的主程序，调用上面两个函数
		void Population_SelectAndCrossor(int nPSelect, int nx, int nOld, Populations_Class_GENOCOP **POld1, int nNew, Populations_Class_GENOCOP **PNew1,double (*ObjectFunction)(int , double *, double *, int, double *));

			//遗传算法内点法
		int Non_Linear_Programming_GENOCOP(int n0, int m0, double **a0, double *b0, double *c0, double *x0,
			int nxP0,
			int nOther, double *Others, double*pLow,double* pHigh,
			void (*SubjectToFunction)(int , int , double **, double *, double *),
			double (*ObjectFunction)(int , double *, double *, int, double *),
			double (*FitnessFunction)(double, int, double *, double *,int),
			std::vector<int> &resultIndex,std::vector<double> &resultVal,double &objVal,
			std::vector<double>& lastBestPopulationVec);


		/*!
		*
		**/
		//bool RegisterConstraintCallback(GeneralConstraintFunction *callback);
		bool RegisterConstraintCallback(boost::function<bool(double*,std::vector<int>,int)> callback);
		

		/*
		* 类的外部接口程序
		**/
		int FindPortforlio(CAnyFunctor &progress, double scanningStep = 0.001/*std::vector<int> &resultIndextmp, std::vector<double> &resultValuetmp*/);
		
		/*!
		*
		**/
		bool Normalization(std::vector<GENEResult> &points,double &minX,double &maxX,double &minY,double &maxY)
		{
			minY=minX=DBL_MAX;
			maxX=maxY=DBL_MIN;
			for(int i=0;i<points.size();i++)
			{
				if(points[i].m_objValue>maxX)
				{
					maxX=points[i].m_objValue;
				}
				if(points[i].m_objValue<minX)
				{
					minX=points[i].m_objValue;
				}
				if(points[i].m_NPV>maxY)
				{
					maxY=points[i].m_NPV;
				}
				if(points[i].m_NPV<minY)
				{
					minY=points[i].m_NPV;
				}
			}
			for(int i=0;i<points.size();i++)
			{
				points[i].m_NPV=(points[i].m_NPV-minY)/(maxY-minY);
				points[i].m_objValue=(points[i].m_objValue-minX)/(maxX-minX);
			}
			return true;
		}

		/*!
		*
		**/
		static double cross(const GENEResult &a, const GENEResult &b,const GENEResult &c)
		{
			GENEResult u,v;
			u.m_objValue=b.m_objValue-a.m_objValue;
			u.m_NPV=b.m_NPV-a.m_NPV;
			v.m_objValue=c.m_objValue-a.m_objValue;
			v.m_NPV=c.m_NPV-a.m_NPV;
			double crossVal=v.m_objValue*u.m_NPV-u.m_objValue*v.m_NPV;
			return crossVal;
		}
		/*!
		*
		**/
		static bool Getdistance(const GENEResult &a, const GENEResult &b)
		{
			return (b.m_objValue-a.m_objValue)*(b.m_objValue-a.m_objValue)+(b.m_NPV-a.m_NPV)*(b.m_NPV-a.m_NPV);
		}
		/*!
		*
		**/
		static bool CompareGraham(const GENEResult &a, const GENEResult &b)
		{
			double result=cross(GENE::p0,a,b);
			if(result<0)
			{
				return true;
			}
			else if(result>0)
			{
				return false;
			}
			else
			{
				return Getdistance(GENE::p0,a)-Getdistance(GENE::p0,b);
			}
			
		}

		/*!
		*   扫描线算法生成凸包
		**/
		bool Granham(std::vector<GENEResult>& points,std::vector<GENEResult>& closurePoints);


		/*!
		* scanningStep for selection of the outer ones
		**/
		bool CalculatePoints(std::vector<GENEResult>& points, double scanningStep);

		/*!
		*
		**/
		static bool CompareGENEResult(const GENEResult &a, const GENEResult &b)
		{
			return a.m_NPV<b.m_NPV;
		}
		/*!
		*
		**/
		void ReleaseAll(bool isAll = true)
		{
			if(m_a2)
			{
				for(int i=0;i<m_m;i++)
				{
					delete[] m_a2[i];
				}
				delete[] m_a2;
				m_a2=NULL;
			}
			if(m_c2)
			{
				delete [] m_c2;
				m_c2=NULL;
			}

			if(m_x2)
			{
				delete [] m_x2;
				m_x2=NULL;
			}
			if(m_Others2)
			{
				delete [] m_Others2;
				m_Others2=NULL;
			}

			/*if(m_curc)
			{
			delete [] m_curc;

			}*/
			if(m_phigh2)
			{
				delete [] m_phigh2;
				m_phigh2=NULL;
			}

			if(m_plow2)
			{
				delete [] m_plow2;
				m_plow2=NULL;
			}

			if(!isAll)
			{
				return;
			}

			if(m_a)
			{
				for (int i=0; i<m_m;  i++)
				{
					if(m_a[i])
					{
						delete [] m_a[i];
					}
				}
				delete [] m_a;
				m_a=NULL;
			}
			if(m_b)
			{
				delete [] m_b;
				m_b=NULL;
			}
			if(m_c)
			{
				delete [] m_c;
				m_c=NULL;
			}
			if(m_x)
			{
				delete [] m_x;
				m_x=NULL;
			}
			if(m_Others)
			{
				delete [] m_Others;
				m_Others=NULL;
			}
			if(m_phigh)
			{
				delete [] m_phigh;
				m_phigh=NULL;
			}
			if(m_plow)
			{
				delete [] m_plow;
				m_plow=NULL;
			}

			m_callback = 0;
		}
	public:
	
		 int m_nxP0;//设定的初始种群个数
		 int m_iterationtimes; //迭代次数
		 int m_simutimes1;//遗传算法次数1
		 int m_simutimes2;//遗传算法次数2
		 int m_n;//规划变量数
		 int m_n2;//规划变量数
		 int m_m; //约束条件方程数
		 // a b c m_Others优化目标 限制条件 x变量取值
		 double **m_a;
		 double **m_a2;
		 double *m_b;
		 double *m_c;
		 double *m_x; 
		 double *m_c2;
		 double *m_curc;
		 double *m_x2; 
		 int m_nOther;
		 double *m_Others;
		 double *m_Others2;
		 double* m_plow;
		 double* m_phigh;
		 double* m_plow2;
		 double* m_phigh2;
		 int m_EqualCol;

		 int m_numSubOptimal;
		 std::vector<int> m_resultIndex;
		 std::vector<double> m_resultValue;
		 double m_objValue;

		 /* std::vector<std::vector<int>> m_subResultIndexVec;
		 std::vector<std::vector<double>> m_subResultValueVec;*/
		 std::vector<GENEResult> m_GeneValueVec;
		 std::vector<GENEResult> m_allResult;
		 GENEResult m_grbest;
		 std::vector<GENEResult> m_OuterResult;
		 std::vector<std::vector<GENEResult>> m_AllInnerResult;
		 std::vector<std::vector<GENEResult>> m_InnerResult;
		 static GENEResult p0;
		 int m_npvPos;
		 bool m_fillPoint;

		 //normarlization factor
		 double m_scaleFactorMinX;
		 double m_scaleFactorMaxX;
		 double m_scaleFactorMinY;
		 double m_scaleFactorMaxY;
	public:
		 //
		 //GeneralConstraintFunction *m_callback;
		 boost::function<bool(double*,std::vector<int>,int)> m_callback;
		 std::vector<int> resultIndext1;
	};
}

#endif
