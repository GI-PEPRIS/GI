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
		* �������캯��
		*/
		CGeoLEquation();

		/**
        * ָ��ϵ���ͳ������캯��
        * 
        * @param mtxCoef - ָ����ϵ������
        * @param mtxConst - ָ���ĳ�������
        */
		CGeoLEquation(CGeoMatrix *mtxCoef, CGeoMatrix *mtxConst);
		~CGeoLEquation();
	
		/**
		* ��ʼ������
		* 
		* @param mtxCoef - ָ����ϵ������
		* @param mtxConst - ָ���ĳ�������
		* @return bool �ͣ���ʼ���Ƿ�ɹ�
		*/
        bool Init(CGeoMatrix *mtxCoef, CGeoMatrix *mtxConst);

		/**
        * ��ȡϵ������
        * 
        * @return Matrix �ͣ�����ϵ������
        */
		CGeoMatrix *GetCoefMatrix();
		
		/**
        * ��ȡδ֪������
        * 
        * @return int �ͣ����ط�����δ֪���ĸ���
        */
        int GetNumUnknowns();

		 /**
        * ȫѡ��Ԫ��˹��ȥ��
        * 
        * @param mtxResult - Matrix���󣬷��ط�����Ľ�
        * @return bool �ͣ�����������Ƿ�ɹ�
        */
        bool GetRootsetGauss(CGeoMatrix *mtxResult);

		/**
		* ���������С��������ĺ�˹�ɶ��±任��
		* 
		* @param mtxResult - Matrix���󣬷��ط���������
		* @param mtxQ - Matrix���󣬷��غ�˹�ɶ��±任��Q����
		* @param mtxR - Matrix���󣬷��غ�˹�ɶ��±任��R����
		* @return bool �ͣ�����������Ƿ�ɹ�
		*/
        bool GetRootsetMqr(CGeoMatrix *mtxResult, CGeoMatrix *mtxQ, CGeoMatrix *mtxR);

	private:
		CGeoMatrix *m_mtxLECoef;		// ϵ������
		CGeoMatrix *m_mtxLEConst;		// ��������
	};
}
#endif
