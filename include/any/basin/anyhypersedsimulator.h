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
#ifndef __ANYBASIN_HYPER_SED_SIMULATOR_H__
#define __ANYBASIN_HYPER_SED_SIMULATOR_H__

//
#include "anybasin.h"

//
#include "any/base/anystl.h"
#include "any/base/anystringbasic.h"
#include "any/base/anydbgmacro.h"
#include "boost/function.hpp"

using namespace AnyBase;

//
namespace AnyBasin
{
	struct SedProgressCallback
	{
		int m_cur;
		int m_total;
		string m_status;
	};

	template<typename Signature>
	struct SedsimProgressCallback : public SedProgressCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};
	/*!
	*
	**/
	class ANYBASIN_CLASS CAnyHyperSedSimulator
	{
	public:
		//
		//
		//
		CAnyHyperSedSimulator(string filename,string outputfile);
		~CAnyHyperSedSimulator();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Prepare();
		void MakeSimulation();

	public:
		std::string m_parameter_file;
		std::string m_input_file;
		std::string m_output_path;

		SedProgressCallback *m_progresscb;
	};

}

#endif