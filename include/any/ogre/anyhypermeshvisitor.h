/*!
 * The AnyOGRE of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYOGRE_HYPER_MESH_VISITOR_H__
#define __ANYOGRE_HYPER_MESH_VISITOR_H__

//
#include "any/cgal/anyhypermesh.h"
#include "any/cgal/anyhypermeshiterator.h"
using namespace AnyCGAL;

// refer to EXPORT & IMPORT
#include "anyogre.h"
#include "anyhypermeshcubeviewex.h"
using namespace AnyOGRE;
#include "any/basin/anyhyperbasinsimulator.h"
#include "any/basin/distributedsimulationmodel.h"
using namespace AnyBasin;

// visitor pattern
#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;



//
namespace AnyOGRE
{
	/*!
	*
	**/
	class ANYOGRE_CLASS CAnyHyperMeshVisitor : public BaseVisitor, public Visitor<TYPELIST_1(CAnyHyperMesh)>
	{
	public:
		//
		//
		//
		CAnyHyperMeshVisitor(CAnyHyperMeshCubeViewEx &hypermeshcube);
		~CAnyHyperMeshVisitor();

	public:
		//
		//
		/*!
		*
		**/
		void Visit(CAnyHyperMesh &hypermesh);
		void DoVisit(CDistributedSimulationModel &hypermeshmodel, std::vector<int> &layercolors, \
			CAnyHyperMeshCubeViewEx::HyperOgreMeshContainer &oldmeshes, std::vector<int> &findinolds_simulated, std::vector<std::vector<CGeoPoint<double> > > &cutlines);
		int CheckPtAndLine(const CGeoPoint<double> &pt, CGeoPoint<double> &pt1, CGeoPoint<double> &pt2);
	public:
		//
		CAnyHyperMeshCubeViewEx &m_hyper_mesh_cube;
	};
}


#endif