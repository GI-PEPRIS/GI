/*!
 * The AnyVis of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * kinds of information visualization etc.
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
#ifndef __ANYPORTFOLIO_REPOSITORY_H__
#define __ANYPORTFOLIO_REPOSITORY_H__

// refer to its parent as one of accumulation activities
#include "anyscenariosolutiongenerator.h"

// namespace
namespace AnyPortfolio
{
	class ANYPORTFOLIO_CLASS CAnyRepository
	{
		public:
			//
			struct RepositoryElementRecord : public CAnyGeneticSolutionGenerator::RepositoryRecord
			{
				//repository id
				long m_repositoryId;
				//
				short m_elementType;
				//
				string m_whodo;
				//
				double m_whendo;

				/*!
				*
				**/
				RepositoryElementRecord()
				{
					//parent
					m_elementid = 0;	

					//
					m_matureType = "";
					m_depthType = "";
					m_trapType = "";
					m_resourceType = "";
					m_fieldType = "";

					//
					m_expInvestment = 0.;
					m_devInvestment = 0.;
					m_resource = 0.;
					m_npv = 0.;
					m_geoRisk = 0.;
					m_ecoRisk = 0.;
					m_engRisk = 0.;
					m_minWeight = 0.;
					m_rtWeight = 0.;
					m_maxWeight = 1.;

					//
					m_exp = 0.;
					m_rov = 0.;

					//itself
					m_repositoryId = 0;
					m_elementType = 0;
					m_whodo = "";
					m_whendo = 0.;
				}

				/*!
				*
				**/
				const RepositoryElementRecord &operator=(const RepositoryElementRecord &other)
				{
					if (this == &other)
					{
						return *this;
					}

					//parent
					m_elementid = other.m_elementid;	

					//
					m_matureType = other.m_matureType;
					m_depthType = other.m_depthType;
					m_trapType = other.m_trapType;
					m_resourceType = other.m_resourceType;
					m_fieldType = other.m_fieldType;

					//
					m_expInvestment = other.m_expInvestment;
					m_devInvestment = other.m_devInvestment;
					m_resource = other.m_resource;
					m_npv = other.m_npv;
					m_geoRisk = other.m_geoRisk;
					m_ecoRisk = other.m_ecoRisk;
					m_engRisk = other.m_engRisk;
					m_minWeight = other.m_minWeight;
					m_rtWeight = other.m_rtWeight;
					m_maxWeight = other.m_maxWeight;

					//
					m_exp = other.m_exp;
					m_rov = other.m_rov;

					//itself
					m_repositoryId = other.m_repositoryId;
					m_elementType = other.m_elementType;
					m_whodo = other.m_whendo;
					m_whendo = other.m_whendo;

					return *this;
				}


			};
			typedef std::vector<RepositoryElementRecord> RepositoryElementVector;
			typedef RepositoryElementVector::iterator re_itr;
			typedef RepositoryElementVector::const_iterator re_citr;

			//
			struct RepositoryActivityRecord
			{
				//practice id
				long m_practiceId;
				//repository id
				long m_repositoryId;
				//group id
				long m_groupId;

				//invest rate
				double m_investRate;

				//values
				double m_xValue;
				double m_yValue;
				long m_xValueType;

				//
				bool m_isApproved;

				/*!
				*
				**/
				RepositoryActivityRecord(): m_practiceId(0), m_repositoryId(0), m_groupId(0), m_investRate(0.), \
					m_xValue(0.), m_yValue(0.), m_xValueType(0), m_isApproved(false)
				{

				}

				const RepositoryActivityRecord &operator=(const RepositoryActivityRecord &other)
				{
					if (this == &other)
					{
						return *this;
					}

					m_practiceId = other.m_practiceId;
					m_repositoryId = other.m_repositoryId;
					m_groupId = other.m_groupId;

					m_investRate = other.m_investRate;

					m_xValue = other.m_xValue;
					m_yValue = other.m_yValue;
					m_xValueType = other.m_xValueType;

					m_isApproved = other.m_isApproved;

					return *this;
				}
			};

			typedef std::vector<RepositoryActivityRecord> RepositoryActivityVector;
			typedef RepositoryActivityVector::iterator ra_itr;
			typedef RepositoryActivityVector::const_iterator ra_citr;
		public:
			//
			//
			//
			/*!
			*
			**/
			CAnyRepository();

			/*!
			*
			**/
			~CAnyRepository();

		public:
			//
			//
			//
			/*!
			*
			**/
			void LoadRepositoryRecords(long type, const std::string &whodo);

			/*!
			*
			**/
			unsigned int CommitRepositoryRecords(const RepositoryElementVector &records);

			/*!
			*
			**/
			const RepositoryElementVector &GetRepositoryRecords();

			/*!
			*
			**/
			void SetRepositoryRecords(const RepositoryElementVector &records);

			//
			//
			//
			/*!
			*
			**/
			unsigned int CommitActivityRepositoryRecords(long practiceId, const RepositoryActivityVector &records);

			/*!
			*
			**/
			void LoadActivityRepositoryRecords(long practiceId);

			/*!
			*
			**/
			const RepositoryActivityVector &GetActivityRepositoryRecords();
		private:
			/*!
			*
			**/
			void DoLoadRepositoryRecords(CAnyAccessor &accessor, RepositoryElementVector &records);

			/*!
			*
			**/
			void DoLoadActivityRepositoryRecords(CAnyAccessor &accessor, RepositoryActivityVector &records);
		private:
			//
			RepositoryElementVector m_repositoryRecords;

			RepositoryActivityVector m_activityRecords;
	};
}
#endif