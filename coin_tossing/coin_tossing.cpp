#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
			property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type 			EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type 			ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor				Edge;
typedef graph_traits<Graph>::vertex_descriptor				Vertex;

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

	int n, m;
	int unknown_games = 0;
	cin >> n >> m;
	int won[n];

	for (int i=0; i<n; i++)
		won[i] = 0;	
	//The size of the graph is the number of players plus the number of the games
	Graph G(n+m); 
	EdgeCapacityMap capacity = get(edge_capacity, G);
	ReverseEdgeMap rev_edge = get(edge_reverse, G);
	ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

	Vertex flow_source = add_vertex(G);
	Vertex flow_sink = add_vertex(G);
//	cout << "source = " << flow_source << endl;
//	cout << "sink = " << flow_sink << endl;
	//Add source and sink -> Na brw poia einai apo ta nodes kai na ta balw mona tous

	for (int i=0; i<m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		switch (c) {
			case 1:
			//	addEdge(i, m+a, 1, capacity, rev_edge, G);
			//	cout << "Adding edge " << i << ", " << m+a << endl;
				won[a]++;
				break;
			case 2:
			//	addEdge(i, m+b, 1, capacity, rev_edge, G);
			//	cout << "Adding edge " << i << ", " << m+b << endl;
				won[b]++;
				break;
			case 0:
				addEdge(i, m+a, 1, capacity, rev_edge, G);
				addEdge(i, m+b, 1, capacity, rev_edge, G);
			//	cout << "Adding edges " << i << ", " << m+a << " and " << i << " , " << m+b << endl;
				addEdge(flow_source, i, 1, capacity, rev_edge, G);
				unknown_games++;
			//	cout << "S: Adding edge " << flow_source << ", " << i << " with capacity " << 1 << endl; 
				break;
		}

	}

	//Add edges for sink 
	int possible = 1;
	int sum_s = 0;
	for (int i=0; i<n; i++) {
		int s;
		cin >> s;
		if (s >= won[i]) {
			addEdge(m+i, flow_sink, s-won[i], capacity, rev_edge, G);
			sum_s += s-won[i];
//			cout << "Adding edge " << m+i << ", " << flow_sink << " with capacity " << s-won[i] << endl; 
		}
		else {
			possible = 0;
		}
			
	}

	if (possible) {
		long flow = edmonds_karp_max_flow(G, flow_source, flow_sink);
		if ((flow == unknown_games) && (sum_s <= unknown_games))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	else 
		cout << "no" << endl;
}	


int main() {

	int T;
	cin >> T;
	int i = T;
	while (T--){
//		cout << "Testcase " << i-T << endl << "------------------" << endl;
		testcase();
	}
	return 0;
}

