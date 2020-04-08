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
#ifndef __ANYMATH_MAXIMUM_PARAMETER_STRATEGY_H__
#define __ANYMATH_MAXIMUM_PARAMETER_STRATEGY_H__

// refer to macro
#include "anymath.h"

// refer to stl
#include "any/base/anystl.h"

//
namespace AnyMath
{
	/*!
	* Contributed by 肖晔, for getting distribution parameter by generally maximum liklihood method
	**/
	class ANYMATH_CLASS CAnyMaximumParameterStrategy
	{
	public:
		/*!
		*
		**/
		CAnyMaximumParameterStrategy();

		/*!
		*
		**/
		~CAnyMaximumParameterStrategy();

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitSamples(const string &distirbution, const std::vector<double> &samples,bool isTruncated=false, double tmax=0.0,double tmin=0.0);

		/*!
		* the similar to powell algorithm， 2维最优化
		**/
		bool Zangwill(double parameters[2], const double es=0.001);

	private:
		/*!
		* 似然函数
		**/
		double Q(double sita[2]);
		
		/*!
		* 方向搜索
		**/
		double g(double t,double z0[2],double a[2]);
		
		/*!
		* 1维最优化
		**/
		double minim(double es,double z0[2],double a[2]);

		//
		// the LOG(PDF) of kinds of distribution, 对数密度函数
		//
		/*!
		* 
		**/
		/*double lnp_pareto(double x,double b,double s);*/

		/*!
		* 
		**/
		double lnp_geological_pareto(double x,double b,double s);

		/*!
		* 
		**/
		double lnp_shift_pareto(double x,double b,double s);

		/*!
		*
		**/
		double lnp_beta(double x,double b,double s);

		/*!
		*
		**/
		double lnp_inverse_gamma(double x,double b,double s);

		/*!
		*
		**/
		double lnp_weibull(double x,double b,double s);

		/*!
		*
		**/
		double lnp_logistic(double x,double m,double s);

		/*!
		*
		**/
		double lnp_extreme(double x,double m,double s);

		/*!
		*
		**/
		double lnp_cauchy(double x,double m,double s);

		/*!
		*
		**/
		double lnp_gamma(double x,double k,double s);

	private:
		// distribution name
		string m_name;
		bool m_Truncated;
		// samples
		std::vector<double> m_samples;
		double m_qmax;
		double m_qmin;
		double m_tqmax,m_tqmin;
	};
}

#endif