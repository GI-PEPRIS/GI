/*!
 * The AnyPetro of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * the domain data model etc.
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
#ifndef __ANYPETRO_SHALE_ANALOG_PREDICATOR_H__
#define __ANYPETRO_SHALE_ANALOG_PREDICATOR_H__

// refer to EXPORT etc macro definitions
#include "anypetro.h"
#include "analogpredicator.h"

//
namespace AnyPetro
{
	/*!
	*
	**/
	class ANYPETRO_CLASS CShaleAnalogPredicator : public CAnalogPredicator
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CShaleAnalogPredicator(CAccumulationElement *curElement);
		~CShaleAnalogPredicator();

	public:
		//
		//
		//
		unsigned int Commit(bool isActivity = true);
		bool MakePredication(ResourcePredication &predication,std::vector<CAccumulationElement *> &memVec,std::vector<double>& resultVec);

	protected:
		//
		//
		//
		void LoadFactorScoringData(CAccumulationElement *curElement,ElementVector &eleVec);
		void LoadFactorOriginalData(CAccumulationElement *curElement,ElementVector &eleVec);
		void CalResourceByCluster(std::vector<double>& result); // Calculate an element's resource by the mean resource of the cluster to which the element belongs 
		void InitFactorScoreRange(); // get score range used to normalization


	public:
		//
		string m_factorTemplateName;
	};
}
#endif
