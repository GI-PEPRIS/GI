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

#ifndef ANYWAY_RCF_DIMENSION_CHUNK_DATA_WRITE_ASFILE_LOGGED_H
#define ANYWAY_RCF_DIMENSION_CHUNK_DATA_WRITE_ASFILE_LOGGED_H

#include "chunk_data_write_asfile.h"

namespace anyway
{
	namespace rcf
	{
		namespace detail
		{
			namespace strategy
			{
				//
				// services
				//
				struct chunk_data_write_asfile_logged : public chunk_data_write_asfile
				{
					//
					//
					typedef strategy_tag_chunk_data_write_asfile_logged type;

					//
					template
					<
						typename MasterServant,
						typename ChunkServant,
						typename ChunkFile,
						typename ChunkData,
						typename ChunkSize
					>
					static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile, ChunkData const& chunkdata, ChunkSize const& chunksize)
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
						bool rt = chunk_data_write_asfile::apply(masterservant, chunkservant, chunkfile,chunkdata, chunksize);

						timeBasic.GetNow(report);
						double endtime = report.m_year * 10000000000 + report.m_month * 100000000 + report.m_day * 1000000 + report.m_hour * 10000 + report.m_minute * 100 + report.m_second;
						double elapsedtime = GFSUploadStatus::CalculateTimeRange(fromtime, endtime);
						{
							GFSUploadStatus uploadstatus;
							GFSChunkStatus chunkstatus;
							masterimpl->GetUploadStatus(chunkfile.m_gfsfile, uploadstatus);
							uploadstatus.m_chunkuploadednumber++;
							masterimpl->GetChunkStatus(chunkfile.m_gfsfile,chunkservant.m_handle.m_ip, chunkservant.m_handle.m_port, chunkstatus);
							chunkstatus.m_uploadedtilenumber++;
							if(ISNAN(uploadstatus.m_chunkminuploadtime) || uploadstatus.m_chunkminuploadtime > elapsedtime)
							{
								uploadstatus.m_chunkminuploadtime = elapsedtime;
								uploadstatus.m_chunkminuploadip = chunkservant.m_handle.m_ip;
							}
							if(ISNAN(uploadstatus.m_chunkmaxuploadtime) || uploadstatus.m_chunkmaxuploadtime < elapsedtime)
							{
								uploadstatus.m_chunkmaxuploadtime = elapsedtime;
								uploadstatus.m_chunkmaxuploadip = chunkservant.m_handle.m_ip;
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
								if(ISNAN(uploadstatus.m_chunkminbandwidth) || uploadstatus.m_chunkminbandwidth > bandwidth)
								{
									uploadstatus.m_chunkminbandwidth = bandwidth;
									uploadstatus.m_chunkminbandip = chunkservant.m_handle.m_ip;
								}
								if(ISNAN(uploadstatus.m_chunkmaxbandwidth) || uploadstatus.m_chunkmaxbandwidth < bandwidth)
								{
									uploadstatus.m_chunkmaxbandwidth = bandwidth;
									uploadstatus.m_chunkmaxbandip = chunkservant.m_handle.m_ip;
								}
								chunkstatus.m_gfschunkbandwidth = bandwidth;
								chunkstatus.m_uploadedtilesize = chunkstatus.m_uploadedtilesize + filelength;
							}
							masterimpl->SetUploadStatus(chunkfile.m_gfsfile, uploadstatus);
							masterimpl->SetChunkStatus(chunkfile.m_gfsfile, chunkservant.m_handle.m_ip, chunkservant.m_handle.m_port, chunkstatus);
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