#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_edges_iterator Edge_Iterator;

using namespace std;

double ceil_to_double(const K::FT& x) {
	double a = std::ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}

void testcase(size_t n) {
	//Store points, so that they can be inserted more efficiently later
	vector<K::Point_2> pts;
	pts.reserve(n);

	for (size_t i=0; i<n; i++) {
		K::Point_2 p;
		cin >> p;
		pts.push_back(p);
	}


	size_t m;
	cin >> m;
//	vector<K::Point_2> restaurants;
//	pts.reserve(m)


	// Construct the triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	// Get nearest vertex
	
	for (size_t i=0; i<m; i++) {
		K::Point_2 p;
		cin >> p;
		Triangulation::Vertex_handle v = t.nearest_vertex(p);
		cout << fixed << setprecision(0) << CGAL::squared_distance(v->point(), p) << endl;
//		restaurants.push_back(p);
	}


}

int main() {

	ios_base::sync_with_stdio(false);
	size_t n;
	cin >> n;
	while(n!=0) {
		testcase(n);
		cin >> n;
	}

	return 0;
}
