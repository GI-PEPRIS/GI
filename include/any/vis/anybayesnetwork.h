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
#ifndef __ANYVIS_BAYES_NETWORK_H__
#define __ANYVIS_BAYES_NETWORK_H__

// refer to macro
#include "anyvis.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to dlib directed graph
#include "dlib/directed_graph.h"
using namespace dlib;

#include "dlib/bayes_utils.h"
using namespace bayes_node_utils;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyBayesNetwork  : public CAnyViewHook
	{
	public:
		// bayesian network
		typedef directed_graph<bayes_node, unsigned short>::kernel_1a DirectedGraph;

	public:
		/*!
		*
		**/
		enum MapOperation
		{
			MO_Default			= 1,
			MO_Node				= 1 << 1,
			MO_Pan					= 1 << 2,
			MO_Pick				= 1 << 3,		// 
			MO_Condition			= 1 << 4,		// create a node
		};

		/*!
		*
		**/
		struct TreeNode : public CGeoPoint<double>
		{
			// for directed acyclic graph
			int m_idx;
			// name and posterior probability
			string m_name;

			// prior and posterior 
			std::vector<string> m_states;
			double *m_priors;						// specified priority for current states
			double *m_posteriors;				// inferenced for current states
			
			// prior probabilities against all parent states
			// 00(parents)0(itself), 011, 100, ...
			int m_parents;
			double *m_settings;					
			char **m_descs;

			// current state
			int m_stateIdx;

			// is hidden for moving
			bool m_isHidden;
			bool m_isEvidence;
			bool m_isWarning;

			//2015/1/27: can be deleted ?
			bool m_isDeletable;

			/*!
			*
			*/
			TreeNode() : m_idx(0), m_name(""), m_priors(0), m_posteriors(0), \
				m_parents(0), m_settings(0), m_descs(0), m_stateIdx(-1), \
				m_isHidden(false), m_isEvidence(false), m_isWarning(false), m_isDeletable(true)
			{
			}

			/*!
			*
			**/
			~TreeNode()
			{
				if(m_priors)
				{
					::free(m_priors);
				}

				if(m_posteriors)
				{
					::free(m_posteriors);
				}

				if(m_settings)
				{
					::free(m_settings);
				}

				if(m_descs)
				{
					int count = 1 << (m_parents+1);
					int i = 0;
					for(; i < count; i++)
					{
						::free(m_descs[i]);
					}
					::free(m_descs);
				}
			}
		};
		typedef std::vector<TreeNode *> NodeVector;
		typedef NodeVector::iterator node_itr;
		typedef NodeVector::const_iterator node_citr;

		/*!
		*
		**/
		struct TreeBranch
		{
			// TOPO:
			// ...
			TreeNode *m_from;
			TreeNode *m_to;

			// is hidden
			bool m_isHidden;

			/*!
			*
			**/
			TreeBranch() : m_from(0), m_to(0), m_isHidden(false)
			{
			}
		};
		typedef std::vector<TreeBranch *> BranchVector;
		typedef BranchVector::iterator branch_itr;
		typedef BranchVector::const_iterator branch_citr;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyBayesNetwork(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyBayesNetwork();

	public:
		//
		//
		//
		/*!
		*
		**/
		void Clone(const CAnyViewHook *prototype);

		//
		//
		//
		/*!
		*
		**/
		long GetNextIdx();

		/*!
		*
		**/
		bool InsertNode(TreeNode *oneNode);

		/*!
		*
		**/
		bool InsertEdge(TreeNode *parent, TreeNode *child);

		/*!
		*
		**/
		TreeNode *FindNode(const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		TreeBranch *FindBranch(const CGeoPoint<double> &scrPt);

		/*!
		*
		**/
		void RemoveNode(TreeNode *node);

		/*!
		*2015/5/21
		**/
		bool RemoveBranch(TreeBranch *branch);

		/*!
		*
		**/
		int GetParentCount(TreeNode *node);

		/*!
		*
		**/
		TreeNode *GetParentNode(int order);

		/*!
		*
		**/
		bool IsValidNetwork();

		/*!
		*
		**/
		int GetNodeCount();

		/*!
		*
		**/
		const TreeNode *GetNode(int order);

		//
		//
		//
		/*!
		*
		**/
		void MakeBayesNetwork();

		/*!
		*2015/1/29
		**/
		void DoMakeBayesNetwork(DirectedGraph *bn, NodeVector &nodes, BranchVector &branches);

		/*!
		* given its parent's current state
		**/
		bool SetProbability(TreeNode *node, int stateIdx, double probability, const char *const desc = "");

		/*!
		*
		**/
		void SetState(TreeNode *node, int stateIdx);

		/*!
		*
		**/
		void AsEvidence(TreeNode *node, bool isEvidence = true);

		/*!
		*
		**/
		void Release();

		//
		//
		//
		/*!
		*
		**/
		void MakeExactInference();

		/*!
		*
		**/
		void MakeApproximateInference(int rounds = 2000);

		//
 		//
		//
		/*!
		*
		**/
		void SetMapOperation(unsigned int op);

		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseMove(const CGeoPoint<double> &scrPoint);

		/*!
		*
		*/
		bool MouseUp(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		bool DoubleClick(const CGeoPoint<double> &scrPoint);

		/*!
		*
		**/
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);

		//
		//
		//
		/*!
		*
		**/
		void GetSubNetworks(std::vector<NodeVector> &nodeVec, std::vector<BranchVector> &branchVec);

		//
		//2015/5/14: boost layout
		//
		/*!
		*
		**/
		bool BoostLayout(short type);

		/*!
		*
		**/
		TreeNode *GetNodeByIdx(int idx);

	private:
		//
		//
		//
		/*!
		*
		**/
		bool IsSetProbability();

		/*!
		*
		**/
		bool IsHasOrphan();

		/*!
		*
		**/
		bool IsOrphanNode(const TreeNode *curNode);

		/*!
		*
		**/
		bool IsHasCyclic();

		/*!
		*
		**/
		bool IsExistEdge(TreeNode *parent, TreeNode *child);

		/*!
		*
		**/
		void DoHideBranches(TreeNode *curNode, bool isHidden = true);

		/*!
		*
		**/
		void DoRenderPicked(CAnyCanvas &canvas);

		/*!
		*
		**/
		void DoRemoveBranches(TreeNode *node, bool asParent = true);

		//
		//
		//
		/*!
		*
		**/
		static bool CompareNodeIdx(const TreeNode *first, const TreeNode *second);

		/*!
		*
		**/
		static bool CompareBranchChildIdx(const TreeBranch *first, const TreeBranch *second);

		/*!
		*
		**/
		static bool CompareBranchParentIdx(const TreeBranch *first, const TreeBranch *second);

		/*!
		*
		**/
		static void ToBinaryString(int n, char *str);
		
		//
		//
		//
		/*!
		* given its parent's current state
		**/
		bool DoSetProbability(DirectedGraph *bn, NodeVector &nodes, TreeNode *node, int stateIdx, double probability, const char *const desc = "");

		/*!
		*
		**/
		void DoSetState(DirectedGraph *bn, TreeNode *node, int stateIdx);

		/*!
		*
		**/
		void DoAsEvidence(DirectedGraph *bn, NodeVector &nodes, TreeNode *node, bool isEvidence = true);

		/*!
		*
		**/
		bool DoIsOrphanNode(DirectedGraph *bn, NodeVector &nodes, const TreeNode *curNode);

		/*!
		*
		**/
		int DoGetParentCount(TreeNode *node, BranchVector &branches);

		/*!
		*
		**/
		TreeNode *DoGetParentNode(int order, NodeVector &nodes);

	public:
		// map operation 
		unsigned int m_operation;

		// bayesian network
		DirectedGraph m_bn;
		// node indices
		NodeVector m_nodes;
		// branch indices
		BranchVector m_branches;

		// parent idxes 
		std::vector<unsigned long> m_parentIdxes;

		// current node
		TreeNode *m_curNode;
		// for creation of directed branch
		TreeNode *m_parent;
		TreeNode *m_child;
		CGeoPoint<double> m_start;
		CGeoPoint<double> m_end;
	};
}
#endif