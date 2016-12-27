#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

using namespace std;

void testcase() {
	size_t l, s, w;
	cin >> l >> s >> w;	

	vector<K::Point_2> lamps;
	lamps.reserve(l);

	vector<K::Point_2> stamps;
	stamps.reserve(s);

	vector<int> max_light;
	max_light.reserve(s);

	vector<K::Segment_2> walls;
	walls.reserve(w);


	for (int i=0; i<l; i++) {
		K::Point_2 p;	
		cin >> p;
		lamps.push_back(p);
	}
	
	for (int i=0; i<s; i++) {
		K::Point_2 p;	
		int max_l;
		cin >> p;
		cin >> max_l;
		stamps.push_back(p);
		max_light.push_back(max_l);
	}

	for (int i=0; i<w; i++) {
		K::Point_2 p1, p2;
		cin >> p1 >> p2;
		K::Segment_2 wall(p1, p2);
		walls.push_back(wall);
	}

	
	Program lp(CGAL::SMALLER, true, 0, false, 0);
	// For every stamp check which lamps are lighting it
	
	bool reachable;
	for (int i=0; i<s; i++) { // stamps
		for (int j=0; j<l; j++) { // lamps
			reachable = true;
			K::Segment_2 seg(stamps[i],lamps[j]); // Segment that connects lamp with stamp
			for (int k=0; (k<w) && reachable; k++) { //walls
				if (CGAL::do_intersect(seg, walls[k])) {
					reachable = false; 
				}
			}
			
			if (reachable) {
				double sq_distance = CGAL::squared_distance(stamps[i], lamps[j]);
				// j should be in the uknown set for that stamp
					lp.set_a(j, i, 1/sq_distance);
					lp.set_a(j, i+s, -1/sq_distance);
//					cout << "Set " << i << " and " << i+s << " constraints " << "for " << j << " lamp " << endl; 
			}
			lp.set_l(j, true, 1);
			lp.set_u(j, true, 4096);
		}

//		cout << "Set " << i << " and " << i+s << " b constants " << endl;	
		lp.set_b(i, max_light[i]);
		lp.set_b(i+s, -1);
	}

		
	Solution sol = CGAL::solve_linear_program(lp, ET());

//	cout << sol << endl;

	if (sol.status() == CGAL::QP_INFEASIBLE) {
		cout << "no" << endl;
	}
	else
		cout << "yes" << endl;

}



int main() {

	size_t tests;
	cin >> tests;
	
	while(tests--) {
		testcase();
	}
	
	return 0;
}
