//#include <complex>
//#include <valarray>
//#include <math.h>
#include "FastFourierTransform.h"
#include "ConditionalSimulationIn3D_Common.h"

int ConditionalSimulationIn3D(double *Grid0,
                                      double *x, double *y, double *z, double *v, int n,
                                      double *H0, int *nH, double ***C,
                                      complex<double> ***S,
                                      double ObjValue0, unsigned long int MaxIterationNum,
                                      int OpMode);

int DataFusion_ConditionalSimulationIn3D(double *Grid0,
                              double *x, double *y, double *z, double *v, int n,
                              double *H0, int *nH, double ***C,  double ***F,
                              complex<double> ***S,
                              double ObjValue0, unsigned long int MaxIterationNum);

void DataFusion_ConditionalSimulationIn3D(double *Grid0,
                              double *H0, int *nH, double ***C, double ***F,
                              complex<double> ***S);

void ConditionalSimulationIn3D_Step2_a(int *nH, complex<double> ***S);
double ConditionalSimulationIn3D_Step3(ConditionDataParas *ConD, int n, complex<double> ***S);
void ConditionalSimulationIn3D_Step4(ConditionDataParas *ConD, int n, complex<double> ***S);
void ConditionalSimulationIn3D_Step5(int *nH, double ***S, complex<double> ***IS);

