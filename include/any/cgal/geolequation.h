 /* The AnyCGAL of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYCGAL_GEOFRACTURE_LINEAR_EQUATION_H__
#define __ANYCGAL_GEOFRACTURE_LINEAR_EQUATION_H__

// macro
#include "anycgal.h"

namespace AnyCGAL
{
	//forward
	class CGeoMatrix;

	/*!
	* LEquations.cs
	**/
	class ANYCGAL_CLASS CGeoLEquation
	{
	public:
		/**
		* 基本构造函数
		*/
		CGeoLEquation();

		/**
        * 指定系数和常数构造函数
        * 
        * @param mtxCoef - 指定的系数矩阵
        * @param mtxConst - 指定的常数矩阵
        */
		CGeoLEquation(CGeoMatrix *mtxCoef, CGeoMatrix *mtxConst);
		~CGeoLEquation();
	
		/**
		* 初始化函数
		* 
		* @param mtxCoef - 指定的系数矩阵
		* @param mtxConst - 指定的常数矩阵
		* @return bool 型，初始化是否成功
		*/
        bool Init(CGeoMatrix *mtxCoef, CGeoMatrix *mtxConst);

		/**
        * 获取系数矩阵
        * 
        * @return Matrix 型，返回系数矩阵
        */
		CGeoMatrix *GetCoefMatrix();
		
		/**
        * 获取未知数个数
        * 
        * @return int 型，返回方程组未知数的个数
        */
        int GetNumUnknowns();

		 /**
        * 全选主元高斯消去法
        * 
        * @param mtxResult - Matrix对象，返回方程组的解
        * @return bool 型，方程组求解是否成功
        */
        bool GetRootsetGauss(CGeoMatrix *mtxResult);

		/**
		* 求解线性最小二乘问题的豪斯荷尔德变换法
		* 
		* @param mtxResult - Matrix对象，返回方程组解矩阵
		* @param mtxQ - Matrix对象，返回豪斯荷尔德变换的Q矩阵
		* @param mtxR - Matrix对象，返回豪斯荷尔德变换的R矩阵
		* @return bool 型，方程组求解是否成功
		*/
        bool GetRootsetMqr(CGeoMatrix *mtxResult, CGeoMatrix *mtxQ, CGeoMatrix *mtxR);

	private:
		CGeoMatrix *m_mtxLECoef;		// 系数矩阵
		CGeoMatrix *m_mtxLEConst;		// 常数矩阵
	};
}
#endif
