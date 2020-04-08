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
#ifndef __ANYGDE_SOMATTRIBUTE_H__
#define __ANYGDE_SOMATTRIBUTE_H__

// refer to export/import macro
#include "anygde.h"
#include "anygdedatahandler.h"
#include "syntheticwaveletestimator.h"

//
namespace AnyGDE
{
	struct SomIterProgressCallback
	{
		int m_curiter;
		int m_maxiter;
		string m_status;
	};

	template<typename Signature>
	struct SomIteratorProgressCallback : public SomIterProgressCallback
	{
		typedef boost::function<Signature> CallbackFunction;
		CallbackFunction m_function;
	};
	
	/*!
	*
	**/
	class ANYGDE_CLASS CSomAttribute : public CAnyGdeDataHandler
	{
	public:
		//
		//
		//
		/*!
		*
		**/
		CSomAttribute();
		~CSomAttribute();

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
		void SeisFaces_Based_SOM2D_TRAIN(std::vector<std::vector<double> > &X, int Numb_Sample, int Numb_Dimen, int Grid_Numb, int Iter_Max, double Radius_initial, double Radius_end,\
			double alpha0, double scale_sigma, int Sample_Order, int proj, std::vector<std::vector<double> > &Unit, std::vector<double> &RGB_merge, std::vector<std::vector<double> > &RGB_Mat, \
			std::vector<double> &X_mean, std::vector<double> &X_Dev, std::vector<double> &Loc_X, std::vector<double> &Loc_Y);
		void Get_Data_Z_Score(std::vector<std::vector<double> > &X, int Numb_Sample, int Numb_Dimen, std::vector<std::vector<double> > &X_Z_Score, std::vector<double> &P1, std::vector<double> &P2, \
			double &sigma_1, double &sigma_2, std::vector<double> &X_mean, std::vector<double> &X_Dev);
		void SOM_2D_TRAIN(std::vector<std::vector<double> > &X_z_score, int Numb_Sample, int Numb_Dimen, std::vector<double> &P1, std::vector<double> &P2, double sigma_1, double sigma_2,\
			int Grid_Numb, int Iter_Max, double Radius_initial, double Radius_end, double alpha0, double scale_sigma, int Sample_Order, int proj, std::vector<std::vector<double> > &Unit, std::vector<double> &RGB_merge,\
			std::vector<std::vector<double> > &RGB_Mat, std::vector<double> &Loc_X, std::vector<double> &Loc_Y);
		void Initial_Unit(double scale_sigma, double sigma_1, double sigma_2, int Grid_Numb, std::vector<double> &P1, std::vector<double> &P2, int Numb_Dimen, \
			std::vector<std::vector<double> > &Unit, int &Numb_Unit, std::vector<double> &POS_X, std::vector<double> &POS_Y);
		bool Eejcb(std::vector<std::vector<double> > &input, int n, double eps, int jtmin, int jtmax, std::vector<std::vector<double> > &output1, std::vector<std::vector<double> > &output2);
		void Cal_Radius_Buff(double r, std::vector<std::vector<double> > &Radius_Buff);
		void Get_BMU(std::vector<std::vector<double> > &Unit, std::vector<double> &x, int Numb_Unit, int Numb_Dimen, std::vector<double> &POS_X, std::vector<double> &POS_Y, int &BMU_X, int &BMU_Y);
		void Get_Search_Region(int BMU_X, int BMU_Y, double r, int Grid_Numb, int &Region_Top_X, int &Region_Bot_X, int &Region_Left_Y, int &Region_Right_Y);
		void Updata_In_Search_Region(int Region_Top_X, int Region_Bot_X, int Region_Left_Y, int Region_Right_Y, std::vector<std::vector<double> > &Unit, std::vector<double> &x, int BMU_X, int BMU_Y, \
			int Grid_Numb, std::vector<std::vector<double> > &Radius_Buff, double r, double alpha);
		void Get_Loc_Mat_2D(std::vector<std::vector<double> > &Unit, std::vector<std::vector<double> > &P, int Numb_Unit, int Numb_Dimen, int proj, std::vector<double> &RGB_merge,\
			std::vector<std::vector<double> > &RGB_Mat, std::vector<double> &Loc_X, std::vector<double> &Loc_Y);
		void SAMMON_MAP_SD(std::vector<std::vector<double> > &Unit, std::vector<std::vector<double> > &P, int Numb_Unit, int Numb_Dimen, int Max_Iter, double TolFun, int MaxHalves, \
			std::vector<std::vector<double> > &Unit_Map);
		void Cal_DIJ(std::vector<std::vector<double> > &Unit, int Numb_Sample, int Numb_Dimen, std::vector<std::vector<double> > &dxij);
		void Cal_E(std::vector<std::vector<double> > &dij, std::vector<std::vector<double> > &dxij, int Numb_Sample, double &E);
		void Cal_OneOrder(std::vector<std::vector<double> > &Unit_Map, std::vector<std::vector<double> > &dij, std::vector<std::vector<double> > &dxij, int p, int q, int Numb_Sample, double &fz, double &fm);
		void Get_Data_Norm(std::vector<std::vector<double> > &X, std::vector<double> &Max_Vec, std::vector<double> &Min_Vec, int Numb_Sample, int Numb_Dimen, std::vector<std::vector<double> > &X_Norm);
		void Loc_Mat_2_HSV(std::vector<std::vector<double> > &Loc_Mat, int Numb_Seed,std::vector<double> &RGB_merge, std::vector<std::vector<double> > &RGB_Mat);
		void HSV2RGB_merge(double H, double S, double V, double &RGB_merge, std::vector<double> &RGB_Mat);

		/*!
		* 
		**/
		void Generate_Faces_Volume_SOM(std::vector<double> &X, std::vector<double> &X_Mean, std::vector<double> &X_Dev, std::vector<std::vector<double> > &Unit, std::vector<double> &RGB_merge, \
			std::vector<int> &Discrete_Vec, int Numb_Unit, int &Faces_HSV, int &Faces_Discrete);
	public:
		std::vector<double> m_X_Mean;
		std::vector<double> m_X_Dev;
		std::vector<std::vector<double> > m_Unit;
		std::vector<double> m_RGB_merge;
		std::vector<int> m_Discrete_Vec;
		int m_Numb_Unit;

		CAnyGeologicalCubeFeature* m_topcubefeature;
		CAnyGeologicalCubeFeature* m_botcubefeature;
		double m_offsettop;
		double m_offsetbot;
		double m_toptime;
		double m_bottime;

		SomIterProgressCallback *m_progresscb;
	};
}
#endif
