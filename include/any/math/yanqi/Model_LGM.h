#include <math.h>


void Cal_Jacoobi_Matrix(int m, double *t, double *G, double X[3], double **DF);
void Cal_FunctionValues(int m, double *t, double *G, double X[3], double F[3]);

double Cal_f1_LGM(int m, double *t, double *G, double K, double a, double n);
double Cal_f2_LGM(int m, double *t, double *G, double K, double a, double n);
double Cal_f3_LGM(int m, double *t, double *G, double K, double a, double n);

double Differential_f1K_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f1a_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f1n_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f2K_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f2a_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f2n_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f3K_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f3a_LGM(int m, double *t, double *G, double K, double a, double n);
double Differential_f3n_LGM(int m, double *t, double *G, double K, double a, double n);

void Cal_LGM_Model_Unknow_K(int m, double *t, double *G, double &K, double &a, double &n);
void Cal_LGM_Model_Know_K(int m, double *t, double *G0, double K, double &a, double &n);
double Cal_LGM_Model_t_q(double t, double K, double a, double n);
double Cal_LGM_Model_t_G(double t, double K, double a, double n);


void Cal_LGM_Model_Unknow_K_PHR(int m, double *t, double *G, double &K, double &a, double &n);
void Cal_Jacoobi_Matrix_PHR(int m, double *t, double *G, double X[3], double **DF, double gMax, double Lmd, double Omiga);
void Cal_FunctionValues_PHR(int m, double *t, double *G, double *X, double *F, double gMax, double Lmd, double Omiga);
double Cal_FunctionG_PHR(double X[3], double gMax, double Lmd, double Omiga);
