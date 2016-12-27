#include <iostream>
#include <cmath>
#include <stdint.h>
#include <climits>

using namespace std;

void testcase() {

	int l, m, n;
	cin >> l >> m >> n;

	int best_a, best_b;
	int best = INT_MAX;

	if (n <= sqrt(l)) {
		for (int a=0; a <= l/m && a<=n ; a++) {
			int b = (l - a*m)/n;
			int rem = l-a*m-b*n;
			if (rem < best) {
				best = rem;
				best_a = a;
				best_b = b;
			}
		}
	}
	else   {
		for (int b=l/n; b>=0; b--) {
			int a = (l-b*n)/m;
			int rem = l-a*m-b*n;
			if (rem < best) {
				best = rem;
				best_a = a;
				best_b = b;
			}
		}

	}

	cout << best_a << " " << best_b << " " << best << endl;

}

int main() {

	std::ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}
