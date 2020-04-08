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
#ifndef __ANYOGRE_COMPOSITE_VIEW_H__
#define __ANYOGRE_COMPOSITE_VIEW_H__


// refer to EXPORT & IMPORT
#include "anyogre.h"

// refer to parent
#include "anyogresampleview.h"

// 
namespace AnyOGRE
{
	/*!
	*
	**/
	class ANYOGRE_CLASS CAnyCompositeCubeView : public CAnyOgreSampleView
	{
	public:
		//
		//
		//
		CAnyCompositeCubeView(const SetupParameter &setup);
		~CAnyCompositeCubeView();

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
	};
}

#endif
