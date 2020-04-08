#if !defined(AFX_MBRBASE_H__7A8DF164_FDDC_47A9_BF79_BFE24FD1325F__INCLUDED_)
#define AFX_MBRBASE_H__7A8DF164_FDDC_47A9_BF79_BFE24FD1325F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
#include <stdio.h>
//#include "GasPvt.h"

using namespace std;

namespace AnyPetro
{
enum MBR_Parameter{
  IPR_A = 0,
  IPR_B,
  IPR_P0,
  OGIP_SRV,
  OGIP_OUT,
  IPR_A2
};

const string MBR_ParamNames[]={
    "IPR_A",
    "IPR_B",
    "IPR_P0",
    "OGIP_SRV",
    "OGIP_OUT",
    "A2"
};

enum WellCtrlType{
	constQg = 0,
	constBhp
};

enum RockType{
    NORMAL_GAS=0,
    SHALE_GAS
};

enum PZTabType{
	NoAdsorp = 0,
	Adsorp
};

struct MBR_Paramer_Info{
   MBR_Parameter param_name;
   double       val;//��ֵ
   double       lb;
   double       ub;
   int          fit_flag;//�Ƿ����
   MBR_Paramer_Info(MBR_Parameter pn,double value,double lb_,double ub_,int fit):
   param_name(pn),val(value),lb(lb_),ub(ub_),fit_flag(fit){}
   ~MBR_Paramer_Info(){}
};

struct Normal_Gas_mb_Data{
  double m_dIPR_A;
  double m_dIPR_B;
  double m_dA2;

  double m_dP0;//
  double m_dOGIP_SRV;//SRV������
  double m_dOGIP_Out;//��������
  double m_dGpw;//�����۲�����  
  double m_dGp12;//�������ۼƴ�����

  int    m_nAreaFlag;
  PZTabType m_nAdsorp_flag;
  int    m_nAbnormal_flag;
  int    m_nCompositeFlag;//�Ƿ��Ǹ�������

  double m_dCur_t;
  double m_dLast_t;
 
  double m_dLastqg;
  double m_dLastqg12;
 
  double m_dPavg_srv;
  double m_dPavg_Out;//����ƽ���ز�ѹ��

  //���Ʒ�ʽ��
  double m_dCtrlVal;//����ֵ
  double m_dCtrlLmt;//����ֵ������ʱ��С��ѹ����ѹʱ������
  int    m_nCtrlMode;

  double m_dCalc_qg;
  double m_dCalc_pwf;
  double m_dCalc_qg12;
  
  /*Normal_Gas_mb_Data(Normal_Gas_mb_Data data){
      //one time when created:
     m_dIPR_A = data.m_dIPR_A;
     m_dIPR_B = data.m_dIPR_B;
     m_dA2    = data.m_dA2;
     m_dP0    = data.m_dP0;
     m_dOGIP_SRV=data.m_dOGIP_SRV;
     m_dOGIP_Out= data.m_dOGIP_Out;
     m_dGpw    = data.m_dGpw;
     m_dGpw12  = data.m_dGpw12;
     m_nAreaFlag=data.m_nAreaFlag;
     m_nAdsorp_flag=data.m_nAdsorp_flag;
     m_nCompositeFlag = data.m_nCompositeFlag;
     //update every time:
     m_dCur_t  = data.m_dCur_t;
     m_dLast_t = data.m_dLast_t;
      //��ǰ���Ʒ�ʽ��
     m_dCtrlVal = data.m_dCtrlVal;
     m_dCtrlLmt = data.m_dCtrlLmt;
     m_nCtrlMode= data.m_nCtrlMode;

     m_dLastqg = data.m_dLastqg;
     m_dLastqg12=data.m_dLastqg12;

     //no need update,but can access after calling:
     m_dPavg_srv=data.m_dPavg_srv;
     m_dPavg_Out=data.m_dPavg_Out;

     //return every time call:
     m_dCalc_qg = data.m_dCalc_qg;
     m_dCalc_pwf= data.m_dCalc_pwf;
     m_dCalc_qg12=data.m_dCalc_qg12;
  }*/
};

//
class CPerformanceDREAnalysis;

//������������ƽ�����Ԥ��ģ���ࣺ
class GasMBRBase
{
public:
	//�������أ�
 GasMBRBase(CPerformanceDREAnalysis *parent, double p0,double t0,double phi,double sw,double cf,double cw=4E-4);
 //ҳ�����أ�
 GasMBRBase(CPerformanceDREAnalysis *parent, double p0,double t0,double phi,double sw,double cf,double rockmd,double vl,double pl,double cw=4E-4);
 ~GasMBRBase(void);


private:
 double   m_dSRV_p0;
 double   m_dT0;//�¶�oC
 
 double   m_dPhi;
 double   m_dSw;
 double   m_dCf;
 double   m_dCw;
 double   m_dRockmd;
 double   m_dVL;
 double   m_dPL;
 double   m_nRockType;

 CPerformanceDREAnalysis *m_parent;

 double*  m_pPressTab;
 double*  m_pPZBarTab;
 int      m_nmbTabPnts;

public:
	//������������ƽ�⶯̬Ԥ�⣺
    int composite_mbr_predict(		
		double ipr_a,double ipr_b, double srv_ogip,/*IPR����ϵ����SRV�������ڷ���*/
	    double out_ogip/*��������*/,double A2,/*˫������ϵ��(10^4m3/MPa)*/
	    int abnormal_flag/*�쳣��ѹ*/,
	    int adsorp_flag/*����������*/,
	    int composite_flag/*������*/,
     //��ƾ������ƶȣ�
     const std::vector<double> tpv,const std::vector<double> ctrlv,const std::vector<double> lmtv,const vector<int> modev,
     const int months,const int points/*Ԥ���������ܽ����*/,
     std::vector<double>& tv,std::vector<double>& calc_qgv,std::vector<double>& calc_pwfv,std::vector<double>& calc_qg12v,
     std::vector<double>& srv_pavgv,std::vector<double>& out_pavgv);

int composite_mbr_predict_new(double ipr_a,double ipr_b, double srv_ogip,/*IPR����ϵ����SRV�������ڷ���*/
		double out_ogip/*��������*/,double A2,/*˫������ϵ��(10^4m3/MPa)*/
		int abnormal_flag/*�쳣��ѹ*/,
		int adsorp_flag/*����������*/,
		int composite_flag/*������*/,
		//��ƾ������ƶȣ�
		const std::vector<double> tpv, //ÿ�������ƶȳ����������������ʷ���ݣ�����1
		const std::vector<double> stair_qgv,//�����ƶȿ���ֵ
		const std::vector<double> lmtv,//�����ƶ�Լ��ֵ
		const vector<int> pntv,//��������ƶ�Ԥ��������������ʷ���ݣ���1
		std::vector<double>& tv,
		std::vector<double>& calc_qgv,
		std::vector<double>& calc_pwfv,
		std::vector<double>& calc_qg12v,
		std::vector<double>& srv_pavgv,
		std::vector<double>& out_pavgv);

    //��ʷ��ϼ��㣺
     int composite_mbr_history(double ipr_a,double ipr_b, double ipr_p0,double srv_ogip,/*IPR����ϵ����SRV�������ڷ���*/
	    double out_ogip/*��������*/,double A2,/*˫������ϵ��(10^4m3/MPa)*/
	    int abnormal_flag,int adsorp_flag,int composite_flag,
        const std::vector<double> tpv,const std::vector<double> qgv,const double pwfL,std::vector<double>& calc_pwfv,
        std::vector<double>& calc_srv_pavg,std::vector<double>& calc_out_pavg);

protected:
    typedef double (*pFunPtr)(double,void*);

	//һԪ�������ԣ����̵�����⣬pfun����ʽ����ָ�룬
	//x0����ֵ������ֵ��
	//user_data:��װ�û�����������ɴ���pfun
	//����ֵ��0�����ɹ���-1�����ʧ��
	int Newton_Raphson(double& x0,void* user_data);

	//��������(ҳ�����أ�����ƽ��ģ�ͣ�����ģ�Ͳв
    double gas_mbr(double pavg,void* user_data);
   
	 //��������ƽ���ֵ��p--->p/z;   p--->p/z**
   //kg_flag���Ƿ���Ӧ������
   int initialize_mb_tab(int adsorp_flag,double min_p = 0.101, double max_p = 100);

    //���������ˣ�ȥ����adsorp_flag���ڲ�����ʱ�������adsorp_flag���¼���p/z��ֵ��:
    //����p/z��p/z**����ز�ѹ��:
    double convertPZ2P(double pz_val,double last_pavg = 20);

     //���ݵز�ѹ������p/Zֵ
     double convertP2PZ(double p);


   //���Բ�ֵ����
    int  interp1(double* xv, double* yv,double x, int n, double& y,int extrap_flag=0);

    int get_index(const double* tpv, int size, double cur_t);

    int min_(double* xv,double* yv, int n,double& x_pos,double& y_pos);
    int max_(double* xv,double* yv, int n,double& x_pos,double& y_pos);

    int check_x0_bounds(vector<MBR_Paramer_Info> x0);
};
}

#endif