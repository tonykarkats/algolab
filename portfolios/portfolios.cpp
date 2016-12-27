#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpz ET; 
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

using namespace std;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {

	int n, m;
	cin >> n >> m;

	while (n != 0 && m != 0) {
		
		int costs[n];
		int ret[n];
		int covar[n][n];		
		int C, R, V;
		double x[n];	

		for (int i=0 ; i<n ; i++) {
			cin >> costs[i] >> ret[i];
		}

		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++){
				cin >> covar[i][j];
			}
		}
		
		for (int i=0; i<m; i++) {
		
			Program qp (CGAL::SMALLER, true, 0, false, 0); 
			cin >> C >> R >> V;

			//Constraint on minimum return
			for (int i=0; i<n; i++) 
				qp.set_a(i, 0, -ret[i]);
	
			qp.set_b(0, -R);
	
			//Strategy constraint Sum(x[i]) = 1
		
//			if (n >1) {	
//				for (int i=0; i<n; i++)
//					qp.set_a(i, 1, 1);
//		
//				qp.set_b(1, 1);
//				qp.set_r(1, CGAL::EQUAL);
//			}

			//Constraint on maximum cost
			for (int i=0; i<n; i++) {
				qp.set_a(i, 2, costs[i]);
			}
		
			qp.set_b(2, C);

			//Objective function to minimize
			for(int i=0; i<n; i++)
				for (int j=0; j<n; j++){
					if (i >= j)
						qp.set_d(i, j, covar[i][j] * 2);
			}
	
			//Solve the problem
			Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
			assert (s.solves_quadratic_program(qp));
	
			//With the values calculated, examine if the covariance restriction can be met
			
			// output
			if (s.status() == CGAL::QP_INFEASIBLE) {
			  std::cout << "No." << endl;
			  continue; 
			} else {
			  
			  assert (s.status() == CGAL::QP_OPTIMAL);
			  
			double var = CGAL::to_double(s.objective_value());
//				cout << "V = , " << V << ", " << "sol = " << var << endl;	
			if (var <= V)
				cout << "Yes." << endl;
			else
				cout << "No." << endl;	 
	
			}
	
		}	
		cin >> n >> m;
	}

	return 0;
}
