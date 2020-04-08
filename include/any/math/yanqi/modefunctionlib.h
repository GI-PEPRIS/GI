#ifndef __ANYMATH_AUTO_SELECT_MODE_H__
#define __ANYMATH_AUTO_SELECT_MODE_H__

#include "curvefittingusingleastsquaremethodcommonlib.h"

// refer to stl
#include "any/base/anystl.h"

class AutoSelectModeCurveFittingResult
{
public:
		int ModeNo;      //ģ�ʹ���
		char ModeName[30];   //ģ������
		int nParam;      //ģ����δ֪��������
		double *Params;   //ģ����δ֪����������
		double (*CurveFunction)(double, double *, int, double *); //����ģ�ͺ�����ֵ
		PartialDerivativeDeFunction *PDF;   //�����δ֪��������ƫ��������ֵ
		double ERR;       //��ϼ������ľ�����
		bool Success;     //ģ�ͼ���ɹ���־��Success=True,����ģ�Ͳ�������ɹ����������ʧ��

		AutoSelectModeCurveFittingResult(){
			ModeNo=-1;
			Params=NULL;
			PDF=NULL;
			Success=false;
		}
		~AutoSelectModeCurveFittingResult(){
			if(Params!=NULL){
				delete [] Params;
			}
			if(PDF!=NULL){
				delete [] PDF;
			}
		}
		void Init(int N, int nP){
			ModeNo = N;
			nParam = nP;
			Params = new double[nParam];
			PDF = new PartialDerivativeDeFunction[nParam];
		}
		double ValueOfModeFunction(double x, double *OParam){
			return (*CurveFunction)(x, Params, nParam, OParam);
		}
};

void AutoSelectModeCurveFitting(int nxy, double *x, double *y, AutoSelectModeCurveFittingResult *RV, int Type=-1);
double PowerEquationModeFun(double x, double *Parms, int nParms, double *OParam);
double PowerEquationModeFun_PartialDerivativeA(double x, double *Parms, double *OParam);
double PowerEquationModeFun_PartialDerivativeB(double x, double *Parms, double *OParam);
double ExponentialEquationModeFun(double x, double *Parms, int nParms, double *OParam);
double ExponentialEquationModeFun_PartialDerivativeA(double x, double *Parms, double *OParam);
double ExponentialEquationModeFun_PartialDerivativeB(double x, double *Parms, double *OParam);
double LogarithmEquationModeFun(double x, double *Parms, int nParms, double *OParam);
double LogarithmEquationModeFun_PartialDerivativeA(double x, double *Parms, double *OParam);
double LogarithmEquationModeFun_PartialDerivativeB(double x, double *Parms, double *OParam);
double InverseExponentialEquationModeFun(double x, double *Parms, int nParms, double *OParam);
double InverseExponentialEquationModeFun_PartialDerivativeA(double x, double *Parms, double *OParam);
double InverseExponentialEquationModeFun_PartialDerivativeB(double x, double *Parms, double *OParam);
double S_IncreaseModeFun(double x, double *Parms, int nParms, double *OParam);
double S_IncreaseModeFun_PartialDerivativeA(double x, double *Parms, double *OParam);
double S_IncreaseModeFun_PartialDerivativeB(double x, double *Parms, double *OParam);
double Z_IncreaseModeFun(double x, double *Parms, int nParms, double *OParam);
double Z_IncreaseModeFun_PartialDerivativeA(double x, double *Parms, double *OParam);
double Z_IncreaseModeFun_PartialDerivativeB(double x, double *Parms, double *OParam);
void CopyAutoSelectModeCurveFittingResult(AutoSelectModeCurveFittingResult oRV, AutoSelectModeCurveFittingResult *RV);
double CalculateStandardDeviation(int nxy, double *x, double *y, double *Param, AutoSelectModeCurveFittingResult *Res);

#endif

