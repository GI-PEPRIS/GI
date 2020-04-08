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
#ifndef __ANYOGRE_MESH_VISITOR_H__
#define __ANYOGRE_MESH_VISITOR_H__

// refer to EXPORT & IMPORT
#include "anyogre.h"

// visitor pattern
#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;

// visitable class
#include "any/vis/anycontour.h"
using namespace AnyVis;

// horizon or fault
#include "any/bridge/anygeologicalcubefeature.h"
#include "any/bridge/anyearthmodel.h"
using namespace AnyBridge;
#include "any/sde/anysderasterlayer.h"
using namespace AnySDE;
// conditional simulator
#include "any/petro/sweetconditionalsimulator.h"
using namespace AnyPetro;

//
#include "anycontourcubeview.h"

//
namespace AnyOGRE
{
	/*!
	*
	**/
	class ANYOGRE_CLASS CAnyMeshVisitor : public BaseVisitor, public Visitor<TYPELIST_4(CAnyViewHook, CAnyGeologicalCubeFeature, CAnySdeRasterLayer, CSweetConditionalSimulator)>
	{
	public:
		struct GraphColoringSetting
		{
			int m_leveloffset;
			std::vector<CGeoPoint<double> > m_range;
			bool m_istoscreen;
			bool m_ismultifile;
			std::vector<string> m_meshfilepaths;
			int m_hisThreshold;
			int m_porosityx;
			int m_porosityy;
			int m_porosityz;
			int m_scanlineminwidth;
			int m_volumeminsize;
			int m_mergeowntimes;
			bool m_isCheckIntersect;
			int m_taskcount;
			int m_tilebuffer;
			GraphColoringSetting() : m_leveloffset(0), m_istoscreen(false), m_ismultifile(false), m_hisThreshold(0), m_porosityx(0), m_porosityy(0), m_porosityz(0), \
				m_scanlineminwidth(0), m_volumeminsize(0), m_mergeowntimes(0), m_isCheckIntersect(false), m_taskcount(0), m_tilebuffer(0)
			{}
			GraphColoringSetting(const GraphColoringSetting &other)
			{
				*this = other;
			}
			const GraphColoringSetting &operator=(const GraphColoringSetting &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_leveloffset = other.m_leveloffset;
				m_range = other.m_range;
				m_istoscreen = other.m_istoscreen;
				m_ismultifile = other.m_ismultifile;
				m_meshfilepaths = other.m_meshfilepaths;
				m_hisThreshold = other.m_hisThreshold;
				m_porosityx = other.m_porosityx;
				m_porosityy = other.m_porosityy;
				m_porosityz = other.m_porosityz;
				m_scanlineminwidth = other.m_scanlineminwidth;
				m_volumeminsize = other.m_volumeminsize;
				m_mergeowntimes = other.m_mergeowntimes;
				m_isCheckIntersect = other.m_isCheckIntersect;
				m_taskcount = other.m_taskcount;
				m_tilebuffer = other.m_tilebuffer;
				return *this;
			}
		};
		struct SweetConditionalSimulatorSetting
		{
			int m_visitwhichdata; //0:m_3dEvs, 1:m_Grid, 2:m_S, 3:m_kringGrid
			int m_visittype;//0:全部立方体绘制，1：切片，2：MC，3：Scatter
			std::vector<int> validxslices;//绘制的立方体切片
			std::vector<int> validyslices;//绘制的立方体切片
			std::vector<int> validzslices;//绘制的立方体切片
			std::vector<std::vector<CGeoPoint<double> > > m_slices;//切片四角坐标
			std::vector<double> m_validvaluemins;//MC有效值下限
			std::vector<double> m_validvaluemaxs;//MC有效值下限
			SweetConditionalSimulatorSetting() : m_visitwhichdata(0), m_visittype(0)
			{}
			SweetConditionalSimulatorSetting(const SweetConditionalSimulatorSetting &other)
			{
				*this = other;
			}
			const SweetConditionalSimulatorSetting &operator=(const SweetConditionalSimulatorSetting &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_visitwhichdata = other.m_visitwhichdata;
				m_visittype = other.m_visittype;
				validxslices = other.validxslices;
				validyslices = other.validyslices;
				validzslices = other.validzslices;
				m_slices = other.m_slices;
				m_validvaluemins = other.m_validvaluemins;
				m_validvaluemaxs = other.m_validvaluemaxs;
				return *this;
			}
		};
		//
		//
		//
		/*!
		*
		**/
		CAnyMeshVisitor(CAnyContourCubeView::MeshConstruct &mesh, CAnyOgreSampleView::GeometryVector &geometries);
		~CAnyMeshVisitor();

	public:
		//
		// contour cube's content: meshes, contour lines, well tracks etc
		//
		/*!
		*
		**/
		void Visit(CAnyViewHook &hook);

		//
		// geological cube content: meshes(feature and fault), well tracks 
		//
		void Visit(CAnyGeologicalCubeFeature &feature);
		void VisitFaultLayer(CAnyGeologicalCubeFeature::SampleVector &samples);
		
		/*!
		*
		**/
		void Visit(CAnySdeRasterLayer &rasterLayer);

		/*!
		*
		**/
		void Visit(CSweetConditionalSimulator &simulator);

	private:
		//
		void DoVisitContourMesh(CAnyContour *contour);
		void DoVisitContourLine(CAnyContour *contour);
		void DoInterpolationLine(int inlinecount, int xlinecount, CAnyGeologicalCubeFeature::SampleVector &samples);
		void DoInterpolationArea(int inlinecount, int xlinecount, CAnyGeologicalCubeFeature::SampleVector &samples);
		int FromValueToColor(double val, double minval, double maxval);
	public:
		CAnyContourCubeView::MeshConstruct &m_mesh;
		CAnyOgreSampleView::GeometryVector &m_geometries;
		CAnyOgreSampleView::ColorCode m_colorcode;
	public:
		GraphColoringSetting m_graphcoloringsetting;
		SweetConditionalSimulatorSetting m_sweetconditionalsimulatorsetting;
	};
}
#endif