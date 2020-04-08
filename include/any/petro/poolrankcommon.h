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
        double **P;     //ǰnP���Ͳع�ģ��5����λ����95%��75%��50%��25%��5%����Ӧ�Ĺ�ģֵ
                        //P[][0]=95%��Ӧ�Ĺ�ģֵ
                        //P[][1]=75%��Ӧ�Ĺ�ģֵ
                        //P[][2]=50%��Ӧ�Ĺ�ģֵ
                        //P[][3]=25%��Ӧ�Ĺ�ģֵ
                        //P[][4]=5%��Ӧ�Ĺ�ģֵ
                        //P[i][j]��ʾ�����ڵ�i��λ���ϵ������أ�����i�������أ��ڵ�j����λ��ʱ����Ӧ��ģֵ
        int *LikelyNo;  //ǰnP���Ͳع�ģ��λ��λ�����
                        //LikelyNo[i]��˵����iΪ��λ˳��λ�ã����Ӵ�С��˳��
                        //��LikelyNo[i]>=0ʱ����ʾ��λ���ϵ��Ͳ�Ϊ�ѷ����Ͳأ����ͲصĹ�ģΪx0[LikelyNo[i]]��
                        //        x0��ʾ�����Ӵ�С��˳�����к�ģ��ѷ����Ͳع۲�ֵ������ԭʼ���ݣ���
                        //��LikelyNo[i]<0ʱ����ʾ��λ���ϵ��Ͳ�ΪԤ���Ͳأ����ͲصĹ�ģΪ���䣺
                        //��P[n][3]��P[n][1]��������n=abs(LikelyNo[i])��
                        //ע����һ�������������Ԥ�������Ϊ0ʱ������-99999��ʾ���������ѷ����Ͳص�������0
                        //���³�����ǹ�λ���ݵ���ʾ���������˵��x0��P��LikelyNo֮��Ĺ�ϵ��
        int nP;
        UpperPercentileClass(int m){
            nP = m;
            P = new double*[nP];
            for (int j = 0; j<nP; j++){
                P[j] = new double[5];
            }
            LikelyNo = new int[nP];
            for (int j = 0; j<nP; j++){
                LikelyNo[j] = -99999;   //��ʼ��Ϊһ������ֵ���ڹ�λ������Ҫ�õ�
            }
        }
        ~UpperPercentileClass(){
            for(int i=0; i<nP; i++)
                delete [] P[i];                 // STEP 1: DELETE THE COLUMNS
            delete [] P;                        // STEP 2: DELETE THE ROWS
            delete [] LikelyNo;
        }
        void OutFallbackResult(int FP, int &Ps, int &OE){
        //����ɲ���FP��ָ��λ���ϵĹ�Ϊ���
        //  0��FP<nP
        //  Ps�����ز�������ֵ��������OE�йأ��������˵��
        //  OE�����ز�������ǹ�λ��������ʣ�
        //         ��OE=0ʱ����ʾ��λ������һ���ѷ��������أ���ʱPsΪ�����������ѷ��������ع�ģ�۲�ֵ�����Ӵ�С��˳�����У������е��±�
        //         ��OE=1ʱ����ʾ��λ������һ��Ԥ�������أ���ʱPs��ʾ���������ڷ�λ������P������Ӧ�ģ���һά���±�
        //                        �������ع�ģ��5����λ������
        //         ��OE=-1ʱ����ʾ�����FP��ֵ���󣬳����˶��巶Χ����ʱPs������
                if(FP<0 || FP>=nP){
                   OE = -1;
                   return;
                }
                Ps = LikelyNo[FP];
                if(Ps<0){   //����λ����LikelyNo[FP]��ֵΪ����ʱ����ʾ��λ������Ԥ���Ͳ�
                   OE = 1;
                   if(Ps == -99999){ //Ps == -99999��ʾ��λ����ΪԤ�������أ����ڷ�λ������P�е�λ��Ϊ0������������Ϊ�����ѷ��������ص�λ��0������
                      Ps = 0;
                   }else{
                      Ps = -Ps;
                   }
                }else{  //����λ����LikelyNo[FP]��ֵ���ڻ����0ʱ����ʾ��λ�������ѷ����Ͳ�
                   OE = 0;
                }
        }
        bool OutputUpper5Percentile(int iP5, double *P5){
        //����ɲ���iP5��ָ��λ���ϵ�5����λ������Ӧ�������ع�ģֵ
        //  0��iP5<nP
        //  P5��һ��������5��Ԫ�ص�����
                if(iP5<0 || iP5>=nP){
                   return false;
                }
                for(int i=0; i<5; i++){
                    P5[i] = P[iP5][i];
                }
                return true;
        }
        int CheckFallback(void){
        //��λ�����飬���ع�λ���ɹ����ѷ��������ظ���
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
        //���ع�λʧ�ܵ��ѷ��������أ��ڰ���С����������ѷ��������ع�ģ�����У���������
        //������Ҫ��CheckFallback���ʹ��
        //n��n>0, ��λʧ�ܵ��ѷ��������ظ�������ͨ��CheckFallback�õ���
        //sno����λʧ�ܵ��ѷ��������������ţ���n��Ԫ��
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
