#include "CommonUseParameterEstimation_UseP10P90.h"
bool ParetoParameterEstimation_UseP10P90(double qmin, double qmax, double Q10, double Q90, double &Gama, double &Lmda);
int RevisionX_Pareto(double qmin, double qmax, double Q10, double Q90,double *X, double *X1, double *F, double *tt);
bool Cal_ParetoF(double qmax, double q0, double Gamam, double Lmda, double Q10, double Q90, double *F);
bool Pareto_CDF(double qmax, double q0, double Gamam, double Lmda, double q, double &F);
void Cal_ParetoDF(double qmax, double q0, double Gama, double Lmda, double q10, double q90, double dfv[2][2]);
double PartialDerivative_ParetodGama(double qmax, double q0, double Gama, double Lmda, double q);
double PartialDerivative_ParetodLmda(double qmax, double q0, double Gama, double Lmda, double q);

