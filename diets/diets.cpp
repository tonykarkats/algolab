#include <cassert>
#include <iostream>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Quotient.h>
#include <cmath>
#include <vector>

//Choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

using namespace std;

//program and solution types
typedef CGAL::Quadratic_program<long> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;




int run (int n, int m) {

//	int n, m;
//	cin >> n >> m;
	
//	while ((n != 0) && (m != 0)) {

			Program qp (CGAL::SMALLER, true, 0, false, 0);
			vector<long> mins;
			vector<long> maxs;
			vector<long> costs;
			
			mins.clear();
			maxs.clear();
			costs.clear();

			int min, max;
			for (int i=0; i<n; i++) {
				//i-th nutrient
				cin >> min >> max;
				//cout << "Read: " << min << ", " << max << endl;
				mins.push_back(min);
				maxs.push_back(max);
			}
			
			for (int i=0; i<m; i++) {
				//Iterate over foods
				long cost;
				cin >> cost;
				//cout << "Read: " << cost << endl;
				long nut_amount;
				
//				cout << "Food : " << i << endl;
				//For minimum constraints
				for (int j=0; j<n; j++) {
					//Nutrients in food i
					cin >> nut_amount;
				//	cout << "Read " << nut_amount << endl;
				//	cout << "Setting constraint "  << j << " to " << -nut_amount << endl;
					qp.set_a(i, j, -nut_amount);
					qp.set_a(i, n+j, nut_amount);
				}
			
				//For maximum constraints
		//		for (int j=n; j<2*n; j++) {
					//Nutrients in food i
		//			cout << "Setting constraint " << j << "to " << nut_amount << endl;
		//			qp.set_a(i, j, nut_amount);
		//		}

				//Setting minimized function
				qp.set_c(i, cost);


		}

		for (int i=0; i<n; i++) {
//			cout << "Setting values  " << mins[i] << "and " << maxs[i] << endl;
			qp.set_b(i, -mins[i]);
			qp.set_b(n+i, maxs[i]);

		}	

	
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		if (s.status() == CGAL::QP_INFEASIBLE)
			cout << "No such diet." << endl;
		else if (s.is_optimal()) {
				CGAL::Quotient<ET> obj_value = s.objective_value();
			    cout << floor(CGAL::to_double(obj_value)) << endl;
		}
	

//		cin >> n >> m;
		
//	}
}

int main() {
	
	int n, m;
	cin >> n >> m;
	
	while ((n != 0) && (m != 0)) {
		run(n, m);
		cin >> n >> m;
	}

	return 0;	
}
