#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
			property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					property<edge_reverse_t, Traits::edge_descriptor,
						property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type 			EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_weight_t>::type 			EdgeWeightMap;
typedef property_map<Graph, edge_reverse_t>::type 			ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor				Edge;
typedef graph_traits<Graph>::vertex_descriptor				Vertex;
typedef graph_traits<Graph>::out_edge_iterator 				OutEdgeIt;
typedef graph_traits<Graph>::vertex_iterator 				VertexIt;

struct request {
	int starting_station;
	int ending_station;
	int departure_time;
	int arrival_time;
	int profit;

};

void addEdge(int from, int to, int c, int w,
			 EdgeCapacityMap &capacity, EdgeWeightMap &weight, ReverseEdgeMap &rev_edge, Graph &G) {

	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	weight[e] = w;
	capacity[reverseE] = 0;
	weight[reverseE] = -w;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;

}

void testcase() {

	int nr_requests;
	int nr_stations;
	cin >> nr_requests >> nr_stations;

	vector<int> cars(nr_stations);
	for (int i=0; i<nr_stations; i++) {
		cin >> cars[i];
	}

	vector<request> requests(nr_requests);
	int tmax = -1;
	for (int i=0; i<nr_requests; i++) {
		request r;
		
		cin >> r.starting_station >> r.ending_station >>
			   r.departure_time   >> r.arrival_time   >>
			   r.profit;

		// Transform to 0-based
		r.starting_station--;
		r.ending_station--;
	
		// Compute tmax for graph size
		tmax = max(r.arrival_time, tmax);

		requests[i] = r;
	}	

	//cout << "Maximum time found = " << tmax << endl;

	/* Create the graph for the max-flow min-cost problem.
	 * The graph is composed of S branches each with ceil(tmax/30) nodes.
	 * So in total we have S*ceil(tmax/30) nodes.
	 */

	int nr_nodes_per_branch = tmax/30 + 1;
	//cout << "nodes per branch = " << nr_nodes_per_branch << endl;
	int nr_nodes = nr_stations * nr_nodes_per_branch;
	Graph G(nr_nodes);

	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
	EdgeWeightMap weight = get(edge_weight, G);

	Vertex flow_source = add_vertex(G);
	Vertex flow_sink   = add_vertex(G);
	//cout << "Source is " << flow_source << " and sink is " << flow_sink << endl;

	/* The graph is organized as follows: 
	 * - Each branch has nodes from tmax*s up to (s+1)tmax - 1 
	 *   where s is the rental station.
	 * - All the node along the branches are connected with edges
	 *   of infinite capacity and zero cost so that we can move freely through
	 *   the graph.
	 * - The source is connected to the car stations.
	 * - The sink is feeded by the tmax nodes.
	 */

	// Add edges for the source and the sink
	for (int i=0; i<nr_stations; i++) {
		int first_node_id = i * nr_nodes_per_branch;
		addEdge(flow_source, first_node_id, cars[i], 0, capacity, weight, rev_edge, G);
	//	cout << "Added: " << flow_source << " -> " << first_node_id << " (" << cars[i] << ", " << "0)" << endl;
	
		int final_node_id = (i+1)*nr_nodes_per_branch - 1;
		addEdge(final_node_id, flow_sink, INT_MAX, 0, capacity, weight, rev_edge, G);
	//	cout << "Added: " << final_node_id << " -> " << flow_sink << " (" << "INF" << ", " << "0)" << endl;
	}

	//cout << "Adding intermediate edges" << endl;
	// Add the intermediate edges
	for (int station = 0; station < nr_stations; station++) {
		for (int i=0; i<nr_nodes_per_branch-1; i++) {
			int from_node = station*nr_nodes_per_branch + i;
			int to_node = from_node + 1;
			addEdge(from_node, to_node, INT_MAX, 0, capacity, weight, rev_edge, G);
			//cout << "Added: " << from_node << " -> " << to_node << endl;
		}
	}

	for (int i=0; i<nr_requests; i++) {
	//	cout << "Inputing request " << i << endl;
		request r;
		r = requests[i];

		int starting_node = r.starting_station * nr_nodes_per_branch + r.departure_time / 30;
		int ending_node   = r.ending_station   * nr_nodes_per_branch + r.arrival_time / 30;

		addEdge(starting_node, ending_node, 1, -r.profit, capacity, weight, rev_edge, G);	
	//	cout << "Added: " << starting_node << " -> " << ending_node << " : (1, " << -r.profit << ")" << endl;

	}

	//return;
	// Compute flow
	int flow = push_relabel_max_flow(G, flow_source, flow_sink);
	cycle_canceling(G);
	int cost = find_flow_cost(G);
	cout << -cost << endl;



}

int main() {

	int t;
	cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}


