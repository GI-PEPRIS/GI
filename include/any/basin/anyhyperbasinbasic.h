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
#ifndef __ANYBASIN_HYPER_BASIN_BASIC_H__
#define __ANYBASIN_HYPER_BASIN_BASIC_H__

#include "any/cgal/anyhypermeshbasic.h"
using namespace AnyCGAL;

//
namespace AnyBasin
{
	//
	//
	//
	enum MethodSimulated
	{
		MS_Unknown,
		MS_Steady_Heat,
		MS_Transit_Heat,
		MS_Overpressure_Only_Water_Phase,
		MS_Overpressure_Black_Oil_Model_No_Phase_Transfer,
		MS_Max
	};

	// border condition data
	struct BorderVariable
	{
		double m_paleo_water_depth;
		double m_paleo_surface_temperature;
		double m_paleo_heat_fluid;
		BorderVariable()
		{
			m_paleo_water_depth = 0;
			m_paleo_surface_temperature = 0;
			m_paleo_heat_fluid = 0;
		}
		BorderVariable(const BorderVariable &other)
		{
			*this = other;
		}
		const BorderVariable &operator=(const BorderVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_paleo_water_depth = other.m_paleo_water_depth;
			m_paleo_surface_temperature = other.m_paleo_surface_temperature;
			m_paleo_heat_fluid = other.m_paleo_heat_fluid;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_paleo_water_depth;
			curSize += sizeof(double);//double m_paleo_surface_temperature;
			curSize += sizeof(double);//double m_paleo_heat_fluid;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_paleo_water_depth, sizeof(double));data += sizeof(double);
			memcpy(data, &m_paleo_surface_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_paleo_heat_fluid, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_paleo_water_depth, data, sizeof(double));data += sizeof(double);
			memcpy(&m_paleo_surface_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_paleo_heat_fluid, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, BorderVariable &bordervariable)
		{
			os << "\r\n>>>>>>>>>>>>>>>BorderVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- m_paleo_water_depth:" << bordervariable.m_paleo_water_depth;
			os << "\r\n---- ---- ---- m_paleo_surface_temperature:" << bordervariable.m_paleo_surface_temperature;
			os << "\r\n---- ---- ---- m_paleo_heat_fluid:" << bordervariable.m_paleo_heat_fluid;
			return os;
		}
	};

	// pvt data
	struct PVTVariable
	{
		//
		double m_middle_temperature;	//
		double m_temperature;			// �¶�

		//������Щѹ���ĵ�λ�����ù��ʵ�λ�ƣ���˹��
		//
		double m_water_fluid_pressure;		// pt,����ѹ��
		double m_water_fluid_middle_pressure;

		double m_water_static_pressure;		// staticpt,������ѹ��
		double m_water_static_middle_pressure;
		double m_water_static_delta_pressure;

		double m_oil_fluid_pressure;		// pt,����ѹ��
		double m_oil_fluid_middle_pressure;
	
		double m_oil_static_pressure;		// staticpt,������ѹ��
		double m_oil_static_middle_pressure;
		double m_oil_static_delta_pressure;

		double m_gas_fluid_pressure;		// pt,����ѹ��
		double m_gas_fluid_middle_pressure;

		double m_gas_static_pressure;		// staticpt,������ѹ��
		double m_gas_static_middle_pressure;
		double m_gas_static_delta_pressure;
		//
		//
		//��Ϊ�������в��͵ײ�������ھ�ˮ����
		double m_water_ultra_pressure;		// ut,���峬ѹ
		double m_water_ultra_middle_pressure;
		double m_water_ultra_delta_pressure;

		double m_oil_ultra_pressure;		// ut,���峬ѹ
		double m_oil_ultra_middle_pressure;

		double m_gas_ultra_pressure;		// ut,���峬ѹ
		double m_gas_ultra_middle_pressure;

		//
		double m_litho_pressure;	// ����ѹ��,plt
		double m_litho_middle_pressure;
		double m_litho_ultra_pressure;  // ��������,ult
		double m_litho_ultra_middle_pressure;
		double m_litho_ultra_delta_pressure; // DELTA

		//
		double m_effective_stress;		// ��ЧӦ��
		double m_effective_middle_stress;

		double m_effective_max_stress;
		double m_effective_max_middle_stress;

		double m_pressure_coefficent;	// ѹ��ϵ��,PCOEt,PCOEm,PCOEb
		double m_pressure_middle_coefficent;

		double m_static_ultra_pressure;
		double m_static_ultra_middle_pressure;//StaticUt,StaticUm,StaticUb��ˮ���ܣ����ڼ�����������ʱ  ,new Added20181130

		double m_ultra_pressure_real;
		double m_ultra_middle_pressure_real;//UtReal,UmReal,UbReal����ھ�ˮѹ���ĳ�ѹ

		double m_static_pressure_abovesealevel; //��ƽ��֮�Ͼ�ˮѹ�� �����ڻָ���ˮ����

		PVTVariable()
		{
			m_middle_temperature = 0;
			m_temperature = 0;

			m_water_fluid_pressure = 0;
			m_water_fluid_middle_pressure = 0;
			m_water_static_pressure = 0.1*1.0e6;
			m_water_static_middle_pressure = 0;
			m_water_static_delta_pressure = 0;

			m_oil_fluid_pressure = 0;
			m_oil_fluid_middle_pressure = 0;
			m_oil_static_pressure = 0;
			m_oil_static_middle_pressure = 0;
			m_oil_static_delta_pressure = 0;

			m_gas_fluid_pressure = 0;
			m_gas_fluid_middle_pressure = 0;
			m_gas_static_pressure = 0;
			m_gas_static_middle_pressure = 0;
			m_gas_static_delta_pressure = 0;

			m_water_ultra_pressure = 0;
			m_water_ultra_middle_pressure = 0;
			m_water_ultra_delta_pressure = 0;
			m_oil_ultra_pressure = 0;
			m_oil_ultra_middle_pressure = 0;
			m_gas_ultra_pressure = 0;
			m_gas_ultra_middle_pressure = 0;

			m_litho_pressure = 0;
			m_litho_middle_pressure = 0;
			m_litho_ultra_pressure = 0;
			m_litho_ultra_middle_pressure = 0;
			m_litho_ultra_delta_pressure = 0;

			m_effective_stress = 0;
			m_effective_middle_stress = 0;
			m_effective_max_stress = 0;
			m_effective_max_middle_stress = 0;
			m_pressure_coefficent = 0;
			m_pressure_middle_coefficent = 0;

			m_static_ultra_pressure = 0;
			m_static_ultra_middle_pressure = 0;
			m_ultra_pressure_real = 0;
			m_ultra_middle_pressure_real = 0;
			m_static_pressure_abovesealevel = 100000;
		}
		PVTVariable(const PVTVariable &other)
		{
			*this = other;
		}
		const PVTVariable &operator=(const PVTVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_middle_temperature = other.m_middle_temperature;
			m_temperature = other.m_temperature;
			m_water_fluid_pressure = other.m_water_fluid_pressure;
			m_water_fluid_middle_pressure = other.m_water_fluid_middle_pressure;
			m_water_static_pressure = other.m_water_static_pressure;
			m_water_static_middle_pressure = other.m_water_static_middle_pressure;
			m_water_static_delta_pressure = other.m_water_static_delta_pressure;

			m_oil_fluid_pressure = other.m_oil_fluid_pressure;
			m_oil_fluid_middle_pressure = other.m_oil_fluid_middle_pressure;
			m_oil_static_pressure = other.m_oil_static_pressure;
			m_oil_static_middle_pressure = other.m_oil_static_middle_pressure;
			m_oil_static_delta_pressure = other.m_oil_static_delta_pressure;

			m_gas_fluid_pressure = other.m_gas_fluid_pressure;
			m_gas_fluid_middle_pressure = other.m_gas_fluid_middle_pressure;
			m_gas_static_pressure = other.m_gas_static_pressure;
			m_gas_static_middle_pressure = other.m_gas_static_middle_pressure;
			m_gas_static_delta_pressure = other.m_gas_static_delta_pressure;

			m_water_ultra_pressure = other.m_water_ultra_pressure;
			m_water_ultra_middle_pressure = other.m_water_ultra_middle_pressure;
			m_water_ultra_delta_pressure = other.m_water_ultra_delta_pressure;
			m_oil_ultra_pressure = other.m_oil_ultra_pressure;
			m_oil_ultra_middle_pressure = other.m_oil_ultra_middle_pressure;
			m_gas_ultra_pressure = other.m_gas_ultra_pressure;
			m_gas_ultra_middle_pressure = other.m_gas_ultra_middle_pressure;

			m_litho_pressure = other.m_litho_pressure;
			m_litho_middle_pressure = other.m_litho_middle_pressure;
			m_litho_ultra_pressure = other.m_litho_ultra_pressure;
			m_litho_ultra_middle_pressure = other.m_litho_ultra_middle_pressure;
			m_litho_ultra_delta_pressure = other.m_litho_ultra_delta_pressure;

			m_effective_stress = other.m_effective_stress;
			m_effective_middle_stress = other.m_effective_middle_stress;
			m_effective_max_stress = other.m_effective_max_stress;
			m_effective_max_middle_stress = other.m_effective_max_middle_stress;
			m_pressure_coefficent = other.m_pressure_coefficent;
			m_pressure_middle_coefficent = other.m_pressure_middle_coefficent;

			m_static_ultra_pressure = other.m_static_ultra_pressure;
			m_static_ultra_middle_pressure = other.m_static_ultra_middle_pressure;
			m_ultra_pressure_real = other.m_ultra_pressure_real;
			m_ultra_middle_pressure_real = other.m_ultra_middle_pressure_real;
			m_static_pressure_abovesealevel = other.m_static_pressure_abovesealevel;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_middle_temperature;
			curSize += sizeof(double);//double m_temperature;
			curSize += sizeof(double);//double m_water_fluid_pressure;
			curSize += sizeof(double);//double m_water_fluid_middle_pressure;
			curSize += sizeof(double);//double m_water_static_pressure;
			curSize += sizeof(double);//double m_water_static_middle_pressure;
			curSize += sizeof(double);//double m_water_static_delta_pressure;
			curSize += sizeof(double);//double m_oil_fluid_pressure;
			curSize += sizeof(double);//double m_oil_fluid_middle_pressure;
			curSize += sizeof(double);//double m_oil_static_pressure;
			curSize += sizeof(double);//double m_oil_static_middle_pressure;
			curSize += sizeof(double);//double m_oil_static_delta_pressure;
			curSize += sizeof(double);//double m_gas_fluid_pressure;
			curSize += sizeof(double);//double m_gas_fluid_middle_pressure;
			curSize += sizeof(double);//double m_gas_static_pressure;
			curSize += sizeof(double);//double m_gas_static_middle_pressure;
			curSize += sizeof(double);//double m_gas_static_delta_pressure;
			curSize += sizeof(double);//double m_water_ultra_pressure;
			curSize += sizeof(double);//double m_water_ultra_middle_pressure;
			curSize += sizeof(double);//double m_water_ultra_delta_pressure
			curSize += sizeof(double);//double m_oil_ultra_pressure;
			curSize += sizeof(double);//double m_oil_ultra_middle_pressure;
			curSize += sizeof(double);//double m_gas_ultra_pressure;
			curSize += sizeof(double);//double m_gas_ultra_middle_pressure;
			curSize += sizeof(double);//double m_litho_pressure;
			curSize += sizeof(double);//double m_litho_middle_pressure;
			curSize += sizeof(double);//double m_litho_ultra_pressure;
			curSize += sizeof(double);//double m_litho_ultra_middle_pressure;
			curSize += sizeof(double);//double m_litho_ultra_delta_pressure;
			curSize += sizeof(double);//double m_effective_stress;
			curSize += sizeof(double);//double m_effective_middle_stress;
			curSize += sizeof(double);//double m_effective_max_stress;
			curSize += sizeof(double);//double m_effective_max_middle_stress;
			curSize += sizeof(double);//double m_pressure_coefficent;
			curSize += sizeof(double);//double m_pressure_middle_coefficent;
			curSize += sizeof(double);//double m_static_ultra_pressure;
			curSize += sizeof(double);//double m_static_ultra_middle_pressure;
			curSize += sizeof(double);//double m_ultra_pressure_real;
			curSize += sizeof(double);//double m_ultra_middle_pressure_real;
			curSize += sizeof(double);//double m_static_pressure_abovesealevel;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_middle_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_fluid_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_fluid_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_static_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_static_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_static_delta_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_fluid_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_fluid_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_static_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_static_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_static_delta_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_fluid_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_fluid_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_static_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_static_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_static_delta_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_ultra_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_ultra_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_ultra_delta_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_ultra_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_ultra_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_ultra_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_ultra_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ultra_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ultra_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ultra_delta_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_effective_stress, sizeof(double));data += sizeof(double);
			memcpy(data, &m_effective_middle_stress, sizeof(double));data += sizeof(double);
			memcpy(data, &m_effective_max_stress, sizeof(double));data += sizeof(double);
			memcpy(data, &m_effective_max_middle_stress, sizeof(double));data += sizeof(double);
			memcpy(data, &m_pressure_coefficent, sizeof(double));data += sizeof(double);
			memcpy(data, &m_pressure_middle_coefficent, sizeof(double));data += sizeof(double);
			memcpy(data, &m_static_ultra_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_static_ultra_middle_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ultra_pressure_real, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ultra_middle_pressure_real, sizeof(double));data += sizeof(double);
			memcpy(data, &m_static_pressure_abovesealevel, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_middle_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_fluid_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_fluid_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_static_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_static_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_static_delta_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_fluid_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_fluid_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_static_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_static_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_static_delta_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_fluid_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_fluid_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_static_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_static_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_static_delta_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_ultra_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_ultra_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_ultra_delta_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_ultra_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_ultra_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_ultra_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_ultra_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ultra_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ultra_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ultra_delta_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_effective_stress, data, sizeof(double));data += sizeof(double);
			memcpy(&m_effective_middle_stress, data, sizeof(double));data += sizeof(double);
			memcpy(&m_effective_max_stress, data, sizeof(double));data += sizeof(double);
			memcpy(&m_effective_max_middle_stress, data, sizeof(double));data += sizeof(double);
			memcpy(&m_pressure_coefficent, data, sizeof(double));data += sizeof(double);
			memcpy(&m_pressure_middle_coefficent, data, sizeof(double));data += sizeof(double);
			memcpy(&m_static_ultra_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_static_ultra_middle_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ultra_pressure_real, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ultra_middle_pressure_real, data, sizeof(double));data += sizeof(double);
			memcpy(&m_static_pressure_abovesealevel, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, PVTVariable &pvtvariable)
		{
			os << "\r\n>>>>>>>>>>>>>>>PVTVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- middle_temperature:" << pvtvariable.m_middle_temperature;
			os << "\r\n---- ---- ---- temperature:" << pvtvariable.m_temperature;
			os << "\r\n---- ---- ---- water_fluid_pressure:" << pvtvariable.m_water_fluid_pressure;
			os << "\r\n---- ---- ---- water_fluid_middle_pressure:" << pvtvariable.m_water_fluid_middle_pressure;
			os << "\r\n---- ---- ---- water_static_pressure:" << pvtvariable.m_water_static_pressure;
			os << "\r\n---- ---- ---- water_static_middle_pressure:" << pvtvariable.m_water_static_middle_pressure;
			os << "\r\n---- ---- ---- water_static_delta_pressure:" << pvtvariable.m_water_static_delta_pressure;
			os << "\r\n---- ---- ---- oil_fluid_pressure:" << pvtvariable.m_oil_fluid_pressure;
			os << "\r\n---- ---- ---- oil_fluid_middle_pressure:" << pvtvariable.m_oil_fluid_middle_pressure;
			os << "\r\n---- ---- ---- oil_static_pressure:" << pvtvariable.m_oil_static_pressure;
			os << "\r\n---- ---- ---- oil_static_middle_pressure:" << pvtvariable.m_oil_static_middle_pressure;
			os << "\r\n---- ---- ---- oil_static_delta_pressure:" << pvtvariable.m_oil_static_delta_pressure;
			os << "\r\n---- ---- ---- gas_fluid_pressure:" << pvtvariable.m_gas_fluid_pressure;
			os << "\r\n---- ---- ---- gas_fluid_middle_pressure:" << pvtvariable.m_gas_fluid_middle_pressure;
			os << "\r\n---- ---- ---- gas_static_pressure:" << pvtvariable.m_gas_static_pressure;
			os << "\r\n---- ---- ---- gas_static_middle_pressure:" << pvtvariable.m_gas_static_middle_pressure;
			os << "\r\n---- ---- ---- gas_static_delta_pressure:" << pvtvariable.m_gas_static_delta_pressure;
			os << "\r\n---- ---- ---- water_ultra_pressure:" << pvtvariable.m_water_ultra_pressure;
			os << "\r\n---- ---- ---- water_ultra_middle_pressure:" << pvtvariable.m_water_ultra_middle_pressure;
			os << "\r\n---- ---- ---- water_ultra_delta_pressure:" << pvtvariable.m_water_ultra_delta_pressure;
			os << "\r\n---- ---- ---- oil_ultra_pressure:" << pvtvariable.m_oil_ultra_pressure;
			os << "\r\n---- ---- ---- oil_ultra_middle_pressure:" << pvtvariable.m_oil_ultra_middle_pressure;
			os << "\r\n---- ---- ---- gas_ultra_pressure:" << pvtvariable.m_gas_ultra_pressure;
			os << "\r\n---- ---- ---- gas_ultra_middle_pressure:" << pvtvariable.m_gas_ultra_middle_pressure;
			os << "\r\n---- ---- ---- litho_pressure:" << pvtvariable.m_litho_pressure;
			os << "\r\n---- ---- ---- litho_middle_pressure:" << pvtvariable.m_litho_middle_pressure;
			os << "\r\n---- ---- ---- litho_ultra_pressure:" << pvtvariable.m_litho_ultra_pressure;
			os << "\r\n---- ---- ---- litho_ultra_middle_pressure:" << pvtvariable.m_litho_ultra_middle_pressure;
			os << "\r\n---- ---- ---- litho_ultra_delta_pressure:" << pvtvariable.m_litho_ultra_delta_pressure;
			os << "\r\n---- ---- ---- effective_stress:" << pvtvariable.m_effective_stress;
			os << "\r\n---- ---- ---- effective_middle_stress:" << pvtvariable.m_effective_middle_stress;
			os << "\r\n---- ---- ---- effective_max_stress:" << pvtvariable.m_effective_max_stress;
			os << "\r\n---- ---- ---- effective_max_middle_stress:" << pvtvariable.m_effective_max_middle_stress;
			os << "\r\n---- ---- ---- pressure_coefficent:" << pvtvariable.m_pressure_coefficent;
			os << "\r\n---- ---- ---- pressure_middle_coefficent:" << pvtvariable.m_pressure_middle_coefficent;
			os << "\r\n---- ---- ---- static_ultra_pressure:" << pvtvariable.m_static_ultra_pressure;
			os << "\r\n---- ---- ---- static_ultra_middle_pressure:" << pvtvariable.m_static_ultra_middle_pressure;
			os << "\r\n---- ---- ---- ultra_pressure_real:" << pvtvariable.m_ultra_pressure_real;
			os << "\r\n---- ---- ---- ultra_middle_pressure_real:" << pvtvariable.m_ultra_middle_pressure_real;
			os << "\r\n---- ---- ---- static_pressure_abovesealevel:" << pvtvariable.m_static_pressure_abovesealevel;
			return os;
		}
	};

	// as vertex and mesh variable meaningly
	struct PhysicalVariable
	{
		// ����ֽ�ز��϶��
		double m_current_porosity;
		double m_difference_porosity;

		//
		double m_ever_porosity;
		double m_ever_middle_porosity;
		double m_ever_permeability;
		double m_ever_middle_permeability;

		//
		//��ϵ�����ĳ�ʼ��϶�Ⱥ�ѹʵϵ��
		double m_mix_porosity;
		double m_mix_compact_factor;

		//
		PhysicalVariable()
		{
			m_current_porosity = 0;
			m_difference_porosity = 0;

			m_ever_porosity = 0;
			m_ever_middle_porosity = 0;
			m_ever_permeability = 0;
			m_ever_middle_permeability = 0;

			m_mix_porosity = 0;
			m_mix_compact_factor = 0;
		}
		PhysicalVariable(const PhysicalVariable &other)
		{
			*this = other;
		}
		const PhysicalVariable &operator=(const PhysicalVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_ever_porosity = other.m_ever_porosity;
			m_ever_middle_porosity = other.m_ever_middle_porosity;
			m_ever_permeability = other.m_ever_permeability;
			m_ever_middle_permeability = other.m_ever_middle_permeability;
			m_current_porosity = other.m_current_porosity;
			m_difference_porosity = other.m_difference_porosity;
			m_mix_porosity = other.m_mix_porosity;
			m_mix_compact_factor = other.m_mix_compact_factor;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_current_porosity;
			curSize += sizeof(double);//double m_difference_porosity;
			curSize += sizeof(double);//double m_ever_porosity;
			curSize += sizeof(double);//double m_ever_middle_porosity;
			curSize += sizeof(double);//double m_ever_permeability;
			curSize += sizeof(double);//double m_ever_middle_permeability;
			curSize += sizeof(double);//double m_mix_porosity;
			curSize += sizeof(double);//double m_mix_compact_factor;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_current_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_difference_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ever_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ever_middle_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ever_permeability, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ever_middle_permeability, sizeof(double));data += sizeof(double);
			memcpy(data, &m_mix_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_mix_compact_factor, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_current_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_difference_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ever_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ever_middle_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ever_permeability, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ever_middle_permeability, data, sizeof(double));data += sizeof(double);
			memcpy(&m_mix_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_mix_compact_factor, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, PhysicalVariable &physicalvariable)
		{
			os << "\r\n>>>>>>>>>>>>>>>PhysicalVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- ever_porosity:" << physicalvariable.m_ever_porosity;
			os << "\r\n---- ---- ---- ever_middle_porosity:" << physicalvariable.m_ever_middle_porosity;
			os << "\r\n---- ---- ---- ever_permeability:" << physicalvariable.m_ever_permeability;
			os << "\r\n---- ---- ---- ever_middle_permeability:" << physicalvariable.m_ever_middle_permeability;
			os << "\r\n---- ---- ---- current_porosity:" << physicalvariable.m_current_porosity;
			os << "\r\n---- ---- ---- difference_porosity:" << physicalvariable.m_difference_porosity;
			os << "\r\n---- ---- ---- mix_porosity:" << physicalvariable.m_mix_porosity;
			os << "\r\n---- ---- ---- mix_compact_factor:" << physicalvariable.m_mix_compact_factor;
			return os;
		}
	};

	struct DensityVariable
	{
		double m_sea_water_density;
		double m_water_density;
		double m_oil_density;
		double m_gas_density;
		double m_total_density; //�ܵ���ʯ�ܶȣ��������е�����͹Ǽܵ��ۺ��ܶȣ�
		double m_total_matrix_density; //�ܵĻ����ܶ�

		//
		DensityVariable()
		{
			m_sea_water_density = 1025;
			m_water_density = 1040;
			m_oil_density = 0;
			m_gas_density = 0;
			m_total_density = 0;
			m_total_matrix_density = 0;
		}
		DensityVariable(const DensityVariable &other)
		{
			*this = other;
		}
		const DensityVariable &operator=(const DensityVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_sea_water_density = other.m_sea_water_density;
			m_water_density = other.m_water_density;
			m_oil_density = other.m_oil_density;
			m_gas_density = other.m_gas_density;
			m_total_density = other.m_total_density;
			m_total_matrix_density = other.m_total_matrix_density;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_sea_water_density;
			curSize += sizeof(double);//double m_water_density;
			curSize += sizeof(double);//double m_oil_density;
			curSize += sizeof(double);//double m_gas_density;
			curSize += sizeof(double);//double m_total_density;
			curSize += sizeof(double);//double m_total_matrix_density;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_sea_water_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_total_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_total_matrix_density, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_sea_water_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_total_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_total_matrix_density, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, DensityVariable &densityvariable)
		{
			os << "\r\n>>>>>>>>>>>>>>>CapacityVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- sea_water_density:" << densityvariable.m_sea_water_density;
			os << "\r\n---- ---- ---- water_density:" << densityvariable.m_water_density;
			os << "\r\n---- ---- ---- oil_density:" << densityvariable.m_oil_density;
			os << "\r\n---- ---- ---- gas_density:" << densityvariable.m_gas_density;
			os << "\r\n---- ---- ---- total_density:" << densityvariable.m_total_density;
			os << "\r\n---- ---- ---- total_matrix_density:" << densityvariable.m_total_matrix_density;
			return os;
		}
	};

	struct CapacityVariable
	{
		double m_total_heat_capacity;
		double m_matrix_heat_capacity;
		double m_water_heat_capacity;
		double m_oil_heat_capacity;
		double m_gas_heat_capacity;
		double m_ice_heat_capacity;
		double m_gas_hydrates_heat_capacity;
		double m_pore_fluid_heat_capacity;

		//
		CapacityVariable()
		{
			m_total_heat_capacity = 0.;
			m_matrix_heat_capacity = 0.;
			m_water_heat_capacity = 0.;
			m_oil_heat_capacity = 0.;
			m_gas_heat_capacity = 0.;
			m_ice_heat_capacity = 0.;
			m_gas_hydrates_heat_capacity = 0.;
			m_pore_fluid_heat_capacity = 0.;
		}
		CapacityVariable(const CapacityVariable &other)
		{
			*this = other;
		}
		const CapacityVariable &operator=(const CapacityVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_total_heat_capacity = other.m_total_heat_capacity;
			m_matrix_heat_capacity = other.m_matrix_heat_capacity;
			m_water_heat_capacity = other.m_water_heat_capacity;
			m_oil_heat_capacity = other.m_oil_heat_capacity;
			m_gas_heat_capacity = other.m_gas_heat_capacity;
			m_ice_heat_capacity = other.m_ice_heat_capacity;
			m_gas_hydrates_heat_capacity = other.m_gas_hydrates_heat_capacity;
			m_pore_fluid_heat_capacity = other.m_pore_fluid_heat_capacity;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_total_heat_capacity;
			curSize += sizeof(double);//double m_matrix_heat_capacity;
			curSize += sizeof(double);//double m_water_heat_capacity;
			curSize += sizeof(double);//double m_oil_heat_capacity;
			curSize += sizeof(double);//double m_gas_heat_capacity;
			curSize += sizeof(double);//double m_ice_heat_capacity;
			curSize += sizeof(double);//double m_gas_hydrates_heat_capacity;
			curSize += sizeof(double);//double m_pore_fluid_heat_capacity;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_total_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_matrix_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_oil_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ice_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_gas_hydrates_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_pore_fluid_heat_capacity, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_total_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_matrix_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_oil_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ice_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_gas_hydrates_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_pore_fluid_heat_capacity, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, CapacityVariable &capacityvariable)
		{
			os << "\r\n>>>>>>>>>>>>>>>CapacityVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- total_heat_capacity:" << capacityvariable.m_total_heat_capacity;
			os << "\r\n---- ---- ---- matrix_heat_capacity:" << capacityvariable.m_matrix_heat_capacity;
			os << "\r\n---- ---- ---- water_heat_capacity:" << capacityvariable.m_water_heat_capacity;
			os << "\r\n---- ---- ---- oil_heat_capacity:" << capacityvariable.m_oil_heat_capacity;
			os << "\r\n---- ---- ---- gas_heat_capacity:" << capacityvariable.m_gas_heat_capacity;
			os << "\r\n---- ---- ---- ice_heat_capacity:" << capacityvariable.m_ice_heat_capacity;
			os << "\r\n---- ---- ---- gas_hydrates_heat_capacity:" << capacityvariable.m_gas_hydrates_heat_capacity;
			os << "\r\n---- ---- ---- pore_fluid_heat_capacity:" << capacityvariable.m_pore_fluid_heat_capacity;
			return os;
		}
	};

	struct PhaseVariable
	{
		//
		double m_Sw;
		double m_So;
		double m_Sg;

		//
		double m_WaterViscosity;  //ˮճ��
		double m_OilViscosity;
		double m_GasViscosity;

		//�����͸��
		double m_k_ro;
		double m_k_rw;
		double m_k_rg;

		//ëϸ��ѹ��
		double m_PcOW;
		double m_delta_PcOW; //ǰ��ʱ��ģ��ֵ�Ĳ�ֵ
		double m_PcGW;
		double m_delta_PcGW;
		double m_PcGO; //�ֱ���ˮ����ˮ�����͵�ë��ѹ��
		double m_delta_PcGO;

		//
		//
		PhaseVariable()
		{
			m_Sw = 1.0;
			m_So = 0.;
			m_Sg = 0.;

			m_WaterViscosity = 0.;
			m_OilViscosity = 0.;
			m_GasViscosity = 0.;

			m_k_ro = 0.;
			m_k_rg = 0.;
			m_k_rw = 0.;

			m_PcOW = 0.;
			m_delta_PcOW = 0.;
			m_PcGW = 0.;
			m_delta_PcGW = 0.;
			m_PcGO = 0.;
			m_delta_PcGO = 0.;
		}
		PhaseVariable(const PhaseVariable &other)
		{
			*this = other;
		}
		const PhaseVariable &operator=(const PhaseVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_Sw = other.m_Sw;
			m_So = other.m_So;
			m_Sg = other.m_Sg;

			m_WaterViscosity = other.m_WaterViscosity;
			m_OilViscosity = other.m_OilViscosity;
			m_GasViscosity = other.m_GasViscosity;

			m_k_ro = other.m_k_ro;
			m_k_rg = other.m_k_rg;
			m_k_rw = other.m_k_rw;

			m_PcOW = other.m_PcOW;
			m_delta_PcOW = other.m_delta_PcOW;
			m_PcGW = other.m_PcGW;
			m_delta_PcGW = other.m_delta_PcGW;
			m_PcGO = other.m_PcGO;
			m_delta_PcGO = other.m_delta_PcGO;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_Sw;
			curSize += sizeof(double);//double m_So;
			curSize += sizeof(double);//double m_Sg;
			curSize += sizeof(double);//double m_WaterViscosity;
			curSize += sizeof(double);//double m_OilViscosity;
			curSize += sizeof(double);//double m_GasViscosity;
			curSize += sizeof(double);//double m_k_ro;
			curSize += sizeof(double);//double m_k_rw;
			curSize += sizeof(double);//double m_k_rg;
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
			memcpy(data, &m_Sw, sizeof(double));data += sizeof(double);
			memcpy(data, &m_So, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Sg, sizeof(double));data += sizeof(double);
			memcpy(data, &m_WaterViscosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilViscosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GasViscosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_k_ro, sizeof(double));data += sizeof(double);
			memcpy(data, &m_k_rw, sizeof(double));data += sizeof(double);
			memcpy(data, &m_k_rg, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcOW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_delta_PcOW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcGW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_delta_PcGW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcGO, sizeof(double));data += sizeof(double);
			memcpy(data, &m_delta_PcGO, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_Sw, data, sizeof(double));data += sizeof(double);
			memcpy(&m_So, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Sg, data, sizeof(double));data += sizeof(double);
			memcpy(&m_WaterViscosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilViscosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GasViscosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_k_ro, data, sizeof(double));data += sizeof(double);
			memcpy(&m_k_rw, data, sizeof(double));data += sizeof(double);
			memcpy(&m_k_rg, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcOW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_delta_PcOW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcGW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_delta_PcGW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcGO, data, sizeof(double));data += sizeof(double);
			memcpy(&m_delta_PcGO, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, PhaseVariable &phase)
		{
			os << "\r\n>>>>>>>>>>>>>>>haseVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- Sw:" << phase.m_Sw;
			os << "\r\n---- ---- ---- So:" << phase.m_So;
			os << "\r\n---- ---- ---- Sg:" << phase.m_Sg;
			os << "\r\n---- ---- ---- WaterViscosity:" << phase.m_WaterViscosity;
			os << "\r\n---- ---- ---- OilViscosity:" << phase.m_OilViscosity;
			os << "\r\n---- ---- ---- GasViscosity:" << phase.m_GasViscosity;
			os << "\r\n---- ---- ---- k_ro:" << phase.m_k_ro;
			os << "\r\n---- ---- ---- k_rg:" << phase.m_k_rg;
			os << "\r\n---- ---- ---- k_rw:" << phase.m_k_rw;
			os << "\r\n---- ---- ---- m_PcOW:" << phase.m_PcOW;
			os << "\r\n---- ---- ---- m_delta_PcOW:" << phase.m_delta_PcOW;
			os << "\r\n---- ---- ---- m_PcGW:" << phase.m_PcGW;
			os << "\r\n---- ---- ---- m_delta_PcGW:" << phase.m_delta_PcGW;
			os << "\r\n---- ---- ---- m_PcGO:" << phase.m_PcGO;
			os << "\r\n---- ---- ---- m_delta_PcGO:" << phase.m_delta_PcGO;
			return os;
		}
	};

	/*!
	* Ŀǰ��ֻ���1ά�ĳ�ѹ������⣻������ά����Ԫ��Ҫ��һ�����ֳ�Ա����
	**/
	struct OverPressureVariable
	{
		double m_COC;//ѹ��ϵ�� Coefficient Of Compressibility
		double m_aOverpressure;
		double m_bOverpressure;
		double m_cOverpressure; //��ѹ�����е��������������һά��ֲ������Ƶ�û���ã�

		double m_vFluild; //���������ٶȣ���һ����û�õ�
		double m_vWater; //�ز�ˮ����

		//
		//
		OverPressureVariable()
		{
			m_COC = 0.;
			m_aOverpressure = 0.;
			m_bOverpressure = 0.;
			m_cOverpressure = 0.;

			m_vFluild = 0.;
			m_vWater = 0.;
		}
		OverPressureVariable(const OverPressureVariable &other)
		{
			*this = other;
		}
		const OverPressureVariable &operator=(const OverPressureVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_COC = other.m_COC;
			m_aOverpressure = other.m_aOverpressure;
			m_bOverpressure = other.m_bOverpressure;
			m_cOverpressure =other.m_cOverpressure;

			m_vFluild = other.m_vFluild;
			m_vWater = other.m_vWater;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_COC;
			curSize += sizeof(double);//double m_aOverpressure;
			curSize += sizeof(double);//double m_bOverpressure;
			curSize += sizeof(double);//double m_cOverpressure;
			curSize += sizeof(double);//double m_vFluild;
			curSize += sizeof(double);//double m_vWater;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_COC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_aOverpressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_bOverpressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_cOverpressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_vFluild, sizeof(double));data += sizeof(double);
			memcpy(data, &m_vWater, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_COC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_aOverpressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_bOverpressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_cOverpressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_vFluild, data, sizeof(double));data += sizeof(double);
			memcpy(&m_vWater, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, OverPressureVariable &overpressure)
		{
			os << "\r\n>>>>>>>>>>>>>>>OverPressureVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- COC:" << overpressure.m_COC;
			os << "\r\n---- ---- ---- aOverpressure:" << overpressure.m_aOverpressure;
			os << "\r\n---- ---- ---- bOverpressure:" << overpressure.m_bOverpressure;
			os << "\r\n---- ---- ---- cOverpressure:" << overpressure.m_cOverpressure;
			os << "\r\n---- ---- ---- vFluild:" << overpressure.m_vFluild;
			os << "\r\n---- ---- ---- vWater:" << overpressure.m_vWater;
			return os;
		}
	};

	//
	//
	/*!
	*
	**/
	struct EasyRO
	{
		//ƽ�з�Ӧ����� ���������ѧ����ϵ���ͻ��ͨ������������NN���Ը��ݱ���е��������� ��
		int m_NNEasyRo;
		//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fEasyRo;
		//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_EEasyRo;
		//Ƶ������ S^-1
		double m_AEasyRo;
		//EasyRoģ���ڵر��ʼʱ�̵�Roֵ  Roo=exp(-1.6);
		double m_RooEasyRo;
		double m_f0;

		EasyRO()
		{
			m_NNEasyRo = 20;

			m_fEasyRo.resize(m_NNEasyRo);
			m_fEasyRo[0]=0.03;
			m_fEasyRo[1]=0.03;
			m_fEasyRo[2]=0.04;
			m_fEasyRo[3]=0.04;
			m_fEasyRo[4]=0.05;
			m_fEasyRo[5]=0.05;
			m_fEasyRo[6]=0.06;
			m_fEasyRo[7]=0.04;
			m_fEasyRo[8]=0.04;
			m_fEasyRo[9]=0.07;
			m_fEasyRo[10]=0.06;
			m_fEasyRo[11]=0.06;
			m_fEasyRo[12]=0.06;
			m_fEasyRo[13]=0.05;
			m_fEasyRo[14]=0.05;
			m_fEasyRo[15]=0.04;
			m_fEasyRo[16]=0.03;
			m_fEasyRo[17]=0.02;
			m_fEasyRo[18]=0.02;
			m_fEasyRo[19]=0.01;

			m_EEasyRo.resize(m_NNEasyRo);
			m_EEasyRo[0]=34;
			m_EEasyRo[1]=36;
			m_EEasyRo[2]=38;
			m_EEasyRo[3]=40;
			m_EEasyRo[4]=42;
			m_EEasyRo[5]=44;
			m_EEasyRo[6]=46;
			m_EEasyRo[7]=48;
			m_EEasyRo[8]=50;
			m_EEasyRo[9]=52;
			m_EEasyRo[10]=54;
			m_EEasyRo[11]=56;
			m_EEasyRo[12]=58;
			m_EEasyRo[13]=60;
			m_EEasyRo[14]=62;
			m_EEasyRo[15]=64;
			m_EEasyRo[16]=66;
			m_EEasyRo[17]=68;
			m_EEasyRo[18]=70;
			m_EEasyRo[19]=72;

			m_AEasyRo = 1.0e13;
			m_RooEasyRo=0.201897;
			m_f0=0;
			for(int i = 0; i < m_NNEasyRo; i++)
				m_f0+=m_fEasyRo[i];
		}
		EasyRO(const EasyRO &other)
		{
			*this = other;
		}
		const EasyRO &operator=(const EasyRO &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_NNEasyRo = other.m_NNEasyRo;
			m_fEasyRo = other.m_fEasyRo;
			m_EEasyRo = other.m_EEasyRo;
			m_AEasyRo = other.m_AEasyRo;
			m_RooEasyRo = other.m_RooEasyRo;
			m_f0 = other.m_f0;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(int);//int m_NNEasyRo;
			curSize += (sizeof(int) + m_fEasyRo.size() * sizeof(double));//std::vector<double> m_fEasyRo;
			curSize += (sizeof(int) + m_EEasyRo.size() * sizeof(double));//std::vector<double> m_EEasyRo;
			curSize += sizeof(double);//double m_AEasyRo;
			curSize += sizeof(double);//double m_RooEasyRo;
			curSize += sizeof(double);//double m_f0;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_NNEasyRo), sizeof(int));data += sizeof(int);
			int fEasyRosize = m_fEasyRo.size();
			memcpy(data, &fEasyRosize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fEasyRosize; j++)
			{
				memcpy(data, &(m_fEasyRo[j]), sizeof(double));data += sizeof(double);
			}
			int EEasyRosize = m_EEasyRo.size();
			memcpy(data, &EEasyRosize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EEasyRosize; j++)
			{
				memcpy(data, &(m_EEasyRo[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_AEasyRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_RooEasyRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_f0), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_NNEasyRo), data, sizeof(int));data += sizeof(int);
			int fEasyRosize;
			memcpy(&fEasyRosize, data, sizeof(int));data += sizeof(int);
			m_fEasyRo.resize(fEasyRosize);
			for(int j = 0; j < fEasyRosize; j++)
			{
				memcpy(&(m_fEasyRo[j]), data, sizeof(double));data += sizeof(double);
			}
			int EEasyRosize;
			memcpy(&EEasyRosize, data, sizeof(int));data += sizeof(int);
			m_EEasyRo.resize(EEasyRosize);
			for(int j = 0; j < EEasyRosize; j++)
			{
				memcpy(&(m_EEasyRo[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_AEasyRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_RooEasyRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_f0), data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, EasyRO &easyro)
		{
			os << "\r\n>>>>>>>>>>>>>>>EasyRO parameter as flow:"; 
			os << "\r\n---- ---- ---- NNEasyRo:" << easyro.m_NNEasyRo;
			for(int i = 0; i < easyro.m_fEasyRo.size(); i++)os << "\r\n---- ---- ---- m_fEasyRo:" << i << ":" << easyro.m_fEasyRo[i];
			for(int i = 0; i < easyro.m_EEasyRo.size(); i++)os << "\r\n---- ---- ---- m_EEasyRo:" << i << ":" << easyro.m_EEasyRo[i];
			os << "\r\n---- ---- ---- AEasyRo:" << easyro.m_AEasyRo;
			os << "\r\n---- ---- ---- RooEasyRo:" << easyro.m_RooEasyRo;
			os << "\r\n---- ---- ---- f0:" << easyro.m_f0;
			return os;
		}
	};
	struct BasinRO
	{
		//ƽ�з�Ӧ�����
		int m_NNBasinRo;
		//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fBasinRo;
		//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_EBasinRo;
		//Ƶ������ S^-1
		double m_ABasinRo;
		//BasinRo��ʼʱ�̵�Roֵ
		double m_RooBasinRo;
		double m_f0;

		BasinRO()
		{
			m_NNBasinRo = 20;
			
			m_fBasinRo.resize(m_NNBasinRo);
			m_fBasinRo[0]=0.0185;
			m_fBasinRo[1]=0.0143;
			m_fBasinRo[2]=0.0569;
			m_fBasinRo[3]=0.0478;
			m_fBasinRo[4]=0.0497;
			m_fBasinRo[5]=0.0344;
			m_fBasinRo[6]=0.0344;
			m_fBasinRo[7]=0.0322;
			m_fBasinRo[8]=0.0282;
			m_fBasinRo[9]=0.0062;
			m_fBasinRo[10]=0.1155;
			m_fBasinRo[11]=0.1041;
			m_fBasinRo[12]=0.1023;
			m_fBasinRo[13]=0.076;
			m_fBasinRo[14]=0.0593;
			m_fBasinRo[15]=0.0512;
			m_fBasinRo[16]=0.0477;
			m_fBasinRo[17]=0.0086;
			m_fBasinRo[18]=0.0246;
			m_fBasinRo[19]=0.0096;
			
			m_EBasinRo.resize(m_NNBasinRo);
			m_EBasinRo[0]=34;
			m_EBasinRo[1]=36;
			m_EBasinRo[2]=38;
			m_EBasinRo[3]=40;
			m_EBasinRo[4]=42;
			m_EBasinRo[5]=44;
			m_EBasinRo[6]=46;
			m_EBasinRo[7]=48;
			m_EBasinRo[8]=50;
			m_EBasinRo[9]=52;
			m_EBasinRo[10]=54;
			m_EBasinRo[11]=56;
			m_EBasinRo[12]=58;
			m_EBasinRo[13]=60;
			m_EBasinRo[14]=62;
			m_EBasinRo[15]=64;
			m_EBasinRo[16]=66;
			m_EBasinRo[17]=68;
			m_EBasinRo[18]=70;
			m_EBasinRo[19]=72;

			m_ABasinRo = 9.70293e12;
			m_RooBasinRo=0.2104;
			m_f0 = 0;
			for(int i = 0; i < m_NNBasinRo; i++)
				m_f0+=m_fBasinRo[i];
		}
		BasinRO(const BasinRO &other)
		{
			*this = other;
		}
		const BasinRO &operator=(const BasinRO &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_NNBasinRo = other.m_NNBasinRo;
			m_fBasinRo = other.m_fBasinRo;
			m_EBasinRo = other.m_EBasinRo;
			m_ABasinRo = other.m_ABasinRo;
			m_RooBasinRo = other.m_RooBasinRo;
			m_f0 = other.m_f0;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(int);//int m_NNBasinRo;
			curSize += (sizeof(int) + m_fBasinRo.size() * sizeof(double));//std::vector<double> m_fBasinRo;
			curSize += (sizeof(int) + m_EBasinRo.size() * sizeof(double));//std::vector<double> m_EBasinRo;
			curSize += sizeof(double);//double m_ABasinRo;
			curSize += sizeof(double);//double m_RooBasinRo;
			curSize += sizeof(double);//double m_f0;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_NNBasinRo), sizeof(int));data += sizeof(int);
			int fBasinRosize = m_fBasinRo.size();
			memcpy(data, &fBasinRosize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fBasinRosize; j++)
			{
				memcpy(data, &(m_fBasinRo[j]), sizeof(double));data += sizeof(double);
			}
			int EBasinRosize = m_EBasinRo.size();
			memcpy(data, &EBasinRosize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EBasinRosize; j++)
			{
				memcpy(data, &(m_EBasinRo[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_ABasinRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_RooBasinRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_f0), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_NNBasinRo), data, sizeof(int));data += sizeof(int);
			int fBasinRosize;
			memcpy(&fBasinRosize, data, sizeof(int));data += sizeof(int);
			m_fBasinRo.resize(fBasinRosize);
			for(int j = 0; j < fBasinRosize; j++)
			{
				memcpy(&(m_fBasinRo[j]), data, sizeof(double));data += sizeof(double);
			}
			int EBasinRosize;
			memcpy(&EBasinRosize, data, sizeof(int));data += sizeof(int);
			m_EBasinRo.resize(EBasinRosize);
			for(int j = 0; j < EBasinRosize; j++)
			{
				memcpy(&(m_EBasinRo[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_ABasinRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_RooBasinRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_f0), data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, BasinRO &basinro)
		{
			os << "\r\n>>>>>>>>>>>>>>>BasinRO parameter as flow:"; 
			os << "\r\n---- ---- ---- NNBasinRo:" << basinro.m_NNBasinRo;
			for(int i = 0; i < basinro.m_fBasinRo.size(); i++)os << "\r\n---- ---- ---- m_fBasinRo:" << i << ":" << basinro.m_fBasinRo[i];
			for(int i = 0; i < basinro.m_EBasinRo.size(); i++)os << "\r\n---- ---- ---- m_EBasinRo:" << i << ":" << basinro.m_EBasinRo[i];
			os << "\r\n---- ---- ---- ABasinRo:" << basinro.m_ABasinRo;
			os << "\r\n---- ---- ---- RooBasinRo:" << basinro.m_RooBasinRo;
			os << "\r\n---- ---- ---- f0:" << basinro.m_f0;
			return os;
		}
	};
	struct SimpleRO
	{
		//�ǵ�һ�Ļ�ѧ����ϵ����Stoichiometric Factor������ʼʱ���൱��EasyRo�еĳ�ʼ��fi֮��
		double m_f0SimpleRo;
		//ͬ�ϣ�ֻ�����ڴ��뺯���Ĺ�������ֵ��仯
		double m_fSimpleRo;
		//Simple Ro�����л��E��lnRo��Ĺ�ϵ����  (E=��lnRo+��)
		double m_aerfSimpleRo;
		double m_beitaSimpleRo;
		//Ƶ������ S^-1
		double m_ASimpleRo;
		//�ز��ڳ�ʼʱ�̵�Roֵ��SimpleRoʹ��EasyRoͬ����ֵ
		double m_RooSimpleRo;

		SimpleRO()
		{
			m_f0SimpleRo = 0.85;
			m_fSimpleRo = 0.85;
			m_aerfSimpleRo = 9.7;
			m_beitaSimpleRo = 54.1;
			m_ASimpleRo = 1.0e13;
			m_RooSimpleRo=0.201897;
		}
		SimpleRO(const SimpleRO &other)
		{
			*this = other;
		}
		const SimpleRO &operator=(const SimpleRO &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_f0SimpleRo = other.m_f0SimpleRo;
			m_fSimpleRo = other.m_fSimpleRo;
			m_aerfSimpleRo = other.m_aerfSimpleRo;
			m_beitaSimpleRo = other.m_beitaSimpleRo;
			m_ASimpleRo = other.m_ASimpleRo;
			m_RooSimpleRo=other.m_RooSimpleRo;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_f0SimpleRo;
			curSize += sizeof(double);//double m_fSimpleRo;
			curSize += sizeof(double);//double m_aerfSimpleRo;
			curSize += sizeof(double);//double m_beitaSimpleRo;
			curSize += sizeof(double);//double m_ASimpleRo;
			curSize += sizeof(double);//double m_RooSimpleRo;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_f0SimpleRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_fSimpleRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_aerfSimpleRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_beitaSimpleRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ASimpleRo), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_RooSimpleRo), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_f0SimpleRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_fSimpleRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_aerfSimpleRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_beitaSimpleRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ASimpleRo), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_RooSimpleRo), data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, SimpleRO &simplero)
		{
			os << "\r\n>>>>>>>>>>>>>>>SimpleRO parameter as flow:"; 
			os << "\r\n---- ---- ---- f0SimpleRo:" << simplero.m_f0SimpleRo;
			os << "\r\n---- ---- ---- fSimpleRo:" << simplero.m_fSimpleRo;
			os << "\r\n---- ---- ---- aerfSimpleRo:" << simplero.m_aerfSimpleRo;
			os << "\r\n---- ---- ---- beitaSimpleRo:" << simplero.m_beitaSimpleRo;
			os << "\r\n---- ---- ---- ASimpleRo:" << simplero.m_ASimpleRo;
			os << "\r\n---- ---- ---- RooSimpleRo:" << simplero.m_RooSimpleRo;
			return os;
		}
	};
	//����Ϊ���Ҹ������ʲ�����struct DR
	struct KerogenDegradation
	{
		//���Ҹ�������
		int m_NKerogen;
		//���ָ��Ҹ���ռ�ı���
		std::vector<double> m_Ratio;
		
		//��Ӧ��I�͸��Ҹ���������ֵ�ĸ���
		int m_NI;
		//DegradationRate Of Type I Kerogen
		std::vector<double> m_DRI;
		//��Ӧ��DegradationRate Of Type I Kerogen��Ro
		std::vector<double> m_RoI;

		//��Ӧ��IIA�͸��Ҹ���������ֵ�ĸ���
		int m_NIIA;
		//DegradationRate Of Type IIA Kerogen
		std::vector<double> m_DRIIA;
		//��Ӧ��DegradationRate Of Type IIA Kerogen��Ro
		std::vector<double> m_RoIIA;

		//��Ӧ��IIB�͸��Ҹ���������ֵ�ĸ���
		int m_NIIB;
		//DegradationRate Of Type IIB Kerogen
		std::vector<double> m_DRIIB;
		//��Ӧ��DegradationRate Of Type IIB Kerogen��Ro
		std::vector<double> m_RoIIB;

		//��Ӧ��III�͸��Ҹ���������ֵ�ĸ���
		int m_NIII;
		//DegradationRate Of Type III Kerogen
		std::vector<double> m_DRIII;
		//��Ӧ��DegradationRate Of Type III Kerogen��Ro
		std::vector<double> m_RoIII;

		//��Ӧ�������⺬������ֵ�ĸ���
		int m_NGDR;
		//�����⺬��
		std::vector<double> m_GDR;
		//�����⺬����Ӧ��Ro%ֵ
		std::vector<double> m_RoGDR;

		//Ϊ����ת���ʣ�һ��ȡֵ0.96m3/kg
		double m_COG;

		//���ֲ�ͬ���͵ĸ��Ҹ���λ������kg)�л�̼������
		double m_HCFromDRI;
		double m_HCFromDRIIA;
		double m_HCFromDRIIB;
		double m_HCFromDRIII; 
		//ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
		double m_InitTOCI;
		double m_InitTOCIIA;
		double m_InitTOCIIB;
		double m_InitTOCIII; 
		//����ֵ�ԭʼ�л�̼�ڵز�ε�ԭʼ�л�̼����kg
		double m_MassInitTOCI;
		double m_MassInitTOCIIA;
		double m_MassInitTOCIIB;
		double m_MassInitTOCIII; 
		double m_GasRatio; //��Ȼ������,�൱���ĵ��е�Pg
		//ÿ��λ��kg��ԭʼ�л�̼������������
		double m_HCGIPerUnitInitTOC_I;
		double m_HCGIPerUnitInitTOC_IIA;
		double m_HCGIPerUnitInitTOC_IIB;
		double m_HCGIPerUnitInitTOC_III; 
		 //ÿ��λ��kg��ԭʼ�л�̼������������
		double m_OGIPerUnitInitTOC_I;
		double m_OGIPerUnitInitTOC_IIA;
		double m_OGIPerUnitInitTOC_IIB;
		double m_OGIPerUnitInitTOC_III; 
		//ÿ��λ��kg��ԭʼ�л�̼������������
		double m_GGIPerUnitInitTOC_I;
		double m_GGIPerUnitInitTOC_IIA;
		double m_GGIPerUnitInitTOC_IIB;
		double m_GGIPerUnitInitTOC_III;  

		double m_TotalDR; //���ָ��Ҹ��ܵĽ�����
		double m_TRO;
		double m_TRG; //�ֱ����ͺ�����ת����

		KerogenDegradation()
		{
			m_NKerogen=4; 
			m_Ratio.resize(m_NKerogen); 
			m_Ratio[0]=0.2; 
			m_Ratio[1]=0.3; 
			m_Ratio[2]=0.3; 
			m_Ratio[3]=0.2;

			m_NI=25; 
			m_DRI.resize(m_NI);  //DegradationRate Of Type I Kerogen
			m_RoI.resize(m_NI);  
			m_RoI[0]=0.2;
			m_RoI[1]=0.311; 
			m_RoI[2]=0.351;
			m_RoI[3]=0.390;
			m_RoI[4]=0.455;
			m_RoI[5]=0.503;
			m_RoI[6]=0.552;
			m_RoI[7]=0.617;
			m_RoI[8]=0.657;
			m_RoI[9]=0.705;
			m_RoI[10]=0.754;
			m_RoI[11]=0.809;
			m_RoI[12]=0.849;
			m_RoI[13]=0.895;
			m_RoI[14]=0.948;
			m_RoI[15]=0.993;
			m_RoI[16]=1.034;
			m_RoI[17]=1.092;
			m_RoI[18]=1.161;
			m_RoI[19]=1.224;
			m_RoI[20]=1.279;
			m_RoI[21]=1.351;
			m_RoI[22]=1.481;
			m_RoI[23]=1.620;
			m_RoI[24]=1.783;
			
			m_DRI[0]=0; 
			m_DRI[1]=0.31;
			m_DRI[2]=1.27;
			m_DRI[3]=2.06;
			m_DRI[4]=3.47;
			m_DRI[5]=4.71;
			m_DRI[6]=6.31;
			m_DRI[7]=8.82;
			m_DRI[8]=10.98;
			m_DRI[9]=13.95;
			m_DRI[10]=17.64;
			m_DRI[11]=22.51;
			m_DRI[12]=26.67;
			m_DRI[13]=31.72;
			m_DRI[14]=37.14;
			m_DRI[15]=41.75;
			m_DRI[16]=45.63;
			m_DRI[17]=50.78;
			m_DRI[18]=56.47;
			m_DRI[19]=60.08;
			m_DRI[20]=61.97;
			m_DRI[21]=63.67;
			m_DRI[22]=65.46;
			m_DRI[23]=66.25;
			m_DRI[24]=66.41;

			m_NIIA=26; 
			m_DRIIA.resize(m_NIIA);  
			m_RoIIA.resize(m_NIIA);  
			m_RoIIA[1]=0.358;m_RoIIA[2]=0.406;m_RoIIA[3]=0.429;m_RoIIA[4]=0.466;m_RoIIA[5]=0.515;m_RoIIA[6]=0.575;m_RoIIA[7]=0.626;m_RoIIA[8]=0.683;
			m_RoIIA[9]=0.730;m_RoIIA[10]=0.802;m_RoIIA[11]=0.856;m_RoIIA[12]=0.901;m_RoIIA[13]=0.958;m_RoIIA[14]=1.014;m_RoIIA[15]=1.051;m_RoIIA[16]=1.089;m_RoIIA[17]=1.146;
			m_RoIIA[18]=1.223;m_RoIIA[19]=1.286;m_RoIIA[20]=1.358;m_RoIIA[21]=1.445;m_RoIIA[22]=1.565;m_RoIIA[23]=1.765;m_RoIIA[24]=2.030;m_RoIIA[25]=2.448;
			
			m_DRIIA[0]=0;m_DRIIA[1]=0.63;m_DRIIA[2]=1.41;m_DRIIA[3]=1.85;m_DRIIA[4]=2.46;m_DRIIA[5]=3.61;m_DRIIA[6]=5.49;m_DRIIA[7]=7.28;m_DRIIA[8]=9.61;
			m_DRIIA[9]=11.49;m_DRIIA[10]=14.82;m_DRIIA[11]=17.79;m_DRIIA[12]=20.76;m_DRIIA[13]=24.73;m_DRIIA[14]=28.97;m_DRIIA[15]=31.77;m_DRIIA[16]=34.39;m_DRIIA[17]=37.91;
			m_DRIIA[18]=41.88;m_DRIIA[19]=43.76;m_DRIIA[20]=45.20;m_DRIIA[21]=46.09;m_DRIIA[22]=46.61;m_DRIIA[23]=47.03;m_DRIIA[24]=47.18;m_DRIIA[25]=47.22;

			m_NIIB=22; 
			m_DRIIB.resize(m_NIIB);  
			m_RoIIB.resize(m_NIIB);  
			m_RoIIB[0]=0.2;m_RoIIB[1]=0.374;m_RoIIB[2]=0.429;m_RoIIB[3]=0.477;m_RoIIB[4]=0.520;m_RoIIB[5]=0.567;m_RoIIB[6]=0.619;m_RoIIB[7]=0.671;m_RoIIB[8]=0.724;m_RoIIB[9]=0.792;m_RoIIB[10]=0.838;
			m_RoIIB[11]=0.896;m_RoIIB[12]=0.958;m_RoIIB[13]=1.038;m_RoIIB[14]=1.124;m_RoIIB[15]=1.201;m_RoIIB[16]=1.261;m_RoIIB[17]=1.356;m_RoIIB[18]=1.435;m_RoIIB[19]=1.595;m_RoIIB[20]=1.861;m_RoIIB[21]=2.355;
			m_DRIIB[0]=0;m_DRIIB[1]=0.62;m_DRIIB[2]=1.13;m_DRIIB[3]=1.91;m_DRIIB[4]=2.71;m_DRIIB[5]=3.68;m_DRIIB[6]=5.20;m_DRIIB[7]=7.17;m_DRIIB[8]=9.23;m_DRIIB[9]=11.83;m_DRIIB[10]=13.63;
			m_DRIIB[11]=15.79;m_DRIIB[12]=17.76;m_DRIIB[13]=20.37;m_DRIIB[14]=22.97;m_DRIIB[15]=25.22;m_DRIIB[16]=26.47;m_DRIIB[17]=27.45;m_DRIIB[18]=27.80;m_DRIIB[19]=28.22;m_DRIIB[20]=28.36;m_DRIIB[21]=28.57;

			m_NIII=16; 
			m_DRIII.resize(m_NIII);  
			m_RoIII.resize(m_NIII);  
			m_RoIII[0]=0.2;m_RoIII[1]=0.418;m_RoIII[2]=0.462;m_RoIII[3]=0.510;m_RoIII[4]=0.568;m_RoIII[5]=0.641;m_RoIII[6]=0.720;m_RoIII[7]=0.823;
			m_RoIII[8]=0.906;m_RoIII[9]=1.006;m_RoIII[10]=1.130;m_RoIII[11]=1.239;m_RoIII[12]=1.361;m_RoIII[13]=1.510;m_RoIII[14]=1.665;m_RoIII[15]=1.887;
			m_DRIII[0]=0;m_DRIII[1]=0.228;m_DRIII[2]=0.745;m_DRIII[3]=1.444;m_DRIII[4]=2.502;m_DRIII[5]=3.738;m_DRIII[6]=5.066;m_DRIII[7]=6.390;
			m_DRIII[8]=7.361;m_DRIII[9]=8.239;m_DRIII[10]=9.114;m_DRIII[11]=9.724;m_DRIII[12]=10.243;m_DRIII[13]=10.759;m_DRIII[14]=11.005;m_DRIII[15]=11.244;

			m_NGDR=21; 
			m_GDR.resize(m_NGDR);
			m_RoGDR.resize(m_NGDR);
			m_RoGDR[0]=0.200;m_RoGDR[1]=0.221;m_RoGDR[2]=0.435;m_RoGDR[3]=0.642;m_RoGDR[4]=0.823;m_RoGDR[5]=0.965;m_RoGDR[6]=1.172;m_RoGDR[7]=1.340;m_RoGDR[8]=1.527;m_RoGDR[9]=1.662;
			m_RoGDR[10]=1.785;m_RoGDR[11]=1.913;m_RoGDR[12]=2.042;m_RoGDR[13]=2.190;m_RoGDR[14]=2.337;m_RoGDR[15]=2.498;m_RoGDR[16]=2.620;m_RoGDR[17]=2.736;m_RoGDR[18]=2.897;m_RoGDR[19]=3.039;m_RoGDR[20]=3.201;
			m_GDR[0]=0.0000;m_GDR[1]=0.0055;m_GDR[2]=0.0273;m_GDR[3]=0.0573;m_GDR[4]=0.0914;m_GDR[5]=0.1228;m_GDR[6]=0.1760;m_GDR[7]=0.2251;m_GDR[8]=0.2865;m_GDR[9]=0.3397;
			m_GDR[10]=0.3874;m_GDR[11]=0.4461;m_GDR[12]=0.5075;m_GDR[13]=0.5894;m_GDR[14]=0.6780;m_GDR[15]=0.7667;m_GDR[16]=0.8349;m_GDR[17]=0.8868;m_GDR[18]=0.9482;m_GDR[19]=0.9850;m_GDR[20]=1.0000;
			
			m_COG=0.96;
			GetTotalDR();
		}
		KerogenDegradation(const KerogenDegradation &other)
		{
			*this = other;
		}
		const KerogenDegradation &operator=(const KerogenDegradation &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_NKerogen = other.m_NKerogen;
			m_Ratio = other.m_Ratio;
			m_NI = other.m_NI;
			m_DRI = other.m_DRI;
			m_RoI = other.m_RoI;
			m_NIIA = other.m_NIIA;
			m_DRIIA = other.m_DRIIA;
			m_RoIIA = other.m_RoIIA;
			m_NIIB = other.m_NIIB;
			m_DRIIB = other.m_DRIIB;
			m_RoIIB = other.m_RoIIB;
			m_NIII = other.m_NIII;
			m_DRIII = other.m_DRIII;
			m_RoIII = other.m_RoIII;
			m_NGDR = other.m_NGDR;
			m_GDR = other.m_GDR;
			m_RoGDR = other.m_RoGDR;
			m_COG = other.m_COG;
			m_HCFromDRI = other.m_HCFromDRI;
			m_HCFromDRIIA = other.m_HCFromDRIIA;
			m_HCFromDRIIB = other.m_HCFromDRIIB;
			m_HCFromDRIII = other.m_HCFromDRIII;
			m_InitTOCI = other.m_InitTOCI;
			m_InitTOCIIA = other.m_InitTOCIIA;
			m_InitTOCIIB = other.m_InitTOCIIB;
			m_InitTOCIII = other.m_InitTOCIII;
			m_MassInitTOCI = other.m_MassInitTOCI;
			m_MassInitTOCIIA = other.m_MassInitTOCIIA;
			m_MassInitTOCIIB = other.m_MassInitTOCIIB;
			m_MassInitTOCIII = other.m_MassInitTOCIII;
			m_GasRatio = other.m_GasRatio;
			m_HCGIPerUnitInitTOC_I = other.m_HCGIPerUnitInitTOC_I;
			m_HCGIPerUnitInitTOC_IIA = other.m_HCGIPerUnitInitTOC_IIA;
			m_HCGIPerUnitInitTOC_IIB = other.m_HCGIPerUnitInitTOC_IIB;
			m_HCGIPerUnitInitTOC_III = other.m_HCGIPerUnitInitTOC_III;
			m_OGIPerUnitInitTOC_I = other.m_OGIPerUnitInitTOC_I;
			m_OGIPerUnitInitTOC_IIA = other.m_OGIPerUnitInitTOC_IIA;
			m_OGIPerUnitInitTOC_IIB = other.m_OGIPerUnitInitTOC_IIB;
			m_OGIPerUnitInitTOC_III = other.m_OGIPerUnitInitTOC_III;
			m_GGIPerUnitInitTOC_I = other.m_GGIPerUnitInitTOC_I;
			m_GGIPerUnitInitTOC_IIA = other.m_GGIPerUnitInitTOC_IIA;
			m_GGIPerUnitInitTOC_IIB = other.m_GGIPerUnitInitTOC_IIB;
			m_GGIPerUnitInitTOC_III = other.m_GGIPerUnitInitTOC_III;
			m_TotalDR = other.m_TotalDR;
			m_TRO = other.m_TRO;
			m_TRG = other.m_TRG;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(int);//int m_NKerogen;
			curSize += (sizeof(int) + m_Ratio.size() * sizeof(double));//std::vector<double> m_Ratio;
			curSize += sizeof(int);//int m_NI;
			curSize += (sizeof(int) + m_DRI.size() * sizeof(double));//std::vector<double> m_DRI;
			curSize += (sizeof(int) + m_RoI.size() * sizeof(double));//std::vector<double> m_RoI;
			curSize += sizeof(int);//int m_NIIA;
			curSize += (sizeof(int) + m_DRIIA.size() * sizeof(double));//std::vector<double> m_DRIIA;
			curSize += (sizeof(int) + m_RoIIA.size() * sizeof(double));//std::vector<double> m_RoIIA;
			curSize += sizeof(int);//int m_NIIB;
			curSize += (sizeof(int) + m_DRIIB.size() * sizeof(double));//std::vector<double> m_DRIIB
			curSize += (sizeof(int) + m_RoIIB.size() * sizeof(double));//std::vector<double> m_RoIIB;
			curSize += sizeof(int);//int m_NIII;
			curSize += (sizeof(int) + m_DRIII.size() * sizeof(double));//std::vector<double> m_DRIII;
			curSize += (sizeof(int) + m_RoIII.size() * sizeof(double));//std::vector<double> m_RoIII;
			curSize += sizeof(int);//int m_NGDR;
			curSize += (sizeof(int) + m_GDR.size() * sizeof(double));//std::vector<double> m_GDR;
			curSize += (sizeof(int) + m_RoGDR.size() * sizeof(double));//std::vector<double> m_RoGDR;
			curSize += sizeof(double);//double m_COG;
			curSize += sizeof(double);//double m_HCFromDRI;
			curSize += sizeof(double);//double m_HCFromDRIIA;
			curSize += sizeof(double);//double m_HCFromDRIIB;
			curSize += sizeof(double);//double m_HCFromDRIII; 
			curSize += sizeof(double);//double m_InitTOCI;
			curSize += sizeof(double);//double m_InitTOCIIA;
			curSize += sizeof(double);//double m_InitTOCIIB;
			curSize += sizeof(double);//double m_InitTOCIII; 
			curSize += sizeof(double);//double m_MassInitTOCI;
			curSize += sizeof(double);//double m_MassInitTOCIIA;
			curSize += sizeof(double);//double m_MassInitTOCIIB;
			curSize += sizeof(double);//double m_MassInitTOCIII; 
			curSize += sizeof(double);//double m_GasRatio;
			curSize += sizeof(double);//double m_HCGIPerUnitInitTOC_I;
			curSize += sizeof(double);//double m_HCGIPerUnitInitTOC_IIA;
			curSize += sizeof(double);//double m_HCGIPerUnitInitTOC_IIB;
			curSize += sizeof(double);//double m_HCGIPerUnitInitTOC_III; 
			curSize += sizeof(double);//double m_OGIPerUnitInitTOC_I;
			curSize += sizeof(double);//double m_OGIPerUnitInitTOC_IIA;
			curSize += sizeof(double);//double m_OGIPerUnitInitTOC_IIB;
			curSize += sizeof(double);//double m_OGIPerUnitInitTOC_III; 
			curSize += sizeof(double);//double m_GGIPerUnitInitTOC_I;
			curSize += sizeof(double);//double m_GGIPerUnitInitTOC_IIA;
			curSize += sizeof(double);//double m_GGIPerUnitInitTOC_IIB;
			curSize += sizeof(double);//double m_GGIPerUnitInitTOC_III;  
			curSize += sizeof(double);//double m_TotalDR;  
			curSize += sizeof(double);//double m_TRO;  
			curSize += sizeof(double);//double m_TRG;  
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_NKerogen), sizeof(int));data += sizeof(int);
			int Ratiosize = m_Ratio.size();
			memcpy(data, &Ratiosize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < Ratiosize; j++)
			{
				memcpy(data, &(m_Ratio[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_NI), sizeof(int));data += sizeof(int);
			int DRIsize = m_DRI.size();
			memcpy(data, &DRIsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < DRIsize; j++)
			{
				memcpy(data, &(m_DRI[j]), sizeof(double));data += sizeof(double);
			}
			int RoIsize = m_RoI.size();
			memcpy(data, &RoIsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < RoIsize; j++)
			{
				memcpy(data, &(m_RoI[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_NIIA), sizeof(int));data += sizeof(int);
			int DRIIAsize = m_DRIIA.size();
			memcpy(data, &DRIIAsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < DRIIAsize; j++)
			{
				memcpy(data, &(m_DRIIA[j]), sizeof(double));data += sizeof(double);
			}
			int RoIIAsize = m_RoIIA.size();
			memcpy(data, &RoIIAsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < RoIIAsize; j++)
			{
				memcpy(data, &(m_RoIIA[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_NIIB), sizeof(int));data += sizeof(int);
			int DRIIBsize = m_DRIIB.size();
			memcpy(data, &DRIIBsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < DRIIBsize; j++)
			{
				memcpy(data, &(m_DRIIB[j]), sizeof(double));data += sizeof(double);
			}
			int RoIIBsize = m_RoIIB.size();
			memcpy(data, &RoIIBsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < RoIIBsize; j++)
			{
				memcpy(data, &(m_RoIIB[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_NIII), sizeof(int));data += sizeof(int);
			int DRIIIsize = m_DRIII.size();
			memcpy(data, &DRIIIsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < DRIIIsize; j++)
			{
				memcpy(data, &(m_DRIII[j]), sizeof(double));data += sizeof(double);
			}
			int RoIIIsize = m_RoIII.size();
			memcpy(data, &RoIIIsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < RoIIIsize; j++)
			{
				memcpy(data, &(m_RoIII[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_NGDR), sizeof(int));data += sizeof(int);
			int GDRsize = m_GDR.size();
			memcpy(data, &GDRsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < GDRsize; j++)
			{
				memcpy(data, &(m_GDR[j]), sizeof(double));data += sizeof(double);
			}
			int RoGDRsize = m_RoGDR.size();
			memcpy(data, &RoGDRsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < RoGDRsize; j++)
			{
				memcpy(data, &(m_RoGDR[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_COG), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCFromDRI), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCFromDRIIA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCFromDRIIB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCFromDRIII), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_InitTOCI), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_InitTOCIIA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_InitTOCIIB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_InitTOCIII), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_MassInitTOCI), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MassInitTOCIIA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MassInitTOCIIB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MassInitTOCIII), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_GasRatio), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCGIPerUnitInitTOC_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCGIPerUnitInitTOC_IIA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCGIPerUnitInitTOC_IIB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HCGIPerUnitInitTOC_III), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_OGIPerUnitInitTOC_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OGIPerUnitInitTOC_IIA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OGIPerUnitInitTOC_IIB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OGIPerUnitInitTOC_III), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_GGIPerUnitInitTOC_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GGIPerUnitInitTOC_IIA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GGIPerUnitInitTOC_IIB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GGIPerUnitInitTOC_III), sizeof(double));data += sizeof(double);  
			memcpy(data, &(m_TotalDR), sizeof(double));data += sizeof(double);  
			memcpy(data, &(m_TRO), sizeof(double));data += sizeof(double);  
			memcpy(data, &(m_TRG), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_NKerogen), data, sizeof(int));data += sizeof(int);
			int Ratiosize;
			memcpy(&Ratiosize, data, sizeof(int));data += sizeof(int);
			m_Ratio.resize(Ratiosize);
			for(int j = 0; j < Ratiosize; j++)
			{
				memcpy(&(m_Ratio[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_NI), data, sizeof(int));data += sizeof(int);
			int DRIsize;
			memcpy(&DRIsize, data, sizeof(int));data += sizeof(int);
			m_DRI.resize(DRIsize);
			for(int j = 0; j < DRIsize; j++)
			{
				memcpy(&(m_DRI[j]), data, sizeof(double));data += sizeof(double);
			}
			int RoIsize;
			memcpy(&RoIsize, data, sizeof(int));data += sizeof(int);
			m_RoI.resize(RoIsize);
			for(int j = 0; j < RoIsize; j++)
			{
				memcpy(&(m_RoI[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_NIIA), data, sizeof(int));data += sizeof(int);
			int DRIIAsize;
			memcpy(&DRIIAsize, data, sizeof(int));data += sizeof(int);
			m_DRIIA.resize(DRIIAsize);
			for(int j = 0; j < DRIIAsize; j++)
			{
				memcpy(&(m_DRIIA[j]), data, sizeof(double));data += sizeof(double);
			}
			int RoIIAsize;
			memcpy(&RoIIAsize, data, sizeof(int));data += sizeof(int);
			m_RoIIA.resize(RoIIAsize);
			for(int j = 0; j < RoIIAsize; j++)
			{
				memcpy(&(m_RoIIA[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_NIIB), data, sizeof(int));data += sizeof(int);
			int DRIIBsize;
			memcpy(&DRIIBsize, data, sizeof(int));data += sizeof(int);
			m_DRIIB.resize(DRIIBsize);
			for(int j = 0; j < DRIIBsize; j++)
			{
				memcpy(&(m_DRIIB[j]), data, sizeof(double));data += sizeof(double);
			}
			int RoIIBsize;
			memcpy(&RoIIBsize, data, sizeof(int));data += sizeof(int);
			m_RoIIB.resize(RoIIBsize);
			for(int j = 0; j < RoIIBsize; j++)
			{
				memcpy(&(m_RoIIB[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_NIII), data, sizeof(int));data += sizeof(int);
			int DRIIIsize;
			memcpy(&DRIIIsize, data, sizeof(int));data += sizeof(int);
			m_DRIII.resize(DRIIIsize);
			for(int j = 0; j < DRIIIsize; j++)
			{
				memcpy(&(m_DRIII[j]), data, sizeof(double));data += sizeof(double);
			}
			int RoIIIsize;
			memcpy(&RoIIIsize, data, sizeof(int));data += sizeof(int);
			m_RoIII.resize(RoIIIsize);
			for(int j = 0; j < RoIIIsize; j++)
			{
				memcpy(&(m_RoIII[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_NGDR), data, sizeof(int));data += sizeof(int);
			int GDRsize;
			memcpy(&GDRsize, data, sizeof(int));data += sizeof(int);
			m_GDR.resize(GDRsize);
			for(int j = 0; j < GDRsize; j++)
			{
				memcpy(&(m_GDR[j]), data, sizeof(double));data += sizeof(double);
			}
			int RoGDRsize;
			memcpy(&RoGDRsize, data, sizeof(int));data += sizeof(int);
			m_RoGDR.resize(RoGDRsize);
			for(int j = 0; j < RoGDRsize; j++)
			{
				memcpy(&(m_RoGDR[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_COG), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCFromDRI), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCFromDRIIA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCFromDRIIB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCFromDRIII), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_InitTOCI), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_InitTOCIIA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_InitTOCIIB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_InitTOCIII), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_MassInitTOCI), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MassInitTOCIIA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MassInitTOCIIB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MassInitTOCIII), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_GasRatio), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCGIPerUnitInitTOC_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCGIPerUnitInitTOC_IIA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCGIPerUnitInitTOC_IIB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HCGIPerUnitInitTOC_III), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_OGIPerUnitInitTOC_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OGIPerUnitInitTOC_IIA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OGIPerUnitInitTOC_IIB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OGIPerUnitInitTOC_III), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_GGIPerUnitInitTOC_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GGIPerUnitInitTOC_IIA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GGIPerUnitInitTOC_IIB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GGIPerUnitInitTOC_III), data, sizeof(double));data += sizeof(double);  
			memcpy(&(m_TotalDR), data, sizeof(double));data += sizeof(double);  
			memcpy(&(m_TRO), data, sizeof(double));data += sizeof(double);  
			memcpy(&(m_TRG), data, sizeof(double));data += sizeof(double); 
		}
		friend std::ofstream &operator << (std::ofstream &os, KerogenDegradation &kerogen)
		{
			os << "\r\n>>>>>>>>>>>>>>>KerogenDegradation parameter as flow:"; 
			os << "\r\n---- ---- ---- NKerogen:" << kerogen.m_NKerogen;
			for(int i = 0; i < kerogen.m_Ratio.size(); i++)os << "\r\n---- ---- ---- m_Ratio:" << i << ":" << kerogen.m_Ratio[i];
			os << "\r\n---- ---- ---- NI:" << kerogen.m_NI;
			for(int i = 0; i < kerogen.m_DRI.size(); i++)os << "\r\n---- ---- ---- m_DRI:" << i << ":" << kerogen.m_DRI[i];
			for(int i = 0; i < kerogen.m_RoI.size(); i++)os << "\r\n---- ---- ---- m_RoI:" << i << ":" << kerogen.m_RoI[i];
			os << "\r\n---- ---- ---- NIIA:" << kerogen.m_NIIA;
			for(int i = 0; i < kerogen.m_DRIIA.size(); i++)os << "\r\n---- ---- ---- m_DRIIA:" << i << ":" << kerogen.m_DRIIA[i];
			for(int i = 0; i < kerogen.m_RoIIA.size(); i++)os << "\r\n---- ---- ---- m_RoIIA:" << i << ":" << kerogen.m_RoIIA[i];
			os << "\r\n---- ---- ---- NIIB:" << kerogen.m_NIIB;
			for(int i = 0; i < kerogen.m_DRIIB.size(); i++)os << "\r\n---- ---- ---- m_DRIIB:" << i << ":" << kerogen.m_DRIIB[i];
			for(int i = 0; i < kerogen.m_RoIIB.size(); i++)os << "\r\n---- ---- ---- m_RoIIB:" << i << ":" << kerogen.m_RoIIB[i];
			os << "\r\n---- ---- ---- NIII:" << kerogen.m_NIII;
			for(int i = 0; i < kerogen.m_DRIII.size(); i++)os << "\r\n---- ---- ---- m_DRIII:" << i << ":" << kerogen.m_DRIII[i];
			for(int i = 0; i < kerogen.m_RoIII.size(); i++)os << "\r\n---- ---- ---- m_RoIII:" << i << ":" << kerogen.m_RoIII[i];
			os << "\r\n---- ---- ---- NGDR:" << kerogen.m_NGDR;
			for(int i = 0; i < kerogen.m_GDR.size(); i++)os << "\r\n---- ---- ---- m_GDR:" << i << ":" << kerogen.m_GDR[i];
			for(int i = 0; i < kerogen.m_RoGDR.size(); i++)os << "\r\n---- ---- ---- m_RoGDR:" << i << ":" << kerogen.m_RoGDR[i];
			os << "\r\n---- ---- ---- COG:" << kerogen.m_COG;
			os << "\r\n---- ---- ---- HCFromDRI:" << kerogen.m_HCFromDRI;
			os << "\r\n---- ---- ---- HCFromDRIIA:" << kerogen.m_HCFromDRIIA;
			os << "\r\n---- ---- ---- HCFromDRIIB:" << kerogen.m_HCFromDRIIB;
			os << "\r\n---- ---- ---- HCFromDRIII:" << kerogen.m_HCFromDRIII;
			os << "\r\n---- ---- ---- InitTOCI:" << kerogen.m_InitTOCI;
			os << "\r\n---- ---- ---- InitTOCIIA:" << kerogen.m_InitTOCIIA;
			os << "\r\n---- ---- ---- InitTOCIIB:" << kerogen.m_InitTOCIIB;
			os << "\r\n---- ---- ---- InitTOCIII:" << kerogen.m_InitTOCIII;
			os << "\r\n---- ---- ---- MassInitTOCI:" << kerogen.m_MassInitTOCI;
			os << "\r\n---- ---- ---- MassInitTOCIIA:" << kerogen.m_MassInitTOCIIA;
			os << "\r\n---- ---- ---- MassInitTOCIIB:" << kerogen.m_MassInitTOCIIB;
			os << "\r\n---- ---- ---- MassInitTOCIII:" << kerogen.m_MassInitTOCIII;
			os << "\r\n---- ---- ---- GasRatio:" << kerogen.m_GasRatio;
			os << "\r\n---- ---- ---- HCGIPerUnitInitTOC_I:" << kerogen.m_HCGIPerUnitInitTOC_I;
			os << "\r\n---- ---- ---- HCGIPerUnitInitTOC_IIA:" << kerogen.m_HCGIPerUnitInitTOC_IIA;
			os << "\r\n---- ---- ---- HCGIPerUnitInitTOC_IIB:" << kerogen.m_HCGIPerUnitInitTOC_IIB;
			os << "\r\n---- ---- ---- HCGIPerUnitInitTOC_III:" << kerogen.m_HCGIPerUnitInitTOC_III;
			os << "\r\n---- ---- ---- OGIPerUnitInitTOC_I:" << kerogen.m_OGIPerUnitInitTOC_I;
			os << "\r\n---- ---- ---- OGIPerUnitInitTOC_IIA:" << kerogen.m_OGIPerUnitInitTOC_IIA;
			os << "\r\n---- ---- ---- OGIPerUnitInitTOC_IIB:" << kerogen.m_OGIPerUnitInitTOC_IIB;
			os << "\r\n---- ---- ---- OGIPerUnitInitTOC_III:" << kerogen.m_OGIPerUnitInitTOC_III;
			os << "\r\n---- ---- ---- GGIPerUnitInitTOC_I:" << kerogen.m_GGIPerUnitInitTOC_I;
			os << "\r\n---- ---- ---- GGIPerUnitInitTOC_IIA:" << kerogen.m_GGIPerUnitInitTOC_IIA;
			os << "\r\n---- ---- ---- GGIPerUnitInitTOC_IIB:" << kerogen.m_GGIPerUnitInitTOC_IIB;
			os << "\r\n---- ---- ---- GGIPerUnitInitTOC_III:" << kerogen.m_GGIPerUnitInitTOC_III;
			os << "\r\n---- ---- ---- TotalDR:" << kerogen.m_TotalDR;
			os << "\r\n---- ---- ---- TRO:" << kerogen.m_TRO;
			os << "\r\n---- ---- ---- TRG:" << kerogen.m_TRG;
			return os;
		}
		double LinerInterpolate(double t,double t0,double p0,double t1,double p1)
		{
			return p1-(p1-p0)*(t1-t)/(t1-t0);
		}
		void GetTotalDR()
		{ 
			m_TotalDR=m_Ratio[0]*m_DRI[m_NI-1]+m_Ratio[1]*m_DRIIA[m_NIIA-1]+m_Ratio[2]*m_DRIIB[m_NIIB-1]+m_Ratio[3]*m_DRIII[m_NIII-1];
			m_TotalDR/=100.;
		}
		void GetTR()
		{   //����ͺ�����ת����
			m_TRO=m_OGIPerUnitInitTOC_I*m_Ratio[0]+m_OGIPerUnitInitTOC_IIA*m_Ratio[1]+m_OGIPerUnitInitTOC_IIB*m_Ratio[2]+m_OGIPerUnitInitTOC_III*m_Ratio[3];
			m_TRO=m_TRO/m_TotalDR;
			m_TRG=m_GGIPerUnitInitTOC_I*m_Ratio[0]+m_GGIPerUnitInitTOC_IIA*m_Ratio[1]+m_GGIPerUnitInitTOC_IIB*m_Ratio[2]+m_GGIPerUnitInitTOC_III*m_Ratio[3];
			m_TRG=m_TRG/m_TotalDR;
		}
		void GetHCFromDR(double Ro)
		{
			if(Ro<=m_RoI[0]) m_HCFromDRI=m_DRI[0];
			else if(Ro>= m_RoI[ m_NI-1])m_HCFromDRI= m_DRI[ m_NI-1];
			else {for(int i=0;i< m_NI-1;i++) if(Ro> m_RoI[i]&&Ro<= m_RoI[i+1]) m_HCFromDRI=LinerInterpolate(Ro, m_RoI[i], m_DRI[i], m_RoI[i+1], m_DRI[i+1]);}
			
			if(Ro<= m_RoIIA[0]) m_HCFromDRIIA= m_DRIIA[0];
			else if(Ro>= m_RoIIA[ m_NIIA-1])m_HCFromDRIIA= m_DRIIA[ m_NIIA-1];
			else {for(int i=0;i< m_NIIA-1;i++) if(Ro> m_RoIIA[i]&&Ro<= m_RoIIA[i+1]) m_HCFromDRIIA=LinerInterpolate(Ro, m_RoIIA[i], m_DRIIA[i], m_RoIIA[i+1], m_DRIIA[i+1]);}
			
			if(Ro<= m_RoIIB[0]) m_HCFromDRIIB= m_DRIIB[0];
			else if(Ro>= m_RoIIB[ m_NIIB-1])m_HCFromDRIIB= m_DRIIB[ m_NIIB-1];
			else {for(int i=0;i< m_NIIB-1;i++) if(Ro> m_RoIIB[i]&&Ro<= m_RoIIB[i+1]) m_HCFromDRIIB=LinerInterpolate(Ro, m_RoIIB[i], m_DRIIB[i], m_RoIIB[i+1], m_DRIIB[i+1]);}
			
			if(Ro<= m_RoIII[0]) m_HCFromDRIII= m_DRIII[0];
			else if(Ro>= m_RoIII[ m_NIII-1])m_HCFromDRIII= m_DRIII[ m_NIII-1];
			else {for(int i=0;i< m_NIII-1;i++) if(Ro> m_RoIII[i]&&Ro<= m_RoIII[i+1]) m_HCFromDRIII=LinerInterpolate(Ro, m_RoIII[i], m_DRIII[i], m_RoIII[i+1], m_DRIII[i+1]);}
			
			if(Ro<= m_RoGDR[0]) m_GasRatio= m_DRIII[0];
			else if(Ro>= m_RoGDR[ m_NGDR-1])m_GasRatio= m_GDR[ m_NGDR-1];
			else {for(int i=0;i< m_NGDR-1;i++) if(Ro> m_RoGDR[i]&&Ro<= m_RoGDR[i+1]) m_GasRatio=LinerInterpolate(Ro, m_RoGDR[i], m_GDR[i], m_RoGDR[i+1], m_GDR[i+1]);}
			
			m_HCGIPerUnitInitTOC_I=m_HCFromDRI/100./0.84; 
			m_HCGIPerUnitInitTOC_IIA=m_HCFromDRIIA/100./0.84;
			m_HCGIPerUnitInitTOC_IIB=m_HCFromDRIIB/100./0.84; 
			m_HCGIPerUnitInitTOC_III=m_HCFromDRIII/100./0.84;

			m_OGIPerUnitInitTOC_I=m_HCGIPerUnitInitTOC_I*(1.0-m_GasRatio);
			m_OGIPerUnitInitTOC_IIA=m_HCGIPerUnitInitTOC_IIA*(1.0-m_GasRatio);
			m_OGIPerUnitInitTOC_IIB=m_HCGIPerUnitInitTOC_IIB*(1.0-m_GasRatio);
			m_OGIPerUnitInitTOC_III=m_HCGIPerUnitInitTOC_III*(1.0-m_GasRatio);

			m_GGIPerUnitInitTOC_I=m_HCGIPerUnitInitTOC_I*m_GasRatio;
			m_GGIPerUnitInitTOC_IIA=m_HCGIPerUnitInitTOC_IIA*m_GasRatio;    //���������Ҳ��kg��ʾ�����ٳ���COGת��Ϊ������
			m_GGIPerUnitInitTOC_IIB=m_HCGIPerUnitInitTOC_IIB*m_GasRatio;
			m_GGIPerUnitInitTOC_III=m_HCGIPerUnitInitTOC_III*m_GasRatio;
			GetTR();
		}
	};

	enum PetroGenStyle {LLNL,Organo,Behar4C};  //�������ɶ���ѧģ������ ��{LLNLģ�ͣ��л���ģ��,Behar����� }
	enum OrganoFaciesStyle{A,B,C,DE,F}; //����һ���л�������ö����
	enum BeharKinetics {TI,TII,TIIS,TIIIMahak,TIIINorthSea}; //��������Behar 1997 �������Ҹ�����
	enum RoType{EasyRoType,BasinRoType,SimpleRoType}; //ѡ�����Ro��ģ��

	 //����ΪBasinMod LLNL I��,II�ͺ�III�͸��Ҹ��Ļ�ѧ����ѧ����
	struct LLNLKinetics
	{
		//����ΪI�͸��Ҹ��Ķ���ѧ����
		double m_W; //��������Ϊ�л�̼�ı���  =0.85
		int m_NKerogenType;   //���Ҹ�������
		std::vector<double> m_RatioKerogenType; // ���Ҹ�����
		std::vector<double> m_InitTOC;//ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
		std::vector<double> m_MassOfInitTOC; //ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
		double m_MassOfInitTOCTotal; //���Ҹ�ԭʼ�л�̼�ܵ�����
		std::vector<double> m_MKer; //ÿ�ָ��Ҹ����л�̼�������ݻ������б仯������������Ҹ����������������¼���20170908
		double m_MKerTotal; //�ܵĸ��Ҹ��л�̼�����������������ѽ�Ľ�̿���� ���¼���20170908

		double m_HI_LLNL_I; //I�͸��Ҹ�����ָ��
		double m_KSF_LLNL_I;//   Kerogen Start Fraction  LLNL��I�͸��Ҹ� ��Ӧ����Ҹ���ʼ�� 
		double m_KToOilF_LLNL_I;// ���Ҹ������͵ı���
		double m_KToGasF_LLNL_I; //  ���Ҹ��������ı���
		double m_OSF_LLNL_I;  // Oil Strat Fraction ��Ӧ��������ʼ����
		double m_OToGasF_LLNL_I; //���������ı���
		double m_OToResidueF_LLNL_I; //�����ɲ�����ı���

		int m_N_LLNL_I_KToOil;//LLNL��I�͸��Ҹ����͵�ƽ�з�Ӧ�����
		std::vector<double> m_fLLNL_I_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_ELLNL_I_KToOil;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_I_KToOil; //Frequency factor

		int m_N_LLNL_I_KToGas;//LLNL��I�͸��Ҹ�������ƽ�з�Ӧ�����
		std::vector<double> m_fLLNL_I_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_ELLNL_I_KToGas;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_I_KToGas; //Frequency factor,Ƶ������
		
		int m_N_LLNL_I_OilToGas;//LLNL��I�͸��Ҹ����������ķ�Ӧ�����
		std::vector<double> m_fLLNL_I_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fLLNL_I_OilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_ELLNL_I_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_I_OilToGas; //Frequency factor
		
		int m_N_LLNL_I_OilToResidue;//LLNL��I�͸��Ҹ������ɲ�����ķ�Ӧ�����
		std::vector<double> m_fLLNL_I_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fLLNL_I_OilToResidueBak;  //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_ELLNL_I_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_I_OilToResidue; //Frequency factor
		//����ΪLLNL II�͸��Ҹ�����
		double m_HI_LLNL_II; //II�͸��Ҹ�����ָ��
		double m_KSF_LLNL_II;//   Kerogen Start Fraction  LLNL��II�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
		double m_KToOilF_LLNL_II;// ���Ҹ������͵ı���
		double m_KToGasF_LLNL_II; //  ���Ҹ��������ı���
		double m_OSF_LLNL_II;  // Oil Strat Fraction ��Ӧ��������ʼ����
		double m_OToGasF_LLNL_II; //���������ı���
		double m_OToResidueF_LLNL_II; //�����ɲ�����ı���

		int m_N_LLNL_II_KToOil;//LLNL��II�͸��Ҹ����͵�ƽ�з�Ӧ�����
		std::vector<double> m_fLLNL_II_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_ELLNL_II_KToOil;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_II_KToOil; //Frequency factor
		
		int m_N_LLNL_II_KToGas;//LLNL��II�͸��Ҹ�������ƽ�з�Ӧ�����
		std::vector<double> m_fLLNL_II_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_ELLNL_II_KToGas;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_II_KToGas; //Frequency factor
		
		int m_N_LLNL_II_OilToGas;//LLNL��II�͸��Ҹ����������ķ�Ӧ�����
		std::vector<double> m_fLLNL_II_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fLLNL_II_OilToGasBak;   //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_ELLNL_II_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_II_OilToGas; //Frequency factor
		
		int m_N_LLNL_II_OilToResidue;//LLNL��II�͸��Ҹ������ɲ�����ķ�Ӧ�����
		std::vector<double> m_fLLNL_II_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fLLNL_II_OilToResidueBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_ELLNL_II_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_II_OilToResidue; //Frequency factor
		
		//����ΪLLNL III�͸��Ҹ�����
		double m_HI_LLNL_III; //III�͸��Ҹ�����ָ��
		double m_KSF_LLNL_III;//   Kerogen Start Fraction  LLNL��III�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
		double m_KToOilF_LLNL_III;// ���Ҹ������͵ı���
		double m_KToGasF_LLNL_III; //  ���Ҹ��������ı���
		double m_OSF_LLNL_III;  // Oil Strat Fraction ��Ӧ��������ʼ����
		double m_OToGasF_LLNL_III; //���������ı���
		double m_OToResidueF_LLNL_III; //�����ɲ�����ı���

		int m_N_LLNL_III_KToOil;//LLNL��III�͸��Ҹ����͵�ƽ�з�Ӧ�����
		std::vector<double> m_fLLNL_III_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_ELLNL_III_KToOil;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_III_KToOil; //Frequency factor
		
		int m_N_LLNL_III_KToGas;//LLNL��III�͸��Ҹ�������ƽ�з�Ӧ�����
		std::vector<double> m_fLLNL_III_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_ELLNL_III_KToGas;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_III_KToGas; //Frequency factor
		
		int m_N_LLNL_III_OilToGas;//LLNL��III�͸��Ҹ����������ķ�Ӧ�����
		std::vector<double> m_fLLNL_III_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fLLNL_III_OilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_ELLNL_III_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_III_OilToGas; //Frequency factor
		
		int m_N_LLNL_III_OilToResidue;//LLNL��III�͸��Ҹ������ɲ�����ķ�Ӧ�����
		std::vector<double> m_fLLNL_III_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_fLLNL_III_OilToResidueBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_ELLNL_III_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
		std::vector<double> m_FFLLNL_III_OilToResidue; //Frequency factor
		
		double m_wBIw0_I_KToOil;
		double m_wBIw0_II_KToOil;
		double m_wBIw0_III_KToOil;//�ֱ���I��II��III�͸��Ҹ��������Ͷ����µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
		double m_wBIw0_I_KToGas;
		double m_wBIw0_II_KToGas;
		double m_wBIw0_III_KToGas;//�ֱ���I��II��III�͸��Ҹ��������������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
		double m_wBIw0_I_OilToGas;
		double m_wBIw0_II_OilToGas;
		double m_wBIw0_III_OilToGas; //�ֱ���I��II��III�͸��Ҹ�������ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
		double m_wBIw0_I_OilToResidue;
		double m_wBIw0_II_OilToResidue;
		double m_wBIw0_III_OilToResidue; //�ֱ���I��II��III�͸��Ҹ�������ѽ�ɲ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1

		double m_OilPerInitTOC_I;
		double m_OilPerInitTOC_II;
		double m_OilPerInitTOC_III; //�ֱ���I��II��III��InitTOC����һʱ��ε�������
		double m_GasPerInitTOC_I;
		double m_GasPerInitTOC_II;
		double m_GasPerInitTOC_III; //�ֱ���I��II��III��InitTOC����һʱ��ε�������
		double m_TOCRemained_I;
		double m_TOCRemained_II;
		double m_TOCRemained_III; //ÿ�����͸��Ҹ��л�̼ʣ���� ����ָ��λ����ԭʼ���Ҹ��Ĳ�����
		double m_OilCracked_I;
		double m_OilCracked_II;
		double m_OilCracked_III; //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ���
		double m_GasCracked_I;
		double m_GasCracked_II;
		double m_GasCracked_III; //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ������
		double m_ResidueCracked_I;
		double m_ResidueCracked_II;
		double m_ResidueCracked_III; //ÿ�ָ��Ҹ���ص�������һʱ��ε��ѽ�ɲ�������
		double m_OilExisted_I;
		double m_OilExisted_II;
		double m_OilExisted_III;   //ÿ�ֵ�λ����ԭʼ���Ҹ������Լ����ѽ�Ϊ������ڵ���
		double m_GasExisted_I;
		double m_GasExisted_II;
		double m_GasExisted_III;   //ÿ�ֵ�λ����ԭʼ���Ҹ������Լ����ѽ����
		double m_ResidueExisted_I;
		double m_ResidueExisted_II;
		double m_ResidueExisted_III;   //ÿ�ֵ�λ����ԭʼ���Ҹ���صĲ�������

		double m_OilGenerated_I;
		double m_OilGenerated_II;
		double m_OilGenerated_III;
		double m_GasGenerated_I;
		double m_GasGenerated_II;
		double m_GasGenerated_III;//�������ۻ����������������Exsited��ͬ���ǵ�λ����ԭʼ�л�̼���ͺ�������
		double m_OilGenerated;
		double m_GasGenerated; //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ���������������
		double m_OilPerInitTOC;
		double m_GasPerInitTOC; //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����������������
		double m_TOCReactableKerogen;
		double m_TOCInertKerogen; //�ֱ��ǿɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ� ����ָ��λԭʼ�л�̼���ڳ�ʼ״̬�Լ���Ӧ�����пɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ�������
		double m_TOCOilKerogen;
		double m_TOCGasKerogen; // new added 20190412�ֱ��ǿɷ�Ӧ�͸��Ҹ��������Ҹ� ����ָ��λԭʼ�л�̼���ڳ�ʼ״̬�Լ���Ӧ�����пɷ�Ӧ�͸��Ҹ��������Ҹ�������
		double m_TOCKerogen; //���Ҹ��л�̼ʣ���� ����ָ��λ����ԭʼ���Ҹ��Ĳ�����
		double m_TOCRemained; //�����л�̼ʣ���� ����ָ��λ����ԭʼ�л�̼���ݻ������еĲ����� ���������Ҹ��л�̼ʣ���� +Դ�����������л�̼����+���ѽ�����Ľ�̿��
		double m_TR; //Դ�ҵ�����ת����

		double m_OilExisted; //ָ���Ǵ�����Դ���е������
		double m_GasExisted; //ָ���Ǵ�����Դ���е������
		double m_GasCracked;//ָ����ÿһ�����ѽ������
		double m_GasCrackedAdded; //ָÿһ���ѽ������ۼ���
		double m_ResidueCracked; // ָ����ÿһ�����ѽ�Ĳ�������
		double m_ResidueCrackedAdded; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
		double m_OilCracked;//ÿһ���͵��ѽ���
		double m_OilCrackedAdded;//ÿһ���͵��ѽ������ۼ���

		double m_MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
		double m_MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
		double m_MKerOil;   //new added 20190412
		double m_MKerGas;  //new added 20190412

		LLNLKinetics()
		{
			m_W=0.85;
			m_NKerogenType=3;
			m_RatioKerogenType.resize(m_NKerogenType);
			m_RatioKerogenType[0]=0.0;m_RatioKerogenType[1]=0.0;m_RatioKerogenType[2]=1.0;
			m_HI_LLNL_I=0.85; //I�͸��Ҹ�����ָ��
			m_KSF_LLNL_I=1.0;//   Kerogen Start Fraction  LLNL��I�͸��Ҹ� ��Ӧ����Ҹ���ʼ�� 
			m_KToOilF_LLNL_I=0.9;// ���Ҹ������͵ı���
			m_KToGasF_LLNL_I=0.1; //  ���Ҹ��������ı���
			m_OSF_LLNL_I=0.;  // Oil Strat Fraction ��Ӧ��������ʼ����
			m_OToGasF_LLNL_I=0.5; //���������ı���
			m_OToResidueF_LLNL_I=0.5; //�����ɲ�����ı���

			m_N_LLNL_I_KToOil=3;//LLNL��I�͸��Ҹ����͵�ƽ�з�Ӧ�����
			m_fLLNL_I_KToOil.resize(m_N_LLNL_I_KToOil);
			m_fLLNL_I_KToOil[0]=0.07;m_fLLNL_I_KToOil[1]=0.9;m_fLLNL_I_KToOil[2]=0.03;
			m_ELLNL_I_KToOil.resize(m_N_LLNL_I_KToOil);
			m_ELLNL_I_KToOil[0]=49;m_ELLNL_I_KToOil[1]=53;m_ELLNL_I_KToOil[2]=54;
			m_FFLLNL_I_KToOil.resize(m_N_LLNL_I_KToOil); //Frequency factor
			m_FFLLNL_I_KToOil[0]=5.07e13;m_FFLLNL_I_KToOil[1]=5.07e13;m_FFLLNL_I_KToOil[2]=5.07e13;

			m_N_LLNL_I_KToGas=3;//LLNL��I�͸��Ҹ�������ƽ�з�Ӧ�����
			m_fLLNL_I_KToGas.resize(m_N_LLNL_I_KToGas);
			m_fLLNL_I_KToGas[0]=0.07;m_fLLNL_I_KToGas[1]=0.9;m_fLLNL_I_KToGas[2]=0.03;
			m_ELLNL_I_KToGas.resize(m_N_LLNL_I_KToGas);
			m_ELLNL_I_KToGas[0]=49;m_ELLNL_I_KToGas[1]=53;m_ELLNL_I_KToGas[2]=54;
			m_FFLLNL_I_KToGas.resize(m_N_LLNL_I_KToGas); //Frequency factor,Ƶ������
			m_FFLLNL_I_KToGas[0]=5.07e13;m_FFLLNL_I_KToGas[1]=5.07e13;m_FFLLNL_I_KToGas[2]=5.07e13;

			m_N_LLNL_I_OilToGas=1;//LLNL��I�͸��Ҹ����������ķ�Ӧ�����
			m_fLLNL_I_OilToGas.resize(m_N_LLNL_I_OilToGas);
			m_fLLNL_I_OilToGas[0]=1;
			m_fLLNL_I_OilToGasBak.resize(m_N_LLNL_I_OilToGas);
			m_fLLNL_I_OilToGasBak[0]=1;
			m_ELLNL_I_OilToGas.resize(m_N_LLNL_I_OilToGas);
			m_ELLNL_I_OilToGas[0]=54;
			m_FFLLNL_I_OilToGas.resize(m_N_LLNL_I_OilToGas); //Frequency factor
			m_FFLLNL_I_OilToGas[0]=1.014e12;

			m_N_LLNL_I_OilToResidue=1;//LLNL��I�͸��Ҹ������ɲ�����ķ�Ӧ�����
			m_fLLNL_I_OilToResidue.resize(m_N_LLNL_I_OilToResidue);
			m_fLLNL_I_OilToResidue[0]=1;
			m_fLLNL_I_OilToResidueBak.resize(m_N_LLNL_I_OilToResidue);
			m_fLLNL_I_OilToResidueBak[0]=1;
			m_ELLNL_I_OilToResidue.resize(m_N_LLNL_I_OilToResidue);
			m_ELLNL_I_OilToResidue[0]=54;
			m_FFLLNL_I_OilToResidue.resize(m_N_LLNL_I_OilToResidue); //Frequency factor
			m_FFLLNL_I_OilToResidue[0]=1.014e12;
			//����ΪLLNL II�͸��Ҹ�����
			m_HI_LLNL_II=0.65; //II�͸��Ҹ�����ָ��
			m_KSF_LLNL_II=1.0;//   Kerogen Start Fraction  LLNL��II�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			m_KToOilF_LLNL_II=0.84;// ���Ҹ������͵ı���
			m_KToGasF_LLNL_II=0.16; //  ���Ҹ��������ı���
			m_OSF_LLNL_II=0.;  // Oil Strat Fraction ��Ӧ��������ʼ����
			m_OToGasF_LLNL_II=0.5; //���������ı���
			m_OToResidueF_LLNL_II=0.5; //�����ɲ�����ı���

			m_N_LLNL_II_KToOil=5;//LLNL��II�͸��Ҹ����͵�ƽ�з�Ӧ�����
			m_fLLNL_II_KToOil.resize(m_N_LLNL_II_KToOil);
			m_fLLNL_II_KToOil[0]=0.05;m_fLLNL_II_KToOil[1]=0.2;m_fLLNL_II_KToOil[2]=0.5;m_fLLNL_II_KToOil[3]=0.2;m_fLLNL_II_KToOil[4]=0.05;
			m_ELLNL_II_KToOil.resize(m_N_LLNL_II_KToOil);
			m_ELLNL_II_KToOil[0]=49;m_ELLNL_II_KToOil[1]=50;m_ELLNL_II_KToOil[2]=51;m_ELLNL_II_KToOil[3]=52;m_ELLNL_II_KToOil[4]=53;
			m_FFLLNL_II_KToOil.resize(m_N_LLNL_II_KToOil); //Frequency factor
			m_FFLLNL_II_KToOil[0]=3.01e13;m_FFLLNL_II_KToOil[1]=3.01e13;m_FFLLNL_II_KToOil[2]=3.01e13;m_FFLLNL_II_KToOil[3]=3.01e13;m_FFLLNL_II_KToOil[4]=3.01e13;

			m_N_LLNL_II_KToGas=5;//LLNL��II�͸��Ҹ�������ƽ�з�Ӧ�����
			m_fLLNL_II_KToGas.resize(m_N_LLNL_II_KToGas);
			m_fLLNL_II_KToGas[0]=0.05;m_fLLNL_II_KToGas[1]=0.2;m_fLLNL_II_KToGas[2]=0.5;m_fLLNL_II_KToGas[3]=0.2;m_fLLNL_II_KToGas[4]=0.05;
			m_ELLNL_II_KToGas.resize(m_N_LLNL_II_KToGas);
			m_ELLNL_II_KToGas[0]=49;m_ELLNL_II_KToGas[1]=50;m_ELLNL_II_KToGas[2]=51;m_ELLNL_II_KToGas[3]=52;m_ELLNL_II_KToGas[4]=53;
			m_FFLLNL_II_KToGas.resize(m_N_LLNL_II_KToGas); //Frequency factor
			m_FFLLNL_II_KToGas[0]=3.01e13;m_FFLLNL_II_KToGas[1]=3.01e13;m_FFLLNL_II_KToGas[2]=3.01e13;m_FFLLNL_II_KToGas[3]=3.01e13;m_FFLLNL_II_KToGas[4]=3.01e13;

			m_N_LLNL_II_OilToGas=1;//LLNL��II�͸��Ҹ����������ķ�Ӧ�����
			m_fLLNL_II_OilToGas.resize(m_N_LLNL_II_OilToGas);
			m_fLLNL_II_OilToGas[0]=1;
			m_fLLNL_II_OilToGasBak.resize(m_N_LLNL_II_OilToGas);
			m_fLLNL_II_OilToGasBak[0]=1;
			m_ELLNL_II_OilToGas.resize(m_N_LLNL_II_OilToGas);
			m_ELLNL_II_OilToGas[0]=54;
			m_FFLLNL_II_OilToGas.resize(m_N_LLNL_II_OilToGas); //Frequency factor
			m_FFLLNL_II_OilToGas[0]=1.014e12;

			m_N_LLNL_II_OilToResidue=1;//LLNL��II�͸��Ҹ������ɲ�����ķ�Ӧ�����
			m_fLLNL_II_OilToResidue.resize(m_N_LLNL_II_OilToResidue);
			m_fLLNL_II_OilToResidue[0]=1;
			m_fLLNL_II_OilToResidueBak.resize(m_N_LLNL_II_OilToResidue);
			m_fLLNL_II_OilToResidueBak[0]=1;
			m_ELLNL_II_OilToResidue.resize(m_N_LLNL_II_OilToResidue);
			m_ELLNL_II_OilToResidue[0]=54;
			m_FFLLNL_II_OilToResidue.resize(m_N_LLNL_II_OilToResidue); //Frequency factor
			m_FFLLNL_II_OilToResidue[0]=1.014e12;

			//����ΪLLNL III�͸��Ҹ�����
			m_HI_LLNL_III=0.25; //III�͸��Ҹ�����ָ��
			m_KSF_LLNL_III=1.0;//   Kerogen Start Fraction  LLNL��III�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			m_KToOilF_LLNL_III=0.31;// ���Ҹ������͵ı���
			m_KToGasF_LLNL_III=0.69; //  ���Ҹ��������ı���
			m_OSF_LLNL_III=0.;  // Oil Strat Fraction ��Ӧ��������ʼ����
			m_OToGasF_LLNL_III=0.5; //���������ı���
			m_OToResidueF_LLNL_III=0.5; //�����ɲ�����ı���

			m_N_LLNL_III_KToOil=8;//LLNL��III�͸��Ҹ����͵�ƽ�з�Ӧ�����
			m_fLLNL_III_KToOil.resize(m_N_LLNL_III_KToOil);
			m_fLLNL_III_KToOil[0]=0.04;m_fLLNL_III_KToOil[1]=0.14;m_fLLNL_III_KToOil[2]=0.32;m_fLLNL_III_KToOil[3]=0.17;m_fLLNL_III_KToOil[4]=0.13;m_fLLNL_III_KToOil[5]=0.1;m_fLLNL_III_KToOil[6]=0.07;m_fLLNL_III_KToOil[7]=0.03;
			m_ELLNL_III_KToOil.resize(m_N_LLNL_III_KToOil);
			m_ELLNL_III_KToOil[0]=48;m_ELLNL_III_KToOil[1]=50;m_ELLNL_III_KToOil[2]=52;m_ELLNL_III_KToOil[3]=54;m_ELLNL_III_KToOil[4]=56;m_ELLNL_III_KToOil[5]=60;m_ELLNL_III_KToOil[6]=64;m_ELLNL_III_KToOil[7]=68;
			m_FFLLNL_III_KToOil.resize(m_N_LLNL_III_KToOil); //Frequency factor
			m_FFLLNL_III_KToOil[0]=1.616e13;m_FFLLNL_III_KToOil[1]=1.616e13;m_FFLLNL_III_KToOil[2]=1.616e13;m_FFLLNL_III_KToOil[3]=1.616e13;m_FFLLNL_III_KToOil[4]=1.616e13;m_FFLLNL_III_KToOil[5]=1.616e13;m_FFLLNL_III_KToOil[6]=1.616e13;m_FFLLNL_III_KToOil[7]=1.616e13;

			m_N_LLNL_III_KToGas=8;//LLNL��III�͸��Ҹ�������ƽ�з�Ӧ�����
			m_fLLNL_III_KToGas.resize(m_N_LLNL_III_KToGas);
			m_fLLNL_III_KToGas[0]=0.04;m_fLLNL_III_KToGas[1]=0.14;m_fLLNL_III_KToGas[2]=0.32;m_fLLNL_III_KToGas[3]=0.17;m_fLLNL_III_KToGas[4]=0.13;m_fLLNL_III_KToGas[5]=0.1;m_fLLNL_III_KToGas[6]=0.07;m_fLLNL_III_KToGas[7]=0.03;
			m_ELLNL_III_KToGas.resize(m_N_LLNL_III_KToGas);
			m_ELLNL_III_KToGas[0]=48;m_ELLNL_III_KToGas[1]=50;m_ELLNL_III_KToGas[2]=52;m_ELLNL_III_KToGas[3]=54;m_ELLNL_III_KToGas[4]=56;m_ELLNL_III_KToGas[5]=60;m_ELLNL_III_KToGas[6]=64;m_ELLNL_III_KToGas[7]=68;
			m_FFLLNL_III_KToGas.resize(m_N_LLNL_III_KToGas); //Frequency factor
			m_FFLLNL_III_KToGas[0]=1.616e13;m_FFLLNL_III_KToGas[1]=1.616e13;m_FFLLNL_III_KToGas[2]=1.616e13;m_FFLLNL_III_KToGas[3]=1.616e13;m_FFLLNL_III_KToGas[4]=1.616e13; m_FFLLNL_III_KToGas[5]=1.616e13;m_FFLLNL_III_KToGas[6]=1.616e13;m_FFLLNL_III_KToGas[7]=1.616e13;

			m_N_LLNL_III_OilToGas=1;//LLNL��III�͸��Ҹ����������ķ�Ӧ�����
			m_fLLNL_III_OilToGas.resize(m_N_LLNL_III_OilToGas);
			m_fLLNL_III_OilToGas[0]=1;
			m_fLLNL_III_OilToGasBak.resize(m_N_LLNL_III_OilToGas);
			m_fLLNL_III_OilToGasBak[0]=1;
			m_ELLNL_III_OilToGas.resize(m_N_LLNL_III_OilToGas);
			m_ELLNL_III_OilToGas[0]=54;
			m_FFLLNL_III_OilToGas.resize(m_N_LLNL_III_OilToGas); //Frequency factor
			m_FFLLNL_III_OilToGas[0]=1.014e12;

			m_N_LLNL_III_OilToResidue=1;//LLNL��III�͸��Ҹ������ɲ�����ķ�Ӧ�����
			m_fLLNL_III_OilToResidue.resize(m_N_LLNL_III_OilToResidue);
			m_fLLNL_III_OilToResidue[0]=1;
			m_fLLNL_III_OilToResidueBak.resize(m_N_LLNL_III_OilToResidue);
			m_fLLNL_III_OilToResidueBak[0]=1;
			m_ELLNL_III_OilToResidue.resize(m_N_LLNL_III_OilToResidue);
			m_ELLNL_III_OilToResidue[0]=54;
			m_FFLLNL_III_OilToResidue.resize(m_N_LLNL_III_OilToResidue); //Frequency factor
			m_FFLLNL_III_OilToResidue[0]=1.014e12;
		}
		LLNLKinetics(const LLNLKinetics &other)
		{
			*this = other;
		}
		const LLNLKinetics &operator=(const LLNLKinetics &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_W = other.m_W;
			m_NKerogenType = other.m_NKerogenType;   //���Ҹ�������
			m_RatioKerogenType = other.m_RatioKerogenType; // ���Ҹ�����
			m_InitTOC = other.m_InitTOC; //ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
			m_MassOfInitTOC = other.m_MassOfInitTOC; //ÿ�ָ��Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
			m_MassOfInitTOCTotal = other.m_MassOfInitTOCTotal; //���Ҹ�ԭʼ�л�̼�ܵ�����
			m_MKer = other.m_MKer;
			m_MKerTotal = other.m_MKerTotal;
			m_HI_LLNL_I = other.m_HI_LLNL_I; //I�͸��Ҹ�����ָ��
			m_KSF_LLNL_I = other.m_KSF_LLNL_I;//   Kerogen Start Fraction  LLNL��I�͸��Ҹ� ��Ӧ����Ҹ���ʼ�� 
			m_KToOilF_LLNL_I = other.m_KToOilF_LLNL_I;// ���Ҹ������͵ı���
			m_KToGasF_LLNL_I = other.m_KToGasF_LLNL_I; //  ���Ҹ��������ı���
			m_OSF_LLNL_I = other.m_OSF_LLNL_I;  // Oil Strat Fraction ��Ӧ��������ʼ����
			m_OToGasF_LLNL_I = other.m_OToGasF_LLNL_I; //���������ı���
			m_OToResidueF_LLNL_I = other.m_OToResidueF_LLNL_I; //�����ɲ�����ı���

			m_N_LLNL_I_KToOil = other.m_N_LLNL_I_KToOil;//LLNL��I�͸��Ҹ����͵�ƽ�з�Ӧ�����
			m_fLLNL_I_KToOil = other.m_fLLNL_I_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_I_KToOil = other.m_ELLNL_I_KToOil;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_I_KToOil = other.m_FFLLNL_I_KToOil; //Frequency factor

			m_N_LLNL_I_KToGas = other.m_N_LLNL_I_KToGas;//LLNL��I�͸��Ҹ�������ƽ�з�Ӧ�����
			m_fLLNL_I_KToGas = other.m_fLLNL_I_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_I_KToGas = other.m_ELLNL_I_KToGas;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_I_KToGas = other.m_FFLLNL_I_KToGas; //Frequency factor,Ƶ������

			m_N_LLNL_I_OilToGas = other.m_N_LLNL_I_OilToGas;//LLNL��I�͸��Ҹ����������ķ�Ӧ�����
			m_fLLNL_I_OilToGas = other.m_fLLNL_I_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_fLLNL_I_OilToGasBak = other.m_fLLNL_I_OilToGasBak;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_I_OilToGas = other.m_ELLNL_I_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_I_OilToGas = other.m_FFLLNL_I_OilToGas; //Frequency factor

			m_N_LLNL_I_OilToResidue = other.m_N_LLNL_I_OilToResidue;//LLNL��I�͸��Ҹ������ɲ�����ķ�Ӧ�����
			m_fLLNL_I_OilToResidue = other.m_fLLNL_I_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_fLLNL_I_OilToResidueBak = other.m_fLLNL_I_OilToResidueBak;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_I_OilToResidue = other.m_ELLNL_I_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_I_OilToResidue = other.m_FFLLNL_I_OilToResidue; //Frequency factor
			//����ΪLLNL II�͸��Ҹ�����
			m_HI_LLNL_II = other.m_HI_LLNL_II; //II�͸��Ҹ�����ָ��
			m_KSF_LLNL_II = other.m_KSF_LLNL_II;//   Kerogen Start Fraction  LLNL��II�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			m_KToOilF_LLNL_II = other.m_KToOilF_LLNL_II;// ���Ҹ������͵ı���
			m_KToGasF_LLNL_II = other.m_KToGasF_LLNL_II; //  ���Ҹ��������ı���
			m_OSF_LLNL_II = other.m_OSF_LLNL_II;  // Oil Strat Fraction ��Ӧ��������ʼ����
			m_OToGasF_LLNL_II = other.m_OToGasF_LLNL_II; //���������ı���
			m_OToResidueF_LLNL_II = other.m_OToResidueF_LLNL_II; //�����ɲ�����ı���

			m_N_LLNL_II_KToOil = other.m_N_LLNL_II_KToOil;//LLNL��II�͸��Ҹ����͵�ƽ�з�Ӧ�����
			m_fLLNL_II_KToOil = other.m_fLLNL_II_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_II_KToOil = other.m_ELLNL_II_KToOil;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_II_KToOil = other.m_FFLLNL_II_KToOil; //Frequency factor

			m_N_LLNL_II_KToGas = other.m_N_LLNL_II_KToGas;//LLNL��II�͸��Ҹ�������ƽ�з�Ӧ�����
			m_fLLNL_II_KToGas = other.m_fLLNL_II_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_II_KToGas = other.m_ELLNL_II_KToGas;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_II_KToGas = other.m_FFLLNL_II_KToGas; //Frequency factor

			m_N_LLNL_II_OilToGas = other.m_N_LLNL_II_OilToGas;//LLNL��II�͸��Ҹ����������ķ�Ӧ�����
			m_fLLNL_II_OilToGas = other.m_fLLNL_II_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_fLLNL_II_OilToGasBak = other.m_fLLNL_II_OilToGasBak;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_II_OilToGas = other.m_ELLNL_II_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_II_OilToGas = other.m_FFLLNL_II_OilToGas; //Frequency factor

			m_N_LLNL_II_OilToResidue = other.m_N_LLNL_II_OilToResidue;//LLNL��II�͸��Ҹ������ɲ�����ķ�Ӧ�����
			m_fLLNL_II_OilToResidue = other.m_fLLNL_II_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_fLLNL_II_OilToResidueBak = other.m_fLLNL_II_OilToResidueBak;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_II_OilToResidue = other.m_ELLNL_II_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_II_OilToResidue = other.m_FFLLNL_II_OilToResidue; //Frequency factor

			//����ΪLLNL III�͸��Ҹ�����
			m_HI_LLNL_III = other.m_HI_LLNL_III; //III�͸��Ҹ�����ָ��
			m_KSF_LLNL_III = other.m_KSF_LLNL_III;//   Kerogen Start Fraction  LLNL��III�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			m_KToOilF_LLNL_III = other.m_KToOilF_LLNL_III;// ���Ҹ������͵ı���
			m_KToGasF_LLNL_III = other.m_KToGasF_LLNL_III; //  ���Ҹ��������ı���
			m_OSF_LLNL_III = other.m_OSF_LLNL_III;  // Oil Strat Fraction ��Ӧ��������ʼ����
			m_OToGasF_LLNL_III = other.m_OToGasF_LLNL_III; //���������ı���
			m_OToResidueF_LLNL_III = other.m_OToResidueF_LLNL_III; //�����ɲ�����ı���

			m_N_LLNL_III_KToOil = other.m_N_LLNL_III_KToOil;//LLNL��III�͸��Ҹ����͵�ƽ�з�Ӧ�����
			m_fLLNL_III_KToOil = other.m_fLLNL_III_KToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_III_KToOil = other.m_ELLNL_III_KToOil;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_III_KToOil = other.m_FFLLNL_III_KToOil; //Frequency factor

			m_N_LLNL_III_KToGas = other.m_N_LLNL_III_KToGas;//LLNL��III�͸��Ҹ�������ƽ�з�Ӧ�����
			m_fLLNL_III_KToGas = other.m_fLLNL_III_KToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_III_KToGas = other.m_ELLNL_III_KToGas;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_III_KToGas = other.m_FFLLNL_III_KToGas; //Frequency factor

			m_N_LLNL_III_OilToGas = other.m_N_LLNL_III_OilToGas;//LLNL��III�͸��Ҹ����������ķ�Ӧ�����
			m_fLLNL_III_OilToGas = other.m_fLLNL_III_OilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_fLLNL_III_OilToGasBak = other.m_fLLNL_III_OilToGasBak;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_III_OilToGas = other.m_ELLNL_III_OilToGas;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_III_OilToGas = other.m_FFLLNL_III_OilToGas; //Frequency factor

			m_N_LLNL_III_OilToResidue = other.m_N_LLNL_III_OilToResidue;//LLNL��III�͸��Ҹ������ɲ�����ķ�Ӧ�����
			m_fLLNL_III_OilToResidue = other.m_fLLNL_III_OilToResidue;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_fLLNL_III_OilToResidueBak = other.m_fLLNL_III_OilToResidueBak;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
			m_ELLNL_III_OilToResidue = other.m_ELLNL_III_OilToResidue;//��ܣ�Activation Energy����Kcal/mole��
			m_FFLLNL_III_OilToResidue = other.m_FFLLNL_III_OilToResidue; //Frequency factor

			m_wBIw0_I_KToOil = other.m_wBIw0_I_KToOil;
			m_wBIw0_II_KToOil = other.m_wBIw0_II_KToOil;
			m_wBIw0_III_KToOil = other.m_wBIw0_III_KToOil;
			m_wBIw0_I_KToGas = other.m_wBIw0_I_KToGas;
			m_wBIw0_II_KToGas = other.m_wBIw0_II_KToGas;
			m_wBIw0_III_KToGas = other.m_wBIw0_III_KToGas;
			m_wBIw0_I_OilToGas = other.m_wBIw0_I_OilToGas;
			m_wBIw0_II_OilToGas = other.m_wBIw0_II_OilToGas;
			m_wBIw0_III_OilToGas = other.m_wBIw0_III_OilToGas;
			m_wBIw0_I_OilToResidue = other.m_wBIw0_I_OilToResidue;
			m_wBIw0_II_OilToResidue = other.m_wBIw0_II_OilToResidue;
			m_wBIw0_III_OilToResidue = other.m_wBIw0_III_OilToResidue;
			m_OilPerInitTOC_I = other.m_OilPerInitTOC_I;
			m_OilPerInitTOC_II = other.m_OilPerInitTOC_II;
			m_OilPerInitTOC_III = other.m_OilPerInitTOC_III;
			m_GasPerInitTOC_I = other.m_GasPerInitTOC_I;
			m_GasPerInitTOC_II = other.m_GasPerInitTOC_II;
			m_GasPerInitTOC_III = other.m_GasPerInitTOC_III; 
			m_TOCRemained_I = other.m_TOCRemained_I;
			m_TOCRemained_II = other.m_TOCRemained_II;
			m_TOCRemained_III = other.m_TOCRemained_III;
			m_OilCracked_I = other.m_OilCracked_I;
			m_OilCracked_II = other.m_OilCracked_II;
			m_OilCracked_III = other.m_OilCracked_III;
			m_GasCracked_I = other.m_GasCracked_I;
			m_GasCracked_II = other.m_GasCracked_II;
			m_GasCracked_III = other.m_GasCracked_III;
			m_ResidueCracked_I = other.m_ResidueCracked_I;
			m_ResidueCracked_II = other.m_ResidueCracked_II;
			m_ResidueCracked_III = other.m_ResidueCracked_III;
			m_OilExisted_I = other.m_OilExisted_I;
			m_OilExisted_II = other.m_OilExisted_II;
			m_OilExisted_III = other.m_OilExisted_III;
			m_GasExisted_I = other.m_GasExisted_I;
			m_GasExisted_II = other.m_GasExisted_II;
			m_GasExisted_III = other.m_GasExisted_III;
			m_ResidueExisted_I = other.m_ResidueExisted_I;
			m_ResidueExisted_II = other.m_ResidueExisted_II;
			m_ResidueExisted_III = other.m_ResidueExisted_III;
			m_OilGenerated_I = other.m_OilGenerated_I;
			m_OilGenerated_II = other.m_OilGenerated_II;
			m_OilGenerated_III = other.m_OilGenerated_III;
			m_GasGenerated_I = other.m_GasGenerated_I;
			m_GasGenerated_II = other.m_GasGenerated_II;
			m_GasGenerated_III = other.m_GasGenerated_III;
			m_OilGenerated = other.m_OilGenerated;
			m_GasGenerated = other.m_GasGenerated;
			m_OilPerInitTOC = other.m_OilPerInitTOC;
			m_GasPerInitTOC = other.m_GasPerInitTOC;
			m_TOCReactableKerogen = other.m_TOCReactableKerogen;
			m_TOCInertKerogen = other.m_TOCInertKerogen;
			m_TOCOilKerogen = other.m_TOCOilKerogen;
			m_TOCGasKerogen = other.m_TOCGasKerogen;
			m_TOCKerogen = other.m_TOCKerogen;
			m_TOCRemained = other.m_TOCRemained;
			m_TR = other.m_TR;
			m_OilExisted = other.m_OilExisted;
			m_GasExisted = other.m_GasExisted;
			m_GasCracked = other.m_GasCracked;
			m_GasCrackedAdded = other.m_GasCrackedAdded; 
			m_ResidueCracked = other.m_ResidueCracked;
			m_ResidueCrackedAdded = other.m_ResidueCrackedAdded;
			m_OilCracked = other.m_OilCracked;
			m_OilCrackedAdded = other.m_OilCrackedAdded;
			m_MKerReac = other.m_MKerReac; 
			m_MKerInert = other.m_MKerInert;
			m_MKerOil = other.m_MKerOil;
			m_MKerGas = other.m_MKerGas;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_W;
			curSize += sizeof(int);//int m_NKerogenType;
			curSize += (sizeof(int) + m_RatioKerogenType.size() * sizeof(double));//std::vector<double> m_RatioKerogenType;
			curSize += (sizeof(int) + m_InitTOC.size() * sizeof(double));//std::vector<double> m_InitTOC; 
			curSize += (sizeof(int) + m_MassOfInitTOC.size() * sizeof(double));//std::vector<double> m_MassOfInitTOC; 
			curSize += sizeof(double);//double m_MassOfInitTOCTotal;
			curSize += (sizeof(int) + m_MKer.size() * sizeof(double));//std::vector<double> m_MKer; 
			curSize += sizeof(double);//double m_MKerTotal;
			curSize += sizeof(double);//double m_HI_LLNL_I;
			curSize += sizeof(double);//double m_KSF_LLNL_I;
			curSize += sizeof(double);//double m_KToOilF_LLNL_I;
			curSize += sizeof(double);//double m_KToGasF_LLNL_I;
			curSize += sizeof(double);//double m_OSF_LLNL_I;
			curSize += sizeof(double);//double m_OToGasF_LLNL_I;
			curSize += sizeof(double);//double m_OToResidueF_LLNL_I;
			curSize += sizeof(int);//int m_N_LLNL_I_KToOil;
			curSize += (sizeof(int) + m_fLLNL_I_KToOil.size() * sizeof(double));//std::vector<double> m_fLLNL_I_KToOil;
			curSize += (sizeof(int) + m_ELLNL_I_KToOil.size() * sizeof(double));//std::vector<double> m_ELLNL_I_KToOil;
			curSize += (sizeof(int) + m_FFLLNL_I_KToOil.size() * sizeof(double));//std::vector<double> m_FFLLNL_I_KToOil;
			curSize += sizeof(int);//int m_N_LLNL_I_KToGas;
			curSize += (sizeof(int) + m_fLLNL_I_KToGas.size() * sizeof(double));//std::vector<double> m_fLLNL_I_KToGas;
			curSize += (sizeof(int) + m_ELLNL_I_KToGas.size() * sizeof(double));//std::vector<double> m_ELLNL_I_KToGas;
			curSize += (sizeof(int) + m_FFLLNL_I_KToGas.size() * sizeof(double));//std::vector<double> m_FFLLNL_I_KToGas;
			curSize += sizeof(int);//int m_N_LLNL_I_OilToGas;
			curSize += (sizeof(int) + m_fLLNL_I_OilToGas.size() * sizeof(double));//std::vector<double> m_fLLNL_I_OilToGas;
			curSize += (sizeof(int) + m_fLLNL_I_OilToGasBak.size() * sizeof(double));//std::vector<double> m_fLLNL_I_OilToGasBak;
			curSize += (sizeof(int) + m_ELLNL_I_OilToGas.size() * sizeof(double));//std::vector<double> m_ELLNL_I_OilToGas;
			curSize += (sizeof(int) + m_FFLLNL_I_OilToGas.size() * sizeof(double));//std::vector<double> m_FFLLNL_I_OilToGas;
			curSize += sizeof(int);//int m_N_LLNL_I_OilToResidue;
			curSize += (sizeof(int) + m_fLLNL_I_OilToResidue.size() * sizeof(double));//std::vector<double> m_fLLNL_I_OilToResidue;
			curSize += (sizeof(int) + m_fLLNL_I_OilToResidueBak.size() * sizeof(double));//std::vector<double> m_fLLNL_I_OilToResidueBak;
			curSize += (sizeof(int) + m_ELLNL_I_OilToResidue.size() * sizeof(double));//std::vector<double> m_ELLNL_I_OilToResidue;
			curSize += (sizeof(int) + m_FFLLNL_I_OilToResidue.size() * sizeof(double));//std::vector<double> m_FFLLNL_I_OilToResidue;
			curSize += sizeof(double);//double m_HI_LLNL_II;
			curSize += sizeof(double);//double m_KSF_LLNL_II;
			curSize += sizeof(double);//double m_KToOilF_LLNL_II;
			curSize += sizeof(double);//double m_KToGasF_LLNL_II;
			curSize += sizeof(double);//double m_OSF_LLNL_II;
			curSize += sizeof(double);//double m_OToGasF_LLNL_II;
			curSize += sizeof(double);//double m_OToResidueF_LLNL_II;
			curSize += sizeof(int);//int m_N_LLNL_II_KToOil;
			curSize += (sizeof(int) + m_fLLNL_II_KToOil.size() * sizeof(double));//std::vector<double> m_fLLNL_II_KToOil;
			curSize += (sizeof(int) + m_ELLNL_II_KToOil.size() * sizeof(double));//std::vector<double> m_ELLNL_II_KToOil;
			curSize += (sizeof(int) + m_FFLLNL_II_KToOil.size() * sizeof(double));//std::vector<double> m_FFLLNL_II_KToOil;
			curSize += sizeof(int);//int m_N_LLNL_II_KToGas;
			curSize += (sizeof(int) + m_fLLNL_II_KToGas.size() * sizeof(double));//std::vector<double> m_fLLNL_II_KToGas;
			curSize += (sizeof(int) + m_ELLNL_II_KToGas.size() * sizeof(double));//std::vector<double> m_ELLNL_II_KToGas;
			curSize += (sizeof(int) + m_FFLLNL_II_KToGas.size() * sizeof(double));//std::vector<double> m_FFLLNL_II_KToGas;
			curSize += sizeof(int);//int m_N_LLNL_II_OilToGas;
			curSize += (sizeof(int) + m_fLLNL_II_OilToGas.size() * sizeof(double));//std::vector<double> m_fLLNL_II_OilToGas;
			curSize += (sizeof(int) + m_fLLNL_II_OilToGasBak.size() * sizeof(double));//std::vector<double> m_fLLNL_II_OilToGasBak;
			curSize += (sizeof(int) + m_ELLNL_II_OilToGas.size() * sizeof(double));//std::vector<double> m_ELLNL_II_OilToGas;
			curSize += (sizeof(int) + m_FFLLNL_II_OilToGas.size() * sizeof(double));//std::vector<double> m_FFLLNL_II_OilToGas;
			curSize += sizeof(int);//int m_N_LLNL_II_OilToResidue;
			curSize += (sizeof(int) + m_fLLNL_II_OilToResidue.size() * sizeof(double));//std::vector<double> m_fLLNL_II_OilToResidue;
			curSize += (sizeof(int) + m_fLLNL_II_OilToResidueBak.size() * sizeof(double));//std::vector<double> m_fLLNL_II_OilToResidueBak;
			curSize += (sizeof(int) + m_ELLNL_II_OilToResidue.size() * sizeof(double));//std::vector<double> m_ELLNL_II_OilToResidue;
			curSize += (sizeof(int) + m_FFLLNL_II_OilToResidue.size() * sizeof(double));//std::vector<double> m_FFLLNL_II_OilToResidue;
			curSize += sizeof(double);//double m_HI_LLNL_III;
			curSize += sizeof(double);//double m_KSF_LLNL_III;
			curSize += sizeof(double);//double m_KToOilF_LLNL_III;
			curSize += sizeof(double);//double m_KToGasF_LLNL_III;
			curSize += sizeof(double);//double m_OSF_LLNL_III;
			curSize += sizeof(double);//double m_OToGasF_LLNL_III;
			curSize += sizeof(double);//double m_OToResidueF_LLNL_III;
			curSize += sizeof(int);//int m_N_LLNL_III_KToOil;
			curSize += (sizeof(int) + m_fLLNL_III_KToOil.size() * sizeof(double));//std::vector<double> m_fLLNL_III_KToOil;
			curSize += (sizeof(int) + m_ELLNL_III_KToOil.size() * sizeof(double));//std::vector<double> m_ELLNL_III_KToOil;
			curSize += (sizeof(int) + m_FFLLNL_III_KToOil.size() * sizeof(double));//std::vector<double> m_FFLLNL_III_KToOil;
			curSize += sizeof(int);//int m_N_LLNL_III_KToGas;
			curSize += (sizeof(int) + m_fLLNL_III_KToGas.size() * sizeof(double));//std::vector<double> m_fLLNL_III_KToGas;
			curSize += (sizeof(int) + m_ELLNL_III_KToGas.size() * sizeof(double));//std::vector<double> m_ELLNL_III_KToGas;
			curSize += (sizeof(int) + m_FFLLNL_III_KToGas.size() * sizeof(double));//std::vector<double> m_FFLLNL_III_KToGas;
			curSize += sizeof(int);//int m_N_LLNL_III_OilToGas;
			curSize += (sizeof(int) + m_fLLNL_III_OilToGas.size() * sizeof(double));//std::vector<double> m_fLLNL_III_OilToGas;
			curSize += (sizeof(int) + m_fLLNL_III_OilToGasBak.size() * sizeof(double));//std::vector<double> m_fLLNL_III_OilToGasBak;
			curSize += (sizeof(int) + m_ELLNL_III_OilToGas.size() * sizeof(double));//std::vector<double> m_ELLNL_III_OilToGas;
			curSize += (sizeof(int) + m_FFLLNL_III_OilToGas.size() * sizeof(double));//std::vector<double> m_FFLLNL_III_OilToGas;
			curSize += sizeof(int);//int m_N_LLNL_III_OilToResidue;
			curSize += (sizeof(int) + m_fLLNL_III_OilToResidue.size() * sizeof(double));//std::vector<double> m_fLLNL_III_OilToResidue;
			curSize += (sizeof(int) + m_fLLNL_III_OilToResidueBak.size() * sizeof(double));//std::vector<double> m_fLLNL_III_OilToResidueBak;
			curSize += (sizeof(int) + m_ELLNL_III_OilToResidue.size() * sizeof(double));//std::vector<double> m_ELLNL_III_OilToResidue;
			curSize += (sizeof(int) + m_FFLLNL_III_OilToResidue.size() * sizeof(double));//std::vector<double> m_FFLLNL_III_OilToResidue;
			curSize += sizeof(double);//double m_wBIw0_I_KToOil;
			curSize += sizeof(double);//double m_wBIw0_II_KToOil;
			curSize += sizeof(double);//double m_wBIw0_III_KToOil;
			curSize += sizeof(double);//double m_wBIw0_I_KToGas;
			curSize += sizeof(double);//double m_wBIw0_II_KToGas;
			curSize += sizeof(double);//double m_wBIw0_III_KToGas;
			curSize += sizeof(double);//double m_wBIw0_I_OilToGas;
			curSize += sizeof(double);//double m_wBIw0_II_OilToGas;
			curSize += sizeof(double);//double m_wBIw0_III_OilToGas;
			curSize += sizeof(double);//double m_wBIw0_I_OilToResidue;
			curSize += sizeof(double);//double m_wBIw0_II_OilToResidue;
			curSize += sizeof(double);//double m_wBIw0_III_OilToResidue;
			curSize += sizeof(double);//double m_OilPerInitTOC_I;
			curSize += sizeof(double);//double m_OilPerInitTOC_II;
			curSize += sizeof(double);//double m_OilPerInitTOC_III;
			curSize += sizeof(double);//double m_GasPerInitTOC_I;
			curSize += sizeof(double);//double m_GasPerInitTOC_II;
			curSize += sizeof(double);//double m_GasPerInitTOC_III; 
			curSize += sizeof(double);//double m_TOCRemained_I;
			curSize += sizeof(double);//double m_TOCRemained_II;
			curSize += sizeof(double);//double m_TOCRemained_III;
			curSize += sizeof(double);//double m_OilCracked_I;
			curSize += sizeof(double);//double m_OilCracked_II;
			curSize += sizeof(double);//double m_OilCracked_III;
			curSize += sizeof(double);//double m_GasCracked_I;
			curSize += sizeof(double);//double m_GasCracked_II;
			curSize += sizeof(double);//double m_GasCracked_III;
			curSize += sizeof(double);//double m_ResidueCracked_I;
			curSize += sizeof(double);//double m_ResidueCracked_II;
			curSize += sizeof(double);//double m_ResidueCracked_III;
			curSize += sizeof(double);//double m_OilExisted_I;
			curSize += sizeof(double);//double m_OilExisted_II;
			curSize += sizeof(double);//double m_OilExisted_III;
			curSize += sizeof(double);//double m_GasExisted_I;
			curSize += sizeof(double);//double m_GasExisted_II;
			curSize += sizeof(double);//double m_GasExisted_III;
			curSize += sizeof(double);//double m_ResidueExisted_I;
			curSize += sizeof(double);//double m_ResidueExisted_II;
			curSize += sizeof(double);//double m_ResidueExisted_III;
			curSize += sizeof(double);//double m_OilGenerated_I;
			curSize += sizeof(double);//double m_OilGenerated_II;
			curSize += sizeof(double);//double m_OilGenerated_III;
			curSize += sizeof(double);//double m_GasGenerated_I;
			curSize += sizeof(double);//double m_GasGenerated_II;
			curSize += sizeof(double);//double m_GasGenerated_III;
			curSize += sizeof(double);//double m_OilGenerated;
			curSize += sizeof(double);//double m_GasGenerated;
			curSize += sizeof(double);//double m_OilPerInitTOC;
			curSize += sizeof(double);//double m_GasPerInitTOC;
			curSize += sizeof(double);//double m_TOCReactableKerogen;
			curSize += sizeof(double);//double m_TOCInertKerogen;
			curSize += sizeof(double);//double m_TOCOilKerogen;
			curSize += sizeof(double);//double m_TOCGasKerogen;
			curSize += sizeof(double);//double m_TOCKerogen;
			curSize += sizeof(double);//double m_TOCRemained;
			curSize += sizeof(double);//double m_TR;
			curSize += sizeof(double);//double m_OilExisted;
			curSize += sizeof(double);//double m_GasExisted;
			curSize += sizeof(double);//double m_GasCracked;
			curSize += sizeof(double);//double m_GasCrackedAdded; 
			curSize += sizeof(double);//double m_ResidueCracked;
			curSize += sizeof(double);//double m_ResidueCrackedAdded;
			curSize += sizeof(double);//double m_OilCracked;
			curSize += sizeof(double);//double m_OilCrackedAdded;
			curSize += sizeof(double);//double m_MKerReac; 
			curSize += sizeof(double);//double m_MKerInert;
			curSize += sizeof(double);//double m_MKerOil;
			curSize += sizeof(double);//double m_MKerGas;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_W), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NKerogenType), sizeof(int));data += sizeof(int);
			int RatioKerogenTypesize = m_RatioKerogenType.size();
			memcpy(data, &RatioKerogenTypesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < RatioKerogenTypesize; j++)
			{
				memcpy(data, &(m_RatioKerogenType[j]), sizeof(double));data += sizeof(double);
			}
			int InitTOCsize = m_InitTOC.size();
			memcpy(data, &InitTOCsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < InitTOCsize; j++)
			{
				memcpy(data, &(m_InitTOC[j]), sizeof(double));data += sizeof(double);
			}
			int MassOfInitTOCsize = m_MassOfInitTOC.size();
			memcpy(data, &MassOfInitTOCsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < MassOfInitTOCsize; j++)
			{
				memcpy(data, &(m_MassOfInitTOC[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_MassOfInitTOCTotal), sizeof(double));data += sizeof(double);
			int MKersize = m_MKer.size();
			memcpy(data, &MKersize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < MKersize; j++)
			{
				memcpy(data, &(m_MKer[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_MKerTotal), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI_LLNL_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KSF_LLNL_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KToOilF_LLNL_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KToGasF_LLNL_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OSF_LLNL_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OToGasF_LLNL_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OToResidueF_LLNL_I), sizeof(double));data += sizeof(double);
			//����ΪI�͸��Ҹ��Ķ���ѧ����
			memcpy(data, &(m_N_LLNL_I_KToOil), sizeof(int));data += sizeof(int);
			int fLLNL_I_KToOilsize = m_fLLNL_I_KToOil.size();
			memcpy(data, &fLLNL_I_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_I_KToOilsize; j++)
			{
				memcpy(data, &(m_fLLNL_I_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_KToOilsize = m_ELLNL_I_KToOil.size();
			memcpy(data, &ELLNL_I_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_I_KToOilsize; j++)
			{
				memcpy(data, &(m_ELLNL_I_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_KToOilsize = m_FFLLNL_I_KToOil.size();
			memcpy(data, &FFLLNL_I_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_I_KToOilsize; j++)
			{
				memcpy(data, &(m_FFLLNL_I_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			//
			memcpy(data, &(m_N_LLNL_I_KToGas), sizeof(int));data += sizeof(int);
			int fLLNL_I_KToGassize = m_fLLNL_I_KToGas.size();
			memcpy(data, &fLLNL_I_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_I_KToGassize; j++)
			{
				memcpy(data, &(m_fLLNL_I_KToGas[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_KToGassize = m_ELLNL_I_KToGas.size();
			memcpy(data, &ELLNL_I_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_I_KToGassize; j++)
			{
				memcpy(data, &(m_ELLNL_I_KToGas[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_KToGassize = m_FFLLNL_I_KToGas.size();
			memcpy(data, &FFLLNL_I_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_I_KToGassize; j++)
			{
				memcpy(data, &(m_FFLLNL_I_KToGas[j]), sizeof(double));data += sizeof(double);
			}
			//
			memcpy(data, &(m_N_LLNL_I_OilToGas), sizeof(int));data += sizeof(int);
			int fLLNL_I_OilToGassize = m_fLLNL_I_OilToGas.size();
			memcpy(data, &fLLNL_I_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_I_OilToGassize; j++)
			{
				memcpy(data, &(m_fLLNL_I_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int fLLNL_I_OilToGasBaksize = m_fLLNL_I_OilToGasBak.size();
			memcpy(data, &fLLNL_I_OilToGasBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_I_OilToGasBaksize; j++)
			{
				memcpy(data, &(m_fLLNL_I_OilToGasBak[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_OilToGassize = m_ELLNL_I_OilToGas.size();
			memcpy(data, &ELLNL_I_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_I_OilToGassize; j++)
			{
				memcpy(data, &(m_ELLNL_I_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_OilToGassize = m_FFLLNL_I_OilToGas.size();
			memcpy(data, &FFLLNL_I_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_I_OilToGassize; j++)
			{
				memcpy(data, &(m_FFLLNL_I_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			//
			memcpy(data, &(m_N_LLNL_I_OilToResidue), sizeof(int));data += sizeof(int);
			int fLLNL_I_OilToResiduesize = m_fLLNL_I_OilToResidue.size();
			memcpy(data, &fLLNL_I_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_I_OilToResiduesize; j++)
			{
				memcpy(data, &(m_fLLNL_I_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			int fLLNL_I_OilToResidueBaksize = m_fLLNL_I_OilToResidueBak.size();
			memcpy(data, &fLLNL_I_OilToResidueBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_I_OilToResidueBaksize; j++)
			{
				memcpy(data, &(m_fLLNL_I_OilToResidueBak[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_OilToResiduesize = m_ELLNL_I_OilToResidue.size();
			memcpy(data, &ELLNL_I_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_I_OilToResiduesize; j++)
			{
				memcpy(data, &(m_ELLNL_I_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_OilToResiduesize = m_FFLLNL_I_OilToResidue.size();
			memcpy(data, &FFLLNL_I_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_I_OilToResiduesize; j++)
			{
				memcpy(data, &(m_FFLLNL_I_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			//����ΪLLNL II�͸��Ҹ�����
			memcpy(data, &(m_HI_LLNL_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KSF_LLNL_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KToOilF_LLNL_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KToGasF_LLNL_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OSF_LLNL_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OToGasF_LLNL_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OToResidueF_LLNL_II), sizeof(double));data += sizeof(double);
			//
			memcpy(data, &(m_N_LLNL_II_KToOil), sizeof(int));data += sizeof(int);
			int fLLNL_II_KToOilsize = m_fLLNL_II_KToOil.size();
			memcpy(data, &fLLNL_II_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_II_KToOilsize; j++)
			{
				memcpy(data, &(m_fLLNL_II_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_KToOilsize = m_ELLNL_II_KToOil.size();
			memcpy(data, &ELLNL_II_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_II_KToOilsize; j++)
			{
				memcpy(data, &(m_ELLNL_II_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_KToOilsize = m_FFLLNL_II_KToOil.size();
			memcpy(data, &FFLLNL_II_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_II_KToOilsize; j++)
			{
				memcpy(data, &(m_FFLLNL_II_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			//
			memcpy(data, &(m_N_LLNL_II_KToGas), sizeof(int));data += sizeof(int);
			int fLLNL_II_KToGassize = m_fLLNL_II_KToGas.size();
			memcpy(data, &fLLNL_II_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_II_KToGassize; j++)
			{
				memcpy(data, &(m_fLLNL_II_KToGas[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_KToGassize = m_ELLNL_II_KToGas.size();
			memcpy(data, &ELLNL_II_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_II_KToGassize; j++)
			{
				memcpy(data, &(m_ELLNL_II_KToGas[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_KToGassize = m_FFLLNL_II_KToGas.size();
			memcpy(data, &FFLLNL_II_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_II_KToGassize; j++)
			{
				memcpy(data, &(m_FFLLNL_II_KToGas[j]), sizeof(double));data += sizeof(double);
			} 
			//
			memcpy(data, &(m_N_LLNL_II_OilToGas), sizeof(int));data += sizeof(int);
			int fLLNL_II_OilToGassize = m_fLLNL_II_OilToGas.size();
			memcpy(data, &fLLNL_II_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_II_OilToGassize; j++)
			{
				memcpy(data, &(m_fLLNL_II_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int fLLNL_II_OilToGasBaksize = m_fLLNL_II_OilToGasBak.size();
			memcpy(data, &fLLNL_II_OilToGasBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_II_OilToGasBaksize; j++)
			{
				memcpy(data, &(m_fLLNL_II_OilToGasBak[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_OilToGassize = m_ELLNL_II_OilToGas.size();
			memcpy(data, &ELLNL_II_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_II_OilToGassize; j++)
			{
				memcpy(data, &(m_ELLNL_II_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_OilToGassize = m_FFLLNL_II_OilToGas.size();
			memcpy(data, &FFLLNL_II_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_II_OilToGassize; j++)
			{
				memcpy(data, &(m_FFLLNL_II_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			//
			memcpy(data, &(m_N_LLNL_II_OilToResidue), sizeof(int));data += sizeof(int);
			int fLLNL_II_OilToResiduesize = m_fLLNL_II_OilToResidue.size();
			memcpy(data, &fLLNL_II_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_II_OilToResiduesize; j++)
			{
				memcpy(data, &(m_fLLNL_II_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			int fLLNL_II_OilToResidueBaksize = m_fLLNL_II_OilToResidueBak.size();
			memcpy(data, &fLLNL_II_OilToResidueBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_II_OilToResidueBaksize; j++)
			{
				memcpy(data, &(m_fLLNL_II_OilToResidueBak[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_OilToResiduesize = m_ELLNL_II_OilToResidue.size();
			memcpy(data, &ELLNL_II_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_II_OilToResiduesize; j++)
			{
				memcpy(data, &(m_ELLNL_II_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_OilToResiduesize = m_FFLLNL_II_OilToResidue.size();
			memcpy(data, &FFLLNL_II_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_II_OilToResiduesize; j++)
			{
				memcpy(data, &(m_FFLLNL_II_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			//����ΪLLNL III�͸��Ҹ�����
			memcpy(data, &(m_HI_LLNL_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KSF_LLNL_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KToOilF_LLNL_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_KToGasF_LLNL_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OSF_LLNL_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OToGasF_LLNL_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OToResidueF_LLNL_III), sizeof(double));data += sizeof(double);
			//
			memcpy(data, &(m_N_LLNL_III_KToOil), sizeof(int));data += sizeof(int);
			int fLLNL_III_KToOilsize = m_fLLNL_III_KToOil.size();
			memcpy(data, &fLLNL_III_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_III_KToOilsize; j++)
			{
				memcpy(data, &(m_fLLNL_III_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_KToOilsize = m_ELLNL_III_KToOil.size();
			memcpy(data, &ELLNL_III_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_III_KToOilsize; j++)
			{
				memcpy(data, &(m_ELLNL_III_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_KToOilsize = m_FFLLNL_III_KToOil.size();
			memcpy(data, &FFLLNL_III_KToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_III_KToOilsize; j++)
			{
				memcpy(data, &(m_FFLLNL_III_KToOil[j]), sizeof(double));data += sizeof(double);
			}
			//
			memcpy(data, &(m_N_LLNL_III_KToGas), sizeof(int));data += sizeof(int);
			int fLLNL_III_KToGassize = m_fLLNL_III_KToGas.size();
			memcpy(data, &fLLNL_III_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_III_KToGassize; j++)
			{
				memcpy(data, &(m_fLLNL_III_KToGas[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_KToGassize = m_ELLNL_III_KToGas.size();
			memcpy(data, &ELLNL_III_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_III_KToGassize; j++)
			{
				memcpy(data, &(m_ELLNL_III_KToGas[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_KToGassize = m_FFLLNL_III_KToGas.size();
			memcpy(data, &FFLLNL_III_KToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_III_KToGassize; j++)
			{
				memcpy(data, &(m_FFLLNL_III_KToGas[j]), sizeof(double));data += sizeof(double);
			} 
			//
			memcpy(data, &(m_N_LLNL_III_OilToGas), sizeof(int));data += sizeof(int);
			int fLLNL_III_OilToGassize = m_fLLNL_III_OilToGas.size();
			memcpy(data, &fLLNL_III_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_III_OilToGassize; j++)
			{
				memcpy(data, &(m_fLLNL_III_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int fLLNL_III_OilToGasBaksize = m_fLLNL_III_OilToGasBak.size();
			memcpy(data, &fLLNL_III_OilToGasBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_III_OilToGasBaksize; j++)
			{
				memcpy(data, &(m_fLLNL_III_OilToGasBak[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_OilToGassize = m_ELLNL_III_OilToGas.size();
			memcpy(data, &ELLNL_III_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_III_OilToGassize; j++)
			{
				memcpy(data, &(m_ELLNL_III_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_OilToGassize = m_FFLLNL_III_OilToGas.size();
			memcpy(data, &FFLLNL_III_OilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_III_OilToGassize; j++)
			{
				memcpy(data, &(m_FFLLNL_III_OilToGas[j]), sizeof(double));data += sizeof(double);
			}
			//
			memcpy(data, &(m_N_LLNL_III_OilToResidue), sizeof(int));data += sizeof(int);
			int fLLNL_III_OilToResiduesize = m_fLLNL_III_OilToResidue.size();
			memcpy(data, &fLLNL_III_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_III_OilToResiduesize; j++)
			{
				memcpy(data, &(m_fLLNL_III_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			int fLLNL_III_OilToResidueBaksize = m_fLLNL_III_OilToResidueBak.size();
			memcpy(data, &fLLNL_III_OilToResidueBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fLLNL_III_OilToResidueBaksize; j++)
			{
				memcpy(data, &(m_fLLNL_III_OilToResidueBak[j]), sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_OilToResiduesize = m_ELLNL_III_OilToResidue.size();
			memcpy(data, &ELLNL_III_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ELLNL_III_OilToResiduesize; j++)
			{
				memcpy(data, &(m_ELLNL_III_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_OilToResiduesize = m_FFLLNL_III_OilToResidue.size();
			memcpy(data, &FFLLNL_III_OilToResiduesize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < FFLLNL_III_OilToResiduesize; j++)
			{
				memcpy(data, &(m_FFLLNL_III_OilToResidue[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_wBIw0_I_KToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_II_KToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_III_KToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_I_KToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_II_KToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_III_KToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_I_OilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_II_OilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_III_OilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_I_OilToResidue), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_II_OilToResidue), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0_III_OilToResidue), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilPerInitTOC_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilPerInitTOC_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilPerInitTOC_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasPerInitTOC_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasPerInitTOC_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasPerInitTOC_III), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_TOCRemained_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCRemained_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCRemained_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCracked_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCracked_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCracked_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCracked_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCracked_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCracked_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCracked_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCracked_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCracked_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilExisted_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilExisted_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilExisted_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasExisted_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasExisted_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasExisted_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueExisted_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueExisted_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueExisted_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilGenerated_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilGenerated_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilGenerated_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasGenerated_I), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasGenerated_II), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasGenerated_III), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilGenerated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasGenerated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilPerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasPerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCReactableKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCInertKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCOilKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCGasKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCRemained), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TR), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCrackedAdded), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_ResidueCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerReac), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_MKerInert), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerGas), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_W), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NKerogenType), data, sizeof(int));data += sizeof(int);
			int RatioKerogenTypesize;
			memcpy(&RatioKerogenTypesize, data, sizeof(int));data += sizeof(int);
			m_RatioKerogenType.resize(RatioKerogenTypesize);
			for(int j = 0; j < RatioKerogenTypesize; j++)
			{
				memcpy(&(m_RatioKerogenType[j]), data, sizeof(double));data += sizeof(double);
			}
			int InitTOCsize;
			memcpy(&InitTOCsize, data, sizeof(int));data += sizeof(int);
			m_InitTOC.resize(InitTOCsize);
			for(int j = 0; j < InitTOCsize; j++)
			{
				memcpy(&(m_InitTOC[j]), data, sizeof(double));data += sizeof(double);
			}
			int MassOfInitTOCsize;
			memcpy(&MassOfInitTOCsize, data, sizeof(int));data += sizeof(int);
			m_MassOfInitTOC.resize(MassOfInitTOCsize);
			for(int j = 0; j < MassOfInitTOCsize; j++)
			{
				memcpy(&(m_MassOfInitTOC[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_MassOfInitTOCTotal), data, sizeof(double));data += sizeof(double);
			int MKersize;
			memcpy(&MKersize, data, sizeof(int));data += sizeof(int);
			m_MKer.resize(MKersize);
			for(int j = 0; j < MKersize; j++)
			{
				memcpy(&(m_MKer[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_MKerTotal), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI_LLNL_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KSF_LLNL_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KToOilF_LLNL_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KToGasF_LLNL_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OSF_LLNL_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OToGasF_LLNL_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OToResidueF_LLNL_I), data, sizeof(double));data += sizeof(double);
			//����ΪI�͸��Ҹ��Ķ���ѧ����
			memcpy(&(m_N_LLNL_I_KToOil), data, sizeof(int));data += sizeof(int);
			int fLLNL_I_KToOilsize;
			memcpy(&fLLNL_I_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_I_KToOil.resize(fLLNL_I_KToOilsize);
			for(int j = 0; j < fLLNL_I_KToOilsize; j++)
			{
				memcpy(&(m_fLLNL_I_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_KToOilsize;
			memcpy(&ELLNL_I_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_I_KToOil.resize(ELLNL_I_KToOilsize);
			for(int j = 0; j < ELLNL_I_KToOilsize; j++)
			{
				memcpy(&(m_ELLNL_I_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_KToOilsize;
			memcpy(&FFLLNL_I_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_I_KToOil.resize(FFLLNL_I_KToOilsize);
			for(int j = 0; j < FFLLNL_I_KToOilsize; j++)
			{
				memcpy(&(m_FFLLNL_I_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			//
			memcpy(&(m_N_LLNL_I_KToGas), data, sizeof(int));data += sizeof(int);
			int fLLNL_I_KToGassize;
			memcpy(&fLLNL_I_KToGassize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_I_KToGas.resize(fLLNL_I_KToGassize);
			for(int j = 0; j < fLLNL_I_KToGassize; j++)
			{
				memcpy(&(m_fLLNL_I_KToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_KToGassize;
			memcpy(&ELLNL_I_KToGassize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_I_KToGas.resize(ELLNL_I_KToGassize);
			for(int j = 0; j < ELLNL_I_KToGassize; j++)
			{
				memcpy(&(m_ELLNL_I_KToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_KToGassize;
			memcpy(&FFLLNL_I_KToGassize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_I_KToGas.resize(FFLLNL_I_KToGassize);
			for(int j = 0; j < FFLLNL_I_KToGassize; j++)
			{
				memcpy(&(m_FFLLNL_I_KToGas[j]), data, sizeof(double));data += sizeof(double);
			} 
			//
			memcpy(&(m_N_LLNL_I_OilToGas), data, sizeof(int));data += sizeof(int);
			int fLLNL_I_OilToGassize;
			memcpy(&fLLNL_I_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_I_OilToGas.resize(fLLNL_I_OilToGassize);
			for(int j = 0; j < fLLNL_I_OilToGassize; j++)
			{
				memcpy(&(m_fLLNL_I_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int fLLNL_I_OilToGasBaksize;
			memcpy(&fLLNL_I_OilToGasBaksize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_I_OilToGasBak.resize(fLLNL_I_OilToGasBaksize);
			for(int j = 0; j < fLLNL_I_OilToGasBaksize; j++)
			{
				memcpy(&(m_fLLNL_I_OilToGasBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_OilToGassize;
			memcpy(&ELLNL_I_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_I_OilToGas.resize(ELLNL_I_OilToGassize);
			for(int j = 0; j < ELLNL_I_OilToGassize; j++)
			{
				memcpy(&(m_ELLNL_I_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_OilToGassize;
			memcpy(&FFLLNL_I_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_I_OilToGas.resize(FFLLNL_I_OilToGassize);
			for(int j = 0; j < FFLLNL_I_OilToGassize; j++)
			{
				memcpy(&(m_FFLLNL_I_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			//
			memcpy(&(m_N_LLNL_I_OilToResidue), data, sizeof(int));data += sizeof(int);
			int fLLNL_I_OilToResiduesize;
			memcpy(&fLLNL_I_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_I_OilToResidue.resize(fLLNL_I_OilToResiduesize);
			for(int j = 0; j < fLLNL_I_OilToResiduesize; j++)
			{
				memcpy(&(m_fLLNL_I_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			int fLLNL_I_OilToResidueBaksize;
			memcpy(&fLLNL_I_OilToResidueBaksize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_I_OilToResidueBak.resize(fLLNL_I_OilToResidueBaksize);
			for(int j = 0; j < fLLNL_I_OilToResidueBaksize; j++)
			{
				memcpy(&(m_fLLNL_I_OilToResidueBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_I_OilToResiduesize;
			memcpy(&ELLNL_I_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_I_OilToResidue.resize(ELLNL_I_OilToResiduesize);
			for(int j = 0; j < ELLNL_I_OilToResiduesize; j++)
			{
				memcpy(&(m_ELLNL_I_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_I_OilToResiduesize;
			memcpy(&FFLLNL_I_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_I_OilToResidue.resize(FFLLNL_I_OilToResiduesize);
			for(int j = 0; j < FFLLNL_I_OilToResiduesize; j++)
			{
				memcpy(&(m_FFLLNL_I_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			//����ΪLLNL II�͸��Ҹ�����
			memcpy(&(m_HI_LLNL_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KSF_LLNL_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KToOilF_LLNL_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KToGasF_LLNL_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OSF_LLNL_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OToGasF_LLNL_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OToResidueF_LLNL_II), data, sizeof(double));data += sizeof(double);
			//
			memcpy(&(m_N_LLNL_II_KToOil), data, sizeof(int));data += sizeof(int);
			int fLLNL_II_KToOilsize;
			memcpy(&fLLNL_II_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_II_KToOil.resize(fLLNL_II_KToOilsize);
			for(int j = 0; j < fLLNL_II_KToOilsize; j++)
			{
				memcpy(&(m_fLLNL_II_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_KToOilsize;
			memcpy(&ELLNL_II_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_II_KToOil.resize(ELLNL_II_KToOilsize);
			for(int j = 0; j < ELLNL_II_KToOilsize; j++)
			{
				memcpy(&(m_ELLNL_II_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_KToOilsize;
			memcpy(&FFLLNL_II_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_II_KToOil.resize(FFLLNL_II_KToOilsize);
			for(int j = 0; j < FFLLNL_II_KToOilsize; j++)
			{
				memcpy(&(m_FFLLNL_II_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			//
			memcpy(&(m_N_LLNL_II_KToGas), data, sizeof(int));data += sizeof(int);
			int fLLNL_II_KToGassize;
			memcpy(&fLLNL_II_KToGassize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_II_KToGas.resize(fLLNL_II_KToGassize);
			for(int j = 0; j < fLLNL_II_KToGassize; j++)
			{
				memcpy(&(m_fLLNL_II_KToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_KToGassize;
			memcpy(&ELLNL_II_KToGassize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_II_KToGas.resize(ELLNL_II_KToGassize);
			for(int j = 0; j < ELLNL_II_KToGassize; j++)
			{
				memcpy(&(m_ELLNL_II_KToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_KToGassize;
			memcpy(&FFLLNL_II_KToGassize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_II_KToGas.resize(FFLLNL_II_KToGassize);
			for(int j = 0; j < FFLLNL_II_KToGassize; j++)
			{
				memcpy(&(m_FFLLNL_II_KToGas[j]), data, sizeof(double));data += sizeof(double);
			} 
			//
			memcpy(&(m_N_LLNL_II_OilToGas), data, sizeof(int));data += sizeof(int);
			int fLLNL_II_OilToGassize;
			memcpy(&fLLNL_II_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_II_OilToGas.resize(fLLNL_II_OilToGassize);
			for(int j = 0; j < fLLNL_II_OilToGassize; j++)
			{
				memcpy(&(m_fLLNL_II_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int fLLNL_II_OilToGasBaksize;
			memcpy(&fLLNL_II_OilToGasBaksize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_II_OilToGasBak.resize(fLLNL_II_OilToGasBaksize);
			for(int j = 0; j < fLLNL_II_OilToGasBaksize; j++)
			{
				memcpy(&(m_fLLNL_II_OilToGasBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_OilToGassize;
			memcpy(&ELLNL_II_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_II_OilToGas.resize(ELLNL_II_OilToGassize);
			for(int j = 0; j < ELLNL_II_OilToGassize; j++)
			{
				memcpy(&(m_ELLNL_II_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_OilToGassize;
			memcpy(&FFLLNL_II_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_II_OilToGas.resize(FFLLNL_II_OilToGassize);
			for(int j = 0; j < FFLLNL_II_OilToGassize; j++)
			{
				memcpy(&(m_FFLLNL_II_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			//
			memcpy(&(m_N_LLNL_II_OilToResidue), data, sizeof(int));data += sizeof(int);
			int fLLNL_II_OilToResiduesize;
			memcpy(&fLLNL_II_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_II_OilToResidue.resize(fLLNL_II_OilToResiduesize);
			for(int j = 0; j < fLLNL_II_OilToResiduesize; j++)
			{
				memcpy(&(m_fLLNL_II_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			int fLLNL_II_OilToResidueBaksize;
			memcpy(&fLLNL_II_OilToResidueBaksize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_II_OilToResidueBak.resize(fLLNL_II_OilToResidueBaksize);
			for(int j = 0; j < fLLNL_II_OilToResidueBaksize; j++)
			{
				memcpy(&(m_fLLNL_II_OilToResidueBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_II_OilToResiduesize;
			memcpy(&ELLNL_II_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_II_OilToResidue.resize(ELLNL_II_OilToResiduesize);
			for(int j = 0; j < ELLNL_II_OilToResiduesize; j++)
			{
				memcpy(&(m_ELLNL_II_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_II_OilToResiduesize;
			memcpy(&FFLLNL_II_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_II_OilToResidue.resize(FFLLNL_II_OilToResiduesize);
			for(int j = 0; j < FFLLNL_II_OilToResiduesize; j++)
			{
				memcpy(&(m_FFLLNL_II_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			//����ΪLLNL III�͸��Ҹ�����
			memcpy(&(m_HI_LLNL_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KSF_LLNL_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KToOilF_LLNL_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_KToGasF_LLNL_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OSF_LLNL_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OToGasF_LLNL_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OToResidueF_LLNL_III), data, sizeof(double));data += sizeof(double);
			//
			memcpy(&(m_N_LLNL_III_KToOil), data, sizeof(int));data += sizeof(int);
			int fLLNL_III_KToOilsize;
			memcpy(&fLLNL_III_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_III_KToOil.resize(fLLNL_III_KToOilsize);
			for(int j = 0; j < fLLNL_III_KToOilsize; j++)
			{
				memcpy(&(m_fLLNL_III_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_KToOilsize;
			memcpy(&ELLNL_III_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_III_KToOil.resize(ELLNL_III_KToOilsize);
			for(int j = 0; j < ELLNL_III_KToOilsize; j++)
			{
				memcpy(&(m_ELLNL_III_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_KToOilsize;
			memcpy(&FFLLNL_III_KToOilsize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_III_KToOil.resize(FFLLNL_III_KToOilsize);
			for(int j = 0; j < FFLLNL_III_KToOilsize; j++)
			{
				memcpy(&(m_FFLLNL_III_KToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			//
			memcpy(&(m_N_LLNL_III_KToGas), data, sizeof(int));data += sizeof(int);
			int fLLNL_III_KToGassize;
			memcpy(&fLLNL_III_KToGassize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_III_KToGas.resize(fLLNL_III_KToGassize);
			for(int j = 0; j < fLLNL_III_KToGassize; j++)
			{
				memcpy(&(m_fLLNL_III_KToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_KToGassize;
			memcpy(&ELLNL_III_KToGassize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_III_KToGas.resize(ELLNL_III_KToGassize);
			for(int j = 0; j < ELLNL_III_KToGassize; j++)
			{
				memcpy(&(m_ELLNL_III_KToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_KToGassize;
			memcpy(&FFLLNL_III_KToGassize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_III_KToGas.resize(FFLLNL_III_KToGassize);
			for(int j = 0; j < FFLLNL_III_KToGassize; j++)
			{
				memcpy(&(m_FFLLNL_III_KToGas[j]), data, sizeof(double));data += sizeof(double);
			} 
			//
			memcpy(&(m_N_LLNL_III_OilToGas), data, sizeof(int));data += sizeof(int);
			int fLLNL_III_OilToGassize;
			memcpy(&fLLNL_III_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_III_OilToGas.resize(fLLNL_III_OilToGassize);
			for(int j = 0; j < fLLNL_III_OilToGassize; j++)
			{
				memcpy(&(m_fLLNL_III_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int fLLNL_III_OilToGasBaksize;
			memcpy(&fLLNL_III_OilToGasBaksize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_III_OilToGasBak.resize(fLLNL_III_OilToGasBaksize);
			for(int j = 0; j < fLLNL_III_OilToGasBaksize; j++)
			{
				memcpy(&(m_fLLNL_III_OilToGasBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_OilToGassize;
			memcpy(&ELLNL_III_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_III_OilToGas.resize(ELLNL_III_OilToGassize);
			for(int j = 0; j < ELLNL_III_OilToGassize; j++)
			{
				memcpy(&(m_ELLNL_III_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_OilToGassize;
			memcpy(&FFLLNL_III_OilToGassize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_III_OilToGas.resize(FFLLNL_III_OilToGassize);
			for(int j = 0; j < FFLLNL_III_OilToGassize; j++)
			{
				memcpy(&(m_FFLLNL_III_OilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			//
			memcpy(&(m_N_LLNL_III_OilToResidue), data, sizeof(int));data += sizeof(int);
			int fLLNL_III_OilToResiduesize;
			memcpy(&fLLNL_III_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_III_OilToResidue.resize(fLLNL_III_OilToResiduesize);
			for(int j = 0; j < fLLNL_III_OilToResiduesize; j++)
			{
				memcpy(&(m_fLLNL_III_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			int fLLNL_III_OilToResidueBaksize;
			memcpy(&fLLNL_III_OilToResidueBaksize, data, sizeof(int));data += sizeof(int);
			m_fLLNL_III_OilToResidueBak.resize(fLLNL_III_OilToResidueBaksize);
			for(int j = 0; j < fLLNL_III_OilToResidueBaksize; j++)
			{
				memcpy(&(m_fLLNL_III_OilToResidueBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int ELLNL_III_OilToResiduesize;
			memcpy(&ELLNL_III_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_ELLNL_III_OilToResidue.resize(ELLNL_III_OilToResiduesize);
			for(int j = 0; j < ELLNL_III_OilToResiduesize; j++)
			{
				memcpy(&(m_ELLNL_III_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			int FFLLNL_III_OilToResiduesize;
			memcpy(&FFLLNL_III_OilToResiduesize, data, sizeof(int));data += sizeof(int);
			m_FFLLNL_III_OilToResidue.resize(FFLLNL_III_OilToResiduesize);
			for(int j = 0; j < FFLLNL_III_OilToResiduesize; j++)
			{
				memcpy(&(m_FFLLNL_III_OilToResidue[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_wBIw0_I_KToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_II_KToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_III_KToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_I_KToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_II_KToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_III_KToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_I_OilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_II_OilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_III_OilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_I_OilToResidue), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_II_OilToResidue), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0_III_OilToResidue), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilPerInitTOC_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilPerInitTOC_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilPerInitTOC_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasPerInitTOC_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasPerInitTOC_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasPerInitTOC_III), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_TOCRemained_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCRemained_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCRemained_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCracked_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCracked_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCracked_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCracked_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCracked_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCracked_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCracked_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCracked_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCracked_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilExisted_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilExisted_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilExisted_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasExisted_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasExisted_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasExisted_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueExisted_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueExisted_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueExisted_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilGenerated_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilGenerated_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilGenerated_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasGenerated_I), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasGenerated_II), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasGenerated_III), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilGenerated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasGenerated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilPerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasPerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCReactableKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCInertKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCOilKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCGasKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCRemained), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TR), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCrackedAdded), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_ResidueCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerReac), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_MKerInert), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerGas), data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, LLNLKinetics &llnlkinetics)
		{
			os << "\r\n>>>>>>>>>>>>>>>LLNLKinetics parameter as flow:"; 
			os << "\r\n---- ---- ---- W:" << llnlkinetics.m_W;
			os << "\r\n---- ---- ---- NKerogenType:" << llnlkinetics.m_NKerogenType;   //���Ҹ�������
			for(int i = 0; i < llnlkinetics.m_RatioKerogenType.size(); i++)os << "\r\n---- ---- ---- m_RatioKerogenType:" << i << ":" << llnlkinetics.m_RatioKerogenType[i];
			for(int i = 0; i < llnlkinetics.m_InitTOC.size(); i++)os << "\r\n---- ---- ---- m_InitTOC:" << i << ":" << llnlkinetics.m_InitTOC[i];
			for(int i = 0; i < llnlkinetics.m_MassOfInitTOC.size(); i++)os << "\r\n---- ---- ---- m_MassOfInitTOC:" << i << ":" << llnlkinetics.m_MassOfInitTOC[i];
			os << "\r\n---- ---- ---- MassOfInitTOCTotal:" << llnlkinetics.m_MassOfInitTOCTotal; //���Ҹ�ԭʼ�л�̼�ܵ�����
			for(int i = 0; i < llnlkinetics.m_MKer.size(); i++)os << "\r\n---- ---- ---- m_MKer:" << i << ":" << llnlkinetics.m_MKer[i];
			os << "\r\n---- ---- ---- MKerTotal:" << llnlkinetics.m_MKerTotal;
			os << "\r\n---- ---- ---- HI_LLNL_I:" << llnlkinetics.m_HI_LLNL_I; //I�͸��Ҹ�����ָ��
			os << "\r\n---- ---- ---- KSF_LLNL_I:" << llnlkinetics.m_KSF_LLNL_I;//   Kerogen Start Fraction  LLNL��I�͸��Ҹ� ��Ӧ����Ҹ���ʼ�� 
			os << "\r\n---- ---- ---- KToOilF_LLNL_I:" << llnlkinetics.m_KToOilF_LLNL_I;// ���Ҹ������͵ı���
			os << "\r\n---- ---- ---- KToGasF_LLNL_I:" << llnlkinetics.m_KToGasF_LLNL_I; //  ���Ҹ��������ı���
			os << "\r\n---- ---- ---- OSF_LLNL_I:" << llnlkinetics.m_OSF_LLNL_I;  // Oil Strat Fraction ��Ӧ��������ʼ����
			os << "\r\n---- ---- ---- OToGasF_LLNL_I:" << llnlkinetics.m_OToGasF_LLNL_I; //���������ı���
			os << "\r\n---- ---- ---- OToResidueF_LLNL_I:" << llnlkinetics.m_OToResidueF_LLNL_I; //�����ɲ�����ı���
			os << "\r\n---- ---- ---- N_LLNL_I_KToOil:" << llnlkinetics.m_N_LLNL_I_KToOil;//LLNL��I�͸��Ҹ����͵�ƽ�з�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_I_KToOil.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_I_KToOil:" << i << ":" << llnlkinetics.m_fLLNL_I_KToOil[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_I_KToOil.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_I_KToOil:" << i << ":" << llnlkinetics.m_ELLNL_I_KToOil[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_I_KToOil.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_I_KToOil:" << i << ":" << llnlkinetics.m_FFLLNL_I_KToOil[i];
			os << "\r\n---- ---- ---- N_LLNL_I_KToGas:" << llnlkinetics.m_N_LLNL_I_KToGas;//LLNL��I�͸��Ҹ�������ƽ�з�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_I_KToGas.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_I_KToGas:" << i << ":" << llnlkinetics.m_fLLNL_I_KToGas[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_I_KToGas.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_I_KToGas:" << i << ":" << llnlkinetics.m_ELLNL_I_KToGas[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_I_KToGas.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_I_KToGas:" << i << ":" << llnlkinetics.m_FFLLNL_I_KToGas[i];
			os << "\r\n---- ---- ---- N_LLNL_I_OilToGas:" << llnlkinetics.m_N_LLNL_I_OilToGas;//LLNL��I�͸��Ҹ����������ķ�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_I_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_I_OilToGas:" << i << ":" << llnlkinetics.m_fLLNL_I_OilToGas[i];
			for(int i = 0; i < llnlkinetics.m_fLLNL_I_OilToGasBak.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_I_OilToGasBak:" << i << ":" << llnlkinetics.m_fLLNL_I_OilToGasBak[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_I_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_I_OilToGas:" << i << ":" << llnlkinetics.m_ELLNL_I_OilToGas[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_I_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_I_OilToGas:" << i << ":" << llnlkinetics.m_FFLLNL_I_OilToGas[i];
			os << "\r\n---- ---- ---- N_LLNL_I_OilToResidue:" << llnlkinetics.m_N_LLNL_I_OilToResidue;//LLNL��I�͸��Ҹ������ɲ�����ķ�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_I_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_I_OilToResidue:" << i << ":" << llnlkinetics.m_fLLNL_I_OilToResidue[i];
			for(int i = 0; i < llnlkinetics.m_fLLNL_I_OilToResidueBak.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_I_OilToResidueBak:" << i << ":" << llnlkinetics.m_fLLNL_I_OilToResidueBak[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_I_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_I_OilToResidue:" << i << ":" << llnlkinetics.m_ELLNL_I_OilToResidue[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_I_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_I_OilToResidue:" << i << ":" << llnlkinetics.m_FFLLNL_I_OilToResidue[i];
			os << "\r\n---- ---- ---- HI_LLNL_II:" << llnlkinetics.m_HI_LLNL_II; //II�͸��Ҹ�����ָ��
			os << "\r\n---- ---- ---- KSF_LLNL_II:" << llnlkinetics.m_KSF_LLNL_II;//   Kerogen Start Fraction  LLNL��II�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			os << "\r\n---- ---- ---- KToOilF_LLNL_II:" << llnlkinetics.m_KToOilF_LLNL_II;// ���Ҹ������͵ı���
			os << "\r\n---- ---- ---- KToGasF_LLNL_II:" << llnlkinetics.m_KToGasF_LLNL_II; //  ���Ҹ��������ı���
			os << "\r\n---- ---- ---- OSF_LLNL_II:" << llnlkinetics.m_OSF_LLNL_II;  // Oil Strat Fraction ��Ӧ��������ʼ����
			os << "\r\n---- ---- ---- OToGasF_LLNL_II:" << llnlkinetics.m_OToGasF_LLNL_II; //���������ı���
			os << "\r\n---- ---- ---- OToResidueF_LLNL_II:" << llnlkinetics.m_OToResidueF_LLNL_II; //�����ɲ�����ı���
			os << "\r\n---- ---- ---- N_LLNL_II_KToOil:" << llnlkinetics.m_N_LLNL_II_KToOil;//LLNL��II�͸��Ҹ����͵�ƽ�з�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_II_KToOil.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_II_KToOil:" << i << ":" << llnlkinetics.m_fLLNL_II_KToOil[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_II_KToOil.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_II_KToOil:" << i << ":" << llnlkinetics.m_ELLNL_II_KToOil[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_II_KToOil.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_II_KToOil:" << i << ":" << llnlkinetics.m_FFLLNL_II_KToOil[i];
			os << "\r\n---- ---- ---- N_LLNL_II_KToGas:" << llnlkinetics.m_N_LLNL_II_KToGas;//LLNL��II�͸��Ҹ�������ƽ�з�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_II_KToGas.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_II_KToGas:" << i << ":" << llnlkinetics.m_fLLNL_II_KToGas[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_II_KToGas.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_II_KToGas:" << i << ":" << llnlkinetics.m_ELLNL_II_KToGas[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_II_KToGas.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_II_KToGas:" << i << ":" << llnlkinetics.m_FFLLNL_II_KToGas[i];
			os << "\r\n---- ---- ---- N_LLNL_II_OilToGas:" << llnlkinetics.m_N_LLNL_II_OilToGas;//LLNL��II�͸��Ҹ����������ķ�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_II_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_II_OilToGas:" << i << ":" << llnlkinetics.m_fLLNL_II_OilToGas[i];
			for(int i = 0; i < llnlkinetics.m_fLLNL_II_OilToGasBak.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_II_OilToGasBak:" << i << ":" << llnlkinetics.m_fLLNL_II_OilToGasBak[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_II_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_II_OilToGas:" << i << ":" << llnlkinetics.m_ELLNL_II_OilToGas[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_II_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_II_OilToGas:" << i << ":" << llnlkinetics.m_FFLLNL_II_OilToGas[i];
			os << "\r\n---- ---- ---- N_LLNL_II_OilToResidue:" << llnlkinetics.m_N_LLNL_II_OilToResidue;//LLNL��II�͸��Ҹ������ɲ�����ķ�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_II_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_II_OilToResidue:" << i << ":" << llnlkinetics.m_fLLNL_II_OilToResidue[i];
			for(int i = 0; i < llnlkinetics.m_fLLNL_II_OilToResidueBak.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_II_OilToResidueBak:" << i << ":" << llnlkinetics.m_fLLNL_II_OilToResidueBak[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_II_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_II_OilToResidue:" << i << ":" << llnlkinetics.m_ELLNL_II_OilToResidue[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_II_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_II_OilToResidue:" << i << ":" << llnlkinetics.m_FFLLNL_II_OilToResidue[i];
			os << "\r\n---- ---- ---- HI_LLNL_III:" << llnlkinetics.m_HI_LLNL_III; //III�͸��Ҹ�����ָ��
			os << "\r\n---- ---- ---- KSF_LLNL_III:" << llnlkinetics.m_KSF_LLNL_III;//   Kerogen Start Fraction  LLNL��III�͸��Ҹ� ��Ӧ����Ҹ���ʼ��
			os << "\r\n---- ---- ---- KToOilF_LLNL_III:" << llnlkinetics.m_KToOilF_LLNL_III;// ���Ҹ������͵ı���
			os << "\r\n---- ---- ---- KToGasF_LLNL_III:" << llnlkinetics.m_KToGasF_LLNL_III; //  ���Ҹ��������ı���
			os << "\r\n---- ---- ---- OSF_LLNL_III:" << llnlkinetics.m_OSF_LLNL_III;  // Oil Strat Fraction ��Ӧ��������ʼ����
			os << "\r\n---- ---- ---- OToGasF_LLNL_III:" << llnlkinetics.m_OToGasF_LLNL_III; //���������ı���
			os << "\r\n---- ---- ---- OToResidueF_LLNL_III:" << llnlkinetics.m_OToResidueF_LLNL_III; //�����ɲ�����ı���
			os << "\r\n---- ---- ---- N_LLNL_III_KToOil:" << llnlkinetics.m_N_LLNL_III_KToOil;//LLNL��III�͸��Ҹ����͵�ƽ�з�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_III_KToOil.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_III_KToOil:" << i << ":" << llnlkinetics.m_fLLNL_III_KToOil[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_III_KToOil.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_III_KToOil:" << i << ":" << llnlkinetics.m_ELLNL_III_KToOil[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_III_KToOil.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_III_KToOil:" << i << ":" << llnlkinetics.m_FFLLNL_III_KToOil[i];
			os << "\r\n---- ---- ---- N_LLNL_III_KToGas:" << llnlkinetics.m_N_LLNL_III_KToGas;//LLNL��III�͸��Ҹ�������ƽ�з�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_III_KToGas.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_III_KToGas:" << i << ":" << llnlkinetics.m_fLLNL_III_KToGas[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_III_KToGas.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_III_KToGas:" << i << ":" << llnlkinetics.m_ELLNL_III_KToGas[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_III_KToGas.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_III_KToGas:" << i << ":" << llnlkinetics.m_FFLLNL_III_KToGas[i];
			os << "\r\n---- ---- ---- N_LLNL_III_OilToGas:" << llnlkinetics.m_N_LLNL_III_OilToGas;//LLNL��III�͸��Ҹ����������ķ�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_III_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_III_OilToGas:" << i << ":" << llnlkinetics.m_fLLNL_III_OilToGas[i];
			for(int i = 0; i < llnlkinetics.m_fLLNL_III_OilToGasBak.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_III_OilToGasBak:" << i << ":" << llnlkinetics.m_fLLNL_III_OilToGasBak[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_III_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_III_OilToGas:" << i << ":" << llnlkinetics.m_ELLNL_III_OilToGas[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_III_OilToGas.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_III_OilToGas:" << i << ":" << llnlkinetics.m_FFLLNL_III_OilToGas[i];
			os << "\r\n---- ---- ---- N_LLNL_III_OilToResidue:" << llnlkinetics.m_N_LLNL_III_OilToResidue;//LLNL��III�͸��Ҹ������ɲ�����ķ�Ӧ�����
			for(int i = 0; i < llnlkinetics.m_fLLNL_III_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_III_OilToResidue:" << i << ":" << llnlkinetics.m_fLLNL_III_OilToResidue[i];
			for(int i = 0; i < llnlkinetics.m_fLLNL_III_OilToResidueBak.size(); i++)os << "\r\n---- ---- ---- m_fLLNL_III_OilToResidueBak:" << i << ":" << llnlkinetics.m_fLLNL_III_OilToResidueBak[i];
			for(int i = 0; i < llnlkinetics.m_ELLNL_III_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_ELLNL_III_OilToResidue:" << i << ":" << llnlkinetics.m_ELLNL_III_OilToResidue[i];
			for(int i = 0; i < llnlkinetics.m_FFLLNL_III_OilToResidue.size(); i++)os << "\r\n---- ---- ---- m_FFLLNL_III_OilToResidue:" << i << ":" << llnlkinetics.m_FFLLNL_III_OilToResidue[i];
			os << "\r\n---- ---- ---- wBIw0_I_KToOil:" << llnlkinetics.m_wBIw0_I_KToOil;
			os << "\r\n---- ---- ---- wBIw0_II_KToOil:" << llnlkinetics.m_wBIw0_II_KToOil;
			os << "\r\n---- ---- ---- wBIw0_III_KToOil:" << llnlkinetics.m_wBIw0_III_KToOil;
			os << "\r\n---- ---- ---- wBIw0_I_KToGas:" << llnlkinetics.m_wBIw0_I_KToGas;
			os << "\r\n---- ---- ---- wBIw0_II_KToGas:" << llnlkinetics.m_wBIw0_II_KToGas;
			os << "\r\n---- ---- ---- wBIw0_III_KToGas:" << llnlkinetics.m_wBIw0_III_KToGas;
			os << "\r\n---- ---- ---- wBIw0_I_OilToGas:" << llnlkinetics.m_wBIw0_I_OilToGas;
			os << "\r\n---- ---- ---- wBIw0_II_OilToGas:" << llnlkinetics.m_wBIw0_II_OilToGas;
			os << "\r\n---- ---- ---- wBIw0_III_OilToGas:" << llnlkinetics.m_wBIw0_III_OilToGas;
			os << "\r\n---- ---- ---- wBIw0_I_OilToResidue:" << llnlkinetics.m_wBIw0_I_OilToResidue;
			os << "\r\n---- ---- ---- wBIw0_II_OilToResidue:" << llnlkinetics.m_wBIw0_II_OilToResidue;
			os << "\r\n---- ---- ---- wBIw0_III_OilToResidue:" << llnlkinetics.m_wBIw0_III_OilToResidue;
			os << "\r\n---- ---- ---- OilPerInitTOC_I:" << llnlkinetics.m_OilPerInitTOC_I;
			os << "\r\n---- ---- ---- OilPerInitTOC_II:" << llnlkinetics.m_OilPerInitTOC_II;
			os << "\r\n---- ---- ---- OilPerInitTOC_III:" << llnlkinetics.m_OilPerInitTOC_III;
			os << "\r\n---- ---- ---- GasPerInitTOC_I:" << llnlkinetics.m_GasPerInitTOC_I;
			os << "\r\n---- ---- ---- GasPerInitTOC_II:" << llnlkinetics.m_GasPerInitTOC_II;
			os << "\r\n---- ---- ---- GasPerInitTOC_III:" << llnlkinetics.m_GasPerInitTOC_III; 
			os << "\r\n---- ---- ---- TOCRemained_I:" << llnlkinetics.m_TOCRemained_I;
			os << "\r\n---- ---- ---- TOCRemained_II:" << llnlkinetics.m_TOCRemained_II;
			os << "\r\n---- ---- ---- TOCRemained_III:" << llnlkinetics.m_TOCRemained_III;
			os << "\r\n---- ---- ---- OilCracked_I:" << llnlkinetics.m_OilCracked_I;
			os << "\r\n---- ---- ---- OilCracked_II:" << llnlkinetics.m_OilCracked_II;
			os << "\r\n---- ---- ---- OilCracked_III:" << llnlkinetics.m_OilCracked_III;
			os << "\r\n---- ---- ---- GasCracked_I:" << llnlkinetics.m_GasCracked_I;
			os << "\r\n---- ---- ---- GasCracked_II:" << llnlkinetics.m_GasCracked_II;
			os << "\r\n---- ---- ---- GasCracked_III:" << llnlkinetics.m_GasCracked_III;
			os << "\r\n---- ---- ---- ResidueCracked_I:" << llnlkinetics.m_ResidueCracked_I;
			os << "\r\n---- ---- ---- ResidueCracked_II:" << llnlkinetics.m_ResidueCracked_II;
			os << "\r\n---- ---- ---- ResidueCracked_III:" << llnlkinetics.m_ResidueCracked_III;
			os << "\r\n---- ---- ---- OilExisted_I:" << llnlkinetics.m_OilExisted_I;
			os << "\r\n---- ---- ---- OilExisted_II:" << llnlkinetics.m_OilExisted_II;
			os << "\r\n---- ---- ---- OilExisted_III:" << llnlkinetics.m_OilExisted_III;
			os << "\r\n---- ---- ---- GasExisted_I:" << llnlkinetics.m_GasExisted_I;
			os << "\r\n---- ---- ---- GasExisted_II:" << llnlkinetics.m_GasExisted_II;
			os << "\r\n---- ---- ---- GasExisted_III:" << llnlkinetics.m_GasExisted_III;
			os << "\r\n---- ---- ---- ResidueExisted_I:" << llnlkinetics.m_ResidueExisted_I;
			os << "\r\n---- ---- ---- ResidueExisted_II:" << llnlkinetics.m_ResidueExisted_II;
			os << "\r\n---- ---- ---- ResidueExisted_III:" << llnlkinetics.m_ResidueExisted_III;
			os << "\r\n---- ---- ---- OilGenerated_I:" << llnlkinetics.m_OilGenerated_I;
			os << "\r\n---- ---- ---- OilGenerated_II:" << llnlkinetics.m_OilGenerated_II;
			os << "\r\n---- ---- ---- OilGenerated_III:" << llnlkinetics.m_OilGenerated_III;
			os << "\r\n---- ---- ---- GasGenerated_I:" << llnlkinetics.m_GasGenerated_I;
			os << "\r\n---- ---- ---- GasGenerated_II:" << llnlkinetics.m_GasGenerated_II;
			os << "\r\n---- ---- ---- GasGenerated_III:" << llnlkinetics.m_GasGenerated_III;
			os << "\r\n---- ---- ---- OilGenerated:" << llnlkinetics.m_OilGenerated;
			os << "\r\n---- ---- ---- GasGenerated:" << llnlkinetics.m_GasGenerated;
			os << "\r\n---- ---- ---- OilPerInitTOC:" << llnlkinetics.m_OilPerInitTOC;
			os << "\r\n---- ---- ---- GasPerInitTOC:" << llnlkinetics.m_GasPerInitTOC;
			os << "\r\n---- ---- ---- TOCReactableKerogen:" << llnlkinetics.m_TOCReactableKerogen;
			os << "\r\n---- ---- ---- TOCInertKerogen:" << llnlkinetics.m_TOCInertKerogen;
			os << "\r\n---- ---- ---- TOCOilKerogen:" << llnlkinetics.m_TOCOilKerogen;
			os << "\r\n---- ---- ---- TOCGasKerogen:" << llnlkinetics.m_TOCGasKerogen;
			os << "\r\n---- ---- ---- TOCKerogen:" << llnlkinetics.m_TOCKerogen;
			os << "\r\n---- ---- ---- TOCRemained:" << llnlkinetics.m_TOCRemained;
			os << "\r\n---- ---- ---- TR:" << llnlkinetics.m_TR;
			os << "\r\n---- ---- ---- OilExisted:" << llnlkinetics.m_OilExisted;
			os << "\r\n---- ---- ---- GasExisted:" << llnlkinetics.m_GasExisted;
			os << "\r\n---- ---- ---- GasCracked:" << llnlkinetics.m_GasCracked;
			os << "\r\n---- ---- ---- GasCrackedAdded:" << llnlkinetics.m_GasCrackedAdded; 
			os << "\r\n---- ---- ---- ResidueCracked:" << llnlkinetics.m_ResidueCracked;
			os << "\r\n---- ---- ---- ResidueCrackedAdded:" << llnlkinetics.m_ResidueCrackedAdded;
			os << "\r\n---- ---- ---- OilCracked:" << llnlkinetics.m_OilCracked;
			os << "\r\n---- ---- ---- OilCrackedAdded:" << llnlkinetics.m_OilCrackedAdded;
			os << "\r\n---- ---- ---- MKerReac:" << llnlkinetics.m_MKerReac; 
			os << "\r\n---- ---- ---- MKerInert:" << llnlkinetics.m_MKerInert;
			os << "\r\n---- ---- ---- MKerOil:" << llnlkinetics.m_MKerOil;
			os << "\r\n---- ---- ---- MKerGas:" << llnlkinetics.m_MKerGas;
			return os;
		}
		void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,std::vector<double> &fLLNL,std::vector<double> &FFLLNL, std::vector<double> &ELLNL,double &wBIw0)
		{  //�ֱ�����һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma����
			// ƽ�з�Ӧ����N_LLNL����ѧ����ϵ��fLLNL,Ƶ������FFLLNL�����ELLNL,�ܵ�ʣ�໯ѧ����ϵ��wBIw0
			wBIw0=0;
			double R=0.001986;//���峣�� ����λ Kcal/(mol*K)
			//������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
			double a,b; // ���Ա仯��ϵ��
			a=(T-TLast)/(t-tLast);b=T-a*t;
			//����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
			int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
			double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
			double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
			double temp=0;
			std::vector<double>wiBIw0i;  //wi/w0i ,�����EasyRo�Ƶ��еĹ�ʽ��8��
			wiBIw0i.resize(N_LLNL);
			for(int i=0;i<N_LLNL;i++)
			{
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					temp+=(-FFLLNL[i]*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
					tt1=tt2;
				}
				wiBIw0i[i]=exp(temp);
				fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //������һʱ��εĻ�ѧ����ϵ��
				wBIw0+=fLLNL[i];  // wBIw0Ϊ�ܵĻ�ѧ����ϵ��ʣ��ֵ
				tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
				temp=0;    //temp���¹���
			}
		}
		void Reactions(double TLast, double tLast, double T, double t)
	   {  //���ʱ���ϵ�һ���ز��
	   // �����Ҹ���֡��͡������ı仯��û�а����ѽⲿ��
		 // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
		 //aParaLLNL Ϊ��һ��ʱ��εĲ����ṹ
		 //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
		 // ����ԭ������PetroMod��������Դ��BasinMod
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		  //����ΪI�͸��Ҹ��Ƚ�
		  double InitwBIw0_I_KToOil=0,InitwBIw0_I_KToGas=0;  //��ʼʱ�̵ĸ����Ҹ���֣���ѧ����ϵ����֮��
		  for(int i=0;i<m_N_LLNL_I_KToOil;i++)InitwBIw0_I_KToOil+=m_fLLNL_I_KToOil[i]; for(int i=0;i<m_N_LLNL_I_KToGas;i++)InitwBIw0_I_KToGas+=m_fLLNL_I_KToGas[i];
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_KToOil,m_fLLNL_I_KToOil,m_FFLLNL_I_KToOil,m_ELLNL_I_KToOil,m_wBIw0_I_KToOil);  // I�͸��Ҹ������Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_KToGas,m_fLLNL_I_KToGas,m_FFLLNL_I_KToGas,m_ELLNL_I_KToGas,m_wBIw0_I_KToGas);  // I�͸��Ҹ������Ƚ�
		  m_OilPerInitTOC_I=m_HI_LLNL_I*m_KToOilF_LLNL_I*(InitwBIw0_I_KToOil-m_wBIw0_I_KToOil);  // *KSF_LLNL_I
		  m_GasPerInitTOC_I=m_HI_LLNL_I*m_KToGasF_LLNL_I*(InitwBIw0_I_KToGas-m_wBIw0_I_KToGas);  //*KSF_LLNL_I
		  m_OilGenerated_I=m_OilPerInitTOC_I; //
		  m_GasGenerated_I=m_GasPerInitTOC_I; //
		  m_TOCRemained_I=1.-m_W*m_OilPerInitTOC_I-m_W*m_GasPerInitTOC_I;   //��ʼʱ��ԭʼ�л�̼Ϊ1
		  //����ΪII�͸��Ҹ��Ƚ�
		  double InitwBIw0_II_KToOil=0,InitwBIw0_II_KToGas=0;  //��ʼʱ�̵ĸ����Ҹ���֣���ѧ����ϵ����֮��
		  for(int i=0;i<m_N_LLNL_II_KToOil;i++)InitwBIw0_II_KToOil+=m_fLLNL_II_KToOil[i]; for(int i=0;i<m_N_LLNL_II_KToGas;i++)InitwBIw0_II_KToGas+=m_fLLNL_II_KToGas[i];
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_II_KToOil,m_fLLNL_II_KToOil,m_FFLLNL_II_KToOil,m_ELLNL_II_KToOil,m_wBIw0_II_KToOil);  // II�͸��Ҹ������Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_II_KToGas,m_fLLNL_II_KToGas,m_FFLLNL_II_KToGas,m_ELLNL_II_KToGas,m_wBIw0_II_KToGas);  // II�͸��Ҹ������Ƚ�
		  m_OilPerInitTOC_II=m_HI_LLNL_II*m_KToOilF_LLNL_II*(InitwBIw0_II_KToOil-m_wBIw0_II_KToOil); // *KSF_LLNL_II
		  m_GasPerInitTOC_II=m_HI_LLNL_II*m_KToGasF_LLNL_II*(InitwBIw0_II_KToGas-m_wBIw0_II_KToGas);  //*KSF_LLNL_II
		  m_OilGenerated_II=m_OilPerInitTOC_II; //
		  m_GasGenerated_II=m_GasPerInitTOC_II; //
		  m_TOCRemained_II=1.-m_W*m_OilPerInitTOC_II-m_W*m_GasPerInitTOC_II;   //��ʼʱ��ԭʼ�л�̼Ϊ1
		  //����ΪIII�͸��Ҹ��Ƚ�
		  double InitwBIw0_III_KToOil=0,InitwBIw0_III_KToGas=0;  //��ʼʱ�̵ĸ����Ҹ���֣���ѧ����ϵ����֮��
		  for(int i=0;i<m_N_LLNL_III_KToOil;i++)InitwBIw0_III_KToOil+=m_fLLNL_III_KToOil[i]; for(int i=0;i<m_N_LLNL_III_KToGas;i++)InitwBIw0_III_KToGas+=m_fLLNL_III_KToGas[i];
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_III_KToOil,m_fLLNL_III_KToOil,m_FFLLNL_III_KToOil,m_ELLNL_III_KToOil,m_wBIw0_III_KToOil);  // III�͸��Ҹ������Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_III_KToGas,m_fLLNL_III_KToGas,m_FFLLNL_III_KToGas,m_ELLNL_III_KToGas,m_wBIw0_III_KToGas);  // III�͸��Ҹ������Ƚ�
		  m_OilPerInitTOC_III=m_HI_LLNL_III*m_KToOilF_LLNL_III*(InitwBIw0_III_KToOil-m_wBIw0_III_KToOil); // *KSF_LLNL_III
		  m_GasPerInitTOC_III=m_HI_LLNL_III*m_KToGasF_LLNL_III*(InitwBIw0_III_KToGas-m_wBIw0_III_KToGas); //*KSF_LLNL_III
		  m_OilGenerated_III=m_OilPerInitTOC_III; //
		  m_GasGenerated_III=m_GasPerInitTOC_III; //
		  m_TOCRemained_III=1.-m_W*m_OilPerInitTOC_III-m_W*m_GasPerInitTOC_III;   //��ʼʱ��ԭʼ�л�̼Ϊ1

		  m_OilPerInitTOC=m_OilPerInitTOC_I*m_RatioKerogenType[0]+m_OilPerInitTOC_II*m_RatioKerogenType[1]+m_OilPerInitTOC_III*m_RatioKerogenType[2]; //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
		  m_GasPerInitTOC=m_GasPerInitTOC_I*m_RatioKerogenType[0]+m_GasPerInitTOC_II*m_RatioKerogenType[1]+m_GasPerInitTOC_III*m_RatioKerogenType[2]; //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
		  m_OilGenerated=m_OilGenerated_I*m_RatioKerogenType[0]+m_OilGenerated_II*m_RatioKerogenType[1]+m_OilGenerated_III*m_RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������
		  m_GasGenerated=m_GasGenerated_I*m_RatioKerogenType[0]+m_GasGenerated_II*m_RatioKerogenType[1]+m_GasGenerated_III*m_RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������
		  
		  m_TOCRemained=m_TOCRemained_I*m_RatioKerogenType[0]+m_TOCRemained_II*m_RatioKerogenType[1]+m_TOCRemained_III*m_RatioKerogenType[2]; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
		  m_TOCKerogen=m_TOCRemained;
		  m_TOCInertKerogen=1.-m_W*(m_OSF_LLNL_I*m_RatioKerogenType[0]+m_OSF_LLNL_II*m_RatioKerogenType[1]+m_OSF_LLNL_III*m_RatioKerogenType[2])-m_W*(m_HI_LLNL_I*m_RatioKerogenType[0]+m_HI_LLNL_II*m_RatioKerogenType[1]+m_HI_LLNL_III*m_RatioKerogenType[2]);   //���Ը��Ҹ�����  ,�Ľṹ���HIֵ Ϊ g/g,������mg/g�����Բ��ó���1000
		  m_TOCReactableKerogen=m_TOCKerogen-m_TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����
		  m_TOCOilKerogen=m_W*(m_HI_LLNL_I*m_RatioKerogenType[0]*m_KToOilF_LLNL_I+m_HI_LLNL_II*m_RatioKerogenType[1]*m_KToOilF_LLNL_II+m_HI_LLNL_III*m_RatioKerogenType[2]*m_KToOilF_LLNL_III)-m_W*m_OilPerInitTOC;   // ��һ����Ӧ���ʣ���͸��Ҹ� new added 20190412
		  m_TOCGasKerogen=m_W*(m_HI_LLNL_I*m_RatioKerogenType[0]*m_KToGasF_LLNL_I+m_HI_LLNL_II*m_RatioKerogenType[1]*m_KToGasF_LLNL_II+m_HI_LLNL_III*m_RatioKerogenType[2]*m_KToGasF_LLNL_III)-m_W*m_GasPerInitTOC;   // ��һ����Ӧ���ʣ�������Ҹ� new added 20190412

		  m_TR= (m_OilGenerated+m_GasGenerated)/ (m_HI_LLNL_I*m_RatioKerogenType[0]+m_HI_LLNL_II*m_RatioKerogenType[1]+m_HI_LLNL_III*m_RatioKerogenType[2]);
		  //����ת���ʵ��ڵ�λ����ԭʼ�л�̼�ۻ����ɵ��������������ָ��Ҹ�ԭʼ�л�̼����ָ�����Ը�����ռ�ı���
	   }
		void Reactions(double TLast, double tLast, double T, double t,LLNLKinetics &aParaLLNL)
	   {  // �����Ҹ���֡��͡������ı仯��û�а����ѽⲿ��
		 // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
		 //aParaLLNL Ϊ��һ��ʱ��εĲ����ṹ
		 //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
		 // ����ԭ������PetroMod��������Դ��BasinMod
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		  //����ΪI�͸��Ҹ��Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_KToOil,m_fLLNL_I_KToOil,m_FFLLNL_I_KToOil,m_ELLNL_I_KToOil,m_wBIw0_I_KToOil);  // I�͸��Ҹ������Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_KToGas,m_fLLNL_I_KToGas,m_FFLLNL_I_KToGas,m_ELLNL_I_KToGas,m_wBIw0_I_KToGas);  // I�͸��Ҹ������Ƚ�
		  m_OilPerInitTOC_I=m_HI_LLNL_I*m_KToOilF_LLNL_I*(aParaLLNL.m_wBIw0_I_KToOil-m_wBIw0_I_KToOil);  // *KSF_LLNL_I
		  m_GasPerInitTOC_I=m_HI_LLNL_I*m_KToGasF_LLNL_I*(aParaLLNL.m_wBIw0_I_KToGas-m_wBIw0_I_KToGas); //*KSF_LLNL_I
		  m_OilGenerated_I=aParaLLNL.m_OilGenerated_I+m_OilPerInitTOC_I; //
		  m_GasGenerated_I=aParaLLNL.m_GasGenerated_I+m_GasPerInitTOC_I; //
		  m_TOCRemained_I=aParaLLNL.m_TOCRemained_I-m_W*m_OilPerInitTOC_I-m_W*m_GasPerInitTOC_I;
		  //����ΪII�͸��Ҹ��Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_II_KToOil,m_fLLNL_II_KToOil,m_FFLLNL_II_KToOil,m_ELLNL_II_KToOil,m_wBIw0_II_KToOil);  // II�͸��Ҹ������Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_II_KToGas,m_fLLNL_II_KToGas,m_FFLLNL_II_KToGas,m_ELLNL_II_KToGas,m_wBIw0_II_KToGas);  // II�͸��Ҹ������Ƚ�
		  m_OilPerInitTOC_II=m_HI_LLNL_II*m_KToOilF_LLNL_II*(aParaLLNL.m_wBIw0_II_KToOil-m_wBIw0_II_KToOil);  //*KSF_LLNL_II
		  m_GasPerInitTOC_II=m_HI_LLNL_II*m_KToGasF_LLNL_II*(aParaLLNL.m_wBIw0_II_KToGas-m_wBIw0_II_KToGas);   //*KSF_LLNL_II
		  m_OilGenerated_II=aParaLLNL.m_OilGenerated_II+m_OilPerInitTOC_II; //
		  m_GasGenerated_II=aParaLLNL.m_GasGenerated_II+m_GasPerInitTOC_II; //
		  m_TOCRemained_II=aParaLLNL.m_TOCRemained_II-m_W*m_OilPerInitTOC_II-m_W*m_GasPerInitTOC_II;
		  //����ΪIII�͸��Ҹ��Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_III_KToOil,m_fLLNL_III_KToOil,m_FFLLNL_III_KToOil,m_ELLNL_III_KToOil,m_wBIw0_III_KToOil);  // III�͸��Ҹ������Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_III_KToGas,m_fLLNL_III_KToGas,m_FFLLNL_III_KToGas,m_ELLNL_III_KToGas,m_wBIw0_III_KToGas);  // III�͸��Ҹ������Ƚ�
		  m_OilPerInitTOC_III=m_HI_LLNL_III*m_KToOilF_LLNL_III*(aParaLLNL.m_wBIw0_III_KToOil-m_wBIw0_III_KToOil);  //*KSF_LLNL_III
		  m_GasPerInitTOC_III=m_HI_LLNL_III*m_KToGasF_LLNL_III*(aParaLLNL.m_wBIw0_III_KToGas-m_wBIw0_III_KToGas);  //*KSF_LLNL_III
		  m_OilGenerated_III=aParaLLNL.m_OilGenerated_III+m_OilPerInitTOC_III; //
		  m_GasGenerated_III=aParaLLNL.m_GasGenerated_III+m_GasPerInitTOC_III; //
		  m_TOCRemained_III=aParaLLNL.m_TOCRemained_III-m_W*m_OilPerInitTOC_III-m_W*m_GasPerInitTOC_III;

		  m_OilPerInitTOC=m_OilPerInitTOC_I*m_RatioKerogenType[0]+m_OilPerInitTOC_II*m_RatioKerogenType[1]+m_OilPerInitTOC_III*m_RatioKerogenType[2];  //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
		  m_GasPerInitTOC=m_GasPerInitTOC_I*m_RatioKerogenType[0]+m_GasPerInitTOC_II*m_RatioKerogenType[1]+m_GasPerInitTOC_III*m_RatioKerogenType[2];  //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������
		  m_OilGenerated=m_OilGenerated_I*m_RatioKerogenType[0]+m_OilGenerated_II*m_RatioKerogenType[1]+m_OilGenerated_III*m_RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������
		  m_GasGenerated=m_GasGenerated_I*m_RatioKerogenType[0]+m_GasGenerated_II*m_RatioKerogenType[1]+m_GasGenerated_III*m_RatioKerogenType[2];  //���ָ��Ҹ���λ����ԭʼ�л�̼�ۼƵ�������
		  
		  m_TOCRemained=m_TOCRemained_I*m_RatioKerogenType[0]+m_TOCRemained_II*m_RatioKerogenType[1]+m_TOCRemained_III*m_RatioKerogenType[2]; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
		  m_TOCKerogen=aParaLLNL.m_TOCKerogen-m_W*m_OilPerInitTOC-m_W*m_GasPerInitTOC;
		  // TOCKerogen=TOCRemained;
		  m_TOCInertKerogen=1.-m_W*(m_OSF_LLNL_I*m_RatioKerogenType[0]+m_OSF_LLNL_II*m_RatioKerogenType[1]+m_OSF_LLNL_III*m_RatioKerogenType[2])-m_W*(m_HI_LLNL_I*m_RatioKerogenType[0]+m_HI_LLNL_II*m_RatioKerogenType[1]+m_HI_LLNL_III*m_RatioKerogenType[2]);   //���Ը��Ҹ�����  ,�Ľṹ���HIֵ Ϊ g/g,������mg/g�����Բ��ó���1000
		  m_TOCReactableKerogen=m_TOCKerogen-m_TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����
		  m_TOCOilKerogen=aParaLLNL.m_TOCOilKerogen-m_W*m_OilPerInitTOC;
		  m_TOCGasKerogen=aParaLLNL.m_TOCGasKerogen-m_W*m_GasPerInitTOC;
		  
		  m_TR= (m_OilGenerated+m_GasGenerated)/ (m_HI_LLNL_I*m_RatioKerogenType[0]+m_HI_LLNL_II*m_RatioKerogenType[1]+m_HI_LLNL_III*m_RatioKerogenType[2]);
		  //����ת���ʵ��ڵ�λ����ԭʼ�л�̼�ۻ����ɵ��������������ָ��Ҹ�ԭʼ�л�̼����ָ�����Ը�����ռ�ı���

	   }
		void OilCrackToGas(double TLast, double tLast, double T, double t)
		{    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			//����ΪStrSeg�д��ڵ����ѽ�Ϊ���Ͳ�����Ĺ��̡������ǵ�һ��ʱ�䲽����ʼʱ��Դ���в�û���ͣ����ʵ������Щ��������Ϊ0��
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��

			double InitwBIw0_I_OilToGas=0,InitwBIw0_I_OilToResidue=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
			for(int i=0;i<m_N_LLNL_I_OilToGas;i++)InitwBIw0_I_OilToGas+=m_fLLNL_I_OilToGas[i]; for(int i=0;i<m_N_LLNL_I_OilToResidue;i++)InitwBIw0_I_OilToResidue+=m_fLLNL_I_OilToResidue[i];
			FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_OilToGas,m_fLLNL_I_OilToGas,m_FFLLNL_I_OilToGas,m_ELLNL_I_OilToGas,m_wBIw0_I_OilToGas);  // I�͸��Ҹ�������ѽ�Ϊ��
			FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_OilToResidue,m_fLLNL_I_OilToResidue,m_FFLLNL_I_OilToResidue,m_ELLNL_I_OilToResidue,m_wBIw0_I_OilToResidue);  // I�͸��Ҹ�������ѽ�Ϊ������
			m_OilExisted=m_MassOfInitTOCTotal*(m_OSF_LLNL_I*m_RatioKerogenType[0]+m_OSF_LLNL_II*m_RatioKerogenType[1]+m_OSF_LLNL_III*m_RatioKerogenType[2])/m_W; //��ʼʱ�̵��͵�����ָ���ǵ�λԭʼ���Ҹ��е��͵�����
			m_GasExisted=0.;    //��ʼʱ�̵ĺ�����Ϊ0
			m_GasCracked=m_OilExisted*m_OToGasF_LLNL_I*(InitwBIw0_I_OilToGas-m_wBIw0_I_OilToGas);   //һ������£��ڳ�ʼʱ��OilExisted=0 , OSF_LLNL_I Ϊ��Ӧ����ͣ��ĳ�ʼ����Ҳ��0
			m_ResidueCracked=m_OilExisted*m_OToResidueF_LLNL_I*(InitwBIw0_I_OilToResidue-m_wBIw0_I_OilToResidue);  //һ������£��ڳ�ʼʱ��OilExisted=0 , OSF_LLNL_I Ϊ��Ӧ����ͣ��ĳ�ʼ����Ҳ��0
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_GasCrackedAdded=m_GasCracked;//�����ǵ�һ��ʱ�䲽��������ۻ��ѽ������ڳ�ʼ�ѽ�����
			m_ResidueCrackedAdded=m_ResidueCracked;
			m_OilCrackedAdded=m_OilCracked;
			m_OilExisted =m_OilExisted +m_OilPerInitTOC*m_MassOfInitTOCTotal-m_OilCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���ɵ�������ȥ��ʱ�䲽�ѽ�ļ�������
			m_GasExisted = m_GasExisted +m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���ɵ��������ϸ�ʱ�䲽�ѽ����ɵ�����
			m_wBIw0_I_OilToGas=0,m_wBIw0_I_OilToResidue=0;
			for(int i=0;i<m_N_LLNL_I_OilToGas;i++) { m_wBIw0_I_OilToGas+=m_fLLNL_I_OilToGasBak[i]; }   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
			for(int i=0;i<m_N_LLNL_I_OilToResidue;i++){ m_wBIw0_I_OilToResidue+=m_fLLNL_I_OilToResidueBak[i];}//ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
		}
		void OilCrackToGas(double TLast, double tLast, double T, double t,LLNLKinetics &aParaLLNL)
		{    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			//����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
			//����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��

			for(int i=0;i<m_N_LLNL_I_OilToGas;i++) m_fLLNL_I_OilToGas[i]=m_fLLNL_I_OilToGasBak[i];  //������ÿ���ѽⶼ�����Ը��Ҹ������͵Ĳ��䣬���������ѽ���������£�������LLNLģ�ͣ����ѽ�Ļ��Ϊ��ֵ�������ڲ�ͬ��ֲܷ����͵Ļ�����⣬��˻�ѧ����ϵ������Ϊ��ʼֵ,
			for(int i=0;i<m_N_LLNL_I_OilToResidue;i++) m_fLLNL_I_OilToResidue[i]=m_fLLNL_I_OilToResidueBak[i];
			FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_OilToGas,m_fLLNL_I_OilToGas,m_FFLLNL_I_OilToGas,m_ELLNL_I_OilToGas,m_wBIw0_I_OilToGas);  // ���ѽ�Ϊ��
			FirstOrderReaction(TLast, tLast,T,t,m_N_LLNL_I_OilToResidue,m_fLLNL_I_OilToResidue,m_FFLLNL_I_OilToResidue,m_ELLNL_I_OilToResidue,m_wBIw0_I_OilToResidue);  // ���ѽ�Ϊ������
			m_GasCracked=aParaLLNL.m_OilExisted*m_OToGasF_LLNL_I*(aParaLLNL.m_wBIw0_I_OilToGas-m_wBIw0_I_OilToGas);
			m_ResidueCracked=aParaLLNL.m_OilExisted*m_OToResidueF_LLNL_I*(aParaLLNL.m_wBIw0_I_OilToResidue-m_wBIw0_I_OilToResidue);
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_GasCrackedAdded=aParaLLNL.m_GasCrackedAdded+m_GasCracked;
			m_ResidueCrackedAdded=aParaLLNL.m_ResidueCrackedAdded+m_ResidueCracked;
			m_OilCrackedAdded=aParaLLNL.m_OilCrackedAdded+m_OilCracked;
			m_OilExisted=aParaLLNL.m_OilExisted+m_OilPerInitTOC*m_MassOfInitTOCTotal-m_OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
			m_GasExisted=aParaLLNL.m_GasExisted+m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
			m_wBIw0_I_OilToGas=0,m_wBIw0_I_OilToResidue=0;
			for(int i=0;i<m_N_LLNL_I_OilToGas;i++) { m_wBIw0_I_OilToGas+=m_fLLNL_I_OilToGasBak[i]; }   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
			for(int i=0;i<m_N_LLNL_I_OilToResidue;i++){ m_wBIw0_I_OilToResidue+=m_fLLNL_I_OilToResidueBak[i];}//ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ
		}
		void SetToItsOrifOilToGas()
		{  //��fOilToGas�趨Ϊԭʼֵ����Ҫ�����ڳ�ѹ�ز�ָ�ʱ���ж��ѭ���������Ӧ�ã�
			//��ʹ���¸�ѭ��ʱ�����õ� fOilToGas���µģ��������ϸ�ѭ��������¼�Ľ��
			for(int i=0;i<m_N_LLNL_I_OilToGas;i++) m_fLLNL_I_OilToGas[i]=m_fLLNL_I_OilToGasBak[i];
		}
		void GetMKer()
		{   //���Դ���и��Ҹ����л�̼������
			//m_MKerInert=(m_KSF_LLNL_I-m_HI_LLNL_I*m_W)*m_MassOfInitTOC[0]+(m_KSF_LLNL_II-m_HI_LLNL_II*m_W)*m_MassOfInitTOC[1]+(m_KSF_LLNL_III-m_HI_LLNL_III*m_W)*m_MassOfInitTOC[2];
			//m_MKer.resize(m_NKerogenType);
			//m_MKer[0]=m_TOCRemained_I *m_MassOfInitTOC[0];  //�����л�̼�����������Գ�ʼ�л�̼����
			//m_MKer[1]=m_TOCRemained_II *m_MassOfInitTOC[1];
			//m_MKer[2]=m_TOCRemained_III *m_MassOfInitTOC[2];
			//m_MKerTotal=m_MKer[0]+m_MKer[1]+m_MKer[2];
			//m_MKerReac=m_MKerTotal-m_MKerInert;
			m_MKerTotal=m_TOCKerogen*m_MassOfInitTOCTotal;         //new added 20190412
			m_MKerInert=m_TOCInertKerogen*m_MassOfInitTOCTotal;     //new added 20190412
			m_MKerReac= m_MKerTotal-m_MKerInert;                   //new added 20190412
			m_MKerOil=m_TOCOilKerogen*m_MassOfInitTOCTotal;         //new added 20190412
			m_MKerGas=m_TOCGasKerogen*m_MassOfInitTOCTotal;         //new added 20190412
		}
	};

	struct OilInResCracking2C
	{
		//����Ϊ����������ֵ��ѽ⣬Ҳ����Դ���п�϶���͵��ѽ⣻�������������ģ���龰
		// double W; //W = 0.85 kgC kgHC^-1  ,����λ�������ຬ�е�̼����   ������Cooles et al. (1986),���Ǽ򵥵ؼ������еĸ�ֵ��ΪW=0.85����
		double m_FFOilToGas; //Frequency factor S-1
		double m_EmeanOilToGas;
		double m_SigmaOilToGas; //�ֱ������ѽ�Ϊ���Ķ���ѧ������������̬�ֲ��ľ��ʺͱ�׼��    KJ/mol
		int m_NOilToGas;//���ѽ�Ϊ����ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
		std::vector<double> m_fOilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor�� ��ͨ������̬�ֲ���ɢ���õ�
		std::vector<double> m_fOilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_EOilToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�
		double m_OToGasF; //���ѽ�Ϊ���ı���
		// double OToResidueF; //���ѽ�Ϊ������ı�������� OToResidueF=1-OToGasF
		//  ���������̿�ⲿ�ֲ������г��ˣ��������ѽ�Ϊ���ĸ�����
		double m_wBIw0OilToGas;//���ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
		double m_wBIw0K; //���Ҹ����͵��ܵ�ʣ�໯ѧ����ϵ����ԭʼΪ1��
		//���������ѽ��йصĶ��Ƕ�Ӧ����������ԭʼ�л�̼������
		double m_OilExisted; //ָ���Ǵ����ڴ����У�����Դ�ҿ�϶�У��������
		double m_GasExisted; //ָ���Ǵ����ڴ����У�����Դ�ҿ�϶�У��������
		double m_ResidueExisted; //ָ�����ڴ����е����ѽ�Ϊ��������
		double m_GasCracked;//ָ����ÿһ�����ѽ������
		double m_GasCrackedAdded; //ָÿһ���ѽ������ۼ���
		double m_ResidueCracked; // ָ����ÿһ�����ѽ�Ĳ�������
		double m_ResidueCrackedAdded; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
		double m_OilCracked;//ÿһ���͵��ѽ���
		double m_OilCrackedAdded;//ÿһ���͵��ѽ������ۼ���

		int m_NFlowInOil; //�������������͵�������
		std::vector<double> m_MassFlowInOil; //������������͵���������Ȼ����������������ͣ�����Ϊ��������Ϊ����
		std::vector<double> m_MassFlowInGas; //�����������������������Ȼ�����������������������Ϊ��������Ϊ����
		std::vector<double> m_RatioFlowInOil; //���������и����͵ı��� �������������������ı�ֵ
		std::vector<std::vector<double> > m_fOilToGasFlowInOil; //������͵Ļ�ѧ����ϵ��  ����Щ��ѧ����ϵ����Ϊ����������������һʱ�̵Ļ�ѧ����ϵ��

		double m_InitialMassOfOil;   //��ʼʱ�̵���������
		double m_InitialMassOfGas;   //��ʼʱ�̵���������
		double m_CrackLeftedOil;//�ѽ��ʣ�������
		double m_ExpedOil; //�ų�ȥ������
		double m_CrackAndExpLeftedOil; //�ѽ���ų���ʣ�������
		double m_RatioCrackAndExpLeftedOil; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���

		double m_RatioGasFromOilCracking;   //��λ�������ѽ�Ϊ������
		double m_RatioResidueFromOilCracking;  //��λ�������ѽ�Ϊ���������
		double m_RatioOilFromOilCracking;  //�����ѽ�ı���

		OilInResCracking2C()
		{
			m_OToGasF=0.5; //���ѽ�Ϊ���ı���
			m_FFOilToGas=1.0e14; m_EmeanOilToGas=246.628; m_SigmaOilToGas=6.248;     //�����ʼ���ѽ� �Ļ�ѧ����ѧ������Դ��Pepper,1995��P327 (5)��(6)��HI=1176ʱ�õ�
			m_NOilToGas=21; //��������̫�ֲ��ֳ�21�����䣬��������ֵλ����һ�����䣬�������߶ԳƵطֱ�ֲ���10���� �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma ��������0.9974�ĸ������䣩
			m_fOilToGas.resize(m_NOilToGas); m_EOilToGas.resize(m_NOilToGas);
			GetEachfAndE(m_NOilToGas, m_EmeanOilToGas,m_SigmaOilToGas,m_fOilToGas,m_EOilToGas);Normalization(m_NOilToGas,m_fOilToGas);
			m_fOilToGasBak.resize(m_NOilToGas); for(int i=0;i<m_NOilToGas;i++) m_fOilToGasBak[i]=m_fOilToGas[i];
		}
		OilInResCracking2C(const OilInResCracking2C &other)
		{
			*this = other;
		}
		const OilInResCracking2C &operator=(const OilInResCracking2C &other)
		{  
			if(this == &other)
			{
				return *this;
			}
			m_FFOilToGas = other.m_FFOilToGas;
			m_EmeanOilToGas = other.m_EmeanOilToGas;
			m_SigmaOilToGas = other.m_SigmaOilToGas;
			m_NOilToGas = other.m_NOilToGas;
			m_fOilToGas = other.m_fOilToGas;
			m_fOilToGasBak = other.m_fOilToGasBak;
			m_EOilToGas = other.m_EOilToGas;
			m_OToGasF = other.m_OToGasF; 
			m_wBIw0OilToGas = other.m_wBIw0OilToGas;
			m_wBIw0K = other.m_wBIw0K; 
			m_OilExisted = other.m_OilExisted; 
			m_GasExisted = other.m_GasExisted;
			m_ResidueExisted = other.m_ResidueExisted; 
			m_GasCracked = other.m_GasCracked;
			m_GasCrackedAdded = other.m_GasCrackedAdded; 
			m_ResidueCracked = other.m_ResidueCracked; 
			m_ResidueCrackedAdded = other.m_ResidueCrackedAdded; 
			m_OilCracked = other.m_OilCracked;
			m_OilCrackedAdded = other.m_OilCrackedAdded;
			m_NFlowInOil = other.m_NFlowInOil;
			m_MassFlowInOil = other.m_MassFlowInOil;
			m_MassFlowInGas = other.m_MassFlowInGas;
			m_RatioFlowInOil = other.m_RatioFlowInOil;
			m_fOilToGasFlowInOil = other.m_fOilToGasFlowInOil;
			m_InitialMassOfOil = other.m_InitialMassOfOil;
			m_InitialMassOfGas = other.m_InitialMassOfGas;
			m_CrackLeftedOil = other.m_CrackLeftedOil;
			m_ExpedOil = other.m_ExpedOil;
			m_CrackAndExpLeftedOil = other.m_CrackAndExpLeftedOil;
			m_RatioCrackAndExpLeftedOil = other.m_RatioCrackAndExpLeftedOil;
			m_RatioGasFromOilCracking = other.m_RatioGasFromOilCracking;
			m_RatioResidueFromOilCracking = other.m_RatioResidueFromOilCracking;
			m_RatioOilFromOilCracking = other.m_RatioOilFromOilCracking;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_FFOilToGas;
			curSize += sizeof(double);//double m_EmeanOilToGas;
			curSize += sizeof(double);//double m_SigmaOilToGas; 
			curSize += sizeof(int);//int m_NOilToGas;
			curSize += (sizeof(int) + m_fOilToGas.size() * sizeof(double));//std::vector<double> m_fOilToGas;
			curSize += (sizeof(int) + m_fOilToGasBak.size() * sizeof(double));//std::vector<double> m_fOilToGasBak; 
			curSize += (sizeof(int) + m_EOilToGas.size() * sizeof(double));//std::vector<double> m_EOilToGas;
			curSize += sizeof(double);//double m_OToGasF;
			curSize += sizeof(double);//double m_wBIw0OilToGas;
			curSize += sizeof(double);//double m_wBIw0K; 
			curSize += sizeof(double);//double m_OilExisted; 
			curSize += sizeof(double);//double m_GasExisted;
			curSize += sizeof(double);//double m_ResidueExisted; 
			curSize += sizeof(double);//double m_GasCracked;
			curSize += sizeof(double);//double m_GasCrackedAdded;
			curSize += sizeof(double);//double m_ResidueCracked;
			curSize += sizeof(double);//double m_ResidueCrackedAdded;
			curSize += sizeof(double);//double m_OilCracked;
			curSize += sizeof(double);//double m_OilCrackedAdded;
			curSize += sizeof(int);//int m_NFlowInOil; 
			curSize += (sizeof(int) + m_MassFlowInOil.size() * sizeof(double));//std::vector<double> m_MassFlowInOil; 
			curSize += (sizeof(int) + m_MassFlowInGas.size() * sizeof(double));//std::vector<double> m_MassFlowInGas; 
			curSize += (sizeof(int) + m_RatioFlowInOil.size() * sizeof(double));//std::vector<double> m_RatioFlowInOil;
			curSize += sizeof(int);//std::vector<std::vector<double> > m_fOilToGasFlowInOil;
			for(int i = 0; i < m_fOilToGasFlowInOil.size(); i++)
			{
				curSize += (sizeof(int) + m_fOilToGasFlowInOil[i].size() * sizeof(double));
			}
			curSize += sizeof(double);//double m_InitialMassOfOil;  
			curSize += sizeof(double);//double m_InitialMassOfGas;  
			curSize += sizeof(double);//double m_CrackLeftedOil;
			curSize += sizeof(double);//double m_ExpedOil;
			curSize += sizeof(double);//double m_CrackAndExpLeftedOil; 
			curSize += sizeof(double);//double m_RatioCrackAndExpLeftedOil;
			curSize += sizeof(double);//double m_RatioGasFromOilCracking;
			curSize += sizeof(double);//double m_RatioResidueFromOilCracking;
			curSize += sizeof(double);//double m_RatioOilFromOilCracking;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_FFOilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_EmeanOilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_SigmaOilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_NOilToGas, sizeof(int));data += sizeof(int);
			int fOilToGassize = m_fOilToGas.size();
			memcpy(data, &fOilToGassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fOilToGassize; i++)
			{
				memcpy(data, &(m_fOilToGas[i]), sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize = m_fOilToGasBak.size();
			memcpy(data, &fOilToGasBaksize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fOilToGasBaksize; i++)
			{
				memcpy(data, &(m_fOilToGasBak[i]), sizeof(double));data += sizeof(double);
			}
			int EOilToGassize = m_EOilToGas.size();
			memcpy(data, &EOilToGassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < EOilToGassize; i++)
			{
				memcpy(data, &(m_EOilToGas[i]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &m_OToGasF, sizeof(double));data += sizeof(double);
			memcpy(data, &m_wBIw0OilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_wBIw0K, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_OilExisted, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasExisted, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ResidueExisted, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasCracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GasCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ResidueCracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ResidueCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilCracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_NFlowInOil, sizeof(int));data += sizeof(int);
			int MassFlowInOilsize = m_MassFlowInOil.size();
			memcpy(data, &MassFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInOilsize; i++)
			{
				memcpy(data, &(m_MassFlowInOil[i]), sizeof(double));data += sizeof(double);
			}
			int MassFlowInGassize = m_MassFlowInGas.size();
			memcpy(data, &MassFlowInGassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInGassize; i++)
			{
				memcpy(data, &(m_MassFlowInGas[i]), sizeof(double));data += sizeof(double);
			}
			int RatioFlowInOilsize = m_RatioFlowInOil.size();
			memcpy(data, &RatioFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < RatioFlowInOilsize; i++)
			{
				memcpy(data, &(m_RatioFlowInOil[i]), sizeof(double));data += sizeof(double);
			}
			int fOilToGasFlowInOilsize = m_fOilToGasFlowInOil.size();
			memcpy(data, &fOilToGasFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fOilToGasFlowInOilsize; i++)
			{
				int fOilToGasFlowInOilisize = m_fOilToGasFlowInOil[i].size();
				memcpy(data, &fOilToGasFlowInOilisize, sizeof(int));data += sizeof(int);
				for(int j = 0; j < fOilToGasFlowInOilisize; j++)
				{
					memcpy(data, &(m_fOilToGasFlowInOil[i][j]), sizeof(double));data += sizeof(double);
				}
			}
			memcpy(data, &m_InitialMassOfOil, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_InitialMassOfGas, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_CrackLeftedOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ExpedOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_CrackAndExpLeftedOil, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioCrackAndExpLeftedOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_RatioGasFromOilCracking, sizeof(double));data += sizeof(double);
			memcpy(data, &m_RatioResidueFromOilCracking, sizeof(double));data += sizeof(double);
			memcpy(data, &m_RatioOilFromOilCracking, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_FFOilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_EmeanOilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_SigmaOilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_NOilToGas, data, sizeof(int));data += sizeof(int);
			int fOilToGassize;
			memcpy(&fOilToGassize, data, sizeof(int));data += sizeof(int);
			m_fOilToGas.resize(fOilToGassize);
			for(int i = 0; i < fOilToGassize; i++)
			{
				memcpy(&(m_fOilToGas[i]), data, sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize;
			memcpy(&fOilToGasBaksize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasBak.resize(fOilToGasBaksize);
			for(int i = 0; i < fOilToGasBaksize; i++)
			{
				memcpy(&(m_fOilToGasBak[i]), data, sizeof(double));data += sizeof(double);
			}
			int EOilToGassize;
			memcpy(&EOilToGassize, data, sizeof(int));data += sizeof(int);
			m_EOilToGas.resize(EOilToGassize);
			for(int i = 0; i < EOilToGassize; i++)
			{
				memcpy(&(m_EOilToGas[i]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&m_OToGasF, data, sizeof(double));data += sizeof(double);
			memcpy(&m_wBIw0OilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_wBIw0K, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_OilExisted, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasExisted, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ResidueExisted, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasCracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GasCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ResidueCracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ResidueCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilCracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_NFlowInOil, data, sizeof(int));data += sizeof(int);
			int MassFlowInOilsize;
			memcpy(&MassFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_MassFlowInOil.resize(MassFlowInOilsize);
			for(int i = 0; i < MassFlowInOilsize; i++)
			{
				memcpy(&(m_MassFlowInOil[i]), data, sizeof(double));data += sizeof(double);
			}
			int MassFlowInGassize;
			memcpy(&MassFlowInGassize, data, sizeof(int));data += sizeof(int);
			m_MassFlowInGas.resize(MassFlowInGassize);
			for(int i = 0; i < MassFlowInGassize; i++)
			{
				memcpy(&(m_MassFlowInGas[i]), data, sizeof(double));data += sizeof(double);
			}
			int RatioFlowInOilsize;
			memcpy(&RatioFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_RatioFlowInOil.resize(RatioFlowInOilsize);
			for(int i = 0; i < RatioFlowInOilsize; i++)
			{
				memcpy(&(m_RatioFlowInOil[i]), data, sizeof(double));data += sizeof(double);
			}
			int fOilToGasFlowInOilsize;
			memcpy(&fOilToGasFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasFlowInOil.resize(fOilToGasFlowInOilsize);
			for(int i = 0; i < fOilToGasFlowInOilsize; i++)
			{
				int fOilToGasFlowInOilisize;
				memcpy(&fOilToGasFlowInOilisize, data, sizeof(int));data += sizeof(int);
				m_fOilToGasFlowInOil[i].resize(fOilToGasFlowInOilisize);
				for(int j = 0; j < fOilToGasFlowInOilisize; j++)
				{
					memcpy(&(m_fOilToGasFlowInOil[i][j]), data, sizeof(double));data += sizeof(double);
				}
			}
			memcpy(&m_InitialMassOfOil, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_InitialMassOfGas, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_CrackLeftedOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ExpedOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_CrackAndExpLeftedOil, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioCrackAndExpLeftedOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_RatioGasFromOilCracking, data, sizeof(double));data += sizeof(double);
			memcpy(&m_RatioResidueFromOilCracking, data, sizeof(double));data += sizeof(double);
			memcpy(&m_RatioOilFromOilCracking, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, OilInResCracking2C &oilintescracking2c)
		{
			os << "\r\n>>>>>>>>>>>>>>>OilInResCracking2C parameter as flow:";
			os << "\r\n---- ---- ---- FFOilToGas:" << oilintescracking2c.m_FFOilToGas;
			os << "\r\n---- ---- ---- EmeanOilToGas:" << oilintescracking2c.m_EmeanOilToGas;
			os << "\r\n---- ---- ---- SigmaOilToGas:" << oilintescracking2c.m_SigmaOilToGas;
			os << "\r\n---- ---- ---- NOilToGas:" << oilintescracking2c.m_NOilToGas;
			for(int i = 0; i < oilintescracking2c.m_fOilToGas.size(); i++)
			{
				os << "\r\n---- ---- ---- m_fOilToGas:" << i << ":" << oilintescracking2c.m_fOilToGas[i];
			}
			for(int i = 0; i < oilintescracking2c.m_fOilToGasBak.size(); i++)
			{
				os << "\r\n---- ---- ---- m_fOilToGasBak:" << i << ":" << oilintescracking2c.m_fOilToGasBak[i];
			}
			for(int i = 0; i < oilintescracking2c.m_EOilToGas.size(); i++)
			{
				os << "\r\n---- ---- ---- m_EOilToGas:" << i << ":" << oilintescracking2c.m_EOilToGas[i];
			}
			os << "\r\n---- ---- ---- OToGasF:" << oilintescracking2c.m_OToGasF; 
			os << "\r\n---- ---- ---- wBIw0OilToGas:" << oilintescracking2c.m_wBIw0OilToGas;
			os << "\r\n---- ---- ---- wBIw0K:" << oilintescracking2c.m_wBIw0K; 
			os << "\r\n---- ---- ---- OilExisted:" << oilintescracking2c.m_OilExisted; 
			os << "\r\n---- ---- ---- GasExisted:" << oilintescracking2c.m_GasExisted;
			os << "\r\n---- ---- ---- ResidueExisted:" << oilintescracking2c.m_ResidueExisted; 
			os << "\r\n---- ---- ---- GasCracked:" << oilintescracking2c.m_GasCracked;
			os << "\r\n---- ---- ---- GasCrackedAdded:" << oilintescracking2c.m_GasCrackedAdded; 
			os << "\r\n---- ---- ---- ResidueCracked:" << oilintescracking2c.m_ResidueCracked; 
			os << "\r\n---- ---- ---- ResidueCrackedAdded:" << oilintescracking2c.m_ResidueCrackedAdded; 
			os << "\r\n---- ---- ---- OilCracked:" << oilintescracking2c.m_OilCracked;
			os << "\r\n---- ---- ---- OilCrackedAdded:" << oilintescracking2c.m_OilCrackedAdded;
			os << "\r\n---- ---- ---- NFlowInOil:" << oilintescracking2c.m_NFlowInOil;
			for(int i = 0; i < oilintescracking2c.m_MassFlowInOil.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInOil:" << i << ":" << oilintescracking2c.m_MassFlowInOil[i];
			}
			for(int i = 0; i < oilintescracking2c.m_MassFlowInGas.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInGas:" << i << ":" << oilintescracking2c.m_MassFlowInGas[i];
			}
			for(int i = 0; i < oilintescracking2c.m_RatioFlowInOil.size(); i++)
			{
				os << "\r\n---- ---- ---- m_RatioFlowInOil:" << i << ":" << oilintescracking2c.m_RatioFlowInOil[i];
			}
			for(int i = 0; i < oilintescracking2c.m_fOilToGasFlowInOil.size(); i++)
			{
				for(int j = 0; j < oilintescracking2c.m_fOilToGasFlowInOil[i].size(); j++)
				{
					os << "\r\n---- ---- ---- m_fOilToGasFlowInOil:" << i << ":" << j << ":" << oilintescracking2c.m_fOilToGasFlowInOil[i][j];
				}
			}
			os << "\r\n---- ---- ---- InitialMassOfOil:" << oilintescracking2c.m_InitialMassOfOil;
			os << "\r\n---- ---- ---- InitialMassOfGas:" << oilintescracking2c.m_InitialMassOfGas;
			os << "\r\n---- ---- ---- CrackLeftedOil:" << oilintescracking2c.m_CrackLeftedOil;
			os << "\r\n---- ---- ---- ExpedOil:" << oilintescracking2c.m_ExpedOil;
			os << "\r\n---- ---- ---- CrackAndExpLeftedOil:" << oilintescracking2c.m_CrackAndExpLeftedOil;
			os << "\r\n---- ---- ---- RatioCrackAndExpLeftedOil:" << oilintescracking2c.m_RatioCrackAndExpLeftedOil;
			os << "\r\n---- ---- ---- RatioGasFromOilCracking:" << oilintescracking2c.m_RatioGasFromOilCracking;
			os << "\r\n---- ---- ---- RatioResidueFromOilCracking:" << oilintescracking2c.m_RatioResidueFromOilCracking;
			os << "\r\n---- ---- ---- RatioOilFromOilCracking:" << oilintescracking2c.m_RatioOilFromOilCracking;
			return os;
		}
		double Jiecheng(int n) //n�Ľ׳�
		{double temp=1; for(int i=0;i<n;i++) temp=temp*double(i+1); return temp; }
		double erf(double x)
		{  //����
			int N=30; //����ľ������
			double pi=3.1415926535;  double temp=0;
			for(int i=0;i<N+1;i++) temp+=pow((double)-1,(double)i)*pow(x,2*i+1)/(2*i+1)/Jiecheng(i);
			temp=temp*2/sqrt(pi);
			return temp;
		}
		double Pnormal(double q,double Emean,double Sigma)
		{//��̬�ֲ��ۻ����ʺ���ֵ����q������ Emean��4*Sigma�ķ�Χ�ڶ�����
			double temp=(q-Emean)/Sigma/sqrt(2.);
			return 0.5+0.5*erf(temp);
		}
		void GetEachfAndE(int N, double aE,double aSigma,std::vector<double> &f,std::vector<double> &E)
		{ //���ݻ��������������̬�ֲ��ľ��ʺͱ�׼������ɢ�Ļ�ܺͶ�Ӧ�Ļ�ѧ����ϵ��
			double LeftPoint, RightPoint; //���Ҷϵ��ֵ �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma
			double Delta; //N�������ÿ������ľ��롪��ƽ����������
			LeftPoint=aE-3.*aSigma; RightPoint=aE+3.*aSigma;
			Delta=6.*aSigma/double(N);
			for(int i=0;i<N;i++)
			{
				if(i==0)
				{    //��������丳ֵ
					E[i]=LeftPoint+0.5*Delta;//ȡ�����е�ֵ
					f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma); //��������ĸ���ֵȡֵΪ�������Ҷ�ֵ����˰����˸�����ֵ������������еĸ���ֵ
				}
				if(i>0&&i<N-1)
				{   //�м�����丳ֵ
					E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
					f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);
				}
				if(i==N-1)
				{  //���ұ����丳ֵ
					E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
					f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);   //��������ĸ���ֵȡֵΪ������ֵ�������ұ����еĸ���ֵ
				}
			}
		}
		void Normalization(int N,std::vector<double> &f)
		{   //��ֵ��һ��
			double Sum=0.;
			for(int i=0;i<N;i++) Sum+=f[i];
			for(int i=0;i<N;i++) f[i]=f[i]/Sum;
		}
		void CopyFromForPC(OilInResCracking2C &aOilInResCracking2C)   //���������
		{   //����һ���ṹ�п���һ�ݲ���
			m_OToGasF=aOilInResCracking2C.m_OToGasF; //���ѽ�Ϊ���ı���
			m_NOilToGas=aOilInResCracking2C.m_NOilToGas;
			m_fOilToGas.clear();m_fOilToGas.resize(m_NOilToGas);m_fOilToGasBak.clear();m_fOilToGasBak.resize(m_NOilToGas); m_EOilToGas.clear();m_EOilToGas.resize(m_NOilToGas);
			for(int i=0;i<m_NOilToGas;i++)
			{
				//fOilToGas[i]=aOilInResCracking2C->fOilToGas[i];
				//fOilToGasBak[i]=aOilInResCracking2C->fOilToGasBak[i];  //��Դ�������͵��ѽⲻͬ��
				m_fOilToGasBak[i]=aOilInResCracking2C.m_fOilToGasBak[i];
				m_EOilToGas[i]=aOilInResCracking2C.m_EOilToGas[i];
			}
		}
		void GenerateNewfOilToGas(double OilInRockPoros,double MExpOil) //����������ͬ�͵Ķ���ȷ���µ�fOilToGas
		{
			double Ratio01,Ratio02;
			Ratio01=OilInRockPoros/(OilInRockPoros+MExpOil);
			Ratio02=MExpOil/(OilInRockPoros+MExpOil);
			for(int i=0;i<m_NOilToGas;i++)
				m_fOilToGas[i]=Ratio01*m_fOilToGas[i]+Ratio02*m_fOilToGasBak[i];
		}
		void GenerateNewfOilToGas(double OilInRockPoros,double MExpOil, std::vector<double> &fOilToGasExpOil) //����������ͬ�͵Ķ���ȷ���µ�fOilToGas
		{
			double Ratio01,Ratio02;
			Ratio01=OilInRockPoros/(OilInRockPoros+MExpOil);
			Ratio02=MExpOil/(OilInRockPoros+MExpOil);
			for(int i=0;i<m_NOilToGas;i++)
				//m_fOilToGas[i]=Ratio01*m_fOilToGas[i]+Ratio02*m_fOilToGasBak[i];
			m_fOilToGas[i]=Ratio01*m_fOilToGas[i]+Ratio02*fOilToGasExpOil[i];
		}
		//ͨ�����Ҹ��������͡����������µ��ܵ�ʣ�໯ѧ����ϵ���ֱ���Ը��Ҹ������͵ı��ʺ��������ı���֮����Ӷ��õ���
		//�����ѽ�Ϊ�����
		void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,std::vector<double> &fLLNL,double FFLLNL, std::vector<double> &ELLNL,double &wBIw0)
		{  //�ֱ�����һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma����
			// ƽ�з�Ӧ����N_LLNL����ѧ����ϵ��fLLNL,Ƶ������FFLLNL�����ELLNL,�ܵ�ʣ�໯ѧ����ϵ��wBIw0
			wBIw0=0.;
			//double R=0.001986;//���峣�� ����λ Kcal/(mol*K)
			double R=0.008314472; //���峣�� KJ/(mol*K)
			//������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
			double a,b; // ���Ա仯��ϵ��
			a=(T-TLast)/(t-tLast);b=T-a*t;
			//����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
			int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
			double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
			double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
			double temp=0;
			std::vector<double>wiBIw0i;  //wi/w0i ,�����EasyRo�Ƶ��еĹ�ʽ��8��
			wiBIw0i.resize(N_LLNL);
			for(int i=0;i<N_LLNL;i++)
			{
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					temp+=(-FFLLNL*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
					tt1=tt2;
				}
				wiBIw0i[i]=exp(temp);
				fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //������һʱ��εĻ�ѧ����ϵ��
				wBIw0+=fLLNL[i];  // wBIw0Ϊ�ܵĻ�ѧ����ϵ��ʣ��ֵ
				tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
				temp=0;    //temp���¹���
			}
		}
		void GetfOilToGas()
		{  //������ѽ�Ϊ���Ļ�ѧ����ϵ�������ݴ����в�ͬ��Դ�͵ı��ʼ��㣻
			std::vector<double>tempfOilToGas; tempfOilToGas.resize(m_NOilToGas);
			for(int i=0;i<m_NOilToGas;i++) tempfOilToGas[i]=0;
			for(int j=0;j<m_NFlowInOil;j++)
			{
				if(m_MassFlowInOil[j]>0)  //ֻ��������ͼ���������� ����˼�ʹRatioFlowInOil[j] Ϊ��������Ϊ��ֵʱ��������㣻fOilToGasFlowInOil[j][i]��ֵ�����Ը�ֵΪ���������͵Ļ�ѧ����ϵ��ֵ��
					for(int i=0;i<m_NOilToGas;i++) tempfOilToGas[i]+=m_fOilToGasFlowInOil[j][i]*m_RatioFlowInOil[j];
			}
			for(int i=0;i<m_NOilToGas;i++) tempfOilToGas[i]+=m_fOilToGas[i]*m_RatioCrackAndExpLeftedOil;   //����Ҫ�����ѽ�ʣ���͵Ļ�ѧ����ϵ��
			for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]= tempfOilToGas[i];  //�ܵĻ�ѧ����ϵ�� ������ʱ�䲽���������ѽ��Լ��ų���ʣ�����������͵Ļ���͵��ܵĻ�ѧ����ϵ��
			m_wBIw0OilToGas=1.;//ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ ��������ֵ�ڴ˴���ֵ�����ؽ�Ҫ
		}
		void OilCrackToGas(double TLast, double tLast, double T, double t)
		{    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			//����ΪStrSeg�д��ڵ����ѽ�Ϊ���Ͳ�����Ĺ��̡������ǵ�һ��ʱ�䲽����ʼʱ�����д���ԭʼ�ͣ��������Ϊһ����С��
			m_InitialMassOfOil=1.0e-6;   //ͨ����϶�г�ʼ������Ϊ0,�������һ����С������λ:kg;
			m_InitialMassOfGas=1.0e-7;//ͨ����϶�г�ʼ������Ϊ0 ,�������һ����С������λ:kg;
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
			for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
			FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // �������ѽ�Ϊ��
			m_OilExisted=m_InitialMassOfOil;
			m_GasExisted=m_InitialMassOfGas;
			m_GasCracked=m_OilExisted*m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ����������Ϊ0��OToGasFΪ��ת��Ϊ���ı�����
			m_ResidueCracked=m_OilExisted*(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_CrackLeftedOil=m_OilExisted-m_OilCracked;
			m_GasCrackedAdded=m_GasCracked;//�����ǵ�һ��ʱ�䲽��������ۻ��ѽ������ڳ�ʼ�ѽ�����
			m_ResidueCrackedAdded=m_ResidueCracked;
			m_OilCrackedAdded=m_OilCracked;
			double OilEntered=0;  //�������͵���
			double GasEntered=0;  //������������
			for(int j=0;j<m_NFlowInOil;j++)
			{OilEntered+=m_MassFlowInOil[j]; GasEntered+=m_MassFlowInGas[j]; }
			m_OilExisted=m_OilExisted+OilEntered-m_OilCracked;    //�������ʱ�䲽�������������
			m_GasExisted=m_GasExisted+GasEntered+m_GasCracked;
			for(int j=0;j<m_NFlowInOil;j++) m_RatioFlowInOil[j]=m_MassFlowInOil[j]/m_OilExisted;    //�������������ռ�������ı��� ,������֮��
			m_ExpedOil=0;
			for(int j=0;j<m_NFlowInOil;j++) if(  m_MassFlowInOil[j]<0 ) m_ExpedOil+=m_MassFlowInOil[j];
			m_ExpedOil=fabs(m_ExpedOil);   //�ų�ȥ������
			m_CrackAndExpLeftedOil=m_CrackLeftedOil-m_ExpedOil; //�ѽ���ų���ʣ�������
			m_RatioCrackAndExpLeftedOil=m_CrackAndExpLeftedOil/m_OilExisted; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���
			Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
			GetfOilToGas();
		}
		void OilCrackToGas(double TLast, double tLast, double T, double t,OilInResCracking2C &aOilInResCracking2C)
		{    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
			for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
			FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
			m_OilExisted=aOilInResCracking2C.m_OilExisted ;    //��һʱ�䲽����ʱ�ʹ����������ڱ�ʱ�䲽��ʼʱ���ʹ�����
			m_GasExisted=aOilInResCracking2C.m_GasExisted ;    //��һʱ�䲽����ʱ�������������ڱ�ʱ�䲽��ʼʱ����������
			m_GasCracked=m_OilExisted*m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ����������Ϊ0��OToGasFΪ��ת��Ϊ���ı�����
			m_ResidueCracked=m_OilExisted*(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_CrackLeftedOil=m_OilExisted-m_OilCracked;
			m_GasCrackedAdded=m_GasCracked+aOilInResCracking2C.m_GasCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
			m_ResidueCrackedAdded=m_ResidueCracked+aOilInResCracking2C.m_ResidueCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���;
			m_OilCrackedAdded=m_OilCracked+aOilInResCracking2C.m_OilCrackedAdded;   //��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
			double OilEntered=0;  //�������͵���
			double GasEntered=0;  //������������
			for(int j=0;j<m_NFlowInOil;j++)
			{OilEntered+=m_MassFlowInOil[j]; GasEntered+=m_MassFlowInGas[j]; }
			m_OilExisted=m_OilExisted+OilEntered-m_OilCracked;    //�������ʱ�䲽�������������
			m_GasExisted =m_GasExisted+GasEntered+m_GasCracked;
			for(int j=0;j<m_NFlowInOil;j++) m_RatioFlowInOil[j]=m_MassFlowInOil[j]/m_OilExisted;    //�������������ռ�������ı���
			m_ExpedOil=0;
			for(int j=0;j<m_NFlowInOil;j++) if(  m_MassFlowInOil[j]<0 ) m_ExpedOil+=m_MassFlowInOil[j];
			m_ExpedOil=fabs(m_ExpedOil);   //�ų�ȥ������
			m_CrackAndExpLeftedOil=m_CrackLeftedOil-m_ExpedOil; //�ѽ���ų���ʣ�������
			m_RatioCrackAndExpLeftedOil=m_CrackAndExpLeftedOil/m_OilExisted; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���
			Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
			GetfOilToGas();   // 
		}
		void OilCrackToGasNew(double TLast, double tLast, double T, double t)
		{    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
			for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
			FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
			//OilExisted=aOilInResCracking2C->OilExisted ;    //��һʱ�䲽����ʱ�ʹ����������ڱ�ʱ�䲽��ʼʱ���ʹ�����
			//GasExisted=aOilInResCracking2C->GasExisted ;    //��һʱ�䲽����ʱ�������������ڱ�ʱ�䲽��ʼʱ����������
			//GasCracked=OilExisted*OToGasF*(InitwBIw0OilToGas-wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ����������Ϊ0��OToGasFΪ��ת��Ϊ���ı�����
			m_RatioGasFromOilCracking=m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);
			//ResidueCracked=OilExisted*(1.-OToGasF)*(InitwBIw0OilToGas-wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
			m_RatioResidueFromOilCracking=(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);
			//OilCracked=GasCracked+ResidueCracked;
			m_RatioOilFromOilCracking=(InitwBIw0OilToGas-m_wBIw0OilToGas);
			//CrackLeftedOil=OilExisted-OilCracked;
			//GasCrackedAdded=GasCracked+aOilInResCracking2C->GasCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
			//ResidueCrackedAdded=ResidueCracked+aOilInResCracking2C->ResidueCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���;
			//OilCrackedAdded=OilCracked+aOilInResCracking2C->OilCrackedAdded;   //��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
			//double OilEntered=0;  //�������͵���
			// double GasEntered=0;  //������������
			// for(int j=0;j<NFlowInOil;j++)
			//   {OilEntered+=MassFlowInOil[j]; GasEntered+=MassFlowInGas[j]; }
			// OilExisted=OilExisted+OilEntered-OilCracked;    //�������ʱ�䲽�������������
			// GasExisted =GasExisted+GasEntered+GasCracked;
			// for(int j=0;j<NFlowInOil;j++) RatioFlowInOil[j]=MassFlowInOil[j]/OilExisted;    //�������������ռ�������ı���
			//ExpedOil=0;
			// for(int j=0;j<NFlowInOil;j++) if(  MassFlowInOil[j]<0 ) ExpedOil+=MassFlowInOil[j];
			//ExpedOil=fabs(ExpedOil);   //�ų�ȥ������
			// CrackAndExpLeftedOil=CrackLeftedOil-ExpedOil; //�ѽ���ų���ʣ�������
			//RatioCrackAndExpLeftedOil=CrackAndExpLeftedOil/OilExisted; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���
			Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
			//GetfOilToGas();   //
		}
		void SetToItsOrifOilToGas()
		{  //��fOilToGas�趨Ϊԭʼֵ����Ҫ�����ڳ�ѹ�ز�ָ�ʱ���ж��ѭ���������Ӧ�ã�
			//��ʹ���¸�ѭ��ʱ�����õ� fOilToGas���µģ��������ϸ�ѭ��������¼�Ľ��
			for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]=m_fOilToGasBak[i];
			// ��������һ�£������ֵ�ǶԵģ�֮���Խ���ֵ��������ԭʼ��fOilToGasBak[i]��
			//����Ϊһ�γ�ѹѭ���Ǵ�ͷ��ʼ�ģ���һ����ѭ��������ѭ�����¿�ʼ����ζ�Ŵ���ԭʼ�Ļ�ѧ����������ʼ��
		}
	};
	struct OilInResCracking4C
	{   //����Ϊ����������ֵ��ѽ⣬����Դ���п�϶���͵��ѽ⣻  ���������ģ���龰
		//����Ϊ��Ҫ����Behar et al., 1997 Thermal cracking of kerogen in open and closed systems�������֣������޸���Pepper 1995�л��������еĲ����͹�ʽ ������ѽ������
		int m_NF; //�����������Behar 1997ģ�ͣ��������4
		double m_FFOilToGas; //Frequency factor
		double m_EmeanOilToGas;
		double m_SigmaOilToGas; //�ֱ������ѽ�Ϊ���Ķ���ѧ������������̬�ֲ��ľ��ʺͱ�׼��
		int m_NOilToGas;//���ѽ�Ϊ����ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
		std::vector<double> m_fOilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor�� ��ͨ������̬�ֲ���ɢ���õ�
		std::vector<double> m_fOilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_EOilToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�
		double m_OToGasF; //���ѽ�Ϊ���ı���
		// double OToResidueF; //���ѽ�Ϊ������ı�������� OToResidueF=1-OToGasF
		//   ���������̿�ⲿ�ֲ������г��ˣ��������ѽ�Ϊ���ĸ�����          
		double m_wBIw0OilToGas;// ���ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
		double m_wBIw0K; //���Ҹ� �ܵ�ʣ�໯ѧ����ϵ����ԭʼΪ1��ͨ�����Ҹ��������͡����������µ��ܵ�ʣ�໯ѧ����ϵ���ֱ���Ը��Ҹ������͵ı��ʺ��������ı���֮����Ӷ��õ���
		//���������ѽ��йصĶ��Ƕ�Ӧ���������г�ʼ������
		double m_C1Existed;
		double m_C2_C5Existed;
		double m_C6_C14Existed;
		double m_C15PlusExisted;   //ָ���Ǵ����ڿ�϶�еĸ����
		double m_OilExisted; //ָ���Ǵ����ڴ����У�����Դ�ҿ�϶�У��������
		double m_GasExisted; //ָ���Ǵ����ڴ����У�����Դ�ҿ�϶�У��������
		double m_ResidueExisted; //ָ�����ڴ����У�����Դ�ҿ�϶�У������ѽ�Ϊ��������
		double m_C1Cracked;
		double m_C2_C5Cracked; // ָ���Ǵ����ڴ����У�����Դ�ҿ�϶�У�ÿһ�����ѽ��C1�Լ�C2_C5����
		double m_GasCracked;//ָ�����ڴ����У�����Դ�ҿ�϶�У����͵�ÿһ���ѽ������
		double m_C1CrackedAdded;
		double m_C2_C5CrackedAdded; // ָ����ÿһ�����ѽ��C1�Լ�C2_C5����
		double m_GasCrackedAdded; //ָÿһ���ѽ������ۼ���
		double m_ResidueCracked; // ָ����ÿһ�����ѽ�Ĳ�������
		double m_ResidueCrackedAdded; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
		double m_C6_C14Cracked;
		double m_C15PlusCracked;
		double m_OilCracked;//ÿһ���͵��ѽ���
		double m_C6_C14CrackedAdded;
		double m_C15PlusCrackedAdded;
		double m_OilCrackedAdded;//ÿһ���͵��ѽ������ۼ���

		int m_NFlowInOil; //�������������͵�������
		std::vector<double> m_MassFlowInOil; //������������͵���������Ȼ����������������ͣ�����Ϊ��������Ϊ����
		std::vector<double> m_MassFlowInC6_C14;
		std::vector<double> m_MassFlowInC15Plus;
		std::vector<double> m_MassFlowInGas; //�����������������������Ȼ�����������������������Ϊ��������Ϊ����
		std::vector<double> m_MassFlowInC1;
		std::vector<double> m_MassFlowInC2_C5;
		std::vector<double> m_RatioFlowInOil; //���������и����͵ı��� �������������������ı�ֵ
		std::vector<std::vector<double> > m_fOilToGasFlowInOil; //������͵Ļ�ѧ����ϵ��  ����Щ��ѧ����ϵ����Ϊ����������������һʱ�̵Ļ�ѧ����ϵ��
		double m_InitialMassOfOil;   //��ʼʱ�̵���������
		double m_InitialMassOfGas;   //��ʼʱ�̵���������
		double m_CrackLeftedOil;//�ѽ��ʣ�������
		double m_ExpedOil; //�ų�ȥ������
		double m_CrackAndExpLeftedOil; //�ѽ���ų���ʣ�������
		double m_RatioCrackAndExpLeftedOil; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���

		double m_RatioCrackedC1; // ���ѽ�Ϊ����C1�ı���
		double m_RatioCrackedC6_C14; //���ѽ���C6_C14�ı��� ,ʵ����û���õ��˲�����ʵ���ѽ����������������ռ�ı���
		double m_RatioC6_C14ToInitialMassOfOil; //��϶�г�ʼ���� C6_C14�ı���
		double m_RatioC1ToInitialMassOfGas; //��϶�г�ʼ���� C1�ı���
		double m_RatioGasFromOilCracking;   //��λ�������ѽ�Ϊ������
		double m_RatioResidueFromOilCracking;  //��λ�������ѽ�Ϊ���������
		double m_RatioOilFromOilCracking;  //�����ѽ�ı���

		OilInResCracking4C()
		{
			m_NF=4;
			m_OToGasF=0.5; //���ѽ�Ϊ���ı���
			m_FFOilToGas=1.0e14; m_EmeanOilToGas=246.628*0.2389; m_SigmaOilToGas=6.248*0.2389;     //�����ʼ���ѽ� �Ļ�ѧ����ѧ������Դ��Pepper,1995��P327 (5)��(6)��HI=1176ʱ�õ� ;����0.2389��KJ/molת��ΪKCal/mol
			m_NOilToGas=21; //��������̫�ֲ��ֳ�21�����䣬��������ֵλ����һ�����䣬�������߶ԳƵطֱ�ֲ���10���� �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma ��������0.9974�ĸ������䣩
			m_fOilToGas.resize(m_NOilToGas); m_EOilToGas.resize(m_NOilToGas);
			GetEachfAndE(m_NOilToGas, m_EmeanOilToGas,m_SigmaOilToGas,m_fOilToGas,m_EOilToGas);Normalization(m_NOilToGas,m_fOilToGas);
			m_fOilToGasBak.resize(m_NOilToGas); for(int i=0;i<m_NOilToGas;i++) m_fOilToGasBak[i]=m_fOilToGas[i];    
		}
		OilInResCracking4C(const OilInResCracking4C &other)
		{
			*this = other;
		}
		const OilInResCracking4C &operator=(const OilInResCracking4C &other)
		{  
			if(this == &other)
			{
				return *this;
			}
			m_NF = other.m_NF;
			m_FFOilToGas = other.m_FFOilToGas;
			m_EmeanOilToGas = other.m_EmeanOilToGas;
			m_SigmaOilToGas = other.m_SigmaOilToGas;
			m_NOilToGas = other.m_NOilToGas;
			m_fOilToGas = other.m_fOilToGas;
			m_fOilToGasBak = other.m_fOilToGasBak;
			m_EOilToGas = other.m_EOilToGas;
			m_OToGasF = other.m_OToGasF; 
			m_wBIw0OilToGas = other.m_wBIw0OilToGas;
			m_wBIw0K = other.m_wBIw0K;
			m_C1Existed = other.m_C1Existed;
			m_C2_C5Existed = other.m_C2_C5Existed;
			m_C6_C14Existed = other.m_C6_C14Existed;
			m_C15PlusExisted = other.m_C15PlusExisted;   
			m_OilExisted = other.m_OilExisted; 
			m_GasExisted = other.m_GasExisted;
			m_ResidueExisted = other.m_ResidueExisted; 
			m_C1Cracked = other.m_C1Cracked;
			m_C2_C5Cracked = other.m_C2_C5Cracked; 
			m_GasCracked = other.m_GasCracked;
			m_C1CrackedAdded = other.m_C1CrackedAdded;
			m_C2_C5CrackedAdded = other.m_C2_C5CrackedAdded; 
			m_GasCrackedAdded = other.m_GasCrackedAdded;
			m_ResidueCracked = other.m_ResidueCracked; 
			m_ResidueCrackedAdded = other.m_ResidueCrackedAdded; 
			m_C6_C14Cracked = other.m_C6_C14Cracked;
			m_C15PlusCracked = other.m_C15PlusCracked;
			m_OilCracked = other.m_OilCracked;
			m_C6_C14CrackedAdded = other.m_C6_C14CrackedAdded;
			m_C15PlusCrackedAdded = other.m_C15PlusCrackedAdded;
			m_OilCrackedAdded = other.m_OilCrackedAdded;
			m_NFlowInOil = other.m_NFlowInOil;
			m_MassFlowInOil = other.m_MassFlowInOil; 
			m_MassFlowInC6_C14 = other.m_MassFlowInC6_C14;
			m_MassFlowInC15Plus = other.m_MassFlowInC15Plus;
			m_MassFlowInGas = other.m_MassFlowInGas; 
			m_MassFlowInC1 = other.m_MassFlowInC1;
			m_MassFlowInC2_C5 = other.m_MassFlowInC2_C5;
			m_RatioFlowInOil = other.m_RatioFlowInOil; 
			m_fOilToGasFlowInOil = other.m_fOilToGasFlowInOil; 
			m_InitialMassOfOil = other.m_InitialMassOfOil;   
			m_InitialMassOfGas = other.m_InitialMassOfGas;  
			m_CrackLeftedOil = other.m_CrackLeftedOil;
			m_ExpedOil = other.m_ExpedOil; 
			m_CrackAndExpLeftedOil = other.m_CrackAndExpLeftedOil; 
			m_RatioCrackAndExpLeftedOil = other.m_RatioCrackAndExpLeftedOil;
			m_RatioCrackedC1 = other.m_RatioCrackedC1; 
			m_RatioCrackedC6_C14 = other.m_RatioCrackedC6_C14; 
			m_RatioC6_C14ToInitialMassOfOil = other.m_RatioC6_C14ToInitialMassOfOil;
			m_RatioC1ToInitialMassOfGas = other.m_RatioC1ToInitialMassOfGas; 
			m_RatioGasFromOilCracking = other.m_RatioGasFromOilCracking; 
			m_RatioResidueFromOilCracking = other.m_RatioResidueFromOilCracking; 
			m_RatioOilFromOilCracking = other.m_RatioOilFromOilCracking; 
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(int);//int m_NF;
			curSize += sizeof(double);//double m_FFOilToGas;
			curSize += sizeof(double);//double m_EmeanOilToGas;
			curSize += sizeof(double);//double m_SigmaOilToGas;
			curSize += sizeof(int);//int m_NOilToGas;
			curSize += (sizeof(int) + m_fOilToGas.size() * sizeof(double));//std::vector<double> m_fOilToGas;
			curSize += (sizeof(int) + m_fOilToGasBak.size() * sizeof(double));//std::vector<double> m_fOilToGasBak;
			curSize += (sizeof(int) + m_EOilToGas.size() * sizeof(double));//std::vector<double> m_EOilToGas;
			curSize += sizeof(double);//double m_OToGasF; 
			curSize += sizeof(double);//double m_wBIw0OilToGas;
			curSize += sizeof(double);//double m_wBIw0K;
			curSize += sizeof(double);//double m_C1Existed;
			curSize += sizeof(double);//double m_C2_C5Existed;
			curSize += sizeof(double);//double m_C6_C14Existed;
			curSize += sizeof(double);//double m_C15PlusExisted;   
			curSize += sizeof(double);//double m_OilExisted; 
			curSize += sizeof(double);//double m_GasExisted;
			curSize += sizeof(double);//double m_ResidueExisted; 
			curSize += sizeof(double);//double m_C1Cracked;
			curSize += sizeof(double);//double m_C2_C5Cracked; 
			curSize += sizeof(double);//double m_GasCracked;
			curSize += sizeof(double);//double m_C1CrackedAdded;
			curSize += sizeof(double);//double m_C2_C5CrackedAdded; 
			curSize += sizeof(double);//double m_GasCrackedAdded;
			curSize += sizeof(double);//double m_ResidueCracked; 
			curSize += sizeof(double);//double m_ResidueCrackedAdded; 
			curSize += sizeof(double);//double m_C6_C14Cracked;
			curSize += sizeof(double);//double m_C15PlusCracked;
			curSize += sizeof(double);//double m_OilCracked;
			curSize += sizeof(double);//double m_C6_C14CrackedAdded;
			curSize += sizeof(double);//double m_C15PlusCrackedAdded;
			curSize += sizeof(double);//double m_OilCrackedAdded;
			curSize += sizeof(int);//int m_NFlowInOil;
			curSize += (sizeof(int) + m_MassFlowInOil.size() * sizeof(double));//std::vector<double> m_MassFlowInOil; 
			curSize += (sizeof(int) + m_MassFlowInC6_C14.size() * sizeof(double));//std::vector<double> m_MassFlowInC6_C14;
			curSize += (sizeof(int) + m_MassFlowInC15Plus.size() * sizeof(double));//std::vector<double> m_MassFlowInC15Plus;
			curSize += (sizeof(int) + m_MassFlowInGas.size() * sizeof(double));//std::vector<double> m_MassFlowInGas; 
			curSize += (sizeof(int) + m_MassFlowInC1.size() * sizeof(double));//std::vector<double> m_MassFlowInC1;
			curSize += (sizeof(int) + m_MassFlowInC2_C5.size() * sizeof(double));//std::vector<double> m_MassFlowInC2_C5;
			curSize += (sizeof(int) + m_RatioFlowInOil.size() * sizeof(double));//std::vector<double> m_RatioFlowInOil; 
			curSize += sizeof(int);//std::vector<std::vector<double> > m_fOilToGasFlowInOil;
			for(int i = 0; i < m_fOilToGasFlowInOil.size(); i++)
			{
				curSize += (sizeof(int) + m_fOilToGasFlowInOil[i].size() * sizeof(double));
			}
			curSize += sizeof(double);//double m_InitialMassOfOil;   
			curSize += sizeof(double);//double m_InitialMassOfGas;  
			curSize += sizeof(double);//double m_CrackLeftedOil;
			curSize += sizeof(double);//double m_ExpedOil; 
			curSize += sizeof(double);//double m_CrackAndExpLeftedOil; 
			curSize += sizeof(double);//double m_RatioCrackAndExpLeftedOil;
			curSize += sizeof(double);//double m_RatioCrackedC1; 
			curSize += sizeof(double);//double m_RatioCrackedC6_C14; 
			curSize += sizeof(double);//double m_RatioC6_C14ToInitialMassOfOil;
			curSize += sizeof(double);//double m_RatioC1ToInitialMassOfGas; 
			curSize += sizeof(double);//double m_RatioGasFromOilCracking; 
			curSize += sizeof(double);//double m_RatioResidueFromOilCracking; 
			curSize += sizeof(double);//double m_RatioOilFromOilCracking; 
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_NF, sizeof(int));data += sizeof(int);
			memcpy(data, &m_FFOilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_EmeanOilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_SigmaOilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_NOilToGas, sizeof(int));data += sizeof(int);
			int fOilToGassize = m_fOilToGas.size();
			memcpy(data, &fOilToGassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fOilToGassize; i++)
			{
				memcpy(data, &(m_fOilToGas[i]), sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize = m_fOilToGasBak.size();
			memcpy(data, &fOilToGasBaksize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fOilToGasBaksize; i++)
			{
				memcpy(data, &(m_fOilToGasBak[i]), sizeof(double));data += sizeof(double);
			}
			int EOilToGassize = m_EOilToGas.size();
			memcpy(data, &EOilToGassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < EOilToGassize; i++)
			{
				memcpy(data, &(m_EOilToGas[i]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &m_OToGasF, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_wBIw0OilToGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_wBIw0K, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C1Existed, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C2_C5Existed, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C6_C14Existed, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C15PlusExisted, sizeof(double));data += sizeof(double);   
			memcpy(data, &m_OilExisted, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasExisted, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ResidueExisted, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C1Cracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C2_C5Cracked, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasCracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C1CrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C2_C5CrackedAdded, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ResidueCracked, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_ResidueCrackedAdded, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C6_C14Cracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C15PlusCracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilCracked, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C6_C14CrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C15PlusCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_NFlowInOil, sizeof(int));data += sizeof(int);
			int MassFlowInOilsize = m_MassFlowInOil.size();
			memcpy(data, &MassFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInOilsize; i++)
			{
				memcpy(data, &(m_MassFlowInOil[i]), sizeof(double));data += sizeof(double);
			}
			int MassFlowInC6_C14size = m_MassFlowInC6_C14.size();
			memcpy(data, &MassFlowInC6_C14size, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInC6_C14size; i++)
			{
				memcpy(data, &(m_MassFlowInC6_C14[i]), sizeof(double));data += sizeof(double);
			}
			int MassFlowInC15Plussize = m_MassFlowInC15Plus.size();
			memcpy(data, &MassFlowInC15Plussize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInC15Plussize; i++)
			{
				memcpy(data, &(m_MassFlowInC15Plus[i]), sizeof(double));data += sizeof(double);
			}
			int MassFlowInGassize = m_MassFlowInGas.size();
			memcpy(data, &MassFlowInGassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInGassize; i++)
			{
				memcpy(data, &(m_MassFlowInGas[i]), sizeof(double));data += sizeof(double);
			}
			int MassFlowInC1size = m_MassFlowInC1.size();
			memcpy(data, &MassFlowInC1size, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInC1size; i++)
			{
				memcpy(data, &(m_MassFlowInC1[i]), sizeof(double));data += sizeof(double);
			}
			int MassFlowInC2_C5size = m_MassFlowInC2_C5.size();
			memcpy(data, &MassFlowInC2_C5size, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInC2_C5size; i++)
			{
				memcpy(data, &(m_MassFlowInC2_C5[i]), sizeof(double));data += sizeof(double);
			}
			int RatioFlowInOilsize = m_RatioFlowInOil.size();
			memcpy(data, &RatioFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < RatioFlowInOilsize; i++)
			{
				memcpy(data, &(m_RatioFlowInOil[i]), sizeof(double));data += sizeof(double);
			}
			int fOilToGasFlowInOilsize = m_fOilToGasFlowInOil.size();
			memcpy(data, &fOilToGasFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fOilToGasFlowInOilsize; i++)
			{
				int fOilToGasFlowInOilisize = m_fOilToGasFlowInOil[i].size();
				memcpy(data, &fOilToGasFlowInOilisize, sizeof(int));data += sizeof(int);
				for(int j = 0; j < fOilToGasFlowInOilisize; j++)
				{
					memcpy(data, &(m_fOilToGasFlowInOil[i][j]), sizeof(double));data += sizeof(double);
				}
			}
			memcpy(data, &m_InitialMassOfOil, sizeof(double));data += sizeof(double);   
			memcpy(data, &m_InitialMassOfGas, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_CrackLeftedOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ExpedOil, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_CrackAndExpLeftedOil, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioCrackAndExpLeftedOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_RatioCrackedC1, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioCrackedC6_C14, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioC6_C14ToInitialMassOfOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_RatioC1ToInitialMassOfGas, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioGasFromOilCracking, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioResidueFromOilCracking, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioOilFromOilCracking, sizeof(double));data += sizeof(double); 
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_NF, data, sizeof(int));data += sizeof(int);
			memcpy(&m_FFOilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_EmeanOilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_SigmaOilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_NOilToGas, data, sizeof(int));data += sizeof(int);
			int fOilToGassize;
			memcpy(&fOilToGassize, data, sizeof(int));data += sizeof(int);
			m_fOilToGas.resize(fOilToGassize);
			for(int i = 0; i < fOilToGassize; i++)
			{
				memcpy(&(m_fOilToGas[i]), data, sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize;
			memcpy(&fOilToGasBaksize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasBak.resize(fOilToGasBaksize);
			for(int i = 0; i < fOilToGasBaksize; i++)
			{
				memcpy(&(m_fOilToGasBak[i]), data, sizeof(double));data += sizeof(double);
			}
			int EOilToGassize;
			memcpy(&EOilToGassize, data, sizeof(int));data += sizeof(int);
			m_EOilToGas.resize(EOilToGassize);
			for(int i = 0; i < EOilToGassize; i++)
			{
				memcpy(&(m_EOilToGas[i]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&m_OToGasF, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_wBIw0OilToGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_wBIw0K, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C1Existed, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C2_C5Existed, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C6_C14Existed, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C15PlusExisted, data, sizeof(double));data += sizeof(double);   
			memcpy(&m_OilExisted, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasExisted, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ResidueExisted, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C1Cracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C2_C5Cracked, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasCracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C1CrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C2_C5CrackedAdded, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ResidueCracked, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_ResidueCrackedAdded, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C6_C14Cracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C15PlusCracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilCracked, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C6_C14CrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C15PlusCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_NFlowInOil, data, sizeof(int));data += sizeof(int);
			int MassFlowInOilsize;
			memcpy(&MassFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_MassFlowInOil.resize(MassFlowInOilsize);
			for(int i = 0; i < MassFlowInOilsize; i++)
			{
				memcpy(&(m_MassFlowInOil[i]), data, sizeof(double));data += sizeof(double);
			}
			int MassFlowInC6_C14size;
			memcpy(&MassFlowInC6_C14size, data, sizeof(int));data += sizeof(int);
			m_MassFlowInC6_C14.resize(MassFlowInC6_C14size);
			for(int i = 0; i < MassFlowInC6_C14size; i++)
			{
				memcpy(&(m_MassFlowInC6_C14[i]), data, sizeof(double));data += sizeof(double);
			}
			int MassFlowInC15Plussize;
			memcpy(&MassFlowInC15Plussize, data, sizeof(int));data += sizeof(int);
			m_MassFlowInC15Plus.resize(MassFlowInC15Plussize);
			for(int i = 0; i < MassFlowInC15Plussize; i++)
			{
				memcpy(&(m_MassFlowInC15Plus[i]), data, sizeof(double));data += sizeof(double);
			}
			int MassFlowInGassize;
			memcpy(&MassFlowInGassize, data, sizeof(int));data += sizeof(int);
			m_MassFlowInGas.resize(MassFlowInGassize);
			for(int i = 0; i < MassFlowInGassize; i++)
			{
				memcpy(&(m_MassFlowInGas[i]), data, sizeof(double));data += sizeof(double);
			}
			int MassFlowInC1size;
			memcpy(&MassFlowInC1size, data, sizeof(int));data += sizeof(int);
			m_MassFlowInC1.resize(MassFlowInC1size);
			for(int i = 0; i < MassFlowInC1size; i++)
			{
				memcpy(&(m_MassFlowInC1[i]), data, sizeof(double));data += sizeof(double);
			}
			int MassFlowInC2_C5size;
			memcpy(&MassFlowInC2_C5size, data, sizeof(int));data += sizeof(int);
			m_MassFlowInC2_C5.resize(MassFlowInC2_C5size);
			for(int i = 0; i < MassFlowInC2_C5size; i++)
			{
				memcpy(&(m_MassFlowInC2_C5[i]), data, sizeof(double));data += sizeof(double);
			}
			int RatioFlowInOilsize;
			memcpy(&RatioFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_RatioFlowInOil.resize(RatioFlowInOilsize);
			for(int i = 0; i < RatioFlowInOilsize; i++)
			{
				memcpy(&(m_RatioFlowInOil[i]), data, sizeof(double));data += sizeof(double);
			}
			int fOilToGasFlowInOilsize;
			memcpy(&fOilToGasFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasFlowInOil.resize(fOilToGasFlowInOilsize);
			for(int i = 0; i < fOilToGasFlowInOilsize; i++)
			{
				int fOilToGasFlowInOilisize;
				memcpy(&fOilToGasFlowInOilisize, data, sizeof(int));data += sizeof(int);
				m_fOilToGasFlowInOil[i].resize(fOilToGasFlowInOilisize);
				for(int j = 0; j < fOilToGasFlowInOilisize; j++)
				{
					memcpy(&(m_fOilToGasFlowInOil[i][j]), data, sizeof(double));data += sizeof(double);
				}
			}
			memcpy(&m_InitialMassOfOil, data, sizeof(double));data += sizeof(double);   
			memcpy(&m_InitialMassOfGas, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_CrackLeftedOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ExpedOil, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_CrackAndExpLeftedOil, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioCrackAndExpLeftedOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_RatioCrackedC1, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioCrackedC6_C14, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioC6_C14ToInitialMassOfOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_RatioC1ToInitialMassOfGas, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioGasFromOilCracking, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioResidueFromOilCracking, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioOilFromOilCracking, data, sizeof(double));data += sizeof(double); 
		}
		friend std::ofstream &operator << (std::ofstream &os, OilInResCracking4C &oilinrescracking4c)
		{
			os << "\r\n>>>>>>>>>>>>>>>OilInResCracking4C parameter as flow:";
			os << "\r\n---- ---- ---- NF:" << oilinrescracking4c.m_NF;
			os << "\r\n---- ---- ---- FFOilToGas:" << oilinrescracking4c.m_FFOilToGas;
			os << "\r\n---- ---- ---- EmeanOilToGas:" << oilinrescracking4c.m_EmeanOilToGas;
			os << "\r\n---- ---- ---- SigmaOilToGas:" << oilinrescracking4c.m_SigmaOilToGas;
			os << "\r\n---- ---- ---- NOilToGas:" << oilinrescracking4c.m_NOilToGas;
			for(int i = 0; i < oilinrescracking4c.m_fOilToGas.size(); i++)
			{
				os << "\r\n---- ---- ---- m_fOilToGas:" << i << ":" << oilinrescracking4c.m_fOilToGas[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_fOilToGasBak.size(); i++)
			{
				os << "\r\n---- ---- ---- m_fOilToGasBak:" << i << ":" << oilinrescracking4c.m_fOilToGasBak[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_EOilToGas.size(); i++)
			{
				os << "\r\n---- ---- ---- m_EOilToGas:" << i << ":" << oilinrescracking4c.m_EOilToGas[i];
			}
			os << "\r\n---- ---- ---- OToGasF:" << oilinrescracking4c.m_OToGasF; 
			os << "\r\n---- ---- ---- wBIw0OilToGas:" << oilinrescracking4c.m_wBIw0OilToGas;
			os << "\r\n---- ---- ---- wBIw0K:" << oilinrescracking4c.m_wBIw0K;
			os << "\r\n---- ---- ---- C1Existed:" << oilinrescracking4c.m_C1Existed;
			os << "\r\n---- ---- ---- C2_C5Existed:" << oilinrescracking4c.m_C2_C5Existed;
			os << "\r\n---- ---- ---- C6_C14Existed:" << oilinrescracking4c.m_C6_C14Existed;
			os << "\r\n---- ---- ---- C15PlusExisted:" << oilinrescracking4c.m_C15PlusExisted;   
			os << "\r\n---- ---- ---- OilExisted:" << oilinrescracking4c.m_OilExisted; 
			os << "\r\n---- ---- ---- GasExisted:" << oilinrescracking4c.m_GasExisted;
			os << "\r\n---- ---- ---- ResidueExisted:" << oilinrescracking4c.m_ResidueExisted; 
			os << "\r\n---- ---- ---- C1Cracked:" << oilinrescracking4c.m_C1Cracked;
			os << "\r\n---- ---- ---- C2_C5Cracked:" << oilinrescracking4c.m_C2_C5Cracked; 
			os << "\r\n---- ---- ---- GasCracked:" << oilinrescracking4c.m_GasCracked;
			os << "\r\n---- ---- ---- C1CrackedAdded:" << oilinrescracking4c.m_C1CrackedAdded;
			os << "\r\n---- ---- ---- C2_C5CrackedAdded:" << oilinrescracking4c.m_C2_C5CrackedAdded; 
			os << "\r\n---- ---- ---- GasCrackedAdded:" << oilinrescracking4c.m_GasCrackedAdded;
			os << "\r\n---- ---- ---- ResidueCracked:" << oilinrescracking4c.m_ResidueCracked; 
			os << "\r\n---- ---- ---- ResidueCrackedAdded:" << oilinrescracking4c.m_ResidueCrackedAdded; 
			os << "\r\n---- ---- ---- C6_C14Cracked:" << oilinrescracking4c.m_C6_C14Cracked;
			os << "\r\n---- ---- ---- C15PlusCracked:" << oilinrescracking4c.m_C15PlusCracked;
			os << "\r\n---- ---- ---- OilCracked:" << oilinrescracking4c.m_OilCracked;
			os << "\r\n---- ---- ---- C6_C14CrackedAdded:" << oilinrescracking4c.m_C6_C14CrackedAdded;
			os << "\r\n---- ---- ---- C15PlusCrackedAdded:" << oilinrescracking4c.m_C15PlusCrackedAdded;
			os << "\r\n---- ---- ---- OilCrackedAdded:" << oilinrescracking4c.m_OilCrackedAdded;
			os << "\r\n---- ---- ---- NFlowInOil:" << oilinrescracking4c.m_NFlowInOil;
			for(int i = 0; i < oilinrescracking4c.m_MassFlowInOil.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInOil:" << i << ":" << oilinrescracking4c.m_MassFlowInOil[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_MassFlowInC6_C14.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInC6_C14:" << i << ":" << oilinrescracking4c.m_MassFlowInC6_C14[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_MassFlowInC15Plus.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInC15Plus:" << i << ":" << oilinrescracking4c.m_MassFlowInC15Plus[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_MassFlowInGas.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInGas:" << i << ":" << oilinrescracking4c.m_MassFlowInGas[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_MassFlowInC1.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInC1:" << i << ":" << oilinrescracking4c.m_MassFlowInC1[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_MassFlowInC2_C5.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInC2_C5:" << i << ":" << oilinrescracking4c.m_MassFlowInC2_C5[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_RatioFlowInOil.size(); i++)
			{
				os << "\r\n---- ---- ---- m_RatioFlowInOil:" << i << ":" << oilinrescracking4c.m_RatioFlowInOil[i];
			}
			for(int i = 0; i < oilinrescracking4c.m_fOilToGasFlowInOil.size(); i++)
			{
				for(int j = 0; j < oilinrescracking4c.m_fOilToGasFlowInOil[i].size(); j++)
				{
					os << "\r\n---- ---- ---- m_fOilToGasFlowInOil:" << i << ":" << j << ":" << oilinrescracking4c.m_fOilToGasFlowInOil[i][j];
				}
			}
			os << "\r\n---- ---- ---- InitialMassOfOil:" << oilinrescracking4c.m_InitialMassOfOil;   
			os << "\r\n---- ---- ---- InitialMassOfGas:" << oilinrescracking4c.m_InitialMassOfGas;  
			os << "\r\n---- ---- ---- CrackLeftedOil:" << oilinrescracking4c.m_CrackLeftedOil;
			os << "\r\n---- ---- ---- ExpedOil:" << oilinrescracking4c.m_ExpedOil; 
			os << "\r\n---- ---- ---- CrackAndExpLeftedOil:" << oilinrescracking4c.m_CrackAndExpLeftedOil; 
			os << "\r\n---- ---- ---- RatioCrackAndExpLeftedOil:" << oilinrescracking4c.m_RatioCrackAndExpLeftedOil;
			os << "\r\n---- ---- ---- RatioCrackedC1:" << oilinrescracking4c.m_RatioCrackedC1; 
			os << "\r\n---- ---- ---- RatioCrackedC6_C14:" << oilinrescracking4c.m_RatioCrackedC6_C14; 
			os << "\r\n---- ---- ---- RatioC6_C14ToInitialMassOfOil:" << oilinrescracking4c.m_RatioC6_C14ToInitialMassOfOil;
			os << "\r\n---- ---- ---- RatioC1ToInitialMassOfGas:" << oilinrescracking4c.m_RatioC1ToInitialMassOfGas; 
			os << "\r\n---- ---- ---- RatioGasFromOilCracking:" << oilinrescracking4c.m_RatioGasFromOilCracking; 
			os << "\r\n---- ---- ---- RatioResidueFromOilCracking:" << oilinrescracking4c.m_RatioResidueFromOilCracking; 
			os << "\r\n---- ---- ---- RatioOilFromOilCracking:" << oilinrescracking4c.m_RatioOilFromOilCracking; 
			return os;
		}
		double Jiecheng(int n) //n�Ľ׳�
		{double temp=1; for(int i=0;i<n;i++) temp=temp*double(i+1); return temp; }
		double erf(double x)
		{  //����
			int N=30; //����ľ������
			double pi=3.1415926535;  double temp=0;
			for(int i=0;i<N+1;i++) temp+=pow((double)-1,(double)i)*pow(x,2*i+1)/(2*i+1)/Jiecheng(i);
			temp=temp*2/sqrt(pi);
			return temp;
		}
		double Pnormal(double q,double Emean,double Sigma)
		{//��̬�ֲ��ۻ����ʺ���ֵ����q������ Emean��4*Sigma�ķ�Χ�ڶ�����
			double temp=(q-Emean)/Sigma/sqrt(2.);
			return 0.5+0.5*erf(temp);
		}
		void GetEachfAndE(int N, double aE,double aSigma,std::vector<double> &f,std::vector<double> &E)
		{ //���ݻ��������������̬�ֲ��ľ��ʺͱ�׼������ɢ�Ļ�ܺͶ�Ӧ�Ļ�ѧ����ϵ��
			double LeftPoint, RightPoint; //���Ҷϵ��ֵ �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma
			double Delta; //N�������ÿ������ľ��롪��ƽ����������
			LeftPoint=aE-3.*aSigma; RightPoint=aE+3.*aSigma;
			Delta=6.*aSigma/double(N);
			for(int i=0;i<N;i++)
			{
				if(i==0)
				{    //��������丳ֵ
					E[i]=LeftPoint+0.5*Delta;//ȡ�����е�ֵ
					f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma); //��������ĸ���ֵȡֵΪ�������Ҷ�ֵ����˰����˸�����ֵ������������еĸ���ֵ
				}
				if(i>0&&i<N-1)
				{   //�м�����丳ֵ
					E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
					f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);
				}
				if(i==N-1)
				{  //���ұ����丳ֵ
					E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
					f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);   //��������ĸ���ֵȡֵΪ������ֵ�������ұ����еĸ���ֵ
				}
			}
		}
		void Normalization(int N,std::vector<double> &f)
		{   //��ֵ��һ��
			double Sum=0.;
			for(int i=0;i<N;i++) Sum+=f[i];
			for(int i=0;i<N;i++) f[i]=f[i]/Sum;
		}
		void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,std::vector<double> &fLLNL,double FFLLNL, std::vector<double> &ELLNL,double &wBIw0)
		{  //�ֱ�����һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma����
			// ƽ�з�Ӧ����N_LLNL����ѧ����ϵ��fLLNL,Ƶ������FFLLNL�����ELLNL,�ܵ�ʣ�໯ѧ����ϵ��wBIw0
			wBIw0=0.;
			double R=0.001986;//���峣�� ����λ Kcal/(mol*K)   ,���ڴ���Ļ�ܵ�λ��KCal/mol�����������������
			//double R=0.008314472; //���峣�� KJ/(mol*K)
			//������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
			double a,b; // ���Ա仯��ϵ��
			a=(T-TLast)/(t-tLast);b=T-a*t;
			//����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
			int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
			double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
			double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
			double temp=0;
			std::vector<double>wiBIw0i;  //wi/w0i ,�����EasyRo�Ƶ��еĹ�ʽ��8��
			wiBIw0i.resize(N_LLNL);
			for(int i=0;i<N_LLNL;i++)
			{
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					temp+=(-FFLLNL*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
					tt1=tt2;
				}
				wiBIw0i[i]=exp(temp);
				fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //������һʱ��εĻ�ѧ����ϵ��
				wBIw0+=fLLNL[i];  // wBIw0Ϊ�ܵĻ�ѧ����ϵ��ʣ��ֵ
				tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
				temp=0;    //temp���¹���
			}
		}
		void GetfOilToGas()
		{  //������ѽ�Ϊ���Ļ�ѧ����ϵ�������ݴ����в�ͬ��Դ�͵ı��ʼ��㣻
			std::vector<double>tempfOilToGas; tempfOilToGas.resize(m_NOilToGas);
			for(int i=0;i<m_NOilToGas;i++) tempfOilToGas[i]=0;
			for(int j=0;j<m_NFlowInOil;j++)
			{
				if(m_MassFlowInOil[j]>0)  //ֻ��������ͼ���������� ����˼�ʹRatioFlowInOil[j] Ϊ��������Ϊ��ֵʱ��������㣻fOilToGasFlowInOil[j][i]��ֵ�����Ը�ֵΪ���������͵Ļ�ѧ����ϵ��ֵ��
					for(int i=0;i<m_NOilToGas;i++) tempfOilToGas[i]+=m_fOilToGasFlowInOil[j][i]*m_RatioFlowInOil[j];
			}
			for(int i=0;i<m_NOilToGas;i++) tempfOilToGas[i]+=m_fOilToGas[i]*m_RatioCrackAndExpLeftedOil;   //����Ҫ�����ѽ�ʣ���͵Ļ�ѧ����ϵ��
			for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]= tempfOilToGas[i];  //�ܵĻ�ѧ����ϵ�� ������ʱ�䲽���������ѽ��Լ��ų���ʣ�����������͵Ļ���͵��ܵĻ�ѧ����ϵ��
			m_wBIw0OilToGas=1.;//ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ ��������ֵ�ڴ˴���ֵ�����ؽ�Ҫ
		}
		void OilCrackToGas(double TLast, double tLast, double T, double t)
		{    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			//����ΪStrSeg�д��ڵ����ѽ�Ϊ���Ͳ�����Ĺ��̡������ǵ�һ��ʱ�䲽����ʼʱ�����д���ԭʼ�ͣ��������Ϊһ����С��
			//���ڶ���ֵ����ѽ�Ϊ������ʱ�Բ����л�����Դ�����ѽⷽ����ֻ������һ�����������ѽ�������������ѽ�����C1����ռ70%
			m_InitialMassOfOil=1.0e-6;   //��һ����С������λ:kg
			m_InitialMassOfGas=1.0e-7;   //��һ����С������λ:kg
			m_RatioC6_C14ToInitialMassOfOil=0.2;   //����һ�������ֵ
			m_RatioC1ToInitialMassOfGas=0.6;  //����һ�������ֵ
			m_RatioCrackedC1=0.7;  //��ʱ�����ѽ�Ϊ����C1�ı���Ϊ0.7�� �������������ڿ��Ը��ݽ�һ�������ϵ���
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
			for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
			FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���Ҹ�������ѽ�Ϊ��
			m_OilExisted=m_InitialMassOfOil;
			m_C6_C14Existed=m_RatioC6_C14ToInitialMassOfOil*m_OilExisted;
			m_C15PlusExisted=(1.-m_RatioC6_C14ToInitialMassOfOil)*m_OilExisted;
			m_GasExisted=m_InitialMassOfGas;
			m_C1Existed=m_RatioC1ToInitialMassOfGas*m_GasExisted;
			m_C2_C5Existed=(1.-m_RatioC1ToInitialMassOfGas)*m_GasExisted;
			m_GasCracked=m_OilExisted*m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);   //OToGasFΪ��ת��Ϊ���ı�����
			m_C1Cracked=m_GasCracked*m_RatioCrackedC1;    //�����趨�ı������ѽ����ϸ����ֺ���
			m_C2_C5Cracked=m_GasCracked*(1.-m_RatioCrackedC1);  //�����趨�ı������ѽ����ϸ����ֺ���
			m_ResidueCracked=m_OilExisted*(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_CrackLeftedOil=m_OilExisted-m_OilCracked;
			m_C6_C14Cracked=m_OilCracked*m_RatioC6_C14ToInitialMassOfOil;  //������������ֵı��������ѽ���
			m_C15PlusCracked=m_OilCracked*(1.-m_RatioC6_C14ToInitialMassOfOil);  //������������ֵı��������ѽ���
			m_GasCrackedAdded=m_GasCracked;//�����ǵ�һ��ʱ�䲽��������ۻ��ѽ������ڳ�ʼ�ѽ�����
			m_C1CrackedAdded= m_C1Cracked;
			m_C2_C5CrackedAdded= m_C2_C5Cracked;
			m_ResidueCrackedAdded=m_ResidueCracked;
			m_OilCrackedAdded=m_OilCracked;
			m_C6_C14CrackedAdded=m_C6_C14Cracked;
			m_C15PlusCrackedAdded=m_C15PlusCracked;
			double  OilEntered=0;  //�������͵���
			double  C6_C14Entered=0; //�������������
			double  C15PlusEntered=0; //�������������
			double  GasEntered=0;  //������������
			double  C1Entered=0; //�������������
			double  C2_C5Entered=0; //�������������
			for(int j=0;j<m_NFlowInOil;j++)
			{
				OilEntered+=m_MassFlowInOil[j];
				C6_C14Entered+=m_MassFlowInC6_C14[j];  C15PlusEntered+=m_MassFlowInC15Plus[j];
				GasEntered+=m_MassFlowInGas[j];
				C1Entered+=m_MassFlowInC1[j];  C2_C5Entered+=m_MassFlowInC2_C5[j];
			}
			m_OilExisted=m_OilExisted+OilEntered-m_OilCracked;    //�������ʱ�䲽�������������
			m_C6_C14Existed=m_C6_C14Existed+C6_C14Entered-m_C6_C14Cracked;  //�������ʱ�䲽������������C6_C14��
			m_C15PlusExisted=m_C15PlusExisted+C15PlusEntered-m_C15PlusCracked;//�������ʱ�䲽������������C15Plus��;
			m_GasExisted =m_GasExisted+GasEntered+m_GasCracked; //�������ʱ�䲽�������������
			m_C1Existed=m_C1Existed+C1Entered-m_C1Cracked;  //�������ʱ�䲽������������C1��
			m_C2_C5Existed=m_C2_C5Existed+C2_C5Entered-m_C2_C5Cracked;//�������ʱ�䲽������������C2_C5��
			for(int j=0;j<m_NFlowInOil;j++) m_RatioFlowInOil[j]=m_MassFlowInOil[j]/m_OilExisted;    //�������������ռ�������ı��� ,������֮��
			m_ExpedOil=0;
			for(int j=0;j<m_NFlowInOil;j++) if(  m_MassFlowInOil[j]<0 ) m_ExpedOil+=m_MassFlowInOil[j];
			m_ExpedOil=fabs(m_ExpedOil);   //�ų�ȥ������
			m_CrackAndExpLeftedOil=m_CrackLeftedOil-m_ExpedOil; //�ѽ���ų���ʣ�������
			m_RatioCrackAndExpLeftedOil=m_CrackAndExpLeftedOil/m_OilExisted; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���
			Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
			GetfOilToGas();
		}
		void OilCrackToGas(double TLast, double tLast, double T, double t,OilInResCracking4C &aOilInResCracking4C)
		{    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			m_RatioCrackedC1=0.7;  //��ʱ�����ѽ�Ϊ����C1�ı���Ϊ0.7�� �������������ڿ��Ը��ݽ�һ�������ϵ���
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
			for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
			FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
			Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
			//����Ϊ��һʱ�䲽���ͣ���֣���������֣�������
			m_OilExisted=aOilInResCracking4C.m_OilExisted ;    //��һʱ�䲽����ʱ�ʹ����������ڱ�ʱ�䲽��ʼʱ���ʹ�����
			m_C6_C14Existed=aOilInResCracking4C.m_C6_C14Existed ;
			m_C15PlusExisted=aOilInResCracking4C.m_C15PlusExisted;
			m_GasExisted=aOilInResCracking4C.m_GasExisted ;    //��һʱ�䲽����ʱ�������������ڱ�ʱ�䲽��ʼʱ����������
			m_C1Existed=aOilInResCracking4C.m_C1Existed ;
			m_C2_C5Existed=aOilInResCracking4C.m_C2_C5Existed;
			//����Ϊ˲ʱ�� ������ʱ�䲽�ѽ����Լ��ѽ�ʣ����
			m_GasCracked=m_OilExisted*m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ����������Ϊ0��OToGasFΪ��ת��Ϊ���ı�����
			m_C1Cracked=m_GasCracked*m_RatioCrackedC1;    //�����趨�ı������ѽ����ϸ����ֺ���
			m_C2_C5Cracked=m_GasCracked*(1.-m_RatioCrackedC1);  //�����趨�ı������ѽ����ϸ����ֺ���
			m_ResidueCracked=m_OilExisted*(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_C6_C14Cracked=m_OilCracked*(m_C6_C14Existed/m_OilExisted);  //������������ֵı��������ѽ���
			m_C15PlusCracked=m_OilCracked*(m_C15PlusExisted/m_OilExisted);  //������������ֵı��������ѽ���
			m_CrackLeftedOil=m_OilExisted-m_OilCracked;
			//����Ϊ�ۻ���
			m_GasCrackedAdded=m_GasCracked+aOilInResCracking4C.m_GasCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
			m_C1CrackedAdded=aOilInResCracking4C.m_C1CrackedAdded+m_C1Cracked;
			m_C2_C5CrackedAdded=aOilInResCracking4C.m_C2_C5CrackedAdded+m_C2_C5Cracked;
			m_ResidueCrackedAdded=m_ResidueCracked+aOilInResCracking4C.m_ResidueCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���;
			m_OilCrackedAdded=m_OilCracked+aOilInResCracking4C.m_OilCrackedAdded;   //��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
			m_C6_C14CrackedAdded=aOilInResCracking4C.m_C6_C14CrackedAdded+m_C6_C14Cracked;
			m_C15PlusCrackedAdded=aOilInResCracking4C.m_C15PlusCrackedAdded+m_C15PlusCracked;
			//����Ϊ��ʱ�䲽��������ͣ���֣���������֣��������Լ����ѽ�Ļ�ѧ����ϵ��
			double OilEntered=0;  //�������͵���
			double C6_C14Entered=0,C15PlusEntered=0; //�������������
			double GasEntered=0;  //������������
			double C1Entered=0,C2_C5Entered=0; //�������������
			for(int j=0;j<m_NFlowInOil;j++)
			{
				OilEntered+=m_MassFlowInOil[j];
				C6_C14Entered+=m_MassFlowInC6_C14[j];  C15PlusEntered+=m_MassFlowInC15Plus[j];
				GasEntered+=m_MassFlowInGas[j];
				C1Entered+=m_MassFlowInC1[j];  C2_C5Entered+=m_MassFlowInC2_C5[j];
			}
			m_OilExisted=m_OilExisted+OilEntered-m_OilCracked;    //�������ʱ�䲽�������������
			m_C6_C14Existed=m_C6_C14Existed+C6_C14Entered-m_C6_C14Cracked;  //�������ʱ�䲽������������C6_C14��
			m_C15PlusExisted=m_C15PlusExisted+C15PlusEntered-m_C15PlusCracked;//�������ʱ�䲽������������C15Plus��;
			m_GasExisted =m_GasExisted+GasEntered+m_GasCracked; //�������ʱ�䲽�������������
			m_C1Existed=m_C1Existed+C1Entered-m_C1Cracked;  //�������ʱ�䲽������������C1��
			m_C2_C5Existed=m_C2_C5Existed+C2_C5Entered-m_C2_C5Cracked;//�������ʱ�䲽������������C2_C5��
			for(int j=0;j<m_NFlowInOil;j++) m_RatioFlowInOil[j]=m_MassFlowInOil[j]/m_OilExisted;    //�������������ռ�������ı��� ,������֮��
			m_ExpedOil=0;
			for(int j=0;j<m_NFlowInOil;j++) if(  m_MassFlowInOil[j]<0 ) m_ExpedOil+=m_MassFlowInOil[j];
			m_ExpedOil=fabs(m_ExpedOil);   //�ų�ȥ������
			m_CrackAndExpLeftedOil=m_CrackLeftedOil-m_ExpedOil; //�ѽ���ų���ʣ�������
			m_RatioCrackAndExpLeftedOil=m_CrackAndExpLeftedOil/m_OilExisted; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���
			GetfOilToGas();
		}
		void OilCrackToGasNew(double TLast, double tLast, double T, double t)
	   {    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
		  m_RatioCrackedC1=0.7;  //��ʱ�����ѽ�Ϊ����C1�ı���Ϊ0.7�� �������������ڿ��Ը��ݽ�һ�������ϵ���
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		  double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
		  for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
		  FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
		  Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
		  //����Ϊ��һʱ�䲽���ͣ���֣���������֣�������
		  //OilExisted=aOilInResCracking4C->OilExisted ;    //��һʱ�䲽����ʱ�ʹ����������ڱ�ʱ�䲽��ʼʱ���ʹ�����
		  //C6_C14Existed=aOilInResCracking4C->C6_C14Existed ;
		 // C15PlusExisted=aOilInResCracking4C->C15PlusExisted;
		  //GasExisted=aOilInResCracking4C->GasExisted ;    //��һʱ�䲽����ʱ�������������ڱ�ʱ�䲽��ʼʱ����������
		  //C1Existed=aOilInResCracking4C->C1Existed ;
		 // C2_C5Existed=aOilInResCracking4C->C2_C5Existed;
		  //����Ϊ˲ʱ�� ������ʱ�䲽�ѽ����Լ��ѽ�ʣ����
		  //GasCracked=OilExisted*OToGasF*(InitwBIw0OilToGas-wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ����������Ϊ0��OToGasFΪ��ת��Ϊ���ı�����
		  m_RatioGasFromOilCracking=m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);
		  //C1Cracked=GasCracked*RatioCrackedC1;    //�����趨�ı������ѽ����ϸ����ֺ���
		  //C2_C5Cracked=GasCracked*(1.-RatioCrackedC1);  //�����趨�ı������ѽ����ϸ����ֺ���
		  //ResidueCracked=OilExisted*(1.-OToGasF)*(InitwBIw0OilToGas-wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
		  m_RatioResidueFromOilCracking=(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);
		  m_RatioOilFromOilCracking=(InitwBIw0OilToGas-m_wBIw0OilToGas);
		  //OilCracked=GasCracked+ResidueCracked;
		  //C6_C14Cracked=OilCracked*(C6_C14Existed/OilExisted);  //������������ֵı��������ѽ���
		  //C15PlusCracked=OilCracked*(C15PlusExisted/OilExisted);  //������������ֵı��������ѽ���
		  //CrackLeftedOil=OilExisted-OilCracked;
		  //����Ϊ�ۻ���
	  //    GasCrackedAdded=GasCracked+aOilInResCracking4C->GasCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
	  //    C1CrackedAdded=aOilInResCracking4C->C1CrackedAdded+C1Cracked;
	 //     C2_C5CrackedAdded=aOilInResCracking4C->C2_C5CrackedAdded+C2_C5Cracked;
	 //     ResidueCrackedAdded=ResidueCracked+aOilInResCracking4C->ResidueCrackedAdded;//��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���;
	   //   OilCrackedAdded=OilCracked+aOilInResCracking4C->OilCrackedAdded;   //��ʱ�䲽���ۻ��ѽ������ڸ�ʱ�䲽���ѽ���������һ��ʱ�䲽���ۻ��ѽ���
		 // C6_C14CrackedAdded=aOilInResCracking4C->C6_C14CrackedAdded+C6_C14Cracked;
		 // C15PlusCrackedAdded=aOilInResCracking4C->C15PlusCrackedAdded+C15PlusCracked;
		  //����Ϊ��ʱ�䲽��������ͣ���֣���������֣��������Լ����ѽ�Ļ�ѧ����ϵ��
	  /*    double OilEntered=0;  //�������͵���
		  double C6_C14Entered=0,C15PlusEntered=0; //�������������
		  double GasEntered=0;  //������������
		  double C1Entered=0,C2_C5Entered=0; //�������������
		  for(int j=0;j<NFlowInOil;j++)
			{
			   OilEntered+=MassFlowInOil[j];
			   C6_C14Entered+=MassFlowInC6_C14[j];  C15PlusEntered+=MassFlowInC15Plus[j];
			   GasEntered+=MassFlowInGas[j];
			   C1Entered+=MassFlowInC1[j];  C2_C5Entered+=MassFlowInC2_C5[j];
			}
		  OilExisted=OilExisted+OilEntered-OilCracked;    //�������ʱ�䲽�������������
		  C6_C14Existed=C6_C14Existed+C6_C14Entered-C6_C14Cracked;  //�������ʱ�䲽������������C6_C14��
		  C15PlusExisted=C15PlusExisted+C15PlusEntered-C15PlusCracked;//�������ʱ�䲽������������C15Plus��;
		  GasExisted =GasExisted+GasEntered+GasCracked; //�������ʱ�䲽�������������
		  C1Existed=C1Existed+C1Entered-C1Cracked;  //�������ʱ�䲽������������C1��
		  C2_C5Existed=C2_C5Existed+C2_C5Entered-C2_C5Cracked;//�������ʱ�䲽������������C2_C5��
		  for(int j=0;j<NFlowInOil;j++) RatioFlowInOil[j]=MassFlowInOil[j]/OilExisted;    //�������������ռ�������ı��� ,������֮��
		  ExpedOil=0;
		  for(int j=0;j<NFlowInOil;j++) if(  MassFlowInOil[j]<0 ) ExpedOil+=MassFlowInOil[j];
		  ExpedOil=fabs(ExpedOil);   //�ų�ȥ������
		  CrackAndExpLeftedOil=CrackLeftedOil-ExpedOil; //�ѽ���ų���ʣ�������
		  RatioCrackAndExpLeftedOil=CrackAndExpLeftedOil/OilExisted; //��������һʱ�䲽�ѽ�ʣ��Ĳ���ȥ��һʱ�䲽�ų��������ܵ����������ѽ��ų���ʣ��������Ͻ�����͵������ı���
		  GetfOilToGas();  */
	   }
		void SetToItsOrifOilToGas()
		{  //��fOilToGas�趨Ϊԭʼֵ����Ҫ�����ڳ�ѹ�ز�ָ�ʱ���ж��ѭ���������Ӧ�ã�
			//��ʹ���¸�ѭ��ʱ�����õ� fOilToGas���µģ��������ϸ�ѭ��������¼�Ľ��
			for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]=m_fOilToGasBak[i];
			// ��������һ�£������ֵ�ǶԵģ�֮���Խ���ֵ��������ԭʼ��fOilToGasBak[i]��
			//����Ϊһ�γ�ѹѭ���Ǵ�ͷ��ʼ�ģ���һ����ѭ��������ѭ�����¿�ʼ����ζ�Ŵ���ԭʼ�Ļ�ѧ����������ʼ��
		}
	};

	//����Ϊ�л���Organofacies���Ҹ��Ļ�ѧ����ѧ����
	struct OrganoFaciesKinetics
	{
		int m_aOrganoFaciesStyle;
		double m_InitTOC;//���Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
		double m_MassOfInitTOCTotal; //���Ҹ�ԭʼ�л�̼�ܵ�����   �����ֻ��һ�����͸��Ҹ�����ñ�������һ���ظ�
		 //���Ҹ����ͻ�ѧ����ѧ����
		double m_FFKToOil;
		double m_EmeanKToOil;
		double m_SigmaKToOil;
		 //���Ҹ�������ѧ����ѧ����
		double m_FFKToGas;
		double m_EmeanKToGas;
		double m_SigmaKToGas;
		double m_TI0;
		double m_HI0;
		double m_G0;
		//���ѽ�Ϊ���Ļ�ѧ����ѧ����
		double m_FFOilToGas;
		double m_EmeanOilToGas;
		double m_SigmaOilToGas; 
		//�����л�����Ҹ����͵��ȶ���ѧ����
		double m_FFKToOilA; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToOilA;
		double m_SigmaKToOilA; //�ֱ����л���A���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToOilB; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToOilB;
		double m_SigmaKToOilB; //�ֱ����л���B���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToOilC; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToOilC;
		double m_SigmaKToOilC; //�ֱ����л���C���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToOilDE; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToOilDE;
		double m_SigmaKToOilDE; //�ֱ����л���DE���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToOilF; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToOilF;
		double m_SigmaKToOilF; //�ֱ����л���F���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		//�����л�����Ҹ��������ȶ���ѧ����
		double m_FFKToGasA; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToGasA;
		double m_SigmaKToGasA; //�ֱ����л���A���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToGasB; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToGasB;
		double m_SigmaKToGasB; //�ֱ����л���B���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToGasC; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToGasC;
		double m_SigmaKToGasC; //�ֱ����л���C���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToGasDE; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToGasDE;
		double m_SigmaKToGasDE; //�ֱ����л���DE���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		double m_FFKToGasF; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		double m_EmeanKToGasF;
		double m_SigmaKToGasF; //�ֱ����л���F���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��,��λKJ/mol
		//���͵������л������͵ĳ�ʼ����ѧ����
		double m_TI0A;
		double m_TI0B;
		double m_TI0C;
		double m_TI0DE;
		double m_TI0F; //TI0=S10/TOC0,��λmg g-1TOC
		double m_HI0A;
		double m_HI0B;
		double m_HI0C;
		double m_HI0DE;
		double m_HI0F; //HI0=S20/TOC0, ��ָ������λmg g-1TOC
		double m_G0A;
		double m_G0B;
		double m_G0C;
		double m_G0DE;
		double m_G0F; //G0=��(C1_5)/total S20 pyrolysate
		double m_W; //ʯ�����л�̼�ı���
		double m_OToGasF; //���ѽ�Ϊ���ı���

		int m_NKToOil;//���Ҹ����͵�ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
		std::vector<double> m_fKToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor����ͨ������̬�ֲ���ɢ���õ�
		std::vector<double> m_EKToOil;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�

		int m_NKToGas;//���Ҹ�������ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
		std::vector<double> m_fKToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor����ͨ������̬�ֲ���ɢ���õ�
		std::vector<double> m_EKToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�

		int m_NOilToGas;//���ѽ�Ϊ����ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
		std::vector<double> m_fOilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor�� ��ͨ������̬�ֲ���ɢ���õ�
		std::vector<double> m_fOilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_fOilToGasTemp; //��ʱ��¼��һ�������ѽ����Ļ�ѧ����ϵ��
		std::vector<double> m_EOilToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�

		double m_wBIw0KToOil;
		double m_wBIw0KToGas;
		double m_wBIw0OilToGas;//�ֱ����͸��Ҹ��������͡������Լ����ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
		double m_wBIw0K; //���Ҹ� �ܵ�ʣ�໯ѧ����ϵ����ԭʼΪ1��ͨ�����Ҹ��������͡����������µ��ܵ�ʣ�໯ѧ����ϵ���ֱ���Ը��Ҹ������͵ı��ʺ��������ı���֮����Ӷ��õ���
		
		double m_OilPerInitTOC; //��λ����ԭʼ�л�̼��InitTOC������һʱ��ε�������
		double m_GasPerInitTOC; //��λ����ԭʼ�л�̼��InitTOC������һʱ��ε�������
		double m_TOCReactableKerogen;
		double m_TOCInertKerogen; //�ֱ��ǿɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ� ����ָ��λԭʼ�л�̼���ڳ�ʼ״̬�Լ���Ӧ�����пɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ�������
		double m_TOCOilKerogen;
		double m_TOCGasKerogen; // new added 20190412�ֱ��ǿɷ�Ӧ�͸��Ҹ��������Ҹ� ����ָ��λԭʼ�л�̼���ڳ�ʼ״̬�Լ���Ӧ�����пɷ�Ӧ�͸��Ҹ��������Ҹ�������
		double m_TOCKerogen; //���Ҹ��л�̼ʣ���� ����ָ��λ����ԭʼ���Ҹ��Ĳ�����
		double m_TOCRemained; //�����л�̼ʣ���� ����ָ��λ����ԭʼ�л�̼���ݻ������еĲ����� ���������Ҹ��л�̼ʣ���� +Դ�����������л�̼����+���ѽ�����Ľ�̿��
		double m_OilGenerated;
		double m_GasGenerated; //���Ҹ���λ����ԭʼ�л�̼�ۼƵ���������������
		double m_TR; //Դ�ҵ�����ת����, ��ԭʼ�ɽ�����Ҹ��л�̼ת��Ϊ�ͺ����е��л�̼����

		//���������ѽ��йصĶ��Ƕ�Ӧ����������ԭʼ�л�̼������
		double m_OilExisted; //ָ���Ǵ�����Դ���е������
		double m_GasExisted; //ָ���Ǵ�����Դ���е������
		double m_ResidueExisted; //ָ������Դ���е����ѽ�Ϊ��������
		double m_GasCracked;//ָ����ÿһ�����ѽ������
		double m_GasCrackedAdded; //ָÿһ���ѽ������ۼ���
		double m_ResidueCracked; // ָ����ÿһ�����ѽ�Ĳ�������
		double m_ResidueCrackedAdded; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
		double m_OilCracked;//ÿһ���͵��ѽ���
		double m_OilCrackedAdded;//ÿһ���͵��ѽ������ۼ���

		double m_MKerTotal; //�ܵĸ��Ҹ��л�̼�����������������ѽ�Ľ�̿���� ���¼���20170908
		double m_MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
		double m_MKerOil;        //new added 20190404
		double m_MKerGas;        //new added 20190404
		double m_MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg

		//
		//double m_tempwBIw0OilToGas;
		//double m_tempfOilToGas10;
		//double m_tempfOilToGas10anot;

		OrganoFaciesKinetics()
		{
			m_aOrganoFaciesStyle=F; //������ʱѡ����л�������ΪA
			//�����л�����Ҹ����͵��ȶ���ѧ����
			m_FFKToOilA=2.13e13; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilA=206.4; m_SigmaKToOilA=8.2; //�ֱ����л���A���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilB=8.14e13; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilB=215.2; m_SigmaKToOilB=8.3; //�ֱ����л���B���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilC=2.44e14; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilC=221.4; m_SigmaKToOilC=3.9; //�ֱ����л���C���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilDE=4.97e14; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilDE=228.2; m_SigmaKToOilDE=7.9; //�ֱ����л���DE���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilF=1.23e17; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilF=259.1; m_SigmaKToOilF=6.6; //�ֱ����л���F���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			//�����л�����Ҹ��������ȶ���ѧ����
			m_FFKToGasA=3.93e12; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasA=206.7; m_SigmaKToGasA=10.7; //�ֱ����л���A���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasB=2.17e18; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasB=278.7; m_SigmaKToGasB=18.4; //�ֱ����л���B���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasC=2.29e16; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasC=250.4; m_SigmaKToGasC=10.1; //�ֱ����л���C���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasDE=1.93e16; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasDE=275.0; m_SigmaKToGasDE=9.9; //�ֱ����л���DE���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasF=1.93e16; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasF=275.0; m_SigmaKToGasF=9.9; //�ֱ����л���F���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			//���͵������л������͵ĳ�ʼ����ѧ����
			m_TI0A=33;m_TI0B=18;m_TI0C=20;m_TI0DE=7;m_TI0F=2; //TI0=S10/TOC0;��λmg g-1TOC
			m_HI0A=617;m_HI0B=592;m_HI0C=600;m_HI0DE=333;m_HI0F=158; //HI0=S20/TOC0; ��ָ������λmg g-1TOC
			m_G0A=0.17;m_G0B=0.17;m_G0C=0.13;m_G0DE=0.23;m_G0F=0.44; //G0=��(C1_5)/total S20 pyrolysate
			m_W=0.85; //ʯ�����л�̼�ı���
			m_OToGasF=0.5; //���ѽ�Ϊ���ı���
		}
		OrganoFaciesKinetics(const OrganoFaciesKinetics &other)
		{
			*this = other;
		}
		const OrganoFaciesKinetics &operator=(const OrganoFaciesKinetics &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_aOrganoFaciesStyle=other.m_aOrganoFaciesStyle; //������ʱѡ����л�������ΪA
			m_InitTOC = other.m_InitTOC;//���Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
			m_MassOfInitTOCTotal = other.m_MassOfInitTOCTotal;//���Ҹ�ԭʼ�л�̼�ܵ�����   �����ֻ��һ�����͸��Ҹ�����ñ�������һ���ظ�
			//���Ҹ����ͻ�ѧ����ѧ����
			m_FFKToOil=other.m_FFKToOil;
			m_EmeanKToOil=other.m_EmeanKToOil;
			m_SigmaKToOil=other.m_SigmaKToOil;
			//���Ҹ�������ѧ����ѧ����
			m_FFKToGas=other.m_FFKToGas;
			m_EmeanKToGas=other.m_EmeanKToGas;
			m_SigmaKToGas=other.m_SigmaKToGas;
			m_TI0=other.m_TI0;
			m_HI0=other.m_HI0;
			m_G0=other.m_G0;
			//���ѽ�Ϊ���Ļ�ѧ����ѧ����
			m_FFOilToGas=other.m_FFOilToGas;
			m_EmeanOilToGas=other.m_EmeanOilToGas;
			m_SigmaOilToGas=other.m_SigmaOilToGas; 
			//�����л�����Ҹ����͵��ȶ���ѧ����
			m_FFKToOilA=other.m_FFKToOilA; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilA=other.m_EmeanKToOilA; m_SigmaKToOilA=other.m_SigmaKToOilA; //�ֱ����л���A���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilB=other.m_FFKToOilB; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilB=other.m_EmeanKToOilB; m_SigmaKToOilB=other.m_SigmaKToOilB; //�ֱ����л���B���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilC=other.m_FFKToOilC; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilC=other.m_EmeanKToOilC; m_SigmaKToOilC=other.m_SigmaKToOilC; //�ֱ����л���C���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilDE=other.m_FFKToOilDE; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilDE=other.m_EmeanKToOilDE; m_SigmaKToOilDE=other.m_SigmaKToOilDE; //�ֱ����л���DE���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToOilF=other.m_FFKToOilF; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToOilF=other.m_EmeanKToOilF; m_SigmaKToOilF=other.m_SigmaKToOilF; //�ֱ����л���F���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			//�����л�����Ҹ��������ȶ���ѧ����
			m_FFKToGasA=other.m_FFKToGasA; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasA=other.m_EmeanKToGasA; m_SigmaKToGasA=other.m_SigmaKToGasA; //�ֱ����л���A���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasB=other.m_FFKToGasB; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasB=other.m_EmeanKToGasB; m_SigmaKToGasB=other.m_SigmaKToGasB; //�ֱ����л���B���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasC=other.m_FFKToGasC; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasC=other.m_EmeanKToGasC; m_SigmaKToGasC=other.m_SigmaKToGasC; //�ֱ����л���C���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasDE=other.m_FFKToGasDE; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasDE=other.m_EmeanKToGasDE; m_SigmaKToGasDE=other.m_SigmaKToGasDE; //�ֱ����л���DE���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			m_FFKToGasF=other.m_FFKToGasF; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			m_EmeanKToGasF=other.m_EmeanKToGasF; m_SigmaKToGasF=other.m_SigmaKToGasF; //�ֱ����л���F���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			//���͵������л������͵ĳ�ʼ����ѧ����
			m_TI0A=other.m_TI0A;m_TI0B=other.m_TI0B;m_TI0C=other.m_TI0C;m_TI0DE=other.m_TI0DE;m_TI0F=other.m_TI0F; //TI0=other.S10/TOC0;��λmg g-1TOC
			m_HI0A=other.m_HI0A;m_HI0B=other.m_HI0B;m_HI0C=other.m_HI0C;m_HI0DE=other.m_HI0DE;m_HI0F=other.m_HI0F; //HI0=other.S20/TOC0; ��ָ������λmg g-1TOC
			m_G0A=other.m_G0A;m_G0B=other.m_G0B;m_G0C=other.m_G0C;m_G0DE=other.m_G0DE;m_G0F=other.m_G0F; //G0=other.��(C1_5)/total S20 pyrolysate
			m_W=other.m_W; //ʯ�����л�̼�ı���
			m_OToGasF=other.m_OToGasF; //���ѽ�Ϊ���ı���
			m_NKToOil = other.m_NKToOil;//���Ҹ����͵�ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
			m_fKToOil = other.m_fKToOil;//�ǻ�ѧ����ϵ����Stoichiometric Factor����ͨ������̬�ֲ���ɢ���õ�
			m_EKToOil = other.m_EKToOil;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�
			m_NKToGas = other.m_NKToGas;//���Ҹ�������ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
			m_fKToGas = other.m_fKToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor����ͨ������̬�ֲ���ɢ���õ�
			m_EKToGas = other.m_EKToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�
			m_NOilToGas = other.m_NOilToGas;//���ѽ�Ϊ����ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
			m_fOilToGas = other.m_fOilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor�� ��ͨ������̬�ֲ���ɢ���õ�
			m_fOilToGasBak = other.m_fOilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
			m_fOilToGasTemp = other.m_fOilToGasTemp; //��ʱ��¼��һ�������ѽ����Ļ�ѧ����ϵ��
			m_EOilToGas = other.m_EOilToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�
			m_wBIw0KToOil = other.m_wBIw0KToOil;
			m_wBIw0KToGas = other.m_wBIw0KToGas;
			m_wBIw0OilToGas = other.m_wBIw0OilToGas;
			m_wBIw0K = other.m_wBIw0K;
			m_OilPerInitTOC = other.m_OilPerInitTOC;
			m_GasPerInitTOC = other.m_GasPerInitTOC;
			m_TOCReactableKerogen = other.m_TOCReactableKerogen;
			m_TOCInertKerogen = other.m_TOCInertKerogen;
			m_TOCOilKerogen = other.m_TOCOilKerogen;
			m_TOCGasKerogen = other.m_TOCGasKerogen;
			m_TOCKerogen = other.m_TOCKerogen;
			m_TOCRemained = other.m_TOCRemained;
			m_OilGenerated = other.m_OilGenerated;
			m_GasGenerated = other.m_GasGenerated;
			m_TR = other.m_TR;
			m_OilExisted = other.m_OilExisted;
			m_GasExisted = other.m_GasExisted;
			m_ResidueExisted = other.m_ResidueExisted;
			m_GasCracked = other.m_GasCracked;
			m_GasCrackedAdded = other.m_GasCrackedAdded;
			m_ResidueCracked = other.m_ResidueCracked;
			m_ResidueCrackedAdded = other.m_ResidueCrackedAdded;
			m_OilCracked = other.m_OilCracked;
			m_OilCrackedAdded = other.m_OilCrackedAdded;
			m_MKerTotal = other.m_MKerTotal;
			m_MKerReac = other.m_MKerReac;
			m_MKerOil = other.m_MKerOil;
			m_MKerGas = other.m_MKerGas;
			m_MKerInert = other.m_MKerInert;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(int);//int m_aOrganoFaciesStyle;
			curSize += sizeof(double);//double m_InitTOC;
			curSize += sizeof(double);//double m_MassOfInitTOCTotal;
			curSize += sizeof(double);//double m_FFKToOil;
			curSize += sizeof(double);//double m_EmeanKToOil;
			curSize += sizeof(double);//double m_SigmaKToOil;
			curSize += sizeof(double);//double m_FFKToGas;
			curSize += sizeof(double);//double m_EmeanKToGas;
			curSize += sizeof(double);//double m_SigmaKToGas;
			curSize += sizeof(double);//double m_TI0;
			curSize += sizeof(double);//double m_HI0;
			curSize += sizeof(double);//double m_G0;
			curSize += sizeof(double);//double m_FFOilToGas;
			curSize += sizeof(double);//double m_EmeanOilToGas;
			curSize += sizeof(double);//double m_SigmaOilToGas; 
			curSize += sizeof(double);//double m_FFKToOilA;
			curSize += sizeof(double);//double m_EmeanKToOilA;
			curSize += sizeof(double);//double m_SigmaKToOilA;
			curSize += sizeof(double);//double m_FFKToOilB;
			curSize += sizeof(double);//double m_EmeanKToOilB;
			curSize += sizeof(double);//double m_SigmaKToOilB;
			curSize += sizeof(double);//double m_FFKToOilC;
			curSize += sizeof(double);//double m_EmeanKToOilC;
			curSize += sizeof(double);//double m_SigmaKToOilC;
			curSize += sizeof(double);//double m_FFKToOilDE;
			curSize += sizeof(double);//double m_EmeanKToOilDE;
			curSize += sizeof(double);//double m_SigmaKToOilDE;
			curSize += sizeof(double);//double m_FFKToOilF; 
			curSize += sizeof(double);//double m_EmeanKToOilF;
			curSize += sizeof(double);//double m_SigmaKToOilF;
			curSize += sizeof(double);//double m_FFKToGasA;
			curSize += sizeof(double);//double m_EmeanKToGasA;
			curSize += sizeof(double);//double m_SigmaKToGasA;
			curSize += sizeof(double);//double m_FFKToGasB;
			curSize += sizeof(double);//double m_EmeanKToGasB;
			curSize += sizeof(double);//double m_SigmaKToGasB;
			curSize += sizeof(double);//double m_FFKToGasC;
			curSize += sizeof(double);//double m_EmeanKToGasC;
			curSize += sizeof(double);//double m_SigmaKToGasC;
			curSize += sizeof(double);//double m_FFKToGasDE;
			curSize += sizeof(double);//double m_EmeanKToGasDE;
			curSize += sizeof(double);//double m_SigmaKToGasDE;
			curSize += sizeof(double);//double m_FFKToGasF;
			curSize += sizeof(double);//double m_EmeanKToGasF;
			curSize += sizeof(double);//double m_SigmaKToGasF;
			curSize += sizeof(double);//double m_TI0A;
			curSize += sizeof(double);//double m_TI0B;
			curSize += sizeof(double);//double m_TI0C;
			curSize += sizeof(double);//double m_TI0DE;
			curSize += sizeof(double);//double m_TI0F;
			curSize += sizeof(double);//double m_HI0A;
			curSize += sizeof(double);//double m_HI0B;
			curSize += sizeof(double);//double m_HI0C;
			curSize += sizeof(double);//double m_HI0DE;
			curSize += sizeof(double);//double m_HI0F;
			curSize += sizeof(double);//double m_G0A;
			curSize += sizeof(double);//double m_G0B;
			curSize += sizeof(double);//double m_G0C;
			curSize += sizeof(double);//double m_G0DE;
			curSize += sizeof(double);//double m_G0F;
			curSize += sizeof(double);//double m_W;
			curSize += sizeof(double);//double m_OToGasF;
			curSize += sizeof(int);//int m_NKToOil;
			curSize += (sizeof(int) + m_fKToOil.size() * sizeof(double));//std::vector<double> m_fKToOil;
			curSize += (sizeof(int) + m_EKToOil.size() * sizeof(double));//std::vector<double> m_EKToOil;
			curSize += sizeof(int);//int m_NKToGas;
			curSize += (sizeof(int) + m_fKToGas.size() * sizeof(double));//std::vector<double> m_fKToGas;
			curSize += (sizeof(int) + m_EKToGas.size() * sizeof(double));//std::vector<double> m_EKToGas;
			curSize += sizeof(int);//int m_NOilToGas;
			curSize += (sizeof(int) + m_fOilToGas.size() * sizeof(double));//std::vector<double> m_fOilToGas;
			curSize += (sizeof(int) + m_fOilToGasBak.size() * sizeof(double));//std::vector<double> m_fOilToGasBak; ;
			curSize += (sizeof(int) + m_fOilToGasTemp.size() * sizeof(double));//std::vector<double> m_fOilToGasTemp; 
			curSize += (sizeof(int) + m_EOilToGas.size() * sizeof(double));//std::vector<double> m_EOilToGas;
			curSize += sizeof(double);//double m_wBIw0KToOil;
			curSize += sizeof(double);//double m_wBIw0KToGas;
			curSize += sizeof(double);//double m_wBIw0OilToGas;
			curSize += sizeof(double);//double m_wBIw0K;
			curSize += sizeof(double);//double m_OilPerInitTOC;
			curSize += sizeof(double);//double m_GasPerInitTOC;
			curSize += sizeof(double);//double m_TOCReactableKerogen;
			curSize += sizeof(double);//double m_TOCInertKerogen;
			curSize += sizeof(double);//double m_TOCOilKerogen;
			curSize += sizeof(double);//double m_TOCGasKerogen;
			curSize += sizeof(double);//double m_TOCKerogen;
			curSize += sizeof(double);//double m_TOCRemained;
			curSize += sizeof(double);//double m_OilGenerated;
			curSize += sizeof(double);//double m_GasGenerated;
			curSize += sizeof(double);//double m_TR;
			curSize += sizeof(double);//double m_OilExisted;
			curSize += sizeof(double);//double m_GasExisted;
			curSize += sizeof(double);//double m_ResidueExisted;
			curSize += sizeof(double);//double m_GasCracked;
			curSize += sizeof(double);//double m_GasCrackedAdded;
			curSize += sizeof(double);//double m_ResidueCracked;
			curSize += sizeof(double);//double m_ResidueCrackedAdded;
			curSize += sizeof(double);//double m_OilCracked;
			curSize += sizeof(double);//double m_OilCrackedAdded;
			curSize += sizeof(double);//double m_MKerTotal;
			curSize += sizeof(double);//double m_MKerReac;
			curSize += sizeof(double);//double m_MKerOil;
			curSize += sizeof(double);//double m_MKerGas;
			curSize += sizeof(double);//double m_MKerInert;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_aOrganoFaciesStyle), sizeof(int));data += sizeof(int);
			memcpy(data, &(m_InitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MassOfInitTOCTotal), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TI0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_G0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFOilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanOilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaOilToGas), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_FFKToOilA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToOilA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToOilA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToOilB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToOilB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToOilB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToOilC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToOilC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToOilC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToOilDE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToOilDE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToOilDE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToOilF), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_EmeanKToOilF), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToOilF), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToGasA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToGasA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToGasA), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToGasB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToGasB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToGasB), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToGasC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToGasC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToGasC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToGasDE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToGasDE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToGasDE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_FFKToGasF), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanKToGasF), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaKToGasF), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TI0A), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TI0B), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TI0C), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TI0DE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TI0F), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI0A), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI0B), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI0C), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI0DE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI0F), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_G0A), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_G0B), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_G0C), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_G0DE), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_G0F), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_W), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OToGasF), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NKToOil), sizeof(int));data += sizeof(int);
			int fKToOilsize = m_fKToOil.size();
			memcpy(data, &fKToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fKToOilsize; j++)
			{
				memcpy(data, &(m_fKToOil[j]), sizeof(double));data += sizeof(double);
			}
			int EKToOilsize = m_EKToOil.size();
			memcpy(data, &EKToOilsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EKToOilsize; j++)
			{
				memcpy(data, &(m_EKToOil[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_NKToGas), sizeof(int));data += sizeof(int);
			int fKToGassize = m_fKToGas.size();
			memcpy(data, &fKToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fKToGassize; j++)
			{
				memcpy(data, &(m_fKToGas[j]), sizeof(double));data += sizeof(double);
			}
			int EKToGassize = m_EKToGas.size();
			memcpy(data, &EKToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EKToGassize; j++)
			{
				memcpy(data, &(m_EKToGas[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_NOilToGas), sizeof(int));data += sizeof(int);
			int fOilToGassize = m_fOilToGas.size();
			memcpy(data, &fOilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fOilToGassize; j++)
			{
				memcpy(data, &(m_fOilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize = m_fOilToGasBak.size();
			memcpy(data, &fOilToGasBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fOilToGasBaksize; j++)
			{
				memcpy(data, &(m_fOilToGasBak[j]), sizeof(double));data += sizeof(double);
			}
			int fOilToGasTempsize = m_fOilToGasTemp.size();
			memcpy(data, &fOilToGasTempsize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fOilToGasTempsize; j++)
			{
				memcpy(data, &(m_fOilToGasTemp[j]), sizeof(double));data += sizeof(double);
			}
			int EOilToGassize = m_EOilToGas.size();
			memcpy(data, &EOilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EOilToGassize; j++)
			{
				memcpy(data, &(m_EOilToGas[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_wBIw0KToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0KToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0OilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0K), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilPerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasPerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCReactableKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCInertKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCOilKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCGasKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCRemained), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilGenerated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasGenerated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TR), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerTotal), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerReac), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerInert), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_aOrganoFaciesStyle), data, sizeof(int));data += sizeof(int);
			memcpy(&(m_InitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MassOfInitTOCTotal), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TI0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_G0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFOilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanOilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaOilToGas), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_FFKToOilA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToOilA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToOilA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToOilB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToOilB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToOilB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToOilC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToOilC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToOilC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToOilDE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToOilDE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToOilDE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToOilF), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_EmeanKToOilF), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToOilF), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToGasA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToGasA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToGasA), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToGasB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToGasB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToGasB), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToGasC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToGasC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToGasC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToGasDE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToGasDE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToGasDE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_FFKToGasF), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanKToGasF), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaKToGasF), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TI0A), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TI0B), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TI0C), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TI0DE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TI0F), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI0A), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI0B), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI0C), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI0DE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI0F), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_G0A), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_G0B), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_G0C), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_G0DE), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_G0F), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_W), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OToGasF), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NKToOil), data, sizeof(int));data += sizeof(int);
			int fKToOilsize;
			memcpy(&fKToOilsize, data, sizeof(int));data += sizeof(int);
			m_fKToOil.resize(fKToOilsize);
			for(int j = 0; j < fKToOilsize; j++)
			{
				memcpy(&(m_fKToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			int EKToOilsize;
			memcpy(&EKToOilsize, data, sizeof(int));data += sizeof(int);
			m_EKToOil.resize(EKToOilsize);
			for(int j = 0; j < EKToOilsize; j++)
			{
				memcpy(&(m_EKToOil[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_NKToGas), data, sizeof(int));data += sizeof(int);
			int fKToGassize;
			memcpy(&fKToGassize, data, sizeof(int));data += sizeof(int);
			m_fKToGas.resize(fKToGassize);
			for(int j = 0; j < fKToGassize; j++)
			{
				memcpy(&(m_fKToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int EKToGassize;
			memcpy(&EKToGassize, data, sizeof(int));data += sizeof(int);
			m_EKToGas.resize(EKToGassize);
			for(int j = 0; j < EKToGassize; j++)
			{
				memcpy(&(m_EKToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_NOilToGas), data, sizeof(int));data += sizeof(int);
			int fOilToGassize;
			memcpy(&fOilToGassize, data, sizeof(int));data += sizeof(int);
			m_fOilToGas.resize(fOilToGassize);
			for(int j = 0; j < fOilToGassize; j++)
			{
				memcpy(&(m_fOilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize;
			memcpy(&fOilToGasBaksize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasBak.resize(fOilToGasBaksize);
			for(int j = 0; j < fOilToGasBaksize; j++)
			{
				memcpy(&(m_fOilToGasBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int fOilToGasTempsize;
			memcpy(&fOilToGasTempsize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasTemp.resize(fOilToGasTempsize);
			for(int j = 0; j < fOilToGasTempsize; j++)
			{
				memcpy(&(m_fOilToGasTemp[j]), data, sizeof(double));data += sizeof(double);
			}
			int EOilToGassize;
			memcpy(&EOilToGassize, data, sizeof(int));data += sizeof(int);
			m_EOilToGas.resize(EOilToGassize);
			for(int j = 0; j < EOilToGassize; j++)
			{
				memcpy(&(m_EOilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_wBIw0KToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0KToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0OilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0K), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilPerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasPerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCReactableKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCInertKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCOilKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCGasKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCRemained), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilGenerated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasGenerated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TR), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerTotal), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerReac), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerInert), data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, OrganoFaciesKinetics &organickinetics)
		{
			os << "\r\n>>>>>>>>>>>>>>>OrganoFaciesKinetics parameter as flow:"; 
			os << "\r\n---- ---- ---- aOrganoFaciesStyle:" << organickinetics.m_aOrganoFaciesStyle; //������ʱѡ����л�������ΪA
			os << "\r\n---- ---- ---- InitTOC:" << organickinetics.m_InitTOC;//���Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
			os << "\r\n---- ---- ---- MassOfInitTOCTotal:" << organickinetics.m_MassOfInitTOCTotal;//���Ҹ�ԭʼ�л�̼�ܵ�����   �����ֻ��һ�����͸��Ҹ�����ñ�������һ���ظ�
			os << "\r\n---- ---- ---- FFKToOil:" << organickinetics.m_FFKToOil;
			os << "\r\n---- ---- ---- EmeanKToOil:" << organickinetics.m_EmeanKToOil;
			os << "\r\n---- ---- ---- SigmaKToOil:" << organickinetics.m_SigmaKToOil;
			os << "\r\n---- ---- ---- FFKToGas:" << organickinetics.m_FFKToGas;
			os << "\r\n---- ---- ---- EmeanKToGas:" << organickinetics.m_EmeanKToGas;
			os << "\r\n---- ---- ---- SigmaKToGas:" << organickinetics.m_SigmaKToGas;
			os << "\r\n---- ---- ---- TI0:" << organickinetics.m_TI0;
			os << "\r\n---- ---- ---- HI0:" << organickinetics.m_HI0;
			os << "\r\n---- ---- ---- G0:" << organickinetics.m_G0;
			os << "\r\n---- ---- ---- FFOilToGas:" << organickinetics.m_FFOilToGas;
			os << "\r\n---- ---- ---- EmeanOilToGas:" << organickinetics.m_EmeanOilToGas;
			os << "\r\n---- ---- ---- SigmaOilToGas:" << organickinetics.m_SigmaOilToGas; 
			os << "\r\n---- ---- ---- FFKToOilA:" << organickinetics.m_FFKToOilA; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToOilA:" << organickinetics.m_EmeanKToOilA; 
			os << "\r\n---- ---- ---- SigmaKToOilA:" << organickinetics.m_SigmaKToOilA; //�ֱ����л���A���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToOilB:" << organickinetics.m_FFKToOilB; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToOilB:" << organickinetics.m_EmeanKToOilB; 
			os << "\r\n---- ---- ---- SigmaKToOilB:" << organickinetics.m_SigmaKToOilB; //�ֱ����л���B���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToOilC:" << organickinetics.m_FFKToOilC; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToOilC:" << organickinetics.m_EmeanKToOilC; 
			os << "\r\n---- ---- ---- SigmaKToOilC:" << organickinetics.m_SigmaKToOilC; //�ֱ����л���C���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToOilDE:" << organickinetics.m_FFKToOilDE; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToOilDE:" << organickinetics.m_EmeanKToOilDE; 
			os << "\r\n---- ---- ---- SigmaKToOilDE:" << organickinetics.m_SigmaKToOilDE; //�ֱ����л���DE���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToOilF:" << organickinetics.m_FFKToOilF; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToOilF:" << organickinetics.m_EmeanKToOilF; 
			os << "\r\n---- ---- ---- SigmaKToOilF:" << organickinetics.m_SigmaKToOilF; //�ֱ����л���F���Ҹ����͵Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToGasA:" << organickinetics.m_FFKToGasA; //�л���A��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToGasA:" << organickinetics.m_EmeanKToGasA; 
			os << "\r\n---- ---- ---- SigmaKToGasA:" << organickinetics.m_SigmaKToGasA; //�ֱ����л���A���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToGasB:" << organickinetics.m_FFKToGasB; //�л���B��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToGasB:" << organickinetics.m_EmeanKToGasB; 
			os << "\r\n---- ---- ---- SigmaKToGasB:" << organickinetics.m_SigmaKToGasB; //�ֱ����л���B���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToGasC:" << organickinetics.m_FFKToGasC; //�л���C��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToGasC:" << organickinetics.m_EmeanKToGasC; 
			os << "\r\n---- ---- ---- SigmaKToGasC:" << organickinetics.m_SigmaKToGasC; //�ֱ����л���C���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToGasDE:" << organickinetics.m_FFKToGasDE; //�л���DE��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToGasDE:" << organickinetics.m_EmeanKToGasDE; 
			os << "\r\n---- ---- ---- SigmaKToGasDE:" << organickinetics.m_SigmaKToGasDE; //�ֱ����л���DE���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- FFKToGasF:" << organickinetics.m_FFKToGasF; //�л���F��Frequency factor  �����Ҹ�����Ƶ�����ӣ���A ����λ��s^-1;Ϊ��ֵ
			os << "\r\n---- ---- ---- EmeanKToGasF:" << organickinetics.m_EmeanKToGasF; 
			os << "\r\n---- ---- ---- SigmaKToGasF:" << organickinetics.m_SigmaKToGasF; //�ֱ����л���F���Ҹ������Ķ���ѧ������������̬�ֲ��ľ�ֵ�ͱ�׼��;��λKJ/mol
			os << "\r\n---- ---- ---- TI0A:" << organickinetics.m_TI0A;
			os << "\r\n---- ---- ---- TI0B:" << organickinetics.m_TI0B;
			os << "\r\n---- ---- ---- TI0C:" << organickinetics.m_TI0C;
			os << "\r\n---- ---- ---- TI0DE:" << organickinetics.m_TI0DE;
			os << "\r\n---- ---- ---- TI0F:" << organickinetics.m_TI0F; //TI0=other.S10/TOC0;��λmg g-1TOC
			os << "\r\n---- ---- ---- HI0A:" << organickinetics.m_HI0A;
			os << "\r\n---- ---- ---- HI0B:" << organickinetics.m_HI0B;
			os << "\r\n---- ---- ---- HI0C:" << organickinetics.m_HI0C;
			os << "\r\n---- ---- ---- HI0DE:" << organickinetics.m_HI0DE;
			os << "\r\n---- ---- ---- HI0F:" << organickinetics.m_HI0F; //HI0=other.S20/TOC0; ��ָ������λmg g-1TOC
			os << "\r\n---- ---- ---- G0A:" << organickinetics.m_G0A;
			os << "\r\n---- ---- ---- G0B:" << organickinetics.m_G0B;
			os << "\r\n---- ---- ---- G0C:" << organickinetics.m_G0C;
			os << "\r\n---- ---- ---- G0DE:" << organickinetics.m_G0DE;
			os << "\r\n---- ---- ---- G0F:" << organickinetics.m_G0F; //G0=other.��(C1_5)/total S20 pyrolysate
			os << "\r\n---- ---- ---- W:" << organickinetics.m_W; //ʯ�����л�̼�ı���
			os << "\r\n---- ---- ---- OToGasF:" << organickinetics.m_OToGasF; //���ѽ�Ϊ���ı���
			os << "\r\n---- ---- ---- NKToOil:" << organickinetics.m_NKToOil;
			for(int i = 0; i < organickinetics.m_fKToOil.size(); i++)os << "\r\n---- ---- ---- m_fKToOil:" << i << ":" << organickinetics.m_fKToOil[i];
			for(int i = 0; i < organickinetics.m_EKToOil.size(); i++)os << "\r\n---- ---- ---- m_EKToOil:" << i << ":" << organickinetics.m_EKToOil[i];
			os << "\r\n---- ---- ---- NKToGas:" << organickinetics.m_NKToGas;
			for(int i = 0; i < organickinetics.m_fKToGas.size(); i++)os << "\r\n---- ---- ---- m_fKToGas:" << i << ":" << organickinetics.m_fKToGas[i];
			for(int i = 0; i < organickinetics.m_EKToGas.size(); i++)os << "\r\n---- ---- ---- m_EKToGas:" << i << ":" << organickinetics.m_EKToGas[i];
			os << "\r\n---- ---- ---- NOilToGas:" << organickinetics.m_NOilToGas;//���ѽ�Ϊ����ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
			for(int i = 0; i < organickinetics.m_fOilToGas.size(); i++)os << "\r\n---- ---- ---- m_fOilToGas:" << i << ":" << organickinetics.m_fOilToGas[i];
			for(int i = 0; i < organickinetics.m_fOilToGasBak.size(); i++)os << "\r\n---- ---- ---- m_fOilToGasBak:" << i << ":" << organickinetics.m_fOilToGasBak[i];
			for(int i = 0; i < organickinetics.m_fOilToGasTemp.size(); i++)os << "\r\n---- ---- ---- m_fOilToGasTemp:" << i << ":" << organickinetics.m_fOilToGasTemp[i];
			for(int i = 0; i < organickinetics.m_EOilToGas.size(); i++)os << "\r\n---- ---- ---- m_EOilToGas:" << i << ":" << organickinetics.m_EOilToGas[i];
			os << "\r\n---- ---- ---- wBIw0KToOil:" << organickinetics.m_wBIw0KToOil;
			os << "\r\n---- ---- ---- wBIw0KToGas:" << organickinetics.m_wBIw0KToGas;
			os << "\r\n---- ---- ---- wBIw0OilToGas:" << organickinetics.m_wBIw0OilToGas;
			os << "\r\n---- ---- ---- wBIw0K:" << organickinetics.m_wBIw0K;
			os << "\r\n---- ---- ---- OilPerInitTOC:" << organickinetics.m_OilPerInitTOC;
			os << "\r\n---- ---- ---- GasPerInitTOC:" << organickinetics.m_GasPerInitTOC;
			os << "\r\n---- ---- ---- TOCReactableKerogen:" << organickinetics.m_TOCReactableKerogen;
			os << "\r\n---- ---- ---- TOCInertKerogen:" << organickinetics.m_TOCInertKerogen;
			os << "\r\n---- ---- ---- TOCOilKerogen:" << organickinetics.m_TOCOilKerogen;
			os << "\r\n---- ---- ---- TOCGasKerogen:" << organickinetics.m_TOCGasKerogen;
			os << "\r\n---- ---- ---- TOCKerogen:" << organickinetics.m_TOCKerogen;
			os << "\r\n---- ---- ---- TOCRemained:" << organickinetics.m_TOCRemained;
			os << "\r\n---- ---- ---- OilGenerated:" << organickinetics.m_OilGenerated;
			os << "\r\n---- ---- ---- GasGenerated:" << organickinetics.m_GasGenerated;
			os << "\r\n---- ---- ---- TR:" << organickinetics.m_TR;
			os << "\r\n---- ---- ---- OilExisted:" << organickinetics.m_OilExisted;
			os << "\r\n---- ---- ---- GasExisted:" << organickinetics.m_GasExisted;
			os << "\r\n---- ---- ---- ResidueExisted:" << organickinetics.m_ResidueExisted;
			os << "\r\n---- ---- ---- GasCracked:" << organickinetics.m_GasCracked;
			os << "\r\n---- ---- ---- GasCrackedAdded:" << organickinetics.m_GasCrackedAdded;
			os << "\r\n---- ---- ---- ResidueCracked:" << organickinetics.m_ResidueCracked;
			os << "\r\n---- ---- ---- ResidueCrackedAdded:" << organickinetics.m_ResidueCrackedAdded;
			os << "\r\n---- ---- ---- OilCracked:" << organickinetics.m_OilCracked;
			os << "\r\n---- ---- ---- OilCrackedAdded:" << organickinetics.m_OilCrackedAdded;
			os << "\r\n---- ---- ---- MKerTotal:" << organickinetics.m_MKerTotal;
			os << "\r\n---- ---- ---- MKerReac:" << organickinetics.m_MKerReac;
			os << "\r\n---- ---- ---- MKerOil:" << organickinetics.m_MKerOil;
			os << "\r\n---- ---- ---- MKerGas:" << organickinetics.m_MKerGas;
			os << "\r\n---- ---- ---- MKerInert:" << organickinetics.m_MKerInert;
			return os;
		}
		double Jiecheng(int n)
		{
			double temp = 1; 
			for(int i = 0; i < n; i++) 
				temp = temp * double(i + 1); 
			return temp; 
		}
		double erf(double x)
		{  
			int N = 30;
			double pi = 3.1415926535;
			double temp = 0;
			for(int i = 0; i < N + 1; i++)
				temp += pow((double)-1, (int)i) * pow(x, (int)(2 * i + 1)) / (2 * i + 1) / Jiecheng(i);
			temp = temp * 2 / sqrt(pi);
			return temp;
		}
		double Pnormal(double q, double Emean, double Sigma)
		{
			double temp = (q - Emean) / Sigma / sqrt(2.);
			return 0.5 + 0.5 * erf(temp);
		}
		void GetEachfAndE(int N, double aE, double aSigma, std::vector<double> &f, std::vector<double> &E)
		{ 
			double LeftPoint, RightPoint;
			double Delta;
			LeftPoint = aE - 3. * aSigma; 
			RightPoint = aE + 3. * aSigma;
			Delta = 6. * aSigma / double(N);
			for(int i = 0; i < N; i++)
			{
				if(i == 0)
				{  
					E[i] = LeftPoint + 0.5 * Delta;
					f[i] = Pnormal(E[i] + 0.5 * Delta, aE, aSigma) - Pnormal(E[i] - 0.5 * Delta, aE, aSigma);
				}
				if(i > 0 && i < N - 1)
				{  
					E[i] = E[i - 1] + Delta;
					f[i] = Pnormal(E[i] + 0.5 * Delta, aE, aSigma) - Pnormal(E[i] - 0.5 * Delta, aE, aSigma);
				}
				if(i == N - 1)
				{ 
					E[i] = E[i - 1] + Delta;
					f[i] = Pnormal(E[i] + 0.5 * Delta, aE, aSigma) - Pnormal(E[i] - 0.5 * Delta, aE, aSigma);
				}
			}
		}
		void Normalization(int N, std::vector<double> &f)
		{  
			double Sum = 0.;
			for(int i = 0; i < N; i++) 
				Sum += f[i];
			for(int i = 0; i < N; i++) 
				f[i] = f[i] / Sum;
		}
		void Construct()
		{
			m_NKToOil = 21;
			m_fKToOil.resize(m_NKToOil);
			m_EKToOil.resize(m_NKToOil);
			GetEachfAndE(m_NKToOil, m_EmeanKToOil, m_SigmaKToOil, m_fKToOil, m_EKToOil); 
			Normalization(m_NKToOil, m_fKToOil);
			m_NKToGas = 21;
			m_fKToGas.resize(m_NKToGas); 
			m_EKToGas.resize(m_NKToGas);
			GetEachfAndE(m_NKToGas, m_EmeanKToGas, m_SigmaKToGas, m_fKToGas, m_EKToGas);
			Normalization(m_NKToGas, m_fKToGas);
			m_NOilToGas = 21;
			m_fOilToGas.resize(m_NOilToGas); 
			m_EOilToGas.resize(m_NOilToGas);
			GetEachfAndE(m_NOilToGas, m_EmeanOilToGas, m_SigmaOilToGas, m_fOilToGas, m_EOilToGas);
			Normalization(m_NOilToGas, m_fOilToGas);
			m_fOilToGasBak.resize(m_NOilToGas); 
			for(int i = 0; i < m_NOilToGas; i++) 
				m_fOilToGasBak[i] = m_fOilToGas[i];
			m_fOilToGasTemp.resize(m_NOilToGas); 
			for(int i = 0; i < m_NOilToGas; i++) 
				m_fOilToGasTemp[i] = m_fOilToGas[i];
		}
		void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,std::vector<double> &fLLNL,double FFLLNL, std::vector<double> &ELLNL,double &wBIw0)
		{  //�ֱ�����һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma����
			// ƽ�з�Ӧ����N_LLNL����ѧ����ϵ��fLLNL,Ƶ������FFLLNL�����ELLNL,�ܵ�ʣ�໯ѧ����ϵ��wBIw0
			wBIw0=0.;
			//double R=0.001986;//���峣�� ����λ Kcal/(mol*K)
			double R=0.008314472; //���峣�� KJ/(mol*K)
			//������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
			double a,b; // ���Ա仯��ϵ��
			a=(T-TLast)/(t-tLast);b=T-a*t;
			//����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
			int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
			double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
			double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
			double temp=0;
			std::vector<double>wiBIw0i;  //wi/w0i ,�����EasyRo�Ƶ��еĹ�ʽ��8��
			wiBIw0i.resize(N_LLNL);
			for(int i=0;i<N_LLNL;i++)
			{
				for(int j=0;j<N;j++)
				{
					tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
					temp+=(-FFLLNL*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
					tt1=tt2;
				}
				wiBIw0i[i]=exp(temp);
				fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //������һʱ��εĻ�ѧ����ϵ��
				wBIw0+=fLLNL[i];  // wBIw0Ϊ�ܵĻ�ѧ����ϵ��ʣ��ֵ
				tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
				temp=0;    //temp���¹���
			}
		}
		void Reactions(double TLast, double tLast, double T, double t)
		{  //���ʱ���ϵ�һ���ز��
			// ���л�̼���͡������ı仯��û�а����ѽⲿ��
			// ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
			//���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
			// ����ԭ������PetroMod��������Դ��Pepper��1995

			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			//����ΪI�͸��Ҹ��Ƚ�
			double InitwBIw0KToOil=0,InitwBIw0KToGas=0;  //��ʼʱ�̵ĸ��Ҹ���֣���ѧ����ϵ����֮��
			for(int i=0;i<m_NKToOil;i++)InitwBIw0KToOil+=m_fKToOil[i]; for(int i=0;i<m_NKToGas;i++)InitwBIw0KToGas+=m_fKToGas[i];
			FirstOrderReaction(TLast, tLast,T,t,m_NKToOil,m_fKToOil,m_FFKToOil,m_EKToOil,m_wBIw0KToOil);  // ���Ҹ������Ƚ�
			FirstOrderReaction(TLast, tLast,T,t,m_NKToGas,m_fKToGas,m_FFKToGas,m_EKToGas,m_wBIw0KToGas);  // ���Ҹ������Ƚ�
			m_OilPerInitTOC=m_HI0*(1.-m_G0)*(InitwBIw0KToOil-m_wBIw0KToOil)/1000.; //   //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������   OilPerInitTOC=HI0*(InitwBIw0KToOil-wBIw0KToOil)*KSF*(1.-G0);
			m_GasPerInitTOC=m_HI0*m_G0*(InitwBIw0KToGas-m_wBIw0KToGas)/1000.;       //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽��������  //       GasPerInitTOC=HI0*(InitwBIw0KToGas-wBIw0KToGas)*KSF*G0;
			m_OilGenerated=m_OilPerInitTOC+m_TI0/1000.; //  //���Ҹ���λ����ԭʼ�л�̼�ۼƵ��������������ڳ�ʼ��������ۻ�������Ϊ�ò������������ʼʱ�̴��ڵ�����֮��
			m_GasGenerated=m_GasPerInitTOC; // //���Ҹ���λ����ԭʼ�л�̼�ۼƵ����������� ��û�г�ʼ�Ĵ���������˳�ʼ�����ۻ����������Ǹò���������
			m_TOCKerogen=1.-m_W*m_TI0/1000.-m_W*m_OilPerInitTOC- m_W*m_GasPerInitTOC;  //��ָ���Ҹ��е��л�̼���� ,��Ҫ��ԭʼ��λ�л�̼-��ʼ���ڵ����������л�̼-�ò����ɵ��ͺ����е��л�̼
			m_TOCRemained=m_TOCKerogen; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
			// TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //Դ����ʣ����л�̼Ϊ���Ҹ��л�̼�������Դ�����ͺ����е��л�̼�Լ����ѽ�Ϊ��֮̿�� ,������Ҫ���ѽ��������ſ�֪�� �������ʽ�Ӳ����ã���ΪOilExisted���ܵ�������StrSeg���ܵĴ��ڵ��͵����������������� Reactions(...)����ʱ����ֵ��δ֪
			m_TOCInertKerogen=1.-m_W*m_TI0/1000.-m_W*m_HI0/1000.;   //���Ը��Ҹ�����
			m_TOCReactableKerogen=m_TOCKerogen-m_TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����
			m_TOCOilKerogen=m_W*m_HI0/1000.*(1.-m_G0)-m_W*m_OilPerInitTOC;   // ��һ����Ӧ���ʣ���͸��Ҹ� new added 20190412
			m_TOCGasKerogen=m_W*m_HI0/1000.*m_G0-m_W*m_GasPerInitTOC;        // ��һ����Ӧ���ʣ�������Ҹ� new added 20190412
			m_TR= (m_OilGenerated-m_TI0/1000.+m_GasGenerated)/(m_HI0/1000.);
			//����ת���ʵ��ڵ�λ����ԭʼ�л�̼�ۻ����ɵ����������Ե�λ����ԭʼ�л�̼����ָ��
		}
		void Reactions(double TLast, double tLast, double T, double t,OrganoFaciesKinetics &aOrganofacies)
		{  // �����Ҹ���֡��͡������ı仯��û�а����ѽⲿ��
			// ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
			//aOrganofaciesΪ��һ��ʱ��εĲ����ṹ
			//���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
			// ����ԭ������PetroMod��������Դ��BasinMod
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			//����Ϊ���Ҹ��Ƚ�
			//wBIw0KToOil=aOrganofacies->wBIw0KToOil;wBIw0KToGas=aOrganofacies->wBIw0KToGas;
			FirstOrderReaction(TLast, tLast,T,t,m_NKToOil,m_fKToOil,m_FFKToOil,m_EKToOil,m_wBIw0KToOil);  // ���Ҹ������Ƚ�
			FirstOrderReaction(TLast, tLast,T,t,m_NKToGas,m_fKToGas,m_FFKToGas,m_EKToGas,m_wBIw0KToGas);  // ���Ҹ������Ƚ�
			m_OilPerInitTOC=m_HI0*(1.-m_G0)*(aOrganofacies.m_wBIw0KToOil-m_wBIw0KToOil)/1000.;
			m_GasPerInitTOC=m_HI0*m_G0*(aOrganofacies.m_wBIw0KToGas-m_wBIw0KToGas)/1000.;;
			m_OilGenerated=aOrganofacies.m_OilGenerated+m_OilPerInitTOC; //
			m_GasGenerated=aOrganofacies.m_GasGenerated+m_GasPerInitTOC; //
			m_TOCKerogen=aOrganofacies.m_TOCKerogen-m_W*m_OilPerInitTOC-m_W*m_GasPerInitTOC; //��ָ���Ҹ��е��л�̼���� ,��Ҫ��ԭʼ��λ�л�̼-��ʼ���ڵ����������л�̼-�Ѿ��ۼ����ɵ��ͺ����е��л�̼
			m_TOCRemained=m_TOCKerogen; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
			//TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //Դ����ʣ����л�̼Ϊ���Ҹ��л�̼�������Դ�����ͺ����е��л�̼֮�� ,������Ҫ���ѽ��������ſ�֪��
			m_TOCInertKerogen=1.-m_W*m_TI0/1000.-m_W*m_HI0/1000.;   //���Ը��Ҹ�����
			m_TOCReactableKerogen=m_TOCKerogen-m_TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����,��ָ��λԭʼ�л�̼������Ӧ����
			m_TOCOilKerogen=aOrganofacies.m_TOCOilKerogen-m_W*m_OilPerInitTOC;   // ��Ӧ���ʣ���͸��Ҹ� new added 20190412
			m_TOCGasKerogen=aOrganofacies.m_TOCGasKerogen-m_W*m_GasPerInitTOC;        // ��Ӧ���ʣ�������Ҹ� new added 20190412
			m_TR= (m_OilGenerated-m_TI0/1000.+m_GasGenerated)/(m_HI0/1000.);
		}
		void GetfOilToGas()
		{  //��õ�һ�������ѽ�Ϊ���Ļ�ѧ����ϵ��������Դ���в�ͬ��Դ�͵ı��ʼ��㣻
			//��Ϊ��һ���ĸ��Ҹ��������Լ���һ�����ѽ�Ϊ��ʣ�����������������֮��ı���ȷ����ͬ��ѧ����ϵ������ռ�ı���
			double RatioKerogenOil,RatioCrackLeftedOil; //�ֱ�����һ�����Ҹ����ɵ��ͺ��ѽ�ʣ�������ռ�ı���
			double SumfOilToGas=0.;
			RatioKerogenOil=m_OilPerInitTOC*m_MassOfInitTOCTotal/m_OilExisted;
			RatioCrackLeftedOil=(m_MassOfInitTOCTotal*m_TI0/1000.-m_OilCracked)/m_OilExisted;
			for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]=m_fOilToGasBak[i]*RatioKerogenOil+m_fOilToGas[i]*RatioCrackLeftedOil;
			m_wBIw0OilToGas=1.;   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ
		}
		void OilCrackToGas(double TLast, double tLast, double T, double t)
		{    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			//����ΪStrSeg�д��ڵ����ѽ�Ϊ���Ͳ�����Ĺ��̡������ǵ�һ��ʱ�䲽����ʼʱ��Դ���д���ԭʼ����
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
			for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
			FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���Ҹ�������ѽ�Ϊ��
			m_OilExisted=m_MassOfInitTOCTotal*m_TI0/1000.;   //��ʼ��λ����Դ���ڵ��ʹ����� ������ԭʼ�л�̼��������TI0ֵ
			m_GasExisted=0.;
			m_GasCracked=m_OilExisted*m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ���� TI0/1000����OToGasFΪ��ת��Ϊ���ı�����
			m_ResidueCracked=m_OilExisted*(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_GasCrackedAdded=m_GasCracked;//�����ǵ�һ��ʱ�䲽��������ۻ��ѽ������ڳ�ʼ�ѽ�����
			m_ResidueCrackedAdded=m_ResidueCracked;
			m_OilCrackedAdded=m_OilCracked;
			m_OilExisted=m_OilExisted+m_OilPerInitTOC*m_MassOfInitTOCTotal-m_OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
			m_GasExisted =m_GasExisted+m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
			if(m_GasExisted < 1.0e-5)
				m_GasExisted = 1.0e-5;
			if(m_OilExisted < 1.0e-5)
				m_OilExisted = 1.0e-5;
			GetfOilToGas();
		}
		void GetfOilToGas(OrganoFaciesKinetics &aOrganofacies)
		{  //���ÿһ�������ѽ�Ϊ���Ļ�ѧ����ϵ��������Դ���в�ͬ��Դ�͵ı��ʼ��㣻
			//��Ϊÿһ���ĸ��Ҹ��������Լ���һ�����ѽ�Ϊ��ʣ�����������������֮��ı���ȷ����ͬ��ѧ����ϵ������ռ�ı���
			double RatioKerogenOil,RatioCrackLeftedOil; //�ֱ�����һ�����Ҹ����ɵ��ͺ��ѽ�ʣ�������ռ�ı���
			double SumfOilToGas=0.;
			RatioKerogenOil=m_OilPerInitTOC*m_MassOfInitTOCTotal/m_OilExisted;
			RatioCrackLeftedOil=(aOrganofacies.m_OilExisted-m_OilCracked)/m_OilExisted;
			Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
			for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]=m_fOilToGasBak[i]*RatioKerogenOil+m_fOilToGas[i]*RatioCrackLeftedOil;
			m_wBIw0OilToGas=1.;   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ
		}
		void OilCrackToGas(double TLast, double tLast, double T, double t,OrganoFaciesKinetics &aOrganofacies)
		{    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			//����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
			//����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
			m_GasCracked=aOrganofacies.m_OilExisted*m_OToGasF*(aOrganofacies.m_wBIw0OilToGas-m_wBIw0OilToGas);
			//m_tempwBIw0OilToGas=m_wBIw0OilToGas;
			//m_tempfOilToGas10=m_fOilToGas[10];
			m_ResidueCracked=aOrganofacies.m_OilExisted*(1.-m_OToGasF)*(aOrganofacies.m_wBIw0OilToGas-m_wBIw0OilToGas);
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_GasCrackedAdded=aOrganofacies.m_GasCrackedAdded+m_GasCracked;
			m_ResidueCrackedAdded=aOrganofacies.m_ResidueCrackedAdded+m_ResidueCracked;
			m_OilCrackedAdded=aOrganofacies.m_OilCrackedAdded+m_OilCracked;
			m_OilExisted=aOrganofacies.m_OilExisted+m_OilPerInitTOC*m_MassOfInitTOCTotal-m_OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
			m_GasExisted=aOrganofacies.m_GasExisted+m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
			if(m_GasExisted < 1.0e-5)
				m_GasExisted = 1.0e-5;
			if(m_OilExisted < 1.0e-5)
				m_OilExisted = 1.0e-5;
			GetfOilToGas(aOrganofacies);
			//m_tempfOilToGas10anot=m_fOilToGas[10];
		}
		void OilCrackToGasForNoOil(double TLast, double tLast, double T, double t,OrganoFaciesKinetics &aOrganofacies)
		{    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
			//����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
			//����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
			TLast+=273;T+=273;   //ת��Ϊ�����¶�
			tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
			t=t*1000000*365*24*3600; //������ת��Ϊ��
			//FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
			m_GasCracked=0;
			//m_tempwBIw0OilToGas=m_wBIw0OilToGas;
			//m_tempfOilToGas10=m_fOilToGas[10];
			m_ResidueCracked=0;
			m_OilCracked=m_GasCracked+m_ResidueCracked;
			m_GasCrackedAdded=aOrganofacies.m_GasCrackedAdded+m_GasCracked;
			m_ResidueCrackedAdded=aOrganofacies.m_ResidueCrackedAdded+m_ResidueCracked;
			m_OilCrackedAdded=aOrganofacies.m_OilCrackedAdded+m_OilCracked;
			m_OilExisted=aOrganofacies.m_OilExisted+m_OilPerInitTOC*m_MassOfInitTOCTotal-m_OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
			m_GasExisted=aOrganofacies.m_GasExisted+m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
			//GetfOilToGas(aOrganofacies);
			//m_tempfOilToGas10anot=m_fOilToGas[10];
		}
		void SetToItsOrifOilToGas()
		{  //��fOilToGas�趨Ϊԭʼֵ����Ҫ�����ڳ�ѹ�ز�ָ�ʱ���ж��ѭ���������Ӧ�ã�
			//��ʹ���¸�ѭ��ʱ�����õ� fOilToGas���µģ��������ϸ�ѭ��������¼�Ľ��
			for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]=m_fOilToGasBak[i];
		}
		void GetMKer()
		{   //���Դ���и��Ҹ����л�̼������
			m_MKerTotal=m_TOCKerogen*m_MassOfInitTOCTotal;
			m_MKerInert=m_TOCInertKerogen*m_MassOfInitTOCTotal;
			m_MKerReac= m_MKerTotal-m_MKerInert;
			m_MKerOil=m_TOCOilKerogen*m_MassOfInitTOCTotal;   //new added 20190412
			m_MKerGas=m_TOCGasKerogen*m_MassOfInitTOCTotal;   //new added 20190412
		}
	};
	struct CompositionalKinetics
	{
		//���ڶ���ֵĽṹ��
		//����Ϊ��Ҫ����Behar et al., 1997 Thermal cracking of kerogen in open and closed systems�����޸���Pepper 1995�л��������еĲ����͹�ʽ
		double m_W; //W = 0.85 kgC kgHC^-1  ,����λ�������ຬ�е�̼����   ������Cooles et al. (1986),���Ǽ򵥵ؼ������еĸ�ֵ��ΪW=0.85����
		double m_InitTOC;//���Ҹ���ԭʼTOC������ԭʼTOCֻ��ģ��������֪�������ֻ�����һ��StrSeg��ֵ
		double m_MassOfInitTOCTotal; //���Ҹ�ԭʼ�л�̼�ܵ�����   �����ֻ��һ�����͸��Ҹ�����ñ�������һ���ظ�
		//����Ϊ���Ҹ��Ķ���ѧ����
		double m_TI0;  // TI0=S10/TOC0 �������ﶼ�����ʼ��TOC0=1�����TI0=S10�������λԭʼ�л�̼�ĵ�λ��g,��TI0��λ��mgHC/gTOC,�����λԭʼ�л�̼��λ��kg,��TI0��λ��gHC/kgTOC
		double m_HI0; //���Ҹ��ĳ�ʼ��ָ����HI0=S20/TOC0����ָ��HI������λ�����л�̼���������������ָ���ṩ�˳����л����з�Ӧ���Ҹ�����Ը��Ҹ��ı���ָʾ��
		double m_QI0; // QI0=(S10+S20)/TOC0
		double m_PI0; //PI0=S10/(S10+S20)
		//  double G0; //���Դ����ʼ���������Ҹ����ܵĳ�ʼ���ͺ��������Ҹ�֮�͵ı�ֵ����G, which is simply the PGC(Pyrolysis-gas chromatography)-derived mass fraction of gas in the S2 yield����ֵ���������KToGasF����KToOilF=1-KToGasF
		int m_NF; //�����������Behar 1997ģ�ͣ��������4
		std::vector<double> m_GF0; //   ���Դ����ʼ��������ָ��Ҹ�ռ�ܵĳ�ʼ�������Ҹ��İٷֱ�
	 
		double m_FFKToC1; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		int m_NKToC1;//��C1��ָ��Ҹ���ƽ�з�Ӧ�����
		std::vector<double> m_fKToC1;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_EKToC1;//��ܣ�Activation Energy����KJ/mole��

		double m_FFKToC2_C5; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		int m_NKToC2_C5;//����C2_C5��ָ��Ҹ�ƽ�з�Ӧ�����
		std::vector<double> m_fKToC2_C5;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_EKToC2_C5;//��ܣ�Activation Energy����KJ/mole��

		double m_FFKToC6_C14; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		int m_NKToC6_C14;//����C6_C14��ָ��Ҹ�ƽ�з�Ӧ�����
		std::vector<double> m_fKToC6_C14;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_EKToC6_C14;//��ܣ�Activation Energy����KJ/mole��

		double m_FFKToC15Plus; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
		int m_NKToC15Plus;//����C15+��ָ��Ҹ�ƽ�з�Ӧ�����
		std::vector<double> m_fKToC15Plus;//�ǻ�ѧ����ϵ����Stoichiometric Factor��
		std::vector<double> m_EKToC15Plus;//��ܣ�Activation Energy����KJ/mole��

		double m_FFOilToGas; //Frequency factor
		double m_EmeanOilToGas;
		double m_SigmaOilToGas; //�ֱ������ѽ�Ϊ���Ķ���ѧ������������̬�ֲ��ľ��ʺͱ�׼��
		int m_NOilToGas;//���ѽ�Ϊ����ƽ�з�Ӧ����� ��������̬�ֲ��Ĳ�����ɢ�ĸ���
		std::vector<double> m_fOilToGas;//�ǻ�ѧ����ϵ����Stoichiometric Factor�� ��ͨ������̬�ֲ���ɢ���õ�
		std::vector<double> m_fOilToGasBak; //���ݵļ���ϵ������Զ��¼���ʼ�Ļ�ѧ����ϵ��ֵ
		std::vector<double> m_EOilToGas;//��ܣ�Activation Energy����KJ/mole����ͨ������̬�ֲ���ɢ���õ�
		double m_OToGasF; //���ѽ�Ϊ���ı���

		double m_wBIw0KToOil;
		double m_wBIw0KToGas;
		double m_wBIw0OilToGas;//�ֱ����͸��Ҹ��������͡������Լ����ѽ���������µ��ܵ�ʣ�໯ѧ����ϵ����ԭʼ���ܵĻ�ѧ����ϵ��Ϊ1
		double m_wBIw0KToC1;
		double m_wBIw0KToC2_C5;
		double m_wBIw0KToC6_C14;
		double m_wBIw0KToC15Plus;//   , wBIw0OilToGas
		double m_wBIw0K; //���Ҹ� �ܵ�ʣ�໯ѧ����ϵ����ԭʼΪ1��ͨ�����Ҹ��������͡����������µ��ܵ�ʣ�໯ѧ����ϵ���ֱ���Ը��Ҹ������͵ı��ʺ��������ı���֮����Ӷ��õ���
		double m_C1PerInitTOC;
		double m_C2_C5PerInitTOC;
		double m_C6_C14PerInitTOC;
		double m_C15PlusPerInitTOC;//��λ����ԭʼ�л�̼��InitTOC������һʱ��ε����ɵ������
		double m_OilPerInitTOC; //��λ����ԭʼ�л�̼��InitTOC������һʱ��ε�������
		double m_GasPerInitTOC; //��λ����ԭʼ�л�̼��InitTOC������һʱ��ε�������

		double m_TOCReactableKerogen;
		double m_TOCInertKerogen; //�ֱ��ǿɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ� ����ָ��λԭʼ�л�̼���ڳ�ʼ״̬�Լ���Ӧ�����пɷ�Ӧ���Ҹ��Ͷ��Ը��Ҹ�������
		double m_TOCKerogen; //���Ҹ��л�̼ʣ���� ����ָ��λ����ԭʼ���Ҹ��Ĳ�����
		double m_TOCOilKerogen;
		double m_TOCGasKerogen; // new added 20190412�ֱ��ǿɷ�Ӧ�͸��Ҹ��������Ҹ� ����ָ��λԭʼ�л�̼���ڳ�ʼ״̬�Լ���Ӧ�����пɷ�Ӧ�͸��Ҹ��������Ҹ�������
		double m_TOCRemained; //�����л�̼ʣ���� ����ָ��λ����ԭʼ�л�̼���ݻ������еĲ����� ���������Ҹ��л�̼ʣ���� +Դ�����������л�̼����+���ѽ�����Ľ�̿��
		double m_C1Generated;
		double m_C2_C5Generated;
		double m_C6_C14Generated;
		double m_C15PlusGenerated;// ���Ҹ���λ����ԭʼ�л�̼�ۼƵ����������
		double m_OilGenerated;
		double m_GasGenerated; //���Ҹ���λ����ԭʼ�л�̼�ۼƵ���������������
		double m_RatioC6_C14ToTI0; //TI0��C2_C14�ı���
		double m_TR; //Դ�ҵ�����ת����, ��ԭʼ�ɽ�����Ҹ��л�̼ת��Ϊ�ͺ����е��л�̼����
		//���������ѽ��йصĶ��Ƕ�Ӧ����������ԭʼ�л�̼������
		double m_C1Existed;
		double m_C2_C5Existed;
		double m_C6_C14Existed;
		double m_C15PlusExisted;   //ָ���Ǵ�����Դ���еĸ����
		double m_OilExisted; //ָ���Ǵ�����Դ���е������
		double m_GasExisted; //ָ���Ǵ�����Դ���е������
		double m_ResidueExisted; //ָ������Դ���е����ѽ�Ϊ��������
		double m_C1Cracked;
		double m_C2_C5Cracked; // ָ����ÿһ�����ѽ��C1�Լ�C2_C5����
		double m_GasCracked;//ָ����ÿһ�����ѽ������
		double m_C1CrackedAdded;
		double m_C2_C5CrackedAdded; // ָ����ÿһ�����ѽ��C1�Լ�C2_C5����
		double m_GasCrackedAdded; //ָÿһ���ѽ������ۼ���
		double m_ResidueCracked; // ָ����ÿһ�����ѽ�Ĳ�������
		double m_ResidueCrackedAdded; // ָ����ÿһ�����ѽ�Ĳ�������ۼ���
		double m_C6_C14Cracked;
		double m_C15PlusCracked;
		double m_OilCracked;//ÿһ���͵��ѽ���
		double m_C6_C14CrackedAdded;
		double m_C15PlusCrackedAdded;
		double m_OilCrackedAdded;//ÿһ���͵��ѽ������ۼ���

		double m_RatioCrackedC1; // ���ѽ�Ϊ����C1�ı���
		double m_RatioCrackedC6_C14; //���ѽ���C6_C14�ı���
		double m_MKerTotal; //�ܵĸ��Ҹ��л�̼�����������������ѽ�Ľ�̿���� ���¼���20170908
		double m_MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
		double m_MKerOil;        //new added 20190412
		double m_MKerGas;        //new added 20190412
		double m_MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
		// double OToResidueF; //���ѽ�Ϊ������ı�������� OToResidueF=1-OToGasF
		CompositionalKinetics()
		{
			m_MassOfInitTOCTotal = 0;
			BeharKinetics aBeharKinetics;
			aBeharKinetics=TI;
			switch(aBeharKinetics)
			{  //������TI���Ҹ��Ĳ�����������в���Editor�����������͸��Ҹ��Ĳ���

			case TI:
				m_W=0.8; //W = 0.8 kgC kgHC^-1  ,����λ�������ຬ�е�̼����
				//����Ϊ���Ҹ��Ķ���ѧ����
				m_TI0=0;  // TI0=S10/TOC0 �������ﶼ�����ʼ��TOC0=1�����TI0=S10�������λԭʼ�л�̼�ĵ�λ��g,��TI0��λ��mgHC/gTOC,�����λԭʼ�л�̼��λ��kg,��TI0��λ��gHC/kgTOC
				if(m_TI0<1.0e-10)m_TI0=1.0e-10;  //���TI0��ֵΪ0��TI0Ҫ��һ���ǳ�Сֵ���Է�ֹ��0���������
				m_HI0=918.3; //���Ҹ��ĳ�ʼ��ָ����HI0=S20/TOC0����ָ��HI������λ�����л�̼���������������ָ���ṩ�˳����л����з�Ӧ���Ҹ�����Ը��Ҹ��ı���ָʾ��
				m_NF=4; //�����������Behar 1997ģ�ͣ��������4
				m_GF0.resize(m_NF);    //ÿ����ָ��Ҹ��İٷֱ�
				m_GF0[0]=0.0179,m_GF0[1]=0.0785,m_GF0[2]=0.0992,m_GF0[3]=0.8044;

				m_FFKToC1=7.4e13; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
				m_NKToC1=8;//��C1��ָ��Ҹ���ƽ�з�Ӧ�����
				m_fKToC1.resize(m_NKToC1);  m_EKToC1.resize(m_NKToC1);
				m_fKToC1[0]=0.0244;m_fKToC1[1]=0.3841;m_fKToC1[2]=0.1890;m_fKToC1[3]=0.1220;m_fKToC1[4]=0.0976;m_fKToC1[5]=0.0793;m_fKToC1[6]=0.0793;m_fKToC1[7]=0.0244;
				m_EKToC1[0]=52;m_EKToC1[1]=54;m_EKToC1[2]=56;m_EKToC1[3]=58;m_EKToC1[4]=60;m_EKToC1[5]=62;m_EKToC1[6]=64;m_EKToC1[7]=66;

				m_FFKToC2_C5=7.4e13; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
				m_NKToC2_C5=2;//����C2_C5��ָ��Ҹ�ƽ�з�Ӧ�����
				m_fKToC2_C5.resize(m_NKToC2_C5);m_EKToC2_C5.resize(m_NKToC2_C5);
				m_fKToC2_C5[0]=0.0485; m_fKToC2_C5[1]=0.9515;
				m_EKToC2_C5[0]=52; m_EKToC2_C5[1]=54;

				m_FFKToC6_C14=7.4e13; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
				m_NKToC6_C14=2;//����C6_C14��ָ��Ҹ�ƽ�з�Ӧ�����
				m_fKToC6_C14.resize(m_NKToC6_C14);m_EKToC6_C14.resize(m_NKToC6_C14);
				m_fKToC6_C14[0]=0.0889; m_fKToC6_C14[1]=0.9111;
				m_EKToC6_C14[0]=52; m_EKToC6_C14[1]=54;

				m_FFKToC15Plus=7.4e13; //Frequency factor  ��Ƶ�����ӣ���A ����λ��s^-1,Ϊ��ֵ
				m_NKToC15Plus=1;//����C15+��ָ��Ҹ�ƽ�з�Ӧ�����
				m_fKToC15Plus.resize(m_NKToC15Plus);m_EKToC15Plus.resize(m_NKToC15Plus);
				m_fKToC15Plus[0]=1.0;
				m_EKToC15Plus[0]=54;
				break;
			case TII:
				;
				break;
			case TIIS:
				;
				break;
			case TIIIMahak:
				;
				break;
			case TIIINorthSea:
				;
				break;
			};
		}
		CompositionalKinetics(const CompositionalKinetics &other)
		{
			*this = other;
		}
		const CompositionalKinetics &operator=(const CompositionalKinetics &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_W = other.m_W;
			m_InitTOC = other.m_InitTOC;
			m_MassOfInitTOCTotal = other.m_MassOfInitTOCTotal;

			m_TI0 = other.m_TI0;
			m_HI0 = other.m_HI0; 
			m_QI0 = other.m_QI0;
			m_PI0 = other.m_PI0;
			m_NF = other.m_NF; 
			m_GF0 = other.m_GF0;

			m_FFKToC1 = other.m_FFKToC1;
			m_NKToC1 = other.m_NKToC1;
			m_fKToC1 = other.m_fKToC1;
			m_EKToC1 = other.m_EKToC1;

			m_FFKToC2_C5 = other.m_FFKToC2_C5;
			m_NKToC2_C5 = other.m_NKToC2_C5;
			m_fKToC2_C5 = other.m_fKToC2_C5;
			m_EKToC2_C5 = other.m_EKToC2_C5;

			m_FFKToC6_C14 = other.m_FFKToC6_C14;
			m_NKToC6_C14 = other.m_NKToC6_C14;
			m_fKToC6_C14 = other.m_fKToC6_C14;
			m_EKToC6_C14 = other.m_EKToC6_C14;

			m_FFKToC15Plus = other.m_FFKToC15Plus;
			m_NKToC15Plus = other.m_NKToC15Plus;
			m_fKToC15Plus = other.m_fKToC15Plus;
			m_EKToC15Plus = other.m_EKToC15Plus;

			m_FFOilToGas = other.m_FFOilToGas;
			m_EmeanOilToGas = other.m_EmeanOilToGas;
			m_SigmaOilToGas = other.m_SigmaOilToGas;
			m_NOilToGas = other.m_NOilToGas;
			m_fOilToGas = other.m_fOilToGas;
			m_fOilToGasBak = other.m_fOilToGasBak;
			m_EOilToGas = other.m_EOilToGas;
			m_OToGasF = other.m_OToGasF;

			m_wBIw0KToOil = other.m_wBIw0KToOil;
			m_wBIw0KToGas = other.m_wBIw0KToGas;
			m_wBIw0OilToGas = other.m_wBIw0OilToGas;
			m_wBIw0KToC1 = other.m_wBIw0KToC1;
			m_wBIw0KToC2_C5 = other.m_wBIw0KToC2_C5;
			m_wBIw0KToC6_C14 = other.m_wBIw0KToC6_C14;
			m_wBIw0KToC15Plus = other.m_wBIw0KToC15Plus;
			m_wBIw0K = other.m_wBIw0K;
			m_C1PerInitTOC = other.m_C1PerInitTOC;
			m_C2_C5PerInitTOC = other.m_C2_C5PerInitTOC;
			m_C6_C14PerInitTOC = other.m_C6_C14PerInitTOC;
			m_C15PlusPerInitTOC = other.m_C15PlusPerInitTOC;
			m_OilPerInitTOC = other.m_OilPerInitTOC;
			m_GasPerInitTOC = other.m_GasPerInitTOC;

			m_TOCReactableKerogen = other.m_TOCReactableKerogen;
			m_TOCInertKerogen = other.m_TOCInertKerogen;
			m_TOCKerogen = other.m_TOCKerogen;
			m_TOCOilKerogen = other.m_TOCOilKerogen;
			m_TOCGasKerogen = other.m_TOCGasKerogen;
			m_TOCRemained = other.m_TOCRemained;
			m_C1Generated = other.m_C1Generated;
			m_C2_C5Generated = other.m_C2_C5Generated;
			m_C6_C14Generated = other.m_C6_C14Generated;
			m_C15PlusGenerated = other.m_C15PlusGenerated;
			m_OilGenerated = other.m_OilGenerated;
			m_GasGenerated = other.m_GasGenerated;
			m_RatioC6_C14ToTI0 = other.m_RatioC6_C14ToTI0;
			m_TR = other.m_TR;

			m_C1Existed = other.m_C1Existed;
			m_C2_C5Existed = other.m_C2_C5Existed;
			m_C6_C14Existed = other.m_C6_C14Existed;
			m_C15PlusExisted = other.m_C15PlusExisted;
			m_OilExisted = other.m_OilExisted;
			m_GasExisted = other.m_GasExisted;
			m_ResidueExisted = other.m_ResidueExisted;
			m_C1Cracked = other.m_C1Cracked;
			m_C2_C5Cracked = other.m_C2_C5Cracked;
			m_GasCracked = other.m_GasCracked;
			m_C1CrackedAdded = other.m_C1CrackedAdded;
			m_C2_C5CrackedAdded = other.m_C2_C5CrackedAdded;
			m_GasCrackedAdded = other.m_GasCrackedAdded;
			m_ResidueCracked = other.m_ResidueCracked;
			m_ResidueCrackedAdded = other.m_ResidueCrackedAdded;
			m_C6_C14Cracked = other.m_C6_C14Cracked;
			m_C15PlusCracked = other.m_C15PlusCracked;
			m_OilCracked = other.m_OilCracked;
			m_C6_C14CrackedAdded = other.m_C6_C14CrackedAdded;
			m_C15PlusCrackedAdded = other.m_C15PlusCrackedAdded;
			m_OilCrackedAdded = other.m_OilCrackedAdded;

			m_RatioCrackedC1 = other.m_RatioCrackedC1;
			m_RatioCrackedC6_C14 = other.m_RatioCrackedC6_C14;
			m_MKerTotal = other.m_MKerTotal;
			m_MKerReac = other.m_MKerReac;
			m_MKerOil = other.m_MKerOil;
			m_MKerGas = other.m_MKerGas;
			m_MKerInert = other.m_MKerInert;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_W;
			curSize += sizeof(double);//double m_InitTOC;
			curSize += sizeof(double);//double m_MassOfInitTOCTotal;
			curSize += sizeof(double);//double m_TI0;
			curSize += sizeof(double);//double m_HI0;
			curSize += sizeof(double);//double m_QI0;
			curSize += sizeof(double);//double m_PI0;
			curSize += sizeof(int);//int m_NF;
			curSize += (sizeof(int) + m_GF0.size() * sizeof(double));//std::vector<double> m_GF0;
			curSize += sizeof(double);//double m_FFKToC1;
			curSize += sizeof(int);//int m_NKToC1;
			curSize += (sizeof(int) + m_fKToC1.size() * sizeof(double));//std::vector<double> m_fKToC1;
			curSize += (sizeof(int) + m_EKToC1.size() * sizeof(double));//std::vector<double> m_EKToC1;
			curSize += sizeof(double);//double m_FFKToC2_C5;
			curSize += sizeof(int);//int m_NKToC2_C5;
			curSize += (sizeof(int) + m_fKToC2_C5.size() * sizeof(double));//std::vector<double> m_fKToC2_C5;
			curSize += (sizeof(int) + m_EKToC2_C5.size() * sizeof(double));//std::vector<double> m_EKToC2_C5;
			curSize += sizeof(double);//double m_FFKToC6_C14;
			curSize += sizeof(int);//int m_NKToC6_C14;
			curSize += (sizeof(int) + m_fKToC6_C14.size() * sizeof(double));//std::vector<double> m_fKToC6_C14;
			curSize += (sizeof(int) + m_EKToC6_C14.size() * sizeof(double));//std::vector<double> m_EKToC6_C14;
			curSize += sizeof(double);//double m_FFKToC15Plus;
			curSize += sizeof(int);//int m_NKToC15Plus;
			curSize += (sizeof(int) + m_fKToC15Plus.size() * sizeof(double));//std::vector<double> m_fKToC15Plus;
			curSize += (sizeof(int) + m_EKToC15Plus.size() * sizeof(double));//std::vector<double> m_EKToC15Plus;
			curSize += sizeof(double);//double m_FFOilToGas;
			curSize += sizeof(double);//double m_EmeanOilToGas;
			curSize += sizeof(double);//double m_SigmaOilToGas;
			curSize += sizeof(int);//int m_NOilToGas;
			curSize += (sizeof(int) + m_fOilToGas.size() * sizeof(double));//std::vector<double> m_fOilToGas;
			curSize += (sizeof(int) + m_fOilToGasBak.size() * sizeof(double));//std::vector<double> m_fOilToGasBak;
			curSize += (sizeof(int) + m_EOilToGas.size() * sizeof(double));//std::vector<double> m_EOilToGas;
			curSize += sizeof(double);//double m_OToGasF;
			curSize += sizeof(double);//double m_wBIw0KToOil;
			curSize += sizeof(double);//double m_wBIw0KToGas;
			curSize += sizeof(double);//double m_wBIw0OilToGas;
			curSize += sizeof(double);//double m_wBIw0KToC1;
			curSize += sizeof(double);//double m_wBIw0KToC2_C5;
			curSize += sizeof(double);//double m_wBIw0KToC6_C14;
			curSize += sizeof(double);//double m_wBIw0KToC15Plus;
			curSize += sizeof(double);//double m_wBIw0K;
			curSize += sizeof(double);//double m_C1PerInitTOC;
			curSize += sizeof(double);//double m_C2_C5PerInitTOC;
			curSize += sizeof(double);//double m_C6_C14PerInitTOC;
			curSize += sizeof(double);//double m_C15PlusPerInitTOC;
			curSize += sizeof(double);//double m_OilPerInitTOC;
			curSize += sizeof(double);//double m_GasPerInitTOC;
			curSize += sizeof(double);//double m_TOCReactableKerogen;
			curSize += sizeof(double);//double m_TOCInertKerogen; 
			curSize += sizeof(double);//double m_TOCKerogen;
			curSize += sizeof(double);//double m_TOCOilKerogen;
			curSize += sizeof(double);//double m_TOCGasKerogen;
			curSize += sizeof(double);//double m_TOCRemained;
			curSize += sizeof(double);//double m_C1Generated;
			curSize += sizeof(double);//double m_C2_C5Generated;
			curSize += sizeof(double);//double m_C6_C14Generated;
			curSize += sizeof(double);//double m_C15PlusGenerated;
			curSize += sizeof(double);//double m_OilGenerated;
			curSize += sizeof(double);//double m_GasGenerated;
			curSize += sizeof(double);//double m_RatioC6_C14ToTI0;
			curSize += sizeof(double);//double m_TR;
			curSize += sizeof(double);//double m_C1Existed;
			curSize += sizeof(double);//double m_C2_C5Existed;
			curSize += sizeof(double);//double m_C6_C14Existed;
			curSize += sizeof(double);//double m_C15PlusExisted;
			curSize += sizeof(double);//double m_OilExisted;
			curSize += sizeof(double);//double m_GasExisted;
			curSize += sizeof(double);//double m_ResidueExisted;
			curSize += sizeof(double);//double m_C1Cracked;
			curSize += sizeof(double);//double m_C2_C5Cracked; 
			curSize += sizeof(double);//double m_GasCracked;
			curSize += sizeof(double);//double m_C1CrackedAdded;
			curSize += sizeof(double);//double m_C2_C5CrackedAdded;
			curSize += sizeof(double);//double m_GasCrackedAdded;
			curSize += sizeof(double);//double m_ResidueCracked;
			curSize += sizeof(double);//double m_ResidueCrackedAdded;
			curSize += sizeof(double);//double m_C6_C14Cracked;
			curSize += sizeof(double);//double m_C15PlusCracked;
			curSize += sizeof(double);//double m_OilCracked;
			curSize += sizeof(double);//double m_C6_C14CrackedAdded;
			curSize += sizeof(double);//double m_C15PlusCrackedAdded;
			curSize += sizeof(double);//double m_OilCrackedAdded;
			curSize += sizeof(double);//double m_RatioCrackedC1;
			curSize += sizeof(double);//double m_RatioCrackedC6_C14;
			curSize += sizeof(double);//double m_MKerTotal;
			curSize += sizeof(double);//double m_MKerReac;
			curSize += sizeof(double);//double m_MKerOil;
			curSize += sizeof(double);//double m_MKerGas;
			curSize += sizeof(double);//double m_MKerInert;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_W), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_InitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MassOfInitTOCTotal), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TI0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_HI0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_QI0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_PI0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NF), sizeof(int));data += sizeof(int);
			int GF0size = m_GF0.size();
			memcpy(data, &GF0size, sizeof(int));data += sizeof(int);
			for(int j = 0; j < GF0size; j++)
			{
				memcpy(data, &(m_GF0[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_FFKToC1), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NKToC1), sizeof(int));data += sizeof(int);
			int fKToC1size = m_fKToC1.size();
			memcpy(data, &fKToC1size, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fKToC1size; j++)
			{
				memcpy(data, &(m_fKToC1[j]), sizeof(double));data += sizeof(double);
			}
			int EKToC1size = m_EKToC1.size();
			memcpy(data, &EKToC1size, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EKToC1size; j++)
			{
				memcpy(data, &(m_EKToC1[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_FFKToC2_C5), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NKToC2_C5), sizeof(int));data += sizeof(int);
			int fKToC2_C5size = m_fKToC2_C5.size();
			memcpy(data, &fKToC2_C5size, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fKToC2_C5size; j++)
			{
				memcpy(data, &(m_fKToC2_C5[j]), sizeof(double));data += sizeof(double);
			}
			int EKToC2_C5size = m_EKToC2_C5.size();
			memcpy(data, &EKToC2_C5size, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EKToC2_C5size; j++)
			{
				memcpy(data, &(m_EKToC2_C5[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_FFKToC6_C14), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NKToC6_C14), sizeof(int));data += sizeof(int);
			int fKToC6_C14size = m_fKToC6_C14.size();
			memcpy(data, &fKToC6_C14size, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fKToC6_C14size; j++)
			{
				memcpy(data, &(m_fKToC6_C14[j]), sizeof(double));data += sizeof(double);
			}
			int EKToC6_C14size = m_EKToC6_C14.size();
			memcpy(data, &EKToC6_C14size, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EKToC6_C14size; j++)
			{
				memcpy(data, &(m_EKToC6_C14[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_FFKToC15Plus), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NKToC15Plus), sizeof(int));data += sizeof(int);
			int fKToC15Plussize = m_fKToC15Plus.size();
			memcpy(data, &fKToC15Plussize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fKToC15Plussize; j++)
			{
				memcpy(data, &(m_fKToC15Plus[j]), sizeof(double));data += sizeof(double);
			}
			int EKToC15Plussize = m_EKToC15Plus.size();
			memcpy(data, &EKToC15Plussize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EKToC15Plussize; j++)
			{
				memcpy(data, &(m_EKToC15Plus[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_FFOilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_EmeanOilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_SigmaOilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_NOilToGas), sizeof(int));data += sizeof(int);
			int fOilToGassize = m_fOilToGas.size();
			memcpy(data, &fOilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fOilToGassize; j++)
			{
				memcpy(data, &(m_fOilToGas[j]), sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize = m_fOilToGasBak.size();
			memcpy(data, &fOilToGasBaksize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < fOilToGasBaksize; j++)
			{
				memcpy(data, &(m_fOilToGasBak[j]), sizeof(double));data += sizeof(double);
			}
			int EOilToGassize = m_EOilToGas.size();
			memcpy(data, &EOilToGassize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < EOilToGassize; j++)
			{
				memcpy(data, &(m_EOilToGas[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_OToGasF), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0KToOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0KToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0OilToGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0KToC1), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0KToC2_C5), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0KToC6_C14), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0KToC15Plus), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_wBIw0K), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C1PerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C2_C5PerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C6_C14PerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C15PlusPerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilPerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasPerInitTOC), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCReactableKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCInertKerogen), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_TOCKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCOilKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCGasKerogen), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TOCRemained), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C1Generated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C2_C5Generated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C6_C14Generated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C15PlusGenerated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilGenerated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasGenerated), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_RatioC6_C14ToTI0), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_TR), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C1Existed), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C2_C5Existed), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C6_C14Existed), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C15PlusExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueExisted), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C1Cracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C2_C5Cracked), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_GasCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C1CrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C2_C5CrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_GasCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_ResidueCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C6_C14Cracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C15PlusCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCracked), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C6_C14CrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_C15PlusCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_OilCrackedAdded), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_RatioCrackedC1), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_RatioCrackedC6_C14), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerTotal), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerReac), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerOil), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerGas), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_MKerInert), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_W), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_InitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MassOfInitTOCTotal), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TI0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_HI0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_QI0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_PI0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NF), data, sizeof(int));data += sizeof(int);
			int GF0size;
			memcpy(&GF0size, data, sizeof(int));data += sizeof(int);
			m_GF0.resize(GF0size);
			for(int j = 0; j < GF0size; j++)
			{
				memcpy(&(m_GF0[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_FFKToC1), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NKToC1), data, sizeof(int));data += sizeof(int);
			int fKToC1size;
			memcpy(&fKToC1size, data, sizeof(int));data += sizeof(int);
			m_fKToC1.resize(fKToC1size);
			for(int j = 0; j < fKToC1size; j++)
			{
				memcpy(&(m_fKToC1[j]), data, sizeof(double));data += sizeof(double);
			}
			int EKToC1size;
			memcpy(&EKToC1size, data, sizeof(int));data += sizeof(int);
			m_EKToC1.resize(EKToC1size);
			for(int j = 0; j < EKToC1size; j++)
			{
				memcpy(&(m_EKToC1[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_FFKToC2_C5), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NKToC2_C5), data, sizeof(int));data += sizeof(int);
			int fKToC2_C5size;
			memcpy(&fKToC2_C5size, data, sizeof(int));data += sizeof(int);
			m_fKToC2_C5.resize(fKToC2_C5size);
			for(int j = 0; j < fKToC2_C5size; j++)
			{
				memcpy(&(m_fKToC2_C5[j]), data, sizeof(double));data += sizeof(double);
			}
			int EKToC2_C5size;
			memcpy(&EKToC2_C5size, data, sizeof(int));data += sizeof(int);
			m_EKToC2_C5.resize(EKToC2_C5size);
			for(int j = 0; j < EKToC2_C5size; j++)
			{
				memcpy(&(m_EKToC2_C5[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_FFKToC6_C14), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NKToC6_C14), data, sizeof(int));data += sizeof(int);
			int fKToC6_C14size;
			memcpy(&fKToC6_C14size, data, sizeof(int));data += sizeof(int);
			m_fKToC6_C14.resize(fKToC6_C14size);
			for(int j = 0; j < fKToC6_C14size; j++)
			{
				memcpy(&(m_fKToC6_C14[j]), data, sizeof(double));data += sizeof(double);
			}
			int EKToC6_C14size;
			memcpy(&EKToC6_C14size, data, sizeof(int));data += sizeof(int);
			m_EKToC6_C14.resize(EKToC6_C14size);
			for(int j = 0; j < EKToC6_C14size; j++)
			{
				memcpy(&(m_EKToC6_C14[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_FFKToC15Plus), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NKToC15Plus), data, sizeof(int));data += sizeof(int);
			int fKToC15Plussize;
			memcpy(&fKToC15Plussize, data, sizeof(int));data += sizeof(int);
			m_fKToC15Plus.resize(fKToC15Plussize);
			for(int j = 0; j < fKToC15Plussize; j++)
			{
				memcpy(&(m_fKToC15Plus[j]), data, sizeof(double));data += sizeof(double);
			}
			int EKToC15Plussize;
			memcpy(&EKToC15Plussize, data, sizeof(int));data += sizeof(int);
			m_EKToC15Plus.resize(EKToC15Plussize);
			for(int j = 0; j < EKToC15Plussize; j++)
			{
				memcpy(&(m_EKToC15Plus[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_FFOilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_EmeanOilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_SigmaOilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_NOilToGas), data, sizeof(int));data += sizeof(int);
			int fOilToGassize;
			memcpy(&fOilToGassize, data, sizeof(int));data += sizeof(int);
			m_fOilToGas.resize(fOilToGassize);
			for(int j = 0; j < fOilToGassize; j++)
			{
				memcpy(&(m_fOilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			int fOilToGasBaksize;
			memcpy(&fOilToGasBaksize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasBak.resize(fOilToGasBaksize);
			for(int j = 0; j < fOilToGasBaksize; j++)
			{
				memcpy(&(m_fOilToGasBak[j]), data, sizeof(double));data += sizeof(double);
			}
			int EOilToGassize;
			memcpy(&EOilToGassize, data, sizeof(int));data += sizeof(int);
			m_EOilToGas.resize(EOilToGassize);
			for(int j = 0; j < EOilToGassize; j++)
			{
				memcpy(&(m_EOilToGas[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_OToGasF), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0KToOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0KToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0OilToGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0KToC1), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0KToC2_C5), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0KToC6_C14), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0KToC15Plus), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_wBIw0K), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C1PerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C2_C5PerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C6_C14PerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C15PlusPerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilPerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasPerInitTOC), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCReactableKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCInertKerogen), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_TOCKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCOilKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCGasKerogen), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TOCRemained), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C1Generated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C2_C5Generated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C6_C14Generated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C15PlusGenerated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilGenerated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasGenerated), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_RatioC6_C14ToTI0), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_TR), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C1Existed), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C2_C5Existed), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C6_C14Existed), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C15PlusExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueExisted), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C1Cracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C2_C5Cracked), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_GasCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C1CrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C2_C5CrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_GasCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_ResidueCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C6_C14Cracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C15PlusCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCracked), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C6_C14CrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_C15PlusCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_OilCrackedAdded), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_RatioCrackedC1), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_RatioCrackedC6_C14), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerTotal), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerReac), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerOil), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerGas), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_MKerInert), data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, CompositionalKinetics &compositionalkinetics)
		{
			os << "\r\n>>>>>>>>>>>>>>>CompositionalKinetics parameter as flow:"; 
			os << "\r\n---- ---- ---- W:" << compositionalkinetics.m_W;
			os << "\r\n---- ---- ---- InitTOC:" << compositionalkinetics.m_InitTOC;
			os << "\r\n---- ---- ---- MassOfInitTOCTotal:" << compositionalkinetics.m_MassOfInitTOCTotal;
			os << "\r\n---- ---- ---- TI0:" << compositionalkinetics.m_TI0;
			os << "\r\n---- ---- ---- HI0:" << compositionalkinetics.m_HI0; 
			os << "\r\n---- ---- ---- QI0:" << compositionalkinetics.m_QI0;
			os << "\r\n---- ---- ---- PI0:" << compositionalkinetics.m_PI0;
			os << "\r\n---- ---- ---- NF:" << compositionalkinetics.m_NF; 
			for(int i = 0; i < compositionalkinetics.m_GF0.size(); i++)os << "\r\n---- ---- ---- m_GF0:" << i << ":" << compositionalkinetics.m_GF0[i];
			os << "\r\n---- ---- ---- FFKToC1:" << compositionalkinetics.m_FFKToC1;
			os << "\r\n---- ---- ---- NKToC1:" << compositionalkinetics.m_NKToC1;
			for(int i = 0; i < compositionalkinetics.m_fKToC1.size(); i++)os << "\r\n---- ---- ---- m_fKToC1:" << i << ":" << compositionalkinetics.m_fKToC1[i];
			for(int i = 0; i < compositionalkinetics.m_EKToC1.size(); i++)os << "\r\n---- ---- ---- m_EKToC1:" << i << ":" << compositionalkinetics.m_EKToC1[i];
			os << "\r\n---- ---- ---- FFKToC2_C5:" << compositionalkinetics.m_FFKToC2_C5;
			os << "\r\n---- ---- ---- NKToC2_C5:" << compositionalkinetics.m_NKToC2_C5;
			for(int i = 0; i < compositionalkinetics.m_fKToC2_C5.size(); i++)os << "\r\n---- ---- ---- m_fKToC2_C5:" << i << ":" << compositionalkinetics.m_fKToC2_C5[i];
			for(int i = 0; i < compositionalkinetics.m_EKToC2_C5.size(); i++)os << "\r\n---- ---- ---- m_EKToC2_C5:" << i << ":" << compositionalkinetics.m_EKToC2_C5[i];
			os << "\r\n---- ---- ---- FFKToC6_C14:" << compositionalkinetics.m_FFKToC6_C14;
			os << "\r\n---- ---- ---- NKToC6_C14:" << compositionalkinetics.m_NKToC6_C14;
			for(int i = 0; i < compositionalkinetics.m_fKToC6_C14.size(); i++)os << "\r\n---- ---- ---- m_fKToC6_C14:" << i << ":" << compositionalkinetics.m_fKToC6_C14[i];
			for(int i = 0; i < compositionalkinetics.m_EKToC6_C14.size(); i++)os << "\r\n---- ---- ---- m_EKToC6_C14:" << i << ":" << compositionalkinetics.m_EKToC6_C14[i];
			os << "\r\n---- ---- ---- FFKToC15Plus:" << compositionalkinetics.m_FFKToC15Plus;
			os << "\r\n---- ---- ---- NKToC15Plus:" << compositionalkinetics.m_NKToC15Plus;
			for(int i = 0; i < compositionalkinetics.m_fKToC15Plus.size(); i++)os << "\r\n---- ---- ---- m_fKToC15Plus:" << i << ":" << compositionalkinetics.m_fKToC15Plus[i];
			for(int i = 0; i < compositionalkinetics.m_EKToC15Plus.size(); i++)os << "\r\n---- ---- ---- m_EKToC15Plus:" << i << ":" << compositionalkinetics.m_EKToC15Plus[i];
			os << "\r\n---- ---- ---- FFOilToGas:" << compositionalkinetics.m_FFOilToGas;
			os << "\r\n---- ---- ---- EmeanOilToGas:" << compositionalkinetics.m_EmeanOilToGas;
			os << "\r\n---- ---- ---- SigmaOilToGas:" << compositionalkinetics.m_SigmaOilToGas;
			os << "\r\n---- ---- ---- NOilToGas:" << compositionalkinetics.m_NOilToGas;
			for(int i = 0; i < compositionalkinetics.m_fOilToGas.size(); i++)os << "\r\n---- ---- ---- m_fOilToGas:" << i << ":" << compositionalkinetics.m_fOilToGas[i];
			for(int i = 0; i < compositionalkinetics.m_fOilToGasBak.size(); i++)os << "\r\n---- ---- ---- m_fOilToGasBak:" << i << ":" << compositionalkinetics.m_fOilToGasBak[i];
			for(int i = 0; i < compositionalkinetics.m_EOilToGas.size(); i++)os << "\r\n---- ---- ---- m_EOilToGas:" << i << ":" << compositionalkinetics.m_EOilToGas[i];
			os << "\r\n---- ---- ---- OToGasF:" << compositionalkinetics.m_OToGasF;
			os << "\r\n---- ---- ---- wBIw0KToOil:" << compositionalkinetics.m_wBIw0KToOil;
			os << "\r\n---- ---- ---- wBIw0KToGas:" << compositionalkinetics.m_wBIw0KToGas;
			os << "\r\n---- ---- ---- wBIw0OilToGas:" << compositionalkinetics.m_wBIw0OilToGas;
			os << "\r\n---- ---- ---- wBIw0KToC1:" << compositionalkinetics.m_wBIw0KToC1;
			os << "\r\n---- ---- ---- wBIw0KToC2_C5:" << compositionalkinetics.m_wBIw0KToC2_C5;
			os << "\r\n---- ---- ---- wBIw0KToC6_C14:" << compositionalkinetics.m_wBIw0KToC6_C14;
			os << "\r\n---- ---- ---- wBIw0KToC15Plus:" << compositionalkinetics.m_wBIw0KToC15Plus;
			os << "\r\n---- ---- ---- wBIw0K:" << compositionalkinetics.m_wBIw0K;
			os << "\r\n---- ---- ---- C1PerInitTOC:" << compositionalkinetics.m_C1PerInitTOC;
			os << "\r\n---- ---- ---- C2_C5PerInitTOC:" << compositionalkinetics.m_C2_C5PerInitTOC;
			os << "\r\n---- ---- ---- C6_C14PerInitTOC:" << compositionalkinetics.m_C6_C14PerInitTOC;
			os << "\r\n---- ---- ---- C15PlusPerInitTOC:" << compositionalkinetics.m_C15PlusPerInitTOC;
			os << "\r\n---- ---- ---- OilPerInitTOC:" << compositionalkinetics.m_OilPerInitTOC;
			os << "\r\n---- ---- ---- GasPerInitTOC:" << compositionalkinetics.m_GasPerInitTOC;
			os << "\r\n---- ---- ---- TOCReactableKerogen:" << compositionalkinetics.m_TOCReactableKerogen;
			os << "\r\n---- ---- ---- TOCInertKerogen:" << compositionalkinetics.m_TOCInertKerogen;
			os << "\r\n---- ---- ---- TOCKerogen:" << compositionalkinetics.m_TOCKerogen;
			os << "\r\n---- ---- ---- TOCOilKerogen:" << compositionalkinetics.m_TOCOilKerogen;
			os << "\r\n---- ---- ---- TOCGasKerogen:" << compositionalkinetics.m_TOCGasKerogen;
			os << "\r\n---- ---- ---- TOCRemained:" << compositionalkinetics.m_TOCRemained;
			os << "\r\n---- ---- ---- C1Generated:" << compositionalkinetics.m_C1Generated;
			os << "\r\n---- ---- ---- C2_C5Generated:" << compositionalkinetics.m_C2_C5Generated;
			os << "\r\n---- ---- ---- C6_C14Generated:" << compositionalkinetics.m_C6_C14Generated;
			os << "\r\n---- ---- ---- C15PlusGenerated:" << compositionalkinetics.m_C15PlusGenerated;
			os << "\r\n---- ---- ---- OilGenerated:" << compositionalkinetics.m_OilGenerated;
			os << "\r\n---- ---- ---- GasGenerated:" << compositionalkinetics.m_GasGenerated;
			os << "\r\n---- ---- ---- RatioC6_C14ToTI0:" << compositionalkinetics.m_RatioC6_C14ToTI0;
			os << "\r\n---- ---- ---- TR:" << compositionalkinetics.m_TR;
			os << "\r\n---- ---- ---- C1Existed:" << compositionalkinetics.m_C1Existed;
			os << "\r\n---- ---- ---- C2_C5Existed:" << compositionalkinetics.m_C2_C5Existed;
			os << "\r\n---- ---- ---- C6_C14Existed:" << compositionalkinetics.m_C6_C14Existed;
			os << "\r\n---- ---- ---- C15PlusExisted:" << compositionalkinetics.m_C15PlusExisted;
			os << "\r\n---- ---- ---- OilExisted:" << compositionalkinetics.m_OilExisted;
			os << "\r\n---- ---- ---- GasExisted:" << compositionalkinetics.m_GasExisted;
			os << "\r\n---- ---- ---- ResidueExisted:" << compositionalkinetics.m_ResidueExisted;
			os << "\r\n---- ---- ---- C1Cracked:" << compositionalkinetics.m_C1Cracked;
			os << "\r\n---- ---- ---- C2_C5Cracked:" << compositionalkinetics.m_C2_C5Cracked;
			os << "\r\n---- ---- ---- GasCracked:" << compositionalkinetics.m_GasCracked;
			os << "\r\n---- ---- ---- C1CrackedAdded:" << compositionalkinetics.m_C1CrackedAdded;
			os << "\r\n---- ---- ---- C2_C5CrackedAdded:" << compositionalkinetics.m_C2_C5CrackedAdded;
			os << "\r\n---- ---- ---- GasCrackedAdded:" << compositionalkinetics.m_GasCrackedAdded;
			os << "\r\n---- ---- ---- ResidueCracked:" << compositionalkinetics.m_ResidueCracked;
			os << "\r\n---- ---- ---- ResidueCrackedAdded:" << compositionalkinetics.m_ResidueCrackedAdded;
			os << "\r\n---- ---- ---- C6_C14Cracked:" << compositionalkinetics.m_C6_C14Cracked;
			os << "\r\n---- ---- ---- C15PlusCracked:" << compositionalkinetics.m_C15PlusCracked;
			os << "\r\n---- ---- ---- OilCracked:" << compositionalkinetics.m_OilCracked;
			os << "\r\n---- ---- ---- C6_C14CrackedAdded:" << compositionalkinetics.m_C6_C14CrackedAdded;
			os << "\r\n---- ---- ---- C15PlusCrackedAdded:" << compositionalkinetics.m_C15PlusCrackedAdded;
			os << "\r\n---- ---- ---- OilCrackedAdded:" << compositionalkinetics.m_OilCrackedAdded;
			os << "\r\n---- ---- ---- RatioCrackedC1:" << compositionalkinetics.m_RatioCrackedC1;
			os << "\r\n---- ---- ---- RatioCrackedC6_C14:" << compositionalkinetics.m_RatioCrackedC6_C14;
			os << "\r\n---- ---- ---- MKerTotal:" << compositionalkinetics.m_MKerTotal;
			os << "\r\n---- ---- ---- MKerOil:" << compositionalkinetics.m_MKerOil;
			os << "\r\n---- ---- ---- MKerGas:" << compositionalkinetics.m_MKerGas;
			os << "\r\n---- ---- ---- MKerInert:" << compositionalkinetics.m_MKerInert;
			return os;
		}
	 /*   ���������̿�ⲿ�ֲ������г��ˣ��������ѽ�Ϊ���ĸ�����            */
	  double Jiecheng(int n) //n�Ľ׳�
		{double temp=1; for(int i=0;i<n;i++) temp=temp*double(i+1); return temp; }
	  double erf(double x)
		{  //����
		 int N=30; //����ľ������
		 double pi=3.1415926535;  double temp=0;
		 for(int i=0;i<N+1;i++) temp+=::powf(-1,i)*::powf(x,2*i+1)/(2*i+1)/Jiecheng(i);
		 temp=temp*2/sqrt(pi);
		 return temp;
		}
	 double Pnormal(double q,double Emean,double Sigma)
	   {//��̬�ֲ��ۻ����ʺ���ֵ����q������ Emean��4*Sigma�ķ�Χ�ڶ�����
		 double temp=(q-Emean)/Sigma/sqrt(2.);
		 return 0.5+0.5*erf(temp);
	   }
	 void GetEachfAndE(int N, double aE,double aSigma,std::vector<double> &f,std::vector<double> &E)
	   { //���ݻ��������������̬�ֲ��ľ��ʺͱ�׼������ɢ�Ļ�ܺͶ�Ӧ�Ļ�ѧ����ϵ��
		 double LeftPoint, RightPoint; //���Ҷϵ��ֵ �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma
		 double Delta; //N�������ÿ������ľ��롪��ƽ����������
		 LeftPoint=aE-3.*aSigma; RightPoint=aE+3.*aSigma;
		 Delta=6.*aSigma/double(N);
		 for(int i=0;i<N;i++)
		   {
			 if(i==0)
			   {    //��������丳ֵ
				 E[i]=LeftPoint+0.5*Delta;//ȡ�����е�ֵ
				 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma); //��������ĸ���ֵȡֵΪ�������Ҷ�ֵ����˰����˸�����ֵ������������еĸ���ֵ
			   }
			 if(i>0&&i<N-1)
			   {   //�м�����丳ֵ
				 E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
				 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);
			   }
			 if(i==N-1)
			   {  //���ұ����丳ֵ
				 E[i]=E[i-1]+Delta;  // ȡ�����е�ֵ
				 f[i]=Pnormal(E[i]+0.5*Delta,aE,aSigma)-Pnormal(E[i]-0.5*Delta,aE,aSigma);   //��������ĸ���ֵȡֵΪ������ֵ�������ұ����еĸ���ֵ
			   }
		   }
	   }
	  void Normalization(int N,std::vector<double> &f)
		{   //��ֵ��һ��
		   double Sum=0.;
		   for(int i=0;i<N;i++) Sum+=f[i];
		   for(int i=0;i<N;i++) f[i]=f[i]/Sum;
		}
	  void Construct(int aNF,std::vector<double> &aGF0,double aW, double aTI0,double aHI0, double aOToGasF,
					 double aFFKToC1,int aNKToC1,std::vector<double> &afKToC1, std::vector<double> &aEKToC1,
					 double aFFKToC2_C5,int aNKToC2_C5,std::vector<double> &afKToC2_C5, std::vector<double> &aEKToC2_C5,
					 double aFFKToC6_C14,int aNKToC6_C14,std::vector<double> &afKToC6_C14, std::vector<double> &aEKToC6_C14,
					 double aFFKToC15Plus,int aNKToC15Plus,std::vector<double> &afKToC15Plus, std::vector<double> &aEKToC15Plus,
					 double aFFOilToGas,double aEmeanOilToGas, double aSigmaOilToGas)
		{
			m_NF=aNF;
			m_GF0.resize(m_NF); for(int i=0;i<m_NF;i++) m_GF0[i]=aGF0[i];//��ֵ��ת��ΪС��
			m_W=aW; m_TI0=aTI0; m_HI0=aHI0; /*QI0=aQI0; PI0=aPI0;*/ //G0=aG0;
			m_OToGasF=aOToGasF; //���ѽ�Ϊ���ı���
			m_FFKToC1=aFFKToC1;    m_NKToC1=aNKToC1; m_fKToC1.resize(m_NKToC1); m_EKToC1.resize(m_NKToC1);
			for(int i=0;i<m_NKToC1;i++) {m_fKToC1[i]=afKToC1[i];m_EKToC1[i]=aEKToC1[i];}
			m_FFKToC2_C5=aFFKToC2_C5;    m_NKToC2_C5=aNKToC2_C5; m_fKToC2_C5.resize(m_NKToC2_C5); m_EKToC2_C5.resize(m_NKToC2_C5);
			for(int i=0;i<m_NKToC2_C5;i++) {m_fKToC2_C5[i]=afKToC2_C5[i];m_EKToC2_C5[i]=aEKToC2_C5[i];}
			m_FFKToC6_C14=aFFKToC6_C14;    m_NKToC6_C14=aNKToC6_C14; m_fKToC6_C14.resize(m_NKToC6_C14); m_EKToC6_C14.resize(m_NKToC6_C14);
			for(int i=0;i<m_NKToC6_C14;i++) {m_fKToC6_C14[i]=afKToC6_C14[i];m_EKToC6_C14[i]=aEKToC6_C14[i];}
			m_FFKToC15Plus=aFFKToC15Plus;    m_NKToC15Plus=aNKToC15Plus; m_fKToC15Plus.resize(m_NKToC15Plus); m_EKToC15Plus.resize(m_NKToC15Plus);
			for(int i=0;i<m_NKToC15Plus;i++) {m_fKToC15Plus[i]=afKToC15Plus[i];m_EKToC15Plus[i]=aEKToC15Plus[i];}
        
			m_EmeanOilToGas=aEmeanOilToGas;   m_SigmaOilToGas=aSigmaOilToGas;
			m_NOilToGas=21; //��������̫�ֲ��ֳ�21�����䣬��������ֵλ����һ�����䣬�������߶ԳƵطֱ�ֲ���10���� �����ֵ����Ҷ˵�ֱ�ΪE��3*Sigma ��������0.9974�ĸ������䣩
			m_fOilToGas.resize(m_NOilToGas); m_EOilToGas.resize(m_NOilToGas);
			GetEachfAndE(m_NOilToGas, m_EmeanOilToGas,m_SigmaOilToGas,m_fOilToGas,m_EOilToGas);Normalization(m_NOilToGas,m_fOilToGas);
			m_fOilToGasBak.resize(m_NOilToGas); for(int i=0;i<m_NOilToGas;i++) m_fOilToGasBak[i]=m_fOilToGas[i];

		}
	  void CopyFrom(CompositionalKinetics &aCompositional)
	   {   //����һ���ṹ�п���һ�ݲ��� ,������Щ������ֱ�ӿ�����ַ


			m_NF=aCompositional.m_NF;
			m_GF0=aCompositional.m_GF0;
			m_W=aCompositional.m_W; m_TI0=aCompositional.m_TI0; m_HI0=aCompositional.m_HI0;//
			m_OToGasF=aCompositional.m_OToGasF; //���ѽ�Ϊ���ı���
			m_FFKToC1=aCompositional.m_FFKToC1;    m_NKToC1=aCompositional.m_NKToC1;m_fKToC1.resize(m_NKToC1);  m_EKToC1.resize(m_NKToC1);
			for(int i=0;i<m_NKToC1;i++){ m_fKToC1[i]=aCompositional.m_fKToC1[i]; m_EKToC1[i]=aCompositional.m_EKToC1[i]; }
			m_FFKToC2_C5=aCompositional.m_FFKToC2_C5;    m_NKToC2_C5=aCompositional.m_NKToC2_C5;m_fKToC2_C5.resize(m_NKToC2_C5);  m_EKToC2_C5.resize(m_NKToC2_C5);
			for(int i=0;i<m_NKToC2_C5;i++){ m_fKToC2_C5[i]=aCompositional.m_fKToC2_C5[i]; m_EKToC2_C5[i]=aCompositional.m_EKToC2_C5[i]; }
			m_FFKToC6_C14=aCompositional.m_FFKToC6_C14;    m_NKToC6_C14=aCompositional.m_NKToC6_C14;m_fKToC6_C14.resize(m_NKToC6_C14);  m_EKToC6_C14.resize(m_NKToC6_C14);
			for(int i=0;i<m_NKToC6_C14;i++){ m_fKToC6_C14[i]=aCompositional.m_fKToC6_C14[i]; m_EKToC6_C14[i]=aCompositional.m_EKToC6_C14[i]; }
			m_FFKToC15Plus=aCompositional.m_FFKToC15Plus;    m_NKToC15Plus=aCompositional.m_NKToC15Plus;m_fKToC15Plus.resize(m_NKToC15Plus);  m_EKToC15Plus.resize(m_NKToC15Plus);
			for(int i=0;i<m_NKToC15Plus;i++){ m_fKToC15Plus[i]=aCompositional.m_fKToC15Plus[i]; m_EKToC15Plus[i]=aCompositional.m_EKToC15Plus[i]; }

			m_NOilToGas=aCompositional.m_NOilToGas;
			m_fOilToGas.resize(m_NOilToGas);  m_EOilToGas.resize(m_NOilToGas); m_fOilToGasBak.resize(m_NOilToGas);
			for(int i=0;i<m_NOilToGas;i++) {
			m_fOilToGas=aCompositional.m_fOilToGas; m_EOilToGas=aCompositional.m_EOilToGas;
			m_fOilToGasBak=aCompositional.m_fOilToGasBak; }

		   /* FFKToC2_C5=aCompositional.m_FFKToC2_C5;    NKToC2_C5=aCompositional.m_NKToC2_C5; fKToC2_C5=aCompositional.m_fKToC2_C5; EKToC2_C5=aCompositional.m_EKToC2_C5;
			FFKToC6_C14=aCompositional.m_FFKToC6_C14;    NKToC6_C14=aCompositional.m_NKToC6_C14; fKToC6_C14=aCompositional.m_fKToC6_C14; EKToC6_C14=aCompositional.m_EKToC6_C14;
			FFKToC15Plus=aCompositional.m_FFKToC15Plus;    NKToC15Plus=aCompositional.m_NKToC15Plus; fKToC15Plus=aCompositional.m_fKToC15Plus; EKToC15Plus=aCompositional.m_EKToC15Plus;
		  //  ShowMessage("EKToC15Plus[0]="+FloatToStr(EKToC15Plus[0]));
			NOilToGas=aCompositional.m_NOilToGas;
			fOilToGas=aCompositional.m_fOilToGas; EOilToGas=aCompositional.m_EOilToGas;
			fOilToGasBak=aCompositional.m_fOilToGasBak;      */
	   }
	  void FirstOrderReaction(double TLast, double tLast, double T, double t,int N_LLNL,std::vector<double> &fLLNL,double FFLLNL, std::vector<double> &ELLNL,double &wBIw0)
		{  //�ֱ�����һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma����
		   // ƽ�з�Ӧ����N_LLNL����ѧ����ϵ��fLLNL,Ƶ������FFLLNL�����ELLNL,�ܵ�ʣ�໯ѧ����ϵ��wBIw0
		 wBIw0=0.;
		 double R=0.001986;//���峣�� ����λ Kcal/(mol*K)   ,���ڴ���Ļ�ܵ�λ��KCal/mol�����������������
		 //double R=0.008314472; //���峣�� KJ/(mol*K)
		 //������t��tLast���¶�T��t�����Թ�ϵ������T��TLast�����Ա仯��T=a*tt+b   ,tt����t��tLast��仯��ʱ��
		 double a,b; // ���Ա仯��ϵ��
		 a=(T-TLast)/(t-tLast);b=T-a*t;
		 //����tLast��t֮�������ֵ���ַ��������ڼ�ȷ�ΪN���ȷ֣���˦�t=(t-tLast)/N
		 int N=int(fabs(T-TLast)/0.5+1); //���������Ǳ�֤��ÿ�����㲽���¶ȱ仯������0.5�棬�����1�Ǳ�֤������1����ִ�С�
		 double Delta_t=(t-tLast)/double(N); //Delta_t�������������������
		 double tt1=tLast,tt2,ttM; // �ֱ���ʱ��ε��¶˵�ֵ���϶˵�ֵ���м�ֵ,��ʼ��tt1ֵ������׶�
		 double temp=0;
		 std::vector<double>wiBIw0i;  //wi/w0i ,�����EasyRo�Ƶ��еĹ�ʽ��8��
		 wiBIw0i.resize(N_LLNL);
		 for(int i=0;i<N_LLNL;i++)
		  {
		   for(int j=0;j<N;j++)
			{
			 tt2=tt1+Delta_t; ttM=0.5*(tt2+tt1);
			 temp+=(-FFLLNL*exp(-ELLNL[i]/R/(a*ttM+b)))*fabs(Delta_t);
			 tt1=tt2;
			}
		   wiBIw0i[i]=exp(temp);
		   fLLNL[i]=fLLNL[i]*wiBIw0i[i];   //������һʱ��εĻ�ѧ����ϵ��
		   wBIw0+=fLLNL[i];  // wBIw0Ϊ�ܵĻ�ѧ����ϵ��ʣ��ֵ
		   tt1=tLast; // ����һ����Ӧ�Ļ�ܵ�wiBIw0i[i]��Ҫ����ʼʱ������
		   temp=0;    //temp���¹���
		  }
		}
	  void Reactions(double TLast, double tLast, double T, double t)
	   {  //���ʱ���ϵ�һ���ز��
	   // ���л�̼���͡������ı仯��û�а����ѽⲿ��
		 // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
		 //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
		 // ����ԭ������PetroMod��������Դ��Pepper��1995
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		 // double InitwBIw0KToOil=0,InitwBIw0KToGas=0;  //��ʼʱ�̵ĸ��Ҹ���֣���ѧ����ϵ����֮��
		  double InitwBIw0KToC1=0,InitwBIw0KToC2_C5=0,InitwBIw0KToC6_C14=0,InitwBIw0KToC15Plus=0;  //��ʼʱ�̵ĸ��Ҹ���֣���ѧ����ϵ����֮��
		  for(int i=0;i<m_NKToC1;i++)InitwBIw0KToC1+=m_fKToC1[i]; for(int i=0;i<m_NKToC2_C5;i++)InitwBIw0KToC2_C5+=m_fKToC2_C5[i];
		  for(int i=0;i<m_NKToC6_C14;i++)InitwBIw0KToC6_C14+=m_fKToC6_C14[i]; for(int i=0;i<m_NKToC15Plus;i++)InitwBIw0KToC15Plus+=m_fKToC15Plus[i];
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC1,m_fKToC1,m_FFKToC1,m_EKToC1,m_wBIw0KToC1);  // ���Ҹ���C1�Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC2_C5,m_fKToC2_C5,m_FFKToC2_C5,m_EKToC2_C5,m_wBIw0KToC2_C5);  // ���Ҹ���C2_C5�Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC6_C14,m_fKToC6_C14,m_FFKToC6_C14,m_EKToC6_C14,m_wBIw0KToC6_C14);  // ���Ҹ���6_C14�Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC15Plus,m_fKToC15Plus,m_FFKToC15Plus,m_EKToC15Plus,m_wBIw0KToC15Plus);  // ���Ҹ���C15Plus�Ƚ�

		  m_C1PerInitTOC=m_HI0*m_GF0[0]*(InitwBIw0KToC1-m_wBIw0KToC1)/1000.;  //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C1
		  m_C2_C5PerInitTOC=m_HI0*m_GF0[1]*(InitwBIw0KToC2_C5-m_wBIw0KToC2_C5)/1000.;       //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C2_C5
		  m_C6_C14PerInitTOC=m_HI0*m_GF0[2]*(InitwBIw0KToC6_C14-m_wBIw0KToC6_C14)/1000.;   //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C6_C14
		  m_C15PlusPerInitTOC=m_HI0*m_GF0[3]*(InitwBIw0KToC15Plus-m_wBIw0KToC15Plus)/1000.;   //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C6_C14
		  m_OilPerInitTOC=m_C6_C14PerInitTOC+m_C15PlusPerInitTOC;
		  m_GasPerInitTOC=m_C1PerInitTOC+m_C2_C5PerInitTOC;

		  m_RatioC6_C14ToTI0=0.2; //TI0��C2_C14�ı��� �����ｫTI0����Ϊ20%��C6_C14��80%��C15Plus,�������¿��ǣ�δ��Դ���г�ʼ���и߷�����������Щ
		  m_C1Generated=m_C1PerInitTOC; // �ڳ�ʼ��������ۻ���C1�����Ǹò�����C1��
		  m_C2_C5Generated=m_C2_C5PerInitTOC; //�ڳ�ʼ��������ۻ���C2_C5�����Ǹò�����C2_C5��
		  m_C6_C14Generated=m_C6_C14PerInitTOC+m_RatioC6_C14ToTI0*m_TI0/1000.;
		  m_C15PlusGenerated=m_C15PlusPerInitTOC+(1.-m_RatioC6_C14ToTI0)*m_TI0/1000.;

		  m_OilGenerated=m_OilPerInitTOC+m_TI0/1000.; //  ���Ҹ���λ����ԭʼ�л�̼�ۼƵ��������������ڳ�ʼ��������ۻ�������Ϊ�ò������������ʼʱ�̴��ڵ�����֮��
		  m_GasGenerated=m_GasPerInitTOC; // //���Ҹ���λ����ԭʼ�л�̼�ۼƵ����������� ��û�г�ʼ�Ĵ���������˳�ʼ�����ۻ����������Ǹò���������

		  m_TOCKerogen=1.-m_W*m_TI0/1000.-m_W*m_OilPerInitTOC- m_W*m_GasPerInitTOC;  //��ָ���Ҹ��е��л�̼���� ,��Ҫ��ԭʼ��λ�л�̼-��ʼ���ڵ����������л�̼-�ò����ɵ��ͺ����е��л�̼
		  m_TOCRemained=m_TOCKerogen; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
		 // TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //Դ����ʣ����л�̼Ϊ���Ҹ��л�̼�������Դ�����ͺ����е��л�̼�Լ����ѽ�Ϊ��֮̿�� ,������Ҫ���ѽ��������ſ�֪�� �������ʽ�Ӳ����ã���ΪOilExisted���ܵ�������StrSeg���ܵĴ��ڵ��͵����������������� Reactions(...)����ʱ����ֵ��δ֪
		  m_TOCInertKerogen=1.-m_W*m_TI0/1000.-m_W*m_HI0/1000.;   //���Ը��Ҹ�����
		  m_TOCReactableKerogen=m_TOCKerogen-m_TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����
		  m_TOCOilKerogen=m_W*m_HI0/1000.*(m_GF0[2]+m_GF0[3])-m_W*m_OilPerInitTOC;   // ��һ����Ӧ���ʣ���͸��Ҹ� new added 20190412
		  m_TOCGasKerogen=m_W*m_HI0/1000.*(m_GF0[0]+m_GF0[1])-m_W*m_GasPerInitTOC;        // ��һ����Ӧ���ʣ�������Ҹ� new added 20190412
		  m_TR= (m_OilGenerated-m_TI0/1000.+m_GasGenerated)/(m_HI0/1000.);
		  //����ת���ʵ��ڵ�λ����ԭʼ�л�̼�ۻ����ɵ����������Ե�λ����ԭʼ�л�̼����ָ��
	   }
	  void Reactions(double TLast, double tLast, double T, double t,CompositionalKinetics &aCompositional)
	   {  // �����Ҹ���֡��͡������ı仯��û�а����ѽⲿ��
		 // ��Ҫ�ں�����������һ�����¶�TLast(��)����һ����ʱ��tLast����λ��Ma��,��һ�����¶�T(��)����һ����ʱ��t����λ��Ma��
		 //aCompositionalΪ��һ��ʱ��εĲ����ṹ
		 //���ǻ��ڵ�λ������kg��ԭʼ�л�̼�����
		 // ����ԭ������PetroMod��������Դ��BasinMod
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		  //����Ϊ���Ҹ��Ƚ�
		  //wBIw0KToOil=aOrganofacies->wBIw0KToOil;wBIw0KToGas=aOrganofacies->wBIw0KToGas;
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC1,m_fKToC1,m_FFKToC1,m_EKToC1,m_wBIw0KToC1);  // ���Ҹ���C1�Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC2_C5,m_fKToC2_C5,m_FFKToC2_C5,m_EKToC2_C5,m_wBIw0KToC2_C5);  // ���Ҹ���C2_C5�Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC6_C14,m_fKToC6_C14,m_FFKToC6_C14,m_EKToC6_C14,m_wBIw0KToC6_C14);  // ���Ҹ���6_C14�Ƚ�
		  FirstOrderReaction(TLast, tLast,T,t,m_NKToC15Plus,m_fKToC15Plus,m_FFKToC15Plus,m_EKToC15Plus,m_wBIw0KToC15Plus);  // ���Ҹ���C15Plus�Ƚ�

		 // FirstOrderReaction(TLast, tLast,T,t,NKToOil,fKToOil,FFKToOil,EKToOil,wBIw0KToOil);  // ���Ҹ������Ƚ�
		 // FirstOrderReaction(TLast, tLast,T,t,NKToGas,fKToGas,FFKToGas,EKToGas,wBIw0KToGas);  // ���Ҹ������Ƚ�

		  m_C1PerInitTOC=m_HI0*m_GF0[0]*(aCompositional.m_wBIw0KToC1-m_wBIw0KToC1)/1000.;  //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C1
		  m_C2_C5PerInitTOC=m_HI0*m_GF0[1]*(aCompositional.m_wBIw0KToC2_C5-m_wBIw0KToC2_C5)/1000.;       //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C2_C5
		  m_C6_C14PerInitTOC=m_HI0*m_GF0[2]*(aCompositional.m_wBIw0KToC6_C14-m_wBIw0KToC6_C14)/1000.;   //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C6_C14
		  m_C15PlusPerInitTOC=m_HI0*m_GF0[3]*(aCompositional.m_wBIw0KToC15Plus-m_wBIw0KToC15Plus)/1000.;   //ÿ��λԭʼ�л�̼�ڸ�ʱ�䲽����C6_C14
		  m_OilPerInitTOC=m_C6_C14PerInitTOC+m_C15PlusPerInitTOC;
		  m_GasPerInitTOC=m_C1PerInitTOC+m_C2_C5PerInitTOC;

		  m_C1Generated=m_C1PerInitTOC+aCompositional.m_C1Generated; //
		  m_C2_C5Generated=m_C2_C5PerInitTOC+aCompositional.m_C2_C5Generated;
		  m_C6_C14Generated=m_C6_C14PerInitTOC+aCompositional.m_C6_C14Generated;
		  m_C15PlusGenerated=m_C15PlusPerInitTOC+aCompositional.m_C15PlusGenerated;
		  m_OilGenerated=m_OilPerInitTOC+aCompositional.m_OilGenerated;
		  m_GasGenerated=m_GasPerInitTOC+aCompositional.m_GasGenerated;
      
		  m_TOCKerogen=aCompositional.m_TOCKerogen-m_W*m_OilPerInitTOC-m_W*m_GasPerInitTOC; //��ָ���Ҹ��е��л�̼���� ,��Ҫ��ԭʼ��λ�л�̼-��ʼ���ڵ����������л�̼-�Ѿ��ۼ����ɵ��ͺ����е��л�̼
		  m_TOCRemained=m_TOCKerogen; //ʣ���л�̼�������ﲻ����Դ���е����࣬���ø��Ҹ��л�̼�����ƴ����ܵ�TOC����Ϊ�ڼ�������в�������ȷ��Դ�������ຬ������Ϊ��ʹ��TOCRemained�������ʱ��û���������ѽ����
		  //TOCRemained=TOCKergen+W*OilExisted+W*GasExisted+ResidueExisted;   //Դ����ʣ����л�̼Ϊ���Ҹ��л�̼�������Դ�����ͺ����е��л�̼֮�� ,������Ҫ���ѽ��������ſ�֪��
		  m_TOCInertKerogen=1.-m_W*m_TI0/1000.-m_W*m_HI0/1000.;   //���Ը��Ҹ�����
		  m_TOCReactableKerogen=m_TOCKerogen-m_TOCInertKerogen; //�ɷ�Ӧ���Ҹ�����,��ָ��λԭʼ�л�̼������Ӧ����
		  m_TOCOilKerogen=aCompositional.m_TOCOilKerogen-m_W*m_OilPerInitTOC;   // ��һ����Ӧ���ʣ���͸��Ҹ� new added 20190412
		  m_TOCGasKerogen=aCompositional.m_TOCGasKerogen-m_W*m_GasPerInitTOC;        // ��һ����Ӧ���ʣ�������Ҹ� new added 20190412
		  m_TR= (m_OilGenerated-m_TI0/1000.+m_GasGenerated)/(m_HI0/1000.);
	   }
	  void GetfOilToGas()
	   {  //��õ�һ�������ѽ�Ϊ���Ļ�ѧ����ϵ��������Դ���в�ͬ��Դ�͵ı��ʼ��㣻
		 //��Ϊ��һ���ĸ��Ҹ��������Լ���һ�����ѽ�Ϊ��ʣ�����������������֮��ı���ȷ����ͬ��ѧ����ϵ������ռ�ı���
		 double RatioKerogenOil,RatioCrackLeftedOil; //�ֱ�����һ�����Ҹ����ɵ��ͺ��ѽ�ʣ�������ռ�ı���
		 double SumfOilToGas=0.;
		 RatioKerogenOil=m_OilPerInitTOC*m_MassOfInitTOCTotal/m_OilExisted;
		 RatioCrackLeftedOil=(m_MassOfInitTOCTotal*m_TI0/1000.-m_OilCracked)/m_OilExisted;
		 for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]=m_fOilToGasBak[i]*RatioKerogenOil+m_fOilToGas[i]*RatioCrackLeftedOil;
		 m_wBIw0OilToGas=1.;   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ
	   }
	   void OilCrackToGas(double TLast, double tLast, double T, double t)
	   {    //���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
		  //����ΪStrSeg�д��ڵ����ѽ�Ϊ���Ͳ�����Ĺ��̡������ǵ�һ��ʱ�䲽����ʼʱ��Դ���д���ԭʼ����
		  //���ڶ���ֵ����ѽ�Ϊ������ʱ�Բ����л�����Դ�����ѽⷽ����ֻ������һ�����������ѽ�������������ѽ�����C1����ռ70%
		  m_RatioCrackedC1=0.7;  //��ʱ�����ѽ�Ϊ����C1�ı���Ϊ0.7�� �������������ڿ��Ը��ݽ�һ�������ϵ���
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		  double InitwBIw0OilToGas=0;  //��ʼʱ�̵ĸ����ѽ⣨��ѧ����ϵ����֮��
		  for(int i=0;i<m_NOilToGas;i++)InitwBIw0OilToGas+=m_fOilToGas[i];//��ֵӦ�õ���1
		  FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���Ҹ�������ѽ�Ϊ��
		  m_OilExisted=m_MassOfInitTOCTotal*m_TI0/1000.;   //��ʼ��λ����Դ���ڵ��ʹ����� ������ԭʼ�л�̼��������TI0ֵ
		  m_C6_C14Existed=m_RatioC6_C14ToTI0*m_OilExisted;
		  m_C15PlusExisted=(1.-m_RatioC6_C14ToTI0)*m_OilExisted;
		  m_GasExisted=0.;
		  m_C1Existed=0.;
		  m_C2_C5Existed=0.;
		  m_GasCracked=m_OilExisted*m_OToGasF*(InitwBIw0OilToGas-m_wBIw0OilToGas);   //�ڳ�ʼʱ�̷�Ӧ����ͣ��ĳ�ʼ�����ĳ�ʼ���� TI0/1000����OToGasFΪ��ת��Ϊ���ı�����
		  m_C1Cracked=m_GasCracked*m_RatioCrackedC1;    //�����趨�ı������ѽ����ϸ����ֺ���
		  m_C2_C5Cracked=m_GasCracked*(1.-m_RatioCrackedC1);  //�����趨�ı������ѽ����ϸ����ֺ���
		  m_ResidueCracked=m_OilExisted*(1.-m_OToGasF)*(InitwBIw0OilToGas-m_wBIw0OilToGas);  //��ת��Ϊ������ı���Ϊ (1.-OToGasF)����ת��Ϊ����������ת��Ϊ����ͬһ���ѽ����
		  m_OilCracked=m_GasCracked+m_ResidueCracked;
		  m_C6_C14Cracked=m_OilCracked*(m_C6_C14Existed/m_OilExisted);  //������������ֵı��������ѽ���
		  m_C15PlusCracked=m_OilCracked*(m_C15PlusExisted/m_OilExisted);  //������������ֵı��������ѽ���
		  m_GasCrackedAdded=m_GasCracked;//�����ǵ�һ��ʱ�䲽��������ۻ��ѽ������ڳ�ʼ�ѽ�����
		  m_C1CrackedAdded= m_C1Cracked;
		  m_C2_C5CrackedAdded= m_C2_C5Cracked;
		  m_ResidueCrackedAdded=m_ResidueCracked;
		  m_OilCrackedAdded=m_OilCracked;
		  m_C6_C14CrackedAdded=m_C6_C14Cracked;
		  m_C15PlusCrackedAdded=m_C15PlusCracked;
		  m_OilExisted=m_OilExisted+m_OilPerInitTOC*m_MassOfInitTOCTotal-m_OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
		  m_C6_C14Existed=m_C6_C14Existed+m_C6_C14PerInitTOC*m_MassOfInitTOCTotal-m_C6_C14Cracked;
		  m_C15PlusExisted=m_C15PlusExisted+m_C15PlusPerInitTOC*m_MassOfInitTOCTotal-m_C15PlusCracked;
		  m_GasExisted =m_GasExisted+m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
		  m_C1Existed=m_C1Existed+m_C1PerInitTOC*m_MassOfInitTOCTotal+m_C1Cracked;
		  m_C2_C5Existed=m_C2_C5Existed+m_C2_C5PerInitTOC*m_MassOfInitTOCTotal+m_C2_C5Cracked;
		  if(m_GasExisted < 1.0e-5)
			  m_GasExisted = 1.0e-5;
		  if(m_OilExisted < 1.0e-5)
			  m_OilExisted = 1.0e-5;
		  GetfOilToGas();
	   }
	  void GetfOilToGas(CompositionalKinetics &aCompositional)
	   {  //���ÿһ�������ѽ�Ϊ���Ļ�ѧ����ϵ��������Դ���в�ͬ��Դ�͵ı��ʼ��㣻
		 //��Ϊÿһ���ĸ��Ҹ��������Լ���һ�����ѽ�Ϊ��ʣ�����������������֮��ı���ȷ����ͬ��ѧ����ϵ������ռ�ı���
		 double RatioKerogenOil,RatioCrackLeftedOil; //�ֱ�����һ�����Ҹ����ɵ��ͺ��ѽ�ʣ�������ռ�ı���
		 double SumfOilToGas=0.;
		 RatioKerogenOil=m_OilPerInitTOC*m_MassOfInitTOCTotal/m_OilExisted;
		 RatioCrackLeftedOil=(aCompositional.m_OilExisted-m_OilCracked)/m_OilExisted;
		 Normalization(m_NOilToGas,m_fOilToGas); //�����ѽ����͵Ļ�ѧ����ϵ����һ��
		 for(int i=0;i<m_NOilToGas;i++) m_fOilToGas[i]=m_fOilToGasBak[i]*RatioKerogenOil+m_fOilToGas[i]*RatioCrackLeftedOil;
		 m_wBIw0OilToGas=1.;   //ÿ�μ�����Ҫ����ֵ��Ϊ��ʼֵ����ʼֵΪ1,������Ϊÿ�μ��������ѽ���Ͷ�����֪�ĳ�ʼֵ
	   }
	  void OilCrackToGas(double TLast, double tLast, double T, double t,CompositionalKinetics &aCompositional)
	   {    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
		  //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
		  //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		  FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
		  m_GasCracked=aCompositional.m_OilExisted*m_OToGasF*(aCompositional.m_wBIw0OilToGas-m_wBIw0OilToGas);
		  m_C1Cracked=m_GasCracked*m_RatioCrackedC1;    //�����趨�ı������ѽ����ϸ����ֺ���
		  m_C2_C5Cracked=m_GasCracked*(1.-m_RatioCrackedC1);  //�����趨�ı������ѽ����ϸ����ֺ���
		  m_ResidueCracked=aCompositional.m_OilExisted*(1.-m_OToGasF)*(aCompositional.m_wBIw0OilToGas-m_wBIw0OilToGas);
		  m_OilCracked=m_GasCracked+m_ResidueCracked;
		  m_C6_C14Cracked=m_OilCracked*(aCompositional.m_C6_C14Existed/aCompositional.m_OilExisted);  //������������ֵı��������ѽ���
		  m_C15PlusCracked=m_OilCracked*(aCompositional.m_C15PlusExisted/aCompositional.m_OilExisted);  //������������ֵı��������ѽ���
		  m_GasCrackedAdded=aCompositional.m_GasCrackedAdded+m_GasCracked;
		  m_C1CrackedAdded=aCompositional.m_C1CrackedAdded+m_C1Cracked;
		  m_C2_C5CrackedAdded=aCompositional.m_C2_C5CrackedAdded+m_C2_C5Cracked;

		  m_ResidueCrackedAdded=aCompositional.m_ResidueCrackedAdded+m_ResidueCracked;
		  m_OilCrackedAdded=aCompositional.m_OilCrackedAdded+m_OilCracked;
		  m_C6_C14CrackedAdded=aCompositional.m_C6_C14CrackedAdded+m_C6_C14Cracked;
		  m_C15PlusCrackedAdded=aCompositional.m_C15PlusCrackedAdded+m_C15PlusCracked;

		  m_OilExisted=aCompositional.m_OilExisted+m_OilPerInitTOC*m_MassOfInitTOCTotal-m_OilCracked;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
		  m_C6_C14Existed=aCompositional.m_C6_C14Existed+m_C6_C14PerInitTOC*m_MassOfInitTOCTotal-m_C6_C14Cracked;
		  m_C15PlusExisted=aCompositional.m_C15PlusExisted+m_C15PlusPerInitTOC*m_MassOfInitTOCTotal-m_C15PlusCracked;
		  m_GasExisted=aCompositional.m_GasExisted+m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
		  m_C1Existed=aCompositional.m_C1Existed+m_C1PerInitTOC*m_MassOfInitTOCTotal+m_C1Cracked;
		  m_C2_C5Existed=aCompositional.m_C2_C5Existed+m_C2_C5PerInitTOC*m_MassOfInitTOCTotal+m_C2_C5Cracked;
		  if(m_GasExisted < 1.0e-5)
			  m_GasExisted = 1.0e-5;
		  if(m_OilExisted < 1.0e-5)
			  m_OilExisted = 1.0e-5;
		  GetfOilToGas(aCompositional);
	  }
	  void OilCrackToGasForNoOil(double TLast, double tLast, double T, double t,CompositionalKinetics &aCompositional)
	  {    //���ڸ��͸��Ҹ����ɵ����ѽ�Ϊ���Ͳ�����Ļ�ѧ����ѧ������ͬ���������I�͸��Ҹ��Ĳ�����Ϊ����Ĳ��� ;���������ʽ�ⷨ�����ѽ��Ϊ��һʱ�䲽���ڵ���
		  //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
		  //����ΪI�͸��Ҹ�������ѽ�Ϊ���Ͳ�����
		  TLast+=273;T+=273;   //ת��Ϊ�����¶�
		  tLast=tLast*1000000*365*24*3600;  //������ת��Ϊ��
		  t=t*1000000*365*24*3600; //������ת��Ϊ��
		  //FirstOrderReaction(TLast, tLast,T,t,m_NOilToGas,m_fOilToGas,m_FFOilToGas,m_EOilToGas,m_wBIw0OilToGas);  // ���ѽ�Ϊ��
		  m_GasCracked=0;
		  m_C1Cracked=m_GasCracked*m_RatioCrackedC1;    //�����趨�ı������ѽ����ϸ����ֺ���
		  m_C2_C5Cracked=m_GasCracked*(1.-m_RatioCrackedC1);  //�����趨�ı������ѽ����ϸ����ֺ���
		  m_ResidueCracked=0;
		  m_OilCracked=m_GasCracked+m_ResidueCracked;
		  m_C6_C14Cracked=0;  //������������ֵı��������ѽ���
		  m_C15PlusCracked=0;  //������������ֵı��������ѽ���
		  m_GasCrackedAdded=aCompositional.m_GasCrackedAdded+m_GasCracked;
		  m_C1CrackedAdded=aCompositional.m_C1CrackedAdded+m_C1Cracked;
		  m_C2_C5CrackedAdded=aCompositional.m_C2_C5CrackedAdded+m_C2_C5Cracked;

		  m_ResidueCrackedAdded=aCompositional.m_ResidueCrackedAdded+m_ResidueCracked;
		  m_OilCrackedAdded=aCompositional.m_OilCrackedAdded+m_OilCracked;
		  m_C6_C14CrackedAdded=aCompositional.m_C6_C14CrackedAdded+m_C6_C14Cracked;
		  m_C15PlusCrackedAdded=aCompositional.m_C15PlusCrackedAdded+m_C15PlusCracked;

		  m_OilExisted=aCompositional.m_OilExisted;     //ָ����ÿ�������ɺ��ѽ�����Դ���д��ڵ���������û�п��������Ϳ�϶���ܹ����ڵ���
		  m_C6_C14Existed=aCompositional.m_C6_C14Existed;
		  m_C15PlusExisted=aCompositional.m_C15PlusExisted;
		  m_GasExisted=aCompositional.m_GasExisted+m_GasPerInitTOC*m_MassOfInitTOCTotal+m_GasCracked;  //��ʱ�䲽�Ĵ������������Ѿ����ڵ�����������һʱ�䲽���Ҹ����ɵ��������ϸ�ʱ�䲽���ѽ����ɵ�����
		  m_C1Existed=aCompositional.m_C1Existed+m_C1PerInitTOC*m_MassOfInitTOCTotal+m_C1Cracked;
		  m_C2_C5Existed=aCompositional.m_C2_C5Existed+m_C2_C5PerInitTOC*m_MassOfInitTOCTotal+m_C2_C5Cracked;
		  //GetfOilToGas(aCompositional);
	  }
		void SetToItsOrifOilToGas()
		{  
			//��fOilToGas�趨Ϊԭʼֵ����Ҫ�����ڳ�ѹ�ز�ָ�ʱ���ж��ѭ���������Ӧ�ã�
			//��ʹ���¸�ѭ��ʱ�����õ� fOilToGas���µģ��������ϸ�ѭ��������¼�Ľ��
			for(int i=0;i<m_NOilToGas;i++) 
				m_fOilToGas[i]=m_fOilToGasBak[i];
		}
		void GetMKer()
		{   //���Դ���и��Ҹ����л�̼������
			m_MKerTotal=m_TOCKerogen*m_MassOfInitTOCTotal;
			m_MKerInert=m_TOCInertKerogen*m_MassOfInitTOCTotal;
			m_MKerReac= m_MKerTotal-m_MKerInert;
			m_MKerOil=m_TOCOilKerogen*m_MassOfInitTOCTotal;     //new added 20190412
			m_MKerGas=m_TOCGasKerogen*m_MassOfInitTOCTotal;     //new added 20190412
		}
	 };

	/*!
	*
	**/
	struct RoVariable
	{
		double m_Tmax; //��¼ģ��������в�������¶�
		double m_Tmaxb;//��¼ģ������еײ�������¶�
		double m_Tmaxt;//��¼ģ������ж���������¶�
		double m_TTI; //�ز��TTIֵ
		double m_Ro;  //�ز��Ro%ֵ
		double m_TTI0; //��ʼʱ�̵�TTIֵ
		EasyRO m_aParaOfEasyRo; //����һ��EasyRoģ�ͽṹ�����ڴ洢����
		BasinRO m_aParaOfBasinRo; //����һ��BasinRoģ�ͽṹ�����ڴ洢����
		SimpleRO m_aParaOfSimpleRo; //����һ��SimpleRoģ�ͽṹ�����ڴ洢����
		int m_aRoType;
		RoVariable()
		{
			m_Tmax = 0;
			m_TTI = 0;
			m_Ro = 0;
			m_TTI0 = 0.004218;
			m_aRoType = BasinRoType;
		}
		RoVariable(const RoVariable &other)
		{
			*this = other;
		}
		const RoVariable &operator=(const RoVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_Tmax = other.m_Tmax;
			m_Tmaxb = other.m_Tmaxb;
			m_Tmaxt = other.m_Tmaxt;
			m_TTI = other.m_TTI;
			m_Ro = other.m_Ro;
			m_TTI0 = other.m_TTI0;
			m_aParaOfEasyRo = other.m_aParaOfEasyRo;
			m_aParaOfBasinRo = other.m_aParaOfBasinRo;
			m_aParaOfSimpleRo = other.m_aParaOfSimpleRo;
			m_aRoType = other.m_aRoType;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_Tmax;
			curSize += sizeof(double);//double m_Tmaxb;
			curSize += sizeof(double);//double m_Tmaxt;
			curSize += sizeof(double);//double m_TTI;
			curSize += sizeof(double);//double m_Ro;
			curSize += sizeof(double);//double m_TTI0;
			curSize += m_aParaOfBasinRo.GetSerializeDataLength();//BasinRO m_aParaOfBasinRo;
			curSize += m_aParaOfSimpleRo.GetSerializeDataLength();//SimpleRO m_aParaOfSimpleRo;
			curSize += m_aParaOfEasyRo.GetSerializeDataLength();//EasyRO m_aParaOfEasyRo;
			curSize += sizeof(int);//int m_aRoType;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_Tmax, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Tmaxb, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Tmaxt, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TTI, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Ro, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TTI0, sizeof(double));data += sizeof(double);
			m_aParaOfEasyRo.SerializeData(data);
			m_aParaOfBasinRo.SerializeData(data);
			m_aParaOfSimpleRo.SerializeData(data);
			memcpy(data, &m_aRoType, sizeof(int));data += sizeof(int);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_Tmax, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Tmaxb, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Tmaxt, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TTI, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Ro, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TTI0, data, sizeof(double));data += sizeof(double);
			m_aParaOfEasyRo.RestoreSerializeData(data);
			m_aParaOfBasinRo.RestoreSerializeData(data);
			m_aParaOfSimpleRo.RestoreSerializeData(data);
			memcpy(&m_aRoType, data, sizeof(int));data += sizeof(int);
		}
		friend std::ofstream &operator << (std::ofstream &os, RoVariable &ro)
		{
			os << "\r\n>>>>>>>>>>>>>>>RoVariable parameter as flow:"; 
			os << "\r\n---- ---- ---- Tmax:" << ro.m_Tmax;
			os << "\r\n---- ---- ---- Tmaxb:" << ro.m_Tmaxb;
			os << "\r\n---- ---- ---- Tmaxt:" << ro.m_Tmaxt;
			os << "\r\n---- ---- ---- TTI:" << ro.m_TTI;
			os << "\r\n---- ---- ---- Ro:" << ro.m_Ro;
			os << "\r\n---- ---- ---- TTI0:" << ro.m_TTI0;
			os << "\r\n---- ---- ---- aParaOfEasyRo:";os << ro.m_aParaOfEasyRo;
			os << "\r\n---- ---- ---- aParaOfBasinRo:";os << ro.m_aParaOfBasinRo;
			os << "\r\n---- ---- ---- aParaOfSimpleRo:";os << ro.m_aParaOfSimpleRo;
			os << "\r\n---- ---- ---- aRoType:" << ro.m_aRoType;
			return os;
		}
	};

	/*!
	*
	**/
	struct HydroGenerationVariable
	{
		double m_TOC; //�����л�̼����
		double m_InitTOC; //ԭʼ�л�̼���� ,�������ڵĵز������µ�ԭʼ�л�̼���������ֽ����ʯ�ܶ����� ������ֵֻ�����һ��ʱ��ĵز�δ���
		double m_MassOfInitTOC;//�õز�ε�λ�����m^2����ԭʼ�л�̼�������� �� ����ֵֻ�����һ��ʱ��ĵز�δ��� .�ڼ�����֮��Ҳ����ֵ����ÿ��ʱ��ĵز��
		int m_aPetroGenStyle;

		KerogenDegradation m_aDR; //����һ�����Ҹ�����ṹ��
		double m_HCGI; //  ����ǿ�� kg/m^2 �����ڽ�������ģ��
		double m_OGI; //oil generating intensity ,����ǿ�� kg/m^2 �����ڽ�������ģ��
		double m_GGI; //gas generating intensity ,����ǿ�� kg/m^2 �����ڽ�������ģ��

		LLNLKinetics m_aParaLLNL; //����һ��LLNL��ѧ��Ӧ����ѧ�����ṹ��
		OrganoFaciesKinetics m_aOrganofacies; //����һ���л���Ļ�ѧ��Ӧ����ѧ�����ṹ��
		CompositionalKinetics m_aCompositional; //����һ��Behar����ֻ�ѧ��ӳ����ѧ�����ṹ��
		OilInResCracking2C m_aOilInResCracking2C; 
		OilInResCracking4C m_aOilInResCracking4C; 
		
		double m_OGI_LLNL;   //oil generating intensity ,����ǿ�� kg/m^2  ,���ڻ�ѧ��Ӧ����ѧ����ģ��   ,��������Ѿ�û����
		double m_GGI_LLNL;   //gas generating intensity ,����ǿ�� kg/m^2��Ҳ��������λ��  ,���ڻ�ѧ��Ӧ����ѧ����ģ�� ,��������Ѿ�û����
		double m_TOCRemained;//ָ���ǲ����л�̼�ٷֺ���
		double m_MassOfTOCTotal; //��������л�̼����
		HydroGenerationVariable()
		{
			m_aPetroGenStyle = Organo;
			m_TOC = 3.5;
		}
		HydroGenerationVariable(const HydroGenerationVariable &other)
		{
			*this = other;
		}
		const HydroGenerationVariable &operator=(const HydroGenerationVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_TOC = other.m_TOC;
			m_InitTOC = other.m_InitTOC;
			m_MassOfInitTOC = other.m_MassOfInitTOC;
			m_aPetroGenStyle = other.m_aPetroGenStyle;
			m_aDR = other.m_aDR;
			m_HCGI = other.m_HCGI;
			m_OGI = other.m_OGI;
			m_GGI = other.m_GGI;
			m_aParaLLNL = other.m_aParaLLNL;
			m_aOrganofacies = other.m_aOrganofacies;
			m_aCompositional = other.m_aCompositional;
			m_aOilInResCracking2C = other.m_aOilInResCracking2C;
			m_aOilInResCracking4C = other.m_aOilInResCracking4C;
			m_OGI_LLNL = other.m_OGI_LLNL;
			m_GGI_LLNL = other.m_GGI_LLNL;
			m_TOCRemained = other.m_TOCRemained;
			m_MassOfTOCTotal = other.m_MassOfTOCTotal;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_TOC;
			curSize += sizeof(double);//double m_InitTOC;
			curSize += sizeof(double);//double m_MassOfInitTOC;
			curSize += sizeof(int);//PetroGenStyle m_aPetroGenStyle;
			curSize += m_aDR.GetSerializeDataLength();//KerogenDegradation m_aDR;
			curSize += sizeof(double);//double m_HCGI;
			curSize += sizeof(double);//double m_OGI;
			curSize += sizeof(double);//double m_GGI;
			curSize += m_aParaLLNL.GetSerializeDataLength();//LLNLKinetics m_aParaLLNL;
			curSize += m_aOrganofacies.GetSerializeDataLength();//OrganoFaciesKinetics m_aOrganofacies;
			curSize += m_aCompositional.GetSerializeDataLength();//CompositionalKinetics m_aCompositional;
			curSize += m_aOilInResCracking2C.GetSerializeDataLength();//OilInResCracking2C m_aOilInResCracking2C; 
			curSize += m_aOilInResCracking4C.GetSerializeDataLength();//OilInResCracking4C m_aOilInResCracking4C; 
			curSize += sizeof(double);//double m_OGI_LLNL;
			curSize += sizeof(double);//double m_GGI_LLNL;
			curSize += sizeof(double);//double m_TOCRemained;
			curSize += sizeof(double);//double m_MassOfTOCTotal;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_TOC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_InitTOC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MassOfInitTOC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_aPetroGenStyle, sizeof(int));data += sizeof(int);
			m_aDR.SerializeData(data);
			memcpy(data, &m_HCGI, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OGI, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GGI, sizeof(double));data += sizeof(double); 
			m_aParaLLNL.SerializeData(data); 
			m_aOrganofacies.SerializeData(data); 
			m_aCompositional.SerializeData(data); 
			m_aOilInResCracking2C.SerializeData(data); 
			m_aOilInResCracking4C.SerializeData(data); 
			memcpy(data, &m_OGI_LLNL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GGI_LLNL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TOCRemained, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MassOfTOCTotal, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_TOC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_InitTOC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MassOfInitTOC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_aPetroGenStyle, data, sizeof(int));data += sizeof(int);
			m_aDR.RestoreSerializeData(data);
			memcpy(&m_HCGI, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OGI, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GGI, data, sizeof(double));data += sizeof(double); 
			m_aParaLLNL.RestoreSerializeData(data);
			m_aOrganofacies.RestoreSerializeData(data);
			m_aCompositional.RestoreSerializeData(data); 
			m_aOilInResCracking2C.RestoreSerializeData(data); 
			m_aOilInResCracking4C.RestoreSerializeData(data); 
			memcpy(&m_OGI_LLNL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GGI_LLNL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TOCRemained, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MassOfTOCTotal, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, HydroGenerationVariable &hydrogeneration)
		{
			os << "\r\n>>>>>>>>>>>>>>>HydroGenerationVariable parameter as flow:";
			os << "\r\n---- ---- ---- TOC:" << hydrogeneration.m_TOC;
			os << "\r\n---- ---- ---- InitTOC:" << hydrogeneration.m_InitTOC;
			os << "\r\n---- ---- ---- MassOfInitTOC:" << hydrogeneration.m_MassOfInitTOC;
			os << "\r\n---- ---- ---- aPetroGenStyle:" << hydrogeneration.m_aPetroGenStyle;
			os << "\r\n---- ---- ---- aDR:";os << hydrogeneration.m_aDR;
			os << "\r\n---- ---- ---- HCGI:" << hydrogeneration.m_HCGI;
			os << "\r\n---- ---- ---- OGI:" << hydrogeneration.m_OGI;
			os << "\r\n---- ---- ---- GGI:" << hydrogeneration.m_GGI;
			os << "\r\n---- ---- ---- aParaLLNL:";os << hydrogeneration.m_aParaLLNL;
			os << "\r\n---- ---- ---- aOrganofacies:";os << hydrogeneration.m_aOrganofacies;
			os << "\r\n---- ---- ---- aCompositional:";os << hydrogeneration.m_aCompositional;
			os << "\r\n---- ---- ---- aOilInResCracking2C:";os << hydrogeneration.m_aOilInResCracking2C;
			os << "\r\n---- ---- ---- aOilInResCracking4C:";os << hydrogeneration.m_aOilInResCracking4C;
			os << "\r\n---- ---- ---- OGI_LLNL:" << hydrogeneration.m_OGI_LLNL;
			os << "\r\n---- ---- ---- GGI_LLNL:" << hydrogeneration.m_GGI_LLNL;
			os << "\r\n---- ---- ---- TOCRemained:" << hydrogeneration.m_TOCRemained;
			os << "\r\n---- ---- ---- MassOfTOCTotal:" << hydrogeneration.m_MassOfTOCTotal;
			return os;
		}
	};

	/*!
	*
	**/
	struct HydroExpellVariable
	{
		double m_aO;//������ϵ��Oil sorption cofficient ����λ��g/gC
		double m_aG;//������ϵ��Gas sorption cofficient ����λ��g/gC
		double m_MKer; //Դ���и��Ҹ����������л�̼��ʽ��������λ��kg
		double m_COS; //Critical oil saturation �ٽ����ͱ��Ͷ�
		double m_CGS; // Critical Gas saturation �ٽ��������Ͷ�
		double m_MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
		double m_MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
		double m_MKerOil; //Դ���п����͵ĸ��Ҹ��������л�̼��ʽ��������λ��kg   new added 20190412
		double m_MKerGas; //Դ���п������ĸ��Ҹ��� �����л�̼��ʽ��������λ��kg  new added 20190412
		double m_MAdxOil; //Դ�����͵�����������λ��kg
		double m_MAdxGas; //Դ������������������λ��kg
		double m_MAdxMaxOil; //Դ�����͵��������������λ��kg
		double m_MAdxMaxGas; //Դ���������������������λ��kg
		double m_MExpOil; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
		double m_MExpGas; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
		double m_MExpOilAdded; //Դ���ۻ�����������λ��kg ��
		double m_MExpGasAdded; //Դ���ۻ�����������λ��kg ��
		double m_MResidualOil;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
		double m_MResidualGas;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
		//double m_OilInSourceRockPoros,m_GasInSourceRockPoros; //�ֱ�ΪԴ�ҿ�϶�е��ͺ����������ڻ�û�п��ǣ���ʱ������Ϊ0�����ڿ��Կ��ǲ�Ϊ0�����
		double m_OilOutOfSourceRock,m_GasOutOfSourceRock; //�ֱ�Ϊ���Ƶ�Դ������ۼƵ��ͺ�����
		double m_OGIFromKerogen,m_GGIFromKerogen; //ָԴ�Ҹ��Ҹ��ۻ��������������� ��������ǰ��OGI_LLNL��GGI_LLNL ������Ҳ������ͬ������ó�����ֻ�Ǹ��Ҹ����ɵ���������������û�п������ѽ���ٵ����������ӵ�����
		double m_OilCrackedAdded; //Դ�����ۻ������ѽ���
		double m_GasCrackedAdded; //Դ�����ۻ������ѽ���
		double m_CokeAdded;//Դ�������ѽ�����Ľ�̿��
		double m_TR; //Դ�ҵ�����ת����

		//����Ϊ��������йصĲ���
		double m_MAdxMaxC1;
		double m_MAdxMaxC2_C5;
		double m_MAdxMaxC6_C14;
		double m_MAdxMaxC15Plus;
		double m_MAdxC1;
		double m_MAdxC2_C5;
		double m_MAdxC6_C14;
		double m_MAdxC15Plus;  //�����������
		double m_MExpC1;
		double m_MExpC2_C5;
		double m_MExpC6_C14;
		double m_MExpC15Plus;  //�ų��������
		double m_MExpC1Added;
		double m_MExpC2_C5Added;
		double m_MExpC6_C14Added;
		double m_MExpC15PlusAdded;  //�ۻ��ų��������,ָ���ǽ����϶�ռ�������������
		//double m_C1InSourceRockPoros;
		//double m_C2_C5InSourceRockPoros;
		//double m_C6_C14InSourceRockPoros;
		//double m_C15PlusInSourceRockPoros; // Դ���п�϶�е��������
		double m_MResidualC1;
		double m_MResidualC2_C5;
		double m_MResidualC6_C14;
		double m_MResidualC15Plus;//Դ���в�����������������������Դ�ҿ�϶�е���
		double m_C1OutOfSourceRock;
		double m_C2_C5OutOfSourceRock;
		double m_C6_C14OutOfSourceRock;
		double m_C15PlusOutOfSourceRock; //�ų�Դ������������
		double m_C1CrackedAdded;
		double m_C2_C5CrackedAdded;
		double m_C6_C14CrackedAdded;
		double m_C15PlusCrackedAdded;    //Դ��������ֵ��ۻ��ѽ���

		double m_OilInRockPoros;
		double m_GasInRockPoros; //�ֱ�Ϊ��ʯ������Դ�Һͷ�Դ�ң���϶�е��ͺ�����������
		double m_C1InRockPoros;
		double m_C2_C5InRockPoros;
		double m_C6_C14InRockPoros;
		double m_C15PlusInRockPoros; // ��ʯ������Դ�Һͷ�Դ�ң���϶�е��������������
		std::vector<std::vector<double> > m_fOilToGasFlowInOil;
		std::vector<double> m_MassFlowInOil;
		std::vector<double> m_MassFlowInGas;  //�����Ǻ���ģ��������������������������������
		//����Ϊ��������йصĲ���
		double m_CrackedGasRatio; //���ѽ����ռ��϶���ı���
		double m_CrackedC1Ratio; //���ѽ��C1ռ��϶C1�ı���
		double m_CrackedC2_C5Ratio; //���ѽ��C2_C5ռ��϶C2_C5�ı���
		double m_CrackedGasInRockPoros; //��϶�е����ѽ���
		double m_CrackedC1InRockPoros; //��϶�е����ѽ�C1
		double m_CrackedC2_C5InRockPoros; //��϶�е����ѽ�C2_C5
		double m_RatioCrackedC1;  //��ʱ�����ѽ�Ϊ����C1�ı���Ϊ0.7�� �������������ڿ��Ը��ݽ�һ�������ϵ���

		HydroExpellVariable()
		{
			m_MExpOil = 0.;
			m_MExpGas = 0.;
			m_OGIFromKerogen = 0;
			m_GGIFromKerogen = 0;
			m_OilInRockPoros = 0;
			m_GasInRockPoros = 0;
			m_C1InRockPoros = 0;
			m_C2_C5InRockPoros = 0;
			m_C6_C14InRockPoros = 0;
			m_C15PlusInRockPoros = 0;
			m_MExpOilAdded = 0;
			m_MExpGasAdded = 0;
			m_OilCrackedAdded = 0;
			m_GasCrackedAdded = 0;
			m_CokeAdded = 0;
			m_MExpC1Added = 0;
			m_MExpC2_C5Added = 0;
			m_MExpC6_C14Added = 0;
			m_MExpC15PlusAdded = 0;
			m_C1CrackedAdded = 0;
			m_C2_C5CrackedAdded = 0;
			m_C6_C14CrackedAdded = 0;
			m_C15PlusCrackedAdded = 0;
		}
		HydroExpellVariable(const HydroExpellVariable &other)
		{
			*this = other;
		}
		const HydroExpellVariable &operator=(const HydroExpellVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_aO = other.m_aO;//������ϵ��Oil sorption cofficient ����λ��g/gC
			m_aG = other.m_aG;//������ϵ��Gas sorption cofficient ����λ��g/gC
			m_MKer = other.m_MKer; //Դ���и��Ҹ����������л�̼��ʽ��������λ��kg
			m_COS = other.m_COS; //Critical oil saturation �ٽ����ͱ��Ͷ�
			m_CGS = other.m_CGS; // Critical Gas saturation �ٽ��������Ͷ�
			m_MKerReac = other.m_MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
			m_MKerInert = other.m_MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
			m_MKerOil = other.m_MKerOil; //Դ���п����͵ĸ��Ҹ��� �����л�̼��ʽ��������λ��kg
			m_MKerGas = other.m_MKerGas; //Դ���п������ĸ��Ҹ��� �����л�̼��ʽ��������λ��kg
			m_MAdxOil = other.m_MAdxOil; //Դ�����͵�����������λ��kg
			m_MAdxGas = other.m_MAdxGas; //Դ������������������λ��kg
			m_MAdxMaxOil = other.m_MAdxMaxOil; //Դ�����͵��������������λ��kg
			m_MAdxMaxGas = other.m_MAdxMaxGas; //Դ���������������������λ��kg
			m_MExpOil = other.m_MExpOil; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
			m_MExpGas = other.m_MExpGas; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
			m_MExpOilAdded = other.m_MExpOilAdded; //Դ���ۻ�����������λ��kg ��
			m_MExpGasAdded = other.m_MExpGasAdded; //Դ���ۻ�����������λ��kg ��
			m_MResidualOil = other.m_MResidualOil;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
			m_MResidualGas = other.m_MResidualGas;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
			m_OilOutOfSourceRock = other.m_OilOutOfSourceRock;
			m_GasOutOfSourceRock = other.m_GasOutOfSourceRock; //�ֱ�Ϊ���Ƶ�Դ������ۼƵ��ͺ�����
			m_OGIFromKerogen = other.m_OGIFromKerogen;
			m_GGIFromKerogen = other.m_GGIFromKerogen; //ָԴ�Ҹ��Ҹ��ۻ��������������� ��������ǰ��OGI_LLNL��GGI_LLNL ������Ҳ������ͬ������ó�����ֻ�Ǹ��Ҹ����ɵ���������������û�п������ѽ���ٵ����������ӵ�����
			m_OilCrackedAdded = other.m_OilCrackedAdded; //Դ�����ۻ������ѽ���
			m_GasCrackedAdded = other.m_GasCrackedAdded; //Դ�����ۻ������ѽ���
			m_CokeAdded = other.m_CokeAdded;//Դ�������ѽ�����Ľ�̿��
			m_TR = other.m_TR;//Դ�ҵ�����ת����

			m_MAdxMaxC1 = other.m_MAdxMaxC1;
			m_MAdxMaxC2_C5 = other.m_MAdxMaxC2_C5;
			m_MAdxMaxC6_C14 = other.m_MAdxMaxC6_C14;
			m_MAdxMaxC15Plus = other.m_MAdxMaxC15Plus;
			m_MAdxC1 = other.m_MAdxC1;
			m_MAdxC2_C5 = other.m_MAdxC2_C5;
			m_MAdxC6_C14 = other.m_MAdxC6_C14;
			m_MAdxC15Plus = other.m_MAdxC15Plus;  
			m_MExpC1 = other.m_MExpC1;
			m_MExpC2_C5 = other.m_MExpC2_C5;
			m_MExpC6_C14 = other.m_MExpC6_C14;
			m_MExpC15Plus = other.m_MExpC15Plus;  
			m_MExpC1Added = other.m_MExpC1Added;
			m_MExpC2_C5Added = other.m_MExpC2_C5Added;
			m_MExpC6_C14Added = other.m_MExpC6_C14Added;
			m_MExpC15PlusAdded = other.m_MExpC15PlusAdded;  
			m_MResidualC1 = other.m_MResidualC1;
			m_MResidualC2_C5 = other.m_MResidualC2_C5;
			m_MResidualC6_C14 = other.m_MResidualC6_C14;
			m_MResidualC15Plus = other.m_MResidualC15Plus; 
			m_C1OutOfSourceRock = other.m_C1OutOfSourceRock;
			m_C2_C5OutOfSourceRock = other.m_C2_C5OutOfSourceRock;
			m_C6_C14OutOfSourceRock = other.m_C6_C14OutOfSourceRock;
			m_C15PlusOutOfSourceRock = other.m_C15PlusOutOfSourceRock; 
			m_C1CrackedAdded = other.m_C1CrackedAdded;
			m_C2_C5CrackedAdded = other.m_C2_C5CrackedAdded;
			m_C6_C14CrackedAdded = other.m_C6_C14CrackedAdded;
			m_C15PlusCrackedAdded = other.m_C15PlusCrackedAdded;    
			m_OilInRockPoros = other.m_OilInRockPoros;
			m_GasInRockPoros = other.m_GasInRockPoros;
			m_C1InRockPoros = other.m_C1InRockPoros;
			m_C2_C5InRockPoros = other.m_C2_C5InRockPoros;
			m_C6_C14InRockPoros = other.m_C6_C14InRockPoros;
			m_C15PlusInRockPoros = other.m_C15PlusInRockPoros;
			m_fOilToGasFlowInOil = other.m_fOilToGasFlowInOil;
			m_MassFlowInOil = other.m_MassFlowInOil;
			m_MassFlowInGas = other.m_MassFlowInGas;
			m_CrackedGasRatio = other.m_CrackedGasRatio;
			m_CrackedC1Ratio = other.m_CrackedC1Ratio;
			m_CrackedC2_C5Ratio = other.m_CrackedC2_C5Ratio;
			m_CrackedGasInRockPoros = other.m_CrackedGasInRockPoros;
			m_CrackedC1InRockPoros = other.m_CrackedC1InRockPoros;
			m_CrackedC2_C5InRockPoros = other.m_CrackedC2_C5InRockPoros;
			m_RatioCrackedC1 = other.m_RatioCrackedC1;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_aO;
			curSize += sizeof(double);//double m_aG;
			curSize += sizeof(double);//double m_MKer;
			curSize += sizeof(double);//double m_COS;
			curSize += sizeof(double);//double m_CGS;
			curSize += sizeof(double);//double m_MKerReac;
			curSize += sizeof(double);//double m_MKerInert;
			curSize += sizeof(double);//double m_MKerOil;
			curSize += sizeof(double);//double m_MKerGas;
			curSize += sizeof(double);//double m_MAdxOil;
			curSize += sizeof(double);//double m_MAdxGas;
			curSize += sizeof(double);//double m_MAdxMaxOil;
			curSize += sizeof(double);//double m_MAdxMaxGas;
			curSize += sizeof(double);//double m_MExpOil;
			curSize += sizeof(double);//double m_MExpGas;
			curSize += sizeof(double);//double m_MExpOilAdded;
			curSize += sizeof(double);//double m_MExpGasAdded;
			curSize += sizeof(double);//double m_MResidualOil;
			curSize += sizeof(double);//double m_MResidualGas;
			curSize += sizeof(double);//double m_OilOutOfSourceRock;
			curSize += sizeof(double);//double m_GasOutOfSourceRock;
			curSize += sizeof(double);//double m_OGIFromKerogen;
			curSize += sizeof(double);//double m_GGIFromKerogen;
			curSize += sizeof(double);//double m_OilCrackedAdded;
			curSize += sizeof(double);//double m_GasCrackedAdded;
			curSize += sizeof(double);//double m_CokeAdded;
			curSize += sizeof(double);//double m_TR;
			curSize += sizeof(double);//double m_MAdxMaxC1;
			curSize += sizeof(double);//double m_MAdxMaxC2_C5;
			curSize += sizeof(double);//double m_MAdxMaxC6_C14;
			curSize += sizeof(double);//double m_MAdxMaxC15Plus;
			curSize += sizeof(double);//double m_MAdxC1;
			curSize += sizeof(double);//double m_MAdxC2_C5;
			curSize += sizeof(double);//double m_MAdxC6_C14;
			curSize += sizeof(double);//double m_MAdxC15Plus;
			curSize += sizeof(double);//double m_MExpC1;
			curSize += sizeof(double);//double m_MExpC2_C5;
			curSize += sizeof(double);//double m_MExpC6_C14;
			curSize += sizeof(double);//double m_MExpC15Plus;
			curSize += sizeof(double);//double m_MExpC1Added;
			curSize += sizeof(double);//double m_MExpC2_C5Added;
			curSize += sizeof(double);//double m_MExpC6_C14Added;
			curSize += sizeof(double);//double m_MExpC15PlusAdded;
			curSize += sizeof(double);//double m_MResidualC1;
			curSize += sizeof(double);//double m_MResidualC2_C5;
			curSize += sizeof(double);//double m_MResidualC6_C14;
			curSize += sizeof(double);//double m_MResidualC15Plus;
			curSize += sizeof(double);//double m_C1OutOfSourceRock;
			curSize += sizeof(double);//double m_C2_C5OutOfSourceRock;
			curSize += sizeof(double);//double m_C6_C14OutOfSourceRock;
			curSize += sizeof(double);//double m_C15PlusOutOfSourceRock;
			curSize += sizeof(double);//double m_C1CrackedAdded;
			curSize += sizeof(double);//double m_C2_C5CrackedAdded;
			curSize += sizeof(double);//double m_C6_C14CrackedAdded;
			curSize += sizeof(double);//double m_C15PlusCrackedAdded;
			curSize += sizeof(double);//double m_OilInRockPoros;
			curSize += sizeof(double);//double m_GasInRockPoros;
			curSize += sizeof(double);//double m_C1InRockPoros;
			curSize += sizeof(double);//double m_C2_C5InRockPoros;
			curSize += sizeof(double);//double m_C6_C14InRockPoros;
			curSize += sizeof(double);//double m_C15PlusInRockPoros;
			curSize += sizeof(int);//std::vector<std::vector<double> > m_fOilToGasFlowInOil;
			for(int i = 0; i < m_fOilToGasFlowInOil.size(); i++)
			{
				curSize += (sizeof(int) + m_fOilToGasFlowInOil[i].size() * sizeof(double));
			}
			curSize += (sizeof(int) + m_MassFlowInOil.size() * sizeof(double));//std::vector<double> m_MassFlowInOil;
			curSize += (sizeof(int) + m_MassFlowInGas.size() * sizeof(double));//std::vector<double> m_MassFlowInGas;
			curSize += sizeof(double);//double m_CrackedGasRatio;
			curSize += sizeof(double);//double m_CrackedC1Ratio; 
			curSize += sizeof(double);//double m_CrackedC2_C5Ratio; 
			curSize += sizeof(double);//double m_CrackedGasInRockPoros;
			curSize += sizeof(double);//double m_CrackedC1InRockPoros;
			curSize += sizeof(double);//double m_CrackedC2_C5InRockPoros;
			curSize += sizeof(double);//double m_RatioCrackedC1;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_aO, sizeof(double));data += sizeof(double);
			memcpy(data, &m_aG, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MKer, sizeof(double));data += sizeof(double);
			memcpy(data, &m_COS, sizeof(double));data += sizeof(double);
			memcpy(data, &m_CGS, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MKerReac, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MKerInert, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MKerOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MKerGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxMaxOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxMaxGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpOilAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpGasAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MResidualOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MResidualGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilOutOfSourceRock, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GasOutOfSourceRock, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OGIFromKerogen, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GGIFromKerogen, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GasCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_CokeAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TR, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxMaxC1, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxMaxC2_C5, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxMaxC6_C14, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxMaxC15Plus, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxC1, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxC2_C5, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxC6_C14, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MAdxC15Plus, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC1, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC2_C5, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC6_C14, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC15Plus, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC1Added, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC2_C5Added, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC6_C14Added, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MExpC15PlusAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MResidualC1, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MResidualC2_C5, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MResidualC6_C14, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MResidualC15Plus, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C1OutOfSourceRock, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C2_C5OutOfSourceRock, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C6_C14OutOfSourceRock, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C15PlusOutOfSourceRock, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C1CrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C2_C5CrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C6_C14CrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_C15PlusCrackedAdded, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilInRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasInRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C1InRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C2_C5InRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C6_C14InRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C15PlusInRockPoros, sizeof(double));data += sizeof(double); 
			int fOilToGasFlowInOilsize = m_fOilToGasFlowInOil.size();
			memcpy(data, &fOilToGasFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fOilToGasFlowInOilsize; i++)
			{
				int fOilToGasFlowInOilisize = m_fOilToGasFlowInOil[i].size();
				memcpy(data, &fOilToGasFlowInOilisize, sizeof(int));data += sizeof(int);
				for(int j = 0; j < fOilToGasFlowInOilisize; j++)
				{
					memcpy(data, &(m_fOilToGasFlowInOil[i][j]), sizeof(double));data += sizeof(double);
				}
			}
			int MassFlowInOilsize = m_MassFlowInOil.size();
			memcpy(data, &MassFlowInOilsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInOilsize; i++)
			{
				memcpy(data, &(m_MassFlowInOil[i]), sizeof(double));data += sizeof(double);
			}
			int MassFlowInGassize = m_MassFlowInGas.size();
			memcpy(data, &MassFlowInGassize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MassFlowInGassize; i++)
			{
				memcpy(data, &(m_MassFlowInGas[i]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &m_CrackedGasRatio, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_CrackedC1Ratio, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_CrackedC2_C5Ratio, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_CrackedGasInRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_CrackedC1InRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_CrackedC2_C5InRockPoros, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_RatioCrackedC1, sizeof(double));data += sizeof(double); 
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_aO, data, sizeof(double));data += sizeof(double);
			memcpy(&m_aG, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MKer, data, sizeof(double));data += sizeof(double);
			memcpy(&m_COS, data, sizeof(double));data += sizeof(double);
			memcpy(&m_CGS, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MKerReac, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MKerInert, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MKerOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MKerGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxMaxOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxMaxGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpOilAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpGasAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MResidualOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MResidualGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilOutOfSourceRock, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GasOutOfSourceRock, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OGIFromKerogen, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GGIFromKerogen, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GasCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_CokeAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TR, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxMaxC1, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxMaxC2_C5, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxMaxC6_C14, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxMaxC15Plus, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxC1, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxC2_C5, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxC6_C14, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MAdxC15Plus, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC1, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC2_C5, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC6_C14, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC15Plus, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC1Added, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC2_C5Added, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC6_C14Added, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MExpC15PlusAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MResidualC1, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MResidualC2_C5, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MResidualC6_C14, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MResidualC15Plus, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C1OutOfSourceRock, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C2_C5OutOfSourceRock, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C6_C14OutOfSourceRock, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C15PlusOutOfSourceRock, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C1CrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C2_C5CrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C6_C14CrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_C15PlusCrackedAdded, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilInRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasInRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C1InRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C2_C5InRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C6_C14InRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C15PlusInRockPoros, data, sizeof(double));data += sizeof(double); 
			int fOilToGasFlowInOilsize;
			memcpy(&fOilToGasFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_fOilToGasFlowInOil.resize(fOilToGasFlowInOilsize);
			for(int i = 0; i < fOilToGasFlowInOilsize; i++)
			{
				int fOilToGasFlowInOilisize;
				memcpy(&fOilToGasFlowInOilisize, data, sizeof(int));data += sizeof(int);
				m_fOilToGasFlowInOil[i].resize(fOilToGasFlowInOilisize);
				for(int j = 0; j < fOilToGasFlowInOilisize; j++)
				{
					memcpy(&(m_fOilToGasFlowInOil[i][j]), data, sizeof(double));data += sizeof(double);
				}
			}
			int MassFlowInOilsize;
			memcpy(&MassFlowInOilsize, data, sizeof(int));data += sizeof(int);
			m_MassFlowInOil.resize(MassFlowInOilsize);
			for(int i = 0; i < MassFlowInOilsize; i++)
			{
				memcpy(&(m_MassFlowInOil[i]), data, sizeof(double));data += sizeof(double);
			}
			int MassFlowInGassize;
			memcpy(&MassFlowInGassize, data, sizeof(int));data += sizeof(int);
			m_MassFlowInGas.resize(MassFlowInGassize);
			for(int i = 0; i < MassFlowInGassize; i++)
			{
				memcpy(&(m_MassFlowInGas[i]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&m_CrackedGasRatio, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_CrackedC1Ratio, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_CrackedC2_C5Ratio, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_CrackedGasInRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_CrackedC1InRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_CrackedC2_C5InRockPoros, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_RatioCrackedC1, data, sizeof(double));data += sizeof(double); 
		}
		friend std::ofstream &operator << (std::ofstream &os, HydroExpellVariable &hydroexpell)
		{
			os << "\r\n>>>>>>>>>>>>>>>HydroExpellVariable parameter as flow:";
			os << "\r\n---- ---- ---- aO:" << hydroexpell.m_aO;//������ϵ��Oil sorption cofficient ����λ��g/gC
			os << "\r\n---- ---- ---- aG:" << hydroexpell.m_aG;//������ϵ��Gas sorption cofficient ����λ��g/gC
			os << "\r\n---- ---- ---- MKer:" << hydroexpell.m_MKer; //Դ���и��Ҹ����������л�̼��ʽ��������λ��kg
			os << "\r\n---- ---- ---- COS:" << hydroexpell.m_COS; //Critical oil saturation �ٽ����ͱ��Ͷ�
			os << "\r\n---- ---- ---- CGS:" << hydroexpell.m_CGS; // Critical Gas saturation �ٽ��������Ͷ�
			os << "\r\n---- ---- ---- MKerReac:" << hydroexpell.m_MKerReac; //Դ���пɷ�Ӧ�ĸ��Ҹ��������л�̼��ʽ��������λ��kg
			os << "\r\n---- ---- ---- MKerInert:" << hydroexpell.m_MKerInert; //Դ������Ч���Ҹ��� �����л�̼��ʽ��������λ��kg
			os << "\r\n---- ---- ---- MKerOil:" << hydroexpell.m_MKerOil; //Դ���п����͵ĸ��Ҹ��� �����л�̼��ʽ��������λ��kg
			os << "\r\n---- ---- ---- MKerGas:" << hydroexpell.m_MKerGas; //Դ���п������ĸ��Ҹ��� �����л�̼��ʽ��������λ��kg
			os << "\r\n---- ---- ---- MAdxOil:" << hydroexpell.m_MAdxOil; //Դ�����͵�����������λ��kg
			os << "\r\n---- ---- ---- MAdxGas:" << hydroexpell.m_MAdxGas; //Դ������������������λ��kg
			os << "\r\n---- ---- ---- MAdxMaxOil:" << hydroexpell.m_MAdxMaxOil; //Դ�����͵��������������λ��kg
			os << "\r\n---- ---- ---- MAdxMaxGas:" << hydroexpell.m_MAdxMaxGas; //Դ���������������������λ��kg
			os << "\r\n---- ---- ---- MExpOil:" << hydroexpell.m_MExpOil; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
			os << "\r\n---- ---- ---- MExpGas:" << hydroexpell.m_MExpGas; //Դ������������λ��kg ����ָ��һ��ʱ�䲽�����ɸ��Ҹ�������Դ���޻���϶�е���
			os << "\r\n---- ---- ---- MExpOilAdded:" << hydroexpell.m_MExpOilAdded; //Դ���ۻ�����������λ��kg ��
			os << "\r\n---- ---- ---- MExpGasAdded:" << hydroexpell.m_MExpGasAdded; //Դ���ۻ�����������λ��kg ��
			os << "\r\n---- ---- ---- MResidualOil:" << hydroexpell.m_MResidualOil;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
			os << "\r\n---- ---- ---- MResidualGas:" << hydroexpell.m_MResidualGas;  //Դ�Ҳ�����������ָ�����������޻��ʿ�϶�е�����
			os << "\r\n---- ---- ---- OilOutOfSourceRock:" << hydroexpell.m_OilOutOfSourceRock;
			os << "\r\n---- ---- ---- GasOutOfSourceRock:" << hydroexpell.m_GasOutOfSourceRock; //�ֱ�Ϊ���Ƶ�Դ������ۼƵ��ͺ�����
			os << "\r\n---- ---- ---- OGIFromKerogen:" << hydroexpell.m_OGIFromKerogen;
			os << "\r\n---- ---- ---- GGIFromKerogen:" << hydroexpell.m_GGIFromKerogen; //ָԴ�Ҹ��Ҹ��ۻ��������������� ��������ǰ��OGI_LLNL��GGI_LLNL ������Ҳ������ͬ������ó�����ֻ�Ǹ��Ҹ����ɵ���������������û�п������ѽ���ٵ����������ӵ�����
			os << "\r\n---- ---- ---- OilCrackedAdded:" << hydroexpell.m_OilCrackedAdded; //Դ�����ۻ������ѽ���
			os << "\r\n---- ---- ---- GasCrackedAdded:" << hydroexpell.m_GasCrackedAdded; //Դ�����ۻ������ѽ���
			os << "\r\n---- ---- ---- CokeAdded:" << hydroexpell.m_CokeAdded;//Դ�������ѽ�����Ľ�̿��
			os << "\r\n---- ---- ---- TR:" << hydroexpell.m_TR;//Դ�ҵ�����ת����
			os << "\r\n---- ---- ---- MAdxMaxC1:" << hydroexpell.m_MAdxMaxC1;
			os << "\r\n---- ---- ---- MAdxMaxC2_C5:" << hydroexpell.m_MAdxMaxC2_C5;
			os << "\r\n---- ---- ---- MAdxMaxC6_C14:" << hydroexpell.m_MAdxMaxC6_C14;
			os << "\r\n---- ---- ---- MAdxMaxC15Plus:" << hydroexpell.m_MAdxMaxC15Plus;
			os << "\r\n---- ---- ---- MAdxC1:" << hydroexpell.m_MAdxC1;
			os << "\r\n---- ---- ---- MAdxC2_C5:" << hydroexpell.m_MAdxC2_C5;
			os << "\r\n---- ---- ---- MAdxC6_C14:" << hydroexpell.m_MAdxC6_C14;
			os << "\r\n---- ---- ---- MAdxC15Plus:" << hydroexpell.m_MAdxC15Plus;  
			os << "\r\n---- ---- ---- MExpC1:" << hydroexpell.m_MExpC1;
			os << "\r\n---- ---- ---- MExpC2_C5:" << hydroexpell.m_MExpC2_C5;
			os << "\r\n---- ---- ---- MExpC6_C14:" << hydroexpell.m_MExpC6_C14;
			os << "\r\n---- ---- ---- MExpC15Plus:" << hydroexpell.m_MExpC15Plus;  
			os << "\r\n---- ---- ---- MExpC1Added:" << hydroexpell.m_MExpC1Added;
			os << "\r\n---- ---- ---- MExpC2_C5Added:" << hydroexpell.m_MExpC2_C5Added;
			os << "\r\n---- ---- ---- MExpC6_C14Added:" << hydroexpell.m_MExpC6_C14Added;
			os << "\r\n---- ---- ---- MExpC15PlusAdded:" << hydroexpell.m_MExpC15PlusAdded;  
			os << "\r\n---- ---- ---- MResidualC1:" << hydroexpell.m_MResidualC1;
			os << "\r\n---- ---- ---- MResidualC2_C5:" << hydroexpell.m_MResidualC2_C5;
			os << "\r\n---- ---- ---- MResidualC6_C14:" << hydroexpell.m_MResidualC6_C14;
			os << "\r\n---- ---- ---- MResidualC15Plus:" << hydroexpell.m_MResidualC15Plus; 
			os << "\r\n---- ---- ---- C1OutOfSourceRock:" << hydroexpell.m_C1OutOfSourceRock;
			os << "\r\n---- ---- ---- C2_C5OutOfSourceRock:" << hydroexpell.m_C2_C5OutOfSourceRock;
			os << "\r\n---- ---- ---- C6_C14OutOfSourceRock:" << hydroexpell.m_C6_C14OutOfSourceRock;
			os << "\r\n---- ---- ---- C15PlusOutOfSourceRock:" << hydroexpell.m_C15PlusOutOfSourceRock; 
			os << "\r\n---- ---- ---- C1CrackedAdded:" << hydroexpell.m_C1CrackedAdded;
			os << "\r\n---- ---- ---- C2_C5CrackedAdded:" << hydroexpell.m_C2_C5CrackedAdded;
			os << "\r\n---- ---- ---- C6_C14CrackedAdded:" << hydroexpell.m_C6_C14CrackedAdded;
			os << "\r\n---- ---- ---- C15PlusCrackedAdded:" << hydroexpell.m_C15PlusCrackedAdded;
			os << "\r\n---- ---- ---- OilInRockPoros:" << hydroexpell.m_OilInRockPoros;
			os << "\r\n---- ---- ---- GasInRockPoros:" << hydroexpell.m_GasInRockPoros;
			os << "\r\n---- ---- ---- C1InRockPoros:" << hydroexpell.m_C1InRockPoros;
			os << "\r\n---- ---- ---- C2_C5InRockPoros:" << hydroexpell.m_C2_C5InRockPoros;
			os << "\r\n---- ---- ---- C6_C14InRockPoros:" << hydroexpell.m_C6_C14InRockPoros;
			os << "\r\n---- ---- ---- C15PlusInRockPoros:" << hydroexpell.m_C15PlusInRockPoros;
			for(int i = 0; i < hydroexpell.m_fOilToGasFlowInOil.size(); i++)
			{
				for(int j = 0; j < hydroexpell.m_fOilToGasFlowInOil[i].size(); j++)
				{
					os << "\r\n---- ---- ---- m_fOilToGasFlowInOil:" << i << ":" << j << ":" << hydroexpell.m_fOilToGasFlowInOil[i][j];
				}
			}
			for(int i = 0; i < hydroexpell.m_MassFlowInOil.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInOil:" << i << ":" << hydroexpell.m_MassFlowInOil[i];
			}
			for(int i = 0; i < hydroexpell.m_MassFlowInGas.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MassFlowInGas:" << i << ":" << hydroexpell.m_MassFlowInGas[i];
			}
			os << "\r\n---- ---- ---- CrackedGasRatio:" << hydroexpell.m_CrackedGasRatio;
			os << "\r\n---- ---- ---- CrackedC1Ratio:" << hydroexpell.m_CrackedC1Ratio;
			os << "\r\n---- ---- ---- CrackedC2_C5Ratio:" << hydroexpell.m_CrackedC2_C5Ratio;
			os << "\r\n---- ---- ---- CrackedGasInRockPoros:" << hydroexpell.m_CrackedGasInRockPoros;
			os << "\r\n---- ---- ---- CrackedC1InRockPoros:" << hydroexpell.m_CrackedC1InRockPoros;
			os << "\r\n---- ---- ---- CrackedC2_C5InRockPoros:" << hydroexpell.m_CrackedC2_C5InRockPoros;
			os << "\r\n---- ---- ---- RatioCrackedC1:" << hydroexpell.m_RatioCrackedC1;
			return os;    
		}

	};
	
	enum HCType{OilGas,Oil,Gas,NoOG};  //�����������ͣ�������̬����õ�,�ֱ����������ࡢ�͡�����û������
	enum EOS{SRK,PR};//����״̬�������͵�ö�����ͣ��ֱ���{the Soave�CRedlich�CKwong EOS (SRK)��the Peng�CRobinson EOS (PR)}

	/*!
	*
	**/
	struct PropertiesVariable
	{
		double m_NGroupCom; //������е������  =5
		std::vector<double> m_ComMolFra; //��������еĸ���ֵ�Ħ������
		std::vector<double> m_MWi;       //���Ħ������  kg/kgmol
		std::vector<double> m_Tci;
		std::vector<double> m_Pci; //����ٽ��¶Ⱥ�ѹ��   K��MPa
		std::vector<double> m_Omegai; //the dimensionless acentric factor,����ֵ�
		std::vector<double> m_Zci;
		std::vector<double> m_Vci;
		double m_MW;
		double m_Tc;
		double m_Pc;
		double m_Omega;
		double m_Zc;
		double m_Vc; //����ֵ��ܵ�����
		double m_PcMolAveraging; //����Ħ��ƽ��ֵ�õ���ֵ������û�в��ã�ֻ�Ǽ������ڱȽϷ���
		double m_z; //mole fraction of the group in the mixture    ��������ڻ�����е�Ħ������
		PropertiesVariable()
		{

		}
		PropertiesVariable(const PropertiesVariable &other)
		{
			*this = other;
		}
		const PropertiesVariable &operator=(const PropertiesVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_NGroupCom = other.m_NGroupCom;
			m_ComMolFra = other.m_ComMolFra;
			m_MWi = other.m_MWi;
			m_Tci = other.m_Tci;
			m_Pci = other.m_Pci;
			m_Omegai = other.m_Omegai;
			m_Zci = other.m_Zci;
			m_Vci = other.m_Vci;
			m_MW = other.m_MW;
			m_Tc = other.m_Tc;
			m_Pc = other.m_Pc;
			m_Omega = other.m_Omega;
			m_Zc = other.m_Zc;
			m_Vc = other.m_Vc;
			m_PcMolAveraging = other.m_PcMolAveraging;
			m_z = other.m_z;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_NGroupCom; 
			curSize += (sizeof(int) + m_ComMolFra.size() * sizeof(double));//std::vector<double> m_ComMolFra;
			curSize += (sizeof(int) + m_MWi.size() * sizeof(double));//std::vector<double> m_MWi; 
			curSize += (sizeof(int) + m_Tci.size() * sizeof(double));//std::vector<double> m_Tci;
			curSize += (sizeof(int) + m_Pci.size() * sizeof(double));//std::vector<double> m_Pci; 
			curSize += (sizeof(int) + m_Omegai.size() * sizeof(double));//std::vector<double> m_Omegai; 
			curSize += (sizeof(int) + m_Zci.size() * sizeof(double));//std::vector<double> m_Zci;
			curSize += (sizeof(int) + m_Vci.size() * sizeof(double));//std::vector<double> m_Vci;
			curSize += sizeof(double);//double m_MW;
			curSize += sizeof(double);//double m_Tc;
			curSize += sizeof(double);//double m_Pc;
			curSize += sizeof(double);//double m_Omega;
			curSize += sizeof(double);//double m_Zc;
			curSize += sizeof(double);//double m_Vc; 
			curSize += sizeof(double);//double m_PcMolAveraging;
			curSize += sizeof(double);//double m_z;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_NGroupCom), sizeof(double));data += sizeof(double);
			int ComMolFrasize = m_ComMolFra.size();
			memcpy(data, &ComMolFrasize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < ComMolFrasize; j++)
			{
				memcpy(data, &(m_ComMolFra[j]), sizeof(double));data += sizeof(double);
			}
			int MWisize = m_MWi.size();
			memcpy(data, &MWisize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < MWisize; j++)
			{
				memcpy(data, &(m_MWi[j]), sizeof(double));data += sizeof(double);
			}
			int Tcisize = m_Tci.size();
			memcpy(data, &Tcisize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < Tcisize; j++)
			{
				memcpy(data, &(m_Tci[j]), sizeof(double));data += sizeof(double);
			}
			int Pcisize = m_Pci.size();
			memcpy(data, &Pcisize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < Pcisize; j++)
			{
				memcpy(data, &(m_Pci[j]), sizeof(double));data += sizeof(double);
			}
			int Omegaisize = m_Omegai.size();
			memcpy(data, &Omegaisize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < Omegaisize; j++)
			{
				memcpy(data, &(m_Omegai[j]), sizeof(double));data += sizeof(double);
			}
			int Zcisize = m_Zci.size();
			memcpy(data, &Zcisize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < Zcisize; j++)
			{
				memcpy(data, &(m_Zci[j]), sizeof(double));data += sizeof(double);
			}
			int Vcisize = m_Vci.size();
			memcpy(data, &Vcisize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < Vcisize; j++)
			{
				memcpy(data, &(m_Vci[j]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &(m_MW), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_Tc), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_Pc), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_Omega), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_Zc), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_Vc), sizeof(double));data += sizeof(double); 
			memcpy(data, &(m_PcMolAveraging), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_z), sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_NGroupCom), data, sizeof(double));data += sizeof(double);
			int ComMolFrasize;
			memcpy(&ComMolFrasize, data, sizeof(int));data += sizeof(int);
			m_ComMolFra.resize(ComMolFrasize);
			for(int j = 0; j < ComMolFrasize; j++)
			{
				memcpy(&(m_ComMolFra[j]), data, sizeof(double));data += sizeof(double);
			}
			int MWisize;
			memcpy(&MWisize, data, sizeof(int));data += sizeof(int);
			m_MWi.resize(MWisize);
			for(int j = 0; j < MWisize; j++)
			{
				memcpy(&(m_MWi[j]), data, sizeof(double));data += sizeof(double);
			}
			int Tcisize;
			memcpy(&Tcisize, data, sizeof(int));data += sizeof(int);
			m_Tci.resize(Tcisize);
			for(int j = 0; j < Tcisize; j++)
			{
				memcpy(&(m_Tci[j]), data, sizeof(double));data += sizeof(double);
			}
			int Pcisize;
			memcpy(&Pcisize, data, sizeof(int));data += sizeof(int);
			m_Pci.resize(Pcisize);
			for(int j = 0; j < Pcisize; j++)
			{
				memcpy(&(m_Pci[j]), data, sizeof(double));data += sizeof(double);
			}
			int Omegaisize;
			memcpy(&Omegaisize, data, sizeof(int));data += sizeof(int);
			m_Omegai.resize(Omegaisize);
			for(int j = 0; j < Omegaisize; j++)
			{
				memcpy(&(m_Omegai[j]), data, sizeof(double));data += sizeof(double);
			}
			int Zcisize;
			memcpy(&Zcisize, data, sizeof(int));data += sizeof(int);
			m_Zci.resize(Zcisize);
			for(int j = 0; j < Zcisize; j++)
			{
				memcpy(&(m_Zci[j]), data, sizeof(double));data += sizeof(double);
			}
			int Vcisize;
			memcpy(&Vcisize, data, sizeof(int));data += sizeof(int);
			m_Vci.resize(Vcisize);
			for(int j = 0; j < Vcisize; j++)
			{
				memcpy(&(m_Vci[j]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&(m_MW), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_Tc), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_Pc), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_Omega), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_Zc), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_Vc), data, sizeof(double));data += sizeof(double); 
			memcpy(&(m_PcMolAveraging), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_z), data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, PropertiesVariable &properties)
		{
			os << "\r\n>>>>>>>>>>>>>>>PropertiesVariable parameter as flow:";
			os << "\r\n---- ---- ---- NGroupCom:" << properties.m_NGroupCom;
			for(int i = 0; i < properties.m_ComMolFra.size(); i++)
			{
				os << "\r\n---- ---- ---- m_ComMolFra:" << i << ":" << properties.m_ComMolFra[i];
			}
			for(int i = 0; i < properties.m_MWi.size(); i++)
			{
				os << "\r\n---- ---- ---- m_MWi:" << i << ":" << properties.m_MWi[i];
			}
			for(int i = 0; i < properties.m_Tci.size(); i++)
			{
				os << "\r\n---- ---- ---- m_Tci:" << i << ":" << properties.m_Tci[i];
			}
			for(int i = 0; i < properties.m_Pci.size(); i++)
			{
				os << "\r\n---- ---- ---- m_Pci:" << i << ":" << properties.m_Pci[i];
			}
			for(int i = 0; i < properties.m_Omegai.size(); i++)
			{
				os << "\r\n---- ---- ---- m_Omegai:" << i << ":" << properties.m_Omegai[i];
			}
			for(int i = 0; i < properties.m_Zci.size(); i++)
			{
				os << "\r\n---- ---- ---- m_Zci:" << i << ":" << properties.m_Zci[i];
			}
			for(int i = 0; i < properties.m_Vci.size(); i++)
			{
				os << "\r\n---- ---- ---- m_Vci:" << i << ":" << properties.m_Vci[i];
			}
			os << "\r\n---- ---- ---- MW:" << properties.m_MW;
			os << "\r\n---- ---- ---- Tc:" << properties.m_Tc;
			os << "\r\n---- ---- ---- Pc:" << properties.m_Pc;
			os << "\r\n---- ---- ---- Omega:" << properties.m_Omega;
			os << "\r\n---- ---- ---- Zc:" << properties.m_Zc;
			os << "\r\n---- ---- ---- Vc:" << properties.m_Vc;
			os << "\r\n---- ---- ---- PcMolAveraging:" << properties.m_PcMolAveraging;
			os << "\r\n---- ---- ---- z:" << properties.m_z;
			return os;
		}
		void ReadinPars(int aNGroupCom, std::vector<double>&aComMolFra,std::vector<double>&aMWi,std::vector<double>&aTci,std::vector<double>&aPci,std::vector<double>&aOmegai,std::vector<double>&aZci,std::vector<double>&aVci)// ,double **akij
		{
			double R=0.008314; //���峣��
			m_NGroupCom=aNGroupCom;
			m_ComMolFra.resize(m_NGroupCom);
			m_MWi.resize(m_NGroupCom);
			m_Tci.resize(m_NGroupCom);
			m_Pci.resize(m_NGroupCom);
			m_Omegai.resize(m_NGroupCom);
			m_Zci.resize(m_NGroupCom);
			m_Vci.resize(m_NGroupCom);
			// kij.resize(NGroupCom);
			// for(int i=0;i<NGroupCom;i++) kij[i].resize(NGroupCom);
			m_z=0;
			for(int i=0;i<m_NGroupCom;i++)
			{m_ComMolFra[i]=aComMolFra[i];m_z+=m_ComMolFra[i]; m_MWi[i]=aMWi[i];m_Tci[i]=aTci[i];m_Pci[i]=aPci[i]; m_Omegai[i]=aOmegai[i];m_Zci[i]=aZci[i];m_Vci[i]=aVci[i];} // for(int j=0;j<NGroupCom;j++)kij[i][j]=akij[i][j];
			for(int i=0;i<m_NGroupCom;i++) m_ComMolFra[i]=m_ComMolFra[i]/m_z;
			m_MW=0;m_Tc=0;m_PcMolAveraging=0;/*m_Pc=0;*/m_Omega=0;m_Zc=0;m_Vc=0;
			for(int i=0;i<m_NGroupCom;i++)   //molar averaging ,�������PC
			{ m_MW+=m_MWi[i]*m_ComMolFra[i];m_Tc+=m_Tci[i]*m_ComMolFra[i]; m_Pc+=m_Pci[i]*m_ComMolFra[i]; m_Omega+=m_Omegai[i]*m_ComMolFra[i];m_Zc+=m_Zci[i]*m_ComMolFra[i];m_Vc+=m_Vci[i]*m_ComMolFra[i];}
			// Pc=Zc*R*Tc/Vc; //����poling  2000 The properties of gases and liquids ��(5-3.2)    ����Pc���ǲ�����Ħ��ƽ��
		}
	};
	struct SolutionOfCE
	{
		double m_x1;
		double m_x2;
		double m_x3;
		int m_Case;
		SolutionOfCE()
		{

		}
		SolutionOfCE(const SolutionOfCE &other)
		{
			*this = other;
		}
		const SolutionOfCE &operator=(const SolutionOfCE &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_x1 = other.m_x1;
			m_x2 = other.m_x2;
			m_x3 = other.m_x3;
			m_Case = other.m_Case;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_x1;
			curSize += sizeof(double);//double m_x2;
			curSize += sizeof(double);//double m_x3;
			curSize += sizeof(int);//int m_Case;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &(m_x1), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_x2), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_x3), sizeof(double));data += sizeof(double);
			memcpy(data, &(m_Case), sizeof(int));data += sizeof(int);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&(m_x1), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_x2), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_x3), data, sizeof(double));data += sizeof(double);
			memcpy(&(m_Case), data, sizeof(int));data += sizeof(int);
		}
		friend std::ofstream &operator << (std::ofstream &os, SolutionOfCE &solutionofce)
		{
			os << "\r\n>>>>>>>>>>>>>>>SolutionOfCE parameter as flow:";
			os << "\r\n---- ---- ---- m_x1:" << solutionofce.m_x1; 
			os << "\r\n---- ---- ---- m_x2:" << solutionofce.m_x2; 
			os << "\r\n---- ---- ---- m_x3:" << solutionofce.m_x3;  
			os << "\r\n---- ---- ---- m_Case:" << solutionofce.m_Case;
			return os;  
		}
	};


	/*!
	*flash Calculation Start ,��̬�������
	**/
	struct FlashCalculationVariable
	{
		bool m_flashcalculated;
		double m_Sgg; //��������ܶ�   ��Good Oil: Sgg= 0.855
		double m_Soo;//�͵�����ܶ�     ; Good Oil:  Soo=0.823
		double m_T_F; //�����¶�
		double m_MolFraC1InWater; //molar fraction of methane in water
		double m_nl;
		double m_nv; //�ֱ���Һ̬����̬��Ħ������
		int m_NCom; //��N����ֵ�����
		std::vector<PropertiesVariable> m_aProperties;
		std::vector<double> m_flash_x;
		std::vector<double> m_flash_y;
		std::vector<double> m_flash_z;  //�ֱ�Ϊ��Һ���е����Ħ������/�������������е����Ħ������/�������ܵ����Ħ������
		std::vector<double> m_K; // The equality of fugacity can be expressed by the equilibrium ratio, K,  K[i] = y[i] / x[i]
		std::vector<double> m_MW;       //���Ħ������  kg/kgmol
		std::vector<double> m_Tci;
		std::vector<double> m_Pci;
		std::vector<double> m_vci; //����ٽ��¶ȡ�ѹ�������   K��MPa��m^3/kmol
		std::vector<double> m_Omegai; //the dimensionless acentric factor,����ֵ�
		std::vector<std::vector<double> > m_kij; //binary interaction parameter ��Ԫ�໥���ò���
		double m_R;//���峣�� ��=0.008314;0.008314 KJ/(mol*K)
		int m_aHCType;
		double m_SCT; //��׼�����µ��¶�15.556���϶�
		double m_SCTK; // ��׼�����µ��¶ȿ����¶�
		double m_SCP; //��׼�����µ�ѹ��1 atm 0.1MPa
		double m_pb; //��ϵ���ݵ�ѹ�� ��MPa
		double m_TmK; //�в��¶ȣ��ÿ����¶ȱ�ʾ��������̬����
		double m_PmMPa; //�в�ѹ������������ʾ��������̬����
		double m_pTc; //׼�ٽ��¶� K   pseudo critical temperature  ,������ֵΪ��ϵ�¶�
		double m_pPc; //׼�ٽ�ѹ�� MPa
		double m_a;
		double m_b; //�ֱ��Ӧ���ٽ���̬��aֵ��bֵ
		double m_vL;
		double m_vV;  //�ֱ����ͺ�����Ħ�����  m3/kgmol
		double m_MWL;
		double m_MWV; //�ֱ�������������Ħ������
		std::vector<double> m_aci;
		std::vector<double> m_bi;
		std::vector<double> m_mi;
		std::vector<double> m_Alphai;
		std::vector<double> m_ai;
		std::vector<double> m_Ai;
		std::vector<double> m_Bi; //
		double m_aL;
		double m_bL;
		double m_aV;
		double m_bV; //�ֱ��Ӧ���ͺ�����aֵ��bֵ
		int m_aEOS;
		double m_AL;
		double m_AV;
		double m_BL;
		double m_BV; // �ֱ��Ӧ���ͺ���
		double m_ZL;
		double m_ZV; //Һ������壬���ͺ�����ѹ��ϵ��
		std::vector<double> m_FaiiL;
		std::vector<double> m_FaiiV; //�ֱ�Ϊ�͡�����̬����ֵ��ݶ�ϵ����fugacity coefficients��
		std::vector<double> m_fiL;
		std::vector<double> m_fiV; //�ֱ�Ϊ�͡�����̬����ֵ��ݶȣ�fugacities��
		double m_OilDensitySC; //��׼������ԭ�͵��ܶ�
		double m_API; //��׼�������͵��ض�
		double m_GOR;//���ͱ�  m3/m3
		double m_Bo; //ԭ�����ϵ��������Ϊ����ԭ����������ԭ�����֮��
		std::vector<double> m_KSC;
		double m_nvSC;
		double m_nlSC;    //��׼����������������Ħ����
		std::vector<double> m_xSC;
		std::vector<double> m_ySC;
		double m_MWLSC;
		double m_vLSC;
		double m_MWVSC;
		double m_vVSC;
		double m_GasDensitySC; // ��׼�����������ܶ� 
		FlashCalculationVariable()
		{
			m_flashcalculated = false;
			int aEOS;
			aEOS=PR;
			int NCom=2; //��N����ֵ�����
			// ������ְ����������Methane��Ethane��Propane��n-Butane��n-Pentane
			int GasNGroupCom=5;
			std::vector<double> GasComMolFra, GasMWi, GasTci, GasPci, GasOmegai;
			std::vector<double> GasZci,GasVci;//
			GasComMolFra.resize(GasNGroupCom); GasComMolFra[0]=47; GasComMolFra[1]=6; GasComMolFra[2]=4; GasComMolFra[3]=3; GasComMolFra[4]=2;
			GasMWi.resize(GasNGroupCom);   GasMWi[0]=16.043; GasMWi[1]=30.070; GasMWi[2]=44.096; GasMWi[3]=58.123; GasMWi[4]=72.150;
			GasTci.resize(GasNGroupCom);   GasTci[0]=190.56; GasTci[1]=305.32; GasTci[2]=369.83; GasTci[3]=425.12; GasTci[4]=469.7;
			GasPci.resize(GasNGroupCom);   GasPci[0]=4.599; GasPci[1]=4.872; GasPci[2]=4.248; GasPci[3]=3.796; GasPci[4]=3.370;
			GasOmegai.resize(GasNGroupCom);GasOmegai[0]=0.0115; GasOmegai[1]=0.0995; GasOmegai[2]=0.1523; GasOmegai[3]=0.2002; GasOmegai[4]=0.2515;
			GasZci.resize(GasNGroupCom);   GasZci[0]=0.2862; GasZci[1]=0.2793; GasZci[2]=0.2763; GasZci[3]=0.2739; GasZci[4]=0.2701;
			GasVci.resize(GasNGroupCom);   GasVci[0]=0.0986; GasVci[1]=0.1455; GasVci[2]=0.2; GasVci[3]=0.255; GasVci[4]=0.313;
			// ������ְ����������C6-14��C15��C25��C35��C45        C6-C14��C10������
			int OilNGroupCom=5;
			std::vector<double>OilComMolFra, OilMWi, OilTci, OilPci, OilOmegai;
			std::vector<double>OilZci,OilVci;//
			OilComMolFra.resize(OilNGroupCom);OilComMolFra[0]=10; OilComMolFra[1]=9; OilComMolFra[2]=8; OilComMolFra[3]=6; OilComMolFra[4]=5;
			OilMWi.resize(OilNGroupCom);   OilMWi[0]=134; OilMWi[1]=206; OilMWi[2]=337; OilMWi[3]=445; OilMWi[4]=539;
			OilTci.resize(OilNGroupCom);   OilTci[0]=627; OilTci[1]=727; OilTci[2]=844; OilTci[3]=920; OilTci[4]=974;
			OilPci.resize(OilNGroupCom);   OilPci[0]=2.481; OilPci[1]=1.853; OilPci[2]=1.263; OilPci[3]=0.998; OilPci[4]=0.835;
			OilOmegai.resize(OilNGroupCom);OilOmegai[0]=0.389; OilOmegai[1]=0.571; OilOmegai[2]=0.874; OilOmegai[3]=1.095; OilOmegai[4]=1.232;
			OilZci.resize(OilNGroupCom);   OilZci[0]=0.2465; OilZci[1]=0.2235; OilZci[2]=0.215; OilZci[3]=0.196; OilZci[4]=0.18;
			OilVci.resize(OilNGroupCom);   OilVci[0]=0.6; OilVci[1]=0.889; OilVci[2]=1.193; OilVci[3]=1.502; OilVci[4]=1.749;
			double tempSum1=0; for(int i=0;i<GasNGroupCom;i++) tempSum1+=GasComMolFra[i];
			double tempSum2=0; for(int i=0;i<OilNGroupCom;i++) tempSum2+=OilComMolFra[i];
			for(int i=0;i<GasNGroupCom;i++)  GasComMolFra[i]/=(tempSum1+tempSum2);    //ת��ΪС����ʽ������ԭ���ǰٷֱ���ʽ����С����ʽ
			for(int i=0;i<OilNGroupCom;i++)  OilComMolFra[i]/=(tempSum1+tempSum2);    //ת��ΪС����ʽ������ԭ���ǰٷֱ���ʽ����С����ʽ
			std::vector<std::vector<double> >GasOilkij; //�������е���ּ�Ķ�Ԫ�໥����ϵ��
			GasOilkij.resize(GasNGroupCom);for(int i=0;i<GasNGroupCom;i++) GasOilkij[i].resize(OilNGroupCom);
			switch(aEOS)
			{
			case SRK:
				GasOilkij[0][0]=0.055; GasOilkij[0][1]=0.06; GasOilkij[0][2]=0; GasOilkij[0][3]=0; GasOilkij[0][4]=0;
				GasOilkij[1][0]=0.02; GasOilkij[1][1]=0.035; GasOilkij[1][2]=0; GasOilkij[1][3]=0; GasOilkij[1][4]=0;
				GasOilkij[2][0]=0.004; GasOilkij[2][1]=0.0005; GasOilkij[2][2]=0; GasOilkij[2][3]=0; GasOilkij[2][4]=0;
				GasOilkij[3][0]=0.001; GasOilkij[3][1]=0.001; GasOilkij[3][2]=0; GasOilkij[3][3]=0; GasOilkij[3][4]=0;
				GasOilkij[4][0]=0; GasOilkij[4][1]=0; GasOilkij[4][2]=0; GasOilkij[4][3]=0; GasOilkij[4][4]=0;
				break;
			case PR:
				GasOilkij[0][0]=0.05; GasOilkij[0][1]=0.06; GasOilkij[0][2]=0; GasOilkij[0][3]=0; GasOilkij[0][4]=0;
				GasOilkij[1][0]=0.03; GasOilkij[1][1]=0.04; GasOilkij[1][2]=0; GasOilkij[1][3]=0; GasOilkij[1][4]=0;
				GasOilkij[2][0]=0.02; GasOilkij[2][1]=0.025; GasOilkij[2][2]=0; GasOilkij[2][3]=0; GasOilkij[2][4]=0;
				GasOilkij[3][0]=0.001; GasOilkij[3][1]=0.001; GasOilkij[3][2]=0; GasOilkij[3][3]=0; GasOilkij[3][4]=0;
				GasOilkij[4][0]=0; GasOilkij[4][1]=0; GasOilkij[4][2]=0; GasOilkij[4][3]=0; GasOilkij[4][4]=0;
				break;
			};
			m_aProperties.resize(NCom);
			m_aProperties[0].ReadinPars(GasNGroupCom, GasComMolFra,GasMWi,GasTci,GasPci,GasOmegai,GasZci,GasVci);  // ,Gaskij
			m_aProperties[1].ReadinPars(OilNGroupCom, OilComMolFra,OilMWi,OilTci,OilPci,OilOmegai,OilZci,OilVci); // ,Oilkij
			m_kij.resize(NCom);  for(int i=0;i<NCom;i++) m_kij[i].resize(NCom);
			GetGroupkij(NCom,m_kij,GasOilkij,m_aProperties); //�������֣��������ͣ���Ķ�Ԫ�໥����ϵ��
			GetProperties(NCom,m_aProperties,m_kij,aEOS);
			GetBehar4CProperties();
		}
		FlashCalculationVariable(const FlashCalculationVariable &other)
		{
			*this = other;
		}
		const FlashCalculationVariable &operator=(const FlashCalculationVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_flashcalculated = other.m_flashcalculated;
			m_Sgg = other.m_Sgg; //��������ܶ�   ��Good Oil: Sgg= 0.855
			m_Soo = other.m_Soo;//�͵�����ܶ�     ; Good Oil:  Soo=0.823
			m_T_F = other.m_T_F; //�����¶�
			m_MolFraC1InWater = other.m_MolFraC1InWater; //molar fraction of methane in water
			m_nl = other.m_nl;
			m_nv = other.m_nv; //�ֱ���Һ̬����̬��Ħ������
			m_NCom = other.m_NCom; //��N����ֵ�����
			m_aProperties = other.m_aProperties;
			m_flash_x = other.m_flash_x;
			m_flash_y = other.m_flash_y;
			m_flash_z = other.m_flash_z;  //�ֱ�Ϊ��Һ���е����Ħ������/�������������е����Ħ������/�������ܵ����Ħ������
			m_K = other.m_K; // The equality of fugacity can be expressed by the equilibrium ratio, K,  K[i] = y[i] / x[i]
			m_MW = other.m_MW;       //���Ħ������  kg/kgmol
			m_Tci = other.m_Tci;
			m_Pci = other.m_Pci;
			m_vci = other.m_vci; //����ٽ��¶ȡ�ѹ�������   K��MPa��m^3/kmol
			m_Omegai = other.m_Omegai; //the dimensionless acentric factor,����ֵ�
			m_kij = other.m_kij; //binary interaction parameter ��Ԫ�໥���ò���
			m_R = other.m_R;//���峣�� ��=0.008314;0.008314 KJ/(mol*K)
			m_aHCType = other.m_aHCType;
			m_SCT = other.m_SCT; //��׼�����µ��¶�15.556���϶�
			m_SCTK = other.m_SCTK; // ��׼�����µ��¶ȿ����¶�
			m_SCP = other.m_SCP; //��׼�����µ�ѹ��1 atm 0.1MPa
			m_pb = other.m_pb; //��ϵ���ݵ�ѹ�� ��MPa
			m_TmK = other.m_TmK; //�в��¶ȣ��ÿ����¶ȱ�ʾ��������̬����
			m_PmMPa = other.m_PmMPa; //�в�ѹ������������ʾ��������̬����
			m_pTc = other.m_pTc; //׼�ٽ��¶� K   pseudo critical temperature  ,������ֵΪ��ϵ�¶�
			m_pPc = other.m_pPc; //׼�ٽ�ѹ�� MPa
			m_a = other.m_a;
			m_b = other.m_b; //�ֱ��Ӧ���ٽ���̬��aֵ��bֵ
			m_vL = other.m_vL;
			m_vV = other.m_vV;  //�ֱ����ͺ�����Ħ�����  m3/kgmol
			m_MWL = other.m_MWL;
			m_MWV = other.m_MWV; //�ֱ�������������Ħ������
			m_aci = other.m_aci;
			m_bi = other.m_bi;
			m_mi = other.m_mi;
			m_Alphai = other.m_Alphai;
			m_ai = other.m_ai;
			m_Ai = other.m_Ai;
			m_Bi = other.m_Bi; //
			m_aL = other.m_aL;
			m_bL = other.m_bL;
			m_aV = other.m_aV;
			m_bV = other.m_bV; //�ֱ��Ӧ���ͺ�����aֵ��bֵ
			m_aEOS = other.m_aEOS;
			m_AL = other.m_AL;
			m_AV = other.m_AV;
			m_BL = other.m_BL;
			m_BV = other.m_BV; // �ֱ��Ӧ���ͺ���
			m_ZL = other.m_ZL;
			m_ZV = other.m_ZV; //Һ������壬���ͺ�����ѹ��ϵ��
			m_FaiiL = other.m_FaiiL;
			m_FaiiV = other.m_FaiiV; //�ֱ�Ϊ�͡�����̬����ֵ��ݶ�ϵ����fugacity coefficients��
			m_fiL = other.m_fiL;
			m_fiV = other.m_fiV; //�ֱ�Ϊ�͡�����̬����ֵ��ݶȣ�fugacities��
			m_OilDensitySC = other.m_OilDensitySC; //��׼������ԭ�͵��ܶ�
			m_API = other.m_API; //��׼�������͵��ض�
			m_GOR = other.m_GOR;//���ͱ�  m3/m3
			m_Bo = other.m_Bo; //ԭ�����ϵ��������Ϊ����ԭ����������ԭ�����֮��
			m_KSC = other.m_KSC;
			m_nvSC = other.m_nvSC;
			m_nlSC = other.m_nlSC;    //��׼����������������Ħ����
			m_xSC = other.m_xSC;
			m_ySC = other.m_ySC;
			m_MWLSC = other.m_MWLSC;
			m_vLSC = other.m_vLSC;
			m_MWVSC = other.m_MWVSC;
			m_vVSC = other.m_vVSC;
			m_GasDensitySC = other.m_GasDensitySC; // ��׼�����������ܶ� 
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(bool);//bool m_flashcalculated;
			curSize += sizeof(double);//double m_Sgg;
			curSize += sizeof(double);//double m_Soo;
			curSize += sizeof(double);//double m_T_F;
			curSize += sizeof(double);//double m_MolFraC1InWater;
			curSize += sizeof(double);//double m_nl;
			curSize += sizeof(double);//double m_nv;
			curSize += sizeof(int);//int m_NCom;
			curSize += sizeof(int);//std::vector<PropertiesVariable> m_aProperties;
			for(int i = 0; i < m_aProperties.size(); i++)
			{
				curSize += m_aProperties[i].GetSerializeDataLength();
			}
			curSize += (sizeof(int) + m_flash_x.size() * sizeof(double));//std::vector<double> m_flash_x;
			curSize += (sizeof(int) + m_flash_y.size() * sizeof(double));//std::vector<double> m_flash_y;
			curSize += (sizeof(int) + m_flash_z.size() * sizeof(double));//std::vector<double> m_flash_z;
			curSize += (sizeof(int) + m_K.size() * sizeof(double));//std::vector<double> m_K;
			curSize += (sizeof(int) + m_MW.size() * sizeof(double));//std::vector<double> m_MW;
			curSize += (sizeof(int) + m_Tci.size() * sizeof(double));//std::vector<double> m_Tci;
			curSize += (sizeof(int) + m_Pci.size() * sizeof(double));//std::vector<double> m_Pci;
			curSize += (sizeof(int) + m_vci.size() * sizeof(double));//std::vector<double> m_vci;
			curSize += (sizeof(int) + m_Omegai.size() * sizeof(double));//std::vector<double> m_Omegai; 
			curSize += sizeof(int);//std::vector<std::vector<double> > m_kij;
			for(int i = 0; i < m_kij.size(); i++)
			{
				curSize += (sizeof(int) + m_kij[i].size() * sizeof(double));
			}
			curSize += sizeof(double);//double m_R;
			curSize += sizeof(int);//int m_aHCType;
			curSize += sizeof(double);//double m_SCT;
			curSize += sizeof(double);//double m_SCTK; 
			curSize += sizeof(double);//double m_SCP;
			curSize += sizeof(double);//double m_pb;
			curSize += sizeof(double);//double m_TmK;
			curSize += sizeof(double);//double m_PmMPa;
			curSize += sizeof(double);//double m_pTc;
			curSize += sizeof(double);//double m_pPc;
			curSize += sizeof(double);//double m_a;
			curSize += sizeof(double);//double m_b;
			curSize += sizeof(double);//double m_vL;
			curSize += sizeof(double);//double m_vV; 
			curSize += sizeof(double);//double m_MWL;
			curSize += sizeof(double);//double m_MWV; 
			curSize += (sizeof(int) + m_aci.size() * sizeof(double));//std::vector<double> m_aci;
			curSize += (sizeof(int) + m_bi.size() * sizeof(double));//std::vector<double> m_bi;
			curSize += (sizeof(int) + m_mi.size() * sizeof(double));//std::vector<double> m_mi;
			curSize += (sizeof(int) + m_Alphai.size() * sizeof(double));//std::vector<double> m_Alphai;
			curSize += (sizeof(int) + m_ai.size() * sizeof(double));//std::vector<double> m_ai;
			curSize += (sizeof(int) + m_Ai.size() * sizeof(double));//std::vector<double> m_Ai;
			curSize += (sizeof(int) + m_Bi.size() * sizeof(double));//std::vector<double> m_Bi;
			curSize += sizeof(double);//double m_aL;
			curSize += sizeof(double);//double m_bL;
			curSize += sizeof(double);//double m_aV;
			curSize += sizeof(double);//double m_bV; 
			curSize += sizeof(int);//int m_aEOS;
			curSize += sizeof(double);//double m_AL;
			curSize += sizeof(double);//double m_AV;
			curSize += sizeof(double);//double m_BL;
			curSize += sizeof(double);//double m_BV; 
			curSize += sizeof(double);//double m_ZL;
			curSize += sizeof(double);//double m_ZV; 
			curSize += (sizeof(int) + m_FaiiL.size() * sizeof(double));//std::vector<double> m_FaiiL;
			curSize += (sizeof(int) + m_FaiiV.size() * sizeof(double));//std::vector<double> m_FaiiV; 
			curSize += (sizeof(int) + m_fiL.size() * sizeof(double));//std::vector<double> m_fiL;
			curSize += (sizeof(int) + m_fiV.size() * sizeof(double));//std::vector<double> m_fiV; 
			curSize += sizeof(double);//double m_OilDensitySC;
			curSize += sizeof(double);//double m_API; 
			curSize += sizeof(double);//double m_GOR;
			curSize += sizeof(double);//double m_Bo;
			curSize += (sizeof(int) + m_KSC.size() * sizeof(double));//std::vector<double> m_KSC;
			curSize += sizeof(double);//double m_nvSC;
			curSize += sizeof(double);//double m_nlSC;    
			curSize += (sizeof(int) + m_xSC.size() * sizeof(double));//std::vector<double> m_xSC;
			curSize += (sizeof(int) + m_ySC.size() * sizeof(double));//std::vector<double> m_ySC;
			curSize += sizeof(double);//double m_MWLSC;
			curSize += sizeof(double);//double m_vLSC;
			curSize += sizeof(double);//double m_MWVSC;
			curSize += sizeof(double);//double m_vVSC;
			curSize += sizeof(double);//double m_GasDensitySC;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_flashcalculated, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_Sgg, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Soo, sizeof(double));data += sizeof(double);
			memcpy(data, &m_T_F, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MolFraC1InWater, sizeof(double));data += sizeof(double);
			memcpy(data, &m_nl, sizeof(double));data += sizeof(double);
			memcpy(data, &m_nv, sizeof(double));data += sizeof(double);
			memcpy(data, &m_NCom, sizeof(int));data += sizeof(int);
			int aPropertiessize = m_aProperties.size();
			memcpy(data, &aPropertiessize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < aPropertiessize; i++)
			{
				m_aProperties[i].SerializeData(data);
			}
			int xsize = m_flash_x.size();
			memcpy(data, &xsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < xsize; i++)
			{
				memcpy(data, &(m_flash_x[i]), sizeof(double));data += sizeof(double);
			}
			int ysize = m_flash_y.size();
			memcpy(data, &ysize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < ysize; i++)
			{
				memcpy(data, &(m_flash_y[i]), sizeof(double));data += sizeof(double);
			}
			int zsize = m_flash_z.size();
			memcpy(data, &zsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < zsize; i++)
			{
				memcpy(data, &(m_flash_z[i]), sizeof(double));data += sizeof(double);
			}
			int Ksize = m_K.size();
			memcpy(data, &Ksize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < Ksize; i++)
			{
				memcpy(data, &(m_K[i]), sizeof(double));data += sizeof(double);
			}
			int MWsize = m_MW.size();
			memcpy(data, &MWsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < MWsize; i++)
			{
				memcpy(data, &(m_MW[i]), sizeof(double));data += sizeof(double);
			}
			int Tcisize = m_Tci.size();
			memcpy(data, &Tcisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < Tcisize; i++)
			{
				memcpy(data, &(m_Tci[i]), sizeof(double));data += sizeof(double);
			}
			int Pcisize = m_Pci.size();
			memcpy(data, &Pcisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < Pcisize; i++)
			{
				memcpy(data, &(m_Pci[i]), sizeof(double));data += sizeof(double);
			}
			int vcisize = m_vci.size();
			memcpy(data, &vcisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < vcisize; i++)
			{
				memcpy(data, &(m_vci[i]), sizeof(double));data += sizeof(double);
			}
			int Omegaisize = m_Omegai.size();
			memcpy(data, &Omegaisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < Omegaisize; i++)
			{
				memcpy(data, &(m_Omegai[i]), sizeof(double));data += sizeof(double);
			}
			int kijsize = m_kij.size();
			memcpy(data, &kijsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < kijsize; i++)
			{
				int kijisize = m_kij[i].size();
				memcpy(data, &kijisize, sizeof(int));data += sizeof(int);
				for(int j = 0; j < kijisize; j++)
				{
					memcpy(data, &(m_kij[i][j]), sizeof(double));data += sizeof(double);
				}
			}
			memcpy(data, &m_R, sizeof(double));data += sizeof(double);
			memcpy(data, &m_aHCType, sizeof(int));data += sizeof(int);
			memcpy(data, &m_SCT, sizeof(double));data += sizeof(double);
			memcpy(data, &m_SCTK, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_SCP, sizeof(double));data += sizeof(double);
			memcpy(data, &m_pb, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TmK, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PmMPa, sizeof(double));data += sizeof(double);
			memcpy(data, &m_pTc, sizeof(double));data += sizeof(double);
			memcpy(data, &m_pPc, sizeof(double));data += sizeof(double);
			memcpy(data, &m_a, sizeof(double));data += sizeof(double);
			memcpy(data, &m_b, sizeof(double));data += sizeof(double);
			memcpy(data, &m_vL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_vV, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_MWL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MWV, sizeof(double));data += sizeof(double); 
			int acisize = m_aci.size();
			memcpy(data, &acisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < acisize; i++)
			{
				memcpy(data, &(m_aci[i]), sizeof(double));data += sizeof(double);
			}
			int bisize = m_bi.size();
			memcpy(data, &bisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < bisize; i++)
			{
				memcpy(data, &(m_bi[i]), sizeof(double));data += sizeof(double);
			}
			int misize = m_mi.size();
			memcpy(data, &misize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < misize; i++)
			{
				memcpy(data, &(m_mi[i]), sizeof(double));data += sizeof(double);
			}
			int Alphaisize = m_Alphai.size();
			memcpy(data, &Alphaisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < Alphaisize; i++)
			{
				memcpy(data, &(m_Alphai[i]), sizeof(double));data += sizeof(double);
			}
			int aisize = m_ai.size();
			memcpy(data, &aisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < aisize; i++)
			{
				memcpy(data, &(m_ai[i]), sizeof(double));data += sizeof(double);
			}
			int Aisize = m_Ai.size();
			memcpy(data, &Aisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < Aisize; i++)
			{
				memcpy(data, &(m_Ai[i]), sizeof(double));data += sizeof(double);
			}
			int Bisize = m_Bi.size();
			memcpy(data, &Bisize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < Bisize; i++)
			{
				memcpy(data, &(m_Bi[i]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &m_aL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_bL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_aV, sizeof(double));data += sizeof(double);
			memcpy(data, &m_bV, sizeof(double));data += sizeof(double);
			memcpy(data, &m_aEOS, sizeof(int));data += sizeof(int);
			memcpy(data, &m_AL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_AV, sizeof(double));data += sizeof(double);
			memcpy(data, &m_BL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_BV, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_ZL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ZV, sizeof(double));data += sizeof(double); 
			int FaiiLsize = m_FaiiL.size();
			memcpy(data, &FaiiLsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < FaiiLsize; i++)
			{
				memcpy(data, &(m_FaiiL[i]), sizeof(double));data += sizeof(double);
			}
			int FaiiVsize = m_FaiiV.size();
			memcpy(data, &FaiiVsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < FaiiVsize; i++)
			{
				memcpy(data, &(m_FaiiV[i]), sizeof(double));data += sizeof(double);
			}
			int fiLsize = m_fiL.size();
			memcpy(data, &fiLsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fiLsize; i++)
			{
				memcpy(data, &(m_fiL[i]), sizeof(double));data += sizeof(double);
			}
			int fiVsize = m_fiV.size();
			memcpy(data, &fiVsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < fiVsize; i++)
			{
				memcpy(data, &(m_fiV[i]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &m_OilDensitySC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_API, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GOR, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Bo, sizeof(double));data += sizeof(double);
			int KSCsize = m_KSC.size();
			memcpy(data, &KSCsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < KSCsize; i++)
			{
				memcpy(data, &(m_KSC[i]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &m_nvSC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_nlSC, sizeof(double));data += sizeof(double);  
			int xSCsize = m_xSC.size();
			memcpy(data, &xSCsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < xSCsize; i++)
			{
				memcpy(data, &(m_xSC[i]), sizeof(double));data += sizeof(double);
			}
			int ySCsize = m_ySC.size();
			memcpy(data, &ySCsize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < ySCsize; i++)
			{
				memcpy(data, &(m_ySC[i]), sizeof(double));data += sizeof(double);
			}
			memcpy(data, &m_MWLSC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_vLSC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MWVSC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_vVSC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GasDensitySC, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_flashcalculated, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_Sgg, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Soo, data, sizeof(double));data += sizeof(double);
			memcpy(&m_T_F, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MolFraC1InWater, data, sizeof(double));data += sizeof(double);
			memcpy(&m_nl, data, sizeof(double));data += sizeof(double);
			memcpy(&m_nv, data, sizeof(double));data += sizeof(double);
			memcpy(&m_NCom, data, sizeof(int));data += sizeof(int);
			int aPropertiessize;
			memcpy(&aPropertiessize, data, sizeof(int));data += sizeof(int);
			m_aProperties.resize(aPropertiessize);
			for(int i = 0; i < aPropertiessize; i++)
			{
				m_aProperties[i].RestoreSerializeData(data);
			}
			int xsize;
			memcpy(&xsize, data, sizeof(int));data += sizeof(int);
			m_flash_x.resize(xsize);
			for(int i = 0; i < xsize; i++)
			{
				memcpy(&(m_flash_x[i]), data, sizeof(double));data += sizeof(double);
			}
			int ysize;
			memcpy(&ysize, data, sizeof(int));data += sizeof(int);
			m_flash_y.resize(ysize);
			for(int i = 0; i < ysize; i++)
			{
				memcpy(&(m_flash_y[i]), data, sizeof(double));data += sizeof(double);
			}
			int zsize;
			memcpy(&zsize, data, sizeof(int));data += sizeof(int);
			m_flash_z.resize(zsize);
			for(int i = 0; i < zsize; i++)
			{
				memcpy(&(m_flash_z[i]), data, sizeof(double));data += sizeof(double);
			}
			int Ksize;
			memcpy(&Ksize, data, sizeof(int));data += sizeof(int);
			m_K.resize(Ksize);
			for(int i = 0; i < Ksize; i++)
			{
				memcpy(&(m_K[i]), data, sizeof(double));data += sizeof(double);
			}
			int MWsize;
			memcpy(&MWsize, data, sizeof(int));data += sizeof(int);
			m_MW.resize(MWsize);
			for(int i = 0; i < MWsize; i++)
			{
				memcpy(&(m_MW[i]), data, sizeof(double));data += sizeof(double);
			}
			int Tcisize;
			memcpy(&Tcisize, data, sizeof(int));data += sizeof(int);
			m_Tci.resize(Tcisize);
			for(int i = 0; i < Tcisize; i++)
			{
				memcpy(&(m_Tci[i]), data, sizeof(double));data += sizeof(double);
			}
			int Pcisize;
			memcpy(&Pcisize, data, sizeof(int));data += sizeof(int);
			m_Pci.resize(Pcisize);
			for(int i = 0; i < Pcisize; i++)
			{
				memcpy(&(m_Pci[i]), data, sizeof(double));data += sizeof(double);
			}
			int vcisize;
			memcpy(&vcisize, data, sizeof(int));data += sizeof(int);
			m_vci.resize(vcisize);
			for(int i = 0; i < vcisize; i++)
			{
				memcpy(&(m_vci[i]), data, sizeof(double));data += sizeof(double);
			}
			int Omegaisize;
			memcpy(&Omegaisize, data, sizeof(int));data += sizeof(int);
			m_Omegai.resize(Omegaisize);
			for(int i = 0; i < Omegaisize; i++)
			{
				memcpy(&(m_Omegai[i]), data, sizeof(double));data += sizeof(double);
			}
			int kijsize;
			memcpy(&kijsize, data, sizeof(int));data += sizeof(int);
			m_kij.resize(kijsize);
			for(int i = 0; i < kijsize; i++)
			{
				int kijisize;
				memcpy(&kijisize, data, sizeof(int));data += sizeof(int);
				m_kij[i].resize(kijisize);
				for(int j = 0; j < kijisize; j++)
				{
					memcpy(&(m_kij[i][j]), data, sizeof(double));data += sizeof(double);
				}
			}
			memcpy(&m_R, data, sizeof(double));data += sizeof(double);
			memcpy(&m_aHCType, data, sizeof(int));data += sizeof(int);
			memcpy(&m_SCT, data, sizeof(double));data += sizeof(double);
			memcpy(&m_SCTK, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_SCP, data, sizeof(double));data += sizeof(double);
			memcpy(&m_pb, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TmK, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PmMPa, data, sizeof(double));data += sizeof(double);
			memcpy(&m_pTc, data, sizeof(double));data += sizeof(double);
			memcpy(&m_pPc, data, sizeof(double));data += sizeof(double);
			memcpy(&m_a, data, sizeof(double));data += sizeof(double);
			memcpy(&m_b, data, sizeof(double));data += sizeof(double);
			memcpy(&m_vL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_vV, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_MWL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MWV, data, sizeof(double));data += sizeof(double); 
			int acisize;
			memcpy(&acisize, data, sizeof(int));data += sizeof(int);
			m_aci.resize(acisize);
			for(int i = 0; i < acisize; i++)
			{
				memcpy(&(m_aci[i]), data, sizeof(double));data += sizeof(double);
			}
			int bisize;
			memcpy(&bisize, data, sizeof(int));data += sizeof(int);
			m_bi.resize(bisize);
			for(int i = 0; i < bisize; i++)
			{
				memcpy(&(m_bi[i]), data, sizeof(double));data += sizeof(double);
			}
			int misize;
			memcpy(&misize, data, sizeof(int));data += sizeof(int);
			m_mi.resize(misize);
			for(int i = 0; i < misize; i++)
			{
				memcpy(&(m_mi[i]), data, sizeof(double));data += sizeof(double);
			}
			int Alphaisize;
			memcpy(&Alphaisize, data, sizeof(int));data += sizeof(int);
			m_Alphai.resize(Alphaisize);
			for(int i = 0; i < Alphaisize; i++)
			{
				memcpy(&(m_Alphai[i]), data, sizeof(double));data += sizeof(double);
			}
			int aisize;
			memcpy(&aisize, data, sizeof(int));data += sizeof(int);
			m_ai.resize(aisize);
			for(int i = 0; i < aisize; i++)
			{
				memcpy(&(m_ai[i]), data, sizeof(double));data += sizeof(double);
			}
			int Aisize;
			memcpy(&Aisize, data, sizeof(int));data += sizeof(int);
			m_Ai.resize(Aisize);
			for(int i = 0; i < Aisize; i++)
			{
				memcpy(&(m_Ai[i]), data, sizeof(double));data += sizeof(double);
			}
			int Bisize;
			memcpy(&Bisize, data, sizeof(int));data += sizeof(int);
			m_Bi.resize(Bisize);
			for(int i = 0; i < Bisize; i++)
			{
				memcpy(&(m_Bi[i]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&m_aL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_bL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_aV, data, sizeof(double));data += sizeof(double);
			memcpy(&m_bV, data, sizeof(double));data += sizeof(double);
			memcpy(&m_aEOS, data, sizeof(int));data += sizeof(int);
			memcpy(&m_AL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_AV, data, sizeof(double));data += sizeof(double);
			memcpy(&m_BL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_BV, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_ZL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ZV, data, sizeof(double));data += sizeof(double); 
			int FaiiLsize;
			memcpy(&FaiiLsize, data, sizeof(int));data += sizeof(int);
			m_FaiiL.resize(FaiiLsize);
			for(int i = 0; i < FaiiLsize; i++)
			{
				memcpy(&(m_FaiiL[i]), data, sizeof(double));data += sizeof(double);
			}
			int FaiiVsize;
			memcpy(&FaiiVsize, data, sizeof(int));data += sizeof(int);
			m_FaiiV.resize(FaiiVsize);
			for(int i = 0; i < FaiiVsize; i++)
			{
				memcpy(&(m_FaiiV[i]), data, sizeof(double));data += sizeof(double);
			}
			int fiLsize;
			memcpy(&fiLsize, data, sizeof(int));data += sizeof(int);
			m_fiL.resize(fiLsize);
			for(int i = 0; i < fiLsize; i++)
			{
				memcpy(&(m_fiL[i]), data, sizeof(double));data += sizeof(double);
			}
			int fiVsize;
			memcpy(&fiVsize, data, sizeof(int));data += sizeof(int);
			m_fiV.resize(fiVsize);
			for(int i = 0; i < fiVsize; i++)
			{
				memcpy(&(m_fiV[i]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&m_OilDensitySC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_API, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GOR, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Bo, data, sizeof(double));data += sizeof(double);
			int KSCsize;
			memcpy(&KSCsize, data, sizeof(int));data += sizeof(int);
			m_KSC.resize(KSCsize);
			for(int i = 0; i < KSCsize; i++)
			{
				memcpy(&(m_KSC[i]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&m_nvSC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_nlSC, data, sizeof(double));data += sizeof(double);  
			int xSCsize;
			memcpy(&xSCsize, data, sizeof(int));data += sizeof(int);
			m_xSC.resize(xSCsize);
			for(int i = 0; i < xSCsize; i++)
			{
				memcpy(&(m_xSC[i]), data, sizeof(double));data += sizeof(double);
			}
			int ySCsize;
			memcpy(&ySCsize, data, sizeof(int));data += sizeof(int);
			m_ySC.resize(ySCsize);
			for(int i = 0; i < ySCsize; i++)
			{
				memcpy(&(m_ySC[i]), data, sizeof(double));data += sizeof(double);
			}
			memcpy(&m_MWLSC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_vLSC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MWVSC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_vVSC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GasDensitySC, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, FlashCalculationVariable &flashcalculation)
		{
			os << "\r\n>>>>>>>>>>>>>>>flash calculation parameter as flow:";
			os << "\r\n---- ---- ---- flashcalculated:" << flashcalculation.m_flashcalculated;
			os << "\r\n---- ---- ---- Sgg:" << flashcalculation.m_Sgg; //��������ܶ�   ��Good Oil: Sgg= 0.855
			os << "\r\n---- ---- ---- Soo:" << flashcalculation.m_Soo;//�͵�����ܶ�     ; Good Oil:  Soo=0.823
			os << "\r\n---- ---- ---- T_F:" << flashcalculation.m_T_F; //�����¶�
			os << "\r\n---- ---- ---- MolFraC1InWater:" << flashcalculation.m_MolFraC1InWater; //molar fraction of methane in water
			os << "\r\n---- ---- ---- nl:" << flashcalculation.m_nl;
			os << "\r\n---- ---- ---- nv:" << flashcalculation.m_nv; //�ֱ���Һ̬����̬��Ħ������
			os << "\r\n---- ---- ---- NCom:" << flashcalculation.m_NCom; //��N����ֵ�����
			for(int i = 0; i < flashcalculation.m_aProperties.size(); i++)
			{
				os << "\r\n---- ---- ---- aProperties:" << i << ":";os << flashcalculation.m_aProperties[i];
			}
			for(int i = 0; i < flashcalculation.m_flash_x.size(); i++)
			{
				os << "\r\n---- ---- ---- flash_x:" << i << ":" << flashcalculation.m_flash_x[i];
			}
			for(int i = 0; i < flashcalculation.m_flash_y.size(); i++)
			{
				os << "\r\n---- ---- ---- flash_y:" << i << ":" << flashcalculation.m_flash_y[i];
			}
			for(int i = 0; i < flashcalculation.m_flash_z.size(); i++)
			{
				os << "\r\n---- ---- ---- flash_z:" << i << ":" << flashcalculation.m_flash_z[i];
			}
			for(int i = 0; i < flashcalculation.m_K.size(); i++)
			{
				os << "\r\n---- ---- ---- K:" << i << ":" << flashcalculation.m_K[i];
			}
			for(int i = 0; i < flashcalculation.m_MW.size(); i++)
			{
				os << "\r\n---- ---- ---- MW:" << i << ":" << flashcalculation.m_MW[i];
			}
			for(int i = 0; i < flashcalculation.m_Tci.size(); i++)
			{
				os << "\r\n---- ---- ---- Tci:" << i << ":" << flashcalculation.m_Tci[i];
			}
			for(int i = 0; i < flashcalculation.m_Pci.size(); i++)
			{
				os << "\r\n---- ---- ---- Pci:" << i << ":" << flashcalculation.m_Pci[i];
			}
			for(int i = 0; i < flashcalculation.m_vci.size(); i++)
			{
				os << "\r\n---- ---- ---- vci:" << i << ":" << flashcalculation.m_vci[i];
			}
			for(int i = 0; i < flashcalculation.m_Omegai.size(); i++)
			{
				os << "\r\n---- ---- ---- Omegai:" << i << ":" << flashcalculation.m_Omegai[i];
			}
			for(int i = 0; i < flashcalculation.m_kij.size(); i++)
			{
				for(int j = 0; j < flashcalculation.m_kij[i].size(); j++)
				{
					os << "\r\n---- ---- ---- kij:" << i << ":" << j << ":" << flashcalculation.m_kij[i][j];
				}
			}
			os << "\r\n---- ---- ---- R:" << flashcalculation.m_R;//���峣�� ��=0.008314;0.008314 KJ/(mol*K)
			os << "\r\n---- ---- ---- aHCType:" << flashcalculation.m_aHCType;
			os << "\r\n---- ---- ---- SCT:" << flashcalculation.m_SCT; //��׼�����µ��¶�15.556���϶�
			os << "\r\n---- ---- ---- SCTK:" << flashcalculation.m_SCTK; // ��׼�����µ��¶ȿ����¶�
			os << "\r\n---- ---- ---- SCP:" << flashcalculation.m_SCP; //��׼�����µ�ѹ��1 atm 0.1MPa
			os << "\r\n---- ---- ---- pb:" << flashcalculation.m_pb; //��ϵ���ݵ�ѹ�� ��MPa
			os << "\r\n---- ---- ---- TmK:" << flashcalculation.m_TmK; //�в��¶ȣ��ÿ����¶ȱ�ʾ��������̬����
			os << "\r\n---- ---- ---- PmMPa:" << flashcalculation.m_PmMPa; //�в�ѹ������������ʾ��������̬����
			os << "\r\n---- ---- ---- pTc:" << flashcalculation.m_pTc; //׼�ٽ��¶� K   pseudo critical temperature  ,������ֵΪ��ϵ�¶�
			os << "\r\n---- ---- ---- pPc:" << flashcalculation.m_pPc; //׼�ٽ�ѹ�� MPa
			os << "\r\n---- ---- ---- a:" << flashcalculation.m_a;
			os << "\r\n---- ---- ---- b:" << flashcalculation.m_b; //�ֱ��Ӧ���ٽ���̬��aֵ��bֵ
			os << "\r\n---- ---- ---- vL:" << flashcalculation.m_vL;
			os << "\r\n---- ---- ---- vV:" << flashcalculation.m_vV;  //�ֱ����ͺ�����Ħ�����  m3/kgmol
			os << "\r\n---- ---- ---- MWL:" << flashcalculation.m_MWL;
			os << "\r\n---- ---- ---- MWV:" << flashcalculation.m_MWV; //�ֱ�������������Ħ������
			for(int i = 0; i < flashcalculation.m_aci.size(); i++)
			{
				os << "\r\n---- ---- ---- aci:" << i << ":" << flashcalculation.m_aci[i];
			}
			for(int i = 0; i < flashcalculation.m_bi.size(); i++)
			{
				os << "\r\n---- ---- ---- bi:" << i << ":" << flashcalculation.m_bi[i];
			}
			for(int i = 0; i < flashcalculation.m_mi.size(); i++)
			{
				os << "\r\n---- ---- ---- mi:" << i << ":" << flashcalculation.m_mi[i];
			}
			for(int i = 0; i < flashcalculation.m_Alphai.size(); i++)
			{
				os << "\r\n---- ---- ---- Alphai:" << i << ":" << flashcalculation.m_Alphai[i];
			}
			for(int i = 0; i < flashcalculation.m_ai.size(); i++)
			{
				os << "\r\n---- ---- ---- ai:" << i << ":" << flashcalculation.m_ai[i];
			}
			for(int i = 0; i < flashcalculation.m_Ai.size(); i++)
			{
				os << "\r\n---- ---- ---- Ai:" << i << ":" << flashcalculation.m_Ai[i];
			}
			for(int i = 0; i < flashcalculation.m_Bi.size(); i++)
			{
				os << "\r\n---- ---- ---- Bi:" << i << ":" << flashcalculation.m_Bi[i];
			}
			os << "\r\n---- ---- ---- aL:" << flashcalculation.m_aL;
			os << "\r\n---- ---- ---- bL:" << flashcalculation.m_bL;
			os << "\r\n---- ---- ---- aV:" << flashcalculation.m_aV;
			os << "\r\n---- ---- ---- bV:" << flashcalculation.m_bV; //�ֱ��Ӧ���ͺ�����aֵ��bֵ
			os << "\r\n---- ---- ---- aEOS:" << flashcalculation.m_aEOS;
			os << "\r\n---- ---- ---- AL:" << flashcalculation.m_AL;
			os << "\r\n---- ---- ---- AV:" << flashcalculation.m_AV;
			os << "\r\n---- ---- ---- BL:" << flashcalculation.m_BL;
			os << "\r\n---- ---- ---- BV:" << flashcalculation.m_BV; // �ֱ��Ӧ���ͺ���
			os << "\r\n---- ---- ---- ZL:" << flashcalculation.m_ZL;
			os << "\r\n---- ---- ---- ZV:" << flashcalculation.m_ZV; //Һ������壬���ͺ�����ѹ��ϵ��
			for(int i = 0; i < flashcalculation.m_FaiiL.size(); i++)
			{
				os << "\r\n---- ---- ---- m_FaiiL:" << i << ":" << flashcalculation.m_FaiiL[i];
			}
			for(int i = 0; i < flashcalculation.m_FaiiV.size(); i++)
			{
				os << "\r\n---- ---- ---- m_FaiiV:" << i << ":" << flashcalculation.m_FaiiV[i];
			}
			for(int i = 0; i < flashcalculation.m_fiL.size(); i++)
			{
				os << "\r\n---- ---- ---- m_fiL:" << i << ":" << flashcalculation.m_fiL[i];
			}
			for(int i = 0; i < flashcalculation.m_fiV.size(); i++)
			{
				os << "\r\n---- ---- ---- m_fiV:" << i << ":" << flashcalculation.m_fiV[i];
			}
			os << "\r\n---- ---- ---- OilDensitySC:" << flashcalculation.m_OilDensitySC; //��׼������ԭ�͵��ܶ�
			os << "\r\n---- ---- ---- API:" << flashcalculation.m_API; //��׼�������͵��ض�
			os << "\r\n---- ---- ---- GOR:" << flashcalculation.m_GOR;//���ͱ�  m3/m3
			os << "\r\n---- ---- ---- Bo:" << flashcalculation.m_Bo; //ԭ�����ϵ��������Ϊ����ԭ����������ԭ�����֮��
			for(int i = 0; i < flashcalculation.m_KSC.size(); i++)
			{
				os << "\r\n---- ---- ---- m_KSC:" << i << ":" << flashcalculation.m_KSC[i];
			}
			os << "\r\n---- ---- ---- nvSC:" << flashcalculation.m_nvSC;
			os << "\r\n---- ---- ---- nlSC:" << flashcalculation.m_nlSC;    //��׼����������������Ħ����
			for(int i = 0; i < flashcalculation.m_xSC.size(); i++)
			{
				os << "\r\n---- ---- ---- m_xSC:" << i << ":" << flashcalculation.m_xSC[i];
			}
			for(int i = 0; i < flashcalculation.m_ySC.size(); i++)
			{
				os << "\r\n---- ---- ---- m_ySC:" << i << ":" << flashcalculation.m_ySC[i];
			}
			os << "\r\n---- ---- ---- MWLSC:" << flashcalculation.m_MWLSC;
			os << "\r\n---- ---- ---- vLSC:" << flashcalculation.m_vLSC;
			os << "\r\n---- ---- ---- MWVSC:" << flashcalculation.m_MWVSC;
			os << "\r\n---- ---- ---- vVSC:" << flashcalculation.m_vVSC;
			os << "\r\n---- ---- ---- GasDensitySC:" << flashcalculation.m_GasDensitySC; // ��׼�����������ܶ� 
			return os;
		}
		void GetGroupkij(int NCom,std::vector<std::vector<double> >&kij,std::vector<std::vector<double> >&GasOilkij,std::vector<PropertiesVariable> &aProperties)
		{ //�������ּ��Binary interaction parameters  Danesh,1998, p309 9.16
			for(int k=0;k<NCom;k++) for(int q=0;q<NCom;q++)kij[k][q]=0;
			for(int k=0;k<NCom;k++) for(int q=0;q<NCom;q++)
			{
				if(k!=q)
					for(int i=0;i<aProperties[k].m_NGroupCom;i++) for(int j=0;j<aProperties[q].m_NGroupCom;j++)
					{
						kij[k][q]+=aProperties[k].m_ComMolFra[i]*aProperties[q].m_ComMolFra[j]*GasOilkij[i][j]/(aProperties[k].m_z*aProperties[q].m_z);
					}
			}
		}
		void GetProperties(int aNCom,std::vector<PropertiesVariable> &aProperties,std::vector<std::vector<double> > &akij,int aaEOS)
		{    //��ú���ģ����ֲ���
			m_NCom=aNCom;
			m_MW.resize(m_NCom);   m_Tci.resize(m_NCom);
			m_Pci.resize(m_NCom); m_Omegai.resize(m_NCom);
			m_kij.resize(m_NCom);
			m_flash_x.resize(m_NCom); m_flash_y.resize(m_NCom);
			m_flash_z.resize(m_NCom);  m_K.resize(m_NCom);
			m_vci.resize(m_NCom);
			for(int i=0;i<m_NCom;i++) m_kij[i].resize(m_NCom);  //
			m_aci.resize(m_NCom);m_bi.resize(m_NCom);m_mi.resize(m_NCom);m_Alphai.resize(m_NCom);m_ai.resize(m_NCom);
			m_Ai.resize(m_NCom);m_Bi.resize(m_NCom); //û����
			m_FaiiL.resize(m_NCom); m_FaiiV.resize(m_NCom);
			m_fiL.resize(m_NCom); m_fiV.resize(m_NCom);
			m_xSC.resize(m_NCom); m_ySC.resize(m_NCom);
			m_KSC.resize(m_NCom);
			for(int i=0;i<m_NCom;i++)
			{
				m_MW[i]=aProperties[i].m_MW; m_Tci[i]=aProperties[i].m_Tc; m_Pci[i]=aProperties[i].m_Pc;
				m_Omegai[i]=aProperties[i].m_Omega; m_flash_z[i]=aProperties[i].m_z;m_vci[i]=aProperties[i].m_Vc;/**/
			}
			m_R=0.008314;//���峣�� ��
			m_aEOS=aaEOS;
			for(int i=0;i<m_NCom;i++)for(int j=0;j<m_NCom;j++)m_kij[i][j]=akij[i][j];
			m_SCT=15.556+273.15; //��׼�����µ��¶�15.556���϶�
			m_SCP=0.101325; //��׼�����µ�ѹ��1 atm 0.1MPa
		}
		void GetBehar4CProperties()
		{  //Behar1997�����C1��C2_C5,C6_C14,C15Plus�Ļ����ϵ����
			m_NCom=4;
			m_MW.resize(m_NCom);   m_Tci.resize(m_NCom);
			m_Pci.resize(m_NCom); m_Omegai.resize(m_NCom);
			m_kij.resize(m_NCom);
			m_flash_x.resize(m_NCom); m_flash_y.resize(m_NCom);
			m_flash_z.resize(m_NCom);  m_K.resize(m_NCom);
			m_vci.resize(m_NCom);
			for(int i=0;i<m_NCom;i++) m_kij[i].resize(m_NCom);
			m_aci.resize(m_NCom);m_bi.resize(m_NCom);m_mi.resize(m_NCom);m_Alphai.resize(m_NCom);m_ai.resize(m_NCom);
			m_Ai.resize(m_NCom);m_Bi.resize(m_NCom); //û����
			m_FaiiL.resize(m_NCom); m_FaiiV.resize(m_NCom);
			m_fiL.resize(m_NCom); m_fiV.resize(m_NCom);
			m_xSC.resize(m_NCom); m_ySC.resize(m_NCom);
			m_KSC.resize(m_NCom);

			//  z[0]=0.6;z[1]=0.4;         //
			m_MW[0]=16.043; m_MW[1]=53.070; m_MW[2]=137.378; m_MW[3]=311.950;
			m_Tci[0]=190.56; m_Tci[1]=400.97; m_Tci[2]=605.58; m_Tci[3]=824.32;
			m_Pci[0]=4.599; m_Pci[1]=3.996; m_Pci[2]=2.215; m_Pci[3]=1.392;
			m_Omegai[0]=0.0115; m_Omegai[1]=0.1828;   m_Omegai[2]=0.4717; m_Omegai[3]=0.8079;
			m_vci[0]=0.0986;m_vci[1]=0.2360;  m_vci[2]=0.5801;m_vci[3]=1.0926;   //m^3/kgmol
			m_R=0.008314;//���峣�� ��
			m_SCT=15.556+273.15; //��׼�����µ��¶�15.556���϶�
			m_SCP=0.101325; //��׼�����µ�ѹ��1 atm 0.1MPa
			m_aEOS=PR;
			switch(m_aEOS)
			{   //����ֵ��໥����ϵ���ֱ���C1,C4,C10,C23������
			case SRK:
				m_kij[0][0]=0;m_kij[0][1]=0.0056; m_kij[0][2]=0.0550;m_kij[0][3]=0.0650;
				m_kij[1][0]=0.0056;m_kij[1][1]=0; m_kij[1][2]=0.0010;m_kij[1][3]=0.0015;
				m_kij[2][0]=0.0550;m_kij[2][1]=0.0010; m_kij[2][2]=0;m_kij[2][3]=0;
				m_kij[3][0]=0.0650;m_kij[3][1]=0.0015; m_kij[3][2]=0;m_kij[3][3]=0;
				break;
			case PR:
				m_kij[0][0]=0;m_kij[0][1]=0.0133; m_kij[0][2]=0.0500;m_kij[0][3]=0.0700;
				m_kij[1][0]=0.0133;m_kij[1][1]=0; m_kij[1][2]=0.0010;m_kij[1][3]=0.0015;
				m_kij[2][0]=0.0500;m_kij[2][1]=0.0010; m_kij[2][2]=0;m_kij[2][3]=0;
				m_kij[3][0]=0.0700;m_kij[3][1]=0.0015; m_kij[3][2]=0;m_kij[3][3]=0;
				break;
			};
		}
	};

	//
	//
	//
	/*!
	* �������������VERTEX������Ǩ�ƽ�Ĵ���
	**/
	struct VertexSimulated : public AnyCGAL::Vertex3D, \
		public PVTVariable,\
		public BorderVariable, \
		public PhysicalVariable, \
		public DensityVariable, \
		public CapacityVariable, \
		public PhaseVariable, \
		public OverPressureVariable, \
		public RoVariable, \
		public HydroGenerationVariable,\
		public FlashCalculationVariable, \
		public HydroExpellVariable 
	{
		VertexSimulated()
		{
		}
		VertexSimulated(const VertexSimulated &other)
		{
			*this = other;
		}
		const VertexSimulated &operator=(const VertexSimulated &other)
		{
			if(this == &other)
			{
				return *this;
			}

			*((Vertex3D*)this) = *((Vertex3D*)&other);
			*((PVTVariable*)this) = *((PVTVariable*)&other);
			*((BorderVariable*)this) = *((BorderVariable*)&other);
			*((PhysicalVariable*)this) = *((PhysicalVariable*)&other);
			*((DensityVariable*)this) = *((DensityVariable*)&other);
			*((CapacityVariable*)this) = *((CapacityVariable*)&other);
			*((PhaseVariable*)this) = *((PhaseVariable*)&other);
			*((OverPressureVariable*)this) = *((OverPressureVariable*)&other);
			*((RoVariable*)this) = *((RoVariable*)&other);
			*((HydroGenerationVariable*)this) = *((HydroGenerationVariable*)&other);
			*((FlashCalculationVariable*)this) = *((FlashCalculationVariable*)&other);
			*((HydroExpellVariable*)this) = *((HydroExpellVariable*)&other);

			return *this;
		}
		void CopyFromVertex3D(AnyCGAL::Vertex3D &other)
		{
			*((Vertex3D*)this) = *((Vertex3D*)&other);
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			//Vertex3D
			curSize += Vertex3D::GetSerializeDataLength();
			//PVTVariable
			curSize += PVTVariable::GetSerializeDataLength();
			//BorderVariable
			curSize += BorderVariable::GetSerializeDataLength();
			//PhysicalVariable
			curSize += PhysicalVariable::GetSerializeDataLength();
			//DensityVariable
			curSize += DensityVariable::GetSerializeDataLength();
			//CapacityVariable
			curSize += CapacityVariable::GetSerializeDataLength();
			//PhaseVariable
			curSize += PhaseVariable::GetSerializeDataLength();
			//OverPressureVariable
			curSize += OverPressureVariable::GetSerializeDataLength();
			// RoVariable
			curSize += RoVariable::GetSerializeDataLength();
			// HydroGenerationVariable
			curSize += HydroGenerationVariable::GetSerializeDataLength();
			// FlashCalculationVariable
			curSize += FlashCalculationVariable::GetSerializeDataLength();
			// HydroExpellVariable
			curSize += HydroExpellVariable::GetSerializeDataLength();
			return curSize;
		}
		int GetSerializeDataLength_Mini()
		{
			int curSize = 0;
			//Vertex3D
			curSize += Vertex3D::GetSerializeDataLength();
			//Others
			curSize += sizeof(double);//double m_temperature;
			curSize += sizeof(double);//double m_ever_porosity;
			curSize += sizeof(double);//double m_water_fluid_pressure;
			curSize += sizeof(double);//double m_OGIFromKerogen;
			curSize += sizeof(double);//double m_GGIFromKerogen;
			curSize += sizeof(double);//double m_TOC;
			curSize += sizeof(double);//double m_litho_pressure;
			curSize += sizeof(double);//double m_effective_max_stress;
			curSize += sizeof(double);//double m_paleo_water_depth;
			curSize += sizeof(double);//double m_ever_thickness;
			curSize += sizeof(double);//double m_bury_from_age;
			curSize += sizeof(double);//double m_bury_depth;
			curSize += sizeof(double);//double m_Ro;
			curSize += sizeof(double);//double m_water_static_pressure;
			curSize += sizeof(double);//double m_ever_middle_permeability;
			curSize += sizeof(double);//double m_total_density;
			curSize += sizeof(double);//double m_paleo_heat_fluid;
			curSize += sizeof(double);//double m_Tmax;
			curSize += sizeof(double);//double m_middle_temperature;
			curSize += sizeof(double);//double m_TOCRemained;
			curSize += sizeof(double);//double m_paleo_surface_temperature;
			curSize += sizeof(double);//double m_TR;
			curSize += sizeof(double);//double m_MKer;
			curSize += sizeof(double);//double m_So;
			curSize += sizeof(double);//double m_Sg;
			return curSize;
		}
		char *SerializeData(int &len)
		{
			char *data;
			len = GetSerializeDataLength();
			data = (char*)malloc(len);
			//Vertex3D
			Vertex3D::SerializeData(data);
			//PVTVariable
			PVTVariable::SerializeData(data);
			//BorderVariable
			BorderVariable::SerializeData(data);
			//PhysicalVariable
			PhysicalVariable::SerializeData(data);
			//DensityVariable
			DensityVariable::SerializeData(data);
			//CapacityVariable
			CapacityVariable::SerializeData(data);
			//PhaseVariable
			PhaseVariable::SerializeData(data);
			//OverPressureVariable
			OverPressureVariable::SerializeData(data);
			// RoVariable
			RoVariable::SerializeData(data);
			// HydroGenerationVariable
			HydroGenerationVariable::SerializeData(data);
			// FlashCalculationVariable
			FlashCalculationVariable::SerializeData(data);
			// HydroExpellVariable
			HydroExpellVariable::SerializeData(data);
			data -= len;
			return data;
		}
		char *SerializeData_Mini(int &len)
		{
			char *data;
			len = GetSerializeDataLength_Mini();
			data = (char*)malloc(len);
			//Vertex3D
			Vertex3D::SerializeData(data);
			//Others
			memcpy(data, &m_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ever_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_fluid_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OGIFromKerogen, sizeof(double));data += sizeof(double);
			memcpy(data, &m_GGIFromKerogen, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TOC, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_effective_max_stress, sizeof(double));data += sizeof(double);
			memcpy(data, &m_paleo_water_depth, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ever_thickness, sizeof(double));data += sizeof(double);
			memcpy(data, &m_bury_from_age, sizeof(double));data += sizeof(double);
			memcpy(data, &m_bury_depth, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Ro, sizeof(double));data += sizeof(double);
			memcpy(data, &m_water_static_pressure, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ever_middle_permeability, sizeof(double));data += sizeof(double);
			memcpy(data, &m_total_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_paleo_heat_fluid, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Tmax, sizeof(double));data += sizeof(double);
			memcpy(data, &m_middle_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TOCRemained, sizeof(double));data += sizeof(double);
			memcpy(data, &m_paleo_surface_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TR, sizeof(double));data += sizeof(double);
			memcpy(data, &m_MKer, sizeof(double));data += sizeof(double);
			memcpy(data, &m_So, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Sg, sizeof(double));data += sizeof(double);
			data -= len;
			return data;
		}
		void RestoreSerializeData(char* &data)
		{
			//Vertex3D
			Vertex3D::RestoreSerializeData(data);
			//PVTVariable
			PVTVariable::RestoreSerializeData(data);
			//BorderVariable
			BorderVariable::RestoreSerializeData(data);
			//PhysicalVariable
			PhysicalVariable::RestoreSerializeData(data);
			//DensityVariable
			DensityVariable::RestoreSerializeData(data);
			//CapacityVariable
			CapacityVariable::RestoreSerializeData(data);
			//PhaseVariable
			PhaseVariable::RestoreSerializeData(data);
			//OverPressureVariable
			OverPressureVariable::RestoreSerializeData(data);
			// RoVariable
			RoVariable::RestoreSerializeData(data);
			// HydroGenerationVariable
			HydroGenerationVariable::RestoreSerializeData(data);
			// FlashCalculationVariable
			FlashCalculationVariable::RestoreSerializeData(data);
			// HydroExpellVariable
			HydroExpellVariable::RestoreSerializeData(data);
		}
		void RestoreSerializeData_Mini(char* &data)
		{
			//Vertex3D
			Vertex3D::RestoreSerializeData(data);
			//Others
			memcpy(&m_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ever_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_fluid_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OGIFromKerogen, data, sizeof(double));data += sizeof(double);
			memcpy(&m_GGIFromKerogen, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TOC, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_effective_max_stress, data, sizeof(double));data += sizeof(double);
			memcpy(&m_paleo_water_depth, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ever_thickness, data, sizeof(double));data += sizeof(double);
			memcpy(&m_bury_from_age, data, sizeof(double));data += sizeof(double);
			memcpy(&m_bury_depth, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Ro, data, sizeof(double));data += sizeof(double);
			memcpy(&m_water_static_pressure, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ever_middle_permeability, data, sizeof(double));data += sizeof(double);
			memcpy(&m_total_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_paleo_heat_fluid, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Tmax, data, sizeof(double));data += sizeof(double);
			memcpy(&m_middle_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TOCRemained, data, sizeof(double));data += sizeof(double);
			memcpy(&m_paleo_surface_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TR, data, sizeof(double));data += sizeof(double);
			memcpy(&m_MKer, data, sizeof(double));data += sizeof(double);
			memcpy(&m_So, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Sg, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, VertexSimulated &vertex)
		{
			//os << "\r\n---- ---- VertexSimulated variables ----- ----- ";
			os << *((Vertex3D *)(&vertex));
			os << *((PVTVariable *)(&vertex));
			os << *((BorderVariable *)(&vertex));
			os << *((PhysicalVariable *)(&vertex));
			os << *((DensityVariable *)(&vertex));
			os << *((CapacityVariable *)(&vertex));
			os << *((PhaseVariable *)(&vertex));
			os << *((OverPressureVariable *)(&vertex));
			os << *((RoVariable *)(&vertex));
			os << *((HydroGenerationVariable *)(&vertex));
			os << *((FlashCalculationVariable *)(&vertex));
			os << *((HydroExpellVariable *)(&vertex));
			return os;
		}
	};

	///////////////////////////////////////
	//
	//
	// litho unit data
	struct LithoVariable
	{
		// match the library
		long m_litho_idx;
		string m_litho_name;
		//���Եı���
		double m_litho_ratio;
		//�жϻ��������Ƿ�Ϊ���Ҹ���ú
		bool m_litho_is_ThisMatrixKerogenOrCoal;
		//��϶��
		double m_litho_initial_porosity;
		double m_litho_ever_bottom_porosity; // for each simulation step
		double m_litho_ever_middle_porosity;
		double m_litho_ever_top_porosity;

		double m_litho_ever_permeability;
		double m_litho_ever_middle_permeability;

		//ѹʵϵ������λ��С��
		double m_litho_initial_compaction_factor;
		//��ʯ�����ܶ� ��kg/m^3
		double m_litho_matrix_density;
		//��ʯ�����ȵ��� ��W/(m��)
		double m_litho_matrix_thermal_cond;
		double m_litho_ThermalCondAnisotr;  //��ͬ���Ե��ȵ��ʵĸ�������ϵ��

		//��ʯ������ ��J/(kg��)
		double m_litho_matrix_heat_capacity;
		//��ʯ���ʵķ����������� ��W/m^3
		double m_litho_matrix_radioactive_heat;
		// ��϶��-��͸�ʹ�ϵ�Թ�ʽ
		string m_litho_poro_perm_formulare;
		// ��϶��-��͸�ʵ������� m_x: porosity, m_y: permeability
		std::vector<CGeoPoint<double> > m_litho_poro_perm_points;
		// ��Ӧ��ͻ��ë��ѹ���Ĳ��� double **aToEntryPr,**bToEntryPr;
		std::vector<CGeoPoint<double> > m_litho_a_pressure_points;
		std::vector<CGeoPoint<double> > m_litho_b_pressure_points;

		double m_Perm_Anisotr;//��ͬ������͸�ʸ�������ֵ����ˮƽ�����봹ֱ������͸�ʱ�ֵ

		//
		LithoVariable()
		{
			m_litho_idx = 0;
			m_litho_name = "";
			m_litho_ratio = 0;
			m_litho_is_ThisMatrixKerogenOrCoal = false;
			m_litho_initial_porosity = 0;
			m_litho_ever_bottom_porosity = 0;
			m_litho_ever_middle_porosity = 0;
			m_litho_ever_top_porosity = 0;
			m_litho_ever_permeability = 0;
			m_litho_ever_middle_permeability = 0;
			m_litho_initial_compaction_factor = 0;
			m_litho_matrix_density = 0;
			m_litho_matrix_thermal_cond = 0;
			m_litho_ThermalCondAnisotr = 1.5;
			m_litho_matrix_heat_capacity = 0;
			m_litho_matrix_radioactive_heat = 0;
			m_litho_poro_perm_formulare = "";
			m_Perm_Anisotr = 1.5;
		}
		LithoVariable(const LithoVariable &other)
		{
			*this = other;
		}
		const LithoVariable &operator=(const LithoVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_litho_idx = other.m_litho_idx;
			m_litho_name = other.m_litho_name;
			m_litho_ratio = other.m_litho_ratio;
			m_litho_is_ThisMatrixKerogenOrCoal = other.m_litho_is_ThisMatrixKerogenOrCoal;
			m_litho_initial_porosity = other.m_litho_initial_porosity;
			m_litho_ever_bottom_porosity = other.m_litho_ever_bottom_porosity;
			m_litho_ever_middle_porosity = other.m_litho_ever_middle_porosity;
			m_litho_ever_top_porosity = other.m_litho_ever_top_porosity;
			m_litho_ever_permeability = other.m_litho_ever_permeability;
			m_litho_ever_middle_permeability = other.m_litho_ever_middle_permeability;
			m_litho_initial_compaction_factor = other.m_litho_initial_compaction_factor;
			m_litho_matrix_density = other.m_litho_matrix_density;
			m_litho_matrix_thermal_cond = other.m_litho_matrix_thermal_cond;
			m_litho_ThermalCondAnisotr = other.m_litho_ThermalCondAnisotr;
			m_litho_matrix_heat_capacity = other.m_litho_matrix_heat_capacity;
			m_litho_matrix_radioactive_heat = other.m_litho_matrix_radioactive_heat;
			m_litho_poro_perm_formulare = other.m_litho_poro_perm_formulare;
			m_litho_poro_perm_points = other.m_litho_poro_perm_points;
			m_litho_a_pressure_points = other.m_litho_a_pressure_points;
			m_litho_b_pressure_points = other.m_litho_b_pressure_points;
			m_Perm_Anisotr = other.m_Perm_Anisotr;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(long);//long m_litho_idx;
			curSize += (sizeof(int) + m_litho_name.length() * sizeof(char));//string m_litho_name;
			curSize += sizeof(double);//double m_litho_ratio;
			curSize += sizeof(bool);//bool m_litho_is_ThisMatrixKerogenOrCoal;
			curSize += sizeof(double);//double m_litho_initial_porosity;
			curSize += sizeof(double);//double m_litho_ever_bottom_porosity;
			curSize += sizeof(double);//double m_litho_ever_middle_porosity;
			curSize += sizeof(double);//double m_litho_ever_top_porosity;
			curSize += sizeof(double);//double m_litho_ever_permeability;
			curSize += sizeof(double);//double m_litho_ever_middle_permeability;
			curSize += sizeof(double);//double m_litho_initial_compaction_factor;
			curSize += sizeof(double);//double m_litho_matrix_density;
			curSize += sizeof(double);//double m_litho_matrix_thermal_cond;
			curSize += sizeof(double);//double m_litho_ThermalCondAnisotr;
			curSize += sizeof(double);//double m_litho_matrix_heat_capacity;
			curSize += sizeof(double);//double m_litho_matrix_radioactive_heat;
			curSize += (sizeof(int) + m_litho_poro_perm_formulare.length() * sizeof(char));//string m_litho_poro_perm_formulare;
			curSize += (sizeof(int) + m_litho_poro_perm_points.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_litho_poro_perm_points;
			curSize += (sizeof(int) + m_litho_a_pressure_points.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_litho_a_pressure_points;
			curSize += (sizeof(int) + m_litho_b_pressure_points.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_litho_b_pressure_points;
			curSize += sizeof(double);//double m_Perm_Anisotr;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_litho_idx, sizeof(long));data += sizeof(long);
			int lithonamelength = m_litho_name.length();
			memcpy(data, &lithonamelength, sizeof(int));data += sizeof(int);
			for(int j = 0; j < m_litho_name.length(); j++)
			{
				memcpy(data, &(m_litho_name[j]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_litho_ratio, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_is_ThisMatrixKerogenOrCoal, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_litho_initial_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ever_bottom_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ever_middle_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ever_top_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ever_permeability, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ever_middle_permeability, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_initial_compaction_factor, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_matrix_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_matrix_thermal_cond, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_ThermalCondAnisotr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_matrix_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_litho_matrix_radioactive_heat, sizeof(double));data += sizeof(double);
			int formularelength = m_litho_poro_perm_formulare.length();
			memcpy(data, &formularelength, sizeof(int));data += sizeof(int);
			for(int j = 0; j < m_litho_poro_perm_formulare.length(); j++)
			{
				memcpy(data, &(m_litho_poro_perm_formulare[j]), sizeof(char));data += sizeof(char);
			}
			int litho_poro_perm_pointssize = m_litho_poro_perm_points.size();
			memcpy(data, &litho_poro_perm_pointssize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < m_litho_poro_perm_points.size(); j++)
			{
				memcpy(data, &(m_litho_poro_perm_points[j]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
			int litho_a_pressure_pointssize = m_litho_a_pressure_points.size();
			memcpy(data, &litho_a_pressure_pointssize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < m_litho_a_pressure_points.size(); j++)
			{
				memcpy(data, &(m_litho_a_pressure_points[j]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
			int litho_b_pressure_pointssize = m_litho_b_pressure_points.size();
			memcpy(data, &litho_b_pressure_pointssize, sizeof(int));data += sizeof(int);
			for(int j = 0; j < m_litho_b_pressure_points.size(); j++)
			{
				memcpy(data, &(m_litho_b_pressure_points[j]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
			memcpy(data, &m_Perm_Anisotr, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_litho_idx, data, sizeof(long));data += sizeof(long);
			int lithonamelength;
			memcpy(&lithonamelength, data, sizeof(int));data += sizeof(int);
			m_litho_name = "";
			for(int j = 0; j < lithonamelength; j++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_litho_name += temp;
			}
			memcpy(&m_litho_ratio, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_is_ThisMatrixKerogenOrCoal, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_litho_initial_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ever_bottom_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ever_middle_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ever_top_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ever_permeability, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ever_middle_permeability, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_initial_compaction_factor, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_matrix_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_matrix_thermal_cond, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_ThermalCondAnisotr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_matrix_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_litho_matrix_radioactive_heat, data, sizeof(double));data += sizeof(double);
			int formularelength;
			memcpy(&formularelength, data, sizeof(int));data += sizeof(int);
			m_litho_poro_perm_formulare = "";
			for(int j = 0; j < formularelength; j++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_litho_poro_perm_formulare += temp;
			}
			int litho_poro_perm_pointssize;
			memcpy(&litho_poro_perm_pointssize, data, sizeof(int));data += sizeof(int);
			for(int j = 0; j < litho_poro_perm_pointssize; j++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_litho_poro_perm_points.push_back(temp);
			}
			int litho_a_pressure_pointssize;
			memcpy(&litho_a_pressure_pointssize, data, sizeof(int));data += sizeof(int);
			for(int j = 0; j < litho_a_pressure_pointssize; j++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_litho_a_pressure_points.push_back(temp);
			}
			int litho_b_pressure_pointssize;
			memcpy(&litho_b_pressure_pointssize, data, sizeof(int));data += sizeof(int);
			for(int j = 0; j < litho_b_pressure_pointssize; j++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_litho_b_pressure_points.push_back(temp);
			}
			memcpy(&m_Perm_Anisotr, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, LithoVariable &litho)
		{
			os << "\r\n>>>>>>>>>>>>>>>Litho Variable parameter as flow:";
			os << "\r\n---- ---- ---- lithology idx: " << litho.m_litho_idx;
			os << "\r\n---- ---- ---- lithology name: " << litho.m_litho_name;
			os << "\r\n---- ---- ---- lithology ratio: " << litho.m_litho_ratio;
			os << "\r\n---- ---- ---- is this matrix kerogen or coal: " << litho.m_litho_is_ThisMatrixKerogenOrCoal;
			os << "\r\n---- ---- ---- initial porosity: " << litho.m_litho_initial_porosity;
			os << "\r\n---- ---- ---- ever(chronic) bottom porosity: " << litho.m_litho_ever_bottom_porosity;
			os << "\r\n---- ---- ---- ever(chronic) middle porosity: " << litho.m_litho_ever_middle_porosity;
			os << "\r\n---- ---- ---- ever(chronic) top porosity: " << litho.m_litho_ever_top_porosity;
			os << "\r\n---- ---- ---- ever(chronic) permeability: " << litho.m_litho_ever_permeability;
			os << "\r\n---- ---- ---- ever(chronic) middle permeability: " << litho.m_litho_ever_middle_permeability;
			os << "\r\n---- ---- ---- compaction factor: " << litho.m_litho_initial_compaction_factor;
			os << "\r\n---- ---- ---- matrix density: " << litho.m_litho_matrix_density;
			os << "\r\n---- ---- ---- matrix thermal conduction: " << litho.m_litho_matrix_thermal_cond;
			os << "\r\n---- ---- ---- matrix thermal conduction ansiotropy coefficient: " << litho.m_litho_ThermalCondAnisotr;
			os << "\r\n---- ---- ---- matrix heat capacity: " << litho.m_litho_matrix_heat_capacity;
			os << "\r\n---- ---- ---- matrix radio active heat: " << litho.m_litho_matrix_radioactive_heat;
			os << "\r\n---- ---- ---- matrix porosity-permeability fomulae: " << litho.m_litho_poro_perm_formulare;
			os << "\r\n---- ---- ---- porosity-permeability points: ";
			for(int i = 0; i < litho.m_litho_poro_perm_points.size(); i++)
			{
				os << "\r\n---- ---- ---- (" << litho.m_litho_poro_perm_points[i].m_x << "," << litho.m_litho_poro_perm_points[i].m_y <<")";
			}
			os << "\r\n---- ---- ---- entry pressure points: ";
			for(int i = 0; i < litho.m_litho_a_pressure_points.size(); i++)
			{
				os << "\r\n---- ---- ---- pressure a is : (" << litho.m_litho_a_pressure_points[i].m_x << "," << litho.m_litho_a_pressure_points[i].m_y << ")";
				os << "\r\n---- ---- ---- pressure b is : (" << litho.m_litho_b_pressure_points[i].m_x << "," << litho.m_litho_b_pressure_points[i].m_y << ")";
			}
			return os;
		}
	};

	// TODO:
	// 
	struct CenterPhaseVariable
	{
		//
		double m_center_sw;
		double m_center_so;
		double m_center_sg;

		// ճ��
		double m_center_water_viscosity;
		double m_center_oil_viscosity;
		double m_center_gas_viscosity;

		// �����͸��
		double m_center_k_rw;
		double m_center_k_ro;
		double m_center_k_rg;

		//ճ�ȡ������͸�ʡ�����������ë��ѹ��
		double m_center_swc;
		double m_center_soc;
		double m_center_sgc; // ����ˮ���Ͷȡ������ͱ��Ͷ� �����������Ͷ�    ,��С����ʾ
		double m_center_swe; //effective saturations Se��Чˮ���Ͷ�for krw and krow,       ,��С����ʾ
		double m_center_soe; // ��Ч�ͱ��Ͷ� ,��ʱû������    ,��С����ʾ
		double m_center_sgoe; //����Krog����Ч���Ͷ�  ,��С����ʾ
		double m_center_sge; // ��Ч�����Ͷ�,����Krg   ,��С����ʾ
		double m_center_Krow;
		double m_center_Krog; //
		double m_center_lamuda;

		double m_aToEntryPr;
		double m_bToEntryPr;//��Ӧ��ͻ��ë��ѹ����ϵ��a��b,��Hantschel 2009 ,P411. Table A.6. Capillary Entry Pressure
		double m_PcbMA; // ͻ��ë��ѹ��,ˮ��-����
		double m_PcMA; //ë��ѹ����ˮ��-����
		double m_PcbOW;
		double m_PcbGW;
		double m_PcbGO; //�ֱ�Ϊ��ˮ����ˮ�����͵�ͻ��ë��ѹ��
		double m_PcOW;
		double m_PcGW;
		double m_PcGO; //�ֱ���ˮ����ˮ�����͵�ë��ѹ��

		double m_RouML;
		double m_RouMV; //�ֱ����ͺ�����Ħ���ܶȣ���λ��gmol/cm 3
		double m_Tc;
		double m_vc; //�ֱ�Ϊ��ϵ���ٽ��¶Ⱥ��ٽ�Ħ�����������Ħ��ƽ��ֵ��ȣ���λ�ֱ�ΪK��cm3/gmol
		double m_TcL;
		double m_TcV; //�ֱ��������������ٽ��¶ȣ���λ��K
		double m_PXigema; //known as the parachor  ,���ű���
		double m_IFTOilWater;
		double m_IFTGasWater;
		double m_IFTGasOil;//��ˮ����ˮ�����͵Ľ�������  interfacial tension (IFT) ����λ��mN/m

		//
		//
		CenterPhaseVariable()
		{
			//
			m_center_sw = 0.99998;
			m_center_so = 0.00001;
			m_center_sg = 0.00001;

			//
			m_center_water_viscosity = 1.;
			m_center_oil_viscosity = 1.;
			m_center_gas_viscosity = 1.;

			//
			m_center_k_rw = 0.;
			m_center_k_ro = 0.;
			m_center_k_rg = 0.;

			m_aToEntryPr = 13.43;//todo
			m_bToEntryPr = -0.053;//todo
		}
		CenterPhaseVariable(const CenterPhaseVariable &other)
		{
			*this = other;
		}
		const CenterPhaseVariable &operator=(const CenterPhaseVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_center_sw = other.m_center_sw;
			m_center_so = other.m_center_so;
			m_center_sg = other.m_center_sg;

			// ճ��
			m_center_water_viscosity = other.m_center_water_viscosity;
			m_center_oil_viscosity = other.m_center_oil_viscosity;
			m_center_gas_viscosity = other.m_center_gas_viscosity;

			// �����͸��
			m_center_k_rw = other.m_center_k_rw;
			m_center_k_ro = other.m_center_k_ro;
			m_center_k_rg = other.m_center_k_rg;

			//ճ�ȡ������͸�ʡ�����������ë��ѹ��
			m_center_swc = other.m_center_swc;
			m_center_soc = other.m_center_soc;
			m_center_sgc = other.m_center_sgc;
			m_center_swe = other.m_center_swe;
			m_center_soe = other.m_center_soe;
			m_center_sgoe = other.m_center_sgoe;
			m_center_sge = other.m_center_sge;
			m_center_Krow = other.m_center_Krow;
			m_center_Krog = other.m_center_Krog;
			m_center_lamuda = other.m_center_lamuda;
			m_aToEntryPr = other.m_aToEntryPr;
			m_bToEntryPr = other.m_bToEntryPr;
			m_PcbMA = other.m_PcbMA;
			m_PcMA = other.m_PcMA;
			m_PcbOW = other.m_PcbOW;
			m_PcbGW = other.m_PcbGW;
			m_PcbGO = other.m_PcbGO;
			m_PcOW = other.m_PcOW;
			m_PcGW = other.m_PcGW;
			m_PcGO = other.m_PcGO;
			m_RouML = other.m_RouML;
			m_RouMV = other.m_RouMV;
			m_Tc = other.m_Tc;
			m_vc = other.m_vc;
			m_TcL = other.m_TcL;
			m_TcV = other.m_TcV;
			m_PXigema = other.m_PXigema;
			m_IFTOilWater = other.m_IFTOilWater;
			m_IFTGasWater = other.m_IFTGasWater;
			m_IFTGasOil = other.m_IFTGasOil;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_center_sw;
			curSize += sizeof(double);//double m_center_so;
			curSize += sizeof(double);//double m_center_sg;
			curSize += sizeof(double);//double m_center_water_viscosity;
			curSize += sizeof(double);//double m_center_oil_viscosity;
			curSize += sizeof(double);//double m_center_gas_viscosity;
			curSize += sizeof(double);//double m_center_k_rw;
			curSize += sizeof(double);//double m_center_k_ro;
			curSize += sizeof(double);//double m_center_k_rg;
			curSize += sizeof(double);//double m_center_swc;
			curSize += sizeof(double);//double m_center_soc;
			curSize += sizeof(double);//double m_center_sgc;
			curSize += sizeof(double);//double m_center_swe;
			curSize += sizeof(double);//double m_center_soe;
			curSize += sizeof(double);//double m_center_sgoe;
			curSize += sizeof(double);//double m_center_sge;
			curSize += sizeof(double);//double m_center_Krow;
			curSize += sizeof(double);//double m_center_Krog;
			curSize += sizeof(double);//double m_center_lamuda;
			curSize += sizeof(double);//double m_aToEntryPr;
			curSize += sizeof(double);//double m_bToEntryPr;
			curSize += sizeof(double);//double m_PcbMA;
			curSize += sizeof(double);//double m_PcMA;
			curSize += sizeof(double);//double m_PcbOW;
			curSize += sizeof(double);//double m_PcbGW;
			curSize += sizeof(double);//double m_PcbGO;
			curSize += sizeof(double);//double m_PcOW;
			curSize += sizeof(double);//double m_PcGW;
			curSize += sizeof(double);//double m_PcGO;
			curSize += sizeof(double);//double m_RouML;
			curSize += sizeof(double);//double m_RouMV;
			curSize += sizeof(double);//double m_Tc;
			curSize += sizeof(double);//double m_vc;
			curSize += sizeof(double);//double m_TcL;
			curSize += sizeof(double);//double m_TcV;
			curSize += sizeof(double);//double m_PXigema;
			curSize += sizeof(double);//double m_IFTOilWater;
			curSize += sizeof(double);//double m_IFTGasWater;
			curSize += sizeof(double);//double m_IFTGasOil;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_center_sw, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_so, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_sg, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_water_viscosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_oil_viscosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_gas_viscosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_k_rw, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_k_ro, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_k_rg, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_swc, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_soc, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_sgc, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_swe, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_soe, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_sgoe, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_sge, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_Krow, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_Krog, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_lamuda, sizeof(double));data += sizeof(double);
			memcpy(data, &m_aToEntryPr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_bToEntryPr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcbMA, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcMA, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcbOW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcbGW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcbGO, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcOW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcGW, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PcGO, sizeof(double));data += sizeof(double);
			memcpy(data, &m_RouML, sizeof(double));data += sizeof(double);
			memcpy(data, &m_RouMV, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Tc, sizeof(double));data += sizeof(double);
			memcpy(data, &m_vc, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TcL, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TcV, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PXigema, sizeof(double));data += sizeof(double);
			memcpy(data, &m_IFTOilWater, sizeof(double));data += sizeof(double);
			memcpy(data, &m_IFTGasWater, sizeof(double));data += sizeof(double);
			memcpy(data, &m_IFTGasOil, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_center_sw, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_so, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_sg, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_water_viscosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_oil_viscosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_gas_viscosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_k_rw, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_k_ro, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_k_rg, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_swc, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_soc, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_sgc, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_swe, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_soe, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_sgoe, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_sge, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_Krow, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_Krog, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_lamuda, data, sizeof(double));data += sizeof(double);
			memcpy(&m_aToEntryPr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_bToEntryPr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcbMA, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcMA, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcbOW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcbGW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcbGO, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcOW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcGW, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PcGO, data, sizeof(double));data += sizeof(double);
			memcpy(&m_RouML, data, sizeof(double));data += sizeof(double);
			memcpy(&m_RouMV, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Tc, data, sizeof(double));data += sizeof(double);
			memcpy(&m_vc, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TcL, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TcV, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PXigema, data, sizeof(double));data += sizeof(double);
			memcpy(&m_IFTOilWater, data, sizeof(double));data += sizeof(double);
			memcpy(&m_IFTGasWater, data, sizeof(double));data += sizeof(double);
			memcpy(&m_IFTGasOil, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, CenterPhaseVariable &phase)
		{
			os << "\r\n>>>>>>>>>>>>>>>center phase variables as flow";
			os << "\r\n---- ---- ---- center_Sw:" << phase.m_center_sw;
			os << "\r\n---- ---- ---- center_So:" << phase.m_center_so;
			os << "\r\n---- ---- ---- center_Sg:" << phase.m_center_sg;
			os << "\r\n---- ---- ---- center_water_viscosity:" << phase.m_center_water_viscosity;
			os << "\r\n---- ---- ---- center_oil_viscosity:" << phase.m_center_oil_viscosity;
			os << "\r\n---- ---- ---- center_gas_viscosity:" << phase.m_center_gas_viscosity;
			os << "\r\n---- ---- ---- center_k_rw:" << phase.m_center_k_rw;
			os << "\r\n---- ---- ---- center_k_ro:" << phase.m_center_k_ro;
			os << "\r\n---- ---- ---- center_k_rg:" << phase.m_center_k_rg;
			os << "\r\n---- ---- ---- center_Swc:" << phase.m_center_swc;
			os << "\r\n---- ---- ---- center_Soc:" << phase.m_center_soc;
			os << "\r\n---- ---- ---- center_Sgc:" << phase.m_center_sgc;
			os << "\r\n---- ---- ---- center_Swe:" << phase.m_center_swe;
			os << "\r\n---- ---- ---- center_Soe:" << phase.m_center_soe;
			os << "\r\n---- ---- ---- center_Sgoe:" << phase.m_center_sgoe;
			os << "\r\n---- ---- ---- center_Sge:" << phase.m_center_sge;
			os << "\r\n---- ---- ---- center_Krow:" << phase.m_center_Krow;
			os << "\r\n---- ---- ---- center_Krog:" << phase.m_center_Krog;
			os << "\r\n---- ---- ---- center_lamuda:" << phase.m_center_lamuda;
			os << "\r\n---- ---- ---- aToEntryPr:" << phase.m_aToEntryPr;
			os << "\r\n---- ---- ---- bToEntryPr:" << phase.m_bToEntryPr;
			os << "\r\n---- ---- ---- PcbMA:" << phase.m_PcbMA;
			os << "\r\n---- ---- ---- PcMA:" << phase.m_PcMA;
			os << "\r\n---- ---- ---- PcbOW:" << phase.m_PcbOW;
			os << "\r\n---- ---- ---- PcbGW:" << phase.m_PcbGW;
			os << "\r\n---- ---- ---- PcbGO:" << phase.m_PcbGO;
			os << "\r\n---- ---- ---- PcOW:" << phase.m_PcOW;
			os << "\r\n---- ---- ---- PcGW:" << phase.m_PcGW;
			os << "\r\n---- ---- ---- PcGO:" << phase.m_PcGO;
			os << "\r\n---- ---- ---- RouML:" << phase.m_RouML;
			os << "\r\n---- ---- ---- RouMV:" << phase.m_RouMV;
			os << "\r\n---- ---- ---- Tc:" << phase.m_Tc;
			os << "\r\n---- ---- ---- vc:" << phase.m_vc;
			os << "\r\n---- ---- ---- TcL:" << phase.m_TcL;
			os << "\r\n---- ---- ---- TcV:" << phase.m_TcV;
			os << "\r\n---- ---- ---- PXigema:" << phase.m_PXigema;
			os << "\r\n---- ---- ---- IFTOilWater:" << phase.m_IFTOilWater;
			os << "\r\n---- ---- ---- IFTGasWater:" << phase.m_IFTGasWater;
			os << "\r\n---- ---- ---- IFTGasOil:" << phase.m_IFTGasOil;
			return os;
		}
	};

	// ���ࡢ���������Լ����������������������   ����ʼ��new added 20190429    ,��û�м��뵽ģ��֮��
	struct MassVariable
	{
		double m_LiquidMassBulk; //������Һ�ࣨ���ࣩ����
		double m_LiquidMassOil; //������Һ�ࣨ���ࣩ������ֵ�����
		double m_LiquidMassGas; //������Һ�ࣨ���ࣩ������ֵ�����
		double m_VaporMassBulk; //��������������
		double m_VaporMassOil; //����������������ֵ�����
		double m_VaporMassGas; //����������������ֵ�����

		double m_LiquidMassC1;
		double m_LiquidMassC2_C5;
		double m_LiquidMassC6_C14;
		double m_LiquidMassC15Plus; //������Һ�ࣨ���ࣩ�и���ֵ�����
		double m_VaporMassC1;
		double m_VaporMassC2_C5;
		double m_VaporMassC6_C14;
		double m_VaporMassC15Plus;  //�����������и���ֵ�����
		double m_VCell; //���������
		double m_ACell; //�����嶥�����
		MassVariable()
		{
			m_LiquidMassBulk = 0;
			m_LiquidMassOil = 0;
			m_LiquidMassGas = 0;
			m_VaporMassBulk = 0;
			m_VaporMassOil = 0;
			m_VaporMassGas = 0; 
			m_LiquidMassC1 = 0;
			m_LiquidMassC2_C5 = 0;
			m_LiquidMassC6_C14 = 0;
			m_LiquidMassC15Plus = 0;
			m_VaporMassC1 = 0;
			m_VaporMassC2_C5 = 0;
			m_VaporMassC6_C14 = 0;
			m_VaporMassC15Plus = 0;
			m_VCell = 0;
			m_ACell = 0;
		}
		MassVariable(const MassVariable &other)
		{
			*this = other;
		}
		const MassVariable &operator=(const MassVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_LiquidMassBulk = other.m_LiquidMassBulk; //������Һ�ࣨ���ࣩ����
			m_LiquidMassOil = other.m_LiquidMassOil; //������Һ�ࣨ���ࣩ������ֵ�����
			m_LiquidMassGas = other.m_LiquidMassGas; //������Һ�ࣨ���ࣩ������ֵ�����
			m_VaporMassBulk = other.m_VaporMassBulk; //��������������
			m_VaporMassOil = other.m_VaporMassOil; //����������������ֵ�����
			m_VaporMassGas = other.m_VaporMassGas; //����������������ֵ�����

			m_LiquidMassC1 = other.m_LiquidMassC1;
			m_LiquidMassC2_C5 = other.m_LiquidMassC2_C5;
			m_LiquidMassC6_C14 = other.m_LiquidMassC6_C14;
			m_LiquidMassC15Plus = other.m_LiquidMassC15Plus; //������Һ�ࣨ���ࣩ�и���ֵ�����
			m_VaporMassC1 = other.m_VaporMassC1;
			m_VaporMassC2_C5 = other.m_VaporMassC2_C5;
			m_VaporMassC6_C14 = other.m_VaporMassC6_C14;
			m_VaporMassC15Plus = other.m_VaporMassC15Plus;  //�����������и���ֵ�����
			m_VCell = other.m_VCell; //���������
			m_ACell = other.m_ACell; //�����嶥����� 
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_LiquidMassBulk;
			curSize += sizeof(double);//double m_LiquidMassOil;
			curSize += sizeof(double);//double m_LiquidMassGas;
			curSize += sizeof(double);//double m_VaporMassBulk;
			curSize += sizeof(double);//double m_VaporMassOil;
			curSize += sizeof(double);//double m_VaporMassGas; 
			curSize += sizeof(double);//double m_LiquidMassC1;
			curSize += sizeof(double);//double m_LiquidMassC2_C5;
			curSize += sizeof(double);//double m_LiquidMassC6_C14;
			curSize += sizeof(double);//double m_LiquidMassC15Plus;
			curSize += sizeof(double);//double m_VaporMassC1;
			curSize += sizeof(double);//double m_VaporMassC2_C5;
			curSize += sizeof(double);//double m_VaporMassC6_C14;
			curSize += sizeof(double);//double m_VaporMassC15Plus;
			curSize += sizeof(double);//double m_VCell;
			curSize += sizeof(double);//double m_ACell;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_LiquidMassBulk, sizeof(double));data += sizeof(double);
			memcpy(data, &m_LiquidMassOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_LiquidMassGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VaporMassBulk, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VaporMassOil, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VaporMassGas, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_LiquidMassC1, sizeof(double));data += sizeof(double);
			memcpy(data, &m_LiquidMassC2_C5, sizeof(double));data += sizeof(double);
			memcpy(data, &m_LiquidMassC6_C14, sizeof(double));data += sizeof(double);
			memcpy(data, &m_LiquidMassC15Plus, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VaporMassC1, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VaporMassC2_C5, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VaporMassC6_C14, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VaporMassC15Plus, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VCell, sizeof(double));data += sizeof(double);
			memcpy(data, &m_ACell, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_LiquidMassBulk, data, sizeof(double));data += sizeof(double);
			memcpy(&m_LiquidMassOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_LiquidMassGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VaporMassBulk, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VaporMassOil, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VaporMassGas, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_LiquidMassC1, data, sizeof(double));data += sizeof(double);
			memcpy(&m_LiquidMassC2_C5, data, sizeof(double));data += sizeof(double);
			memcpy(&m_LiquidMassC6_C14, data, sizeof(double));data += sizeof(double);
			memcpy(&m_LiquidMassC15Plus, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VaporMassC1, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VaporMassC2_C5, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VaporMassC6_C14, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VaporMassC15Plus, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VCell, data, sizeof(double));data += sizeof(double);
			memcpy(&m_ACell, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, MassVariable &mass)
		{
			os << "\r\n>>>>>>>>>>>>>>>mass variables as flow";
			os << "\r\n---- ---- ---- LiquidMassBulk:" << mass.m_LiquidMassBulk;
			os << "\r\n---- ---- ---- LiquidMassOil:" << mass.m_LiquidMassOil;
			os << "\r\n---- ---- ---- LiquidMassGas:" << mass.m_LiquidMassGas;
			os << "\r\n---- ---- ---- VaporMassBulk:" << mass.m_VaporMassBulk;
			os << "\r\n---- ---- ---- VaporMassOil:" << mass.m_VaporMassOil;
			os << "\r\n---- ---- ---- VaporMassGas:" << mass.m_VaporMassGas; 
			os << "\r\n---- ---- ---- LiquidMassC1:" << mass.m_LiquidMassC1;
			os << "\r\n---- ---- ---- LiquidMassC2_C5:" << mass.m_LiquidMassC2_C5;
			os << "\r\n---- ---- ---- LiquidMassC6_C14:" << mass.m_LiquidMassC6_C14;
			os << "\r\n---- ---- ---- LiquidMassC15Plus:" << mass.m_LiquidMassC15Plus;
			os << "\r\n---- ---- ---- VaporMassC1:" << mass.m_VaporMassC1;
			os << "\r\n---- ---- ---- VaporMassC2_C5:" << mass.m_VaporMassC2_C5;
			os << "\r\n---- ---- ---- VaporMassC6_C14:" << mass.m_VaporMassC6_C14;
			os << "\r\n---- ---- ---- VaporMassC15Plus:" << mass.m_VaporMassC15Plus;
			os << "\r\n---- ---- ---- VCell:" << mass.m_VCell;
			os << "\r\n---- ---- ---- ACell:" << mass.m_ACell;
			return os;
		}
		/*
		void GetLVMass() // �����������������������
		  {
			LiquidMassBulk=VCell*Porom*So*OilDensity;
			VaporMassBulk=VCell*Porom*Sg*GasDensity;
			switch(aPetroGenStyle)
			 {
			 case LLNL||Organo:     //������������ֵ������ֻ�Ƕ����ɵ��ͺ���������̬����
				LiquidMassOil=LiquidMassBulk*(x[1]*MW[1])/(x[0]*MW[0]+x[1]*MW[1]);
				LiquidMassGas=LiquidMassBulk*(x[0]*MW[0])/(x[0]*MW[0]+x[1]*MW[1]);
				VaporMassOil=VaporMassBulk*(y[1]*MW[1])/(y[0]*MW[0]+y[1]*MW[1]);
				VaporMassGas=VaporMassBulk*(y[0]*MW[0])/(y[0]*MW[0]+y[1]*MW[1]);
			 break;
			 case Behar4C:        //��������ֵ������
				LiquidMassOil=LiquidMassBulk*(x[2]*MW[2]+x[3]*MW[3])/(x[0]*MW[0]+x[1]*MW[1]+x[2]*MW[2]+x[3]*MW[3]);
				LiquidMassGas=LiquidMassBulk*(x[0]*MW[0]+x[1]*MW[1])/(x[0]*MW[0]+x[1]*MW[1]+x[2]*MW[2]+x[3]*MW[3]);
				VaporMassOil=VaporMassBulk*(y[2]*MW[2]+y[3]*MW[3])/(y[0]*MW[0]+y[1]*MW[1]+y[2]*MW[2]+y[3]*MW[3]);
				VaporMassGas=VaporMassBulk*(y[0]*MW[0]+y[1]*MW[1])/(y[0]*MW[0]+y[1]*MW[1]+y[2]*MW[2]+y[3]*MW[3]);

				LiquidMassC1=LiquidMassBulk*(x[0]*MW[0])/(x[0]*MW[0]+x[1]*MW[1]+x[2]*MW[2]+x[3]*MW[3]);
				LiquidMassC2_C5=LiquidMassBulk*(x[1]*MW[1])/(x[0]*MW[0]+x[1]*MW[1]+x[2]*MW[2]+x[3]*MW[3]);
				LiquidMassC6_C14=LiquidMassBulk*(x[2]*MW[2])/(x[0]*MW[0]+x[1]*MW[1]+x[2]*MW[2]+x[3]*MW[3]);
				LiquidMassC15Plus=LiquidMassBulk*(x[3]*MW[3])/(x[0]*MW[0]+x[1]*MW[1]+x[2]*MW[2]+x[3]*MW[3]);

				VaporMassC1=VaporMassBulk*(y[0]*MW[0])/(y[0]*MW[0]+y[1]*MW[1]+y[2]*MW[2]+y[3]*MW[3]);
				VaporMassC2_C5=VaporMassBulk*(y[1]*MW[1])/(y[0]*MW[0]+y[1]*MW[1]+y[2]*MW[2]+y[3]*MW[3]);
				VaporMassC6_C14=VaporMassBulk*(y[2]*MW[2])/(y[0]*MW[0]+y[1]*MW[1]+y[2]*MW[2]+y[3]*MW[3]);
				VaporMassC15Plus=VaporMassBulk*(y[3]*MW[3])/(y[0]*MW[0]+y[1]*MW[1]+y[2]*MW[2]+y[3]*MW[3]);
			 break;
			 };
		  }
			   */
	};

	/*!
	*
	**/
	struct PercolationVariable
	{
		double m_PosX;
		double m_PosY;
		double m_PosZ; //ÿһ���������ĵ��x��y��z���ꡣ ���½�����Ϊ0,0  ,˳��Ϊ���������¶�������������������������
		double m_VP;//�������϶���
		double m_VOil; //�����������͵����
		double m_VGas; //�����������������
		double m_Pw;//ˮѹ
		double m_Po; //����ѹ��
		double m_Pg; //����ѹ��
		double m_PHC; //����ϵͳѹ�����������������ۺ�ѹ����Ϊ����ѹ����Ȩ�غ� ���������������е�ѹ��
		bool m_OpenBoundary; //��Ǹ������Ƿ���п��ű߽磬tureΪ�п��ű߽磬falseΪ��ձ߽磬���ھ��ж���߽������ֻҪ��һ���߽��ǿ�������Ϊ���п��ű߽磬����յĲ�Ϊ��ձ߽�

		//���²�������������������ģ����ڴ���ĳһ�����������Ͷȴ��ڵ���1�����
		bool m_SogBiggerThan1; //���ڱ�Ǹ������������Ͷȴ���1��������������1����Ҫ�ֲ����������㺬�������Ͷ�С��1
		double m_C1InFluxMiniStep; //ÿһС����C1������
		double m_C2_C5InFluxMiniStep;  //ÿһС����C2_C5������
		double m_C6_C14InFluxMiniStep;   //ÿһС����C6_C14������
		double m_C15PlusInFluxMiniStep;   //ÿһС����C15Plus������
		double m_GasInFluxMiniStep;   //ÿһС������������
		double m_OilInFluxMiniStep;   //ÿһС������������

		double m_qInFluxLeft;  //ÿһС����ʣ����ܵ�������
		double m_C1InFluxLeft;    //ÿһС����ʣ���C1������
		double m_C2_C5InFluxLeft;  //ÿһС����ʣ���C2_C5������
		double m_C6_C14InFluxLeft;   //ÿһС����ʣ���C6_C14������
		double m_C15PlusInFluxLeft;    //ÿһС����ʣ���C15Plus������
		double m_GasInFluxLeft;   //ÿһС����ʣ�����������P
		double m_OilInFluxLeft;    //ÿһС����ʣ�����������

		double m_C1Last;  //��һ����ע���������C1��
		double m_C2_C5Last; //��һ����ע���������C2_C5��
		double m_C6_C14Last; //��һ����ע���������C6_C14��
		double m_C15PlusLast;  //��һ����ע���������C15Plus��
		double m_GasLast; //��һ����ע�������������
		double m_OilLast;  //��һ����ע���������Oil��
		double m_DeltaX;
		double m_DeltaY;
		double m_DeltaZ; //������ĳ����
		PercolationVariable()
		{
			m_VOil = 0;
			m_VGas = 0;
		}
		PercolationVariable(const PercolationVariable &other)
		{
			*this = other;
		}
		const PercolationVariable &operator=(const PercolationVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_PosX = other.m_PosX;
			m_PosY = other.m_PosY;
			m_PosZ = other.m_PosZ; //ÿһ���������ĵ��x��y��z���ꡣ ���½�����Ϊ0,0  ,˳��Ϊ���������¶�������������������������
			m_VP = other.m_VP;//�������϶���
			m_VOil = other.m_VOil; //�����������͵����
			m_VGas = other.m_VGas; //�����������������
			m_Pw = other.m_Pw;//ˮѹ
			m_Po = other.m_Po; //����ѹ��
			m_Pg = other.m_Pg; //����ѹ��
			m_PHC = other.m_PHC; //����ϵͳѹ�����������������ۺ�ѹ����Ϊ����ѹ����Ȩ�غ� ���������������е�ѹ��
			m_OpenBoundary = other.m_OpenBoundary; //��Ǹ������Ƿ���п��ű߽磬tureΪ�п��ű߽磬falseΪ��ձ߽磬���ھ��ж���߽������ֻҪ��һ���߽��ǿ�������Ϊ���п��ű߽磬����յĲ�Ϊ��ձ߽�
			m_SogBiggerThan1 = other.m_SogBiggerThan1; //���ڱ�Ǹ������������Ͷȴ���1��������������1����Ҫ�ֲ����������㺬�������Ͷ�С��1
			m_C1InFluxMiniStep = other.m_C1InFluxMiniStep; //ÿһС����C1������
			m_C2_C5InFluxMiniStep = other.m_C2_C5InFluxMiniStep;  //ÿһС����C2_C5������
			m_C6_C14InFluxMiniStep = other.m_C6_C14InFluxMiniStep;   //ÿһС����C6_C14������
			m_C15PlusInFluxMiniStep = other.m_C15PlusInFluxMiniStep;   //ÿһС����C15Plus������
			m_GasInFluxMiniStep = other.m_GasInFluxMiniStep;   //ÿһС������������
			m_OilInFluxMiniStep = other.m_OilInFluxMiniStep;   //ÿһС������������
			m_qInFluxLeft = other.m_qInFluxLeft;  //ÿһС����ʣ����ܵ�������
			m_C1InFluxLeft = other.m_C1InFluxLeft;    //ÿһС����ʣ���C1������
			m_C2_C5InFluxLeft = other.m_C2_C5InFluxLeft;  //ÿһС����ʣ���C2_C5������
			m_C6_C14InFluxLeft = other.m_C6_C14InFluxLeft;   //ÿһС����ʣ���C6_C14������
			m_C15PlusInFluxLeft = other.m_C15PlusInFluxLeft;    //ÿһС����ʣ���C15Plus������
			m_GasInFluxLeft = other.m_GasInFluxLeft;   //ÿһС����ʣ�����������P
			m_OilInFluxLeft = other.m_OilInFluxLeft;    //ÿһС����ʣ�����������
			m_C1Last = other.m_C1Last;  //��һ����ע���������C1��
			m_C2_C5Last = other.m_C2_C5Last; //��һ����ע���������C2_C5��
			m_C6_C14Last = other.m_C6_C14Last; //��һ����ע���������C6_C14��
			m_C15PlusLast = other.m_C15PlusLast;  //��һ����ע���������C15Plus��
			m_GasLast = other.m_GasLast; //��һ����ע�������������
			m_OilLast = other.m_OilLast;  //��һ����ע���������Oil��
			m_DeltaX = other.m_DeltaX;
			m_DeltaY = other.m_DeltaY;
			m_DeltaZ = other.m_DeltaZ;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_PosX;
			curSize += sizeof(double);//double m_PosY;
			curSize += sizeof(double);//double m_PosZ;
			curSize += sizeof(double);//double m_VP;
			curSize += sizeof(double);//double m_VOil; 
			curSize += sizeof(double);//double m_VGas;
			curSize += sizeof(double);//double m_Pw;
			curSize += sizeof(double);//double m_Po; 
			curSize += sizeof(double);//double m_Pg; 
			curSize += sizeof(double);//double m_PHC; 
			curSize += sizeof(bool);//bool m_OpenBoundary; 
			curSize += sizeof(bool);//bool m_SogBiggerThan1; 
			curSize += sizeof(double);//double m_C1InFluxMiniStep; 
			curSize += sizeof(double);//double m_C2_C5InFluxMiniStep;  
			curSize += sizeof(double);//double m_C6_C14InFluxMiniStep;  
			curSize += sizeof(double);//double m_C15PlusInFluxMiniStep; 
			curSize += sizeof(double);//double m_GasInFluxMiniStep; 
			curSize += sizeof(double);//double m_OilInFluxMiniStep;  
			curSize += sizeof(double);//double m_qInFluxLeft; 
			curSize += sizeof(double);//double m_C1InFluxLeft;   
			curSize += sizeof(double);//double m_C2_C5InFluxLeft;  
			curSize += sizeof(double);//double m_C6_C14InFluxLeft;  
			curSize += sizeof(double);//double m_C15PlusInFluxLeft;    
			curSize += sizeof(double);//double m_GasInFluxLeft;  
			curSize += sizeof(double);//double m_OilInFluxLeft;   
			curSize += sizeof(double);//double m_C1Last;  
			curSize += sizeof(double);//double m_C2_C5Last; 
			curSize += sizeof(double);//double m_C6_C14Last; 
			curSize += sizeof(double);//double m_C15PlusLast; 
			curSize += sizeof(double);//double m_GasLast;
			curSize += sizeof(double);//double m_OilLast;
			curSize += sizeof(double);//double m_DeltaX;
			curSize += sizeof(double);//double m_DeltaY;
			curSize += sizeof(double);//double m_DeltaZ;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_PosX, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PosY, sizeof(double));data += sizeof(double);
			memcpy(data, &m_PosZ, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VP, sizeof(double));data += sizeof(double);
			memcpy(data, &m_VOil, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_VGas, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Pw, sizeof(double));data += sizeof(double);
			memcpy(data, &m_Po, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_Pg, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_PHC, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_OpenBoundary, sizeof(bool));data += sizeof(bool); 
			memcpy(data, &m_SogBiggerThan1, sizeof(bool));data += sizeof(bool); 
			memcpy(data, &m_C1InFluxMiniStep, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C2_C5InFluxMiniStep, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_C6_C14InFluxMiniStep, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_C15PlusInFluxMiniStep, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasInFluxMiniStep, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_OilInFluxMiniStep, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_qInFluxLeft, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C1InFluxLeft, sizeof(double));data += sizeof(double);   
			memcpy(data, &m_C2_C5InFluxLeft, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_C6_C14InFluxLeft, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_C15PlusInFluxLeft, sizeof(double));data += sizeof(double);    
			memcpy(data, &m_GasInFluxLeft, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_OilInFluxLeft, sizeof(double));data += sizeof(double);   
			memcpy(data, &m_C1Last, sizeof(double));data += sizeof(double);  
			memcpy(data, &m_C2_C5Last, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C6_C14Last, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_C15PlusLast, sizeof(double));data += sizeof(double); 
			memcpy(data, &m_GasLast, sizeof(double));data += sizeof(double);
			memcpy(data, &m_OilLast, sizeof(double));data += sizeof(double);
			memcpy(data, &m_DeltaX, sizeof(double));data += sizeof(double);
			memcpy(data, &m_DeltaY, sizeof(double));data += sizeof(double);
			memcpy(data, &m_DeltaZ, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_PosX, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PosY, data, sizeof(double));data += sizeof(double);
			memcpy(&m_PosZ, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VP, data, sizeof(double));data += sizeof(double);
			memcpy(&m_VOil, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_VGas, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Pw, data, sizeof(double));data += sizeof(double);
			memcpy(&m_Po, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_Pg, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_PHC, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_OpenBoundary, data, sizeof(bool));data += sizeof(bool); 
			memcpy(&m_SogBiggerThan1, data, sizeof(bool));data += sizeof(bool); 
			memcpy(&m_C1InFluxMiniStep, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C2_C5InFluxMiniStep, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_C6_C14InFluxMiniStep, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_C15PlusInFluxMiniStep, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasInFluxMiniStep, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_OilInFluxMiniStep, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_qInFluxLeft, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C1InFluxLeft, data, sizeof(double));data += sizeof(double);   
			memcpy(&m_C2_C5InFluxLeft, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_C6_C14InFluxLeft, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_C15PlusInFluxLeft, data, sizeof(double));data += sizeof(double);    
			memcpy(&m_GasInFluxLeft, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_OilInFluxLeft, data, sizeof(double));data += sizeof(double);   
			memcpy(&m_C1Last, data, sizeof(double));data += sizeof(double);  
			memcpy(&m_C2_C5Last, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C6_C14Last, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_C15PlusLast, data, sizeof(double));data += sizeof(double); 
			memcpy(&m_GasLast, data, sizeof(double));data += sizeof(double);
			memcpy(&m_OilLast, data, sizeof(double));data += sizeof(double);
			memcpy(&m_DeltaX, data, sizeof(double));data += sizeof(double);
			memcpy(&m_DeltaY, data, sizeof(double));data += sizeof(double);
			memcpy(&m_DeltaZ, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, PercolationVariable &percolation)
		{
			os << "\r\n>>>>>>>>>>>>>>>PercolationVariable parameter as flow:";
			os << "\r\n---- ---- ---- PosX:" << percolation.m_PosX;
			os << "\r\n---- ---- ---- PosY:" << percolation.m_PosY;
			os << "\r\n---- ---- ---- PosZ:" << percolation.m_PosZ;
			os << "\r\n---- ---- ---- VP:" << percolation.m_VP;//�������϶���
			os << "\r\n---- ---- ---- VOil:" << percolation.m_VOil; //�����������͵����
			os << "\r\n---- ---- ---- VGas:" << percolation.m_VGas; //�����������������
			os << "\r\n---- ---- ---- Pw:" << percolation.m_Pw;//ˮѹ
			os << "\r\n---- ---- ---- Po:" << percolation.m_Po; //����ѹ��
			os << "\r\n---- ---- ---- Pg:" << percolation.m_Pg; //����ѹ��
			os << "\r\n---- ---- ---- PHC:" << percolation.m_PHC; //����ϵͳѹ�����������������ۺ�ѹ����Ϊ����ѹ����Ȩ�غ� ���������������е�ѹ��
			os << "\r\n---- ---- ---- OpenBoundary:" << percolation.m_OpenBoundary; //��Ǹ������Ƿ���п��ű߽磬tureΪ�п��ű߽磬falseΪ��ձ߽磬���ھ��ж���߽������ֻҪ��һ���߽��ǿ�������Ϊ���п��ű߽磬����յĲ�Ϊ��ձ߽�
			os << "\r\n---- ---- ---- SogBiggerThan1:" << percolation.m_SogBiggerThan1; //���ڱ�Ǹ������������Ͷȴ���1��������������1����Ҫ�ֲ����������㺬�������Ͷ�С��1
			os << "\r\n---- ---- ---- C1InFluxMiniStep:" << percolation.m_C1InFluxMiniStep; //ÿһС����C1������
			os << "\r\n---- ---- ---- C2_C5InFluxMiniStep:" << percolation.m_C2_C5InFluxMiniStep;  //ÿһС����C2_C5������
			os << "\r\n---- ---- ---- C6_C14InFluxMiniStep:" << percolation.m_C6_C14InFluxMiniStep;   //ÿһС����C6_C14������
			os << "\r\n---- ---- ---- C15PlusInFluxMiniStep:" << percolation.m_C15PlusInFluxMiniStep;   //ÿһС����C15Plus������
			os << "\r\n---- ---- ---- GasInFluxMiniStep:" << percolation.m_GasInFluxMiniStep;   //ÿһС������������
			os << "\r\n---- ---- ---- OilInFluxMiniStep:" << percolation.m_OilInFluxMiniStep;   //ÿһС������������
			os << "\r\n---- ---- ---- qInFluxLeft:" << percolation.m_qInFluxLeft;  //ÿһС����ʣ����ܵ�������
			os << "\r\n---- ---- ---- C1InFluxLeft:" << percolation.m_C1InFluxLeft;    //ÿһС����ʣ���C1������
			os << "\r\n---- ---- ---- C2_C5InFluxLeft:" << percolation.m_C2_C5InFluxLeft;  //ÿһС����ʣ���C2_C5������
			os << "\r\n---- ---- ---- C6_C14InFluxLeft:" << percolation.m_C6_C14InFluxLeft;   //ÿһС����ʣ���C6_C14������
			os << "\r\n---- ---- ---- C15PlusInFluxLeft:" << percolation.m_C15PlusInFluxLeft;    //ÿһС����ʣ���C15Plus������
			os << "\r\n---- ---- ---- GasInFluxLeft:" << percolation.m_GasInFluxLeft;   //ÿһС����ʣ�����������P
			os << "\r\n---- ---- ---- OilInFluxLeft:" << percolation.m_OilInFluxLeft;    //ÿһС����ʣ�����������
			os << "\r\n---- ---- ---- C1Last:" << percolation.m_C1Last;  //��һ����ע���������C1��
			os << "\r\n---- ---- ---- C2_C5Last:" << percolation.m_C2_C5Last; //��һ����ע���������C2_C5��
			os << "\r\n---- ---- ---- C6_C14Last:" << percolation.m_C6_C14Last; //��һ����ע���������C6_C14��
			os << "\r\n---- ---- ---- C15PlusLast:" << percolation.m_C15PlusLast;  //��һ����ע���������C15Plus��
			os << "\r\n---- ---- ---- GasLast:" << percolation.m_GasLast; //��һ����ע�������������
			os << "\r\n---- ---- ---- OilLast:" << percolation.m_OilLast;  //��һ����ע���������Oil��
			os << "\r\n---- ---- ---- DeltaX:" << percolation.m_DeltaX;
			os << "\r\n---- ---- ---- DeltaY:" << percolation.m_DeltaY;
			os << "\r\n---- ---- ---- DeltaZ:" << percolation.m_DeltaZ;
			return os;    
		}
	};

	// matrix data
	struct CenterMatrixVariable
	{
		// �����ܶȵ�λ��kg/m^3
		double m_center_matrix_density;
		// �����ȴ���
		double m_center_matrix_thermal_cond; //�ܵĻ����ȵ��ʣ���ֱ����
		double m_center_TMatrixThermalCondH; //�ܵĻ����ȵ��ʣ�ˮƽ����
		// ���ݵĵ�λ��J/(kg��);�õ���������ƽ��ֵ
		double m_center_matrix_heat_capacity;

		//
		CenterMatrixVariable()
		{
			m_center_matrix_density = 0;
			m_center_matrix_thermal_cond = 0;
			m_center_TMatrixThermalCondH = 0;
			m_center_matrix_heat_capacity = 0;
		}
		CenterMatrixVariable(const CenterMatrixVariable &other)
		{
			*this = other;
		}
		const CenterMatrixVariable &operator=(const CenterMatrixVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_center_matrix_density = other.m_center_matrix_density;
			m_center_matrix_thermal_cond = other.m_center_matrix_thermal_cond;
			m_center_TMatrixThermalCondH = other.m_center_TMatrixThermalCondH;
			m_center_matrix_heat_capacity = other.m_center_matrix_heat_capacity;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_center_matrix_density;
			curSize += sizeof(double);//double m_center_matrix_thermal_cond;
			curSize += sizeof(double);//double m_center_TMatrixThermalCondH;
			curSize += sizeof(double);//double m_center_matrix_heat_capacity;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_center_matrix_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_matrix_thermal_cond, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_TMatrixThermalCondH, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_matrix_heat_capacity, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_center_matrix_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_matrix_thermal_cond, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_TMatrixThermalCondH, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_matrix_heat_capacity, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, CenterMatrixVariable &matrix)
		{
			os << "\r\n>>>>>>>>>>>>>>>center matrix variables as flow";
			os << "\r\n---- ---- ---- matrix density:" << matrix.m_center_matrix_density;
			os << "\r\n---- ---- ---- matrix thermal conduction:" << matrix.m_center_matrix_thermal_cond;
			os << "\r\n---- ---- ---- matrix horizontal thermal conduction:" << matrix.m_center_TMatrixThermalCondH;
			os << "\r\n---- ---- ---- matrix heat capacity:" << matrix.m_center_matrix_heat_capacity;
			return os;
		}
	};

	// capacity variable
	struct CenterPoreFluidVariable
	{
		double m_center_total_heat_capacity;
		double m_center_fluid_heat_capacity;
		
		double m_center_water_heat_capacity;
		double m_center_oil_heat_capacity;
		double m_center_gas_heat_capacity;

		double m_center_ice_heat_capacity;
		double m_center_gas_hydrate_heat_capacity;

		// compound
		double m_center_pore_thermal_cond;
		double m_center_total_thermal_cond; //�ܵ��ȵ���  ���������ʺͿ�϶���壩
		double m_TotalThermalCondH;//ˮƽ�����ܵ��ȵ���
		double m_TThermalCondAnisotr; //�ܵ��ȵ��ʸ�������ϵ��

		// independent
		double m_center_water_thermal_cond;
		double m_center_oil_thermal_cond;
		double m_center_gas_thermal_cond;

		//
		CenterPoreFluidVariable() 
		{
			m_center_total_heat_capacity = 0;
			m_center_fluid_heat_capacity = 0;
			m_center_water_heat_capacity = 0;
			m_center_oil_heat_capacity = 0;
			m_center_gas_heat_capacity = 0;
			m_center_ice_heat_capacity = 0;
			m_center_gas_hydrate_heat_capacity = 0;
			m_center_pore_thermal_cond = 0;
			m_center_total_thermal_cond = 0;
			m_TotalThermalCondH = 0;
			m_TThermalCondAnisotr = 0;
			m_center_water_thermal_cond = 0;
			m_center_oil_thermal_cond = 0;
			m_center_gas_thermal_cond = 0;
		}
		CenterPoreFluidVariable(const CenterPoreFluidVariable &other)
		{
			*this = other;
		}
		const CenterPoreFluidVariable &operator=(const CenterPoreFluidVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_center_total_heat_capacity = other.m_center_total_heat_capacity;
			m_center_fluid_heat_capacity = other.m_center_fluid_heat_capacity;
			m_center_water_heat_capacity = other.m_center_water_heat_capacity;
			m_center_oil_heat_capacity = other.m_center_oil_heat_capacity;
			m_center_gas_heat_capacity = other.m_center_gas_heat_capacity;

			m_center_ice_heat_capacity = other.m_center_ice_heat_capacity;
			m_center_gas_hydrate_heat_capacity = other.m_center_gas_hydrate_heat_capacity;

			m_center_pore_thermal_cond = other.m_center_pore_thermal_cond;
			m_center_total_thermal_cond = other.m_center_total_thermal_cond;
			m_TotalThermalCondH = other.m_TotalThermalCondH;
			m_TThermalCondAnisotr = other.m_TThermalCondAnisotr;

			m_center_water_thermal_cond = other.m_center_water_thermal_cond;
			m_center_oil_thermal_cond = other.m_center_oil_thermal_cond;
			m_center_gas_thermal_cond = other.m_center_gas_thermal_cond;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_center_total_heat_capacity;
			curSize += sizeof(double);//double m_center_fluid_heat_capacity;
			curSize += sizeof(double);//double m_center_water_heat_capacity;
			curSize += sizeof(double);//double m_center_oil_heat_capacity;
			curSize += sizeof(double);//double m_center_gas_heat_capacity;
			curSize += sizeof(double);//double m_center_ice_heat_capacity;
			curSize += sizeof(double);//double m_center_gas_hydrate_heat_capacity;
			curSize += sizeof(double);//double m_center_pore_thermal_cond;
			curSize += sizeof(double);//double m_center_total_thermal_cond;
			curSize += sizeof(double);//double m_TotalThermalCondH;
			curSize += sizeof(double);//double m_TThermalCondAnisotr;
			curSize += sizeof(double);//double m_center_water_thermal_cond;
			curSize += sizeof(double);//double m_center_oil_thermal_cond;
			curSize += sizeof(double);//double m_center_gas_thermal_cond;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_center_total_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_fluid_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_water_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_oil_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_gas_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_ice_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_gas_hydrate_heat_capacity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_pore_thermal_cond, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_total_thermal_cond, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TotalThermalCondH, sizeof(double));data += sizeof(double);
			memcpy(data, &m_TThermalCondAnisotr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_water_thermal_cond, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_oil_thermal_cond, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_gas_thermal_cond, sizeof(double));data += sizeof(double);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_center_total_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_fluid_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_water_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_oil_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_gas_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_ice_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_gas_hydrate_heat_capacity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_pore_thermal_cond, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_total_thermal_cond, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TotalThermalCondH, data, sizeof(double));data += sizeof(double);
			memcpy(&m_TThermalCondAnisotr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_water_thermal_cond, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_oil_thermal_cond, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_gas_thermal_cond, data, sizeof(double));data += sizeof(double);
		}
		friend std::ofstream &operator << (std::ofstream &os, CenterPoreFluidVariable &porefluid)
		{
			os << "\r\n>>>>>>>>>>>>>>>pore fluid parameter as flow:";
			os << "\r\n---- ---- ---- total heat capacity:" << porefluid.m_center_total_heat_capacity;
			os << "\r\n---- ---- ---- fluid heat capacity:" << porefluid.m_center_fluid_heat_capacity;
			os << "\r\n---- ---- ---- water heat capacity:" << porefluid.m_center_water_heat_capacity;
			os << "\r\n---- ---- ---- oil heat capacity:" << porefluid.m_center_oil_heat_capacity;
			os << "\r\n---- ---- ---- gas heat capacity:" << porefluid.m_center_gas_heat_capacity;
			os << "\r\n---- ---- ---- ice heat capacity:" << porefluid.m_center_ice_heat_capacity;
			os << "\r\n---- ---- ---- hydrate gas heat capacity:" << porefluid.m_center_gas_hydrate_heat_capacity;
			os << "\r\n---- ---- ---- pore thermal conduction:" << porefluid.m_center_pore_thermal_cond;
			os << "\r\n---- ---- ---- total thermal conduction:" << porefluid.m_center_total_thermal_cond;
			os << "\r\n---- ---- ---- total thermal conduction along horizon:" << porefluid.m_TotalThermalCondH;
			os << "\r\n---- ---- ---- total thermal conduction anisotropy coefficient:" << porefluid.m_TThermalCondAnisotr;
			os << "\r\n---- ---- ---- water thermal conduction:" << porefluid.m_center_water_thermal_cond;
			os << "\r\n---- ---- ---- oil thermal conduction:" << porefluid.m_center_oil_thermal_cond;
			os << "\r\n---- ---- ---- gas thermal conduction:" << porefluid.m_center_gas_thermal_cond;
			return os;
		}
	};

	/*!
	*
	**/
	struct FiniteElementVariable
	{
		// for finite element
		double m_volume;
		std::vector<double> m_subtetravolumes;

		FiniteElementVariable()
		{
			m_volume = 0;
			m_subtetravolumes.resize(6, 0);
		}
		FiniteElementVariable(const FiniteElementVariable &other)
		{
			*this = other;
		}
		const FiniteElementVariable &operator=(const FiniteElementVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}

			m_volume = other.m_volume;
			m_subtetravolumes = other.m_subtetravolumes;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(double);//double m_volume;
			curSize += (sizeof(int) + m_subtetravolumes.size() * sizeof(double));//std::vector<double> m_subtetravolumes;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_volume, sizeof(double));data += sizeof(double);
			int subtetravolumesize = m_subtetravolumes.size();
			memcpy(data, &subtetravolumesize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < subtetravolumesize; i++)
			{
				memcpy(data, &(m_subtetravolumes[i]), sizeof(double));data += sizeof(double);
			}
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_volume, data, sizeof(double));data += sizeof(double);
			m_subtetravolumes.clear();
			int subtetravolumesize;
			memcpy(&subtetravolumesize, data, sizeof(int));data += sizeof(int);
			for(int i = 0; i < subtetravolumesize; i++)
			{
				double temp;
				memcpy(&temp, data, sizeof(double));data += sizeof(double);
				m_subtetravolumes.push_back(temp);
			}
		}
		friend std::ofstream &operator << (std::ofstream &os, FiniteElementVariable &finiteelement)
		{
			os << "\r\n>>>>>>>>>>>>>>>finite element parameter as flow:";
			os << "\r\n---- ---- ---- volume:" << finiteelement.m_volume;
			os << "\r\n---- ---- ---- subtetravolumes: ";
			for(int i = 0; i < finiteelement.m_subtetravolumes.size(); i++)os << "\r\n---- ---- ---- subtetravolumes " << i << ":" << finiteelement.m_subtetravolumes[i];
			return os;
		}
	};

	/*!
	*
	**/
	struct SourceRockVariable
	{
		bool m_is_source_rock;

		int m_aOrganoFaciesStyle;

		SourceRockVariable()
		{
			m_is_source_rock = true;
			m_aOrganoFaciesStyle = B;
		}
		SourceRockVariable(const SourceRockVariable &other)
		{
			*this = other;
		}
		const SourceRockVariable &operator=(const SourceRockVariable &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_is_source_rock = other.m_is_source_rock;
			m_aOrganoFaciesStyle = other.m_aOrganoFaciesStyle;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(bool);//bool m_is_source_rock;
			curSize += sizeof(int);//int m_aOrganoFaciesStyle;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_is_source_rock, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_aOrganoFaciesStyle, sizeof(int));data += sizeof(int);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_is_source_rock, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_aOrganoFaciesStyle, data, sizeof(int));data += sizeof(int);
		}
		friend std::ofstream &operator << (std::ofstream &os, SourceRockVariable &sourcerock)
		{
			os << "\r\n>>>>>>>>>>>>>>>source rock parameter as flow:";
			os << "\r\n---- ---- ---- is_source_rock:" << sourcerock.m_is_source_rock;
			os << "\r\n---- ---- ---- aOrganoFaciesStyle:" << sourcerock.m_aOrganoFaciesStyle;
			return os;
		}
	};
	/*!
	*
	**/
	struct FaceDefinition
	{
		//basic information
		long m_idx;
		std::string m_name;
		int m_color;
		// Litho variable
		std::string m_lith_name;
		int m_lithovariablenum;
		std::vector<LithoVariable> m_lithovariables;
		//TOC
		double m_toc;//all same	value
		//TOC contour	
		std::string m_itemname_toc;
		std::string m_viewname_toc;
		int m_interpolatetype_toc;
		int m_tocrows;
		int m_toccols;
		std::vector<CGeoPoint<double> > m_tocs;//different TOC against each grid
		//HI0
		double m_HI0;//all same value
		//HIO contour		
		std::string m_itemname_HI0;
		std::string m_viewname_HI0;
		int m_interpolatetype_HI0;
		int m_HI0rows;
		int m_HI0cols;
		std::vector<CGeoPoint<double> > m_HI0s;//different HI0 against each grid
		//all same LLNLKinetics
		std::string m_kinetic_name;
		LLNLKinetics m_kinetics;
		FaceDefinition()
		{
			m_idx = 0;
			m_name = "";
			m_color = 0;
			m_lith_name = "";
			m_lithovariablenum = 0;
			m_lithovariables.clear();
			m_toc = 0.;
			m_tocrows = 0;
			m_toccols = 0;
			m_tocs.clear();
			m_itemname_toc = "";
			m_viewname_toc = "";
			m_interpolatetype_toc = 0;
			m_HI0 = 0.;
			m_HI0rows = 0;
			m_HI0cols = 0;
			m_HI0s.clear();
			m_itemname_HI0 = "";
			m_viewname_HI0 = "";
			m_interpolatetype_HI0 = 0;
			m_kinetic_name = "";
		}
		FaceDefinition(const FaceDefinition &other)
		{
			*this = other;
		}
		const FaceDefinition &operator=(const FaceDefinition &other)
		{
			if(this == &other)
			{
				return *this;
			}
			m_idx = other.m_idx;
			m_name = other.m_name;
			m_color = other.m_color;
			m_lith_name = other.m_lith_name;
			m_lithovariables = other.m_lithovariables;
			m_lithovariablenum = other.m_lithovariablenum;
			m_toc = other.m_toc;
			m_tocrows = other.m_tocrows;
			m_toccols = other.m_toccols;
			m_tocs = other.m_tocs;
			m_itemname_toc = other.m_itemname_toc;
			m_viewname_toc = other.m_viewname_toc;
			m_interpolatetype_toc = other.m_interpolatetype_toc;
			m_HI0 = other.m_HI0;
			m_HI0rows = other.m_HI0rows;
			m_HI0cols = other.m_HI0cols;
			m_HI0s = other.m_HI0s;
			m_itemname_HI0 = other.m_itemname_HI0;
			m_viewname_HI0 = other.m_viewname_HI0;
			m_interpolatetype_HI0 = other.m_interpolatetype_HI0;
			m_kinetic_name = other.m_kinetic_name;
			m_kinetics = other.m_kinetics;
			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(long);//long m_idx;
			curSize += (sizeof(int) + m_name.length() * sizeof(char));//std::string m_name;
			curSize += sizeof(int);//int m_color;
			curSize += (sizeof(int) + m_lith_name.length() * sizeof(char));//std::string m_lith_name;
			curSize += sizeof(int);//int m_lithovariablenum;
			curSize += sizeof(int);//std::vector<LithoVariable> m_lithovariables;
			for(int i = 0; i < m_lithovariables.size(); i++)
			{
				curSize += m_lithovariables[i].GetSerializeDataLength();
			}
			curSize += sizeof(double);//double m_toc;	
			curSize += (sizeof(int) + m_itemname_toc.length() * sizeof(char));//std::string m_itemname_toc;
			curSize += (sizeof(int) + m_viewname_toc.length() * sizeof(char));//std::string m_viewname_toc;
			curSize += sizeof(int);//int m_interpolatetype_toc;
			curSize += sizeof(int);//int m_tocrows;
			curSize += sizeof(int);//int m_toccols;
			curSize += (sizeof(int) + m_tocs.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_tocs;
			curSize += sizeof(double);//double m_HI0;		
			curSize += (sizeof(int) + m_itemname_HI0.length() * sizeof(char));//std::string m_itemname_HI0;
			curSize += (sizeof(int) + m_viewname_HI0.length() * sizeof(char));//std::string m_viewname_HI0;
			curSize += sizeof(int);//int m_interpolatetype_HI0;
			curSize += sizeof(int);//int m_HI0rows;
			curSize += sizeof(int);//int m_HI0cols;
			curSize += (sizeof(int) + m_HI0s.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_HI0s;
			curSize += (sizeof(int) + m_kinetic_name.length() * sizeof(char));//std::string m_kinetic_name;
			curSize += m_kinetics.GetSerializeDataLength();//LLNLKinetics m_kinetics;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_idx, sizeof(long));data += sizeof(long);
			int namelength = m_name.length();
			memcpy(data, &namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_name.length(); i++)
			{
				memcpy(data, &(m_name[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_color, sizeof(int));data += sizeof(int);
			int lith_namelength = m_lith_name.length();
			memcpy(data, &lith_namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_lith_name.length(); i++)
			{
				memcpy(data, &(m_lith_name[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_lithovariablenum, sizeof(int));data += sizeof(int);
			int lithovariablessize = m_lithovariables.size();
			memcpy(data, &lithovariablessize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < lithovariablessize; i++)
			{
				m_lithovariables[i].SerializeData(data);
			}
			memcpy(data, &m_toc, sizeof(double));data += sizeof(double);
			int itemname_toclength = m_itemname_toc.length();
			memcpy(data, &itemname_toclength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_itemname_toc.length(); i++)
			{
				memcpy(data, &(m_itemname_toc[i]), sizeof(char));data += sizeof(char);
			}
			int viewname_toclength = m_viewname_toc.length();
			memcpy(data, &viewname_toclength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_viewname_toc.length(); i++)
			{
				memcpy(data, &(m_viewname_toc[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_interpolatetype_toc, sizeof(int));data += sizeof(int);
			memcpy(data, &m_tocrows, sizeof(int));data += sizeof(int);
			memcpy(data, &m_toccols, sizeof(int));data += sizeof(int);
			int tocssize = m_tocs.size();
			memcpy(data, &tocssize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < tocssize; i++)
			{
				memcpy(data, &(m_tocs[i]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
			memcpy(data, &m_HI0, sizeof(double));data += sizeof(double);
			int itemname_HI0length = m_itemname_HI0.length();
			memcpy(data, &itemname_HI0length, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_itemname_HI0.length(); i++)
			{
				memcpy(data, &(m_itemname_HI0[i]), sizeof(char));data += sizeof(char);
			}
			int viewname_HI0length = m_viewname_HI0.length();
			memcpy(data, &viewname_HI0length, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_viewname_HI0.length(); i++)
			{
				memcpy(data, &(m_viewname_HI0[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_interpolatetype_HI0, sizeof(int));data += sizeof(int);
			memcpy(data, &m_HI0rows, sizeof(int));data += sizeof(int);
			memcpy(data, &m_HI0cols, sizeof(int));data += sizeof(int);
			int HI0ssize = m_HI0s.size();
			memcpy(data, &HI0ssize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < HI0ssize; i++)
			{
				memcpy(data, &(m_HI0s[i]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
			int kinetic_namelength = m_kinetic_name.length();
			memcpy(data, &kinetic_namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_kinetic_name.length(); i++)
			{
				memcpy(data, &(m_kinetic_name[i]), sizeof(char));data += sizeof(char);
			}
			m_kinetics.SerializeData(data);
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_idx, data, sizeof(long));data += sizeof(long);
			int namelength;
			memcpy(&namelength, data, sizeof(int));data += sizeof(int);
			m_name = "";
			for(int i = 0; i < namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_name += temp;
			}
			memcpy(&m_color, data, sizeof(int));data += sizeof(int);
			int lith_namelength;
			memcpy(&lith_namelength, data, sizeof(int));data += sizeof(int);
			m_lith_name = "";
			for(int i = 0; i < lith_namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_lith_name += temp;
			}
			memcpy(&m_lithovariablenum, data, sizeof(int));data += sizeof(int);
			m_lithovariables.clear();
			int lithovariablessize;
			memcpy(&lithovariablessize, data, sizeof(int));data += sizeof(int);
			m_lithovariables.resize(lithovariablessize);
			for(int i = 0; i < lithovariablessize; i++)
			{
				m_lithovariables[i].RestoreSerializeData(data);
			}
			memcpy(&m_toc, data, sizeof(double));data += sizeof(double);
			int itemname_toclength;
			memcpy(&itemname_toclength, data, sizeof(int));data += sizeof(int);
			m_itemname_toc = "";
			for(int i = 0; i < itemname_toclength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_itemname_toc += temp;
			}
			int viewname_toclength;
			memcpy(&viewname_toclength, data, sizeof(int));data += sizeof(int);
			m_viewname_toc = "";
			for(int i = 0; i < viewname_toclength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_viewname_toc += temp;
			}
			memcpy(&m_interpolatetype_toc, data, sizeof(int));data += sizeof(int);
			memcpy(&m_tocrows, data, sizeof(int));data += sizeof(int);
			memcpy(&m_toccols, data, sizeof(int));data += sizeof(int);
			m_tocs.clear();
			int tocssize;
			memcpy(&tocssize, data, sizeof(int));data += sizeof(int);
			for(int i = 0; i < tocssize; i++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_tocs.push_back(temp);
			}
			memcpy(&m_HI0, data, sizeof(double));data += sizeof(double);
			int itemname_HI0length;
			memcpy(&itemname_HI0length, data, sizeof(int));data += sizeof(int);
			m_itemname_HI0 = "";
			for(int i = 0; i < itemname_HI0length; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_itemname_HI0 += temp;
			}
			int viewname_HI0length;
			memcpy(&viewname_HI0length, data, sizeof(int));data += sizeof(int);
			m_viewname_HI0 = "";
			for(int i = 0; i < viewname_HI0length; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_viewname_HI0 += temp;
			}
			memcpy(&m_interpolatetype_HI0, data, sizeof(int));data += sizeof(int);
			memcpy(&m_HI0rows, data, sizeof(int));data += sizeof(int);
			memcpy(&m_HI0cols, data, sizeof(int));data += sizeof(int);
			m_HI0s.clear();
			int HI0ssize;
			memcpy(&HI0ssize, data, sizeof(int));data += sizeof(int);
			for(int i = 0; i < HI0ssize; i++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_HI0s.push_back(temp);
			} 
			int kinetic_namelength;
			memcpy(&kinetic_namelength, data, sizeof(int));data += sizeof(int);
			m_kinetic_name = "";
			for(int i = 0; i < kinetic_namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_kinetic_name += temp;
			}
			m_kinetics.RestoreSerializeData(data);
		}
		double Interpolate_toc(VertexSimulated *curvertex)
		{
			CGeoPoint<double> &pt0 = m_tocs[0];
			CGeoPoint<double> &pt1 = m_tocs[m_toccols - 1];
			CGeoPoint<double> &pt2 = m_tocs[(m_tocrows - 1) * m_toccols];
			CGeoPoint<double> vectora(pt1.m_x - pt0.m_x, pt1.m_y - pt0.m_y);
			CGeoPoint<double> vectorb(pt2.m_x - pt0.m_x, pt2.m_y - pt0.m_y);
			CGeoPoint<double> vectorc(curvertex->m_x - pt0.m_x, curvertex->m_y - pt0.m_y);
			double m = (vectorc.m_x * vectorb.m_y - vectorc.m_y * vectorb.m_x) / (vectora.m_x * vectorb.m_y - vectora.m_y * vectorb.m_x);
			double n = (vectorc.m_x * vectora.m_y - vectorc.m_y * vectora.m_x) / (vectora.m_y * vectorb.m_x - vectora.m_x * vectorb.m_y);
			int row = n * (m_tocrows - 1) + 0.5;
			int col = m * (m_toccols - 1) + 0.5;
			if(row < 0)
				row = 0;
			if(col < 0)
				col = 0;
			if(row > m_tocrows - 1)
				row = m_tocrows - 1;
			if(col > m_toccols - 1)
				col = m_toccols - 1;
			return m_tocs[row * m_toccols + col].m_z;
		}
		double Interpolate_HI0(VertexSimulated *curvertex)
		{
			CGeoPoint<double> &pt0 = m_HI0s[0];
			CGeoPoint<double> &pt1 = m_HI0s[m_HI0cols - 1];
			CGeoPoint<double> &pt2 = m_HI0s[(m_HI0rows - 1) * m_HI0cols];
			CGeoPoint<double> vectora(pt1.m_x - pt0.m_x, pt1.m_y - pt0.m_y);
			CGeoPoint<double> vectorb(pt2.m_x - pt0.m_x, pt2.m_y - pt0.m_y);
			CGeoPoint<double> vectorc(curvertex->m_x - pt0.m_x, curvertex->m_y - pt0.m_y);
			double m = (vectorc.m_x * vectorb.m_y - vectorc.m_y * vectorb.m_x) / (vectora.m_x * vectorb.m_y - vectora.m_y * vectorb.m_x);
			double n = (vectorc.m_x * vectora.m_y - vectorc.m_y * vectora.m_x) / (vectora.m_y * vectorb.m_x - vectora.m_x * vectorb.m_y);
			int row = n * (m_HI0rows - 1) + 0.5;
			int col = m * (m_HI0cols - 1) + 0.5;
			if(row < 0)
				row = 0;
			if(col < 0)
				col = 0;
			if(row > m_HI0rows - 1)
				row = m_HI0rows - 1;
			if(col > m_HI0cols - 1)
				col = m_HI0cols - 1;
			return m_HI0s[row * m_HI0cols + col].m_z;
		}
	};
	typedef std::vector<FaceDefinition> FaceDefinitions;

	// border condition
	enum BorderConditionType
	{
		BCT_Unknown,
		BCT_Paleo_Water_Depth,
		BCT_Paleo_Surface_Temperature,
		BCT_Paleo_Heat_Fluid,
		BCT_Max
	};
	struct WaterDepthDefinition
	{
		//basic information
		long m_idx;
		long m_model_idx;
		std::string m_name;

		// Water Depth variable
		double m_age_from;
		std::string m_reference;

		//layer
		std::string m_itemname_layer;
		std::string m_viewname_layer;
		int m_interpolatetype_layer;
		std::vector<double> m_layer_values;

		//model
		std::string m_mode;
		double m_depth;

		//depth map
		std::string m_itemname_depth;
		std::string m_viewname_depth;
		int m_interpolatetype_depth;
		int m_rows;
		int m_cols;
		std::vector<CGeoPoint<double> > m_depth_values;

		WaterDepthDefinition()
		{
			//basic information
			m_idx = 0;
			m_model_idx = 0;
			m_name = "";

			// Water Depth variable
			m_age_from = 0.;
			m_reference = "";

			//layer
			m_itemname_layer = "";
			m_viewname_layer = "";
			m_interpolatetype_layer = 0;
			m_layer_values.clear();

			//model
			m_mode = "";
			m_depth = 0.;

			//depth map
			m_itemname_depth = "";
			m_viewname_depth = "";
			m_interpolatetype_depth = 0;
			m_rows = 0;
			m_cols = 0;
			m_depth_values.clear();
		}

		WaterDepthDefinition(const WaterDepthDefinition &other)
		{
			*this = other;
		}

		const WaterDepthDefinition &operator=(const WaterDepthDefinition &other)
		{
			if(this == &other)
			{
				return *this;
			}
			//basic information
			m_idx = other.m_idx;
			m_model_idx = other.m_model_idx;
			m_name = other.m_name;

			// Water Depth variable
			m_age_from = other.m_age_from;
			m_reference = other.m_reference;

			//layer
			m_itemname_layer = other.m_itemname_layer;
			m_viewname_layer = other.m_viewname_layer;
			m_interpolatetype_layer = other.m_interpolatetype_layer;
			m_layer_values = other.m_layer_values;

			//model
			m_mode = other.m_mode;
			m_depth = other.m_depth;

			//depth map
			m_itemname_depth = other.m_itemname_depth;
			m_viewname_depth = other.m_viewname_depth;
			m_interpolatetype_depth = other.m_interpolatetype_depth;
			m_rows = other.m_rows;
			m_cols = other.m_cols;
			m_depth_values = other.m_depth_values;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(long);//long m_idx;
			curSize += sizeof(long);//long m_model_idx;
			curSize += (sizeof(int) + m_name.length() * sizeof(char));//std::string m_name;
			curSize += sizeof(double);//double m_age_from;
			curSize += (sizeof(int) + m_reference.length() * sizeof(char));//std::string m_reference;
			curSize += (sizeof(int) + m_itemname_layer.length() * sizeof(char));//std::string m_itemname_layer;
			curSize += (sizeof(int) + m_viewname_layer.length() * sizeof(char));//std::string m_viewname_layer;
			curSize += sizeof(int);//int m_interpolatetype_layer;
			curSize += (sizeof(int) + m_layer_values.size() * sizeof(double));//std::vector<double> m_layer_values;
			curSize += (sizeof(int) + m_mode.length() * sizeof(char));//std::string m_mode;
			curSize += sizeof(double);//double m_depth;
			curSize += (sizeof(int) + m_itemname_depth.length() * sizeof(char));//std::string m_itemname_depth;
			curSize += (sizeof(int) + m_viewname_depth.length() * sizeof(char));//std::string m_viewname_depth;
			curSize += sizeof(int);//int m_interpolatetype_depth;
			curSize += sizeof(int);//int m_rows;
			curSize += sizeof(int);//int m_cols;
			curSize += (sizeof(int) + m_depth_values.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_depth_values;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_model_idx, sizeof(long));data += sizeof(long);
			int namelength = m_name.length();
			memcpy(data, &namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_name.length(); i++)
			{
				memcpy(data, &(m_name[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_age_from, sizeof(double));data += sizeof(double);
			int referencelength = m_reference.length();
			memcpy(data, &referencelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_reference.length(); i++)
			{
				memcpy(data, &(m_reference[i]), sizeof(char));data += sizeof(char);
			}
			int itemname_layerlength = m_itemname_layer.length();
			memcpy(data, &itemname_layerlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_itemname_layer.length(); i++)
			{
				memcpy(data, &(m_itemname_layer[i]), sizeof(char));data += sizeof(char);
			}
			int viewname_layerlength = m_viewname_layer.length();
			memcpy(data, &viewname_layerlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_viewname_layer.length(); i++)
			{
				memcpy(data, &(m_viewname_layer[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_interpolatetype_layer, sizeof(int));data += sizeof(int);
			int layer_valuessize = m_layer_values.size();
			memcpy(data, &layer_valuessize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < layer_valuessize; i++)
			{
				memcpy(data, &(m_layer_values[i]), sizeof(double));data += sizeof(double);
			}
			int modelength = m_mode.length();
			memcpy(data, &modelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_mode.length(); i++)
			{
				memcpy(data, &(m_mode[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_depth, sizeof(double));data += sizeof(double);
			int itemname_depthlength = m_itemname_depth.length();
			memcpy(data, &itemname_depthlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_itemname_depth.length(); i++)
			{
				memcpy(data, &(m_itemname_depth[i]), sizeof(char));data += sizeof(char);
			}
			int viewname_depthlength = m_viewname_depth.length();
			memcpy(data, &viewname_depthlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_viewname_depth.length(); i++)
			{
				memcpy(data, &(m_viewname_depth[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_interpolatetype_depth, sizeof(int));data += sizeof(int);
			memcpy(data, &m_rows, sizeof(int));data += sizeof(int);
			memcpy(data, &m_cols, sizeof(int));data += sizeof(int);
			int depth_valuessize = m_depth_values.size();
			memcpy(data, &depth_valuessize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < depth_valuessize; i++)
			{
				memcpy(data, &(m_depth_values[i]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_model_idx, data, sizeof(long));data += sizeof(long);
			int namelength;
			memcpy(&namelength, data, sizeof(int));data += sizeof(int);
			m_name = "";
			for(int i = 0; i < namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_name += temp;
			}
			memcpy(&m_age_from, data, sizeof(double));data += sizeof(double);
			int referencelength;
			memcpy(&referencelength, data, sizeof(int));data += sizeof(int);
			m_reference = "";
			for(int i = 0; i < referencelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_reference += temp;
			}
			int itemname_layerlength;
			memcpy(&itemname_layerlength, data, sizeof(int));data += sizeof(int);
			m_itemname_layer = "";
			for(int i = 0; i < itemname_layerlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_itemname_layer += temp;
			}
			int viewname_layerlength;
			memcpy(&viewname_layerlength, data, sizeof(int));data += sizeof(int);
			m_viewname_layer = "";
			for(int i = 0; i < viewname_layerlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_viewname_layer += temp;
			}
			memcpy(&m_interpolatetype_layer, data, sizeof(int));data += sizeof(int);
			int layer_valuessize;
			memcpy(&layer_valuessize, data, sizeof(int));data += sizeof(int);
			m_layer_values.clear();
			for(int i = 0; i < layer_valuessize; i++)
			{
				double temp;
				memcpy(&temp, data, sizeof(double));data += sizeof(double);
				m_layer_values.push_back(temp);
			}
			int modelength;
			memcpy(&modelength, data, sizeof(int));data += sizeof(int);
			m_mode = "";
			for(int i = 0; i < modelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_mode += temp;
			}
			memcpy(&m_depth, data, sizeof(double));data += sizeof(double);
			int itemname_depthlength;
			memcpy(&itemname_depthlength, data, sizeof(int));data += sizeof(int);
			m_itemname_depth = "";
			for(int i = 0; i < itemname_depthlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_itemname_depth += temp;
			}
			int viewname_depthlength;
			memcpy(&viewname_depthlength, data, sizeof(int));data += sizeof(int);
			m_viewname_depth = "";
			for(int i = 0; i < viewname_depthlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_viewname_depth += temp;
			}
			memcpy(&m_interpolatetype_depth, data, sizeof(int));data += sizeof(int);
			memcpy(&m_rows, data, sizeof(int));data += sizeof(int);
			memcpy(&m_cols, data, sizeof(int));data += sizeof(int);
			m_depth_values.clear();
			int depth_valuessize;
			memcpy(&depth_valuessize, data, sizeof(int));data += sizeof(int);
			for(int i = 0; i < depth_valuessize; i++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_depth_values.push_back(temp);
			}
		}
		double Interpolate(VertexSimulated *curvertex)
		{
			CGeoPoint<double> &pt0 = m_depth_values[0];
			CGeoPoint<double> &pt1 = m_depth_values[m_cols - 1];
			CGeoPoint<double> &pt2 = m_depth_values[(m_rows - 1) * m_cols];
			CGeoPoint<double> vectora(pt1.m_x - pt0.m_x, pt1.m_y - pt0.m_y);
			CGeoPoint<double> vectorb(pt2.m_x - pt0.m_x, pt2.m_y - pt0.m_y);
			CGeoPoint<double> vectorc(curvertex->m_x - pt0.m_x, curvertex->m_y - pt0.m_y);
			double m = (vectorc.m_x * vectorb.m_y - vectorc.m_y * vectorb.m_x) / (vectora.m_x * vectorb.m_y - vectora.m_y * vectorb.m_x);
			double n = (vectorc.m_x * vectora.m_y - vectorc.m_y * vectora.m_x) / (vectora.m_y * vectorb.m_x - vectora.m_x * vectorb.m_y);
			int row = n * (m_rows - 1) + 0.5;
			int col = m * (m_cols - 1) + 0.5;
			if(row < 0)
				row = 0;
			if(col < 0)
				col = 0;
			if(row > m_rows - 1)
				row = m_rows - 1;
			if(col > m_cols - 1)
				col = m_cols - 1;
			return m_depth_values[row * m_cols + col].m_z;
		}
	};
	typedef std::vector<WaterDepthDefinition> WaterDepthDefinitions;

	struct SedimentWaterInterfaceTemperatureDefinition
	{
		//basic information
		long m_idx;
		long m_model_idx;
		std::string m_name;
		// WaterInterfaceTemperature variable
		double m_age_from;
		std::string m_reference;
		//model
		std::string m_mode;
		double m_temperature;
		//depth map
		std::string m_itemname_depth;
		std::string m_viewname_depth;
		int m_interpolatetype_depth;
		int m_rows;
		int m_cols;
		std::vector<CGeoPoint<double> > m_depth_values;

		SedimentWaterInterfaceTemperatureDefinition()
		{
			//basic information
			m_idx = 0;
			m_model_idx = 0;
			m_name = "";

			// WaterInterfaceTemperature variable
			m_age_from = 0.;
			m_reference = "";

			//model
			m_mode = "";
			m_temperature = 0.;

			//depth map
			m_itemname_depth = "";
			m_viewname_depth = "";
			m_interpolatetype_depth = 0;
			m_rows = 0;
			m_cols = 0;
			m_depth_values.clear();
		}

		SedimentWaterInterfaceTemperatureDefinition(const SedimentWaterInterfaceTemperatureDefinition &other)
		{
			*this = other;
		}

		const SedimentWaterInterfaceTemperatureDefinition &operator=(const SedimentWaterInterfaceTemperatureDefinition &other)
		{
			if(this == &other)
			{
				return *this;
			}
			//basic information
			m_idx = other.m_idx;
			m_model_idx = other.m_model_idx;
			m_name = other.m_name;

			//WaterInterfaceTemperature variable
			m_age_from = other.m_age_from;
			m_reference = other.m_reference;

			//model
			m_mode = other.m_mode;
			m_temperature = other.m_temperature;

			//depth map
			m_itemname_depth = other.m_itemname_depth;
			m_viewname_depth = other.m_viewname_depth;
			m_interpolatetype_depth = other.m_interpolatetype_depth;
			m_rows = other.m_rows;
			m_cols = other.m_cols;
			m_depth_values = other.m_depth_values;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(long);//long m_idx;
			curSize += sizeof(long);//long m_model_idx;
			curSize += (sizeof(int) + m_name.length() * sizeof(char));//std::string m_name;
			curSize += sizeof(double);//double m_age_from;
			curSize += (sizeof(int) + m_reference.length() * sizeof(char));//std::string m_reference;
			curSize += (sizeof(int) + m_mode.length() * sizeof(char));//std::string m_mode;
			curSize += sizeof(double);//double m_temperature;
			curSize += (sizeof(int) + m_itemname_depth.length() * sizeof(char));//std::string m_itemname_depth;
			curSize += (sizeof(int) + m_viewname_depth.length() * sizeof(char));//std::string m_viewname_depth;
			curSize += sizeof(int);//int m_interpolatetype_depth;
			curSize += sizeof(int);//int m_rows;
			curSize += sizeof(int);//int m_cols;
			curSize += (sizeof(int) + m_depth_values.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_depth_values;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_model_idx, sizeof(long));data += sizeof(long);
			int namelength = m_name.length();
			memcpy(data, &namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_name.length(); i++)
			{
				memcpy(data, &(m_name[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_age_from, sizeof(double));data += sizeof(double);
			int referencelength = m_reference.length();
			memcpy(data, &referencelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_reference.length(); i++)
			{
				memcpy(data, &(m_reference[i]), sizeof(char));data += sizeof(char);
			}
			int modelength = m_mode.length();
			memcpy(data, &modelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_mode.length(); i++)
			{
				memcpy(data, &(m_mode[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_temperature, sizeof(double));data += sizeof(double);
			int itemname_depthlength = m_itemname_depth.length();
			memcpy(data, &itemname_depthlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_itemname_depth.length(); i++)
			{
				memcpy(data, &(m_itemname_depth[i]), sizeof(char));data += sizeof(char);
			}
			int viewname_depthlength = m_viewname_depth.length();
			memcpy(data, &viewname_depthlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_viewname_depth.length(); i++)
			{
				memcpy(data, &(m_viewname_depth[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_interpolatetype_depth, sizeof(int));data += sizeof(int);
			memcpy(data, &m_rows, sizeof(int));data += sizeof(int);
			memcpy(data, &m_cols, sizeof(int));data += sizeof(int);
			int depth_valuessize = m_depth_values.size();
			memcpy(data, &depth_valuessize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < depth_valuessize; i++)
			{
				memcpy(data, &(m_depth_values[i]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_model_idx, data, sizeof(long));data += sizeof(long);
			int namelength;
			memcpy(&namelength, data, sizeof(int));data += sizeof(int);
			m_name = "";
			for(int i = 0; i < namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_name += temp;
			}
			memcpy(&m_age_from, data, sizeof(double));data += sizeof(double);
			int referencelength;
			memcpy(&referencelength, data, sizeof(int));data += sizeof(int);
			m_reference = "";
			for(int i = 0; i < referencelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_reference += temp;
			}
			int modelength;
			memcpy(&modelength, data, sizeof(int));data += sizeof(int);
			m_mode = "";
			for(int i = 0; i < modelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_mode += temp;
			}
			memcpy(&m_temperature, data, sizeof(double));data += sizeof(double);
			int itemname_depthlength;
			memcpy(&itemname_depthlength, data, sizeof(int));data += sizeof(int);
			m_itemname_depth = "";
			for(int i = 0; i < itemname_depthlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_itemname_depth += temp;
			}
			int viewname_depthlength;
			memcpy(&viewname_depthlength, data, sizeof(int));data += sizeof(int);
			m_viewname_depth = "";
			for(int i = 0; i < viewname_depthlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_viewname_depth += temp;
			}
			memcpy(&m_interpolatetype_depth, data, sizeof(int));data += sizeof(int);
			memcpy(&m_rows, data, sizeof(int));data += sizeof(int);
			memcpy(&m_cols, data, sizeof(int));data += sizeof(int);
			m_depth_values.clear();
			int depth_valuessize;
			memcpy(&depth_valuessize, data, sizeof(int));data += sizeof(int);
			for(int i = 0; i < depth_valuessize; i++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_depth_values.push_back(temp);
			}
		}
		double Interpolate(VertexSimulated *curvertex)
		{
			CGeoPoint<double> &pt0 = m_depth_values[0];
			CGeoPoint<double> &pt1 = m_depth_values[m_cols - 1];
			CGeoPoint<double> &pt2 = m_depth_values[(m_rows - 1) * m_cols];
			CGeoPoint<double> vectora(pt1.m_x - pt0.m_x, pt1.m_y - pt0.m_y);
			CGeoPoint<double> vectorb(pt2.m_x - pt0.m_x, pt2.m_y - pt0.m_y);
			CGeoPoint<double> vectorc(curvertex->m_x - pt0.m_x, curvertex->m_y - pt0.m_y);
			double m = (vectorc.m_x * vectorb.m_y - vectorc.m_y * vectorb.m_x) / (vectora.m_x * vectorb.m_y - vectora.m_y * vectorb.m_x);
			double n = (vectorc.m_x * vectora.m_y - vectorc.m_y * vectora.m_x) / (vectora.m_y * vectorb.m_x - vectora.m_x * vectorb.m_y);
			int row = n * (m_rows - 1) + 0.5;
			int col = m * (m_cols - 1) + 0.5;
			if(row < 0)
				row = 0;
			if(col < 0)
				col = 0;
			if(row > m_rows - 1)
				row = m_rows - 1;
			if(col > m_cols - 1)
				col = m_cols - 1;
			return m_depth_values[row * m_cols + col].m_z;
		}
	};
	typedef std::vector<SedimentWaterInterfaceTemperatureDefinition> SedimentWaterInterfaceTemperatureDefinitions;

	struct HeatFlowDefinition
	{
		//basic information
		long m_idx;
		long m_model_idx;
		std::string m_name;
		// WaterInterfaceTemperature variable
		double m_age_from;
		std::string m_reference;
		//model
		std::string m_mode;
		double m_value;
		//depth map
		std::string m_itemname_depth;
		std::string m_viewname_depth;
		int m_interpolatetype_depth;
		int m_rows;
		int m_cols;
		std::vector<CGeoPoint<double> > m_depth_values;

		HeatFlowDefinition()
		{
			//basic information
			m_idx = 0;
			m_model_idx = 0;
			m_name = "";

			// WaterInterfaceTemperature variable
			m_age_from = 0.;
			m_reference = "";

			//model
			m_mode = "";
			m_value = 0.;

			//depth map
			m_itemname_depth = "";
			m_viewname_depth = "";
			m_interpolatetype_depth = 0;
			m_rows = 0;
			m_cols = 0;
			m_depth_values.clear();
		}

		HeatFlowDefinition(const HeatFlowDefinition &other)
		{
			*this = other;
		}

		const HeatFlowDefinition &operator=(const HeatFlowDefinition &other)
		{
			if(this == &other)
			{
				return *this;
			}
			//basic information
			m_idx = other.m_idx;
			m_model_idx = other.m_model_idx;
			m_name = other.m_name;

			//WaterInterfaceTemperature variable
			m_age_from = other.m_age_from;
			m_reference = other.m_reference;

			//model
			m_mode = other.m_mode;
			m_value = other.m_value;

			//depth map
			m_itemname_depth = other.m_itemname_depth;
			m_viewname_depth = other.m_viewname_depth;
			m_interpolatetype_depth = other.m_interpolatetype_depth;
			m_rows = other.m_rows;
			m_cols = other.m_cols;
			m_depth_values = other.m_depth_values;

			return *this;
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(long);//long m_idx;
			curSize += sizeof(long);//long m_model_idx;
			curSize += (sizeof(int) + m_name.length() * sizeof(char));//std::string m_name;
			curSize += sizeof(double);//double m_age_from;
			curSize += (sizeof(int) + m_reference.length() * sizeof(char));//std::string m_reference;
			curSize += (sizeof(int) + m_mode.length() * sizeof(char));//std::string m_mode;
			curSize += sizeof(double);//double m_value;
			curSize += (sizeof(int) + m_itemname_depth.length() * sizeof(char));//std::string m_itemname_depth;
			curSize += (sizeof(int) + m_viewname_depth.length() * sizeof(char));//std::string m_viewname_depth;
			curSize += sizeof(int);//int m_interpolatetype_depth;
			curSize += sizeof(int);//int m_rows;
			curSize += sizeof(int);//int m_cols;
			curSize += (sizeof(int) + m_depth_values.size() * sizeof(CGeoPoint<double>));//std::vector<CGeoPoint<double> > m_depth_values;
			return curSize;
		}
		void SerializeData(char* &data)
		{
			memcpy(data, &m_idx, sizeof(long));data += sizeof(long);
			memcpy(data, &m_model_idx, sizeof(long));data += sizeof(long);
			int namelength = m_name.length();
			memcpy(data, &namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_name.length(); i++)
			{
				memcpy(data, &(m_name[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_age_from, sizeof(double));data += sizeof(double);
			int referencelength = m_reference.length();
			memcpy(data, &referencelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_reference.length(); i++)
			{
				memcpy(data, &(m_reference[i]), sizeof(char));data += sizeof(char);
			}
			int modelength = m_mode.length();
			memcpy(data, &modelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_mode.length(); i++)
			{
				memcpy(data, &(m_mode[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_value, sizeof(double));data += sizeof(double);
			int itemname_depthlength = m_itemname_depth.length();
			memcpy(data, &itemname_depthlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_itemname_depth.length(); i++)
			{
				memcpy(data, &(m_itemname_depth[i]), sizeof(char));data += sizeof(char);
			}
			int viewname_depthlength = m_viewname_depth.length();
			memcpy(data, &viewname_depthlength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_viewname_depth.length(); i++)
			{
				memcpy(data, &(m_viewname_depth[i]), sizeof(char));data += sizeof(char);
			}
			memcpy(data, &m_interpolatetype_depth, sizeof(int));data += sizeof(int);
			memcpy(data, &m_rows, sizeof(int));data += sizeof(int);
			memcpy(data, &m_cols, sizeof(int));data += sizeof(int);
			int depth_valuessize = m_depth_values.size();
			memcpy(data, &depth_valuessize, sizeof(int));data += sizeof(int);
			for(int i = 0; i < depth_valuessize; i++)
			{
				memcpy(data, &(m_depth_values[i]), sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
			}
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_idx, data, sizeof(long));data += sizeof(long);
			memcpy(&m_model_idx, data, sizeof(long));data += sizeof(long);
			int namelength;
			memcpy(&namelength, data, sizeof(int));data += sizeof(int);
			m_name = "";
			for(int i = 0; i < namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_name += temp;
			}
			memcpy(&m_age_from, data, sizeof(double));data += sizeof(double);
			int referencelength;
			memcpy(&referencelength, data, sizeof(int));data += sizeof(int);
			m_reference = "";
			for(int i = 0; i < referencelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_reference += temp;
			}
			int modelength;
			memcpy(&modelength, data, sizeof(int));data += sizeof(int);
			m_mode = "";
			for(int i = 0; i < modelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_mode += temp;
			}
			memcpy(&m_value, data, sizeof(double));data += sizeof(double);
			int itemname_depthlength;
			memcpy(&itemname_depthlength, data, sizeof(int));data += sizeof(int);
			m_itemname_depth = "";
			for(int i = 0; i < itemname_depthlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_itemname_depth += temp;
			}
			int viewname_depthlength;
			memcpy(&viewname_depthlength, data, sizeof(int));data += sizeof(int);
			m_viewname_depth = "";
			for(int i = 0; i < viewname_depthlength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_viewname_depth += temp;
			}
			memcpy(&m_interpolatetype_depth, data, sizeof(int));data += sizeof(int);
			memcpy(&m_rows, data, sizeof(int));data += sizeof(int);
			memcpy(&m_cols, data, sizeof(int));data += sizeof(int);
			m_depth_values.clear();
			int depth_valuessize;
			memcpy(&depth_valuessize, data, sizeof(int));data += sizeof(int);
			for(int i = 0; i < depth_valuessize; i++)
			{
				CGeoPoint<double> temp;
				memcpy(&temp, data, sizeof(CGeoPoint<double>));data += sizeof(CGeoPoint<double>);
				m_depth_values.push_back(temp);
			}
		}

		double Interpolate(VertexSimulated *curvertex)
		{
			CGeoPoint<double> &pt0 = m_depth_values[0];
			CGeoPoint<double> &pt1 = m_depth_values[m_cols - 1];
			CGeoPoint<double> &pt2 = m_depth_values[(m_rows - 1) * m_cols];
			CGeoPoint<double> vectora(pt1.m_x - pt0.m_x, pt1.m_y - pt0.m_y);
			CGeoPoint<double> vectorb(pt2.m_x - pt0.m_x, pt2.m_y - pt0.m_y);
			CGeoPoint<double> vectorc(curvertex->m_x - pt0.m_x, curvertex->m_y - pt0.m_y);
			double m = (vectorc.m_x * vectorb.m_y - vectorc.m_y * vectorb.m_x) / (vectora.m_x * vectorb.m_y - vectora.m_y * vectorb.m_x);
			double n = (vectorc.m_x * vectora.m_y - vectorc.m_y * vectora.m_x) / (vectora.m_y * vectorb.m_x - vectora.m_x * vectorb.m_y);
			int row = n * (m_rows - 1) + 0.5;
			int col = m * (m_cols - 1) + 0.5;
			if(row < 0)
				row = 0;
			if(col < 0)
				col = 0;
			if(row > m_rows - 1)
				row = m_rows - 1;
			if(col > m_cols - 1)
				col = m_cols - 1;
			return m_depth_values[row * m_cols + col].m_z;
		}
	};
	typedef std::vector<HeatFlowDefinition> HeatFlowDefinitions;

	/*!
	*
	**/
	struct MeshSimulated : public AnyCGAL::Mesh3D, \
		public CenterMatrixVariable, \
		public CenterPhaseVariable, \
		public MassVariable, \
		public CenterPoreFluidVariable, \
		public SourceRockVariable,\
		public FiniteElementVariable, \
		public PercolationVariable
	{
		//�ز������ ��1Ϊ�ز㣬2Ϊ��㣬3Ϊ��ʴ
		unsigned char m_geological_event;
		//��ʴ������������������
		int m_connecting_marker;

		//�����ж�������Ƿ��Ѿ�����ʴ���ˣ���ʼ��ֵʱ����false
		bool m_is_eroded;

		// Litho variable
		int m_lithovariablenum;
		LithoVariable* m_lithovariables;

		//face definition name
		//find the FaceDefinition from FaceDefinitions
		std::string m_face_definition_name;

		//
		//double m_center_temperature;
		double m_center_porosity;
		double m_center_permeability; // �ܵ���͸�� Permeability�� ��λ��m^2 ��Ҳ���Ǵ�ֱ������͸��
		double m_center_PermH; //ˮƽ������͸�� 
		double m_center_TPerm_Anisotr;//�ܵ���͸�ʸ�������ֵ����ˮƽ�����봹ֱ������͸�ʱ�ֵ

		double m_center_water_density;

		double m_center_heat_qr;
		double m_center_pressure_water_qr;
		double m_center_pressure_oil_qr;
		double m_center_pressure_gas_qr;
		double m_center_COC;

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

		//
		MeshSimulated() : m_lithovariablenum(0), m_lithovariables(0), m_face_definition_name("")
		{
			//m_center_temperature = 0;
			m_center_porosity = 0;
			m_center_permeability = 0;
			m_center_PermH = 0;
			m_center_TPerm_Anisotr = 0;
			m_center_water_density = 0;
			m_center_heat_qr = 0;
			m_center_pressure_water_qr = 0;
			m_center_pressure_oil_qr = 0;
			m_center_pressure_gas_qr = 0;
			m_center_COC = 0;
			m_center_MExpOil= 0.;
			m_center_MExpGas = 0.;

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
		~MeshSimulated()
		{
			Release();
			if(m_lithovariables)
				delete []m_lithovariables;
			m_lithovariables = 0;
			m_lithovariablenum = 0;
		}
		MeshSimulated(const MeshSimulated &other)
		{
			*this = other;
		}
		const MeshSimulated &operator=(const MeshSimulated &other)
		{
			if(this == &other)
			{
				return *this;
			}
			// Mesh 3D operator=
			{
				//m_mesh_code = other.m_mesh_code;
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
			}

			*((CenterMatrixVariable*)this) = *((CenterMatrixVariable*)&other);
			*((CenterPhaseVariable*)this) = *((CenterPhaseVariable*)&other);
			*((MassVariable*)this) = *((MassVariable*)&other);
			*((CenterPoreFluidVariable*)this) = *((CenterPoreFluidVariable*)&other);
			*((SourceRockVariable*)this) = *((SourceRockVariable*)&other);
			*((FiniteElementVariable*)this) = *((FiniteElementVariable*)&other);
			*((PercolationVariable*)this) = *((PercolationVariable*)&other);

			m_geological_event = other.m_geological_event;
			m_connecting_marker = other.m_connecting_marker;
			m_is_eroded = other.m_is_eroded;
			if(m_lithovariables)
				delete []m_lithovariables;
			m_lithovariables = 0;
			m_lithovariablenum = other.m_lithovariablenum;
			if(m_lithovariablenum)
			{
				m_lithovariables = new LithoVariable[m_lithovariablenum];
				for(int i = 0; i < m_lithovariablenum; i++)
					m_lithovariables[i] = other.m_lithovariables[i];
			}
			m_face_definition_name = other.m_face_definition_name;
			//m_center_temperature = other.m_center_temperature;
			m_center_porosity = other.m_center_porosity;
			m_center_permeability = other.m_center_permeability;
			m_center_PermH = other.m_center_PermH;
			m_center_TPerm_Anisotr = other.m_center_TPerm_Anisotr;
			m_center_water_density = other.m_center_water_density;
			m_center_heat_qr = other.m_center_heat_qr;
			m_center_pressure_water_qr = other.m_center_pressure_water_qr;
			m_center_pressure_oil_qr = other.m_center_pressure_oil_qr;
			m_center_pressure_gas_qr = other.m_center_pressure_gas_qr;
			m_center_COC = other.m_center_COC;
			m_center_MExpOil= other.m_center_MExpOil;
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
		void CopyFromMesh3D(AnyCGAL::Mesh3D &other)
		{
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
		}
		int GetSerializeDataLength()
		{
			int curSize = 0;
			curSize += sizeof(unsigned char);//unsigned char m_geological_event;
			curSize += sizeof(int);//int m_connecting_marker;
			curSize += sizeof(bool);//bool m_is_eroded;
			curSize += sizeof(int);//int m_lithovariablenum;
			for(int i = 0; i < m_lithovariablenum; i++)
			{
				curSize += m_lithovariables[i].GetSerializeDataLength();
			}
			curSize += (sizeof(int) + m_face_definition_name.length() * sizeof(char));//string m_face_definition_name;
			//curSize += sizeof(double);//double m_center_temperature;
			curSize += sizeof(double);//double m_center_porosity;
			curSize += sizeof(double);//double m_center_permeability;
			curSize += sizeof(double);//double m_center_PermH;
			curSize += sizeof(double);//double m_center_TPerm_Anisotr;
			curSize += sizeof(double);//double m_center_water_density;
			curSize += sizeof(double);//double m_center_heat_qr;
			curSize += sizeof(double);//double m_center_pressure_water_qr;
			curSize += sizeof(double);//double m_center_pressure_oil_qr;
			curSize += sizeof(double);//double m_center_pressure_gas_qr;
			curSize += sizeof(double);//double m_center_COC;
			curSize += sizeof(double);//double m_center_MExpOil
			curSize += sizeof(double);//double m_center_MExpGas
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
			// Mesh3D
			curSize += Mesh3D::GetSerializeDataLength();
			// CenterMatrixVariable
			curSize += CenterMatrixVariable::GetSerializeDataLength();
			// CenterPhaseVariable
			curSize += CenterPhaseVariable::GetSerializeDataLength();
			// MassVariable
			curSize += MassVariable::GetSerializeDataLength();
			// CenterPoreFluidVariable
			curSize += CenterPoreFluidVariable::GetSerializeDataLength();
			// SourceRockVariable
			curSize += SourceRockVariable::GetSerializeDataLength();
			// FiniteElementVariable
			curSize += FiniteElementVariable::GetSerializeDataLength();
			// PercolationVariable
			curSize += PercolationVariable::GetSerializeDataLength();
			return curSize;
		}
		int GetSerializeDataLength_Mini()
		{
			int curSize = 0;
			//curSize += sizeof(double);//double m_center_temperature;
			curSize += sizeof(double);//double m_center_porosity;
			curSize += sizeof(double);//double m_center_total_thermal_cond;
			// Mesh3D
			curSize += Mesh3D::GetSerializeDataLength();
			return curSize;
		}
		char *SerializeData(int &len)
		{
			char *data;
			len = GetSerializeDataLength();
			data = (char*)malloc(len);
			memcpy(data, &m_geological_event, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(data, &m_connecting_marker, sizeof(int));data += sizeof(int);
			memcpy(data, &m_is_eroded, sizeof(bool));data += sizeof(bool);
			memcpy(data, &m_lithovariablenum, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_lithovariablenum; i++)
			{
				m_lithovariables[i].SerializeData(data);
			}
			int face_definition_namelength = m_face_definition_name.length();
			memcpy(data, &face_definition_namelength, sizeof(int));data += sizeof(int);
			for(int i = 0; i < m_face_definition_name.length(); i++)
			{
				memcpy(data, &(m_face_definition_name[i]), sizeof(char));data += sizeof(char);
			}
			//memcpy(data, &m_center_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_permeability, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_PermH, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_TPerm_Anisotr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_water_density, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_heat_qr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_pressure_water_qr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_pressure_oil_qr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_pressure_gas_qr, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_COC, sizeof(double));data += sizeof(double);
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
			// Mesh3D
			Mesh3D::SerializeData(data);
			// CenterMatrixVariable
			CenterMatrixVariable::SerializeData(data);
			// CenterPhaseVariable
			CenterPhaseVariable::SerializeData(data);
			// MassVariable
			MassVariable::SerializeData(data);
			// CenterPoreFluidVariable
			CenterPoreFluidVariable::SerializeData(data);
			// SourceRockVariable
			SourceRockVariable::SerializeData(data);
			// FiniteElementVariable
			FiniteElementVariable::SerializeData(data);
			// PercolationVariable
			PercolationVariable::SerializeData(data);
			data -= len;
			return data;
		}
		char *SerializeData_Mini(int &len)
		{
			char *data;
			len = GetSerializeDataLength_Mini();
			data = (char*)malloc(len);
			//memcpy(data, &m_center_temperature, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_porosity, sizeof(double));data += sizeof(double);
			memcpy(data, &m_center_total_thermal_cond, sizeof(double));data += sizeof(double);
			// Mesh3D
			Mesh3D::SerializeData(data);
			data -= len;
			return data;
		}
		void RestoreSerializeData(char* &data)
		{
			memcpy(&m_geological_event, data, sizeof(unsigned char));data += sizeof(unsigned char);
			memcpy(&m_connecting_marker, data, sizeof(int));data += sizeof(int);
			memcpy(&m_is_eroded, data, sizeof(bool));data += sizeof(bool);
			memcpy(&m_lithovariablenum, data, sizeof(int));data += sizeof(int);
			if(m_lithovariablenum > 0)
				m_lithovariables = new LithoVariable[m_lithovariablenum];
			for(int i = 0; i < m_lithovariablenum; i++)
			{
				m_lithovariables[i].RestoreSerializeData(data);
			}
			int face_definition_namelength;
			memcpy(&face_definition_namelength, data, sizeof(int));data += sizeof(int);
			m_face_definition_name = "";
			for(int i = 0; i < face_definition_namelength; i++)
			{
				char temp;
				memcpy(&temp, data, sizeof(char));data += sizeof(char);
				m_face_definition_name += temp;
			}
			//memcpy(&m_center_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_permeability, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_PermH, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_TPerm_Anisotr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_water_density, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_heat_qr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_pressure_water_qr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_pressure_oil_qr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_pressure_gas_qr, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_COC, data, sizeof(double));data += sizeof(double);
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
			// Mesh3D
			Mesh3D::RestoreSerializeData(data);
			// CenterMatrixVariable
			CenterMatrixVariable::RestoreSerializeData(data);
			// CenterPhaseVariable
			CenterPhaseVariable::RestoreSerializeData(data);
			// MassVariable
			MassVariable::RestoreSerializeData(data);
			// CenterPoreFluidVariable
			CenterPoreFluidVariable::RestoreSerializeData(data);
			// SourceRockVariable
			SourceRockVariable::RestoreSerializeData(data);
			// FiniteElementVariable
			FiniteElementVariable::RestoreSerializeData(data);
			// PercolationVariable
			PercolationVariable::RestoreSerializeData(data);
		}
		void RestoreSerializeData_Mini(char* &data)
		{
			//memcpy(&m_center_temperature, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_porosity, data, sizeof(double));data += sizeof(double);
			memcpy(&m_center_total_thermal_cond, data, sizeof(double));data += sizeof(double);
			// Mesh3D
			Mesh3D::RestoreSerializeData(data);
		}
		friend std::ofstream &operator << (std::ofstream &os, MeshSimulated &mesh)
		{
			//os << "\r\n---- ---- MeshSimulated variables ----- ----- ";
			os << "\r\n---- ---- ---- geological event: " << mesh.m_geological_event;
			os << "\r\n---- ---- ---- connecting marker: " << mesh.m_connecting_marker;
			os << "\r\n---- ---- ---- is eroded: " << mesh.m_is_eroded;
			os << "\r\n---- ---- ---- lithology number: " << mesh.m_lithovariablenum;
			for(int i = 0; i < mesh.m_lithovariablenum; i++)
			{
				os << "\r\n---- ---- ---- the " << i << "th litho parameter as flow: ";
				os << mesh.m_lithovariables[i];
			}
			os << "\r\n---- ---- ---- face definition: " << mesh.m_face_definition_name;
			//os << "\r\n---- ---- ---- center temperature: " << mesh.m_center_temperature;
			os << "\r\n---- ---- ---- center porosity: " << mesh.m_center_porosity;
			os << "\r\n---- ---- ---- center permeability: " << mesh.m_center_permeability;
			os << "\r\n---- ---- ---- permeability along horizon: " << mesh.m_center_PermH;
			os << "\r\n---- ---- ---- permeability anisotropy coefficient: " << mesh.m_center_TPerm_Anisotr;
			os << "\r\n---- ---- ---- center water density: " << mesh.m_center_water_density;
			os << "\r\n---- ---- ---- center heat qr: " << mesh.m_center_heat_qr;
			os << "\r\n---- ---- ---- center pressure water qr: " << mesh.m_center_pressure_water_qr;
			os << "\r\n---- ---- ---- center pressure oil qr: " << mesh.m_center_pressure_oil_qr;
			os << "\r\n---- ---- ---- center pressure gas qr: " << mesh.m_center_pressure_gas_qr;
			os << "\r\n---- ---- ---- center compact coefficient: " << mesh.m_center_COC;
			os << "\r\n---- ---- ---- center MExpOil: " << mesh.m_center_MExpOil;
			os << "\r\n---- ---- ---- center MExpGas: " << mesh.m_center_MExpGas;
			os << "\r\n---- ---- ---- center vwater points: ";
			for(int i = 0; i < mesh.m_center_vwater_x.size(); i++)
			{
				os << "\r\n---- ---- ---- (" << mesh.m_center_vwater_x[i] << "," << mesh.m_center_vwater_y[i] << "," << mesh.m_center_vwater_z[i] <<")";
			}
			os << "\r\n---- ---- ---- bcd: ";
			for(int i = 0; i < mesh.m_b.size(); i++)
			{
				for(int j = 0; j < mesh.m_b[i].size(); j++)
				{
					os << "\r\n---- ---- ---- (" << i << ":" << j << ":" << mesh.m_b[i][j] << "," << mesh.m_c[i][j] << "," << mesh.m_d[i][j] <<")";
				}
			}
			os << "\r\n---- ---- ---- kxxkyykzz: ";
			for(int i = 0; i < mesh.m_kxx.size(); i++)
			{
				os << "\r\n---- ---- ---- (" << mesh.m_kxx[i] << "," << mesh.m_kyy[i] << "," << mesh.m_kzz[i] <<")";
			}

			//os << *((Mesh3D *)(&mesh));
			os << *((CenterMatrixVariable *)(&mesh));
			os << *((CenterPhaseVariable *)(&mesh));
			os << *((MassVariable *)(&mesh));
			os << *((CenterPoreFluidVariable *)(&mesh));
			os << *((SourceRockVariable *)(&mesh));
			os << *((FiniteElementVariable *)(&mesh));
			os << *((PercolationVariable *)(&mesh));

			return os;
		}
	};
}
#endif