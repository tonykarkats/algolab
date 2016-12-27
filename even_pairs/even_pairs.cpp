#include <iostream>
#include <vector>

using namespace std;

int main() {

	int n;
	cin >> n;

	vector<int> x;

	for (int i=0; i<n; i++) {
		int x_in;
		cin >> x_in;
		x.push_back(x_in);
	}

	// Calculate partial sums
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

//	cout << e[0] << " ";
	
	for (int i=1; i<n; i++) {
		if (sums[i] % 2 == 0)
			e[i]  = e[i-1] + 1;
		else
			e[i] = e[i-1];
//		cout << e[i] << " ";
	}	

	int counter = 0;
	for (int j=0; j<n; j++) {
		if (sums[j] % 2 == 0)
			counter += e[j];
		else
			counter += (j) - e[j];
	}

//	cout << " ----" << endl;
	cout << counter << endl;
	
	return 0;
}
