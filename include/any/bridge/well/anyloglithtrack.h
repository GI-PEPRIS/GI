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
#ifndef __ANYBRIDGE_LOG_LITH_TRACK_H__
#define __ANYBRIDGE_LOG_LITH_TRACK_H__

// refer to EXPORT & IMPORT
#include "..\anybridge.h"

// refer to its parent
#include "anylogtrackcomponent.h"
#include "any/base/anybmpbasic.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

#include "any/vis/anyvectorsymbolplot.h"
using namespace AnyVis;

//
#include "any/map/anycanvasbasic.h"
using namespace AnyMap;

//
namespace AnyBridge
{
	/*!
	* also as a raster or image show track
	**/
	class ANYBRIDGE_CLASS CAnyLogLithTrack : public CAnyLogTrackComponent
	{
	public:

		enum SymbolType
		{
			ST_Raster_Symbol = 0,
			ST_Vector_Symbol,
		};
		
		//struct VectorSymbol
		//{
		//	int m_idx;// UNIQUE
		//	string m_name; 
		//	int m_leanType;//0-center, 1-left, 2-right
		//	double m_widthRate;
		//	int indent;
		//	bool baseline;
		//	bool dual;
		//	bool turn;
		//	
		//	CGeoRect<double> m_symbolMapPort;//samples' map port 
		//	CGeoRect<double> m_positionMapPort;//map position in component
		//	CGeoRect<double> m_positionScrPort;//screen position in component
		//	
		//	int m_elementnumber;
		//	std::vector<CAnyVectorSymbolPlot::VectorSymbolElement *> m_elements;
		//	std::vector<CAnyVectorSymbolPlot::VectorSymbolElement *> m_inclusion_elements;
		//	std::vector<CAnyVectorSymbolPlot::VectorSymbolElement *> m_prefix_elements;
		//	std::vector<CAnyVectorSymbolPlot::VectorSymbolElement *> m_struct_elements;
		//	std::vector<CAnyVectorSymbolPlot::VectorSymbolElement *> m_oiloccrence_elements;
		//	ColorStyle m_backgroundColor;

		//	VectorSymbol() : m_idx(-1), m_name(""), m_leanType(0), m_widthRate(1.), m_elementnumber(0), indent(0),baseline(true),dual(true),turn(true)
		//	{
		//	}

		//	~VectorSymbol()
		//	{
		//	}

		//	bool Add(CAnyVectorSymbolPlot::VectorSymbolElement *element);
		//	bool Remove(int idx);
		//	void Align(std::vector<int> &idxes, short type);
		//	void Map2Scr(CGeoPoint<double> &mappt, CGeoPoint<double> &scrpt);
		//	void Scr2Map(CGeoPoint<double> &scrpt, CGeoPoint<double> &mappt);
		//	void RenderSymbol(CAnyCanvas &canvas,bool isturn=false);
		//	void Release();
		//	void DrawElement(CAnyCanvas &canvas, CAnyVectorSymbolPlot::VectorSymbolElement *element, CGeoRect<double> extentFrom, CGeoRect<double> extentTo,bool isturn=false);
		//};
		//typedef std::map<string, VectorSymbol> VectorSymbolMap;
		//typedef VectorSymbolMap::iterator vsm_itr;
		//typedef VectorSymbolMap::const_iterator vsm_citr;

		//
		//
		//
		struct RasterSymbol
		{
			long m_idx;
			std::string m_name;
			std::string m_path;
			CAnyBmpBasic *m_image;//picture
			CGeoRect<double> m_position;
			bool m_isBlended;//transparent valid?
			int m_leanType;//0-center, 1-left, 2-right
			double m_widthRate;

			RasterSymbol() : m_idx(-1), m_name(""), m_path(""), m_image(0), m_isBlended(true), m_leanType(0), m_widthRate(1.)
			{
			}

			~RasterSymbol()
			{
				
			}

			void Release()
			{
				if (m_image)
				{
					m_image->Destroy();
				}
				m_image = 0;
			}
		};

		typedef std::map<string, RasterSymbol> RasterSymbolMap;
		typedef RasterSymbolMap::iterator rsm_itr;
		typedef RasterSymbolMap::const_iterator rsm_citr;

		/*!
		*
		**/
		CAnyLogLithTrack();
		~CAnyLogLithTrack();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);

		//
		//
		//
		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		std::string FindRasterSymbol(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		* return -1(not found) 0(top) 1(bottom)
		**/
		int FindRasterSymbolEdge(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		bool RemoveRasterSymbol(const std::string &name);
			
		/*!
		*
		**/
		bool AdjustRectExtent(CGeoRect<double> &extent, bool adjustParaExtent = true, const std::string &exceptionName = "");

		//
		//2016/3/4
		//
		/*!
		*
		**/
		std::string FindVectorSymbol(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		* return -1(not found) 0(top) 1(bottom)
		**/
		int FindVectorSymbolEdge(CAnyView &curView, const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		bool RemoveVectorSymbol(const std::string &name, bool isRelease = true);

		//
		//
		//
		/*!
		*2016/3/11: save/load
		**/
		unsigned char *DoEncoding(long long &length);

		
		/*!
		*2018/2/28: add parameter const long &len = 0
		**/
		bool DoDecoding(unsigned char* parameter, const long &len = 0);
	private:
		/*!
		*
		**/
		void DoRenderRasterSymbol(CAnyCanvas &canvas, CAnyView &curView);

		/*!
		*
		**/
		void DoRenderRasterImage(CAnyCanvas &canvas, CAnyView &curView, const CGeoRect<double> &theRect, RasterSymbol &rasterSymbol);

		/*!
		*
		**/
		void DoRenderTempRasterSymbol(CAnyCanvas &canvas, CAnyView &curView);

		//
		//2016/3/4
		//
		/*!
		*
		**/
		void DoRenderVectorSymbol(CAnyCanvas &canvas, CAnyView &curView);

		/*!
		*
		**/
		void DoRenderVectorSymbol(CAnyCanvas &canvas, CAnyView &curView, const CGeoRect<double> &theRect, CAnyVectorSymbolPlot::VectorSymbol &vectorSymbol);

		/*!
		*
		**/
		void DoRenderTempVectorSymbol(CAnyCanvas &canvas, CAnyView &curView);
	public:
		//
		RasterSymbolMap m_rastersymbols;
		std::string m_curRasterSymbol;

		//for m_curView.Refresh(true)
		CGeoRect<double> m_tempRect;

		//2016/3/7: the current created symbol's type
		int m_symbolType;

		CAnyVectorSymbolPlot::VectorSymbolMap m_vectorSymbols;
		std::string m_curVectorSymbol;
	};
}
#endif