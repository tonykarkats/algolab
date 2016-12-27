#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
			property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					property<edge_reverse_t, Traits::edge_descriptor,
						property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type 			EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_weight_t>::type 			EdgeWeightMap;
typedef property_map<Graph, edge_reverse_t>::type 			ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor				Edge;
typedef graph_traits<Graph>::vertex_descriptor				Vertex;
typedef graph_traits<Graph>::out_edge_iterator 				OutEdgeIt;
typedef graph_traits<Graph>::vertex_iterator 				VertexIt;

void addEdge(int from, int to, int c, int w,
			 EdgeCapacityMap &capacity, EdgeWeightMap &weight, ReverseEdgeMap &rev_edge, Graph &G) {

	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	weight[e] = w;
	capacity[reverseE] = 0;
	weight[reverseE] = -w;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;

}

void testcase() {

	// Read Input
	int n, m, s;
	cin >> n >> m >> s;
	
	vector<int> limits;
	for (int i=0; i<s; i++) {
		int limit;
		cin >> limit;
		limits.push_back(limit);
	}

	vector<int> state;
	for (int i=0; i<m; i++) {
		int st;
		cin >> st;
		state.push_back(st);
	}
	
	Graph G(n+m+s);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
	EdgeWeightMap weight = get(edge_weight, G);

	Vertex flow_source = add_vertex(G);
	Vertex flow_sink   = add_vertex(G);
	
//	cout << flow_source <<" " << flow_sink <<endl;

	// Create graph

	for (int i=0; i<n; i++) {
		addEdge(flow_source, i, 1, 0, capacity, weight, rev_edge, G);
//		cout << "Added " << flow_source << " " << i << " with " << "1,0" <<endl;
		// Go over all bidders and 
		for (int j=0; j<m; j++) {
			int bid;
			cin >> bid;
			addEdge(i, n+j, 1, 100-bid, capacity, weight, rev_edge, G);
//			cout << "Added " << i << " " << n+j << " with" << " 1, " << bid << endl;
		}
	}

	//Add final vertices for limits per state
	for (int i=0; i<m; i++) {
		//Property i belongs to state state[i]
		addEdge(n+i, n+m+state[i]-1 , 1, 0, capacity, weight, rev_edge, G);
//		cout << "Added " << n+i << " " << n+m-1+state[i] << "with " << "1,0" <<  endl;
	}

	//Connect states to sink
	for (int i=0; i<s; i++) {
		addEdge(n+m+i, flow_sink, limits[i], 0, capacity, weight, rev_edge, G);
//		cout << "Added " << n+m+i << " " << flow_sink <<  " with " << limits[i] << " ,0" << endl;
	}
	//Compute the flow of the graph

	successive_shortest_path_nonnegative_weights(G, flow_source, flow_sink);
	long flow = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			Edge e = edge(i, n+j, G).first;
			flow += capacity[e] - res_capacity[e];
		}
	}


	long cost = find_flow_cost(G) - flow*100;
	
	cout << flow << " " << -cost << endl;
}


int main() {

	int t;
	cin >> t;
	while (t--)
		testcase();
	return 0;
}

