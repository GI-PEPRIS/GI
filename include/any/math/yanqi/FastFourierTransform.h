#include <complex>
#include <vector>
#include <math.h>
using namespace std;


bool FastFourierTransform_1D(std::vector<complex<double> > &p, std::vector<complex<double> > &f, int ct);
void FastFourierTransform_2D(double **u, int *n, complex<double> **U);
void FastInverseFourierTransform_2D(complex<double> **u, int *n, complex<double> **U);

bool FastFourierTransform_3D(double ***u, int *n, complex<double> ***U);
bool FastFourierTransform_3D(complex<double> ***u, int *n, complex<double> ***U);

bool FastInverseFourierTransform_3D(complex<double> ***u, int *n, complex<double> ***U);
bool FourierTransform(std::vector<complex<double> >& pp, std::vector<complex<double> >& ff, int l, int il);