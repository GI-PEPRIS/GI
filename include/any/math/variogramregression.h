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
#ifndef __ANYMATH_KRIG_VARIOGRAM_REGRESSION_H__
#define __ANYMATH_KRIG_VARIOGRAM_REGRESSION_H__

#include "anymath.h"

//
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

namespace AnyMath
{
	//����������ͣ��ֱ�����״��ָ������˹�����ԡ�Ƕ����״������Բ�Ρ��������ȶ�
	enum VariogramType{VM_SPHERICAL,VM_EXPONENTIAL,VM_GAUSSIAN,VM_LINEAR,/*VM_NESTEDSPHERICAL,*/VM_PENTASPHERICAL,VM_CIRCULAR,VM_CUBIC/*,VM_STABLE*/};
	static std::string VariogramName[] = {
		"Spherical",
		"Exponential",
		"Gaussian",
		"Linear",
		"Nested Spherical",
		"Penta Spherical",
		"Circular",
		"Cubic"/*,
		"Stable"*/
	};

	//
	class ANYMATH_CLASS CVariogramRegression
	{
		template <class T>
		int ReturnMaxFlag(T Array[],int n)  //����Array����Сֵ���±�ֵ
		{
		  T Temp=Array[0];
		  int k;
		  for(int i=0;i<n;i++)
			if(Temp<Array[i]) {Temp=Array[i]; k=i;}
		  return k;
		}
		template <class T>
		T ReturnMin(T Array[],int n)
		{
		  T Temp=Array[0];
		  for(int i=0;i<n;i++)
			if(Temp>Array[i]) {Temp=Array[i]; }
		  return Temp;
		}

		template <class T>
		T ReturnMax(T Array[],int n)
		{
		  T Temp=Array[0];
		  for(int i=0;i<n;i++)
			if(Temp<Array[i]) {Temp=Array[i]; }
		  return Temp;
		}

		static double PAI;//=3.14159265358979;
		struct DataGroup //����һ����ά����ṹ
		{
			int Row;    //������
			int Column; //������
			double **Data; //��������ָ��
			DataGroup(int i,int j):Row(i),Column(j)
				{
				Data=new double *[Row];
					for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				}
		};
		
		//---------------------------------------------------------------------------
		class Matrix     //����һ��������
		{
		  public:
			Matrix(DataGroup *DataGroupX):Row(DataGroupX->Row),Column(DataGroupX->Column)
			{   //����һDataGroup�ṹ��һ����ľ���ֵ
				Data=new double*[Row];
				for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
					Data[i][j]=DataGroupX->Data[i][j];
			}
			Matrix(int R):Row(R),Column(R)//����һ����λ����
			{
				Data=new double*[Row];
				for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
					{
						if(j==i) Data[i][j]=1;
						else Data[i][j]=0;
					}
			}
			Matrix(int R,int C):Row(R),Column(C)//����һ��ȷ��ά������
			{
				Data=new double*[Row];
				for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
						Data[i][j]=0;
			}
			Matrix():Row(1),Column(1)          //����һ��δ������
			{
				Data=new double*[Row];
				for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
					Data[i][j]=0;
			}
			Matrix(const Matrix &OrginMatrix)//���ƹ��캯��
			{
				Row=OrginMatrix.Row;
				Column=OrginMatrix.Column;
				Data=new double*[Row];
					for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
					Data[i][j]=OrginMatrix.Data[i][j];
			}
			Matrix(const Matrix &OrginMatrix,int n)
			{  //����OrginMatrix��ǰn��������
				Row=OrginMatrix.Row;
				if(n>OrginMatrix.Column) Column=OrginMatrix.Column;
				else Column=n;
				Data=new double*[Row];
				for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
					Data[i][j]=OrginMatrix.Data[i][j];
			}
			void Init(int R,int C)   // �����󿪱�ȷ���Ĵ洢�ռ�
			{
				for(int i=0;i<Row;i++)
					delete[] Data[i];
				delete[] Data;
				Row=R;Column=C;
				Data=new double*[Row];
				for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
			}
			Matrix& operator =(const Matrix &MatrixRight)//����ֵ������
			{
				if(this==&MatrixRight) return *this;
				for(int i=0;i<Row;i++)
					delete[] Data[i];
				delete[] Data;
				Row=MatrixRight.Row;
				Column=MatrixRight.Column;
				Data=new double*[Row];
					for(int i=0;i<Row;i++)
					Data[i]=new double[Column];
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
					Data[i][j]=MatrixRight.Data[i][j];
				return *this;
			}
			Matrix operator~(void) //����ת��
			{
				Matrix Result(Column,Row);
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
					Result.Data[i][j]=Data[j][i];
				return Result;
			}
			Matrix operator !(void) //����������������
			{
				Matrix Result(Row,Column);
				double Temp=0;
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
					{
						if(i>j) Result.Data[i][j]=0;
						if(i==j) Result.Data[i][j]=1.0/Data[i][j];
						Temp=0;
						if(i<j)
						{
							for(int k=i;k<j;k++) Temp=Temp+Result.Data[i][k]*Data[k][j];
							Result.Data[i][j]=-Temp/Data[j][j];
						}
					}
					return Result;
			}
			Matrix operator ++(void) //�����ⷽ��������
			{
				Matrix Result(Row,Column);
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
						Result.Data[i][j]=::powf(-1,i+j+2)*ChildMatrix(*this,j,i).Det();
				return Result/Det();
			}

			Matrix operator-(void) //�����󷴣���������������Ԫ�ر��
			{
				Matrix Result(Row,Column);
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
					Result.Data[i][j]=-Data[i][j];
				return Result;
			}
			Matrix operator+(const Matrix& M)//�ӷ�������
			{
				Matrix Result(Row,Column);
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
					Result.Data[i][j]=Data[i][j]+M.Data[i][j];
				return Result;
			}
			Matrix operator-(const Matrix& M)//����������
			{
				Matrix Result(Row,Column);
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
					Result.Data[i][j]=Data[i][j]-M.Data[i][j];
				return Result;
			}
			Matrix operator*(const Matrix& M)//�˷�������
			{
				Matrix Result(Row,M.Column);
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
					for(int k=0;k<Column;k++)
					Result.Data[i][j]=Result.Data[i][j]+Data[i][k]*M.Data[k][j];
				return Result;
			}
			Matrix operator/(double Coeff)
			{   //����������,�������һ��ʵ��
				Matrix Result(Row,Column);
				for(int i=0;i<Row;i++)
					for(int j=0;j<Column;j++)
					Result.Data[i][j]=Data[i][j]/Coeff;
				return Result;
			}

			//
			friend Matrix operator*(double Coeff,Matrix& M)//һ��ʵ����������
			{  //һ��ʵ����������
				Matrix Result(M.Row,M.Column);
				for(int i=0;i<Result.Row;i++)
					for(int j=0;j<Result.Column;j++)
						Result.Data[i][j]=Coeff*M.Data[i][j];
				return Result;
			}
			static Matrix eArray(int Row,int n) //Householder�е�e����
			{
				//Class Matrix����Ա����  //���˵�nλ����1��(n��0����)����������Ϊ0
				Matrix Array;                 //����Householder�任�е�e����
				Array.Row=Row;
				Array.Column=1;
				Array.Data=new double*[Row];
				for(int i=0;i<Array.Row;i++)
					Array.Data[i]=new double[Array.Column];
				for(int i=0;i<Array.Row;i++)
					for(int j=0;j<Array.Column;j++)
					{
						if(i==n) Array.Data[i][j]=1;
						else Array.Data[i][j]=0;
					}
					return Array;
			}
			static Matrix FilterArray(Matrix &ArrayX,int n)
			{
				//�������ڽ�������ArrayXǰn���滻Ϊ0: n=0ʱ���滻��
				//n=2ʱ�滻ǰ����,Ҳ�����ھ���
				Matrix Array;
				Array.Row=ArrayX.FRow();
				Array.Column=ArrayX.FColumn();
				Array.Data=new double*[Array.Row];
				for(int i=0;i<Array.Row;i++)
					Array.Data[i]=new double[Array.Column];
				for(int i=0;i<Array.Row;i++)
					for(int j=0;j<Array.Column;j++)
					{
						if(i<n) Array.Data[i][j]=0;
						else Array.Data[i][j]=ArrayX.Data[i][j];
					}
					return Array;
			}
			
			static Matrix CopyColumnArrays(Matrix &OrginMatrix,int StartColumn,int EndColumn)
			{
				// CopyColumnArrays()�������ڿ���һ�����д�StartColumn�е�EndColumn�е�����
				Matrix Result(OrginMatrix.Row,EndColumn-StartColumn+1);
				for(int i=0;i<Result.Row;i++)
					for(int j=StartColumn;j<=EndColumn;j++)
						Result.Data[i][j-StartColumn]=OrginMatrix.Data[i][j];
				return Result;
			}
			// CopyRowArrays()�������ڿ���һ�����д�StartRow�е�EndRow�е�����
			static Matrix CopyRowArrays(Matrix &OrginMatrix,int StartRow,int EndRow)
			{
				// CopyRowArrays()�������ڿ���һ�����д�StartRow�е�EndRow�е�����
				Matrix Result(EndRow-StartRow+1,OrginMatrix.Column);
				for(int i=StartRow;i<=EndRow;i++)
					for(int j=0;j<Result.Column;j++)
						Result.Data[i-StartRow][j]=OrginMatrix.Data[i][j];
				return Result;
			}
			static Matrix ChildMatrix(Matrix &X,int m,int n)
			{
				Matrix Child(X.FRow()-1,X.FColumn()-1);
				for(int i=0;i<X.FRow();i++)
					for(int j=0;j<X.FColumn();j++)
					{
						if(i<m&&j<n) Child.Data[i][j]=X.FData()[i][j];
						if(i<m&&j>n) Child.Data[i][j-1]=X.FData()[i][j];
						if(i>m&&j<n) Child.Data[i-1][j]=X.FData()[i][j];
						if(i>m&&j>n) Child.Data[i-1][j-1]=X.FData()[i][j];
					}
				return Child;
			}

			//
			int FRow(void){return Row;}  //���ؾ��������
			int FColumn(void){return Column;}  //���ؾ��������
			double** FData(void){return Data;}  //���ؾ������ݵĵ�ַ
			void InputData(int i,int j,double aNumber){Data[i][j]=aNumber;}  //�ھ�����ȷ��λ����������
			double OutputData(int i,int j){return Data[i][j];} //���ؾ�����ȷ�����е���ֵ
			double Det(void)   //��������ʽ
			{
				double D=0;
				if(FRow()!=FColumn()) { assert(false); return D;}
				if(FRow()==1) D=FData()[0][0];
				if(FRow()==2) D=FData()[0][0]*FData()[1][1]-FData()[0][1]*FData()[1][0];
				if(FRow()>2)
					for(int i=0;i<FRow();i++)  D+=::powf(-1,i)*FData()[i][0]*ChildMatrix(*this,i,0).Det();
				return D;
			}

			public:
				int Row,Column;
				double **Data;
			};		
	
	public:
		CVariogramRegression()
		{	
			m_c0 = 0.;
			m_c = 0.;
			m_r = 0.;
			m_aerf = 0.; //�ȶ�ģ�͵Ĳ���
			m_c1 = 0.;
			m_c2 = 0.;
			m_r1 = 0.;
			m_r2 = 0.;//Ƕ����״ģ�͵Ĳ���
			m_sill = 0.;   //���ͼ�еĻ�ֵ̨
			m_range= 0.;  //���
			m_nugget= 0.; //���ֵ
			m_kernelType = VM_SPHERICAL;

			m_is_fitted_normally;
		}
		~CVariogramRegression(){}

		friend class CAnyKrigSimulator;

	public:
		VariogramType Fit_Best_Consider_AllParameters(const std::vector<CGeoPoint<double> > &variances); //for the first time to call
		void Fit_NotConsiderNuddget(const std::vector<CGeoPoint<double> > &variances, VariogramType kernel_type);
		void Fit_ConsiderNuddget(const std::vector<CGeoPoint<double> > &variances, VariogramType kernel_type);
		double Fit_GetModelValue(short kernel_type, double h,double sill, double range, double nugget);

		void Fit_GetVariogramParameter(short &kernel_type, double &sill, double &range, double &nugget);
		void Fit_SetVariogramParameter(short kernel_type, double sill, double range, double nugget);

	private:
		double CalcuLengthOfArray(Matrix &xi);
		void QRDecompose(Matrix &X,Matrix &Q,Matrix &R);
		Matrix FSpherical(Matrix &X,Matrix &Theta);
		Matrix FSphericalDeri(Matrix &X,Matrix &Theta);
		Matrix FSphericalTheta(Matrix &X,Matrix &Y);
		Matrix FSpherical(Matrix &X,Matrix &Theta,double c0);
		Matrix FSphericalDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FSphericalTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FExponential(Matrix &X,Matrix &Theta);
		Matrix FExponentialDeri(Matrix &X,Matrix &Theta);
		Matrix FExponentialTheta(Matrix &X,Matrix &Y);
		Matrix FExponential(Matrix &X,Matrix &Theta,double c0);
		Matrix FExponentialDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FExponentialTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FGaussian(Matrix &X,Matrix &Theta);
		Matrix FGaussianDeri(Matrix &X,Matrix &Theta);
		Matrix FGaussianTheta(Matrix &X,Matrix &Y);
		Matrix FGaussian(Matrix &X,Matrix &Theta,double c0);
		Matrix FGaussianDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FGaussianTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FLinear(Matrix &X,Matrix &Theta);
		Matrix FLinearDeri(Matrix &X,Matrix &Theta);
		Matrix FLinearTheta(Matrix &X,Matrix &Y);
		Matrix FLinear(Matrix &X,Matrix &Theta,double c0);
		Matrix FLinearDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FLinearTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FNestedSpherical(Matrix &X,Matrix &Theta);
		Matrix FNestedSphericalDeri(Matrix &X,Matrix &Theta);
		Matrix FNestedSphericalTheta(Matrix &X,Matrix &Y);
		Matrix FNestedSpherical(Matrix &X,Matrix &Theta,double c0);
		Matrix FNestedSphericalDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FNestedSphericalTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FPentaSpherical(Matrix &X,Matrix &Theta);
		Matrix CVariogramRegression::FPentaSpherical(Matrix &X,Matrix &Theta,double c0);
		Matrix FPentaSphericalDeri(Matrix &X,Matrix &Theta);
		Matrix FPentaSphericalDeri(Matrix &X,Matrix &Theta,double c0);

		Matrix FPentaSphericalTheta(Matrix &X,Matrix &Y);
		Matrix FPentaSphericalTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FCircular(Matrix &X,Matrix &Theta);
		Matrix FCircularDeri(Matrix &X,Matrix &Theta);
		Matrix FCircularTheta(Matrix &X,Matrix &Y);
		Matrix FCircular(Matrix &X,Matrix &Theta,double c0);
		Matrix FCircularDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FCircularTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FCubic(Matrix &X,Matrix &Theta);
		Matrix FCubicDeri(Matrix &X,Matrix &Theta);
		Matrix FCubicTheta(Matrix &X,Matrix &Y);
		Matrix FCubic(Matrix &X,Matrix &Theta,double c0);
		Matrix FCubicDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FCubicTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FStable(Matrix &X,Matrix &Theta);
		Matrix FStableDeri(Matrix &X,Matrix &Theta);
		Matrix FStableTheta(Matrix &X,Matrix &Y);
		Matrix FStable(Matrix &X,Matrix &Theta,double c0);
		Matrix FStableDeri(Matrix &X,Matrix &Theta,double c0);
		Matrix FStableTheta(Matrix &X,Matrix &Y,double c0);
		Matrix FunctionOfNonlinerRegression(double *h,double *gamma,int NPair,VariogramType m_kernelType);
		Matrix FunctionOfNonlinerRegression(double *h,double *gamma,int NPair,double c0,VariogramType m_kernelType);
		
		int ReturnTheBestModel(double *h,double *gamma,int NPair,int STN,int *ST);
		int ReturnTheBestModelWithc0(double *h,double *gamma,int NPair,double c0,int STN,int *ST);
		double GetRangeExponential(double c0,double c,double r);
		double GetRangeGaussian(double c0,double c,double r);
		double GetRangeStable(double c0,double c,double r,double aerf);
		void GetNuggetSillRange(double c0,double c,double r,double aerf,double c1,double c2,double r1,double r2,VariogramType m_kernelType,double &nugget,double &sill,double &range);
		void GetParasFromNuggetSillRange(double &c0,double &c,double &r,double &aerf,double &c1,double &c2,double &r1,double &r2,VariogramType m_kernelType,double nugget,double sill,double range);
		double GetModelValue(double h,double c0,double c,double r,double aerf,double c1,double c2,double r1,double r2,VariogramType m_kernelType);

		double GetrExponential(double c0,double c,double range)
		{ //value=c0+c*(1-exp(-x/r));    value=0.95*(c0+c)����x
			double v=0.95*(c0+c);
			return -range/log(1.-(v-c0)/c);
		}
		double GetrGaussian(double c0,double c,double range)
		{ //value=c0+c*(1-exp(-x*x/r/r));    value=0.95*(c0+c)����x
			double v=0.95*(c0+c);
			return sqrt(-range*range/log(1.-(v-c0)/c));
		}
		double GetrStable(double c0,double c,double range,double aerf)
		{ //value=c0+c*(1.-exp(-pow(x,aerf)/pow(r,aerf)))   value=0.95*(c0+c)����x
			double v=0.95*(c0+c);
			return pow(-pow(range,aerf)/log(1.-(v-c0)/c),1./aerf);
		}

	protected:
		double m_c0,m_c,m_r;   //x����h
		double m_aerf; //�ȶ�ģ�͵Ĳ���
		double m_c1,m_c2,m_r1,m_r2;//Ƕ����״ģ�͵Ĳ���
		double m_sill;   //���ͼ�еĻ�ֵ̨
		double m_range;  //���
		double m_nugget; //���ֵ
		VariogramType m_kernelType;

		bool m_is_fitted_normally;
	};
}
#endif