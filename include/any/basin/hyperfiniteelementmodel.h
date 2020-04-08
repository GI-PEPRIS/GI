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
#ifndef __ANYBASIN_HYPER_FINITE_ELEMENT_MODEL_H__
#define __ANYBASIN_HYPER_FINITE_ELEMENT_MODEL_H__

//
#include "anybasin.h"
#include "anyhyperbasinsimulator.h"
#include "hyper data/hyperdata.h"

//
namespace AnyBasin
{
	/*!
	*
	**/
	class CHyperFiniteElementModel
	{
	protected:
		//
		//
		//
		/*!
		*
		**/
		CHyperFiniteElementModel(CAnyHyperBasinSimulator *simulator);
		virtual ~CHyperFiniteElementModel();

	public:
		//
		//
		//
		/*!
		*
		**/
		double MakeFE(int simulationstep, double deltatime, bool isretry = false);
		virtual bool DoInitSimulatorModel();
		virtual void DoInitLeftMatrix();
		virtual bool DoInitLeftMatrix_VertexOffset(int meshoffset, int tetraoffset, \
			int &horizon0, int &horizon1, int &horizon2,int &horizon3,\
			int &vertexoffset0, int &vertexoffset1, int &vertexoffset2, int &vertexoffset3, \
			int &invalidptoffset0, int &invalidptoffset1, int &invalidptoffset2, int &invalidptoffset3);
		virtual double DoInitLeftMatrix_TetraVolume(int meshoffset, int tetraoffset, \
			int horizon0, int horizon1, int horizon2,int horizon3,\
			int vertexoffset0, int vertexoffset1, int vertexoffset2, int vertexoffset3, \
			int invalidptoffset0, int invalidptoffset1, int invalidptoffset2, int invalidptoffset3, \
			int *mp, double *b, double *c, double *d, \
			int &i, int &j, int &k, int &m);
		virtual void DoInitLeftMatrix_Stiffness(int meshoffset, int tetraoffset, int *mp, \
			std::vector<std::vector<HyperSparseBatch::Entry> > &gc_entrys, std::vector<std::vector<HyperSparseBatch::Entry> > &st_entrys, \
			int i, int j, int k, int m, \
			double *b, double *c, double *d, double v) = 0; // gc & st matrix

		virtual void DoInitLeftVector() = 0;
		virtual void DoInitRightVector() = 0;
		virtual void DoSolveModel();
		virtual void DoResetSimulatorModel() = 0;
		virtual double DoCalulateError() = 0;

		//
		//
		//
		/*!
		*
		**/
		void Release();

	public:
		//
		CAnyHyperBasinSimulator *m_simulator;
		CAnyHyperBasinSimulator::HyperModelBasic m_current_simulator_model;

		//
		void *m_global_left_matrix;
		void *m_gc_matrix;
		void *m_st_matrix;
		void *m_l_matrix;
		std::vector<double> m_global_left_vector;
		std::vector<double> m_l_vector;
		std::vector<double> m_r_vector;

		//
		short m_model_type;

	public:
		//
		std::vector<float> m_w1_vector;
		std::vector<float> m_w2_vector;
		std::vector<float> m_w3_vector;
		std::vector<float> m_w4_vector;
		std::vector<float> m_w_vector;
	};

}

#endif
