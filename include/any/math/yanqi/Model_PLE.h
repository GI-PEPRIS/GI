//#include "NumericalIntegration.h"
#include "Model_qDb.h"

void Cal_PLE_Model(int m0, double *t0, double *q0, double &n, double &D1, double &D8, double &qi);

void Cal_nD1_PLE(int m, double *t, double *D, double &n, double &D1);
double Cal_D8_PLE(int m, double *t, double *D, double n, double D1);
double Cal_qi_PLE(int m, double *t, double *q, double n, double D1, double D8);

void Cal_AllParamters_PLE(int m, double *t, double *q, double *D, double &n, double &D1, double &D8, double &qi, double deltaD);
double Cal_Production_q_PLE(double t, double n, double D1, double D8, double qi);
double Cal_CumulativeProduction_Q_PLE(double t0, double t1, double n, double D1, double D8, double qi);
double Cal_DeclineRate_D_PLE(double t, double n, double D1, double D8);
double Cal_Production_q_PLE(double x, double *P, int np);
double Cal_DecayIndex_b_PLE(double t, double n, double D1, double D8);


 