#include <iostream>
#include <vector>
#include <climits>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge; //Edge type
typedef graph_traits<Graph>::vertex_descriptor Vertex; //Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; //Edge Iterator
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt; //Edge Iterator

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

	//print_graph(G);


	// Calculate the MST the way Princess Leia does starting from Tatooine
	// -->Prim<--

	vector<int> pred(n);
	prim_minimum_spanning_tree(G, &pred[0], root_vertex(t_index));
	
	vector<Edge> mst_edges;	

	Graph MST(n);
	WeightMap wm_mst;
	wm_mst = get(edge_weight, MST);

	int mst_cost = 0;

	for (size_t i=0; i<pred.size() ; i++) {
		if (pred[i] != i) {
			Edge e;
			tie(e, tuples::ignore) = edge(i, pred[i], G);
			mst_edges.push_back(e);
			mst_cost += wm[e];
	
			Edge e_mst;
			tie(e_mst, tuples::ignore) = add_edge(i, pred[i], MST);
			wm_mst[e_mst] = wm[e];
			
		}
	}

		//cout << "MST has cost = " << mst_cost << endl;
		//print_graph(MST);

	// Precompute the most expensive edge for all the paths (u, v) on top of the MST T
	vector<vector<int> > largest_edge(n, vector<int>(n, -1));

	for (int i=0; i<n; i++) {
//		cout << "BFS for " << i << endl;
		vector<bool> visited(n, false);
		std::queue<int> q;
		q.push(i);
		
		while (!q.empty()) {
			int u = q.front();
//			cout << "Visited " << u << endl;
			q.pop();
			visited[u] = true;

			OutEdgeIt it, end;
			for (tie(it, end) = out_edges(u, MST); it != end; ++it) {
				int v = target(*it, MST);
//				cout << "Discovered " << v << endl;
				
				if ( visited[v] ) {  continue; }

				q.push(v);
//				cout << "Weight of  " << *it << " is " << wm_mst[*it] << endl;
//				cout << "Weight of " << i << ", " << u << " is " << largest_edge[i][u] << endl;
				if (wm_mst[*it] > largest_edge[i][u]) {
					//TODO : Some extra calculations here?? Half the matrix is needed
//					 cout << "Edge " << *it << "has weight " << wm_mst[*it] << " larger than " << largest_edge[i][u] << endl;
					 largest_edge[i][v] = wm_mst[*it];
				}
				else
					largest_edge[i][v] = largest_edge[i][u];
					
			}
		}


	}

//	for (int i=0; i<n; i++) {
//		for (int j=0; j<n; j++) {
//			cout << "lar[" << i << "][" << j << "] = " << largest_edge[i][j] << endl;
//		}
//	}

	// Iterate over the edges not in the MST and find the second shortest MST
	int second_min_weight = INT_MAX;
	EdgeIt eit, eend;
	for (tie(eit, eend) = edges(G); eit != eend; ++eit) {
		
		// Check only for edges not in the MST
		Edge e;
		bool success;
		tie(e, success) = edge(source(*eit, G), target(*eit, G), MST);
		if (success) {
//			cout << *eit << " belongs to the MST" << endl;
		}
		else {
//			cout << *eit << " does not belong to the MST" << endl;
			second_min_weight = std::min(second_min_weight, mst_cost + wm[*eit] - largest_edge[source(*eit, G)][target(*eit, G)]);

		}


	}
	
	cout << second_min_weight << endl;

}

	 
