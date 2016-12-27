#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/find_flow_cost.hpp>

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
	int tmax = -1; // Needed?
	
	
	vector<set<int>> times(nr_stations);
	for (int i=0; i<nr_requests; i++) {
		request r;
		
		cin >> r.starting_station >> r.ending_station >>
			   r.departure_time   >> r.arrival_time   >>
			   r.profit;

		// Transform to 0-based
		r.starting_station--;
		r.ending_station--;

		// Insert the times into the map
		times[r.starting_station].insert(r.departure_time);
		times[r.ending_station].insert(r.arrival_time);
	
		// Compute tmax for graph size
		tmax = max(r.arrival_time, tmax);

		requests[i] = r;
	}	

	//cout << "Maximum time found = " << tmax << endl;

	/* Now every branch has a different number of nodes.
	 * Here we create the compressed nodes and keep them in the map */

	Graph G;

	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
	EdgeWeightMap weight = get(edge_weight, G);

	int global_station_count = 0; // Needed
	vector<map<int, int>> compress_map(nr_stations);
	
	/* This map holds the translation for the coordinates for every station.
	 * The key is the timeslice and the value is the input time and the value is the
	 * compressed coordinate
	 */

	vector<int> station_nodes_nr(nr_stations);
	int sum_of_durations = 0;
	for (int i=0; i<nr_stations; i++) {
		set<int> station_nodes;
		station_nodes = times[i];

		// If not present insert 0 and tmax to every branch
		station_nodes.insert(0);
		station_nodes.insert(tmax);

		int station_nodes_count = station_nodes.size();
		station_nodes_nr[i] = station_nodes_count;
		//cout << "Station " << i << " has " << station_nodes_count << " nodes" << endl;
		
		map<int, int> station_map;
		// Iterate over the station_nodes and map the compressed coordinates
		set<int>::iterator it;
		int node_count = 0;
		int last_time = 0;
		for (it = station_nodes.begin(); it != station_nodes.end(); it++) {
				//cout << *it << endl;
				int global_node_id = global_station_count + node_count ;
				//cout << "Inserting into map " << *it << " -> " << global_node_id << endl;
				station_map.insert(pair<int, int>(*it, global_node_id));
				// Now is a good time to add intermediate edges
				if (node_count < station_nodes_count - 1) {
					set<int>::iterator next_element = it;
					next_element++;
					addEdge(global_node_id, global_node_id + 1, INT_MAX, (*(next_element) - *it)*100, capacity, weight, rev_edge, G);
					if (i == 0) {
						sum_of_durations += (*(next_element) - *it) ;
					}
					//cout << "Added edge (" << global_node_id << ", " << global_node_id + 1 << " with " << " INF/ " << *next_element - *it << endl;
				}

				node_count++;
		}
		compress_map[i] = station_map;
		global_station_count += station_nodes_count;
	}

	//cout << "SUM of durations = " << sum_of_durations << endl;
	//cout << "Total nodes without source-sink" << global_station_count << endl;

	Vertex flow_source = add_vertex(G);
	Vertex flow_sink   = add_vertex(G);

	// Add edges for the source and the sink
	int nodes_before = 0;
	for (int i=0; i<nr_stations; i++) {
		// Add first element of every station to source
		//cout << "Adding for source " << flow_source << " -> " << nodes_before << endl;
		addEdge(flow_source, nodes_before, cars[i], 0, capacity, weight, rev_edge, G);
		// Add last element to sink
		nodes_before += station_nodes_nr[i];
		addEdge(nodes_before-1, flow_sink, INT_MAX, 0, capacity, weight, rev_edge, G);
		//cout << "Adding for sink " << nodes_before - 1 << " -> " << flow_sink << endl;
	}

	for (int i=0; i<nr_requests; i++) {
	//	cout << "Inputing request " << i << endl;
		request r;
		r = requests[i];

		// Lookup the corresponding nodes in the map
		
		int starting_node = compress_map[r.starting_station][r.departure_time];
		int ending_node = compress_map[r.ending_station][r.arrival_time];
		int duration = r.arrival_time - r.departure_time ;
	
		
		addEdge(starting_node, ending_node, 1, duration * 100 - r.profit, capacity, weight, rev_edge, G);	
		//cout << "Adding for requests " << starting_node << " -> " << ending_node << " with 1/ " << duration * 100 - r.profit << endl;

	}

	// Compute flow using nonnegative weights
	successive_shortest_path_nonnegative_weights(G, flow_source, flow_sink);
	long flow = 0;

	nodes_before = 0;
	for (int i=0; i<nr_stations; i++) {
		Edge e = edge(flow_source, nodes_before, G).first;
		flow += capacity[e] - res_capacity[e];
		nodes_before += station_nodes_nr[i];
	}
	// Compute total amount of flow
	//for (int i=0; i<nr_stations; i++) {
	//	Edge e = edge(flow_source, i*nr_nodes_per_branch, G).first;	
	//	flow += capacity[e] - res_capacity[e];

	//}

	/*
	cout << "Flow = " << flow << endl;

	VertexIt vert_i, vert_end;
    OutEdgeIt edge_i, edge_end;

	for(tie(vert_i, vert_end) = vertices(G); vert_i != vert_end; ++vert_i)
       for(tie(edge_i, edge_end) = out_edges(*vert_i, G); edge_i != edge_end; ++edge_i) {
		int edge_flow = capacity[*edge_i] - res_capacity[*edge_i]; 
		if (edge_flow > 0)
			cout << *edge_i << " flow = " << edge_flow << endl;
	}
	*/

	long cost = find_flow_cost(G) - sum_of_durations * 100 * flow;
	//cout << "-------------" << endl;
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


