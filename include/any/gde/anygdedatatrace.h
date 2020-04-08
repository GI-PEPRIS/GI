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
#ifndef __ANYGDE_SAMPLE_DATA_TRACE_H__
#define __ANYGDE_SAMPLE_DATA_TRACE_H__

// refer to EXPORT & IMPORT
#include "anygde.h"

// refer to CGeoPoint
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyGDE
{
	// forward class
	class CAnyGdeDataSet;

	/*!
	* recursively compositie from children until to one octree tile
	**/
	class ANYGDE_CLASS CAnyGdeDataTrace
	{
		// relatives
		friend class CAnyGdeDataSet;
		friend class CAnyGdeDataOctree;

	public:
		// trace cache by defualt sorted in sequence order
		typedef std::vector<CAnyGdeDataTrace *> TraceVector;
		typedef TraceVector::iterator trace_itr;
		typedef TraceVector::const_iterator trace_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataTrace();

		/*!
		*
		**/
		virtual ~CAnyGdeDataTrace();

	private:
		//
		CAnyGdeDataTrace(const CAnyGdeDataTrace &other)
		{
			*this = other;
		}
		const CAnyGdeDataTrace &operator=(const CAnyGdeDataTrace &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_sequenceOrder = other.m_sequenceOrder;
			m_lineNo = other.m_lineNo;
			m_cdpNo = other.m_cdpNo;
			m_cmpcount = other.m_cmpcount;
			m_coord = other.m_coord;
			m_minTime = other.m_minTime;
			m_maxTime = other.m_maxTime;
			m_interval = other.m_interval;
			m_minA = other.m_minA;
			m_maxA = other.m_maxA;
			m_maxValue = other.m_maxValue;
			m_minValue = other.m_minValue;
			m_samples = other.m_samples;
			m_children = other.m_children;
			m_isDirty = other.m_isDirty;
			m_hits = other.m_hits;

			return *this;
		}
	public:
		//
		//
		//
		/*!
		*
		**/
		void MakeDirty(bool isDirty)
		{
			m_isDirty = isDirty;
		}

		/*!
		*
		**/
		bool IsDirty()
		{
			return m_isDirty;
		}

		//
		//
		//
		/*!
		*
		**/
		bool IsCover(const CAnyGdeDataTrace &other);

		/*!
		*
		**/
		bool IsCover(double minTime, double maxTime);

		/*!
		*
		**/
		bool IsIntersect(const CAnyGdeDataTrace &other);

		/*!
		*
		**/
		bool IsIntersect(double minTime, double maxTime);

		/*!
		*
		**/
		void Merge(CAnyGdeDataTrace *other, int mergetype = 0, bool changetimerange = true);

		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataTrace *Clone();
				
		/*!
		*
		**/
		CAnyGdeDataTrace *Clone(double mintime, double maxtime);

		//
		//
		//
		/*!
		*
		**/
		void SetSample(double time, double value);

		/*!
		*
		**/
		double GetSample(double time);

		/*!
		*
		**/
		const double *GetSampleData();

		/*!
		*
		**/
		void Clear();
		
		/*!
		*
		**/
		void GetMaxMin();
	public:
		// sequence order
		long m_sequenceOrder;
		// x - xline, y - inline
		double m_lineNo;
		double m_cdpNo;
		int m_cmpcount;
		// coordinate
		CGeoPoint<double> m_coord;

		// time window
		double m_minTime;
		double m_maxTime;
		double m_interval;

		// max and min amplitude of this trace
		double m_minA;
		double m_maxA;
		double m_maxValue;
		double m_minValue;

		// samples inherited from one octree tile
		std::vector<double> m_samples;
		// components
		std::vector<CAnyGdeDataTrace *> m_children;

		// commit status
		bool m_isDirty;
		// frequency called
		long m_hits;
	};
}

#endif
