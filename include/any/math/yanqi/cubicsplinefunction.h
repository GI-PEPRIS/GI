#ifndef __ANYMATH_CUBIC_SPLINE_H__
#define __ANYMATH_CUBIC_SPLINE_H__

// refer to stl
#include "any/base/anystl.h"

void CubicSplineInterpolationCoefficient(int xn, double *x, double *y, double *M, double dx0, double dxn);
double CubicSplineInterpolation(int nx, double *x, double *y, double *M, double cx);
double AntiCubicSplineInterpolation(int nx, double *x, double *y, double *M, double cy, int YD);
void Equations_setUseChasingMethod(int n, double *lmd, double *G, double *M);
int SolveCubicEquationWithOneUnknown(double a, double b, double c, double *roots);
double akspl(int n,double x[],double y[],double t);
#endif