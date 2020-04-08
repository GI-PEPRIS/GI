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
#ifndef __ANYOGRE_CONTOUR_CUBE_VIEW_H__
#define __ANYOGRE_CONTOUR_CUBE_VIEW_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

// refer to its parent
#include "anyogresampleview.h"

//
namespace AnyOGRE
{
	class ANYOGRE_CLASS CAnyContourCubeView : public CAnyOgreSampleView
	{
	public:
		/*!
		*
		**/
		struct MeshConstruct
		{
			// mesh name
			string m_name;
			bool m_isshown;
			// faces
			int m_fNumber;
			int *m_faces;
			// vertexes
			int m_vNumber;
			float *m_vertices;
			float *m_values;
			// normals
			float *m_normals;
			// colors
			unsigned int *m_colors;
			float m_alpha;
			// texture
			float *m_tCoords;

			//
			Ogre::MovableObject *m_entity;

			/*!
			*
			**/
			MeshConstruct() : m_isshown(true), m_fNumber(0), m_faces(0), m_vNumber(0), m_vertices(0), m_values(0), m_normals(0), m_colors(0), m_alpha(1), \
				m_tCoords(0), m_entity(0)
			{
			}

			/*!
			*
			**/
			MeshConstruct(const MeshConstruct &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const MeshConstruct &operator=(const MeshConstruct &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// mesh name
				m_name = other.m_name;
				m_isshown = other.m_isshown;
				// faces
				m_fNumber = other.m_fNumber;
				if(m_faces)
				{
					::free(m_faces);
				}
				m_faces = (int *)::malloc(m_fNumber * 3 * sizeof(int));
				::memcpy(m_faces, other.m_faces, m_fNumber * 3 * sizeof(int));

				// vertexes
				m_vNumber = other.m_vNumber;
				if(m_vertices)
				{
					::free(m_vertices);
				}
				m_vertices = (float *)::malloc(m_vNumber * 3 * sizeof(float));
				::memcpy(m_vertices, other.m_vertices, m_vNumber * 3 * sizeof(float));

				if(m_values)
				{
					::free(m_values);
					m_values = 0;
				}
				if(other.m_values)
				{
					m_values = (float *)::malloc(m_vNumber * sizeof(float));
					::memcpy(m_values, other.m_values, m_vNumber * sizeof(float));
				}

				if(m_normals)
				{
					::free(m_normals);
				}
				m_normals = (float *)::malloc(m_vNumber * 3 * sizeof(float));
				::memcpy(m_normals, other.m_normals, m_vNumber * 3 * sizeof(float));

				if(m_colors)
				{
					::free(m_colors);
				}
				m_colors = (unsigned int *)::malloc(m_vNumber * 3 * sizeof(unsigned int));
				::memcpy(m_colors, other.m_colors, m_vNumber * 3 * sizeof(unsigned int));
				m_alpha = other.m_alpha;

				// texture
				if(m_tCoords)
				{
					::free(m_tCoords);
				}
				m_tCoords = (float *)::malloc(m_vNumber * 2 * sizeof(float));
				::memcpy(m_tCoords, other.m_tCoords, m_vNumber * 2 * sizeof(float));

				//
				m_entity = other.m_entity;
				
				return *this;
			}

			/*!
			*
			**/
			bool IsValid()
			{
				if(!m_vNumber || !m_vertices 
					|| m_fNumber || !m_faces)
				{
					return false;
				}

				return true;
			}

			/*!
			*
			**/
			void Release()
			{
				if(m_faces)
				{
					::free(m_faces);
				}
				m_faces = 0;

				if(m_vertices)
				{
					::free(m_vertices);
				}
				m_vertices = 0;

				if(m_values)
				{
					::free(m_values);
				}
				m_values = 0;

				if(m_normals)
				{
					::free(m_normals);
				}
				m_normals = 0;

				if(m_colors)
				{
					::free(m_colors);
				}
				m_colors = 0;

				if(m_tCoords)
				{
					::free(m_tCoords);
				}
				m_tCoords = 0;
			}
		};
		typedef std::vector<MeshConstruct *> MeshVector;

	public:
		/*!
		*
		**/
		CAnyContourCubeView(const MeshVector &meshes, const GeometryVector &geometries, const SetupParameter &setup);
		~CAnyContourCubeView();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool AddMesh(MeshConstruct *mesh);
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
		// meshes
		MeshVector m_meshes;
	};
}
#endif