#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void testcase() {

	// Read number of aliens and number of humans
	int n, m;
	cin >> n >> m;

	vector<pair<int, int> > interval;

	int superior_aliens = n;
	for (int i=0; i<n; i++) {
		int p_in, q_in;
		cin >> p_in >> q_in;
		if ((p_in == 0) && (q_in == 0)) {
			superior_aliens--;
		}
		else
			interval.push_back(make_pair(p_in, q_in));
	}

		

	// (1) Check for each human that there exists an alien that wounds him
	
	// Sort elements according to the left end
	sort(interval.begin(), interval.end());
	int rightmost = 0;

	for (int i=0; i<n; i++) {
		if (interval[i].first > rightmost + 1) {
			//cout << "Human " << rightmost + 1 << " is not wounded!" << endl;
			cout << 0 << endl;
			return;
		}
		else
			rightmost = max(rightmost, interval[i].second);
	}

	if (rightmost < m) {
		cout << "Human " << m << " is not wounded!" << endl;
		cout << 0 << endl;
		return;
	}

	// (2) Find the number of intervals which are not contained in any other interval
	// std::sort sorts our pairs by .first and then by .second

	
	rightmost = 0;
	for (int i=0; i<n; i++) {
		if (i != n-1) {
			if ((interval[i].first == interval[i+1].first) && (interval[i].second < interval[i+1].second)) {
				superior_aliens--;
				continue;
			}

		}

		if (interval[i].second <= rightmost) {
			//Alien i is not part of the solution
			superior_aliens--;
		}
		else
			rightmost = max(rightmost, interval[i].second);
	}

	cout << superior_aliens << endl;


//	vector<pair<int, int> >::iterator it;
//	cout << "Sorted by lefts " << endl;
//	for (it = interval.begin(); it != interval.end(); it++) {
//		cout << (*it).first << " " << (*it).second << endl;
//	}

}


int main() {

	int t;
	cin >> t;
	while (t--)
		testcase();

	return 0;
}
