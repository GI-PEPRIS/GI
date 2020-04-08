#include <stdio.h>
#include <math.h>


double Cal_AppendixD_Theorem1_1(int R, int Rj, int Rj1, double X, double Xj, double Xj1,
                              double (*h)(double, int, double *),
                                 int nP, double *P);
double Cal_AppendixD_Theorem1_2(int R, int R1, double X, double X1,
                              double (*h)(double, int, double *),
                                 int nP, double *P);
double Cal_GamaFun(int m);
double Cal_H(double x, double (*h)(double, int, double *), int nP, double *P);
 