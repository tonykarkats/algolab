#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <vector>
#include <algorithm>



using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
			property<edge_capacity_t, int,
				property<edge_residual_capacity_t, int,
					property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type 			EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type 			ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor				Edge;
typedef graph_traits<Graph>::vertex_descriptor				Vertex;
typedef graph_traits<Graph>::out_edge_iterator 				OutEdgeIt;
typedef graph_traits<Graph>::vertex_iterator 				VertexIt;

void addEdge(int from, int to, int c,
			 EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {

	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;

}

set<Vertex> visited;

struct my_visitor: default_bfs_visitor {
public:
  void discover_vertex(const Vertex u, const Graph & g)
  {
//		cout <<" Discovered " << u <<  endl; 
		visited.insert(u);
  }

};


void testcase() {

	visited.clear();

	int g, s, l;
	cin >> g >> s >> l;

	Graph G(g+s);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);


	Vertex flow_source = add_vertex(G);
	Vertex flow_sink   = add_vertex(G);

//	cout << "Source is " << flow_source << " and sink is " << flow_sink << endl;

	// Ground stations are numbered from 0...g-1
	// Satellites are numbered from g..g+s-1

	for (int i=0; i<l; i++) {
		int ground_station, satellite;
		cin >> ground_station >> satellite ;
		addEdge(ground_station, satellite + g, 1, capacity, rev_edge, G);
//		cout << "Adding edge " << ground_station << "," << satellite+g << endl;
	}

	//Connect source with ground stations
	for (int i=0; i<g; i++) {
		addEdge(flow_source, i, 1, capacity, rev_edge, G);
//		cout << "Adding edge " << flow_source << "," << i << endl;
	}

	//Connect sink with sattelite stations	
	for (int i=0; i<s; i++) {
		addEdge(i + g, flow_sink, 1, capacity, rev_edge, G);
//		cout << "Adding edge " << i + g << "," << flow_sink  << endl;
	}

	//Compute the flow of the graph
		
	int flow = push_relabel_max_flow(G, flow_source, flow_sink);
	
	OutEdgeIt ei, e_end;
//	// Check to see if the matching is as expected
//	for (int i=0; i<g+s+2; i++) {
//		for (boost::tie(ei, e_end) = out_edges(i, G); ei != e_end; ++ei) {
//			if (capacity[*ei] > 0)
//				cout << "flow " << source(*ei, G) << " " << target(*ei, G) << " " << (capacity[*ei] - res_capacity[*ei]) << endl;
//		}
//	}


	// Construct Residual Graph
	//cout << "Residual Graph" << endl;
	Graph G_res(g+s);
	for (int i=0; i<g+s+2; i++) {
		for (boost::tie(ei, e_end) = out_edges(i, G); ei != e_end; ++ei) {
			if (res_capacity[*ei] > 0) {
//				cout << "flow " << source(*ei, G) << " " << target(*ei, G) << " " <<  res_capacity[*ei] << endl;
				Edge e;
				tie(e, tuples::ignore) = add_edge((int) source(*ei, G_res), (int) target(*ei, G_res), G_res);
			}
		}
	}


	// Do a BFS Search on the residual graph starting from s
	my_visitor vis;
	breadth_first_search(G_res, flow_source, visitor(vis));

	set<Vertex> unvisited;
	set<Vertex> all_vertices;

	for (int i=0; i<g+s+2; i++)
		all_vertices.insert(i);

	set_difference(all_vertices.begin(), all_vertices.end(), visited.begin(), visited.end(), inserter(unvisited, unvisited.begin()));	


	set<Vertex>::iterator diff_i;
	vector<Vertex> left_unvisited;
	vector<Vertex> right_visited;



	for (diff_i = unvisited.begin() ; diff_i != unvisited.end(); diff_i++)
		if ( *diff_i < g )
			//cout << *diff_i << " ";
			left_unvisited.push_back(*diff_i);

	for (diff_i = visited.begin(); diff_i != visited.end(); diff_i++)
		if (*diff_i >=g && *diff_i < g+s)
			//cout << *diff_i - g << " ";
			right_visited.push_back(*diff_i);

	vector<Vertex>::iterator ite;

	cout << left_unvisited.size() << " " << right_visited.size() << endl;
	for (ite = left_unvisited.begin(); ite != left_unvisited.end(); ite++)
		cout << *ite << " ";

	for (ite = right_visited.begin(); ite != right_visited.end(); ite++)
		cout << *ite - g<< " ";

	cout << endl;
}


int main() {

	int t;
	cin >> t;
	while (t--)
		testcase();
	return 0;
}

