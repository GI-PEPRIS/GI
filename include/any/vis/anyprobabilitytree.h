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
#ifndef __ANYVIS_PROBABILITY_TREE_H__
#define __ANYVIS_PROBABILITY_TREE_H__

// refer to macro
#include "anyvis.h"

// refer to geopoint
#include "any/base/anygeom.h"
using namespace AnyBase;

// refer to its parent
#include "any/map/anyviewhook.h"
using namespace AnyMap;

//
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyProbabilityTree  : public CAnyViewHook
	{
	public:
		/*!
		*
		**/
		enum ProbabilityType
		{
			PT_Unknown = -1,
			PT_Equal,
			PT_Bernoulli,
			PT_Independence,
			PT_Dependence,
			PT_Max
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
			
			// 'F' or 'S' combination
			string m_description;
			double m_value;

			// relations
			TreeNode *m_parent;
			std::vector<TreeNode *> m_children;

			// flag for solving
			bool m_isSolved;
			bool m_isGreen;

			//current level
			int m_level;

			//2014/11/5
			int m_childrenDegree;
			double m_childHighY;
			double m_childLowY;

			//2014/11/18: 00,01,10,11...
			string m_code;

			/*!
			*
			**/
			TreeNode() : m_idx(0), m_parent(0), m_isSolved(false), m_isGreen(false), m_description(""), m_value(0.),\
				m_level(0),m_childrenDegree(2),m_childHighY(0.),m_childLowY(0.),m_code("")
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
			// branch description
			string m_description;
			// branch quantification
			double m_value;

			//2014/11/18: reverse value
			double m_reverseValue;

			// topological relations
			TreeNode *m_from;
			TreeNode *m_to;
			TreeBranch *m_parent;

			// polyline
			CGeoPoint<double> m_pts[2];

			// flag
			bool m_isGreen;

			/*!
			*
			**/
			TreeBranch() : m_description(""), m_value(0.), m_from(0), m_to(0), m_parent(0), m_isGreen(false),m_reverseValue(0.)
			{
			}
		};
		typedef std::vector<TreeBranch *> BranchVector;
		typedef BranchVector::iterator branch_itr;
		typedef BranchVector::const_iterator branch_citr;

		/*!
		*
		**/
		struct SamplePoint
		{
			// FTTTFF...
			string m_description;
			double m_probability;

			SamplePoint() : m_description(""), m_probability(0.)
			{
			}

			const SamplePoint &operator=(const SamplePoint &other)
			{
				if(this == &other)
				{
					return *this;
				}

				m_description = other.m_description;
				m_probability = other.m_probability;

				return *this;
			}
		};
		typedef std::vector<SamplePoint> SampleVector;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyProbabilityTree(CAnyView &curView);

		/*!
		*
		**/
		virtual ~CAnyProbabilityTree();

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
		* asAlgorithm means not to render and directly calculate
		**/
		void InsertProbabilityLevel(string &name, unsigned short type, double upProbability = 1.0, bool asAlogrithm = false, int childrenDegree = 2);

		/*!
		*
		**/
		void RemoveProbabilityLevel(int level = -1);

		/*!
		*
		**/
		void Release();

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
		void UpdateBranch(const TreeBranch *branch);

		/*!
		* 2014.8.20 update branches with 2 more degrees
		**/
		void UpdateBranch(const TreeBranch *branch, std::vector<double> &vals);

		/*!
		*
		**/
		int GetNodeCount();

		/*!
		*
		**/
		void Reset();

		//
		//
		//
		/*!
		*
		**/
		void SolvingTree();

		/*!
		*
		**/
		int GetSampleCount();

		/*!
		*
		**/
		const TreeNode *GetSampleNode(int order);

		/*!
		*
		**/
		const std::vector<string> &GetNodeNames();

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
		*2014/11/19
		**/
		static bool CompareBranchToLevel(const TreeBranch *first, const TreeBranch *second);

		/*!
		*
		**/
		static bool CompareSamplePointProbability(const SamplePoint &first, const SamplePoint &second);

		//
		//
		//
		/*!
		*2014/11/6
		**/
		int GetLevelNodeCount(int level, std::vector<int> &ids);

		//
		//
		//
		/*!
		*2014/11/18
		**/
		bool IsAllLevelSame(int level = -1);

		/*!
		*
		**/
		void ReverseSolvingTree(int startLevel = 0, int endLevel = -1);
	private:
		//
		//
		//
		/*!
		*
		**/
		bool DoInsertNode(TreeNode *parent, TreeNode *child, unsigned short type);

		/*!
		*
		**/
		void DoRemoveNode(TreeNode *node);

		/*!
		*
		**/
		double DoGetProbability(unsigned short type, bool isUp = true);

		//
		//
		//
		/*!
		*
		**/
		int DoGetNodeLevel(const TreeNode *node);

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
		std::vector<string> m_names;
		std::vector<string> m_reverseNames;//2014/11/19
		
		// map layout
		double m_xstep;
		double m_ystep;

		// root node
		TreeNode *m_root;

		// container for nodes
		NodeVector m_nodes;

		// container for branches
		BranchVector m_branches;

		// results or sample points
		SampleVector m_samples;

		//rendered name
		string m_sampleStr;
		string m_probabilityStr;

		//record sorts of value of current level
		std::map<int,std::vector<double>> m_valsMap;
		std::vector<double> m_vals;

	//private:
		//2014/11/5
		int m_maxId;//record max node's id

		double m_maxDegree;

		//reverse probability?
		bool m_isReverseMode;
		int m_startLevel;
		int m_endLevel;
	};
}
#endif