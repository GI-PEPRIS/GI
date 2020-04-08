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
#ifndef __ANYPETRO_LINEAR_RESOURCE_PREDICATOR_H__
#define __ANYPETRO_LINEAR_RESOURCE_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to stl
#include "any/base/anystl.h"

// refer to cgeopoint
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CLinearResourcePredicator : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		enum ShiftQ
		{
			SQ_Unknown = -1,
			SQ_Sequence,
			SQ_Error,
			SQ_Max,
		};

		/*!
		*
		**/
		struct RegressionLine
		{
			long m_start;	// subscript for current samples ordered
			long m_end;	// subscript for current samples ordered
			double m_slope;
			double m_interception;

			/*!
			*
			**/
			string ToParameterString()
			{
				char parameter[512] = "";
				::sprintf(parameter, "%d|%d|%.3f|%.3f", m_start, m_end, m_slope, m_interception);

				return parameter;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("|");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				assert(curCount == 4);

				m_start = ::atoi(curToken.GetAt(0));
				m_end = ::atoi(curToken.GetAt(1));
				m_slope = ::atof(curToken.GetAt(2));
				m_interception = ::atof(curToken.GetAt(3));
			}
		};

		/*!
		*
		**/
		struct ResourcePredication
		{
			// which samples
			// 0 means the all samples except those abnormal samples represented by < 0
			// > 0 means different sample groups
			short m_resType;

			// shift existing Q in different ways
			// ...
			short m_shiftType;
			// minimum pool size
			double m_minP;
			// regression lines
			int m_groups;
			RegressionLine *m_regressionLines;

			// results
			// ...
			// maximum pool size
			double m_maxP;
			// pool number
			int m_totalN;
			// total Q in average
			double m_avgQ;
			// total Q in maximum
			double m_maxQ;
			// total Q in minimum
			double m_minQ;
			// swasonQ
			double m_swasonQ;

			// Q sequences
			int *m_rangeN;
			CGeoPoint<double> **m_rangeP;	// x for sample value, y for predication value

			// pool structure analysis
			int m_ranges;

			//resource class
			int m_resourceclass;
			//resource type
			int m_resourcecategory;

			std::vector<CGeoPoint<double>> m_lastseq;
			/*!
			*
			**/
			ResourcePredication() 
			{
				Reset();
			}

			~ResourcePredication() 
			{
				Release();
				Reset();
			}

			
			/*!
			*
			**/
			void Release()
			{
				// pool number against different sample groups
				if(m_rangeN)
				{
					::free(m_rangeN);
				}
				m_rangeN = 0;

				// pool sizes against different sample groups
				if(m_rangeP)
				{
					int i = 0;
					for(; i < m_groups; i++)
					{
						if(m_rangeP[i])
						{
							::free(m_rangeP[i]);
							m_rangeP[i]=0;
						}
					}
					::free(m_rangeP);
				}
				m_rangeP = 0;

				// regression lines from different sample group
				if(m_regressionLines)
				{
					::free(m_regressionLines);
				}
				m_regressionLines = 0;

				m_lastseq.clear();
			}

			ResourcePredication(const ResourcePredication &other)
			{
				Release();
				Reset();
				*this = other;
			}

			/*!
			*
			**/
			void Reset()
			{
				m_resType = 0;
				m_shiftType = SQ_Sequence;
				m_minP = 1.;
				m_maxP = m_minP;
				m_avgQ = 0.;
				m_maxQ = 0.;
				m_minQ = 0.;
				m_totalN = 0;
				m_rangeN = 0;
				m_rangeP = 0;
				m_groups = 1;
				m_regressionLines = 0;
				m_ranges = 3;
				m_resourceclass=0;
				m_resourcecategory=0;
				m_swasonQ = 0;
				m_lastseq.clear();
			}

			/*!
			*
			**/
			const ResourcePredication &operator=(const ResourcePredication &other)
			{
				//
				if(this == &other)
				{
					return *this;
				}

				//
				Release();
				Reset();

				//
				m_resType = other.m_resType;
				m_shiftType = other.m_shiftType;
				m_minP = other.m_minP;
				m_maxP = other.m_maxP;
				m_avgQ = other.m_avgQ;
				m_maxQ = other.m_maxQ;
				m_minQ = other.m_minQ;
				m_totalN = other.m_totalN;
				m_ranges = other.m_ranges;
				m_resourcecategory=other.m_resourcecategory;
				m_resourceclass=other.m_resourceclass;
				m_swasonQ = other.m_swasonQ;

				m_groups = other.m_groups;
				m_rangeN = (int *)::malloc(sizeof(int) * other.m_groups);
				::memcpy(m_rangeN, other.m_rangeN, sizeof(int) * other.m_groups);
				m_rangeP =  (CGeoPoint<double> **)::malloc(sizeof(CGeoPoint<double> *) * other.m_groups);
				int i = 0;
				for(; i < other.m_groups; i++)
				{
					m_rangeP[i] = (CGeoPoint<double> *)::malloc(sizeof(CGeoPoint<double>) * other.m_rangeN[i]);
					::memcpy(m_rangeP[i], other.m_rangeP[i], sizeof(CGeoPoint<double>) * other.m_rangeN[i]);
				}
				m_regressionLines = (RegressionLine *)::malloc(sizeof(RegressionLine) * other.m_groups);
				::memcpy(m_regressionLines, other.m_regressionLines, sizeof(RegressionLine) * other.m_groups);

				m_lastseq.clear();
				for(int i=0;i<other.m_lastseq.size();i++)
				{
					m_lastseq.push_back(other.m_lastseq[i]);
				}
				//
				return *this;
			}
			
			/*!
			*
			**/
			bool IsValid() const
			{
				if(!m_totalN ||
					!m_minQ ||
					!m_maxP || 
					!m_rangeN || 
					!m_rangeP || 
					(m_avgQ < m_minQ) || 
					( m_maxQ < m_avgQ))
				{
					return false;
				}

				return true;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");
				int count = curToken.Trim(parameter.c_str(), parameter.size());

				m_resType = ::atoi(curToken.GetAt(0));
				m_shiftType = ::atoi(curToken.GetAt(1));
				m_minP = ::atof(curToken.GetAt(2));
				m_groups = ::atoi(curToken.GetAt(3));
				m_ranges = ::atoi(curToken.GetAt(4));
				m_resourceclass = ::atoi(curToken.GetAt(5));
				m_resourcecategory = ::atoi(curToken.GetAt(6));
				m_swasonQ = ::atof(curToken.GetAt(7));
				if(count==11)
				{
					m_totalN = ::atoi(curToken.GetAt(8));
					m_maxP = ::atof(curToken.GetAt(9));
				}
				assert(!m_regressionLines);
				if(m_regressionLines)
				{
					::free(m_regressionLines);
				}
				m_regressionLines = (RegressionLine *)::malloc(sizeof(RegressionLine) * m_groups);
				int i = 0;
				for(; i < m_groups; i++)
				{
					m_regressionLines[i].FromParameterString((string)(curToken.GetAt(count-m_groups+i)));
				}
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				m_groups = m_regressionLines ? m_groups : 0;
				char parameter[512] = "";
				::sprintf(parameter, "%d#%d#%.3f#%d#%d#%d#%d#%.3f#%d#%.2f#", m_resType, m_shiftType, m_minP, m_groups,m_ranges,m_resourceclass,m_resourcecategory,m_swasonQ,m_totalN,m_maxP);
				string str = parameter;

				int i = 0;
				for(; i < m_groups; i++)
				{
					str += m_regressionLines[i].ToParameterString();
					if(i < m_groups -1)
					{
						str += "#";
					}
				}
				return str;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CLinearResourcePredicator(CAccumulationElement *curElement);

		/*!
		*
		**/
		virtual ~CLinearResourcePredicator();

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitSamples(CGeoPoint<double> *samples, int number);

		/*!
		*
		**/
		const CGeoPoint<double> *GetSamples(int &number) const;

		/*!
		//返回代码
		//0 非法样本
		//1 正确
		//2 回归线个数错误
		//3 分组计算 maxP<minp
		//4 预测结果 N 小于0
		//5 计算结果错误
		//6 总油藏数小于样本值
		**/
		int MakePredication(ResourcePredication &predication);

		/*!
		const?
		**/
		ResourcePredication &GetPredication()
		{
			return m_predication;
		}

		/*!
		isForNumber：是否是统计个数，true个数，false规模
		isusergroups:是否是用户自定义分组，true自定义直接按leftight范围，false 平均范围
		**/
		bool GetRangeDesc(int order, double &left, double &right, double &sample, double &predication, double &diff, bool isForNumber = true,bool isusergroups=false);

		/*!
		*
		**/
		void Release()
		{
			if(m_samples)
			{
				::free(m_samples);
			}
			m_samples = 0;
			m_number = 0;

			m_predication.Release();
		}

		//
		//
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);

		void ReSetPoolPosition(	 int predicationN,
								 int sampleN,
								double *samples,
								double *predicationpools,
								double maxpool,
								double slop,
								double intercept,
								int *position,
								std::vector<CGeoPoint<double>> &lastseq) ;   //position的元素个数=sampleN

	private:
		//
		//
		//
		/*!
		*
		**/
		double DoGetMaxP();

		/*!
		*
		**/
		double DoReplacePredicationInSequence(ResourcePredication &predication);

		/*!
		*
		**/
		double DoReplacePredicationInError(ResourcePredication &predication);

		/*!
		*
		**/
		double DoMatchAsMinError(ResourcePredication &predication, CGeoPoint<double> &curValue, int &whichGroup, int &whichPos);

		/*!
		*
		**/
		double DoCalculateStudentQ(ResourcePredication &predication, double probability);

	private:
		// samples
		CGeoPoint<double> *m_samples;
		int m_number;

		// parameters
		ResourcePredication m_predication;

	public:
		string m_remark;
		char *m_datagroupbitmap;
		int m_datagroupbitmaplength;
		char *m_resgroupbitmap;
		int m_resgroupbitmaplength;
		char *m_disbitmap;
		int m_disbitmaplength;
		std::vector<std::vector<string>> m_datagroup;
		std::vector<std::vector<string>> m_resgroup;
	};
}

#endif