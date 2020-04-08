/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGDE_LOW_FREQUENCY_MODEL_BUILDER_H__
#define __ANYGDE_LOW_FREQUENCY_MODEL_BUILDER_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"

//
#include "any/bridge/anyearthmodel.h"
#include "any/bridge/anygeologicalcubefeature.h"
#include "any/bridge/well/anyloglayer.h"
using namespace AnyBridge;

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CLowFrequencyModelBuilder : public CAnyGdeDataHandler
	{
	public:
		//
		enum StratigraphyProjectionModel
		{
			SPM_Unknown = -1,
			SPM_Top_Base,
			SPM_Top,
			SPM_Base,
			SPM_Max
		};
		//
		struct BuilderParameter
		{
			std::vector<short> m_projectionModels;//沉积模式
			std::vector<CAnyGeologicalCubeFeature*> m_topcubefeatures;//顶层位
			std::vector<CAnyGeologicalCubeFeature*> m_botcubefeatures;//底层位
			std::vector<double> m_topOffsets;//顶偏移量
			std::vector<double> m_botOffsets;//底偏移量

			std::vector<CGeoPoint<double> > m_curve_positions;//各个井曲线的井口位置
			std::vector<std::vector<double> > m_curve_shiftxs;//各个井曲线在地震时间域上的井斜x偏移量
			std::vector<std::vector<double> > m_curve_shiftys;//各个井曲线在地震时间域上的井斜y偏移量
			std::vector<std::vector<double> > m_curve_times;//各个井曲线在地震时间域上的时间值
			std::vector<std::vector<double> > m_curve_samples;//各个井曲线在地震时间域上的数据值

			BuilderParameter()
			{
			}
			BuilderParameter(const BuilderParameter &other)
			{
				*this = other;
			}
			const BuilderParameter &operator=(const BuilderParameter &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_projectionModels = other.m_projectionModels;
				m_topcubefeatures = other.m_topcubefeatures;
				m_botcubefeatures = other.m_botcubefeatures;
				m_topOffsets = other.m_topOffsets;
				m_botOffsets = other.m_botOffsets;

				m_curve_positions = other.m_curve_positions;
				m_curve_shiftxs = other.m_curve_shiftxs;
				m_curve_shiftys = other.m_curve_shiftys;
				m_curve_times = other.m_curve_times;
				m_curve_samples = other.m_curve_samples;
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
		CLowFrequencyModelBuilder(const BuilderParameter &parameter);
		~CLowFrequencyModelBuilder();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle(HandlerStruct &handlerstruct);

		/*!
		*
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		*
		**/
		void DoGetTraceHead(std::vector<double> &results);

	public:
		BuilderParameter m_parameter;
	};
}
#endif
