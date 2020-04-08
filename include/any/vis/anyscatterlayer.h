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
#ifndef __ANYVIS_SCATTER_LAYER_H__
#define __ANYVIS_SCATTER_LAYER_H__

// refer to export macroes
#include "anyscattermatrix.h"

#include "any/base/anymediator.h"
using namespace AnyBase;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyScatterLayer : public CAnyViewHook, public CAnyObservable
	{
	public:
		struct ScatterLayer
		{
			CAnyScatterMatrix *m_scatter;

			//infor
			CGeoPoint <double> m_mapPt;

			double m_width;
			double m_height;

			/*!
			*
			**/
			ScatterLayer() : m_width(10.), m_height(10.),m_scatter(0)
			{
			}

			~ScatterLayer()
			{
				Release();
			}

			/*!
			*
			**/
			const ScatterLayer &operator=(const ScatterLayer *other)
			{
				if(this == other)
				{
					return *this;
				}

				Release();

				m_scatter = other->m_scatter;

				m_mapPt = other->m_mapPt;
				m_width = other->m_width;
				m_height = other->m_height;
				
				return *this;
			}

			/*!
			*
			**/
			void Release()
			{
				if (m_scatter)
				{
					delete m_scatter;
					m_scatter = 0;
				}
			}
		};

		typedef std::vector<ScatterLayer *> ScatterVector;
		typedef ScatterVector::iterator s_itr;
		typedef ScatterVector::const_iterator s_citr;
	
	public:
		/*!
		*
		**/
		CAnyScatterLayer(CAnyView &curView);

		/*!
		*
		**/
		~CAnyScatterLayer();

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
		**/
		void AddScatterLayer(const ScatterLayer * layer);

		/*!
		*
		**/
		void UpdateScatterLayer(const ScatterLayer * layer);

		/*!
		*
		**/
		void RemoveScatterLayer(const ScatterLayer * layer);

		/*!
		*
		**/
		int GetScatterLayerCount();
		
		/*!
		*
		**/
		ScatterLayer *GetScatterLayer(int order);
		
		/*!
		*
		**/
		ScatterLayer *GetScatterLayer(const string &name);
		
		/*!
		*2018/4/8: release
		**/
		void Release();

		//
 		// layer's functions
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
		// observer design pattern
		//
        /*!
        * Let sub-class have its specified event types
        */
        void Notify(short type);

        /*!
        *
        */
        void Register(CAnyObserver *oneObserver);

	private:
		// layers
		ScatterVector m_scatters;

		// observer
		CAnyObserver *m_observer;
	};
}

#endif
