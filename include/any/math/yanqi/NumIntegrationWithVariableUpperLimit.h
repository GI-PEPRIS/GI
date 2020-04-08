#include "any/base/anystl.h"

#include "NumericalIntegration.h"

//typedef double(*IntegrandFunction)(x);
//typedef double(*IntegrandFunction)(double x, double *P, int nP);
//typedef double(*IntegrandFunction)(double x);
//
#include "boost/function.hpp"
typedef boost::function<double (double, const string&)> Compression_Function;

double NumIntegrationWithVariableUpperLimit_K1(double x, double y, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP);
double NumIntegrationWithVariableUpperLimit_K2(double x, double y, double h, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP);
bool NumIntegrationWithVariableUpperLimit(double x0, double fx0, double h, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP, double &X);
