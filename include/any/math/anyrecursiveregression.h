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
#ifndef __ANYMATH_RECURSIVE_REGRESSION_H__
#define __ANYMATH_RECURSIVE_REGRESSION_H__

// refer to macro
#include "anymath.h"
#include "any/base/anystl.h"

namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyRecursiveRegression
	{
	public:
		//
		struct GeologicalVariable
		{
			double m_correlation;	// xVariable & yVaraible
			string m_name;
			std::vector<double> m_samples;
			bool m_isPicked;
			int m_polynormals;

			GeologicalVariable() : m_correlation(0.), m_name(""), m_isPicked(false), m_polynormals(1)
			{
			}
			GeologicalVariable(const GeologicalVariable &other)
			{
				*this = other;
			}
			const GeologicalVariable &operator=(const GeologicalVariable &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_correlation = other.m_correlation;
				m_name = other.m_name;
				m_isPicked = other.m_isPicked;
				m_samples.clear();
				m_samples.assign(other.m_samples.begin(), other.m_samples.end());

				return *this;
			}
		};
		typedef std::vector<GeologicalVariable> VariableVector;

		//
		struct SimulatedCorrelation
		{
			int m_order;
			double m_correlation;
		};
		typedef std::vector<SimulatedCorrelation> CorrelationVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyRecursiveRegression(double limit = 0.3);
		~CAnyRecursiveRegression();

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitSamples(const GeologicalVariable &yVariable, VariableVector &xVariables);
		void CalculateCorrelation();
		void RecursiveRegression();
		double MakePredication(const GeologicalVariable &xVariable);
		void Release();

	protected:
		// 
		static bool CompareVariableCorrelation(const GeologicalVariable &first, const GeologicalVariable &second)
		{
			return first.m_correlation > second.m_correlation;
		}
		static bool CompareSimulatedCorrelation(const SimulatedCorrelation &first, const SimulatedCorrelation &second)
		{
			return first.m_correlation < second.m_correlation;
		}

		//
		void DoCalculateBeta(double **xmatrix);
		int DoPickNextVariable(double **xmatrix, double &rssp);
		bool IsStopPick(double **xmatrix);
		bool IsStopPick(double prevrssp, double rssp);

		double DoCalculateCorrelation(std::vector<double> &xValues, std::vector<double> &yValues);
		double DoCalculateStdVariance(std::vector<double> &samples);
		double DoCalculateVariableSimulatedCorrelation(std::vector<double> &samples, double **ymatrixsimulated, double &rssp);

	public:
		//
		double m_correlationlimit;

		//
		GeologicalVariable m_yVariable;
		VariableVector m_xVariables;

		//
		int m_rows;
		int m_cols;
		double **m_betas;
		double **m_ymatrix;
	};
}

#endif
