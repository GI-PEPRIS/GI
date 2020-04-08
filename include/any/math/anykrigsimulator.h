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
#ifndef __ANYMATH_KRIG_SIMULATOR_H__
#define __ANYMATH_KRIG_SIMULATOR_H__

// refer to macro
#include "anymath.h"
#include "histogramdistribution.h"

//
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;


//
namespace AnyMath
{
	// only to fit consider here still exist uncontrol bugs
	//class CVariogramRegression;

	/*!
	*
	**/
	class ANYMATH_CLASS CAnyKrigSimulator
	{
	public:
		//// variogram fitting
		//enum VariogramModel
		//{
		//	VM_SPHERICAL=0,
		//	VM_EXPONETIAL,
		//	VM_GUASSIAN,
		//	VM_LINEAR,
		//};

		//
		enum SampleType
		{
			ST_Original = 0,
			ST_Log,
			ST_Guass,
		};

		//
		enum UniversalType
		{
			ULINEAR = 0,
			UQUADRATIC,
		};

	protected:
		//
		struct VarianceThreadParameter
		{
			int m_sample_from;
			int m_sample_to;

			int m_lag_from;
			int m_lag_to;

			double m_lag;

			std::vector<CGeoPoint<double> > &m_distances;
			std::vector<CGeoPoint<double> > &m_variances;

			VarianceThreadParameter(std::vector<CGeoPoint<double> > &distances, std::vector<CGeoPoint<double> > &variances) : \
				m_distances(distances), m_variances(variances)
			{
			}
		};
		void VairanceDistanceThreadFunc(VarianceThreadParameter &parameter);
		void VairanceLagThreadFunc(VarianceThreadParameter &parameter);

		//
		//
		struct SequentialOrder : public CGeoPoint<double>
		{
			//double m_x;
			//double m_y;
			double m_value;
			int m_index;
			bool m_issample;
		};
		static bool CompareSequentialOrder(const SequentialOrder &first, const SequentialOrder &second)
		{
			return first.m_value < second.m_value;
		}

		//
		struct KrigDirectThreadParameter
		{
			int m_location_from;
			int m_location_to;
			CGeoPoint<double> *m_locations;

			//
			bool m_isall;
			std::vector<SequentialOrder > m_arounds;

			KrigDirectThreadParameter() : m_location_from(0), m_location_to(0), m_locations(0), m_isall(false)
			{
			}
		};
		void KrigDirectThreadFunc(KrigDirectThreadParameter &parameter);

		//
		struct UniversalKrigDirectThreadParameter : public KrigDirectThreadParameter
		{
			short m_universaltype;

			//
			bool m_isall;
			std::vector<SequentialOrder > m_arounds;

			//
			UniversalKrigDirectThreadParameter() : m_universaltype(ULINEAR), m_isall(false)
			{
			}
		};
		void UniversalKrigDirectThreadFunc(UniversalKrigDirectThreadParameter &parameter);

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyKrigSimulator();
		~CAnyKrigSimulator();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetSamples(const std::vector<CGeoPoint<double> > &samples); // isostropy

		//
		//
		//
		void SetAnisotropyParameter(double degree_angle, double degree_angle_tolerance = 10.)	// anisostropy
		{
			if(degree_angle)
			{
				m_isAnisotropy = true;

				m_anisotropy_angle = degree_angle;				
				if(m_anisotropy_angle >= 180) m_anisotropy_angle -= 180;

				m_anisotropy_angle_tolerance = degree_angle_tolerance;
			}
		}
		void GetSampleVariance(std::vector<CGeoPoint<double> >&variances, double tolerance = 1.); //  (d,r)
		void GetSampleVariance_Threaded(std::vector<CGeoPoint<double> >&variances, double tolerance = 1.); //  (d,r)
		void GetModelVariance(std::vector<CGeoPoint<double> >&variances);

		// deprecated variogram functions
		//void SetVariogramModel(short type, double sill, double range, double nugget);
		//void GetVariogramParameter(double &sill, double &range, double &nugget)
		//{
		//	sill = m_sill;
		//	range = m_range;
		//	nugget = m_nugget;
		//}
		//void FitVariogramModel(short type);
		//double GetModelValue(double h, double sill, double range, double nugget);

		// the latest variogram functions 
		void Fit_Best_Consider_AllParameters(); //for the first time to call
		void Fit_NotConsiderNuddget(short kernel_type);
		void Fit_ConsiderNuddget(short kernel_type);
		void Fit_GetVariogramParameter(short &kernel_type, double &sill, double &range, double &nugget);
		void Fit_SetVariogramParameter(short type, double sill, double range, double nugget);
		double Fit_GetModelValue(short kernel_type, double h,double sill, double range, double nugget);

		bool Fit_2D_Variogram(int sectioncountx, int sectioncounty, double &c0_hor, \
			double Ratio_Crit, std::vector<std::vector<double> > &Var_2D_show, std::vector<double> &x_axis_show, std::vector<double> &y_axis_show, std::vector<CGeoPoint<double> > &sample_for_plot);

		// ordinary krig
		void KrigDirect(std::vector<CGeoPoint<double> > &locations, int rows = 0, int cols = 0);
		void KrigDirect_Threaded(std::vector<CGeoPoint<double> > &locations, int rows = 0, int cols = 0);

		// universal krig
		void UniversalKrigDirect(std::vector<CGeoPoint<double> > &locations, int rows = 0, int cols = 0, short universaltype = ULINEAR);
		void UniversalKrigDirect_Threaded(std::vector<CGeoPoint<double> > &locations, int rows = 0, int cols = 0, short universaltype = ULINEAR);

	protected:
		//
		static bool CompareSampleValue(const CGeoPoint<double> &first, const CGeoPoint<double> &second)
		{
			return first.m_z < second.m_z;
		}
		static bool CompareVarianceOrder(const CGeoPoint<double> &first, const CGeoPoint<double> &second)
		{
			return first.m_x < second.m_x;
		}
		static bool CompareDistanceY(const CGeoPoint<double> &first, const CGeoPoint<double> &second)
		{
			return first.m_y < second.m_y;
		}

		// inverse distance weight when facing krig can't interplolate

		//
		double *Powell(double es);
		double Minim(double es,double z0[3],double a[3]);
		double DirectionFunction(double t,double z0[3],double a[3]);
		double ErrorFunction(double x[3]);

		//
		double DoGetVarianceDistance(const CGeoPoint<double> &firstpt, const CGeoPoint<double> &secondpt, bool is_anisotropy_interpolation = false);
		bool IsLocateCurrentLag(double distance, double angle, double fromlag, double tolag);
		double DoGetVarianceAngle(const CGeoPoint<double> &firstpt, const CGeoPoint<double> &secondpt);

		//
		void DoIDW(std::vector<CGeoPoint<double> > &locations);
		
		//
		bool Cal_Exp_Var_2D_Discrete(std::vector<CGeoPoint<double> > &discretepts, int sectioncountx, int sectioncounty, \
			std::vector<std::vector<double> > &Var_2D, std::vector<std::vector<double> > &fold_2D, double &c0_hor, \
			double Ratio_Crit, std::vector<std::vector<double> > &Var_2D_show, std::vector<double> &x_axis_show, std::vector<double> &y_axis_show, std::vector<CGeoPoint<double> > &samples_for_plot);
	public:
		//
		void DoCreateSampleVarianceIndice();
		void DoCreateSampleSpatialIndice(int rows, int cols);
		void DoReleaseSampleVarianceIndice();
		void DoGetArounds(const CGeoPoint<double> &cur, std::vector<SequentialOrder> &arounds);
		void DoGetArounds_WithIndex(const CGeoPoint<double> &cur, std::vector<SequentialOrder> &arounds);

	public:
		// samples
		short m_sampletype;
		double m_same_distance;
		std::vector<CGeoPoint<double> > m_initial_samples;
		std::vector<CGeoPoint<double> > m_samples;
		std::vector<CGeoPoint<double> > m_variances;
		int m_rows;
		int m_cols;
		CGeoRect<double> m_extent;

		// for guass change
		std::vector<double> m_normal_fractiles;
		CAnyDistributionStrategy *m_normaldistribution;

		// variance
		bool m_is_max_lag_distance;
		int m_lags;
		double m_lag_distance;
		short m_kernelType;
		double m_sill;
		double m_nugget;
		double m_range; // primary direction
		double m_secondary_range; // secondary direction

		// anisotropy
		bool m_isAnisotropy;
		double m_anisotropy_angle;
		double m_anisotropy_angle_tolerance;

		// indice
		double **m_sample_distances;
		double **m_sample_covariances;

		//
		bool m_arounds_is_limited;
		int m_arounds_limited_number;

		//variogram regression
	    //CVariogramRegression *m_variogram_regression;
		std::vector<CGeoPoint<double> > m_sample_between_distances;
		
	protected:
		int m_taskcount;
		void *m_scheduler;

		//sample index: 10*10 grid
		std::vector<std::vector<int> > m_sampleIndex;
		double m_indexgridX;
		double m_indexgridY;
		int m_indexgridnumX;
		int m_indexgridnumY;
	};
}

#endif