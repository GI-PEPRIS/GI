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
#ifndef __ANYRCF_GEO_LOCATION_SERVANT_H__
#define __ANYRCF_GEO_LOCATION_SERVANT_H__

//
#include "anyrcf.h"
#include "rcfserviceimpl.h"
#include "any/base/anystl.h"

//
namespace AnyRCF
{
	// interface
	RCF_BEGIN(I_AnyGeoLocation, "I_AnyGeoLocation")
		//here is soft control(rcf server start/stop) hard control is implemented in console app using psService.
		RCF_METHOD_R1(bool, Init, const ServiceHandle&)
		RCF_METHOD_V1(void, GetHandle, ServiceHandle&)
		RCF_METHOD_V1(void, SetEventHandle, const ServiceHandle&)
		RCF_METHOD_V0(void, Start)
		RCF_METHOD_V2(void, Listen, const std::string&, short)
		RCF_METHOD_V3(void, Notify, short, const std::string&, long)
		RCF_METHOD_R1(bool, Login, const LoginInfo&)
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
		RCF_METHOD_V2(void, GetChildren, int, const ServiceVector&)
		RCF_METHOD_V3(void, CollectHeartbeat, const ServiceHandle&, const MasterChunkServer&, const JobTaskServer&)

		//communicate with cms e.g. heart beats
		RCF_METHOD_V3(void, BindTo, int, string&, int)
		RCF_METHOD_V0(void, SetResponseUserData)
		RCF_METHOD_V1(void, SetClientName, const std::string&)
		RCF_METHOD_V1(void, Callback, const std::string&)
		RCF_METHOD_V1(void, OnCallback, const std::string&)	// response to callback

		//
		RCF_METHOD_V5(void, InitDB, short, const std::string&, const std::string&, const std::string&, const std::string&)
		RCF_METHOD_V0(void, LoadGeoLocationGrid)
		RCF_METHOD_V0(void, SaveGeoLocationGrid)
		RCF_METHOD_V0(void, RemoveGeoLocationGrid)
		RCF_METHOD_V2(void, UpdateGeoLocationMachine, const GeoLocationPolygon&, std::vector<unsigned long long>&)
		RCF_METHOD_V2(void, GetGeoLocationPointCode, const GeoLocationPoint&, string&)
		RCF_METHOD_V2(void, GetGeoLocationPolygonCode, const GeoLocationPolygon&, string&)
		RCF_METHOD_V5(void, GetGeoLocationCandidateMachine, std::vector<char>&, std::vector<string>&, std::vector<unsigned long long>&, std::vector<unsigned long long>&, std::vector<std::vector<char> >&)
		RCF_METHOD_V3(void, GetGeoLocationRelatedFiles, std::vector<char>&, std::vector<string>&, std::vector<std::vector<int> >&)
		RCF_METHOD_V3(void, GetGeoLocationNextDFS, const string&, short, string&)
		RCF_METHOD_V1(void, SetAllMachineLocations, std::vector<unsigned long long>&)
		RCF_METHOD_V2(void, GetGridMachineLocations, const string&, std::vector<unsigned long long>&)
		//

	RCF_END(I_AnyGeoLocation)

	/*!
	* almost the same as RCFServiceImpl
	**/
	class ANYRCF_CLASS CGeoLocationServant : public CRCFServiceImpl
	{
		// callback
		typedef RcfClient<I_AnyGeoLocation> CbClient;
		typedef boost::shared_ptr<CbClient> CbClientPtr;

		// to schedule machines into geographic extent to store
		typedef std::list<GeoLocationMachine*> MachineLocationContainer;
		typedef MachineLocationContainer::iterator machine_itr;
		typedef MachineLocationContainer::const_iterator machine_citr;

		// to decide which level and cell allocated DFS files
		typedef std::list<GeoLocationNextKey*> NextKeyContainer;
		typedef NextKeyContainer::iterator nextkey_itr;
		typedef NextKeyContainer::const_iterator nextkey_citr;

		// inverse sort table for each DFS file
		struct InverseSortUnit
		{
			string m_filename;
			std::vector<unsigned long long> m_machine_uuids;
		};
		typedef std::vector<InverseSortUnit*> InverseSortTable;
		typedef InverseSortTable::iterator inverse_itr;
		typedef InverseSortTable::const_iterator inverse_citr;

	public:
		/*!
		*
		**/
		CGeoLocationServant();
		~CGeoLocationServant();

	public:
		//
		//
		//
		void Start();
		void DoScheduleEntries(std::deque<RequestEntry *> &entries);
		
		//
		//
		//
		void Callback(const std::string &topic);
		void OnCallback(const std::string &topic);

		//
		//
		//
		void InitDB(short type, const std::string &srcname, const std::string &user, const std::string &pwd, const std::string &dbname);
		void RemoveGeoLocationGrid();
		void SaveGeoLocationGrid();
		void LoadGeoLocationGrid();
		void UpdateGeoLocationMachine(const GeoLocationPolygon &locationextent, std::vector<unsigned long long> &machinelocations);
		void GetGeoLocationPointCode(const GeoLocationPoint &pointlocation, string& locationcode);
		void GetGeoLocationPolygonCode(const GeoLocationPolygon &polylocation, string &locationcode);
		void GetGeoLocationCandidateMachine(std::vector<char> &geocode, std::vector<string> &uuidcodes, std::vector<unsigned long long> &partlengths, \
			std::vector<unsigned long long> &machinelocations, std::vector<std::vector<char> > &rowkeycodes);
		void GetGeoLocationRelatedFiles(std::vector<char> &geocode, std::vector<string> &uuidcodes, std::vector<std::vector<int> > &rowkeyoffsets);
		void GetGeoLocationNextDFS(const string &geocode, short filetype, string &dfsname);
		void SetAllMachineLocations(std::vector<unsigned long long> &allmachinelocations);
		void GetGridMachineLocations(const string &gridcode, std::vector<unsigned long long> &machinelocations);

		//
		//
		//
		void FindGridCodeForLocationCode(const string &locationcode, string &gridcode);
		void AddDataToGrid(const string &gridcode, const string &locationcode, const string &infocode, unsigned long long datalength, short filetype, string gfsname, \
			std::vector<string> &uuidcodes, std::vector<unsigned long long> &partlengths, std::vector<unsigned long long> &machinelocations, std::vector<GeoLocationRowKey> &rowkeys);
		void AddDataToNewGrid(const string &gridcode, const string &locationcode, const string &infocode, unsigned long long datalength, short filetype, string gfsname, \
			std::vector<string> &uuidcodes, std::vector<unsigned long long> &partlengths, std::vector<unsigned long long> &machinelocations, std::vector<GeoLocationRowKey> &rowkeys);
		void AddDataToExistGrid(GeoLocationGrid &grid, const string &gridcode, const string &locationcode, const string &infocode, unsigned long long datalength, short filetype, string gfsname, \
			std::vector<string> &uuidcodes, std::vector<unsigned long long> &partlengths, std::vector<unsigned long long> &machinelocations, std::vector<GeoLocationRowKey> &rowkeys);
		void SplitOneGrid(GeoLocationGrid &grid);

	private:
		//
		//
		//
		/*!
		*
		**/
		void OnCallbackConnectionCreated(RCF::RcfSessionPtr sessionPtr, RCF::ClientTransportAutoPtr clientTransportPtr);

	private:
		// callback connections
		std::map<std::string, CbClientPtr> m_cbClients;

		// master servant client or as children

		//
		MachineLocationContainer m_machines;
		NextKeyContainer m_nextkeys;
		std::vector<GeoLocationGrid> m_location_grids;
		std::vector<unsigned long long> m_allmachinelocations;
		MasterDBConnection m_srcDesc;
	};
}
#endif