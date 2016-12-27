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

	int n, m, s;
	cin >> n >> m >> s;
	vector<int> shops;	
	for (int i=0; i<s; i++){
		int shop;
		cin >> shop;
		shops.push_back(shop);
	}	

	Graph G(n);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	//Add source and sink -> Na brw poia einai apo ta nodes kai na ta balw mona tous

	for (int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		addEdge(u, v, 1, capacity, rev_edge, G);
		addEdge(v, u, 1, capacity, rev_edge, G);
//		cout << "Added edge " << u << " " << v << endl;

	}

	Vertex flow_sink = add_vertex(G);

	vector<int>::iterator it;
	for (it = shops.begin(); it != shops.end(); ++it){
		addEdge(*it, flow_sink, 1000, capacity, rev_edge, G);

	}

	long flow = edmonds_karp_max_flow(G, 0, flow_sink);

	if (flow >= s)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

}


int main() {

	int T;
	cin >> T;
	while (T--)
		testcase();
	return 0;
}

