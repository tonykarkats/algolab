#include <iostream>
#include <vector>
#include <climits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;     //Edge type
typedef graph_traits<Graph>::vertex_descriptor Vertex; //Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt;     //Edge Iterator
typedef graph_traits<Graph>::vertex_iterator VertexIt; //Vertex Iterator

typedef property_map<Graph, edge_weight_t>::type WeightMap;

void testcase() {
	
	int n, m;
	cin >> n >> m;

	int s, t;
	cin >> s >> t;
	
	Graph G(4*n);
	WeightMap wm = get(edge_weight, G);

	/* For every original vertex u we create 4 vertices based on the the route up to there
	 * 4*u   : The number of edges up to this vertex is even and the weight is even
	 * 4*u+1 : The number of edges up to this vertex is even and the weight is odd
	 * 4*u+2 : The number of edges up to this vertex is odd and the weight is even
	 * 4*u+3 : The number of edges up to this vertex is odd and the weight is odd
	 */

	for (int i=0; i<m; i++) {

		int u, v;
		int weight;

		cin >> u >> v >> weight;
		Edge e;

		tie(e, tuples::ignore) = add_edge(4*u,     4*v + 2 + weight % 2, G);
		wm[e] = weight;

		tie(e, tuples::ignore) = add_edge(4*u + 1, 4*v + 3 - weight % 2, G);
		wm[e] = weight;

		tie(e, tuples::ignore) = add_edge(4*u + 2, 4*v     + weight % 2, G);
		wm[e] = weight;

		tie(e, tuples::ignore) = add_edge(4*u + 3, 4*v + 1 - weight % 2, G);
		wm[e] = weight;
		
	}

	// Dijkstra shortest path from 
	vector<int> dist(4*n, INT_MAX);
	vector<int> pred(4*n);

	dijkstra_shortest_paths(G, 4*s, predecessor_map(make_iterator_property_map(pred.begin(), get(vertex_index, G))).
							distance_map(make_iterator_property_map(dist.begin(), get(vertex_index, G))));

	// Now we need to find the shortest path from even-even to odd-odd
	if (dist[4*t+3] == INT_MAX)
		cout << "no" << endl;
	else
		cout << dist[4*t+3] << endl;

}

int main(int argc, char *argv[]) {

	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) {
		 testcase();
	}

	return 0;
}
