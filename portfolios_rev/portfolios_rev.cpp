#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <vector>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpz ET; 
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

using namespace std;

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

bool solvable(int n, int C, int R, int V, vector<int>& cost, vector<int>& exp_return, vector<vector<int>> covar) {
	
	// Exactly as portfolios. Solve QP with C, R, V restrictions and return if feasible

	Program qp(CGAL::SMALLER, true, 0, false, 0);
	
	// Constraint 0: Maximum cost
	for (int i=0; i<n; i++) {
		qp.set_a(i, 0, cost[i]);
	}
	qp.set_b(0, C);

	// Constraint 1: Minimum Return
	for (int i=0; i<n; i++) {
		qp.set_a(i, 1, exp_return[i]);
	}
	qp.set_b(1, R);
	qp.set_r(1, CGAL::LARGER);

	// Obj. Function to Minimize
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i>=j)
				qp.set_d(i, j, covar[i][j] * 2); // CAREFUL HERE!
		}
	}

	Solution sol = CGAL::solve_nonnegative_quadratic_program(qp, ET());

	return (sol.is_optimal() && (sol.objective_value() <= V));


}

int main() {

	int n, m;
	cin >> n >> m;

	while ((n != 0) && (m != 0)) {
		
		// Input cost and expected return for every asset
		vector<int> cost(n);
		vector<int> exp_return(n);
		for (int i=0; i<n; i++) {
			cin >> cost[i] >> exp_return[i];
		}

		// Input covariances
		vector<vector<int>> covar(n, vector<int>(n));
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				cin >> covar[i][j];
			}
		}
	
		// Input Cost and Covariance Constraints	
		int C, V;
		for (int i=0; i<m; i++) {
			cin >> C >> V;
		
			/* We are implementing the risk-averse strategy as mentioned
			 * on the LP slides p. 75. We cannot just solve for maximum return
			 * as the variance constraints on the risk are quadratic.
			 * Therefore we increase the return rate until we find the maximum
		     * that is solvable and then narrow down the solution with binary search
			 */
			
			 int R = 1;
			 while (solvable(n, C, R, V, cost, exp_return, covar)) {
				R *= 2;
			 } 
				
			 // We now know that the maximum is in the range [R/2, R]
			 // Use binary search to find it

			 int low = R/2;
			 int high = R;
			 int val;

			 while (low <= high) {
			 	R = (high - low)/2 + low;
				if (solvable(n, C, R, V, cost, exp_return, covar)) {
					low = R+1;
					val = R;
				}
				else {
					high = R - 1;
				}
			 }

			 cout << val << endl;
			
		}

		cin >> n >> m;
		
	}

	return 0;
}
