//各分布的密度函数
double ExponentialDensityFun(double x, int nP, double *P);   //指数分布密度函数
double Normal(double x, int nP, double *P);    //正态分布密度函数
double LogNormal(double x, int nP, double *P);    //对数正态分布密度函数

void GenerateExponentialRandoms(double lmda, int N, double *x);   //产生一组指数分布随机数
void GenerateNormalRandoms(double miu,double sigma, int N, double *x);  //产生一组正态分布随机数，并且所得到的随机数值都大于0
void GenerateLogNormalRandoms(double miu,double sigma, int N, double *x); //产生一组对数正态分布随机数

void GenerateRandomNumber01(int nr, double *r);
double AverageRandom(double min,double max);
double NormalRandom(double miu,double sigma,double min,double max);
