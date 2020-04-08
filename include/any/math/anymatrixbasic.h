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
#ifndef __ANYMATH_MATRIX_BASIC_H__
#define __ANYMATH_MATRIX_BASIC_H__

// refer to macro
#include "anymath.h"
#include "any/base/anystl.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyMatrixBasic
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyMatrixBasic();
		~CAnyMatrixBasic();

		/*!
		*
		**/
		struct MatrixThreadParameter
		{
			// 
			int m_row_from;
			int m_row_to;
			int m_col_from;
			int m_col_to;

			//
			double **m_left_matrix;			
			double **m_right_matrix;
			double **m_rt_matrix;

			//
			double *m_right_vector;
			double *m_left_vector;
			double *m_rt_vector;

			//
			int m_row_number;
			int m_col_number;
			int m_rt_number;

			//
			MatrixThreadParameter() : m_row_from(0), m_row_to(0), \
				m_left_matrix(0), m_right_matrix(0), m_rt_matrix(0), \
				m_left_vector(0), m_right_vector(0), m_rt_vector(0), \
				m_row_number(0), m_col_number(0), m_rt_number(0)
			{

			};
		};

	public:
		/*!
		*
		**/
		static int CalcInversionMatrix(double **rhs, double **m, int stRank);
		static int CalcInversionMatrix_CLAPACK(double **rhs, double **m, int stRank);
		int CalcInversionMatrix_Threaded(double **rhs, double **R, int stRank);
		void InversionMatrixThreadFunc(MatrixThreadParameter &parameter);

		/*!
		*
		**/
		static void CalcTransformMatrix(double **rhs, int nRow, int nCol,double **m);
		void CalcTransformMatrix_Threaded(double **rhs, int nRow, int nCol,double **m);
		void TransformThreadFunc(MatrixThreadParameter &parameter);

		/*!
		*
		**/
		static void CalcProductMatrix(double **rhs, double **m, int nRow, int nR, int nCol, double **R);
		void CalcProductMatrix_Threaded(double **rhs, double **m, int nRow, int nR, int nCol, double **R);
		void ProductMatrixThreadFunc(MatrixThreadParameter &parameter);

		/*!
		*
		**/
		static void CalcProductMatrixVector(double **rhs, double *m, int nRow, int nCol, double *R);
		void CalcProductMatrixVector_Threaded(double **rhs, double *m, int nRow, int nCol, double *R);
		void ProductMatrixRightVectorThreadFunc(MatrixThreadParameter &parameter);

		static void CalcProductMatrixVector(double *m, double **rhs, int nRow, int nCol, double *R);
		void CalcProductMatrixVector_Threaded(double *m, double **rhs, int nRow, int nCol, double *R);
		void ProductMatrixLeftVectorThreadFunc(MatrixThreadParameter &parameter);

		/*!
		* Cholesky to get upper or lower triangular matrix
		* -2 means fail, +2 means success
		**/
		static int GetCholeskyTriangularMatrix(double *a, int number, double &det);
		static void CalcProductMatrix(double *a, double *b, int m, int n, int k, double *c);
		static int CalcCharacteristicMatrixAndValue(double **a, int m, double **CharacteristicMatrix, double *CharacteristicValue);

		//
		//
		//
		static void CalcProductMatrixCUDA(double **rhs, double **m, int nRow, int nR, int nCol, double **R);
		static int CalcInversionMatrixCUDA(double **rhs, double **m, int stRank);
		static int CalcInversionMatrixCUDA(std::vector<double**> &rhs, std::vector<double**> &m, int stRank);

	private:
		void MatrixProduct_MultiThead_Yan(double **rhs, double **m, int nRow, int nR, int nCol, double **R);

	private:
		int m_taskcount;
		void *m_scheduler;
	};
}

#endif
