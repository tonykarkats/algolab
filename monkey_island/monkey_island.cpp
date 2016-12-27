#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> 	Traits;
typedef adjacency_list<vecS, vecS, directedS> 			Graph;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::edge_iterator 				EdgeIt;

int main() {
	
	// Input settings
	ios_base::sync_with_stdio(false); 
	//ifstream cin("MonkeyIsland.txt");
	
	// Iterate over test cases
	int T;
	cin >> T;
	while (T > 0) {
		T--;
		
		int n, m;
		cin >> n; // Number of locations
		cin >> m; // Number of roads
		
		// Instantiate graph
		Graph G(n);
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			Edge e;
			tie(e, tuples::ignore) = add_edge(u - 1, v - 1, G);
		}
		
		// Save costs of building stations
		int costs[n];
		for (int i = 0; i < n; i++) {
			cin >> costs[i];
		}
		
		// Calculate components in graph
		std::vector<int> component(num_vertices(G));
		int comp_count = strong_components(G, &component[0]); 

		// Component cost
		vector<int> compCost;
		compCost.reserve(comp_count);
		for (int i = 0; i < comp_count; i++) {
			compCost.push_back(INT_MAX);
		}
		
		// Calculate cost for each component to turn it into a police station
		for (int i = 0; i < n; i++) {

			// Minimum
			compCost[component[i]] = 
			min(
				compCost[component[i]], 	// Costs of making others police stations
				costs[i] 					// Cost of making this the police station
			);
			
		}
		
		// Initialize that none of the components have incoming edges
		bool hasIncomingEdges[comp_count];
		for (int i = 0; i < comp_count; i++) {
			hasIncomingEdges[i] = false;
		}
		
		// Iterate over all edges between components
		EdgeIt ei, ei_end;
		for (tie(ei, ei_end) = edges(G); ei != ei_end; ++ei) {
			if (component[source(*ei, G)] != component[target(*ei, G)]) {
					hasIncomingEdges[component[target(*ei, G)]] = true;
			}
		}
		
		// Calculate total cost
		int fcost = 0;
		for (int i = 0; i < comp_count; i++) {
			if (!hasIncomingEdges[i]) {
				fcost += compCost[i];
			}
		}

		// Print result
		cout << fcost << endl;
		
	}
	
}


