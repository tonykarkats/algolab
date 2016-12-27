#include <iostream>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <math.h>

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

//		for (int i=0; i<n; i++)
//			cout << citizens[i] << endl;
//		cout << "-------" << endl;

		Min_circle mc(citizens, citizens + n , true);
		Traits::Circle c = mc.circle();
//		cout << ceil(sqrt(c.squared_radius())) << endl;
		K::FT min_radius = c.squared_radius() + 1000000;
//		cout << "Min Radius = " <<  min_radius << endl;
		CGAL::Min_circle_2< Traits >::Support_point_iterator it;

		for (it = mc.support_points_begin(); it != mc.support_points_end(); it++) {
			//Create min circle for citizens_without_*it []	
//			cout << "Point on circle : " << *it << endl;
			K::Point_2 *pbegin = citizens;
			K::Point_2 *pend = citizens + sizeof(citizens)/sizeof(K::Point_2);
			pend = std::remove(pbegin, pend, *it);
//			cout << "After removing " << *it << endl;
			Min_circle mc_left(pbegin, pend, true);
			Traits::Circle c_left = mc_left.circle();
//			for (K::Point_2 *p = pbegin; p != pend; ++p)
//				cout  << *p << endl ;
//			cout << "Radius = " << c_left.squared_radius() << endl; 
			if (c_left.squared_radius() < min_radius){
//				cout << "Updating min_radius" << endl;
				min_radius = c_left.squared_radius();
			}
//			cout << "-------" << endl;
		
		}
		cout <<  ceil(sqrt(min_radius)) << endl;
		//Print out the least of the distances calculated above!
		//cout << "-------------------------" << endl;	
        std::cin >> n;
    	}
	
    return 0;
}
