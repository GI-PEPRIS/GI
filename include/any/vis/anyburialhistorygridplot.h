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
		 //油气生成动力学模型类型 ，{LLNL模型，有机相模型 }
		enum PetroGenStyle 
		{
			LLNL = 0,
			Organo,
		}; 

		//定义一个有机相类型枚举类
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

		 //定义烃类类型，根据相态计算得到,分别是油气两相、油和气
		enum HCType
		{
			OilGas = 0,
			Oil,
			Gas
		}; 

		//定义状态方程类型的枚举类型，分别是{the Soave–Redlich–Kwong EOS (SRK)，the Peng–Robinson EOS (PR)}
		enum EOS
		{
			SRK = 0,
			PR
		};

	private:

		
		//拟组分内的组分的性质   properties of pseudo-components  赋值和计算
		struct Properties 
		{    
			int NGroupCom; //拟组分中的组分数  =5
			double *ComMolFra; //在拟组分中的各组分的摩尔比例
			double *MWi;       //组分摩尔质量  kg/kgmol
			double *Tci,*Pci; //组分临界温度和压力   K和MPa
			double *Omegai; //the dimensionless acentric factor,各组分的
			double *Zci,*Vci;
			//double **kij; //binary interaction parameter 二元相互作用参数
			double MW,Tc,Pc,Omega,Zc,Vc; //拟组分的总的性质
			double PcMolAveraging; //根据摩尔平均值得到的值，这里没有采用，只是计算用于比较分析
			double z; //mole fraction of the group in the mixture    该拟组分在混合物中的摩尔比例
			
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

				double R=0.008314; //气体常数
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
				for(int i=0;i<NGroupCom;i++)   //molar averaging ,但这里的PC
				{ MW+=MWi[i]*ComMolFra[i];Tc+=Tci[i]*ComMolFra[i]; Pc+=Pci[i]*ComMolFra[i]; Omega+=Omegai[i]*ComMolFra[i];Zc+=Zci[i]*ComMolFra[i];Vc+=Vci[i]*ComMolFra[i];}
				// Pc=Zc*R*Tc/Vc; //根据poling  2000 The properties of gases and liquids ，(5-3.2)    对于Pc还是采用了摩尔平均
			}
		};

		static void GetGroupkij(int NCom,double **kij,double **GasOilkij,Properties *aProperties)
		{ //获得拟组分间的Binary interaction parameters  Danesh,1998, p309 9.16
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

		static double ReturnMin(double x1,double x2,double x3) //返回
		{ 
			double temp = 0.; 
			if(x1<x2)
				temp=x1;
			else 
				temp=x2; 
			if(temp>x3) temp=x3; 
			
			return temp;
		}
		
		static double ReturnMax(double x1,double x2,double x3) //返回
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

		//一元三次方程的解
		//分别为方程的三个解，Case代表状态
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
			//方程 ax^3+bx^2+cx+d=0; 盛金公式求解
			SolutionOfCE aSCE;
			//double a=15.,b=-200.,c=3.,d=4.;
			double A=b*b-3.*a*c;
			double B=b*c-9.*a*d;
			double C=c*c-3.*b*d;
			double Delta=B*B-4.*A*C;
			double x1,x2,x3; //方程解
			if(A==0&&B==0)  // "A==0&&B==0,有一个三重根"
			{aSCE.x1=-b/3./a;aSCE.x2=aSCE.x1;aSCE.x3=aSCE.x2; aSCE.Case=1;}
			else
			{
				if(Delta>0)
				{ // Delta>0，有一个实根，两个虚根，虚根略,
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
				{ // "Delta==0，有三个实根，其中有两个是二重根"
					double K=B/A;
					aSCE.x1=-b/a+K;
					aSCE.x2=-K/2.;
					aSCE.x3=aSCE.x2;
					aSCE.Case=3;
				}
				if(Delta<0)
				{ // "Delta<0，有三个不同实根"
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
		double GetVOfRRE(int NCom,double *z,double *K, double aPoint) //获得Rachford-Rice方程值 Danesh 1998, (5.6)P169
		{
			double tempV=0;
			for(int i=0;i<NCom;i++)
				tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*aPoint);
			return tempV;
		}
		void GetInitKi(int NCom,double *K, double *Pci,double Pm, double *Omegai,double *Tci,double Tm)
		{ //获得每一组分的初始的平衡比Ki，Danesh 1998, (3.66)P122
			for(int i=0;i<NCom;i++) K[i]=Pci[i]/Pm*exp(5.37*(1.+Omegai[i])*(1.-Tci[i]/Tm));
		}

		void GetParasOfComsInEOS(int NCom,double *xi,double **kij,double *Tci,double *pci, double Tm,double Pm,double *Omegai,double R,double &a,double &b,double *aci,double *bi,double *mi,double *Alphai, double *ai,double *Ai,double *Bi,EOS aEOS) //获得状态方程中各组分的参数
		{

			b=0; a=0;  //赋初值为0
			for(int i=0;i<NCom;i++)
			{
				switch(aEOS)
				{
				case SRK:
					aci[i]=0.42747*R*R*Tci[i]*Tci[i]/pci[i];      //Danish,1998 P140  4.22
					bi[i]=0.08664*R*Tci[i]/pci[i];            //Danish,1998 P140  4.22
					mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
					Alphai[i]=(1.+mi[i]*(1.-sqrt(Tm/Tci[i])))*(1.+mi[i]*(1.-sqrt(Tm/Tci[i]))); //Danish,1998 P140  4.23
					ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
					Ai[i]=ai[i]*Pm/(R*Tm*R*Tm);          //Danish,1998 P132  4.7  虽然计算了，但暂时没有用到
					Bi[i]=bi[i]*Pm/(R*Tm);              //Danish,1998 P132  4.8   虽然计算了，但暂时没有用到
					break;
				case PR:
					aci[i]=0.457235*R*R*Tci[i]*Tci[i]/pci[i];    //Danish,1998 P141  4.27
					bi[i]=0.077796*R*Tci[i]/pci[i];          //Danish,1998 P141  4.27
					mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
					Alphai[i]=(1.+mi[i]*(1.-sqrt(Tm/Tci[i])))*(1.+mi[i]*(1.-sqrt(Tm/Tci[i]))); //Danish,1998 P140  4.23
					ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
					Ai[i]=ai[i]*Pm/(R*Tm*R*Tm);          //Danish,1998 P132  4.7     虽然计算了，但暂时没有用到
					Bi[i]=bi[i]*Pm/(R*Tm);              //Danish,1998 P132  4.8      虽然计算了，但暂时没有用到
					break;
				};
			}
			for(int i=0;i<NCom;i++)
			{    //混合规则  Mixture parameters
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
		void GetFaii(int NCom,EOS aEOS,double *Faii,double *ai,double *bi,double *x,double a,double b,double **kij,double A,double B,double Z)   //计算逸度系数 Danish,1998 p157 E4.5
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
		{    //获得油气相态组分的逸度以及组分的平衡比
			for(int i=0;i<NCom;i++)  { fiL[i]=FaiiL[i]*x[i]*Pm;  fiV[i]=FaiiV[i]*y[i]*Pm; K[i]=FaiiL[i]/FaiiV[i];}
		}
		void GetErrorValue_fiLfiV(double &ErrorValue_fiLfiV,int NCom,double *fiL,double *fiV)
		{     //Danish,1998  P174
			ErrorValue_fiLfiV=0;
			for(int i=0;i<NCom;i++) ErrorValue_fiLfiV+=(1.-fiL[i]/fiV[i])*(1.-fiL[i]/fiV[i]);
		}
		void BubblePressureAdjusted(int NCom,double &Pm,double *x,double *K)//调整压力使其接近泡点压力 Danesh 1998,P174  (E5.2')
		{
			double tempSum=0;
			for(int i=0;i<NCom;i++) tempSum+=x[i]*K[i];
			Pm=Pm*tempSum;
		}
		void DewPressureAdjusted(int NCom,double &Pm,double *y,double *K)//调整压力使其接近露点压力 Danesh 1998,P174  (E5.2')
		{
			double tempSum=0;
			for(int i=0;i<NCom;i++) tempSum+=y[i]/K[i];
			Pm=Pm*tempSum;
		}
		void GetvLvV(double &vL,double &vV,double R,double Tm,double ZL,double ZV,double Pm ) //获得油气的摩尔体积  Danish,1998 P40 2.5
		{
			vL=R*Tm*ZL/Pm;
			vV=R*Tm*ZV/Pm;
		}
		void GetMWLMWV(int NCom,double &MWL,double &MWV,double *MW,double *x,double *y) //获得油相和气相的摩尔质量
		{
			MWL=0;MWV=0;
			for(int i=0;i<NCom;i++)
			{
				MWL+=x[i]*MW[i];
				MWV+=y[i]*MW[i];
			}
		}
		void GetLVDensity(double &OilDensity, double &GasDensity, double vL,double vV,double MWL,double MWV) //获得油、气相的密度
		{
			OilDensity=MWL/vL; GasDensity=MWV/vV;
		}
		void GetpTcpPc(int NCom,double *xi,double **kij,double *Tci,double *pci, double *Omegai,double R,double &a,double &b,double *aci,double *bi,double *mi,double *Alphai, double *ai,double &pTc,double &pPc,EOS aEOS/*,TMemo *Memo1*/)
		{  //用于计算临界温度和压力,通过迭代法获得， --用于混合物
			double pTctemp=pTc; //
			double wc; //前后两次迭代的温度差绝对值
			double wcx=0.01; //判断收敛到结果的误差值
			int n=0;
			do
			{
				n++;
				b=0; a=0;  //赋初值为0
				for(int i=0;i<NCom;i++)
				{
					switch(aEOS)
					{
					case SRK:
						aci[i]=0.42747*R*R*Tci[i]*Tci[i]/pci[i];      //Danish,1998 P140  4.22
						bi[i]=0.08664*R*Tci[i]/pci[i];            //Danish,1998 P140  4.22
						mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
						Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
						ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
						break;
					case PR:
						aci[i]=0.457235*R*R*Tci[i]*Tci[i]/pci[i];    //Danish,1998 P141  4.27
						bi[i]=0.077796*R*Tci[i]/pci[i];          //Danish,1998 P141  4.27
						mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
						Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
						ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
						break;
					};
				}
				for(int i=0;i<NCom;i++)
				{    //混合规则  Mixture parameters
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
				//Memo1->Lines->Add("临界温度pTctemp="+FloatToStr(pTctemp));
				//Memo1->Lines->Add("临界温度pTc="+FloatToStr(pTc));
				//if(n==100) ShowMessage("停");
				pTctemp=pTc;
			}while(wc>wcx);
		}
		double NewtonIterationFornv(int NCom,double *z,double *K, double aPoint) //用牛顿迭代法求nv
		{
			double tempV; //函数值
			double tempVD;  //导数值
			double nv01,nv02; //返回值
			double wc;
			nv01=aPoint;
			do
			{
				tempV=0;
				tempVD=0;
				for(int i=0;i<NCom;i++)
					tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*nv01);    //获得Rachford-Rice方程值 Danesh 1998, (5.6)P169
				//ShowMessage("1.+(KK[0]-1.0)*nv01="+FloatToStr(1.+(K[0]-1.0)*nv01));
				//ShowMessage("1.+(KK[1]-1.0)*nv01="+FloatToStr(1.+(K[1]-1.0)*nv01));

				for(int i=0;i<NCom;i++)
					tempVD+=-z[i]*(K[i]-1.)*(K[i]-1.)/pow(1.+(K[i]-1.0)*nv01,2.);  //获得Rachford-Rice方程导数值
				nv02=nv01-tempV/tempVD;
				wc=fabs(nv02-nv01);
				nv01=nv02;
			}while(wc>1.0e-10);
			return nv02;
		}
		


		double rrand()
		{  // 产生0-1间随机数
			double l;
			l=(std::rand()%1000)/1000.0;
			return(l);
		}

		double GetRand()         //产生-1，+1间的随机数，来自网络
		{
			return 2.0*std::rand()/double(RAND_MAX)-1.0;
		} /**/
		
		double GetRand0_1() {return std::rand()/double(RAND_MAX);}  //产生0-1间的随机数
		
		double RandomRange( double b)
		{ //产生-b,b间的随机数
			return GetRand()*b;
		}
				
		struct POS
		{
			int x,y; //记录三维数组的头两维

			POS()
			{
				x = 0;
				y = 0;
			}
		};

		struct Poro_Perm  //纪录孔隙度和渗透率关系的数据对
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
			//以下为EasyRo模型参数 ,也可用于定义BasinRo模型参数或其它类似的参数
			int NN;//平行反应活化能数 ，（如果化学计量系数和活化能通过表格给出，则NN可以根据表格中的行数给出 ）
			double *f;//是化学计量系数（Stoichiometric Factor）
			double *E;//活化能（Activation Energy）（Kcal/mole）
			double A;//频率因子 S^-1
			double Roo;//EasyRo模型在地表初始时刻的Ro值  Roo=exp(-1.6);
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
				
				//对结构体赋值
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
				
				//从另一个结构中拷贝一份参数
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
			//以下为EasyRo模型参数 ,也可用于定义BasinRo模型参数或其它类似的参数
			double f0;//是单一的化学计量系数（Stoichiometric Factor），初始时刻相当于EasyRo中的初始的fi之和
			double f;//同上，只不过在代入函数的过程中数值会变化
			double aerf,beita; //Simple Ro方法中活化能E和lnRo间的关系常数  (E=αlnRo+β)
			double A;//频率因子 S^-1
			double Roo;//Ro=exp(-1.6); //地层在初始时刻的Ro值，SimpleRo使用EasyRo同样的值
			
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
			{   //对结构体赋值
				f0=f0SimpleRo; f=fSimpleRo; aerf=aerfSimpleRo;beita=beitaSimpleRo; A=ASimpleRo; Roo=RooSimpleRo;
			}
			
			void CopyFrom(ParaOfSimpleRo *aPara)
			{   
				if (!aPara)
				{
					return;
				}
				
				//从另一个结构中拷贝一份参数
				f0=aPara->f0;
				f=aPara->f;
				aerf=aPara->aerf;
				beita=aPara->beita;
				A= aPara->A;
				Roo=aPara->Roo ;
			}
		};
		
		struct DR
		{ //干酪根降解率结构体 ，用于干酪根降解率与Ro关系
		  int NKerogen; //干酪根类型数
		  double *Ratio; //各种干酪根所占的比例
		  int NI; //对应于I型干酪根降解率数值的个数
		  int NIIA; //对应于IIA型干酪根降解率数值的个数
		  int NIIB; //对应于IIB型干酪根降解率数值的个数
		  int NIII; //对应于III型干酪根降解率数值的个数
		  int NGDR; //对应于气降解含量的数值的个数
		  double * DRI;  //DegradationRate Of Type I Kerogen
		  double *RoI;  //对应于DegradationRate Of Type I Kerogen的Ro
		  double * DRIIA;  //DegradationRate Of Type IIA Kerogen
		  double *RoIIA;  //对应于DegradationRate Of Type IIA Kerogen的Ro
		  double * DRIIB;  //DegradationRate Of Type IIB Kerogen
		  double *RoIIB;  //对应于DegradationRate Of Type IIB Kerogen的Ro
		  double * DRIII;  //DegradationRate Of Type III Kerogen
		  double *RoIII;  //对应于DegradationRate Of Type III Kerogen的Ro
		  double *GDR; //气降解含量
		  double *RoGDR; //气降解含量对应的Ro%值
		  double COG;//为油气转化率，一般取值0.96m3/kg ，暂时没用这个转化率，气量也用kg表示
		  

		  DR()
		  {
			  Init();
		  }

		  void Init()
		  {
			NKerogen = 0; //干酪根类型数
			Ratio = 0; //各种干酪根所占的比例

			NI = 0; //对应于I型干酪根降解率数值的个数
			NIIA = 0; //对应于IIA型干酪根降解率数值的个数
			NIIB = 0; //对应于IIB型干酪根降解率数值的个数
			NIII = 0; //对应于III型干酪根降解率数值的个数
			NGDR = 0; //对应于气降解含量的数值的个数

			DRI = 0;  //DegradationRate Of Type I Kerogen
			RoI = 0;  //对应于DegradationRate Of Type I Kerogen的Ro

			DRIIA = 0;  //DegradationRate Of Type IIA Kerogen
			RoIIA = 0;  //对应于DegradationRate Of Type IIA Kerogen的Ro

			DRIIB = 0;  //DegradationRate Of Type IIB Kerogen
			RoIIB = 0;  //对应于DegradationRate Of Type IIB Kerogen的Ro

			DRIII = 0;  //DegradationRate Of Type III Kerogen
			RoIII = 0;  //对应于DegradationRate Of Type III Kerogen的Ro

			GDR = 0; //气降解含量
			RoGDR = 0; //气降解含量对应的Ro%值

			COG = 0; //为油气转化率，一般取值0.96m3/kg ，暂时没用这个转化率，气量也用kg表示

			/////////////////////////////////////////output////////////////////////////////
			for (int idx = RO_TTI; idx <= RO_Basin; idx++)
			{
				//四种不同类型的干酪根单位质量（kg)有机碳降解量
				HCFromDRI[idx] = 0;
				HCFromDRIIA[idx] = 0;
				HCFromDRIIB[idx] = 0;
				HCFromDRIII[idx] = 0; 

				//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
				InitTOCI[idx] = 0;
				InitTOCIIA[idx] = 0;
				InitTOCIIB[idx] = 0;
				InitTOCIII[idx] = 0; 

				//各组分的原始有机碳在地层段的原始有机碳质量kg
				MassInitTOCI[idx] = 0;
				MassInitTOCIIA[idx] = 0;
				MassInitTOCIIB[idx] = 0;
				MassInitTOCIII[idx] = 0; 

				//天然气比率,相当于文档中的Pg
				GasRatio[idx] = 0;

				//每单位（kg）原始有机碳质量的生烃量
				HCGIPerUnitInitTOC_I[idx] = 0;
				HCGIPerUnitInitTOC_IIA[idx] = 0;
				HCGIPerUnitInitTOC_IIB[idx] = 0;
				HCGIPerUnitInitTOC_III[idx] = 0; 

				//每单位（kg）原始有机碳质量的生油量
				OGIPerUnitInitTOC_I[idx] = 0;
				OGIPerUnitInitTOC_IIA[idx] = 0;
				OGIPerUnitInitTOC_IIB[idx] = 0;
				OGIPerUnitInitTOC_III[idx] = 0; 

				//每单位（kg）原始有机碳质量的生气量
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
		  double HCFromDRI[4],HCFromDRIIA[4], HCFromDRIIB[4], HCFromDRIII[4]; //四种不同类型的干酪根单位质量（kg)有机碳降解量
		  double InitTOCI[4],InitTOCIIA[4],InitTOCIIB[4],InitTOCIII[4]; //每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
		  double MassInitTOCI[4],MassInitTOCIIA[4],MassInitTOCIIB[4],MassInitTOCIII[4]; //各组分的原始有机碳在地层段的原始有机碳质量kg
		  double GasRatio[4]; //天然气比率,相当于文档中的Pg
		  double HCGIPerUnitInitTOC_I[4], HCGIPerUnitInitTOC_IIA[4],HCGIPerUnitInitTOC_IIB[4],HCGIPerUnitInitTOC_III[4]; //每单位（kg）原始有机碳质量的生烃量
		  double OGIPerUnitInitTOC_I[4],OGIPerUnitInitTOC_IIA[4],OGIPerUnitInitTOC_IIB[4],OGIPerUnitInitTOC_III[4];  //每单位（kg）原始有机碳质量的生油量
		  double GGIPerUnitInitTOC_I[4],GGIPerUnitInitTOC_IIA[4],GGIPerUnitInitTOC_IIB[4],GGIPerUnitInitTOC_III[4];  //每单位（kg）原始有机碳质量的生气量
		  double LinerInterpolate(double t,double t0,double p0,double t1,double p1){return p1-(p1-p0)*(t1-t)/(t1-t0);}//线性插值函数
		 
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
				   GGIPerUnitInitTOC_IIA[idx]=HCGIPerUnitInitTOC_IIA[idx]*GasRatio[idx];    //这里的气量也用kg表示，不再乘以COG转化为立方米
				   GGIPerUnitInitTOC_IIB[idx]=HCGIPerUnitInitTOC_IIB[idx]*GasRatio[idx];
				   GGIPerUnitInitTOC_III[idx]=HCGIPerUnitInitTOC_III[idx]*GasRatio[idx];
			   }
		   }

		};

		 struct ParaLLNL
		 {
			   //以下为Lawrence Livermore National Laboratories (LLNL)干酪根反映动力学参数
			  double W; //油气换算为有机碳的比例  =0.85
			  int NKerogenType;   //干酪根类型数
			  double *RatioKerogenType; // 干酪根比例
			  double *InitTOC;//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
			  double *MassOfInitTOC; //每种干酪根的原始TOC质量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
			  
			  //2017/10/13: new added variables below
			  double MassOfInitTOCTotal; //干酪根原始有机碳总的质量

			  double *MKer; //每种干酪根的有机碳质量，演化过程中变化的量（残余干酪根量，总质量）；新加入20170908
			  double MKerTotal; //总的干酪根有机碳质量，（不包括油裂解的焦炭量） ；新加入20170908

			  //以下为I型干酪根的动力学参数
			  double HI_LLNL_I; //I型干酪根的氢指数
			  double KSF_LLNL_I;//   Kerogen Start Fraction  LLNL的I型干酪根 反应物干酪根初始量
			  double KToOilF_LLNL_I;// 干酪根生成油的比率
			  double KToGasF_LLNL_I; //  干酪根生成气的比率
			  double OSF_LLNL_I;  // Oil Strat Fraction 反应物（生成物）起始含量;;这里指初始油中有机碳在总有机碳中的比例
			  double OToGasF_LLNL_I; //油生成气的比例
			  double OToResidueF_LLNL_I; //油生成残余物的比例

			  int N_LLNL_I_KToOil;//LLNL的I型干酪根生油的平行反应活化能数
			  double *fLLNL_I_KToOil;//是化学计量系数（Stoichiometric Factor）
			  double *ELLNL_I_KToOil;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_I_KToOil; //Frequency factor  ，即A

			  int N_LLNL_I_KToGas;//LLNL的I型干酪根生气的平行反应活化能数
			  double *fLLNL_I_KToGas;//是化学计量系数（Stoichiometric Factor）
			  double *ELLNL_I_KToGas;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_I_KToGas; //Frequency factor,频率因子

			  int N_LLNL_I_OilToGas;//LLNL的I型干酪根油生成气的反应活化能数
			  double *fLLNL_I_OilToGas;//是化学计量系数（Stoichiometric Factor）
			  double *fLLNL_I_OilToGasBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			  double *ELLNL_I_OilToGas;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_I_OilToGas; //Frequency factor

			  int N_LLNL_I_OilToResidue;//LLNL的I型干酪根油生成残余物的反应活化能数
			  double *fLLNL_I_OilToResidue;//是化学计量系数（Stoichiometric Factor）
			  double *fLLNL_I_OilToResidueBak;  //备份的计量系数，永远纪录最初始的化学计量系数值
			  double *ELLNL_I_OilToResidue;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_I_OilToResidue; //Frequency factor
			//以下为LLNL II型干酪根参数
			  double HI_LLNL_II; //II型干酪根的氢指数
			  double KSF_LLNL_II;//   Kerogen Start Fraction  LLNL的II型干酪根 反应物干酪根初始量
			  double KToOilF_LLNL_II;// 干酪根生成油的比率
			  double KToGasF_LLNL_II; //  干酪根生成气的比率
			  double OSF_LLNL_II;  // Oil Strat Fraction 反应物（生成物）起始含量
			  double OToGasF_LLNL_II; //油生成气的比例
			  double OToResidueF_LLNL_II; //油生成残余物的比例

			  int N_LLNL_II_KToOil;//LLNL的II型干酪根生油的平行反应活化能数
			  double *fLLNL_II_KToOil;//是化学计量系数（Stoichiometric Factor）
			  double *ELLNL_II_KToOil;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_II_KToOil; //Frequency factor

			  int N_LLNL_II_KToGas;//LLNL的II型干酪根生气的平行反应活化能数
			  double *fLLNL_II_KToGas;//是化学计量系数（Stoichiometric Factor）
			  double *ELLNL_II_KToGas;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_II_KToGas; //Frequency factor

			  int N_LLNL_II_OilToGas;//LLNL的II型干酪根油生成气的反应活化能数
			  double *fLLNL_II_OilToGas;//是化学计量系数（Stoichiometric Factor）
			  double *fLLNL_II_OilToGasBak;   //备份的计量系数，永远纪录最初始的化学计量系数值
			  double *ELLNL_II_OilToGas;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_II_OilToGas; //Frequency factor

			  int N_LLNL_II_OilToResidue;//LLNL的II型干酪根油生成残余物的反应活化能数
			  double *fLLNL_II_OilToResidue;//是化学计量系数（Stoichiometric Factor）
			  double *fLLNL_II_OilToResidueBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			  double *ELLNL_II_OilToResidue;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_II_OilToResidue; //Frequency factor

			//以下为LLNL III型干酪根参数
			  double HI_LLNL_III; //III型干酪根的氢指数
			  double KSF_LLNL_III;//   Kerogen Start Fraction  LLNL的III型干酪根 反应物干酪根初始量
			  double KToOilF_LLNL_III;// 干酪根生成油的比率
			  double KToGasF_LLNL_III; //  干酪根生成气的比率
			  double OSF_LLNL_III;  // Oil Strat Fraction 反应物（生成物）起始含量
			  double OToGasF_LLNL_III; //油生成气的比例
			  double OToResidueF_LLNL_III; //油生成残余物的比例

			  int N_LLNL_III_KToOil;//LLNL的III型干酪根生油的平行反应活化能数
			  double *fLLNL_III_KToOil;//是化学计量系数（Stoichiometric Factor）
			  double *ELLNL_III_KToOil;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_III_KToOil; //Frequency factor

			  int N_LLNL_III_KToGas;//LLNL的III型干酪根生气的平行反应活化能数
			  double *fLLNL_III_KToGas;//是化学计量系数（Stoichiometric Factor）
			  double *ELLNL_III_KToGas;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_III_KToGas; //Frequency factor

			  int N_LLNL_III_OilToGas;//LLNL的III型干酪根油生成气的反应活化能数
			  double *fLLNL_III_OilToGas;//是化学计量系数（Stoichiometric Factor）
			  double *fLLNL_III_OilToGasBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			  double *ELLNL_III_OilToGas;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_III_OilToGas; //Frequency factor

			  int N_LLNL_III_OilToResidue;//LLNL的III型干酪根油生成残余物的反应活化能数
			  double *fLLNL_III_OilToResidue;//是化学计量系数（Stoichiometric Factor）
			  double *fLLNL_III_OilToResidueBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			  double *ELLNL_III_OilToResidue;//活化能（Activation Energy）（Kcal/mole）
			  double *FFLLNL_III_OilToResidue; //Frequency factor

			  ParaLLNL()
			  {
				  Init();
			  }

			  void Init()
			  {
				  W = 0.85;
				  NKerogenType = 0;   //干酪根类型数
				  RatioKerogenType = 0; // 干酪根比例
				  InitTOC = 0;//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
				  MassOfInitTOC = 0; //每种干酪根的原始TOC质量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值

				  //以下为I型干酪根的动力学参数
				  HI_LLNL_I = 0.; //I型干酪根的氢指数
				  KSF_LLNL_I = 0.;//   Kerogen Start Fraction  LLNL的I型干酪根 反应物干酪根初始量
				  KToOilF_LLNL_I = 0.;// 干酪根生成油的比率
				  KToGasF_LLNL_I = 0.; //  干酪根生成气的比率
				  OSF_LLNL_I = 0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				  OToGasF_LLNL_I = 0.; //油生成气的比例
				  OToResidueF_LLNL_I = 0.; //油生成残余物的比例

				  N_LLNL_I_KToOil = 0;//LLNL的I型干酪根生油的平行反应活化能数
				  fLLNL_I_KToOil = 0;//是化学计量系数（Stoichiometric Factor）
				  ELLNL_I_KToOil = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_I_KToOil = 0; //Frequency factor  ，即A

				  N_LLNL_I_KToGas = 0;//LLNL的I型干酪根生气的平行反应活化能数
				  fLLNL_I_KToGas = 0;//是化学计量系数（Stoichiometric Factor）
				  ELLNL_I_KToGas = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_I_KToGas = 0; //Frequency factor,频率因子

				  N_LLNL_I_OilToGas = 0;//LLNL的I型干酪根油生成气的反应活化能数
				  fLLNL_I_OilToGas = 0;//是化学计量系数（Stoichiometric Factor）
				  fLLNL_I_OilToGasBak = 0; //备份的计量系数，永远纪录最初始的化学计量系数值
				  ELLNL_I_OilToGas = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_I_OilToGas = 0; //Frequency factor

				  N_LLNL_I_OilToResidue = 0;//LLNL的I型干酪根油生成残余物的反应活化能数
				  fLLNL_I_OilToResidue = 0;//是化学计量系数（Stoichiometric Factor）
				  fLLNL_I_OilToResidueBak = 0;  //备份的计量系数，永远纪录最初始的化学计量系数值
				  ELLNL_I_OilToResidue = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_I_OilToResidue = 0; //Frequency factor

				  //以下为LLNL II型干酪根参数
				  HI_LLNL_II = 0.; //II型干酪根的氢指数
				  KSF_LLNL_II = 0.;//   Kerogen Start Fraction  LLNL的II型干酪根 反应物干酪根初始量
				  KToOilF_LLNL_II = 0.;// 干酪根生成油的比率
				  KToGasF_LLNL_II = 0.; //  干酪根生成气的比率
				  OSF_LLNL_II = 0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				  OToGasF_LLNL_II = 0.; //油生成气的比例
				  OToResidueF_LLNL_II = 0.; //油生成残余物的比例

				  N_LLNL_II_KToOil = 0;//LLNL的II型干酪根生油的平行反应活化能数
				  fLLNL_II_KToOil = 0;//是化学计量系数（Stoichiometric Factor）
				  ELLNL_II_KToOil = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_II_KToOil = 0; //Frequency factor

				  N_LLNL_II_KToGas = 0;//LLNL的II型干酪根生气的平行反应活化能数
				  fLLNL_II_KToGas = 0;//是化学计量系数（Stoichiometric Factor）
				  ELLNL_II_KToGas = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_II_KToGas = 0; //Frequency factor

				  N_LLNL_II_OilToGas = 0;//LLNL的II型干酪根油生成气的反应活化能数
				  fLLNL_II_OilToGas = 0;//是化学计量系数（Stoichiometric Factor）
				  fLLNL_II_OilToGasBak = 0;   //备份的计量系数，永远纪录最初始的化学计量系数值
				  ELLNL_II_OilToGas = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_II_OilToGas = 0; //Frequency factor

				  N_LLNL_II_OilToResidue = 0;//LLNL的II型干酪根油生成残余物的反应活化能数
				  fLLNL_II_OilToResidue = 0;//是化学计量系数（Stoichiometric Factor）
				  fLLNL_II_OilToResidueBak = 0; //备份的计量系数，永远纪录最初始的化学计量系数值
				  ELLNL_II_OilToResidue = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_II_OilToResidue = 0; //Frequency factor

				  //以下为LLNL III型干酪根参数
				  HI_LLNL_III = 0.; //III型干酪根的氢指数
				  KSF_LLNL_III = 0.;//   Kerogen Start Fraction  LLNL的III型干酪根 反应物干酪根初始量
				  KToOilF_LLNL_III = 0.;// 干酪根生成油的比率
				  KToGasF_LLNL_III = 0.; //  干酪根生成气的比率
				  OSF_LLNL_III = 0.;  // Oil Strat Fraction 反应物（生成物）起始含量
				  OToGasF_LLNL_III = 0.; //油生成气的比例
				  OToResidueF_LLNL_III = 0.; //油生成残余物的比例

				  N_LLNL_III_KToOil = 0;//LLNL的III型干酪根生油的平行反应活化能数
				  fLLNL_III_KToOil = 0;//是化学计量系数（Stoichiometric Factor）
				  ELLNL_III_KToOil = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_III_KToOil = 0; //Frequency factor

				  N_LLNL_III_KToGas = 0;//LLNL的III型干酪根生气的平行反应活化能数
				  fLLNL_III_KToGas = 0;//是化学计量系数（Stoichiometric Factor）
				  ELLNL_III_KToGas = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_III_KToGas = 0; //Frequency factor

				  N_LLNL_III_OilToGas = 0;//LLNL的III型干酪根油生成气的反应活化能数
				  fLLNL_III_OilToGas = 0;//是化学计量系数（Stoichiometric Factor）
				  fLLNL_III_OilToGasBak = 0; //备份的计量系数，永远纪录最初始的化学计量系数值
				  ELLNL_III_OilToGas = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_III_OilToGas = 0; //Frequency factor

				  N_LLNL_III_OilToResidue = 0;//LLNL的III型干酪根油生成残余物的反应活化能数
				  fLLNL_III_OilToResidue = 0;//是化学计量系数（Stoichiometric Factor）
				  fLLNL_III_OilToResidueBak = 0; //备份的计量系数，永远纪录最初始的化学计量系数值
				  ELLNL_III_OilToResidue = 0;//活化能（Activation Energy）（Kcal/mole）
				  FFLLNL_III_OilToResidue = 0; //Frequency factor

				  //分别是I、II、III型干酪根由于生油而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				  wBIw0_I_KToOil = 0.;
				  wBIw0_II_KToOil = 0.;
				  wBIw0_III_KToOil = 0.;

				  //分别是I、II、III型干酪根由于生气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				  wBIw0_I_KToGas = 0.;
				  wBIw0_II_KToGas = 0.;
				  wBIw0_III_KToGas = 0.;

				  //分别是I、II、III型干酪根相关油裂解成气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				  wBIw0_I_OilToGas = 0.;
				  wBIw0_II_OilToGas = 0.;
				  wBIw0_III_OilToGas = 0.; 

				  //分别是I、II、III型干酪根相关油裂解成残余物而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
				  wBIw0_I_OilToResidue = 0.;
				  wBIw0_II_OilToResidue = 0.;
				  wBIw0_III_OilToResidue = 0.; 

				  //分别是I、II、III型干酪根 总的剩余化学计量系数，原始为1。通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到。
				  wBIw0_I_K = 0.;
				  wBIw0_II_K = 0.;
				  wBIw0_III_K = 0.; 

				  //分别是I、II、III型InitTOC在这一时间段的生油量
				  OilPerInitTOC_I = 0.;
				  OilPerInitTOC_II = 0.;
				  OilPerInitTOC_III = 0.; 

				  //分别是I、II、III型InitTOC在这一时间段的生气量
				  GasPerInitTOC_I = 0.;
				  GasPerInitTOC_II = 0.;
				  GasPerInitTOC_III = 0.;; 

				  //每种类型干酪根有机碳剩余量
				  TOCRemained_I = 0.;
				  TOCRemained_II = 0.;
				  TOCRemained_III = 0.;

				  //每种干酪根相关的油在这一时间段的裂解量
				  OilCracked_I = 0.;
				  OilCracked_II = 0.;
				  OilCracked_III = 0.; 

				  //每种干酪根相关的油在这一时间段的裂解成气量
				  GasCracked_I = 0.;
				  GasCracked_II = 0.;
				  GasCracked_III = 0.;

				  //每种干酪根相关的油在这一时间段的裂解成残余物量
				  ResidueCracked_I = 0.;
				  ResidueCracked_II = 0.;
				  ResidueCracked_III = 0.; 

				  //每种单位质量原始干酪根生油以及油裂解为气后存在的油
				  OilExisted_I = 0.;
				  OilExisted_II = 0.;
				  OilExisted_III = 0.;   

				  //每种单位质量原始干酪根生气以及油裂解的气
				  GasExisted_I = 0.;
				  GasExisted_II = 0.;
				  GasExisted_III = 0.;  

				  //每种单位质量原始干酪根相关的残余物量
				  ResidueExisted_I = 0.;
				  ResidueExisted_II = 0.;
				  ResidueExisted_III = 0.;  

				  //2017/10/13: new added variables below
				  MassOfInitTOCTotal = 0.;//干酪根原始有机碳总的质量
				  
				  MKer = 0; //每种干酪根的有机碳质量，演化过程中变化的量（残余干酪根量，总质量）；新加入20170908
				  MKerTotal = 0.; //总的干酪根有机碳质量，（不包括油裂解的焦炭量） ；新加入20170908

				  //油气的累积生成量，与存在量Exsited不同，是单位质量原始有机碳生油和生气量
				  OilGenerated_I = 0.;
				  OilGenerated_II = 0.;
				  OilGenerated_III = 0.;
				  GasGenerated_I = 0.;
				  GasGenerated_II = 0.;
				  GasGenerated_III = 0.;

				  //三种干酪跟单位质量原始有机碳累计的生油量和生气量
				  OilGenerated = 0.;
				  GasGenerated = 0.;

				   //每单位原始有机碳在该时间步的生油量和生气量
				  OilPerInitTOC = 0.;
				  GasPerInitTOC = 0.;

				  //源岩的油气转化率
				  TR = 0.; 

				  OilExisted = 0.; //指的是存在于源岩中的油组分
				  GasExisted = 0.;//指的是存在于源岩中的气组分
				  GasCracked = 0.;//指的是每一步油裂解的气量
				  GasCrackedAdded = 0.; //指每一步裂解气的累加量
				  ResidueCracked = 0.; // 指的是每一步油裂解的残余物量
				  ResidueCrackedAdded = 0.; // 指的是每一步油裂解的残余物的累加量
				  OilCracked = 0.;//每一步油的裂解量
				  OilCrackedAdded = 0.;//每一步油的裂解量的累加量

				  MKerReac = 0.; //源岩中可反应的干酪根量，以有机碳形式给出，单位：kg
				  MKerInert = 0.; //源岩中无效干酪根量 ，以有机碳形式给出，单位：kg
			  }

			  void Release()
			  {
				  DoRelease(RatioKerogenType); // 干酪根比例
				  DoRelease(InitTOC);//每种干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
				  DoRelease(MassOfInitTOC); //每种干酪根的原始TOC质量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
				 
				  DoRelease(fLLNL_I_KToOil);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(ELLNL_I_KToOil);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_I_KToOil); //Frequency factor  ，即A

				  DoRelease(fLLNL_I_KToGas);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(ELLNL_I_KToGas);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_I_KToGas); //Frequency factor,频率因子

				  DoRelease(fLLNL_I_OilToGas);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(fLLNL_I_OilToGasBak); //备份的计量系数，永远纪录最初始的化学计量系数值
				  DoRelease(ELLNL_I_OilToGas);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_I_OilToGas); //Frequency factor

				  DoRelease(fLLNL_I_OilToResidue);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(fLLNL_I_OilToResidueBak);  //备份的计量系数，永远纪录最初始的化学计量系数值
				  DoRelease(ELLNL_I_OilToResidue);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_I_OilToResidue); //Frequency factor
				 
				  DoRelease(fLLNL_II_KToOil);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(ELLNL_II_KToOil);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_II_KToOil); //Frequency factor

				  DoRelease(fLLNL_II_KToGas);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(ELLNL_II_KToGas);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_II_KToGas); //Frequency factor

				  DoRelease(fLLNL_II_OilToGas);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(fLLNL_II_OilToGasBak);   //备份的计量系数，永远纪录最初始的化学计量系数值
				  DoRelease(ELLNL_II_OilToGas);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_II_OilToGas); //Frequency factor

				  DoRelease(fLLNL_II_OilToResidue);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(fLLNL_II_OilToResidueBak); //备份的计量系数，永远纪录最初始的化学计量系数值
				  DoRelease(ELLNL_II_OilToResidue);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_II_OilToResidue); //Frequency factor

				 
				  DoRelease(fLLNL_III_KToOil);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(ELLNL_III_KToOil);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_III_KToOil); //Frequency factor

				  DoRelease(fLLNL_III_KToGas);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(ELLNL_III_KToGas);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_III_KToGas); //Frequency factor

				  DoRelease(fLLNL_III_OilToGas);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(fLLNL_III_OilToGasBak); //备份的计量系数，永远纪录最初始的化学计量系数值
				  DoRelease(ELLNL_III_OilToGas);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_III_OilToGas); //Frequency factor

				  DoRelease(fLLNL_III_OilToResidue);//是化学计量系数（Stoichiometric Factor）
				  DoRelease(fLLNL_III_OilToResidueBak); //备份的计量系数，永远纪录最初始的化学计量系数值
				  DoRelease(ELLNL_III_OilToResidue);//活化能（Activation Energy）（Kcal/mole）
				  DoRelease(FFLLNL_III_OilToResidue); //Frequency factor

				  //2017/10/13: new added variables below
				  DoRelease(MKer);//每种干酪根的有机碳质量，演化过程中变化的量（残余干酪根量，总质量）
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
				   
				   //从另一个结构中拷贝一份参数
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

			  double wBIw0_I_KToOil,  wBIw0_II_KToOil,  wBIw0_III_KToOil;//分别是I、II、III型干酪根由于生油而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
			  double wBIw0_I_KToGas,  wBIw0_II_KToGas,  wBIw0_III_KToGas;//分别是I、II、III型干酪根由于生气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
			  double wBIw0_I_OilToGas,  wBIw0_II_OilToGas,  wBIw0_III_OilToGas; //分别是I、II、III型干酪根相关油裂解成气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
			  double wBIw0_I_OilToResidue,  wBIw0_II_OilToResidue,  wBIw0_III_OilToResidue; //分别是I、II、III型干酪根相关油裂解成残余物而导致的总的剩余化学计量系数，原始的总的化学计量系数为1

			  double wBIw0_I_K,wBIw0_II_K, wBIw0_III_K; //分别是I、II、III型干酪根 总的剩余化学计量系数，原始为1。通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到。
			  double OilPerInitTOC_I, OilPerInitTOC_II, OilPerInitTOC_III; //分别是I、II、III型InitTOC在这一时间段的生油量
			  double GasPerInitTOC_I, GasPerInitTOC_II, GasPerInitTOC_III; //分别是I、II、III型InitTOC在这一时间段的生气量
			  double TOCRemained_I, TOCRemained_II, TOCRemained_III; //每种类型干酪根有机碳剩余量 。是指单位质量原始干酪跟的残余量
			  double OilCracked_I,OilCracked_II,OilCracked_III; //每种干酪根相关的油在这一时间段的裂解量
			  double GasCracked_I,GasCracked_II,GasCracked_III; //每种干酪根相关的油在这一时间段的裂解成气量
			  double ResidueCracked_I,ResidueCracked_II,ResidueCracked_III; //每种干酪根相关的油在这一时间段的裂解成残余物量
			  double OilExisted_I, OilExisted_II, OilExisted_III;   //每种单位质量原始干酪根生油以及油裂解为气后存在的油
			  double GasExisted_I, GasExisted_II, GasExisted_III;   //每种单位质量原始干酪根生气以及油裂解的气
			  double ResidueExisted_I, ResidueExisted_II, ResidueExisted_III;   //每种单位质量原始干酪根相关的残余物量
			  
			  void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,double *fLLNL,double *FFLLNL, double *ELLNL,double &wBIw0)
				{  //分别是上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma），
				   // 平行反应个数N_LLNL，化学计量系数fLLNL,频率因子FFLLNL，活化能ELLNL,总的剩余化学计量系数wBIw0
				 wBIw0=0;
				 double R=0.001986;//气体常数 ，单位 Kcal/(mol*K)
				 //假设在t和tLast间温度T与t呈线性关系，即在T和TLast间线性变化：T=a*tt+b   ,tt是在t和tLast间变化的时间
				 double a,b; // 线性变化的系数
				 a=(T-TLast)/(t-tLast);b=T-a*t;
				 //对于tLast和t之间采用数值积分方法，将期间等分为N个等分，因此Δt=(t-tLast)/N
				 int N=int(fabs(T-TLast)/0.5+1); //这样计算是保证在每个计算步下温度变化不超过0.5℃，后面加1是保证至少有1步来执行。
				 double Delta_t=(t-tLast)/double(N); //Delta_t在这里是有正负概念的
				 double tt1=tLast,tt2,ttM; // 分别是时间段的下端点值、上端点值和中间值,初始的tt1值设在最底端
				 double temp=0;
				 double *wiBIw0i;  //wi/w0i ,含义见EasyRo推导中的公式（8）
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
				   fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //计算这一时间段的化学计量系数
				   wBIw0+=fLLNL[i];  // wBIw0为总的化学计量系数剩余值
				   tt1=tLast; // 算下一个对应的活化能的wiBIw0i[i]需要将初始时间重置
				   temp=0;    //temp重新归零
				  }

				 //release
				 delete wiBIw0i;
				}

			  //2017/10/13: new added variables
			  double OilGenerated_I,OilGenerated_II,OilGenerated_III,GasGenerated_I,GasGenerated_II,GasGenerated_III;//油气的累积生成量，与存在量Exsited不同，是单位质量原始有机碳生油和生气量
			  double OilGenerated,GasGenerated; //三种干酪跟单位质量原始有机碳累计的生油量和生气量
			  double OilPerInitTOC, GasPerInitTOC; //每单位原始有机碳在该时间步的生油量和生气量
			  double TR; //源岩的油气转化率

			  void Reactions(double TLast, double tLast, double T, double t)
			  {  //针对时间上第一个地层段
				  // 各干酪根组分、油、气量的变化，没有包括裂解部分
				  // 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				  //aParaLLNL 为上一个时间段的参数结构
				  //都是基于单位质量（kg）原始有机碳计算的
				  // 计算原理来自PetroMod；参数来源于BasinMod
				  TLast+=273;T+=273;   //转化为开氏温度
				  tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				  t=t*1000000*365*24*3600; //百万年转化为秒
				  //以下为I型干酪根热解
				  double InitwBIw0_I_KToOil=0,InitwBIw0_I_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
				  for(int i=0;i<N_LLNL_I_KToOil;i++)InitwBIw0_I_KToOil+=fLLNL_I_KToOil[i]; for(int i=0;i<N_LLNL_I_KToGas;i++)InitwBIw0_I_KToGas+=fLLNL_I_KToGas[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil,FFLLNL_I_KToOil,ELLNL_I_KToOil,wBIw0_I_KToOil);  // I型干酪根成油热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas,FFLLNL_I_KToGas,ELLNL_I_KToGas,wBIw0_I_KToGas);  // I型干酪根成气热解
				  OilPerInitTOC_I=HI_LLNL_I*KToOilF_LLNL_I*(InitwBIw0_I_KToOil-wBIw0_I_KToOil);  // *KSF_LLNL_I
				  GasPerInitTOC_I=HI_LLNL_I*KToGasF_LLNL_I*(InitwBIw0_I_KToGas-wBIw0_I_KToGas);  //*KSF_LLNL_I
				  OilGenerated_I=OilPerInitTOC_I; //
			      GasGenerated_I=GasPerInitTOC_I; //
				  TOCRemained_I=1.-W*OilPerInitTOC_I-W*GasPerInitTOC_I;   //初始时刻原始有机碳为1
				  
				  //以下为II型干酪根热解
				  double InitwBIw0_II_KToOil=0,InitwBIw0_II_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
				  for(int i=0;i<N_LLNL_II_KToOil;i++)InitwBIw0_II_KToOil+=fLLNL_II_KToOil[i]; for(int i=0;i<N_LLNL_II_KToGas;i++)InitwBIw0_II_KToGas+=fLLNL_II_KToGas[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil,FFLLNL_II_KToOil,ELLNL_II_KToOil,wBIw0_II_KToOil);  // II型干酪根成油热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas,FFLLNL_II_KToGas,ELLNL_II_KToGas,wBIw0_II_KToGas);  // II型干酪根成气热解
				  OilPerInitTOC_II=HI_LLNL_II*KToOilF_LLNL_II*(InitwBIw0_II_KToOil-wBIw0_II_KToOil); // *KSF_LLNL_II
                  GasPerInitTOC_II=HI_LLNL_II*KToGasF_LLNL_II*(InitwBIw0_II_KToGas-wBIw0_II_KToGas);  //*KSF_LLNL_II
                  OilGenerated_II=OilPerInitTOC_II; //
                  GasGenerated_II=GasPerInitTOC_II; //
                  TOCRemained_II=1.-W*OilPerInitTOC_II-W*GasPerInitTOC_II;   //初始时刻原始有机碳为1
				  
				  //以下为III型干酪根热解
				  double InitwBIw0_III_KToOil=0,InitwBIw0_III_KToGas=0;  //初始时刻的各干酪根组分（化学计量系数）之和
				  for(int i=0;i<N_LLNL_III_KToOil;i++)InitwBIw0_III_KToOil+=fLLNL_III_KToOil[i]; for(int i=0;i<N_LLNL_III_KToGas;i++)InitwBIw0_III_KToGas+=fLLNL_III_KToGas[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil,FFLLNL_III_KToOil,ELLNL_III_KToOil,wBIw0_III_KToOil);  // III型干酪根成油热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas,FFLLNL_III_KToGas,ELLNL_III_KToGas,wBIw0_III_KToGas);  // III型干酪根成气热解
				  OilPerInitTOC_III=HI_LLNL_III*KToOilF_LLNL_III*(InitwBIw0_III_KToOil-wBIw0_III_KToOil); // *KSF_LLNL_III
                  GasPerInitTOC_III=HI_LLNL_III*KToGasF_LLNL_III*(InitwBIw0_III_KToGas-wBIw0_III_KToGas); //*KSF_LLNL_III
                  OilGenerated_III=OilPerInitTOC_III; //
                  GasGenerated_III=GasPerInitTOC_III; //
                  TOCRemained_III=1.-W*OilPerInitTOC_III-W*GasPerInitTOC_III;   //初始时刻原始有机碳为1

				  OilPerInitTOC=OilPerInitTOC_I*RatioKerogenType[0]+OilPerInitTOC_II*RatioKerogenType[1]+OilPerInitTOC_III*RatioKerogenType[2]; //每单位原始有机碳在该时间步的生油量
				  GasPerInitTOC=GasPerInitTOC_I*RatioKerogenType[0]+GasPerInitTOC_II*RatioKerogenType[1]+GasPerInitTOC_III*RatioKerogenType[2]; //每单位原始有机碳在该时间步的生气量
				  OilGenerated=OilGenerated_I*RatioKerogenType[0]+OilGenerated_II*RatioKerogenType[1]+OilGenerated_III*RatioKerogenType[2];  //三种干酪跟单位质量原始有机碳累计的生油量
				  GasGenerated=GasGenerated_I*RatioKerogenType[0]+GasGenerated_II*RatioKerogenType[1]+GasGenerated_III*RatioKerogenType[2];  //三种干酪跟单位质量原始有机碳累计的生气量

				  TR= (OilGenerated+GasGenerated)/ (HI_LLNL_I*RatioKerogenType[0]+HI_LLNL_II*RatioKerogenType[1]+HI_LLNL_III*RatioKerogenType[2]);
				  //油气转化率等于单位质量原始有机碳累积生成的油气量除以三种干酪根原始有机碳的氢指数乘以各自所占的比例
			  }
			  void Reactions(double TLast, double tLast, double T, double t,ParaLLNL *aParaLLNL)
			  {  // 各干酪根组分、油、气量的变化，没有包括裂解部分
				  // 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				  //aParaLLNL 为上一个时间段的参数结构
				  //都是基于单位质量（kg）原始有机碳计算的
				  // 计算原理来自PetroMod；参数来源于BasinMod
				  TLast+=273;T+=273;   //转化为开氏温度
				  tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				  t=t*1000000*365*24*3600; //百万年转化为秒
				  //以下为I型干酪根热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToOil,fLLNL_I_KToOil,FFLLNL_I_KToOil,ELLNL_I_KToOil,wBIw0_I_KToOil);  // I型干酪根成油热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_KToGas,fLLNL_I_KToGas,FFLLNL_I_KToGas,ELLNL_I_KToGas,wBIw0_I_KToGas);  // I型干酪根成气热解
				  OilPerInitTOC_I=HI_LLNL_I*KToOilF_LLNL_I*(aParaLLNL->wBIw0_I_KToOil-wBIw0_I_KToOil);  // *KSF_LLNL_I
                  GasPerInitTOC_I=HI_LLNL_I*KToGasF_LLNL_I*(aParaLLNL->wBIw0_I_KToGas-wBIw0_I_KToGas); //*KSF_LLNL_I
                  OilGenerated_I=aParaLLNL->OilGenerated_I+OilPerInitTOC_I; //
                  GasGenerated_I=aParaLLNL->GasGenerated_I+GasPerInitTOC_I; //
                  TOCRemained_I=aParaLLNL->TOCRemained_I-W*OilPerInitTOC_I-W*GasPerInitTOC_I;
				  
				  //以下为II型干酪根热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToOil,fLLNL_II_KToOil,FFLLNL_II_KToOil,ELLNL_II_KToOil,wBIw0_II_KToOil);  // II型干酪根成油热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_II_KToGas,fLLNL_II_KToGas,FFLLNL_II_KToGas,ELLNL_II_KToGas,wBIw0_II_KToGas);  // II型干酪根成气热解
				  OilPerInitTOC_II=HI_LLNL_II*KToOilF_LLNL_II*(aParaLLNL->wBIw0_II_KToOil-wBIw0_II_KToOil);  //*KSF_LLNL_II
                  GasPerInitTOC_II=HI_LLNL_II*KToGasF_LLNL_II*(aParaLLNL->wBIw0_II_KToGas-wBIw0_II_KToGas);   //*KSF_LLNL_II
                  OilGenerated_II=aParaLLNL->OilGenerated_II+OilPerInitTOC_II; //
                  GasGenerated_II=aParaLLNL->GasGenerated_II+GasPerInitTOC_II; //
                  TOCRemained_II=aParaLLNL->TOCRemained_II-W*OilPerInitTOC_II-W*GasPerInitTOC_II;
				  
				  //以下为III型干酪根热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToOil,fLLNL_III_KToOil,FFLLNL_III_KToOil,ELLNL_III_KToOil,wBIw0_III_KToOil);  // III型干酪根成油热解
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_III_KToGas,fLLNL_III_KToGas,FFLLNL_III_KToGas,ELLNL_III_KToGas,wBIw0_III_KToGas);  // III型干酪根成气热解
				  OilPerInitTOC_III=HI_LLNL_III*KToOilF_LLNL_III*(aParaLLNL->wBIw0_III_KToOil-wBIw0_III_KToOil);  //*KSF_LLNL_III
                  GasPerInitTOC_III=HI_LLNL_III*KToGasF_LLNL_III*(aParaLLNL->wBIw0_III_KToGas-wBIw0_III_KToGas);  //*KSF_LLNL_III
                  OilGenerated_III=aParaLLNL->OilGenerated_III+OilPerInitTOC_III; //
                  GasGenerated_III=aParaLLNL->GasGenerated_III+GasPerInitTOC_III; //
                  TOCRemained_III=aParaLLNL->TOCRemained_III-W*OilPerInitTOC_III-W*GasPerInitTOC_III;

				  OilPerInitTOC=OilPerInitTOC_I*RatioKerogenType[0]+OilPerInitTOC_II*RatioKerogenType[1]+OilPerInitTOC_III*RatioKerogenType[2];  //每单位原始有机碳在该时间步的生油量
				  GasPerInitTOC=GasPerInitTOC_I*RatioKerogenType[0]+GasPerInitTOC_II*RatioKerogenType[1]+GasPerInitTOC_III*RatioKerogenType[2];  //每单位原始有机碳在该时间步的生气量
				  OilGenerated=OilGenerated_I*RatioKerogenType[0]+OilGenerated_II*RatioKerogenType[1]+OilGenerated_III*RatioKerogenType[2];  //三种干酪跟单位质量原始有机碳累计的生油量
				  GasGenerated=GasGenerated_I*RatioKerogenType[0]+GasGenerated_II*RatioKerogenType[1]+GasGenerated_III*RatioKerogenType[2];  //三种干酪跟单位质量原始有机碳累计的生气量

				  TR= (OilGenerated+GasGenerated)/ (HI_LLNL_I*RatioKerogenType[0]+HI_LLNL_II*RatioKerogenType[1]+HI_LLNL_III*RatioKerogenType[2]);
				  //油气转化率等于单位质量原始有机碳累积生成的油气量除以三种干酪根原始有机碳的氢指数乘以各自所占的比例

			  }
			  double OilExisted; //指的是存在于源岩中的油组分
			  double GasExisted; //指的是存在于源岩中的气组分
			  double GasCracked;//指的是每一步油裂解的气量
			  double GasCrackedAdded; //指每一步裂解气的累加量
			  double ResidueCracked; // 指的是每一步油裂解的残余物量
			  double ResidueCrackedAdded; // 指的是每一步油裂解的残余物的累加量
			  double OilCracked;//每一步油的裂解量
			  double OilCrackedAdded;//每一步油的裂解量的累加量
			  void OilCrackToGas(double TLast, double tLast, double T, double t)
			  {    //由于各型干酪根生成的油裂解为气和残余物的化学动力学参数相同，这里采用I型干酪跟的参数作为总体的参数 ;这里采用显式解法，即裂解的为上一时间步存在的油
				  //以下为StrSeg中存在的油裂解为气和残余物的过程。由于是第一个时间步，初始时刻源岩中并没有油，因此实际上这些计算结果都为0。
				  TLast+=273;T+=273;   //转化为开氏温度
				  tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				  t=t*1000000*365*24*3600; //百万年转化为秒

				  double InitwBIw0_I_OilToGas=0,InitwBIw0_I_OilToResidue=0;  //初始时刻的各油裂解（化学计量系数）之和
				  for(int i=0;i<N_LLNL_I_OilToGas;i++)InitwBIw0_I_OilToGas+=fLLNL_I_OilToGas[i]; for(int i=0;i<N_LLNL_I_OilToResidue;i++)InitwBIw0_I_OilToResidue+=fLLNL_I_OilToResidue[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas,FFLLNL_I_OilToGas,ELLNL_I_OilToGas,wBIw0_I_OilToGas);  // I型干酪根相关油裂解为气
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue,FFLLNL_I_OilToResidue,ELLNL_I_OilToResidue,wBIw0_I_OilToResidue);  // I型干酪根相关油裂解为残余物
				  OilExisted=MassOfInitTOCTotal*(OSF_LLNL_I*RatioKerogenType[0]+OSF_LLNL_II*RatioKerogenType[1]+OSF_LLNL_III*RatioKerogenType[2])/W; //初始时刻的油的量（指的是单位原始干酪跟中的油的量）
				  GasExisted=0.;    //初始时刻的含气量为0
				  GasCracked=OilExisted*OToGasF_LLNL_I*(InitwBIw0_I_OilToGas-wBIw0_I_OilToGas);   //一般情况下，在初始时刻OilExisted=0 , OSF_LLNL_I 为反应物（即油）的初始含量也是0
				  ResidueCracked=OilExisted*OToResidueF_LLNL_I*(InitwBIw0_I_OilToResidue-wBIw0_I_OilToResidue);  //一般情况下，在初始时刻OilExisted=0 , OSF_LLNL_I 为反应物（即油）的初始含量也是0
				  OilCracked=GasCracked+ResidueCracked;
				  GasCrackedAdded=GasCracked;//由于是第一个时间步，因此气累积裂解量等于初始裂解量。
				  ResidueCrackedAdded=ResidueCracked;
				  OilCrackedAdded=OilCracked;
				  OilExisted =OilExisted +OilPerInitTOC*MassOfInitTOCTotal-OilCracked;  //该时间步的存在油量等于已经存在的油量加上这一时间步生成的油量减去该时间步裂解的减少油量
				  GasExisted = GasExisted +GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //该时间步的存在气量等于已经存在的气量加上这一时间步生成的气量加上该时间步裂解生成的气量
				  wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
				  for(int i=0;i<N_LLNL_I_OilToGas;i++) { wBIw0_I_OilToGas+=fLLNL_I_OilToGasBak[i]; }   //每次计算完要将该值归为起始值
				  for(int i=0;i<N_LLNL_I_OilToResidue;i++){ wBIw0_I_OilToResidue+=fLLNL_I_OilToResidueBak[i];}//每次计算完要将该值归为起始值
			  }
			  void OilCrackToGas(double TLast, double tLast, double T, double t,ParaLLNL *aParaLLNL)
			  {    //由于各型干酪跟生成的油裂解为气和残余物的化学动力学参数相同，这里采用I型干酪跟的参数作为总体的参数 ;这里采用显式解法，即裂解的为上一时间步存在的油
				  //以下为I型干酪根相关油裂解为气和残余物
				  //以下为I型干酪根相关油裂解为气和残余物
				  TLast+=273;T+=273;   //转化为开氏温度
				  tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				  t=t*1000000*365*24*3600; //百万年转化为秒

				  for(int i=0;i<N_LLNL_I_OilToGas;i++) fLLNL_I_OilToGas[i]=fLLNL_I_OilToGasBak[i];  //由于油每次裂解都有来自干酪根生成油的补充，即可用于裂解的油量更新，而对于LLNL模型，油裂解的活化能为单值，不存在不同活化能分布的油的混合问题，因此化学计量系数都赋为初始值,
				  for(int i=0;i<N_LLNL_I_OilToResidue;i++) fLLNL_I_OilToResidue[i]=fLLNL_I_OilToResidueBak[i];
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToGas,fLLNL_I_OilToGas,FFLLNL_I_OilToGas,ELLNL_I_OilToGas,wBIw0_I_OilToGas);  // 油裂解为气
				  FirstOrderReaction(TLast, tLast,T,t,N_LLNL_I_OilToResidue,fLLNL_I_OilToResidue,FFLLNL_I_OilToResidue,ELLNL_I_OilToResidue,wBIw0_I_OilToResidue);  // 油裂解为残余物
				  GasCracked=aParaLLNL->OilExisted*OToGasF_LLNL_I*(aParaLLNL->wBIw0_I_OilToGas-wBIw0_I_OilToGas);
				  ResidueCracked=aParaLLNL->OilExisted*OToResidueF_LLNL_I*(aParaLLNL->wBIw0_I_OilToResidue-wBIw0_I_OilToResidue);
				  OilCracked=GasCracked+ResidueCracked;
				  GasCrackedAdded=aParaLLNL->GasCrackedAdded+GasCracked;
				  ResidueCrackedAdded=aParaLLNL->ResidueCrackedAdded+ResidueCracked;
				  OilCrackedAdded=aParaLLNL->OilCrackedAdded+OilCracked;
				  OilExisted=aParaLLNL->OilExisted+OilPerInitTOC*MassOfInitTOCTotal-OilCracked;     //指的是每次油生成和裂解后可在源岩中存在的油量，还没有考虑吸附和孔隙中能够存在的量
				  GasExisted=aParaLLNL->GasExisted+GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //该时间步的存在气量等于已经存在的气量加上这一时间步干酪根生成的气量加上该时间步油裂解生成的气量
				  wBIw0_I_OilToGas=0,wBIw0_I_OilToResidue=0;
				  for(int i=0;i<N_LLNL_I_OilToGas;i++) { wBIw0_I_OilToGas+=fLLNL_I_OilToGasBak[i]; }   //每次计算完要将该值归为起始值
				  for(int i=0;i<N_LLNL_I_OilToResidue;i++){ wBIw0_I_OilToResidue+=fLLNL_I_OilToResidueBak[i];}//每次计算完要将该值归为起始值
			  }
			  double MKerReac; //源岩中可反应的干酪根量，以有机碳形式给出，单位：kg
			  double MKerInert; //源岩中无效干酪根量 ，以有机碳形式给出，单位：kg
			  void GetMKer()
			  {   //获得源岩中干酪根（有机碳）质量
				  MKerInert=(KSF_LLNL_I-HI_LLNL_I*W)*MassOfInitTOC[0]+(KSF_LLNL_II-HI_LLNL_II*W)*MassOfInitTOC[1]+(KSF_LLNL_III-HI_LLNL_III*W)*MassOfInitTOC[2];
				  MKer=new double[NKerogenType];
				  MKer[0]=TOCRemained_I *MassOfInitTOC[0];  //残余有机碳含量比例乘以初始有机碳含量
				  MKer[1]=TOCRemained_II *MassOfInitTOC[1];
				  MKer[2]=TOCRemained_III *MassOfInitTOC[2];
				  MKerTotal=MKer[0]+MKer[1]+MKer[2];
				  MKerReac=MKerTotal-MKerInert;
			  }
			 
		 };

		 //
		 struct Organofacies
		 {
			 //以下为Pepper 1995 Simple kinetic models of petroleum formation.系类文章中的参数和公式
			 //采用有机相，不存在所谓的混合干酪跟，因此干酪跟类型就是一种
			 double W; //W = 0.85 kgC kgHC^-1  ,即单位质量烃类含有的碳质量   （根据Cooles et al. (1986),我们简单地假设所有的该值都为W=0.85。）
			 double InitTOC;//干酪根的原始TOC含量，原始TOC只有模拟结束后才知道，因此只在最后一个StrSeg有值
			 double MassOfInitTOCTotal; //干酪根原始有机碳总的质量   ，如果只有一种类型干酪根，则该变量与上一个重复
			 //以下为干酪根的动力学参数
			 double TI0;  // TI0=S10/TOC0 ，在这里都假设初始的TOC0=1，因此TI0=S10，如果单位原始有机碳的单位是g,则TI0单位是mgHC/gTOC,如果单位原始有机碳单位是kg,则TI0单位是gHC/kgTOC
			 double HI0; //干酪根的初始氢指数，HI0=S20/TOC0（氢指数HI，即单位质量有机碳的生烃量，因此氢指数提供了沉积有机质中反应干酪根与惰性干酪根的比例指示）
			 double QI0; // QI0=(S10+S20)/TOC0
			 double PI0; //PI0=S10/(S10+S20)
			 double G0; //可以代表初始的生气干酪根与总的初始生油和生气干酪根之和的比值，（G, which is simply the PGC(Pyrolysis-gas chromatography)-derived mass fraction of gas in the S2 yield）该值就是下面的KToGasF，而KToOilF=1-KToGasF
			 // double KToGasF; //  有效干酪根中生成气的比率
			 // double KToOilF;// 有效干酪根中生成油的比率
			 //  double KSF;//   Kerogen Start Fraction   反应物干酪根初始量 ,即初始时刻有机碳中的干酪根的碳含量，与下面的OSF是互补的关系，即KSF=1-OSF
			 // double OSF; //Oil Strat Fraction 反应物（生成物）起始含量 ，即初始时刻有机碳中油的碳含量，与TI0的关系是 OSF=W*TI0/1000
			 //  void GetKSFAndOSF() { OSF=W*TI0/1000.;KSF=1.-OSF;}  //根据TI0值获得原始有机碳中干酪根部分和初始油部分的碳比例

			 double FFKToOil; //Frequency factor  ，频率因子，即A ，单位：s^-1,为单值
			 double EmeanKToOil, SigmaKToOil; //分别是干酪根生油的动力学参数，代表正态分布的均值和标准差
			 int NKToOil;//干酪根生油的平行反应活化能数 ，即将正态分布的参数离散的个数
			 double *fKToOil;//是化学计量系数（Stoichiometric Factor），通过将正态分布离散化得到
			 double *EKToOil;//活化能（Activation Energy）（KJ/mole），通过将正态分布离散化得到

			 double FFKToGas; //Frequency factor  ，频率因子，即A，单位：s^-1,为单值
			 double EmeanKToGas, SigmaKToGas; //分别是干酪根生气的动力学参数，代表正态分布的均质和标准差
			 int NKToGas;//干酪根生气的平行反应活化能数 ，即将正态分布的参数离散的个数
			 double *fKToGas;//是化学计量系数（Stoichiometric Factor），通过将正态分布离散化得到
			 double *EKToGas;//活化能（Activation Energy）（KJ/mole），通过将正态分布离散化得到


			 double FFOilToGas; //Frequency factor
			 double EmeanOilToGas, SigmaOilToGas; //分别是油裂解为气的动力学参数，代表正态分布的均质和标准差
			 int NOilToGas;//油裂解为气的平行反应活化能数 ，即将正态分布的参数离散的个数
			 double *fOilToGas;//是化学计量系数（Stoichiometric Factor） ，通过将正态分布离散化得到
			 double *fOilToGasBak; //备份的计量系数，永远纪录最初始的化学计量系数值
			 double *EOilToGas;//活化能（Activation Energy）（KJ/mole），通过将正态分布离散化得到
			 double OToGasF; //油裂解为气的比例
			 // double OToResidueF; //油裂解为残余物的比例，因此 OToResidueF=1-OToGasF
			 /*   残余物，即焦炭这部分不单独列出了，就是油裂解为气的副产物            */
			
			 double Jiecheng(int n) //n的阶乘
			 {double temp=1; for(int i=0;i<n;i++) temp=temp*double(i+1); return temp; }
			 
			 double erf(double x)
			 {  //误差函数
				 int N=30; //计算的精度相关
				 double pi=3.1415926535;  double temp=0;
				 for(int i=0;i<N+1;i++) temp+=pow(-1.,i)*pow(x,2*i+1)/(2*i+1)/Jiecheng(i);
				 temp=temp*2/sqrt(pi);
				 return temp;
			 }
			 
			 double Pnormal(double q,double Emean,double Sigma)
			 {//正态分布累积概率函数值，在q不超过 Emean±4*Sigma的范围内都可用
				 double temp=(q-Emean)/Sigma/sqrt(2.);
				 return 0.5+0.5*erf(temp);
			 }
			 
			 void GetEachfAndE(int N, double aE,double aSigma,double *f,double *E)
			 { //根据划分区间个数和正态分布的均质和标准差获得离散的活化能和对应的化学计量系数
				 double LeftPoint, RightPoint; //左右断点的值 ，划分的左右端点分别为E±3*Sigma
				 double Delta; //N个区间的每个区间的距离——平均分配区间
				 LeftPoint=aE-3.*aSigma; RightPoint=aE+3.*aSigma;
				 Delta=6.*aSigma/double(N);
				 for(int i=0;i<N;i++)
				 {
					 if(i==0)
					 {    //最左边区间赋值
						 E[i]=LeftPoint+0.5*Delta;//取区间中点值
						 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma); //最左区间的概率值取值为该区间右端值，因此包含了该区间值加上其左边所有的概率值
					 }
					 if(i>0&&i<N-1)
					 {   //中间的区间赋值
						 E[i]=E[i-1]+Delta;  // 取区间中点值
						 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);
					 }
					 if(i==N-1)
					 {  //最右边区间赋值
						 E[i]=E[i-1]+Delta;  // 取区间中点值
						 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);   //最左区间的概率值取值为该区间值加上其右边所有的概率值
					 }
				 }
			 }
			 void Normalization(int N,double *f)
			 {   //将值归一化
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

				 OToGasF=aOToGasF; //油裂解为气的比例
				 W=aW; TI0=aTI0; HI0=aHI0; /*QI0=aQI0; PI0=aPI0;*/ G0=aG0;
				 FFKToOil=aFFKToOil; EmeanKToOil=aEmeanKToOil; SigmaKToOil=aSigmaKToOil; FFKToGas=aFFKToGas; EmeanKToGas=aEmeanKToGas; SigmaKToGas=aSigmaKToGas;
				 FFOilToGas=aFFOilToGas; EmeanOilToGas=aEmeanOilToGas; SigmaOilToGas=aSigmaOilToGas; //OToResidueF=aOToResidueF;
				 NKToOil=21; //将对数正太分布分成21个区间，其中在中值位置有一个区间，另外两边对称地分别分布着10区间 ，划分的左右端点分别为E±3*Sigma （包含了0.9974的概率区间）
				 fKToOil=new double[NKToOil]; EKToOil=new double[NKToOil];
				 GetEachfAndE(NKToOil, EmeanKToOil,SigmaKToOil,fKToOil,EKToOil); Normalization(NKToOil,fKToOil);
				 //for(int i=0;i<NKToOil;i++)ShowMessage("fkToOil="+FloatToStr(fKToOil[i]));
				 NKToGas=21; //将对数正太分布分成21个区间，其中在中值位置有一个区间，另外两边对称地分别分布着10区间 ，划分的左右端点分别为E±3*Sigma （包含了0.9974的概率区间）
				 fKToGas=new double[NKToGas]; EKToGas=new double[NKToGas];
				 GetEachfAndE(NKToGas, EmeanKToGas,SigmaKToGas,fKToGas,EKToGas); Normalization(NKToGas,fKToGas);
				 NOilToGas=21; //将对数正太分布分成21个区间，其中在中值位置有一个区间，另外两边对称地分别分布着10区间 ，划分的左右端点分别为E±3*Sigma （包含了0.9974的概率区间）
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
				 
				 //从另一个结构中拷贝一份参数
				 OToGasF=aOrganofacies->OToGasF; //油裂解为气的比例
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

			 double wBIw0KToOil,  wBIw0KToGas, wBIw0OilToGas;//分别是型干酪根由于生油、生气以及油裂解成气而导致的总的剩余化学计量系数，原始的总的化学计量系数为1
			 double wBIw0K; //干酪根 总的剩余化学计量系数，原始为1。通过干酪根由于生油、生气而导致的总的剩余化学计量系数分别乘以干酪根生成油的比率和生成气的比率之后相加而得到。
			 void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,double *fLLNL,double FFLLNL, double *ELLNL,double &wBIw0)
			 {  //分别是上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma），
				 // 平行反应个数N_LLNL，化学计量系数fLLNL,频率因子FFLLNL，活化能ELLNL,总的剩余化学计量系数wBIw0
				 wBIw0=0.;
				 //double R=0.001986;//气体常数 ，单位 Kcal/(mol*K)
				 double R=0.008314472; //气体常数 KJ/(mol*K)
				 //假设在t和tLast间温度T与t呈线性关系，即在T和TLast间线性变化：T=a*tt+b   ,tt是在t和tLast间变化的时间
				 double a,b; // 线性变化的系数
				 a=(T-TLast)/(t-tLast);b=T-a*t;
				 //对于tLast和t之间采用数值积分方法，将期间等分为N个等分，因此Δt=(t-tLast)/N
				 int N=int(fabs(T-TLast)/0.5+1); //这样计算是保证在每个计算步下温度变化不超过0.5℃，后面加1是保证至少有1步来执行。
				 double Delta_t=(t-tLast)/double(N); //Delta_t在这里是有正负概念的
				 double tt1=tLast,tt2,ttM; // 分别是时间段的下端点值、上端点值和中间值,初始的tt1值设在最底端
				 double temp=0;
				 double *wiBIw0i;  //wi/w0i ,含义见EasyRo推导中的公式（8）
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
					 fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //计算这一时间段的化学计量系数
					 wBIw0+=fLLNL[i];  // wBIw0为总的化学计量系数剩余值
					 tt1=tLast; // 算下一个对应的活化能的wiBIw0i[i]需要将初始时间重置
					 temp=0;    //temp重新归零
				 }

				 //release
				 delete wiBIw0i;
			 }

			 double OilPerInitTOC; //单位质量原始有机碳（InitTOC）在这一时间段的生油量
			 double GasPerInitTOC; //单位质量原始有机碳（InitTOC）在这一时间段的生气量
			 double TOCReactableKerogen, TOCInertKerogen; //分别是可反应干酪根和惰性干酪根 ，是指单位原始有机碳中在初始状态以及反应过程中可反应干酪根和惰性干酪根的量。
			 double TOCKerogen; //干酪根有机碳剩余量 。是指单位质量原始干酪跟的残余量
			 double TOCRemained; //残余有机碳剩余量 。是指单位质量原始有机碳在演化过程中的残余量 ，包括干酪根有机碳剩余量 +源岩中油气中有机碳含量+油裂解后残余的焦炭量
			 double OilGenerated,GasGenerated; //干酪跟单位质量原始有机碳累计的生油量和生气量
			 double TR; //源岩的油气转化率, 即原始可降解干酪根有机碳转化为油和气中的有机碳比例
			 void Reactions(double TLast, double tLast, double T, double t)
			 {  //针对时间上第一个地层段
				 // 各有机碳、油、气量的变化，没有包括裂解部分
				 // 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				 //都是基于单位质量（kg）原始有机碳计算的
				 // 计算原理来自PetroMod；参数来源于Pepper，1995

				 TLast+=273;T+=273;   //转化为开氏温度
				 tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				 t=t*1000000*365*24*3600; //百万年转化为秒
				 //以下为I型干酪根热解
				 double InitwBIw0KToOil=0,InitwBIw0KToGas=0;  //初始时刻的干酪根组分（化学计量系数）之和
				 for(int i=0;i<NKToOil;i++)InitwBIw0KToOil+=fKToOil[i]; for(int i=0;i<NKToGas;i++)InitwBIw0KToGas+=fKToGas[i];
				 FirstOrderReaction(TLast, tLast,T,t,NKToOil,fKToOil,FFKToOil,EKToOil,wBIw0KToOil);  // 干酪根成油热解
				 FirstOrderReaction(TLast, tLast,T,t,NKToGas,fKToGas,FFKToGas,EKToGas,wBIw0KToGas);  // 干酪根成气热解
				 OilPerInitTOC=HI0*(1.-G0)*(InitwBIw0KToOil-wBIw0KToOil)/1000.; //   //每单位原始有机碳在该时间步的生油量   OilPerInitTOC=HI0*(InitwBIw0KToOil-wBIw0KToOil)*KSF*(1.-G0);
				 GasPerInitTOC=HI0*G0*(InitwBIw0KToGas-wBIw0KToGas)/1000.;       //每单位原始有机碳在该时间步的生气量  //       GasPerInitTOC=HI0*(InitwBIw0KToGas-wBIw0KToGas)*KSF*G0;
				 OilGenerated=OilPerInitTOC+TI0/1000.; //  //干酪跟单位质量原始有机碳累计的生油量。。。在初始步计算的累积生油量为该步的生油量与初始时刻存在的油量之和
				 GasGenerated=GasPerInitTOC; // //干酪跟单位质量原始有机碳累计的生气量。。 气没有初始的存在量，因此初始步的累积生气量就是该步的生气量
				 TOCKerogen=1.-W*TI0/1000.-W*OilPerInitTOC- W*GasPerInitTOC;  //是指干酪根中的有机碳含量 ,需要用原始单位有机碳-初始存在的油所含的有机碳-该步生成的油和气中的有机碳
				 TOCRemained=TOCKerogen; //剩余有机碳量在这里不考虑源岩中的烃类，即用干酪根有机碳量近似代替总的TOC。因为在计算过程中并不容易确定源岩中烃类含量，因为在使用TOCRemained这个参数时还没有运行油裂解程序。
				 // TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //源岩中剩余的有机碳为干酪根有机碳与存在与源岩中油和气中的有机碳以及油裂解为焦炭之和 ,该项需要在裂解和排烃后才可知晓 ；；这个式子不能用，因为OilExisted是总的网个体StrSeg中总的存在的油的质量，并且在运行 Reactions(...)函数时，该值还未知
				 TOCInertKerogen=1.-W*TI0/1000.-W*HI0/1000.;   //惰性干酪根含量
				 TOCReactableKerogen=TOCKerogen-TOCInertKerogen; //可反应干酪根含量
				 TR= (OilGenerated-TI0/1000.+GasGenerated)/(HI0/1000.);
				 //油气转化率等于单位质量原始有机碳累积生成的油气量除以单位质量原始有机碳的氢指数
			 }
			 void Reactions(double TLast, double tLast, double T, double t,Organofacies *aOrganofacies)
			 {  // 各干酪根组分、油、气量的变化，没有包括裂解部分
				 // 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				 //aOrganofacies为上一个时间段的参数结构
				 //都是基于单位质量（kg）原始有机碳计算的
				 // 计算原理来自PetroMod；参数来源于BasinMod
				 TLast+=273;T+=273;   //转化为开氏温度
				 tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				 t=t*1000000*365*24*3600; //百万年转化为秒
				 //以下为干酪根热解
				 //wBIw0KToOil=aOrganofacies->wBIw0KToOil;wBIw0KToGas=aOrganofacies->wBIw0KToGas;
				 FirstOrderReaction(TLast, tLast,T,t,NKToOil,fKToOil,FFKToOil,EKToOil,wBIw0KToOil);  // 干酪根成油热解
				 FirstOrderReaction(TLast, tLast,T,t,NKToGas,fKToGas,FFKToGas,EKToGas,wBIw0KToGas);  // 干酪根成气热解
				 OilPerInitTOC=HI0*(1.-G0)*(aOrganofacies->wBIw0KToOil-wBIw0KToOil)/1000.;
				 GasPerInitTOC=HI0*G0*(aOrganofacies->wBIw0KToGas-wBIw0KToGas)/1000.;;
				 OilGenerated=aOrganofacies->OilGenerated+OilPerInitTOC; //
				 GasGenerated=aOrganofacies->GasGenerated+GasPerInitTOC; //
				 TOCKerogen=aOrganofacies->TOCKerogen-W*OilPerInitTOC-W*GasPerInitTOC; //是指干酪根中的有机碳含量 ,需要用原始单位有机碳-初始存在的油所含的有机碳-已经累计生成的油和气中的有机碳
				 TOCRemained=TOCKerogen; //剩余有机碳量在这里不考虑源岩中的烃类，即用干酪根有机碳量近似代替总的TOC。因为在计算过程中并不容易确定源岩中烃类含量，因为在使用TOCRemained这个参数时还没有运行油裂解程序。
				 //TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //源岩中剩余的有机碳为干酪根有机碳与存在于源岩中油和气中的有机碳之和 ,该项需要在裂解和排烃后才可知晓
				 TOCInertKerogen=1.-W*TI0/1000.-W*HI0/1000.;   //惰性干酪根含量
				 TOCReactableKerogen=TOCKerogen-TOCInertKerogen; //可反应干酪根含量,是指单位原始有机碳中所对应的量
				 TR= (OilGenerated-TI0/1000.+GasGenerated)/(HI0/1000.);
			 }

			 //以下与油裂解有关的都是对应于网格体中原始有机碳含量的
			 double OilExisted; //指的是存在于源岩中的油组分
			 double GasExisted; //指的是存在于源岩中的气组分
			 double ResidueExisted; //指存在于源岩中的油裂解为残余物量
			 double GasCracked;//指的是每一步油裂解的气量
			 double GasCrackedAdded; //指每一步裂解气的累加量
			 double ResidueCracked; // 指的是每一步油裂解的残余物量
			 double ResidueCrackedAdded; // 指的是每一步油裂解的残余物的累加量
			 double OilCracked;//每一步油的裂解量
			 double OilCrackedAdded;//每一步油的裂解量的累加量
			 void GetfOilToGas()
			 {  //获得第一步的油裂解为气的化学计量系数，根据源岩中不同来源油的比率计算；
				 //分为第一步的干酪根降解油以及这一步油裂解为气剩余的油量，根据它们之间的比率确定不同化学计量系数的所占的比例
				 double RatioKerogenOil,RatioCrackLeftedOil; //分别是这一步干酪根生成的油和裂解剩余的油所占的比例
				 double SumfOilToGas=0.;
				 RatioKerogenOil=OilPerInitTOC*MassOfInitTOCTotal/OilExisted;
				 RatioCrackLeftedOil=(MassOfInitTOCTotal*TI0/1000.-OilCracked)/OilExisted;
				 for(int i=0;i<NOilToGas;i++) fOilToGas[i]=fOilToGasBak[i]*RatioKerogenOil+fOilToGas[i]*RatioCrackLeftedOil;
				 wBIw0OilToGas=1.;   //每次计算完要将该值归为起始值，初始值为1,这是因为每次计算用于裂解的油都是已知的初始值
			 }

			 void OilCrackToGas(double TLast, double tLast, double T, double t)
			 {    //由于各型干酪根生成的油裂解为气和残余物的化学动力学参数相同，这里采用I型干酪跟的参数作为总体的参数 ;这里采用显式解法，即裂解的为上一时间步存在的油
				 //以下为StrSeg中存在的油裂解为气和残余物的过程。由于是第一个时间步，初始时刻源岩中存在原始的油
				 TLast+=273;T+=273;   //转化为开氏温度
				 tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				 t=t*1000000*365*24*3600; //百万年转化为秒
				 double InitwBIw0OilToGas=0;  //初始时刻的各油裂解（化学计量系数）之和
				 for(int i=0;i<NOilToGas;i++)InitwBIw0OilToGas+=fOilToGas[i];//和值应该等于1
				 FirstOrderReaction(TLast, tLast,T,t,NOilToGas,fOilToGas,FFOilToGas,EOilToGas,wBIw0OilToGas);  // 干酪根相关油裂解为气
				 OilExisted=MassOfInitTOCTotal*TI0/1000.;   //初始单位网格源岩内的油存在量 ，等于原始有机碳质量乘以TI0值
				 GasExisted=0.;
				 GasCracked=OilExisted*OToGasF*(InitwBIw0OilToGas-wBIw0OilToGas);   //在初始时刻反应物（即油）的初始含量的初始含量 TI0/1000；；OToGasF为油转化为气的比例；
				 ResidueCracked=OilExisted*(1.-OToGasF)*(InitwBIw0OilToGas-wBIw0OilToGas);  //油转化为残余物的比例为 (1.-OToGasF)，油转化为残余物与油转化为气是同一个裂解过程
				 OilCracked=GasCracked+ResidueCracked;
				 GasCrackedAdded=GasCracked;//由于是第一个时间步，因此气累积裂解量等于初始裂解量。
				 ResidueCrackedAdded=ResidueCracked;
				 OilCrackedAdded=OilCracked;
				 OilExisted=OilExisted+OilPerInitTOC*MassOfInitTOCTotal-OilCracked;     //指的是每次油生成和裂解后可在源岩中存在的油量，还没有考虑吸附和孔隙中能够存在的量
				 GasExisted =GasExisted+GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //该时间步的存在气量等于已经存在的气量加上这一时间步干酪根生成的气量加上该时间步油裂解生成的气量
				 GetfOilToGas();
			 }
			 void GetfOilToGas(Organofacies *aOrganofacies)
			 {  //获得每一步的油裂解为气的化学计量系数，根据源岩中不同来源油的比率计算；
				 //分为每一步的干酪根降解油以及这一步油裂解为气剩余的油量，根据它们之间的比率确定不同化学计量系数的所占的比例
				 double RatioKerogenOil,RatioCrackLeftedOil; //分别是这一步干酪根生成的油和裂解剩余的油所占的比例
				 double SumfOilToGas=0.;
				 RatioKerogenOil=OilPerInitTOC*MassOfInitTOCTotal/OilExisted;
				 RatioCrackLeftedOil=(aOrganofacies->OilExisted-OilCracked)/OilExisted;
				 Normalization(NOilToGas,fOilToGas); //将热裂解后的油的化学计量系数归一化
				 for(int i=0;i<NOilToGas;i++) fOilToGas[i]=fOilToGasBak[i]*RatioKerogenOil+fOilToGas[i]*RatioCrackLeftedOil;
				 wBIw0OilToGas=1.;   //每次计算完要将该值归为起始值，初始值为1,这是因为每次计算用于裂解的油都是已知的初始值
			 }
			 void OilCrackToGas(double TLast, double tLast, double T, double t,Organofacies *aOrganofacies)
			 {    //由于各型干酪跟生成的油裂解为气和残余物的化学动力学参数相同，这里采用I型干酪跟的参数作为总体的参数 ;这里采用显式解法，即裂解的为上一时间步存在的油
				 //以下为I型干酪根相关油裂解为气和残余物
				 //以下为I型干酪根相关油裂解为气和残余物
				 TLast+=273;T+=273;   //转化为开氏温度
				 tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				 t=t*1000000*365*24*3600; //百万年转化为秒
				 FirstOrderReaction(TLast, tLast,T,t,NOilToGas,fOilToGas,FFOilToGas,EOilToGas,wBIw0OilToGas);  // 油裂解为气
				 GasCracked=aOrganofacies->OilExisted*OToGasF*(aOrganofacies->wBIw0OilToGas-wBIw0OilToGas);
				 ResidueCracked=aOrganofacies->OilExisted*(1.-OToGasF)*(aOrganofacies->wBIw0OilToGas-wBIw0OilToGas);
				 OilCracked=GasCracked+ResidueCracked;
				 GasCrackedAdded=aOrganofacies->GasCrackedAdded+GasCracked;
				 ResidueCrackedAdded=aOrganofacies->ResidueCrackedAdded+ResidueCracked;
				 OilCrackedAdded=aOrganofacies->OilCrackedAdded+OilCracked;
				 OilExisted=aOrganofacies->OilExisted+OilPerInitTOC*MassOfInitTOCTotal-OilCracked;     //指的是每次油生成和裂解后可在源岩中存在的油量，还没有考虑吸附和孔隙中能够存在的量
				 GasExisted=aOrganofacies->GasExisted+GasPerInitTOC*MassOfInitTOCTotal+GasCracked;  //该时间步的存在气量等于已经存在的气量加上这一时间步干酪根生成的气量加上该时间步油裂解生成的气量
				 GetfOilToGas(aOrganofacies);
			 }
			 double MKerTotal; //总的干酪根有机碳质量，（不包括油裂解的焦炭量） ；新加入20170908
			 double MKerReac; //源岩中可反应的干酪根量，以有机碳形式给出，单位：kg
			 double MKerInert; //源岩中无效干酪根量 ，以有机碳形式给出，单位：kg
			 void GetMKer()
			 {   //获得源岩中干酪根（有机碳）质量
				 MKerTotal=TOCKerogen*MassOfInitTOCTotal;
				 MKerInert=TOCInertKerogen*MassOfInitTOCTotal;
				 MKerReac= MKerTotal-MKerInert;
			 }

		 };

		struct Str  //定义一个地层、虚层或剥蚀结构
		{
			int LithNumber;  //地层混合岩性数
			double *LithRatio;  //地层混合岩性比例
			int Property; //地层的性质 ，1为地层，2为虚层，3为剥蚀
			double BeginAge; // 地层、虚层或剥蚀开始时间
			double EndAge;// // 地层、虚层或剥蚀结束时间

			double CurrentThickness;// 现今地层、虚层或剥蚀厚度
			double MaxBuryTopDepth; //顶面最大深度
			double MaxBuryBottomDepth;//底面最大深度

			double Thickness;// 地层、虚层或剥蚀厚度
			double TopDepth; //顶面深度，没包括古水深
			double BottomDepth;//底面深度 ，没包括古水深

			int  ConnectingMarker; //剥蚀和相关联的需层关联标记
			int *VirtualErosionPair; //虚层StrSeg和其对应的剥蚀StrSeg关联对；
			int StrSegNumber; //每个地层或事件包括的地层段数量
			double CurrentStrSegThickness;  //里面的地层段现今存在的厚度；每个StrSeg均分
			double *CurrentSST;  //用数组表示的地层中每个地层段的厚度，虽然对于地层或虚层均分，每个CurrentSST[]数值相同，
								//但对于剥蚀事件，其对应的虚层可能不止一个，每个虚层的CurrentStrSegThickness并不一致，因此用数组表示更好一些
			double MatrixThickness;  //骨架厚度

			bool SourceRock; //用于判断是否为源岩
			double TOC; //  源岩有机碳含量

			Str()
			{
				Init();
			}

			void Init()
			{
				LithNumber = 0;  //地层混合岩性数
				LithRatio = 0;  //地层混合岩性比例
				Property = 0; //地层的性质 ，1为地层，2为虚层，3为剥蚀
				BeginAge = 0.; // 地层、虚层或剥蚀开始时间
				EndAge = 0.; // // 地层、虚层或剥蚀结束时间

				CurrentThickness = 0.;// 现今地层、虚层或剥蚀厚度
				MaxBuryTopDepth = 0.; //顶面最大深度
				MaxBuryBottomDepth = 0.;//底面最大深度

				Thickness = 0.;// 地层、虚层或剥蚀厚度
				TopDepth = 0.; //顶面深度，没包括古水深
				BottomDepth = 0.;//底面深度 ，没包括古水深

				ConnectingMarker = 0; //剥蚀和相关联的需层关联标记
				VirtualErosionPair = 0; //虚层StrSeg和其对应的剥蚀StrSeg关联对；
				StrSegNumber = 0; //每个地层或事件包括的地层段数量
				CurrentStrSegThickness = 0.;  //里面的地层段现今存在的厚度；每个StrSeg均分
				CurrentSST = 0;  //用数组表示的地层中每个地层段的厚度，虽然对于地层或虚层均分，每个CurrentSST[]数值相同，
				//但对于剥蚀事件，其对应的虚层可能不止一个，每个虚层的CurrentStrSegThickness并不一致，因此用数组表示更好一些
				MatrixThickness = 0.;  //骨架厚度

				SourceRock = false; //用于判断是否为源岩
				TOC = 0.; //  源岩有机碳含量
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
			{ //复制MaxTopThickness,MaxBottomDepth到TopDepth 和BottomDepth
				TopDepth=MaxBuryTopDepth;
				BottomDepth=MaxBuryBottomDepth;
				Thickness=CurrentThickness;
			}

		};

		struct StrSeg
		{    
			//LLNL/Organo
			PetroGenStyle aPetroGenStyle;			
			
			//定义一个地层段类；是各地层的细分段 ，也可以是一个事件，如剥蚀和已存在过的地层
			//--------------------------------------------各种单值的参数
			int pos_i,pos_j,pos_k; //记录该地层段在三维数组中的坐标
			int EndPoint; //记录地层段最后一个时间在三维数组中的坐标

			double MarginOfErrorThickness; //判断虚层剥蚀情况的容错误差限
			double Ma2Second;

			int LithNumber;   //混合岩性的个数
			double *LithRatio; //混合岩性的比例 ；地层段的各个参数都是依据混合岩性的比例给出的

			double BeginAge; //地层段开始时间
			double EndAge;   //地层段结束时间
			double MiddleAge;//地层段中间时间
			double DeltaAge; //地层段或事件的经历时间

			int Property;   //地层段性质：1是地层，2是虚层，3是剥蚀，4沉积间断
			int ConnectingMarker;  //虚层和剥蚀事件的关联标记
			int VirtualErosionPair; //虚层StrSeg和其对应的剥蚀StrSeg关联对；用整数来标记每一个虚层StrSeg的VirtualErosionPair值与唯一的对应的一个剥蚀事件的StrSeg的VirtualErosionPair值相同。
			bool Eroded; //用于判断虚拟层是否已经被剥蚀掉了，初始赋值时都是false
			bool SourceRock; //用于判断是否为源岩
			bool *IsThisMatrixKerogenOrCoal; //判断基质类型是否为干酪跟或煤

			double MaxBuryMiddleDepth; //地层段经历的最大埋藏中部深度
			double MaxBuryTopDepth;    //地层段经历的最大埋藏顶部深度
			double MaxBuryBottomDepth; //地层段经历的最大埋藏底部深度
			double TopDepth; //顶面深度  ，指的是加上了古水深的顶面深度
			double BottomDepth;//底面深度
			double MiddleDepth;//中部深度
			double BuryTopDepth; //顶面埋藏深度 ，不算古水深，只是沉积物的深度，从沉积物-水表面算起的深度
			double BuryBottomDepth;//底面埋藏深度
			double BuryMiddleDepth;//中部埋藏深度
			double CurrentThickness;//现今的厚度(包括虚地层)，剥蚀厚度为负  ;地层或虚层的现今的厚度即对应于最大深度的厚度
			double Thickness; //厚度
			double MatrixThickness;//骨架厚度
			//以下这些压力的单位都采用国际单位制：帕斯卡
			double Pt,Pm,Pb; //地层段顶部、中部和底部流体压力
			double Ut,Um,Ub; //分别为顶部、中部和底部的流体超压
			double StaticPt,StaticPm,StaticPb; //地层段顶部、中部和底部静流体压力
			double Plt,Plm,Plb; //静岩压力,分别是StrSeg顶部、中部、和底部的静岩压力
			double Ult,Ulm,Ulb; //静岩势能,分别是StrSeg顶部、中部、和底部的静岩势能
			double EffectiveStresst,EffectiveStressm, EffectiveStressb; //有效应力，分别是StrSeg顶部、中部、和底部的
			double MaxEffectiveStresst,MaxEffectiveStressm,MaxEffectiveStressb;  //记录StrSeg经历的最大有效应力

			double COC;//压缩系数 Coefficient Of Compressibility
			double aOverpressure,bOverpressure,cOverpressure; //超压方程中的三个参数

			double vFluild; //流体流动速度，这一参数没用到
			double vWater; //地层水流速

			double *InitialPorosity,*CompactionFactor;  //初始孔隙度和关于静水压力深度的Athy定律的压实系数 kArthDepth
			double TInitialPorosity,TCompactionFactor;  //混合的总体的初始孔隙度和压实系数
			double *Porosityt; //各混合岩性的孔隙度，孔隙度为小数;;顶部值
			double *Porositym;  // 各混合岩性的孔隙度，孔隙度为小数;;中部值
			double *Porosityb;  // 各混合岩性的孔隙度，孔隙度为小数;;底部值
			double Porot,Porom,Porob; //为顶、中部和底的孔隙度 ，小数
			double EndPorom; //现今地层的孔隙度值，包括虚层在剥蚀前最小的孔隙度值。用于比较迭代前后孔隙度以判断是否收敛。用于超压方程
			double DifferencePoromEndPorom; //计算的最终的孔隙度值和上一次迭代（或初始）的孔隙度差值
			double *LogPermeability; //各混合岩性的渗透率自然对数值,单位是LogmD
			double Perm; // 总的渗透率 Permeability， 单位是m^2
			Poro_Perm *aPoro_Perm; //孔隙度-渗透率关系数据对

			//=================粘度、相对渗透率、界面张力、毛管压力========开始
			double WaterViscosity;  //水粘度
			double OilViscosity; //油粘度
			double GasViscosity; //气粘度
			double Sw,So,Sg; //水、油、气的饱和度  ,用小数表示
			double Swc,Soc,Sgc; // 束缚水饱和度、残余油饱和度 、残余气饱和度    ,用小数表示
			double Swe; //effective saturations Se有效水饱和度for krw and krow,       ,用小数表示
			double Soe; // 有效油饱和度 ,暂时没有用上    ,用小数表示
			double Sgoe; //用于Krog的有效饱和度  ,用小数表示
			double Sge; // 有效气饱和度,用于Krg   ,用小数表示
			void GetSe() //获得有效水、油、气有效饱和度  ,用小数表示
			{
				Sw=0.5; So=0.3;Sg=0.2;   //暂时给定的值，测试用
				Swc=0;Soc=0;Sgc=0; //暂时在模拟中将这些参数都定为0
				Swe = (Sw-Swc)/(1.-Swc-Soc);
				Soe = (So-Soc)/(1.-Swc-Soc);
				Sgoe=Sg/(1.-Swc);
				Sge = (Sg-Sgc)/(1.-Swc-Sgc);
			} //
			double Krow,Krog; //
			double Krw,Krg,Kro; //分别是水、气、油的相对渗透率
			double lamuda; // a parameter λ which describes a "sorting" of the rock. It can vary between 0 and ∞. A small value indicates a poorly sorted (inhomogeneous) rock (Sylta, 2002a; Ataie-Ashtiani et al., 2002).
		/*  void GetKr()  //获得油、气、水的相对渗透率
			{  //Hantschel 2009 ,P252  Table 6.1
				Krw=0.4*Swe*Swe;
				Krow=1.-1.8*Swe+0.8*Swe*Swe;
				Krg=0.4*Sge*Sge;
				Krog=1.-1.8*Sgoe+0.8*Sgoe*Sgoe;
				Kro=Krow*Krog;
			}   */
			void GetKrwKrow()              //相对渗透率计算，采用Brooks-Corey经验公式
				{
					Krw=pow(Swe,(2.0+3.0*lamuda)/lamuda);
					Krow=pow(1.0-Swe,2)*(1.0-pow(Swe,(2.0+lamuda)/lamuda));
				}
			void GetKrwKrg()              //相对渗透率计算，采用Brooks-Corey经验公式
				{
					Krw=pow(Swe,(2.0+3.0*lamuda)/lamuda);
					Krg=pow(1.0-Swe,2)*(1.0-pow(Swe,(2.0+lamuda)/lamuda));
				}
			void GetKrgKrog()              //相对渗透率计算，采用Brooks-Corey经验公式
				{
					Krg=pow(Sge,(2.0+3.0*lamuda)/lamuda);
					Krog=pow(1.0-Sge,2)*(1.0-pow(Sge,(2.0+lamuda)/lamuda));
				}
			void GetKr()  //获得油、气、水的相对渗透率
				{
				lamuda=0.34; //各种岩性统一定为该值
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
			double aToEntryPr,bToEntryPr;//对应于突破毛管压力的系数a和b,在Hantschel 2009 ,P411. Table A.6. Capillary Entry Pressure
			double PcbMA; // 突破毛管压力,水银-空气
			double PcMA; //毛管压力，水银-空气
			double PcbOW,PcbGW,PcbGO; //分别为油水、气水和气油的突破毛管压力
			double PcOW,PcGW,PcGO; //分别油水、气水和气油的毛管压力
			double RouML,RouMV; //分别是油和气的摩尔密度，单位：gmol/cm 3
			double Tc,vc; //分别为体系的临界温度和临界摩尔体积，根据摩尔平均值或等；单位分别为K和cm3/gmol
			double TcL,TcV; //分别是油相和气相的临界温度，单位：K
			double PXigema; //known as the parachor  ,等张比容
			double IFTOilWater,IFTGasWater,IFTGasOil;//油水、气水和气油的界面张力  interfacial tension (IFT) ，单位：mN/m
			void GetTcVc()
			{  //获得体系的临济温度和临界体积
				Tc=0;vc=0;
				for(int i=0;i<NCom;i++) {Tc+=z[i]*Tci[i];vc+=z[i]*vci[i];}
				vc*=1000.; // 将m3/kgmol转化为cm3/mol
			}
			void GetTcLTcV()
			{  //获得油相和气相的临界温度 ,单位 ：K
				TcL=0;TcV=0;
				for(int i=0;i<NCom;i++) {TcL+=x[i]*Tci[i];TcV+=y[i]*Tci[i];}
			}
			void GetRouMLRouMV(){ RouML=1.e-3/vL;RouMV=1.e-3/vV; } //获得体系的摩尔体积,单位：gmol/cm 3
			void GetIFTOilAndWater(){IFTOilWater=111.*pow((WaterDensity-OilDensity)/1000.,1.024)*pow(TmK/TcL,-1.25);} //获得油水界面张力mN/m，Danesh, 1998 ，P294 8.24 在Hantschel 2009 ,P234. （5.85)
			void GetIFTGasAndWater(){IFTGasWater=111.*pow((WaterDensity-GasDensity)/1000.,1.024)*pow(TmK/TcV,-1.25);} //获得气水界面张力（在仅有气水两相的情况下使用）mN/m，Danesh, 1998 ，P294 8.24 在Hantschel 2009 ,P234. （5.85)
			void GetPXigema() {PXigema=0.324*pow(Tc,0.25)*pow(vc,7./8.);}       //the critical temperature Tc is in K and the critical volume vc is in cm3/gmol. Danesh, 1998 ，P286 8.6
			void GetIFTGasOil() {GetPXigema(); IFTGasOil=pow(PXigema*(RouML-RouMV),4);}     //Parachor Method
			void GetIFT()  //获得总的界面张力
			{
				GetTcVc();
				GetTcLTcV();
				GetRouMLRouMV();
				GetIFTOilAndWater();
				GetIFTGasAndWater();
				GetIFTGasOil();
			}
			void GetPcbMA() {PcbMA=aToEntryPr*pow(10.,bToEntryPr*Porom*100.);} //计算突破毛管压力，水银-空气，孔隙度依赖模型 Hantschel,2009  P257 (6.17)
			void GetPcb(){GetPcbMA();GetIFT(); PcbOW=PcbMA*IFTOilWater/360.8; PcbGW=PcbMA*IFTGasWater/360.8;PcbGO=PcbMA*IFTGasOil/360.8;} // Hantschel,2009  P254 (6.11)
			void GetPc(){GetPcb();PcOW=PcbOW*pow(Swe,-1./lamuda); PcGW=PcbGW*pow(Swe,-1./lamuda); PcGO=PcbGO*powl(1.-Sge,-1./lamuda);} //分别为油和气的毛管压力--随饱和度的变化
			void GetKrPc()
			{   //得到相对渗透率和毛管压力值
				GetSe();
				GetKr();
				GetPc();
			}
			void GetViscosityKrPc()  //得到粘度、相对渗透率和毛管压力值
			{GetWaterViscosity();GetOilGasViscosity();GetKrPc();}
			void GetWaterViscosity()
			{    //华氏度(℉)=32+摄氏度(℃)×1.8
				WaterViscosity=109.5*pow(32+Tm*1.8,-1.122);  //这里的单位为厘泊cP,1厘泊(1cP)=1毫帕斯卡.秒 (1mPa.s)
				WaterViscosity/=1000.; //最终转化为Pa.s
			}
		void GetOilGasViscosity()
			{    //来自：Danish 1998, P335    Lohrenz-Bray-Clark (LBC) method
				double *Miu0i; Miu0i=new double[NCom];
				double *Tri; Tri=new double[NCom];
				double *Lamudai; Lamudai=new double[NCom];
				double Miu0L,Miu0V; //低压下油和气相的粘度
				double LamudaL,LamudaV; //油和气相的λ
				double vcL,vcV;  //分别为油和气的临界摩尔体积critical molar volume
				// double Tc,Tr; //油相的临界温度和对比温度
				// double Pc; //油相的临界压力
				double RouRL,RouRV; // 油和气的比密度，reduced density, ρr = ρ/ρc=vc/v,
				for(int i=0;i<NCom;i++)
					{
					Tri[i]=(Tm+273.15)/Tci[i];   //这里的临界温度单位为K
					Lamudai[i]=pow(Tci[i],1./6.)*pow(MW[i],-0.5)*pow(Pci[i]/0.101325,-2./3.);  //(9.25)  这里的临界压力单位为大气压
					if(Tri[i]<=1.5)
					Miu0i[i]=34.e-5*pow(Tri[i],0.94)/Lamudai[i];   //单位：mPa.s
					else
					Miu0i[i]=17.78e-5*pow(4.58*Tri[i]-1.67,5./8.)/Lamudai[i];  //单位：mPa.s
					}
				double temp01=0,temp02=0,temp03=0,temp04=0,temp05=0,temp06=0;   //对应于油相
				double temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;   //对应于气相
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
				Miu0L=temp01/temp02;                     //(9.28)，单位：mPa.s
				Miu0V=temp1/temp2;                     //(9.28)，单位：mPa.s
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
				OilViscosity= (pow(RightPartOil,4)-1.e-4)/LamudaL+Miu0L;                                 //(9.26)  这里单位为：mPa.s，即cp
				GasViscosity= (pow(RightPartGas,4)-1.e-4)/LamudaV+Miu0V;                                 //(9.26)  这里单位为：mPa.s，即cp
				OilViscosity/=1000.; GasViscosity/=1000.; //转化为Pa.s，即千克。米。秒单位体系

				//release
				delete Miu0i;
				delete Tri;
				delete Lamudai;


			}

			//=================粘度、相对渗透率、界面张力、毛管压力========开始

			double *MatrixDensity; //不同岩性基质的密度
			double TMatrixDensity; //  总的基质密度
			double WaterDensity; //地层水密度
			double OilDensity; //油密度
			double GasDensity; //气密度
			double SeaWaterDensity;  //海水密度取值=1025 kg/m^3
			double TotalDensity; //总的岩石密度（包括其中的流体和骨架的综合密度）

			double TotalThermalCond; //总的热导率  （包括基质和孔隙流体）
			double *MatrixThermalCond; //不同的基质热导率
			double TMatrixThermalCond; //总的基质热导率
			double WaterThermalCond; //地层水热导率
			double OilThermalCond; //油热导率
			double GasThermalCond; //气热导率
			double PoreFluidThermalCond; //孔隙流体热导率
			double IceThermalCond; //冰热导率
			double GasHydratesThermalCond; //天然气水合物热导率

			double TotalHeatCapacity; //总的比热容 （包括基质和孔隙流体）
			double *MatrixHeatCapacity; //基质比热容，不同的基质
			double TMatrixHeatCapacity; //总的基质比热容
			double WaterHeatCapacity; //地层水比热容
			double OilHeatCapacity; //油比热容
			double GasHeatCapacity; //气比热容
			double IceHeatCapacity; //冰比热容
			double GasHydratesHeatCapacity; //天然气水合物比热容
			double PoreFluidHeatCapacity; //孔隙流体比热容


			double *MatrixRadioactiveHeat;    //不同岩性基质的辐射热
			double Qr; // 总的辐射热

			double PaleoWaterDepth;//记录古水深
			double SurfaceT; //地表温度，记录最上面的格子
			double HF; //记录古热流

			double Tt; //顶部温度
			double Tm; //中部温度
			double Tb; //底部温度
			double Tmax; //记录模拟过程中中部的最高温度


			double TTI; //地层的TTI值
			double Ro[4];  //地层的Ro%值
			double TTI0; //初始时刻的TTI值
			ParaOfEasyRo *aParaOfEasyRo; //定义一个EasyRo模型结构，用于存储参数
			ParaOfEasyRo *aParaOfBasinRo; //定义一个BasinRo模型结构，用于存储参数
			ParaOfSimpleRo *aParaOfSimpleRo; //定义一个SimpleRo模型结构，用于存储参数

			double TOC; //残余有机碳含量
			double InitTOC; //原始有机碳含量 ,是在现在的地层条件下的原始有机碳含量，即现今的岩石密度条件 。该数值只有最后一个时间的地层段存在
			double MassOfInitTOC;//该地层段单位面积（m^2）上原始有机碳的总质量 。 该数值只有最后一个时间的地层段存在

			DR *aDR;  //定义一个干酪根降解结构体
			double HCGI[4]; //  生烃强度 kg/m^2 ，用于降解生烃模型
			double OGI[4]; //oil generating intensity ,生油强度 kg/m^2 ，用于降解生烃模型
			double GGI[4]; //gas generating intensity ,生气强度 kg/m^2 ，用于降解生烃模型

			//2017/11/27: 定义一个有机相的化学反应动力学参数结构体
			Organofacies *aOrganofacies; 

			ParaLLNL *aParaLLNL; //定义一个LLNL化学反应动力学参数结构体
			double OGI_LLNL;   //oil generating intensity ,生油强度 kg/m^2  ,用于化学反应动力学生烃模拟
			double GGI_LLNL;   //gas generating intensity ,生气强度 kg/m^2（也用质量单位）  ,用于化学反应动力学生烃模拟

			//2017/8/8: pressure coefficient(压力系数)
			double PCOEt;//top
			double POCEm;//middle
			double POCEb;//bottom

			//2017/10/13: ---------------------------------排烃 START-----------------------------------------------------
			// double HI0; //源岩初始的氢指数，g/gTOC
			double aO;//油吸附系数Oil sorption cofficient ，单位：g/gC
			double aG;//气吸附系数Gas sorption cofficient ，单位：g/gC
			double MKer; //源岩中干酪根质量，以有机碳形式给出，单位：kg
			double COS; //Critical oil saturation 临界排油饱和度
			double CGS; // Critical Gas saturation 临界排气饱和度
			double MKerReac; //源岩中可反应的干酪根量，以有机碳形式给出，单位：kg
			double MKerInert; //源岩中无效干酪根量 ，以有机碳形式给出，单位：kg
			double MAdxOil; //源岩中油的吸附量，单位：kg
			double MAdxGas; //源岩中气的吸附量，单位：kg
			double MAdxMaxOil; //源岩中油的最大吸附量，单位：kg
			double MAdxMaxGas; //源岩中气的最大吸附量，单位：kg
			double MExpOil; //源岩排油量，单位：kg ，是指在一个时间步长上由干酪根中排向源岩无机孔隙中的量
			double MExpGas; //源岩排气量，单位：kg ，是指在一个时间步长上由干酪根中排向源岩无机孔隙中的量
			double MExpOilAdded; //源岩累积排油量，单位：kg ，
			double MExpGasAdded; //源岩累积排气量，单位：kg ，
			double MResidualOil;  //源岩残余油量，是指吸附量加上无机质孔隙中的油量
			double MResidualGas;  //源岩残余气量，是指吸附量加上无机质孔隙中的气量
			double OilInSourceRockPoros,GasInSourceRockPoros; //分别为源岩孔隙中的油和气量，现在还没有考虑，暂时都假设为0，后期可以考虑不为0的情况
			double OilOutOfSourceRock,GasOutOfSourceRock; //分别为运移到源岩外的累计的油和气量
			double OGIFromKerogen,GGIFromKerogen; //指源岩干酪根累积生油量和生气量 ，代替以前的OGI_LLNL和GGI_LLNL ，含义也有所不同，这里得出的量只是干酪根生成的油量和气量，而没有考虑油裂解减少的油量和增加的气量
			double OilCrackedAdded; //源岩中累积的油裂解量
			double GasCrackedAdded; //源岩中累积的气裂解量
			double CokeAdded;//源岩中油裂解产生的焦炭量
			double TR; //源岩的油气转化率
			
			void GetaG()
			{  //根据温度和压力获得干酪根对气的吸附系数
				aG=0.0067+0.0094*log(Pm/1.0e6)-0.000062*Tm;
				if(aG<0)aG=0.;
			}

			void GetGeneratedOilAndGas()
			{ //获得生成的油气量等  ,仅针对第一个时间步
				//获得通过这一步的干酪根裂解和油裂解后得到的源岩中的油和气量 ，暂时先没有考虑排的问题
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->OilCrackToGas(SurfaceT,BeginAge,Tm,EndAge);  //使用的是上一步源岩中存在的油量 ，因此最先运行该函数，下面的量都是指在该时间步运行结束时该时间步存在的量
					OGIFromKerogen=aParaLLNL->OilGenerated*aParaLLNL->MassOfInitTOCTotal;
					GGIFromKerogen=aParaLLNL->GasGenerated*aParaLLNL->MassOfInitTOCTotal;
					CokeAdded=aParaLLNL->ResidueCrackedAdded; //对于第一个时间步，累计焦炭量为0
					break;
				case Organo:
					aOrganofacies->OilCrackToGas(SurfaceT,BeginAge,Tm,EndAge);  //使用的是上一步源岩中存在的油量 ，因此最先运行该函数，下面的量都是指在该时间步运行结束时该时间步存在的量
					OGIFromKerogen=aOrganofacies->OilGenerated*aOrganofacies->MassOfInitTOCTotal;
					GGIFromKerogen=aOrganofacies->GasGenerated*aOrganofacies->MassOfInitTOCTotal;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //对于第一个时间步，累计焦炭量为0
					break;
				};
			}
			
			void GetMAdxAndExpOfOilAndGas()
			{  //获得源岩中的吸附油气量和排油气量 ，包括生油气量部分  ,仅针对第一个时间步
				GetGeneratedOilAndGas();  //获得生成的油气量等
				GetaG(); //获得干酪根对气的吸附系数
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->GetMKer(); //获得干酪跟含量
					MKer=aParaLLNL->MKerTotal;
					MKerReac=aParaLLNL->MKerReac;
					MKerInert=aParaLLNL->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //源岩能吸附的最大油量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					MAdxMaxGas=aG*(MKer+CokeAdded);  //源岩能吸附的最大气量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					if(aParaLLNL->OilExisted<=MAdxMaxOil) {MAdxOil=aParaLLNL->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aParaLLNL->OilExisted-MAdxOil;     }
					if(aParaLLNL->GasExisted<=MAdxMaxGas) {MAdxGas=aParaLLNL->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aParaLLNL->GasExisted-MAdxGas;     }
					MExpOilAdded=MExpOil;   //累积排油量
					MExpGasAdded=MExpGas;   //累积排气量
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;    //假设源岩孔隙的油气量为0
					MResidualOil=MAdxOil+OilInSourceRockPoros;// 源岩残余油量,包括干酪根吸附量和孔隙油量，这里暂时假设孔隙含油量为0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// 源岩残余气量,包括干酪根吸附量和孔隙气量，这里暂时假设孔隙含气量为0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aParaLLNL->OilExisted=MResidualOil; //现在源岩中的存在的油量为源岩残余油量
					aParaLLNL->GasExisted=MResidualGas; //现在源岩中的存在的气量为源岩残余油量
					OilCrackedAdded=aParaLLNL->OilCrackedAdded;
					GasCrackedAdded=aParaLLNL->GasCrackedAdded;
					CokeAdded=aParaLLNL->ResidueCrackedAdded; //
					TR=aParaLLNL->TR;
					break;
				case Organo:
					aOrganofacies->GetMKer(); //获得干酪跟含量
					MKer=aOrganofacies->MKerTotal;
					MKerReac=aOrganofacies->MKerReac;
					MKerInert=aOrganofacies->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //源岩能吸附的最大油量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					MAdxMaxGas=aG*(MKer+CokeAdded);  //源岩能吸附的最大气量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					if(aOrganofacies->OilExisted<=MAdxMaxOil) {MAdxOil=aOrganofacies->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aOrganofacies->OilExisted-MAdxOil;     }
					if(aOrganofacies->GasExisted<=MAdxMaxGas) {MAdxGas=aOrganofacies->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aOrganofacies->GasExisted-MAdxGas;     }
					MExpOilAdded=MExpOil;   //累积排油量
					MExpGasAdded=MExpGas;   //累积排气量
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;    //假设源岩孔隙的油气量为0
					MResidualOil=MAdxOil+OilInSourceRockPoros;// 源岩残余油量,包括干酪根吸附量和孔隙油量，这里暂时假设孔隙含油量为0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// 源岩残余气量,包括干酪根吸附量和孔隙气量，这里暂时假设孔隙含气量为0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aOrganofacies->OilExisted=MResidualOil; //现在源岩中的存在的油量为源岩残余油量
					aOrganofacies->GasExisted=MResidualGas; //现在源岩中的存在的气量为源岩残余油量
					OilCrackedAdded=aOrganofacies->OilCrackedAdded;
					GasCrackedAdded=aOrganofacies->GasCrackedAdded;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //
					TR=aOrganofacies->TR;
					break;
				};
			}
			
			void GetGeneratedOilAndGas(StrSeg *StrSegLeft)
			{ //获得生成的油气量和存在于源岩的油气量
				//首先获得通过这一步的干酪根裂解和油裂解后得到的源岩中的油和气量 ，暂时先没有考虑排的问题
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->OilCrackToGas(StrSegLeft->Tm,BeginAge,Tm,EndAge,StrSegLeft->aParaLLNL );
					OGIFromKerogen=aParaLLNL->OilGenerated*aParaLLNL->MassOfInitTOCTotal;
					GGIFromKerogen=aParaLLNL->GasGenerated*aParaLLNL->MassOfInitTOCTotal;
					CokeAdded=aParaLLNL->ResidueCrackedAdded;   //焦炭量等于上一时间步的裂解残余累积量，因为在该函数运行于该时间步油裂解之前
					break;
				case Organo:
					aOrganofacies->OilCrackToGas(StrSegLeft->Tm,BeginAge,Tm,EndAge,StrSegLeft->aOrganofacies);  //使用的是上一步源岩中存在的油量 ，因此最先运行该函数，下面的量都是指在该时间步运行结束时该时间步存在的量
					OGIFromKerogen=aOrganofacies->OilGenerated*aOrganofacies->MassOfInitTOCTotal;
					GGIFromKerogen=aOrganofacies->GasGenerated*aOrganofacies->MassOfInitTOCTotal;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //
					break;
				};
			}
			
			void GetMAdxAndExpOfOilAndGas(StrSeg *StrSegLeft)
			{  //获得源岩中的吸附油气量和排油气量 ，包括生油气量部分
				GetGeneratedOilAndGas(StrSegLeft);
				GetaG(); //获得干酪根对气的吸附系数
				switch(aPetroGenStyle)
				{
				case LLNL:
					aParaLLNL->GetMKer(); //获得干酪跟含量
					MKer=aParaLLNL->MKerTotal;
					MKerReac=aParaLLNL->MKerReac;
					MKerInert=aParaLLNL->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //源岩能吸附的最大油量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					MAdxMaxGas=aG*(MKer+CokeAdded);  //源岩能吸附的最大气量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					if(aParaLLNL->OilExisted<=MAdxMaxOil) {MAdxOil=aParaLLNL->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aParaLLNL->OilExisted-MAdxOil;     }
					if(aParaLLNL->GasExisted<=MAdxMaxGas) {MAdxGas=aParaLLNL->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aParaLLNL->GasExisted-MAdxGas;     }
					MExpOilAdded=StrSegLeft->MExpOilAdded+MExpOil;
					MExpGasAdded=StrSegLeft->MExpGasAdded+MExpGas;
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;
					MResidualOil=MAdxOil+OilInSourceRockPoros;// 源岩残余油量,包括干酪根吸附量和孔隙油量，这里暂时假设孔隙含油量为0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// 源岩残余气量,包括干酪根吸附量和孔隙气量，这里暂时假设孔隙含气量为0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aParaLLNL->OilExisted=MResidualOil; //现在源岩中的存在的油量为源岩残余油量
					aParaLLNL->GasExisted=MResidualGas; //现在源岩中的存在的气量为源岩残余油量
					OilCrackedAdded=aParaLLNL->OilCrackedAdded;
					GasCrackedAdded=aParaLLNL->GasCrackedAdded;
					CokeAdded=aParaLLNL->ResidueCrackedAdded; //
					TR=aParaLLNL->TR;
					break;
				case Organo:
					aOrganofacies->GetMKer(); //获得干酪跟含量
					MKer=aOrganofacies->MKerTotal;
					MKerReac=aOrganofacies->MKerReac;
					MKerInert=aOrganofacies->MKerInert;
					MAdxMaxOil=aO*(MKer+CokeAdded);  //源岩能吸附的最大油量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					MAdxMaxGas=aG*(MKer+CokeAdded);  //源岩能吸附的最大气量---有机碳量包括残余干酪根量和油裂解的残余物量两部分
					if(aOrganofacies->OilExisted<=MAdxMaxOil) {MAdxOil=aOrganofacies->OilExisted; MExpOil=0.; }
					else {MAdxOil=MAdxMaxOil; MExpOil=aOrganofacies->OilExisted-MAdxOil;     }
					if(aOrganofacies->GasExisted<=MAdxMaxGas) {MAdxGas=aOrganofacies->GasExisted; MExpGas=0.; }
					else {MAdxGas=MAdxMaxGas; MExpGas=aOrganofacies->GasExisted-MAdxGas;     }
					MExpOilAdded=StrSegLeft->MExpOilAdded+MExpOil;
					MExpGasAdded=StrSegLeft->MExpGasAdded+MExpGas;
					OilInSourceRockPoros=0.;GasInSourceRockPoros=0.;
					MResidualOil=MAdxOil+OilInSourceRockPoros;// 源岩残余油量,包括干酪根吸附量和孔隙油量，这里暂时假设孔隙含油量为0
					MResidualGas=MAdxGas+GasInSourceRockPoros;// 源岩残余气量,包括干酪根吸附量和孔隙气量，这里暂时假设孔隙含气量为0
					OilOutOfSourceRock=MExpOilAdded-OilInSourceRockPoros;
					GasOutOfSourceRock=MExpGasAdded-GasInSourceRockPoros;
					aOrganofacies->OilExisted=MResidualOil; //现在源岩中的存在的油量为源岩残余油量
					aOrganofacies->GasExisted=MResidualGas; //现在源岩中的存在的气量为源岩残余油量
					OilCrackedAdded=aOrganofacies->OilCrackedAdded;
					GasCrackedAdded=aOrganofacies->GasCrackedAdded;
					CokeAdded=aOrganofacies->ResidueCrackedAdded; //
					TR=aOrganofacies->TR;
					break;
				};
			}

			// double MKerReacInit;//初始时刻反应干酪根的量，单位：kg
			// double rKerInert; //初始时刻无效干酪根的比例
			// double TRO,TRG; //Transformation Ratio 烃转化比例 ,值在[0-1] 之间,分别是油和气的
			 double SoTreshold;   //临界排油饱和度，值在[0-1]之间
			 double SgTreshold;   //临界排气饱和度，值在[0-1]之间




			 //================== flash Calculation Start ,相态计算相关

			// double Rs; //溶解油气比, m3/m3
			 double Sgg; //气体相对密度   ；Good Oil: Sgg= 0.855
			 double Soo;//油的相对密度     ; Good Oil:  Soo=0.823
			 double T_F; //华氏温度
			// double Coeff_a; //泡点公式中的系数
			// void GetT_FFromCelsiusDegree(){  T_F=32.+Tm*1.8;   } //摄氏度转为华氏度
			// void GetCoeff_a(){GetT_FFromCelsiusDegree(); Coeff_a=0.00091*T_F-0.0125*API;}
			// void Getpb(){GetCoeff_a(); pb=18.2*(pow(Rs/Sgg,0.83)*pow(10.,Coeff_a)-1.4);  } //获得油的泡点压力
			 double MolFraC1InWater; //molar fraction of methane in water
			 void GetMolFraC1InWater() //获得甲烷在水中溶解的摩尔比例 ，原文公式可能还有问题，有待查证
			   {MolFraC1InWater=-55.811+7478.84/TmK+20.6794*log(TmK/100.)+0.753158*log(PmMPa);}
			 double nl,nv; //分别是液态和气态的摩尔分数
			 int NCom; //有N个组分的烃类
			 Properties *aProperties;
			 double *x,*y,*z;  //分别为在液相中的组分摩尔比例/分数，在气相中的组分摩尔比例/分数，总的组分摩尔分数
			 double *K; // The equality of fugacity can be expressed by the equilibrium ratio, K,  K[i] = y[i] / x[i]
			 double *MW;       //组分摩尔质量  kg/kgmol
			 double *Tci,*Pci,*vci; //组分临界温度、压力和体积   K，MPa，m^3/kmol
			 double *Omegai; //the dimensionless acentric factor,各组分的
			 double **kij; //binary interaction parameter 二元相互作用参数
			 double R;//气体常数 ，=0.008314;0.008314 KJ/(mol*K)
			HCType aHCType;
			void GetProperties(int aNCom,Properties *aProperties,double **akij,EOS aaEOS)
			 {    //获得黑油模型组分参数
				 
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
				 Ai=new double[NCom];Bi=new double[NCom]; //没用上
				 FaiiL=new double[NCom]; FaiiV=new double[NCom];
				 fiL=new double[NCom]; fiV=new double[NCom];
				 xSC=new double[NCom]; ySC=new double[NCom];
				 KSC=new double[NCom];
				 for(int i=0;i<NCom;i++)
				  {
					MW[i]=aProperties[i].MW; Tci[i]=aProperties[i].Tc; Pci[i]=aProperties[i].Pc;
					Omegai[i]=aProperties[i].Omega; z[i]=aProperties[i].z;vci[i]=aProperties[i].Vc;/**/
				  }
				 R=0.008314;//气体常数 ，
				 aEOS=aaEOS;
				 for(int i=0;i<NCom;i++)for(int j=0;j<NCom;j++)kij[i][j]=akij[i][j];
				 SCT=15.556+273.15; //标准条件下的温度15.556摄氏度
				 SCP=0.101325; //标准条件下的压力1 atm 0.1MPa
			 }

			void GetProperties()
			 {  //两组分C1和nC10的混合体系参数，
				
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
				 Ai=new double[NCom];Bi=new double[NCom]; //没用上
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
				   R=0.008314;;//气体常数 ，
				   SCT=15.556+273.15; //标准条件下的温度15.556摄氏度
				   SCP=0.101325; //标准条件下的压力1 atm 0.1MPa
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

			 double SCT; //标准条件下的温度15.556摄氏度
			 double SCTK; // 标准条件下的温度开氏温度
			 double SCP; //标准条件下的压力1 atm 0.1MPa
			 double pb; //体系的泡点压力 ，MPa
			 double TmK; //中部温度，用开氏温度表示，用于相态计算
			 double PmMPa; //中部压力，用兆帕表示，用于相态计算
			 double pTc; //准临界温度 K   pseudo critical temperature  ,赋给初值为体系温度
			 double pPc; //准临界压力 MPa
			 double a,b; //分别对应于临界相态的a值和b值
			 double vL,vV;  //分别是油和气的摩尔体积  m3/kgmol
			 double MWL,MWV; //分别是油相和气相的摩尔质量
			 double *aci,*bi,*mi,*Alphai,*ai;
			 double *Ai,*Bi; //
			 double aL,bL,aV,bV; //分别对应于油和气的a值和b值
			 EOS aEOS;
			 double AL,AV,BL,BV; // 分别对应于油和气
			 double ZL,ZV; //液体和气体，即油和气的压缩系数
			 double *FaiiL,*FaiiV; //分别为油、气相态中组分的逸度系数（fugacity coefficients）
			 double *fiL,*fiV; //分别为油、气相态中组分的逸度（fugacities）

			void GetpTcpPc()
			{   //用于计算临界温度和压力,通过迭代法获得， --用于混合物
				 double pTcInit=0;
				 for(int i=0;i<NCom;i++) pTcInit+=z[i]*Tci[i];
				 pTc=pTcInit;  //给pTC赋初值
				 double pTctemp=pTc; //
				 double wc; //前后两次迭代的温度差绝对值
				 double wcx=0.01; //判断收敛到结果的误差值
				 int NLoop=0;
				do
				{
				 NLoop++; //如果循环数达到某一数值还没收敛，则跳出循环
				 b=0; a=0;  //赋初值为0
				 for(int i=0;i<NCom;i++)
				 {
				  switch(aEOS)
				  {
				   case SRK:
				   aci[i]=0.42747*R*R*Tci[i]*Tci[i]/Pci[i];      //Danish,1998 P140  4.22
				   bi[i]=0.08664*R*Tci[i]/Pci[i];            //Danish,1998 P140  4.22
				   mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
				   break;
				   case PR:
				   aci[i]=0.457235*R*R*Tci[i]*Tci[i]/Pci[i];    //Danish,1998 P141  4.27
				   bi[i]=0.077796*R*Tci[i]/Pci[i];          //Danish,1998 P141  4.27
				   mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(pTc/Tci[i])))*(1.+mi[i]*(1.-sqrt(pTc/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
				   break;
				  };
				 }
				 for(int i=0;i<NCom;i++)
				 {    //混合规则  Mixture parameters
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
				{ //如果过了100次还没收敛，则将其值等于各组分临界温度的摩尔平均值
				  pTc=pTcInit;
				}
			}
			double GetVOfRRE(double aPoint) //获得Rachford-Rice方程值 Danesh 1998, (5.6)P169
			   {    //  int NCom,double *z,double *K,
				 double tempV=0;
				 for(int i=0;i<NCom;i++)
					tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*aPoint);
				 return tempV;
			   }
			void GetInitKi()
			   { //获得每一组分的初始的平衡比Ki，Danesh 1998, (3.66)P122    int NCom,double *K, double *Pci,double PmMPa, double *Omegai,double *Tci,double TmK
				  for(int i=0;i<NCom;i++) K[i]=Pci[i]/PmMPa*exp(5.37*(1.+Omegai[i])*(1.-Tci[i]/TmK));
			   }
			void GetParasOfComsInEOS(double *xi,double &aLV,double &bLV) //获得状态方程中各组分的参数
			{ //
				 bLV=0; aLV=0;  //赋初值为0
				 for(int i=0;i<NCom;i++)
				 {
				  switch(aEOS)
				  {
				   case SRK:
				   aci[i]=0.42747*R*R*Tci[i]*Tci[i]/Pci[i];      //Danish,1998 P140  4.22
				   bi[i]=0.08664*R*Tci[i]/Pci[i];            //Danish,1998 P140  4.22
				   mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmK/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmK/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
				   Ai[i]=ai[i]*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7  虽然计算了，但暂时没有用到
				   Bi[i]=bi[i]*PmMPa/(R*TmK);              //Danish,1998 P132  4.8   虽然计算了，但暂时没有用到
				   break;
				   case PR:
				   aci[i]=0.457235*R*R*Tci[i]*Tci[i]/Pci[i];    //Danish,1998 P141  4.27
				   bi[i]=0.077796*R*Tci[i]/Pci[i];          //Danish,1998 P141  4.27
				   mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
				   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmK/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmK/Tci[i]))); //Danish,1998 P140  4.23
				   ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
				   Ai[i]=ai[i]*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7     虽然计算了，但暂时没有用到
				   Bi[i]=bi[i]*PmMPa/(R*TmK);              //Danish,1998 P132  4.8      虽然计算了，但暂时没有用到
				   break;
				  };
				 }
				 for(int i=0;i<NCom;i++)
				 {    //混合规则  Mixture parameters
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
			void GetFaii(double *Faii,double *xx,double aLV,double bLV,double A,double B,double Z)   //计算逸度系数 Danish,1998 p157 E4.5
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
			 {    //获得油气相态组分的逸度以及组分的平衡比  int NCom,double *fiL,double *fiV,double *FaiiL,double *FaiiV,double *K,double *x,double *y,double PmMPa
			   for(int i=0;i<NCom;i++)  { fiL[i]=FaiiL[i]*x[i]*PmMPa;  fiV[i]=FaiiV[i]*y[i]*PmMPa; K[i]=FaiiL[i]/FaiiV[i];/*if(fabs(K[i])<1e-8)ShowMessage("fabs(K[i])="+FloatToStr(K[i]));*/}
			 }
			void Getfi_KSC()
			 {    //获得油气相态组分的逸度以及组分的平衡比  int NCom,double *fiL,double *fiV,double *FaiiL,double *FaiiV,double *K,double *x,double *y,double PmMPa
			   for(int i=0;i<NCom;i++)  { fiL[i]=FaiiL[i]*xSC[i]*SCP;  fiV[i]=FaiiV[i]*ySC[i]*SCP; KSC[i]=FaiiL[i]/FaiiV[i];/*if(fabs(K[i])<1e-8)ShowMessage("fabs(K[i])="+FloatToStr(K[i]));*/}
			 }
			void GetErrorValue_fiLfiV(double &ErrorValue_fiLfiV) // ,int NCom,double *fiL,double *fiV
			  {     //Danish,1998  P174
				ErrorValue_fiLfiV=0;
				for(int i=0;i<NCom;i++) ErrorValue_fiLfiV+=(1.-fiL[i]/fiV[i])*(1.-fiL[i]/fiV[i]);
			  }
			 void BubblePressureAdjusted()//调整压力使其接近泡点压力 Danesh 1998,P174  (E5.2')
			 {
				 double tempSum=0;
				 for(int i=0;i<NCom;i++) tempSum+=x[i]*K[i];
				 pb=pb*tempSum;
			 }
			/*void DewPressureAdjusted(int NCom,double &PmMPa,double *y,double *K)//调整压力使其接近露点压力 Danesh 1998,P174  (E5.2')
			 {
				 double tempSum=0;
				 for(int i=0;i<NCom;i++) tempSum+=y[i]/K[i];
				 PmMPa=PmMPa*tempSum;
			 }  */
			void GetvLvV() //获得油气的摩尔体积  Danish,1998 P40 2.5
			  { //  double &vL,double &vV,double R,double TmK,double ZL,double ZV,double PmMPa
				  vL=R*TmK*ZL/PmMPa;
				  vV=R*TmK*ZV/PmMPa;
			  }
			  void GetvLvVSC() //获得标准条件下的油气的摩尔体积  Danish,1998 P40 2.5
			  { //
				  vLSC=R*SCT*ZL/SCP;
				  vVSC=R*SCT*ZV/SCP;
			  }
			void GetMWLMWV(double *xx,double *yy) //获得油相和气相的摩尔质量
			  {  // int NCom,double &MWL,double &MWV,double *MW,
				MWL=0;MWV=0;
				for(int i=0;i<NCom;i++)
				 {
				   MWL+=xx[i]*MW[i];
				   MWV+=yy[i]*MW[i];
				 }
			  }
			void GetMWLMWVSC(double *xx,double *yy) //获得标准条件下的油相和气相的摩尔质量
			  {
				MWLSC=0;MWVSC=0;
				for(int i=0;i<NCom;i++)
				 {
				   MWLSC+=xx[i]*MW[i];
				   MWVSC+=yy[i]*MW[i];
				 }
			  }
			void GetLVDensity() {OilDensity=MWL/vL; GasDensity=MWV/vV;}//获得油、气相的密度
			void GetLVDensitySC() {OilDensitySC=MWLSC/vLSC; GasDensitySC=MWVSC/vVSC;}//获得标准条件下的油、气相的密度
			void GetLDensity() {OilDensity=MWL/vL; }  //获得油相密度
			void GetLDensitySC() {OilDensitySC=MWLSC/vLSC; }  //获得标准条件下的油相密度
			void GetVDensity() {GasDensity=MWV/vV; }  //获得气相密度
			void GetVDensitySC() {GasDensitySC=MWVSC/vVSC; }  //获得标准条件下的气相密度
			void GetBubblePointPressure()
			{
				double aa,bb,cc,dd; //cubic EOS --三次状态方程的系数
				double ObjectiveValueInFlash; //Danish,1998  P174     =1.0e-12;
				double ErrorValue_fiLfiV;
				ObjectiveValueInFlash=1.0e-12;
				SolutionOfCE aSCEZ;
				GetInitKi();
				pb=PmMPa; //初始的泡点压力赋值为地层压力
				do
				{
				 for(int i=0;i<NCom;i++)x[i]=z[i]; //将体系中的组分摩尔比赋值给液相中的组分摩尔比
				 for(int i=0;i<NCom;i++)y[i]=K[i]*x[i];  //泡点压力时，体系中的组分摩尔比就是液相中的组分摩尔比
				 GetParasOfComsInEOS(x,aL,bL); //求对应于油相的a,b
				 AL=aL*pb/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
				 BL=bL*pb/(R*TmK);              //Danish,1998 P132  4.8
				 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数   ,aEOS
				 aSCEZ=CubicEquation(aa,bb,cc,dd);
				 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; /* 有一个三重根和一个实根的情况ShowMessage("ZL="+FloatToStr(ZL)); */   }
				 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); /* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */  }
				 GetParasOfComsInEOS(y,aV,bV); //求对应于油相的a,b
				 AV=aV*pb/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
				 BV=bV*pb/(R*TmK);              //Danish,1998 P132  4.8
				 GetaEOSParas(aa,bb,cc,dd,AV,BV); //计算 对应于油相的cubic EOS --三次状态方程的系数   ,aEOS
				 aSCEZ=CubicEquation(aa,bb,cc,dd);
				 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; /* 有一个三重根和一个实根的情况ShowMessage("ZL="+FloatToStr(ZL)); */   }
				 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); /* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */  }
				 GetFaii(FaiiL,z,aL,bL,AL,BL,ZL) ; //求油相的逸度系数
				 GetFaii(FaiiV,y,aV,bV,AV,BV,ZV) ; //求气相的逸度系数
				 Getfi_K();    //获得油气相态组分的逸度以及组分的平衡比   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
				 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
				 BubblePressureAdjusted();
				}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);
			}
			double NewtonIterationFornv(double aPoint) //用牛顿迭代法求nv
			 {
				   double tempV; //函数值
				   double tempVD;  //导数值
				   double nv01,nv02; //返回值
				   double wc;
				   double num=0;
				   nv01=aPoint;
				   do
				   {
					num++;
					tempV=0;
					tempVD=0;
					for(int i=0;i<NCom;i++)
					 tempV+=z[i]*(K[i]-1.0)/(1.0+(K[i]-1.0)*nv01);    //获得Rachford-Rice方程值 Danesh 1998, (5.6)P169
					for(int i=0;i<NCom;i++)
					 tempVD+=-z[i]*(K[i]-1.)*(K[i]-1.)/pow(1.+(K[i]-1.0)*nv01,2.);  //获得Rachford-Rice方程导数值
					nv02=nv01-tempV/tempVD;
					wc=fabs(nv02-nv01);
					nv01=nv02;
				   }while(wc>1.0e-10&&num<1000);
				   return nv02;
			 }
			double OilDensitySC; //标准条件下原油的密度
			double API; //标准条件下油的重度
			double GOR;//气油比  m3/m3
			double Bo; //原油体积系数，定义为地下原油体积与地面原油体积之比
			double *KSC;
			double nvSC,nlSC;    //标准条件下气相和油相的摩尔比
			double *xSC,*ySC;
			double MWLSC,vLSC,MWVSC,vVSC;
			double GasDensitySC; // 标准条件下气相密度
			void GetInitKi(int NCom,double *KK, double *Pci,double Pmm, double *Omegai,double *Tci,double Tmm)
			   { //获得每一组分的初始的平衡比Ki，Danesh 1998, (3.66)P122
				  for(int i=0;i<NCom;i++) KK[i]=Pci[i]/Pmm*exp(5.37*(1.+Omegai[i])*(1.-Tci[i]/Tmm));
			   }
			void GetParasOfComsInEOS(int NCom,double *xiI,double **kij,double *Tci,double *pci, double TmM,double PmM,double *Omegai,double R,double &a,double &b,double *aci,double *bi,double *mi,double *Alphai, double *ai,double *Ai,double *Bi,EOS aEOS) //获得状态方程中各组分的参数
			{
			 b=0; a=0;  //赋初值为0
			 for(int i=0;i<NCom;i++)
			 {
			  switch(aEOS)
			  {
			   case SRK:
			   aci[i]=0.42747*R*R*Tci[i]*Tci[i]/pci[i];      //Danish,1998 P140  4.22
			   bi[i]=0.08664*R*Tci[i]/pci[i];            //Danish,1998 P140  4.22
			   mi[i]=0.480+1.574*Omegai[i]-0.176*Omegai[i]*Omegai[i]; //Danish,1998 P140  4.24
			   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmM/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmM/Tci[i]))); //Danish,1998 P140  4.23
			   ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
			   Ai[i]=ai[i]*PmM/(R*TmM*R*TmM);          //Danish,1998 P132  4.7  虽然计算了，但暂时没有用到
			   Bi[i]=bi[i]*PmM/(R*TmM);              //Danish,1998 P132  4.8   虽然计算了，但暂时没有用到
			   break;
			   case PR:
			   aci[i]=0.457235*R*R*Tci[i]*Tci[i]/pci[i];    //Danish,1998 P141  4.27
			   bi[i]=0.077796*R*Tci[i]/pci[i];          //Danish,1998 P141  4.27
			   mi[i]=0.3796+1.485*Omegai[i]-0.1644*Omegai[i]*Omegai[i]+0.01667*Omegai[i]*Omegai[i]*Omegai[i]; //Danish,1998 P141  4.29
			   Alphai[i]=(1.+mi[i]*(1.-sqrt(TmM/Tci[i])))*(1.+mi[i]*(1.-sqrt(TmM/Tci[i]))); //Danish,1998 P140  4.23
			   ai[i]=aci[i]*Alphai[i]; //参考Danish,1998 P144 Example 4.4    p136 4.19
			   Ai[i]=ai[i]*PmM/(R*TmM*R*TmM);          //Danish,1998 P132  4.7     虽然计算了，但暂时没有用到
			   Bi[i]=bi[i]*PmM/(R*TmM);              //Danish,1998 P132  4.8      虽然计算了，但暂时没有用到
			   break;
			  };
			 }
			 for(int i=0;i<NCom;i++)
			 {    //混合规则  Mixture parameters
			  b+=xiI[i]*bi[i];   //Danish,1998 P155  4.74
			   for(int j=0;j<NCom;j++)
				 a+=xiI[i]*xiI[j]*sqrt(ai[i]*ai[j])*(1.-kij[i][j]);   //Danish,1998 P155  4.78
			 }
			}
			double NewtonIterationFornv(int NCom1,double *zZ,double *KK, double aPoint) //用牛顿迭代法求nv
			 {
			   double tempV; //函数值
			   double tempVD;  //导数值
			   double nv01,nv02; //返回值
			   double wc;
			   nv01=aPoint;
			  double num=0;
			   do
			   {
				 num++;
				tempV=0;
				tempVD=0;
				for(int i=0;i<NCom1;i++)
				 tempV+=zZ[i]*(KK[i]-1.0)/(1.0+(KK[i]-1.0)*nv01);  //获得Rachford-Rice方程值 Danesh 1998, (5.6)P169
				for(int i=0;i<NCom1;i++)
				 tempVD+=-zZ[i]*(KK[i]-1.)*(KK[i]-1.)/pow(1.+(KK[i]-1.0)*nv01,2);  //获得Rachford-Rice方程导数值
				nv02=nv01-tempV/tempVD;
				wc=fabs(nv02-nv01);
				nv01=nv02;
			   }while(wc>1.0e-10);      // &&num<1000
			   return nv02;
			 }
			void GetGOR()
			  {   //气油比
				if(nvSC<=0) GOR=0;
				else if(nvSC>=1) GOR=-1;
				else GOR=vVSC*nvSC/(vLSC*nlSC);
			  }
			void GetBo()
			  { //体积系数
				if(nvSC<1)
				Bo=OilDensitySC/OilDensity;
				else Bo=-1; //负数代表地下无油相
			  }
			void FlashCalculationSC()    //地面标准条件下的计算的油气性质
			{ ////flash calculation start
			//先只是考虑油气两组分的情况，而没有多组分，只是对生成的油和气进行相态计算
			z[0]=GGIFromKerogen/MW[0]; //气的摩尔数
			z[1]=OGIFromKerogen/MW[1]; //油的摩尔数
			double tteemm=z[0]+z[1];
			z[0]=z[0]/tteemm; //气的摩尔比
			z[1]=z[1]/tteemm; //油的摩尔比
			if(z[0]<1.0e-5){ z[0]=1.0e-5;z[1]=1.0-z[0];}
			if(z[1]<1.0e-5){ z[1]=1.0e-5;z[0]=1.0-z[1];}  
			SolutionOfCE aSCEZ;
			double ObjectiveValueInFlash; //Danish,1998  P174     =1.0e-12;
			double ErrorValue_fiLfiV;
			double XigemaKizi;
			double XigemaziBiKi;
			double wcx=1.e-5;
			double nvLeftPoint; //二分法nv左端点，  初始值为0
			double nvRightPoint; //二分法nv右端点， 初始值为1
			double nvMiddlePoint; //二分法的中间点，为左右端点和的一半
			double aa,bb,cc,dd; //cubic EOS --三次状态方程的系数
			ObjectiveValueInFlash=1.0e-12;
			double KiMin,KiMax; //记录组分的平衡比的最小值和最大值
			GetpTcpPc();  //获得混合物准临界温度和压力值，用于判断混合物温度是否超过临界温度，如果超过则不进行闪蒸计算，而是直接计算密度
			if(SCT<pTc)
			{  //如果体系温度没超过准临界温度，则进行闪蒸计算 ————开始
			GetInitKi(NCom,KSC,Pci,SCP,Omegai,Tci,SCT);    //获得每一组分的初始的平衡比Ki，Danesh 1998, (3.66)P122
			do
			{
			KiMin=KSC[0];KiMax=KSC[0];
			for(int i=1;i<NCom;i++) {if(KSC[i]<KiMin) KiMin=KSC[i]; if(KSC[i]>KiMax) KiMax=KSC[i];}
			if(fabs(1-KiMax)<1e-10||fabs(1-KiMin)<1e-10)  {nvSC=-10000.; break;}
			   nvLeftPoint=1./(1.-KiMax); //nv值域左端点   ,Whitson 1989 The negative flash  P52
			   nvRightPoint=1./(1.-KiMin); //nv值域右端点  ,Whitson 1989 The negative flash  P52
			   nvMiddlePoint=(nvLeftPoint+nvRightPoint)/2.;  //初始值
			   nvSC=NewtonIterationFornv(NCom,z,KSC,nvMiddlePoint); //用牛顿迭代法求nv
			   nlSC=1-nvSC;
				for(int i=0;i<NCom;i++)
				  {
					xSC[i]=z[i]/(1.0+(KSC[i]-1.0)*nvSC);
					ySC[i]=z[i]*KSC[i]/(1.0+(KSC[i]-1.0)*nvSC);
				  }
			 GetParasOfComsInEOS(NCom,xSC,kij,Tci,Pci,SCT,SCP,Omegai,R,aL,bL,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS);
			 AL=aL*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BL=bL*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* 有一个三重根和一个实根的情况*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);}/* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根;;有三个根的情况下要选择其中的最大值 */
			 GetParasOfComsInEOS(NCom,ySC,kij,Tci,Pci,SCT,SCP,Omegai,R,aV,bV,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS); //求对应于气相的a,b
			 AV=aV*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BV=bV*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AV,BV); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; } /* 有一个三重根和一个实根的情况 */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); } /* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
			 GetFaii(FaiiL,xSC,aL,bL,AL,BL,ZL) ; //求油相的逸度系数
			 GetFaii(FaiiV,ySC,aV,bV,AV,BV,ZV) ; //求气相的逸度系数
			 Getfi_KSC();    //获得油气相态组分的逸度以及组分的平衡比   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
			 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
			}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);   //  &&runtimes<=100
			////////////////////////////////--------------------------------------------
			if(nvSC<=0||nvSC>=1)
			{ //nv<0,表明 体系为单一的液相，nv>1,表明体系是单一的气相，利用下面计算密度
			 GetParasOfComsInEOS(NCom,z,kij,Tci,Pci,SCT,SCP,Omegai,R,aL,bL,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS);
			 AL=aL*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BL=bL*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(nvSC<=0)
			 { //nv<0,表明 体系为单一的液相
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* 有一个三重根和一个实根的情况 */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }/* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
			 GetvLvVSC(); //获得油气的摩尔体积  Danish,1998 P40 2.5
			 GetMWLMWVSC(z,ySC); //获得油相和气相的摩尔质量  ,由于是单一的油相，因此用z代替x，而气相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vVSC=1.;
			 GetLDensitySC(); //获得油相的密度
			 API=141.5/(OilDensitySC/1000.)-131.5; //where So is the stock tank oil specific gravity, or relative density, to water at 60°F
			 GetGOR();
			 GetBo();
			 }
			 if(nvSC>=1)
			 { //nv>1,表明体系是单一的气相
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; }  // 有一个三重根和一个实根的情况
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }// 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根
			 GetvLvVSC(); //获得油气的摩尔体积  Danish,1998 P40 2.5   ,
			 GetMWLMWVSC(xSC,z); //获得油相和气相的摩尔质量 ,由于是单一的气相，因此用z代替y，而油相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vLSC=1.;
			 GetVDensitySC(); //获得气相的密度
			 GetGOR();
			 GetBo();
			 }
			}
			else
			{ //以下为两相体系
			 GetvLvVSC(); //获得油气的摩尔体积  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWVSC(xSC,ySC); //获得油相和气相的摩尔质量   NCom,MWL,MWV,MW,
			 GetLVDensitySC(); //获得油、气相的密度  OilDensity,GasDensity,vL,vV,MWL,MWV
			 API=141.5/(OilDensitySC/1000.)-131.5; //where So is the stock tank oil specific gravity, or relative density, to water at 60°F
			 GetGOR();
			 GetBo();
			}
			}  //如果体系温度没超过准临界温度，则进行闪蒸计算  ————结束
			if(SCT>=pTc)
			{  //如果体系温度大于准临界温度，则只进行单相的PVT计算  ，这里用“L”来对该单相进行计算
			 nvSC=-2; //代表为超临界流体
			 GetParasOfComsInEOS(NCom,z,kij,Tci,Pci,SCT,SCP,Omegai,R,aL,bL,aci,bi,mi,Alphai,ai,Ai,Bi,aEOS);
			 AL=aL*SCP/(R*SCT*R*SCT);          //Danish,1998 P132  4.7
			 BL=bL*SCP/(R*SCT);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1;}  /* 有一个三重根和一个实根的情况 ShowMessage("单实根或三重实根");*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);} /* ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);ShowMessage("三个实根");有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
											   //之所以选择最大值是因为最小值在计算结果上为负数，而最大值通过验算符合实际
			 GetvLvVSC(); //获得油气的摩尔体积  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWVSC(z,ySC); //获得油相和气相的摩尔质量  ,由于是单一的油相，因此用z代替x，而气相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vV=1.;
			 GetLDensitySC(); //获得该体系（油相代替）的密度
			 API=141.5/(OilDensitySC/1000.)-131.5; //where So is the stock tank oil specific gravity, or relative density, to water at 60°F
			 GetGOR();
			 GetBo();
			}
			} ////flash calculation end
			void FlashCalculation()   //第一个StrSeg的计算函数
			{ ////flash calculation start
			//先只是考虑油气两组分的情况，而没有多组分，只是对生成的油和气进行相态计算
			z[0]=GGIFromKerogen/MW[0]; //气的摩尔数
			z[1]=OGIFromKerogen/MW[1]; //油的摩尔数
			double tteemm=z[0]+z[1];
			z[0]=z[0]/tteemm; //气的摩尔比
			z[1]=z[1]/tteemm; //油的摩尔比
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
			double nvLeftPoint; //二分法nv左端点，  初始值为0
			double nvRightPoint; //二分法nv右端点， 初始值为1
			double nvMiddlePoint; //二分法的中间点，为左右端点和的一半
			double aa,bb,cc,dd; //cubic EOS --三次状态方程的系数
			ObjectiveValueInFlash=1.0e-12;
			double KiMin,KiMax; //记录组分的平衡比的最小值和最大值
			GetpTcpPc();  //获得混合物准临界温度和压力值，用于判断混合物温度是否超过临界温度，如果超过则不进行闪蒸计算，而是直接计算密度
			if(TmK<pTc)
			{  //如果体系温度没超过准临界温度，则进行闪蒸计算 ————开始
			GetBubblePointPressure(); //获得体系的泡点压力
			GetInitKi();  //获得每一组分的初始的平衡比Ki，Danesh 1998, (3.66)P122
			do
			{
			KiMin=K[0];KiMax=K[0];
			for(int i=1;i<NCom;i++) {if(K[i]<KiMin) KiMin=K[i]; if(K[i]>KiMax) KiMax=K[i];}
			if(fabs(1-KiMax)<1e-8||fabs(1-KiMin)<1e-8)  {nv=-10000.; break;}
			   nvLeftPoint=1./(1.-KiMax); //nv值域左端点   ,Whitson 1989 The negative flash  P52
			   nvRightPoint=1./(1.-KiMin); //nv值域右端点  ,Whitson 1989 The negative flash  P52
			   nvMiddlePoint=(nvLeftPoint+nvRightPoint)/2.;  //初始值
			   nv=NewtonIterationFornv(nvMiddlePoint);    //用牛顿迭代法求nv值
				nl=1-nv;
				for(int i=0;i<NCom;i++)
				  {
					x[i]=z[i]/(1.0+(K[i]-1.0)*nv);
					y[i]=z[i]*K[i]/(1.0+(K[i]-1.0)*nv);
				  }
			 GetParasOfComsInEOS(x,aL,bL); //求对应于油相的a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* 有一个三重根和一个实根的情况*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);}/* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根;;有三个根的情况下要选择其中的最大值 */
			 GetParasOfComsInEOS(y,aV,bV); //求对应于气相的a,b
			 AV=aV*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BV=bV*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AV,BV); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; } /* 有一个三重根和一个实根的情况 */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); } /* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
			 GetFaii(FaiiL,x,aL,bL,AL,BL,ZL) ; //求油相的逸度系数
			 GetFaii(FaiiV,y,aV,bV,AV,BV,ZV) ; //求气相的逸度系数
			 Getfi_K();    //获得油气相态组分的逸度以及组分的平衡比   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
			 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
			}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);   //  &&runtimes<=100
			if(nv<0||nv>1)
			{ //nv<0,表明 体系为单一的液相，nv>1,表明体系是单一的气相，利用下面计算密度
			 GetParasOfComsInEOS(z,aL,bL); //求对应于体系的a,b   这里虽然使用的油相的符号“L”，但在nv>1的情况下也用于计算气相
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(nv<0)
			 { //nv<0,表明 体系为单一的液相
			 aHCType=Oil;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //之所以将y[i]也赋值，是为了在以后的计算中防止出现除以0的情况，但实际y[i]是不存在的
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* 有一个三重根和一个实根的情况 */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }/* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5
			 GetMWLMWV(x,y); //获得油相和气相的摩尔质量  ,由于是单一的油相，因此用z代替x，而气相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vV=1.;
			 GetLDensity(); //获得油相的密度
			 }
			 if(nv>1)
			 { //nv>1,表明体系是单一的气相
			 aHCType=Gas;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //之所以将x[i]也赋值，是为了在以后的计算中防止出现除以0的情况，但实际x[i]是不存在的
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; }  // 有一个三重根和一个实根的情况
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }// 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5   ,
			 GetMWLMWV(x,y); //获得油相和气相的摩尔质量 ,由于是单一的气相，因此用z代替y，而油相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vL=1.;
			 GetVDensity(); //获得气相的密度
			 }
			}
			else
			{ //以下为两相体系
			 aHCType=OilGas;
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(x,y); //获得油相和气相的摩尔质量   NCom,MWL,MWV,MW,
			 GetLVDensity(); //获得油、气相的密度  OilDensity,GasDensity,vL,vV,MWL,MWV
			}
			}  //如果体系温度没超过准临界温度，则进行闪蒸计算  ————结束
			if(TmK>=pTc)
			{  //如果体系温度大于准临界温度，则只进行单相的PVT计算  ，这里用“L”来对该单相进行计算
			 nv=-2; //代表为超临界流体
			 aHCType=Oil; //超临界流体算作油
			 GetParasOfComsInEOS(z,aL,bL);  //求对应于油相的a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1;}  /* 有一个三重根和一个实根的情况 ShowMessage("单实根或三重实根");*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);} /* ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);ShowMessage("三个实根");有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
											   //之所以选择最大值是因为最小值在计算结果上为负数，而最大值通过验算符合实际
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //之所以将y[i]也赋值，是为了在以后的计算中防止出现除以0的情况，但实际y[i]是不存在的
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(z,y); //获得油相和气相的摩尔质量  ,由于是单一的油相，因此用z代替x，而气相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vV=1.;
			 GetLDensity(); //获得该体系（油相代替）的密度
			}
			} ////flash calculation end

			void FlashCalculation(StrSeg *aStrSeg)
			{ ////flash calculation start
			//先只是考虑油气两组分的情况，而没有多组分，只是对生成的油和气进行相态计算
			z[0]=GGIFromKerogen/MW[0]; //气的摩尔数
			z[1]=OGIFromKerogen/MW[1]; //油的摩尔数
			double tteemm=z[0]+z[1];
			z[0]=z[0]/tteemm; //气的摩尔比
			z[1]=z[1]/tteemm; //油的摩尔比
			if(z[0]<1.0e-5){ z[0]=1.0e-5;z[1]=1.0-z[0];}  //为了能稳定计算，需设定一个气组分的最小值
			if(z[1]<1.0e-5){ z[1]=1.0e-5;z[0]=1.0-z[1];}   //为了能稳定计算，需设定一个油组分的最小值
			TmK=Tm+273.15;
			PmMPa=Pm/1.0e6;
			SolutionOfCE aSCEZ;
			double ObjectiveValueInFlash; //Danish,1998  P174     =1.0e-12;
			double ErrorValue_fiLfiV;
			double XigemaKizi;
			double XigemaziBiKi;
			double nvLeftPoint; //二分法nv左端点，  初始值为0
			double nvRightPoint; //二分法nv右端点， 初始值为1
			double nvMiddlePoint; //二分法的中间点，为左右端点和的一半
			double aa,bb,cc,dd; //cubic EOS --三次状态方程的系数
			ObjectiveValueInFlash=1.0e-12;
			double KiMin,KiMax; //记录组分的平衡比的最小值和最大值
			GetpTcpPc();  //获得混合物准临界温度和压力值，用于判断混合物温度是否超过临界温度，如果超过则不进行闪蒸计算，而是直接计算密度
			for(int i=0;i<NCom;i++) K[i]=aStrSeg->K[i];
			if(TmK<pTc)
			{  //如果体系温度没超过准临界温度，则进行闪蒸计算 ————开始
			GetBubblePointPressure(); //获得体系的泡点压力
			do
			{
			KiMin=K[0];KiMax=K[0];
			for(int i=1;i<NCom;i++) {if(K[i]<KiMin) KiMin=K[i]; if(K[i]>KiMax) KiMax=K[i];}
			if(fabs(1-KiMax)<1e-8||fabs(1-KiMin)<1e-8)  {nv=-10000.; break;}
			   nvLeftPoint=1./(1.-KiMax); //nv值域左端点   ,Whitson 1989 The negative flash  P52
			   nvRightPoint=1./(1.-KiMin); //nv值域右端点  ,Whitson 1989 The negative flash  P52
			   nvMiddlePoint=(nvLeftPoint+nvRightPoint)/2.;  //初始值
			   nv=NewtonIterationFornv(nvMiddlePoint);    //用牛顿迭代法求nv值
				nl=1-nv;
				for(int i=0;i<NCom;i++)
				  {
					x[i]=z[i]/(1.0+(K[i]-1.0)*nv);
					y[i]=z[i]*K[i]/(1.0+(K[i]-1.0)*nv);
				  }
			 GetParasOfComsInEOS(x,aL,bL); //求对应于油相的a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* 有一个三重根和一个实根的情况*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);}/* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根;有三个根的情况下要选择其中的最大值 */
			 GetParasOfComsInEOS(y,aV,bV); //求对应于气相的a,b
			 AV=aV*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BV=bV*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AV,BV); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; } /* 有一个三重根和一个实根的情况 */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); } /* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
			 GetFaii(FaiiL,x,aL,bL,AL,BL,ZL) ; //求油相的逸度系数
			 GetFaii(FaiiV,y,aV,bV,AV,BV,ZV) ; //求气相的逸度系数
			 Getfi_K();    //获得油气相态组分的逸度以及组分的平衡比   NCom,fiL,fiV,FaiiL,FaiiV,K,x,y,PmMPa
			 GetErrorValue_fiLfiV(ErrorValue_fiLfiV);
			}while(ErrorValue_fiLfiV>ObjectiveValueInFlash);   //  &&runtimes<=100
			if(nv<0||nv>1)
					  //else  //如果地层压力大于泡点压力，则计算单一的液态
			{ //nv<0,表明 体系为单一的液相，nv>1,表明体系是单一的气相，利用下面计算密度
			 GetParasOfComsInEOS(z,aL,bL); //求对应于体系的a,b   这里虽然使用的油相的符号“L”，但在nv>1的情况下也用于计算气相
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(nv<0)
			 { //nv<0,表明 体系为单一的液相
			 aHCType=Oil;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //之所以将y[i]也赋值，是为了在以后的计算中防止出现除以0的情况，但实际y[i]是不存在的
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1; }/* 有一个三重根和一个实根的情况 */
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }/* 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5
			 GetMWLMWV(x,y); //获得油相和气相的摩尔质量  ,由于是单一的油相，因此用z代替x，而气相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vV=1.;
			 GetLDensity(); //获得油相的密度
			 }
			 if(nv>1)
			 { //nv>1,表明体系是单一的气相
			 aHCType=Gas;
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //之所以将x[i]也赋值，是为了在以后的计算中防止出现除以0的情况，但实际x[i]是不存在的
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZV=aSCEZ.x1; }  // 有一个三重根和一个实根的情况
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZV=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3); }// 有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5   ,
			 GetMWLMWV(x,y); //获得油相和气相的摩尔质量 ,由于是单一的气相，因此用z代替y，而油相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vL=1.;
			 GetVDensity(); //获得气相的密度
			 }  /* */
			}
			else
			{ //以下为两相体系
			 aHCType=OilGas;
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(x,y); //获得油相和气相的摩尔质量   NCom,MWL,MWV,MW,
			 GetLVDensity(); //获得油、气相的密度  OilDensity,GasDensity,vL,vV,MWL,MWV
			}
			}  //如果体系温度没超过准临界温度，则进行闪蒸计算  ————结束
			if(TmK>=pTc)
			{  //如果体系温度大于准临界温度，则只进行单相的PVT计算  ，这里用“L”来对该单相进行计算
			 nv=-2; //代表为超临界流体
			 aHCType=Oil; //超临界流体作为油处理
			 GetParasOfComsInEOS(z,aL,bL);  //求对应于油相的a,b
			 AL=aL*PmMPa/(R*TmK*R*TmK);          //Danish,1998 P132  4.7
			 BL=bL*PmMPa/(R*TmK);              //Danish,1998 P132  4.8
			 GetaEOSParas(aa,bb,cc,dd,AL,BL); //计算 对应于油相的cubic EOS --三次状态方程的系数
			 aSCEZ=CubicEquation(aa,bb,cc,dd);
			 if(aSCEZ.Case==1||aSCEZ.Case==2) {ZL=aSCEZ.x1;}  /* 有一个三重根和一个实根的情况 ShowMessage("单实根或三重实根");*/
			 if(aSCEZ.Case==3||aSCEZ.Case==4) {ZL=ReturnMax(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);} /* ZL=ReturnMin(aSCEZ.x1,aSCEZ.x2,aSCEZ.x3);ShowMessage("三个实根");有三个实根情况，其中Case==3为有两个重根，Case==4为有三个不同实根 */
											   //之所以选择最大值是因为最小值在计算结果上为负数，而最大值通过验算符合实际
			 for(int i=0;i<NCom;i++) {x[i]=z[i]; y[i]=z[i];  }  //之所以将y[i]也赋值，是为了在以后的计算中防止出现除以0的情况，但实际y[i]是不存在的
			 GetvLvV(); //获得油气的摩尔体积  Danish,1998 P40 2.5  vL,vV,R,TmK,ZL,ZV,PmMPa
			 GetMWLMWV(x,y); //获得油相和气相的摩尔质量  ,由于是单一的油相，因此用z代替x，而气相在这里由于采用油气两相的函数，因此只是进行了运算，而不显示结果
			 vV=1.;
			 GetLDensity(); //获得该体系（油相代替）的密度
			}
			} ////flash calculation end

			//====================flash Calculation End ，相态计算相关 结束

			//------------------------- 排烃 END----------------------------------
			
			StrSeg()
			{
				Init();
			}

			void Init()
			{
				pos_i = 0;
				pos_j = 0;
				pos_k = 0; //记录该地层段在三维数组中的坐标
				EndPoint = 0; //记录地层段最后一个时间在三维数组中的坐标

				MarginOfErrorThickness = 0; //判断虚层剥蚀情况的容错误差限
				Ma2Second = 0;

				LithNumber = 0;   //混合岩性的个数
				LithRatio = 0; //混合岩性的比例 ；地层段的各个参数都是依据混合岩性的比例给出的

				BeginAge = 0; //地层段开始时间
				EndAge = 0;   //地层段结束时间
				MiddleAge = 0;//地层段中间时间
				DeltaAge = 0; //地层段或事件的年代区间

				Property = 0;   //地层段性质：1是地层，2是虚层，3是剥蚀，4沉积间断
				ConnectingMarker = 0;  //虚层和剥蚀事件的关联标记
				VirtualErosionPair = 0; //虚层StrSeg和其对应的剥蚀StrSeg关联对；用整数来标记每一个虚层StrSeg的VirtualErosionPair值与唯一的对应的一个剥蚀事件的StrSeg的VirtualErosionPair值相同。
				Eroded = false; //用于判断虚拟层是否已经被剥蚀掉了，初始赋值时都是false
				SourceRock = false; //用于判断是否为源岩
				IsThisMatrixKerogenOrCoal = 0; //判断基质类型是否为干酪跟或煤

				MaxBuryMiddleDepth = 0; //地层段经历的最大埋藏中部深度
				MaxBuryTopDepth = 0;    //地层段经历的最大埋藏顶部深度
				MaxBuryBottomDepth = 0; //地层段经历的最大埋藏底部深度
				TopDepth = 0; //顶面深度  ，指的是加上了古水深的顶面深度
				BottomDepth = 0;//底面深度
				MiddleDepth = 0;//中部深度
				BuryTopDepth = 0; //顶面埋藏深度 ，不算古水深，只是沉积物的深度，从沉积物-水表面算起的深度
				BuryBottomDepth = 0;//底面埋藏深度
				BuryMiddleDepth = 0;//中部埋藏深度
				CurrentThickness = 0;//现今的厚度(包括虚地层)，剥蚀厚度为负   = 0;地层或虚层的现今的厚度即对应于最大深度的厚度
				Thickness = 0; //厚度
				MatrixThickness = 0;//骨架厚度
				//以下这些压力的单位都采用国际单位制：帕斯卡
				Pt = 0;
				Pm = 0;
				Pb = 0; //地层段顶部、中部和底部流体压力
				Ut = 0;
				Um = 0;
				Ub = 0; //分别为顶部、中部和底部的流体超压
				StaticPt = 0;
				StaticPm = 0;
				StaticPb = 0; //地层段顶部、中部和底部静流体压力
				Plt = 0;
				Plm = 0;
				Plb = 0; //静岩压力,分别是StrSeg顶部、中部、和底部的静岩压力
				Ult = 0;
				Ulm = 0;
				Ulb = 0; //静岩势能,分别是StrSeg顶部、中部、和底部的静岩势能
				EffectiveStresst = 0;EffectiveStressm = 0; EffectiveStressb = 0; //有效应力，分别是StrSeg顶部、中部、和底部的
				MaxEffectiveStresst = 0;MaxEffectiveStressm = 0;MaxEffectiveStressb = 0;  //记录StrSeg经历的最大有效应力

				COC = 0;//压缩系数 Coefficient Of Compressibility
				aOverpressure = 0;bOverpressure = 0;cOverpressure = 0; //超压方程中的三个参数

				vFluild = 0; //流体流动速度，这一参数没用到
				vWater = 0; //地层水流速

				InitialPorosity = 0;CompactionFactor = 0;  //初始孔隙度和关于静水压力深度的Athy定律的压实系数 kArthDepth
				TInitialPorosity = 0;TCompactionFactor = 0;  //混合的总体的初始孔隙度和压实系数
				Porosityt = 0; //各混合岩性的孔隙度，孔隙度为小数;;顶部值
				Porositym = 0;  // 各混合岩性的孔隙度，孔隙度为小数;;中部值
				Porosityb = 0;  // 各混合岩性的孔隙度，孔隙度为小数;;底部值
				Porot = 0;Porom = 0;Porob = 0; //为顶、中部和底的孔隙度 ，小数
				EndPorom = 0; //现今地层的孔隙度值，包括虚层在剥蚀前最小的孔隙度值。用于比较迭代前后孔隙度以判断是否收敛。用于超压方程
				DifferencePoromEndPorom = 0; //计算的最终的孔隙度值和上一次迭代（或初始）的孔隙度差值
				LogPermeability = 0; //各混合岩性的渗透率自然对数值 = 0;单位是LogmD
				Perm = 0; // 总的渗透率 Permeability， 单位是m^2
				aPoro_Perm = 0; //孔隙度-渗透率关系数据对

				Sw = 0;So = 0;Sg = 0; //水、油、气的饱和度
				WaterViscosity = 0;  //水粘度

				MatrixDensity = 0; //不同岩性基质的密度
				TMatrixDensity = 0; //  总的基质密度
				WaterDensity = 0; //地层水密度
				OilDensity = 0; //油密度
				GasDensity = 0; //气密度
				SeaWaterDensity = 0;  //海水密度取值=1025 kg/m^3
				TotalDensity = 0; //总的岩石密度（包括其中的流体和骨架的综合密度）

				TotalThermalCond = 0; //总的热导率  （包括基质和孔隙流体）
				MatrixThermalCond = 0; //不同的基质热导率
				TMatrixThermalCond = 0; //总的基质热导率
				WaterThermalCond = 0; //地层水热导率
				OilThermalCond = 0; //油热导率
				GasThermalCond = 0; //气热导率
				PoreFluidThermalCond = 0; //孔隙流体热导率
				IceThermalCond = 0; //冰热导率
				GasHydratesThermalCond = 0; //天然气水合物热导率

				TotalHeatCapacity = 0; //总的比热容 （包括基质和孔隙流体）
				MatrixHeatCapacity = 0; //基质比热容，不同的基质
				TMatrixHeatCapacity = 0; //总的基质比热容
				WaterHeatCapacity = 0; //地层水比热容
				OilHeatCapacity = 0; //油比热容
				GasHeatCapacity = 0; //气比热容
				IceHeatCapacity = 0; //冰比热容
				GasHydratesHeatCapacity = 0; //天然气水合物比热容
				PoreFluidHeatCapacity = 0; //孔隙流体比热容


				MatrixRadioactiveHeat = 0;    //不同岩性基质的辐射热
				Qr = 0; // 总的辐射热

				PaleoWaterDepth = 0;//记录古水深
				SurfaceT = 0; //地表温度，记录最上面的格子
				HF = 0; //记录古热流

				Tt = 0; //顶部温度
				Tm = 0; //中部温度
				Tb = 0; //底部温度
				Tmax = 0; //记录模拟过程中中部的最高温度


				TTI = 0; //地层的TTI值
				
				Ro[RO_TTI] = 0;  //地层的Ro%值
				Ro[RO_Simple] = 0;  //地层的Ro%值
				Ro[RO_Easy] = 0;  //地层的Ro%值
				Ro[RO_Basin] = 0;  //地层的Ro%值

				TTI0 = 0; //初始时刻的TTI值
				aParaOfEasyRo = 0; //定义一个EasyRo模型结构，用于存储参数
				aParaOfBasinRo = 0; //定义一个BasinRo模型结构，用于存储参数
				aParaOfSimpleRo = 0; //定义一个SimpleRo模型结构，用于存储参数

				TOC = 0; //残余有机碳含量
				InitTOC = 0; //原始有机碳含量 ,是在现在的地层条件下的原始有机碳含量，即现今的岩石密度条件 。该数值只有最后一个时间的地层段存在
				MassOfInitTOC = 0;//该地层段单位面积（m^2）上原始有机碳的总质量 。 该数值只有最后一个时间的地层段存在

				aDR = 0;  //定义一个干酪根降解结构体

				for (int idx = RO_TTI; idx <= RO_Basin; idx++)
				{
					HCGI[idx] = 0; //  生烃强度 kg/m^2 ，用于降解生烃模型
					OGI[idx] = 0; //oil generating intensity ,生油强度 kg/m^2 ，用于降解生烃模型
					GGI[idx] = 0; //gas generating intensity ,生气强度 kg/m^2 ，用于降解生烃模型
				}
				
				aParaLLNL = 0; //定义一个LLNL化学反应动力学参数结构体
				OGI_LLNL = 0;   //oil generating intensity ,生油强度 kg/m^2  ,用于化学反应动力学生烃模拟
				GGI_LLNL = 0;   //gas generating intensity ,生气强度 kg/m^2（也用质量单位）  ,用于化学反应动力学生烃模拟

				//2017/11/27:organo facies
				aOrganofacies = 0;
				aPetroGenStyle = LLNL;

				//
				PCOEt = 0.;//top pressure coefficient
				POCEm = 0.;//middle pressure coefficient
				POCEb = 0.;//bottom pressure coefficient

				//2018/8/15: new variables
				OilViscosity = 0.; //油粘度
				GasViscosity = 0.; //气粘度
				Swc = 0.,Soc = 0.,Sgc = 0.; // 束缚水饱和度、残余油饱和度 、残余气饱和度    ,用小数表示
				Swe = 0.; //effective saturations Se有效水饱和度for krw and krow,       ,用小数表示
				Soe = 0.; // 有效油饱和度 ,暂时没有用上    ,用小数表示
				Sgoe = 0.; //用于Krog的有效饱和度  ,用小数表示
				Sge = 0.; // 有效气饱和度,用于Krg   ,用小数表示

				Krow = 0.,Krog = 0.; //
				Krw = 0.,Krg = 0.,Kro = 0.; //分别是水、气、油的相对渗透率
				lamuda = 0.; 
				aToEntryPr = 0.,bToEntryPr = 0.;//对应于突破毛管压力的系数a和b,在Hantschel 2009 ,P411. Table A.6. Capillary Entry Pressure
				PcbMA = 0.; // 突破毛管压力,水银-空气
				PcMA = 0.; //毛管压力，水银-空气
				PcbOW = 0.,PcbGW = 0.,PcbGO = 0.; //分别为油水、气水和气油的突破毛管压力
				PcOW = 0.,PcGW = 0.,PcGO = 0.; //分别油水、气水和气油的毛管压力
				RouML = 0.,RouMV = 0.; //分别是油和气的摩尔密度，单位：gmol/cm 3
				Tc = 0.,vc = 0.; //分别为体系的临界温度和临界摩尔体积，根据摩尔平均值或等；单位分别为K和cm3/gmol
				TcL = 0.,TcV = 0.; //分别是油相和气相的临界温度，单位：K
				PXigema = 0.; //known as the parachor  ,等张比容
				IFTOilWater = 0.,IFTGasWater = 0.,IFTGasOil = 0.;//油水、气水和气油的界面张力  interfacial tension (IFT) ，单位：mN/m

				//================== flash Calculation Start ,相态计算相关
				SoTreshold = 0.;   //临界排油饱和度，值在[0-1]之间
				SgTreshold = 0.;   //临界排气饱和度，值在[0-1]之间

				Sgg = 0.; //气体相对密度   ；Good Oil: Sgg= 0.855
				Soo = 0.;//油的相对密度     ; Good Oil:  Soo=0.823
				T_F = 0.; //华氏温度
				MolFraC1InWater = 0.; //molar fraction of methane in water
				
				nl = 0.,nv = 0.; //分别是液态和气态的摩尔分数
				NCom = 0; //有N个组分的烃类
				aProperties = 0;
				x = 0,y = 0,z = 0;  //分别为在液相中的组分摩尔比例/分数，在气相中的组分摩尔比例/分数，总的组分摩尔分数
				K = 0; // The equality of fugacity can be expressed by the equilibrium ratio, K,  K[i] = y[i] / x[i]
				MW = 0;       //组分摩尔质量  kg/kgmol
				Tci = 0, Pci = 0, vci = 0; //组分临界温度、压力和体积   K，MPa，m^3/kmol
				Omegai = 0; //the dimensionless acentric factor,各组分的
				kij = 0; //binary interaction parameter 二元相互作用参数
				R = 0.;//气体常数 ，=0.008314;0.008314 KJ/(mol*K)
				aHCType = OilGas;

				//
				SCT = 0.; //标准条件下的温度15.556摄氏度
				SCTK = 0.; // 标准条件下的温度开氏温度
				SCP = 0.; //标准条件下的压力1 atm 0.1MPa
				pb = 0.; //体系的泡点压力 ，MPa
				TmK = 0.; //中部温度，用开氏温度表示，用于相态计算
				PmMPa = 0.; //中部压力，用兆帕表示，用于相态计算
				pTc = 0.; //准临界温度 K   pseudo critical temperature  ,赋给初值为体系温度
				pPc = 0.; //准临界压力 MPa
				a = 0.,b = 0.; //分别对应于临界相态的a值和b值
				vL = 0.,vV = 0.;  //分别是油和气的摩尔体积  m3/kgmol
				MWL = 0.,MWV = 0.; //分别是油相和气相的摩尔质量
				aci = 0,bi = 0,mi = 0,Alphai = 0,ai = 0;
				Ai = 0,Bi = 0; //
				aL = 0.,bL = 0.,aV = 0.,bV = 0.; //分别对应于油和气的a值和b值
				aEOS = SRK;
				AL = 0.,AV = 0.,BL = 0.,BV = 0.; // 分别对应于油和气
				ZL = 0.,ZV = 0.; //液体和气体，即油和气的压缩系数
				FaiiL = 0,FaiiV = 0; //分别为油、气相态中组分的逸度系数（fugacity coefficients）
				fiL = 0,fiV = 0; //分别为油、气相态中组分的逸度（fugacities）

				//
				OilDensitySC = 0.; //标准条件下原油的密度
				API = 0.; //标准条件下油的重度
				GOR = 0.;//气油比  m3/m3
				Bo = 0.; //原油体积系数，定义为地下原油体积与地面原油体积之比
				KSC = 0;
				nvSC = 0.,nlSC = 0.;    //标准条件下气相和油相的摩尔比
				xSC = 0,ySC = 0;
				MWLSC = 0.,vLSC = 0.,MWVSC = 0.,vVSC = 0.;
				GasDensitySC = 0.; // 标准条件下气相密度
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
				//获得单位质量原始有机碳的生油量和生气量 ,通过LLNL化学反应动力学参数获得
				//用于除了初始的StrSeg
				switch(aPetroGenStyle)
				{
				case LLNL:
					if (!aParaLLNL)
					{
						aParaLLNL=new ParaLLNL;
					}
					aParaLLNL->CopyFrom(StrSegLeft->aParaLLNL);
					if(Property==2&&Eroded)
						aParaLLNL->Reactions(SurfaceT,BeginAge,SurfaceT,EndAge,StrSegLeft->aParaLLNL );  //如果是剥蚀的虚层，则采用地表温度进行计算，实际上什么都不会变
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
						aOrganofacies->Reactions(SurfaceT,BeginAge,SurfaceT,EndAge,StrSegLeft->aOrganofacies );  //如果是剥蚀的虚层，则采用地表温度进行计算，实际上什么都不会变
					else
						aOrganofacies->Reactions(StrSegLeft->Tm,BeginAge,Tm,EndAge,StrSegLeft->aOrganofacies );
					break;
				};
			}
			
			void GainHCGIPerUnitInitTOC()
			{ //用于初始的StrSeg, 获得单位质量原始有机碳的生油量和生气量 ,通过LLNL化学反应动力学参数获得
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
			
			//获得原始有机碳含量和质量    ;;新修20170908
			void GainInitTOC()  
			{            
				 //当达到了地层段模拟的最后一个时间点时执行计算
				if(pos_k==EndPoint)
				{ 
					switch(aPetroGenStyle)
					{
					case LLNL:
						if (aParaLLNL)//LLNL动力学反应
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
			{   //获得单位质量原始有机碳的生烃量、生油量和生气量 ,通过有机碳降解率与Ro关系曲线获得
				//用于除了初始的StrSeg

				if (!aDR)
				{
					aDR=new DR; //新建一个干酪根降解结构体
				}
								
				aDR->CopyFrom(StrSegLeft->aDR);  //将上个时刻的地层段的干酪根降解结构体参数赋值给现在的结构体
				aDR->GetHCFromDR(Ro);
			}
			
			void GetHCGIPerUnitInitTOC()
			{   //获得单位质量原始有机碳的生烃量、生油量和生气量,通过有机碳降解率与Ro关系曲线获得
				//用于初始的StrSeg

				if (aDR)
				{
					aDR->GetHCFromDR(Ro);
				}
			}
			
			void GetInitTOC()  //获得原始有机碳含量和质量，用于降解率-Ro方法
			{
				if (!aDR)
				{
					return;
				}

				if(pos_k==EndPoint)
				{  //当达到了地层段模拟的最后一个时间点时执行计算

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
			{  //最新的（顶部的）地层段温度计算 ,稳态公式
				double TempTm;
				double wcx;
				Tt=SurfaceT;
				Tm =SurfaceT;//首先将地表温度赋值给地层段中部温度
				do{
				GetTotalThermalCond();
				TempTm=Tt+HF*0.5*Thickness/TotalThermalCond;
				wcx=fabs(Tm-TempTm);
				Tm=TempTm;
				}while(wcx>0.0001);
				Tb=Tm+HF*0.5*Thickness/TotalThermalCond;
			}

			void GetT(StrSeg *StrSegLeft, StrSeg *StrSegTop)
			{  //其它非最新的（顶部的）地层段温度计算 ,稳态公式
				double TempTm;
				double wcx;
				Tt=StrSegTop->Tb; //将其之上的StrSeg的底部温度赋给该StrSeg顶面
				Tm =StrSegLeft->Tm;//首先将左侧地层段中部温度赋值给地层段中部温度
				do{
				GetTotalThermalCond();
				TempTm=Tt+HF*0.5*Thickness/TotalThermalCond;  //如果没有被剥蚀，则采用全部的厚度--Thickness来计算
				wcx=fabs(Tm-TempTm);
				Tm=TempTm;
				}while(wcx>0.0001);
				Tb=Tm+HF*0.5*Thickness/TotalThermalCond;
			}
			
			void GetTmax(StrSeg *StrSegLeft)
			{  //获得最大现在或以前经历的最高温度
				if(Tm>StrSegLeft->Tmax ) Tmax=Tm;
				else Tmax=StrSegLeft->Tmax;
			}
			
			void GetPoreFluidThermalCond()
			{  //获得孔隙流体热导率
				GetWaterThermalCond();
				GetOilThermalCond();
				GetGasThermalCond();
				GetIceThermalCond();
				GetGasHydratesThermalCond();
				PoreFluidThermalCond=pow(WaterThermalCond,Sw)+pow(OilThermalCond,So)+pow(GasThermalCond,Sg);   //这里的Sw,So,Sg暂时还没赋值
			}
			
			void GetTotalThermalCond()
			{  // 总热导率由基质和孔隙热导率的几何平均值得到
				GetMatrixThermalCond();
				GetPoreFluidThermalCond();
				TotalThermalCond=pow(TMatrixThermalCond,1.0-Porom)*pow(WaterThermalCond,Porom);  //还没有用孔隙流体热导率，因为 PoreFluidThermalCond 还没有赋值
				//下面的为更复杂的混合形式，来自Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling；先隐掉，必要时可参考  ;经比较与几何平均算法总体的热导率要低一些，但趋势一致
				// double Z= WaterThermalCond/MatrixThermalCond;
			//  double aerf=5.0;double E=(1.0-Z)/(1.0+aerf*Z);
				// TotalThermalCond= MatrixThermalCond*(1.0-E*Porom)/(1.0+aerf*E*Porom);
			}
			
			void GetWaterThermalCond()
			{
				//来自 Deming and Chapman (1989) ,原文，  单位W/(mK)
				double A1 = 0.565;
				double B1 = 0.00188;
				double C1 = -7.23e-6;
				double A2 =0.602;
				double B2 = 0.00131;
				double C2 = -5.14e-6;
				if((Tm)<=137) WaterThermalCond=A1+B1*Tm+C1*Tm*Tm; //这里得到的热传导单位是W/(m℃)
				if((Tm)>137) WaterThermalCond=A2+B2*Tm+C2*Tm*Tm;  //这里得到的热传导单位是W/(m℃)
			}
			
			void GetOilThermalCond()
			{   //conductivities of liquid petroleum   ，after Hantschel et al., 2009  ，经过验证
				if(Tm<240) OilThermalCond=0.2389-4.593e-4*(Tm+273.15)+2.676e-7*(Tm+273.15)*(Tm+273.15);   //这里得到的热传导单位是W/(m℃)
				else OilThermalCond= 0.075;                                    //这里得到的热传导单位是W/(m℃)
			}
			
			void GetGasThermalCond()
			{   //conductivities of vapor petroleum   ，after Hantschel et al., 2009  ，经过验证
				if(Tm<120) GasThermalCond=-0.0969+4.37e-4*(Tm+273.15);                //这里得到的热传导单位是W/(m℃)
				else GasThermalCond= 0.075;                                    //这里得到的热传导单位是W/(m℃)
			}
			
			void GetIceThermalCond() { IceThermalCond=2.23; } //冰热导率， 单位是W/(m℃)。只是赋值了，还没有应用
			
			void GetGasHydratesThermalCond() {GasHydratesThermalCond=0.49; } //天然气水合物热导率， 单位是W/(m℃) 。只是赋值了，还没有应用
			
			void GetMatrixThermalCond()
			{  //热导率，最终得到kg.m.s单位制；
				TMatrixThermalCond=1.;
				for(int i=0;i<LithNumber;i++)
				TMatrixThermalCond*=pow(MatrixThermalCond[i],LithRatio[i]); //这里得到的热传导单位是W/(m℃);得到的是几何平均值
				TMatrixThermalCond=358.*(1.0227*TMatrixThermalCond-1.882)*(1./(Tm+273.15)-0.00068)+1.84; //考虑热传导随温度的变化——Sekiguchi–Waples Model   ，经过验证
			}
			
			void GetMatrixHeatCapacity()
			{   //这里得到热容的单位是J/(kg℃);得到的是算术平均值
				TMatrixHeatCapacity=0.;
				double c20; //20℃时的比热容
				double cT; //现今温度下的比热容
				for(int i=0;i<LithNumber;i++)
				{
					c20=MatrixHeatCapacity[i]; 
					if(!IsThisMatrixKerogenOrCoal[i])  //不是干酪根或煤的情况下，已验证   //from Waples and Waples (2004a) ，Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
					cT=c20*(0.953+2.29e-3*Tm-2.835e-6*Tm*Tm+1.191e-9*Tm*Tm*Tm);
					if(IsThisMatrixKerogenOrCoal[i]) //是干酪根或煤的情况下 ，直接根据下面的公式给出。，已验证    from Waples and Waples (2004a) ，Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
					cT=1214.3+6.2657*Tm-0.12345*Tm*Tm+1.7165e-3*Tm*Tm*Tm-1.1491e-5*Tm*Tm*Tm*Tm+3.5686e-8*Tm*Tm*Tm*Tm*Tm-4.1208e-11*Tm*Tm*Tm*Tm*Tm*Tm;
					TMatrixHeatCapacity+=LithRatio[i]*cT;   //这里得到热容的单位是J/(kg℃);得到的是算术平均值
				}
			}
			
			void GetQr()
			{  //获得地层的放射性生热量，根据每种岩性的放射性生热固定值和岩性比例计算
				Qr=0.;
				for(int i=0;i<LithNumber;i++)
				Qr+=MatrixRadioactiveHeat[i]*LithRatio[i];    //获得混合基质的放射性生热量
				Qr*=(1.0-Porom);                 //获得地层的放射性生热量。这时的单位还是μW/m^3
				Qr*=1.0e-6;           //转化为W/m^3
			}
			
			void GetWaterHeatCapacity()
			{   //水比热容计算  ，已经验证；公式来自Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
				if(Tm<=290) WaterHeatCapacity=(4245.-1.841*Tm);   //单位：J/m/K
				if(Tm>290)  WaterHeatCapacity=3703*exp(-0.00481*(Tm-290)+2.34*0.0001*(Tm-290)*(Tm-290));  //单位：J/m/K
			}
			
			void GetOilHeatCapacity()
			{  //油比热容计算  ，已经验证；公式来自Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
				OilDensity=800.; //这里先假定油密度为800kg/m^3;
				OilHeatCapacity=(1684.+3.389*Tm)*sqrt(OilDensity/1000.);  //单位：J/m/K ,
			}
			
			void GetGasHeatCapacity()
			{  //气比热容计算  ，已经验证；公式来自Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
				GasHeatCapacity=3250;  //单位：J/m/K   ,from (Waples and Waples, 2004b)
			}
			
			void GetIceHeatCapactiy()  //已经验证   来自Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
			{ IceHeatCapacity=2115.;  } //单位：J/m/K
			
			void GetGasHydratesHeatCapactiy() //已经验证  来自Hantschel 2009 Fundamentals of Basin and Petroleum Systems Modeling
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
			{   //获得水的达西流速 ,单位：m/m.y.
				vWater=-Perm/WaterViscosity*(Ut-Ub)/Thickness;
				vWater*=Ma2Second;       //将vWater转化为m/my
			}
			
			void GetWaterDensity()
			{  //得到一定温度和压力下的地层水密度
				double WaterDensityStandardCond=1040.; //单位：kg/m^3
				double Aerf=5.0e-4; //℃^-1
				double Beita=4.3e-4; //MPa^-1
				WaterDensity=WaterDensityStandardCond*exp(Beita*(Pm/1.0e6-0.1)-Aerf*(Tm-25.));
			}
			
			void GetMatrixDensity()
			{  //得到的密度单位是kg/m^3
				TMatrixDensity=0.;
				for(int i=0;i<LithNumber;i++)
				TMatrixDensity+=LithRatio[i]*MatrixDensity[i];
			}
			
			void GetStaticPressure()
			{ //用于顶部网格,单位帕斯卡 ,只适用于真实的地层，不用于剥蚀事件
				StaticPt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;  //水表面净水压力等于一个大气压，即0.1MPa
				StaticPm=StaticPt+WaterDensity*9.8*Thickness/2.0;
				StaticPb=StaticPt+WaterDensity*9.8*Thickness;
			}
			
			void GetStaticPressure(StrSeg *StrSegTop)
			{   //用于非顶部网格 ,单位帕斯卡 ,只适用于真实的地层，不用于剥蚀事件
				StaticPt=StrSegTop->StaticPb;
				StaticPm=StaticPt+WaterDensity*9.8*Thickness/2.0;
				StaticPb=StaticPt+WaterDensity*9.8*Thickness;
			}
			
			void CalculateWaterDensityAndStaticPressure()
			{ //通过耦合计算水密度和静水压力，用于最顶部的StrSeg的计算
				double TempWaterDensity;
				double wc;
				WaterDensity=1040.; //对于最上面的StrSeg，先设水密度为通常的地层水密度
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
			{ //通过耦合计算水密度和静水压力，用于除了最顶部的StrSeg的计算
				double TempWaterDensity;
				double wc;
				//对于初始的地层水密度，如果不是第一个StrSeg,是由 GetFromNearbyStrSegPart01(StrSeg *StrSegLeft, StrSeg *StrSegTop) 函数将StrSegLeft的地层水密度传过来作为初始密度值的
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
			{ //用于最顶部的StrSeg的计算
				GetMatrixDensity();
				CalculateWaterDensityAndStaticPressure(); //计算流体静压力 和水密度
				TotalDensity=Porom*WaterDensity+(1.-Porom)*TMatrixDensity;
			}
			
			void GetTotalDensity(StrSeg *StrSegTop)
			{  //用于除了最顶部的StrSeg的计算
				GetMatrixDensity();
				CalculateWaterDensityAndStaticPressure(StrSegTop); //计算流体静压力 和水密度
				TotalDensity=Porom*WaterDensity+(1.-Porom)*TMatrixDensity;
			}
			
			void GetPl()   //获得静岩压力 ,单位，Pa
			{
				Plt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;  //水表面净水压力等于一个大气压，即0.1MPa
				Plm=Plt+TotalDensity*9.8*Thickness/2.0;
				Plb=Plt+TotalDensity*9.8*Thickness;
			}
			
			void GetPl(StrSeg *StrSegTop)  //获得静岩压力 ,单位，Pa
			{   //用于非顶部网格
				Plt=StrSegTop->Plb;
				Plm=Plt+TotalDensity*9.8*Thickness/2.0;
				Plb=Plt+TotalDensity*9.8*Thickness;
			}
			
			void GetUl()   //获得静岩势能 ,单位，Pa
			{
				GetTotalDensity(); //该函数已经包含了静水压力的求取函数
				GetPl();
				Ult=Plt-StaticPt;
				Ulm=Plm-StaticPm;
				Ulb=Plb-StaticPb;
			}
			
			void GetUl(StrSeg *StrSegTop)  //获得静岩势能 ,单位，Pa
			{   //用于非顶部网格
				GetTotalDensity(StrSegTop); //该函数已经包含了静水压力的求取函数
				GetPl(StrSegTop);    //获得静岩压力
				Ult=Plt-StaticPt;    //获得静岩势能，顶部
				Ulm=Plm-StaticPm;    //获得静岩势能，中部
				Ulb=Plb-StaticPb;    //获得静岩势能，底部
			}
			
			void GetEffectiveStress() //有效应力计算
			{ EffectiveStresst=Ult-Ut; EffectiveStressm=Ulm-Um;  EffectiveStressb=Ulb-Ub;  }
			
			void GetPoroFromEffectiveStress()
			{  
				//基于静水压力深度的Athy定律,对于初始的StrSeg
				GetUl();// //获得静岩势能 ,单位，Pa
				GetEffectiveStress(); //有效应力计算
				MaxEffectiveStresst =EffectiveStresst;   //对于初始的StrSeg其有效应力即为最大有效应力
				MaxEffectiveStressm =EffectiveStressm;
				MaxEffectiveStressb =EffectiveStressb;
				//在GetIfItIsTheTopestStrSegOP01()函数中已经将*Porosityt、*Porositym、*Porosityb开了空间并赋值了初值
				Porot=0.; Porom=0.; Porob=0.;
				double fFait,fFaiDerivativet,fFaim,fFaiDerivativem,fFaib,fFaiDerivativeb;  //牛顿迭代法中的变量
				for(int i=0;i<LithNumber;i++)
				{
					double wcx=0.0001;
					double tempPorot,tempPorom, tempPorob;
					double ErrorPorot,ErrorPorom , ErrorPorob;
					do
					{  //通过迭代获得孔隙度值
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
						if(Porosityt[i]<=0.||Porosityt[i]>InitialPorosity[i]) Porosityt[i]= GetRand(0., InitialPorosity[i]);   //如果迭代计算的孔隙度超出合理的范围值，则随机给出孔隙度初始值进行下一次迭代
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
				//基于静水压力深度的Athy定律,对于非初始的StrSeg
				GetUl(StrSegTop);// //获得静岩势能 ,单位，MPa
				GetEffectiveStress(); //有效应力计算
				for(int i=0;i<LithNumber;i++)
				{
					Porosityt[i]=StrSegLeft->Porosityt[i]; //将上个时间段的孔隙度值赋值给该时间段作为迭代的初始值
					Porositym[i]=StrSegLeft->Porositym[i];
					Porosityb[i]=StrSegLeft->Porosityb[i];
				}
				double fFait,fFaiDerivativet,fFaim,fFaiDerivativem,fFaib,fFaiDerivativeb;  //牛顿迭代法中的变量
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
						{  //通过迭代获得孔隙度值
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
							if(Porosityt[i]<=0.||Porosityt[i]>InitialPorosity[i]) Porosityt[i]= GetRand(0., InitialPorosity[i]);  //如果迭代计算的孔隙度超出合理的范围值，则随机给出孔隙度初始值进行下一次迭代
							if(Porositym[i]<=0.||Porositym[i]>InitialPorosity[i]) Porositym[i]= GetRand(0., InitialPorosity[i]);
							if(Porosityb[i]<=0.||Porosityb[i]>InitialPorosity[i]) Porosityb[i]= GetRand(0., InitialPorosity[i]);
						}while(ErrorPorot>wcx||ErrorPorom>wcx||ErrorPorob>wcx);
						Porot+=Porosityt[i]*LithRatio[i];
						Porom+=Porositym[i]*LithRatio[i];
						Porob+=Porosityb[i]*LithRatio[i];
					}
				}
				else
				{ //如果有效应力小于等于最大有效应力，孔隙度保持不变；各混合岩性孔隙度已经在上面赋值了。
					MaxEffectiveStresst=StrSegLeft->MaxEffectiveStresst;
					MaxEffectiveStressm=StrSegLeft->MaxEffectiveStressm;
					MaxEffectiveStressb=StrSegLeft->MaxEffectiveStressb;
					Porot=StrSegLeft->Porot;
					Porom=StrSegLeft->Porom;
					Porob=StrSegLeft->Porob;
				}
			}
			
			void GetCOC() //获得压缩系数
			{
				COC=TCompactionFactor/(TMatrixDensity-WaterDensity)/9.8*Porom/(1.-Porom);
			}
			
			void GetParaOfOverpressureEquation()
			{  //获得超压方程的三个参数 ,对于第一个StrSeg
				GetPoroFromEffectiveStress();
				GetThickness();
				GetDepths();
				GetCOC();
				GetPermeability();
				GetWaterViscosity();
				aOverpressure=COC*WaterDensity/(1.-Porom);
				bOverpressure=WaterDensity*Perm/WaterViscosity;                                                                                       
				cOverpressure=COC*WaterDensity/(1.-Porom)*(Ulm-0.)/(DeltaAge*Ma2Second)-Porom*(WaterDensity-WaterDensity)/(DeltaAge*Ma2Second);  // 用两个相同的水密度只差是代表对于首个StrSeg,这一时间和虚拟的上一时间水密度相同 ；虚拟的上一时间静岩势能为0
			}

			void GetParaOfOverpressureEquation(StrSeg *StrSegLeft,StrSeg *StrSegTop)
			{  //获得超压方程的三个参数 ,对于非第一个StrSeg
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
			{  //获得剥蚀事件或沉积间断的第一个StrSeg的静水压力和静岩压力
				StaticPt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;
				StaticPb=StaticPt;
				Plt=0.1*1.0e6+SeaWaterDensity*9.8*PaleoWaterDepth;  //水表面净水压力等于一个大气压，即0.1MPa
				Plb=Plt;
			}
			
			void GetThickness()
			{
				Thickness=MatrixThickness/(1.-Porom);
			}
			
			void GetDepths() //获得相关深度值
			{    //对于第一个StrSeg
					BuryBottomDepth=BuryTopDepth+Thickness;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度,从沉积表面算起
					MiddleDepth=TopDepth+0.5*Thickness;//总的深度中部深度，从水面算起
					BottomDepth=TopDepth+Thickness;//底面深度
					MaxBuryTopDepth=BuryTopDepth;   //这里只是记录最大埋深，在超压方程中实际上并没有应用
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
			}
			
			void GetDepths(StrSeg *StrSegLeft,StrSeg *StrSegTop) //获得相关深度值
			{     //对于非第一个StrSeg
					BuryTopDepth=StrSegTop->BuryBottomDepth;  //由于在超压计算中有循环迭代过程，厚度一直在变化，因此得到的每个StrSeg的深度也在变化，因此每次计算深度时都要先得到变化的空间上的上一StrSeg的（底部）深度值
					TopDepth=StrSegTop->BottomDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度,从沉积表面算起
					BuryBottomDepth=BuryTopDepth+Thickness;
					MiddleDepth=TopDepth+0.5*Thickness;//总的深度中部深度，从水面算起
					BottomDepth=TopDepth+Thickness;//底面深度
					if((Property==1||(Property==2&&!Eroded))&&BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
					{   //如果顶部埋深大于前一时刻该StrSeg顶面最大埋深，则更新最大埋深。这里只是记录最大埋深，在超压方程中实际上并没有应用
						MaxBuryTopDepth=BuryTopDepth;
						MaxBuryMiddleDepth=BuryMiddleDepth;
						MaxBuryBottomDepth=BuryBottomDepth;
					}
					else
					{
						MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;    //最大埋深保持不变
						MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
						MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
					}
			}
			
			
			void RealThicknessCalculating()
			{ // 通过循环迭代获得稳定的厚度，基于静水压力，以及稳态的温度计算；仅针对第一个StrSeg，即[0][0][0]
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
			{  // 用于处理超压模型，包括瞬态热流模型
				TopDepth=PaleoWaterDepth;   //最顶面StrSeg顶部深度为古水深
				BuryTopDepth=0.;   //最顶面StrSeg顶部埋深为0
				if(Property==1||Property==2)
				{  //沉积过程最顶部StrSeg作用过程
				Tt=SurfaceT; //,对于第一个StrSeg, 在第一部分给出顶部温度
				Tm =SurfaceT;//首先将地表温度赋值给地层段中部温度
				Tb=SurfaceT;
				Ut=0.; Um=0.;Ub=0.; //对于第一个StrSeg，顶部、中部和底部的超压都设为0
				Porosityt=new double[LithNumber];
				Porositym=new double[LithNumber];
				Porosityb=new double[LithNumber];
				//由于是第一个StrSeg，因此可以采用等效静水压力深度进行厚度和孔隙度的计算作为下面迭代的初始值
				GetBuryBottomDepth();
				Thickness=BuryBottomDepth-BuryTopDepth;
				BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度
				MiddleDepth=TopDepth+0.5*Thickness;//总的中部深度，从水面算起
				BottomDepth=TopDepth+Thickness; //底部深度
				MaxBuryTopDepth=BuryTopDepth;
				MaxBuryMiddleDepth=BuryMiddleDepth;
				MaxBuryBottomDepth=BuryBottomDepth;
				GetPorosity();
				}
				if(Property==3)
				{ //剥蚀事件最顶部StrSeg作用过程，剥蚀事件也按埋藏过程处理
					//由于在超压模拟过程中，虚层（非虚层也一样）的StrSeg的厚度是变化的，因此对应的剥蚀事件的StrSeg的厚度就不能用恒定的值CurrentThickness了，
					//而需要在第一次遇到一个剥蚀事件的StrSeg时，寻找对应虚层的StrSeg，将该虚层StrSeg的厚度Thickness赋值给这一剥蚀事件StrSeg的厚度（当然要变成负值了），这需要在外面操作，就不再这里赋值了。
				BottomDepth=TopDepth+Thickness;//底面深度
				BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度 ，因此底面埋深就是负值
				GetStaticPAndPlOfTheFirstStrSeg();  //获得剥蚀事件的第一个StrSeg的静水压力和静岩压力
				Tt=SurfaceT;
				Tb=Tt; //剥蚀事件StrSeg对温度是透明的
				}
				if(Property==4)
				{ //沉积间断事件最顶部StrSeg作用过程，间断事件也按埋藏过程处理
				Thickness=CurrentThickness;  //将CurrentThickness赋值给Thickness，显然对于间断事件，其厚度是0
				BottomDepth=TopDepth+Thickness;//底面深度
				BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度 ，因此底面埋深就是0
				GetStaticPAndPlOfTheFirstStrSeg(); //获得沉积间断的第一个StrSeg的静水压力和静岩压力
				Tt=SurfaceT;
				Tb=Tt; //间断事件StrSeg对温度是透明的
				}
			}
			
			void GetFromNearbyStrSegOP01(StrSeg *StrSegLeft, StrSeg *StrSegTop) //通过左侧（即时间上的上一步）和上部（即空间上的）StrSeg获得信息
			{ //此函数应用于非初始StrSeg；适用于各种地层段属性的情况 ;   // 用于处理超压以及瞬态热流模型
				aPetroGenStyle=StrSegLeft->aPetroGenStyle; ///new added 2017-11-22
				BeginAge=StrSegTop->BeginAge ;   //给各段赋时间值
				EndAge=StrSegTop->EndAge ;
				MiddleAge=StrSegTop->MiddleAge ;
				DeltaAge=StrSegTop->DeltaAge ;
				TopDepth=StrSegTop->BottomDepth;  //顶部深度永远等于上部StrSeg的底部深度
				BuryTopDepth=StrSegTop->BuryBottomDepth;  //顶部深度永远等于上部StrSeg的底部深度
				PaleoWaterDepth=StrSegTop->PaleoWaterDepth; //古水深等于顶部地层段的古水深 ，，其实该古水深在非第一个StrSeg上可能一直没有用到
				HF=StrSegTop->HF; //热流等于顶部地层段的热流
				SurfaceT=StrSegTop->SurfaceT; //表面温度由上面的StrSeg的表明温度传来
				MatrixThickness=StrSegLeft->MatrixThickness;//从上一个时间段(即左侧)的StrSeg获得骨架厚度
				EndPorom=StrSegLeft->EndPorom;
				SourceRock=StrSegLeft->SourceRock ;   //从上一个时间段的StrSeg获得是否为源岩的信息
				if(SourceRock) TOC=StrSegLeft->TOC ;     //从上一个时间段的StrSeg获得残余有机碳含量
				Tt=StrSegLeft->Tt; //将上一时间StrSeg的顶部温度赋值给现在StrSeg的顶部温度
				Tm =StrSegLeft->Tm;//将上一时间StrSeg的中部温度赋值给现在StrSeg的中部温度
				Tb =StrSegLeft->Tb;//将上一时间StrSeg的底部温度赋值给现在StrSeg的底部温度
				Ut=StrSegLeft->Ut; Um=StrSegLeft->Um;Ub=StrSegLeft->Ub; //将上一时间段的超压值赋值给该时间段
				WaterDensity=StrSegLeft->WaterDensity; //将上一时间段的水密度传给本时间段的StrSeg，作为计算静水压力的起始数据
				//根据不同的StrSeg性质进行不同的判断和操作
				if(Property==1)
				{   //是地层的情况
				Porosityt=new double[LithNumber];
				Porositym=new double[LithNumber];
				Porosityb=new double[LithNumber];
				for(int i=0;i<LithNumber;i++)//将上一时刻孔隙度值赋值给这时刻的孔隙度，作为迭代的初始孔隙度值
					{
					Porosityt[i]=StrSegLeft->Porosityt[i];
					Porositym[i]=StrSegLeft->Porositym[i];
					Porosityb[i]=StrSegLeft->Porosityb[i];
					}
				Thickness=StrSegLeft->Thickness ;//将上一个时间段的StrSeg厚度赋值给该时刻该StrSeg的厚度。作为迭代计算初始值用
				Porot=StrSegLeft->Porot;
				Porom=StrSegLeft->Porom;
				Porob=StrSegLeft->Porob;
				GetDepths(StrSegLeft,StrSegTop);  // 虽然该函数在这里应用了，但对于后面的计算没影响，因为静岩或静水压力的计算都是基于每个StrSeg的累积
				}
				if(Property==2)
				{ //如果是虚拟层 ----开始
				if(!StrSegLeft->Eroded) //如果没被剥蚀过，就按正常的地层处理
					{ //*********************************************
					Porosityt=new double[LithNumber];
					Porositym=new double[LithNumber];
					Porosityb=new double[LithNumber];
					for(int i=0;i<LithNumber;i++)//将上一时刻孔隙度值赋值给这时刻的孔隙度，作为迭代的初始孔隙度值
					{
						Porosityt[i]=StrSegLeft->Porosityt[i];
						Porositym[i]=StrSegLeft->Porositym[i];
						Porosityb[i]=StrSegLeft->Porosityb[i];
					}
					Thickness=StrSegLeft->Thickness ;//将上一个时间段的StrSeg厚度赋值给该时刻该StrSeg的厚度。
					Porot=StrSegLeft->Porot;
					Porom=StrSegLeft->Porom;    //将上一时间段StrSeg的孔隙度传给这一时间段，作为一些参数计算的初始值
					Porob=StrSegLeft->Porob;
					GetDepths(StrSegLeft,StrSegTop);  
					if(BuryBottomDepth<MarginOfErrorThickness)  //给定一定的误差容错值，这里为 1cm
						{ // 如果底部深度小于一定的误差容错值，表明该地层段已经被剥蚀了
						Eroded=true; //当底部埋深等于0时，说明已经被剥蚀，将Eroded属性设为true
						StaticPt=StrSegTop->StaticPb; //将上部的StrSeg底部的静水压力赋值给该StrSeg顶部的静水压力
						StaticPb=StaticPt;     //剥蚀或间断事件的StrSeg对静水压力透明，起传导作用
						Plt=StrSegTop->Plb;  //将上部的StrSeg底部的静岩压力赋值给该StrSeg顶部静岩压力
						Plb=Plt;
						}
					} //*********************************************
				if(StrSegLeft->Eroded)
					{  //如果已经被剥蚀了，再计算时厚度保持不变，与剥蚀StrSeg构成消减对---即它们作用（厚度）之和为0
					Eroded=true;
					Thickness=StrSegLeft->Thickness;
					Porosityt=new double[LithNumber];
					Porositym=new double[LithNumber];
					Porosityb=new double[LithNumber];
					for(int i=0;i<LithNumber;i++)//将上一时刻孔隙度值赋值给这时刻的孔隙度，作为迭代的初始孔隙度值
					{
						Porosityt[i]=StrSegLeft->Porosityt[i];
						Porositym[i]=StrSegLeft->Porositym[i];
						Porosityb[i]=StrSegLeft->Porosityb[i];
					}
					Porot=StrSegLeft->Porot;  //顶部、中部和底部孔隙度只是这样传过来，在显示或作图时可以在剥蚀后的时间段上一直有数值
					Porom=StrSegLeft->Porom;  //虚层的孔隙度值在最后计算循环迭代的MatrixThickness时起作用
					Porob=StrSegLeft->Porob;
					GetDepths(StrSegLeft,StrSegTop);
					StaticPt=StrSegTop->StaticPb; //将上部的StrSeg底部的静水压力赋值给该StrSeg顶部的静水压力
					StaticPb=StaticPt;     //已经剥蚀了虚层的StrSeg对静水压力透明，起传导作用
					Plt=StrSegTop->Plb;  //将上部的StrSeg底部的静岩压力赋值给该StrSeg顶部静岩压力
					Plb=Plt;             //已经剥蚀了虚层的StrSeg对静岩压力透明，起传导作用
					}
				}  //如果是虚拟层 ----结束
				if(Property==3)
				{  
					Thickness=StrSegLeft->Thickness; //由于这里的剥蚀事件的StrSeg不是初始时刻出现，在后续的时间段中其厚度保持不变，因此厚度Thickness在这里赋值
					BottomDepth=TopDepth+Thickness;//底面深度
					BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度
					StaticPt=StrSegTop->StaticPb; //将上部的StrSeg底部的静水压力赋值给该StrSeg顶部的静水压力
					StaticPb=StaticPt;     //剥蚀或间断事件的StrSeg对静水压力透明，起传导作用
					Plt=StrSegTop->Plb;  //将上部的StrSeg底部的静岩压力赋值给该StrSeg顶部静岩压力
					Plb=Plt;
				}
				if(Property==4)
				{ //如果是间断事件属性，只有厚度和底部深度参数是有作用的
					Thickness=StrSegLeft->Thickness;   //由于不是第一个StrSeg，间断事件的厚度只需将前一时间段的Thickness传过来就可以了
					BottomDepth=TopDepth+Thickness;//底面深度
					BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度
					StaticPt=StrSegTop->StaticPb; //将上部的StrSeg底部的静水压力赋值给该StrSeg顶部的静水压力
					StaticPb=StaticPt;     //剥蚀或间断事件的StrSeg对静水压力透明，起传导作用
					Plt=StrSegTop->Plb;  //将上部的StrSeg底部的静岩压力赋值给该StrSeg顶部静岩压力
					Plb=Plt;
				}
			}     
			
			void GetIfItIsTheTopestStrSegPart01()
			{  // 用于处理瞬态热流模型
				TopDepth=PaleoWaterDepth;   //最顶面StrSeg顶部深度为古水深
				BuryTopDepth=0.;   //最顶面StrSeg顶部埋深为0
				if(Property==1||Property==2)
				{  ////沉积过程最顶部StrSeg作用过程
				GetBuryBottomDepth();  //  通过该函数获得埋藏底部深度
				Thickness=BuryBottomDepth-BuryTopDepth;
				BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度
				MiddleDepth=TopDepth+0.5*Thickness;  //总的中部深度，从水面算起
				BottomDepth=TopDepth+Thickness;  //总的底部深度，从水面算起
				MaxBuryTopDepth=BuryTopDepth;      //
				MaxBuryMiddleDepth=BuryMiddleDepth;
				MaxBuryBottomDepth=BuryBottomDepth;
				GetPorosity();
				GetPermeability();
				Tt=SurfaceT; //,对于第一个StrSeg, 在第一部分给出顶部温度
				Tm =SurfaceT;//首先将地表温度赋值给地层段中部温度
				Tb=SurfaceT;
				}
				if(Property==3||Property==4)
				{ //剥蚀或沉积间断事件最顶部StrSeg作用过程，剥蚀或间断事件也按埋藏过程处理
				Thickness=CurrentThickness;  //将CurrentThickness赋值给Thickness，这里的厚度都是负数或0
				BottomDepth=TopDepth+Thickness;//底面深度
				BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度 ，因此底面埋深就是负值或0
				Tt=SurfaceT;
				Tb=Tt; //剥蚀或间断事件StrSeg对温度是透明的
				}
			}
			
			void GetIfItIsTheTopestStrSegPart02()
			{ // 用于处理瞬态热流模型 ，也用于超压模型的后半部分计算
				if(Property==1||Property==2)
				{  ////沉积过程最顶部StrSeg作用过程
				Tmax=Tm; //将地层段中部的温度赋值给Tmax
				GetTTI(); //获得第一个地层段的TTI

				GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
				GetRoFromEasyRo(); //获得EasyRo方法得到的Ro值   ！！！！不能删除
				GetRoFromBasinRo(); //获得BasinRo方法得到的Ro值
				GetRoFromSimpleRo(); //获得SimpleRo方法得到的Ro值  ！！！！不能删除
				
				if(SourceRock)
					{
					GetHCGIPerUnitInitTOC(); //如果是源岩，则计算单位质量(kg)原始有机碳的降解量 ，降解量-Ro方法
					GetInitTOC();  //获得原始有机碳含量和质量      ，降解量-Ro方法
					GainHCGIPerUnitInitTOC();  //LLNL 化学反应动力学计算方法
					GainInitTOC(); //获得原始有机碳含量和质量 ，化学动力学方法
					// GetEEFromRo();  //根据Ro获得排烃效率
					// FlashCalculation();  
					//  GetTRFromDR();  // //获得来自降解率方法的油气转化率
					// GetEEFromTR();  //通过TR获得排油效率和排气效率
					}
				}
			}
			
			void GetIfItIsTheTopestStrSeg()
			{  //最顶部的StrSeg处理函数 ，沉积过程和剥蚀过程一并处理，根据StrSeg性质Property判断 ，稳态热传导模型
				TopDepth=PaleoWaterDepth;   //最顶面StrSeg顶部深度为古水深
				BuryTopDepth=0.;   //最顶面StrSeg顶部埋深为0
				if(Property==1||Property==2)
				{  ////沉积过程最顶部StrSeg作用过程
					GetMatrixDensity();//2017/10/13: new added method
					GetBuryBottomDepth();
					Thickness=BuryBottomDepth-BuryTopDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度
					MiddleDepth=TopDepth+0.5*Thickness;//总的中部深度，从水面算起
					BottomDepth=TopDepth+Thickness; //底部深度
					MaxBuryTopDepth=BuryTopDepth;      //
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
					GetPorosity();
					GetT(); //根据稳态热传导获得温度
					Tmax=Tm; //将地层段中部的温度赋值给Tmax
					GetTTI(); //获得第一个地层段的TTI

					GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
					GetRoFromEasyRo(); //获得EasyRo方法得到的Ro值   ！！！！不能删除
					GetRoFromBasinRo(); //获得BasinRo方法得到的Ro值
					GetRoFromSimpleRo(); //获得SimpleRo方法得到的Ro值  ！！！！不能删除

					//2017/7/18: add density
					GetMatrixDensity();

					if(SourceRock)
					{
						GetHCGIPerUnitInitTOC(); //如果是源岩，则计算单位质量(kg)原始有机碳的降解量 ，降解量-Ro方法
						GetInitTOC();  //获得原始有机碳含量和质量      ，降解量-Ro方法
						GainHCGIPerUnitInitTOC();  //LLNL 化学反应动力学计算方法
						GainInitTOC(); //获得原始有机碳含量和质量 ，化学动力学方法
					}
				}
				if(Property==3||Property==4)
				{ //剥蚀或沉积间断事件最顶部StrSeg作用过程，剥蚀或间断事件也按埋藏过程处理
				Thickness=CurrentThickness;  //将CurrentThickness赋值给Thickness，这里的厚度都是负数或0
				BottomDepth=TopDepth+Thickness;//底面深度
				BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度 ，因此底面埋深就是负值或0
				Tt=SurfaceT;
				Tb=Tt; //剥蚀或间断事件StrSeg对温度是透明的
				}
			}
			
			void GetFromNearbyStrSegPart01(StrSeg *StrSegLeft, StrSeg *StrSegTop) //通过左侧（即时间上的上一步）和上部（即空间上的）StrSeg获得信息
			{ //此函数应用于非初始StrSeg；适用于各种地层段属性的情况 ;   // 用于处理瞬态热流模型
				aPetroGenStyle=StrSegLeft->aPetroGenStyle; ///new added 2017-11-22
				BeginAge=StrSegTop->BeginAge ;   //给各段赋时间值
				EndAge=StrSegTop->EndAge ;
				MiddleAge=StrSegTop->MiddleAge ;
				DeltaAge=StrSegTop->DeltaAge ;
				TopDepth=StrSegTop->BottomDepth;  //顶部深度永远等于上部StrSeg的底部深度
				BuryTopDepth=StrSegTop->BuryBottomDepth;  //顶部深度永远等于上部StrSeg的底部深度
				PaleoWaterDepth=StrSegTop->PaleoWaterDepth; //古水深等于顶部地层段的古水深 ，，其实该古水深在非第一个StrSeg上可能一直没有用到
				HF=StrSegTop->HF; //热流等于顶部地层段的热流
				SurfaceT=StrSegTop->SurfaceT; //表面温度由上面的StrSeg的表明温度传来
				MatrixThickness=StrSegLeft->MatrixThickness;//从上一个时间段(即左侧)的StrSeg获得骨架厚度
				SourceRock=StrSegLeft->SourceRock ;   //从上一个时间段的StrSeg获得是否为源岩的信息
				if(SourceRock) TOC=StrSegLeft->TOC ;     //从上一个时间段的StrSeg获得残余有机碳含量
				Tt=StrSegLeft->Tt; //将上一时间StrSeg的顶部温度赋值给现在StrSeg的顶部温度
				Tm =StrSegLeft->Tm;//将上一时间StrSeg的中部温度赋值给现在StrSeg的中部温度
				Tb =StrSegLeft->Tb;//将上一时间StrSeg的底部温度赋值给现在StrSeg的底部温度
				StaticPt=StrSegLeft->StaticPt;  //将上一时间段的静水压力传给本时间段的StrSeg，作为计算水密度的起始数据  ,
				StaticPm=StrSegLeft->StaticPm;
				StaticPb=StrSegLeft->StaticPb;
				Pt=StrSegLeft->Pt;  //将上一时间段的水压力传给本时间段的StrSeg，作为计算水密度的起始数据 ,在没有异常压力存在的情况下，认为水压力等于静水压力
				Pm=StrSegLeft->Pm;
				Pb=StrSegLeft->Pb;
				WaterDensity=StrSegLeft->WaterDensity; //将上一时间段的水密度传给本时间段的StrSeg，作为计算静水压力的起始数据
				//根据不同的StrSeg性质进行不同的判断和操作
				//====================================
				if(Property==1)
				{   //是地层的情况
				if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
				{   //判断顶部埋深大于最大埋深，则进行压实过程
					GetBuryBottomDepth();  //
					Thickness=BuryBottomDepth-BuryTopDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度,从沉积表面算起
					MiddleDepth=TopDepth+0.5*Thickness;//总的深度中部深度，从水面算起
					BottomDepth=TopDepth+Thickness;//底面深度
					MaxBuryTopDepth=BuryTopDepth;      //  更新最大埋深
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
					GetPorosity();      //获得孔隙度
				}
				else
				{ //当顶部深度小于等于最大顶部埋深时，厚度不变，最大埋深不变
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//底面深度
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//中部深度
					BottomDepth=TopDepth+Thickness;//底面深度
					MiddleDepth=TopDepth+0.5*Thickness;//中部深度
					MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;    //最大埋深保持不变
					MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
					MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
					Porom=StrSegLeft->Porom;  //孔隙度保持不变

					//2019/1/24: add top,bottom value
					Porot=StrSegLeft->Porot;  //孔隙度保持不变,t
					Porob=StrSegLeft->Porob;  //孔隙度保持不变,b
				}
				}
				if(Property==2)
				{ //如果是虚拟层 ----开始
				if(!StrSegLeft->Eroded) //如果没被剥蚀过，就按正常的地层处理
					{ //*********************************************
					if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
					{  //当顶部深度大于最大埋藏深度，说明处于沉降过程，按压实过程处理
						GetBuryBottomDepth();  //
						Thickness=BuryBottomDepth-BuryTopDepth;
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度,从沉积表面算起
						MiddleDepth=TopDepth+0.5*Thickness;//总的深度中部深度，从水面算起
						BottomDepth=TopDepth+Thickness;//底面深度
						MaxBuryTopDepth=BuryTopDepth;      //  更新最大埋深
						MaxBuryMiddleDepth=BuryMiddleDepth;
						MaxBuryBottomDepth=BuryBottomDepth;
						GetPorosity();      //获得孔隙度
						GetPermeability();
					}
					else
					{ //当顶部深度小于等于最大顶部埋深时，厚度不变，最大埋深不变
						//这时的虚层有三种状态，其一是还没被剥蚀，其二是已经被剥蚀，其三是部分剥蚀
						// 下面两个if()之上的部分处理的是还没剥蚀的情况，同时对全部和部分剥蚀也起作用
						Thickness=StrSegLeft->Thickness;
						BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//中部埋藏深度
						BottomDepth=TopDepth+Thickness;//底面深度
						MiddleDepth=TopDepth+0.5*Thickness;//中部深度
						MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;
						MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
						MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
						Porom=StrSegLeft->Porom;

						//2019/1/24: add top,bottom value
						Porot=StrSegLeft->Porot;  //孔隙度保持不变,t
						Porob=StrSegLeft->Porob;  //孔隙度保持不变,b

						if(BuryBottomDepth<MarginOfErrorThickness)  //给定一定的误差容错值，这里为 1cm
						{ // 如果底部深度等于0了，表明该地层段已经被剥蚀了
						Eroded=true; //当底部埋深等于0时，说明已经被剥蚀，将Eroded属性设为true
						}
					}
					} //*********************************************
				if(StrSegLeft->Eroded)
					{  //如果已经被剥蚀了，再计算时厚度保持不变，与剥蚀StrSeg构成消减对---即它们作用（厚度）之和为0
					Eroded=true;
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//埋藏底面深度
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度
					BottomDepth=TopDepth+Thickness;//底面深度
					MiddleDepth=TopDepth+0.5*Thickness;//中部深度
					Porom=StrSegLeft->Porom;   //被剥蚀后仍保持原先的孔隙度，主要用于生烃量计算——用于计算有机碳 和原始有机碳量
					}
				}  //如果是虚拟层 ----结束
				if(Property==3||Property==4)
				{ //如果是剥蚀或间断事件属性，只有厚度和底部深度参数是有作用的
					Thickness=StrSegLeft->Thickness;
					BottomDepth=TopDepth+Thickness;//底面深度
					BuryBottomDepth=BuryTopDepth+Thickness;//底面深度
				}
			}
			
			void GetFromNearbyStrSegPart02(StrSeg *StrSegLeft, StrSeg *StrSegTop) //通过左侧（即时间上的上一步）和上部（即空间上的）StrSeg获得信息
			{ //此函数应用于非初始StrSeg；适用于各种地层段属性的情况 ;   // 用于处理瞬态热流模型 ,也用于超压模型
				if(Property==1)
				{   //是地层的情况---开始
					//  FlashCalculation(StrSegLeft);  //暂时只对有油气生成的源岩进行计算
					GetTmax(StrSegLeft); //获得现在或之前的最高温度
					GetTTI(StrSegLeft);//获得TTI值

					GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
					GetRoFromEasyRo(StrSegLeft); //获得EasyRo方法得到的Ro值  ！！！！不能删除
					GetRoFromBasinRo(StrSegLeft); //获得BasinRo方法得到的Ro值
					GetRoFromSimpleRo(StrSegLeft); //获得SimpleRo方法得到的Ro值 ！！！！不能删除
					
					if(SourceRock)
					{
						GetHCGIPerUnitInitTOC(StrSegLeft); //如果是源岩，则计算单位质量(kg)原始有机碳的降解量 ，降解量-Ro方法
						GetInitTOC();  //获得原始有机碳含量和质量 ，降解量-Ro方法
						GainHCGIPerUnitInitTOC(StrSegLeft); //获得单位原始有机碳生油气量，化学动力学方法
						GainInitTOC(); //获得原始有机碳含量和质量 ，化学动力学方法
						// FlashCalculation(StrSegLeft);
						// GetEEFromRo();  //根据Ro获得排烃效率
						//  GetTRFromDR();  // //获得来自降解率方法的油气转化率
						//  GetEEFromTR();  //通过TR获得排油效率和排气效率
					}
				} //是地层的情况---结束
				if(Property==2)
				{ //如果是虚拟层----开始
				if(!Eroded) //如果没被剥蚀过，就按正常的地层处理
					{ //*********************************************
						GetTmax(StrSegLeft); //获得现在或之前的最高温度
						GetTTI(StrSegLeft);//获得TTI值

						GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
						GetRoFromEasyRo(StrSegLeft); //获得EasyRo方法得到的Ro值    ！！！！不能删除
						GetRoFromBasinRo(StrSegLeft); //获得BasinRo方法得到的Ro值
						GetRoFromSimpleRo(StrSegLeft); //获得SimpleRo方法得到的Ro值   ！！！！不能删除
						 //FlashCalculation(StrSegLeft);
					} //*********************************************
				if(Eroded)
					{  //如果已经被剥蚀
						Tt=StrSegTop->Tb;
						Tb=Tt;       //当被剥蚀后，该StrSeg对温度透明
						//Ro=StrSegLeft->Ro;       //仍保持原先的镜质体反射率，用于计算热降解，其实Ro保持之前的状态也意味着热降解率不变
						for (int i = RO_TTI; i <= RO_Basin; i++)
						{
							Ro[i] = StrSegLeft->Ro[i];
						}

					}
				if(SourceRock)
					{    //虽然是剥蚀了的虚地层，但也与正常地层一样计算生烃强度，只不过剥蚀后任何时候的生烃强度都与剥蚀前的生烃强度一致
					GetHCGIPerUnitInitTOC(StrSegLeft); //如果是源岩，则计算单位质量(kg)原始有机碳的降解量  ,降解量-Ro方法
					GetInitTOC();  //获得原始有机碳含量和质量    ,降解量-Ro方法
					GainHCGIPerUnitInitTOC(StrSegLeft); //获得单位原始有机碳生油气量，化学动力学方法
					GainInitTOC(); //获得原始有机碳含量和质量 ，化学动力学方法
					}
				} //如果是虚拟层----结束
				if(Property==3||Property==4)
				{ //如果是剥蚀或间断事件属性
					Tt=StrSegTop->Tb;
					Tb=Tt;       //剥蚀和间断事件的StrSeg对温度透明
				}
			}

			void GetFromNearbyStrSeg(StrSeg *StrSegLeft, StrSeg *StrSegTop) //通过左侧（即时间上的上一步）和上部（即空间上的）StrSeg获得信息
			{    //此函数应用于非初始StrSeg；适用于各种地层段属性的情况
				aPetroGenStyle=StrSegLeft->aPetroGenStyle; ///new added 2017-11-22
				BeginAge=StrSegTop->BeginAge ;   //给各段赋时间值
				EndAge=StrSegTop->EndAge ;
				DeltaAge=StrSegTop->DeltaAge ;
				MiddleAge=StrSegTop->MiddleAge ;
				TopDepth=StrSegTop->BottomDepth;  //顶部深度永远等于上部StrSeg的底部深度
				BuryTopDepth=StrSegTop->BuryBottomDepth;  //顶部深度永远等于上部StrSeg的底部深度
				PaleoWaterDepth=StrSegTop->PaleoWaterDepth; //古水深等于等不地层段的古水深
				HF=StrSegTop->HF; //热流等于顶部地层段的热流
				SurfaceT=StrSegTop->SurfaceT; //表面温度由上面的StrSeg的表明温度传来
				MatrixThickness=StrSegLeft->MatrixThickness;//从上一个时间段(即左侧)的StrSeg获得骨架厚度
				SourceRock=StrSegLeft->SourceRock ;   //从上一个时间段的StrSeg获得是否为源岩的信息
				
				//2017/7/18:add density
				TMatrixDensity = StrSegLeft->TMatrixDensity;

				if(SourceRock) TOC=StrSegLeft->TOC ;     //从上一个时间段的StrSeg获得残余有机碳含量
				//根据不同的StrSeg性质进行不同的判断和操作
				//====================================
				if(Property==1)
				{   //是地层的情况
				if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
				{   //判断顶部埋深大于最大埋深，则进行压实过程
					GetBuryBottomDepth();
					Thickness=BuryBottomDepth-BuryTopDepth;
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度,从沉积表面算起
					MiddleDepth=TopDepth+0.5*Thickness;//中部深度
					BottomDepth=TopDepth+Thickness;//底面深度
					MaxBuryTopDepth=BuryTopDepth;      //  更新最大埋深
					MaxBuryMiddleDepth=BuryMiddleDepth;
					MaxBuryBottomDepth=BuryBottomDepth;
					GetPorosity();             //获得孔隙度
				}
				else
				{ //当顶部埋藏深度小于等于最大顶部埋深时，厚度不变，最大埋深不变
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//底面深度
					BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//中部深度
					BottomDepth=TopDepth+Thickness;//底面深度
					MiddleDepth=TopDepth+0.5*Thickness;//中部深度
					MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;    //最大埋深保持不变
					MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
					MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
					Porom=StrSegLeft->Porom;            //孔隙度保持不变

					//2019/1/24: add top,bottom value
					Porot=StrSegLeft->Porot;  //孔隙度保持不变,t
					Porob=StrSegLeft->Porob;  //孔隙度保持不变,b
				}
				GetT(StrSegLeft, StrSegTop); //获得温度
				GetTmax(StrSegLeft); //获得现在或之前的最高温度
				GetTTI(StrSegLeft);//获得TTI值

				GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
				GetRoFromEasyRo(StrSegLeft); //获得EasyRo方法得到的Ro值  ！！！！不能删除
				GetRoFromBasinRo(StrSegLeft); //获得BasinRo方法得到的Ro值
				GetRoFromSimpleRo(StrSegLeft); //获得SimpleRo方法得到的Ro值 ！！！！不能删除
				if(SourceRock)
					{
					GetHCGIPerUnitInitTOC(StrSegLeft); //如果是源岩，则计算单位质量(kg)原始有机碳的降解量 ，降解量-Ro方法
					GetInitTOC();  //获得原始有机碳含量和质量 ，降解量-Ro方法
					GainHCGIPerUnitInitTOC(StrSegLeft); //获得单位原始有机碳生油气量，化学动力学方法
					GainInitTOC(); //获得原始有机碳含量和质量 ，化学动力学方法
					}
				}
				//===================
				if(Property==2)
				{ //如果是虚拟层
				if(!StrSegLeft->Eroded) //如果没被剥蚀过，就按正常的地层处理
					{ //*********************************************
					if(BuryTopDepth>StrSegLeft->MaxBuryTopDepth)
					{  //当顶部深度大于最大埋藏深度，说明处于沉降过程，按压实过程处理
						GetBuryBottomDepth();  //
						Thickness=BuryBottomDepth-BuryTopDepth;
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度,从沉积表面算起
						MiddleDepth=TopDepth+0.5*Thickness;//总的深度中部深度，从水面算起
						BottomDepth=TopDepth+Thickness;//底面深度
						MaxBuryTopDepth=BuryTopDepth;      //  更新最大埋深
						MaxBuryMiddleDepth=BuryMiddleDepth;
						MaxBuryBottomDepth=BuryBottomDepth;
						GetPorosity();      //获得孔隙度
						GetT(StrSegLeft, StrSegTop); //获得温度
						GetTmax(StrSegLeft); //获得现在或之前的最高温度
						GetTTI(StrSegLeft);//获得TTI值

						GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
						GetRoFromEasyRo(StrSegLeft); //获得EasyRo方法得到的Ro值    ！！！！不能删除
						GetRoFromBasinRo(StrSegLeft); //获得BasinRo方法得到的Ro值
						GetRoFromSimpleRo(StrSegLeft); //获得SimpleRo方法得到的Ro值   ！！！！不能删除
					}
					else
					{ //当顶部深度小于等于最大顶部埋深时，厚度不变，最大埋深不变
						//这时的虚层有两种状态，其一是还没被剥蚀，其二是已经被剥蚀
						// 下面两个if()之上的部分处理的是还没剥蚀的情况，同时对全部和部分剥蚀也起作用
						Thickness=StrSegLeft->Thickness;
						BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//中部埋藏深度
						BottomDepth=TopDepth+Thickness;//底面深度
						MiddleDepth=TopDepth+0.5*Thickness;//中部深度
						MaxBuryTopDepth=StrSegLeft->MaxBuryTopDepth;
						MaxBuryMiddleDepth=StrSegLeft->MaxBuryMiddleDepth;
						MaxBuryBottomDepth=StrSegLeft->MaxBuryBottomDepth;
						Porom=StrSegLeft->Porom;

						//2019/1/24: add top,bottom value
						Porot=StrSegLeft->Porot;  //孔隙度保持不变,t
						Porob=StrSegLeft->Porob;  //孔隙度保持不变,b

						if(BuryBottomDepth<MarginOfErrorThickness)  //给定一定的误差容错值，这里为 1cm
						{ // 如果底部深度小于0了，表明该地层段已经被完全剥蚀了
							Eroded=true; //当底部埋深小于0时，说明已经被剥蚀，将Eroded属性设为true
							Tt=StrSegTop->Tb;
							Tm=Tt;
							Tb=Tt;       //当被剥蚀后，该StrSeg对温度透明
							
							//Ro=StrSegLeft->Ro; //被剥蚀了Ro始终保持以前的值
							for (int i = RO_TTI; i <= RO_Basin; i++)
							{
								Ro[i] = StrSegLeft->Ro[i];
							}
						}
						else
						{  //如果没有剥蚀
							GetT(StrSegLeft, StrSegTop); //该函数已经处理了关于部分剥蚀的情况。
							GetTmax(StrSegLeft); //获得现在或之前的最高温度
							GetTTI(StrSegLeft);//获得TTI值

							GetRoFromTTIRo();//2017/7/25: get ro by tti-ro
							GetRoFromEasyRo(StrSegLeft); //获得EasyRo方法得到的Ro值   ！！！！不能删除
							GetRoFromBasinRo(StrSegLeft); //获得BasinRo方法得到的Ro值
							GetRoFromSimpleRo(StrSegLeft); //获得SimpleRo方法得到的Ro值  ！！！！不能删除
						}
					}
					} //*********************************************
				if(StrSegLeft->Eroded)
					{  //如果已经被剥蚀了，再计算时厚度保持不变，与剥蚀StrSeg构成消减对---即它们作用（厚度）之和为0
						Eroded=true;
						Thickness=StrSegLeft->Thickness;
						BuryBottomDepth=BuryTopDepth+Thickness;//埋藏底面深度
						BuryMiddleDepth=BuryTopDepth+0.5*Thickness;//埋藏中部深度
						BottomDepth=TopDepth+Thickness;//底面深度
						MiddleDepth=TopDepth+0.5*Thickness;//中部深度
						Porom=StrSegLeft->Porom;   //被剥蚀后仍保持原先的孔隙度，主要用于生烃量计算——用于计算有机碳 和原始有机碳量
						Tt=StrSegTop->Tb;
						Tm=Tt;
						Tb=Tt;       //当被剥蚀后，该StrSeg对温度透明
						//Ro=StrSegLeft->Ro;       //仍保持原先的镜质体反射率，用于计算热降解，其实Ro保持之前的状态也意味着热降解率不变

						for (int i = RO_TTI; i <= RO_Basin; i++)
						{
							Ro[i] = StrSegLeft->Ro[i];
						}
					}
					if(SourceRock)
					{    //虽然是剥蚀了的虚地层，但也与正常地层一样计算生烃强度，只不过剥蚀后任何时候的生烃强度都与剥蚀前的生烃强度一致
						GetHCGIPerUnitInitTOC(StrSegLeft); //如果是源岩，则计算单位质量(kg)原始有机碳的降解量  ,降解量-Ro方法
						GetInitTOC();  //获得原始有机碳含量和质量    ,降解量-Ro方法
						GainHCGIPerUnitInitTOC(StrSegLeft); //获得单位原始有机碳生油气量，化学动力学方法
						GainInitTOC(); //获得原始有机碳含量和质量 ，化学动力学方法
					}
				}
				//=======================================
				if(Property==3||Property==4)
				{ //如果是剥蚀或间断事件属性，只有厚度和底部深度参数是有作用的
					Thickness=StrSegLeft->Thickness;
					BuryBottomDepth=BuryTopDepth+Thickness;//底面埋藏深度
					BottomDepth=TopDepth+Thickness;//底面深度
					Tt=StrSegTop->Tb;
					Tb=Tt;       //剥蚀事件StrSeg对温度透明
				}
			}
			
			void GetMatrixThickness()
			{   //获得岩石骨架厚度 ;;根据最大顶深和底深获得骨架厚度
				double tempTop=0.,tempBottom=0.;
				for(int i=0;i<LithNumber;i++)
				{
					tempTop+=LithRatio[i]*PorosityToDepthExpDivByComp(InitialPorosity[i],CompactionFactor[i], MaxBuryTopDepth);
					tempBottom+=LithRatio[i]*PorosityToDepthExpDivByComp(InitialPorosity[i],CompactionFactor[i], MaxBuryBottomDepth);
				}
				MatrixThickness=(MaxBuryBottomDepth-MaxBuryTopDepth+tempBottom-tempTop);
			}
			
			void GetEndPorom()
			{ //获得现今地层孔隙度
				EndPorom=1.-MatrixThickness/CurrentThickness; 
			}
			
			void GetBuryBottomDepth()
			{  //根据顶部深度获得底部深度，迭代法获得
				int kk=0;
				double tempBuryBottomDepth1=BuryTopDepth+MatrixThickness; //迭代的初始底部深度设为顶部深度
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
				//孔隙度与深度指数变化关系，并被CompactionFactor除，用于厚度恢复之用；
				//输入相应的岩石初始孔隙度和压实系数,输入的深度单位为m
				double OutPut;
				if(fabs(InitPoro)<1.0e-8) OutPut=0.;   //如果岩石初始孔隙度为0，则输出结果为0
				else OutPut= InitPoro*exp(-CompF*Depth)/CompF;
				return  OutPut;
			}

			void GetPorosity()
			{  //根据混合岩性比例获得孔隙度，该函数是针对等效深度算法，即认为埋藏深度就是等效深度
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
					LogPermeability[i]=GetPermeabilityFromPorosity(Porositym[i],3,aPoro_Perm[i].Perm.data(),aPoro_Perm[i].Poro.data());  //得到的结果 单位为Log mD
				double GeometricMeanLogPerm=0.;
				for(int i=0;i<LithNumber;i++)  
					GeometricMeanLogPerm+=LithRatio[i]*LogPermeability[i];
				
				//2017/9/6: fix overpressure problems
				Perm = ::pow(10.,GeometricMeanLogPerm);
				//Perm=exp(GeometricMeanLogPerm); //现在的单位是mD
				
				Perm/=1000.;   //转化为达西D     1md=0.98692e-3μm^2
				Perm*= 0.98692e-12; //转化为m^2     ,也就是1md=0.98692e-15m^2
			}

			double GetPermeabilityFromPorosity(double aPorosity,int NumPoroPermPairs,double *LogPerms,double *Poros)
			{ //用于获得对应于孔隙度的渗透率自然对数值
				double LogPermi; //渗透率自然对数值
				if(aPorosity*100.<=Poros[0]) LogPermi=LogPerms[0];  //由于Poro_Perm对中的孔隙度都是百分数，而输入的孔隙度为小数，因此要对输入的孔隙度值乘以100
				if(aPorosity*100.>=Poros[NumPoroPermPairs-1]) LogPermi=LogPerms[NumPoroPermPairs-1];
				for(int i=0;i<NumPoroPermPairs-1;i++)
					if(aPorosity*100.>=Poros[i]&&aPorosity*100.<Poros[i+1])
						LogPermi=LinerInterpolate( aPorosity*100.,Poros[i],LogPerms[i],Poros[i+1],LogPerms[i+1]);
				return LogPermi;
			}
		
			//void GetWaterViscosity()
			//{    //华氏度(℉)=32+摄氏度(℃)×1.8
			//	WaterViscosity=109.5*pow(32+Tm*1.8,-1.122);  //这里的单位为厘泊cP,1厘泊(1cP)=1毫帕斯卡.秒 (1mPa.s)
			//	WaterViscosity/=1000.; //最终转化为Pa.s
			//}
		
			void GetMatrixThicknessInTheEnd()
			{ 
				//在虚层被剥蚀的时刻以及在模拟结束时刻分别计算在本次循环中根据本次循环得到的孔隙度求下一循环应该使用的骨架厚度
				//并计算两次迭代孔隙度的差值的绝对值
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
			{  //获得TTI值
				TTI=TTIF(StrSegLeft->Tm,BeginAge ,Tm,EndAge,StrSegLeft->Tmax,StrSegLeft->TTI);
			}
		
			void GetTTI()
			{  //获得最顶部地层段的TTI
				TTI=TTIF(SurfaceT,BeginAge ,Tm,EndAge,SurfaceT,TTI0);
			}

			double TTIF(double TLast, double tLast, double T, double t,double LastTMax,double TTILast)
			{
				//TTI计算函数
				// 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				//Tmax 纪录的是这一地层点将经历的最大温度，当地层温度小于TMax时不进行TTI计算，TTI保持原值，只有当地层温度大于TMax时才计算TTI值，并将这时的地层温度赋值给TMax
				//TTILast是上一步的TTI值
				double TTI;
				if(T<=LastTMax) TTI=TTILast; //如果现在的温度小于等于上一步所记录的TMax，则TTI就等于上一步的TTI值
				else
				{
				TTI=TTILast;  
				double a,b; // 线性变化的系数
				a=(T-TLast)/(t-tLast);b=T-a*t;
				//对于tLast和t之间采用数值积分方法，将期间等分为N个等分，因此Δt=(t-tLast)/N
				int N=int(fabs(T-TLast)/2.0+1); //这样计算是保证在每个计算步下温度变化不超过2℃，后面加1是保证至少有1步来执行。
				double Delta_t=(t-tLast)/double(N);  //Delta_t在这里是有正负概念的
				double tt1=tLast,tt2,ttM; // 分别是时间段的下端点值、上端点值和中间值,初始的tt1值设在最底端
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
				aParaOfEasyRo=new ParaOfEasyRo;  //先开出结构空间
				aParaOfEasyRo->CopyFrom(StrSegLeft->aParaOfEasyRo); //将左侧地层段的EasyRo参数赋值给本地层段的EasyRo参数结构体
				Ro[RO_Easy]=EasyRo(StrSegLeft->Tm,BeginAge, Tm, EndAge,aParaOfEasyRo->NN,aParaOfEasyRo->f,aParaOfEasyRo->E,aParaOfEasyRo->A,aParaOfEasyRo->Roo,aParaOfEasyRo->f0 );
			}
			
			void GetRoFromEasyRo()
			{   //用于第一个地层段的Ro计算
				Ro[RO_Easy]=EasyRo(SurfaceT,BeginAge ,Tm,EndAge,aParaOfEasyRo->NN,aParaOfEasyRo->f,aParaOfEasyRo->E,aParaOfEasyRo->A,aParaOfEasyRo->Roo,aParaOfEasyRo->f0 );
			}
			
			void GetRoFromBasinRo(StrSeg *StrSegLeft)
			{
				aParaOfBasinRo=new ParaOfEasyRo;  //先开出结构空间
				aParaOfBasinRo->CopyFrom(StrSegLeft->aParaOfBasinRo); //将左侧地层段的EasyRo参数赋值给本地层段的EasyRo参数结构体
				Ro[RO_Basin]=EasyRo(StrSegLeft->Tm,BeginAge, Tm, EndAge,aParaOfBasinRo->NN,aParaOfBasinRo->f,aParaOfBasinRo->E,aParaOfBasinRo->A,aParaOfBasinRo->Roo,aParaOfBasinRo->f0 );
			}
			
			void GetRoFromBasinRo()
			{ //用于第一个地层段的Ro计算
				Ro[RO_Basin]=EasyRo(SurfaceT,BeginAge ,Tm,EndAge,aParaOfBasinRo->NN,aParaOfBasinRo->f,aParaOfBasinRo->E,aParaOfBasinRo->A,aParaOfBasinRo->Roo,aParaOfBasinRo->f0 );
			}
			
			void GetRoFromSimpleRo(StrSeg *StrSegLeft)
			{
				aParaOfSimpleRo=new ParaOfSimpleRo;
				aParaOfSimpleRo->CopyFrom(StrSegLeft->aParaOfSimpleRo);
				Ro[RO_Simple]=SimpleRo(StrSegLeft->Tm,BeginAge, Tm, EndAge,aParaOfSimpleRo->f,aParaOfSimpleRo->aerf,aParaOfSimpleRo->beita,aParaOfSimpleRo->A,aParaOfSimpleRo->Roo, aParaOfSimpleRo->f0);
			}
			
			void GetRoFromSimpleRo()
			{   //用于第一个地层段的Ro计算
				Ro[RO_Simple]=SimpleRo(SurfaceT,BeginAge ,Tm,EndAge,aParaOfSimpleRo->f,aParaOfSimpleRo->aerf,aParaOfSimpleRo->beita,aParaOfSimpleRo->A,aParaOfSimpleRo->Roo, aParaOfSimpleRo->f0);
			}

			double EasyRo(double TLast, double tLast, double T, double t,int NN,double *f,double *E,double A,double Roo,double f0 )
			{
				// EASY%Ro计算函数，也用于BasinRo和相似的用户自定义参数Ro模型计算.函数返回值为Ro%
				// 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				//NN是平行反应活化能数
				//f 是化学计量系数（Stoichiometric Factor）
				//E是活化能（Activation Energy）（Kcal/mole）
				//A是频率因子 S^-1
				//Roo是在地表初始时刻的镜质体Ro值;
				//f0是初始化学计量系数之和
				//公式原理来源于Sweeney and Burnham,1990
				double *wiBIw0i;  //wi/w0i
				wiBIw0i=new double[NN];
				TLast+=273;T+=273;   //转化为开氏温度
				tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				t=t*1000000*365*24*3600; //百万年转化为秒
				double Ro;//计算的镜质体反射率值
				double F=0;//正文公式（1）和附件公式（6）中的值，指的是反应物的转化比例
				double wBIw0=0;//附件公式（6）中的w/w0
				double R=0.001986;//气体常数 ，单位 Kcal/(mol*K)
				//假设在t和tLast间温度T与t呈线性关系，即在T和TLast间线性变化：T=a*tt+b   ,tt是在t和tLast间变化的时间
				double a,b; // 线性变化的系数
				a=(T-TLast)/(t-tLast);b=T-a*t;
				//对于tLast和t之间采用数值积分方法，将期间等分为N个等分，因此Δt=(t-tLast)/N
				int N=int(fabs(T-TLast)/0.5+1); //这样计算是保证在每个计算步下温度变化不超过0.5℃，后面加1是保证至少有1步来执行。
				double Delta_t=(t-tLast)/double(N); //Delta_t在这里是有正负概念的
				double tt1=tLast,tt2,ttM; // 分别是时间段的下端点值、上端点值和中间值,初始的tt1值设在最底端
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
				tt1=tLast; // 算下一个对应的活化能的wiBIw0i[i]需要将初始时间重置
				temp=0;    //temp重新归零
				}

				//release
				delete wiBIw0i;

				F=f0-wBIw0;  //f0为文献中化学计量系数总和，wBIw0为化学计量系数剩余值
				Ro=Roo*exp(3.7*F);
				return Ro;
			}

			double SimpleRo(double TLast, double tLast, double T, double t,double &f,double aerf,double beita,double A,double Roo, double f0)
			{
				//Simple%Ro计算函数，也用于相似的用户自定义参数Ro模型计算.函数返回值为Ro%
				// 需要在函数中输入上一步的温度TLast(℃)和上一步的时间tLast（单位：Ma）,这一步的温度T(℃)和这一步的时间t（单位：Ma）
				//f 是化学计量系数（Stoichiometric Factor），是单值，在函数中会被改变
				//aerf, beita是Simple Ro方法中活化能E和lnRo间的关系常数  (E=αlnRo+β) ，E的单位是Kcal/mol
				//A是频率因子 S^-1
				//Roo是在地表初始时刻的镜质体Ro值;
				//f0是初始化学计量系数,为单值
				//公式原理来源于Suzuki et al.,1993
				double Ro;
				double F=f0-f;  //F指的是反应物的转化比例,即初始的化学计量系数减去反应后的化学计量系数
				Ro=Roo*exp(3.7*F); //计算的镜质体反射率值。这里先利用上一步的f值获得这一步计算活化能E的Ro值
				TLast+=273;T+=273;   //转化为开氏温度
				tLast=tLast*1000000*365*24*3600;  //百万年转化为秒
				t=t*1000000*365*24*3600; //百万年转化为秒
				double wBIw0;//附件公式（6）中的w/w0
				double R=0.001986;//气体常数 ，单位 Kcal/(mol*K)
				double E; //活化能（Activation Energy）（Kcal/mole）
				E=aerf*log(Ro)+beita; //Simple Ro中E和Ro的关系
				double a,b; // 线性变化的系数
				a=(T-TLast)/(t-tLast);b=T-a*t;
				//对于tLast和t之间采用数值积分方法，将期间等分为N个等分，因此Δt=(t-tLast)/N
				int N=int(fabs(T-TLast)/0.5+1); //这样计算是保证在每个计算步下温度变化不超过0.5℃，后面加1是保证至少有1步来执行。
				double Delta_t=(t-tLast)/double(N);  //Delta_t在这里是有正负概念的
				double tt1=tLast,tt2,ttM; // 分别是时间段的下端点值、上端点值和中间值,初始的tt1值设在最底端
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					wBIw0=exp((-A*exp(-E/R/(a*ttM+b)))*fabs(Delta_t));
					f=f*wBIw0;
					F=f0-f;  //f0为文献中化学计量系数总和，f为化学计量系数剩余值
					Ro=Roo*exp(3.7*F);
					E=aerf*log(Ro)+beita;
					tt1=tt2;
				}
				return Ro;
			}

		};  //struct  StrSeg结束

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