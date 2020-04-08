#include<vector>
#include "any/base/anyport.h"

#include "NumIntegrationWithVariableUpperLimit.h"
using namespace std;

//const static long ANY_NANSPEC[2]={0xFFFFFFFF, 0x7FFFFFFF};
//const static double ANY_NAN=*(double*)(ANY_NANSPEC);

class RegainBurialHistoryUsingBack_Stripping_ForMultiFunction{
//����������ͬ����¼���ز�Ǽܺ�ȵĺ����������
//�������Ķ���������ȶ����ڱ��ṹ�еĲ�����FromDepth, ToDepth����Χ��ʱ�����ú�����myFunction����ĺ�������ز�Ǽܺ��
//myFunction������Ҫ��������������ͨ��AddFunctionParameter�����ӵ����ṹ�в����ݵ�myFunction
        public:
            double FromDepth, ToDepth;
            Compression_Function myFunction;
			int m_divisions;
			string m_formulae;

			// deprecated variables
            int nP;
            double *P;


       RegainBurialHistoryUsingBack_Stripping_ForMultiFunction(double minD, double maxD, int divisions, Compression_Function Function, const string& formulae){
            FromDepth=minD;
            ToDepth=maxD;
            myFunction=Function;
            P=0;
            nP=0;
			m_divisions = divisions;
			m_formulae = formulae;
       }
       ~RegainBurialHistoryUsingBack_Stripping_ForMultiFunction(){
            if(P!=0){
                delete[] P;
                nP=0;
            }
       }
       int AddFunctionParameter(double x){
            double *a;
            a = new double[nP+1];
            for(int i=0; i<nP; i++){
                a[i]=P[i];
            }
            a[nP]=x;
            if(P!=0){
                delete[] P;
            }
            P=a;
            nP++;
            return nP;
       }
};


void RegainBurialHistoryUsingBack_Stripping(int nLayer, double *Thickness, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP, double **H);
void RegainBurialHistoryUsingBack_Stripping(int nLayer, double *Thickness, std::vector<RegainBurialHistoryUsingBack_Stripping_ForMultiFunction *>UserFun,
                                            double **H);

double CalLayerSkeletonThickness(double z1,double z2, Compression_Function myIntegrandFunction, const string& formulae, double *P, int nP);
double NumericalIntegration_Self(double a, double b, Compression_Function IFun,const string& formulae, 
	double *IFunPs, int IPs, int n);

