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
#ifndef __ANYVIS_VECTOR_SYMBOL_PLOT_H__
#define __ANYVIS_VECTOR_SYMBOL_PLOT_H__

// refer to macro
#include "anyvis.h"

// refer to its parent
#include "anyscattermatrix.h"

// refer to geopoint
#include "any/base/anygeom.h"
#include "any/base/anyvectop.h"
using namespace AnyBase;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyVectorSymbolPlot  : public CAnyViewHook
	{
	public:
		/*!
		*
		**/
		enum VectorSymbolOperation
		{
			VS_Default			= 1,			//
			VS_Pick				= 1 << 1,		//move 
			VS_Curve			= 1 << 2,		//2016/4/20: create a free curve
			VS_Spline			= 1 << 3,		//2016/4/20: create a spline curve
			VS_Multi_Sel		= 1 << 4,		//2016/5/10: multiple selection
		};

		/*!
		*enum
		**/
		enum VectorSymbolType
		{
			VST_Unknown,
			VST_Line,
			VST_Polygon,
			VST_Circle,
			VST_Circle_Verticle,
			VST_Circle_Horizontal,
			VST_Rectangle,
			VST_Rectangle_LT,
			VST_Rectangle_LB,
			VST_Character,
			VST_Curve,//2016/4/20:free curve
			VST_Spline,//2016/4/26:spline
			VST_Real_Symbol,//2016/5/5:real symbol
			VST_Arc,
			VST_Pie,
			VST_Chord,
			VST_Parrallel,
			VST_Max
		};

		enum VectorSymbolAlign
		{
			VSA_No_Space		= 0,
			VSA_Left			= 1 << 1,
			VSA_Right			= 1 << 2,
			VSA_Top				= 1 << 3,
			VSA_Bottom			= 1 << 4,
		};

		/*!
		*struct
		**/
		struct VectorSymbolStyle : public AnyMap::LineStyle, AnyMap::PolyStyle, AnyMap::LabelStyle, AnyMap::SymbolStyle, AnyMap::ArrowStyle
		{
		};

		struct VectorSymbolElement
		{
			// basic
			int m_idx;
			int m_number;
			
			//special
			double m_radiusRateA;//for RenderEllipse
			double m_radiusRateB;//for RenderEllipse
			double m_screenWidth;//for RenderEllipse
			double m_startAngle;//for Render Arc & Pie
			double m_sweepAngle;//for Render Arc & Pie

			std::string m_label;//for RenderGlyphs
			CGeoPoint<double> m_labelWidthHeight;//for RenderGlyphs

			//style
			int m_symboltype;
			VectorSymbolStyle *m_symbolstyle;
			VectorSymbolStyle *m_symbolstyle1;

			//position
			std::vector<CGeoPoint<double> > m_originalCoords;
			std::vector<CGeoPoint<double> > m_mapCoords;
			std::vector<CGeoPoint<double> > m_scrCoords;
			CGeoRect<double> m_scrextent;
			CGeoRect<double> m_mapextent;

			//replace
			std::string m_replace;

			// topo
			VectorSymbolElement *m_top;
			VectorSymbolElement *m_bottom;
			VectorSymbolElement *m_left;
			VectorSymbolElement *m_right;

			//
			VectorSymbolElement() : m_idx(-1), m_number(0), m_symboltype(VST_Unknown), m_symbolstyle(0), m_symbolstyle1(0), m_radiusRateA(1.), m_radiusRateB(1.), m_screenWidth(1.), \
				m_startAngle(0.),m_sweepAngle(0.),m_label(""), m_top(0), m_bottom(0), m_left(0), m_right(0),m_replace(""),m_scrextent(0,0,0,0),m_mapextent(0,0,0,0)
			{
			}

			~VectorSymbolElement()
			{
			}

			void Release()
			{
				if (m_symbolstyle)
				{
					delete m_symbolstyle;
				}
				m_symbolstyle = 0;

				if (m_symbolstyle1)
				{
					delete m_symbolstyle1;
				}
				m_symbolstyle1 = 0;
			}

			/*!
			*
			**/
			const VectorSymbolElement &operator=(const VectorSymbolElement &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_idx=other.m_idx;
				m_number=other.m_number;
				m_symboltype=other.m_symboltype;
				m_symbolstyle=other.m_symbolstyle;
				m_symbolstyle1=other.m_symbolstyle1;
				m_radiusRateA=other.m_radiusRateA;
				m_radiusRateB=other.m_radiusRateB;
				m_screenWidth=other.m_screenWidth;
				m_startAngle=other.m_startAngle;
				m_label=other.m_label;
				m_top=other.m_top;
				m_bottom=other.m_bottom;
				m_left=other.m_left;
				m_right=other.m_right;
				m_replace=other.m_replace;
				m_scrextent=other.m_scrextent;
				m_mapextent=other.m_mapextent;
				m_originalCoords.clear();
				for(int i=0;i<other.m_originalCoords.size();i++)
					m_originalCoords.push_back(other.m_originalCoords[i]);
				m_mapCoords.clear();
				for(int i=0;i<other.m_mapCoords.size();i++)
					m_mapCoords.push_back(other.m_mapCoords[i]);
				m_scrCoords.clear();
				for(int i=0;i<other.m_scrCoords.size();i++)
					m_scrCoords.push_back(other.m_scrCoords[i]);

				return *this;
			}

			void Draw(CAnyCanvas &canvas, bool isHighLight = false)
			{
				//exception
				if (!m_scrCoords.size() || !m_symbolstyle || m_symboltype <= VST_Unknown || m_symboltype >= VST_Max)
				{
					return;
				}

				//2016/5/10: set highlight color
				ColorStyle highlightColor;
				highlightColor.m_red = 255;
				ColorStyle highlightColor1;
				highlightColor1.m_green = 127;

				if (m_symboltype == VST_Line || m_symboltype == VST_Curve || m_symboltype == VST_Spline)
				{
					if (m_scrCoords.size() < 2)
					{
						return;
					}

					LineStyle *style = (LineStyle*)m_symbolstyle;
					if (style)
					{
						LineStyle newstyle;
						newstyle.m_color = highlightColor;
						canvas.RenderLine(m_scrCoords.data(),m_scrCoords.size(),!isHighLight ? *style : newstyle);
					}
				}
				if(m_symboltype == VST_Parrallel)
				{
					if (m_scrCoords.size() < 2)
					{
						return;
					}

					LineStyle *style = (LineStyle*)m_symbolstyle;
					if (style)
					{
						LineStyle newstyle;
						newstyle.m_color = highlightColor;

						for(int i=0;i<m_scrCoords.size()-1;)
						{
							std::vector<CGeoPoint<double>> pts;

							CGeoPoint<double> pt1 = m_scrCoords[i];
							pts.push_back(pt1);

							CGeoPoint<double> pt2 = m_scrCoords[i+1];
							pts.push_back(pt2);

							canvas.RenderLine(pts.data(),pts.size(),!isHighLight ? *style : newstyle);

							i+=2;
						}
					}
				}
				else if (m_symboltype == VST_Polygon)
				{
					if (m_scrCoords.size() < 3)
					{
						return;
					}

					PolyStyle *style = (PolyStyle*)m_symbolstyle;
					if (style)
					{
						PolyStyle newstyle;
						newstyle.m_color = highlightColor;
						canvas.RenderPolygon(m_scrCoords.data(),m_scrCoords.size(),!isHighLight ? *style : newstyle);
					}
				}
				else if (m_symboltype == VST_Circle || m_symboltype == VST_Circle_Verticle || m_symboltype == VST_Circle_Horizontal)
				{
					//2016/4/15: get radius
					//double maxX = -0x7fffffff;
					//int i = 0;
					//for (; i < m_scrCoords.size(); i++)
					//{
					//	if (maxX < m_scrCoords[i].m_x)
					//	{
					//		maxX = m_scrCoords[i].m_x;
					//	}
					//}
					//double radius = ::fabs(maxX - m_scrCoords[0].m_x);
					double radiusA = m_radiusRateA * m_screenWidth;//calculate radius
					double radiusB = m_radiusRateB * m_screenWidth;//calculate radius
					if (m_symboltype == VST_Circle)
					{
						SymbolStyle *style = (SymbolStyle*)m_symbolstyle;
						if (style)
						{
							SymbolStyle newstyle;
							newstyle.m_color = highlightColor;
							canvas.RenderEllipse(m_scrCoords[0], radiusA, radiusB, !isHighLight ? *style : newstyle);//center point
						}
					}
					else if (m_symboltype == VST_Circle_Verticle)
					{
						//draw circle
						SymbolStyle *style = (SymbolStyle*)m_symbolstyle;
						if (style)
						{
							SymbolStyle newstyle;
							newstyle.m_color = highlightColor;
							canvas.RenderEllipse(m_scrCoords[0], radiusA, radiusB, !isHighLight ? *style : newstyle);//center point
						}

						//draw vertical line
						LineStyle *style1 = (LineStyle*)m_symbolstyle;
						if (style1)
						{
							std::vector<CGeoPoint<double>> pts;

							CGeoPoint<double> pt1 = m_scrCoords[0];
							pt1.m_y -= radiusB;
							pts.push_back(pt1);

							CGeoPoint<double> pt2 = m_scrCoords[0];
							pt2.m_y += radiusB;
							pts.push_back(pt2);

							LineStyle newstyle;
							newstyle.m_color = highlightColor1;
							canvas.RenderLine(pts.data(),pts.size(),!isHighLight ? *style1 : newstyle);
						}
					}
					else if (m_symboltype == VST_Circle_Horizontal)
					{
						//draw circle
						SymbolStyle *style = (SymbolStyle*)m_symbolstyle;
						if (style)
						{
							SymbolStyle newstyle;
							newstyle.m_color = highlightColor;
							canvas.RenderEllipse(m_scrCoords[0], radiusA, radiusB, !isHighLight ? *style : newstyle);//center point
						}

						//draw Horizontal line
						LineStyle *style1 = (LineStyle*)m_symbolstyle;
						if (style1)
						{
							std::vector<CGeoPoint<double>> pts;

							CGeoPoint<double> pt1 = m_scrCoords[0];
							pt1.m_x -= radiusA;
							pts.push_back(pt1);

							CGeoPoint<double> pt2 = m_scrCoords[0];
							pt2.m_x += radiusA;
							pts.push_back(pt2);

							LineStyle newstyle;
							newstyle.m_color = highlightColor1;
							canvas.RenderLine(pts.data(),pts.size(),!isHighLight ? *style1 : newstyle);
						}
					}
				}
				else if (m_symboltype == VST_Rectangle)
				{
					if (m_scrCoords.size() < 4)
					{
						return;
					}

					//m_scrCoords: left top(0) ->left bottom(1) ->right bottom (2)-> right top(3)
					//SymbolStyle *style = (SymbolStyle*)m_symbolstyle;
					PolyStyle *style = (PolyStyle*)m_symbolstyle;
					if (style)
					{
						//CGeoRect<double> rect;
						//rect.m_minX = m_scrCoords[0].m_x;
						//rect.m_minY = m_scrCoords[0].m_y;
						//rect.m_maxX = m_scrCoords[2].m_x;
						//rect.m_maxY = m_scrCoords[2].m_y;
						//
						//SymbolStyle newstyle;
						//newstyle.m_color = highlightColor;
						//canvas.RenderRectangle(rect, !isHighLight ? *style : newstyle);//center point
						std::vector<CGeoPoint<double>> pts;
						pts.push_back(m_scrCoords[0]);
						pts.push_back(m_scrCoords[1]);
						pts.push_back(m_scrCoords[2]);
						pts.push_back(m_scrCoords[3]);
						pts.push_back(m_scrCoords[0]);

						PolyStyle newstyle;
						newstyle.m_color = highlightColor;
						canvas.RenderPolygon(pts.data(),pts.size(),!isHighLight ? *style : newstyle);
					}
				}
				else if (m_symboltype == VST_Rectangle_LT)
				{
					if (m_scrCoords.size() < 4)
					{
						return;
					}

					//m_scrCoords: left top(0) ->left bottom(1) ->right bottom (2)-> right top(3)
					PolyStyle *style = (PolyStyle*)m_symbolstyle;
					if (style)
					{
						std::vector<CGeoPoint<double>> pts;
						pts.push_back(m_scrCoords[0]);
						pts.push_back(m_scrCoords[1]);
						pts.push_back(m_scrCoords[2]);
						pts.push_back(m_scrCoords[0]);

						PolyStyle newstyle;
						newstyle.m_color = highlightColor;
						canvas.RenderPolygon(pts.data(),pts.size(),!isHighLight ? *style : newstyle);
					}

					PolyStyle *style1 = (PolyStyle*)m_symbolstyle1;
					if (style1)
					{
						std::vector<CGeoPoint<double>> pts;
						pts.push_back(m_scrCoords[0]);
						pts.push_back(m_scrCoords[2]);
						pts.push_back(m_scrCoords[3]);
						pts.push_back(m_scrCoords[0]);

						PolyStyle newstyle;
						newstyle.m_color = highlightColor1;
						canvas.RenderPolygon(pts.data(),pts.size(),!isHighLight ? *style1 : newstyle);
					}
				}
				else if (m_symboltype == VST_Rectangle_LB)
				{
					if (m_scrCoords.size() < 4)
					{
						return;
					}

					//m_scrCoords: left top(0) ->left bottom(1) ->right bottom (2)-> right top(3)
					PolyStyle *style = (PolyStyle*)m_symbolstyle;
					if (style)
					{
						std::vector<CGeoPoint<double>> pts;
						pts.push_back(m_scrCoords[1]);
						pts.push_back(m_scrCoords[3]);
						pts.push_back(m_scrCoords[0]);
						pts.push_back(m_scrCoords[1]);

						PolyStyle newstyle;
						newstyle.m_color = highlightColor;
						canvas.RenderPolygon(pts.data(),pts.size(),!isHighLight ? *style : newstyle);
					}

					PolyStyle *style1 = (PolyStyle*)m_symbolstyle1;
					if (style1)
					{
						std::vector<CGeoPoint<double>> pts;
						pts.push_back(m_scrCoords[1]);
						pts.push_back(m_scrCoords[3]);
						pts.push_back(m_scrCoords[2]);
						pts.push_back(m_scrCoords[1]);

						PolyStyle newstyle;
						newstyle.m_color = highlightColor1;
						canvas.RenderPolygon(pts.data(),pts.size(),!isHighLight ? *style1 : newstyle);
					}
				}
				else if (m_symboltype == VST_Character || m_symboltype == VST_Real_Symbol)
				{
					LabelStyle *style = (LabelStyle*)m_symbolstyle;
					if (style)
					{
						if (m_symboltype == VST_Character)
						{
							if (m_label.size())
							{
								//2016/5/5: backup font
								std::string bkfontname = canvas.m_curfontname;

								//2016/4/20:load font
								std::string fontName = style->m_font;
								if (!fontName.size() || (fontName.find(".") != string::npos))
								{
									fontName = "google";
									std::strcpy(style->m_font,  fontName.c_str());
								}
								canvas.LoadFont(style->m_font);

								LabelStyle newstyle;
								newstyle.m_color = highlightColor;
								newstyle.m_size = style->m_size;
								m_labelWidthHeight = canvas.RenderGlyphs(m_scrCoords[0], !isHighLight ? *style : newstyle, m_label.c_str());

								//2016/5/5: recover original font
								canvas.LoadFont(bkfontname);
							}
						}
						else if (m_symboltype == VST_Real_Symbol)//2016/5/5:VST_Real_Symbol 
						{
							if (style->m_fldIdx >= 0)
							{
								std::string bkfontname = canvas.m_curfontname;

								std::string fontName = style->m_font;
								if (!fontName.size() || (fontName.find(".") != string::npos))
								{
									fontName = "google";
									std::strcpy(style->m_font,  fontName.c_str());
								}
								canvas.LoadFont(style->m_font);
								
								LabelStyle newstyle;
								newstyle.m_color = highlightColor;
								newstyle.m_size = style->m_size;
								m_labelWidthHeight = canvas.RenderGlyphs(m_scrCoords[0], !isHighLight ? *style : newstyle, style->m_fldIdx);

								//2016/5/5: recover original font
								canvas.LoadFont(bkfontname);
							}
						}						
					}
				}
				else if(m_symboltype == VST_Arc || m_symboltype == VST_Pie ||m_symboltype == VST_Chord)
				{
					double radiusA = m_radiusRateA * m_screenWidth;//calculate radius
					double radiusB = m_radiusRateB * m_screenWidth;//calculate radius

					if(m_symboltype == VST_Pie)
					{
						PolyStyle *style = (PolyStyle*)m_symbolstyle;
						if (style)
						{
							PolyStyle newstyle;
							newstyle.m_color = highlightColor;
							canvas.RenderBezierArc(m_scrCoords[0], radiusA, radiusB, m_startAngle,m_sweepAngle, !isHighLight ? *style : newstyle);//center point
						}
					}
					else//if(m_symboltype == VST_Arc ||m_symboltype == VST_Chord)
					{
						LineStyle *style = (LineStyle*)m_symbolstyle;
						if (style)
						{
							LineStyle newstyle;
							newstyle.m_color = highlightColor;
							canvas.RenderBezierArcLine(m_scrCoords[0], radiusA, radiusB, m_startAngle,m_sweepAngle, !isHighLight ? *style : newstyle);//center point

							if(m_symboltype == VST_Chord)
							{
								std::vector<CGeoPoint<double>> pts;

								CGeoPoint<double> pt1 = m_scrCoords[0];
								pt1.m_x -= radiusA;
								pts.push_back(pt1);

								CGeoPoint<double> pt2 = m_scrCoords[0];
								pt2.m_x += radiusA;
								pts.push_back(pt2);

								canvas.RenderLine(pts.data(),pts.size(),!isHighLight ? *style : newstyle);
							}
						}
					}
				}
			}
		};
		struct Combin
		{
			double x;
			double y;
			double size;
			double height;
			double width;
			double rotate;
			std::string border;
			std::string replace;
			bool limit_height;
			CGeoRect<double> extent;
			std::vector<VectorSymbolElement *> elements;
			std::vector<Combin *> combins;

			//
			Combin() : x(0.), y(0.), size(0.), width(0.),height(0.),rotate(0.), border(""),replace(""),limit_height(false),extent(0,0,0,0)
			{
			}

			~Combin()
			{
			}
		};
		enum LithoAttributeType
		{
			LAT_Unknown,
			LAT_Litho,
			LAT_Oiloccurence,
			LAT_Inclusion	,
			LAT_Prefix,
			LAT_Struct,
		};
				
		struct LithoItem
		{
			int id;//value
			std::string name;
			int type;//LithoAttributeType

			//for Litho
			double scale;
			int indent;
			bool baseline;
			bool dual;
			bool turn;

			//extent
			CGeoRect<double> m_itemMapExtent;

			//shapes
			std::vector<VectorSymbolElement *> elements;
			std::vector<Combin *> combins;

			//
			LithoItem():id(-1),name(""),type(VST_Unknown),scale(1.),indent(0),baseline(true),dual(true),turn(true)
			{

			}
			~LithoItem()
			{

			}

			/*!
			*
			**/
			const LithoItem &operator=(const LithoItem &other)
			{
				if(this == &other)
				{
					return *this;
				}

				id=other.id;
				name=other.name;
				type=other.type;
				scale=other.scale;
				indent=other.indent;
				baseline=other.baseline;
				dual=other.dual;
				turn=other.turn;
				m_itemMapExtent=other.m_itemMapExtent;

				elements.clear();
				for(int i=0;i<other.elements.size();i++)
					elements.push_back(other.elements[i]);
				combins.clear();
				for(int i=0;i<other.combins.size();i++)
					combins.push_back(other.combins[i]);

				return *this;
			}
		};

		struct LithoClolor
		{
			std::string id;
			std::string name;
			ColorStyle style;

			LithoClolor(): id(""),name("")
			{
				style.m_alpha=0;
			}
		};

		struct VectorSymbol
		{
			int m_idx;// UNIQUE
			string m_name; 
			int m_leanType;//0-center, 1-left, 2-right
			double m_widthRate;//scale:0-1
			int indent;
			bool baseline;
			bool dual;
			bool turn;

			CGeoRect<double> m_symbolMapPort;//samples' map port 
			CGeoRect<double> m_positionMapPort;//map position in component
			CGeoRect<double> m_positionScrPort;//screen position in component

			LithoItem m_litho;
			LithoItem m_inclusion;
			LithoItem m_prefix;
			LithoItem m_struct;
			LithoItem m_oiloccrence;
			LithoClolor m_backgroundColor;

			VectorSymbol() : m_idx(-1), m_name(""), m_leanType(0), m_widthRate(1.), indent(0),baseline(true),dual(true),turn(true)/*,m_elementnumber(0)*/
			{				
				m_litho.type=CAnyVectorSymbolPlot::LAT_Litho;				
				m_inclusion.type=CAnyVectorSymbolPlot::LAT_Inclusion;				
				m_prefix.type=CAnyVectorSymbolPlot::LAT_Prefix;				
				m_struct.type=CAnyVectorSymbolPlot::LAT_Struct;			
				m_oiloccrence.type=CAnyVectorSymbolPlot::LAT_Oiloccurence;
			}

			~VectorSymbol()
			{
			}

			const VectorSymbol &operator=(const VectorSymbol &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_idx=other.m_idx;
				m_name=other.m_name;
				m_leanType=other.m_leanType;
				m_widthRate=other.m_widthRate;
				indent=other.indent;
				baseline=other.baseline;
				dual=other.dual;
				turn=other.turn;
				m_symbolMapPort=other.m_symbolMapPort;
				m_positionMapPort=other.m_positionMapPort;
				m_positionScrPort=other.m_positionScrPort;

				m_litho=other.m_litho;
				m_inclusion=other.m_inclusion;
				m_prefix=other.m_prefix;
				m_struct=other.m_struct;
				m_oiloccrence=other.m_oiloccrence;
				m_backgroundColor=other.m_backgroundColor;

				return *this;
			}

			bool Add(CAnyVectorSymbolPlot::VectorSymbolElement *element);
			bool Remove(int idx);
			void Align(std::vector<int> &idxes, short type);
			void Map2Scr(CGeoPoint<double> &mappt, CGeoPoint<double> &scrpt);
			void Scr2Map(CGeoPoint<double> &scrpt, CGeoPoint<double> &mappt);
			bool RenderSymbol(CAnyCanvas &canvas,bool isturn=false);
			void Release();
			void DrawElement(CAnyCanvas &canvas, VectorSymbolElement *element, const CGeoRect<double> &extentFrom, const CGeoRect<double> &extentTo,bool isturn=false);
		};
		typedef std::map<string, VectorSymbol> VectorSymbolMap;
		typedef VectorSymbolMap::iterator vsm_itr;
		typedef VectorSymbolMap::const_iterator vsm_citr;
		
		struct WellSymbol
		{
			int id;//value
			std::string name;

			//extent
			CGeoRect<double> m_itemMapExtent;

			//shapes
			std::vector<VectorSymbolElement *> elements;
			std::vector<Combin *> combins;

			//
			WellSymbol():id(-1),name("")
			{

			}
			~WellSymbol()
			{

			}

			/*!
			*
			**/
			const WellSymbol &operator=(const WellSymbol &other)
			{
				if(this == &other)
				{
					return *this;
				}

				id=other.id;
				name=other.name;
				m_itemMapExtent=other.m_itemMapExtent;

				elements.clear();
				for(int i=0;i<other.elements.size();i++)
					elements.push_back(other.elements[i]);
				combins.clear();
				for(int i=0;i<other.combins.size();i++)
					combins.push_back(other.combins[i]);

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
		CAnyVectorSymbolPlot(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyVectorSymbolPlot();

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
		//
		//
		/*!
		*
		**/
		bool IsDataLegal();
		
		//
		//
		//
		void Release();
		bool Add(VectorSymbolElement *element);
		bool Remove(int idx);
		VectorSymbolElement *FindElement(const CGeoPoint<double> &scrPt);

		void SetMapPort();
		void GetBorderExtent(CGeoRect<double> &mapExtent);

		/*!
		*2016/4/15: get cloned element
		**/
		VectorSymbolElement *CloneElement(VectorSymbolElement *element);

		/*!
		*2016/3/15: save/load elements
		**/
		static std::string GetElementsBlobContent(std::vector<VectorSymbolElement *> &elements);
		static bool SetElementsByBlobContent(std::vector<CAnyVectorSymbolPlot::VectorSymbolElement *> &elements, std::string *str_pt);

		void DrawElement(CAnyCanvas &canvas, VectorSymbolElement *element, const CGeoRect<double> &extentFrom, const CGeoRect<double> &extentTo);
		void RenderVectorSymbol(CAnyCanvas &canvas);
		void Scr2Map(LithoItem *litem);
		void Scr2Map(WellSymbol *wsymbol);
		void Scr2Map_Elements(std::vector<VectorSymbolElement *> &elements, CGeoRect<double> &mapextent);
		/*!
		*
		**/
		static void RenderSymbolToExtent(CAnyCanvas &canvas, CAnyView &curView, const CGeoRect<double> &theRect, VectorSymbol &vectorSymbol, bool drawborderline=true);
		/*!
		*
		**/
		static std::string EncodingVectorSymbol(VectorSymbol &vs);
		/*!
		*
		**/
		static bool DecodingVectorSymbol(VectorSymbol &vs,std::string *str_pt);
		/*!
		*
		**/
		static std::string EncodingLithoItem(LithoItem &litem);
		/*!
		*
		**/
		static bool DecodingLithoItem(LithoItem &litem,std::string *str_pt);
	private:
		static std::string GetVSSBlobContent(VectorSymbolStyle *style);
		static void SetVSSBlobContent(VectorSymbolStyle * &style, std::string &str);

		/*!
		*2016/4/15: Set VectorSymbolStyle
		**/
		void SetVectorSymbolStyle(VectorSymbolStyle * &cloneStyle, VectorSymbolStyle * style);
	public:
		int m_curSymbolType;
		std::vector<VectorSymbolElement *> m_elements;
		std::vector<VectorSymbolElement *> m_selectedElements;//2016/5/10
		std::vector<VectorSymbolElement *> m_inclusion_elements;
		std::vector<VectorSymbolElement *> m_prefix_elements;
		std::vector<VectorSymbolElement *> m_struct_elements;
		std::vector<VectorSymbolElement *> m_oiloccrence_elements;
		ColorStyle m_backgroundColor;

		VectorSymbol vs;

		int m_operation;//VectorSymbolOperation
	
		//2016/4/26: switch of grid line
		bool m_isRenderGrid;
		double m_gridStep;
	private:
		//2016/4/15: for element movement
		VectorSymbolElement *m_pickElement;
		CGeoPoint<double> m_prePos;// every mouse position

		//2016/4/20: record points in a curve
		bool m_isMoveDown;
		std::vector<CGeoPoint<double> > m_curveScrCoords;
	};
}
#endif