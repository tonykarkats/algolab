#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <set>
#include <map>

using namespace std;

int node_id(int x, int y, int nodes_per_cc) {
	return x * nodes_per_cc + y;
}

void print_graph(vector<vector<int>> graph) {

	int n = graph.size();
	for (int i=0; i<n; i++) {
		cout << i << " -> ";
		for (int j=0; j<graph[i].size(); j++) {
			cout << " " << graph[i][j];
		}
		cout << endl;
	}
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
	vector<vector<int>> graph(graph_size);

	set<int> supervised;
	vector<int> degree(graph_size);
	
	for (int i=0; i<m; i++) {
		int u, v, h;
		cin >> u >> v >> h;

		for (int j=0; j<h; j++) {
			int x, y;
			cin >> x >> y;

			int from = node_id(u, x, s);
			int to = node_id(v, y, s);

			degree[from]++;
			degree[to]++;

			supervised.insert(to);
			graph[to].push_back(from);
			graph[from].push_back(to);
		}
	}

	//print_graph(graph);

	// We use a priority queue for the degrees of the nodes
	
	set<pair<int, int>> node; //degree, node_id
	for (int i=0; i<graph_size; i++) {
		int degree_i = degree[i];
		//cout << "Degree of " << i << " = " << degree_i << endl;
		node.insert(make_pair(degree_i, i));
	}

	set<int> mis; // The maximum independent set
	while (!node.empty()) {
		// Pick the first element from the set
		pair<int, int> top = *(node.begin());
		int node_id = top.second;
		mis.insert(node_id);
		node.erase(top);		
		
		// Remove all neighbors
		vector<int>::iterator it;
		for (it = graph[node_id].begin(); it != graph[node_id].end(); it++) {
			node.erase(make_pair(degree[*it], *it));
		}

	}

	cout << mis.size() << endl;

	cout << "Graph size = " << graph_size << endl;
	cout << "Supervised size = " ;
	cout << supervised.size() << endl;

	//print_graph(graph);

}

int main() {

	int t;
	cin >> t;

	while (t--) {
		testcase();
	}

	return 0;
}
