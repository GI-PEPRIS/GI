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
#ifndef __ANYDEEPLEARNING_XGBOOST_H__
#define __ANYDEEPLEARNING_XGBOOST_H__

#include "anylearning.h"

#include "any/base/anystl.h"
using namespace std;

namespace AnyLearning
{
	/*!
	* 
	**/
	class ANYLEARNING_CLASS CAnyXGBooster
	{
	public:
		//
		//
		//
		CAnyXGBooster();
		~CAnyXGBooster();

	public:
		//
		//
		//
		/*!
		*
		**/
		int CreateTrainingMatrixFromVector(float *data, long nrow, long ncol, float missing);
		int SetMatrixMetaInfo(const char *field, float *info, long len);
		int GetMatrixMetaInfo(const char *field, long &bst_result, const float *&out_floats);

		//
		//
		//
		/*!
		*
		**/
		int CreateBooster();
		int SetBoosterParam(const char *name, const char *value);
		int UpdateBooster(int iterations);

		//
		//
		//
		/*!
		*
		**/
		int CreateTestMatrixFromVector(float *data, long nrow, long ncol, const float missing);
		int BoosterPredict(long &out_len, const float *&out_result);

	public:
		//
		void *m_h_train[1];
		void *m_h_test;
		void *m_h_booster;

	};
}


#endif