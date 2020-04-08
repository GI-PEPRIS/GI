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
#ifndef __ANYSDE_SDE_OVERLAY_ANALYSIS_H__
#define __ANYSDE_SDE_OVERLAY_ANALYSIS_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to property vector
#include "anysdegeometrylayer.h"

// refer to STL
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
#include "any/base/anyport.h"
using namespace AnyBase;

//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnyOverlayAnalysis : public CAnyViewHook
	{
		/*!
		*
		**/
		struct IntersectionParameter
		{
			int m_taskcount;
			int m_index;
			int m_markfirst;
			int m_outputgeometrytype;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> m_geometries;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> &m_geometries0;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> &m_outputgeometries;
			std::vector<std::vector<long>> &m_basegeomIds;
			std::vector<std::vector<long>> &m_currentgeomIds;
			IntersectionParameter(int taskcount, int index,int markfirst,int outputgeometrytype,std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries,std::vector<boost::shared_ptr<CAnySdeGeometry>> &geometries0,std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries,std::vector<std::vector<long>> &basegeomIds,std::vector<std::vector<long>> &currentgeomIds):m_geometries0(geometries0),m_outputgeometries(outputgeometries),m_basegeomIds(basegeomIds),m_currentgeomIds(currentgeomIds)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_markfirst=markfirst;
				m_outputgeometrytype=outputgeometrytype;
				m_geometries=geometries;
			}
		};
					
		/*!
		*
		**/
		struct IntersectionParameter_Point
		{
			int m_taskcount;
			int m_index;
			int m_type;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> m_geometries;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> m_geometries0;
			std::vector<std::vector<long>> &m_outputid;
			std::vector<std::vector<long>> &m_basegeomIds;
			IntersectionParameter_Point(int taskcount, int index,int type,std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries,std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries0,std::vector<std::vector<long>> &outputid,std::vector<std::vector<long>> &basegeomIds):m_outputid(outputid),m_basegeomIds(basegeomIds)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_type=type;
				m_geometries=geometries;
				m_geometries0=geometries0;
			}
		};	
		/*!
		*
		**/
		struct UnionParameter
		{
			int m_taskcount;
			int m_index;
			int m_order;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> m_geometries;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> m_geometries0;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> &m_outputgeometries;
			std::vector<std::vector<long>> &m_basegeomIds;
			std::vector<std::vector<long>> &m_currentgeomIds;
			UnionParameter(int taskcount, int index,int order,std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries,std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries0,std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries,std::vector<std::vector<long>> &basegeomIds,std::vector<std::vector<long>> &currentgeomIds):m_outputgeometries(outputgeometries),m_basegeomIds(basegeomIds),m_currentgeomIds(currentgeomIds)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_order=order;
				m_geometries=geometries;
				m_geometries0=geometries0;
			}
		};
				
		/*!
		*
		**/
		struct SymDifferenceParameter_Point
		{
			int m_taskcount;
			int m_index;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> m_geometries;
			std::vector<boost::shared_ptr<CAnySdeGeometry>> m_geometries0;
			std::vector<long> &m_outputid;
			std::vector<long> &m_outputid2;
			SymDifferenceParameter_Point(int taskcount,int index,std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries,std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries0,std::vector<long> &outputid,std::vector<long> &outputid2):m_outputid(outputid),m_outputid2(outputid2)
			{
				m_taskcount=taskcount;
				m_index=index;
				m_geometries=geometries;
				m_geometries0=geometries0;
			}
		};
	public:
		enum OverlayType
		{
			OT_Intersect,
			OT_Union,
			OT_Erase,
			OT_SymmetricalDifference,
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyOverlayAnalysis(CAnyView &curView);
		CAnyOverlayAnalysis(CAnyView &curView, CAnyViewHook *layer);
				
		/*!
		*
		**/
		~CAnyOverlayAnalysis();

	public:
		//
		// inherited from view hook
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);
		
		
		//
		// behaviors as a typical view hook
		//
		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect = false);
		bool MouseDown(const CGeoPoint<double> &scrPoint);
		bool MouseMove(const CGeoPoint<double> &scrPoint);
		bool MouseUp(const CGeoPoint<double> &scrPoint);
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		//
		//
		//

		/*!
		*
		**/
		void Intersection(std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, int outputgeometrytype, std::vector<std::vector<long>> &basegeomIds);
		void Intersection(vector<CAnySdeGeometryLayer*> inputlayers, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, int outputgeometrytype, std::vector<std::vector<long>> &basegeomIds);
		void IntersectionMT(vector<CAnySdeGeometryLayer*> inputlayers, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, int outputgeometrytype, std::vector<std::vector<long>> &basegeomIds);
		void IntersectionMT(std::vector<boost::shared_ptr<CAnySdeGeometry>> geometries0,std::vector<std::vector<boost::shared_ptr<CAnySdeGeometry>>> inputgeometries, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, int outputgeometrytype,  std::vector<std::vector<long>> &basegeomIds);
		void Intersection_Thread(const IntersectionParameter &parameter);
		void Intersection_Thread_Point(const IntersectionParameter_Point &parameter);
		/*!
		*
		**/
		void Union(vector<CAnySdeGeometryLayer*> inputlayers, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, std::vector<std::vector<long>> &basegeomIds);
		void UnionMT(vector<CAnySdeGeometryLayer*> inputlayers, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, std::vector<std::vector<long>> &basegeomIds);
		void Union_Thread(const UnionParameter &parameter);

		/*!
		*
		**/
		void Erase(CAnySdeGeometryLayer* inputlayer, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries,  std::vector<long> &basegeomIds);
				
		/*!
		*
		**/
		void SymDifference(CAnySdeGeometryLayer* inputlayer, std::vector<boost::shared_ptr<CAnySdeGeometry>> &outputgeometries, std::vector<long> &basegeomIds);
		void SymDifference_Thread_Point(const SymDifferenceParameter_Point &parameter);
	public:
		// raster extent
		CGeoRect<double> m_extent;


		// host layer
		CAnySdeGeometryLayer *m_layer;

	};
}
#endif