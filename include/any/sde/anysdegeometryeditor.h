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
#ifndef __ANYSDE_SDE_GEOMETRY_EDITOR_H__
#define __ANYSDE_SDE_GEOMETRY_EDITOR_H__

// refer to EXPORT & IMPORT macroes
#include "anysde.h"

// refer to property vector
#include "anysdegeometrylayer.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//
namespace AnySDE
{
	// forward class
	class CAnySdeGeometryLayer;
	class CAnySdeGeometry;

	/*!
	* as dummy hook layer and strawman when editting one layer
	**/
	class ANYSDE_CLASS CAnySdeGeometryEditor : public CAnyViewHook
	{
	public:
		//
		enum EdittingTaskType
		{
			EAT_Unknown,

			// general editting
			EAT_Create,
			EAT_Property,
			EAT_Delete,
			EAT_Move,
			EAT_Rotate,
			EAT_Mirror,
			EAT_Reshape,
			EAT_Smooth,

			//special
			EAT_Overhead,//2015/6/16
			EAT_Shorthead,//2015/6/16
			EAT_Select,//2015/6/23
			EAT_Spline_Interpolation,//2015/7/1
			
			EAT_Polygon_Merge,//2016/4/8: polygon merge
			EAT_Polygon_Split,//2016/4/8: polygon split
			
			// refer to arcmap editting tool
			EAT_Intersection,
			EAT_Arc,
			EAT_Midpoint,
			EAT_Endpoint_Arc,
			EAT_Tangent_Curve,
			EAT_Distance_Distance,
			EAT_Direction_Distance,
			EAT_Trace,
			EAT_Max,
		};

		enum ReshapeType
		{
			RT_Unknown,
			RT_Move,
			RT_Add,
			RT_Delete,
			RT_Continue_Right,//20170303
			RT_Continue_Left,//20170515
			RT_Continue_Part,//continue drawing another part of the multigeometry
			RT_Max,
		};

		enum LineCreatingType
		{
			LCT_Unknown,
			LCT_Horizontal,
			LCT_Vertical,
			LCT_Max,
		};

		enum PolygonCreatingType
		{
			PCT_Unknown,
			PCT_Rectangle,
			PCT_Circle,
			PCT_Ellipes,
			PCT_Max,
		};

		// redo/undo list
		struct SDEElement
		{
			CAnySdeGeometry *m_geometry;
			CAnySdeLayer::PropertyVector m_properties; // BLOB field ?

			SDEElement() : m_geometry(0)
			{
			};
			~SDEElement()
			{
				if(m_geometry)
				{
					delete m_geometry;
					m_geometry = 0;
				}
			}
		};
		typedef std::vector<SDEElement *> RedoUndoElement;
		typedef std::vector<RedoUndoElement *> RedoUndoVector;
		typedef RedoUndoVector::iterator do_itr;
		typedef RedoUndoVector::const_iterator do_citr;

		//2015/9/22:to do...
		typedef std::stack<std::vector<RedoUndoElement *>> RedoUndoStack;

		//2015/8/31: compare coordinates x
		typedef std::pair<int,double> Pair;
		typedef std::vector<Pair> PairVec;
		typedef std::vector<Pair>::iterator PairItr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeGeometryEditor(CAnyView &curView, CAnySdeGeometryLayer &layer);

		/*!
		*
		**/
		~CAnySdeGeometryEditor();
		//
		// inherited from view hook
		//
		/*!
		*
		**/
		 void Clone(const CAnyViewHook *prototype)
		 {
		 }

	protected:
		//
		// behaviors as a typical view hook
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
				
		//
		//
		//
		/*!
		*
		**/
		bool StartEditting();

		/*!
		*
		**/
		bool StopEditting();
		/*!
		*
		**/
		void SetEdittingType(short type);
		

		/*!
		*
		**/
		short GetEdittingType();
		

		/*!
		*
		**/
		void SetReshapeType(short type)
		{
			m_reshapeType = type;
		}

		/*!
		*
		**/
		short GetReshapeType()
		{
			return m_reshapeType;
		}
				
		/*!
		*
		**/
		void SetCreatingType(short type);
		
		/*!
		*
		**/
		short GetCreatingType();

		/*!
		*
		**/
		void UpdateFeature(long geometryIdx, CAnySdeLayer::PropertyVector &properties);

		/*!
		*
		**/
		void OnNewEditAction();
		
		/*!
		*
		**/
		void ExcuteUndo();

		/*!
		*
		**/
		void ExcuteRedo();

		/*!
		*2015/6/11
		**/
		void QueryByPointExtent(const CGeoPoint<double> &scrPoint, std::vector<unsigned long> &selections);

		/*!
		*2015/6/19
		**/
		void UpdateUndoRedoVector(RedoUndoElement *redoClone, RedoUndoElement *undoClone = 0);

		/*!
		*
		**/
		bool DeleteGeometries(const std::vector<unsigned long> &selections, bool isDeleteAll = true);

		/*!
		*2015/7/20
		**/
		bool SplineInterpolation(std::vector<unsigned long> &selections);

		/*!
		*2015/6/11
		**/
		CGeoRect<double> GetPointMapExtent(const CGeoPoint<double> &scrPt);

		/*!
		*2015/8/11
		**/
		bool AddGeometries(const std::vector<CGeoPoint<double>> &pts);

		/*!
		*2015/8/31
		**/
		bool AdjustLines( std::vector<unsigned long> &idxes, const std::vector<CGeoPoint<double> > &poly, bool isOverHead);

		/*!
		*2015/8/31
		**/
		bool MergeLines(std::vector<unsigned long> &idxes);

		/*!
		*2015/8/31: return smaller one
		**/
		static bool CompareValue(const Pair &first, const Pair &second);

		/*!
		*
		**/
		bool SplitPolygon(std::vector<unsigned long> &idxes, const std::vector<CGeoPoint<double> > &clipPolys, double bufferwidth);

		/*!
		*2016/4/21: three geometries :1,2,3 -> one geometry (1,2,3)
		**/
		bool MergeGeometries(std::vector<unsigned long> &idxes);
				
		/*!
		*20170301 delete nodes in m_selections[0]
		**/
		void DeleteNodesInSelectedGeometry(const CGeoRect<double> &rect, int &remainPointNum);
				
		/*!
		*
		**/
		bool CloseLine(unsigned long &idx);
	private:
		//
		//
		//
		/*!
		*
		**/
		void Clear();

		/*!
		*2015/5/29: for MouseDown\MouseUp\MouseMove\DoubleClick
		**/
		bool IsConditionValid();

	protected:
		// host layer
		//CAnySdeGeometryLayer &m_layer;
		
		// task type
		short m_edittingType;
		short m_reshapeType; // todo: kick off this variable
		short m_lineType;
		short m_polygonType;
		
		//
		RedoUndoElement m_geometry4bungee;

		// anchors for reshaping
		std::vector<CGeoPoint<double> > m_anchors;

		// MouseDown position
		CGeoPoint<double> m_startPos;
		// every mouse position,for bungee
		CGeoPoint<double> m_prePos;

	public:	
		// host layer
		CAnySdeGeometryLayer &m_layer;

		// selected idxes
		std::vector<unsigned long> m_selections;

		// redo/undo list, strictly match
		int m_undoCursor;
		RedoUndoVector m_redos;
		RedoUndoVector m_undos;

		double m_interpolations;//for spline interpolation
	};
}
#endif