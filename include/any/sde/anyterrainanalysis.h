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
#ifndef __ANYSDE_SDE_TERRAIN_ANALYSIS_H__
#define __ANYSDE_SDE_TERRAIN_ANALYSIS_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"
#include "anysderasterlayer.h"

// refer to STL
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "any/base/anyport.h"
using namespace AnyBase;

#include "any/math/anykriging.h"
using namespace AnyMath;

#include "any/cgal/anyrastermorphometricanalysis.h"
using namespace AnyCGAL;

using namespace std;
//
namespace AnySDE
{
	// forward class
	class CAnySdeRasterLayer;
	/*!
	*
	**/
	class ANYSDE_CLASS CAnyTerrainAnalysis : public CAnyViewHook
	{
	public:
		//
		enum TerrainAnalysisType
		{
			//micro factors
			TAT_Gradients,
			TAT_Aspects,
			TAT_SOS,
			TAT_SOA,
			TAT_Plancurvature,
			TAT_Profilecurvature,
			TAT_Radiation,
			TAT_Normals,
			//macro factors
			TAT_Roughness,
			TAT_Relief,
			TAT_Incision,
			TAT_Variancecoefficient,
			TAT_Slopeshape,
			//Feature Terrain
			TAT_Flowdirection,
			TAT_Flowaccumulation,
			TAT_Ridgepoints,
			TAT_Valleypoints,

			TAT_Fill,
		};

	public:
		//
		//
		//
		CAnyTerrainAnalysis(CAnyView &curView, CAnyViewHook *layer, std::string layername,double zfactor=1.0);
		CAnyTerrainAnalysis(CAnyView &curView, CAnyViewHook *layer, std::string layername, CGeoRect<double> extent, int rows,int cols,double min,double max,double **samples);
		~CAnyTerrainAnalysis();
				
		//
		// inherited from view hook
		//
		/*!
		*
		**/
		 void Clone(const CAnyViewHook *prototype)
		 {
		 }

	protected:
		//
		// behaviors as a typical view hook
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);
		
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);
				
		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);
		
	public:	
		//
		//
		//
		/*!
		*
		**/
		void ReadSampleData();
		void InitialTerrainFactors();
		void Release();

		void CalculateGradients();
		void CalculateAspect();//
		void CalculateConvexityConcavity();//
		void CalculatePlanCurvature();//
		void CalculateProfileCurvature();//
		void CalculateSOS();//
		void CalculateSOA();//
		void CalculateRoughness();//
		void CalculateReliefAmplitude(int windowsize=3);//
		void CalculateSurfaceIncision(int windowsize=3);//
		void CalculateVarianceCoefficient(int windowsize=3);//
		void CalculateSlopeShape(int windowsize=3);//
		void CalculateRadiation(double altitude=45.0, double direction=315.0);//
		void CalculateFlowDirection(int number=8);//
		void CalculateFlowAccumulation(int scantype=0);//
		void ExtractValleyPoints();//
		void ExtractRidgePoints();//
		void FillDEM();
		void CalculateStreamlines_peng(std::vector<std::vector<double> > inputraster, std::vector<std::vector<CGeoPoint<double> > > &outlines, \
			int xscale, int yscale, int xrange, int yrange, int interplotype, int scantype, bool checkinputraster);
		void CalculateStreamlinesOfDEM(std::vector<std::vector<double>> inputraster,std::vector<std::vector<CGeoPoint<int>>> &outlines, int scantype);
		void CalculateStreamlines(std::vector<std::vector<double>> inputraster,std::vector<std::vector<CGeoPoint<int>>> &outlines);
		void CalculateStreamlinesOfContour(std::vector<std::vector<double>> inputraster,std::vector<std::vector<CGeoPoint<int>>> &outlines,int rowcellnum, int colcellnum, double accum);
	public:
		// host layer
		CAnyViewHook *m_layer;
		std::string m_layeritemname;

	//protected:
		CAnyRasterMorphometricAnalysis morphanalysis;
		// raster extent
		CGeoRect<double> m_extent;
		int m_rows;
		int m_cols;
		double m_demmin;
		double m_demmax;
		//sample data
		double **m_samples;
		double **m_samples_extrapolation;//ExtrapolationDEM
		double **m_filldem;
		double m_zFactor;

		//terrain factors
		//micro factors
		double **m_gradients;
		double **m_aspects;
		double **m_SOS;
		double **m_SOA;
		double **m_plancurvature;
		double **m_profilecurvature;
		double **m_radiation;
		double **m_normals;
		//macro factors
		double **m_roughness;
		double **m_relief;
		double **m_incision;
		double **m_variancecoefficient;
		double **m_slopeshape;
		//Feature Terrain
		double **m_flowdirection;//8 directions
		double **m_flowdirection16;//16 directions
		double **m_flowdirection32;//32 directions
		double **m_flowaccumulation;
		double **m_ridgepoints;
		double **m_valleypoints;
	};
}
#endif