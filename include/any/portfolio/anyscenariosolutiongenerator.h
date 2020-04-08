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
#ifndef __ANYPORTFOLIO_MONTECARLO_SOLUTION_H__
#define __ANYPORTFOLIO_MONTECARLO_SOLUTION_H__

// refer to EXPORT & IMPORT
#include "anyportfolio.h"

// refer to its parent as one of accumulation activities
#include "any/petro/accumulationassessor.h"
using namespace AnyPetro;

#include "any/thread/jtc.h"
//// random generator
#include "any/math/anyrandomgenerator.h"
#include "any/math/anygibssampler.h"
using namespace AnyMath;

#include "anygeneticsolutiongenerator.h"
// refer to functor
#include "any/base/anymediator.h"
using namespace AnyBase;


namespace AnyPortfolio
{
	// forward class
	class CAnyScenarioNPV;

	/*!
	*
	**/
	class ANYPORTFOLIO_CLASS CAnyScenarioSolutionGenerator : public CAnyGeneticSolutionGenerator
	{
	public:
		
		//
		typedef std::vector<CAnyScenarioNPV *> ProjectVector;
		typedef ProjectVector::iterator prj_itr;
		typedef ProjectVector::const_iterator prj_citr;

		//
		struct ScenarioPortfolio
		{
			//
			long m_idx;

			//
			double m_slope;

			// optimization out, x means RISK, y means NPV
			CGeoPoint<double> m_pt;
			// projects selected
			std::vector<string> m_projects;
			
			//2015/4/14:projects related weight,invest...
			std::vector<CAnyScenarioNPV *> m_npvs;
		};
		typedef std::vector<ScenarioPortfolio> PortfolioGroup;
		typedef PortfolioGroup::iterator port_itr;
		typedef PortfolioGroup::const_iterator port_citr;

		// RISK kind
		enum RiskType
		{
			RT_Variance,
			RT_Semi_Variance,
			RT_VaR,
			RT_CVaR
		};


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

		// multithread's task
		class ScenariaoSolutionTask: public CAnySignalTask<void()>,public JTCMonitor
		{
		public:
			ScenariaoSolutionTask(int taskcount,int m_index,CAnyScenarioSolutionGenerator* parent,PortfolioGroup** sample,\
				CAnyRandomGenerator::RandomVector& groupNumber, bool isGibs);
			~ScenariaoSolutionTask();
			void DoExecuteTask();
		public:
			int m_index;
			int m_taskcount;
			CAnyScenarioSolutionGenerator* m_parent;
			CAnyRandomGenerator::RandomVector m_groupNumber;
			PortfolioGroup* m_samples;
			bool m_isGibs;
		};
		friend class ScenariaoSolutionTask;
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyScenarioSolutionGenerator();

		/*!
		*
		**/
		~CAnyScenarioSolutionGenerator();

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
		//
		//
		/*!
		*
		**/
		void AddProject(CAnyScenarioNPV *prj);

		/*!
		*
		**/
		void RemoveProject(const string &name);

		/*!
		*
		**/
		void RemoveAll();

		/*!
		*
		**/
		CAnyGibsSampler &GetGibsSampler()
		{
			return m_gibs;
		}

		//
		//
		//
		/*!
		*
		**/
		void MakePortfolioMT(int iterations, short riskType,CAnyFunctor &progress, bool isGibs = false);

		/*!
		*
		**/
		const PortfolioGroup &GetInnterSamples();

		/*!
		*
		**/
		const PortfolioGroup &GetFrontierSamples();


		/*!
		*
		**/
		bool Normalization(double &minX,double &maxX,double &minY,double &maxY);
	
		/*!
		*
		**/
		bool CalculateInnerOuterPoints();
		
		/*!
		*
		**/
		void UpdateVariable(const CAnyGeneticSolutionGenerator::ConstraintVariable &variable);

		/*!
		*2015/2/5
		**/
		void ClearVariable();

		/*!
		*
		**/
		bool CheckSpecialConstrinatVariable(int *scales, int number);


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

	private:
		//
		//
		//
		/*!
		*
		**/
		double DoGetVariance(const std::vector<double> &samples);
		bool DoGranhamScanning(PortfolioGroup& points, PortfolioGroup& closurePoints);
		static bool CompareGraham(const ScenarioPortfolio &a, const ScenarioPortfolio &b);
		static void GetFrontierBoundingPoint(PortfolioGroup& points, bool isExchange = true);
		static bool CompareSlope(const ScenarioPortfolio &a, const ScenarioPortfolio &b)
		{
			return a.m_slope > b.m_slope;
		}

		/*!
		*
		**/
		static double cross(const ScenarioPortfolio &a, const ScenarioPortfolio &b,const ScenarioPortfolio &c)
		{
			ScenarioPortfolio u,v;
			u.m_pt.m_x=b.m_pt.m_x-a.m_pt.m_x;
			u.m_pt.m_y=b.m_pt.m_y-a.m_pt.m_y;
			v.m_pt.m_x=c.m_pt.m_x-a.m_pt.m_x;
			v.m_pt.m_y=c.m_pt.m_y-a.m_pt.m_y;
			return v.m_pt.m_x*u.m_pt.m_y-u.m_pt.m_x*v.m_pt.m_y;
		}
		/*!
		*
		**/
		static bool Getdistance(const ScenarioPortfolio &a, const ScenarioPortfolio &b)
		{
			return (b.m_pt.m_x-a.m_pt.m_x)*(b.m_pt.m_x-a.m_pt.m_x)+(b.m_pt.m_y-a.m_pt.m_y)*(b.m_pt.m_y-a.m_pt.m_y);
		}

	private:
		// all points
		ProjectVector m_projects;

		// innerior points excluding frontier points
		PortfolioGroup m_samples;

		// efficient frontier, frontier points
		PortfolioGroup m_frontiers;

		// iterations
		int m_iterations;

		// sequences
		std::vector<prj_itr> m_sequences;

		// risk type
		short m_riskType;

		//normalization factor
		double m_scaleFactorMinX;
		double m_scaleFactorMaxX;
		double m_scaleFactorMinY;
		double m_scaleFactorMaxY;

		//task count for multithreads
		int m_taskcount;

		// sub sample set for each thread
		PortfolioGroup* m_subsamples;

		CAnyGeneticSolutionGenerator::VariableVector m_variables;
		SpecialConstraintVector m_specialConstraints;

		// given project dependence
		CAnyGibsSampler m_gibs;

		// granhamm
		static ScenarioPortfolio m_theLeftPt;
		static ScenarioPortfolio m_theTopPt;

		// seed
		static int m_seed;
	public:
		boost::function<bool(VariableVector&, ScenarioPortfolio &portfolio, double, double, double)> m_monConstraintFunction;
	};
}
#endif