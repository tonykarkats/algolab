#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
			property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type 			EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type 			ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor				Edge;
typedef graph_traits<Graph>::vertex_descriptor				Vertex;

void addEdge(int from, int to, long c,
			 EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {

	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;

}

void testcase() {

	int n, m, s, d;
	cin >> n >> m >> s >> d;

	Graph G(2*n); 
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	Vertex flow_source = add_vertex(G);
	Vertex flow_sink = add_vertex(G);
//	cout << "source = " << flow_source << endl;
//	cout << "sink = " << flow_sink << endl;

	/*  For every node we add another one and connect them with capacity 1.
	 *  The incoming edges go into the first and the outcoming edges come 
	 *  out of the second.
     */

	for (int i=0; i<n; i++)
		addEdge(i, i+n, 1, capacity, rev_edge, G);

	for (int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		addEdge(a+n, b, 1, capacity, rev_edge, G);
	}


	//Starting nodes
	for (int i=0; i<s; i++) {
		int starting_node;
		cin >> starting_node;
		addEdge(flow_source, starting_node, 1, capacity, rev_edge, G);
	}
	
	for (int i=0; i<d; i++) {
		int finishing_node;
		cin >> finishing_node;
		addEdge(finishing_node + n, flow_sink, 1, capacity, rev_edge, G);
	}

	long flow = edmonds_karp_max_flow(G, flow_source, flow_sink);

	cout << flow << endl;
}	


int main() {

	int T;
	cin >> T;
	int i = T;
	while (T--){
		testcase();
	}
	return 0;
}

