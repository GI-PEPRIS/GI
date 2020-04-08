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
#ifndef __ANYPETRO_ANALOG_PREDICATOR_H__
#define __ANYPETRO_ANALOG_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

#include "accumulationfactor.h"
#include "accumulationelement.h"
// refer to its parent
#include "accumulationassessor.h"

#include "accumulationpropertyrecord.h"
#include "accumulationpropertyset.h"
#include "riskquickscore.h"

// refer to stl
#include "any/base/anystl.h"

// refer to cgeopoint
#include "any/base/anygeom.h"
#include "any/base/anytokenstring.h"
using namespace AnyBase;

// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;

//#include <limits>

namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CAnalogPredicator : public CAccumulationAssessor
	{
	public:
		typedef std::vector<double> ScoreVector;
		typedef std::vector<string> QualiTypeVector;
		

		//factors maybe qualitative or quantitative
		struct ElementVector
		{
			int m_elementID;
			ScoreVector m_scoreNodes;
			QualiTypeVector m_qualiTypeNodes;

			void clear()
			{
				m_scoreNodes.clear();
				m_qualiTypeNodes.clear();
			}
		};

		//cluster
		struct Centroid
		{
			ElementVector m_meanNode;
			std::vector<int> m_elementIndex;
		};

		struct EleWeights
		{
			CAccumulationElement *m_element;
			double m_angindex;
			double m_weight;
		};

		/*!
		*
		**/
		struct ResourcePredication
		{
			double m_avgQ;
			double m_maxQ;
			double m_minQ;

			double m_avgN;
			double m_maxN;
			double m_minN;
			int m_clusterNum;
			int m_iterationTimes;
			int m_neighborNum;
			int m_datatype;
			int m_methodtype;
			bool m_isFirstLevel;

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
				;
			}

			ResourcePredication(const ResourcePredication &other)
			{
				m_avgQ =other.m_avgQ;
				m_maxQ =other.m_maxQ;
				m_minQ = other.m_minQ;
				m_avgN = other.m_avgN;
				m_maxN = other.m_maxN;
				m_minN = other.m_minN;
				m_clusterNum=other.m_clusterNum;
				m_iterationTimes=other.m_iterationTimes;
				m_neighborNum=other.m_neighborNum;
				m_datatype=other.m_datatype;
				m_methodtype=other.m_methodtype;
				m_isFirstLevel=other.m_isFirstLevel;
			}
			void Reset()
			{
				m_avgQ = 0.;
				m_maxQ = 0.;
				m_minQ = 0.;
				m_avgN = 0.;
				m_maxN = 0.;
				m_minN = 0.;
				m_clusterNum=2;
				m_iterationTimes=100;
				m_neighborNum=5;
				m_datatype=0;
				m_methodtype=0;
				m_isFirstLevel=false;

			}
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

				m_avgQ = other.m_avgQ;
				m_maxQ = other.m_maxQ;
				m_minQ = other.m_minQ;
				m_avgN = other.m_avgN;
				m_maxN = other.m_maxN;
				m_minN = other.m_minN;
				m_clusterNum=other.m_clusterNum;
				m_iterationTimes=other.m_iterationTimes;
				m_neighborNum=other.m_neighborNum;
				m_datatype=other.m_datatype;
				m_methodtype=other.m_methodtype;
				m_isFirstLevel=other.m_isFirstLevel;
				return *this;
			}
			bool IsValid() const
			{
				if(!m_minN ||
					!m_minQ ||
					!m_maxN || 
					!m_avgN || 
					!m_maxQ || 
					!m_avgQ)
				{
					return false;
				}

				return true;
			}
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");
				int count = curToken.Trim(parameter.c_str(), parameter.size());

				m_clusterNum = ::atoi(curToken.GetAt(0));
				m_iterationTimes = ::atoi(curToken.GetAt(1));
				m_neighborNum = ::atof(curToken.GetAt(2));
				m_datatype = ::atoi(curToken.GetAt(3));
				m_methodtype = ::atoi(curToken.GetAt(4));
				m_isFirstLevel = ::atoi(curToken.GetAt(5));
			}
			string ToParameterString()
			{
				//m_groups = m_regressionLines ? m_groups : 0;
				char parameter[512] = "";
				::sprintf(parameter, "%d#%d#%d#%d#%d#%d#", m_clusterNum, m_iterationTimes, m_neighborNum, m_datatype,m_methodtype,m_isFirstLevel);
				string str = parameter;
				return str;
			}
		};

	public:
		/*!
		*
		**/
		CAnalogPredicator(CAccumulationElement *curElement/*,std::vector<CAccumulationElement *>elementvec,int clusternum=2,int iterationTime=100,int knnnum=5,bool isFirstLevel=false*/);
		virtual ~CAnalogPredicator();

	public:
		/*!
		*
		**/
		unsigned int Commit(bool isActivity = true);
		bool MakePredication(ResourcePredication &predication,std::vector<CAccumulationElement *> &memVec,std::vector<double>& resultVec);

		/*!
		*
		**/
		void EstimateResourceByKmeanScoringData(std::vector<double> &result); // Estimate Resource by kmeans using scoring data(from 0 to 1 assigned by experts).
		void EstimateResourceByKmeanOriginalData(std::vector<double> &result); //  Estimate Resource by kmeans using original data.

		/*!
		*  
		**/
		void EstimateResourceByKNNOriginalData(std::vector<double> &result); // Estimate Resource by KNN using original data.
		void EstimateResourceByKNNScoringData(std::vector<double> &result); // Estimate Resource by KNN using original data.
		void EstimateResourceByExpert(std::vector<double> &result); //Estimate Resource by KNN using original data.

		/*!
		*
		**/
		void GetPointInSameCluster(int *points,int &length);
		void GetPointOfNeighbor(int *points,int &length);
		double GetArea( CAccumulationElement *itr );
		void GetNumber( CAccumulationElement *itr ,std::vector<double>& numberVec);

	protected:
		//
		//
		//
		/*!
		*  
		**/
		virtual void LoadFactorScoringData(CAccumulationElement *curElement,ElementVector &eleVec);
		virtual void LoadFactorOriginalData(CAccumulationElement *curElement,ElementVector &eleVec);
		virtual void CalResourceByCluster(std::vector<double>& result); // Calculate an element's resource by the mean resource of the cluster to which the element belongs 
		virtual void InitFactorScoreRange(); // get score range used to normalization

		//
		//
		//
		/*!
		*  
		**/
		bool KMean();
		void KNN();

		double CalNorm2Distance(ElementVector &s1,ElementVector &s2); // euler distance for quantitative factors and 0-1 distance for qualitative factors
		double CalMahalanobisDistance(ElementVector &s1,ElementVector &s2); //  Mahalanobis distance for quantitative factors and 0-1 distance for qualitative factors
		bool CalCovMatrix(); // calculate covariance matrix

		void ReCalMean(); // calculate mean for each cluster again
		void AssignToMean(); //   assign every element to the nearest mean

		void ResetCentroidCollection(); //set every centroid's element list to zero
		bool CheckStoppingCriteria(); //check whether to stop iteration
		double GetTotalLoss(); //  taotal loss means the sum of distance between all the nodes to their nearest center.

		void Reset();
		void RandomInitKMeans(); // random select 10 groups of init means of every cluster and choose the group with lowest loss 

		void CalResourceByKNN(std::vector<double>& result); // Calculate an element's resource by the average of the K nearest neighbor
		int MatrixInverseGS(double **rhs,double **m,int stRank);
		int GetOverAllType(int elementtype);
private:
		
		CAccumulationElement::FactorVector m_factorVector;
		CAccumulationElement* m_element;
		
		// collection of element with factors 
		std::vector<ElementVector> m_elementCollection;
		//k cluster correspponds to k centroid collection
		std::vector<Centroid> m_centroidCollection;
		//last k clusters to compare with the new clusters to determine whether to stop iteration
		std::vector<Centroid> m_lastCentroidCollection;
		//CRiskQuickScore is used to access r_risk_factor table to get the range of each factor
		// to implement normalization
		CRiskQuickScore &m_strategy;
		std::map<int,double> m_factorScoreRangeMap;
		double* m_sampleMean;
		double** m_covMatrix;
		double** m_covInverseMatrix;
		int m_dim;
		//k neighbor collection
		std::vector<ElementVector> m_neighborCollection;
		std::vector<int> m_neighborIndex;
public:	
		std::vector<CAccumulationElement *> m_elementVector;
		// parameters
		ResourcePredication m_predication;

		std::vector<EleWeights> m_EleWeights;
		int m_buildtype;
		int m_curparanum;
		
	};
}

#endif