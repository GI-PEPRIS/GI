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
#ifndef __ANYCGAL_HYPER_MESH_H__
#define __ANYCGAL_HYPER_MESH_H__

// Refer to EXPORT & IMPORT macroes
#include "anycgal.h"

//
#include "anyhypermeshbasic.h"
#include "anyhypermeshiterator.h"

#include "any/base/loki/visitor.h"
using namespace AnyBase::Loki;

// namespace 
namespace AnyCGAL
{
	/*!
	* VISITOR DESIGN MODEL
	**/
	class ANYCGAL_CLASS CAnyHyperMesh : public BaseVisitable<>
	{
	public:
		LOKI_DEFINE_VISITABLE()
		//
		//
		//
		/*!
		*
		**/
		CAnyHyperMesh();
		virtual ~CAnyHyperMesh();

	public:
		//
		// sample data
		//
		/*!
		* kinds of horizon modes: LMT_XXX
		**/
		bool AddHorizon(Horizon3D *horizon);
		void ReleaseHorizon();
		bool IsHorizonReady();	// time-, depth-, erosen-conflict
		void EraseHorizon(const string &name);

		//
		//
		//
		void GetLayerIdxes(std::vector<int> &layeridxes);
		void GetLayerHorizonIdxes(int layeridx, std::vector<int> &horizonidxes);
		void GetDepositionAgeHorizonIdxes(double age, std::vector<int> &horizonidxes);

		//
		// create mesh
		//
		void ReleaseMesh();
		bool CheckIncrementalUpdate(std::vector<int> &horizonevents, int solidtype, short meshtype, int meshrows, int meshcols, const CGeoRect<double> &meshextent);

		//
		template<typename MeshType, typename VertexType>
		bool MakeMeshIncremental(HorizonVector &newhorizons, std::vector<int> &findinolds_simulated, std::vector<bool> &oldfindsimulated)
		{
			if(!newhorizons.size() || m_mesh_type == HT_Unknown)
				return false;
			if(m_mesh_rows <= 1 || m_mesh_cols <= 1 || m_mesh_extent.Width() == 0 || m_mesh_extent.Height() == 0)
				return false;
			std::vector<int> findinolds;
			for(int offset = 0; offset < newhorizons.size(); offset++)
			{
				int findinold = -1;
				for(int i = 0; i < m_horizons.size(); i++)
				{
					if(m_horizons[i]->m_horizon_name == newhorizons[offset]->m_horizon_name)
					{
						findinold = i;
						break;
					}
				}
				findinolds.push_back(findinold);
			}
			for(int offset = 0; offset < newhorizons.size(); offset++)
			{
				newhorizons[offset]->m_layer_idx = offset;
				newhorizons[offset]->m_horizon_idx = 0;
				if(findinolds[offset] == -1)
					newhorizons[offset]->DoDepthStatic();
			}

			// firstly, make mesh for each layer horizon
			// larger means deeper, size-1, means deepest horizon, 0 means earth horizon
			for(int offset = 0; offset < newhorizons.size(); offset++)	
			{
				if(findinolds[offset] == -1)
					newhorizons[offset]->DoInterpolate(m_mesh_rows, m_mesh_cols, m_mesh_type, m_mesh_extent);
			}

			// secondly, to detail layer horizon against simulated horizon segment
			HorizonVector new_horizons_simulated;
			DoGetSimulatedHorizonIncremental(new_horizons_simulated, newhorizons, findinolds_simulated);
			m_octreeLevel = 1;
			while(pow(2.0, m_octreeLevel - 1) < m_mesh_rows || \
				pow(2.0, m_octreeLevel - 1) < m_mesh_cols || \
				pow(2.0, m_octreeLevel - 1) < new_horizons_simulated.size())
			{
				m_octreeLevel++;
			}

			// thirdly, set up mesh vertexes
			std::vector<VertexContainer> new_initial_vertexes; 
			int vertexorder = 0;
			for(int offset = 0; offset < new_horizons_simulated.size(); offset++)	
			{
				if(findinolds_simulated[offset] != -1)
				{
					for(int i = 0; i < m_initial_vertexes[findinolds_simulated[offset]].size(); i++)
					{
						Vertex3D *onevertex = m_initial_vertexes[findinolds_simulated[offset]][i];
						onevertex->m_sequence_idx = vertexorder;
						//CGeoPoint<int> position(i % m_mesh_cols, (int)i / m_mesh_cols, offset);
						//CGeoPoint<int> postile;
						//PositionToPostile(position, m_octreeLevel, postile);
						//std::vector<int> morton;
						//Postile2Morton(postile, m_octreeLevel, morton);
						//Morton2Tileid(morton, onevertex->m_tile_code);
						vertexorder++;
					}
					new_initial_vertexes.push_back(m_initial_vertexes[findinolds_simulated[offset]]);
				}
				else
				{
					VertexContainer onehorizonvertexes;
					for(int i = 0; i < new_horizons_simulated[offset]->m_mesh_grids.size(); i++)
					{
						Vertex3D *onevertex = new VertexType;
						onevertex->m_sequence_idx = vertexorder;
						//CGeoPoint<int> position(i % m_mesh_cols, (int)i / m_mesh_cols, offset);
						//CGeoPoint<int> postile;
						//PositionToPostile(position, m_octreeLevel, postile);
						//std::vector<int> morton;
						//Postile2Morton(postile, m_octreeLevel, morton);
						//Morton2Tileid(morton, onevertex->m_tile_code);
						onevertex->m_x = new_horizons_simulated[offset]->m_mesh_grids[i].m_x;
						onevertex->m_y = new_horizons_simulated[offset]->m_mesh_grids[i].m_y;
						onevertex->m_z = new_horizons_simulated[offset]->m_mesh_grids[i].m_z;
						onevertex->m_w = new_horizons_simulated[offset]->m_mesh_grids[i].m_w;
						vertexorder++;
						onehorizonvertexes.push_back(onevertex);
					}
					new_initial_vertexes.push_back(onehorizonvertexes);
				}
			}
			// lastly, construct mesh
			std::vector<MeshContainer> new_initial_meshes;
			for(int offset = 1; offset < new_horizons_simulated.size(); offset++)
			{
				Horizon3D *curhorizon = new_horizons_simulated[offset];
				Horizon3D *lasthorizon = new_horizons_simulated[offset - 1];
				if(!lasthorizon->m_mesh_grids.size() || !curhorizon->m_mesh_grids.size())
					continue;
				if(findinolds_simulated[offset] != -1 && findinolds_simulated[offset - 1] != -1)
				{
					for(int i = 0; i < m_mesh_rows - 1; i++)
					{
						for(int j = 0; j < m_mesh_cols - 1; j++)
						{
							Mesh3D *mesh3d = m_initial_meshes[findinolds_simulated[offset - 1]][i * (m_mesh_cols - 1) + j];
							mesh3d->m_layer_idx = lasthorizon->m_layer_idx;
							mesh3d->m_horizon_idx = lasthorizon->m_horizon_idx;
							mesh3d->m_vertex_idxes[0] = new_initial_vertexes[offset - 1][i * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[1] = new_initial_vertexes[offset - 1][i * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[2] = new_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[3] = new_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[4] = new_initial_vertexes[offset][i * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[5] = new_initial_vertexes[offset][i * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[6] = new_initial_vertexes[offset][(i + 1) * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[7] = new_initial_vertexes[offset][(i + 1) * m_mesh_cols + j + 1]->m_sequence_idx;
						}
					}
					new_initial_meshes.push_back(m_initial_meshes[findinolds_simulated[offset - 1]]);
				}
				else
				{
					MeshContainer onehorizonmeshes;
					for(int i = 0; i < m_mesh_rows - 1; i++)
					{
						for(int j = 0; j < m_mesh_cols - 1; j++)
						{
							Mesh3D *mesh3d = new MeshType;
							if(ISNAN(new_initial_vertexes[offset][i * m_mesh_cols + j]->m_z) || ISNAN(new_initial_vertexes[offset - 1][i * m_mesh_cols + j]->m_z))
								mesh3d->m_status = MS_Invalid;
							else if(ISNAN(new_initial_vertexes[offset][i * m_mesh_cols + j + 1]->m_z) || ISNAN(new_initial_vertexes[offset - 1][i * m_mesh_cols + j + 1]->m_z))
								mesh3d->m_status = MS_Invalid;
							else if(ISNAN(new_initial_vertexes[offset][(i + 1) * m_mesh_cols + j]->m_z) || ISNAN(new_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j]->m_z))
								mesh3d->m_status = MS_Invalid;
							else if(ISNAN(new_initial_vertexes[offset][(i + 1) * m_mesh_cols + j + 1]->m_z) || ISNAN(new_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j + 1]->m_z))
								mesh3d->m_status = MS_Invalid;
							else
								mesh3d->m_status = MS_Normal;
							mesh3d->m_layer_idx = lasthorizon->m_layer_idx;
							mesh3d->m_horizon_idx = lasthorizon->m_horizon_idx;
							mesh3d->m_type = m_mesh_type;
							mesh3d->m_vertex_number = 8;
							mesh3d->m_vertex_idxes = (long*)::malloc(sizeof(long) * mesh3d->m_vertex_number);
							mesh3d->m_vertex_idxes[0] = new_initial_vertexes[offset - 1][i * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[1] = new_initial_vertexes[offset - 1][i * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[2] = new_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[3] = new_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[4] = new_initial_vertexes[offset][i * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[5] = new_initial_vertexes[offset][i * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[6] = new_initial_vertexes[offset][(i + 1) * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[7] = new_initial_vertexes[offset][(i + 1) * m_mesh_cols + j + 1]->m_sequence_idx;
							onehorizonmeshes.push_back(mesh3d);
						}
					}
					new_initial_meshes.push_back(onehorizonmeshes);
				}
			}
			// release unused old data
			std::vector<bool> oldfind;
			oldfind.resize(m_horizons.size(), false);
			oldfindsimulated.resize(m_horizons_simulated.size(), false);
			for(int i = 0; i < findinolds.size(); i++)
			{
				if(findinolds[i] != -1)
					oldfind[findinolds[i]] = true;
			}
			for(int i = 0; i < findinolds_simulated.size(); i++)
			{
				if(findinolds_simulated[i] != -1)
					oldfindsimulated[findinolds_simulated[i]] = true;
			}
			for(int i = 0; i < m_horizons.size(); i++)
			{
				if(!oldfind[i])
				{
					delete m_horizons[i];
					m_horizons[i] = 0;
				}
			}
			m_horizons.clear();
			for(int i = 0; i < m_horizons_simulated.size(); i++)
			{
				if(!oldfindsimulated[i])
				{
					delete m_horizons_simulated[i];
					m_horizons_simulated[i] = 0;
				}
			}
			m_horizons_simulated.clear();
			for(int i = 0; i < m_initial_vertexes.size(); i++)
			{
				if(!oldfindsimulated[i])
				{
					for(int j = 0; j < m_initial_vertexes[i].size(); j++)
					{
						delete m_initial_vertexes[i][j];
					}
					m_initial_vertexes[i].clear();
				}
			}
			m_initial_vertexes.clear();
			for(int i = 0; i < m_initial_meshes.size(); i++)
			{
				if(!oldfindsimulated[i] && !oldfindsimulated[i + 1])
				{
					for(int j = 0; j < m_initial_meshes[i].size(); j++)
					{
						delete m_initial_meshes[i][j];
					}
					m_initial_meshes[i].clear();
				}
			}
			m_initial_meshes.clear();
			for(int i = 0; i < m_initial_vertex_relations.size(); i++)
			{
				for(int j = 0; j < m_initial_vertex_relations[i].size(); j++)
				{
					delete m_initial_vertex_relations[i][j];
				}
				m_initial_vertex_relations[i].clear();
			}
			m_initial_vertex_relations.clear();
			m_horizons = newhorizons;
			m_horizons_simulated = new_horizons_simulated;
			m_initial_vertexes = new_initial_vertexes; 
			m_initial_meshes = new_initial_meshes;
			for(int offset = 0; offset < m_initial_vertexes.size(); offset++)
			{
				VertexTopoContainer onehorizontopo;
				for(int i = 0; i < m_mesh_rows; i++)
				{
					for(int j = 0; j < m_mesh_cols; j++)
					{
						VertexTOPO *onetopo = new VertexTOPO;
						if(j < m_mesh_cols - 1)
							onetopo->m_next_x = m_initial_vertexes[offset].begin() + i * m_mesh_cols + j + 1;
						else
							onetopo->m_next_x = m_initial_vertexes[offset].end();
						if(i < m_mesh_rows - 1)
							onetopo->m_next_y = m_initial_vertexes[offset].begin() + (i + 1) * m_mesh_cols + j;
						else
							onetopo->m_next_y = m_initial_vertexes[offset].end();
						if(offset < m_initial_vertexes.size() - 1)
							onetopo->m_next_z = m_initial_vertexes[offset + 1].begin() + i * m_mesh_cols + j;
						else
							onetopo->m_next_z = m_initial_vertexes[offset].end();
						onehorizontopo.push_back(onetopo);
					}
				}
				m_initial_vertex_relations.push_back(onehorizontopo);
			}
		}
		//
		template<typename MeshType, typename VertexType>
		bool MakeMesh(short meshtype, int meshrows, int meshcols, const CGeoRect<double> &meshextent)
		{
			if(!m_horizons.size() || meshtype == HT_Unknown)
				return false;
			m_mesh_type = meshtype;
			m_mesh_rows = meshrows;
			m_mesh_cols = meshcols;
			m_mesh_extent = meshextent;
			if(m_mesh_rows <= 1 || m_mesh_cols <= 1 || m_mesh_extent.Width() == 0 || m_mesh_extent.Height() == 0)
				return false;
			ReleaseMesh();

			// firstly, make mesh for each layer horizon
			// larger means deeper, size-1, means deepest horizon, 0 means earth horizon
			for(int offset = 0; offset < m_horizons.size(); offset++)	
			{
				m_horizons[offset]->DoInterpolate(m_mesh_rows, m_mesh_cols, m_mesh_type, m_mesh_extent);
			}

			// secondly, to detail layer horizon against simulated horizon segment
			m_horizons_simulated.clear();
			DoGetSimulatedHorizon(m_horizons_simulated);

			m_octreeLevel = 1;
			while(pow(2.0, m_octreeLevel - 1) < m_mesh_rows || \
				pow(2.0, m_octreeLevel - 1) < m_mesh_cols || \
				pow(2.0, m_octreeLevel - 1) < m_horizons_simulated.size())
			{
				m_octreeLevel++;
			}

			// thirdly, set up mesh vertexes
			assert(!m_initial_vertexes.size());
			int vertexorder = 0;
			for(int offset = 0; offset < m_horizons_simulated.size(); offset++)	
			{
				VertexContainer onehorizonvertexes;
				for(int i = 0; i < m_horizons_simulated[offset]->m_mesh_grids.size(); i++)
				{
					Vertex3D *onevertex = new VertexType;
					onevertex->m_sequence_idx = vertexorder;
					//CGeoPoint<int> position(i % m_mesh_cols, (int)i / m_mesh_cols, offset);
					//CGeoPoint<int> postile;
					//PositionToPostile(position, m_octreeLevel, postile);
					//std::vector<int> morton;
					//Postile2Morton(postile, m_octreeLevel, morton);
					//Morton2Tileid(morton, onevertex->m_tile_code);
					onevertex->m_x = m_horizons_simulated[offset]->m_mesh_grids[i].m_x;
					onevertex->m_y = m_horizons_simulated[offset]->m_mesh_grids[i].m_y;
					onevertex->m_z = m_horizons_simulated[offset]->m_mesh_grids[i].m_z;
					onevertex->m_w = m_horizons_simulated[offset]->m_mesh_grids[i].m_w;
					vertexorder++;
					onehorizonvertexes.push_back(onevertex);
				}
				m_initial_vertexes.push_back(onehorizonvertexes);
			}
			assert(!m_initial_vertex_relations.size());
			for(int offset = 0; offset < m_initial_vertexes.size(); offset++)
			{
				VertexTopoContainer onehorizontopo;
				for(int i = 0; i < m_mesh_rows; i++)
				{
					for(int j = 0; j < m_mesh_cols; j++)
					{
						if(m_mesh_type == HT_Hedron_Hexa || m_mesh_type == HT_Hedron_Hexa_Tetra)
						{
							VertexTOPO *onetopo = new VertexTOPO;
							if(j < m_mesh_cols - 1)
								onetopo->m_next_x = m_initial_vertexes[offset].begin() + i * m_mesh_cols + j + 1;
							else
								onetopo->m_next_x = m_initial_vertexes[offset].end();
							if(i < m_mesh_rows - 1)
								onetopo->m_next_y = m_initial_vertexes[offset].begin() + (i + 1) * m_mesh_cols + j;
							else
								onetopo->m_next_y = m_initial_vertexes[offset].end();
							if(offset < m_initial_vertexes.size() - 1)
								onetopo->m_next_z = m_initial_vertexes[offset + 1].begin() + i * m_mesh_cols + j;
							else
								onetopo->m_next_z = m_initial_vertexes[offset].end();
							onehorizontopo.push_back(onetopo);
						}
						else if(m_mesh_type == HT_Hedron_Octa || m_mesh_type == HT_Hedron_Octa_Tetra)
						{
							for(int k = 0; k < 7; k++)
							{
								VertexTOPO *onetopo = new VertexTOPO;
								if(j < m_mesh_cols - 1)
									onetopo->m_next_x = m_initial_vertexes[offset].begin() + (i * m_mesh_cols + j + 1) * 7 + k;
								else
									onetopo->m_next_x = m_initial_vertexes[offset].end();
								if(i < m_mesh_rows - 1)
									onetopo->m_next_y = m_initial_vertexes[offset].begin() + ((i + 1) * m_mesh_cols + j) * 7 + k;
								else
									onetopo->m_next_y = m_initial_vertexes[offset].end();
								if(offset < m_initial_vertexes.size() - 1)
									onetopo->m_next_z = m_initial_vertexes[offset + 1].begin() + (i * m_mesh_cols + j) * 7 + k;
								else
									onetopo->m_next_z = m_initial_vertexes[offset].end();
								onehorizontopo.push_back(onetopo);
							}
						}
					}
				}
				m_initial_vertex_relations.push_back(onehorizontopo);
			}
			// lastly, construct mesh
			assert(!m_initial_meshes.size());
			for(int offset = 1; offset < m_horizons_simulated.size(); offset++)
			{
				Horizon3D *curhorizon = m_horizons_simulated[offset];
				Horizon3D *lasthorizon = m_horizons_simulated[offset - 1];
				if(!lasthorizon->m_mesh_grids.size() || !curhorizon->m_mesh_grids.size())
					continue;
				MeshContainer onehorizonmeshes;
				if(m_mesh_type == HT_Hedron_Hexa || m_mesh_type == HT_Hedron_Hexa_Tetra)
				{
					for(int i = 0; i < m_mesh_rows - 1; i++)
					{
						for(int j = 0; j < m_mesh_cols - 1; j++)
						{
							Mesh3D *mesh3d = new MeshType;
							if(ISNAN(m_initial_vertexes[offset][i * m_mesh_cols + j]->m_z) || ISNAN(m_initial_vertexes[offset - 1][i * m_mesh_cols + j]->m_z))
								mesh3d->m_status = MS_Invalid;
							else if(ISNAN(m_initial_vertexes[offset][i * m_mesh_cols + j + 1]->m_z) || ISNAN(m_initial_vertexes[offset - 1][i * m_mesh_cols + j + 1]->m_z))
								mesh3d->m_status = MS_Invalid;
							else if(ISNAN(m_initial_vertexes[offset][(i + 1) * m_mesh_cols + j]->m_z) || ISNAN(m_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j]->m_z))
								mesh3d->m_status = MS_Invalid;
							else if(ISNAN(m_initial_vertexes[offset][(i + 1) * m_mesh_cols + j + 1]->m_z) || ISNAN(m_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j + 1]->m_z))
								mesh3d->m_status = MS_Invalid;
							else
								mesh3d->m_status = MS_Normal;
							mesh3d->m_layer_idx = lasthorizon->m_layer_idx;
							mesh3d->m_horizon_idx = lasthorizon->m_horizon_idx;
							mesh3d->m_type = m_mesh_type;
							mesh3d->m_vertex_number = 8;
							mesh3d->m_vertex_idxes = (long*)::malloc(sizeof(long) * mesh3d->m_vertex_number);
							mesh3d->m_vertex_idxes[0] = m_initial_vertexes[offset - 1][i * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[1] = m_initial_vertexes[offset - 1][i * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[2] = m_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[3] = m_initial_vertexes[offset - 1][(i + 1) * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[4] = m_initial_vertexes[offset][i * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[5] = m_initial_vertexes[offset][i * m_mesh_cols + j + 1]->m_sequence_idx;
							mesh3d->m_vertex_idxes[6] = m_initial_vertexes[offset][(i + 1) * m_mesh_cols + j]->m_sequence_idx;
							mesh3d->m_vertex_idxes[7] = m_initial_vertexes[offset][(i + 1) * m_mesh_cols + j + 1]->m_sequence_idx;
							//if(m_mesh_type == HT_Hedron_Hexa_Tetra)
							//{
							//	mesh3d->m_sub_tetra_number = 6;
							//	mesh3d->m_sub_tetras = new MeshType*[mesh3d->m_sub_tetra_number];
							//	for(int k = 0; k < 6; k++)
							//	{
							//		mesh3d->m_sub_tetras[k] = new MeshType;
							//		mesh3d->m_sub_tetras[k]->m_type = m_mesh_type;
							//		mesh3d->m_sub_tetras[k]->m_status = MS_Normal;
							//		mesh3d->m_sub_tetras[k]->m_layer_idx = mesh3d->m_layer_idx;
							//		mesh3d->m_sub_tetras[k]->m_horizon_idx = mesh3d->m_horizon_idx;
							//		mesh3d->m_sub_tetras[k]->m_vertex_number = 4;
							//		mesh3d->m_sub_tetras[k]->m_vertex_idxes = (long*)::malloc(sizeof(long) * mesh3d->m_sub_tetras[k]->m_vertex_number);
							//		mesh3d->m_sub_tetras[k]->m_sub_mesh_number = 0;
							//		mesh3d->m_sub_tetras[k]->m_sub_tetra_number = 0;
							//		if(k == 0)
							//		{
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[0] = mesh3d->m_vertex_idxes[0];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[1] = mesh3d->m_vertex_idxes[2];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[2] = mesh3d->m_vertex_idxes[1];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[3] = mesh3d->m_vertex_idxes[5];
							//		}
							//		else if(k == 1)
							//		{
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[0] = mesh3d->m_vertex_idxes[4];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[1] = mesh3d->m_vertex_idxes[5];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[2] = mesh3d->m_vertex_idxes[6];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[3] = mesh3d->m_vertex_idxes[0];
							//		}
							//		else if(k == 2)
							//		{
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[0] = mesh3d->m_vertex_idxes[0];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[1] = mesh3d->m_vertex_idxes[6];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[2] = mesh3d->m_vertex_idxes[2];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[3] = mesh3d->m_vertex_idxes[5];
							//		}
							//		else if(k == 3)
							//		{
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[0] = mesh3d->m_vertex_idxes[1];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[1] = mesh3d->m_vertex_idxes[7];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[2] = mesh3d->m_vertex_idxes[2];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[3] = mesh3d->m_vertex_idxes[3];
							//		}
							//		else if(k == 4)
							//		{
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[0] = mesh3d->m_vertex_idxes[5];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[1] = mesh3d->m_vertex_idxes[7];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[2] = mesh3d->m_vertex_idxes[6];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[3] = mesh3d->m_vertex_idxes[2];
							//		}
							//		else if(k == 5)
							//		{
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[0] = mesh3d->m_vertex_idxes[1];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[1] = mesh3d->m_vertex_idxes[5];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[2] = mesh3d->m_vertex_idxes[2];
							//			mesh3d->m_sub_tetras[k]->m_vertex_idxes[3] = mesh3d->m_vertex_idxes[7];
							//		}
							//	}
							//}
							onehorizonmeshes.push_back(mesh3d);
						}
					}
				}
				else if(m_mesh_type == HT_Hedron_Octa || m_mesh_type == HT_Hedron_Octa_Tetra)
				{
					for(int i = 0; i < m_mesh_rows; i++)
					{
						for(int j = 0; j < m_mesh_cols; j++)
						{
							Mesh3D *mesh3d = new MeshType;
							if(ISNAN(m_initial_vertexes[offset-1][(i * m_mesh_cols + j) * 7]->m_z) || ISNAN(m_initial_vertexes[offset][(i * m_mesh_cols + j) * 7]->m_z))
								mesh3d->m_status = MS_Invalid;
							else
								mesh3d->m_status = MS_Normal;
							mesh3d->m_layer_idx = lasthorizon->m_layer_idx;
							mesh3d->m_horizon_idx = lasthorizon->m_horizon_idx;
							mesh3d->m_type = m_mesh_type;
							mesh3d->m_vertex_number = 14;
							mesh3d->m_vertex_idxes = (long*)::malloc(sizeof(long) * mesh3d->m_vertex_number);
							for(int k = 0; k < 7; k++)
							{
								mesh3d->m_vertex_idxes[k] = m_initial_vertexes[offset - 1][(i * m_mesh_cols + j) * 7 + k]->m_sequence_idx;
								mesh3d->m_vertex_idxes[7 + k] = m_initial_vertexes[offset][(i * m_mesh_cols + j) * 7 + k]->m_sequence_idx;
							}
							//if(m_mesh_type == HT_Hedron_Octa_Tetra)
							//{
							//	mesh3d->m_sub_tetra_number = 18;
							//	mesh3d->m_sub_tetras = new MeshType*[mesh3d->m_sub_tetra_number];
							//	for(int k = 0; k < 6; k++)
							//	{
							//		std::vector<long> trianglecube;
							//		if(k == 0)
							//		{
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[0]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[5]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[4]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[7]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[12]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[11]);
							//		}
							//		else if(k == 1)
							//		{
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[0]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[4]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[3]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[7]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[11]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[10]);
							//		}
							//		else if(k == 2)
							//		{
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[0]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[3]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[2]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[7]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[10]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[9]);
							//		}
							//		else if(k == 3)
							//		{
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[0]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[2]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[1]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[7]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[9]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[8]);
							//		}
							//		else if(k == 4)
							//		{
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[0]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[1]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[6]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[7]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[8]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[13]);
							//		}
							//		else if(k == 5)
							//		{
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[0]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[6]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[5]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[7]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[13]);
							//			trianglecube.push_back(mesh3d->m_vertex_idxes[12]);
							//		}
							//		for(int l = 0; l < 3; l++)
							//		{
							//			mesh3d->m_sub_tetras[k * 3 + l] = new MeshType;
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_type = m_mesh_type;
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_status = MS_Normal;
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_layer_idx = mesh3d->m_layer_idx;
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_horizon_idx = mesh3d->m_horizon_idx;
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_number = 4;
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes = (long*)::malloc(sizeof(long) * mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_number);
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_sub_mesh_number = 0;
							//			mesh3d->m_sub_tetras[k * 3 + l]->m_sub_tetra_number = 0;
							//			if(l == 0)
							//			{
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[0] = trianglecube[0];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[1] = trianglecube[2];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[2] = trianglecube[1];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[3] = trianglecube[3];
							//			}
							//			else if(l == 1)
							//			{
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[0] = trianglecube[3];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[1] = trianglecube[4];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[2] = trianglecube[5];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[3] = trianglecube[1];
							//			}
							//			else if(l == 2)
							//			{
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[0] = trianglecube[2];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[1] = trianglecube[3];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[2] = trianglecube[5];
							//				mesh3d->m_sub_tetras[k * 3 + l]->m_vertex_idxes[3] = trianglecube[1];
							//			}
							//		}
							//	}
							//}
							onehorizonmeshes.push_back(mesh3d);
						}
					}
				}
				m_initial_meshes.push_back(onehorizonmeshes);
			}
		}
		void RefineMesh(const CGeoRect<double> &extent, unsigned char times);

		//
		// deprecated
		//
		void Pick(int layeridx, int horizonidx, MeshContainer &meshes, bool istetra);	// tetra-hedron
		void Pick(double depositionage, MeshContainer &meshes, bool istetra);
		void Pick(const Horizon3D &fault, MeshContainer &meshes, bool istetra);
		void GetMeshVertexes(const Mesh3D *const meshes, std::vector<Vertex3D *> &vertexes);	// need to order by tile code

		//
		// loop mesh with isochronus iterator
		//
		void GetMesh(double fromage, double toage, IsoMeshIterator &meshes);
		void GetVertex(double fromage, double toage, IsoVertexIterator &vertexes);

		void GetLayerMesh(int layeridx, IsoMeshIterator &meshes);
		void GetLayerVertex(int layeridx, IsoVertexIterator &vertexes);

		void GetHorizonMesh(int horizonidx, IsoMeshIterator &meshes);
		void GetHorizonVertex(int horizonidx, IsoVertexIterator &vertexes);

		void GetAllMesh(IsoMeshIterator &meshes);
		void GetAllVertex(IsoVertexIterator &vertexes);
		
		// loop mesh with zdirection iterator
		void GetMesh(short direction, CGeoPoint<double> &position, DirectionMeshIterator &meshes);
		void GetVertex(short direction, CGeoPoint<double> &position, DirectionVertexIterator &vertexes);
		void GetVertexoffset(CGeoPoint<double> &position, int &vertexoffset);

		void GetAllMesh(DirectionMeshIterator &meshes);
		void GetAllVertex(DirectionVertexIterator &vertexes);

		// loop mesh with slice iterator
		void GetNaNMesh(SliceMeshIterator &meshes);
		void GetNaNVertex(SliceVertexIterator &vertexes);

		void GetIntersectMesh(const Horizon3D &fault, SliceMeshIterator &meshes);
		void GetIntersectVertex(const Horizon3D &fault, SliceVertexIterator &vertexes);

		void GetFirstBorderMesh(SliceMeshIterator &meshes);
		void GetFirstBorderVertex(SliceVertexIterator &vertexes);

		void GetSecondBorderMesh(SliceMeshIterator &meshes);
		void GetSecondBorderVertex(SliceVertexIterator &vertexes);

		// loop mesh with octree iterator
		void GetOctreeMesh(CGeoPoint<double> &position, int fetchlevel, OctreeMeshIterator &meshes);
		void GetOctreeVertex(CGeoPoint<double> &position, int fetchlevel, OctreeVertexIterator &vertexes);

		void GetOctreeMesh(CGeoRect<double> &top, CGeoRect<double> &base, OctreeMeshIterator &meshes);
		void GetOctreeVertex(CGeoRect<double> &top,CGeoRect<double> &base, OctreeVertexIterator &vertexes);

		// 
		// topo relation
		//
		void GetVertexRelation(short direction, int horizonidx, VertexItr &cur, std::vector<Vertex3D*> &vertexes);
		void GetVertexRelationMesh(Vertex3D* vertexa, Vertex3D* vertexb, std::vector<Mesh3D*> &commonmesh);

	public:
		//
		void DoGetSimulatedHorizon(HorizonVector &horizonssplitted);
		void DoGetSimulatedHorizonIncremental(HorizonVector &horizonssplitted, HorizonVector &newhorizons, std::vector<int> &findinolds_simulated);
		void UnionHorizonExtents(int meshrows, int meshcols, CGeoRect<double> meshextent, bool handlenan);
		void UnionHorizonExtentsIncremental(HorizonVector &newhorizons, bool handlenan);

		//
		static bool DoCompareLayerIdx(const Horizon3D *first, const Horizon3D *second)
		{
			return first->m_layer_idx < second->m_layer_idx;
		}
		static bool DoCompareLayerAge(const Horizon3D *first, const Horizon3D *second)
		{
			return first->m_deposition_age_from < second->m_deposition_age_from;
		}		

		//
		bool PositionToPostile(CGeoPoint<int> Position, int fetchlevel, CGeoPoint<int> &postile);
		bool PostileToPosition(CGeoPoint<int> postile, int fetchlevel, CGeoPoint<int> &Position1, CGeoPoint<int> &Position2);
		bool Postile2Morton(CGeoPoint<int> postile, int fetchlevel, std::vector<int> &morton);
		bool Morton2Postile(std::vector<int> morton, CGeoPoint<int> &postile, int &fetchlevel);
		bool Morton2Tileid(std::vector<int> morton, int &tileid);
		bool Tileid2Morton(int tileid, std::vector<int> &morton);

	public:
		// horizons
		HorizonVector m_horizons;
		HorizonVector m_horizons_simulated;
		
		// vertex in horizon order 
		// order by layeridx firstly, then horizonidx secondly
		std::vector<VertexContainer> m_initial_vertexes; 
		std::vector<MeshContainer> m_initial_meshes;
		std::vector<VertexTopoContainer> m_initial_vertex_relations;

		//	
		unsigned char m_mesh_type;
		string m_mesh_name;
		CGeoRect<double> m_mesh_extent;
		int m_mesh_rows;
		int m_mesh_cols;
		CGeoRect<int> m_mesh_rowcol_extent;//当前网在原始网中的范围，用于表示精化网格的范围

		// octree settings
		int m_octreeLevel;
		int m_tileSizex;
		int m_tileSizey;
		int m_tileSizez;
	};
}

#endif