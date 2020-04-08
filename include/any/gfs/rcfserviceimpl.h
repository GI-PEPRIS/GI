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
#ifndef __ANYRCF_RCF_SERVICE_IMPL_H__
#define __ANYRCF_RCF_SERVICE_IMPL_H__

//
#include "anyrcf.h"
#include "anyserviceimpl.h"
#include "anyeventimpl.h"
#include "rcfservicebasic.h"
#include "anyclientimpl.h"

//
namespace AnyRCF
{
	class CEventServant;

	/*!
	* its servant and as client or stub as another service
	**/
	class ANYRCF_CLASS CRCFServiceImpl : public CAnyServiceImpl, public CAnyEventImpl, protected CRCFServiceBasic
	{
	public:
		/*!
		*
		**/
		template<typename Signature>
		struct RCFRequestCookie : public RequestCookie
		{
			typedef boost::function<Signature> RequestFunction;
			RequestFunction m_function;

			RCF::RemoteCallContextImpl *m_context;
		};
		typedef std::map<string, boost::function<void(const string&)> > CallbackMap;

	protected:
		//
		//
		//
		/*!
		*
		**/
		CRCFServiceImpl();
		virtual ~CRCFServiceImpl();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool Init(const ServiceHandle &handle);
		void GetHandle(ServiceHandle &handle);
		bool DoPrepareThread();
		bool Login(const LoginInfo &info);
		virtual bool OnAccess(int dispatchId);				// work with Login() calling
		void Stop();
		void Suspend();
		void Resume(bool isstopheart = false, bool isstopbroadcast = false, bool isstoprequest = false);
		bool IsRunning();

		void NetworkBandwidthAsSender(std::string &ip, int port, int calls, int buflen);
		void NetworkBandwidthAsReceiver(int calls, int buflen);

		SessionObjectVector QuerySessionObject();
		void ClearSessionObject(const string &clientAddr);

		/*!
		*
		**/
		void SetJobSpecification(const JobSpecification &specification){};
		void InitDB(short type, const std::string &srcname, const std::string &user, const std::string &pwd, const std::string &dbname){};
		void GetDB(MasterDBConnection &conn){};
		void SetMapTask(const JobTaskServer &task){};
		void SetReduceTask(const JobTaskServer &task){};

		/*!
		* simple or direct communication
		**/
		void SetClientName(const std::string &name);
		void SetResponseUserData();

		//
		//
		//
		/*!
		*
		**/
		void RegisterChildren(int type, const ServiceHandle &handle);
		void DoQueueRegisterChildren(long key);
		void DoDirectRegisterChildren(int type, const ServiceHandle &handle);

		void RemoveChildren(string &ip, int port);
		void DoQueueRemoveChildren(long key);
		bool DoDirectRemoveChildren(string &ip, int port);
		
		void GetChildren(int type, ServiceVector &handles);
		void DoQueueGetChildren(long key);
		bool DoDirectGetChildren(int type, ServiceVector &handles);
		
		void DoQueueAddRequestEntry(RequestCookie *cookie);
		void BindTo(int type, string &ip, int port);
		virtual CAnyClientImpl *DoDirectBindTo(int type, string &ip, int port);

		void CollectHeartbeat(const ServiceHandle &handle, const MasterChunkServer &chunkstatus, const JobTaskServer &taskstatus);
		void DoQueueCollectHeartBeat(long key);
		void DoDirectCollectHeartbeat(const ServiceHandle &handle, const MasterChunkServer &chunkstatus, const JobTaskServer &taskstatus);
		bool DoReadyToBeat();
		void OnHeartbeat();
		virtual void DoCollectServerStatus(ServiceHandle &handle, MasterChunkServer &chunkstatus, JobTaskServer &taskstatus)
		{
		}

		bool IsChildrenCrashed(const ServiceHandle &childrenhandle);

		//
		// thread-function
		//
		/*!
		*
		**/
		void DispatchMessageThread();
		void DispatchRequestThread();
		virtual void DoScheduleEntries(std::deque<RequestEntry *> &entries) = 0;

		//
		//
		//
		/*!
		* as client be called and not a remote calling function
		**/
		void RegisterCallback(string &topic, boost::function<void(const string&)> function); 

		//
		// deprecated functions: publish\subscribe
		//
		void SetEventHandle(const ServiceHandle &eventhandle);
		void SetLocationHandle(const ServiceHandle &locationhandle);
		void OnSubscriptionDisconnected(RCF::RcfSession & session);

		//
		//
		//
		/*!
		* broadcast
		**/
		void Listen(const std::string &multicastip, int multicastport);
		void Notify(short topic, const string &multicastip, long multicastport)
		{
			DoDirectNotify(topic, multicastip, multicastport, m_handle);
		}
		void DoDirectNotify(short topic, const string &multicastip, long multicastport, const ServiceHandle &which);
		virtual void OnNotify();

	protected:
		//
		//
		//
		/*!
		* Serialization and deserialization of remote call parameters can become a performance bottleneck.\
		* In particular, deserialization of a complex datatype involves \
		* not only creating the object to begin with, but also a number of memory allocations (and CPU cycles) when deserializing all the fields and subfields of the object.
		* ClearFunction = boost::function1<void, Parameter*>
		**/
		template<typename Parameter, typename ClearFunction>
		void EnableCaching()
		{
			RCF::ObjectPool & cache = RCF::getObjectPool();

			// Enable caching for std::string.
			// * Don't cache more than 10 std::string objects.
			// * Call std::string::clear() before putting a string into the cache.
			cache.enableCaching<Parameter>(10, ClearFunction/*boost::bind(&std::string::clear, _1)*/);
		}
		template<typename Parameter>
		void DisableCaching()
		{
			// Disable caching for std::string.
			cache.disableCaching<Parameter>();
		}
		void SetServerAdvancedSetting();

	public:
		// RCF skeleton as a server
		RCF::RcfServer m_server;
		
		// broadcast
		RCF::RcfServer m_listener;
		CEventServant *m_broadcast;

		// request entries for intent schedule
		std::deque<RequestEntry *> m_rEntries;
		// request cookies
		std::map<long, RequestCookie*> m_rCookies;
		// callbacks
		CallbackMap m_callbacks;

		// thread configure
		RCF::ThreadPoolPtr m_poolThreadPtr;
		RCF::ThreadPtr	*m_requestThreadPtr;
		RCF::ThreadPtr m_heartThreadPtr;
		RCF::ThreadPtr m_broadcastThreadPtr;

		// thread mutex
		RCF::Mutex m_childrenMutex;
		RCF::Mutex m_parentMutex;
		RCF::Mutex m_queueMutex;
		RCF::Mutex m_cbMutex; // callback, Server-side - taking control of callback connections.

		//
		// common services
		//

		// event subscribers
		ServiceHandle m_eventhandle;
		CAnyClientImpl *m_eventclient;
		RCF::Mutex m_subscriberMutex; 
		std::map<short, std::vector<RCF::SubscriptionPtr> > m_subscribers;

		// server status related to m_children
		std::map<unsigned long long, MasterChunkServer> m_chunkserverstatus;
		std::map<unsigned long long, JobTaskServer> m_taskserverstatus;

		// geo location servant
		ServiceHandle m_geolocation_handle;
		CAnyClientImpl *m_geolocation_client;

		// Session Objects
		SessionObjectVector m_sessions;
	};
}
#endif