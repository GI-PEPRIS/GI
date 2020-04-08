/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGDE_SAMPLE_DATA_CALCULATOR_CUBE__H__
#define __ANYGDE_SAMPLE_DATA_CALCULATOR_CUBE__H__

// refer to EXPORT & IMPORT
#include "anygde.h"

//
#include "anygdedatatrace.h"

// refer to stl, ANY_NAN
#include "any/base/anystl.h"
#include "any/base/anyport.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CalculatorCube
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		struct CubeExtent
		{
			// inline extent
			long m_inlStart;
			long m_inlStep;
			long m_inlEnd;

			// cross line
			long m_crlStart;
			long m_crlStep;
			long m_crlEnd;

			// time or depth window
			double m_minZ;
			double m_maxZ;

			/*!
			*
			**/
			CubeExtent() : m_inlStart(ANY_NAN), m_inlStep(ANY_NAN), m_inlEnd(ANY_NAN), \
				m_crlStart(ANY_NAN), m_crlStep(ANY_NAN), m_crlEnd(ANY_NAN), m_minZ(ANY_NAN), m_maxZ(ANY_NAN)
			{
			}

			/*!
			*
			**/
			CubeExtent(const CubeExtent &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const CubeExtent &operator=(const CubeExtent &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_inlStart = other.m_inlStart;
				m_inlStep = other.m_inlStep;
				m_inlEnd = other.m_inlEnd;
				m_crlStart = other.m_crlStart;
				m_crlStep = other.m_crlStep;
				m_crlEnd = other.m_crlEnd;
				m_minZ = other.m_minZ;
				m_maxZ = other.m_maxZ;

				return *this;
			}
		};

		/*!
		* 
		**/
		struct DataCubeSize
		{
			int m_inlCount;
			int m_crlCount;
			double m_windowZ;

			/*!
			*
			**/
			DataCubeSize() : m_inlCount(0), m_crlCount(0), m_windowZ(0.)
			{
			}

			/*!
			*
			**/
			DataCubeSize(const DataCubeSize &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const DataCubeSize &operator=(const DataCubeSize &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_inlCount = other.m_inlCount;
				m_crlCount = other.m_crlCount;
				m_windowZ = other.m_windowZ;

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
		CalculatorCube();

		/*!
		*
		**/
		~CalculatorCube();

	public:
		//
		CalculatorCube(const CalculatorCube &other)
		{
			*this = other;
		}
		const CalculatorCube &operator=(const CalculatorCube &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_extent = other.m_extent;
			m_order = other.m_order;
			m_inputs = other.m_inputs;

			return *this;
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetCubeExtent(const CubeExtent &extent)
		{
			m_extent = extent;
		}

		/*!
		*
		**/
		const CubeExtent &GetCubeExtent() const
		{
			return m_extent;
		}

		//
		//
		//
		/*!
		*
		**/
		int GetTraceCount();

		/*!
		*
		**/
		CAnyGdeDataTrace *GetSampleTrace(int order);
		
		/*!
		*
		**/
		void Release();

	public:
		// cube extent
		CubeExtent m_extent;

		// input data
		CAnyGdeDataTrace::TraceVector m_inputs;

		// order in all cubes
		int m_order;
	};
}
#endif