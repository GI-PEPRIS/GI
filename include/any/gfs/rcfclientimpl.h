/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYRCF_RCF_STUB_IMPL_H__
#define __ANYRCF_RCF_STUB_IMPL_H__

//
#include "anyrcf.h"
#include "anyclientimpl.h"
#include "rcfservicebasic.h"

//
namespace AnyRCF
{
	/*!
	* its servant and as client or stub as another service
	**/
	class ANYRCF_CLASS CRCFClientImpl : public CAnyClientImpl, protected CRCFServiceBasic
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CRCFClientImpl()
		{
			m_init = RCF::RcfInitDeinit();
		}
		virtual ~CRCFClientImpl()
		{
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		void OnClientCallback(std::size_t bytesTransferred, std::size_t bytesTotal, RCF::ClientProgress::Trigger trigger, RCF::ClientProgress::Activity activity, RCF::ClientProgress::Action &action)
		{
			switch (trigger)
			{
				case RCF::ClientProgress::Event:
					//++gEventCallbacks;

					if (activity == RCF::ClientProgress::Connect) 
					{
						//++gEventCallbacksConnect;
					}

					if (activity == RCF::ClientProgress::Send) 
					{
						//++gEventCallbacksSend;
					}

					if (activity == RCF::ClientProgress::Receive) 
					{
						//++gEventCallbacksReceive;
					}

					break;

				case RCF::ClientProgress::Timer:
					//++gTimerCallbacks;
					break;

				case RCF::ClientProgress::UiMessage:

		//#ifdef BOOST_WINDOWS

		//			{
		//				MSG msg = {0};
		//				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//				{
		//					if (msg.message == WM_QUIT)
		//					{

		//					}
		//					else if (msg.message == WM_PAINT)
		//					{
		//						TranslateMessage(&msg);
		//						DispatchMessage(&msg);
		//					}
		//				}
		//			}

		//#endif

					//++gMessageFilterCallbacks;
					break;

				default:
					RCF_ASSERT(0);
			}
			//action = gAction;
			// To cancel the call...
			//action = RCF::ClientProgress::Cancel;
			// Or to continue the call.
			//action = RCF::ClientProgress::Continue;
		}

	protected:
		RCF::RcfInitDeinit m_init;
		//
		RCF::RcfServer m_callbackServer;
	};
}
#endif