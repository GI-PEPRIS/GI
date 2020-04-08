#include "CommonUseParameterEstimation_UseP10P90.h"
double Cal_RouFunc_9(double x, double a, double b, int m=100);
double Cal_RouFunc_da_10(double x, double a, double b, int m=100);
double Cal_RouFunc_db_11(double x, double a, double b, int m=100);
double Cal_BetaMode_dGamaFun(double a, double **L, int nL);
double Cal_BetaMode_GamaFun(double a, double **L, int nL);

void BetaParameterEstimation_Stifen(double Q10, double Q90, double &a, double &b, double **L, int nL);
void Cal_BetaF(double a, double b, double Q10, double Q90, double *F, double **L, int nL);
void Cal_BetaDF(double a, double b, double q10, double q90, double **L, int nL, double dfv[2][2]);
int BetaRevisionX_Beta(double Q10, double Q90,double *X, double *X1, double *F, double *tt, double **L, int nL);

double BetaMode_CDF_da(double x, double a, double b, double **L, int nL);
double BetaMode_CDF_db(double x, double a, double b, double **L, int nL);
double BetaMode_CDF(double x, double a, double b, double **L, int nL);

int BetaMode_StartingValue_YTF(int nP, double *P, double *P0, double Q10, double Q90, int N, double **L, int nL);
void BetaParameterEstimation_UseP10P90(double Q10, double Q90, double &a, double &b);
void RearryPoint(double *A, double *B, double *FAB);
