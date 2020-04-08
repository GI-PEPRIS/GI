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
#ifndef __ANYBASIN_DISTRIBUTED_SIMULATION_MODEL_H__
#define __ANYBASIN_DISTRIBUTED_SIMULATION_MODEL_H__

//
#include "anybasin.h"
#include "distributedsimulationgeneric.h"
#include "any/cgal/anyhypermesh.h"
using namespace AnyCGAL;

// forward class
namespace AnyCGAL
{
	class CAnyHyperMesh;
}
using namespace AnyCGAL;

//
namespace AnyBasin
{
	// forward class
	class CAnyHyperBasinSimulator;

	/*!
	* CDistributedSimulationModel model;
	* model.DeployModel<CAnyHyperMesh, CAnyHyperSimulator, hexa_tetra_hyper_mesh_tag>(hyermesh);
	* model.Model2Solution<,>();
	* for(int i = 0; i < model.m_simulaiton_solutions.size();i++)
    * {
	*    m_simulaiton_solutions[i]->DeployBlock<>();
	*    m_simulaiton_solutions[i]->Solution2Job();
	* }
	* model.model_run_solution();
	**/
	class ANYBASIN_CLASS CDistributedSimulationModel : DistributedModel
	{
		//
		friend class CDistributedSimulationSolution;
	public:
		/*!
		*
		**/
		CDistributedSimulationModel(){m_host_geological_model_impl = 0;}
		~CDistributedSimulationModel(){Release();}

	public:
		//
		//
		//
		/*!
		* \brief 三维模拟模型对应SIMULATOR及分布式文件生成
		* \param initial_hyper, 初始、整体MESH模型
		* \param children_hypers, 基于初始模型，考虑不同地质事件、模拟精度而定义的子MESH模型
		* (1) MODEL DATA文件的生成与分发
		* (2) MATRIX DATA文件的生成与分发（空）
		* (3) SIMULATION DATA文件的生成与分发（空），考虑放到SOLUTION BLOCK
		**/
		template<typename HyperMesh, typename HyperSimulator, typename MeshTag>
		void DeployModel(HyperMesh *initial_hyper, std::vector<HyperMesh *> &refined_hypers);
		template<>
		void DeployModel<CAnyHyperMesh, CAnyHyperBasinSimulator, hexa_tetra_hyper_model_mesh_tag>(CAnyHyperMesh *initial_hyper, std::vector<CAnyHyperMesh *> &refined_hypers);

		template<typename HyperMesh, typename HyperSimulator, typename MeshTag>
		void DeployResultModel(HyperMesh *resultsimulator);
		template<>
		void DeployResultModel<CAnyHyperMesh, CAnyHyperBasinSimulator, hexa_tetra_hyper_model_mesh_tag>(CAnyHyperMesh *resultsimulator);

		/*!
		* \brief 同一个模型的持久化恢复，也支持不同模型的衔接
		* \param hypermeshfile, MODEL对应的分布式文件名称，元数据文件
		* \param HyperMesh 恢复的整体MESH
		* \paramchildren_hypers, 恢复的子MESH模型
		* 
		**/
		template<typename HyperMesh, typename MeshTag>
		void DeployModel(const std::string &hypermeshfile, HyperMesh **initial_hyper, std::vector<HyperMesh *> &refined_hypers);

		//
		//
		//
		/*!
		* 
		**/
		template<typename Simulator>
		void Model2Solution();
		template<>
		void Model2Solution<CAnyHyperBasinSimulator>();

		//
		//
		//
		/*!
		*
		**/
		void Release()
		{
			for(int i = 0; i < m_simulaiton_solutions.size(); i++)
			{
				delete m_simulaiton_solutions[i];
			}
		}

		// rpc interfaces
		int get_solution_number()
		{
			return m_simulaiton_solutions.size();
		}
		DistributedSolution *get_solution(int order)
		{
			return m_simulaiton_solutions[order];
		}

	public:
		//
		//
		//
		/*!
		*
		**/
		static void HexConvert(unsigned long long sourcecode, string &targetcode, long targethex);
		static void GetGeoLocationPointCode(const CGeoPoint<double> &pointlocation, string& locationcode);
		static void GetGeoLocationPolygonCode(const CGeoRect<double> &polylocation, string &locationcode);
		
		/*!
		*
		**/
		void UpdateBlockToSimulator();
		void GetSimulators(std::vector<CAnyHyperMesh*> &simulators);
		void GetUnionMeshAndVertex(std::vector<CAnyHyperMesh*> &simulators, std::vector<std::vector<Vertex3D*> > &vertexs, std::vector<std::vector<Mesh3D*> > &meshes);
		void RecoverMeshidUnionToSingle(std::vector<CAnyHyperMesh *> &simulators);
		void MeshidSingleToUnion(int simulatoroffset, std::vector<CAnyHyperMesh *> &simulators, long &vertexid);
		void MeshidUnionToSingle(int simulatoroffset, std::vector<CAnyHyperMesh *> &simulators, long &vertexid);
		void GetUnionVertexesSimulated(int offseti, int offsetj, int offsetk, std::vector<Vertex3D*> &vertexs, int bottomortop, int colorsource);
		void ClearMemory(int whichlayer, int whichhorizon, int whichstep, bool reusemem = false);
		void LoadFromFile(int whichlayer, int whichhorizon, int whichstep, bool ismini = false, bool reusemem = false);
		void OutPutToFile(int whichlayer, int whichhorizon, int whichstep, string filedir);

	public:
		// the whole geological model
		DistributedModel *m_host_geological_model_impl;
		// one geological model maybe represented by distributed meshes
		ModelSolutionContainer m_simulaiton_solutions;
	};
}

#endif