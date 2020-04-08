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
		//�������캯��
		CGeoMatrix(); 

		//ָ��ֵ���캯��
		//@param nRows--ָ���ľ�������
		//@param nCols--ָ���ľ�������
		//@param value--һά����,����ΪnRows*nCols,�洢�����Ԫ�ص�ֵ
		CGeoMatrix(int nRows, int nCols, double *elements);

		//�������캯��
		//@param other--Դ����
		CGeoMatrix(CGeoMatrix &other);

		~CGeoMatrix();

		//
		const CGeoMatrix &operator=(CGeoMatrix &other); 
			 
		//��ʼ������
		//@param nRows--ָ���ľ�������
		//@param nCols--ָ���ľ�������
		//@return bool,�ɹ�����true,���򷵻�false
		bool Init(int nRows, int nCols);

		//��ȡ���������
		//@return int��,���������
		int GetNumColumns();
		
		//��ȡ���������
		//@return int��,���������
		int GetNumRows();

		//��ȡ���������
		//@return double������,ָ������Ԫ�ص����ݻ�����
		double *GetData(int &number);

		//���þ����Ԫ�ص�ֵ
		//@param value--һά����,����numColumns*numRows,�洢�����Ԫ�ص�ֵ
		void SetData(double *elements);

		//������ֵ
		//@param other--���ڸ�����ֵ��Դ����
		//@return Matrix��,������other���
		const CGeoMatrix &SetValue(CGeoMatrix &other);

		//һ��ʵ�����QR�ֽ�,�ֽ�ɹ���,ԭ���󽫳�ΪR����
		//@param mtxQ---���طֽ���Q����
		//@return bool��,����Ƿ�ɹ�
		bool SplitQR(CGeoMatrix &mtxQ);

	private:
		//free memory
		void Release(bool isInit = false);

	private:
		int m_numColumns;//��������
		int m_numRows;//��������
		double m_eps;//ȱʡ����
		double *m_elements;//�������ݻ�����
	};
}
#endif