#include <iostream>
#include <vector>
#include <climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

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
	int n;
	cin >> n;
	while (n--)
		 testcase();
	return 0;
}

void testcase() {

	int t, e, s, a, b;	

	cin >> t >> e >> s >> a >> b;
	cout << "Nr. Species = " << s << endl;

	// Initialize Graphs for every species
	Graph G[s];
	WeightMap wm[s];
	
	for (int i=0; i<s; i++) {
		Graph temp_G(t);
		G[i] = temp_G;
		wm[i] = get(edge_weight, G[i]);
	}

	Graph G_final;
	WeightMap wm_final;
	wm_final = get(edge_weight, G_final);

	for (int i=0; i<e; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		Edge edg;
		tie(edg, tuples::ignore) = add_edge(t1, t2, G_final);
		wm_final[edg] = INT_MAX;
		for (int j=0; j<s; j++) {
			int cost;
			cin >> cost;
			Edge ed;
			tie(ed, tuples::ignore) = add_edge(t1, t2, G[j]);
			wm[j][ed] = cost;
		}
	}


	// For every species Graph apply MST in order to get their private network
	// Incrementally construct the final Graph by checking if there exists lower cost
	// for each edge

	for (int i=0; i<s; i++) {
		int hive;
		cin >> hive;
					
		vector<int> pred(t);
		prim_minimum_spanning_tree(G[i], &pred[0], root_vertex(hive));

	
		// Now pred[u], u holds the minimum spanning tree
		for (size_t j=0; j<t ; j++) {
			Edge f_edge;   // Get edge from the final graph
			Edge st_edge;  // Get edge from MST
			bool success;
			tie(f_edge, success) = edge(j, pred[j], G_final);
			tie(st_edge, success) = edge(j, pred[j], G[i]);
			if (success) {
				if (wm_final[f_edge] >= wm[i][st_edge])
					wm_final[f_edge] = wm[i][st_edge];
			}
		}
	}
	
	// Apply Dijkstra's Shortest Paths on the final Graph to calculate the minimum cost


	vector<int> dijkstra_dist(t);
	vector<int> dijkstra_pred(t);

	dijkstra_shortest_paths(G_final, a, predecessor_map(make_iterator_property_map(dijkstra_pred.begin(), get(vertex_index, G_final))).
							distance_map(make_iterator_property_map(dijkstra_dist.begin(), get(vertex_index, G_final))));
	


	cout << dijkstra_dist[b] << endl;
	
//	vector<int>::iterator it;
//	it = std::max_element(dist.begin(), dist.end());
//	cout << sum_weights << ' ' << *it << endl;
		
}

	 
