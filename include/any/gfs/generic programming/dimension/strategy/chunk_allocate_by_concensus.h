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

#ifndef ANYWAY_RCF_DIMENSION_CHUNK_ALLOCATE_BY_CONCENSUS_H
#define ANYWAY_RCF_DIMENSION_CHUNK_ALLOCATE_BY_CONCENSUS_H

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
				//
				// services
				//
				struct chunk_allocate_by_concensus : public default_strategy
				{
					//
					typedef strategy_tag_master_file_allocate_concensus type;

					//
					template
						<
						typename Servant,
						typename MasterFile
						>
						static inline std::vector<unsigned long long> apply(Servant const& servant, MasterFile &masterfile)
					{
						std::vector<unsigned long long> chunkuuids;
						try
						{
							typedef typename rcf_serviceimpl<Servant>::type ServantImpl;
							ServantImpl *impl = servant.m_servant;
							assert(impl);

							//std::vector<unsigned long long> chunkuuids;
							//if(impl->IsRunning())
							{
								chunkuuids = impl->GetChunk(masterfile.m_filename);
								if(chunkuuids.empty())
								{
									chunkuuids = impl->AllocateChunk(masterfile.m_filename, masterfile.m_blockcount);							
								}
							}					
						}
						catch(...)
						{
							return chunkuuids;
						}

						return chunkuuids;
					}
				};
			}
		}
	}
}


#endif