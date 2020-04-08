#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "any/base/anymediator.h"
using namespace AnyBase;

typedef class SamplingDataClass
{
protected:

public:
        int nData;
        double *x;
        SamplingDataClass(int n, double *y){
           nData = n;
           x = new double[n];
           for(int i=0; i<n; i++){
              x[i] = y[i];
           }
        }
        ~SamplingDataClass(){
           delete [] x;
        }
}SamplingDataClass;


typedef class UpperPercentileClass
{
public:
        double **P;     //前nP个油藏规模的5个分位数（95%、75%、50%、25%、5%）对应的规模值
                        //P[][0]=95%对应的规模值
                        //P[][1]=75%对应的规模值
                        //P[][2]=50%对应的规模值
                        //P[][3]=25%对应的规模值
                        //P[][4]=5%对应的规模值
                        //P[i][j]表示排序在第i个位置上的油气藏（即第i大油气藏）在第j个分位数时所对应规模值
        int *LikelyNo;  //前nP个油藏规模归位的位置序号
                        //LikelyNo[i]的说明：i为归位顺序位置（按从大到小的顺序）
                        //当LikelyNo[i]>=0时，表示该位置上的油藏为已发现油藏，该油藏的规模为x0[LikelyNo[i]]，
                        //        x0表示（按从大到小的顺序排列后的）已发现油藏观测值（即：原始数据）；
                        //当LikelyNo[i]<0时，表示该位置上的油藏为预测油藏，该油藏的规模为区间：
                        //【P[n][3]，P[n][1]】，这里n=abs(LikelyNo[i])；
                        //注意有一种特殊情况：当预测区间号为0时，则用-99999表示，以区分已发现油藏的样本号0
                        //以下程序段是归位数据的显示输出，用以说明x0、P、LikelyNo之间的关系：
        int nP;
        UpperPercentileClass(int m){
            nP = m;
            P = new double*[nP];
            for (int j = 0; j<nP; j++){
                P[j] = new double[5];
            }
            LikelyNo = new int[nP];
            for (int j = 0; j<nP; j++){
                LikelyNo[j] = -99999;   //初始化为一个特殊值，在归位过程中要用到
            }
        }
        ~UpperPercentileClass(){
            for(int i=0; i<nP; i++)
                delete [] P[i];                 // STEP 1: DELETE THE COLUMNS
            delete [] P;                        // STEP 2: DELETE THE ROWS
            delete [] LikelyNo;
        }
        void OutFallbackResult(int FP, int &Ps, int &OE){
        //输出由参数FP所指定位置上的归为结果
        //  0≤FP<nP
        //  Ps：返回参数，其值的意义与OE有关，见下面的说明
        //  OE：返回参数，标记归位结果的性质：
        //         当OE=0时，表示该位置上是一个已发现油气藏，此时Ps为该油气藏在已发现油气藏规模观测值（按从大到小的顺序排列）数组中的下标
        //         当OE=1时，表示该位置上是一个预测油气藏，此时Ps表示该油气藏在分位数数组P中所对应的（第一维）下标
        //                        其油气藏规模由5个分位数给定
        //         当OE=-1时，表示输入的FP的值错误，超出了定义范围，此时Ps无意义
                if(FP<0 || FP>=nP){
                   OE = -1;
                   return;
                }
                Ps = LikelyNo[FP];
                if(Ps<0){   //当该位置上LikelyNo[FP]的值为负数时，表示该位置上是预测油藏
                   OE = 1;
                   if(Ps == -99999){ //Ps == -99999表示该位置上为预测油气藏，其在分位数数组P中的位置为0，这样设置是为了与已发现油气藏的位置0相区分
                      Ps = 0;
                   }else{
                      Ps = -Ps;
                   }
                }else{  //当该位置上LikelyNo[FP]的值大于或等于0时，表示该位置上是已发现油藏
                   OE = 0;
                }
        }
        bool OutputUpper5Percentile(int iP5, double *P5){
        //输出由参数iP5所指定位置上的5个分位数所对应的油气藏规模值
        //  0≤iP5<nP
        //  P5是一个至少有5个元素的数组
                if(iP5<0 || iP5>=nP){
                   return false;
                }
                for(int i=0; i<5; i++){
                    P5[i] = P[iP5][i];
                }
                return true;
        }
        int CheckFallback(void){
        //归位结果检查，返回归位不成功的已发现油气藏个数
                int sn, tn, m;
                tn = -1;
                for(int i=0; i<nP; i++){
                    m = LikelyNo[i];
                    if(m < 0){
                        continue;
                    }
                    tn = (tn>m) ? tn : m;
                }
                tn += 1;
                int *oPos = new int[tn];
                for(int i=0; i<tn; i++){
                    oPos[i] = i;
                }

                for(int i=0; i<nP; i++){
                    m = LikelyNo[i];
                    if(m < 0){
                        continue;
                    }
                    oPos[m] = -1;
                }

                sn = 0;
                for(int i=0; i<tn; i++){
                    if(oPos[i] >= 0){
                        sn++;
                    }
                }
                delete [] oPos;
                return sn;
        }
        void OutNonFallbackNo(int n, int *sno){
        //返回归位失败的已发现油气藏（在按从小到大排序的已发现油气藏规模数组中）的样本号
        //本段需要与CheckFallback配合使用
        //n：n>0, 归位失败的已发现油气藏个数，须通过CheckFallback得到；
        //sno：归位失败的已发现油气藏样本号，有n个元素
                int sn, tn, m;
                tn = -1;
                for(int i=0; i<nP; i++){
                    m = LikelyNo[i];
                    if(m < 0){
                        continue;
                    }
                    tn = (tn>m) ? tn : m;
                }
                tn += 1;
                int *oPos = new int[tn];
                for(int i=0; i<tn; i++){
                    oPos[i] = i;
                }

                for(int i=0; i<nP; i++){
                    m = LikelyNo[i];
                    if(m < 0){
                        continue;
                    }
                    oPos[m] = -1;
                }

                m = 0;
                for(int i=0; i<tn; i++){
                    if(oPos[i] >= 0){
                        sno[m] = oPos[i];
                        m++;
                    }
                }
                delete [] oPos;
        }

}UpperPercentileClass;



void RearrangeFromLargerToLittle(int nx, double *x);
void Build_CFGT(int nx, double *x, int xint, double *xinterval, double *CFGT);
void Build_xinterval(int nx, double *x, int xint, double *xinterval);
double Cal_XusePercentile(double percentile, int xint, double *xinterval, double *CFGT);
double Cal_PercentileUseX(double x, int xint, double *xinterval, double *CFGT);
double LinearInterpolation(double xa, double ya, double xb, double yb, double xoy, char xymark);

void CubicSplineInterpolationCoefficient(int xn, double *x, double *y, double *M, double dx0, double dxn);
double CubicSplineInterpolation(int nx, double *x, double *y, double *M, double cx);
double AntiCubicSplineInterpolation(int nx, double *x, double *y, double *M, double cy, int YD);
void Equations_setUseChasingMethod(int n, double *lmd, double *G, double *M);
int SolveCubicEquationWithOneUnknown(double a, double b, double c, double *roots);

void Cal_Percentile(int np, int SN, SamplingDataClass **sd, UpperPercentileClass *Percentile);
void OilSizeFallbackPosition(int n, double *x0, UpperPercentileClass *Percentile);

void ReduceUncertainty( int nx, double *x0,
                        UpperPercentileClass *Percentile,
                        double (*hf)(double, int, double *),
                        int nP, double *P);

UpperPercentileClass* Cal_Upper5Percentile(int nx, double *x0, int SamplingNum, int SampleNum, int MaxPoolNum,
               double (*hf)(double, int, double *), int nP, double *P, CAnyFunctor &progress);
void DeleteReduplicateDots(int &n, double *x);               
