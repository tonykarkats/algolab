#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/squared_distance_2.h>
#include <vector>

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
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

using namespace std;

void testcase() {

	// a: asteroid particles
	// s: laser shots
	// b: bounty hunters

	int a, s, b;
	cin >> a >> s >> b;

	// e: Total energy of the ship
	long e;
	cin >> e;
	
	vector<K::Point_2> particles;
	vector<K::Point_2> lasers;
	vector<K::Point_2> hunters;
	vector<int> density;

	// Input Particles
	for (int i=0; i<a; i++) {
		// |x| < 2^24 so it fits in a long
		long x, y;
		cin >> x >> y;
		particles.push_back(K::Point_2(x, y));		

		long dens;
		cin >> dens;
		density.push_back(dens);
	}

	// Input Lasers
	for (int i=0; i<s; i++) {
		long x, y;
		cin >> x >> y;
		lasers.push_back(K::Point_2(x, y));
	}
	
	// Input Bounty Hunters
	for (int i=0; i<b; i++) {
		long x, y;
		cin >> x >> y;
		hunters.push_back(K::Point_2(x, y));
	}

	vector<long> radii;
	if (b != 0) {

		// Create Delaunay Triangulation on the set of bounty hunters so that I can easily
		// precompute the radii of the lasers
		
		Triangulation t;
		t.insert(hunters.begin(), hunters.end());
		
		// Precompute the radii of the laser shots as the distance to the closest bounty hunter
		for (int i=0; i<s; i++) {
			Triangulation::Vertex_handle v = t.nearest_vertex(lasers[i]);
			long long sq_radius = CGAL::squared_distance(v->point(), lasers[i]);
			radii.push_back(sq_radius);
	//		cout << "Closest distance = " << sq_radius << endl;
		}
	}
	else {
		// The radius for every laser can be infinite
		for (int i=0; i<s; i++)
			radii.push_back(LONG_MAX);
	}
	
	// Start Setting up the Linear Program
	
	Program lp(CGAL::SMALLER, true, 0, false, 0);
	
	// First Constraint
	// e0 + e1 + .. + e(s-1) <= e
	for (int i=0; i<s; i++) {
		lp.set_a(i, 0, 1);
	}
	lp.set_b(0, e);

	// For each particle the total energy received must be equal or greater than
	// its density (a restrictions)

	for (int i=0; i<a; i++) {
		for (int j=0; j<s; j++) {
			long long sq_dist_from_laser;
			sq_dist_from_laser = CGAL::squared_distance(particles[i], lasers[j]);
			// If particle is in radius then add the respective amount of energy to it
			if (sq_dist_from_laser <= radii[j]) {
				if (sq_dist_from_laser != 0) {
					lp.set_a(j, i+1, 1.0/sq_dist_from_laser);
//					cout << "Setting constraint " << i+1 << " for variable " << j << " to " << 1.0/sq_dist_from_laser << endl;
				}
				else
					lp.set_a(j, i+1, 1);
			}
		}
		lp.set_r(i+1, CGAL::LARGER);	
		lp.set_b(i+1, density[i]);
	}

	Solution sol = CGAL::solve_linear_program(lp, ET());
	assert(sol.solves_linear_program(lp));

	if (sol.status() == CGAL::QP_INFEASIBLE)
		cout << "n" << endl;
	else
		cout << "y" << endl;

}


int main() {

	int t;
	cin >> t;

	while (t--)
		testcase();

	return 0;
}
