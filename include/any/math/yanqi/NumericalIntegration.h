#include <math.h>

//被积函数接口定义
typedef double(*IntegrationFuncWithManyP)(double x, double *P, int nP); //被积函数IFun除自变量外，还有其它参数需要传入
typedef double(*IntegrationFuncWith1P)(double x);  //被积函数IFun除自变量外，没有其它参数需要传入
//x: 自变量的值
//P:是一维数组，用于传入被积函数中的(除自变量)其它参数值
//n是其它参数个数

double NumericalIntegration(int n, double *x, double *f);
double NumericalIntegration(double a, double b, IntegrationFuncWithManyP IFun,
                            double *IFunPs, int IPs, int n);
double NumericalIntegration(double a, double b, IntegrationFuncWith1P IFun, int n);


void NumericalDifferential(int n, double *x, double *f, double *D);
double NumericalDifferential_5D_LagrangeDiff(int n, double *x, int n0, int k, double X);
