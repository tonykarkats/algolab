#include <iostream>
#include <cmath>
#include <climits>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Point_set_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Point_set_2<K, Tds> PSet;
typedef CGAL::Point_set_2<K, Tds>::Vertex_handle Vertex_handle;

void testcase() {

	// Input nr of participants and nr of lamps	
	int n, m;
	cin >> m >> n;

	/* Input Participants as a pair :
	 * .first  : Position
	 * .second : Radius
	 */
	vector<pair<K::Point_2, int>> participants(m);
	for (int i=0; i<m; i++) {
		int x, y, r;
		cin >> x >> y >> r;
		participants[i] = make_pair(K::Point_2(x, y), r);
	}

	// Input height of lamp
	int h;
	cin >> h;

	/* Input lamps as a pair :
	 * .first  : Position
	 * .second : Lamp index
	 */ 
	
	vector<pair<K::Point_2, int>> lamps(n);

	for (int i=0; i<n; i++) {
		int l_x, l_y;
		cin >> l_x >> l_y;
		lamps[i] = make_pair(K::Point_2(l_x, l_y), i);
	}

	// Create Delaunay Triangulation of the lamps
	PSet lamps_tr;
	lamps_tr.insert(lamps.begin(), lamps.end());	

	// Contains the ID of the light that hit a participant first or MAX if he was not hit
	vector<int> min_light_hit(m, INT_MAX);

	// Globally max light that hit someone
	int max_light_hit = -1;

	// For every participant check the his closest lamp.
	for (int participant_index = 0; participant_index < m; participant_index++) {
		// Get closest lamp
		K::Point_2 participant_point = participants[participant_index].first;
		Vertex_handle lamp_vertex = lamps_tr.nearest_neighbor(participant_point);

		// Maximum distance in which the lamp kills a participant (squared)
		double sq_max_kill_distance = pow(participants[participant_index].second + h, 2);

		// If closest lamp is too far away then the participant isn't killed by any other lamp
		if (CGAL::squared_distance(lamp_vertex->point(), participant_point) >= sq_max_kill_distance) {
			continue;
		}

		// Iterate over all lamps searching for the one that hits the participant first
		for (int lamp_index = 0; lamp_index < n; lamp_index++) {
			if (CGAL::squared_distance(lamps[lamp_index].first, participant_point) < sq_max_kill_distance) {
				// The participant dies
				min_light_hit[participant_index] = lamps[lamp_index].second;
				max_light_hit = max(max_light_hit, lamps[lamp_index].second);
				break; // No need to continue
			}
		}
	}

		// Survivors list
		vector<int> survivors;
		for (int participant_index = 0; participant_index < m; participant_index++) {
			if (min_light_hit[participant_index] == INT_MAX) {
				survivors.push_back(participant_index);
			}
		}

		// If everyone was hit, search for ones that were hit last
		if (survivors.size() == 0) {
			for (int participant_index = 0; participant_index < m; participant_index++) {
				if (min_light_hit[participant_index] == max_light_hit) {
					survivors.push_back(participant_index);
				}
			}
		}

		// Print our sorted list
		sort(survivors.begin(), survivors.end());
		for (int i=0; i<survivors.size(); i++) {
			cout << survivors[i] << " " ;
		}
		cout << endl;

}

int main() {

	int t;
	cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}
