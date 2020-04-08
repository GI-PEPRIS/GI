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
#ifndef __ANYOGRE_HYPERMESH_CUBE_VIEW_EX_H__
#define __ANYOGRE_HYPERMESH_CUBE_VIEW_EX_H__

// here to fix  error C2039: 'decVal' : is not a member of 'tagVARIANT::<unnamed-type-n1>::__tagVARIANT::<unnamed-type-n3>'
#include "any/cgal/anyhypermeshiterator.h"
using namespace AnyCGAL;


// refer to EXPORT & IMPORT
#include "anyogre.h"

// refer to its parent
#include "anyogresampleview.h"

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anylightlru.h"
using namespace AnyBase;

//
namespace AnyOGRE
{
	/*!
	*
	**/
	class ANYOGRE_CLASS CAnyHyperMeshCubeViewEx : public CAnyOgreSampleView
	{
	public:
		//
		struct HyperOgreMeshFace
		{
			std::vector<unsigned long> m_vertex_idexes;
			long m_max_idx;				// unique idx 
			long m_material_idx;		// those faces belong to the same category, such as one layer etc
			HyperOgreMeshFace() : m_max_idx(0), m_material_idx(0)
			{
			}
			HyperOgreMeshFace(const HyperOgreMeshFace &other)
			{
				*this = other;
			}
			const HyperOgreMeshFace &operator=(const HyperOgreMeshFace &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_vertex_idexes = other.m_vertex_idexes;
				m_max_idx = other.m_max_idx;
				m_material_idx = other.m_material_idx;
				return *this;
			}
		};
		typedef std::vector<HyperOgreMeshFace *> MeshFaceContainer;

		//
		struct HyperOgreMeshVertex
		{
			CGeoPoint<float> m_value;	
			HyperOgreMeshVertex()
			{
			}
			HyperOgreMeshVertex(const HyperOgreMeshVertex &other)
			{
				*this = other;
			}
			const HyperOgreMeshVertex &operator=(const HyperOgreMeshVertex &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_value = other.m_value;
				return *this;
			}
		};
		typedef std::vector<HyperOgreMeshVertex *> MeshVertexContainer;

		// row col
		struct HyperOgreMeshMeta
		{

		};

		// sub mesh
		//
		struct HyperOgreChildMesh
		{
			//
			int m_child_layer_idx;
			// = horizon idx of hyper mesh
			int m_child_bottom_horizon_idx;	
			int m_child_top_horizon_idx;	
			// ogre inner definition
			std::string m_child_mesh_name;
			bool m_isshown;
			int m_vertexcount;
			int m_facecount;
			// faces
			Ogre::uint32* m_faces;
			// vertices
			float* m_positions;
			// values
			float* m_values;
			// normals
			float* m_normals;
			// colors
			unsigned int* m_colors;
			//
			HyperOgreChildMesh() : m_child_layer_idx(0), m_child_bottom_horizon_idx(0), m_child_top_horizon_idx(0), m_child_mesh_name(""), m_isshown(true), \
				m_vertexcount(0), m_facecount(0), m_faces(0), m_positions(0), m_values(0), m_normals(0), m_colors(0)
			{
			}
			HyperOgreChildMesh(const HyperOgreChildMesh &other)
			{
				*this = other;
			}
			void Release()
			{
				m_vertexcount = 0;
				m_facecount = 0;
				if(m_faces)
					::free(m_faces);
				m_faces = 0;
				if(m_positions)
					::free(m_positions);
				m_positions = 0;
				if(m_values)
					::free(m_values);
				m_values = 0;
				if(m_normals)
					::free(m_normals);
				m_normals = 0;
				if(m_colors)
					::free(m_colors);
				m_colors = 0;
			}
			const HyperOgreChildMesh &operator=(const HyperOgreChildMesh &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_child_layer_idx = other.m_child_layer_idx;
				m_child_bottom_horizon_idx = other.m_child_bottom_horizon_idx;
				m_child_top_horizon_idx = other.m_child_top_horizon_idx;
				m_child_mesh_name = other.m_child_mesh_name;
				m_isshown = other.m_isshown;
				m_vertexcount = other.m_vertexcount;
				m_facecount = other.m_facecount;
				m_faces = other.m_faces;
				m_positions = other.m_positions;
				m_values = other.m_values;
				m_normals = other.m_normals;
				m_colors = other.m_colors;
				return *this;
			}
		};
		typedef std::vector<HyperOgreChildMesh> MeshChildrenContainer;

		// 
		struct HyperOgreLODMesh
		{
			// layer or horizon name
			std::string m_parent_mesh_name;
			// = level of details
			short m_octree_level; 
			// model data
			MeshChildrenContainer m_children_meshes;

			//
			// ogre mesh object which is composed by those children meshes above
			Ogre::MeshPtr m_ogre_mesh;
			Ogre::MaterialPtr m_ogre_material;
			Ogre::MovableObject *m_ogre_entity;
			Ogre::AxisAlignedBox m_ogre_AABB;

			//
			HyperOgreLODMesh() : m_parent_mesh_name(""), m_octree_level(0), m_ogre_entity(0)
			{
			}
			HyperOgreLODMesh(const HyperOgreLODMesh &other)
			{
				*this = other;
			}
			const HyperOgreLODMesh &operator=(const HyperOgreLODMesh &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_parent_mesh_name = other.m_parent_mesh_name;
				m_octree_level = other.m_octree_level;
				m_children_meshes = other.m_children_meshes;
				m_ogre_mesh = other.m_ogre_mesh;
				m_ogre_material = other.m_ogre_material;
				m_ogre_entity = other.m_ogre_entity;
				m_ogre_AABB = other.m_ogre_AABB;
				return *this;
			}
		};
		typedef std::vector<HyperOgreLODMesh> LODMeshContainer;

		//
		enum HyperOgreMeshType
		{
			HOMT_Unknown,
			// for earth model
			HOMT_Static_Layer_Block,
			HOMT_Static_Layer_Contour,
			HOMT_Static_Horizon_Block,
			HOMT_Static_Horizon_Contour,
			// for simulated process
			HOMT_Dynamic_Layer_Block,
			HOMT_Dynamic_Layer_Contour,
			HOMT_Dynamic_Horizon_Block,
			HOMT_Dynamic_Horizon_Contour,
			HOMT_Max
		};
		typedef std::map<HyperOgreMeshType, LODMeshContainer> HyperOgreMeshContainer;
		typedef HyperOgreMeshContainer::iterator ogre_mesh_itr;
		typedef HyperOgreMeshContainer::const_iterator ogre_mesh_citr;

		//
		struct ChildMeshBufferUnit
		{
			// = horizon idx of hyper mesh
			int m_child_layer_idx;	// layer, horizon, contour etc
			int m_child_bottom_horizon_idx;	
			int m_child_top_horizon_idx;	
			// ogre inner definition
			std::string m_child_mesh_name;
			// = level of details
			short m_lod_which_level;
			HyperOgreMeshType m_lod_mesh_type;
			//
			Ogre::SubMesh* m_submesh_cached;
			ChildMeshBufferUnit() : m_child_layer_idx(0), m_child_bottom_horizon_idx(0), m_child_top_horizon_idx(0), m_child_mesh_name(""), \
				m_lod_which_level(0), m_lod_mesh_type(HOMT_Unknown), m_submesh_cached(0)
			{
			}
			ChildMeshBufferUnit(const ChildMeshBufferUnit &other)
			{
				*this = other;
			}
			const ChildMeshBufferUnit &operator=(const ChildMeshBufferUnit &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_child_layer_idx = other.m_child_layer_idx;
				m_child_bottom_horizon_idx = other.m_child_bottom_horizon_idx;
				m_child_top_horizon_idx = other.m_child_top_horizon_idx;
				m_child_mesh_name = other.m_child_mesh_name;
				m_lod_which_level = other.m_lod_which_level;
				m_lod_mesh_type = other.m_lod_mesh_type;
				m_submesh_cached = other.m_submesh_cached;
				return *this;
			}
			 void Delete()
			 {
				 if(m_submesh_cached)
				 {
					 delete m_submesh_cached;
				 }
			 }
		};
		typedef CAnyLightLru<ChildMeshBufferUnit> ChildMeshCache;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyHyperMeshCubeViewEx(const GeometryVector &geometries, const SetupParameter &setup);
		~CAnyHyperMeshCubeViewEx();

	public:
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
		void RemoveAll();

		/*!
		*
		**/
		int GetMovableObjectNumber(unsigned short type);
		Ogre::MovableObject *GetMovableObject(unsigned short type, long order);

		//
		//
		//
		/*!
		*
		**/
		void CreateHyperOgreMesh(HyperOgreMeshType whichmeshtype);
		void SwitchHyperOgreMesh(HyperOgreMeshType whichmeshtype);
		
		//
		//
		//
		/*!
		*
		**/
		void AddChildMesh(HyperOgreMeshType whichmeshtype, int whichlodlevel, HyperOgreChildMesh &hyperchildmesh);
		void DestroyChildMesh(HyperOgreMeshType whichmeshtype, int whichlodlevel, const std::string &childname);

		void UpdateChildMeshVertex(HyperOgreMeshType whichmeshtype, int whichlodlevel, const std::string &childname, std::vector<CGeoPoint<float> > &vertexes);
		void UpdateChildMeshNormal(HyperOgreMeshType whichmeshtype, int whichlodlevel, const std::string &childname, std::vector<CGeoPoint<float> > &normals);
		void UpdateChildMeshColor(HyperOgreMeshType whichmeshtype, int whichlodlevel, const std::string &childname, std::vector<CGeoPoint<float> > &color);
		void UpdateChildMesh(HyperOgreMeshType whichmeshtype, int whichlodlevel, AnyCGAL::IsoVertexIterator &vertexes, int simulatedlayercount, std::vector<int> &layereventmodes, std::vector<int> &layercolors, \
			std::vector<int> &horizonids, std::vector<int> &microlayercount, std::vector<std::vector<CGeoRect<double> > > &diffpart_extent, std::vector<std::vector<int> > &diffpart_geoevent, bool hasscene, bool discrete);
		void UpdateChildMeshCount(HyperOgreMeshType whichmeshtype, int whichlodlevel, int simulatedlayercount, int showmeshorgeometry, std::vector<int> &layergeometrycount, \
			std::vector<int> &layereventmodes, std::vector<int> &microlayercount, bool hasscene, std::vector<bool> &isshown);
		void ChangeLODrate(double lodrate);
		void AddGeometry(std::vector<Vertex3D*> &pts, bool isZDirection = false);
		void DetachAttach(HyperOgreLODMesh &lodmesh);
	private:
		//
		//
		//
		/*!
		* after corresponding visitor got layer and horizon meshes 
		**/
		void DoCreateOgreParentDirectMesh(HyperOgreLODMesh &lodmesh);
		void DoCreateOgreChildDirectMesh(HyperOgreLODMesh &ogreparentmesh, HyperOgreChildMesh &hyperchildmesh);
		void MakeLOD(HyperOgreChildMesh &hyperchildmesh);
		void DoReleaseMesh(HyperOgreLODMesh &ogreparentmesh);

	public:
		// LOD
		short m_lod_levels;
		short m_lod_which_level;
		double m_lodrate;
		std::vector<int> m_lod_vertexoffsets;
		std::vector<int> m_lod_faces;
		int m_mesh_row;
		int m_mesh_col;

		// static or dynamic meshes as buffer also
		HyperOgreMeshType m_current_lod_mesh_type;
		HyperOgreLODMesh *m_current_lod_mesh;
		HyperOgreLODMesh *m_cutface_mesh;
		HyperOgreMeshContainer m_hyper_ogre_meshes;

		// submesh buffer
		ChildMeshCache m_child_meshes_cached; 
	};
}

#endif
