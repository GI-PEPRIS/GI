#ifndef __ANYMATH_YANQI_MATRIX_H__
#define __ANYMATH_YANQI_MATRIX_H__

#include <math.h>

typedef double (*PartialDerivativeDeFunction)(double, double *, double *);

double MeanValue(int m, double *x);

int MatrixInversionGS(double **rhs, double **m, int stRank);
void MatrixTransform(double **rhs, int nRow, int nCol,double **m);
void MatrixProduct(double **rhs, double **m, int nRow, int nR, int nCol, double **R);
void MatrixProductVector(double **rhs, double *m, int nRow, int nCol, double *R);  //矩阵左乘向量
void MatrixProductVector(double *m, double **rhs, int nRow, int nCol, double *R);  //向量左乘矩阵

int CurveFittingUsingLeastSquareMethod(double *x, double *y, int Nxy,
                                       double *Vector_Param, int Nparms,
                                       double *Oparam,
                                       double (*CurveFunction)(double, double *, int, double *),
                                       PartialDerivativeDeFunction *PDF,
                                       double err);

double Cal_f4_1(double *Vector_F, double *x, double *y, int Nxy, double *Vector_Param, int nParamsdouble, double *Oparam, double (*CurveFunction)(double, double *, int, double *));
int Cal_f4_4(double **DF, int N, int M, double **DFT, double *F, double U, double *Pk);
void Cal_Matrix_DF(double **Matrix_DF, double *x, int Nxy, double *Vector_Param, int Nparms, double *Oparam, PartialDerivativeDeFunction *PDF);

int nDegreePolynomialFitting(double *x, double *y, int m, int n, double *a, double *OParam);  //一元N-1次曲线拟合（N≥2）
double ValueOfEquationWithOneUnknown(double x, double *a, int n, double *OParam);  //计算一元n-1次方程在x处的的函数值（n≥2）

bool Bi_TrendSurfaceAnalysis(double *x, double *y, double *z, int n, double *P); //二元二次回归(趋势面）分析
bool Tri_TrendSurfaceAnalysis(double *x, double *y, double *z, int n, double *P);//二元三次回归(趋势面）分析
bool Equation_2element_nIndex(double *x, double *y, double *z, int m, int n, double *a);  //二元n次曲线拟合


int CurveFittingUsingLeastSquareMethod(double *x, double *y, int Nxy,
                                       double *Vector_Param, int Nparms,
                                       double *Oparam,
                                       double (*CurveFunction)(double, double *, int, double *),
                                       PartialDerivativeDeFunction *PDF,
                                       bool (*CurveFunctionCheck)(double, double *, int, double *),
                                       double err);
#endif

