#include <iostream>
#include <vector>
#include <climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/depth_first_search.hpp>

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
	
	int t;
	cin >> t;
	while (t--)
		 testcase();
	return 0;
}

void testcase() {

	int n, t_index;

	cin >> n >> t_index ; 
	t_index--;

	Graph G(n);
	WeightMap wm;
	
	wm = get(edge_weight, G);

	for (int j=0; j<n-1; j++) {
		for (int k=1; k < n-j; k++) {
			int weight;
			cin >> weight;
			Edge e;
			tie (e, tuples::ignore) = add_edge(j, j+k, G);
			wm[e] = weight;
		}
	}


	// Calculate the MST the way Princess Leia does starting from Tatooine
	// -->Prim<--

	vector<int> pred(n);
	prim_minimum_spanning_tree(G, &pred[0], root_vertex(t_index));
	
	//cout << "Prim OK" << endl;

	vector<Edge> mst_edges;	
	int mst_cost = 0;

	for (size_t i=0; i<pred.size() ; i++) {
		if (pred[i] != i) {
			Edge e;
			tie(e, tuples::ignore) = edge(i, pred[i], G);
	//		cout << "Edge " << i << " ," << pred[i] << " has weight " << wm[e] << endl;;
			mst_edges.push_back(e);
			mst_cost += wm[e];
		}
	}


//	cout << "MST has cost = " << mst_cost << endl;

	// Sort list of edges of the mst by weight
	// Do I have to??

	int second_best_cost = INT_MAX;
	
	vector<Edge>::iterator mst_iter;
	// Try to calculate second MST by removing one edge at a time from the mst
	for (mst_iter = mst_edges.begin(); mst_iter != mst_edges.end(); mst_iter++) {

		vector<int> pred2(n);	
		int weight = wm[*mst_iter];	
		wm[*mst_iter] = INT_MAX;
		prim_minimum_spanning_tree(G, &pred2[0], root_vertex(t_index));

		int cost2 = 0;	

		for (size_t i=0; i<pred2.size() ; i++) {
			if (pred2[i] != i) {
				Edge e;
				tie(e, tuples::ignore) = edge(i, pred2[i], G);
				cost2 += wm[e];
			}
		}

		if ((cost2 < second_best_cost) && (cost2 >= mst_cost))
				second_best_cost = cost2;

			// Revert to old cost
			wm[*mst_iter] = weight;
			
	}	

	cout << second_best_cost << endl;

}

	 
