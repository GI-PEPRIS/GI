/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
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
#ifndef __ANYCGAL_HYPER_MESH_BASIC_H__
#define __ANYCGAL_HYPER_MESH_BASIC_H__

#include "any/math/anykrigsimulator.h"
using namespace AnyMath;

//
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//
#include "any/base/anygeom.h"
#include "any/base/anystl.h"
using namespace AnyBase;

//
namespace AnyCGAL
{
	// tetra, hexa, octa etc hedron
	enum HedronType
	{
		HT_Unknown,
		HT_Hedron_Tetra,
		HT_Hedron_Hexa,
		HT_Hedron_Hexa_Tetra,
		HT_Hedron_Octa,
		HT_Hedron_Octa_Tetra,
		HT_Max
	};

	// struct geological basic data
	struct BuryVariable
	{
		//
		float m_bury_from_age;
		float m_bury_to_age;

		// for each simulation step
		float m_ever_thickness;
		// only for today
		float m_current_thickness;
		//
		//骨架厚度
		float m_matrix_thickness;

		//
		float m_z_middle_depth;
		float m_bury_depth; // not considering water depth
		float m_bury_middle_depth;
		// 最大埋深, the most
		float m_max_bury_depth;

		// for each simulation step
		float m_ever_max_bury_depth;
		float m_ever_max_bury_middle_depth;

		//
		BuryVariable()
		{
		}
		BuryVariable(const BuryVariable &other)
		{
			*this = other;
		}
		const BuryVariable &operator=(const BuryVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_bury_from_age = other.m_bury_from_age;
			m_bury_to_age = other.m_bury_to_age;
			m_z_middle_depth = other.m_z_middle_depth;
			m_bury_depth = other.m_bury_depth;
			m_max_bury_depth = other.m_max_bury_depth;
			m_bury_middle_depth = other.m_bury_middle_depth;
			m_ever_max_bury_middle_depth = other.m_ever_max_bury_middle_depth;
			m_ever_max_bury_depth = other.m_ever_max_bury_depth;
			m_ever_thickness = other.m_ever_thickness;
			m_current_thickness = other.m_current_thickness;
			m_matrix_thickness = other.m_matrix_thickness;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(float);//float m_bury_from_age;
			curSize += sizeof(float);//float m_bury_to_age;
			curSize += sizeof(float);//float m_ever_thickness;
			curSize += sizeof(float);//float m_current_thickness;
			curSize += sizeof(float);//float m_matrix_thickness;
			curSize += sizeof(float);//float m_z_middle_depth;
			curSize += sizeof(float);//float m_bury_depth;
			curSize += sizeof(float);//float m_bury_middle_depth;
			curSize += sizeof(float);//float m_max_bury_depth;
			curSize += sizeof(float);//float m_ever_max_bury_depth;
			curSize += sizeof(float);//float m_ever_max_bury_middle_depth;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_bury_from_age, sizeof(float));data += sizeof(float);
			memcpy(data, &m_bury_to_age, sizeof(float));data += sizeof(float);
			memcpy(data, &m_ever_thickness, sizeof(float));data += sizeof(float);
			memcpy(data, &m_current_thickness, sizeof(float));data += sizeof(float);
			memcpy(data, &m_matrix_thickness, sizeof(float));data += sizeof(float);
			memcpy(data, &m_z_middle_depth, sizeof(float));data += sizeof(float);
			memcpy(data, &m_bury_depth, sizeof(float));data += sizeof(float);
			memcpy(data, &m_bury_middle_depth, sizeof(float));data += sizeof(float);
			memcpy(data, &m_max_bury_depth, sizeof(float));data += sizeof(float);
			memcpy(data, &m_ever_max_bury_depth, sizeof(float));data += sizeof(float);
			memcpy(data, &m_ever_max_bury_middle_depth, sizeof(float));data += sizeof(float);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_bury_from_age, data, sizeof(float));data += sizeof(float);
			memcpy(&m_bury_to_age, data, sizeof(float));data += sizeof(float);
			memcpy(&m_ever_thickness, data, sizeof(float));data += sizeof(float);
			memcpy(&m_current_thickness, data, sizeof(float));data += sizeof(float);
			memcpy(&m_matrix_thickness, data, sizeof(float));data += sizeof(float);
			memcpy(&m_z_middle_depth, data, sizeof(float));data += sizeof(float);
			memcpy(&m_bury_depth, data, sizeof(float));data += sizeof(float);
			memcpy(&m_bury_middle_depth, data, sizeof(float));data += sizeof(float);
			memcpy(&m_max_bury_depth, data, sizeof(float));data += sizeof(float);
			memcpy(&m_ever_max_bury_depth, data, sizeof(float));data += sizeof(float);
			memcpy(&m_ever_max_bury_middle_depth, data, sizeof(float));data += sizeof(float);
		}
		friend std::ofstream &operator << (std::ofstream &os, BuryVariable &buryvariable)
		{
			os << "\r\n---- ---- BuryVariable variables ----- ----- ";
			os << "\r\n---- ---- ---- bury_from_age: " << buryvariable.m_bury_from_age;
			os << "\r\n---- ---- ---- bury_to_age: " << buryvariable.m_bury_to_age;
			os << "\r\n---- ---- ---- z_middle_depth: " << buryvariable.m_z_middle_depth;
			os << "\r\n---- ---- ---- bury_depth: " << buryvariable.m_bury_depth;
			os << "\r\n---- ---- ---- max_bury_depth: " << buryvariable.m_max_bury_depth;
			os << "\r\n---- ---- ---- bury_middle_depth: " << buryvariable.m_bury_middle_depth;
			os << "\r\n---- ---- ---- ever_max_bury_middle_depth: " << buryvariable.m_ever_max_bury_middle_depth;
			os << "\r\n---- ---- ---- ever_max_bury_depth: " << buryvariable.m_ever_max_bury_depth;
			os << "\r\n---- ---- ---- ever_thickness: " << buryvariable.m_ever_thickness;
			os << "\r\n---- ---- ---- current_thickness: " << buryvariable.m_current_thickness;
			os << "\r\n---- ---- ---- matrix_thickness: " << buryvariable.m_matrix_thickness;
			return os;
		}
	};

	// x,y,z,w
	struct Vertex3D : public CGeoPoint<double>, 
		public BuryVariable
	{
		// subscript
		long m_sequence_idx;			// m_initial_vertexes's subscript
		// encode
		int m_tile_code;				// octal tree code to sequence order
		
		Vertex3D() : m_sequence_idx(0), m_tile_code(0)
		{
		}
		Vertex3D(const Vertex3D &other)
		{
			*this = other;
		}
		const Vertex3D &operator=(const Vertex3D &other)
		{
			if(this == &other)
			{
				return *this;
			}
			*((CGeoPoint<double>*)this) = *((CGeoPoint<double>*)&other);
			*((BuryVariable*)this) = *((BuryVariable*)&other);
			m_sequence_idx = other.m_sequence_idx;
			m_tile_code = other.m_tile_code;
			return *this;
		}
		static bool CompareTileCode(const Vertex3D* first, const Vertex3D* second)
		{
			return first->m_tile_code < second->m_tile_code;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			//Vertex3D
			curSize += sizeof(double);//double m_x;
			curSize += sizeof(double);//double m_y;
			curSize += sizeof(double);//double m_z;
			curSize += sizeof(double);//double m_w;
			curSize += sizeof(long);//long m_sequence_idx;
			curSize += sizeof(int);//int m_tile_code
			//BuryVariable
			curSize += BuryVariable::GetSerializeDataLength();
			return curSize;
		}
		char *SerializeData(int &len)
		{
			char *data;
			len = GetSerializeDataLength();
			data = (char*)malloc(len);
			SerializeData(data);
			data -= len;
			return data;
		}
		void SerializeData(char* &data)
		{
			//Vertex3D
			memcpy(data, &m_x, sizeof(double));data += sizeof(double);
			memcpy(data, &m_y, sizeof(double));data += sizeof(double);
			memcpy(data, &m_z, sizeof(double));data += sizeof(double);
			memcpy(data, &m_w, sizeof(double));data += sizeof(double);
			memcpy(data, &m_sequence_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_tile_code, sizeof(int));data += sizeof(int);
			//BuryVariable
			BuryVariable::SerializeData(data);
		}
		void RestoreSerializeData(char* &data)
		{
			//Vertex3D
			memcpy(&m_x, data, sizeof(double));data += sizeof(double);
			memcpy(&m_y, data, sizeof(double));data += sizeof(double);
			memcpy(&m_z, data, sizeof(double));data += sizeof(double);
			memcpy(&m_w, data, sizeof(double));data += sizeof(double);
			memcpy(&m_sequence_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_tile_code, data, sizeof(int));data += sizeof(int);
			//BuryVariable
			BuryVariable::RestoreSerializeData(data);
		}
		friend std::ofstream &operator << (std::ofstream &os, Vertex3D &vertex)
		{
			os << "\r\n---- ---- Vertex3D variables ----- ----- ";
			os << "\r\n---- ---- ---- x: " << vertex.m_x;
			os << "\r\n---- ---- ---- y: " << vertex.m_y;
			os << "\r\n---- ---- ---- z: " << vertex.m_z;
			os << "\r\n---- ---- ---- w: " << vertex.m_w;
			os << "\r\n---- ---- ---- sequence_idx: " << vertex.m_sequence_idx;
			os << "\r\n---- ---- ---- tile_code: " << vertex.m_tile_code;
			os << *((BuryVariable *)(&vertex));
			return os;
		}
	};
	//
	typedef std::vector<Vertex3D*> VertexContainer;
	typedef VertexContainer::iterator VertexItr;
	typedef VertexContainer::const_iterator VertexConstItr;

	//
	struct VertexTOPO
	{
		VertexItr m_next_x;
		VertexItr m_next_y;
		VertexItr m_next_z;

		VertexTOPO()
		{
		}
		VertexTOPO(const VertexTOPO &other)
		{
			*this = other;
		}
		const VertexTOPO &operator=(const VertexTOPO &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_next_x = other.m_next_x;
			m_next_y = other.m_next_y;
			m_next_z = other.m_next_z;
			return *this;
		}
	};
	typedef std::vector<VertexTOPO*> VertexTopoContainer;
	typedef VertexTopoContainer::iterator VertexTopoItr;
	typedef VertexTopoContainer::const_iterator VertexConstTopoItr;

	// edge
	struct Edge3D
	{
		long m_idx;
		int m_vertex_idx_from;
		int m_vertex_idx_to;
		Edge3D() : m_idx(-1), m_vertex_idx_from(0), m_vertex_idx_to(0)
		{
		}
		Edge3D(const Edge3D &other)
		{
			*this = other;
		}
		const Edge3D &operator=(const Edge3D &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_idx = other.m_idx;
			m_vertex_idx_from = other.m_vertex_idx_from;
			m_vertex_idx_to = other.m_vertex_idx_to;

			return *this;
		}
	};

	// one mesh / hash map structure
	enum MeshStatus
	{
		MS_Unknown,
		MS_Normal,
		MS_Empty,
		MS_Erosion,	// z is a negative value
		MS_Invalid,
		MS_Max
	};
	struct Mesh3D
	{
		// group
		int m_layer_idx;
		int m_horizon_idx;

		// type
		unsigned char m_type;
		unsigned char m_status;

		// itself as a whole
		int m_vertex_number;
		long *m_vertex_idxes;	// default order, from bottom to top

		// TOPO definition given direction order
		Mesh3D() : m_type(HT_Unknown), m_status(MS_Normal), m_layer_idx(0), m_horizon_idx(0), \
			m_vertex_number(0), m_vertex_idxes(0)
		{
		}
		~Mesh3D()
		{
			Release();
		}
		void Release()
		{
			if(m_vertex_idxes && m_vertex_number)
				::free(m_vertex_idxes);
			m_vertex_idxes = 0;
			m_vertex_number = 0;
		}
		Mesh3D(const Mesh3D &other)
		{
			*this = other;
		}
		const Mesh3D &operator=(const Mesh3D &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_type = other.m_type;
			m_status = other.m_status;
			m_layer_idx = other.m_layer_idx;
			m_horizon_idx = other.m_horizon_idx;
			Release();
			m_vertex_number = other.m_vertex_number;
			if(m_vertex_number)
			{
				m_vertex_idxes = (long*)::malloc(sizeof(long) * m_vertex_number);
				for(int i = 0; i < m_vertex_number; i++)
					m_vertex_idxes[i] = other.m_vertex_idxes[i];
			}
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(int);//int m_layer_idx;
			curSize += sizeof(int);//int m_horizon_idx;
			curSize += sizeof(unsigned char);//unsigned char m_type;
			curSize += sizeof(unsigned char);//unsigned char m_status;
			curSize += sizeof(int);//int m_vertex_number;
			curSize += (sizeof(long) * m_vertex_number);//long *m_vertex_idxes;
			return curSize;
		}
		char *SerializeData(int &len)
		{
			char *data;
			len = GetSerializeDataLength();
			data = (char*)malloc(len);
			SerializeData(data);
			data -= len;
			return data;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_layer_idx, sizeof(int));data += sizeof(int);
			memcpy(data, &m_horizon_idx, sizeof(int));data += sizeof(int);
			memcpy(data, &m_type, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(data, &m_status, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(data, &m_vertex_number, sizeof(int));data += sizeof(int);
			memcpy(data, (char*)m_vertex_idxes, sizeof(long) * m_vertex_number);data += (sizeof(long) * m_vertex_number);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_layer_idx, data, sizeof(int));data += sizeof(int);
			memcpy(&m_horizon_idx, data, sizeof(int));data += sizeof(int);
			memcpy(&m_type, data, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(&m_status, data, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(&m_vertex_number, data, sizeof(int));data += sizeof(int);
			m_vertex_idxes = (long*)::malloc(sizeof(long) * m_vertex_number);
			memcpy(m_vertex_idxes, data, sizeof(long) * m_vertex_number);data += (sizeof(long) * m_vertex_number);
		}
		friend std::ofstream &operator << (std::ofstream &os, Mesh3D &mesh3d)
		{
			os << "\r\n---- ---- Mesh3D variables ----- ----- ";
			os << "\r\n---- ---- ---- type: " << mesh3d.m_type;
			os << "\r\n---- ---- ---- status: " << mesh3d.m_status;
			os << "\r\n---- ---- ---- layer_idx: " << mesh3d.m_layer_idx;
			os << "\r\n---- ---- ---- horizon_idx: " << mesh3d.m_horizon_idx;
			os << "\r\n---- ---- ---- vertex_number: " << mesh3d.m_vertex_number;
			for(int i = 0; i < mesh3d.m_vertex_number; i++)os << "\r\n---- ---- ---- vertex_idxes:" << i << ":" << mesh3d.m_vertex_idxes[i];
			return os;
		}
	};
	//
	typedef std::vector<Mesh3D*> MeshContainer;
	typedef MeshContainer::iterator MeshItr;
	typedef MeshContainer::const_iterator MeshConstItr;

	// horizon and layer
	enum LayerMapType
	{
		LMT_Unknown,
		LMT_Contour_Krig,		// krig contour
		LMT_Contour_Direct,	// seismic data, contour direct mode, contour inverse distance, etc
		LMT_Contour_Thickness,
		LMT_SDE_Point,
		LMT_SDE_Line,
		LMT_SDE_Poly,
		LMT_Max
	};
	enum LayerEventMode
	{
		LHEM_Unknown = 0,
		LHEM_Horizon_Current = 1,
		LHEM_Horizon_Virtual,
		LHEM_Horizon_Erosion,
		LHEM_Horizon_Hiatus,
		LHEM_Max
	};
	class Horizon3D
	{
	public:
		// take it as horizon order, smaller means deeper
		string m_horizon_name;
		CGeoRect<double> m_horizon_extent;
		int m_layer_idx;
		int m_horizon_idx;							//

		// connection marker between erosion and virtual horizons
		int m_horizon_virtual_idx;					// corresponding idx
		int m_connection_marker;

		// geological age
		double m_deposition_age_from;					// absolute 
		double m_deposition_age_delta;					// simulation delta
		int m_sub_horizons;							// simulation horizons
		int m_sub_horizontype;						//parallel type,0:top+bot,1:top,2:bot

		// sample depth range
		double m_deposition_depth_min;					// min depth
		double m_deposition_depth_max;					// max depth

		// event type or mode
		unsigned char m_geological_event;

		// mesh vertexes
		// control grid points
		int m_mesh_rows;
		int m_mesh_cols;
		std::vector<std::vector<CGeoPoint<double> > > m_mesh_areas;
		std::vector<CGeoPoint<double> > m_mesh_grids;

		std::vector<CGeoRect<int> > m_diffpart_rowcolextent;
		std::vector<int> m_diffpart_geoevent;
		std::vector<int> m_diffpart_connection_marker;

		//store the face definition, which includes lithology/LLNL...
		std::vector<std::string> m_face_definitions;

		//
		Horizon3D() : m_horizon_name(""), m_layer_idx(0), m_horizon_idx(0), m_horizon_virtual_idx(-1), m_connection_marker(-1), \
			m_deposition_age_from(ANY_NAN), m_deposition_age_delta(ANY_NAN), m_sub_horizons(0), m_sub_horizontype(0), \
			m_deposition_depth_min(ANY_NAN), m_deposition_depth_max(ANY_NAN), \
			m_geological_event(LHEM_Unknown)
		{
		}
		virtual ~Horizon3D()
		{
			Release();
		}
		void Release()
		{
			m_mesh_grids.clear();
		}
		Horizon3D(const Horizon3D &other)
		{
			*this = other;
		}
		const Horizon3D &operator=(const Horizon3D &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_horizon_name = other.m_horizon_name;
			m_horizon_extent = other.m_horizon_extent;
			m_layer_idx = other.m_layer_idx;
			m_horizon_idx = other.m_horizon_idx;

			m_horizon_virtual_idx = other.m_horizon_virtual_idx;
			m_connection_marker = other.m_connection_marker;

			m_deposition_age_from = other.m_deposition_age_from;
			m_deposition_age_delta = other.m_deposition_age_delta;
			m_sub_horizons = other.m_sub_horizons;

			m_deposition_depth_min = other.m_deposition_depth_min;
			m_deposition_depth_max = other.m_deposition_depth_max;
			m_geological_event = other.m_geological_event;

			m_mesh_rows = other.m_mesh_rows;
			m_mesh_cols = other.m_mesh_cols;
			m_mesh_areas = other.m_mesh_areas;
			m_mesh_grids = other.m_mesh_grids;

			m_diffpart_rowcolextent = other.m_diffpart_rowcolextent;
			m_diffpart_geoevent = other.m_diffpart_geoevent;
			m_diffpart_connection_marker = other.m_diffpart_connection_marker;

			m_face_definitions = other.m_face_definitions;

			return *this;
		}
		virtual void DoInterpolate(int rows, int cols, int meshtype, const CGeoRect<double> &extent){}
		virtual void DoDepthStatic(){}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += (sizeof(int) + m_horizon_name.length() * sizeof(char));//string m_horizon_name;
			curSize += sizeof(CGeoRect<double>);//CGeoRect<double> m_horizon_extent;
			curSize += sizeof(int);//int m_layer_idx;
			curSize += sizeof(int);//int m_horizon_idx;
			curSize += sizeof(int);//int m_horizon_virtual_idx;
			curSize += sizeof(int);//int m_connection_marker;
			curSize += sizeof(double);//double m_deposition_age_from;
			curSize += sizeof(double);//double m_deposition_age_delta;
			curSize += sizeof(int);//int m_sub_horizons;
			curSize += sizeof(int);//int m_sub_horizontype;
			curSize += sizeof(double);//double m_deposition_depth_min;
			curSize += sizeof(double);//double m_deposition_depth_max;
			curSize += sizeof(unsigned char);//unsigned char m_geological_event;
			curSize += sizeof(int);//int m_mesh_rows;
			curSize += sizeof(int);//int m_mesh_cols;
			curSize += sizeof(int);//std::vector<std::vector<CGeoPoint<double> > > m_mesh_areas;
			for(int i = 0; i < m_mesh_areas.size(); i++)
			{
				curSize += (sizeof(int) + m_mesh_areas[i].size() * sizeof(CGeoPoint<double>));
			}
			curSize += (sizeof(int) + m_mesh_grids.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_mesh_grids;
			curSize += (sizeof(int) + m_diffpart_rowcolextent.size() * sizeof(CGeoRect<int>));//std::vector<CGeoRect<int> > m_diffpart_rowcolextent;
			curSize += (sizeof(int) + m_diffpart_geoevent.size() * sizeof(int));//std::vector<int> m_diffpart_geoevent;
			curSize += (sizeof(int) + m_diffpart_connection_marker.size() * sizeof(int));//std::vector<int> m_diffpart_connection_marker;
			curSize += sizeof(int);//std::vector<string> m_face_definitions;
			for(int i = 0; i < m_face_definitions.size(); i++)
			{
				curSize += (sizeof(int) + m_face_definitions[i].length() * sizeof(char));
			}
			return curSize;
		}
		char *SerializeData(int &len)
		{
			char *data;
			len = GetSerializeDataLength();
			data = (char*)malloc(len);
			SerializeData(data);
			data -= len;
			return data;
		}
		void SerializeData(char* &data)
		{
			int horizon_namelength = m_horizon_name.length();
			memcpy(data, &horizon_namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_horizon_name.length(); i++)
			{
				memcpy(data, &(m_horizon_name[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_horizon_extent, sizeof(CGeoRect<double>));data += sizeof(CGeoRect<double>);
			memcpy(data, &m_layer_idx, sizeof(int));data += sizeof(int);
			memcpy(data, &m_horizon_idx, sizeof(int));data += sizeof(int);
			memcpy(data, &m_horizon_virtual_idx, sizeof(int));data += sizeof(int);
			memcpy(data, &m_connection_marker, sizeof(int));data += sizeof(int);
			memcpy(data, &m_deposition_age_from, sizeof(double));data += sizeof(double);
			memcpy(data, &m_deposition_age_delta, sizeof(double));data += sizeof(double);
			memcpy(data, &m_sub_horizons, sizeof(int));data += sizeof(int);
			memcpy(data, &m_sub_horizontype, sizeof(int));data += sizeof(int);
			memcpy(data, &m_deposition_depth_min, sizeof(double));data += sizeof(double);
			memcpy(data, &m_deposition_depth_max, sizeof(double));data += sizeof(double);
			memcpy(data, &m_geological_event, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(data, &m_mesh_rows, sizeof(int));data += sizeof(int);
			memcpy(data, &m_mesh_cols, sizeof(int));data += sizeof(int);
			int mesh_areassize = m_mesh_areas.size();
			memcpy(data, &mesh_areassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < mesh_areassize; i++)
			{
				int submesh_areassize = m_mesh_areas[i].size();
				memcpy(data, &submesh_areassize, sizeof(int));data += sizeof(int);
				for(int j = 0; j < submesh_areassize; j++)
				{
					memcpy(data, &(m_mesh_areas[i][j]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				}
			}
			int mesh_gridssize = m_mesh_grids.size();
			memcpy(data, &mesh_gridssize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < mesh_gridssize; i++)
			{
				memcpy(data, &(m_mesh_grids[i]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
			int diffpart_rowcolextentsize = m_diffpart_rowcolextent.size();
			memcpy(data, &diffpart_rowcolextentsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < diffpart_rowcolextentsize; i++)
			{
				memcpy(data, &(m_diffpart_rowcolextent[i]), sizeof(CGeoRect<int>));data += sizeof(CGeoRect<int>);
			}
			int diffpart_geoeventsize = m_diffpart_geoevent.size();
			memcpy(data, &diffpart_geoeventsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < diffpart_geoeventsize; i++)
			{
				memcpy(data, &(m_diffpart_geoevent[i]), sizeof(int));data += sizeof(int);
			}
			int diffpart_connection_markersize = m_diffpart_connection_marker.size();
			memcpy(data, &diffpart_connection_markersize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < diffpart_connection_markersize; i++)
			{
				memcpy(data, &(m_diffpart_connection_marker[i]), sizeof(int));data += sizeof(int);
			}
			int face_definitions_size = m_face_definitions.size();
			memcpy(data, &face_definitions_size, sizeof(int));data += sizeof(int);
			for(int i = 0; i < face_definitions_size; i++)
			{
				int face_definition_length = m_face_definitions[i].length();
				memcpy(data, &face_definition_length, sizeof(int));data += sizeof(int);
				for(int j = 0; j < m_face_definitions[i].length(); j++)
				{
					memcpy(data, &(m_face_definitions[i][j]), sizeof(char));data += sizeof(char);
				}
			}
		}
		void RestoreSerializeData(char* &data)
		{
			int horizon_namelength;
			memcpy(&horizon_namelength, data, sizeof(int));data += sizeof(int);
			m_horizon_name = "";
			for(int i = 0; i < horizon_namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_horizon_name += temp;
			}
			memcpy(&m_horizon_extent, data, sizeof(CGeoRect<double>));data += sizeof(CGeoRect<double>);
			memcpy(&m_layer_idx, data, sizeof(int));data += sizeof(int);
			memcpy(&m_horizon_idx, data, sizeof(int));data += sizeof(int);
			memcpy(&m_horizon_virtual_idx, data, sizeof(int));data += sizeof(int);
			memcpy(&m_connection_marker, data, sizeof(int));data += sizeof(int);
			memcpy(&m_deposition_age_from, data, sizeof(double));data += sizeof(double);
			memcpy(&m_deposition_age_delta, data, sizeof(double));data += sizeof(double);
			memcpy(&m_sub_horizons, data, sizeof(int));data += sizeof(int);
			memcpy(&m_sub_horizontype, data, sizeof(int));data += sizeof(int);
			memcpy(&m_deposition_depth_min, data, sizeof(double));data += sizeof(double);
			memcpy(&m_deposition_depth_max, data, sizeof(double));data += sizeof(double);
			memcpy(&m_geological_event, data, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(&m_mesh_rows, data, sizeof(int));data += sizeof(int);
			memcpy(&m_mesh_cols, data, sizeof(int));data += sizeof(int);
			int mesh_areassize;
			memcpy(&mesh_areassize, data, sizeof(int));data += sizeof(int);
			m_mesh_areas.resize(mesh_areassize);
			for(int i = 0; i < mesh_areassize; i++)
			{
				int submesh_areassize;
				memcpy(&submesh_areassize, data, sizeof(int));data += sizeof(int);
				m_mesh_areas[i].resize(submesh_areassize);
				for(int j = 0; j < submesh_areassize; j++)
				{
					memcpy(&(m_mesh_areas[i][j]), data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				}
			}
			int mesh_gridssize;
			memcpy(&mesh_gridssize, data, sizeof(int));data += sizeof(int);
			m_mesh_grids.resize(mesh_gridssize);
			for(int i = 0; i < mesh_gridssize; i++)
			{
				memcpy(&(m_mesh_grids[i]), data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
			int diffpart_rowcolextentsize;
			memcpy(&diffpart_rowcolextentsize, data, sizeof(int));data += sizeof(int);
			m_diffpart_rowcolextent.resize(diffpart_rowcolextentsize);
			for(int i = 0; i < diffpart_rowcolextentsize; i++)
			{
				memcpy(&(m_diffpart_rowcolextent[i]), data, sizeof(CGeoRect<int>));data += sizeof(CGeoRect<int>);
			}
			int diffpart_geoeventsize;
			memcpy(&diffpart_geoeventsize, data, sizeof(int));data += sizeof(int);
			m_diffpart_geoevent.resize(diffpart_geoeventsize);
			for(int i = 0; i < diffpart_geoeventsize; i++)
			{
				memcpy(&(m_diffpart_geoevent[i]), data, sizeof(int));data += sizeof(int);
			}
			int diffpart_connection_markersize;
			memcpy(&diffpart_connection_markersize, data, sizeof(int));data += sizeof(int);
			m_diffpart_connection_marker.resize(diffpart_connection_markersize);
			for(int i = 0; i < diffpart_connection_markersize; i++)
			{
				memcpy(&(m_diffpart_connection_marker[i]), data, sizeof(int));data += sizeof(int);
			}
			int face_definitions_size;
			memcpy(&face_definitions_size, data, sizeof(int));data += sizeof(int);
			m_face_definitions.resize(face_definitions_size);
			for(int i = 0; i < face_definitions_size; i++)
			{
				int face_definition_length;
				memcpy(&face_definition_length, data, sizeof(int));data += sizeof(int);
				m_face_definitions[i] = "";
				for(int j = 0; j < face_definition_length; j++)
				{
					char temp;
					memcpy(&temp, data, sizeof(char));data += sizeof(char);
					m_face_definitions[i] += temp;
				}
			}
		}
	};

	class KrigHorizon3D : public Horizon3D
	{
	public:
		// samples
		int m_number;
		CGeoPoint<double> *m_samples;
		// krig settings
		unsigned char m_variance_model_type;
		double m_sill;
		double m_range;
		double m_nugget;
		KrigHorizon3D() : m_number(0), m_samples(0), m_variance_model_type(0), m_sill(ANY_NAN), m_range(ANY_NAN), m_nugget(ANY_NAN)
		{
		}
		KrigHorizon3D(const KrigHorizon3D &other)
		{
			*this = other;
		}
		const KrigHorizon3D &operator=(const KrigHorizon3D &other)
		{
			if(this == &other)
			{
				return *this;
			}
			*((Horizon3D*)this) = *((Horizon3D*)&other);
			m_number = other.m_number;
			m_samples = other.m_samples;
			m_variance_model_type = other.m_variance_model_type;
			m_sill = other.m_sill;
			m_range = other.m_range;
			m_nugget = other.m_nugget;
			return *this;
		}
		void DoInterpolate(int rows, int cols, int meshtype, const CGeoRect<double> &extent)
		{
			Release();
			m_mesh_rows = rows;
			m_mesh_cols = cols;
			std::vector<CGeoPoint<double> > samples;
			for(int i = 0; i < m_number; i++)
			{
				CGeoPoint<double> sample(m_samples[i].m_x, m_samples[i].m_y, m_samples[i].m_z);
				sample.m_w = m_samples[i].m_w;
				samples.push_back(sample);
			}
			CAnyKrigSimulator simulator;
			simulator.SetSamples(samples);
			if(ISNAN(m_sill) || ISNAN(m_nugget) || ISNAN(m_range))
			{
				std::vector<CGeoPoint<double> > variances;
				simulator.GetSampleVariance(variances);
			}
			else
			{
				simulator.Fit_SetVariogramParameter(m_variance_model_type, m_sill, m_range, m_nugget);//simulator.SetVariogramModel(m_variance_model_type, m_sill, m_range, m_nugget);
			}
			for(int i = 0; i < rows; i++)
			{
				for(int j = 0; j < cols; j++)
				{
					CGeoPoint<double> gridpoint;
					gridpoint.m_x = extent.m_minX + j * extent.Width() / (cols - 1);
					gridpoint.m_y = extent.m_minY + i * extent.Height() / (rows - 1);
					m_mesh_grids.push_back(gridpoint);
				}
			}
			simulator.KrigDirect_Threaded(m_mesh_grids);
		}
		void DoDepthStatic()
		{
			m_deposition_depth_min = 0x7FFFFFFF;
			m_deposition_depth_max = -0x7FFFFFFF;
			for(int i = 0; i < m_number; i++)
			{
				if(ISNAN(m_samples[i].m_z))
					continue;
				m_deposition_depth_min = m_deposition_depth_min > m_samples[i].m_z ? m_samples[i].m_z : m_deposition_depth_min;
				m_deposition_depth_max = m_deposition_depth_max < m_samples[i].m_z ? m_samples[i].m_z : m_deposition_depth_max;
			}
			if(m_number == 0)
			{
				for(int i = 0; i < m_mesh_grids.size(); i++)
				{
					if(ISNAN(m_mesh_grids[i].m_z))
						continue;
					m_deposition_depth_min = m_deposition_depth_min > m_mesh_grids[i].m_z ? m_mesh_grids[i].m_z : m_deposition_depth_min;
					m_deposition_depth_max = m_deposition_depth_max < m_mesh_grids[i].m_z ? m_mesh_grids[i].m_z : m_deposition_depth_max;
				}
			}
		}
	};
	//
	class SeismicHorizon3D : public Horizon3D	// direct mode
	{
	public:
		int m_rows;
		int m_cols;
		// samples
		CGeoPoint<double> *m_samples;
		SeismicHorizon3D() : m_rows(0), m_cols(0), m_samples(0)
		{
		}
		SeismicHorizon3D(const SeismicHorizon3D &other)
		{
			*this = other;
		}
		const SeismicHorizon3D &operator=(const SeismicHorizon3D &other)
		{
			if(this == &other)
			{
				return *this;
			}
			*((Horizon3D*)this) = *((Horizon3D*)&other);
			m_rows = other.m_rows;
			m_cols = other.m_cols;
			m_samples = other.m_samples;
			return *this;
		}
		void DoInterpolate(int rows, int cols, int meshtype, const CGeoRect<double> &extent)
		{
			Release();
			m_mesh_rows = rows;
			m_mesh_cols = cols;
			int rowmin = -1, rowmax = -1, colmin = -1, colmax = -1;
			if(ISNAN(extent.m_minX) || ISNAN(extent.m_maxX) || ISNAN(extent.m_minY) || ISNAN(extent.m_maxY))
			{
				rowmin = 0;
				rowmax = m_rows - 1;
				colmin = 0;
				colmax = m_cols - 1;
			}
			else
			{
				for(int i = 0; i < m_rows; i++)
				{
					for(int j = 0; j < m_cols; j++)
					{
						CGeoPoint<double> &curpt = m_samples[i * m_cols + j];
						if(curpt.m_x < extent.m_minX || curpt.m_x > extent.m_maxX || curpt.m_y < extent.m_minY || curpt.m_y > extent.m_maxY)
							continue;
						if(rowmin == -1 || rowmax == -1 || colmin == -1 || colmax == -1)
						{
							rowmin = rowmax = i;
							colmin = colmax = j;
						}
						else
						{
							if(rowmin > i)
								rowmin = i;
							if(rowmax < i)
								rowmax = i;
							if(colmin > j)
								colmin = j;
							if(colmax < j)
								colmax = j;
						}
					}
				}
			}
			double rowsize = rowmax - rowmin;
			double colsize = colmax - colmin;
			if(rowsize == 0 || colsize == 0)
				return;
			CGeoPoint<double> vectora(m_samples[(m_rows - 1) * m_cols].m_x - m_samples[0].m_x, m_samples[(m_rows - 1) * m_cols].m_y - m_samples[0].m_y);
			CGeoPoint<double> vectorb(m_samples[m_cols - 1].m_x - m_samples[0].m_x, m_samples[m_cols - 1].m_y - m_samples[0].m_y);
			CGeoPoint<double> cellvectora(vectora.m_x / (m_rows - 1), vectora.m_y / (m_rows - 1));
			CGeoPoint<double> cellvectorb(vectorb.m_x / (m_cols - 1), vectorb.m_y / (m_cols - 1));
			CGeoPoint<double> hexvectora(cellvectora.m_x * 2 / 3 * rowsize / (rows - 1), cellvectora.m_y * 2 / 3 * rowsize / (rows - 1));
			CGeoPoint<double> hexvectorb(cellvectorb.m_x / 2 * colsize / (cols - 1), cellvectorb.m_y / 2 * colsize / (cols - 1));
			std::vector<CGeoRect<int> > new_diffpart_rowcolextent;
			std::vector<int> new_diffpart_geoevent;
			std::vector<int> new_diffpart_connection_marker;
			for(int i = 0; i < m_diffpart_rowcolextent.size(); i++)
			{
				CGeoRect<int> currect = m_diffpart_rowcolextent[i];
				int geoevent = m_diffpart_geoevent[i];
				int connection_marker = m_diffpart_connection_marker[i];
				currect.m_minX = max(rowmin, currect.m_minX);
				currect.m_maxX = min(rowmax, currect.m_maxX);
				currect.m_minY = max(colmin, currect.m_minY);
				currect.m_maxY = min(colmax, currect.m_maxY);
				if(currect.Width() < 1 || currect.Height() < 1)
					continue;
				currect.m_minX = (rows - 1) * (currect.m_minX - rowmin) / rowsize;
				currect.m_maxX = (rows - 1) * (currect.m_maxX - rowmin) / rowsize;
				currect.m_minY = (cols - 1) * (currect.m_minY - colmin) / colsize;
				currect.m_maxY = (cols - 1) * (currect.m_maxY - colmin) / colsize;
				if(currect.Width() < 1 || currect.Height() < 1)
					continue;
				while(true)
				{
					bool hasintersect = false;
					for(int j = 0; j < new_diffpart_rowcolextent.size(); j++)
					{
						CGeoRect<int> comparerect = new_diffpart_rowcolextent[j];
						if(currect.IsIntersect(comparerect))
						{
							hasintersect = true;
							if(currect.m_minX == comparerect.m_maxX)
								currect.m_minX++;
							else if(currect.m_maxX == comparerect.m_minX)
								currect.m_maxX--;
							else if(currect.m_minY == comparerect.m_maxY)
								currect.m_minY++;
							else if(currect.m_maxY == comparerect.m_minY)
								currect.m_maxY--;
							break;
						}
					}
					if(!hasintersect || currect.Width() < 1 || currect.Height() < 1)
						break;
				}
				new_diffpart_rowcolextent.push_back(currect);
				new_diffpart_geoevent.push_back(geoevent);
				new_diffpart_connection_marker.push_back(connection_marker);
			}
			m_diffpart_rowcolextent = new_diffpart_rowcolextent;
			m_diffpart_geoevent = new_diffpart_geoevent;
			m_diffpart_connection_marker = new_diffpart_connection_marker;
			std::vector<string> new_face_definitions;
			for(int i = 0; i < rows; i++)
			{
				for(int j = 0; j < cols; j++)
				{
					double currowd = (double)rowmin + (double)rowsize * i / (rows - 1);
					double curcold = (double)colmin + (double)colsize * j / (cols - 1);
					int currow = currowd;
					int curcol = curcold;
					int nextrow = currow + 1;
					int nextcol = curcol + 1;
					if(nextrow >= m_rows)
						nextrow = m_rows - 1;
					if(nextcol >= m_cols)
						nextcol = m_cols - 1;
					double u = currowd - currow;
					double v = curcold - curcol;
					CGeoPoint<double> meshpt;
					meshpt.m_x = m_samples[0].m_x + cellvectora.m_x * currowd + cellvectorb.m_x * curcold;
					meshpt.m_y = m_samples[0].m_y + cellvectora.m_y * currowd + cellvectorb.m_y * curcold;
					if(currow == nextrow)
					{
						if(curcol == nextcol)
						{
							meshpt.m_z = m_samples[currow * m_cols + curcol].m_z;
							meshpt.m_w = m_samples[currow * m_cols + curcol].m_w;
						}
						else
						{
							meshpt.m_z = v * m_samples[currow * m_cols + nextcol].m_z + \
								(1 - v) * m_samples[currow * m_cols + curcol].m_z;
							meshpt.m_w = v * v * m_samples[currow * m_cols + nextcol].m_w + \
								(1 - v) * (1 - v) * m_samples[currow * m_cols + curcol].m_w;
							meshpt.m_w = meshpt.m_w / (v * v + (1 - v) * (1 - v));
						}
					}
					else
					{
						if(curcol == nextcol)
						{
							meshpt.m_z = u * m_samples[nextrow * m_cols + curcol].m_z + \
								(1 - u) * m_samples[currow * m_cols + curcol].m_z;
							meshpt.m_w = u * u * m_samples[nextrow * m_cols + curcol].m_w + \
								(1 - u) * (1 - u) * m_samples[currow * m_cols + curcol].m_w;
							meshpt.m_w = meshpt.m_w / (u * u + (1 - u) * (1 - u));
						}
						else
						{
							meshpt.m_z = u * v * m_samples[nextrow * m_cols + nextcol].m_z + \
								(1 - u) * v * m_samples[currow * m_cols + nextcol].m_z + \
								u * (1 - v) * m_samples[nextrow * m_cols + curcol].m_z + \
								(1 - u) * (1 - v) * m_samples[currow * m_cols + curcol].m_z;
							meshpt.m_w = u * u * v * v * m_samples[nextrow * m_cols + nextcol].m_w + \
								(1 - u) * (1 - u) * v * v * m_samples[currow * m_cols + nextcol].m_w + \
								u * u * (1 - v) * (1 - v) * m_samples[nextrow * m_cols + curcol].m_w + \
								(1 - u) * (1 - u) * (1 - v) * (1 - v) * m_samples[currow * m_cols + curcol].m_w;
							meshpt.m_w = meshpt.m_w / (u * u * v * v + (1 - u) * (1 - u) * v * v + u * u * (1 - v) * (1 - v) + (1 - u) * (1 - u) * (1 - v) * (1 - v));
						}
					}
					meshpt.m_w = m_samples[currow * m_cols + curcol].m_w;
					if(m_face_definitions.size() == m_rows * m_cols)
					{
						new_face_definitions.push_back(m_face_definitions[currow * m_cols + curcol]);
					}
					if(meshtype == HT_Hedron_Hexa || meshtype == HT_Hedron_Hexa_Tetra)
					{
						m_mesh_grids.push_back(meshpt);
					}
					else if(meshtype ==  HT_Hedron_Octa || meshtype == HT_Hedron_Octa_Tetra)
					{
						CGeoPoint<double> curhexcenter = meshpt;
						if(i % 2 != 0)
						{
							curhexcenter.m_x = curhexcenter.m_x + hexvectorb.m_x;
							curhexcenter.m_y = curhexcenter.m_y + hexvectorb.m_y;
						}
						CGeoPoint<double> pt = curhexcenter;
						m_mesh_grids.push_back(pt);
						pt.m_x = curhexcenter.m_x + hexvectora.m_x;
						pt.m_y = curhexcenter.m_y + hexvectora.m_y;
						m_mesh_grids.push_back(pt);
						pt.m_x = curhexcenter.m_x + hexvectorb.m_x + hexvectora.m_x / 2;
						pt.m_y = curhexcenter.m_y + hexvectorb.m_y + hexvectora.m_y / 2;
						m_mesh_grids.push_back(pt);
						pt.m_x = curhexcenter.m_x + hexvectorb.m_x - hexvectora.m_x / 2;
						pt.m_y = curhexcenter.m_y + hexvectorb.m_y - hexvectora.m_y / 2;
						m_mesh_grids.push_back(pt);
						pt.m_x = curhexcenter.m_x - hexvectora.m_x;
						pt.m_y = curhexcenter.m_y - hexvectora.m_y;
						m_mesh_grids.push_back(pt);
						pt.m_x = curhexcenter.m_x - hexvectorb.m_x - hexvectora.m_x / 2;
						pt.m_y = curhexcenter.m_y - hexvectorb.m_y - hexvectora.m_y / 2;
						m_mesh_grids.push_back(pt);
						pt.m_x = curhexcenter.m_x - hexvectorb.m_x + hexvectora.m_x / 2;
						pt.m_y = curhexcenter.m_y - hexvectorb.m_y + hexvectora.m_y / 2;
						m_mesh_grids.push_back(pt);
					}
				}
			}
			m_face_definitions = new_face_definitions;
			if(meshtype ==  HT_Hedron_Octa || meshtype == HT_Hedron_Octa_Tetra)
			{
				for(int i = 0; i < rows; i++)
				{
					for(int j = 0; j < cols; j++)
					{
						double curz = m_mesh_grids[(i * cols + j) * 7].m_z;
						if(ISNAN(curz))
							continue;
						double zdisa = 0, zdisb = 0;
						if(i < rows - 1)
							zdisa = m_mesh_grids[((i + 1) * cols + j) * 7].m_z - curz;
						else if(i > 0)
							zdisa = curz - m_mesh_grids[((i - 1) * cols + j) * 7].m_z;
						if(j < cols - 1)
							zdisb = m_mesh_grids[(i * cols + j + 1) * 7].m_z - curz;
						else if(j > 0)
							zdisb = curz - m_mesh_grids[(i * cols + j - 1) * 7].m_z;
						if(ISNAN(zdisa) || ISNAN(zdisb))
							continue;
						zdisa = zdisa * 2 / 3;
						zdisb = zdisb / 2;
						m_mesh_grids[(i * cols + j) * 7 + 1].m_z = m_mesh_grids[(i * cols + j) * 7 + 1].m_z + zdisa;
						m_mesh_grids[(i * cols + j) * 7 + 2].m_z = m_mesh_grids[(i * cols + j) * 7 + 2].m_z + zdisb + zdisa / 2;
						m_mesh_grids[(i * cols + j) * 7 + 3].m_z = m_mesh_grids[(i * cols + j) * 7 + 3].m_z + zdisb - zdisa / 2;
						m_mesh_grids[(i * cols + j) * 7 + 4].m_z = m_mesh_grids[(i * cols + j) * 7 + 4].m_z - zdisa;
						m_mesh_grids[(i * cols + j) * 7 + 5].m_z = m_mesh_grids[(i * cols + j) * 7 + 5].m_z - zdisb - zdisa / 2;
						m_mesh_grids[(i * cols + j) * 7 + 6].m_z = m_mesh_grids[(i * cols + j) * 7 + 6].m_z - zdisb + zdisa / 2;
					}
				}
			}
		}
		void DoDepthStatic()
		{
			m_deposition_depth_min = 0x7FFFFFFF;
			m_deposition_depth_max = -0x7FFFFFFF;
			for(int i = 0; i < m_rows * m_cols; i++)
			{
				if(ISNAN(m_samples[i].m_z))
					continue;
				m_deposition_depth_min = m_deposition_depth_min > m_samples[i].m_z ? m_samples[i].m_z : m_deposition_depth_min;
				m_deposition_depth_max = m_deposition_depth_max < m_samples[i].m_z ? m_samples[i].m_z : m_deposition_depth_max;
			}
			if(m_rows == 0 || m_cols == 0)
			{
				for(int i = 0; i < m_mesh_grids.size(); i++)
				{
					if(ISNAN(m_mesh_grids[i].m_z))
						continue;
					m_deposition_depth_min = m_deposition_depth_min > m_mesh_grids[i].m_z ? m_mesh_grids[i].m_z : m_deposition_depth_min;
					m_deposition_depth_max = m_deposition_depth_max < m_mesh_grids[i].m_z ? m_mesh_grids[i].m_z : m_deposition_depth_max;
				}
			}
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(int);//int m_rows;
			curSize += sizeof(int);//int m_cols;
			curSize += (m_rows * m_cols * sizeof(CGeoPoint<double>));//CGeoPoint<double> *m_samples;
			// Horizon3D
			curSize += Horizon3D::GetSerializeDataLength();
			return curSize;
		}
		char *SerializeData(int &len)
		{
			char *data;
			len = GetSerializeDataLength();
			data = (char*)malloc(len);
			SerializeData(data);
			data -= len;
			return data;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_rows, sizeof(int));data += sizeof(int);
			memcpy(data, &m_cols, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_rows * m_cols; i++)
				memcpy(data, &(m_samples[i]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			// Horizon3D
			Horizon3D::SerializeData(data);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_rows, data, sizeof(int));data += sizeof(int);
			memcpy(&m_cols, data, sizeof(int));data += sizeof(int);
			m_samples = (CGeoPoint<double>*)::malloc(m_rows * m_cols * sizeof(CGeoPoint<double>));
			for(int i = 0; i < m_rows * m_cols; i++)
				memcpy(&(m_samples[i]), data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			// Horizon3D
			Horizon3D::RestoreSerializeData(data);
		}
	};
	//
	class SDEHorizon3D : public Horizon3D
	{
	public:
		SDEHorizon3D()
		{
		}
		SDEHorizon3D(const SDEHorizon3D &other)
		{
			*this = other;
		}
		const SDEHorizon3D &operator=(const SDEHorizon3D &other)
		{
			if(this == &other)
			{
				return *this;
			}
			*((Horizon3D*)this) = *((Horizon3D*)&other);
			return *this;
		}
		void DoInterpolate(int rows, int cols, int meshtype, const CGeoRect<double> &extent)
		{
			Release();
			m_mesh_rows = rows;
			m_mesh_cols = cols;
			// to get its previous horizon then add current interpolation result
		}
		void DoDepthStatic()
		{
			// do nothing
		}
	};
	typedef std::vector<Horizon3D*> HorizonVector;
	
	//
	class CompositeHorizon3D : public Horizon3D
	{
		void DoInterpolate(int rows, int cols, int meshtype, const CGeoRect<double> &extent)
		{
			Release();
			m_mesh_rows = rows;
			m_mesh_cols = cols;
			// to get its previous horizon then add current interpolation result
			for(int offset = 0; offset < m_children_horizons.size(); offset++)
			{
				SeismicHorizon3D* curhorizon = (SeismicHorizon3D*)(m_children_horizons[offset]);
				curhorizon->Release();
				int rowmin = -1, rowmax = -1, colmin = -1, colmax = -1;
				CGeoRect<double> filterextent(ANY_NAN, ANY_NAN, ANY_NAN, ANY_NAN);
				for(int i = 0; i < curhorizon->m_rows; i++)
				{
					for(int j = 0; j < curhorizon->m_cols; j++)
					{
						CGeoPoint<double> &curpt = curhorizon->m_samples[i * curhorizon->m_cols + j];
						if(curpt.m_x < extent.m_minX || curpt.m_x > extent.m_maxX || curpt.m_y < extent.m_minY || curpt.m_y > extent.m_maxY)
							continue;
						if(rowmin == -1 || rowmax == -1 || colmin == -1 || colmax == -1)
						{
							rowmin = rowmax = i;
							colmin = colmax = j;
							filterextent.m_maxX = filterextent.m_minX = curpt.m_x;
							filterextent.m_maxY = filterextent.m_minY = curpt.m_y;
						}
						else
						{
							if(rowmin > i)
								rowmin = i;
							if(rowmax < i)
								rowmax = i;
							if(colmin > j)
								colmin = j;
							if(colmax < j)
								colmax = j;
							if(filterextent.m_minX > curpt.m_x)
								filterextent.m_minX = curpt.m_x;
							if(filterextent.m_maxX < curpt.m_x)
								filterextent.m_maxX = curpt.m_x;
							if(filterextent.m_minY > curpt.m_y)
								filterextent.m_minY = curpt.m_y;
							if(filterextent.m_maxY < curpt.m_y)
								filterextent.m_maxY = curpt.m_y;
						}
					}
				}
				double rowsize = rowmax - rowmin;
				double colsize = colmax - colmin;
				if(rowsize == 0 || colsize == 0)
				{
					curhorizon->m_mesh_cols = curhorizon->m_mesh_rows = 0;
					continue;
				}
				curhorizon->m_mesh_rows = rows * filterextent.Height() / extent.Height();
				curhorizon->m_mesh_cols = cols * filterextent.Width() / extent.Width();
				if(curhorizon->m_mesh_rows < 2 || curhorizon->m_mesh_cols < 2)
				{
					curhorizon->m_mesh_cols = curhorizon->m_mesh_rows = 0;
					continue;
				}
				CGeoPoint<double> vectora(curhorizon->m_samples[(curhorizon->m_rows - 1) * curhorizon->m_cols].m_x - curhorizon->m_samples[0].m_x, curhorizon->m_samples[(curhorizon->m_rows - 1) * curhorizon->m_cols].m_y - curhorizon->m_samples[0].m_y);
				CGeoPoint<double> vectorb(curhorizon->m_samples[curhorizon->m_cols - 1].m_x - curhorizon->m_samples[0].m_x, curhorizon->m_samples[curhorizon->m_cols - 1].m_y - curhorizon->m_samples[0].m_y);
				CGeoPoint<double> cellvectora(vectora.m_x / (curhorizon->m_rows - 1), vectora.m_y / (curhorizon->m_rows - 1));
				CGeoPoint<double> cellvectorb(vectorb.m_x / (curhorizon->m_cols - 1), vectorb.m_y / (curhorizon->m_cols - 1));
				CGeoPoint<double> hexvectora(cellvectora.m_x * 2 / 3 * rowsize / (curhorizon->m_mesh_rows - 1), cellvectora.m_y * 2 / 3 * rowsize / (curhorizon->m_mesh_rows - 1));
				CGeoPoint<double> hexvectorb(cellvectorb.m_x / 2 * colsize / (curhorizon->m_mesh_cols - 1), cellvectorb.m_y / 2 * colsize / (curhorizon->m_mesh_cols - 1));
				for(int i = 0; i < curhorizon->m_mesh_rows; i++)
				{
					for(int j = 0; j < curhorizon->m_mesh_cols; j++)
					{
						double currowd = (double)rowmin + (double)rowsize * i / (curhorizon->m_mesh_rows - 1);
						double curcold = (double)colmin + (double)colsize * j / (curhorizon->m_mesh_cols - 1);
						int currow = currowd;
						int curcol = curcold;
						int nextrow = currow + 1;
						int nextcol = curcol + 1;
						if(nextrow >= curhorizon->m_rows)
							nextrow = curhorizon->m_rows - 1;
						if(nextcol >= curhorizon->m_cols)
							nextcol = curhorizon->m_cols - 1;
						double u = currowd - currow;
						double v = curcold - curcol;
						CGeoPoint<double> meshpt;
						meshpt.m_x = curhorizon->m_samples[0].m_x + cellvectora.m_x * currowd + cellvectorb.m_x * curcold;
						meshpt.m_y = curhorizon->m_samples[0].m_y + cellvectora.m_y * currowd + cellvectorb.m_y * curcold;
						if(currow == nextrow)
						{
							if(curcol == nextcol)
							{
								meshpt.m_z = curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_z;
								meshpt.m_w = curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_w;
							}
							else
							{
								meshpt.m_z = v * curhorizon->m_samples[currow * curhorizon->m_cols + nextcol].m_z + \
									(1 - v) * curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_z;
								meshpt.m_w = v * v * curhorizon->m_samples[currow * curhorizon->m_cols + nextcol].m_w + \
									(1 - v) * (1 - v) * curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_w;
								meshpt.m_w = meshpt.m_w / (v * v + (1 - v) * (1 - v));
							}
						}
						else
						{
							if(curcol == nextcol)
							{
								meshpt.m_z = u * curhorizon->m_samples[nextrow * curhorizon->m_cols + curcol].m_z + \
									(1 - u) * curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_z;
								meshpt.m_w = u * u * curhorizon->m_samples[nextrow * curhorizon->m_cols + curcol].m_w + \
									(1 - u) * (1 - u) * curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_w;
								meshpt.m_w = meshpt.m_w / (u * u + (1 - u) * (1 - u));
							}
							else
							{
								meshpt.m_z = u * v * curhorizon->m_samples[nextrow * curhorizon->m_cols + nextcol].m_z + \
									(1 - u) * v * curhorizon->m_samples[currow * curhorizon->m_cols + nextcol].m_z + \
									u * (1 - v) * curhorizon->m_samples[nextrow * curhorizon->m_cols + curcol].m_z + \
									(1 - u) * (1 - v) * curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_z;
								meshpt.m_w = u * u * v * v * curhorizon->m_samples[nextrow * curhorizon->m_cols + nextcol].m_w + \
									(1 - u) * (1 - u) * v * v * curhorizon->m_samples[currow * curhorizon->m_cols + nextcol].m_w + \
									u * u * (1 - v) * (1 - v) * curhorizon->m_samples[nextrow * curhorizon->m_cols + curcol].m_w + \
									(1 - u) * (1 - u) * (1 - v) * (1 - v) * curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_w;
								meshpt.m_w = meshpt.m_w / (u * u * v * v + (1 - u) * (1 - u) * v * v + u * u * (1 - v) * (1 - v) + (1 - u) * (1 - u) * (1 - v) * (1 - v));
							}
						}
						meshpt.m_w = curhorizon->m_samples[currow * curhorizon->m_cols + curcol].m_w;
						if(meshtype == HT_Hedron_Hexa || meshtype == HT_Hedron_Hexa_Tetra)
						{
							curhorizon->m_mesh_grids.push_back(meshpt);
						}
						else if(meshtype ==  HT_Hedron_Octa || meshtype == HT_Hedron_Octa_Tetra)
						{
							CGeoPoint<double> curhexcenter = meshpt;
							if(i % 2 != 0)
							{
								curhexcenter.m_x = curhexcenter.m_x + hexvectorb.m_x;
								curhexcenter.m_y = curhexcenter.m_y + hexvectorb.m_y;
							}
							CGeoPoint<double> pt = curhexcenter;
							curhorizon->m_mesh_grids.push_back(pt);
							pt.m_x = curhexcenter.m_x + hexvectora.m_x;
							pt.m_y = curhexcenter.m_y + hexvectora.m_y;
							curhorizon->m_mesh_grids.push_back(pt);
							pt.m_x = curhexcenter.m_x + hexvectorb.m_x + hexvectora.m_x / 2;
							pt.m_y = curhexcenter.m_y + hexvectorb.m_y + hexvectora.m_y / 2;
							curhorizon->m_mesh_grids.push_back(pt);
							pt.m_x = curhexcenter.m_x + hexvectorb.m_x - hexvectora.m_x / 2;
							pt.m_y = curhexcenter.m_y + hexvectorb.m_y - hexvectora.m_y / 2;
							curhorizon->m_mesh_grids.push_back(pt);
							pt.m_x = curhexcenter.m_x - hexvectora.m_x;
							pt.m_y = curhexcenter.m_y - hexvectora.m_y;
							curhorizon->m_mesh_grids.push_back(pt);
							pt.m_x = curhexcenter.m_x - hexvectorb.m_x - hexvectora.m_x / 2;
							pt.m_y = curhexcenter.m_y - hexvectorb.m_y - hexvectora.m_y / 2;
							curhorizon->m_mesh_grids.push_back(pt);
							pt.m_x = curhexcenter.m_x - hexvectorb.m_x + hexvectora.m_x / 2;
							pt.m_y = curhexcenter.m_y - hexvectorb.m_y + hexvectora.m_y / 2;
							curhorizon->m_mesh_grids.push_back(pt);
						}
					}
				}
				if(meshtype ==  HT_Hedron_Octa || meshtype == HT_Hedron_Octa_Tetra)
				{
					for(int i = 0; i < curhorizon->m_mesh_rows; i++)
					{
						for(int j = 0; j < curhorizon->m_mesh_cols; j++)
						{
							double curz =  curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7].m_z;
							if(ISNAN(curz))
								continue;
							double zdisa = 0, zdisb = 0;
							if(i < curhorizon->m_mesh_rows - 1)
								zdisa = curhorizon->m_mesh_grids[((i + 1) * curhorizon->m_mesh_cols + j) * 7].m_z - curz;
							else if(i > 0)
								zdisa = curz - curhorizon->m_mesh_grids[((i - 1) * curhorizon->m_mesh_cols + j) * 7].m_z;
							if(j < curhorizon->m_mesh_cols - 1)
								zdisb = curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j + 1) * 7].m_z - curz;
							else if(j > 0)
								zdisb = curz - curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j - 1) * 7].m_z;
							if(ISNAN(zdisa) || ISNAN(zdisb))
								continue;
							zdisa = zdisa * 2 / 3;
							zdisb = zdisb / 2;
							curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 1].m_z = curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 1].m_z + zdisa;
							curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 2].m_z = curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 2].m_z + zdisb + zdisa / 2;
							curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 3].m_z = curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 3].m_z + zdisb - zdisa / 2;
							curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 4].m_z = curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 4].m_z - zdisa;
							curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 5].m_z = curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 5].m_z - zdisb - zdisa / 2;
							curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 6].m_z = curhorizon->m_mesh_grids[(i * curhorizon->m_mesh_cols + j) * 7 + 6].m_z - zdisb + zdisa / 2;
						}
					}
				}
			}
		}
		void DoDepthStatic()
		{
			m_deposition_depth_min = 0x7FFFFFFF;
			m_deposition_depth_max = -0x7FFFFFFF;
			for(int offset = 0; offset < m_children_horizons.size(); offset++)
			{
				SeismicHorizon3D* curhorizon = (SeismicHorizon3D*)(m_children_horizons[offset]);
				for(int i = 0; i < curhorizon->m_rows * curhorizon->m_cols; i++)
				{
					if(ISNAN(curhorizon->m_samples[i].m_z))
						continue;
					m_deposition_depth_min = m_deposition_depth_min > curhorizon->m_samples[i].m_z ? curhorizon->m_samples[i].m_z : m_deposition_depth_min;
					m_deposition_depth_max = m_deposition_depth_max < curhorizon->m_samples[i].m_z ? curhorizon->m_samples[i].m_z : m_deposition_depth_max;
				}
				if(curhorizon->m_rows == 0 || curhorizon->m_cols == 0)
				{
					for(int i = 0; i < curhorizon->m_mesh_grids.size(); i++)
					{
						if(ISNAN(curhorizon->m_mesh_grids[i].m_z))
							continue;
						m_deposition_depth_min = m_deposition_depth_min > curhorizon->m_mesh_grids[i].m_z ? curhorizon->m_mesh_grids[i].m_z : m_deposition_depth_min;
						m_deposition_depth_max = m_deposition_depth_max < curhorizon->m_mesh_grids[i].m_z ? curhorizon->m_mesh_grids[i].m_z : m_deposition_depth_max;
					}
				}
			}
		}

		// at the same geological age but has different event property
		// also as block initiative
		// ...
		HorizonVector m_children_horizons;
	};

	//
	// layer or horizon mesh batch in isochronus
	template<typename IteratorType, typename DataType>
	struct IsoDataBatch	// data batch during the same geological age
	{
		int m_base_horizon_idx; // the idx of the first horizon of this layer

		int m_number;
		IteratorType m_first;
		IteratorType m_last;
		IteratorType m_cursor;

		inline DataType &operator[](int i)
		{
			m_cursor = m_first + i;
			return *m_cursor;
		}
	};
	typedef IsoDataBatch<MeshItr, Mesh3D*> IsoMeshBatch;
	typedef IsoDataBatch<VertexItr, Vertex3D*> IsoVertexBatch;

	// batch in slice
	template<typename IteratorType, typename DataType>
	struct SliceDataBatch // not only a plane, 
	{
		int m_number;
		std::map<int, std::vector<IteratorType> > m_batch; // the first is horizon idx

		inline DataType &operator[](int i)
		{
			std::map<int, std::vector<IteratorType> >::iterator first = m_batch.begin();
			std::map<int, std::vector<IteratorType> >::iterator last = m_batch.end();
			int order = 0;
			for(; first != last; first++)
			{
				for(int j = 0; j < first->second.size();j++,order++)
				{
					if(order== i)
					{
						return *(first->second[i]);
					}
				}
			}
		}
	};
	typedef SliceDataBatch<MeshItr, Mesh3D*> SliceMeshBatch;
	typedef SliceDataBatch<VertexItr, Vertex3D*> SliceVertexBatch;

	//
	enum BatchDirection
	{
		BD_X,
		BD_Y,
		BD_Z,
	};
	// batch in z-direction
	template<typename IteratorType, typename DataType>
	struct DirectionDataBatch // not only a plane, 
	{
		int m_from_horizon_idx; 
		int m_to_horizon_idx;

		int m_number;
		std::vector<IteratorType> m_batch;
		inline DataType &operator[](int i)
		{
			return *m_batch[i];
		}
	};
	typedef DirectionDataBatch<MeshItr, Mesh3D*> DirectionMeshBatch;
	typedef DirectionDataBatch<VertexItr, Vertex3D*> DirectionVertexBatch;

	// batch in octree sub node
	template<typename IteratorType, typename DataType>
	struct OctreeDataBatch // not only a plane, 
	{
		int m_from_tile_idx;
		int m_to_tile_idx;

		int m_number;
		std::vector<IteratorType> m_batch;
		inline DataType &operator[](int i)
		{
			return *m_batch[i];
		}
	};
	typedef OctreeDataBatch<MeshItr, Mesh3D*> OctreeMeshBatch;
	typedef OctreeDataBatch<VertexItr, Vertex3D*> OctreeVertexBatch;
}

#endif