#ifndef __ANYRCF_KFS_READWRITER_H__
#define __ANYRCF_KFS_READWRITER_H__

//
#include "anyrcf.h"
#include "rcfserviceimpl.h"
#include "any/base/anystl.h"

//
namespace AnyRCF
{
	class ANYRCF_CLASS CAnyKFSReadWriter
	{
	public:
		CAnyKFSReadWriter();
		~CAnyKFSReadWriter();
	public:
		static void WriteKFS(std::vector<std::vector<string> > &alluuidcodes, std::vector<std::vector<unsigned long long> > &allpartlengths, std::vector<std::vector<std::vector<char> > > &allrowkeycodes, \
			string localfiledir, std::vector<char*> &parameters, std::vector<string> &alllocalfilepaths, std::vector<unsigned long long> &alllocaluuids);
		static void WriteOneKFS(std::vector<string> &uuidcodes, std::vector<unsigned long long> &partlengths, std::vector<std::vector<char> > &rowkeycodes, \
			string localfiledir, char* &parameter, std::vector<string> &localfilepaths, std::vector<unsigned long long> &localuuids);
		static void ReadKFS(std::vector<string> &localfilepaths, std::vector<std::vector<int> > &rowkeyoffsets, \
			std::vector<int> &datatypes, std::vector<string> &datatypenames, std::vector<unsigned long long> &tracedatalengths, std::vector<unsigned char*> &tracedatas);
	};
}
#endif