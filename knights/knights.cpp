#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;     //Edge type
typedef graph_traits<Graph>::vertex_descriptor Vertex; //Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt;     //Edge Iterator

typedef property_map<Graph, edge_weight_t>::type WeightMap;

bool inBounds(int x, int y, int n) {
	return (x>=0 && y>=0 && x<n && y<n);
}

void testcase() {

	int n;
	cin >> n;

	int c[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> c[i][j];

	// Construct graph 
	Graph G(n*n);
	WeightMap wm = get(edge_weight, G);

	// For every non-empty square place knight and add edge to every other knight
    // Fill up chessboard row by row 

	int nr_knights = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (c[i][j] == 1) {
				nr_knights++;
				if (inBounds(i+2, j+1, n)) {
					if (c[i+2][j+1] == 1) {
						add_edge(i*n + j, (i+2)*n + (j+1), G);
						//cout << "Adding : " << i << ", " <<  j << " -> " << i+2 << ", " << j+1 << endl;
					}
				}
				if (inBounds(i+2, j-1, n)) {
					if (c[i+2][j-1] == 1) {
						add_edge(i*n + j, (i+2)*n + (j-1), G);
				//		cout << "Adding : " << i << ", " <<  j << " -> " << i+2 << ", " << j-1 << endl;
					}
				}
				if (inBounds(i+1, j+2, n)) {
					if (c[i+1][j+2] == 1) {
						add_edge(i*n + j, (i+1)*n + (j+2), G);
				//		cout << "Adding : " << i << ", " <<  j << " -> " << i+1 << ", " << j+2 << endl;
					}

				}
				if (inBounds(i+1, j-2, n)) {
					if (c[i+1][j-2] == 1) {
						add_edge(i*n + j, (i+1)*n + (j-2), G);
				//		cout << "Adding : " << i << ", " <<  j << " -> " << i+1 << ", " << j-2 << endl;
					}
				}
			}	
		}
	}

	//print_graph(G);

	// Graph is bipartite so min vertex cover size is equal to the size of maximum matching

	vector<Vertex> mate(n*n);
	const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();

	edmonds_maximum_cardinality_matching(G, &mate[0]);

//	int nr_mates = 0;
//	for (int i=0; i<n*n; i++) {
//		if (mate[i] != NULL_VERTEX && i<mate[i]) {
//			nr_mates++;
//		}
//	}
	

	int matching_sz = matching_size(G, &mate[0]);
	//cout << "Size of matching = " << matching_sz << endl;

	cout << nr_knights - matching_sz << endl;

	
}

int main() {

	int t;
	cin >> t;
	while (t--)
		testcase();

	return 0;
}
