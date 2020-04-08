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
#ifndef __ANYRCF_EVENT_SERVANT_H__
#define __ANYRCF_EVENT_SERVANT_H__

//
#include "anyrcf.h"
#include "rcfserviceimpl.h"

//
namespace AnyRCF
{
	// interface
	RCF_BEGIN(I_AnyEvent, "I_AnyEvent")
		//here is soft control(rcf server start/stop) hard control is implemented in console app using psService.
		RCF_METHOD_R1(bool, Init, const ServiceHandle&)
		RCF_METHOD_V1(void, GetHandle, ServiceHandle&)
		RCF_METHOD_V1(void, SetEventHandle, const ServiceHandle&)
		RCF_METHOD_V0(void, Start)
		RCF_METHOD_V2(void, Listen, const std::string&, short)
		RCF_METHOD_V3(void, Notify, short, const std::string&, long)
		RCF_METHOD_V0(void, Stop)
		RCF_METHOD_V3(void, Resume, bool, bool, bool)
		RCF_METHOD_V0(void, Suspend)
		RCF_METHOD_R0(bool, IsRunning)
		RCF_METHOD_V2(void, NetworkBandwidthAsReceiver, int, int)
		RCF_METHOD_V4(void, NetworkBandwidthAsSender, string&, int, int, int)
		RCF_METHOD_R0(SessionObjectVector, QuerySessionObject)
		RCF_METHOD_V1(void, ClearSessionObject, const string&)

		//console operate on chilren of cms
		RCF_METHOD_V2(void, RegisterChildren, int, const ServiceHandle&)
		RCF_METHOD_V2(void, RemoveChildren, string&, int)
		RCF_METHOD_V2(void, GetChildren, int, ServiceVector&)
		//communicate with cms e.g. heart beats
		RCF_METHOD_V3(void, BindTo, int, string&, int)
		RCF_METHOD_V3(void, CollectHeartbeat, const ServiceHandle&, const MasterChunkServer&, const JobTaskServer&)
		RCF_METHOD_V0(void, SetResponseUserData)
		RCF_METHOD_V1(void, SetClientName, const std::string&)
		RCF_METHOD_V1(void, Callback, const std::string&)
		RCF_METHOD_V1(void, OnCallback, const std::string&)	// response to callback
		//publish\subscribe
		RCF_METHOD_V1(void, ClearPublisher, short)
		RCF_METHOD_V2(void, SetPublisher, short, const ServiceHandle&)
		RCF_METHOD_V2(void, GetPublisher, short, std::vector<ServiceHandle>&)
		RCF_METHOD_V2(void, SetSubscriber, short, const ServiceHandle&)

		// broadcast
		RCF_METHOD_V2(void, Broadcast, const ServiceHandle&, short)
	RCF_END(I_AnyEvent)

	/*!
	* almost the same as RCFServiceImpl
	**/
	class ANYRCF_CLASS CEventServant : public CRCFServiceImpl
	{
		// publisher
		typedef RCF::Publisher<I_AnyEvent> EventPublisher;
		typedef boost::shared_ptr< EventPublisher > EventPublisherPtr;

		// callback
		typedef RcfClient<I_AnyEvent> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

	public:
		/*!
		*
		**/
		CEventServant();
		~CEventServant();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Start();
		void DoScheduleEntries(std::deque<RequestEntry *> &entries);

		//
		//
		//
		void OnNotify();
		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);

		//
		//
		//
		/*!
		*
		**/
		void SetPublisher(short topic, const ServiceHandle &whichservant);
		void DoDirectSetPublisher(short topic, const ServiceHandle &whichservant);

		void ClearPublisher(short topic);
		void GetPublisher(short topic, std::vector<ServiceHandle> &servants);

		void SetSubscriber(short topic, ServiceHandle &subscriber);
		void ClearSubscriber(short topic, ServiceHandle &subscriber);


	private:
		//
		//
		//
		/*!
		*
		**/
		bool OnSubscriberConnect(RCF::RcfSession & session, const std::string & topicName);
		void OnSubscriberDisconnect(RCF::RcfSession & session, const std::string & topicName);

		/*!
		*
		**/
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);

	private:
		// publishers
		RCF::Mutex m_publisherMutex;
		std::map<short, EventPublisherPtr> m_publishers;

		// machines to subscribe
		RCF::Mutex m_subscriberMutex;
		std::map<short, std::vector<ServiceHandle> > m_subhandles;

		// machine to trigger or publish
		std::map<short, std::vector<ServiceHandle> > m_pubhandles;

		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;
	};
}
#endif