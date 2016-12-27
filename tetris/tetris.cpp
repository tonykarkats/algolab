#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

void addEdge(int from, int to, long c,
             EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {

	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;
}

void testcase() {

	int w;   // Wall length
	long n;  // Number of bricks
	cin >> w >> n;

	/* This problem will be solved as a max-flow problem.
	 * For every brick [a,b] we add an edge a->b with unit cost.
	 * In order to overcome the restriction that no two bricks can start or end at the
	 * same point, we impose a minimum flow per vertex using the known trick where we 
	 * split every node into two nodes */

	/* Create the graph [0,w-1] : w-1 nodes for the splits + 2 for source and sink */
	Graph G(2*w + 1);

	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);

	int source = w + 1;
	int sink = w;

	// Create edges for the splits
	for (int i=0; i<w; i++) {
		addEdge(i, w+i+1, 1, capacity, rev_edge, G);
	}

	// Input bricks and create the respective edges

	for (int i=0; i<n; i++) {
		
		int start, end;
		cin >> start >> end;

		// Check if start is before the end
		if (start > end) {
			int temp = start;
			start = end;
			end = temp;
		}

		// Check if we exceed the limits
		if (end > w) {
			continue;
		}

		// Add the respective edge
		addEdge(start + w + 1, end, 1, capacity, rev_edge, G);

	}

	/* Compute the max flow. Push relabel is chosen as it has an upper bound of
	 * O(|w|^3) and in our case the w is bound to be fairly small (<=500).
	 */

	long max_flow = push_relabel_max_flow(G, source, sink);
	cout << max_flow << endl;



}

int main() {

	int t;
	cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}
