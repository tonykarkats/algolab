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

	//Construct the triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	vector<K::FT> distances;
	//Iterate over all edges to find the smallest distance
	for (Edge_Iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
	//	cout << endl << t.segment(e) << endl;	
		Triangulation::Edge edge = *e;
		Triangulation::Vertex_handle v1 = edge.first->vertex((edge.second + 1) % 3);
		Triangulation::Vertex_handle v2 = edge.first->vertex((edge.second + 2) % 3);
	//	cout << "P1 = " << v1->point() << ". " << "P2 = " << v2->point() << endl;
		K::FT d = sqrt(squared_distance(v1->point(), v2->point()));
		distances.push_back(d/2);
//		cout << d/2.000 << endl;
//	  	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(10) << CGAL::to_double(d) << std::endl ;

	//	if (d < min_distance)
	//		min_distance = d;
	//	cout << "d = " << d*50 << endl;

	}

	cout << fixed << setprecision(0) << ceil_to_double(*min_element(distances.begin(), distances.end()) * 100.0) << endl;
}


int main() {

	size_t n;
	cin >> n;
	while(n!=0) {
		testcase(n);
		cin >> n;
	}

	return 0;
}
