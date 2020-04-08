/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
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
#ifndef __ANYSDE_SDE_GEOMETRY_LINE_EDITOR_H__
#define __ANYSDE_SDE_GEOMETRY_LINE_EDITOR_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to parent
#include "anysdegeometryeditor.h"

//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnySdeLineEditor : public CAnySdeGeometryEditor
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeLineEditor(CAnyView &curView, CAnySdeGeometryLayer &layer);

		/*!
		*
		**/
		~CAnySdeLineEditor();

	public:

		//
		// behaviors as a view hook
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);

		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);
	};
}

#endif
