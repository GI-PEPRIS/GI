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
#ifndef __ANYBRIDGE_TRACE_SAMPLE_ALGEBRA_H__
#define __ANYBRIDGE_TRACE_SAMPLE_ALGEBRA_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to ANYTRACESAMPLE
#include "..\anybridgedatamodel.h"

// namespace
namespace AnyBridge
{
	/*!
	* also as a decorator
	**/
	class ANYBRIDGE_CLASS CAnyTraceSampleAlgebra
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyTraceSampleAlgebra();
		CAnyTraceSampleAlgebra(const std::vector<AnyTraceSample> &samples, double invalidVal = ANY_NAN);
		CAnyTraceSampleAlgebra(const CAnyTraceSampleAlgebra &other);
		const CAnyTraceSampleAlgebra &operator=(const CAnyTraceSampleAlgebra &other);
		~CAnyTraceSampleAlgebra();
		
	public:
		//
		//
		//
		/*!
		*
		**/
		void SetSampleName(const string &name);
		string GetSampleName();
	
		//
		// binary operations including basic operators such as arithmetic, relational, boolean, combinatorial, assignment etc
		//
		/*!
		*
		**/
		CAnyTraceSampleAlgebra operator+(const CAnyTraceSampleAlgebra &other);
		CAnyTraceSampleAlgebra operator-(const CAnyTraceSampleAlgebra &other);
		CAnyTraceSampleAlgebra operator*(const CAnyTraceSampleAlgebra &other);
		CAnyTraceSampleAlgebra operator/(const CAnyTraceSampleAlgebra &other);

		/*!
		*
		**/
		CAnyTraceSampleAlgebra operator+(double scalar);
		CAnyTraceSampleAlgebra operator-(double scalar);
		CAnyTraceSampleAlgebra operator*(double scalar);
		CAnyTraceSampleAlgebra operator/(double scalar);

		/*!
		*
		**/
		CAnyTraceSampleAlgebra operator+=(const CAnyTraceSampleAlgebra &other);
		CAnyTraceSampleAlgebra operator-=(const CAnyTraceSampleAlgebra &other);
		CAnyTraceSampleAlgebra operator*=(const CAnyTraceSampleAlgebra &other);
		CAnyTraceSampleAlgebra operator/=(const CAnyTraceSampleAlgebra &other);

		/*!
		*
		**/
		void pow(const CAnyTraceSampleAlgebra &other);
		void fabs();
		void sqrt();
		void sinh();
		void cosh();
		void tanh();
		void atan();
		void log();
		void log10();
		void exp();
		void sin();
		void cos();
		void cot();
		void tan();
		void asin();
		void acos();
		void integer();

		void Signl();
		void RAD();
		void DEG();
		void ArSinh();
		void ArCosh();
		void ArTanh();
				
		void SetMax();
		void SetMin();
		void SetSampleValue(double val);
		void Delta();
		void Slope();
	public:
		// as unique identification
		string m_name; 
		double m_value;//if m_samples is null,set all m_samples = m_value  
		std::vector<AnyTraceSample> m_samples;
		double m_invalidValue;//2016/7/14
	private:
		std::vector<AnyTraceSample> m_bkSamples;
	};
}

#endif