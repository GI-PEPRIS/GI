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
#ifndef __ANYVIS_JOBSTREAM_H__
#define __ANYVIS_JOBSTREAM_H__

// refer to macro
#include "anyvis.h"
#include "anyaxises.h"

// boost
#include "boost/function.hpp";
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/point_traits.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/topological_sort.hpp"
#include "boost/graph/connected_components.hpp"
#include "boost/graph/topology.hpp"

//boost layout
#include "boost\graph\circle_layout.hpp"
#include "boost\graph\kamada_kawai_spring_layout.hpp"
#include "boost\graph\random_layout.hpp"
#include "boost\graph\gursoy_atun_layout.hpp"
#include "boost\graph\fruchterman_reingold.hpp"
#include "boost\random\linear_congruential.hpp"
using namespace boost;

enum vertex_position_t { vertex_position };
namespace boost { BOOST_INSTALL_PROPERTY(vertex, position); }

// base
#include "any/base/anygeom.h"
using namespace AnyBase;
// map
#include "any/map/anyviewhook.h"
using namespace AnyMap;

// refer to persistence
#include "any/db/anyaccessor.h"
using namespace AnyDB;

// 
namespace AnyVis
{
	/*!
	*
	**/
	class ANYVIS_CLASS CAnyJobStream  :  public CAnyViewHook
	{
	public:
		/*!
		*
		**/
		enum MapOperation
		{
			MO_Default			= 1,
			MO_Node				= 1 << 1,
			MO_Pan				= 1 << 2,
			MO_Pick				= 1 << 3,		// 
			MO_Condition		= 1 << 4,		// create a branch
			MO_Multi_Sel		= 1 << 5,		//2015/11/10: multiple selection
		};

		/*!
		*
		**/
		enum JobLayoutType
		{
			JST_Unknown,
			JST_Data_Flow,
			// below http://www.boost.org/doc/libs/1_57_0/libs/graph/doc/table_of_contents.html
			JST_Topology_Square,
			JST_Topology_Cube,
			JST_Topology_Ball,			
			JST_Topology_Circle,
			JST_Topology_Sphere,
			JST_Topology_Heart,
			JST_Random,
			JST_Circle,
			JST_Kamada,
			JST_Fruchterman,
			JST_Gursoy,
			JST_Tree_Horizontal,//2016/1/8
			JST_Tree_Vertical,//2016/1/8
			JST_Max
		};

		/*!
		*
		**/
		enum JobGlyphType
		{
			JGT_Unknown = -1,
			JGT_Circle,
			JGT_Rectangle,
			JGT_Triangular,
			JGT_Triangular_A,
			JGT_Rhombus,
			//JGT_Rectangle_Round,
			JGT_Max
		};

		/*!
		*
		**/
		struct JobEntry
		{
			long m_graphIdx;//idx in graph
			long m_bkGraphId;//2016/1/15: backup graph id

			long m_jobId;//practice id...
			string m_name;	// text out on node
			string m_key;		// or IP etc encoding
			string m_tip;		// as tip, returned by m_function

			/*!
			*
			**/
			JobEntry() : m_graphIdx(-1),m_jobId(-1),m_name(""), m_tip(""), m_key(""), m_bkGraphId(-1)
			{
			}
		};

		template <typename Signature>
		struct JobFunction : public JobEntry
		{
			typedef boost::function<Signature> Callback;

			Callback m_function; // m_function=boost::bind(&AnyCMS::CRcfCMSImpl::DoRemoveOneTypeChildren,this,_1);
		};

		struct JobNode : public CGeoPoint<double>//2015.5.4: inherit from CGeoPoint
		{
			JobEntry *m_entry;//node call back
			JobEntry *m_branchEntry;//branch call back

			CGeoRect<double> m_position;
			
			std::vector<JobNode *> m_parents; //node may have different parent
			std::vector<JobNode *> m_children;	// children may in parallel execution

			int m_glyphType;
			unsigned int m_color;
			int m_level;
			double m_size;//2015/11/18: node size

			//2015/11/10:group id/name
			int m_groupId;
			std::string m_groupName;
			
			//2016/1/8
			double m_childHighPos;
			double m_childLowPos;
			
			/*!
			*
			**/
			JobNode() : m_entry(0), m_glyphType(JGT_Rectangle), m_color(0),m_level(0), m_branchEntry(0),m_groupId(0),m_groupName(""),m_size(10.),m_childHighPos(0.), m_childLowPos(0.)
			{
			}

			/*!
			*
			**/
			~JobNode()
			{
				if (m_entry)
				{
					delete m_entry;
					m_entry = 0;
				}

				if (m_branchEntry)
				{
					delete m_branchEntry;
					m_branchEntry = 0;
				}
			}

			static bool CompareNodeEntry(const JobNode *first, const JobNode *second)
			{
				return first->m_entry->m_graphIdx < second->m_entry->m_graphIdx;
			}
		};
		typedef std::vector<JobNode *> JobStream;
		typedef JobStream::iterator job_itr;
		typedef JobStream::const_iterator job_citr;

		//
		struct JobBranch
		{
			JobNode *m_from;
			JobNode *m_to;

			CGeoPoint<double> m_pts[6];

			JobBranch() : m_from(0),m_to(0)
			{
			}
		};
		typedef std::vector<JobBranch *> JobBranches;
		typedef JobBranches::iterator branch_itr;
		typedef JobBranches::const_iterator branch_citr;

		// for boost
	private:
		typedef adjacency_list< vecS, vecS, directedS> BoostGraph;
		typedef boost::graph_traits<BoostGraph>::vertex_descriptor BoostVertex;
		typedef property_map<BoostGraph, vertex_index_t>::const_type BoostVertexIndex;

		struct cycle_detector : public dfs_visitor<>
		{
			cycle_detector( bool& has_cycle) 
				: _has_cycle(has_cycle) { }

			template <class Edge, class Graph>
			void back_edge(Edge, Graph&) {
				_has_cycle = true;
			}
			protected:
			bool& _has_cycle;
		};

		//boost layout
		typedef square_topology<>::point_type point;
		
		struct kamada_kawai_done
		{
			double last_delta;

			kamada_kawai_done() : last_delta(0.) {}

			template<typename Graph>
			bool operator()(double delta_p, typename boost::graph_traits<Graph>::vertex_descriptor /*p*/, const Graph& /*g*/,bool global)
			{
				if (global) 
				{
					double diff = last_delta - delta_p;
					if (diff < 0) 
					{
						diff = -diff;
					}
					last_delta = delta_p;
					return diff < 0.01;
				} 
				else
				{
					return delta_p < 0.01;
				}
			}
		};

	public:
		//boost edge
		struct SimpleEdge
		{
			int first, second;
		};
		typedef std::vector<SimpleEdge> SimpleEdges;

	public:
		//
		//
		//
		/*!
		*
		**/
		CAnyJobStream(CAnyView &curView);
		~CAnyJobStream();

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
		bool AddNode(JobNode *node);
		bool RemoveNode(long idx);
		JobNode *GetNode(long idx);
		JobStream &GetJobStream();

		/*!
		*
		**/
		bool InsertBranch(JobNode *parent, JobNode *child, bool isBindRelation = true);

		/*!
		*2015/4/17
		*/
		void GetJobNodeLevels(std::vector<int> &levels);
		
		/*!
		*
		*/
		void GetJobNodes(int level, std::vector<JobNode*> &nodes, bool orderByParent = false);

		/*!
		*
		**/
		void ReleaseAll();
		
		/*!
		*
		**/
		void SetLayoutType(short type);

		/*!
		*2015/5/4
		**/
		short GetLayoutType();

		/*!
		*
		**/
		void ResetNormalBranches();

		/*!
		*
		**/
		void ResetStreamLevel();

		//
		//
		//
		/*!
		* graph and its corresponding algorithm
		**/
		bool MakeGraph();
		bool IsCyclic();
		bool IsConnected();
		void MakeLayout(short type);
		void DoFlowLayout(short type);
		void DoTopoLayout(short type);
		void MakeTopoSort(std::vector<long> &idxes);

		//
		//
		//
		/*!
		*
		*/
		bool MouseDown(const CGeoPoint<double> &scrPoint);
		bool MouseMove(const CGeoPoint<double> &scrPoint);
		bool MouseUp(const CGeoPoint<double> &scrPoint);
		bool DoubleClick(const CGeoPoint<double> &scrPoint);
		void OnPaint(CAnyCanvas &canvas, const CGeoRect<double> &clipBox, bool isDirect);
		
		//
		//
		//
		/*!
		*2015/5/5
		*/
		void DoRenderPicked(CAnyCanvas &canvas);

		//
		//
		//
		/*!
		*
		*/
		JobNode * FindNode(CGeoPoint<double> &coord);

		/*!
		*
		*/
		JobBranch * FindBranch(CGeoPoint<double> &coord);

		//
		//
		//
		/*!
		*
		*/
		void SetMapPort();

		/*!
		*
		*/
		void SetMapOperation(int op);
				
		/*!
		*
		**/
		bool RemoveBranch(JobBranch *branch);

		
		//
		//database operation
		//
		bool CanCommit();

		/*!
		*
		*/
		void Commit(long elementId);

		/*!
		*
		*/
		bool CanLoad(long elementId);

		/*!
		*
		*/
		void Load(long elementId);

		//
		//2015/5/7: boost layout
		//
		/*!
		*
		**/
		bool BoostLayout(short type);

		
		/*!
		*
		*/
		static bool DoBoostLayout(short type, int verticeCount, const SimpleEdges &simpleEdges, CGeoRect<double> &mapExtent, std::vector<CGeoPoint<double>> &pts, std::vector<int> &ids);

		//
		//2016/1/8: tree layout
		//
		/*!
		*
		**/
		bool TreeLayout(short type);

		/*!
		*
		**/
		void RemoveBackupJobNodes();

		/*!
		*
		**/
		bool IsTreeLayout(int &type);

		/*!
		*2016/1/15
		**/
		void GetBackupNodes(long backupId, std::vector<JobNode*> &nodes);

	private:

		//
		//
		//
		/*!
		*
		*/
		JobNode *DoGetNode(JobNode *parentNode, long idx);
		
		/*!
		*
		**/
		void ReleaseBranches(bool isAll = true);

		//
		//
		//
		/*!
		*
		*/
		void RenderGraph(CAnyCanvas &canvas);

		/*!
		*
		*/
		static bool CompareJobNodeLevel(int level1, int level2);

		//
		//database operation
		//
		/*!
		*
		*/
		void DoLoad(CAnyAccessor &accessor, bool isFirst);

		/*!
		*
		*/
		void BindRelation(CAnyAccessor &accessor);
		
		/*!
		*
		*/
		void DoCommit(CAnyAccessor &accessor, long practiceId, long elementId, long relid, long id, long parentId, long childId, long level, const string &name,\
			const string &key, const string &tip, long glyphType, long color, double x, double y, long groupId, const std::string &groupName);

		/*!
		*2015/5/4
		**/
		void DoResetStreamLevel(JobNode *node, int level);

		//
		//2015/5/7
		//
		/*!
		*
		*/
		template<typename Graph, typename PositionMap, typename Topology>
		static void GetGraphLayout(const Graph& g, PositionMap position, const Topology& topology, CGeoRect<double> &mapExtent, std::vector<CGeoPoint<double>> &pts, std::vector<int> &ids);

		/*!
		*
		*/
		void DoSetMapPort(const CGeoRect<double> &mapExtent);
		
		//
		//2016/1/15: tree layout
		//
		/*!
		*
		**/
		void DoTreeLayout(JobNode *parentNode, JobNode *curNode, int order, double maxY, double yStep, double minX, double xStep, std::vector<JobNode*> &paintedNodes, bool isVertical);

		/*!
		*2016/1/15
		**/
		bool RemoveBranch(JobNode *node);

		/*!
		*2016/1/15
		**/
		bool CanRenderBranch(JobBranch *branch);

	public:
		//nodes
		JobStream m_stream;

		//2015/11/10: temporary selected nodes
		JobStream m_selectedStream;

		//normal branches
		JobBranches m_normalBranches;

	private:
		//branches
		JobBranches m_branches;

		//
		BoostGraph m_graph;

		//
		int m_layoutType;

		//2016/1/15
		int m_treeLayoutType;

		//tip related
		JobNode *m_tipNode;
		CGeoPoint<double> m_tipPt;
		bool m_isMouseDown;

		//operation
		int m_operation;

		// for creation of directed branch
		JobNode *m_curNode;
		JobNode *m_parent;
		JobNode *m_child;
		CGeoPoint<double> m_start;
		CGeoPoint<double> m_end;
	};
}
#endif