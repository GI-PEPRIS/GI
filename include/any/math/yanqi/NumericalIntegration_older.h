#include <math.h>

typedef double (*Integrand)(double x, double *P, int n);  //��������IFun���Ա����⣬��������������Ҫ����
typedef double (*Integrand_NoPars)(double x);  //��������IFun���Ա����⣬û������������Ҫ����
//���������ӿڶ���
//x: �Ա�����ֵ
//P:��һά���飬���ڴ��뱻�������е�(���Ա���)��������ֵ, ��û������NULL
//n��������������


double NumericalIntegration(int n, double *x, double *f);
double NumericalIntegration(double a, double b, double (*IFun)(double x, double *P, int n),
                            double *IFunPs, int IPs, int n/*=50*/);
double NumericalIntegration(double a, double b, double (*IFun)(double x), int n/*=50*/);


void NumericalDifferential(int n, double *x, double *f, double *D);
double NumericalDifferential_5D_LagrangeDiff(int n, double *x, int n0, int k, double X);