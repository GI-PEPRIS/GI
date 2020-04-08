#include <math.h>

//���������ӿڶ���
typedef double(*IntegrationFuncWithManyP)(double x, double *P, int nP); //��������IFun���Ա����⣬��������������Ҫ����
typedef double(*IntegrationFuncWith1P)(double x);  //��������IFun���Ա����⣬û������������Ҫ����
//x: �Ա�����ֵ
//P:��һά���飬���ڴ��뱻�������е�(���Ա���)��������ֵ
//n��������������

double NumericalIntegration(int n, double *x, double *f);
double NumericalIntegration(double a, double b, IntegrationFuncWithManyP IFun,
                            double *IFunPs, int IPs, int n);
double NumericalIntegration(double a, double b, IntegrationFuncWith1P IFun, int n);


void NumericalDifferential(int n, double *x, double *f, double *D);
double NumericalDifferential_5D_LagrangeDiff(int n, double *x, int n0, int k, double X);
