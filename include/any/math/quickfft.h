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
#ifndef __ANYMATH_QUICK_FFT_H__
#define __ANYMATH_QUICK_FFT_H__

// refer to macro
#include "anymath.h"

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anyport.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CQuickFFT
	{
	public:
		/*!
		*
		**/
		struct Complex
		{
			double m_real;
			double m_image;

			/*!
			*
			**/
			Complex() : m_real(0.), m_image(0.)
			{
			}

			/*!
			*
			**/
			Complex(const Complex &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const Complex &operator=(const Complex &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_real = other.m_real;
				m_image = other.m_image;

				return *this;
			}

			/*!
			*
			**/
			double GetAmplitude() const
			{
				return ::sqrt(m_real*m_real + m_image*m_image);
			}

			/*!
			*
			**/
			double GetPhase() const
			{
				return m_real == 0. ? ANY_NAN : ::atan(m_image/m_real);
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CQuickFFT();

		/*!
		*
		**/
		~CQuickFFT();

		/*!
		*
		**/
		CQuickFFT(const CQuickFFT &other)
		{
			*this = other;
		}

		CQuickFFT &operator=(const CQuickFFT &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_rows = other.m_rows;
			m_cols = other.m_cols;
			m_rExponential = other.m_rExponential;
			m_cExponential = other.m_cExponential;
			if(m_contents)
			{
				::free(m_contents);
			}
			m_contents = (Complex *)::malloc(sizeof(Complex) * m_rows * m_cols);
			::memcpy(m_contents, other.m_contents, sizeof(Complex) * m_rows * m_cols);
			
			return *this;
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		void InitImage(int rows, int cols)
		{
			m_rExponential = DoAlign2Power(rows);
			m_cExponential = DoAlign2Power(cols);
			m_rows = ::pow(2.0, m_rExponential);
			m_cols = ::pow(2.0, m_cExponential);

			if(m_contents)
			{
				::free(m_contents);
			}
			m_contents = (Complex *)::malloc(sizeof(Complex) * m_rows * m_cols);
			::memset(m_contents, 0x00, sizeof(Complex) * m_rows * m_cols);
		}

		/*!
		*
		**/
		long GetRows() const
		{
			return m_rows;
		}

		/*!
		*
		**/
		long GetCols() const
		{
			return m_cols;
		}

		/*!
		*
		**/
		void SetComplex(int row, int col, const Complex& value)
		{
			assert(m_contents);
			assert(row >= 0 && row < m_rows);
			assert(col >= 0 && col < m_cols);

			m_contents[row*m_cols+col] = value;
		}

		/*!
		*
		**/
		const Complex &GetComplex(int row, int col)
		{
			assert(m_contents);
			assert(row >= 0 && row < m_rows);
			assert(col >= 0 && col < m_cols);

			return m_contents[row * m_cols + col];
		}

		//
		//
		//
		/*!
		*
		**/
		void MakeFFT();

		/*!
		*
		**/
		void MakeIFFT()
		{
			DoIFFT();
		}

		/*!
		*
		**/
		void MakeIFFT(const CQuickFFT &real, const CQuickFFT &image)
		{
			DoMerge(real, image);
			DoIFFT();
		}

	private:
		//
		//
		//
		/*!
		*
		**/
		int DoAlign2Power(int older);

		/*!
		*
		**/
		void DoReverse(int len, int M, int **a, int **b);

		/*!
		*
		**/
		void DoMerge(const CQuickFFT &real, const CQuickFFT &image);

		/*!
		*
		**/
		Complex Add(const Complex &c1, const Complex &c2);

		/*!
		*
		**/
		Complex Sub(const Complex &c1, const Complex &c2);

		/*!
		*
		**/
		Complex Mul(const Complex &c1, const Complex &c2);

		/*!
		*
		**/
		void FFT1D(Complex *A, int fft_nLen, int fft_M);

		/*!
		*
		**/
		void DoIFFT();

	private:
		// matrix or image
		int m_rows;
		int m_cols;
		Complex *m_contents;
		int m_rExponential;
		int m_cExponential;
	};
}

#endif
