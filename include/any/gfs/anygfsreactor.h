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
#ifndef __ANYRCF_META_PROGRAMMING_GFS_REACTOR_H__
#define __ANYRCF_META_PROGRAMMING_GFS_REACTOR_H__

// refer to EXPORT & IMPORT
#include "anyrcf.h"

// stl
#include "any/base/anystl.h"
#include "any/base/anymediator.h"
#include "boost/function.hpp"
using namespace AnyBase;

// traits
#include "generic programming\core\rcf_servicehandle.h"
#include "generic programming\core\gfs_metanode.h"
#include "generic programming\core\rcf_serviceimpl.h"
#include "generic programming\core\gfs_metastorage.h"
#include "generic programming\core\gfs_metarecord.h"
#include "generic programming\core\gfs_masterchunk.h"
#include "generic programming\core\gfs_masterfile.h"
#include "generic programming\core\gfs_localchunk.h"
#include "generic programming\core\gfs_chunklocation.h"
#include "generic programming\core\gfs_chunkdata.h"
#include "generic programming\core\gfs_chunksize.h"

#include "generic programming\dimension\strategy\chunk_data_read_asfile_logged.h"
#include "generic programming\dimension\strategy\chunk_data_write_asfile_logged.h"
using namespace anyway::rcf;
using namespace anyway::rcf::detail::strategy;

//
namespace AnyRCF
{
	/*!
	*
	**/
	template
	<
		typename MasterServer, 
		typename ChunkServer, 
		typename ReadStrategy = chunk_data_read_asfile_logged,
		typename WriteStrategy = chunk_data_write_asfile_logged,
		typename ProductFunction = boost::function<void(int, int, std::vector<std::vector<void*> >&, std::vector<std::vector<int> >&, bool)>,
		typename PrintFunction = boost::function<void(string)>
	>
	class ANYRCF_CLASS CAnyGfsReactor
	{
	public:
		// traits
		typedef typename rcf_servicehandle<MasterServer>::type ReactorServiceHandle;
		typedef typename rcf_serviceimpl<MasterServer>::type MasterServiceImpl;
		typedef typename rcf_serviceimpl<ChunkServer>::type ChunkServiceImpl;

		typedef typename gfs_metanode<MasterServer>::type MasterMetaNode;
		typedef typename gfs_metastorage<MasterServer>::type MasterMetaConnection;
		typedef typename gfs_metarecord<MasterServer>::type MasterMetaRecord;
		typedef typename gfs_masterfile<MasterServer>::type MasterFile;

		typedef typename gfs_masterchunk<ChunkServer>::type MasterChunkRecord;
		typedef typename gfs_localchunk<ChunkServer>::type LocalChunkFile;
		typedef typename gfs_chunklocation<ChunkServer>::type ChunkServerLocation;

		typedef typename gfs_chunkdata<ChunkServer>::type ChunkData;
		typedef typename gfs_chunksize<ChunkServer>::type ChunkSize;

		typedef std::vector<LocalChunkFile *> LocalChunkFileVector;
		typedef std::vector<ChunkServerLocation> ChunkServerLocationVector;

		typedef typename ProductFunction CreateLocalFunction;
		typedef typename PrintFunction PrintLocalFunction;
		typedef typename ReadStrategy ChunkReadStrategy;
		typedef typename WriteStrategy ChunkWriteStrategy;

		//

	private:
		/*!
		*
		**/
		struct ReadWriteThreadParameter
		{
			MasterFile const& m_file;
			std::vector<unsigned long> const& m_offsets;
			short m_ioindicator;	// 0 - read // 1 - write
			int m_from;
			int m_to;
			std::vector<ChunkData > const& m_chunks;
			std::vector<ChunkSize > const& m_sizes;

			ReadWriteThreadParameter(MasterFile const& file, std::vector<unsigned long> const& offsets, short ioindicator, std::vector<ChunkData > const& chunks, std::vector<ChunkSize > const& sizes) : \
				m_file(file), m_offsets(offsets), m_ioindicator(ioindicator), m_from(0), m_to(0), \
				m_chunks(chunks), m_sizes(sizes)
			{
			}
		};

		// function callback
		struct ProductionThreadParameter
		{
			long m_from;
			long m_to;

			std::vector<ChunkData> m_data_block; //std::vector<std::vector<void *> >m_data_block;
			std::vector<ChunkSize> m_data_block_size; //std::vector<std::vector<int> > m_data_block_size;

			CreateLocalFunction m_function;
		};

		// print function callback
		struct PrintThreadParameter
		{
			std::string m_msg;
			PrintLocalFunction m_function;
		};

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGfsReactor();
		~CAnyGfsReactor();

	public:
		//
		// configure reactor framework
		//
		void RegisterHandler(ReactorServiceHandle &handle);
		void RemoveHandler(ReactorServiceHandle &handle);

		//
		// namespace on master server
		//
		void LoadNamespace(MasterMetaConnection const& conn, std::vector<MasterMetaNode> &nodes);
		void CreateNamespaceNode(MasterMetaNode const& node);
		void AddNamespaceNode(MasterMetaNode const& node);	// commit 
		void GetNamespaceChildren(MasterMetaNode const& node, std::vector<MasterMetaRecord> &children);
		void DeleteNamespaceNode(MasterMetaNode const& node);

		//
		// gfs file open or creation
		//
		void GetLocation(MasterFile const& file, ChunkServerLocationVector &chunklocations);
		long Allocate(MasterFile &file, string const& localpath);
		long AllocateGeoLocation(MasterFile &file, string const& localpath);

		//
		bool Read(MasterFile const& file, unsigned long fileoffset);	
		bool Read(MasterFile const& file, std::vector<unsigned long> const& fileoffsets);

		//
		//bool Write(MasterFile const& file, unsigned long fileoffset);
		//bool Write(MasterFile const& file, std::vector<unsigned long> const& fileoffsets);

		// as memory
		bool Write(MasterFile const& file, ChunkData const& chunkdata, ChunkSize const& chunksize, unsigned long fileoffset);
		bool Write(MasterFile const& file, std::vector<ChunkData > const& chunkdatas, std::vector<ChunkSize > const& chunksizes, std::vector<unsigned long> const& fileoffsets);


		// in file format
		void UploadAsFile(MasterFile const& file, CreateLocalFunction productionfunc, PrintLocalFunction printfunc, int batchnumber, CAnyFunctor &progress, bool isuploadforgfs, int tilescutlimit, int starttileidx, int cuttype);
		// in memory
		void UploadAsMemory(MasterFile const& file, CreateLocalFunction productionfunc, PrintLocalFunction printfunc, int batchnumber, CAnyFunctor &progress, bool isuploadforgfs, int tilescutlimit, int starttileidx);

	public:
		//
		unsigned long FileOffset2ChunkIndex(unsigned long);
		bool IsHasThisChunk(unsigned long chunkindex, LocalChunkFile &chunk);
		bool IsExistLocalChunk(const string &localchunk);

		//
		static bool CompreChunkIndex(const LocalChunkFile *first, const LocalChunkFile *second)
		{
			return first->m_chunkindex < second->m_chunkindex;
		}

		//
		void DoReadWriteThreaded(ReadWriteThreadParameter const& parameter);	
		void DoProductChunkThread(ProductionThreadParameter const& parameter);

	public:
		// Master servant
		MasterServer *m_master;

		//gfs
		string m_gfsname; 
		std::vector<unsigned long long> m_chunkuuids;
		ChunkServerLocationVector m_chunklocations;

		// local chunk file
		LocalChunkFileVector m_locals;
		string m_gfslocalpath;
		int m_locallimits;
		int m_uploadedbatchindex;

	};


}
#endif
