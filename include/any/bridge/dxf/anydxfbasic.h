/*
 * The UrbanEye PND solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy one kind
 * of mobile or portable devices with competitive qualities being a leading one.
 *
 * Copyright (C) 2008 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Graduate School
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYBRIDGE_DXFBASIC_H__
#define __ANYBRIDGE_DXFBASIC_H__


// refer to stl
#include "any/base/anystl.h"
#include "any/base/anygeom.h"
using namespace AnyBase;

// Declare namespace
namespace AnyBridge
{
	struct Vector2d 
	{
		double m_X;
		double m_Y;

		Vector2d()
		{
			m_X = 0.;
			m_Y = 0.;
		}

		/// <summary>
		/// Initialize a new instance of the Vector2d object. 
		/// </summary>
		/// <param name="X">X coordinate</param>
		/// <param name="Y">Y coordinate</param>
		/// <returns>A DXF Vector2d object</returns>
		Vector2d(double X, double Y) 
		{
			m_X = X;
			m_Y = Y;
		}

		const Vector2d &operator=(const Vector2d &other)
		{
			if(this == &other)
			{
				return *this;
			}

			//
			m_X = other.m_X;
			m_Y = other.m_Y;			
			return *this;								
		}


		/// <summary>
		/// Gets a Vector2d at the origin (0,0)
		/// </summary>
		/// <returns>A DXF Vector2d object</returns>
		static Vector2d Zero() 
		{
			return Vector2d(0, 0);
		}
	};

	/// <summary>
	/// Defines a DXF vertex, with position, bulge and layer
	/// </summary>
	struct Vertex 
	{
		Vector2d m_Position;
		double m_Bulge;
		std::string m_Layer;
		int m_mark;

		/// <summary>
		/// Initialize a new instance of the Vertex object. Bulge and Layer are optional (defaults to 0).
		/// </summary>
		/// <param name="Location">A Vector2d containg X and Y coordinates</param>
		/// <param name="Bulge">The tangent of 1/4 the included angle for an arc segment. Negative if the arc goes clockwise from the start point to the endpoint.</param>
		/// <param name="Layer">Layer name</param>
		/// <returns>A DXF Vertex object</returns>
		Vertex(const Vector2d &Location, double Bulge = 0, const std::string &Layer = "0", int mark=0) 
		{
			m_Position = Location;
			m_Bulge = Bulge;
			m_Layer = Layer;
			m_mark = mark;
		}

		/// <summary>
		/// Initialize a new instance of the Vertex object. Bulge and Layer are optional (defaults to 0).
		/// </summary>
		/// <param name="X">X coordinate</param>
		/// <param name="Y">Y coordinate</param>
		/// <param name="Bulge">The tangent of 1/4 the included angle for an arc segment. Negative if the arc goes clockwise from the start point to the endpoint.</param>
		/// <param name="Layer">Layer name</param>
		/// <returns>A DXF Vertex object</returns>
		Vertex(double X, double Y, double Bulge = 0, const std::string &Layer = "0", int mark=0) 
		{
			//m_Position = Vector2d(0, 0);
			m_Position.m_X = X;
			m_Position.m_Y = Y;
			m_Bulge = Bulge;
			m_Layer = Layer;
			m_mark = mark;
		}
	};

	/// <summary>
	/// Defines a DXF layer, with it's name and AciColor code
	/// </summary>
	struct Layer 
	{
		string m_Name;
		int m_ColorIndex;

		/// <summary>
		/// Initialize a new instance of the Layer object
		/// </summary>
		/// <param name="Name">Layer name</param>
		/// <param name="ColorIndex">The AciColor index for the layer</param>
		/// <returns>A DXF Layer object</returns>
		Layer(const std::string &Name, int ColorIndex) 
		{
			m_Name = Name;
			m_ColorIndex = ColorIndex;
		}
	};

	/// <summary>
	/// Defines a DXF line, with starting and ending point
	/// </summary>
	struct Line 
	{
		Vector2d m_P1;
		Vector2d m_P2;
		std::string m_Layer;

		Line(){}

		/// <summary>
		/// Initialize a new instance of the Line object
		/// </summary>
		/// <param name="P1">A Vector2d containg X and Y coordinates of the first point</param>
		/// <param name="P2">A Vector2d containg X and Y coordinates of the second point</param>
		/// <param name="Layer">Layer name</param>
		/// <returns>A DXF Line object</returns>
		Line(const Vector2d &P1, const Vector2d &P2, const std::string &Layer) 
		{
			m_P1 = P1;
			m_P2 = P2;
			m_Layer = Layer;
		}

	};

	/// <summary>
	/// Defines a DXF polyline, with it's layer, vertex list and closed flag
	/// </summary>
	struct Polyline 
	{
		string m_Layer;
		std::vector<Vertex> m_Vertexes;
		bool m_Closed;

		/// <summary>
		/// Initialize a new instance of the Polyline object
		/// </summary>
		/// <param name="Vertexes">A Vertex list containg X and Y coordinates of each vertex</param>
		/// <param name="Layer">Layer name</param>
		/// <param name="Closed">Determine if the polyline is opened or closed</param>
		/// <returns>A DXF Polyline object</returns>
		Polyline(const std::vector<Vertex> &Vertexes, const std::string &Layer, bool Closed)
		{
			m_Vertexes = Vertexes;
			m_Layer = Layer;
			m_Closed = Closed;
		}
	};

	/// <summary>
	/// Defines a DXF circle, with it's layer, center point and radius
	/// </summary>
	struct Circle 
	{
		double m_Radius;
		Vector2d m_Center;
		string m_Layer;

		/// <summary>
		/// Initialize a new instance of the Circle object
		/// </summary>
		/// <param name="Center">A Vector2d containg X and Y center coordinates</param>
		/// <param name="Radius">Circle radius</param>
		/// <param name="Layer">Layer name</param>
		/// <returns>A DXF Circle object</returns>
		Circle(const Vector2d &Center, double Radius, const std::string &Layer) 
		{
			m_Center = Center;
			m_Radius = Radius;
			m_Layer = Layer;
		}
	};

	/// <summary>
	/// Defines a DXF arc, with it's layer, center point, radius, start and end angle
	/// </summary>
	struct Arc 
	{
		std::string m_Layer;
		Vector2d m_Center;
		double m_Radius;
		double m_StartAngle;
		double m_EndAngle;

		/// <summary>
		/// Initialize a new instance of the Arc object
		/// </summary>
		/// <param name="Center">A Vector2d containg X and Y center coordinates</param>
		/// <param name="Radius">Arc radius</param>
		/// <param name="StartAng">Starting angle, in degrees</param>
		/// <param name="EndAng">Ending angle, in degrees</param>
		/// <param name="Layer">Layer name</param>
		/// <returns>A DXF Arc object</returns>

		Arc(const Vector2d &Center, double Radius, double StartAng, double EndAng, const std::string &Layer) 
		{
			m_Center = Center;
			m_Radius = Radius;
			m_StartAngle = StartAng;
			m_EndAngle = EndAng;
			m_Layer = Layer;
		}
	};

	/// <summary>
	/// Defines a DXF text, with its layer, node point and text value
	/// </summary>
	struct Text 
	{
		std::string m_Value;
		std::string m_Layer;
		Vector2d m_Position;

		/// <summary>
		/// Initialize a new instance of the Text object
		/// </summary>
		/// <param name="Position">A Vector2d containg  X and Y coordinates</param>
		/// <param name="Value">The text string itself</param>
		/// <param name="Layer">Layer name</param>
		/// <returns>A DXF Text object</returns>
		Text(const Vector2d &Position, const string &Value, const string &Layer) 
		{
			m_Position = Position;
			m_Value = Value;
			m_Layer = Layer;
		}
	};

	/// <summary>
	/// Defines a DXF point, with it's layer and position
	/// </summary>
	struct Point 
	{
		Vector2d m_Position;
		std::string m_Layer;

		/// <summary>
		/// Initialize a new instance of the Point object
		/// </summary>
		/// <param name="Position">A Vector2d containg X and Y coordinates</param>
		/// <param name="Layer">Layer name</param>
		/// <returns>A DXF Point object</returns>
		Point(const Vector2d &Position, const string &Layer) 
		{
			m_Position = Position;
			m_Layer = Layer;
		}
	};

	//
	//const static double PI = 3.14159265358979323846264338327950288419716939937510;

	/// <summary>
	/// Helper class to create polygonal vertexes for circles, arcs and polylines.
	/// </summary>
	struct VertexConverter 
	{
		/// <summary>
		/// Multiply this by an angle in degress to get the result in radians
		/// </summary>
		double DegToRad;

		/// <summary>
		/// Multiply this by an angle in radians to get the result in degrees
		/// </summary>
		double RadToDeg;

		VertexConverter()
		{
			DegToRad = PI / 180.0;
			RadToDeg = 180.0 / PI;
		}

		/// <summary>
		/// Get circle vertexes using a given precision. Higher the precision, smoother the circle shape, with an increase in vertex count.
		/// </summary>
		/// <param name="entity">The circle entity</param>
		/// <param name="precision">Shape precision (number of edges). Must be equal or higher than 3</param>
		/// <returns>A 2D vector list containing the circle shape</returns>
		std::vector<Vector2d> GetCircleVertexes(const Circle &entity, int precision = 3) 
		{
			std::vector<Vector2d> coords;
			double X, Y, R, increment;

			X = entity.m_Center.m_X;
			Y = entity.m_Center.m_Y;
			R = entity.m_Radius;

			if (precision < 3)
				precision = 3;

			//High-school unit circle math ;)
			increment = PI * 2 / precision;
			for (int i = 0; i < precision; i++) 
			{
				double sin = ::sin(increment * i) * R;
				double cos = ::cos(increment * i) * R;

				coords.push_back(Vector2d(X + cos, Y + sin));
			}

			return coords;
		}

		/// <summary>
		/// Get arc vertexes using a given precision. Higher the precision, smoother the arc curve, with an increase in vertex count.
		/// </summary>
		/// <param name="entity">The arc entity</param>
		/// <param name="precision">Arc precision (number of segments). Must be equal or higher than 2</param>
		/// <returns>A 2D vector list containing the arc shape</returns>
		std::vector<Vector2d> GetArcVertexes(const Arc &entity, int precision = 2)
		{
			//
			DegToRad = PI / 180.0;
			RadToDeg = 180.0 / PI;

			//
			std::vector<Vector2d> coords;

			double start = (entity.m_StartAngle * DegToRad);
			double end = (entity.m_EndAngle * DegToRad);
			double angle;

			if (precision < 2)
				precision = 2;

			//Gets the angle increment for the given precision
			if (start > end)
				angle = (end + ((2 * PI) - start)) / precision;
			else
				angle = (end - start) / precision;

			//Basic unit circle math to calculate arc vertex coordinate for a given angle and radius
			for (int i = 0; i <= precision; i++) 
			{
				double sine = (entity.m_Radius * ::sin(start + angle * i));
				double cosine = (entity.m_Radius * ::cos(start + angle * i));
				coords.push_back(Vector2d(cosine + entity.m_Center.m_X, sine + entity.m_Center.m_Y));
			}

			return coords;
		}

		/// <summary>
		/// Get polyline vertexes using a given precision. Higher precision, smoother the polyline curves will be, with an increase in vertex count.
		/// </summary>
		/// <param name="entity">The polyline entity</param>
		/// <param name="precision">Curve precision (number of segments). Must be equal or higher than 2</param>
		/// <returns>A 2D vector list containing all the polyline vertexes, including straight and curved segments</returns>
		std::vector<Vector2d> GetPolyVertexes(const Polyline &entity, int precision = 2) 
		{
			std::vector<Vector2d> coords;

			if (precision < 2)
				precision = 2;

			for (int i = 0; i < entity.m_Vertexes.size(); i++) 
			{
				if (entity.m_Vertexes[i].m_Bulge == 0) 
				{
					coords.push_back(Vector2d(entity.m_Vertexes[i].m_Position.m_X, entity.m_Vertexes[i].m_Position.m_Y));
				}
				else
				{
					if (i != entity.m_Vertexes.size() - 1) 
					{
						double bulge = entity.m_Vertexes[i].m_Bulge;
						double p1x = entity.m_Vertexes[i].m_Position.m_X;
						double p1y = entity.m_Vertexes[i].m_Position.m_Y;
						double p2x = entity.m_Vertexes[i + 1].m_Position.m_X;
						double p2y = entity.m_Vertexes[i + 1].m_Position.m_Y;

						//Definition of bulge, from Autodesk DXF fileformat specs
						double angulo = ::fabs(::atan(bulge) * 4);
						bool girou = false;

						//For my method, this angle should always be less than 180. 
						if (angulo >= PI) 
						{
							angulo = PI * 2 - angulo;
							girou = true;
						}

						//Distance between the two vertexes, the angle between Center-P1 and P1-P2 and the arc radius
						double distancia = ::sqrt(::pow(p1x - p2x, 2) + ::pow(p1y - p2y, 2));
						double alfa = (PI - angulo) / 2;
						double raio = distancia * ::sin(alfa) / ::sin(angulo);

						double xc, yc, angulo1, angulo2, multiplier, incr;

						//Used to invert the signal of the calculations below
						if (bulge < 0)
							multiplier = 1;
						else
							multiplier = -1;

						//Calculates the arc center
						if (!girou) 
						{
							xc = ((p1x + p2x) / 2) - multiplier * ((p1y - p2y) / 2) * ::sqrt((::pow(2 * raio / distancia, 2)) - 1);
							yc = ((p1y + p2y) / 2) + multiplier * ((p1x - p2x) / 2) * ::sqrt((::pow(2 * raio / distancia, 2)) - 1);
						}
						else 
						{
							xc = ((p1x + p2x) / 2) + multiplier * ((p1y - p2y) / 2) * ::sqrt((::pow(2 * raio / distancia, 2)) - 1);
							yc = ((p1y + p2y) / 2) - multiplier * ((p1x - p2x) / 2) * ::sqrt((::pow(2 * raio / distancia, 2)) - 1);
						}

						//Invert start and end angle, depending on the bulge (clockwise or counter-clockwise)
						if (bulge < 0) 
						{
							angulo1 = PI + ::atan2(yc - entity.m_Vertexes[i + 1].m_Position.m_Y, xc - entity.m_Vertexes[i + 1].m_Position.m_X);
							angulo2 = PI + ::atan2(yc - entity.m_Vertexes[i].m_Position.m_Y, xc - entity.m_Vertexes[i].m_Position.m_X);
						} 
						else 
						{
							angulo1 = PI + ::atan2(yc - entity.m_Vertexes[i].m_Position.m_Y, xc - entity.m_Vertexes[i].m_Position.m_X);
							angulo2 = PI + ::atan2(yc - entity.m_Vertexes[i + 1].m_Position.m_Y, xc - entity.m_Vertexes[i + 1].m_Position.m_X);
						}

						//If it's more than 360, subtract 360 to keep it in the 0~359 range
						if (angulo1 >= PI * 2) angulo1 -= PI * 2;
						if (angulo2 >= PI * 2) angulo2 -= PI * 2;

						//Calculate the angle increment for each vertex for the given precision
						if (angulo1 > angulo2)
							incr = (angulo2 + ((2 * PI) - angulo1)) / precision;
						else
							incr = (angulo2 - angulo1) / precision;

						//Gets the arc coordinates. If bulge is negative, invert the order
						if (bulge > 0) 
						{
							for (int a = 0; a <= precision; a++)
							{
								double sine = (::fabs(raio) * ::sin(angulo1 + incr * a));
								double cosine = (::fabs(raio) * ::cos(angulo1 + incr * a));
								coords.push_back(Vector2d(cosine + xc, sine + yc));
							}
						} 
						else
						{
							for (int a = precision; a >= 0; a--) 
							{
								double sine = (::fabs(raio) * ::sin(angulo1 + incr * a));
								double cosine = (::fabs(raio) * ::cos(angulo1 + incr * a));
								coords.push_back(Vector2d(cosine + xc, sine + yc));
							}
						}
					}

				}
			}
			
			return coords;
		}

	};

	/// <summary>
	/// AciColor class, containing all the AciColor codes and ARGB converters
	/// </summary>
	struct AciColor 
	{
		int m_index;

		//Hex values (ARGB) for all the 256 ACI Color indexes
		std::vector<long> argb;
		

		AciColor()
		{
			Init();
		}

		/// <summary>
		/// Initialize a new instance of the AciColor object
		/// </summary>
		/// <param name="index">The AciColor index</param>
		/// <returns>An AciColor object</returns>
		AciColor(int index) 
		{
			Init();
			m_index = index;
		}

		void Init()
		{
			argb.clear();
			argb.push_back(0xFF000000);argb.push_back(0xFFFF0000);argb.push_back(0xFFFFFF00);argb.push_back(0xFF00FF00);argb.push_back(0xFF00FF00);argb.push_back(0xFF0000FF);argb.push_back(0xFFFF00FF);argb.push_back(0xFFFFFFFF);//007
			argb.push_back(0xFF414141);argb.push_back(0xFF808080);argb.push_back(0xFFFF0000);argb.push_back(0xFFFFAAAA);argb.push_back(0xFFBD0000);argb.push_back(0xFFBD7E7E);argb.push_back(0xFF810000);argb.push_back(0xFF815656);//015
			argb.push_back(0xFF680000);argb.push_back(0xFF684545);argb.push_back(0xFF4F0000);argb.push_back(0xFF4F3535);argb.push_back(0xFFFF3F00);argb.push_back(0xFFFFBFAA);argb.push_back(0xFFBD2E00);argb.push_back(0xFFBD8D7E);//023
			argb.push_back(0xFF811F00);argb.push_back(0xFF816056);argb.push_back(0xFF681900);argb.push_back(0xFF684E45);argb.push_back(0xFF4F1300);argb.push_back(0xFF4F3B35);argb.push_back(0xFFFF7F00);argb.push_back(0xFFFFD4AA);//031
			argb.push_back(0xFFBD5E00);argb.push_back(0xFFBD9D7E);argb.push_back(0xFF814000);argb.push_back(0xFF816B56);argb.push_back(0xFF683400);argb.push_back(0xFF685645);argb.push_back(0xFF4F2700);argb.push_back(0xFF4F4235);//039
			argb.push_back(0xFFFFBF00);argb.push_back(0xFFFFEAAA);argb.push_back(0xFFBD8D00);argb.push_back(0xFFBDAD7E);argb.push_back(0xFF816000);argb.push_back(0xFF817656);argb.push_back(0xFF684E00);argb.push_back(0xFF685F45);//047
			argb.push_back(0xFF4F3B00);argb.push_back(0xFF4F4935);argb.push_back(0xFFFFFF00);argb.push_back(0xFFFFFFAA);argb.push_back(0xFFBDBD00);argb.push_back(0xFFBDBD7E);argb.push_back(0xFF818100);argb.push_back(0xFF818156);//055
			argb.push_back(0xFF686800);argb.push_back(0xFF686845);argb.push_back(0xFF4F4F00);argb.push_back(0xFF4F4F35);argb.push_back(0xFFBFFF00);argb.push_back(0xFFEAFFAA);argb.push_back(0xFF8DBD00);argb.push_back(0xFFADBD7E);//063
			argb.push_back(0xFF608100);argb.push_back(0xFF768156);argb.push_back(0xFF4E6800);argb.push_back(0xFF5F6845);argb.push_back(0xFF3B4F00);argb.push_back(0xFF494F35);argb.push_back(0xFF7FFF00);argb.push_back(0xFFD4FFAA);//071
			argb.push_back(0xFF5EBD00);argb.push_back(0xFF9DBD7E);argb.push_back(0xFF408100);argb.push_back(0xFF6B8156);argb.push_back(0xFF346800);argb.push_back(0xFF566845);argb.push_back(0xFF274F00);argb.push_back(0xFF424F35);//079
			argb.push_back(0xFF3FFF00);argb.push_back(0xFFBFFFAA);argb.push_back(0xFF2EBD00);argb.push_back(0xFF8DBD7E);argb.push_back(0xFF1F8100);argb.push_back(0xFF608156);argb.push_back(0xFF196800);argb.push_back(0xFF4E6845);//087
			argb.push_back(0xFF134F00);argb.push_back(0xFF3B4F35);argb.push_back(0xFF00FF00);argb.push_back(0xFFAAFFAA);argb.push_back(0xFF00BD00);argb.push_back(0xFF7EBD7E);argb.push_back(0xFF008100);argb.push_back(0xFF568156);//095
			argb.push_back(0xFF006800);argb.push_back(0xFF456845);argb.push_back(0xFF004F00);argb.push_back(0xFF354F35);argb.push_back(0xFF00FF3F);argb.push_back(0xFFAAFFBF);argb.push_back(0xFF00BD2E);argb.push_back(0xFF7EBD8D);//103
			argb.push_back(0xFF00811F);argb.push_back(0xFF568160);argb.push_back(0xFF006819);argb.push_back(0xFF45684E);argb.push_back(0xFF004F13);argb.push_back(0xFF354F3B);argb.push_back(0xFF00FF7F);argb.push_back(0xFFAAFFD4);//111
			argb.push_back(0xFF00BD5E);argb.push_back(0xFF7EBD9D);argb.push_back(0xFF008140);argb.push_back(0xFF56816B);argb.push_back(0xFF006834);argb.push_back(0xFF456856);argb.push_back(0xFF004F27);argb.push_back(0xFF354F42);//119
			argb.push_back(0xFF00FFBF);argb.push_back(0xFFAAFFEA);argb.push_back(0xFF00BD8D);argb.push_back(0xFF7EBDAD);argb.push_back(0xFF008160);argb.push_back(0xFF568176);argb.push_back(0xFF00684E);argb.push_back(0xFF45685F);//127
			argb.push_back(0xFF004F3B);argb.push_back(0xFF354F49);argb.push_back(0xFF00FFFF);argb.push_back(0xFFAAFFFF);argb.push_back(0xFF00BDBD);argb.push_back(0xFF7EBDBD);argb.push_back(0xFF008181);argb.push_back(0xFF568181);//135
			argb.push_back(0xFF006868);argb.push_back(0xFF456868);argb.push_back(0xFF004F4F);argb.push_back(0xFF354F4F);argb.push_back(0xFF00BFFF);argb.push_back(0xFFAAEAFF);argb.push_back(0xFF008DBD);argb.push_back(0xFF7EADBD);//143
			argb.push_back(0xFF006081);argb.push_back(0xFF567681);argb.push_back(0xFF004E68);argb.push_back(0xFF455F68);argb.push_back(0xFF003B4F);argb.push_back(0xFF35494F);argb.push_back(0xFF007FFF);argb.push_back(0xFFAAD4FF);//151
			argb.push_back(0xFF005EBD);argb.push_back(0xFF7E9DBD);argb.push_back(0xFF004081);argb.push_back(0xFF566B81);argb.push_back(0xFF003468);argb.push_back(0xFF455668);argb.push_back(0xFF00274F);argb.push_back(0xFF35424F);//159
			argb.push_back(0xFF003FFF);argb.push_back(0xFFAABFFF);argb.push_back(0xFF002EBD);argb.push_back(0xFF7E8DBD);argb.push_back(0xFF001F81);argb.push_back(0xFF566081);argb.push_back(0xFF001968);argb.push_back(0xFF454E68);//167
			argb.push_back(0xFF00134F);argb.push_back(0xFF353B4F);argb.push_back(0xFF0000FF);argb.push_back(0xFFAAAAFF);argb.push_back(0xFF0000BD);argb.push_back(0xFF7E7EBD);argb.push_back(0xFF000081);argb.push_back(0xFF565681);//175
			argb.push_back(0xFF000068);argb.push_back(0xFF454568);argb.push_back(0xFF00004F);argb.push_back(0xFF35354F);argb.push_back(0xFF3F00FF);argb.push_back(0xFFBFAAFF);argb.push_back(0xFF2E00BD);argb.push_back(0xFF8D7EBD);//183
			argb.push_back(0xFF1F0081);argb.push_back(0xFF605681);argb.push_back(0xFF190068);argb.push_back(0xFF4E4568);argb.push_back(0xFF13004F);argb.push_back(0xFF3B354F);argb.push_back(0xFF7F00FF);argb.push_back(0xFFD4AAFF);//191
			argb.push_back(0xFF5E00BD);argb.push_back(0xFF9D7EBD);argb.push_back(0xFF400081);argb.push_back(0xFF6B5681);argb.push_back(0xFF340068);argb.push_back(0xFF564568);argb.push_back(0xFF27004F);argb.push_back(0xFF42354F);//199
			argb.push_back(0xFFBF00FF);argb.push_back(0xFFEAAAFF);argb.push_back(0xFF8D00BD);argb.push_back(0xFFAD7EBD);argb.push_back(0xFF600081);argb.push_back(0xFF765681);argb.push_back(0xFF4E0068);argb.push_back(0xFF5F4568);//207
			argb.push_back(0xFF3B004F);argb.push_back(0xFF49354F);argb.push_back(0xFFFF00FF);argb.push_back(0xFFFFAAFF);argb.push_back(0xFFBD00BD);argb.push_back(0xFFBD7EBD);argb.push_back(0xFF810081);argb.push_back(0xFF815681);//215
			argb.push_back(0xFF680068);argb.push_back(0xFF684568);argb.push_back(0xFF4F004F);argb.push_back(0xFF4F354F);argb.push_back(0xFFFF00BF);argb.push_back(0xFFFFAAEA);argb.push_back(0xFFBD008D);argb.push_back(0xFFBD7EAD);//223
			argb.push_back(0xFF810060);argb.push_back(0xFF815676);argb.push_back(0xFF68004E);argb.push_back(0xFF68455F);argb.push_back(0xFF4F003B);argb.push_back(0xFF4F3549);argb.push_back(0xFFFF007F);argb.push_back(0xFFFFAAD4);//231
			argb.push_back(0xFFBD005E);argb.push_back(0xFFBD7E9D);argb.push_back(0xFF810040);argb.push_back(0xFF81566B);argb.push_back(0xFF680034);argb.push_back(0xFF684556);argb.push_back(0xFF4F0027);argb.push_back(0xFF4F3542);//239
			argb.push_back(0xFFFF003F);argb.push_back(0xFFFFAABF);argb.push_back(0xFFBD002E);argb.push_back(0xFFBD7E8D);argb.push_back(0xFF81001F);argb.push_back(0xFF815660);argb.push_back(0xFF680019);argb.push_back(0xFF68454E);//247
			argb.push_back(0xFF4F0013);argb.push_back(0xFF4F353B);argb.push_back(0xFF333333);argb.push_back(0xFF505050);argb.push_back(0xFF696969);argb.push_back(0xFF828282);argb.push_back(0xFFBEBEBE);argb.push_back(0xFFFFFFFF);//255  
		}

		/// <summary>
		/// Convert current AciColor to ARGB
		/// </summary>
		/// <returns>32bit unsigned integer with the color in ARGB format</returns>
		long ToARGB() 
		{
			if (m_index > 255 || m_index < 0)
				return 0;
			else
				return argb[m_index];
		}

		/// <summary>
		/// Convert any AciColor value to ARGB
		/// </summary>
		/// <param name="ACIColor">The AciColor index, from 0 to 2055</param>
		/// <returns>32bit unsigned integer with the color in ARGB format</returns>
		long ACItoARGB(const AciColor &color)
		{
			if (color.m_index > 255 || color.m_index < 0)
				return 0;
			else
				return argb[color.m_index];
		}
	};
}
#endif