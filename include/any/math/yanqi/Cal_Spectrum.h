#include "FastFourierTransform.h"
#include "ExperimentalVariogram_BaiscHead.h"

void CovarianceToSpectrum_3D(int *nH, ExperimentalVariogram_Structure ***C, complex<double> ***S);
void SpectrumToCovariance_3D(int *nH, complex<double> ***S, ExperimentalVariogram_Structure ***C);
void CovarianceToSpectrum_2D(int *nH, ExperimentalVariogram_Structure **C, complex<double> **S);
void SpectrumToCovariance_2D(int *nH, complex<double> **S, ExperimentalVariogram_Structure **C);

