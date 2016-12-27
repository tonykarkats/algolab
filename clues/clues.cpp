#include <vector>
#include <cmath>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Point_set_2.h>

using namespace std;
using namespace boost;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_edges_iterator Edge_Iterator;
typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;

typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Point_set_2<K, Tds> PSet;
typedef CGAL::Point_set_2<K, Tds>::Vertex_handle Vertex_handle;

void testcase() {

	int nr_stations, nr_clues;
	K::FT range;
	cin >> nr_stations >> nr_clues >> range;


	// Use squared distances for efficiency
	range = pow(range, 2);

	/* Read in the stations in a vector of pairs
	 * .first  : Station index
	 * .second : Station position
	 */

	vector<pair<K::Point_2, int>> stations(nr_stations);
	for (int i=0; i<nr_stations; i++) {
		int x, y;
		cin >> x >> y;

		stations[i] = make_pair(K::Point_2(x, y), i);
	}


	// Read clues
	vector<pair<K::Point_2, K::Point_2>> clues(nr_clues);
	for (int i=0; i<nr_clues; i++) {
		int a_x, a_y, b_x, b_y;
		cin >> a_x >> a_y >> b_x >> b_y;

		clues[i] = make_pair(K::Point_2(a_x, a_y), K::Point_2(b_x, b_y));
	}

	// Create graph
	Graph G(nr_stations);	

	// Create Delaunay triangulation for the stations so that we can efficiently
	// calculate nearest neighbours. We are going to use a CGAL::Point_set_2 here
	// to efficiently find all the points in a given radius.

	PSet triang;
	triang.insert(stations.begin(), stations.end());

	// Iterate over all the stations and for every one check which stations lie
	// inside the radius

	for (int station_i=0; station_i<nr_stations; station_i++) {
		K::Point_2 station = stations[station_i].first;
		K::Circle_2 station_circle = K::Circle_2(station, range);

		// Get all stations inside that circle
		vector<Vertex_handle> stations_in_range;
		triang.range_search(station_circle, back_inserter(stations_in_range));

		// Go through the stations in range and make sure they are at distance at 
		// least 'range' from each other. Otherwise there are conflicts in the graph
		// and none of the clues can succeed trhough.
		for (int i=0; i<stations_in_range.size(); i++) {
			for (int j=i+1; j<stations_in_range.size(); j++) {
				int station1 = stations_in_range[i]->info();
				int station2 = stations_in_range[j]->info();

				// We also have to make sure that we do not check the 'station' of the outer
				// for-loop again.
				if ((station1 != station_i) && (station2 != station_i)) {
					if (CGAL::squared_distance(stations_in_range[i]->point(), stations_in_range[j]->point()) <= range) {
						// There is a conflict
						for (int i=0; i<nr_clues; i++) {
							cout << "n";
						}
						cout << endl;
						return;
					}
				}
			}
		}	

		// Now stations are ok so we add the edges to the graph
		for (int i=0; i<stations_in_range.size(); i++) {
			int to_station = stations_in_range[i]->info();
			if (to_station != station_i) {
				add_edge(station_i, to_station, G);
			}
		}		

	}

	// We now check for bipartiteness
	if (!is_bipartite(G)) {
		for (int i=0; i<nr_clues; i++) {
			cout << "n";
		}
		cout << endl;
		return;
	}
	else {
		// We have to make sure there is a path for the clues.
		// There is a path only if the start and end clue are in the same connected
		// component.
		vector<int> in_component(nr_stations);
		connected_components(G, &in_component[0]);

		for (int i=0; i<nr_clues; i++) {
			K::Point_2 source = clues[i].first;
			K::Point_2 target = clues[i].second;

			// If clues are within 'range' they can communicate directly
			if (CGAL::squared_distance(source, target) <= range) {
				cout << "y";
				continue;
			}

			// Check to see if a station can be reached from the start
			Vertex_handle nearest_to_start;
			nearest_to_start = triang.nearest_vertex(source);
			if (CGAL::squared_distance(nearest_to_start->point(), source) > range) {
				cout << "n";
				continue;
			}

			// Same for the end
			Vertex_handle nearest_to_end;
			nearest_to_end = triang.nearest_vertex(target);
			if (CGAL::squared_distance(nearest_to_end->point(), target) > range) {
				cout << "n";
				continue;
			}

			// Now we only have to check whether the starting and ending stations 
			// are in the same connected component
			if (in_component[nearest_to_end->info()] == in_component[nearest_to_end->info()]) {
				cout << "y";
			}
			else {
				cout << "n";
			}
		}
		cout << endl;
	}

}

int main() {

	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);	
	cout << fixed << setprecision(0);
	int t;
	cin >> t;
	
	while(t--) {
		testcase();
	}

	return 0;
}
