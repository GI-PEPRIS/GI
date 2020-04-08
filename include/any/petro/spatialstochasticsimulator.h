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
#ifndef __ANYPETRO_SPATIAL_STOCHASTIC_SIMULATOR_H__
#define __ANYPETRO_SPATIAL_STOCHASTIC_SIMULATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"

// refer to its parent
#include "accumulationassessor.h"

// refer to geometry basic
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to anyaccessor
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// refer to histogram
#include "any/math/histogramdistribution.h"
#include "any/math/quickfft.h"
using namespace AnyMath;

// refer to contour 
#include "any/vis/anycontour.h"
using namespace AnyVis;

// refer to boost share_ptr
#include "boost/smart_ptr.hpp"
using namespace boost;

#include "any/base/agm/reflection.hpp"
using namespace agm::reflection;

//
namespace AnyPetro
{
	/*!
	* algothims from excellent work shared by Prof. Chen of GSC
	**/
	class ANYPETRO_CLASS CSpatialStochasticSimulator : public CAccumulationAssessor
	{
	public:
			
		/*!
		*2015/4/27: change to relfection mode, for adding member to data base without changing load/commit codes 
		**/
		struct WellRecord
		{
			CLASS(WellRecord, agm::reflection::NullClass);
			
			//
			FIELD2(public,long, m_propertyid);
			FIELD2(public,long, m_elementid);

			FIELD2(public,long, m_idx);
			FIELD2(public,string, m_name);
			FIELD2(public,bool, m_ishc);
			FIELD2(public,double, m_x);
			FIELD2(public,double, m_y);
			FIELD2(public,double, m_grossthickness);
			FIELD2(public,double, m_netthickness);
			FIELD2(public,double, m_porosity);
			FIELD2(public,double, m_saturation);
			FIELD2(public,double, m_netgross);
			FIELD2(public,double, m_capthickness);
			FIELD2(public,double, m_uplift);
			FIELD2(public,double, m_presuregradient);
			FIELD2(public,double, m_salinitygradient);
			FIELD2(public,double, m_structure);
			FIELD2(public,double, m_structureresiduals);
			
			// MD
			FIELD2(public,double, m_md);
			FIELD2(public,double, m_risk); // from MD, for geological model
			
			// for resource model
			FIELD2(public,double, m_resource); // for resource model as persistence field
			FIELD2(public,double, m_predication); // for resource model as temporary value

			//2015/6/30:newly added, used in Resource Abundance model
			FIELD2(public,double, m_sourcerockthickness);
			FIELD2(public,double, m_toccontent);
			FIELD2(public,double, m_romaturity);
			FIELD2(public,double, m_absorbedGas);
			FIELD2(public,double, m_dailyProduction);
			
			//2015/6/30:newly added, not used in Resource Abundance model
			FIELD2(public,string, m_organicType);
			FIELD2(public,double, m_recovery);
			FIELD2(public,double, m_wellReserves);
			FIELD2(public,double, m_resourceAbundance);
			FIELD2(public,double, m_mineralComponents);

			//2017/3/15: add 'forg'
			FIELD2(public,double, m_forg);

			// for performance issue
			bool m_isCalculated;
			long m_geometryid;

			/*!
			*
			**/
			WellRecord()
			{
				m_propertyid = 0;
				m_elementid = 0;
				
				m_idx = 0;
				m_name = "";
				m_ishc = 0;
				m_x = 0.;
				m_y = 0.;
				m_grossthickness = 0.;
				m_netthickness = 0.;
				m_porosity = 0.;
				m_saturation = 0.;
				m_netgross = 0.;
				m_capthickness = 0.;
				m_uplift = 0.;
				m_presuregradient = 0.;
				m_salinitygradient = 0.;
				m_structure = 0.;
				m_structureresiduals = 0.;
				m_resource = 0.;
				m_predication = 0.;
				m_md = 0.;
				m_risk = 0.;

				//2015/6/30
				m_sourcerockthickness = 0.;
				m_toccontent = 0.;
				m_romaturity = 0.;
				m_absorbedGas = 0.;
				m_dailyProduction = 0.;
				m_organicType = "";
				m_recovery = 0.;
				m_wellReserves = 0.;
				m_resourceAbundance = 0.;
				m_mineralComponents = 0.;

				//
				m_geometryid = 0;
				m_isCalculated = false;

				//2017/3/15: add 'forg'
				m_forg = 0.;

			}
		};
		typedef std::vector<WellRecord> WellVector;
		typedef WellVector::iterator well_itr;
		typedef WellVector::const_iterator well_citr;

		/*!
		*
		**/
		struct VariableProbability
		{
			double m_theta_x;
			double m_theta_y;
			double m_pHC;
			double m_pDry;
			double m_favorability;

			/*!
			*
			**/
			VariableProbability() : m_theta_x(0.), m_theta_y(0.), m_pHC(0.), m_pDry(0.), m_favorability(0.)
			{

			}
		};
		typedef std::map<string, VariableProbability> ProbabilityMap;
		typedef ProbabilityMap::iterator prob_itr;
		typedef ProbabilityMap::const_iterator prob_citr;

		// nuclear curve against differernt geological variable
		struct VariableCurve
		{
			//
			CHistogramDistribution *m_mix;
			CHistogramDistribution *m_favor;
			CHistogramDistribution *m_unfavor;

			/*!
			*
			**/
			VariableCurve() : m_mix(0), m_favor(0), m_unfavor(0)
			{
			}

			/*!
			*
			**/
			~VariableCurve()
			{
				if(m_mix)
				{
					delete m_mix;
					m_mix=NULL;
				}

				if(m_favor)
				{
					delete m_favor;
					m_favor=NULL;
				}

				if(m_unfavor)
				{
					delete m_unfavor;
					m_unfavor=NULL;
				}
			}

			VariableCurve(const VariableCurve& other)
			{
				*this = other;
			}
			const VariableCurve &operator=(const VariableCurve &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_mix=other.m_mix;
				m_favor=other.m_favor;
				m_unfavor=other.m_unfavor;
				return *this;
			}


		};
		typedef std::map<string, VariableCurve*> CurveMap;
		typedef CurveMap::iterator curve_itr;
		typedef CurveMap::const_iterator curve_citr;

		/*!
		*
		**/
		struct FractalParameter
		{
			// fractal coefficients
			double m_theta;
			double m_C;
			double m_H;
			double m_sigma;
			//parameters in anIsotropy mode
			double m_a;
			double m_b;
			double m_fai;


			bool m_isIsotropy;
			bool m_isRandomPhase;
			long m_simulations;
			long m_iterations;		
			int m_rows;
			int m_cols;
			int m_orirows;
			int m_oricols;
			double m_quantile;
			/*!
			*
			**/
			FractalParameter() : m_iterations(30),m_simulations(20),m_quantile(0),m_rows(20),m_cols(20),m_theta(0.), m_C(0.), m_H(0.), m_sigma(0.), m_a(0.), m_b(0.), m_fai(0.), m_isIsotropy(true), m_isRandomPhase(false),m_orirows(0),m_oricols(0)
			{
			}

			/*!
			*
			**/
			FractalParameter(const FractalParameter &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const FractalParameter &operator=(const FractalParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_theta = other.m_theta;
				m_C = other.m_C;
				m_H = other.m_H;
				m_sigma = other.m_sigma;
				m_a = other.m_a;
				m_b = other.m_b;
				m_fai = other.m_fai;
				m_isIsotropy = other.m_isIsotropy;
				m_isRandomPhase = other.m_isRandomPhase;
				m_iterations=other.m_iterations;
				m_rows=other.m_rows;
				m_cols=other.m_cols;
				m_simulations=other.m_simulations;
				m_quantile=other.m_quantile;
				m_oricols=other.m_oricols;
				m_orirows=other.m_orirows;
				return *this;
			}

			/*!
			*
			**/
			void FromParameterString(const string &parameter)
			{
				CAnyTokenString curToken;
				curToken.SetToken("#");
				int count = curToken.Trim(parameter.c_str(), parameter.size());

				m_isIsotropy = ::atoi(curToken.GetAt(0));
				m_isRandomPhase = ::atoi(curToken.GetAt(1));
				m_iterations = ::atoi(curToken.GetAt(2));
				m_orirows = ::atoi(curToken.GetAt(3));
				m_oricols = ::atoi(curToken.GetAt(4));
				m_simulations = ::atoi(curToken.GetAt(5));
				m_quantile = ::atof(curToken.GetAt(6));
			}

			/*!
			*
			**/
			string ToParameterString()
			{
				char parameter[512] = "";
				::sprintf(parameter, "%d#%d#%d#%d#%d#%d#%.2f#", m_isIsotropy, m_isRandomPhase, m_iterations, m_orirows,m_oricols,m_simulations,m_quantile);
				string str = parameter;

				
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
		CSpatialStochasticSimulator(CAccumulationElement *curElement);

		/*!
		*
		**/
		~CSpatialStochasticSimulator();

	public:
		//
		// overiding functions
		//
		/*!
		*
		**/
		void Load();

		/*!
		*
		**/
		unsigned int Commit(bool isDeleted = false);
		
		//
		// geological model, namely, risk evaluation given to spatial position
		//
		/*!
		*
		**/
		bool PrepareGeologicalModel();

		/*!
		*
		**/
		void ClearGeologicalModel();

		/*!
		*
		**/
		 VariableCurve* GetVariableCurve(const string &name,bool& isAbnormalData);

		/*!
		*
		**/
		const VariableProbability &GetVariableFavorability(const string &name);

		/*!
		*
		**/
		void EraseGeologicalVariable(const string &name);

		/*!
		* Mahalanobis Distance
		**/
		void MakeMD();

		/*!
		*
		**/
		const WellVector &GetWellRisk();

		//
		// for resource model
		//
		/*!
		*
		**/
		bool PrepareResourceModel(CAnyContour *hcMap, CAnyContour *geoMap, int iterations);

		/*!
		*
		**/
		void ClearResourceModel();

		/*!
		*
		**/
		void GetInitialMap();

		/*!
		*
		**/
		bool MakeSimulation(/*int iterations, */FractalParameter &fractal, CAnyFunctor &progress);

		/*!
		* for phase random situation
		**/
		bool MakeSimulationRdm(/*int iterations, */FractalParameter &fractal, CAnyFunctor &progress);

		/*!
		*
		**/
		void GetPowerMap(std::vector<CGeoPoint<double> > &samples);

		/*!
		*
		**/
		void GetQuantileMap(double probability, std::vector<CGeoPoint<double> > &samples);

		/*!
		* linear regression for getting m_C & m_H
		**/
		void GetIsotropyCoefficient(std::vector<CGeoPoint<double> > &samples, int &number);

		/*!
		*
		**/
		void GetAnIsotropyCoefficient(std::vector<CGeoPoint<double> > &samples, int &number, bool isAAxis, int angle);

		/*!
		*
		**/
		bool OnCommitWellData();
	public:
		//
		//
		//
		/*!
		*
		**/
		static void LoadWellData(WellVector &wells);
		/*!
		*
		**/
		static void DoLoadWellRecord(CAnyAccessor &accessor, WellVector &wells);
	private:
		//
		// for generation of geological model
		//
		/*!
		*
		**/
		void DoGetSamples(const string &name, std::vector<CGeoPoint<double> > &samples, bool isHC);

		/*!
		*
		**/
		double DoGetSampleValue(const string &name, well_citr &itr);

		/*!
		*
		**/
		bool isFavor(std::vector<CGeoPoint<double> >favors, std::vector<CGeoPoint<double> >unfavors, double favorMax, double unfavorMax, int& first, int& fourth);

		/*!
		*
		**/
		void findCross(std::vector<CGeoPoint<double> >leftCurve, std::vector<CGeoPoint<double> >rightCurve, int first, int fourth, VariableProbability& probability);

		/*!
		*
		**/
		void DoCalcDistance(/*bool isHC*/);

		/*!
		*
		**/
		void DoSetDistanceHistogram(bool isHC);

		/*!
		*
		**/
		static bool CompareWellHC(const WellRecord &first, const WellRecord &second);

		//
		// for resource model
		//
		/*!
		*
		**/
		void DoMakeResourceModelFFT();

		/*!
		*
		**/
		void DoMakeGeologicalModelFFT();

		/*!
		* 
		**/
		void DoCalculateSpectralSynthesis(CQuickFFT &gpmap, std::vector<double> &gausses, bool isPhaseRandom = false);

		/*!
		*
		**/
		bool IsObjectApproximation();

		/*!
		*
		**/
		bool IsObjectApproximationRdm(int *probability);

		/*!
		*
		**/
		void DoInterpolatePredication(std::vector<CGeoPoint<double> > &pts, int curRow, int curCol);

		/*!
		*
		**/
		void DoAdjustGeologicalModel();

		/*!
		*
		**/
		void DoGetNearestWellResource(const CGeoPoint<double> &pt, const std::vector<WellRecord> &sels, double &value);

		/*!
		*
		**/
		void DoExtractEnvolope(std::vector<CGeoPoint<double> > &pts, CGeoRect<double> &gridExtent);

		/*!
		*
		**/
		double DoGetQuantileValue(double probability, int row, int col);

		/*!
		*
		**/
		static int CompareResourceValue(const void *a , const void *b);

	public:
		// basic data
		WellVector m_wells;
		int m_hcNumber;
		int m_dryNumber;
		bool m_isInit;
		// kinds of results against different geological variables
		ProbabilityMap m_probabilities;
		CurveMap m_curves;
		// MD histogram
		CHistogramDistribution *m_hcDistribution;
		CHistogramDistribution *m_dryDistribution;

		// resource model, original resource map
		CAnyContour *m_hcMap;
		CQuickFFT m_oamap;

		// geological model
		CAnyContour *m_geoMap; 
		CQuickFFT m_gpmap;

		// fractial map
		CQuickFFT m_mfamap;
		// predicated and adjusted map given samples
		CQuickFFT m_mfhcmap; // FHCMAP and MFHCMAP

		// iterations
		//long m_iterations;		
		// predication histograms driven by grid tracing mechanism hidden above contour
		//int m_rows;
		//int m_cols;
		int m_oldCount; // resource's col count used when free memory
		double **m_resources;
		CGeoRect<double> m_extent;
		double m_minResource;
		double m_maxResource;

		// fractal parameter
		FractalParameter m_fractal;

		//adjust m_theta(threshold) automatically
		double m_obj;

		//
		std::vector<CGeoPoint<double>> wellToGridPoint;

	public:
		// which well field to play
		static std::vector<string> m_variableNames;
		string m_remark;
	};
}

#endif