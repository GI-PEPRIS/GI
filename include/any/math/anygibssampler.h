/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYMATH_GIBS_SAMPLER_H__
#define __ANYMATH_GIBS_SAMPLER_H__

// refer to macro
#include "anymath.h"

// refer to dlib directed graph
#include "dlib/directed_graph.h"
using namespace dlib;

//
#include "any/base/anystl.h"

#include "dlib/bayes_utils.h"
using namespace bayes_node_utils;

namespace AnyMath
{
	/*!
	* given the limited graph number and not no need to sort
	**/
	class ANYMATH_CLASS CAnyGibsSampler
	{
	public:
		// bayesian network
		typedef directed_graph<bayes_node, unsigned short>::kernel_1a DirectedGraph;

		/*!
		*
		**/
		struct NetworkOccurence
		{
			unsigned int m_netIdx;
			std::vector<bool> m_ocurrences; // order as default node id
		};
		typedef std::vector<NetworkOccurence> OnceOccurenceVector;
		typedef std::vector<OnceOccurenceVector> SampleVector;

		//
		struct AnyDirectedGraph
		{
			long m_netIdx;
			DirectedGraph *m_bn;
			std::vector<std::string> m_nodeNames;
		};
		typedef std::vector<AnyDirectedGraph> GraphVector;
		typedef GraphVector::iterator graph_itr;
		typedef GraphVector::const_iterator graph_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGibsSampler();
		~CAnyGibsSampler();

		//
		//
		//
		/*!
		*
		**/
		void AddNetwork(const AnyDirectedGraph &graph);

		/*!
		*
		**/
		void RemoveNetwork(long netIdx, bool isRelease = false);

		/*!
		*
		**/
		void RemoveAll(bool isRelease = false)
		{
			if(isRelease)
			{
				int i = 0;
				for(; i < m_bns.size(); i++)
				{
					delete m_bns[i].m_bn;
				}
			}
			m_bns.erase(m_bns.begin(), m_bns.end());
			m_bns.clear();
		}

		/*!
		*
		**/
		int GetNetworkNumber()
		{
			return m_bns.size();
		}

		/*!
		*
		**/
		void MakeGibsSample(long iterations);

		/*!
		*
		**/
		const OnceOccurenceVector &GetGibsSample(long whichIteration);

		/*!
		*
		**/
		const string GetGraphNodeName(long netIdx, long nodeOrder);

	private:
		// bayes networks
		GraphVector m_bns;
		// simulation number
		long m_iterations;
		// sample
		SampleVector m_gibs;
	};
}

#endif
