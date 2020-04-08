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
#ifndef __ANYMATH_KRIG_CO_SIMULATOR_H__
#define __ANYMATH_KRIG_CO_SIMULATOR_H__

// refer to macro
#include "anymath.h"
#include "anykrigsimulator.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyCoKrigSimulator : public CAnyKrigSimulator
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyCoKrigSimulator();
		~CAnyCoKrigSimulator();

	public:
		//
		//
		//
		void SetCoSimualator(CAnyKrigSimulator *co)
		{
			m_cooperator = co;
		}

		//
		//
		//
		void CoKrigDirect(std::vector<CGeoPoint<double> > &locations, int rows, int cols);
		void CoKrigDirect(std::vector<CGeoPoint<double> > &locations, int rows, int cols, CAnyKrigSimulator *cooperator);

	private:
		//
		void DoCalculateCoSampleVariance();
		void DoReleaseCoSampleVarianceIndice();

	public:
		// co-simulator
		CAnyKrigSimulator *m_cooperator;

		// set by two operators
		double m_co_sill;
		double m_co_nugget;
		double m_co_range;

		// indices
		double **m_co_sample_distances;
		double **m_co_sample_covariances;
	};
}

#endif
