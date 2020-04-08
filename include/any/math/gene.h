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
//#define PUNISHFACTOR DBL_MAX  //�ͷ������ĳͷ�����
const double PUNISHFACTOR=9e16;

typedef void (*SubjectToFunction)(int m, int n, double **A, double *X, double *V);
//SubjectToFunction: ����������(������ʽ��˼���ʽ��ֵ)��ͨ�ýӿ�
//                   m: ���������
//                   n: �滮��������
//                   A: ����������ϵ������m�С�n��
//                   X: Ŀ�귽�̱�����������n��Ԫ��
//                   V: ��������������ʽ��˼���ʽ��ֵ����m��Ԫ��
typedef double (*ObjectFunction)(int n, double *C, double *X);
//OubjectFunction: Ŀ�꺯����ͨ�ýӿ�
//                 n: �滮��������
//                 C: Ŀ�귽��ϵ����������n��Ԫ��
//                 X: Ŀ�귽�̱�����������n��Ԫ��
//

typedef double (*FitnessFunction)(double OV, int nSV, double *SV,int m);
//FitnessFunction: ������Ӧ�Ⱥ�����ͨ�ýӿ�
//                 OV: Ŀ�귽��ֵ
//                 nSV: �������̸���
//                 SV: �������̲���ʽ��˼���ֵ��������nSV��Ԫ��
//
typedef bool (*GeneralConstraintFunction)(double *scales, int number);
//

//SubjectToFunction: ����������(������ʽ��˼���ʽ��ֵ)��ͨ�ýӿ�
void CalculateSubjectFunctionValue(int m, int n, double **A, double *X, double *V);
//OubjectFunction: Ŀ�꺯����ͨ�ýӿ�
double CalculateObjectFunctionValue(int n, double *C, double *X, int nOther, double *Others);
//FitnessFunction: ������Ӧ�Ⱥ�����ͨ�ýӿ�
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

		typedef class ParDescribeInfo   //�滮������Ϣ�����ṹ
		{
		public:
			//        double x;         //������ʮ����ֵ
			double Min,Max;   //����ֵ�ı仯��Χ
			int DecimalNum;   //������С��λ����DecimalNum��0
			int CodingLength; //�������������Ķ����Ʊ��볤�ȣ�CodingLength>0
		}ParDescribeInfo; //����������Ϣ

		typedef class  Populations_Class_GENOCOP   //��Ⱥ�ṹ
		{
		public:
			double *x;               //��Ⱥ������ʮ����ֵ
			double ObjFunValue;      //��Ⱥ�����Ŀ�꺯��ֵ
			double Fitness;          //��Ⱥ�������Ӧ��ֵ
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
		}Populations_Class_GENOCOP; //����������Ϣ


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

		//���������ʼ��Ⱥ������������� ��Ҫ�����������н�һ��ɸѡ
		void CreateRandomXValue(int n, double *X);
		//���������ʼ��Ⱥ������������� ��Ҫ�����������н�һ��ɸѡ
		bool CreateRandomXValueLowHigh(int n, double *X,double* pLow, double* pHigh);
		//���������ʼ��Ⱥ������������� ��Ҫ�����������н�һ��ɸѡ
		bool CreateRandomXValueLowHighEqual(int n, double *X,double* pLow, double* pHigh,double equalVal,double* equalCoef);
		//������ʼ��Ⱥ
		bool CreateInitialPopulations(int n0, int m0, double **a0, double *b0, double *c0,
			int &nxP0,  double*pLow,double* pHigh,Populations_Class_GENOCOP *Populations,
			int nOther, double *Others,
			void (*SubjectToFunction)(int , int , double **, double *, double *),
			double (*ObjectFunction)(int , double *, double *, int, double *),
			double (*FitnessFunction)(double, int, double *, double *,int),
			std::vector<double>& lastBestPopulationVec);


		////ʹ�����̶�ѡ��������Ⱥѡ��
		int Population_Select_RollGambling(int nxP0, double *P);

		//ÿ�ε���������ѡ��ʹ�ö������̶ĵķ���
		void Population_Select(int nx, int nP, Populations_Class_GENOCOP *Populations, int nPSelect, int *SelectNo);

		//�ڵ㷨���н���
		void Population_Crossor(int father1, int father2, double *Child1, double *Child2, int nx, Populations_Class_GENOCOP *Populations);
	
		//ѡ�񽻲�������򣬵���������������
		void Population_SelectAndCrossor(int nPSelect, int nx, int nOld, Populations_Class_GENOCOP **POld1, int nNew, Populations_Class_GENOCOP **PNew1,double (*ObjectFunction)(int , double *, double *, int, double *));

			//�Ŵ��㷨�ڵ㷨
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
		* ����ⲿ�ӿڳ���
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
		*   ɨ�����㷨����͹��
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
	
		 int m_nxP0;//�趨�ĳ�ʼ��Ⱥ����
		 int m_iterationtimes; //��������
		 int m_simutimes1;//�Ŵ��㷨����1
		 int m_simutimes2;//�Ŵ��㷨����2
		 int m_n;//�滮������
		 int m_n2;//�滮������
		 int m_m; //Լ������������
		 // a b c m_Others�Ż�Ŀ�� �������� x����ȡֵ
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
