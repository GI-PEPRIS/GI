#include "FastFourierTransform.h"
#include "ExperimentalVariogram_BaiscHead.h"

void Cal_3DExperimentalVariogram_Anisotropic_Multithreading(int StartGridX, int StartGridY, int StartGridZ,
                                                            int EndGridX, int EndGridY, int EndGridZ,
                                                            double *x, double *y, double *z, double *v, int n,
                                                            double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure ***C);
void Cal_3DExperimentalVariogram_Isotropic_Multithreading(int StartGridX, int StartGridY, int StartGridZ,
                                                          int EndGridX, int EndGridY, int EndGridZ,
                                                          double *x, double *y, double *z, double *v, int n,
                                                          double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure ***C);


int ExperimentalVariogram_3DFor1Direction_Anisotropic(double *x, double *y, double *z, double *v, int n, double *dirP, double H, double HTolerate, double cosDirTolerate, double &EVV);
int ExperimentalVariogram_3DFor1Startpoint_Anisotropic(double *x, double *y, double *z, double *v, int n, double *dirP, double *P0, int cJ, double H, double HTolerate, double cosDirTolerate, double &DotPairValue);
bool ExperimentalVariogram_3DIsDotWithinErrorRange_Anisotropic(double *P, double *P0, double *P1, double H, double HTolerate, double cosDirTolerate);
void Cal_DirectP_3D(double *P0, double *dirP, double h, double *P);
void Cal_3DExperimentalVariogram_Isotropic(double *x, double *y, double *z, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure ***C);
void Cal_3DExperimentalVariogram_Anisotropic(double *x, double *y, double *z, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure ***C);
int ExperimentalVariogram_3DFor1Lag_Isotropic(double *x, double *y, double *z, double *v, int n, double H, double HTolerate, double &EVV);
int ExperimentalVariogram_3DFor1Startpoint_Isotropic(double *x, double *y, double *z, double *v, int n, double *P0, double P0V, double H, double HTolerate, double &DotPairValue);
bool ExperimentalVariogram_3DIsDotWithinErrorRange_Isotropic(double *P, double *P0, double H, double HTolerate);
void ChangeExperimentalVariogram3DGridToXY(double *H0, int *nH, ExperimentalVariogram_Structure ***C, double *X, double *Y);

void ExperimentalVariogram_3DCovarianceGrid_InitialPars(double *x, double *y, double *z, int n, int *nH, double *H0, double &HTolerate);
void ExperimentalVariogram_3DCovarianceGrid_InitialPars(double *x, double *y, double *z, int n, int *nH, double *H0);


