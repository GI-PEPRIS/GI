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

#ifndef ANYWAY_RCF_DIMENSION_CHUNK_DATA_READ_ASFILE_LOGGED_H
#define ANYWAY_RCF_DIMENSION_CHUNK_DATA_READ_ASFILE_LOGGED_H

//
#include "any/base/anydirbasic.h"
#include "any/base/anystringbasic.h"
#include "any/base/anytimebasic.h"
using namespace AnyBase;

#include "chunk_data_read_asfile.h"

namespace anyway
{
	namespace rcf
	{
		namespace detail
		{
			namespace strategy
			{
				struct chunk_data_read_asfile_logged : public chunk_data_read_asfile
				{
					//
					//
					typedef strategy_tag_chunk_data_read_asfile_logged type;

					//
					template
					<
						typename MasterServant,
						typename ChunkServant,
						typename ChunkFile
					>
					static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile)
					{
						//
						typedef typename rcf_serviceimpl<MasterServant>::type MasterServantImpl;
						MasterServantImpl *masterimpl = masterservant.m_servant;
						assert(masterimpl);
						
						typedef typename rcf_serviceimpl<ChunkServant>::type ChunkServantImpl;
						ChunkServantImpl *chunkimpl = chunkservant.m_servant;
						assert(chunkimpl);

						//
						CAnyTimeBasic::TimeReport report;
						CAnyTimeBasic timeBasic;
						timeBasic.GetNow(report);
						double fromtime = report.m_year * 10000000000 + report.m_month * 100000000 + report.m_day * 1000000 + report.m_hour * 10000 + report.m_minute * 100 + report.m_second;

						//
						bool rt = chunk_data_read_asfile::apply(masterservant, chunkservant, chunkfile);

						//
						// to wait until current file on local path
						timeBasic.GetNow(report);
						double endtime = report.m_year * 10000000000 + report.m_month * 100000000 + report.m_day * 1000000 + report.m_hour * 10000 + report.m_minute * 100 + report.m_second;
						double elapsedtime = GFSUploadStatus::CalculateTimeRange(fromtime, endtime);
						{
							GFSDownloadStatus downloadstatus;
							masterimpl->GetDownloadStatus(chunkfile.m_gfsfile, downloadstatus);
							downloadstatus.m_chunkdownfinishednumber++;
							if(ISNAN(downloadstatus.m_chunkmindownloadtime) || downloadstatus.m_chunkmindownloadtime > elapsedtime)
							{
								downloadstatus.m_chunkmindownloadtime = elapsedtime;
								downloadstatus.m_chunkmindownloadip = chunkservant.m_handle.m_ip;
							}
							if(ISNAN(downloadstatus.m_chunkmaxdownloadtime) || downloadstatus.m_chunkmaxdownloadtime < elapsedtime)
							{
								downloadstatus.m_chunkmaxdownloadtime = elapsedtime;
								downloadstatus.m_chunkmaxdownloadip = chunkservant.m_handle.m_ip;
							}
							if(elapsedtime > 0)
							{
								long long filelength = 0;
								{
									TCHAR wbuf[1024] = {0, };
									CAnyStringBasic::Get().Ascii2Wcs((char *)chunkfile.m_localfile.c_str(), wbuf, 1024);
									wstring wchunkfile = wbuf;
									if(CAnyDirBasic::Get().IsFileExist(wchunkfile))
									{
										const CAnyFileBasic &fileBasic = CAnyFileBasic::Get();
										void *fileHandle = fileBasic.OpenFile(wchunkfile, CAnyFileBasic::ANY_FILE_READ);
										fileBasic.SeekFile(fileHandle, 0, CAnyFileBasic::ANY_SEEK_END);
										filelength = fileBasic.TellFilePos(fileHandle);
										fileBasic.CloseFile(fileHandle);
									}
								}

								double bandwidth = filelength / elapsedtime / 1024;
								if(ISNAN(downloadstatus.m_chunkminbandwidth) || downloadstatus.m_chunkminbandwidth > bandwidth)
								{
									downloadstatus.m_chunkminbandwidth = bandwidth;
									downloadstatus.m_chunkminbandip = chunkservant.m_handle.m_ip;
								}
								if(ISNAN(downloadstatus.m_chunkmaxbandwidth) || downloadstatus.m_chunkmaxbandwidth < bandwidth)
								{
									downloadstatus.m_chunkmaxbandwidth = bandwidth;
									downloadstatus.m_chunkmaxbandip = chunkservant.m_handle.m_ip;
								}
							}
							masterimpl->SetDownloadStatus(chunkfile.m_gfsfile, downloadstatus);
						}

						//
						return rt;
					}
				};
			}
		}
	}
}


#endif