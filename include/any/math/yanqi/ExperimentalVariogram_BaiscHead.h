#ifndef __ExperimentalVariogram_Structure_H__
#define __ExperimentalVariogram_Structure_H__

#include <math.h>

enum {
VM_SPHERICAL=0,
VM_EXPONETIAL,
VM_GUASSIAN,
VM_LINEAR
};


struct ExperimentalVariogram_Structure{
        int nDotPairs;
        double ExperimentalVariogramValue;
        ExperimentalVariogram_Structure(){
            nDotPairs = 0;
            ExperimentalVariogramValue = 0;
        }
};
#define PAI 3.1415926
#endif

double Cal_Variance(double *v, int n);
void Cal_DirectP_3D(double *P0, double *dirP, double h, double *P);
void Cal_DirectP_2D(double *P0, double *dirP, double h, double *P);
double Cal_SphereVariogramModel(double h, double a, double C0, double C);

double GetModelValue(double h, double sill, double range, double nugget, int ModelType);

