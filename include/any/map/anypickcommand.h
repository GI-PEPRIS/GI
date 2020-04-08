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
#ifndef __ANYMAP_VIEW_PICKCOMMAND_H__
#define __ANYMAP_VIEW_PICKCOMMAND_H__

// refer to its parent
#include "anyviewcommand.h"

//
namespace AnyMap
{
	/*!
	*
	**/
	class CAnyPickCommand : public CAnyViewCommand
	{
		// relatives
		friend class CAnyViewImpl;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyPickCommand(CAnyViewImpl *viewImpl);

		/*!
		*
		**/
		~CAnyPickCommand();

	public:
		//
		//
		//
		/*!
		* Note: It is invalid to timer command
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint, short mouseFlag = MF_Left);

		/*!
		* Note: It is invalid to timer and pan command
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint, short mouseFlag = MF_Left);

		/*!
		* Note: It is invalid to timer command
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint, short mouseFlag = MF_Left);

	private:
		// indicator whether the first to move

		// references to host view
		unsigned int &m_moMode;
		std::vector<CGeoPoint<double> > &m_moTrackPoints;
	};
}
#endif
