#if !defined(AFX_PVTCALCULATE_H)
#define AFX_PVTCALCULATE_H
 
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum RSO_MethodType
{
	RSO_STANDING,
	RSO_VASQUEZ_BEGGS,
	RSO_GLASO,
};

enum BOSAT_MethodType
{
	BOSAT_DEFINITE,
	BOSAT_STANDING,
	BOSAT_VASQUEZ_BEGGS,
	BOSAT_GLASO,
	BOSAT_MARHOUN,
	BOSAT_AHMED,
};

enum BOUNSAT_MethodType
{
	BOUNSAT_DEFINITE,
	BOUNSAT_VASQUEZ_BEGGS,
	BOUNSAT_AHMED,
};

enum BOT_MethodType
{
	BOT_DEFINITE,
	BOT_GLASO,
	BOT_MARHOUN,
};

enum UODEGAS_MethodType
{
	UODEGAS_STANDING,
	UODEGAS_BEGGS_ROBINSON,
	UODEGAS_GLASO,
};

enum UOSAT_MethodType
{
	UOSAT_STANDING,
	UOSAT_BEGGS_ROBINSON,
	UOSAT_KHAN,
};

enum UOUNSAT_MethodType
{
	UOUNSAT_STANDING,
	UOUNSAT_VASQUEZ_BEGGS,
	UOUNSAT_KHAN,
};

enum ZG_MethodType
{
	ZG_HALL_YARBOUGH,
	ZG_DRANCHUK_PURVIS_ROBINSON,
	ZG_Dranchuk_Abu_Kassem,
	ZG_DEFAULT,
};

enum COUNSAT_MethodType
{
	COUNSAT_VASQUEZ_BEGGS,
	COUNSAT_AHMED,
};

enum CG_MethodType
{
	CG_HALL_YARBOUGH,
	CG_MATTAR_BRAR_AZIZ,
	CG_DEFAULT,
};

enum UG_MethodType
{
	UG_LEE_GONZALEA_EAKIN,
	UG_STANDING,
};

float Rsw_Mineralized( float fPress, float fTemp, float fS );
float Bw_Mineralized( float fPress, float fTemp, float fS );
float Cw_Saturated( float fPress, float fTemp, float fS, float fRsw );
float Uw_Mineralized( float fTemp );

float Rso_Calculate( float fPress, float fTemp, float frg, 
					 float fro,    float frgs,  int iMethod );
float BoSat_Calculate( float fPress, float fTemp,   float frg,  float fro,
                       float fRs,    float fDoTank, float frgs, int iBosatMethod );
float BoUnsat_Calculate( float fPress, float fPb,  float fTemp, 
						 float frg,    float fro,  float fRs, 
						 float fBosat, float fCoUnsat, int iBoUnsatMethod );
float Bot_Calculate( float fPress, float fTemp, float frg, 
					 float fro,    float fRs,   int iBotMethod );
float UoDegas_Calculate( float fTemp, float fro, int iUoDegasMethod );
float UoSat_Calculate( float fTemp, float frg,  float fro, 
					   float fRs,   float fUod, int iUosatMethod );
float UoUnsat_Calculate( float fPress, float fPb, float fUob, int iUoUnsatMethod );
float CoUnsat_Calculate( float fPress, float fTemp, float frgs, 
						 float fro,    float fRs,   int iCoUnsatMethod );


float Tpc_Car_Kobayshi_Burrows(float fTpc, float fCO2, float fH2S, float fN2);
float Ppc_Car_Kobayshi_Burrows(float fPpc, float fCO2, float fH2S, float fN2);


//天然气拟临界温度校正系数计算：郭绪强
//fCO2, fH2S：%
float CorrectionFactor_GuoXuQiang(float fCO2, float fH2S);
float Tpc_Guo_XuQiang(float fTpc, float fCO2, float fH2S);
float Ppc_Guo_xuqiang(float fTpcCorrected, float fPpc, float fCO2, float fH2S);

//天然气拟临界温度校正系数计算：WA
//fCO2, fH2S：%
float CorrectionFactor_Wichert_Aziz(float fCO2, float fH2S);
float Tpc_Wichert_Aziz(float fTpc, float fCO2, float fH2S);
float Ppc_Wichert_Aziz(float fTpcCorrected, float fPpc, float fCO2, float fH2S);

//天然气拟临界温度校正：WAJ
//fCO2, fH2S, fN2, fH2O：%
float Tpc_Wichert_Aziz_John(float fTpc, float fCO2, float fH2S, float fN2, float fH2O);
float Ppc_Wichert_Aziz_John(float fTpcUnCorrected, float fPpc, float fCO2, float fH2S, float fN2, float fH2O);

// 偏差因子
float Zg_Calculate( float fPseudoTc, float fPseudoPc,
				    float fTemp,     float fPress,     int iZgMethod );
// 压缩系数
float Cg_Calculate( float fPseudoTc, float fPseudoPc, float fTemp,     float fPress,
				    float fZ,        int   iCgMethod );
// 体积系数
float Bg_Calculate( float fTemp, float fPress, float fZ );

// 粘度系数
float Ug_Calculate( float fTc,  float fPc,  float fTemp, float fPress, float fZ,
	 			    float frg,  float fN2,  float fCO2,  float fH2S,   int iUgMethod);

void SetPMP_Pressure(float* pfPress, int iNum);
void CalGasWellPseudoPressure(  int    iNum,
							    float *pfPress,
								float *pfMp,
								float  fPseudoPc,
								float  fPseudoTc, 
								float  fResTemp,
								float  frg,    
								float  fN2,   
								float  fCO2, 
								float  fH2S, 
								int    iUgMethod,
								int    iZgMethod);

#endif //AFX_PVTCALCULATE_H
