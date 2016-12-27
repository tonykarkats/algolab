#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <vector>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <algorithm>
#include <numeric>

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

	// Read Input
	int n;
	cin >> n;

	vector<int> a;
	vector<int> c;

	for (int i=0; i<n; i++) {
		int a_in, c_in;
		cin >> a_in >> c_in;
		a.push_back(a_in);
		c.push_back(c_in);
	}

	vector<int> p;
	vector<int> s;


	int max_price = 0;
	for (int i=0; i<n; i++) {
		int p_in, s_in;
		cin >> s_in >> p_in;
		s.push_back(s_in);
		p.push_back(p_in);
		if (max_price < p_in)
			max_price = p_in;
	}

	long sum_students = accumulate(s.begin(), s.end(), 0);

	vector<int> u;
	vector<int> e;

	for (int i=0; i<n-1; i++) {
		int u_in, e_in;
		cin >> u_in >> e_in;
		u.push_back(u_in);
		e.push_back(e_in);
	}

	Graph G(n);
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
	EdgeWeightMap weight = get(edge_weight, G);

	Vertex flow_source = add_vertex(G);
	Vertex flow_sink   = add_vertex(G);

	// Create graph

	for (int i=0; i<n; i++) {
		addEdge(flow_source, i, a[i], c[i], capacity, weight, rev_edge, G);	
		addEdge(i, flow_sink, s[i], max_price-p[i], capacity, weight, rev_edge, G);
		if (i != n-1) {
			addEdge(i, i+1, u[i], e[i], capacity, weight, rev_edge, G);	
		}
	}

	//Compute the flow of the graph
	
	successive_shortest_path_nonnegative_weights(G, flow_source, flow_sink);
	long flow = 0;
	for (int i=0; i<n; i++) {
		Edge e = edge(i, flow_sink, G).first;
		flow += capacity[e] - res_capacity[e];

	}


	long cost = find_flow_cost(G) - flow*max_price;
	if (flow == sum_students)
		cout << "possible ";
	else
		cout << "impossible ";
	cout << flow << " " << -cost << endl;
}


int main() {

	int t;
	cin >> t;
	while (t--)
		testcase();
	return 0;
}

