/*!
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
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
 * Resource Faculty
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYBASE_TIME_BASIC_H__
#define __ANYBASE_TIME_BASIC_H__

// Refer to EXPORT & IMPORT macroes
#include "anybase.h"

// Refer to tstring 
#include "anyport.h"

// Erase compile warnings
#pragma warning( push )
#pragma warning( disable: 4275 )  // X needs to have dll-interface to be used by clients of class Z
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z

// Declare namespace
namespace AnyBase
{
	///////////////////////////////////////////////////////////////////////
	// Note: This class is mainly referred to one source code recommended by codeguru and this class should be
	// limited to MS OS environment not one cross-platform class
	//
	class ANYBASE_CLASS CAnyTimeBasic
	{
#if _WIN32
		// OS-depedent time type which can be analized into year, month, etc basic information
		typedef double DATE;
		const static int MIN_DATE  = -657434;  // about year 100
		const static int MAX_DATE  = 2958465;    // about year 9999
#else
		#pragma message(__FILE__(" >> Here need one time type for one specified platform"))
#endif

	public:
		/*!
		*
		**/
		struct TimeReport
		{
			// Demands
			long m_year;
			long m_month;
			long m_day;
			long m_hour;
			long m_minute;
			long m_second;
			long m_dayOfWeek;

			//
			double m_latitude;
			double m_longitude;
			double m_zone;

			// Returned results
			double m_sunrise;
			double m_sunset;
			double m_noon;
			double m_sunpos;
			double m_morning;
			double m_dawn;

			/*!
			*
			**/
			TimeReport()
			{
				m_year = 0.;
				m_month = 0.;
				m_day = 0.;
				m_hour = 0.;
				m_minute = 0.;
				m_second = 0.;
				m_dayOfWeek = 0.;

				//
				m_latitude = 0.;
				m_longitude = 0.;
				m_zone = 0.;

				// Returned results
				m_sunrise = 0.;
				m_sunset = 0.;
				m_noon = 0.;
				m_sunpos = 0.;
				m_morning = 0.;
				m_dawn = 0.;
			};
		};

		/*!
		*
		**/
		CAnyTimeBasic();

		/*!
		*
		**/
		CAnyTimeBasic(CAnyTimeBasic& dateSrc);

		/*!
		*
		**/
		CAnyTimeBasic(double dtSrc);

		/*!
		*
		**/
		~CAnyTimeBasic();

	public:
		/*!
		*
		**/
		double GetNow(TimeReport &report);
		void GetSpecial(TimeReport &report);
		bool IsValid();

		/*!
		*
		**/
		void Double2Time(double timestamp, TimeReport &report);
		double Time2Double(TimeReport const& report);

		//
		//
		//
		/*!
		*
		**/
		const CAnyTimeBasic &operator =(CAnyTimeBasic& dateSrc);

		/*!
		*
		**/
		const CAnyTimeBasic &operator =(double dtSrc);

		/*!
		*
		**/
		bool operator ==(CAnyTimeBasic& date);

		/*!
		*
		**/
		bool operator !=(CAnyTimeBasic& date);

		/*!
		*
		**/
		bool operator < (CAnyTimeBasic& date);

		/*!
		*
		**/
		bool operator >(CAnyTimeBasic& date);

		/*!
		*
		**/
		bool operator <=(CAnyTimeBasic& date);

		/*!
		*
		**/
		bool operator >=(CAnyTimeBasic& date);

		/*!
		*
		**/
		operator double();

	private:
		//
		//
		//
		/*!
		*
		**/
		double Date2Double(DATE date);

		/*!
		*
		**/
		DATE Double2Date(double date);

		//
		// For calculating special time
		//
		/*!
		* Get the days to J2000
		* h is UT in decimal hours
		* FNday only works between 1901 to 2099 - see Meeus chapter 7
		**/
		static double FNday (long y, long m, long d, double h)
		{
			long luku = - 7 * (y + (m + 9)/12)/4 + 275*m/9 + d;

			// Typecasting needed for TClite on PC DOS at least, to avoid product overflow
			luku+= (long)(y*367);

			return (double)(luku - 730531.5 + h/24.0);
		}

		/*!
		* the function below returns an angle in the range
		* 0 to 2*pi
		**/
		static double FNrange (double x) 
		{
			double b = x / m_tpi;
			double a = m_tpi * (b - (long)(b));
			if (a < 0) a = m_tpi + a;
			return a;
		}

		/*!
		* Calculating the hourangle
		**/
		static double f0(double lat, double declin) 
		{
			double fo,dfo;
			// Correction: different sign at S HS
			dfo = m_rads*(0.5*m_sundia + m_airrefr); if (lat < 0.0) dfo = -dfo;
			fo = tan(declin + dfo) * tan(lat*m_rads);

			if (fo > 0.99999) fo=1.0; // to avoid overflow //
			fo = asin(fo) + m_pi/2.0;
			return fo;
		}

		/*!
		* Calculating the hourangle for twilight times
		**/
		static double f1(double lat, double declin) 
		{
			double fi,df1;
			// Correction: different sign at S HS
			df1 = m_rads * 6.0; if (lat < 0.0) df1 = -df1;
			fi = tan(declin + df1) * tan(lat*m_rads);

			if (fi > 0.99999) fi=1.0; // to avoid overflow //
			fi = asin(fi) + m_pi/2.0;
			return fi;
		}

		/*!
		* Find the ecliptic longitude of the Sun
		**/
		static double FNsun (double d) 
		{
			// mean longitude of the Sun
			m_L = FNrange(280.461 * m_rads + .9856474 * m_rads * d);

			// mean anomaly of the Sun
			m_g = FNrange(357.528 * m_rads + .9856003 * m_rads * d);

			// Ecliptic longitude of the Sun
			return FNrange(m_L + 1.915 * m_rads * sin(m_g) + .02 * m_rads * sin(2 * m_g));
		}

	private:
		// Time stamp and time output format
		DATE m_timeStamp;
		bool m_isValid;

		// Constant variables
		static const double m_pi;
		static const double m_tpi;
		static const double m_degs;
		static const double m_rads;

		static const double m_sundia;  // Sunradius degrees
		static const double m_airrefr; // athmospheric refraction degrees //

		static double m_L;
		static double m_g;
		static double m_daylen;
	};
}
#endif
