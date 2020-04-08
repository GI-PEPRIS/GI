void InverseGamaParameterEstimation_UseP10P90(double Q10, double Q90, double &Gama, double &Lmda);
int InverseGamaRevisionX(double Q10, double Q90,double *X, double *X1, double *F, double *tt, double **L, int nL);
void Cal_InverseGamaF(double Gama, double Lmda, double Q10, double Q90, double *F, double **L, int nL);
double InverseGamaMode_CDF(double x, double Gama, double Lmda, double **L, int nL);
double InverseGamaMode_Fm(double Gama, double **L, int nL);
double InverseGamaMode_Fz(double x, double Gama, double Lmda, double **L, int nL);
void Cal_InverseGamaDF(double Gama, double Lmda, double q10, double q90, double **L, int nL, double dfv[2][2]);
double InverseGamaMode_dGGama(double x, double Gama, double Lmda, double **L, int nL);
double InverseGamaMode_dGLmda(double x, double Gama, double Lmda, double **L, int nL);
 