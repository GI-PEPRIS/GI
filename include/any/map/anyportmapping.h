/*!
 * The AnyMap of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYMAP_PORT_MAPPING_H__
#define __ANYMAP_PORT_MAPPING_H__

//
#include "anyviewbasic.h"

//
namespace AnyMap
{
	/*!
	*
	**/
	class CAnyPortMapping
	{
		// relative
		friend class CAnyViewImpl;
		friend class CWinViewImpl;
		friend class CAnyPanCommand;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyPortMapping();

		/*!
		*
		**/
		~CAnyPortMapping();

    protected:
		//
		//
		//
		/*!
		*
		*/
		void SetMapPort(const MapPort &layout, bool isUnion);

		/*!
		*
		**/
		void SetScrPort(const ScreenPort &scrLayout);

		/*!
		*
		**/
		void SetZoomCoff(double zoomCoff);

    protected:
		//
		double m_zoomCoff;
		//
		ScreenPort m_scrPort;
		//
		MapPort m_mapPort;

		// Values for performance
		double m_cos;
		double m_sin;
		long m_cosExt;
		long m_sinExt;
		double m_sinMulByScale;
		double m_cosMulByScale;
		double m_sinDivByScale;
		double m_cosDivByScale;
	};
}

#endif
