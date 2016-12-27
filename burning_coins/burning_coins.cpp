#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void testcase() {

	int n;
	cin >> n;

	// This table is going to hold the values for our DP
	int F[n][n];
	int v[n];
	
	for (int i=0; i<n; i++) {
		cin >> v[i];
		//v.push_back(input);
	}

	// For subproblem [i,j] we have to choose the maximum of
	// 1) V[i] + min(F[i+2][j], F[i+1][j-1])
	// 2) V[j] + min(F[i][j-2], F[i+1][j-1])

	// We assume x = F[i+1][j-1]
	//			 y = F[i+2][j]
    //			 z = F[i][j-2]

	// We have to fill in the table diagonally
	int gap, i, j;
	for (gap = 0; gap < n; ++gap)
    {
        for (i = 0, j = gap; j < n; ++i, ++j) {
	        int x, y, z;

			x = (i+2 <= j)   ? F[i+2][j]   : 0;
			y = (i+1 <= j-1) ? F[i+1][j-1] : 0;
			z = (i <= j-2)   ? F[i][j-2]   : 0;

			F[i][j] = max(v[i] + min(y, x), v[j] + min(z, y));
		}
	}

	cout << F[0][n-1] << endl;

}

int main() {
	
	int t;
	cin >> t;

	while (t--) {
		testcase();
	}
	return 0;
}
