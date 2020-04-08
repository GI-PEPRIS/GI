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
#ifndef __ANYGDE_SAMPLE_DATA_GRID_SURVEY_H__
#define __ANYGDE_SAMPLE_DATA_GRID_SURVEY_H__

// refer to EXPORT & IMPORT macroes
#include "anygde.h"

// refer to parent
#include "anygdedatasurvey.h"

// 
namespace AnyGDE
{
	/*!
	* 规则网格型CDP分布,等线间距、等道间距、等线号间隔、等道号间隔，并且每条线上的CDP个数相同。
	* 线号和道号增减规律整个网格一致
	**/
	class ANYGDE_CLASS CAnyGdeDataGridSurvey : public CAnyGdeDataSurvey
	{
	public:
		/*!
		*
		**/
		struct GridSurvey
		{
			//测网原点东坐标
			double m_oriEast;
			//测网原点北坐标
			double m_oriNorth;
			//测网原点CDP号
			double m_oriCDPNo;
			//测网原点线号
			double m_oriLineNo;
			//CDP号间隔，永远为正
			double m_CDPNoInterval;
			//CDP道距间隔，永远为正
			double m_CDPDistInterval;
			//线号间隔，可能为负
			double m_lineNoInterval;
			//线距间隔，永远为正
			double m_lineDistInterval;
			//测网方位角，CDP小号到大号的方向，与x轴方向的夹角,0到2PI
			double m_azmuith;
			//测网中每条测线上的CDP道数
			int m_CDPNumInLine;
			//测网中的测线个数
			int m_lineNum;
			//如果所有道在原点正轴方向为true否则为false
			bool m_bCDPPositive;
			//如果所有线在原点正轴方向为true否则为false
			bool m_bLinePositive;

			/*!
			*
			**/
			GridSurvey()
			{
				m_oriEast = 0;
				m_oriNorth = 0;
				m_oriCDPNo = 0;
				m_oriLineNo = 0;
				m_CDPNoInterval = 1;
				m_CDPDistInterval = 25;
				m_lineNoInterval = 1;
				m_lineDistInterval = 100;
				m_CDPNumInLine = 0;
				m_lineNum = 0;
				m_bCDPPositive = true;
				m_bLinePositive = true;
				m_azmuith = PI / 2;	
			}

			/*!
			*
			**/
			GridSurvey(const GridSurvey &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const GridSurvey &operator=(const GridSurvey &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_oriEast = other.m_oriEast;
				m_oriNorth = other.m_oriNorth;
				m_oriCDPNo = other.m_oriCDPNo;
				m_oriLineNo = other.m_oriLineNo;
				m_CDPNoInterval = other.m_CDPNoInterval;
				m_CDPDistInterval = other.m_CDPDistInterval;
				m_lineNoInterval = other.m_lineNoInterval;
				m_lineDistInterval = other.m_lineDistInterval;
				m_CDPNumInLine = other.m_CDPNumInLine;
				m_lineNum = other.m_lineNum;
				m_bCDPPositive = other.m_bCDPPositive;
				m_bLinePositive = other.m_bLinePositive;
				m_azmuith = other.m_azmuith;

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
		CAnyGdeDataGridSurvey(const GridSurvey &survey);

		/*!
		*
		**/
		~CAnyGdeDataGridSurvey();

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
		CAnyGdeDataIterator *CreateInLineIterator(long lineNo);

		/*!
		*
		**/
		CAnyGdeDataIterator *CreateCrossLineIterator(long cdpNo);

		/*!
		*
		**/
		CAnyGdeDataIterator *CreatePolygonIterator(CAnyGdeDataPolygon &poly);

		/*!
		*
		**/
		CAnyGdeDataProcessBin *GetProcessBin(long sequenceOrder, int binSize);

	private:
		//
		//
		//
		/*!
		*
		**/
		void DoGetPorfileWithCoord(CAnyGdeDataPolygon &poly);

	public:
		//
		GridSurvey m_survey;
		
		// for performance issue
		double m_sina;
		double m_cosa;
	};
}
#endif