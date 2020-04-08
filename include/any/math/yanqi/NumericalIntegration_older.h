#include <math.h>

typedef double (*Integrand)(double x, double *P, int n);  //被积函数IFun除自变量外，还有其它参数需要传入
typedef double (*Integrand_NoPars)(double x);  //被积函数IFun除自变量外，没有其它参数需要传入
//被积函数接口定义
//x: 自变量的值
//P:是一维数组，用于传入被积函数中的(除自变量)其它参数值, 若没有则传入NULL
//n是其它参数个数


double NumericalIntegration(int n, double *x, double *f);
double NumericalIntegration(double a, double b, double (*IFun)(double x, double *P, int n),
                            double *IFunPs, int IPs, int n/*=50*/);
double NumericalIntegration(double a, double b, double (*IFun)(double x), int n/*=50*/);


void NumericalDifferential(int n, double *x, double *f, double *D);
double NumericalDifferential_5D_LagrangeDiff(int n, double *x, int n0, int k, double X);