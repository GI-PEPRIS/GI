/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYMATH_ANN_BP_H__
#define __ANYMATH_ANN_BP_H__

// refer to macro
#include "anymath.h"
#include "any/base/anystl.h"

namespace  AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyBPDeep
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyBPDeep();
		~CAnyBPDeep();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Train(std::vector<double> &in, std::vector<double> &tar);
		void BpDeep(std::vector<int> &layernum, double rate, double mobp);
		//�����ǰ�������
		std::vector<double> ComputeOut(std::vector<double> &in);
		//��㷴��������޸�Ȩ��
		void UpdateWeight(std::vector<double> &tar);
	public:
		//������n�������磬�����ö�ά����layer��¼�ڵ�ֵ����һάΪ�������ڶ�άΪ�ò�ڵ�λ�ã������ֵΪ�ڵ�ֵ��
		// ͬ�����ڵ����ֵlayerErrҲ�����Ʒ�ʽ��¼��
		// ����ά����layer_weight��¼���ڵ�Ȩ�أ���һάΪ�������ڶ�άΪ�ò�ڵ�λ�ã�����άΪ�²�ڵ�λ�ã������ֵΪĳ�ڵ㵽���²�ĳ�ڵ��Ȩ��ֵ����ʼֵΪ0-1֮����������
		// Ϊ���Ż������ٶȣ�������ö�����Ȩֵ��������Ҫ��¼��һ��Ȩֵ������������ά����layer_weight_delta����¼��
		// �ؾ���������ｫ�ؾ��ֵ����Ϊ1������ֻ��Ҫ��������Ȩ�ؾͿ����ˡ�

		// layer number
		std::vector<int> m_layerNum;
		//���������ڵ� 
		std:: vector<std::vector<double> > m_layers;
		//��������ڵ���� 
		std:: vector<std::vector<double> > m_layerErr;
		//����ڵ�Ȩ�� 
		std::vector<std::vector<std::vector<double> > > m_layer_weight;
		//����ڵ�Ȩ�ض��� 
		std::vector<std::vector<std::vector<double> > > m_layer_weight_delta;
		//����ϵ��
		double m_mobp; 
		//ѧϰϵ��
		double m_rate;
	};
}
#endif
