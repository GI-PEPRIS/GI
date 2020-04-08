#ifndef __ANYMATH_WENGLIFE_CYCLE_H__
#define __ANYMATH_WENGLIFE_CYCLE_H__

#include "curvefittingusingleastsquaremethodcommonlib.h"

// refer to stl
#include "any/base/anystl.h"

double PartialDerivativeA_WengLifeCycleModel(double T, double *Pars, double *OParam);    //������������ģ�ͺ����Դ�������A��ƫ������ֵ
double PartialDerivativeC_WengLifeCycleModel(double T, double *Pars, double *OParam);    //������������ģ�ͺ����Դ�������C��ƫ������ֵ
double PartialDerivativen_WengLifeCycleModel(double T, double *Pars, double *OParam);    //������������ģ�ͺ����Դ�������n��ƫ������ֵ
double WengLifeCycleModelFun(double T, double *Pars, int nPars, double *OParam);    //������������ģ�ͺ�����ֵ
void CurveFittingUsingLeastSquareMethod_WengLifeCycleModel(double *x, double *y, int Nxy,
                                       double *Vector_Param, int Nparms,
                                       double *OParam,
                                       double (*CurveFunction)(double, double *, int, double *),
                                       PartialDerivativeDeFunction *PDF,
                                       double err);
int WengLifeCycleModel_ParameterEstimation(int Nty, double *T, double *y, double &A, double &C, double &n, double T0=0);

#endif