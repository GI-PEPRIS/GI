#ifndef __ANYMATH_AUTO_SELECT_MODE_H__
#define __ANYMATH_AUTO_SELECT_MODE_H__

#include "curvefittingusingleastsquaremethodcommonlib.h"

// refer to stl
#include "any/base/anystl.h"

class AutoSelectModeCurveFittingResult
{
public:
		int ModeNo;      //模型代码
		char ModeName[30];   //模型名称
		int nParam;      //模型中未知参数个数
		double *Params;   //模型中未知参数计算结果
		double (*CurveFunction)(double, double *, int, double *); //计算模型函数的值
		PartialDerivativeDeFunction *PDF;   //计算各未知参数进行偏导函数的值
		double ERR;       //拟合计算结果的均方差
		bool Success;     //模型计算成功标志，Success=True,表明模型参数计算成功，否则计算失败

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

