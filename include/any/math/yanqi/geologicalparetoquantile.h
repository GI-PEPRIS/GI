void ParetoParameterEstimation_UseQuantile(double qmin, double qmax, double Q10, double Q90, double &Gama, double &Lmda);
int RevisionX(double qmin, double qmax, double Q10, double Q90,double *X, double *X1, double *F, double *tt);
void Cal_IDf(double DF[2][2], double IDF[2][2]);
void Cal_F(double qmax, double q0, double Gamam, double Lmda, double Q10, double Q90, double *F);
double Pareto_CDF(double qmax, double q0, double Gamam, double Lmda, double q);
void Cal_DF(double qmax, double q0, double Gama, double Lmda, double q10, double q90, double dfv[2][2]);
double PartialDerivative_Gama(double qmax, double q0, double Gama, double Lmda, double q);
double PartialDerivative_Lmda(double qmax, double q0, double Gama, double Lmda, double q);
 