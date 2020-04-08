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
#ifndef __ANYGDE_SAMPLE_DATA_POLY_SURVEY_H__
#define __ANYGDE_SAMPLE_DATA_POLY_SURVEY_H__

// refer to EXPORT & IMPORT macroes
#include "anygde.h"

// refer to parent
#include "anygdedatasurvey.h"

// 
namespace AnyGDE
{
	/*!
	* 折线型CDP分布。用于描述二维折线形式的CDP分布，这种折线由多个方位角不同的段构成。
	* 在具体段上CDP点具有相同的距离间隔和号间隔，在不同段上可以不相同。整个折线CDP号
	* 递增或递减，所以bCDPPositive必须全部为真或全部为假。
	* 该类同时可用于描述由规则Grid分布产生的连井线，这时它实际上是由原Grid中
	* inline方向线的多个段构成。他们有相同的方位角、道距，但有不同的线道号，在用该类
	* 进行描述时将忽略其原有线道号，使每段中：oriCDPNo＝oriCDPIndex，CDPNoInterval＝1
	* CDPDistInterval为规则Grid的CDP距离间隔，azmuith等于Grid的inLine方位角或相反，
	* bCDPPositive＝true。这样他们将暴露给外部的是相同的线号，CDP号与道序号相同。
	**/
	class ANYGDE_CLASS CAnyGdeDataPolySurvey : public CAnyGdeDataSurvey
	{
	public:
		/*!
		*
		**/
		struct PolySection
		{
			//该段上第一个CDP点的东坐标
			double m_oriCoorEast;
			//该段上第一个CDP点的北坐标
			double m_oriCoorNorth;
			//该段上第一个CDP点在整个线上的序号，从0开始
			int m_oriCDPIndex;
			//该段上的CDP个数
			int m_pointsInSection;
			//如果该段上的所有道在原点正轴方向为true否则为false
			bool m_bCDPPositive;
			//该段上的CDP距离间隔
			double m_CDPDistInterval;
			//该段的方位角
			double m_azmuith;
			//该段上第一个CDP点号
			double m_oriCDPNo;
			//CDP号间隔，永远为正
			double m_CDPNoInterval;
			//azmuith对应的Sin、Cos值，为提高运算效率而设，在指定azmuith时应同时指定
			double m_sina;
			double m_cosa;

			/*!
			*
			**/
			PolySection()
			{
				m_oriCoorEast = m_oriCoorNorth =0.0;
				m_oriCDPIndex = m_pointsInSection = 0;
				m_bCDPPositive = true;
				m_CDPDistInterval = 25;
				m_azmuith = PI/2;//缺省水平
				m_oriCDPNo = 0.0;
				m_CDPNoInterval = 1;
				m_sina = 1;
				m_cosa = 0;
			};
		};
		typedef std::vector<PolySection> SectionVector;
		typedef SectionVector::iterator sect_itr;
		typedef SectionVector::const_iterator sect_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataPolySurvey(const SectionVector &sections);

		/*!
		*
		**/
		~CAnyGdeDataPolySurvey();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool IsSame(CAnyGdeDataSurvey *other);

		/*!
		*
		**/
		long GetTotalTraceNumber();

		/*!
		*
		**/
		bool Coord2Survey(const CGeoPoint<double> &pt, double &lineNo, double &cdpNo);

		/*!
		*
		**/
		bool Survey2Coord(double lineNo, double cdpNo, CGeoPoint<double> &pt);	

		/*!
		*
		**/
		bool Survey2Sequence(double lineNo, double cdpNo, long &sequenceOrder);

		/*!
		*
		**/
		bool Sequence2Survey(long sequenceOrder, double &lineNo, double &cdpNo);

		/*!
		*
		**/
		bool Positionxy2Sequence(int Positionx, int Positiony, long &sequenceOrder);

		/*!
		*
		**/
		bool Sequence2Positionxy(long sequenceOrder, int &Positionx, int &Positiony);
		
		/*!
		*
		**/
		int GetLineIncrement();
				
		/*!
		*
		**/
		int GetCDPIncrement();

		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataIterator *CreatePolygonIterator(CAnyGdeDataPolygon &poly);

		/*!
		*
		**/
		CAnyGdeDataProcessBin *GetProcessBin(long sequenceOrder, int binSize);
		
		/*!
		*
		**/
		bool IsIntersect( CGeoPoint<double> p1, CGeoPoint<double> p2, CGeoPoint<double> p3, CGeoPoint<double> p4 );

		/*!
		*
		**/
		double CrossProduct( CGeoPoint<double> pii, CGeoPoint<double> pj, CGeoPoint<double> pk );
	public:
		//
		SectionVector m_sections;
		// line cursor
		long m_lineNo;
	};
}
#endif