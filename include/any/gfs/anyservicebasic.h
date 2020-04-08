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
#ifndef __ANYRCF_SERVICE_BASIC_H__
#define __ANYRCF_SERVICE_BASIC_H__

//
#include "any/base/anystl.h"
#include "any/base/anyport.h"
#include "any/base/anygeom.h"
using namespace AnyBase;
#include "any/db/anyaccessorbasic.h"
using namespace AnyDB;

//
#include <SF/vector.hpp>
#include <SF/string.hpp>
#include <SF/SerializeParent.hpp>

#include "boost\circular_buffer.hpp"


namespace AnyRCF
{
	/*!
	* in circular way using four bytes: the last  byte means current state, previous is previous state
	*/
	enum ServiceState
	{
		IDLE				=	 1,
		RUNNING		=   1 << 1,
		SUSPEND		=   1 << 2,
		TERMINATE	=   1 << 3,
	};

	/*!
	*
	**/
	enum ServiceType
	{
		ST_Unknown							= 0,
		ST_CMS								= 1,
		ST_Event							= 1 << 1,
		ST_GFS_Master						= 1 << 2,
		ST_GFS_Chunk						= 1 << 3,
		ST_GFS_Job							= 1 << 4,
		ST_GFS_Task							= 1 << 5,
		ST_GFS_Mapper						= 1 << 6,
		ST_GFS_Reducer						= 1 << 7,
		ST_Geo_Location						= 1 << 8,
		ST_Simulation_Master				= 1 << 9,
		ST_Simulation_Worker				= 1 << 10,
		ST_Max
	};

	/*!
	*
	**/
	enum ServiceRoleType
	{
		SRT_Unknown							= 1 << 12,
		SRT_Slice,
		SRT_TriangleFilter,
		SRT_InstantAttribute,
		SRT_DipAzimuth,
		SRT_AlphaFilter,
		SRT_Irregular,
		SRT_Ellipse,
		SRT_ThreeBayes,
		SRT_BasicTrack,
		SRT_RockPhysics,
		SRT_Brick,
		SRT_Conherency,
		SRT_Raster,
		SRT_Basin_Simulation,
		SRT_Reservoir_Simulation,
		SRT_Max
	};

	/*!
	*
	**/
	enum ServiceTransportType
	{
		STT_Unknown = -1,
		STT_TCP,
		STT_UDP,
		STT_NamedPipe,
		STT_Boost_Asio,
		STT_Max
	};

	/*!
	*
	**/
	enum FileContentType
	{
		FCT_Unknown = -1,
		FCT_Dir,
		FCT_Seismic,
		FCT_Log,
		FCT_Seismic_Slice,
		FCT_Seismic_TriangleFilter,
		FCT_Seismic_InstantAttribute,
		FCT_Seismic_DipAzimuth,
		FCT_Seismic_AlphaFilter,
		FCT_Seismic_Irregular,
		FCT_Seismic_Ellipse,
		FCT_Seismic_ThreeBayes,
		FCT_Seismic_BasicTrack,
		FCT_Seismic_RockPhysics,
		FCT_Seismic_Brick,
		FCT_Seismic_Conherency,
		FCT_Seismic_Curvature,
		FCT_Seismic_Cag,
		FCT_Seismic_Window,
		FCT_Seismic_MarchingCube,
		FCT_SDE,
		FCT_SDE_MarchingCube,
		FCT_GDX,
		FCT_Max
	};

	/*!
	*
	**/
	enum MessageTopic
	{
		MT_Unknown = -1,
		MT_Register_Event,
		MT_Heartbeat_Missing,
		MT_Metadata_Update,
		MT_Mapper_Done,
		MT_Mapper_All_Done,
		MT_Reducer_Done,
		MT_Reducer_All_Done,
		MT_Max,
	};
	static char gMessageTopic[MT_Max][127] = { \
		"Register Event Service",
		"Missing Heartbeat",							
		"Update Metadata",
		"Mapper Done",
		"Mapper All Done",
		"Reducer Done",
		"Reducer All Done",
	};

	/*!
	* service metadata, and dont delcare as refaction mechasnism for remote call unknown reason
	**/
	struct ServiceAdvancedSetting
	{
		string m_namedPipe;
		bool m_isAutoReconnect;
		long m_maxMessageLength;
		bool m_isCompressed;
		long m_connectionLimits;

		long m_uploadbandwidth;
		long m_downbandwidth;

		bool m_islogging;
		short m_loglevel;	// 1,2,3,4
		string m_logfile;
		
		bool m_issamelocation;

		/*!
		*
		**/
		ServiceAdvancedSetting() : m_namedPipe(""), m_isAutoReconnect(true), m_maxMessageLength(128*1024*1024/*PENG*/), m_isCompressed(false), m_connectionLimits(100), \
			m_uploadbandwidth(0), m_downbandwidth(0), m_islogging(false), m_loglevel(3), m_logfile(""), m_issamelocation(true)
		{
		}
		ServiceAdvancedSetting(const ServiceAdvancedSetting &other)
		{
			*this = other;
		}
		const ServiceAdvancedSetting &operator=(const ServiceAdvancedSetting &other)
		{
			if(this != &other)
			{
				m_namedPipe=other.m_namedPipe;
				m_isAutoReconnect = other.m_isAutoReconnect;
				m_maxMessageLength = other.m_maxMessageLength;
				m_isCompressed = other.m_isCompressed;
				m_connectionLimits = other.m_connectionLimits;
				m_uploadbandwidth = other.m_uploadbandwidth;
				m_downbandwidth = other.m_downbandwidth;
				m_islogging = other.m_islogging;
				m_loglevel = other.m_loglevel;
				m_logfile = other.m_logfile;
				m_issamelocation = other.m_issamelocation;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_namedPipe & m_isAutoReconnect & m_maxMessageLength & m_isCompressed & m_connectionLimits & m_uploadbandwidth & m_downbandwidth & \
				m_islogging & m_loglevel & m_logfile & m_issamelocation;
		}
	};
	struct ServiceHandle : public ServiceAdvancedSetting
	{
		// basic
		string m_name;
		int m_servicetype;
		int m_service_role_type;
		unsigned char m_transporttype;
		long m_rackid;
		string m_ip;
		int m_port;

		// running status
		unsigned int m_state;						// idle, in-progress, compeleted
		unsigned int m_prevstate;				// previous state
		string m_datadir;								// data directory for current service
		double m_oldtimestamp;					// whether both are different means alive
		double m_newtimestamp;

		// broadcast
		string m_multicastip;							// multicast or broadcast
		long m_multicastport;

		//listen
		string m_listenip;                      //listen on ip and port
		long m_listenport;
	
		// configuration
		bool m_isstoprequest;
		bool m_isstopbroadcast;
		short  m_poolthreads;						// thread number for concurrent response
		short m_entrythreads;						// thread number for request or entry schedule

		int m_contimeout;								// seconds timeout when establishing network connection.
		int m_calltimeout;								// seconds timeout when waiting for remote call response from the server
		int m_lasthearttime;
		int m_hearttimeout;							// sleep seconds in theart thread func
		int m_broadcasttimeout;					// sleep seconds in broadcast thread func

		ServiceHandle() : m_name(""), m_servicetype(ST_Unknown), m_service_role_type(SRT_Unknown), m_transporttype(STT_Unknown), m_rackid(0), m_ip("127.0.0.1"), m_port(0), \
			m_state(IDLE), m_prevstate(IDLE), m_datadir(""), m_oldtimestamp(0), m_newtimestamp(0), \
			m_multicastip("255.255.255.255"), m_multicastport(0), \
			m_listenip("255.255.255.255"), m_listenport(0), \
			m_isstoprequest(true), m_isstopbroadcast(true), \
			m_poolthreads(4), m_entrythreads(2), m_contimeout(36000*1000), m_calltimeout(36000*1000), m_lasthearttime(0), m_hearttimeout(10*1000), m_broadcasttimeout(10*1000)
		{
		}
		void serialize(SF::Archive &ar)
		{
			serializeParent( (ServiceAdvancedSetting*) 0, ar, *this);
			ar & m_name & m_servicetype & m_service_role_type & m_transporttype & m_rackid & m_ip & m_port &  \
			m_state & m_prevstate & m_datadir & m_oldtimestamp & m_newtimestamp & \
			m_multicastip & m_multicastport & \
			m_listenip & m_listenport & \
			m_isstoprequest & m_isstopbroadcast & \
			m_poolthreads & m_entrythreads & m_contimeout & m_calltimeout & m_lasthearttime & m_hearttimeout & m_broadcasttimeout;
		}

		ServiceHandle(const ServiceHandle &other)
		{
			*this = other;
		}
		const ServiceHandle &operator=(const ServiceHandle &other)
		{
			if(this == &other)
			{
				return *this;
			}
			*((ServiceAdvancedSetting*)this) = *((ServiceAdvancedSetting*)&other);

			// basic
			m_name = other.m_name;
			m_servicetype = other.m_servicetype;
			m_service_role_type = other.m_service_role_type;
			m_transporttype = other.m_transporttype;
			m_rackid = other.m_rackid;
			m_ip = other.m_ip;
			m_port = other.m_port;

			// running status
			m_state = other.m_state;
			m_prevstate = other.m_prevstate;
			m_datadir = other.m_datadir;	
			m_oldtimestamp = other.m_oldtimestamp;	
			m_newtimestamp = other.m_newtimestamp;

			// broadcast & listen
			m_multicastip = other.m_multicastip;
			m_multicastport = other.m_multicastport;
			m_listenip = other.m_listenip;
			m_listenport = other.m_listenport;
	
			// configuration
			m_isstoprequest = other.m_isstoprequest;
			m_isstopbroadcast = other.m_isstopbroadcast;
			m_poolthreads = other.m_poolthreads;	
			m_entrythreads = other.m_entrythreads;	
			m_contimeout = other.m_contimeout;	
			m_calltimeout = other.m_calltimeout;	
			m_lasthearttime = other.m_lasthearttime;
			m_hearttimeout = other.m_hearttimeout;		
			m_broadcasttimeout = other.m_broadcasttimeout;	

			return *this;
		}
		bool operator==(const ServiceHandle &other)
		{
			return m_rackid == other.m_rackid && m_ip == other.m_ip && m_port == other.m_port;
		}
		bool operator!=(const ServiceHandle &other)
		{
			return m_rackid != other.m_rackid || m_ip!=other.m_ip || m_port != other.m_port;
		}
		bool IsValid()
		{
			return m_ip.size() && m_port && m_servicetype != ST_Unknown;
		}
		bool IsBasicParameterChanged(const ServiceHandle &other)
		{
			return m_servicetype != other.m_servicetype || \
				m_transporttype != other.m_transporttype || \
		        m_ip != other.m_ip || \
				m_port != other.m_port || \
				m_poolthreads != other.m_poolthreads || \
				m_entrythreads != other.m_entrythreads || \
				m_contimeout != other.m_contimeout || \
				m_calltimeout != other.m_calltimeout;	
		}
		bool IsThreadParameterChanged(const ServiceHandle &other)
		{
			return m_isstopbroadcast !=  other.m_isstopbroadcast || \
				m_isstoprequest != other.m_isstoprequest; 
		}
	};

	// service type and corresponding services
	typedef std::vector<ServiceHandle> ServiceVector;
	typedef std::map<int, ServiceVector > ServiceGroup;

	/*!
	*
	**/
	struct MasterDBConnection : public DBSourceDesc
	{
		/*!
		*
		**/
		MasterDBConnection()
		{
		}
		MasterDBConnection(const MasterDBConnection &other)
		{
			*this = other;
		}
		const MasterDBConnection &operator=(const MasterDBConnection &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_type = other.m_type;
			m_srcName = other.m_srcName;
			m_user = other.m_user;
			m_pwd = other.m_pwd;
			m_dbName = other.m_dbName;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_type & m_srcName & m_user & m_pwd & m_dbName;
		}
		bool operator==(const MasterDBConnection &other)
		{
			return m_type == other.m_type && \
				m_srcName == other.m_srcName && \
				m_user == other.m_user && \
				m_pwd == other.m_pwd && \
				m_dbName == other.m_dbName;
		}
	};

	/*!
	*
	**/
	struct MasterNamespace
	{
		// namespace 1:N
		long m_diridx;										// name or directory idx, maybe survey idx
		long m_parentidx;									//
		string m_name;										// dir or file name
		string m_path;										// the full path 
		long m_type;										// file type

		/*!
		*
		**/
		MasterNamespace() : m_diridx(0), m_parentidx(0), m_name(""), m_path(""), m_type(FCT_Unknown)
		{
		}
		MasterNamespace(const MasterNamespace &other)
		{
			*this = other;
		}
		const MasterNamespace &operator=(const MasterNamespace &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_diridx = other.m_diridx;
			m_parentidx = other.m_parentidx;
			m_name = other.m_name;
			m_path = other.m_path;
			m_type = other.m_type;

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_diridx & m_parentidx & m_name & m_path & m_type;
		}
		bool operator==(const MasterNamespace &other)
		{
			return m_diridx == other.m_diridx;
		}
	};
	typedef std::vector<MasterNamespace> MasterNamespaceVector;

	/*!
	* server not chunk data
	**/
	struct MasterChunkServer
	{
		// chunk
		long m_rackid;								// belong to which rack
		string m_ip;									// hash(name or imageidx)
		long m_port;
		unsigned long long m_chunklocation;			// hash(rack, ip, port)
		unsigned char m_status;				// idle,in-progress,completed
		bool m_isprimary;							// is getting lease
		short m_connections;					// for load balancing
		short m_diskbandwidth;				// for load balancing
		short m_netbandwidth;					// for load balancing
		unsigned long m_quota;						// disk space

		/*!
		*
		**/
		MasterChunkServer() :m_rackid(0), m_ip(""), m_port(0), m_chunklocation(0), \
			m_status(IDLE), m_isprimary(false), \
			m_connections(0), m_diskbandwidth(0), m_netbandwidth(0), m_quota(0)
		{
		}
		MasterChunkServer(const MasterChunkServer &other)
		{
			*this = other;
		}
		const MasterChunkServer &operator=(const MasterChunkServer &other)
		{
			if(this != &other)
			{
				m_rackid = other.m_rackid;
				m_ip = other.m_ip;
				m_port= other.m_port;
				m_chunklocation = other.m_chunklocation;
				m_status = other.m_status;
				m_isprimary = other.m_isprimary;
				m_connections = other.m_isprimary;
				m_diskbandwidth = other.m_diskbandwidth;
				m_netbandwidth = other.m_netbandwidth;
				m_quota = other.m_quota;
			}

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_rackid & m_ip & m_port & m_chunklocation & \
				m_status & m_isprimary & \
				m_connections & m_diskbandwidth & m_netbandwidth & m_quota;
		}
		bool operator==(const MasterChunkServer &other)
		{
			return m_rackid == other.m_rackid && m_ip == other.m_ip && m_port == other.m_port;
		}
	};
	typedef std::vector<MasterChunkServer> MasterChunkServerVector;

	/*!
	*
	**/
	struct MasterFile
	{
		// file 
		string m_filename;												// if it is a file, m_filename == m_name in MasterNamespace
		unsigned long m_filehandle;										// as image idx, HASH(dir+m_name), the list of blocks belonging to each file, or can also as octree root node?
		unsigned long m_fromhandle;										// relation
		unsigned char m_replicas;										// desired replicas
		int m_blockcount;												// chunk number
		std::vector<std::vector<char> > m_geocodes;						// chunk geo codes
		std::vector<std::vector<string> > m_uuidcodes;					// return value
		std::vector<std::vector<unsigned long long> > m_partlengths;	// return value
		std::vector<std::vector<std::vector<char> > > m_rowkeycodes;	// return value
		bool m_isfirst;													// append mode
		unsigned char m_datatype;										// SEGY, LOG, etc
		double m_mtimestamp;											// modification time
		double m_ctimestamp;											// creation time
		double m_atimestamp;											// attribute change time

		/*!
		*
		**/
		MasterFile() : m_filename(""), m_filehandle(0), m_fromhandle(0), \
			m_replicas(1), m_blockcount(0), m_datatype(FCT_Dir), \
			m_mtimestamp(0), m_ctimestamp(0), m_atimestamp(0), m_isfirst(true)
		{
		}
		MasterFile(const MasterFile &other)
		{
			*this = other;
		}
		const MasterFile &operator=(const MasterFile &other)
		{
			if(this != &other)
			{
				m_filename = other.m_filename;
				m_filehandle = other.m_filehandle;
				m_fromhandle = other.m_fromhandle;
				m_replicas = other.m_replicas;
				m_blockcount = other.m_blockcount;
				m_geocodes = other.m_geocodes;
				m_uuidcodes = other.m_uuidcodes;
				m_partlengths = other.m_partlengths;
				m_rowkeycodes = other.m_rowkeycodes;
				m_isfirst = other.m_isfirst;
				m_datatype = other.m_datatype;
				m_mtimestamp = other.m_mtimestamp;
				m_ctimestamp = other.m_ctimestamp;
				m_atimestamp = other.m_atimestamp;
			}

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_filename & m_filehandle & m_fromhandle & m_replicas & m_blockcount & m_geocodes & m_uuidcodes & m_partlengths & m_rowkeycodes & m_isfirst & m_datatype & m_mtimestamp & m_ctimestamp & m_atimestamp;
		}
		bool operator==(const MasterFile &other)
		{
			return m_filename == other.m_filename && m_filehandle == other.m_filehandle;
		}
	};
	typedef std::vector<MasterFile> MasterFileVector;

	/*!
	*
	**/
	struct MasterChunk
	{
		// block
		long long m_fileoffset;								//
		long long m_chunkhandle;							// also as chunkhandle, uuid
		long long m_version;								//
		long m_chunklength;
		string m_chunkfile;									// alias name of m_name
		string m_localdir;									// corresponding to chunk server, disk

		/*!
		*
		**/
		MasterChunk() : m_fileoffset(0), m_chunkhandle(0), m_version(0), m_chunklength(0), m_chunkfile(""), m_localdir("")
		{
		}
		MasterChunk(const MasterChunk &other)
		{
			*this = other;
		}
		const MasterChunk &operator=(const MasterChunk &other)
		{
			if(this != &other)
			{
				m_fileoffset = other.m_fileoffset;
				m_chunkhandle = other.m_chunkhandle;
				m_version = other.m_version;
				m_chunklength = other.m_chunklength;
				m_chunkfile = other.m_chunkfile;
				m_localdir = other.m_localdir;
			}

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_fileoffset & m_chunkhandle & m_version & m_chunklength & m_chunkfile & m_localdir;
		}
		bool operator==(const MasterChunk &other)
		{
			return m_chunkhandle == other.m_chunkhandle;
		}
	};
	typedef std::vector<MasterChunk> MasterChunkVector;

	/*!
	*
	**/
	struct MasterSpatial
	{
		// spatial, as the whole layer or as a geometry: st-kida
		double m_minx;
		double m_maxx;
		double m_miny;
		double m_maxy;
		double m_minz;
		double m_maxz;

		/*!
		*
		**/
		MasterSpatial() : m_minx(0.), m_miny(0.), m_maxx(0.), m_maxy(0.), m_minz(0.), m_maxz(0.)
		{
		}
		MasterSpatial(const MasterSpatial &other)
		{
			*this = other;
		}
		const MasterSpatial &operator=(const MasterSpatial &other)
		{
			if(this != &other)
			{
				m_minx = other.m_minx;
				m_maxx = other.m_maxx;
				m_miny = other.m_miny;
				m_maxy = other.m_maxy;
				m_minz = other.m_minz;
				m_maxz = other.m_maxz;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_minx & m_maxx & m_miny & m_maxy & m_minz & m_maxz;
		}
		bool operator==(const MasterSpatial &other)
		{
			return ::fabs(m_minx-other.m_minx) < 10. && ::fabs(m_maxx - other.m_maxx) < 10. && \
				::fabs(m_miny-other.m_miny) < 10. && ::fabs(m_maxy-other.m_maxy) < 10.;
		}
	};

	/*!
	*
	**/
	struct MasterAccess
	{
		long m_rlock;
		long m_wlock;
		long long m_writinghandle;
		double m_leasefrom;
		double m_leaseto;

		/*!
		*
		**/
		MasterAccess() : m_rlock(0), m_wlock(0), m_writinghandle(0), m_leasefrom(0), m_leaseto(0)
		{
		}
		MasterAccess(const MasterAccess &other)
		{
			*this = other;
		}
		const MasterAccess &operator=(const MasterAccess &other)
		{
			if(this != &other)
			{
				m_rlock = other.m_rlock;
				m_wlock = other.m_wlock;
				m_writinghandle = other.m_writinghandle;
				m_leasefrom = other.m_leasefrom;
				m_leaseto = other.m_leaseto;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_rlock & m_wlock &  m_writinghandle & m_leasefrom & m_leaseto;
		}
		bool operator==(const MasterSpatial &other)
		{
			return true;
		}
	};

	/*!
	*
	**/
	struct MasterOperation
	{
		bool m_isAdded;
		bool m_isUpdated;
		bool m_isDeleted;

		/*!
		*
		**/
		MasterOperation() : m_isAdded(false), m_isUpdated(false), m_isDeleted(false)
		{
		}
		MasterOperation(const MasterOperation &other)
		{
			*this = other;
		}
		const MasterOperation &operator=(const MasterOperation &other)
		{
			if(this != &other)
			{
				m_isAdded = other.m_isAdded;
				m_isUpdated = other.m_isUpdated;
				m_isDeleted = other.m_isDeleted;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_isAdded & m_isUpdated &  m_isDeleted;
		}
		bool operator==(const MasterSpatial &other)
		{
			return true;
		}
	};

	/*!
	*
	**/
	struct MasterRecord : public MasterNamespace, \
		public MasterChunkServer, \
		public MasterFile, \
		public MasterChunk ,\
		public MasterSpatial, \
		public MasterAccess,\
		public MasterOperation
	{
		const MasterRecord &operator=(const MasterRecord &other)
		{
			if(this != &other)
			{
				*((MasterNamespace*)this) = *((MasterNamespace*)&other);
				*((MasterChunkServer*)this) = *((MasterChunkServer*)&other);
				*((MasterFile*)this) = *((MasterFile*)&other);
				*((MasterChunk*)this) = *((MasterChunk*)&other);
				*((MasterSpatial*)this) = *((MasterSpatial*)&other);
				*((MasterAccess*)this) = *((MasterAccess*)&other);
				*((MasterOperation*)this) = *((MasterOperation*)&other);
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			serializeParent( (MasterNamespace*) 0, ar, *this);
			serializeParent( (MasterChunkServer*) 0, ar, *this);
			serializeParent( (MasterFile*) 0, ar, *this);
			serializeParent( (MasterChunk*) 0, ar, *this);
			serializeParent( (MasterSpatial*) 0, ar, *this);
			serializeParent( (MasterAccess*) 0, ar, *this);
			serializeParent( (MasterOperation*) 0, ar, *this);
		}
		bool operator==(const MasterRecord &other)
		{
			return
				MasterNamespace::operator==(other) &&
				MasterChunkServer::operator==(other) &&
				MasterFile::operator==(other) &&
				MasterChunk::operator==(other) &&
				MasterSpatial::operator==(other) &&
				MasterAccess::operator==(other) &&
				MasterOperation::operator==(other);
		}
	};
	typedef std::vector<MasterRecord> MasterRecordVector;
	typedef MasterRecordVector::iterator rec_itr;
	typedef MasterRecordVector::const_iterator rec_citr;

	/*!
	*
	**/
	struct RequestEntry
	{
		enum Priority
		{
			Lowest = 0,
			Low,
			Middle,
			High,
			Highest
		};

		int m_priority;
		long m_key;
		long m_timestamp;
		long m_spatialstamp;
		bool m_isReady;

		static int GetNextKey()
		{
			static int m_nextKey = 0;
			return m_nextKey++;
		};
	};
	struct RequestCookie : public RequestEntry
	{
	};

	/*!
	*
	**/
	struct LoginInfo
	{
		// ...

		void serialize(SF::Archive & ar) 
		{}
	};

	/*!
	*
	**/
	struct AuthenticationState
	{
		bool m_isAuthenticated;
		std::string m_clientUsername;
		LoginInfo m_loginInfo;

		/*!
		*
		**/
		AuthenticationState() : m_isAuthenticated(false)
		{
		}
	};

	/*!
	*
	**/
	enum JobEngineType
	{
		JET_Unknown = -1,
		JET_GDE_Slice,
		JET_GDE_Attribute_Triangulate,
		JET_GDE_Attribute_Instant,
		JET_GDE_Attribute_DipAzimuth,
		JET_GDE_Attribute_AlphaFilter,
		JET_GDE_Attribute_Irregular,
		JET_GDE_Attribute_Ellipse,
		JET_GDE_Attribute_ThreeBayes,
		JET_GDE_Attribute_BasicTrack,
		JET_GDE_Attribute_RockPhysics,
		JET_GDE_Attribute_Brick,
		JET_GDE_Attribute_Conherency,
		JET_GDE_Attribute_Curvature,
		JET_GDE_Attribute_Cag,
		JET_GDE_Attribute_Window,
		JET_GDE_Raster_Slice,
		JET_GDE_Marching_Cube,
		JET_SDE_Marching_Cube,
		JET_Max
	};
	static char gJobEngineName[JET_Max][127] = { \
		"GDE for Slice",
		"GDE for Time-Frequency Attribute Analysis with Triangulate Filter",
		"GDE for Instant Attribute",
		"GDE for Dip Azimuth",
		"GDE for Alpha Filter",
		"GDE for Irregular",
		"GDE for Fracture Analysis with Ellpise Fitting",
		"GDE for Three Bayes",
		"GDE for Basic Track",
		"GDE for Rock Physics",
		"GDE for Brick",
		"GDE for Conherency",
		"GDE for Curvature",
		"GDE for Cag",
		"GDE for Time window Attribute",
		"GDE for Raster Slice",
		"GDE for Marching Cube",
		"SDE for Marching Cube"
	};

	/*!
	*
	**/
	struct JobSpecification
	{
		string m_input_gfsname;						// upon which gfs
		string m_output_gfsname;
		short m_jobtype;							// job type for schedule chunks, mapper and reducer
		int m_workernumber;					// limits
		int m_mapworkernumber;			// limits for worker id

		/*!
		*
		**/
		JobSpecification() : m_input_gfsname(""), m_output_gfsname(""), m_jobtype(JET_Unknown), m_workernumber(0), m_mapworkernumber(0)
		{
		}
		JobSpecification(const JobSpecification &other)
		{
			*this = other;
		}
		const JobSpecification &operator=(const JobSpecification &other)
		{
			if(this != &other)
			{
				m_input_gfsname = other.m_input_gfsname;
				m_output_gfsname = other.m_output_gfsname;
				m_jobtype = other.m_jobtype;
				m_workernumber = other.m_workernumber;
				m_mapworkernumber = other.m_workernumber;
			}

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_input_gfsname & m_output_gfsname & m_jobtype & m_workernumber & m_mapworkernumber;
		}
	};

	/*!
	*
	**/
	struct JobTaskServer
	{
		string m_gfsname;
		string m_outgfsname;
		long m_rackid;																// belong to which rack
		string m_ip;																	// hash(name or imageidx)
		long m_port;
		unsigned long long m_workerid;									// hash()
		unsigned char m_workertype;										// mapper, reducer, only mapper, mapper and reducer, etc
		unsigned long long m_groupid;									// mapper and reducer in the same group
		short m_buffersize;
		string m_inputdir;															// m_inputdir\mapper\hash(m_gfsname)\..., m_inputdir\reducer\hash(m_gfsname)\..., 
		string m_outputdir;														// m_outputdir\mapper\hash(m_gfsname)\..., m_outputdir\reducer\hash(m_gfsname)\..., 
		std::vector<unsigned long long> m_chunkuuids;

		/*!
		*
		**/
		JobTaskServer() : m_gfsname(""), m_outgfsname(""), m_rackid(0), m_ip(""), m_port(0), \
			m_workerid(0),  m_workertype(ST_GFS_Task), m_groupid(0), \
			m_buffersize(0), m_inputdir(""), m_outputdir("")
		{
		}
		JobTaskServer(const JobTaskServer &other)
		{
			*this = other;
		}
		const JobTaskServer &operator=(const JobTaskServer &other)
		{
			if(this != &other)
			{
				m_gfsname = other.m_gfsname;
				m_outgfsname = other.m_outgfsname;
				m_rackid = other.m_rackid;
				m_ip = other.m_ip;
				m_port = other.m_port;
				m_workerid = other.m_workerid;
				m_workertype = other.m_workertype;
				m_groupid = other.m_groupid;
				m_buffersize = other.m_buffersize;
				m_inputdir = other.m_inputdir;
				m_outputdir = other.m_outputdir;
				m_chunkuuids.clear();
				m_chunkuuids.assign(other.m_chunkuuids.begin(), other.m_chunkuuids.end());
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gfsname & m_outgfsname & m_rackid & m_ip & m_port & m_workerid & m_workertype & m_groupid & m_buffersize & m_inputdir & m_outputdir & m_chunkuuids;
		}
	};
	typedef std::vector<JobTaskServer> JobTaskServerVector;

	// as parent def for concrete ones defined by other packages
	/*!
	*
	**/
	struct JobParameter
	{
		void serialize(SF::Archive &ar)
		{

		}
	};

	struct MapKey
	{
		void serialize(SF::Archive &ar)
		{

		}
	};
	typedef std::vector<MapKey*> MapKeyVector;

	struct MapValue
	{
		void serialize(SF::Archive &ar)
		{

		}
	};

	struct MapPair
	{
		MapKey *m_key;
		MapValue *m_value;

		MapPair() : m_key(0), m_value(0)
		{
		}

		void serialize(SF::Archive &ar)
		{
			ar & m_key & m_value;
		}
	};
	typedef std::vector<MapPair> MapPairVector;

	struct ReduceKey
	{
		void serialize(SF::Archive &ar)
		{
		}
	};
	typedef std::vector<ReduceKey*> ReduceKeyVector;

	struct ReduceValue
	{
		void serialize(SF::Archive &ar)
		{
		}
	};

	struct ReducePair
	{
		ReduceKey *m_key;
		ReduceValue *m_value;

		ReducePair() : m_key(0), m_value(0)
		{
		}

		void serialize(SF::Archive &ar)
		{
			ar & m_key & m_value;
		}
	};
	typedef std::vector<ReducePair> ReducePairVector;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	/*!
	*
	**/
	struct DeploymentStatus
	{
		// service type masked in different bits
		unsigned int m_kinds;

		// number depolied
		short m_gfsmasternumber;
		short m_gfschunknumber;
		short m_eventnumber;
		short m_mappernumber;
		short m_reducernumber;
		short m_jobnumber;

		// 
		short m_clients;
		short m_machines;										// 部署的机器数
		short m_racks;												// 部署的集群数

		DeploymentStatus() : m_kinds(0), m_gfsmasternumber(0), m_gfschunknumber(0), m_eventnumber(0), m_mappernumber(0), m_reducernumber(0), \
			m_jobnumber(0), m_clients(0), m_machines(0), m_racks(0)
		{
		}
		DeploymentStatus(const DeploymentStatus &other)
		{
			*this = other;
		}
		const DeploymentStatus &operator=(const DeploymentStatus &other)
		{
			if(this != &other)
			{
				m_kinds = other.m_kinds;

				m_gfsmasternumber = other.m_gfsmasternumber;
				m_gfschunknumber = other.m_gfschunknumber;
				m_eventnumber = other.m_eventnumber;
				m_mappernumber = other.m_mappernumber;
				m_reducernumber = other.m_reducernumber;
				m_jobnumber = other.m_jobnumber;

				m_clients = other.m_clients;
				m_machines = other.m_machines;
				m_racks = other.m_racks;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_kinds & m_gfsmasternumber & m_gfschunknumber & m_eventnumber & m_mappernumber & m_reducernumber & m_jobnumber & m_clients & m_machines & m_racks;
		}
	};

	/*!
	* declared in MasterServant, collected by ChunkServant & MasterServant & GFSClient
	**/
	struct GFSChunkStatus 
	{
		string m_gfsfilename;
		string m_gfschunkip;
		int m_gfschunkport;
		string m_gfschunkname;
		double m_uploadedtilesize;
		double m_uploadedtilenumber;
		double m_gfschunkbandwidth;
		double m_splittilenumber;

		GFSChunkStatus() : m_gfsfilename(""), m_gfschunkip(""), m_gfschunkport(0), m_gfschunkname(""), m_uploadedtilesize(0), m_uploadedtilenumber(0), m_gfschunkbandwidth(0), \
			m_splittilenumber(0)
		{
		}
		GFSChunkStatus(const GFSChunkStatus &other)
		{
			*this = other;
		}
		const GFSChunkStatus &operator=(const GFSChunkStatus &other)
		{
			if(this != &other)
			{
				m_gfsfilename = other.m_gfsfilename;
				m_gfschunkip = other.m_gfschunkip;
				m_gfschunkport = other.m_gfschunkport;
				m_gfschunkname = other.m_gfschunkname;
				m_uploadedtilesize = other.m_uploadedtilesize;
				m_uploadedtilenumber = other.m_uploadedtilenumber;
				m_gfschunkbandwidth = other.m_gfschunkbandwidth;
				m_splittilenumber = other.m_splittilenumber;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gfsfilename & m_gfschunkip & m_gfschunkport & m_gfschunkname & m_uploadedtilesize & m_uploadedtilenumber & m_gfschunkbandwidth & m_splittilenumber;
		}
	};

	typedef std::map<string, std::map<pair<string,int>, GFSChunkStatus>> GFSChunkStatusMap;
	/*!
	* declared in MasterServant, collected by ChunkServant & MasterServant & GFSClient
	**/
	struct GFSUploadStatus
	{
		// for the whole distribution file
		string m_gfsfilename;									// 创建的分布式文件名称
		double m_gfsfilesize;									// 创建的分布式文件大小, MB
		long m_gfsrmetarecords;								// 创建的分布式文件对应的元数据记录

		// input
		string m_inputfilename;								// 输入文件名称
		double m_inputfilesize;										// 输入文件大小, MB

		double m_gfsfromtime;									// 创建的	起始时间， CAnyTimeBasic
		double m_gfstotime;                                     // 创建的结束时间，
		double m_gfsfileelapsedtime;							// 完成的时间，单位秒
		
		long m_gfschunkscrashed;								// 所属失败CHUNK数
		std::vector<string> m_chunkipcrashed;			// 失败CHUNK的IP

		// for one chunk file
		double m_chunkfilesize;										// 对应的单一数据块文件大小
		long m_chunkfilenumber;									// 数据块文件总数
		long m_chunkreplicas;										// 数据块冗余备份

		// for upload a chunk
		double m_chunkminuploadtime;							// 上传最慢时间
		double m_chunkmaxuploadtime;							// 上传最快时间
		string m_chunkminuploadip;							// 完成上传最慢服务
		string m_chunkmaxuploadip;							 // 完成上传最快服务

		double m_chunkminbandwidth;                          // 完成上传最小带宽 kb/s
		double m_chunkmaxbandwidth;                         // 完成上传最大带宽 kb/s
		string m_chunkminbandip;							  // 完成上传最小带宽服务
		string m_chunkmaxbandip;                           // 完成上传最大带宽服务

		long m_chunkminfilenumber;							// 存储最少数据块数目
		long m_chunkmaxfilenumber;                         // 存储最多数据块数目
		string m_chunkminfilenumberip;                 // 存储最少数据块数目的服务
		string m_chunkmaxfilenumberip;					// 存储最多数据块数目的服务

		// for upload process
		long m_chunkuploadednumber;                     // 已完成的上传数据块数目，可用于进度提示
		long m_chunkfailednumber;                            // 创建过程中失败的上传数据块数目

		// mem
		std::vector<string> m_status;

		GFSUploadStatus() : m_gfsfilename(""), m_gfsfilesize(ANY_NAN), m_gfsrmetarecords(0), m_inputfilename(""), m_inputfilesize(ANY_NAN), m_gfsfromtime(ANY_NAN), \
			m_gfstotime(ANY_NAN), m_gfsfileelapsedtime(ANY_NAN), m_gfschunkscrashed(0), m_chunkfilesize(ANY_NAN), m_chunkfilenumber(0), m_chunkreplicas(0), m_chunkminuploadtime(ANY_NAN), \
			m_chunkmaxuploadtime(ANY_NAN), m_chunkminuploadip(""), m_chunkmaxuploadip(""), m_chunkminbandwidth(ANY_NAN), m_chunkmaxbandwidth(ANY_NAN), m_chunkminbandip(""), m_chunkmaxbandip(""), \
			m_chunkminfilenumber(0), m_chunkmaxfilenumber(0), m_chunkminfilenumberip(""), m_chunkmaxfilenumberip(""), m_chunkuploadednumber(0), m_chunkfailednumber(0)
		{
		}
		GFSUploadStatus(const GFSUploadStatus &other)
		{
			*this = other;
		}
		const GFSUploadStatus &operator=(const GFSUploadStatus &other)
		{
			if(this != &other)
			{
				m_gfsfilename = other.m_gfsfilename;
				m_gfsfilesize = other.m_gfsfilesize;
				m_gfsrmetarecords = other.m_gfsrmetarecords;

				m_inputfilename = other.m_inputfilename;
				m_inputfilesize = other.m_inputfilesize;

				m_gfsfromtime = other.m_gfsfromtime;
				m_gfstotime = other.m_gfstotime;
				m_gfsfileelapsedtime = other.m_gfsfileelapsedtime;

				m_gfschunkscrashed = other.m_gfschunkscrashed;
				m_chunkipcrashed = other.m_chunkipcrashed;

				m_chunkfilesize = other.m_chunkfilesize;
				m_chunkfilenumber = other.m_chunkfilenumber;
				m_chunkreplicas = other.m_chunkreplicas;

				m_chunkminuploadtime = other.m_chunkminuploadtime;
				m_chunkmaxuploadtime = other.m_chunkmaxuploadtime;
				m_chunkminuploadip = other.m_chunkminuploadip;
				m_chunkmaxuploadip = other.m_chunkmaxuploadip;

				m_chunkminbandwidth = other.m_chunkminbandwidth;
				m_chunkmaxbandwidth = other.m_chunkmaxbandwidth;
				m_chunkminbandip = other.m_chunkminbandip;
				m_chunkmaxbandip = other.m_chunkmaxbandip;

				m_chunkminfilenumber = other.m_chunkminfilenumber;
				m_chunkmaxfilenumber = other.m_chunkmaxfilenumber;
				m_chunkminfilenumberip = other.m_chunkminfilenumberip;
				m_chunkmaxfilenumberip = other.m_chunkmaxfilenumberip;

				m_chunkuploadednumber = other.m_chunkuploadednumber;
				m_chunkfailednumber = other.m_chunkfailednumber;

				m_status.clear();
				m_status.assign(other.m_status.begin(), other.m_status.end());
			}
			return *this;
		}
		static double CalculateTimeRange(double begintime, double endtime)
		{
			int beginyear = (int)(begintime / 10000000000);
			int beginmonth = (int)((begintime - beginyear * 10000000000) / 100000000);
			int beginday = (int)((begintime - beginyear * 10000000000 - beginmonth * 100000000) / 1000000);
			int beginhour = (int)((begintime - beginyear * 10000000000 - beginmonth * 100000000 - beginday * 1000000) / 10000);
			int beginminitue = (int)((begintime - beginyear * 10000000000 - beginmonth * 100000000 - beginday * 1000000 - beginhour * 10000) / 100);
			int beginsecond = (int)((begintime - beginyear * 10000000000 - beginmonth * 100000000 - beginday * 1000000 - beginhour * 10000 - beginminitue * 100) / 1);
			int endyear = (int)(endtime / 10000000000);
			int endmonth = (int)((endtime - endyear * 10000000000) / 100000000);
			int endday = (int)((endtime - endyear * 10000000000 - endmonth * 100000000) / 1000000);
			int endhour = (int)((endtime - endyear * 10000000000 - endmonth * 100000000 - endday * 1000000) / 10000);
			int endminitue = (int)((endtime - endyear * 10000000000 - endmonth * 100000000 - endday * 1000000 - endhour * 10000) / 100);
			int endsecond = (int)((endtime - endyear * 10000000000 - endmonth * 100000000 - endday * 1000000 - endhour * 10000 - endminitue * 100) / 1);
			return (endyear - beginyear) * 365 * 24 * 3600 + (endmonth - beginmonth) * 30 * 24 * 3600 + (endday - beginday) * 24 * 3600 + (endhour - beginhour) * 3600 + \
				(endminitue - beginminitue) * 60 + (endsecond - beginsecond);
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gfsfilename & m_gfsfilesize & m_gfsrmetarecords & m_inputfilename & m_inputfilesize & m_gfsfromtime & m_gfstotime & m_gfsfileelapsedtime & \
				m_gfschunkscrashed & m_chunkipcrashed & m_chunkfilesize & m_chunkfilenumber & m_chunkreplicas & m_chunkminuploadtime & m_chunkmaxuploadtime & m_chunkminuploadip & \
				m_chunkmaxuploadip & m_chunkminbandwidth & m_chunkmaxbandwidth & m_chunkminbandip & m_chunkmaxbandip & m_chunkminfilenumber & m_chunkmaxfilenumber & m_chunkminfilenumberip & \
				m_chunkmaxfilenumberip & m_chunkuploadednumber & m_chunkfailednumber & m_status;
		}
	};
	typedef std::map<string, GFSUploadStatus> GFSUploadStatusMap;

	/*!
	* declared in MasterServant, collected by ChunkServant & MasterServant & GFSClient
	**/
	struct GFSDownloadStatus
	{
		//
		string m_gfsfilename;								// 创建的分布式文件名称
		double m_gfsfilesize;								// 创建的分布式文件大小, MB
		long m_gfschunktotalnumber;
		
		//
		long m_chunkdownlimits;											// 客户端CHUNK下载的限制
		long m_chunkdownnumber;										// 客户端需要完成的下载数目
		long m_chunkdownfinishednumber;						// 已完成的数，可用于进度

		//
		double m_chunkallfromtime;									// 完成所有chunk下载的起始时间
		double m_chunkalltotime;											// 完成上述下载的结束时间
		double m_chunkallelapsedtime;									// 完成上述下载的时间

		// for download process
		double m_chunkmindownloadtime;								// 上传最慢时间
		double m_chunkmaxdownloadtime;							// 上传最快时间
		string m_chunkmindownloadip;								// 完成上传最慢服务
		string m_chunkmaxdownloadip;								// 完成上传最快服务

		double m_chunkminbandwidth;									// 完成上传最小带宽
		double m_chunkmaxbandwidth;									// 完成上传最大带宽
		string m_chunkminbandip;										// 完成上传最小带宽服务
		string m_chunkmaxbandip;										// 完成上传最大带宽服务

		long m_chunkminfilenumber;									// 下载最少数据块数目
		long m_chunkmaxfilenumber;									// 下载最多数据块数目
		string m_chunkminfilenumberip;								// 下载最少数据块数目的服务
		string m_chunkmaxfilenumberip;								// 下载最多数据块数目的服务

		//
		std::vector<string> m_status;

		GFSDownloadStatus() : m_gfsfilename(""), m_gfsfilesize(ANY_NAN), m_gfschunktotalnumber(0), m_chunkdownlimits(0), m_chunkdownnumber(0), \
			m_chunkdownfinishednumber(0), m_chunkallfromtime(ANY_NAN), m_chunkalltotime(ANY_NAN), m_chunkallelapsedtime(ANY_NAN), m_chunkmindownloadtime(ANY_NAN), \
			m_chunkmaxdownloadtime(ANY_NAN), m_chunkmindownloadip(""), m_chunkmaxdownloadip(""), m_chunkminbandwidth(ANY_NAN), m_chunkmaxbandwidth(ANY_NAN), m_chunkminbandip(""), m_chunkmaxbandip(""), \
			m_chunkminfilenumber(0), m_chunkmaxfilenumber(0), m_chunkminfilenumberip(""), m_chunkmaxfilenumberip("")
		{
		}
		GFSDownloadStatus(const GFSDownloadStatus &other)
		{
			*this = other;
		}
		const GFSDownloadStatus &operator=(const GFSDownloadStatus &other)
		{
			if(this != &other)
			{
				m_gfsfilename = other.m_gfsfilename;
				m_gfsfilesize = other.m_gfsfilesize;
				m_gfschunktotalnumber = other.m_gfschunktotalnumber;

				m_chunkdownlimits = other.m_chunkdownlimits;
				m_chunkdownnumber = other.m_chunkdownnumber;
				m_chunkdownfinishednumber = other.m_chunkdownfinishednumber;

				m_chunkallfromtime = other.m_chunkallfromtime;
				m_chunkalltotime = other.m_chunkalltotime;
				m_chunkallelapsedtime = other.m_chunkallelapsedtime;

				m_chunkmindownloadtime = other.m_chunkmindownloadtime;
				m_chunkmaxdownloadtime = other.m_chunkmaxdownloadtime;
				m_chunkmindownloadip = other.m_chunkmindownloadip;
				m_chunkmaxdownloadip = other.m_chunkmaxdownloadip;

				m_chunkminbandwidth = other.m_chunkminbandwidth;
				m_chunkmaxbandwidth = other.m_chunkmaxbandwidth;
				m_chunkminbandip = other.m_chunkminbandip;
				m_chunkmaxbandip = other.m_chunkmaxbandip;

				m_chunkminfilenumber = other.m_chunkminfilenumber;
				m_chunkmaxfilenumber = other.m_chunkmaxfilenumber;
				m_chunkminfilenumberip = other.m_chunkminfilenumberip;
				m_chunkmaxfilenumberip = other.m_chunkmaxfilenumberip;

				m_status = other.m_status;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gfsfilename & m_gfsfilesize & m_gfschunktotalnumber & m_chunkdownlimits & m_chunkdownnumber & m_chunkdownfinishednumber & m_chunkallfromtime & m_chunkalltotime & \
				m_chunkallelapsedtime & m_chunkmindownloadtime & m_chunkmaxdownloadtime & m_chunkmindownloadip & m_chunkmaxdownloadip & m_chunkminbandwidth & m_chunkmaxbandwidth & \
				m_chunkminbandip & m_chunkmaxbandip & m_chunkminfilenumber & m_chunkmaxfilenumber & m_chunkminfilenumberip & m_chunkmaxfilenumberip & m_status;
		}
	};
	typedef std::map<string, GFSDownloadStatus> GFSDownloadStatusMap;

	/*!
	* declared in xxxTaskServant, collected or monitored by JobClient & xxTaskServant
	**/
	struct JobTaskStatus
	{
		string m_gfsfilename;													// 计算的分布式文件
		long m_gfschunknumber;													// 分配待计算的总数据块数
		std::vector<string> m_gfschunkip;										// 数据块所在的服务

		double m_memoryquota;													// 剩余的内存
		double m_datadirquota;													// 剩余的硬盘空间, m_datadir
		double m_inputdirquota;													// 剩余的硬盘空间, m_intputdir
		double m_outputdirquota;												// 剩余的硬盘空间, m_outputdir
		string m_whichpartition;												// which分区剩余空间最大
		double m_diskmaxquota;

		long m_taskchunks;														// 每一MAPPER与REDUCER执行的任务数
		long m_taskexecuted;													// 已执行的任务数，可用作进度
		long m_taskfails;														// 执行过程中失败的任务数
		
		double m_taskmintime;													// 执行的最少时间
		double m_taskmaxtime;													// 执行的最多时间

		double m_taskminbandwidth;												// 当前服务，执行时的最小带宽
		double m_taskmaxbandwidth;												// 当前服务，执行时的最大带宽

		double m_taskallfromtime;												// 当前服务，所有任务执行开始的时间
		double m_taskalltotime;													// 当前服务，所有任务执行结束的时间	
		double m_taskallelapsed;												// 当前服务，所有任务执行时间

		bool m_isnormaldone;													// 正常结束
		bool m_isabnormaldone;													// 异常退出，结束

		JobTaskStatus() : m_gfsfilename(""), m_gfschunknumber(0), m_memoryquota(ANY_NAN), m_datadirquota(ANY_NAN), m_inputdirquota(ANY_NAN), m_outputdirquota(ANY_NAN), \
			m_whichpartition(""), m_diskmaxquota(ANY_NAN), m_taskchunks(0), m_taskexecuted(0), m_taskfails(0), \
			m_taskmintime(ANY_NAN), m_taskmaxtime(ANY_NAN), m_taskminbandwidth(ANY_NAN), m_taskmaxbandwidth(ANY_NAN), m_taskallfromtime(ANY_NAN), \
			m_taskalltotime(ANY_NAN), m_taskallelapsed(ANY_NAN), m_isnormaldone(false), m_isabnormaldone(false)
		{
		}
		JobTaskStatus(const JobTaskStatus &other)
		{
			*this = other;
		}
		const JobTaskStatus &operator=(const JobTaskStatus &other)
		{
			if(this != &other)
			{
				m_gfsfilename = other.m_gfsfilename;
				m_gfschunknumber = other.m_gfschunknumber;
				m_gfschunkip = other.m_gfschunkip;

				m_memoryquota = other.m_memoryquota;
				m_datadirquota = other.m_datadirquota;
				m_inputdirquota = other.m_inputdirquota;
				m_outputdirquota = other.m_outputdirquota;
				m_whichpartition = other.m_whichpartition;
				m_diskmaxquota = other.m_diskmaxquota;

				m_taskchunks = other.m_taskchunks;
				m_taskexecuted = other.m_taskexecuted;
				m_taskfails = other.m_taskfails;

				m_taskmintime = other.m_taskmintime;
				m_taskmaxtime = other.m_taskmaxtime;
				
				m_taskminbandwidth = other.m_taskminbandwidth;
				m_taskmaxbandwidth = other.m_taskmaxbandwidth;
				
				m_taskallfromtime = other.m_taskallfromtime;
				m_taskalltotime = other.m_taskalltotime;
				m_taskallelapsed = other.m_taskallelapsed;

				m_isnormaldone = other.m_isnormaldone;
				m_isabnormaldone = other.m_isabnormaldone;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gfsfilename & m_gfschunknumber & m_gfschunkip & m_memoryquota & m_datadirquota & m_inputdirquota & m_outputdirquota & \
				m_whichpartition & m_diskmaxquota & m_taskchunks & m_taskexecuted & m_taskfails & m_taskmintime & m_taskmaxtime & \
				m_taskminbandwidth & m_taskmaxbandwidth & m_taskallfromtime & m_taskalltotime & m_taskallelapsed & m_isnormaldone & m_isabnormaldone;
		}
	};
	typedef std::map<string, JobTaskStatus> JobTaskStatusMap;

	/*!
	* declared in JobServant, collected or monitored by JobClient & JobServant & eventServant
	**/
	struct JobStatus
	{
		//
		string m_gfsfilename;										// 计算的分布式文件
		int m_gfschunknumber;										// 待计算的总数据块数
		int m_gfschunkexecutednumber;						// 已完成的数据块数，可用作进度

		//
		double m_jobfromtime;										// job开始时间
		double m_jobtotime;											// job结束时间		
		double m_jobelapsedtime;								// job总用时

		//
		double m_jobminbandwidth;							// job最小带宽
		double m_jobmaxbandwidth;							// job最大带宽

		//
		unsigned short m_jobtasktype;						// 计算类型
		bool m_ismapperalldone;								// 是否所有mapper执行完毕
		bool m_isreduceralldone;									// 是否所有reducer执行完毕
		long m_mapperexecuted;								// 已执行的mapper数
		long m_mapperfails;											/// 失败的mapper数
		std::vector<string> m_mapperfailsip;				// 失败的MAPPER服务
		long m_reducerexecuted;									// 已执行的reducer数
		long m_reducerfails;											// 失败的reducer数
		std::vector<string> m_reducerfailsip;				// 失败的REDUCER服务

		/*!
		*
		**/
		JobStatus() : m_gfsfilename(""), m_gfschunknumber(0), m_gfschunkexecutednumber(0), m_jobfromtime(ANY_NAN), m_jobtotime(ANY_NAN), m_jobelapsedtime(ANY_NAN), \
			m_jobminbandwidth(ANY_NAN), m_jobmaxbandwidth(ANY_NAN), m_jobtasktype(0), m_ismapperalldone(false), m_isreduceralldone(false), \
			m_mapperexecuted(0), m_mapperfails(0), m_reducerexecuted(0), m_reducerfails(0)
		{
		}
		JobStatus(const JobStatus &other)
		{
			*this = other;
		}
		const JobStatus &operator=(const JobStatus &other)
		{
			if(this != &other)
			{
				m_gfsfilename = other.m_gfsfilename;
				m_gfschunknumber = other.m_gfschunknumber;
				m_gfschunkexecutednumber = other.m_gfschunkexecutednumber;

				m_jobfromtime = other.m_jobfromtime;
				m_jobtotime = other.m_jobtotime;
				m_jobelapsedtime = other.m_jobelapsedtime;

				m_jobminbandwidth = other.m_jobminbandwidth;
				m_jobmaxbandwidth = other.m_jobmaxbandwidth;

				m_jobtasktype = other.m_jobtasktype;
				m_ismapperalldone = other.m_ismapperalldone;
				m_isreduceralldone = other.m_isreduceralldone;
				m_mapperexecuted = other.m_mapperexecuted;
				m_mapperfails = other.m_mapperfails;
				m_mapperfailsip = other.m_mapperfailsip;
				m_reducerexecuted = other.m_reducerexecuted;
				m_reducerfails = other.m_reducerfails;
				m_reducerfailsip = other.m_reducerfailsip;
			}
			return *this;
		}
		void Initialize()
		{
			m_ismapperalldone = false;
			m_isreduceralldone = false;
			m_mapperexecuted = 0;
			m_mapperfails = 0;
			m_mapperfailsip.clear();
			m_reducerexecuted = 0;
			m_reducerfails = 0;
			m_reducerfailsip.clear();
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_gfsfilename & m_gfschunknumber & m_gfschunkexecutednumber & m_jobfromtime & m_jobtotime & m_jobelapsedtime & m_jobminbandwidth & m_jobmaxbandwidth & \
				m_jobtasktype & m_ismapperalldone & m_isreduceralldone & m_mapperexecuted & m_mapperfails & m_mapperfailsip & m_reducerexecuted & m_reducerfails & m_reducerfailsip;
		}
	};
	typedef std::map<string, JobStatus> JobStatusMap;   // 现在暂不支持：同一分布式文件，不同作业。

	/*!
	* 
	**/
	struct RCFpointInt
	{
		int m_x;
		int m_y;
		int m_z;

		/*!
		*
		**/
		RCFpointInt() : m_x(ANY_NAN), m_y(ANY_NAN), m_z(ANY_NAN)
		{
		}
		RCFpointInt(int x, int y, int z) : m_x(x), m_y(y), m_z(z)
		{
		}
		RCFpointInt(const RCFpointInt &other)
		{
			*this = other;
		}
		const RCFpointInt &operator=(const RCFpointInt &other)
		{
			if(this != &other)
			{
				m_x = other.m_x;
				m_y = other.m_y;
				m_z = other.m_z;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_x & m_y & m_z;
		}
	};

	/*!
	*
	**/
	struct SessionRequest
	{
		std::string	mServantBindingName;
		std::string	mInterfaceName;
		int	mFnId;
		bool	mOneway;
		short   mSerializationProtocol;
		int                     mRuntimeVersion;
		int                     mArchiveVersion;
		boost::uint32_t         mPingBackIntervalMs;
		bool                    mUseNativeWstringSerialization;
		bool                    mEnableSfPointerTracking;

		SessionRequest() : mServantBindingName(""), mInterfaceName(""), mFnId(-1), mOneway(false), mSerializationProtocol(0), mRuntimeVersion(0), mArchiveVersion(0), mPingBackIntervalMs(0), \
			mUseNativeWstringSerialization(false), mEnableSfPointerTracking(false)
		{
		}
		SessionRequest(const SessionRequest &other)
		{
			*this = other;
		}
		const SessionRequest &operator=(const SessionRequest &other)
		{
			if(this != &other)
			{
				mServantBindingName = other.mServantBindingName;
				mInterfaceName = other.mInterfaceName;
				mFnId = other.mFnId;
				mOneway = other.mOneway;
				mSerializationProtocol = other.mSerializationProtocol;
				mRuntimeVersion = other.mRuntimeVersion;
				mArchiveVersion = other.mArchiveVersion;
				mPingBackIntervalMs = other.mPingBackIntervalMs;
				mUseNativeWstringSerialization = other.mUseNativeWstringSerialization;
				mEnableSfPointerTracking = other.mEnableSfPointerTracking;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar &  mServantBindingName & mInterfaceName & mFnId & mOneway & mSerializationProtocol & mRuntimeVersion & mArchiveVersion & mPingBackIntervalMs & \
			mUseNativeWstringSerialization & mEnableSfPointerTracking;
		}
	};
	struct SessionConnection
	{
		// 传输协议
		short m_transportType;
		// 客户端地址:端口
		string m_clientAddr;
		// 请求
		// 自定义的请求附加数据
		string m_customRequestData;
		// 客户端的连接成功的时间点（ms)
		time_t m_connectedAt;
		// 客户端连接的时长(S)，从客户端调用接口开始计算
		size_t m_connectedDurationS;
		// 客户端的调用次数
		size_t m_callCount;
		// 发送和收到的字节数
		boost::uint64_t m_totalBytesReceived;
		boost::uint64_t m_totalBytesSent;

		SessionConnection() : m_transportType(0), m_clientAddr(""), m_customRequestData(""), m_connectedAt(0), m_connectedDurationS(0), m_callCount(0), m_totalBytesReceived(0), m_totalBytesSent(0)
		{
		}
		SessionConnection(const SessionConnection &other)
		{
			*this = other;
		}
		const SessionConnection &operator=(const SessionConnection &other)
		{
			if(this != &other)
			{
				m_transportType = other.m_transportType;
				// 客户端地址:端口
				m_clientAddr = other.m_clientAddr;
				// 自定义的请求附加数据
				m_customRequestData = other.m_customRequestData;
				// 客户端的连接成功的时间点（ms)
				m_connectedAt = other.m_connectedAt;
				// 客户端连接的时长(S)，从客户端调用接口开始计算
				m_connectedDurationS = other.m_connectedDurationS;
				// 客户端的调用次数
				m_callCount = other.m_callCount;
				// 发送和收到的字节数
				m_totalBytesReceived = other.m_totalBytesReceived;
				m_totalBytesSent = other.m_totalBytesSent;					
			}

			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar &  m_transportType & m_clientAddr & m_customRequestData & m_connectedAt & m_connectedDurationS & m_callCount & m_totalBytesReceived & m_totalBytesSent;
		}
	};

	struct SessionObject : public SessionRequest, public SessionConnection
	{
		const SessionObject &operator=(const SessionObject &other)
		{
			if(this != &other)
			{
				*((SessionRequest*)this) = *((SessionRequest*)&other);
				*((SessionConnection*)this) = *((SessionConnection*)&other);
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			serializeParent( (SessionRequest*) 0, ar, *this);
			serializeParent( (SessionConnection*) 0, ar, *this);
		}
	};
	typedef std::vector<SessionObject> SessionObjectVector;

	/*!
	*
	**/
	struct LocalChunkFile
	{
		long m_chunkindex;			 // 
		unsigned long long m_chunkuuid;
		string m_chunkfile;

		bool m_isallocated;			// whether is ready for upload
		bool m_isuploaded;			// whether is uploaded 
		bool m_isdownloaded;
		short m_hits;
		long m_order;				// 
	
		string m_gfsfile;			//
		string m_localpath;			//
		string m_localfile;			// include path

		int m_failure_tries;			// the number setting until upload or download successfully
		int m_failure_try_seconds;		// the sleep time for next try, ms

		LocalChunkFile() : m_chunkindex(0), m_chunkuuid(0), m_chunkfile(""), m_isallocated(false), \
			m_isdownloaded(false), m_isuploaded(false), m_hits(0),m_order(0), \
			m_gfsfile(""), m_localpath(""), m_localfile(""), \
			m_failure_tries(500), m_failure_try_seconds(10000)
		{
		}

		/*!
		*
		**/
		string GetChunkFile()
		{
			char buf[64] = {};
			::sprintf(buf, "%llu.afs", m_chunkuuid);
			m_chunkfile = buf;

			return m_chunkfile;
		}
	};


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// geo location servant
	//
	/*!
	* schedule for machine allocation
	*
	* code level per 4 quad tree levels
	* point(16 bytes): location code(14) + direction code(2) 
	* polygon(21 bytes): location code(14) + sequence code(2) + extent code(5)
	**/
	struct GeoLocationBasic
	{
		// current level: 0-1-7
		int m_level;
		// uuid code
		unsigned long long m_uuid_code;
		// hexadecimal code
		string m_geo_code; // // 1: level to assure bytes; 2-15: geosot(hexadecimal) code; >15, 4 bytes for next keys

		GeoLocationBasic()
		{
		}
		GeoLocationBasic(const GeoLocationBasic &other)
		{
			*this = other;
		}
		const GeoLocationBasic &operator=(const GeoLocationBasic &other)
		{
			if(this != &other)
			{
				m_level = other.m_level;
				m_uuid_code = other.m_uuid_code;
				m_geo_code = other.m_geo_code;
			}
			return *this;
		}
	};
	struct GeoLocationMachine : public GeoLocationBasic
	{
		// machine info
		std::vector<unsigned long long> m_machine_locations;

		GeoLocationMachine()
		{
		}
		GeoLocationMachine(const GeoLocationMachine &other)
		{
			*this = other;
		}
		const GeoLocationMachine &operator=(const GeoLocationMachine &other)
		{
			if(this != &other)
			{
				*((GeoLocationBasic*)this) = *((GeoLocationBasic*)&other);
				m_machine_locations = other.m_machine_locations;
			}
			return *this;
		}
	};
	struct GeoLocationNextKey : public GeoLocationBasic
	{
		// next key info
		unsigned long m_next_key;

		GeoLocationNextKey()
		{
		}
		GeoLocationNextKey(const GeoLocationNextKey &other)
		{
			*this = other;
		}
		const GeoLocationNextKey &operator=(const GeoLocationNextKey &other)
		{
			if(this != &other)
			{
				*((GeoLocationBasic*)this) = *((GeoLocationBasic*)&other);
				m_next_key = other.m_next_key;
			}
			return *this;
		}
	};
	struct GeoLocationRowKey
	{
		string m_locationcode;
		string m_infocode;//direction, depth...
		int m_part;//which part of one well, seismic...
		unsigned long long m_datalength;

		GeoLocationRowKey()
		{
		}
		GeoLocationRowKey(const GeoLocationRowKey &other)
		{
			*this = other;
		}
		const GeoLocationRowKey &operator=(const GeoLocationRowKey &other)
		{
			if(this != &other)
			{
				m_locationcode = other.m_locationcode;
				m_infocode = other.m_infocode;
				m_part = other.m_part;
				m_datalength = other.m_datalength;
			}
			return *this;
		}
	};
	struct GeoLocationGrid : public GeoLocationNextKey
	{
		// location code of center point
		unsigned long long m_grid_code;
		string m_grid_codestr;
		// files of this grid
		int m_filecount;
		std::vector<unsigned long long> m_filelengths;
		std::vector<string> m_gfsnames;
		std::vector<std::vector<GeoLocationRowKey> > m_filegeolocationkeys;
		unsigned long long m_filelengthlimit;
		// machine info
		std::vector<unsigned long long> m_machine_locations;

		GeoLocationGrid() : m_filelengthlimit(64 * 1024 * 1024)
		{
		}
		GeoLocationGrid(const GeoLocationGrid &other)
		{
			*this = other;
		}
		const GeoLocationGrid &operator=(const GeoLocationGrid &other)
		{
			if(this != &other)
			{
				*((GeoLocationNextKey*)this) = *((GeoLocationNextKey*)&other);
				m_grid_code = other.m_grid_code;
				m_grid_codestr = other.m_grid_codestr;
				m_filecount = other.m_filecount;
				m_filelengths = other.m_filelengths;
				m_gfsnames = other.m_gfsnames;
				m_filegeolocationkeys = other.m_filegeolocationkeys;
				m_filelengthlimit = other.m_filelengthlimit;
				m_machine_locations = other.m_machine_locations;
			}
			return *this;
		}
	};
	struct GeoLocationPoint : public GeoLocationBasic
	{
		//
		double m_longitude;
		double m_latitude;
		short m_direction_angle;

		//
		GeoLocationPoint() : m_longitude(ANY_NAN), m_latitude(ANY_NAN), m_direction_angle(0)
		{

		}
		GeoLocationPoint(const GeoLocationPoint &other)
		{
			*this = other;
		}
		const GeoLocationPoint &operator=(const GeoLocationPoint &other)
		{
			if(this != &other)
			{
				m_longitude = other.m_longitude;
				m_latitude = other.m_latitude;
				m_direction_angle = other.m_direction_angle;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar &  m_longitude & m_latitude & m_direction_angle;
		}
	};

	struct GeoLocationPolygon : public GeoLocationBasic
	{
		// extent
		double m_longitude_from;
		double m_longitude_to;
		double m_latitude_from;
		double m_latitude_to;

		// point inside
		double m_inside_longitude;
		double m_inside_latitude;

		GeoLocationPolygon() : m_longitude_from(ANY_NAN), m_longitude_to(ANY_NAN), m_latitude_from(ANY_NAN), m_latitude_to(ANY_NAN), \
			m_inside_longitude(ANY_NAN), m_inside_latitude(ANY_NAN)
		{

		}
		GeoLocationPolygon(const GeoLocationPolygon &other)
		{
			*this = other;
		}
		const GeoLocationPolygon &operator=(const GeoLocationPolygon &other)
		{
			if(this != &other)
			{
				m_longitude_from = other.m_longitude_from;
				m_longitude_to = other.m_longitude_to;
				m_latitude_from = other.m_latitude_from;
				m_latitude_to = other.m_latitude_to;
				m_inside_longitude = other.m_inside_longitude;
				m_inside_latitude = other.m_inside_latitude;
			}
			return *this;
		}
		void serialize(SF::Archive &ar)
		{
			ar & m_longitude_from & m_longitude_to & m_latitude_from & m_latitude_to & m_inside_longitude & m_inside_latitude;
		}
	};

	// the state of job node
	enum JobState
	{
		JS_Ready	= 0,
		JS_Run		= 1,
		JS_Wait		= 1 << 1,
		JS_Done		= 1 << 2, // also as mark bits
	};

	// the generic specification of job node 
	struct SimulationJobNode
	{
		// geo model
		long m_model_idx;
		long m_solution_idx;
		long m_block_idx;

		// simulation process
		long m_job_graph_idx;
		long m_job_node_idx;

		// job state 
		unsigned long m_job_state;

		// this job node repeated until the job meets condition
		bool m_is_need_repeated;
		long m_repeat_from_job_idx;

		// for rpc transfer since rpc cant support template function
		bool m_is_loop_node;
		bool m_is_async_node;
		bool m_is_sync_node;
		bool m_is_need_update_model;
		bool m_is_need_solve_model_matrix;
		bool m_is_need_update_solution_block;
		std::string m_function_name;

		//
		SimulationJobNode()
		{
			m_job_node_idx = -1;
			m_is_need_repeated = false;
			m_repeat_from_job_idx = -1;
			m_job_state = JS_Ready;
		}
		SimulationJobNode(const SimulationJobNode &other)
		{
			*this = other;
		}
		const SimulationJobNode &operator=(const SimulationJobNode &other)
		{
			if(this != &other)
			{
				m_model_idx = other.m_model_idx; 
				m_solution_idx = other.m_solution_idx; 
				m_block_idx = other.m_block_idx; 
				m_job_graph_idx = other.m_job_graph_idx; 
				m_job_node_idx = other.m_job_node_idx; 
				m_job_state = other.m_job_state; 
				m_is_need_repeated = other.m_is_need_repeated; 
				m_repeat_from_job_idx = other.m_repeat_from_job_idx; 
				m_is_loop_node = other.m_is_loop_node; 
				m_is_async_node = other.m_is_async_node; 
				m_is_sync_node = other.m_is_sync_node; 
				m_is_need_update_model = other.m_is_need_update_model; 
				m_is_need_solve_model_matrix = other.m_is_need_solve_model_matrix; 
				m_is_need_update_solution_block = other.m_is_need_update_solution_block; 
				m_function_name = other.m_function_name; 
			}
			return *this;
		}

		// agasint RCF
		void serialize(SF::Archive &ar)
		{
			ar & m_model_idx & m_solution_idx & m_block_idx & \
				m_job_graph_idx & m_job_node_idx & m_job_state & m_is_need_repeated & m_repeat_from_job_idx & \
				m_is_loop_node & m_is_async_node & m_is_sync_node & m_is_need_update_model & m_is_need_solve_model_matrix & m_is_need_update_solution_block & m_function_name;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(long);//long m_model_idx;
			curSize += sizeof(long);//long m_solution_idx;
			curSize += sizeof(long);//long m_block_idx;
			curSize += sizeof(long);//long m_job_graph_idx;
			curSize += sizeof(long);//long m_job_node_idx;
			curSize += sizeof(unsigned long);//unsigned long m_job_state;
			curSize += sizeof(bool);//bool m_is_need_repeated;
			curSize += sizeof(long);//long m_repeat_from_job_idx;
			curSize += sizeof(bool);//bool m_is_loop_node;
			curSize += sizeof(bool);//bool m_is_async_node;
			curSize += sizeof(bool);//bool m_is_sync_node;
			curSize += sizeof(bool);//bool m_is_need_update_model;
			curSize += sizeof(bool);//bool m_is_need_solve_model_matrix;
			curSize += sizeof(bool);//bool m_is_need_update_solution_block;
			curSize += (sizeof(int) + m_function_name.length() * sizeof(char));//std::string m_function_name;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_model_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_solution_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_block_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_job_graph_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_job_node_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_job_state, sizeof(unsigned long));data += sizeof(unsigned long);
			memcpy(data, &m_is_need_repeated, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_repeat_from_job_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_is_loop_node, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_is_async_node, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_is_sync_node, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_is_need_update_model, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_is_need_solve_model_matrix, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_is_need_update_solution_block, sizeof(bool));data += sizeof(bool);
			int function_namelength = m_function_name.length();
			memcpy(data, &function_namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_function_name.length(); i++)
			{
				memcpy(data, &(m_function_name[i]), sizeof(char));data += sizeof(char);
			}
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_model_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_solution_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_block_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_job_graph_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_job_node_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_job_state, data, sizeof(unsigned long));data += sizeof(unsigned long);
			memcpy(&m_is_need_repeated, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_repeat_from_job_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_is_loop_node, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_is_async_node, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_is_sync_node, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_is_need_update_model, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_is_need_solve_model_matrix, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_is_need_update_solution_block, data, sizeof(bool));data += sizeof(bool);
			int function_namelength;
			memcpy(&function_namelength, data, sizeof(int));data += sizeof(int);
			m_function_name = "";
			for(int i = 0; i < function_namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_function_name += temp;
			}
		}

		//
		virtual bool do_job() = 0;
	};
	template<typename Signature>
	struct JobNodeRunner : public SimulationJobNode
	{
		typedef boost::function<Signature> BlockFunction;
		BlockFunction m_block_function;

		JobNodeRunner(SimulationJobNode *host_node)
		{
			// geo model
			m_model_idx = host_node->m_model_idx;
			m_solution_idx = host_node->m_solution_idx;
			m_block_idx = host_node->m_block_idx;

			// simulation process
			m_job_graph_idx = host_node->m_job_graph_idx;
			m_job_node_idx = host_node->m_job_node_idx;

			// job state 
			m_job_state = host_node->m_job_state;

			// this job node repeated until the job meets condition
			m_is_need_repeated = host_node->m_is_need_repeated;
			m_repeat_from_job_idx = host_node->m_repeat_from_job_idx;

			// for rpc transfer since rpc cant support template function
			m_is_loop_node = host_node->m_is_loop_node;
			m_is_async_node = host_node->m_is_async_node;
			m_is_sync_node = host_node->m_is_sync_node;
			m_is_need_update_model = host_node->m_is_need_update_model;
			m_is_need_solve_model_matrix = host_node->m_is_need_solve_model_matrix;
			m_is_need_update_solution_block = host_node->m_is_need_update_solution_block;
			m_function_name = host_node->m_function_name;
		}
		bool do_job()
		{
			return m_block_function();
		}
	};
	typedef std::vector<SimulationJobNode*> SimulationJobNodeContainer;

	// job edge
	struct SimulationJobEdge
	{
		SimulationJobNode *m_from_node;
		SimulationJobNode *m_to_node;
	};
	typedef std::vector<SimulationJobEdge*> SimulationJobEdgeContainer;

	//
	struct SimulationJobGraph
	{
		//
		long m_job_graph_idx;
	};

	//
	// simulator & matrix
	//
	struct GeoSimulationSimulator
	{
	};

	struct GeoSimulationMatrix
	{
	};

	//
	// geo model
	struct GeoSimulationBlock : public CGeoRect<double>
	{
		// MPI machine id
		long m_model_idx;
		long m_solution_idx;
		long m_block_idx;

		// includes parameter, intial & partial mesh
		std::string m_block_distributed_data_file;
		// simulation results in phases
		std::vector<std::string> m_block_distributed_simulation_files;
	};
	typedef std::vector<GeoSimulationBlock*> GeoSimulationBlockContainer;

	// one distributed mesh against one kind of solution
	struct GeoSimulationSolution : public CGeoRect<double>
	{
		// MPI machine id
		long m_model_idx;
		long m_solution_idx;
	};

	//
	struct GeoSimulationModel : public CGeoRect<double>
	{
		// MPI machine id
		long m_model_idx; // derived from location rect

		// includes parameter, initial mesh
		std::string m_model_distributed_data_file; // derived from location rect
		// simulation results in phases
		std::vector<std::string> m_model_distributed_simulation_files;
	};

}
#endif