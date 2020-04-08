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
#ifndef __ANYOGRE_TEXTURE_VISITOR_H__
#define __ANYOGRE_TEXTURE_VISITOR_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

// visitor pattern
#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;

// visitable class
#include "any/map/anyviewhook.h"
using namespace AnyMap;
#include "any/geop/anysegyprofile.h"
#include "any/geop/anysegylayer.h"
using namespace AnyGeoP;
#include "any/gde/anygdedatagate.h"
#include "any/gde/anygdedataoctreegate.h"
#include "any/gde/anysegyfile.h"
#include "any/gde/anygdedataset.h"
#include "any/gde/anygdedatasurvey.h"
#include "any/gde/anygdedataoctree.h"
using namespace AnyGDE;
#include "any/sde/anysderasterlayer.h"
using namespace AnySDE;

//
#include "anygislayercubeview.h"
#include "anyseismiccubeview.h"

//
namespace AnyOGRE
{
	/*!
	*
	**/
	class ANYOGRE_CLASS CAnyTextureVisitor : public BaseVisitor, public Visitor<TYPELIST_3(CAnyViewHook, CAnySegyLayer, CAnySdeRasterLayer)>
	{
		/*!
		*
		**/
		class VisitSegyLayerTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			VisitSegyLayerTask(int taskcount, int index, CAnyTextureVisitor *parent, CAnyGdeDataGate* gate, std::vector<long> &orders, std::vector<int> &starts, std::vector<int> &ends, CAnyCPUScheduler *scheduler);
			~VisitSegyLayerTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyTextureVisitor *m_parent;
			CAnyGdeDataGate *m_gate;
			std::vector<long> &m_orders;
			std::vector<int> &m_starts;
			std::vector<int> &m_ends;
			CAnyCPUScheduler *m_scheduler;
		};
		/*!
		*
		**/
		class VisitGDELayerTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			VisitGDELayerTask(int taskcount, int index, CAnyTextureVisitor *parent, CAnyGdeDataGate* gate, std::vector<long> &sequenceOrders, std::vector<double> &minTimes, std::vector<double> &maxTimes, CAnyGdeDataSurvey *survey, CAnyCPUScheduler *scheduler);
			~VisitGDELayerTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyTextureVisitor *m_parent;
			CAnyGdeDataGate *m_gate;
			std::vector<long> &m_sequenceOrders;
			std::vector<double> &m_minTimes;
			std::vector<double> &m_maxTimes;
			CAnyGdeDataSurvey *m_survey;
			CAnyCPUScheduler *m_scheduler;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyTextureVisitor(CAnyGisLayerCubeView::LayerConstruct &layer, CAnySeismicCubeView::SeismicCubePlane &seismic);
		~CAnyTextureVisitor();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Visit(CAnyViewHook &layer);
		void Visit(CAnySegyLayer &sgyLayer);
		void Visit(CAnySdeRasterLayer &rasterLayer);
				
		/*!
		*
		**/
		void DoVisitDC(CAnyViewHook &layer);

		/*!
		*
		**/
		double Dither(double value, double dlt)
		{
			assert(dlt > 0);
			if(value > 0)
				value += dlt / 2;
			else
				value -= dlt / 2;

			return value;
		}
	private:
		
		/*!
		*
		**/
		void DoFillImage(CGeoRect<double> &block, double &f1, double &f2, double &f3, double &f4, double &minValue, double &maxValue, CAnySegyProfile::ProfileRecord &profile);
	public:
		// layer construct
		CAnyGisLayerCubeView::LayerConstruct &m_layer;
		// seismic construct
		CAnySeismicCubeView::SeismicCubePlane &m_seismic;
		CAnyOgreSampleView::ColorCode m_colorcode;
	public:
		// results for multiline class access
		std::vector<std::vector<double> > m_resultsforMT;
		bool m_isvisitdc;
		bool m_ispremode;//是否叠前模式
		int m_previsittype;//0:normal, 1:共方位角，2:共偏移距
		double m_low;//方位角或偏移距下限
		double m_up;//方位角或偏移距上限
	};
}
#endif