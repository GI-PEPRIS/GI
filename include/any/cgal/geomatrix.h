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
#ifndef __ANYCGAL_GEOFRACTURE_MATRIX_H__
#define __ANYCGAL_GEOFRACTURE_MATRIX_H__

// macro
#include "anycgal.h"

namespace AnyCGAL
{
	/*!
	* Matrix.cs
	**/
	class ANYCGAL_CLASS CGeoMatrix
	{
	public:
		//基本构造函数
		CGeoMatrix(); 

		//指定值构造函数
		//@param nRows--指定的矩阵行数
		//@param nCols--指定的矩阵列数
		//@param value--一维数组,长度为nRows*nCols,存储矩阵各元素的值
		CGeoMatrix(int nRows, int nCols, double *elements);

		//拷贝构造函数
		//@param other--源矩阵
		CGeoMatrix(CGeoMatrix &other);

		~CGeoMatrix();

		//
		const CGeoMatrix &operator=(CGeoMatrix &other); 
			 
		//初始化函数
		//@param nRows--指定的矩阵行数
		//@param nCols--指定的矩阵列数
		//@return bool,成功返回true,否则返回false
		bool Init(int nRows, int nCols);

		//获取矩阵的列数
		//@return int型,矩阵的列数
		int GetNumColumns();
		
		//获取矩阵的行数
		//@return int型,矩阵的行数
		int GetNumRows();

		//获取矩阵的数据
		//@return double型数组,指向矩阵各元素的数据缓冲区
		double *GetData(int &number);

		//设置矩阵各元素的值
		//@param value--一维数组,长度numColumns*numRows,存储矩阵各元素的值
		void SetData(double *elements);

		//给矩阵赋值
		//@param other--用于给矩阵赋值的源矩阵
		//@return Matrix型,矩阵与other相等
		const CGeoMatrix &SetValue(CGeoMatrix &other);

		//一般实矩阵的QR分解,分解成功后,原矩阵将成为R矩阵
		//@param mtxQ---返回分解后的Q矩阵
		//@return bool型,求解是否成功
		bool SplitQR(CGeoMatrix &mtxQ);

	private:
		//free memory
		void Release(bool isInit = false);

	private:
		int m_numColumns;//矩阵列数
		int m_numRows;//矩阵行数
		double m_eps;//缺省精度
		double *m_elements;//矩阵数据缓冲区
	};
}
#endif