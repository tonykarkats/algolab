#include <vector>
#include <cmath>
#include <iostream>
#include <map>

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace std;
using namespace boost;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_edges_iterator Edge_Iterator;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge; //Edge type
typedef graph_traits<Graph>::vertex_descriptor Vertex; //Edge type
typedef graph_traits<Graph>::edge_iterator EdgeIt; //Edge Iterator


bool is_feasible(int n, int r, int k, vector<K::Point_2>& planets, map<K::Point_2, Vertex>& points_map) {

	if (k >= n)
		return false;
	
	if (n == 2) {
		if (k == 1) return true;
	}

	long long r_squared = pow(r, 2);
	// Create Delaunay Triangulation for points {P[k], ..., P[n-1]}
	Triangulation triang;
	triang.insert(planets.begin() + k, planets.end());

	// Prepare Graph
	Graph G;

	// Iterate over the edges of the triangulation and create the graph accordingly
	Edge_Iterator eit;
	for (eit = triang.finite_edges_begin(); eit	!= triang.finite_edges_end(); ++eit) {
		// Get the 2 vertices of e
		Triangulation::Edge e = *eit;
		Triangulation::Vertex_handle v1 = e.first->vertex((e.second + 1) % 3);
		Triangulation::Vertex_handle v2 = e.first->vertex((e.second + 2) % 3);
		
		// Check if points are closer than the vessel radius and add to the graph
		if (CGAL::to_double(CGAL::squared_distance(v1->point(), v2->point())) <= r_squared) {
			add_edge(points_map[v1->point()], points_map[v2->point()], G);
	//		cout << "Added edge " << points_map[v1->point()] << points_map[v2->point()] << endl;
		}

	}
	
	
	// If the Graph is empty return false
	if (num_vertices(G) == 0)
		return false;
	
	// We now compute the connected components of the graph
	vector<int> component(num_vertices(G));
	int num_components = connected_components(G, &component[0]);

	vector<int> component_size(num_components);
	for (int i=0; i<component.size(); i++) {
		component_size[component[i]]++;
	}

	// Find max component size
	return (*max_element(component_size.begin(), component_size.end()) >= k) ;
}


void testcase() {

	// Read input
	// n: number of planets
	// r: vessel radius
	int n, r;
	cin >> n >> r;


	vector<K::Point_2> planets(n);
	
	// This map is used to map the planet K::Point_2s with a specific id
	// for the graph
	map<K::Point_2, Vertex> points_map;
	
	for (int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		K::Point_2 p(x,y);
		planets[i] = p;
		points_map.insert(make_pair(p, i));
	}

	if (r == 0) {
		// The vessel cannot move
		cout << 1 << endl;
		return;
	}

	// Fast exponentiation and binary search to find k
	int k = 1;

	while (is_feasible(n, r, k, planets, points_map)) {
	//	cout << "k= " << k << " is a feasible solution" << endl;
		k *= 2;
	}

	// We now know that the k we search for is in the range [k/2, k]
	// Do a binary search to find it!!
	int k_low = k/2;
	int k_high = k;
	int k_mid;
	int val;
	
	
	while (k_low <= k_high) {
//	cout << "Binary search in " << k_low << " , " << k_high << endl;
		k_mid = (k_low + k_high) / 2;
		if (is_feasible(n, r, k_mid, planets, points_map)) {
			k_low = k_mid + 1;	
			val = k_mid;
		}
		else {
			k_high = k_mid - 1;
		}

	}

	cout << val << endl;
}

int main() {

	int t;
	cin >> t;
	
	while (t--) {
		testcase();
	}

	return 0;
}
