/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYSDE_ANY_SNESIM_H__
#define __ANYSDE_ANY_SNESIM_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"
#include "anysdelayer.h"
using namespace AnySDE;

namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnySnesim
	{
	public:
		struct SNESIMitem
		{
			int m_surrondgridcount;//周围格子的个数
			std::vector<int> m_surrondvalues;//周围格子的值，-1表示没有此格子
			std::vector<int> m_surrondvalues_unorder;//周围已有格子的值,不区分格子位置
			std::vector<int> m_valuecounts;//中心格子各个值出现的次数,下标即值
			SNESIMitem *m_parent;
			std::vector<SNESIMitem*> m_childrens;

			SNESIMitem() : m_surrondgridcount(0), m_parent(0)
			{
			}
			~SNESIMitem()
			{
				for(int i = 0; i < m_childrens.size(); i++)
				{
					delete m_childrens[i];
					m_childrens[i] = 0;
				}
				m_childrens.clear();
				m_parent = 0;
			}
			SNESIMitem(const SNESIMitem &other)
			{
				*this = other;
			}
			const SNESIMitem &operator=(const SNESIMitem &other)
			{
				if(this != &other)
				{
					m_surrondgridcount = other.m_surrondgridcount;
					m_surrondvalues = other.m_surrondvalues;
					m_surrondvalues_unorder = other.m_surrondvalues_unorder;
					m_valuecounts = other.m_valuecounts;
					m_parent = other.m_parent;
					m_childrens = other.m_childrens;
				}
				return *this;
			}
			static bool Compareitem(const SNESIMitem &a, const SNESIMitem &b)
			{
				if(a.m_surrondgridcount < b.m_surrondgridcount)
					return true;
				if(a.m_surrondgridcount > b.m_surrondgridcount)
					return false;
				for(int i = 0; i < a.m_surrondvalues.size(); i++)
				{
					if(a.m_surrondvalues[i] < b.m_surrondvalues[i])
						return true;
					if(a.m_surrondvalues[i] > b.m_surrondvalues[i])
						return false;
				}
				return false;
			}
		};
		struct SNESIMParameter
		{
			int m_taskcount;
			int m_index;
			std::vector<SNESIMitem> &m_cmps;
			std::vector<int> &m_centerormotevalues;
			int m_traintype;
			int m_randcount;
			bool m_addtotrain;
			SNESIMParameter(int taskcount, int index, std::vector<SNESIMitem> &cmps, std::vector<int> &centerormotevalues, int traintype, int randcount, bool addtotrain) : \
				m_cmps(cmps), m_centerormotevalues(centerormotevalues)
			{
				m_taskcount = taskcount;
				m_index = index;
				m_traintype = traintype;
				m_randcount = randcount;
				m_addtotrain = addtotrain;
			}
			SNESIMParameter(int taskcount, int index, std::vector<SNESIMitem> &cmps, std::vector<int> &centerormotevalues, int traintype) : \
				m_cmps(cmps), m_centerormotevalues(centerormotevalues)
			{
				m_taskcount = taskcount;
				m_index = index;
				m_traintype = traintype;
				m_randcount = 1;
			}
		};
	public:
		//
		//
		//
		/*!
		* 
		**/
		CAnySnesim();
		~CAnySnesim();

	public:

		/*!
		*
		**/
		void Clear();
		bool IsSameItem(SNESIMitem &a, SNESIMitem &b);
		bool IsSameItem_NoOrder(SNESIMitem &a, SNESIMitem &b);
		bool IsCover(SNESIMitem &a, SNESIMitem &b);
		bool IsCover_NoOrder(SNESIMitem &a, SNESIMitem &b);
		int SameValueCount(SNESIMitem &a, SNESIMitem &b);
		void MergeItems(std::vector<SNESIMitem> &a, std::vector<SNESIMitem> &b, std::vector<SNESIMitem> &output);
		void FindParentItems(SNESIMitem &a, std::vector<SNESIMitem> &parentitems, int surrondgridcount);
		void FindNeighborItems(SNESIMitem &a, std::vector<SNESIMitem> &neighboritems, int samevaluecount);
		CAnySnesim::SNESIMitem* FindTreeItem(SNESIMitem *root, SNESIMitem &cmp);
		CAnySnesim::SNESIMitem* FindTreeItemExist(SNESIMitem *root, SNESIMitem &cmp);
		void AddTreeItem(SNESIMitem *&root, SNESIMitem &cmp);

		void Train(std::vector<SNESIMitem> &cmps, std::vector<int> &centervalues, int traintype);
		void TrainMT(std::vector<SNESIMitem> &cmps, std::vector<int> &centervalues, int traintype);
		void Train_Thread(const SNESIMParameter &parameter);
		void DoTrainOneGrid(SNESIMitem &cmp, int centervalue, int traintype);
		void Predict(std::vector<SNESIMitem> &cmps, std::vector<int> &motevalues, int traintype, int randcount, bool addtotrain);
		void PredictMT(std::vector<SNESIMitem> &cmps, std::vector<int> &motevalues, int traintype, int randcount, bool addtotrain);
		void Predict_Thread(const SNESIMParameter &parameter);
		void DoPredictOneGrid(SNESIMitem &cmp, int &motevalue, int traintype, int randcount, bool addtotrain);
	public:
		SNESIMitem *m_snesimroot;//搜索树根节点
		std::vector<SNESIMitem> m_snesimitems;//训练集
		std::vector<SNESIMitem> m_snesimitemscache;//训练集缓存
		int m_snesimitemscachelimit;//缓存大小
		int m_snesimcmin;//阈值cmin
		int m_snesimvaluecount;//取值种类的个数
	};
}
#endif