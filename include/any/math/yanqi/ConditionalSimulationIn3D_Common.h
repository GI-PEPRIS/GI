#include <math.h>
#define RandCoef2053 2053
#define RandCoef13849 13849
#define MODUL65536 65536

#ifndef __CONDITIONALSIMULATION_H__
#define __CONDITIONALSIMULATION_H__


struct CoordiateParaments{  //����ģ��ԭʼ���ݵ��������
    public:
        double xmin, ymin, zmin;
//        double xmax, ymax, zmax;
//        double dx, dy, dz;
//        double Hx, Hy, Hz;
//        int nHx, nHy, nHz;
};

struct ConditionDataParas{ //����ÿ������������������������֮��Ĺ�ϵ����
    public:
        int iX, iY, iZ; //��������������������ڵ�ģ���������
        double x,y,z;   //���������ݵ�ԭʼ�۲�����
        double v;      //���������ݵ�ԭʼֵ
        double sv;      //ͨ���������ݲ�ֵ���õ���������ڵ�[iX][iY][iZ]����ֵ
        double d;     //����������������������֮��ľ���
};

double RandomUniform01(double seed);
void CreateConditionDataParaments(double *Grid0,
                                  double *x, double *y, double *z, double *v, int n,
                                  double *H0, int *nH, ConditionDataParas *codps,
                                  int InterpretatDots=8);
void RearrayIntDot(ConditionDataParas *iDs, int intDs);                                  

void ChangeGridcondition2Realcondition(double *Grid0, double *H0,
                                      int GridX, int GridY, int GridZ,
                                      double &x, double &y, double &z);
#endif
