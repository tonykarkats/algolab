#include <iostream>

using namespace std;

void testcase() {

	int n;
	cin >> n;

	int h[n];
	for (int i=0; i<n; i++)
		cin >> h[i];

	int fallen = 1;
	int hrem = h[0];
	
	for (int i=1; i<n; i++) {
		hrem--;
		if (hrem == 0)
			break;
		if (hrem >= 1)
			fallen++;
		if (h[i] > hrem)
			hrem = h[i];

	}
	
	cout << fallen << endl;

}

int main() {

	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--) {
		testcase();
	}
	return 0;
}
