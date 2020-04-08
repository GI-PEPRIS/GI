#include "Cal_3DExperimentalVariogram.h"
#include "Cal_Spectrum.h"
#include "ConditionalSimulationIn3D_Common.h"


int ConditionalSpectralSimulationIn3D(CoordiateParaments Cops,
                                      double ***ConD,
                                      double *H0, int *nH, ExperimentalVariogram_Structure ***C,
                                      complex<double> ***S,
                                      double ObjValue0, unsigned long int MaxIterationNum);

int ConditionalSpectralSimulationIn3D(double *Grid0,
                                      double *x, double *y, double *z, double *v, int n,
                                      double *H0, int *nH, ExperimentalVariogram_Structure ***C,
                                      complex<double> ***S,
                                      double ObjValue0, unsigned long int MaxIterationNum);

void ConditionalSpectralSimulationIn3D_Step2_a(int *nH, double ***A0, complex<double> ***S);
double ConditionalSpectralSimulationIn3D_Step3(double ***ConD, complex<double> ***S, int *nH);
double ConditionalSpectralSimulationIn3D_Step3(ConditionDataParas *ConD, int n, complex<double> ***S);
void ConditionalSpectralSimulationIn3D_Step4(double ***ConD, complex<double> ***S, int *nH);
void ConditionalSpectralSimulationIn3D_Step4(ConditionDataParas *ConD, int n, complex<double> ***S);
void ConditionalSpectralSimulationIn3D_Step5(int *nH, double ***S, complex<double> ***IS);
void ConditionalSpectralSimulationIn3D_CorrectSpectrum(int *nH, complex<double> ***S);
void ConditionalSpectralSimulationIn3D_ExperimentalCovariance(double *x, double *y, double *z, double *v, int n,
                                                              double *dirP, double *H0, int *nH,
                                                              double HTolerate, double dirTolerate, ExperimentalVariogram_Structure ***C);

void GetCorrdinateChangePars(double *x, double *y, double *z, int n, double *H0, int *nH, CoordiateParaments &Cops);
void ChangeCorrdinate_Grid2Real(double ix, double iy, double iz, CoordiateParaments Cops, double &x, double &y, double &z);
void ChangeCorrdinate_Real2Grid(double x, double y, double z, CoordiateParaments Cops, double &ix, double &iy, double &iz);

void Cal_3DExperimentalCovariance(ExperimentalVariogram_Structure ***C, int *nH);
void Cal_3DExperimentalCovariance2Variogram(ExperimentalVariogram_Structure ***C, int *nH, double Covariance);
