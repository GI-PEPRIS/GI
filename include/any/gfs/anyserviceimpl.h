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
#ifndef __ANYRCF_SERVICE_IMPL_H__
#define __ANYRCF_SERVICE_IMPL_H__

//
#include "anyrcf.h"
#include "anyservicebasic.h"
#include "anyclientimpl.h"

//
//#define RPC_REQUESTENTRY 1

//
namespace AnyRCF
{
	/*!
	*
	**/
	class ANYRCF_CLASS CAnyServiceImpl
	{
	public:
		// directly declare its parent's stub
		typedef std::map<unsigned short, std::vector<CAnyClientImpl *> > ClientGroup;
		typedef ClientGroup::iterator stub_itr;
		typedef ClientGroup::const_iterator stub_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyServiceImpl()
		{
		}
		virtual ~CAnyServiceImpl()
		{
		}

	public:
		/*!
		*
		**/
		virtual bool Init(const ServiceHandle &handle) = 0;
		virtual void GetHandle(ServiceHandle &handle) = 0;
		virtual void Start() = 0;
		virtual bool Login(const LoginInfo &info) = 0;
		virtual void Stop() = 0;
		virtual void Suspend() = 0;
		virtual void Resume(bool isstopheart = false, bool isstopbroadcast = false, bool isstoprequest = false) = 0;
		virtual bool IsRunning() = 0;
		virtual void SetClientName(const std::string &name) = 0;
		virtual void SetResponseUserData() = 0;	// one messge way
		virtual void Callback(const std::string &topic) = 0;
		virtual void OnCallback(const std::string &topic) = 0;
		virtual void SetEventHandle(const ServiceHandle &eventhandle) = 0;

		/*!
		*
		**/
		virtual void RegisterChildren(int type, const ServiceHandle &handle) = 0;
		virtual void RemoveChildren(string &ip, int port) = 0;
		virtual void GetChildren(int type, ServiceVector &handles) = 0;

		virtual void BindTo(int type, string &ip, int port) = 0;	// directly declare the client stub of its parent service
		virtual void CollectHeartbeat(const ServiceHandle &handle,const MasterChunkServer &chunkstatus, const JobTaskServer &taskstatus) = 0;

		/*!
		*
		**/
		virtual void SetJobSpecification(const JobSpecification &specification) = 0;
		virtual void InitDB(short type, const std::string &srcname, const std::string &user, const std::string &pwd, const std::string &dbname) = 0;
		virtual void GetDB(MasterDBConnection &conn) = 0;
		virtual void SetMapTask(const JobTaskServer &task) = 0;
		virtual void SetReduceTask(const JobTaskServer &task) = 0;

	public:
		// service info
		ServiceHandle m_handle;
		// children services or chunk nodes
		ServiceGroup m_children;
		// bind to which parent or interested stubs
		ClientGroup m_parents;

		// request entries for intent schedule
		std::deque<RequestEntry *> m_rEntries;
		// request cookies for one function
		std::map<int, RequestCookie*> m_rCookies;
	};
}
#endif