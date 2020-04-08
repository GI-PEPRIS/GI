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
#ifndef __ANYVIS_POOL_RANK_BOX_H__
#define __ANYVIS_POOL_RANK_BOX_H__

// refer to export macro
#include "anyvis.h"

// refer to parent
#include "anyaxises.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CPoolRankBoxPlot : public CAnyViewHook, private CAnyAxises
	{
			// 5%, 25%, 50%, 75%, 95%, and the matched sample
			const static int PERCENTILES = 6;

	public:
		//
		//
		//
		/*!
		*
		**/
		enum PoolRankViewMode
		{
			// whether adopt the view hook mechanism
			SVM_Map_Operation											= 1
		};
		/*!
		*
		**/
		CPoolRankBoxPlot(CAnyView &curView, bool isForNpv = false);

		/*!
		*
		**/
		~CPoolRankBoxPlot();

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
		void RenderBoxes(CGeoPoint<double> **percentiles, int number);

		/*!
		*
		**/
		CGeoPoint<double> **GetPercentiles(int &number);

		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		void SetMode(unsigned int mode);

		/*!
		*
		**/
		void SetAxisInfo(const AxisInfo &axisInfo);

		/*!
		*
		**/
		inline void SetLogMode(bool isLog);

		/*!
		*
		**/
		inline bool IsLogMode();

		//
		//
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

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
	private:
		/*!
		*
		**/
		void DoRenderLegend(CAnyCanvas &canvas);

		/*!
		*
		**/
		bool GetLogValue(double &val);

	private:
		// boxes
		CGeoPoint<double> **m_percentiles;
		int m_number;
		// axis extent
		CGeoRect<double> m_extent;
		// view mode, haining
		unsigned int m_mode;

		//
		bool m_isForNpv;

		//
		bool m_isLog;
	};
}

#endif