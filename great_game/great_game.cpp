#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int get_min_moves(int start, int n, vector<vector<int>>& trans,
				  vector<int>& min_moves, vector<int>& max_moves);

int get_max_moves(int start, int n, vector<vector<int>>& trans,
				  vector<int>& min_moves, vector<int>& max_moves) {

	// Have we reached the end?
	if (start == n-1) {
		return 0;
	}

	// Calculate only if not yet calculated
	if (max_moves[start] == -1) {
		int max_found = -1;
		
		//Iterate over the transitions until we reach the end
		vector<int>::iterator it;
		for (it = trans[start].begin(); it != trans[start].end(); ++it) {

			/* *it is now the next position we will reach
			 * Because the next player will also play however he will try to
			 * maximize our number of moves. So we have to search for the maximum number of moves
			 * from the starting point.
			 */
			
			int possible_max = get_min_moves(*it, n, trans, min_moves, max_moves);
			if (possible_max > max_found) {
				max_found = possible_max;
			}

		}

		max_moves[start] = max_found + 1;	
	}

	return max_moves[start];
}
int get_min_moves(int start, int n, vector<vector<int>>& trans,
				  vector<int>& min_moves, vector<int>& max_moves) {

	// Have we reached the end?
	if (start == n-1) {
		return 0;
	}

	// Calculate only if not yet calculated
	if (min_moves[start] == -1) {
		int min_found = INT_MAX;
		
		//Iterate over the transitions until we reach the end
		vector<int>::iterator it;
		for (it = trans[start].begin(); it != trans[start].end(); ++it) {

			/* *it is now the next position we will reach
			 * Because the next player will also play however he will try to
			 * maximize our number of moves. So we have to search for the maximum number of moves
			 * from the starting point.
			 */
			
			int possible_min = get_max_moves(*it, n, trans, min_moves, max_moves);
			if (possible_min < min_found) {
				min_found = possible_min;
			}

		}

		min_moves[start] = min_found + 1;	
	}

	return min_moves[start];
}

void testcase() {

	// n : positions
	// m : transitions
	int n, m;
	cin >> n >> m;

	// r : starting point of red meeple
	// b : starting point of black meeple
	int r, b;
	cin >> r >> b;

	// Transform to 0-based
	r--;
	b--;

	// Input transitions
	vector<vector<int>> trans(n, vector<int>());
	for (int i=0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		trans[u].push_back(v);
	}

	// Calculate minimum and maximum number of moves for red and black meeples tor reach the destination.
	// Store them to avoid recomputation.

	vector<int> min_moves(n, -1);
	vector<int> max_moves(n, -1);

	int min_red   = get_min_moves(r, n, trans, min_moves, max_moves);
	int min_black = get_min_moves(b, n, trans, min_moves, max_moves);

	// Now we have to calculate the minimum amount of moves for every player
	int min_sherlock = -1;
	int min_moriarty = -1;

	// Check parity of min_red moves
	if (min_red % 2 == 0) {
		// Compute how many steps are needed for the red meeple to reach the destination.
		// We take into account that Sherlock moves the red meeple every second turn!
		min_sherlock = ((min_red - 2) / 2) * 4 + 4;		
	}
	else {
		min_sherlock = ((min_red - 1) / 2) * 4 + 1;
	}
	
		
	// Same for min_black moves
	if (min_black % 2 == 0) {
		min_moriarty = ((min_black - 2) / 2) * 4 + 3;		
	}
	else {
		min_moriarty = ((min_black - 1) / 2) * 4 + 2;
	}

	if (min_sherlock < min_moriarty) {
		cout << 0 << endl;
	}
	else {
		cout << 1 << endl;
	}

}

int main() {

	int t;
	cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}
