/*!
 * The AnyBridge of PetroCOVERY Solution is a collection of native C++ classes that implement 
 * rendering pipeline and key display implementatios etc.
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
#ifndef __ANYBRIDGE_TOKENIZER_H__
#define __ANYBRIDGE_TOKENIZER_H__

// refer to EXPORT and IMPORT
#include "anybridge.h"
// refer to datamodel
#include "anybridgedatamodel.h"

// refer to STL
#include "any/base/anystl.h"
#include "any/base/anyfilebasic.h"
using namespace AnyBase;

// namepspace
namespace AnyBridge
{
	/*!
	*
	**/
	class ANYBRIDGE_CLASS CAnyTokenizer
	{
	public:

		/*!
		*
		**/
		enum FunctorType
		{
			FT_Unknown = -1,
			FT_TOKEN,
			FT_Max
		};

		/*!
		*
		**/
		struct BlockDescription
		{
			// block indicator
			string m_indicator;
			// block content
			string m_content;
			// block token
			string m_token;
			// position in file
			int m_offset;
			// line position in file
			int m_lineoffset;
			// number of lines
			int m_lines;
		};

		// Blocks
		typedef std::vector<BlockDescription> BlockVector;
		typedef BlockVector::const_iterator blk_citr;
		typedef BlockVector::iterator blk_itr;

		class GetDataTask : public CAnySignalTask<void()>, public JTCMonitor
		{
		public:
			GetDataTask(int taskcount, int index, CAnyTokenizer *parent, std::vector<int> &startoffsets, \
				std::vector<int> &endoffsets, char* data, CAnyCPUScheduler *scheduler);
			~GetDataTask();
			void DoExecuteTask();
			int m_taskcount;
			int m_index;
			CAnyTokenizer *m_parent;
			std::vector<int> m_startoffsets;
			std::vector<int> m_endoffsets;
			char* m_data;
			CAnyCPUScheduler *m_scheduler;
		};

	public:
		/*!
		*
		**/
		CAnyTokenizer(const string &fileName);

		/*!
		*
		**/
		virtual ~CAnyTokenizer();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool IsValid();

		/*!
		*
		**/
		void AddBlockDescription(const BlockDescription &blk);

		/*!
		*
		**/
		void EraseBlockDescription(const BlockDescription &blk);

		/*!
		*
		**/
		bool GetBlockDescription(const string &indicator, BlockDescription &blockdescription);

		/*!
		* indicators empty means to load all blocks
		**/
		bool Load(const std::vector<string> &indicators, const std::vector<string> &tokens);

		/*!
		* against kinds of tokenizing strategies 
		**/
		virtual int Extract(long elementid, long classid, int num = 0, int startline = 0, int endline = -1) = 0;

		//
		//
		//
		/*!
		*
		**/
		void SwitchFile(const string &otherFile)
		{
			m_fileName = otherFile;
		}

		/*!
		*
		**/
		bool Open();

		/*!
		*
		**/
		void Close();

		/*!
		* move to first block
		**/
		bool MoveFirst(const string &indicator);

		/*!
		* next block
		**/
		bool MoveNext();

		/*!
		* tokenize current block
		**/
		template<typename T, typename Children>
		void Tokenize(Children &decorator, const string &indicator, const int &blockorder = 0, const bool frombegin = false, int startline = 0, int endline = -1)
		{
			if(!frombegin)
			{
				// prepare
				BlockDescription curBlock;
				if(!GetBlockDescription(indicator, curBlock))
					return;
				CAnyTokenString curToken;
				curToken.SetToken(curBlock.m_token.c_str());
				// loop
				string curLine;
				if(MoveFirstLine(indicator, curLine, blockorder))
				{
					int linecount = 0;
					while(MoveNextLine(curLine))
					{
						if(m_functorMap[FT_TOKEN] != NULL)
							(*m_functorMap[FT_TOKEN])(true, curBlock.m_lines, linecount);
						if(IsBlockLine(curLine))
							break;
						if(IsCommentLine(curLine))
							continue;
						if(IsEmptyLine(curLine))
							continue;
						curToken.Trim(curLine.c_str(), curLine.size());
						decorator.Bind<T>(curToken);
						linecount++;
					}
					if(m_functorMap[FT_TOKEN] != NULL)
						(*m_functorMap[FT_TOKEN])(false, -1, -1);
				}
			}
			else
			{
				// loop
				string curLine;
				for(int i = 0; i < startline; i++)
					MoveNextLine(curLine);
				int lineflag = startline;
				int totallines = 0;
				if(m_ismultiline)
				{
					for(int i = 0; i < m_datalinesMT.size(); i++)
						totallines += m_datalinesMT[i].size();
				}
				else
					totallines = m_datalines.size();
				while(MoveNextLine(curLine))
				{
					if(endline >= 0 && lineflag + endline >= totallines && totallines > 0)
						break;
					lineflag++;
					if(IsBlockLine(curLine))
						break;
					if(IsCommentLine(curLine))
						continue;
					if(IsEmptyLine(curLine))
						continue;
					CAnyTokenString curToken;
					curToken.SetToken(" ");
					curToken.Trim(curLine.c_str(), curLine.size());
					decorator.Bind<T>(curToken);
				}
			}
		}
		
		/*!
		*
		**/
		bool RegisterFunctor(int type,CAnyFunctor *func);

		/*!
		*
		**/
		bool RemoveFunctor(int type);

	public:
		//
		//
		//
		/*!
		*
		**/
		bool MoveFirstLine(const string &whichPart, string &curLine, const int &blockorder = 0);

		/*!
		*
		**/
		bool MoveNextLine(string &curLine);

		/*!
		*
		**/
		virtual  bool IsCommentLine(const string &curLine) = 0;

		/*!
		*
		**/
		virtual  bool IsBlockLine(const string &curLine) = 0;

		/*!
		*
		**/
		virtual  bool IsEmptyLine(const string &curLine) = 0;
	public:
		// file name including the whole path
		string m_fileName;

		//File basic functions
		const CAnyFileBasic &m_fileBasic;

		// File handle
		void *m_fileHandle;

		// kinds of block parts
		BlockVector m_blocks;

		// call back funtions
		std::map<int,CAnyFunctor*> m_functorMap;

		// cache
		bool m_ismultiline;
		std::vector<string> m_datalines;
		std::vector<std::vector<string> > m_datalinesMT;
		int m_curdataline;
		int m_curdataMToffset;
	};
}
#endif
