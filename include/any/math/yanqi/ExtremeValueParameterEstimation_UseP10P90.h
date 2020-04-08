void ExtremeValueParameterEstimation_UseP10P90(double Q10, double Q90, double &mui, double &gama);
int ExtremeValueRevisionX(double Q10, double Q90, double *X, double *X1, double *F, double *tt);
void ExtremeValueMode_F(double mui, double gama, double Q10, double Q90, double *F);
void Cal_ExtremeValueDF(double mui, double gama, double q10, double q90, double dfv[2][2]);
double ExtremeValueMode_CDF(double x, double mui, double gama);
double ExtremeValueMode_PartialDerivative_mui(double x, double mui, double gama);
double ExtremeValueMode_PartialDerivative_gama(double x, double mui, double gama);
 