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

#ifndef ANYWAY_RCF_DIMENSION_CHUNK_DATA_WRITE_ASFILE_H
#define ANYWAY_RCF_DIMENSION_CHUNK_DATA_WRITE_ASFILE_H

#include <RCF/Win32NamedPipeEndpoint.hpp>

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
				struct chunk_data_write_asfile : public default_strategy
				{
					//
					//
					typedef strategy_tag_chunk_data_write_asfile type;

					//
					template
					<
						typename MasterServant,
						typename ChunkServant,
						typename ChunkFile,
						typename ChunkData,
						typename ChunkSize
					>
					static inline bool apply(MasterServant const& masterservant, ChunkServant const& chunkservant, ChunkFile const& chunkfile,ChunkData const& chunkdata, ChunkSize const& chunksize)
					{
						bool isuploaded = true;
						try
						{
							//
							typedef typename rcf_serviceimpl<MasterServant>::type MasterServantImpl;
							MasterServantImpl *masterimpl = masterservant.m_servant;
							assert(masterimpl);

							//
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
							string uploadfilepath = datadir + buf;
							uploadfilepath += "\\";
							char uuidchar[64] = {};
							::sprintf(uuidchar, "%llu.afs", chunkfile.m_chunkuuid);
							uploadfilepath += uuidchar;

							// assure whether normally passed
							{
								TCHAR wbuf[1024] = {0, };
								CAnyStringBasic::Get().Ascii2Wcs((char *)chunkfile.m_localfile.c_str(), wbuf, 1024);
								wstring wchunkfile = wbuf;
								if(CAnyDirBasic::Get().IsFileExist(wchunkfile))
								{
									RCF::FileUpload fileUpload(chunkfile.m_localfile);
									chunkimpl->UploadFileByPath(uploadfilepath, fileUpload);
									/*long long filelength = 0;
									chunkimpl->GetFileLength(uploadfilepath, filelength);
									int count = 0;

									while(filelength == 0)
									{
										Sleep(chunkfile.m_failure_try_seconds);
										chunkimpl->GetFileLength(uploadfilepath, filelength);
										count++;
										if(count > chunkfile.m_failure_tries)
										{
											isuploaded = false;
											break;
										}
									}*/
								}
							}
						}
						catch(...)
						{
							return false;
						}

						return isuploaded;
					}
				};
			}
		}
	}
}


#endif