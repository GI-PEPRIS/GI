#ifndef __ANYMATH_YANQI_MATRIX_H__
#define __ANYMATH_YANQI_MATRIX_H__

#include <math.h>

typedef double (*PartialDerivativeDeFunction)(double, double *, double *);

double MeanValue(int m, double *x);

int MatrixInversionGS(double **rhs, double **m, int stRank);
void MatrixTransform(double **rhs, int nRow, int nCol,double **m);
void MatrixProduct(double **rhs, double **m, int nRow, int nR, int nCol, double **R);
void MatrixProductVector(double **rhs, double *m, int nRow, int nCol, double *R);  //�����������
void MatrixProductVector(double *m, double **rhs, int nRow, int nCol, double *R);  //������˾���

int CurveFittingUsingLeastSquareMethod(double *x, double *y, int Nxy,
                                       double *Vector_Param, int Nparms,
                                       double *Oparam,
                                       double (*CurveFunction)(double, double *, int, double *),
                                       PartialDerivativeDeFunction *PDF,
                                       double err);

double Cal_f4_1(double *Vector_F, double *x, double *y, int Nxy, double *Vector_Param, int nParamsdouble, double *Oparam, double (*CurveFunction)(double, double *, int, double *));
int Cal_f4_4(double **DF, int N, int M, double **DFT, double *F, double U, double *Pk);
void Cal_Matrix_DF(double **Matrix_DF, double *x, int Nxy, double *Vector_Param, int Nparms, double *Oparam, PartialDerivativeDeFunction *PDF);

int nDegreePolynomialFitting(double *x, double *y, int m, int n, double *a, double *OParam);  //һԪN-1��������ϣ�N��2��
double ValueOfEquationWithOneUnknown(double x, double *a, int n, double *OParam);  //����һԪn-1�η�����x���ĵĺ���ֵ��n��2��

bool Bi_TrendSurfaceAnalysis(double *x, double *y, double *z, int n, double *P); //��Ԫ���λع�(�����棩����
bool Tri_TrendSurfaceAnalysis(double *x, double *y, double *z, int n, double *P);//��Ԫ���λع�(�����棩����
bool Equation_2element_nIndex(double *x, double *y, double *z, int m, int n, double *a);  //��Ԫn���������


int CurveFittingUsingLeastSquareMethod(double *x, double *y, int Nxy,
                                       double *Vector_Param, int Nparms,
                                       double *Oparam,
                                       double (*CurveFunction)(double, double *, int, double *),
                                       PartialDerivativeDeFunction *PDF,
                                       bool (*CurveFunctionCheck)(double, double *, int, double *),
                                       double err);
#endif

