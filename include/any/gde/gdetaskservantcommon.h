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
#ifndef __ANYGDE_GFS_TASK_SERVANT_COMMON_H__
#define __ANYGDE_GFS_TASK_SERVANT_COMMON_H__

#include"anygde.h"
#include "gdetaskbasic.h"

//
#include "any/gfs/gfstaskservant.h"
using namespace AnyRCF;

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CGdeTaskServantCommon : public CGFSTaskServant
	{
	protected:
		//
		//
		//
		CGdeTaskServantCommon();
		virtual ~CGdeTaskServantCommon();

	protected:
		//
		//
		//
		void GetGxSurvey();
		bool Time2Positionz(double time, int &ZPosition);
		bool Positionz2Time(int ZPosition, double &time);
		bool PositionToPostile(CGeoPoint<int> Position, int fetchlevel, CGeoPoint<int> &postile);
		bool PostileToPosition(CGeoPoint<int> postile, int fetchlevel, CGeoPoint<int> &Position1, CGeoPoint<int> &Position2);
		bool Postile2Morton(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);
		bool Morton2Postile(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		bool Morton2Tileid(std::vector<int> morton, int &tileid);
		bool Tileid2Morton(int tileid, std::vector<int> &morton);
		void GetChunkData(unsigned long long chunkuuid, std::vector<int> &cmpcounts, long sequenceOrder, double minTime, double maxTime, std::vector<std::vector<double> > &samples, bool ispremode, void* &mapperinputfilehandle);
		void GetChunkDataMulti(unsigned long long chunkuuid, std::vector<int> &cmpcounts, long sequenceOrder, double minTime, double maxTime, std::vector<std::vector<double> > &samples, bool ispremode, std::vector<void*> &mapperinputfilehandles, std::vector<string> &gfsnames);
		void GetChunkCmpcounts( unsigned long long chunkuuid, std::vector<int> &cmpcounts );
		void GetChunkRange( unsigned long long chunkuuid, int &inlinestart, int &inlineend, int &xlinestart, int &xlineend, double &mintime, double &maxtime );
		void FromPositionToChunkuuid(long sequenceOrder, double time, unsigned long long &chunkuuid);
	protected:
		//
		JobParameter *m_parameter;

		//
		TaskSurveyInfoData m_surveyinfodata;
		std::map<unsigned long long, int> m_chunkuuid_tileid;
	};

}

#endif
