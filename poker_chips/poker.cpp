#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void testcase() {

	// Read number of stacks
	int n;
	cin >> n;

	// Read number of chips per stack
	int m[n];
	for (int i=0; i<n; i++)
		cin >> m[i];
	
	// Allocate space for every stack
	int **c;
	c = (int**)malloc(n*sizeof(int *));
	for (int i=0; i<n; i++)
		c[i] = (int *)malloc(m[i]*sizeof(int));

	for (int i=0; i<n; i++) {
		for (int j=0; j<m[i]; j++) {
			cin >> c[i][j];
		}
	}

	//Iterate over all subsets
	int max_points = solve(c, m, 	

}


int main() {

	int T;
	cin >> T;
	while (T--)
		testcase();

	return 0;
}
