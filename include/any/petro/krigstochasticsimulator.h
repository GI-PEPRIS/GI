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
#ifndef __ANYPETRO_EUR_KRIG_SIMULATOR_H__
#define __ANYPETRO_EUR_KRIG_SIMULATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"
#include "accumulationassessor.h"
#include "accumulationelement.h"
//
#include "any/math/anysequentialgausssimulator.h"
using namespace AnyMath;

#include "any/map/anyviewhook.h"
using namespace AnyMap;

#include "anypetrodata.h"
#include "any/base/anymediator.h"
using namespace AnyBase;

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CKrigStochasticSimulator : public CAccumulationAssessor,public CAnyObservable
	{
	public:
		//
		struct SimulationSamples
		{
			CGeoPoint<double> m_pos;
			std::vector<CGeoPoint<double> > m_samples; // z: eur, w: indicator
		};
		struct SimulationResource
		{
			int m_whichsimulation;
			double m_resource;

			SimulationResource() : m_whichsimulation(0), m_resource(0.)
			{
			}
			SimulationResource(const SimulationResource &other)
			{
				*this = other;
			}
			const SimulationResource &operator=(const SimulationResource &other)
			{
				if(this != &other)
				{
					m_whichsimulation = other.m_whichsimulation;
					m_resource = other.m_resource;
				}

				return *this;
			}
		};

		//
		struct KrigStochasticSimulation
		{
			string m_loglayername;
			string m_celllayername;
			double m_eurlimit;
			double m_drainagelimit;
			double m_cellsize;

			std::vector<CGeoPoint<double> > m_polygon;
			CGeoRect<double> m_bounding;
			std::vector<CGeoPoint<double> > m_indicators;
			
			bool   m_isostropic;
			double m_ellipseangle;
			double m_ellipsescale;
			int    m_locations;
			int    m_realizations;
			int    m_seed;

			CAnyViewHook *m_loglayer;
			CAnyViewHook *m_celllayer;

			//results
			double m_eurquantile;
			double m_eursum;

			//gauss &kring
			double m_kringsill;
			double m_kringrange;
			double m_kringnugget;
			bool   m_kringusesys;

			double m_gausssill;
			double m_gaussrange;
			double m_gaussnugget;
			bool   m_gaussusesys;

			KrigStochasticSimulation() 
			{
				m_loglayername="";
				m_celllayername="";
				m_eurlimit=0;
				m_drainagelimit=0;

				m_polygon.clear();
				m_indicators.clear();
				m_bounding.Empty();

				m_isostropic=0;
				m_ellipseangle=0.1;
				m_ellipsescale=0.1;
				m_locations=1;
				m_realizations=50;
				m_cellsize=0;
				m_seed=1999;
				
				m_loglayer=0;
				m_celllayer=0;

				m_eurquantile=0.5;
				m_eursum=0;

				m_kringsill		=0;
				m_kringrange	=0;	
				m_kringnugget	=0;
				m_kringusesys	=true;

				m_gausssill		=0;
				m_gaussrange	=0;
				m_gaussnugget	=0;
				m_gaussusesys	=true;
			}

			const KrigStochasticSimulation &operator=(const KrigStochasticSimulation &other)
			{
				//
				if(this == &other)
				{
					return *this;
				}

				m_loglayername   =	other.m_loglayername ;
				m_celllayername  =	other.m_celllayername;
				m_eurlimit       =	other.m_eurlimit     ;
				m_drainagelimit  =	other.m_drainagelimit;
				m_isostropic	 =	other.m_isostropic	 ;
				m_ellipseangle	 =	other.m_ellipseangle ;
				m_ellipsescale	 =	other.m_ellipsescale ;
				m_locations		 =	other.m_locations	 ; 
				m_realizations	 =	other.m_realizations ;
				m_seed			 =	other.m_seed		 ;
				m_cellsize		 =	other.m_cellsize	 ;		

				m_loglayer		 =	other.m_loglayer	 ;	
				m_celllayer		 =	other.m_celllayer	 ;	
				
				m_eurquantile	=	other.m_eurquantile	 ;
				m_eursum		=	other.m_eursum		 ;

				m_kringsill		=other.m_kringsill		 ;
				m_kringrange	=other.m_kringrange		 ;
				m_kringnugget	=other.m_kringnugget	 ;
				m_kringusesys	=other.m_kringusesys	 ;
														 ;
				m_gausssill		=other.m_gausssill		 ;
				m_gaussrange	=other.m_gaussrange		 ;
				m_gaussnugget	=other.m_gaussnugget	 ;
				m_gaussusesys	=other.m_gaussusesys	 ;

				m_bounding = other.m_bounding;
				m_polygon.clear();
				if (other.m_polygon.size())
				{
					m_polygon.assign(other.m_polygon.begin(),other.m_polygon.end());
				}
				m_indicators.clear();
				if (other.m_indicators.size())
				{
					m_indicators.assign(other.m_indicators.begin(),other.m_indicators.end());
				}
				//
				return *this;
			}

			void Release()
			{
				m_loglayername="";
				m_celllayername="";
				m_eurlimit=0;
				m_drainagelimit=0;

				m_polygon.clear();
				m_indicators.clear();

				m_isostropic=0;
				m_ellipseangle=0.1;
				m_ellipsescale=0.1;
				m_locations=10;
				m_realizations=10;
				m_cellsize=0;
				m_seed=1999;

				m_loglayer=0;
				m_celllayer=0;
				m_bounding.Empty();

				m_eurquantile=0.5;
				m_eursum=0;

				m_kringsill		=0;
				m_kringrange	=0;	
				m_kringnugget	=0;
				m_kringusesys	=true;

				m_gausssill		=0;
				m_gaussrange	=0;
				m_gaussnugget	=0;
				m_gaussusesys	=true;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CKrigStochasticSimulator(CAccumulationElement *curElement);
		~CKrigStochasticSimulator();

		void Notify(short type);
		void Register(CAnyObserver *oneObserver);
		void Update(int cur,int cur1,int cur1all,int cur2,int cur2all,string &msg);

	public:
		//
		//
		//
		/*!
		*
		**/
		//设置样本
		void SetSamples(const std::vector<CGeoPoint<double> > &samples);
		
		//实验变差
		void GetKrigSampleVariance(std::vector<CGeoPoint<double> >&variances,double tolerance = 1.);
		void SetKrigVariogramModel(short type, double sill, double range, double nugget)
		{
			m_krig.Fit_SetVariogramParameter(type, sill, range, nugget);//m_krig.SetVariogramModel(type, sill, range, nugget);
		}
		void GetKrigVariogramParameter(double &sill, double &range, double &nugget)
		{
			short kernel_type;
			m_krig.Fit_GetVariogramParameter(kernel_type, sill, range, nugget);//m_krig.GetVariogramParameter(sill, range, nugget);
		}
		//理论变差
		void GetKrigModelVariance(short type,std::vector<CGeoPoint<double> >&variances);
		void GetKrigModelVariance(short type,double sill, double range, double nugget, std::vector<CGeoPoint<double> >&variances);
		

		//实验变差
		void GetGaussSampleVariance(std::vector<CGeoPoint<double> >&variances, double tolerance = 1.);
		void SetGaussVariogramModel(short type, double sill, double range, double nugget)
		{
			m_gauss.Fit_SetVariogramParameter(type, sill, range, nugget);//m_gauss.SetVariogramModel(type, sill, range, nugget);
		}
		void GetGaussVariogramParameter(double &sill, double &range, double &nugget)
		{
			short kernel_type;
			m_gauss.Fit_GetVariogramParameter(kernel_type, sill, range, nugget);//m_gauss.GetVariogramParameter(sill, range, nugget);
		}
		//理论变差
		void GetGaussModelVariance(short type,std::vector<CGeoPoint<double> >&variances);
		void GetGaussModelVariance(short type,double sill, double range, double nugget, std::vector<CGeoPoint<double> >&variances);
		//
		//
		//
		/*!
		*
		**/
		void PrepareIndicator();
		void CreateCellLayer(CAnyViewHook *celllayer,string &name);
		void MakeSimulation();
		void GetSimulation(double quantile, double &potential, std::vector<CGeoPoint<double> > &eurs, bool islog = true);

		//
		KrigStochasticSimulation &GetTheSimulation()
		{
			return m_simulation;
		}

		void FormCommitParaString(string &parastring);
		bool GetParasFromString(string &parastring);
		unsigned int Commit(bool isDeleted = false);

	private:
		//
		void DoMakeIsostropicIndicator(int cur, double drainage, double eur);
		void DoMakeAnisostropicIndicator(int cur, double drainage, double eur);
		static bool CompareResourceSimulated(const SimulationResource& first, const SimulationResource &second)
		{
			return first.m_resource > second.m_resource;
		}
		SimulationResource DoGetResourceQuantile(double probability, std::vector<SimulationResource> &resources);

	public:
		//
		CAnyObserver *m_observer;
		CAccumulationElement *m_element;
		CAnySequentialGaussSimulator m_krig;
		CAnySequentialGaussSimulator m_gauss;

		//
		std::vector<CGeoPoint<double> > m_wells;		

		//
		//std::vector<CGeoPoint<double> > m_polygon;
		//CGeoRect<double> m_bounding;
		//double m_eurlimit;
		//double m_drainagelimit;
		//double m_cellsize;

		////
		//bool m_isostropic;
		//double m_ellipseangle;
		//double m_ellipsescale; // the long and short radius of an ellipse

		//
		//std::vector<CGeoPoint<double> > m_indicators;
		//int m_locations;
		//int m_realizations;
		//unsigned int m_seed;
		std::vector<SimulationSamples>m_simulations;//eur result


		KrigStochasticSimulation m_simulation;//parameters and mid results
		//for commit
		string m_remark;
	};
}
#endif
