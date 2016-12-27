#include <iostream>
#include <vector>

using namespace std;

int even_pairs(int x[], int n) {


	vector<int> sums;
	sums.resize(n);
	sums[0] = x[0];

	for (int i=1; i<n; i++) {
		sums[i] = sums[i-1] + x[i];
	}	


	vector<int> e;
	e.resize(n);

	if (sums[0] % 2 == 0)
		e[0] = 1;
	else
		e[0] = 0;

	
	for (int i=1; i<n; i++) {
		if (sums[i] % 2 == 0)
			e[i]  = e[i-1] + 1;
		else
			e[i] = e[i-1];
	}	

	int counter = 0;
	for (int j=0; j<n; j++) {
		if (sums[j] % 2 == 0)
			counter += e[j];
		else
			counter += (j) - e[j];
	}

	return counter;

}

void testcase() {

	int n;
	cin >> n;

	int x[n][n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> x[i][j];


	// Precompute the parities of all the subcolumns 

	bool parity[n][n][n];

	for (int j=0; j<n; j++) {
		for (int i1=0; i1<n; i1++) {
			int par = x[i1][j];
			parity[i1][i1][j] = par;
			for (int i2=i1+1; i2<n; i2++) {
				par = par^x[i2][j]; 
				parity[i1][i2][j] = par;
			}
		}
	}


	// Fix i1, i2 and consider only rectangles that contain
	// rows from i1 to i2	


	int even_sums = 0;
	int a[n];
	for (int i=0; i<n;i++)
		a[i] = 0;

		
		for (int i1=0; i1<n; i1++) {
			for (int i2=i1; i2<n; i2++) {
				for (int j=0; j<n; j++) {
					a[j] = parity[i1][i2][j];
				}
				even_sums += even_pairs(a, n);
			}
		}

	cout << even_sums << endl;

}

int main() {

	int t;
	cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}
