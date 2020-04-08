#include "any/math/yanqi/GA.h"

double HI_TmaxModel_ObjectFunction_GA(int nP, double *P, vector<GA_UserData> UserData);
double HI_TmaxModel_ObjectFunction(int n, double *Tmax, double *HI, double HI0, double C, double Sita, double Beita, double T0, double T1);
double HI_TmaxModel_FunctionValue(double T, double HI0, double C, double Sita, double Beita);
double HI_TmaxModel_Fitness(int nP, double *P, double ObjFunValue);
bool HI_TmaxModel_ParametersIsAvailable(int nx, double *x);
int HI_TmaxModel_CalPrecisionValue(int nx, double *x, double ObjFunValue, double Fitness, double &PrecisionValue);
void HI_TmaxModel_GA(int n, double *Tmax, double *HI, double HI0, double C, double T0, double T1, double &Sita, double &Beita);
