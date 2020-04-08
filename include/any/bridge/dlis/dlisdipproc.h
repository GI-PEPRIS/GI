/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
 *
 * Copyright (C) 2015 XIUJIE SHENG
 *
 * This library isn't a free software, so you cann't take the source code without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will not harm your computer or ongoing 
 * business if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Resource Faculty
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYBRIDGE_DLISDIPPROC_H__
#define __ANYBRIDGE_DLISDIPPROC_H__

// refer to EXPORT and IMPORT
#include "..\anybridge.h"
#include "math.h"
#include "dlishelp.h"

#include "any/base/anystl.h"
#include "any/base/anyfilebasic.h"
#include "any/base/anydirbasic.h"
#include "any/base/anystringbasic.h"
using namespace AnyBase;
//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CDlisDipProc
	{
	public:
		struct Slf_CURVE
		{
			char  Name[16];
			char  AliasName[16];
			char  Unit[8];
			char  AliasUnit[16];
			WORD  RepCode;
			WORD  CodeLen;
			float MinValue;
			float MaxValue;
			float StartDepth;
			float EndDepth;
			float DepLevel;
			char  DepthUnit[8];
		};

		struct Slf_WAVE
		{
			char  Name[16];
			char  AliasName[16];
			char  Unit[8];
			char  AliasUnit[16];
			WORD  RepCode;
			WORD  CodeLen;
			float MinValue;
			float MaxValue;
			float StartDepth;
			float EndDepth;
			float DepLevel;
			char  DepthUnit[8];
			float StartTime;
			float TimeLevel;
			DWORD TimeSamples;
			char  TimeUnit[8];
		};
		struct HD_STRU
		{
			float Dep,Depo,Sdep,Edep,Rlev,StartDep,EndDep;
			char Param[16],Plot[16],buffer[500];
			HD_STRU():Dep(0),Depo(0),Sdep(0),Edep(0),Rlev(0),StartDep(0),EndDep(0)
			{
			}
		};
		struct OUTC_STRU
		{
			int Noo;
			char Name[8192];
			char Script[8192];
		};
		struct INC_STRU
		{
			int Noi;
			char Name[8192];
			char Script[8192];
		};
		struct CONC_STRU
		{
			int Noc;
			char Name[8192];
			char Script[8192];
		};
		struct CON_STRU
		{
			float yy[512];
		};
		struct INP_STRU
		{
			int InpPos[1024],InpLen[1024];
			float yy[10560];
		};
		struct OUTP_STRU
		{
			int OutPos[1024],OutLen[1024];
			float yy[10560];
		};
		struct ErrorInf{
			int ErrorNo;
			char ErrorStr[128];
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CDlisDipProc();

		/*!
		*
		**/
		~CDlisDipProc();
	public:
		
		/*!
		*
		**/
		void InitDipProc(int number);
		int Process4();
		int Process6();
		int Process8();
		void ClearData();
		void GetInCurveName(int index, char *Name);
		void GetOutCurveName(int index, char *Name);
		int OpenCurve(const char *Name);
		int OpenCurve(Slf_CURVE &curveinf);
		int OpenWave(const char *Name);
		int OpenWave(Slf_WAVE &waveinf);
		void CloseWave(int index);
		void CloseCurve(int index);
		void GetWaveInfo(int index, Slf_WAVE &waveinf);
		void GetCurveInfo( int index, Slf_CURVE &curveinf );
		void ReadCurve(int index, float depth, DWORD count, float* &buffer);
		void ReadCurve(int index, float depth, DWORD count, short* &buffer);
		void WriteCurve(int index, float depth, DWORD count, float* buffer, Slf_CURVE &curveinf);
		void WriteCurve(int index, float depth, DWORD count, short* buffer, Slf_CURVE &curveinf);
		void ReadWave(int index, float depth, DWORD count, float* &buffer);
		void ReadWave(int index, float depth, DWORD count, short* &buffer);
		void WriteWave(int index, float depth, DWORD count, float* buffer, Slf_WAVE &waveinf);
		void WriteWave(int index, float depth, DWORD count, short* buffer, Slf_WAVE &waveinf);

		/*!
		*
		**/
		void ReSampling(float *mr,int Row,int Col,float *aDep,float *tDep,int tnp);
		void ReSampling(short *mr,int Row,int Col,float *aDep,float *tDep,int tnp);
		bool LReSamplingTurn(float *aDep,float *aVal,int anp,float *tDep,int tnp,float rlev,int method);
		void ReOrder(float *mr,int Row,int Col,float *tDep);
		void ReOrder(short *mr,int Row,int Col,float *tDep);
		void qs(float*datx,float*mr,int left,int right,int Col);
		void qs(float*datx,short*mr,int left,int right,int Col);
		bool LReSampling(float *aDep,float *aVal,int anp,float *tDep,float *curve,int tnp,int method);
		void Linear(float *x,float *y,int n,float *a,float *b);
		void Parabola(float *x,float *y,int n,float *a,float *b,float *c);
		void Akima(float *x,float *y,int n,float *a,float *b,float *c,float *d);
		float GetXstep(float x2,float x1);
		void AccelerationCorrect(float *aDep,float *fCaz,float *fTim,int np,float *tDep,int method);
		void AccelMethod1(float *Dep,float *fCaz,float *fTim,int np,float *tDep);
		void AccelMethod2(float *aDep,float *fCaz,float *fTim,int np,float *tDep);
		void MXM(double m1[][3],double m2[][3],double m3[][3]);
		void MT(double m1[][3]);
		void RemoveBadPoint(float *mr,int num,int BtnPerPad);
		void RemoveBadPoint(short *mr,int num,int BtnPerPad);
		void DepthAlign(float *mr,int num,int pad,int ToolType);
		void EMEXCorrect(float *mr,float *pd6g,int pad,float *padg,float *gg01,int Row,int Col,float rm,int tooltype);
		void RemoveInvalidPoints(float *val,int Row,int Col);
		void RemoveInvalidPoints(short *val,int Row,int Col);
		void Normalize(float *mr,int Row,int Col);
		void Normalize(short *mr,int Row,int Col);
		void CaliLLS(float *mr,int Row,int Col,float caa,float cbb);
		void CreateCombDIP(float *wbufo,int num,int col,float *lbuf);
		void GetMinAndMax(float *mr,int nRow,int nCol,float *rmin,float *rmax);
		void AzmiuthCorrect(float *mr,int Row,int Col,float *p1az);
		void AzmiuthCorrect(short *mr,int Row,int Col,float *p1az,bool acindepend);
		void ResToGray(float *mr,int nRow,int nCol,float rmin,float rmax,short *out);
		void DynamicEhance(short *img,int Row,int Col,int wlen);
		void FmiAzmiuthCorrect(float *mr,int Row,int Col,float *p1az);
		void HorizMirror(float *mr,int Row,int Col);
		void StandOffCorrect(short *tt,short *ta,int Row,int Col,float vf,float vm,float vn);
		void mnth1(float *x,float *y,int np,double *c,int nc);
		double qc2(float *y,float xc,float yc,double *c);
		void mnth2(float *y,float xc,float yc,double *c,int nc);
		float Reflecta(float vm,float vn,float cosa);
		double qc30(float *x,float *y,float *z,int np,float xc,float yc,double *c,float vm,float vn);
		double qc3(float *x,float *y,float *z,int np,float xc,float yc,double *c,float vm,float vn);
		void mnth3(float *x,float *y,float *z,int np,float xc,float yc,double *c,int nc,float vm,float vn);
		void Normalize2(short *mr,int nRow,int nCol);
		void Ehance(short *img,int Row,int Col);
		bool Filter(float *in,int Row,int Col,int n,float *out);
		bool Filter(short *in,int Row,int Col,int n,short *out);
		double qc1(float *x,float *y,int np,double *c);

		/*!
		*
		**/
		void LFilter(float *y,int num,int glFilterWL,int glFilterMethod);
		void LFilter(float *y,int num,int glFilterWL);
		float Correl(float *x,float *y,int n);
		float gradfun(float *rc,int n);
		float CalcDet(float ma[][3]);
		void PlanRegres(int n,float *xi,float *yi,float *zi,float *coef);
		void RegularCurve(float *xy,int n);
		bool CORMN0(int nPad,float *inbuf,float stdep,float rlev,int num,float wl,float sl,float step,float rcutoff,float *outbuf);
		bool CORMN10(int nPad,float *inbuf,float *radbuf,float stdep,float rlev,int num,float wl,float sl,float step,float rcutoff,int ipbad,float *outbuf);
		bool CORMN1(int nPad,float *inbuf,float *radbuf,float stdep,float rlev,int num,float wl,float sl,float step,float rcutoff,int ipbad,float *outbuf);
		bool CORMN2(int nPad,float *inbuf,float *radbuf,float stdep,float rlev,int num,float wl,float sl,float step,float rcutoff,int ipbad,float *outbuf);
		void NormalizeVectorN(float *vN,float *vn);
		void V1XV2(float *v1,float *v2,float *v3);
		void MXV(float ma[][3],float *vect1,int n,float *vect2);
		void FDA2ENV(float *nfda,float rb,float dev,float hazi,float *nenv);
		void GetDipAzim0(float *vn,float *dip,float *azim);
		void GetDipAzim(float *vn,float *dip,float *azim);
		void GetDipAzim2(float *vn,float *dip,float *azim);
		void RemoveStrucDipSingle(float dang,float ddir,float sdang,float sddir,float *dangc,float *ddirc);
		void RemoveStrucDip(int num,float *dang,float *ddir,float *sdang,float *sddir,float *dangc,float *ddirc);
		bool cluster(float *x,int np,float dcutoff,float *dang,float *ddir);
		void DIPLOG0(float *Par,int nPad,float *inbuf,float stdep,float rlev,int num,float *rb,float *dev,float *p1az,float *hazi,float *outbuf);
		void DIPLOG1(float *Par,int nPad,float *inbuf,float stdep,float rlev,int num,float *rb,float *dev,float *p1az,float *hazi,float *sdang,float *sddir,float *outbuf);
		void DIPLOG2(float *Par,int nPad,float *inbuf,float stdep,float rlev,int num,float *rb,float *dev,float *p1az,float *hazi,float *sdang,float *sddir,float *outbuf);
		float ArithmeticAverage(float *x,int n);
		float BeselStdErr(float *x,int n);
		float ArithmeticAverageExcludeXi(float *x,int n,int i);
		float BeselStdErrExcludeXi(float *x,int n,int i);
		float Gan(float alfa,int n);
		void GrubbsCriterion(float *x,int n,float alfa,int *id);
		void PauTaCriterion(float *x,int n,int *id);
		void KSZCriterion(float *x,int n,int *id);
		float CalcAverageWithoutAbnorm(float *x,int n,int method);
		void  CalcStressDir(float *radbuf,float *p1az,int num,int nPad,int nstep,float *la,float *sb,float *dir,int *stloc,int *np);

	public:
		float m_CompWinLen;
		float m_SearchLen;
		float m_CompStep;
		BOOL m_LFilter;
		BOOL m_RemoveStrucDip;
		BOOL mSaveDDYes;
		BOOL m_OutStrucDipYes;
		int m_ipbad;
		BOOL mEAccCorrect;
	public:
		std::vector<string> inputnames;
		std::vector<string> inputremarks;
		std::vector<string> outputnames;
		std::vector<string> outputremarks;
		INC_STRU INC;
		OUTC_STRU OUTC;
		CONC_STRU CONC;
		CON_STRU CON;
		INP_STRU INP;
		OUTP_STRU OUTP;
		ErrorInf ERRORINF;
		HD_STRU HD;
	public:
		std::vector<CDlisHelp::Curve> m_curves;
		std::vector<float*> m_curvedatas;
		std::vector<CDlisHelp::Curve> m_outcurves;
		std::vector<float*> m_outcurvedatas;
	};
}
#endif
