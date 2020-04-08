#include <math.h>
void Cal_am_Doung(int n, double *t, double *q, double *Q, double &aa, double &m);
void Cal_q0q8_Doung(int n, double *t, double *q, double aa, double m, double &q0, double &q8);
double Cal_tam_Doung(double t, double a, double m);
void Cal_AllParamters_Doung(int n, double *t, double *q, double *Q, double &aa, double &m, double &q0, double &q8);
double Func_q_t_Doung(double t, double a, double m, double q0, double q8);
double Func_Q_t_Doung(double t, double a, double m, double q0);
double Func_D_t_Doung(double t, double a, double m);
double Func_b_t_Doung(double t, double a, double m);
