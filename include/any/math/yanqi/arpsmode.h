#include <math.h>



double ArpsMode_valueNp_t(double t, double Q0, double a0, double n);


void ArpsModeCurveFitting_Q_t(int Nxy, double *x, double *y, double Q0, double a0, double &n);
double ArpsMode_valueQ_t(double t, double Q0, double a0, double n);
double ArpsMode_valueQ_t_1(double t, double *Params, int Nparms, double *OParams);
double ArpsMode_valueQ_t_nPartialDerivative(double t, double *Params, int Nparms, double *OParams);
bool ArpsMode_valuea_Q_t_DomainCheck(double t, double *Params, int Nparms, double *OParams);

void ArpsModeCurveFitting_Np_Q(int Nxy, double *x, double *y, double Q0, double a0, double &n);
double ArpsMode_valueNp_Q_nPartialDerivative(double Q, double *Params, double *OParams);
double ArpsMode_valueNp_Q(double Q, double Q0, double a0, double n);
double ArpsMode_valueNp_Q_1(double Q, double *Params, int Nparms, double *OParams);
bool ArpsMode_value_Np_Q_DomainCheck(double Q, double *Params, int Nparms, double *OParams);


void ArpsModeCurveFitting_a_t(int Nxy, double *x, double *y, double a0, double &n);
double ArpsMode_value_a_t_nPartialDerivative(double t, double *Params, double *OParams);
double ArpsMode_value_a_t(double t, double a0, double n);
double ArpsMode_value_a_t_1(double t, double *Params, int Nparms, double *OParams);
bool ArpsMode_value_a_t_DomainCheck(double t, double *Params, int Nparms, double *OParams);



