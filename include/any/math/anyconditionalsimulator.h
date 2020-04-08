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
#ifndef __ANYMATH_CONDITIONAL_SIMULATOR_H__
#define __ANYMATH_CONDITIONAL_SIMULATOR_H__

// refer to macro
#include "anymath.h"

// temp
#include "yanqi\ExperimentalVariogram_BaiscHead.h"

//
#include "any/base/anygeom.h"
#include<complex>
using namespace AnyBase;

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyConditionalSimulator
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyConditionalSimulator();
		~CAnyConditionalSimulator();

	public:
		//
		//
		//
		void Init3DExperimentalVariogramParameter(double *x, double *y, double *z, int n, int *nH, double *H0, double &HTolerate);
		void Init3DExperimentalVariogramParameter(double *x, double *y, double *z, int n, int *nH, double *H0);

		/*!
		* ʵ�����������
		**/
		//n�۲�����ݸ���
		//x, y�ǹ۲����ݵ���ά������ֵ
		//v�Ƕ�Ӧ�ڸ����ϵĹ۲�ֵ
		//x, y, v���Ǿ���n��Ԫ�ص�һά����
		//dirP: ��������꣨2��Ԫ�ص�һά���飬�ֱ����X��Y��������O��dirP���������ʱ�ķ���(����O��������ԭ��)��
		//      �ҷ����dirP��(0,0)
		//H0:  2��Ԫ�ص�һά���飬˳���ʾ��x��y���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��dx��dy��dz,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy
		//nH:  2��Ԫ�ص�һά���飬˳���ʾ��x��y���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��������ʱ����󲽳�����
		//HTolerate: ����Э����/���ʱ���ֵ���������
		//dirTolerate: ����Э����/���ʱ���������������λΪ�棻
		//C: ��ExperimentalVariogram_3D�ṹ��nH[0])*nH[1]��ά���飬���沢���ظ��ڵ�ı��ֵ
		//    ע1��C����������±�ֱ��ʾ����Э����ʱx��y���������ϵĲ�����Ҳ������������ڵ��λ�ã����ǵĹ�ϵ��:
		//        C[i][j]��ʾx��y������x��y��������Ĳ���ֵ�ֱ�Ϊ(i+1)*H[0]��(j+1)*H[1]ʱ�ı��ֵ�����Ը���
		//    ע2: C[0][0]��ֵ�������ķ���
		void Get2DExperimentalVariogramAnisotropic(double *x, double *y, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure **C);
		void Get2DExperimentalVariogramAnisotropic_Thread(int StartGridX, int StartGridY, int EndGridX, int EndGridY, double *x, double *y, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure **C);
		//n�۲�����ݸ���
		//x, y�ǹ۲����ݵ���ά������ֵ
		//v�Ƕ�Ӧ�ڸ����ϵĹ۲�ֵ
		//x, y, v���Ǿ���n��Ԫ�ص�һά����
		//H0:  2��Ԫ�ص�һά���飬˳���ʾ��x��y���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��dx��dy��dz,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy
		//nH:  2��Ԫ�ص�һά���飬˳���ʾ��x��y���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��������ʱ����󲽳�����
		//HTolerate: ����Э����/���ʱ���ֵ���������
		//C: ��ExperimentalVariogram_struct�ṹ��nH[0])*nH[1]��ά���飬���沢���ظ��ڵ�ı��ֵ
		//    ע1��C����������±�ֱ��ʾ����Э����ʱx��y���������ϵĲ�����Ҳ������������ڵ��λ�ã����ǵĹ�ϵ��:
		//        C[i][j]��ʾx��y������x��y��������Ĳ���ֵ�ֱ�Ϊ(i+1)*H[0]��(j+1)*H[1]ʱ�ı��ֵ�����Ը���
		//    ע2: C[0][0]��ֵ�������ķ���
		void Get2DExperimentalVariogramIsotropic(double *x, double *y, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure **C);
		void Get2DExperimentalVariogramIsotropic_Thread(int StartGridX, int StartGridY, int EndGridX, int EndGridY, double *x, double *y, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure **C);

		//n�۲�����ݸ���
		//x, y, z�ǹ۲����ݵ���ά������ֵ
		//v�Ƕ�Ӧ�ڸ����ϵĹ۲�ֵ
		//x, y, z��v���Ǿ���n��Ԫ�ص�һά����
		//H0:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��dx��dy��dz,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy*dz
		//nH:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��������ʱ����󲽳�����
		//HTolerate: ����Э����/���ʱ���ֵ���������
		//C: ��ExperimentalVariogram_3D�ṹ��nH[0])*nH[1]*nH[2]��ά���飬���沢���ظ��ڵ�ı��ֵ
		//    ע1��C����������±�ֱ��ʾ����Э����ʱx��y��z���������ϵĲ�����Ҳ������������ڵ��λ�ã����ǵĹ�ϵ��:
		//        C[i][j][k]��ʾx��y��z������x��y��z��������Ĳ���ֵ�ֱ�Ϊ(i+1)*H[0]��(j+1)*H[1]��(k+1)*H[2]ʱ�ı��ֵ�����Ը���
		//    ע2: C[0][0][0]��ֵ�������ķ���
		void Get3DExperimentalVariogramIsotropic(double *x, double *y, double *z, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure ***C);
		void Get3DExperimentalVariogramIsotropic_Thread(int StartGridX, int StartGridY, int StartGridZ, int EndGridX, int EndGridY, int EndGridZ, double *x, double *y, double *z, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure ***C);

		//n�۲�����ݸ���
		//x, y, z�ǹ۲����ݵ���ά������ֵ
		//v�Ƕ�Ӧ�ڸ����ϵĹ۲�ֵ
		//x, y, z��v���Ǿ���n��Ԫ�ص�һά����
		//dirP: ��������꣨3��Ԫ�ص�һά���飬�ֱ����X��Y��Z��������O��dirP���������ʱ�ķ���(����O��������ԭ��)��
		//      �ҷ����dirP��(0,0,0)
		//H0:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��dx��dy��dz,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy*dz
		//nH:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��������ʱ����󲽳�����
		//HTolerate: ����Э����/���ʱ���ֵ���������
		//dirTolerate: ����Э����/���ʱ���������������λΪ�棻
		//C: ��ExperimentalVariogram_3D�ṹ��nH[0])*nH[1]*nH[2]��ά���飬���沢���ظ��ڵ�ı��ֵ
		//    ע1��C����������±�ֱ��ʾ����Э����ʱx��y��z���������ϵĲ�����Ҳ������������ڵ��λ�ã����ǵĹ�ϵ��:
		//        C[i][j][k]��ʾx��y��z������x��y��z��������Ĳ���ֵ�ֱ�Ϊ(i+1)*H[0]��(j+1)*H[1]��(k+1)*H[2]ʱ�ı��ֵ�����Ը���
		//    ע2: C[0][0][0]��ֵ�������ķ���
		void Get3DExperimentalVariogramAnisotropic(double *x, double *y, double *z, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure ***C);
		void Get3DExperimentalVariogramAnisotropic_Thread(int StartGridX, int StartGridY, int StartGridZ, int EndGridX, int EndGridY, int EndGridZ, double *x, double *y, double *z, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure ***C);

		//H0:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��dx��dy��dz,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy*dz
		//nH:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��������ʱ����󲽳�����
		//C: ���ֵ,��ExperimentalVariogram_3D�ṹ��nH[0])*nH[1]*nH[2]��ά����
		//X,Y: �����ͼ���ݣ�X,YΪһά���飬����Ԫ�ظ���=nH[0])*nH[1]*nH[2]
		void Get3DGridToXY(double *H0, int *nH, ExperimentalVariogram_Structure ***C, double *X, double *Y);
		void Get3DGridToXY(double *H0, int *nH, double ***C, double *X, double *Y);
		//H0:  2��Ԫ�ص�һά���飬˳���ʾ��x��y���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��dx��dy,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy
		//nH:  2��Ԫ�ص�һά���飬˳���ʾ��x��y���������ϼ�����ʱ�Ĳ�������Ƽ�������൱��lag��������ʱ����󲽳�����
		//C: ���ֵ,��ExperimentalVariogram_3D�ṹ��nH[0])*nH[1]��ά����
		//X,Y: �����ͼ���ݣ�X,YΪһά���飬����Ԫ�ظ���=nH[0])*nH[1]
		void Get2DGridToXY(double *H0, int *nH, ExperimentalVariogram_Structure **C, double *X, double *Y);
		void GetRandomDirection(std::vector<CGeoPoint<double> > &directions, int number);

		/*!
		* ��������Բ�ֵ���⻬������
		**/
		//C: ��ExperimentalVariogram_3D�ṹ��nH[0])*nH[1]*nH[2]��ά���飬��ά����ģ�ʵ�飩Э����ֵ
		//    ע��C����������±�ֱ��ʾ����Э����ʱx��y��z���������ϵĲ�����Ҳ����Э����������ڵ��λ�ã����ǵĹ�ϵ��:
		//        C[i][j][k]��ʾ��x��y��z��������Ĳ���ֵ�ֱ�Ϊ(i+1)*H0[0]��(j+1)*H0[1]��(k+1)*H0[2]ʱ��Э����ֵ�����Ը���
		//nH: 3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ���Э����/���ʱ��������Ƽ��, �൱��lag���������
		//H0:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ���Э����/���ʱ�Ĳ�������Ƽ��, �൱��lag��dx��dy��dz,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy*dz
		//dirP: ��������꣨3��Ԫ�ص�һά���飬�ֱ����X��Y��Z��������O��dirP�������Э����/���ʱC�ķ���(����O��������ԭ��), �ҷ����dirP��(0,0,0);
		//IR, IA: ���в�ֵ���⻬������ģ�Բ׶�壩��Χ�������: IR=�����뾶�ģ�Բ׶���ĸ�߳��ȣ���IA=Բ׶���Բ�Ľ�(��λΪ��,0<IA<90)
		//ע: IRӦ������sqrt(H0[0]*H0[0]+H0[1]*H0[1]+H0[2]*H0[2])��ֵ������ͻ���������������С���޷����в�ֵ���⻬������
		void Get3DCovarianceGridInterpolation_Anisotropic(ExperimentalVariogram_Structure ***C, int *nH, double *H0, double *dirP, double IR, double IA);
		void Get3DCovarianceGridInterpolation_Isotropic(ExperimentalVariogram_Structure ***C, int *nH, double *H0, double IR);

		//ECV: ��ExperimentalVariogram_3D�ṹ��nH[0])*nH[1]*nH[2]��ά���飬��ά����ģ�ʵ�飩���ֵ
		//    ע��C����������±�ֱ��ʾ����Э����ʱx��y��z���������ϵĲ�����Ҳ����Э����������ڵ��λ�ã����ǵĹ�ϵ��:
		//        C[i][j][k]��ʾx��y��z������x��y��z��������Ĳ���ֵ�ֱ�Ϊ(i+1)*H[0]��(j+1)*H[1]��(k+1)*H[2]ʱ��Э����ֵ�����Ը���
		//H0:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ���ʵ����ʱ�Ĳ�������Ƽ�������൱��lag��dx��dy��dz,
		//      Ҳ����˵��Э��������ĵ�Ԫ��cell���Ĵ�С�������Ϊdx*dy*dz
		//nH:  3��Ԫ�ص�һά���飬˳���ʾ��x��y��z���������ϼ�����ʱ��������Ƽ�������൱��lag������󲽳�����
		//a: ��״ģ�ͱ��
		//C0: ��״ģ�Ϳ����
		//C: ��״ģ�͹���
		//   C0+CΪ��ֵ̨
		bool Get3DCovarianceGridInterpolation_Direct(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double &a, double &C0, double &C);
		//a: ��״ģ�ͱ��
		//C0: ��״ģ�Ϳ����
		//C: ��״ģ�͹���
		bool Get3DCovarianceGridInterpolation_Polynomial(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double &a, double &C0, double &C);
		//����״ģ�ͼ���������
		//ECV:���ڱ������������
		//nH��3�������ϵ��������
		//H0: 3�������ϵ����񲽳�
		//a: ��״ģ�ͱ��
		//C0: ��״ģ�Ϳ����
		//C: ��״ģ�͹���
		//   C0+CΪ��ֵ̨
		//dhx,dhy,dhz: ��������ʱ���������򲽳��ı������ӣ���Ϊ����ͬ��ʱ, dhx=dhy=dhz=1
		void Get3DCovarianceGridInterpolation_Sphere(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double a, double C0, double C, double *dirP,bool isAnisotropic, bool iMode=true);

		//
		//
		//
		/*!
		*
		**/
		bool Get2DCovarianceGridInterpolation_Direct(ExperimentalVariogram_Structure **ECV, int *nH, double *H0, double &a, double &C0, double &C);
		bool Get2DCovarianceGridInterpolation_Polynomial(ExperimentalVariogram_Structure **ECV, int *nH, double *H0, double &a, double &C0, double &C);
		void Get2DCovarianceGridInterpolation_Sphere(ExperimentalVariogram_Structure **ECV, int *nH, double *H0, double a, double C0, double C, double *dirP, bool isAnisotropic, bool iMode=true);

		void Get2DCovarianceGridInterpolation_Anisotropic(ExperimentalVariogram_Structure **C, int *nH, double *H0, double *dirP, double IR, double IA);
		void Get2DCovarianceGridInterpolation_Isotropic(ExperimentalVariogram_Structure **C, int *nH, double *H0, double IR);

		//
		// simulation
		//
		int MakeConditionalSpectralSimulation_3D(double *Grid0, double *x, double *y, double *z, double *v, int n, double *H0, int *nH, ExperimentalVariogram_Structure ***C,complex<double> ***S,double ObjValue0, unsigned long int MaxIterationNum);
		int MakeConditionalSimulationIn3D(double *Grid0,double *x, double *y, double *z, double *v, int n,double *H0, int *nH, double ***C,complex<double> ***S, double ObjValue0, unsigned long int MaxIterationNum = 1000,int OpMode = 0);

		void MakeGridInterpolation_3D_InverseDistanceWeight(double *x, double *y, double *z, double *v, int nXYZ,double x0, double y0, double z0,double *H0,double ***Grid, int *nH,int InterpolationDots=10);
		void MakeGridInterpolation_3D_OrdinaryKriging_Isotropic(double *x, double *y, double *z, double *v, int nXYZ,double x0, double y0, double z0,double *H0,double ***Grid, int *nH, int InterpolationDots,double a, double C0, double C, int ModelType = 0);
		void MakeGridInterpolation_3D_OrdinaryKriging_AnsiIsotropic(double *x, double *y, double *z, double *v, int nXYZ,double x0, double y0, double z0,double *H0,double ***Grid, int *nH, int InterpolationDots,double a, double C0, double C,double *dirP, int ModelType = 0);
		int MakeDataFusion_ConditionalSimulationIn3D(double *Grid0,double *x, double *y, double *z, double *v, int n,double *H0, int *nH, double ***C,  double ***F,complex<double> ***S,double ObjValue0, unsigned long int MaxIterationNum);
		int MakeDataFusion_ConditionalSimulationIn3D(double *Grid0,double *H0, int *nH, double ***C, double ***F,complex<double> ***S);
		void GetGridInterpolation_3D_TheoryVariogram(double ***Grid, int *nH, double *H0, double a, double C0, double C, double *dirP,int ModelType, bool isAnisotropic);

		//
		void DoChangeGridcondition2Realcondition(double *Grid0, double *H0,int GridX, int GridY, int GridZ,double &x, double &y, double &z);
	};
}
#endif