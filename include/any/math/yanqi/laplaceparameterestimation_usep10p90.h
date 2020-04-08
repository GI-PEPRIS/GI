#include "CommonUseParameterEstimation_UseP10P90.h"
void LaplaceParameterEstimation_UseP10P90(double Q10, double Q90, double &Mui, double &Lmda);
double LaplaceMode_CDF(double x, double Mui, double Lmda);
double LaplaceMode_PartialDerivative_Mui(double x, double Mui, double Lmda);
double LaplaceMode_PartialDerivative_Lmda(double x, double Mui, double Lmda);
int LaplaceRevisionX(double Q10, double Q90, double *X, double *X1, double *F, double *tt);
void Cal_LaplaceDF(double Mui, double Lmda, double q10, double q90, double dfv[2][2]);
void LaplaceMode_F(double Mui, double Lmda, double Q10, double Q90, double *F);
 