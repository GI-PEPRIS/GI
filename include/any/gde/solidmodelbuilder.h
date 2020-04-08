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
#ifndef __ANYGDE_SOLID_MODEL_BUILDER_H__
#define __ANYGDE_SOLID_MODEL_BUILDER_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"

//
namespace AnyGDE
{
	/*!
	*
	**/
	class ANYGDE_CLASS CSolidModelBuilder
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CSolidModelBuilder();
		~CSolidModelBuilder();

	public:
		//
		//
		//
		/*!
		*
		**/
		void DoHandle();
	public:
		std::vector<std::vector<std::vector<double> > > m_Hor_buff;
		double m_Top_offset;
		double m_Bot_offset;
		std::vector<int> m_stratigraphy_choice;
		double m_Int_sample;
		int m_min_inline;
		int m_min_xline;
		int m_start_inline;
		int m_end_inline;
		int m_start_xline;
		int m_end_xline;
		std::vector<string> m_horizonnames;

		string m_outputname;
	};
}
#endif
