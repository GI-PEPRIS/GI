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
#ifndef __ANYPORTFOLIO_GENETIC_SOLUTION_H__
#define __ANYPORTFOLIO_GENETIC_SOLUTION_H__

// refer to EXPORT & IMPORT
#include "anyportfolio.h"

// refer core algorithm
#include "any/math/gene.h"
using namespace AnyMath;

// refer to PORT
#include "any/base/anyport.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

// refer to its parent as one of accumulation activities
#include "any/petro/accumulationassessor.h"
using namespace AnyPetro;

// namespace
namespace AnyPortfolio
{
	/*!
	* as ST_Value_Portfolio activity
	**/
	class ANYPORTFOLIO_CLASS CAnyGeneticSolutionGenerator : public CAccumulationAssessor
	{
	public:
		enum GPTYPE
		{
			INNERPOINT=0,
			OUTERPOINT,
			KPOINT
		};

		/*!
		* a_repository
		**/
		struct GraphPoint
		{
			// object value
			double m_objVal;
			// real object value
			double m_RealNPVVal;
			// npv value
			double m_colVal;
			// point type
			int m_type;
			
			std::vector<int> m_projectIndex;
			std::vector<double> m_projectweight;

			/*!
			*
			**/
			GraphPoint()
			{
				m_objVal = 0;	
				m_colVal = 0.;
				m_type = 0.;
				m_RealNPVVal=0.;
				
			}

			/*!
			*
			**/
			const GraphPoint &operator=(const GraphPoint &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_objVal = other.m_objVal;	
				m_colVal = other.m_colVal;
				m_RealNPVVal=other.m_RealNPVVal;
				m_type = other.m_type;
				m_projectIndex.clear();
				m_projectweight.clear();
				m_projectIndex=other.m_projectIndex;
				m_projectweight=other.m_projectweight;
				return *this;
			}
		};
		typedef std::vector<GraphPoint> GraphPointVector;
		typedef GraphPointVector::iterator gp_itr;
		typedef GraphPointVector::const_iterator gp_citr;

		/*!
		*
		**/
		struct GeneticParameter
		{
			int m_iterationNumber;
			int m_groups;				// nxp0
			int m_candidates;			// m_n
			int m_constraints;			// m_m
			int m_stepNum;
		};

		/*!
		* a_repository
		**/
		struct RepositoryRecord
		{
			// to get element name
			long m_elementid;	

			// get content by element object
			string m_matureType;
			string m_depthType;
			string m_trapType;
			string m_resourceType;
			string m_fieldType;

			// exploration investment
			double m_expInvestment;
			// development investment
			double m_devInvestment;
			// resource value in P50
			double m_resource;
			// economic value in P50
			double m_npv;
			// geological risk
			double m_geoRisk;
			// economic risk
			double m_ecoRisk;
			// engineering risk
			double m_engRisk;
			// minimum investment weight 
			double m_minWeight;
			// desired or return investment weight
			double m_rtWeight;
			// max investment weight
			double m_maxWeight;

			//2014/12/16:exp
			double m_exp;
			//2014/12/16:rov
			double m_rov;

			/*!
			*
			**/
			RepositoryRecord()
			{
				m_elementid = 0;	

				//
				m_matureType = "";
				m_depthType = "";
				m_trapType = "";
				m_resourceType = "";
				m_fieldType = "";

				//
				m_expInvestment = 0.;
				m_devInvestment = 0.;
				m_resource = 0.;
				m_npv = 0.;
				m_geoRisk = 0.;
				m_ecoRisk = 0.;
				m_engRisk = 0.;
				m_minWeight = 0.;
				m_rtWeight = 0.;
				m_maxWeight = 1.;

				//
				m_exp = 0.;
				m_rov = 0.;
			}

			/*!
			*
			**/
			const RepositoryRecord &operator=(const RepositoryRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_elementid = other.m_elementid;	

				//
				m_matureType = other.m_matureType;
				m_depthType = other.m_depthType;
				m_trapType = other.m_trapType;
				m_resourceType = other.m_resourceType;
				m_fieldType = other.m_fieldType;

				//
				m_expInvestment = other.m_expInvestment;
				m_devInvestment = other.m_devInvestment;
				m_resource = other.m_resource;
				m_npv = other.m_npv;
				m_geoRisk = other.m_geoRisk;
				m_ecoRisk = other.m_ecoRisk;
				m_engRisk = other.m_engRisk;
				m_minWeight = other.m_minWeight;
				m_rtWeight = other.m_rtWeight;
				m_maxWeight = other.m_maxWeight;

				//
				m_exp = other.m_exp;
				m_rov = other.m_rov;

				return *this;
			}
		};
		typedef std::vector<RepositoryRecord> CandidateVector;
		typedef CandidateVector::iterator can_itr;
		typedef CandidateVector::const_iterator can_citr;

		/*!
		*
		**/
		struct ConstraintVariable
		{
			string m_name;
			std::vector<double> m_samples;
			bool m_isGreater;
			bool m_isObjective;
			double m_limits;		// constaint value

			/*!
			*
			**/
			ConstraintVariable() : m_name(""), m_isGreater(true), m_isObjective(false), m_limits(0.)
			{
			}
			ConstraintVariable(const ConstraintVariable &other)
			{
				*this = other;
			}
			const ConstraintVariable &operator=(const ConstraintVariable&other)
			{
				m_name = other.m_name;
				m_samples.assign(other.m_samples.begin(),other.m_samples.end());
				m_isGreater = other.m_isGreater;
				m_isObjective = other.m_isObjective;
				m_limits = other.m_limits;

				return *this;
			}
		};
		typedef std::vector<ConstraintVariable> VariableVector;
		typedef VariableVector::iterator var_itr;
		typedef VariableVector::const_iterator var_citr;

		/*!
		*
		**/
		enum SpecialConstraintType
		{
			CCT_Unknown = -1,
			CCT_Mature,				// 新、老区
			CCT_Depth,				// 深度类型
			CCT_Trap,
			CCT_Resource,			// 油气资源类型
			CCT_Field,					// 不同区域或油田
			CCT_Max
		};

		/*!
		*
		**/
		struct SpecialConstraintVariable
		{
			enum OPTYPE
			{
				GREATEREQUAL=0,
				LESSEQUAL,
				EQUAL
			};

			int m_type;	//
			string m_which;
			int m_optype;//>= = <=
			double m_scale; // or number

			SpecialConstraintVariable()
			{
				m_optype=GREATEREQUAL;
				m_scale=0.0;
			}
		};
		typedef std::vector<SpecialConstraintVariable> SpecialConstraintVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGeneticSolutionGenerator();

		/*!
		*
		**/
		~CAnyGeneticSolutionGenerator();

	public:
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
		unsigned int Commit(bool isActivity = true);

		//
		// select candidates from i_el_evaluation_view
		//
		/*!
		*
		**/
		void AddCandidate(RepositoryRecord &candidate, bool isSort = false);

		/*!
		*
		**/
		void RemoveCandidate(unsigned long idx);

		/*!
		*
		**/
		void ClearCandidates();

		/*!
		*
		**/
		int GetCandidateCount();

		/*!
		*
		**/
		const RepositoryRecord &GetCandidate(int order);

		/*!
		*
		**/
		const RepositoryRecord &FindCandidate(long elementIdx);

		/*!
		*
		**/
		static bool CompareCandidateElementIdx(const RepositoryRecord &first, const RepositoryRecord &second)
		{
			return first.m_elementid < second.m_elementid;
		}

		//
		//
		//
		/*!
		*
		**/
		void SetParameter(const GeneticParameter &parameter);

		/*!
		*
		**/
		const GeneticParameter &GetParameter();

		/*!
		*
		**/
		void UpdateVariable(const ConstraintVariable &variable);

		/*!
		*2015/2/5
		**/
		void ClearVariable();

		/*!
		*
		**/
		bool GetVariable(ConstraintVariable &variable);

		//
		//special constrinants
		//
		/*!
		*
		**/
		void SetSpecialConstriantVariable(SpecialConstraintVector &constraints)
		{
			//assert(constraints.size());
			m_specialConstraints.clear();
			m_specialConstraints.assign(constraints.begin(), constraints.end());
		}

		/*!
		*
		**/
		SpecialConstraintVector &GetSpecialConstriantVariable()
		{
			return m_specialConstraints;
		}

		/*!
		*
		**/
		/*static */bool CheckSpecialConstrinatVariable(double *scales, std::vector<int> indexVec, int number);

		//
		//
		//
		/*!
		*    return value: 1  success
		                   0  no solutions!
		**/
		int MakePortfolio(CAnyFunctor &progress);

		/*!
		*
		**/
		bool PrepareMakePortfolio();

		/*!
		*	
		**/
		void GetInnerPoints(GraphPointVector& gpv);

		/*!
		*
		**/
		void GetOuterPoints(GraphPointVector& gpv);

		/*!
		*
		**/
		void GetSlopPoint(GraphPoint& gp);

		/*!
		*    Corresponding to NPV
		**/
		void GetYaxisRange(double& minv,double& maxv);

		/*!
		*    Corresponding to Risk
		**/
		void GetXaxisRange(double& minv,double& maxv);
	
	private:
		/*!
		*2015/4/30
		**/
		static bool CompareObjectVal(const GraphPoint &pt1, const GraphPoint &pt2);

	protected:
		// candidates 
		CandidateVector m_candidates;
		// straw class
		GENE m_generator;
		// 
		GeneticParameter m_parameter;
		//
		VariableVector m_variables;

		GraphPointVector m_graphInnerPoints;
		GraphPointVector m_graphOuterPoints;
		GraphPoint m_graphSlopePoint;

		double m_minY;
		double m_minX;
		double m_maxY;
		double m_maxX;

		//
		/*static */SpecialConstraintVector m_specialConstraints;

	public:
		boost::function<void(VariableVector&,GENE&)> m_geneConstraintFunction;
	};
}
#endif