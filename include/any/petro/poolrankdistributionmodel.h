//���ֲ����ܶȺ���
double ExponentialDensityFun(double x, int nP, double *P);   //ָ���ֲ��ܶȺ���
double Normal(double x, int nP, double *P);    //��̬�ֲ��ܶȺ���
double LogNormal(double x, int nP, double *P);    //������̬�ֲ��ܶȺ���

void GenerateExponentialRandoms(double lmda, int N, double *x);   //����һ��ָ���ֲ������
void GenerateNormalRandoms(double miu,double sigma, int N, double *x);  //����һ����̬�ֲ���������������õ��������ֵ������0
void GenerateLogNormalRandoms(double miu,double sigma, int N, double *x); //����һ�������̬�ֲ������

void GenerateRandomNumber01(int nr, double *r);
double AverageRandom(double min,double max);
double NormalRandom(double miu,double sigma,double min,double max);
