/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYVIS_BASIN_MODEL_BURIAL_HISTORY_GRID_H__
#define __ANYVIS_BASIN_MODEL_BURIAL_HISTORY_GRID_H__

// refer to macro
#include "anyburialhistoryplot.h"
using namespace AnyVis;

namespace AnyVis
{
	class ANYVIS_CLASS CAnyBurialHistoryGridPlot : public CAnyBurialHistoryPlot
	{

	public:
		CAnyBurialHistoryGridPlot(CAnyView &curView);
		~CAnyBurialHistoryGridPlot();

	public:
		// 
		// hook
		//
		/*!
		*
		*/
		void Clone(const CAnyViewHook *prototype);

	private:

		// 
		//canvas
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

	public:
		 //�������ɶ���ѧģ������ ��{LLNLģ�ͣ��л���ģ�� }
		enum PetroGenStyle 
		{
			LLNL = 0,
			Organo,
		}; 

		//����һ���л�������ö����
		enum OrganoFaciesStyle
		{
			A = 1,
			B,
			C,
			DE,
			F,
		};

		/*!
		*
		**/
		double GetDefaultHIO(OrganoFaciesStyle id);
		
		
		/*!
		*
		**/
		void DoSimulation();

		 //�����������ͣ�������̬����õ�,�ֱ����������ࡢ�ͺ���
		enum HCType
		{
			OilGas = 0,
			Oil,
			Gas
		}; 

		//����״̬�������͵�ö�����ͣ��ֱ���{the Soave�CRedlich�CKwong EOS (SRK)��the Peng�CRobinson EOS (PR)}
		enum EOS
		{
			SRK = 0,
			PR
		};

	private:

		
		//������ڵ���ֵ�����   properties of pseudo-components  ��ֵ�ͼ���
		struct Properties 
		{    
			int NGroupCom; //������е������  =5
			double *ComMolFra; //��������еĸ���ֵ�Ħ������
			double *MWi;       //���Ħ������  kg/kgmol
			double *Tci,*Pci; //����ٽ��¶Ⱥ�ѹ��   K��MPa
			double *Omegai; //the dimensionless acentric factor,����ֵ�
			double *Zci,*Vci;
			//double **kij; //binary interaction parameter ��Ԫ�໥���ò���
			double MW,Tc,Pc,Omega,Zc,Vc; //����ֵ��ܵ�����
			double PcMolAveraging; //����Ħ��ƽ��ֵ�õ���ֵ������û�в��ã�ֻ�Ǽ������ڱȽϷ���
			double z; //mole fraction of the group in the mixture    ��������ڻ�����е�Ħ������
			
			Properties()
			{
				Init();
			}

			void Init()
			{
				NGroupCom = 5;

				ComMolFra = 0;
				MWi = 0;
				Tci = 0;
				Pci = 0;				
				Omegai = 0;				
				Zci = 0;
				Vci = 0;

				MW = 0.;
				Tc = 0.;
				Pc = 0.;
				Omega = 0.;
				Zc = 0.;
				Vc = 0.; 
				PcMolAveraging = 0.; 
				z = 0.;
			}

			void Release()
			{
				DoRelease(ComMolFra);
				DoRelease(MWi);
				DoRelease(Tci);
				DoRelease(Pci);
				DoRelease(Omegai);
				DoRelease(Zci);
				DoRelease(Vci);
			}


			void DoRelease(double *&val)
			{
				if (val)
				{
					delete val;
				}
				val = 0;
			}
			
			
			void ReadinPars(int aNGroupCom, double *aComMolFra,double *aMWi,double *aTci,double *aPci,double *aOmegai,double *aZci,double *aVci)// ,double **akij
			{
				Release();

				double R=0.008314; //���峣��
				NGroupCom=aNGroupCom;
				ComMolFra=new double[NGroupCom];
				MWi=new double[NGroupCom];
				Tci=new double[NGroupCom];
				Pci=new double[NGroupCom];
				Omegai=new double[NGroupCom];
				Zci=new double[NGroupCom];
				Vci=new double[NGroupCom];
				// kij=new double*[NGroupCom];
				// for(int i=0;i<NGroupCom;i++) kij[i]=new double[NGroupCom];
				z=0;
				for(int i=0;i<NGroupCom;i++)
				{ComMolFra[i]=aComMolFra[i];z+=ComMolFra[i]; MWi[i]=aMWi[i];Tci[i]=aTci[i];Pci[i]=aPci[i]; Omegai[i]=aOmegai[i];Zci[i]=aZci[i];Vci[i]=aVci[i];} // for(int j=0;j<NGroupCom;j++)kij[i][j]=akij[i][j];
				for(int i=0;i<NGroupCom;i++) ComMolFra[i]=ComMolFra[i]/z;
				MW=0;Tc=0;PcMolAveraging=0;Omega=0;Zc=0;Vc=0;
				for(int i=0;i<NGroupCom;i++)   //molar averaging ,�������PC
				{ MW+=MWi[i]*ComMolFra[i];Tc+=Tci[i]*ComMolFra[i]; Pc+=Pci[i]*ComMolFra[i]; Omega+=Omegai[i]*ComMolFra[i];Zc+=Zci[i]*ComMolFra[i];Vc+=Vci[i]*ComMolFra[i];}
				// Pc=Zc*R*Tc/Vc; //����poling  2000 The properties of gases and liquids ��(5-3.2)    ����Pc���ǲ�����Ħ��ƽ��
			}
		};

		static void GetGroupkij(int NCom,double **kij,double **GasOilkij,Properties *aProperties)
		{ //�������ּ��Binary interaction parameters  Danesh,1998, p309 9.16
			for(int k=0;k<NCom;k++) for(int q=0;q<NCom;q++)kij[k][q]=0;
			for(int k=0;k<NCom;k++) for(int q=0;q<NCom;q++)
			{
				if(k!=q)
					for(int i=0;i<aProperties[k].NGroupCom;i++) for(int j=0;j<aProperties[q].NGroupCom;j++)
					{
						kij[k][q]+=aProperties[k].ComMolFra[i]*aProperties[q].ComMolFra[j]*GasOilkij[i][j]/(aProperties[k].z*aProperties[q].z);
					}
			}
		}

		static double ReturnMin(double x1,double x2,double x3) //����
		{ 
			double temp = 0.; 
			if(x1<x2)
				temp=x1;
			else 
				temp=x2; 
			if(temp>x3) temp=x3; 
			
			return temp;
		}
		
		static double ReturnMax(double x1,double x2,double x3) //����
		{ 
			double temp = 0.;
			if(x1>x2)
				temp=x1;
			else 
				temp=x2; 
			if(temp<x3)
				temp=x3;
			
			return temp; 
		}

		//һԪ���η��̵Ľ�
		//�ֱ�Ϊ���̵������⣬Case����״̬
		struct SolutionOfCE  
		{
			double x1;
			double x2;
			double x3;
			int Case;

			SolutionOfCE()
			{
				x1 = 0.;
				x2 = 0.;
				x3 = 0.;
				Case = 1;
			}
		};
		
		static SolutionOfCE CubicEquation(double a,double b,double c,double d)
		{  //
			//SolutionOfCubicEquation
			//���� ax^3+bx^2+cx+d=0; ʢ��ʽ���
			SolutionOfCE aSCE;
			//double a=15.,b=-200.,c=3.,d=4.;
			double A=b*b-3.*a*c;
			double B=b*c-9.*a*d;
			double C=c*c-3.*b*d;
			double Delta=B*B-4.*A*C;
			double x1,x2,x3; //���̽�
			if(A==0&&B==0)  // "A==0&&B==0,��һ�����ظ�"
			{aSCE.x1=-b/3./a;aSCE.x2=aSCE.x1;aSCE.x3=aSCE.x2; aSCE.Case=1;}
			else
			{
				if(Delta>0)
				{ // Delta>0����һ��ʵ������������������,
					double Y1=A*b+3.*a*((-B+sqrt(B*B-4.*A*C))/2.);
					double Y2=A*b+3.*a*((-B-sqrt(B*B-4.*A*C))/2.);
					double temp1,temp2;
					if(Y1<0) temp1=-pow(fabs(Y1),1./3.);
					else temp1=pow(fabs(Y1),1./3.);
					if(Y2<0) temp2=-pow(fabs(Y2),1./3.);
					else temp2=pow(fabs(Y2),1./3.);
					aSCE.x1=(-b-(temp1+temp2))/(3.*a);
					aSCE.Case=2;
				}
				if(Delta==0)
				{ // "Delta==0��������ʵ���������������Ƕ��ظ�"
					double K=B/A;
					aSCE.x1=-b/a+K;
					aSCE.x2=-K/2.;
					aSCE.x3=aSCE.x2;
					aSCE.Case=3;
				}
				if(Delta<0)
				{ // "Delta<0����������ͬʵ��"
					double T=(2.*A*b-3.*a*B)/2./A/sqrt(A);
					double Theta=acos(T);
					aSCE.x1=(-b-2.*sqrt(A)*cos(Theta/3.))/(3.*a);
					aSCE.x2=(-b+sqrt(A)*(cos(Theta/3.)+sqrt(3.)*sin(Theta/3.)))/(3.*a);
					aSCE.x3=(-b+sqrt(A)*(cos(Theta/3.)-sqrt(3.)*sin(Theta/3.)))/(3.*a);
					aSCE.Case=4;
				}
			}
			return aSCE;
		}
		double GetVOfRRE(int NCom,double *z,double *K, double aPoint) //���Rachford-Rice����ֵ Danesh 1998, (5.6)P169
		{
			double tempV=0;
			for(int i=0;i<NCom;i++)
				tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*aPoint);
			return tempV;
		}
		void GetInitKi(int NCom,double *K, double *Pci,double Pm, double *Omegai,double *Tci,double Tm)
		{ //���ÿһ��ֵĳ�ʼ��ƽ���Ki��Danesh 1998, (3.66)P122
			for(int i=0;i<NCom;i++) K[i]=Pci[i]/Pm*exp(5.37*(1.+Omegai[i])*(1.-Tci[i]/Tm));
		}

		void GetParasOfComsInEOS(int NCom,double *xi,double **kij,double *Tci,double *pci, double Tm,double Pm,double *Omegai,double R,double &a,double &b,double *aci,double *bi,double *mi,double *Alphai, double *ai,double *Ai,double *Bi,EOS aEOS) //���״̬�����и���ֵĲ���
		{

			b=0; a=0;  //����ֵΪ0
			for(int i=0;i<NCom;i++)
			{
				switch(aEOS)
				{
				case SRK:
					aci[i]=0.42747*R*R*Tci[i]*Tci[i]/pci[i];      //Danish,1998 P140  4.22
					bi[i]=0.08664*R*Tci[i]/pci[i];            //Danish,1998 P140  4.22
					mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
					Alphai[i]=(1.+mi[i]*(1.-sqrt(Tm/Tci[i])))*(1.+mi[i]*(1.-sqrt(Tm/Tci[i]))); //Danish,1998 P140  4.23
					ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
					Ai[i]=ai[i]*Pm/(R*Tm*R*Tm);          //Danish,1998 P132  4.7  ��Ȼ�����ˣ�����ʱû���õ�
					Bi[i]=bi[i]*Pm/(R*Tm);              //Danish,1998 P132  4.8   ��Ȼ�����ˣ�����ʱû���õ�
					break;
				case PR:
					aci[i]=0.457235*R*R*Tci[i]*Tci[i]/pci[i];    //Danish,1998 P141  4.27
					bi[i]=0.077796*R*Tci[i]/pci[i];          //Danish,1998 P141  4.27
					mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
					Alphai[i]=(1.+mi[i]*(1.-sqrt(Tm/Tci[i])))*(1.+mi[i]*(1.-sqrt(Tm/Tci[i]))); //Danish,1998 P140  4.23
					ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
					Ai[i]=ai[i]*Pm/(R*Tm*R*Tm);          //Danish,1998 P132  4.7     ��Ȼ�����ˣ�����ʱû���õ�
					Bi[i]=bi[i]*Pm/(R*Tm);              //Danish,1998 P132  4.8      ��Ȼ�����ˣ�����ʱû���õ�
					break;
				};
			}
			for(int i=0;i<NCom;i++)
			{    //��Ϲ���  Mixture parameters
				b+=xi[i]*bi[i];   //Danish,1998 P155  4.74
				for(int j=0;j<NCom;j++)
					a+=xi[i]*xi[j]*sqrt(ai[i]*ai[j])*(1.-kij[i][j]);   //Danish,1998 P155  4.78
			}
		}



		void GetaEOSParas(double &aa,double &bb,double &cc,double &dd,double A,double B,EOS aEOS)
		{
			switch(aEOS)
			{
			case SRK:
				aa=1.; bb=-1.;cc=A-B-B*B;dd=-A*B;
				break;
			case PR:
				aa=1.; bb=-(1.-B);cc=A-2.*B-3.*B*B;dd=-A*B+B*B+B*B*B;
				break;
			};
		}
		void GetFaii(int NCom,EOS aEOS,double *Faii,double *ai,double *bi,double *x,double a,double b,double **kij,double A,double B,double Z)   //�����ݶ�ϵ�� Danish,1998 p157 E4.5
		{
			//GetParasOfComsInEOS();
			double Delta1,Delta2;
			double lnFaii;
			switch(aEOS)
			{
			case SRK:
				Delta1=1.;
				Delta2=0.;
				break;
			case PR:
				Delta1=1+sqrt(2.);
				Delta2=1-sqrt(2.);
				break;
			};
			double tempXigemaxjaij;
			double aij;
			for(int i=0;i<NCom;i++)
			{
				tempXigemaxjaij=0;
				for(int j=0;j<NCom;j++)
				{
					aij=sqrt(ai[i]*ai[j])*(1-kij[i][j]); // Danish,1998 p155 4.77
					tempXigemaxjaij+=x[j]*aij;
				}
				lnFaii=bi[i]/b*(Z-1.)-log(Z-B)-A/(B*(Delta2-Delta1))*(2*tempXigemaxjaij/a-bi[i]/b)*log((Z+Delta2*B)/(Z+Delta1*B));
				Faii[i]=exp(lnFaii);
			}
		}

		void Getfi_K(int NCom,double *fiL,double *fiV,double *FaiiL,double *FaiiV,double *K,double *x,double *y,double Pm)
		{    //���������̬��ֵ��ݶ��Լ���ֵ�ƽ���
			for(int i=0;i<NCom;i++)  { fiL[i]=FaiiL[i]*x[i]*Pm;  fiV[i]=FaiiV[i]*y[i]*Pm; K[i]=FaiiL[i]/FaiiV[i];}
		}
		void GetErrorValue_fiLfiV(double &ErrorValue_fiLfiV,int NCom,double *fiL,double *fiV)
		{     //Danish,1998  P174
			ErrorValue_fiLfiV=0;
			for(int i=0;i<NCom;i++) ErrorValue_fiLfiV+=(1.-fiL[i]/fiV[i])*(1.-fiL[i]/fiV[i]);
		}
		void BubblePressureAdjusted(int NCom,double &Pm,double *x,double *K)//����ѹ��ʹ��ӽ��ݵ�ѹ�� Danesh 1998,P174  (E5.2')
		{
			double tempSum=0;
			for(int i=0;i<NCom;i++) tempSum+=x[i]*K[i];
			Pm=Pm*tempSum;
		}
		void DewPressureAdjusted(int NCom,double &Pm,double *y,double *K)//����ѹ��ʹ��ӽ�¶��ѹ�� Danesh 1998,P174  (E5.2')
		{
			double tempSum=0;
			for(int i=0;i<NCom;i++) tempSum+=y[i]/K[i];
			Pm=Pm*tempSum;
		}
		void GetvLvV(double &vL,double &vV,double R,double Tm,double ZL,double ZV,double Pm ) //���������Ħ�����  Danish,1998 P40 2.5
		{
			vL=R*Tm*ZL/Pm;
			vV=R*Tm*ZV/Pm;
		}
		void GetMWLMWV(int NCom,double &MWL,double &MWV,double *MW,double *x,double *y) //�������������Ħ������
		{
			MWL=0;MWV=0;
			for(int i=0;i<NCom;i++)
			{
				MWL+=x[i]*MW[i];
				MWV+=y[i]*MW[i];
			}
		}
		void GetLVDensity(double &OilDensity, double &GasDensity, double vL,double vV,double MWL,double MWV) //����͡�������ܶ�
		{
			OilDensity=MWL/vL; GasDensity=MWV/vV;
		}
		void GetpTcpPc(int NCom,double *xi,double **kij,double *Tci,double *pci, double *Omegai,double R,double &a,double &b,double *aci,double *bi,double *mi,double *Alphai, double *ai,double &pTc,double &pPc,EOS aEOS/*,TMemo *Memo1*/)
		{  //���ڼ����ٽ��¶Ⱥ�ѹ��,ͨ����������ã� --���ڻ����
			double pTctemp=pTc; //
			double wc; //ǰ�����ε������¶Ȳ����ֵ
			double wcx=0.01; //�ж���������������ֵ
			int n=0;
			do
			{
				n++;
				b=0; a=0;  //����ֵΪ0
				for(int i=0;i<NCom;i++)
				{
					switch(aEOS)
					{
					case SRK:
						aci[i]=0.42747*R*R*Tci[i]*Tci[i]/pci[i];      //Danish,1998 P140  4.22
						bi[i]=0.08664*R*Tci[i]/pci[i];            //Danish,1998 P140  4.22
						mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
						Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
						ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
						break;
					case PR:
						aci[i]=0.457235*R*R*Tci[i]*Tci[i]/pci[i];    //Danish,1998 P141  4.27
						bi[i]=0.077796*R*Tci[i]/pci[i];          //Danish,1998 P141  4.27
						mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
						Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
						ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
						break;
					};
				}
				for(int i=0;i<NCom;i++)
				{    //��Ϲ���  Mixture parameters
					b+=xi[i]*bi[i];   //Danish,1998 P155  4.74
					for(int j=0;j<NCom;j++)
						a+=xi[i]*xi[j]*sqrt(ai[i]*ai[j])*(1.-kij[i][j]);   //Danish,1998 P155  4.78
				}
				switch(aEOS)
				{
				case SRK:
					pTc=0.08664/0.42747*a/b/R;   // Danish 1998 P140 4.22
					pPc=0.08664*R*pTc/b;
					break;
				case PR:
					pTc=0.17014446*a/R/b; // Danish 1998 P179 E5.4
					pPc=0.077796*R*pTc/b;
					break;
				};
				wc=fabs(pTc-pTctemp);
				//Memo1->Lines->Add("�ٽ��¶�pTctemp="+FloatToStr(pTctemp));
				//Memo1->Lines->Add("�ٽ��¶�pTc="+FloatToStr(pTc));
				//if(n==100) ShowMessage("ͣ");
				pTctemp=pTc;
			}while(wc>wcx);
		}
		double NewtonIterationFornv(int NCom,double *z,double *K, double aPoint) //��ţ�ٵ�������nv
		{
			double tempV; //����ֵ
			double tempVD;  //����ֵ
			double nv01,nv02; //����ֵ
			double wc;
			nv01=aPoint;
			do
			{
				tempV=0;
				tempVD=0;
				for(int i=0;i<NCom;i++)
					tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*nv01);    //���Rachford-Rice����ֵ Danesh 1998, (5.6)P169
				//ShowMessage("1.+(KK[0]-1.0)*nv01="+FloatToStr(1.+(K[0]-1.0)*nv01));
				//ShowMessage("1.+(KK[1]-1.0)*nv01="+FloatToStr(1.+(K[1]-1.0)*nv01));

				for(int i=0;i<NCom;i++)
					tempVD+=-z[i]*(K[i]-1.)*(K[i]-1.)/pow(1.+(K[i]-1.0)*nv01,2.);  //���Rachford-Rice���̵���ֵ
				nv02=nv01-tempV/tempVD;
				wc=fabs(nv02-nv01);
				nv01=nv02;
			}while(wc>1.0e-10);
			return nv02;
		}
		


		double rrand()
		{  // ����0-1�������
			double l;
			l=(std::rand()%1000)/1000.0;
			return(l);
		}

		double GetRand()         //����-1��+1������������������
		{
			return 2.0*std::rand()/double(RAND_MAX)-1.0;
		} /**/
		
		double GetRand0_1() {return std::rand()/double(RAND_MAX);}  //����0-1��������
		
		double RandomRange( double b)
		{ //����-b,b��������
			return GetRand()*b;
		}
				
		struct POS
		{
			int x,y; //��¼��ά�����ͷ��ά

			POS()
			{
				x = 0;
				y = 0;
			}
		};

		struct Poro_Perm  //��¼��϶�Ⱥ���͸�ʹ�ϵ�����ݶ�
		{
			std::vector<double> Poro;
			std::vector<double> Perm;
			
			Poro_Perm()
			{
				Poro.resize(3);
				Perm.resize(3);
			}

			void Release()
			{
				Poro.clear();
				Perm.clear();
			}
		};

		struct ParaOfEasyRo
		{
			//����ΪEasyRoģ�Ͳ��� ,Ҳ�����ڶ���BasinRoģ�Ͳ������������ƵĲ���
			int NN;//ƽ�з�Ӧ����� ���������ѧ����ϵ���ͻ��ͨ������������NN���Ը��ݱ���е��������� ��
			double *f;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			double *E;//��ܣ�Activation Energy����Kcal/mole��
			double A;//Ƶ������ S^-1
			double Roo;//EasyRoģ���ڵر��ʼʱ�̵�Roֵ  Roo=exp(-1.6);
			double f0;

			ParaOfEasyRo()
			{
				NN = 0;
				f = 0;
				E = 0;
				f0 = 0.;
				A = 0.;
				Roo = 0.;
			}

			void Release()
			{
				if (f)
				{
					delete f;
				}
				f = 0;

				if (E)
				{
					delete E;
				}
				E = 0;
			} 

			void Construct(int NNN,double *ff, double *EE,double AA,double Roooo)
			{   
				Release();
				
				//�Խṹ�帳ֵ
				NN=NNN;
				f=new double[NN];
				E=new double[NN];
				f0=0;
				for(int i=0;i<NNN;i++)
				{
					f[i]=ff[i];
					E[i]=EE[i];
					f0+=f[i];
				}
				A=AA;
				Roo=Roooo;
			}
			
			void CopyFrom(ParaOfEasyRo *aPara)
			{   
				if (!aPara)
				{
					return;
				}

				Release();
				
				//����һ���ṹ�п���һ�ݲ���
				NN=aPara->NN;
				f=new double[NN];
				E=new double[NN];
				for(int i=0;i<NN;i++)
				{
					f[i]=aPara->f[i];
					E[i]=aPara->E[i];
				}
				A=aPara->A;
				Roo=aPara->Roo ;
				f0=aPara->f0;
			}
		};
		
		struct ParaOfSimpleRo
		{
			//����ΪEasyRoģ�Ͳ��� ,Ҳ�����ڶ���BasinRoģ�Ͳ������������ƵĲ���
			double f0;//�ǵ�һ�Ļ�ѧ����ϵ����Stoichiometric Factor������ʼʱ���൱��EasyRo�еĳ�ʼ��fi֮��
			double f;//ͬ�ϣ�ֻ�����ڴ��뺯���Ĺ�������ֵ��仯
			double aerf,beita; //Simple Ro�����л��E��lnRo��Ĺ�ϵ����  (E=��lnRo+��)
			double A;//Ƶ������ S^-1
			double Roo;//Ro=exp(-1.6); //�ز��ڳ�ʼʱ�̵�Roֵ��SimpleRoʹ��EasyRoͬ����ֵ
			
			ParaOfSimpleRo()
			{
				f0 = 0.;
				f = 0.;
				aerf = 0.;
				beita = 0.;
				A = 0.;
				Roo = 0.;
			}

			void Construct(double f0SimpleRo,double fSimpleRo, double aerfSimpleRo,double beitaSimpleRo,double ASimpleRo,double RooSimpleRo)
			{   //�Խṹ�帳ֵ
				f0=f0SimpleRo; f=fSimpleRo; aerf=aerfSimpleRo;beita=beitaSimpleRo; A=ASimpleRo; Roo=RooSimpleRo;
			}
			
			void CopyFrom(ParaOfSimpleRo *aPara)
			{   
				if (!aPara)
				{
					return;
				}
				
				//����һ���ṹ�п���һ�ݲ���
				f0=aPara->f0;
				f=aPara->f;
				aerf=aPara->aerf;
				beita=aPara->beita;
				A= aPara->A;
				Roo=aPara->Roo ;
			}
		};
		
		struct DR
		{ //���Ҹ������ʽṹ�� �����ڸ��Ҹ���������Ro��ϵ
		  int NKerogen; //���Ҹ�������
		  double *Ratio; //���ָ��Ҹ���ռ�ı���
		  int NI; //��Ӧ��I�͸��Ҹ���������ֵ�ĸ���
		  int NIIA; //��Ӧ��IIA�͸��Ҹ���������ֵ�ĸ���
		  int NIIB; //��Ӧ��IIB�͸��Ҹ���������ֵ�ĸ���
		  int NIII; //��Ӧ��III�͸��Ҹ���������ֵ�ĸ���
		  int NGDR; //��Ӧ�������⺬������ֵ�ĸ���
		  double * DRI;  //DegradationRate Of Type I Kerogen
		  double *RoI;  //��Ӧ��DegradationRate Of Type I Kerogen��Ro
		  double * DRIIA;  //DegradationRate Of Type IIA Kerogen
		  double *RoIIA;  //��Ӧ��DegradationRate Of Type IIA Kerogen��Ro
		  double * DRIIB;  //DegradationRate Of Type IIB Kerogen
		  double *RoIIB;  //��Ӧ��DegradationRate Of Type IIB Kerogen��Ro
		  double * DRIII;  //DegradationRate Of Type III Kerogen
		  double *RoIII;  //��Ӧ��DegradationRate Of Type III Kerogen��Ro
		  double *GDR; //�����⺬��
		  double *RoGDR; //�����⺬����Ӧ��Ro%ֵ
		  double COG;//Ϊ����ת���ʣ�һ��ȡֵ0.96m3/kg ����ʱû�����ת���ʣ�����Ҳ��kg��ʾ
		  

		  DR()
		  {
			  Init();
		  }

		  void Init()
		  {
			NKerogen = 0; //���Ҹ�������
			Ratio = 0; //���ָ��Ҹ���ռ�ı���

			NI = 0; //��Ӧ��I�͸��Ҹ���������ֵ�ĸ���
			NIIA = 0; //��Ӧ��IIA�͸��Ҹ���������ֵ�ĸ���
			NIIB = 0; //��Ӧ��IIB�͸��Ҹ���������ֵ�ĸ���
			NIII = 0; //��Ӧ��III�͸��Ҹ���������ֵ�ĸ���
			NGDR = 0; //��Ӧ�������⺬������ֵ�ĸ���

			DRI = 0;  //DegradationRate Of Type I Kerogen
			RoI = 0;  //��Ӧ��DegradationRate Of Type I Kerogen��Ro

			DRIIA = 0;  //DegradationRate Of Type IIA Kerogen
			RoIIA = 0;  //��Ӧ��DegradationRate Of Type IIA Kerogen��Ro

			DRIIB = 0;  //DegradationRate Of Type IIB Kerogen
			RoIIB = 0;  //��Ӧ��DegradationRate Of Type IIB Kerogen��Ro

			DRIII = 0;  //DegradationRate Of Type III Kerogen
			RoIII = 0;  //��Ӧ��DegradationRate Of Type III Kerogen��Ro

			GDR = 0; //�����⺬��
			RoGDR = 0; //�����⺬����Ӧ��Ro%ֵ

			COG = 0; //Ϊ����ת���ʣ�һ��ȡֵ0.96m3/kg ����ʱû�����ת���ʣ�����Ҳ��kg��ʾ

			/////////////////////////////////////////output////////////////////////////////
			for (int idx = RO_TTI; idx <= RO_Basin; idx++)
			{
				//���ֲ�ͬ���͵ĸ��Ҹ���λ������kg)�л�̼������
				HCFromDRI[idx] = 0;
				HCFromDRIIA[idx] = 0;
				HCFromDRIIB[idx] = 0;
				HCFromDRIII[idx] = 0; 

				//ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
				InitTOCI[idx] = 0;
				InitTOCIIA[idx] = 0;
				InitTOCIIB[idx] = 0;
				InitTOCIII[idx] = 0; 

				//����ֵ�ԭʼ�л�̼�ڵز�ε�ԭʼ�л�̼����kg
				MassInitTOCI[idx] = 0;
				MassInitTOCIIA[idx] = 0;
				MassInitTOCIIB[idx] = 0;
				MassInitTOCIII[idx] = 0; 

				//��Ȼ������,�൱���ĵ��е�Pg
				GasRatio[idx] = 0;

				//ÿ��λ��kg��ԭʼ�л�̼������������
				HCGIPerUnitInitTOC_I[idx] = 0;
				HCGIPerUnitInitTOC_IIA[idx] = 0;
				HCGIPerUnitInitTOC_IIB[idx] = 0;
				HCGIPerUnitInitTOC_III[idx] = 0; 

				//ÿ��λ��kg��ԭʼ�л�̼������������
				OGIPerUnitInitTOC_I[idx] = 0;
				OGIPerUnitInitTOC_IIA[idx] = 0;
				OGIPerUnitInitTOC_IIB[idx] = 0;
				OGIPerUnitInitTOC_III[idx] = 0; 

				//ÿ��λ��kg��ԭʼ�л�̼������������
				GGIPerUnitInitTOC_I[idx] = 0;
				GGIPerUnitInitTOC_IIA[idx] = 0;
				GGIPerUnitInitTOC_IIB[idx] = 0;
				GGIPerUnitInitTOC_III[idx] = 0; 
			}
		  }


		  void Release()
		  {
			//
			if (Ratio)
			{
				delete Ratio;
			}
			Ratio = 0;

			//
			if (DRI)
			{
				delete DRI;
			}
			DRI = 0;

			if (RoI)
			{
				delete RoI;
			}
			RoI = 0;

			//
			if (DRIIA)
			{
				delete DRIIA;
			}
			DRIIA = 0;

			if (RoIIA)
			{
				delete RoIIA;
			}
			RoIIA = 0;

			//
			if (DRIIB)
			{
				delete DRIIB;
			}
			DRIIB = 0;

			if (RoIIB)
			{
				delete RoIIB;
			}
			RoIIB = 0;

			//
			if (DRIII)
			{
				delete DRIII;
			}
			DRIII = 0;

			if (RoIII)
			{
				delete RoIII;
			}
			RoIII = 0;

			//
			if (GDR)
			{
				delete GDR;
			}
			GDR = 0;

			if (RoGDR)
			{
				delete RoGDR;
			}
			RoGDR = 0;
		  }

		  void Construct(int aNKerogen,double *aRatio,int aNI, int aNIIA, int aNIIB,int aNIII, int aNGDR, double *aDRI,double *aRoI,double *aDRIIA, double *aRoIIA,double *aDRIIB, double *aRoIIB,double *aDRIII,double *aRoIII,double *aGDR, double *aRoGDR,double aCOG)
		  {
			Release();
			Init();

			NKerogen=aNKerogen;NI=aNI;NIIA=aNIIA;NIIB=aNIIB;NIII=aNIII;NGDR=aNGDR;
			Ratio=new double[NKerogen]; DRI=new double[NI];RoI=new double[NI];DRIIA=new double[NIIA];RoIIA=new double[NIIA];
			DRIIB=new double[NIIB]; RoIIB=new double[NIIB]; DRIII=new double[NIII]; RoIII=new double[NIII]; GDR=new double[NGDR];RoGDR=new double[NGDR];
			for(int i=0;i<NKerogen;i++) Ratio[i]=aRatio[i];
			for(int i=0;i<NI;i++) {DRI[i]=aDRI[i];RoI[i]=aRoI[i];}
			for(int i=0;i<NIIA;i++) {DRIIA[i]=aDRIIA[i];RoIIA[i]=aRoIIA[i];}
			for(int i=0;i<NIIB;i++) {DRIIB[i]=aDRIIB[i];RoIIB[i]=aRoIIB[i];}
			for(int i=0;i<NIII;i++) {DRIII[i]=aDRIII[i];RoIII[i]=aRoIII[i];}
			for(int i=0;i<NGDR;i++) {GDR[i]=aGDR[i];RoGDR[i]=aRoGDR[i];}
			COG=aCOG;
		  }

		  void CopyFrom(DR *aaDR)
		  {
			if (!aaDR)
			{
				return;
			}

			Release();
			Init();

			NKerogen=aaDR->NKerogen;NI=aaDR->NI;NIIA=aaDR->NIIA;NIIB=aaDR->NIIB;NIII=aaDR->NIII;NGDR=aaDR->NGDR;
			Ratio=new double[NKerogen]; DRI=new double[NI];RoI=new double[NI];DRIIA=new double[NIIA];RoIIA=new double[NIIA];
			DRIIB=new double[NIIB]; RoIIB=new double[NIIB]; DRIII=new double[NIII]; RoIII=new double[NIII]; GDR=new double[NGDR];RoGDR=new double[NGDR];
			for(int i=0;i<NKerogen;i++) Ratio[i]=aaDR->Ratio[i];
			for(int i=0;i<NI;i++) {DRI[i]=aaDR->DRI[i];RoI[i]=aaDR->RoI[i];}
			for(int i=0;i<NIIA;i++) {DRIIA[i]=aaDR->DRIIA[i];RoIIA[i]=aaDR->RoIIA[i];}
			for(int i=0;i<NIIB;i++) {DRIIB[i]=aaDR->DRIIB[i];RoIIB[i]=aaDR->RoIIB[i];}
			for(int i=0;i<NIII;i++) {DRIII[i]=aaDR->DRIII[i];RoIII[i]=aaDR->RoIII[i];}
			for(int i=0;i<NGDR;i++) {GDR[i]=aaDR->GDR[i];RoGDR[i]=aaDR->RoGDR[i];}
			COG=aaDR->COG;
		  }
		  double HCFromDRI[4],HCFromDRIIA[4], HCFromDRIIB[4], HCFromDRIII[4]; //���ֲ�ͬ���͵ĸ��Ҹ���λ������kg)�л�̼������
		  double InitTOCI[4],InitTOCIIA[4],InitTOCIIB[4],InitTOCIII[4]; //ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
		  double MassInitTOCI[4],MassInitTOCIIA[4],MassInitTOCIIB[4],MassInitTOCIII[4]; //����ֵ�ԭʼ�л�̼�ڵز�ε�ԭʼ�л�̼����kg
		  double GasRatio[4]; //��Ȼ������,�൱���ĵ��е�Pg
		  double HCGIPerUnitInitTOC_I[4], HCGIPerUnitInitTOC_IIA[4],HCGIPerUnitInitTOC_IIB[4],HCGIPerUnitInitTOC_III[4]; //ÿ��λ��kg��ԭʼ�л�̼������������
		  double OGIPerUnitInitTOC_I[4],OGIPerUnitInitTOC_IIA[4],OGIPerUnitInitTOC_IIB[4],OGIPerUnitInitTOC_III[4];  //ÿ��λ��kg��ԭʼ�л�̼������������
		  double GGIPerUnitInitTOC_I[4],GGIPerUnitInitTOC_IIA[4],GGIPerUnitInitTOC_IIB[4],GGIPerUnitInitTOC_III[4];  //ÿ��λ��kg��ԭʼ�л�̼������������
		  double LinerInterpolate(double t,double t0,double p0,double t1,double p1){return p1-(p1-p0)*(t1-t)/(t1-t0);}//���Բ�ֵ����
		 
		  void GetHCFromDR(double *Ro)
		   {
			   for (int idx = RO_TTI; idx <= RO_Basin; idx++)
			   {
				   if(Ro[idx]<=RoI[0]) HCFromDRI[idx]=DRI[0];
				   else if(Ro[idx]>= RoI[ NI-1]) HCFromDRI[idx]= DRI[ NI-1];
				   else {for(int i=0;i< NI-1;i++) if(Ro[idx]> RoI[i]&&Ro[idx]<= RoI[i+1]) HCFromDRI[idx]=LinerInterpolate(Ro[idx], RoI[i], DRI[i], RoI[i+1], DRI[i+1]);}
				   
				   if(Ro[idx]<= RoIIA[0]) HCFromDRIIA[idx]= DRIIA[0];
				   else if(Ro[idx]>= RoIIA[ NIIA-1]) HCFromDRIIA[idx]= DRIIA[ NIIA-1];
				   else {for(int i=0;i< NIIA-1;i++) if(Ro[idx]> RoIIA[i]&&Ro[idx]<= RoIIA[i+1]) HCFromDRIIA[idx]=LinerInterpolate(Ro[idx], RoIIA[i], DRIIA[i], RoIIA[i+1], DRIIA[i+1]);}
				   
				   if(Ro[idx]<= RoIIB[0]) HCFromDRIIB[idx]= DRIIB[0];
				   else if(Ro[idx]>= RoIIB[ NIIB-1]) HCFromDRIIB[idx]= DRIIB[ NIIB-1];
				   else {for(int i=0;i< NIIB-1;i++) if(Ro[idx]> RoIIB[i]&&Ro[idx]<= RoIIB[i+1]) HCFromDRIIB[idx]=LinerInterpolate(Ro[idx], RoIIB[i], DRIIB[i], RoIIB[i+1], DRIIB[i+1]);}
				   
				   if(Ro[idx]<= RoIII[0]) HCFromDRIIB[idx]= DRIII[0];
				   else if(Ro[idx]>= RoIII[ NIII-1]) HCFromDRIII[idx]= DRIII[ NIII-1];
				   else {for(int i=0;i< NIII-1;i++) if(Ro[idx]> RoIII[i]&&Ro[idx]<= RoIII[i+1]) HCFromDRIII[idx]=LinerInterpolate(Ro[idx], RoIII[i], DRIII[i], RoIII[i+1], DRIII[i+1]);}
				   
				   if(Ro[idx]<= RoGDR[0]) GasRatio[idx]= DRIII[0];
				   else if(Ro[idx]>= RoGDR[ NGDR-1])GasRatio[idx]= GDR[ NGDR-1];
				   else {for(int i=0;i< NGDR-1;i++) if(Ro[idx]> RoGDR[i]&&Ro[idx]<= RoGDR[i+1]) GasRatio[idx]=LinerInterpolate(Ro[idx], RoGDR[i], GDR[i], RoGDR[i+1], GDR[i+1]);}
				   
				   HCGIPerUnitInitTOC_I[idx]=HCFromDRI[idx]/100./0.84;  
				   HCGIPerUnitInitTOC_IIA[idx]=HCFromDRIIA[idx]/100./0.84;
				   HCGIPerUnitInitTOC_IIB[idx]=HCFromDRIIB[idx]/100./0.84; 
				   HCGIPerUnitInitTOC_III[idx]=HCFromDRIII[idx]/100./0.84;
				   
				   OGIPerUnitInitTOC_I[idx]=HCGIPerUnitInitTOC_I[idx]*(1.0-GasRatio[idx]);
				   OGIPerUnitInitTOC_IIA[idx]=HCGIPerUnitInitTOC_IIA[idx]*(1.0-GasRatio[idx]);
				   OGIPerUnitInitTOC_IIB[idx]=HCGIPerUnitInitTOC_IIB[idx]*(1.0-GasRatio[idx]);
				   OGIPerUnitInitTOC_III[idx]=HCGIPerUnitInitTOC_III[idx]*(1.0-GasRatio[idx]);
				   
				   GGIPerUnitInitTOC_I[idx]=HCGIPerUnitInitTOC_I[idx]*GasRatio[idx];
				   GGIPerUnitInitTOC_IIA[idx]=HCGIPerUnitInitTOC_IIA[idx]*GasRatio[idx];    //���������Ҳ��kg��ʾ�����ٳ���COGת��Ϊ������
				   GGIPerUnitInitTOC_IIB[idx]=HCGIPerUnitInitTOC_IIB[idx]*GasRatio[idx];
				   GGIPerUnitInitTOC_III[idx]=HCGIPerUnitInitTOC_III[idx]*GasRatio[idx];
			   }
		   }

		};

		 struct ParaLLNL
		 {
			   //����ΪLawrence Livermore National Laboratories (LLNL)���Ҹ���ӳ����ѧ����
			  double W; //��������Ϊ�л�̼�ı���  =0.85
			  int NKerogenType;   //���Ҹ�������
			  double *RatioKerogenType; // ���Ҹ�����
			  double *InitTOC;//ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
			  double *MassOfInitTOC; //ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
			  
			  //2017/10/13: new added variables below
			  double MassOfInitTOCTotal; //���Ҹ�ԭʼ�л�̼�ܵ�����

			  double *MKer; //ÿ�ָ��Ҹ����л�̼�������ݻ������б仯������������Ҹ����������������¼���20170908
			  double MKerTotal; //�ܵĸ��Ҹ��л�̼�����������������ѽ�Ľ�̿���� ���¼���20170908

			  //����ΪI�͸��Ҹ��Ķ���ѧ����
			  double HI_LLNL_I; //I�͸��Ҹ�����ָ��
			  double KSF_LLNL_I;//   Kerogen Start Fraction  LLNL��I�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			  double KToOilF_LLNL_I;// ���Ҹ������͵ı���
			  double KToGasF_LLNL_I; //  ���Ҹ��������ı���
			  double OSF_LLNL_I;  // Oil Strat Fraction ��Ӧ��������ʼ����;;����ָ��ʼ�����л�̼�����л�̼�еı���
			  double OToGasF_LLNL_I; //���������ı���
			  double OToResidueF_LLNL_I; //�����ɲ�����ı���

			  int N_LLNL_I_KToOil;//LLNL��I�͸��Ҹ����͵�ƽ�з�Ӧ�����
			  double *fLLNL_I_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *ELLNL_I_KToOil;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_I_KToOil; //Frequency factor  ����A

			  int N_LLNL_I_KToGas;//LLNL��I�͸��Ҹ�������ƽ�з�Ӧ�����
			  double *fLLNL_I_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *ELLNL_I_KToGas;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_I_KToGas; //Frequency factor,Ƶ������

			  int N_LLNL_I_OilToGas;//LLNL��I�͸��Ҹ����������ķ�Ӧ�����
			  double *fLLNL_I_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *fLLNL_I_OilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			  double *ELLNL_I_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_I_OilToGas; //Frequency factor

			  int N_LLNL_I_OilToResidue;//LLNL��I�͸��Ҹ������ɲ�����ķ�Ӧ�����
			  double *fLLNL_I_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *fLLNL_I_OilToResidueBak;  //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			  double *ELLNL_I_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_I_OilToResidue; //Frequency factor
			//����ΪLLNL II�͸��Ҹ�����
			  double HI_LLNL_II; //II�͸��Ҹ�����ָ��
			  double KSF_LLNL_II;//   Kerogen Start Fraction  LLNL��II�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			  double KToOilF_LLNL_II;// ���Ҹ������͵ı���
			  double KToGasF_LLNL_II; //  ���Ҹ��������ı���
			  double OSF_LLNL_II;  // Oil Strat Fraction ��Ӧ��������ʼ����
			  double OToGasF_LLNL_II; //���������ı���
			  double OToResidueF_LLNL_II; //�����ɲ�����ı���

			  int N_LLNL_II_KToOil;//LLNL��II�͸��Ҹ����͵�ƽ�з�Ӧ�����
			  double *fLLNL_II_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *ELLNL_II_KToOil;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_II_KToOil; //Frequency factor

			  int N_LLNL_II_KToGas;//LLNL��II�͸��Ҹ�������ƽ�з�Ӧ�����
			  double *fLLNL_II_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *ELLNL_II_KToGas;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_II_KToGas; //Frequency factor

			  int N_LLNL_II_OilToGas;//LLNL��II�͸��Ҹ����������ķ�Ӧ�����
			  double *fLLNL_II_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *fLLNL_II_OilToGasBak;   //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			  double *ELLNL_II_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_II_OilToGas; //Frequency factor

			  int N_LLNL_II_OilToResidue;//LLNL��II�͸��Ҹ������ɲ�����ķ�Ӧ�����
			  double *fLLNL_II_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *fLLNL_II_OilToResidueBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			  double *ELLNL_II_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_II_OilToResidue; //Frequency factor

			//����ΪLLNL III�͸��Ҹ�����
			  double HI_LLNL_III; //III�͸��Ҹ�����ָ��
			  double KSF_LLNL_III;//   Kerogen Start Fraction  LLNL��III�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			  double KToOilF_LLNL_III;// ���Ҹ������͵ı���
			  double KToGasF_LLNL_III; //  ���Ҹ��������ı���
			  double OSF_LLNL_III;  // Oil Strat Fraction ��Ӧ��������ʼ����
			  double OToGasF_LLNL_III; //���������ı���
			  double OToResidueF_LLNL_III; //�����ɲ�����ı���

			  int N_LLNL_III_KToOil;//LLNL��III�͸��Ҹ����͵�ƽ�з�Ӧ�����
			  double *fLLNL_III_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *ELLNL_III_KToOil;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_III_KToOil; //Frequency factor

			  int N_LLNL_III_KToGas;//LLNL��III�͸��Ҹ�������ƽ�з�Ӧ�����
			  double *fLLNL_III_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *ELLNL_III_KToGas;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_III_KToGas; //Frequency factor

			  int N_LLNL_III_OilToGas;//LLNL��III�͸��Ҹ����������ķ�Ӧ�����
			  double *fLLNL_III_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *fLLNL_III_OilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			  double *ELLNL_III_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_III_OilToGas; //Frequency factor

			  int N_LLNL_III_OilToResidue;//LLNL��III�͸��Ҹ������ɲ�����ķ�Ӧ�����
			  double *fLLNL_III_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			  double *fLLNL_III_OilToResidueBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			  double *ELLNL_III_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
			  double *FFLLNL_III_OilToResidue; //Frequency factor

			  ParaLLNL()
			  {
				  Init();
			  }

			  void Init()
			  {
				  W = 0.85;
				  NKerogenType = 0;   //���Ҹ�������
				  RatioKerogenType = 0; // ���Ҹ�����
				  InitTOC = 0;//ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
				  MassOfInitTOC = 0; //ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ

				  //����ΪI�͸��Ҹ��Ķ���ѧ����
				  HI_LLNL_I = 0.; //I�͸��Ҹ�����ָ��
				  KSF_LLNL_I = 0.;//   Kerogen Start Fraction  LLNL��I�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
				  KToOilF_LLNL_I = 0.;// ���Ҹ������͵ı���
				  KToGasF_LLNL_I = 0.; //  ���Ҹ��������ı���
				  OSF_LLNL_I = 0.;  // Oil Strat Fraction ��Ӧ��������ʼ����
				  OToGasF_LLNL_I = 0.; //���������ı���
				  OToResidueF_LLNL_I = 0.; //�����ɲ�����ı���

				  N_LLNL_I_KToOil = 0;//LLNL��I�͸��Ҹ����͵�ƽ�з�Ӧ�����
				  fLLNL_I_KToOil = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  ELLNL_I_KToOil = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_I_KToOil = 0; //Frequency factor  ����A

				  N_LLNL_I_KToGas = 0;//LLNL��I�͸��Ҹ�������ƽ�з�Ӧ�����
				  fLLNL_I_KToGas = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  ELLNL_I_KToGas = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_I_KToGas = 0; //Frequency factor,Ƶ������

				  N_LLNL_I_OilToGas = 0;//LLNL��I�͸��Ҹ����������ķ�Ӧ�����
				  fLLNL_I_OilToGas = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  fLLNL_I_OilToGasBak = 0; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  ELLNL_I_OilToGas = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_I_OilToGas = 0; //Frequency factor

				  N_LLNL_I_OilToResidue = 0;//LLNL��I�͸��Ҹ������ɲ�����ķ�Ӧ�����
				  fLLNL_I_OilToResidue = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  fLLNL_I_OilToResidueBak = 0;  //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  ELLNL_I_OilToResidue = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_I_OilToResidue = 0; //Frequency factor

				  //����ΪLLNL II�͸��Ҹ�����
				  HI_LLNL_II = 0.; //II�͸��Ҹ�����ָ��
				  KSF_LLNL_II = 0.;//   Kerogen Start Fraction  LLNL��II�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
				  KToOilF_LLNL_II = 0.;// ���Ҹ������͵ı���
				  KToGasF_LLNL_II = 0.; //  ���Ҹ��������ı���
				  OSF_LLNL_II = 0.;  // Oil Strat Fraction ��Ӧ��������ʼ����
				  OToGasF_LLNL_II = 0.; //���������ı���
				  OToResidueF_LLNL_II = 0.; //�����ɲ�����ı���

				  N_LLNL_II_KToOil = 0;//LLNL��II�͸��Ҹ����͵�ƽ�з�Ӧ�����
				  fLLNL_II_KToOil = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  ELLNL_II_KToOil = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_II_KToOil = 0; //Frequency factor

				  N_LLNL_II_KToGas = 0;//LLNL��II�͸��Ҹ�������ƽ�з�Ӧ�����
				  fLLNL_II_KToGas = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  ELLNL_II_KToGas = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_II_KToGas = 0; //Frequency factor

				  N_LLNL_II_OilToGas = 0;//LLNL��II�͸��Ҹ����������ķ�Ӧ�����
				  fLLNL_II_OilToGas = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  fLLNL_II_OilToGasBak = 0;   //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  ELLNL_II_OilToGas = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_II_OilToGas = 0; //Frequency factor

				  N_LLNL_II_OilToResidue = 0;//LLNL��II�͸��Ҹ������ɲ�����ķ�Ӧ�����
				  fLLNL_II_OilToResidue = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  fLLNL_II_OilToResidueBak = 0; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  ELLNL_II_OilToResidue = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_II_OilToResidue = 0; //Frequency factor

				  //����ΪLLNL III�͸��Ҹ�����
				  HI_LLNL_III = 0.; //III�͸��Ҹ�����ָ��
				  KSF_LLNL_III = 0.;//   Kerogen Start Fraction  LLNL��III�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
				  KToOilF_LLNL_III = 0.;// ���Ҹ������͵ı���
				  KToGasF_LLNL_III = 0.; //  ���Ҹ��������ı���
				  OSF_LLNL_III = 0.;  // Oil Strat Fraction ��Ӧ��������ʼ����
				  OToGasF_LLNL_III = 0.; //���������ı���
				  OToResidueF_LLNL_III = 0.; //�����ɲ�����ı���

				  N_LLNL_III_KToOil = 0;//LLNL��III�͸��Ҹ����͵�ƽ�з�Ӧ�����
				  fLLNL_III_KToOil = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  ELLNL_III_KToOil = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_III_KToOil = 0; //Frequency factor

				  N_LLNL_III_KToGas = 0;//LLNL��III�͸��Ҹ�������ƽ�з�Ӧ�����
				  fLLNL_III_KToGas = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  ELLNL_III_KToGas = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_III_KToGas = 0; //Frequency factor

				  N_LLNL_III_OilToGas = 0;//LLNL��III�͸��Ҹ����������ķ�Ӧ�����
				  fLLNL_III_OilToGas = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  fLLNL_III_OilToGasBak = 0; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  ELLNL_III_OilToGas = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_III_OilToGas = 0; //Frequency factor

				  N_LLNL_III_OilToResidue = 0;//LLNL��III�͸��Ҹ������ɲ�����ķ�Ӧ�����
				  fLLNL_III_OilToResidue = 0;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  fLLNL_III_OilToResidueBak = 0; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  ELLNL_III_OilToResidue = 0;//��ܣ�Activation Energy����Kcal/mole��
				  FFLLNL_III_OilToResidue = 0; //Frequency factor

				  //�ֱ���I��II��III�͸��Ҹ��������Ͷ����µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
				  wBIw0_I_KToOil = 0.;
				  wBIw0_II_KToOil = 0.;
				  wBIw0_III_KToOil = 0.;

				  //�ֱ���I��II��III�͸��Ҹ��������������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
				  wBIw0_I_KToGas = 0.;
				  wBIw0_II_KToGas = 0.;
				  wBIw0_III_KToGas = 0.;

				  //�ֱ���I��II��III�͸��Ҹ�������ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
				  wBIw0_I_OilToGas = 0.;
				  wBIw0_II_OilToGas = 0.;
				  wBIw0_III_OilToGas = 0.; 

				  //�ֱ���I��II��III�͸��Ҹ�������ѽ�ɲ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
				  wBIw0_I_OilToResidue = 0.;
				  wBIw0_II_OilToResidue = 0.;
				  wBIw0_III_OilToResidue = 0.; 

				  //�ֱ���I��II��III�͸��Ҹ� �ܵ�ʣ�໯ѧ����ϵ����ԭʼΪ1��ͨ�����Ҹ��������͡����������µ��ܵ�ʣ�໯ѧ����ϵ���ֱ���Ը��Ҹ������͵ı��ʺ��������ı���֮����Ӷ��õ���
				  wBIw0_I_K = 0.;
				  wBIw0_II_K = 0.;
				  wBIw0_III_K = 0.; 

				  //�ֱ���I��II��III��InitTOC����һʱ��ε�������
				  OilPerInitTOC_I = 0.;
				  OilPerInitTOC_II = 0.;
				  OilPerInitTOC_III = 0.; 

				  //�ֱ���I��II��III��InitTOC����һʱ��ε�������
				  GasPerInitTOC_I = 0.;
				  GasPerInitTOC_II = 0.;
				  GasPerInitTOC_III = 0.;; 

				  //ÿ�����͸��Ҹ��л�̼ʣ����
				  TOCRemained_I = 0.;
				  TOCRemained_II = 0.;
				  TOCRemained_III = 0.;

				  //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ���
				  OilCracked_I = 0.;
				  OilCracked_II = 0.;
				  OilCracked_III = 0.; 

				  //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ������
				  GasCracked_I = 0.;
				  GasCracked_II = 0.;
				  GasCracked_III = 0.;

				  //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ�ɲ�������
				  ResidueCracked_I = 0.;
				  ResidueCracked_II = 0.;
				  ResidueCracked_III = 0.; 

				  //ÿ�ֵ�λ����ԭʼ���Ҹ������Լ����ѽ�Ϊ������ڵ���
				  OilExisted_I = 0.;
				  OilExisted_II = 0.;
				  OilExisted_III = 0.;   

				  //ÿ�ֵ�λ����ԭʼ���Ҹ������Լ����ѽ����
				  GasExisted_I = 0.;
				  GasExisted_II = 0.;
				  GasExisted_III = 0.;  

				  //ÿ�ֵ�λ����ԭʼ���Ҹ���صĲ�������
				  ResidueExisted_I = 0.;
				  ResidueExisted_II = 0.;
				  ResidueExisted_III = 0.;  

				  //2017/10/13: new added variables below
				  MassOfInitTOCTotal = 0.;//���Ҹ�ԭʼ�л�̼�ܵ�����
				  
				  MKer = 0; //ÿ�ָ��Ҹ����л�̼�������ݻ������б仯������������Ҹ����������������¼���20170908
				  MKerTotal = 0.; //�ܵĸ��Ҹ��л�̼�����������������ѽ�Ľ�̿���� ���¼���20170908

				  //�������ۻ����������������Exsited��ͬ���ǵ�λ����ԭʼ�л�̼���ͺ�������
				  OilGenerated_I = 0.;
				  OilGenerated_II = 0.;
				  OilGenerated_III = 0.;
				  GasGenerated_I = 0.;
				  GasGenerated_II = 0.;
				  GasGenerated_III = 0.;

				  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ���������������
				  OilGenerated = 0.;
				  GasGenerated = 0.;

				   //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����������������
				  OilPerInitTOC = 0.;
				  GasPerInitTOC = 0.;

				  //Դ�ҵ�����ת����
				  TR = 0.; 

				  OilExisted = 0.; //ָ���Ǵ�����Դ���е������
				  GasExisted = 0.;//ָ���Ǵ�����Դ���е������
				  GasCracked = 0.;//ָ����ÿһ�����ѽ������
				  GasCrackedAdded = 0.; //ָÿһ���ѽ������ۼ���
				  ResidueCracked = 0.; // ָ����ÿһ�����ѽ�Ĳ�������
				  ResidueCrackedAdded = 0.; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
				  OilCracked = 0.;//ÿһ���͵��ѽ���
				  OilCrackedAdded = 0.;//ÿһ���͵��ѽ������ۼ���

				  MKerReac = 0.; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
				  MKerInert = 0.; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
			  }

			  void Release()
			  {
				  DoRelease(RatioKerogenType); // ���Ҹ�����
				  DoRelease(InitTOC);//ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
				  DoRelease(MassOfInitTOC); //ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
				 
				  DoRelease(fLLNL_I_KToOil);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(ELLNL_I_KToOil);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_I_KToOil); //Frequency factor  ����A

				  DoRelease(fLLNL_I_KToGas);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(ELLNL_I_KToGas);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_I_KToGas); //Frequency factor,Ƶ������

				  DoRelease(fLLNL_I_OilToGas);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(fLLNL_I_OilToGasBak); //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  DoRelease(ELLNL_I_OilToGas);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_I_OilToGas); //Frequency factor

				  DoRelease(fLLNL_I_OilToResidue);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(fLLNL_I_OilToResidueBak);  //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  DoRelease(ELLNL_I_OilToResidue);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_I_OilToResidue); //Frequency factor
				 
				  DoRelease(fLLNL_II_KToOil);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(ELLNL_II_KToOil);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_II_KToOil); //Frequency factor

				  DoRelease(fLLNL_II_KToGas);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(ELLNL_II_KToGas);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_II_KToGas); //Frequency factor

				  DoRelease(fLLNL_II_OilToGas);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(fLLNL_II_OilToGasBak);   //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  DoRelease(ELLNL_II_OilToGas);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_II_OilToGas); //Frequency factor

				  DoRelease(fLLNL_II_OilToResidue);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(fLLNL_II_OilToResidueBak); //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  DoRelease(ELLNL_II_OilToResidue);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_II_OilToResidue); //Frequency factor

				 
				  DoRelease(fLLNL_III_KToOil);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(ELLNL_III_KToOil);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_III_KToOil); //Frequency factor

				  DoRelease(fLLNL_III_KToGas);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(ELLNL_III_KToGas);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_III_KToGas); //Frequency factor

				  DoRelease(fLLNL_III_OilToGas);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(fLLNL_III_OilToGasBak); //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  DoRelease(ELLNL_III_OilToGas);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_III_OilToGas); //Frequency factor

				  DoRelease(fLLNL_III_OilToResidue);//�ǻ�ѧ����ϵ����Stoichiometric Factor��
				  DoRelease(fLLNL_III_OilToResidueBak); //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
				  DoRelease(ELLNL_III_OilToResidue);//��ܣ�Activation Energy����Kcal/mole��
				  DoRelease(FFLLNL_III_OilToResidue); //Frequency factor

				  //2017/10/13: new added variables below
				  DoRelease(MKer);//ÿ�ָ��Ҹ����л�̼�������ݻ������б仯������������Ҹ�������������
			  }

			  void DoRelease(double *&val)
			  {
				if (val)
				{
					delete val;
				}
				val = 0;
			  }

			  void Construct(int aNKerogenType,double *aRatioKerogenType,double aHI_LLNL_I,double aKSF_LLNL_I,double aKToOilF_LLNL_I,double aKToGasF_LLNL_I,double aOSF_LLNL_I,double aOToGasF_LLNL_I,double aOToResidueF_LLNL_I,
							 int aN_LLNL_I_KToOil,double *afLLNL_I_KToOil,double *aELLNL_I_KToOil,double *aFFLLNL_I_KToOil,int aN_LLNL_I_KToGas,double *afLLNL_I_KToGas,double *aELLNL_I_KToGas,double *aFFLLNL_I_KToGas,
							 int aN_LLNL_I_OilToGas,double *afLLNL_I_OilToGas,double *aELLNL_I_OilToGas,double *aFFLLNL_I_OilToGas,int aN_LLNL_I_OilToResidue,double *afLLNL_I_OilToResidue,double *aELLNL_I_OilToResidue,double *aFFLLNL_I_OilToResidue,
							 double aHI_LLNL_II,double aKSF_LLNL_II,double aKToOilF_LLNL_II,double aKToGasF_LLNL_II,double aOSF_LLNL_II,double aOToGasF_LLNL_II,double aOToResidueF_LLNL_II,
							 int aN_LLNL_II_KToOil,double *afLLNL_II_KToOil,double *aELLNL_II_KToOil,double *aFFLLNL_II_KToOil,int aN_LLNL_II_KToGas,double *afLLNL_II_KToGas,double *aELLNL_II_KToGas,double *aFFLLNL_II_KToGas,
							 int aN_LLNL_II_OilToGas,double *afLLNL_II_OilToGas,double *aELLNL_II_OilToGas,double *aFFLLNL_II_OilToGas,int aN_LLNL_II_OilToResidue,double *afLLNL_II_OilToResidue,double *aELLNL_II_OilToResidue,double *aFFLLNL_II_OilToResidue,
							 double aHI_LLNL_III,double aKSF_LLNL_III,double aKToOilF_LLNL_III,double aKToGasF_LLNL_III,double aOSF_LLNL_III,double aOToGasF_LLNL_III,double aOToResidueF_LLNL_III,
							 int aN_LLNL_III_KToOil,double *afLLNL_III_KToOil,double *aELLNL_III_KToOil,double *aFFLLNL_III_KToOil,int aN_LLNL_III_KToGas,double *afLLNL_III_KToGas,double *aELLNL_III_KToGas,double *aFFLLNL_III_KToGas,
							 int aN_LLNL_III_OilToGas,double *afLLNL_III_OilToGas,double *aELLNL_III_OilToGas,double *aFFLLNL_III_OilToGas,int aN_LLNL_III_OilToResidue,double *afLLNL_III_OilToResidue,double *aELLNL_III_OilToResidue,double *aFFLLNL_III_OilToResidue )
				{
				   Release();

				   W=0.85;
				   NKerogenType=aNKerogenType;
				   RatioKerogenType=new double[NKerogenType];
				   for(int i=0;i<NKerogenType;i++) RatioKerogenType[i]=aRatioKerogenType[i];

				   HI_LLNL_I=aHI_LLNL_I;KSF_LLNL_I=aKSF_LLNL_I;KToOilF_LLNL_I=aKToOilF_LLNL_I;KToGasF_LLNL_I=aKToGasF_LLNL_I;OSF_LLNL_I=aOSF_LLNL_I;OToGasF_LLNL_I=aOToGasF_LLNL_I;OToResidueF_LLNL_I=aOToResidueF_LLNL_I;
				   N_LLNL_I_KToOil=aN_LLNL_I_KToOil; fLLNL_I_KToOil=new double[N_LLNL_I_KToOil]; ELLNL_I_KToOil=new double[N_LLNL_I_KToOil];FFLLNL_I_KToOil=new double[N_LLNL_I_KToOil];
				   for(int i=0;i< N_LLNL_I_KToOil;i++) {fLLNL_I_KToOil[i]=afLLNL_I_KToOil[i];ELLNL_I_KToOil[i]=aELLNL_I_KToOil[i];FFLLNL_I_KToOil[i]=aFFLLNL_I_KToOil[i];}
				   N_LLNL_I_KToGas=aN_LLNL_I_KToGas; fLLNL_I_KToGas=new double[N_LLNL_I_KToGas]; ELLNL_I_KToGas=new double[N_LLNL_I_KToGas];FFLLNL_I_KToGas=new double[N_LLNL_I_KToGas];
				   for(int i=0;i< N_LLNL_I_KToGas;i++) {fLLNL_I_KToGas[i]=afLLNL_I_KToGas[i];ELLNL_I_KToGas[i]=aELLNL_I_KToGas[i];FFLLNL_I_KToGas[i]=aFFLLNL_I_KToGas[i];}
				   N_LLNL_I_OilToGas=aN_LLNL_I_OilToGas;fLLNL_I_OilToGas=new double[N_LLNL_I_OilToGas]; fLLNL_I_OilToGasBak=new double[N_LLNL_I_OilToGas];ELLNL_I_OilToGas=new double[N_LLNL_I_OilToGas];FFLLNL_I_OilToGas=new double[N_LLNL_I_OilToGas];
				   for(int i=0;i<N_LLNL_I_OilToGas;i++) {fLLNL_I_OilToGas[i]=afLLNL_I_OilToGas[i];fLLNL_I_OilToGasBak[i]=afLLNL_I_OilToGas[i];ELLNL_I_OilToGas[i]=aELLNL_I_OilToGas[i];FFLLNL_I_OilToGas[i]=aFFLLNL_I_OilToGas[i];}
				   N_LLNL_I_OilToResidue=aN_LLNL_I_OilToResidue;fLLNL_I_OilToResidue=new double[N_LLNL_I_OilToResidue];fLLNL_I_OilToResidueBak=new double[N_LLNL_I_OilToResidue]; ELLNL_I_OilToResidue=new double[N_LLNL_I_OilToResidue]; FFLLNL_I_OilToResidue=new double[N_LLNL_I_OilToResidue];
				   for(int i=0;i<N_LLNL_I_OilToResidue;i++) {fLLNL_I_OilToResidue[i]=afLLNL_I_OilToResidue[i];fLLNL_I_OilToResidueBak[i]=afLLNL_I_OilToResidue[i];ELLNL_I_OilToResidue[i]=aELLNL_I_OilToResidue[i];FFLLNL_I_OilToResidue[i]=aFFLLNL_I_OilToResidue[i];}

				   HI_LLNL_II=aHI_LLNL_II;KSF_LLNL_II=aKSF_LLNL_II;KToOilF_LLNL_II=aKToOilF_LLNL_II;KToGasF_LLNL_II=aKToGasF_LLNL_II;OSF_LLNL_II=aOSF_LLNL_II;OToGasF_LLNL_II=aOToGasF_LLNL_II;OToResidueF_LLNL_II=aOToResidueF_LLNL_II;
				   N_LLNL_II_KToOil=aN_LLNL_II_KToOil; fLLNL_II_KToOil=new double[N_LLNL_II_KToOil]; ELLNL_II_KToOil=new double[N_LLNL_II_KToOil];FFLLNL_II_KToOil=new double[N_LLNL_II_KToOil];
				   for(int i=0;i< N_LLNL_II_KToOil;i++) {fLLNL_II_KToOil[i]=afLLNL_II_KToOil[i];ELLNL_II_KToOil[i]=aELLNL_II_KToOil[i];FFLLNL_II_KToOil[i]=aFFLLNL_II_KToOil[i];}
				   N_LLNL_II_KToGas=aN_LLNL_II_KToGas; fLLNL_II_KToGas=new double[N_LLNL_II_KToGas]; ELLNL_II_KToGas=new double[N_LLNL_II_KToGas];FFLLNL_II_KToGas=new double[N_LLNL_II_KToGas];
				   for(int i=0;i< N_LLNL_II_KToGas;i++) {fLLNL_II_KToGas[i]=afLLNL_II_KToGas[i];ELLNL_II_KToGas[i]=aELLNL_II_KToGas[i];FFLLNL_II_KToGas[i]=aFFLLNL_II_KToGas[i];}
				   N_LLNL_II_OilToGas=aN_LLNL_II_OilToGas;fLLNL_II_OilToGas=new double[N_LLNL_II_OilToGas];fLLNL_II_OilToGasBak=new double[N_LLNL_II_OilToGas]; ELLNL_II_OilToGas=new double[N_LLNL_II_OilToGas];FFLLNL_II_OilToGas=new double[N_LLNL_II_OilToGas];
				   for(int i=0;i<N_LLNL_II_OilToGas;i++) {fLLNL_II_OilToGas[i]=afLLNL_II_OilToGas[i];fLLNL_II_OilToGasBak[i]=afLLNL_II_OilToGas[i];ELLNL_II_OilToGas[i]=aELLNL_II_OilToGas[i];FFLLNL_II_OilToGas[i]=aFFLLNL_II_OilToGas[i];}
				   N_LLNL_II_OilToResidue=aN_LLNL_II_OilToResidue;fLLNL_II_OilToResidue=new double[N_LLNL_II_OilToResidue];fLLNL_II_OilToResidueBak=new double[N_LLNL_II_OilToResidue]; ELLNL_II_OilToResidue=new double[N_LLNL_II_OilToResidue]; FFLLNL_II_OilToResidue=new double[N_LLNL_II_OilToResidue];
				   for(int i=0;i<N_LLNL_II_OilToResidue;i++) {fLLNL_II_OilToResidue[i]=afLLNL_II_OilToResidue[i];fLLNL_II_OilToResidueBak[i]=afLLNL_II_OilToResidue[i];ELLNL_II_OilToResidue[i]=aELLNL_II_OilToResidue[i];FFLLNL_II_OilToResidue[i]=aFFLLNL_II_OilToResidue[i];}

				   HI_LLNL_III=aHI_LLNL_III;KSF_LLNL_III=aKSF_LLNL_III;KToOilF_LLNL_III=aKToOilF_LLNL_III;KToGasF_LLNL_III=aKToGasF_LLNL_III;OSF_LLNL_III=aOSF_LLNL_III;OToGasF_LLNL_III=aOToGasF_LLNL_III;OToResidueF_LLNL_III=aOToResidueF_LLNL_III;
				   N_LLNL_III_KToOil=aN_LLNL_III_KToOil; fLLNL_III_KToOil=new double[N_LLNL_III_KToOil]; ELLNL_III_KToOil=new double[N_LLNL_III_KToOil];FFLLNL_III_KToOil=new double[N_LLNL_III_KToOil];
				   for(int i=0;i< N_LLNL_III_KToOil;i++) {fLLNL_III_KToOil[i]=afLLNL_III_KToOil[i];ELLNL_III_KToOil[i]=aELLNL_III_KToOil[i];FFLLNL_III_KToOil[i]=aFFLLNL_III_KToOil[i];}
				   N_LLNL_III_KToGas=aN_LLNL_III_KToGas; fLLNL_III_KToGas=new double[N_LLNL_III_KToGas]; ELLNL_III_KToGas=new double[N_LLNL_III_KToGas];FFLLNL_III_KToGas=new double[N_LLNL_III_KToGas];
				   for(int i=0;i< N_LLNL_III_KToGas;i++) {fLLNL_III_KToGas[i]=afLLNL_III_KToGas[i];ELLNL_III_KToGas[i]=aELLNL_III_KToGas[i];FFLLNL_III_KToGas[i]=aFFLLNL_III_KToGas[i];}
				   N_LLNL_III_OilToGas=aN_LLNL_III_OilToGas;fLLNL_III_OilToGas=new double[N_LLNL_III_OilToGas];fLLNL_III_OilToGasBak=new double[N_LLNL_III_OilToGas];  ELLNL_III_OilToGas=new double[N_LLNL_III_OilToGas];FFLLNL_III_OilToGas=new double[N_LLNL_III_OilToGas];
				   for(int i=0;i<N_LLNL_III_OilToGas;i++) {fLLNL_III_OilToGas[i]=afLLNL_III_OilToGas[i];fLLNL_III_OilToGasBak[i]=afLLNL_III_OilToGas[i];ELLNL_III_OilToGas[i]=aELLNL_III_OilToGas[i];FFLLNL_III_OilToGas[i]=aFFLLNL_III_OilToGas[i];}
				   N_LLNL_III_OilToResidue=aN_LLNL_III_OilToResidue;fLLNL_III_OilToResidue=new double[N_LLNL_III_OilToResidue];fLLNL_III_OilToResidueBak=new double[N_LLNL_III_OilToResidue]; ELLNL_III_OilToResidue=new double[N_LLNL_III_OilToResidue]; FFLLNL_III_OilToResidue=new double[N_LLNL_III_OilToResidue];
				   for(int i=0;i<N_LLNL_III_OilToResidue;i++) {fLLNL_III_OilToResidue[i]=afLLNL_III_OilToResidue[i];fLLNL_III_OilToResidueBak[i]=afLLNL_III_OilToResidue[i];ELLNL_III_OilToResidue[i]=aELLNL_III_OilToResidue[i];FFLLNL_III_OilToResidue[i]=aFFLLNL_III_OilToResidue[i];}

				}
			  void CopyFrom(ParaLLNL *aParaLLNL)
			   {   
				   if (!aParaLLNL)
				   {
					   return;
				   }

				   Release();
				   
				   //����һ���ṹ�п���һ�ݲ���
				   W=aParaLLNL->W;
				   NKerogenType=aParaLLNL->NKerogenType;
				   RatioKerogenType=new double[NKerogenType];
				   for(int i=0;i<NKerogenType;i++) RatioKerogenType[i]=aParaLLNL->RatioKerogenType[i];

				   HI_LLNL_I=aParaLLNL->HI_LLNL_I;KSF_LLNL_I=aParaLLNL->KSF_LLNL_I;KToOilF_LLNL_I=aParaLLNL->KToOilF_LLNL_I;KToGasF_LLNL_I=aParaLLNL->KToGasF_LLNL_I;OSF_LLNL_I=aParaLLNL->OSF_LLNL_I;OToGasF_LLNL_I=aParaLLNL->OToGasF_LLNL_I;OToResidueF_LLNL_I=aParaLLNL->OToResidueF_LLNL_I;
				   N_LLNL_I_KToOil=aParaLLNL->N_LLNL_I_KToOil; fLLNL_I_KToOil=new double[N_LLNL_I_KToOil]; ELLNL_I_KToOil=new double[N_LLNL_I_KToOil];FFLLNL_I_KToOil=new double[N_LLNL_I_KToOil];
				   for(int i=0;i< N_LLNL_I_KToOil;i++) {fLLNL_I_KToOil[i]=aParaLLNL->fLLNL_I_KToOil[i];ELLNL_I_KToOil[i]=aParaLLNL->ELLNL_I_KToOil[i];FFLLNL_I_KToOil[i]=aParaLLNL->FFLLNL_I_KToOil[i];}
				   N_LLNL_I_KToGas=aParaLLNL->N_LLNL_I_KToGas; fLLNL_I_KToGas=new double[N_LLNL_I_KToGas]; ELLNL_I_KToGas=new double[N_LLNL_I_KToGas];FFLLNL_I_KToGas=new double[N_LLNL_I_KToGas];
				   for(int i=0;i< N_LLNL_I_KToGas;i++) {fLLNL_I_KToGas[i]=aParaLLNL->fLLNL_I_KToGas[i];ELLNL_I_KToGas[i]=aParaLLNL->ELLNL_I_KToGas[i];FFLLNL_I_KToGas[i]=aParaLLNL->FFLLNL_I_KToGas[i];}
				   N_LLNL_I_OilToGas=aParaLLNL->N_LLNL_I_OilToGas;fLLNL_I_OilToGas=new double[N_LLNL_I_OilToGas];fLLNL_I_OilToGasBak=new double[N_LLNL_I_OilToGas]; ELLNL_I_OilToGas=new double[N_LLNL_I_OilToGas];FFLLNL_I_OilToGas=new double[N_LLNL_I_OilToGas];
				   for(int i=0;i<N_LLNL_I_OilToGas;i++) {fLLNL_I_OilToGas[i]=aParaLLNL->fLLNL_I_OilToGas[i];fLLNL_I_OilToGasBak[i]=aParaLLNL->fLLNL_I_OilToGasBak[i];ELLNL_I_OilToGas[i]=aParaLLNL->ELLNL_I_OilToGas[i];FFLLNL_I_OilToGas[i]=aParaLLNL->FFLLNL_I_OilToGas[i];}
				   N_LLNL_I_OilToResidue=aParaLLNL->N_LLNL_I_OilToResidue;fLLNL_I_OilToResidue=new double[N_LLNL_I_OilToResidue];fLLNL_I_OilToResidueBak=new double[N_LLNL_I_OilToResidue]; ELLNL_I_OilToResidue=new double[N_LLNL_I_OilToResidue]; FFLLNL_I_OilToResidue=new double[N_LLNL_I_OilToResidue];
				   for(int i=0;i<N_LLNL_I_OilToResidue;i++) {fLLNL_I_OilToResidue[i]=aParaLLNL->fLLNL_I_OilToResidue[i];fLLNL_I_OilToResidueBak[i]=aParaLLNL->fLLNL_I_OilToResidueBak[i];ELLNL_I_OilToResidue[i]=aParaLLNL->ELLNL_I_OilToResidue[i];FFLLNL_I_OilToResidue[i]=aParaLLNL->FFLLNL_I_OilToResidue[i];}

				   HI_LLNL_II=aParaLLNL->HI_LLNL_II;KSF_LLNL_II=aParaLLNL->KSF_LLNL_II;KToOilF_LLNL_II=aParaLLNL->KToOilF_LLNL_II;KToGasF_LLNL_II=aParaLLNL->KToGasF_LLNL_II;OSF_LLNL_II=aParaLLNL->OSF_LLNL_II;OToGasF_LLNL_II=aParaLLNL->OToGasF_LLNL_II;OToResidueF_LLNL_II=aParaLLNL->OToResidueF_LLNL_II;
				   N_LLNL_II_KToOil=aParaLLNL->N_LLNL_II_KToOil; fLLNL_II_KToOil=new double[N_LLNL_II_KToOil]; ELLNL_II_KToOil=new double[N_LLNL_II_KToOil];FFLLNL_II_KToOil=new double[N_LLNL_II_KToOil];
				   for(int i=0;i< N_LLNL_II_KToOil;i++) {fLLNL_II_KToOil[i]=aParaLLNL->fLLNL_II_KToOil[i];ELLNL_II_KToOil[i]=aParaLLNL->ELLNL_II_KToOil[i];FFLLNL_II_KToOil[i]=aParaLLNL->FFLLNL_II_KToOil[i];}
				   N_LLNL_II_KToGas=aParaLLNL->N_LLNL_II_KToGas; fLLNL_II_KToGas=new double[N_LLNL_II_KToGas]; ELLNL_II_KToGas=new double[N_LLNL_II_KToGas];FFLLNL_II_KToGas=new double[N_LLNL_II_KToGas];
				   for(int i=0;i< N_LLNL_II_KToGas;i++) {fLLNL_II_KToGas[i]=aParaLLNL->fLLNL_II_KToGas[i];ELLNL_II_KToGas[i]=aParaLLNL->ELLNL_II_KToGas[i];FFLLNL_II_KToGas[i]=aParaLLNL->FFLLNL_II_KToGas[i];}
				   N_LLNL_II_OilToGas=aParaLLNL->N_LLNL_II_OilToGas;fLLNL_II_OilToGas=new double[N_LLNL_II_OilToGas];fLLNL_II_OilToGasBak=new double[N_LLNL_II_OilToGas];  ELLNL_II_OilToGas=new double[N_LLNL_II_OilToGas];FFLLNL_II_OilToGas=new double[N_LLNL_II_OilToGas];
				   for(int i=0;i<N_LLNL_II_OilToGas;i++) {fLLNL_II_OilToGas[i]=aParaLLNL->fLLNL_II_OilToGas[i];fLLNL_II_OilToGasBak[i]=aParaLLNL->fLLNL_II_OilToGasBak[i];ELLNL_II_OilToGas[i]=aParaLLNL->ELLNL_II_OilToGas[i];FFLLNL_II_OilToGas[i]=aParaLLNL->FFLLNL_II_OilToGas[i];}
				   N_LLNL_II_OilToResidue=aParaLLNL->N_LLNL_II_OilToResidue;fLLNL_II_OilToResidue=new double[N_LLNL_II_OilToResidue];fLLNL_II_OilToResidueBak=new double[N_LLNL_II_OilToResidue];  ELLNL_II_OilToResidue=new double[N_LLNL_II_OilToResidue]; FFLLNL_II_OilToResidue=new double[N_LLNL_II_OilToResidue];
				   for(int i=0;i<N_LLNL_II_OilToResidue;i++) {fLLNL_II_OilToResidue[i]=aParaLLNL->fLLNL_II_OilToResidue[i];fLLNL_II_OilToResidueBak[i]=aParaLLNL->fLLNL_II_OilToResidueBak[i];ELLNL_II_OilToResidue[i]=aParaLLNL->ELLNL_II_OilToResidue[i];FFLLNL_II_OilToResidue[i]=aParaLLNL->FFLLNL_II_OilToResidue[i];}

				   HI_LLNL_III=aParaLLNL->HI_LLNL_III;KSF_LLNL_III=aParaLLNL->KSF_LLNL_III;KToOilF_LLNL_III=aParaLLNL->KToOilF_LLNL_III;KToGasF_LLNL_III=aParaLLNL->KToGasF_LLNL_III;OSF_LLNL_III=aParaLLNL->OSF_LLNL_III;OToGasF_LLNL_III=aParaLLNL->OToGasF_LLNL_III;OToResidueF_LLNL_III=aParaLLNL->OToResidueF_LLNL_III;
				   N_LLNL_III_KToOil=aParaLLNL->N_LLNL_III_KToOil; fLLNL_III_KToOil=new double[N_LLNL_III_KToOil]; ELLNL_III_KToOil=new double[N_LLNL_III_KToOil];FFLLNL_III_KToOil=new double[N_LLNL_III_KToOil];
				   for(int i=0;i< N_LLNL_III_KToOil;i++) {fLLNL_III_KToOil[i]=aParaLLNL->fLLNL_III_KToOil[i];ELLNL_III_KToOil[i]=aParaLLNL->ELLNL_III_KToOil[i];FFLLNL_III_KToOil[i]=aParaLLNL->FFLLNL_III_KToOil[i];}
				   N_LLNL_III_KToGas=aParaLLNL->N_LLNL_III_KToGas; fLLNL_III_KToGas=new double[N_LLNL_III_KToGas]; ELLNL_III_KToGas=new double[N_LLNL_III_KToGas];FFLLNL_III_KToGas=new double[N_LLNL_III_KToGas];
				   for(int i=0;i< N_LLNL_III_KToGas;i++) {fLLNL_III_KToGas[i]=aParaLLNL->fLLNL_III_KToGas[i];ELLNL_III_KToGas[i]=aParaLLNL->ELLNL_III_KToGas[i];FFLLNL_III_KToGas[i]=aParaLLNL->FFLLNL_III_KToGas[i];}
				   N_LLNL_III_OilToGas=aParaLLNL->N_LLNL_III_OilToGas;fLLNL_III_OilToGas=new double[N_LLNL_III_OilToGas];fLLNL_III_OilToGasBak=new double[N_LLNL_III_OilToGas]; ELLNL_III_OilToGas=new double[N_LLNL_III_OilToGas];FFLLNL_III_OilToGas=new double[N_LLNL_III_OilToGas];
				   for(int i=0;i<N_LLNL_III_OilToGas;i++) {fLLNL_III_OilToGas[i]=aParaLLNL->fLLNL_III_OilToGas[i];fLLNL_III_OilToGasBak[i]=aParaLLNL->fLLNL_III_OilToGasBak[i];ELLNL_III_OilToGas[i]=aParaLLNL->ELLNL_III_OilToGas[i];FFLLNL_III_OilToGas[i]=aParaLLNL->FFLLNL_III_OilToGas[i];}
				   N_LLNL_III_OilToResidue=aParaLLNL->N_LLNL_III_OilToResidue;fLLNL_III_OilToResidue=new double[N_LLNL_III_OilToResidue];fLLNL_III_OilToResidueBak=new double[N_LLNL_III_OilToResidue]; ELLNL_III_OilToResidue=new double[N_LLNL_III_OilToResidue]; FFLLNL_III_OilToResidue=new double[N_LLNL_III_OilToResidue];
				   for(int i=0;i<N_LLNL_III_OilToResidue;i++) {fLLNL_III_OilToResidue[i]=aParaLLNL->fLLNL_III_OilToResidue[i];fLLNL_III_OilToResidueBak[i]=aParaLLNL->fLLNL_III_OilToResidueBak[i];ELLNL_III_OilToResidue[i]=aParaLLNL->ELLNL_III_OilToResidue[i];FFLLNL_III_OilToResidue[i]=aParaLLNL->FFLLNL_III_OilToResidue[i];}
			   }

			  double wBIw0_I_KToOil,  wBIw0_II_KToOil,  wBIw0_III_KToOil;//�ֱ���I��II��III�͸��Ҹ��������Ͷ����µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
			  double wBIw0_I_KToGas,  wBIw0_II_KToGas,  wBIw0_III_KToGas;//�ֱ���I��II��III�͸��Ҹ��������������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
			  double wBIw0_I_OilToGas,  wBIw0_II_OilToGas,  wBIw0_III_OilToGas; //�ֱ���I��II��III�͸��Ҹ�������ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
			  double wBIw0_I_OilToResidue,  wBIw0_II_OilToResidue,  wBIw0_III_OilToResidue; //�ֱ���I��II��III�͸��Ҹ�������ѽ�ɲ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1

			  double wBIw0_I_K,wBIw0_II_K, wBIw0_III_K; //�ֱ���I��II��III�͸��Ҹ� �ܵ�ʣ�໯ѧ����ϵ����ԭʼΪ1��ͨ�����Ҹ��������͡����������µ��ܵ�ʣ�໯ѧ����ϵ���ֱ���Ը��Ҹ������͵ı��ʺ��������ı���֮����Ӷ��õ���
			  double OilPerInitTOC_I, OilPerInitTOC_II, OilPerInitTOC_III; //�ֱ���I��II��III��InitTOC����һʱ��ε�������
			  double GasPerInitTOC_I, GasPerInitTOC_II, GasPerInitTOC_III; //�ֱ���I��II��III��InitTOC����һʱ��ε�������
			  double TOCRemained_I, TOCRemained_II, TOCRemained_III; //ÿ�����͸��Ҹ��л�̼ʣ���� ����ָ��λ����ԭʼ���Ҹ��Ĳ�����
			  double OilCracked_I,OilCracked_II,OilCracked_III; //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ���
			  double GasCracked_I,GasCracked_II,GasCracked_III; //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ������
			  double ResidueCracked_I,ResidueCracked_II,ResidueCracked_III; //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ�ɲ�������
			  double OilExisted_I, OilExisted_II, OilExisted_III;   //ÿ�ֵ�λ����ԭʼ���Ҹ������Լ����ѽ�Ϊ������ڵ���
			  double GasExisted_I, GasExisted_II, GasExisted_III;   //ÿ�ֵ�λ����ԭʼ���Ҹ������Լ����ѽ����
			  double ResidueExisted_I, ResidueExisted_II, ResidueExisted_III;   //ÿ�ֵ�λ����ԭʼ���Ҹ���صĲ�������
			  
			  void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,double *fLLNL,double *FFLLNL, double *ELLNL,double &wBIw0)
				{  //�ֱ�����һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma����
				   // ƽ�з�Ӧ����N_LLNL����ѧ����ϵ��fLLNL,Ƶ������FFLLNL�����ELLNL,�ܵ�ʣ�໯ѧ����ϵ��wBIw0
				 wBIw0=0;
				 double R=0.001986;//���峣�� ����λ Kcal/(mol*K)
				 //������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
				 double a,b; // ���Ա仯��ϵ��
				 a=(T-TLast)/(t-tLast);b=T-a*t;
				 //����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
				 int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
				 double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
				 double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
				 double temp=0;
				 double *wiBIw0i;  //wi/w0i ,�����EasyRo�Ƶ��еĹ�ʽ��8��
				 wiBIw0i=new double[N_LLNL];
				 for(int i=0;i<N_LLNL;i++)
				  {
				   for(int j=0;j<N;j++)
					{
					 tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					 temp+=(-FFLLNL[i]*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
					 tt1=tt2;
					}
				   wiBIw0i[i]=exp(temp);
				   fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //������һʱ��εĻ�ѧ����ϵ��
				   wBIw0+=fLLNL[i];  // wBIw0Ϊ�ܵĻ�ѧ����ϵ��ʣ��ֵ
				   tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
				   temp=0;    //temp���¹���
				  }

				 //release
				 delete wiBIw0i;
				}

			  //2017/10/13: new added variables
			  double OilGenerated_I,OilGenerated_II,OilGenerated_III,GasGenerated_I,GasGenerated_II,GasGenerated_III;//�������ۻ����������������Exsited��ͬ���ǵ�λ����ԭʼ�л�̼���ͺ�������
			  double OilGenerated,GasGenerated; //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ���������������
			  double OilPerInitTOC, GasPerInitTOC; //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����������������
			  double TR; //Դ�ҵ�����ת����

			  void Reactions(double TLast, double tLast, double T, double t)
			  {  //���ʱ���ϵ�һ���ز��
				  // �����Ҹ���֡��͡������ı仯��û�а����ѽⲿ��
				  // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
				  //aParaLLNL Ϊ��һ��ʱ��εĲ����ṹ
				  //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
				  // ����ԭ������PetroMod��������Դ��BasinMod
				  TLast+=273;T+=273;   //ת��Ϊ�����¶�
				  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				  t=t*1000000*365*24*3600; //������ת��Ϊ��
				  //����ΪI�͸��Ҹ��Ƚ�
				  double InitwBIw0_I_KToOil=0,InitwBIw0_I_KToGas=0;  //��ʼʱ�̵ĸ����Ҹ���֣���ѧ����ϵ����֮��
				  for(int i=0;i<N_LLNL_I_KToOil;i++)InitwBIw0_I_KToOil+=fLLNL_I_KToOil[i]; for(int i=0;i<N_LLNL_I_KToGas;i++)InitwBIw0_I_KToGas+=fLLNL_I_KToGas[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil,FFLLNL_I_KToOil,ELLNL_I_KToOil,wBIw0_I_KToOil);  // I�͸��Ҹ������Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas,FFLLNL_I_KToGas,ELLNL_I_KToGas,wBIw0_I_KToGas);  // I�͸��Ҹ������Ƚ�
				  OilPerInitTOC_I=HI_LLNL_I*KToOilF_LLNL_I*(InitwBIw0_I_KToOil-wBIw0_I_KToOil);  // *KSF_LLNL_I
				  GasPerInitTOC_I=HI_LLNL_I*KToGasF_LLNL_I*(InitwBIw0_I_KToGas-wBIw0_I_KToGas);  //*KSF_LLNL_I
				  OilGenerated_I=OilPerInitTOC_I; //
			      GasGenerated_I=GasPerInitTOC_I; //
				  TOCRemained_I=1.-W*OilPerInitTOC_I-W*GasPerInitTOC_I;   //��ʼʱ��ԭʼ�л�̼Ϊ1
				  
				  //����ΪII�͸��Ҹ��Ƚ�
				  double InitwBIw0_II_KToOil=0,InitwBIw0_II_KToGas=0;  //��ʼʱ�̵ĸ����Ҹ���֣���ѧ����ϵ����֮��
				  for(int i=0;i<N_LLNL_II_KToOil;i++)InitwBIw0_II_KToOil+=fLLNL_II_KToOil[i]; for(int i=0;i<N_LLNL_II_KToGas;i++)InitwBIw0_II_KToGas+=fLLNL_II_KToGas[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil,FFLLNL_II_KToOil,ELLNL_II_KToOil,wBIw0_II_KToOil);  // II�͸��Ҹ������Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas,FFLLNL_II_KToGas,ELLNL_II_KToGas,wBIw0_II_KToGas);  // II�͸��Ҹ������Ƚ�
				  OilPerInitTOC_II=HI_LLNL_II*KToOilF_LLNL_II*(InitwBIw0_II_KToOil-wBIw0_II_KToOil); // *KSF_LLNL_II
                  GasPerInitTOC_II=HI_LLNL_II*KToGasF_LLNL_II*(InitwBIw0_II_KToGas-wBIw0_II_KToGas);  //*KSF_LLNL_II
                  OilGenerated_II=OilPerInitTOC_II; //
                  GasGenerated_II=GasPerInitTOC_II; //
                  TOCRemained_II=1.-W*OilPerInitTOC_II-W*GasPerInitTOC_II;   //��ʼʱ��ԭʼ�л�̼Ϊ1
				  
				  //����ΪIII�͸��Ҹ��Ƚ�
				  double InitwBIw0_III_KToOil=0,InitwBIw0_III_KToGas=0;  //��ʼʱ�̵ĸ����Ҹ���֣���ѧ����ϵ����֮��
				  for(int i=0;i<N_LLNL_III_KToOil;i++)InitwBIw0_III_KToOil+=fLLNL_III_KToOil[i]; for(int i=0;i<N_LLNL_III_KToGas;i++)InitwBIw0_III_KToGas+=fLLNL_III_KToGas[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil,FFLLNL_III_KToOil,ELLNL_III_KToOil,wBIw0_III_KToOil);  // III�͸��Ҹ������Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas,FFLLNL_III_KToGas,ELLNL_III_KToGas,wBIw0_III_KToGas);  // III�͸��Ҹ������Ƚ�
				  OilPerInitTOC_III=HI_LLNL_III*KToOilF_LLNL_III*(InitwBIw0_III_KToOil-wBIw0_III_KToOil); // *KSF_LLNL_III
                  GasPerInitTOC_III=HI_LLNL_III*KToGasF_LLNL_III*(InitwBIw0_III_KToGas-wBIw0_III_KToGas); //*KSF_LLNL_III
                  OilGenerated_III=OilPerInitTOC_III; //
                  GasGenerated_III=GasPerInitTOC_III; //
                  TOCRemained_III=1.-W*OilPerInitTOC_III-W*GasPerInitTOC_III;   //��ʼʱ��ԭʼ�л�̼Ϊ1

				  OilPerInitTOC=OilPerInitTOC_I*RatioKerogenType[0]+OilPerInitTOC_II*RatioKerogenType[1]+OilPerInitTOC_III*RatioKerogenType[2]; //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
				  GasPerInitTOC=GasPerInitTOC_I*RatioKerogenType[0]+GasPerInitTOC_II*RatioKerogenType[1]+GasPerInitTOC_III*RatioKerogenType[2]; //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
				  OilGenerated=OilGenerated_I*RatioKerogenType[0]+OilGenerated_II*RatioKerogenType[1]+OilGenerated_III*RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������
				  GasGenerated=GasGenerated_I*RatioKerogenType[0]+GasGenerated_II*RatioKerogenType[1]+GasGenerated_III*RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������

				  TR= (OilGenerated+GasGenerated)/ (HI_LLNL_I*RatioKerogenType[0]+HI_LLNL_II*RatioKerogenType[1]+HI_LLNL_III*RatioKerogenType[2]);
				  //����ת���ʵ��ڵ�λ����ԭʼ�л�̼�ۻ����ɵ��������������ָ��Ҹ�ԭʼ�л�̼����ָ�����Ը�����ռ�ı���
			  }
			  void Reactions(double TLast, double tLast, double T, double t,ParaLLNL *aParaLLNL)
			  {  // �����Ҹ���֡��͡������ı仯��û�а����ѽⲿ��
				  // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
				  //aParaLLNL Ϊ��һ��ʱ��εĲ����ṹ
				  //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
				  // ����ԭ������PetroMod��������Դ��BasinMod
				  TLast+=273;T+=273;   //ת��Ϊ�����¶�
				  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				  t=t*1000000*365*24*3600; //������ת��Ϊ��
				  //����ΪI�͸��Ҹ��Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil,FFLLNL_I_KToOil,ELLNL_I_KToOil,wBIw0_I_KToOil);  // I�͸��Ҹ������Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas,FFLLNL_I_KToGas,ELLNL_I_KToGas,wBIw0_I_KToGas);  // I�͸��Ҹ������Ƚ�
				  OilPerInitTOC_I=HI_LLNL_I*KToOilF_LLNL_I*(aParaLLNL->wBIw0_I_KToOil-wBIw0_I_KToOil);  // *KSF_LLNL_I
                  GasPerInitTOC_I=HI_LLNL_I*KToGasF_LLNL_I*(aParaLLNL->wBIw0_I_KToGas-wBIw0_I_KToGas); //*KSF_LLNL_I
                  OilGenerated_I=aParaLLNL->OilGenerated_I+OilPerInitTOC_I; //
                  GasGenerated_I=aParaLLNL->GasGenerated_I+GasPerInitTOC_I; //
                  TOCRemained_I=aParaLLNL->TOCRemained_I-W*OilPerInitTOC_I-W*GasPerInitTOC_I;
				  
				  //����ΪII�͸��Ҹ��Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil,FFLLNL_II_KToOil,ELLNL_II_KToOil,wBIw0_II_KToOil);  // II�͸��Ҹ������Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas,FFLLNL_II_KToGas,ELLNL_II_KToGas,wBIw0_II_KToGas);  // II�͸��Ҹ������Ƚ�
				  OilPerInitTOC_II=HI_LLNL_II*KToOilF_LLNL_II*(aParaLLNL->wBIw0_II_KToOil-wBIw0_II_KToOil);  //*KSF_LLNL_II
                  GasPerInitTOC_II=HI_LLNL_II*KToGasF_LLNL_II*(aParaLLNL->wBIw0_II_KToGas-wBIw0_II_KToGas);   //*KSF_LLNL_II
                  OilGenerated_II=aParaLLNL->OilGenerated_II+OilPerInitTOC_II; //
                  GasGenerated_II=aParaLLNL->GasGenerated_II+GasPerInitTOC_II; //
                  TOCRemained_II=aParaLLNL->TOCRemained_II-W*OilPerInitTOC_II-W*GasPerInitTOC_II;
				  
				  //����ΪIII�͸��Ҹ��Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil,FFLLNL_III_KToOil,ELLNL_III_KToOil,wBIw0_III_KToOil);  // III�͸��Ҹ������Ƚ�
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas,FFLLNL_III_KToGas,ELLNL_III_KToGas,wBIw0_III_KToGas);  // III�͸��Ҹ������Ƚ�
				  OilPerInitTOC_III=HI_LLNL_III*KToOilF_LLNL_III*(aParaLLNL->wBIw0_III_KToOil-wBIw0_III_KToOil);  //*KSF_LLNL_III
                  GasPerInitTOC_III=HI_LLNL_III*KToGasF_LLNL_III*(aParaLLNL->wBIw0_III_KToGas-wBIw0_III_KToGas);  //*KSF_LLNL_III
                  OilGenerated_III=aParaLLNL->OilGenerated_III+OilPerInitTOC_III; //
                  GasGenerated_III=aParaLLNL->GasGenerated_III+GasPerInitTOC_III; //
                  TOCRemained_III=aParaLLNL->TOCRemained_III-W*OilPerInitTOC_III-W*GasPerInitTOC_III;

				  OilPerInitTOC=OilPerInitTOC_I*RatioKerogenType[0]+OilPerInitTOC_II*RatioKerogenType[1]+OilPerInitTOC_III*RatioKerogenType[2];  //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
				  GasPerInitTOC=GasPerInitTOC_I*RatioKerogenType[0]+GasPerInitTOC_II*RatioKerogenType[1]+GasPerInitTOC_III*RatioKerogenType[2];  //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
				  OilGenerated=OilGenerated_I*RatioKerogenType[0]+OilGenerated_II*RatioKerogenType[1]+OilGenerated_III*RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������
				  GasGenerated=GasGenerated_I*RatioKerogenType[0]+GasGenerated_II*RatioKerogenType[1]+GasGenerated_III*RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������

				  TR= (OilGenerated+GasGenerated)/ (HI_LLNL_I*RatioKerogenType[0]+HI_LLNL_II*RatioKerogenType[1]+HI_LLNL_III*RatioKerogenType[2]);
				  //����ת���ʵ��ڵ�λ����ԭʼ�л�̼�ۻ����ɵ��������������ָ��Ҹ�ԭʼ�л�̼����ָ�����Ը�����ռ�ı���

			  }
			  double OilExisted; //ָ���Ǵ�����Դ���е������
			  double GasExisted; //ָ���Ǵ�����Դ���е������
			  double GasCracked;//ָ����ÿһ�����ѽ������
			  double GasCrackedAdded; //ָÿһ���ѽ������ۼ���
			  double ResidueCracked; // ָ����ÿһ�����ѽ�Ĳ�������
			  double ResidueCrackedAdded; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
			  double OilCracked;//ÿһ���͵��ѽ���
			  double OilCrackedAdded;//ÿһ���͵��ѽ������ۼ���
			  void OilCrackToGas(double TLast, double tLast, double T, double t)
			  {    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
				  //����ΪStrSeg�д��ڵ����ѽ�Ϊ���Ͳ�����Ĺ��̡������ǵ�һ��ʱ�䲽����ʼʱ��Դ���в�û���ͣ����ʵ������Щ��������Ϊ0��
				  TLast+=273;T+=273;   //ת��Ϊ�����¶�
				  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				  t=t*1000000*365*24*3600; //������ת��Ϊ��

				  double InitwBIw0_I_OilToGas=0,InitwBIw0_I_OilToResidue=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
				  for(int i=0;i<N_LLNL_I_OilToGas;i++)InitwBIw0_I_OilToGas+=fLLNL_I_OilToGas[i]; for(int i=0;i<N_LLNL_I_OilToResidue;i++)InitwBIw0_I_OilToResidue+=fLLNL_I_OilToResidue[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas,FFLLNL_I_OilToGas,ELLNL_I_OilToGas,wBIw0_I_OilToGas);  // I�͸��Ҹ�������ѽ�Ϊ��
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue,FFLLNL_I_OilToResidue,ELLNL_I_OilToResidue,wBIw0_I_OilToResidue);  // I�͸��Ҹ�������ѽ�Ϊ������
				  OilExisted=MassOfInitTOCTotal*(OSF_LLNL_I*RatioKerogenType[0]+OSF_LLNL_II*RatioKerogenType[1]+OSF_LLNL_III*RatioKerogenType[2])/W; //��ʼʱ�̵��͵�����ָ���ǵ�λԭʼ���Ҹ��е��͵�����
				  GasExisted=0.;    //��ʼʱ�̵ĺ�����Ϊ0
				  GasCracked=OilExisted*OToGasF_LLNL_I*(InitwBIw0_I_OilToGas-wBIw0_I_OilToGas);   //һ������£��ڳ�ʼʱ��OilExisted=0 , OSF_LLNL_I Ϊ��Ӧ����ͣ��ĳ�ʼ����Ҳ��0
				  ResidueCracked=OilExisted*OToResidueF_LLNL_I*(InitwBIw0_I_OilToResidue-wBIw0_I_OilToResidue);  //һ������£��ڳ�ʼʱ��OilExisted=0 , OSF_LLNL_I Ϊ��Ӧ����ͣ��ĳ�ʼ����Ҳ��0
				  OilCracked=GasCracked+ResidueCracked;
				  GasCrackedAdded=GasCracked;//�����ǵ�һ��ʱ�䲽��������ۻ��ѽ������ڳ�ʼ�ѽ�����
				  ResidueCrackedAdded=ResidueCracked;
				  OilCrackedAdded=OilCracked;
				  OilExisted =OilExisted +OilPerInitTOC*MassOfInitTOCTotal-OilCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���ɵ�������ȥ��ʱ�䲽�ѽ�ļ�������
				  GasExisted = GasExisted +GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���ɵ��������ϸ�ʱ�䲽�ѽ����ɵ�����
				  wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
				  for(int i=0;i<N_LLNL_I_OilToGas;i++) { wBIw0_I_OilToGas+=fLLNL_I_OilToGasBak[i]; }   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
				  for(int i=0;i<N_LLNL_I_OilToResidue;i++){ wBIw0_I_OilToResidue+=fLLNL_I_OilToResidueBak[i];}//ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
			  }
			  void OilCrackToGas(double TLast, double tLast, double T, double t,ParaLLNL *aParaLLNL)
			  {    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
				  //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
				  //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
				  TLast+=273;T+=273;   //ת��Ϊ�����¶�
				  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				  t=t*1000000*365*24*3600; //������ת��Ϊ��

				  for(int i=0;i<N_LLNL_I_OilToGas;i++) fLLNL_I_OilToGas[i]=fLLNL_I_OilToGasBak[i];  //������ÿ���ѽⶼ�����Ը��Ҹ������͵Ĳ��䣬���������ѽ���������£�������LLNLģ�ͣ����ѽ�Ļ��Ϊ��ֵ�������ڲ�ͬ��ֲܷ����͵Ļ�����⣬��˻�ѧ����ϵ������Ϊ��ʼֵ,
				  for(int i=0;i<N_LLNL_I_OilToResidue;i++) fLLNL_I_OilToResidue[i]=fLLNL_I_OilToResidueBak[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas,FFLLNL_I_OilToGas,ELLNL_I_OilToGas,wBIw0_I_OilToGas);  // ���ѽ�Ϊ��
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue,FFLLNL_I_OilToResidue,ELLNL_I_OilToResidue,wBIw0_I_OilToResidue);  // ���ѽ�Ϊ������
				  GasCracked=aParaLLNL->OilExisted*OToGasF_LLNL_I*(aParaLLNL->wBIw0_I_OilToGas-wBIw0_I_OilToGas);
				  ResidueCracked=aParaLLNL->OilExisted*OToResidueF_LLNL_I*(aParaLLNL->wBIw0_I_OilToResidue-wBIw0_I_OilToResidue);
				  OilCracked=GasCracked+ResidueCracked;
				  GasCrackedAdded=aParaLLNL->GasCrackedAdded+GasCracked;
				  ResidueCrackedAdded=aParaLLNL->ResidueCrackedAdded+ResidueCracked;
				  OilCrackedAdded=aParaLLNL->OilCrackedAdded+OilCracked;
				  OilExisted=aParaLLNL->OilExisted+OilPerInitTOC*MassOfInitTOCTotal-OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
				  GasExisted=aParaLLNL->GasExisted+GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
				  wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
				  for(int i=0;i<N_LLNL_I_OilToGas;i++) { wBIw0_I_OilToGas+=fLLNL_I_OilToGasBak[i]; }   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
				  for(int i=0;i<N_LLNL_I_OilToResidue;i++){ wBIw0_I_OilToResidue+=fLLNL_I_OilToResidueBak[i];}//ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
			  }
			  double MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
			  double MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
			  void GetMKer()
			  {   //���Դ���и��Ҹ����л�̼������
				  MKerInert=(KSF_LLNL_I-HI_LLNL_I*W)*MassOfInitTOC[0]+(KSF_LLNL_II-HI_LLNL_II*W)*MassOfInitTOC[1]+(KSF_LLNL_III-HI_LLNL_III*W)*MassOfInitTOC[2];
				  MKer=new double[NKerogenType];
				  MKer[0]=TOCRemained_I *MassOfInitTOC[0];  //�����л�̼�����������Գ�ʼ�л�̼����
				  MKer[1]=TOCRemained_II *MassOfInitTOC[1];
				  MKer[2]=TOCRemained_III *MassOfInitTOC[2];
				  MKerTotal=MKer[0]+MKer[1]+MKer[2];
				  MKerReac=MKerTotal-MKerInert;
			  }
			 
		 };

		 //
		 struct Organofacies
		 {
			 //����ΪPepper 1995 Simple kinetic models of petroleum formation.ϵ�������еĲ����͹�ʽ
			 //�����л��࣬��������ν�Ļ�ϸ��Ҹ�����˸��Ҹ����;���һ��
			 double W; //W = 0.85 kgC kgHC^-1  ,����λ�������ຬ�е�̼����   ������Cooles et al. (1986),���Ǽ򵥵ؼ������еĸ�ֵ��ΪW=0.85����
			 double InitTOC;//���Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
			 double MassOfInitTOCTotal; //���Ҹ�ԭʼ�л�̼�ܵ�����   �����ֻ��һ�����͸��Ҹ�����ñ�������һ���ظ�
			 //����Ϊ���Ҹ��Ķ���ѧ����
			 double TI0;  // TI0=S10/TOC0 �������ﶼ�����ʼ��TOC0=1�����TI0=S10�������λԭʼ�л�̼�ĵ�λ��g,��TI0��λ��mgHC/gTOC,�����λԭʼ�л�̼��λ��kg,��TI0��λ��gHC/kgTOC
			 double HI0; //���Ҹ��ĳ�ʼ��ָ����HI0=S20/TOC0����ָ��HI������λ�����л�̼���������������ָ���ṩ�˳����л����з�Ӧ���Ҹ�����Ը��Ҹ��ı���ָʾ��
			 double QI0; // QI0=(S10+S20)/TOC0
			 double PI0; //PI0=S10/(S10+S20)
			 double G0; //���Դ����ʼ���������Ҹ����ܵĳ�ʼ���ͺ��������Ҹ�֮�͵ı�ֵ����G, which is simply the PGC(Pyrolysis-gas chromatography)-derived mass fraction of gas in the S2 yield����ֵ���������KToGasF����KToOilF=1-KToGasF
			 // double KToGasF; //  ��Ч���Ҹ����������ı���
			 // double KToOilF;// ��Ч���Ҹ��������͵ı���
			 //  double KSF;//   Kerogen Start Fraction   ��Ӧ����Ҹ���ʼ�� ,����ʼʱ���л�̼�еĸ��Ҹ���̼�������������OSF�ǻ����Ĺ�ϵ����KSF=1-OSF
			 // double OSF; //Oil Strat Fraction ��Ӧ��������ʼ���� ������ʼʱ���л�̼���͵�̼��������TI0�Ĺ�ϵ�� OSF=W*TI0/1000
			 //  void GetKSFAndOSF() { OSF=W*TI0/1000.;KSF=1.-OSF;}  //����TI0ֵ���ԭʼ�л�̼�и��Ҹ����ֺͳ�ʼ�Ͳ��ֵ�̼����

			 double FFKToOil; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
			 double EmeanKToOil, SigmaKToOil; //�ֱ��Ǹ��Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��
			 int NKToOil;//���Ҹ����͵�ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
			 double *fKToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor����ͨ������̬�ֲ���ɢ���õ�
			 double *EKToOil;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�

			 double FFKToGas; //Frequency factor  ��Ƶ�����ӣ���A����λ��s^-1,Ϊ��ֵ
			 double EmeanKToGas, SigmaKToGas; //�ֱ��Ǹ��Ҹ������Ķ���ѧ������������̬�ֲ��ľ��ʺͱ�׼��
			 int NKToGas;//���Ҹ�������ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
			 double *fKToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor����ͨ������̬�ֲ���ɢ���õ�
			 double *EKToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�


			 double FFOilToGas; //Frequency factor
			 double EmeanOilToGas, SigmaOilToGas; //�ֱ������ѽ�Ϊ���Ķ���ѧ������������̬�ֲ��ľ��ʺͱ�׼��
			 int NOilToGas;//���ѽ�Ϊ����ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
			 double *fOilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor�� ��ͨ������̬�ֲ���ɢ���õ�
			 double *fOilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			 double *EOilToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�
			 double OToGasF; //���ѽ�Ϊ���ı���
			 // double OToResidueF; //���ѽ�Ϊ������ı�������� OToResidueF=1-OToGasF
			 /*   ���������̿�ⲿ�ֲ������г��ˣ��������ѽ�Ϊ���ĸ�����            */
			
			 double Jiecheng(int n) //n�Ľ׳�
			 {double temp=1; for(int i=0;i<n;i++) temp=temp*double(i+1); return temp; }
			 
			 double erf(double x)
			 {  //����
				 int N=30; //����ľ������
				 double pi=3.1415926535;  double temp=0;
				 for(int i=0;i<N+1;i++) temp+=pow(-1.,i)*pow(x,2*i+1)/(2*i+1)/Jiecheng(i);
				 temp=temp*2/sqrt(pi);
				 return temp;
			 }
			 
			 double Pnormal(double q,double Emean,double Sigma)
			 {//��̬�ֲ��ۻ����ʺ���ֵ����q������ Emean��4*Sigma�ķ�Χ�ڶ�����
				 double temp=(q-Emean)/Sigma/sqrt(2.);
				 return 0.5+0.5*erf(temp);
			 }
			 
			 void GetEachfAndE(int N, double aE,double aSigma,double *f,double *E)
			 { //���ݻ��������������̬�ֲ��ľ��ʺͱ�׼������ɢ�Ļ�ܺͶ�Ӧ�Ļ�ѧ����ϵ��
				 double LeftPoint, RightPoint; //���Ҷϵ��ֵ �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma
				 double Delta; //N�������ÿ������ľ��롪��ƽ����������
				 LeftPoint=aE-3.*aSigma; RightPoint=aE+3.*aSigma;
				 Delta=6.*aSigma/double(N);
				 for(int i=0;i<N;i++)
				 {
					 if(i==0)
					 {    //��������丳ֵ
						 E[i]=LeftPoint+0.5*Delta;//ȡ�����е�ֵ
						 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma); //��������ĸ���ֵȡֵΪ�������Ҷ�ֵ����˰����˸�����ֵ������������еĸ���ֵ
					 }
					 if(i>0&&i<N-1)
					 {   //�м�����丳ֵ
						 E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
						 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);
					 }
					 if(i==N-1)
					 {  //���ұ����丳ֵ
						 E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
						 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);   //��������ĸ���ֵȡֵΪ������ֵ�������ұ����еĸ���ֵ
					 }
				 }
			 }
			 void Normalization(int N,double *f)
			 {   //��ֵ��һ��
				 double Sum=0.;
				 for(int i=0;i<N;i++) Sum+=f[i];
				 for(int i=0;i<N;i++) f[i]=f[i]/Sum;
			 }

			 Organofacies()
			 {
				 Init();
			 }

			 void Init()
			 {
				 W = 0.; 
				 InitTOC = 0.;
				 MassOfInitTOCTotal = 0.;
				 
				 TI0 = 0.;  
				 HI0 = 0.;
				 QI0 = 0.;
				 PI0 = 0.;
				 G0 = 0.;
				 
				 FFKToOil = 0.;
				 EmeanKToOil = 0.;
				 SigmaKToOil = 0.;				 
				 NKToOil = 0;
				 fKToOil = 0;
				 EKToOil = 0;

				 FFKToGas = 0.;
				 EmeanKToGas = 0.;
				 SigmaKToGas = 0.;
				 NKToGas = 0;
				 fKToGas = 0;
				 EKToGas = 0;
				 
				 FFOilToGas = 0.;
				 EmeanOilToGas = 0.;
				 SigmaOilToGas = 0.;
				 NOilToGas = 0;
				 fOilToGas = 0;
				 fOilToGasBak = 0;
				 EOilToGas = 0;
				 OToGasF = 0.;

				 wBIw0KToOil = 0.;
				 wBIw0KToGas = 0.;
				 wBIw0OilToGas = 0.;
				 wBIw0K = 0.;

				 OilPerInitTOC = 0.;
				 GasPerInitTOC = 0.;
				 TOCReactableKerogen = 0.;
				 TOCInertKerogen = 0.;
				 TOCKerogen = 0.;
				 TOCRemained = 0.;
				 OilGenerated = 0.;
				 GasGenerated = 0.;
				 TR = 0.;

				 //
				 OilExisted = 0.;
				 GasExisted = 0.;
				 ResidueExisted = 0.;
				 GasCracked = 0.;
				 GasCrackedAdded = 0.;
				 ResidueCracked = 0.;
				 ResidueCrackedAdded = 0.;
				 OilCracked = 0.;
				 OilCrackedAdded = 0.;

				 //
				 MKerTotal = 0.;
				 MKerReac = 0.;
				 MKerInert = 0.;
			 }

			 void Release()
			 {
				 DoRelease(fKToOil);
				 DoRelease(EKToOil);

				 DoRelease(fKToGas);
				 DoRelease(EKToGas);

				 DoRelease(fOilToGas);
				 DoRelease(fOilToGasBak);
				 DoRelease(EOilToGas);
			 }

			 void DoRelease(double *&val)
			 {
				 if (val)
				 {
					 delete val;
				 }
				 val = 0;
			 }

			 void Construct(double aOToGasF,double aW, double aTI0,double aHI0,double aG0,double aFFKToOil,double aEmeanKToOil, double aSigmaKToOil,double aFFKToGas,double aEmeanKToGas, double aSigmaKToGas,
				 double aFFOilToGas,double aEmeanOilToGas, double aSigmaOilToGas )//int aTypeOfOrganofacies, double aQI0, double aPI0,,double aOToResidueF
			 {
				 Release();

				 OToGasF=aOToGasF; //���ѽ�Ϊ���ı���
				 W=aW; TI0=aTI0; HI0=aHI0; /*QI0=aQI0; PI0=aPI0;*/ G0=aG0;
				 FFKToOil=aFFKToOil; EmeanKToOil=aEmeanKToOil; SigmaKToOil=aSigmaKToOil; FFKToGas=aFFKToGas; EmeanKToGas=aEmeanKToGas; SigmaKToGas=aSigmaKToGas;
				 FFOilToGas=aFFOilToGas; EmeanOilToGas=aEmeanOilToGas; SigmaOilToGas=aSigmaOilToGas; //OToResidueF=aOToResidueF;
				 NKToOil=21; //��������̫�ֲ��ֳ�21�����䣬��������ֵλ����һ�����䣬�������߶ԳƵطֱ�ֲ���10���� �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma ��������0.9974�ĸ������䣩
				 fKToOil=new double[NKToOil]; EKToOil=new double[NKToOil];
				 GetEachfAndE(NKToOil, EmeanKToOil,SigmaKToOil,fKToOil,EKToOil); Normalization(NKToOil,fKToOil);
				 //for(int i=0;i<NKToOil;i++)ShowMessage("fkToOil="+FloatToStr(fKToOil[i]));
				 NKToGas=21; //��������̫�ֲ��ֳ�21�����䣬��������ֵλ����һ�����䣬�������߶ԳƵطֱ�ֲ���10���� �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma ��������0.9974�ĸ������䣩
				 fKToGas=new double[NKToGas]; EKToGas=new double[NKToGas];
				 GetEachfAndE(NKToGas, EmeanKToGas,SigmaKToGas,fKToGas,EKToGas); Normalization(NKToGas,fKToGas);
				 NOilToGas=21; //��������̫�ֲ��ֳ�21�����䣬��������ֵλ����һ�����䣬�������߶ԳƵطֱ�ֲ���10���� �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma ��������0.9974�ĸ������䣩
				 fOilToGas=new double[NOilToGas]; EOilToGas=new double[NOilToGas];
				 GetEachfAndE(NOilToGas, EmeanOilToGas,SigmaOilToGas,fOilToGas,EOilToGas);Normalization(NOilToGas,fOilToGas);
				 fOilToGasBak=new double[NOilToGas]; for(int i=0;i<NOilToGas;i++) fOilToGasBak[i]=fOilToGas[i];
				 // GetKSFAndOSF();
			 }
			 void CopyFrom(Organofacies *aOrganofacies)
			 {   
				 if (!aOrganofacies)
				 {
					 return;
				 }

				 //
				 Release();
				 
				 //����һ���ṹ�п���һ�ݲ���
				 OToGasF=aOrganofacies->OToGasF; //���ѽ�Ϊ���ı���
				 W=aOrganofacies->W; TI0=aOrganofacies->TI0; HI0=aOrganofacies->HI0; G0=aOrganofacies->G0;
				 //QI0=aOrganofacies->QI0; PI0=aOrganofacies->PI0;
				 FFKToOil=aOrganofacies->FFKToOil; EmeanKToOil=aOrganofacies->EmeanKToOil; SigmaKToOil=aOrganofacies->SigmaKToOil;
				 FFKToGas=aOrganofacies->FFKToGas; EmeanKToGas=aOrganofacies->EmeanKToGas; SigmaKToGas=aOrganofacies->SigmaKToGas;
				 FFOilToGas=aOrganofacies->FFOilToGas; EmeanOilToGas=aOrganofacies->EmeanOilToGas; SigmaOilToGas=aOrganofacies->SigmaOilToGas;// OToResidueF=aOrganofacies->OToResidueF;
				 NKToOil=aOrganofacies->NKToOil;
				 fKToOil=new double[NKToOil]; EKToOil=new double[NKToOil];
				 for(int i=0;i<NKToOil;i++) {fKToOil[i]=aOrganofacies->fKToOil[i];EKToOil[i]=aOrganofacies->EKToOil[i];}
				 //GetEachfAndE(NKToOil, EmeanKToOil,SigmaKToOil,fKToOil,EKToOil);
				 NKToGas=aOrganofacies->NKToGas;
				 fKToGas=new double[NKToGas]; EKToGas=new double[NKToGas];
				 for(int i=0;i<NKToGas;i++) {fKToGas[i]=aOrganofacies->fKToGas[i];EKToGas[i]=aOrganofacies->EKToGas[i];}
				 //GetEachfAndE(NKToGas, EmeanKToGas,SigmaKToGas,fKToGas,EKToGas);
				 NOilToGas=aOrganofacies->NOilToGas;
				 fOilToGas=new double[NOilToGas];fOilToGasBak=new double[NOilToGas]; EOilToGas=new double[NOilToGas];
				 for(int i=0;i<NOilToGas;i++) {fOilToGas[i]=aOrganofacies->fOilToGas[i];fOilToGasBak[i]=aOrganofacies->fOilToGasBak[i];EOilToGas[i]=aOrganofacies->EOilToGas[i];}
				 //GetEachfAndE(NOilToGas, EmeanOilToGas,SigmaOilToGas,fOilToGas,EOilToGas);
				 //  KSF=aOrganofacies->KSF;  OSF=aOrganofacies->OSF;
			 }

			 double wBIw0KToOil,  wBIw0KToGas, wBIw0OilToGas;//�ֱ����͸��Ҹ��������͡������Լ����ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
			 double wBIw0K; //���Ҹ� �ܵ�ʣ�໯ѧ����ϵ����ԭʼΪ1��ͨ�����Ҹ��������͡����������µ��ܵ�ʣ�໯ѧ����ϵ���ֱ���Ը��Ҹ������͵ı��ʺ��������ı���֮����Ӷ��õ���
			 void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,double *fLLNL,double FFLLNL, double *ELLNL,double &wBIw0)
			 {  //�ֱ�����һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma����
				 // ƽ�з�Ӧ����N_LLNL����ѧ����ϵ��fLLNL,Ƶ������FFLLNL�����ELLNL,�ܵ�ʣ�໯ѧ����ϵ��wBIw0
				 wBIw0=0.;
				 //double R=0.001986;//���峣�� ����λ Kcal/(mol*K)
				 double R=0.008314472; //���峣�� KJ/(mol*K)
				 //������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
				 double a,b; // ���Ա仯��ϵ��
				 a=(T-TLast)/(t-tLast);b=T-a*t;
				 //����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
				 int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
				 double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
				 double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
				 double temp=0;
				 double *wiBIw0i;  //wi/w0i ,�����EasyRo�Ƶ��еĹ�ʽ��8��
				 wiBIw0i=new double[N_LLNL];
				 for(int i=0;i<N_LLNL;i++)
				 {
					 for(int j=0;j<N;j++)
					 {
						 tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
						 temp+=(-FFLLNL*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
						 tt1=tt2;
					 }
					 wiBIw0i[i]=exp(temp);
					 fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //������һʱ��εĻ�ѧ����ϵ��
					 wBIw0+=fLLNL[i];  // wBIw0Ϊ�ܵĻ�ѧ����ϵ��ʣ��ֵ
					 tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
					 temp=0;    //temp���¹���
				 }

				 //release
				 delete wiBIw0i;
			 }

			 double OilPerInitTOC; //��λ����ԭʼ�л�̼��InitTOC������һʱ��ε�������
			 double GasPerInitTOC; //��λ����ԭʼ�л�̼��InitTOC������һʱ��ε�������
			 double TOCReactableKerogen, TOCInertKerogen; //�ֱ��ǿɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ� ����ָ��λԭʼ�л�̼���ڳ�ʼ״̬�Լ���Ӧ�����пɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ�������
			 double TOCKerogen; //���Ҹ��л�̼ʣ���� ����ָ��λ����ԭʼ���Ҹ��Ĳ�����
			 double TOCRemained; //�����л�̼ʣ���� ����ָ��λ����ԭʼ�л�̼���ݻ������еĲ����� ���������Ҹ��л�̼ʣ���� +Դ�����������л�̼����+���ѽ�����Ľ�̿��
			 double OilGenerated,GasGenerated; //���Ҹ���λ����ԭʼ�л�̼�ۼƵ���������������
			 double TR; //Դ�ҵ�����ת����, ��ԭʼ�ɽ�����Ҹ��л�̼ת��Ϊ�ͺ����е��л�̼����
			 void Reactions(double TLast, double tLast, double T, double t)
			 {  //���ʱ���ϵ�һ���ز��
				 // ���л�̼���͡������ı仯��û�а����ѽⲿ��
				 // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
				 //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
				 // ����ԭ������PetroMod��������Դ��Pepper��1995

				 TLast+=273;T+=273;   //ת��Ϊ�����¶�
				 tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				 t=t*1000000*365*24*3600; //������ת��Ϊ��
				 //����ΪI�͸��Ҹ��Ƚ�
				 double InitwBIw0KToOil=0,InitwBIw0KToGas=0;  //��ʼʱ�̵ĸ��Ҹ���֣���ѧ����ϵ����֮��
				 for(int i=0;i<NKToOil;i++)InitwBIw0KToOil+=fKToOil[i]; for(int i=0;i<NKToGas;i++)InitwBIw0KToGas+=fKToGas[i];
				 FirstOrderReaction(TLast, tLast,T,t,NKToOil,fKToOil,FFKToOil,EKToOil,wBIw0KToOil);  // ���Ҹ������Ƚ�
				 FirstOrderReaction(TLast, tLast,T,t,NKToGas,fKToGas,FFKToGas,EKToGas,wBIw0KToGas);  // ���Ҹ������Ƚ�
				 OilPerInitTOC=HI0*(1.-G0)*(InitwBIw0KToOil-wBIw0KToOil)/1000.; //   //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������   OilPerInitTOC=HI0*(InitwBIw0KToOil-wBIw0KToOil)*KSF*(1.-G0);
				 GasPerInitTOC=HI0*G0*(InitwBIw0KToGas-wBIw0KToGas)/1000.;       //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������  //       GasPerInitTOC=HI0*(InitwBIw0KToGas-wBIw0KToGas)*KSF*G0;
				 OilGenerated=OilPerInitTOC+TI0/1000.; //  //���Ҹ���λ����ԭʼ�л�̼�ۼƵ��������������ڳ�ʼ��������ۻ�������Ϊ�ò������������ʼʱ�̴��ڵ�����֮��
				 GasGenerated=GasPerInitTOC; // //���Ҹ���λ����ԭʼ�л�̼�ۼƵ����������� ��û�г�ʼ�Ĵ���������˳�ʼ�����ۻ����������Ǹò���������
				 TOCKerogen=1.-W*TI0/1000.-W*OilPerInitTOC- W*GasPerInitTOC;  //��ָ���Ҹ��е��л�̼���� ,��Ҫ��ԭʼ��λ�л�̼-��ʼ���ڵ����������л�̼-�ò����ɵ��ͺ����е��л�̼
				 TOCRemained=TOCKerogen; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
				 // TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //Դ����ʣ����л�̼Ϊ���Ҹ��л�̼�������Դ�����ͺ����е��л�̼�Լ����ѽ�Ϊ��֮̿�� ,������Ҫ���ѽ��������ſ�֪�� �������ʽ�Ӳ����ã���ΪOilExisted���ܵ�������StrSeg���ܵĴ��ڵ��͵����������������� Reactions(...)����ʱ����ֵ��δ֪
				 TOCInertKerogen=1.-W*TI0/1000.-W*HI0/1000.;   //���Ը��Ҹ�����
				 TOCReactableKerogen=TOCKerogen-TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����
				 TR= (OilGenerated-TI0/1000.+GasGenerated)/(HI0/1000.);
				 //����ת���ʵ��ڵ�λ����ԭʼ�л�̼�ۻ����ɵ����������Ե�λ����ԭʼ�л�̼����ָ��
			 }
			 void Reactions(double TLast, double tLast, double T, double t,Organofacies *aOrganofacies)
			 {  // �����Ҹ���֡��͡������ı仯��û�а����ѽⲿ��
				 // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
				 //aOrganofaciesΪ��һ��ʱ��εĲ����ṹ
				 //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
				 // ����ԭ������PetroMod��������Դ��BasinMod
				 TLast+=273;T+=273;   //ת��Ϊ�����¶�
				 tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				 t=t*1000000*365*24*3600; //������ת��Ϊ��
				 //����Ϊ���Ҹ��Ƚ�
				 //wBIw0KToOil=aOrganofacies->wBIw0KToOil;wBIw0KToGas=aOrganofacies->wBIw0KToGas;
				 FirstOrderReaction(TLast, tLast,T,t,NKToOil,fKToOil,FFKToOil,EKToOil,wBIw0KToOil);  // ���Ҹ������Ƚ�
				 FirstOrderReaction(TLast, tLast,T,t,NKToGas,fKToGas,FFKToGas,EKToGas,wBIw0KToGas);  // ���Ҹ������Ƚ�
				 OilPerInitTOC=HI0*(1.-G0)*(aOrganofacies->wBIw0KToOil-wBIw0KToOil)/1000.;
				 GasPerInitTOC=HI0*G0*(aOrganofacies->wBIw0KToGas-wBIw0KToGas)/1000.;;
				 OilGenerated=aOrganofacies->OilGenerated+OilPerInitTOC; //
				 GasGenerated=aOrganofacies->GasGenerated+GasPerInitTOC; //
				 TOCKerogen=aOrganofacies->TOCKerogen-W*OilPerInitTOC-W*GasPerInitTOC; //��ָ���Ҹ��е��л�̼���� ,��Ҫ��ԭʼ��λ�л�̼-��ʼ���ڵ����������л�̼-�Ѿ��ۼ����ɵ��ͺ����е��л�̼
				 TOCRemained=TOCKerogen; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
				 //TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //Դ����ʣ����л�̼Ϊ���Ҹ��л�̼�������Դ�����ͺ����е��л�̼֮�� ,������Ҫ���ѽ��������ſ�֪��
				 TOCInertKerogen=1.-W*TI0/1000.-W*HI0/1000.;   //���Ը��Ҹ�����
				 TOCReactableKerogen=TOCKerogen-TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����,��ָ��λԭʼ�л�̼������Ӧ����
				 TR= (OilGenerated-TI0/1000.+GasGenerated)/(HI0/1000.);
			 }

			 //���������ѽ��йصĶ��Ƕ�Ӧ����������ԭʼ�л�̼������
			 double OilExisted; //ָ���Ǵ�����Դ���е������
			 double GasExisted; //ָ���Ǵ�����Դ���е������
			 double ResidueExisted; //ָ������Դ���е����ѽ�Ϊ��������
			 double GasCracked;//ָ����ÿһ�����ѽ������
			 double GasCrackedAdded; //ָÿһ���ѽ������ۼ���
			 double ResidueCracked; // ָ����ÿһ�����ѽ�Ĳ�������
			 double ResidueCrackedAdded; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
			 double OilCracked;//ÿһ���͵��ѽ���
			 double OilCrackedAdded;//ÿһ���͵��ѽ������ۼ���
			 void GetfOilToGas()
			 {  //��õ�һ�������ѽ�Ϊ���Ļ�ѧ����ϵ��������Դ���в�ͬ��Դ�͵ı��ʼ��㣻
				 //��Ϊ��һ���ĸ��Ҹ��������Լ���һ�����ѽ�Ϊ��ʣ�����������������֮��ı���ȷ����ͬ��ѧ����ϵ������ռ�ı���
				 double RatioKerogenOil,RatioCrackLeftedOil; //�ֱ�����һ�����Ҹ����ɵ��ͺ��ѽ�ʣ�������ռ�ı���
				 double SumfOilToGas=0.;
				 RatioKerogenOil=OilPerInitTOC*MassOfInitTOCTotal/OilExisted;
				 RatioCrackLeftedOil=(MassOfInitTOCTotal*TI0/1000.-OilCracked)/OilExisted;
				 for(int i=0;i<NOilToGas;i++) fOilToGas[i]=fOilToGasBak[i]*RatioKerogenOil+fOilToGas[i]*RatioCrackLeftedOil;
				 wBIw0OilToGas=1.;   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ
			 }

			 void OilCrackToGas(double TLast, double tLast, double T, double t)
			 {    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
				 //����ΪStrSeg�д��ڵ����ѽ�Ϊ���Ͳ�����Ĺ��̡������ǵ�һ��ʱ�䲽����ʼʱ��Դ���д���ԭʼ����
				 TLast+=273;T+=273;   //ת��Ϊ�����¶�
				 tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				 t=t*1000000*365*24*3600; //������ת��Ϊ��
				 double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
				 for(int i=0;i<NOilToGas;i++)InitwBIw0OilToGas+=fOilToGas[i];//��ֵӦ�õ���1
				 FirstOrderReaction(TLast, tLast,T,t,NOilToGas,fOilToGas,FFOilToGas,EOilToGas,wBIw0OilToGas);  // ���Ҹ�������ѽ�Ϊ��
				 OilExisted=MassOfInitTOCTotal*TI0/1000.;   //��ʼ��λ����Դ���ڵ��ʹ����� ������ԭʼ�л�̼��������TI0ֵ
				 GasExisted=0.;
				 GasCracked=OilExisted*OToGasF*(InitwBIw0OilToGas-wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ���� TI0/1000����OToGasFΪ��ת��Ϊ���ı�����
				 ResidueCracked=OilExisted*(1.-OToGasF)*(InitwBIw0OilToGas-wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
				 OilCracked=GasCracked+ResidueCracked;
				 GasCrackedAdded=GasCracked;//�����ǵ�һ��ʱ�䲽��������ۻ��ѽ������ڳ�ʼ�ѽ�����
				 ResidueCrackedAdded=ResidueCracked;
				 OilCrackedAdded=OilCracked;
				 OilExisted=OilExisted+OilPerInitTOC*MassOfInitTOCTotal-OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
				 GasExisted =GasExisted+GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
				 GetfOilToGas();
			 }
			 void GetfOilToGas(Organofacies *aOrganofacies)
			 {  //���ÿһ�������ѽ�Ϊ���Ļ�ѧ����ϵ��������Դ���в�ͬ��Դ�͵ı��ʼ��㣻
				 //��Ϊÿһ���ĸ��Ҹ��������Լ���һ�����ѽ�Ϊ��ʣ�����������������֮��ı���ȷ����ͬ��ѧ����ϵ������ռ�ı���
				 double RatioKerogenOil,RatioCrackLeftedOil; //�ֱ�����һ�����Ҹ����ɵ��ͺ��ѽ�ʣ�������ռ�ı���
				 double SumfOilToGas=0.;
				 RatioKerogenOil=OilPerInitTOC*MassOfInitTOCTotal/OilExisted;
				 RatioCrackLeftedOil=(aOrganofacies->OilExisted-OilCracked)/OilExisted;
				 Normalization(NOilToGas,fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
				 for(int i=0;i<NOilToGas;i++) fOilToGas[i]=fOilToGasBak[i]*RatioKerogenOil+fOilToGas[i]*RatioCrackLeftedOil;
				 wBIw0OilToGas=1.;   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ
			 }
			 void OilCrackToGas(double TLast, double tLast, double T, double t,Organofacies *aOrganofacies)
			 {    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
				 //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
				 //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
				 TLast+=273;T+=273;   //ת��Ϊ�����¶�
				 tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				 t=t*1000000*365*24*3600; //������ת��Ϊ��
				 FirstOrderReaction(TLast, tLast,T,t,NOilToGas,fOilToGas,FFOilToGas,EOilToGas,wBIw0OilToGas);  // ���ѽ�Ϊ��
				 GasCracked=aOrganofacies->OilExisted*OToGasF*(aOrganofacies->wBIw0OilToGas-wBIw0OilToGas);
				 ResidueCracked=aOrganofacies->OilExisted*(1.-OToGasF)*(aOrganofacies->wBIw0OilToGas-wBIw0OilToGas);
				 OilCracked=GasCracked+ResidueCracked;
				 GasCrackedAdded=aOrganofacies->GasCrackedAdded+GasCracked;
				 ResidueCrackedAdded=aOrganofacies->ResidueCrackedAdded+ResidueCracked;
				 OilCrackedAdded=aOrganofacies->OilCrackedAdded+OilCracked;
				 OilExisted=aOrganofacies->OilExisted+OilPerInitTOC*MassOfInitTOCTotal-OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
				 GasExisted=aOrganofacies->GasExisted+GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
				 GetfOilToGas(aOrganofacies);
			 }
			 double MKerTotal; //�ܵĸ��Ҹ��л�̼�����������������ѽ�Ľ�̿���� ���¼���20170908
			 double MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
			 double MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
			 void GetMKer()
			 {   //���Դ���и��Ҹ����л�̼������
				 MKerTotal=TOCKerogen*MassOfInitTOCTotal;
				 MKerInert=TOCInertKerogen*MassOfInitTOCTotal;
				 MKerReac= MKerTotal-MKerInert;
			 }

		 };

		struct Str  //����һ���ز㡢�����ʴ�ṹ
		{
			int LithNumber;  //�ز���������
			double *LithRatio;  //�ز������Ա���
			int Property; //�ز������ ��1Ϊ�ز㣬2Ϊ��㣬3Ϊ��ʴ
			double BeginAge; // �ز㡢�����ʴ��ʼʱ��
			double EndAge;// // �ز㡢�����ʴ����ʱ��

			double CurrentThickness;// �ֽ�ز㡢�����ʴ���
			double MaxBuryTopDepth; //����������
			double MaxBuryBottomDepth;//����������

			double Thickness;// �ز㡢�����ʴ���
			double TopDepth; //������ȣ�û������ˮ��
			double BottomDepth;//������� ��û������ˮ��

			int  ConnectingMarker; //��ʴ������������������
			int *VirtualErosionPair; //���StrSeg�����Ӧ�İ�ʴStrSeg�����ԣ�
			int StrSegNumber; //ÿ���ز���¼������ĵز������
			double CurrentStrSegThickness;  //����ĵز���ֽ���ڵĺ�ȣ�ÿ��StrSeg����
			double *CurrentSST;  //�������ʾ�ĵز���ÿ���ز�εĺ�ȣ���Ȼ���ڵز�������֣�ÿ��CurrentSST[]��ֵ��ͬ��
								//�����ڰ�ʴ�¼������Ӧ�������ܲ�ֹһ����ÿ������CurrentStrSegThickness����һ�£�����������ʾ����һЩ
			double MatrixThickness;  //�Ǽܺ��

			bool SourceRock; //�����ж��Ƿ�ΪԴ��
			double TOC; //  Դ���л�̼����

			Str()
			{
				Init();
			}

			void Init()
			{
				LithNumber = 0;  //�ز���������
				LithRatio = 0;  //�ز������Ա���
				Property = 0; //�ز������ ��1Ϊ�ز㣬2Ϊ��㣬3Ϊ��ʴ
				BeginAge = 0.; // �ز㡢�����ʴ��ʼʱ��
				EndAge = 0.; // // �ز㡢�����ʴ����ʱ��

				CurrentThickness = 0.;// �ֽ�ز㡢�����ʴ���
				MaxBuryTopDepth = 0.; //����������
				MaxBuryBottomDepth = 0.;//����������

				Thickness = 0.;// �ز㡢�����ʴ���
				TopDepth = 0.; //������ȣ�û������ˮ��
				BottomDepth = 0.;//������� ��û������ˮ��

				ConnectingMarker = 0; //��ʴ������������������
				VirtualErosionPair = 0; //���StrSeg�����Ӧ�İ�ʴStrSeg�����ԣ�
				StrSegNumber = 0; //ÿ���ز���¼������ĵز������
				CurrentStrSegThickness = 0.;  //����ĵز���ֽ���ڵĺ�ȣ�ÿ��StrSeg����
				CurrentSST = 0;  //�������ʾ�ĵز���ÿ���ز�εĺ�ȣ���Ȼ���ڵز�������֣�ÿ��CurrentSST[]��ֵ��ͬ��
				//�����ڰ�ʴ�¼������Ӧ�������ܲ�ֹһ����ÿ������CurrentStrSegThickness����һ�£�����������ʾ����һЩ
				MatrixThickness = 0.;  //�Ǽܺ��

				SourceRock = false; //�����ж��Ƿ�ΪԴ��
				TOC = 0.; //  Դ���л�̼����
			}

			void Release()
			{
				if (LithRatio)
				{
					delete LithRatio;
				}
				LithRatio = 0;

				//
				if (VirtualErosionPair)
				{
					delete VirtualErosionPair;
				}
				VirtualErosionPair = 0;
				
				//
				if (CurrentSST)
				{
					delete CurrentSST;
				}
				CurrentSST = 0;
			}


			void CopyMaxDepthToDepth()
			{ //����MaxTopThickness,MaxBottomDepth��TopDepth ��BottomDepth
				TopDepth=MaxBuryTopDepth;
				BottomDepth=MaxBuryBottomDepth;
				Thickness=CurrentThickness;
			}

		};

		struct StrSeg
		{    
			//LLNL/Organo
			PetroGenStyle aPetroGenStyle;			
			
			//����һ���ز���ࣻ�Ǹ��ز��ϸ�ֶ� ��Ҳ������һ���¼������ʴ���Ѵ��ڹ��ĵز�
			//--------------------------------------------���ֵ�ֵ�Ĳ���
			int pos_i,pos_j,pos_k; //��¼�õز������ά�����е�����
			int EndPoint; //��¼�ز�����һ��ʱ������ά�����е�����

			double MarginOfErrorThickness; //�ж�����ʴ������ݴ������
			double Ma2Second;

			int LithNumber;   //������Եĸ���
			double *LithRatio; //������Եı��� ���ز�εĸ��������������ݻ�����Եı���������

			double BeginAge; //�ز�ο�ʼʱ��
			double EndAge;   //�ز�ν���ʱ��
			double MiddleAge;//�ز���м�ʱ��
			double DeltaAge; //�ز�λ��¼��ľ���ʱ��

			int Property;   //�ز�����ʣ�1�ǵز㣬2����㣬3�ǰ�ʴ��4�������
			int ConnectingMarker;  //���Ͱ�ʴ�¼��Ĺ������
			int VirtualErosionPair; //���StrSeg�����Ӧ�İ�ʴStrSeg�����ԣ������������ÿһ�����StrSeg��VirtualErosionPairֵ��Ψһ�Ķ�Ӧ��һ����ʴ�¼���StrSeg��VirtualErosionPairֵ��ͬ��
			bool Eroded; //�����ж�������Ƿ��Ѿ�����ʴ���ˣ���ʼ��ֵʱ����false
			bool SourceRock; //�����ж��Ƿ�ΪԴ��
			bool *IsThisMatrixKerogenOrCoal; //�жϻ��������Ƿ�Ϊ���Ҹ���ú

			double MaxBuryMiddleDepth; //�ز�ξ������������в����
			double MaxBuryTopDepth;    //�ز�ξ����������ض������
			double MaxBuryBottomDepth; //�ز�ξ����������صײ����
			double TopDepth; //�������  ��ָ���Ǽ����˹�ˮ��Ķ������
			double BottomDepth;//�������
			double MiddleDepth;//�в����
			double BuryTopDepth; //���������� �������ˮ�ֻ�ǳ��������ȣ��ӳ�����-ˮ������������
			double BuryBottomDepth;//����������
			double BuryMiddleDepth;//�в�������
			double CurrentThickness;//�ֽ�ĺ��(������ز�)����ʴ���Ϊ��  ;�ز�������ֽ�ĺ�ȼ���Ӧ�������ȵĺ��
			double Thickness; //���
			double MatrixThickness;//�Ǽܺ��
			//������Щѹ���ĵ�λ�����ù��ʵ�λ�ƣ���˹��
			double Pt,Pm,Pb; //�ز�ζ������в��͵ײ�����ѹ��
			double Ut,Um,Ub; //�ֱ�Ϊ�������в��͵ײ������峬ѹ
			double StaticPt,StaticPm,StaticPb; //�ز�ζ������в��͵ײ�������ѹ��
			double Plt,Plm,Plb; //����ѹ��,�ֱ���StrSeg�������в����͵ײ��ľ���ѹ��
			double Ult,Ulm,Ulb; //��������,�ֱ���StrSeg�������в����͵ײ��ľ�������
			double EffectiveStresst,EffectiveStressm, EffectiveStressb; //��ЧӦ�����ֱ���StrSeg�������в����͵ײ���
			double MaxEffectiveStresst,MaxEffectiveStressm,MaxEffectiveStressb;  //��¼StrSeg�����������ЧӦ��

			double COC;//ѹ��ϵ�� Coefficient Of Compressibility
			double aOverpressure,bOverpressure,cOverpressure; //��ѹ�����е���������

			double vFluild; //���������ٶȣ���һ����û�õ�
			double vWater; //�ز�ˮ����

			double *InitialPorosity,*CompactionFactor;  //��ʼ��϶�Ⱥ͹��ھ�ˮѹ����ȵ�Athy���ɵ�ѹʵϵ�� kArthDepth
			double TInitialPorosity,TCompactionFactor;  //��ϵ�����ĳ�ʼ��϶�Ⱥ�ѹʵϵ��
			double *Porosityt; //��������ԵĿ�϶�ȣ���϶��ΪС��;;����ֵ
			double *Porositym;  // ��������ԵĿ�϶�ȣ���϶��ΪС��;;�в�ֵ
			double *Porosityb;  // ��������ԵĿ�϶�ȣ���϶��ΪС��;;�ײ�ֵ
			double Porot,Porom,Porob; //Ϊ�����в��͵׵Ŀ�϶�� ��С��
			double EndPorom; //�ֽ�ز�Ŀ�϶��ֵ����������ڰ�ʴǰ��С�Ŀ�϶��ֵ�����ڱȽϵ���ǰ���϶�����ж��Ƿ����������ڳ�ѹ����
			double DifferencePoromEndPorom; //��������յĿ�϶��ֵ����һ�ε��������ʼ���Ŀ�϶�Ȳ�ֵ
			double *LogPermeability; //��������Ե���͸����Ȼ����ֵ,��λ��LogmD
			double Perm; // �ܵ���͸�� Permeability�� ��λ��m^2
			Poro_Perm *aPoro_Perm; //��϶��-��͸�ʹ�ϵ���ݶ�

			//=================ճ�ȡ������͸�ʡ�����������ë��ѹ��========��ʼ
			double WaterViscosity;  //ˮճ��
			double OilViscosity; //��ճ��
			double GasViscosity; //��ճ��
			double Sw,So,Sg; //ˮ���͡����ı��Ͷ�  ,��С����ʾ
			double Swc,Soc,Sgc; // ����ˮ���Ͷȡ������ͱ��Ͷ� �����������Ͷ�    ,��С����ʾ
			double Swe; //effective saturations Se��Чˮ���Ͷ�for krw and krow,       ,��С����ʾ
			double Soe; // ��Ч�ͱ��Ͷ� ,��ʱû������    ,��С����ʾ
			double Sgoe; //����Krog����Ч���Ͷ�  ,��С����ʾ
			double Sge; // ��Ч�����Ͷ�,����Krg   ,��С����ʾ
			void GetSe() //�����Чˮ���͡�����Ч���Ͷ�  ,��С����ʾ
			{
				Sw=0.5; So=0.3;Sg=0.2;   //��ʱ������ֵ��������
				Swc=0;Soc=0;Sgc=0; //��ʱ��ģ���н���Щ��������Ϊ0
				Swe = (Sw-Swc)/(1.-Swc-Soc);
				Soe = (So-Soc)/(1.-Swc-Soc);
				Sgoe=Sg/(1.-Swc);
				Sge = (Sg-Sgc)/(1.-Swc-Sgc);
			} //
			double Krow,Krog; //
			double Krw,Krg,Kro; //�ֱ���ˮ�������͵������͸��
			double lamuda; // a parameter �� which describes a "sorting" of the rock. It can vary between 0 and ��. A small value indicates a poorly sorted (inhomogeneous) rock (Sylta, 2002a; Ataie-Ashtiani et al., 2002).
		/*  void GetKr()  //����͡�����ˮ�������͸��
			{  //Hantschel 2009 ,P252  Table 6.1
				Krw=0.4*Swe*Swe;
				Krow=1.-1.8*Swe+0.8*Swe*Swe;
				Krg=0.4*Sge*Sge;
				Krog=1.-1.8*Sgoe+0.8*Sgoe*Sgoe;
				Kro=Krow*Krog;
			}   */
			void GetKrwKrow()              //�����͸�ʼ��㣬����Brooks-Corey���鹫ʽ
				{
					Krw=pow(Swe,(2.0+3.0*lamuda)/lamuda);
					Krow=pow(1.0-Swe,2)*(1.0-pow(Swe,(2.0+lamuda)/lamuda));
				}
			void GetKrwKrg()              //�����͸�ʼ��㣬����Brooks-Corey���鹫ʽ
				{
					Krw=pow(Swe,(2.0+3.0*lamuda)/lamuda);
					Krg=pow(1.0-Swe,2)*(1.0-pow(Swe,(2.0+lamuda)/lamuda));
				}
			void GetKrgKrog()              //�����͸�ʼ��㣬����Brooks-Corey���鹫ʽ
				{
					Krg=pow(Sge,(2.0+3.0*lamuda)/lamuda);
					Krog=pow(1.0-Sge,2)*(1.0-pow(Sge,(2.0+lamuda)/lamuda));
				}
			void GetKr()  //����͡�����ˮ�������͸��
				{
				lamuda=0.34; //��������ͳһ��Ϊ��ֵ
				switch(aHCType)
								{
								case Oil:
								GetKrwKrow();
								Kro=Krow;
								break;
								case Gas:
								GetKrwKrg();
								break;
								case OilGas:
								GetKrwKrow();
								GetKrgKrog();
								Kro=Krow*Krog;
								break;
								};
				}
			double aToEntryPr,bToEntryPr;//��Ӧ��ͻ��ë��ѹ����ϵ��a��b,��Hantschel 2009 ,P411. Table A.6. Capillary Entry Pressure
			double PcbMA; // ͻ��ë��ѹ��,ˮ��-����
			double PcMA; //ë��ѹ����ˮ��-����
			double PcbOW,PcbGW,PcbGO; //�ֱ�Ϊ��ˮ����ˮ�����͵�ͻ��ë��ѹ��
			double PcOW,PcGW,PcGO; //�ֱ���ˮ����ˮ�����͵�ë��ѹ��
			double RouML,RouMV; //�ֱ����ͺ�����Ħ���ܶȣ���λ��gmol/cm 3
			double Tc,vc; //�ֱ�Ϊ��ϵ���ٽ��¶Ⱥ��ٽ�Ħ�����������Ħ��ƽ��ֵ��ȣ���λ�ֱ�ΪK��cm3/gmol
			double TcL,TcV; //�ֱ��������������ٽ��¶ȣ���λ��K
			double PXigema; //known as the parachor  ,���ű���
			double IFTOilWater,IFTGasWater,IFTGasOil;//��ˮ����ˮ�����͵Ľ�������  interfacial tension (IFT) ����λ��mN/m
			void GetTcVc()
			{  //�����ϵ���ټ��¶Ⱥ��ٽ����
				Tc=0;vc=0;
				for(int i=0;i<NCom;i++) {Tc+=z[i]*Tci[i];vc+=z[i]*vci[i];}
				vc*=1000.; // ��m3/kgmolת��Ϊcm3/mol
			}
			void GetTcLTcV()
			{  //��������������ٽ��¶� ,��λ ��K
				TcL=0;TcV=0;
				for(int i=0;i<NCom;i++) {TcL+=x[i]*Tci[i];TcV+=y[i]*Tci[i];}
			}
			void GetRouMLRouMV(){ RouML=1.e-3/vL;RouMV=1.e-3/vV; } //�����ϵ��Ħ�����,��λ��gmol/cm 3
			void GetIFTOilAndWater(){IFTOilWater=111.*pow((WaterDensity-OilDensity)/1000.,1.024)*pow(TmK/TcL,-1.25);} //�����ˮ��������mN/m��Danesh, 1998 ��P294 8.24 ��Hantschel 2009 ,P234. ��5.85)
			void GetIFTGasAndWater(){IFTGasWater=111.*pow((WaterDensity-GasDensity)/1000.,1.024)*pow(TmK/TcV,-1.25);} //�����ˮ�����������ڽ�����ˮ����������ʹ�ã�mN/m��Danesh, 1998 ��P294 8.24 ��Hantschel 2009 ,P234. ��5.85)
			void GetPXigema() {PXigema=0.324*pow(Tc,0.25)*pow(vc,7./8.);}       //the critical temperature Tc is in K and the critical volume vc is in cm3/gmol. Danesh, 1998 ��P286 8.6
			void GetIFTGasOil() {GetPXigema(); IFTGasOil=pow(PXigema*(RouML-RouMV),4);}     //Parachor Method
			void GetIFT()  //����ܵĽ�������
			{
				GetTcVc();
				GetTcLTcV();
				GetRouMLRouMV();
				GetIFTOilAndWater();
				GetIFTGasAndWater();
				GetIFTGasOil();
			}
			void GetPcbMA() {PcbMA=aToEntryPr*pow(10.,bToEntryPr*Porom*100.);} //����ͻ��ë��ѹ����ˮ��-��������϶������ģ�� Hantschel,2009  P257 (6.17)
			void GetPcb(){GetPcbMA();GetIFT(); PcbOW=PcbMA*IFTOilWater/360.8; PcbGW=PcbMA*IFTGasWater/360.8;PcbGO=PcbMA*IFTGasOil/360.8;} // Hantschel,2009  P254 (6.11)
			void GetPc(){GetPcb();PcOW=PcbOW*pow(Swe,-1./lamuda); PcGW=PcbGW*pow(Swe,-1./lamuda); PcGO=PcbGO*powl(1.-Sge,-1./lamuda);} //�ֱ�Ϊ�ͺ�����ë��ѹ��--�汥�Ͷȵı仯
			void GetKrPc()
			{   //�õ������͸�ʺ�ë��ѹ��ֵ
				GetSe();
				GetKr();
				GetPc();
			}
			void GetViscosityKrPc()  //�õ�ճ�ȡ������͸�ʺ�ë��ѹ��ֵ
			{GetWaterViscosity();GetOilGasViscosity();GetKrPc();}
			void GetWaterViscosity()
			{    //���϶�(�H)=32+���϶�(��)��1.8
				WaterViscosity=109.5*pow(32+Tm*1.8,-1.122);  //����ĵ�λΪ�岴cP,1�岴(1cP)=1����˹��.�� (1mPa.s)
				WaterViscosity/=1000.; //����ת��ΪPa.s
			}
		void GetOilGasViscosity()
			{    //���ԣ�Danish 1998, P335    Lohrenz-Bray-Clark (LBC) method
				double *Miu0i; Miu0i=new double[NCom];
				double *Tri; Tri=new double[NCom];
				double *Lamudai; Lamudai=new double[NCom];
				double Miu0L,Miu0V; //��ѹ���ͺ������ճ��
				double LamudaL,LamudaV; //�ͺ�����Ħ�
				double vcL,vcV;  //�ֱ�Ϊ�ͺ������ٽ�Ħ�����critical molar volume
				// double Tc,Tr; //������ٽ��¶ȺͶԱ��¶�
				// double Pc; //������ٽ�ѹ��
				double RouRL,RouRV; // �ͺ����ı��ܶȣ�reduced density, ��r = ��/��c=vc/v,
				for(int i=0;i<NCom;i++)
					{
					Tri[i]=(Tm+273.15)/Tci[i];   //������ٽ��¶ȵ�λΪK
					Lamudai[i]=pow(Tci[i],1./6.)*pow(MW[i],-0.5)*pow(Pci[i]/0.101325,-2./3.);  //(9.25)  ������ٽ�ѹ����λΪ����ѹ
					if(Tri[i]<=1.5)
					Miu0i[i]=34.e-5*pow(Tri[i],0.94)/Lamudai[i];   //��λ��mPa.s
					else
					Miu0i[i]=17.78e-5*pow(4.58*Tri[i]-1.67,5./8.)/Lamudai[i];  //��λ��mPa.s
					}
				double temp01=0,temp02=0,temp03=0,temp04=0,temp05=0,temp06=0;   //��Ӧ������
				double temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;   //��Ӧ������
				for(int i=0;i<NCom;i++)
					{
					temp01+=x[i]*Miu0i[i]*sqrt(MW[i]);  //(9.28)
					temp1+=y[i]*Miu0i[i]*sqrt(MW[i]);  //(9.28)
					temp02+=x[i]*sqrt(MW[i]);           //(9.28)
					temp2+=y[i]*sqrt(MW[i]);           //(9.28)
					temp03+=x[i]*Tci[i];                //(9.29)
					temp3+=y[i]*Tci[i];                //(9.29)
					temp04+=x[i]*MW[i];                 //(9.29)
					temp4+=y[i]*MW[i];                 //(9.29)
					temp05+=x[i]*Pci[i]/0.101325;       //(9.29)
					temp5+=y[i]*Pci[i]/0.101325;       //(9.29)
					temp06+=x[i]*vci[i];                //(9.30)
					temp6+=y[i]*vci[i];                //(9.30)
					}
				Miu0L=temp01/temp02;                     //(9.28)����λ��mPa.s
				Miu0V=temp1/temp2;                     //(9.28)����λ��mPa.s
				LamudaL=pow(temp03,1./6.)*pow(temp04,-1./2.)*pow(temp05,-2/3.); //(9.29)
				LamudaV=pow(temp3,1./6.)*pow(temp4,-1./2.)*pow(temp5,-2/3.); //(9.29)
				vcL=temp06;                              //(9.30)
				vcV=temp6;                              //(9.30)
				RouRL=vcL/vL;                           //(9.30)
				RouRV=vcV/vV;                           //(9.30)
				double a1 = 0.10230;
				double a2 = 0.023364;
				double a3 = 0.058533;
				double a4 =-0.040758;
				double a5 = 0.0093324;
				double RightPartOil,RightPartGas;
				RightPartOil=a1+a2*RouRL+a3*RouRL*RouRL+a4*RouRL*RouRL*RouRL+a5*RouRL*RouRL*RouRL*RouRL; //(9.26)
				RightPartGas=a1+a2*RouRV+a3*RouRV*RouRV+a4*RouRV*RouRV*RouRV+a5*RouRV*RouRV*RouRV*RouRV; //(9.26)
				OilViscosity= (pow(RightPartOil,4)-1.e-4)/LamudaL+Miu0L;                                 //(9.26)  ���ﵥλΪ��mPa.s����cp
				GasViscosity= (pow(RightPartGas,4)-1.e-4)/LamudaV+Miu0V;                                 //(9.26)  ���ﵥλΪ��mPa.s����cp
				OilViscosity/=1000.; GasViscosity/=1000.; //ת��ΪPa.s����ǧ�ˡ��ס��뵥λ��ϵ

				//release
				delete Miu0i;
				delete Tri;
				delete Lamudai;


			}

			//=================ճ�ȡ������͸�ʡ�����������ë��ѹ��========��ʼ

			double *MatrixDensity; //��ͬ���Ի��ʵ��ܶ�
			double TMatrixDensity; //  �ܵĻ����ܶ�
			double WaterDensity; //�ز�ˮ�ܶ�
			double OilDensity; //���ܶ�
			double GasDensity; //���ܶ�
			double SeaWaterDensity;  //��ˮ�ܶ�ȡֵ=1025 kg/m^3
			double TotalDensity; //�ܵ���ʯ�ܶȣ��������е�����͹Ǽܵ��ۺ��ܶȣ�

			double TotalThermalCond; //�ܵ��ȵ���  ���������ʺͿ�϶���壩
			double *MatrixThermalCond; //��ͬ�Ļ����ȵ���
			double TMatrixThermalCond; //�ܵĻ����ȵ���
			double WaterThermalCond; //�ز�ˮ�ȵ���
			double OilThermalCond; //���ȵ���
			double GasThermalCond; //���ȵ���
			double PoreFluidThermalCond; //��϶�����ȵ���
			double IceThermalCond; //���ȵ���
			double GasHydratesThermalCond; //��Ȼ��ˮ�����ȵ���

			double TotalHeatCapacity; //�ܵı����� ���������ʺͿ�϶���壩
			double *MatrixHeatCapacity; //���ʱ����ݣ���ͬ�Ļ���
			double TMatrixHeatCapacity; //�ܵĻ��ʱ�����
			double WaterHeatCapacity; //�ز�ˮ������
			double OilHeatCapacity; //�ͱ�����
			double GasHeatCapacity; //��������
			double IceHeatCapacity; //��������
			double GasHydratesHeatCapacity; //��Ȼ��ˮ���������
			double PoreFluidHeatCapacity; //��϶���������


			double *MatrixRadioactiveHeat;    //��ͬ���Ի��ʵķ�����
			double Qr; // �ܵķ�����

			double PaleoWaterDepth;//��¼��ˮ��
			double SurfaceT; //�ر��¶ȣ���¼������ĸ���
			double HF; //��¼������

			double Tt; //�����¶�
			double Tm; //�в��¶�
			double Tb; //�ײ��¶�
			double Tmax; //��¼ģ��������в�������¶�


			double TTI; //�ز��TTIֵ
			double Ro[4];  //�ز��Ro%ֵ
			double TTI0; //��ʼʱ�̵�TTIֵ
			ParaOfEasyRo *aParaOfEasyRo; //����һ��EasyRoģ�ͽṹ�����ڴ洢����
			ParaOfEasyRo *aParaOfBasinRo; //����һ��BasinRoģ�ͽṹ�����ڴ洢����
			ParaOfSimpleRo *aParaOfSimpleRo; //����һ��SimpleRoģ�ͽṹ�����ڴ洢����

			double TOC; //�����л�̼����
			double InitTOC; //ԭʼ�л�̼���� ,�������ڵĵز������µ�ԭʼ�л�̼���������ֽ����ʯ�ܶ����� ������ֵֻ�����һ��ʱ��ĵز�δ���
			double MassOfInitTOC;//�õز�ε�λ�����m^2����ԭʼ�л�̼�������� �� ����ֵֻ�����һ��ʱ��ĵز�δ���

			DR *aDR;  //����һ�����Ҹ�����ṹ��
			double HCGI[4]; //  ����ǿ�� kg/m^2 �����ڽ�������ģ��
			double OGI[4]; //oil generating intensity ,����ǿ�� kg/m^2 �����ڽ�������ģ��
			double GGI[4]; //gas generating intensity ,����ǿ�� kg/m^2 �����ڽ�������ģ��

			//2017/11/27: ����һ���л���Ļ�ѧ��Ӧ����ѧ�����ṹ��
			Organofacies *aOrganofacies; 

			ParaLLNL *aParaLLNL; //����һ��LLNL��ѧ��Ӧ����ѧ�����ṹ��
			double OGI_LLNL;   //oil generating intensity ,����ǿ�� kg/m^2  ,���ڻ�ѧ��Ӧ����ѧ����ģ��
			double GGI_LLNL;   //gas generating intensity ,����ǿ�� kg/m^2��Ҳ��������λ��  ,���ڻ�ѧ��Ӧ����ѧ����ģ��

			//2017/8/8: pressure coefficient(ѹ��ϵ��)
			double PCOEt;//top
			double POCEm;//middle
			double POCEb;//bottom

			//2017/10/13: ---------------------------------���� START-----------------------------------------------------
			// double HI0; //Դ�ҳ�ʼ����ָ����g/gTOC
			double aO;//������ϵ��Oil sorption cofficient ����λ��g/gC
			double aG;//������ϵ��Gas sorption cofficient ����λ��g/gC
			double MKer; //Դ���и��Ҹ����������л�̼��ʽ��������λ��kg
			double COS; //Critical oil saturation �ٽ����ͱ��Ͷ�
			double CGS; // Critical Gas saturation �ٽ��������Ͷ�
			double MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
			double MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
			double MAdxOil; //Դ�����͵�����������λ��kg
			double MAdxGas; //Դ������������������λ��kg
			double MAdxMaxOil; //Դ�����͵��������������λ��kg
			double MAdxMaxGas; //Դ���������������������λ��kg
			double MExpOil; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
			double MExpGas; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
			double MExpOilAdded; //Դ���ۻ�����������λ��kg ��
			double MExpGasAdded; //Դ���ۻ�����������λ��kg ��
			double MResidualOil;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
			double MResidualGas;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
			double OilInSourceRockPoros,GasInSourceRockPoros; //�ֱ�ΪԴ�ҿ�϶�е��ͺ����������ڻ�û�п��ǣ���ʱ������Ϊ0�����ڿ��Կ��ǲ�Ϊ0�����
			double OilOutOfSourceRock,GasOutOfSourceRock; //�ֱ�Ϊ���Ƶ�Դ������ۼƵ��ͺ�����
			double OGIFromKerogen,GGIFromKerogen; //ָԴ�Ҹ��Ҹ��ۻ��������������� ��������ǰ��OGI_LLNL��GGI_LLNL ������Ҳ������ͬ������ó�����ֻ�Ǹ��Ҹ����ɵ���������������û�п������ѽ���ٵ����������ӵ�����
			double OilCrackedAdded; //Դ�����ۻ������ѽ���
			double GasCrackedAdded; //Դ�����ۻ������ѽ���
			double CokeAdded;//Դ�������ѽ�����Ľ�̿��
			double TR; //Դ�ҵ�����ת����
			
			void GetaG()
			{  //�����¶Ⱥ�ѹ����ø��Ҹ�����������ϵ��
				aG=0.0067+0.0094*log(Pm/1.0e6)-0.000062*Tm;
				if(aG<0)aG=0.;
			}

			void GetGeneratedOilAndGas()
			{ //������ɵ���������  ,����Ե�һ��ʱ�䲽
				//���ͨ����һ���ĸ��Ҹ��ѽ�����ѽ��õ���Դ���е��ͺ����� ����ʱ��û�п����ŵ�����
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->OilCrackToGas(SurfaceT,BeginAge,Tm,EndAge);  //ʹ�õ�����һ��Դ���д��ڵ����� ������������иú����������������ָ�ڸ�ʱ�䲽���н���ʱ��ʱ�䲽���ڵ���
					OGIFromKerogen=aParaLLNL->OilGenerated*aParaLLNL->MassOfInitTOCTotal;
					GGIFromKerogen=aParaLLNL->GasGenerated*aParaLLNL->MassOfInitTOCTotal;
					CokeAdded=aParaLLNL->ResidueCrackedAdded; //���ڵ�һ��ʱ�䲽���ۼƽ�̿��Ϊ0
					break;
				case Organo:
					aOrganofacies->OilCrackToGas(SurfaceT,BeginAge,Tm,EndAge);  //ʹ�õ�����һ��Դ���д��ڵ����� ������������иú����������������ָ�ڸ�ʱ�䲽���н���ʱ��ʱ�䲽���ڵ���
					OGIFromKerogen=aOrganofacies->OilGenerated*aOrganofacies->MassOfInitTOCTotal;
					GGIFromKerogen=aOrganofacies->GasGenerated*aOrganofacies->MassOfInitTOCTotal;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //���ڵ�һ��ʱ�䲽���ۼƽ�̿��Ϊ0
					break;
				};
			}
			
			void GetMAdxAndExpOfOilAndGas()
			{  //���Դ���е��������������������� ������������������  ,����Ե�һ��ʱ�䲽
				GetGeneratedOilAndGas();  //������ɵ���������
				GetaG(); //��ø��Ҹ�����������ϵ��
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->GetMKer(); //��ø��Ҹ�����
					MKer=aParaLLNL->MKerTotal;
					MKerReac=aParaLLNL->MKerReac;
					MKerInert=aParaLLNL->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					MAdxMaxGas=aG*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					if(aParaLLNL->OilExisted<=MAdxMaxOil) {MAdxOil=aParaLLNL->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aParaLLNL->OilExisted-MAdxOil;     }
					if(aParaLLNL->GasExisted<=MAdxMaxGas) {MAdxGas=aParaLLNL->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aParaLLNL->GasExisted-MAdxGas;     }
					MExpOilAdded=MExpOil;   //�ۻ�������
					MExpGasAdded=MExpGas;   //�ۻ�������
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;    //����Դ�ҿ�϶��������Ϊ0
					MResidualOil=MAdxOil+OilInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aParaLLNL->OilExisted=MResidualOil; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					aParaLLNL->GasExisted=MResidualGas; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					OilCrackedAdded=aParaLLNL->OilCrackedAdded;
					GasCrackedAdded=aParaLLNL->GasCrackedAdded;
					CokeAdded=aParaLLNL->ResidueCrackedAdded; //
					TR=aParaLLNL->TR;
					break;
				case Organo:
					aOrganofacies->GetMKer(); //��ø��Ҹ�����
					MKer=aOrganofacies->MKerTotal;
					MKerReac=aOrganofacies->MKerReac;
					MKerInert=aOrganofacies->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					MAdxMaxGas=aG*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					if(aOrganofacies->OilExisted<=MAdxMaxOil) {MAdxOil=aOrganofacies->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aOrganofacies->OilExisted-MAdxOil;     }
					if(aOrganofacies->GasExisted<=MAdxMaxGas) {MAdxGas=aOrganofacies->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aOrganofacies->GasExisted-MAdxGas;     }
					MExpOilAdded=MExpOil;   //�ۻ�������
					MExpGasAdded=MExpGas;   //�ۻ�������
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;    //����Դ�ҿ�϶��������Ϊ0
					MResidualOil=MAdxOil+OilInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aOrganofacies->OilExisted=MResidualOil; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					aOrganofacies->GasExisted=MResidualGas; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					OilCrackedAdded=aOrganofacies->OilCrackedAdded;
					GasCrackedAdded=aOrganofacies->GasCrackedAdded;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //
					TR=aOrganofacies->TR;
					break;
				};
			}
			
			void GetGeneratedOilAndGas(StrSeg *StrSegLeft)
			{ //������ɵ��������ʹ�����Դ�ҵ�������
				//���Ȼ��ͨ����һ���ĸ��Ҹ��ѽ�����ѽ��õ���Դ���е��ͺ����� ����ʱ��û�п����ŵ�����
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->OilCrackToGas(StrSegLeft->Tm,BeginAge,Tm,EndAge,StrSegLeft->aParaLLNL );
					OGIFromKerogen=aParaLLNL->OilGenerated*aParaLLNL->MassOfInitTOCTotal;
					GGIFromKerogen=aParaLLNL->GasGenerated*aParaLLNL->MassOfInitTOCTotal;
					CokeAdded=aParaLLNL->ResidueCrackedAdded;   //��̿��������һʱ�䲽���ѽ�����ۻ�������Ϊ�ڸú��������ڸ�ʱ�䲽���ѽ�֮ǰ
					break;
				case Organo:
					aOrganofacies->OilCrackToGas(StrSegLeft->Tm,BeginAge,Tm,EndAge,StrSegLeft->aOrganofacies);  //ʹ�õ�����һ��Դ���д��ڵ����� ������������иú����������������ָ�ڸ�ʱ�䲽���н���ʱ��ʱ�䲽���ڵ���
					OGIFromKerogen=aOrganofacies->OilGenerated*aOrganofacies->MassOfInitTOCTotal;
					GGIFromKerogen=aOrganofacies->GasGenerated*aOrganofacies->MassOfInitTOCTotal;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //
					break;
				};
			}
			
			void GetMAdxAndExpOfOilAndGas(StrSeg *StrSegLeft)
			{  //���Դ���е��������������������� ������������������
				GetGeneratedOilAndGas(StrSegLeft);
				GetaG(); //��ø��Ҹ�����������ϵ��
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->GetMKer(); //��ø��Ҹ�����
					MKer=aParaLLNL->MKerTotal;
					MKerReac=aParaLLNL->MKerReac;
					MKerInert=aParaLLNL->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					MAdxMaxGas=aG*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					if(aParaLLNL->OilExisted<=MAdxMaxOil) {MAdxOil=aParaLLNL->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aParaLLNL->OilExisted-MAdxOil;     }
					if(aParaLLNL->GasExisted<=MAdxMaxGas) {MAdxGas=aParaLLNL->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aParaLLNL->GasExisted-MAdxGas;     }
					MExpOilAdded=StrSegLeft->MExpOilAdded+MExpOil;
					MExpGasAdded=StrSegLeft->MExpGasAdded+MExpGas;
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;
					MResidualOil=MAdxOil+OilInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aParaLLNL->OilExisted=MResidualOil; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					aParaLLNL->GasExisted=MResidualGas; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					OilCrackedAdded=aParaLLNL->OilCrackedAdded;
					GasCrackedAdded=aParaLLNL->GasCrackedAdded;
					CokeAdded=aParaLLNL->ResidueCrackedAdded; //
					TR=aParaLLNL->TR;
					break;
				case Organo:
					aOrganofacies->GetMKer(); //��ø��Ҹ�����
					MKer=aOrganofacies->MKerTotal;
					MKerReac=aOrganofacies->MKerReac;
					MKerInert=aOrganofacies->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					MAdxMaxGas=aG*(MKer+CokeAdded);  //Դ�����������������---�л�̼������������Ҹ��������ѽ�Ĳ�������������
					if(aOrganofacies->OilExisted<=MAdxMaxOil) {MAdxOil=aOrganofacies->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aOrganofacies->OilExisted-MAdxOil;     }
					if(aOrganofacies->GasExisted<=MAdxMaxGas) {MAdxGas=aOrganofacies->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aOrganofacies->GasExisted-MAdxGas;     }
					MExpOilAdded=StrSegLeft->MExpOilAdded+MExpOil;
					MExpGasAdded=StrSegLeft->MExpGasAdded+MExpGas;
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;
					MResidualOil=MAdxOil+OilInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// Դ�Ҳ�������,�������Ҹ��������Ϳ�϶������������ʱ�����϶������Ϊ0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aOrganofacies->OilExisted=MResidualOil; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					aOrganofacies->GasExisted=MResidualGas; //����Դ���еĴ��ڵ�����ΪԴ�Ҳ�������
					OilCrackedAdded=aOrganofacies->OilCrackedAdded;
					GasCrackedAdded=aOrganofacies->GasCrackedAdded;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //
					TR=aOrganofacies->TR;
					break;
				};
			}

			// double MKerReacInit;//��ʼʱ�̷�Ӧ���Ҹ���������λ��kg
			// double rKerInert; //��ʼʱ����Ч���Ҹ��ı���
			// double TRO,TRG; //Transformation Ratio ��ת������ ,ֵ��[0-1] ֮��,�ֱ����ͺ�����
			 double SoTreshold;   //�ٽ����ͱ��Ͷȣ�ֵ��[0-1]֮��
			 double SgTreshold;   //�ٽ��������Ͷȣ�ֵ��[0-1]֮��




			 //================== flash Calculation Start ,��̬�������

			// double Rs; //�ܽ�������, m3/m3
			 double Sgg; //��������ܶ�   ��Good Oil: Sgg= 0.855
			 double Soo;//�͵�����ܶ�     ; Good Oil:  Soo=0.823
			 double T_F; //�����¶�
			// double Coeff_a; //�ݵ㹫ʽ�е�ϵ��
			// void GetT_FFromCelsiusDegree(){  T_F=32.+Tm*1.8;   } //���϶�תΪ���϶�
			// void GetCoeff_a(){GetT_FFromCelsiusDegree(); Coeff_a=0.00091*T_F-0.0125*API;}
			// void Getpb(){GetCoeff_a(); pb=18.2*(pow(Rs/Sgg,0.83)*pow(10.,Coeff_a)-1.4);  } //����͵��ݵ�ѹ��
			 double MolFraC1InWater; //molar fraction of methane in water
			 void GetMolFraC1InWater() //��ü�����ˮ���ܽ��Ħ������ ��ԭ�Ĺ�ʽ���ܻ������⣬�д���֤
			   {MolFraC1InWater=-55.811+7478.84/TmK+20.6794*log(TmK/100.)+0.753158*log(PmMPa);}
			 double nl,nv; //�ֱ���Һ̬����̬��Ħ������
			 int NCom; //��N����ֵ�����
			 Properties *aProperties;
			 double *x,*y,*z;  //�ֱ�Ϊ��Һ���е����Ħ������/�������������е����Ħ������/�������ܵ����Ħ������
			 double *K; // The equality of fugacity can be expressed by the equilibrium ratio, K,  K[i] = y[i] / x[i]
			 double *MW;       //���Ħ������  kg/kgmol
			 double *Tci,*Pci,*vci; //����ٽ��¶ȡ�ѹ�������   K��MPa��m^3/kmol
			 double *Omegai; //the dimensionless acentric factor,����ֵ�
			 double **kij; //binary interaction parameter ��Ԫ�໥���ò���
			 double R;//���峣�� ��=0.008314;0.008314 KJ/(mol*K)
			HCType aHCType;
			void GetProperties(int aNCom,Properties *aProperties,double **akij,EOS aaEOS)
			 {    //��ú���ģ����ֲ���
				 
				 //release firstly
				 ReleaseProperties();

				 //
				 NCom=aNCom;
				 MW=new double[NCom];   Tci=new double[NCom];
				 Pci=new double[NCom]; Omegai=new double[NCom];
				 kij=new double*[NCom];
				 x=new double[NCom]; y=new double[NCom];
				 z=new double[NCom];  K=new double[NCom];
				 vci=new double[NCom];
				 for(int i=0;i<NCom;i++) kij[i]=new double[NCom];  //
				 aci=new double[NCom];bi=new double[NCom];mi=new double[NCom];Alphai=new double[NCom];ai=new double[NCom];
				 Ai=new double[NCom];Bi=new double[NCom]; //û����
				 FaiiL=new double[NCom]; FaiiV=new double[NCom];
				 fiL=new double[NCom]; fiV=new double[NCom];
				 xSC=new double[NCom]; ySC=new double[NCom];
				 KSC=new double[NCom];
				 for(int i=0;i<NCom;i++)
				  {
					MW[i]=aProperties[i].MW; Tci[i]=aProperties[i].Tc; Pci[i]=aProperties[i].Pc;
					Omegai[i]=aProperties[i].Omega; z[i]=aProperties[i].z;vci[i]=aProperties[i].Vc;/**/
				  }
				 R=0.008314;//���峣�� ��
				 aEOS=aaEOS;
				 for(int i=0;i<NCom;i++)for(int j=0;j<NCom;j++)kij[i][j]=akij[i][j];
				 SCT=15.556+273.15; //��׼�����µ��¶�15.556���϶�
				 SCP=0.101325; //��׼�����µ�ѹ��1 atm 0.1MPa
			 }

			void GetProperties()
			 {  //�����C1��nC10�Ļ����ϵ������
				
				 //release firstly
				 ReleaseProperties();
				 
				 NCom=2;
				 MW=new double[NCom];   Tci=new double[NCom];
				 Pci=new double[NCom]; Omegai=new double[NCom];
				 kij=new double*[NCom];
				 x=new double[NCom]; y=new double[NCom];
				 z=new double[NCom];  K=new double[NCom];
				 vci=new double[NCom];
				 for(int i=0;i<NCom;i++) kij[i]=new double[NCom];
				 aci=new double[NCom];bi=new double[NCom];mi=new double[NCom];Alphai=new double[NCom];ai=new double[NCom];
				 Ai=new double[NCom];Bi=new double[NCom]; //û����
				 FaiiL=new double[NCom]; FaiiV=new double[NCom];
				 fiL=new double[NCom]; fiV=new double[NCom];
				 xSC=new double[NCom]; ySC=new double[NCom];
				 KSC=new double[NCom];
				   z[0]=0.6;z[1]=0.4;
				   MW[0]=16.043; MW[1]=142.28;
				   Tci[0]=190.56; Tci[1]=617.7;
				   Pci[0]=4.599; Pci[1]=2.110;
				   Omegai[0]=0.0115; Omegai[1]=0.4923;
				   vci[0]=0.0986;vci[1]=0.6;    //m^3/kgmol
				   R=0.008314;;//���峣�� ��
				   SCT=15.556+273.15; //��׼�����µ��¶�15.556���϶�
				   SCP=0.101325; //��׼�����µ�ѹ��1 atm 0.1MPa
				  aEOS=PR;
				  switch(aEOS)
				  {
				   case SRK:
				   kij[0][0]=0;kij[0][1]=0.0550;
				   kij[1][0]=0.0550;kij[1][1]=0;
				   break;
				   case PR:
				   kij[0][0]=0;kij[0][1]=0.0411;
				   kij[1][0]=0.0411;kij[1][1]=0;
				   break;
				  };
			 }

			 double SCT; //��׼�����µ��¶�15.556���϶�
			 double SCTK; // ��׼�����µ��¶ȿ����¶�
			 double SCP; //��׼�����µ�ѹ��1 atm 0.1MPa
			 double pb; //��ϵ���ݵ�ѹ�� ��MPa
			 double TmK; //�в��¶ȣ��ÿ����¶ȱ�ʾ��������̬����
			 double PmMPa; //�в�ѹ������������ʾ��������̬����
			 double pTc; //׼�ٽ��¶� K   pseudo critical temperature  ,������ֵΪ��ϵ�¶�
			 double pPc; //׼�ٽ�ѹ�� MPa
			 double a,b; //�ֱ��Ӧ���ٽ���̬��aֵ��bֵ
			 double vL,vV;  //�ֱ����ͺ�����Ħ�����  m3/kgmol
			 double MWL,MWV; //�ֱ�������������Ħ������
			 double *aci,*bi,*mi,*Alphai,*ai;
			 double *Ai,*Bi; //
			 double aL,bL,aV,bV; //�ֱ��Ӧ���ͺ�����aֵ��bֵ
			 EOS aEOS;
			 double AL,AV,BL,BV; // �ֱ��Ӧ���ͺ���
			 double ZL,ZV; //Һ������壬���ͺ�����ѹ��ϵ��
			 double *FaiiL,*FaiiV; //�ֱ�Ϊ�͡�����̬����ֵ��ݶ�ϵ����fugacity coefficients��
			 double *fiL,*fiV; //�ֱ�Ϊ�͡�����̬����ֵ��ݶȣ�fugacities��

			void GetpTcpPc()
			{   //���ڼ����ٽ��¶Ⱥ�ѹ��,ͨ����������ã� --���ڻ����
				 double pTcInit=0;
				 for(int i=0;i<NCom;i++) pTcInit+=z[i]*Tci[i];
				 pTc=pTcInit;  //��pTC����ֵ
				 double pTctemp=pTc; //
				 double wc; //ǰ�����ε������¶Ȳ����ֵ
				 double wcx=0.01; //�ж���������������ֵ
				 int NLoop=0;
				do
				{
				 NLoop++; //���ѭ�����ﵽĳһ��ֵ��û������������ѭ��
				 b=0; a=0;  //����ֵΪ0
				 for(int i=0;i<NCom;i++)
				 {
				  switch(aEOS)
				  {
				   case SRK:
				   aci[i]=0.42747*R*R*Tci[i]*Tci[i]/Pci[i];      //Danish,1998 P140  4.22
				   bi[i]=0.08664*R*Tci[i]/Pci[i];            //Danish,1998 P140  4.22
				   mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
				   break;
				   case PR:
				   aci[i]=0.457235*R*R*Tci[i]*Tci[i]/Pci[i];    //Danish,1998 P141  4.27
				   bi[i]=0.077796*R*Tci[i]/Pci[i];          //Danish,1998 P141  4.27
				   mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
				   break;
				  };
				 }
				 for(int i=0;i<NCom;i++)
				 {    //��Ϲ���  Mixture parameters
				  b+=z[i]*bi[i];   //Danish,1998 P155  4.74
				   for(int j=0;j<NCom;j++)
					 a+=z[i]*z[j]*sqrt(ai[i]*ai[j])*(1.-kij[i][j]);   //Danish,1998 P155  4.78
				 }
				  switch(aEOS)
				  {
				   case SRK:
				   pTc=0.08664/0.42747*a/b/R;   // Danish 1998 P140 4.22
				   pPc=0.08664*R*pTc/b;
				   break;
				   case PR:
				   pTc=0.17014446*a/R/b; // Danish 1998 P179 E5.4
				   pPc=0.077796*R*pTc/b;
				   break;
				  };
				  wc=fabs(pTc-pTctemp);
				  pTctemp=pTc;
				}while(wc>wcx&&NLoop<100);
				if(NLoop==100)
				{ //�������100�λ�û����������ֵ���ڸ�����ٽ��¶ȵ�Ħ��ƽ��ֵ
				  pTc=pTcInit;
				}
			}
			double GetVOfRRE(double aPoint) //���Rachford-Rice����ֵ Danesh 1998, (5.6)P169
			   {    //  int NCom,double *z,double *K,
				 double tempV=0;
				 for(int i=0;i<NCom;i++)
					tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*aPoint);
				 return tempV;
			   }
			void GetInitKi()
			   { //���ÿһ��ֵĳ�ʼ��ƽ���Ki��Danesh 1998, (3.66)P122    int NCom,double *K, double *Pci,double PmMPa, double *Omegai,double *Tci,double TmK
				  for(int i=0;i<NCom;i++) K[i]=Pci[i]/PmMPa*exp(5.37*(1.+Omegai[i])*(1.-Tci[i]/TmK));
			   }
			void GetParasOfComsInEOS(double *xi,double &aLV,double &bLV) //���״̬�����и���ֵĲ���
			{ //
				 bLV=0; aLV=0;  //����ֵΪ0
				 for(int i=0;i<NCom;i++)
				 {
				  switch(aEOS)
				  {
				   case SRK:
				   aci[i]=0.42747*R*R*Tci[i]*Tci[i]/Pci[i];      //Danish,1998 P140  4.22
				   bi[i]=0.08664*R*Tci[i]/Pci[i];            //Danish,1998 P140  4.22
				   mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmK/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmK/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
				   Ai[i]=ai[i]*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7  ��Ȼ�����ˣ�����ʱû���õ�
				   Bi[i]=bi[i]*PmMPa/(R*TmK);              //Danish,1998 P132  4.8   ��Ȼ�����ˣ�����ʱû���õ�
				   break;
				   case PR:
				   aci[i]=0.457235*R*R*Tci[i]*Tci[i]/Pci[i];    //Danish,1998 P141  4.27
				   bi[i]=0.077796*R*Tci[i]/Pci[i];          //Danish,1998 P141  4.27
				   mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmK/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmK/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
				   Ai[i]=ai[i]*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7     ��Ȼ�����ˣ�����ʱû���õ�
				   Bi[i]=bi[i]*PmMPa/(R*TmK);              //Danish,1998 P132  4.8      ��Ȼ�����ˣ�����ʱû���õ�
				   break;
				  };
				 }
				 for(int i=0;i<NCom;i++)
				 {    //��Ϲ���  Mixture parameters
				  bLV+=xi[i]*bi[i];   //Danish,1998 P155  4.74
				   for(int j=0;j<NCom;j++)
					 aLV+=xi[i]*xi[j]*sqrt(ai[i]*ai[j])*(1.-kij[i][j]);   //Danish,1998 P155  4.78
				 }
			}
			void GetaEOSParas(double &aa,double &bb,double &cc,double &dd,double A,double B)
			 {   //  ,EOS aEOS
				 switch(aEOS)
				  {
				   case SRK:
				   aa=1.; bb=-1.;cc=A-B-B*B;dd=-A*B;
				   break;
				   case PR:
				   aa=1.; bb=-(1.-B);cc=A-2.*B-3.*B*B;dd=-A*B+B*B+B*B*B;
				   break;
				  };
			 }
			void GetFaii(double *Faii,double *xx,double aLV,double bLV,double A,double B,double Z)   //�����ݶ�ϵ�� Danish,1998 p157 E4.5
			 {   //
				  double Delta1,Delta2;
				  double lnFaii;
				  switch(aEOS)
				  {
				   case SRK:
				   Delta1=1.;
				   Delta2=0.;
				   break;
				   case PR:
				   Delta1=1+sqrt(2.);
				   Delta2=1-sqrt(2.);
				   break;
				  };
				  double tempXigemaxjaij;
				  double aij;
				  for(int i=0;i<NCom;i++)
				  {
					tempXigemaxjaij=0;
					for(int j=0;j<NCom;j++)
					 {
					  aij=sqrt(ai[i]*ai[j])*(1-kij[i][j]); // Danish,1998 p155 4.77
					  tempXigemaxjaij+=xx[j]*aij;
					 }
					lnFaii=bi[i]/bLV*(Z-1.)-log(Z-B)-A/(B*(Delta2-Delta1))*(2.*tempXigemaxjaij/aLV-bi[i]/bLV)*log((Z+Delta2*B)/(Z+Delta1*B));
					Faii[i]=exp(lnFaii);
				  }
			 }
			void Getfi_K()
			 {    //���������̬��ֵ��ݶ��Լ���ֵ�ƽ���  int NCom,double *fiL,double *fiV,double *FaiiL,double *FaiiV,double *K,double *x,double *y,double PmMPa
			   for(int i=0;i<NCom;i++)  { fiL[i]=FaiiL[i]*x[i]*PmMPa;  fiV[i]=FaiiV[i]*y[i]*PmMPa; K[i]=FaiiL[i]/FaiiV[i];/*if(fabs(K[i])<1e-8)ShowMessage("fabs(K[i])="+FloatToStr(K[i]));*/}
			 }
			void Getfi_KSC()
			 {    //���������̬��ֵ��ݶ��Լ���ֵ�ƽ���  int NCom,double *fiL,double *fiV,double *FaiiL,double *FaiiV,double *K,double *x,double *y,double PmMPa
			   for(int i=0;i<NCom;i++)  { fiL[i]=FaiiL[i]*xSC[i]*SCP;  fiV[i]=FaiiV[i]*ySC[i]*SCP; KSC[i]=FaiiL[i]/FaiiV[i];/*if(fabs(K[i])<1e-8)ShowMessage("fabs(K[i])="+FloatToStr(K[i]));*/}
			 }
			void GetErrorValue_fiLfiV(double &ErrorValue_fiLfiV) // ,int NCom,double *fiL,double *fiV
			  {     //Danish,1998  P174
				ErrorValue_fiLfiV=0;
				for(int i=0;i<NCom;i++) ErrorValue_fiLfiV+=(1.-fiL[i]/fiV[i])*(1.-fiL[i]/fiV[i]);
			  }
			 void BubblePressureAdjusted()//����ѹ��ʹ��ӽ��ݵ�ѹ�� Danesh 1998,P174  (E5.2')
			 {
				 double tempSum=0;
				 for(int i=0;i<NCom;i++) tempSum+=x[i]*K[i];
				 pb=pb*tempSum;
			 }
			/*void DewPressureAdjusted(int NCom,double &PmMPa,double *y,double *K)//����ѹ��ʹ��ӽ�¶��ѹ�� Danesh 1998,P174  (E5.2')
			 {
				 double tempSum=0;
				 for(int i=0;i<NCom;i++) tempSum+=y[i]/K[i];
				 PmMPa=PmMPa*tempSum;
			 }  */
			void GetvLvV() //���������Ħ�����  Danish,1998 P40 2.5
			  { //  double &vL,double &vV,double R,double TmK,double ZL,double ZV,double PmMPa
				  vL=R*TmK*ZL/PmMPa;
				  vV=R*TmK*ZV/PmMPa;
			  }
			  void GetvLvVSC() //��ñ�׼�����µ�������Ħ�����  Danish,1998 P40 2.5
			  { //
				  vLSC=R*SCT*ZL/SCP;
				  vVSC=R*SCT*ZV/SCP;
			  }
			void GetMWLMWV(double *xx,double *yy) //�������������Ħ������
			  {  // int NCom,double &MWL,double &MWV,double *MW,
				MWL=0;MWV=0;
				for(int i=0;i<NCom;i++)
				 {
				   MWL+=xx[i]*MW[i];
				   MWV+=yy[i]*MW[i];
				 }
			  }
			void GetMWLMWVSC(double *xx,double *yy) //��ñ�׼�����µ�����������Ħ������
			  {
				MWLSC=0;MWVSC=0;
				for(int i=0;i<NCom;i++)
				 {
				   MWLSC+=xx[i]*MW[i];
				   MWVSC+=yy[i]*MW[i];
				 }
			  }
			void GetLVDensity() {OilDensity=MWL/vL; GasDensity=MWV/vV;}//����͡�������ܶ�
			void GetLVDensitySC() {OilDensitySC=MWLSC/vLSC; GasDensitySC=MWVSC/vVSC;}//��ñ�׼�����µ��͡�������ܶ�
			void GetLDensity() {OilDensity=MWL/vL; }  //��������ܶ�
			void GetLDensitySC() {OilDensitySC=MWLSC/vLSC; }  //��ñ�׼�����µ������ܶ�
			void GetVDensity() {GasDensity=MWV/vV; }  //��������ܶ�
			void GetVDensitySC() {GasDensitySC=MWVSC/vVSC; }  //��ñ�׼�����µ������ܶ�
			void GetBubblePointPressure()
			{
				double aa,bb,cc,dd; //cubic EOS --����״̬���̵�ϵ��
				double ObjectiveValueInFlash; //Danish,1998  P174     =1.0e-12;
				double ErrorValue_fiLfiV;
				ObjectiveValueInFlash=1.0e-12;
				SolutionOfCE aSCEZ;
				GetInitKi();
				pb=PmMPa; //��ʼ���ݵ�ѹ����ֵΪ�ز�ѹ��
				do
				{
				 for(int i=0;i<NCom;i++)x[i]=z[i]; //����ϵ�е����Ħ���ȸ�ֵ��Һ���е����Ħ����
				 for(int i=0;i<NCom;i++)y[i]=K[i]*x[i];  //�ݵ�ѹ��ʱ����ϵ�е����Ħ���Ⱦ���Һ���е����Ħ����
				 GetParasOfComsInEOS(x,aL,bL); //���Ӧ�������a,b
				 AL=aL*pb/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
				 BL=bL*pb/(R*TmK);              //Danish,1998 P132  4.8
				 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��   ,aEOS
				 aSCEZ=CubicEquation(aa,bb,cc,dd);
				 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; /* ��һ�����ظ���һ��ʵ�������ShowMessage("ZL="+FloatToStr(ZL)); */   }
				 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); /* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */  }
				 GetParasOfComsInEOS(y,aV,bV); //���Ӧ�������a,b
				 AV=aV*pb/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
				 BV=bV*pb/(R*TmK);              //Danish,1998 P132  4.8
				 GetaEOSParas(aa,bb,cc,dd,AV,BV); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��   ,aEOS
				 aSCEZ=CubicEquation(aa,bb,cc,dd);
				 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; /* ��һ�����ظ���һ��ʵ�������ShowMessage("ZL="+FloatToStr(ZL)); */   }
				 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); /* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */  }
				 GetFaii(FaiiL,z,aL,bL,AL,BL,ZL) ; //��������ݶ�ϵ��
				 GetFaii(FaiiV,y,aV,bV,AV,BV,ZV) ; //��������ݶ�ϵ��
				 Getfi_K();    //���������̬��ֵ��ݶ��Լ���ֵ�ƽ���   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
				 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
				 BubblePressureAdjusted();
				}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);
			}
			double NewtonIterationFornv(double aPoint) //��ţ�ٵ�������nv
			 {
				   double tempV; //����ֵ
				   double tempVD;  //����ֵ
				   double nv01,nv02; //����ֵ
				   double wc;
				   double num=0;
				   nv01=aPoint;
				   do
				   {
					num++;
					tempV=0;
					tempVD=0;
					for(int i=0;i<NCom;i++)
					 tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*nv01);    //���Rachford-Rice����ֵ Danesh 1998, (5.6)P169
					for(int i=0;i<NCom;i++)
					 tempVD+=-z[i]*(K[i]-1.)*(K[i]-1.)/pow(1.+(K[i]-1.0)*nv01,2.);  //���Rachford-Rice���̵���ֵ
					nv02=nv01-tempV/tempVD;
					wc=fabs(nv02-nv01);
					nv01=nv02;
				   }while(wc>1.0e-10&&num<1000);
				   return nv02;
			 }
			double OilDensitySC; //��׼������ԭ�͵��ܶ�
			double API; //��׼�������͵��ض�
			double GOR;//���ͱ�  m3/m3
			double Bo; //ԭ�����ϵ��������Ϊ����ԭ����������ԭ�����֮��
			double *KSC;
			double nvSC,nlSC;    //��׼����������������Ħ����
			double *xSC,*ySC;
			double MWLSC,vLSC,MWVSC,vVSC;
			double GasDensitySC; // ��׼�����������ܶ�
			void GetInitKi(int NCom,double *KK, double *Pci,double Pmm, double *Omegai,double *Tci,double Tmm)
			   { //���ÿһ��ֵĳ�ʼ��ƽ���Ki��Danesh 1998, (3.66)P122
				  for(int i=0;i<NCom;i++) KK[i]=Pci[i]/Pmm*exp(5.37*(1.+Omegai[i])*(1.-Tci[i]/Tmm));
			   }
			void GetParasOfComsInEOS(int NCom,double *xiI,double **kij,double *Tci,double *pci, double TmM,double PmM,double *Omegai,double R,double &a,double &b,double *aci,double *bi,double *mi,double *Alphai, double *ai,double *Ai,double *Bi,EOS aEOS) //���״̬�����и���ֵĲ���
			{
			 b=0; a=0;  //����ֵΪ0
			 for(int i=0;i<NCom;i++)
			 {
			  switch(aEOS)
			  {
			   case SRK:
			   aci[i]=0.42747*R*R*Tci[i]*Tci[i]/pci[i];      //Danish,1998 P140  4.22
			   bi[i]=0.08664*R*Tci[i]/pci[i];            //Danish,1998 P140  4.22
			   mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
			   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmM/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmM/Tci[i]))); //Danish,1998 P140  4.23
			   ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
			   Ai[i]=ai[i]*PmM/(R*TmM*R*TmM);          //Danish,1998 P132  4.7  ��Ȼ�����ˣ�����ʱû���õ�
			   Bi[i]=bi[i]*PmM/(R*TmM);              //Danish,1998 P132  4.8   ��Ȼ�����ˣ�����ʱû���õ�
			   break;
			   case PR:
			   aci[i]=0.457235*R*R*Tci[i]*Tci[i]/pci[i];    //Danish,1998 P141  4.27
			   bi[i]=0.077796*R*Tci[i]/pci[i];          //Danish,1998 P141  4.27
			   mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
			   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmM/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmM/Tci[i]))); //Danish,1998 P140  4.23
			   ai[i]=aci[i]*Alphai[i]; //�ο�Danish,1998 P144 Example 4.4    p136 4.19
			   Ai[i]=ai[i]*PmM/(R*TmM*R*TmM);          //Danish,1998 P132  4.7     ��Ȼ�����ˣ�����ʱû���õ�
			   Bi[i]=bi[i]*PmM/(R*TmM);              //Danish,1998 P132  4.8      ��Ȼ�����ˣ�����ʱû���õ�
			   break;
			  };
			 }
			 for(int i=0;i<NCom;i++)
			 {    //��Ϲ���  Mixture parameters
			  b+=xiI[i]*bi[i];   //Danish,1998 P155  4.74
			   for(int j=0;j<NCom;j++)
				 a+=xiI[i]*xiI[j]*sqrt(ai[i]*ai[j])*(1.-kij[i][j]);   //Danish,1998 P155  4.78
			 }
			}
			double NewtonIterationFornv(int NCom1,double *zZ,double *KK, double aPoint) //��ţ�ٵ�������nv
			 {
			   double tempV; //����ֵ
			   double tempVD;  //����ֵ
			   double nv01,nv02; //����ֵ
			   double wc;
			   nv01=aPoint;
			  double num=0;
			   do
			   {
				 num++;
				tempV=0;
				tempVD=0;
				for(int i=0;i<NCom1;i++)
				 tempV+=zZ[i]*(KK[i]-1.0)/(1.0+(KK[i]-1.0)*nv01);  //���Rachford-Rice����ֵ Danesh 1998, (5.6)P169
				for(int i=0;i<NCom1;i++)
				 tempVD+=-zZ[i]*(KK[i]-1.)*(KK[i]-1.)/pow(1.+(KK[i]-1.0)*nv01,2);  //���Rachford-Rice���̵���ֵ
				nv02=nv01-tempV/tempVD;
				wc=fabs(nv02-nv01);
				nv01=nv02;
			   }while(wc>1.0e-10);      // &&num<1000
			   return nv02;
			 }
			void GetGOR()
			  {   //���ͱ�
				if(nvSC<=0) GOR=0;
				else if(nvSC>=1) GOR=-1;
				else GOR=vVSC*nvSC/(vLSC*nlSC);
			  }
			void GetBo()
			  { //���ϵ��
				if(nvSC<1)
				Bo=OilDensitySC/OilDensity;
				else Bo=-1; //�����������������
			  }
			void FlashCalculationSC()    //�����׼�����µļ������������
			{ ////flash calculation start
			//��ֻ�ǿ�����������ֵ��������û�ж���֣�ֻ�Ƕ����ɵ��ͺ���������̬����
			z[0]=GGIFromKerogen/MW[0]; //����Ħ����
			z[1]=OGIFromKerogen/MW[1]; //�͵�Ħ����
			double tteemm=z[0]+z[1];
			z[0]=z[0]/tteemm; //����Ħ����
			z[1]=z[1]/tteemm; //�͵�Ħ����
			if(z[0]<1.0e-5){ z[0]=1.0e-5;z[1]=1.0-z[0];}
			if(z[1]<1.0e-5){ z[1]=1.0e-5;z[0]=1.0-z[1];}  
			SolutionOfCE aSCEZ;
			double ObjectiveValueInFlash; //Danish,1998  P174     =1.0e-12;
			double ErrorValue_fiLfiV;
			double XigemaKizi;
			double XigemaziBiKi;
			double wcx=1.e-5;
			double nvLeftPoint; //���ַ�nv��˵㣬  ��ʼֵΪ0
			double nvRightPoint; //���ַ�nv�Ҷ˵㣬 ��ʼֵΪ1
			double nvMiddlePoint; //���ַ����м�㣬Ϊ���Ҷ˵�͵�һ��
			double aa,bb,cc,dd; //cubic EOS --����״̬���̵�ϵ��
			ObjectiveValueInFlash=1.0e-12;
			double KiMin,KiMax; //��¼��ֵ�ƽ��ȵ���Сֵ�����ֵ
			GetpTcpPc();  //��û����׼�ٽ��¶Ⱥ�ѹ��ֵ�������жϻ�����¶��Ƿ񳬹��ٽ��¶ȣ���������򲻽����������㣬����ֱ�Ӽ����ܶ�
			if(SCT<pTc)
			{  //�����ϵ�¶�û����׼�ٽ��¶ȣ�������������� ����������ʼ
			GetInitKi(NCom,KSC,Pci,SCP,Omegai,Tci,SCT);    //���ÿһ��ֵĳ�ʼ��ƽ���Ki��Danesh 1998, (3.66)P122
			do
			{
			KiMin=KSC[0];KiMax=KSC[0];
			for(int i=1;i<NCom;i++) {if(KSC[i]<KiMin) KiMin=KSC[i]; if(KSC[i]>KiMax) KiMax=KSC[i];}
			if(fabs(1-KiMax)<1e-10||fabs(1-KiMin)<1e-10)  {nvSC=-10000.; break;}
			   nvLeftPoint=1./(1.-KiMax); //nvֵ����˵�   ,Whitson 1989 The negative flash  P52
			   nvRightPoint=1./(1.-KiMin); //nvֵ���Ҷ˵�  ,Whitson 1989 The negative flash  P52
			   nvMiddlePoint=(nvLeftPoint+nvRightPoint)/2.;  //��ʼֵ
			   nvSC=NewtonIterationFornv(NCom,z,KSC,nvMiddlePoint); //��ţ�ٵ�������nv
			   nlSC=1-nvSC;
				for(int i=0;i<NCom;i++)
				  {
					xSC[i]=z[i]/(1.0+(KSC[i]-1.0)*nvSC);
					ySC[i]=z[i]*KSC[i]/(1.0+(KSC[i]-1.0)*nvSC);
				  }
			 GetParasOfComsInEOS(NCom,xSC,kij,Tci,Pci,SCT,SCP,Omegai,R,aL,bL,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS);
			 AL=aL*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BL=bL*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* ��һ�����ظ���һ��ʵ�������*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);}/* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ��;;���������������Ҫѡ�����е����ֵ */
			 GetParasOfComsInEOS(NCom,ySC,kij,Tci,Pci,SCT,SCP,Omegai,R,aV,bV,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS); //���Ӧ�������a,b
			 AV=aV*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BV=bV*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AV,BV); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; } /* ��һ�����ظ���һ��ʵ������� */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); } /* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
			 GetFaii(FaiiL,xSC,aL,bL,AL,BL,ZL) ; //��������ݶ�ϵ��
			 GetFaii(FaiiV,ySC,aV,bV,AV,BV,ZV) ; //��������ݶ�ϵ��
			 Getfi_KSC();    //���������̬��ֵ��ݶ��Լ���ֵ�ƽ���   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
			 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
			}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);   //  &&runtimes<=100
			////////////////////////////////--------------------------------------------
			if(nvSC<=0||nvSC>=1)
			{ //nv<0,���� ��ϵΪ��һ��Һ�࣬nv>1,������ϵ�ǵ�һ�����࣬������������ܶ�
			 GetParasOfComsInEOS(NCom,z,kij,Tci,Pci,SCT,SCP,Omegai,R,aL,bL,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS);
			 AL=aL*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BL=bL*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(nvSC<=0)
			 { //nv<0,���� ��ϵΪ��һ��Һ��
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* ��һ�����ظ���һ��ʵ������� */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }/* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
			 GetvLvVSC(); //���������Ħ�����  Danish,1998 P40 2.5
			 GetMWLMWVSC(z,ySC); //�������������Ħ������  ,�����ǵ�һ�����࣬�����z����x�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vVSC=1.;
			 GetLDensitySC(); //���������ܶ�
			 API=141.5/(OilDensitySC/1000.)-131.5; //where So is the stock tank oil specific gravity, or relative density, to water at 60��F
			 GetGOR();
			 GetBo();
			 }
			 if(nvSC>=1)
			 { //nv>1,������ϵ�ǵ�һ������
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; }  // ��һ�����ظ���һ��ʵ�������
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }// ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ��
			 GetvLvVSC(); //���������Ħ�����  Danish,1998 P40 2.5   ,
			 GetMWLMWVSC(xSC,z); //�������������Ħ������ ,�����ǵ�һ�����࣬�����z����y�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vLSC=1.;
			 GetVDensitySC(); //���������ܶ�
			 GetGOR();
			 GetBo();
			 }
			}
			else
			{ //����Ϊ������ϵ
			 GetvLvVSC(); //���������Ħ�����  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWVSC(xSC,ySC); //�������������Ħ������   NCom,MWL,MWV,MW,
			 GetLVDensitySC(); //����͡�������ܶ�  OilDensity,GasDensity,vL,vV,MWL,MWV
			 API=141.5/(OilDensitySC/1000.)-131.5; //where So is the stock tank oil specific gravity, or relative density, to water at 60��F
			 GetGOR();
			 GetBo();
			}
			}  //�����ϵ�¶�û����׼�ٽ��¶ȣ��������������  ������������
			if(SCT>=pTc)
			{  //�����ϵ�¶ȴ���׼�ٽ��¶ȣ���ֻ���е����PVT����  �������á�L�����Ըõ�����м���
			 nvSC=-2; //����Ϊ���ٽ�����
			 GetParasOfComsInEOS(NCom,z,kij,Tci,Pci,SCT,SCP,Omegai,R,aL,bL,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS);
			 AL=aL*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BL=bL*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1;}  /* ��һ�����ظ���һ��ʵ������� ShowMessage("��ʵ��������ʵ��");*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);} /* ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);ShowMessage("����ʵ��");������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
											   //֮����ѡ�����ֵ����Ϊ��Сֵ�ڼ�������Ϊ�����������ֵͨ���������ʵ��
			 GetvLvVSC(); //���������Ħ�����  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWVSC(z,ySC); //�������������Ħ������  ,�����ǵ�һ�����࣬�����z����x�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vV=1.;
			 GetLDensitySC(); //��ø���ϵ��������棩���ܶ�
			 API=141.5/(OilDensitySC/1000.)-131.5; //where So is the stock tank oil specific gravity, or relative density, to water at 60��F
			 GetGOR();
			 GetBo();
			}
			} ////flash calculation end
			void FlashCalculation()   //��һ��StrSeg�ļ��㺯��
			{ ////flash calculation start
			//��ֻ�ǿ�����������ֵ��������û�ж���֣�ֻ�Ƕ����ɵ��ͺ���������̬����
			z[0]=GGIFromKerogen/MW[0]; //����Ħ����
			z[1]=OGIFromKerogen/MW[1]; //�͵�Ħ����
			double tteemm=z[0]+z[1];
			z[0]=z[0]/tteemm; //����Ħ����
			z[1]=z[1]/tteemm; //�͵�Ħ����
			if(z[0]<1.0e-5){ z[0]=1.0e-5;z[1]=1.0-z[0];}
			if(z[1]<1.0e-5){ z[1]=1.0e-5;z[0]=1.0-z[1];}
			TmK=Tm+273.15;
			PmMPa=Pm/1.0e6;
			SolutionOfCE aSCEZ;
			double ObjectiveValueInFlash; //Danish,1998  P174     =1.0e-12;
			double ErrorValue_fiLfiV;
			double XigemaKizi;
			double XigemaziBiKi;
			double wcx=1.e-5;
			double nvLeftPoint; //���ַ�nv��˵㣬  ��ʼֵΪ0
			double nvRightPoint; //���ַ�nv�Ҷ˵㣬 ��ʼֵΪ1
			double nvMiddlePoint; //���ַ����м�㣬Ϊ���Ҷ˵�͵�һ��
			double aa,bb,cc,dd; //cubic EOS --����״̬���̵�ϵ��
			ObjectiveValueInFlash=1.0e-12;
			double KiMin,KiMax; //��¼��ֵ�ƽ��ȵ���Сֵ�����ֵ
			GetpTcpPc();  //��û����׼�ٽ��¶Ⱥ�ѹ��ֵ�������жϻ�����¶��Ƿ񳬹��ٽ��¶ȣ���������򲻽����������㣬����ֱ�Ӽ����ܶ�
			if(TmK<pTc)
			{  //�����ϵ�¶�û����׼�ٽ��¶ȣ�������������� ����������ʼ
			GetBubblePointPressure(); //�����ϵ���ݵ�ѹ��
			GetInitKi();  //���ÿһ��ֵĳ�ʼ��ƽ���Ki��Danesh 1998, (3.66)P122
			do
			{
			KiMin=K[0];KiMax=K[0];
			for(int i=1;i<NCom;i++) {if(K[i]<KiMin) KiMin=K[i]; if(K[i]>KiMax) KiMax=K[i];}
			if(fabs(1-KiMax)<1e-8||fabs(1-KiMin)<1e-8)  {nv=-10000.; break;}
			   nvLeftPoint=1./(1.-KiMax); //nvֵ����˵�   ,Whitson 1989 The negative flash  P52
			   nvRightPoint=1./(1.-KiMin); //nvֵ���Ҷ˵�  ,Whitson 1989 The negative flash  P52
			   nvMiddlePoint=(nvLeftPoint+nvRightPoint)/2.;  //��ʼֵ
			   nv=NewtonIterationFornv(nvMiddlePoint);    //��ţ�ٵ�������nvֵ
				nl=1-nv;
				for(int i=0;i<NCom;i++)
				  {
					x[i]=z[i]/(1.0+(K[i]-1.0)*nv);
					y[i]=z[i]*K[i]/(1.0+(K[i]-1.0)*nv);
				  }
			 GetParasOfComsInEOS(x,aL,bL); //���Ӧ�������a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* ��һ�����ظ���һ��ʵ�������*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);}/* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ��;;���������������Ҫѡ�����е����ֵ */
			 GetParasOfComsInEOS(y,aV,bV); //���Ӧ�������a,b
			 AV=aV*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BV=bV*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AV,BV); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; } /* ��һ�����ظ���һ��ʵ������� */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); } /* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
			 GetFaii(FaiiL,x,aL,bL,AL,BL,ZL) ; //��������ݶ�ϵ��
			 GetFaii(FaiiV,y,aV,bV,AV,BV,ZV) ; //��������ݶ�ϵ��
			 Getfi_K();    //���������̬��ֵ��ݶ��Լ���ֵ�ƽ���   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
			 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
			}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);   //  &&runtimes<=100
			if(nv<0||nv>1)
			{ //nv<0,���� ��ϵΪ��һ��Һ�࣬nv>1,������ϵ�ǵ�һ�����࣬������������ܶ�
			 GetParasOfComsInEOS(z,aL,bL); //���Ӧ����ϵ��a,b   ������Ȼʹ�õ�����ķ��š�L��������nv>1�������Ҳ���ڼ�������
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(nv<0)
			 { //nv<0,���� ��ϵΪ��һ��Һ��
			 aHCType=Oil;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //֮���Խ�y[i]Ҳ��ֵ����Ϊ�����Ժ�ļ����з�ֹ���ֳ���0���������ʵ��y[i]�ǲ����ڵ�
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* ��һ�����ظ���һ��ʵ������� */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }/* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5
			 GetMWLMWV(x,y); //�������������Ħ������  ,�����ǵ�һ�����࣬�����z����x�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vV=1.;
			 GetLDensity(); //���������ܶ�
			 }
			 if(nv>1)
			 { //nv>1,������ϵ�ǵ�һ������
			 aHCType=Gas;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //֮���Խ�x[i]Ҳ��ֵ����Ϊ�����Ժ�ļ����з�ֹ���ֳ���0���������ʵ��x[i]�ǲ����ڵ�
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; }  // ��һ�����ظ���һ��ʵ�������
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }// ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ��
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5   ,
			 GetMWLMWV(x,y); //�������������Ħ������ ,�����ǵ�һ�����࣬�����z����y�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vL=1.;
			 GetVDensity(); //���������ܶ�
			 }
			}
			else
			{ //����Ϊ������ϵ
			 aHCType=OilGas;
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(x,y); //�������������Ħ������   NCom,MWL,MWV,MW,
			 GetLVDensity(); //����͡�������ܶ�  OilDensity,GasDensity,vL,vV,MWL,MWV
			}
			}  //�����ϵ�¶�û����׼�ٽ��¶ȣ��������������  ������������
			if(TmK>=pTc)
			{  //�����ϵ�¶ȴ���׼�ٽ��¶ȣ���ֻ���е����PVT����  �������á�L�����Ըõ�����м���
			 nv=-2; //����Ϊ���ٽ�����
			 aHCType=Oil; //���ٽ�����������
			 GetParasOfComsInEOS(z,aL,bL);  //���Ӧ�������a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1;}  /* ��һ�����ظ���һ��ʵ������� ShowMessage("��ʵ��������ʵ��");*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);} /* ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);ShowMessage("����ʵ��");������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
											   //֮����ѡ�����ֵ����Ϊ��Сֵ�ڼ�������Ϊ�����������ֵͨ���������ʵ��
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //֮���Խ�y[i]Ҳ��ֵ����Ϊ�����Ժ�ļ����з�ֹ���ֳ���0���������ʵ��y[i]�ǲ����ڵ�
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(z,y); //�������������Ħ������  ,�����ǵ�һ�����࣬�����z����x�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vV=1.;
			 GetLDensity(); //��ø���ϵ��������棩���ܶ�
			}
			} ////flash calculation end

			void FlashCalculation(StrSeg *aStrSeg)
			{ ////flash calculation start
			//��ֻ�ǿ�����������ֵ��������û�ж���֣�ֻ�Ƕ����ɵ��ͺ���������̬����
			z[0]=GGIFromKerogen/MW[0]; //����Ħ����
			z[1]=OGIFromKerogen/MW[1]; //�͵�Ħ����
			double tteemm=z[0]+z[1];
			z[0]=z[0]/tteemm; //����Ħ����
			z[1]=z[1]/tteemm; //�͵�Ħ����
			if(z[0]<1.0e-5){ z[0]=1.0e-5;z[1]=1.0-z[0];}  //Ϊ�����ȶ����㣬���趨һ������ֵ���Сֵ
			if(z[1]<1.0e-5){ z[1]=1.0e-5;z[0]=1.0-z[1];}   //Ϊ�����ȶ����㣬���趨һ������ֵ���Сֵ
			TmK=Tm+273.15;
			PmMPa=Pm/1.0e6;
			SolutionOfCE aSCEZ;
			double ObjectiveValueInFlash; //Danish,1998  P174     =1.0e-12;
			double ErrorValue_fiLfiV;
			double XigemaKizi;
			double XigemaziBiKi;
			double nvLeftPoint; //���ַ�nv��˵㣬  ��ʼֵΪ0
			double nvRightPoint; //���ַ�nv�Ҷ˵㣬 ��ʼֵΪ1
			double nvMiddlePoint; //���ַ����м�㣬Ϊ���Ҷ˵�͵�һ��
			double aa,bb,cc,dd; //cubic EOS --����״̬���̵�ϵ��
			ObjectiveValueInFlash=1.0e-12;
			double KiMin,KiMax; //��¼��ֵ�ƽ��ȵ���Сֵ�����ֵ
			GetpTcpPc();  //��û����׼�ٽ��¶Ⱥ�ѹ��ֵ�������жϻ�����¶��Ƿ񳬹��ٽ��¶ȣ���������򲻽����������㣬����ֱ�Ӽ����ܶ�
			for(int i=0;i<NCom;i++) K[i]=aStrSeg->K[i];
			if(TmK<pTc)
			{  //�����ϵ�¶�û����׼�ٽ��¶ȣ�������������� ����������ʼ
			GetBubblePointPressure(); //�����ϵ���ݵ�ѹ��
			do
			{
			KiMin=K[0];KiMax=K[0];
			for(int i=1;i<NCom;i++) {if(K[i]<KiMin) KiMin=K[i]; if(K[i]>KiMax) KiMax=K[i];}
			if(fabs(1-KiMax)<1e-8||fabs(1-KiMin)<1e-8)  {nv=-10000.; break;}
			   nvLeftPoint=1./(1.-KiMax); //nvֵ����˵�   ,Whitson 1989 The negative flash  P52
			   nvRightPoint=1./(1.-KiMin); //nvֵ���Ҷ˵�  ,Whitson 1989 The negative flash  P52
			   nvMiddlePoint=(nvLeftPoint+nvRightPoint)/2.;  //��ʼֵ
			   nv=NewtonIterationFornv(nvMiddlePoint);    //��ţ�ٵ�������nvֵ
				nl=1-nv;
				for(int i=0;i<NCom;i++)
				  {
					x[i]=z[i]/(1.0+(K[i]-1.0)*nv);
					y[i]=z[i]*K[i]/(1.0+(K[i]-1.0)*nv);
				  }
			 GetParasOfComsInEOS(x,aL,bL); //���Ӧ�������a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* ��һ�����ظ���һ��ʵ�������*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);}/* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ��;���������������Ҫѡ�����е����ֵ */
			 GetParasOfComsInEOS(y,aV,bV); //���Ӧ�������a,b
			 AV=aV*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BV=bV*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AV,BV); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; } /* ��һ�����ظ���һ��ʵ������� */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); } /* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
			 GetFaii(FaiiL,x,aL,bL,AL,BL,ZL) ; //��������ݶ�ϵ��
			 GetFaii(FaiiV,y,aV,bV,AV,BV,ZV) ; //��������ݶ�ϵ��
			 Getfi_K();    //���������̬��ֵ��ݶ��Լ���ֵ�ƽ���   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
			 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
			}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);   //  &&runtimes<=100
			if(nv<0||nv>1)
					  //else  //����ز�ѹ�������ݵ�ѹ��������㵥һ��Һ̬
			{ //nv<0,���� ��ϵΪ��һ��Һ�࣬nv>1,������ϵ�ǵ�һ�����࣬������������ܶ�
			 GetParasOfComsInEOS(z,aL,bL); //���Ӧ����ϵ��a,b   ������Ȼʹ�õ�����ķ��š�L��������nv>1�������Ҳ���ڼ�������
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(nv<0)
			 { //nv<0,���� ��ϵΪ��һ��Һ��
			 aHCType=Oil;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //֮���Խ�y[i]Ҳ��ֵ����Ϊ�����Ժ�ļ����з�ֹ���ֳ���0���������ʵ��y[i]�ǲ����ڵ�
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* ��һ�����ظ���һ��ʵ������� */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }/* ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5
			 GetMWLMWV(x,y); //�������������Ħ������  ,�����ǵ�һ�����࣬�����z����x�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vV=1.;
			 GetLDensity(); //���������ܶ�
			 }
			 if(nv>1)
			 { //nv>1,������ϵ�ǵ�һ������
			 aHCType=Gas;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //֮���Խ�x[i]Ҳ��ֵ����Ϊ�����Ժ�ļ����з�ֹ���ֳ���0���������ʵ��x[i]�ǲ����ڵ�
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; }  // ��һ�����ظ���һ��ʵ�������
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }// ������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ��
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5   ,
			 GetMWLMWV(x,y); //�������������Ħ������ ,�����ǵ�һ�����࣬�����z����y�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vL=1.;
			 GetVDensity(); //���������ܶ�
			 }  /* */
			}
			else
			{ //����Ϊ������ϵ
			 aHCType=OilGas;
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(x,y); //�������������Ħ������   NCom,MWL,MWV,MW,
			 GetLVDensity(); //����͡�������ܶ�  OilDensity,GasDensity,vL,vV,MWL,MWV
			}
			}  //�����ϵ�¶�û����׼�ٽ��¶ȣ��������������  ������������
			if(TmK>=pTc)
			{  //�����ϵ�¶ȴ���׼�ٽ��¶ȣ���ֻ���е����PVT����  �������á�L�����Ըõ�����м���
			 nv=-2; //����Ϊ���ٽ�����
			 aHCType=Oil; //���ٽ�������Ϊ�ʹ���
			 GetParasOfComsInEOS(z,aL,bL);  //���Ӧ�������a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //���� ��Ӧ�������cubic EOS --����״̬���̵�ϵ��
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1;}  /* ��һ�����ظ���һ��ʵ������� ShowMessage("��ʵ��������ʵ��");*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);} /* ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);ShowMessage("����ʵ��");������ʵ�����������Case==3Ϊ�������ظ���Case==4Ϊ��������ͬʵ�� */
											   //֮����ѡ�����ֵ����Ϊ��Сֵ�ڼ�������Ϊ�����������ֵͨ���������ʵ��
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //֮���Խ�y[i]Ҳ��ֵ����Ϊ�����Ժ�ļ����з�ֹ���ֳ���0���������ʵ��y[i]�ǲ����ڵ�
			 GetvLvV(); //���������Ħ�����  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(x,y); //�������������Ħ������  ,�����ǵ�һ�����࣬�����z����x�����������������ڲ�����������ĺ��������ֻ�ǽ��������㣬������ʾ���
			 vV=1.;
			 GetLDensity(); //��ø���ϵ��������棩���ܶ�
			}
			} ////flash calculation end

			//====================flash Calculation End ����̬������� ����

			//------------------------- ���� END----------------------------------
			
			StrSeg()
			{
				Init();
			}

			void Init()
			{
				pos_i = 0;
				pos_j = 0;
				pos_k = 0; //��¼�õز������ά�����е�����
				EndPoint = 0; //��¼�ز�����һ��ʱ������ά�����е�����

				MarginOfErrorThickness = 0; //�ж�����ʴ������ݴ������
				Ma2Second = 0;

				LithNumber = 0;   //������Եĸ���
				LithRatio = 0; //������Եı��� ���ز�εĸ��������������ݻ�����Եı���������

				BeginAge = 0; //�ز�ο�ʼʱ��
				EndAge = 0;   //�ز�ν���ʱ��
				MiddleAge = 0;//�ز���м�ʱ��
				DeltaAge = 0; //�ز�λ��¼����������

				Property = 0;   //�ز�����ʣ�1�ǵز㣬2����㣬3�ǰ�ʴ��4�������
				ConnectingMarker = 0;  //���Ͱ�ʴ�¼��Ĺ������
				VirtualErosionPair = 0; //���StrSeg�����Ӧ�İ�ʴStrSeg�����ԣ������������ÿһ�����StrSeg��VirtualErosionPairֵ��Ψһ�Ķ�Ӧ��һ����ʴ�¼���StrSeg��VirtualErosionPairֵ��ͬ��
				Eroded = false; //�����ж�������Ƿ��Ѿ�����ʴ���ˣ���ʼ��ֵʱ����false
				SourceRock = false; //�����ж��Ƿ�ΪԴ��
				IsThisMatrixKerogenOrCoal = 0; //�жϻ��������Ƿ�Ϊ���Ҹ���ú

				MaxBuryMiddleDepth = 0; //�ز�ξ������������в����
				MaxBuryTopDepth = 0;    //�ز�ξ����������ض������
				MaxBuryBottomDepth = 0; //�ز�ξ����������صײ����
				TopDepth = 0; //�������  ��ָ���Ǽ����˹�ˮ��Ķ������
				BottomDepth = 0;//�������
				MiddleDepth = 0;//�в����
				BuryTopDepth = 0; //���������� �������ˮ�ֻ�ǳ��������ȣ��ӳ�����-ˮ������������
				BuryBottomDepth = 0;//����������
				BuryMiddleDepth = 0;//�в�������
				CurrentThickness = 0;//�ֽ�ĺ��(������ز�)����ʴ���Ϊ��   = 0;�ز�������ֽ�ĺ�ȼ���Ӧ�������ȵĺ��
				Thickness = 0; //���
				MatrixThickness = 0;//�Ǽܺ��
				//������Щѹ���ĵ�λ�����ù��ʵ�λ�ƣ���˹��
				Pt = 0;
				Pm = 0;
				Pb = 0; //�ز�ζ������в��͵ײ�����ѹ��
				Ut = 0;
				Um = 0;
				Ub = 0; //�ֱ�Ϊ�������в��͵ײ������峬ѹ
				StaticPt = 0;
				StaticPm = 0;
				StaticPb = 0; //�ز�ζ������в��͵ײ�������ѹ��
				Plt = 0;
				Plm = 0;
				Plb = 0; //����ѹ��,�ֱ���StrSeg�������в����͵ײ��ľ���ѹ��
				Ult = 0;
				Ulm = 0;
				Ulb = 0; //��������,�ֱ���StrSeg�������в����͵ײ��ľ�������
				EffectiveStresst = 0;EffectiveStressm = 0; EffectiveStressb = 0; //��ЧӦ�����ֱ���StrSeg�������в����͵ײ���
				MaxEffectiveStresst = 0;MaxEffectiveStressm = 0;MaxEffectiveStressb = 0;  //��¼StrSeg�����������ЧӦ��

				COC = 0;//ѹ��ϵ�� Coefficient Of Compressibility
				aOverpressure = 0;bOverpressure = 0;cOverpressure = 0; //��ѹ�����е���������

				vFluild = 0; //���������ٶȣ���һ����û�õ�
				vWater = 0; //�ز�ˮ����

				InitialPorosity = 0;CompactionFactor = 0;  //��ʼ��϶�Ⱥ͹��ھ�ˮѹ����ȵ�Athy���ɵ�ѹʵϵ�� kArthDepth
				TInitialPorosity = 0;TCompactionFactor = 0;  //��ϵ�����ĳ�ʼ��϶�Ⱥ�ѹʵϵ��
				Porosityt = 0; //��������ԵĿ�϶�ȣ���϶��ΪС��;;����ֵ
				Porositym = 0;  // ��������ԵĿ�϶�ȣ���϶��ΪС��;;�в�ֵ
				Porosityb = 0;  // ��������ԵĿ�϶�ȣ���϶��ΪС��;;�ײ�ֵ
				Porot = 0;Porom = 0;Porob = 0; //Ϊ�����в��͵׵Ŀ�϶�� ��С��
				EndPorom = 0; //�ֽ�ز�Ŀ�϶��ֵ����������ڰ�ʴǰ��С�Ŀ�϶��ֵ�����ڱȽϵ���ǰ���϶�����ж��Ƿ����������ڳ�ѹ����
				DifferencePoromEndPorom = 0; //��������յĿ�϶��ֵ����һ�ε��������ʼ���Ŀ�϶�Ȳ�ֵ
				LogPermeability = 0; //��������Ե���͸����Ȼ����ֵ = 0;��λ��LogmD
				Perm = 0; // �ܵ���͸�� Permeability�� ��λ��m^2
				aPoro_Perm = 0; //��϶��-��͸�ʹ�ϵ���ݶ�

				Sw = 0;So = 0;Sg = 0; //ˮ���͡����ı��Ͷ�
				WaterViscosity = 0;  //ˮճ��

				MatrixDensity = 0; //��ͬ���Ի��ʵ��ܶ�
				TMatrixDensity = 0; //  �ܵĻ����ܶ�
				WaterDensity = 0; //�ز�ˮ�ܶ�
				OilDensity = 0; //���ܶ�
				GasDensity = 0; //���ܶ�
				SeaWaterDensity = 0;  //��ˮ�ܶ�ȡֵ=1025 kg/m^3
				TotalDensity = 0; //�ܵ���ʯ�ܶȣ��������е�����͹Ǽܵ��ۺ��ܶȣ�

				TotalThermalCond = 0; //�ܵ��ȵ���  ���������ʺͿ�϶���壩
				MatrixThermalCond = 0; //��ͬ�Ļ����ȵ���
				TMatrixThermalCond = 0; //�ܵĻ����ȵ���
				WaterThermalCond = 0; //�ز�ˮ�ȵ���
				OilThermalCond = 0; //���ȵ���
				GasThermalCond = 0; //���ȵ���
				PoreFluidThermalCond = 0; //��϶�����ȵ���
				IceThermalCond = 0; //���ȵ���
				GasHydratesThermalCond = 0; //��Ȼ��ˮ�����ȵ���

				TotalHeatCapacity = 0; //�ܵı����� ���������ʺͿ�϶���壩
				MatrixHeatCapacity = 0; //���ʱ����ݣ���ͬ�Ļ���
				TMatrixHeatCapacity = 0; //�ܵĻ��ʱ�����
				WaterHeatCapacity = 0; //�ز�ˮ������
				OilHeatCapacity = 0; //�ͱ�����
				GasHeatCapacity = 0; //��������
				IceHeatCapacity = 0; //��������
				GasHydratesHeatCapacity = 0; //��Ȼ��ˮ���������
				PoreFluidHeatCapacity = 0; //��϶���������


				MatrixRadioactiveHeat = 0;    //��ͬ���Ի��ʵķ�����
				Qr = 0; // �ܵķ�����

				PaleoWaterDepth = 0;//��¼��ˮ��
				SurfaceT = 0; //�ر��¶ȣ���¼������ĸ���
				HF = 0; //��¼������

				Tt = 0; //�����¶�
				Tm = 0; //�в��¶�
				Tb = 0; //�ײ��¶�
				Tmax = 0; //��¼ģ��������в�������¶�


				TTI = 0; //�ز��TTIֵ
				
				Ro[RO_TTI] = 0;  //�ز��Ro%ֵ
				Ro[RO_Simple] = 0;  //�ز��Ro%ֵ
				Ro[RO_Easy] = 0;  //�ز��Ro%ֵ
				Ro[RO_Basin] = 0;  //�ز��Ro%ֵ

				TTI0 = 0; //��ʼʱ�̵�TTIֵ
				aParaOfEasyRo = 0; //����һ��EasyRoģ�ͽṹ�����ڴ洢����
				aParaOfBasinRo = 0; //����һ��BasinRoģ�ͽṹ�����ڴ洢����
				aParaOfSimpleRo = 0; //����һ��SimpleRoģ�ͽṹ�����ڴ洢����

				TOC = 0; //�����л�̼����
				InitTOC = 0; //ԭʼ�л�̼���� ,�������ڵĵز������µ�ԭʼ�л�̼���������ֽ����ʯ�ܶ����� ������ֵֻ�����һ��ʱ��ĵز�δ���
				MassOfInitTOC = 0;//�õز�ε�λ�����m^2����ԭʼ�л�̼�������� �� ����ֵֻ�����һ��ʱ��ĵز�δ���

				aDR = 0;  //����һ�����Ҹ�����ṹ��

				for (int idx = RO_TTI; idx <= RO_Basin; idx++)
				{
					HCGI[idx] = 0; //  ����ǿ�� kg/m^2 �����ڽ�������ģ��
					OGI[idx] = 0; //oil generating intensity ,����ǿ�� kg/m^2 �����ڽ�������ģ��
					GGI[idx] = 0; //gas generating intensity ,����ǿ�� kg/m^2 �����ڽ�������ģ��
				}
				
				aParaLLNL = 0; //����һ��LLNL��ѧ��Ӧ����ѧ�����ṹ��
				OGI_LLNL = 0;   //oil generating intensity ,����ǿ�� kg/m^2  ,���ڻ�ѧ��Ӧ����ѧ����ģ��
				GGI_LLNL = 0;   //gas generating intensity ,����ǿ�� kg/m^2��Ҳ��������λ��  ,���ڻ�ѧ��Ӧ����ѧ����ģ��

				//2017/11/27:organo facies
				aOrganofacies = 0;
				aPetroGenStyle = LLNL;

				//
				PCOEt = 0.;//top pressure coefficient
				POCEm = 0.;//middle pressure coefficient
				POCEb = 0.;//bottom pressure coefficient

				//2018/8/15: new variables
				OilViscosity = 0.; //��ճ��
				GasViscosity = 0.; //��ճ��
				Swc = 0.,Soc = 0.,Sgc = 0.; // ����ˮ���Ͷȡ������ͱ��Ͷ� �����������Ͷ�    ,��С����ʾ
				Swe = 0.; //effective saturations Se��Чˮ���Ͷ�for krw and krow,       ,��С����ʾ
				Soe = 0.; // ��Ч�ͱ��Ͷ� ,��ʱû������    ,��С����ʾ
				Sgoe = 0.; //����Krog����Ч���Ͷ�  ,��С����ʾ
				Sge = 0.; // ��Ч�����Ͷ�,����Krg   ,��С����ʾ

				Krow = 0.,Krog = 0.; //
				Krw = 0.,Krg = 0.,Kro = 0.; //�ֱ���ˮ�������͵������͸��
				lamuda = 0.; 
				aToEntryPr = 0.,bToEntryPr = 0.;//��Ӧ��ͻ��ë��ѹ����ϵ��a��b,��Hantschel 2009 ,P411. Table A.6. Capillary Entry Pressure
				PcbMA = 0.; // ͻ��ë��ѹ��,ˮ��-����
				PcMA = 0.; //ë��ѹ����ˮ��-����
				PcbOW = 0.,PcbGW = 0.,PcbGO = 0.; //�ֱ�Ϊ��ˮ����ˮ�����͵�ͻ��ë��ѹ��
				PcOW = 0.,PcGW = 0.,PcGO = 0.; //�ֱ���ˮ����ˮ�����͵�ë��ѹ��
				RouML = 0.,RouMV = 0.; //�ֱ����ͺ�����Ħ���ܶȣ���λ��gmol/cm 3
				Tc = 0.,vc = 0.; //�ֱ�Ϊ��ϵ���ٽ��¶Ⱥ��ٽ�Ħ�����������Ħ��ƽ��ֵ��ȣ���λ�ֱ�ΪK��cm3/gmol
				TcL = 0.,TcV = 0.; //�ֱ��������������ٽ��¶ȣ���λ��K
				PXigema = 0.; //known as the parachor  ,���ű���
				IFTOilWater = 0.,IFTGasWater = 0.,IFTGasOil = 0.;//��ˮ����ˮ�����͵Ľ�������  interfacial tension (IFT) ����λ��mN/m

				//================== flash Calculation Start ,��̬�������
				SoTreshold = 0.;   //�ٽ����ͱ��Ͷȣ�ֵ��[0-1]֮��
				SgTreshold = 0.;   //�ٽ��������Ͷȣ�ֵ��[0-1]֮��

				Sgg = 0.; //��������ܶ�   ��Good Oil: Sgg= 0.855
				Soo = 0.;//�͵�����ܶ�     ; Good Oil:  Soo=0.823
				T_F = 0.; //�����¶�
				MolFraC1InWater = 0.; //molar fraction of methane in water
				
				nl = 0.,nv = 0.; //�ֱ���Һ̬����̬��Ħ������
				NCom = 0; //��N����ֵ�����
				aProperties = 0;
				x = 0,y = 0,z = 0;  //�ֱ�Ϊ��Һ���е����Ħ������/�������������е����Ħ������/�������ܵ����Ħ������
				K = 0; // The equality of fugacity can be expressed by the equilibrium ratio, K,  K[i] = y[i] / x[i]
				MW = 0;       //���Ħ������  kg/kgmol
				Tci = 0, Pci = 0, vci = 0; //����ٽ��¶ȡ�ѹ�������   K��MPa��m^3/kmol
				Omegai = 0; //the dimensionless acentric factor,����ֵ�
				kij = 0; //binary interaction parameter ��Ԫ�໥���ò���
				R = 0.;//���峣�� ��=0.008314;0.008314 KJ/(mol*K)
				aHCType = OilGas;

				//
				SCT = 0.; //��׼�����µ��¶�15.556���϶�
				SCTK = 0.; // ��׼�����µ��¶ȿ����¶�
				SCP = 0.; //��׼�����µ�ѹ��1 atm 0.1MPa
				pb = 0.; //��ϵ���ݵ�ѹ�� ��MPa
				TmK = 0.; //�в��¶ȣ��ÿ����¶ȱ�ʾ��������̬����
				PmMPa = 0.; //�в�ѹ������������ʾ��������̬����
				pTc = 0.; //׼�ٽ��¶� K   pseudo critical temperature  ,������ֵΪ��ϵ�¶�
				pPc = 0.; //׼�ٽ�ѹ�� MPa
				a = 0.,b = 0.; //�ֱ��Ӧ���ٽ���̬��aֵ��bֵ
				vL = 0.,vV = 0.;  //�ֱ����ͺ�����Ħ�����  m3/kgmol
				MWL = 0.,MWV = 0.; //�ֱ�������������Ħ������
				aci = 0,bi = 0,mi = 0,Alphai = 0,ai = 0;
				Ai = 0,Bi = 0; //
				aL = 0.,bL = 0.,aV = 0.,bV = 0.; //�ֱ��Ӧ���ͺ�����aֵ��bֵ
				aEOS = SRK;
				AL = 0.,AV = 0.,BL = 0.,BV = 0.; // �ֱ��Ӧ���ͺ���
				ZL = 0.,ZV = 0.; //Һ������壬���ͺ�����ѹ��ϵ��
				FaiiL = 0,FaiiV = 0; //�ֱ�Ϊ�͡�����̬����ֵ��ݶ�ϵ����fugacity coefficients��
				fiL = 0,fiV = 0; //�ֱ�Ϊ�͡�����̬����ֵ��ݶȣ�fugacities��

				//
				OilDensitySC = 0.; //��׼������ԭ�͵��ܶ�
				API = 0.; //��׼�������͵��ض�
				GOR = 0.;//���ͱ�  m3/m3
				Bo = 0.; //ԭ�����ϵ��������Ϊ����ԭ����������ԭ�����֮��
				KSC = 0;
				nvSC = 0.,nlSC = 0.;    //��׼����������������Ħ����
				xSC = 0,ySC = 0;
				MWLSC = 0.,vLSC = 0.,MWVSC = 0.,vVSC = 0.;
				GasDensitySC = 0.; // ��׼�����������ܶ�
			}

			void Release()
			{
				if (LithRatio)
				{
					delete LithRatio;
				}
				LithRatio = 0;

				//
				if (IsThisMatrixKerogenOrCoal)
				{
					delete IsThisMatrixKerogenOrCoal;
				}
				IsThisMatrixKerogenOrCoal = 0;
				
				//
				if (InitialPorosity)
				{
					delete InitialPorosity;
				}
				InitialPorosity = 0;

				//
				if (CompactionFactor)
				{
					delete CompactionFactor;
				}
				CompactionFactor = 0;

				//
				if (Porosityt)
				{
					delete Porosityt;
				}
				Porosityt = 0;

				//
				if (Porositym)
				{
					delete Porositym;
				}
				Porositym = 0;

				//
				if (Porosityb)
				{
					delete Porosityb;
				}
				Porosityb = 0;

				//
				if (LogPermeability)
				{
					delete LogPermeability;
				}
				LogPermeability = 0;

				//
				if (aPoro_Perm)
				{
					aPoro_Perm->Release();
					delete [] aPoro_Perm;
				}
				aPoro_Perm = 0;

				//
				if (MatrixDensity)
				{
					delete MatrixDensity;
				}
				MatrixDensity = 0;
				
				//
				if (MatrixThermalCond)
				{
					delete MatrixThermalCond;
				}
				MatrixThermalCond = 0;

				//
				if (MatrixHeatCapacity)
				{
					delete MatrixHeatCapacity;
				}
				MatrixHeatCapacity = 0;

				//
				if (MatrixRadioactiveHeat)
				{
					delete MatrixRadioactiveHeat;
				}
				MatrixRadioactiveHeat = 0;

				//
				if (aParaOfEasyRo)
				{
					aParaOfEasyRo->Release();
					delete aParaOfEasyRo;
				}
				aParaOfEasyRo = 0;

				//
				if (aParaOfBasinRo)
				{
					aParaOfBasinRo->Release();
					delete aParaOfBasinRo;
				}
				aParaOfBasinRo = 0;

				//
				if (aParaOfSimpleRo)
				{
					delete aParaOfSimpleRo;
				}
				aParaOfSimpleRo = 0;
					 
				//
				if (aDR)
				{
					aDR->Release();
					delete aDR;
				}
				aDR = 0;

				//
				if (aParaLLNL)
				{
					aParaLLNL->Release();
					delete aParaLLNL;
				}
				aParaLLNL = 0;

				//2017/11/27: aOrganofacies
				if (aOrganofacies)
				{
					aOrganofacies->Release();
					delete aOrganofacies;
				}
				aOrganofacies = 0;

				//2018/8/15: new variables
				if (aProperties)
				{
					aProperties->Release();
					delete aProperties;
				}
				aProperties = 0;

				//
				ReleaseProperties();
			}

			//
			void ReleaseProperties()
			{
				Properties tmp;
				tmp.DoRelease(x);
				tmp.DoRelease(y);
				tmp.DoRelease(z);
				tmp.DoRelease(K);
				tmp.DoRelease(MW);
				tmp.DoRelease(Tci);
				tmp.DoRelease(Pci);
				tmp.DoRelease(vci);
				tmp.DoRelease(Omegai);

				//
				if (kij)
				{
					//delete each element
					for (int i = 0; i < NCom; i++)
					{
						tmp.DoRelease(kij[i]);
					}

					delete kij;					
				}
				kij = 0;

				//
				tmp.DoRelease(aci);
				tmp.DoRelease(bi);
				tmp.DoRelease(mi);
				tmp.DoRelease(Alphai);
				tmp.DoRelease(ai);
				tmp.DoRelease(Ai);
				tmp.DoRelease(Bi);
				tmp.DoRelease(FaiiL);
				tmp.DoRelease(FaiiV);
				tmp.DoRelease(fiL);
				tmp.DoRelease(fiV);

				//
				tmp.DoRelease(KSC);
				tmp.DoRelease(xSC);
				tmp.DoRelease(ySC);
			}

			void GainHCGIPerUnitInitTOC(StrSeg *StrSegLeft)
			{ 
				//��õ�λ����ԭʼ�л�̼���������������� ,ͨ��LLNL��ѧ��Ӧ����ѧ�������
				//���ڳ��˳�ʼ��StrSeg
				switch(aPetroGenStyle)
				{
				case LLNL:
					if (!aParaLLNL)
					{
						aParaLLNL=new ParaLLNL;
					}
					aParaLLNL->CopyFrom(StrSegLeft->aParaLLNL);
					if(Property==2&&Eroded)
						aParaLLNL->Reactions(SurfaceT,BeginAge,SurfaceT,EndAge,StrSegLeft->aParaLLNL );  //����ǰ�ʴ����㣬����õر��¶Ƚ��м��㣬ʵ����ʲô�������
					else
						aParaLLNL->Reactions(StrSegLeft->Tm,BeginAge,Tm,EndAge,StrSegLeft->aParaLLNL );
					break;
				case Organo:

					if (!aOrganofacies)
					{
						aOrganofacies=new Organofacies;
					}					
					aOrganofacies->CopyFrom(StrSegLeft->aOrganofacies);
					if(Property==2&&Eroded)
						aOrganofacies->Reactions(SurfaceT,BeginAge,SurfaceT,EndAge,StrSegLeft->aOrganofacies );  //����ǰ�ʴ����㣬����õر��¶Ƚ��м��㣬ʵ����ʲô�������
					else
						aOrganofacies->Reactions(StrSegLeft->Tm,BeginAge,Tm,EndAge,StrSegLeft->aOrganofacies );
					break;
				};
			}
			
			void GainHCGIPerUnitInitTOC()
			{ //���ڳ�ʼ��StrSeg, ��õ�λ����ԭʼ�л�̼���������������� ,ͨ��LLNL��ѧ��Ӧ����ѧ�������
				switch(aPetroGenStyle)
				{
				case LLNL:
					if (aParaLLNL)
					{
						aParaLLNL->Reactions(SurfaceT,BeginAge,Tm,EndAge);
					}					
					break;
				case Organo:
					if (aOrganofacies)
					{
						aOrganofacies->Reactions(SurfaceT,BeginAge,Tm,EndAge);
					}					
					break;
				};

			}
			
			//���ԭʼ�л�̼����������    ;;����20170908
			void GainInitTOC()  
			{            
				 //���ﵽ�˵ز��ģ������һ��ʱ���ʱִ�м���
				if(pos_k==EndPoint)
				{ 
					switch(aPetroGenStyle)
					{
					case LLNL:
						if (aParaLLNL)//LLNL����ѧ��Ӧ
						{
							aParaLLNL->DoRelease(aParaLLNL->InitTOC);
							aParaLLNL->DoRelease(aParaLLNL->MassOfInitTOC);
							aParaLLNL->InitTOC=new double[aParaLLNL->NKerogenType];
							aParaLLNL->InitTOC[0]=aParaLLNL->RatioKerogenType[0]*TOC/aParaLLNL->TOCRemained_I;
							aParaLLNL->InitTOC[1]=aParaLLNL->RatioKerogenType[1]*TOC/aParaLLNL->TOCRemained_II;
							aParaLLNL->InitTOC[2]=aParaLLNL->RatioKerogenType[2]*TOC/aParaLLNL->TOCRemained_III;
							aParaLLNL->MassOfInitTOC=new double[aParaLLNL->NKerogenType];
							aParaLLNL->MassOfInitTOC[0]=Thickness*TMatrixDensity*(1.0-Porom)*aParaLLNL->InitTOC[0]/100.;
							aParaLLNL->MassOfInitTOC[1]=Thickness*TMatrixDensity*(1.0-Porom)*aParaLLNL->InitTOC[1]/100.;
							aParaLLNL->MassOfInitTOC[2]=Thickness*TMatrixDensity*(1.0-Porom)*aParaLLNL->InitTOC[2]/100.;
							aParaLLNL->MassOfInitTOCTotal=aParaLLNL->MassOfInitTOC[0]+aParaLLNL->MassOfInitTOC[1]+aParaLLNL->MassOfInitTOC[2];
						}						
						break;
					case Organo:
						if (aOrganofacies)
						{
							aOrganofacies->InitTOC=TOC/aOrganofacies->TOCRemained;
							aOrganofacies->MassOfInitTOCTotal=Thickness*TMatrixDensity*(1.0-Porom)*aOrganofacies->InitTOC/100.;
						}
						break;
					};
				}
			}
			
			void GetHCGIPerUnitInitTOC(StrSeg *StrSegLeft)
			{   //��õ�λ����ԭʼ�л�̼������������������������ ,ͨ���л�̼��������Ro��ϵ���߻��
				//���ڳ��˳�ʼ��StrSeg

				if (!aDR)
				{
					aDR=new DR; //�½�һ�����Ҹ�����ṹ��
				}
								
				aDR->CopyFrom(StrSegLeft->aDR);  //���ϸ�ʱ�̵ĵز�εĸ��Ҹ�����ṹ�������ֵ�����ڵĽṹ��
				aDR->GetHCFromDR(Ro);
			}
			
			void GetHCGIPerUnitInitTOC()
			{   //��õ�λ����ԭʼ�л�̼������������������������,ͨ���л�̼��������Ro��ϵ���߻��
				//���ڳ�ʼ��StrSeg

				if (aDR)
				{
					aDR->GetHCFromDR(Ro);
				}
			}
			
			void GetInitTOC()  //���ԭʼ�л�̼���������������ڽ�����-Ro����
			{
				if (!aDR)
				{
					return;
				}

				if(pos_k==EndPoint)
				{  //���ﵽ�˵ز��ģ������һ��ʱ���ʱִ�м���

					for (int idx = RO_TTI; idx <= RO_Basin; idx++)
					{
						aDR->InitTOCI[idx]=TOC*aDR->Ratio[0]/(1.0-aDR->HCFromDRI[idx]/100.);
						aDR->InitTOCIIA[idx]=TOC*aDR->Ratio[1]/(1.0-aDR->HCFromDRIIA[idx]/100.);
						aDR->InitTOCIIB[idx]=TOC*aDR->Ratio[2]/(1.0-aDR->HCFromDRIIB[idx]/100.);
						aDR->InitTOCIII[idx]=TOC*aDR->Ratio[3]/(1.0-aDR->HCFromDRIII[idx]/100.);
						
						aDR->MassInitTOCI[idx]=Thickness*TMatrixDensity*(1.0-Porom)*aDR->InitTOCI[idx]/100.;
						aDR->MassInitTOCIIA[idx]=Thickness*TMatrixDensity*(1.0-Porom)*aDR->InitTOCIIA[idx]/100.;
						aDR->MassInitTOCIIB[idx]=Thickness*TMatrixDensity*(1.0-Porom)*aDR->InitTOCIIB[idx]/100.;
						aDR->MassInitTOCIII[idx]=Thickness*TMatrixDensity*(1.0-Porom)*aDR->InitTOCIII[idx]/100.;
					}
				}
			}

			void GetT()
			{  //���µģ������ģ��ز���¶ȼ��� ,��̬��ʽ
				double TempTm;
				double wcx;
				Tt=SurfaceT;
				Tm =SurfaceT;//���Ƚ��ر��¶ȸ�ֵ���ز���в��¶�
				do{
				GetTotalThermalCond();
				TempTm=Tt+HF*0.5*Thickness/TotalThermalCond;
				wcx=fabs(Tm-TempTm);
				Tm=TempTm;
				}while(wcx>0.0001);
				Tb=Tm+HF*0.5*Thickness/TotalThermalCond;
			}

			void GetT(StrSeg *StrSegLeft, StrSeg *StrSegTop)
			{  //���������µģ������ģ��ز���¶ȼ��� ,��̬��ʽ
				double TempTm;
				double wcx;
				Tt=StrSegTop->Tb; //����֮�ϵ�StrSeg�ĵײ��¶ȸ�����StrSeg����
				Tm =StrSegLeft->Tm;//���Ƚ����ز���в��¶ȸ�ֵ���ز���в��¶�
				do{
				GetTotalThermalCond();
				TempTm=Tt+HF*0.5*Thickness/TotalThermalCond;  //���û�б���ʴ�������ȫ���ĺ��--Thickness������
				wcx=fabs(Tm-TempTm);
				Tm=TempTm;
				}while(wcx>0.0001);
				Tb=Tm+HF*0.5*Thickness/TotalThermalCond;
			}
			
			void GetTmax(StrSeg *StrSegLeft)
			{  //���������ڻ���ǰ����������¶�
				if(Tm>StrSegLeft->Tmax ) Tmax=Tm;
				else Tmax=StrSegLeft->Tmax;
			}
			
			void GetPoreFluidThermalCond()
			{  //��ÿ�϶�����ȵ���
				GetWaterThermalCond();
				GetOilThermalCond();
				GetGasThermalCond();
				GetIceThermalCond();
				GetGasHydratesThermalCond();
				PoreFluidThermalCond=pow(WaterThermalCond,Sw)+pow(OilThermalCond,So)+pow(GasThermalCond,Sg);   //�����Sw,So,Sg��ʱ��û��ֵ
			}
			
			void GetTotalThermalCond()
			{  // ���ȵ����ɻ��ʺͿ�϶�ȵ��ʵļ���ƽ��ֵ�õ�
				GetMatrixThermalCond();
				GetPoreFluidThermalCond();
				TotalThermalCond=pow(TMatrixThermalCond,1.0-Porom)*pow(WaterThermalCond,Porom);  //��û���ÿ�϶�����ȵ��ʣ���Ϊ PoreFluidThermalCond ��û�и�ֵ
				//�����Ϊ�����ӵĻ����ʽ������Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling������������Ҫʱ�ɲο�  ;���Ƚ��뼸��ƽ���㷨������ȵ���Ҫ��һЩ��������һ��
				// double Z= WaterThermalCond/MatrixThermalCond;
			//  double aerf=5.0;double E=(1.0-Z)/(1.0+aerf*Z);
				// TotalThermalCond= MatrixThermalCond*(1.0-E*Porom)/(1.0+aerf*E*Porom);
			}
			
			void GetWaterThermalCond()
			{
				//���� Deming and Chapman (1989) ,ԭ�ģ�  ��λW/(mK)
				double A1 = 0.565;
				double B1 = 0.00188;
				double C1 = -7.23e-6;
				double A2 =0.602;
				double B2 = 0.00131;
				double C2 = -5.14e-6;
				if((Tm)<=137) WaterThermalCond=A1+B1*Tm+C1*Tm*Tm; //����õ����ȴ�����λ��W/(m��)
				if((Tm)>137) WaterThermalCond=A2+B2*Tm+C2*Tm*Tm;  //����õ����ȴ�����λ��W/(m��)
			}
			
			void GetOilThermalCond()
			{   //conductivities of liquid petroleum   ��after Hantschel et al., 2009  ��������֤
				if(Tm<240) OilThermalCond=0.2389-4.593e-4*(Tm+273.15)+2.676e-7*(Tm+273.15)*(Tm+273.15);   //����õ����ȴ�����λ��W/(m��)
				else OilThermalCond= 0.075;                                    //����õ����ȴ�����λ��W/(m��)
			}
			
			void GetGasThermalCond()
			{   //conductivities of vapor petroleum   ��after Hantschel et al., 2009  ��������֤
				if(Tm<120) GasThermalCond=-0.0969+4.37e-4*(Tm+273.15);                //����õ����ȴ�����λ��W/(m��)
				else GasThermalCond= 0.075;                                    //����õ����ȴ�����λ��W/(m��)
			}
			
			void GetIceThermalCond() { IceThermalCond=2.23; } //���ȵ��ʣ� ��λ��W/(m��)��ֻ�Ǹ�ֵ�ˣ���û��Ӧ��
			
			void GetGasHydratesThermalCond() {GasHydratesThermalCond=0.49; } //��Ȼ��ˮ�����ȵ��ʣ� ��λ��W/(m��) ��ֻ�Ǹ�ֵ�ˣ���û��Ӧ��
			
			void GetMatrixThermalCond()
			{  //�ȵ��ʣ����յõ�kg.m.s��λ�ƣ�
				TMatrixThermalCond=1.;
				for(int i=0;i<LithNumber;i++)
				TMatrixThermalCond*=pow(MatrixThermalCond[i],LithRatio[i]); //����õ����ȴ�����λ��W/(m��);�õ����Ǽ���ƽ��ֵ
				TMatrixThermalCond=358.*(1.0227*TMatrixThermalCond-1.882)*(1./(Tm+273.15)-0.00068)+1.84; //�����ȴ������¶ȵı仯����Sekiguchi�CWaples Model   ��������֤
			}
			
			void GetMatrixHeatCapacity()
			{   //����õ����ݵĵ�λ��J/(kg��);�õ���������ƽ��ֵ
				TMatrixHeatCapacity=0.;
				double c20; //20��ʱ�ı�����
				double cT; //�ֽ��¶��µı�����
				for(int i=0;i<LithNumber;i++)
				{
					c20=MatrixHeatCapacity[i]; 
					if(!IsThisMatrixKerogenOrCoal[i])  //���Ǹ��Ҹ���ú������£�����֤   //from Waples and Waples (2004a) ��Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
					cT=c20*(0.953+2.29e-3*Tm-2.835e-6*Tm*Tm+1.191e-9*Tm*Tm*Tm);
					if(IsThisMatrixKerogenOrCoal[i]) //�Ǹ��Ҹ���ú������� ��ֱ�Ӹ�������Ĺ�ʽ������������֤    from Waples and Waples (2004a) ��Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
					cT=1214.3+6.2657*Tm-0.12345*Tm*Tm+1.7165e-3*Tm*Tm*Tm-1.1491e-5*Tm*Tm*Tm*Tm+3.5686e-8*Tm*Tm*Tm*Tm*Tm-4.1208e-11*Tm*Tm*Tm*Tm*Tm*Tm;
					TMatrixHeatCapacity+=LithRatio[i]*cT;   //����õ����ݵĵ�λ��J/(kg��);�õ���������ƽ��ֵ
				}
			}
			
			void GetQr()
			{  //��õز�ķ�����������������ÿ�����Եķ��������ȹ̶�ֵ�����Ա�������
				Qr=0.;
				for(int i=0;i<LithNumber;i++)
				Qr+=MatrixRadioactiveHeat[i]*LithRatio[i];    //��û�ϻ��ʵķ�����������
				Qr*=(1.0-Porom);                 //��õز�ķ���������������ʱ�ĵ�λ���Ǧ�W/m^3
				Qr*=1.0e-6;           //ת��ΪW/m^3
			}
			
			void GetWaterHeatCapacity()
			{   //ˮ�����ݼ���  ���Ѿ���֤����ʽ����Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
				if(Tm<=290) WaterHeatCapacity=(4245.-1.841*Tm);   //��λ��J/m/K
				if(Tm>290)  WaterHeatCapacity=3703*exp(-0.00481*(Tm-290)+2.34*0.0001*(Tm-290)*(Tm-290));  //��λ��J/m/K
			}
			
			void GetOilHeatCapacity()
			{  //�ͱ����ݼ���  ���Ѿ���֤����ʽ����Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
				OilDensity=800.; //�����ȼٶ����ܶ�Ϊ800kg/m^3;
				OilHeatCapacity=(1684.+3.389*Tm)*sqrt(OilDensity/1000.);  //��λ��J/m/K ,
			}
			
			void GetGasHeatCapacity()
			{  //�������ݼ���  ���Ѿ���֤����ʽ����Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
				GasHeatCapacity=3250;  //��λ��J/m/K   ,from (Waples and Waples, 2004b)
			}
			
			void GetIceHeatCapactiy()  //�Ѿ���֤   ����Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
			{ IceHeatCapacity=2115.;  } //��λ��J/m/K
			
			void GetGasHydratesHeatCapactiy() //�Ѿ���֤  ����Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
			{ GasHydratesHeatCapacity=2090.+7.235*Tm+0.0199*Tm*Tm;   } //
			
			void GetPoreFluidHeatCapacity()
			{
				GetWaterHeatCapacity();
				GetOilHeatCapacity();
				GetGasHeatCapacity();
				GetIceHeatCapactiy();
				GetGasHydratesHeatCapactiy();
				PoreFluidHeatCapacity=WaterHeatCapacity*Sw+OilHeatCapacity*So+GasHeatCapacity*Sg;
			}
			
			void GetTotalHeatCapacity()
			{
				GetMatrixHeatCapacity();
				GetPoreFluidHeatCapacity();
				TotalHeatCapacity=TMatrixHeatCapacity*(1.0-Porom)+WaterHeatCapacity*Porom;
			}  
			
			void GetvWater()
			{   //���ˮ�Ĵ������� ,��λ��m/m.y.
				vWater=-Perm/WaterViscosity*(Ut-Ub)/Thickness;
				vWater*=Ma2Second;       //��vWaterת��Ϊm/my
			}
			
			void GetWaterDensity()
			{  //�õ�һ���¶Ⱥ�ѹ���µĵز�ˮ�ܶ�
				double WaterDensityStandardCond=1040.; //��λ��kg/m^3
				double Aerf=5.0e-4; //��^-1
				double Beita=4.3e-4; //MPa^-1
				WaterDensity=WaterDensityStandardCond*exp(Beita*(Pm/1.0e6-0.1)-Aerf*(Tm-25.));
			}
			
			void GetMatrixDensity()
			{  //�õ����ܶȵ�λ��kg/m^3
				TMatrixDensity=0.;
				for(int i=0;i<LithNumber;i++)
				TMatrixDensity+=LithRatio[i]*MatrixDensity[i];
			}
			
			void GetStaticPressure()
			{ //���ڶ�������,��λ��˹�� ,ֻ��������ʵ�ĵز㣬�����ڰ�ʴ�¼�
				StaticPt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;  //ˮ���澻ˮѹ������һ������ѹ����0.1MPa
				StaticPm=StaticPt+WaterDensity*9.8*Thickness/2.0;
				StaticPb=StaticPt+WaterDensity*9.8*Thickness;
			}
			
			void GetStaticPressure(StrSeg *StrSegTop)
			{   //���ڷǶ������� ,��λ��˹�� ,ֻ��������ʵ�ĵز㣬�����ڰ�ʴ�¼�
				StaticPt=StrSegTop->StaticPb;
				StaticPm=StaticPt+WaterDensity*9.8*Thickness/2.0;
				StaticPb=StaticPt+WaterDensity*9.8*Thickness;
			}
			
			void CalculateWaterDensityAndStaticPressure()
			{ //ͨ����ϼ���ˮ�ܶȺ;�ˮѹ�������������StrSeg�ļ���
				double TempWaterDensity;
				double wc;
				WaterDensity=1040.; //�����������StrSeg������ˮ�ܶ�Ϊͨ���ĵز�ˮ�ܶ�
				do
				{
				GetStaticPressure();
				Pt=StaticPt+Ut;Pm=StaticPm+Um;Pb=StaticPb+Ub;

				//2017/8/8:pressure coefficient
				PCOEt = Pt/StaticPt;
				POCEm = Pm/StaticPm;
				POCEb = Pb/StaticPb;

				TempWaterDensity=WaterDensity;
				GetWaterDensity();
				wc=fabs(WaterDensity-TempWaterDensity);
				}while(wc>0.0001);
			}

			void CalculateWaterDensityAndStaticPressure(StrSeg *StrSegTop)
			{ //ͨ����ϼ���ˮ�ܶȺ;�ˮѹ�������ڳ��������StrSeg�ļ���
				double TempWaterDensity;
				double wc;
				//���ڳ�ʼ�ĵز�ˮ�ܶȣ�������ǵ�һ��StrSeg,���� GetFromNearbyStrSegPart01(StrSeg *StrSegLeft, StrSeg *StrSegTop) ������StrSegLeft�ĵز�ˮ�ܶȴ�������Ϊ��ʼ�ܶ�ֵ��
				do
				{
				GetStaticPressure(StrSegTop);
				Pt=StaticPt+Ut;Pm=StaticPm+Um;Pb=StaticPb+Ub;

				//2017/8/8:pressure coefficient
				PCOEt = Pt/StaticPt;
				POCEm = Pm/StaticPm;
				POCEb = Pb/StaticPb;

				TempWaterDensity=WaterDensity;
				GetWaterDensity();
				wc=fabs(WaterDensity-TempWaterDensity);
				}while(wc>0.0001);
			}
			
			void GetTotalDensity()
			{ //���������StrSeg�ļ���
				GetMatrixDensity();
				CalculateWaterDensityAndStaticPressure(); //�������徲ѹ�� ��ˮ�ܶ�
				TotalDensity=Porom*WaterDensity+(1.-Porom)*TMatrixDensity;
			}
			
			void GetTotalDensity(StrSeg *StrSegTop)
			{  //���ڳ��������StrSeg�ļ���
				GetMatrixDensity();
				CalculateWaterDensityAndStaticPressure(StrSegTop); //�������徲ѹ�� ��ˮ�ܶ�
				TotalDensity=Porom*WaterDensity+(1.-Porom)*TMatrixDensity;
			}
			
			void GetPl()   //��þ���ѹ�� ,��λ��Pa
			{
				Plt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;  //ˮ���澻ˮѹ������һ������ѹ����0.1MPa
				Plm=Plt+TotalDensity*9.8*Thickness/2.0;
				Plb=Plt+TotalDensity*9.8*Thickness;
			}
			
			void GetPl(StrSeg *StrSegTop)  //��þ���ѹ�� ,��λ��Pa
			{   //���ڷǶ�������
				Plt=StrSegTop->Plb;
				Plm=Plt+TotalDensity*9.8*Thickness/2.0;
				Plb=Plt+TotalDensity*9.8*Thickness;
			}
			
			void GetUl()   //��þ������� ,��λ��Pa
			{
				GetTotalDensity(); //�ú����Ѿ������˾�ˮѹ������ȡ����
				GetPl();
				Ult=Plt-StaticPt;
				Ulm=Plm-StaticPm;
				Ulb=Plb-StaticPb;
			}
			
			void GetUl(StrSeg *StrSegTop)  //��þ������� ,��λ��Pa
			{   //���ڷǶ�������
				GetTotalDensity(StrSegTop); //�ú����Ѿ������˾�ˮѹ������ȡ����
				GetPl(StrSegTop);    //��þ���ѹ��
				Ult=Plt-StaticPt;    //��þ������ܣ�����
				Ulm=Plm-StaticPm;    //��þ������ܣ��в�
				Ulb=Plb-StaticPb;    //��þ������ܣ��ײ�
			}
			
			void GetEffectiveStress() //��ЧӦ������
			{ EffectiveStresst=Ult-Ut; EffectiveStressm=Ulm-Um;  EffectiveStressb=Ulb-Ub;  }
			
			void GetPoroFromEffectiveStress()
			{  
				//���ھ�ˮѹ����ȵ�Athy����,���ڳ�ʼ��StrSeg
				GetUl();// //��þ������� ,��λ��Pa
				GetEffectiveStress(); //��ЧӦ������
				MaxEffectiveStresst =EffectiveStresst;   //���ڳ�ʼ��StrSeg����ЧӦ����Ϊ�����ЧӦ��
				MaxEffectiveStressm =EffectiveStressm;
				MaxEffectiveStressb =EffectiveStressb;
				//��GetIfItIsTheTopestStrSegOP01()�������Ѿ���*Porosityt��*Porositym��*Porosityb���˿ռ䲢��ֵ�˳�ֵ
				Porot=0.; Porom=0.; Porob=0.;
				double fFait,fFaiDerivativet,fFaim,fFaiDerivativem,fFaib,fFaiDerivativeb;  //ţ�ٵ������еı���
				for(int i=0;i<LithNumber;i++)
				{
					double wcx=0.0001;
					double tempPorot,tempPorom, tempPorob;
					double ErrorPorot,ErrorPorom , ErrorPorob;
					do
					{  //ͨ��������ÿ�϶��ֵ
						tempPorot=Porosityt[i]; tempPorom=Porositym[i];  tempPorob=Porosityb[i];
						fFait=EffectiveStresst*CompactionFactor[i]/(MatrixDensity[i]-WaterDensity)/9.8+InitialPorosity[i]+log(Porosityt[i]/InitialPorosity[i])-Porosityt[i];
						fFaiDerivativet=1./Porosityt[i]-1.;
						Porosityt[i]=Porosityt[i]-fFait/fFaiDerivativet;
						fFaim=EffectiveStressm*CompactionFactor[i]/(MatrixDensity[i]-WaterDensity)/9.8+InitialPorosity[i]+log(Porositym[i]/InitialPorosity[i])-Porositym[i];
						fFaiDerivativem=1./Porositym[i]-1.;
						Porositym[i]=Porositym[i]-fFaim/fFaiDerivativem;
						fFaib=EffectiveStressb*CompactionFactor[i]/(MatrixDensity[i]-WaterDensity)/9.8+InitialPorosity[i]+log(Porosityb[i]/InitialPorosity[i])-Porosityb[i];
						fFaiDerivativeb=1./Porosityb[i]-1.;
						Porosityb[i]=Porosityb[i]-fFaib/fFaiDerivativeb;
						ErrorPorot=fabs(tempPorot-Porosityt[i]);
						ErrorPorom=fabs(tempPorom-Porositym[i]);
						ErrorPorob=fabs(tempPorob-Porosityb[i]);
						if(Porosityt[i]<=0.||Porosityt[i]>InitialPorosity[i]) Porosityt[i]= GetRand(0., InitialPorosity[i]);   //�����������Ŀ�϶�ȳ�������ķ�Χֵ�������������϶�ȳ�ʼֵ������һ�ε���
						if(Porositym[i]<=0.||Porositym[i]>InitialPorosity[i]) Porositym[i]= GetRand(0., InitialPorosity[i]);
						if(Porosityb[i]<=0.||Porosityb[i]>InitialPorosity[i]) Porosityb[i]= GetRand(0., InitialPorosity[i]);
					}while(ErrorPorot>wcx||ErrorPorom>wcx||ErrorPorob>wcx);
					Porot+=Porosityt[i]*LithRatio[i];
					Porom+=Porositym[i]*LithRatio[i];
					Porob+=Porosityb[i]*LithRatio[i];
				}
			}
			
			void GetPoroFromEffectiveStress(StrSeg *StrSegLeft,StrSeg *StrSegTop)
			{   
				//���ھ�ˮѹ����ȵ�Athy����,���ڷǳ�ʼ��StrSeg
				GetUl(StrSegTop);// //��þ������� ,��λ��MPa
				GetEffectiveStress(); //��ЧӦ������
				for(int i=0;i<LithNumber;i++)
				{
					Porosityt[i]=StrSegLeft->Porosityt[i]; //���ϸ�ʱ��εĿ�϶��ֵ��ֵ����ʱ�����Ϊ�����ĳ�ʼֵ
					Porositym[i]=StrSegLeft->Porositym[i];
					Porosityb[i]=StrSegLeft->Porosityb[i];
				}
				double fFait,fFaiDerivativet,fFaim,fFaiDerivativem,fFaib,fFaiDerivativeb;  //ţ�ٵ������еı���
				if(EffectiveStresst>StrSegLeft->MaxEffectiveStresst)
				{
					MaxEffectiveStresst =EffectiveStresst;
					MaxEffectiveStressm =EffectiveStressm;
					MaxEffectiveStressb =EffectiveStressb;
					Porot=0.; Porom=0.; Porob=0.;
					for(int i=0;i<LithNumber;i++)
					{
						double wcx=0.0001;
						double tempPorot,tempPorom, tempPorob;
						double ErrorPorot,ErrorPorom , ErrorPorob;
						do
						{  //ͨ��������ÿ�϶��ֵ
							tempPorot=Porosityt[i]; tempPorom=Porositym[i];  tempPorob=Porosityb[i];
							fFait=EffectiveStresst*CompactionFactor[i]/(MatrixDensity[i]-WaterDensity)/9.8+InitialPorosity[i]+log(Porosityt[i]/InitialPorosity[i])-Porosityt[i];
							fFaiDerivativet=1./Porosityt[i]-1.;
							Porosityt[i]=Porosityt[i]-fFait/fFaiDerivativet;
							fFaim=EffectiveStressm*CompactionFactor[i]/(MatrixDensity[i]-WaterDensity)/9.8+InitialPorosity[i]+log(Porositym[i]/InitialPorosity[i])-Porositym[i];
							fFaiDerivativem=1./Porositym[i]-1.;
							Porositym[i]=Porositym[i]-fFaim/fFaiDerivativem;
							fFaib=EffectiveStressb*CompactionFactor[i]/(MatrixDensity[i]-WaterDensity)/9.8+InitialPorosity[i]+log(Porosityb[i]/InitialPorosity[i])-Porosityb[i];
							fFaiDerivativeb=1./Porosityb[i]-1.;
							Porosityb[i]=Porosityb[i]-fFaib/fFaiDerivativeb;
							ErrorPorot=fabs(tempPorot-Porosityt[i]);
							ErrorPorom=fabs(tempPorom-Porositym[i]);
							ErrorPorob=fabs(tempPorob-Porosityb[i]);
							if(Porosityt[i]<=0.||Porosityt[i]>InitialPorosity[i]) Porosityt[i]= GetRand(0., InitialPorosity[i]);  //�����������Ŀ�϶�ȳ�������ķ�Χֵ�������������϶�ȳ�ʼֵ������һ�ε���
							if(Porositym[i]<=0.||Porositym[i]>InitialPorosity[i]) Porositym[i]= GetRand(0., InitialPorosity[i]);
							if(Porosityb[i]<=0.||Porosityb[i]>InitialPorosity[i]) Porosityb[i]= GetRand(0., InitialPorosity[i]);
						}while(ErrorPorot>wcx||ErrorPorom>wcx||ErrorPorob>wcx);
						Porot+=Porosityt[i]*LithRatio[i];
						Porom+=Porositym[i]*LithRatio[i];
						Porob+=Porosityb[i]*LithRatio[i];
					}
				}
				else
				{ //�����ЧӦ��С�ڵ��������ЧӦ������϶�ȱ��ֲ��䣻��������Կ�϶���Ѿ������渳ֵ�ˡ�
					MaxEffectiveStresst=StrSegLeft->MaxEffectiveStresst;
					MaxEffectiveStressm=StrSegLeft->MaxEffectiveStressm;
					MaxEffectiveStressb=StrSegLeft->MaxEffectiveStressb;
					Porot=StrSegLeft->Porot;
					Porom=StrSegLeft->Porom;
					Porob=StrSegLeft->Porob;
				}
			}
			
			void GetCOC() //���ѹ��ϵ��
			{
				COC=TCompactionFactor/(TMatrixDensity-WaterDensity)/9.8*Porom/(1.-Porom);
			}
			
			void GetParaOfOverpressureEquation()
			{  //��ó�ѹ���̵��������� ,���ڵ�һ��StrSeg
				GetPoroFromEffectiveStress();
				GetThickness();
				GetDepths();
				GetCOC();
				GetPermeability();
				GetWaterViscosity();
				aOverpressure=COC*WaterDensity/(1.-Porom);
				bOverpressure=WaterDensity*Perm/WaterViscosity;                                                                                       
				cOverpressure=COC*WaterDensity/(1.-Porom)*(Ulm-0.)/(DeltaAge*Ma2Second)-Porom*(WaterDensity-WaterDensity)/(DeltaAge*Ma2Second);  // ��������ͬ��ˮ�ܶ�ֻ���Ǵ�������׸�StrSeg,��һʱ����������һʱ��ˮ�ܶ���ͬ ���������һʱ�侲������Ϊ0
			}

			void GetParaOfOverpressureEquation(StrSeg *StrSegLeft,StrSeg *StrSegTop)
			{  //��ó�ѹ���̵��������� ,���ڷǵ�һ��StrSeg
				GetPoroFromEffectiveStress(StrSegLeft,StrSegTop);
				GetThickness();
				GetDepths(StrSegLeft, StrSegTop);
				GetCOC();
				GetPermeability();
				GetWaterViscosity();
				aOverpressure=COC*WaterDensity/(1.-Porom);
				bOverpressure=WaterDensity*Perm/WaterViscosity;
				cOverpressure=COC*WaterDensity/(1.-Porom)*(Ulm-StrSegLeft->Ulm)/(DeltaAge*Ma2Second)-Porom*(WaterDensity-StrSegLeft->WaterDensity)/(DeltaAge*Ma2Second);    //*1e6   *1e6
			}
			
			void GetStaticPAndPlOfTheFirstStrSeg()
			{  //��ð�ʴ�¼��������ϵĵ�һ��StrSeg�ľ�ˮѹ���;���ѹ��
				StaticPt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;
				StaticPb=StaticPt;
				Plt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;  //ˮ���澻ˮѹ������һ������ѹ����0.1MPa
				Plb=Plt;
			}
			
			void GetThickness()
			{
				Thickness=MatrixThickness/(1.-Porom);
			}
			
			void GetDepths() //���������ֵ
			{    //���ڵ�һ��StrSeg
					BuryBottomDepth=BuryTopDepth+Thickness;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����,�ӳ�����������
					MiddleDepth=TopDepth+0.5*Thickness;//�ܵ�����в���ȣ���ˮ������
					BottomDepth=TopDepth+Thickness;//�������
					MaxBuryTopDepth=BuryTopDepth;   //����ֻ�Ǽ�¼�������ڳ�ѹ������ʵ���ϲ�û��Ӧ��
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
			}
			
			void GetDepths(StrSeg *StrSegLeft,StrSeg *StrSegTop) //���������ֵ
			{     //���ڷǵ�һ��StrSeg
					BuryTopDepth=StrSegTop->BuryBottomDepth;  //�����ڳ�ѹ��������ѭ���������̣����һֱ�ڱ仯����˵õ���ÿ��StrSeg�����Ҳ�ڱ仯�����ÿ�μ������ʱ��Ҫ�ȵõ��仯�Ŀռ��ϵ���һStrSeg�ģ��ײ������ֵ
					TopDepth=StrSegTop->BottomDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����,�ӳ�����������
					BuryBottomDepth=BuryTopDepth+Thickness;
					MiddleDepth=TopDepth+0.5*Thickness;//�ܵ�����в���ȣ���ˮ������
					BottomDepth=TopDepth+Thickness;//�������
					if((Property==1||(Property==2&&!Eroded))&&BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
					{   //��������������ǰһʱ�̸�StrSeg�������������������������ֻ�Ǽ�¼�������ڳ�ѹ������ʵ���ϲ�û��Ӧ��
						MaxBuryTopDepth=BuryTopDepth;
						MaxBuryMiddleDepth=BuryMiddleDepth;
						MaxBuryBottomDepth=BuryBottomDepth;
					}
					else
					{
						MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;    //�������ֲ���
						MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
						MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
					}
			}
			
			
			void RealThicknessCalculating()
			{ // ͨ��ѭ����������ȶ��ĺ�ȣ����ھ�ˮѹ�����Լ���̬���¶ȼ��㣻����Ե�һ��StrSeg����[0][0][0]
				double tempPoro=Porom;
				double wc;
				do{
				GetT();
				GetPoroFromEffectiveStress();
				GetThickness();
				GetDepths();
				GetTotalHeatCapacity();
				GetQr();
				wc=fabs(tempPoro-Porom);
				tempPoro=Porom;
				}while(wc>0.0001);
				GetPermeability();
			}

			void GetIfItIsTheTopestStrSegOP01()
			{  // ���ڴ���ѹģ�ͣ�����˲̬����ģ��
				TopDepth=PaleoWaterDepth;   //���StrSeg�������Ϊ��ˮ��
				BuryTopDepth=0.;   //���StrSeg��������Ϊ0
				if(Property==1||Property==2)
				{  //�����������StrSeg���ù���
				Tt=SurfaceT; //,���ڵ�һ��StrSeg, �ڵ�һ���ָ��������¶�
				Tm =SurfaceT;//���Ƚ��ر��¶ȸ�ֵ���ز���в��¶�
				Tb=SurfaceT;
				Ut=0.; Um=0.;Ub=0.; //���ڵ�һ��StrSeg���������в��͵ײ��ĳ�ѹ����Ϊ0
				Porosityt=new double[LithNumber];
				Porositym=new double[LithNumber];
				Porosityb=new double[LithNumber];
				//�����ǵ�һ��StrSeg����˿��Բ��õ�Ч��ˮѹ����Ƚ��к�ȺͿ�϶�ȵļ�����Ϊ��������ĳ�ʼֵ
				GetBuryBottomDepth();
				Thickness=BuryBottomDepth-BuryTopDepth;
				BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����
				MiddleDepth=TopDepth+0.5*Thickness;//�ܵ��в���ȣ���ˮ������
				BottomDepth=TopDepth+Thickness; //�ײ����
				MaxBuryTopDepth=BuryTopDepth;
				MaxBuryMiddleDepth=BuryMiddleDepth;
				MaxBuryBottomDepth=BuryBottomDepth;
				GetPorosity();
				}
				if(Property==3)
				{ //��ʴ�¼����StrSeg���ù��̣���ʴ�¼�Ҳ����ع��̴���
					//�����ڳ�ѹģ������У���㣨�����Ҳһ������StrSeg�ĺ���Ǳ仯�ģ���˶�Ӧ�İ�ʴ�¼���StrSeg�ĺ�ȾͲ����ú㶨��ֵCurrentThickness�ˣ�
					//����Ҫ�ڵ�һ������һ����ʴ�¼���StrSegʱ��Ѱ�Ҷ�Ӧ����StrSeg���������StrSeg�ĺ��Thickness��ֵ����һ��ʴ�¼�StrSeg�ĺ�ȣ���ȻҪ��ɸ�ֵ�ˣ�������Ҫ������������Ͳ������︳ֵ�ˡ�
				BottomDepth=TopDepth+Thickness;//�������
				BuryBottomDepth=BuryTopDepth+Thickness;//���������� ����˵���������Ǹ�ֵ
				GetStaticPAndPlOfTheFirstStrSeg();  //��ð�ʴ�¼��ĵ�һ��StrSeg�ľ�ˮѹ���;���ѹ��
				Tt=SurfaceT;
				Tb=Tt; //��ʴ�¼�StrSeg���¶���͸����
				}
				if(Property==4)
				{ //��������¼����StrSeg���ù��̣�����¼�Ҳ����ع��̴���
				Thickness=CurrentThickness;  //��CurrentThickness��ֵ��Thickness����Ȼ���ڼ���¼���������0
				BottomDepth=TopDepth+Thickness;//�������
				BuryBottomDepth=BuryTopDepth+Thickness;//���������� ����˵����������0
				GetStaticPAndPlOfTheFirstStrSeg(); //��ó�����ϵĵ�һ��StrSeg�ľ�ˮѹ���;���ѹ��
				Tt=SurfaceT;
				Tb=Tt; //����¼�StrSeg���¶���͸����
				}
			}
			
			void GetFromNearbyStrSegOP01(StrSeg *StrSegLeft, StrSeg *StrSegTop) //ͨ����ࣨ��ʱ���ϵ���һ�������ϲ������ռ��ϵģ�StrSeg�����Ϣ
			{ //�˺���Ӧ���ڷǳ�ʼStrSeg�������ڸ��ֵز�����Ե���� ;   // ���ڴ���ѹ�Լ�˲̬����ģ��
				aPetroGenStyle=StrSegLeft->aPetroGenStyle; ///new added 2017-11-22
				BeginAge=StrSegTop->BeginAge ;   //�����θ�ʱ��ֵ
				EndAge=StrSegTop->EndAge ;
				MiddleAge=StrSegTop->MiddleAge ;
				DeltaAge=StrSegTop->DeltaAge ;
				TopDepth=StrSegTop->BottomDepth;  //���������Զ�����ϲ�StrSeg�ĵײ����
				BuryTopDepth=StrSegTop->BuryBottomDepth;  //���������Զ�����ϲ�StrSeg�ĵײ����
				PaleoWaterDepth=StrSegTop->PaleoWaterDepth; //��ˮ����ڶ����ز�εĹ�ˮ�� ������ʵ�ù�ˮ���ڷǵ�һ��StrSeg�Ͽ���һֱû���õ�
				HF=StrSegTop->HF; //�������ڶ����ز�ε�����
				SurfaceT=StrSegTop->SurfaceT; //�����¶��������StrSeg�ı����¶ȴ���
				MatrixThickness=StrSegLeft->MatrixThickness;//����һ��ʱ���(�����)��StrSeg��ùǼܺ��
				EndPorom=StrSegLeft->EndPorom;
				SourceRock=StrSegLeft->SourceRock ;   //����һ��ʱ��ε�StrSeg����Ƿ�ΪԴ�ҵ���Ϣ
				if(SourceRock) TOC=StrSegLeft->TOC ;     //����һ��ʱ��ε�StrSeg��ò����л�̼����
				Tt=StrSegLeft->Tt; //����һʱ��StrSeg�Ķ����¶ȸ�ֵ������StrSeg�Ķ����¶�
				Tm =StrSegLeft->Tm;//����һʱ��StrSeg���в��¶ȸ�ֵ������StrSeg���в��¶�
				Tb =StrSegLeft->Tb;//����һʱ��StrSeg�ĵײ��¶ȸ�ֵ������StrSeg�ĵײ��¶�
				Ut=StrSegLeft->Ut; Um=StrSegLeft->Um;Ub=StrSegLeft->Ub; //����һʱ��εĳ�ѹֵ��ֵ����ʱ���
				WaterDensity=StrSegLeft->WaterDensity; //����һʱ��ε�ˮ�ܶȴ�����ʱ��ε�StrSeg����Ϊ���㾲ˮѹ������ʼ����
				//���ݲ�ͬ��StrSeg���ʽ��в�ͬ���жϺͲ���
				if(Property==1)
				{   //�ǵز�����
				Porosityt=new double[LithNumber];
				Porositym=new double[LithNumber];
				Porosityb=new double[LithNumber];
				for(int i=0;i<LithNumber;i++)//����һʱ�̿�϶��ֵ��ֵ����ʱ�̵Ŀ�϶�ȣ���Ϊ�����ĳ�ʼ��϶��ֵ
					{
					Porosityt[i]=StrSegLeft->Porosityt[i];
					Porositym[i]=StrSegLeft->Porositym[i];
					Porosityb[i]=StrSegLeft->Porosityb[i];
					}
				Thickness=StrSegLeft->Thickness ;//����һ��ʱ��ε�StrSeg��ȸ�ֵ����ʱ�̸�StrSeg�ĺ�ȡ���Ϊ���������ʼֵ��
				Porot=StrSegLeft->Porot;
				Porom=StrSegLeft->Porom;
				Porob=StrSegLeft->Porob;
				GetDepths(StrSegLeft,StrSegTop);  // ��Ȼ�ú���������Ӧ���ˣ������ں���ļ���ûӰ�죬��Ϊ���һ�ˮѹ���ļ��㶼�ǻ���ÿ��StrSeg���ۻ�
				}
				if(Property==2)
				{ //���������� ----��ʼ
				if(!StrSegLeft->Eroded) //���û����ʴ�����Ͱ������ĵز㴦��
					{ //*********************************************
					Porosityt=new double[LithNumber];
					Porositym=new double[LithNumber];
					Porosityb=new double[LithNumber];
					for(int i=0;i<LithNumber;i++)//����һʱ�̿�϶��ֵ��ֵ����ʱ�̵Ŀ�϶�ȣ���Ϊ�����ĳ�ʼ��϶��ֵ
					{
						Porosityt[i]=StrSegLeft->Porosityt[i];
						Porositym[i]=StrSegLeft->Porositym[i];
						Porosityb[i]=StrSegLeft->Porosityb[i];
					}
					Thickness=StrSegLeft->Thickness ;//����һ��ʱ��ε�StrSeg��ȸ�ֵ����ʱ�̸�StrSeg�ĺ�ȡ�
					Porot=StrSegLeft->Porot;
					Porom=StrSegLeft->Porom;    //����һʱ���StrSeg�Ŀ�϶�ȴ�����һʱ��Σ���ΪһЩ��������ĳ�ʼֵ
					Porob=StrSegLeft->Porob;
					GetDepths(StrSegLeft,StrSegTop);  
					if(BuryBottomDepth<MarginOfErrorThickness)  //����һ��������ݴ�ֵ������Ϊ 1cm
						{ // ����ײ����С��һ��������ݴ�ֵ�������õز���Ѿ�����ʴ��
						Eroded=true; //���ײ��������0ʱ��˵���Ѿ�����ʴ����Eroded������Ϊtrue
						StaticPt=StrSegTop->StaticPb; //���ϲ���StrSeg�ײ��ľ�ˮѹ����ֵ����StrSeg�����ľ�ˮѹ��
						StaticPb=StaticPt;     //��ʴ�����¼���StrSeg�Ծ�ˮѹ��͸�����𴫵�����
						Plt=StrSegTop->Plb;  //���ϲ���StrSeg�ײ��ľ���ѹ����ֵ����StrSeg��������ѹ��
						Plb=Plt;
						}
					} //*********************************************
				if(StrSegLeft->Eroded)
					{  //����Ѿ�����ʴ�ˣ��ټ���ʱ��ȱ��ֲ��䣬���ʴStrSeg����������---���������ã���ȣ�֮��Ϊ0
					Eroded=true;
					Thickness=StrSegLeft->Thickness;
					Porosityt=new double[LithNumber];
					Porositym=new double[LithNumber];
					Porosityb=new double[LithNumber];
					for(int i=0;i<LithNumber;i++)//����һʱ�̿�϶��ֵ��ֵ����ʱ�̵Ŀ�϶�ȣ���Ϊ�����ĳ�ʼ��϶��ֵ
					{
						Porosityt[i]=StrSegLeft->Porosityt[i];
						Porositym[i]=StrSegLeft->Porositym[i];
						Porosityb[i]=StrSegLeft->Porosityb[i];
					}
					Porot=StrSegLeft->Porot;  //�������в��͵ײ���϶��ֻ������������������ʾ����ͼʱ�����ڰ�ʴ���ʱ�����һֱ����ֵ
					Porom=StrSegLeft->Porom;  //���Ŀ�϶��ֵ��������ѭ��������MatrixThicknessʱ������
					Porob=StrSegLeft->Porob;
					GetDepths(StrSegLeft,StrSegTop);
					StaticPt=StrSegTop->StaticPb; //���ϲ���StrSeg�ײ��ľ�ˮѹ����ֵ����StrSeg�����ľ�ˮѹ��
					StaticPb=StaticPt;     //�Ѿ���ʴ������StrSeg�Ծ�ˮѹ��͸�����𴫵�����
					Plt=StrSegTop->Plb;  //���ϲ���StrSeg�ײ��ľ���ѹ����ֵ����StrSeg��������ѹ��
					Plb=Plt;             //�Ѿ���ʴ������StrSeg�Ծ���ѹ��͸�����𴫵�����
					}
				}  //���������� ----����
				if(Property==3)
				{  
					Thickness=StrSegLeft->Thickness; //��������İ�ʴ�¼���StrSeg���ǳ�ʼʱ�̳��֣��ں�����ʱ��������ȱ��ֲ��䣬��˺��Thickness�����︳ֵ
					BottomDepth=TopDepth+Thickness;//�������
					BuryBottomDepth=BuryTopDepth+Thickness;//����������
					StaticPt=StrSegTop->StaticPb; //���ϲ���StrSeg�ײ��ľ�ˮѹ����ֵ����StrSeg�����ľ�ˮѹ��
					StaticPb=StaticPt;     //��ʴ�����¼���StrSeg�Ծ�ˮѹ��͸�����𴫵�����
					Plt=StrSegTop->Plb;  //���ϲ���StrSeg�ײ��ľ���ѹ����ֵ����StrSeg��������ѹ��
					Plb=Plt;
				}
				if(Property==4)
				{ //����Ǽ���¼����ԣ�ֻ�к�Ⱥ͵ײ���Ȳ����������õ�
					Thickness=StrSegLeft->Thickness;   //���ڲ��ǵ�һ��StrSeg������¼��ĺ��ֻ�轫ǰһʱ��ε�Thickness�������Ϳ�����
					BottomDepth=TopDepth+Thickness;//�������
					BuryBottomDepth=BuryTopDepth+Thickness;//����������
					StaticPt=StrSegTop->StaticPb; //���ϲ���StrSeg�ײ��ľ�ˮѹ����ֵ����StrSeg�����ľ�ˮѹ��
					StaticPb=StaticPt;     //��ʴ�����¼���StrSeg�Ծ�ˮѹ��͸�����𴫵�����
					Plt=StrSegTop->Plb;  //���ϲ���StrSeg�ײ��ľ���ѹ����ֵ����StrSeg��������ѹ��
					Plb=Plt;
				}
			}     
			
			void GetIfItIsTheTopestStrSegPart01()
			{  // ���ڴ���˲̬����ģ��
				TopDepth=PaleoWaterDepth;   //���StrSeg�������Ϊ��ˮ��
				BuryTopDepth=0.;   //���StrSeg��������Ϊ0
				if(Property==1||Property==2)
				{  ////�����������StrSeg���ù���
				GetBuryBottomDepth();  //  ͨ���ú��������صײ����
				Thickness=BuryBottomDepth-BuryTopDepth;
				BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����
				MiddleDepth=TopDepth+0.5*Thickness;  //�ܵ��в���ȣ���ˮ������
				BottomDepth=TopDepth+Thickness;  //�ܵĵײ���ȣ���ˮ������
				MaxBuryTopDepth=BuryTopDepth;      //
				MaxBuryMiddleDepth=BuryMiddleDepth;
				MaxBuryBottomDepth=BuryBottomDepth;
				GetPorosity();
				GetPermeability();
				Tt=SurfaceT; //,���ڵ�һ��StrSeg, �ڵ�һ���ָ��������¶�
				Tm =SurfaceT;//���Ƚ��ر��¶ȸ�ֵ���ز���в��¶�
				Tb=SurfaceT;
				}
				if(Property==3||Property==4)
				{ //��ʴ���������¼����StrSeg���ù��̣���ʴ�����¼�Ҳ����ع��̴���
				Thickness=CurrentThickness;  //��CurrentThickness��ֵ��Thickness������ĺ�ȶ��Ǹ�����0
				BottomDepth=TopDepth+Thickness;//�������
				BuryBottomDepth=BuryTopDepth+Thickness;//���������� ����˵���������Ǹ�ֵ��0
				Tt=SurfaceT;
				Tb=Tt; //��ʴ�����¼�StrSeg���¶���͸����
				}
			}
			
			void GetIfItIsTheTopestStrSegPart02()
			{ // ���ڴ���˲̬����ģ�� ��Ҳ���ڳ�ѹģ�͵ĺ�벿�ּ���
				if(Property==1||Property==2)
				{  ////�����������StrSeg���ù���
				Tmax=Tm; //���ز���в����¶ȸ�ֵ��Tmax
				GetTTI(); //��õ�һ���ز�ε�TTI

				GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
				GetRoFromEasyRo(); //���EasyRo�����õ���Roֵ   ������������ɾ��
				GetRoFromBasinRo(); //���BasinRo�����õ���Roֵ
				GetRoFromSimpleRo(); //���SimpleRo�����õ���Roֵ  ������������ɾ��
				
				if(SourceRock)
					{
					GetHCGIPerUnitInitTOC(); //�����Դ�ң�����㵥λ����(kg)ԭʼ�л�̼�Ľ����� ��������-Ro����
					GetInitTOC();  //���ԭʼ�л�̼����������      ��������-Ro����
					GainHCGIPerUnitInitTOC();  //LLNL ��ѧ��Ӧ����ѧ���㷽��
					GainInitTOC(); //���ԭʼ�л�̼���������� ����ѧ����ѧ����
					// GetEEFromRo();  //����Ro�������Ч��
					// FlashCalculation();  
					//  GetTRFromDR();  // //������Խ����ʷ���������ת����
					// GetEEFromTR();  //ͨ��TR�������Ч�ʺ�����Ч��
					}
				}
			}
			
			void GetIfItIsTheTopestStrSeg()
			{  //�����StrSeg������ ���������̺Ͱ�ʴ����һ����������StrSeg����Property�ж� ����̬�ȴ���ģ��
				TopDepth=PaleoWaterDepth;   //���StrSeg�������Ϊ��ˮ��
				BuryTopDepth=0.;   //���StrSeg��������Ϊ0
				if(Property==1||Property==2)
				{  ////�����������StrSeg���ù���
					GetMatrixDensity();//2017/10/13: new added method
					GetBuryBottomDepth();
					Thickness=BuryBottomDepth-BuryTopDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����
					MiddleDepth=TopDepth+0.5*Thickness;//�ܵ��в���ȣ���ˮ������
					BottomDepth=TopDepth+Thickness; //�ײ����
					MaxBuryTopDepth=BuryTopDepth;      //
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
					GetPorosity();
					GetT(); //������̬�ȴ�������¶�
					Tmax=Tm; //���ز���в����¶ȸ�ֵ��Tmax
					GetTTI(); //��õ�һ���ز�ε�TTI

					GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
					GetRoFromEasyRo(); //���EasyRo�����õ���Roֵ   ������������ɾ��
					GetRoFromBasinRo(); //���BasinRo�����õ���Roֵ
					GetRoFromSimpleRo(); //���SimpleRo�����õ���Roֵ  ������������ɾ��

					//2017/7/18: add density
					GetMatrixDensity();

					if(SourceRock)
					{
						GetHCGIPerUnitInitTOC(); //�����Դ�ң�����㵥λ����(kg)ԭʼ�л�̼�Ľ����� ��������-Ro����
						GetInitTOC();  //���ԭʼ�л�̼����������      ��������-Ro����
						GainHCGIPerUnitInitTOC();  //LLNL ��ѧ��Ӧ����ѧ���㷽��
						GainInitTOC(); //���ԭʼ�л�̼���������� ����ѧ����ѧ����
					}
				}
				if(Property==3||Property==4)
				{ //��ʴ���������¼����StrSeg���ù��̣���ʴ�����¼�Ҳ����ع��̴���
				Thickness=CurrentThickness;  //��CurrentThickness��ֵ��Thickness������ĺ�ȶ��Ǹ�����0
				BottomDepth=TopDepth+Thickness;//�������
				BuryBottomDepth=BuryTopDepth+Thickness;//���������� ����˵���������Ǹ�ֵ��0
				Tt=SurfaceT;
				Tb=Tt; //��ʴ�����¼�StrSeg���¶���͸����
				}
			}
			
			void GetFromNearbyStrSegPart01(StrSeg *StrSegLeft, StrSeg *StrSegTop) //ͨ����ࣨ��ʱ���ϵ���һ�������ϲ������ռ��ϵģ�StrSeg�����Ϣ
			{ //�˺���Ӧ���ڷǳ�ʼStrSeg�������ڸ��ֵز�����Ե���� ;   // ���ڴ���˲̬����ģ��
				aPetroGenStyle=StrSegLeft->aPetroGenStyle; ///new added 2017-11-22
				BeginAge=StrSegTop->BeginAge ;   //�����θ�ʱ��ֵ
				EndAge=StrSegTop->EndAge ;
				MiddleAge=StrSegTop->MiddleAge ;
				DeltaAge=StrSegTop->DeltaAge ;
				TopDepth=StrSegTop->BottomDepth;  //���������Զ�����ϲ�StrSeg�ĵײ����
				BuryTopDepth=StrSegTop->BuryBottomDepth;  //���������Զ�����ϲ�StrSeg�ĵײ����
				PaleoWaterDepth=StrSegTop->PaleoWaterDepth; //��ˮ����ڶ����ز�εĹ�ˮ�� ������ʵ�ù�ˮ���ڷǵ�һ��StrSeg�Ͽ���һֱû���õ�
				HF=StrSegTop->HF; //�������ڶ����ز�ε�����
				SurfaceT=StrSegTop->SurfaceT; //�����¶��������StrSeg�ı����¶ȴ���
				MatrixThickness=StrSegLeft->MatrixThickness;//����һ��ʱ���(�����)��StrSeg��ùǼܺ��
				SourceRock=StrSegLeft->SourceRock ;   //����һ��ʱ��ε�StrSeg����Ƿ�ΪԴ�ҵ���Ϣ
				if(SourceRock) TOC=StrSegLeft->TOC ;     //����һ��ʱ��ε�StrSeg��ò����л�̼����
				Tt=StrSegLeft->Tt; //����һʱ��StrSeg�Ķ����¶ȸ�ֵ������StrSeg�Ķ����¶�
				Tm =StrSegLeft->Tm;//����һʱ��StrSeg���в��¶ȸ�ֵ������StrSeg���в��¶�
				Tb =StrSegLeft->Tb;//����һʱ��StrSeg�ĵײ��¶ȸ�ֵ������StrSeg�ĵײ��¶�
				StaticPt=StrSegLeft->StaticPt;  //����һʱ��εľ�ˮѹ��������ʱ��ε�StrSeg����Ϊ����ˮ�ܶȵ���ʼ����  ,
				StaticPm=StrSegLeft->StaticPm;
				StaticPb=StrSegLeft->StaticPb;
				Pt=StrSegLeft->Pt;  //����һʱ��ε�ˮѹ��������ʱ��ε�StrSeg����Ϊ����ˮ�ܶȵ���ʼ���� ,��û���쳣ѹ�����ڵ�����£���Ϊˮѹ�����ھ�ˮѹ��
				Pm=StrSegLeft->Pm;
				Pb=StrSegLeft->Pb;
				WaterDensity=StrSegLeft->WaterDensity; //����һʱ��ε�ˮ�ܶȴ�����ʱ��ε�StrSeg����Ϊ���㾲ˮѹ������ʼ����
				//���ݲ�ͬ��StrSeg���ʽ��в�ͬ���жϺͲ���
				//====================================
				if(Property==1)
				{   //�ǵز�����
				if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
				{   //�ж϶���������������������ѹʵ����
					GetBuryBottomDepth();  //
					Thickness=BuryBottomDepth-BuryTopDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����,�ӳ�����������
					MiddleDepth=TopDepth+0.5*Thickness;//�ܵ�����в���ȣ���ˮ������
					BottomDepth=TopDepth+Thickness;//�������
					MaxBuryTopDepth=BuryTopDepth;      //  �����������
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
					GetPorosity();      //��ÿ�϶��
				}
				else
				{ //���������С�ڵ�����󶥲�����ʱ����Ȳ��䣬��������
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//�������
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//�в����
					BottomDepth=TopDepth+Thickness;//�������
					MiddleDepth=TopDepth+0.5*Thickness;//�в����
					MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;    //�������ֲ���
					MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
					MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
					Porom=StrSegLeft->Porom;  //��϶�ȱ��ֲ���

					//2019/1/24: add top,bottom value
					Porot=StrSegLeft->Porot;  //��϶�ȱ��ֲ���,t
					Porob=StrSegLeft->Porob;  //��϶�ȱ��ֲ���,b
				}
				}
				if(Property==2)
				{ //���������� ----��ʼ
				if(!StrSegLeft->Eroded) //���û����ʴ�����Ͱ������ĵز㴦��
					{ //*********************************************
					if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
					{  //��������ȴ�����������ȣ�˵�����ڳ������̣���ѹʵ���̴���
						GetBuryBottomDepth();  //
						Thickness=BuryBottomDepth-BuryTopDepth;
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����,�ӳ�����������
						MiddleDepth=TopDepth+0.5*Thickness;//�ܵ�����в���ȣ���ˮ������
						BottomDepth=TopDepth+Thickness;//�������
						MaxBuryTopDepth=BuryTopDepth;      //  �����������
						MaxBuryMiddleDepth=BuryMiddleDepth;
						MaxBuryBottomDepth=BuryBottomDepth;
						GetPorosity();      //��ÿ�϶��
						GetPermeability();
					}
					else
					{ //���������С�ڵ�����󶥲�����ʱ����Ȳ��䣬��������
						//��ʱ�����������״̬����һ�ǻ�û����ʴ��������Ѿ�����ʴ�������ǲ��ְ�ʴ
						// ��������if()֮�ϵĲ��ִ�����ǻ�û��ʴ�������ͬʱ��ȫ���Ͳ��ְ�ʴҲ������
						Thickness=StrSegLeft->Thickness;
						BuryBottomDepth=BuryTopDepth+Thickness;//����������
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//�в�������
						BottomDepth=TopDepth+Thickness;//�������
						MiddleDepth=TopDepth+0.5*Thickness;//�в����
						MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;
						MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
						MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
						Porom=StrSegLeft->Porom;

						//2019/1/24: add top,bottom value
						Porot=StrSegLeft->Porot;  //��϶�ȱ��ֲ���,t
						Porob=StrSegLeft->Porob;  //��϶�ȱ��ֲ���,b

						if(BuryBottomDepth<MarginOfErrorThickness)  //����һ��������ݴ�ֵ������Ϊ 1cm
						{ // ����ײ���ȵ���0�ˣ������õز���Ѿ�����ʴ��
						Eroded=true; //���ײ��������0ʱ��˵���Ѿ�����ʴ����Eroded������Ϊtrue
						}
					}
					} //*********************************************
				if(StrSegLeft->Eroded)
					{  //����Ѿ�����ʴ�ˣ��ټ���ʱ��ȱ��ֲ��䣬���ʴStrSeg����������---���������ã���ȣ�֮��Ϊ0
					Eroded=true;
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//��ص������
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����
					BottomDepth=TopDepth+Thickness;//�������
					MiddleDepth=TopDepth+0.5*Thickness;//�в����
					Porom=StrSegLeft->Porom;   //����ʴ���Ա���ԭ�ȵĿ�϶�ȣ���Ҫ�������������㡪�����ڼ����л�̼ ��ԭʼ�л�̼��
					}
				}  //���������� ----����
				if(Property==3||Property==4)
				{ //����ǰ�ʴ�����¼����ԣ�ֻ�к�Ⱥ͵ײ���Ȳ����������õ�
					Thickness=StrSegLeft->Thickness;
					BottomDepth=TopDepth+Thickness;//�������
					BuryBottomDepth=BuryTopDepth+Thickness;//�������
				}
			}
			
			void GetFromNearbyStrSegPart02(StrSeg *StrSegLeft, StrSeg *StrSegTop) //ͨ����ࣨ��ʱ���ϵ���һ�������ϲ������ռ��ϵģ�StrSeg�����Ϣ
			{ //�˺���Ӧ���ڷǳ�ʼStrSeg�������ڸ��ֵز�����Ե���� ;   // ���ڴ���˲̬����ģ�� ,Ҳ���ڳ�ѹģ��
				if(Property==1)
				{   //�ǵز�����---��ʼ
					//  FlashCalculation(StrSegLeft);  //��ʱֻ�����������ɵ�Դ�ҽ��м���
					GetTmax(StrSegLeft); //������ڻ�֮ǰ������¶�
					GetTTI(StrSegLeft);//���TTIֵ

					GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
					GetRoFromEasyRo(StrSegLeft); //���EasyRo�����õ���Roֵ  ������������ɾ��
					GetRoFromBasinRo(StrSegLeft); //���BasinRo�����õ���Roֵ
					GetRoFromSimpleRo(StrSegLeft); //���SimpleRo�����õ���Roֵ ������������ɾ��
					
					if(SourceRock)
					{
						GetHCGIPerUnitInitTOC(StrSegLeft); //�����Դ�ң�����㵥λ����(kg)ԭʼ�л�̼�Ľ����� ��������-Ro����
						GetInitTOC();  //���ԭʼ�л�̼���������� ��������-Ro����
						GainHCGIPerUnitInitTOC(StrSegLeft); //��õ�λԭʼ�л�̼������������ѧ����ѧ����
						GainInitTOC(); //���ԭʼ�л�̼���������� ����ѧ����ѧ����
						// FlashCalculation(StrSegLeft);
						// GetEEFromRo();  //����Ro�������Ч��
						//  GetTRFromDR();  // //������Խ����ʷ���������ת����
						//  GetEEFromTR();  //ͨ��TR�������Ч�ʺ�����Ч��
					}
				} //�ǵز�����---����
				if(Property==2)
				{ //����������----��ʼ
				if(!Eroded) //���û����ʴ�����Ͱ������ĵز㴦��
					{ //*********************************************
						GetTmax(StrSegLeft); //������ڻ�֮ǰ������¶�
						GetTTI(StrSegLeft);//���TTIֵ

						GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
						GetRoFromEasyRo(StrSegLeft); //���EasyRo�����õ���Roֵ    ������������ɾ��
						GetRoFromBasinRo(StrSegLeft); //���BasinRo�����õ���Roֵ
						GetRoFromSimpleRo(StrSegLeft); //���SimpleRo�����õ���Roֵ   ������������ɾ��
						 //FlashCalculation(StrSegLeft);
					} //*********************************************
				if(Eroded)
					{  //����Ѿ�����ʴ
						Tt=StrSegTop->Tb;
						Tb=Tt;       //������ʴ�󣬸�StrSeg���¶�͸��
						//Ro=StrSegLeft->Ro;       //�Ա���ԭ�ȵľ����巴���ʣ����ڼ����Ƚ��⣬��ʵRo����֮ǰ��״̬Ҳ��ζ���Ƚ����ʲ���
						for (int i = RO_TTI; i <= RO_Basin; i++)
						{
							Ro[i] = StrSegLeft->Ro[i];
						}

					}
				if(SourceRock)
					{    //��Ȼ�ǰ�ʴ�˵���ز㣬��Ҳ�������ز�һ����������ǿ�ȣ�ֻ������ʴ���κ�ʱ�������ǿ�ȶ����ʴǰ������ǿ��һ��
					GetHCGIPerUnitInitTOC(StrSegLeft); //�����Դ�ң�����㵥λ����(kg)ԭʼ�л�̼�Ľ�����  ,������-Ro����
					GetInitTOC();  //���ԭʼ�л�̼����������    ,������-Ro����
					GainHCGIPerUnitInitTOC(StrSegLeft); //��õ�λԭʼ�л�̼������������ѧ����ѧ����
					GainInitTOC(); //���ԭʼ�л�̼���������� ����ѧ����ѧ����
					}
				} //����������----����
				if(Property==3||Property==4)
				{ //����ǰ�ʴ�����¼�����
					Tt=StrSegTop->Tb;
					Tb=Tt;       //��ʴ�ͼ���¼���StrSeg���¶�͸��
				}
			}

			void GetFromNearbyStrSeg(StrSeg *StrSegLeft, StrSeg *StrSegTop) //ͨ����ࣨ��ʱ���ϵ���һ�������ϲ������ռ��ϵģ�StrSeg�����Ϣ
			{    //�˺���Ӧ���ڷǳ�ʼStrSeg�������ڸ��ֵز�����Ե����
				aPetroGenStyle=StrSegLeft->aPetroGenStyle; ///new added 2017-11-22
				BeginAge=StrSegTop->BeginAge ;   //�����θ�ʱ��ֵ
				EndAge=StrSegTop->EndAge ;
				DeltaAge=StrSegTop->DeltaAge ;
				MiddleAge=StrSegTop->MiddleAge ;
				TopDepth=StrSegTop->BottomDepth;  //���������Զ�����ϲ�StrSeg�ĵײ����
				BuryTopDepth=StrSegTop->BuryBottomDepth;  //���������Զ�����ϲ�StrSeg�ĵײ����
				PaleoWaterDepth=StrSegTop->PaleoWaterDepth; //��ˮ����ڵȲ��ز�εĹ�ˮ��
				HF=StrSegTop->HF; //�������ڶ����ز�ε�����
				SurfaceT=StrSegTop->SurfaceT; //�����¶��������StrSeg�ı����¶ȴ���
				MatrixThickness=StrSegLeft->MatrixThickness;//����һ��ʱ���(�����)��StrSeg��ùǼܺ��
				SourceRock=StrSegLeft->SourceRock ;   //����һ��ʱ��ε�StrSeg����Ƿ�ΪԴ�ҵ���Ϣ
				
				//2017/7/18:add density
				TMatrixDensity = StrSegLeft->TMatrixDensity;

				if(SourceRock) TOC=StrSegLeft->TOC ;     //����һ��ʱ��ε�StrSeg��ò����л�̼����
				//���ݲ�ͬ��StrSeg���ʽ��в�ͬ���жϺͲ���
				//====================================
				if(Property==1)
				{   //�ǵز�����
				if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
				{   //�ж϶���������������������ѹʵ����
					GetBuryBottomDepth();
					Thickness=BuryBottomDepth-BuryTopDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����,�ӳ�����������
					MiddleDepth=TopDepth+0.5*Thickness;//�в����
					BottomDepth=TopDepth+Thickness;//�������
					MaxBuryTopDepth=BuryTopDepth;      //  �����������
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
					GetPorosity();             //��ÿ�϶��
				}
				else
				{ //������������С�ڵ�����󶥲�����ʱ����Ȳ��䣬��������
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//�������
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//�в����
					BottomDepth=TopDepth+Thickness;//�������
					MiddleDepth=TopDepth+0.5*Thickness;//�в����
					MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;    //�������ֲ���
					MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
					MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
					Porom=StrSegLeft->Porom;            //��϶�ȱ��ֲ���

					//2019/1/24: add top,bottom value
					Porot=StrSegLeft->Porot;  //��϶�ȱ��ֲ���,t
					Porob=StrSegLeft->Porob;  //��϶�ȱ��ֲ���,b
				}
				GetT(StrSegLeft, StrSegTop); //����¶�
				GetTmax(StrSegLeft); //������ڻ�֮ǰ������¶�
				GetTTI(StrSegLeft);//���TTIֵ

				GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
				GetRoFromEasyRo(StrSegLeft); //���EasyRo�����õ���Roֵ  ������������ɾ��
				GetRoFromBasinRo(StrSegLeft); //���BasinRo�����õ���Roֵ
				GetRoFromSimpleRo(StrSegLeft); //���SimpleRo�����õ���Roֵ ������������ɾ��
				if(SourceRock)
					{
					GetHCGIPerUnitInitTOC(StrSegLeft); //�����Դ�ң�����㵥λ����(kg)ԭʼ�л�̼�Ľ����� ��������-Ro����
					GetInitTOC();  //���ԭʼ�л�̼���������� ��������-Ro����
					GainHCGIPerUnitInitTOC(StrSegLeft); //��õ�λԭʼ�л�̼������������ѧ����ѧ����
					GainInitTOC(); //���ԭʼ�л�̼���������� ����ѧ����ѧ����
					}
				}
				//===================
				if(Property==2)
				{ //����������
				if(!StrSegLeft->Eroded) //���û����ʴ�����Ͱ������ĵز㴦��
					{ //*********************************************
					if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
					{  //��������ȴ�����������ȣ�˵�����ڳ������̣���ѹʵ���̴���
						GetBuryBottomDepth();  //
						Thickness=BuryBottomDepth-BuryTopDepth;
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����,�ӳ�����������
						MiddleDepth=TopDepth+0.5*Thickness;//�ܵ�����в���ȣ���ˮ������
						BottomDepth=TopDepth+Thickness;//�������
						MaxBuryTopDepth=BuryTopDepth;      //  �����������
						MaxBuryMiddleDepth=BuryMiddleDepth;
						MaxBuryBottomDepth=BuryBottomDepth;
						GetPorosity();      //��ÿ�϶��
						GetT(StrSegLeft, StrSegTop); //����¶�
						GetTmax(StrSegLeft); //������ڻ�֮ǰ������¶�
						GetTTI(StrSegLeft);//���TTIֵ

						GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
						GetRoFromEasyRo(StrSegLeft); //���EasyRo�����õ���Roֵ    ������������ɾ��
						GetRoFromBasinRo(StrSegLeft); //���BasinRo�����õ���Roֵ
						GetRoFromSimpleRo(StrSegLeft); //���SimpleRo�����õ���Roֵ   ������������ɾ��
					}
					else
					{ //���������С�ڵ�����󶥲�����ʱ����Ȳ��䣬��������
						//��ʱ�����������״̬����һ�ǻ�û����ʴ��������Ѿ�����ʴ
						// ��������if()֮�ϵĲ��ִ�����ǻ�û��ʴ�������ͬʱ��ȫ���Ͳ��ְ�ʴҲ������
						Thickness=StrSegLeft->Thickness;
						BuryBottomDepth=BuryTopDepth+Thickness;//����������
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//�в�������
						BottomDepth=TopDepth+Thickness;//�������
						MiddleDepth=TopDepth+0.5*Thickness;//�в����
						MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;
						MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
						MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
						Porom=StrSegLeft->Porom;

						//2019/1/24: add top,bottom value
						Porot=StrSegLeft->Porot;  //��϶�ȱ��ֲ���,t
						Porob=StrSegLeft->Porob;  //��϶�ȱ��ֲ���,b

						if(BuryBottomDepth<MarginOfErrorThickness)  //����һ��������ݴ�ֵ������Ϊ 1cm
						{ // ����ײ����С��0�ˣ������õز���Ѿ�����ȫ��ʴ��
							Eroded=true; //���ײ�����С��0ʱ��˵���Ѿ�����ʴ����Eroded������Ϊtrue
							Tt=StrSegTop->Tb;
							Tm=Tt;
							Tb=Tt;       //������ʴ�󣬸�StrSeg���¶�͸��
							
							//Ro=StrSegLeft->Ro; //����ʴ��Roʼ�ձ�����ǰ��ֵ
							for (int i = RO_TTI; i <= RO_Basin; i++)
							{
								Ro[i] = StrSegLeft->Ro[i];
							}
						}
						else
						{  //���û�а�ʴ
							GetT(StrSegLeft, StrSegTop); //�ú����Ѿ������˹��ڲ��ְ�ʴ�������
							GetTmax(StrSegLeft); //������ڻ�֮ǰ������¶�
							GetTTI(StrSegLeft);//���TTIֵ

							GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
							GetRoFromEasyRo(StrSegLeft); //���EasyRo�����õ���Roֵ   ������������ɾ��
							GetRoFromBasinRo(StrSegLeft); //���BasinRo�����õ���Roֵ
							GetRoFromSimpleRo(StrSegLeft); //���SimpleRo�����õ���Roֵ  ������������ɾ��
						}
					}
					} //*********************************************
				if(StrSegLeft->Eroded)
					{  //����Ѿ�����ʴ�ˣ��ټ���ʱ��ȱ��ֲ��䣬���ʴStrSeg����������---���������ã���ȣ�֮��Ϊ0
						Eroded=true;
						Thickness=StrSegLeft->Thickness;
						BuryBottomDepth=BuryTopDepth+Thickness;//��ص������
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//����в����
						BottomDepth=TopDepth+Thickness;//�������
						MiddleDepth=TopDepth+0.5*Thickness;//�в����
						Porom=StrSegLeft->Porom;   //����ʴ���Ա���ԭ�ȵĿ�϶�ȣ���Ҫ�������������㡪�����ڼ����л�̼ ��ԭʼ�л�̼��
						Tt=StrSegTop->Tb;
						Tm=Tt;
						Tb=Tt;       //������ʴ�󣬸�StrSeg���¶�͸��
						//Ro=StrSegLeft->Ro;       //�Ա���ԭ�ȵľ����巴���ʣ����ڼ����Ƚ��⣬��ʵRo����֮ǰ��״̬Ҳ��ζ���Ƚ����ʲ���

						for (int i = RO_TTI; i <= RO_Basin; i++)
						{
							Ro[i] = StrSegLeft->Ro[i];
						}
					}
					if(SourceRock)
					{    //��Ȼ�ǰ�ʴ�˵���ز㣬��Ҳ�������ز�һ����������ǿ�ȣ�ֻ������ʴ���κ�ʱ�������ǿ�ȶ����ʴǰ������ǿ��һ��
						GetHCGIPerUnitInitTOC(StrSegLeft); //�����Դ�ң�����㵥λ����(kg)ԭʼ�л�̼�Ľ�����  ,������-Ro����
						GetInitTOC();  //���ԭʼ�л�̼����������    ,������-Ro����
						GainHCGIPerUnitInitTOC(StrSegLeft); //��õ�λԭʼ�л�̼������������ѧ����ѧ����
						GainInitTOC(); //���ԭʼ�л�̼���������� ����ѧ����ѧ����
					}
				}
				//=======================================
				if(Property==3||Property==4)
				{ //����ǰ�ʴ�����¼����ԣ�ֻ�к�Ⱥ͵ײ���Ȳ����������õ�
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//����������
					BottomDepth=TopDepth+Thickness;//�������
					Tt=StrSegTop->Tb;
					Tb=Tt;       //��ʴ�¼�StrSeg���¶�͸��
				}
			}
			
			void GetMatrixThickness()
			{   //�����ʯ�Ǽܺ�� ;;���������͵����ùǼܺ��
				double tempTop=0.,tempBottom=0.;
				for(int i=0;i<LithNumber;i++)
				{
					tempTop+=LithRatio[i]*PorosityToDepthExpDivByComp(InitialPorosity[i],CompactionFactor[i], MaxBuryTopDepth);
					tempBottom+=LithRatio[i]*PorosityToDepthExpDivByComp(InitialPorosity[i],CompactionFactor[i], MaxBuryBottomDepth);
				}
				MatrixThickness=(MaxBuryBottomDepth-MaxBuryTopDepth+tempBottom-tempTop);
			}
			
			void GetEndPorom()
			{ //����ֽ�ز��϶��
				EndPorom=1.-MatrixThickness/CurrentThickness; 
			}
			
			void GetBuryBottomDepth()
			{  //���ݶ�����Ȼ�õײ���ȣ����������
				int kk=0;
				double tempBuryBottomDepth1=BuryTopDepth+MatrixThickness; //�����ĳ�ʼ�ײ������Ϊ�������
				double tempBuryBottomDepth2;
				double tempBuryTop=0,tempBuryBottom=0;
				double wc;
				do
				{
					for(int i=0;i<LithNumber;i++)
					{
						tempBuryTop+=LithRatio[i]*PorosityToDepthExpDivByComp(InitialPorosity[i],CompactionFactor[i], BuryTopDepth);
						tempBuryBottom+=LithRatio[i]*PorosityToDepthExpDivByComp(InitialPorosity[i],CompactionFactor[i], tempBuryBottomDepth1);
					}
					tempBuryBottomDepth2=(MatrixThickness+BuryTopDepth+tempBuryTop-tempBuryBottom);
					wc=fabs(tempBuryBottomDepth2-tempBuryBottomDepth1);
					tempBuryBottomDepth1= tempBuryBottomDepth2;
					tempBuryTop=0,tempBuryBottom=0;
					kk++;
				}while(wc>0.00001 && kk<100);
				
				BuryBottomDepth=tempBuryBottomDepth1;
			}
		
			double PorosityToDepthExpDivByComp(double InitPoro, double CompF,double Depth)
			{ 
				//��϶�������ָ���仯��ϵ������CompactionFactor�������ں�Ȼָ�֮�ã�
				//������Ӧ����ʯ��ʼ��϶�Ⱥ�ѹʵϵ��,�������ȵ�λΪm
				double OutPut;
				if(fabs(InitPoro)<1.0e-8) OutPut=0.;   //�����ʯ��ʼ��϶��Ϊ0����������Ϊ0
				else OutPut= InitPoro*exp(-CompF*Depth)/CompF;
				return  OutPut;
			}

			void GetPorosity()
			{  //���ݻ�����Ա�����ÿ�϶�ȣ��ú�������Ե�Ч����㷨������Ϊ�����Ⱦ��ǵ�Ч���
				Porot=0; Porom=0; Porob=0;
				Porosityt=new double[LithNumber]; Porositym=new double[LithNumber]; Porosityb=new double[LithNumber];
				for(int i=0;i<LithNumber;i++)
				{
					Porosityt[i]=InitialPorosity[i]*exp(-CompactionFactor[i]*BuryTopDepth);
					Porositym[i]=InitialPorosity[i]*exp(-CompactionFactor[i]*BuryMiddleDepth);
					Porosityb[i]=InitialPorosity[i]*exp(-CompactionFactor[i]*BuryBottomDepth);
					Porot+= Porosityt[i]*LithRatio[i];
					Porom+= Porositym[i]*LithRatio[i];
					Porob+= Porosityb[i]*LithRatio[i];
				}
			}

			void GetPermeability()
			{
				LogPermeability=new double[LithNumber];
				for(int i=0;i<LithNumber;i++)
					LogPermeability[i]=GetPermeabilityFromPorosity(Porositym[i],3,aPoro_Perm[i].Perm.data(),aPoro_Perm[i].Poro.data());  //�õ��Ľ�� ��λΪLog mD
				double GeometricMeanLogPerm=0.;
				for(int i=0;i<LithNumber;i++)  
					GeometricMeanLogPerm+=LithRatio[i]*LogPermeability[i];
				
				//2017/9/6: fix overpressure problems
				Perm = ::pow(10.,GeometricMeanLogPerm);
				//Perm=exp(GeometricMeanLogPerm); //���ڵĵ�λ��mD
				
				Perm/=1000.;   //ת��Ϊ����D     1md=0.98692e-3��m^2
				Perm*= 0.98692e-12; //ת��Ϊm^2     ,Ҳ����1md=0.98692e-15m^2
			}

			double GetPermeabilityFromPorosity(double aPorosity,int NumPoroPermPairs,double *LogPerms,double *Poros)
			{ //���ڻ�ö�Ӧ�ڿ�϶�ȵ���͸����Ȼ����ֵ
				double LogPermi; //��͸����Ȼ����ֵ
				if(aPorosity*100.<=Poros[0]) LogPermi=LogPerms[0];  //����Poro_Perm���еĿ�϶�ȶ��ǰٷ�����������Ŀ�϶��ΪС�������Ҫ������Ŀ�϶��ֵ����100
				if(aPorosity*100.>=Poros[NumPoroPermPairs-1]) LogPermi=LogPerms[NumPoroPermPairs-1];
				for(int i=0;i<NumPoroPermPairs-1;i++)
					if(aPorosity*100.>=Poros[i]&&aPorosity*100.<Poros[i+1])
						LogPermi=LinerInterpolate( aPorosity*100.,Poros[i],LogPerms[i],Poros[i+1],LogPerms[i+1]);
				return LogPermi;
			}
		
			//void GetWaterViscosity()
			//{    //���϶�(�H)=32+���϶�(��)��1.8
			//	WaterViscosity=109.5*pow(32+Tm*1.8,-1.122);  //����ĵ�λΪ�岴cP,1�岴(1cP)=1����˹��.�� (1mPa.s)
			//	WaterViscosity/=1000.; //����ת��ΪPa.s
			//}
		
			void GetMatrixThicknessInTheEnd()
			{ 
				//����㱻��ʴ��ʱ���Լ���ģ�����ʱ�̷ֱ�����ڱ���ѭ���и��ݱ���ѭ���õ��Ŀ�϶������һѭ��Ӧ��ʹ�õĹǼܺ��
				//���������ε�����϶�ȵĲ�ֵ�ľ���ֵ
				if(pos_k==EndPoint)
				{
					if(Property==1||Property==2)
					{
						MatrixThickness=(1.-Porom)*CurrentThickness;
						DifferencePoromEndPorom=fabs(Porom-EndPorom);
						EndPorom=Porom;
					}
				}
			}
			
			void GetTTI(StrSeg *StrSegLeft)
			{  //���TTIֵ
				TTI=TTIF(StrSegLeft->Tm,BeginAge ,Tm,EndAge,StrSegLeft->Tmax,StrSegLeft->TTI);
			}
		
			void GetTTI()
			{  //�������ز�ε�TTI
				TTI=TTIF(SurfaceT,BeginAge ,Tm,EndAge,SurfaceT,TTI0);
			}

			double TTIF(double TLast, double tLast, double T, double t,double LastTMax,double TTILast)
			{
				//TTI���㺯��
				// ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
				//Tmax ��¼������һ�ز�㽫����������¶ȣ����ز��¶�С��TMaxʱ������TTI���㣬TTI����ԭֵ��ֻ�е��ز��¶ȴ���TMaxʱ�ż���TTIֵ��������ʱ�ĵز��¶ȸ�ֵ��TMax
				//TTILast����һ����TTIֵ
				double TTI;
				if(T<=LastTMax) TTI=TTILast; //������ڵ��¶�С�ڵ�����һ������¼��TMax����TTI�͵�����һ����TTIֵ
				else
				{
				TTI=TTILast;  
				double a,b; // ���Ա仯��ϵ��
				a=(T-TLast)/(t-tLast);b=T-a*t;
				//����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
				int N=int(fabs(T-TLast)/2.0+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������2�棬�����1�Ǳ�֤������1����ִ�С�
				double Delta_t=(t-tLast)/double(N);  //Delta_t�������������������
				double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
				double TMM;
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					TMM=a*ttM+b;
					TTI+=pow(2.0,(TMM-105.0)/10.0)*fabs(Delta_t);
					tt1=tt2;
				}
				} 
				return TTI;
			}
			
			//2017/7/25: tti-ro
			void GetRoFromTTIRo()
			{
				Ro[RO_TTI] = 0;/*GetRoByTTI(TTI)*/;
			}

			void GetRoFromEasyRo(StrSeg *StrSegLeft)
			{
				aParaOfEasyRo=new ParaOfEasyRo;  //�ȿ����ṹ�ռ�
				aParaOfEasyRo->CopyFrom(StrSegLeft->aParaOfEasyRo); //�����ز�ε�EasyRo������ֵ�����ز�ε�EasyRo�����ṹ��
				Ro[RO_Easy]=EasyRo(StrSegLeft->Tm,BeginAge, Tm, EndAge,aParaOfEasyRo->NN,aParaOfEasyRo->f,aParaOfEasyRo->E,aParaOfEasyRo->A,aParaOfEasyRo->Roo,aParaOfEasyRo->f0 );
			}
			
			void GetRoFromEasyRo()
			{   //���ڵ�һ���ز�ε�Ro����
				Ro[RO_Easy]=EasyRo(SurfaceT,BeginAge ,Tm,EndAge,aParaOfEasyRo->NN,aParaOfEasyRo->f,aParaOfEasyRo->E,aParaOfEasyRo->A,aParaOfEasyRo->Roo,aParaOfEasyRo->f0 );
			}
			
			void GetRoFromBasinRo(StrSeg *StrSegLeft)
			{
				aParaOfBasinRo=new ParaOfEasyRo;  //�ȿ����ṹ�ռ�
				aParaOfBasinRo->CopyFrom(StrSegLeft->aParaOfBasinRo); //�����ز�ε�EasyRo������ֵ�����ز�ε�EasyRo�����ṹ��
				Ro[RO_Basin]=EasyRo(StrSegLeft->Tm,BeginAge, Tm, EndAge,aParaOfBasinRo->NN,aParaOfBasinRo->f,aParaOfBasinRo->E,aParaOfBasinRo->A,aParaOfBasinRo->Roo,aParaOfBasinRo->f0 );
			}
			
			void GetRoFromBasinRo()
			{ //���ڵ�һ���ز�ε�Ro����
				Ro[RO_Basin]=EasyRo(SurfaceT,BeginAge ,Tm,EndAge,aParaOfBasinRo->NN,aParaOfBasinRo->f,aParaOfBasinRo->E,aParaOfBasinRo->A,aParaOfBasinRo->Roo,aParaOfBasinRo->f0 );
			}
			
			void GetRoFromSimpleRo(StrSeg *StrSegLeft)
			{
				aParaOfSimpleRo=new ParaOfSimpleRo;
				aParaOfSimpleRo->CopyFrom(StrSegLeft->aParaOfSimpleRo);
				Ro[RO_Simple]=SimpleRo(StrSegLeft->Tm,BeginAge, Tm, EndAge,aParaOfSimpleRo->f,aParaOfSimpleRo->aerf,aParaOfSimpleRo->beita,aParaOfSimpleRo->A,aParaOfSimpleRo->Roo, aParaOfSimpleRo->f0);
			}
			
			void GetRoFromSimpleRo()
			{   //���ڵ�һ���ز�ε�Ro����
				Ro[RO_Simple]=SimpleRo(SurfaceT,BeginAge ,Tm,EndAge,aParaOfSimpleRo->f,aParaOfSimpleRo->aerf,aParaOfSimpleRo->beita,aParaOfSimpleRo->A,aParaOfSimpleRo->Roo, aParaOfSimpleRo->f0);
			}

			double EasyRo(double TLast, double tLast, double T, double t,int NN,double *f,double *E,double A,double Roo,double f0 )
			{
				// EASY%Ro���㺯����Ҳ����BasinRo�����Ƶ��û��Զ������Roģ�ͼ���.��������ֵΪRo%
				// ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
				//NN��ƽ�з�Ӧ�����
				//f �ǻ�ѧ����ϵ����Stoichiometric Factor��
				//E�ǻ�ܣ�Activation Energy����Kcal/mole��
				//A��Ƶ������ S^-1
				//Roo���ڵر��ʼʱ�̵ľ�����Roֵ;
				//f0�ǳ�ʼ��ѧ����ϵ��֮��
				//��ʽԭ����Դ��Sweeney and Burnham,1990
				double *wiBIw0i;  //wi/w0i
				wiBIw0i=new double[NN];
				TLast+=273;T+=273;   //ת��Ϊ�����¶�
				tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				t=t*1000000*365*24*3600; //������ת��Ϊ��
				double Ro;//����ľ����巴����ֵ
				double F=0;//���Ĺ�ʽ��1���͸�����ʽ��6���е�ֵ��ָ���Ƿ�Ӧ���ת������
				double wBIw0=0;//������ʽ��6���е�w/w0
				double R=0.001986;//���峣�� ����λ Kcal/(mol*K)
				//������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
				double a,b; // ���Ա仯��ϵ��
				a=(T-TLast)/(t-tLast);b=T-a*t;
				//����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
				int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
				double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
				double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
				double temp=0;
				for(int i=0;i<NN;i++)
				{
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					temp+=(-A*exp(-E[i]/R/(a*ttM+b)))*fabs(Delta_t);
					tt1=tt2;
				}
				wiBIw0i[i]=exp(temp);
				f[i]=f[i]*wiBIw0i[i];
				wBIw0+=f[i];
				tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
				temp=0;    //temp���¹���
				}

				//release
				delete wiBIw0i;

				F=f0-wBIw0;  //f0Ϊ�����л�ѧ����ϵ���ܺͣ�wBIw0Ϊ��ѧ����ϵ��ʣ��ֵ
				Ro=Roo*exp(3.7*F);
				return Ro;
			}

			double SimpleRo(double TLast, double tLast, double T, double t,double &f,double aerf,double beita,double A,double Roo, double f0)
			{
				//Simple%Ro���㺯����Ҳ�������Ƶ��û��Զ������Roģ�ͼ���.��������ֵΪRo%
				// ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
				//f �ǻ�ѧ����ϵ����Stoichiometric Factor�����ǵ�ֵ���ں����лᱻ�ı�
				//aerf, beita��Simple Ro�����л��E��lnRo��Ĺ�ϵ����  (E=��lnRo+��) ��E�ĵ�λ��Kcal/mol
				//A��Ƶ������ S^-1
				//Roo���ڵر��ʼʱ�̵ľ�����Roֵ;
				//f0�ǳ�ʼ��ѧ����ϵ��,Ϊ��ֵ
				//��ʽԭ����Դ��Suzuki et al.,1993
				double Ro;
				double F=f0-f;  //Fָ���Ƿ�Ӧ���ת������,����ʼ�Ļ�ѧ����ϵ����ȥ��Ӧ��Ļ�ѧ����ϵ��
				Ro=Roo*exp(3.7*F); //����ľ����巴����ֵ��������������һ����fֵ�����һ��������E��Roֵ
				TLast+=273;T+=273;   //ת��Ϊ�����¶�
				tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
				t=t*1000000*365*24*3600; //������ת��Ϊ��
				double wBIw0;//������ʽ��6���е�w/w0
				double R=0.001986;//���峣�� ����λ Kcal/(mol*K)
				double E; //��ܣ�Activation Energy����Kcal/mole��
				E=aerf*log(Ro)+beita; //Simple Ro��E��Ro�Ĺ�ϵ
				double a,b; // ���Ա仯��ϵ��
				a=(T-TLast)/(t-tLast);b=T-a*t;
				//����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
				int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
				double Delta_t=(t-tLast)/double(N);  //Delta_t�������������������
				double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					wBIw0=exp((-A*exp(-E/R/(a*ttM+b)))*fabs(Delta_t));
					f=f*wBIw0;
					F=f0-f;  //f0Ϊ�����л�ѧ����ϵ���ܺͣ�fΪ��ѧ����ϵ��ʣ��ֵ
					Ro=Roo*exp(3.7*F);
					E=aerf*log(Ro)+beita;
					tt1=tt2;
				}
				return Ro;
			}

		};  //struct  StrSeg����

		//temperature/overpressure
		void GetParaByTransitHeatCond(int Pointer,POS *aPOS,StrSeg ***StrSegWell);
		void GetParaBySteadyHeatCond(int Pointer,POS *aPOS,StrSeg ***StrSegWell);
		void GetParaByOverpressureEquation(int Pointer,POS *aPOS,StrSeg ***StrSegWell);
		
		//
		template <class T>
		T ReturnMaxValue(T Array[],int n)
		{
			T Temp=Array[0];
			for(int i=0;i<n;i++)
				if(Temp<Array[i]) {Temp=Array[i]; }
				return Temp;
		}

		//
		static double LinerInterpolate(double t,double t0,double p0,double t1,double p1);
		static double GetRand( double a, double b);
		
		//
		void StretchHeatFlowMode(double SBeginAge,double SEndAge,double EndTime,double Beita, double a, double Ts, double Tm, double k,double rou, double c, int N,double *t,double *Fs);
			
		//
		double GetPaleoWaterDepth(double t,int NumPaleoWaterDepth,double *PaleoWaterDepth,double *PaleoWaterDepth_t);
		double GetSurfaceT(double t,int NumSurfaceT,double *SurfaceT,double *SurfaceT_t);
		double GetHF(double t,int NumHF,double *HF,double *HF_t, double toage);
		
	};
}
#endif