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
#ifndef __ANYVIS_FUZZY_INFERENCE_H__
#define __ANYVIS_FUZZY_INFERENCE_H__

// refer to macro
#include "anyvis.h"

// refer to view hook
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to axis parent
#include "anyaxises.h"

// refer to geometry basic
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyFuzzyInference : public CAnyViewHook, private CAnyAxises
	{
	public:
		/*!
		*
		**/
		struct MemberFunction
		{
			// parameters for triangular and trapezodial 
			// member function
			CGeoPoint<double> m_upper;
			CGeoPoint<double> m_lower;
			CGeoPoint<double> m_right;
			CGeoPoint<double> m_left;
			string m_name;
			string m_favorability;

			// output
			int m_ptNumber;
			CGeoPoint<double> *m_pts;

			/*!
			*
			**/
			MemberFunction() : m_ptNumber(0), m_pts(0)
			{
			}
		};
		typedef std::map<string, MemberFunction> FunctionMap;
		typedef FunctionMap::iterator func_itr;
		typedef FunctionMap::const_iterator func_citr;

		/*!
		*
		**/
		enum MemberValueType
		{
			MVT_Unknown = -1,
			MVT_Categorial,
			MVT_Ordinal,
			MVT_Rational,
			MVT_Max,
		};

		/*!
		*
		**/
		enum MemberFunctionType
		{
			MFT_Unknown = -1,
			MFT_Triangular,
			MFT_Trapezodial,
			MFT_Max,
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyFuzzyInference(CAnyView &curView, short funcType = MFT_Trapezodial, short valueType = MVT_Ordinal);

		/*!
		*
		**/
		~CAnyFuzzyInference();

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
		**/
		void SetSuccessor(CAnyFuzzyInference *successor);

		/*!
		*
		**/
		CAnyFuzzyInference *GetSuccessor() const
		{
			assert(m_successor);
			return m_successor;
		}

		/*!
		*
		**/
		void GetDefuzzyScore(double &score, double &lower, double &upper)
		{
			lower = m_lower;
			score = m_centroid.m_x;
			upper = m_upper;
		}

		/*!
		*
		**/
		void MoveTo(CGeoPoint<double> &mapPt);

		/*!
		*
		**/
		void MoveTo(const string &memberName);

		//
		// 
		//
		/*!
		*
		**/
		void SetMemberType(short type);

		/*!
		*
		**/
		short GetMemberType() const;

		/*!
		*
		**/
		void SetValueType(short type);

		/*!
		*
		**/
		short GetValueType() const;

		/*!
		*
		**/
		void Add(MemberFunction &member);

		/*!
		*
		**/
		void Clear();

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

	private:
		//
		//
		//
		/*!
		*
		**/
		void Defuzzification();

		/*!
		*
		**/
		void HandleChain(MemberFunction &prevMember, CGeoPoint<double> &value);

		//
		//
		//
		/*!
		*
		**/
		void GetMapExtent(CGeoRect<double> &mapExtent);

		/*!
		*
		**/
		void ConstructPolyLines();

		/*!
		*
		**/
		void GetMemberSet(const CGeoPoint<double> &scrPoint);

		//
		//
		//
		/*!
		*
		**/
		void DoRenderCategorial(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderOrdinal(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderCursor(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRenderCursorLine(CAnyCanvas &canvas, CGeoPoint<double> &mapCursor);

		/*!
		*
		**/
		void DoRenderPolygon(CAnyCanvas &canvas);

	private:
		// member function type
		short m_funcType;

		// member value type
		// Note:
		// if "if-else" part seems clumsy, it had better to use inheritence 
		// to polymophsim those kinds of value
		// ...
		short m_valueType;

		// member functions
		FunctionMap m_functions;
		// the value vector of fuzzy set
		std::vector<CGeoPoint<double> > m_members;

		// current position which for getting m_members
		double m_cursor;
		// indicator for moving cursor 
		bool m_isCaptured;

		// the successor fuzzy inference
		CAnyFuzzyInference *m_successor;
		// polygon for defuzzification
		std::vector<CGeoPoint<double> > m_vertexes;
		// centroid
		CGeoPoint<double> m_centroid;
		double m_lower;
		double m_upper;
	};
}

#endif