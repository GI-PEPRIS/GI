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
#ifndef __ANYGDE_MAPREDUCE_GDE_CLIENT_H__
#define __ANYGDE_MAPREDUCE_GDE_CLIENT_H__

//
#include "anygde.h"
#include "gdetaskbasic.h"
#include "any/gfs/anyjobtaskrunner.h"
using namespace AnyRCF;

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CAnyGdeJobClient : public CAnyJobTaskRunner
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGdeJobClient();
		~CAnyGdeJobClient()
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
		void Run(GdeJobParameter &parameter, bool issequential = true);
		void Finalize();

		void GetReduceResult(std::vector<GdeMapPair> &pairs);
		void GetOneReduceResultPair(int whichreducer, int pairoffset, GdeMapPair &pair, std::vector<unsigned long long> &pairsoffsets);
		void GetReduceResult_DownloadMode(string gfslocalpath, std::vector<GdeMapPair> &pairs);

		void SetMapTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
		void GetMapTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
		void SetReduceTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
		void GetReduceTaskStatus(std::string& gfsname, int offset, JobTaskStatus& taskstatus);
	};
}
#endif
