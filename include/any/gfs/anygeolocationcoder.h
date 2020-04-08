#ifndef __ANYRCF_GEO_LOCATION_CODER_H__
#define __ANYRCF_GEO_LOCATION_CODER_H__

//
#include "anyrcf.h"
#include "rcfserviceimpl.h"
#include "any/base/anystl.h"

//
namespace AnyRCF
{
	class ANYRCF_CLASS CAnyGeoLocationCoder
	{
	public:
		CAnyGeoLocationCoder();
		~CAnyGeoLocationCoder();
	public:
		static void EncodeRowKey(GeoLocationRowKey &rowkey, char *&parameter, unsigned long long &datalen);
		static void DecodeRowKey(char *&parameter, unsigned long long &datalen, GeoLocationRowKey &rowkey);
		static void EncodeLocationCode(double longitude, double latitude, string &locationcode);
		static void EncodeGeocode(const string &locationcode, const string &infocode, unsigned long long &datalength, short &filetype, const string &gfsname, std::vector<char> &geocode);
		static void DecodeGeocode(std::vector<char> &geocode, string &locationcode, string &infocode, unsigned long long &datalength, short &filetype, string &gfsname);
		static void FromGridcodeAndFileoffsetTouuidcode(const string &gridcode, int fileoffset, string &uuidcode);

		static void HexConvert(const string &sourcecode, string &targetcode, long sourcehex, long targethex);
		static void HexConvert(const string &sourcecode, unsigned long long &targetcode, long sourcehex);
		static void HexConvert(unsigned long long sourcecode, string &targetcode, long targethex);

		static bool IsInside(const string &sourcecode, const string &targetcode);
		static bool IsCover(const string &sourcecode, const string &targetcode);
		static bool IsOverlap(const string &sourcecode, const string &targetcode);
		static bool IsDisjoint(const string &sourcecode, const string &targetcode);
	};
}
#endif
