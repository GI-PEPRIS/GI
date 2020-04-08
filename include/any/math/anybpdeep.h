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
		//逐层向前计算输出
		std::vector<double> ComputeOut(std::vector<double> &in);
		//逐层反向计算误差并修改权重
		void UpdateWeight(std::vector<double> &tar);
	public:
		//由于是n层神经网络，我们用二维数组layer记录节点值，第一维为层数，第二维为该层节点位置，数组的值为节点值；
		// 同样，节点误差值layerErr也是相似方式记录。
		// 用三维数组layer_weight记录各节点权重，第一维为层数，第二维为该层节点位置，第三维为下层节点位置，数组的值为某节点到达下层某节点的权重值，初始值为0-1之间的随机数。
		// 为了优化收敛速度，这里采用动量法权值调整，需要记录上一次权值调整量，用三维数组layer_weight_delta来记录，
		// 截距项处理：程序里将截距的值设置为1，这样只需要计算它的权重就可以了。

		// layer number
		std::vector<int> m_layerNum;
		//神经网络各层节点 
		std:: vector<std::vector<double> > m_layers;
		//神经网络各节点误差 
		std:: vector<std::vector<double> > m_layerErr;
		//各层节点权重 
		std::vector<std::vector<std::vector<double> > > m_layer_weight;
		//各层节点权重动量 
		std::vector<std::vector<std::vector<double> > > m_layer_weight_delta;
		//动量系数
		double m_mobp; 
		//学习系数
		double m_rate;
	};
}
#endif
