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
#ifndef __ANYMAP_VIEW_H__
#define __ANYMAP_VIEW_H__

// refer to export
#include "anymap.h"

// refer to sreenport etc structure
#include "anyviewbasic.h"

// AnyMap
namespace AnyMap
{
	// forward class
	class CAnyViewImpl;
	class CAnyViewHook;

	/*!
	*
	**/
	class ANYMAP_CLASS CAnyView
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyView(short type);

		/*!
		*
		**/
		~CAnyView();

	private:
		//
		CAnyView(const CAnyView &other);
		const CAnyView operator=(const CAnyView &other);

	public:
		//
		//
		//
		/*!
		*
		**/
		bool Attach(void *curWnd, const ScreenPort &scrPort);
		void Detach();
		void *GetBMP();	//for bitmap generation etc by outside
		void *GetDC();

		//
		//
		//
		/*!
		*
		**/
		void SetScrPort(const ScreenPort &scrPort);
		const ScreenPort &GetScrPort() const;
		void SetMapPort(const MapPort &mapPort, bool isUnion = true, double zoomCoff = 1.);
		const MapPort &GetMapPort() const;
		double GetZoomCoff();
		bool Scr2Map(const CGeoPoint<double> &scrPoint, CGeoPoint<double> &mapPoint);
		bool Map2Scr(CGeoPoint<double> &mapPoint, CGeoPoint<double> &scrPoint);
		void GetMapExtent(const CGeoRect<double> &scrExtent, CGeoRect<double> &mapExtent);
		void ZoomIn(double scalecoff = 2.);
		void ZoomOut(double scalecoff = 2.);
		void ZoomFull();	//  full map
		void MoveTo(const CGeoPoint<double> &pos, double angle);	//Note: It is invalid to select commands

		//
		//
		//
		/*!
		*
		**/
		void RegisterHook(CAnyViewHook *curHook);
		void RemoveHook(CAnyViewHook *curHook, bool isDeleted = true);
		CAnyViewHook *GetHook(const string &name);
		int GetHookCount();
		CAnyViewHook *GetHook(long order); //idx means order
		void Refresh(bool isDirect = false);
		void OnPaint(bool isDirect = false);
		void RefreshHook(int idx);

		//
		// map operation
		//
		/*!
		*
		**/
		void SetMapOpterationMode(unsigned int moMode);
		unsigned int GetMapOperationMode();
		CGeoPoint<double> *GetTrackPoints(int &number);	//after once map operation, get track points
		void ReleaseTrackPoints();

		//
		// human-interaction interface
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);
		bool MouseMove(const CGeoPoint<double> &scrPoint);
		bool MouseUp(const CGeoPoint<double> &scrPoint);
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		//
		//
		//
		static long NextHookIdx();

	private:
		//
		//
		//
		CAnyViewImpl *GetViewImpl(short type);

	private:
		// handle object
		CAnyViewImpl *m_impl;
	};
}

#endif