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

#ifndef ANYWAY_RCF_DIMENSION_SIMULATION_WORKER_UPDATE_BLOCK_BY_FILE_H
#define ANYWAY_RCF_DIMENSION_SIMULATION_WORKER_UPDATE_BLOCK_BY_FILE_H

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
				struct simulation_worker_update_block_by_file : public default_strategy
				{
					//
					template
						<
						typename Worker,
						typename Model,
						typename Block,
						typename GraphNode
						>
					static bool apply(Worker &worker, Model &model, Block &block, GraphNode *running_node)
					{
						bool isuploaded = true;
						try
						{
							typedef typename rcf_serviceimpl<Worker>::type WorkerServantImpl;
							WorkerServantImpl *workerimpl = worker.m_servant;
							assert(workerimpl);

							if(!workerimpl->IsRunning())
							{
								//masterimpl->RemoveChildren(const_cast<std::string&>(chunkservant.m_handle.m_ip), chunkservant.m_handle.m_port);
								return 0;
							}

							if(!running_node)//initialize
							{
								typedef simulation_simulator<Model>::type Simulator;
								Simulator *block_simulator = block.m_host_job_block_simulator;
								string filepath = "";
								block_simulator->get_block_simulator_data_dir(&block, filepath);
								{
									char buffer[256];
									::sprintf(buffer, "simulator_data");
									string str = buffer;
									filepath = filepath + str;
								}
								RCF::FileUpload fileUpload(filepath);
								workerimpl->UploadBlockFile(0, filepath, fileUpload);
							}
							else
							{
								typedef simulation_simulator<Model>::type Simulator;
								Simulator *model_simulator = model.m_host_model_simulator;
								Simulator *block_simulator = block.m_host_job_block_simulator;
								long whichsimulationstep;
								int pressure_LoopNumber;
								int heat_LoopNumber;
								model_simulator->DoDownloadModelData(&model, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
								block_simulator->DoDownloadBlockData(&block, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
								workerimpl->UploadBlockData(0, whichsimulationstep, pressure_LoopNumber, heat_LoopNumber);
								std::vector<string> filepaths;
								block_simulator->get_block_step_data_filepath(&block, filepaths);
								for(int i = 0; i < filepaths.size(); i++)
								{
									RCF::FileUpload fileUpload(filepaths[i]);
									workerimpl->UploadBlockStepFile(0, filepaths[i], fileUpload);
								}
								workerimpl->LoadBlockCurrentStepData(0);
							}
							//else if(running_node->m_is)
							//{

							//}

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

						return isuploaded;
					}
				};
			}
		}
	}
}


#endif