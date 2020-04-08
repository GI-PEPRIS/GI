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
#ifndef __ANYMAP_DECISION_TREE_H__
#define __ANYMAP_DECISION_TREE_H__

// refer to macro
#include "anymap.h"

// refer to its parent
#include "anyviewhook.h"

// refer to geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyMap
{
	/*!
	*
	**/
	class ANYMAP_CLASS CAnyDecisionTree  : public CAnyViewHook
	{
	public:
		/*!
		*
		**/
		enum NodeType
		{
			NT_Unknown = -1,
			NT_Decision,
			NT_Chance,
			NT_Outcome,
			NT_Max
		};

		/*!
		*
		**/
		enum BranchType
		{
			BT_Unknown = -1,
			BT_Decision,
			BT_Chance,
			BT_Max
		};

		// forward structures
		struct TreeNode;
		struct TreeBranch;

		/*!
		*
		**/
		struct TreeNode : public CGeoPoint<double>
		{
			// unique id and encoding code
			int m_idx;
			// node type
			int m_type;
			
			// expected value when making a decision
			double m_decisionValue;
			// before get decision value
			double m_nodeValue;

			// relations
			TreeNode *m_parent;
			std::vector<TreeNode *> m_children;

			// flag for solving
			bool m_isSolved;
			bool m_isGreen;

			// flag for visible
			bool m_isVisible;

			/*!
			*
			**/
			TreeNode() : m_idx(0), m_type(NT_Unknown), m_decisionValue(0.), m_nodeValue(0.), m_parent(0), m_isSolved(false), m_isGreen(false), m_isVisible(true)
			{
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
			// branch type
			int m_type;
			
			// branch description
			string m_description;
			// branch quantification
			double m_value;

			// topological relations
			TreeNode *m_from;
			TreeNode *m_to;
			TreeBranch *m_parent;

			// polyline
			CGeoPoint<double> m_pts[3];

			// flag
			bool m_isGreen;
			bool m_isVisible;

			/*!
			*
			**/
			TreeBranch() : m_type(BT_Unknown), m_description(""), m_value(0.), m_from(0), m_to(0), m_parent(0), m_isGreen(false), m_isVisible(true)
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
		CAnyDecisionTree(CAnyView &curView, int degree);

		/*!
		*
		**/
		virtual ~CAnyDecisionTree();

	public:
		//
		//
		//
		/*!
		*
		**/
		bool InsertNode(TreeNode *parent, TreeNode *child, string &bDescription, double bValue, bool isDirectLevel = false);

		/*!
		*
		**/
		void UpdateBranchType(const TreeNode *node);

		/*!
		*
		**/
		void RemoveNode(TreeNode *node);

		/*!
		*
		**/
		void RemoveSiblingNode(TreeNode *node);

		/*!
		*
		**/
		const TreeNode *FindNode(const CGeoPoint<double> &coord);

		/*!
		*
		**/
		const TreeBranch *FindBranch(const CGeoPoint<double> &coord);

		/*!
		*
		**/
		void MakeLayout(int level);

		//
		//
		//
		/*!
		*
		**/
		int GetNodeLevel(const TreeNode *node);

		/*!
		*
		**/
		int GetNodeCount();

		/*!
		*
		**/
		int GetTreeLevel()
		{
			return m_curLevel;
		}

		/*!
		*
		**/
		int GetSiblingCount(int level);

		/*!
		*
		**/
		const TreeNode *GetSiblingNode(int level, int order);

		//
		// kinds of map operation
		//
		/*!
		*
		**/
		void MoveToPrevious(const TreeNode *curNode);

		/*!
		*
		**/
		void MoveToNext(const TreeNode *curNode);

		/*!
		*
		**/
		void RenderDecisionPath();

		/*!
		*
		**/
		void RenderPartialMap(const TreeNode *curNode);

		/*!
		*
		**/
		void RenderFullMap();

		//
		//
		//
		/*!
		*
		**/
		void Release();

		/*!
		*
		**/
		void Reset(bool isVisible = true);

		/*!
		*
		**/
		void SolvingTree();

		//
 		//
		//
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
		static bool CompareNodeIdx(const TreeNode *first, const TreeNode *second);

		/*!
		*
		**/
		static bool CompareBranchFromIdx(const TreeBranch *first, const TreeBranch *second);

		/*!
		*
		**/
		static bool CompareBranchToIdx(const TreeBranch *first, const TreeBranch *second);

	private:
		//
		//
		//
		/*!
		*
		**/
		void ResetVisibility(bool isVisible);

		/*!
		*
		**/
		void DoSetVisibility(TreeNode *curNode, bool isVisible);

		/*!
		*
		**/
		double DoCalculateXStep();

		//
		//
		//
		/*!
		*
		**/
		bool IsTooShort(CGeoPoint<double> &first, CGeoPoint<double> &second);

		/*!
		*
		**/
		void DoMakeLayout();

		/*!
		*
		**/
		void DoRecursivelyRemoveNode(TreeNode *node);

	private:
		// branch schema
		double m_degree;

		// level indicator
		int m_curLevel;

		// root node
		TreeNode *m_root;

		// container for nodes
		NodeVector m_nodes;

		// container for branches
		BranchVector m_branches;
	};
}
#endif