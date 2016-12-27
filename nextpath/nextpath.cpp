#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int bfs(const vector<vector<int>>& graph, int v, int t) {

    bool found_first = false;  		 // Indicate whether we have already reached t once
    int second_shortest_length = 0;  // Our second shortest length

	// Number of times each vertex has been visited
    vector<int> visited(graph.size(), 0);

	// For every Graph node we store the depth when it was discovered
    queue<pair<int, int>> q;

    q.push(make_pair(v, 0));
    ++visited[v];
    while (!q.empty() && second_shortest_length == -1) {
        auto p = q.front();
        q.pop();
        auto s = p.first;
        auto depth = p.second;

        if (s == t) {
            if (found_first) {
                second_shortest_length = depth;
                continue;
            } else
                found_first = true;
        }
		
		// For every adjacent node that hasn't been visited twice push it into the queue
		// and increment its visited index
        for (int next : graph[s]) {
            if (visited[next] != 2) {
                q.push(make_pair(next, depth + 1));
                ++visited[next];
            }
        }
    }
    return second_shortest_length;
}

int main() {
    ios_base::sync_with_stdio(false);
    int cases;
    cin >> cases;
    while (cases--) {
        int n, m, s, t;
        cin >> n >> m;
        cin >> s >> t;
        --s;
        --t;
        vector<vector<int>> graph;
        graph.resize(n);
        while (m--) {
            int v1, v2;
            cin >> v1 >> v2;
            --v1;
            --v2;
            graph[v1].push_back(v2);
        }

        int second_shortest_length = bfs(graph, s, t);

        if (second_shortest_length != -1)
            cout << second_shortest_length;
        else
            cout << "no";
        cout << "\n";
    }
}

