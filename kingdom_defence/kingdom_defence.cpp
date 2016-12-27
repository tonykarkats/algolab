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

typedef graph_traits<Graph>::edge_iterator EdgeIterator;

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

	int l, p;
	cin >> l >> p;

	int g[l], d[l];

	for (int i=0; i<l; i++)
		cin >> g[i] >> d[i];

	Graph G(l); 
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	Vertex flow_source = add_vertex(G);
	Vertex flow_sink = add_vertex(G);

	// These tables hold the sums of the minimum flows for all the in and out edges
	// of every node.
	int sumc_in[l], sumc_out[l];
	int sum_c = 0;
	for (int i=0; i<l; i++) {
		sumc_in[i] = 0;
		sumc_out[i] = 0;
	}

	for (int i=0; i<p; i++) {
		int f, t, c, cap;
		cin >> f >> t >> c >> cap;
		addEdge(f, t, cap-c, capacity, rev_edge, G);
		sumc_out[f] += c;
		sumc_in[t]  += c;
		sum_c += c;
	}

	

	// Add flow source and flow sink
	// Also send initial garissons to the nodes

	for (int i=0; i<l; i++) {
		addEdge(flow_source, i, sumc_in[i] + g[i], capacity, rev_edge, G);
		sum_c += g[i];
		addEdge(i, flow_sink, sumc_out[i], capacity, rev_edge, G);
	}



	
	long flow = edmonds_karp_max_flow(G, flow_source, flow_sink);
//	cout << "Source is " << flow_source << "and Sink = " << flow_sink << endl;

	cout << "Max flow is : " << flow << endl;
	

	//Check if flow is saturating
	if (flow == sum_c) 
		cout << "yes" << endl;
	else
		cout << "no" << endl;
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

