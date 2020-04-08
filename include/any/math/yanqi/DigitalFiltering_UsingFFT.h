#include <math.h>
#include <vector>
#include "FastFourierTransform.h"

void DigitalFiltering_UsingFFT_FilteringHighFrenquency(int MinFrenquency, int n0, double *x, std::vector<complex<double> > &R);
void DigitalFiltering_UsingFFT_FilteringLowFrenquency(int MaxFrenquency, int n0, double *x,  std::vector<complex<double> > &R);

