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
#ifndef __ANYGDE_SAMPLE_DATA_SURVEY_H__
#define __ANYGDE_SAMPLE_DATA_SURVEY_H__

// refer to EXPORT & IMPORT
#include "anygde.h"

// geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyGDE
{
	// forward class
	class CAnyGdeDataIterator;
	class CAnyGdeDataPolygon;
	class CAnyGdeDataProcessBin;

	/*!
	* The Curiously Recurring Template Pattern 
	**/
	class ANYGDE_CLASS CAnyGdeDataSurvey
	{
		//
		friend class CAnyGdeDataSet;

	public:
		//
		enum SurveyType
		{
			ST_Unknown,
			ST_Line,
			ST_Grid,
			ST_Poly
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeDataSurvey(int surveyType) : m_type(surveyType)
		{
		}

		/*!
		*
		**/
		virtual ~CAnyGdeDataSurvey()
		{
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual bool IsSame(CAnyGdeDataSurvey *other) = 0;

		/*!
		*
		**/
		virtual long GetTotalTraceNumber() = 0;

		/*!
		*
		**/
		virtual bool Coord2Survey(const CGeoPoint<double> &pt, double &lineNo, double &cdpNo) = 0;

		/*!
		*
		**/
		virtual bool Survey2Coord(double lineNo, double cdpNo, CGeoPoint<double> &pt) = 0;	

		/*!
		*
		**/
		virtual bool Survey2Sequence(double lineNo, double cdpNo, long &sequenceOrder) = 0;

		/*!
		*
		**/
		virtual bool Sequence2Survey(long sequenceOrder, double &lineNo, double &cdpNo) = 0;
		
		/*!
		*
		**/
		virtual bool Positionxy2Sequence(int Positionx, int Positiony, long &sequenceOrder) = 0;

		/*!
		*
		**/
		virtual bool Sequence2Positionxy(long sequenceOrder, int &Positionx, int &Positiony) = 0;
				
		/*!
		*
		**/
		virtual int GetLineIncrement() = 0;
				
		/*!
		*
		**/
		virtual int GetCDPIncrement() = 0;

		/*!
		*
		**/
		virtual bool Coord2Sequence(const CGeoPoint<double> &pt, long &sequenceOrder);

		/*!
		*
		**/
		virtual bool Sequence2Coord(long sequenceOrder, CGeoPoint<double> &pt);

		//
		//
		//
		/*!
		* factory method
		**/
		virtual CAnyGdeDataIterator *CreateIterator();

		/*!
		*
		**/
		virtual CAnyGdeDataIterator *CreateInLineIterator(long lineNo)
		{
			return 0;
		}

		/*!
		*
		**/
		virtual CAnyGdeDataIterator *CreateCrossLineIterator(long cdpNo)
		{
			return 0;
		}

		/*!
		*
		**/
		virtual CAnyGdeDataIterator *CreatePolygonIterator(CAnyGdeDataPolygon &poly)
		{
			return 0;
		}

		//
		//
		//
		/*!
		*
		**/
		virtual CAnyGdeDataProcessBin *GetProcessBin(long sequenceOrder, int binSize) = 0;

	protected:
		/*!
		*
		**/
		double Dither(double value,double dlt)
		{
			assert(dlt>0);

			if(value > 0)
				value+=dlt/2;
			else
				value-=dlt/2;

			return value;
		}

		/*!
		*
		**/
		double CalcAzmuith(double x1, double y1, double x2, double y2)
		{
			double alf=atan2((y2-y1),(x2-x1));
			if(alf<0)
				alf+=4*asin(1.0);

			return alf;
		}

	public:
		// survey type
		int m_type;
	};
}

#endif
