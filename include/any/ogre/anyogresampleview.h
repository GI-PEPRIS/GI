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
#ifndef __ANYOGRE_SAMPLE_VIEW_H__
#define __ANYOGRE_SAMPLE_VIEW_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

//
#include "ogre\Ogre.h"
#include "ogre\OgreFrameListener.h"
#include "ogre\overlay\OgreOverlaySystem.h"
#include "ois\OIS.h"
#include "anyogremovabletext.h"
using namespace Ogre;

// refer to camera man
#include "anycameraman.h"
//
#include "anyogrequeryman.h"

// refer to cgeopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

// namespace
namespace AnyOGRE
{
	/*!
	* complex scene in composite mode
	**/
	class ANYOGRE_CLASS CAnyOgreSampleView : public FrameListener, public OIS::MouseListener, public OIS::KeyListener  
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		enum CubeOperationType
		{
			COT_Unknown	= 0,
			COT_Camera	= 1,
			COT_Query		= 1 << 1,
			COT_Mask		= 0xFFFFFFFF
		};

		/*!
		*
		**/
		enum CubeConstructType
		{
			CCT_Unknown,
			CCT_Geometry,
			CCT_Well_Trace,
			CCT_Seismic_Plane,
			CCT_Contour_Mesh,
			CCT_GIS_Layer,
			CCT_Tick,
			CCT_Max
		};

		enum ViewType
		{
			View_gislayer,
			View_contour,
			View_composite,
			View_magic,
			View_scatter,
			View_seismic,
			View_hypermesh,
		};

		/*!
		*
		**/
		struct GeometryConstruct
		{
			// basics
			string m_name;
			string m_label;
			bool m_isshown;
			int m_type;	// OT_POINT_LIST, OT_LINE_STRIP, OT_TRIANGLE_LIST
			// verices
			int m_vNumber;
			float *m_vertices;
			unsigned int *m_colors;

			// faces for polygon
			int m_fNumber;
			int *m_faces;

			//
			ManualObject *m_entity;

			/*!
			*
			**/
			GeometryConstruct() : m_name(""), m_isshown(true), m_label(""), m_vNumber(0), m_vertices(0), m_colors(0), m_fNumber(0), m_faces(0), m_entity(0)
			{
			}

			/*!
			*
			**/
			GeometryConstruct(GeometryConstruct &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const GeometryConstruct &operator=(GeometryConstruct &other)
			{
				if(this == &other)
				{
					return *this;
				}

				// basics
				m_name = other.m_name;
				m_isshown = other.m_isshown;
				m_label = other.m_label;
				m_type = other.m_type;	// OT_POINT_LIST, OT_LINE_STRIP, OT_TRIANGLE_LIST

				// verices
				m_vNumber = other.m_vNumber;
				if(m_vertices)
				{
					::free(m_vertices);
				}
				m_vertices = (float *)::malloc(m_vNumber * sizeof(float) * 3);
				::memcpy(m_vertices, other.m_vertices, m_vNumber * sizeof(float) * 3);

				// faces
				m_fNumber = other.m_fNumber;
				if(m_faces)
				{
					::free(m_faces);
				}
				m_faces = (int *)::malloc(m_vNumber * sizeof(int) * 3);
				::memcpy(m_faces, other.m_faces, m_vNumber * sizeof(int) * 3);

				return *this;
			}

			/*!
			*
			**/
			void Release()
			{
				if(m_vertices)
				{
					::free(m_vertices);
				}
				m_vertices = 0;

				if(m_colors)
				{
					::free(m_colors);
				}
				m_colors = 0;

				if(m_faces)
				{
					::free(m_faces);
				}
				m_faces = 0;
			}
		};
		typedef std::vector<GeometryConstruct *> GeometryVector;

		/*!
		*
		**/
		struct ColorCode
		{
			CGeoPoint<double> m_startpt;
			CGeoPoint<double> m_endpt;
			std::vector<double> m_values;
			std::vector<int> m_colors;
			ColorCode(){}
			ColorCode(const ColorCode &other)
			{
				*this = other;
			}
			const ColorCode &operator=(const ColorCode &other)
			{
				if(this == &other)
					return *this;
				m_startpt = other.m_startpt;
				m_endpt = other.m_endpt;
				m_values = other.m_values;
				m_colors = other.m_colors;
				return *this;
			}
		};

	public:
		/*!
		*
		**/
		struct SetupParameter
		{
			// render system
			string m_renderSystem;
			// camera style
			short m_cameraStyle;
			// current or host window
			void *m_hWnd;
			// parent wnd of current
			void *m_hParentWnd;
			// cube extent
			CGeoPoint<double> m_cubecorners[8];
			// own extent
			CGeoPoint<double> m_owncorners[8];

			CGeoPoint<double> m_camerapos;
			CGeoPoint<double> m_cameradirection;

			int m_polygonmode; 

			/*!
			*
			**/
			SetupParameter() : m_renderSystem("OpenGL Rendering Subsystem"), m_cameraStyle(CAnyCameraMan::CS_ORBIT), m_hWnd(0), m_hParentWnd(0)
			{
				m_camerapos.m_x = 0;
				m_camerapos.m_x = 0;
				m_camerapos.m_x = 150;
				m_cameradirection.m_x = 0;
				m_cameradirection.m_x = 0;
				m_cameradirection.m_x = -1;
				m_polygonmode = PM_SOLID;
			}

			/*!
			*
			**/
			SetupParameter(const SetupParameter &setup)
			{
				*this = setup;
			}

			/*!
			*
			**/
			const SetupParameter &operator=(const SetupParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_renderSystem = other.m_renderSystem;
				m_cameraStyle = other.m_cameraStyle;
				m_hWnd = other.m_hWnd;
				m_hParentWnd = other.m_hParentWnd;
				for(int i = 0; i < 8; i++)
					m_cubecorners[i] = other.m_cubecorners[i];
				for(int i = 0; i < 8; i++)
					m_owncorners[i] = other.m_owncorners[i];
				m_camerapos = other.m_camerapos;
				m_cameradirection = other.m_cameradirection;
				m_polygonmode = other.m_polygonmode;

				return *this;
			}

			/*!
			*
			**/
			void GetCubeExtent(double &xmin, double &xmax, double &ymin, double &ymax, double &zmin, double &zmax)
			{
				for(int i = 0; i < 8; i++)
				{
					if(i == 0)
					{
						xmin = xmax = m_cubecorners[i].m_x;
						ymin = ymax = m_cubecorners[i].m_y;
						zmin = zmax = m_cubecorners[i].m_z;
					}
					if(xmin > m_cubecorners[i].m_x)
						xmin = m_cubecorners[i].m_x;
					if(xmax < m_cubecorners[i].m_x)
						xmax = m_cubecorners[i].m_x;
					if(ymin > m_cubecorners[i].m_y)
						ymin = m_cubecorners[i].m_y;
					if(ymax < m_cubecorners[i].m_y)
						ymax = m_cubecorners[i].m_y;
					if(zmin > m_cubecorners[i].m_z)
						zmin = m_cubecorners[i].m_z;
					if(zmax < m_cubecorners[i].m_z)
						zmax = m_cubecorners[i].m_z;
				}
			}

			/*!
			*
			**/
			void GetOwnExtent(double &xmin, double &xmax, double &ymin, double &ymax, double &zmin, double &zmax)
			{
				for(int i = 0; i < 8; i++)
				{
					if(i == 0)
					{
						xmin = xmax = m_owncorners[i].m_x;
						ymin = ymax = m_owncorners[i].m_y;
						zmin = zmax = m_owncorners[i].m_z;
					}
					if(xmin > m_owncorners[i].m_x)
						xmin = m_owncorners[i].m_x;
					if(xmax < m_owncorners[i].m_x)
						xmax = m_owncorners[i].m_x;
					if(ymin > m_owncorners[i].m_y)
						ymin = m_owncorners[i].m_y;
					if(ymax < m_owncorners[i].m_y)
						ymax = m_owncorners[i].m_y;
					if(zmin > m_owncorners[i].m_z)
						zmin = m_owncorners[i].m_z;
					if(zmax < m_owncorners[i].m_z)
						zmax = m_owncorners[i].m_z;
				}
			}

			/*!
			*
			**/
			void SetCubeCornersByExtent(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
			{
				/*
						   1-------2
						  /|      /|
						 / |     / |
						0-------3  |
						|  5----|--6
						| /     | /
						|/      |/
						4-------7
				*/
				m_cubecorners[0].m_x = m_cubecorners[1].m_x = m_cubecorners[4].m_x = m_cubecorners[5].m_x = xmin;
				m_cubecorners[2].m_x = m_cubecorners[3].m_x = m_cubecorners[6].m_x = m_cubecorners[7].m_x = xmax;
				m_cubecorners[0].m_y = m_cubecorners[3].m_y = m_cubecorners[4].m_y = m_cubecorners[7].m_y = ymin;
				m_cubecorners[1].m_y = m_cubecorners[2].m_y = m_cubecorners[5].m_y = m_cubecorners[6].m_y = ymax;
				m_cubecorners[4].m_z = m_cubecorners[5].m_z = m_cubecorners[6].m_z = m_cubecorners[7].m_z = zmin;
				m_cubecorners[0].m_z = m_cubecorners[1].m_z = m_cubecorners[2].m_z = m_cubecorners[3].m_z = zmax;
			}
				
			/*!
			*
			**/
			void SetOwnCornersByExtent(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
			{
				/*
						   1-------2
						  /|      /|
						 / |     / |
						0-------3  |
						|  5----|--6
						| /     | /
						|/      |/
						4-------7
				*/
				m_owncorners[0].m_x = m_owncorners[1].m_x = m_owncorners[4].m_x = m_owncorners[5].m_x = xmin;
				m_owncorners[2].m_x = m_owncorners[3].m_x = m_owncorners[6].m_x = m_owncorners[7].m_x = xmax;
				m_owncorners[0].m_y = m_owncorners[3].m_y = m_owncorners[4].m_y = m_owncorners[7].m_y = ymin;
				m_owncorners[1].m_y = m_owncorners[2].m_y = m_owncorners[5].m_y = m_owncorners[6].m_y = ymax;
				m_owncorners[4].m_z = m_owncorners[5].m_z = m_owncorners[6].m_z = m_owncorners[7].m_z = zmin;
				m_owncorners[0].m_z = m_owncorners[1].m_z = m_owncorners[2].m_z = m_owncorners[3].m_z = zmax;
			}

			/*!
			*
			**/
			void GetCubeEdge(int order, CGeoPoint<double> &pt1, CGeoPoint<double> &pt2)
			{
				if(order == 0)
				{
					pt1 = m_cubecorners[0];
					pt2 = m_cubecorners[4];
				}
				else if(order == 1)
				{
					pt1 = m_cubecorners[1];
					pt2 = m_cubecorners[5];
				}
				else if(order == 2)
				{
					pt1 = m_cubecorners[2];
					pt2 = m_cubecorners[6];
				}
				else if(order == 3)
				{
					pt1 = m_cubecorners[3];
					pt2 = m_cubecorners[7];
				}
				else if(order == 4)
				{
					pt1 = m_cubecorners[0];
					pt2 = m_cubecorners[3];
				}
				else if(order == 5)
				{
					pt1 = m_cubecorners[1];
					pt2 = m_cubecorners[2];
				}
				else if(order == 6)
				{
					pt1 = m_cubecorners[4];
					pt2 = m_cubecorners[7];
				}
				else if(order == 7)
				{
					pt1 = m_cubecorners[5];
					pt2 = m_cubecorners[6];
				}
				else if(order == 8)
				{
					pt1 = m_cubecorners[0];
					pt2 = m_cubecorners[1];
				}
				else if(order == 9)
				{
					pt1 = m_cubecorners[2];
					pt2 = m_cubecorners[3];
				}
				else if(order == 10)
				{
					pt1 = m_cubecorners[4];
					pt2 = m_cubecorners[5];
				}
				else if(order == 11)
				{
					pt1 = m_cubecorners[6];
					pt2 = m_cubecorners[7];
				}
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyOgreSampleView(const SetupParameter &setup);

		/*!
		*
		**/
		virtual ~CAnyOgreSampleView();

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual bool SetupOgre(const SetupParameter &setup);
		virtual bool Shutdown();

		//
		//
		//
		virtual bool CreateScene();
		virtual void DoCreateScene() = 0;
		virtual void DoAttachObject();
		virtual void DoDetachObject();
		virtual void DoCreateAxis();
		virtual bool SelectRenderSystem(const string &renderSystem);
		virtual bool CreateRenderWindow();
		virtual bool CreateSceneManager();
		virtual bool CreateCamera(int cameraStyle);
		virtual bool CreateViewPort();
		virtual bool SetupInputManager();
		virtual bool CleanupContent();
		virtual bool UnloadResources();
		virtual bool LoadResources();

		//
		// callback interface copied from various listeners
		//
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);

		//
		//
		//
		virtual void OnPaint();
		virtual void OnSize(int width, int height);
		virtual void OnMouseMove(short type, CGeoPoint<double> &scrPt);
		virtual void OnMouseDown(short type, CGeoPoint<double> &scrPt);
		virtual void OnMouseUp(short type, CGeoPoint<double> &scrPt);
		virtual void OnMouseWheel(bool isPositive);
		virtual void OnKeyDown(long keycode);
		virtual void OnKeyUp(long keycode);

		//
		//
		//
		bool mouseMoved(const OIS::MouseEvent &e);  
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);   
		bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);  
		bool keyPressed(const OIS::KeyEvent &e);  
		bool keyReleased(const OIS::KeyEvent &e);  
		void restoreCameraPosition();

		//
		//
		//
		void SetOperationType(unsigned int type)
		{
			m_manType = type; 
		}
		unsigned int GetOperationType()
		{
			return m_manType;
		}
		int GetSelectedCount()
		{
			return m_queryMan->m_selected.size();
		}
		Ogre::MovableObject *GetSelectedObject(int order)
		{
			assert(m_queryMan && order >= 0 && order < m_queryMan->m_selected.size());
			return m_queryMan->m_selected[order];
		}

		//
		//
		//
		void SwitchCubeScene();
		void *GetBMP();
		void ReleaseGeometries();
		void ReleaseTicks();
		void ReleaseTickLabels();

		//
		// functions for composite
		//
		virtual int GetMovableObjectNumber(unsigned short type);
		virtual Ogre::MovableObject *GetMovableObject(unsigned short type, long order);
		bool AddChildren(CAnyOgreSampleView *cube);
		bool RemoveChildren(const string &name);
		short GetChildrenNumber();
		CAnyOgreSampleView *GetChildren(short order);
		CAnyOgreSampleView *GetChildren(const string &name);
		bool GetChildrenShown(const string &name);
		void SetChildrenShown(const string &name, bool isshown);
		void UpdateChildrenRanges();

		//
		//
		//
		static Ogre::Vector2 GetScreenspaceCoords(const Vector3& iPoint, const Camera& iCamera);
		double GetDoubleFloor(double val);

	protected:
		//
		//
		//
		void DestroyAllAttachedMovableObjects(SceneNode* node);
		void DestroySceneNode(Ogre::SceneNode* node);

	public:
		// setup parameter
		SetupParameter m_setup;
		// cube resolution in screen 
		Ogre::Vector3 m_cubePort; 
		bool m_isxyscale;//是否xy方向保持形状
		bool m_isxyzscale;//是否xyz方向保持形状
		bool m_isverticalmode;//是否将切片旋转90度

		// is first draw
		bool m_isFirstDraw;
		bool m_isFirstFontload;

		 // OGRE root object
		Ogre::Root *m_root;    
		// Overlay system
		Ogre::OverlaySystem* m_overlaySystem;  
		// context render window
		Ogre::RenderWindow* m_window;
		// scene manager for this sample
		Ogre::SceneManager* m_sceneMgr;
		// main viewport
		Ogre::Viewport* m_viewport;    		
		// main camera
		Ogre::Camera* m_camera; 

		// operation type
		unsigned int m_manType;
		// camera man
		CAnyCameraMan *m_cameraMan;
		double m_orbitratex;
		double m_orbitratey;
		double m_freelookratex;
		double m_freelookratey;
		double m_wheelratemin;
		double m_wheelratemax;
		// query man
		CAnyOgreQueryMan *m_queryMan;

		// event 
		OIS::Keyboard* m_keyboard;        
		OIS::Mouse* m_mouse;              
		OIS::InputManager* m_inputManager;
		CGeoPoint<double> m_lastscrPt;

		// bounding
		Ogre::AxisAlignedBox m_boundingBox;
		bool m_showqueryobjboundingBox;
		Ogre::AxisAlignedBox m_queryobjboundingBox;
		string m_queryobjboundingBoxname;

		// scene in composite mode
		CAnyOgreSampleView *m_sceneParent;
		Ogre::SceneNode *m_sceneNode;
		string m_sceneName;
		int m_viewtype;
		Ogre::Vector3 m_scenePosition;

		// geometry primitives
		GeometryVector m_geometries;

		// axis ticks, edges, grids
		GeometryVector m_ticks;
		std::vector<SceneNode*> m_ticklabels;
		std::vector<ColorCode> m_colorcodes;
		int m_ticktype; //0:按数量,1:按间隔
		bool m_zlabelinverse;
		bool m_zdatainverse;
		int m_xaxiscount;
		int m_yaxiscount;
		int m_zaxiscount;
		double m_xaxisinterval;
		double m_yaxisinterval;
		double m_zaxisinterval;
		int m_axisred;
		int m_axisgreen;
		int m_axisblue;
		int m_edgered;
		int m_edgegreen;
		int m_edgeblue;
		bool m_isshowgrid;
		int m_xgridcount;
		int m_ygridcount;
		int m_zgridcount;
		int m_gridred;
		int m_gridgreen;
		int m_gridblue;
		string m_fontName;
		int m_fontsize;
		int m_fontresolution;
		int m_labelred;
		int m_labelgreen;
		int m_labelblue;
		double m_labelheight;
		double m_labelwidth;
		int m_labelhoralign;
		int m_labelveralign;
		bool m_labeltop;
		bool m_isshowcenteraxis;
		Ogre::ColourValue m_ambientlight;
		Ogre::ColourValue m_diffusecolor;
		Ogre::ColourValue m_specularcolor;
		int m_lighttype;
		CGeoPoint<double> m_lightposition;
		CGeoPoint<double> m_lightdirection;

		// compositee
		std::vector<CAnyOgreSampleView *> m_children;
		std::vector<bool> m_childrenshown;
		CAnyOgreSampleView *m_parent;

		// against different render window
		static CAnyOgreSampleView *m_current;
		static int m_winIdx;
		static int m_constructIdx;
	};
}
#endif
