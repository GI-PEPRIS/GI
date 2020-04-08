/*!
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYCGAL_RASTER_MORPHOMETRIC_ANALYSIS_H__
#define __ANYCGAL_RASTER_MORPHOMETRIC_ANALYSIS_H__

// macro
#include "anycgal.h"

#include "any/base/anygeom.h"
using namespace AnyBase;
#include "any/thread/jtc.h"
//
namespace AnyCGAL
{
	/*!
	*
	**/
	class ANYCGAL_CLASS CAnyRasterMorphometricAnalysis
	{
		/*!
		*
		**/
		struct CalculateSlopeParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double m_xus;
			double m_yus;
			double **m_v1;
			double **&m_normals;
			double **&m_aspects;
			double **&m_gradients;
			CalculateSlopeParameter(int taskcount, int index,int xas, int yas, double xus,double yus,double **v1,double **&normals,double **&aspects,double **&gradients) : m_normals(normals), m_aspects(aspects), m_gradients(gradients)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_xus=xus;
				m_yus=yus;
				m_v1=v1;
			}
		};
		struct CalculateSlopeParameter1
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double m_xus;
			double m_yus;
			double **&m_dem_extrapolation;
			double **&m_normals;
			double **&m_aspects;
			double **&m_gradients;
			CalculateSlopeParameter1(int taskcount, int index,int xas, int yas, double xus,double yus,double **&dem_extrapolation,double **&normals,double **&aspects,double **&gradients) : \
				m_dem_extrapolation(dem_extrapolation), m_normals(normals), m_aspects(aspects), m_gradients(gradients)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_xus=xus;
				m_yus=yus;
			}
		};
		struct CalculateCurvatureParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double m_xus;
			double **m_v1;
			double **&m_slopeangles;
			double **&m_aspectangles;
			double **&m_profiles;
			double **&m_plans;
			CalculateCurvatureParameter(int taskcount, int index,int xas, int yas, double xus,double **v1,double **&slopeangles,double **&aspectangles,double **&profiles,double **&plans) : \
				m_slopeangles(slopeangles), m_aspectangles(aspectangles), m_profiles(profiles), m_plans(plans)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_xus=xus;
				m_v1=v1;
			}
		};
		struct CalculateRoughnessParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double m_xus;
			double m_yus;
			double **m_v1;
			double **m_gradients;
			double **&m_roughness;
			CalculateRoughnessParameter(int taskcount, int index,int xas, int yas, double xus,double yus,double **v1,double **gradients,double **&roughness) : m_roughness(roughness)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_xus=xus;
				m_yus=yus;
				m_v1=v1;
				m_gradients=gradients;
			}
		};
		struct CalculateReliefAmplitudeParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double **m_v1;
			int m_windowsize;
			double **&m_relief;
			CalculateReliefAmplitudeParameter(int taskcount, int index,int xas, int yas, double **v1,int windowsize,double **&relief) : m_relief(relief)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_v1=v1;
				m_windowsize = windowsize;
			}
		};
		struct CalculateSurfaceIncisionParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double **m_v1;
			int m_windowsize;
			double **&m_incision;
			CalculateSurfaceIncisionParameter(int taskcount, int index,int xas, int yas, double **v1,int windowsize,double **&incision) : m_incision(incision)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_v1=v1;
				m_windowsize = windowsize;
			}
		};
		struct CalculateVarianceCoefficientParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double **m_v1;
			int m_windowsize;
			double **&m_variancecoefficient;
			CalculateVarianceCoefficientParameter(int taskcount, int index,int xas, int yas, double **v1,int windowsize,double **&variancecoefficient) : m_variancecoefficient(variancecoefficient)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_v1=v1;
				m_windowsize = windowsize;
			}
		};
		struct CalculateSlopeShapeParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double **m_v1;
			int m_windowsize;
			double **&m_slopeshape;
			CalculateSlopeShapeParameter(int taskcount, int index,int xas, int yas, double **v1,int windowsize,double **&slopeshape) : m_slopeshape(slopeshape)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_v1=v1;
				m_windowsize = windowsize;
			}
		};
		struct CalculateHydrologicalModellingParameter
		{
			int m_taskcount;
			int m_index;
			int m_xas;
			int m_yas;
			double m_ux;
			double m_uy;
			double m_uxy;
			double **m_v1;
			double **m_v3;
			double **&m_streamlines;
			CalculateHydrologicalModellingParameter(int taskcount, int index,int xas, int yas, double ux,double uy,double uxy,double **v1,double **v3,double ** &streamlines) : m_streamlines(streamlines)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_xas=xas;
				m_yas=yas;
				m_ux=ux;
				m_uy=uy;
				m_uxy=uxy;
				m_v1=v1;
				m_v3 = (double **)::malloc(sizeof(double*)*(m_xas+2));
				for(int i = 0; i < (m_xas+2); i++)
				{
					m_v3[i] = (double*)::malloc(sizeof(double)*(m_yas+2));
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
		CAnyRasterMorphometricAnalysis();
		~CAnyRasterMorphometricAnalysis();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Initialize(double **samples, int rows, int cols, const CGeoRect<double> &extent);

		//
		// mapraster2
		//
		/*!
		* Gradient angle at each location was calculated from the DEM and draped in color
		* Aspect angle of the slope at each location was calculated from the DEM and draped in color. Zero (blue) denotes the north-facing slope 
		* and the value increases clockwise up to 360 in degrees.
		**/
		void CalculateSlope(double **normals, double **aspects, double **gradients);
		void CalculateSlopeMT(double **normals, double **aspects, double **gradients);
		void CalculateSlope_Thread(const CalculateSlopeParameter &parameter);
		void CalculateSlope(double **samples, double **normals, double **aspects, double **gradients);
		void CalculateSlopeMT(double **samples, double **normals, double **aspects, double **gradients);
		void CalculateSlope_Thread1(const CalculateSlopeParameter1 &parameter);
		/*!
		* Convexity and concavity (negative convexity) of the terrain are calculated via Laplacian operation. In the study area, where rainfall, surface runoff and 
		* streams are dominant factors of terrain formation, index of convexity / concavity shows ridge lines and stream lines. To extract major features of the terrain, 
		* the original data are preprocessed by smoothing operation.
		**/
		void CalculateConvexityConcavity(double **laplacians);
		/*!
		* Zevenbergen and Thorne (1987) proposed a procedure to output surface parameters such as slope angle, aspect angle, 
		* profile curvature and plan curvature through calculating coefficients of the quadratic surface (polynomial) fitted to the nine neighborhood points. 
		* The result of calculating plan curvature is shown on the right. As for the result of aspect angle, same values are output in every 180 degrees...(hey!) 
		* Since the grid of the processed DEM is assumed to be square, the DEM is preprocessed through resampling.
		**/
		void CalculateCurvature(double **slopeangles, double **aspectangles, double **profiles, double **plans);
		void CalculateCurvatureMT(double **slopeangles, double **aspectangles, double **profiles, double **plans);
		void CalculateCurvature_Thread(const CalculateCurvatureParameter &parameter);
		/*!
		* Ridge lines are shown in yellow. The function of extracting ridge lines from DEMs is not implemented in mapRaster2 yet. 
		* The program for this function was coded by students at our laboratory using C++ language, based on the procedure described in the pages 54-55 of Principles of Geographical Information 
		* Systems for Land Resources Assessment by P. A. Burrough (1986).
		**/
		void CalculateRidgeLines(double **ridgelines);
		/*!
		* In the same way as shown above, stream lines are extracted from the DEM and shown in blue. 
		* Because of the nature of the Grid DEM, stream lines in the real world cannot be traced exactly. Therefore extracted stream lines are sometimes disconnected.
		**/
		void CalculateValleyLines(double **valleylines);
		/*!
		* Surface flow from each point on the DEM is simulated, then the flow courses are accumulated to map stream lines. 
		* As mentioned above, because of the nature of the Grid DEM, simulated stream lines are sometimes disconnected.
		* More important difference of this model from the reality is that, on the forested surface such as this study area, rainfall mostly infiltrates into the soil and does not run over the surface.
		**/
		void CalculateHydrologicalModelling( double **streamlines);
		void CalculateHydrologicalModellingMT( double **streamlines);
		void CalculateHydrologicalModelling_Thread(const CalculateHydrologicalModellingParameter &parameter);

		/*!
		* return flow directions: 1,2,4,8,16,32,64,128
		**/
		double ** CalculateFlowDirection();
		/*!
		* return flow directions: 0-31
		**/
		double ** CalculateFlowDirection2(int count);
		double ** CalculateFlowAccumulationFromDirection(double** flowdir);
		double ** CalculateFlowAccumulationFromDirection2(double** flowdir);
		/*!
		* roughness
		**/
		void CalculateRoughness(double **roughness);
		void CalculateRoughnessMT(double **roughness);
		void CalculateRoughness_Thread(const CalculateRoughnessParameter &parameter);
		double ** CalculateRoughnessFromGradients( double **gradients);
				
		/*!
		* slope of slope
		**/
		void CalculateSOS(double **sos);
		void CalculateSOSMT(double **sos);
		double ** CalculateSOSFromGradients( double **gradients);
		double ** CalculateSOSFromGradientsMT( double **gradients);
		/*!
		* slope of aspect
		**/
		void CalculateSOA(double **soa);
		void CalculateSOAMT(double **soa);
		double ** CalculateSOAFromAspects( double **aspects);
		double ** CalculateSOAFromAspects( double **aspects, double **aspects_reverse);
		double ** CalculateSOAFromAspectsMT( double **aspects, double **aspects_reverse);
		/*!
		* ReliefAmplitude
		**/
		void CalculateReliefAmplitude(double **relief, int windowsize=3);
		void CalculateReliefAmplitudeMT(double **relief, int windowsize=3);
		void CalculateReliefAmplitude_Thread(const CalculateReliefAmplitudeParameter &parameter);
				
		/*!
		* SurfaceIncision
		**/
		void CalculateSurfaceIncision(double **incision, int windowsize=3);
		void CalculateSurfaceIncisionMT(double **incision, int windowsize=3);
		void CalculateSurfaceIncision_Thread(const CalculateSurfaceIncisionParameter &parameter);
				
		/*!
		* VarianceCoefficient
		**/
		void CalculateVarianceCoefficient(double **variancecoefficient, int windowsize=3);
		void CalculateVarianceCoefficientMT(double **variancecoefficient, int windowsize=3);
		void CalculateVarianceCoefficient_Thread(const CalculateVarianceCoefficientParameter &parameter);
				
		/*!
		* ReliefAmplitude
		**/
		void CalculateSlopeShape(double **slopeshape, int windowsize=3);
		void CalculateSlopeShapeMT(double **slopeshape, int windowsize=3);
		void CalculateSlopeShape_Thread(const CalculateSlopeShapeParameter &parameter);
				
		/*!
		* Radiation/HillShade
		**/
		void CalculateRadiation(double **radiation, double altitude=45.0, double direction=315.0);
		void CalculateRadiationMT(double **radiation, double altitude=45.0, double direction=315.0);
		double ** CalculateRadiationFromSlope(double **gradients,double **aspects,double altitude=45.0, double direction=315.0);

		double** ExtrapolationDEM(double **dem,int width, int height, int windowsize);
		double** ExtrapolationDEM(double **dem,int width, int height);

		double** MeanValueDEM(double **dem,int row,int col, int windowsize);
		double** PositiveTerrain(double **dem,int row,int col, int windowsize);
		double** NegativeTerrain(double **dem,int row,int col, int windowsize);

		double **FillDEM();
	protected:
		//
		//
		//
		/*!
		*
		**/
		static CGeoPoint<double> DoCalculateNormVector(CGeoPoint<double> tri[3]);



		double **ReverseDEM(double **dem,int row,int col);

		void MaxMinValueDEM(double **dem,int row,int col, double &maxval, double &minval);


	private:
		// sample data
		double **m_samples;
		int m_rows;
		int m_cols;

		// geo extent
		CGeoRect<double> m_extent;

		double **m_samples_extrapolation;//ExtrapolationDEM
	};
}
#endif