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
#ifndef __ANYRCF_CLIENT_IMPL_H__
#define __ANYRCF_CLIENT_IMPL_H__

//
#include "anyrcf.h"
#include "anyservicebasic.h"

namespace AnyRCF
{
	/*!
	*
	**/
	class ANYRCF_CLASS CAnyClientImpl
	{
	public:
		CAnyClientImpl()
		{
		}
		virtual ~CAnyClientImpl()
		{
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		virtual void Init(const ServiceHandle &handle) = 0;
		virtual void Ping() = 0;
		virtual bool IsRunning() = 0;
		virtual void GetHandle(ServiceHandle &handle) = 0;
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual void Suspend() = 0;
		virtual void Resume(bool isstopheart, bool isstopbroadcast, bool isstoprequest) = 0;
		virtual string GetResponseUserData(const string &data) = 0;

		virtual void RegisterChildren(int type, const ServiceHandle &handle) = 0;
		virtual void RemoveChildren(string &ip, int port) = 0;
		virtual void GetChildren(int type, ServiceVector &handles) = 0;
		virtual void BindTo(int type, string &ip, int port) = 0;
		virtual void CollectHeartbeat(const ServiceHandle &handle, const MasterChunkServer &chunkstatus, const JobTaskServer &taskstatus) = 0;
		virtual void SetClientName(const std::string &name) = 0;
		virtual void Callback(const std::string &topic) = 0;

	public:
		//
		ServiceHandle m_handle;
	};
}
#endif