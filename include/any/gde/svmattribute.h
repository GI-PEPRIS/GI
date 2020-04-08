/*!
 * The AnyGeop of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the key algorithms about geophysics etc.
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
#ifndef __ANYGDE_SVMATTRIBUTE_H__
#define __ANYGDE_SVMATTRIBUTE_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include "syntheticwaveletestimator.h"
#include "svm.h"

//
namespace AnyGDE
{
	struct SvmIterProgressCallback
	{
		int m_curiter;
		int m_maxiter;
		string m_status;
	};

	template<typename Signature>
	struct SvmIteratorProgressCallback : public SvmIterProgressCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};

	/*!
	*
	**/
	class ANYGDE_CLASS CSvmAttribute : public CAnyGdeDataHandler
	{
	public:
		
	public:
		//
		//
		//
		/*!
		*
		**/
		CSvmAttribute();
		~CSvmAttribute();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle(HandlerStruct &handlerstruct);

		/*!
		*
		**/
		void DoGetTraceSample(std::vector<double> &results, int &cmpcount);

		/*!
		*
		**/
		void DoGetTraceHead(std::vector<double> &results);
		
		/*!
		*
		**/
		struct svm_model *SVM_Train(const struct svm_problem *prob, const struct svm_parameter *param);
	public:
		svm_model* m_svm_model;
		std::vector<double> m_X_Mean;
		std::vector<double> m_X_Dev;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;

		SvmIterProgressCallback *m_progresscb;
	};
}
#endif
