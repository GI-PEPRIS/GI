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
#ifndef __ANYRCF_SERVICE_STUB_H__
#define __ANYRCF_SERVICE_STUB_H__

//
#include "anyrcf.h"
#include "rcfclientimpl.h"
#include "eventservant.h"

//
namespace AnyRCF
{
	template<typename ServiceInterface>
	class CServiceStub : public CRCFClientImpl
	{
	public:
		typedef RcfClient<ServiceInterface> ServiceStub;
		typedef boost::shared_ptr<ServiceStub> ServiceStubPtr;

	protected:
		CServiceStub()
		{
		}
		virtual ~CServiceStub()
		{
			if(m_client)
				m_client.reset();
			m_client = 0;
		}
	public:
		/*!
		*
		**/
		void Init(const ServiceHandle &handle)
		{
			try
			{
				m_handle = handle;
				RCF::TcpEndpoint point(m_handle.m_ip,m_handle.m_port);				

				ServiceStubPtr clientPtr(new ServiceStub(point));
				m_client = clientPtr;
				m_client->getClientStub().setConnectTimeoutMs(m_handle.m_contimeout);
				m_client->getClientStub().setRemoteCallTimeoutMs(m_handle.m_calltimeout);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void GetHandle(ServiceHandle &handle)
		{
			try
			{
				m_client->GetHandle(handle);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void SetEventHandle(const ServiceHandle &handle)
		{
			try
			{
				m_client->SetEventHandle(handle);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		//
		// RPC
		//
		/*!
		*
		**/
		void Start()
		{
			try
			{
				m_client->Start();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Listen(const std::string &multicastip, int multicastport)
		{
			try
			{
				m_client->Listen(multicastip, multicastport);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Notify(short topic, const std::string &multicastip, long multicastport)
		{
			try
			{
				m_client->Notify(topic, multicastip, multicastport);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Stop()
		{
			try
			{
				m_client->Stop();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}			
		}
		void Suspend()
		{
			try
			{
				m_client->Suspend();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void Resume(bool isstopheart = false, bool isstopbroadcast = false, bool isstoprequest = false)
		{
			try
			{
				m_client->Resume(isstopheart, isstopbroadcast, isstoprequest);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		bool IsRunning()
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				int previousConnectTimeoutMs = m_client->getClientStub().getConnectTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(10000);
				m_client->getClientStub().setConnectTimeoutMs(10000);

				bool isRunning = m_client->IsRunning();

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
				m_client->getClientStub().setConnectTimeoutMs(previousTimeoutMs);
				return isRunning;
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);

				return false;
			}
		}
		string GetResponseUserData(const string &data)
		{
			try
			{
				m_client->getClientStub().setRequestUserData(data);
				m_client->SetResponseUserData();
				return m_client->getClientStub().getResponseUserData();
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);

				return "";
			}
		}

		//
		//
		//
		/*!
		*
		**/
		void RegisterChildren(int type, const ServiceHandle &handle)
		{
			try
			{
				m_client->RegisterChildren(type, handle);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void RemoveChildren(string &ip, int port)
		{
			try
			{
				m_client->RemoveChildren(ip, port);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetChildren(int type, ServiceVector &handles)
		{
			try
			{
				m_client->GetChildren(type, handles);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void BindTo(int type, string &ip, int port)
		{
			try
			{
				m_client->BindTo(type, ip, port);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void CollectHeartbeat(const ServiceHandle &handle, const MasterChunkServer &chunkstatus, const JobTaskServer &taskstatus)
		{
			try
			{
				m_client->CollectHeartbeat(handle, chunkstatus, taskstatus);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetClientName(const std::string &name)
		{
			try
			{
				m_client->SetClientName(name);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		/*!
		* local not remote call, if connection is dropped, throw an exception
		**/
		void Ping()
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(1000);

				// Ping.
				m_client->getClientStub().ping();

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void NetworkBandwidthAsSender(std::string &ip, int ports, int calls, int buflen)
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(10000000);

				m_client->NetworkBandwidthAsSender(ip, ports, calls, buflen);

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void NetworkBandwidthAsReceiver(int calls, int buflen)
		{
			try
			{
				// Set a short timeout for the ping.
				int previousTimeoutMs = m_client->getClientStub().getRemoteCallTimeoutMs();
				m_client->getClientStub().setRemoteCallTimeoutMs(10000000);

				m_client->NetworkBandwidthAsReceiver(calls, buflen);

				// Set the timeout back to what it was.
				m_client->getClientStub().setRemoteCallTimeoutMs(previousTimeoutMs);
				
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		SessionObjectVector QuerySessionObject()
		{
			try
			{
				return m_client->QuerySessionObject();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		void ClearSessionObject(const string &clientAddr)
		{
			try
			{
				m_client->ClearSessionObject(clientAddr);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		/*!
		*
		**/
		void Callback(const std::string &topic)
		{
			try
			{
				m_client->Callback(topic);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		/*!
		*
		**/
		void ConfigClientProgress()
		{
			try
			{
				RCF::ClientProgressPtr clientProgressPtr( new RCF::ClientProgress() );
				{
					clientProgressPtr->mTriggerMask = RCF::ClientProgress::Event | RCF::ClientProgress::Timer | RCF::ClientProgress::UiMessage;
					clientProgressPtr->mTimerIntervalMs = 500;
					clientProgressPtr->mUiMessageFilter = QS_PAINT;

					// vc6 hack
					clientProgressPtr->mProgressCallback = boost::bind(&CRCFClientImpl::OnClientCallback, this,_1,_2,_3,_4,_5);
					//clientProgressPtr->mProgressCallback = RCF::ClientProgress::ProgressCallback(&CRCFClientImpl::myCallback, _5);
				}
				m_client->getClientStub().setClientProgressPtr(clientProgressPtr);
			}
			catch(const RCF::Exception &e)
			{
				ToLog(e);
			}
		}

		/*!
		* On the client-side, to create a callback connection to receive calls on
		**/
		template<typename ServiceInterface, typename ServiceImpl>
		void RegisterCallback(ServiceImpl &impl)
		{
			// Client-side - create callback connection.
			m_callbackServer.bind<ServiceInterface>(impl);

			// Client-side - start a callback server.
			// Client needs a callback server, to receive calls from the server. -1 as 
			// the port number indicates that this server will not actively listen on any port. 
			m_callbackServer.addEndpoint(RCF::TcpEndpoint(m_handle.m_port));
			if(m_callbackServer.isStarted())
			{
				m_callbackServer.stop();
			}
			m_callbackServer.start();
			RCF::createCallbackConnection((*m_client), m_callbackServer);
		}
	public:
		ServiceStubPtr m_client;
	};
}
#endif