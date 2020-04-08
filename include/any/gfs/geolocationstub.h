#ifndef __ANYRCF_GEO_LOCATION_STUB_H__
#define __ANYRCF_GEO_LOCATION_STUB_H__

//
#include "anyrcf.h"
#include "servicestub.h"
#include "geolocationservant.h"

//
namespace AnyRCF
{
	/*!
	*
	**/
	class ANYRCF_CLASS CGeoLocationStub : public CServiceStub<I_AnyGeoLocation>
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CGeoLocationStub();
		~CGeoLocationStub();

	public:
		//
		//
		//
		void InitDB(short type, const string &srcname, const string &user, const string &pwd, const string &dbname)
		{
			try
			{
				m_client->InitDB(type, srcname, user, pwd, dbname);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void LoadGeoLocationGrid()
		{
			try
			{
				m_client->LoadGeoLocationGrid();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void SaveGeoLocationGrid()
		{
			try
			{
				m_client->SaveGeoLocationGrid();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void RemoveGeoLocationGrid()
		{
			try
			{
				m_client->RemoveGeoLocationGrid();
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}	
		void UpdateGeoLocationMachine(const GeoLocationPolygon &locationextent, std::vector<unsigned long long> &machinelocations)
		{
			try
			{
				m_client->UpdateGeoLocationMachine(locationextent, machinelocations);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetGeoLocationPointCode(const GeoLocationPoint &pointlocation, string& geocode)
		{
			try
			{
				m_client->GetGeoLocationPointCode(pointlocation, geocode);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetGeoLocationPolygonCode(const GeoLocationPolygon &polylocation, string &geocode)
		{
			try
			{
				m_client->GetGeoLocationPolygonCode(polylocation, geocode);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetGeoLocationCandidateMachine(std::vector<char> &geocode, std::vector<string> &uuidcodes, std::vector<unsigned long long> &partlengths, std::vector<unsigned long long> &machinelocations, std::vector<std::vector<char> > &rowkeycodes)
		{
			try
			{
				m_client->GetGeoLocationCandidateMachine(geocode, uuidcodes, partlengths, machinelocations, rowkeycodes);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetGeoLocationRelatedFiles(std::vector<char> &geocode, std::vector<string> &uuidcodes, std::vector<std::vector<int> > &rowkeyoffsets)
		{
			try
			{
				m_client->GetGeoLocationRelatedFiles(geocode, uuidcodes, rowkeyoffsets);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetGeoLocationNextDFS(const string &geocode, short filetype, string &dfsname)
		{
			try
			{
				m_client->GetGeoLocationNextDFS(geocode, filetype, dfsname);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void SetAllMachineLocations(std::vector<unsigned long long> &allmachinelocations)
		{
			try
			{
				m_client->SetAllMachineLocations(allmachinelocations);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
		void GetGridMachineLocations(const string &gridcode, std::vector<unsigned long long> &machinelocations)
		{
			try
			{
				m_client->GetGridMachineLocations(gridcode, machinelocations);
			}
			catch(RCF::Exception &e)
			{
				ToLog(e);
			}
		}
	};
	template class ANYRCF_CLASS CServiceStub<I_AnyGeoLocation>;
}

#endif
