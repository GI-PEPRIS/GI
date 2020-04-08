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

#ifndef ANYWAY_RCF_DIMENSION_CHUNK_DATA_READ_ASFILE_H
#define ANYWAY_RCF_DIMENSION_CHUNK_DATA_READ_ASFILE_H

#include <RCF/Win32NamedPipeEndpoint.hpp>
#include "default_strategy.h"
#include "..\..\core\tags.h"

namespace anyway
{
	namespace rcf
	{
		namespace detail
		{
			namespace strategy
			{
				struct chunk_data_read_asfile : public default_strategy
				{
					//
					//
					typedef strategy_tag_chunk_data_read_asfile type;

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
						try
						{
							//
							typedef typename rcf_serviceimpl<MasterServant>::type MasterServantImpl;
							MasterServantImpl *masterimpl = masterservant.m_servant;
							assert(masterimpl);

							typedef typename rcf_serviceimpl<ChunkServant>::type ChunkServantImpl;
							ChunkServantImpl *chunkimpl = chunkservant.m_servant;
							assert(chunkimpl);

							if(!chunkimpl->IsRunning())
							{
								masterimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
								return false;
							}

							//
							chunkimpl->m_client->getClientStub().setAutoReconnect(chunkimpl->m_handle.m_isAutoReconnect);
							chunkimpl->m_client->getClientStub().setEnableCompression(chunkimpl->m_handle.m_isCompressed);
							chunkimpl->m_client->getClientStub().getTransport().setMaxIncomingMessageLength(chunkimpl->m_handle.m_maxMessageLength);
							if(chunkimpl->m_handle.m_namedPipe.size())
							{
								TCHAR buf[256] = {0, };
								CAnyStringBasic::Get().Ascii2Wcs((char *)chunkimpl->m_handle.m_namedPipe.c_str(), buf, 256);
								chunkimpl->m_client->getClientStub().setEndpoint(RCF::Win32NamedPipeEndpoint(buf));
							}

							//
							string datadir;
							chunkimpl->GetDataDir(datadir);
							unsigned long long gfshash = MD5Hash(chunkfile.m_gfsfile);
							char buf[1024] = {};
							::sprintf(buf, "%llu", gfshash);
							string filedir = datadir + buf;//服务器端文件dir
							filedir += "\\";
							char uuidchar[64] = {};
							::sprintf(uuidchar, "%llu.afs", chunkfile.m_chunkuuid);
							string filepath = filedir + uuidchar;//服务器端文件path

							//
							RCF::FileDownload fileDownload;
							fileDownload.setDownloadToPath(chunkfile.m_localpath);
							chunkimpl->DownloadFileByPath(filepath, fileDownload);
						}
						catch(...)
						{
							return false;
						}
						return true;
					}
				};
			}
		}
	}
}


#endif