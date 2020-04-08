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
#ifndef __ANYBRIDGE_LOG_SEIS_TRACK_H__
#define __ANYBRIDGE_LOG_SEIS_TRACK_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to parent
#include "anylogtrackcomponent.h"

// refer to ANYTRACESAMPLE
#include "..\anybridgedatamodel.h"

// namespace
namespace AnyBridge
{
	/*!
	* also as a decorator
	**/
	class ANYBRIDGE_CLASS CAnyLogSeisTrack : public CAnyLogTrackComponent
	{
	public:

		class RenderColorTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			RenderColorTask(int taskcount, int index, CAnyCPUScheduler *scheduler, CAnyLogSeisTrack *parent, CAnyCanvas &canvas, \
				const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
			~RenderColorTask();
			void DoExecuteTask();
		private:
			int m_taskcount;
			int m_index;
			CAnyCPUScheduler *m_scheduler;
			CAnyLogSeisTrack *m_parent;
			CAnyCanvas &m_canvas;
			const CGeoRect<double> &m_validExtent;
			CAnyView &m_curView;
			int &m_namesize;
			double &m_labelscale;
			LabelStyle &m_lablestyle;
		};

		class RenderWaveTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			RenderWaveTask(int taskcount, int index, CAnyCPUScheduler *scheduler, CAnyLogSeisTrack *parent, CAnyCanvas &canvas, \
				const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
			~RenderWaveTask();
			void DoExecuteTask();
		private:
			int m_taskcount;
			int m_index;
			CAnyCPUScheduler *m_scheduler;
			CAnyLogSeisTrack *m_parent;
			CAnyCanvas &m_canvas;
			const CGeoRect<double> &m_validExtent;
			CAnyView &m_curView;
			int &m_namesize;
			double &m_labelscale;
			LabelStyle &m_lablestyle;
		};

		//
		//
		//
		/*!
		*
		**/
		CAnyLogSeisTrack();

		/*!
		*
		**/
		~CAnyLogSeisTrack();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
		
		/*!
		*
		**/
		void DoRenderColor(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
		void DoRenderWave(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

	public:
		//
		std::vector<long> m_sequenceorders;
		std::vector<std::vector<AnyTraceSample> > m_samples;//samples render in wave type
		std::vector<std::vector<AnyTraceSample> > m_samplescolor;//samples render in color type

		std::vector<std::vector<double> > m_horizonlines;//层位
		std::vector<std::vector<int> > m_horizonposes;//层位
		std::vector<string> m_horizonnames;//层位

		double m_linelength; //地震道对应的折线的总长度
		int m_wellposition;//井口位置
		std::vector<AnyTraceSample> m_wellsamples;//井轨迹
		string m_wellname;//井轨迹名称

		double m_scale;//缩放比例

		std::vector<double> m_lineminA;
		std::vector<double> m_linemaxA;
		std::vector<double> m_lineminAcolor;
		std::vector<double> m_linemaxAcolor;
		std::vector<double> m_colorcodevals;//色标配置
		std::vector<int> m_colorcodecolors;//色标配置
		
		//2016/2/26
		CurveProperties m_curves;

		// for show cursor
		std::vector<std::vector<CGeoPoint<double> > > m_lines;
		std::vector<std::vector<AnyTraceSample> > m_datas;
		std::vector<std::vector<long>> m_dataOrders;//2016/4/15: record cursor shown order in m_samples
		bool m_ispaintwave;
		bool m_ispaintcolor;
		int m_paintcolormode;//0:color, 1:gray
	};
}

#endif