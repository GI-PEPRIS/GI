#include <math.h>
#include "LaguerreAndHermit_Integration.h"
#include "CurveFittingUsingLeastSquareMethodCommonLib.h"


void SEPD_ParameterSeeking(double C1, double C2, double r1, double C3, double C4, double r2, double &n, double &Tao);
double GamaMode_Fm(double x, double **L, int nL);
double GamaMode_Fm2(double x, double y, double **L, int nL);
double GamaMode_Fm3(double x, double y, double **L, int nL);
void Cal_EquationSetValue(double C1, double C2, double r1, double C3, double C4, double r2, double *x, double *f, double **L, int nL);
void Solve_SEPD_EquationSet(double C1, double C2, double r1, double C3, double C4, double r2, double &n, double &Tao);

double SEPD_EquationValue_t_q(double t, double q0, double n, double Tao);
double SEPD_EquationValue_t_Q(double t, double q0, double n, double Tao);
double SEPD_EquationValue_EUR(double q0, double n, double Tao);
double SEPD_EquationValue_rp(double Q, double q0, double n, double EUR);
double SEPD_EquationValue_rp(double q, double q0, double n);

