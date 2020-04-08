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
#ifndef __ANYVIS_DECISION_TREE_H__
#define __ANYVIS_DECISION_TREE_H__

// refer to macro
#include "anyvis.h"

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyDecisionTree  : public CAnyViewHook
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

			//2014/10/31
			int m_level;
			int m_childrenDegree;

			double m_childHighY;
			double m_childLowY;

			//2014/11/21:reverse probability mode, for chance node
			bool m_isReverseProbability;
			double m_reverseValue;
			std::string m_code;

			//2015/1/7
			std::string m_name;
			std::string m_reverseName;

			/*!
			*
			**/
			TreeNode() : m_idx(0), m_type(NT_Unknown), m_decisionValue(0.), m_nodeValue(0.), m_parent(0),\
				m_isSolved(false), m_isGreen(false), m_isVisible(true),\
				m_level(0),m_childrenDegree(2),m_childHighY(0.),m_childLowY(0.),\
				m_isReverseProbability(false),m_reverseValue(0.),m_code(""),m_name(""),m_reverseName("")
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

			//2014/11/21:reverse value
			double m_reverseValue;

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
			TreeBranch() : m_type(BT_Unknown), m_description(""), m_value(0.), \
				m_from(0), m_to(0), m_parent(0), m_isGreen(false), m_isVisible(true), m_reverseValue(0.)
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
		void Clone(const CAnyViewHook *prototype);

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
		void Reset(bool isVisible = true, bool isChangeReverse = false);

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

		/*!
		*
		**/
		static bool CompareBranchToLevel(const TreeBranch *first, const TreeBranch *second);

		/*!
		*
		**/
		static bool CompareBranchFromLevel(const TreeBranch *first, const TreeBranch *second);

		//
		//
		//
		/*!
		*2014/10/31
		**/
		int GetLevelNodeCount(int level, std::vector<int> &ids);

		//
		//2014/11/21: reverse probability mode
		//
		/*!
		*
		**/
		bool IsValidReverseProbabilityNode(TreeNode *root);	

		/*!
		*
		**/
		void ChangeNodeReverseProbabilityMode(TreeNode *root);

		/*!
		*
		**/
		void ReverseSolvingTree(TreeNode *root);

	private:
		//
		//2014/11/21: reverse probability mode
		//
		/*!
		*
		**/
		void DoFindChanceNodes(TreeNode *root, std::vector<TreeNode *> &nodes);
		
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

	public:
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

	//private:
		//2014/10/31
		int m_maxId;//record max node's id
	};
}
#endif