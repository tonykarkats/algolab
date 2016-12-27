#include <iostream>
#include <stdexcept>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <boost/bind.hpp>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;

int main() {

	ios_base::sync_with_stdio(false);	
	int n, intersected;
    double r,s,t,u,x,y,a,b;
    K::Point_2 p1,p2;
    K::Point_2 o1,o2;
    K::Segment_2 obstacle;
    K::Ray_2 ray;

	std::cin >> n;
	while (n != 0) {
        intersected = 0;
        std::cin >> x;
        std::cin >> y;
        std::cin >> a;
        std::cin >> b;
        p1 = K::Point_2(x, y);
        p2 = K::Point_2(a, b);
        ray = K::Ray_2(p1, p2);

        for (int i=0; i<n; i++) {
            std::cin >> r;
            std::cin >> s;
            std::cin >> t;
            std::cin >> u;
            o1 = K::Point_2(r, s);
            o2 = K::Point_2(t, u);
			//If segment
            //Check for intersection

            	obstacle = K::Segment_2(o1, o2);
            	if (CGAL::do_intersect(ray, obstacle)){
                	cout << "yes" << endl;
                	intersected = 1;
					//read the rest of the input and break the loop
					//cin.ignore(4*(n-i+1), EOF);
					for (int j=i+1; j<n; j++) {
            			std::cin >> r;
            			std::cin >> s;
            			std::cin >> t;
            			std::cin >> u;
					}	
                	break;
            	}

        }
	
        if (intersected == 0)
            cout << "no" << endl;

        std::cin >> n;
    }

    return 0;
}
