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
#ifndef __ANYBRIDGE_DXF_H__
#define __ANYBRIDGE_DXF_H__

// Refer to EXPORT & IMPORT 
#include "anybridge.h"

// Refer to portable type definitions
#include "any/base/anyport.h"

// refer to dir and file basic
#include "any/base/anydirbasic.h"
#include "any/base/anyfilebasic.h"
using namespace AnyBase;

// Refer to DBF basic definitions
#include "anydxfbasic.h"

// Erase compiling warnings
#pragma warning( push )
#pragma warning( disable: 4251 )  //  needs to have dll-interface
#pragma warning( disable: 4996 )  //  needs to have dll-interface

// Declare namespace
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyDxfReader
	{

	public:

		struct CodePair 
		{
			int m_Code;
			std::string m_Value;

			CodePair()
			{
			}

			~CodePair()
			{
			}

			/// <summary>
			/// Initialize a new instance of the CodePair object. 
			/// </summary>
			/// <param name="Code">Numeric DXF code</param>
			/// <param name="Value">The value of the corresponding code</param>
			/// <returns>A DXF Vector2d object</returns>
			CodePair(int Code, const std::string &Value) 
			{
				m_Code = Code;
				m_Value = Value;
			}
		};
		
		enum Encoding
		{
			ASCII =0,
			UTF8,
		};
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyDxfReader(const anystring &file, int encoding=0);

		/*!
		*
		**/
		CAnyDxfReader();

		/*!
		*
		**/
		~CAnyDxfReader();

	public:
		//
		//
		//
		/**
		*
		**/
		bool Open();

		/**
		*
		**/
		void Release();

		/// <summary>
		/// Read and parse the DXF file
		/// </summary>
		bool Read();

		/// <summary>
		/// Reads a code/value pair at the current line from DXF file
		/// </summary>
		/// <returns>A CodePair object containing code and value for the current line pair</returns>
		CodePair ReadPair();

		/// <summary>
		/// Reads the SECTION name from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A string containing the section name</returns>
		std::string ReadSection(CodePair &code);

		/// <summary>
		/// Reads the LINE data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Line object with layer and two point data</returns>
		AnyBridge::Line ReadLine(CodePair &code);

		/// <summary>
		/// Reads the ARC data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>An Arc object with layer, center point, radius, start angle and end angle data</returns>
		AnyBridge::Arc ReadArc(CodePair &code);

		/// <summary>
		/// Reads the LWPOLYLINE data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Polyline object with layer, closed flag and vertex list data</returns>
		AnyBridge::Polyline ReadLwPolyline(CodePair &code);

		/// <summary>
		/// Reads the POLYLINE data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Polyline object with layer, closed flag and vertex list data</returns>
		AnyBridge::Polyline ReadPolyline(CodePair &code);

		/// <summary>
		/// Reads the VERTEX data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Vertex object with layer, position and bulge data</returns>
		AnyBridge::Vertex ReadVertex(CodePair &code);

		/// <summary>
		/// Reads the CIRCLE data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Circle object with layer, center point and radius data</returns>
		AnyBridge::Circle ReadCircle(CodePair &code);

		/// <summary>
		/// Reads the POINT data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Point object with layer and position data</returns>
		AnyBridge::Point ReadPoint(CodePair &code);

		/// <summary>
		/// Reads the TEXT data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Text object with layer, value (text) and position data</returns>
		AnyBridge::Text ReadText(CodePair &code);

		/// <summary>
		/// Reads the LAYER data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>A Layer object with name and AciColor index</returns>
		AnyBridge::Layer ReadLayer(CodePair &code);

		/// <summary>
		/// Reads the HEADER data from the DXF file
		/// </summary>
		/// <param name="code">A reference to the current CodePair read</param>
		/// <returns>Extent of the DXF map</returns>
		CGeoRect<double> ReadHeader( CodePair &code );

		/*!
		*
		**/
		const anystring &GetFileName();
	
		/*!
		*
		**/
		void SetFileName(const anystring &file);
				
		/*!
		*
		**/
		string GetMTEXTValue(string mtext);

	private:

		// File name
		anystring m_fileName;

		// Path basic functions
		const CAnyDirBasic &m_pathBasic;

		//General declarations
		 //StreamReader dxfReader;
		ifstream *m_dxfReader;
		int m_dxfLinesRead;

		int m_encoding;
	public:
		std::vector<AnyBridge::Layer> m_Layers;
		std::vector<AnyBridge::Line> m_Lines;
		std::vector<AnyBridge::Polyline> m_Polylines;
		std::vector<AnyBridge::Circle> m_Circles;
		std::vector<AnyBridge::Arc> m_Arcs;
		std::vector<AnyBridge::Text> m_Texts;
		std::vector<AnyBridge::Point> m_Points;

		CGeoRect<double> m_extent;
	};
}
#endif
