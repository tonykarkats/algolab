#include <cassert>
#include <iostream>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Quotient.h>
#include <cmath>

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
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


int main() {

	int p, a, b;
	cin >> p;
	
	while (p != 0) {
		cin >> a >> b;
		const int X = 0;
		const int Y = 1;
		const int U = 2; // U=Z^2

		//cout << endl << "Problem " << p << " ->  ";	
		if (p == 1) { //Maximum Problem
			Program qp (CGAL::SMALLER, true, 0, false, 0);           // x,y >= 0
	
			qp.set_a(X, 0, 1) ; qp.set_a(Y, 0, 1); qp.set_b(0, 4);   //  x +  y <= 4
			qp.set_a(X, 1, 4) ; qp.set_a(Y, 1, 2); qp.set_b(1, a*b); // 4x + 2y <= a*b
			qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1); qp.set_b(2, 1);   // -x +  y <= 1 
	
			qp.set_d(X, X, 2*a);	qp.set_c(Y, -b); qp.set_c0(0); 					 //Obj. fun:  -b*y + a* x^2
	
			Solution s = CGAL::solve_quadratic_program(qp, ET());
			if (s.status() == CGAL::QP_INFEASIBLE)
				cout << "no" << endl;
			else if(s.is_optimal()) {
				CGAL::Quotient<ET> obj_value = -s.objective_value();
			    cout << setprecision(0) << fixed << floor(CGAL::to_double(obj_value)) << endl;

			}
				//double numerator = s.objective_value_numerator().to_double();
				//double denominator = s.objective_value_denominator().to_double();
				//cout << -ceil(numerator/denominator) + 0 << endl;
	
		}
		else { //Minimum Problem
			//Note: substituting u with z^2 so that I can have linear constraint
			Program qp (CGAL::SMALLER, false, 0, true, 0);          // x,y <= 0
			
			qp.set_a(X, 0, -1) ; qp.set_a(Y, 0, -1); 					 qp.set_b(0, 4);   // -x-y <= 4
			qp.set_a(X, 1, -4) ; qp.set_a(Y, 1, -2); qp.set_a(U, 1, -1); qp.set_b(1, a*b); // -4x -2y -u <= ab
			qp.set_a(X, 2, 1)  ; qp.set_a(Y, 2, -1); 					 qp.set_b(2, 1);   // x - y <= 1
			qp.set_u(U, false, 0);	

			qp.set_d(X, X, 2*a); qp.set_d(U, U, 2); qp.set_c(Y, b);   //Obj. fun: ax^2 + u^2 +by
	
			Solution s = CGAL::solve_quadratic_program(qp, ET());
			if (s.status() == CGAL::QP_INFEASIBLE)
				cout << "no" << endl;
			else if(s.is_optimal()) {
				CGAL::Quotient<ET> obj_value = s.objective_value();
			    cout << setprecision(0) << fixed << ceil(CGAL::to_double(obj_value)) << endl;
			}
			else
				cout << "unbounded" << endl;
		}

		cin >> p;
		
	}
	return 0;
}
