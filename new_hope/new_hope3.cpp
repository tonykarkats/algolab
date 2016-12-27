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

	print_graph(graph);

	// We use a priority queue for the degrees of the nodes
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> node; //degree, node_id
	for (int i=0; i<graph_size; i++) {
		int degree_i = degree[i];
		cout << "Degree of " << i << " = " << degree_i << endl;
		node.push(make_pair(degree_i, i));
	}

	// Now all the nodes are sorted according to their degree.
	set<int> mis; // The maximum independent set

	while (!node.empty()) {
		// Top of the queue contains lowest degree node
		int top_node = node.top();
		int degree = top_node.first;
		int node_id = top_node.second;
		cout << node_id << " -> " << degree << endl;
		node.pop();
		s.insert(node_id);
		
		// Now remove all its neighbors from
		vector<int, int>::iterator it;
		for (it = graph[node_id].begin(); it != graph[node_id].end(); it++) {
			int v = *it;
			
		}
	
	}	

	//cout << "Supervised size = " ;
	//cout << supervised.size() << endl;

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
