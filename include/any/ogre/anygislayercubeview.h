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
#ifndef __ANYOGRE_GISLAYER_CUBE_VIEW_H__
#define __ANYOGRE_GISLAYER_CUBE_VIEW_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

// refer to parent
#include "anyogresampleview.h"

// namespace 
namespace AnyOGRE
{
	/*!
	*
	**/
	class ANYOGRE_CLASS CAnyGisLayerCubeView : public CAnyOgreSampleView
	{
	public:
		/*!
		*
		**/
		struct LayerConstruct
		{
			// layer name
			string m_layerName;
			// spatial extent, here z may play sense
			CGeoRect<double> m_extent;
			// depth
			double m_depth;
			// image width
			int m_imageWidth;
			// image height
			int m_imageHeight;
			// image data
			unsigned char *m_imageData;

			// quad
			Ogre::MovableObject *m_quad;

			/*!
			*
			**/
			LayerConstruct() : m_layerName(""), m_imageWidth(0), m_imageHeight(0), m_imageData(0), m_quad(0), m_depth(0)
			{
			}

			/*!
			*
			**/
			LayerConstruct(const LayerConstruct &other)
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
			LayerConstruct *Clone()
			{
				LayerConstruct *cloned = new LayerConstruct;
				*cloned = *this;
				return cloned;
			}

			/*!
			*
			**/
			const LayerConstruct &operator=(const LayerConstruct &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_layerName = other.m_layerName;
				m_extent = other.m_extent;
				m_depth = other.m_depth;
				m_imageWidth = other.m_imageWidth;
				m_imageHeight = other.m_imageHeight;
				if(m_imageData)
				{
					::free(m_imageData);
				}
				m_imageData = (unsigned char *)::malloc(m_imageWidth*m_imageHeight*3);
				::memcpy(m_imageData, other.m_imageData, m_imageWidth*m_imageHeight*3);

				return *this;
			}
		};
		typedef std::vector<LayerConstruct *> LayerVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGisLayerCubeView(const LayerVector &layers, const SetupParameter &setup);
		~CAnyGisLayerCubeView();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool AddLayer(LayerConstruct *layer);
		bool RemoveLayer(const string &name);
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
		// directly in raster
		LayerVector m_layers;
	};
}
#endif

