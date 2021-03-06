#include "ExperimentalVariogram_BaiscHead.h"
bool Cal_3DSphereVariogramModelUsingPolynomialRegressionWithWeightfittingMethod(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double &a, double &C0, double &C);
bool Cal_3DSphereVariogramModelUsingDirectfittingMethod(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double &a, double &C0, double &C);
void Interpolation_3DTheoryVariogram(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double a, double C0, double C, double *dirP,
                                     bool isAnisotropic, bool iMode);
