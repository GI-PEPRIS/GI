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

#ifndef ANYWAY_RCF_DIMENSION_SIMULATION_MASTER_DOWNLOAD_MODEL_BY_FILE_H
#define ANYWAY_RCF_DIMENSION_SIMULATION_MASTER_DOWNLOAD_MODEL_BY_FILE_H

#include <RCF/Win32NamedPipeEndpoint.hpp>
#include "default_strategy.h"
#include "../../core/tags.h"

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
				struct simulation_master_download_model_by_file : public default_strategy
				{
					//
					template
						<
						typename Master,
						typename Model,
						typename GraphNode
						>
					static bool apply(Master &master, Model &model, GraphNode *running_node)
					{
						bool isdownloaded = true;
						try
						{
							typedef typename rcf_serviceimpl<Master>::type MasterServantImpl;
							MasterServantImpl *masterimpl = master.m_servant;
							assert(masterimpl);

							if(!masterimpl->IsRunning())
							{
								//masterimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
								return 0;
							}
							{
								typedef simulation_simulator<Model>::type Simulator;
								Simulator *model_simulator = model.m_host_model_simulator;
								masterimpl->SaveModelCurrentStepData(0);
								long whichsimulationstep;
								int pressure_LoopNumber;
								int heat_LoopNumber;
								masterimpl->DownloadModelData(0, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
								model_simulator->DoUploadModelData(&model, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
								std::vector<string> filepaths;
								model_simulator->get_model_step_data_filepath(&model, filepaths);
								for(int i = 0; i < filepaths.size(); i++)
								{
									masterimpl->m_client->getClientStub().setAutoReconnect(masterimpl->m_handle.m_isAutoReconnect);
									masterimpl->m_client->getClientStub().setEnableCompression(masterimpl->m_handle.m_isCompressed);
									masterimpl->m_client->getClientStub().getTransport().setMaxIncomingMessageLength(masterimpl->m_handle.m_maxMessageLength);
									if(masterimpl->m_handle.m_namedPipe.size())
									{
										TCHAR buf[256] = {0, };
										CAnyStringBasic::Get().Ascii2Wcs((char *)masterimpl->m_handle.m_namedPipe.c_str(), buf, 256);
										masterimpl->m_client->getClientStub().setEndpoint(RCF::Win32NamedPipeEndpoint(buf));
									}
									string filepath = filepaths[i];
									long long filelength = 0;
									masterimpl->DownloadModelFile_getfilelen(0, filepath, filelength);
									if(filelength > 0)
									{
										void* fileHandle = NULL;
										std::vector<char> data;data.resize(512 * 1024);
										for(long long i = 0; i < filelength; i = i + 512 * 1024)
										{
											int readlength = i + 512 * 1024 > filelength ? filelength - i : 512 * 1024;
											masterimpl->DownloadModelFile_readmode(0, filepath, data, readlength, i);
											int datalength = readlength;
											long long offset = i;
											int filehandletype = (i == 0 ? CAnyFileBasic::ANY_FILE_WRITE : CAnyFileBasic::ANY_FILE_ALL);
											{
												const CAnyFileBasic &fileBasic = CAnyFileBasic::Get();
												if(!fileHandle)
												{
													string filepathpartA = "";
													string filepathpartB = filepath;
													while(true)
													{
														string subpath = filepathpartB.substr(0, filepathpartB.find_first_of("\\") + 1);
														if(subpath == "")
															break;
														filepathpartA += subpath;
														filepathpartB = filepathpartB.substr(filepathpartB.find_first_of("\\") + 1, filepathpartB.length());
														TCHAR wbuf[1024] = {0, };
														CAnyStringBasic::Get().Ascii2Wcs((char *)filepathpartA.c_str(), wbuf, 1024);
														wstring wsubdir = wbuf;
														if(!CAnyDirBasic::Get().IsDirExist(wsubdir))
															CAnyDirBasic::Get().CreateDir(wsubdir);
													}
													TCHAR wbuf[1024] = {0, };
													CAnyStringBasic::Get().Ascii2Wcs((char *)filepath.c_str(), wbuf, 1024);
													wstring wchunkfile = wbuf;
													fileHandle = fileBasic.OpenFile(wchunkfile, filehandletype);
													fileBasic.SeekFile(fileHandle, offset, CAnyFileBasic::ANY_SEEK_BEGIN);
												}
												char *datachar = data.data();
												fileBasic.WriteFile(fileHandle, (void*)datachar, datalength, 1);
											}
										}
										if(fileHandle)
										{
											const CAnyFileBasic &fileBasic = CAnyFileBasic::Get();
											fileBasic.FlushFile(fileHandle);
											fileBasic.CloseFile(fileHandle);
										}
									}
									//RCF::FileDownload fileDownload;
									//fileDownload.setDownloadToPath(filepaths[i].substr(0, filepaths[i].find_last_of("\\")));
									//masterimpl->DownloadModelFile(0, filepaths[i], fileDownload); 
								}
							}
							//
						//	masterimpl->m_client->getClientStub().setAutoReconnect(chunkimpl->m_handle.m_isAutoReconnect);
						//	masterimpl->m_client->getClientStub().setEnableCompression(chunkimpl->m_handle.m_isCompressed);
						//	masterimpl->m_client->getClientStub().getTransport().setMaxIncomingMessageLength(chunkimpl->m_handle.m_maxMessageLength);
						//	if(masterimpl->m_handle.m_namedPipe.size())
						//	{
						//		TCHAR buf[256] = {0, };
						//		CAnyStringBasic::Get().Ascii2Wcs((char *)chunkimpl->m_handle.m_namedPipe.c_str(), buf, 256);
						//		masterimpl->m_client->getClientStub().setEndpoint(RCF::Win32NamedPipeEndpoint(buf));
						//	}

						////
						//string datadir;
						//masterimpl->GetDataDir(datadir);
						//unsigned long long gfshash = MD5Hash(model.m_gfsfile);
						//char buf[1024] = {};
						//::sprintf(buf, "%llu", gfshash);
						//string uploadfilepath = datadir + buf;
						//uploadfilepath += "\\";
						//char uuidchar[64] = {};
						//::sprintf(uuidchar, "%llu.afs", chunkfile.m_chunkuuid);
						//uploadfilepath += uuidchar;

						// assure whether normally passed
	/*					{
							TCHAR wbuf[1024] = {0, };
							CAnyStringBasic::Get().Ascii2Wcs((char *)chunkfile.m_localfile.c_str(), wbuf, 1024);
							wstring wchunkfile = wbuf;
							if(CAnyDirBasic::Get().IsFileExist(wchunkfile))
							{
								RCF::FileUpload fileUpload(chunkfile.m_localfile);
								masterimpl->UploadModelFile(uploadfilepath, fileUpload);

							}
						}*/

						}
						catch (...)
						{
						}

						return isdownloaded;
					}
				};
			}
		}
	}
}


#endif