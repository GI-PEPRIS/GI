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
#ifndef __ANYMATH_SEQUENTIAL_GAUSS_SIMULATOR_H__
#define __ANYMATH_SEQUENTIAL_GAUSS_SIMULATOR_H__

// refer to macro
#include "anymath.h"

//
#include "anykrigsimulator.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnySequentialGaussSimulator : public CAnyKrigSimulator
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySequentialGaussSimulator();
		~CAnySequentialGaussSimulator();

	public:

		//
		//
		//
		void KrigSimulation(std::vector<CGeoPoint<double> > &locations);
		void GaussSimulation(std::vector<CGeoPoint<double> > &locations);

		void ExcedenceSimulation(std::vector<CGeoPoint<double> > &locations, int iterations, double probability);
		void ExcedenceSimulation(std::vector<CGeoPoint<double> > &locations, int iterations,std::vector<std::vector<double> > &allsimulations);

	private:


		static int CompareValue( const void *a , const void *b ) 
		{ 
			return (*(double*)b-*(double*)a > 0) ? 1 : -1;
		}

		double DoGetQuantile(double *samples, double probability, int iterations);
		double DoNormal2Sample(double normalvalue);



	public:
		//
		unsigned long m_userSeed;
	};
}
#endif