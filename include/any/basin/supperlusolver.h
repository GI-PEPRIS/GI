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
#ifndef __ANYBASIN_FINITE_ELEMENT_SUPPERLU_SOLVER_H__
#define __ANYBASIN_FINITE_ELEMENT_SUPPERLU_SOLVER_H__

//
#include "anybasin.h"
#include "hyperfiniteelementmodelsolver.h"

//
namespace AnyBasin
{
	class CSupperLUSolver : public CHyperFiniteElementModelSolver
	{
	public:
		CSupperLUSolver(CHyperFiniteElementModel *model);
		~CSupperLUSolver();

	public:
		//
		//
		//
		void SolveMatrix(int N, int vertexcount, int allvertexcount);

	};
}

#endif


