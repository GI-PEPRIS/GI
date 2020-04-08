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
#ifndef __ANYBRIDGE_LOG_TEXT_TRACK_H__
#define __ANYBRIDGE_LOG_TEXT_TRACK_H__

// refer to EXPORT & IMPORT
#include "anybridge.h"

// refer to its parent
#include "anylogpicktrack.h"

//
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyLogTextTrack : public CAnyLogPickTrack
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyLogTextTrack();

		/*!
		*
		**/
		~CAnyLogTextTrack();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoRenderTrack(CAnyCanvas &canvas, const CGeoRect<double> &validExtent, bool isDirect, CAnyView &curView, int &namesize, double &labelscale, LabelStyle &lablestyle);
	};
}
#endif