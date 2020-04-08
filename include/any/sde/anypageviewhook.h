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
#ifndef __ANYSDE_SDE_PAGE_VIEWHOOK_H__
#define __ANYSDE_SDE_PAGE_VIEWHOOK_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to its parent
#include "any/map/anyviewhookcomposite.h"
using namespace AnyMap;

using namespace std;
//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnyPageViewHook : public CAnyViewHookComposite
	{
	public:
		/*!
		*
		**/
		struct PageLayout
		{
			// center or ancor point with real map
			// by default the center of current map to be pinted
			CGeoPoint<double> m_center;
			// page physical extent in page coord
			CGeoRect<double> m_extent;
			// current map scale
			int m_scale;
			// map border shrinked from m_pageExtent in page coord
			CGeoRect<double> m_border;
			// compass position in page coord
			CGeoPoint<double> m_compass;
			// scale bar in page coord
			CGeoRect<double> m_bar;
			// title position in page coord
			CGeoPoint<double> m_titlepos;
			CGeoRect<double> m_titleextent;
			std::string m_title;
			AnyMap::LabelStyle m_titlestyle;
			/*!
			*
			**/
			PageLayout() : m_center(ANY_NAN, ANY_NAN), m_extent(ANY_NAN, ANY_NAN, ANY_NAN, ANY_NAN), m_scale(ANY_NAN), \
				m_border(ANY_NAN, ANY_NAN, ANY_NAN, ANY_NAN), m_compass(ANY_NAN, ANY_NAN), m_bar(ANY_NAN, ANY_NAN, ANY_NAN, ANY_NAN),\
				m_titlepos(ANY_NAN, ANY_NAN),m_titleextent(ANY_NAN, ANY_NAN, ANY_NAN, ANY_NAN),m_title(""),m_titlestyle()
			{
			}

			/*!
			*
			**/
			PageLayout(const PageLayout &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const PageLayout &operator=(const PageLayout &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_center = other.m_center;
				m_extent = other.m_extent;
				m_scale = other.m_scale;
				m_border = other.m_border;
				m_compass = other.m_compass;
				m_bar = other.m_bar;
				m_titlepos=other.m_titlepos;
				m_titleextent=other.m_titleextent;
				m_title=other.m_title;
				m_titlestyle=other.m_titlestyle;

				return *this;
			}
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyPageViewHook(CAnyView &view);

		/*!
		*
		**/
		~CAnyPageViewHook();

	public:
		//
		//
		//
		/*!
		*
		**/
		void SetPageLayout(const PageLayout &layout)
		{
			m_layout = layout;
		}

		/*!
		*
		**/
		const PageLayout &GetPageLayout() const
		{
			return m_layout;
		}

		/*!
		*
		**/
		void OnPrint()
		{
			// TODO:
			// ...
		}

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

	public:
		/*!
		*
		**/
		void DoResetMapPort();

		void DoRenderBorderLines(CAnyCanvas &canvas,const CGeoRect<double> mapExtent, int flag, int tickcount);

		void DoRenderGrid(CAnyCanvas &canvas,const CGeoRect<double> mapExtent, int flag, double stepx, double stepy);

		void DoRenderGrid(CAnyCanvas &canvas);
	public:
		// page output schema
		PageLayout m_layout;

		//20171027 draw border axis
		bool m_isdrawborder;
		int m_rowtickcount;
		int m_coltickcount;

		//draw grid
		bool m_isdrawgrid;
		int m_gridtype;
		double m_stepx;
		double m_stepy;
		std::vector<std::vector<CGeoPoint<double>>> m_parallelines;
		std::vector<std::vector<CGeoPoint<double>>> m_verticallines;

		CGeoRect<double> m_titleborder;
		bool m_ismovingtitle;
		// MouseDown position
		CGeoPoint<double> m_startPos;
	};
}
#endif