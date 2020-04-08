#include "ExperimentalVariogram_BaiscHead.h"
#include "Cal_2DTheoryCovariance.h"

void Cal_2DExperimentalVariogram_Anisotropic_Multithreading(int StartGridX, int StartGridY,
                                                            int EndGridX, int EndGridY,
                                                            double *x, double *y, double *v, int n,
                                                            double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure **C);
void Cal_2DExperimentalVariogram_Isotropic_Multithreading(int StartGridX, int StartGridY,
                                                          int EndGridX, int EndGridY,
                                                          double *x, double *y, double *v, int n,
                                                          double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure **C);


void Cal_2DExperimentalVariogram_Anisotropic(double *x, double *y, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure **C);
int ExperimentalVariogram_2DFor1Direction_Anisotropic(double *x, double *y, double *v, int n, double *dirP, double H, double HTolerate, double cosDirTolerate, double &EVV);
int ExperimentalVariogram_2DFor1Startpoint_Anisotropic(double *x, double *y, double *v, int n,
                                         double *dirP, double *P0, double P0V, double H, double HTolerate, double cosDirTolerate, double &DotPairValue);
bool ExperimentalVariogram_2DIsDotWithinErrorRange_Anisotropic(double *P, double *P0, double *P1, double H, double HTolerate, double cosDirTolerate);
//void Cal_DirectP_2D(double *P0, double *dirP, double h, double *P);
void Cal_2DExperimentalVariogram_Isotropic(double *x, double *y, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure **C);
int ExperimentalVariogram_2DFor1Lag_Isotropic(double *x, double *y, double *v, int n, double H, double HTolerate, double &EVV);
int ExperimentalVariogram_2DFor1Startpoint_Isotropic(double *x, double *y, double *v, int n,
                                         double *P0, double P0V, double H, double HTolerate, double &DotPairValue);
bool ExperimentalVariogram_2DIsDotWithinErrorRange_Isotropic(double *P, double *P0, double H, double HTolerate);
void ChangeExperimentalVariogram2DGridToXY(double *H0, int *nH, ExperimentalVariogram_Structure **C, double *X, double *Y);
