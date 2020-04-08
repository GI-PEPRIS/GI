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
#ifndef __ANYPETRO_POOL_RANK_PREDICATOR_H__
#define __ANYPETRO_POOL_RANK_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to stl
#include "any/base/anystl.h"

// refer to cgeopoint
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// refer to distribution
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CPoolRankPredicator : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		struct ResourcePredication
		{
			// 5%, 25%, 50%, 75%, 95%, and the matched sample
			const static int PERCENTILES = 6;

			// resource type
			short m_resType;
			//resource class
			int m_resourceclass;
			//resource type
			int m_resourcecategory;
			// samples
			CGeoPoint<double> *m_samples;
			int m_number;

			// iterations
			long m_iterations;
			// sample number
			long m_samplings;
			
			// before which order sequence
			long m_beforeOrder;
			CGeoPoint<double> **m_percentiles;
			// the maxium size of a pool
			double m_maxP;
			// the maximum number 
			long m_maxN;
			// N is known
			bool m_isKnown;

			// distribution type of pool size
			string m_distributionName;
			double m_alpha;
			double m_lambda;

			// is to erase uncertainty
			bool m_isUncertainty;
			long m_inorder;
			long m_outorder;

			std::vector<std::vector<string>> m_stringpercentiles;
			/*!
			*
			**/
			ResourcePredication() : m_resType(0),m_resourcecategory(0),m_resourceclass(0),m_samples(0), m_number(0), m_iterations(500), m_samplings(1000), m_beforeOrder(50), \
				m_inorder(0),m_outorder(0),m_percentiles(0), m_maxP(0.), m_maxN(0), m_isKnown(false), m_distributionName("lognormal"), m_alpha(1.), m_lambda(4.5), m_isUncertainty(true)
			{
				m_stringpercentiles.clear();
			}

			/*!
			*
			**/
			void Reset()
			{
				m_resType=0;
				m_resourcecategory=0;
				m_resourceclass=0;
				m_samples=0; 
				m_number=0; 
				m_iterations=500; 
				m_samplings=1000;
				m_beforeOrder=50;
				m_percentiles=0; 
				m_maxP=0; 
				m_maxN = 0;
				m_isKnown = false;
				m_distributionName="lognormal";
				m_alpha=1.0; 
				m_lambda=4.5; 
				m_isUncertainty=true;
				m_inorder=0;
				m_outorder=0;
				m_stringpercentiles.clear();
			}

			/*!
			*
			**/
			ResourcePredication(const ResourcePredication &other)
			{
				Reset();
				*this = other;
			}

			~ResourcePredication()
			{
				Release();
				Reset();
			}
			/*!
			*
			**/
			const ResourcePredication &operator=(const ResourcePredication &other)
			{
				if(this == &other)
				{
					return *this;
				}

				Release();
				Reset();

				m_resType = other.m_resType;
				m_resourcecategory=other.m_resourcecategory;
				m_resourceclass=other.m_resourceclass;
				// samples
				if(other.m_samples)
				{
					m_number = other.m_number;
					m_samples = (CGeoPoint<double> *)::malloc(sizeof(CGeoPoint<double>) * m_number);
					::memcpy(m_samples, other.m_samples, sizeof(CGeoPoint<double>) * m_number);
				}

				// iterations
				m_iterations = other.m_iterations;
				// sample number
				m_samplings = other.m_samplings;
			
				// before which order sequence
				m_beforeOrder = other.m_beforeOrder;
				if(other.m_percentiles)
				{
					
					Prepare();
					int i = 0;
					for(; i < m_beforeOrder; i++)
					{
						int j = 0;
						for(; j < PERCENTILES; j++)
						{
							m_percentiles[i][j] = other.m_percentiles[i][j];
						}
					}
				}

				// distribution type of pool size
				m_distributionName = other.m_distributionName;
				m_maxP = other.m_maxP;
				m_maxN = other.m_maxN;
				m_isKnown = other.m_isKnown;
				m_alpha = other.m_alpha;
				m_lambda = other.m_lambda;
				m_isUncertainty = other.m_isUncertainty;
				m_inorder=other.m_inorder;
				m_outorder = other.m_outorder;
				return *this;
			}

			/*!
			*
			**/
			void Prepare()
			{
				m_percentiles = (CGeoPoint<double> **)::malloc(sizeof(CGeoPoint<double>*) * m_beforeOrder);
				int i = 0;
				for(; i < m_beforeOrder; i++)
				{
					m_percentiles[i] = (CGeoPoint<double> *)::malloc(sizeof(CGeoPoint<double>) * PERCENTILES);
					::memset(m_percentiles[i], 0x00, sizeof(CGeoPoint<double>) * PERCENTILES);
				}
			}

			void PercentilesToParameterString()
			{
				m_stringpercentiles.clear();
				if(!m_percentiles)
				{
					return;
				}

				for(int i=0; i < m_beforeOrder; i++)
				{
					std::vector<string> ss;
					for(int j=0;j<PERCENTILES;j++)
					{
						char parameter[512] ="\0"; 
						::sprintf(parameter,  "%.3f#%.3f#%.3f#%.3f", m_percentiles[i][j].m_x,m_percentiles[i][j].m_y,m_percentiles[i][j].m_z,m_percentiles[i][j].m_w);
						string s(parameter);
						ss.push_back(s);
					}
					m_stringpercentiles.push_back(ss);
				}
			}
			void ParameterStringToPercentiles()
			{
				if(m_percentiles)
				{
					int i = 0;
					for(; i < m_beforeOrder; i++)
					{
						::free(m_percentiles[i]);
					}
					::free(m_percentiles);
				}
				m_percentiles = 0;
				if(m_stringpercentiles.size()<=0)
				{
					return;
				}
				Prepare();

				for(int i=0; i < m_stringpercentiles.size(); i++)
				{
					for(int j=0;j<m_stringpercentiles[i].size();j++)
					{
						string s = m_stringpercentiles[i][j];
						CAnyTokenString curToken("#","","");
						int curCount = curToken.Trim(s.c_str(), s.size());
		
						m_percentiles[i][j].m_x = ::atof(curToken.GetAt(0));
						m_percentiles[i][j].m_y = ::atof(curToken.GetAt(1));
						m_percentiles[i][j].m_z = ::atof(curToken.GetAt(2));
						m_percentiles[i][j].m_w = ::atof(curToken.GetAt(3));
					}
					
				}
			}
			/*!
			*
			**/
			bool IsReady()
			{
				if(!m_samples || !m_number || !m_percentiles || !m_beforeOrder || !m_iterations)
				{
					return false;
				}

				return true;
			}

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

				if(m_percentiles)
				{
					int i = 0;
					for(; i < m_beforeOrder; i++)
					{
						::free(m_percentiles[i]);
					}
					::free(m_percentiles);
				}
				m_percentiles = 0;
			}

						/*!
			*
			**/
			string ToParameterString()
			{

				int Uncertaintycheck ;
				if(m_isUncertainty)
				{
					Uncertaintycheck=1;
				}
				else
				{
					Uncertaintycheck=0;
				}
				char parameter[512] ="\0"; 
				::sprintf(parameter,  "%d#%d#%d#%d#%s#%.2f#%.2f#%d#%d#%d#%d", 
				m_resType,m_resourcecategory,m_resourceclass,m_beforeOrder,m_distributionName.c_str(),m_alpha,m_lambda,Uncertaintycheck,m_maxN,m_inorder,m_outorder);

				return parameter;
			}

			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken("#","","");
				int curCount = curToken.Trim(parameter.c_str(), parameter.size());
				//assert(curCount == 11);

				m_resType = ::atoi(curToken.GetAt(0));
				m_resourcecategory = ::atoi(curToken.GetAt(1));
				m_resourceclass = ::atoi(curToken.GetAt(2));
				m_beforeOrder = ::atoi(curToken.GetAt(3));
				m_distributionName = curToken.GetAt(4);
				m_alpha = ::atof(curToken.GetAt(5));

				m_lambda = ::atof(curToken.GetAt(6));
				int Uncertaintycheck;
				Uncertaintycheck = ::atoi(curToken.GetAt(7));
				if(Uncertaintycheck==0)
				{
					m_isUncertainty=false;
				}
				else
				{
					m_isUncertainty=true;
				}
				if(curCount>8)
				{
					m_maxN = ::atoi(curToken.GetAt(8));
				}
				else
				{
					m_maxN=0;
				}
				m_inorder = ::atoi(curToken.GetAt(9));
				m_outorder = ::atoi(curToken.GetAt(10));
			}








		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CPoolRankPredicator(CAccumulationElement *curElement);

		/*!
		*
		**/
		virtual ~CPoolRankPredicator();

	public:
		//
		//
		//
		/*!
		*
		**/
		ResourcePredication &GetPredication()
		{
			return m_predication;
		}

		/*!
		*
		**/
		bool MakePredication(ResourcePredication &predication, CAnyFunctor &progress);

		/*!
		*
		**/
		void Relese()
		{
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

		/*!
		从数据库中获取grid的详细信息
		**/
		bool GetGridDetailInfo(long practiceid, long elementid, long activityid, std::vector<string> &geologicalsamples,string type );
		void RestorePracticeVector(long practiceIdx);
	private:
		//
		ResourcePredication m_predication;
	public:
		string m_remark;
		std::vector<string> m_gridstringvector;
		char *m_groupbitmap;
		int m_groupbitmaplength;
		char *m_distributionbitmap;
		int m_distributionbitmaplength;
		std::vector<std::vector<string>> m_resgridstringvector;
	};
}

#endif