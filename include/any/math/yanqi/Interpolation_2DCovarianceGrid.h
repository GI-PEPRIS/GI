#include "ExperimentalVariogram_BaiscHead.h"

void Interpolation_2DCovarianceGrid_Anisotropic(ExperimentalVariogram_Structure **C, int *nH, double *H0, double *dirP, double IR, double IA);
void Interpolation_2DCovarianceGrid_Anisotropic_For1GridDot(int *IC, ExperimentalVariogram_Structure **C, int *nH,
                    double *H0, double *dirP, double IR, double IA);
bool Interpolation_2DIsDotWithinErrorRange_Anisotropic(double *P, double *P0, double *dirP, double H, double cosDir);


void Interpolation_2DCovarianceGrid_Isotropic(ExperimentalVariogram_Structure **C, int *nH, double *H0, double IR);
void Interpolation_2DCovarianceGrid_Isotropic_For1GridDot(int *IC, ExperimentalVariogram_Structure **C, int *nH, double *H0, double IR);
bool Interpolation_2DIsDotWithinErrorRange_Isotropic(double *P, double *P0, double H);


void Interpolation_2DCovarianceGrid_Addition(ExperimentalVariogram_Structure **C, int *nH, double *H0, double IR0);
                    

