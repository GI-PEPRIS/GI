/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYSDE_MAPREDUCE_GDE_CLIENT_H__
#define __ANYSDE_MAPREDUCE_GDE_CLIENT_H__

//
#include "anysde.h"
#include "sdetaskbasic.h"
#include "any/gfs/anyjobtaskrunner.h"
using namespace AnyRCF;

//
namespace AnySDE
{
	/*!
	*
	**/
	class ANYSDE_CLASS CAnySdeJobClient : public CAnyJobTaskRunner
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnySdeJobClient();
		~CAnySdeJobClient()
		{
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		bool Initialize(JobSpecification &specification, const ServiceHandle &masterhandle, const ServiceHandle &jobhandle, const ServiceHandle &eventhandle);
		void Run(SdeJobParameter &parameter, bool issequential = true);
		void Finalize();

		void GetReduceResult(std::vector<SdeMapPair> &pairs);
		void GetOneReduceResultPair(int whichreducer, int pairoffset, SdeMapPair &pair, std::vector<unsigned long long> &pairsoffsets);
		void GetReduceResult_DownloadMode(string gfslocalpath, std::vector<SdeMapPair> &pairs);

		void SetMapTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
		void GetMapTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
		void SetReduceTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
		void GetReduceTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
	};
}
#endif
