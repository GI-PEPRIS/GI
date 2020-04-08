/*!
 * The AnyMap of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYMAP_VIEW_HOOK_H__
#define __ANYMAP_VIEW_HOOK_H__

// refer to export macro
#include "anymap.h"

//
#include "anyview.h"
#include "anycanvas.h"

// refer to stl
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include"any/base/anymediator.h"
#include "any/base/loki/visitor.h"
using namespace AnyBase;
using namespace AnyBase::Loki;

//
namespace AnyMap
{
	/*!
	*
	**/
	class ANYMAP_CLASS CAnyViewHook : public BaseVisitable<>
	{
		// relatives
		friend class CAnyViewImpl;
		friend class CWinViewImpl;

	public:
		//
		LOKI_DEFINE_VISITABLE()

		// kinds of functor
		typedef std::map<int, CAnyFunctor*> FunctorMap;
		typedef FunctorMap::iterator func_itr;
		typedef FunctorMap::const_iterator func_citr;

		/*!
		*
		**/
		enum HookFunctorType
		{
			HFT_Unknown = -1,
			HFT_Rendering,
			HFT_Max
		};

		/*!
		* for different categories of geometry rendering
		**/
		struct LayerSelection
		{
			GeometryStyle *m_style;
			std::vector<unsigned long> m_idxes; // empty means the default style of current layer or hook

			/*!
			*
			**/
			LayerSelection() : m_style(0)
			{
			}

			/*!
			*
			**/
			LayerSelection(const LayerSelection &other)
			{
				m_style = 0;
				*this = other;
			}

			/*!
			*
			**/
			~LayerSelection()
			{
				if(m_style)
				{
					delete m_style;
				}
				m_style = 0;
			}

			/*!
			*
			**/
			const LayerSelection &operator=(const LayerSelection &other)
			{
				if(this == &other)
				{
					return *this;
				}

				if(m_style)
				{
					delete m_style;
				}
				m_style = CreateStyle(other.m_style->m_styleType);
				switch(other.m_style->m_styleType)
				{
				case GST_Line:
					{
						*((LineStyle *)m_style) = *((LineStyle *)other.m_style);
					}
					break;
				case GST_Polygon:
					{
						*((PolyStyle *)m_style) = *((PolyStyle *)other.m_style);
					}
					break;
				case GST_Label:
					{
						*((LabelStyle *)m_style) = *((LabelStyle *)other.m_style);
					}
					break;
				case GST_Symbol:
					{
						*((SymbolStyle *)m_style) = *((SymbolStyle *)other.m_style);
					}
					break;
				}

				m_idxes.clear();
				m_idxes.assign(other.m_idxes.begin(), other.m_idxes.end());
				return *this;
			}

			/*!
			* factor method
			**/
			static GeometryStyle *CreateStyle(short type)
			{
				switch(type)
				{
				case GST_Line:
					{
						return new LineStyle;
					}
				case GST_Polygon:
					{
						return new PolyStyle;
					}
				case GST_Label:
					{
						return new LabelStyle;
					}
				case GST_Symbol:
					{
						return new SymbolStyle;
					}
				}

				assert(false);
				return 0;
			}

			/*!
			*
			**/
			static bool CompareIdx(unsigned long first, unsigned long second)
			{
				return first < second;
			}
		};
		typedef std::vector<LayerSelection> SelectionVector;
		typedef SelectionVector::iterator selection_itr;
		typedef SelectionVector::const_iterator selection_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyViewHook(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyViewHook();

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual void Clone(const CAnyViewHook *prototype) = 0;

		/*!
		*
		**/
		CAnyView &GetView()
		{
			return m_curView;
		}

		//
		//
		//
		/*!
		*
		**/
		bool RegisterFunctor(int type, CAnyFunctor *functor);

		/*!
		*
		**/
		void EraseFunctor(int type);

		//
		// map algebra
		//
		/*!
		*
		**/
		virtual CGeoPoint<double> *MakeRasterization(const CGeoRect<double> &extent, const string &field, int rows, int cols)
		{
			return 0;
		}

		//
		// selection and layer display
		//
		/*!
		*
		**/
		virtual bool Query(const CGeoPoint<double> &pt, std::vector<unsigned long> &idxes)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool Query(const CGeoRect<double> &rect, std::vector<unsigned long> &idxes, bool isCircle = false)
		{
			return false;
		}

		/*!
		*
		**/
		virtual bool Query(const std::vector<CGeoPoint<double> > &poly, std::vector<unsigned long> &idxes)
		{
			return false;
		}

		/*!
 		*
		**/
		void SetLayerStyle(GeometryStyle *style);

		/*!
		*
		**/
		const GeometryStyle *GetLayerStyle()
		{
			assert(m_style);
			return m_style;
		}

		/*!
		*
		**/
		void AddSelectionStyle(LayerSelection &selection);

		/*!
		*
		**/
		void SetLightStyle(const LayerSelection &selection);

		/*!
		*
		**/
		void SetLabelStyle(const LabelStyle &labelStyle);

		/*!
		*
		**/
		void ClearLights();

		/*!
		*
		**/
		void ClearSelection();

		/*!
		*
		**/
		const GeometryStyle *GetGeometryStyle(unsigned long idx);

		/*!
		*
		**/
		const LabelStyle &GetLabelStyle()
		{
			return m_labelStyle;
		}

		//
		//
		//
		/*!
		*
		**/
		void SetIdx(long idx)
		{
			m_idx = idx;
		}

		/*!
		*
		**/
		long GetIdx() const
		{
			return m_idx;
		}

		/*!
		*
		**/
		void SetName(const string &name)
		{
			m_name = name;
		}

		/*!
		*
		**/
		const string &GetName() const
		{
			return m_name;
		}

		/*!
		*
		**/
		void SetOrder(int order)
		{
			m_order = order;
		}

		/*!
		*
		**/
		short GetOrder() const
		{
			return m_order;
		}

		/*!
		*
		**/
		void SetSwitch(bool isRender)
		{
			m_isRender = isRender;
		}

		/*!
		*
		**/
		bool IsRendering()
		{
			return m_isRender;
		}

		/*!
		*
		**/
		void SetActive(bool isActivated)
		{
			m_isActivated = isActivated;
		}

		/*!
		*
		**/
		bool IsActivated()
		{
			return m_isActivated;
		}

		//
		//
		//
		/*!
		*
		**/
		virtual void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false) = 0;

		//
		//
		//
		/*!
		*
		*/
		virtual bool MouseDown(const CGeoPoint<double> &scrPoint) = 0;

		/*!
		*
		*/
		virtual bool MouseMove(const CGeoPoint<double> &scrPoint) = 0;

		/*!
		*
		*/
		virtual bool MouseUp(const CGeoPoint<double> &scrPoint) = 0;

		/*!
		*
		**/
		virtual bool DoubleClick(const CGeoPoint<double> &scrPoint) = 0;

	protected:
		// hook idx
		long m_idx;
		// hook name
		string m_name;
		// rendering order
		short m_order;
		// is rendered
		bool m_isRender;
		// is activated
		bool m_isActivated;

		// layer display
		SelectionVector m_selections;
		LayerSelection m_lights;
		GeometryStyle *m_style; // defauly layer style
		LabelStyle m_labelStyle;

		// host view
		CAnyView &m_curView;

		// kinds of callback functor
		FunctorMap m_functors;
	};
}

#endif