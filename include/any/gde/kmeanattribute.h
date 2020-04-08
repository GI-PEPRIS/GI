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
#ifndef __ANYGDE_KMEANATTRIBUTE_H__
#define __ANYGDE_KMEANATTRIBUTE_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include "syntheticwaveletestimator.h"

//
namespace AnyGDE
{
	struct IterProgressCallback
	{
		int m_curiter;
		int m_maxiter;
		string m_status;
	};

	template<typename Signature>
	struct IteratorProgressCallback : public IterProgressCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};
	
	/*!
	*
	**/
	class ANYGDE_CLASS CKmeanAttribute : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CKmeanAttribute();
		~CKmeanAttribute();

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
		void Train_Based_K_Mean_Plus_Plus(std::vector<std::vector<double> > &X, std::vector<double> &Max_Vec, std::vector<double> &Min_Vec, std::vector<double> &Mean_Vec, \
			int Numb_Sample, int Numb_Dimen, int &Numb_Seed, int Max_iter, int Thre, std::vector<int> &RGB_merge, std::vector<std::vector<double> > &Seed, \
			std::vector<std::vector<int> > &RGB_Mat, std::vector<double> &Loc_X, std::vector<double> &Loc_Y);
		void Get_Data_Norm(std::vector<std::vector<double> > &X, std::vector<double> &Max_Vec, std::vector<double> &Min_Vec, int Numb_Sample, int Numb_Dimen, std::vector<std::vector<double> > &X_Norm);
		void Get_Data_Norm(std::vector<double> &X, std::vector<double> &Max_Vec, std::vector<double> &Min_Vec, int Numb_Sample, int Numb_Dimen, std::vector<double> &X_Norm);
		void K_mean_PlusPlus(std::vector<std::vector<double> > &X, int Numb_Sample, int Numb_Dimen, int &Numb_Seed, int Max_iter, int Thre, std::vector<std::vector<double> > &Seed);
		void Get_Projection_Mat(std::vector<std::vector<double> > &X_norm, std::vector<double> &Mean_Vec, int Numb_Dimen, int Numb_Sample, std::vector<std::vector<double> > &P);
		void Get_Loc_Mat(std::vector<std::vector<double> > &Seed, std::vector<std::vector<double> > &P, std::vector<double> &Mean_Vec, int Numb_Seed, int Numb_Dimen, \
			std::vector<int> &RGB_merge, std::vector<std::vector<int> > &RGB_Mat, std::vector<double> &Loc_X, std::vector<double> &Loc_Y);

		void Select_Seed(std::vector<std::vector<double> > &X, int Numb_Sample, int Numb_Dimen, int Numb_Seed, std::vector<std::vector<double> > &Seed, double &crit);
		void Remove_Vec_From_Mat(std::vector<std::vector<double> > &temp1, int N, int M, int K, std::vector<std::vector<double> > &temp2);
		void Loc_Mat_2_HSV(std::vector<std::vector<double> > &Loc_Mat, int Numb_Seed, std::vector<int> &RGB_merge, std::vector<std::vector<int> > &RGB_Mat);
		void HSV2RGB_merge(double H, double S, double V, int &RGB_merge, std::vector<int> &RGB_Mat);
				
		/*!
		*
		**/
		void Generate_Faces_Volume(std::vector<double> &X, std::vector<double> &Min_Vec, std::vector<double> &Max_Vec, std::vector<std::vector<double> > &Seed, std::vector<int> &RGB_merge, \
			std::vector<int> &Discrete_Vec, int Numb_Seed, int &Faces_HSV, int &Faces_Discrete);
		bool Eejcb(std::vector<std::vector<double> > &input, int n, double eps, int jtmin, int jtmax, std::vector<std::vector<double> > &output1, std::vector<std::vector<double> > &output2);
	public:
		std::vector<double> m_Min_Vec;
		std::vector<double> m_Max_Vec;
		std::vector<std::vector<double> > m_Seed;
		std::vector<int> m_RGB_merge;
		std::vector<int> m_Discrete_Vec;
		int m_Numb_Seed;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;

		IterProgressCallback *m_progresscb;
	};
}
#endif
