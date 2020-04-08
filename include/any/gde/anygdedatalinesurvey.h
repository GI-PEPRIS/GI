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
#ifndef __ANYGDE_SAMPLE_DATA_LINE_SURVEY_H__
#define __ANYGDE_SAMPLE_DATA_LINE_SURVEY_H__

// refer to EXPORT & IMPORT macroes
#include "anygde.h"

// refer to parent
#include "anygdedatasurvey.h"

// 
namespace AnyGDE
{
	/*!
	* ֱ����CDP�ֲ�������CDP��һ��ֱ���ϣ�����CDP��ȼ��Ҳ�Ⱥž࣬CDP�ŵ�����ݼ�
	**/
	class ANYGDE_CLASS CAnyGdeDataLineSurvey : public CAnyGdeDataSurvey
	{
	public:
		/*!
		*
		**/
		struct LineSurvey
		{
			// ����ԭ�㶫����
			double m_oriEast;
			//����ԭ�㱱����
			double m_oriNorth;
			//����ԭ��CDP��
			double m_oriCDPNo;
			//CDP�ż������ԶΪ��
			double m_CDPNoInterval;
			//CDP����������ԶΪ��
			double m_CDPDistInterval;
			//���߷�λ�ǣ�CDPС�ŵ���ŵķ�����x�᷽��ļн�,0��2PI
			double m_azmuith;
			//�����ߺ�
			double m_lineNo;
			//�����ϵ�CDP����
			int	   m_CDPNumInLine;
			//������е���ԭ�����᷽��Ϊtrue����Ϊfalse
			bool m_bCDPPositive;

			/*!
			*
			**/
			LineSurvey()
			{
				m_oriEast = 0;
				m_oriNorth = 0;
				m_oriCDPNo = 0;
				m_CDPNoInterval = 1;
				m_CDPDistInterval = 25;
				m_azmuith = PI / 2;	
				m_lineNo = 0;
				m_CDPNumInLine = 0;
				m_bCDPPositive = true;
			}

			/*!
			*
			**/
			LineSurvey(const LineSurvey &other)
			{
				*this = other;
			}

			/*!
			*
			**/
			const LineSurvey &operator=(const LineSurvey &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_oriEast = other.m_oriEast;
				m_oriNorth = other.m_oriNorth;
				m_oriCDPNo = other.m_oriCDPNo;
				m_CDPNoInterval = other.m_CDPNoInterval;
				m_CDPDistInterval = other.m_CDPDistInterval;
				m_azmuith = other.m_azmuith;//ȱʡˮƽ����
				m_lineNo = other.m_lineNo;
				m_CDPNumInLine = other.m_CDPNumInLine;
				m_bCDPPositive = other.m_bCDPPositive;

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
		CAnyGdeDataLineSurvey(const LineSurvey &survey);

		/*!
		*
		**/
		~CAnyGdeDataLineSurvey();

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
		long GetTotalTraceNumber()
		{
			return m_survey.m_CDPNumInLine;
		}

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
		CAnyGdeDataIterator *CreateInLineIterator(long lineNo)
		{
			return CreateIterator();
		}

		/*!
		*
		**/
		CAnyGdeDataIterator *CreatePolygonIterator(CAnyGdeDataPolygon &poly);
	
		/*!
		*
		**/
		CAnyGdeDataProcessBin *GetProcessBin(long sequenceOrder, int binSize);

	public:
		//
		LineSurvey m_survey;
		
		// for performance issue
		double m_sina;
		double m_cosa;
	};
}
#endif