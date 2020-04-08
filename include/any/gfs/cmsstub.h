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
#ifndef __ANYRCF_CMS_STUB_H__
#define __ANYRCF_CMS_STUB_H__

//
#include "anyrcf.h"
#include "cmsservant.h"
#include "servicestub.h"

//
namespace AnyRCF
{
	//
	template class ANYRCF_CLASS CServiceStub<I_AnyCMS>;

	/*!
	*
	**/
	class ANYRCF_CLASS CCMSStub : public CServiceStub<I_AnyCMS>
	{
	public:
		CCMSStub()
		{
		}
		~CCMSStub()
		{
		}

	public:
		void Login(const LoginInfo &info)
		{
			try
			{
				m_client->Login(info);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
	};
}

#endif