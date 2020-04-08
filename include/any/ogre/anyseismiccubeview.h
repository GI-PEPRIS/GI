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
#ifndef __ANYOGRE_SEISMIC_CUBE_VIEW_H__
#define __ANYOGRE_SEISMIC_CUBE_VIEW_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

// refer to parent
#include "anyogresampleview.h"

// namespace
namespace AnyOGRE
{
	/*!
	* almost the same as CAnyGisCubeView
	**/
	class ANYOGRE_CLASS CAnySeismicCubeView : public CAnyOgreSampleView
	{
	public:
		/*!
		*
		**/
		struct SeismicCubePlane
		{
			// plane name
			string m_planeName;
			// spatial extent
			CGeoPoint<double> m_corners[4];
			// image
			int m_imageWidth;
			int m_imageHeight;
			unsigned char *m_imageData;
			// quad
			Ogre::MovableObject *m_quad;
			// which gate
			int m_gateoffset;
			string m_cubefeaturename;

			/*!
			*
			**/
			SeismicCubePlane() : m_planeName(""), m_imageWidth(0), m_imageHeight(0), m_imageData(0), m_quad(0), m_gateoffset(0), m_cubefeaturename("")
			{
			}
			/*!
			*
			**/
			SeismicCubePlane(const SeismicCubePlane &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			bool IsValid()
			{
				return m_imageWidth == 0 || 
					m_imageHeight == 0 || 
					m_imageData == 0;
			}

			/*!
			*
			**/
			void Release()
			{
				if(m_imageData)
				{
					::free(m_imageData);
				}
				m_imageData = 0;
			}

			/*!
			*
			**/
			SeismicCubePlane *Clone()
			{
				SeismicCubePlane *cloned = new SeismicCubePlane;
				*cloned = *this;
				return cloned;
			}

			/*!
			*
			**/
			const SeismicCubePlane &operator=(const SeismicCubePlane &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_planeName = other.m_planeName;
				for(int i = 0; i < 4; i++)
					m_corners[i] = other.m_corners[i];
				m_imageWidth = other.m_imageWidth;
				m_imageHeight = other.m_imageHeight;
				if(m_imageData)
				{
					::free(m_imageData);
				}
				m_imageData = (unsigned char *)::malloc(m_imageWidth*m_imageHeight*3);
				::memcpy(m_imageData, other.m_imageData, m_imageWidth*m_imageHeight*3);
				m_gateoffset = other.m_gateoffset;
				m_cubefeaturename = other.m_cubefeaturename;
				return *this;
			}
		};
		typedef std::vector<SeismicCubePlane *> PlaneVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySeismicCubeView(const PlaneVector &planes, const SetupParameter &setup);
		CAnySeismicCubeView(const PlaneVector &planes, const GeometryVector &geometries, const SetupParameter &setup);

		/*!
		*
		**/
		~CAnySeismicCubeView();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool AddPlane(SeismicCubePlane *plane);
		bool RemovePlane(const string &name);
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
		bool DoCreateTexture(int current);
		bool DoCreateMaterial(int current);
		bool DoCreateQuad(int current);

	private:
		//
		PlaneVector m_planes;
	};
}
#endif
