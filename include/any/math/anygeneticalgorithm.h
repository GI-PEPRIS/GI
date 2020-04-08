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
#ifndef __ANYMATH_GENETIC_ALGORITHM_H__
#define __ANYMATH_GENETIC_ALGORITHM_H__

#include "anymath.h"
#include "yanqi/GA.h"

//
namespace AnyMath
{
	/*!
	*
	**/
	class ANYMATH_CLASS CAnyGeneticAlgorithm
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyGeneticAlgorithm()
		{

		}
		~CAnyGeneticAlgorithm()
		{

		}

	public:
		//
		//
		//
		/*!
		*
		**/
		void AddVariable(double min, double max, short precision)
		{
			m_population.Add_Variable(min, max, precision);
		}
		void AddUserData(int number, double *samples)
		{
			m_population.Add_UserData(number, samples);
		}
		void SetObjectFunction(GA_ObjFunction objfunction)
		{
			m_population.ObjFun = objfunction;
		}
		void SetFitnessFunction(GA_ObjFunValueToFitness fitfunction)
		{
			m_population.CalculateFitness = fitfunction;
		}
		void SetCheckFunction(GA_ParametersIsAvailable checkfunction)
		{
			m_population.ParametersIsAvailable = checkfunction;
		}
		void SetPrecisionFunction(GA_CalPrecisionValue precisionfunction)
		{
			m_population.CalPrecisionValue = precisionfunction;
		}

		//
		//
		//
		void SetInitialPopulation(int number)
		{
			m_population.CreateInitialPopulation(number);
		}
		void Execute(std::vector<double> &opts, double &objvalue, double &fitness)
		{
			m_population.Main();

			opts.clear();
			for(int i = 0; i < m_population.Vb.size(); i++)
			{
				opts.push_back(m_population.BestIndividal->V[i].v);
			}

			objvalue = m_population.BestIndividal->ObjFunctionValue;
			fitness = m_population.BestIndividal->Fitness;
		}
		
	private:
		GA_Population m_population;
	};

}

#endif