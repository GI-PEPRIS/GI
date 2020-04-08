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
#ifndef __ANYPETRO_GSC_NON_PARAMETER_PREDICATOR_H__
#define __ANYPETRO_GSC_NON_PARAMETER_PREDICATOR_H__

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
	class ANYPETRO_CLASS CGSCNonParameterPredicator : public CAccumulationAssessor
	{
	public:
		/*!
		*
		**/
		struct ResourcePredication
		{
			// resource type
			short m_resourceType;

			// calculate type
			// 0 -contour 1 - Nelder
			short m_calculationType;

			// found samples
			int m_sampleNumber;
			CGeoPoint<double> *m_samples;

			// interval number
			int m_groupNumber;
			// interval value
			double *m_groups;
			// average pool size against one group
			double *m_groupV;

			// kinds of limits
			long m_iterations;
			double m_error;

			// alpha, beta
			double m_beta;
			double m_lambda;

			// predicated values
			int *m_predicatedN;
			int *m_foundN;
			double *m_predicatedQ;
			double *m_foundQ; // min Q

			// for triangle distirbution
			double m_minQ;
			double m_avgQ;
			double m_maxQ;
			double m_swasonQ;
			//resource type
			int m_resourcecategory;
			//resource class
			int m_resourceclass;

			int m_grouptype;
			int m_PNnum;//预测总个数
			/*!
			*
			**/
			ResourcePredication() : m_resourceType(0), m_resourcecategory(0),m_resourceclass(0),m_calculationType(1), m_sampleNumber(0), m_samples(0), m_groupNumber(0), m_groups(0), m_groupV(0)
				, m_iterations(0), m_error(0.), m_lambda(0.), m_beta(0.)
				, m_predicatedN(0), m_foundN(0), m_predicatedQ(0), m_foundQ(0), m_minQ(0.), m_avgQ(0.), m_maxQ(0.),m_swasonQ(0.),m_grouptype(0),m_PNnum(0)
			{
			}

			~ResourcePredication()
			{
				Release();
			}
			
			ResourcePredication(const ResourcePredication &other)
			{
				Release();
				*this = other;
			}

			/*!
			*
			**/
			const ResourcePredication &operator=(const ResourcePredication &other)
			{
				// whether is the same one
				if(this == &other)
				{
					return *this;
				}

				// release
				Release();

				// resource type
				m_resourceType = other.m_resourceType;

				// calculation type
				m_calculationType = other.m_calculationType;

				// samples
				if(other.m_samples && other.m_sampleNumber>0)
				{
					m_sampleNumber = other.m_sampleNumber;
					m_samples = (CGeoPoint<double> *)::malloc(m_sampleNumber * sizeof(CGeoPoint<double>));
					::memcpy(m_samples, other.m_samples, other.m_sampleNumber * sizeof(CGeoPoint<double>));
				}


				// intervals

				if(other.m_groups && other.m_groupNumber>0)
				{
					m_groupNumber = other.m_groupNumber;
					m_groups = (double *)::malloc((m_groupNumber+1) * sizeof(double));
					::memcpy(m_groups, other.m_groups, (m_groupNumber+1) * sizeof(double));
				}
				if(other.m_groupV && other.m_groupNumber>0)
				{
					m_groupV = (double *)::malloc(m_groupNumber * sizeof(double));
					::memcpy(m_groupV, other.m_groupV, m_groupNumber * sizeof(double));
				}

				// kinds of limits
				m_iterations = other.m_iterations;
				m_error = other.m_error;

				// alpha, beta
				m_lambda = other.m_lambda;
				m_beta = other.m_beta;

				// predicated values
				if(other.m_predicatedN && other.m_groupNumber>0)
				{
					m_predicatedN = (int *)::malloc(m_groupNumber * sizeof(int));
					::memcpy(m_predicatedN, other.m_predicatedN, m_groupNumber * sizeof(int));
				}

				if(other.m_foundN && other.m_groupNumber>0)
				{
					m_foundN = (int *)::malloc(m_groupNumber * sizeof(int));
					::memcpy(m_foundN, other.m_foundN, m_groupNumber * sizeof(int));
				}


				if(other.m_predicatedQ && other.m_groupNumber>0)
				{
					m_predicatedQ = (double *)::malloc(m_groupNumber * sizeof(double));
					::memcpy(m_predicatedQ, other.m_predicatedQ, m_groupNumber * sizeof(double));
				}

				if(other.m_foundQ && other.m_groupNumber>0)
				{
					m_foundQ = (double *)::malloc(m_groupNumber * sizeof(double)); // min Q
					::memcpy(m_foundQ, other.m_foundQ, m_groupNumber * sizeof(double));
				}

				m_minQ = other.m_minQ;
				m_avgQ = other.m_avgQ;
				m_maxQ = other.m_maxQ;
				m_swasonQ=other.m_swasonQ;
				
				m_resourcecategory = other.m_resourcecategory;
				m_resourceclass= other.m_resourceclass;

				m_grouptype = other.m_grouptype;
				return *this;
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
				m_sampleNumber = 0;

				if(m_groups)
				{
					::free(m_groups);
				}
				m_groups = 0;
				m_groupNumber = 0;

				if(m_groupV)
				{
					::free(m_groupV);
				}
				m_groupV = 0;

			    if(m_predicatedN)
				{
					::free(m_predicatedN);
				}
				m_predicatedN = 0;

			    if(m_foundN)
				{
					::free(m_foundN);
				}
				m_foundN = 0;

			    if(m_predicatedQ)
				{
					::free(m_predicatedQ);
				}
				m_predicatedQ = 0;

			    if(m_foundQ)
				{
					::free(m_foundQ);
				}
				m_foundQ = 0;

				m_grouptype=0;
				m_PNnum=0;
			}

			/*!
			*
			**/
			bool IsReady()
			{
				if(!m_sampleNumber || !m_samples || !m_groupNumber || !m_groups)
				{
					return false;
				}

				return true;
			}

			/*!
			*
			**/
			bool IsValid()
			{
				if(!m_predicatedQ || !m_predicatedN)
				{
					return false;
				}

				return true;
			}

			/*!
			*
			**/
			void MakeStatistics()
			{
				// calculate the average pool against one group
				assert(m_groups);
				if(m_groupV)
				{
					::free(m_groupV);
				}
				m_groupV = (double *)::malloc(m_groupNumber * sizeof(double));
				int i = 0;
				for(; i < m_groupNumber; i++)
				{
					m_groupV[i] = (m_groups[i] + m_groups[i+1]) / 2.;
				}

				// statistics for current samples
				if(m_foundN)
				{
					::free(m_foundN);
				}
				m_foundN = (int *)::malloc((m_groupNumber+1) * sizeof(int));
				::memset(m_foundN, 0x00, (m_groupNumber+1) * sizeof(int));
				if(m_foundQ)
				{
					::free(m_foundQ);
				}
				m_foundQ = (double *)::malloc((m_groupNumber+1) * sizeof(double));
				::memset(m_foundQ, 0x00, (m_groupNumber+1) * sizeof(double));

				// histogram statisitc and replace the current found pool with average size
				i = 0;
				for(; i < m_sampleNumber; i++)
				{
					int j = 0;
					for(; j < m_groupNumber; j++)
					{
						// left-open, right-close decision
						if(m_samples[i].m_x >= m_groups[j] && m_samples[i].m_x < m_groups[j+1])
						{
							m_foundN[j]++;
							m_foundQ[j] += m_samples[i].m_x;
							m_samples[i].m_y = m_groupV[j];

							break;
						}
					}
				}

				// get culmulated Q in discovery sequence
				m_samples[0].m_w = m_samples[0].m_x; /*m_samples[0].m_y*/;
				i = 1;
				for(; i < m_sampleNumber; i++)
				{
					m_samples[i].m_w = m_samples[i-1].m_w + m_samples[i].m_x; /* m_samples[i].m_y;*/
				}
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				//
				assert(m_groupNumber);

				int PN=0;
				for(int n=0; n < m_groupNumber; n++)
				{
					PN = PN+m_predicatedN[n];
				}

				char parameter[512] = "";
				::sprintf(parameter, "%d#%d#%d#%d#%.1f#%.2f#%.2f#%d#%d#%.2f#%d#%d", m_resourceType, m_calculationType, m_groupNumber, m_iterations, m_error, m_beta, m_lambda,m_resourcecategory,m_resourceclass,m_swasonQ,m_grouptype,PN);

				// store groups definition
				string str = parameter;
				if(m_groupNumber)
				{
					str += "#";
					int i = 0;
					for(; i < m_groupNumber + 1; i++)
					{
						char value[127] = "";
						::sprintf(value, "%.1f", m_groups[i]);
						str += value;

						if(i < m_groupNumber)
						{
							str+= "|";
						}
					}
				}
				str = (str.size() < 255) ? str : "";
				return str;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");

				int count = curToken.Trim(parameter.c_str(), parameter.size());
				//assert(count == 11);

				m_resourceType = ::atoi(curToken.GetAt(0));
				m_calculationType = ::atoi(curToken.GetAt(1));
				m_groupNumber = ::atoi(curToken.GetAt(2));
				m_iterations = ::atoi(curToken.GetAt(3));
				m_error = ::atof(curToken.GetAt(4));
				m_beta = ::atof(curToken.GetAt(5));
				m_lambda = ::atof(curToken.GetAt(6));
				m_resourcecategory = ::atoi(curToken.GetAt(7));
				m_resourceclass = ::atoi(curToken.GetAt(8));
				m_swasonQ = ::atof(curToken.GetAt(9));
				m_grouptype = ::atoi(curToken.GetAt(10));
				if(count==13)
				{
					m_PNnum = ::atoi(curToken.GetAt(11));
				}

				CAnyTokenString groupToken;
				groupToken.SetToken("|");
				int groups = groupToken.Trim(curToken.GetAt(count-1), ::strlen(curToken.GetAt(count-1)));
				if(groups == m_groupNumber+1)
				{
					assert(!m_groups);
					if(m_groups)
					{
						::free(m_groups);
					}
					m_groups = (double *)::malloc(sizeof(double) * (m_groupNumber+1));
					int i = 0;
					for(; i < groups; i++)
					{
						m_groups[i] = ::atof(groupToken.GetAt(i));
					}

					if(m_foundN)
					{
						::free(m_foundN);
					}
					m_foundN = (int *)::malloc(sizeof(int) * m_groupNumber);
					::memset(m_foundN, 0x00, sizeof(int) * m_groupNumber);
				}
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CGSCNonParameterPredicator(CAccumulationElement *curElement);

		/*!
		*
		**/
		virtual ~CGSCNonParameterPredicator();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool MakePredication(ResourcePredication &predication);

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
		void Release()
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
	private:
		//
		//
		//
		/*!
		*
		**/
		int DoEstimateN(int foundN, double foundP, double beta, double lambda);

		/*!
		*
		**/
		double DoEstimateQ(const ResourcePredication &predication, double *founds, double *weights, int order);

		/*!
		*
		**/
		double DoGetTheLeastSquare(const ResourcePredication &predication, double curBeta, double curLambda);

		/*!
		* directly find the matched beta and lambda parameters
		**/
		void DoCalculateParameterWithContour(ResourcePredication &predication);

		/*!
		* geometric method 
		**/
		void DoCalculateParameterWithNelder(ResourcePredication &predication);

		/*!
		*
		**/
		void RearrayPoints(double *betas, double *lamdas, double *leasts);

	private:
		// input & output parameter
		ResourcePredication m_predication;
	public:
		string m_remark;
		std::vector<string> m_gridstringvector;
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