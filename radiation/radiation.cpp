#include <iostream>
#include <cassert>
#include <vector>

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET; 
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

using namespace std;

typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

struct Cell {
	int x;
	int y;
	int z;
};

/* This function tests whether a specific configuration of healthy and tumorous 
 * cells is solvable for a specific dimension. 
 */

bool can_solve(const vector<Cell>& healthy, const vector<Cell>& tumor, int dim) {

	// Set up our linear program. There is no constraint for the variable
	// range.
	Program qp (CGAL::LARGER, false, 0, false, 0);

	// Set up h constraints for the healthy cells
	int h = healthy.size();
	
	for (int i=0; i<h; i++) {
		Cell c;
		c = healthy[i];
		int var_index = 0;

		for (int x_dim = 0; x_dim <= dim; x_dim++) {
			for (int y_dim = 0; y_dim <= dim - x_dim; y_dim++) {
				for (int z_dim = 0; z_dim <= dim - x_dim - y_dim; z_dim++) {
					qp.set_a(var_index , i, pow(c.x, x_dim) * pow(c.y, y_dim) * pow(c.z, z_dim));
					var_index++;
							
				}
			}
		}
		
 		/* We choose the constant value e=1 to avoid the fact that our restrictions are < and >.
		 * Here we use the scaling trick to overcome that >0 becomes >=1 and <0 becomes <=-1).
		 */
		qp.set_b(i, 1);

	}

	// Set up t constraints for the tumorous cells
	int t = tumor.size();
	
	for (int i=0; i<t; i++) {
		Cell c;
		c = tumor[i];
		int var_index = 0;

		for (int x_dim = 0; x_dim <= dim; x_dim++) {
			for (int y_dim = 0; y_dim <= dim - x_dim; y_dim++) {
				for (int z_dim = 0; z_dim <= dim - x_dim - y_dim; z_dim++) {
					qp.set_a(var_index , h+i, pow(c.x, x_dim) * pow(c.y, y_dim) * pow(c.z, z_dim));
					var_index++;
							
				}
			}
		}
		
		qp.set_r(i+h, CGAL::SMALLER);	
		qp.set_b(i+h, -1);

	}

	// Solve the QP
	CGAL::Quadratic_program_options options;
	options.set_pricing_strategy(CGAL::QP_BLAND); // Avoid cycles.
	Solution s = CGAL::solve_quadratic_program(qp, ET(), options);
	
	if (s.status() == CGAL::QP_INFEASIBLE)
		return false;
	else
		return true;

}


void testcase() {

	int h, t;
	cin >> h >> t;

	// Input Cells
	vector<Cell> healthy(h);
	vector<Cell> tumor(t);

	for (int i=0; i<h; ++i) {
		Cell c;
		cin >> c.x >> c.y >> c.z;
		healthy[i] = c;
	}

	for (int i=0; i<t; ++i) {
		Cell c;
		cin >> c.x >> c.y >> c.z;
		tumor[i] = c;
	}

	// TODO Maybe precompute values for the powers??

	// Use fast exponentiation to find a range for the dimension
	int dim_val = 1;
	do {
		//cout << "Trying to solve for dim_value = " << dim_val << endl;
		dim_val *= 2;
	} while ((dim_val <= 30) && (!can_solve(healthy, tumor, dim_val)));

	// Now we know that the right dimension is in the range [dim_val/2, dim_val]
	// Do a binary search to find it
	
	int min_dim = dim_val/2 - 1;
	int max_dim = (dim_val > 30) ? 30 : dim_val;

	int last_ok = false;
	while (min_dim < max_dim) {
		int mid_dim = (max_dim + min_dim) / 2;

		if (can_solve(healthy, tumor, mid_dim)) {
			// Solution in [min_dim, mid_dim]
			max_dim = mid_dim;
			last_ok = true;
		}
		else {
			//Solution in [mid_dim+1, max_dim]
			min_dim = mid_dim + 1;
			last_ok = false;
		}
	} 

	if ((min_dim == 30) && !last_ok)
		cout << "Impossible!" << endl;
	else
		cout << min_dim << endl;
	
}


int main() {

	int N;
	cin >> N;
	while (N--) {
		testcase();
	}
	
	return 0;
}
