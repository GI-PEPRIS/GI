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
#ifndef __ANYOGRE_HYPERMESH_CUBE_VIEW_H__
#define __ANYOGRE_HYPERMESH_CUBE_VIEW_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

#include "any/cgal/anyhypermeshbasic.h"
#include "any/cgal/anyhypermeshiterator.h"
using namespace AnyCGAL;
// refer to its parent
#include "anyogresampleview.h"
#include "anycontourcubeview.h"

//
namespace AnyOGRE
{
	class ANYOGRE_CLASS CAnyHyperMeshCubeView : public CAnyOgreSampleView
	{
	public:
		class UpdateVertexTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			UpdateVertexTask(int taskcount, int index, CAnyHyperMeshCubeView *parent, IsoVertexIterator &vertexes, std::vector<int> &layercolors, std::vector<VertexTopoContainer> &vertex_relations, CAnyCPUScheduler *scheduler);
			~UpdateVertexTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyHyperMeshCubeView *m_parent;
			IsoVertexIterator &m_vertexes;
			std::vector<int> &m_layercolors;
			std::vector<VertexTopoContainer> &m_vertex_relations;
			CAnyCPUScheduler *m_scheduler;
		};
		class UpdateMeshTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			UpdateMeshTask(int taskcount, int index, CAnyHyperMeshCubeView *parent, IsoMeshIterator &meshes, CAnyCPUScheduler *scheduler);
			~UpdateMeshTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyHyperMeshCubeView *m_parent;
			IsoMeshIterator &m_meshes;
			CAnyCPUScheduler *m_scheduler;
		};
	public:
		/*!
		*
		**/
		CAnyHyperMeshCubeView(const CAnyContourCubeView::MeshVector &meshes, const GeometryVector &geometries, const SetupParameter &setup);
		~CAnyHyperMeshCubeView();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool AddMesh(CAnyContourCubeView::MeshConstruct *mesh);
		bool RemoveMesh(const string &name);
		void RemoveAll();

		//
		//
		//
		/*!
		*
		**/
		void DoCreateScene();
		void DoAttachObject();
		void DoDetachObject();
		bool CleanupContent();

		//
		//
		//
		/*!
		*
		**/
		int GetMovableObjectNumber(unsigned short type);
		Ogre::MovableObject *GetMovableObject(unsigned short type, long order);

	private:
		//
		//
		//
		/*!
		*
		**/
		bool DoComposeMesh(int cur);
		bool DoCreateMesh(int cur);
		bool DoCreateMaterial(int cur);
	public:
		//
		//
		//
		/*!
		*
		**/
		void DoTempRefresh(int solidlayer, int microlayer, int showmeshorgeometry, std::vector<int> &layercolors);

		// deprecated
		void UpdateVertex(IsoVertexIterator &vertexes, std::vector<int> &layercolors, std::vector<VertexTopoContainer> &vertex_relations);
		void UpdateVertex(IsoVertexIterator &vertexes);
		void UpdateMesh(IsoMeshIterator &meshes);
		void AddGeometry(std::vector<Vertex3D*> &pts, bool isZDirection = false);
		void GetMeshPtsAndFaces(int layer, int microlayer, std::vector<int> &layercolors, IsoMeshIterator &meshes, IsoVertexIterator &vertexes, std::vector<VertexTopoContainer> &vertex_relations);
	public:
		// meshes
		CAnyContourCubeView::MeshVector m_meshes;
		std::vector<int> m_layervertexcount;
		std::vector<int> m_layermeshcount;
		std::vector<int> m_layergeometrycount;
		std::vector<int> m_microlayercount;
		std::vector<int> m_layereventmodes;
		std::vector<std::vector<CGeoRect<double> > > m_diffpart_extent;
		std::vector<std::vector<int> > m_diffpart_geoevent;
		bool m_isgradient;
		unsigned char m_mesh_type;
		bool m_islod;
		int m_lodnum;
		int m_lodindex;
	};
}
#endif