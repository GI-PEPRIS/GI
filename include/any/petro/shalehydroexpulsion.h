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
#ifndef __ANYPETRO_SHALE_HYDRO_EXPULSION_H__
#define __ANYPETRO_SHALE_HYDRO_EXPULSION_H__

// refer to EXPORT etc macroes
#include "anypetro.h"
#include "accumulationassessor.h"

#include "any/base/anygeom.h"
using namespace AnyBase;

#include "any/map/anyviewhook.h"
using namespace AnyMap;

#include "any/base/anyformulaparser.h"

#include "any/math/anysequentialgausssimulator.h"
using namespace AnyMath;


//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CShaleHydroExpulsion  : public CAccumulationAssessor,public CAnyObservable
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		enum VariableParameterType
		{
			VPT_Unknown = -1,						
			VPT_Thick,
			VPT_RO,
			VPT_TOC,

			VPT_Max,
		};

		enum UnitType
		{
			Hy_Unit_m= 0,						
			Hy_Unit_Km,
		
		};

		CShaleHydroExpulsion(CAccumulationElement *curElement, int activityType=CAccumulationAssessor::ST_Shale_Play_Ro);
		~CShaleHydroExpulsion();

		void Notify(short type);
		/*!
		*
		*/
		void Register(CAnyObserver *oneObserver);
		/*!
		*
		*/
		void Update();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Prepare();
		void MakeCalculation(int iterations = 0, double probability = 0.);
		unsigned int Commit(bool isDeleted = false);

	private:
		//
		bool DoGetExtentBounding(CGeoRect<double> &bounding);
		CGeoPoint<double> *CShaleHydroExpulsion::DoCalcCellValue(CGeoPoint<double> *cells);
		bool IsInsideExtent(const CGeoPoint<double> &pt);
		double DoGetHydroGeneration(double ro);
		double DoGetHydroExpulsion(double ro);
		double DoGetHydroDensity(double ro);
		double DoCalcLinearInterploation(const std::vector<CGeoPoint<double> > &samples, double ro);

		//
		void DoDirectCalculation(std::vector<CGeoPoint<double> > &centers, CGeoPoint<double> *rovalues, CGeoPoint<double> *thickvalues, CGeoPoint<double> *tocvalues);


	public:
		struct ResourcePredication
		{
			double m_generation;
			double m_expulsion;
			double m_retain;
			double m_ratio;
			

			ResourcePredication() : m_generation(0.), m_expulsion(0.), m_retain(0.), m_ratio(0.)
			{
			}
			ResourcePredication(const ResourcePredication &other)
			{
				*this = other;
			}
			const ResourcePredication &operator=(const ResourcePredication &other)
			{
				if(this != &other)
				{
					m_generation = other.m_generation;
					m_expulsion = other.m_expulsion;
					m_retain = other.m_retain;
					m_ratio = other.m_ratio;
				
				}
				return *this;
			}
		};
		typedef std::vector<ResourcePredication> ResourcePredicationVector;


	
		typedef std::map<short, std::vector<CGeoPoint<double> > > VariableParameterMap;
		
		// variable simulator
		typedef std::map<short, CAnySequentialGaussSimulator> VariableSimulatorMap;

		CAnySequentialGaussSimulator &GetSimulator(short variabletype);	// 变差分析及设置

		void GetUncertainResultsamples(std::vector<CGeoPoint<double> > &generationsamples,std::vector<CGeoPoint<double> > &expulsionsamples,std::vector<CGeoPoint<double> > &expulsionRatiosamples,std::vector<CGeoPoint<double> > &expulsionRessamples);
		
		void DoCalcCellValue2(std::vector<CGeoPoint<double> > &centers,std::vector<std::vector<double> > &points,std::vector<std::vector<double> > &grids,std::vector<CGeoPoint<double> > &cellpos,int iterations);
	public:
		CAnyObserver *m_observer;

		VariableParameterMap m_varsamples;
		VariableSimulatorMap m_varsimulators;
		ResourcePredicationVector m_varres;
		
		// uncertainty analysis
		unsigned int m_userseed;
		int m_iterations;

		// current object
		CAccumulationElement *m_element;

		// for one point, m_x: (s1+s2)/Toc, m_y:ro, m_z:depth
		std::vector<CGeoPoint<double> > m_ihcppoints;
		std::vector<CGeoPoint<double> > m_ihcpcurve; // the last point of this curve is senseful //残留烃
		std::vector<CGeoPoint<double> > m_ihcocurve; //生成烃
		CGeoPoint<double> m_ihcomax;	// the rightest point of ihcp points

		// geochemical variable
		double m_recoverycoff; // recovery coff
		double m_rodelta;

		// density formular
		string m_densityformular;

		// input maps
		std::vector<CGeoPoint<double> > m_polygon;
		CGeoRect<double> m_bounding;
		int m_rows;
		int m_cols;

		//
		CAnyViewHook *m_ro;
		string m_rofield;	// for none contour layer
		CAnySequentialGaussSimulator m_rosimulator;

		CAnyViewHook *m_thickness;
		string m_thickfield;	// for none contour layer
		CAnySequentialGaussSimulator m_thicknesssimulator;

		CAnyViewHook *m_toc;
		string m_tocfield;
		CAnySequentialGaussSimulator m_tocsimulator;


		std::vector<std::vector<double> > m_rovalues;
		std::vector<std::vector<double> > m_thickvalues;
		std::vector<std::vector<double> > m_tocvalues;

		
		std::vector<CGeoPoint<double> > m_rosamples;
		std::vector<CGeoPoint<double> > m_thicksamples;
		std::vector<CGeoPoint<double> > m_tocsamples;


	
		// outputs curve
		std::vector<CGeoPoint<double> > m_generationcurve; // hydro generation //生成烃
		std::vector<CGeoPoint<double> > m_expulsioncurve;	// hydro expulsion //排烃曲线
		std::vector<CGeoPoint<double> > m_expulsionRatiocurve;	// hydro expulsion //排烃率曲线

		// map
		CAnyViewHook *m_generationQ;//生
		std::vector<CGeoPoint<double> > m_generationsamples;
		
		CAnyViewHook *m_expulsionQ;//排
		std::vector<CGeoPoint<double> > m_expulsionsamples;
		
		CAnyViewHook *m_expulsionRatio;//排率	
		std::vector<CGeoPoint<double> > m_expulsionRatiosamples;
		
		CAnyViewHook *m_expulsionResidual;//剩
		std::vector<CGeoPoint<double> > m_expulsionRessamples;

		//不确定性
		ResourcePredicationVector m_resources;
		std::vector<std::vector<CGeoPoint<double> >> m_uncertaingenerationsamples;
		std::vector<std::vector<CGeoPoint<double> >> m_uncertainexpulsionsamples;
		std::vector<std::vector<CGeoPoint<double> >> m_uncertainexpulsionRatiosamples;
		std::vector<std::vector<CGeoPoint<double> >> m_uncertainexpulsionRessamples;

		int m_unitX;
		int m_unitY;

		double m_dyindex;

	};
}
#endif