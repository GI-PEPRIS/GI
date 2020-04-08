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
#ifndef __ANYOGRE_QUERY_MAN_H__
#define __ANYOGRE_QUERY_MAN_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

//
#include "ogre\Ogre.h"
#include "ois\OIS.h"
using namespace Ogre;

//
namespace AnyOGRE
{
	/*!
	*
	**/
	class ANYOGRE_CLASS CAnyOgreQueryMan
	{
		//
		friend class CAnyOgreSampleView;

	public:
		//
		enum QueryType
		{
			QT_Unknown,
			QT_Plane,
			QT_AABB,
			QT_Sphere,
			QT_Max
		};

		/*!
		*
		**/
		class SelectionBox : public Ogre::ManualObject
		{
		public :
			SelectionBox(const Ogre::String& name);
			~SelectionBox(void);
 
			void setCorners(float left, float top, float right, float bottom);
			void setCorners(const Ogre::Vector2& topLeft, const Ogre::Vector2& topRight);
		};
 
	public:
		CAnyOgreQueryMan(short qureyType, Ogre::SceneManager* sceneMgr, Ogre::Camera* camera);
		~CAnyOgreQueryMan();

	public:
		//
		//
		//
		virtual bool mouseMoved(const OIS::MouseEvent& arg);
		virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
 
		//
		//
		//
		void performSelection(const Ogre::Vector2& first, const Ogre::Vector2& second);
		void deselectObjects();
		void selectObject(Ogre::MovableObject* obj);
		
	private:
		//
		static void swap(float& x, float& y)
		{
			float temp = x;
			x = y;
			y = temp;
		}

	protected:
		// scene manager for this sample
	    Ogre::SceneManager* m_sceneMgr;
		// main camera
		Ogre::Camera* m_camera; 

		//
		Ogre::Vector2 m_start;
		Ogre::Vector2 m_stop;
		Ogre::PlaneBoundedVolumeListSceneQuery *m_volQuery;
		std::vector<Ogre::MovableObject*> m_selected;
		bool m_isSelecting;
		SelectionBox *m_selectionBox;
	};
}
#endif
