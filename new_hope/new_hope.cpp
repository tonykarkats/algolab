#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
					   no_property,
					   property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor 		  Edge;
typedef graph_traits<Graph>::edge_iterator			  EdgeIt;
typedef graph_traits<Graph>::vertex_descriptor  	  Vertex;

int node_id(int x, int y, int nodes_per_cc) {
	return x * nodes_per_cc + y;
}

void testcase() {

	// k: total number of command centers
	// s: number of stormtroopers per command center
	// m: number of distinct command center supervisions
	int k, s, m;
	cin >> k >> s >> m;

	// Only for first testcase (s == 1)
	//assert(s==1);

	int graph_size = k * s;
	Graph G(graph_size);
	

	set<int> supervised;
	
	for (int i=0; i<m; i++) {
		int u, v, h;
		cin >> u >> v >> h;

		for (int j=0; j<h; j++) {
			int x, y;
			cin >> x >> y;

			int from = node_id(u, x, s);
			int to = node_id(v, y, s);

			supervised.insert(to);
			add_edge(from, to , G);

		}
	}
	//print_graph(graph);

	vector<Vertex> mate(graph_size);
	const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();

	edmonds_maximum_cardinality_matching(G, &mate[0]);

	cout << graph_size - matching_size(G, &mate[0]) << endl;
}

int main() {

	int t;
	cin >> t;

	while (t--) {
		testcase();
	}

	return 0;
}
