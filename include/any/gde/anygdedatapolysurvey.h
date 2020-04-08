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
	* ������CDP�ֲ�������������ά������ʽ��CDP�ֲ������������ɶ����λ�ǲ�ͬ�Ķι��ɡ�
	* �ھ������CDP�������ͬ�ľ������ͺż�����ڲ�ͬ���Ͽ��Բ���ͬ����������CDP��
	* ������ݼ�������bCDPPositive����ȫ��Ϊ���ȫ��Ϊ�١�
	* ����ͬʱ�����������ɹ���Grid�ֲ������������ߣ���ʱ��ʵ��������ԭGrid��
	* inline�����ߵĶ���ι��ɡ���������ͬ�ķ�λ�ǡ����࣬���в�ͬ���ߵ��ţ����ø���
	* ��������ʱ��������ԭ���ߵ��ţ�ʹÿ���У�oriCDPNo��oriCDPIndex��CDPNoInterval��1
	* CDPDistIntervalΪ����Grid��CDP��������azmuith����Grid��inLine��λ�ǻ��෴��
	* bCDPPositive��true���������ǽ���¶���ⲿ������ͬ���ߺţ�CDP����������ͬ��
	**/
	class ANYGDE_CLASS CAnyGdeDataPolySurvey : public CAnyGdeDataSurvey
	{
	public:
		/*!
		*
		**/
		struct PolySection
		{
			//�ö��ϵ�һ��CDP��Ķ�����
			double m_oriCoorEast;
			//�ö��ϵ�һ��CDP��ı�����
			double m_oriCoorNorth;
			//�ö��ϵ�һ��CDP�����������ϵ���ţ���0��ʼ
			int m_oriCDPIndex;
			//�ö��ϵ�CDP����
			int m_pointsInSection;
			//����ö��ϵ����е���ԭ�����᷽��Ϊtrue����Ϊfalse
			bool m_bCDPPositive;
			//�ö��ϵ�CDP������
			double m_CDPDistInterval;
			//�öεķ�λ��
			double m_azmuith;
			//�ö��ϵ�һ��CDP���
			double m_oriCDPNo;
			//CDP�ż������ԶΪ��
			double m_CDPNoInterval;
			//azmuith��Ӧ��Sin��Cosֵ��Ϊ�������Ч�ʶ��裬��ָ��azmuithʱӦͬʱָ��
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
				m_azmuith = PI/2;//ȱʡˮƽ
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