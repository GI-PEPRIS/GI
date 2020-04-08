/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYVIS_REAL_SYMBOL_PLOT_H__
#define __ANYVIS_REAL_SYMBOL_PLOT_H__

// refer to macro
#include "anyvis.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to geopoint
#include "any/base/anygeom.h"
#include "any/base/anyvectop.h"
using namespace AnyBase;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyRealSymbolPlot : public CAnyViewHook
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyRealSymbolPlot(CAnyView &curView, bool isAllSymbol = true);

		/*!
		*
		**/
		virtual ~CAnyRealSymbolPlot();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		//
 		//
		//
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

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

		//
		//
		//
		/*!
		*
		**/
		void SetMapPort();
		
		/*!
		*
		**/
		unsigned short FindCharacterCode(const CGeoPoint<double> &scrPoint);
	private:
		std::vector<unsigned short> m_ids;//painted character indexes
		std::vector<CGeoRect<double>> m_idRects;//painted character index's position rectangle
		std::vector<unsigned short> m_characters;//all character indexes
	public:
		bool m_isAllSymbol;
		std::string m_fontname;
		int m_page;
		int m_index;
		double m_symbolSize;
		double m_rotation;
		ColorStyle m_color;
	};
}
#endif