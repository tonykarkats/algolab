#include <iostream>
#include <vector>

using namespace std;


int **stored;
int **sum_a;
int **sum_b;

int sum(int a[], int i, int j) {
	int sum = 0;
	for (int k=i; k<=j; k++)
		sum += a[k];

	return sum;
}

void precompute_sums(int a[], int b[], int n) {

	for (int i=1; i<=n; i++){
		sum_a[i][i] = a[i];
		sum_b[i][i] = b[i];
		for (int j=i+1; j<=n; j++) {
			sum_a[i][j] = sum_a[i][j-1] + a[j];
			sum_b[i][j] = sum_b[i][j-1] + b[j];
		}
	}

}

int compute(int a[], int b[], int i, int j) {

	int best, cost;	

	if (i == 1){stored[1][j] = a[1]*sum_b[1][j] ; return (a[1] * sum_b[1][j]);}
	if (j == 1){stored[i][1] = b[1]*sum_a[1][i] ; return (b[1] * sum_a[1][i]);}
	
	best = sum_a[1][i] * sum_b[1][j];

	for (int l=1; l<=i-1; l++) {
		cost = sum_a[i-l+1][i] * b[j];

		if (stored[i-l][j-1] == 0) {
			compute(a, b, i-l, j-1);
		}
		if (cost + stored[i-l][j-1] < best)
			best = cost + stored[i-l][j-1];

		
	}

	for (int m=1; m<=j-1; m++) {
		cost = sum_b[j-m+1][j] * a[i];

		if (stored[i-1][j-m] == 0)
			compute(a, b, i-1, j-m);

		if (cost + stored[i-1][j-m] < best)
			best = cost + stored[i-1][j-m];

	}

	stored[i][j] = best;
	return best;
	

}


void testcase() {
	int n;
	cin >> n;


	//Allocate memory for global arrays
	sum_a = new int*[n+1];
	sum_b = new int*[n+1];
	stored = new int*[n+1];
	for (int i=1; i<=n; i++){
		stored[i] = new int[n+1];
		sum_a[i] = new int[n+1];
		sum_b[i] = new int[n+1];
		
	}

	int a[n], b[n];

	for (int i=1; i<=n; i++) {
		cin >> a[i];
		a[i]--;
	}
	for (int i=1; i<=n; i++) {
		cin >> b[i];
		b[i]--;
	}

	precompute_sums(a, b, n);

	//Initialize best
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			stored[i][j] = 0;

//	cout << "Computing for n= " << n << endl;	
	int min_sum = compute(a, b, n, n);
	cout << min_sum << endl;
}

int main() {

	int T;
	cin >> T;
	while (T--)
		testcase();

	return 0;
}
