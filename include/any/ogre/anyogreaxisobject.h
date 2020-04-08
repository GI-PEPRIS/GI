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
#ifndef __ANYOGRE_OGRE_AXIS_OBJECT_H__
#define __ANYOGRE_OGRE_AXIS_OBJECT_H__

//
#include "anyogre.h"

//
#include "ogre\Ogre.h"
using namespace Ogre;

//
namespace AnyOGRE
{
	class ANYOGRE_CLASS CAnyOgreAxisObject
	{
	public:
		enum BoxParts
		{
			BOX_NONE			= 0x00,
			BOX_TOP			= 0x01,
			BOX_BOT			= 0x02,
			BOX_FRONT		= 0x04,
			BOX_BACK			= 0x08,
			BOX_LEFT			= 0x10,
			BOX_RIGHT		= 0x20,
			BOX_ALL			= 0xFF
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyOgreAxisObject();
		~CAnyOgreAxisObject();

	public:
		//
		//
		//
		/*!
		*
		**/
	    Ogre::ManualObject *CreateAxis(Ogre::SceneManager *scene, const Ogre::String &name, Ogre::Real scale);

	private:
		//
		//
		//
		/*!
		*
		**/
		void AddMaterial(const Ogre::String& mat, Ogre::ColourValue &clr, Ogre::SceneBlendType sbt);
		void AddBox(Ogre::ManualObject* obj, Ogre::Vector3 dim, Ogre::Vector3 pos, Ogre::ColourValue color, short boxMask);
	};
}
#endif
