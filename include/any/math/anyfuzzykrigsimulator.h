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
#ifndef __ANYMATH_FUZZY_KRIG_SIMULATOR_H__
#define __ANYMATH_FUZZY_KRIG_SIMULATOR_H__

// refer to macro
#include "anymath.h"

#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyMath
{
	/*!
	* both support 2D and 3D
	**/
	class ANYMATH_CLASS CAnyFuzzyKrigSimulator
	{
	public:
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
		struct KrigSample : public CGeoPoint<double>
		{
			long m_idx;
		};
		typedef std::vector<KrigSample > SampleContainer;
		typedef SampleContainer::iterator sample_itr;
		typedef SampleContainer::const_iterator sample_citr;

		//
		struct SampleCubeIndex
		{
			// [Xmin Ymin Zmin]
			CGeoPoint<double> m_min_point;	
			// [Xmax Ymax Zmax]
			CGeoPoint<double> m_max_point;

			// store position of sample container
			std::vector<sample_itr> m_samples;
		};
		typedef std::list<SampleCubeIndex> SampleIndexContainer;
		typedef SampleIndexContainer::iterator sample_index_itr;
		typedef SampleIndexContainer::const_iterator sample_index_citr;

		//
		struct KrigWeightParameter
		{
			//
			CGeoPoint<double> m_position;
			std::vector<sample_itr> m_arounds;

			//
			double m_sill;
			double m_nugget;
			double m_range;

			double m_value;
			double m_variance;

			//
			std::map<sample_itr, double> m_weights;

			bool operator < (const KrigWeightParameter &other)
			{
				return m_value < other.m_value;
			}
		};
		typedef std::vector<KrigWeightParameter> KrigParameterContainer;
		typedef KrigParameterContainer::iterator parameter_itr;
		typedef KrigParameterContainer::const_iterator parameter_citr;

		// variance fitting model
		enum VariogramModel
		{
			VM_SPHERICAL=0,
			VM_EXPONETIAL,
			VM_GUASSIAN,
			VM_LINEAR,
		};

		//
		//
		//
		/*!
		*
		**/
		CAnyFuzzyKrigSimulator(bool is3d = false, bool isAnisotropy = false);
		~CAnyFuzzyKrigSimulator();

	public:
		//
		//
		//
		void SetAnisotropyParameter(double angle = 0., double axisscale = 1.)	// anisostropy
		{
			m_isAnisotropy = true;
			m_anisotropy_angle = angle;
			m_anisotorpy_scale = axisscale;
		}

		//
		//
		//
		/*!
		*
		**/
		void SetSamples(const SampleContainer &samples);
		void CreateIndice(int xcells, int ycells, int zcells);
		void CreateIndice(int xcells, int ycells);

		//
		//
		//
		/*!
		*
		**/
		void GetSampleVariance(std::vector<CGeoPoint<double> >&variances, double tolerance);
		void SetVariogramModel(short type, double sill, double range, double nugget);
		void GetVariogramParameter(double &sill, double &range, double &nugget)
		{
			sill = m_sill;
			range = m_range;
			nugget = m_nugget;
		}
		void FitVariogramModel(short type);
		void GetModelVariance(std::vector<CGeoPoint<double> >&variances);
		void GetModelVariance(std::vector<CGeoPoint<double> >&variances, double nugget, double sill, double range);

		//
		//
		//
		/*!
		*
		**/
		void SetFuzzyMember(double theta1, double theta2, double theta3)
		{
			m_nugget_theta = theta1;
			m_sill_theta = theta2;
			m_range_theta = theta3;
		}
		void CalculateClassicKrigParameter(SampleContainer &locations, KrigParameterContainer &parameters);
		bool CalculateFuzzyKrigParameter(SampleContainer &locations, int iterations, KrigWeightParameter &min_parameters, KrigWeightParameter &max_parameters);

	private:
		//
		double GetModelValue(double h, double sill, double range, double nugget);
		double *Powell(double es);
		double Minim(double es,double z0[3],double a[3]);
		double DirectionFunction(double t,double z0[3],double a[3]);
		double ErrorFunction(double x[3]);

		//
		void DoKrigArounds(const CGeoPoint<double> &location, std::vector<sample_itr>& arounds);
		bool DoKrigInterpolation(KrigWeightParameter &parameter);
		void DoCalculateClassicKrigParameter(SampleContainer &locations, KrigParameterContainer &parameters, double nugget, double sill, double range);

		const SampleCubeIndex &DoGetSampleCube(const CGeoPoint<double> &location);
		void DoGetSampleCube(const CGeoPoint<double> &minxyz, const const CGeoPoint<double> &maxxyz, SampleIndexContainer &indices);

		//
		static bool CompareVarianceOrder(const CGeoPoint<double> &first, const CGeoPoint<double> &second)
		{
			return first.m_x < second.m_x;
		}

		//
		double DoGetVarianceDistance(const CGeoPoint<double> &firstpt, const CGeoPoint<double> &secondpt);
		bool IsLocateCurrentLag(double distance, double angle, double fromlag, double tolag);
		double DoGetVarianceAngle(const CGeoPoint<double> &firstpt, const CGeoPoint<double> &secondpt);

	public:
		//
		bool m_is_3d;
		// anisotropy
		bool m_isAnisotropy;
		double m_anisotropy_angle;
		double m_anisotropy_angle_tolerance;
		double m_anisotorpy_scale;

		// sample
		SampleContainer m_samples;
		std::vector<CGeoPoint<double> > m_variances;
		int m_lags;
		unsigned long m_userSeed;

		//
		SampleCubeIndex m_sample_extent;
		SampleIndexContainer m_indices;
		int m_xcells;
		int m_ycells;
		int m_zcells;
		double m_xcellwidth;
		double m_ycellwidth;
		double m_zcellwidth;

		// variance function
		short m_kernelType;
		double m_sill;
		double m_nugget;
		double m_range;

		// fuzzy definition
		double m_nugget_theta;
		double m_sill_theta;
		double m_range_theta;
		double m_fuzzy_theta;

		// limit to the number of arounds
		int m_around_number;
		double m_same_distance;

		//
	private:
		int m_taskcount;
		void *m_scheduler;
	};
}

#endif
