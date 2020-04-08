#include "CommonUseParameterEstimation_UseP10P90.h"
void GamaParameterEstimation_UseP10P90(double Q10, double Q90, double &Gama, double &Lmda);
double GamaMode_G(double x, double Gama, double Lmda, double **L, int nL);
double GamaMode_Fs(double x, double Gama, double Lmda, double **L, int nL);
double GamaMode_Fm(double Gama, double **L, int nL);
double GamaMode_dFsGama(double x, double Gama, double Lmda, double **L, int nL);
double GamaMode_dFsLmda(double x, double Gama, double Lmda, double **L, int nL);
double GamaMode_dFmGama(double x, double Gama, double Lmda, double **L, int nL);

void Cal_GamaF(double Gama, double Lmda, double Q10, double Q90, double *F, double **L, int nL);
void Cal_GamaDF(double Gama, double Lmda, double q10, double q90, double **L, int nL, double dfv[2][2]);
double GamaMode_dGGama(double x, double Gama, double Lmda, double **L, int nL);
double GamaMode_dGLmda(double x, double Gama, double Lmda, double **L, int nL);
void GetInterpolationPars(char name, double **V);
int GamaRevisionX(double Q10, double Q90,double *X, double *X1, double *F, double *tt, double **L, int nL);

int Gama_StartingValue_YTF(int nP, double *P, double *P0, double Q10, double Q90, int N, double **L, int nL);


