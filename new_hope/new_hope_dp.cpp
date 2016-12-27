#include <iostream>
#include <cmath>
#include <set>
#include <vector>

using namespace std;


// Given a set of integers this function returns all the
// subsets of the set
void find_subsets(vector<int> _set, set<set<int>>& subsets) {

	int set_size = _set.size();
	int pow_set_size = pow(2, set_size);

	int counter, j;

	// Run counter from 000...0 to 111...1
	for (counter = 0; counter < pow_set_size; counter++) {
		set<int> subset;
		for (j = 0; j < set_size; j++) {
			//Check if j-th bit of counter is set
			if (counter & (1<<j)) {
				subset.insert(_set[j]);
			}
		}
		subsets.insert(subset);
	}

}

void print_pset(set<set<int>> pset) {

	//Print pset
	for (auto s : pset) {
		// s is now our set
		for (auto i : s) {
			cout << i << " ";
		}
		cout << endl;
	}
}

void testcase() {

	// This is the state for every CC. It indicates whether the CC is
	// being supervised by the first, the second, none, or both of its supervisors
	enum state {FIRST, SECOND, BOTH, NONE} ;
	
	// k: total number of command centers
	// s: number of stormtroopers per command center
	// m: number of distinct command center supervisions
	
	// Test out powerset implementation
	//	vector<int> myset = {1,2,3,4};
	//	set<set<int>> pset;
	//	find_subsets(myset, pset);
	//	print_pset(pset);

	int k, s, m;
	cin >> k >> s >> m;
	
	// These vectors store which CCs control which other CCs and vice versa
	vector<int> controls(k);
	vector<int> is_controlled(k);

	for (int i=0; i<m; i++) {
		int u, v, h;
		cin >> u >> v >> h;
		controls[u] = v;
		is_controlled[v] = u;

		for (int j=0; j<h; j++) {
			int x, y;
			cin >> x >> y;

			int from = node_id(u, x, s);
			int to = node_id(v, y, s);

		}
	}


		


}

int main() {

	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	
	while (t--) {
		testcase();
	}
	
	return 0;
}



