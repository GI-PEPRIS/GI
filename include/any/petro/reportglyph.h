#ifndef __REPORT_GLYPH_H__
#define __REPORT_GLYPH_H__
#include "any/base/anystl.h"
// refer to EXPORT etc macroes
#include "anypetro.h"
namespace AnyPetro
{
	enum ReportNodeType{
		Report_Vertical,
		Report_Horizontal,
		Report_Text,
		Report_Image,
		Report_Grid,
	};

	class ANYPETRO_CLASS CAnyReportTree{
	public:

		struct ReportNode  
		{
			ReportNode(){;}
			ReportNode(int nodeType,int x,int y,int totalWidth,ReportNode* parent=NULL){
				m_nodeType=nodeType;
				m_parent=parent;
				m_width=x;
				m_height=y;
				m_totalWidth=totalWidth;
			}
			virtual ~ReportNode(){
			}
			int m_nodeType;
			ReportNode* m_parent;
			std::vector<ReportNode*> m_children;
			int m_height;
			int m_width;
			int m_totalWidth;
		};

		struct VerticalNode: public ReportNode{
			VerticalNode();

			virtual ~VerticalNode(){
				for(int i=0;i<m_children.size();i++){
					delete m_children[i];
				}
				m_parent=NULL;
			};
			VerticalNode(int nodeType,int x,int y,int totalWidth,ReportNode* parent=NULL):ReportNode(nodeType,x,y,totalWidth,parent){
			}
		};

		struct HorizontalNode: public ReportNode{
			HorizontalNode();
			virtual ~HorizontalNode(){
				for(int i=0;i<m_children.size();i++){
					delete m_children[i];
				}
				m_parent=NULL;
			};
			HorizontalNode(int nodeType,int x,int y,int totalWidth,ReportNode* parent=NULL):ReportNode(nodeType,x,y,totalWidth,parent){
				m_nodeType=nodeType;
				m_parent=parent;
			}
		};

		struct TextNode: public ReportNode{
			TextNode();
			
			TextNode(int nodeType,string text,int x,int y,int totalWidth,ReportNode* parent=NULL):ReportNode(nodeType,x,y,totalWidth,parent){
				m_text=text;
			}
			virtual ~TextNode(){
				for(int i=0;i<m_children.size();i++){
					if(m_children[i])
					{
						delete m_children[i];
					}
				}
				m_parent=NULL;
			};
			string m_text;
		};

		struct ImageNode: public ReportNode{
			ImageNode();
			virtual ~ImageNode(){
				/*if(m_image)
				{
				delete m_image;
				}*/
				for(int i=0;i<m_children.size();i++){
					if(m_children[i])
					{
						delete m_children[i];
					}
				}
				m_parent=NULL;
			};
			ImageNode(int nodeType,void* bmp,int x,int y,int totalWidth,ReportNode* parent=NULL):ReportNode(nodeType,x,y,totalWidth,parent){
				m_image=bmp;
			}
			void* m_image;
		};
		struct GridNode: public ReportNode{
			GridNode();
			GridNode(int nodeType,int rowNum,int colNum,std::vector<string>& data,std::vector<string>& labelData,std::vector<int>& labelSize,int x,int y,int totalWidth,ReportNode* parent=NULL):ReportNode(nodeType,x,y,totalWidth,parent){
				m_rowNum=rowNum;
				m_colNum=colNum;
				m_data=data;
				m_colLabel=labelData;
				m_labelSize=labelSize;
			}
			virtual ~GridNode(){
				for(int i=0;i<m_children.size();i++){
					if(m_children[i])
					{
						delete m_children[i];
					}
				}
				m_parent=NULL;
			};
			int m_rowNum;
			int m_colNum;
			std::vector<string> m_data;
			std::vector<string> m_colLabel;
			std::vector<int> m_labelSize;
		};

	public:
		CAnyReportTree(ReportNode* root);
		~CAnyReportTree();
		bool Insert(ReportNode* node);
		bool Parent();
		bool Child(int index);
		ReportNode* m_root;
		ReportNode* m_current;
	};
}
#endif