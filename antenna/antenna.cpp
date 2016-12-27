#include <iostream>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <cmath>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits>     Min_circle;

int main() {
	
	int n, intersected;
    double x,y;
	std::cin >> n;
	while (n != 0) {
		K::Point_2 citizens[n];
        for (int i=0; i<n; i++) {
            cin >> x;
            cin >> y;
			citizens[i] = K::Point_2(x,y);
        }
		
		Min_circle mc(citizens, citizens + n, true);
		Traits::Circle c = mc.circle();
		//cout << c.squared_radius() << endl;
		cout << ceil(sqrt(c.squared_radius())) << endl;

        std::cin >> n;
    }

    return 0;
}
