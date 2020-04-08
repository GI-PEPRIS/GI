#include "ExperimentalVariogram_BaiscHead.h"
#include "CurveFittingUsingLeastSquareMethodCommonLib.h"

struct InterpolationDotInfo
{
    public:
        int NO;       //�μӲ�ֵ����ԭʼ�����е���ţ�
        double dist;  //�μӲ�ֵ���뱻��ֵ�����֮��ľ��룻
        double cosAngle; //��������ʱ����¼����ֵ�����->�μӲ�ֵ�۲����ɵ������뷽������dirP֮��ļнǵ�����ֵ
};


class CubicBox
{
       public:
           double x[8],y[8],z[8];  //�������8����������
           double dirP[3];  //�������峤��ģ�������������0->dirP��ʾ
           double cP[3];  //��������������
           double eP[3];  //��dirPΪ������cPΪ��㡢�Ҿ�cP��ΪH/2���������յ�����
           double L,W,H;   //������ĳ�������(��>=��>=��)
           double **MaxtrixCoordinateTransformation;   //����任����
       CubicBox(){   //�����������꼰�������ߣ�����������ṹ
           MaxtrixCoordinateTransformation = new double*[4];
           for(int i=0; i<4; i++){
               MaxtrixCoordinateTransformation[i] = new double[4];
           }
       }
       ~CubicBox(void){
           for(int i=0; i<4; i++){
               delete[] MaxtrixCoordinateTransformation[i];
           }
           delete[] MaxtrixCoordinateTransformation;
       }

       void BuildCubicBox(double *cP1, double L1,double W1,double H1, double *dirP1)
       {
           //�����������꼰�������ߣ�����������ṹ
           //cP1: ��������������
           //L1, W1, H1: ������ĳ�������
           //dirP1: �����峤��ķ�������, (0,0,0)->(dirP1[0],dirP1[1],dirP1[2]);
           for(int i=0; i<4; i++){
               for(int j=0; j<4; j++){
                   MaxtrixCoordinateTransformation[i][j] = 0;
               }
               MaxtrixCoordinateTransformation[i][i] = 1;
           }

           double t;
           L=L1, W=W1, H=H1;
           for(int i=0; i<3; i++){
               cP[i]=cP1[i];
               dirP[i]=dirP1[i];
           }
           //ʹ���������㣺��>=��>=��
           if(L<W){
              t=L;
              L=W;
              W=t;
           }
           if(L<H){
              t=L;
              L=H;
              H=t;
           }
           if(W<H){
              t=W;
              W=H;
              H=t;
           }

           Cal_DirectP_3D(cP, dirP, L/2.0, eP); //��eP
           for(int i=0; i<3; i++){
               MaxtrixCoordinateTransformation[3][i] = -cP[i];  //��cPƽ�Ƶ�����ԭ��ı任����
           }
           BuildRotateMatrix();
       }
        void Cal_DirectP_3D(double *P0, double *dirP, double h, double *P)
        {
        //------ �����ռ��е�һ��P0(cx, cy, cz)��һ������dirP, ����P0Ϊ��㣬��dirPΪ����������Ͼ�P0��ľ���Ϊh�ĵ�P������-----------
        //P�� ������ʼ�����꣨3��Ԫ�ص�һά���飬�ֱ����X��Y��Z��
        //dirP����������꣨��Ʒ���������3��Ԫ�ص�һά���飬�ֱ����X��Y��Z��������O��dirP���������ķ���O��ʾ����ԭ�㣩��
        //      �ҷ����dirP��(0,0,0)
        //h:  �����P��P0֮��ľ���
        //P����������꣨3��Ԫ�ص�һά���飬�ֱ����X��Y��Z��
                double t;
                t = h/sqrt(dirP[0]*dirP[0]+dirP[1]*dirP[1]+dirP[2]*dirP[2]);
                P[0] = P0[0] + t*dirP[0];
                P[1] = P0[1] + t*dirP[1];
                P[2] = P0[2] + t*dirP[2];
        }


       void BuildRotateMatrix(){  //����������ת�任����: �������������cP������ԭ��ʱ��������cP->eP��ת����x�������غ�ʱ�ľ���任
            double **RMatrixX, **RMatrixY, **RMatrix;
            RMatrixX = new double*[4];
            RMatrixY = new double*[4];
            RMatrix = new double*[4];
            for(int i=0; i<4; i++){
                RMatrixX[i] = new double[4];
                RMatrixY[i] = new double[4];
                RMatrix[i] = new double[4];
            }
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    RMatrixX[i][j] = 0;
                    RMatrixY[i][j] = 0;
                }
                RMatrixX[i][i] = 1;
                RMatrixY[i][i] = 1;
            }
            double t;
            double sa,ca,sb,cb;

            t = sqrt(dirP[1]*dirP[1] + dirP[2]*dirP[2]);
            sa = dirP[1]/t;
            ca = dirP[2]/t;
            RMatrixX[1][1] = ca;
            RMatrixX[1][2] = sa;
            RMatrixX[2][1] = -sa;
            RMatrixX[2][2] = ca;

            t = sqrt(dirP[0]*dirP[0] + dirP[1]*dirP[1] + dirP[2]*dirP[2]);
            sb = -sqrt(dirP[1]*dirP[1] + dirP[2]*dirP[2])/t;
            cb = dirP[0]/t;
            RMatrixY[0][0] = cb;
            RMatrixY[0][2] = sb;
            RMatrixY[2][0] = -sb;
            RMatrixY[2][2] = cb;
            MatrixProduct(MaxtrixCoordinateTransformation, RMatrixX, 4, 4, 4, RMatrix);
            MatrixProduct(RMatrix, RMatrixY, 4, 4, 4, MaxtrixCoordinateTransformation);

            for(int i=0; i<4; i++){
                delete[] RMatrixX[i];
                delete[] RMatrixY[i];
                delete[] RMatrix[i];
            }
            delete RMatrixX;
            delete RMatrixY;
            delete RMatrix;
       }
       void CoordinateTransformation(double *P)
       {
            //�����ѽ����õı任�����������б任,P��������3��Ԫ�ص�һά����
            double P1[4], P2[4];
            P1[0]=P[0],P1[1]=P[1], P1[2]=P[2], P1[3]=1;
            MatrixProductVector(P1, MaxtrixCoordinateTransformation, 4, 4, P2);
            P[0]=P2[0], P[1]=P2[1], P[2]=P2[2];
       }
       bool IsInBox(double *P)
       {
           CoordinateTransformation(P);
           double L1, W1, H1;
           L1 = L/2.0;
           W1 = W/2.0;
           H1 = H/2.0;
           if(P[0]<-L1 || P[0]>L1){
               return false;
           }
           if(P[1]<-W1 || P[1]>W1){
               return false;
           }
           if(P[2]<-H1 || P[2]>H1){
               return false;
           }
           return true;
       }

};


void GridInterpolation_3D_InverseDistanceWeight(double *x, double *y, double *z, double *v, int nXYZ,
                                                double x0, double y0, double z0,
                                                double *H0,double ***Grid, int *nH,
                                                int InterpolationDots=10);
void GridInterpolation_2D_InverseDistanceWeight(double *x, double *y, double *v, int nXY,
                                                double x0, double y0,
                                                double *H0,double **Grid, int *nH, int InterpolationDots=10);

void GridInterpolation_3D_OrdinaryKriging_Isotropic(double *x, double *y, double *z, double *v, int nXYZ,
                                                double x0, double y0, double z0,
                                                double *H0,double ***Grid, int *nH, int InterpolationDots,
                                                double a, double C0, double C, int ModelType);
void GridInterpolation_3D_OrdinaryKriging_AnsiIsotropic(double *x, double *y, double *z, double *v, int nXYZ,
                                                double x0, double y0, double z0,
                                                double *H0,double ***Grid, int *nH, int InterpolationDots,
                                                double a, double C0, double C,
                                                double *dirP, int ModelType);

void RearrayIntDot(InterpolationDotInfo *iDs, int intDs);
double Cal_2VectorCosAngle(double *P, double *P0, double *P1);

void GridInterpolation_3D_AfterInterpolation(double *H0,double ***Grid, int *nH,
                                             bool ***isInterpolated);

void GridInterpolation_3D_TheoryVariogram(double ***Grid, int *nH, double *H0, double a, double C0, double C, double *dirP,
                                          int ModelType, bool isAnisotropic);
void ChangeExperimentalVariogram3DGridToXY(double *H0, int *nH, double ***C, double *X, double *Y);
