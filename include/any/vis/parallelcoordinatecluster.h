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
#ifndef __ANYVIS_PARALLEL_COORDINATE_CLUSTER_H__
#define __ANYVIS_PARALLEL_COORDINATE_CLUSTER_H__

//
#include "any/base/anystl.h"

// refer to PolyLine structure
#include "anyparallelcoordinate.h"

// namespace
namespace AnyVis
{
	/*!
	*
	**/
	class CParallelCoordinateCluster
	{
		//
		typedef std::vector<CAnyParallelCoordinate::PolyLine *> ClusterVector;
		typedef ClusterVector::iterator cluster_itr;
		typedef ClusterVector::const_iterator cluster_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CParallelCoordinateCluster();

		/*!
		*
		**/
		~CParallelCoordinateCluster();

	public:
		//
		//
		//
		/*!
		*
		**/
		void MakeClusters(CAnyParallelCoordinate::PolyLine *lines, int lineNumber, int k, int iterations);

	protected:
		//
		//
		//
		/*!
		*
		**/
		void DoInitClusters(int clusters, CAnyParallelCoordinate::PolyLine *lines, int lineNumber);

		/*!
		*
		**/
		void DoInitCentroids(int clusters);

		/*!
		*
		**/
		void DoResetCentroids();

		/*!
		*
		**/
		void DoGetMeans();

		/*!
		*
		**/
		double DoCalcDistance(CAnyParallelCoordinate::PolyLine *curLine, int curCluster);

		/*!
		*
		**/
		void DoGetMaxMin(double &max, double &min, int curDim);

	private:
		//
		//
		//
		/*!
		*
		**/
		static bool CompareCluster(CAnyParallelCoordinate::PolyLine *first, CAnyParallelCoordinate::PolyLine *second);

	private:
		//
		ClusterVector m_lines;
		// 
		short m_clusters;
		//
		CAnyParallelCoordinate::PolyLine *m_centroids;
		//
		int m_iterations;
	};
}
#endif