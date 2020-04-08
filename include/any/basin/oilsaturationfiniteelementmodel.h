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
#ifndef __ANYBASIN_HYPER_OIL_SATURATION_FINITE_ELEMENT_MODEL_H__
#define __ANYBASIN_HYPER_OIL_SATURATION_FINITE_ELEMENT_MODEL_H__

//
#include "anybasin.h"
#include "hyperfiniteelementmodel.h"

namespace AnyBasin
{
	/*!
	*
	**/
	class COilSaturationFiniteElementModel : public CHyperFiniteElementModel
	{
	public:
		//
		enum SaturationType
		{
			ST_Water,
			ST_Oil,
			ST_Gas
		};

	public:
		COilSaturationFiniteElementModel(CAnyHyperBasinSimulator *simulator, short staturation_type);
		~COilSaturationFiniteElementModel();

	public:
		//
		//
		//
		bool DoInitSimulatorModel();
		void DoInitLeftMatrix_Stiffness(int meshoffset, int tetraoffset, int *mp, \
			std::vector<std::vector<HyperSparseBatch::Entry> > &gc_entrys, std::vector<std::vector<HyperSparseBatch::Entry> > &st_entrys, \
			int i, int j, int k, int m, \
			double *b, double *c, double *d, double v);
		void DoInitLeftVector();
		void DoInitRightVector();
		double DoCalulateError();
		void DoResetSimulatorModel();

	public:
		//
		unsigned char m_saturation_type;
	};
}

#endif
