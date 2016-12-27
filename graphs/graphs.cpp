#include <iostream>
#include <vector>
#include <climits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge; //Edge type
typedef graph_traits<Graph>::vertex_descriptor Vertex; //Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; //Edge Iterator

typedef property_map<Graph, edge_weight_t>::type WeightMap;

void testcase();

int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) testcase();
	return 0;
}

void testcase() {
	int V, E;	// Nr. of vertices and Edges of Graph

	cin >> V >> E;
	Graph G(V);
	
	WeightMap wm = get(edge_weight, G);

	for (int i=0; i<E; i++) {
		int u, v, w;
		Edge e;
		cin >> u >> v >> w;
		tie(e, tuples::ignore) = add_edge(u, v, G);
		wm[e] = w;
	//	cout << "Added Edge : " << e << " with weight " << w << endl; 
	}

	print_graph(G);

	//Apply Kruskal's Algorithm to calculate MST
	vector<Edge> mst;
	int sum_weights = 0;
	kruskal_minimum_spanning_tree(G, back_inserter(mst));	
	
	vector<Edge>::iterator ebeg, eend = mst.end();
	for (ebeg = mst.begin(); ebeg != eend; ++ebeg)
		sum_weights += wm[*ebeg];

	//Apply Dijkstra with negative weights to find the longest path
	vector<int> dist(V);
	vector<int> pred(V);
	//for (ebeg = mst.begin(); ebeg != eend; ++ebeg)
	//	wm[*ebeg]= constant - wm[*ebeg];

	dijkstra_shortest_paths(G, 0, predecessor_map(make_iterator_property_map(pred.begin(), get(vertex_index, G))).
							distance_map(make_iterator_property_map(dist.begin(), get(vertex_index, G))));

	
	vector<int>::iterator it;
	it = std::max_element(dist.begin(), dist.end());
	cout << sum_weights << ' ' << *it << endl;
		

}

	 
