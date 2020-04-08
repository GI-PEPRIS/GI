#include "ExperimentalVariogram_BaiscHead.h"
#include "CurveFittingUsingLeastSquareMethodCommonLib.h"

struct InterpolationDotInfo
{
    public:
        int NO;       //参加插值点在原始数据中的序号；
        double dist;  //参加插值点与被插值网格点之间的距离；
        double cosAngle; //各向异性时，记录被插值网格点->参加插值观测点组成的向量与方向向量dirP之间的夹角的余弦值
};


class CubicBox
{
       public:
           double x[8],y[8],z[8];  //立方体的8个定点坐标
           double dirP[3];  //（立方体长轴的）方向向量，以0->dirP表示
           double cP[3];  //立方体中心坐标
           double eP[3];  //以dirP为方向、以cP为起点、且距cP点为H/2的向量的终点坐标
           double L,W,H;   //立方体的长、宽、高(长>=宽>=高)
           double **MaxtrixCoordinateTransformation;   //坐标变换矩阵
       CubicBox(){   //给定中心坐标及长、宽、高，构建立方体结构
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
           //给定中心坐标及长、宽、高，构建立方体结构
           //cP1: 立方体中心坐标
           //L1, W1, H1: 立方体的长、宽、高
           //dirP1: 立方体长轴的方向向量, (0,0,0)->(dirP1[0],dirP1[1],dirP1[2]);
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
           //使立方体满足：长>=宽>=高
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

           Cal_DirectP_3D(cP, dirP, L/2.0, eP); //求eP
           for(int i=0; i<3; i++){
               MaxtrixCoordinateTransformation[3][i] = -cP[i];  //把cP平移到坐标原点的变换矩阵
           }
           BuildRotateMatrix();
       }
        void Cal_DirectP_3D(double *P0, double *dirP, double h, double *P)
        {
        //------ 给定空间中的一点P0(cx, cy, cz)、一个方向dirP, 求以P0为起点，以dirP为方向的向量上距P0点的距离为h的点P的坐标-----------
        //P： 向量起始点坐标（3个元素的一维素组，分别代表X、Y、Z）
        //dirP：方向点坐标（或称方向数）（3个元素的一维素组，分别代表X、Y、Z），向量O→dirP代表向量的方向（O表示坐标原点）；
        //      且方向点dirP≠(0,0,0)
        //h:  所求点P与P0之间的距离
        //P：所求点坐标（3个元素的一维素组，分别代表X、Y、Z）
                double t;
                t = h/sqrt(dirP[0]*dirP[0]+dirP[1]*dirP[1]+dirP[2]*dirP[2]);
                P[0] = P0[0] + t*dirP[0];
                P[1] = P0[1] + t*dirP[1];
                P[2] = P0[2] + t*dirP[2];
        }


       void BuildRotateMatrix(){  //建立坐标旋转变换矩阵: 把立方体的中心cP在坐标原点时，把向量cP->eP旋转到与x轴正向重合时的矩阵变换
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
            //利用已建立好的变换矩阵对坐标进行变换,P是至少有3个元素的一维素组
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
