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
#ifndef __ANYMAP_VIEW_IMPL_H__
#define __ANYMAP_VIEW_IMPL_H__

// refer to basic structure such as ScreenPort
#include "anyviewbasic.h"

// refer to mapping
#include "anyportmapping.h"

//
namespace AnyMap
{
	// forward
	class CAnyViewHook;
	class CAnyViewCommand;

	/*!
	*
	**/
	class CAnyViewImpl
	{
		// relatives
		friend class CAnyView;
		friend class CAnyViewCommand;
		friend class CAnyPanCommand;
		friend class CAnyPickCommand;
		friend class CAnyViewHookComposite;

	protected:
		// Name aliases for view commands
		typedef std::map<short, CAnyViewCommand*> CommandMap;
		typedef CommandMap::iterator cmd_itr;
		typedef CommandMap::const_iterator cmd_citr;

		// hooks
		typedef std::vector<CAnyViewHook *> HookVector;
		typedef HookVector::iterator hook_itr;
		typedef HookVector::const_iterator hook_citr;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CAnyViewImpl();

		/*!
		*
		**/
		virtual ~CAnyViewImpl();

	private:
		//
		CAnyViewImpl(const CAnyViewImpl &other);
		const CAnyViewImpl &operator=(const CAnyViewImpl &other);

	protected:
		//
		//
		//
		/*!
		*
		**/
		virtual bool Attach(void *curWnd, const ScreenPort &scrPort) = 0;
		virtual void Detach() = 0;
		virtual void *GetBMP() = 0;
		virtual void *GetDC() = 0;

		//
		//
		//
		/*!
		*
		**/
		void SetScrPort(const ScreenPort &scrPort);
		const ScreenPort &GetScrPort() const
		{
			return m_mapping.m_scrPort;
		}
		void SetMapPort(const MapPort &mapPort, bool isUnion = true, double zoomCoff = 0.);
		const MapPort &GetMapPort() const
		{
			return m_mapping.m_mapPort;
		}
		double GetZoomCoff()
		{
			return m_mapping.m_zoomCoff;
		}
		bool Scr2Map(const CGeoPoint<double> &scrPoint, CGeoPoint<double> &mapPoint);
		bool Map2Scr(CGeoPoint<double> &mapPoint, CGeoPoint<double> &scrPoint);
		void GetMapExtent(const CGeoRect<double> &scrExtent, CGeoRect<double> &mapExtent);
		void ZoomIn(double scalecoff);
		void ZoomOut(double scalecoff);
		void ZoomFull();
		void ZoomExtent(const CGeoPoint<double> *pts, int number);
		void MoveTo(const CGeoPoint<double> &pos, double angle); //Note: It is invalid to select commands

		//
		//
		//
		/*!
		*
		**/
		void RegisterHook(CAnyViewHook *curHook);
		void RemoveHook(CAnyViewHook *curHook, bool isDeleted);
		CAnyViewHook *GetHook(const string &name);
		int GetHookCount();
		CAnyViewHook *GetHook(long order);

		/*!
		*
		**/
		virtual void Refresh(bool isDirect = false) = 0;
		virtual void OnPaint(bool isDirect = false) = 0;
		virtual void RefreshHook(int idx) = 0;

		//
		//
		//
		/*!
		*
		*/
		virtual bool MouseDown(const CGeoPoint<double> &scrPoint);
		virtual bool MouseMove(const CGeoPoint<double> &scrPoint);
		virtual bool MouseUp(const CGeoPoint<double> &scrPoint);
		virtual bool DoubleClick(const CGeoPoint<double> &scrPoint);

		//
		// map operation
		//
		/*!
		*
		**/
		void SetMapOpterationMode(unsigned int moMode);
		unsigned int GetMapOperationMode();
		CGeoPoint<double> *GetTrackPoints(int &number); //after once map operation, get track points
		void ReleaseTrackPoints();

		//
		//
		//
		/*!
		* factort method
		**/
		static CAnyViewImpl *GetViewImpl(short type);

	protected:
		//
		//
		//
		/*!
		*
		**/
		int GetCommandType();

		//
		//
		//
		/*!
		*
		*/
		virtual void UpFlash(const CGeoPoint<double> &start, const CGeoPoint<double> &end) = 0;

		/*!
		*
		*/
		virtual void PanFlash(const CGeoPoint<double> &start, const CGeoPoint<double> &end) = 0;

		//
		//
		//
		/*!
		*
		**/
		static bool CompareHookIdx(const CAnyViewHook *first, const CAnyViewHook *second);

		/*!
		*
		**/
		static bool CompareHookOrder(const CAnyViewHook *first, const CAnyViewHook *second);

	protected:
		// 
		CAnyPortMapping m_mapping;
		//
		CommandMap m_commands;
		//
		HookVector m_hooks;
		
		// map operation mode
		unsigned int m_moMode;
		std::vector<CGeoPoint<double> > m_moTrackPts;
	};
}

#endif