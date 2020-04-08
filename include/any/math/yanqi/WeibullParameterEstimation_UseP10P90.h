void WeibullParameterEstimation_UseP10P90(double Q10, double Q90, double &Lmda, double &K);
double WeibullMode_CDF(double x, double Lmda, double K);
double WeibullMode_PartialDerivative_Lmda(double x, double Lmda, double K);
double WeibullMode_PartialDerivative_K(double x, double Lmda, double K);

void WeibullMode_F(double Lmda, double K, double Q10, double Q90, double *F);
void Cal_WeibullDF(double Lmda, double K, double q10, double q90, double dfv[2][2]);
int WeibullRevisionX(double Q10, double Q90, double *X, double *X1, double *F, double *tt);

int Weibull_StartingValue_YTF(int nP, double *P, double *P0, double Q10, double Q90, int N=20);

