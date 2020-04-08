#ifndef __REPORT_FORMAT_GRID_H__
#define __REPORT_FORMAT_GRID_H__
#include "any/base/anystl.h"
// refer to EXPORT etc macroes
#include "anypetro.h"


#include "any/base/agm/reflection.hpp"
using namespace agm::reflection;
// refer to AnyDB relatives
#include "any/db/anyaccessor.h"
using namespace AnyDB;
namespace AnyPetro
{

	class ANYPETRO_CLASS CAnyReportFormatGridData{
	public:

		struct GridCellRecord{
			CLASS(GridCellRecord, agm::reflection::NullClass);
			FIELD2(public,string, m_formatName);
			FIELD2(public,int, m_posX);
			FIELD2(public,int, m_posY);
			FIELD2(public,int, m_type);
			FIELD2(public,int, m_sizeX);
			FIELD2(public,int, m_sizeY);
			FIELD2(public,int, m_rowSize);
			FIELD2(public,int, m_colSize);
			FIELD2(public,int, m_totalHeight);
			FIELD2(public,int, m_totalWidth);
			//FIELD2(public,void*, m_blob);
			FIELD2(public,char*, m_blob);
			int m_length;

			GridCellRecord():m_formatName(""),m_posX(0),m_posY(0),m_type(0),m_sizeX(0),m_sizeY(0),m_rowSize(0),m_colSize(0),m_totalHeight(0),m_totalWidth(0),m_blob(NULL),m_length(0){}
			GridCellRecord(string name,int px,int py,int t,int sx,int sy,int rs,int cs,int th,int tw):m_formatName(name),m_posX(px),m_posY(py),m_type(t),m_sizeX(sx),m_sizeY(sy),m_rowSize(rs),m_colSize(cs),m_totalHeight(th),m_totalWidth(tw),m_blob(NULL),m_length(0){}
			
			~GridCellRecord()
			{
				if(m_blob)
				{
					delete m_blob;
				}
				
			}
			void SetBlob(void* data,int length){
				m_blob=(char*)malloc(length);
				memcpy(m_blob,data,length);
				m_length=length;
			}
			GridCellRecord(const GridCellRecord& other){
				m_formatName=other.m_formatName;
				m_posX=other.m_posX;
				m_posY=other.m_posY;
				m_type=other.m_type;
				m_sizeX=other.m_sizeX;
				m_sizeY=other.m_sizeY;
				m_rowSize=other.m_rowSize;
				m_colSize=other.m_colSize;
				m_totalHeight=other.m_totalHeight;
				m_totalWidth=other.m_totalWidth;
				
				m_length=other.m_length;
				if(other.m_blob)
				{
					m_blob=(char* )malloc(m_length);
					for(int i=0;i<m_length;i++){
						m_blob[i]=other.m_blob[i];
					}
				}
				else
				{
					m_blob=NULL;
				}
				
			}

			const GridCellRecord &operator=(const GridCellRecord &other)
			{
				if(this == &other)
				{
					return *this;
				}
				m_formatName=other.m_formatName;
				m_posX=other.m_posX;
				m_posY=other.m_posY;
				m_type=other.m_type;
				m_sizeX=other.m_sizeX;
				m_sizeY=other.m_sizeY;
				m_rowSize=other.m_rowSize;
				m_colSize=other.m_colSize;
				m_totalHeight=other.m_totalHeight;
				m_totalWidth=other.m_totalWidth;
				m_length=other.m_length;

				if(other.m_blob)
				{
					m_blob=(char* )malloc(m_length);
					for(int i=0;i<m_length;i++){
						m_blob[i]=other.m_blob[i];
					}
				}
				else
				{
					m_blob=NULL;
				}
				return *this;
			}
			/*!
			*
			**/
			void GetMemberAddressVec(std::vector<void*> &memberAddressVec){
				memberAddressVec.push_back(&m_formatName);
				memberAddressVec.push_back(&m_posX);
				memberAddressVec.push_back(&m_posY);
				memberAddressVec.push_back(&m_type);
				memberAddressVec.push_back(&m_sizeX);
				memberAddressVec.push_back(&m_sizeY);
				memberAddressVec.push_back(&m_rowSize);
				memberAddressVec.push_back(&m_colSize);
				memberAddressVec.push_back(&m_totalHeight);
				memberAddressVec.push_back(&m_totalWidth);
			}


		};

		CAnyReportFormatGridData();
		CAnyReportFormatGridData(string name){m_formatName=name;}

		~CAnyReportFormatGridData();
		
		bool Commit();

		bool Load();

		void DoLoad(CAnyAccessor &accessor);

		void Clear();

		void InsertRecord(GridCellRecord& record);

		void GetFormatList(std::vector<string> &vec);

		bool DeleteTemplate(string name);

		void Serials();


	public:
		string m_formatName;
		std::vector<GridCellRecord> m_cellRecordsVec;
	};
}
#endif