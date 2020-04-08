#include <math.h>
#define RandCoef2053 2053
#define RandCoef13849 13849
#define MODUL65536 65536

#ifndef __CONDITIONALSIMULATION_H__
#define __CONDITIONALSIMULATION_H__


struct CoordiateParaments{  //描述模拟原始数据的坐标参数
    public:
        double xmin, ymin, zmin;
//        double xmax, ymax, zmax;
//        double dx, dy, dz;
//        double Hx, Hy, Hz;
//        int nHx, nHy, nHz;
};

struct ConditionDataParas{ //描述每个条件数据与其最近的网格点之间的关系参数
    public:
        int iX, iY, iZ; //与该条件数据最近的网格节点的（网格）坐标
        double x,y,z;   //该条件数据的原始观测坐标
        double v;      //该条件数据的原始值
        double sv;      //通过条件数据插值所得到的在网格节点[iX][iY][iZ]处的值
        double d;     //条件数据与其最近的网格点之间的距离
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
