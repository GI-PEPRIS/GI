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
#ifndef __ANYBASIN_HYPER_BASIN_SIMULATOR_H__
#define __ANYBASIN_HYPER_BASIN_SIMULATOR_H__

//
#include "anybasin.h"
#include "anyhyperbasinbasic.h"
#include "horizonbatchsimulated.h"
#include "horizonbatchdistributed.h"

//
#include "any/cgal/anyhypermesh.h"
using namespace AnyCGAL;
#include "any/vis/anyburialhistoryplot.h"
using namespace AnyVis;

//
namespace AnyBasin
{
	/*!
	*
	**/
	class ANYBASIN_CLASS CAnyHyperBasinSimulator : public CAnyHyperMesh
	{
	private:

		struct MemoryDebugHelper
		{
			MemoryDebugHelper();
			~MemoryDebugHelper();

			double m_start;
			double m_end;
		};

		struct TimeDebugHelper
		{
			TimeDebugHelper();
			~TimeDebugHelper();

			long m_start;
			long m_end;
		};

	public:
		// for recover max depth
		struct BurialHistorySimulated
		{
			//
			int m_top_horizon_idx;
			int m_bottom_horizon_idx;

			//
			double m_geological_event;
			int m_connection_marker;
			double m_from_age;
			double m_to_age;

			//
			double m_ever_thickness;
			double m_current_thickness;

			//
			double m_top_depth;
			double m_bottom_depth;

			//
			double m_max_top_depth;
			double m_max_bottom_depth;

			//
			void CopyMaxDepthToDepth()
			{ 
				//复制MaxTopThickness,MaxBottomDepth到TopDepth 和BottomDepth
				m_top_depth=m_max_top_depth;
				m_bottom_depth=m_max_bottom_depth;
				m_ever_thickness=m_current_thickness;
			}
			BurialHistorySimulated()
			{
			}
			BurialHistorySimulated(const BurialHistorySimulated &other)
			{
				*this = other;
			}
			const BurialHistorySimulated &operator=(const BurialHistorySimulated &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_top_horizon_idx = other.m_top_horizon_idx;
				m_bottom_horizon_idx = other.m_bottom_horizon_idx;
				m_geological_event = other.m_geological_event;
				m_connection_marker = other.m_connection_marker;
				m_from_age = other.m_from_age;
				m_to_age = other.m_to_age;
				m_ever_thickness = other.m_ever_thickness;
				m_current_thickness = other.m_current_thickness;
				m_top_depth = other.m_top_depth;
				m_bottom_depth = other.m_bottom_depth;
				m_max_top_depth = other.m_max_top_depth;
				m_max_bottom_depth = other.m_max_bottom_depth;

				return *this;
			}
		};

		//
		struct BatchSimulatedOrder
		{
			int m_current_layer;
			int m_current_horizon;
		};

		/*!
		* FOR GENERATION OF FINITE ELEMENT MODEL 
		**/
		struct HyperModelBasicVertex : public AnyCGAL::Vertex3D
		{
			double m_water_ultra_pressure;
			double m_water_ultra_delta_pressure;
			double m_oil_ultra_pressure;
			double m_gas_ultra_pressure;

			double m_water_static_pressure;
			double m_water_static_delta_pressure;

			double m_oil_static_pressure;
			double m_oil_static_delta_pressure;
			
			double m_gas_static_pressure;
			double m_gas_static_delta_pressure;

			double m_water_fluid_pressure;
			double m_oil_fluid_pressure;
			double m_gas_fluid_pressure;

			double m_Sw;
			double m_So;
			double m_Sg;

			double m_COC;
			double m_ever_porosity;

			double m_litho_ultra_delta_pressure;
			
			double m_temperature;
			double m_paleo_heat_fluid;
			double m_total_matrix_density;

			//毛细管压力
			double m_PcOW;
			double m_delta_PcOW; //前后时刻模拟值的插值
			double m_PcGW;
			double m_delta_PcGW;
			double m_PcGO; //分别油水、气水和气油的毛管压力
			double m_delta_PcGO;

			HyperModelBasicVertex()
			{
			}
			HyperModelBasicVertex(const HyperModelBasicVertex &other)
			{
				*this = other;
			}
			const HyperModelBasicVertex &operator=(const HyperModelBasicVertex &other)
			{
				if(this == &other)
				{
					return *this;
				}
				*((Vertex3D*)this) = *((Vertex3D*)&other);
				
				m_water_ultra_pressure = other.m_water_ultra_pressure;
				m_water_ultra_delta_pressure = other.m_water_ultra_delta_pressure;
				m_oil_ultra_pressure = other.m_oil_ultra_pressure;
				m_gas_ultra_pressure = other.m_gas_ultra_pressure;

				m_water_static_pressure = other.m_water_static_pressure;
				m_water_static_delta_pressure = other.m_water_static_delta_pressure;
				m_oil_static_pressure = other.m_oil_static_pressure;
				m_oil_static_delta_pressure = other.m_oil_static_delta_pressure;
				m_gas_static_pressure = other.m_gas_static_pressure;
				m_gas_static_delta_pressure = other.m_gas_static_delta_pressure;

				m_water_fluid_pressure = other.m_water_fluid_pressure;
				m_oil_fluid_pressure = other.m_oil_fluid_pressure;
				m_gas_fluid_pressure = other.m_gas_fluid_pressure;

				m_Sw = other.m_Sw;
				m_So = other.m_So;
				m_Sg = other.m_Sg;

				m_COC = other.m_COC;
				m_ever_porosity = other.m_ever_porosity;
				m_litho_ultra_delta_pressure = other.m_litho_ultra_delta_pressure;
				m_temperature = other.m_temperature;
				m_paleo_heat_fluid = other.m_paleo_heat_fluid;
				m_total_matrix_density = other.m_total_matrix_density;

				//毛细管压力
				m_PcOW = other.m_PcOW;
				m_delta_PcOW = other.m_delta_PcOW; //前后时刻模拟值的插值
				m_PcGW = other.m_PcGW;
				m_delta_PcGW = other.m_delta_PcGW;
				m_PcGO = other.m_PcGO; //分别油水、气水和气油的毛管压力
				m_delta_PcGO = other.m_delta_PcGO;
				
				return *this;
			}
			int GetSerializeDataLength()
			{
				int curSize = 0;
				// Vertex3D
				curSize += Vertex3D::GetSerializeDataLength();
				curSize += sizeof(double);//double m_water_ultra_pressure;
				curSize += sizeof(double);//double m_water_ultra_delta_pressure;
				curSize += sizeof(double);//double m_oil_ultra_pressure;
				curSize += sizeof(double);//double m_gas_ultra_pressure;
				curSize += sizeof(double);//double m_water_static_pressure;
				curSize += sizeof(double);//double m_water_static_delta_pressure;
				curSize += sizeof(double);//double m_oil_static_pressure;
				curSize += sizeof(double);//double m_oil_static_delta_pressure;
				curSize += sizeof(double);//double m_gas_static_pressure;
				curSize += sizeof(double);//double m_gas_static_delta_pressure;
				curSize += sizeof(double);//double m_water_fluid_pressure;
				curSize += sizeof(double);//double m_oil_fluid_pressure;
				curSize += sizeof(double);//double m_gas_fluid_pressure;
				curSize += sizeof(double);//double m_Sw;
				curSize += sizeof(double);//double m_So;
				curSize += sizeof(double);//double m_Sg;
				curSize += sizeof(double);//double m_COC;
				curSize += sizeof(double);//double m_ever_porosity;
				curSize += sizeof(double);//double m_litho_ultra_delta_pressure;
				curSize += sizeof(double);//double m_temperature;
				curSize += sizeof(double);//double m_paleo_heat_fluid;
				curSize += sizeof(double);//double m_total_matrix_density;
				curSize += sizeof(double);//double m_PcOW;
				curSize += sizeof(double);//double m_delta_PcOW;
				curSize += sizeof(double);//double m_PcGW;
				curSize += sizeof(double);//double m_delta_PcGW;
				curSize += sizeof(double);//double m_PcGO;
				curSize += sizeof(double);//double m_delta_PcGO;
				return curSize;
			}
			void SerializeData(char* &data)
			{
				// Vertex3D
				Vertex3D::SerializeData(data);
				memcpy(data, &m_water_ultra_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_water_ultra_delta_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_oil_ultra_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_gas_ultra_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_water_static_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_water_static_delta_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_oil_static_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_oil_static_delta_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_gas_static_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_gas_static_delta_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_water_fluid_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_oil_fluid_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_gas_fluid_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_Sw, sizeof(double));data += sizeof(double);
				memcpy(data, &m_So, sizeof(double));data += sizeof(double);
				memcpy(data, &m_Sg, sizeof(double));data += sizeof(double);
				memcpy(data, &m_COC, sizeof(double));data += sizeof(double);
				memcpy(data, &m_ever_porosity, sizeof(double));data += sizeof(double);
				memcpy(data, &m_litho_ultra_delta_pressure, sizeof(double));data += sizeof(double);
				memcpy(data, &m_temperature, sizeof(double));data += sizeof(double);
				memcpy(data, &m_paleo_heat_fluid, sizeof(double));data += sizeof(double);
				memcpy(data, &m_total_matrix_density, sizeof(double));data += sizeof(double);
				memcpy(data, &m_PcOW, sizeof(double));data += sizeof(double);
				memcpy(data, &m_delta_PcOW, sizeof(double));data += sizeof(double);
				memcpy(data, &m_PcGW, sizeof(double));data += sizeof(double);
				memcpy(data, &m_delta_PcGW, sizeof(double));data += sizeof(double);
				memcpy(data, &m_PcGO, sizeof(double));data += sizeof(double);
				memcpy(data, &m_delta_PcGO, sizeof(double));data += sizeof(double);
			}
			void RestoreSerializeData(char* &data)
			{
				// Vertex3D
				Vertex3D::RestoreSerializeData(data);
				memcpy(&m_water_ultra_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_water_ultra_delta_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_oil_ultra_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_gas_ultra_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_water_static_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_water_static_delta_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_oil_static_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_oil_static_delta_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_gas_static_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_gas_static_delta_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_water_fluid_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_oil_fluid_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_gas_fluid_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_Sw, data, sizeof(double));data += sizeof(double);
				memcpy(&m_So, data, sizeof(double));data += sizeof(double);
				memcpy(&m_Sg, data, sizeof(double));data += sizeof(double);
				memcpy(&m_COC, data, sizeof(double));data += sizeof(double);
				memcpy(&m_ever_porosity, data, sizeof(double));data += sizeof(double);
				memcpy(&m_litho_ultra_delta_pressure, data, sizeof(double));data += sizeof(double);
				memcpy(&m_temperature, data, sizeof(double));data += sizeof(double);
				memcpy(&m_paleo_heat_fluid, data, sizeof(double));data += sizeof(double);
				memcpy(&m_total_matrix_density, data, sizeof(double));data += sizeof(double);
				memcpy(&m_PcOW, data, sizeof(double));data += sizeof(double);
				memcpy(&m_delta_PcOW, data, sizeof(double));data += sizeof(double);
				memcpy(&m_PcGW, data, sizeof(double));data += sizeof(double);
				memcpy(&m_delta_PcGW, data, sizeof(double));data += sizeof(double);
				memcpy(&m_PcGO, data, sizeof(double));data += sizeof(double);
				memcpy(&m_delta_PcGO, data, sizeof(double));data += sizeof(double);
			}
			void CopyFromVertexSimulated(VertexSimulated &other)
			{
				*((Vertex3D*)this) = *((Vertex3D*)&other);
				
				m_water_ultra_pressure = other.m_water_ultra_pressure;
				m_water_ultra_delta_pressure = other.m_water_ultra_delta_pressure;
				m_oil_ultra_pressure = other.m_oil_ultra_pressure;
				m_gas_ultra_pressure = other.m_gas_ultra_pressure;

				m_water_static_pressure = other.m_water_static_pressure;
				m_water_static_delta_pressure = other.m_water_static_delta_pressure;
				m_oil_static_pressure = other.m_oil_static_pressure;
				m_oil_static_delta_pressure = other.m_oil_static_delta_pressure;
				m_gas_static_pressure = other.m_gas_static_pressure;
				m_gas_static_delta_pressure = other.m_gas_static_delta_pressure;

				m_water_fluid_pressure = other.m_water_fluid_pressure;
				m_oil_fluid_pressure = other.m_oil_fluid_pressure;
				m_gas_fluid_pressure = other.m_gas_fluid_pressure;

				m_Sw = other.m_Sw;
				m_So = other.m_So;
				m_Sg = other.m_Sg;

				m_COC = other.m_COC;
				m_ever_porosity = other.m_ever_porosity;
				m_litho_ultra_delta_pressure = other.m_litho_ultra_delta_pressure;
				m_temperature = other.m_temperature;
				m_paleo_heat_fluid = other.m_paleo_heat_fluid;
				m_total_matrix_density = other.m_total_matrix_density;

				//毛细管压力
				m_PcOW = other.m_PcOW;
				m_delta_PcOW = other.m_delta_PcOW; //前后时刻模拟值的插值
				m_PcGW = other.m_PcGW;
				m_delta_PcGW = other.m_delta_PcGW;
				m_PcGO = other.m_PcGO; //分别油水、气水和气油的毛管压力
				m_delta_PcGO = other.m_delta_PcGO;
			}
			void PasteToVertexSimulated(VertexSimulated &other)
			{
				other.m_water_ultra_pressure = m_water_ultra_pressure;
				other.m_water_ultra_delta_pressure = m_water_ultra_delta_pressure;
				other.m_oil_ultra_pressure = m_oil_ultra_pressure;
				other.m_gas_ultra_pressure = m_gas_ultra_pressure;

				other.m_water_static_pressure = m_water_static_pressure;
				other.m_water_static_delta_pressure = m_water_static_delta_pressure;
				other.m_oil_static_pressure = m_oil_static_pressure;
				other.m_oil_static_delta_pressure = m_oil_static_delta_pressure;
				other.m_gas_static_pressure = m_gas_static_pressure;
				other.m_gas_static_delta_pressure = m_gas_static_delta_pressure;

				other.m_water_fluid_pressure = m_water_fluid_pressure;
				other.m_oil_fluid_pressure = m_oil_fluid_pressure;
				other.m_gas_fluid_pressure = m_gas_fluid_pressure;

				other.m_Sw = m_Sw;
				other.m_So = m_So;
				other.m_Sg = m_Sg;

				other.m_COC = m_COC;
				other.m_ever_porosity = m_ever_porosity;
				other.m_litho_ultra_delta_pressure = m_litho_ultra_delta_pressure;
				other.m_temperature = m_temperature;
				other.m_paleo_heat_fluid = m_paleo_heat_fluid;
				other.m_total_matrix_density = m_total_matrix_density;

				//毛细管压力
				other.m_PcOW = m_PcOW;
				other.m_delta_PcOW = m_delta_PcOW; //前后时刻模拟值的插值
				other.m_PcGW = m_PcGW;
				other.m_delta_PcGW = m_delta_PcGW;
				other.m_PcGO = m_PcGO; //分别油水、气水和气油的毛管压力
				other.m_delta_PcGO = m_delta_PcGO;
			}
		};
		struct HyperModelBasicMesh : public AnyCGAL::Mesh3D
		{
			std::vector<double> m_subtetravolumes;
			double m_center_COC;
			double m_center_water_viscosity;
			double m_center_oil_viscosity;
			double m_center_gas_viscosity;

			double m_center_permeability;
			double m_center_porosity;
			double m_center_pore_thermal_cond;

			// for black oil model
			double m_center_sw;
			double m_center_so;
			double m_center_sg;

			double m_center_k_rw; //相对渗透率
			double m_center_k_ro;
			double m_center_k_rg;

			//
			double m_center_water_heat_capacity;
			double m_center_water_density;

			double m_center_matrix_heat_capacity;
			double m_center_matrix_density;
			double m_center_heat_qr;

			double m_center_MExpOil;
			double m_center_MExpGas;

			std::vector<double> m_center_vwater_x;
			std::vector<double> m_center_vwater_y;
			std::vector<double> m_center_vwater_z;
			std::vector<std::vector<double> > m_b;
			std::vector<std::vector<double> > m_c;
			std::vector<std::vector<double> > m_d;
			std::vector<double> m_kxx;
			std::vector<double> m_kyy;
			std::vector<double> m_kzz;

			HyperModelBasicMesh()
			{
				m_subtetravolumes.resize(6, 0);
				m_center_vwater_x.resize(6, 0);
				m_center_vwater_y.resize(6, 0);
				m_center_vwater_z.resize(6, 0);
				m_b.resize(6);
				m_c.resize(6);
				m_d.resize(6);
				for(int i = 0; i < 6; i++)
				{
					m_b[i].resize(4, 0);
					m_c[i].resize(4, 0);
					m_d[i].resize(4, 0);
				}
				m_kxx.resize(6, 0);
				m_kyy.resize(6, 0);
				m_kzz.resize(6, 0);
			}
			HyperModelBasicMesh(const HyperModelBasicMesh &other)
			{
				*this = other;
			}
			const HyperModelBasicMesh &operator=(const HyperModelBasicMesh &other)
			{
				if(this == &other)
				{
					return *this;
				}
				*((Mesh3D*)this) = *((Mesh3D*)&other);
				m_subtetravolumes = other.m_subtetravolumes;
				m_center_COC = other.m_center_COC;
				m_center_water_viscosity = other.m_center_water_viscosity;
				m_center_oil_viscosity = other.m_center_oil_viscosity;
				m_center_gas_viscosity = other.m_center_gas_viscosity;
				m_center_permeability = other.m_center_permeability;
				m_center_porosity = other.m_center_porosity;
				m_center_pore_thermal_cond = other.m_center_pore_thermal_cond;
				m_center_sw = other.m_center_sw;
				m_center_so = other.m_center_so;
				m_center_sg = other.m_center_sg;
				m_center_k_rw = other.m_center_k_rw;
				m_center_k_ro = other.m_center_k_ro;
				m_center_k_rg = other.m_center_k_rg;
				m_center_water_heat_capacity = other.m_center_water_heat_capacity;
				m_center_water_density = other.m_center_water_density;
				m_center_matrix_heat_capacity = other.m_center_matrix_heat_capacity;
				m_center_matrix_density = other.m_center_matrix_density;
				m_center_heat_qr = other.m_center_heat_qr;
				m_center_MExpOil = other.m_center_MExpOil;
				m_center_MExpGas = other.m_center_MExpGas;

				m_center_vwater_x = other.m_center_vwater_x;
				m_center_vwater_y = other.m_center_vwater_y;
				m_center_vwater_z = other.m_center_vwater_z;
				m_b = other.m_b;
				m_c = other.m_c;
				m_d = other.m_d;
				m_kxx = other.m_kxx;
				m_kyy = other.m_kyy;
				m_kzz = other.m_kzz;
				return *this;
			}
			int GetSerializeDataLength()
			{
				int curSize = 0;
				// Mesh3D
				curSize += Mesh3D::GetSerializeDataLength();
				curSize += (sizeof(int) + m_subtetravolumes.size() * sizeof(double));//std::vector<double> m_subtetravolumes;
				curSize += sizeof(double);//double m_center_COC;
				curSize += sizeof(double);//double m_center_water_viscosity;
				curSize += sizeof(double);//double m_center_oil_viscosity;
				curSize += sizeof(double);//double m_center_gas_viscosity;
				curSize += sizeof(double);//double m_center_permeability;
				curSize += sizeof(double);//double m_center_porosity;
				curSize += sizeof(double);//double m_center_pore_thermal_cond;
				curSize += sizeof(double);//double m_center_sw;
				curSize += sizeof(double);//double m_center_so;
				curSize += sizeof(double);//double m_center_sg;
				curSize += sizeof(double);//double m_center_k_rw;
				curSize += sizeof(double);//double m_center_k_ro;
				curSize += sizeof(double);//double m_center_k_rg;
				curSize += sizeof(double);//double m_center_water_heat_capacity;
				curSize += sizeof(double);//double m_center_water_density;
				curSize += sizeof(double);//double m_center_matrix_heat_capacity;
				curSize += sizeof(double);//double m_center_matrix_density;
				curSize += sizeof(double);//double m_center_heat_qr;
				curSize += sizeof(double);//double m_center_MExpOil;
				curSize += sizeof(double);//double m_center_MExpGas;
				curSize += (sizeof(int) + m_center_vwater_x.size() * sizeof(double));//std::vector<double> m_center_vwater_x;
				curSize += (sizeof(int) + m_center_vwater_y.size() * sizeof(double));//std::vector<double> m_center_vwater_y;
				curSize += (sizeof(int) + m_center_vwater_z.size() * sizeof(double));//std::vector<double> m_center_vwater_z;
				curSize += sizeof(int);//std::vector<std::vector<double> > m_b;
				for(int i = 0; i < m_b.size(); i++)
				{
					curSize += (sizeof(int) + m_b[i].size() * sizeof(double));
				}
				curSize += sizeof(int);//std::vector<std::vector<double> > m_c;
				for(int i = 0; i < m_c.size(); i++)
				{
					curSize += (sizeof(int) + m_c[i].size() * sizeof(double));
				}
				curSize += sizeof(int);//std::vector<std::vector<double> > m_d;
				for(int i = 0; i < m_d.size(); i++)
				{
					curSize += (sizeof(int) + m_d[i].size() * sizeof(double));
				}
				curSize += (sizeof(int) + m_kxx.size() * sizeof(double));//std::vector<double> m_kxx;
				curSize += (sizeof(int) + m_kyy.size() * sizeof(double));//std::vector<double> m_kyy;
				curSize += (sizeof(int) + m_kzz.size() * sizeof(double));//std::vector<double> m_kzz;
				return curSize;
			}
			void SerializeData(char* &data)
			{
				// Mesh3D
				Mesh3D::SerializeData(data);
				int subtetravolumessize = m_subtetravolumes.size();
				memcpy(data, &subtetravolumessize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < subtetravolumessize; i++)
				{
					memcpy(data, &(m_subtetravolumes[i]), sizeof(double));data += sizeof(double);
				}
				memcpy(data, &m_center_COC, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_water_viscosity, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_oil_viscosity, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_gas_viscosity, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_permeability, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_porosity, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_pore_thermal_cond, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_sw, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_so, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_sg, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_k_rw, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_k_ro, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_k_rg, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_water_heat_capacity, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_water_density, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_matrix_heat_capacity, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_matrix_density, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_heat_qr, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_MExpOil, sizeof(double));data += sizeof(double);
				memcpy(data, &m_center_MExpGas, sizeof(double));data += sizeof(double);
				int center_vwater_xsize = m_center_vwater_x.size();
				memcpy(data, &center_vwater_xsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < center_vwater_xsize; i++)
				{
					memcpy(data, &(m_center_vwater_x[i]), sizeof(double));data += sizeof(double);
				}
				int center_vwater_ysize = m_center_vwater_y.size();
				memcpy(data, &center_vwater_ysize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < center_vwater_ysize; i++)
				{
					memcpy(data, &(m_center_vwater_y[i]), sizeof(double));data += sizeof(double);
				}
				int center_vwater_zsize = m_center_vwater_z.size();
				memcpy(data, &center_vwater_zsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < center_vwater_zsize; i++)
				{
					memcpy(data, &(m_center_vwater_z[i]), sizeof(double));data += sizeof(double);
				}
				int bsize = m_b.size();
				memcpy(data, &bsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < bsize; i++)
				{
					int bisize = m_b[i].size();
					memcpy(data, &bisize, sizeof(int));data += sizeof(int);
					for(int j = 0; j < bisize; j++)
					{
						memcpy(data, &(m_b[i][j]), sizeof(double));data += sizeof(double);
					}
				}
				int csize = m_c.size();
				memcpy(data, &csize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < csize; i++)
				{
					int cisize = m_c[i].size();
					memcpy(data, &cisize, sizeof(int));data += sizeof(int);
					for(int j = 0; j < cisize; j++)
					{
						memcpy(data, &(m_c[i][j]), sizeof(double));data += sizeof(double);
					}
				}
				int dsize = m_d.size();
				memcpy(data, &dsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < dsize; i++)
				{
					int disize = m_d[i].size();
					memcpy(data, &disize, sizeof(int));data += sizeof(int);
					for(int j = 0; j < disize; j++)
					{
						memcpy(data, &(m_d[i][j]), sizeof(double));data += sizeof(double);
					}
				}
				int kxxsize = m_kxx.size();
				memcpy(data, &kxxsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < kxxsize; i++)
				{
					memcpy(data, &(m_kxx[i]), sizeof(double));data += sizeof(double);
				}
				int kyysize = m_kyy.size();
				memcpy(data, &kyysize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < kyysize; i++)
				{
					memcpy(data, &(m_kyy[i]), sizeof(double));data += sizeof(double);
				}
				int kzzsize = m_kzz.size();
				memcpy(data, &kzzsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < kzzsize; i++)
				{
					memcpy(data, &(m_kzz[i]), sizeof(double));data += sizeof(double);
				}
			}
			void RestoreSerializeData(char* &data)
			{
				// Mesh3D
				Mesh3D::RestoreSerializeData(data);
				m_subtetravolumes.clear();
				int subtetravolumessize;
				memcpy(&subtetravolumessize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < subtetravolumessize; i++)
				{
					double temp;
					memcpy(&temp, data, sizeof(double));data += sizeof(double);
					m_subtetravolumes.push_back(temp);
				}
				memcpy(&m_center_COC, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_water_viscosity, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_oil_viscosity, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_gas_viscosity, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_permeability, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_porosity, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_pore_thermal_cond, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_sw, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_so, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_sg, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_k_rw, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_k_ro, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_k_rg, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_water_heat_capacity, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_water_density, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_matrix_heat_capacity, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_matrix_density, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_heat_qr, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_MExpOil, data, sizeof(double));data += sizeof(double);
				memcpy(&m_center_MExpGas, data, sizeof(double));data += sizeof(double);
				m_center_vwater_x.clear();
				int center_vwater_xsize;
				memcpy(&center_vwater_xsize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < center_vwater_xsize; i++)
				{
					double temp;
					memcpy(&temp, data, sizeof(double));data += sizeof(double);
					m_center_vwater_x.push_back(temp);
				}
				m_center_vwater_y.clear();
				int center_vwater_ysize;
				memcpy(&center_vwater_ysize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < center_vwater_ysize; i++)
				{
					double temp;
					memcpy(&temp, data, sizeof(double));data += sizeof(double);
					m_center_vwater_y.push_back(temp);
				}
				m_center_vwater_z.clear();
				int center_vwater_zsize;
				memcpy(&center_vwater_zsize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < center_vwater_zsize; i++)
				{
					double temp;
					memcpy(&temp, data, sizeof(double));data += sizeof(double);
					m_center_vwater_z.push_back(temp);
				}
				int bsize;
				memcpy(&bsize, data, sizeof(int));data += sizeof(int);
				m_b.resize(bsize);
				for(int i = 0; i < bsize; i++)
				{
					int bisize;
					memcpy(&bisize, data, sizeof(int));data += sizeof(int);
					m_b[i].resize(bisize);
					for(int j = 0; j < bisize; j++)
					{
						memcpy(&(m_b[i][j]), data, sizeof(double));data += sizeof(double);
					}
				}
				int csize;
				memcpy(&csize, data, sizeof(int));data += sizeof(int);
				m_c.resize(csize);
				for(int i = 0; i < csize; i++)
				{
					int cisize;
					memcpy(&cisize, data, sizeof(int));data += sizeof(int);
					m_c[i].resize(cisize);
					for(int j = 0; j < cisize; j++)
					{
						memcpy(&(m_c[i][j]), data, sizeof(double));data += sizeof(double);
					}
				}
				int dsize;
				memcpy(&dsize, data, sizeof(int));data += sizeof(int);
				m_d.resize(dsize);
				for(int i = 0; i < dsize; i++)
				{
					int disize;
					memcpy(&disize, data, sizeof(int));data += sizeof(int);
					m_d[i].resize(disize);
					for(int j = 0; j < disize; j++)
					{
						memcpy(&(m_d[i][j]), data, sizeof(double));data += sizeof(double);
					}
				}
				m_kxx.clear();
				int kxxsize;
				memcpy(&kxxsize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < kxxsize; i++)
				{
					double temp;
					memcpy(&temp, data, sizeof(double));data += sizeof(double);
					m_kxx.push_back(temp);
				}
				m_kyy.clear();
				int kyysize;
				memcpy(&kyysize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < kyysize; i++)
				{
					double temp;
					memcpy(&temp, data, sizeof(double));data += sizeof(double);
					m_kyy.push_back(temp);
				}
				m_kzz.clear();
				int kzzsize;
				memcpy(&kzzsize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < kzzsize; i++)
				{
					double temp;
					memcpy(&temp, data, sizeof(double));data += sizeof(double);
					m_kzz.push_back(temp);
				}
			}
			void CopyFromMeshSimulated(MeshSimulated &other)
			{
				*((Mesh3D*)this) = *((Mesh3D*)&other);
				m_subtetravolumes = other.m_subtetravolumes;
				m_center_COC = other.m_center_COC;
				m_center_water_viscosity = other.m_center_water_viscosity;
				m_center_oil_viscosity = other.m_center_oil_viscosity;
				m_center_gas_viscosity = other.m_center_gas_viscosity;
				m_center_permeability = other.m_center_permeability;
				m_center_porosity = other.m_center_porosity;
				m_center_pore_thermal_cond = other.m_center_pore_thermal_cond;
				m_center_sw = other.m_center_sw;
				m_center_so = other.m_center_so;
				m_center_sg = other.m_center_sg;
				m_center_k_rw = other.m_center_k_rw;
				m_center_k_ro = other.m_center_k_ro;
				m_center_k_rg = other.m_center_k_rg;
				m_center_water_heat_capacity = other.m_center_water_heat_capacity;
				m_center_water_density = other.m_center_water_density;
				m_center_matrix_heat_capacity = other.m_center_matrix_heat_capacity;
				m_center_matrix_density = other.m_center_matrix_density;
				m_center_heat_qr = other.m_center_heat_qr;
				m_center_MExpOil = other.m_center_MExpOil;
				m_center_MExpGas = other.m_center_MExpGas;

				m_center_vwater_x = other.m_center_vwater_x;
				m_center_vwater_y = other.m_center_vwater_y;
				m_center_vwater_z = other.m_center_vwater_z;
				m_b = other.m_b;
				m_c = other.m_c;
				m_d = other.m_d;
				m_kxx = other.m_kxx;
				m_kyy = other.m_kyy;
				m_kzz = other.m_kzz;
			}
			void PasteToMeshSimulated(MeshSimulated &other)
			{
				other.m_subtetravolumes = m_subtetravolumes;
				other.m_center_COC = m_center_COC;
				other.m_center_water_viscosity = m_center_water_viscosity;
				other.m_center_oil_viscosity = m_center_oil_viscosity;
				other.m_center_gas_viscosity = m_center_gas_viscosity;
				other.m_center_permeability = m_center_permeability;
				other.m_center_porosity = m_center_porosity;
				other.m_center_pore_thermal_cond = m_center_pore_thermal_cond;
				other.m_center_sw = m_center_sw;
				other.m_center_so = m_center_so;
				other.m_center_sg = m_center_sg;
				other.m_center_k_rw = m_center_k_rw;
				other.m_center_k_ro = m_center_k_ro;
				other.m_center_k_rg = m_center_k_rg;
				other.m_center_water_heat_capacity = m_center_water_heat_capacity;
				other.m_center_water_density = m_center_water_density;
				other.m_center_matrix_heat_capacity = m_center_matrix_heat_capacity;
				other.m_center_matrix_density = m_center_matrix_density;
				other.m_center_heat_qr = m_center_heat_qr;
				other.m_center_MExpOil = m_center_MExpOil;
				other.m_center_MExpGas = m_center_MExpGas;

				other.m_center_vwater_x = m_center_vwater_x;
				other.m_center_vwater_y = m_center_vwater_y;
				other.m_center_vwater_z = m_center_vwater_z;
				other.m_b = m_b;
				other.m_c = m_c;
				other.m_d = m_d;
				other.m_kxx = m_kxx;
				other.m_kyy = m_kyy;
				other.m_kzz = m_kzz;
			}
		};
		struct HyperModelBasic
		{
			//
			int m_which_simulation_step;
			double m_delta_time;
			bool m_isretry;

			//
			int m_tophorizon;
			std::vector<bool> m_horizonOK;
			std::vector<std::vector<int> > m_invalidptpos;
			std::vector<HyperModelBasicVertex*> m_vertexs;
			std::vector<int> m_eachlayervertexcount;
			std::vector<HyperModelBasicMesh*> m_meshes;
			std::vector<bool> m_vertexhasvalidmeshes;
			
			//
			int m_totalvertexcount;
			int m_layervertexcount;
			std::vector<std::vector<int> > m_all_to_valid_offset;
			HyperModelBasic()
			{
			}
			~HyperModelBasic()
			{
				Release();
			}
			HyperModelBasic(const HyperModelBasic &other)
			{
				*this = other;
			}
			const HyperModelBasic &operator=(const HyperModelBasic &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_which_simulation_step = other.m_which_simulation_step;
				m_delta_time = other.m_delta_time;
				m_isretry = other.m_isretry;
				m_tophorizon = other.m_tophorizon;
				m_horizonOK = other.m_horizonOK;
				m_invalidptpos = other.m_invalidptpos;
				m_vertexs = other.m_vertexs;
				m_eachlayervertexcount = other.m_eachlayervertexcount;
				m_meshes = other.m_meshes;
				m_vertexhasvalidmeshes = other.m_vertexhasvalidmeshes;
				return *this;
			}
			void Release()
			{
				for(int i = 0; i < m_vertexs.size(); i++)
					delete m_vertexs[i];
				m_vertexs.clear();
				for(int i = 0; i < m_meshes.size(); i++)
					delete m_meshes[i];
				m_meshes.clear();
			}
			int GetSerializeDataLength()
			{
				int curSize = 0;
				curSize += sizeof(int);//int m_which_simulation_step;
				curSize += sizeof(double);//double m_delta_time;
				curSize += sizeof(bool);//bool m_isretry;
				curSize += sizeof(int);//int m_tophorizon;
				curSize += (sizeof(int) + m_horizonOK.size() * sizeof(bool));//std::vector<bool> m_horizonOK;
				curSize += sizeof(int);//std::vector<std::vector<int> > m_invalidptpos;
				for(int i = 0; i < m_invalidptpos.size(); i++)
				{
					curSize += (sizeof(int) + m_invalidptpos[i].size() * sizeof(int));
				}
				curSize += sizeof(int);//std::vector<HyperModelBasicVertex*> m_vertexs;
				for(int i = 0; i < m_vertexs.size(); i++)
				{
					curSize += m_vertexs[i]->GetSerializeDataLength();
				}
				curSize += (sizeof(int) + m_eachlayervertexcount.size() * sizeof(int));//std::vector<int> m_eachlayervertexcount;
				curSize += sizeof(int);//std::vector<HyperModelBasicMesh*> m_meshes;
				for(int i = 0; i < m_meshes.size(); i++)
				{
					curSize += m_meshes[i]->GetSerializeDataLength();
				}
				curSize += (sizeof(int) + m_vertexhasvalidmeshes.size() * sizeof(bool));//std::vector<bool> m_vertexhasvalidmeshes;
				curSize += sizeof(int);//int m_totalvertexcount;
				curSize += sizeof(int);//int m_layervertexcount;
				curSize += sizeof(int);//std::vector<std::vector<int> > m_all_to_valid_offset;
				for(int i = 0; i < m_all_to_valid_offset.size(); i++)
				{
					curSize += (sizeof(int) + m_all_to_valid_offset[i].size() * sizeof(int));
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
				memcpy(data, &m_which_simulation_step, sizeof(int));data += sizeof(int);
				memcpy(data, &m_delta_time, sizeof(double));data += sizeof(double);
				memcpy(data, &m_isretry, sizeof(bool));data += sizeof(bool);
				memcpy(data, &m_tophorizon, sizeof(int));data += sizeof(int);
				int horizonOKsize = m_horizonOK.size();
				memcpy(data, &horizonOKsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < horizonOKsize; i++)
				{
					memcpy(data, &(m_horizonOK[i]), sizeof(bool));data += sizeof(bool);
				}
				int invalidptpossize = m_invalidptpos.size();
				memcpy(data, &invalidptpossize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < invalidptpossize; i++)
				{
					int invalidptposisize = m_invalidptpos[i].size();
					memcpy(data, &invalidptposisize, sizeof(int));data += sizeof(int);
					for(int j = 0; j < invalidptposisize; j++)
					{
						memcpy(data, &(m_invalidptpos[i][j]), sizeof(int));data += sizeof(int);
					}
				}
				int vertexssize = m_vertexs.size();
				memcpy(data, &vertexssize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < vertexssize; i++)
				{
					m_vertexs[i]->SerializeData(data);
				}
				int eachlayervertexcountsize = m_eachlayervertexcount.size();
				memcpy(data, &eachlayervertexcountsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < eachlayervertexcountsize; i++)
				{
					memcpy(data, &(m_eachlayervertexcount[i]), sizeof(int));data += sizeof(int);
				}
				int meshessize = m_meshes.size();
				memcpy(data, &meshessize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < meshessize; i++)
				{
					m_meshes[i]->SerializeData(data);
				}
				int vertexhasvalidmeshessize = m_vertexhasvalidmeshes.size();
				memcpy(data, &vertexhasvalidmeshessize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < vertexhasvalidmeshessize; i++)
				{
					memcpy(data, &(m_vertexhasvalidmeshes[i]), sizeof(bool));data += sizeof(bool);
				}
				memcpy(data, &m_totalvertexcount, sizeof(int));data += sizeof(int);
				memcpy(data, &m_layervertexcount, sizeof(int));data += sizeof(int);
				int all_to_valid_offsetsize = m_all_to_valid_offset.size();
				memcpy(data, &all_to_valid_offsetsize, sizeof(int));data += sizeof(int);
				for(int i = 0; i < all_to_valid_offsetsize; i++)
				{
					int all_to_valid_offsetisize = m_all_to_valid_offset[i].size();
					memcpy(data, &all_to_valid_offsetisize, sizeof(int));data += sizeof(int);
					for(int j = 0; j < all_to_valid_offsetisize; j++)
					{
						memcpy(data, &(m_all_to_valid_offset[i][j]), sizeof(int));data += sizeof(int);
					}
				}
			}
			void RestoreSerializeData(char* &data)
			{
				memcpy(&m_which_simulation_step, data, sizeof(int));data += sizeof(int);
				memcpy(&m_delta_time, data, sizeof(double));data += sizeof(double);
				memcpy(&m_isretry, data, sizeof(bool));data += sizeof(bool);
				memcpy(&m_tophorizon, data, sizeof(int));data += sizeof(int);
				m_horizonOK.clear();
				int horizonOKsize;
				memcpy(&horizonOKsize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < horizonOKsize; i++)
				{
					bool temp;
					memcpy(&temp, data, sizeof(bool));data += sizeof(bool);
					m_horizonOK.push_back(temp);
				}
				int invalidptpossize;
				memcpy(&invalidptpossize, data, sizeof(int));data += sizeof(int);
				m_invalidptpos.resize(invalidptpossize);
				for(int i = 0; i < invalidptpossize; i++)
				{
					int invalidptposisize;
					memcpy(&invalidptposisize, data, sizeof(int));data += sizeof(int);
					m_invalidptpos[i].resize(invalidptposisize);
					for(int j = 0; j < invalidptposisize; j++)
					{
						memcpy(&(m_invalidptpos[i][j]), data, sizeof(int));data += sizeof(int);
					}
				}
				m_vertexs.clear();
				int vertexssize;
				memcpy(&vertexssize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < vertexssize; i++)
				{
					HyperModelBasicVertex* temp = new HyperModelBasicVertex;
					temp->RestoreSerializeData(data);
					m_vertexs.push_back(temp);
				}
				m_eachlayervertexcount.clear();
				int eachlayervertexcountsize;
				memcpy(&eachlayervertexcountsize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < eachlayervertexcountsize; i++)
				{
					int temp;
					memcpy(&temp, data, sizeof(int));data += sizeof(int);
					m_eachlayervertexcount.push_back(temp);
				}
				m_meshes.clear();
				int meshessize;
				memcpy(&meshessize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < meshessize; i++)
				{
					HyperModelBasicMesh* temp = new HyperModelBasicMesh;
					temp->RestoreSerializeData(data);
					m_meshes.push_back(temp);
				}
				m_vertexhasvalidmeshes.clear();
				int vertexhasvalidmeshessize;
				memcpy(&vertexhasvalidmeshessize, data, sizeof(int));data += sizeof(int);
				for(int i = 0; i < vertexhasvalidmeshessize; i++)
				{
					bool temp;
					memcpy(&temp, data, sizeof(bool));data += sizeof(bool);
					m_vertexhasvalidmeshes.push_back(temp);
				}
				memcpy(&m_totalvertexcount, data, sizeof(int));data += sizeof(int);
				memcpy(&m_layervertexcount, data, sizeof(int));data += sizeof(int);
				int all_to_valid_offsetsize;
				memcpy(&all_to_valid_offsetsize, data, sizeof(int));data += sizeof(int);
				m_all_to_valid_offset.resize(all_to_valid_offsetsize);
				for(int i = 0; i < all_to_valid_offsetsize; i++)
				{
					int all_to_valid_offsetisize;
					memcpy(&all_to_valid_offsetisize, data, sizeof(int));data += sizeof(int);
					m_all_to_valid_offset[i].resize(all_to_valid_offsetisize);
					for(int j = 0; j < all_to_valid_offsetisize; j++)
					{
						memcpy(&(m_all_to_valid_offset[i][j]), data, sizeof(int));data += sizeof(int);
					}
				}
			}
		};

	public:
		//
		//
		//
		CAnyHyperBasinSimulator();
		~CAnyHyperBasinSimulator();
		
	public:
		//
		//	geological model given by parent class MakeMesh
		//
		void ReleaseBatch();

		//
		// bury history roughly but accurately
		//
		bool RecoverMaxBurialDepth();
		void RecoverOneMaxBurialDepth(DirectionVertexBatch &onedirectionbatch);
		void DoRecoverMaxBurialDepth(std::vector<BurialHistorySimulated> &burialhistories);

		//
		//
		//
		bool PrepareBatchesSimulated_OnlyMalloc();
		bool PrepareBatchesSimulatedStep1();
		bool PrepareBatchesSimulatedStep2();
		bool DoPrepareBatchesSimulatedStep2(bool iscreatesimulatedata);
		bool PrepareBatchesSimulatedStep3();
		bool PrepareBatchesSimulatedStep4();
		bool DoPrepareBatchesSimulatedStep4(bool iscreatesimulatedata);
		bool PrepareBatchesSimulatedStep5();
		bool PrepareBatchesSimulatedStep6();

		// new functions for job nodes' schedule as more parallel as possible
		// ..
		bool MakeSimulation_Begin();
		bool MakeSimulation_OneStep_Prepare(); // onestep1
		// overpressure
		bool MakeSimulation_OneStep_Burial_Overpressure_Prepare(); // onestep2-1 - overpressure case
		bool MakeSimulation_OneStep_Burial_Overpressure_FE_Prepare(); // onestep2-2 - overpressure case
		bool MakeSimulation_OneStep_Burial_Overpressure_FE(); // onestep2-2 - overpressure case
		bool MakeSimulation_OneStep_Burial_Overpressure_Threephase_FE(); // onestep2-2 - overpressure case
		bool MakeSimulation_OneStep_Burial_Overpressure_Saturationwater_FE(); // onestep2-2 - overpressure case
		bool MakeSimulation_OneStep_Burial_Overpressure_Saturationoil_FE(); // onestep2-2 - overpressure case
		bool MakeSimulation_OneStep_Burial_Overpressure_FE_IsOver(); // onestep2-2 - overpressure case
		bool MakeSimulation_OneStep_Burial_Overpressure_Done(); 

		// thermal
		bool MakeSimulation_OneStep_Thermal_Transit_Prepare(); // onestep2 - transit case
		bool MakeSimulation_OneStep_Thermal_Transit_FE_Prepare(); // onestep2 - transit case
		bool MakeSimulation_OneStep_Thermal_Transit_FE(); // onestep2 - transit case
		bool MakeSimulation_OneStep_Thermal_Transit_FE_IsOver(); // onestep2 - transit case
		bool MakeSimulation_OneStep_Thermal_Transit_Done(); 

		bool MakeSimulation_OneStep_Pressure_Theraml_FE_IsOver(); 

		// steady
		bool MakeSimulation_OneStep_Thermal_Steady(); // dyHeatSimulat
		bool MakeSimulation_OneStep_End();
		bool MakeSimulation_OneStep_IsOver();
		bool MakeSimulation_Exchange_Block2Model(); //single2union
		bool MakeSimulation_Exchange_Model2Block();	// union2single
		bool MakeSimulation_IsOver();
		bool MakeSimulation_SourceRock();
		bool MakeSimulation_Percolation();

		// 
		void MakeOneSimulationStep1();
		void MakeOneSimulationEnd();
		bool MakeOneSimulationRockSource();
		void MakeOneSimulationPercolation();
		void DoMakeOverpressureSimulationStep1();
		double DoMakeOverpressureSimulationStep2_1();
		double DoMakeOverpressureSimulationStep2_2();
		double DoMakeOverpressureSimulationStep2_2_Threephase();
		double DoMakeOverpressureSimulationStep2_2_Saturationwater();
		double DoMakeOverpressureSimulationStep2_2_Saturationoil();
		void DoMakeOverpressureSimulationStep3();
		double DoMakeOverpressureSimulationStep4();
		void DoMakeTransitHeatSimulationStep1();
		double DoMakeTransitHeatSimulationStep2();
		double DoMakeTransitHeatSimulationStep2_1();
		double DoMakeTransitHeatSimulationStep2_2();
		void DoMakeTransitHeatSimulationStep3();
		void DoMakeSteadyHeatSimulation();

		//
		//
		//
		void ExtractBurialHistory(CGeoPoint<double> &position, int colorsource, std::vector<std::vector<VertexSimulated> > &horizons, std::vector<int> &horizonypes);
		void ExtractBurialHistory(std::vector<CGeoPoint<double> > &positions, int colorsource, int simulatedlayercount, std::vector<std::vector<VertexSimulated> > &horizons, std::vector<int> &horizonypes);
		void ExtractBurialHistory(std::vector<int> &vertexoffsets, int colorsource, int simulatedlayercount, std::vector<std::vector<VertexSimulated> > &horizons, std::vector<int> &horizonypes);
		void ModifyVertexColor(int offseti, int offsetj, int offsetk, int colorsource, int bottomortop);

		//
		// for finite element model
		//
		void GetJobBlockVertexes(std::vector<VertexSimulated*> &jobblockvertexes, int whichsimulationstep, int whichhorizon, int bottomortop);
		void GetJobBlockMeshes(std::vector<MeshSimulated*> &jobblockmeshes, std::vector<int> &jobblockoffsets, int whichsimulationstep, int whichhorizon);
		void GetHyperModelBasicVertex(std::vector<HyperModelBasicVertex> &modelbasicvertexes, int whichsimulationstep, int whichhorizon, int bottomortop);
		void GetHyperModelBasicMesh(std::vector<HyperModelBasicMesh> &modelbasicmeshes, int whichsimulationstep, int whichhorizon);
		void GetJobBlockHyperModelBasicVertex(std::vector<HyperModelBasicVertex> &jobblockmodelbasicvertexes, int whichsimulationstep, int whichhorizon, int bottomortop);
		void GetJobBlockHyperModelBasicMesh(std::vector<HyperModelBasicMesh> &jobblockmodelbasicmeshes, std::vector<int> &jobblockoffsets, int whichsimulationstep, int whichhorizon);
		void GetHorizonOKpara(int whichsimulationstep, int whichhorizon, int &initialmeshnumber, int &geological_event, bool &is_eroded);
		void GetVertexCount(int &vertexcount, int whichsimulationstep, int whichhorizon);
		void GetMeshCount(int &meshcount, int whichsimulationstep, int whichhorizon);
		bool IsHorizonOK(int whichhorizon);
		bool IsHorizonOK(int whichhorizon, std::vector<bool> &blockoks, std::vector<bool> &refineoks, bool &ownok);
		void GetTrueTop(std::vector<int> &blocktops, std::vector<int> &refinetops, int &owntop);
		void GetHyperModelBasic(HyperModelBasic &modelbasic);
		void SaveCurrentStepData();
		
		// reset model
		void MeshidJobBlockToSingle(int simulatoroffset, long &vertexid);
		void MeshidBlockToSingle(int simulatoroffset, long &vertexid);
		void MeshidSingleToUnion(int simulatoroffset, long &vertexid);
		void RecoverMeshidUnionToSingle(int &tophorizon);
		void MeshidUnionToSingle(int simulatoroffset, long &vertexid);
		void MeshidSingleToJobBlock( int simulatoroffset, long &vertexid);
		void MeshidSingleToBlock( int simulatoroffset, long &vertexid);

		// write back model
		void GetVertexValid(std::vector<bool> &vertexvalid, int whichsimulationstep, int whichhorizon, int bottomortop);
		void GetMeshValid(std::vector<bool> &meshvalid, int whichsimulationstep, int whichhorizon);
		void GetJobBlockVertexValid(std::vector<bool> &vertexvalid, int whichsimulationstep, int whichhorizon, int bottomortop);
		void GetJobBlockMeshValid(std::vector<bool> &meshvalid, int whichsimulationstep, int whichhorizon);
		void UpdateFromModelBasicVertex(std::vector<HyperModelBasicVertex> &modelbasicvertexes, int &curvertexoffset, int whichsimulationstep, int whichhorizon, int bottomortop, bool isrefine);
		void UpdateJobBlockFromModelBasicVertex(std::vector<HyperModelBasicVertex> &modelbasicvertexes, int &curvertexoffset, int whichsimulationstep, int whichhorizon, int bottomortop, bool isrefine);
		void DoUpdateJobBlockFromModelBasicVertex(std::vector<HyperModelBasicVertex> &modelbasicvertexes, std::vector<int> &validoffset, int parentcols, int whichsimulationstep, int whichhorizon, int bottomortop);
		void UpdateFromModelBasicMesh(std::vector<HyperModelBasicMesh> &modelbasicmeshes, int &curmeshoffset, std::vector<bool> &meshvalid, int whichsimulationstep, int whichhorizon);
		void UpdateJobBlockFromModelBasicMesh(std::vector<HyperModelBasicMesh> &modelbasicmeshes, int &curmeshoffset, std::vector<bool> &meshvalid, int whichsimulationstep, int whichhorizon);
		void LoadCurrentStepData();
		void DoWriteBackData(HyperModelBasic &modelbasic);
		void DoUpdateTemperature(int whichsimulationstep, int truetop);
		void DoUpdateTemperature();

		// model functions
		void CutSimulatorToBlock(CAnyHyperMesh *simulator, std::vector<CAnyHyperMesh*> &blocksimulators);
		void CutSimulatorToJobBlock(std::vector<CAnyHyperBasinSimulator*> &jobblocksimulators, int jobblockrows, int jobblockcols);
		bool SaveToFile();
		bool LoadFromFile();
		int GetSerializeDataLength();
		void SerializeData(char* &data);
		void RestoreSerializeData(char* &data);
		int GetSerializeDataLength_GeologicalLithology(CAnyBurialHistoryPlot::GeologicalLithology &tmp);
		void SerializeData_GeologicalLithology(CAnyBurialHistoryPlot::GeologicalLithology &tmp, char* &data);
		void RestoreSerializeData_GeologicalLithology(CAnyBurialHistoryPlot::GeologicalLithology &tmp, char* &data);

	public:

		// deprecated:
		// face map to connect litho parameter lib
		CAnyBurialHistoryPlot::GeologicalLithologyMap m_lithmap;

		//face definition
		FaceDefinitions m_face_definitions;
		WaterDepthDefinitions m_waterdepthdefinitions;
		SedimentWaterInterfaceTemperatureDefinitions m_sedimentwaterinterfacedefinitions;
		HeatFlowDefinitions m_heatflowdefinitions;

		// process or simulation
		//
		int m_simulation_method;
		CHorizonBatchSimulated ****m_horizon_batches_simulated;
		CHorizonBatchDistributed m_batches_distributed;
		int m_steps_simulated;
		int m_aRoType;
		int m_aPetroGenStyle;

		// for simulator group 
		std::vector<CAnyHyperBasinSimulator*> m_refined_simulators;
		std::vector<CAnyHyperBasinSimulator*> m_block_simulators;
		std::vector<CAnyHyperBasinSimulator*> m_jobblock_simulators;//second level

		// middle variables
		BatchSimulatedOrder *m_simulation_orders;
		std::vector<int> m_simulation_events;
		long m_whichsimulationstep;
		int m_allsimulationsteps;

		int m_simulationLoopNumber;
		double m_wcPoroBackup;
		int m_pressure_LoopNumber;
		int m_heat_LoopNumber;
		bool m_pressure_FE_needloop;
		bool m_heat_FE_needloop;

		// for log tracing
		long m_solution_idx;
		long m_block_idx;
	};
}


#endif

