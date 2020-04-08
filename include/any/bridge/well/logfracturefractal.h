/*!
 * The AnyMap of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_LOG_ALGO_FRACTURE_FRACTAL_H__
#define __ANYBRIDGE_LOG_ALGO_FRACTURE_FRACTAL_H__

// refer to EXPORT & IMPORT
#include "anybridge.h"

//
// refer to ANYTRACESAMPLE
#include "anybridgedatamodel.h"

//
#include "any/base/anystl.h"
#include "any/base/anyport.h"
using namespace AnyBase;

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CLogFractureFractal
	{
	public:
		//
		struct LogCurve
		{
			string m_name;
			double m_leftvalue;
			double m_rightvalue;
			bool m_islogarithm;
			double m_weight;
			double m_invalidValue;
			std::vector<AnyTraceSample> m_samples;

			/*!
			*
			**/
			LogCurve() : m_name(""), m_leftvalue(ANY_NAN), m_rightvalue(ANY_NAN), m_islogarithm(false), m_weight(1.), m_invalidValue(ANY_NAN)
			{
			}
			LogCurve(const LogCurve &other)
			{
				*this = other;
			}
			const LogCurve &operator=(const LogCurve &other)
			{
				if(this != &other)
				{
					m_name = other.m_name;
					m_leftvalue = other.m_leftvalue;
					m_rightvalue = other.m_rightvalue;
					m_islogarithm = other.m_islogarithm;
					m_weight = other.m_weight;
					m_invalidValue = other.m_invalidValue;

					m_samples.clear();
					m_samples.assign(other.m_samples.begin(), other.m_samples.end());
				}

				return *this;
			}
		};
		typedef std::vector<LogCurve> CurveVector;

		//
		struct FractalParameter
		{
			// range
			double m_fromdepth;
			double m_todepth;

			// points needed at least along depth direction 
			int m_points;
			// L1, L2, L3, L4, L5
			int m_levelgrids[5];

			FractalParameter() : m_points(17), m_fromdepth(0.), m_todepth(0.)
			{
				m_levelgrids[0] = 8;
				m_levelgrids[1] = 16;
				m_levelgrids[2] = 32;
				m_levelgrids[3] = 64;
				m_levelgrids[4] = 80;
			}
			FractalParameter(const FractalParameter &other)
			{
				*this = other;
			}
			const FractalParameter &operator=(const FractalParameter &other)
			{
				if(this != &other)
				{
					m_points = other.m_points;
					::memcpy(m_levelgrids, other.m_levelgrids, sizeof(int)*5);
				}

				return *this;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CLogFractureFractal();
		~CLogFractureFractal();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetFractalParameter(const FractalParameter &para);
		const FractalParameter &GetFractalParameter();
		void SetLogCurve(const CurveVector &curves);
		const CurveVector &GetLogCurve();

		/*!
		*
		**/
		void GetFactalCurve(std::vector<AnyTraceSample> &curve);

	private:
		//
		double DoComputeFitK(double *xArray, double *yArray);

	private:
		//
		FractalParameter m_parameter;

		//
		CurveVector m_curves;
	};
}
#endif
