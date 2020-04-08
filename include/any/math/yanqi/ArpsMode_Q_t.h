#include <math.h>
void ArpsModeCurveFitting_a_t(int Nxy, double *x, double *y, double a0, double &n); //对外接口
double ArpsModeCurveFitting_Q_t_1(int Nxy, double *x, double *y, double Q0, double a0);   //内部调用
double ArpsMode_Q_t_ObjectFunctionValue(int Nxy, double *x, double *y, double Q0, double a0, double n);
double ArpsMode_Q_t_ObjectFunction_nPartialDerivativeValue(int Nxy, double *x, double *y, double Q0, double a0, double n);
double ArpsMode_valueQ_t_nPartialDerivative_2(double t, double Q0, double a0, double n);
double ArpsMode_valueQ_t_nPartialDerivative(double t, double Q0, double a0, double n);
double ArpsMode_valueQ_t(double t, double Q0, double a0, double n);
double ArpsMode_valueNp_t(double t, double Q0, double a0, double n);
