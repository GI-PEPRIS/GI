/*!
 * The AnySDB of PetroCOVERY solution is a collection of packages based on native C++ classes
 * that implement the fundamental algorithms & operations required to satisfy management 
 * and rendering of geometries being a leading one.
 *
 * Copyright (C) 2015 Xiujie Sheng
 *
 * This library isn't a free software, so you cann't take the sourcecode without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will harm your computer or ongoing business 
 * if you illegally got it. 
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
#ifndef __ANYDEEPLEARNING_LOGISTIC_H__
#define __ANYDEEPLEARNING_LOGISTIC_H__

#include "anylearning.h"

#include "any/base/anystl.h"
using namespace std;

namespace AnyLearning
{
	/*!
	* data cube in memory, as part of distributed data cube in future
	**/
	class ANYLEARNING_CLASS CAnyLogistic
	{
	public:
		//
		//
		//
		CAnyLogistic();
		~CAnyLogistic();

	public:
		//
		// meta data of current cube
		//
		void DoHandle();
		void Dologistic(std::vector<std::vector<double> > &data, std::vector<double> &beta);
		void lnL(std::vector<double> &Y, std::vector<std::vector<double> > &X, std::vector<std::vector<double> > &bb, std::vector<double> &lL);
		void gradHessian(std::vector<double> &Y, std::vector<std::vector<double> > &X, std::vector<double> &beta, std::vector<double> &L, std::vector<std::vector<double> > &H);
		void GetResult(std::vector<std::vector<double> > &curvedatas, std::vector<double> &betas, std::vector<double> &results);
		
	public:
		std::vector<double> m_Y;
		std::vector<std::vector<double> > m_datas;
		std::vector<double> m_beta;
	};
}


#endif