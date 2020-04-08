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
		* 实验变差网格计算
		**/
		//n观测点数据个数
		//x, y是观测数据的三维点坐标值
		//v是对应于各点上的观测值
		//x, y, v都是具有n个元素的一维数组
		//dirP: 方向点坐标（2个元素的一维素组，分别代表X、Y），向量O→dirP代表计算变差时的方向(其中O代表坐标原点)；
		//      且方向点dirP≠(0,0)
		//H0:  2个元素的一维素组，顺序表示在x、y三个方向上计算变差时的步长（或称间隔）（相当于lag）dx、dy、dz,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy
		//nH:  2个元素的一维素组，顺序表示在x、y两个方向上计算变差时的步长（或称间隔）（相当于lag）变差计算时的最大步长倍数
		//HTolerate: 计算协方差/变差时间隔值所允许的误差；
		//dirTolerate: 计算协方差/变差时方向所允许的误差，单位为℃；
		//C: 是ExperimentalVariogram_3D结构的nH[0])*nH[1]二维数组，保存并返回各节点的变差值
		//    注1：C数组的两个下标分别表示计算协方差时x、y两个方向上的步长，也代表变差网格体节点的位置，它们的关系是:
		//        C[i][j]表示x、y的是在x、y两个方向的步长值分别为(i+1)*H[0]、(j+1)*H[1]时的变差值及其点对个数
		//    注2: C[0][0]的值是样本的方差
		void Get2DExperimentalVariogramAnisotropic(double *x, double *y, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure **C);
		void Get2DExperimentalVariogramAnisotropic_Thread(int StartGridX, int StartGridY, int EndGridX, int EndGridY, double *x, double *y, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure **C);
		//n观测点数据个数
		//x, y是观测数据的三维点坐标值
		//v是对应于各点上的观测值
		//x, y, v都是具有n个元素的一维数组
		//H0:  2个元素的一维素组，顺序表示在x、y二个方向上计算变差时的步长（或称间隔）（相当于lag）dx、dy、dz,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy
		//nH:  2个元素的一维素组，顺序表示在x、y二个方向上计算变差时的步长（或称间隔）（相当于lag）变差计算时的最大步长倍数
		//HTolerate: 计算协方差/变差时间隔值所允许的误差；
		//C: 是ExperimentalVariogram_struct结构的nH[0])*nH[1]二维数组，保存并返回各节点的变差值
		//    注1：C数组的三个下标分别表示计算协方差时x、y二个方向上的步长，也代表变差网格体节点的位置，它们的关系是:
		//        C[i][j]表示x、y的是在x、y二个方向的步长值分别为(i+1)*H[0]、(j+1)*H[1]时的变差值及其点对个数
		//    注2: C[0][0]的值是样本的方差
		void Get2DExperimentalVariogramIsotropic(double *x, double *y, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure **C);
		void Get2DExperimentalVariogramIsotropic_Thread(int StartGridX, int StartGridY, int EndGridX, int EndGridY, double *x, double *y, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure **C);

		//n观测点数据个数
		//x, y, z是观测数据的三维点坐标值
		//v是对应于各点上的观测值
		//x, y, z，v都是具有n个元素的一维数组
		//H0:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算变差时的步长（或称间隔）（相当于lag）dx、dy、dz,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy*dz
		//nH:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算变差时的步长（或称间隔）（相当于lag）变差计算时的最大步长倍数
		//HTolerate: 计算协方差/变差时间隔值所允许的误差；
		//C: 是ExperimentalVariogram_3D结构的nH[0])*nH[1]*nH[2]三维数组，保存并返回各节点的变差值
		//    注1：C数组的三个下标分别表示计算协方差时x、y、z三个方向上的步长，也代表变差网格体节点的位置，它们的关系是:
		//        C[i][j][k]表示x、y、z的是在x、y、z三个方向的步长值分别为(i+1)*H[0]、(j+1)*H[1]、(k+1)*H[2]时的变差值及其点对个数
		//    注2: C[0][0][0]的值是样本的方差
		void Get3DExperimentalVariogramIsotropic(double *x, double *y, double *z, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure ***C);
		void Get3DExperimentalVariogramIsotropic_Thread(int StartGridX, int StartGridY, int StartGridZ, int EndGridX, int EndGridY, int EndGridZ, double *x, double *y, double *z, double *v, int n, double *H0, int *nH, double HTolerate, ExperimentalVariogram_Structure ***C);

		//n观测点数据个数
		//x, y, z是观测数据的三维点坐标值
		//v是对应于各点上的观测值
		//x, y, z，v都是具有n个元素的一维数组
		//dirP: 方向点坐标（3个元素的一维素组，分别代表X、Y、Z），向量O→dirP代表计算变差时的方向(其中O代表坐标原点)；
		//      且方向点dirP≠(0,0,0)
		//H0:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算变差时的步长（或称间隔）（相当于lag）dx、dy、dz,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy*dz
		//nH:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算变差时的步长（或称间隔）（相当于lag）变差计算时的最大步长倍数
		//HTolerate: 计算协方差/变差时间隔值所允许的误差；
		//dirTolerate: 计算协方差/变差时方向所允许的误差，单位为℃；
		//C: 是ExperimentalVariogram_3D结构的nH[0])*nH[1]*nH[2]三维数组，保存并返回各节点的变差值
		//    注1：C数组的三个下标分别表示计算协方差时x、y、z三个方向上的步长，也代表变差网格体节点的位置，它们的关系是:
		//        C[i][j][k]表示x、y、z的是在x、y、z三个方向的步长值分别为(i+1)*H[0]、(j+1)*H[1]、(k+1)*H[2]时的变差值及其点对个数
		//    注2: C[0][0][0]的值是样本的方差
		void Get3DExperimentalVariogramAnisotropic(double *x, double *y, double *z, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure ***C);
		void Get3DExperimentalVariogramAnisotropic_Thread(int StartGridX, int StartGridY, int StartGridZ, int EndGridX, int EndGridY, int EndGridZ, double *x, double *y, double *z, double *v, int n, double *dirP, double *H0, int *nH, double HTolerate, double dirTolerate, ExperimentalVariogram_Structure ***C);

		//H0:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算变差时的步长（或称间隔）（相当于lag）dx、dy、dz,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy*dz
		//nH:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算变差时的步长（或称间隔）（相当于lag）变差计算时的最大步长倍数
		//C: 变差值,是ExperimentalVariogram_3D结构的nH[0])*nH[1]*nH[2]三维数组
		//X,Y: 变差作图数据，X,Y为一维数组，数组元素个数=nH[0])*nH[1]*nH[2]
		void Get3DGridToXY(double *H0, int *nH, ExperimentalVariogram_Structure ***C, double *X, double *Y);
		void Get3DGridToXY(double *H0, int *nH, double ***C, double *X, double *Y);
		//H0:  2个元素的一维素组，顺序表示在x、y两个方向上计算变差时的步长（或称间隔）（相当于lag）dx、dy,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy
		//nH:  2个元素的一维素组，顺序表示在x、y两个方向上计算变差时的步长（或称间隔）（相当于lag）变差计算时的最大步长倍数
		//C: 变差值,是ExperimentalVariogram_3D结构的nH[0])*nH[1]二维数组
		//X,Y: 变差作图数据，X,Y为一维数组，数组元素个数=nH[0])*nH[1]
		void Get2DGridToXY(double *H0, int *nH, ExperimentalVariogram_Structure **C, double *X, double *Y);
		void GetRandomDirection(std::vector<CGeoPoint<double> > &directions, int number);

		/*!
		* 网格进行性插值及光滑化处理
		**/
		//C: 是ExperimentalVariogram_3D结构的nH[0])*nH[1]*nH[2]三维数组，三维网格的（实验）协方差值
		//    注：C数组的三个下标分别表示计算协方差时x、y、z三个方向上的步长，也代表协方差网格体节点的位置，它们的关系是:
		//        C[i][j][k]表示在x、y、z三个方向的步长值分别为(i+1)*H0[0]、(j+1)*H0[1]、(k+1)*H0[2]时的协方差值及其点对个数
		//nH: 3个元素的一维素组，顺序表示在x、y、z三个方向上计算协方差/变差时步长（或称间隔, 相当于lag）的最大倍数
		//H0:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算协方差/变差时的步长（或称间隔, 相当于lag）dx、dy、dz,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy*dz
		//dirP: 方向点坐标（3个元素的一维素组，分别代表X、Y、Z），向量O→dirP代表计算协方差/变差时C的方向(其中O代表坐标原点), 且方向点dirP≠(0,0,0);
		//IR, IA: 进行插值及光滑化计算的（圆锥体）范围定义参数: IR=搜索半径的（圆锥体的母线长度），IA=圆锥体的圆心角(单位为℃,0<IA<90)
		//注: IR应当大于sqrt(H0[0]*H0[0]+H0[1]*H0[1]+H0[2]*H0[2])的值，否则就会造成因搜索区域过小而无法进行插值及光滑化计算
		void Get3DCovarianceGridInterpolation_Anisotropic(ExperimentalVariogram_Structure ***C, int *nH, double *H0, double *dirP, double IR, double IA);
		void Get3DCovarianceGridInterpolation_Isotropic(ExperimentalVariogram_Structure ***C, int *nH, double *H0, double IR);

		//ECV: 是ExperimentalVariogram_3D结构的nH[0])*nH[1]*nH[2]三维数组，三维网格的（实验）变差值
		//    注：C数组的三个下标分别表示计算协方差时x、y、z三个方向上的步长，也代表协方差网格体节点的位置，它们的关系是:
		//        C[i][j][k]表示x、y、z的是在x、y、z三个方向的步长值分别为(i+1)*H[0]、(j+1)*H[1]、(k+1)*H[2]时的协方差值及其点对个数
		//H0:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算实验变差时的步长（或称间隔）（相当于lag）dx、dy、dz,
		//      也就是说，协方差网格的单元（cell）的大小（体积）为dx*dy*dz
		//nH:  3个元素的一维素组，顺序表示在x、y、z三个方向上计算变差时步长（或称间隔）（相当于lag）的最大步长倍数
		//a: 球状模型变程
		//C0: 球状模型块金常数
		//C: 球状模型拱高
		//   C0+C为基台值
		bool Get3DCovarianceGridInterpolation_Direct(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double &a, double &C0, double &C);
		//a: 球状模型变程
		//C0: 球状模型块金常数
		//C: 球状模型拱高
		bool Get3DCovarianceGridInterpolation_Polynomial(ExperimentalVariogram_Structure ***ECV, int *nH, double *H0, double &a, double &C0, double &C);
		//用球状模型计算变差网格
		//ECV:用于保存网格计算结果
		//nH：3个方向上的网格个数
		//H0: 3个方向上的网格步长
		//a: 球状模型变程
		//C0: 球状模型块金常数
		//C: 球状模型拱高
		//   C0+C为基台值
		//dhx,dhy,dhz: 各向异性时的三个方向步长的比例因子，当为各向同性时, dhx=dhy=dhz=1
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