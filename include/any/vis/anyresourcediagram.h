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
#ifndef __ANYVIS_ASSESSMENT_RESOURCE_DIAGRAM_H__
#define __ANYVIS_ASSESSMENT_RESOURCE_DIAGRAM_H__

// refer to macro
#include "anyvis.h"

// refer to view hook
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to axis parent
#include "anyaxises.h"

// refer to geometry basic
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to exceedence mode
#include "any/math/anydistributionstrategy.h"
using namespace AnyMath;

//
namespace AnyVis
{
	class ANYVIS_CLASS CAnyResourceDiagram : public CAnyViewHook, private CAnyAxises
	{
	public:
		/*!
		*
		**/
		struct ExceedenceResource
		{
			long m_idx;
			string m_name;
			double m_resource;

			/*!
			*
			**/
			ExceedenceResource() : m_idx(0), m_name(""), m_resource(0.)
			{
			}

			/*!
			*
			**/
			const ExceedenceResource &operator=(const ExceedenceResource &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx = other.m_idx;
				m_name = other.m_name;
				m_resource = other.m_resource;

				return *this;
			}
		};
		typedef std::vector<ExceedenceResource> ResourceGroup;
		typedef std::vector<ResourceGroup > ResourceVector;

		// for kinds of geological scene
		struct SegmentProbability
		{
			double m_individual;
			double m_together;

			/*!
			*
			**/
			const SegmentProbability &operator=(const SegmentProbability &other)
			{
				m_individual = other.m_individual;
				m_together = other.m_together;
			}
		};
		typedef std::map<string, SegmentProbability> ProbabilityMap;
		typedef ProbabilityMap::iterator prob_itr;
		typedef ProbabilityMap::const_iterator prob_citr;

		/*!
		*
		**/
		struct ExceedenceProbability
		{
			double m_maturity;
			ProbabilityMap m_map;

			/*!
			*
			**/
			ExceedenceProbability() : m_maturity(0.)
			{
			}

			/*!
			*
			**/
			const ExceedenceProbability &operator=(const ExceedenceProbability &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_maturity = other.m_maturity;
				m_map.clear();
				prob_citr first = other.m_map.begin();
				prob_citr last = other.m_map.end();
				for(; first != last; first++)
				{
					m_map.insert(ProbabilityMap::value_type(first->first, first->second));
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
		CAnyResourceDiagram(CAnyView &curView);

		/*!
		*
		**/
		~CAnyResourceDiagram();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetResources(ResourceVector &resources, const ExceedenceProbability &probabilities, unsigned short mode = CAnyDistributionStrategy::EM_Midpoints);

		/*!
		*
		**/
		double GetQuantile(double probability);

		/*!
		*
		**/
		double GetMean();

		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

		//
		//
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

	private:
		/*!
		*
		**/
		void DoGetMapPort(CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		static bool CompareResourceVector(ResourceGroup &first, ResourceGroup &second);

	private:
		// resource distribution simulated
		int m_limits;
		ResourceVector m_resources;
		std::vector<double> m_fractiles;	
		// the risk from montecarlo
		ExceedenceProbability m_probabilities;

		// color table
		int m_cursor;
		std::map<int, unsigned int> m_colors; // 
		static std::vector<unsigned int> m_tables; // color table
	};
}
#endif